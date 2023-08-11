#pragma once

#include <array>

class StringHash final
{
public:
    explicit StringHash(const char* s);

    bool operator==(const StringHash& rhs) const;

    const char* String() const;

    bool operator<(const StringHash& rhs) const
    {
        return mHash < rhs.mHash;
    }


private:
    using Digest = std::array<u8, 16>;
    Digest mHash = {};
    const char* mOriginalString;
};
