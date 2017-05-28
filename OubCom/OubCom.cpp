//
// OubCom.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include <cstring>

#include "..\JLib\trace.h"
#include "OubCom.h"

//
//	Statics
//
NIFTY_STATIC_IMPL( jlib, CClientSocket, oub, CLogonSvrConnection,
	mClientSocket, LOGONSVR_IP, LOGONSVR_PORT )

// jlib::CClientSocket	oub::CLogonSvrConnection::mClientSocket(
//	LOGONSVR_IP, LOGONSVR_PORT);

void oub::CCmdConnect::Exec()
{
	CLogonSvrConnection::GetClientSocket().Connect();
}

//
//	Executes the help command
//
void oub::CCmdHelp::Exec()
{
	std::cout << "c, connect	connect to the logon server" << std::endl;
	std::cout << "h, help		display a list of commands" << std::endl;
	std::cout << "q, quit		exit OubCom" << std::endl;
}

//
//	Executes the help command
//
void oub::CCmdQuit::Exec()
{
	std::cout << "bye!" << std::endl;
	exit(EXIT_SUCCESS);
}

//
//	Executes a command
//
void oub::CCmdProcessor::ExecCmd(const std::vector<std::string>& rTokVect)
{
	if (rTokVect.empty())
		return;
	else if (rTokVect[0] == "quit" || rTokVect[0] == "q")
		oub::CCmdQuit::Exec();
	else if (rTokVect[0] == "help" || rTokVect[0] == "h")
		oub::CCmdHelp::Exec();
	else if (rTokVect[0] == "connect" || rTokVect[0] == "c")
		oub::CCmdConnect::Exec();
	else
		std::cout << "Unknown command: " << rTokVect[0];
}

//
//	Reads a command line and returns a vector of tokens
//
void oub::CCmdProcessor::ReadCmd(std::vector<std::string>& rTokVect)
{
	std::string		sCmdLine;
	char*			pzArg;
	char*			pzNextTok = NULL;

	std::cout << "OubCom> ";
	std::getline(std::cin, sCmdLine);
	rTokVect.erase(rTokVect.begin(), rTokVect.end());
	pzArg = strtok_s((char*)sCmdLine.c_str(), " ", &pzNextTok);
	while (pzArg != NULL)
	{
		rTokVect.push_back(pzArg);
		pzArg = strtok_s(NULL, " ", &pzNextTok);
	}
}

//
//	Command processer run loop
//
void oub::CCmdProcessor::Run()
{
	std::vector<std::string>		vTokVect;
	while (true)
	{
		ReadCmd(vTokVect);
		ExecCmd(vTokVect);
	}
}

//
//	Main 
//
int main()
{
	oub::CCmdProcessor				vCmdProcessor;

	TR("OubCom", "Startng Oubcom");
	std::cout << "OubCom ~ Oub Command Line Interpreter" << std::endl;
	std::cout << "(C) 2017 by Jeffery A Esposito" << std::endl;

	vCmdProcessor.Run();

	return 0;
}

