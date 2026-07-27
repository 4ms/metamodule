#include "heap_dispatch.hh"
#include "plugin_arena.hh"

// ---- free/realloc dispatchers (--wrap) -------------------------------------
// Ownership legitimately crosses the firmware/plugin boundary in both
// directions (e.g. a std::string handed across), so every free/realloc must
// dispatch by the pointer's address. PluginArena blocks go back to the arena
// allocator, everything else to newlib free()
//
// The firmware links with --wrap=free etc, which
// redirects every firmware call site including newlib-internal ones.
// Plugin imports of free are redirected here as well

using namespace MetaModule;

extern "C" {

void __real_free(void *);
void __real__free_r(struct _reent *, void *);
void *__real_realloc(void *, size_t);
void *__real__realloc_r(struct _reent *, void *, size_t);

void __wrap_free(void *p) {
	if (PluginArena::contains(p))
		PluginArena::free(p);
	else
		__real_free(p);
}

void __wrap__free_r(struct _reent *r, void *p) {
	if (PluginArena::contains(p))
		PluginArena::free(p);
	else
		__real__free_r(r, p);
}

void *__wrap_realloc(void *p, size_t size) {
	if (PluginArena::contains(p))
		return PluginArena::realloc(p, size);
	return __real_realloc(p, size);
}

void *__wrap__realloc_r(struct _reent *r, void *p, size_t size) {
	if (PluginArena::contains(p))
		return PluginArena::realloc(p, size);
	return __real__realloc_r(r, p, size);
}

} // extern "C"
