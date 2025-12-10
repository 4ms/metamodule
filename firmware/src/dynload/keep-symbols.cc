// These must be inluded so the symbols are not dropped by the linker:
#include "dsp/block_resampler.hh"
#include "dsp/stream_resampler.hh"
#include "graphics/waveform_display.hh"

#include "CoreModules/async_thread.hh"
#include "dirent.h"
#include "metamodule-plugin-sdk/core-interface/audio/settings.hh"
#include "metamodule-plugin-sdk/core-interface/filesystem/helpers.hh"
#include "metamodule-plugin-sdk/core-interface/gui/notification.hh"
#include "metamodule-plugin-sdk/core-interface/midi/midi_message.hh"
#include "metamodule-plugin-sdk/core-interface/patch/patch_file.hh"
#include "metamodule-plugin-sdk/core-interface/system/memory.hh"
#include "metamodule-plugin-sdk/core-interface/system/random.hh"
#include "metamodule-plugin-sdk/core-interface/system/time.hh"
#include "metamodule-plugin-sdk/core-interface/wav/wav_file_stream.hh"

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
					 ModuleFactory::CreateModuleFunc funcCreate,
					 ModuleInfoView const &info,
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
		auto x = &clock;
		(void)x;
	}

	{
		MetaModule::BlockResampler b{};
		auto x = &b;
		(void)x;
	}

	{
		MetaModule::AsyncThread b{nullptr};
		auto x = &b;
		(void)x;
	}

	MetaModule::Filesystem::is_local_path("");
	MetaModule::Patch::get_path();
	MetaModule::Patch::get_dir();
	MetaModule::Audio::get_block_size();
	MetaModule::WavFileStream w{2};
	MetaModule::StreamResampler{};
	(void)&MetaModule::register_module;
	MetaModule::System::free_memory();
	MetaModule::System::get_ticks();
	MetaModule::System::delay_ms(1);
	MetaModule::System::hardware_random();
	//register_module
	MetaModule::Gui::notify_user("", 1);
	std::array<uint8_t, 3> c{0, 0, 0};
	MetaModule::Midi::toPrettyString(c);
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
	[[maybe_unused]] MetaModule::WavFileStream stream{8};

	[[maybe_unused]] auto x1 = MetaModule::System::hardware_random();
	[[maybe_unused]] auto x2 = MetaModule::System::random();
	[[maybe_unused]] auto x3 = MetaModule::System::total_memory();
	[[maybe_unused]] auto x4 = MetaModule::System::free_memory();
	[[maybe_unused]] auto x5 = MetaModule::System::get_ticks();

	[[maybe_unused]] auto x6 = MetaModule::Audio::get_block_size();
	MetaModule::Patch::mark_patch_modified();
	MetaModule::Gui::notify_user("", 0);
}
