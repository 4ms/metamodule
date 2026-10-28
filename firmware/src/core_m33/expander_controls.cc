#include "expander_controls.hh"
#include <cstdio>

namespace MetaModule
{

namespace
{
constexpr uint8_t TCA9555_InputPort0 = 0x00;

constexpr const char *ExpanderNames[] = {"U1210", "U1211", "U1213", "U1209"};

bool is_low(uint16_t reading, Controls::ExpBit b) {
	return (reading & (1 << b.bit)) == 0;
}
} // namespace

void ExpanderControls::start() {
	for (auto &bus : buses) {
		for (auto exp : bus.exps) {
			if (!bus.i2c.probe(Controls::Expanders[exp].chip.addr << 1))
				printf("M33: control expander %s (0x%02x) not found\n",
					   ExpanderNames[exp],
					   Controls::Expanders[exp].chip.addr);
		}
		// The probes are blocking: from here on, update() uses the interrupt-driven reads
		bus.i2c.enable_IT(bus.conf.priority1, bus.conf.priority2);
	}
	started = true;
}

void ExpanderControls::update() {
	if (!started)
		return;

	if (++frame_ctr < TickFrames)
		return;
	frame_ctr = 0;

	for (auto &bus : buses)
		step(bus);
}

void ExpanderControls::step(Bus &bus) {
	if (bus.stopped.load(std::memory_order_acquire))
		return;

	if (bus.in_flight) {
		if (!bus.i2c.is_ready()) {
			if (++bus.ticks_in_flight >= TimeoutTicks)
				stop(bus);
			return;
		}

		bus.in_flight = false;
		if (bus.i2c.had_error()) {
			if (++bus.errors_in_a_row >= ErrorsBeforeReset) {
				stop(bus);
				return;
			}
		} else {
			bus.errors_in_a_row = 0;
			decode(bus.exps[bus.cur], (bus.rx[1] << 8) | bus.rx[0]);
		}
	}

	bus.cur = bus.cur ? 0 : 1;
	auto addr = Controls::Expanders[bus.exps[bus.cur]].chip.addr << 1;
	if (bus.i2c.mem_read_IT(addr, TCA9555_InputPort0, I2C_MEMADD_SIZE_8BIT, bus.rx.data(), bus.rx.size()) ==
		mdrivlib::I2CPeriph::I2C_NO_ERR)
	{
		bus.in_flight = true;
		bus.ticks_in_flight = 0;
	} else if (++bus.errors_in_a_row >= ErrorsBeforeReset) {
		stop(bus);
	}
}

void ExpanderControls::stop(Bus &bus) {
	bus.in_flight = false;
	bus.stopped.store(true, std::memory_order_release);
}

void ExpanderControls::process() {
	for (auto &bus : buses) {
		if (!bus.stopped.load(std::memory_order_acquire))
			continue;

		printf("M33: control expanders %s/%s: I2C errors, resetting the bus\n",
			   ExpanderNames[bus.exps[0]],
			   ExpanderNames[bus.exps[1]]);
		bus.i2c.clear_bus(bus.conf);
		bus.i2c.reset(bus.conf);
		bus.i2c.enable_IT(bus.conf.priority1, bus.conf.priority2);
		bus.errors_in_a_row = 0;
		bus.stopped.store(false, std::memory_order_release);
	}
}

void ExpanderControls::decode(unsigned exp, uint16_t reading) {
	readings[exp] = reading;

	for (unsigned i = 0; i < NumEncoders; i++) {
		auto const &enc = Controls::Encoders[i];

		// An encoder's A and B are always on the same expander
		if (enc.a.exp == exp) {
			encoders[i].update(is_low(reading, enc.a), is_low(reading, enc.b));
			enc_positions[i] = enc_positions[i] + encoders[i].read_position();
		}

		if (enc.but.exp == exp)
			enc_buttons[i].register_state(is_low(reading, enc.but));
	}

	for (unsigned i = 0; i < NumButtons; i++) {
		if (Controls::Buttons[i].exp == exp)
			buttons[i].register_state(is_low(reading, Controls::Buttons[i]));
	}
}

} // namespace MetaModule
