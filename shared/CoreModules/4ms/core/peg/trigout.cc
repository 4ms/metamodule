#include "dig_inout_pins.hh"
#include "flash_user.hh"
#include "leds.h"
#include "settings.h"

uint8_t trigout_high = 0;
extern volatile uint32_t trigouttmr;
extern struct SystemSettings settings;

static void trigout_on();
static void trigout_off();

void trigout_on() {
	if (!trigout_high) {
		DigIO::EOJack::high();
		set_led_brightness(kMaxBrightness, PWM_EOF_LED);
		trigout_high = 1;
		trigouttmr = 0;
	}
}
void trigout_off() {
	if (!settings.trigout_is_trig && (trigouttmr > TRIGOUT_MIN_GATE_TIME)) {
		DigIO::EOJack::low();
		set_led_brightness(0, PWM_EOF_LED);
		trigouttmr = 0;
	}
	trigout_high = 0;
}

void handle_trigout_trigfall() {
	if (settings.trigout_is_trig && trigouttmr > TRIGOUT_TRIG_TIME) {
		DigIO::EOJack::low();
		set_led_brightness(0, PWM_EOF_LED);
		trigouttmr = 0;
	}
}

//Todo: verify these are inlined by the compiler, otherwise explicity do it
void eor_on() {
	if (settings.trigout_function == TRIGOUT_IS_ENDOFRISE)
		trigout_on();
}
void eor_off() {
	if (settings.trigout_function == TRIGOUT_IS_ENDOFRISE)
		trigout_off();
}

void eof_on() {
	if (settings.trigout_function == TRIGOUT_IS_ENDOFFALL)
		trigout_on();
}
void eof_off() {
	if (settings.trigout_function == TRIGOUT_IS_ENDOFFALL)
		trigout_off();
}

void hr_on() {
	if (settings.trigout_function == TRIGOUT_IS_HALFRISE)
		trigout_on();
}
void hr_off() {
	if (settings.trigout_function == TRIGOUT_IS_HALFRISE)
		trigout_off();
}

void tapclkout_on() {
	if (settings.trigout_function == TRIGOUT_IS_TAPCLKOUT)
		trigout_on();
}
void tapclkout_off() {
	if (settings.trigout_function == TRIGOUT_IS_TAPCLKOUT)
		trigout_off();
}
void clockbus_on() {
	DigIO::ClockBusOut::high();
}
void clockbus_off() {
	DigIO::ClockBusOut::low();
}
