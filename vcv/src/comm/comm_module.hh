#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "comm/comm_jack.hh"

// CommModule wraps CoreProcessors for use in VCV Rack

class CommModule : public rack::Module {
public:
	struct AltParam {
		bool is_updated = false;
		unsigned id;
		float val;
	};

	std::unique_ptr<CoreProcessor> core;
	std::vector<AltParam> altParams;
	std::vector<CommInputJack> inJacks;
	std::vector<CommOutputJack> outJacks;

private:
	bool sampleRateChanged = true;

protected:
	CommModule() = default;
	~CommModule() = default;

	void configComm(unsigned NUM_PARAMS, unsigned NUM_INPUTS, unsigned NUM_OUTPUTS, unsigned NUM_LIGHTS);
	void process(const ProcessArgs &args) override;
	void onSampleRateChange() override;
};
