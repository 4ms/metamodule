#pragma once
#include "coreProcessor.h"
#include "moduleTypes.h"
#include "processors/fadeloop.hh"
#include "processors/tools/clockToSamples.h"
#include "util/math.hh"

using namespace MathTools;

class FadeDelayCore : public CoreProcessor {
public:
	const static inline long maxSamples = 48000;
	enum Inputs { AudioIn, Clock, CV };
	enum Outputs { AudioOut };
	enum Params { DelayTime, Feedback, FadeTime, Mix, CVAmount };

	virtual void update(void) override
	{
		float sampleDelay;

		clockSamples.update(clockInput);

		float finalDelay = constrain(baseDelay + cvInput * cvAmount, 0.0f, 1.0f);
		if (clockAttached == false) {
			const float oneSample = 1.0f / sampleRate;
			const float oneSecond = sampleRate * 1.0f;
			sampleDelay = map_value(finalDelay, 0.0f, 1.0f, oneSample, oneSecond);
		} else {
			int divSelect = finalDelay * 4.0f;
			auto delayCalc = clockSamples.getSamples() * divTable[divSelect];
			if (delayCalc < maxSamples)
				sampleDelay = delayCalc;
		}

		delayLine.change_delay(sampleDelay);

		delayLine.write(input + lastOutput * feedback);
		lastOutput = delayLine.read();

		delayOutput = (interpolate(input, lastOutput, mix));
	}

	FadeDelayCore() {}

	virtual void set_param(const int param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				baseDelay = val;
				break;
			case 1:
				feedback = val;
				break;
			case 2: {
				changeSec = map_value(val, 0.0f, 1.0f, 0.001f, 1.0f);
				update_fade_time();
			} break;
			case 3:
				mix = val;
				break;
			case 4:
				cvAmount = val;
				break;
		}
	}

	virtual void set_samplerate(const float sr) override
	{
		sampleRate = sr;
		update_fade_time();
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				input = val;
				break;
			case 1:
				clockInput = val;
				break;
			case 2:
				cvInput = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = delayOutput;
				break;
		}
		return output;
	}

	virtual void mark_input_unpatched(const int input_id) override
	{
		if (input_id == 1)
			clockAttached = false;
	}
	virtual void mark_input_patched(const int input_id) override
	{
		if (input_id == 1)
			clockAttached = true;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<FadeDelayCore>();
	}
	static constexpr char typeID[20] = "FADEDELAY";
	static constexpr char description[] = "Fade Delay";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	void update_fade_time()
	{
		delayLine.set_fade_speed(1.f / (changeSec * sampleRate));
	}
	float feedback = 0;
	float mix = 0.5f;

	float delayOutput = 0;
	float lastOutput = 0;
	float feedbackSample = 0;

	float input = 0;

	float baseDelay = 0;

	float sampleRate = 48000;
	float changeSec = 0.01f;

	float cvInput = 0;
	float cvAmount = 0;

	FadeLoop<float, maxSamples> delayLine;

	const float divTable[5] = {0.125, 0.25, 0.5, 1, 2};
	float clockInput = 0;
	bool clockAttached = false;
	ClockToSamples clockSamples;
};
