#pragma once
///////////////////////////////////////////////////////////////////////////////
//
//	Tcp/Ip utilities
//
//	(C) 2016 by Jeffery A Esposito
//
///////////////////////////////////////////////////////////////////////////////

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

#include "misc.h"

#define DEFAULT_BUFLEN	4096

//
//  A class that listens in a loop, creating handler threads when they
//	connect.
//
class CListener
{
public:
	CListener(const std::string& rsIpaddr, const std::string& rsPort);
	void ListenLoop(); // TODO ...

private:
	virtual CHandler* CreateHandler() = 0;

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
	TListener(const std::string& rIpaddr, const std::string& rsPort )
		: CHandler(rIpaddr, vPort) {}
	
private:
	virtual CHandler* CreateHandler() { return new AHandler; }
};

//
//	Handler thread
//
class CHandler
{
	virtual void OnReqReceived( const CReq& rReq ) = 0;
};