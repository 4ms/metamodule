#pragma once
#include "coreProcessor.h"
#include "moduleTypes.h"
#include "panel_mini_defs.hh"
#include "util/parameter.h"

// Todo: DAC out, gate out, gate in
class Panel : public CoreProcessor {
public:
	static constexpr int NumKnobs = PanelDef::NumPot;
	static constexpr int NumOutJacks = PanelDef::NumAudioIn + PanelDef::NumCVIn + PanelDef::NumGateIn;
	static constexpr int NumInJacks = PanelDef::NumAudioOut + PanelDef::NumDACOut + PanelDef::NumGateOut;
	// "OutJack" is a user-facing Input [and vice-versa]
	static constexpr int NumUserFacingOutJacks = NumInJacks;
	static constexpr int NumUserFacingInJacks = NumOutJacks;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"A", "B", "C", "D", "a", "b", "c", "d"};
	static inline const std::array<StaticString<NameChars>, NumUserFacingOutJacks> InJackNames{
		"OutL", "OutR", "CVOut1", "CVOut2", "ClockOut"};
	static inline const std::array<StaticString<NameChars>, NumUserFacingInJacks> OutJackNames{
		"In L", "In R", "CV A", "CV B", "CV C", "CV D", "GateIn1", "GateIn2", "ClockIn"};
	static inline const StaticString<LongNameChars> description{"Panel"};

	// user_facing_outs are inputs as seen by the patch (the patch outputs to the user_facing_outs), and vice-versa
	// the patch inputs from the user_facing_ins, so the latter are outputs
	float user_facing_outs[NumUserFacingOutJacks];
	float user_facing_ins[NumUserFacingInJacks];
	float params[NumKnobs];

	Panel() {}

	void update() override {}
	void set_samplerate(const float sr) override {}

	void set_param(const int param_id, const float val) override
	{
		if (param_id >= NumKnobs)
			return;
		params[param_id] = val;
	}

	float get_param(const int param_id) const
	{
		if (param_id >= NumKnobs)
			return 0.f;
		return params[param_id];
	}

	// Sets the value of a user_facing_outs jack (Audio OUT L, for example), which is an "input" as seen by the patch.
	// Used by the patch to store the outputs of the internal modules, on their way to the real world
	virtual void set_input(const int jack_id, const float val) override
	{
		if (jack_id >= NumUserFacingOutJacks)
			return;
		user_facing_outs[jack_id] = val;
	}

	// Returns the value on a user_facing_outs jack (Audio OUT L, for example)
	// Used by the audio loop to pass outputs from the internal modules to the real world
	float get_panel_output(const int jack_id) const
	{
		if (jack_id >= NumUserFacingOutJacks)
			return 0.f;
		return user_facing_outs[jack_id];
	}

	// Sets the value of a user_facing_ins jack (Audio IN L, for example)
	// Used by the audio loop to store a signal captured from the real world
	void set_panel_input(const int jack_id, const float val)
	{
		if (jack_id >= NumUserFacingInJacks)
			return;
		user_facing_ins[jack_id] = val;
	}

	// Returns the value on a user_facing_ins jack (Audio IN L, for example), which is an output as seen by the patch
	// Used by the patch, to pass a stored signal (which was capture from the real world) to internal modules
	float get_output(const int jack_id) const override
	{
		if (jack_id >= NumUserFacingInJacks)
			return 0.f;
		return user_facing_ins[jack_id];
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<Panel>();
	}

	// clang-format off
	static inline bool s_registered = ModuleFactory::registerModuleType(PanelDef::typeID, description, create);
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
};
