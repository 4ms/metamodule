#include "patch/patch.hh"
#define RYML_SINGLE_HDR_DEFINE_NOW
#include "ryml_all.hpp"
#include "ryml_serial_chars.hh"

#include "printf.h"

void write(ryml::NodeRef *n, Jack const &jack) {
	*n |= ryml::MAP;
	n->append_child() << ryml::key("module_id") << jack.module_id;
	n->append_child() << ryml::key("jack_id") << jack.jack_id;
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
	if (n.num_children() != 6)
		return false;
	if (n.child(0).key() != "panel_knob_id")
		return false;
	if (n.child(1).key() != "module_id")
		return false;
	if (n.child(2).key() != "param_id")
		return false;
	if (n.child(3).key() != "curve_type")
		return false;
	if (n.child(4).key() != "min")
		return false;
	if (n.child(5).key() != "max")
		return false;

	n["panel_knob_id"] >> k->panel_knob_id;
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

namespace RymlInit
{
void init_once() {
	static bool already_init = false;
	static c4::yml::Callbacks callbacks;
	if (!already_init) {
		already_init = true;
		callbacks.m_error = [](const char *msg, size_t /*msg_len*/, c4::yml::Location loc, void * /*user_data*/) {
			if (loc.name.empty())
				printf("[ryml] %s\r\n", msg);
			else
				printf("[ryml] %s in %s %zu:%zu)\r\n", msg, loc.name.data(), loc.line, loc.col);
		};
		c4::yml::set_callbacks(callbacks);
	}
}
} // namespace RymlInit
