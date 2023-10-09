#include "mapping/midi_modules.hh"
#include "mapping/JackMap.hh"
#include "mapping/module_directory.hh"
#include "patch/midi_def.hh"
#include <rack.hpp>

namespace MetaModule::MIDI
{

std::optional<MidiCVSettings> readMidiCVModule(int64_t module_id) {
	auto context = rack::contextGet();
	auto engine = context->engine;
	auto module = engine->getModule(module_id);
	if (!module)
		return std::nullopt;

	json_t *rootJ = module->dataToJson();
	json_t *pwRangeJ = json_object_get(rootJ, "pwRange");
	json_t *channelsJ = json_object_get(rootJ, "channels");
	json_t *polyModeJ = json_object_get(rootJ, "polyMode");

	MidiCVSettings settings;
	settings.pwRange = pwRangeJ ? json_number_value(pwRangeJ) : -1;
	settings.channels = channelsJ ? json_integer_value(channelsJ) : 1;
	auto polyMode = polyModeJ ? json_integer_value(polyModeJ) : 0;
	if (polyMode >= 0 && polyMode <= 3)
		settings.polyMode = static_cast<MidiCVSettings::PolyMode>(polyMode);
	else
		settings.polyMode = MidiCVSettings::ROTATE_MODE;

	json_decref(rootJ);
	return settings;
}

std::optional<MidiGateSettings> readMidiGateModule(int64_t module_id) {
	auto context = rack::contextGet();
	auto engine = context->engine;
	auto module = engine->getModule(module_id);
	if (!module)
		return std::nullopt;

	MidiGateSettings settings;

	json_t *rootJ = module->dataToJson();
	json_t *notesJ = json_object_get(rootJ, "notes");
	json_t *velocityJ = json_object_get(rootJ, "velocity");
	json_t *mpeModeJ = json_object_get(rootJ, "mpeMode");

	if (!notesJ)
		return std::nullopt;

	for (int i = 0; auto &note : settings.notes) {
		json_t *noteJ = json_array_get(notesJ, i);
		if (noteJ) {
			note = json_integer_value(noteJ);
		}
		i++;
	}
	settings.velocity_mode = velocityJ ? json_boolean_value(velocityJ) : false;
	settings.mpe_mode = mpeModeJ ? json_boolean_value(mpeModeJ) : false;

	json_decref(rootJ);

	return settings;
}

std::optional<MidiCCCVSettings> readMidiCCCVModule(int64_t module_id) {
	auto context = rack::contextGet();
	auto engine = context->engine;
	auto module = engine->getModule(module_id);
	if (!module)
		return std::nullopt;

	json_t *rootJ = module->dataToJson();
	json_decref(rootJ);

	MidiCCCVSettings settings;

	return settings;
}

std::optional<MidiCCKnobSettings> readMidiMapModule(int64_t module_id) {
	auto context = rack::contextGet();
	auto engine = context->engine;
	auto module = engine->getModule(module_id);
	if (!module)
		return std::nullopt;

	json_t *rootJ = module->dataToJson();
	json_decref(rootJ);

	MidiCCKnobSettings settings;

	return settings;
}

} // namespace MetaModule::MIDI

// namespace MetaModule::MIDIMapping
// {

// std::optional<MidiCVSettings> mapMidiToCV(CableMap *cable) {
// 	auto context = rack::contextGet();
// 	auto engine = context->engine;
// 	auto module = engine->getModule(cable->sendingModuleId);
// 	if (!module)
// 		return std::nullopt;

// 	json_t *rootJ = module->dataToJson();
// 	json_t *pwRangeJ = json_object_get(rootJ, "pwRange");
// 	json_t *channelsJ = json_object_get(rootJ, "channels");
// 	json_t *polyModeJ = json_object_get(rootJ, "polyMode");
// 	json_decref(rootJ);

// 	MidiCVSettings settings;
// 	settings.pwRange = pwRangeJ ? json_number_value(pwRangeJ) : -1;
// 	settings.channels = channelsJ ? json_integer_value(channelsJ) : 1;
// 	auto polyMode = polyModeJ ? json_integer_value(polyModeJ) : 0;
// 	if (polyMode >= 0 && polyMode <= 3)
// 		settings.polyMode = static_cast<MidiCVSettings::PolyMode>(polyMode);
// 	else
// 		settings.polyMode = MidiCVSettings::ROTATE_MODE;

// 	// Translate VCV jack id on MidiCV module to
// 	// Metamodule Midi Mapping panel ID
// 	uint16_t MapIds[12]{MidiMonoNoteJack,
// 						MidiMonoGateJack,
// 						MidiVelocityJack,
// 						MidiAftertouchJack,
// 						MidiPitchWheelJack,
// 						MidiModWheelJack,
// 						MidiRetriggerJack,
// 						MidiClockJack,
// 						MidiClockDivJack,
// 						MidiStartJack,
// 						MidiStopJack,
// 						MidiContinueJack};
// 	if (cable->sendingJackId < 12 && cable->sendingJackId >= 0)
// 		cable->sendingJackId = MapIds[cable->sendingJackId];

// 	return settings;
// }

// std::optional<MidiGateSettings> mapMidiToGate(CableMap *cable) {
// 	auto context = rack::contextGet();
// 	auto engine = context->engine;
// 	auto module = engine->getModule(cable->sendingModuleId);
// 	if (!module)
// 		return std::nullopt;

// 	MidiGateSettings settings;

// 	json_t *rootJ = module->dataToJson();
// 	json_t *notesJ = json_object_get(rootJ, "notes");
// 	json_t *velocityJ = json_object_get(rootJ, "velocity");
// 	json_t *mpeModeJ = json_object_get(rootJ, "mpeMode");
// 	json_decref(rootJ);

// 	if (!notesJ)
// 		return std::nullopt;

// 	for (int i = 0; auto &note : settings.notes) {
// 		json_t *noteJ = json_array_get(notesJ, i);
// 		if (noteJ)
// 			note = json_integer_value(noteJ);
// 		i++;
// 	}
// 	settings.velocity_mode = velocityJ ? json_boolean_value(velocityJ) : false;
// 	settings.mpe_mode = mpeModeJ ? json_boolean_value(mpeModeJ) : false;

// 	return settings;
// }

// std::optional<MidiCCCVSettings> mapMidiCCToCV(CableMap *cable) {
// 	auto context = rack::contextGet();
// 	auto engine = context->engine;
// 	auto module = engine->getModule(cable->sendingModuleId);
// 	if (!module)
// 		return std::nullopt;

// 	json_t *rootJ = module->dataToJson();
// 	json_decref(rootJ);

// 	MidiCCCVSettings settings;

// 	return settings;
// }

// std::optional<MidiCCKnobSettings> mapMidiCCToKnob(int64_t module_id) {
// 	auto context = rack::contextGet();
// 	auto engine = context->engine;
// 	auto module = engine->getModule(module_id);
// 	if (!module)
// 		return std::nullopt;

// 	json_t *rootJ = module->dataToJson();
// 	json_decref(rootJ);

// 	MidiCCKnobSettings settings;

// 	return settings;
// }

// } // namespace MetaModule::MIDIMapping
