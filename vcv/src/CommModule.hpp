#pragma once
#include "CommData.hpp"
#include "CommJackParam.hpp"
#include "CoreModules/coreProcessor.h"
#include "plugin.hpp"

class CommModule : public Module {
public:
	std::function<void(void)> updateDisplay;
	std::string DEBUGSTR = "";
	std::unique_ptr<CoreProcessor> core;

protected:
	ModuleID selfID;
	std::vector<std::unique_ptr<CommParam>> commParams;
	std::vector<std::unique_ptr<CommOutputJack>> outputJacks;
	std::vector<std::unique_ptr<CommInputJack>> inputJacks;

private:
	int _numLights = 0;
	bool _sample_rate_changed = true;
	enum CommStatus { Normal = 0, StartSending, PropagateData1, PropagateData2 } _comm_status;

protected:
	CommModule();
	~CommModule() = default;

	void configComm(int NUM_PARAMS, int NUM_INPUTS, int NUM_OUTPUTS, int NUM_LIGHTS);
	virtual void process(const ProcessArgs &args) override;
	virtual void onAdd() override;
	virtual void onRemove() override;
	virtual void onSampleRateChange() override;

private:
	void updateCommIDs(int id);
	void handleCommunication();
};
