#include "StringHash.hpp"
#include "md5.h"

StringHash::StringHash(const char* s)
    : mOriginalString(s)
{
    mHash = md5::compute(mOriginalString);
}

bool StringHash::operator == (const StringHash& rhs) const
{
    return mHash == rhs.mHash;
}

const char* StringHash::String() const
{
    return mOriginalString;
}