// LogonServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\OubLib\tcp.h"
#include "Msg.h"
#include "LogonHandler.h"

//
// Need to link with Ws2_32.lib
//
#pragma comment (lib, "Ws2_32.lib")
 
#define DEFAULT_PORT	"27015"

int main()
{

	oub::TListener<oub::CLogonHandler>	vListener("localhost", DEFAULT_PORT);
	char								ch;

	std::cout
		<< "QtOub Logon Server ~ (C) 2016 by Jeffery A Esposito"
		<< std::endl;
	vListener.ListenLoop();
	std::cin >> ch;
	return 0;
}


