#pragma once
#include "mapping/JackMap.hh"
#include "mapping/ModuleID.h"
#include "mapping/ParamMap.hh"
#include "mapping/module_directory.hh"
#include "mapping/patch_writer.hh"
#include <fstream>
#include <rack.hpp>

// Adpats VCVRack-format of patch data to a format PatchFileWriter can use
struct VCVPatchFileWriter {

	static void writePatchFile(
		int64_t hubModuleId, auto &mappings, std::string fileName, std::string patchName, std::string patchDesc) {

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
					for (int i = 0; auto &p : module->params) {
						paramData.push_back({.value = p.value, .paramID = i, .moduleID = moduleID});
						i++;
					}
				}
			}
		}

		std::vector<CableMap> cableData;
		for (auto cableID : engine->getCableIds()) {
			auto cable = engine->getCable(cableID);
			auto out = cable->outputModule;
			auto in = cable->inputModule;

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
			});
		}

		PatchFileWriter pw{moduleData, hubModuleId};
		pw.setPatchName(patchName);
		pw.setPatchDesc(patchDesc);
		pw.setCableList(cableData);
		pw.setParamList(paramData);

		for (unsigned hubParamId = 0; auto &knob_maps : mappings) {
			std::vector<Mapping> active_maps;
			active_maps.reserve(8);

			for (auto &m : knob_maps) {
				if (m.paramHandle.module && m.paramHandle.moduleId > 0)
					active_maps.push_back(m);
			}

			if (active_maps.size())
				pw.addKnobMaps(hubParamId, active_maps);

			hubParamId++;
		}

		std::string yml = pw.printPatchYAML();
		writeToFile(fileName, yml);
		// writeAsHeader(fileName + ".hh", patchStructName + "_patch", yml);
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
