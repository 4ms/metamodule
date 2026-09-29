#pragma once
#include "gui/notify/queue.hh"
#include "params/metaparams.hh"

namespace MetaModule
{

// Notifies the user on jack sense faults (I2C bus errors)
class JackSenseMonitor {
	uint8_t prev = 0;

public:
	void update(uint8_t cur, NotificationQueue &notify_queue) {
		if (cur == prev)
			return;

		const auto appeared = cur & ~prev;
		const auto cleared = prev & ~cur;
		prev = cur;

		if (appeared & JackSenseFault::MainFailed) {
			notify_queue.put({"Jack detection failed: all jacks are treated as patched. Check expander cables and "
							  "restart.",
							  Notification::Priority::Error,
							  6000});

		} else if (appeared & JackSenseFault::ExtLost) {
			notify_queue.put({"Lost connection to MetaAIO: its jacks are treated as patched. Check the cable and "
							  "restart.",
							  Notification::Priority::Error,
							  6000});
		}

		if (cleared & JackSenseFault::MainFailed)
			notify_queue.put({"Jack detection recovered", Notification::Priority::Info, 2000});
	}
};

} // namespace MetaModule
