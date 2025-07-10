#pragma once
#include <memory>

namespace MetaModule
{

struct UserSettings;
struct PatchPlayLoader;

struct PluginInterface {

	PluginInterface(UserSettings &settings, PatchPlayLoader &playloader);
	~PluginInterface();

	// Plugin side:
	uint32_t get_block_size() const;
	void mark_patch_modified();

	static PluginInterface *instance;

	void register_interface() {
		instance = this;
	}

private:
	struct Internal;
	std::unique_ptr<Internal> internal;
};
} // namespace MetaModule
