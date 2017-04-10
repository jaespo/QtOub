#pragma once
#include <string>

class COubDb
{
public:
	COubDb();
	~COubDb();

	std::string GetPasswordForUser(const std::string&);
};

