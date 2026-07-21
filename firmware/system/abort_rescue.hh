#pragma once
#include <csetjmp>

// Rescue scopes for plugin deaths. A plugin that hits an unrecoverable error
// (typically an uncaught bad_alloc: its own operator new throws, nothing
// catches, its std::terminate runs) ends up calling its imported abort(),
// which the dynloader routes to mm_plugin_abort() in plugin_arena.cc. Plugin
// exceptions cannot unwind through firmware frames (separate self-contained
// unwinders), so the only way to regain control is to longjmp back to a
// rescue scope armed just before firmware called into the plugin.
//
// A longjmp skips every destructor between the abort and the scope, so
// whatever the plugin allocated is leaked into the plugin arena (bounded,
// reported, reclaimed on reboot -- or by a future arena reset). The caller
// at the rescue point is responsible for backing out firmware-side state
// (unregistering brands, substituting a null module, ...).

namespace MetaModule
{

#if defined(SIMULATOR) || defined(TESTPROJECT)

// Hosted builds: plugins share the host runtime; aborts are not rescued
struct AbortRescue {
	std::jmp_buf jb;
	void arm() {
	}
};

#else

struct AbortRescue {
	AbortRescue() = default;
	~AbortRescue();

	// Call only AFTER setjmp(jb) has filled the buffer:
	//   if (setjmp(rescue.jb) == 0) { rescue.arm(); ...protected... }
	//   else { ...rescued... }
	void arm();

	std::jmp_buf jb;

	AbortRescue *prev = nullptr;
	int proc = -1;
	bool active = false;
};

// Called from the plugin abort hook. If the current process has an armed
// scope and no allocator locks are held, disarms and longjmps (does not
// return). Returns if rescue is not possible; the caller must halt.
void abort_rescue_try(const char *reason);

#endif

} // namespace MetaModule
