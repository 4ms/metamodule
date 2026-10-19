#pragma once
#include "CoreModules/hub/panel_medium_defs.hh"
#include "drivers/gpio_expander.hh"
#include "drivers/pin.hh"
#include <cstdint>
#include <optional>

// Jack sense: TCA9555 U1212 on the jack board, on the same I2C4 bus as the codec
// (codec_jack_i2c_conf in i2c_conf.hh). Its INT goes to PH9.
//
// The pro p1 jack layout matches the medium panel: 6 audio ins, 2 gate ins, 8 outs,
// so PanelDef (panel_medium_defs.hh) is used for now.
//
// TODO: verify sense polarity on hardware (MP1 reads 1 = patched)

namespace MetaModule::JackSense
{
const mdrivlib::GPIO_expander_conf gpio_expander_conf = {
	.addr = 0x20, // A0=A1=A2=GND
	.config = mdrivlib::GPIO_expander_conf::AllInputs(),
};

constexpr mdrivlib::PinDef IntPin{mdrivlib::GPIO::H, mdrivlib::PinNum::_9};
} // namespace MetaModule::JackSense

// Bit in the 16-bit expander reading (port 0 = bits 0-7, port 1 = bits 8-15) for each panel jack
// U1212: P00 GATEIN1, P01 GATEIN2, P02 In5, P03 In6, P04 In3, P05 In4, P06 In1, P07 In2,
//        P10 OUT8, P11 OUT7, P12 OUT6, P13 OUT5, P14 OUT4, P15 OUT3, P16 OUT2, P17 OUT1
constexpr unsigned jacksense_pin_order[16] = {
	/*in*/ 6, 7, 4, 5, 2, 3, /*gate in*/ 0, 1, /*out*/ 15, 14, 13, 12, 11, 10, 9, 8};

constexpr inline bool jack_is_patched(uint32_t jack_sense_reading, unsigned panel_jack_idx) {
	return (jack_sense_reading >> jacksense_pin_order[panel_jack_idx]) & 1;
}

constexpr inline std::optional<unsigned> main_jacksense_output_bit(unsigned panel_outjack_idx) {
	if (PanelDef::is_main_panel_output(panel_outjack_idx))
		return jacksense_pin_order[panel_outjack_idx + PanelDef::NumUserFacingInJacks];
	else
		return {};
}

constexpr inline std::optional<unsigned> main_jacksense_input_bit(unsigned panel_injack_idx) {
	if (PanelDef::is_main_panel_input(panel_injack_idx))
		return jacksense_pin_order[panel_injack_idx];
	else
		return {};
}
