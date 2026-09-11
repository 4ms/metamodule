#pragma once
#include "midi/midi_message.hh"
#include <array>
#include <cstdint>
#include <optional>

namespace MetaModule::Midi
{

// Turns a serial MIDI byte stream (a DIN or TRS jack) into MidiMessages.
//
// Differs from USB-MIDI parser because this one has to handle:
//   - Running status: a data byte can arrive with no status byte, reusing the
//     status of the previous channel-voice message.
//   - System Real Time (0xF8..0xFF): a single byte that may appear inside
//     another message, including inside a SysEx, without interrupting it.
//     TODO: verify against the spec
//   - SysEx of any length, which USB-MIDI carries as groups of three bytes with
//     the Code Index Number saying how the last group ends.
class StreamParser {
public:
	std::optional<MidiMessage> parse(uint8_t byte) {
		// System Real Time never disturbs a message in progress, not even SysEx
		if (byte >= TimingClock)
			return MidiMessage{byte};

		if (byte & 0x80)
			return parse_status(byte);

		return parse_data(byte);
	}

	void reset() {
		status = 0;
		running_status = 0;
		expected = 0;
		count = 0;
		in_sysex = false;
		sysex_count = 0;
	}

private:
	uint8_t status = 0;			// status of the message being assembled
	uint8_t running_status = 0; // channel-voice status a bare data byte reuses
	uint8_t expected = 0;		// data bytes this message needs
	uint8_t count = 0;			// data bytes collected so far
	std::array<uint8_t, 2> data{};

	bool in_sysex = false;
	uint8_t sysex_count = 0;
	std::array<uint8_t, 3> sysex{};

	std::optional<MidiMessage> parse_status(uint8_t byte) {
		if (byte == SysEx) {
			in_sysex = true;
			sysex_count = 0;
			sysex[sysex_count++] = byte;
			status = 0;
			running_status = 0;
			return std::nullopt;
		}

		if (byte == EndExclusive) {
			if (!in_sysex)
				return std::nullopt; // stray F7

			in_sysex = false;
			sysex[sysex_count++] = byte;
			return end_sysex();
		}

		// Any other status byte abandons an unterminated SysEx and starts fresh
		in_sysex = false;
		count = 0;
		status = byte;
		expected = data_bytes(byte);

		// Running status applies to channel voice only: a System Common message
		// cancels it
		running_status = (byte < SysEx) ? byte : 0;

		if (expected == 0) {
			// Tune Request, or the undefined F4/F5
			status = 0;
			return MidiMessage{byte};
		}

		return std::nullopt;
	}

	std::optional<MidiMessage> parse_data(uint8_t byte) {
		if (in_sysex) {
			sysex[sysex_count++] = byte;

			if (sysex_count < sysex.size())
				return std::nullopt;

			sysex_count = 0;
			// CIN 0x4: SysEx starts or continues
			return MidiMessage{0x04, sysex[0], sysex[1], sysex[2]};
		}

		if (status == 0) {
			// No status byte pending, so this is running status
			if (running_status == 0)
				return std::nullopt; // data with no status ever seen: drop it

			status = running_status;
			expected = data_bytes(status);
			count = 0;
		}

		data[count++] = byte;

		if (count < expected)
			return std::nullopt;

		const auto msg = MidiMessage{status, data[0], expected > 1 ? data[1] : uint8_t(0)};

		count = 0;
		// Cleared so the next data byte falls through to running_status, which
		// is only set for channel-voice messages
		status = 0;

		return msg;
	}

	std::optional<MidiMessage> end_sysex() {
		// The CIN says how many of the three bytes are payload in the last group
		const uint8_t cin = sysex_count == 1 ? 0x5 : sysex_count == 2 ? 0x6 : 0x7;

		const auto msg = MidiMessage{
			cin, sysex[0], sysex_count > 1 ? sysex[1] : uint8_t(0), sysex_count > 2 ? sysex[2] : uint8_t(0)};
		sysex_count = 0;

		return msg;
	}

	static constexpr uint8_t data_bytes(uint8_t status) {
		switch (status & 0xF0) {
			case 0x80: // Note Off
			case 0x90: // Note On
			case 0xA0: // Poly Key Pressure
			case 0xB0: // Control Change
			case 0xE0: // Pitch Bend
				return 2;

			case 0xC0: // Program Change
			case 0xD0: // Channel Pressure
				return 1;

			default:
				break;
		}

		switch (status) {
			case SongPositionPtr:
				return 2;

			case TimeCodeQuarterFrame:
			case SongSelect:
				return 1;

			default:
				return 0;
		}
	}
};

} // namespace MetaModule::Midi
