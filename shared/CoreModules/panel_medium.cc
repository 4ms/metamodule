#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/PanelMedium_info.hh"
#include "CoreModules/moduleFactory.hh"
#include "panel_medium_defs.hh"

// Todo: DAC out, gate out, gate in
class PanelMedium : public CoreProcessor {
public:
	using Info = PanelMediumInfo;
	using ThisCore = PanelMedium;

	static constexpr int NumKnobs = PanelDef::NumPot;
	static constexpr int NumOutJacks = PanelDef::NumAudioIn + PanelDef::NumCVIn + PanelDef::NumGateIn;
	static constexpr int NumInJacks = PanelDef::NumAudioOut + PanelDef::NumDACOut + PanelDef::NumGateOut;
	// User-facing out jacks, like "Audio Out 3", is an input jack as seen by other virtual modules
	static constexpr int NumUserFacingOutJacks = NumInJacks;
	// User-facing in jacks, like "Audio In 1", is an output jack as seen by other virtual modules
	static constexpr int NumUserFacingInJacks = NumOutJacks;
	// user_facing_outs are inputs as seen by the patch (the patch outputs to the user_facing_outs), and vice-versa
	// the patch inputs from the user_facing_ins, so the latter are outputs
	float user_facing_outs[NumUserFacingOutJacks];
	float user_facing_ins[NumUserFacingInJacks];
	float params[NumKnobs];

	PanelMedium() {
	}

	void update() override {
	}

	void set_samplerate(const float sr) override {
	}

	void set_param(const int param_id, const float val) override {
		if (param_id >= NumKnobs)
			return;
		params[param_id] = val;
	}

	// float get_param(const int param_id) const {
	// 	if (param_id >= NumKnobs)
	// 		return 0.f;
	// 	return params[param_id];
	// }

	// Sets the value of a user_facing_outs jack (Audio Out 1, for example), which is an "input" as seen by the patch.
	// Used by the patch to store the outputs of the internal modules, on their way to the real world
	void set_input(const int jack_id, const float val) override {
		if (jack_id >= NumUserFacingOutJacks)
			return;
		user_facing_outs[jack_id] = val;
	}

	// Returns the value on a user_facing_outs jack (Audio OUT L, for example)
	// Used by the audio loop to pass outputs from the internal modules to the real world
	// float get_panel_output(const int jack_id) const {
	// 	if (jack_id >= NumUserFacingOutJacks)
	// 		return 0.f;
	// 	return user_facing_outs[jack_id];
	// }

	// // Sets the value of a user_facing_ins jack (Audio IN L, for example)
	// // Used by the audio loop to store a signal captured from the real world
	// void set_panel_input(const int jack_id, const float val) {
	// 	if (jack_id >= NumUserFacingInJacks)
	// 		return;
	// 	user_facing_ins[jack_id] = val;
	// }

	// Returns the value on a user_facing_ins jack (Audio IN L, for example), which is an output as seen by the patch
	// Used by the patch, to pass a stored signal (which was capture from the real world) to internal modules
	float get_output(const int jack_id) const override {
		if (jack_id >= NumUserFacingInJacks)
			return 0.f;
		return user_facing_ins[jack_id];
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on
};
