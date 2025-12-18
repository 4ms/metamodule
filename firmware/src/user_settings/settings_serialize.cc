#include "settings_serialize.hh"
#include "ryml.hpp"
#include "ryml_init.hh"
#include "ryml_std.hpp"
#include <span>

namespace MetaModule
{

[[maybe_unused]] static void write(ryml::NodeRef *n, AudioSettings const &s) {
	*n |= ryml::MAP;

	n->append_child() << ryml::key("sample_rate") << s.sample_rate;
	n->append_child() << ryml::key("block_size") << s.block_size;
	n->append_child() << ryml::key("max_overrun_retries") << s.max_overrun_retries;
}

[[maybe_unused]] static void write(ryml::NodeRef *n, PluginPreloadSettings const &s) {
	*n |= ryml::SEQ;

	for (auto const &s : s.slugs)
		n->append_child() << s;
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

	data["audio"] << settings.audio;
	data["plugin_autoload"] << settings.plugin_preload;
	data["last_patch_opened"] << settings.initial_patch_name;
	data["last_patch_vol"] << static_cast<unsigned>(settings.initial_patch_vol);
	data["load_initial_patch"] << settings.load_initial_patch;

	auto res = ryml::emit_yaml(tree, c4::substr(buffer.data(), buffer.size()));
	return res.size();
}

//
} // namespace Settings
} // namespace MetaModule
