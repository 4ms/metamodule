#pragma once
#include "conf/control_conf.hh"
#include "conf/pin_conf.hh"
#include "core_m4/sense_pin_reader.hh"
#include "drivers/adc_builtin.hh"
#include "drivers/debounced_switch.hh"
#include "drivers/gpio_expander.hh"
#include "drivers/led_driver_lp5009.hh"
#include "drivers/pin.hh"
#include "drivers/pin_change.hh"
#include "params/metaparams.hh"
#include "params/param_block.hh"
#include "params/params.hh"
#include "util/interp_param.hh"

namespace MetaModule
{

struct MidiHost;

using mdrivlib::DebouncedButton;
using mdrivlib::DebouncedPin;
using mdrivlib::GPIOExpander;
using mdrivlib::PinMode;
using mdrivlib::PinPolarity;

struct Controls {
	Controls(DoubleBufParamBlock &param_blocks_ref);

	void start();
	void process();

private:
	void update_params();
	void update_debouncers();
	void update_lights();

	float get_pot_reading(uint32_t pot_id);

	void set_samplerate(unsigned sample_rate);

	template<size_t block_num>
	void start_param_block();

	void parse_midi();
	void update_midi_connected();
	void update_control_expander();
	void update_rotary();

	// Switches/Buttons
	mdrivlib::DebouncedSPDT3pos<ListenClosely::CompSwitch0, ListenClosely::CompSwitch1, PinPolarity::Inverted>
		comp_switch;

	Debouncer<0b0001, 0b1110, 0b1111> eq_switch_pin0{};
	Debouncer<0b0001, 0b1110, 0b1111> eq_switch_pin1{};

	DebouncedButton<ListenClosely::LowSelBut, PinPolarity::Normal> low_sel_button;
	DebouncedButton<ListenClosely::MidSelBut, PinPolarity::Normal> mid_sel_button;
	DebouncedButton<ListenClosely::HighSelBut, PinPolarity::Normal> high_sel_button;

	// TODO: use this to save plug and unplug events in metaparams (instead of state)
	Toggler jack_sense[5];

	// LEDs:
	std::array<mdrivlib::Pin, 4> low_sel_leds{{
		{ListenClosely::LowSelLeds[0], PinMode::Output},
		{ListenClosely::LowSelLeds[1], PinMode::Output},
		{ListenClosely::LowSelLeds[2], PinMode::Output},
		{ListenClosely::LowSelLeds[3], PinMode::Output},
	}};

	std::array<mdrivlib::Pin, 6> mid_sel_leds{{
		{ListenClosely::MidSelLeds[0], PinMode::Output},
		{ListenClosely::MidSelLeds[1], PinMode::Output},
		{ListenClosely::MidSelLeds[2], PinMode::Output},
		{ListenClosely::MidSelLeds[3], PinMode::Output},
		{ListenClosely::MidSelLeds[4], PinMode::Output},
		{ListenClosely::MidSelLeds[5], PinMode::Output},
	}};

	std::array<mdrivlib::Pin, 5> high_sel_leds{{
		{ListenClosely::HighSelLeds[0], PinMode::Output},
		{ListenClosely::HighSelLeds[1], PinMode::Output},
		{ListenClosely::HighSelLeds[2], PinMode::Output},
		{ListenClosely::HighSelLeds[3], PinMode::Output},
		{ListenClosely::HighSelLeds[4], PinMode::Output},
	}};

	mdrivlib::Pin clip_left_led{ListenClosely::ClipLeftLed, PinMode::Output};
	mdrivlib::Pin clip_right_led{ListenClosely::ClipRightLed, PinMode::Output};

	// Shared I2C bus
	mdrivlib::I2CPeriph i2c;

	// LED chip:
	mdrivlib::LP5009::Device<mdrivlib::LP5009::Chip::LP5009> led_driver;
	std::array<uint8_t, 9> packed_leds;
	std::array<float, 9> brightness;

	// Analog controls (pots)
	static constexpr size_t NumAdcs = sizeof(ListenClosely::PotConfs) / sizeof(mdrivlib::AdcChannelConf);
	std::array<uint16_t, NumAdcs> pot_vals{};
	mdrivlib::AdcDmaPeriph<ListenClosely::PotAdcConf> pot_adc{pot_vals, ListenClosely::PotConfs};

	InterpParamVariable<float> _adcs[NumAdcs]{};
	static constexpr uint32_t AdcReadFrequency = 580; //571
	bool _new_adc_data_ready = false;

	// GPIO Expander
	SensePinReader sense_pin_reader; //also eq mode switch

	// Task
	mdrivlib::PinChangeInt<ListenClosely::FrameRatePinChangeConf> read_controls_task;

	// Params
	DoubleBufParamBlock &param_blocks;
	Params *cur_params;
	MetaParams *cur_metaparams;
	LedStates *cur_leds;

	// Internal state
	bool _buffer_full = false;
	bool _first_param = true;
	unsigned num_pot_updates = 0;

	uint32_t sample_rate = StreamConf::Audio::SampleRate;
};

} // namespace MetaModule
