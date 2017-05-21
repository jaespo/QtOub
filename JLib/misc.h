#pragma once
//
//	Miscelleous declarations
//
//	(C) 2016 by Jeffery A Esposito
//

#include <string.h>
#include <sstream>

namespace jlib
{

	//
	//	Various data types used by oub
	//
	typedef __int16			YReqCode;
	typedef __int16			YRspCode;
	typedef __int64			YReqSeq;
	typedef char			YUserId[32];
	typedef char			YPassword[32];
	typedef char			YErrorText[1024];

	//
	//	fills a fixed width field, padding spaces.
	//
	//	dst is a fixed sized char field
	//	src is a std::string
	//
#define FILLFIELD( dst, src )									\
{																\
    memmove(dst, src.c_str(), src.size());						\
	memchr(dst + src.size(), ' ', sizeof( dst ) - src.size());	\
}

	//
	//	This define creates and throws a CErrorInfo
	//
#define THROW_ERR( zCode, zText )						\
{														\
	jlib::CErrorInfo	vErrorInfo(zCode, __FILE__ );	\
	std::ostringstream	ss;								\
	ss zText;						                    \
	vErrorInfo.SetText( ss.str() );						\
	throw vErrorInfo;									\
}

	//
	//	Class thrown on an error 
	//
	class CErrorInfo
	{
	public:
		CErrorInfo() { mCode = 0; }
		CErrorInfo(__int32 vCode, const char *pzSrcFile);
		~CErrorInfo() {}
		CErrorInfo(CErrorInfo& ei)
		{
			msSrcFile = ei.msSrcFile;
			mCode = ei.mCode;
			msText = ei.msText;
		}
		std::string GetText() { return msText; }
		std::string GetSrcFile() { return msSrcFile; }
		__int32 GetCode() { return mCode; }

		void SetText(const std::string& sText ) { msText = sText; }
		void SetSrcFile(const std::string& sSrcFile) { msSrcFile = sSrcFile; }
		void GetCode(__int32 vCode ) { mCode = vCode; }

	private:
		std::string						msSrcFile;
		__int32							mCode;
		std::string 					msText;
	};

};	// namespace jlib
