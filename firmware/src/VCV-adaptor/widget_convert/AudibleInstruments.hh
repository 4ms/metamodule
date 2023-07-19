#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV-adaptor/widget_convert/base.hh"

// Forward declare widgets from Befaco/src/plugin.hpp
namespace rack
{
struct RedGreenBlueLight;
}

template<typename Base>
struct Rogan6PSLight;

template<>
struct Rogan6PSLight<rack::RedGreenBlueLight>;

namespace rack
{

template<>
struct ElementConvert<Rogan6PSLight<rack::RedGreenBlueLight>> {
	using ElementType = MetaModule::NullElement;
};

} // namespace rack
