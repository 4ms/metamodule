#pragma once
#include <cstdint>
#include <span>

// #define MIDIDEBUG
#if defined(MIDIDEBUG)
#include "pr_dbg.hh"
#endif

// Specifications from
// https://www.midi.org/specifications/midi1-specifications/m1-v4-2-1-midi-1-0-detailed-specification-96-1-4

enum class MidiCommand : uint8_t {
	None = 0,
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
	MidiStatusByte status{MidiCommand::None, 0};
	MidiDataBytes data{0, 0};

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

	bool is_timing_transport() const {
		return status == TimingClock || status == Start || status == Stop || status == Continue;
	}

	bool is_sysex() const {
		return status == SysEx;
	}

	bool has_sysex_end() const {
		return status == EndExclusive || data.byte[0] == EndExclusive || data.byte[1] == EndExclusive;
	}

	bool is_noteoff() const {
		return is_command<MidiCommand::NoteOff>() || (is_command<MidiCommand::NoteOn>() && velocity() == 0);
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

	// -8192 .. 8191
	int16_t bend() const {
		return ((int16_t)data.byte[0] | ((int16_t)data.byte[1] << 7)) - 8192;
	}

	static void print(MidiMessage msg) {
#if defined(MIDIDEBUG)
		using enum MidiCommand;
		if (msg.is_command<NoteOn>()) {
			pr_dbg("Note: %d Vel: %d\n", msg.note(), msg.velocity());

		} else if (msg.is_command<NoteOff>()) {
			pr_dbg("Note: %d OFF\n", msg.note());

		} else if (msg.is_command<PolyKeyPressure>()) {
			pr_dbg("Poly Key Pressure: %d %d\n", msg.note(), msg.aftertouch());

		} else if (msg.is_command<ControlChange>()) {
			pr_dbg("CC: #%d = %d\n", msg.data.byte[0], msg.data.byte[1]);

		} else if (msg.is_command<ProgramChange>()) {
			pr_dbg("PC: #%d\n", msg.data.byte[0]);

		} else if (msg.is_command<ChannelPressure>()) {
			pr_dbg("CP: #%d\n", msg.chan_pressure());

		} else if (msg.is_command<PitchBend>()) {
			pr_dbg("Bend: #%d\n", msg.bend());

		} else if (msg.is_system_realtime<TimingClock>()) {
			pr_dbg("Clk\n");

		} else if (msg.is_system_realtime<Start>()) {
			pr_dbg("Start\n");

		} else if (msg.is_system_realtime<Stop>()) {
			pr_dbg("Stop\n");

		} else if (msg.is_system_realtime<Continue>()) {
			pr_dbg("Continue\n");

		} else if (msg.is_sysex()) {
			pr_dbg("SYSEX: 0x%02x%02x\n", msg.data.byte[0], msg.data.byte[1]);

		} else {
			pr_dbg("Raw: %06x\n", (unsigned)msg.raw());
		}
#endif
	}

	static void dump_raw(std::span<uint8_t> buffer) {
#if defined(MIDIDEBUG)
		pr_dbg("%d bytes ", buffer.size());
		for (auto byte : buffer)
			pr_dbg("0x%02x ", byte);
		pr_dbg("\n");
#endif
	}

	void print() const {
		MidiMessage::print(*this);
	}
};
