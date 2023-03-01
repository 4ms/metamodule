#pragma once
#include "CoreModules/moduleFactory.hh"
#include "comm_data.hh"
#include "comm_module.hh"
#include "comm_widget.hh"
#include "hub_jack.hh"
#include "hub_knob.hh"
#include "local_path.hh"
#include "map_palette.hh"
#include "patch_writer.hh"
#include "plugin.hh"
#include "util/math.hh"
#include "util/string_util.hh"
#include <fstream>
#include <functional>
#include <string.h>

template<int NumKnobMaps>
struct MetaModuleHubBase : public CommModule {

	std::function<void()> updatePatchName;
	std::string labelText = "";
	std::string patchNameText = "";
	std::string patchDescText = "";

	long responseTimer = 0;
	bool buttonAlreadyHandled = false;

	MetaModuleHubBase() = default;

	~MetaModuleHubBase() { centralData->unregisterKnobMapsBySrcModule(id); }

	// This is called periodically on auto-save
	// CentralData->maps and the patch name/description are converted to json
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
			json_object_set_new(thisMapJ, "RangeMin", json_real(m.range_min));
			json_object_set_new(thisMapJ, "RangeMax", json_real(m.range_max));
			json_object_set_new(thisMapJ, "AliasName", json_string(m.alias_name.c_str()));

			json_array_append(mapsJ, thisMapJ);
			json_decref(thisMapJ);
		}
		json_object_set_new(rootJ, "Mappings", mapsJ);

		if (updatePatchName) {
			updatePatchName();
			json_t *patchNameJ = json_string(patchNameText.c_str());
			json_object_set_new(rootJ, "PatchName", patchNameJ);

			json_t *patchDescJ = json_string(patchDescText.c_str());
			json_object_set_new(rootJ, "PatchDesc", patchDescJ);
		} else
			printf("Error: CommModuleWidget has not been constructed, but dataToJson is being called\n");
		return rootJ;
	}

	// This is called on startup, and on loading a new patch file
	// json is converted to centralData->maps
	void dataFromJson(json_t *rootJ) override
	{
		auto patchNameJ = json_object_get(rootJ, "PatchName");
		if (json_is_string(patchNameJ)) {
			patchNameText = json_string_value(patchNameJ);
		}

		auto patchDescJ = json_object_get(rootJ, "PatchDesc");
		if (json_is_string(patchDescJ)) {
			patchDescText = json_string_value(patchDescJ);
		}

		auto mapsJ = json_object_get(rootJ, "Mappings");
		if (json_is_array(mapsJ)) {
			centralData->maps.clear();
			for (size_t i = 0; i < json_array_size(mapsJ); i++) {
				auto mappingJ = json_array_get(mapsJ, i);
				CentralData::MappingExt mapping;

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

					val = json_object_get(mappingJ, "AliasName");
					if (json_is_string(val))
						mapping.alias_name = json_string_value(val);
					else
						mapping.alias_name = "";

					mapping.dst_module = centralData->getRegisteredModulePtr(mapping.dst.moduleID);

					centralData->maps.push_back(mapping);
				}
			}
			// for (auto &m : centralData->maps) {
			// 	if (m.src.objType == LabelButtonID::Types::Knob) {
			// 		centralData->registerKnobParamHandle(m.src, m.dst);
			// 	}
			// }
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
		for (int i = 0; i < NumKnobMaps; i++) {
			// TODO:
			//  LabelButtonID src{mapSrcType[i], i, id};
			LabelButtonID src{LabelButtonID::Types::Knob, i, id};
			auto maps = centralData->getMappingsFromSrc(src);
			for (auto &m : maps) {
				if (m.dst.moduleID != -1) {
					Module *module = m.dst_module;
					if (module) {
						int paramId = m.dst.objID;
						LabelButtonID dst{LabelButtonID::Types::Knob, paramId, m.dst.moduleID};
						auto [min, max] = centralData->getMapRange(src, dst);
						auto newMappedVal = MathTools::map_value(params[i].getValue(), 0.0f, 1.0f, min, max);
						ParamQuantity *paramQuantity = module->paramQuantities[paramId];
						paramQuantity->setValue(newMappedVal);
					} else {
						// disable the mapping because the module was deleted
						// paramHandle->moduleId = -1;
						// FIXME: send a message to centralData that the module was deleted.
						// Or better yet, make sure every module's destructor removes its mappings from centralData
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
				// TODO:add patchDesc here:
				writePatchFile(patchFileName, patchStructName.str, patchName, patchDescText);

				labelText = "Wrote patch file: ";
				labelText += patchStructName.str + ".yml";
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

	void writePatchFile(std::string fileName, std::string patchStructName, std::string patchName, std::string patchDesc)
	{
		labelText = "Creating patch..";
		updateDisplay();

		std::vector<ModuleID> moduleData;
		moduleData.reserve(centralData->moduleData.size());
		for (auto &m : centralData->moduleData)
			moduleData.push_back({m.id, m.slug});

		PatchFileWriter pw{moduleData};
		pw.setPatchName(patchName);
		pw.setPatchDesc(patchDesc);
		pw.setJackList(centralData->jackData);
		pw.setParamList(centralData->paramData);
		std::vector<Mapping> maps;
		maps.reserve(centralData->maps.size());
		for (auto &m : centralData->maps)
			maps.push_back({m.src, m.dst, m.range_max, m.range_min, m.alias_name});
		pw.addMaps(maps);

		std::string yml = pw.printPatchYAML();
		writeToFile(fileName + ".yml", yml);
		writeAsHeader(fileName + ".hh", patchStructName + "_patch", yml);
	}

	void writeToFile(std::string fileName, std::string textToWrite)
	{
		std::ofstream myfile;
		myfile.open(fileName);
		myfile << textToWrite;
		myfile.close();
	}

	void writeAsHeader(std::string_view fileName, std::string_view structname, std::string_view textToWrite)
	{
		std::ofstream myfile;
		myfile.open(fileName);
		myfile << "static char " << structname << "[] = \n";
		myfile << "R\"(\n";
		myfile << textToWrite;
		myfile << "\n)\";";
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

	// void onHover(const HoverEvent &e) override
	// {
	// 	CommModuleWidget::onHover(e);
	// 	centralData->processKnobParamHandleQueue();
	// do {
	// 	auto [src, dst] = centralData->popRegisterKnobParamHandle();
	// 	if (src.moduleID < 0 || dst.moduleID < 0)
	// 		break;
	// 	centralData->registerKnobParamHandle(src, dst);
	// } while (true);
	// }

	template<typename KnobType>
	void addLabeledKnobPx(const std::string labelText, int knobId, Vec posPx, float defaultValue = 0.f)
	{
		HubKnobMapButton *button = new HubKnobMapButton{*this};
		button->box.pos = Vec(posPx.x - mm2px(kKnobSpacingX) / 2, posPx.y - mm2px(kKnobSpacingY) / 2); // top-left
		button->box.size.x = mm2px(kKnobSpacingX);
		button->box.size.y = mm2px(kKnobSpacingY);
		button->text = labelText;
		button->id = {LabelButtonID::Types::Knob, knobId, hubModule ? hubModule->id : -1};
		addChild(button);

		auto *p = new HubKnob<KnobType>{*button};
		p->box.pos = posPx;
		p->box.pos = p->box.pos.minus(p->box.size.div(2));
		p->app::ParamWidget::module = hubModule;
		p->app::ParamWidget::paramId = knobId;
		p->initParamQuantity();

		if (module) {
			auto pq = p->getParamQuantity();
			pq = module->paramQuantities[knobId];
			pq->defaultValue = defaultValue;
			button->setParamQuantity(pq);
		}
		addParam(p);
	}

	template<typename KnobType>
	void addLabeledKnobMM(const std::string labelText, int knobId, Vec posMM, float defaultValue = 0.f)
	{
		Vec posPx = mm2px(posMM);
		addLabeledKnobPx<KnobType>(labelText, knobId, posPx, defaultValue);
	}

	enum class JackDir { Input, Output };

	template<typename JackType>
	void addLabeledJackPx(const std::string labelText, int jackId, Vec posPx, JackDir inout)
	{
		auto mapButton = new HubJackMapButton{*this};

		mapButton->box.pos = Vec(posPx.x - mm2px(kKnobSpacingX) / 2, posPx.y - mm2px(kKnobSpacingY) / 2); // top-left
		mapButton->box.size.x = mm2px(kKnobSpacingX);
		mapButton->box.size.y = mm2px(kKnobSpacingY);
		mapButton->text = labelText;
		auto type = inout == JackDir::Input ? LabelButtonID::Types::InputJack : LabelButtonID::Types::OutputJack;
		mapButton->id = {type, jackId, hubModule ? hubModule->id : -1};
		addChild(mapButton);

		auto *jack = new HubJack<JackType>(*mapButton);
		jack->box.pos = posPx;
		jack->box.pos = jack->box.pos.minus(jack->box.size.div(2));
		jack->module = module;
		jack->type = inout == JackDir::Input ? Port::INPUT : Port::OUTPUT;
		jack->portId = jackId;
		if (inout == JackDir::Input)
			addInput(jack);
		else
			addOutput(jack);
	}
};
