#include "metamodule/VCV_module_wrapper.hh"
#include "console/pr_dbg.hh"
#include <random.hpp>

VCVModuleWrapper::VCVModuleWrapper() {
	rack::random::init();
}

void VCVModuleWrapper::update() {
	args.frame++;
	process(args);
}

void VCVModuleWrapper::set_samplerate(float rate) {
	args.sampleRate = rate;
	args.sampleTime = 1.f / rate;
}

void VCVModuleWrapper::set_param(int id, float val) {
	if ((size_t)id < paramQuantities.size() && paramQuantities[id]) {
		val *= (paramQuantities[id]->maxValue - paramQuantities[id]->minValue);
		val += paramQuantities[id]->minValue;
		if (paramQuantities[id]->snapEnabled)
			val = std::round(val);
	}
	if ((size_t)id < params.size())
		params[id].setValue(val);
}

void VCVModuleWrapper::set_input(int input_id, float val) {
	if ((size_t)input_id < inputs.size())
		inputs[input_id].setVoltage(val);
}

float VCVModuleWrapper::get_output(int output_id) const {
	if ((size_t)output_id < outputs.size())
		return outputs[output_id].getVoltage();
	else
		return 0.f;
}

float VCVModuleWrapper::get_led_brightness(int led_id) const {
	if ((size_t)led_id < lights.size()) {
		auto l = std::clamp(lights[led_id].value, 0.f, 1.f);
		return l;
	}
	return 0;
}

void VCVModuleWrapper::mark_all_inputs_unpatched() {
	for (auto &in : inputs) {
		for (auto &chan_volts : in.voltages) {
			chan_volts = 0;
		}
		in.channels = 0;
	}
}

void VCVModuleWrapper::mark_input_unpatched(int input_id) {
	if ((size_t)input_id < inputs.size()) {
		inputs[input_id].channels = 0;
		for (auto &chan_volts : inputs[input_id].voltages) {
			chan_volts = 0;
		}
	}
}

void VCVModuleWrapper::mark_input_patched(int input_id) {
	if ((size_t)input_id < inputs.size())
		inputs[input_id].channels = 1;
}

void VCVModuleWrapper::mark_all_outputs_unpatched() {
	for (auto &out : outputs)
		out.channels = 0;
}

void VCVModuleWrapper::mark_output_unpatched(int output_id) {
	if ((size_t)output_id < outputs.size())
		outputs[output_id].channels = 0;
}

void VCVModuleWrapper::mark_output_patched(int output_id) {
	if ((size_t)output_id < outputs.size())
		outputs[output_id].channels = 1;
}
