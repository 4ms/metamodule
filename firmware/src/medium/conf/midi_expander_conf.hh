#pragma once

#include "core_m4/midi_expander_driver.hh"

namespace MetaModule::Expander::Midi
{

inline constexpr auto addr = 0x30;

inline constexpr auto max_tx_payload = 255;
inline constexpr auto max_rx_payload = 255;

const MIDI_expander_conf midi_chip_conf = {
	.addr = addr,
};

} // namespace MetaModule::Expander::Midi
