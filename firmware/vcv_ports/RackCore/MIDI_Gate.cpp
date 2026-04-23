#include "patch/patch_file.hh"
#include "plugin.hpp"

namespace rack
{
namespace core
{

struct MIDI_Gate : Module {
	enum ParamIds { NUM_PARAMS };
	enum InputIds { NUM_INPUTS };
	enum OutputIds { ENUMS(GATE_OUTPUTS, 16), NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	midi::InputQueue midiInput;

	/** True when a cell's gate is held. [cell][channel] */
	bool gates[16][16];
	/** Last velocity value of cell. [cell][channel] */
	uint8_t velocities[16][16];
	/** Triggered when a cell's note is played. [cell][channel] */
	dsp::PulseGenerator trigPulses[16][16];
	/** Cell ID in learn mode, or -1 if none. */
	int learningId;
	/** [cell] */
	int8_t learnedNotes[16];

	// Settings

	enum VelocityMode {
		FIXED_MODE,
		VELOCITY_MODE,
		AFTERTOUCH_MODE,
	};
	VelocityMode velocityMode;
	bool mpeMode;
	bool trigMode;

	MIDI_Gate() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		for (int i = 0; i < 16; i++)
			configOutput(GATE_OUTPUTS + i, string::f("Gate %d", i + 1));

		onReset();
	}

	void onReset() override {
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				learnedNotes[4 * y + x] = 36 + 4 * (3 - y) + x;
			}
		}
		learningId = -1;
		midiInput.reset();
		velocityMode = FIXED_MODE;
		mpeMode = false;
		trigMode = false;
		panic();
	}

	void panic() {
		for (int i = 0; i < 16; i++) {
			for (int c = 0; c < 16; c++) {
				gates[i][c] = false;
				velocities[i][c] = 127;
				trigPulses[i][c].reset();
			}
		}
	}

	void process(const ProcessArgs &args) override {
		midi::Message msg;
		while (midiInput.tryPop(&msg, args.frame)) {
			processMessage(msg);
		}

		int channels = mpeMode ? 16 : 1;

		for (int i = 0; i < 16; i++) {
			for (int c = 0; c < channels; c++) {
				bool pulse = trigPulses[i][c].process(args.sampleTime);
				bool gate = pulse || (!trigMode && gates[i][c]);
				float velocity = gate ? 1.f : 0.f;
				if (velocityMode != FIXED_MODE)
					velocity *= velocities[i][c] / 127.f;
				outputs[GATE_OUTPUTS + i].setVoltage(velocity * 10.f, c);
			}
			outputs[GATE_OUTPUTS + i].setChannels(channels);
		}
	}

	void processMessage(const midi::Message &msg) {
		switch (msg.getStatus()) {
			// note off
			case 0x8: {
				releaseNote(msg.getChannel(), msg.getNote());
			} break;
			// note on
			case 0x9: {
				uint8_t velocity = msg.getValue();
				if (velocity > 0) {
					pressNote(msg.getChannel(), msg.getNote(), velocity);
				} else {
					// Note-on event with velocity 0 is an alternative for note-off event.
					releaseNote(msg.getChannel(), msg.getNote());
				}
			} break;
			// polyphonic pressure/aftertouch
			case 0xa: {
				if (velocityMode == AFTERTOUCH_MODE) {
					uint8_t c = mpeMode ? msg.getChannel() : 0;
					uint8_t note = msg.getNote();
					uint8_t velocity = msg.getValue();
					for (int i = 0; i < 16; i++) {
						if (learnedNotes[i] == note) {
							velocities[i][c] = velocity;
						}
					}
				}
			} break;
			// channel pressure/aftertouch
			case 0xd: {
				if (velocityMode == AFTERTOUCH_MODE) {
					uint8_t c = mpeMode ? msg.getChannel() : 0;
					uint8_t velocity = msg.getNote();
					for (int i = 0; i < 16; i++) {
						velocities[i][c] = velocity;
					}
				}
			} break;
			default:
				break;
		}
	}

	void pressNote(uint8_t channel, uint8_t note, uint8_t vel) {
		int c = mpeMode ? channel : 0;
		// Learn
		if (learningId >= 0) {
			setLearnedNote(learningId, note);
			learningId = -1;
		}
		// Find id
		for (int i = 0; i < 16; i++) {
			if (learnedNotes[i] == note) {
				gates[i][c] = true;
				if (velocityMode == VELOCITY_MODE)
					velocities[i][c] = vel;
				trigPulses[i][c].trigger(1e-3f);
			}
		}
	}

	void releaseNote(uint8_t channel, uint8_t note) {
		int c = mpeMode ? channel : 0;
		// Find id
		for (int i = 0; i < 16; i++) {
			if (learnedNotes[i] == note) {
				gates[i][c] = false;
			}
		}
	}

	void setLearnedNote(int id, int8_t note) {
		// Unset IDs of similar note
		if (note >= 0) {
			for (int i = 0; i < 16; i++) {
				if (i != id && learnedNotes[i] == note) {
					learnedNotes[i] = -1;
				}
			}
		}
		learnedNotes[id] = note;
	}

	json_t *dataToJson() override {
		json_t *rootJ = json_object();

		json_t *notesJ = json_array();
		for (int i = 0; i < 16; i++) {
			json_array_append_new(notesJ, json_integer(learnedNotes[i]));
		}
		json_object_set_new(rootJ, "notes", notesJ);

		json_object_set_new(rootJ, "velocity", json_integer(velocityMode));

		json_object_set_new(rootJ, "mpeMode", json_boolean(mpeMode));

		json_object_set_new(rootJ, "trigMode", json_boolean(trigMode));

		json_object_set_new(rootJ, "midi", midiInput.toJson());

		return rootJ;
	}

	void dataFromJson(json_t *rootJ) override {
		json_t *notesJ = json_object_get(rootJ, "notes");
		if (notesJ) {
			for (int i = 0; i < 16; i++) {
				json_t *noteJ = json_array_get(notesJ, i);
				if (noteJ)
					setLearnedNote(i, json_integer_value(noteJ));
			}
		}

		json_t *velocityJ = json_object_get(rootJ, "velocity");
		// Boolean in Rack <=v2.6.4
		if (json_is_true(velocityJ))
			velocityMode = VELOCITY_MODE;
		else if (json_is_integer(velocityJ))
			velocityMode = VelocityMode(json_integer_value(velocityJ));

		json_t *mpeModeJ = json_object_get(rootJ, "mpeMode");
		if (mpeModeJ)
			mpeMode = json_boolean_value(mpeModeJ);

		json_t *trigModeJ = json_object_get(rootJ, "trigMode");
		if (trigModeJ)
			trigMode = json_boolean_value(trigModeJ);

		json_t *midiJ = json_object_get(rootJ, "midi");
		if (midiJ)
			midiInput.fromJson(midiJ);
	}

	// METAMODULE
	static std::string note_string(int8_t note) {
		if (note < 0)
			return "--";
		static const std::string noteNames[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
		int oct = note / 12 - 1;
		int semi = note % 12;
		return noteNames[semi] + std::to_string(oct);
	}

	size_t get_display_text(int led_id, std::span<char> text) override {
		std::string chars = "";

		for (auto i = 0; i < 16; i++) {
			chars += (i == 0) ? "" : ((i % 4) == 0) ? "\n" : " ";

			auto note = learnedNotes[i];
			std::string str = note_string(note).substr(0, 3);

			for (auto len = str.length(); len < 3; len++)
				chars += " ";
			chars += str;
		}

		size_t chars_to_copy = std::min(text.size(), chars.length());
		std::copy(chars.begin(), chars.begin() + chars_to_copy, text.begin());

		return chars_to_copy;
	}
};

struct MIDI_GateWidget : ModuleWidget {
	MIDI_GateWidget(MIDI_Gate *module) {
		setModule(module);
		setPanel(createPanel(asset::system("res/Core/MIDI_Gate.svg"), asset::system("res/Core/MIDI_Gate-dark.svg")));

		addChild(createWidget<ThemedScrew>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ThemedScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ThemedScrew>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ThemedScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(8, 78)), module, MIDI_Gate::GATE_OUTPUTS + 0));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(20, 78)), module, MIDI_Gate::GATE_OUTPUTS + 1));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(32, 78)), module, MIDI_Gate::GATE_OUTPUTS + 2));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(43, 78)), module, MIDI_Gate::GATE_OUTPUTS + 3));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(8, 91)), module, MIDI_Gate::GATE_OUTPUTS + 4));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(20, 91)), module, MIDI_Gate::GATE_OUTPUTS + 5));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(32, 91)), module, MIDI_Gate::GATE_OUTPUTS + 6));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(43, 91)), module, MIDI_Gate::GATE_OUTPUTS + 7));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(8, 104)), module, MIDI_Gate::GATE_OUTPUTS + 8));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(20, 104)), module, MIDI_Gate::GATE_OUTPUTS + 9));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(32, 104)), module, MIDI_Gate::GATE_OUTPUTS + 10));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(43, 104)), module, MIDI_Gate::GATE_OUTPUTS + 11));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(8, 116)), module, MIDI_Gate::GATE_OUTPUTS + 12));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(20, 116)), module, MIDI_Gate::GATE_OUTPUTS + 13));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(32, 116)), module, MIDI_Gate::GATE_OUTPUTS + 14));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(43, 116)), module, MIDI_Gate::GATE_OUTPUTS + 15));

		// Changed for METAMODULE
		auto display = createWidget<MetaModule::VCVTextDisplay>(mm2px(Vec(1, 15)));
		display->box.size = mm2px(Vec(52, 64));
		display->firstLightId = 0;
		display->font = "RackCore/ShareTechMono_12.bin";
		display->color = Colors565::Yellow;
		addChild(display);
	}

	void appendContextMenu(Menu *menu) override {
		MIDI_Gate *module = dynamic_cast<MIDI_Gate *>(this->module);

		menu->addChild(new MenuSeparator);

		menu->addChild(createIndexPtrSubmenuItem("Output type",
												 {
													 "Gates",
													 "Triggers",
												 },
												 &module->trigMode));

		menu->addChild(createIndexPtrSubmenuItem("Output amplitude",
												 {
													 "10V",
													 "Velocity",
													 "Aftertouch",
												 },
												 &module->velocityMode));

		menu->addChild(createBoolPtrMenuItem("MPE mode", "", &module->mpeMode));

		menu->addChild(new MenuSeparator);

		menu->addChild(createMenuItem("Reset MIDI (Panic)", "", [=]() { module->panic(); }));

		// METAMODULE: add MIDI Channel to context menu:
		menu->addChild(new MenuSeparator);
		menu->addChild(createSubmenuItem(
			"MIDI channel",
			[=] {
				auto chan = module->midiInput.getChannel();
				return chan < 0 ? "Omni" : std::to_string(chan + 1);
			},
			[=](Menu *menu) {
				menu->addChild(createCheckMenuItem(
					"Omni",
					"",
					[=]() { return module->midiInput.getChannel() == -1; },
					[=]() { module->midiInput.setChannel(-1); }));
				for (int c = 0; c < 16; c++) {
					menu->addChild(createCheckMenuItem(
						string::f("Channel %d", c + 1),
						"",
						[=]() { return module->midiInput.getChannel() == c; },
						[=]() { module->midiInput.setChannel(c); }));
				}
			}));

		menu->addChild(new MenuSeparator);

		for (auto cell = 0; cell < 16; cell++) {
			menu->addChild(createSubmenuItem(
				"Cell " + std::to_string(cell + 1) + " ",
				[=] { return MIDI_Gate::note_string(module->learnedNotes[cell]); },
				[=](Menu *menu) {
					for (int note = 0; note < 128; note++) {
						menu->addChild(createCheckMenuItem(
							MIDI_Gate::note_string(note),
							"",
							[=]() { return module->learnedNotes[cell] == note; },
							[=]() {
								module->setLearnedNote(cell, note);
								MetaModule::Patch::mark_patch_modified();
							}));
					}
				}));
		}
	}
};

// Use legacy slug for compatibility
Model *modelMIDI_Gate = createModel<MIDI_Gate, MIDI_GateWidget>("MIDITriggerToCVInterface");

} // namespace core
} // namespace rack
