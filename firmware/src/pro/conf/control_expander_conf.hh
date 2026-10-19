#pragma once
#include "drivers/gpio_expander.hh"
#include "drivers/pin.hh"
#include <array>
#include <cstdint>

// Encoders and buttons on the four TCA9555 control expanders.
// (The fifth TCA9555, for jack sense, is in jack_sense_conf.hh)
//
// Bit numbering: a 16-bit expander reading has port 0 (P00..P07) in bits 0..7
// and port 1 (P10..P17) in bits 8..15.
//
// Encoders ENC1..ENC16 are the 16 panel knobs. ENC numbering follows the
// schematic net names (/ENCn_A, /ENCn_B, /ENCn_BUT).

namespace MetaModule::Controls
{

struct ExpanderConf {
	mdrivlib::GPIO_expander_conf chip;
	enum class Bus { ControlsA, ControlsB } bus; // controls_a_i2c_conf (I2C2), controls_b_i2c_conf (I2C3)
	mdrivlib::PinDef int_pin; // active-low, open drain (TCA9555 INT)
};

// U1210 on I2C2 (A0=1, A1=0, A2=0)
constexpr ExpanderConf ExpA = {
	.chip = {.addr = 0x21, .config = mdrivlib::GPIO_expander_conf::AllInputs()},
	.bus = ExpanderConf::Bus::ControlsA,
	.int_pin = {mdrivlib::GPIO::B, mdrivlib::PinNum::_2},
};

// U1211 on I2C2 (A0=0, A1=1, A2=0)
constexpr ExpanderConf ExpB = {
	.chip = {.addr = 0x22, .config = mdrivlib::GPIO_expander_conf::AllInputs()},
	.bus = ExpanderConf::Bus::ControlsA,
	.int_pin = {mdrivlib::GPIO::B, mdrivlib::PinNum::_11}, // !! also devboard microSD SDDET1
};

// U1213 on I2C3 (A0=1, A1=1, A2=0)
constexpr ExpanderConf ExpC = {
	.chip = {.addr = 0x23, .config = mdrivlib::GPIO_expander_conf::AllInputs()},
	.bus = ExpanderConf::Bus::ControlsB,
	.int_pin = {mdrivlib::GPIO::G, mdrivlib::PinNum::_7},
};

// U1209 on I2C3 (A0=0, A1=0, A2=1)
constexpr ExpanderConf ExpD = {
	.chip = {.addr = 0x24, .config = mdrivlib::GPIO_expander_conf::AllInputs()},
	.bus = ExpanderConf::Bus::ControlsB,
	.int_pin = {mdrivlib::GPIO::C, mdrivlib::PinNum::_12},
};

constexpr std::array Expanders{ExpA, ExpB, ExpC, ExpD};

// Location of one signal: which expander (index into Expanders) and which bit
struct ExpBit {
	uint8_t exp;
	uint8_t bit;
};

struct EncoderBits {
	ExpBit a;
	ExpBit b;
	ExpBit but;
};

constexpr uint8_t P0(uint8_t n) {
	return n;
}
constexpr uint8_t P1(uint8_t n) {
	return 8 + n;
}

// clang-format off
constexpr std::array<EncoderBits, 16> Encoders{{
	/* ENC1  */ {.a = {1, P1(5)}, .b = {1, P1(6)}, .but = {1, P1(7)}},
	/* ENC2  */ {.a = {1, P1(2)}, .b = {1, P1(3)}, .but = {1, P1(4)}},
	/* ENC3  */ {.a = {1, P0(7)}, .b = {1, P1(0)}, .but = {1, P1(1)}},
	/* ENC4  */ {.a = {0, P1(1)}, .b = {0, P1(2)}, .but = {0, P1(0)}},
	/* ENC5  */ {.a = {1, P0(1)}, .b = {1, P0(2)}, .but = {1, P0(0)}},
	/* ENC6  */ {.a = {1, P0(4)}, .b = {1, P0(5)}, .but = {1, P0(3)}},
	/* ENC7  */ {.a = {0, P1(6)}, .b = {0, P1(7)}, .but = {1, P0(6)}},
	/* ENC8  */ {.a = {0, P1(4)}, .b = {0, P1(3)}, .but = {0, P1(5)}},
	/* ENC9  */ {.a = {3, P1(5)}, .b = {3, P1(6)}, .but = {3, P1(7)}},
	/* ENC10 */ {.a = {3, P1(3)}, .b = {3, P1(2)}, .but = {3, P1(4)}},
	/* ENC11 */ {.a = {2, P0(0)}, .b = {2, P0(1)}, .but = {3, P1(1)}},
	/* ENC12 */ {.a = {2, P0(5)}, .b = {2, P0(4)}, .but = {2, P0(2)}},
	/* ENC13 */ {.a = {3, P0(1)}, .b = {3, P0(2)}, .but = {3, P0(0)}},
	/* ENC14 */ {.a = {3, P0(4)}, .b = {3, P0(5)}, .but = {3, P0(3)}},
	/* ENC15 */ {.a = {3, P0(7)}, .b = {3, P1(0)}, .but = {3, P0(6)}},
	/* ENC16 */ {.a = {2, P0(7)}, .b = {2, P0(6)}, .but = {2, P0(3)}},
}};

enum class Button : uint8_t {
	But1, But2, But3, But4, But5, But6, But7, But8,
	Nav1, Nav2, Nav3, Nav4, Nav5, Nav6,
	Knobset,
	Play,
};

constexpr std::array<ExpBit, 16> Buttons{{
	/* BUT1    */ {0, P0(4)},
	/* BUT2    */ {0, P0(5)},
	/* BUT3    */ {0, P0(6)},
	/* BUT4    */ {0, P0(7)},
	/* BUT5    */ {2, P1(0)},
	/* BUT6    */ {2, P1(1)},
	/* BUT7    */ {2, P1(2)},
	/* BUT8    */ {2, P1(3)},
	/* NAV1    */ {0, P0(2)},
	/* NAV2    */ {0, P0(1)},
	/* NAV3    */ {0, P0(0)},
	/* NAV4    */ {2, P1(7)},
	/* NAV5    */ {2, P1(6)},
	/* NAV6    */ {2, P1(5)},
	/* KNOBSET */ {0, P0(3)},
	/* PLAY    */ {2, P1(4)},
}};
// clang-format on

// Controls wired directly to MCU GPIOs
namespace Direct
{
// Main "control" encoder (next to the screen)
constexpr mdrivlib::PinDef CtlEncA{mdrivlib::GPIO::C, mdrivlib::PinNum::_3};
constexpr mdrivlib::PinDef CtlEncB{mdrivlib::GPIO::C, mdrivlib::PinNum::_9};
constexpr mdrivlib::PinDef CtlEncBut{mdrivlib::GPIO::H, mdrivlib::PinNum::_10};

// Navigation encoder
constexpr mdrivlib::PinDef NavEncA{mdrivlib::GPIO::C, mdrivlib::PinNum::_6};
constexpr mdrivlib::PinDef NavEncB{mdrivlib::GPIO::A, mdrivlib::PinNum::_10};
constexpr mdrivlib::PinDef NavEncBut{mdrivlib::GPIO::A, mdrivlib::PinNum::_5};

constexpr mdrivlib::PinDef BackBut{mdrivlib::GPIO::A, mdrivlib::PinNum::_9};

// Gate inputs (also sensed by the jack-sense expander)
constexpr mdrivlib::PinDef GateIn1{mdrivlib::GPIO::F, mdrivlib::PinNum::_0};
constexpr mdrivlib::PinDef GateIn2{mdrivlib::GPIO::C, mdrivlib::PinNum::_10};
} // namespace Direct

} // namespace MetaModule::Controls
