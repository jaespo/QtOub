#pragma once
///////////////////////////////////////////////////////////////////////////////
//
//	Tcp/Ip utilities
//
//	(C) 2016 by Jeffery A Esposito
//
///////////////////////////////////////////////////////////////////////////////

//
//	std includes
//
#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include <string>
#include <vector>
#include <thread>

//
//	Winsock related includes
//
#undef UNICODE
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

//
//	Project includes
//
#include "misc.h"
#include "msg.h"

#define DEFAULT_BUFLEN	4096

namespace oub {

	//
	//  A class that represents a socket
	//
	class CSocket
	{
	public:
		typedef std::shared_ptr<CSocket>	Yq;

		CSocket(SOCKET vSocket) { mSocket = vSocket; }
		~CSocket();

		bool ReadUpdate(CReq& rReq);
		void Reply(CRsp& rRsp);

	private:
		SOCKET		mSocket;
	};

	//
	//	Handler thread base class.
	//
	class CHandler
	{
	public:
		typedef std::shared_ptr<CHandler>	Yq;
		virtual ~CHandler() {}

		CSocket::Yq GetSocket() { return mqSocket; }
		void RunLoop(CSocket::Yq qSocket);
		virtual void DoProcessReq(const CReq& rReq, const CRsp& rRsp ) = 0;

		static void RunThread(CHandler::Yq qHandler, CSocket::Yq qSocket);
			
	private:
		std::shared_ptr<CSocket>		mqSocket;
	};

	//
	//  A class that listens in a loop, creating handler threads when they
	//	connect.
	//
	class CListener
	{
	public:
		CListener(const std::string& rsIpaddr, const std::string& vPort);
		void ListenLoop();
		
	private:
		typedef std::shared_ptr<std::thread>	YqThread;
		virtual std::shared_ptr<CHandler> CreateHandler() = 0;

		std::string				msIpaddr;
		std::string				msPort;
		std::vector<YqThread>	mThreadVect;
	};

	//
	//  A class that listens in a loop, creating handler threads when they
	//	connect.  Most of the functionality is in CListener.
	//
	template<class AHandler> class TListener : public CListener
	{
	public:
		TListener(const std::string& rsIpaddr, const std::string& rsPort) :
			CListener(rsIpaddr, rsPort) {}

	private:
		virtual CHandler::Yq CreateHandler() 
		{ 
			return CHandler::Yq( new AHandler ); 
		}
	};


};	// namespace oub