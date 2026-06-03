#include "usb_midi_device.hh"
#include "console/pr_dbg.hh"
#include "drivers/interrupt_control.hh"
#include "util/lockfree_fifo_spsc.hh"
#include <array>
#include <cstring>

extern "C" USBD_DescriptorsTypeDef MIDI_Desc;

namespace MetaModule
{

// DMA-capable (4-byte aligned), sized for one HS bulk max packet.
static uint8_t midi_rx_buf[MIDI_DATA_HS_MAX_PACKET_SIZE] __attribute__((aligned(4)));
static uint8_t midi_tx_buf[MIDI_DATA_HS_MAX_PACKET_SIZE] __attribute__((aligned(4)));

// Outgoing (device -> host) FIFO of raw 4-byte USB-MIDI event packets. Decouples
// "data produced" from "IN endpoint free" so bursts aren't dropped. True SPSC:
//   producer = the app (transmit(), in the FrameRate ISR) -- only put()
//   consumer = pump_tx(), called from TransmitCplt (OTG ISR) AND the main loop.
// The two pump_tx sites never overlap: the main-loop drain masks the OTG IRQ,
// and the main loop is the lowest priority so it can't run while the OTG ISR is
// servicing TransmitCplt. So there is effectively a single consumer at a time.
using MidiEventPacket = std::array<uint8_t, MIDI_EVENT_PACKET_SIZE>;
static LockFreeFifoSpsc<MidiEventPacket, 512> tx_fifo;

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

// Drain the TX FIFO into the IN endpoint. Only starts a transfer when the
// endpoint is free (TxState == 0); otherwise the in-flight transfer's
// TransmitCplt will pump the rest. Must only run in a pump_tx site (OTG ISR or
// the OTG-masked main-loop drain) -- never from the app/FrameRate ISR, which
// would clobber the shared midi_tx_buf mid-DMA.
void UsbMidiDevice::pump_tx() {
	auto *hmidi = static_cast<USBD_MIDI_HandleTypeDef *>(pdev->pClassData);
	if (hmidi == nullptr || hmidi->TxState != 0U)
		return; // not configured, or a transfer is already in flight

	uint32_t n = 0;
	MidiEventPacket pkt;
	while ((n + MIDI_EVENT_PACKET_SIZE) <= sizeof(midi_tx_buf) && tx_fifo.get_move(pkt)) {
		std::memcpy(&midi_tx_buf[n], pkt.data(), MIDI_EVENT_PACKET_SIZE);
		n += MIDI_EVENT_PACKET_SIZE;
	}
	if (n == 0)
		return; // nothing queued

	USBD_MIDI_SetTxBuffer(pdev, midi_tx_buf, n);
	USBD_MIDI_TransmitPacket(pdev); // endpoint was free, so this starts the transfer
}

// Idle-kick drain, called from the main loop (UsbDeviceManager::process). Masks
// the OTG IRQ so this pump can't overlap the TransmitCplt-driven pump.
void UsbMidiDevice::process() {
	mdrivlib::InterruptControl::disable_irq(OTG_IRQn);
	pump_tx();
	mdrivlib::InterruptControl::enable_irq(OTG_IRQn);
}

bool UsbMidiDevice::transmit(std::span<const uint8_t> usb_midi_packets) {
	// Producer side: only enqueue. Never pump from here -- see pump_tx().
	bool ok = true;
	for (size_t i = 0; (i + MIDI_EVENT_PACKET_SIZE) <= usb_midi_packets.size(); i += MIDI_EVENT_PACKET_SIZE) {
		MidiEventPacket pkt;
		std::memcpy(pkt.data(), &usb_midi_packets[i], MIDI_EVENT_PACKET_SIZE);
		if (!tx_fifo.put(pkt)) {
			ok = false; // FIFO full: drop (back-pressure)
			break;
		}
	}
	return ok;
}

int8_t UsbMidiDevice::MIDI_Itf_Init() {
	USBD_MIDI_SetRxBuffer(_instance->pdev, midi_rx_buf);
	USBD_MIDI_SetTxBuffer(_instance->pdev, midi_tx_buf, 0);
	_instance->_connected = true;
	return USBD_OK;
}

int8_t UsbMidiDevice::MIDI_Itf_DeInit() {
	_instance->_connected = false;
	tx_fifo.reset();
	return USBD_OK;
}

int8_t UsbMidiDevice::MIDI_Itf_Receive(uint8_t *Buf, uint32_t *Len) {
	// Hand the received USB-MIDI event packets to the app's MIDI router (the same
	// way MIDI-host input is routed). Runs in the USB ISR.
	if (_instance->_rx_callback)
		_instance->_rx_callback(std::span<uint8_t>{Buf, *Len});

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
