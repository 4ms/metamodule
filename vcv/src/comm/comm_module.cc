#include "comm/comm_module.hh"

void CommModule::onSampleRateChange() {
	sampleRateChanged = true;
}

void CommModule::process(const ProcessArgs &args) {
	for (unsigned i = 0; auto &p : params) {
		core->set_param(i, p.getValue());
		i++;
	}

	for (auto &alt : altParams) {
		if (alt.is_updated)
			core->set_alt_param(alt.id, alt.val);
		alt.is_updated = false;
	}

	for (auto &injack : inJacks) {
		auto id = injack.getId();
		injack.updateInput();

		if (injack.isJustPatched())
			core->mark_input_patched(id);

		if (injack.isJustUnpatched()) {
			core->set_input(id, 0); // 0 = unpatched value. TODO: allow for normalizations
			core->mark_input_unpatched(id);
		}

		if (injack.isConnected()) {
			auto scaledIn = injack.getValue() / 5.f; // TODO: Move scaling to SmartCoreProcessor or other wrapper
			core->set_input(id, scaledIn);
		}
	}

	if (sampleRateChanged) {
		sampleRateChanged = false;
		core->set_samplerate(args.sampleRate);
	}

	core->update();

	for (auto &out : outJacks) {
		auto raw_value = core->get_output(out.getId());
		out.setValue(raw_value * 5.f); // TODO: Move scaling to SmartCoreProcessor or other wrapper
	}

	for (unsigned i = 0; auto &light : lights) {
		light.setBrightness(core->get_led_brightness(i));
		i++;
	}
}

void CommModule::configComm(unsigned NUM_PARAMS, unsigned NUM_INPUTS, unsigned NUM_OUTPUTS, unsigned NUM_LIGHTS) {
	config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

	for (unsigned i = 0; i < NUM_INPUTS; i++) {
		inJacks.push_back({inputs[i], i});
	}
	for (unsigned i = 0; i < NUM_OUTPUTS; i++) {
		outJacks.push_back({outputs[i], i});
	}
	core->mark_all_inputs_unpatched();
	core->mark_all_outputs_unpatched();
}
