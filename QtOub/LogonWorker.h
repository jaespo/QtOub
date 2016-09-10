#pragma once

#include <QObject.h>

//
//	Object that is run in a thread to send a logon request and process
//	its response.
//
class LogonWorker : public QObject
{
	Q_OBJECT

public:
	LogonWorker( QObject *parent );
	~LogonWorker();

public slots:
	void process();

signals:
	void error(QString errorText);
	void finished();

private:

};

