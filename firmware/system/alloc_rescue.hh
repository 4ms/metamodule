#pragma once
#include <csetjmp>
#include <cstddef>
#include <string_view>

namespace MetaModule
{

#if defined(SIMULATOR)

// Hosted builds: OOM rescue is firmware-only (alloc_rescue.cc is not linked).
// The stand-in compiles the same guarded-scope code but never triggers.
struct AllocRescue {
	jmp_buf &jump_buf() {
		return jb;
	}
	void arm() {
	}
	bool was_oom() const {
		return false;
	}
	size_t free_survivors() {
		return 0;
	}
	size_t leaked_bytes() const {
		return 0;
	}
	jmp_buf jb;
};

namespace AllocRescueHooks
{
inline void *allocator_redirect(std::string_view) {
	return nullptr;
}
} // namespace AllocRescueHooks

#else

// Arms a rollback point for a bounded operation that might exhaust memory
// (constructing a module, running a plugin's init()). Usage:
//
//   AllocRescue rescue;
//   if (setjmp(rescue.jump_buf()) == 0) {
//       rescue.arm(); // AFTER setjmp has filled the buffer, never before
//       ...guarded operation...
//   } else {
//       // Rolled back: the operation died mid-flight. Run ownership-based
//       // cleanup first (it frees what escaped into live structures, and the
//       // log marks those blocks dead), then optionally free_survivors().
//   }
//
// The jump happens when an allocation fails in this same process (see
// try_rescue). Scopes nest: an inner scope shadows the outer until it exits.
// While armed, every allocation is recorded in a per-process undo log --
// including plugin-side allocations, which reach malloc through the host
// symbol table redirects (allocator_redirect below).
struct AllocRescue {
	AllocRescue();
	~AllocRescue();
	AllocRescue(AllocRescue const &) = delete;
	AllocRescue &operator=(AllocRescue const &) = delete;

	jmp_buf &jump_buf() {
		return jb;
	}

	// Start logging allocations and accept rescue jumps. Call only after
	// setjmp() has returned 0.
	void arm();

	// Valid after rollback: was the failure heap exhaustion (vs some other
	// abort during the guarded operation)?
	bool was_oom() const;

	// After rollback: free every block allocated since arm() that is not
	// already freed, returning the byte count. Run ownership-based cleanup
	// FIRST (unregister, delete, reset) -- the log keeps recording through the
	// rollback handler, so blocks those teardowns free are marked dead and
	// only the truly orphaned remainder is freed here. Any scope allocation
	// still reachable from a structure that outlives the scope when this is
	// called will be double-freed later -- clean up ownership first.
	size_t free_survivors();

	// After rollback: bytes still live in the log -- what free_survivors()
	// would reclaim, or what leaks if it can't be called safely.
	size_t leaked_bytes() const;

private:
	friend struct RescueState;
	jmp_buf jb;
	AllocRescue *prev{};
	unsigned slot{};
	unsigned log_start{};
	// active: a rescue jump may target this scope. Cleared when the jump is
	// taken so a failure inside the handler escalates outward.
	bool active = false;
	// logging: allocations/frees are recorded. Stays set through the rollback
	// handler so ownership cleanup there marks its frees in the log, letting
	// free_survivors() free only what is genuinely orphaned.
	bool logging = false;
	bool oom = false;
};

namespace AllocRescueHooks
{

// Record an allocation/deallocation in the current process's undo log.
// No-ops unless a rescue is armed for the current process.
void log_alloc(void *ptr, size_t size);
void log_free(void *ptr);

enum class RescueReason { OutOfMemory, Abort };

// If a rescue is armed for the current process and it is safe to jump (not
// holding the malloc lock), longjmp to it -- does not return in that case.
// Otherwise returns and the caller proceeds with its usual failure path.
void try_rescue(RescueReason);

// Called by _sbrk when the heap limit is hit, so a subsequent abort-rescue
// can be attributed to memory exhaustion
void note_heap_exhausted();

// Returns the logging wrapper for an allocator function name ("malloc",
// "_malloc_r", ...) or nullptr. The dynloader uses this to redirect plugins'
// allocator imports: plugins carry their own statically-linked operator new,
// so this is the only place their allocations can be observed.
void *allocator_redirect(std::string_view name);

} // namespace AllocRescueHooks

#endif // SIMULATOR

} // namespace MetaModule
