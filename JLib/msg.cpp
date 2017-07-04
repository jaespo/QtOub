#include <sstream>
#include <algorithm>
#include <cstring>
#include "msg.h"

//
//	Statics
//
jlib::YReqSeq jlib::CReq::mgCurReqSeq;

//
//	Get a message from an archive
//
void jlib::CMsg::FromArchive(CArchive& rArchive)
{
	rArchive.GetNum(mMsgLen);
}

//
//	Get a message from an archive
//
void jlib::CMsg::ToArchive(CArchive& rArchive)
{
	rArchive.PutNum(mMsgLen);
}

//
//	Creates a request with the specified request code
//
jlib::CReq::Yq jlib::CMsgFactory::CreateReq(YReqCode vReqCode)
{
	YReqCreatorMap::iterator vIter = mReqCreatorMap.find(vReqCode);
	if (vIter == mReqCreatorMap.end())
	{
		THROW_ERR(9999,
			<< "No request creator in factory for request code "
			<< vReqCode);
	}
	else
	{
		return vIter->second->CreateReq();
	}
}

//
//	Creates a response with the specified request and response codes
//
jlib::CRsp::Yq jlib::CMsgFactory::CreateRsp(YReqCode vReqCode, YRspCode vRspCode)
{
	YRspCreatorMap::iterator vIter
		= mRspCreatorMap.find(std::make_pair(vReqCode, vRspCode));
	if (vIter == mRspCreatorMap.end())
	{
		THROW_ERR(9999,
			<< "No response creator in factory for codes "
			<< vReqCode
			<< ", " 
			<< vRspCode
		);
	}
	else
	{
		return vIter->second->CreateRsp();
	}
}

//
//	Registers a request creator in the message factory
//
void jlib::CMsgFactory::RegisterReqCreator(
	CReqCreator::Yq			qReqCreator,
	YReqCode				vReqCode
)
{
	mReqCreatorMap[vReqCode] = qReqCreator;
}

//
//	Registers a response creator in the message factory
//
void jlib::CMsgFactory::RegisterRspCreator(
	CRspCreator::Yq			qRspCreator,
	YReqCode				vReqCode,
	YReqCode				vRspCode
)
{
	mRspCreatorMap[std::make_pair( vReqCode, vRspCode )] = qRspCreator;
}


//
//	gets a request from an archive
//
void jlib::CReq::FromArchive(CArchive& rArchive)
{
	jlib::CMsg::FromArchive(rArchive);
	rArchive.GetNum(mReqCode);
	rArchive.GetNum(mReqSeq);
}

//
//	Saves a request to an archive
//
void jlib::CReq::ToArchive(CArchive& rArchive)
{
	jlib::CMsg::ToArchive(rArchive);
	rArchive.PutNum(mReqCode);
	rArchive.PutNum(mReqSeq);
}

//
//	Returns a string that traces a request
//
std::string jlib::CReq::TraceStr() const
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
//	gets a response from an archive
//
void jlib::CRsp::FromArchive(CArchive& rArchive)
{
	jlib::CMsg::FromArchive(rArchive);
	rArchive.GetNum(mReqCode);
	rArchive.GetNum(mReqSeq);
	rArchive.GetNum(mRspCode);
	rArchive.GetChars(mErrorText, sizeof( mErrorText ));
}

//
//	Saves a response to an archive
//
void jlib::CRsp::ToArchive(CArchive& rArchive)
{
	jlib::CMsg::ToArchive(rArchive);
	rArchive.PutNum(mReqCode);
	rArchive.PutNum(mReqSeq);
	rArchive.GetNum(mRspCode);
	rArchive.GetChars(mErrorText, sizeof(mErrorText));
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
std::string jlib::CRsp::TraceStr() const
{
	std::stringstream ss;
	ss << "ReqCode:        " << mReqCode << "\n";
	ss << "ReqSeq:         " << mReqSeq << "\n";
	ss << "RspCode:        " << mRspCode << "\n";
	ss << "ErrorText:      " << mErrorText << "\n";
	return ss.str();
}


