#pragma once
#include "coreProcessor.h"
#include "moduleTypes.h"
#include "scalingConfig.hh"
#include "util/math.hh"

using namespace MathTools;

class QuantizerCore : public CoreProcessor {
	static inline const int NumInJacks = 1;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 0;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Input"};
	static inline const StaticString<LongNameChars> description{"Quantizer"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on

public:
	virtual void update(void) override
	{
		// Todo: base all values on Low/HighRangeVolts
		if (notesActive > 0) {
			lastNote = currentNote;
			currentNote = map_value(signalInput, -1.0f, 1.0f, 0.0f, inputRangeNotes);
			if ((currentNote != lastNote) || scaleChanged) {
				signalOutput = static_cast<float>(calcNote(currentNote)) / outputRangeNotes * rangeScaling - 1.0f;
				scaleChanged = false;
			}
		} else {
			signalOutput = signalInput;
		}
	}

	QuantizerCore()
	{
		outputRangeNotes = (OutputHighRangeVolts - OutputLowRangeVolts) * 12.f;
		inputRangeNotes = (InputHighRangeVolts - InputLowRangeVolts) * 12.f;
		rangeScaling = 2.0f * outputRangeNotes / inputRangeNotes;
		for (int i = 0; i < 12; i++) {
			keyStatus[i] = false;
		}
	}

	virtual void set_param(int const param_id, const float val) override
	{
		if (param_id >= 12 || param_id < 0)
			return;
		bool newVal = val > 0.1f;
		if (newVal == true && keyStatus[param_id] == false) {
			keyStatus[param_id] = true;
			notesActive++;
			scaleChanged = true;
		}
		if (newVal == false && keyStatus[param_id] == true) {
			keyStatus[param_id] = false;
			notesActive--;
			scaleChanged = true;
		}
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
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	bool keyStatus[12];

	float currentNote = 0;
	float lastNote = 0;

	float outputRangeNotes;
	float inputRangeNotes;
	float rangeScaling;

	bool scaleChanged = false;

	float signalInput = 0;
	float signalOutput = 0;

	int notesActive = 0;

	int calcNote(float inputNote)
	{
		float lowestDiff = 40;
		float calcDiff = 0;
		for (int i = 0; i < 12; i++) {
			if (keyStatus[i] == true) {
				float noteInOctave = fmod(inputNote, 12);
				float thisDiff = i - noteInOctave;
				float diffCompliment = 12 - fabsf(thisDiff);
				if (fabsf(thisDiff) < fabsf(diffCompliment)) {
					if (fabsf(thisDiff) < lowestDiff) {
						lowestDiff = fabsf(thisDiff);
						calcDiff = thisDiff;
					}
				} else {
					if (fabsf(diffCompliment) < lowestDiff) {
						lowestDiff = fabsf(diffCompliment);
						calcDiff = diffCompliment;
					}
				}
			}
		}
		int outputNote = inputNote + calcDiff;
		return outputNote;
	}
};
