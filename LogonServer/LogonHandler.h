#pragma once
/////////////////////////////////////////////////////////////////////
//
// (C) 2016 by Jeffery A Esposito
//
/////////////////////////////////////////////////////////////////////

#include "..\OubLib\tcp.h"
#include "msg.h"

class CLogonHandler : public CHandler
{
public:
	CLogonHandler();	// TODO ...
	~CLogonHandler();	// TODO ...

	virtual void onReqReceived(const CReq& rReq);	// TODO ...
};

