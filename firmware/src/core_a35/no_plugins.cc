// MP2 versions of the plugin memory arena (src/memory/plugin_arena.cc) and abort rescue
// (system/abort_rescue.cc). MP2 can't load plugins yet (see mp2-stubs/dynload/dynloader.hh), so
// there's no arena and nothing to rescue.
#include "memory/plugin_arena.hh"
#include "system/abort_rescue.hh"

namespace MetaModule
{

namespace PluginArena
{

size_t used_bytes() {
	return 0;
}

size_t peak_bytes() {
	return 0;
}

size_t claimed_bytes() {
	return 0;
}

} // namespace PluginArena

AbortRescue::~AbortRescue() = default;

void AbortRescue::arm() {
}

void abort_rescue_try(const char *) {
}

} // namespace MetaModule
