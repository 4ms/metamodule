#include "midi/midi_message.hh"
#include "plugin.hpp"
#include "util/circular_buffer.hh"

// #define DEMO_MIDI_OUT
#ifdef DEMO_MIDI_OUT
#include "../../src/midi/midi_test_data.hh"
#endif

namespace rack
{
namespace core
{

struct MidiOutput : dsp::MidiGenerator<PORT_MAX_CHANNELS>, midi::Output {
	CircularBuffer<midi::Message, 2> msg_history;

	void onMessage(const midi::Message &message) override {
		Output::sendMessage(message);

		midi::Message msg = message;
		if (msg.getStatus() != 0xF)
			msg.setChannel(getChannel());

		if (msg.bytes[0] < 0xFE && msg.bytes[0] != 0xF8)
			msg_history.put(msg);
	}

	void reset() {
		Output::reset();
		MidiGenerator::reset();
	}
};

struct CV_MIDI : Module {
	enum ParamIds { NUM_PARAMS };
	enum InputIds {
		PITCH_INPUT,
		GATE_INPUT,
		VEL_INPUT,
		AFT_INPUT,
		PW_INPUT,
		MW_INPUT,
		CLK_INPUT,
		VOL_INPUT,
		PAN_INPUT,
		START_INPUT,
		STOP_INPUT,
		CONTINUE_INPUT,
		NUM_INPUTS
	};
	enum OutputIds { NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	MidiOutput midiOutput;
	dsp::Timer rateLimiterTimer;

	CV_MIDI() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configInput(PITCH_INPUT, "1V/octave pitch");
		configInput(GATE_INPUT, "Gate");
		configInput(VEL_INPUT, "Velocity");
		configInput(AFT_INPUT, "Aftertouch");
		configInput(PW_INPUT, "Pitch wheel");
		configInput(MW_INPUT, "Mod wheel");
		configInput(CLK_INPUT, "Clock");
		configInput(VOL_INPUT, "Volume");
		configInput(PAN_INPUT, "Pan");
		configInput(START_INPUT, "Start trigger");
		configInput(STOP_INPUT, "Stop trigger");
		configInput(CONTINUE_INPUT, "Continue trigger");
		onReset();

#ifdef DEMO_MIDI_OUT
		fill_midi_data();
#endif
	}

	void onReset() override {
		midiOutput.reset();
	}

	static inline unsigned tick = 0;
	static inline unsigned last_msg = 0;
	static inline unsigned md_idx = 0;

	void process(const ProcessArgs &args) override {
#ifdef DEMO_MIDI_OUT
		tick++;
		if (tick - last_msg > 300) {
			if (md_idx >= MidiDemoData.size())
				md_idx = 0;
			midiOutput.onMessage(MidiDemoData[md_idx]);
			md_idx++;
			last_msg = tick;
		}
#endif

		// MIDI baud rate is 31250 b/s, or 3125 B/s.
		// CC messages are 3 bytes, so we can send a maximum of 1041 CC messages per second.
		// Since multiple CCs can be generated, play it safe and limit the CC rate to 200 Hz.
		const float rateLimiterPeriod = 1 / 200.f;
		bool rateLimiterTriggered = (rateLimiterTimer.process(args.sampleTime) >= rateLimiterPeriod);
		if (rateLimiterTriggered)
			rateLimiterTimer.time -= rateLimiterPeriod;

		midiOutput.setFrame(args.frame);

		for (int c = 0; c < inputs[PITCH_INPUT].getChannels(); c++) {
			int vel = (int)std::round(inputs[VEL_INPUT].getNormalPolyVoltage(10.f * 100 / 127, c) / 10.f * 127);
			vel = clamp(vel, 0, 127);
			midiOutput.setVelocity(vel, c);

			int note = (int)std::round(inputs[PITCH_INPUT].getVoltage(c) * 12.f + 60.f);
			note = clamp(note, 0, 127);
			bool gate = inputs[GATE_INPUT].getPolyVoltage(c) >= 1.f;
			midiOutput.setNoteGate(note, gate, c);

			int aft = (int)std::round(inputs[AFT_INPUT].getPolyVoltage(c) / 10.f * 127);
			aft = clamp(aft, 0, 127);
			midiOutput.setKeyPressure(aft, c);
		}

		if (rateLimiterTriggered) {
			int pw = (int)std::round((inputs[PW_INPUT].getVoltage() + 5.f) / 10.f * 0x4000);
			pw = clamp(pw, 0, 0x3fff);
			midiOutput.setPitchWheel(pw);

			int mw = (int)std::round(inputs[MW_INPUT].getVoltage() / 10.f * 127);
			mw = clamp(mw, 0, 127);
			midiOutput.setModWheel(mw);

			int vol = (int)std::round(inputs[VOL_INPUT].getNormalVoltage(10.f) / 10.f * 127);
			vol = clamp(vol, 0, 127);
			midiOutput.setVolume(vol);

			int pan = (int)std::round((inputs[PAN_INPUT].getVoltage() + 5.f) / 10.f * 127);
			pan = clamp(pan, 0, 127);
			midiOutput.setPan(pan);
		}

		bool clk = inputs[CLK_INPUT].getVoltage() >= 1.f;
		midiOutput.setClock(clk);

		bool start = inputs[START_INPUT].getVoltage() >= 1.f;
		midiOutput.setStart(start);

		bool stop = inputs[STOP_INPUT].getVoltage() >= 1.f;
		midiOutput.setStop(stop);

		bool cont = inputs[CONTINUE_INPUT].getVoltage() >= 1.f;
		midiOutput.setContinue(cont);
	}

	json_t *dataToJson() override {
		json_t *rootJ = json_object();
		json_object_set_new(rootJ, "midi", midiOutput.toJson());
		return rootJ;
	}

	void dataFromJson(json_t *rootJ) override {
		json_t *midiJ = json_object_get(rootJ, "midi");
		if (midiJ)
			midiOutput.fromJson(midiJ);
	}

	// METAMODULE
	size_t get_display_text(int led_id, std::span<char> text) override {
		std::string chars = "";

		for (auto i = 0u; i < midiOutput.msg_history.count(); i++) {
			auto msg = midiOutput.msg_history.peek(i);
			if (i != 0)
				chars += "\n\n";
			chars += MetaModule::Midi::toPrettyMultilineString(msg.bytes);
		}

		size_t chars_to_copy = std::min(text.size(), chars.length());
		std::copy(chars.begin(), chars.begin() + chars_to_copy, text.begin());

		return chars_to_copy;
	}
};

struct CV_MIDIPanicItem : MenuItem {
	CV_MIDI *module;
	void onAction(const ActionEvent &e) override {
		module->midiOutput.panic();
	}
};

struct CV_MIDIWidget : ModuleWidget {
	CV_MIDIWidget(CV_MIDI *module) {
		setModule(module);
		setPanel(createPanel(asset::system("res/Core/CV_MIDI.svg"), asset::system("res/Core/CV_MIDI-dark.svg")));

		addChild(createWidget<ThemedScrew>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ThemedScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ThemedScrew>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ThemedScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(7.906, 64.347)), module, CV_MIDI::PITCH_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(20.249, 64.347)), module, CV_MIDI::GATE_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(32.591, 64.347)), module, CV_MIDI::VEL_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(7.906, 80.603)), module, CV_MIDI::AFT_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(20.249, 80.603)), module, CV_MIDI::PW_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(32.591, 80.603)), module, CV_MIDI::MW_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(7.906, 96.859)), module, CV_MIDI::CLK_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(20.249, 96.707)), module, CV_MIDI::VOL_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(32.591, 96.859)), module, CV_MIDI::PAN_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(7.906, 113.115)), module, CV_MIDI::START_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(20.249, 113.115)), module, CV_MIDI::STOP_INPUT));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(32.591, 112.975)), module, CV_MIDI::CONTINUE_INPUT));

		// Changed for METAMODULE
		auto display = createWidget<MetaModule::VCVTextDisplay>(mm2px(Vec(4, 12)));
		display->box.size = mm2px(Vec(32, 42));
		display->firstLightId = 0;
		display->font = "Default_10";
		display->color = Colors565::Yellow;
		addChild(display);
	}

	void appendContextMenu(Menu *menu) override {
		CV_MIDI *module = dynamic_cast<CV_MIDI *>(this->module);

		if (!module)
			return;

		menu->addChild(new MenuSeparator);

		// METAMODULE: add MIDI channel selection to menu
		menu->addChild(createSubmenuItem(
			"MIDI channel",
			[=] {
				auto chan = module->midiOutput.getChannel();
				return chan < 0 ? "Omni" : std::to_string(chan + 1);
			},
			[=](Menu *menu) {
				for (int c = 0; c < 16; c++) {
					menu->addChild(createCheckMenuItem(
						string::f("Channel %d", c + 1),
						"",
						[=]() { return module->midiOutput.getChannel() == c; },
						[=]() { module->midiOutput.setChannel(c); }));
				}
			}));

		menu->addChild(createMenuItem("Panic", "", [=]() { module->midiOutput.panic(); }));
	}
};

Model *modelCV_MIDI = createModel<CV_MIDI, CV_MIDIWidget>("CV-MIDI");

} // namespace core
} // namespace rack
