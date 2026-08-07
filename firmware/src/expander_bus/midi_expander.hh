#pragma once
#include "conf/midi_expander_conf.hh"
#include "drivers/i2c.hh"
#include "expander_bus.hh"
#include "midi_expander_driver.hh"
#include "pr_dbg.hh"
#include "stm32mp1xx_hal.h"
#include "util/lockfree_fifo_spsc.hh"
#include <algorithm>
#include <array>
#include <cstdint>
#include <span>
#include <utility>

namespace MetaModule
{

// The MIDI Expander on the aux I2C bus.
//
// One full cycle is: read how many bytes each jack has for us and how many it
// will take from us, read that many, hand them over, then send whatever is
// queued for its output jacks. One transaction per turn.
class MidiExpanderManager {
public:
	// Jack ordering does not mach Port ordering! (USB=0)
	enum Jack : uint8_t { Din = 0, Trs = 1 };

	explicit MidiExpanderManager(mdrivlib::I2CPeriph &i2c)
		: driver{i2c, Expander::Midi::midi_chip_conf} {
	}

	void scan() {
		rescan_tmr = HAL_GetTick();

		found = false;
		driver.set_address(Expander::Midi::addr);

		if (driver.is_present()) {
			found = true;
			driver.start();

			// Start clean: this may be a reconnect, so nothing from the old
			// session should carry over
			driver.discard_payload();
			state = States::ReadSize;
			num_errors = 0;
			num_error_retries = 0;
			missing_logged = false;

			pr_info("MIDI Expander found at addr 0x%x\n", Expander::Midi::addr);

		} else if (!missing_logged) {
			// Only on the first miss: this runs every second until one shows up
			missing_logged = true;
			pr_dbg("MIDI Expander not found at addr 0x%x, will keep looking\n", Expander::Midi::addr);
		}
	}

	BusRequest update(XferResult prev) {
		BusRequest req{};

		if (!found) {
			if ((HAL_GetTick() - rescan_tmr) >= RescanIntervalMs)
				scan();

			req.turn_done = true;
			return req;
		}

		// Only a transfer that actually completed proves the expander is still
		// there, so it's the only thing that may clear the error count
		if (prev == XferResult::Ok)
			num_errors = 0;

		if (prev == XferResult::Failed) {
			driver.discard_payload();
			// Back to the top: ReadPayload would act on sizes that never arrived
			state = States::ReadSize;
			return handle_error(req);
		}

		switch (state) {
			using enum States;

			case ReadSize: {
				tx_len = {};

				if (driver.read_sizes() != MIDIExpander::None) {
					pr_dbg("MidiExpander: error reading size\n");
					return handle_error(req);
				}

				req.started_xfer = true;
				state = ReadPayload;
				break;
			}

			case ReadPayload: {
				if (driver.read_payload() != MIDIExpander::None) {
					pr_dbg("MidiExpander: error reading payload\n");
					return handle_error(req);
				}

				req.started_xfer = true;
				state = CollectPayload;
				break;
			}

			case CollectPayload: {
				rx_payloads = driver.collect_payload();
				state = Write;
				break;
			}

			case Write: {
				// Only refill once the previous write was acknowledged, so a
				// failed transfer resends the same bytes instead of losing them
				if (tx_len[0] == 0 && tx_len[1] == 0) {
					const auto space = driver.tx_space();
					tx_len[0] = stage_tx(0, space[0]);
					tx_len[1] = stage_tx(1, space[1]);
				}

				if (tx_len[0] || tx_len[1]) {
					const auto err = driver.write_payload({tx_buf[0].data(), tx_len[0]}, {tx_buf[1].data(), tx_len[1]});

					if (err != MIDIExpander::None) {
						pr_dbg("MidiExpander: error writing payload\n");
						return handle_error(req);
					}

					req.started_xfer = true;
				}

				state = ReadSize;
				req.turn_done = true;
				break;
			}
		}

		return req;
	}

	void on_bus_reset() {
		state = States::ReadSize;
		driver.discard_payload();
	}

	bool connected() const {
		return found;
	}

	bool send(std::span<const uint8_t> bytes, unsigned jack) {
		if (jack >= tx_queue.size())
			return false;

		auto &queue = tx_queue[jack];

		if (queue.num_free() < bytes.size()) {
			tx_drops++;
			return false;
		}

		for (auto byte : bytes)
			queue.put(byte);

		return true;
	}

	// Returns spans pointing to the driver's internal rx buffers
	// Caller must copy or use the buffers before the next read (max 10ms)
	[[nodiscard]] std::array<std::span<const uint8_t>, 2> take_rx_payloads() {
		return std::exchange(rx_payloads, {});
	}

private:
	// Errors before the bus is reset, and resets before we give up entirely
	static constexpr uint32_t MaxErrorsBeforeReset = 8;
	static constexpr uint32_t MaxResetsBeforeDisable = 5;

	static constexpr uint32_t RescanIntervalMs = 2000;

	// could be raised to 255
	static constexpr size_t MaxTxPerPoll = 128;

	MIDIExpander driver;
	bool found = false;

	enum class States {
		ReadSize,
		ReadPayload,
		CollectPayload,
		Write,
	} state = States::ReadSize;

	uint32_t rescan_tmr = 0;
	bool missing_logged = false;

	uint32_t num_errors{};
	uint32_t num_error_retries{};

	std::array<std::span<const uint8_t>, 2> rx_payloads;

	std::array<LockFreeFifoSpsc<uint8_t, 512>, 2> tx_queue;

	// Staged for the current write, and held until the transfer is acknowledged
	std::array<std::array<uint8_t, MaxTxPerPoll>, 2> tx_buf{};
	std::array<uint8_t, 2> tx_len{};

	uint32_t tx_drops = 0;

	uint8_t stage_tx(unsigned jack, uint8_t space) {
		auto &queue = tx_queue[jack];

		const auto n = std::min({queue.num_filled(), size_t(space), MaxTxPerPoll});

		for (auto i = 0u; i < n; i++)
			tx_buf[jack][i] = queue.get_or_default();

		return n;
	}

	BusRequest handle_error(BusRequest req) {
		num_errors++;
		pr_dbg("MidiExpander: I2C error (%u)\n", num_errors);

		if (num_errors <= MaxErrorsBeforeReset) {
			state = States::ReadSize;
			req.turn_done = true;
			return req;
		}

		num_errors = 0;
		num_error_retries++;

		if (num_error_retries > MaxResetsBeforeDisable) {
			pr_err("MidiExpander: too many errors, disabling\n");
			found = false;

			// empty the queue so we have room for new data
			for (auto &queue : tx_queue)
				queue.reset();
			tx_len = {};
		}

		req.reset_bus = true;
		return req;
	}
};

} // namespace MetaModule
