#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV_adaptor/widget_convert/base.hh"

// Forward declare widgets from Befaco/src/plugin.hpp
namespace rack::componentlibrary
{
struct RedGreenBlueLight;
}

// Used in Frames and Warps
template<typename Base>
struct Rogan6PSLight;
template<>
struct Rogan6PSLight<rack::componentlibrary::RedGreenBlueLight>;

// Convert Widgets to MetaModule Elements

namespace MetaModule
{

template<>
inline Element make_element<Rogan6PSLight<rack::componentlibrary::RedGreenBlueLight>>(BaseElement b) {
	return NullElement{};
};

} // namespace MetaModule
