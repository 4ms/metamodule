#include "CommData.h"
#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/moduleTypes.h"
#include "hub_knob_menu.hh"
#include "localPath.h"
#include "paletteHub.hh"
#include "patch_writer.hh"
#include "plugin.hpp"
#include "string.h"
#include "util/string_util.hh"
#include <fstream>
#include <functional>
#include <iostream>

static const int NUM_KNOBS = 8;
static const int NUM_MAPPINGS_PER_KNOB = 8;

class KnobMaps {
public:
	ParamHandle paramHandles[NUM_MAPPINGS_PER_KNOB];
	std::pair<float, float> mapRange[NUM_MAPPINGS_PER_KNOB];

	KnobMaps(NVGcolor mapColor)
	{
		for (int i = 0; i < NUM_MAPPINGS_PER_KNOB; i++) {
			paramHandles[i].color = mapColor;
			APP->engine->addParamHandle(&paramHandles[i]);
			mapRange[i] = {0, 1};
		}
	}

	~KnobMaps()
	{
		for (int i = 0; i < NUM_MAPPINGS_PER_KNOB; i++) {
			APP->engine->removeParamHandle(&paramHandles[i]);
		}
	}

	int getNumMaps()
	{
		int num = 0;
		for (int i = 0; i < NUM_MAPPINGS_PER_KNOB; i++) {
			if (paramHandles[i].moduleId != -1) {
				num++;
			}
		}
		return num;
	}

	int firstAvailable()
	{
		int availableSlot = -1;
		int tempNum = NUM_MAPPINGS_PER_KNOB;
		if (getNumMaps() < 8) {
			for (int i = 0; i < NUM_MAPPINGS_PER_KNOB; i++) {
				if (paramHandles[i].moduleId == -1) {
					tempNum = std::min<int>(tempNum, i);
				}
			}
			availableSlot = tempNum;
		}
		return availableSlot;
	}
};

struct MetaModuleHub : public CommModule {

	KnobMaps knobMaps[NUM_KNOBS]{PaletteHub::color[0],
								 PaletteHub::color[1],
								 PaletteHub::color[2],
								 PaletteHub::color[3],
								 PaletteHub::color[4],
								 PaletteHub::color[5],
								 PaletteHub::color[6],
								 PaletteHub::color[7]};

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

		selfID.typeID = "PANEL_8";
	}

	~MetaModuleHub() {}

	json_t *dataToJson() override
	{
		json_t *rootJ = json_object();
		json_t *mapsJ = json_array();
		saveMappingRanges();

		for (auto &m : centralData->maps) {
			json_t *thisMapJ = json_object();
			json_object_set_new(thisMapJ, "DstModID", json_integer(m.dst.moduleID));
			json_object_set_new(thisMapJ, "DstObjID", json_integer(m.dst.objID));
			json_object_set_new(thisMapJ, "DstObjType", json_string(m.dst.objTypeStr()));
			json_object_set_new(thisMapJ, "SrcModID", json_integer(m.src.moduleID));
			json_object_set_new(thisMapJ, "SrcObjID", json_integer(m.src.objID));
			json_object_set_new(thisMapJ, "SrcObjType", json_string(m.src.objTypeStr()));
			json_object_set_new(thisMapJ, "RangeMin", json_real(m.range_min));
			json_object_set_new(thisMapJ, "RangeMax", json_real(m.range_max));

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
					mapping.dst.moduleID = json_is_integer(val) ? json_integer_value(val) : -1;

					val = json_object_get(mappingJ, "DstObjID");
					mapping.dst.objID = json_is_integer(val) ? json_integer_value(val) : -1;

					val = json_object_get(mappingJ, "DstObjType");
					if (json_is_string(val))
						mapping.dst.setObjTypeFromString(json_string_value(val));
					else
						mapping.dst.objType = LabelButtonID::Types::None;

					val = json_object_get(mappingJ, "SrcModID");
					mapping.src.moduleID = json_is_integer(val) ? json_integer_value(val) : -1;

					val = json_object_get(mappingJ, "SrcObjID");
					mapping.src.objID = json_is_integer(val) ? json_integer_value(val) : -1;

					val = json_object_get(mappingJ, "SrcObjType");
					if (json_is_string(val))
						mapping.src.setObjTypeFromString(json_string_value(val));
					else
						mapping.src.objType = LabelButtonID::Types::None;

					val = json_object_get(mappingJ, "RangeMin");
					mapping.range_min = json_is_real(val) ? json_real_value(val) : 0.f;

					val = json_object_get(mappingJ, "RangeMax");
					mapping.range_max = json_is_real(val) ? json_real_value(val) : 1.f;

					centralData->maps.push_back(mapping);
				}
			}
			loadMappings();
		}
	}

	void saveMappingRanges()
	{
		for (int i = 0; i < NUM_KNOBS; i++) {
			for (int x = 0; x < NUM_MAPPINGS_PER_KNOB; x++) {
				LabelButtonID dst = {LabelButtonID::Types::Knob,
									 knobMaps[i].paramHandles[x].paramId,
									 knobMaps[i].paramHandles[x].moduleId};
				LabelButtonID src = {LabelButtonID::Types::Knob, i, id};
				centralData->setMapRange(src, dst, knobMaps[i].mapRange[x].first, knobMaps[i].mapRange[x].second);
			}
		}
	}

	void loadMappings()
	{
		for (auto &m : centralData->maps) {
			auto knobToMap = m.src.objID;
			auto lowestEmpty = knobMaps[knobToMap].firstAvailable();
			APP->engine->updateParamHandle(&knobMaps[knobToMap].paramHandles[lowestEmpty], m.dst.moduleID, m.dst.objID);
			auto [min, max] = centralData->getMapRange(m.src, m.dst);
			knobMaps[knobToMap].mapRange[lowestEmpty] = {min, max};
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

		for (int i = 0; i < NUM_KNOBS; i++) {
			for (int x = 0; x < NUM_MAPPINGS_PER_KNOB; x++) {
				bool knobMapped = (knobMaps[i].paramHandles[x].moduleId) != -1;
				if (knobMapped) {
					Module *module = knobMaps[i].paramHandles[x].module;
					int paramId = knobMaps[i].paramHandles[x].paramId;
					ParamQuantity *paramQuantity = module->paramQuantities[paramId];
					auto newMappedVal = MathTools::map_value(params[i].getValue(),
															 0.0f,
															 1.0f,
															 knobMaps[i].mapRange[x].first,
															 knobMaps[i].mapRange[x].second);
					paramQuantity->setValue(newMappedVal);
				}
			}
		}

		if (responseTimer) {
			if (--responseTimer == 0) {
				printDebugFile();
				saveMappingRanges();

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

struct MetaModuleHubWidget;

class HubKnobLabel : public LabeledButton {
public:
	HubKnobLabel(MetaModuleHubWidget &hub);
	void onDeselect(const event::Deselect &e) override;
	MetaModuleHubWidget &_hub;

private:
};

class HubKnob : public RoundBlackKnob {
public:
	void onButton(const event::Button &e) override;
	void draw(const DrawArgs &args) override;
	HubKnob(HubKnobLabel &_hubKnobLabel)
		: hubKnobLabel{_hubKnobLabel}
	{}
	HubKnobLabel &hubKnobLabel;

private:
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

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/meta-module-no-words.svg")));

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
		addSmallLabeledKnobMM("a", 4, {8.5, 59.5});
		addSmallLabeledKnobMM("b", 5, {31.9, 72.8});
		addSmallLabeledKnobMM("c", 6, {48.8, 72.8});
		addSmallLabeledKnobMM("d", 7, {72.2, 59.3});

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

		auto *p = new HubKnob(*button);
		p->box.pos = mm2px(position);
		p->box.pos = p->box.pos.minus(p->box.size.div(2));
		if (module) {
			p->paramQuantity = module->paramQuantities[knobID];
			p->paramQuantity->defaultValue = defaultValue;
		}
		/*auto p = createParamCentered<HubKnob>(mm2px(position), module, knobID);
		if (p->paramQuantity)
			p->paramQuantity->defaultValue = defaultValue;*/

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
	if (touchedParam && centralData->isMappingInProgress()) {
		APP->scene->rack->touchedParam = NULL;
		int moduleId = touchedParam->paramQuantity->module->id;
		int paramId = touchedParam->paramQuantity->paramId;

		//	Create mapping
		if (_hub.expModule->id != moduleId) { // button on module clicked
			int knobToMap = centralData->getMappingSource().objID;
			for (int i = 0; i < NUM_MAPPINGS_PER_KNOB; i++) {
				auto thisHandle = _hub.expModule->knobMaps[knobToMap].paramHandles[i];
				bool duplicateMap = (thisHandle.moduleId == moduleId && thisHandle.paramId == paramId);
				if (!duplicateMap) {
					auto lowestEmpty = _hub.expModule->knobMaps[knobToMap].firstAvailable();
					if (lowestEmpty != -1) { // create mapping
						APP->engine->updateParamHandle(
							&_hub.expModule->knobMaps[knobToMap].paramHandles[lowestEmpty], moduleId, paramId, true);
						centralData->registerMapDest({LabelButtonID::Types::Knob, paramId, moduleId});
					} else {
						centralData->abortMappingProcedure();
					}
				}
			}

		} else { // button on hub clicked, abort
			centralData->abortMappingProcedure();
		}
	} else {
		//	Abort mapping
		//	module->disableLearn(id);
	}
}

void HubKnob::draw(const DrawArgs &args)
{

	RoundBlackKnob::draw(args);

	auto knobNum = this->hubKnobLabel.id.objID;

	NVGcolor color = PaletteHub::color[knobNum];
	auto hubMod = this->hubKnobLabel._hub.expModule;

	if (hubMod != nullptr) {
		bool isKnobMapped = hubMod->knobMaps[knobNum].getNumMaps() > 0;
		if (isKnobMapped) {
			nvgBeginPath(args.vg);
			const float radius = 6;
			// nvgCircle(args.vg, box.size.x / 2, box.size.y / 2, radius);
			nvgRect(args.vg, box.size.x - radius, box.size.y - radius, radius, radius);
			nvgFillColor(args.vg, color);
			nvgFill(args.vg);
			nvgStrokeColor(args.vg, color::mult(color, 0.5));
			nvgStrokeWidth(args.vg, 1.0);
			nvgStroke(args.vg);
		}
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

			ParamResetItem *resetItem = new ParamResetItem;
			resetItem->text = "Initialize";
			resetItem->rightText = "Double-click";
			resetItem->paramWidget = this;
			menu->addChild(resetItem);

			auto knobNum = this->hubKnobLabel.id.objID;
			auto hubModule = this->hubKnobLabel._hub.expModule;

			auto &thisMap = hubModule->knobMaps[knobNum];
			if (thisMap.getNumMaps() > 0) {
				for (int x = 0; x < NUM_MAPPINGS_PER_KNOB; x++) {
					bool knobMapped = thisMap.paramHandles[x].moduleId != -1;
					if (knobMapped) {

						MapFieldEntry *paramLabel2 = new MapFieldEntry;
						paramLabel2->moduleId = thisMap.paramHandles[x].moduleId;
						paramLabel2->paramId = thisMap.paramHandles[x].paramId;
						menu->addChild(paramLabel2);

						MinField *o = new MinField(hubModule->knobMaps[knobNum].mapRange[x]);
						o->box.size.x = 100;
						menu->addChild(o);

						MaxField *l = new MaxField(hubModule->knobMaps[knobNum].mapRange[x]);
						l->box.size.x = 100;
						menu->addChild(l);
					}
				}
			}

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
