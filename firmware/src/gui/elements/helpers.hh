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

inline JackName get_full_jack_name(Jack jack, JackDir dir, PatchData const &patch) {
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

} // namespace MetaModule
