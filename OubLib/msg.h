#pragma once
#include <string>
#include "misc.h"

//
//	the base message class
//
class CMsg
{

public:
	virtual ~CMsg() {}

	__int16			mMsgLen;
};

//
//	the base request class
//
class CReq: public CMsg
{

public: 
	CReq() {}
	virtual ~CReq() {}

	YReqCode		mReqCode;
	YReqId			mReqId;

	static YReqId GetNextReqId() { return mgCurReqId++; }

private:
	static YReqId	mgCurReqId;
};

//
//	the base response class
//
class CRsp : public CMsg
{
	YReqCode		mReqCode;
	YReqId			mReqId;
	YRspCode		mRspCode;
	YErrorText		mErrorText;
};




