#pragma once
#include "plugin_manager.hh"

namespace MetaModule
{

struct AutoLoader {
	enum class State { NotStarted, Done, Error, Processing, LoadingPlugin };
	struct Status {
		State state;
		std::string message;
	};

	AutoLoader(PluginManager &plugins, PluginAutoloadSettings const &plugin_settings)
		: plugin_settings{plugin_settings}
		, plugins{plugins} {
	}

	Status process() {
		if (autoload_state == State::NotStarted) {
			return start();
		}

		if (autoload_state == State::Processing) {
			return process_loading();
		}

		if (autoload_state == State::LoadingPlugin) {
			return start_loading_plugin();
		}

		return {autoload_state, ""};
	}

private:
	Status start() {
		if (plugin_settings.slug.size()) {
			HAL_Delay(600); //allow time for ???

			pr_info("Autoload: Scanning...\n");
			plugins.start_loading_plugin_list();

			autoload_state = State::Processing;
			return {autoload_state, "Scanning disks"};
		} else {
			pr_info("Autoload: No plugins to load\n");
			autoload_state = State::Done;
			return {autoload_state, "No plugins to auto-load"};
		}
	}

	Status start_loading_plugin() {
		if (slug_idx >= plugin_settings.slug.size()) {
			autoload_state = State::Done;
			return {State::Done, "Autoloading done"};
		}

		auto &s = plugin_settings.slug[slug_idx];
		pr_info("Autoload: Looking for plugin: %s\n", s.c_str());

		autoload_state = State::Processing;

		if (load_plugin(s)) {
			return {State::Processing, "Auto-loading " + s};
		} else {
			return {State::Processing, "Can't find " + s};
		}
	}

	Status process_loading() {
		auto result = plugins.process_loading();

		if (result.state == PluginFileLoader::State::GotList) {
			found_plugins = plugins.found_plugin_list();

			slug_idx = 0;
			autoload_state = State::LoadingPlugin;
			return {autoload_state, "All disks scanned"};
		}

		if (result.state == PluginFileLoader::State::Success) {
			auto &s = plugin_settings.slug[slug_idx];
			pr_info("Autoload: Loaded plugin: %s\n", s.c_str());

			slug_idx++;
			autoload_state = State::LoadingPlugin;
			return {autoload_state, "Loaded " + s};
		}

		if (result.state == PluginFileLoader::State::Error) {
			if (result.error_message.length()) {
				pr_err("Autoload: Error: %s\n", result.error_message.c_str());
				autoload_state = State::Error;
				return {State::Error, "Error: " + result.error_message};
			} else
				return {State::Error, "Error auto-loading"};
		}

		return {autoload_state, ""};
	}

	bool load_plugin(std::string_view s) {
		const auto match = std::find_if(found_plugins->begin(), found_plugins->end(), [s](PluginFile const &f) {
			return f.plugin_name == std::string_view(s);
		});

		if (match == found_plugins->end()) {
			pr_info("Autoload: Can't find plugin: %.*s\n", (int)s.size(), s.data());
			slug_idx++;
			return false;
		}

		const auto idx = std::distance(found_plugins->begin(), match);
		plugins.load_plugin(idx);

		return true;
	}

	PluginAutoloadSettings const &plugin_settings;
	PluginManager &plugins;
	PluginFileList const *found_plugins = nullptr;
	unsigned slug_idx = 0;
	State autoload_state{State::NotStarted};
};

} // namespace MetaModule
