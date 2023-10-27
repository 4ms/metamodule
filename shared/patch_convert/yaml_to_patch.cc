#include "yaml_to_patch.hh"
#include "ryml/ryml_serial.hh"

bool yaml_raw_to_patch(char *yaml, size_t size, PatchData &pd) {
	RymlInit::init_once();

	ryml::Tree tree = ryml::parse_in_place(ryml::substr(yaml, size));

	if (tree.num_children(0) == 0)
		return false;

	ryml::ConstNodeRef root = tree.rootref();

	if (!root.has_child("PatchData"))
		return false;

	ryml::ConstNodeRef patchdata = root["PatchData"];

	if (!patchdata.has_child("patch_name"))
		return false;

	patchdata["patch_name"] >> pd.patch_name;

	if (patchdata.has_child("description"))
		patchdata["description"] >> pd.description;

	patchdata["module_slugs"] >> pd.module_slugs;
	patchdata["int_cables"] >> pd.int_cables;
	patchdata["mapped_ins"] >> pd.mapped_ins;

	patchdata["mapped_outs"] >> pd.mapped_outs;
	patchdata["static_knobs"] >> pd.static_knobs;
	patchdata["mapped_knobs"] >> pd.knob_sets;

	if (patchdata.has_child("midi_maps"))
		patchdata["midi_maps"] >> pd.midi_maps;

	if (patchdata.has_child("midi_poly_num"))
		patchdata["midi_poly_num"] >> pd.midi_poly_num;

	// Check for VCV Module State data
	if (root.has_child("vcvModuleStates"))
		root["vcvModuleStates"] >> pd.module_states;

	return true;
}

bool yaml_raw_to_patch(std::span<char> yaml, PatchData &pd) {
	return yaml_raw_to_patch(yaml.data(), yaml.size_bytes(), pd);
}

bool yaml_string_to_patch(std::string yaml, PatchData &pd) {
	return yaml_raw_to_patch(yaml.data(), yaml.size(), pd);
}
