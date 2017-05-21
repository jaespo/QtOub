#pragma once
//
//	Miscelleous declarations
//
//	(C) 2016 by Jeffery A Esposito
//

#include <string.h>
#include <sstream>


//
//	define used in a .h file to declare a global static variable whose construction and
//	destruction or is controlled by a nifty reference counter
//
//	vClass	is the class of the variable
//	vVar	is the name of the variable
//
#define GLOBAL_DCL( vClass, vVar )			\
	extern vClass&			vVar;			\
	static struct C##vVar##_Initializer		\
	{										\
		C##vVar##_Initializer();			\
		~C##vVar##_Initializr();			\
	} g##vVar##_Initializer;				

//
//	define used in a .cpp file to construct a global object before its first use
//	and destruct it after all other static objects that use it are destructed
//
//	vNameSpace		is the namespace of the object's class
//	vClass			is the class of the object
//	vVar			is the variable name of the object
//
#define GLOBAL_IMPL( vNameSpace, vClass, vVar )								\
	static int vNameSpace##vVar##_nifty_counter;							\
	static typename std::aligned_storage<sizeof(vNamespace##::##vClass),	\
		alignof(vNamespace##::##vClass)>::type vNameSpace##vVar##_buf;		\
	vNamespace::vClass& vNameSpace##::##vVar =								\
		reinterpret_cast<vNameSpace##::##vVar&>(CTrace_buf);				\
	vNameSpace##::C##vVar##_Initializer()									\
	{
	if (nifty_counter++ == 0)
	new (&jlib::gTrace) CTrace();
	}

	jlib::CJlibInitializer::~CJlibInitializer()
	{
		if (--nifty_counter == 0)
			(&jlib::gTrace)->~CTrace();
	}

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
