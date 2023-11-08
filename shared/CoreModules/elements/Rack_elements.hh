#pragma once
#include "base_element.hh"

namespace MetaModule
{

struct LEDBezel : MomentaryButton {};

template<typename LedT>
struct VCVLightBezel : LedT {};

template<typename LedT>
struct MediumLight : LedT {};

template<typename LedT>
struct SmallLight : LedT {};

} // namespace MetaModule
