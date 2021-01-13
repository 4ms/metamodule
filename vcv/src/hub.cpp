#include "CommData.h"
#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/moduleTypes.h"
#include "localPath.h"
#include "plugin.hpp"
#include "string.h"
#include <fstream>
#include <functional>
#include <iostream>

// Todo: rename this to Hub (or something?)
struct Expander : public CommModule {

	enum ParamIds {
		ENUMS(KNOBS, 8),
		GET_INFO,
		NUM_PARAMS,
	};
	enum InputIds {
		AUDIO_IN_L,
		AUDIO_IN_R,
		CV_1,
		CV_2,
		CV_3,
		CV_4,
		NUM_INPUTS,
	};
	enum OutputIds {
		AUDIO_OUT_L,
		AUDIO_OUT_R,
		NUM_OUTPUTS,
	};
	enum LightIds {
		NUM_LIGHTS,
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
				if (startMessageLeft(GetAllIDs) != nullptr)
					finishMessageLeft();
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
					} else {
						debugContents += "Input jack " + std::to_string(jData.sendingJackId) + " on module " +
										 std::to_string(jData.sendingModuleId) + " not connected" + "\n";
					}
				}

				for (auto pData : message->paramData) {
					debugContents += "Parameter # " + std::to_string(pData.paramID) + " on module # " +
									 std::to_string(pData.moduleID) + " value is " + std::to_string(pData.value) + "\n";
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
		} else {
			buttonAlreadyHandled = false;
		}
		return false;
	}

	CommData *startMessageLeft(GlobalMessage message_type)
	{
		if (leftExpander.moduleId != CommModule::CommModuleExpanderID)
			return nullptr;
		auto message = messageToSendLeft();
		message->messageType = message_type;
		return message;
	}

	void finishMessageLeft()
	{
		leftExpander.module->rightExpander.messageFlipRequested = true;
	}

	void notifyLabelButtonClicked(LabelButtonID id) override
	{
		labelText = "label button clicked" + std::to_string(static_cast<int>(id.type)) + ", " + std::to_string(id.ID);
		updateDisplay();

		auto message = startMessageLeft(InitMapping);
		if (message != nullptr) {
			message->mappings.push_back(id);
			finishMessageLeft();
		}
	}
};

struct ExpanderWidget : CommModuleWidget {

	Label *valueLabel;
	Label *valueLabel2;
	Expander *expModule; // for debugging text only

	ExpanderWidget(Expander *module)
	{
		setModule(module);
		mainModule = static_cast<CommModule *>(module);
		expModule = module;

		if (expModule != nullptr) {
			expModule->updateDisplay = [&]() { this->valueLabel->text = this->expModule->labelText; };
		}

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/16hpTemplate.svg")));

		addParam(createParamCentered<BefacoPush>(mm2px(Vec(23.292, 70.977)), module, Expander::GET_INFO));

		valueLabel = createWidget<Label>(mm2px(Vec(0, 50)));
		valueLabel->color = rack::color::BLACK;
		valueLabel->text = "";
		valueLabel->fontSize = 13;
		addChild(valueLabel);

		addLabeledKnob("A", 0, {0, 0});
		addLabeledKnob("B", 1, {1, 0});
		addLabeledKnob("C", 2, {2, 0});
		addLabeledKnob("D", 3, {3, 0});
		addLabeledKnob("a", 4, {0, 1});
		addLabeledKnob("b", 5, {1, 1});
		addLabeledKnob("c", 6, {2, 1});
		addLabeledKnob("d", 7, {3, 1});

		for (int i = 0; i < 2; i++) {
			addLabeledInput("A IN", i, {(float)i, 1});
		}
		for (int i = 0; i < 2; i++) {
			addLabeledOutput("A OUT", i, {(float)(i + 2), 1});
		}
		for (int i = 2; i < 6; i++) {
			addLabeledInput("CV IN", i, {(float)(i - 2), 0});
		}
	}
};

Model *modelExpander = createModel<Expander, ExpanderWidget>("expanderModule");
