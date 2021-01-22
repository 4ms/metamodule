#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"

using namespace MathTools;

class StereomixerCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		float tempLeft = 0;
		float tempRight = 0;
		for (int i = 0; i < 4; i++) {
			float leftLevel = 0;
			float rightLevel = 0;
			if (pan[i] >= 0.5f) {
				leftLevel = map_value(pan[i], 0.5f, 1.0f, 1.0f, 0.0f);
				rightLevel = 1.0f;
			} else {
				rightLevel = map_value(pan[i], 0.0f, 0.5f, 0.0f, 1.0f);
				leftLevel = 1.0f;
			}

			leftLevel *= level[i];
			rightLevel *= level[i];

			tempLeft += (signalInputs[i][0] * leftLevel);
			tempRight += (signalInputs[i][1] * rightLevel);
		}

		leftOut = tempLeft;
		rightOut = tempRight;
	}

	StereomixerCore()
	{
		for (int x = 0; x < 4; x++) {
			for (int y = 0; y < 2; y++) {
				signalInputs[x][y] = 0;
			}
			level[x] = 1.0f;
			pan[x] = 0.5f;
		}
	}

	virtual void set_param(int const param_id, const float val) override
	{
		if (param_id < 4) {
			level[param_id] = val;
		} else {
			int panChannel = param_id - 4;
			pan[panChannel] = val;
		}
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		int inputChannelNum = input_id % 4;
		if (input_id < 4) {
			signalInputs[inputChannelNum][0] = val;
		} else {
			if (rightConnected[input_id - 4]) {
				signalInputs[inputChannelNum][1] = val;
			}
			else
			{
				signalInputs[inputChannelNum][1]=signalInputs[inputChannelNum][0];
			}
			
		}
	}

	virtual void mark_input_unpatched(const int input_id) override
	{
		if (input_id > 3) {
			rightConnected[input_id - 4] = false;
		}
	}
	virtual void mark_input_patched(const int input_id) override
	{
		if (input_id > 3) {
			rightConnected[input_id - 4] = true;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = leftOut;
				break;
			case 1:
				output = rightOut;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<StereomixerCore>();
	}
	static constexpr char typeID[20] = "STEREOMIXER";
	static constexpr char description[] = "Stereo Mixer";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float signalInputs[4][2];
	float level[4];
	float pan[4];
	float leftOut = 0;
	float rightOut = 0;
	bool rightConnected[4] = {false, false, false, false};
};
