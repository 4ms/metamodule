#include "user_settings/settings.hh"

namespace MetaModule
{

namespace
{

static UserSettings const *settings = nullptr;

} // namespace

__attribute__((visibility("hidden"))) void register_settings(UserSettings const *user_settings) {
	settings = user_settings;
}

uint32_t get_block_size() {

	if (settings) {
		return settings->audio.block_size;

	} else
		return 32; //reasonable default, but should never happen
}

} // namespace MetaModule
