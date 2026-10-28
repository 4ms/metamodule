#pragma once
#include "conf/board_codec_conf.hh"
#include "conf/control_expander_conf.hh"
#include "conf/fusb30x_conf.hh"
#include "conf/i2c_conf.hh"
#include "conf/jack_sense_conf.hh"
#include "conf/led_driver_conf.hh"
#include "core_intercom/shared_i2c_lock.hh"
#include "drivers/i2c.hh"
#include <array>
#include <cstdio>

// Pro p1 bring-up check: probes every address on each I2C bus, and prints which of the devices that
// should be there answered (see conf/README.md), and anything else that did. For the TCA9555s that
// answer, it reads their inputs too.
//
// Not for the test carrier: its wiring is different (PB4, which is I2C2 here, is its VBUS enable).

namespace MetaModule
{

namespace I2CScan
{

struct Device {
	uint8_t addr; // 7-bit
	const char *name;
	bool is_tca9555 = false;
};

struct Bus {
	const char *name;
	const mdrivlib::I2CConfig &conf;
	std::array<Device, 3> devices; // addr = 0: none
};

// TCA9555 input port registers (port 0, then port 1)
constexpr uint8_t TCA9555_InputPort0 = 0x00;

inline void read_tca9555_inputs(mdrivlib::I2CPeriph &i2c, uint8_t addr) {
	std::array<uint8_t, 2> inputs{};
	if (i2c.mem_read(addr << 1, TCA9555_InputPort0, 1, inputs.data(), inputs.size()) == mdrivlib::I2CPeriph::I2C_NO_ERR)
		printf(" (inputs P1:P0 = 0x%02x%02x)", inputs[1], inputs[0]);
	else
		printf(" (reading inputs FAILED)");
}

inline void scan_bus(mdrivlib::I2CPeriph &i2c, Bus const &bus) {
	printf("%s:", bus.name);

	if (bus.conf.I2Cx->ISR & I2C_ISR_BUSY) {
		printf(" bus is BUSY (SDA or SCL held low?)\n");
		return;
	}

	std::array<bool, 128> found{};
	for (unsigned addr = 0x08; addr < 0x78; addr++)
		found[addr] = i2c.probe(addr << 1);

	for (auto const &dev : bus.devices) {
		if (dev.addr == 0)
			continue;
		printf(" 0x%02x %s %s", dev.addr, dev.name, found[dev.addr] ? "OK" : "MISSING");
		if (found[dev.addr] && dev.is_tca9555)
			read_tca9555_inputs(i2c, dev.addr);
		printf(",");
		found[dev.addr] = false;
	}

	printf(" others:");
	bool any_others = false;
	for (unsigned addr = 0; addr < found.size(); addr++) {
		if (found[addr]) {
			printf(" 0x%02x", addr);
			any_others = true;
		}
	}
	printf("%s\n", any_others ? "" : " none");
}

} // namespace I2CScan

// I2C4 is shared with the M33, and its peripheral is the codec's, so call this after the codec is
// initialized (so it's out of reset, and answers).
inline void scan_i2c_buses() {
	using namespace I2CScan;
	using Controls::Expanders;
	using ButtonLEDs::LedChipAddr7bit;

	printf("I2C scan:\n");

	{
		mdrivlib::I2CPeriph i2c{controls_a_i2c_conf};
		scan_bus(i2c,
				 {"  I2C2 (PB5/PB4, needs the SDA/SCL swap bodge)",
				  controls_a_i2c_conf,
				  {{{Expanders[0].chip.addr, "U1210 TCA9555", true}, {Expanders[1].chip.addr, "U1211 TCA9555", true}}}});
	}

	{
		mdrivlib::I2CPeriph i2c{controls_b_i2c_conf};
		scan_bus(i2c,
				 {"  I2C3 (PG2/PG1)",
				  controls_b_i2c_conf,
				  {{{Expanders[2].chip.addr, "U1213 TCA9555", true}, {Expanders[3].chip.addr, "U1209 TCA9555", true}}}});
	}

	{
		SharedI2CGuard lock;
		scan_bus(Hardware::i2c,
				 {"  I2C4 (PD10/PD11)",
				  codec_jack_i2c_conf,
				  {{{JackSense::gpio_expander_conf.addr, "U1212 TCA9555 (jack sense)", true},
					{FUSBDevAddr >> 1, "FUSB302"},
					{0x44, "PCM3168"}}}});
	}

	{
		// The LP5018s also answer their broadcast address, 0x3C
		mdrivlib::I2CPeriph i2c{led_i2c_conf};
		scan_bus(i2c,
				 {"  I2C6 (PG5/PG6)",
				  led_i2c_conf,
				  {{{LedChipAddr7bit[0], "U5 LP5018"}, {LedChipAddr7bit[1], "U8 LP5018"}, {0x3C, "LP5018 broadcast"}}}});
	}
}

} // namespace MetaModule
