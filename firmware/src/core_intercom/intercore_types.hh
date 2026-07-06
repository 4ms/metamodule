#pragma once
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <optional>
#include <span>
#include <type_traits>
#include <utility>
#include <variant>

// Fixed-layout vocabulary types for data shared between cores.
//
// On MP1 both cores are 32-bit and see shared memory at the same addresses.
// On MP2 the A35 is 64-bit and the M33 is 32-bit, so structs that cross the
// core boundary must not contain pointers, std::span, std::optional,
// std::variant, size_t, or long: the layouts differ (and a raw address from
// one core may not be usable on the other).
//
// These types have identical layout on 32-bit ARM, AArch64, and 64-bit test
// hosts, and mimic the API of what they replace so call sites stay readable.
//
// Every struct that crosses the core boundary should pin its layout:
//   static_assert(sizeof(X) == <N>);
// compiled by BOTH cores' builds (and the simulator), so divergence is a
// build error rather than a silent protocol mismatch.

namespace MetaModule
{

// Each core sets its own view of the shared region base once at startup.
// Only 32-bit offsets from this base cross the core boundary.
// Where both cores see shared memory at the same 32-bit addresses (MP1 today),
// leave base = 0: offsets are then just addresses.
struct InterCoreSharedRegion {
	static inline uintptr_t base = 0;
};

// A pointer shared between cores: stored as a 32-bit offset from
// InterCoreSharedRegion::base. Mimics a raw pointer (->, *, bool).
//
// The simulator is a single 64-bit process with no core boundary, and its
// objects are scattered across a 64-bit address space that a 32-bit offset
// cannot represent -- so simulator builds store the native pointer instead
// (same API; the pinned cross-core layout only matters on hardware, where the
// unit-test build still verifies it).
template<typename T>
struct InterCorePtr32 {
	static constexpr uint32_t NullOffset = 0xFFFF'FFFF;

#if defined(SIMULATOR)
	T *raw = nullptr;

	InterCorePtr32() = default;

	InterCorePtr32(T *ptr) {
		raw = ptr;
	}

	InterCorePtr32 &operator=(T *ptr) {
		raw = ptr;
		return *this;
	}

	T *get() const {
		return raw;
	}
#else
	uint32_t offset = NullOffset;

	InterCorePtr32() = default;

	InterCorePtr32(T *ptr) {
		*this = ptr;
	}

	InterCorePtr32 &operator=(T *ptr) {
		offset = ptr ? static_cast<uint32_t>(reinterpret_cast<uintptr_t>(ptr) - InterCoreSharedRegion::base) :
					   NullOffset;
		return *this;
	}

	T *get() const {
		return offset == NullOffset ? nullptr : reinterpret_cast<T *>(InterCoreSharedRegion::base + offset);
	}
#endif

	T *operator->() const {
		return get();
	}

	T &operator*() const {
		return *get();
	}

	explicit operator bool() const {
		return get() != nullptr;
	}
};

// A span shared between cores: 32-bit offset + 32-bit count.
// Mimics std::span (data/size/begin/end/[]/empty) and converts to/from one.
template<typename T>
struct InterCoreSpan {
	InterCorePtr32<T> ptr{};
	uint32_t count = 0;

	InterCoreSpan() = default;

	// Accepts spans of T, and of non-const T when T is const (like std::span)
	template<typename U>
		requires std::is_convertible_v<U (*)[], T (*)[]>
	InterCoreSpan(std::span<U> sp) {
		*this = sp;
	}

	InterCoreSpan(T *data, size_t count) {
		ptr = data;
		this->count = static_cast<uint32_t>(count);
	}

	template<typename U>
		requires std::is_convertible_v<U (*)[], T (*)[]>
	InterCoreSpan &operator=(std::span<U> sp) {
		ptr = static_cast<T *>(sp.data());
		count = static_cast<uint32_t>(sp.size());
		return *this;
	}

	std::span<T> get() const {
		if (auto *p = ptr.get())
			return {p, count};
		return {};
	}

	operator std::span<T>() const {
		return get();
	}

	T *data() const {
		return ptr.get();
	}

	uint32_t size() const {
		return count;
	}

	uint32_t size_bytes() const {
		return count * sizeof(T);
	}

	bool empty() const {
		return count == 0 || !ptr;
	}

	T *begin() const {
		return data();
	}

	T *end() const {
		return data() + count;
	}

	T &operator[](uint32_t i) const {
		return data()[i];
	}
};

// An optional shared between cores: value + 32-bit valid flag.
// Mimics std::optional (bool, *, value_or, reset) and converts to/from one.
template<typename T>
struct InterCoreOptional {
	static_assert(std::is_trivially_copyable_v<T>);

	T val{};
	uint32_t valid = 0;

	InterCoreOptional() = default;

	InterCoreOptional(T v)
		: val{v}
		, valid{1} {
	}

	InterCoreOptional(std::nullopt_t) {
	}

	InterCoreOptional(const std::optional<T> &o) {
		*this = o;
	}

	InterCoreOptional &operator=(const std::optional<T> &o) {
		valid = o.has_value() ? 1 : 0;
		val = o.value_or(T{});
		return *this;
	}

	InterCoreOptional &operator=(T v) {
		val = v;
		valid = 1;
		return *this;
	}

	InterCoreOptional &operator=(std::nullopt_t) {
		reset();
		return *this;
	}

	bool has_value() const {
		return valid != 0;
	}

	explicit operator bool() const {
		return has_value();
	}

	T value() const {
		return val;
	}

	T operator*() const {
		return val;
	}

	T value_or(T alt) const {
		return has_value() ? val : alt;
	}

	void reset() {
		valid = 0;
		val = T{};
	}

	std::optional<T> to_optional() const {
		return has_value() ? std::optional<T>{val} : std::nullopt;
	}

	operator std::optional<T>() const {
		return to_optional();
	}
};

namespace detail
{
template<typename T, typename... Ts>
constexpr uint32_t index_of() {
	uint32_t idx = 0;
	bool found = ((std::is_same_v<T, Ts> ? true : (idx++, false)) || ...);
	return found ? idx : ~0u;
}
} // namespace detail

// A variant shared between cores: 32-bit tag + union storage of trivially
// copyable alternatives. Business logic can keep using std::visit by
// round-tripping through std::variant:
//   auto v = shared_msg.to_variant();
//   std::visit(handler, v);
//   shared_msg = v;
// or dispatch in place with .visit(f) (no copies).
template<typename... Ts>
struct InterCoreVariant {
	static_assert((std::is_trivially_copyable_v<Ts> && ...),
				  "All alternatives must be trivially copyable to cross the core boundary");

	using Variant = std::variant<Ts...>;

	uint32_t tag = 0; // index into Ts... (matches std::variant::index())
	alignas(Ts...) uint8_t storage[std::max({sizeof(Ts)...})]{};

	InterCoreVariant() {
		*this = first_alternative();
	}

	template<typename T>
		requires(detail::index_of<T, Ts...>() != ~0u)
	InterCoreVariant(const T &v) {
		*this = v;
	}

	InterCoreVariant(const Variant &v) {
		*this = v;
	}

	template<typename T>
		requires(detail::index_of<T, Ts...>() != ~0u)
	InterCoreVariant &operator=(const T &v) {
		tag = detail::index_of<T, Ts...>();
		std::memcpy(storage, &v, sizeof(T));
		return *this;
	}

	InterCoreVariant &operator=(const Variant &v) {
		std::visit([this](auto const &alt) { *this = alt; }, v);
		return *this;
	}

	uint32_t index() const {
		return tag;
	}

	template<typename T>
	bool holds() const {
		return tag == detail::index_of<T, Ts...>();
	}

	// In-place access. Only valid if holds<T>().
	template<typename T>
	T &as() {
		return *reinterpret_cast<T *>(storage);
	}

	template<typename T>
	const T &as() const {
		return *reinterpret_cast<const T *>(storage);
	}

	Variant to_variant() const {
		Variant v = as_alternative<Ts...>();
		return v;
	}

	operator Variant() const {
		return to_variant();
	}

	// In-place visit (no copies): f is invoked with a reference to the active
	// alternative, like std::visit on a variant of references.
	template<typename F>
	decltype(auto) visit(F &&f) {
		return visit_impl(std::forward<F>(f), std::index_sequence_for<Ts...>{});
	}

	template<typename F>
	decltype(auto) visit(F &&f) const {
		return visit_impl(std::forward<F>(f), std::index_sequence_for<Ts...>{});
	}

private:
	static auto first_alternative() {
		return std::variant_alternative_t<0, Variant>{};
	}

	template<typename... Us>
	Variant as_alternative() const {
		using Ctor = Variant (*)(const uint8_t *);
		static constexpr Ctor table[] = {
			[](const uint8_t *s) { return Variant{std::in_place_type<Us>, *reinterpret_cast<const Us *>(s)}; }...};
		return table[tag](storage);
	}

	template<typename F, size_t... I>
	decltype(auto) visit_impl(F &&f, std::index_sequence<I...>) {
		using R = decltype(f(as<std::variant_alternative_t<0, Variant>>()));
		if constexpr (std::is_void_v<R>) {
			((tag == I ? (f(as<std::variant_alternative_t<I, Variant>>()), void()) : void()), ...);
		} else {
			R r{};
			((tag == I ? (r = f(as<std::variant_alternative_t<I, Variant>>()), void()) : void()), ...);
			return r;
		}
	}

	template<typename F, size_t... I>
	decltype(auto) visit_impl(F &&f, std::index_sequence<I...>) const {
		using R = decltype(f(as<std::variant_alternative_t<0, Variant>>()));
		if constexpr (std::is_void_v<R>) {
			((tag == I ? (f(as<std::variant_alternative_t<I, Variant>>()), void()) : void()), ...);
		} else {
			R r{};
			((tag == I ? (r = f(as<std::variant_alternative_t<I, Variant>>()), void()) : void()), ...);
			return r;
		}
	}
};

// Layout checks: these types must be identical on 32-bit ARM, AArch64, and the
// unit-test host build (the simulator uses native pointers -- see above)
#if !defined(SIMULATOR)
static_assert(sizeof(InterCorePtr32<int>) == 4);
static_assert(sizeof(InterCoreSpan<char>) == 8);
static_assert(sizeof(InterCoreOptional<uint32_t>) == 8);
static_assert(alignof(InterCorePtr32<int>) == 4);
static_assert(alignof(InterCoreSpan<char>) == 4);
#endif

} // namespace MetaModule
