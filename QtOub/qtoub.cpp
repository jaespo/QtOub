#include "qtoub.h"
#include <qmessagebox.h>
#include "..\LogonServer\Msg.h"

//
//	slot called when a logon completes
//
void QtOub::onLogonFinished(const oub::CLogonRsp &)
{
	QMessageBox(QMessageBox::Icon::Information, "Logged on", "Logged on");
	ui.pushButton_logon->setEnabled(true);
}

//
//	slot called when there was a communications error on the logon server
//
void QtOub::onLogonError(const QString& errorText )
{
	QMessageBox(QMessageBox::Icon::Critical, "Logon Error", errorText);
	ui.pushButton_logon->setEnabled(true);
}

QtOub::QtOub(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//
	//	Set up the logon worker thread
	//
	qRegisterMetaType<oub::CLogonReq>("oub::CLogonReq");
	qRegisterMetaType<oub::CLogonRsp>("oub::CLogonRsp");
	mpLogonThread = new QThread(this);
	mpLogonWorker = new LogonWorker;
	mpLogonWorker->moveToThread(mpLogonThread);
	connect(mpLogonWorker, SIGNAL(logonFinished(const oub::CLogonRsp&)),
		this, SLOT(onLogonFinished(const oub::CLogonRsp&)));
	connect(mpLogonWorker, SIGNAL(logonError(const QString&)),
		this, SLOT(onLogonError(const QString&)));
	connect(this, SIGNAL(startLogon(const oub::CLogonReq&)),
		mpLogonWorker, SLOT(onStartLogon(const oub::CLogonReq&)));
}

QtOub::~QtOub()
{
    
}

//
//	Called when the logon button is clicked
//
void QtOub::onPushButton_logon_clicked()
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
	oub::CLogonReq		req;
	oub::CLogonRsp		rsp;
	req.mReqCode = oub::ELogonServerReqCode::kReqCodeLogon;
	req.mReqId = oub::CReq::GetNextReqId();
	FILLFIELD(req.mUserId, user.toStdString());
	FILLFIELD(req.mPassword, password.toStdString());
	if ( !mpLogonThread->isRunning() )
		mpLogonThread->start();
	ui.pushButton_logon->setEnabled(false);
	emit startLogon(req);
	
	//
	//	slot logonFinished or logonError will be invoked upon completion
	//
}
