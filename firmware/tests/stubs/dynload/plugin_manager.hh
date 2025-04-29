#pragma once
#include "dynload/plugin_loader.hh"
#include "util/version_tools.hh"
#include <string_view>
#include <vector>

namespace MetaModule
{

using Version = VersionUtil::Version;

inline Version sdk_version() {
	return {2, 0, 0};
}

struct PluginManager {
	std::vector<unsigned> spy_loaded;
	PluginFileList *fake_plugin_list = nullptr;
	std::string error;

	enum class State { Init, StartLoadingList, SentList, Loaded };
	State state = State::Init;

	void start_loading_plugin_list() {
		state = State::StartLoadingList;
	}

	PluginFileList const *found_plugin_list() {
		if (state == State::StartLoadingList)
			state = State::SentList;
		else
			error += "Got list before requesting to start loading it. ";

		return fake_plugin_list;
	}

	void load_plugin(unsigned idx) {
		spy_loaded.push_back(idx);
		state = State::Loaded;
	}

	void unload_plugin(std::string_view name) {
	}

	PluginFileLoader::Status process_loading() {
		if (state == State::StartLoadingList)
			return {.state = PluginFileLoader::State::GotList};

		if (state == State::Loaded)
			return {.state = PluginFileLoader::State::Success};
		return {};
	}
};
} // namespace MetaModule
