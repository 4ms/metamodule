#include "yaml_to_patch.hh"
#include "ryml_serial.hh"

#include <iostream>

bool yaml_string_to_patch(std::string yaml, PatchHeader &ph, PatchData &pd) {

	ryml::Tree tree = ryml::parse_in_place(ryml::substr(yaml.data(), yaml.size()));

	//std::cout << "tree.num_children(0) == " << tree.num_children(0) << std::endl;
	if (tree.num_children(0) < 2)
		return false;

	//TODO: can we check if tree["PatchHeader"] is valid? That would allow header/data to be in either order
	ryml::NodeRef header_root = tree[0];
	if (header_root.key() != "PatchHeader")
		return false;

	header_root >> ph;

	ryml::NodeRef data_root = tree[1];
	if (data_root.key() != "PatchData")
		return false;

	data_root["module_slugs"] >> pd.module_slugs;
	data_root["int_cables"] >> pd.int_cables;
	data_root["mapped_ins"] >> pd.mapped_ins;

	data_root["mapped_outs"] >> pd.mapped_outs;
	data_root["static_knobs"] >> pd.static_knobs;
	data_root["mapped_knobs"] >> pd.mapped_knobs;

	return true;
}
