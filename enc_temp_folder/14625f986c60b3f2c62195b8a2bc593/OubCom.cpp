//
// OubCom.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

//
//	Reads a command line and returns a vector of tokens
//
void ReadCmd(std::vector<std::string>& rTokVect)
{
	std::string		sCmdLine;
	char*			pzArg;
	char*			pzNextTok = NULL;

	std::cout << "OubCom> ";
	std::getline(std::cin, sCmdLine);
	pzArg = strtok_s((char*)sCmdLine.c_str(), " ", &pzNextTok);
	while (pzArg != NULL)
	{
		rTokVect.push_back(pzArg);
		pzArg = strtok_s(NULL, " ", &pzNextTok);
	}
}

//
//	Executes the help command
//
void ExecCmdHelp()
{
	std::cout << "h, help		display a list of commands" << std::endl;
	std::cout << "q, quit		exit OubCom" << std::endl;
}

//
//	Executes a command
//
void ExecCmd(const std::vector<std::string>& rTokVect)
{
	if (rTokVect.empty())
		return;
	else if (rTokVect[0] == "quit" || rTokVect[0] == "q")
		exit(EXIT_SUCCESS);
	else if (rTokVect[0] == "help" || rTokVect[0] == "h")
		ExecCmdHelp();
	else
		std::cout << "Unknown command: " << rTokVect[0];
}

//
//	Main 
//
int main()
{
	std::vector<std::string>		vTokVect;

	std::cout << "OubCom ~ Oub Command Line Interpreter" << std::endl;
	std::cout << "(C) 2017 by Jeffery A Esposito" << std::endl;

	while (true)
	{
		ReadCmd(vTokVect);
		ExecCmd(vTokVect);
	}
	return 0;
}

