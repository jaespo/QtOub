//
//	(C) 2016 by Jeffery A Esposito
//
#pragma once
#include <string>
#include "misc.h"

namespace jlib
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

		YReqCode			mReqCode;
		YReqSeq				mReqSeq;

		static YReqSeq GetNextReqSeq() { return mgCurReqSeq++; }
		virtual std::string traceStr() const;

	private:
		static YReqSeq		mgCurReqSeq;
	};

	//
	//	the base response class
	//
	class CRsp : public CMsg
	{
	public:
		CRsp();
		void SetErrorText(const std::string& rTxt);
		void InitFromReq(const CReq& rReq);

		YReqCode			mReqCode;
		YReqSeq				mReqSeq;
		YRspCode			mRspCode;
		YErrorText			mErrorText;

		virtual std::string traceStr() const;
	};

}; // namespace oub

