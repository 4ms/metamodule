#include "uart_log.hh"
#include "conf/hsem_conf.hh"
#include "drivers/hsem.hh"
#include "drivers/rcc.hh"
#include <algorithm>
#include <array>
#include <cstdarg>
#include <cstdio>

namespace MetaModule
{

namespace
{
uint32_t core_id() {
	// The A7 instance of UartLog serves two cores; the M4 instance uses index 0
#ifdef CORE_CA7
	return std::min<uint32_t>(__get_MPIDR() & 0xFF, UartLog::NumCores - 1);
#else
	return 0;
#endif
}

bool spin_lock() {
#ifdef CORE_CA7
	auto cid = __get_MPIDR() & 0xFF;
#else
	auto cid = 2;
#endif
	uint32_t tmout = 800'000'000;
	while (mdrivlib::HWSemaphore<UartLock>::lock(cid) != mdrivlib::HWSemaphoreFlag::LockedOk) {
		if (--tmout == 0)
			return false;
	}
	return true;
}

void unlock() {
#ifdef CORE_CA7
	auto cid = __get_MPIDR() & 0xFF;
#else
	auto cid = 2;
#endif
	mdrivlib::HWSemaphore<UartLock>::unlock(cid);
}

uint32_t disable_irqs() {
#ifdef CORE_CA7
	auto irqs_masked = __get_CPSR() & CPSR_I_Msk;
	__disable_irq();
	return irqs_masked;
#else
	auto irqs_masked = __get_PRIMASK();
	__disable_irq();
	return irqs_masked;
#endif
}

void restore_irqs(uint32_t irqs_were_masked) {
	if (!irqs_were_masked)
		__enable_irq();
}

// Not shared between cores, but must align to cache lines or else two A7 cores could ping-pong
struct alignas(64) WriteState {
	std::atomic<uint32_t> reserve_pos{0}; // next free byte; all of [write_pos, reserve_pos) is claimed
	std::atomic<uint32_t> depth{0};		  // how many writes on this core are in flight (nested)
};

std::array<WriteState, UartLog::NumCores> write_state;

void write_reserved(ConcurrentBuffer *buff, WriteState &st, const char *ptr, size_t len) {
	// Disable interrupts for ~5 instructions to reserve a block we'll write into
	auto irqs = disable_irqs();
	// Keep track of the nested interrupt depth (only the lowest level publishes)
	st.depth = st.depth + 1;
	const uint32_t start = st.reserve_pos;
	// Reserve what we need, then restore interrupts
	st.reserve_pos = start + len;
	restore_irqs(irqs);

	buff->copy_in({ptr, len}, start);

	// Disable interrupts again to publish the block (which just bumps the pos up)
	irqs = disable_irqs();
	// Only the outermost caller needs to publish since this will write all inner callers too
	if (st.depth == 1)
		buff->publish(st.reserve_pos);
	st.depth = st.depth - 1;
	restore_irqs(irqs);
}

#ifdef CORE_CA7
// Wait until M4 has drained the buffer enough for us to write. Times out if M4 is hung.
void wait_for_space(ConcurrentBuffer *buff, WriteState &st, uint32_t len) {
	uint32_t spins = 500'000'000; // very roughly seconds at 800MHz
	while ((st.reserve_pos - buff->read_pos) + len > ConcurrentBuffer::Size) {
		if (--spins == 0)
			return;
	}
}
#endif

} // namespace

void UartLog::init() {
	uart_regs();
}

USART_TypeDef *UartLog::uart_regs() {
#ifdef CORE_CA7
	return log_uart.uart();
#else
	// Let A7 enable UART, M4 just enables the clock
	[[maybe_unused]] static bool once = [] {
		mdrivlib::core_m4::RCC_Enable::UART7_::set();
		return true;
	}();
	return reinterpret_cast<USART_TypeDef *>(LogUartConfig.base_addr);
#endif
}

void UartLog::putchar(char c) {
	auto uart = uart_regs();
	uart->TDR = c;
	while ((uart->ISR & USART_ISR_TXFE) == 0)
		;
}

void UartLog::log(const char *format, ...) {
	va_list va;
	va_start(va, format);
	vprintf(format, va);
	va_end(va);
}

void UartLog::use_buffer(ConcurrentBuffer *buffer) {
	auto core = core_id();
	write_state[core].reserve_pos.store(buffer->write_pos.load());
	write_state[core].depth.store(0);
	log_buff[core] = buffer;
	mode[core] = Mode::Buffered;
}

void UartLog::use_direct() {
	mode[core_id()] = Mode::Direct;
}

void UartLog::puts(const char *ptr) {
	if (spin_lock()) {
		while (*ptr) {
			UartLog::putchar(*ptr++);
		}
		unlock();
	}
}

void UartLog::write_uart(const char *ptr, size_t len) {
	if (spin_lock()) {
		for (auto idx = 0u; idx < len; idx++) {
			UartLog::putchar(*ptr++);
		}
		unlock();
	}
}

void UartLog::write_buffered(const char *ptr, size_t len) {
	auto core = core_id();
	auto *buff = log_buff[core];
	auto &st = write_state[core];

#ifdef CORE_CA7
	// Handle huge writes without overflowing the buffer, by throttling the
	// write back until the M4 has made room for more.
	// Not interrupt-safe, so only do this if depth == 0
	if (st.depth == 0) {
		constexpr size_t MaxChunk = ConcurrentBuffer::Size / 4;
		while (len > 0) {
			const auto chunk = std::min(len, MaxChunk);
			wait_for_space(buff, st, chunk);
			write_reserved(buff, st, ptr, chunk);
			ptr += chunk;
			len -= chunk;
		}
		return;
	}
#endif

	write_reserved(buff, st, ptr, len);
}

void UartLog::write_stdout(const char *ptr, size_t len) {
	auto core = core_id();
	if (mode[core] == Mode::Buffered && log_buff[core])
		write_buffered(ptr, len);
	else
		write_uart(ptr, len);
}

// This is used for bypassing write() and going direct to UART
extern "C" void _putchar(char c) {
	UartLog::putchar(c);
}

} // namespace MetaModule
