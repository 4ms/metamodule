#include "CommData.h"
#include "CommModule.h"
#include "CoreModules/moduleTypes.h"
#include "localPath.h"
#include "plugin.hpp"
#include "string.h"
#include <fstream>
#include <functional>
#include <iostream>

//Todo: rename this to Hub (or something?)
struct Expander : public CommModule {

	enum ParamIds {
		GET_INFO,
		MAIN_KNOB,
		NUM_PARAMS
	};
	enum InputIds {
		NUM_INPUTS
	};
	enum OutputIds {
		MAIN_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	CommData leftMessages[2];
	CommData rightMessages[2];

	std::string debugContents;
	std::string labelText = "";

	float currentValue = 0;
	float lastValue = 0;

	bool buttonAlreadyHandled = false;

	Expander()
	{
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		leftExpander.producerMessage = &leftMessages[0];
		leftExpander.consumerMessage = &leftMessages[1];
		rightExpander.producerMessage = &rightMessages[0];
		rightExpander.consumerMessage = &rightMessages[1];
	}

	void process(const ProcessArgs &args) override
	{
		if (leftExpander.module) {

			if (buttonJustPressed()) {
				sendMessageLeft(GetAllIDs);
			}

			auto message = messageReceivedFromLeft();

			if (message->messageType == SendingIDs) {
				labelText = "Received from left";
				updateDisplay();

				debugContents = "";
				for (auto recID : message->moduleData) {
					debugContents += "Module of type ";
					debugContents += ModuleFactory::getModuleSlug(recID.typeID);
					debugContents += " (" + ModuleFactory::getModuleTypeName(recID.typeID) + ") ";
					debugContents += "connected with ID " + std::to_string(recID.id) + "\n";
				}

				for (auto jData : message->jackData) {
					if (jData.connected == true) {
						debugContents += "Input jack " + std::to_string(jData.sendingJackId);
						debugContents += " on module " + std::to_string(jData.sendingModuleId);
						debugContents += " is connected to output jack " + std::to_string(jData.receivedJackId);
						debugContents += " on module " + std::to_string(jData.receivedModuleId) + "\n";
					}
					else {
						debugContents += "Input jack " + std::to_string(jData.sendingJackId) + " on module " + std::to_string(jData.sendingModuleId) + " not connected" + "\n";
					}
				}

				for (auto pData : message->paramData) {
					debugContents += "Parameter # " + std::to_string(pData.paramID) + " on module # " + std::to_string(pData.moduleID) + " value is " + std::to_string(pData.value) + "\n";
				}

				writeToDebugFile(debugFile, debugContents);

				message->messageType = NoMessage;
				message->moduleData.clear();
				message->jackData.clear();
				message->paramData.clear();
			}
		}
	}

	void writeToDebugFile(std::string inFile, std::string textToWrite)
	{
		std::ofstream myfile;
		myfile.open(inFile);
		myfile << textToWrite;
		myfile.close();
	}

	bool buttonJustPressed()
	{
		if (params[GET_INFO].getValue() > 0.f) {
			if (!buttonAlreadyHandled) {
				buttonAlreadyHandled = true;
				labelText = "Sending to left";
				updateDisplay();
				return true;
			}
		}
		else {
			buttonAlreadyHandled = false;
		}
		return false;
	}

	void sendMessageLeft(GlobalMessage message_type)
	{
		auto message = messageToSendLeft();
		message->messageType = message_type;
		leftExpander.module->rightExpander.messageFlipRequested = true;
	}
};

struct ExpanderWidget : ModuleWidget {

	Label *valueLabel;
	Label *valueLabel2;
	Expander *expModule;

	ExpanderWidget(Expander *module)
	{
		setModule(module);
		expModule = module;

		if (expModule != nullptr) {
			expModule->updateDisplay = [&]() {
				this->valueLabel->text = this->expModule->labelText;
			};
		}

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/hub.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<BefacoPush>(mm2px(Vec(23.292, 90.977)), module, Expander::GET_INFO));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(9.627, 17.01)), module, Expander::MAIN_KNOB));

		valueLabel = createWidget<Label>(mm2px(Vec(0, 40)));
		valueLabel->color = rack::color::BLACK;
		valueLabel->text = "exp_default";
		valueLabel->fontSize = 13;
		addChild(valueLabel);

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.859, 110.779)), module, Expander::MAIN_OUTPUT));
	}
};

Model *modelExpander = createModel<Expander, ExpanderWidget>("expanderModule");
