#pragma once
//
//	(C) 2016 by Jeffery A Esposito
//
#include <memory>
#include <qstring.h>
#include <QtNetwork\QTcpSocket>
#include "..\LogonServer\Msg.h"

class ClientSocket
{
public:
	typedef std::shared_ptr<ClientSocket>	Yq;
	ClientSocket( const QString& ipaddr, const QString& port );
	~ClientSocket();

	void Connect();
	bool WriteRead(const oub::CReq& req, oub::CRsp& rsp);

private:
	int								kWriteTimeout = 2000;	// 2 seconds
	int								kReadTimeout = 30000;	// 30 seconds
	QString							mIpAddr;
	int								mPort;
	std::shared_ptr<QTcpSocket>		mqSocket;
};

 