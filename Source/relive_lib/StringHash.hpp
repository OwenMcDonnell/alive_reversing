#pragma once

#include <array>

class StringHash final
{
public:
    explicit constexpr StringHash(const char* s);

    bool operator==(const StringHash& rhs) const;
    bool operator!=(const StringHash& rhs) const;

    const char* String() const;

    bool operator<(const StringHash& rhs) const
    {
        return mHash < rhs.mHash;
    }

    constexpr u64 Value() const
    {
        return 
            (static_cast<u64>(mHash[7]) << 0) + 
            (static_cast<u64>(mHash[6]) << 8) + 
            (static_cast<u64>(mHash[5]) << 16) + 
            (static_cast<u64>(mHash[4]) << 24) + 
            (static_cast<u64>(mHash[3]) << 32) + 
            (static_cast<u64>(mHash[2]) << 40) + 
            (static_cast<u64>(mHash[1]) << 48) + 
            (static_cast<u64>(mHash[0]) << 56);
    }

private:
    using Digest = std::array<u8, 16>;
    Digest mHash = {};
    const char* mOriginalString;
};
