//
//	(C) 2016 by Jeffery A Esposito
//


#include <qstring.h>
#include "..\OubLib\oubmisc.h"
#include "..\OubLib\oubmsg.h"
#include "ClientSocket.h"

//
// ctor
//
ClientSocket::ClientSocket(const QString& ipaddr, const QString& port)
{
	mIpAddr = ipaddr;
	mPort = port.toInt();
}

//
//	dtor
//
ClientSocket::~ClientSocket()
{
}

//
//	connect the socket
//
void ClientSocket::Connect()
{
	mqSocket = std::shared_ptr<QTcpSocket>(new QTcpSocket);
	mqSocket->connectToHost( mIpAddr, mPort );
	if (!mqSocket->waitForConnected(LOGONSVR_CONNECT_TIMEOUT))
	{
		THROW_ERR( 9999, 
			<< mIpAddr.toStdString() 
			<< ":" 
			<< mPort 
			<< "Unable to connect, error " 
			<< mqSocket->error()
			<< ": "
			<< mqSocket->errorString().toStdString() );
	}
	bool connected = (mqSocket->state() == QTcpSocket::ConnectedState);
}

//
//	writes a request to the socket and reads the server's reply
//
bool ClientSocket::WriteRead(const jlib::CReq& req, jlib ::CRsp& rsp)
{
	bool connected = (mqSocket->state() == QTcpSocket::ConnectedState);
	bool gotCount = false;
	qint64 bufoff = 0;

	if (!connected)
	{
		THROW_ERR(9999,
			<< mIpAddr.toStdString()
			<< ":"
			<< mPort
			<< " is not connected");
	}
	mqSocket->write((const char *)&req, req.mMsgLen);
	while( mqSocket->bytesToWrite() > 0 )
	{
		if ( !mqSocket->waitForBytesWritten(2000) );
		{
			THROW_ERR(9999,
				<< mIpAddr.toStdString()
				<< ":"
				<< mPort
				<< " write failed with error "
				<< mqSocket->error()
				<< ": "
				<< mqSocket->errorString().toStdString());
		}
	}
	qDebug() << "Wrote request: \n" ;
	std::string strReq = req.TraceStr();
	qDebug() << QString::fromStdString(strReq);
	while (mqSocket->waitForReadyRead(kReadTimeout))
	{
		qint64 countRead = mqSocket->read(((char *)&rsp)+bufoff, sizeof(rsp));
		bufoff += countRead;
		bool hasEnufDataQueued = bufoff >= sizeof(rsp.mMsgLen)
			&& bufoff >= rsp.mMsgLen;
		if (bufoff > rsp.mMsgLen)
		{
			THROW_ERR(9999,
			<< mIpAddr.toStdString()
			<< ":"
				<< mPort
				<< " rsp too big, was "
				<< bufoff
				<< " s/b "
				<< rsp.mMsgLen);
		}
		return true;
	}
	THROW_ERR(9999,
		<< mIpAddr.toStdString()
		<< ":"
		<< mPort
		<< " read failed with error "
		<< mqSocket->error()
		<< ": "
		<< mqSocket->errorString().toStdString());
	return false;
}


