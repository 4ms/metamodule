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
	void createWidget(T element) {
		printf("unknown\n");
	};

	template<>
	void createWidget<Slider25mmVert>(Slider25mmVert element);

	template<>
	void createWidget<Knob9mm>(Knob9mm element);

private:
	[[maybe_unused]] rack::Module *module;
	[[maybe_unused]] rack::ModuleWidget *module_widget;
};

} // namespace MetaModule
