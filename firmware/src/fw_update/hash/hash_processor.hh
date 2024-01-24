#pragma once

#include <span>
#include <cstdio>
#include "md5_hash.h"

namespace MetaModule
{

class MD5Processor
{
public:
    using Digest_t = std::array<uint8_t,16>;

public:
    MD5Processor();
    void update(std::span<uint8_t>);
    Digest_t getDigest();

private:
    MD5Context context;
};

inline auto to_hex_string = [](MD5Processor::Digest_t val) 
{
    std::array<char,32> result;
    for (std::size_t i=0; i<val.size(); i++)
    {
        sprintf(result.data() + 2*i, "%02x", val[i]);
    }
    return result;
};

}