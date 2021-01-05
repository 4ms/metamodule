// #include "CommData.h"
#include "plugin.hpp"

struct AdjTest : Module {

	enum ParamIds {
		MAIN_KNOB,
		NUM_PARAMS
	};
	enum InputIds {
		NUM_INPUTS
	};
	enum OutputIds {
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	std::string labelText = "";
	std::string recLabelText = "receive";

	std::function<void(void)> updateDisplay;

	// CommData *recData = nullptr;

	// CommData tempData;

	// ModuleID selfID;

	// CommData leftMessages[2];
	AdjTest()
	{
		// leftExpander.producerMessage = &leftMessages[0];
		// leftExpander.consumerMessage = &leftMessages[1];
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		// selfID.type = 3;
	}

	void process(const ProcessArgs &args) override
	{
		// selfID.id = this->id;

		/* todo: fix this or remove it  
		if (rightExpander.module) {
			// Get message from right expander
			// Write message
			auto message = static_cast<CommData *>(rightExpander.module->leftExpander.producerMessage);

			if (tempData.moduleData.size() > 0 && leftExpander.module) {
				message->moduleData = tempData.moduleData;
			}

			message->moduleData.push_back(selfID);

			// TODO : push this modules data and received data

			// Flip messages at the end of the timestep
			rightExpander.module->leftExpander.messageFlipRequested = true;
		}

		if (leftExpander.module) {
			// Get consumer message
			recData = static_cast<CommData *>(leftExpander.consumerMessage);

			tempData.moduleData = recData->moduleData;

			recLabelText = std::to_string(recData->moduleData.size());

			updateDisplay();

			recData->moduleData.clear();
		}
		else {
			recLabelText = "na";
			updateDisplay();
		}
		*/
	}
};

struct AdjTestWidget : ModuleWidget {

	AdjTest *mainModule;

	Label *valueLabel;
	Label *recLabel;

	AdjTestWidget(AdjTest *module)
	{
		setModule(module);
		mainModule = module;

		if (mainModule != nullptr) {
			mainModule->updateDisplay = [&]() {
				this->recLabel->text = this->mainModule->recLabelText;
			};
		}

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/adjTest.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(9.627, 17.01)), module, AdjTest::MAIN_KNOB));

		valueLabel = createWidget<Label>(mm2px(Vec(0, 40)));
		valueLabel->color = rack::color::BLACK;
		valueLabel->text = "default";
		valueLabel->fontSize = 15;
		addChild(valueLabel);

		recLabel = createWidget<Label>(mm2px(Vec(0, 80)));
		recLabel->color = rack::color::BLACK;
		recLabel->text = "receive";
		recLabel->fontSize = 15;
		addChild(recLabel);
	}
};

Model *modelAdjTest = createModel<AdjTest, AdjTestWidget>("adjTest");
