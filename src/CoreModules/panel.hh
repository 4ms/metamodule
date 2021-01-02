#pragma once
#include "coreProcessor.h"
#include "moduleTypes.h"

class Panel : public CoreProcessor {
public:
	static inline const int NumKnobs = 8;
	static inline const int NumInJacks = 6;
	static inline const int NumOutJacks = 2;

	float inputs[NumInJacks];
	float outputs[NumOutJacks];
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

	virtual void set_input(const int jack_id, const float val) override
	{
		if (jack_id >= NumInJacks)
			return;
		inputs[jack_id] = val;
	}

	virtual float get_output(const int jack_id) const override
	{
		if (jack_id >= NumOutJacks)
			return 0.f;

		return outputs[jack_id];
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<Panel>();
	}
	static constexpr ModuleIDType get_module_type()
	{
		return ModuleType::PANEL;
	}

private:
	static inline bool s_registered = ModuleFactory::registerModuleType(get_module_type(), "Panel", create);
};

