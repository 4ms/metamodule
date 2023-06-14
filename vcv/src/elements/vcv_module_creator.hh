#pragma once
#include "elements.hh"
#include "rack.hpp"

namespace MetaModule
{

struct VCVModuleParamCreator {

	unsigned lights = 0;

	VCVModuleParamCreator(rack::Module *module)
		: module{module} {
	}

	void config_element(BaseElement){};

	void config_element(JackInput el) {
		module->configInput(el.idx, el.short_name.data());
	};
	void config_element(JackOutput el) {
		module->configOutput(el.idx, el.short_name.data());
	};
	void config_element(Pot el) {
		module->configParam(el.idx, el.min_val, el.max_val, el.default_val, el.short_name.data());
	};
	void config_element(MonoLight el) {
		module->configLight(lights++, el.short_name.data());
	};
	void config_element(DualLight el) {
		module->configLight(lights, el.short_name.data());
		lights+=2;
	};
	void config_element(MomentaryButtonRGB el) {
		module->configParam(el.idx, 0.f, 1.f, el.default_val, el.short_name.data());
		module->configLight(lights, el.short_name.data());
		lights += 3;
	}
	void config_element(LatchingButtonMonoLight el) {
		module->configParam(el.idx, 0.f, 1.f, el.default_val, el.short_name.data());
		module->configLight(lights++, el.short_name.data());
	}
	void config_element(Switch el) {
		module->configParam(el.idx, 0.f, 1.f, 0.f, el.short_name.data());
	};
	void config_element(Toggle3pos el) {
		module->configParam(el.idx, 0.f, 2.f, 0.f, el.short_name.data());
	};
	void config_element(LEDEncoder el) {
		module->configParam(el.idx, -INFINITY, INFINITY, 0.0f, el.short_name.data());
	};

private:
	rack::Module *module;
};

} // namespace MetaModule
