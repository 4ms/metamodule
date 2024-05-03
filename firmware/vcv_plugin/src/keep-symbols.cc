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
// #include <sys/unistd.h>

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

extern "C" int getentropy(void *, size_t) {
	return 0;
}

extern "C" int read(int file, char *ptr, int len) {
	return 0;
}
extern "C" void lseek() {
}
extern "C" void fstat() {
}
extern "C" wint_t _uc2jp_l(wint_t c, struct __locale_t *l);
extern "C" int _write(int file, char *ptr, int len);
extern "C" int write(int file, char *ptr, int len) {
	return _write(file, ptr, len);
}

using _Unwind_Ptr = void *;
extern "C" _Unwind_Ptr __gnu_Unwind_Find_exidx(_Unwind_Ptr pc, int *pcount) {
	return nullptr;
}

extern "C" void *_ZGTtnaj(size_t sz) {
	return nullptr;
}
extern "C" void *_ZGTtnaX(size_t sz) {
	return nullptr;
}
extern "C" void _ZGTtdlPv(void *ptr) {
}
extern "C" uint8_t _ITM_RU1(const uint8_t *p) {
	return {};
}
extern "C" uint16_t _ITM_RU2(const uint16_t *p) {
	return {};
}
extern "C" uint32_t _ITM_RU4(const uint32_t *p) {
	return {};
}
extern "C" uint64_t _ITM_RU8(const uint64_t *p) {
	return {};
}
extern "C" void _ITM_memcpyRtWn(void *, const void *, size_t) {
}
extern "C" void _ITM_memcpyRnWt(void *, const void *, size_t) {
}
extern "C" void _ITM_addUserCommitAction(void (*)(void *), uint64_t, void *) {
}

void __attribute__((optimize("-O0"))) keep_symbols() {
	{
		auto x = &_uc2jp_l;
		(void)x;
	}
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
