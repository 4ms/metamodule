#pragma once

namespace LDKit::Mocks
{

struct MockedTrigger
{
	void update() {}
	bool is_pressed() { return false;}
	bool is_just_released()  { return false;}
    bool is_just_pressed()  { return false;}
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
	}

	void high()
	{
	}
};

struct MockedLED : OutputPin
{
};

struct InputPin
{
    void update()
    {

    }
    bool just_went_high()
    {
        return false;
    }
};

}
