#include "main.hh"
#include "dig_inout_pins.hh"
#include "leds.h"
#include "settings.h"

namespace MetaModule::PEG
{


void MiniPEG::trigout_on() {
	if (!trigout_high) {
		DigIO::EOJack.high();
		set_led_brightness(kMaxBrightness, PWM_EOF_LED);
		trigout_high = 1;
		trigouttmr = 0;
	}
}
void MiniPEG::trigout_off() {
	if (!settings.trigout_is_trig && (trigouttmr > TRIGOUT_MIN_GATE_TIME)) {
		DigIO::EOJack.low();
		set_led_brightness(0, PWM_EOF_LED);
		trigouttmr = 0;
	}
	trigout_high = 0;
}

void MiniPEG::handle_trigout_trigfall() {
	if (settings.trigout_is_trig && trigouttmr > TRIGOUT_TRIG_TIME) {
		DigIO::EOJack.low();
		set_led_brightness(0, PWM_EOF_LED);
		trigouttmr = 0;
	}
}

//Todo: verify these are inlined by the compiler, otherwise explicity do it
void MiniPEG::eor_on() {
	if (settings.trigout_function == TRIGOUT_IS_ENDOFRISE)
		trigout_on();
}
void MiniPEG::eor_off() {
	if (settings.trigout_function == TRIGOUT_IS_ENDOFRISE)
		trigout_off();
}

void MiniPEG::eof_on() {
	if (settings.trigout_function == TRIGOUT_IS_ENDOFFALL)
		trigout_on();
}
void MiniPEG::eof_off() {
	if (settings.trigout_function == TRIGOUT_IS_ENDOFFALL)
		trigout_off();
}

void MiniPEG::hr_on() {
	if (settings.trigout_function == TRIGOUT_IS_HALFRISE)
		trigout_on();
}
void MiniPEG::hr_off() {
	if (settings.trigout_function == TRIGOUT_IS_HALFRISE)
		trigout_off();
}

void MiniPEG::tapclkout_on() {
	if (settings.trigout_function == TRIGOUT_IS_TAPCLKOUT)
		trigout_on();
}
void MiniPEG::tapclkout_off() {
	if (settings.trigout_function == TRIGOUT_IS_TAPCLKOUT)
		trigout_off();
}
void MiniPEG::clockbus_on() {
	DigIO::ClockBusOut.high();
}
void MiniPEG::clockbus_off() {
	DigIO::ClockBusOut.low();
}
}
