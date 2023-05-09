#pragma once
#include "coreProcessor.h"
#include <array>
#include <optional>


template <typename INFO>
class SmartCoreProcessor : public CoreProcessor
{
public:
	SmartCoreProcessor()
	{
	}	

protected:
	void setOutput(int i, float val)
	{
		outputValues[i] = val;
	}

	void setLED(int i, float val)
	{
		ledValues[i] = val;
	}

	std::optional<float> getInput(int i)
	{
		auto result = inputValues[i];
		inputValues[i].reset();
		return result;
	}

	float getKnob(int i)
	{
		return knobValues[i];
	}

	float getSwitch(int i)
	{
		return switchValues[i];
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

private:

	std::array<float,INFO::Knobs.size()> knobValues;
	std::array<std::optional<float>,INFO::InJacks.size()> inputValues;
	std::array<float,INFO::OutJacks.size()> outputValues;
	std::array<float,INFO::Switches.size()> switchValues;

	// ignores switches with light for now
	std::array<float,INFO::Leds.size()> ledValues;	
};
