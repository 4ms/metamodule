#include "comm/comm_module.hh"
#include "c4/base64.hpp"

void CommModule::onSampleRateChange() {
	sampleRateChanged = true;
}

void CommModule::process(const ProcessArgs &args) {
	for (unsigned i = 0; auto &p : params) {

		// Transform VCV scaled values to MetaModule 0...1:
		// This is needed for 3-pos switches only
		auto val = getParamQuantity(i)->toScaled(p.getValue());

		core->set_param(i, val);
		i++;
	}

	for (auto &injack : inJacks) {
		auto id = injack.getId();
		injack.updateInput();

		if (injack.isJustPatched())
			core->mark_input_patched(id);

		if (injack.isJustUnpatched()) {
			core->mark_input_unpatched(id);
			core->set_input(id, 0); // 0 = unpatched value
		}

		if (injack.isConnected()) {
			auto scaledIn = injack.getValue();
			core->set_input(id, scaledIn);
		}
	}

	if (sampleRateChanged) {
		sampleRateChanged = false;
		core->set_samplerate(args.sampleRate);
	}

	// Patched state needs to be set before update
	// otherwise the first sample after patching can be undefined
	for (auto &out : outJacks) {

		auto id = out.getId();

		if (out.isConnected()) core->mark_output_patched(id);
		else                   core->mark_output_unpatched(id);
	}

	core->update();

	// Always set output independent of patch state
	// since when unpatched the value will not be used anyway
	for (auto &out : outJacks) {

		auto raw_value = core->get_output(out.getId());
		out.setValue(raw_value);
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

json_t *CommModule::dataToJson() {
	// Get state blob from module
	auto const state_data = core->save_state();

	// base64 encode it
	auto needed_size = c4::base64_encode({}, {state_data.data(), state_data.size()});
	std::string encoded_data(needed_size, '\0');
	c4::base64_encode({encoded_data.data(), encoded_data.size()}, {state_data.data(), state_data.size()});

	// serialize the base64 string
	json_t *rootJ = json_object();
	json_object_set_new(rootJ, "base64", json_string(encoded_data.c_str()));
	return rootJ;
}

void CommModule::dataFromJson(json_t *rootJ) {
	// Decode vcv patch json into a base64 string
	if (auto base64J = json_object_get(rootJ, "base64"); base64J) {
		if (auto base64_str = json_string_value(base64J); base64_str) {

			auto needed_size = c4::base64_decode(base64_str, {});
			std::vector<uint8_t> decoded_data(needed_size);
			c4::base64_decode(base64_str, {decoded_data.data(), decoded_data.size()});

			core->load_state(decoded_data);
		}
	}
}
