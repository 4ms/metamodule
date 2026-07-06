#pragma once
#include "core_intercom/intercore_modulefs_message.hh"
#include <array>

namespace MetaModule
{

// Open-object tables on the filesystem core: FatFs FIL/DIR objects live here,
// and clients on the other core address them by FsHandle (the table index).
template<typename T, size_t MaxOpen>
struct FsObjectTable {
	std::array<T, MaxOpen> objects{};
	std::array<bool, MaxOpen> used{};

	// Returns a fresh object (and its handle), or nullptr if the table is full
	T *alloc(IntercoreModuleFS::FsHandle &handle) {
		for (size_t i = 0; i < MaxOpen; i++) {
			if (!used[i]) {
				used[i] = true;
				objects[i] = {};
				handle = i;
				return &objects[i];
			}
		}
		handle = IntercoreModuleFS::InvalidFsHandle;
		return nullptr;
	}

	T *get(IntercoreModuleFS::FsHandle handle) {
		if (handle < MaxOpen && used[handle])
			return &objects[handle];
		return nullptr;
	}

	void free(IntercoreModuleFS::FsHandle handle) {
		if (handle < MaxOpen)
			used[handle] = false;
	}
};

} // namespace MetaModule
