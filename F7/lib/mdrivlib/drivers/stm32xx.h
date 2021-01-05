#ifdef STM32F7
	#include "stm32f7xx.h"
#else
	#ifdef STM32H7
		#include "stm32h7xx.h"
	#else
		#ifdef STM32F4
			#include "stm32f4xx.h"
		#else
			#ifdef STM32MP1
				#ifdef CORE_CM4
					#include "stm32mp1xx.h"
				#else
					#error "STM32MP1 is defined, but not CORE_CM4. This library does not support Cortex-A cores"
				#endif
			#else
				#error "Please #define STM32F4, STM32F7, STM32H7, or STM32MP1 in a header or Makefile"
			#endif
		#endif
	#endif
#endif

