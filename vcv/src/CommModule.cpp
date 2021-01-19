#include "CommModule.h"
#include "CommData.h"

CommModule::CommModule() {}

void CommModule::handleCommunication()
{
	if (centralData->getMyMessage(selfID.id) == CentralData::RequestAllParamData) {
		for (auto &p : commParams)
			centralData->updateParamStatus(p->paramStatus);

		for (auto &ins : inputJacks)
			centralData->updateJackStatus(ins->inputJackStatus);
	}
}

void CommModule::updateCommIDs(int id)
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
	centralData->registerModule(selfID);
}

void CommModule::onAdd()
{
	selfID.id = this->id;
	updateCommIDs(selfID.id);
}

void CommModule::onRemove()
{
	centralData->unregisterModule(selfID);
}

void CommModule::onSampleRateChange()
{
	// core->set_samplerate(args.sampleRate);
}
void CommModule::process(const ProcessArgs &args)
{
	for (auto &element : commParams) {
		element->updateValue();
		core->set_param(element->getID(), element->getValue());
	}

	for (auto &element : inputJacks) {
		element->updateInput();
		auto scaledIn = element->scale(element->getValue());
		core->set_input(element->getID(), scaledIn);
		if (element->inputJackStatus.connected) {
			core->mark_input_patched(element->getID());
		} else {
			core->mark_input_unpatched(element->getID());
		}
	}

	core->update();
	core->set_samplerate(args.sampleRate);

	for (auto &out : outputJacks) {
		out->setValue(out->scale(core->get_output(out->getID())));
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
	for (int i = 0; i < NUM_INPUTS; i++) {
		inputJacks.push_back(std::make_unique<CommInputJack>(inputs[i], i));
	}
	for (int i = 0; i < NUM_OUTPUTS; i++) {
		outputJacks.push_back(std::make_unique<CommOutputJack>(outputs[i], i));
	}
	for (int i = 0; i < NUM_PARAMS; i++) {
		commParams.push_back(std::make_unique<CommParam>(params[i], i));
	}
	_numLights = NUM_LIGHTS;
}

