#pragma once

#include "../helpers/mapping.h"
#include "gcem/include/gcem.hpp"
#include <numbers>

namespace MetaModule
{

struct PanningRange {
    static constexpr float min = 0.f;
    static constexpr float max = 1.f;
};

static constinit auto PanningTable = 
    Mapping::LookupTable_t<50>::generate<PanningRange>([](auto potValue) {
        return gcem::sin(potValue * std::numbers::pi / 2);
    });

}