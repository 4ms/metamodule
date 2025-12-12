#pragma once
#include <array>
#include <cstdint>
#include <span>
#include <string>

// #define MIDIDEBUG
#if defined(MIDIDEBUG)
#include "pr_dbg.hh"
#endif

// Specifications from
// https://midi.org/midi-1-0-core-specifications

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
	uint8_t channel : 4;
	MidiCommand command : 4;

	constexpr static MidiStatusByte make(uint8_t raw) {
		return MidiStatusByte{
			.channel = uint8_t(raw & 0x0F),
			.command = MidiCommand(raw >> 4),
		};
	}

	constexpr operator uint8_t() const {
		return (uint8_t)command << 4 | channel;
	}
};

struct MidiDataBytes {
	uint8_t byte[2];

	constexpr operator uint16_t() const {
		return ((uint16_t)byte[0] << 8) | byte[1];
	}
};

enum MidiSystemCommonCommand : uint8_t {
	TimeCodeQuarterFrame = 0xF1, // packet = 2 bytes
	SongPositionPtr = 0xF2,		 // packet = 3 byte
	SongSelect = 0xF3,			 // packet = 2 bytes
	// 0xF4 undefined
	// 0xF5 undefined
	TuneRequest = 0xF6,	 // packet = 1 byte
	EndExclusive = 0xF7, // packet = 1 byte
};

enum MidiSystemRealTimeCommand : uint8_t {
	// packet = 1 byte
	TimingClock = 0xF8,
	// 0xF9 undefined
	Start = 0xFA,
	Continue = 0xFB,
	Stop = 0xFC,
	// 0xFD undefined
	ActiveSending = 0xFE,
	SystemReset = 0xFF,
};

enum MidiSystemExclusiveCommand : uint8_t {
	SysEx = 0xF0,
};

struct UsbCableCodeByte {
	uint8_t cin : 4 = 0;	   // low nibble
	uint8_t cable_num : 4 = 0; // high nibble

	constexpr UsbCableCodeByte(uint8_t raw)
		: cin(raw & 0x0F)
		, cable_num(raw >> 4) {
	}

	constexpr static UsbCableCodeByte make(uint8_t raw) {
		return raw;
	}

	constexpr operator uint8_t() const {
		return (uint8_t)cable_num << 4 | cin;
	}

	constexpr static uint8_t cin_from_status_byte(uint8_t status) {
		// Deduce the CIN code based on the status byte
		// We cannot deduce SysEx payload size here: that must be set already, so we never set CIN to 0x6 or 0x7 here.
		return (status >= 0x80 && status < 0xF0)						? (status >> 4) : //voice messages
			   status == SysEx					  						? 0x4 :
			   (status == TimeCodeQuarterFrame || status == SongSelect) ? 0x2 :
			   status == SongPositionPtr					  			? 0x3 :
			   status == TuneRequest || status == EndExclusive   		? 0x5 : 
			   status >= 0xF8					  						? 0xF : // single byte System Realtime
																		  0x4;  // unknown: default to sysex payload
	}
};
static_assert(UsbCableCodeByte::make(0x1B).cable_num == 1);
static_assert(UsbCableCodeByte::make(0x1B).cin == 0xB);

struct MidiMessage {
	MidiStatusByte status{0, MidiCommand::None};
	MidiDataBytes data{0, 0};
	UsbCableCodeByte usb_hdr{0};

	constexpr MidiMessage() = default;

	constexpr MidiMessage(uint8_t status_byte, uint8_t data_byte0 = 0, uint8_t data_byte1 = 0)
		: status{MidiStatusByte::make(status_byte)}
		, data{data_byte0, data_byte1}
		, usb_hdr{UsbCableCodeByte::cin_from_status_byte(status_byte)} {
	}

	constexpr MidiMessage(uint8_t usb_header, uint8_t status_byte, uint8_t data_byte0, uint8_t data_byte1)
		: status{MidiStatusByte::make(status_byte)}
		, data{data_byte0, data_byte1}
		, usb_hdr{usb_header} {
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

	bool is_noteon() const {
		return is_command<MidiCommand::NoteOn>() && velocity() > 0;
	}

	bool is_noteoff() const {
		return is_command<MidiCommand::NoteOff>() || (is_command<MidiCommand::NoteOn>() && velocity() == 0);
	}

	uint32_t raw() const {
		return (usb_hdr << 24) | (status << 16) | data;
	}

	// Fill given `bytes` array with a valid usb midi packet
	void make_usb_msg(std::array<uint8_t, 4> &bytes) {
		// If usb CIN field is not set, then deduce it from the status byte
		if (usb_hdr.cin == 0) {
			usb_hdr.cin = UsbCableCodeByte::cin_from_status_byte(status);
		}

		bytes[0] = usb_hdr;
		bytes[1] = status;
		bytes[2] = data.byte[0];
		bytes[3] = data.byte[1];
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

	uint8_t pcval() const {
		return data.byte[1];
	}

	// -8192 .. 8191
	int16_t bend() const {
		return ((int16_t)data.byte[0] | ((int16_t)data.byte[1] << 7)) - 8192;
	}

	unsigned message_size() const {
		if (is_timing_transport()) {
			return 1;
		} else if (status.command == MidiCommand::ChannelPressure) {
			return 2;
		} else if (usb_hdr.cin == 0x5) {
			return 1;
		} else if (usb_hdr.cin == 0x6) {
			return 2;
		} else {
			return 3;
		}
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

	static std::string note_name(uint8_t midi_val) {
		constexpr std::array<std::string_view, 12> nts = {
			"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
		// "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"};

		// int oct = int(b) / 12 - 6; // This makes it consistant with a MIDI loop (Rack on computer->BSP->CV outputs -> CV_MIDI module
		int oct = int(midi_val) / 12 - 2; // This makes it consistant with MetaModule MIDI

		return std::string(nts[midi_val % 12]) + std::to_string(oct);
	}
};

static_assert(MidiMessage(0x3B, 0xB0, 0x10, 0x20).usb_hdr.cin == 0xB);
static_assert(MidiMessage(0x3B, 0xB0, 0x10, 0x20).usb_hdr.cable_num == 0x3);
