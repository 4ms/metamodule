#pragma once
#include "util/static_string.hh"
#include <cstddef>
#include <string_view>

namespace MetaModule
{

#if defined(SIMULATOR)

// Hosted builds: allocation-failure diagnostics are firmware-only, and the
// implementation (alloc_diag.cc) is not linked. No-op stand-in.
struct AllocContext {
	AllocContext(std::string_view, std::string_view) {
	}
};

#else

namespace AllocDiag
{

struct Context {
	StaticString<24> kind;
	StaticString<96> name;
	bool active = false;
};

// Swap in a new context for the current process, returning the previous one
Context exchange(std::string_view kind, std::string_view name);
void restore(Context const &prev);

// Mark the current process's context inactive, keeping the strings as a
// breadcrumb. Used when a rescue longjmp abandons the stack frames whose
// AllocContext destructors would have restored it.
void abandon();

} // namespace AllocDiag

// Names the operation currently allocating (which module is being constructed,
// which plugin is running init()) so that an allocation failure can report the
// culprit. Scoped and nestable: the destructor restores the enclosing context.
// After the outermost scope exits, the name is kept as a breadcrumb and
// reported as "last completed" rather than in-progress.
// Contexts are tracked per-process (see reent_mm.hh), so an async thread
// arming a context does not clobber the main loop's.
struct AllocContext {
	AllocContext(std::string_view kind, std::string_view name)
		: prev{AllocDiag::exchange(kind, name)} {
	}
	~AllocContext() {
		AllocDiag::restore(prev);
	}
	AllocContext(AllocContext const &) = delete;
	AllocContext &operator=(AllocContext const &) = delete;

private:
	AllocDiag::Context prev;
};

// Reports the failed request, any in-flight contexts, and the heap state to
// the console, then halts this core. Never returns: callers of new do not
// reliably handle nullptr, so returning would turn a named failure here into
// an anonymous crash somewhere else.
[[noreturn]] void alloc_failed(std::size_t size, std::size_t align);

// Print any in-flight (or last-completed) allocation contexts, without
// altering control flow. Called from _sbrk when the heap limit is hit: a
// plugin's allocations go through its own statically-linked operator new,
// which firmware's new.cc never sees, so sbrk is the one chokepoint that can
// attribute every failure. Safe under the malloc lock (allocates nothing).
void report_alloc_contexts();

#endif // SIMULATOR

} // namespace MetaModule
