#include "qtoub.h"
#include <qmessagebox.h>
#include "..\LogonServer\Msg.h"

QtOub::QtOub(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//
	//	Set up the logon worker thread
	//
	mpLogonThread = new QThread( this );
	mpLogonWorker = new LogonWorker( this );
	mpLogonWorker->moveToThread( mpLogonThread );
	connect(mpLogonWorker, SIGNAL(error(QString)), 
			 this, SLOT(errorString(QString)));
	connect(mpLogonThread, SIGNAL(started()), 
			mpLogonWorker, SLOT(process()));
	connect(mpLogonWorker, SIGNAL(finished()), 
			mpLogonThread, SLOT(quit()));
	connect(mpLogonWorker, SIGNAL(finished()), 
			mpLogonWorker, SLOT(deleteLater()));
	connect(mpLogonThread, SIGNAL(finished()), 
			mpLogonThread, SLOT(deleteLater()));
}

QtOub::~QtOub()
{
    
}

//
//	Called when the logon button is clicked
//
void QtOub::on_pushButton_logon_clicked()
{
	QString user = ui.lineEdit_user->text();
	QString password = ui.lineEdit_password->text();

	//
	//	Verify that a user name was given
	//
	if (user == "")
	{
		QMessageBox::critical(this, "Missing user name",
			"Please specify a user name");
		return;
	}

	//
	//	Verify that a password was given
	//
	if ( password == "")
	{
		QMessageBox::critical(this, "Missing password",
			"Please specify a password");
		return;
	}

	//
	//	Format a logon request
	//
	CLogonReq		req;
	CLogonRsp		rsp;
	req.mReqCode = ELogonServerReqCode::kLogon;
	req.mReqId = CReq::GetNextReqId();
	FILLFIELD(req.mUserId, user.toStdString());
	FILLFIELD(req.mPassword, password.toStdString());
	qDebug("Startomg Logon thread");
	mpLogonThread->start();

	//
	//	slot logonFinished will be invoked upon completion
	//
}
