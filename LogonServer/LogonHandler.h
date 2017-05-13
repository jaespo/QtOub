#pragma once
/////////////////////////////////////////////////////////////////////
//
// (C) 2016 by Jeffery A Esposito
//
/////////////////////////////////////////////////////////////////////
#include "..\JLib\tcp.h"
#include "..\OubLib\oubmsg.h"
#include "..\OubDb\oubdb.h"

namespace oub 
{
	class CLogonHandler : public jlib::CHandler
	{
	public:
		CLogonHandler() {}
		~CLogonHandler() {}

		virtual void DoProcessReq(const jlib::CReq& rReq, const jlib::CRsp& rRsp );
		void ProcessLogonReq(const CLogonReq& rLogonReq, CLogonRsp& rLogonRsp);

	private:
		COubDbConnection			mOubDbCon;
	};
};	// namespace oub

