#pragma once
#include <cstdint>

#define MIDIDEBUG
#if defined(MIDIDEBUG)
#include "printf.h"
#endif

// Specifications from
// https://www.midi.org/specifications/midi1-specifications/m1-v4-2-1-midi-1-0-detailed-specification-96-1-4

enum class MidiCommand : uint8_t {
	NoteOff = 0x8,
	NoteOn = 0x9,
	PolyKeyPressure = 0xA,
	ControlChange = 0xB,
	ProgramChange = 0xC,
	ChannelPressure = 0xD,
	PitchBend = 0xE,
	Sys = 0xF,
};

struct MidiStatusByte {
	MidiCommand command : 4;
	uint8_t channel : 4;

	static MidiStatusByte make(uint8_t raw) {
		return MidiStatusByte{
			.command = MidiCommand(raw >> 4),
			.channel = uint8_t(raw & 0x0F),
		};
	}

	operator uint8_t() const {
		return (uint8_t)command << 4 | channel;
	}
};

struct MidiDataBytes {
	uint8_t byte[2];

	operator uint16_t() const {
		return ((uint16_t)byte[0] << 8) | byte[1];
	}
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

	MidiMessage(uint8_t status_byte, uint8_t data_byte0 = 0, uint8_t data_byte1 = 0)
		: status{MidiStatusByte::make(status_byte)}
		, data{data_byte0, data_byte1} {
	}

	template<MidiCommand cmd>
	bool is_command() const {
		return (status.command == cmd);
	}

	template<MidiSystemCommonCommand cmd>
	bool is_system_common() const {
		return status == cmd;
	}

	template<MidiSystemRealTimeCommand cmd>
	bool is_system_realtime() const {
		return status == cmd;
	}

	bool is_sysex() const {
		return status == SysEx;
	}

	uint32_t raw() const {
		return (status << 16) | data;
	}

	uint8_t note() const {
		return data.byte[0];
	}

	uint8_t ccnum() const {
		return data.byte[0];
	}

	uint8_t velocity() const {
		return data.byte[1];
	}

	uint8_t aftertouch() const {
		return data.byte[1];
	}

	uint8_t chan_pressure() const {
		return data.byte[0];
	}

	uint8_t ccval() const {
		return data.byte[1];
	}

	int16_t bend() const {
		return ((int16_t)data.byte[0] | ((int16_t)data.byte[1] << 7)) - 8192;
	}

	static void print(MidiMessage msg) {
#if defined(MIDIDEBUG)
		using enum MidiCommand;
		if (msg.is_command<NoteOn>()) {
			printf_("Note: %d Vel: %d\n", msg.note(), msg.velocity());

		} else if (msg.is_command<NoteOff>()) {
			printf_("Note: %d OFF\n", msg.note());

		} else if (msg.is_command<PolyKeyPressure>()) {
			printf_("Poly Key Pressure: %d %d\n", msg.note(), msg.aftertouch());

		} else if (msg.is_command<ControlChange>()) {
			printf_("CC: #%d = %d\n", msg.data.byte[0], msg.data.byte[1]);

		} else if (msg.is_command<ProgramChange>()) {
			printf_("PC: #%d\n", msg.data.byte[0]);

		} else if (msg.is_command<ChannelPressure>()) {
			printf_("CP: #%d\n", msg.chan_pressure());

		} else if (msg.is_command<PitchBend>()) {
			printf_("Bend: #%d\n", msg.bend());

		} else if (msg.is_system_realtime<TimingClock>()) {
			// printf_("Clk\n");

		} else if (msg.is_sysex()) {
			printf_("SYSEX: 0x%02x%02x\n", msg.data.byte[0], msg.data.byte[1]);

		} else if (msg.raw()) {
			printf_("Raw: %06x\n", msg.raw());
		}
#endif
	}

	void print() const {
		MidiMessage::print(*this);
	}
};
