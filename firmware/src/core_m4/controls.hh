#pragma once
#include "conf/control_conf.hh"
#include "conf/pin_conf.hh"
#include "core_m4/sense_pin_reader.hh"
#include "drivers/adc_builtin.hh"
#include "drivers/debounced_switch.hh"
#include "drivers/gpio_expander.hh"
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
using mdrivlib::PinPolarity;

struct Controls {
	Controls(DoubleBufParamBlock &param_blocks_ref);

	void start();
	void process();

private:
	void update_params();
	void update_debouncers();

	float get_pot_reading(uint32_t pot_id);

	void set_samplerate(unsigned sample_rate);

	template<size_t block_num>
	void start_param_block();

	void parse_midi();
	void update_midi_connected();
	void update_control_expander();
	void update_rotary();

	mdrivlib::PinChangeInt<ListenClosely::FrameRatePinChangeConf> read_controls_task;

	mdrivlib::DebouncedSPDT3pos<ListenClosely::CompSwitch0, ListenClosely::CompSwitch1, mdrivlib::PinPolarity::Inverted>
		comp_switch;

	Debouncer<0b0001, 0b1110, 0b1111> eq_switch_pin0{};
	Debouncer<0b0001, 0b1110, 0b1111> eq_switch_pin1{};

	DebouncedButton<ListenClosely::LowSelBut, PinPolarity::Inverted> low_sel_button;
	DebouncedButton<ListenClosely::MidSelBut, PinPolarity::Inverted> mid_sel_button;
	DebouncedButton<ListenClosely::HighSelBut, PinPolarity::Inverted> high_sel_button;

	// Analog controls (pots)
	static constexpr size_t NumAdcs = sizeof(ListenClosely::PotConfs) / sizeof(mdrivlib::AdcChannelConf);
	std::array<uint16_t, NumAdcs> pot_vals{};
	mdrivlib::AdcDmaPeriph<ListenClosely::PotAdcConf> pot_adc{pot_vals, ListenClosely::PotConfs};

	InterpParamVariable<float> _adcs[NumAdcs]{};
	static constexpr uint32_t AdcReadFrequency = 580; //571
	bool _new_adc_data_ready = false;

	SensePinReader sense_pin_reader; //also eq mode switch

	// Params
	DoubleBufParamBlock &param_blocks;
	Params *cur_params;
	MetaParams *cur_metaparams;
	bool _buffer_full = false;
	bool _first_param = true;

	uint32_t sample_rate = 48000;

	unsigned num_pot_updates = 0;
};

} // namespace MetaModule
