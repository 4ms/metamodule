#pragma once
#include "../comm/comm_module.hh"
#include "hub_knob_mappings.hh"
#include "local_path.hh"
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
	HubKnobMappings<PanelDef::NumPot, MaxMapsPerPot> mappings{id};

	MetaModuleHubBase(const std::span<MappableObj::Type> mappingSrcs)
		: numMappings{mappingSrcs.size()}
		, mappingSrcs{mappingSrcs} {
	}

	~MetaModuleHubBase() {
		// centralData->unregisterKnobMapsBySrcModule(id);
	}

	bool registerMap(int hubParamId, rack::Module *module, int64_t moduleParamId) {
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

		auto *map = mappings.addMap(hubParamId, module->id, moduleParamId);
		map->range_max = 1.f;
		map->range_min = 0.f;
		map->alias_name = "";

		return true;
	}

	void processMaps() {
		for (int hubParamId = 0; auto &knobs : mappings) {
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
		json_t *rootJ = mappings.encodeJson();

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

		mappings.decodeJson(rootJ);
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
