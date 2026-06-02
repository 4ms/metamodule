#include "usb_midi_device.hh"
#include "console/pr_dbg.hh"
#include <cstring>

extern "C" USBD_DescriptorsTypeDef MIDI_Desc;

namespace MetaModule
{

// DMA-capable (4-byte aligned), sized for one HS bulk max packet.
static uint8_t midi_rx_buf[MIDI_DATA_HS_MAX_PACKET_SIZE] __attribute__((aligned(4)));
static uint8_t midi_tx_buf[MIDI_DATA_HS_MAX_PACKET_SIZE] __attribute__((aligned(4)));

USBD_MIDI_ItfTypeDef UsbMidiDevice::fops = {
	MIDI_Itf_Init,
	MIDI_Itf_DeInit,
	MIDI_Itf_Receive,
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

bool UsbMidiDevice::transmit(std::span<const uint8_t> usb_midi_packets) {
	auto len = usb_midi_packets.size();
	if (len > sizeof(midi_tx_buf))
		len = sizeof(midi_tx_buf);
	std::memcpy(midi_tx_buf, usb_midi_packets.data(), len);
	USBD_MIDI_SetTxBuffer(pdev, midi_tx_buf, len);
	return USBD_MIDI_TransmitPacket(pdev) == USBD_OK;
}

int8_t UsbMidiDevice::MIDI_Itf_Init() {
	USBD_MIDI_SetRxBuffer(_instance->pdev, midi_rx_buf);
	USBD_MIDI_SetTxBuffer(_instance->pdev, midi_tx_buf, 0);
	return USBD_OK;
}

int8_t UsbMidiDevice::MIDI_Itf_DeInit() {
	return USBD_OK;
}

int8_t UsbMidiDevice::MIDI_Itf_Receive(uint8_t *Buf, uint32_t *Len) {
	uint32_t len = *Len;

	// DEBUG/loopback: echo the received USB-MIDI event packets back to the host.
	// (Real app routing replaces this; see header.)
	_instance->transmit(std::span<const uint8_t>{Buf, len});

	// Re-arm the OUT endpoint to receive the next packet.
	USBD_MIDI_ReceivePacket(_instance->pdev);
	return USBD_OK;
}

} // namespace MetaModule
