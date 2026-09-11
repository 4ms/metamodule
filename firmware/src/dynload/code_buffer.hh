#pragma once
#include <cstdint>
#include <new>
#include <vector>

namespace MetaModule
{

// Allocator for the buffer a plugin's ELF image is loaded into.
// Forces 4096 (0x1000) alignment (ELF segment alignment)
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

// Matches p_align of LOAD segments in SDK-built plugins; DynLoader warns if a
// plugin's ELF requests something larger
inline constexpr std::size_t CodeBufferAlignment = 0x1000;

using CodeBuffer = std::vector<uint8_t, ElfImageAllocator<uint8_t, CodeBufferAlignment>>;

} // namespace MetaModule
