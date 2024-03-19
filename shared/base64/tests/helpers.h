#pragma once

#include <limits>
#include <vector>


inline std::vector<uint8_t> make_bin_array(size_t count)
{
    std::vector<uint8_t> data(count);
    constexpr size_t max = std::numeric_limits<uint8_t>::max() + 1;

    for (size_t i = 0; i < count; ++i)
        data[i] = static_cast<uint8_t>(i % max);

    return data;
};
