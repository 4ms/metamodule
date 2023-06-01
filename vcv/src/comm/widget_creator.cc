#include "widget_creator.hh"
#include "elements/befaco_widgets.hh"
#include "mapping/mappable_jack.hh"
#include "rack.hpp"

namespace MetaModule
{

// TODO: Add Mappable wrappers

template<>
void VCVWidgetCreator::createWidget<Davies1900hWhiteKnob>(Davies1900hWhiteKnob element) {
	module_widget->addParam(
		rack::createParam<rack::Davies1900hWhiteKnob>(rack::Vec(element.posx, element.posy), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<Davies1900hBlackKnob>(Davies1900hBlackKnob element) {
	module_widget->addParam(
		rack::createParam<rack::Davies1900hBlackKnob>(rack::Vec(element.posx, element.posy), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<Davies1900hRedKnob>(Davies1900hRedKnob element) {
	module_widget->addParam(
		rack::createParam<rack::Davies1900hRedKnob>(rack::Vec(element.posx, element.posy), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<BefacoInputPort>(BefacoInputPort element) {
	module_widget->addInput(
		rack::createParam<Befaco::BefacoInputPort>(rack::Vec(element.posx, element.posy), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<BefacoOutputPort>(BefacoOutputPort element) {
	module_widget->addOutput(
		rack::createParam<Befaco::BefacoOutputPort>(rack::Vec(element.posx, element.posy), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<BefacoTinyKnobWhite>(BefacoTinyKnobWhite element) {
	module_widget->addParam(
		rack::createParam<Befaco::BefacoTinyKnobWhite>(rack::Vec(element.posx, element.posy), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<BefacoTinyKnobRed>(BefacoTinyKnobRed element) {
	module_widget->addParam(
		rack::createParam<Befaco::BefacoTinyKnobRed>(rack::Vec(element.posx, element.posy), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<BefacoTinyKnobDarkGrey>(BefacoTinyKnobDarkGrey element) {
	module_widget->addParam(
		rack::createParam<Befaco::BefacoTinyKnobDarkGrey>(rack::Vec(element.posx, element.posy), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<BefacoTinyKnobLightGrey>(BefacoTinyKnobLightGrey element) {
	module_widget->addParam(
		rack::createParam<Befaco::BefacoTinyKnobLightGrey>(rack::Vec(element.posx, element.posy), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<BefacoTinyKnobBlack>(BefacoTinyKnobBlack element) {
	module_widget->addParam(
		rack::createParam<Befaco::BefacoTinyKnobBlack>(rack::Vec(element.posx, element.posy), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<Davies1900hLargeGreyKnob>(Davies1900hLargeGreyKnob element) {
	module_widget->addParam(rack::createParam<Befaco::Davies1900hLargeGreyKnob>(
		rack::Vec(element.posx, element.posy), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<Davies1900hLightGreyKnob>(Davies1900hLightGreyKnob element) {
	module_widget->addParam(rack::createParam<Befaco::Davies1900hLightGreyKnob>(
		rack::Vec(element.posx, element.posy), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<Davies1900hDarkGreyKnob>(Davies1900hDarkGreyKnob element) {
	module_widget->addParam(
		rack::createParam<Befaco::Davies1900hDarkGreyKnob>(rack::Vec(element.posx, element.posy), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<CKSSNarrow>(CKSSNarrow element) {
	module_widget->addParam(
		rack::createParam<Befaco::CKSSNarrow>(rack::Vec(element.posx, element.posy), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<Crossfader>(Crossfader element) {
	module_widget->addParam(
		rack::createParam<Befaco::Crossfader>(rack::Vec(element.posx, element.posy), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<BefacoSwitchHorizontal>(BefacoSwitchHorizontal element) {
	module_widget->addParam(
		rack::createParam<Befaco::BefacoSwitchHorizontal>(rack::Vec(element.posx, element.posy), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<CKSSHoriz2>(CKSSHoriz2 element) {
	module_widget->addParam(
		rack::createParam<Befaco::CKSSHoriz2>(rack::Vec(element.posx, element.posy), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<CKSSVert7>(CKSSVert7 element) {
	module_widget->addParam(
		rack::createParam<Befaco::CKSSVert7>(rack::Vec(element.posx, element.posy), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<CKSSHoriz4>(CKSSHoriz4 element) {
	module_widget->addParam(
		rack::createParam<Befaco::CKSSHoriz4>(rack::Vec(element.posx, element.posy), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<CKSSNarrow3>(CKSSNarrow3 element) {
	module_widget->addParam(
		rack::createParam<Befaco::CKSSNarrow3>(rack::Vec(element.posx, element.posy), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<Davies1900hLargeLightGreyKnob>(Davies1900hLargeLightGreyKnob element) {
	module_widget->addParam(rack::createParam<Befaco::Davies1900hLargeLightGreyKnob>(
		rack::Vec(element.posx, element.posy), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<BefacoSlidePotSmall>(BefacoSlidePotSmall element) {
	module_widget->addParam(
		rack::createParam<Befaco::BefacoSlidePotSmall>(rack::Vec(element.posx, element.posy), module, element.idx));
}

// TODO: mm2px? and how to indicate if posx, posy are center or corner?
template<>
void VCVWidgetCreator::createWidget<JackOutput>(JackOutput element) {
	module_widget->addOutput(rack::createParam<MappableOutputJack<rack::PJ301MPort>>(
		rack::Vec(element.posx, element.posy), module, element.idx));
}

template<>
void VCVWidgetCreator::createWidget<JackInput>(JackInput element) {
	module_widget->addInput(rack::createParam<MappableInputJack<rack::PJ301MPort>>(
		rack::Vec(element.posx, element.posy), module, element.idx));
}

} // namespace MetaModule
