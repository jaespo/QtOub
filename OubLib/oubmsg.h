//
//	(C) 2016 by Jeffery A Esposito
//
#pragma once
#include "..\JLib\misc.h"
#include "..\JLib\msg.h"
#include "oubmisc.h"

#define LOGONSVR_IP					"localhost"
#define LOGONSVR_PORT				"27016"
#define LOGONSVR_CONNECT_TIMEOUT	10000

namespace oub
{
	const unsigned __int16		kLogonServerPort = 3141;

	enum ELogonServerReqCode
	{
		kReqCodeLogon,
		kReqCodeLogoff,
		kReqGetWorldServers
	};

	//
	//	A logon request
	//
	class CLogonReq : public jlib::CReq
	{
	public:
		YUserId			mUserId;
		YPassword		mPassword;

		std::string traceStr() const;
	};

	//
	//	A response to a logon request
	//
	class CLogonRsp : public jlib::CRsp
	{
		//
		//	All of the members are in the base CRsp
		//
		
		std::string traceStr() const;

	};
};	// namespace oub
