#include "console.hh"
#include "conf/console_uart_conf.hh"
#include "conf/hsem_conf.hh"
#include "console/console_buffer_writer.hh"
#include "console/uart_log.hh"
#include "drivers/hsem.hh"
#include "drivers/system_reg.hh"
#include "drivers/uart.hh"
#include <array>

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

// Masks IRQs and FIQs (handlers can nest: see vectors.S)
struct IrqGuard {
	uint64_t daif = mdrivlib::read_daif();
	IrqGuard() {
		asm volatile("msr daifset, #3" ::: "memory");
	}
	~IrqGuard() {
		mdrivlib::write_daif(daif);
	}
};

// One per core
std::array<ConsoleBufferWriter<IrqGuard>, 2> writers;

ConsoleBufferWriter<IrqGuard> &this_core_writer() {
	return writers[std::min<uint64_t>(mdrivlib::get_mpid() & 0xFF, writers.size() - 1)];
}

void write_uart(const char *ptr, int len) {
	Lock lock;
	for (int i = 0; i < len; i++) {
		if (ptr[i] == '\n')
			uart.putchar('\r');
		uart.putchar(ptr[i]);
	}
}
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

bool core0_buffered() {
	return writers[0].attached();
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
	if (auto &writer = this_core_writer(); writer.attached())
		writer.write(ptr, len, true);
	else
		write_uart(ptr, len);
}

void MetaModule::UartLog::use_buffer(ConcurrentBuffer *buffer) {
	MetaModule::A35Console::this_core_writer().attach(buffer);
}

void MetaModule::UartLog::use_direct() {
	MetaModule::A35Console::this_core_writer().detach();
}
