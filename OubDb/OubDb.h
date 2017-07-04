#ifndef __OUBDB_H__
#define __OUBDB_H__

#include <string>
#include <mysql.h>

#define			kDbHost			"localhost"
#define			kDbUser			"jeff"
#define			kDbPassword		"jrfftypaep"
#define			kDbName 		"oubdb"

namespace oub {
	//
	//	static class that initialises the mysql library
	//
	class COubDbInitializer
	{

	public:
		COubDbInitializer();
		~COubDbInitializer();

	};

	//
	//	instantiate one of these per thread that uses the database
	//
	class COubDbConnection
	{

	public:
		COubDbConnection();
		~COubDbConnection();

		void InitOubDbConnection();
		std::string GetPasswordForUser(const std::string& sUser, bool& rbNotFound);

	private:
		MYSQL*						mCon;
		static COubDbInitializer	mgOubDbInitializer;
	};
}

#endif
