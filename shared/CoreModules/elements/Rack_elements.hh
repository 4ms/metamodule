#pragma once
#include "base_element.hh"

namespace MetaModule
{

template<typename LedT>
struct VCVLightBezel : LedT {};

template<typename LedT>
struct MediumLight : LedT {};

template<typename LedT>
struct SmallLight : LedT {};

} // namespace MetaModule
