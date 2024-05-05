#include "debounced_digins.h"
#include "dig_inouts.hh"
#include "drivers/pin_change.hh"
#include "drivers/timekeeper.hh"
#include "trigout.h"
#include "util/debouncer.hh"

namespace
{
std::array<Debouncer<0x0001, 0xFFFE, 0xFFFF>, NUM_DEBOUNCED_DIGINS> debouncers;
mdrivlib::Timekeeper digintmr;

struct PingPinChangeConf : mdrivlib::DefaultPinChangeConf {
	static constexpr uint32_t pin = DigIO::PingJack::PinNum_v;
	static constexpr mdrivlib::GPIO port = DigIO::PingJack::Gpio_v;
	static constexpr bool on_rising_edge = true;
	static constexpr uint32_t priority1 = 0;
	static constexpr uint32_t priority2 = 0;
};
mdrivlib::PinChangeInt<PingPinChangeConf> ping_int;
} // namespace

extern volatile uint32_t pingtmr;
extern volatile uint32_t ping_irq_timestamp;
extern volatile uint8_t using_tap_clock;

void init_debouncer() {
	HAL_StatusTypeDef err;

	for (auto &d : debouncers)
		d.reset();

	mdrivlib::TimekeeperConfig conf{
		.TIMx = TIM7,
		.period_ns = 1'000'000'000 / 33000,
		.priority1 = 2,
		.priority2 = 2,
	};
	digintmr.init(conf, [] {
		debouncers[PING_BUTTON].register_state(DigIO::PingBut::read() ? 1 : 0);
		debouncers[CYCLE_BUTTON].register_state(DigIO::CycleBut::read() ? 1 : 0);
		debouncers[TRIGGER_JACK].register_state(DigIO::TrigJack::read() ? 1 : 0);
		debouncers[CYCLE_JACK].register_state(DigIO::CycleJack::read() ? 1 : 0);
	});
	digintmr.start();

	ping_int.init([] {
		clockbus_on();
		ping_irq_timestamp = pingtmr;
		pingtmr = 0;
		using_tap_clock = 0;
	});
	ping_int.start();
}
// Ping jitter: with reading in the debouncer task:
//f746: @33000Hz clockbus fires 50-75us after incoming ping trigger. Jitter = +25us, Latency = 50us
//f423: @33000Hz clockbus fires 47-77us after incoming ping trigger. Jitter = +30us, Latency = 47us
//f423: @66000Hz clockbus fires 47-67us after incoming ping trigger. Jitter = +20us, Latency = 47us
// with using an EXTI:
//f423: clockbus fires 45-55us after incoming ping trigger. Jitter = +10us, Latency = 45us
//f746: clockbus fires 45-52us after incoming ping trigger. Jitter = +7us, Latency = 45us

bool is_pressed(DebouncedDiginList pin) {
	return debouncers[pin].is_pressed();
}

bool just_pressed(DebouncedDiginList pin) {
	return debouncers[pin].is_just_pressed();
}

bool just_released(DebouncedDiginList pin) {
	return debouncers[pin].is_just_released();
}
