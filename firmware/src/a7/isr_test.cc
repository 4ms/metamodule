#include "debug.hh"
#include "drivers/hsem.hh"
#include "drivers/pinchange.hh"

void test_nesting_isr()
{
	// Reset debug pins and LEDs
	Debug::red_LED1::high();
	Debug::red_LED2::high();
	Debug::green_LED1::high();
	Debug::green_LED2::high();
	Debug::Pin3::low();
	Debug::Pin2::low();
	Debug::Pin1::low();
	Debug::Pin0::low();

	// Pin 0: high indicates HSEM ISR running, low = not running
	// red_LED1 on = HSEM ISR reached
	InterruptManager::registerISR(HSEM_IT1_IRQn, 1, 0, [&]() {
		Debug::Pin0::high();
		for (int i = 0; i < 1000; i++)
			Debug::red_LED1::low();
		Debug::Pin0::low();
	});
	HWSemaphore<1>::disable_channel_ISR();
	HWSemaphore<1>::clear_ISR();
	target::System::enable_irq(HSEM_IT1_IRQn);
	HWSemaphore<1>::enable_channel_ISR();
	HWSemaphore<1>::lock();

	// Pin 1: high indicates Pinchange ISR is running, low = not running
	// red LED2 on = pinchange isr reached
	// Pinchange ISR = Debug 3 pin
	PinChangeInterrupt pcint;
	const PinChangeConfig pcconf = {
		.pin = Debug::Pin3::PinNum,
		.port = Debug::Pin3::Gpio,
		.on_rising_edge = true,
		.on_falling_edge = false,
		.priority1 = 2,
		.priority2 = 2,
	};
	pcint.init(pcconf, []() {
		Debug::Pin1::high();
		Debug::red_LED2::low();
		Debug::Pin1::low();
	});
	pcint.start();

	// Trigger ISRs
	// HWSemaphore<1>::unlock();
	Debug::Pin3::high();

	while (1) {
		Debug::Pin2::low();
		Debug::Pin2::high();
	}
}
