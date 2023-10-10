#include "mapping/midi_modules.hh"
#include "mapping/module_directory.hh"
#include <rack.hpp>

namespace MetaModule::MIDIMapping
{

std::vector<MappedKnob> mapMidiMaps() {
	std::vector<MappedKnob> m;

	return m;
}

std::vector<MappedInputJack> mapMidiToCV(rack::Module *module) {
	std::vector<MappedInputJack> maps;

	auto rootJ = module->dataToJson();
	json_t *pwRangeJ = json_object_get(rootJ, "pwRange");
	auto pwRange = pwRangeJ ? json_number_value(pwRangeJ) : -1;

	json_t *channelsJ = json_object_get(rootJ, "channels");
	auto channels = channelsJ ? json_integer_value(channelsJ) : 1;

	json_t *polyModeJ = json_object_get(rootJ, "polyMode");
	auto polyMode = polyModeJ ? json_integer_value(polyModeJ) : 0;

	printf("pwRange %f, polyMode %lld, channels %lld\n", pwRange, polyMode, channels);

	auto context = rack::contextGet();
	auto engine = context->engine;

	for (auto cableID : engine->getCableIds()) {
		auto cable = engine->getCable(cableID);

		if (cable->outputModule != module)
			continue;

		if (!ModuleDirectory::isInPlugin(cable->inputModule))
			continue;

		// Mapping map;
		// map.moduleId = cable->inputModule->id;
		// map.paramId = cable->inputId;
		// map.range_min = 0.f;
		// map.range_max = 1.f;
		// // TODO: depends on poly mode, etc...
		// uint16_t panelJackId = (cable->outputId == 0) ? MidiMonoNoteJack : MidiMonoGateJack;
		// std::vector<Jack> ins{{.module_id = cable->inputModule->id, .jack_id = cable->inputId}};
		// maps.emplace_back(MappedInputJack{
		// 	.panel_jack_id = panelJackId,
		// 	.ins = ins,
		// 	.alias_name = "MIDICV",
		// });
	}

	// json_t *clockDivisionJ = json_object_get(rootJ, "clockDivision");
	// if (clockDivisionJ)
	// 	clockDivision = json_integer_value(clockDivisionJ);

	// json_t *lastPitchJ = json_object_get(rootJ, "lastPitch");
	// if (lastPitchJ)
	// 	pws[0] = json_integer_value(lastPitchJ);

	// json_t *lastModJ = json_object_get(rootJ, "lastMod");
	// if (lastModJ)
	// 	mods[0] = json_integer_value(lastModJ);

	return maps;
}

} // namespace MetaModule::MIDIMapping
