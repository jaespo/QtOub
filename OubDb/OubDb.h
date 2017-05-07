#pragma once
#include <string>
#include <my_global.h>
#include <mysql.h>

#define			kDbHost			"localhost"
#define			kDbUser			"jeff"
#define			kDbPassword		"jrfftypaep"
#define			kDbName 		"oubdb"
	
class COubDb
{
 
public:
	COubDb();
	~COubDb();

	void InitOubDb();	
	std::string GetPasswordForUser(const std::string& sUser);

private:
	MYSQL*		mCon;
};

