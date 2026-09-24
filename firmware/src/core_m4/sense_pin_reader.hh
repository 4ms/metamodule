#pragma once
#include "conf/gpio_expander_conf.hh"
#include "conf/hsem_conf.hh"
#include "conf/i2c_codec_conf.hh"
#include "drivers/gpio_expander.hh"
#include "drivers/hsem.hh"
#include "params/metaparams.hh"
#include "pr_dbg.hh"
#include <array>
#include <atomic>
#include <cstdint>

namespace MetaModule
{

// I2C Bus shared between Codec, main GPIO Expander, and optional Audio Expander module.
// The Main PCB has a GPIO expander chip used to detect if jacks are plugged.
// The Audio Expander module also has a GPIO Expander chip for the same purpose.
//
// Recovery from I2C errors (e.g. noise on the Audio Expander cable):
// - Errors are retried on the next poll. Every few consecutive errors on a chip,
//   the bus is cleared and the I2C peripheral is reset.
// - The Audio Expander is only looked for at boot. If it stops responding for
//   long enough (while the main chip is fine), we give up on it until the next
//   power cycle and report its jacks as patched.
// - If the main chip stops responding for long enough, all jacks are reported
//   as patched (fail-safe mode), and we keep retrying. After a few
//   good reads in a row, normal jack sensing resumes.
class SensePinReader {
	using GPIOExpander = mdrivlib::GPIOExpander;
	using I2CPeriph = mdrivlib::I2CPeriph;
	using I2CLock = mdrivlib::HWSemaphore<SharedI2CLock>;

public:
	SensePinReader() {
		//Spin until we get the lock
		while (I2CLock::lock() == mdrivlib::HWSemaphoreFlag::LockFailed) {
		}

		i2c.enable_IT(a7m4_shared_i2c_codec_conf.priority1, a7m4_shared_i2c_codec_conf.priority2);

		const auto now = HAL_GetTick();

		chips[Main].state = ChipState::Active;
		chips[Main].last_ok_tm = now;

		if (!chips[Main].driver.is_present()) {
			pr_err("Main Jack sense GPIO Expander failed to be found\n");
		} else {
			pr_dbg("Main Jack sense GPIO Expander present\n");
			chips[Main].driver.start();
		}

		if (chips[Ext].driver.is_present()) {
			pr_dbg("Audio Expander GPIO expander chip present\n");
			chips[Ext].state = ChipState::Active;
			chips[Ext].last_ok_tm = now;
			chips[Ext].driver.start();
		}

		I2CLock::unlock();

		publish();
	}

	void update() {
		const auto now = HAL_GetTick();

		if (xfer_in_flight) {
			// Note: this just checks if I2C is busy in this process, not globally
			if (!i2c.is_ready()) {
				if ((now - xfer_start_tm) >= XferTimeoutMs) {
					if (!main_failsafe)
						pr_warn("Jack sense %s: I2C transfer timed out\n", name(cur_chip));
					xfer_in_flight = false;
					handle_result(false, now);
					// We still hold the lock from starting the xfer
					reset_bus(now);
					release_bus();
				}
				return;
			}

			xfer_in_flight = false;
			const bool ok = !i2c.had_error();
			release_bus();
			handle_result(ok, now);
		}

		if ((now - pause_tm) < pause_ms)
			return;

		// If we can't get the lock, the A7 is using the bus. Try again next time.
		if (!take_bus())
			return;

		if (bus_reset_pending) {
			reset_bus(now);
			release_bus();
			return;
		}

		start_read(now);
	}

	// Called from the controls ISR
	uint32_t last_reading() const {
		return jack_senses.load(std::memory_order_relaxed);
	}

	// Called from the controls ISR
	uint8_t faults() const {
		return fault_flags.load(std::memory_order_relaxed);
	}

private:
	// Poll period for each read (main and ext chips alternate)
	static constexpr uint32_t PollMs = 100;
	// Poll period while in the fail-safe state: the bus is probably dead, so don't hog the M4
	static constexpr uint32_t FailSafeRetryMs = 1000;
	// Pause after resetting the bus
	static constexpr uint32_t BusResetPauseMs = 50;

	// Max time an xfer has to complete before we consider it a failure
	// Typical time is under 1ms
	static constexpr uint32_t XferTimeoutMs = 50;

	// Consecutive errors on one chip before the bus is cleared and reset
	static constexpr uint32_t ErrorsBeforeBusReset = 16;

	// Main chip: if we go this amount of time and have this many
	// erros without a good xfer, then go to failsafe mode
	// => report all jacks patched
	static constexpr uint32_t MainFailSafeMs = 5000;
	static constexpr uint32_t MainFailSafeErrors = 8;

	// Good reads in a row needed to leave the fail-safe state
	static constexpr uint32_t MainRecoverReads = 2;

	// Ext chip: no good read for this long (and at least this many failed
	// attempts) while the main chip is fine => give up until power cycle
	static constexpr uint32_t ExtGiveUpMs = 10000;
	static constexpr uint32_t ExtGiveUpErrors = 40;

	enum ChipId : unsigned { Main = 0, Ext = 1 };

	enum class ChipState {
		Absent, // Not found at boot, not polled
		Active, // Polled
		Lost,	// Gave up after too many errors, not polled
	};

	struct Chip {
		GPIOExpander driver;
		ChipState state = ChipState::Absent;
		uint16_t raw_reading = 0; // Pins are low when patched, so 0 = all patched
		uint32_t errors_since_ok = 0;
		uint32_t last_ok_tm = 0;
	};

	I2CPeriph i2c{a7m4_shared_i2c_codec_conf};

	std::array<Chip, 2> chips{{
		{.driver = {i2c, mainboard_gpio_expander_conf}},
		{.driver = {i2c, extaudio_gpio_expander_conf}},
	}};

	ChipId cur_chip = Main;

	bool have_lock = false;
	bool xfer_in_flight = false;
	uint32_t xfer_start_tm = 0;
	bool bus_reset_pending = false;

	uint32_t pause_tm = 0;
	uint32_t pause_ms = 0;

	bool main_failsafe = false;
	uint32_t main_good_reads = 0;

	std::atomic<uint32_t> jack_senses{0xFFFF'FFFF};
	std::atomic<uint8_t> fault_flags{0};

	static const char *name(ChipId id) {
		return id == Main ? "main" : "Audio Expander";
	}

	bool take_bus() {
		if (!have_lock)
			have_lock = (I2CLock::lock() == mdrivlib::HWSemaphoreFlag::LockedOk);
		return have_lock;
	}

	void release_bus() {
		if (have_lock) {
			I2CLock::unlock();
			have_lock = false;
		}
	}

	void start_read(uint32_t now) {
		// Alternate between the chips, skipping the Ext chip if it's not active
		cur_chip = (cur_chip == Main && chips[Ext].state == ChipState::Active) ? Ext : Main;

		if (chips[cur_chip].driver.read_inputs() != GPIOExpander::Error::None) {
			release_bus();
			handle_result(false, now);
			return;
		}

		xfer_in_flight = true;
		xfer_start_tm = now;
	}

	void handle_result(bool ok, uint32_t now) {
		auto &chip = chips[cur_chip];

		if (ok) {
			chip.raw_reading = chip.driver.collect_last_reading();

			if (chip.errors_since_ok > 0 && !main_failsafe)
				pr_warn("Jack sense %s: recovered after %u I2C errors\n", name(cur_chip), chip.errors_since_ok);

			chip.errors_since_ok = 0;
			chip.last_ok_tm = now;

			if (cur_chip == Main && main_failsafe) {
				if (++main_good_reads >= MainRecoverReads) {
					main_failsafe = false;
					pr_err("Jack sense: I2C bus recovered, jack sensing resumed\n");
				}
			}

		} else {
			chip.errors_since_ok++;

			if (cur_chip == Main)
				main_good_reads = 0;

			// Just the first error in a run: noise on the bus is expected to cause
			// the occasional error, and we don't want to flood the console
			if (chip.errors_since_ok == 1 && !main_failsafe)
				pr_warn("Jack sense %s: I2C error, will retry\n", name(cur_chip));

			if ((chip.errors_since_ok % ErrorsBeforeBusReset) == 0)
				bus_reset_pending = true;

			check_give_up(now);
		}

		pause_tm = now;
		pause_ms = main_failsafe ? FailSafeRetryMs : PollMs;

		publish();
	}

	void check_give_up(uint32_t now) {
		auto &main = chips[Main];
		auto &ext = chips[Ext];

		if (!main_failsafe && main.errors_since_ok >= MainFailSafeErrors && (now - main.last_ok_tm) >= MainFailSafeMs) {
			main_failsafe = true;
			main_good_reads = 0;
			pr_err("Jack sense: main GPIO expander not responding for %ums (%u errors). "
				   "Reporting all jacks as patched\n",
				   now - main.last_ok_tm,
				   main.errors_since_ok);
		}

		// Only blame the Audio Expander if the bus is otherwise working.
		// If the whole bus is down, the main chip fail-safe covers it
		const bool main_healthy = !main_failsafe && main.errors_since_ok == 0;

		if (ext.state == ChipState::Active && main_healthy && ext.errors_since_ok >= ExtGiveUpErrors &&
			(now - ext.last_ok_tm) >= ExtGiveUpMs)
		{
			ext.state = ChipState::Lost;
			pr_err("Jack sense: Audio Expander not responding for %ums (%u errors). Giving up until power cycle, "
				   "reporting its jacks as patched\n",
				   now - ext.last_ok_tm,
				   ext.errors_since_ok);
		}
	}

	void publish() {
		// For stereo jacks: patched = low
		uint16_t main_jacksense = main_failsafe ? 0xFFFF : ~chips[Main].raw_reading;
		uint16_t ext_jacksense =
			(main_failsafe || chips[Ext].state != ChipState::Active) ? 0xFFFF : ~chips[Ext].raw_reading;

		jack_senses.store(main_jacksense | (uint32_t(ext_jacksense) << 16), std::memory_order_relaxed);

		uint8_t flags = 0;
		if (main_failsafe)
			flags |= JackSenseFault::MainFailed;
		if (chips[Ext].state == ChipState::Lost)
			flags |= JackSenseFault::ExtLost;
		fault_flags.store(flags, std::memory_order_relaxed);
	}

	// Must hold the lock
	void reset_bus(uint32_t now) {
		if (!main_failsafe)
			pr_warn("Jack sense: resetting I2C bus\n");

		i2c.clear_bus(a7m4_shared_i2c_codec_conf);
		i2c.reset(a7m4_shared_i2c_codec_conf);

		bus_reset_pending = false;
		xfer_in_flight = false;

		pause_tm = now;
		pause_ms = main_failsafe ? FailSafeRetryMs : BusResetPauseMs;
	}
};

} // namespace MetaModule
