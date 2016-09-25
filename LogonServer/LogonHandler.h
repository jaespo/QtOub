#pragma once
/////////////////////////////////////////////////////////////////////
//
// (C) 2016 by Jeffery A Esposito
//
/////////////////////////////////////////////////////////////////////

#include "..\OubLib\tcp.h"
#include "msg.h"

namespace oub {
	class CLogonHandler : public CHandler
	{
	public:
		CLogonHandler() {}
		~CLogonHandler() {}

		virtual void DoProcessReq(const CReq& rReq, const CRsp& rRsp );
		void ProcessLogonReq(const CLogonReq& rLogonReq, CLogonRsp& rLogonRsp);
	};
};	// namespace oub

