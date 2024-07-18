#include "gui/pages/view_settings.hh"
#include "ryml.hpp"
#include "ryml_init.hh"
#include "ryml_std.hpp"
#include <span>

namespace MetaModule
{

static void write(ryml::NodeRef *n, MapRingStyle const &style) {
	*n |= ryml::MAP;

	using enum MapRingStyle::Mode;
	ryml::csubstr mode_string = style.mode == HideAlways		 ? "HideAlways" :
								style.mode == CurModule			 ? "CurModule" :
								style.mode == CurModuleIfPlaying ? "CurModuleIfPlaying" :
								style.mode == ShowAll			 ? "ShowAll" :
								style.mode == ShowAllIfPlaying	 ? "ShowAllIfPlaying" :
																   "ShowAll";
	n->append_child() << ryml::key("mode") << mode_string;
	n->append_child() << ryml::key("opa") << style.opa;
}

static void write(ryml::NodeRef *n, ModuleDisplaySettings const &s) {
	*n |= ryml::MAP;

	n->append_child() << ryml::key("map_ring_flash_active") << s.map_ring_flash_active;
	n->append_child() << ryml::key("scroll_to_active_param") << s.scroll_to_active_param;
	n->append_child() << ryml::key("view_height_px") << s.view_height_px;
	n->append_child() << ryml::key("param_style") << s.param_style;
	n->append_child() << ryml::key("paneljack_style") << s.paneljack_style;
	n->append_child() << ryml::key("cable_style") << s.cable_style;
}

static void write(ryml::NodeRef *n, AudioSettings const &s) {
	*n |= ryml::MAP;

	n->append_child() << ryml::key("sample_rate") << s.sample_rate;
	n->append_child() << ryml::key("block_size") << s.block_size;
}

namespace Settings
{

uint32_t serialize(ViewSettings const &settings, std::span<char> buffer) {
	RymlInit::init_once();

	ryml::Tree tree;
	auto root = tree.rootref();
	root |= ryml::MAP;

	auto data = root["Settings"];
	data |= ryml::MAP;

	data["patch_view"] << settings.patch_view;
	data["module_view"] << settings.module_view;
	data["audio"] << settings.audio;

	auto res = ryml::emit_yaml(tree, c4::substr(buffer.data(), buffer.size()));
	return res.size();
}

//
} // namespace Settings
} // namespace MetaModule
