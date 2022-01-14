#pragma once
#include "CommData.hpp"
#include "CommModule.hpp"
#include "CommWidget.hpp"
#include "CoreModules/moduleFactory.hh"
#include "hub_jack.hpp"
#include "hub_knob.hpp"
#include "knob_map.hpp"
#include "localPath.hpp"
#include "paletteHub.hpp"
#include "patch_writer.hpp"
#include "plugin.hpp"
#include "util/math.hh"
#include "util/string_util.hh"
#include <fstream>
#include <functional>
#include <string.h>

template<int NumKnobMaps>
struct MetaModuleHubBase : public CommModule {

	std::array<KnobMap, NumKnobMaps> knobMaps;

	std::function<void()> updatePatchName;
	std::function<void()> redrawPatchName;
	std::string labelText = "";
	std::string patchNameText = "";

	long responseTimer = 0;
	bool buttonAlreadyHandled = false;

	MetaModuleHubBase()
	{
		for (int i = 0; i < NumKnobMaps; i++)
			knobMaps[i].paramId = i;
	}
	// ~MetaModuleHubBase() = default;

	json_t *dataToJson() override
	{
		json_t *rootJ = json_object();
		json_t *mapsJ = json_array();
		refreshMappings();

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
					// printf("Loaded mapping from json: type: %s src: m:%d knob:%d, dst: m:%d knob:%d\n",
					// 	   mapping.src.objTypeStr(),
					// 	   mapping.src.moduleID,
					// 	   mapping.src.objID,
					// 	   mapping.dst.moduleID,
					// 	   mapping.dst.objID);
				}
			}
			loadMappings();
		}
	}

	void refreshMappings()
	{
		// user might have right-clicked a knob and selected Unmap
		// Or user may have changed min/max sliders
		// We don't get a notification of this, so we need to rebuild the knob maps
		centralData->unregisterKnobMapsBySrcModule(id);
		for (auto &knobmap : knobMaps) {
			for (auto &mapping : knobmap.maps) {
				if (mapping->paramHandle.moduleId > -1) {
					LabelButtonID dst = {
						LabelButtonID::Types::Knob,
						mapping->paramHandle.paramId,
						mapping->paramHandle.moduleId,
					};
					LabelButtonID src = {
						LabelButtonID::Types::Knob,
						knobmap.paramId,
						id, // this module ID
					};
					centralData->registerMapping(src, dst, mapping->range.first, mapping->range.second);
					// printf("refreshing knob mappings: centralData->registerMapping(src: m:%d knob:%d, dst: m:%d "
					// 	   "knob:%d, )\n",
					// 	   src.moduleID,
					// 	   src.objID,
					// 	   dst.moduleID,
					// 	   dst.objID);
				}
			}
		}
	}

	void loadMappings()
	{
		for (auto &m : centralData->maps) {
			if (m.src.objType == LabelButtonID::Types::Knob) {
				auto knobToMap = m.src.objID;
				auto [min, max] = centralData->getMapRange(m.src, m.dst);
				knobMaps[knobToMap].create(m.dst.moduleID, m.dst.objID, PaletteHub::color[knobToMap], min, max);
			}
		}
	}

	// Hub class needs to call this from its process
	void processPatchButton(float patchButtonState)
	{
		if (buttonJustPressed(patchButtonState)) {
			responseTimer = 48000 / 4; // TODO: set this to the sampleRate
			centralData->requestAllParamDataAllModules();
			labelText = "Requesting all modules send their data";
			updatePatchName();
			updateDisplay();
		}
	}

	// Hub class needs to call this from its process
	void processKnobMaps()
	{
		for (auto &knobmap : knobMaps) {
			for (auto &mapping : knobmap.maps) {
				bool isKnobMapped = (mapping->paramHandle.moduleId) != -1;
				if (isKnobMapped) {
					Module *module = mapping->paramHandle.module;
					if (module) {
						int paramId = mapping->paramHandle.paramId;
						ParamQuantity *paramQuantity = module->paramQuantities[paramId];
						auto newMappedVal = MathTools::map_value(params[knobmap.paramId].getValue(),
																 0.0f,
																 1.0f,
																 mapping->range.first,
																 mapping->range.second);
						paramQuantity->setValue(newMappedVal);
					} else {
						// disable the mapping because the module was deleted
						mapping->paramHandle.moduleId = -1;
					}
				}
			}
		}
	}

	// Hub class needs to call this from its process
	void processCreatePatchFile()
	{
		if (responseTimer) {
			if (--responseTimer == 0) {
				refreshMappings();

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

template<size_t NumKnobMaps>
struct MetaModuleHubBaseWidget : CommModuleWidget {

	Label *valueLabel;
	MetaModuleHubBase<NumKnobMaps> *hubModule;

	MetaModuleHubBaseWidget() = default;

	template<typename KnobType>
	void addLabeledKnobPx(const std::string labelText, int knobId, Vec posPx, float defaultValue = 0.f)
	{
		HubKnobMapButton *button;

		if (hubModule) {
			button = new HubKnobMapButton{*this, hubModule->knobMaps[knobId]};
		} else {
			button = new HubKnobMapButton{*this};
		}

		button->box.pos = Vec(posPx.x - mm2px(kKnobSpacingX) / 2, posPx.y - mm2px(kKnobSpacingY) / 2); // top-left
		button->box.size.x = mm2px(kKnobSpacingX);
		button->box.size.y = mm2px(kKnobSpacingY + 4);
		button->text = labelText;
		button->id = {LabelButtonID::Types::Knob, knobId, hubModule ? hubModule->id : -1};
		addChild(button);

		auto *p = new HubKnob<KnobType>(*button);
		p->box.pos = posPx;
		p->box.pos = p->box.pos.minus(p->box.size.div(2));
		if (module) {
			p->paramQuantity = module->paramQuantities[knobId];
			p->paramQuantity->defaultValue = defaultValue;
		}
		addParam(p);
	}

	template<typename KnobType>
	void addLabeledKnobMM(const std::string labelText, int knobId, Vec posMM, float defaultValue = 0.f)
	{
		Vec posPx = mm2px(posMM);
		addLabeledKnobPx<KnobType>(labelText, knobId, posPx, defaultValue);
	}

	enum class JackInOut { Input, Output };

	template<typename JackType>
	void addLabeledJackPx(const std::string labelText, int jackId, Vec posPx, JackInOut inout)
	{
		auto mapButton = new HubJackMapButton{*this};

		mapButton->box.pos = Vec(posPx.x - mm2px(kKnobSpacingX) / 2, posPx.y - mm2px(kKnobSpacingY) / 2); // top-left
		mapButton->box.size.x = mm2px(kKnobSpacingX);
		mapButton->box.size.y = mm2px(kKnobSpacingY);
		mapButton->text = labelText;
		auto type = inout == JackInOut::Input ? LabelButtonID::Types::InputJack : LabelButtonID::Types::OutputJack;
		mapButton->id = {type, jackId, hubModule ? hubModule->id : -1};
		addChild(mapButton);

		auto *jack = new HubJack<JackType>(*mapButton);
		jack->box.pos = posPx;
		jack->box.pos = jack->box.pos.minus(jack->box.size.div(2));
		jack->module = module;
		jack->type = inout == JackInOut::Input ? app::PortWidget::INPUT : app::PortWidget::OUTPUT;
		jack->portId = jackId;
		if (inout == JackInOut::Input)
			addInput(jack);
		else
			addOutput(jack);
	}
};
