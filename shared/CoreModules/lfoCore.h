#pragma once

#include "coreProcessor.h"
#include "moduleTypes.h"
#include "util/math.hh"
#include "util/math_tables.hh"
#include "util/parameter.h"

using namespace MathTools;

class NodeLFOCore : public CoreProcessor {
public:
	static inline const int NumInJacks = 2;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 3;
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

	NodeLFOCore()
	{
		freqJack = 0.f;
		resetJack = 0.f;
		sinOut = 0.f;
	}

	NodeLFOCore(float &nFreq, float &nReset, float &nOut)
		: freqJack{nFreq}
		, resetJack{nReset}
		, sinOut{nOut}
	{
		freqJack = 0.f;
		resetJack = 0.f;
		sinOut = 0.f;
	}

	virtual void update() override
	{
		check_changes();

		if (doReset) {
			phaccu = 0.f;
			doReset = false;
		} else {
			phaccu += frequency / sampleRate;
			if (phaccu >= 1.0f)
				phaccu -= 1.0f;
		}

		sinOut = sinTable.interp_wrap(phaccu + phaseOffset) * level;
	}

	void check_changes()
	{
		if (freqJack.isChanged()) {
			auto f = expTable.closest(constrain(freqJack.getValue(), 0.f, 1.f));
			cv_frequency = f * f / 0.1f;
			// cv_frequency = map_value(freqJack, 0.0f, 1.0f, 0.1f, 200.f);
			combineKnobCVFreq();
		}

		if (resetJack.isChanged()) {
			// Todo: check hystersis here
			if (resetJack > GateThreshold) {
				if (!lastReset) {
					doReset = true;
				}
				lastReset = true;
			} else
				lastReset = false;
		}
	}

	virtual void set_param(int const param_id, const float val) override
	{
		if (param_id == 0) {
			auto f = expTable.closest(constrain(val, 0.f, 1.f));
			knob_frequency = f * f / 0.1f;
			// knob_frequency = map_value(val, 0.0f, 1.0f, 0.1f, 200.0f);
			combineKnobCVFreq();
		}
		if (param_id == 1) {
			phaseOffset = val;
		}
		if (param_id == 2) {
			level = val;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		sampleRate = sr;
	}

	virtual void set_input(const int input_id, const float val) override
	{
		if (input_id == 0) {
			freqJack = val;
		}
		if (input_id == 1) {
			resetJack = val;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		if (output_id == 0)
			return sinOut;
		return 0.f;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<NodeLFOCore>();
	}
	static std::unique_ptr<CoreProcessor> create(float *nodelist, const uint8_t *idx)
	{
		return std::make_unique<NodeLFOCore>(nodelist[idx[0]], nodelist[idx[1]], nodelist[idx[2]]);
	}
	static constexpr char typeID[20] = "LFOSINE";
	static constexpr char description[] = "(node format) Basic Sine LFO";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);
	static inline bool s_registered_wp = ModuleFactory::registerModuleType(typeID, description, NumInJacks, create);

private:
	const float GateThreshold = 0.1f;

	RefParameter<float> freqJack = nodes[0];
	RefParameter<float> resetJack = nodes[1];
	RefParameter<float> sinOut = nodes[2];

	// knobs
	float phaseOffset = 0;
	float level = 1;
	Parameter<float> knob_frequency{1.f};

	// internals
	float cv_frequency = 0.f;
	float phaccu = 0;
	float frequency = 1;
	float sampleRate = 48000;
	bool lastReset = false;
	bool doReset = false;

	void combineKnobCVFreq()
	{
		frequency = knob_frequency + cv_frequency;
	}
};
