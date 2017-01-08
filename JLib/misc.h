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
#define THROW_ERR( zCode, zText )					\
{													\
	oub::CErrorInfo	vErrorInfo(zCode, __FILE__ );	\
	vErrorInfo.GetStream() zText;					\
	throw vErrorInfo;								\
}

	//
	//	Class thrown on an error 
	//
	class CErrorInfo
	{
	public:
		CErrorInfo() { mCode = 0; }
		CErrorInfo(__int32 vCode, const char *pzSrcFile);

		std::ostringstream& GetStream() { return mStream; }
		std::string GetText() { return mStream.str(); }
		std::string GetSrcFile() { return msSrcFile; }
		__int32 GetCode() { return mCode; }

	private:
		std::string						msSrcFile;
		__int32							mCode;
		std::ostringstream				mStream;
	};

};	// namespace jlib
