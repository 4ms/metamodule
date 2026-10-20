// MP2's version of MP1's src/usb/usbd_conf.cc: the USB Device Library's low-level interface,
// on the USB3DR controller (Synopsys DWC3) with ST's HAL PCD (stm32mp2xx_hal_pcd_drd.c).
//
// Differences from MP1:
// - The DWC3 always uses DMA, and the HAL does no cache maintenance. So hpcd (which holds the
//   controller's event buffer, TRBs, and setup packet) and the class handles are in .dma_nc,
//   which isn't cached (see system_init.cc). Data buffers can be anywhere: IN data is cleaned
//   from the cache before the transfer, and OUT data is received into a per-endpoint buffer in
//   .dma_nc and copied to the class's buffer when it arrives.
// - No FIFO sizing: the DWC3 sizes its FIFOs itself.
// - The clocks, resets, and PHY are set up by mdrivlib::Usb3DR (drivers/usb3dr.hh).

#include "conf/usb_conf.hh"
#include "console/pr_dbg.hh"
#include "device_composite/usbd_composite_builder.h"
#include "device_midi/usbd_midi.h"
#include "drivers/cache.hh"
#include "drivers/interrupt.hh"
#include "drivers/stm32xx.h"
#include "drivers/usb3dr.hh"
#include "usbd_cdc.h"
#include "usbd_core.h"
#include "usbd_msc.h"
#include "usbd_video.h"
#include <algorithm>
#include <array>
#include <cstring>

#define DMA_NC __attribute__((section(".dma_nc")))

extern "C" char _sdma_nc[]; // linker script

DMA_NC PCD_HandleTypeDef hpcd;

namespace
{
// Every OUT transfer the classes ask for fits (CDC, MIDI, and MSC packets are at most 512 bytes)
constexpr uint32_t OutBufferSize = 512;
constexpr uint32_t NumEndpoints = USB_DWC3_NUM_OUT_EP;

struct OutTransfer {
	uint8_t *dst = nullptr; // the class's buffer: where the data is copied to when it arrives
};

DMA_NC alignas(32) std::array<std::array<uint8_t, OutBufferSize>, NumEndpoints> out_buffers;
std::array<OutTransfer, NumEndpoints> out_transfers;

bool is_dma_nc(const void *p) {
	auto addr = reinterpret_cast<uintptr_t>(p);
	return addr >= reinterpret_cast<uintptr_t>(_sdma_nc) && addr < M33_LOAD_ADDR + M33_REGION_SIZE;
}

// The DCACHE maintenance commands aren't re-entrant: don't let the USB interrupt (or any other)
// start one while another is running
void clean_dcache(void *addr, uint32_t size) {
	auto primask = __get_PRIMASK();
	__disable_irq();
	mdrivlib::SystemCache::clean_dcache_by_range(addr, size);
	__set_PRIMASK(primask);
}

} // namespace

void HAL_PCD_MspInit(PCD_HandleTypeDef *) {
	mdrivlib::Usb3DR::init(mdrivlib::Usb3DR::Role::Device);

	// TODO: VBUS sensing (FUSB302). Until then, act as if a host is always supplying VBUS
	mdrivlib::Usb3DR::set_vbus_valid(true);
}

void HAL_PCD_MspDeInit(PCD_HandleTypeDef *) {
	mdrivlib::Usb3DR::deinit();
}

/*******************************************************************************
					   LL Driver Callbacks (PCD -> USB Device Library)
*******************************************************************************/

void HAL_PCD_SetupStageCallback(PCD_HandleTypeDef *hpcd) {
	USBD_LL_SetupStage((USBD_HandleTypeDef *)hpcd->pData, (uint8_t *)hpcd->Setup);
}

void HAL_PCD_DataOutStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum) {
	auto &xfer = out_transfers[epnum];
	if (xfer.dst) {
		std::memcpy(xfer.dst, out_buffers[epnum].data(), HAL_PCD_EP_GetRxCount(hpcd, epnum));
		USBD_LL_DataOutStage((USBD_HandleTypeDef *)hpcd->pData, epnum, xfer.dst);
	} else
		USBD_LL_DataOutStage((USBD_HandleTypeDef *)hpcd->pData, epnum, hpcd->OUT_ep[epnum].xfer_buff);
}

void HAL_PCD_DataInStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum) {
	USBD_LL_DataInStage((USBD_HandleTypeDef *)hpcd->pData, epnum, hpcd->IN_ep[epnum].xfer_buff);
}

void HAL_PCD_SOFCallback(PCD_HandleTypeDef *hpcd) {
	USBD_LL_SOF((USBD_HandleTypeDef *)hpcd->pData);
}

void HAL_PCD_ResetCallback(PCD_HandleTypeDef *hpcd) {
	// The HAL has read the enumerated speed into Init.speed
	auto speed = hpcd->Init.speed == PCD_SPEED_HIGH ? USBD_SPEED_HIGH : USBD_SPEED_FULL;

	USBD_LL_Reset((USBD_HandleTypeDef *)hpcd->pData);
	USBD_LL_SetSpeed((USBD_HandleTypeDef *)hpcd->pData, speed);
}

void HAL_PCD_SuspendCallback(PCD_HandleTypeDef *hpcd) {
	USBD_LL_Suspend((USBD_HandleTypeDef *)hpcd->pData);
}

void HAL_PCD_ResumeCallback(PCD_HandleTypeDef *hpcd) {
	USBD_LL_Resume((USBD_HandleTypeDef *)hpcd->pData);
}

void HAL_PCD_ISOOUTIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum) {
	USBD_LL_IsoOUTIncomplete((USBD_HandleTypeDef *)hpcd->pData, epnum);
}

void HAL_PCD_ISOINIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum) {
	USBD_LL_IsoINIncomplete((USBD_HandleTypeDef *)hpcd->pData, epnum);
}

void HAL_PCD_ConnectCallback(PCD_HandleTypeDef *hpcd) {
	USBD_LL_DevConnected((USBD_HandleTypeDef *)hpcd->pData);
}

void HAL_PCD_DisconnectCallback(PCD_HandleTypeDef *hpcd) {
	USBD_LL_DevDisconnected((USBD_HandleTypeDef *)hpcd->pData);
}

/*******************************************************************************
					   LL Driver Interface (USB Device Library --> PCD)
*******************************************************************************/
static void reset_class_arena();

USBD_StatusTypeDef USBD_LL_Init(USBD_HandleTypeDef *pdev) {
	hpcd.Instance = USB3;
	hpcd.Init.speed = PCD_SPEED_HIGH;
	hpcd.Init.phy_itface = PCD_PHY_UTMI;
	hpcd.Init.ep0_mps = PCD_SPEED_HIGH_MAXPACKETSIZE;
	hpcd.Init.Sof_enable = true;
	hpcd.Init.low_power_enable = false;
	hpcd.Init.lpm_enable = false;
	hpcd.Init.battery_charging_enable = false;
	hpcd.Init.vbus_sensing_enable = false;
	hpcd.Init.use_dedicated_ep1 = false;
	hpcd.Init.use_external_vbus = false;

	/* Link The driver to the stack */
	hpcd.pData = pdev;
	pdev->pData = &hpcd;

	// Note: Library was altered here:
	// Force this to null, so ST USB library doesn't try to de-init it
	((USBD_HandleTypeDef *)hpcd.pData)->pClassData = nullptr;

	if (HAL_PCD_Init(&hpcd) != HAL_OK)
		return USBD_FAIL;

	// AHB bursts: INCR4 only, as in ST's stm32mp257f-ev1 device tree (the HAL enables INCR4/8/16).
	// Longer bursts can trip up the AHB5/RISAF path.
	auto &gsbuscfg0 = *reinterpret_cast<volatile uint32_t *>(reinterpret_cast<uintptr_t>(USB3) + 0xC100);
	gsbuscfg0 = (gsbuscfg0 & ~0xFFu) | (1u << 1); // INCR4BRSTENA

	out_transfers = {};
	reset_class_arena();

	mdrivlib::InterruptManager::register_and_start_isr(
		MetaModule::UsbIRQn, 3, 0, [] { HAL_PCD_IRQHandler(&hpcd); });

	return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_DeInit(USBD_HandleTypeDef *pdev) {
	mdrivlib::InterruptControl::disable_irq(MetaModule::UsbIRQn);
	HAL_PCD_DeInit((PCD_HandleTypeDef *)pdev->pData);
	return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_Start(USBD_HandleTypeDef *pdev) {
	HAL_PCD_Start((PCD_HandleTypeDef *)pdev->pData);
	return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_Stop(USBD_HandleTypeDef *pdev) {
	HAL_PCD_Stop((PCD_HandleTypeDef *)pdev->pData);
	return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_OpenEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr, uint8_t ep_type, uint16_t ep_mps) {
	HAL_PCD_EP_Open((PCD_HandleTypeDef *)pdev->pData, ep_addr, ep_mps, ep_type);
	return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_CloseEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr) {
	HAL_PCD_EP_Close((PCD_HandleTypeDef *)pdev->pData, ep_addr);
	return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_FlushEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr) {
	HAL_PCD_EP_Flush((PCD_HandleTypeDef *)pdev->pData, ep_addr);
	return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_StallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr) {
	HAL_PCD_EP_SetStall((PCD_HandleTypeDef *)pdev->pData, ep_addr);
	return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_ClearStallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr) {
	HAL_PCD_EP_ClrStall((PCD_HandleTypeDef *)pdev->pData, ep_addr);
	return USBD_OK;
}

uint8_t USBD_LL_IsStallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr) {
	auto *hpcd = (PCD_HandleTypeDef *)pdev->pData;

	if ((ep_addr & 0x80) == 0x80) {
		return hpcd->IN_ep[ep_addr & 0x7F].is_stall;
	} else {
		return hpcd->OUT_ep[ep_addr & 0x7F].is_stall;
	}
}

USBD_StatusTypeDef USBD_LL_SetUSBAddress(USBD_HandleTypeDef *pdev, uint8_t dev_addr) {
	HAL_PCD_SetAddress((PCD_HandleTypeDef *)pdev->pData, dev_addr);
	return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_Transmit(USBD_HandleTypeDef *pdev, uint8_t ep_addr, uint8_t *pbuf, uint32_t size) {
	if (size && !is_dma_nc(pbuf))
		clean_dcache(pbuf, size);

	HAL_PCD_EP_Transmit((PCD_HandleTypeDef *)pdev->pData, ep_addr, pbuf, size);
	return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_PrepareReceive(USBD_HandleTypeDef *pdev, uint8_t ep_addr, uint8_t *pbuf, uint32_t size) {
	auto epnum = ep_addr & 0x7F;
	auto &xfer = out_transfers[epnum];

	if (size == 0 || is_dma_nc(pbuf)) {
		xfer.dst = nullptr;
	} else {
		if (size > OutBufferSize) {
			pr_err("USB: EP%u OUT transfer of %u bytes is bigger than its buffer (%u)\n",
				   epnum,
				   (unsigned)size,
				   (unsigned)OutBufferSize);
			size = OutBufferSize;
		}
		xfer.dst = pbuf;
		pbuf = out_buffers[epnum].data();
	}

	HAL_PCD_EP_Receive((PCD_HandleTypeDef *)pdev->pData, ep_addr, pbuf, size);
	return USBD_OK;
}

uint32_t USBD_LL_GetRxDataSize(USBD_HandleTypeDef *pdev, uint8_t ep_addr) {
	return HAL_PCD_EP_GetRxCount((PCD_HandleTypeDef *)pdev->pData, ep_addr);
}

// Each registered class allocates its handle here during SetConfiguration and
// releases it on ClrClassConfig. A composite configuration has several classes
// live at once, so this cannot hand out one shared block the way ST's template
// does -- it bump-allocates from an arena instead, and rewinds once every
// allocation has been released. USBD_LL_Init() resets it outright: a fresh
// USBD_Init means every previously handed-out handle is dead.
// (Same as MP1, but in .dma_nc: the handles hold buffers that the controller reads and writes.)
//
// Sized for the largest device mode: MIDI + Console (plus the MSC handle, which
// is the biggest of the four and is what the developer-mode drive will add).
static constexpr uint32_t round4(uint32_t n) {
	return (n + 3u) & ~3u;
}

static constexpr uint32_t ArenaSize = std::max(round4(sizeof(USBD_CDC_HandleTypeDef)) +
												   round4(sizeof(USBD_MIDI_HandleTypeDef)) +
												   round4(sizeof(USBD_MSC_BOT_HandleTypeDef)),
											   round4(sizeof(USBD_VIDEO_HandleTypeDef)));

DMA_NC static uint32_t class_arena[ArenaSize / 4];
static uint32_t arena_used;	  // bytes handed out
static uint32_t arena_allocs; // outstanding allocations

static void reset_class_arena() {
	arena_used = 0;
	arena_allocs = 0;
}

void *USBD_static_malloc(uint32_t size) {
	size = round4(size);

	if (arena_used + size > sizeof(class_arena)) {
		// The caller (a class Init) reports this to the core as USBD_EMEM
		return nullptr;
	}

	void *p = reinterpret_cast<uint8_t *>(class_arena) + arena_used;
	arena_used += size;
	arena_allocs++;
	return p;
}

void USBD_static_free(void *p) {
	if (p != nullptr && arena_allocs > 0) {
		// Classes are torn down as a group (USBD_ClrClassConfig / USBD_DeInit),
		// so rewinding when the last one goes is enough to keep this stable
		// across re-enumeration; individual frees are otherwise no-ops.
		if (--arena_allocs == 0)
			arena_used = 0;
	}
}

void USBD_LL_Delay(uint32_t Delay) {
	HAL_Delay(Delay);
}
