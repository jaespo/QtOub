#ifndef __TRACE_H__
#define __TRACE_H__

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

#include "misc.h"
#include "nifty.h"

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

	NIFTY_DCL(CTrace, gTrace)

}   // end namespace

#endif

