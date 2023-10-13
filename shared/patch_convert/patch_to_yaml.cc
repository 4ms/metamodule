#include "patch_to_yaml.hh"
#include "ryml/ryml_serial.hh"
#include "util/byte_block.hh"
#include "util/countzip.hh"

std::string patch_to_yaml_string(PatchData const &pd) {
	RymlInit::init_once();

	ryml::Tree tree;
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

	return ryml::emitrs_yaml<std::string>(tree);
}

std::string json_to_yml(std::string json) {
	if (json.back() == '\0')
		json.pop_back();

	ryml::Tree tree = ryml::parse_in_place(ryml::to_substr(json));

	return ryml::emitrs_yaml<std::string>(tree);
}
