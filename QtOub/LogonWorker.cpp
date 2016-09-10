#include "LogonWorker.h"

//
//	ctor for the logon worker
//
LogonWorker::LogonWorker( QObject* parent ) :
	QObject( parent )
{
}

//
//	dtor for the logon worker
//
LogonWorker::~LogonWorker()
{
}

//
// Start processing data.
//
void LogonWorker::process() 
{
	// TODO put socket stuff here
	qDebug("LogonWorker processing");
	emit finished();
}
