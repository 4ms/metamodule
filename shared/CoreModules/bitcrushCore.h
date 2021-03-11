#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "processors/bit_crush.h"
#include "util/math.hh"

using namespace MathTools;

class BitcrushCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		if(bCvConnected==false)
		bCV=0;
		if(srCvConnected==false)
		srCV=0;
		auto finalSR = constrain(srOffset + srCV, 0.0f, 1.0f);
		auto finalBit = constrain(bOffset + bCV, 0.0f, 1.0f);
		bc.set_param(0, finalSR);
		bc.set_param(1, finalBit);
		signalOutput = bc.update(signalInput);
	}

	BitcrushCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		if (param_id == 0) {
			srOffset = val;
		} else if (param_id == 1) {
			bOffset = val;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		bc.set_samplerate(sr);
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				signalInput = val;
				break;
			case 1:
				srCV = val;
				break;
			case 2:
				bCV = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = signalOutput;
				break;
		}
		return output;
	}

	virtual void mark_input_unpatched(const int input_id) override
	{
		if (input_id == 1) {
			srCvConnected = false;
		} else if (input_id == 2) {
			bCvConnected = false;
		}
	}
	virtual void mark_input_patched(const int input_id) override
	{
		if (input_id == 1) {
			srCvConnected = true;
		} else if (input_id == 2) {
			bCvConnected = true;
		}
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<BitcrushCore>();
	}
	static constexpr char typeID[20] = "BITCRUSH";
	static constexpr char description[] = "Bit Crusher";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	BitCrusher bc;

	float signalInput = 0;
	float signalOutput = 0;

	float srOffset = 0;
	float bOffset = 0;
	float srCV = 0;
	float bCV = 0;

	bool srCvConnected = false;
	bool bCvConnected = false;
};
