#include "doctest.h"
#include "dynload/autoload_plugins.hh"

TEST_CASE("Versions") {
	MetaModule::PluginManager plugins;

	// User requested to auto load these plugins:
	MetaModule::PluginAutoloadSettings settings;
	settings.slug.push_back("b1");
	settings.slug.push_back("b2");
	settings.slug.push_back("b3");
	settings.slug.push_back("z9");

	// Found these file names on disk (filename is `plugin_name`-v`version.mmplugin`)
	MetaModule::PluginFileList plugin_list;
	plugin_list.push_back({.plugin_name = "b1", .version_in_filename = "1.2"});
	plugin_list.push_back({.plugin_name = "b1", .version_in_filename = "2.0"});
	plugin_list.push_back({.plugin_name = "b1", .version_in_filename = "2.0.2"});
	plugin_list.push_back({.plugin_name = "b1", .version_in_filename = "2.0.1"});
	plugin_list.push_back({.plugin_name = "b1", .version_in_filename = "1.3"});

	plugin_list.push_back({.plugin_name = "b2", .version_in_filename = "1.0"});

	plugin_list.push_back({.plugin_name = "b3", .version_in_filename = "1.1-dev-12.1"});
	plugin_list.push_back({.plugin_name = "b3", .version_in_filename = "1.1-dev-12.3"});
	plugin_list.push_back({.plugin_name = "b3", .version_in_filename = "1.1-dev-12.2"});

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
	CHECK(plugin_list[plugins.spy_loaded[0]].version_in_filename.is_equal("2.0.2"));

	// Load next plugin: b2
	// Only one choice, should load it
	autoloader.process();
	autoloader.process();
	CHECK(plugins.spy_loaded.size() == 2);
	CHECK(plugin_list[plugins.spy_loaded[1]].version_in_filename.is_equal("1.0"));

	// Load next plugin: b3
	// Should pick latest: 1.1-dev-12.3
	autoloader.process();
	autoloader.process();
	CHECK(plugins.spy_loaded.size() == 3);
	CHECK(plugin_list[plugins.spy_loaded[2]].version_in_filename.is_equal("1.1-dev-12.3"));

	// Load next plugin: z9
	// Not found, should not add any more plugins
	autoloader.process();
	autoloader.process();
	CHECK(plugins.spy_loaded.size() == 3);

	CHECK(plugins.error == "");
}
