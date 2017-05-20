#pragma once
#include <vector>
#include "..\JLib\tcp.h"
#include "..\OubLib\oubmsg.h"

namespace oub
{
	class CCmdProcessor
	{
	public:
		void Run();

	private:
		void ReadCmd(std::vector<std::string>& rTokVect);
		void ExecCmd(const std::vector<std::string>& rTokVect);
	};

	class CLogonSvrConnection
	{
	public:
		static jlib::CClientSocket& GetClientSocket() { return mClientSocket;  }

	private:
		static jlib::CClientSocket		mClientSocket;
	};

	class CCmdConnect
	{
	public:
		static void Exec();
	};

	class CCmdHelp
	{
	public:
		static void Exec();
	};

	class CCmdQuit
	{
	public:
		static void Exec();
	};
}
