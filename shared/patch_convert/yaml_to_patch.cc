#include "yaml_to_patch.hh"
#include "ryml/ryml_serial.hh"

bool yaml_string_to_patch(std::string yaml, PatchData &pd) {
	RymlInit::init_once();

	ryml::Tree tree = ryml::parse_in_place(ryml::substr(yaml.data(), yaml.size()));

	if (tree.num_children(0) == 0)
		return false;

	ryml::NodeRef data_root = tree[0];
	if (data_root.key() != "PatchData")
		return false;

	data_root["patch_name"] >> pd.patch_name;

	data_root["module_slugs"] >> pd.module_slugs;
	data_root["int_cables"] >> pd.int_cables;
	data_root["mapped_ins"] >> pd.mapped_ins;

	data_root["mapped_outs"] >> pd.mapped_outs;
	data_root["static_knobs"] >> pd.static_knobs;
	data_root["mapped_knobs"] >> pd.mapped_knobs;

	return true;
}
