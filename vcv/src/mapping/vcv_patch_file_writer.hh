#pragma once
#include "hub/hub_knob_mappings.hh"
#include "mapping/JackMap.hh"
#include "mapping/ModuleID.h"
#include "mapping/ParamMap.hh"
#include "mapping/module_directory.hh"
#include "mapping/patch_writer.hh"
#include <fstream>
#include <rack.hpp>
#include "lv_color.h"

// Adpats VCVRack-format of patch data to a format PatchFileWriter can use
template<size_t NumKnobs, size_t MaxMapsPerPot, size_t MaxKnobSets>
struct VCVPatchFileWriter {
	using HubKnobsMultiMap = typename HubKnobMappings<NumKnobs, MaxMapsPerPot, MaxKnobSets>::HubKnobsMultiMaps;

	static void writePatchFile(int64_t hubModuleId,
							   HubKnobsMultiMap &mappings,
							   std::span<std::string> knobSetNames,
							   std::string fileName,
							   std::string patchName,
							   std::string patchDesc) {

		auto context = rack::contextGet();
		auto engine = context->engine;

		// Find all compatible modules in this patch
		// TODO: only add modules that are mapped to this hub
		// Find all knobs on those modules (static knobs)
		std::vector<ModuleID> moduleData;
		std::vector<ParamMap> paramData;
		for (auto moduleID : engine->getModuleIds()) {
			auto *module = engine->getModule(moduleID);
			if (ModuleDirectory::isInPlugin(module)) {

				moduleData.push_back({moduleID, module->model->slug.c_str()});
				if (module->model->slug.size() > 31)
					printf("Warning: module slug truncated to 31 chars\n");

				if (!ModuleDirectory::isHub(module)) {
					for (size_t i = 0; i < module->paramQuantities.size(); i++) { //auto &p : module->params) {
						float val = module->getParamQuantity(i)->getScaledValue();
						paramData.push_back({.value = val, .paramID = (int)i, .moduleID = moduleID});
					}
				}
			}
		}

		std::vector<CableMap> cableData;
		for (auto cableID : engine->getCableIds()) {
			auto cable = engine->getCable(cableID);
			auto out = cable->outputModule;
			auto in = cable->inputModule;
			
			lv_color_t color = {{0, 0, 0}};
			for (auto cableWidget : APP->scene->rack->getCompleteCables()) {
				if (cableWidget->cable == cable) {
					color = lv_color_make((int)(255*cableWidget->color.r), (int)(255*cableWidget->color.g), (int)(255*cableWidget->color.b));
					break;
				}
			}

			// Both modules on a cable must be in the plugin
			if (!ModuleDirectory::isInPlugin(out) || !ModuleDirectory::isInPlugin(in))
				continue;

			// Ignore cables that are connected to a different hub
			if (ModuleDirectory::isHub(out) && (out->getId() != hubModuleId))
				continue;
			if (ModuleDirectory::isHub(in) && (in->getId() != hubModuleId))
				continue;

			// Ignore two hub jacks patched together
			if (ModuleDirectory::isHub(out) && ModuleDirectory::isHub(in))
				continue;

			cableData.push_back({
				.sendingJackId = cable->outputId,
				.receivedJackId = cable->inputId,
				.sendingModuleId = out->getId(),
				.receivedModuleId = in->getId(),
				.lv_color_full = color.full,
			});
		}

		PatchFileWriter pw{moduleData, hubModuleId};
		pw.setPatchName(patchName);
		pw.setPatchDesc(patchDesc);
		pw.setCableList(cableData);
		pw.setParamList(paramData);

		// Iterate mappings, by MaxKnobSets times
		for (unsigned set_i = 0; set_i < MaxKnobSets; set_i++) {
			pw.addKnobMapSet(set_i, knobSetNames[set_i]);

			for (unsigned hubParamId = 0; auto &knob_maps : mappings) {

				std::vector<Mapping> active_maps;
				active_maps.reserve(8);

				for (auto &mapsets : knob_maps) {
					auto &map = mapsets.maps[set_i];
					if (map.moduleId > 0)
						active_maps.push_back(map);
				}

				if (active_maps.size())
					pw.addKnobMaps(hubParamId, set_i, active_maps);

				hubParamId++;
			}
		}

		std::string yml = pw.printPatchYAML();
		writeToFile(fileName, yml);
		// writeAsHeader(fileName + ".hh", patchName + "_patch", yml);
	}

	static void writeToFile(const std::string &fileName, std::string textToWrite) {
		std::ofstream myfile;
		myfile.open(fileName);
		myfile << textToWrite;
		myfile.close();
	}

	static void writeAsHeader(const std::string &fileName, std::string_view structname, std::string_view textToWrite) {
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
