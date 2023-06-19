#include "../vcv_widget_context.hh"
#include "4ms_widgets.hh"

namespace MetaModule::VCVImplementation::Widget
{
	// Units are in center positions in mm for 4ms widgets, but VCV uses 75px/in coordinates
	static constexpr float Fix4msScaling = 75.f / 25.4f;

	void do_create(DaviesLargeKnob el, WidgetContext_t& context) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		context.module_widget->addParam(rack::createParamCentered<DaviesLarge4ms>(ctr_pos, context.module, el.idx));
	}

	void do_create(Davies1900hBlackKnob el, WidgetContext_t& context) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		context.module_widget->addParam(rack::createParamCentered<Davies1900hBlackKnob4ms>(ctr_pos, context.module, el.idx));
	}

	void do_create(Knob9mm el, WidgetContext_t& context) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		context.module_widget->addParam(rack::createParamCentered<Small9mmKnob>(ctr_pos, context.module, el.idx));
	}

	void do_create(Slider25mmVert el, WidgetContext_t& context) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		context.module_widget->addParam(
			rack::createParamCentered<FourmsLightSlider<rack::WhiteLight>>(ctr_pos, context.module, el.idx));
	}

	void do_create(Slider25mmHoriz el, WidgetContext_t& context) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		context.module_widget->addParam(
			rack::createParamCentered<FourmsLightSliderHorizontal<rack::WhiteLight>>(ctr_pos, context.module, el.idx));
	}

	void do_create(Toggle2pos el, WidgetContext_t& context) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		context.module_widget->addParam(rack::createParamCentered<SubMiniToggle2pos>(ctr_pos, context.module, el.idx));
	}

	void do_create(Toggle3pos el, WidgetContext_t& context) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		context.module_widget->addParam(rack::createParamCentered<SubMiniToggle3pos>(ctr_pos, context.module, el.idx));
	}

	void do_create(LatchingButtonMonoLight el, WidgetContext_t& context) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		context.module_widget->addParam(rack::createParamCentered<LatchingSwitch<rack::LEDBezel>>(ctr_pos, context.module, el.idx));
		context.module_widget->addChild(
			rack::createLightCentered<rack::LEDBezelLight<rack::YellowLight>>(ctr_pos, context.module, context.num_lights));
		context.num_lights += 1;
	}

	void do_create(MomentaryButtonRGB el, WidgetContext_t& context) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		context.module_widget->addParam(
			rack::createParamCentered<rack::MomentarySwitch<rack::LEDBezel>>(ctr_pos, context.module, el.idx));
		context.module_widget->addChild(
			rack::createLightCentered<rack::LEDBezelLight<rack::RedGreenBlueLight>>(ctr_pos, context.module, context.num_lights));
		context.num_lights += 3;
	}

	void do_create(Encoder el, WidgetContext_t& context) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		context.module_widget->addParam(rack::createParamCentered<Davies1900hBlackKnobUnlined4ms>(ctr_pos, context.module, el.idx));
	}

	void do_create(SmallEncoder el, WidgetContext_t& context) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		context.module_widget->addParam(rack::createParamCentered<Small9mmUnlinedKnob>(ctr_pos, context.module, el.idx));
	}

	// TODO: does this look OK?
	void do_create(LEDEncoder el, WidgetContext_t& context) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		context.module_widget->addParam(rack::createParamCentered<Davies1900hBlackKnobUnlined4ms>(ctr_pos, context.module, el.idx));
		context.module_widget->addChild(
			rack::createLightCentered<rack::LEDBezelLight<rack::RedGreenBlueLight>>(ctr_pos, context.module, context.num_lights));
		context.num_lights += 3;
	}
	// TODO: does this look OK?
	void do_create(SmallLEDEncoder el, WidgetContext_t& context) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		context.module_widget->addParam(rack::createParamCentered<Small9mmUnlinedKnob>(ctr_pos, context.module, el.idx));
		context.module_widget->addChild(
			rack::createLightCentered<rack::LEDBezelLight<rack::RedGreenBlueLight>>(ctr_pos, context.module, context.num_lights));
		context.num_lights += 3;
	}

	void do_create(JackOutput el, WidgetContext_t& context) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		context.module_widget->addOutput(rack::createOutputCentered<rack::PJ301MPort>(ctr_pos, context.module, el.idx));
	}

	void do_create(JackInput el, WidgetContext_t& context) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		context.module_widget->addInput(rack::createInputCentered<rack::PJ301MPort>(ctr_pos, context.module, el.idx));
	}

	void do_create(RedBlueLight el, WidgetContext_t& context) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		// FIXME: create our own Red/Blue light, VCV only has Red/Green
		context.module_widget->addChild(
			rack::createLightCentered<rack::LEDBezelLight<rack::GreenRedLight>>(ctr_pos, context.module, context.num_lights));
		context.num_lights += 2;
	}

	void do_create(OrangeLight el, WidgetContext_t& context) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		// FIXME: create our own Orange light
		context.module_widget->addChild(
			rack::createLightCentered<rack::LEDBezelLight<rack::YellowLight>>(ctr_pos, context.module, context.num_lights));
		context.num_lights += 1;
	}	
}
