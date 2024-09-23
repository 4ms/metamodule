#pragma once

#include "util/fixed_vector.hh"

struct AllocationWatcher {
	struct Block {
		void *addr{};
		size_t size{};
		bool dealloced = false;
	};

	FixedVector<Block, 4096> allocs{};

	// Error condition: more blocks allocated than we can measure
	bool too_many_allocs = false;

	// A block was freed that is not active
	bool double_free = false;

	// Peak memory usage during test
	int64_t peak_usage = 0;

	// Total blocks allocated and deallocated
	int64_t mem_alloced = 0;
	int64_t mem_dealloced = 0;

	void register_alloc(size_t size, void *addr) {
		mem_alloced += size;
		peak_usage = std::max(mem_alloced - mem_dealloced, peak_usage);
		if (!allocs.push_back({addr, size, false}))
			too_many_allocs = true;
	}

	void register_dealloc(void *addr) {
		auto block = std::find_if(allocs.begin(), allocs.end(), [addr = addr](Block &alloc) {
			return (alloc.addr == addr) && (alloc.dealloced == false);
		});
		if (block != allocs.end()) {
			block->dealloced = true;
			mem_dealloced += block->size;
		}
	}

	void reset() {
		peak_usage = 0;
		mem_alloced = 0;
		mem_dealloced = 0;
		too_many_allocs = false;
		allocs.clear();
	}
};
