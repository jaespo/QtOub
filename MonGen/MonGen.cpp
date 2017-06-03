#include <iostream>
#include <string>
#include "..\Jlib\misc.h"
#include "..\OubDb\OubDb.h"

int main()
{
	oub::COubDbConnection	vDb;
	std::string				sPassword;
	bool					bNotFound;
	try {
		vDb.InitOubDbConnection();

		sPassword = vDb.GetPasswordForUser("jeff", bNotFound);
		std::cout << "jeff " << sPassword << ", bNotFound=" << bNotFound << std::endl;
		sPassword = vDb.GetPasswordForUser("eff", bNotFound);
		std::cout << "eff " << sPassword << ", bNotFound=" << bNotFound << std::endl;
	}
	catch (jlib::CErrorInfo e)
	{
		std::cout << e.GetText() << std::endl;
	}
	return 0;
}


