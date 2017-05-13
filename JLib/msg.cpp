#include <sstream>
#include <algorithm>
#include <cstring>
#include "msg.h"

//
//	Statics
//
jlib::YReqSeq jlib::CReq::mgCurReqSeq;

//
//	Returns a string that traces a request
//
std::string jlib::CReq::traceStr() const
{
	std::stringstream ss;
	ss << "ReqCode:        " << mReqCode << "\n";
	ss << "ReqSeq:         " << mReqSeq << "\n";
	return ss.str();
}

// 
//  ctor for a CRsp
//
jlib::CRsp::CRsp()
{
	memset(mErrorText, 0, sizeof(mErrorText));
}

//
//	Sets the error text, truncating it to the max size of the
//	field.
//
void jlib::CRsp::SetErrorText(const std::string& rTxt)
{
	size_t vLen = std::max(rTxt.length(), sizeof(mErrorText)) - 1;
	memcpy(mErrorText, rTxt.c_str(), vLen );
	memset(&mErrorText[vLen], 0, sizeof(mErrorText) - vLen );
}

//
//	Initizes a response from its request
//
void jlib::CRsp::InitFromReq(const CReq& rReq)
{
	mReqCode = rReq.mReqCode;
	mReqSeq = rReq.mReqSeq;
	mMsgLen = sizeof(*this);
	memset(mErrorText, 0, sizeof(mErrorText));
}

//
//	Returns a string that traces a response
//
std::string jlib::CRsp::traceStr() const
{
	std::stringstream ss;
	ss << "ReqCode:        " << mReqCode << "\n";
	ss << "ReqSeq:         " << mReqSeq << "\n";
	ss << "RspCode:        " << mRspCode << "\n";
	ss << "ErrorText:      " << mErrorText << "\n";
	return ss.str();
}


