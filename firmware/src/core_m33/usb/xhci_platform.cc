// What lib/xhci needs from us (xhci_platform.h): memory the controller can DMA to and from, and a
// timer. Like the USB device (usbd_conf.cc), the controller's memory is in .dma_nc, which isn't
// cached, so nothing needs cache maintenance.

#include "drivers/stm32xx.h"
#include "ld.h"
#include "xhci_platform.h"
#include <algorithm>
#include <array>
#include <bit>
#include <cstdio>
#include <cstring>

#define DMA_NC __attribute__((section(".dma_nc")))

extern "C" char _sdma_nc[]; // linker script

namespace
{

// Contexts, rings, the scratchpad, and the library's own structs. About 25kB per device, plus 30kB
// for the controller.
constexpr uint32_t PoolSize = 384 * 1024;
DMA_NC alignas(4096) std::array<uint8_t, PoolSize> pool;

// Blocking transfers whose buffers aren't in .dma_nc go through this (one at a time)
constexpr uint32_t BounceSize = 64 * 1024;
DMA_NC alignas(64) std::array<uint8_t, BounceSize> bounce;

// First-fit allocator over pool. The blocks cover the pool, in address order.
struct Block {
	uint32_t start;
	uint32_t size;
	bool used;
};
std::array<Block, 256> blocks{Block{0, PoolSize, false}};
unsigned num_blocks = 1;

void insert_block(unsigned idx, Block b) {
	std::copy_backward(&blocks[idx], &blocks[num_blocks], &blocks[num_blocks + 1]);
	blocks[idx] = b;
	num_blocks++;
}

void remove_block(unsigned idx) {
	std::copy(&blocks[idx + 1], &blocks[num_blocks], &blocks[idx]);
	num_blocks--;
}

bool is_dma_safe(const void *p, size_t len) {
	auto addr = reinterpret_cast<uintptr_t>(p);
	return addr >= reinterpret_cast<uintptr_t>(_sdma_nc) && addr + len <= M33_REGION_END;
}

} // namespace

extern "C" void *xhci_platform_alloc(size_t align, size_t size) {
	size = (size + 63) & ~size_t(63);
	align = std::max<size_t>(align, 64);
	// Rings and contexts must not cross a 64kB boundary: align blocks up to 4kB to their size
	if (size <= 4096)
		align = std::max<size_t>(align, std::bit_ceil(size));

	for (unsigned i = 0; i < num_blocks; i++) {
		auto b = blocks[i];
		if (b.used)
			continue;
		auto aligned = (b.start + align - 1) & ~uint32_t(align - 1);
		auto pad = aligned - b.start;
		if (pad + size > b.size)
			continue;

		// Need room for up to two more blocks (the padding before, the rest after)
		if (num_blocks + 2 > blocks.size()) {
			printf("xHCI: memory pool has too many blocks\n");
			return nullptr;
		}

		auto rest = b.size - pad - size;
		blocks[i] = Block{aligned, uint32_t(size), true};
		if (rest)
			insert_block(i + 1, Block{aligned + uint32_t(size), rest, false});
		if (pad)
			insert_block(i, Block{b.start, pad, false});

		auto *p = &pool[aligned];
		std::memset(p, 0, size);
		return p;
	}

	printf("xHCI: out of memory (%u bytes)\n", (unsigned)size);
	return nullptr;
}

extern "C" void xhci_platform_free(void *ptr) {
	if (!ptr)
		return;

	auto start = uint32_t(static_cast<uint8_t *>(ptr) - pool.data());
	for (unsigned i = 0; i < num_blocks; i++) {
		if (blocks[i].start != start || !blocks[i].used)
			continue;

		blocks[i].used = false;
		// Merge with the free neighbors
		if (i + 1 < num_blocks && !blocks[i + 1].used) {
			blocks[i].size += blocks[i + 1].size;
			remove_block(i + 1);
		}
		if (i > 0 && !blocks[i - 1].used) {
			blocks[i - 1].size += blocks[i].size;
			remove_block(i);
		}
		return;
	}

	printf("xHCI: freeing %p, which wasn't allocated\n", ptr);
}

extern "C" void *xhci_platform_dma_buffer(void *buf, size_t len) {
	if (is_dma_safe(buf, len))
		return buf;
	if (len > BounceSize) {
		printf("xHCI: transfer of %u bytes is too big to bounce\n", (unsigned)len);
		return nullptr;
	}
	return bounce.data();
}

extern "C" unsigned long get_timer(unsigned long base) {
	return HAL_GetTick() - base;
}
