#include <sstream>
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
