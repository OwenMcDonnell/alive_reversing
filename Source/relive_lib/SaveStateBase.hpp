#pragma once

#include "ObjectTypes.hpp"

struct SaveStateBase
{
    SaveStateBase(StringHash type, u32 size)
        : mType(type)
        , mSize(size)
    { }
    StringHash mType;
    u32 mSize = 0;
};
