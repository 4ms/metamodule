#include "app/ModuleLightWidget.hpp"
#include "app/ModuleWidget.hpp"
#include "app/SvgSlider.hpp"
#include "app/SvgSwitch.hpp"
#include "metamodule/make_element.hh"
#include "random.hpp"
#include "widget/TransformWidget.hpp"

#include "history.hpp"
#include "jansson.h"
#include "string.hpp"
#include <cmath>
#include <cstring>
#include <memory>

extern "C" __attribute__((optimize("-O0"))) void _empty_func_stub() {
}

void __attribute__((optimize("-O0"))) keep_symbols() {
	// Force these symbols from libc and other libs
	// TODO: how to do this otherwise?
	// We can't link the plugin to libc unless we compile a libc with it, since the arm-none-eabi libc
	// was not compiled with -fPIC
	// - Linker KEEP()?
	// - build libc with the plugin, maybe musl libc?
	// - build plugin with json library

	auto keep = [&](auto *func) {
		return func;
	};

	// Can't use keep() with clang because these are template functions:
	(void)exp(1.f);
	(void)expf(1.f);
	(void)fmod(1.f, 1.f);
	(void)sinf(1.f);
	(void)tanf(1.f);
	(void)tanh(1.f);
	(void)sqrt(1.f);
	(void)sqrtf(1.f);
	(void)powf(1.f, 1.f);
	(void)pow(1., 1.);
	(void)sin(1.f);
	(void)log(1.f);
	(void)log10(1.f);
	(void)log10f(1.f);
	(void)logf(1.f);
	(void)log2f(1.f);
	(void)cos(1.f);
	(void)cosf(1.f);
	(void)ceil(1.f);
	(void)ceilf(1.f);
	(void)floor(1.f);
	(void)floorf(1.f);

	(void)keep(json_object_set_new);
	(void)keep(json_array_get);
	(void)keep(json_array_insert_new);
	(void)keep(json_number_value);
	(void)keep(json_dumps);

	(void)keep(strlen);
	(void)keep(malloc);
	(void)keep(free);
	(void)keep(puts);

	(void)keep(rack::random::local);
	(void)keep(rack::string::f);

	rack::history::ModuleAdd{}.setModule({});
	rack::history::State{}.push({});
	rack::widget::TransformWidget{}.translate({});
	rack::widget::TransformWidget{}.rotate({});
	rack::widget::TransformWidget{}.rotate({}, {});
	rack::widget::TransformWidget{}.scale({});
	rack::widget::Widget{}.removeChild({});
	rack::widget::Widget{}.addChildBottom({});
	rack::widget::Widget{}.addChildBelow({}, {});
	rack::app::SvgSwitch{}.addFrame(std::make_shared<rack::window::Svg>(""));
	rack::app::SvgSlider{}.setHandleSvg({});
	rack::app::SvgSlider{}.setBackgroundSvg({});
	rack::app::SvgSlider{}.setHandlePos({}, {});
	rack::app::ModuleWidget{}.addChild(new rack::app::ModuleLightWidget);

	rack::app::SvgSwitch sw;
	rack::app::SvgPort port;
	rack::app::SvgKnob knob;
	rack::app::SvgSlider slider;
	rack::app::SvgScrew screw;
	rack::widget::SvgWidget wid;
	rack::componentlibrary::Rogan rogan;

	MetaModule::make_element_output(&port, MetaModule::BaseElement{});
	MetaModule::make_element_input(&port, MetaModule::BaseElement{});
	MetaModule::make_element(&knob, MetaModule::BaseElement{});
	MetaModule::make_element(&slider, MetaModule::BaseElement{});
	MetaModule::make_element_slideswitch(&slider, MetaModule::BaseElement{});
	MetaModule::make_element(&rogan, MetaModule::BaseElement{});
	MetaModule::make_element(&sw, MetaModule::BaseElement{});
	MetaModule::make_element(&screw, MetaModule::BaseElement{});
	MetaModule::make_element(&wid, MetaModule::BaseElement{});

	auto ar = new int[10];
	delete[] ar;

	volatile auto alloc = std::allocator<char>{}; //seems to do nothing
	(void)alloc;

	//stdlib
}
