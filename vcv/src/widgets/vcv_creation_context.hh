#pragma once
#include "rack.hpp"

struct WidgetContext_t
{
	rack::ModuleWidget* module_widget;
	rack::Module* module;
	unsigned num_lights = 0;
};

struct ModuleContext_t
{
	rack::Module* module;
	unsigned lights = 0;
};