#include <cstdint>
#include <span>
#include <string>

namespace MetaModule::Midi
{

std::string toPrettyString(std::span<uint8_t, 3> bytes) {
	std::string s = "";

	if ((bytes[0] & 0xF0) == 0x90) {
		s = "Note";
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
		s = "Pressure";
	}

	if ((bytes[0] & 0xF0) == 0xE0) {
		s = "Bend";
	}

	if (s.length()) {
		uint8_t chan = bytes[0] & 0x0F;
		s += std::to_string(bytes[1]);
		s += " ";
		s += std::to_string(bytes[2]);
		s += " ch" + std::to_string(chan);
	}

	return s;
}
} // namespace MetaModule::Midi
