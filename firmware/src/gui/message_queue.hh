#pragma once
#include <string>

namespace MetaModule
{
//TODO: make this thread-safe
struct MessageQueue {
	std::string message{""};

	size_t max_size = 1024;

	MessageQueue(size_t max_message_size)
		: max_size{max_message_size} {
		// Allocate once, and do not let message get bigger than Max
		message.reserve(max_size);
	}

	void set_message(const std::string_view m) {
		message = m.size() > max_size ? m.substr(0, max_size) : m;
	}

	void clear_message() {
		message.clear();
	}

	[[nodiscard]] std::string_view get_message() const {
		return message;
	}

	void append_message(const std::string_view m) {
		size_t available = max_size - message.length();
		message.append(m.size() <= available ? m : m.substr(0, available));
	}
};

} // namespace MetaModule
