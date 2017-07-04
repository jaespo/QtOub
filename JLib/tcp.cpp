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
//	Statics
//
NIFTY_STATIC_IMPL( jlib, CSocketInitializer, jlib, CSocketInitializer, mgInst )

jlib::CBaseSocket::CBaseSocket(
	SOCKET					vWsaSocket,
	const std::string&		rsIpAddr,
	const std::string&		rsPort)
{
	mWsaSocket = vWsaSocket;
	msIpAddr = rsIpAddr;
	msPort = rsPort;
}

//
//	dtor for the base socket 
//
jlib::CBaseSocket::~CBaseSocket()
{
	Disconnect();
}

//
//	disconnect from the socket.  If it is not connected, 
//	do nothing.  Ignores errors are we may just be trying to shutdown
//
void jlib::CBaseSocket::Disconnect()
{
	if (mWsaSocket != INVALID_SOCKET)
	{
		closesocket(mWsaSocket);
		mWsaSocket = INVALID_SOCKET;
	}
	TR("tcp",
		<< GetIpAndPort()
		<< ": Disconnected");
}

//
//	reads a message from the socket.  Returns an EOF flag
//
jlib::CMsg::Yq jlib::CBaseSocket::ReadMsg()
{
	char			pBuf[DEFAULT_BUFLEN];
	int32_t			vTotCountRead = 0;
	int32_t			vCountRead;
	int16_t			vReqSize;
	bool			bGotLen = false;
	bool			bDone = false;

	TR("tcp",
		<< GetIpAndPort()
		<< ": ReadMsg initiated");
	//
	//	The data may come in in clumps, so loop reading them until the request
	//	fills up.
	//
	while (!bDone)
	{
		//
		//	Read some data and return if we are at EOF
		//
		vCountRead = recv(mWsaSocket, pBuf + vTotCountRead,
			DEFAULT_BUFLEN - vTotCountRead, 0);
		TR("tcp",
			<< GetIpAndPort()
			<< ": recv() completed with "
			<< vCountRead
			<< " bytes");
		if (vCountRead == 0 || vCountRead == -1 )
		{
			TR("tcp", 
				<< GetIpAndPort()
				<< ": ReadMsg EOF");
			return nullptr;
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
		if (vTotCountRead > vReqSize)
		{
			THROW_ERR(9999,
				<< GetIpAndPort()
				<< ": too much data received, expected "
				<< vReqSize
				<< " got "
				<< vTotCountRead);
		}

		bDone = (vTotCountRead == vReqSize);
	}
	TR("tcp",
		<< GetIpAndPort()
		<< ": ReadUpdate completed with "
		<< vTotCountRead
		<< " bytes");
	jlib::CRsp::Yq qMsg = jlib::CRsp::Yq((jlib::CRsp*)( new char[vTotCountRead] ));
	memcpy((void *)qMsg.get(), pBuf, vTotCountRead);
	return qMsg;
}

//
//	sends the specified buffer.
//
void jlib::CBaseSocket::WriteMsg( const CMsg& rMsg )
{
	int				iSendResult;

	iSendResult = send(mWsaSocket, (const char*)&rMsg, rMsg.mMsgLen, 0);
	if (iSendResult == SOCKET_ERROR)
	{
		long err = WSAGetLastError();
		THROW_ERR(7,
			<< GetIpAndPort()
			<< ": send failed with error: "
			<< err);
	}
	TR("tcp",
		<< GetIpAndPort() 
		<< ": sent "
		<< rMsg.mMsgLen
		<< " bytes");
}

//
//	ctor for a client socket
//
void jlib::CClientSocket::Connect()
{
	struct addrinfo		*result = NULL,
						*ptr = NULL,
						hints;
	int					iResult;

	if (mWsaSocket != INVALID_SOCKET)
	{
		THROW_ERR( 9999, 
			<< GetIpAndPort() 
			<< ": already connected" )
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	//
	//	Resolve the server address and port
	//
	iResult = getaddrinfo(msIpAddr.c_str(), msPort.c_str(), &hints, &result);
	if (iResult != 0)
	{
		THROW_ERR(9999, 
			<< GetIpAndPort() 
			<< ": getaddrinfo failed with error: " 
			<< iResult);
	}

	//
	//	Attempt to connect to an address until one succeeds
	//
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
	{
		//
		//	Create a SOCKET for connecting to server
		//
		mWsaSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (mWsaSocket == INVALID_SOCKET)
		{
			THROW_ERR(9999, 
				<< GetIpAndPort()
				<< ": socket() failed with error: "
				<< WSAGetLastError());
		}

		//
		//	Connect to server.
		//
		iResult = connect(mWsaSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) 
		{
			closesocket(mWsaSocket);
			mWsaSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if ( mWsaSocket == INVALID_SOCKET ) 
	{
		THROW_ERR(9999,
			<< GetIpAndPort()
			<< ": unable to connect");
	}

	TR("tcp",
		<< GetIpAndPort()
		<< ": Connected");
}

//
//	Sets the timeout on calls to WriteRead()
//
void jlib::CClientSocket::SetReqTimeout(int32_t vMillisecs)
{
	if (!setsockopt(mWsaSocket, SOL_SOCKET, SO_RCVTIMEO,
		(const char*)&vMillisecs, sizeof(vMillisecs)))
	{
		THROW_ERR(9999, 
			<< GetIpAndPort()
			<< ": setsocketop failed, error: "
			<< WSAGetLastError() );
	}
	TR("tcp",
		<< GetIpAndPort()
		<< "SetReqTimeout to " << vMillisecs << "ms");
}

//
//	Writes a request to the client socket and reads the response
//
jlib::CRsp::Yq jlib::CClientSocket::WriteRead(CReq& rReq)
{
	WriteMsg(rReq);
	jlib::CMsg::Yq qMsg = ReadMsg();
	jlib::CRsp::Yq qRsp = std::dynamic_pointer_cast<jlib::CRsp>( qMsg );
	if ( qRsp == nullptr )
	{
		THROW_ERR(9999,
			<< GetIpAndPort()
			<< ": EOF on read of response");
	}
	return qRsp;
}

//
//	Called when the handler thread starts
//
void jlib::CHandler::RunLoop(CServerSocket::Yq qSocket)
{
	char					pRspBuf[DEFAULT_BUFLEN];
	CReq::Yq				qReq;
	CRsp*					pRsp = (CRsp*)pRspBuf;

	TR("tcp", 
		<< qSocket->GetIpAndPort() 
		<< ": handler run loop started");
	mqSocket = qSocket;
	//
	//	Loop reading requests
	//
	while (true)
	{
		try
		{
			qReq = qSocket->ReadReq();
			if (qReq == nullptr)
				return;
		}
		catch (std::shared_ptr<CErrorInfo> qError)
		{
			std::cerr << qError->GetText() << std::endl;
			return;
		}

		DoProcessReq(*qReq, *pRsp);
		mqSocket->Reply(*pRsp);
	}
}

//
//	Called by std::thread when it wants to start running the thread
//
void jlib::CHandler::RunThread(CHandler::Yq qHandler, CServerSocket::Yq qSocket)
{
	qHandler->RunLoop(qSocket);
}

//
//	ctor of the listener
//
void jlib::CListener::InitListener(
	const std::string&	rsIpAddr, 
	const std::string&	rsPort)
{
	msIpAddr = rsIpAddr;
	msPort = rsPort;
}

//
//	Runs the listen loop.
//
void jlib::CListener::ListenLoop()
{
	int					iResult;
	SOCKET				vListenSocket = INVALID_SOCKET;
	SOCKET				vClientSocket = INVALID_SOCKET;

	struct addrinfo*	result = NULL;
	struct addrinfo		hints;

	TR("tcp", 
		<< GetIpAndPort()
		<< ": CListener::ListenLoop started");

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
		THROW_ERR(2, 
			<< GetIpAndPort() 
			<< "getaddrinfo failed with error: " 
			<< iResult);
	}

	//
	// Create a SOCKET for connecting to server
	//
	vListenSocket = socket(
		result->ai_family, result->ai_socktype, result->ai_protocol);
	if (vListenSocket == INVALID_SOCKET)
	{
		long err = WSAGetLastError();
		freeaddrinfo(result);
		THROW_ERR(3, 
			<< GetIpAndPort()
			<< ": socket() failed with error: " << err);
	}

	//
	// Setup the TCP listening socket
	//
	iResult = bind(vListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		long err = WSAGetLastError();
		freeaddrinfo(result);
		closesocket(vListenSocket);
		THROW_ERR(4, 
			<< GetIpAndPort()
			<< ": bind failed with error: " << err);
	}

	freeaddrinfo(result);

	//
	//	Listen for a connection
	//
	TR("tcp", 
		<< GetIpAndPort() 
		<< ": posting listen on port " 
		<< msPort);
	iResult = listen(vListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
		long err = WSAGetLastError();
		closesocket(vListenSocket);
		THROW_ERR(5, 
			<< GetIpAndPort() 
			<< ": listen failed with error: " 
			<< err);
	}

	while (true)
	{
		//
		//	Accept a client socket
		//
		TR("tcp", 
			<< GetIpAndPort()
			<< ": posting accept");
		vClientSocket = accept(vListenSocket, NULL, NULL);
		TR("tcp", 
			<< GetIpAndPort()
			<< ": accept completed");
		if (vClientSocket == INVALID_SOCKET)
		{
			long err = WSAGetLastError();
			closesocket(vListenSocket);
			THROW_ERR(6, 
				<< GetIpAndPort()
				<< ": accept failed with error: " 
				<< err);
		}

		//
		//	Start the handler thread
		//
		CServerSocket::Yq 	qSocket(
			new CServerSocket(vClientSocket, msIpAddr, msPort));
		CHandler::Yq		qHandler(CreateHandler());
		YqThread			qThread( 
			new std::thread(CHandler::RunThread, qHandler, qSocket));
		mThreadVect.push_back(qThread);
	}
}

	
//
//	ctor for the socket initializer class.
//
jlib::CSocketInitializer::CSocketInitializer()
{
	WSADATA				wsaData;

	//
	//	Initialize Winsock
	//
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		THROW_ERR(1, << "WSAStartup failed with error: " << iResult);
	}
}

//
//	dtor for winsock
//
jlib::CSocketInitializer::~CSocketInitializer()
{
	WSACleanup();
}



//
//	dtor for a CSocket
//
jlib::CServerSocket::~CServerSocket()
{
	shutdown(mSocket, SD_BOTH);
	closesocket(mSocket);
}

//
//	Reads a request
//
//	nullptr means EOF
//
jlib::CReq::Yq jlib::CServerSocket::ReadReq()
{
	return std::dynamic_pointer_cast<jlib::CReq>( ReadMsg() );
}

//
//	Writes a reply to request
//
void jlib::CServerSocket::Reply(CRsp& rRsp)
{
	TR("tcp",
		<< GetIpAndPort()
		<< ": replying with rsp "
		<< rRsp.TraceStr());
	WriteMsg( rRsp );
}



