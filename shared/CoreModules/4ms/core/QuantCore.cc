#include "CoreModules/coreProcessor.h"
#include "CoreModules/moduleFactory.hh"
#include "info/Quant_info.hh"
#include "scaling_config.hh"
#include "util/math.hh"
#include <cmath>

//FIXME:
// The code below is for a module with 12 on/off buttons that set the scale
// But the current module is three knobs: Scale, Root, Transpose
// So we need to make Scale select a pre-set scale pattern,
// And Root transposes it by semitones ("modes")
// And Transpose shifts it by a variable amount (tuning)
// Also add a display to show the resulting pattern

namespace MetaModule
{

class QuantCore : public CoreProcessor {
	using Info = QuantInfo;
	using ThisCore = QuantCore;

public:
	QuantCore() {
		outputRangeNotes = (OutputHighRangeVolts - OutputLowRangeVolts) * 12.f;
		inputRangeNotes = (InputHighRangeVolts - InputLowRangeVolts) * 12.f;
		rangeScaling = 2.0f * outputRangeNotes / inputRangeNotes;
		for (int i = 0; i < 12; i++) {
			keyStatus[i] = false;
		}
	}

	void update() override {
		// Todo: base all values on Low/HighRangeVolts
		if (notesActive > 0) {
			lastNote = currentNote;
			currentNote = MathTools::map_value(signalInput, -1.0f, 1.0f, 0.0f, inputRangeNotes);
			if ((currentNote != lastNote) || scaleChanged) {
				signalOutput = static_cast<float>(calcNote(currentNote)) / outputRangeNotes * rangeScaling - 1.0f;
				scaleChanged = false;
			}
		} else {
			signalOutput = signalInput;
		}
	}

	void set_param(int param_id, float val) override {
		if (param_id >= (Info::NumKnobs) || param_id < 0)
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

	void set_input(int input_id, float val) override {
		if (input_id == Info::InputInput)
			signalInput = val;
	}

	float get_output(int output_id) const override {
		return output_id == Info::OutputOut ? signalOutput : 0.f;
	}

	void set_samplerate(float sr) override {
	}

	float get_led_brightness(int led_id) const override {
		return keyStatus[led_id] ? 1.0f : 0.0f;
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

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

	int calcNote(float inputNote) {
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

} // namespace MetaModule
