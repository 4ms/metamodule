#pragma once
#include "patch/module_type_slug.hh"
#include "patch_play/patch_player.hh"
#include "system/alloc_watch.hh"
#include <malloc.h>
#include <string_view>

extern AllocationWatcher *watch;

namespace MetaModule
{

struct ModuleMemoryTester {

	struct Measurements {
		size_t peak_mem_startup{};
		size_t peak_running_mem{};
		size_t mem_leaked{};
		bool results_invalid = false;
		bool double_free = false;
	};

	ModuleMemoryTester(std::string_view slug)
		: slug{slug}
		, info{ModuleFactory::getModuleInfo(slug)}
		, counts{ElementCount::count(info.elements)} {
	}

	enum class TestType { FirstRun };

	Measurements run_test(TestType test_type) {
		Measurements meas;
		struct mallinfo mi {};

		// Enable allocation watching
		watch = &watcher;

		mi = mallinfo();
		auto start_mem_used = mi.uordblks;

		if (test_type == TestType::FirstRun) {
			watcher.reset();

			auto module = ModuleFactory::create(slug);
			if (!module) {
				pr_err("Module %s not found\n", slug.c_str());
				return {};
			}
			meas.peak_mem_startup = watcher.peak_usage;
			watcher.peak_usage = watcher.mem_alloced - watcher.mem_dealloced;

			module->update();

			for (uint16_t injack_id = 0; injack_id < counts.num_inputs; injack_id++) {
				module->mark_input_patched(injack_id);
				module->set_input(injack_id, 0.5f);
			}

			for (uint16_t outjack_id = 0; outjack_id < counts.num_outputs; outjack_id++) {
				module->mark_output_patched(outjack_id);
				[[maybe_unused]] auto val = module->get_output(outjack_id);
			}

			module->update();
			module->update();
			module->update();
			// TODO: modulate jacks/params?

			meas.peak_running_mem = watcher.peak_usage;
		}

		// Check for leaks: not working, detects false leaks?
		// uint64_t leaked = 0;
		// for (auto const &block : watcher.allocs) {
		// 	if (block.dealloced == false) {
		// 		leaked += block.size;
		// 	}
		// }

		// Leak detects false? leaks in OrangeLine (all modules) and Bogaudio:DADSRH, DADSRHPlus
		mi = mallinfo();
		auto end_mem_used = mi.uordblks;
		meas.mem_leaked = end_mem_used - start_mem_used;

		meas.double_free = watcher.double_free;
		meas.results_invalid = watcher.too_many_allocs;

		// Disable allocation watching
		watch = nullptr;
		watcher.reset();

		return meas;
	}

private:
	AllocationWatcher watcher;

	BrandModuleSlug slug;
	ModuleInfoView info;
	ElementCount::Counts counts;
};

} // namespace MetaModule
