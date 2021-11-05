#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/defs/EnOscDefs.hh"
#include "CoreModules/moduleTypes.h"
#include "math.hh"

struct EnOscModule : CommModule {
	using Defs = EnOscDefs;

	EnOscModule()
	{
		configComm(Defs::NumKnobs, Defs::NumInJacks, Defs::NumOutJacks, 0);
		core = ModuleFactory::create(Defs::slug);
		selfID.typeID = Defs::slug;

		// outputJacks[LfoModule::LFO_OUTPUT]->scale = [](float f) { return f * 5.0f; };
	}
};

struct EnOscWidget : CommModuleWidget {
	using Defs = EnOscDefs;

	CommModule *mainModule;

	EnOscWidget(CommModule *module)
	{
		setModule(static_cast<Module *>(module));
		mainModule = module;

		std::string svg_name{Defs::svg_filename}; // clone it because asset::plugin requires a string
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, svg_name)));

		for (auto knob : Defs::Knobs) {
			addLabeledKnobMM(knob.long_name.data(), knob.id, Vec{knob.x, knob.y});
		}

		// for (auto injack : Defs::InJacks) {
		// addLabeledInputMM("FM", LfoModule::FM_INPUT, {0, 2});
		// }

		// for (auto outjack : Defs::OutJacks) {
		// addLabeledOutputMM("OUT", LfoModule::LFO_OUTPUT, {0, 0});
		// }

		addModuleTitle(Defs::slug.data());
	}
};

Model *modelEnOsc = createModel<EnOscModule, EnOscWidget>(EnOscDefs::slug.data());
