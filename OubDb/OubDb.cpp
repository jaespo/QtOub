#undef UNICODE
#include <stdio.h>
#include <my_global.h>
#include <mysql.h>

#include "OubDb.h"


COubDb::COubDb()
{
}


COubDb::~COubDb()
{
}

//
//	Opens the database and throws an error on failure
//
void COubDb::InitOubDb()
{
	mCon = mysql_init(NULL);
	if (mCon == NULL)
	{
		THROW_ERR(9999,	<< "init of DB failed: "
	}

	if (mysql_real_connect( 
		mCon, kDbHost, kDbUser, kDbPassword, kDbName, 0, NULL, 0) == NULL)
	{
		const char* sErrTxt = mysql_error(mCon);
		int vErrNo = mysql_errno(mCon);
		mysql_close(mCon);
		mCon = NULL;
		THROW_ERR(9999,
			<< "Connect to DB failed: "
			<< sErrText
			<< ", errno "
			<< vErrNo
		);
	}
}

//
//	returns the password for a user id
//
std::string GetPasswordForUser(const std::string& sUser)
{
	//
	//	Query the db
	//
	if (mysql_query(mCon, "SELECT password FROM user where name = " + sUser ) )
	{
		const char* sErrTxt = mysql_error(mCon);
		int vErrNo = mysql_errno(mCon);
		THROW_ERR(9999,
			<< "Select of user " 
			<< sUser
			< " failed: "
			<< sErrText
			<< ", errno "
			<< vErrNo
		);
	}

	MYSQL_RES *result = mysql_store_result(cCon);
	if (result == NULL)
	{
		const char* sErrTxt = mysql_error(mCon);
		int vErrNo = mysql_errno(mCon);
	}
	int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	if (row == null)
	{
		THROW_ERR(9999, << "No such user";
	};

	std::string sPwd = row[0];
	mysql_free_result(result);
	return sPwd;
}
 