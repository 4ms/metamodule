#pragma once
#include "patch/module_type_slug.hh"
#include "patch_play/patch_player.hh"
#include <chrono>
#include <string_view>

namespace MetaModule
{
enum class KnobTestType { Bare, AllStill, AllMovingSlowly };
enum class JackTestType { NonePatched, AllInputsZero, AllInputsRandom, AllInputsAudio, OneInputLFO, OneInputAudio };

struct ModuleLoadTester {

	struct Measurements {
		uint64_t first_run_time{};
		uint64_t worst_run_time_after_first{};
		float average_run_time{};

		Measurements() = default;
		Measurements(std::span<uint64_t> update_times)
			: first_run_time(update_times[0])
			, average_run_time(std::accumulate(update_times.begin(), update_times.end(), 0.f) /
							   (float)update_times.size()) {
			worst_run_time_after_first = *std::max_element(update_times.begin(), update_times.end());
		}
	};

	BrandModuleSlug slug;
	ModuleLoadTester(std::string_view slug)
		: slug{slug}
		, info{ModuleFactory::getModuleInfo(slug)}
		, counts{ElementCount::count(info.elements)} {
	}

	Measurements run_test(unsigned block_size, KnobTestType knob_test, JackTestType jack_test) {
		patch.blank_patch(slug);
		module_id = patch.add_module(slug);

		if (knob_test == KnobTestType::Bare && jack_test == JackTestType::NonePatched) {
			return test_bare();

		} else if (knob_test == KnobTestType::AllStill && jack_test == JackTestType::NonePatched) {
			patch_all_knobs_static();
			if (load_patch()) {
				set_all_params(0.5f);
				send_to_all_inputs(0.f);
				return run_patch([] {}, block_size);
			}

		} else if (knob_test == KnobTestType::AllStill && jack_test == JackTestType::AllInputsZero) {
			patch_all_knobs_static();
			auto other_module_id = patch.add_module("HubMedium");
			patch_all_input_jacks(other_module_id);
			patch_all_output_jacks(other_module_id);
			if (load_patch()) {
				set_all_params(0.5f);
				send_to_all_inputs(0.f);
				return run_patch([] {}, block_size);
			}

		} else if (knob_test == KnobTestType::AllStill && jack_test == JackTestType::AllInputsRandom) {
			patch_all_knobs_static();
			auto other_module_id = patch.add_module("HubMedium");
			patch_all_input_jacks(other_module_id);
			patch_all_output_jacks(other_module_id);
			if (load_patch()) {
				set_all_params(0.5f);
				int16_t x = 0;
				return run_patch(
					[&, this] {
						float f = ((float)x / (2147483648.f / 5.f));
						send_to_all_inputs(f);
						x += 4800;
					},
					block_size);
			}
		}
		return {};
	}

	uint64_t measure_construction_time() {
		std::unique_ptr<CoreProcessor> module;
		return measure([&]() { module = ModuleFactory::create(slug); });
	}

	Measurements test_bare() {
		if (auto module = ModuleFactory::create(slug)) {
			std::array<uint64_t, 64> update_times{};
			for (auto &tm : update_times)
				tm = measure([&]() { module->update(); });

			return Measurements{update_times};
		}

		return {};
	}

	void set_all_params(float val) {
		for (uint16_t param_id = 0; param_id < counts.num_params; param_id++) {
			player.modules[module_id]->set_param(param_id, val);
		}
	}

	void send_to_all_inputs(float val) {
		for (uint16_t injack_id = 0; injack_id < counts.num_inputs; injack_id++) {
			player.modules[module_id]->set_input(injack_id, val);
		}
	}

	void patch_all_knobs_static() {
		// Map all knobs
		auto num_knob_maps = std::min<uint32_t>(counts.num_params, PanelDef::NumKnobs);
		for (uint16_t knob = 0; knob < num_knob_maps; knob++) {
			MappedKnob map{.panel_knob_id = knob, .module_id = module_id, .param_id = knob, .min = 0.f, .max = 1.f};
			patch.add_update_mapped_knob(0, map);
		}
	}

	void patch_all_input_jacks(uint16_t other_module_id) {
		for (uint16_t in = 0; in < counts.num_inputs; in++) {
			patch.add_internal_cable({.module_id = module_id, .jack_id = in},
									 {.module_id = other_module_id, .jack_id = in});
		}
	}

	void patch_all_output_jacks(uint16_t other_module_id) {
		for (uint16_t out = 0; out < counts.num_outputs; out++) {
			patch.add_internal_cable({.module_id = other_module_id, .jack_id = out},
									 {.module_id = module_id, .jack_id = out});
		}
	}

	bool load_patch() {
		auto res = player.load_patch(patch);
		if (res.success == false) {
			pr_err("Test failed to load patch: %s\n", res.error_string.c_str());
			return false;
		}
		return true;
	}

	Measurements run_patch(auto control_func, size_t iterations) {
		std::vector<uint64_t> times(iterations, 0);

		for (auto &tm : times) {
			control_func();
			tm = measure([&]() { player.update_patch_singlecore(); });
		}

		return Measurements{times};
	}

	static uint64_t time_us() {
		return std::chrono::steady_clock::now().time_since_epoch().count() / 1000ULL;
	}

	[[nodiscard]] static uint64_t measure(auto test) {
		auto start = time_us();
		test();
		auto end = time_us();
		return end - start;
	}

private:
	PatchPlayer player;
	PatchData patch;
	ModuleInfoView info;
	uint16_t module_id{};
	ElementCount::Counts counts;
};

} // namespace MetaModule
