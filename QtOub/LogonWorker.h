#pragma once

#include <memory>

#include <QObject.h>
#include <QtNetwork\QTcpSocket>
#include "..\LogonServer\msg.h"

//
//	Object that is run in a thread to send a logon request and process
//	its response.
//
class LogonWorker : public QObject
{
	Q_OBJECT

public:
	LogonWorker();
	~LogonWorker();

	private slots:
	void onStartLogon(const oub::CLogonReq& rReq);

signals:
	void logonFinished(const oub::CLogonRsp& rRsp);
	void logonError(const QString& rErrorText);

private:
	std::shared_ptr<QTcpSocket>	mqSocket;
	bool						mbLogonPending;
};

