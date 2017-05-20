#include <new>
#include "trace.h"

//
//  Statics
//
static int nifty_counter;
static typename std::aligned_storage<sizeof(jlib::CTrace),
	alignof(jlib::CTrace)>::type CTrace_buf;
jlib::CTrace& jlib::gTrace = reinterpret_cast<jlib::CTrace&>( CTrace_buf );


// jlib::CTrace::CTrace() {}
// jlib::CTrace::~CTrace() {}

//
//  Enables the specfied tag
//      
//  @param pzTag
//      is the tag to enable
//
void jlib::CTrace::EnableTag(const char* pzTag)
{
	mTagList.push_back(std::string(pzTag));
}

//
//  Disables all of the enabled tags
//
void jlib::CTrace::Reset()
{
	mTagList.erase(mTagList.begin(), mTagList.end());
}

bool jlib::CTrace::IsTagActive(const char* pzTag) const
{
	std::list<std::string>::const_iterator it;
	std::string      sTag(pzTag);

	it = std::find(mTagList.begin(), mTagList.end(), sTag);
	return (it != mTagList.end());
}

//
//	Static globals initializer
//
jlib::CJlibInitializer::CJlibInitializer()
{
	if (nifty_counter++ == 0) 
		new (&jlib::gTrace) CTrace();
}

jlib::CJlibInitializer::~CJlibInitializer()
{
	if (--nifty_counter == 0) 
		(&jlib::gTrace)->~CTrace();
}

