#include "console/uart_log.hh"
#include "safe_log.hh"
#include <cerrno>
#include <cstdint>

// Set to 1 to log every _sbrk() call (heap growth/shrink) to the console.
#define MM_DEBUG_SBRK 0

// Only log increments at least this large, in bytes. 0 logs everything.
#define MM_DEBUG_SBRK_MIN_INCR 0

static char *heap_end = nullptr;
// Defined by the linker
extern char _sheap;
extern char _eheap;

#ifdef CORE_CA7
// The firmware heap shares the A7 heap region with the plugin arena, which
// claims slabs downward from _eheap: the boundary is dynamic. Growth is
// authorized by mm_arena_allow_brk() (plugin_arena.cc), which checks against
// the arena floor and records the firmware's high-water break so arena slab
// claims keep clear of it.
extern "C" int mm_arena_allow_brk(uintptr_t new_brk);
extern "C" uintptr_t mm_arena_floor(void);

static char *heap_limit() {
	return reinterpret_cast<char *>(mm_arena_floor());
}
static bool allow_grow(char *new_end) {
	return mm_arena_allow_brk(reinterpret_cast<uintptr_t>(new_end)) != 0;
}
#else
static char *heap_limit() {
	return &_eheap;
}
static bool allow_grow(char *new_end) {
	return new_end <= &_eheap;
}
#endif

size_t get_heap_size() {
	return reinterpret_cast<size_t>(heap_end) - reinterpret_cast<size_t>(&_sheap);
}

// The firmware heap's current break, for the plugin arena's headroom guard
// and diagnostics
extern "C" uintptr_t mm_current_brk(void) {
	return reinterpret_cast<uintptr_t>(heap_end ? heap_end : &_sheap);
}

// _sbrk runs underneath malloc, and printf() calls malloc, so we use SafeLog to push chars
// to a stack buffer and flush directly to the uart instead of using printf()
namespace
{

using SbrkLog = MetaModule::SafeLog;

// Running stats, so the OOM report can say whether one giant request blew the heap
// or whether we simply crept up to the ceiling.
int64_t sbrk_largest_incr = 0;
uint64_t sbrk_calls = 0;
char *sbrk_peak = nullptr;

void log_sbrk(int incr, char *brk, bool oom) {
	SbrkLog log;
	log.str(oom ? "[sbrk] OOM! incr=" : "[sbrk] incr=");
	log.i64(incr);

	log.str(" used=");
	log.u64(uintptr_t(brk) - uintptr_t(&_sheap));

	log.str(" free=");
	log.u64(uintptr_t(heap_limit()) - uintptr_t(brk));

	log.str(" brk=");
	log.hex(uintptr_t(brk));

	if (oom) {
		log.str(" peak=");
		log.u64(uintptr_t(sbrk_peak) - uintptr_t(&_sheap));
		log.str(" largest_incr=");
		log.i64(sbrk_largest_incr);
		log.str(" calls=");
		log.u64(sbrk_calls);
	}

	log.flush();
}

} // namespace

extern "C" size_t _sbrk(int incr) {
	char *prev_heap_end;

	if (heap_end == nullptr) {
		heap_end = &_sheap;
	}
	prev_heap_end = heap_end;

	// Overflow-safe pre-check against the current limit, then the
	// authoritative check-and-reserve against the (dynamic) arena boundary
	if (incr > 0) {
		if (static_cast<uintptr_t>(incr) > static_cast<uintptr_t>(heap_limit() - heap_end) ||
			!allow_grow(heap_end + incr))
		{
			log_sbrk(incr, heap_end, true);
			errno = ENOMEM;
			return -1;
			// OOM!!!
		}
	}

	heap_end += incr;

	sbrk_calls++;
	if (incr > sbrk_largest_incr)
		sbrk_largest_incr = incr;
	if (heap_end > sbrk_peak)
		sbrk_peak = heap_end;

#if MM_DEBUG_SBRK
	if (incr >= MM_DEBUG_SBRK_MIN_INCR || incr < 0)
		log_sbrk(incr, heap_end, false);
#endif

	return (size_t)prev_heap_end;
}
