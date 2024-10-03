#include "app/ModuleLightWidget.hpp"
#include "app/ModuleWidget.hpp"
#include "app/SvgSlider.hpp"
#include "app/SvgSwitch.hpp"
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

#include "CoreModules/moduleFactory.hh"

namespace MetaModule
{
bool register_module(std::string_view brand_name,
					 std::string_view typeslug,
					 MetaModule::ModuleFactory::CreateModuleFunc funcCreate,
					 MetaModule::ModuleInfoView const &info,
					 std::string_view faceplate_filename);
}

extern "C" __attribute__((optimize("-O0"))) void _empty_func_stub() {
}

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

	{
		log1pl(1.);
		expm1l(1.);
	}

	volatile const auto addr = &MetaModule::register_module;

	// provides vtable for Quantity
	rack::Quantity q;

	//`typeinfo for __cxxabiv1::__forced_unwind`
	// try {
	// 	char *x = reinterpret_cast<char *>(0xD0000000);
	// 	std::stoi(x, nullptr);

	// } catch (__cxxabiv1::__forced_unwind &) {
	// 	printf("fail\n");
	// }
}
