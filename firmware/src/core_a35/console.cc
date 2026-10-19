#include "console.hh"
#include "conf/console_uart_conf.hh"
#include "conf/hsem_conf.hh"
#include "console/uart_log.hh"
#include "drivers/hsem.hh"
#include "drivers/uart.hh"

namespace MetaModule::A35Console
{

namespace
{
mdrivlib::Uart<LogUartConfig> uart;
bool hsem_ready = false;

struct Lock {
	using UartSem = mdrivlib::HWSemaphore<UartLock>;

	Lock() {
		if (hsem_ready) {
			while (UartSem::lock(UartLockA7Core0) != mdrivlib::HWSemaphoreFlag::LockedOk)
				;
		}
	}

	~Lock() {
		if (hsem_ready)
			UartSem::unlock(UartLockA7Core0);
	}
};
} // namespace

void init() {
	uart.init();
}

void use_hsem_lock() {
	hsem_ready = true;
}

void write(const char *str) {
	Lock lock;
	uart.write(str);
}

bool receive(uint8_t &c) {
	auto usart = reinterpret_cast<USART_TypeDef *>(LogUartConfig.base_addr);
	// Characters that arrived while the RX FIFO was full are lost: clear the overrun flag
	if (usart->ISR & USART_ISR_ORE)
		usart->ICR = USART_ICR_ORECF;
	return uart.receive(&c);
}

} // namespace MetaModule::A35Console

// printf() etc. output (pr_err(), pr_info(), ...): newlib's _write() calls this for stdout and
// stderr (src/fs/syscall)
void MetaModule::UartLog::write_stdout(const char *ptr, int len) {
	using namespace MetaModule::A35Console;
	Lock lock;
	for (int i = 0; i < len; i++) {
		if (ptr[i] == '\n')
			uart.putchar('\r');
		uart.putchar(ptr[i]);
	}
}
