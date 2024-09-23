#pragma once
#include "patch/module_type_slug.hh"
#include "patch_play/patch_player.hh"
#include "system/alloc_watch.hh"
#include <string_view>

extern AllocationWatch *watch;

namespace MetaModule
{

struct ModuleMemoryTester {
	struct MemUsage {
		size_t memory_used{};
		bool measuring_failed = false;
		int32_t memory_leaked{};
	};

	struct Measurements {
		MemUsage create{};
		MemUsage run_unpatched{};
		MemUsage run_fully_patched{};
	};

	ModuleMemoryTester(std::string_view slug)
		: slug{slug}
		, info{ModuleFactory::getModuleInfo(slug)}
		, counts{ElementCount::count(info.elements)} {
	}

	enum class TestType { FirstRun };

	Measurements run_test(TestType test_type) {
		Measurements meas;

		// Enable allocation watching
		watch = &watcher;

		if (test_type == TestType::FirstRun) {
			watcher.reset();

			auto module = ModuleFactory::create(slug);
			{
				int32_t leaked = (int32_t)watcher.allocations - (int32_t)watcher.deallocations;
				meas.create = MemUsage{watcher.allocations, watcher.overflowed, leaked};
				watcher.reset();
			}

			module->update();
			{
				int32_t leaked = (int32_t)watcher.allocations - (int32_t)watcher.deallocations;
				meas.run_unpatched = MemUsage{watcher.allocations, watcher.overflowed, leaked};
				watcher.reset();
			}

			for (uint16_t injack_id = 0; injack_id < counts.num_inputs; injack_id++) {
				module->mark_input_patched(injack_id);
				module->set_input(injack_id, 0.5f);
			}

			for (uint16_t outjack_id = 0; outjack_id < counts.num_outputs; outjack_id++) {
				module->mark_output_patched(outjack_id);
				[[maybe_unused]] auto val = module->get_output(outjack_id);
			}

			module->update();
			{
				int32_t leaked = (int32_t)watcher.allocations - (int32_t)watcher.deallocations;
				meas.run_fully_patched = MemUsage{watcher.allocations, watcher.overflowed, leaked};
				watcher.reset();
			}
		}

		// Disable allocation watching
		watch = nullptr;

		return meas;
	}

private:
	AllocationWatch watcher;

	BrandModuleSlug slug;
	ModuleInfoView info;
	ElementCount::Counts counts;
};

} // namespace MetaModule
