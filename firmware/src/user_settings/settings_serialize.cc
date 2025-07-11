#include "settings_serialize.hh"
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
	n->append_child() << ryml::key("show_graphic_screens") << s.show_graphic_screens;
	n->append_child() << ryml::key("graphic_screen_throttle") << s.graphic_screen_throttle;
}

static void write(ryml::NodeRef *n, AudioSettings const &s) {
	*n |= ryml::MAP;

	n->append_child() << ryml::key("sample_rate") << s.sample_rate;
	n->append_child() << ryml::key("block_size") << s.block_size;
	n->append_child() << ryml::key("max_overrun_retries") << s.max_overrun_retries;
}

static void write(ryml::NodeRef *n, PluginPreloadSettings const &s) {
	*n |= ryml::SEQ;

	for (auto const &s : s.slug)
		n->append_child() << s;
}

static void write(ryml::NodeRef *n, ScreensaverSettings const &s) {
	*n |= ryml::MAP;

	n->append_child() << ryml::key("index") << s.timeout_ms;
	n->append_child() << ryml::key("knobs_can_wake") << s.knobs_can_wake;
}

static void write(ryml::NodeRef *n, CatchupSettings const &s) {
	*n |= ryml::MAP;

	using enum CatchupParam::Mode;
	ryml::csubstr mode_string = s.mode == ResumeOnEqual	 ? "ResumeOnEqual" :
								s.mode == ResumeOnMotion ? "ResumeOnMotion" :
								s.mode == LinearFade	 ? "LinearFade" :
														   "ResumeOnMotion";
	n->append_child() << ryml::key("mode") << mode_string;
	n->append_child() << ryml::key("allow_jump_outofrange") << s.allow_jump_outofrange;
}

static void write(ryml::NodeRef *n, FilesystemSettings const &s) {
	*n |= ryml::MAP;

	n->append_child() << ryml::key("auto_reload_patch_file") << s.auto_reload_patch_file;
	n->append_child() << ryml::key("max_open_patches") << s.max_open_patches;
}

[[maybe_unused]] static void write(ryml::NodeRef *n, MidiSettings const &s) {
	*n |= ryml::MAP;

	n->append_child() << ryml::key("midi_feedback") << std::to_underlying(s.midi_feedback);
}

namespace Settings
{

uint32_t serialize(UserSettings const &settings, std::span<char> buffer) {
	RymlInit::init_once();

	ryml::Tree tree;
	auto root = tree.rootref();
	root |= ryml::MAP;

	auto data = root["Settings"];
	data |= ryml::MAP;

	data["patch_view"] << settings.patch_view;
	data["module_view"] << settings.module_view;
	data["audio"] << settings.audio;
	data["plugin_autoload"] << settings.plugin_preload;
	data["last_patch_opened"] << settings.last_patch_opened;
	data["last_patch_vol"] << static_cast<unsigned>(settings.last_patch_vol);
	data["screensaver"] << settings.screensaver;
	data["catchup"] << settings.catchup;
	data["filesystem"] << settings.filesystem;
	data["midi"] << settings.midi;

	auto res = ryml::emit_yaml(tree, c4::substr(buffer.data(), buffer.size()));
	return res.size();
}

//
} // namespace Settings
} // namespace MetaModule
