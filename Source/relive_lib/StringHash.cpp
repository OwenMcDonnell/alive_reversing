#include "StringHash.hpp"
#include "md5.h"

constexpr StringHash::StringHash(const char* s)
    : mOriginalString(s)
{
    mHash = md5::compute(mOriginalString);
}

bool StringHash::operator == (const StringHash& rhs) const
{
    return mHash == rhs.mHash;
}

bool StringHash::operator != (const StringHash& rhs) const
{
    return mHash != rhs.mHash;
}

const char* StringHash::String() const
{
    return mOriginalString;
}