#include "stdafx.h"
#include "LogonHandler.h"

//
//	virtual override.  Called when the handler receives a request.
//
void oub::CLogonHandler::DoProcessReq(const jlib::CReq& rReq, const jlib::CRsp& rRsp )
{
	if ( rReq.mReqCode == oub::kReqCodeLogon )
	{
		ProcessLogonReq( (const CLogonReq&)(rReq), (CLogonRsp&)(rRsp));
	}
}

//
//	Called upon the receipt of a logon request
//
void oub::CLogonHandler::ProcessLogonReq(const CLogonReq& rLogonReq, CLogonRsp& rLogonRsp)
{
	rLogonRsp.mReqCode = rLogonReq.mReqCode;
	rLogonRsp.mReqSeq = rLogonReq.mReqSeq;
	rLogonRsp.mMsgLen = sizeof(rLogonRsp);
	rLogonRsp.mRspCode = 0;
	memset(rLogonRsp.mErrorText, 0, sizeof(rLogonRsp.mErrorText));
}
