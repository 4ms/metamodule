#pragma once
#include "CoreModules/elements/element_strings.hh"
#include "util/overloaded.hh"
#include <engine/Module.hpp>

namespace MetaModule
{

inline std::string_view getParamName(rack::engine::Module *module, int id) {
	if (auto pq = module->getParamQuantity(id)) {
		if (pq->name.size()) {
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

inline void set_labels(std::span<std::string_view> pos_names, std::vector<std::string> &labels) {
	for (unsigned i = 0; auto &label : labels) {
		if (i >= pos_names.size())
			break;
		pos_names[i++] = label;
	}
}

inline void set_labels(rack::engine::ParamQuantity *pq, MetaModule::Element &element) {
	// Switches with strings for each position
	if (pq->labels.size() > 0) {
		using namespace MetaModule;
		std::visit(overloaded{
					   [](BaseElement &) {},
					   [&pq](FlipSwitch &el) {
						   el.num_pos = std::clamp<unsigned>(pq->maxValue - pq->minValue + 1, 2, 3);
						   set_labels(el.pos_names, pq->labels);
					   },
					   [&pq](SlideSwitch &el) {
						   el.num_pos = std::clamp<unsigned>(pq->maxValue - pq->minValue + 1, 2, 8);
						   set_labels(el.pos_names, pq->labels);
					   },
				   },
				   element);
	}
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
