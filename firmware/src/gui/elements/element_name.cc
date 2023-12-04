#include "element_name.hh"
#include "CoreModules/moduleFactory.hh"
#include "gui/elements/context.hh"
#include "patch/patch.hh"
#include "patch/patch_data.hh"

namespace MetaModule
{

// Return the module name and element name, given the IDs and type (not the Element)
FullElementName
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

void append_connected_jack_name(std::string &opts, GuiElement const &drawn, PatchData const &patch) {

	FullElementName name{"", ""};
	if (drawn.idx.input_idx != ElementCount::Indices::NoElementMarker) {
		Jack in_jack = {.module_id = drawn.module_idx, .jack_id = drawn.idx.input_idx};
		if (auto *cable = patch.find_internal_cable_with_injack(in_jack)) {
			name = get_full_element_name(cable->out.module_id, cable->out.jack_id, ElementType::Output, patch);
		}
	}
	if (drawn.idx.output_idx != ElementCount::Indices::NoElementMarker) {
		Jack out_jack = {.module_id = drawn.module_idx, .jack_id = drawn.idx.input_idx};
		if (auto *cable = patch.find_internal_cable_with_outjack(out_jack)) {
			name = get_full_element_name(cable->ins[0].module_id, cable->ins[0].jack_id, ElementType::Input, patch);
		}
	}
	if (name.module_name.size() || name.element_name.size()) {
		opts = opts + " [" + std::string(name.module_name) + " " + std::string(name.element_name) + "]";
	}
}

} // namespace MetaModule
