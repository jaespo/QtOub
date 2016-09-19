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
#include <string>

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
		CSocket(SOCKET vSocket) { mSocket = vSocket; }
		~CSocket();

		void ReadUpdate(CReq& rReq);
		void Reply(CRsp& rRsp);

	private:
		SOCKET		mSocket;
	};

	//
	//  A class that listens in a loop, creating handler threads when they
	//	connect.
	//
	class CListener
	{
	public:
		CListener(const std::string& rsIpaddr, const std::string& rsPort);
		void ListenLoop();

	private:
		virtual std::shared_ptr<CHandler> CreateHandler() = 0;

		std::string		msIpaddr;
		std::string		msPort;
	};

	//
	//  A class that listens in a loop, creating handler threads when they
	//	connect.
	//
	template<class AHandler> class TListener : public CListener
	{
	public:
		TListener(const std::string& rIpaddr, const std::string& rsPort)
			: CHandler(rIpaddr, vPort) {}

	private:
		virtual shared_ptr<CHandler> CreateHandler() { return shared_ptr( new AHandler ); }
	};

	//
	//	Handler thread base class.
	//
	class CHandler
	{
	public:
		virtual ~CHandler() {}
		void operator()( SOCKET vSocket );
		virtual void DoProcessReq(const CReq& rReq) = 0;
	};

};	// namespace oub