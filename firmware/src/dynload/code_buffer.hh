#pragma once
#include <cstdint>
#include <new>
#include <vector>

namespace MetaModule
{

// Allocator for the buffer a plugin's ELF image is loaded into.
//
// DynLoader places every segment at buffer.data() + vaddr, so the buffer base
// must be at least as aligned as the ELF's segment alignment (p_align, 0x1000
// in SDK-built plugins): the linker only guarantees each object's alignment
// *relative to a properly-aligned load base*. A plain std::vector<uint8_t>
// guarantees just 8 bytes, which left every alignas(16) global inside a
// plugin misaligned whenever the heap block landed on an odd-8 address --
// gcc emits NEON loads with alignment hints (vld1 [rN@128]) for such globals,
// and those data-abort on a misaligned address. First seen with
// SignalFunctionSet:Operator's msfa engine (its aligned(16) `zeros` table).
template<typename T, std::size_t Alignment>
struct ElfImageAllocator {
	using value_type = T;

	ElfImageAllocator() noexcept = default;
	template<typename U>
	ElfImageAllocator(ElfImageAllocator<U, Alignment> const &) noexcept {
	}

	// Required: the default allocator_traits rebind can't pattern-match a
	// template with a non-type parameter
	template<typename U>
	struct rebind {
		using other = ElfImageAllocator<U, Alignment>;
	};

	T *allocate(std::size_t n) {
		// Throwing form: DynLoader::load() reports OOM by catching bad_alloc
		return static_cast<T *>(::operator new(n * sizeof(T), std::align_val_t{Alignment}));
	}

	void deallocate(T *p, std::size_t) noexcept {
		::operator delete(p, std::align_val_t{Alignment});
	}

	template<typename U>
	bool operator==(ElfImageAllocator<U, Alignment> const &) const noexcept {
		return true;
	}
};

using CodeBuffer = std::vector<uint8_t, ElfImageAllocator<uint8_t, 0x1000>>;

} // namespace MetaModule
