#pragma once

#include "coreProcessor.h"
#include "moduleTypes.h"
#include "util/math.hh"

using namespace MathTools;

class QuantizerCore : public CoreProcessor {
public:
	void scaleChanged()
	{
		if (notesActive > 0) {
			int tempNote = 13;
			for (int i = 0; i < 12; i++) {
				if (keyStatus[i] == true) {
					tempNote = min(tempNote, i);
				}
			}
			firstActive = tempNote;

			int fillNote = firstActive;

			for (int i = 0; i < 12; i++) {
				if (i < firstActive)
					mapTable[i] = fillNote;
				else {
					if (keyStatus[i] == 1)
						fillNote = i;
					mapTable[i] = fillNote;
				}
			}
		}
	}

	virtual void update(void) override
	{
		notesActive = 0;
		int changeStatus = 0;
		for (int i = 0; i < 12; i++) {
			if (currentButton[i] > lastButton[i]) {
				keyStatus[i] = !keyStatus[i];
				changeStatus = 1;
			}
			notesActive += keyStatus[i];
		}

		if (changeStatus) {
			scaleChanged();
		}

		if (notesActive > 0) {
			int sign;
			if (signalInput >= 0)
				sign = 1;
			else
				sign = -1;
			float noteValue = MathTools::f_abs(signalInput) * 60.0f;
			int octave = noteValue / 12.0f;

			int currentNote = mapTable[(int)noteValue % 12] + octave * 12.0f;
			if (currentNote > 60) {
				while (currentNote > 60) {
					octave = noteValue / 12.0f;
					currentNote = mapTable[(int)noteValue % 12] + octave * 12.0f;
					noteValue -= 1.0f;
				}
			}
			signalOutput = currentNote / 60.0f * sign;

		} else {
			signalOutput = signalInput;
		}
	}

	QuantizerCore()
	{
		for (int i = 0; i < 12; i++) {
			keyStatus[i] = false;
			currentButton[i] = false;
			lastButton[i] = false;
			mapTable[i] = i;
		}
	}

	virtual void set_param(int const param_id, const float val) override
	{
		lastButton[param_id] = currentButton[param_id];
		currentButton[param_id] = val > 0;
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				signalInput = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = signalOutput;
				break;
		}
		return output;
	}

	virtual float get_led_brightness(const int led_id) const override
	{
		return keyStatus[led_id] ? 1.0f : 0.0f;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<QuantizerCore>();
	}
	static constexpr char typeID[20] = "QUANTIZER";
	static constexpr char description[] = "Quantizer";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	bool keyStatus[12];
	bool currentButton[12];
	bool lastButton[12];

	int mapTable[12];
	int notesActive = 0;

	int firstActive = 0;

	float signalInput;
	float signalOutput;
};
