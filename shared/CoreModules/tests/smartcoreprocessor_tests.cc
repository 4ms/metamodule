#include "../SmartCoreProcessor.hh"
#include "CoreModules/elements/element_info.hh"
#include "doctest.h"

using namespace MetaModule;

struct TestInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"Test"};
	static constexpr std::string_view description{""};
	static constexpr uint32_t width_hp = 4;
	static constexpr std::string_view svg_filename{""};

	using enum Coords;

	static constexpr std::array<Element, 6> Elements{{
		JackInput{{to_mm<72>(29.28), to_mm<72>(78.14), Center, "Samp 1", ""}},
		JackInput{{to_mm<72>(29.28), to_mm<72>(124.26), Center, "In 1", ""}},
		JackInput{{to_mm<72>(29.28), to_mm<72>(168.85), Center, "Samp 2", ""}},
		JackInput{{to_mm<72>(29.28), to_mm<72>(214.97), Center, "In 2", ""}},
		JackOutput{{to_mm<72>(29.28), to_mm<72>(264.07), Center, "Out 1", ""}},
		JackOutput{{to_mm<72>(29.28), to_mm<72>(312.29), Center, "Out 2", ""}},
	}};

	enum class Elem {
		Samp1In,
		In1In,
		Samp2In,
		In2In,
		Out1Out,
		Out2Out,
	};
};

struct TestModuleCore : SmartCoreProcessor<TestInfo> {
	void update() override {
	}
	void set_samplerate(float sr) override {
	}
};

TEST_CASE("Fail") {
	TestModuleCore core;

	// auto e = core.encode("ABCD");
	std::vector<uint8_t> raw{1, 2, 3, 4};
	std::string encoded = "{\"state\": \"AQIDBA==\"}";
	CHECK(encoded == core.encode(raw));

	auto roundtrip_raw = core.decode(encoded);
	for (unsigned i = 0; auto c : roundtrip_raw) {
		CHECK(c == raw[i++]);
	}
}
