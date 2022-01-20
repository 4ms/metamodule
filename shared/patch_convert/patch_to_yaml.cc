#include "patch_to_yaml.hh"
#include "ryml/ryml_all.hpp"
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

	//data.append_child() << ryml::key("patch_name") << pd.patch_name.c_str();
	data["patch_name"] << pd.patch_name;

	ryml::NodeRef slugs = data["module_slugs"];
	slugs |= ryml::MAP;
	for (auto [i, x] : enumerate(pd.module_slugs)) {
		auto idx_s = std::to_string(i);
		ryml::csubstr idx(idx_s.c_str(), idx_s.length());
		ryml::csubstr slug(x.c_str(), x.length());
		slugs.append_child() << ryml::key(idx) << slug;
	}

	ryml::NodeRef int_cables = data["int_cables"];
	int_cables |= ryml::SEQ;
	for (auto &x : pd.int_cables) {
		ryml::NodeRef el = int_cables.append_child({ryml::MAP});
		el["out"] << x.out;
		el["ins"] |= ryml::SEQ;
		for (auto [in_i, in] : enumerate(x.ins)) {
			if (in.jack_id < 0 || in.module_id < 0)
				break;
			el["ins"][in_i] << in;
		}
	}

	ryml::NodeRef mapped_ins = data["mapped_ins"];
	mapped_ins |= ryml::SEQ;
	for (auto &x : pd.mapped_ins) {
		ryml::NodeRef el = mapped_ins.append_child({ryml::MAP});
		el["panel_jack_id"] << x.panel_jack_id;
		el["ins"] |= ryml::SEQ;
		for (auto [in_i, in] : enumerate(x.ins)) {
			if (in.jack_id < 0 || in.module_id < 0)
				break;
			el["ins"][in_i] << in;
		}
	}

	ryml::NodeRef mapped_outs = data["mapped_outs"];
	mapped_outs |= ryml::SEQ;
	for (auto &x : pd.mapped_outs) {
		ryml::NodeRef el = mapped_outs.append_child({ryml::MAP});
		el["panel_jack_id"] << x.panel_jack_id;
		el["out"] << x.out;
	}

	ryml::NodeRef static_knobs = data["static_knobs"];
	static_knobs |= ryml::SEQ;
	for (auto &x : pd.static_knobs) {
		ryml::NodeRef el = static_knobs.append_child({ryml::MAP});
		el["module_id"] << x.module_id;
		el["param_id"] << x.param_id;
		el["value"] << x.value;
	}

	ryml::NodeRef mapped_knobs = data["mapped_knobs"];
	mapped_knobs |= ryml::SEQ;
	for (auto &x : pd.mapped_knobs) {
		ryml::NodeRef el = mapped_knobs.append_child({ryml::MAP});
		el["panel_knob_id"] << x.panel_knob_id;
		el["module_id"] << x.module_id;
		el["param_id"] << x.param_id;
		el["curve_type"] << x.curve_type;
		el["min"] << x.min;
		el["max"] << x.max;
	}

	return ryml::emitrs<std::string>(tree);
}
