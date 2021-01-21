#pragma once
#include "coreProcessor.h"
#include "moduleTypes.h"
#include "processors/tools/parameter.h"

class NodePanel : public CoreProcessor {
public:
	static inline const int NumInJacks = 6;
	static inline const int NumOutJacks = 2;
	static inline const int NumKnobs = 8;
	virtual int get_num_inputs() const override
	{
		return NumInJacks;
	}
	virtual int get_num_outputs() const override
	{
		return NumOutJacks;
	}
	virtual int get_num_params() const override
	{
		return NumKnobs;
	}

	RefParameter<float> inputs[NumInJacks];
	RefParameter<float> outputs[NumOutJacks];
	float params[NumKnobs];

	NodePanel()
		: inputs{nodes[0], nodes[1], nodes[2], nodes[3], nodes[4], nodes[5]}
		, outputs{nodes[6], nodes[7]}
	{}

	NodePanel(float &cable0,
			  float &cable1,
			  float &cable2,
			  float &cable3,
			  float &cable4,
			  float &cable5,
			  float &cable6,
			  float &cable7)
		: inputs{cable0, cable1, cable2, cable3, cable4, cable5}
		, outputs{cable6, cable7}
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
	static constexpr char description[] = "(node) Panel: 8 Pots, 2/2 AudioIO, 4/2 AnalogIO, 1/3 GateIO";

	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);
	static inline bool s_registered_wp = ModuleFactory::registerModuleType(typeID, description, NumInJacks, create);
};

