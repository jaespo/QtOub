#ifndef __OUBCOM_H__
#define __OUBCOM_H__

#include <vector>
#include "..\JLib\nifty.h"
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
		static jlib::CClientSocket& GetClientSocket() { return mgClientSocket;  }

	private:
		NIFTY_STATIC_DCL(CLogonSvrConnection, jlib::CClientSocket, mgClientSocket)
	};

	NIFTY_STATIC_INIT_DCL(CLogonSvrConnection, mgClientSocket)

	class CCmdConnect
	{
	public:
		static void Exec();
	};

	class CCmdLogon
	{
	public:
		static void Exec(const std::vector<std::string>& rTokVect);
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

#endif
