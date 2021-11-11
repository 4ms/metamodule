#include "doctest.h"
#include "moduleTypes.h"
#include <iostream>
#include <stdint.h>

struct TestCoreMod : public CoreProcessor {
	void update() override {
	}
	void set_samplerate(const float sr) override {
	}
	void set_param(const int param_id, const float val) override {
	}
	void set_input(const int input_id, const float val) override {
	}
	float get_output(const int output_id) const override {
		return 0.f;
	}
};

std::unique_ptr<CoreProcessor> create() {
	return std::unique_ptr<TestCoreMod>();
}

struct TestInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"HIJ"};
	static constexpr uint32_t width_hp = 2;
};

TEST_CASE("Register derived object uses its values, not ModuleInfoBase") {
	bool already_exists = ModuleFactory::registerModuleType("ABC", "abc module", create);
	CHECK_FALSE(already_exists);

	already_exists = ModuleFactory::registerModuleType("DEF", "def module", create, ModuleInfoBase{});
	CHECK_FALSE(already_exists);

	already_exists = ModuleFactory::registerModuleType("HIJ", "hij module", create, TestInfo{});
	CHECK_FALSE(already_exists);

	auto info = ModuleFactory::getModuleInfo("HIJ");
	// CHECK(info.width_hp == 2); //Fails!
}
