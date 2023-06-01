#pragma once
#include "elements.hh"
#include "rack.hpp"

namespace MetaModule
{

struct VCVCreator {
	VCVCreator(rack::ModuleWidget *module_widget, rack::Module *module)
		: module{module}
		, module_widget{module_widget}
	{}

	template<typename T>
	void createWidget(T element){
		// by default, do nothing
	};

	unsigned num_params = 0;
	unsigned num_inputs = 0;
	unsigned num_outputs = 0;
	unsigned num_lights = 0;

private:
	rack::Module *module;
	rack::ModuleWidget *module_widget;
};

} // namespace MetaModule
