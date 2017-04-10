///////////////////////////////////////////////////////////////////////////
//
// (C) 2016  by Jeffery A Esposito
//
///////////////////////////////////////////////////////////////////////////
#include <memory>
#include <iostream>
#include <thread>
#include "tcp.h"
#include "trace.h"

//
//	Called when the handler thread starts
//
void jlib::CHandler::RunLoop(CSocket::Yq qSocket)
{
	char					pReqBuf[DEFAULT_BUFLEN];
	char					pRspBuf[DEFAULT_BUFLEN];
	CReq*					pReq = (CReq*)pReqBuf;
	CRsp*					pRsp = (CRsp*)pRspBuf;

	TR("tcp", << "Handler run loop started");
	mqSocket = qSocket;
	//
	//	Loop reading requests
	//
	while (true)
	{
		try
		{
			bool bEof = mqSocket->ReadUpdate(*pReq);
			if (bEof)
				return;
		}
		catch (std::shared_ptr<CErrorInfo> qError)
		{
			std::cerr << qError->GetText() << std::endl;
			return;
		}

		DoProcessReq(*pReq, *pRsp);
		mqSocket->Reply(*pRsp);
	}
}

//
//	Called by std::thread when it wants to start running the thread
//
void jlib::CHandler::RunThread(CHandler::Yq qHandler, CSocket::Yq qSocket)
{
	qHandler->RunLoop(qSocket);
}

//
//	ctor of the listener
//
void jlib::CListener::InitListener(const std::string& rsIpaddr, const std::string& vPort)
{
	msIpaddr = rsIpaddr;
	msPort = vPort;
}

//
//	Runs the listen loop.
//
void jlib::CListener::ListenLoop()
{
	WSADATA				wsaData;
	int					iResult;
	SOCKET				ListenSocket = INVALID_SOCKET;
	SOCKET				ClientSocket = INVALID_SOCKET;

	struct addrinfo*	result = NULL;
	struct addrinfo		hints;

	TR("tcp", << "Listener::ListenLoop started");

	//
	//	Initialize Winsock
	//
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		THROW_ERR(1, << "WSAStartup failed with error: " << iResult);
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	//
	// Resolve the server address and port
	//
	iResult = getaddrinfo(NULL, msPort.c_str(), &hints, &result);
	if (iResult != 0)
	{
		WSACleanup();
		THROW_ERR(2, << "getaddrinfo failed with error: " << iResult);
	}

	//
	// Create a SOCKET for connecting to server
	//
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET)
	{
		long err = WSAGetLastError();
		freeaddrinfo(result);
		WSACleanup();
		THROW_ERR(3, << "socket failed with error: " << err);
	}

	//
	// Setup the TCP listening socket
	//
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		long err = WSAGetLastError();
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		THROW_ERR(4, << "bind failed with error: " << err);
	}

	freeaddrinfo(result);

	//
	//	Listen for a connection
	//
	TR("tcp", << "posting listen on port " << msPort);
	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
		long err = WSAGetLastError();
		closesocket(ListenSocket);
		WSACleanup();
		THROW_ERR(5, << "listen failed with error: " << err);
	}

	while (true)
	{
		//
		//	Accept a client socket
		//
		TR("tcp", << "posting accept");
		ClientSocket = accept(ListenSocket, NULL, NULL);
		TR("tcp", << "accept completed");
		if (ClientSocket == INVALID_SOCKET)
		{
			long err = WSAGetLastError();
			closesocket(ListenSocket);
			WSACleanup();
			THROW_ERR(6, << "accept failed with error: " << err);
		}

		//
		//	Start the handler thread
		//
		CSocket::Yq 	qSocket(new CSocket(ClientSocket));
		CHandler::Yq	qHandler(CreateHandler());
		YqThread		qThread(
			new std::thread(CHandler::RunThread, qHandler, qSocket));
		mThreadVect.push_back(qThread);
	}
}

//
//	dtor for a CSocket
//
jlib::CSocket::~CSocket()
{
	shutdown(mSocket, SD_BOTH);
	closesocket(mSocket);
}

//
//	Reads a request
//
//	returns an EOF flag
//
bool jlib::CSocket::ReadUpdate(CReq& rReq)
{
	char			pBuf[DEFAULT_BUFLEN];
	__int32			vTotCountRead = 0;
	__int32			vCountRead;
	__int16			vReqSize;
	bool			bGotLen = false;
	bool			bDone = false;

	TR("tcp", << "ReadUpdate initiated");
	//
	//	The data may come in in clumps, so loop reading them until the request
	//	fills up.
	//
	while (!bDone)
	{
		//
		//	Read some data and return if we are at EOF
		//
		vCountRead = recv(mSocket, pBuf + vTotCountRead,
			DEFAULT_BUFLEN - vTotCountRead, 0);
		TR("tcp", << "recv() completed with " << vCountRead << " bytes");
		if (vCountRead == 0)
		{
			TR("tcp", << "ReadUpdate EOF");
			return true;
		}

		//
		//	Extract the request size if we havent done so already
		//
		vTotCountRead += vCountRead;
		if (!bGotLen && vTotCountRead > sizeof(vReqSize))
		{
			bGotLen = true;
			memcpy(&vReqSize, pBuf, sizeof(vReqSize));
		}

		//
		//	check to see if we have the full request
		//
		bDone = (vTotCountRead >= vReqSize);
		if (bDone)
		{
			memcpy(&rReq, pBuf, vTotCountRead);
		}
	}
	TR("tcp", << "ReadUpdate completed with " << vTotCountRead << " bytes");
	return false;
}

//
//	Writes a reply to request
//
void jlib::CSocket::Reply(CRsp& rRsp)
{
	int				iSendResult;

	iSendResult = send(mSocket, (const char *)&rRsp, rRsp.mMsgLen, 0);
	if (iSendResult == SOCKET_ERROR)
	{
		long err = WSAGetLastError();
		THROW_ERR(7, << "send failed with error: " << err);
		closesocket(mSocket);
		WSACleanup();
	}
	TR("tcp", << "Replied with " << rRsp.mMsgLen << " bytes");
}



