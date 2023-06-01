#include "widget_creator.hh"
#include "components.h"
#include "elements/befaco_widgets.hh"
#include "mapping/mappable_jack.hh"
#include "mapping/mappable_knob.hh"
#include "rack.hpp"

#include <cstdio>

namespace MetaModule
{

// TODO: Add Mappable wrappers
// 4ms widgets

template<>
void VCVWidgetCreator::createWidget<Knob9mm>(Knob9mm element) {
	using WidgetT = Small9mmKnob;
	auto ctr_pos = rack::Vec(element.x_mm, element.y_mm);

	auto *kn = rack::createParamCentered<WidgetT>(ctr_pos, module, element.idx);
	module_widget->addChild(new MappableKnobRing{*kn, 10});
	module_widget->addParam(kn);
}

template<>
void VCVWidgetCreator::createWidget<Slider25mmVert>(Slider25mmVert element) {
	using WidgetT = MappableKnob<FourmsLightSlider<rack::WhiteLight>>;
	auto ctr_pos = rack::Vec(element.x_mm, element.y_mm);

	auto *kn = rack::createParamCentered<WidgetT>(ctr_pos, module, element.idx);
	module_widget->addChild(new MappableSliderRing{*kn, 20, 40});
	module_widget->addParam(kn);
}

template<>
void VCVWidgetCreator::createWidget<Slider25mmHoriz>(Slider25mmHoriz element) {
	using WidgetT = MappableKnob<FourmsLightSliderHorizontal<rack::WhiteLight>>;
	auto ctr_pos = rack::Vec(element.x_mm, element.y_mm);

	auto *kn = rack::createParamCentered<WidgetT>(ctr_pos, module, element.idx);
	module_widget->addChild(new MappableSliderRing{*kn, 40, 20});
	module_widget->addParam(kn);
}

// Befaco widgets
template<>
void VCVWidgetCreator::createWidget<Davies1900hWhiteKnob>(Davies1900hWhiteKnob element) {
	module_widget->addParam(
		rack::createParam<rack::Davies1900hWhiteKnob>(rack::Vec(element.x_mm, element.y_mm), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<MediumLight<RedGreenBlueLight>>(MediumLight<RedGreenBlueLight> element) {
}

template<>
void VCVWidgetCreator::createWidget<Davies1900hRedKnob>(Davies1900hRedKnob element) {
	module_widget->addParam(
		rack::createParam<rack::Davies1900hRedKnob>(rack::Vec(element.x_mm, element.y_mm), module, element.idx));
}

// template<>
// void VCVWidgetCreator::createWidget<BefacoTinyKnobWhite>(BefacoTinyKnobWhite element)
// {
// 	module_widget->addParam(
// 		rack::createParam<Befaco::BefacoTinyKnobWhite>(rack::Vec(element.x_mm, element.y_mm), module, element.idx));
// }

// template<>
// void VCVWidgetCreator::createWidget<BefacoTinyKnobRed>(BefacoTinyKnobRed element)
// {
// 	module_widget->addParam(
// 		rack::createParam<Befaco::BefacoTinyKnobRed>(rack::Vec(element.x_mm, element.y_mm), module, element.idx));
// }

// template<>
// void VCVWidgetCreator::createWidget<BefacoTinyKnobDarkGrey>(BefacoTinyKnobDarkGrey element)
// {
// 	module_widget->addParam(
// 		rack::createParam<Befaco::BefacoTinyKnobDarkGrey>(rack::Vec(element.x_mm, element.y_mm), module, element.idx));
// }

// template<>
// void VCVWidgetCreator::createWidget<BefacoTinyKnobLightGrey>(BefacoTinyKnobLightGrey element)
// {
// 	module_widget->addParam(
// 		rack::createParam<Befaco::BefacoTinyKnobLightGrey>(rack::Vec(element.x_mm, element.y_mm), module, element.idx));
// }

// template<>
// void VCVWidgetCreator::createWidget<BefacoTinyKnobBlack>(BefacoTinyKnobBlack element)
// {
// 	module_widget->addParam(
// 		rack::createParam<Befaco::BefacoTinyKnobBlack>(rack::Vec(element.x_mm, element.y_mm), module, element.idx));
// }

// template<>
// void VCVWidgetCreator::createWidget<Davies1900hLargeGreyKnob>(Davies1900hLargeGreyKnob element)
// {
// 	module_widget->addParam(rack::createParam<Befaco::Davies1900hLargeGreyKnob>(
// 		rack::Vec(element.x_mm, element.y_mm), module, element.idx));
// }

// template<>
// void VCVWidgetCreator::createWidget<Davies1900hLightGreyKnob>(Davies1900hLightGreyKnob element)
// {
// 	module_widget->addParam(rack::createParam<Befaco::Davies1900hLightGreyKnob>(
// 		rack::Vec(element.x_mm, element.y_mm), module, element.idx));
// }

// template<>
// void VCVWidgetCreator::createWidget<Davies1900hDarkGreyKnob>(Davies1900hDarkGreyKnob element)
// {
// 	module_widget->addParam(
// 		rack::createParam<Befaco::Davies1900hDarkGreyKnob>(rack::Vec(element.x_mm, element.y_mm), module, element.idx));
// }

// template<>
// void VCVWidgetCreator::createWidget<CKSSNarrow>(CKSSNarrow element)
// {
// 	module_widget->addParam(
// 		rack::createParam<Befaco::CKSSNarrow>(rack::Vec(element.x_mm, element.y_mm), module, element.idx));
// }

// template<>
// void VCVWidgetCreator::createWidget<Crossfader>(Crossfader element)
// {
// 	module_widget->addParam(
// 		rack::createParam<Befaco::Crossfader>(rack::Vec(element.x_mm, element.y_mm), module, element.idx));
// }

// template<>
// void VCVWidgetCreator::createWidget<BefacoSwitchHorizontal>(BefacoSwitchHorizontal element)
// {
// 	module_widget->addParam(
// 		rack::createParam<Befaco::BefacoSwitchHorizontal>(rack::Vec(element.x_mm, element.y_mm), module, element.idx));
// }

// template<>
// void VCVWidgetCreator::createWidget<CKSSHoriz2>(CKSSHoriz2 element)
// {
// 	module_widget->addParam(
// 		rack::createParam<Befaco::CKSSHoriz2>(rack::Vec(element.x_mm, element.y_mm), module, element.idx));
// }

// template<>
// void VCVWidgetCreator::createWidget<CKSSVert7>(CKSSVert7 element)
// {
// 	module_widget->addParam(
// 		rack::createParam<Befaco::CKSSVert7>(rack::Vec(element.x_mm, element.y_mm), module, element.idx));
// }

// template<>
// void VCVWidgetCreator::createWidget<CKSSHoriz4>(CKSSHoriz4 element)
// {
// 	module_widget->addParam(
// 		rack::createParam<Befaco::CKSSHoriz4>(rack::Vec(element.x_mm, element.y_mm), module, element.idx));
// }

// template<>
// void VCVWidgetCreator::createWidget<CKSSNarrow3>(CKSSNarrow3 element)
// {
// 	module_widget->addParam(
// 		rack::createParam<Befaco::CKSSNarrow3>(rack::Vec(element.x_mm, element.y_mm), module, element.idx));
// }

// template<>
// void VCVWidgetCreator::createWidget<Davies1900hLargeLightGreyKnob>(Davies1900hLargeLightGreyKnob element)
// {
// 	module_widget->addParam(rack::createParam<Befaco::Davies1900hLargeLightGreyKnob>(
// 		rack::Vec(element.x_mm, element.y_mm), module, element.idx));
// }

// template<>
// void VCVWidgetCreator::createWidget<BefacoSlidePotSmall>(BefacoSlidePotSmall element)
// {
// 	module_widget->addParam(
// 		rack::createParam<Befaco::BefacoSlidePotSmall>(rack::Vec(element.x_mm, element.y_mm), module, element.idx));
// }

// // TODO: mm2px? and how to indicate if x_mm, y_mm are center or corner?
template<>
void VCVWidgetCreator::createWidget<JackOutput>(JackOutput element) {
	module_widget->addOutput(rack::createOutputCentered<MappableOutputJack<rack::PJ301MPort>>(
		rack::Vec(element.x_mm, element.y_mm), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<JackInput>(JackInput element) {
	module_widget->addInput(rack::createInput<MappableInputJack<rack::PJ301MPort>>(
		rack::Vec(element.x_mm, element.y_mm), module, element.idx));
}

static const auto BefacoJackOffsetFix = rack::Vec{-10, -10};

template<>
void VCVWidgetCreator::createWidget<BefacoInputPort>(BefacoInputPort element) {
	module_widget->addInput(rack::createInput<MappableInputJack<Befaco::BananutBlack>>(
		rack::Vec(element.x_mm, element.y_mm).plus(BefacoJackOffsetFix), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<BefacoOutputPort>(BefacoOutputPort element) {
	module_widget->addOutput(rack::createOutput<MappableOutputJack<Befaco::BananutRed>>(
		rack::Vec(element.x_mm, element.y_mm).plus(BefacoJackOffsetFix), module, element.idx));
}

} // namespace MetaModule
