#include "patch/patch.hh"
#define RYML_SINGLE_HDR_DEFINE_NOW
#include "ryml_all.hpp"
#include "ryml_serial_chars.hh"

void write(ryml::NodeRef *n, Jack const &jack) {
	*n |= ryml::MAP;
	n->append_child() << ryml::key("module_id") << jack.module_id;
	n->append_child() << ryml::key("jack_id") << jack.jack_id;
}

void write(ryml::NodeRef *n, PatchHeader const &ph) {
	*n |= ryml::MAP;
	n->append_child() << ryml::key("header_version") << std::to_string(ph.header_version);
	n->append_child() << ryml::key("patch_name") << ph.patch_name.c_str();
	n->append_child() << ryml::key("num_modules") << std::to_string(ph.num_modules);
	n->append_child() << ryml::key("num_int_cables") << std::to_string(ph.num_int_cables);
	n->append_child() << ryml::key("num_mapped_ins") << std::to_string(ph.num_mapped_ins);
	n->append_child() << ryml::key("num_mapped_outs") << std::to_string(ph.num_mapped_outs);
	n->append_child() << ryml::key("num_static_knobs") << std::to_string(ph.num_static_knobs);
	n->append_child() << ryml::key("num_mapped_knobs") << std::to_string(ph.num_mapped_knobs);
}

bool read(ryml::NodeRef const &n, Jack *jack) {
	if (n.num_children() != 2)
		return false;
	if (n.child(0).key() != "module_id")
		return false;
	if (n.child(1).key() != "jack_id")
		return false;

	n["module_id"] >> jack->module_id;
	n["jack_id"] >> jack->jack_id;
	return true;
}

bool read(ryml::NodeRef const &n, PatchHeader *ph) {
	if (n.num_children() != 8)
		return false;
	if (n.child(0).key() != "header_version")
		return false;
	if (n.child(1).key() != "patch_name")
		return false;
	if (n.child(2).key() != "num_modules")
		return false;
	//TODO: rest of fields...

	n["header_version"] >> ph->header_version;
	n["patch_name"] >> ph->patch_name;
	n["num_modules"] >> ph->num_modules;
	n["num_int_cables"] >> ph->num_int_cables;
	n["num_mapped_ins"] >> ph->num_mapped_ins;
	n["num_mapped_outs"] >> ph->num_mapped_outs;
	n["num_static_knobs"] >> ph->num_static_knobs;
	n["num_mapped_knobs"] >> ph->num_mapped_knobs;
	return true;
}

bool read(ryml::NodeRef const &n, InternalCable *cable) {
	if (n.num_children() != 2)
		return false;
	if (n.child(0).key() != "out")
		return false;
	if (n.child(1).key() != "ins")
		return false;

	n["out"] >> cable->out;

	unsigned i = 0;
	for (auto &in : n["ins"].children())
		in >> cable->ins[i++];

	// Terminate
	if (i < (MAX_CONNECTIONS_PER_NODE - 1)) //1,2
		cable->ins[i] = Jack{-1, -1};

	return true;
}

bool read(ryml::NodeRef const &n, MappedInputJack *j) {
	if (n.num_children() != 2)
		return false;
	if (n.child(0).key() != "panel_jack_id")
		return false;
	if (n.child(1).key() != "ins")
		return false;

	n["panel_jack_id"] >> j->panel_jack_id;

	unsigned i = 0;
	for (auto &in : n["ins"].children())
		in >> j->ins[i++];

	// Terminate
	if (i < (MAX_CONNECTIONS_PER_NODE - 1))
		j->ins[i] = Jack{-1, -1};

	return true;
}

bool read(ryml::NodeRef const &n, MappedOutputJack *j) {
	if (n.num_children() != 2)
		return false;
	if (n.child(0).key() != "panel_jack_id")
		return false;
	if (n.child(1).key() != "out")
		return false;

	n["panel_jack_id"] >> j->panel_jack_id;
	n["out"] >> j->out;

	return true;
}

bool read(ryml::NodeRef const &n, MappedKnob *k) {
	if (n.num_children() != 5)
		return false;
	if (n.child(0).key() != "module_id")
		return false;
	if (n.child(1).key() != "param_id")
		return false;
	if (n.child(2).key() != "curve_type")
		return false;
	if (n.child(3).key() != "min")
		return false;
	if (n.child(4).key() != "max")
		return false;

	n["module_id"] >> k->module_id;
	n["param_id"] >> k->param_id;
	n["curve_type"] >> k->curve_type;
	n["min"] >> k->min;
	n["max"] >> k->max;

	return true;
}

bool read(ryml::NodeRef const &n, StaticParam *k) {
	if (n.num_children() != 3)
		return false;
	if (n.child(0).key() != "module_id")
		return false;
	if (n.child(1).key() != "param_id")
		return false;
	if (n.child(2).key() != "value")
		return false;

	n["module_id"] >> k->module_id;
	n["param_id"] >> k->param_id;
	n["value"] >> k->value;

	return true;
}
