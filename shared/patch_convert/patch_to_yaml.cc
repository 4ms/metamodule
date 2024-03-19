#include "patch_to_yaml.hh"
#include "ryml/ryml_serial.hh"
#include <span>

static ryml::Tree create_tree(PatchData const &pd, ryml::Tree &tree) {
	ryml::NodeRef root = tree.rootref();
	root |= ryml::MAP;

	ryml::NodeRef data = root["PatchData"];
	data |= ryml::MAP;

	data["patch_name"] << pd.patch_name;
	data["description"] << pd.description;
	data["module_slugs"] << pd.module_slugs;
	data["int_cables"] << pd.int_cables;
	data["mapped_ins"] << pd.mapped_ins;
	data["mapped_outs"] << pd.mapped_outs;
	data["static_knobs"] << pd.static_knobs;
	data["mapped_knobs"] << pd.knob_sets;
	data["midi_maps"] << pd.midi_maps;
	data["midi_poly_num"] << pd.midi_poly_num;
	data["vcvModuleStates"] << pd.module_states;

	return tree;
}

std::string patch_to_yaml_string(PatchData const &pd) {
	RymlInit::init_once();

	ryml::Tree tree;
	create_tree(pd, tree);

	return ryml::emitrs_yaml<std::string>(tree);
}

size_t patch_to_yaml_buffer(PatchData const &pd, std::span<char> &buffer) {
	RymlInit::init_once();

	ryml::Tree tree;
	create_tree(pd, tree);

	ryml::substr s{buffer.data(), buffer.size()};
	bool emit_error_on_overflow = true;
	auto res = ryml::emit_yaml(tree, s, emit_error_on_overflow);
	//resize
	buffer = buffer.subspan(0, res.size());
	return res.size();
}

std::string json_to_yml(std::string json) {
	if (json.back() == '\0')
		json.pop_back();

	ryml::Tree tree = ryml::parse_in_place(ryml::to_substr(json));

	return ryml::emitrs_yaml<std::string>(tree);
}
