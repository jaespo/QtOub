#include <sstream>
#include "oubmsg.h"

//
//	Returns a string that traces the logon request
//
std::string oub::CLogonReq::TraceStr() const
{
	std::stringstream ss;
	ss << "LogonReq" << "\n";
	ss << CReq::TraceStr();
	ss << "mUserId:        " << mUserId << "\n";
	ss << "mPassword:      " << mPassword << "\n";
	return ss.str();
}

//
//	Returns a string that traces the logon response
//
std::string oub::CLogonRsp::TraceStr() const
{
	std::stringstream ss;
	ss << "LogonRsp" << "\n";
	switch (this->mRspCode)
	{
	case kRcOk: 
		ss << "kRcRspOk" << "\n";
		break;
	case kRcDbError:
		ss << "kRcDbError" << "\n";
		break;
	case kRcUserNotFound:
		ss << "kRcUserNotFound" << "\n";
		break;
	case kRcBadPassword:
		ss << "kRcBadPassword" << "\n";
		break;
	}
	ss << CRsp::TraceStr();
	return ss.str();
}
