#include "../vcv_creation_context.hh"
#include "4ms_widgets.hh"
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/elements.hh"

namespace MetaModule::VCVImplementation::Widget
{
using Indices = ElementCount::Indices;

// Units are in center positions in mm for 4ms widgets, but VCV uses 75px/in coordinates
static constexpr float Fix4msScaling = 75.f / 25.4f;

////// Helpers

template<typename WidgetT, typename LightT = void>
void create_4ms_param(float x_mm, float y_mm, const Indices &indices, const WidgetContext_t &context) {
	auto ctr_pos = rack::Vec(x_mm, y_mm).mult(Fix4msScaling);
	context.module_widget->addParam(rack::createParamCentered<WidgetT>(ctr_pos, context.module, indices.param_idx));

	if constexpr (!std::is_same_v<LightT, void>)
		context.module_widget->addChild(rack::createLightCentered<LightT>(ctr_pos, context.module, indices.light_idx));
}

template<typename WidgetT, typename LightT = void>
void create_4ms_light_param(float x_mm, float y_mm, const Indices &indices, const WidgetContext_t &context) {
	auto ctr_pos = rack::Vec(x_mm, y_mm).mult(Fix4msScaling);
	context.module_widget->addParam(
		rack::createLightParamCentered<WidgetT>(ctr_pos, context.module, indices.param_idx, indices.light_idx));
}

/////////////// Params

inline void do_create(DaviesLargeKnob el, const Indices &indices, const WidgetContext_t &context) {
	create_4ms_param<DaviesLarge4ms>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(Davies1900hBlackKnob el, const Indices &indices, const WidgetContext_t &context) {
	create_4ms_param<Davies1900hBlackKnob4ms>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(Knob9mm el, const Indices &indices, const WidgetContext_t &context) {
	create_4ms_param<Small9mmKnob>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(Slider25mmVert el, const Indices &indices, const WidgetContext_t &context) {
	create_4ms_param<FourmsSlider>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(Slider25mmHoriz el, const Indices &indices, const WidgetContext_t &context) {
	create_4ms_param<FourmsSliderHorizontal>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(Slider25mmVertLED el, const Indices &indices, const WidgetContext_t &context) {
	create_4ms_light_param<FourmsLightSlider<rack::WhiteLight>>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(Slider25mmHorizLED el, const Indices &indices, const WidgetContext_t &context) {
	create_4ms_light_param<FourmsLightSliderHorizontal<rack::WhiteLight>>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(Toggle2pos el, const Indices &indices, const WidgetContext_t &context) {
	create_4ms_param<SubMiniToggle2pos>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(Toggle3pos el, const Indices &indices, const WidgetContext_t &context) {
	create_4ms_param<SubMiniToggle3pos>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(LatchingButtonMonoLight el, const Indices &indices, const WidgetContext_t &context) {
	using WidgetT = LatchingSwitch<rack::LEDBezel>;
	using LightT = rack::LEDBezelLight<rack::YellowLight>;
	create_4ms_param<WidgetT, LightT>(el.x_mm, el.y_mm, indices, context);
	// create_light_param??
}

inline void do_create(MomentaryButtonRGB el, const Indices &indices, const WidgetContext_t &context) {
	using WidgetT = rack::MomentarySwitch<rack::LEDBezel>;
	using LightT = rack::LEDBezelLight<rack::RedGreenBlueLight>;
	create_4ms_param<WidgetT, LightT>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(Encoder el, const Indices &indices, const WidgetContext_t &context) {
	create_4ms_param<Davies1900hBlackKnobUnlined4ms>(el.x_mm, el.y_mm, indices, context);
}

inline void do_create(SmallEncoder el, const Indices &indices, const WidgetContext_t &context) {
	create_4ms_param<Small9mmUnlinedKnob>(el.x_mm, el.y_mm, indices, context);
}

// TODO: does this look OK when rendered?
inline void do_create(EncoderRGB el, const Indices &indices, const WidgetContext_t &context) {
	using WidgetT = Davies1900hBlackKnobUnlined4ms;
	using LightT = rack::LEDBezelLight<rack::RedGreenBlueLight>;
	create_4ms_param<WidgetT, LightT>(el.x_mm, el.y_mm, indices, context);
}

// TODO: does this look OK when rendered?
inline void do_create(SmallLEDEncoder el, const Indices &indices, const WidgetContext_t &context) {
	using WidgetT = Small9mmUnlinedKnob;
	using LightT = rack::LEDBezelLight<rack::RedGreenBlueLight>;
	create_4ms_param<WidgetT, LightT>(el.x_mm, el.y_mm, indices, context);
}

////// Jacks

inline void do_create(JackOutput el, const Indices &indices, const WidgetContext_t &context) {
	auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
	context.module_widget->addOutput(
		rack::createOutputCentered<rack::PJ301MPort>(ctr_pos, context.module, indices.output_idx));
}

inline void do_create(JackInput el, const Indices &indices, const WidgetContext_t &context) {
	auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
	context.module_widget->addInput(
		rack::createInputCentered<rack::PJ301MPort>(ctr_pos, context.module, indices.input_idx));
}

/////// Lights

inline void do_create(RedBlueLight el, const Indices &indices, const WidgetContext_t &context) {
	auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);

	// FIXME: create our own Red/Blue light, VCV only has Red/Green
	using LightT = rack::LEDBezelLight<rack::GreenRedLight>;
	context.module_widget->addChild(rack::createLightCentered<LightT>(ctr_pos, context.module, indices.light_idx));
}

inline void do_create(OrangeLight el, const Indices &indices, const WidgetContext_t &context) {
	auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);

	// FIXME: create our own Orange light
	using LightT = rack::LEDBezelLight<rack::YellowLight>;
	context.module_widget->addChild(rack::createLightCentered<LightT>(ctr_pos, context.module, indices.light_idx));
}
} // namespace MetaModule::VCVImplementation::Widget
