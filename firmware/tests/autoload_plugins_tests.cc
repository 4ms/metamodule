#include "doctest.h"
#include "dynload/autoload_plugins.hh"

TEST_CASE("Versions") {
	MetaModule::PluginManager plugins;

	// User requested to auto load these plugins:
	MetaModule::PluginAutoloadSettings settings;
	settings.slug.push_back("b1");
	settings.slug.push_back("b2");
	settings.slug.push_back("z9");

	// Found these file names on disk (filename is `plugin_name`-v`version.mmplugin`)
	MetaModule::PluginFileList plugin_list;
	plugin_list.push_back({.plugin_name = "b1", .version = "1.2"});
	plugin_list.push_back({.plugin_name = "b1", .version = "2.0"});
	plugin_list.push_back({.plugin_name = "b1", .version = "2.0.2"});
	plugin_list.push_back({.plugin_name = "b1", .version = "2.0.1"});
	plugin_list.push_back({.plugin_name = "b1", .version = "1.3"});
	plugin_list.push_back({.plugin_name = "b2", .version = ""});

	plugins.fake_plugin_list = &plugin_list;

	MetaModule::AutoLoader autoloader{plugins, settings};

	// Load the plugin list (first process())
	CHECK(plugins.spy_loaded.size() == 0);
	autoloader.process();

	// Load first plugin: b1
	// lots of choices for versions: should pick latest it can host (2.0.2)
	autoloader.process();
	autoloader.process();
	CHECK(plugins.spy_loaded.size() == 1);
	CHECK(plugin_list[plugins.spy_loaded[0]].version.is_equal("2.0.2"));

	// Load next plugin: b2
	// Only one choice, should load it
	autoloader.process();
	autoloader.process();
	CHECK(plugins.spy_loaded.size() == 2);

	CHECK(plugins.error == "");
}
