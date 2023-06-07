#pragma once
#include "../comm/comm_module.hh"
#include "local_path.hh"
#include "mapping/Mapping2.h"
#include "mapping/central_data.hh"
#include "mapping/patch_writer.hh"
#include "util/string_util.hh"
#include <fstream>
#include <span>

struct MetaModuleHubBase : public CommModule {

	std::function<void()> updatePatchName;
	std::string labelText = "";
	std::string patchNameText = "";
	std::string patchDescText = "";

	bool shouldWritePatch = false;
	bool buttonAlreadyHandled = false;

	size_t numMappings;
	std::span<MappableObj::Type> mappingSrcs;

	static constexpr uint32_t MaxMapsPerPot = 8;

	using KnobParamHandles = std::array<Mapping2, MaxMapsPerPot>;
	std::array<KnobParamHandles, PanelDef::NumPot> paramHandles;

	MetaModuleHubBase(const std::span<MappableObj::Type> mappingSrcs)
		: numMappings{mappingSrcs.size()}
		, mappingSrcs{mappingSrcs} {

		for (unsigned i = 0; auto &pot : paramHandles) {
			auto color = PaletteHub::color(i++);
			for (auto &map : pot) {
				map.paramHandle.color = color;
				APP->engine->addParamHandle(&map.paramHandle);
				printf("%d, %p\n", i, &map.paramHandle);
			}
		}
	}

	~MetaModuleHubBase() {
		centralData->unregisterKnobMapsBySrcModule(id);
		for (auto &pot : paramHandles) {
			for (auto &map : pot)
				APP->engine->removeParamHandle(&map.paramHandle);
		}
	}

	Mapping2 *next_free_map(unsigned hubParamId) {
		// Find first unused paramHandle
		for (auto &p : paramHandles[hubParamId]) {
			if (p.paramHandle.moduleId < 0) {
				return &p;
			}
		}
		// If all are used, then overwrite the last one
		return &paramHandles[hubParamId][MaxMapsPerPot - 1];
	}

	bool registerMapDest(int hubParamId, rack::Module *module, int64_t moduleParamId) {
		if (!centralData->isMappingInProgress()) {
			pr_dbg("Error: registerMapDest() called but we aren't mapping!\n");
			return false;
		}

		if (!module) {
			pr_dbg("Error: Dest module ptr is null. Aborting mapping.\n");
			return false;
		}

		if (centralData->isRegisteredHub(module->id)) {
			pr_dbg("Dest module is a hub. Aborting mapping.\n");
			return false;
		}

		auto *map = next_free_map(hubParamId);
		printf("next free map: %p\n", &map->paramHandle);

		APP->engine->updateParamHandle(&map->paramHandle, module->id, moduleParamId, true);
		map->panelParamId = hubParamId;
		map->range_max = 1.f;
		map->range_min = 0.f;
		map->alias_name = "";

		return true;
	}

	void processKnobMaps() {
		for (int hubParamId = 0; auto &knobs : paramHandles) {
			for (auto &map : knobs) {

				int paramId = map.paramHandle.paramId;
				auto module = map.paramHandle.module;
				if (!module)
					continue;

				rack::ParamQuantity *paramQuantity = module->paramQuantities[paramId];
				if (!paramQuantity)
					continue;
				if (!paramQuantity->isBounded())
					continue;

				auto val = MathTools::map_value(params[hubParamId].getValue(), 0.f, 1.f, map.range_min, map.range_max);
				paramQuantity->setScaledValue(val);
			}
			hubParamId++;
		}
	}

	void processPatchButton(float patchButtonState) {
		if (buttonJustPressed(patchButtonState)) {
			shouldWritePatch = true;
			updatePatchName();
			updateDisplay();
		}
	}

	void processCreatePatchFile() {
		if (shouldWritePatch) {
			shouldWritePatch = false;

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
			writePatchFile(patchFileName, patchStructName.str, patchName, patchDescText);

			labelText = "Wrote patch file: ";
			labelText += patchStructName.str + ".yml";
			updateDisplay();
		}
	}

	// This is called periodically on auto-save
	// maps and the patch name/description are converted to json
	json_t *dataToJson() override {
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
			printf("Error: Widget has not been constructed, but dataToJson is being called\n");
		return rootJ;
	}

	// This is called on startup, and on loading a new patch file
	// json is converted to centralData->maps
	void dataFromJson(json_t *rootJ) override {
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
						mapping.dst.objType = MappableObj::Type::None;

					val = json_object_get(mappingJ, "SrcModID");
					mapping.src.moduleID = json_is_integer(val) ? json_integer_value(val) : -1;

					val = json_object_get(mappingJ, "SrcObjID");
					mapping.src.objID = json_is_integer(val) ? json_integer_value(val) : -1;

					val = json_object_get(mappingJ, "SrcObjType");
					if (json_is_string(val))
						mapping.src.setObjTypeFromString(json_string_value(val));
					else
						mapping.src.objType = MappableObj::Type::None;

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
		}
	}

private:
	bool buttonJustPressed(bool button_value) {
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

	void
	writePatchFile(std::string fileName, std::string patchStructName, std::string patchName, std::string patchDesc) {
		labelText = "Creating patch...";
		updateDisplay();

		auto context = rack::contextGet();
		auto engine = context->engine;

		std::vector<ModuleID> moduleData;
		std::vector<ParamStatus> paramData;
		for (auto moduleID : engine->getModuleIds()) {
			auto *module = engine->getModule(moduleID);
			if (centralData->isInPlugin(module)) {
				moduleData.push_back({moduleID, module->model->slug.c_str()});
				if (module->model->slug.size() > 31)
					printf("Warning: module slug truncated to 31 chars\n");

				if (!centralData->isHub(module)) {
					for (int i = 0; auto &p : module->params) {
						paramData.push_back({.value = p.value, .paramID = i, .moduleID = moduleID});
						i++;
					}
				}
			}
		}

		std::vector<JackStatus> jackData;
		for (auto cableID : engine->getCableIds()) {
			auto cable = engine->getCable(cableID);
			auto source = cable->outputModule;
			auto dest = cable->inputModule;

			if (centralData->isModuleInPlugin(source) && centralData->isModuleInPlugin(dest)) {
				jackData.push_back({.sendingJackId = cable->outputId,
									.receivedJackId = cable->inputId,
									.sendingModuleId = source->getId(),
									.receivedModuleId = dest->getId(),
									.connected = true});
			}
		}

		PatchFileWriter pw{moduleData};
		pw.setPatchName(patchName);
		pw.setPatchDesc(patchDesc);
		pw.setJackList(jackData);
		pw.setParamList(paramData);

		std::vector<Mapping> maps;
		maps.reserve(centralData->maps.size());
		for (auto &m : centralData->maps)
			maps.push_back({m.src, m.dst, m.range_min, m.range_max, m.alias_name});
		pw.addMaps(maps);

		std::string yml = pw.printPatchYAML();
		writeToFile(fileName + ".yml", yml);
		writeAsHeader(fileName + ".hh", patchStructName + "_patch", yml);
	}

	void writeToFile(const std::string &fileName, std::string textToWrite) {
		std::ofstream myfile;
		myfile.open(fileName);
		myfile << textToWrite;
		myfile.close();
	}

	void writeAsHeader(const std::string &fileName, std::string_view structname, std::string_view textToWrite) {
		std::ofstream myfile;
		myfile.open(fileName);
		myfile << "static char " << structname << "[] = \n";
		myfile << "R\"(\n";
		myfile << textToWrite;
		myfile << "\n)\";";
		myfile.close();
	}

	void writeBinaryFile(const std::string &fileName, const std::vector<unsigned char> data) {
		std::ofstream myfile{fileName, std::ios_base::binary | std::ios_base::out | std::ios_base::trunc};
		myfile.write(reinterpret_cast<const char *>(data.data()), data.size());
		myfile.close();
	}
};
