#pragma once

#include "StringHash.hpp"
#include <vector>

class StringHashCollection
{
public:
    StringHashCollection() = default;
    virtual ~StringHashCollection() = default;

    explicit StringHashCollection(u32 reserveSize)
    {
        mHashes.reserve(reserveSize);
    }

    void Add(const StringHash& h)
    {
        mHashes.emplace_back(h);
    }

    const std::vector<StringHash>& Hashes() const
    {
        return mHashes;
    }

private:
    std::vector<StringHash> mHashes;
};
