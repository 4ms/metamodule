#include "heap_dispatch.hh"
#include "plugin_arena.hh"
#include "system/abort_rescue.hh"
#include "system/safe_log.hh"
#include <cstdlib>
#include <cstring>
#include <new>
#include <string_view>

// ---- Plugin allocator wrappers ---------------------------------------------
// Plugins statically link their own operator new/delete/std containers, which
// call the C allocator functions imported from firmware. The dynloader
// rebinds those imports (via allocator_redirect below) to these wrappers so
// that everything plugin code allocates lands in the arena.
//
// A failed arena allocation returns nullptr, same as malloc. The plugin's own
// operator new then throws its own bad_alloc, which the plugin can catch and
// recover from. If it doesn't, its calls the imported abort() symbol which
// is redirected to mm_plugin_abort below.

using namespace MetaModule;

extern "C" void *__real_realloc(void *, size_t);

namespace
{

void *plugin_realloc(void *old, size_t size) {
	// A firmware-heap block stays on the firmware heap (newlib owns it); a
	// null or arena pointer (re)allocates in the arena -- unlike __wrap_realloc,
	// the caller here is known to be plugin code
	if (old && !PluginArena::contains(old))
		return __real_realloc(old, size);
	return PluginArena::realloc(old, size);
}

} // namespace

extern "C" {

void *mm_plugin_malloc(size_t size) {
	return PluginArena::alloc(size);
}

void *mm_plugin_calloc(size_t nmemb, size_t size) {
	auto total = nmemb * size;
	auto *p = PluginArena::alloc(total);
	if (p)
		memset(p, 0, total);
	return p;
}

void *mm_plugin_realloc(void *old, size_t size) {
	return plugin_realloc(old, size);
}

void *mm_plugin_memalign(size_t align, size_t size) {
	return PluginArena::alloc_aligned(align, size);
}

int mm_plugin_posix_memalign(void **memptr, size_t align, size_t size) {
	auto *p = PluginArena::alloc_aligned(align, size);
	if (!p)
		return 12; // ENOMEM
	*memptr = p;
	return 0;
}

void *mm_plugin_aligned_alloc(size_t align, size_t size) {
	return PluginArena::alloc_aligned(align, size);
}

// newlib reentrant entry points: same behavior, reent unused
void *mm_plugin_malloc_r(struct _reent *, size_t size) {
	return PluginArena::alloc(size);
}

void *mm_plugin_realloc_r(struct _reent *, void *old, size_t size) {
	return plugin_realloc(old, size);
}

void *mm_plugin_calloc_r(struct _reent *, size_t nmemb, size_t size) {
	return mm_plugin_calloc(nmemb, size);
}

void *mm_plugin_memalign_r(struct _reent *, size_t align, size_t size) {
	return mm_plugin_memalign(align, size);
}

// C++ operator new/delete, for plugins that import them instead of statically
// linking libstdc++'s. The throwing news must not return nullptr; the thrown
// bad_alloc is the firmware's, and (until cross-boundary unwinding exists)
// will terminate if no handler is reached before plugin frames.
void *mm_plugin_op_new(unsigned size) {
	auto *p = PluginArena::alloc(size);
	if (!p)
		throw std::bad_alloc{};
	return p;
}

void *mm_plugin_op_new_nothrow(unsigned size, void const *) {
	return PluginArena::alloc(size);
}

void *mm_plugin_op_new_aligned(unsigned size, unsigned align) {
	auto *p = PluginArena::alloc_aligned(align, size);
	if (!p)
		throw std::bad_alloc{};
	return p;
}

// A plugin that hits an unrecoverable error calls its imported abort() --
// most commonly via its own std::terminate after an uncaught bad_alloc (its
// verbose-terminate message has already been printed by the time we get
// here). Plugin exceptions cannot unwind into firmware frames, so this hook
// is the only chance to regain control: longjmp back to the rescue scope
// armed around the call into plugin code (module creation, plugin init).
// With no scope armed (e.g. death in the audio context), fall through to a
// real abort and halt.
void mm_plugin_abort(void) {
	{
		SafeLog log;
		log.str("[abort] plugin called abort(); arena used=");
		log.u64(PluginArena::used_bytes());
		log.str(" of ");
		log.u64(PluginArena::claimed_bytes());
		log.flush();
	}
	MetaModule::abort_rescue_try("plugin abort");
	::abort();
}

void mm_plugin_op_delete(void *p) {
	__wrap_free(p);
}

void mm_plugin_op_delete_sized(void *p, unsigned) {
	__wrap_free(p);
}

void mm_plugin_op_delete_aligned(void *p, unsigned) {
	__wrap_free(p);
}

} // extern "C"

namespace MetaModule::PluginArena
{

void *allocator_redirect(std::string_view name) {
	// clang-format off
	if (name == "malloc")          return reinterpret_cast<void *>(mm_plugin_malloc);
	if (name == "calloc")          return reinterpret_cast<void *>(mm_plugin_calloc);
	if (name == "realloc")         return reinterpret_cast<void *>(mm_plugin_realloc);
	if (name == "memalign")        return reinterpret_cast<void *>(mm_plugin_memalign);
	if (name == "posix_memalign")  return reinterpret_cast<void *>(mm_plugin_posix_memalign);
	if (name == "aligned_alloc")   return reinterpret_cast<void *>(mm_plugin_aligned_alloc);
	if (name == "_malloc_r")       return reinterpret_cast<void *>(mm_plugin_malloc_r);
	if (name == "_realloc_r")      return reinterpret_cast<void *>(mm_plugin_realloc_r);
	if (name == "_calloc_r")       return reinterpret_cast<void *>(mm_plugin_calloc_r);
	if (name == "_memalign_r")     return reinterpret_cast<void *>(mm_plugin_memalign_r);

	// De-allocation goes to the address-dispatching wrappers: a name lookup
	// of "free" in the ELF finds real newlib free (--wrap doesn't rename), so
	// plugins would otherwise free arena pointers into the newlib heap
	if (name == "free")            return reinterpret_cast<void *>(__wrap_free);
	if (name == "_free_r")         return reinterpret_cast<void *>(__wrap__free_r);

	// Plugin death (uncaught exception -> terminate -> abort) routes to the
	// rescue hook instead of halting
	if (name == "abort")           return reinterpret_cast<void *>(mm_plugin_abort);

	// operator new(unsigned), new[], nothrow and aligned variants (arm32 mangling)
	if (name == "_Znwj")                     return reinterpret_cast<void *>(mm_plugin_op_new);
	if (name == "_Znaj")                     return reinterpret_cast<void *>(mm_plugin_op_new);
	if (name == "_ZnwjRKSt9nothrow_t")       return reinterpret_cast<void *>(mm_plugin_op_new_nothrow);
	if (name == "_ZnajRKSt9nothrow_t")       return reinterpret_cast<void *>(mm_plugin_op_new_nothrow);
	if (name == "_ZnwjSt11align_val_t")      return reinterpret_cast<void *>(mm_plugin_op_new_aligned);
	if (name == "_ZnajSt11align_val_t")      return reinterpret_cast<void *>(mm_plugin_op_new_aligned);

	// operator delete(void*), delete[], sized and aligned variants
	if (name == "_ZdlPv")                    return reinterpret_cast<void *>(mm_plugin_op_delete);
	if (name == "_ZdaPv")                    return reinterpret_cast<void *>(mm_plugin_op_delete);
	if (name == "_ZdlPvj")                   return reinterpret_cast<void *>(mm_plugin_op_delete_sized);
	if (name == "_ZdaPvj")                   return reinterpret_cast<void *>(mm_plugin_op_delete_sized);
	if (name == "_ZdlPvSt11align_val_t")     return reinterpret_cast<void *>(mm_plugin_op_delete_aligned);
	if (name == "_ZdaPvSt11align_val_t")     return reinterpret_cast<void *>(mm_plugin_op_delete_aligned);
	// clang-format on
	return nullptr;
}

} // namespace MetaModule::PluginArena
