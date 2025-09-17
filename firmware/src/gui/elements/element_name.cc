#include "element_name.hh"
#include "CoreModules/moduleFactory.hh"
#include "gui/elements/panel_name.hh"
#include "gui/styles.hh"
#include "patch/patch.hh"
#include "patch/patch_data.hh"
#include "util/overloaded.hh"

namespace MetaModule
{

// Return the module name and element name, given the IDs and type (not the Element)
FullElementName
get_full_element_name(unsigned module_id, unsigned element_idx, ElementType type, PatchData const &patch) {
	FullElementName fullname{"?", "?"};

	if (module_id < patch.module_slugs.size()) {
		fullname.module_name = ModuleFactory::getModuleDisplayName(patch.module_slugs[module_id]);

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

static std::string get_mapped_color(Element const &element, uint16_t panel_id) {
	return std::visit(
		overloaded{
			[=](ParamElement const &el) { return std::string(Gui::color_to_html(Gui::get_knob_color(panel_id))); },
			[=](JackElement const &el) { return Gui::color_to_html(Gui::mapped_jack_color(panel_id)); },
			[](BaseElement const &) { return std::string(""); },
		},
		element);
}

void append_panel_name(std::string &opts, Element const &el, uint16_t mapped_panel_id) {
	const auto name = std::visit([=](auto &e) { return get_panel_name(e, mapped_panel_id); }, el);
	if (name.size() < 0)
		return;
	const auto color = get_mapped_color(el, mapped_panel_id);
	if (color[0] == '\0')
		return;
	opts += " ";
	opts += Gui::color_text(name, color);
}

void append_connected_jack_name(std::string &opts,
								ElementCount::Indices indices,
								uint16_t module_idx,
								PatchData const &patch) {

	auto append = [&opts, &patch](Jack jack, ElementType type) {
		FullElementName name = get_full_element_name(jack.module_id, jack.jack_id, type, patch);
		opts = opts + " [" + std::string(name.module_name) + " " + std::string(name.element_name) + "] ";
	};

	if (indices.input_idx != ElementCount::Indices::NoElementMarker) {
		Jack in_jack = {.module_id = module_idx, .jack_id = indices.input_idx};

		if (auto *cable = patch.find_internal_cable_with_injack(in_jack)) {
			if (auto out_map = patch.find_mapped_outjack(cable->out)) {
				const auto color = get_mapped_color(JackOutput{}, out_map->panel_jack_id);
				const auto p_name = get_panel_name(JackOutput{}, out_map->panel_jack_id);
				opts += " " + Gui::color_text(p_name, color);
			}

			append(cable->out, ElementType::Output);

			for (auto &in : cable->ins) {
				if (in != in_jack)
					append(in, ElementType::Input);
			}
		}
	}

	else if (indices.output_idx != ElementCount::Indices::NoElementMarker)
	{
		Jack out_jack = {.module_id = module_idx, .jack_id = indices.output_idx};

		if (auto *cable = patch.find_internal_cable_with_outjack(out_jack)) {
			for (auto &in : cable->ins)
				append(in, ElementType::Input);
		}
	}
}

void param_item_name(std::string &s, MappedKnob const &map, PatchData const *patch) {
	if (map.alias_name.length()) {
		s = std::string_view{map.alias_name};
	} else {
		auto fullname = get_full_element_name(map.module_id, map.param_id, ElementType::Param, *patch);
		s = fullname.element_name;
		s.append(" - ");
		s.append(fullname.module_name);
	}
}

} // namespace MetaModule
