#pragma once
#include <qstring.h>
#include "..\LogonServer\Msg.h"

class ClientSocket
{
public:
	ClientSocket( const QString& ipaddr, const QString& port ); // todo
	~ClientSocket(); // todo

	void Connect(); // todo
	void WriteRead(const oub::CReq& req, oub::CRsp& rsp); // todo 
	// todo move logon code here
};

