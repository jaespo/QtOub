#include <qmessagebox.h>
#include <qdebug.h>
#include "LogonWorker.h"
#include <QtNetwork\QTcpSocket>


//
//	ctor for the logon worker
//
LogonWorker::LogonWorker()
{
	mbLogonPending = false;
}

//
//	dtor for the logon worker
//
LogonWorker::~LogonWorker()
{
}

//
//	starts the logon processing
//
void LogonWorker::onStartLogon(const oub::CLogonReq & rReq)
{
	oub::CLogonRsp		rsp;  // todo code talking to server
	qDebug() << "Logging on";
	mqSocket = std::shared_ptr<QTcpSocket>( new QTcpSocket(this) );
	mqSocket->connectToHost( LOGONSVR_IP, QString( LOGONSVR_PORT ).toInt() );
	mqSocket->waitForConnected(LOGONSVR_CONNECT_TIMEOUT);
	emit logonFinished(rsp);
}

