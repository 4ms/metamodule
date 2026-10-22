#include "dynload/exidx_registry.hh"
#include "pr_dbg.hh"
#include <array>

// MP2 version of src/dynload/exidx_registry.cc. AArch64 has no .ARM.exidx tables: a plugin's unwind
// info is its .eh_frame (DWARF), which we register with libgcc's unwinder, as the firmware does its
// own (system/eh_frame_ca35.cc). Plugins import that unwinder (_Unwind_*), so an exception can
// unwind through plugin and firmware frames. Same API as MP1's: unwind_table is the .eh_frame's
// address (the SDK ends it with a zero terminator), and num_entries isn't used.

extern "C" {
void __register_frame_info(const void *begin, void *object);
void *__deregister_frame_info(const void *begin);
}

namespace MetaModule::ExidxRegistry
{

namespace
{
struct Entry {
	uintptr_t code_start = 0;
	const void *eh_frame = nullptr;
	// libgcc's struct object (unwind-dw2-fde.h), which it fills in: 6 pointers on AArch64, with room
	// to spare
	void *object[16]{};
};

// As many as MP1's registry
std::array<Entry, 32> entries;
} // namespace

void register_range(uintptr_t code_start, uintptr_t code_end, uintptr_t unwind_table, unsigned num_entries) {
	unregister_range(code_start);

	for (auto &entry : entries) {
		if (entry.eh_frame == nullptr) {
			entry.code_start = code_start;
			entry.eh_frame = reinterpret_cast<const void *>(unwind_table);
			__register_frame_info(entry.eh_frame, entry.object);
			return;
		}
	}

	pr_err("Too many plugins to register their exception tables: exceptions in this one won't be caught\n");
}

void unregister_range(uintptr_t code_start) {
	for (auto &entry : entries) {
		if (entry.eh_frame && entry.code_start == code_start) {
			__deregister_frame_info(entry.eh_frame);
			entry.eh_frame = nullptr;
			entry.code_start = 0;
		}
	}
}

} // namespace MetaModule::ExidxRegistry
