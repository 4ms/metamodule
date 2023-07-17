#pragma once
#include "CoreModules/elements/elements.hh"

namespace rack
{

template<typename TParamWidget>
struct ElementConvert {
	//FIXME: more sensible default
	using ElementType = MetaModule::Davies1900hBlackKnob;
};

} // namespace rack
