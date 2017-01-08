// LogonServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\OubLib\tcp.h"
#include "Msg.h"
#include "LogonHandler.h"
#include "..\OubLib\trace.h"

//
// Need to link with Ws2_32.lib
//
#pragma comment (lib, "Ws2_32.lib")
 
int main()
{
	oub::CTrace::inst().EnableTag("tcp");
	oub::TListener<oub::CLogonHandler>	vListener( LOGONSVR_IP, LOGONSVR_PORT );

	std::cout
		<< "QtOub Logon Server ~ (C) 2016 by Jeffery A Esposito"
		<< std::endl;
	vListener.ListenLoop();
	return 0;
}


