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

size_t get_heap_size() {
	return reinterpret_cast<size_t>(heap_end) - reinterpret_cast<size_t>(&_sheap);
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
	log.u64(uintptr_t(&_eheap) - uintptr_t(brk));

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

	// Overflow-safe bounds check
	if (incr > 0 && static_cast<uintptr_t>(incr) > static_cast<uintptr_t>(&_eheap - heap_end)) {
		log_sbrk(incr, heap_end, true);
		errno = ENOMEM;
		return -1;
		// OOM!!!
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
