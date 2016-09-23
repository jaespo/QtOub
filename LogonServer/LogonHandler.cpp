#include "stdafx.h"
#include "msg.h"
#include "LogonHandler.h"

//
//	virtual override.  Called when the handler receives a request.
//
void oub::CLogonHandler::DoProcessReq(const CReq& rReq)
{
	if (dynamic_cast<const CLogonReq*>(&rReq) != NULL)
	{
		ProcessLogonReq(dynamic_cast<const CLogonReq&>(rReq));
	}
}

//
//	Called upon the receipt of a logon request
//
void oub::CLogonHandler::ProcessLogonReq(const CLogonReq& rLogonReq)
{
	CLogonRsp		vLogonRsp;

	vLogonRsp.mReqCode = rLogonReq.mReqCode;
	vLogonRsp.mReqId = rLogonReq.mReqId;
	vLogonRsp.mRspCode = 0;
	memset(vLogonRsp.mErrorText, 0, sizeof(vLogonRsp.mErrorText));
	GetSocket()->Reply(vLogonRsp);
}
