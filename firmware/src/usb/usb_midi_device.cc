#include "usb_midi_device.hh"
#include "console/pr_dbg.hh"
#include <cstring>

extern "C" USBD_DescriptorsTypeDef MIDI_Desc;

namespace MetaModule
{

// DMA-capable (4-byte aligned), sized for one HS bulk max packet.
static uint8_t midi_rx_buf[MIDI_DATA_HS_MAX_PACKET_SIZE] __attribute__((aligned(4)));
static uint8_t midi_tx_buf[MIDI_DATA_HS_MAX_PACKET_SIZE] __attribute__((aligned(4)));

// Outgoing (device -> host) byte FIFO. Decouples "data produced" from "IN
// endpoint free", so nothing is dropped when MIDI arrives in bursts. SPSC:
// one producer (the USB ISR for loopback today; the app later) and the drain
// (pump_tx) running in the same/ISR context. Power-of-two size for masking.
static constexpr uint32_t TxFifoSize = 2048;
static uint8_t tx_fifo[TxFifoSize];
static volatile uint32_t tx_head = 0; // write index
static volatile uint32_t tx_tail = 0; // read index

static void fifo_push(const uint8_t *data, uint32_t n) {
	for (uint32_t i = 0; i < n; i++) {
		uint32_t next = (tx_head + 1) & (TxFifoSize - 1);
		if (next == tx_tail)
			break; // full: drop (acceptable for a debug loopback)
		tx_fifo[tx_head] = data[i];
		tx_head = next;
	}
}

USBD_MIDI_ItfTypeDef UsbMidiDevice::fops = {
	MIDI_Itf_Init,
	MIDI_Itf_DeInit,
	MIDI_Itf_Receive,
	MIDI_Itf_TransmitCplt,
};

UsbMidiDevice::UsbMidiDevice(USBD_HandleTypeDef *pDevice)
	: pdev{pDevice} {
	_instance = this;
}

void UsbMidiDevice::start() {
	_instance = this;
	auto init_ok = USBD_Init(pdev, &MIDI_Desc, 0);
	if (init_ok != USBD_OK) {
		pr_err("USB MIDI Device failed to initialize! Error %d\n", static_cast<int>(init_ok));
		return;
	}
	USBD_RegisterClass(pdev, USBD_MIDI_CLASS);
	USBD_MIDI_RegisterInterface(pdev, &fops);
	USBD_Start(pdev);
	pr_info("Started UsbMidiDevice\n");
}

void UsbMidiDevice::stop() {
	pr_info("Stopping UsbMidiDevice\n");
	USBD_Stop(pdev);
	USBD_DeInit(pdev);
}

void UsbMidiDevice::soft_stop() {
	// See UsbVideoDevice::soft_stop -- skip USBD_DeInit so hpcd->State stays
	// READY and the next USBD_Init won't toggle USBO_CLK via MspInit.
	pr_info("Stopping UsbMidiDevice\n");
	USBD_Stop(pdev);
}

// Send as much of the TX FIFO as fits in one bulk packet, but only commit the
// read index if the endpoint accepted it (otherwise retry on the next pump).
void UsbMidiDevice::pump_tx() {
	if (tx_head == tx_tail)
		return; // nothing queued

	uint32_t n = 0;
	uint32_t t = tx_tail;
	while (t != tx_head && n < sizeof(midi_tx_buf)) {
		midi_tx_buf[n++] = tx_fifo[t];
		t = (t + 1) & (TxFifoSize - 1);
	}

	USBD_MIDI_SetTxBuffer(pdev, midi_tx_buf, n);
	if (USBD_MIDI_TransmitPacket(pdev) == USBD_OK)
		tx_tail = t; // committed; IN endpoint now busy until DataIn completes
}

bool UsbMidiDevice::transmit(std::span<const uint8_t> usb_midi_packets) {
	fifo_push(usb_midi_packets.data(), static_cast<uint32_t>(usb_midi_packets.size()));
	pump_tx();
	return true;
}

int8_t UsbMidiDevice::MIDI_Itf_Init() {
	USBD_MIDI_SetRxBuffer(_instance->pdev, midi_rx_buf);
	USBD_MIDI_SetTxBuffer(_instance->pdev, midi_tx_buf, 0);
	return USBD_OK;
}

int8_t UsbMidiDevice::MIDI_Itf_DeInit() {
	tx_head = 0;
	tx_tail = 0;
	return USBD_OK;
}

int8_t UsbMidiDevice::MIDI_Itf_Receive(uint8_t *Buf, uint32_t *Len) {
	// DEBUG/loopback: queue the received USB-MIDI event packets straight back to
	// the host. (Real app routing will push these into the MIDI router instead.)
	fifo_push(Buf, *Len);
	_instance->pump_tx();

	// Re-arm the OUT endpoint right away so host -> device flow never stalls.
	USBD_MIDI_ReceivePacket(_instance->pdev);
	return USBD_OK;
}

int8_t UsbMidiDevice::MIDI_Itf_TransmitCplt(uint8_t *Buf, uint32_t *Len, uint8_t epnum) {
	(void)Buf;
	(void)Len;
	(void)epnum;
	// IN endpoint just freed -- push the next queued chunk.
	_instance->pump_tx();
	return USBD_OK;
}

} // namespace MetaModule
