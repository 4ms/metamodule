#pragma once
#include "CoreModules/CoreProcessor.hh"
#include <array>
#include <memory>
#include <optional>

// A stub module that records its jack patched-state the same way SmartCoreProcessor does.
//
// The default CoreProcessor::mark_*_patched() are no-ops, and TestModule doesn't override
// them, so neither can observe whether a jack is patched. Output-normalling modules
// (DLD, Tapo, SISM) branch their audio on isPatched<...Out>() -- the patched-state of an
// *output* jack -- so they need a stub that tracks it to pin desync bugs.
//
// mark_*() bodies below mirror SmartCoreProcessor.hh exactly so the observed state matches
// what a real module would see.
struct PatchedFlagModule : public CoreProcessor {
	static constexpr unsigned NumJacks = 8;

	std::array<bool, NumJacks> output_patched{};
	std::array<std::optional<float>, NumJacks> input_vals{};

	void update() override {
	}
	void set_samplerate(float) override {
	}
	void set_param(int, float) override {
	}

	void set_input(int id, float val) override {
		if ((unsigned)id < NumJacks)
			input_vals[id] = val;
	}
	float get_output(int) const override {
		return 0.f;
	}

	void mark_all_inputs_unpatched() override {
		input_vals.fill(std::nullopt);
	}
	void mark_input_unpatched(int id) override {
		if ((unsigned)id < NumJacks)
			input_vals[id].reset();
	}
	void mark_input_patched(int id) override {
		if ((unsigned)id < NumJacks && !input_vals[id].has_value())
			input_vals[id] = 0.f;
	}

	void mark_all_outputs_unpatched() override {
		output_patched.fill(false);
	}
	void mark_output_unpatched(int id) override {
		if ((unsigned)id < NumJacks)
			output_patched[id] = false;
	}
	void mark_output_patched(int id) override {
		if ((unsigned)id < NumJacks)
			output_patched[id] = true;
	}

	// Mirrors SmartCoreProcessor::isPatched<EL>() for output and input elements
	bool is_output_patched(unsigned id) const {
		return id < NumJacks ? output_patched[id] : false;
	}
	bool is_input_patched(unsigned id) const {
		return id < NumJacks ? input_vals[id].has_value() : false;
	}

	static std::unique_ptr<CoreProcessor> create() {
		return std::make_unique<PatchedFlagModule>();
	}
};
