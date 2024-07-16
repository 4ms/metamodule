#include "gui/pages/view_settings.hh"
#include "ryml.hpp"
#include "ryml_init.hh"
#include <span>

namespace MetaModule
{

template<typename T>
void read_or_default(ryml::ConstNodeRef const &n, c4::csubstr name, T *s, auto member_ptr) {
	if (n.is_map() && n.has_child(name)) {
		n[name] >> s->*member_ptr;
	} else {
		s->*member_ptr = T{}.*member_ptr;
	}
}

static bool read(ryml::ConstNodeRef const &n, MapRingStyle *s) {
	if (!n.is_map())
		return false;

	using enum MapRingStyle::Mode;

	if (n.has_child("mode")) {
		s->mode = n["mode"].val() == "HideAlways"		  ? HideAlways :
				  n["mode"].val() == "CurModule"		  ? CurModule :
				  n["mode"].val() == "CurModuleIfPlaying" ? CurModuleIfPlaying :
				  n["mode"].val() == "ShowAll"			  ? ShowAll :
				  n["mode"].val() == "ShowAllIfPlaying"	  ? ShowAllIfPlaying :
															ShowAll;
	} else {
		s->mode = MapRingStyle{}.mode;
	}

	// Use default value if opa is defined, but not a number
	if (n.has_child("opa") && n["opa"].val().is_number()) {
		n["opa"] >> s->opa;
	} else {
		s->opa = MapRingStyle{}.opa;
	}

	return true;
}

static bool read(ryml::ConstNodeRef const &node, ViewSettings::BlockSize *bs) {
	*bs = node.val() == "32"  ? ViewSettings::BlockSize::BS_32 :
		  node.val() == "64"  ? ViewSettings::BlockSize::BS_64 :
		  node.val() == "128" ? ViewSettings::BlockSize::BS_128 :
		  node.val() == "256" ? ViewSettings::BlockSize::BS_256 :
		  node.val() == "512" ? ViewSettings::BlockSize::BS_512 :
								ViewSettings{}.block_size;
	return true;
}

static bool read(ryml::ConstNodeRef const &node, ViewSettings::SampleRate *sr) {
	*sr = node.val() == "24000" ? ViewSettings::SampleRate::SR_24K :
		  node.val() == "48000" ? ViewSettings::SampleRate::SR_48K :
		  node.val() == "96000" ? ViewSettings::SampleRate::SR_96K :
								  ViewSettings{}.sample_rate;
	return true;
}

static bool read(ryml::ConstNodeRef const &node, ModuleDisplaySettings *s) {
	if (!node.is_map())
		return false;

	read_or_default(node, "map_ring_flash_active", s, &ModuleDisplaySettings::map_ring_flash_active);
	read_or_default(node, "scroll_to_active_param", s, &ModuleDisplaySettings::scroll_to_active_param);
	read_or_default(node, "view_height_px", s, &ModuleDisplaySettings::view_height_px);
	read_or_default(node, "param_style", s, &ModuleDisplaySettings::param_style);
	read_or_default(node, "paneljack_style", s, &ModuleDisplaySettings::paneljack_style);
	read_or_default(node, "cable_style", s, &ModuleDisplaySettings::cable_style);

	return true;
}

namespace Settings
{

bool parse(std::span<char> yaml, ViewSettings *settings) {
	RymlInit::init_once();

	ryml::Tree tree = ryml::parse_in_place(ryml::substr(yaml.data(), yaml.size()));

	if (tree.num_children(0) == 0)
		return false;

	ryml::ConstNodeRef root = tree.rootref();

	if (!root.has_child("Settings"))
		return false;

	ryml::ConstNodeRef node = root["Settings"];

	read_or_default(node, "patch_view", settings, &ViewSettings::patch_view);
	read_or_default(node, "module_view", settings, &ViewSettings::module_view);
	read_or_default(node, "sample_rate", settings, &ViewSettings::sample_rate);
	read_or_default(node, "block_size", settings, &ViewSettings::block_size);

	return true;
}

} // namespace Settings
} // namespace MetaModule
