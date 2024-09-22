#pragma once

#include "util/fixed_vector.hh"

struct AllocationWatch {
	size_t allocations = 0;

	FixedVector<std::pair<size_t, void *>, 4096> allocs{};
	bool overflowed = false;

	void register_alloc(size_t size, void *addr) {
		allocations += size;
		if (!allocs.push_back({size, addr}))
			overflowed = true;
	}

	void register_dealloc(void *addr) {
		for (auto i = 0u; auto alloc : allocs) {
			if (alloc.second == addr) {
				allocs.erase(i);
				break;
			}
		}
	}

	void reset() {
		allocations = 0;
		overflowed = false;
		allocs.clear();
	}
};
