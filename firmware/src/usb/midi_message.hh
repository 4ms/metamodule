#pragma once
#include <array>
#include <bit>
#include <cstdint>

// From https://www.midi.org/specifications/midi1-specifications/m1-v4-2-1-midi-1-0-detailed-specification-96-1-4
namespace Midi
{
enum MidiCommand {
	NoteOff = 0x8,
	NoteOn = 0x9,
	PolyKeyPressue = 0xA,
	ControlChange = 0xB,
	ProgramChange = 0xC,
	ChannelPressure = 0xD,
	PitchBend = 0xE,
	Sys = 0xF,
};

// TODO: check std::variant overhead instead of union
struct MidiStatusByte {
	union {
		struct {
			uint8_t channel : 4;
			MidiCommand command : 4;
		};
		uint8_t raw;
	};

	MidiStatusByte() = default;
	MidiStatusByte(uint8_t val)
		: raw{val} {
	}
};

struct MidiDataBytes {
	uint8_t byte[2];
};

enum MidiSystemCommonCommand : uint8_t {
	TimeCodeQuarterFrame = 0xF1,
	SongPositionPtr = 0xF2,
	SongSelect = 0xF3,
	TuneRequest = 0xF6,
	EndExclusive = 0xF7,
};

enum MidiSystemRealTimeCommand : uint8_t {
	TimingClock = 0xF8,
	Start = 0xFA,
	Continue = 0xFB,
	Stop = 0xFC,
	ActiveSending = 0xFE,
	SystemReset = 0xFF,
};

enum MidiSystemExclusiveCommand : uint8_t {
	SysEx = 0xF0,
};

struct MidiMessage {
	MidiStatusByte status;
	MidiDataBytes data;

	MidiMessage() = default;

	MidiMessage(uint8_t status_byte, uint8_t data_byte0, uint8_t data_byte1)
		: status{status_byte}
		, data{data_byte0, data_byte1} {
	}

	template<MidiCommand cmd>
	bool is_command() const {
		return (status.command == cmd);
	}

	template<MidiSystemCommonCommand cmd>
	bool is_system_common() const {
		return status.raw == cmd;
	}

	template<MidiSystemRealTimeCommand cmd>
	bool is_system_realtime() const {
		return status.raw == cmd;
	}

	bool is_sysex() const {
		return status.raw == SysEx;
	}

	uint32_t raw_data() const {
		return (status.raw << 16) | (data.byte[0] << 8) | data.byte[1];
	}
};
} // namespace Midi
