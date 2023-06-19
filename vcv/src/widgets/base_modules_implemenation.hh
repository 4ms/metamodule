#include "vcv_module_creator.hh"
#include "CoreModules/elements/elements.hh"

namespace MetaModule
{

template <>
void VCVModuleParamCreator::config_element<JackInput>(JackInput el) {
	module->configInput(el.idx, el.short_name.data());
};

template <>
void VCVModuleParamCreator::config_element<JackOutput>(JackOutput el) {
	module->configOutput(el.idx, el.short_name.data());
};

template <>
void VCVModuleParamCreator::config_element<Pot>(Pot el) {
	module->configParam(el.idx, el.min_val, el.max_val, el.default_val, el.short_name.data());
};

template <>
void VCVModuleParamCreator::config_element<MonoLight>(MonoLight el) {
	module->configLight(lights++, el.short_name.data());
};

template <>
void VCVModuleParamCreator::config_element<DualLight>(DualLight el) {
	module->configLight(lights, el.short_name.data());
	lights += 2;
};

template <>
void VCVModuleParamCreator::config_element<MomentaryButtonRGB>(MomentaryButtonRGB el) {
	module->configParam(el.idx, 0.f, 1.f, el.default_val, el.short_name.data());
	module->configLight(lights, el.short_name.data());
	lights += 3;
}

template <>
void VCVModuleParamCreator::config_element<LatchingButtonMonoLight>(LatchingButtonMonoLight el) {
	module->configParam(el.idx, 0.f, 1.f, el.default_val, el.short_name.data());
	module->configLight(lights++, el.short_name.data());
}

template <>
void VCVModuleParamCreator::config_element<Switch>(Switch el) {
	module->configParam(el.idx, 0.f, 1.f, 0.f, el.short_name.data());
};

template <>
void VCVModuleParamCreator::config_element<Toggle3pos>(Toggle3pos el) {
	module->configParam(el.idx, 0.f, 2.f, 0.f, el.short_name.data());
};

template <>
void VCVModuleParamCreator::config_element<LEDEncoder>(LEDEncoder el) {
	module->configParam(el.idx, -INFINITY, INFINITY, 0.0f, el.short_name.data());
};

}