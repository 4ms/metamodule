#ifndef _SRC_DRIVERS_HAL_CALLBACK
#define _SRC_DRIVERS_HAL_CALLBACK

#ifdef STM32F7
	#include "stm32f7xx.h"
#else
#endif
#include <functional>

enum class HALCallbackID {
	I2C_MemTxCplt,
	SAI_TxCplt,
	SAI_TxHalfCplt,

	MAX,
};
const int kMaxHALCallbackIDs = static_cast<uint32_t>(HALCallbackID::MAX);

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

struct HALCallback : public HALCallbackManager::HALCBBase {
	template<typename Func>
	HALCallback(HALCallbackID cbnum, const Func func)
		: func_(func)
	{
		HALCallbackManager::registerHALCB(cbnum, this);
	}
	virtual void halcb()
	{
		func_();
	}

private:
	const std::function<void(void)> func_;
};

#endif
