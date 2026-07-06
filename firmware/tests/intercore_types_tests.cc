// Tests for the fixed-layout inter-core vocabulary types (see
// core_intercom/intercore_types.hh and docs/MP2-Intercom-Audit.md).
// The layout static_asserts in the header run everywhere it's included; these
// tests cover behavior (offset round-trips, optional/variant conversions).
#include "core_intercom/intercore_types.hh"
#include "doctest.h"
#include <array>

using namespace MetaModule;

TEST_CASE("InterCorePtr32 round-trips through a 32-bit offset") {
	// Simulate a shared region: offsets are relative to its base
	alignas(8) static std::array<uint32_t, 64> shared_region{};
	InterCoreSharedRegion::base = reinterpret_cast<uintptr_t>(shared_region.data());

	SUBCASE("null by default and from nullptr") {
		InterCorePtr32<uint32_t> p;
		CHECK_FALSE(bool(p));
		CHECK(p.get() == nullptr);

		p = &shared_region[5];
		CHECK(bool(p));
		p = nullptr;
		CHECK_FALSE(bool(p));
	}

	SUBCASE("points back to the same object") {
		shared_region[7] = 0xABCD1234;
		InterCorePtr32<uint32_t> p = &shared_region[7];
		CHECK(p.offset == 7 * sizeof(uint32_t));
		CHECK(*p == 0xABCD1234);
		CHECK(p.get() == &shared_region[7]);
	}

	SUBCASE("operator-> works on struct members") {
		struct Thing {
			uint32_t x;
		};
		static Thing thing{42};
		InterCoreSharedRegion::base = reinterpret_cast<uintptr_t>(&thing);
		InterCorePtr32<Thing> p = &thing;
		CHECK(p->x == 42);
	}

	InterCoreSharedRegion::base = 0;
}

TEST_CASE("InterCoreSpan behaves like a span") {
	static std::array<char, 16> buf{"hello"};
	InterCoreSharedRegion::base = reinterpret_cast<uintptr_t>(buf.data());

	InterCoreSpan<char> s = std::span<char>{buf};
	CHECK(s.size() == 16);
	CHECK(s.data() == buf.data());
	CHECK(s[1] == 'e');

	std::span<char> back = s;
	CHECK(back.data() == buf.data());
	CHECK(back.size() == 16);

	SUBCASE("empty/default") {
		InterCoreSpan<char> e;
		CHECK(e.empty());
		CHECK(e.get().size() == 0);
		CHECK(e.data() == nullptr);
	}

	InterCoreSharedRegion::base = 0;
}

TEST_CASE("InterCoreOptional mimics std::optional") {
	InterCoreOptional<uint32_t> o;
	CHECK_FALSE(o.has_value());
	CHECK(o.value_or(9) == 9);

	o = 5u;
	CHECK(o.has_value());
	CHECK(*o == 5);
	CHECK(o.value_or(9) == 5);

	o = std::nullopt;
	CHECK_FALSE(o.has_value());

	SUBCASE("converts to and from std::optional") {
		std::optional<uint32_t> stdopt = 77;
		InterCoreOptional<uint32_t> ic = stdopt;
		CHECK(ic.has_value());
		CHECK(*ic == 77);

		std::optional<uint32_t> back = ic.to_optional();
		REQUIRE(back.has_value());
		CHECK(*back == 77);

		ic = std::optional<uint32_t>{};
		CHECK_FALSE(ic.to_optional().has_value());
	}
}

namespace
{
struct MsgA {
	uint32_t a{};
};
struct MsgB {
	uint32_t x{};
	uint32_t y{};
};
struct MsgC {
	uint64_t big{};
	uint32_t res{};
};
using TestICV = InterCoreVariant<MsgA, MsgB, MsgC>;
} // namespace

TEST_CASE("InterCoreVariant: tag, storage, and std::variant round-trip") {
	TestICV icv;
	CHECK(icv.index() == 0); // default = first alternative, like std::variant
	CHECK(icv.holds<MsgA>());

	icv = MsgB{.x = 3, .y = 4};
	CHECK(icv.index() == 1);
	CHECK(icv.holds<MsgB>());
	CHECK(icv.as<MsgB>().y == 4);

	SUBCASE("to_variant matches std::variant index and value") {
		auto v = icv.to_variant();
		CHECK(v.index() == 1);
		CHECK(std::get<MsgB>(v).x == 3);
	}

	SUBCASE("business logic via std::visit round-trip") {
		auto v = icv.to_variant();
		std::visit(
			[](auto &msg) {
				if constexpr (requires { msg.y; })
					msg.y += 10;
			},
			v);
		icv = v; // write the result back to the shared representation
		CHECK(icv.as<MsgB>().y == 14);
	}

	SUBCASE("in-place visit dispatches to the active alternative") {
		int which = -1;
		icv.visit([&](auto &msg) {
			using T = std::remove_cvref_t<decltype(msg)>;
			if constexpr (std::is_same_v<T, MsgB>)
				which = 1;
			else
				which = 0;
		});
		CHECK(which == 1);

		// mutate in place, no copies
		icv.visit([](auto &msg) {
			if constexpr (requires { msg.x; })
				msg.x = 99;
		});
		CHECK(icv.as<MsgB>().x == 99);
	}

	SUBCASE("in-place visit returns a value") {
		auto sz = icv.visit([](auto &msg) { return uint32_t(sizeof(msg)); });
		CHECK(sz == sizeof(MsgB));
	}

	SUBCASE("constructing from a std::variant") {
		std::variant<MsgA, MsgB, MsgC> v = MsgC{.big = 0x1234'5678'9ABC'DEF0, .res = 7};
		TestICV ic2 = v;
		CHECK(ic2.holds<MsgC>());
		CHECK(ic2.as<MsgC>().big == 0x1234'5678'9ABC'DEF0);
	}

	SUBCASE("layout: tag + max-size storage, alignment of largest member") {
		CHECK(sizeof(TestICV) == 4 /*tag*/ + 4 /*pad for u64 align*/ + sizeof(MsgC));
		CHECK(alignof(TestICV) == alignof(MsgC));
	}
}
