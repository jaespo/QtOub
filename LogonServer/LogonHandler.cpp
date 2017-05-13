#include "..\JLib\misc.h"
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
	bool			bNotFound;
	std::string		sPwd;

	rLogonRsp.InitFromReq(rLogonReq);
	rLogonRsp.mReqCode = rLogonReq.mReqCode;
	rLogonRsp.mReqSeq = rLogonReq.mReqSeq;
	rLogonRsp.mMsgLen = sizeof(rLogonRsp);
	memset(rLogonRsp.mErrorText, 0, sizeof(rLogonRsp.mErrorText));

	try
	{
		sPwd = mOubDbCon.GetPasswordForUser(rLogonReq.mUserId, bNotFound);
	}
	catch (jlib::CErrorInfo ei)
	{
		rLogonRsp.mRspCode = CLogonRsp::kRcDbError;
		rLogonRsp.SetErrorText(ei.GetText());
		return;
	}

	if (bNotFound)
	{
		rLogonRsp.mRspCode = CLogonRsp::kRcUserNotFound;
		rLogonRsp.SetErrorText("User not found");
		return;
	}
	rLogonRsp.mRspCode = CLogonRsp::kRcOk;
}
