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
			float noteValue =
				map_value(signalInput, -1.0f, 1.0f, static_cast<float>(lowestNote), static_cast<float>(highestNote));
			int octave = noteValue / 12.0f;

			int tempNote = mapTable[(int)(noteValue + lowestNote) % 12] + octave * 12.0f;
			if (tempNote <= totalNotes)
				currentNote = tempNote;
			signalOutput = (currentNote / static_cast<float>(totalNotes)) * 2.0f - 1.0f;
		} else {
			signalOutput = signalInput;
		}
	}

	QuantizerCore()
	{
		maxCalculatedVolt = ceilf(OutputHighRangeVolts);
		if (OutputLowRangeVolts < 0) {
			minCalculatedVolt = ceilf(fabsf(OutputLowRangeVolts)) * -1.0f;
		} else {
			minCalculatedVolt = ceilf(OutputLowRangeVolts);
		}

		lowestNote = 12 * minCalculatedVolt;
		highestNote = 12 * maxCalculatedVolt;

		totalNotes = (maxCalculatedVolt - minCalculatedVolt) * 12;
		for (int i = 0; i < 12; i++) {
			keyStatus[i] = false;
			currentButton[i] = false;
			lastButton[i] = false;
			mapTable[i] = i;
		}
	}

	virtual void set_param(int const param_id, const float val) override
	{
		if (param_id >= 12 || param_id < 0)
			return;
		keyStatus[param_id] = (val > 0.1f);
		scaleUpdate();
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
	bool currentButton[12];
	bool lastButton[12];

	int currentNote = 0;

	int mapTable[12];
	int notesActive = 0;
	int lowestNote;
	int highestNote;

	int totalNotes;

	int firstActive = 0;
	float signalInput = 0;
	float signalOutput = 0;

	int minCalculatedVolt = -5;
	int maxCalculatedVolt = 5;

	uint16_t currentScale = 0;
	uint16_t lastScale = 0;

	void scaleUpdate()
	{
		notesActive = 0;

		for (int i = 0; i < 12; i++) {
			notesActive += keyStatus[i] ? 1 : 0;
		}

		if (notesActive > 0) {
			lastScale = currentScale;
			currentScale = 0;
			for (int i = 0; i < 12; i++) {
				currentScale += keyStatus[i] << i;
			}

			if (currentScale != lastScale) {
				firstActive = lowestValidNote();

				genTable();
			}
		}
	}

	int lowestValidNote()
	{
		int tempNote = 13;
		for (int i = 0; i < 12; i++) {
			if (keyStatus[i] == true) {
				tempNote = min(tempNote, i);
			}
		}
		return (tempNote);
	}

	void genTable()
	{
		int fillNote = firstActive;

		for (int i = 0; i < 12; i++) {
			if (i < firstActive)
				mapTable[i] = fillNote;
			else {
				if (keyStatus[i] == true) {
					fillNote = i;
				}
				mapTable[i] = fillNote;
			}
		}
	}
};
