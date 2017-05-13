// LogonServer.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "..\JLib\tcp.h"
#include "..\OubLib\oubmsg.h"
#include "LogonHandler.h"
#include "..\JLib\trace.h"
#include "..\OubDb\OubDb.h"

//
// Need to link with Ws2_32.lib
//
#pragma comment (lib, "Ws2_32.lib")
 
int main()
{
	jlib::CTrace::inst().EnableTag("tcp");
	jlib::TListener<oub::CLogonHandler>	vListener( LOGONSVR_IP, LOGONSVR_PORT );

	std::cout
		<< "QtOub Logon Server ~ (C) 2016 by Jeffery A Esposito"
		<< std::endl;
	vListener.ListenLoop();
	return 0;
}


