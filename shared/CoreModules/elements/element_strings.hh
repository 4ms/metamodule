#pragma once
#include <string>

// Blindly replace extended chars with an underscore
// TODO: add more unicode characters to fonts used by the GUI
inline void remove_extended_chars(std::string &name) {
	for (auto &c : name) {
		if (c < 0)
			c = '_';
	}
}
