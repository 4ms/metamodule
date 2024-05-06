#include "globals.h"
#include "stm32xx.h"

extern struct SystemSettings settings;
extern uint32_t clk_time;
extern uint8_t cycle_but_on;
extern bool adjusting_shift_mode;
extern bool toggled_sync_mode;

bool system_mode_active = false;

void handle_system_mode(bool sync_to_ping_mode) {
	uint8_t d;
	enum SystemModeParams system_mode_cur;
	static uint32_t ping_held_time = 0;
	static uint32_t cycle_held_time = 0;
	uint32_t now = HAL_GetTick();

	if (!is_pressed(CYCLE_BUTTON))
		cycle_held_time = now;

	if (adjusting_shift_mode || toggled_sync_mode)
		return;

	if ((now - cycle_held_time) <= (3000 * TICKS_PER_MS))
		return;

	// Enter System Mode
	for (d = 0; d < 5; d++) {
		set_rgb_led(LED_PING, c_WHITE);
		set_rgb_led(LED_CYCLE, c_WHITE);
		set_rgb_led(LED_ENVA, c_PURPLE);
		set_rgb_led(LED_ENVB, c_PURPLE);
		set_led_brightness(1024, PWM_EOF_LED);

		HAL_Delay(100);
		if (d == 4)
			HAL_Delay(500);

		set_rgb_led(LED_PING, c_OFF);
		set_rgb_led(LED_CYCLE, c_OFF);
		set_rgb_led(LED_ENVA, c_OFF);
		set_rgb_led(LED_ENVB, c_OFF);
		set_led_brightness(0, PWM_EOF_LED);

		HAL_Delay(100);
	}

	while (is_pressed(CYCLE_BUTTON)) {
		;
	}
	while (just_released(CYCLE_BUTTON))
		;
	HAL_Delay(50);

	ping_held_time = now;
	system_mode_cur = static_cast<SystemModeParams>(0);

	while (1) {
		system_mode_active = true;

		now = HAL_GetTick();

		// Hold either button to exit
		if (!is_pressed(PING_BUTTON))
			ping_held_time = now;
		else if ((now - ping_held_time) > (3000 * TICKS_PER_MS))
			break;

		if (!is_pressed(CYCLE_BUTTON))
			cycle_held_time = now;
		else if ((now - cycle_held_time) > (3000 * TICKS_PER_MS))
			break;

		//Cycle: go to next
		if (just_released(CYCLE_BUTTON)) {
			system_mode_cur = static_cast<SystemModeParams>(system_mode_cur + 1);
		}

		switch (system_mode_cur) {
			case (NUM_SYSMODE_PARAMS):
				system_mode_cur = static_cast<SystemModeParams>(0); //SET_TRIGIN_FUNC;
				break;

			case (SET_TRIGOUT_FUNC):
				set_led_brightness(1024, PWM_EOF_LED);
				if (settings.trigout_function == TRIGOUT_IS_ENDOFRISE)
					set_rgb_led(LED_PING, c_RED);
				else if (settings.trigout_function == TRIGOUT_IS_ENDOFFALL)
					set_rgb_led(LED_PING, c_ORANGE);
				else if (settings.trigout_function == TRIGOUT_IS_HALFRISE)
					set_rgb_led(LED_PING, c_GREEN);
				else if (settings.trigout_function == TRIGOUT_IS_TAPCLKOUT)
					set_rgb_led(LED_PING, c_WHITE);

				set_rgb_led(LED_CYCLE, c_OFF);
				set_rgb_led(LED_ENVA, c_OFF);
				set_rgb_led(LED_ENVB, c_OFF);
				break;

			case (SET_TRIGOUT_IS_TRIG):
				if (settings.trigout_is_trig) {
					set_rgb_led(LED_PING, c_WHITE);
					if (now & 0x0F0)
						set_led_brightness(0, PWM_EOF_LED);
					else
						set_led_brightness(1024, PWM_EOF_LED);
				} else {
					set_rgb_led(LED_PING, c_ORANGE);
					if (now & 0x100)
						set_led_brightness(0, PWM_EOF_LED);
					else
						set_led_brightness(1024, PWM_EOF_LED);
				}
				set_rgb_led(LED_CYCLE, c_OFF);
				set_rgb_led(LED_ENVA, c_OFF);
				set_rgb_led(LED_ENVB, c_OFF);
				break;

			case (SET_LIMIT_SKEW):
				set_rgb_led(LED_ENVA, c_BLUE);
				if (settings.limit_skew)
					set_rgb_led(LED_PING, c_WHITE);
				else
					set_rgb_led(LED_PING, c_ORANGE);

				set_rgb_led(LED_CYCLE, c_OFF);
				set_rgb_led(LED_ENVB, c_OFF);
				set_led_brightness(0, PWM_EOF_LED);
				break;

			case (SET_FREE_RUNNING_PING):
				if (settings.free_running_ping) {
					set_rgb_led(LED_PING, (now & 0x100) ? c_WHITE : c_OFF);
				} else {
					set_rgb_led(LED_PING, c_RED);
				}
				set_rgb_led(LED_CYCLE, c_OFF);
				set_rgb_led(LED_ENVA, c_OFF);
				set_rgb_led(LED_ENVB, c_OFF);
				set_led_brightness(0, PWM_EOF_LED);
				break;

			case (SET_TRIGIN_FUNCTION):
				set_led_brightness(1024, PWM_EOF_LED);
				set_rgb_led(LED_ENVA, c_RED);
				if (settings.trigin_function == TRIGIN_IS_QNT)
					set_rgb_led(LED_PING, c_BLUE);
				else if (settings.trigin_function == TRIGIN_IS_ASYNC)
					set_rgb_led(LED_PING, c_ORANGE);
				else if (settings.trigin_function == TRIGIN_IS_ASYNC_SUSTAIN)
					set_rgb_led(LED_PING, c_GREEN);

				set_rgb_led(LED_CYCLE, c_OFF);
				set_rgb_led(LED_ENVB, c_OFF);
				break;

			case (SET_CYCLEJACK_FUNCTION):
				if (settings.cycle_jack_behavior == CYCLE_JACK_RISING_EDGE_TOGGLES)
					set_rgb_led(LED_CYCLE, (now & 0x200) ? c_RED : c_OFF);
				else if (settings.cycle_jack_behavior == CYCLE_JACK_BOTH_EDGES_TOGGLES)
					set_rgb_led(LED_CYCLE, (now & 0x100) ? c_ORANGE : c_OFF);
				else if (settings.cycle_jack_behavior == CYCLE_JACK_BOTH_EDGES_TOGGLES_QNT)
					set_rgb_led(LED_CYCLE, (now & 0x100) ? c_BLUE : c_OFF);

				set_rgb_led(LED_PING, c_OFF);
				set_rgb_led(LED_ENVA, c_OFF);
				set_rgb_led(LED_ENVB, c_OFF);
				set_led_brightness(0, PWM_EOF_LED);
				break;
		}

		if (just_released(PING_BUTTON)) {

			HAL_Delay(50); //to de-noise the cycle button

			switch (system_mode_cur) {
				case (SET_TRIGOUT_FUNC):
					settings.trigout_function = static_cast<TrigOutFunctions>(settings.trigout_function + 1);
					if (settings.trigout_function >= NUM_TRIGOUT_FUNCTIONS)
						settings.trigout_function = TRIGOUT_IS_ENDOFRISE;
					break;

				case (SET_TRIGOUT_IS_TRIG):
					settings.trigout_is_trig = settings.trigout_is_trig ? 0 : 1;
					break;

				case (SET_LIMIT_SKEW):
					settings.limit_skew = settings.limit_skew ? 0 : 1;
					break;

				case (SET_FREE_RUNNING_PING):
					settings.free_running_ping = settings.free_running_ping ? 0 : 1;
					break;

				case (SET_TRIGIN_FUNCTION):
					settings.trigin_function = static_cast<TrigInFunctions>(settings.trigin_function + 1);
					if (settings.trigin_function >= NUM_TRIGIN_FUNCTIONS)
						settings.trigin_function = TRIGIN_IS_ASYNC;
					break;

				case (SET_CYCLEJACK_FUNCTION):
					settings.cycle_jack_behavior = static_cast<CycleJackBehaviors>(settings.cycle_jack_behavior + 1);
					if (settings.cycle_jack_behavior >= NUM_CYCLEJACK_BEHAVIORS)
						settings.cycle_jack_behavior = CYCLE_JACK_RISING_EDGE_TOGGLES;
					break;
				default:
					break;
			}
		}
	}

	// Save if we exited by holding Ping
	if (is_pressed(PING_BUTTON)) {
		settings.start_clk_time = clk_time;
		settings.start_cycle_on = cycle_but_on;
		settings.start_sync_on = sync_to_ping_mode;

		write_settings();
	}

	while (is_pressed(CYCLE_BUTTON) || is_pressed(PING_BUTTON)) {
		set_rgb_led(LED_PING, c_WHITE);
		set_rgb_led(LED_CYCLE, c_WHITE);
		set_rgb_led(LED_ENVA, c_PURPLE);
		set_rgb_led(LED_ENVB, c_PURPLE);
		set_led_brightness(1024, PWM_EOF_LED);

		HAL_Delay(50);

		set_rgb_led(LED_PING, c_OFF);
		set_rgb_led(LED_CYCLE, c_OFF);
		set_rgb_led(LED_ENVA, c_OFF);
		set_rgb_led(LED_ENVB, c_OFF);
		set_led_brightness(0, PWM_EOF_LED);

		HAL_Delay(50);
	}

	//clear edges:
	while (just_released(CYCLE_BUTTON))
		;
	while (just_released(PING_BUTTON))
		;

	//restore lights:
	if (cycle_but_on)
		set_rgb_led(LED_CYCLE, c_ORANGE);

	system_mode_active = false;
}
