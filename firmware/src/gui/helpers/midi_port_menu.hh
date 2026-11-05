#pragma once
#include "conf/midi_ports_conf.hh"
#include "patch/midi_def.hh"
#include <algorithm>
#include <array>
#include <cstdint>
#include <optional>
#include <string_view>

// The MIDI port dropdowns: item 0 is "All", then the board's ports (Midi::BoardPorts)
namespace MetaModule::MidiPortMenu
{

// MP1 lists every port, in order: item n is port n-1
inline constexpr bool ListsAllPorts =
	std::ranges::equal(Midi::BoardPorts, std::array{Midi::USB, Midi::TRS, Midi::DIN5});

// The dropdowns' options (checked against BoardPorts, below)
inline constexpr const char *ShortOptions = ListsAllPorts ? "All\nUSB\nTRS\nDIN5" : "All\nUSB\nDIN5";
inline constexpr const char *LongOptions =
	ListsAllPorts ? "All Ports\nUSB only\nTRS only\nDIN5 only" : "All Ports\nUSB only\nDIN5 only";

// The port's item, or 0 if it isn't listed
constexpr uint16_t find_item(uint8_t port) {
	for (uint16_t i = 0; i < Midi::BoardPorts.size(); i++) {
		if (Midi::BoardPorts[i] == port)
			return i + 1;
	}
	return 0;
}

// Is the port in the dropdowns?
constexpr bool lists(uint8_t port) {
	if constexpr (ListsAllPorts)
		return port < Midi::NumPorts;
	else
		return find_item(port) != 0;
}

// A listed port's item
constexpr uint16_t item(uint8_t port) {
	if constexpr (ListsAllPorts)
		return port + 1;
	else
		return find_item(port);
}

// The item for a mapping's port (Midi::selected_port()): 0 (All) for all ports, or for a port that
// isn't listed
constexpr uint16_t item(std::optional<uint8_t> port) {
	if constexpr (ListsAllPorts)
		return port.has_value() ? *port + 1 : 0;
	else
		return port.has_value() ? find_item(*port) : 0;
}

// The port mask for an item
constexpr uint8_t port_mask(uint16_t item) {
	if constexpr (ListsAllPorts)
		return item == 0 ? Midi::AllPorts : Midi::only_port(uint8_t(item - 1));
	else
		return (item == 0 || item > Midi::BoardPorts.size()) ? Midi::AllPorts :
															   Midi::only_port(Midi::BoardPorts[item - 1]);
}

namespace detail
{
constexpr std::string_view port_name(Midi::Port port) {
	return port == Midi::USB ? "USB" : port == Midi::TRS ? "TRS" : "DIN5";
}

// The options are `all`, then each of the board's ports followed by `suffix`, one per line
constexpr bool lists_board_ports(std::string_view options, std::string_view all, std::string_view suffix) {
	if (!options.starts_with(all))
		return false;
	options.remove_prefix(all.size());

	for (auto port : Midi::BoardPorts) {
		for (auto part : {std::string_view{"\n"}, port_name(port), suffix}) {
			if (!options.starts_with(part))
				return false;
			options.remove_prefix(part.size());
		}
	}
	return options.empty();
}
} // namespace detail

static_assert(detail::lists_board_ports(ShortOptions, "All", ""));
static_assert(detail::lists_board_ports(LongOptions, "All Ports", " only"));

// Each port's item selects just that port
static_assert([] {
	for (auto port : Midi::BoardPorts) {
		if (!lists(port) || port_mask(item(port)) != Midi::only_port(port))
			return false;
	}
	return port_mask(0) == Midi::AllPorts;
}());

} // namespace MetaModule::MidiPortMenu
