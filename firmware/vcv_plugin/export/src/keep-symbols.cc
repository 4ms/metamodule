// These must be inluded so the symbols are not dropped by the linker:
// VCV:
#include "app/ModuleLightWidget.hpp"
#include "app/ModuleWidget.hpp"
#include "app/SvgSlider.hpp"
#include "app/SvgSwitch.hpp"
#include "dsp/block_resampler.hh"
#include "dsp/stream_resampler.hh"
#include "graphics/waveform_display.hh"
#include "history.hpp"
#include "random.hpp"
#include "string.hpp"
#include "ui/ChoiceButton.hpp"
#include "ui/List.hpp"
#include "ui/OptionButton.hpp"
#include "widget/TransformWidget.hpp"

#include "CoreModules/async_thread.hh"
#include "dirent.h"
#include "jansson.h"
#include "metamodule-plugin-sdk/core-interface/patch/audio.hh"
#include "metamodule-plugin-sdk/core-interface/patch/patch.hh"
#include "metamodule-plugin-sdk/core-interface/system/memory.hh"
#include "metamodule-plugin-sdk/core-interface/system/random.hh"
#include "metamodule-plugin-sdk/core-interface/system/time.hh"
#include "metamodule-plugin-sdk/core-interface/wav/wav_file_stream.hh"
#include "pffft.h"

#include <cmath>
#include <cstring>
#include <ctime>
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

	{
		auto x = &clock;
		(void)x;
	}

	// provides vtable for Quantity
	rack::Quantity q;
}

void keep_async() {
	MetaModule::AsyncThread a{nullptr};
	a.start();
	a.start([]() {});
	a.run_once();
	a.stop();
	MetaModule::AsyncThread b{nullptr, []() {
							  }};
}

void __attribute__((optimize("-O0"))) keep_math(float x) {
	[[maybe_unused]] auto y = log1pl(x);
	[[maybe_unused]] auto z = expm1l(y);
}

void keep_register_module() {
	static auto addr = &MetaModule::register_module;
	printf("%p\n", addr);
}

void keep_rack_widgets() {
	{
		rack::app::LightWidget x;
		printf("%p\n", &x);
	}
	{
		rack::ui::List x{};
		printf("%p\n", &x);
	}
	{
		rack::ui::OptionButton x{};
		printf("%p\n", &x);
	}
	{
		rack::ui::ChoiceButton x{};
		printf("%p\n", &x);
	}
}

void keep_dirent() {
	auto d = opendir(".");
	auto e = readdir(d);
	closedir(d);
	alphasort({}, {});
	[[maybe_unused]] auto x = dirfd({});
	[[maybe_unused]] auto x2 = fdopendir(0);
	[[maybe_unused]] auto x3 = readdir_r(d, e, {});
	rewinddir(d);
	[[maybe_unused]] auto x4 = scandir({}, {}, {}, {});
	seekdir(d, 0);
	telldir(d);
}

void keep_coreproc() {
	MetaModule::StreamResampler res{2};
	MetaModule::BlockResampler res2{2};
	MetaModule::StreamingWaveformDisplay disp{1, 1};
	[[maybe_unused]] auto x1 = MetaModule::hardware_random();
	[[maybe_unused]] auto x2 = MetaModule::random();
	[[maybe_unused]] MetaModule::WavFileStream stream{8};
	[[maybe_unused]] auto x3 = MetaModule::total_memory();
	[[maybe_unused]] auto x4 = MetaModule::free_memory();
	[[maybe_unused]] auto x5 = MetaModule::get_ticks();
	[[maybe_unused]] auto x6 = MetaModule::get_block_size();
	MetaModule::mark_patch_modified();
}
