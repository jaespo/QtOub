// LogonServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\OubLib\tcp.h"
#include "Msg.h"

//
// Need to link with Ws2_32.lib
//
#pragma comment (lib, "Ws2_32.lib")
 
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT 27015

int main()
{

	CListener<CLogonHandler>	vListener("localhost", DEFAULT_PORT);
	char						ch;

	std::cout
		<< "QtOub Logon Server ~ (C) 2016 by Jeffery A Esposito"
		<< std::endl;
	vListener.listenLoop();
	std::cin >> ch;
	return 0;
}

	// No longer need server socket
	closesocket(ListenSocket);

	// Receive until the peer shuts down the connection
	do {

		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);

			// Echo the buffer back to the sender
			iSendResult = send(ClientSocket, recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				return 1;
			}
			printf("Bytes sent: %d\n", iSendResult);
		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}

	} while (iResult > 0);

	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();

	return 0;
}


}

