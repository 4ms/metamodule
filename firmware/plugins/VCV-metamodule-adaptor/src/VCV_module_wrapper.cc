#include "metamodule/VCV_module_wrapper.hh"
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
	if (id < (int)paramQuantities.size()) {
		val *= (paramQuantities[id]->maxValue - paramQuantities[id]->minValue);
		val += paramQuantities[id]->minValue;
		if (paramQuantities[id]->snapEnabled)
			val = std::round(val);
	}
	params[id].setValue(val);
}

void VCVModuleWrapper::set_input(const int input_id, const float val) {
	inputs[input_id].setVoltage(val);
}

float VCVModuleWrapper::get_output(const int output_id) const {
	return outputs[output_id].getVoltage();
}

float VCVModuleWrapper::get_led_brightness(const int led_id) const {
	if (led_id >= 0 && led_id < (int)lights.size()) {
		auto l = std::clamp(lights[led_id].value, 0.f, 1.f);
		return l;
	}
	return 0;
}

void VCVModuleWrapper::mark_all_inputs_unpatched() {
	for (auto &in : inputs)
		in.connected = false;
}

void VCVModuleWrapper::mark_input_unpatched(const int input_id) {
	inputs[input_id].connected = false;
}

void VCVModuleWrapper::mark_input_patched(const int input_id) {
	inputs[input_id].connected = true;
}

void VCVModuleWrapper::mark_all_outputs_unpatched() {
	for (auto &out : outputs)
		out.connected = false;
}

void VCVModuleWrapper::mark_output_unpatched(const int output_id) {
	outputs[output_id].connected = false;
}

void VCVModuleWrapper::mark_output_patched(const int output_id) {
	outputs[output_id].connected = true;
}
