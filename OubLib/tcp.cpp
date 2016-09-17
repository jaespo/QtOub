#pragma once
///////////////////////////////////////////////////////////////////////////
//
// (C) 2016  by Jeffery A Esposito
//
///////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "tcp.h"

//
//	ctor of the listener
//
CListener::CListener(const std::string& rsIpaddr, __int16 vPort)
{
	msIpaddr = rsIpaddr;
	mPort = vPort;
}

//
//	Runs the listen loop.
//
void CListener::ListenLoop()
{
	WSADATA				wsaData;
	int					iResult;
	int					iSendResult;
	SOCKET				ListenSocket = INVALID_SOCKET;
	SOCKET				ClientSocket = INVALID_SOCKET;

	struct addrinfo*	result = NULL;
	struct addrinfo		hints;

	char				recvbuf[DEFAULT_BUFLEN];
	int					recvbuflen = DEFAULT_BUFLEN;


	//
	//	Initialize Winsock
	//
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		std::cerr << "WSAStartup failed with error: " << iResult << std::endl;
		return 1;
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
		std::cerr << "getaddrinfo failed with error: " << iResult << std::endl;
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
}

}

