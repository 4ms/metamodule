#pragma once
#include "CommData.h"
#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/moduleTypes.h"
#include "hub_knob.hh"
#include "knob_map.hh"
#include "localPath.h"
#include "paletteHub.hh"
#include "patch_writer.hh"
#include "plugin.hpp"
#include "string.h"
#include "util/string_util.hh"
#include <fstream>
#include <functional>

struct MetaModuleHubBase : public CommModule {

	static constexpr int NUM_MAPPINGS_PER_KNOB = 8;
	std::vector<KnobMap> knobMaps;

	// std::function<void()> updatePatchName;
	// std::function<void()> redrawPatchName;
	std::string labelText = "";
	std::string patchNameText = "";

	long responseTimer = 0;
	bool buttonAlreadyHandled = false;

	MetaModuleHubBase() = default;
	~MetaModuleHubBase() = default;

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
			for (auto &mapping : knobmap.maps) {
				LabelButtonID dst = {
					LabelButtonID::Types::Knob,
					mapping.paramHandle.paramId,
					mapping.paramHandle.moduleId,
				};
				LabelButtonID src = {
					LabelButtonID::Types::Knob,
					knobmap.paramId,
					id, // this module ID
				};
				centralData->setMapRange(src, dst, mapping.range.first, mapping.range.second);
			}
		}
	}

	void loadMappings()
	{
		// Clear all maps in all knobMaps first?
		for (auto &m : centralData->maps) {
			auto knobToMap = m.src.objID;
			auto [min, max] = centralData->getMapRange(m.src, m.dst);
			knobMaps[knobToMap].create(m.dst.moduleID, m.dst.objID, PaletteHub::color[knobToMap], min, max);
		}
	}

	// Hub class needs to call this from its process
	void processPatchButton(float patchButtonState)
	{
		if (buttonJustPressed(patchButtonState)) {
			responseTimer = 48000 / 4; // todo: set this to the sampleRate
			centralData->requestAllParamDataAllModules();
			labelText = "Requesting all modules send their data";
			updatePatchName();
			updateDisplay();
		}
	}

	void processKnobMaps()
	{
		for (auto &knobmap : knobMaps) {
			for (auto &mapping : knobmap.maps) {
				bool isKnobMapped = (mapping.paramHandle.moduleId) != -1;
				if (isKnobMapped) {
					Module *module = mapping.paramHandle.module;
					int paramId = mapping.paramHandle.paramId;
					ParamQuantity *paramQuantity = module->paramQuantities[paramId];
					auto newMappedVal = MathTools::map_value(
						params[knobmap.paramId].getValue(), 0.0f, 1.0f, mapping.range.first, mapping.range.second);
					paramQuantity->setValue(newMappedVal);
				}
			}
		}
	}

	void processCreatePatchFile()
	{
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
	bool buttonJustPressed(bool button_value)
	{
		if (button_value > 0.f) {
			if (!buttonAlreadyHandled) {
				buttonAlreadyHandled = true;
				return true;
			}
		} else {
			buttonAlreadyHandled = false;
		}
		return false;
	}

	////////// put this in PatchFileWriter, or a new class PatchTextFileWriter and rename the other
	/// PatchBinaryFileWriter
	// centralData ==> string

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
	//
	//
	///////////////////////// end move to PatchFileWriter
};

struct MetaModuleHubBaseWidget : CommModuleWidget {

	Label *valueLabel;
	LedDisplayTextField *patchName;
	MetaModuleHubBase *expModule;

	MetaModuleHubBaseWidget() = default; // MetaModuleHubBase *module)
	// {
	// We'll have to copy this boilerplate into each Hub module, since it's customized for each size hub
	//
	// setModule(module);
	// expModule = module;

	// if (expModule != nullptr) {
	// 	expModule->updateDisplay = [&]() { this->valueLabel->text = this->expModule->labelText; };
	// 	expModule->updatePatchName = [&]() { this->expModule->patchNameText = this->patchName->text; };
	// 	expModule->redrawPatchName = [&]() { this->patchName->text = this->expModule->patchNameText; };
	// }
	// setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/meta-module-no-words.svg")));

	// // addParam(createParamCentered<BefacoPush>(mm2px(Vec(69.7, 19.5)), module, MetaModuleHub::GET_INFO));
	// addLabeledToggleMM("WRITE", MetaModuleHub::WRITE_LIGHT, MetaModuleHub::GET_INFO, {70, 19.5});

	// valueLabel = createWidget<Label>(mm2px(Vec(0, 1)));
	// valueLabel->color = rack::color::BLACK;
	// valueLabel->text = "";
	// valueLabel->fontSize = 10;
	// addChild(valueLabel);

	// patchName = createWidget<MetaModuleTextBox>(mm2px(Vec(24.6, 9.6)));
	// if (expModule != nullptr && expModule->patchNameText.length() > 0)
	// 	patchName->text = this->expModule->patchNameText;
	// else
	// 	patchName->text = "Enter Patch Name";
	// patchName->color = rack::color::WHITE;
	// patchName->box.size = {mm2px(Vec(33.6, 31.3))};
	// addChild(patchName);

	// addLabeledKnobMM<RoundBlackKnob>("A", 0, {9, 38.9});
	// addLabeledKnobMM<RoundSmallBlackKnob>("a", 4, {8.6, 59.6});
	// addLabeledInputMM("CV IN 1", MetaModuleHub::CV_1, {7.6, 74.5});
	// addLabeledOutputMM("CV Out 1", MetaModuleHub::AUDIO_OUT_3, {25.7, 96.2});
	// Todo:
	// addLabeledToggle() for both RGB Buttons
	// }

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

		HubKnobLabel *button;

		if (expModule)
			button = new HubKnobLabel{*this, expModule->knobMaps[knobID]};
		else
			button = new HubKnobLabel{*this};
		button->isOnHub = true;

		button->box.pos = Vec(posPx.x - mm2px(kKnobSpacingX) / 2, posPx.y + mm2px(kTextOffset));
		button->box.size.x = mm2px(kKnobSpacingX);
		button->box.size.y = 12;
		button->text = labelText;
		button->id = {
			LabelButtonID::Types::Knob, knobID, -1}; // moduleID is -1 for now, since we might not have a module
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
