#pragma once
///////////////////////////////////////////////////////////////////////
//
//	trace.h
//
//	(C) 2016 by Jeffery A Esposito
//
///////////////////////////////////////////////////////////////////////

#include <strstream>
#include <string>
#include <list>
#include <algorithm>
#include <iomanip>
#include <new>
#include <type_traits>

//
//  Trace utilities
//
#define TR( strTag, txt )                                   \
{                                                           \
    if ( jlib::gTrace.IsTagActive( strTag ) )				\
        std::cout << std::left << std::setw( 16 )           \
            << strTag                                       \
            << ": " txt                                     \
            << std::endl;                                   \
}

namespace jlib
{
	class CTrace
	{
	public:
		void EnableTag(const char*);
		void Reset();
		bool IsTagActive(const char*) const;

	private:
		std::list<std::string>  mTagList;
	};

	extern CTrace&			gTrace;

	static struct CJlibInitializer
	{
		CJlibInitializer();
		~CJlibInitializer();
	} gJlibInitializer;


}   // end namespace
