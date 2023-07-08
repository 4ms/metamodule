#pragma once
#include "VCV-adaptor/VCV_module_wrapper.hh"
#include "VCV-adaptor/json.hpp"
#include "VCV-adaptor/param_quantity.hh"

namespace rack
{
struct Module : VCVModuleWrapper {

	static constexpr size_t PORT_MAX_CHANNELS = 4;

	static_assert(PORT_MAX_CHANNELS % 4 == 0, "PORT_MAX_CHANNELS must be a mulitple of 4 or else simd:: fails");

	void config(unsigned num_params, unsigned num_inputs, unsigned num_outputs, unsigned num_lights = 0) {
		params.resize(num_params);
		inputs.resize(num_inputs);
		outputs.resize(num_outputs);
		lights.resize(num_lights);
	}

	template<class TParamQuantity = ParamQuantity>
	TParamQuantity *configParam(int paramId,
								float minValue,
								float maxValue,
								float defaultValue,
								std::string_view name = "",
								std::string_view unit = "",
								float displayBase = 0.f,
								float displayMultiplier = 1.f,
								float displayOffset = 0.f) {
		// TODO: set
		// param_scales[id].range
		// param_scales[id].offset
	}

	ParamQuantity *getParamQuantity(int index) {
		return &mock_pq;
	}

	void configBypass(unsigned, unsigned) {
	}

	virtual json_t *dataToJson() {
		return nullptr;
	}
	virtual void dataFromJson(json_t *) {
	}

private:
	ParamQuantity mock_pq;
};

} // namespace rack
