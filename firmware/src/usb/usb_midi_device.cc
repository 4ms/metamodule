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

// TX pump diagnostics: sizes of the IN transfers handed to the endpoint, and
// how far the FIFO backs up between pumps. Written in pump_tx (OTG ISR or
// OTG-masked main loop); printed once per second from the main loop.
struct PumpTxStats {
	uint32_t xfers = 0;
	uint32_t bytes = 0;
	uint32_t max_len = 0;
	uint32_t full_size = 0;		  // transfer == sizeof(midi_tx_buf): a ZLP follows
	uint32_t fifo_high_water = 0; // max packets queued at pump time
};
static PumpTxStats pump_tx_stats;

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

	auto backlog = tx_fifo.num_filled();
	if (backlog > pump_tx_stats.fifo_high_water)
		pump_tx_stats.fifo_high_water = backlog;

	uint32_t n = 0;
	MidiEventPacket pkt;
	while ((n + MIDI_EVENT_PACKET_SIZE) <= sizeof(midi_tx_buf) && tx_fifo.get_move(pkt)) {
		std::memcpy(&midi_tx_buf[n], pkt.data(), MIDI_EVENT_PACKET_SIZE);
		n += MIDI_EVENT_PACKET_SIZE;
	}
	if (n == 0)
		return; // nothing queued

	pump_tx_stats.xfers++;
	pump_tx_stats.bytes += n;
	if (n > pump_tx_stats.max_len)
		pump_tx_stats.max_len = n;
	if (n == sizeof(midi_tx_buf))
		pump_tx_stats.full_size++;

	USBD_MIDI_SetTxBuffer(pdev, midi_tx_buf, n);
	USBD_MIDI_TransmitPacket(pdev); // endpoint was free, so this starts the transfer
}

// Idle-kick drain, called from the main loop (UsbDeviceManager::process). Masks
// the OTG IRQ so this pump can't overlap the TransmitCplt-driven pump.
void UsbMidiDevice::process() {
	mdrivlib::InterruptControl::disable_irq(OTG_IRQn);
	pump_tx();
	mdrivlib::InterruptControl::enable_irq(OTG_IRQn);

	print_pump_stats();
}

// Once-per-second TX transfer summary (main loop; quiet when no traffic)
void UsbMidiDevice::print_pump_stats() {
	static uint32_t last_ms = 0;
	static uint32_t last_xfers = 0;
	static uint32_t last_bytes = 0;

	auto now = HAL_GetTick();
	if (now - last_ms < 1000)
		return;
	auto elapsed_ms = now - last_ms;
	last_ms = now;

	auto s = pump_tx_stats; // copy: pump_tx may run during the printf
	if (s.xfers == last_xfers)
		return;

	printf("[USBD-MIDI] %u xfer/s avg %u B | total %u xfers %u B | max %u B, %u full-size, fifo high-water %u pkts\n",
		   (unsigned)((s.xfers - last_xfers) * 1000 / elapsed_ms),
		   (unsigned)((s.bytes - last_bytes) / (s.xfers - last_xfers)),
		   (unsigned)s.xfers,
		   (unsigned)s.bytes,
		   (unsigned)s.max_len,
		   (unsigned)s.full_size,
		   (unsigned)s.fifo_high_water);

	last_xfers = s.xfers;
	last_bytes = s.bytes;
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
