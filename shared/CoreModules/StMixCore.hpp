#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/StMix_info.hh"
#include "CoreModules/moduleFactory.hh"

#include "util/math.hh"

class StMixCore : public CoreProcessor {
	using Info = StMixInfo;
	using ThisCore = StMixCore;

public:
	StMixCore() = default;

	void update() override {
		float tempLeft = 0;
		float tempRight = 0;
		for (int i = 0; i < 4; i++) {
			float leftLevel;
			float rightLevel;
			if (pan[i] >= 0.5f) {
				leftLevel = level[i] * MathTools::map_value(pan[i], 0.5f, 1.0f, 1.0f, 0.0f);
				rightLevel = level[i];
			} else {
				leftLevel = level[i];
				rightLevel = level[i] * MathTools::map_value(pan[i], 0.0f, 0.5f, 0.0f, 1.0f);
			}
			tempLeft += signalInputs[i][0] * leftLevel;
			tempRight += signalInputs[i][1] * rightLevel;
		}

		leftOut = tempLeft;
		rightOut = tempRight;
	}

	void set_param(int param_id, float val) override {
		switch (param_id) {
			case Info::KnobLevel_1:
				level[0] = val;
				break;
			case Info::KnobLevel_2:
				level[1] = val;
				break;
			case Info::KnobLevel_3:
				level[2] = val;
				break;
			case Info::KnobLevel_4:
				level[3] = val;
				break;
			case Info::KnobPan_1:
				pan[0] = val;
				break;
			case Info::KnobPan_2:
				pan[1] = val;
				break;
			case Info::KnobPan_3:
				pan[2] = val;
				break;
			case Info::KnobPan_4:
				pan[3] = val;
				break;
		}
	}

	void set_input(int input_id, float val) override {
		switch (input_id) {
			case Info::InputIn_1_L:
				signalInputs[0][0] = val;
				if (!rightConnected[0])
					signalInputs[0][1] = val;
				break;
			case Info::InputIn_2_L:
				signalInputs[1][0] = val;
				if (!rightConnected[0])
					signalInputs[1][1] = val;
				break;
			case Info::InputIn_3_L:
				signalInputs[2][0] = val;
				if (!rightConnected[0])
					signalInputs[2][1] = val;
				break;
			case Info::InputIn_4_L:
				signalInputs[3][0] = val;
				if (!rightConnected[0])
					signalInputs[3][1] = val;
				break;
			case Info::InputIn_1_R:
				signalInputs[0][1] = val;
				break;
			case Info::InputIn_2_R:
				signalInputs[1][1] = val;
				break;
			case Info::InputIn_3_R:
				signalInputs[2][1] = val;
				break;
			case Info::InputIn_4_R:
				signalInputs[3][1] = val;
				break;
		}
	}

	float get_output(int output_id) const override {
		if (output_id == Info::OutputL)
			return leftOut;
		if (output_id == Info::OutputR)
			return rightOut;
		return 0.f;
	}

	void set_samplerate(float sr) override {
	}

	float get_led_brightness(int led_id) const override {
		return 0.f;
	}

	void mark_input_unpatched(const int input_id) override {
		switch (input_id) {
			case Info::InputIn_1_R:
				rightConnected[0] = false;
				break;
			case Info::InputIn_2_R:
				rightConnected[1] = false;
				break;
			case Info::InputIn_3_R:
				rightConnected[2] = false;
				break;
			case Info::InputIn_4_R:
				rightConnected[3] = false;
				break;
		}
	}

	void mark_input_patched(const int input_id) override {
		switch (input_id) {
			case Info::InputIn_1_R:
				rightConnected[0] = true;
				break;
			case Info::InputIn_2_R:
				rightConnected[1] = true;
				break;
			case Info::InputIn_3_R:
				rightConnected[2] = true;
				break;
			case Info::InputIn_4_R:
				rightConnected[3] = true;
				break;
		}
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
	float signalInputs[4][2]{{0}, {0}};
	float level[4]{1.f, 1.f, 1.f, 1.f};
	float pan[4]{0.5f, 0.5f, 0.5f, 0.5f};
	float leftOut = 0;
	float rightOut = 0;
	bool rightConnected[4]{false, false, false, false};
};
