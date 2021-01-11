#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"

using namespace MathTools;

class QuantizerCore : public CoreProcessor {
public:
	void scaleChanged()
	{
		if (notesActive > 0) {
			for (int i = 0; i < 12; i++) {
				notesActive += keyStatus[i];
			}

			if (notesActive > 0) {
				int tempNote = 13;
				for (int i = 0; i < 12; i++) {
					if (keyStatus[i] == 1) {
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
	}
	virtual void update(void) override
	{
		notesActive = 0;
		for (int i = 0; i < 12; i++) {
			if (currentButton[i] > lastButton[i]) {
				keyStatus[i] = !keyStatus[i];
				scaleChanged();
			}
			notesActive += keyStatus[i];
		}

		if (notesActive > 0) {

		} else {
			signalOutput = signalInput;
		}
	}

	QuantizerCore()
	{
		for (int i = 0; i < 12; i++) {
			keyStatus[i] = false;
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
	int currentButton[12];
	int lastButton[12];

	int mapTable[12];
	int notesActive = 0;

	int firstActive = 0;

	float signalInput;
	float signalOutput;
};
