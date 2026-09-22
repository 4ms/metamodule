#pragma once
#include "CoreModules/hub/button_expander_defs.hh"
#include "conf/button_expander_conf.hh"
#include "drivers/gpio_expander.hh"
#include "drivers/i2c.hh"
#include "expander_bus.hh"
#include "pr_dbg.hh"
#include "stm32mp1xx_hal.h"
#include <algorithm>
#include <array>
#include <atomic>
#include <cstdint>

namespace MetaModule
{

// Button Expanders on the expander I2C bus
//
// Reads one Button Expander per turn
class ButtonExpanderManager {
	using GPIOExpander = mdrivlib::GPIOExpander;

public:
	explicit ButtonExpanderManager(mdrivlib::I2CPeriph &i2c)
		: expanders{{
			  {false, {i2c, Expander::Button::gpio_chip_conf}},
			  {false, {i2c, Expander::Button::gpio_chip_conf}},
			  {false, {i2c, Expander::Button::gpio_chip_conf}},
			  {false, {i2c, Expander::Button::gpio_chip_conf}},
		  }} {
	}

	// Blocking: probes every address we don't already have
	unsigned auto_scan_idx = 0;
	void scan() {
		for (auto i = 0u; i < expanders.size(); i++)
			auto_scan(i);
	}

	void auto_scan(unsigned idx) {
		auto &expander = expanders[idx];
		const auto addr = addresses[idx];

		if (expander.found)
			return;

		expander.driver.set_address(addr);

		if (expander.driver.is_present()) {
			expander.found = true;
			expander.driver.start();

			num_errors[idx] = 0;
			num_error_retries[idx] = 0;

			pr_info("Button Expander found at addr 0x%x\n", addr);

		} else if (first_scan) {
			// Only on the first pass: after that this runs every couple of
			// seconds and would just repeat itself
			pr_dbg("Button Expander not found at addr 0x%x\n", addr);
		}

		first_scan = false;
	}

	BusRequest update(XferResult prev) {
		BusRequest req{};

		if (prev == XferResult::Ok && cur_reading > 0)
			num_errors[cur_reading - 1] = 0;

		switch (state) {
			using enum States;

			case ReadInputs: {
				if (prev == XferResult::Failed) {
					if (cur_reading > 0)
						cur_reading--;
					return handle_error(req);
				}

				if (cur_reading == 0 && (HAL_GetTick() - rescan_tmr) >= RescanIntervalMs) {
					rescan_tmr = HAL_GetTick();
					if (++auto_scan_idx >= expanders.size())
						auto_scan_idx = 0;
					auto_scan(auto_scan_idx);
				}

				if (cur_reading >= expanders.size()) {
					cur_reading = 0;
					state = CollectReadings;
					break;
				}

				if (expanders[cur_reading].found) {
					auto err = expanders[cur_reading].driver.read_inputs();
					if (err != GPIOExpander::Error::None)
						return handle_error(req);

					req.started_xfer = true;
				}

				cur_reading++;
				break;
			}

			case CollectReadings: {
				uint32_t readings = 0;

				for (auto i = 0u; auto &expander : expanders) {
					if (expander.found) {
						auto reading = Expander::Button::order_buttons(expander.driver.collect_last_reading());
						// First expander will be in the LSByte
						readings |= reading << (i * 8);
					}
					i++;
				}

				latest_reading.store(readings);

				state = ReadInputs;
				req.turn_done = true;
				break;
			}
		}

		return req;
	}

	// The bus was reset underneath us: start the pass over
	void on_bus_reset() {
		state = States::ReadInputs;
		cur_reading = 0;
	}

	uint32_t get_buttons() const {
		return latest_reading.load();
	}

	uint32_t connected_bitfield() const {
		uint32_t bitfield = 0u;

		for (auto i = 0u; auto &expander : expanders) {
			if (expander.found)
				bitfield |= 1 << i;
			i++;
		}

		return bitfield;
	}

private:
	// Errors on one expander before the bus is reset, and resets before we give
	// up on it entirely
	static constexpr uint32_t MaxErrorsBeforeReset = 8;
	static constexpr uint32_t MaxResetsBeforeDisable = 10;

	// How often to look for expanders that aren't (yet) there
	static constexpr uint32_t RescanIntervalMs = 1900;

	static constexpr std::array<int, Expander::Button::MaxExpanders> addresses{
		Expander::Button::gpio_chip_conf.addr + 6, // Jumper pos 1: ~0b001
		Expander::Button::gpio_chip_conf.addr + 5, // Jumper pos 2: ~0b010
		Expander::Button::gpio_chip_conf.addr + 3, // Jumper pos 3: ~0b100
		Expander::Button::gpio_chip_conf.addr + 7, // No jumpers  : ~0b000

		// Invalid positions:
		// addr + 4, // (jumpers pos 1+2)
		// addr + 2, // (jumpers pos 1+3)
		// addr + 1, // (jumpers pos 2+3)
		// addr + 0, // (all jumpers)
	};

	uint32_t rescan_tmr = 0;
	bool first_scan = true;

	struct FoundExpander {
		bool found = false;
		GPIOExpander driver;
	};

	std::array<FoundExpander, Expander::Button::MaxExpanders> expanders;

	enum class States {
		ReadInputs,
		CollectReadings,
	} state = States::ReadInputs;

	uint32_t cur_reading = 0;

	std::atomic<uint32_t> latest_reading{};

	std::array<uint32_t, Expander::Button::MaxExpanders> num_errors{};
	std::array<uint32_t, Expander::Button::MaxExpanders> num_error_retries{};

	BusRequest handle_error(BusRequest req) {
		num_errors[cur_reading]++;
		pr_dbg("ButtonExpander %u: I2C error (%u)\n", cur_reading, num_errors[cur_reading]);

		if (num_errors[cur_reading] <= MaxErrorsBeforeReset) {
			// End the cycle rather than retrying straight away: spinning here
			// on a dead expander would starve the MIDI expander of the bus.
			state = States::ReadInputs;
			req.turn_done = true;
			return req;
		}

		// Start counting afresh, so the next reset takes another full batch
		num_errors[cur_reading] = 0;
		num_error_retries[cur_reading]++;

		if (num_error_retries[cur_reading] > MaxResetsBeforeDisable) {
			pr_err("ButtonExpander %u: too many errors, disabling\n", cur_reading);
			expanders[cur_reading].found = false;
		}

		req.reset_bus = true;
		return req;
	}
};

} // namespace MetaModule
