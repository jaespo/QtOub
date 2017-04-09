#include <sstream>
#include "oubmsg.h"

//
//	Returns a string that traces the logon request
//
std::string oub::CLogonReq::traceStr() const
{
	std::stringstream ss;
	ss << "LogonReq" << "\n";
	ss << CReq::traceStr();
	ss << "mUserId:        " << mUserId << "\n";
	ss << "mPassword:      " << mPassword << "\n";
	return ss.str();
}

//
//	Returns a string that traces the logon response
//
std::string oub::CLogonRsp::traceStr() const
{
	std::stringstream ss;
	ss << "LogonRsp" << "\n";
	ss << CRsp::traceStr();
	return ss.str();
}
