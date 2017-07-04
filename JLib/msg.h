#ifndef __MSG_H__
#define __MSG_H__

//
//	(C) 2016 by Jeffery A Esposito
//
#include <memory>
#include <string>
#include <map>
#include "misc.h"
#include "serialize.h"

namespace jlib
{
	//
	//	the base message class
	//
	class CMsg
	{

	public:
		typedef std::shared_ptr<CMsg>	Yq;
		
		virtual ~CMsg() {}

		//
		//	Inclusive
		//
		int16_t			mMsgLen;

		virtual void ToArchive( CArchive& rArchive );
		virtual void FromArchive( CArchive& rArchive );
	};

	//
	//	the base request class
	//
	class CReq : public CMsg
	{
	public:
		typedef std::shared_ptr<CReq>	Yq;
		
		CReq() {}
		virtual ~CReq() {}

		YReqCode			mReqCode;
		YReqSeq				mReqSeq;

		static YReqSeq GetNextReqSeq() { return mgCurReqSeq++; }
		virtual std::string TraceStr() const;
	
		virtual void ToArchive( CArchive& rArchive );
		virtual void FromArchive( CArchive& rArchive );

	private:
		static YReqSeq		mgCurReqSeq;
	};

	//
	//	the base response class
	//
	class CRsp : public CMsg
	{
	public:
		typedef std::shared_ptr<CRsp>	Yq;

		CRsp();
		void SetErrorText(const std::string& rTxt);
		void InitFromReq(const CReq& rReq);

		YReqCode			mReqCode;
		YReqSeq				mReqSeq;
		YRspCode			mRspCode;
		YErrorText			mErrorText;

		virtual void ToArchive( CArchive& rArchive );
		virtual void FromArchive( CArchive& rArchive );

		virtual std::string TraceStr() const;
	};

	class CReqCreator
	{
	public:
		typedef std::shared_ptr<CReqCreator>		Yq;
		virtual CReq::Yq CreateReq() = 0;
	};

	class CRspCreator
	{
	public:
		typedef std::shared_ptr<CRspCreator>		Yq;
		virtual CRsp::Yq CreateRsp() = 0;
	};

	class CMsgFactory
	{
	public:
		typedef std::map<YReqCode, CReqCreator::Yq>							
			YReqCreatorMap;
		typedef std::map<std::pair<YReqCode, YRspCode>, CRspCreator::Yq>	
			YRspCreatorMap;

		void RegisterReqCreator(
			CReqCreator::Yq			qReqCreator, 
			YReqCode				vReqCode 
		);
		void RegisterRspCreator(
			CRspCreator::Yq			qRspCreator, 
			YReqCode				vReqCode, 
			YReqCode				vRspCode
		);
		CReq::Yq CreateReq(YReqCode vReqCode);
		CRsp::Yq CreateRsp(YReqCode vReqCode, YRspCode vRspCode);

	private:
		YReqCreatorMap				mReqCreatorMap;
		YRspCreatorMap				mRspCreatorMap;
	};

}; // namespace jlib

#endif


