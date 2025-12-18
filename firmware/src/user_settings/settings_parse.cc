#include "settings_parse.hh"
#include "ryml.hpp"
#include "ryml_init.hh"
#include "ryml_std.hpp"
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

[[maybe_unused]] static bool read(ryml::ConstNodeRef const &node, AudioSettings *audio) {
	if (!node.is_map())
		return false;

	read_or_default(node, "sample_rate", audio, &AudioSettings::sample_rate);
	read_or_default(node, "block_size", audio, &AudioSettings::block_size);
	read_or_default(node, "max_overrun_retries", audio, &AudioSettings::max_overrun_retries);
	audio->make_valid();

	return true;
}

[[maybe_unused]] static bool read(ryml::ConstNodeRef const &node, PluginPreloadSettings *autoload) {
	if (!node.is_seq())
		return false;

	autoload->slugs.resize(node.num_children());
	auto pos = 0u;
	for (auto const ch : node.children())
		ch >> autoload->slugs[pos++];

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

	read_or_default(node, "audio", settings, &UserSettings::audio);
	read_or_default(node, "plugin_autoload", settings, &UserSettings::plugin_preload);
	read_or_default(node, "last_patch_opened", settings, &UserSettings::initial_patch_name);
	// TODO: cleaner way to parse an enum and reject out of range?
	if (node.is_map() && node.has_child("last_patch_vol")) {
		unsigned t = 0;
		node["last_patch_vol"] >> t;
		if (t < static_cast<unsigned>(Volume::MaxVolumes))
			settings->initial_patch_vol = static_cast<Volume>(t);
	} else {
		settings->initial_patch_vol = UserSettings{}.initial_patch_vol;
	}

	// load_initial_patch: Be backwards compatible when upgrading from v2.0.x to v2.1
	// If the settings file doesn't have this field, then make it true if last_patch_opened was set
	if (node.is_map() && node.has_child("load_initial_patch")) {
		node["load_initial_patch"] >> settings->load_initial_patch;
	} else {
		settings->load_initial_patch = (settings->initial_patch_name.length() > 0);
	}

	return true;
}

} // namespace Settings
} // namespace MetaModule
