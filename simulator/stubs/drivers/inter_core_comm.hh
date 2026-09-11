#pragma once
#include <cstdint>

namespace mdrivlib
{

enum class ICCRoleType { Initiator = 1, Responder = 2 };

template<ICCRoleType Role, typename MessageT, uint32_t Chan = 1>
class InterCoreComm {
	MessageT &shared_message_;

public:
	InterCoreComm(MessageT &shared_message)
		: shared_message_{shared_message} {
	}

	[[nodiscard]] bool send_message(const MessageT &msg) {
		shared_message_ = msg;
		return true;
	}

	[[nodiscard]] MessageT get_new_message() {
		return MessageT{};
	}
};

} // namespace mdrivlib
