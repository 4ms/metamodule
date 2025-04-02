#pragma once
#include "console/pr_dbg.hh"
#include "dynload/plugin_file_list.hh"
#include "dynload/plugin_manager.hh"
#include "user_settings/plugin_autoload_settings.hh"
#include "util/version_tools.hh"

namespace MetaModule
{

struct AutoLoader {
	enum class State { NotStarted, Done, Warning, Error, Processing, LoadingPlugin };
	struct Status {
		State state;
		std::string message;
	};

	AutoLoader(PluginManager &plugins, PluginAutoloadSettings &plugin_settings)
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
			pr_trace("Autoload: Scanning...\n");

			plugins.start_loading_plugin_list();

			attempted_to_load.clear();
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
		// trim leading and trailing whitespace on plugin name:
		s = s.substr(0, s.find_last_not_of(" \t\n") + 1);
		s = s.substr(s.find_first_not_of(" \t\n"));
		pr_trace("Autoload: Looking for plugin: '%s'\n", s.c_str());

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

		if (result.state == PluginFileLoader::State::Idle || result.state == PluginFileLoader::State::Success) {
			auto &s = plugin_settings.slug[slug_idx];
			pr_trace("Autoload: Done with plugin: %s\n", s.c_str());

			slug_idx++;
			autoload_state = State::LoadingPlugin;
			return {autoload_state, "Loaded " + s};
		}

		if (result.state == PluginFileLoader::State::InvalidPlugin) {

			if (left_to_try > 1) {
				pr_trace("Autoload: failed with '%s', %u left to try\n", result.error_message.c_str(), left_to_try);
				autoload_state = State::LoadingPlugin;

			} else {
				pr_warn("Autoload: Warning: %s\n", result.error_message.c_str());
				slug_idx++;
				if (slug_idx >= plugin_settings.slug.size()) {
					autoload_state = State::Done;
				} else {
					autoload_state = State::LoadingPlugin;
				}
				return {State::Warning, "Error: " + result.error_message};
			}
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
		Version latest_version{};
		std::optional<unsigned> match_idx{std::nullopt};

		left_to_try = 0;

		for (unsigned idx = 0; auto const &found_plugin : *found_plugins) {
			if (found_plugin.plugin_name == s) {

				// Skip this file if we've already attempted to load it
				if (std::ranges::find(attempted_to_load, idx) == attempted_to_load.end()) {

					left_to_try++;

					auto found_version = VersionUtil::Version(found_plugin.version_in_filename);

					if (!latest_version.is_later(found_version)) {
						// Note that if versions are equal, we make this one the latest

						latest_version.major = found_version.major;
						latest_version.minor = found_version.minor;
						latest_version.revision = found_version.revision;
						match_idx = idx;
					}
				}
			}
			idx++;
		}

		if (match_idx.has_value()) {
			pr_trace("Autoload: Attempting to load '%.*s', found at idx %u (total %u left to try)\n",
					 (int)s.size(),
					 s.data(),
					 match_idx.value(),
					 left_to_try);

			attempted_to_load.push_back(match_idx.value());
			plugins.load_plugin(match_idx.value());
			return true;

		} else {
			pr_info("Autoload: Can't find plugin: '%.*s'\n", (int)s.size(), s.data());
			return false;
		}
	}

	PluginAutoloadSettings &plugin_settings;
	PluginManager &plugins;
	PluginFileList const *found_plugins = nullptr;
	unsigned slug_idx = 0;
	State autoload_state{State::NotStarted};

	std::vector<unsigned> attempted_to_load;
	unsigned left_to_try;
};

} // namespace MetaModule
