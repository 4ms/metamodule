#pragma once
#include "elements.hh"
#include "rack.hpp"

namespace MetaModule
{

struct VCVWidgetCreator {
	VCVWidgetCreator(rack::ModuleWidget *module_widget, rack::Module *module)
		: module{module}
		, module_widget{module_widget} {
	}

	template<typename T>
	void createWidget(T element){};
	template<>
	void createWidget<Slider25mmVert>(Slider25mmVert element);
	template<>
	void createWidget<Knob9mm>(Knob9mm element);
	template<>
	void createWidget<JackOutput>(JackOutput element);
	template<>
	void createWidget<JackInput>(JackInput element);
	template<>
	void createWidget<Davies1900hWhiteKnob>(Davies1900hWhiteKnob element);
	template<>
	void createWidget<Davies1900hRedKnob>(Davies1900hRedKnob element);
	template<>
	void createWidget<BefacoInputPort>(BefacoInputPort element);
	template<>
	void createWidget<BefacoOutputPort>(BefacoOutputPort element);
	template<>
	void createWidget<MediumLight<RedGreenBlueLight>>(MediumLight<RedGreenBlueLight> element);

private:
	[[maybe_unused]] rack::Module *module;
	[[maybe_unused]] rack::ModuleWidget *module_widget;
};

} // namespace MetaModule
