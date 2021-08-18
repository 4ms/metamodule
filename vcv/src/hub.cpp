#include "CommData.h"
#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/moduleTypes.h"
#include "hub_knob_menu.hh"
#include "localPath.h"
#include "patch_writer.hh"
#include "plugin.hpp"
#include "string.h"
#include "util/string_util.hh"
#include <fstream>
#include <functional>
#include <iostream>

static const int MAX_CHANNELS = 8;

struct MetaModuleHub : public CommModule {

	ParamHandle paramHandles[MAX_CHANNELS];
	bool knobMapped[MAX_CHANNELS];

	enum ParamIds { ENUMS(KNOBS, 8), GET_INFO, NUM_PARAMS };
	enum InputIds { AUDIO_IN_L, AUDIO_IN_R, CV_1, CV_2, CV_3, CV_4, GATE_IN_1, GATE_IN_2, CLOCK_IN, NUM_INPUTS };
	enum OutputIds { AUDIO_OUT_L, AUDIO_OUT_R, AUDIO_OUT_3, AUDIO_OUT_4, CLOCK_OUT, NUM_OUTPUTS };
	enum LightIds { WRITE_LIGHT, NUM_LIGHTS };

	std::string labelText = "";
	std::string patchNameText = "";

	long responseTimer = 0;
	bool buttonAlreadyHandled = false;

	MetaModuleHub()
	{
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

		for (int id = 0; id < MAX_CHANNELS; id++) {
			paramHandles[id].color = nvgRGB(rand() % 256, rand() % 256, rand() % 256);
			APP->engine->addParamHandle(&paramHandles[id]);
			knobMapped[id] = false;
		}

		selfID.typeID = "PANEL_8";
	}

	~MetaModuleHub()
	{
		for (int id = 0; id < MAX_CHANNELS; id++) {
			APP->engine->removeParamHandle(&paramHandles[id]);
		}
	}

	json_t *dataToJson() override
	{
		json_t *rootJ = json_object();
		json_t *mapsJ = json_array();
		for (auto &m : centralData->maps) {
			json_t *thisMapJ = json_object();
			json_object_set_new(thisMapJ, "DstModID", json_integer(m.dst.moduleID));
			json_object_set_new(thisMapJ, "DstObjID", json_integer(m.dst.objID));
			json_object_set_new(thisMapJ, "DstObjType", json_string(m.dst.objTypeStr()));
			json_object_set_new(thisMapJ, "SrcModID", json_integer(m.src.moduleID));
			json_object_set_new(thisMapJ, "SrcObjID", json_integer(m.src.objID));
			json_object_set_new(thisMapJ, "SrcObjType", json_string(m.src.objTypeStr()));

			json_array_append(mapsJ, thisMapJ);
			json_decref(thisMapJ);
		}
		json_object_set_new(rootJ, "Mappings", mapsJ);
		json_t *patchNameJ = json_string(patchNameText.c_str());
		json_object_set_new(rootJ, "PatchName", patchNameJ);
		return rootJ;
	}

	void dataFromJson(json_t *rootJ) override
	{
		auto patchNameJ = json_object_get(rootJ, "PatchName");
		if (json_is_string(patchNameJ)) {
			patchNameText = json_string_value(patchNameJ);
			redrawPatchName();
		}

		auto mapsJ = json_object_get(rootJ, "Mappings");
		if (json_is_array(mapsJ)) {
			centralData->maps.clear();
			for (size_t i = 0; i < json_array_size(mapsJ); i++) {
				auto mappingJ = json_array_get(mapsJ, i);
				Mapping mapping;

				if (json_is_object(mappingJ)) {
					json_t *val;

					val = json_object_get(mappingJ, "DstModID");
					if (json_is_integer(val))
						mapping.dst.moduleID = json_integer_value(val);
					val = json_object_get(mappingJ, "DstObjID");
					if (json_is_integer(val))
						mapping.dst.objID = json_integer_value(val);
					val = json_object_get(mappingJ, "DstObjType");
					if (json_is_string(val))
						mapping.dst.setObjTypeFromString(json_string_value(val));

					val = json_object_get(mappingJ, "SrcModID");
					if (json_is_integer(val))
						mapping.src.moduleID = json_integer_value(val);
					val = json_object_get(mappingJ, "SrcObjID");
					if (json_is_integer(val))
						mapping.src.objID = json_integer_value(val);
					val = json_object_get(mappingJ, "SrcObjType");
					if (json_is_string(val))
						mapping.src.setObjTypeFromString(json_string_value(val));

					centralData->maps.push_back(mapping);
				}
			}
		}
	}

	void process(const ProcessArgs &args) override
	{
		if (buttonJustPressed()) {
			responseTimer = 48000 / 4; // todo: set this to the sampleRate
			centralData->requestAllParamDataAllModules();
			labelText = "Requesting all modules send their data";
			updatePatchName();
			updateDisplay();
		}

		for (int i = 0; i < MAX_CHANNELS; i++) {
			if (knobMapped[i]) {
				Module *module = paramHandles[i].module;
				int paramId = paramHandles[i].paramId;
				ParamQuantity *paramQuantity = module->paramQuantities[paramId];
				paramQuantity->setValue(params[i].getValue());
			}
		}

		if (responseTimer) {
			if (--responseTimer == 0) {
				printDebugFile();

				std::string patchName;
				std::string patchDir;
				if (patchNameText.substr(0, 5) == "test_")
					patchDir = testPatchDir;
				else
					patchDir = examplePatchDir;
				if (patchNameText != "" && patchNameText != "Enter Patch Name") {
					patchName = patchNameText.c_str();
				} else {
					std::string randomname = "Unnamed" + std::to_string(MathTools::randomNumber<unsigned int>(10, 99));
					patchName = randomname.c_str();
				}
				ReplaceString patchStructName{patchName};
				patchStructName.replace_all(" ", "")
					.replace_all("-", "")
					.replace_all(",", "")
					.replace_all("/", "")
					.replace_all("\\", "")
					.replace_all("\"", "")
					.replace_all("'", "")
					.replace_all(".", "")
					.replace_all("?", "")
					.replace_all("#", "")
					.replace_all("!", "");
				std::string patchFileName = patchDir + patchStructName.str;
				writePatchFile(patchFileName, patchName);

				labelText = "Wrote patch file: ";
				labelText += patchStructName.str + ".txt";
				updateDisplay();
			}
		}
	}

private:
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

	void writePatchFile(std::string fileName, std::string patchName)
	{
		labelText = "Creating patch..";
		updateDisplay();

		PatchFileWriter pw{centralData->moduleData};
		pw.setPatchName(patchName);
		pw.setJackList(centralData->jackData);
		pw.setParamList(centralData->paramData);
		pw.addMaps(centralData->maps);

		writeToFile(fileName + ".txt", pw.printPatchYAML());
		writeBinaryFile(fileName + ".mmpatch", pw.printPatchBinary());
	}

	void printDebugFile()
	{
		std::string str = "";
		appendModuleList(str);
		appendParamList(str);
		appendCableList(str);
		appendMappingList(str);

		labelText = "Printing debug file...";
		updateDisplay();

		writeToFile(debugFile, str);
	}

	void appendModuleList(std::string &str)
	{
		for (auto &mod : centralData->moduleData) {
			str += "Module slug in centralData = ";
			str += mod.typeID;
			str += ". CoreModule slug = ";
			str += ModuleFactory::getModuleSlug(mod.typeID);
			str += " (";
			str += ModuleFactory::getModuleTypeName(mod.typeID);
			str += ") ";
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

	void writeToFile(std::string fileName, std::string textToWrite)
	{
		std::ofstream myfile;
		myfile.open(fileName);
		myfile << textToWrite;
		myfile.close();
	}

	void writeBinaryFile(std::string fileName, const std::vector<unsigned char> data)
	{
		std::ofstream myfile{fileName, std::ios_base::binary | std::ios_base::out | std::ios_base::trunc};
		myfile.write(reinterpret_cast<const char *>(data.data()), data.size());
		myfile.close();
	}
};

class HubKnob : public RoundBlackKnob {
public:
	void onButton(const event::Button &e) override;
};

struct MetaModuleHubWidget;

class HubKnobLabel : public LabeledButton {
public:
	HubKnobLabel(MetaModuleHubWidget &hub);
	void onDeselect(const event::Deselect &e) override;

private:
	MetaModuleHubWidget &_hub;
};

struct MetaModuleHubWidget : CommModuleWidget {

	Label *valueLabel;
	Label *valueLabel2;
	LedDisplayTextField *patchName;
	MetaModuleHub *expModule; // for debugging text only

	MetaModuleHubWidget(MetaModuleHub *module)
	{
		setModule(module);
		expModule = module;

		if (expModule != nullptr) {
			expModule->updateDisplay = [&]() { this->valueLabel->text = this->expModule->labelText; };
			expModule->updatePatchName = [&]() { this->expModule->patchNameText = this->patchName->text; };
			expModule->redrawPatchName = [&]() { this->patchName->text = this->expModule->patchNameText; };
		}

		// setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/16hptemplate.svg")));
		// setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/meta-module-art-only.svg")));
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/meta-module-no-words.svg")));
		// setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/meta-module-all-gray.svg")));

		// addParam(createParamCentered<BefacoPush>(mm2px(Vec(69.7, 19.5)), module, MetaModuleHub::GET_INFO));
		addLabeledToggleMM("WRITE", MetaModuleHub::WRITE_LIGHT, MetaModuleHub::GET_INFO, {70, 19.5});

		valueLabel = createWidget<Label>(mm2px(Vec(0, 1)));
		valueLabel->color = rack::color::BLACK;
		valueLabel->text = "";
		valueLabel->fontSize = 10;
		addChild(valueLabel);

		patchName = createWidget<MetaModuleTextBox>(mm2px(Vec(24.6, 9.6)));
		if (expModule != nullptr && expModule->patchNameText.length() > 0)
			patchName->text = this->expModule->patchNameText;
		else
			patchName->text = "Enter Patch Name";
		patchName->color = rack::color::WHITE;
		patchName->box.size = {mm2px(Vec(33.6, 31.3))};
		addChild(patchName);
		patchName->selectAll(); // Doesn't work :(

		addLabeledKnobMM("A", 0, {9, 38.9});
		addLabeledKnobMM("B", 1, {29.4, 51.4});
		addLabeledKnobMM("C", 2, {51.6, 51.6});
		addLabeledKnobMM("D", 3, {72, 38.9});
		addLabeledKnobMM("a", 4, {8.5, 59.5});
		addLabeledKnobMM("b", 5, {31.9, 72.8});
		addLabeledKnobMM("c", 6, {48.8, 72.8});
		addLabeledKnobMM("d", 7, {72.2, 59.3});

		addLabeledInputMM("CV IN 1", MetaModuleHub::CV_1, {7.6, 74.5});
		addLabeledInputMM("CV IN 2", MetaModuleHub::CV_2, {20, 82.1});
		addLabeledInputMM("CV IN 3", MetaModuleHub::CV_3, {60.7, 82.4});
		addLabeledInputMM("CV IN 4", MetaModuleHub::CV_4, {73.1, 74.5});

		addLabeledInputMM("Gate In 1", MetaModuleHub::GATE_IN_1, {9, 94.5});
		addLabeledInputMM("Gate In 2", MetaModuleHub::GATE_IN_2, {71.7, 94.5});
		addLabeledInputMM("Clock In", MetaModuleHub::CLOCK_IN, {40.4, 88.9});

		addLabeledInputMM("Audio IN L", MetaModuleHub::AUDIO_IN_L, {8.2, 111.8});
		addLabeledInputMM("Audio IN R", MetaModuleHub::AUDIO_IN_R, {23.4, 111.8});

		addLabeledOutputMM("Audio OUT L", MetaModuleHub::AUDIO_OUT_L, {57.3, 111.8});
		addLabeledOutputMM("Audio OUT R", MetaModuleHub::AUDIO_OUT_R, {72.8, 111.8});

		addLabeledOutputMM("CV Out 1", MetaModuleHub::AUDIO_OUT_3, {25.7, 96.2});
		addLabeledOutputMM("CV Out 2", MetaModuleHub::AUDIO_OUT_4, {55, 96.2});

		addLabeledOutputMM("Clock Out", MetaModuleHub::CLOCK_OUT, {40.4, 106.4});

		// Todo:
		// addLabeledToggle() for both RGB Buttons
	}

	LabeledButton *createLabel() override
	{
		auto tmp = new LabeledButton{*this};
		tmp->isOnHub = true;
		return tmp;
	}

	void notifyLabelButtonClicked(LabeledButton &button) override
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

	void addLabeledKnobMM(const std::string labelText,
						  const int knobID,
						  const Vec position,
						  const float defaultValue = 0.f) override
	{

		auto *button = new HubKnobLabel{*this};
		button->isOnHub = true;
		button->box.pos = mm2px(Vec(position.x - kKnobSpacingX / 4.0f, position.y + kTextOffset));
		button->box.size.x = kGridSpacingX / 2.0f;
		button->box.size.y = 12;
		button->text = labelText;
		button->id = {LabelButtonID::Types::Knob, knobID, -1};
		addChild(button);

		auto p = createParamCentered<HubKnob>(mm2px(position), module, knobID);
		if (p->paramQuantity)
			p->paramQuantity->defaultValue = defaultValue;
		addParam(p);
	}
};

HubKnobLabel::HubKnobLabel(MetaModuleHubWidget &hub)
	: LabeledButton{static_cast<CommModuleWidget &>(hub)}
	, _hub{hub}
{}

void HubKnobLabel::onDeselect(const event::Deselect &e)
{
	// if (!_hub.expModule)
	// 	return;
	// if (!module)
	// 	return;

	// Check if a ParamWidget was touched
	ParamWidget *touchedParam = APP->scene->rack->touchedParam;
	if (touchedParam) {
		APP->scene->rack->touchedParam = NULL;
		int moduleId = touchedParam->paramQuantity->module->id;
		int paramId = touchedParam->paramQuantity->paramId;

		//	Create mapping
		if (_hub.expModule->id != moduleId) { // button on module clicked
			int mapNum = centralData->getMappingSource().objID;
			if (_hub.expModule->paramHandles[mapNum].moduleId == moduleId &&
				_hub.expModule->paramHandles[mapNum].paramId == paramId)
			{ // destination knob is already mapped, unmap
				_hub.expModule->knobMapped[mapNum] = false;
			} else { // destination knob is not mapped, map
				_hub.expModule->knobMapped[mapNum] = true;
				for (int i = 0; i < 8; i++) {
					if (i != mapNum) {
						if (_hub.expModule->paramHandles[i].moduleId == moduleId) {
							if (_hub.expModule->paramHandles[i].paramId == paramId)
								_hub.expModule->knobMapped[i] = false;
						}
					}
				}
			}
			APP->engine->updateParamHandle(&_hub.expModule->paramHandles[mapNum], moduleId, paramId, true);
			centralData->abortMappingProcedure();
		} else { // button on hub clicked, abort
			centralData->abortMappingProcedure();
		}
		// if (expModule->knobMapped[buttonNum] == false)
		// 	expModule->knobMapped[buttonNum] = true;
		// else {
		// 	expModule->knobMapped[buttonNum] = false;
		// }
	} else {
		//	Abort mapping
		//	module->disableLearn(id);
	}
}

void HubKnob::onButton(const event::Button &e)
{
	math::Vec c = box.size.div(2);
	float dist = e.pos.minus(c).norm();
	if (dist <= c.x) {
		OpaqueWidget::onButton(e);

		// Touch parameter
		if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_LEFT && (e.mods & RACK_MOD_MASK) == 0) {
			if (paramQuantity) {
				APP->scene->rack->touchedParam = this;
			}
			e.consume(this);
		}

		// Right click to open context menu
		if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_RIGHT && (e.mods & RACK_MOD_MASK) == 0) {
			ui::Menu *menu = createMenu();

			MapFieldLabel *paramLabel = new MapFieldLabel;
			paramLabel->paramWidget = this;
			menu->addChild(paramLabel);

			MapField *paramField = new MapField;
			paramField->box.size.x = 100;
			paramField->setParamWidget(this);
			menu->addChild(paramField);

			for (int i = 0; i < 8; i++) {
				MapField *m = new MapField;
				m->box.size.x = 100;
				m->setParamWidget(this);
				menu->addChild(m);
			}

			ParamResetItem *resetItem = new ParamResetItem;
			resetItem->text = "Initialize";
			resetItem->rightText = "Double-click";
			resetItem->paramWidget = this;
			menu->addChild(resetItem);

			// ParamFineItem *fineItem = new ParamFineItem;
			// fineItem->text = "Fine adjust";
			// fineItem->rightText = RACK_MOD_CTRL_NAME "+drag";
			// fineItem->disabled = true;
			// menu->addChild(fineItem);

			engine::ParamHandle *paramHandle =
				paramQuantity ? APP->engine->getParamHandle(paramQuantity->module->id, paramQuantity->paramId) : NULL;
			if (paramHandle) {
				ParamUnmapItem *unmapItem = new ParamUnmapItem;
				unmapItem->text = "Unmap";
				unmapItem->rightText = paramHandle->text;
				unmapItem->paramWidget = this;
				menu->addChild(unmapItem);
			}
			e.consume(this);
		}
	}
}

Model *modelMetaModuleHub = createModel<MetaModuleHub, MetaModuleHubWidget>("metaModuleHubModule");
