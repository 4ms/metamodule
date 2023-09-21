#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/moduleFactory.hh"
#include "patch/patch.hh"
#include "patch/patch_data.hh"
#include <algorithm>

namespace MetaModule
{

struct JackName {
	std::string_view module_name;
	std::string_view jack_name;
};

enum class JackDir { In, Out };

[[deprecated]] inline JackName get_full_jack_name(Jack jack, JackDir dir, PatchData const &patch) {
	JackName fullname{"?", "?"};
	if (jack.module_id < patch.module_slugs.size()) {
		fullname.module_name = patch.module_slugs[jack.module_id];
		auto &info = ModuleFactory::getModuleInfo(patch.module_slugs[jack.module_id]);

		if (info.width_hp) {
			auto res = std::ranges::find_if(info.indices, [=](auto idx) {
				return jack.jack_id == (dir == JackDir::In ? idx.input_idx : idx.output_idx);
			});
			if (res != info.indices.end()) {
				auto el_id = std::distance(info.indices.begin(), res);
				fullname.jack_name = base_element(info.elements[el_id]).short_name;
			}
		}
	}
	return fullname;
}

struct FullElementName {
	std::string_view module_name;
	std::string_view element_name;
};

enum class ElementType { Param, Input, Output, Light };

inline FullElementName
get_full_element_name(unsigned module_id, unsigned element_idx, ElementType type, PatchData const &patch) {
	FullElementName fullname{"?", "?"};

	if (module_id < patch.module_slugs.size()) {
		fullname.module_name = patch.module_slugs[module_id];

		auto &info = ModuleFactory::getModuleInfo(patch.module_slugs[module_id]);

		if (info.width_hp) {
			auto res = std::ranges::find_if(info.indices, [=](auto idx) {
				return (type == ElementType::Param)	 ? element_idx == idx.param_idx :
					   (type == ElementType::Input)	 ? element_idx == idx.input_idx :
					   (type == ElementType::Output) ? element_idx == idx.output_idx :
					   (type == ElementType::Light)	 ? element_idx == idx.light_idx :
													   false;
			});

			if (res != info.indices.end()) {
				auto el_id = std::distance(info.indices.begin(), res);
				fullname.element_name = base_element(info.elements[el_id]).short_name;
			}
		}
	}
	return fullname;
}

} // namespace MetaModule
