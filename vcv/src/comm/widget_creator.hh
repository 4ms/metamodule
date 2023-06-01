#pragma once
#include "elements.hh"

namespace MetaModule
{

struct VCVCreator {
	// VCVCreator() {}

	template<typename T>
	void createWidget(T element){
		// by default, do nothing
	};

	unsigned num_params = 0;
	unsigned num_inputs = 0;
	unsigned num_outputs = 0;
	unsigned num_lights = 0;
};

} // namespace MetaModule
