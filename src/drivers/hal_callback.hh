#ifndef _SRC_DRIVERS_HAL_CALLBACK
#define _SRC_DRIVERS_HAL_CALLBACK

#ifdef STM32F7
	#include "stm32f7xx.h"
#else
#endif

enum class HALCallbackID {
	I2C_MemTxCplt,
	SAI_TxCplt,
	SAI_TxHalfCplt,
};

const int kMaxHALCallbackIDs = 3;

class HALCallbackManager {
public:
	struct HALCBBase {
		virtual void halcb() = 0;
	};
	using HALCBType = HALCBBase *;
	static inline void registerHALCB(HALCallbackID cbnum, HALCBType cb_obj)
	{
		HALCBs[get_cb_int(cbnum)] = cb_obj;
	}
	static inline void callHALCB(HALCallbackID cbnum)
	{
		HALCBs[get_cb_int(cbnum)]->halcb();
	}
	static uint8_t constexpr get_cb_int(HALCallbackID cbnum)
	{
		return static_cast<uint8_t>(cbnum);
	}

private:
	static inline HALCBType HALCBs[kMaxHALCallbackIDs];
};

#endif
