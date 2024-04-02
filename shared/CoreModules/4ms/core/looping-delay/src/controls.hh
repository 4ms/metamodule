#pragma once
#include "brain_conf.hh"
#include "conf/board_conf.hh"
#include "debug.hh"
#include "drivers/adc_builtin.hh"
#include "drivers/analog_in_ext.hh"
#include "drivers/debounced_switch.hh"
#include "elements.hh"
#include "util/filter.hh"

namespace LDKit
{

class Controls {
	// ADCs (Pots and CV):
	static inline __attribute__((section(".noncachable"))) std::array<uint16_t, NumCVs> cv_adc_buffer;
	mdrivlib::AdcDmaPeriph<Brain::CVAdcConf> cv_adcs{cv_adc_buffer, Board::CVAdcChans};

	static inline __attribute__((section(".noncachable"))) std::array<uint16_t, NumPots> pot_adc_buffer;
	mdrivlib::AdcDmaPeriph<Brain::PotAdcConf> pot_adcs{pot_adc_buffer, Board::PotAdcChans};

	static constexpr bool hardware_oversampling = Brain::PotAdcConf::oversample;
	std::array<Oversampler<256, uint16_t>, NumPots> pots;
	std::array<Oversampler<64, uint16_t>, NumCVs> cvs;

public:
	Controls() = default;

	// Buttons/Switches:
	Board::PingButton ping_button;
	Board::RevButton rev_button;
	Board::HoldButton inf_button;
	Board::TimeSwitch time_switch;

	// Trig Jacks
	Board::RevJack rev_jack;
	Board::HoldJack inf_jack;

	// LEDs:
	Board::PingLED ping_led;
	Board::HoldLED inf_led;
	Board::RevLED rev_led;

	using SwitchPos = mdrivlib::SwitchPos;

	uint16_t read_pot(PotAdcElement adcnum) {
		if constexpr (hardware_oversampling)
			return pot_adc_buffer[adcnum];
		else
			return pots[adcnum].val();
	}
	uint16_t read_cv(CVAdcElement adcnum) {
		if constexpr (hardware_oversampling)
			return cv_adc_buffer[adcnum];
		else
			return cvs[adcnum].val();
	}

	SwitchPos read_time_switch() {
		return static_cast<SwitchPos>(time_switch.read());
	}

	void start() {
		if constexpr (!hardware_oversampling) {
			pot_adcs.register_callback([this] {
				// F723: 168kHz. With 128 O.S. = 1.3kHz
				// Debug::Pin1::high();
				for (unsigned i = 0; auto &pot : pots)
					pot.add_val(pot_adc_buffer[i++]);
				// Debug::Pin1::low();
			});
			cv_adcs.register_callback([this] {
				// F723: 168kHz. With 32 O.S. = 5kHz
				// Step response is worst-case 2 windows = 32 * 2 = 64 / 168kHz = 0.38ms
				// Debug::Pin0::high();
				for (unsigned i = 0; auto &cv : cvs)
					cv.add_val(cv_adc_buffer[i++]);
				// Debug::Pin0::low();
			});
		}
		pot_adcs.start();
		cv_adcs.start();
	}

	void update() {
		ping_button.update();
		rev_button.update();
		inf_button.update();

		// ping_jack.update();
		rev_jack.update();
		inf_jack.update();
	}
};
} // namespace LDKit
