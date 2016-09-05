#pragma once
#include "oubtypes.h"

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


