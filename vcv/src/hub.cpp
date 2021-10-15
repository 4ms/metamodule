#include "CommData.h"
#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/moduleTypes.h"
#include "CoreModules/panel_mini_defs.hh"
#include "hub_knob_menu.hh"
#include "knob_map.hh"
#include "localPath.h"
#include "paletteHub.hh"
#include "patch_writer.hh"
#include "plugin.hpp"
#include "string.h"
#include "util/string_util.hh"
#include <fstream>
#include <functional>
#include <iostream>

constexpr int NUM_MAPPINGS_PER_KNOB = 8;

struct MetaModuleHub : public CommModule {

	std::vector<KnobMap<NUM_MAPPINGS_PER_KNOB>> knobMaps;
	// std::array<KnobMap<NUM_MAPPINGS_PER_KNOB>, PanelDef::NumKnobs> knobMaps{{
	// 	{0, PaletteHub::color[0]},
	// 	{1, PaletteHub::color[1]},
	// 	{2, PaletteHub::color[2]},
	// 	{3, PaletteHub::color[3]},
	// 	{4, PaletteHub::color[4]},
	// 	{5, PaletteHub::color[5]},
	// 	{6, PaletteHub::color[6]},
	// 	{7, PaletteHub::color[7]},
	// }};

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
		printf("MMHub ctor()\n");
		for (int i = 0; i < PanelDef::NumKnobs; i++)
			knobMaps.emplace_back(i, PaletteHub::color[i]);

		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		selfID.typeID = "PANEL_8";
		printf("MMHub ctor() end\n");
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
		for (auto &knobmap : knobMaps) {
			for (int x = 0; x < NUM_MAPPINGS_PER_KNOB; x++) {
				LabelButtonID dst = {
					LabelButtonID::Types::Knob, knobmap.paramHandles[x].paramId, knobmap.paramHandles[x].moduleId};
				LabelButtonID src = {LabelButtonID::Types::Knob, knobmap.paramId, id};
				centralData->setMapRange(src, dst, knobmap.mapRange[x].first, knobmap.mapRange[x].second);
			}
		}
	}

	void loadMappings()
	{
		for (auto &m : centralData->maps) {
			auto knobToMap = m.src.objID;
			// Todo: knobMaps[knobToMap].mapping.push_back({});
			// auto &ph = knobMaps[knobToMap].mapping.last();
			//
			auto lowestEmpty = knobMaps[knobToMap].firstAvailable();
			knobMaps[knobToMap].paramHandles[lowestEmpty].color = PaletteHub::color[knobToMap];
			printf("loadMappings: Adding paramhandle &%x", &knobMaps[knobToMap].paramHandles[lowestEmpty]);
			APP->engine->addParamHandle(&knobMaps[knobToMap].paramHandles[lowestEmpty]);
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

		for (auto &knobmap : knobMaps) {
			// Todo: for(auto &mapping : knobmap)
			// auto &ph = mapping.paramHandle;
			// auto &mr = mapping.mapRange;
			for (int x = 0; x < NUM_MAPPINGS_PER_KNOB; x++) {
				bool knobMapped = (knobmap.paramHandles[x].moduleId) != -1;
				if (knobMapped) {
					Module *module = knobmap.paramHandles[x].module;
					int paramId = knobmap.paramHandles[x].paramId;
					ParamQuantity *paramQuantity = module->paramQuantities[paramId];
					auto newMappedVal = MathTools::map_value(params[knobmap.paramId].getValue(),
															 0.0f,
															 1.0f,
															 knobmap.mapRange[x].first,
															 knobmap.mapRange[x].second);
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
	void draw(const DrawArgs &args) override;
	MetaModuleHubWidget &_hub;

private:
};

template<typename BaseKnobT>
class HubKnob : public BaseKnobT {
public:
	void onButton(const event::Button &e) override;
	void draw(const typename BaseKnobT::DrawArgs &args) override;
	HubKnob(HubKnobLabel &_hubKnobLabel)
		: hubKnobLabel{_hubKnobLabel}
	{}
	HubKnobLabel &hubKnobLabel;
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

		printf("Created MMHubWidget\n");

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

		addLabeledKnobMM<RoundBlackKnob>("A", 0, {9, 38.9});
		addLabeledKnobMM<RoundBlackKnob>("B", 1, {29.4, 51.7});
		addLabeledKnobMM<RoundBlackKnob>("C", 2, {51.6, 51.7});
		addLabeledKnobMM<RoundBlackKnob>("D", 3, {72, 38.9});
		addLabeledKnobMM<RoundSmallBlackKnob>("a", 4, {8.6, 59.6});
		addLabeledKnobMM<RoundSmallBlackKnob>("b", 5, {32.1, 73.0});
		addLabeledKnobMM<RoundSmallBlackKnob>("c", 6, {49.0, 73.0});
		addLabeledKnobMM<RoundSmallBlackKnob>("d", 7, {72.6, 59.6});

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

	template<typename KnobType>
	void
	addLabeledKnobMM(const std::string labelText, const int knobID, const Vec position, const float defaultValue = 0.f)
	{
		Vec posPx = mm2px(position);

		auto *button = new HubKnobLabel{*this};
		button->isOnHub = true;

		button->box.pos = Vec(posPx.x - mm2px(kKnobSpacingX) / 2, posPx.y + mm2px(kTextOffset));
		button->box.size.x = mm2px(kKnobSpacingX);
		button->box.size.y = 12;
		button->text = labelText;
		button->id = {LabelButtonID::Types::Knob, knobID, -1};
		addChild(button);

		auto *p = new HubKnob<KnobType>(*button);
		p->box.pos = posPx;
		p->box.pos = p->box.pos.minus(p->box.size.div(2));
		if (module) {
			p->paramQuantity = module->paramQuantities[knobID];
			p->paramQuantity->defaultValue = defaultValue;
		}
		addParam(p);
	}
};

HubKnobLabel::HubKnobLabel(MetaModuleHubWidget &hub)
	: LabeledButton{static_cast<CommModuleWidget &>(hub)}
	, _hub{hub}
{}

void HubKnobLabel::onDeselect(const event::Deselect &e)
{
	printf("Entering onDeselect()\n");
	if (!_hub.expModule)
		return;
	// if (!module)
	// 	return;

	// Check if a ParamWidget was touched
	ParamWidget *touchedParam = APP->scene->rack->touchedParam;
	if (touchedParam && centralData->isMappingInProgress()) {
		int moduleId = touchedParam->paramQuantity->module->id;
		int paramId = touchedParam->paramQuantity->paramId;
		APP->scene->rack->touchedParam = NULL;

		//	Create mapping
		if (_hub.expModule->id != moduleId) { // button on module clicked
			int knobToMap = centralData->getMappingSource().objID;
			// Search if mapping already exists
			bool duplicateMap = false;
			for (int i = 0; i < NUM_MAPPINGS_PER_KNOB; i++) {
				auto thisHandle = _hub.expModule->knobMaps[knobToMap].paramHandles[i];
				duplicateMap = (thisHandle.moduleId == moduleId && thisHandle.paramId == paramId);
			}

			if (!duplicateMap) {
				auto lowestEmpty = _hub.expModule->knobMaps[knobToMap].firstAvailable();
				if (lowestEmpty != -1) {
					// create mapping
					_hub.expModule->knobMaps[knobToMap].paramHandles[lowestEmpty].color = PaletteHub::color[knobToMap];
					printf("Adding paramhandle &%x", &_hub.expModule->knobMaps[knobToMap].paramHandles[lowestEmpty]);
					APP->engine->addParamHandle(&_hub.expModule->knobMaps[knobToMap].paramHandles[lowestEmpty]);
					APP->engine->updateParamHandle(
						&_hub.expModule->knobMaps[knobToMap].paramHandles[lowestEmpty], moduleId, paramId, true);
					centralData->registerMapDest({LabelButtonID::Types::Knob, paramId, moduleId});
				} else {
					centralData->abortMappingProcedure();
				}
			} else {
				// TODO remove mapping?
			}
		} else { // user clicked on a hub knob, abort
			centralData->abortMappingProcedure();
		}
	} else {
		//	Whatever we touched, it wasn't another module's knob
		//	Or-- a mapping is not in progress
		// Either way, just ignore the event
	}
}

void HubKnobLabel::draw(const DrawArgs &args)
{
	updateState();

	nvgBeginPath(args.vg);
	float padding_x = 2;
	float knob_height = 40;
	nvgRoundedRect(args.vg, padding_x, -knob_height, box.size.x - padding_x * 2, knob_height + box.size.y, 5.0);
	nvgStrokeColor(args.vg, rack::color::WHITE);
	nvgStrokeWidth(args.vg, 0.0);
	if (isCurrentMapSrc) {
		auto knobNum = this->id.objID;
		nvgFillColor(args.vg, PaletteHub::color[knobNum]);
	} else {
		nvgFillColor(args.vg, rack::color::alpha(rack::color::BLACK, 0.0f));
	}
	nvgStroke(args.vg);
	nvgFill(args.vg);

	nvgBeginPath(args.vg);
	nvgTextAlign(args.vg, NVGalign::NVG_ALIGN_CENTER | NVGalign::NVG_ALIGN_MIDDLE);
	nvgFillColor(args.vg, nvgRGBA(0, 0, 0, 255));
	nvgFontSize(args.vg, 8.0f);
	nvgText(args.vg, box.size.x / 2.0f, box.size.y / 2.0f, text.c_str(), NULL);
}

template<typename BaseKnobT>
void HubKnob<BaseKnobT>::draw(const typename BaseKnobT::DrawArgs &args)
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
			nvgRect(args.vg, this->box.size.x - radius, this->box.size.y - radius, radius, radius);
			nvgFillColor(args.vg, color);
			nvgFill(args.vg);
			nvgStrokeColor(args.vg, color::mult(color, 0.5));
			nvgStrokeWidth(args.vg, 1.0);
			nvgStroke(args.vg);
		}
	}
}

template<typename BaseKnobT>
void HubKnob<BaseKnobT>::onButton(const event::Button &e)
{
	math::Vec c = this->box.size.div(2);
	float dist = e.pos.minus(c).norm();
	if (dist <= c.x) {
		OpaqueWidget::onButton(e);

		// Touch parameter
		if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_LEFT && (e.mods & RACK_MOD_MASK) == 0) {
			if (this->paramQuantity) {
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
				this->paramQuantity
					? APP->engine->getParamHandle(this->paramQuantity->module->id, this->paramQuantity->paramId)
					: NULL;
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
