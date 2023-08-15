#include "StringHash.hpp"

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