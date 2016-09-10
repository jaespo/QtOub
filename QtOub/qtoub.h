#ifndef QTOUB_H
#define QTOUB_H

#include <QtWidgets/QMainWindow>
#include <QThread.h>

#include "ui_qtoub.h"
#include "LogonWorker.h"

class QtOub : public QMainWindow
{
	Q_OBJECT

private slots:
	void onPushButton_logon_clicked();
	void onLogonFinished(const CLogonRsp&); 
	void onLogonError(const QString&);

signals:
	void startLogon(const CLogonReq& rReq);

public:
	QtOub(QWidget *parent = 0);
	~QtOub();

private:
	Ui::QtOubClass	ui;
	QThread*		mpLogonThread;
	LogonWorker*	mpLogonWorker;
};

#endif // QTOUB_H
