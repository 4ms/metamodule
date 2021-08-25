#include "CommData.h"
#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/moduleTypes.h"
#include "CoreModules/panel_medium_defs.hh"
#include "plugin.hpp"
#include "util/math.hh"

struct HubMedium : public CommModule {

	enum ParamIds { NUM_PARAMS = PanelDef::NumPot + PanelDef::NumMetaRgbButton };
	enum InputIds { NUM_INPUTS = PanelDef::NumAudioIn + PanelDef::NumGateIn };
	enum OutputIds { NUM_OUTPUTS = PanelDef::NumAudioOut + PanelDef::NumGateOut };
	enum LightIds { NUM_LIGHTS = 0 };

	HubMedium()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		selfID.typeID = "PANEL_MED";
	}

	void process(const ProcessArgs &args) override {}
};

struct HubMediumWidget : CommModuleWidget {

	HubMedium *mainModule;

	Label *valueLabel;
	Label *recLabel;

	HubMediumWidget(HubMedium *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/meta-module-medium.svg")));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>((Vec(22.31, 43.16)), module, 0));

		addParam(createParamCentered<RoundBlackKnob>((Vec(64.57, 53.24)), module, 1));
		// addSmallLabeledKnobPx("x", 1, {64.57, 53.24});
		addParam(createParamCentered<RoundBlackKnob>((Vec(27.94, 88.42)), module, 2));
		addParam(createParamCentered<RoundBlackKnob>((Vec(343.34, 92.99)), module, 3));
		addParam(createParamCentered<RoundBlackKnob>((Vec(295.26, 117.58)), module, 4));
		addParam(createParamCentered<RoundBlackKnob>((Vec(64.57, 120.56)), module, 5));
		addParam(createParamCentered<RoundBlackKnob>((Vec(34.23, 166.3)), module, 6));
		addParam(createParamCentered<RoundBlackKnob>((Vec(341.35, 166.41)), module, 7));
		addParam(createParamCentered<RoundBlackKnob>((Vec(94.21, 193.61)), module, 8));
		addParam(createParamCentered<RoundBlackKnob>((Vec(280.72, 193.68)), module, 9));
		addParam(createParamCentered<RoundBlackKnob>((Vec(155.15, 213.81)), module, 10));
		addParam(createParamCentered<RoundBlackKnob>((Vec(220.04, 214.26)), module, 11));
		addParam(createParamCentered<RoundBlackKnob>((Vec(44.14, 226.16)), module, 12));

		addInput(createInputCentered<PJ301MPort>((Vec(22.9, 274.7)), module, 0));
		addInput(createInputCentered<PJ301MPort>((Vec(66.42, 274.7)), module, 1));
		addInput(createInputCentered<PJ301MPort>((Vec(109.61, 282.75)), module, 2));
		addInput(createInputCentered<PJ301MPort>((Vec(153.13, 282.75)), module, 3));
		addInput(createInputCentered<PJ301MPort>((Vec(36.34, 324.15)), module, 4));
		addInput(createInputCentered<PJ301MPort>((Vec(79.86, 324.15)), module, 5));
		addInput(createInputCentered<PJ301MPort>((Vec(122.6, 324.18)), module, 6));
		addInput(createInputCentered<PJ301MPort>((Vec(166.12, 324.18)), module, 7));

		addOutput(createOutputCentered<PJ301MPort>((Vec(352.74, 219.83)), module, 0));
		addOutput(createOutputCentered<PJ301MPort>((Vec(316.22, 238.83)), module, 1));
		addOutput(createOutputCentered<PJ301MPort>((Vec(308.9, 282.15)), module, 2));
		addOutput(createOutputCentered<PJ301MPort>((Vec(352.42, 282.15)), module, 3));
		addOutput(createOutputCentered<PJ301MPort>((Vec(222.16, 282.79)), module, 4));
		addOutput(createOutputCentered<PJ301MPort>((Vec(265.68, 282.79)), module, 5));
		addOutput(createOutputCentered<PJ301MPort>((Vec(209.28, 324.18)), module, 6));
		addOutput(createOutputCentered<PJ301MPort>((Vec(252.8, 324.18)), module, 7));
		addOutput(createOutputCentered<PJ301MPort>((Vec(295.21, 324.2)), module, 8));
		addOutput(createOutputCentered<PJ301MPort>((Vec(338.73, 324.2)), module, 9));
	}
};

Model *modelHubMedium = createModel<HubMedium, HubMediumWidget>("PANEL_MED");
