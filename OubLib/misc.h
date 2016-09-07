#pragma once
//
//	Miscelleous declarations used by oub
//
//	(C) 2016 by Jeffery A Esposito
//

#include <string.h>

//
//	Various data types used by oub
//
typedef __int16			YReqCode;
typedef __int16			YRspCode;
typedef __int64			YReqId;
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
	memchr(dst + src.size(), ' ', sizeof( dst ) - src.size())	\
}
