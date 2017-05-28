#include "trace.h"

//
//  Statics
//
NIFTY_IMPL(jlib, CTrace, gTrace )

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


