#pragma once
#include "panel_node.hh"
/*
#include "coreProcessor.h"
#include "moduleTypes.h"
#include "panel_defs.hh"
class Panel : public CoreProcessor {
public:
	static constexpr int NumKnobs = PanelDef::NumPot;

	// Yep, In/Out are swapped from how all other modules work:
	static constexpr int NumOutJacks = PanelDef::NumAudioIn + PanelDef::NumCVIn;
	static constexpr int NumInJacks = PanelDef::NumAudioOut;
	// Todo: DAC out, gate out, gate in

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"A", "B", "C", "D", "a", "b", "c", "d"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"OutL", "OutR"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{
		"In L", "In R", "CV A", "CV B", "CV C", "CV D"};
	static inline const StaticString<LongNameChars> description{"PANEL"};

	float inputs[NumInJacks];	// AudioOut
	float outputs[NumOutJacks]; // AudioIn
	float params[NumKnobs];

	Panel() {}

	virtual void update() override {}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_param(const int param_id, const float val) override
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

	virtual void set_input(const int jack_id, const float val) override
	{
		if (jack_id >= NumInJacks)
			return;
		inputs[jack_id] = val;
	}

	float get_input(const int jack_id) const
	{
		if (jack_id >= NumInJacks)
			return 0.f;

		return inputs[jack_id];
	}

	virtual float get_output(const int jack_id) const override
	{
		if (jack_id >= NumOutJacks)
			return 0.f;

		return outputs[jack_id];
	}

	void set_output(const int jack_id, const float val)
	{
		if (jack_id >= NumOutJacks)
			return;

		outputs[jack_id] = val;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<Panel>();
	}

	static constexpr char typeID[20] = "netPANEL_8";

	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);
	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] :
""; } virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ?
OutJackNames[idx] : ""; } virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
};
*/
