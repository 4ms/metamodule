//#include "debug.hh"
#include "drivers/pin.hh"
#include "drivers/register_access.hh"

void main()
{
	FPin<GPIO::I, 8, PinMode::Output> red_LED2_init;
	FPin<GPIO::I, 9, PinMode::Output> green_LED2_init;

	while (1) {
		FPin<GPIO::I, 8, PinMode::Output>::low();
		for (int i = 0; i < 5000000; i++) { // 100000 = 75Hz
		}
		FPin<GPIO::I, 8, PinMode::Output>::high();

		FPin<GPIO::I, 9, PinMode::Output>::low();
		for (int i = 0; i < 5000000; i++) {
		}
		FPin<GPIO::I, 9, PinMode::Output>::high();
	}
}
