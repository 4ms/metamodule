#pragma once

namespace LDKit::Mocks
{

struct InputPin
{
    void update()
    {
    }
	
    bool just_went_high()
    {
        if (value and not compareValue)
		{
			compareValue = true;
			return true;
		}
		return false;
    }

	bool just_went_low()
    {
        if (not value and compareValue)
		{
			compareValue = false;
			return true;
		}
		return false;
    }

	void sideload_set(bool val)
	{
		value = val;
	}

protected:
	bool value;
	bool compareValue;
};


struct MockedTrigger : public InputPin
{
	bool is_pressed() { return value; }
	bool is_just_released()  { return just_went_low(); }
    bool is_just_pressed()  { return just_went_high(); }
};

struct MockedButton : public MockedTrigger
{
	unsigned how_long_held() { return 0;}
	unsigned how_long_held_pressed() { return 0;}
};



enum class SwitchPos { Invalid = 0b00, Up = 0b01, Down = 0b10, Center = 0b11 };

struct MockedSwitch3Pos
{
	SwitchPos read()
	{
		return SwitchPos::Down;
	}
};

struct OutputPin
{
	void set(bool val)
	{
		if (val) high();
		else low();
	}

	void low()
	{
		value = false;
	}

	void high()
	{
		value = true;
	}

	bool sideload_get()
	{
		return value;
	}

private:
	bool value;
};

struct MockedLED : OutputPin
{
};


}
