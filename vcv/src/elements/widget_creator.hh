#pragma once
#include "elements.hh"
#include "elements/4ms_widgets.hh"
#include "elements/befaco_widgets.hh"
#include "rack.hpp"

namespace MetaModule
{

struct VCVWidgetCreator {
	VCVWidgetCreator(rack::ModuleWidget *module_widget, rack::Module *module)
		: module{module}
		, module_widget{module_widget} {
	}

	// Default: do nothing
	void create(BaseElement) {
	}

	// 4ms widgets

	void create(Knob9mm el) {
		module_widget->addParam(rack::createParamCentered<Small9mmKnob>(rack::Vec(el.x_mm, el.y_mm), module, el.idx));
	}

	void create(Slider25mmVert el) {
		module_widget->addParam(rack::createParamCentered<FourmsLightSlider<rack::WhiteLight>>(
			rack::Vec(el.x_mm, el.y_mm), module, el.idx));
	}

	void create(Slider25mmHoriz el) {
		module_widget->addParam(rack::createParamCentered<FourmsLightSliderHorizontal<rack::WhiteLight>>(
			rack::Vec(el.x_mm, el.y_mm), module, el.idx));
	}

	void create(JackOutput el) {
		module_widget->addOutput(rack::createOutput<rack::PJ301MPort>(rack::Vec(el.x_mm, el.y_mm), module, el.idx));
	}
	void create(JackInput el) {
		module_widget->addInput(rack::createInput<rack::PJ301MPort>(rack::Vec(el.x_mm, el.y_mm), module, el.idx));
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
