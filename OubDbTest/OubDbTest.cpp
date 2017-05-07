// OubDbTest.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include "..\Jlib\misc.h"
#include "..\OubDb\OubDb.h"

int main()
{
	COubDb			vDb;
	std::string		sPassword;
	try {
		vDb.InitOubDb();

		sPassword = vDb.GetPasswordForUser("jeff");
		std::cout << "jeff " << sPassword << std::endl;

		sPassword = vDb.GetPasswordForUser("eff");
		std::cout << "eff " << sPassword << std::endl;
	}
	catch (jlib::CErrorInfo e)
	{
		std::cout << e.GetText() << std::endl;
	}
	return 0;
}

