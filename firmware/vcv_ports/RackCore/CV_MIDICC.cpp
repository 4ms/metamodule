#include "plugin.hpp"

namespace rack
{
namespace core
{

struct CCMidiOutput : midi::Output {
	uint8_t lastValues[128];
	int64_t frame = -1;

	CCMidiOutput() {
		reset();
	}

	void reset() {
		for (uint8_t n = 0; n < 128; n++) {
			lastValues[n] = -1;
		}
		Output::reset();
	}

	void setValue(uint8_t value, uint8_t cc) {
		if (value == lastValues[cc])
			return;
		lastValues[cc] = value;
		// CC
		midi::Message m;
		m.setStatus(0xb);
		m.setNote(cc);
		m.setValue(value);
		m.setFrame(frame);
		sendMessage(m);
	}

	void setFrame(int64_t frame) {
		this->frame = frame;
	}
};

struct CV_MIDICC : Module {
	enum ParamIds { NUM_PARAMS };
	enum InputIds { ENUMS(CC_INPUTS, 16), NUM_INPUTS };
	enum OutputIds { NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	CCMidiOutput midiOutput;
	dsp::Timer rateLimiterTimer;
	int learningId = -1;
	int8_t learnedCcs[16] = {};

	CV_MIDICC() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		for (int id = 0; id < 16; id++)
			configInput(CC_INPUTS + id, string::f("Cell %d", id + 1));
		onReset();
	}

	void onReset() override {
		for (int id = 0; id < 16; id++) {
			learnedCcs[id] = id + 1;
		}
		learningId = -1;
		midiOutput.reset();
		midiOutput.midi::Output::reset();
	}

	void process(const ProcessArgs &args) override {
		const float rateLimiterPeriod = 1 / 200.f;
		bool rateLimiterTriggered = (rateLimiterTimer.process(args.sampleTime) >= rateLimiterPeriod);
		if (rateLimiterTriggered)
			rateLimiterTimer.time -= rateLimiterPeriod;
		else
			return;

		midiOutput.setFrame(args.frame);

		for (int id = 0; id < 16; id++) {
			if (learnedCcs[id] < 0)
				continue;

			uint8_t value = (uint8_t)clamp(std::round(inputs[CC_INPUTS + id].getVoltage() / 10.f * 127), 0.f, 127.f);
			midiOutput.setValue(value, learnedCcs[id]);
		}
	}

	void setLearnedCc(int id, int8_t cc) {
		// Unset IDs of similar CCs
		if (cc >= 0) {
			for (int id = 0; id < 16; id++) {
				if (learnedCcs[id] == cc)
					learnedCcs[id] = -1;
			}
		}
		learnedCcs[id] = cc;
	}

	json_t *dataToJson() override {
		json_t *rootJ = json_object();

		json_t *ccsJ = json_array();
		for (int id = 0; id < 16; id++) {
			json_array_append_new(ccsJ, json_integer(learnedCcs[id]));
		}
		json_object_set_new(rootJ, "ccs", ccsJ);

		json_object_set_new(rootJ, "midi", midiOutput.toJson());
		return rootJ;
	}

	void dataFromJson(json_t *rootJ) override {
		json_t *ccsJ = json_object_get(rootJ, "ccs");
		if (ccsJ) {
			for (int id = 0; id < 16; id++) {
				json_t *ccJ = json_array_get(ccsJ, id);
				if (ccJ)
					setLearnedCc(id, json_integer_value(ccJ));
			}
		}

		json_t *midiJ = json_object_get(rootJ, "midi");
		if (midiJ)
			midiOutput.fromJson(midiJ);
	}

	// METAMODULE
	size_t get_display_text(int led_id, std::span<char> text) override {
		std::string chars = "";

		for (auto i = 0; i < 16; i++) {
			if (i != 0) {
				if ((i % 4) == 0)
					chars += "\n";
				else
					chars += " ";
			}

			auto str = learnedCcs[i] >= 0 ? std::to_string(learnedCcs[i]) : "  -";

			for (auto sp = 0u; sp < (3 - str.length()); sp++)
				chars += " ";
			chars += str;
		}

		size_t chars_to_copy = std::min(text.size(), chars.length());
		std::copy(chars.begin(), chars.begin() + chars_to_copy, text.begin());

		return chars_to_copy;
	}
};

struct CV_MIDICCWidget : ModuleWidget {
	CV_MIDICCWidget(CV_MIDICC *module) {
		setModule(module);
		setPanel(createPanel(asset::system("res/Core/CV_MIDICC.svg"), asset::system("res/Core/CV_MIDICC-dark.svg")));

		addChild(createWidget<ThemedScrew>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ThemedScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ThemedScrew>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ThemedScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(8.189, 64.347)), module, CV_MIDICC::CC_INPUTS + 0));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(19.739, 64.347)), module, CV_MIDICC::CC_INPUTS + 1));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(31.289, 64.347)), module, CV_MIDICC::CC_INPUTS + 2));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(42.838, 64.347)), module, CV_MIDICC::CC_INPUTS + 3));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(8.189, 80.603)), module, CV_MIDICC::CC_INPUTS + 4));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(19.739, 80.603)), module, CV_MIDICC::CC_INPUTS + 5));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(31.289, 80.603)), module, CV_MIDICC::CC_INPUTS + 6));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(42.838, 80.603)), module, CV_MIDICC::CC_INPUTS + 7));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(8.189, 96.859)), module, CV_MIDICC::CC_INPUTS + 8));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(19.739, 96.859)), module, CV_MIDICC::CC_INPUTS + 9));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(31.289, 96.859)), module, CV_MIDICC::CC_INPUTS + 10));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(42.838, 96.859)), module, CV_MIDICC::CC_INPUTS + 11));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(8.189, 113.115)), module, CV_MIDICC::CC_INPUTS + 12));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(19.739, 113.115)), module, CV_MIDICC::CC_INPUTS + 13));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(31.289, 113.115)), module, CV_MIDICC::CC_INPUTS + 14));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(42.838, 113.115)), module, CV_MIDICC::CC_INPUTS + 15));

		// Changed for METAMODULE
		auto display = createWidget<MetaModule::VCVTextDisplay>(mm2px(Vec(1, 15)));
		display->box.size = mm2px(Vec(52, 56));
		display->firstLightId = 0;
		display->font = "RackCore/ShareTechMono_12.bin";
		display->color = Colors565::Yellow;
		addChild(display);
	}
};

Model *modelCV_MIDICC = createModel<CV_MIDICC, CV_MIDICCWidget>("CV-CC");

} // namespace core
} // namespace rack
