#pragma once
#include "coreProcessor.h"
#include "moduleTypes.h"
#include "panel_defs.hh"

class Panel : public CoreProcessor {
public:
	static constexpr int NumKnobs = PanelDef::NumPot;
	static constexpr int NumInJacks = PanelDef::NumAudioIn + PanelDef::NumCVIn;
	static constexpr int NumOutJacks = PanelDef::NumAudioOut;
	// Todo: DAC out, gate out, gate in

	float inputs[NumInJacks];	// OutsideToPatch
	float outputs[NumOutJacks]; // PatchToOutside
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
	static constexpr char description[] = "Panel: 8 Pots, 2/2 AudioIO, 4/2 AnalogIO, 1/3 GateIO";

	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);
};
