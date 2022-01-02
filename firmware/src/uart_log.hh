#include "drivers/uart.hh"

namespace MetaModule
{
struct UartLog {
	static inline mdrivlib::Uart<UART4_BASE> log_uart;
};
} // namespace MetaModule
