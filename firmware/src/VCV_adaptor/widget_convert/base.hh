#pragma once
#include "CoreModules/elements/elements.hh"

namespace rack
{

// Default
template<typename TParamWidget>
struct ElementConvert {
	using ElementType = MetaModule::NullElement;
};

} // namespace rack
