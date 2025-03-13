#include "settings_parse.hh"
#include "catchup_settings.hh"
#include "ryml.hpp"
#include "ryml_init.hh"
#include "ryml_std.hpp"
#include "util/countzip.hh"
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

static bool read(ryml::ConstNodeRef const &node, AudioSettings *audio) {
	if (!node.is_map())
		return false;

	read_or_default(node, "sample_rate", audio, &AudioSettings::sample_rate);
	read_or_default(node, "block_size", audio, &AudioSettings::block_size);
	read_or_default(node, "max_overrun_retries", audio, &AudioSettings::max_overrun_retries);
	audio->make_valid();

	return true;
}

static bool read(ryml::ConstNodeRef const &node, PluginAutoloadSettings *autoload) {
	if (!node.is_seq())
		return false;

	autoload->slug.resize(node.num_children());
	auto pos = 0u;
	for (auto const ch : node.children())
		ch >> autoload->slug[pos++];

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
	read_or_default(node, "show_graphic_screens", s, &ModuleDisplaySettings::show_graphic_screens);

	return true;
}

static bool read(ryml::ConstNodeRef const &node, ScreensaverSettings *s) {
	if (!node.is_map())
		return false;

	read_or_default(node, "index", s, &ScreensaverSettings::timeout_ms);
	read_or_default(node, "knobs_can_wake", s, &ScreensaverSettings::knobs_can_wake);

	return true;
}

static bool read(ryml::ConstNodeRef const &node, CatchupSettings *settings) {
	if (!node.is_map())
		return false;

	using enum CatchupParam::Mode;

	if (node.has_child("mode")) {
		settings->mode = node["mode"].val() == "ResumeOnEqual"	? ResumeOnEqual :
						 node["mode"].val() == "ResumeOnMotion" ? ResumeOnMotion :
						 node["mode"].val() == "LinearFade"		? LinearFade :
																  ResumeOnMotion;
	} else {
		settings->mode = CatchupParam{}.mode;
	}

	read_or_default(node, "exclude_buttons", settings, &CatchupSettings::button_exclude);
	settings->make_valid();

	return true;
}

static bool read(ryml::ConstNodeRef const &node, FilesystemSettings *settings) {
	if (!node.is_map())
		return false;

	using enum CatchupParam::Mode;

	read_or_default(node, "auto_reload_patch_file", settings, &FilesystemSettings::auto_reload_patch_file);
	read_or_default(node, "max_open_patches", settings, &FilesystemSettings::max_open_patches);
	settings->make_valid();

	return true;
}

namespace Settings
{

bool parse(std::span<char> yaml, UserSettings *settings) {
	RymlInit::init_once();

	ryml::Tree tree = ryml::parse_in_place(ryml::substr(yaml.data(), yaml.size()));

	if (tree.num_children(0) == 0)
		return false;

	ryml::ConstNodeRef root = tree.rootref();

	if (!root.has_child("Settings"))
		return false;

	ryml::ConstNodeRef node = root["Settings"];

	read_or_default(node, "patch_view", settings, &UserSettings::patch_view);
	read_or_default(node, "module_view", settings, &UserSettings::module_view);
	read_or_default(node, "audio", settings, &UserSettings::audio);
	read_or_default(node, "plugin_autoload", settings, &UserSettings::plugin_autoload);
	read_or_default(node, "last_patch_opened", settings, &UserSettings::last_patch_opened);
	read_or_default(node, "screensaver", settings, &UserSettings::screensaver);
	read_or_default(node, "catchup", settings, &UserSettings::catchup);
	read_or_default(node, "filesystem", settings, &UserSettings::filesystem);

	// TODO: cleaner way to parse an enum and reject out of range?
	if (node.is_map() && node.has_child("last_patch_vol")) {
		unsigned t = 0;
		node["last_patch_vol"] >> t;
		if (t < static_cast<unsigned>(Volume::MaxVolumes))
			settings->last_patch_vol = static_cast<Volume>(t);
	} else {
		settings->last_patch_vol = UserSettings{}.last_patch_vol;
	}

	return true;
}

} // namespace Settings
} // namespace MetaModule
