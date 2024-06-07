#include "app/ModuleLightWidget.hpp"
#include "app/ModuleWidget.hpp"
#include "app/SvgSlider.hpp"
#include "app/SvgSwitch.hpp"
#include "make_element.hh"
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

// Define std::random so plugins can use it
// namespace std
// {
// random_device::result_type random_device::_M_getval() {
// 	return rack::random::get<random_device::result_type>();
// }

// void random_device::_M_init(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>> const &) {
// }
// } // namespace std

extern "C" int gettimeofday(struct timeval *tp, struct timezone *tzp);
extern "C" void __cxa_pure_virtual();
extern "C" void *memalign(size_t align, size_t nbytes);

void __attribute__((optimize("-O0"))) keep_symbols() {
	{
		auto x = &calloc;
		(void)x;
	}

	{
		auto x = &memalign;
		(void)x;
	}

	{
		auto x = &__cxa_pure_virtual;
		(void)x;
	}

	{
		auto x = &gettimeofday;
		(void)x;
	}

	// provides vtable for Quantity
	rack::Quantity q;
}
