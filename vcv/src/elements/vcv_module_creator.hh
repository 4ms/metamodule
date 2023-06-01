#pragma once
#include "elements.hh"
#include "rack.hpp"

namespace MetaModule
{

struct VCVModuleParamCreator {

	VCVModuleParamCreator(rack::Module *module)
		: module{module} {
	}

	void count_element(BaseElement element){};

	void count_element(InJackElement element) {
		num_inputs++;
	};
	void count_element(OutJackElement element) {
		num_outputs++;
	};
	void count_element(KnobElement element) {
		num_params++;
	};
	void count_element(LightElement element) {
		num_lights++;
	};

	void count_element(MomentaryButton element) {
		num_lights += 3;
		num_params++;
	}
	void count_element(LatchingButton element) {
		num_params++;
		num_lights++;
	}
	void count_element(Toggle2pos element) {
		num_params++;
	};
	void count_element(Toggle3pos element) {
		num_params++;
	};
	void count_element(LEDEncoder element) {
		num_lights += 3;
		num_params++;
	};

	void config_element(BaseElement element){};
	void config_element(InJackElement element) {
		std::visit([this](auto &el) { module->configInput(el.idx, el.short_name.data()); }, element);
	};
	void config_element(OutJackElement element) {
		std::visit([this](auto &el) { module->configOutput(el.idx, el.short_name.data()); }, element);
	};
	void config_element(KnobElement element) {
		std::visit([this](auto &el) { module->configParam(el.idx, 0.f, 1.f, el.default_val, el.short_name.data()); },
				   element);
	};
	void config_element(LightElement element) {
		std::visit([this](auto &el) { module->configLight(el.idx, el.short_name.data()); }, element);
	};

	void config_element(MomentaryButton element) {
		module->configParam(element.idx, 0.f, 1.f, element.default_val, element.short_name.data());
	}
	void config_element(LatchingButton element) {
		module->configParam(element.idx, 0.f, 1.f, element.default_val, element.short_name.data());
	}
	void config_element(Toggle2pos element) {
		module->configParam(element.idx, 0.f, 1.f, 0.f, element.short_name.data());
	};
	void config_element(Toggle3pos element) {
		module->configParam(element.idx, 0.f, 2.f, 0.f, element.short_name.data());
		// scaleFactor = 1.f/2.f;
	};
	void config_element(LEDEncoder element) {
		module->configParam(element.idx, -INFINITY, INFINITY, 0.0f, element.short_name.data());
	};

	unsigned num_params = 0;
	unsigned num_inputs = 0;
	unsigned num_outputs = 0;
	unsigned num_lights = 0;

private:
	rack::Module *module;
};

} // namespace MetaModule
