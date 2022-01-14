#define RYML_SINGLE_HDR_DEFINE_NOW
#include "ryml_all.hpp"

#include "patch/patch.hh"

void write(ryml::NodeRef *n, Jack const &jack)
{
	*n |= ryml::MAP;
	n->append_child() << ryml::key("module_id") << jack.module_id;
	n->append_child() << ryml::key("jack_id") << jack.jack_id;
}

void write(ryml::NodeRef *n, PatchHeader const &ph)
{
	*n |= ryml::MAP;
	n->append_child() << ryml::key("header_version") << std::to_string(ph.header_version);
	n->append_child() << ryml::key("patch_name") << ph.patch_name.c_str();
	n->append_child() << ryml::key("num_modules") << std::to_string(ph.num_modules);
	n->append_child() << ryml::key("num_int_cables") << std::to_string(ph.num_int_cables);
	n->append_child() << ryml::key("num_mapped_ins") << std::to_string(ph.num_mapped_ins);
	n->append_child() << ryml::key("num_mapped_outs") << std::to_string(ph.num_mapped_outs);
	n->append_child() << ryml::key("num_mapped_knobs") << std::to_string(ph.num_mapped_knobs);
}

// bool read(ryml::NodeRef const &n, PatchHeader *ph)
// {
// 	n["header_version"] >> ph->header_version;
// 	n["patch_name"] >> ph->patch_name;
// 	n["num_modules"] >> ph->num_modules;
// 	n["num_int_cables"] >> ph->num_int_cables;
// 	n["num_mapped_ins"] >> ph->num_mapped_ins;
// 	n["num_mapped_outs"] >> ph->num_mapped_outs;
// 	n["num_mapped_knobs"] >> ph->num_mapped_knobs;
// 	return true;
// }
