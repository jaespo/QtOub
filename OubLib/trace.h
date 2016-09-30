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

//
//  Trace utilities
//
#define TR( strTag, txt )                                   \
{                                                           \
    if ( oub::CTrace::inst().IsTagActive( strTag ) )    \
        std::cout << std::left << std::setw( 16 )           \
            << strTag                                       \
            << ": " txt                                     \
            << std::endl;                                   \
}

namespace oub 
{
	class CTrace
	{
	public:
		static CTrace& inst() { return mgInst; }

		void EnableTag(const char*);
		void Reset();
		bool IsTagActive(const char*) const;

	private:
		static CTrace           mgInst;
		std::list<std::string>  mTagList;
	};

}   // end namespace
