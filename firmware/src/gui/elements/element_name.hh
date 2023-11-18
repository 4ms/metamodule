#pragma once
#include "CoreModules/moduleFactory.hh"
#include "patch/patch.hh"
#include "patch/patch_data.hh"

namespace MetaModule
{

struct FullElementName {
	std::string_view module_name;
	std::string_view element_name;
};

enum class ElementType { Param, Input, Output, Light };

// Return the module name and element name, given the IDs and type (not the Element)
inline FullElementName
get_full_element_name(unsigned module_id, unsigned element_idx, ElementType type, PatchData const &patch) {
	FullElementName fullname{"?", "?"};

	if (module_id < patch.module_slugs.size()) {
		fullname.module_name = patch.module_slugs[module_id];

		auto &info = ModuleFactory::getModuleInfo(patch.module_slugs[module_id]);

		if (info.width_hp) {
			// Search in reverse (the matching element is the last one with the matching index)
			for (int el_id = info.indices.size() - 1; el_id >= 0; el_id--) {

				auto idx = info.indices[el_id];

				bool is_found = (type == ElementType::Param)  ? element_idx == idx.param_idx :
								(type == ElementType::Input)  ? element_idx == idx.input_idx :
								(type == ElementType::Output) ? element_idx == idx.output_idx :
								(type == ElementType::Light)  ? element_idx == idx.light_idx :
																false;
				if (is_found) {
					fullname.element_name = base_element(info.elements[el_id]).short_name;
					break;
				}
			}
		}
	}
	return fullname;
}

} // namespace MetaModule
