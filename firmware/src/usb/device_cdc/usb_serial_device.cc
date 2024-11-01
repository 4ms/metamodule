#include "usb_serial_device.hh"
#include "console/pr_dbg.hh"

void UsbSerialDevice::init_usb_device() {
}

extern USBD_CDC_ItfTypeDef USBD_CDC_fops;
extern USBD_DescriptorsTypeDef VCP_Desc;

// TODO: put usbd_cdc_interface into this class, so USBD_Device can live as a member
USBD_HandleTypeDef USBD_Device;

UsbSerialDevice::UsbSerialDevice()
	: pdev{&USBD_Device} {
}

void UsbSerialDevice::start() {
	auto init_ok = USBD_Init(pdev, &VCP_Desc, 0);
	if (init_ok != USBD_OK) {
		pr_err("USB Serial Device failed to initialize!\r\n");
		pr_err("Error code: %d", static_cast<int>(init_ok));
		return;
	}

	USBD_RegisterClass(pdev, USBD_CDC_CLASS);
	USBD_CDC_RegisterInterface(pdev, &USBD_CDC_fops);
	USBD_Start(pdev);
}

void UsbSerialDevice::stop() {
	pr_info("Stopping UsbSerialDevice\n");
	USBD_Stop(pdev);
	USBD_DeInit(pdev);
}
