#include "app/ModuleLightWidget.hpp"
#include "app/ModuleWidget.hpp"
#include "app/SvgSlider.hpp"
#include "app/SvgSwitch.hpp"
#include "metamodule/make_element.hh"
#include "random.hpp"
#include "widget/TransformWidget.hpp"

#include "history.hpp"
#include "jansson.h"
#include "pffft.h"
#include "string.hpp"
#include <cmath>
#include <cstring>
#include <memory>

extern "C" __attribute__((optimize("-O0"))) void _empty_func_stub() {
}

extern "C" __attribute__((optimize("-O0"))) float roundevenf(float x) {
	return roundf(x);
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
	(void)acos(1.f);
	(void)acosh(1.f);
	(void)acoshf(1.f);
	(void)acosf(1.f);
	(void)asin(1.f);
	(void)asinh(1.f);
	(void)asinhf(1.f);
	(void)asinf(1.f);
	(void)atan2(1.f, 2.f);
	(void)atan2f(1.f, 2.f);
	(void)ceil(1.f);
	(void)ceilf(1.f);
	(void)cos(1.f);
	(void)cosf(1.f);
	(void)cosh(1.f);
	(void)coshf(1.f);
	(void)erf(2.f);
	(void)erfc(2.f);
	(void)gamma(2.f);
	(void)lgamma(2.f);
	(void)remainder(1.f, 2.f);
	(void)exp(1.f);
	(void)exp2(1.f);
	(void)exp2f(1.f);
	(void)expf(1.f);
	(void)floor(1.f);
	(void)floorf(1.f);
	(void)fmax(1.f, 2.f);
	(void)fmaxf(2.f, 2.f);
	(void)fmin(1.f, 2.f);
	(void)fminf(2.f, 2.f);
	(void)fmod(1.f, 1.f);
	(void)fmodf(2.f, 2.f);
	(void)ldexp(1.f, 1.f);
	(void)ldexpf(1.f, 1.f);
	(void)log(1.f);
	(void)log10(1.f);
	(void)log10f(1.f);
	(void)log2(1.f);
	(void)log2f(1.f);
	(void)logf(1.f);
	(void)nextafterf(1.f, 2.f);
	(void)pow(1., 1.);
	(void)powf(1.f, 1.f);
	(void)round(1.f);
	(void)roundf(1.f);
	(void)roundevenf(1.f);
	(void)sin(1.f);
	(void)sinf(1.f);
	(void)sinh(1.f);
	(void)sinhf(1.f);
	(void)sqrt(1.f);
	(void)sqrtf(1.f);
	(void)tan(1.f);
	(void)tanf(1.f);
	(void)tanh(1.f);
	(void)tanhf(1.f);
	(void)tolower('a');
	(void)trunc(2.f);
	(void)truncf(2.f);

	(void)keep(strlen);
	(void)keep(malloc);
	(void)keep(free);
	(void)keep(puts);

	// provides std::_Sp_make_shared_tag::_S_eq(std::type_info const&)
	// aka: _ZNSt19_Sp_make_shared_tag5_S_eqERKSt9type_info
	auto f = std::make_shared<float>(1.f);

	// (void)keep(json_object_set_new);
	// (void)keep(json_array_get);
	// (void)keep(json_array_insert_new);
	// (void)keep(json_number_value);
	// (void)keep(json_dumps);

	// (void)keep(rack::random::local);
	// (void)keep(rack::string::f);

	// rack::history::ModuleAdd{}.setModule({});
	// rack::history::State{}.push({});
	// rack::widget::TransformWidget{}.translate({});
	// rack::widget::TransformWidget{}.rotate({});
	// rack::widget::TransformWidget{}.rotate({}, {});
	// rack::widget::TransformWidget{}.scale({});
	// rack::widget::Widget{}.removeChild({});
	// rack::widget::Widget{}.addChildBottom({});
	// rack::widget::Widget{}.addChildBelow({}, {});
	// rack::app::SvgSwitch{}.addFrame(std::make_shared<rack::window::Svg>(""));
	// rack::app::SvgSlider{}.setHandleSvg({});
	// rack::app::SvgSlider{}.setBackgroundSvg({});
	// rack::app::SvgSlider{}.setHandlePos({}, {});
	// rack::app::ModuleWidget{}.addChild(new rack::app::ModuleLightWidget);

	// rack::app::SvgSwitch sw;
	// rack::app::SvgPort port;
	// rack::app::SvgKnob knob;
	// rack::app::SvgSlider slider;
	// rack::app::SvgScrew screw;
	// rack::widget::SvgWidget wid;
	// rack::componentlibrary::Rogan rogan;

	// MetaModule::make_element_output(&port, MetaModule::BaseElement{});
	// MetaModule::make_element_input(&port, MetaModule::BaseElement{});
	// MetaModule::make_element(&knob, MetaModule::BaseElement{});
	// MetaModule::make_element(&slider, MetaModule::BaseElement{});
	// MetaModule::make_element_slideswitch(&slider, MetaModule::BaseElement{});
	// MetaModule::make_element(&rogan, MetaModule::BaseElement{});
	// MetaModule::make_element(&sw, MetaModule::BaseElement{});
	// MetaModule::make_element(&screw, MetaModule::BaseElement{});
	// MetaModule::make_element(&wid, MetaModule::BaseElement{});

	// (void)keep(pffft_new_setup);
	// (void)keep(pffft_destroy_setup);
	// (void)keep(pffft_transform);
	// (void)keep(pffft_transform_ordered);
	// (void)keep(pffft_zreorder);
	// (void)keep(pffft_zconvolve_accumulate);
	// (void)keep(pffft_aligned_free);
	// (void)keep(pffft_aligned_malloc);
	// (void)keep(pffft_simd_size);

	// rack::settings::preferDarkPanels = false;

	// auto ar = new int[10];
	// delete[] ar;

	// volatile auto alloc = std::allocator<char>{}; //seems to do nothing
	// (void)alloc;

	//stdlib
}
