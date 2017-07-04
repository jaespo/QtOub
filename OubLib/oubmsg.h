#ifndef __OUBMSG_H__
#define __OUBMSG_H__

//
//	(C) 2016 by Jeffery A Esposito
//
#include "..\JLib\misc.h"
#include "..\JLib\msg.h"
#include "oubmisc.h"

#define LOGONSVR_IP					"localhost"
#define LOGONSVR_PORT				"27016"
#define LOGONSVR_CONNECT_TIMEOUT	10000

namespace oub
{
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

		std::string TraceStr() const;
	};

	//
	//	A response to a logon request
	//
	class CLogonRsp : public jlib::CRsp
	{
	public:
		enum ERspCode
		{
			kRcOk,
			kRcDbError,
			kRcUserNotFound,
			kRcBadPassword
		};

		//
		//	All of the members are in the base CRsp
		//
		std::string TraceStr() const;

	};
};	// namespace oub

#endif 
