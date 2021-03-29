#pragma once
#include "coreProcessor.h"
#include "moduleTypes.h"
#include "panel_defs.hh"
#include "util/parameter.h"

class NodePanel : public CoreProcessor {
public:
	static constexpr int NumKnobs = PanelDef::NumPot;
	static constexpr int NumInJacks = PanelDef::NumAudioIn + PanelDef::NumCVIn;
	static constexpr int NumOutJacks = PanelDef::NumAudioOut;
	// Todo: DAC out, gate out, gate in

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"A", "B", "C", "D", "a", "b", "c", "d"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"OutL", "OutR"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{
		"In L", "In R", "CV A", "CV B", "CV C", "CV D"};
	static inline const StaticString<LongNameChars> description{"PANEL"};

	RefParameter<float> outputs[NumOutJacks];
	RefParameter<float> inputs[NumInJacks];
	float params[NumKnobs];

	NodePanel()
		: outputs{nodes[0], nodes[1]}
		, inputs{nodes[2], nodes[3], nodes[4], nodes[5], nodes[6], nodes[7]}
	{}

	NodePanel(float &cable0,
			  float &cable1,
			  float &cable2,
			  float &cable3,
			  float &cable4,
			  float &cable5,
			  float &cable6,
			  float &cable7)
		: outputs{cable0, cable1}
		, inputs{cable2, cable3, cable4, cable5, cable6, cable7}
	{}

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
		return std::make_unique<NodePanel>();
	}

	static std::unique_ptr<CoreProcessor> create(float *nodes, const uint8_t *idx)
	{
		return std::make_unique<NodePanel>(nodes[idx[0]],
										   nodes[idx[1]],
										   nodes[idx[2]],
										   nodes[idx[3]],
										   nodes[idx[4]],
										   nodes[idx[5]],
										   nodes[idx[6]],
										   nodes[idx[7]]);
	}

	static constexpr char typeID[20] = "PANEL_8";

	// Swapped In/Out! Beacuse panel is different than other modules
	static inline bool s_registered_wp =
		ModuleFactory::registerModuleType(typeID, description, create, NumOutJacks, NumInJacks, NumKnobs);

	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);
	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
};
