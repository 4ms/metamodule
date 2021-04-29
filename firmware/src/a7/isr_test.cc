#include "debug.hh"
#include "drivers/hsem.hh"
#include "drivers/interrupt.hh"
#include "drivers/pinchange.hh"

// Test nested interrupts.
//
// Debug Pin 0 should emit a long high pulse
// While Debug Pin 0 is still high, Debug Pin 1 should go high for a short pulse
// Assert: Debug Pin 0 goes high, then low while Debug Pin 1 is still high
// Assert: Debug Pin 2 toggle infinitely immediately after Debug Pin 1 goes low
//
// Additional tests: Swap priority of two ISRs and verify Debug Pin 0 goes high and low before Debug Pin 1 goes high.
//
// Debug Pin 0: high indicates Semaphore ISR running, low = not running
// red_LED1 on = Semaphore ISR reached
// Debug Pin 1: high indicates Pinchange ISR is running, low = not running
// red LED2 on = pinchange isr reached
// Debug Pin 2: toggling indicates non-ISR level code is running
// Debug Pin 3: used to create a PinChange interrupt
void test_nesting_isr()
{
	// Reset debug pins and LEDs to a known state
	Debug::red_LED1::high();
	Debug::red_LED2::high();
	Debug::Pin3::low();
	Debug::Pin2::low();
	Debug::Pin1::low();
	Debug::Pin0::low();

	constexpr uint32_t TestSemaphoreID = 1;
	constexpr IRQType TestSemaphoreIRQn = HSEM_IT1_IRQn;

	// Create callback for low-priority ISR (Semaphore unlocked)
	// which triggers the high-priority ISR from within it
	InterruptManager::registerISR(TestSemaphoreIRQn, 3, 3, [&]() {
		if (HWSemaphore<TestSemaphoreID>::is_ISR_triggered_and_enabled()) {
			Debug::Pin0::high();
			for (int i = 0; i < 800; i++) {
				if (i == 50)
					Debug::Pin3::high();
				Debug::red_LED1::low();
			}
			Debug::Pin0::low();
			HWSemaphore<TestSemaphoreID>::clear_ISR();
		}
	});
	// Clear pending interrupts and enable the channel
	HWSemaphore<TestSemaphoreID>::disable_channel_ISR();
	HWSemaphore<TestSemaphoreID>::clear_ISR();
	target::System::enable_irq(TestSemaphoreIRQn);
	HWSemaphore<TestSemaphoreID>::enable_channel_ISR();
	HWSemaphore<TestSemaphoreID>::lock();

	// Create callback for high-priority ISR (Pinchange ISR = Debug 3 pin goes high)
	PinChangeInterrupt pcint;
	const PinChangeConfig pcconf = {
		.pin = Debug::Pin3::PinNum_v,
		.port = Debug::Pin3::Gpio_v,
		.on_rising_edge = true,
		.on_falling_edge = false,
		.priority1 = 0,
		.priority2 = 0,
	};
	pcint.init(pcconf, []() {
		Debug::Pin1::high();
		Debug::red_LED2::low();
		Debug::Pin1::low();
	});
	// Enable interrupt
	pcint.start();

	// Trigger the low-priority ISR
	HWSemaphore<TestSemaphoreID>::unlock();

	// Loop forever
	while (1) {
		Debug::Pin2::low();
		Debug::Pin2::high();
	}
}
