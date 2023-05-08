#include "comm_module.hh"
#include "hub/central_data.hh"

CommModule::CommModule() {}

void CommModule::handleCommunication()
{
	if (_comm_status == PropagateData2) {
		for (auto &p : commParams)
			centralData->updateParamStatus(p->paramStatus);
	}

	if (_comm_status == PropagateData2) {
		for (auto &ins : inputJacks) {
			ins->updateWithCommData();
			centralData->updateJackStatus(ins->inputJackStatus);
		}
	}

	if (_comm_status != Normal) {
		for (auto &out : outputJacks)
			out->updateOutputWithCommData();
	}
}

void CommModule::setModuleId(int64_t id)
{
	for (auto &el : inputJacks) {
		el->setModuleID(id);
	}
	for (auto &el : outputJacks) {
		el->setModuleID(id);
	}
	for (auto &el : commParams) {
		el->setModuleID(id);
	}
}

void CommModule::onAdd()
{
	selfID.id = this->id;
	setModuleId(selfID.id);
	centralData->registerModule(selfID, this);
}

void CommModule::onRemove() { centralData->unregisterModule(selfID); }

void CommModule::onSampleRateChange() { _sample_rate_changed = true; }

void CommModule::process(const ProcessArgs &args)
{
	if (centralData->getMyMessage(selfID.id) == CentralData::RequestAllParamData) {
		_comm_status = StartSending;
	} else if (_comm_status == StartSending)
		_comm_status = PropagateData1;
	else if (_comm_status == PropagateData1)
		_comm_status = PropagateData2;
	else if (_comm_status == PropagateData2)
		_comm_status = Normal;

	for (auto &param : commParams) {
		param->updateValue();
		core->set_param(param->getID(), param->getValue());
	}

	for (auto &alt : altParams) {
		if (alt.is_updated)
			core->set_alt_param(alt.id, alt.val);
		alt.is_updated = false;
	}

	for (auto &injack : inputJacks) {
		injack->updateInput();

		if (injack->isJustPatched())
			core->mark_input_patched(injack->getID());

		if (injack->isJustUnpatched()) {
			core->set_input(injack->getID(), 0); // 0 = unpatched value. TODO: allow for normalizations
			core->mark_input_unpatched(injack->getID());
		}

		if (injack->inputJackStatus.connected) {
			auto scaledIn = injack->getValue() * injack->scaleFactor;
			core->set_input(injack->getID(), scaledIn);
		}
	}

	core->update();

	if (_sample_rate_changed) {
		core->set_samplerate(args.sampleRate);
		_sample_rate_changed = false;
	}

	for (auto &out : outputJacks) {
		out->setValue(core->get_output(out->getID()) * out->scaleFactor);
		out->updateOutput();
	}

	for (int i = 0; i < _numLights; i++) {
		lights[i].setBrightness(core->get_led_brightness(i));
	}

	handleCommunication();
}

void CommModule::configComm(int NUM_PARAMS, int NUM_INPUTS, int NUM_OUTPUTS, int NUM_LIGHTS)
{
	config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	_numLights = NUM_LIGHTS;

	for (int i = 0; i < NUM_INPUTS; i++) {
		inputJacks.push_back(std::make_unique<CommInputJack>(inputs[i], i));
	}
	for (int i = 0; i < NUM_OUTPUTS; i++) {
		outputJacks.push_back(std::make_unique<CommOutputJack>(outputs[i], i));
	}
	for (int i = 0; i < NUM_PARAMS; i++) {
		commParams.push_back(std::make_unique<CommParam>(params[i], i));
	}
}
