#include <stdio.h>
#include "..\JLib\misc.h"
#include "OubDb.h"

//
//	Statics
//
oub::COubDbInitializer oub::COubDbConnection::mgOubDbInitializer;

oub::COubDbConnection::COubDbConnection()
{
}


oub::COubDbConnection::~COubDbConnection()
{
	mysql_thread_end();
}

//
//	Opens the database connection and throws an error on failure
//
void oub::COubDbConnection::InitOubDbConnection()
{
	mCon = mysql_init(NULL);
	if (mCon == NULL)
	{
		THROW_ERR(9999, << "init of DB failed: ");
	}

	if (mysql_real_connect(
		mCon, kDbHost, kDbUser, kDbPassword, kDbName, 0, NULL, 0) == NULL)
	{
		const char* sErrTxt = mysql_error(mCon);
		int vErrNo = mysql_errno(mCon);
		mysql_close(mCon);
		mCon = NULL;
		THROW_ERR(9999,
			<< "mysql_real_connect failed: "
			<< sErrTxt
			<< ", errno "
			<< vErrNo
		);
	}
}

//
//	returns the password for a user id
//
std::string oub::COubDbConnection::GetPasswordForUser(
	const std::string&	sUser, 
	bool&				rbNotFound)
{
	//
	//	Query the db
	//
	std::string sQuery = "SELECT password FROM user where name = '";
	sQuery.append(sUser);
	sQuery.append("'");
	if (mysql_query(mCon, sQuery.c_str() ) )
	{
		const char* sErrTxt = mysql_error(mCon);
		int vErrNo = mysql_errno(mCon);
		THROW_ERR(9999,
			<< "mysql_query select of user " 
			<< kDbUser
			<< " failed: "
			<< sErrTxt
			<< ", errno "
			<< vErrNo
		);
	}

	MYSQL_RES *result = mysql_store_result(mCon);
	if (result == NULL)
	{
		const char* sErrTxt = mysql_error(mCon);
		int vErrNo = mysql_errno(mCon);
	}
	int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	if (row == NULL )
	{
		mysql_free_result(result);
		rbNotFound = true;
		return "";
	};

	std::string sPwd = row[0];
	mysql_free_result(result);
	rbNotFound = false;
	return sPwd;
}

//
//	initialzes the mysql library
//
oub::COubDbInitializer::COubDbInitializer()
{
	mysql_library_init(0, NULL, NULL);
}

//
//	deinitizes the mysql library
//
oub::COubDbInitializer::~COubDbInitializer()
{
	mysql_library_end();
}
