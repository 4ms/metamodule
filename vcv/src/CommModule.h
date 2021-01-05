#pragma once

#include "CommData.h"
#include "CommJackParam.h"
#include "CoreModules/coreProcessor.h"
#include "plugin.hpp"

class CommModule : public Module {
public:
	std::function<void(void)> updateDisplay;
	std::string DEBUGSTR = "";

protected:
	ModuleID selfID;
	std::vector<std::unique_ptr<CommParam>> commParams;
	std::vector<std::unique_ptr<CommOutputJack>> outputJacks;
	std::vector<std::unique_ptr<CommInputJack>> inputJacks;

	std::unique_ptr<CoreProcessor> core;

private:
	CommData recdFromLeftData;
	CommData recdFromRightData;
	bool pushIDsPending = false;

	CommData leftMessages[2];
	CommData rightMessages[2];
	bool alreadyUpdatedIDs = false;

protected:
	CommModule();
	~CommModule() = default;

	void configComm(int NUM_PARAMS, int NUM_INPUTS, int NUM_OUTPUTS, int NUM_LIGHTS);
	void updateCommIDs(int id);
	void handleCommunication();
	virtual void process(const ProcessArgs &args) override;

	CommData *messageToSendRight()
	{
		return static_cast<CommData *>(rightExpander.module->leftExpander.producerMessage);
	}
	CommData *messageReceivedFromRight()
	{
		return static_cast<CommData *>(rightExpander.consumerMessage);
	}
	CommData *messageToSendLeft()
	{
		return static_cast<CommData *>(leftExpander.module->rightExpander.producerMessage);
	}
	CommData *messageReceivedFromLeft()
	{
		return static_cast<CommData *>(leftExpander.consumerMessage);
	}

private:
	void sendToRight();
	void readFromRight();
	void initiateStatusDumpToRight();
	void sendToLeft();
	void readFromLeft();
	void appendModuleID(CommData *message);
	void appendJackData(CommData *message);
	void appendParamData(CommData *message);
};

