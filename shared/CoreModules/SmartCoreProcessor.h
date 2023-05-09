#pragma once
#include "coreProcessor.h"
#include <array>


template <typename INFO>
class SmartCoreProcessor : public CoreProcessor
{
public:
	SmartCoreProcessor()
	{
	}	

protected:

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
		if (param_id < knobValues.size()) 
		{
			
			knobValues[param_id] = val;
		}
		else
		{
			param_id -= knobValues.size();
			if (param_id < switchValues.size())
			{
				switchValues[param_id] = val;
			}
		}
	}

	float get_led_brightness(int led_id) const override
	{
		// ignores switches with light for now
		if (led_id < ledValues.size())
		{
			return ledValues[led_id];	
		}
		else
		{
			return 0.0f;
		}
	}

protected:
	std::array<float,INFO::Knobs.size()> knobValues;
	std::array<float,INFO::InJacks.size()> inputValues;
	std::array<float,INFO::OutJacks.size()> outputValues;
	std::array<float,INFO::Switches.size()> switchValues;

	// ignores switches with light for now
	std::array<float,INFO::Leds.size()> ledValues;	
};
