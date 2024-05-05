//Todo: replace as many as possible with HAL_GetTicks() modulo some value
//
#include <stdint.h>

volatile uint32_t systmr = 0;
volatile uint32_t tapouttmr = 0;
volatile uint32_t tapintmr = 0;
volatile uint32_t pingtmr = 0;
volatile uint32_t trigouttmr = 0;

void inc_tmrs(void) {
	systmr++;
	tapouttmr++;
	tapintmr++;
	pingtmr++;
	trigouttmr++;
}
