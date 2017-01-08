//
//	(C) 2016 by Jeffery A Esposito
//
#pragma once
#include <string>
#include "misc.h"

#define LOGONSVR_IP					"localhost"
#define LOGONSVR_PORT				"27016"
#define LOGONSVR_CONNECT_TIMEOUT	10000

namespace oub 
{
	//
	//	the base message class
	//
	class CMsg
	{

	public:
		virtual ~CMsg() {}

		//
		//	Inclusive
		//
		__int16			mMsgLen;
	};

	//
	//	the base request class
	//
	class CReq : public CMsg
	{

	public:
		CReq() {}
		virtual ~CReq() {}

		oub::YReqCode		mReqCode;
		oub::YReqId			mReqId;

		static YReqId GetNextReqId() { return mgCurReqId++; }

	private:
		static YReqId		mgCurReqId;
	};

	//
	//	the base response class
	//
	class CRsp : public CMsg
	{
	public:
		YReqCode			mReqCode;
		YReqId				mReqId;
		YRspCode			mRspCode;
		YErrorText			mErrorText;
	};

}; // namespace oub

