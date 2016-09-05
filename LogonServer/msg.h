#pragma once
//
//	Logon server message formats
//
//	(C) 2016 by Jeffery A Esposito
//

#include "..\OubLib\oubtypes.h"
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
	YUserId			mUserId;
	YPassword		mPassword;
};

//
//	A response to a logon request
//
class CLogonRsp: public CRsp
{
	YReqCode		mReqCode;
	YReqId			mReqId;
	YRspCode		mRspCode;
	YErrorText		mErrorText;
};
