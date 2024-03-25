#pragma once

#include "../helpers/mapping.h"
#include "gcem/include/gcem.hpp"
#include <numbers>

namespace MetaModule
{

struct Range {
    static constexpr float min = 0.f;
    static constexpr float max = 1.f;
};

static constinit auto PanningTable = 
    Mapping::LookupTable_t<50>::generate<Range>([](auto potValue) {
        return gcem::sin(potValue * std::numbers::pi / 2);
    });

static constinit auto LevelTable = 
    Mapping::LookupTable_t<50>::generate<Range>([](auto potValue) {
        return -1.f * gcem::log(1.01f - potValue) / 4.6f;
    });

}