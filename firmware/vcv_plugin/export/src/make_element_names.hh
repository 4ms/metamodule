#pragma once
#include "util/contains_word.hh"
#include "util/overloaded.hh"
#include <engine/Module.hpp>

namespace MetaModule
{

static void remove_extended_chars(std::string &name) {
	// Do nothing -- all fonts have been updated with many unicode chars
	// But keep this function here in case we need to start filtering again
	// for (auto &c : name) {
	// 	if (c < 0)
	// 		c = '_';
	// }
}

inline std::string_view getParamName(rack::engine::Module *module, int id) {
	if (auto pq = module->getParamQuantity(id)) {
		if (pq->name.size() && pq->name != " ") {
			remove_extended_chars(pq->name);
			return pq->name;
		} else {
			pq->name = "Param " + std::to_string(id + 1);
			return pq->name;
		}
	} else {
		if ((size_t)id < module->paramQuantities.size()) {
			module->paramQuantities[id] = new rack::engine::ParamQuantity;
			module->paramQuantities[id]->name = "Param " + std::to_string(id + 1);
			return module->paramQuantities[id]->name;
		}
	}
	return "(Param)";
}

inline std::string_view getInputName(rack::engine::Module *module, int id) {
	if (auto info = module->getInputInfo(id)) {
		if (info->name.size()) {
			remove_extended_chars(info->name);
			if (!contains_word(info->name, "in") && !contains_word(info->name, "input"))
				info->name += " In";
			return info->name;
		} else {
			info->name = "In " + std::to_string(id + 1);
			return info->name;
		}
	} else {
		if ((size_t)id < module->inputInfos.size()) {
			module->inputInfos[id] = new rack::engine::PortInfo;
			module->inputInfos[id]->name = "In " + std::to_string(id + 1);
			return module->inputInfos[id]->name;
		}
	}

	return "(In)";
}

inline std::string_view getOutputName(rack::engine::Module *module, int id) {
	if (auto info = module->getOutputInfo(id)) {
		if (info->name.size()) {
			remove_extended_chars(info->name);
			if (!contains_word(info->name, "out") && !contains_word(info->name, "output"))
				info->name += " Out";
			return info->name;
		} else {
			info->name = "Out " + std::to_string(id + 1);
			return info->name;
		}
	} else {
		if ((size_t)id < module->outputInfos.size()) {
			module->outputInfos[id] = new rack::engine::PortInfo;
			module->outputInfos[id]->name = "Out " + std::to_string(id + 1);
			return module->outputInfos[id]->name;
		}
	}
	return "(Out)";
}

inline std::string_view getLightName(rack::engine::Module *module, int id) {
	if (auto info = module->getLightInfo(id)) {
		if (info->name.size()) {
			remove_extended_chars(info->name);
			return info->name;
		}
	}
	return "(Light)";
}

// Debug helper:
inline ImageElement image_element(MetaModule::Element const &el) {
	return std::visit(overloaded{
						  [](BaseElement const &) { return ImageElement{}; },
						  [](ImageElement const &e) { return e; },
					  },
					  el);
}

} // namespace MetaModule
