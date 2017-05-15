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

namespace jlib
{
	//
	//	The following class is static and is used to initialize
	//	the socket library.
	//
	class CSocketInitializer
	{
	public:
		CSocketInitializer();
		~CSocketInitializer();

	private:
		static CSocketInitializer	mgInst;
	};

	//
	//	The base class for the CClientSocket and CServerSocket 
	//	classes
	//
	class CBaseSocket
	{
	public:
		CBaseSocket(
			SOCKET					vWsaSocket,
			const std::string&		rsIpAddr,
			const std::string&		rsPort);
		~CBaseSocket();

		std::string GetIpAndPort() { return msIpAddr + ":" + msPort; }
		void Disconnect();

	protected:
		void WriteMsg( const CMsg& rMsg );
		bool ReadMsg( const CMsg& rMsg );
 
		std::string 		msIpAddr;
		std::string			msPort;
		SOCKET				mWsaSocket;
	};

	//
	//  A class that represents a socket as used by a client
	//
	class CClientSocket : public CBaseSocket
	{
	public:
		typedef std::shared_ptr<CClientSocket>	Yq;

		CClientSocket(
			const std::string&		rsIpAddr,
			const std::string&		rsPort)
			: CBaseSocket(INVALID_SOCKET, rsIpAddr, rsPort) {}
		~CClientSocket() {}

		void Connect();
		void SetReqTimeout(__int32 vMillisecs);
		bool WriteRead(CReq& rReq, CRsp& rRsp);
	};

	//
	//  A class that represents a socket as used by a server
	//
	class CServerSocket : public CBaseSocket
	{
	public:
		typedef std::shared_ptr<CServerSocket>	Yq;

		CServerSocket(
			SOCKET					vWsaSocket,
			const std::string&		rsIpAddr,
			const std::string&		rsPort)
			: CBaseSocket(vWsaSocket, rsIpAddr, rsPort) {}
		~CServerSocket();

		bool ReadReq(CReq& rReq);
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

		CServerSocket::Yq GetSocket() { return mqSocket; }
		void RunLoop(CServerSocket::Yq qSocket);
		virtual void DoProcessReq(const CReq& rReq, const CRsp& rRsp) = 0;

		static void RunThread(CHandler::Yq qHandler, CServerSocket::Yq qSocket);

	private:
		std::shared_ptr<CServerSocket>		mqSocket;
	};

	//
	//  A class that listens in a loop, creating handler threads when they
	//	connect.
	//
	class CListener
	{
	public:
		void InitListener(const std::string& rsIpaddr, const std::string& rsPort);
		void ListenLoop();
		std::string GetIpAndPort() { return msIpAddr + ":" + msPort; }

	private:
		typedef std::shared_ptr<std::thread>	YqThread;
		virtual std::shared_ptr<CHandler> CreateHandler() = 0;

		std::string				msIpAddr;
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
		TListener(const std::string& rsIpaddr, const std::string& rsPort)
		{
			InitListener(rsIpaddr, rsPort);
		}

	private:
		virtual CHandler::Yq CreateHandler()
		{
			return CHandler::Yq(new AHandler);
		}
	};


};	// namespace oub