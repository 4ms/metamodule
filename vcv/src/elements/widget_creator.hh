#pragma once
#include "elements.hh"
#include "elements/4ms_widgets.hh"
#include "elements/befaco_widgets.hh"
#include "rack.hpp"

namespace MetaModule
{

struct VCVWidgetCreator {
	unsigned num_lights = 0;

	VCVWidgetCreator(rack::ModuleWidget *module_widget, rack::Module *module)
		: module{module}
		, module_widget{module_widget} {
	}

	// Default: do nothing
	void create(BaseElement) {
	}

	// 4ms widgets

	// Units are in center positions in mm for 4ms widgets, but VCV uses 75px/in coordinates
	static constexpr float Fix4msScaling = 75.f / 25.4f;

	void create(DaviesLargeKnob el) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		module_widget->addParam(rack::createParamCentered<DaviesLarge4ms>(ctr_pos, module, el.idx));
	}

	void create(Davies1900hBlackKnob el) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		module_widget->addParam(rack::createParamCentered<Davies1900hBlackKnob4ms>(ctr_pos, module, el.idx));
	}

	void create(Knob9mm el) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		module_widget->addParam(rack::createParamCentered<Small9mmKnob>(ctr_pos, module, el.idx));
	}

	void create(Slider25mmVert el) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		module_widget->addParam(
			rack::createParamCentered<FourmsLightSlider<rack::WhiteLight>>(ctr_pos, module, el.idx));
	}

	void create(Slider25mmHoriz el) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		module_widget->addParam(
			rack::createParamCentered<FourmsLightSliderHorizontal<rack::WhiteLight>>(ctr_pos, module, el.idx));
	}

	void create(Toggle2pos el) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		module_widget->addParam(rack::createParamCentered<SubMiniToggle2pos>(ctr_pos, module, el.idx));
	}

	void create(Toggle3pos el) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		module_widget->addParam(rack::createParamCentered<SubMiniToggle3pos>(ctr_pos, module, el.idx));
	}

	void create(LatchingButtonMonoLight el) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		module_widget->addParam(rack::createParamCentered<LatchingSwitch<rack::LEDBezel>>(ctr_pos, module, el.idx));
		module_widget->addChild(
			rack::createLightCentered<rack::LEDBezelLight<rack::YellowLight>>(ctr_pos, module, num_lights));
		num_lights += 1;
	}

	void create(MomentaryButtonRGB el) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		module_widget->addParam(
			rack::createParamCentered<rack::MomentarySwitch<rack::LEDBezel>>(ctr_pos, module, el.idx));
		module_widget->addChild(
			rack::createLightCentered<rack::LEDBezelLight<rack::RedGreenBlueLight>>(ctr_pos, module, num_lights));
		num_lights += 3;
	}

	void create(Encoder el) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		module_widget->addParam(rack::createParamCentered<Davies1900hBlackKnobUnlined4ms>(ctr_pos, module, el.idx));
	}

	void create(SmallEncoder el) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		module_widget->addParam(rack::createParamCentered<Small9mmUnlinedKnob>(ctr_pos, module, el.idx));
	}

	// TODO: does this look OK?
	void create(LEDEncoder el) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		module_widget->addParam(rack::createParamCentered<Davies1900hBlackKnobUnlined4ms>(ctr_pos, module, el.idx));
		module_widget->addChild(
			rack::createLightCentered<rack::LEDBezelLight<rack::RedGreenBlueLight>>(ctr_pos, module, num_lights));
		num_lights += 3;
	}
	// TODO: does this look OK?
	void create(SmallLEDEncoder el) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		module_widget->addParam(rack::createParamCentered<Small9mmUnlinedKnob>(ctr_pos, module, el.idx));
		module_widget->addChild(
			rack::createLightCentered<rack::LEDBezelLight<rack::RedGreenBlueLight>>(ctr_pos, module, num_lights));
		num_lights += 3;
	}

	void create(JackOutput el) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		module_widget->addOutput(rack::createOutputCentered<rack::PJ301MPort>(ctr_pos, module, el.idx));
	}

	void create(JackInput el) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		module_widget->addInput(rack::createInputCentered<rack::PJ301MPort>(ctr_pos, module, el.idx));
	}

	void create(RedBlueLight el) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		// FIXME: create our own Red/Blue light, VCV only has Red/Green
		module_widget->addChild(
			rack::createLightCentered<rack::LEDBezelLight<rack::GreenRedLight>>(ctr_pos, module, num_lights));
		num_lights += 2;
	}

	void create(OrangeLight el) {
		auto ctr_pos = rack::Vec(el.x_mm, el.y_mm).mult(Fix4msScaling);
		// FIXME: create our own Orange light
		module_widget->addChild(
			rack::createLightCentered<rack::LEDBezelLight<rack::YellowLight>>(ctr_pos, module, num_lights));
		num_lights += 1;
	}

	// Befaco widgets

	void create(Davies1900hWhiteKnob el) {
		auto corner_pos = rack::Vec(el.x_mm, el.y_mm);
		module_widget->addParam(rack::createParam<rack::Davies1900hWhiteKnob>(corner_pos, module, el.idx));
	}

	void create(Davies1900hRedKnob el) {
		auto corner_pos = rack::Vec(el.x_mm, el.y_mm);
		module_widget->addParam(rack::createParam<rack::Davies1900hRedKnob>(corner_pos, module, el.idx));
	}

	void create(BefacoTinyKnobWhite el) {
		module_widget->addParam(
			rack::createParam<Befaco::BefacoTinyKnobWhite>(rack::Vec(el.x_mm, el.y_mm), module, el.idx));
	}

	void create(BefacoTinyKnobRed el) {
		module_widget->addParam(
			rack::createParam<Befaco::BefacoTinyKnobRed>(rack::Vec(el.x_mm, el.y_mm), module, el.idx));
	}

	void create(BefacoTinyKnobDarkGrey el) {
		module_widget->addParam(
			rack::createParam<Befaco::BefacoTinyKnobDarkGrey>(rack::Vec(el.x_mm, el.y_mm), module, el.idx));
	}

	void create(BefacoTinyKnobLightGrey el) {
		module_widget->addParam(
			rack::createParam<Befaco::BefacoTinyKnobLightGrey>(rack::Vec(el.x_mm, el.y_mm), module, el.idx));
	}

	void create(BefacoTinyKnobBlack el) {
		module_widget->addParam(
			rack::createParam<Befaco::BefacoTinyKnobBlack>(rack::Vec(el.x_mm, el.y_mm), module, el.idx));
	}

	void create(Davies1900hLargeGreyKnob el) {
		module_widget->addParam(
			rack::createParam<Befaco::Davies1900hLargeGreyKnob>(rack::Vec(el.x_mm, el.y_mm), module, el.idx));
	}

	void create(Davies1900hLightGreyKnob el) {
		module_widget->addParam(
			rack::createParam<Befaco::Davies1900hLightGreyKnob>(rack::Vec(el.x_mm, el.y_mm), module, el.idx));
	}

	void create(Davies1900hDarkGreyKnob el) {
		module_widget->addParam(
			rack::createParam<Befaco::Davies1900hDarkGreyKnob>(rack::Vec(el.x_mm, el.y_mm), module, el.idx));
	}

	void create(CKSSNarrow el) {
		module_widget->addParam(rack::createParam<Befaco::CKSSNarrow>(rack::Vec(el.x_mm, el.y_mm), module, el.idx));
	}

	void create(Crossfader el) {
		module_widget->addParam(rack::createParam<Befaco::Crossfader>(rack::Vec(el.x_mm, el.y_mm), module, el.idx));
	}

	void create(BefacoSwitchHorizontal el) {
		module_widget->addParam(
			rack::createParam<Befaco::BefacoSwitchHorizontal>(rack::Vec(el.x_mm, el.y_mm), module, el.idx));
	}

	void create(CKSSHoriz2 el) {
		module_widget->addParam(rack::createParam<Befaco::CKSSHoriz2>(rack::Vec(el.x_mm, el.y_mm), module, el.idx));
	}

	void create(CKSSVert7 el) {
		module_widget->addParam(rack::createParam<Befaco::CKSSVert7>(rack::Vec(el.x_mm, el.y_mm), module, el.idx));
	}

	void create(CKSSHoriz4 el) {
		module_widget->addParam(rack::createParam<Befaco::CKSSHoriz4>(rack::Vec(el.x_mm, el.y_mm), module, el.idx));
	}

	void create(CKSSNarrow3 el) {
		module_widget->addParam(rack::createParam<Befaco::CKSSNarrow3>(rack::Vec(el.x_mm, el.y_mm), module, el.idx));
	}

	void create(Davies1900hLargeLightGreyKnob el) {
		module_widget->addParam(
			rack::createParam<Befaco::Davies1900hLargeLightGreyKnob>(rack::Vec(el.x_mm, el.y_mm), module, el.idx));
	}

	void create(BefacoSlidePotSmall el) {
		module_widget->addParam(
			rack::createParam<Befaco::BefacoSlidePotSmall>(rack::Vec(el.x_mm, el.y_mm), module, el.idx));
	}

	static const inline auto BefacoJackOffsetFix = rack::Vec{-10, -10};

	void create(BefacoInputPort el) {
		module_widget->addInput(rack::createInput<Befaco::BananutBlack>(
			rack::Vec(el.x_mm, el.y_mm).plus(BefacoJackOffsetFix), module, el.idx));
	}

	void create(BefacoOutputPort el) {
		module_widget->addOutput(rack::createOutput<Befaco::BananutRed>(
			rack::Vec(el.x_mm, el.y_mm).plus(BefacoJackOffsetFix), module, el.idx));
	}

private:
	[[maybe_unused]] rack::Module *module;
	[[maybe_unused]] rack::ModuleWidget *module_widget;
};

} // namespace MetaModule
