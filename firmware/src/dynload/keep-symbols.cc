#include "VCV_adaptor/app/Widget.hh"
#include "VCV_adaptor/random.hpp"
#include "VCV_adaptor/widget/Widget.hh"

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
	(void)sin(1.f);
	(void)log(1.f);
	(void)logf(1.f);
	(void)log2f(1.f);
	(void)cos(1.f);
	(void)cosf(1.f);

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

	auto ar = new int[10];
	delete[] ar;

	volatile auto alloc = std::allocator<char>{}; //seems to do nothing
	(void)alloc;

	//stdlib
}
