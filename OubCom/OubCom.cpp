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
	mgClientSocket, LOGONSVR_IP, LOGONSVR_PORT )

//
//	Executes the connect command
//
void oub::CCmdConnect::Exec()
{
	try
	{
		CLogonSvrConnection::GetClientSocket().Connect();
	}
	catch (jlib::CErrorInfo& rErrorInfo )
	{
		std::cout << rErrorInfo.GetText() << std::endl;
	}
}

//
//	Executes the help command
//
void oub::CCmdHelp::Exec()
{
	std::cout << "c, connect	connect to the logon server" << std::endl;
	std::cout << "h, help		display a list of commands" << std::endl;
	std::cout << "l, logon		issue logon request to the logon server" << std::endl;
	std::cout << "q, quit		exit OubCom" << std::endl;
}

//
//	Executes the logon command
//
void oub::CCmdLogon::Exec(const std::vector<std::string>& rTokVect)
{
	//
	//	Format a logon request
	//
	oub::CLogonReq		vReq;
	oub::CLogonRsp::Yq	qRsp;

	vReq.mReqCode = oub::ELogonServerReqCode::kReqCodeLogon;
	vReq.mReqSeq = jlib::CReq::GetNextReqSeq();
	vReq.mMsgLen = sizeof(oub::CLogonReq);
	if (rTokVect.size() < 2)
	{
		std::cout << "Error: expected logon <user> <pwd>" << std::endl;
		return;
	}
	FILLFIELD(vReq.mUserId, rTokVect[1] );
	FILLFIELD(vReq.mPassword, rTokVect[2] );

	try
	{
		qRsp = CLogonSvrConnection::GetClientSocket().WriteRead( vReq );
	}
	catch (jlib::CErrorInfo& rErrorInfo)
	{
		std::cout << rErrorInfo.GetText() << std::endl;
	}
	std::cout << qRsp->TraceStr() << std::endl;
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
	else if (rTokVect[0] == "logon" || rTokVect[0] == "l")
		oub::CCmdLogon::Exec( rTokVect );
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

