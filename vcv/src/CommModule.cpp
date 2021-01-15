#include "CommModule.h"
#include "CommData.h"

CommModule::CommModule()
{
	leftExpander.producerMessage = &leftMessages[0];
	leftExpander.consumerMessage = &leftMessages[1];
	rightExpander.producerMessage = &rightMessages[0];
	rightExpander.consumerMessage = &rightMessages[1];

	recdFromRightData.messageType = NoMessage;
	recdFromLeftData.messageType = NoMessage;
}

void CommModule::handleCommunication()
{
	if (centralData->getMyMessage(selfID.id) == CentralData::RequestAllParamData) {
		for (auto &p : commParams)
			centralData->updateParamStatus(p->paramStatus);

		for (auto &ins : inputJacks)
			centralData->updateJackStatus(ins->inputJackStatus);
	}

	// if (rightExpander.module) {
	// 	sendToRight();
	// 	readFromRight();
	// }

	// if (leftExpander.module) {
	// 	sendToLeft();
	// 	readFromLeft();
	// } else {
	// 	if (recdFromRightData.messageType == GetAllIDs) {
	// 		initiateStatusDumpToRight();
	// 	}
	// }
}

void CommModule::updateCommIDs(int id)
{
	if (!alreadyUpdatedIDs) {
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
		alreadyUpdatedIDs = true;
	}
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
	}

	for (auto &element : outputJacks) {
		element->updateOutput();
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

void CommModule::sendToRight()
{
	auto message = messageToSendRight();

	if (pushIDsPending) {
		pushIDsPending = false;

		message->moduleData.clear();
		message->jackData.clear();
		message->paramData.clear();
		appendModuleID(message);
		appendJackData(message);
		appendParamData(message);
		message->messageType = SendingIDs;

		rightExpander.module->leftExpander.messageFlipRequested = true;
	} else if (recdFromLeftData.messageType == SendingIDs) {
		*message = std::move(recdFromLeftData);
		appendModuleID(message);
		appendJackData(message);
		appendParamData(message);
		message->messageType = SendingIDs;

		recdFromLeftData.messageType = NoMessage;

		rightExpander.module->leftExpander.messageFlipRequested = true;
	}
}

void CommModule::readFromRight()
{
	auto recMessage = messageReceivedFromRight();
	if (recMessage->messageType == GetAllIDs) {
		recdFromRightData.messageType = GetAllIDs;
		recMessage->messageType = NoMessage;
	}
}

void CommModule::initiateStatusDumpToRight()
{
	pushIDsPending = true;
	recdFromRightData.messageType = NoMessage;
}

void CommModule::sendToLeft()
{
	auto message = messageToSendLeft();

	if (recdFromRightData.messageType == GetAllIDs) {
		recdFromRightData.messageType = NoMessage;
		message->messageType = GetAllIDs;
		leftExpander.module->rightExpander.messageFlipRequested = true;
	}
}

void CommModule::readFromLeft()
{
	auto recMessage = messageReceivedFromLeft();

	if (recMessage->messageType == SendingIDs) {
		recdFromLeftData = std::move(*recMessage);
		recMessage->messageType = NoMessage;
	}
}

void CommModule::appendModuleID(CommData *message)
{
	message->moduleData.push_back(selfID);
}

void CommModule::appendJackData(CommData *message)
{
	for (auto &jack : inputJacks) {
		message->jackData.push_back(jack->inputJackStatus);
	}
}
void CommModule::appendParamData(CommData *message)
{
	for (auto &param : commParams) {
		message->paramData.push_back(param->paramStatus);
	}
}

void CommModule::notifyLabelButtonClicked(LabelButtonID id)
{
	// todo
	// Send message to the hub that a label was clicked
}

// LabelState CommModule::getLabelButtonState(LabelButtonID id)
// {
// 	return LabelState::Normal;
// }
