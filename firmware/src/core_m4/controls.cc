#include "controls.hh"
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "hsem_handler.hh"
#include "util/countzip.hh"

namespace MetaModule
{

using namespace mdrivlib;

void Controls::update_debouncers() {
	comp_switch.update();
	low_sel_button.update();
	mid_sel_button.update();
	high_sel_button.update();
}

void Controls::update_params() {
	// Interpolate knob readings across the param block, since we capture them at a slower rate than audio process
	if (_new_adc_data_ready) {
		for (unsigned i = 0; i < NumAdcs; i++) {
			_adcs[i].set_new_value(get_pot_reading(i));
			num_pot_updates = 0;
		}
		_new_adc_data_ready = false;
	}

	num_pot_updates++;
	if (num_pot_updates >= _adcs[0].get_num_updates()) {
		for (unsigned i = 0; i < NumAdcs; i++) {
			auto val = _adcs[i].target_val;
			if (i < PanelDef::NumPot)
				cur_params->knobs[i] = std::clamp(val, 0.f, 1.f);
			else
				cur_params->width_cv = std::clamp(val, 0.f, 1.f);

			_adcs[i].cur_val = _adcs[i].target_val;
		}
	} else {
		for (unsigned i = 0; i < NumAdcs; i++) {
			auto val = _adcs[i].next();
			if (i < PanelDef::NumPot)
				cur_params->knobs[i] = std::clamp(val, 0.f, 1.f);
			else
				cur_params->width_cv = std::clamp(val, 0.f, 1.f);
		}
	}

	if (_first_param) {
		_first_param = false;

		cur_metaparams->low_sel.transfer_events(low_sel_button);
		cur_metaparams->mid_sel.transfer_events(mid_sel_button);
		cur_metaparams->high_sel.transfer_events(high_sel_button);

		auto gpio_exp = sense_pin_reader.last_reading();
		cur_metaparams->inL_plugged = gpio_exp & ListenClosely::GpioExpBit::SenseInL;
		cur_metaparams->inR_plugged = gpio_exp & ListenClosely::GpioExpBit::SenseInR;
		cur_metaparams->outL_plugged = gpio_exp & ListenClosely::GpioExpBit::SenseOutL;
		cur_metaparams->outR_plugged = gpio_exp & ListenClosely::GpioExpBit::SenseOutR;
		cur_metaparams->cv_plugged = gpio_exp & ListenClosely::GpioExpBit::SenseInCV;

		eq_switch_pin0.register_state(gpio_exp & ListenClosely::GpioExpBit::EQSwitch_0);
		eq_switch_pin1.register_state(gpio_exp & ListenClosely::GpioExpBit::EQSwitch_1);

		cur_metaparams->eq_switch = (eq_switch_pin0.is_high() ? 0 : 0b01) | (eq_switch_pin1.is_high() ? 0 : 0b10);

		cur_metaparams->comp_switch = comp_switch.state();
	}

	cur_params++;
	if (cur_params == param_blocks[0].params.end() || cur_params == param_blocks[1].params.end())
		_buffer_full = true;
}

template<size_t block_num>
void Controls::start_param_block() {
	static_assert(block_num <= 1, "There is only block 0 and block 1");

	// 28us width, every 1.3ms (audio block rate for 64-frame blocks) = 2.15% load
	cur_metaparams = &param_blocks[block_num].metaparams;
	cur_params = param_blocks[block_num].params.begin();
	_first_param = true;
	_buffer_full = false;
}

void Controls::start() {
	HWSemaphore<ParamsBuf1Lock>::clear_ISR();
	HWSemaphore<ParamsBuf1Lock>::disable_channel_ISR();
	HWSemaphoreCoreHandler::register_channel_ISR<ParamsBuf1Lock>([&]() { start_param_block<0>(); });

	HWSemaphore<ParamsBuf2Lock>::clear_ISR();
	HWSemaphore<ParamsBuf2Lock>::disable_channel_ISR();
	HWSemaphoreCoreHandler::register_channel_ISR<ParamsBuf2Lock>([&]() { start_param_block<1>(); });

	HWSemaphore<ParamsBuf1Lock>::enable_channel_ISR();
	HWSemaphore<ParamsBuf2Lock>::enable_channel_ISR();

	read_controls_task.start();
}

void Controls::process() {
	sense_pin_reader.update();
}

void Controls::set_samplerate(unsigned sample_rate) {
	this->sample_rate = sample_rate;
	for (auto &adc : _adcs) {
		adc.set_num_updates(sample_rate / AdcReadFrequency);
	}
}

Controls::Controls(DoubleBufParamBlock &param_blocks_ref)
	: param_blocks(param_blocks_ref)
	, cur_params(param_blocks[0].params.begin())
	, cur_metaparams(&param_blocks_ref[0].metaparams) {

	// TODO: get IRQn, ADC1 periph from PotAdcConf. Also use register_access<>
	// TODO: _new_adc_data_ready is set true here (pri 2) and set false in read_controls_task (pri 0)
	InterruptManager::register_and_start_isr(ADC1_IRQn, 2, 2, [&] {
		uint32_t tmp = ADC1->ISR;
		if (tmp & ADC_ISR_EOS) {
			ADC1->ISR = tmp | ADC_ISR_EOS;
			_new_adc_data_ready = true;
		}
	});

	set_samplerate(sample_rate);

	pot_adc.start();

	// Todo: use RCC_Enable or create DBGMCU_Control:
	// HSEM_IT2_IRQn (125) and ADC1 (18) make it hard to debug, but they can't be frozen
	__HAL_DBGMCU_FREEZE_TIM6();
	__HAL_DBGMCU_FREEZE_TIM17();

	read_controls_task.init([this]() {
		if (_buffer_full)
			return;
		update_debouncers();
		update_params();
	});
}

float Controls::get_pot_reading(uint32_t pot_id) {
	if (pot_id < pot_vals.size()) {
		auto raw = (int32_t)pot_vals[pot_id];
		float val = raw - ListenClosely::MinPotValue;
		return std::clamp(val / ListenClosely::MaxPotValue, 0.f, 1.f);
	}
	return 0;
}

} // namespace MetaModule
