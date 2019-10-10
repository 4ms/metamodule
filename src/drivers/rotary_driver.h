/*
* rotary_driver.h - drivers for rotary encoders
*
* State machine table taken from code copyright 2011 Ben Buxton (bb@cactii.net) and licenced under the GNU GPL Version 3.
*
* Conversion for use with STM32 in 2015 by: Dan Green (danngreen1@gmail.com)
*
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
* 
* -----------------------------------------------------------------------------
*/


#pragma once

#include <stm32f7xx.h>


enum PinTypes {
	PULLUP, 				// 0
	PULLDOWN,	  			// 1
	NOPULL,					// 2
	DISABLED,				// 3
	
	NUM_PIN_TYPES
};

enum StepTypes {
	HALFSTEP, 				// 0
	FULLSTEP,	  			// 1

	NUM_STEP_TYPES
};

enum PressTypes {
	RELEASED, 				// 0
	PRESSED,				// 1
	SHORT_PRESSED,  		// 2
	MED_PRESSED,  			// 3
	LONG_PRESSED,  			// 4
	UNKNOWN_PRESS,			// 5

	NUM_PRESS_TYPES
};


typedef struct o_switch {
	enum PressTypes		pressed;
	GPIO_TypeDef 	   *gpio;
	uint32_t			pin;
	enum PinTypes		ptype; 	
} o_switch;


typedef struct o_turn {
	uint8_t				state;
	int8_t				queue;
	GPIO_TypeDef 	   *A_gpio;
	uint32_t			A_pin;
	GPIO_TypeDef 	   *B_gpio;
	uint32_t			B_pin;
	enum StepTypes 		step_size; 
} o_turn;

typedef struct o_rotary {
	o_turn				turn;
	o_switch			hwswitch;
} o_rotary;


#define R_START 0x0

// Values returned by 'process'
#define DIR_NONE 	0x0 	// No complete step yet.
#define DIR_CW 		0x10 	// Clockwise step.
#define DIR_CCW 	0x20	// Anti-clockwise step.

void 	init_rotary_turn(o_turn *turn_object);
int8_t 	read_rotary_turn(o_rotary *rotary_object);
void 	update_rotary_queue(o_turn *turn_object);
int8_t 	pop_rotary_queue(o_turn *turn_object);
uint8_t read_rotary_press(o_rotary *rotary_object);
