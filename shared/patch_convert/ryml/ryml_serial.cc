
#include "ryml_std.hpp"
//
#include "patch/patch.hh"
#include "ryml.hpp"
#include "ryml_serial_chars.hh"
#include <cstdio>

#include "CoreModules/module_type_slug.hh"
#include "cpputil/util/countzip.hh"

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

void write(ryml::NodeRef *n, InternalCable const &cable) {
	*n |= ryml::MAP;
	n->append_child() << ryml::key("out") << cable.out;
	n->append_child() << ryml::key("ins") << cable.ins;
	if (cable.color.has_value()) {
		n->append_child() << ryml::key("color") << cable.color.value();
	}
}

void write(ryml::NodeRef *n, MappedInputJack const &j) {
	*n |= ryml::MAP;
	n->append_child() << ryml::key("panel_jack_id") << j.panel_jack_id;
	n->append_child() << ryml::key("ins") << j.ins;
	if (j.alias_name.length())
		n->append_child() << ryml::key("alias_name") << j.alias_name;
}

void write(ryml::NodeRef *n, MappedOutputJack const &j) {
	*n |= ryml::MAP;
	n->append_child() << ryml::key("panel_jack_id") << j.panel_jack_id;
	n->append_child() << ryml::key("out") << j.out;
	if (j.alias_name.length())
		n->append_child() << ryml::key("alias_name") << j.alias_name;
}

void write(ryml::NodeRef *n, StaticParam const &k) {
	*n |= ryml::MAP;
	n->append_child() << ryml::key("module_id") << k.module_id;
	n->append_child() << ryml::key("param_id") << k.param_id;
	n->append_child() << ryml::key("value") << k.value;
}

void write(ryml::NodeRef *n, std::vector<ModuleTypeSlug> const &slugs) {
	*n |= ryml::MAP;
	for (auto [i, x] : enumerate(slugs)) {
		auto idx_s = std::to_string(i);
		ryml::csubstr idx(idx_s.c_str(), idx_s.length());
		ryml::csubstr slug(x.c_str(), x.length());
		n->append_child() << ryml::key(idx) << slug;
	}
}

void write(ryml::NodeRef *n, ModuleInitState const &state) {
	*n |= ryml::MAP;
	n->append_child() << ryml::key("module_id") << state.module_id;

	auto data_node = n->append_child();
	data_node |= ryml::_WIP_VAL_LITERAL;
	data_node << ryml::key("data") << state.state_data;
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

	if (n.has_child("color")) {
		uint16_t color;
		n["color"] >> color;
		cable->color = color;
	} else {
		cable->color = std::nullopt;
	}

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

	if (n.has_child("alias_name")) {
		if (n["alias_name"].val().size())
			n["alias_name"] >> j->alias_name;
		else
			j->alias_name = "";
	}

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

	if (n.has_child("alias_name")) {
		if (n["alias_name"].val().size())
			n["alias_name"] >> j->alias_name;
		else
			j->alias_name = "";
	}

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

	if (n.has_child("alias_name")) {
		if (n["alias_name"].val().size())
			n["alias_name"] >> k->alias_name;
		else
			k->alias_name = "";
	}

	return true;
}

bool read(ryml::ConstNodeRef const &n, MappedKnobSet *ks) {
	// Allow empty knob set
	if (!n.is_map())
		return true;

	if (n.has_child("name")) {
		if (n["name"].val().size())
			n["name"] >> ks->name;
		else
			ks->name = "";
	}

	if (n.has_child("set"))
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

bool read(ryml::ConstNodeRef const &n, ModuleInitState *m) {
	if (n.num_children() < 2)
		return false;

	if (!n.is_map())
		return false;
	if (!n.has_child("module_id"))
		return false;
	if (!n.has_child("data"))
		return false;

	n["module_id"] >> m->module_id;

	// copy the data field as a string
	// Modules will decide how to deserialize
	ryml::ConstNodeRef data_node = n["data"];
	m->state_data = std::string{data_node.val().data(), data_node.val().size()};

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
