#include "ryml_std.hpp"
//
#include "patch/patch.hh"
#include "printf.h"
#include "ryml.hpp"
#include "ryml_serial_chars.hh"

void write(ryml::NodeRef *n, Jack const &jack) {
	*n |= ryml::MAP;
	n->append_child() << ryml::key("module_id") << jack.module_id;
	n->append_child() << ryml::key("jack_id") << jack.jack_id;
}

void write(ryml::NodeRef *n, MappedKnob const &mapped_knob) {
	*n |= ryml::MAP;
	n->append_child() << ryml::key("panel_knob_id") << mapped_knob.panel_knob_id;
	n->append_child() << ryml::key("module_id") << mapped_knob.module_id;
	n->append_child() << ryml::key("param_id") << mapped_knob.param_id;
	n->append_child() << ryml::key("curve_type") << mapped_knob.curve_type;
	n->append_child() << ryml::key("min") << mapped_knob.min;
	n->append_child() << ryml::key("max") << mapped_knob.max;
	if (mapped_knob.alias_name.length())
		n->append_child() << ryml::key("alias_name") << mapped_knob.alias_name;
}

void write(ryml::NodeRef *n, MappedKnobSet const &knob_set) {
	*n |= ryml::MAP;
	n->append_child() << ryml::key("name") << knob_set.name;
	n->append_child() << ryml::key("set") << knob_set.set;
}

bool read(ryml::ConstNodeRef const &n, Jack *jack) {
	if (n.num_children() < 2)
		return false;
	if (!n.is_map())
		return false;
	if (!n.has_child("module_id"))
		return false;
	if (!n.has_child("jack_id"))
		return false;

	n["module_id"] >> jack->module_id;
	n["jack_id"] >> jack->jack_id;
	return true;
}

bool read(ryml::ConstNodeRef const &n, InternalCable *cable) {
	if (n.num_children() < 2)
		return false;
	if (!n.is_map())
		return false;
	if (!n.has_child("out"))
		return false;
	if (!n.has_child("ins"))
		return false;

	n["out"] >> cable->out;

	auto num_ins = n["ins"].num_children();
	if (num_ins < 1)
		return false;
	cable->ins.reserve(num_ins);
	n["ins"] >> cable->ins;

	return true;
}

bool read(ryml::ConstNodeRef const &n, MappedInputJack *j) {
	if (n.num_children() < 2)
		return false;
	if (!n.is_map())
		return false;
	if (!n.has_child("panel_jack_id"))
		return false;
	if (!n.has_child("ins"))
		return false;

	n["panel_jack_id"] >> j->panel_jack_id;

	auto num_ins = n["ins"].num_children();
	if (num_ins < 1)
		return false;
	j->ins.reserve(num_ins);
	n["ins"] >> j->ins;

	if (n.has_child("alias_name"))
		n["alias_name"] >> j->alias_name;

	return true;
}

bool read(ryml::ConstNodeRef const &n, MappedOutputJack *j) {
	if (n.num_children() < 2)
		return false;
	if (!n.is_map())
		return false;
	if (!n.has_child("panel_jack_id"))
		return false;
	if (!n.has_child("out"))
		return false;

	n["panel_jack_id"] >> j->panel_jack_id;
	n["out"] >> j->out;

	if (n.has_child("alias_name"))
		n["alias_name"] >> j->alias_name;

	return true;
}

bool read(ryml::ConstNodeRef const &n, MappedKnob *k) {
	if (n.num_children() < 6)
		return false;
	if (!n.is_map())
		return false;
	if (!n.has_child("panel_knob_id"))
		return false;
	if (!n.has_child("module_id"))
		return false;
	if (!n.has_child("param_id"))
		return false;
	if (!n.has_child("curve_type"))
		return false;
	if (!n.has_child("min"))
		return false;
	if (!n.has_child("max"))
		return false;

	n["panel_knob_id"] >> k->panel_knob_id;
	n["module_id"] >> k->module_id;
	n["param_id"] >> k->param_id;
	n["curve_type"] >> k->curve_type;
	n["min"] >> k->min;
	n["max"] >> k->max;

	if (n.has_child("alias_name"))
		n["alias_name"] >> k->alias_name;

	return true;
}

bool read(ryml::ConstNodeRef const &n, MappedKnobSet *ks) {
	if (n.num_children() < 1)
		return false;
	if (!n.is_map())
		return false;
	if (!n.has_child("set"))
		return false;

	if (n.has_child("name"))
		n["name"] >> ks->name;

	n["set"] >> ks->set;

	return true;
}

bool read(ryml::ConstNodeRef const &n, StaticParam *k) {
	if (n.num_children() < 3)
		return false;
	if (!n.is_map())
		return false;
	if (!n.has_child("module_id"))
		return false;
	if (!n.has_child("param_id"))
		return false;
	if (!n.has_child("value"))
		return false;

	n["module_id"] >> k->module_id;
	n["param_id"] >> k->param_id;
	n["value"] >> k->value;

	return true;
}

namespace RymlInit
{
void init_once() {
	static bool already_init = false;
	static c4::yml::Callbacks callbacks;
	if (!already_init) {
		already_init = true;
		callbacks.m_error = [](const char *msg, size_t /*msg_len*/, c4::yml::Location loc, void * /*user_data*/) {
			if (loc.name.empty())
				printf("[ryml] %s\n", msg);
			else
				printf("[ryml] %s in %s %zu:%zu)\n", msg, loc.name.data(), loc.line, loc.col);
		};
		c4::yml::set_callbacks(callbacks);
	}
}
} // namespace RymlInit
