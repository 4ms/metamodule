#pragma once
#include "VCV-adaptor/VCV_module_wrapper.hh"

namespace rack
{

struct Module : VCVModuleWrapper {

	void config(unsigned num_params, unsigned num_inputs, unsigned num_outputs, unsigned num_lights) {
		params.resize(num_params);
		inputs.resize(num_inputs);
		outputs.resize(num_outputs);
		lights.resize(num_lights);
	}

	void configParam(unsigned id,
					 float min = 0,
					 float max = 0,
					 float deflt = 0,
					 std::string_view name = "",
					 std::string_view units = "") {
		//param_scales[id].range
		//param_scales[id].offset
	}

	void configBypass(unsigned, unsigned) {
	}
};

} // namespace rack
