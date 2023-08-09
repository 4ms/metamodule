#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV_adaptor/widget_convert/base.hh"

// Forward declare widgets from Befaco/src/plugin.hpp
namespace rack::componentlibrary
{
struct RedGreenBlueLight;
}

template<typename Base>
struct Rogan6PSLight;

template<>
struct Rogan6PSLight<rack::componentlibrary::RedGreenBlueLight>;

namespace rack
{

template<>
struct ElementConvert<Rogan6PSLight<rack::componentlibrary::RedGreenBlueLight>> {
	using ElementType = MetaModule::NullElement;
};

} // namespace rack
