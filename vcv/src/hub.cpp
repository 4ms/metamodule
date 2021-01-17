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

	std::string labelText = "";

	long responseTimer = 0;
	bool buttonAlreadyHandled = false;

	Expander()
	{
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		selfID.typeID = "HUB";
	}

	void appendModuleList(std::string &str)
	{
		for (auto &mod : centralData->moduleData) {
			str += "Module slug in centralData = ";
			str += mod.typeID.name;
			str += ". CoreModule slug = ";
			str += ModuleFactory::getModuleSlug(mod.typeID);
			str += " (" + ModuleFactory::getModuleTypeName(mod.typeID) + ") ";
			str += ". VCV Rack unique ID = " + std::to_string(mod.id) + "\n";
		}
	}

	void appendCableList(std::string &str)
	{
		for (auto jData : centralData->jackData) {
			if (jData.connected == true) {
				str += "Input jack " + std::to_string(jData.sendingJackId);
				str += " on module " + std::to_string(jData.sendingModuleId);
				str += " is connected to output jack " + std::to_string(jData.receivedJackId);
				str += " on module " + std::to_string(jData.receivedModuleId) + "\n";
			} else {
				str += "Input jack " + std::to_string(jData.sendingJackId) + " on module " +
					   std::to_string(jData.sendingModuleId) + " not connected" + "\n";
			}
		}
	}

	void appendParamList(std::string &str)
	{
		for (auto pData : centralData->paramData) {
			str += "Parameter # " + std::to_string(pData.paramID) + " on module # " + std::to_string(pData.moduleID) +
				   " value is " + std::to_string(pData.value) + "\n";
		}
	}

	void appendMappingList(std::string &str)
	{
		for (auto &m : centralData->maps) {
			str += "Mapping: src param ID = " + std::to_string(m.src.objID);
			str += " type = " + std::to_string((int)m.src.objType);
			str += " moduleID = " + std::to_string(m.src.moduleID);
			str += " ==> dst param ID = " + std::to_string(m.dst.objID);
			str += " type = " + std::to_string((int)m.dst.objType);
			str += " moduleID = " + std::to_string(m.dst.moduleID);
			str += "\n";
		}
	}

	void process(const ProcessArgs &args) override
	{
		if (buttonJustPressed()) {
			responseTimer = 48000 / 4; // todo: set this to the sampleRate
			centralData->requestAllParamDataAllModules();
			labelText = "Requesting all modules send their data";
			updateDisplay();
		}
		if (responseTimer) {
			if (--responseTimer == 0) {
				std::string str = "";
				appendModuleList(str);
				appendParamList(str);
				appendCableList(str);
				appendMappingList(str);
				writeToDebugFile(debugFile, str);

				labelText = "Writing module list to file";
				updateDisplay();
			}
		}
	}

	void writeToDebugFile(std::string fileName, std::string &textToWrite)
	{
		std::ofstream myfile;
		myfile.open(fileName);
		myfile << textToWrite;
		myfile.close();
	}

	bool buttonJustPressed()
	{
		if (params[GET_INFO].getValue() > 0.f) {
			if (!buttonAlreadyHandled) {
				buttonAlreadyHandled = true;
				return true;
			}
		} else {
			buttonAlreadyHandled = false;
		}
		return false;
	}
};

struct ExpanderWidget : CommModuleWidget {

	Label *valueLabel;
	Label *valueLabel2;
	Expander *expModule; // for debugging text only

	ExpanderWidget(Expander *module)
	{
		setModule(module);
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

	virtual LabeledButton *createLabel() override
	{
		auto tmp = new LabeledButton{*this};
		tmp->isOnHub = true;
		return tmp;
	}

	virtual void notifyLabelButtonClicked(LabeledButton &button) override
	{
		button.id.moduleID = module->id; // workaround for VCV passing bad ptr to module

		bool currentSourceIsThisButton = false;

		if (centralData->isMappingInProgress()) {
			currentSourceIsThisButton = centralData->getMappingSource() == button.id;
			centralData->abortMappingProcedure();
			valueLabel->text = "Aborted mapping";
		}
		if (!currentSourceIsThisButton) {
			centralData->startMappingProcedure(button.id);
			valueLabel->text = "Start Mapping from: " + std::to_string(static_cast<int>(button.id.objType)) + ", " +
							   std::to_string(button.id.objID);
		}
	}
};

Model *modelExpander = createModel<Expander, ExpanderWidget>("expanderModule");
