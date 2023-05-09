#pragma once
#include "coreProcessor.h"
#include <vector>


template <typename INFO>
class SmartCoreProcessor : public CoreProcessor
{
public:
	SmartCoreProcessor()
	{
		knobValues.reserve(INFO::Knobs.size());
		inputValues.reserve(INFO::InJacks.size());
		outputValues.reserve(INFO::OutJacks.size());
		switchValues.reserve(INFO::Switches.size());

		// ignores switches with light for now
		ledValues.reserve(INFO::Leds.size());
	}

	float get_output(int output_id) const override
	{
		return outputValues[output_id] / 5.0f;
	}

	void set_input(int input_id, float val) override
	{
		inputValues[input_id] = val * 5.0f;
	}

	void set_param(int param_id, float val) override
	{
		// Here we are assuming how params are merged in a different place
		if (param_id < knobValues.capacity()) 
		{
			
			knobValues[param_id] = val;
		}
		else
		{
			param_id -= knobValues.capacity();
			if (param_id < switchValues.capacity())
			{
				switchValues[param_id] = val;
			}
		}
	}

	float get_led_brightness(int led_id) const override
	{
		// ignores switches with light for now
		if (led_id < ledValues.capacity())
		{
			return ledValues[led_id];	
		}
		else
		{
			return 0.0f;
		}
	}

protected:
	std::vector<float> knobValues;
	std::vector<float> inputValues;
	std::vector<float> outputValues;
	std::vector<float> switchValues;
	std::vector<float> ledValues;	
};
