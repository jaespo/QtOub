#pragma once
//
//	Logon server message formats
//
//	(C) 2016 by Jeffery A Esposito
//
#include "..\OubLib\misc.h"
#include "..\OubLib\msg.h"

enum ELogonServerReqCode
{
	kLogon,
	kLogoff,
	kGetWorldServers
};

//
//	A logon request
//
class CLogonReq: public CReq
{
public:
	YUserId			mUserId;
	YPassword		mPassword;
};

//
//	A response to a logon request
//
class CLogonRsp: public CRsp
{
	//
	//	All of the members are in the base CRsp
};
