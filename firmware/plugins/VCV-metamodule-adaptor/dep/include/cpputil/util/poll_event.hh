#pragma once

template<typename TimeT = long int>
struct PollEvent {
	PollEvent(TimeT period)
		: period{period} {
	}

	void poll(TimeT now, auto action) {
		bool expired = false;

		// Handle overflow
		if (now < last_poll) {
			if (now >= TimeT(last_poll + period)) {
				expired = true;
			}
		} else if ((now - last_poll) >= period) {
			expired = true;
		}

		if (expired) {
			last_poll = now;
			action();
		}
	}

private:
	TimeT period;
	TimeT last_poll{};
};
