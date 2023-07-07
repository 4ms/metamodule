#include "../vcv_creation_context.hh"
#include "CoreModules/elements/element_counter.hh"
#include "befaco_widgets.hh"

namespace MetaModule::VCVImplementation::Widget
{

using Indices = ElementCount::Indices;

////// Helpers

template<typename WidgetT, typename LightT = void>
void create_befaco_param(float x_mm, float y_mm, const Indices &indices, const WidgetContext_t &context) {
	auto corner_pos = rack::Vec(x_mm, y_mm);
	context.module_widget->addParam(rack::createParam<WidgetT>(corner_pos, context.module, indices.param_idx));

	if constexpr (!std::is_same_v<LightT, void>)
		context.module_widget->addChild(rack::createLight<LightT>(corner_pos, context.module, indices.light_idx));
}

inline void do_create(Davies1900hWhiteKnob el, const Indices &indices, const WidgetContext_t &context) {
	create_befaco_param<rack::Davies1900hWhiteKnob>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(Davies1900hRedKnob el, const Indices &indices, const WidgetContext_t &context) {
	create_befaco_param<rack::Davies1900hRedKnob>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(BefacoTinyKnobWhite el, const Indices &indices, const WidgetContext_t &context) {
	create_befaco_param<Befaco::BefacoTinyKnobWhite>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(BefacoTinyKnobRed el, const Indices &indices, const WidgetContext_t &context) {
	create_befaco_param<Befaco::BefacoTinyKnobRed>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(BefacoTinyKnobDarkGrey el, const Indices &indices, const WidgetContext_t &context) {
	create_befaco_param<Befaco::BefacoTinyKnobDarkGrey>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(BefacoTinyKnobLightGrey el, const Indices &indices, const WidgetContext_t &context) {
	create_befaco_param<Befaco::BefacoTinyKnobLightGrey>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(BefacoTinyKnobBlack el, const Indices &indices, const WidgetContext_t &context) {
	create_befaco_param<Befaco::BefacoTinyKnobBlack>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(Davies1900hLargeGreyKnob el, const Indices &indices, const WidgetContext_t &context) {
	create_befaco_param<Befaco::Davies1900hLargeGreyKnob>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(Davies1900hLightGreyKnob el, const Indices &indices, const WidgetContext_t &context) {
	create_befaco_param<Befaco::Davies1900hLightGreyKnob>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(Davies1900hDarkGreyKnob el, const Indices &indices, const WidgetContext_t &context) {
	create_befaco_param<Befaco::Davies1900hDarkGreyKnob>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(CKSSNarrow el, const Indices &indices, const WidgetContext_t &context) {
	create_befaco_param<Befaco::CKSSNarrow>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(Crossfader el, const Indices &indices, const WidgetContext_t &context) {
	create_befaco_param<Befaco::Crossfader>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(BefacoSwitchHorizontal el, const Indices &indices, const WidgetContext_t &context) {
	create_befaco_param<Befaco::BefacoSwitchHorizontal>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(CKSSHoriz2 el, const Indices &indices, const WidgetContext_t &context) {
	create_befaco_param<Befaco::CKSSHoriz2>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(CKSSVert7 el, const Indices &indices, const WidgetContext_t &context) {
	create_befaco_param<Befaco::CKSSVert7>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(CKSSHoriz4 el, const Indices &indices, const WidgetContext_t &context) {
	create_befaco_param<Befaco::CKSSHoriz4>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(CKSSNarrow3 el, const Indices &indices, const WidgetContext_t &context) {
	create_befaco_param<Befaco::CKSSNarrow3>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(Davies1900hLargeLightGreyKnob el, const Indices &indices, const WidgetContext_t &context) {
	create_befaco_param<Befaco::Davies1900hLargeLightGreyKnob>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(BefacoSlidePotSmall el, const Indices &indices, const WidgetContext_t &context) {
	create_befaco_param<Befaco::BefacoSlidePotSmall>(el.x_mm, el.y_mm, indices, context);
}

// FIXME: Why is this needed?
static const inline auto BefacoJackOffsetFix = rack::Vec{-10, -10};

inline void do_create(BefacoInputPort el, const Indices &indices, const WidgetContext_t &context) {
	context.module_widget->addInput(rack::createInput<Befaco::BananutBlack>(
		rack::Vec(el.x_mm, el.y_mm).plus(BefacoJackOffsetFix), context.module, indices.input_idx));
}

inline void do_create(BefacoOutputPort el, const Indices &indices, const WidgetContext_t &context) {
	context.module_widget->addOutput(rack::createOutput<Befaco::BananutRed>(
		rack::Vec(el.x_mm, el.y_mm).plus(BefacoJackOffsetFix), context.module, indices.output_idx));
}

} // namespace MetaModule::VCVImplementation::Widget
