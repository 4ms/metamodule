#pragma once
#include <string>

namespace MetaModule
{
struct UiAudioMailbox {
	std::string message{""};

	static constexpr size_t MaxMessageSize = 1024;

	UiAudioMailbox() {
		// Allocate once, and do not let message get bigger than Max
		message.reserve(MaxMessageSize);
	}

	void set_message(const std::string_view m) {
		message = m.size() > MaxMessageSize ? m.substr(0, MaxMessageSize) : m;
	}

	void clear_message() {
		message.clear();
	}

	[[nodiscard]] std::string_view get_message() const {
		return message;
	}

	void append_message(const std::string_view m) {
		size_t available = MaxMessageSize - message.length();
		message.append(m.size() <= available ? m : m.substr(0, available));
	}
};

} // namespace MetaModule
