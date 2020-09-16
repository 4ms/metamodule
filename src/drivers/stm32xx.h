#ifdef STM32F7
	#include "stm32f7xx.h"
#else
	#ifdef STM32H7
		#include "stm32h7xx.h"
	#else
		#ifdef STM32F4
			#include "stm32f4xx.h"
		#else
			#error "Please #define STM32F4, STM32F7, or STM32H7 in a header or Makefile"
		#endif
	#endif
#endif

