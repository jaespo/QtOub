#include <qmessagebox.h>
#include <qdebug.h>
#include "LogonWorker.h"

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
	qDebug() << "Logging on";
	emit logonFinished(rsp);
}

