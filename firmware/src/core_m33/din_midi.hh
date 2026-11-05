#pragma once
#include "conf/wifi_midi_uart_conf.hh"
#include "drivers/uart.hh"
#include "midi/midi_message.hh"
#include "midi/midi_stream_parser.hh"
#include "util/lockfree_fifo_spsc.hh"
#include <array>
#include <optional>

namespace MetaModule
{

// The DIN5 MIDI jacks on the jack board (USART6). MP1 has them on the MIDI Expander
// (expander_bus/midi_expander.hh).
//
// Polled from the frame interrupt, every ~21us: at MIDI's 31250 baud a byte takes 320us, so the
// UART's FIFOs can't fill up between polls.
class DinMidi {
public:
	void init() {
		uart.init();
	}

	// Frame interrupt: takes the received bytes, and fills the TX FIFO from the queue
	void update() {
		// The data still arrives, so carry on (it's up to the parser to recover)
		if (usart->ISR & (USART_ISR_ORE | USART_ISR_FE | USART_ISR_NE))
			usart->ICR = USART_ICR_ORECF | USART_ICR_FECF | USART_ICR_NECF;

		uint8_t byte;
		while (uart.receive(&byte)) {
			if (auto msg = parser.parse(byte))
				rx_buf.put(*msg);
		}

		while ((usart->ISR & USART_ISR_TXE_TXFNF) && !tx_queue.empty())
			usart->TDR = tx_queue.get_or_default();
	}

	// Frame interrupt: queues a message to send. If there's no room for all of it, it's dropped.
	bool send(MidiMessage msg) {
		const auto len = msg.message_size();
		if (len == 0 || tx_queue.num_free() < len)
			return false;

		std::array<uint8_t, 3> bytes;
		msg.make_bytes(bytes);
		for (auto i = 0u; i < len; i++)
			tx_queue.put(bytes[i]);
		return true;
	}

	// Frame interrupt: the next received message
	std::optional<MidiMessage> receive() {
		return rx_buf.get();
	}

private:
	mdrivlib::Uart<MidiUartConf> uart;
	USART_TypeDef *const usart = reinterpret_cast<USART_TypeDef *>(MidiUartConf.base_addr);

	Midi::StreamParser parser;
	// Same sizes as MP1's (Controls::_midi_exp_rx_buf, MidiExpanderManager's TX queue)
	LockFreeFifoSpsc<MidiMessage, 64> rx_buf;
	LockFreeFifoSpsc<uint8_t, 512> tx_queue;
};

} // namespace MetaModule
