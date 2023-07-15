#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/elements.hh"
#include "vcv_creation_context.hh"

namespace MetaModule::VCVImplementation::Module
{
using Indices = ElementCount::Indices;

inline void do_config_element(JackInput el, const Indices &indices, const ModuleContext_t &context) {
	context.module->configInput(indices.input_idx, el.short_name.data());
};

inline void do_config_element(JackOutput el, const Indices &indices, const ModuleContext_t &context) {
	context.module->configOutput(indices.output_idx, el.short_name.data());
};

inline void do_config_element(Pot el, const Indices &indices, const ModuleContext_t &context) {
	context.module->configParam(indices.param_idx, 0.f, 1.f, 0.5f, el.short_name.data());
};

inline void do_config_element(SliderMonoLight el, const Indices &indices, const ModuleContext_t &context) {
	context.module->configParam(indices.param_idx, 0.f, 1.f, 0.5f, el.short_name.data());
	context.module->configLight(indices.light_idx, el.short_name.data());
};

inline void do_config_element(LightElement el, const Indices &indices, const ModuleContext_t &context) {
	context.module->configLight(indices.light_idx, el.short_name.data());
};

inline void do_config_element(MomentaryButtonRGB el, const Indices &indices, const ModuleContext_t &context) {
	context.module->configParam(indices.param_idx, 0, 1, 0, el.short_name.data());
	context.module->configLight(indices.light_idx, el.short_name.data());
}

inline void do_config_element(LatchingButtonMonoLight el, const Indices &indices, const ModuleContext_t &context) {
	context.module->configParam(indices.param_idx, 0, 1, 0, el.short_name.data());
	context.module->configLight(indices.light_idx, el.short_name.data());
}

inline void do_config_element(Switch el, const Indices &indices, const ModuleContext_t &context) {
	context.module->configParam(indices.param_idx, 0, 1, 0, el.short_name.data());
};

inline void do_config_element(Toggle3pos el, const Indices &indices, const ModuleContext_t &context) {
	context.module->configParam(indices.param_idx, 0, 2, 0, el.short_name.data());
};

inline void do_config_element(Encoder el, const Indices &indices, const ModuleContext_t &context) {
	context.module->configParam(indices.param_idx, -INFINITY, INFINITY, 0, el.short_name.data());
};

inline void do_config_element(EncoderRGB el, const Indices &indices, const ModuleContext_t &context) {
	context.module->configParam(indices.param_idx, -INFINITY, INFINITY, 0, el.short_name.data());
	context.module->configLight(indices.light_idx, el.short_name.data());
};

inline void do_config_element(EncoderWhiteLight el, const Indices &indices, const ModuleContext_t &context) {
	context.module->configParam(indices.param_idx, -INFINITY, INFINITY, 0, el.short_name.data());
	context.module->configLight(indices.light_idx, el.short_name.data());
};

} // namespace MetaModule::VCVImplementation::Module
