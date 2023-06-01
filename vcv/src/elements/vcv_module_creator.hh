#pragma once
#include "elements.hh"
#include "rack.hpp"

namespace MetaModule
{

struct VCVModuleParamCreator {

	VCVModuleParamCreator(rack::Module *module)
		: module{module} {
	}

	void count_element(BaseElement){};
	void count_element(JackInput) {
		num_inputs++;
	};
	void count_element(JackOutput) {
		num_outputs++;
	};
	void count_element(Pot) {
		num_params++;
	};
	void count_element(Switch) {
		num_params++;
	};
	void count_element(Light) {
		num_lights++;
	};
	void count_element(MediumLight<RedGreenBlueLight>) {
		num_lights += 3;
	};
	void count_element(MomentaryButtonRGB element) {
		num_lights += 3;
		num_params++;
	}
	void count_element(LatchingButtonMonoLight element) {
		num_params++;
		num_lights++;
	}
	void count_element(LEDEncoder element) {
		num_lights += 3;
		num_params++;
	};

	void config_element(BaseElement){};
	void config_element(JackInput el) {
		module->configInput(el.idx, el.short_name.data());
	};
	void config_element(JackOutput el) {
		module->configOutput(el.idx, el.short_name.data());
	};
	void config_element(Pot el) {
		module->configParam(el.idx, 0.f, 1.f, el.default_val, el.short_name.data());
	};
	void config_element(Light el) {
		module->configLight(el.idx, el.short_name.data());
	};
	void config_element(MomentaryButtonRGB element) {
		module->configParam(element.idx, 0.f, 1.f, element.default_val, element.short_name.data());
		//TODO: LED?
	}
	void config_element(LatchingButtonMonoLight element) {
		module->configParam(element.idx, 0.f, 1.f, element.default_val, element.short_name.data());
		//TODO: LED?
	}
	void config_element(Switch element) {
		module->configParam(element.idx, 0.f, 1.f, 0.f, element.short_name.data());
	};
	void config_element(Toggle3pos element) {
		module->configParam(element.idx, 0.f, 2.f, 0.f, element.short_name.data());
	};
	void config_element(LEDEncoder element) {
		module->configParam(element.idx, -INFINITY, INFINITY, 0.0f, element.short_name.data());
		// TODO: LED?
	};

	unsigned num_params = 0;
	unsigned num_inputs = 0;
	unsigned num_outputs = 0;
	unsigned num_lights = 0;

private:
	rack::Module *module;
};

} // namespace MetaModule
