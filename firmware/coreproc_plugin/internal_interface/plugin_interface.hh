#pragma once
#include "gui/notify/queue.hh"
#include <memory>

namespace MetaModule
{

struct UserSettings;
struct PatchPlayLoader;

struct PluginInterface {

	PluginInterface(UserSettings &settings, PatchPlayLoader &playloader, NotificationQueue &notify_queue);
	~PluginInterface();

	// Plugin side:
	uint32_t get_block_size() const;
	void mark_patch_modified();
	void notify_user(std::string_view message, int duration_ms);

	static PluginInterface *instance;

	// Firmware side:
	void register_interface() {
		instance = this;
	}

private:
	struct Internal;
	std::unique_ptr<Internal> internal;
};
} // namespace MetaModule
