#include "vcv_creation_context.hh"
#include "CoreModules/elements/elements.hh"

namespace MetaModule::VCVImplementation::Module
{

void do_config_element(JackInput el, ModuleContext_t& context) {
	context.module->configInput(el.idx, el.short_name.data());
};
void do_config_element(JackOutput el, ModuleContext_t& context) {
	context.module->configOutput(el.idx, el.short_name.data());
};
void do_config_element(Pot el, ModuleContext_t& context) {
	context.module->configParam(el.idx, el.min_val, el.max_val, el.default_val, el.short_name.data());
};
void do_config_element(MonoLight el, ModuleContext_t& context) {
	context.module->configLight(context.lights++, el.short_name.data());
};
void do_config_element(DualLight el, ModuleContext_t& context) {
	context.module->configLight(context.lights, el.short_name.data());
	context.lights += 2;
};
void do_config_element(MomentaryButtonRGB el, ModuleContext_t& context) {
	context.module->configParam(el.idx, 0.f, 1.f, el.default_val, el.short_name.data());
	context.module->configLight(context.lights, el.short_name.data());
	context.lights += 3;
}
void do_config_element(LatchingButtonMonoLight el, ModuleContext_t& context) {
	context.module->configParam(el.idx, 0.f, 1.f, el.default_val, el.short_name.data());
	context.module->configLight(context.lights++, el.short_name.data());
}
void do_config_element(Switch el, ModuleContext_t& context) {
	context.module->configParam(el.idx, 0.f, 1.f, 0.f, el.short_name.data());
};
void do_config_element(Toggle3pos el, ModuleContext_t& context) {
	context.module->configParam(el.idx, 0.f, 2.f, 0.f, el.short_name.data());
};
inline void do_config_element(EncoderRGB el, ModuleContext_t &context) {
	context.module->configParam(el.idx, -INFINITY, INFINITY, 0.0f, el.short_name.data());
};
inline void do_config_element(EncoderWhiteLight el, ModuleContext_t &context) {
	context.module->configParam(el.idx, -INFINITY, INFINITY, 0.0f, el.short_name.data());
};

}