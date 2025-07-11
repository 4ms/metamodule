#pragma once
#include "util/static_string.hh"
#include <memory>
#include <string>

namespace MetaModule
{

class PluginAppInterface {
public:
	// Audio
	static uint32_t get_block_size();

	// Patch
	static void mark_patch_modified();
	static StaticString<7> get_volume();
	static std::string get_path();

	// Gui
	static void notify_user(std::string_view message, int duration_ms);

	struct Internal;

private:
	std::unique_ptr<Internal> internal;
	static PluginAppInterface *instance;

public:
	PluginAppInterface(Internal &internal);
	~PluginAppInterface();

	void register_interface();
};
} // namespace MetaModule
