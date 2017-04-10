#include <qmessagebox.h>
#include <qdebug.h>
#include "LogonWorker.h"
#include "ClientSocket.h"


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
	oub::CLogonRsp		rsp;

	qDebug() << "ClientSocket: Logging on";
	mqClientSocket 
		= ClientSocket::Yq( new ClientSocket(LOGONSVR_IP, LOGONSVR_PORT ) );
	try
	{
		mqClientSocket->Connect();
		mqClientSocket->WriteRead(rReq, rsp);
	}
	catch ( jlib::CErrorInfo& e )
	{
		qDebug() << "ClientSocket: " << QString::fromStdString( e.GetText() );
		emit logonError("Unable to writeread request to logon server: " 
			+ QString::fromStdString(e.GetText()) );
		return;
	}
	emit logonFinished(rsp);
}

