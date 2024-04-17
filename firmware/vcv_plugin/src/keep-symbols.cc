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
#include <random>
#include <unordered_map>

extern "C" __attribute__((optimize("-O0"))) void _empty_func_stub() {
}

extern "C" __attribute__((optimize("-O0"))) float roundevenf(float x) {
	return roundf(x);
}

namespace std
{
random_device::result_type random_device::_M_getval() {
	return rack::random::get<random_device::result_type>();
}

void random_device::_M_init(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>> const &) {
}
} // namespace std

extern "C" _Complex float csqrtf(_Complex float x) {
	return __builtin_csqrtf(x);
}

void __attribute__((optimize("-O0"))) keep_symbols() {
	auto keep = [&](auto *func) {
		return func;
	};

	(void)keep(strlen);
	(void)keep(malloc);
	(void)keep(calloc);
	(void)keep(free);
	(void)keep(puts);
	(void)keep(std::__throw_bad_function_call);

	// provides std::_Sp_make_shared_tag::_S_eq(std::type_info const&)
	// aka: _ZNSt19_Sp_make_shared_tag5_S_eqERKSt9type_info
	auto f = std::make_shared<float>(1.f);
	auto f2 = std::make_shared<float>(1.5f);
	if (f != f2)
		f = f2;

	// provides _Znaj: operator new[](unsigned int)
	auto ar = new int[10];

	// provides _ZdaPv: operator delete[](void*)
	delete[] ar;

	auto a = new int;
	// provides: _ZdlPv: operator delete(void*)
	delete a;

	std::string x = "A very long String, longer than SSO could optimize without dynamic memory allocation";

	std::unordered_map<std::string, std::string> umap;
	umap[x] = "This string resolves Symbol in plugin not found "
			  "_ZNKSt8__detail20_Prime_rehash_policy14_M_need_rehashEjjj, by being very long";

	// provide __aeabi_f2uzl and __aeabi_f2lz
	float xx = 1.1f;
	auto yy = static_cast<unsigned long long>(xx);
	(void)yy;
	auto zz = static_cast<long long>(xx);
	(void)zz;

	// provides: __mulsc3 and __divsc3
	volatile float _Complex xfa{1};
	volatile float _Complex xfb{2};
	xfa = xfa * xfb;
	xfb = xfb / xfa;
	(void)xfa;
	(void)xfb;

	// provides: __muldc3 and __divdc3
	volatile double _Complex xfc{1};
	volatile double _Complex xfd{2};
	xfc = xfc * xfd;
	xfd = xfd / xfc;
	(void)xfd;
	(void)xfc;

	// provides vtable for Quantity
	rack::Quantity q;
}
