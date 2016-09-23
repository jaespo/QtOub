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

		bool ReadUpdate(CReq& rReq);
		void Reply(CRsp& rRsp);			// TODO ...

	private:
		SOCKET		mSocket;
	};

	//
	//	Handler thread base class.
	//
	class CHandler
	{
	public:
		virtual ~CHandler() {}

		std::shared_ptr<CSocket> GetSocket() { return mqSocket; }
		void operator()(std::shared_ptr<CSocket> qSocket);
		virtual void DoProcessReq(const CReq& rReq) {};

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
		CListener(const std::string& rsIpaddr, const std::string& vPort);// TODO
		void ListenLoop(); // TODO

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
		TListener(const std::string& rsIpaddr, const std::string& rsPort) :
			CListener(rsIpaddr, rsPort) {}

	private:
		virtual std::shared_ptr<CHandler> CreateHandler() 
		{ 
			return std::shared_ptr<CHandler>( new AHandler ); 
		}
	};


};	// namespace oub