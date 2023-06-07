#pragma once
#include "../comm/comm_module.hh"
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

	MetaModuleHubBase(const std::span<MappableObj::Type> mappingSrcs)
		: numMappings{mappingSrcs.size()}
		, mappingSrcs{mappingSrcs} {
	}

	~MetaModuleHubBase() {
		centralData->unregisterKnobMapsBySrcModule(id);
	}

	// This is called periodically on auto-save
	// CentralData->maps and the patch name/description are converted to json
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

	// Hub class needs to call this from its process
	void processKnobMaps() {
		//TODO: range for
		for (unsigned i = 0; i < numMappings; i++) {
			MappableObj src{mappingSrcs[i], i, id};
			auto maps = centralData->getMappingsFromSrc(src);
			for (auto &m : maps) {
				if (m.dst.moduleID != -1) {
					Module *module = m.dst_module;
					if (module) {
						int paramId = m.dst.objID;
						MappableObj dst{MappableObj::Type::Knob, paramId, m.dst.moduleID};
						auto [min, max] = centralData->getMapRange(src, dst);
						auto knob_min = module->paramQuantities[paramId]->minValue;
						auto knob_max = module->paramQuantities[paramId]->maxValue;
						min = MathTools::map_value(min, 0.f, 1.f, knob_min, knob_max);
						max = MathTools::map_value(max, 0.f, 1.f, knob_min, knob_max);
						auto newMappedVal = MathTools::map_value(params[i].getValue(), 0.f, 1.f, min, max);
						auto paramQuantity = module->paramQuantities[paramId];
						paramQuantity->setValue(newMappedVal);
					} else {
						// disable the mapping because the module was deleted
						// FIXME: send a message to centralData that the module was deleted.
						// Or better yet, make sure every module's destructor removes its mappings from centralData
					}
				}
			}
		}
	}

	// Hub class needs to call this from its process
	void processPatchButton(float patchButtonState) {
		if (buttonJustPressed(patchButtonState)) {
			shouldWritePatch = true;
			updatePatchName();
			updateDisplay();
		}
	}

	// Hub class needs to call this from its process
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

	bool registerMapDest(rack::Module *module, int64_t paramId) {
		return false;
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
