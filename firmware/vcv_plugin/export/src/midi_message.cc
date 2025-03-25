#include "midi/midi_message.hh"
#include <cstdint>
#include <span>
#include <string>

namespace MetaModule::Midi
{

std::string toPrettyMultilineString(std::span<uint8_t, 3> bytes) {
	std::string s = "";

	MidiMessage msg(bytes[0], bytes[1], bytes[2]);
	auto channel = [b = bytes[0]] {
		uint8_t chan = (b & 0x0F) + 1;
		std::string channel = "Ch:" + std::to_string(chan);
		return channel;
	};

	if (msg.is_noteon()) {
		s = "Note On ";
		s += MidiMessage::note_name(bytes[1]);
		s += "\nV:" + std::to_string(bytes[2]);
		s += " " + channel();
	}

	else if (msg.is_noteoff())
	{
		s = "Note Off ";
		s += MidiMessage::note_name(bytes[1]);
		s += "\n" + channel();
	}

	else if (msg.is_command<MidiCommand::PolyKeyPressure>())
	{
		s = "Aft Note #";
		s += MidiMessage::note_name(bytes[1]);
		s += "\nV:" + std::to_string(bytes[2]);
		s += " " + channel();
	}

	else if (msg.is_command<MidiCommand::ControlChange>())
	{
		s = "CC#";
		s += std::to_string(bytes[1]);
		s += "\n = " + std::to_string(bytes[2]);
		s += " " + channel();
	}

	else if (msg.is_command<MidiCommand::ProgramChange>())
	{
		s = "PC#";
		s += std::to_string(bytes[1]);
		s += "\n" + channel();
	}

	else if (msg.is_command<MidiCommand::ChannelPressure>())
	{
		s = "Pressure:\n";
		s += "V:" + std::to_string(bytes[1]);
		s += " " + channel();
	}

	else if (msg.is_command<MidiCommand::PitchBend>())
	{
		s = "Pitch Bend:\n ";
		int32_t amt = (bytes[2] << 7) + bytes[1];
		s += std::to_string(amt - 8192);
		s += " " + channel();
	}

	else if (msg.is_system_realtime<MidiSystemRealTimeCommand::Start>())
	{
		s = "Start";
	}

	else if (msg.is_system_realtime<MidiSystemRealTimeCommand::Continue>())
	{
		s = "Continue";
	}

	else if (msg.is_system_realtime<MidiSystemRealTimeCommand::Stop>())
	{
		s = "Stop";
	}

	else
	{
		// s += std::to_string(bytes[0]) + " " + std::to_string(bytes[1]) + "\n" + std::to_string(bytes[2]);
	}

	return s;
}

std::string toPrettyString(std::span<uint8_t, 3> bytes) {
	std::string s = "";

	if ((bytes[0] & 0xF0) == 0x90) {
		// Convert note-off via vel=0 to a proper note-off
		if (bytes[2] == 0)
			bytes[0] &= 0xEF; // 0x9x => 0x8x
		else
			s = "Nte";
	}

	if ((bytes[0] & 0xF0) == 0x80) {
		s = "Off";
	}

	if ((bytes[0] & 0xF0) == 0xA0) {
		s = "Aft";
	}

	if ((bytes[0] & 0xF0) == 0xB0) {
		s = "CC";
	}

	if ((bytes[0] & 0xF0) == 0xC0) {
		s = "PC";
	}

	if ((bytes[0] & 0xF0) == 0xD0) {
		s = "Prs";
	}

	if ((bytes[0] & 0xF0) == 0xE0) {
		s = "Bnd";
	}

	// Handle "normal" commands
	if (s.length()) {
		uint8_t chan = bytes[0] & 0x0F;
		s += std::to_string(bytes[1]);

		// Ignore velocity for note-off and channel pressure
		if ((bytes[0] & 0xF0) != 0x80 && (bytes[0] & 0xF0) != 0xD0) {
			s += " ";
			s += std::to_string(bytes[2]);
		}

		s += " Ch" + std::to_string(chan);
	} else {
		if (bytes[0] == 0xFA) {
			s = "Start";
		}
		if (bytes[0] == 0xFB) {
			s = "Continue";
		}
		if (bytes[0] == 0xFC) {
			s = "Stop";
		}
	}

	return s;
}
} // namespace MetaModule::Midi
