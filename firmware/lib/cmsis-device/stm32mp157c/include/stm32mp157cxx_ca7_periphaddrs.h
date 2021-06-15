
/** @addtogroup Peripheral_memory_map
  * @{
  */
#define AHB_SRAM            ((uint32_t)0x30000000) /*!< Base address of : (up to 288KB) system data RAM accessible over over AHB             */
#define AHB_RETRAM          ((uint32_t)0x38000000) /*!< Base address of : (up to 64KB) Retention RAM accessible over over AHB                */

#define SYSRAM_BASE             ((uint32_t)0x2FFC0000) /*!< Base address of : (up to 256KB) System RAM accessible over over AXI                  */
#define RETRAM_BASE             MCU_AHB_RETRAM
#define SRAM_BASE               AHB_SRAM
#define PERIPH_BASE             ((uint32_t)0x40000000) /*!< Base address of : AHB/ABP Peripherals                                                */
#define AXI_BUS_MEMORY_BASE     ((uint32_t)0x60000000) /*!< Base address of : AXI Bus                                                            */

#define FMC_NOR_MEM_BASE        (AXI_BUS_MEMORY_BASE)              /*!< Base address of : FMC NOR memories  accessible over AXI              */
#define QSPI_MEM_BASE           (AXI_BUS_MEMORY_BASE + 0x10000000) /*!< Base address of : QSPI memories  accessible over AXI                 */
#define FMC_NAND_MEM_BASE       (AXI_BUS_MEMORY_BASE + 0x20000000) /*!< Base address of : FMC NAND memories  accessible over AXI             */
#define STM_DATA_BASE           (AXI_BUS_MEMORY_BASE + 0x30000000) /*!< Base address of : STM Data accessible over AXI                       */
#define DRAM_MEM_BASE           (AXI_BUS_MEMORY_BASE + 0x60000000) /*!< Base address of : DRAM (DDR) over AXI                                */

/*!< Device electronic signature memory map */
#define UID_BASE                  (0x5C005234L)            /*!< Unique Device ID register base address */
#define PACKAGE_BASE              (0x5C005240L)            /*!< Package Data register base address */
#define RPN_BASE                  (0x5C005204L)            /*!< Device Part Number register base address */
#define DV_BASE                   (0x50081000L)            /*!< Device Version register base address */

/*!< Peripheral memory map */
#define APB1_PERIPH_BASE          (PERIPH_BASE + 0x00000000)
#define APB2_PERIPH_BASE          (PERIPH_BASE + 0x04000000)
#define AHB2_PERIPH_BASE          (PERIPH_BASE + 0x08000000)
#define AHB3_PERIPH_BASE          (PERIPH_BASE + 0x0C000000)
#define AHB4_PERIPH_BASE          (PERIPH_BASE + 0x10000000)
#define APB3_PERIPH_BASE          (PERIPH_BASE + 0x10020000)
#define APB_DEBUG_PERIPH_BASE     (PERIPH_BASE + 0x10080000)
#define AHB5_PERIPH_BASE          (PERIPH_BASE + 0x14000000)
#define GPV_PERIPH_BASE           (PERIPH_BASE + 0x17000000)
#define AHB6_PERIPH_BASE          (PERIPH_BASE + 0x18000000)
#define APB4_PERIPH_BASE          (PERIPH_BASE + 0x1A000000)
#define APB5_PERIPH_BASE          (PERIPH_BASE + 0x1C000000)


#define MCU_AHB_SRAM              AHB_SRAM
#define MCU_AHB_RETRAM            AHB_RETRAM
#define MPU_AXI_BUS_MEMORY_BASE   AXI_BUS_MEMORY_BASE
#define MCU_APB1_PERIPH_BASE      APB1_PERIPH_BASE
#define MCU_APB2_PERIPH_BASE      APB2_PERIPH_BASE
#define MCU_AHB2_PERIPH_BASE      AHB2_PERIPH_BASE
#define MCU_AHB3_PERIPH_BASE      AHB3_PERIPH_BASE
#define MCU_AHB4_PERIPH_BASE      AHB4_PERIPH_BASE
#define MCU_APB3_PERIPH_BASE      APB3_PERIPH_BASE
#define MPU_AHB5_PERIPH_BASE      AHB5_PERIPH_BASE
#define MPU_AHB6_PERIPH_BASE      AHB6_PERIPH_BASE
#define MPU_APB4_PERIPH_BASE      APB4_PERIPH_BASE
#define MPU_APB5_PERIPH_BASE      APB5_PERIPH_BASE

/*!< APB1 */
#define TIM2_BASE             (APB1_PERIPH_BASE + 0x0000)
#define TIM3_BASE             (APB1_PERIPH_BASE + 0x1000)
#define TIM4_BASE             (APB1_PERIPH_BASE + 0x2000)
#define TIM5_BASE             (APB1_PERIPH_BASE + 0x3000)
#define TIM6_BASE             (APB1_PERIPH_BASE + 0x4000)
#define TIM7_BASE             (APB1_PERIPH_BASE + 0x5000)
#define TIM12_BASE            (APB1_PERIPH_BASE + 0x6000)
#define TIM13_BASE            (APB1_PERIPH_BASE + 0x7000)
#define TIM14_BASE            (APB1_PERIPH_BASE + 0x8000)
#define LPTIM1_BASE           (APB1_PERIPH_BASE + 0x9000)
#define WWDG1_BASE            (APB1_PERIPH_BASE + 0xA000)
#define SPI2_BASE             (APB1_PERIPH_BASE + 0xB000)
#define SPI3_BASE             (APB1_PERIPH_BASE + 0xC000)
#define SPDIFRX_BASE          (APB1_PERIPH_BASE + 0xD000)
#define USART2_BASE           (APB1_PERIPH_BASE + 0xE000)
#define USART3_BASE           (APB1_PERIPH_BASE + 0xF000)
#define UART4_BASE            (APB1_PERIPH_BASE + 0x10000)
#define UART5_BASE            (APB1_PERIPH_BASE + 0x11000)
#define I2C1_BASE             (APB1_PERIPH_BASE + 0x12000)
#define I2C2_BASE             (APB1_PERIPH_BASE + 0x13000)
#define I2C3_BASE             (APB1_PERIPH_BASE + 0x14000)
#define I2C5_BASE             (APB1_PERIPH_BASE + 0x15000)
#define CEC_BASE              (APB1_PERIPH_BASE + 0x16000)
#define DAC1_BASE             (APB1_PERIPH_BASE + 0x17000)
#define UART7_BASE            (APB1_PERIPH_BASE + 0x18000)
#define UART8_BASE            (APB1_PERIPH_BASE + 0x19000)
#define MDIOS_BASE            (APB1_PERIPH_BASE + 0x1C000)

/*!< APB2 */
#define TIM1_BASE             (APB2_PERIPH_BASE + 0x0000)
#define TIM8_BASE             (APB2_PERIPH_BASE + 0x1000)
#define USART6_BASE           (APB2_PERIPH_BASE + 0x3000)
#define SPI1_BASE             (APB2_PERIPH_BASE + 0x4000)
#define SPI4_BASE             (APB2_PERIPH_BASE + 0x5000)
#define TIM15_BASE            (APB2_PERIPH_BASE + 0x6000)
#define TIM16_BASE            (APB2_PERIPH_BASE + 0x7000)
#define TIM17_BASE            (APB2_PERIPH_BASE + 0x8000)
#define SPI5_BASE             (APB2_PERIPH_BASE + 0x9000)
#define SAI1_BASE             (APB2_PERIPH_BASE + 0xA000)
#define SAI1_Block_A_BASE     (SAI1_BASE + 0x004)
#define SAI1_Block_B_BASE     (SAI1_BASE + 0x024)
#define SAI2_BASE             (APB2_PERIPH_BASE + 0xB000)
#define SAI2_Block_A_BASE     (SAI2_BASE + 0x004)
#define SAI2_Block_B_BASE     (SAI2_BASE + 0x024)
#define SAI3_BASE             (APB2_PERIPH_BASE + 0xC000)
#define SAI3_Block_A_BASE     (SAI3_BASE + 0x004)
#define SAI3_Block_B_BASE     (SAI3_BASE + 0x024)
#define DFSDM1_BASE           (APB2_PERIPH_BASE + 0xD000)
#define DFSDM1_Channel0_BASE  (DFSDM1_BASE + 0x00)
#define DFSDM1_Channel1_BASE  (DFSDM1_BASE + 0x20)
#define DFSDM1_Channel2_BASE  (DFSDM1_BASE + 0x40)
#define DFSDM1_Channel3_BASE  (DFSDM1_BASE + 0x60)
#define DFSDM1_Channel4_BASE  (DFSDM1_BASE + 0x80)
#define DFSDM1_Channel5_BASE  (DFSDM1_BASE + 0xA0)
#define DFSDM1_Channel6_BASE  (DFSDM1_BASE + 0xC0)
#define DFSDM1_Channel7_BASE  (DFSDM1_BASE + 0xE0)
#define DFSDM1_Filter0_BASE   (DFSDM1_BASE + 0x100)
#define DFSDM1_Filter1_BASE   (DFSDM1_BASE + 0x180)
#define DFSDM1_Filter2_BASE   (DFSDM1_BASE + 0x200)
#define DFSDM1_Filter3_BASE   (DFSDM1_BASE + 0x280)
#define DFSDM1_Filter4_BASE   (DFSDM1_BASE + 0x300)
#define DFSDM1_Filter5_BASE   (DFSDM1_BASE + 0x380)
#define FDCAN1_BASE           (APB2_PERIPH_BASE + 0xE000)
#define FDCAN2_BASE           (APB2_PERIPH_BASE + 0xF000)
#define TTFDCAN1_BASE         (APB2_PERIPH_BASE + 0xE100)
#define FDCAN_CCU_BASE        (APB2_PERIPH_BASE + 0x10000)
#define SRAMCAN_BASE          (APB2_PERIPH_BASE + 0x11000)

/*!< AHB2 */
#define DMA1_BASE             (AHB2_PERIPH_BASE + 0x0000)
#define DMA2_BASE             (AHB2_PERIPH_BASE + 0x1000)
#define DMAMUX1_BASE          (AHB2_PERIPH_BASE + 0x2000)
#define ADC1_BASE             (AHB2_PERIPH_BASE + 0x3000)
#define ADC2_BASE             (AHB2_PERIPH_BASE + 0x3100)
#define ADC12_COMMON_BASE     (AHB2_PERIPH_BASE + 0x3300)
#define SDMMC3_BASE           (AHB2_PERIPH_BASE + 0x4000)
#define DLYB_SDMMC3_BASE      (AHB2_PERIPH_BASE + 0x5000)
#define USBOTG_BASE           (AHB2_PERIPH_BASE + 0x1000000)


/*!< AHB3 */
#define HSEM_BASE             (AHB3_PERIPH_BASE + 0x0000)
#define IPCC_BASE             (AHB3_PERIPH_BASE + 0x1000)
#define HASH2_BASE            (AHB3_PERIPH_BASE + 0x2000)
#define HASH2_DIGEST_BASE     (AHB3_PERIPH_BASE + 0x2310)
#define RNG2_BASE             (AHB3_PERIPH_BASE + 0x3000)
#define CRC2_BASE             (AHB3_PERIPH_BASE + 0x4000)
#define CRYP2_BASE            (AHB3_PERIPH_BASE + 0x5000)
#define DCMI_BASE             (AHB3_PERIPH_BASE + 0x6000)

/*!< AHB4 */
#define RCC_BASE              (AHB4_PERIPH_BASE + 0x0000)
#define PWR_BASE              (AHB4_PERIPH_BASE + 0x1000)
#define GPIOA_BASE            (AHB4_PERIPH_BASE + 0x2000)
#define GPIOB_BASE            (AHB4_PERIPH_BASE + 0x3000)
#define GPIOC_BASE            (AHB4_PERIPH_BASE + 0x4000)
#define GPIOD_BASE            (AHB4_PERIPH_BASE + 0x5000)
#define GPIOE_BASE            (AHB4_PERIPH_BASE + 0x6000)
#define GPIOF_BASE            (AHB4_PERIPH_BASE + 0x7000)
#define GPIOG_BASE            (AHB4_PERIPH_BASE + 0x8000)
#define GPIOH_BASE            (AHB4_PERIPH_BASE + 0x9000)
#define GPIOI_BASE            (AHB4_PERIPH_BASE + 0xA000)
#define GPIOJ_BASE            (AHB4_PERIPH_BASE + 0xB000)
#define GPIOK_BASE            (AHB4_PERIPH_BASE + 0xC000)
#define AIEC_BASE             (AHB4_PERIPH_BASE + 0xD000)
#define AIEC_C1_BASE          (AIEC_BASE + 0x0080)
#define AIEC_C2_BASE          (AIEC_BASE + 0x00C0)
/* Alias EXTI_BASE defined because HAL code not yet reworked with new name AIEC*/
#define EXTI_BASE             AIEC_BASE
#define EXTI_C1_BASE          AIEC_C1_BASE
#define EXTI_C2_BASE          AIEC_C2_BASE


/*!< APB3 */
#define SYSCFG_BASE           (APB3_PERIPH_BASE + 0x0000)
#define LPTIM2_BASE           (APB3_PERIPH_BASE + 0x1000)
#define LPTIM3_BASE           (APB3_PERIPH_BASE + 0x2000)
#define LPTIM4_BASE           (APB3_PERIPH_BASE + 0x3000)
#define LPTIM5_BASE           (APB3_PERIPH_BASE + 0x4000)
#define VREFBUF_BASE          (APB3_PERIPH_BASE + 0x5000)
#define SAI4_BASE             (APB3_PERIPH_BASE + 0x7000)
#define SAI4_Block_A_BASE     (SAI4_BASE + 0x004)
#define SAI4_Block_B_BASE     (SAI4_BASE + 0x024)
#define DTS_BASE              (APB3_PERIPH_BASE + 0x8000)
#define PMB_BASE              (APB3_PERIPH_BASE + 0x9000)
#define HDP_BASE              (APB3_PERIPH_BASE + 0xA000)

/*!< AHB4 _APB_Debug */
#define DBGMCU_BASE           ((uint32_t )0x50081000)

/*!< AHB5 */
#define BKPSRAM_BASE          (AHB5_PERIPH_BASE + 0x0000)
#define CRYP1_BASE            (AHB5_PERIPH_BASE + 0x1000)
#define HASH1_BASE            (AHB5_PERIPH_BASE + 0x2000)
#define HASH1_DIGEST_BASE     (AHB5_PERIPH_BASE + 0x2310)
#define RNG1_BASE             (AHB5_PERIPH_BASE + 0x3000)
#define GPIOZ_BASE            (AHB5_PERIPH_BASE + 0x4000)

/*!< GPV */

/*!< MPU_AHB6 */
#define MDMA_BASE               (AHB6_PERIPH_BASE + 0x0000)
#define FMC_R_BASE              (AHB6_PERIPH_BASE + 0x2000)
#define QSPI_R_BASE             (AHB6_PERIPH_BASE + 0x3000)
#define DLYB_QSPI_BASE          (AHB6_PERIPH_BASE + 0x4000)
#define SDMMC1_BASE             (AHB6_PERIPH_BASE + 0x5000)
#define DLYB_SDMMC1_BASE        (AHB6_PERIPH_BASE + 0x6000)
#define SDMMC2_BASE             (AHB6_PERIPH_BASE + 0x7000)
#define DLYB_SDMMC2_BASE        (AHB6_PERIPH_BASE + 0x8000)
#define CRC1_BASE               (AHB6_PERIPH_BASE + 0x9000)
#define ETH_BASE                (AHB6_PERIPH_BASE + 0xA000)
#define ETH_MAC_BASE            (ETH_BASE)
#define USB1HSFSP2_BASE         (AHB6_PERIPH_BASE + 0xC000)
#define USB1HSFSP1_BASE         (AHB6_PERIPH_BASE + 0xD000)
#define GPU_BASE                (AHB6_PERIPH_BASE + 0x1000000)

/*!< MPU_APB4 */
#define DSI_BASE              (APB4_PERIPH_BASE + 0x0000)
#define LTDC_BASE             (APB4_PERIPH_BASE + 0x1000)
#define LTDC_Layer1_BASE      (LTDC_BASE + 0x84)
#define LTDC_Layer2_BASE      (LTDC_BASE + 0x104)
#define IWDG2_BASE            (APB4_PERIPH_BASE + 0x2000)
#define DDRCTRL_BASE          (APB4_PERIPH_BASE + 0x3000)
#define DDRPHYC_BASE          (APB4_PERIPH_BASE + 0x4000)
#define STGENR_BASE           (APB4_PERIPH_BASE + 0x5000)
#define USBPHYC_BASE          (APB4_PERIPH_BASE + 0x6000)
#define DDRPERFM_BASE         (APB4_PERIPH_BASE + 0x7000)
#define USBPHYC_PHY1_BASE     (USBPHYC_BASE + 0x100)
#define USBPHYC_PHY2_BASE     (USBPHYC_BASE + 0x200)

/*!< MPU_APB5 */
#define USART1_BASE           (APB5_PERIPH_BASE + 0x0000)
#define SPI6_BASE             (APB5_PERIPH_BASE + 0x1000)
#define I2C4_BASE             (APB5_PERIPH_BASE + 0x2000)
#define IWDG1_BASE            (APB5_PERIPH_BASE + 0x3000)
#define RTC_BASE              (APB5_PERIPH_BASE + 0x4000)
#define BSEC_BASE             (APB5_PERIPH_BASE + 0x5000)
#define TZC_BASE              (APB5_PERIPH_BASE + 0x6000)
#define TZPC_BASE             (APB5_PERIPH_BASE + 0x7000)
#define STGENC_BASE           (APB5_PERIPH_BASE + 0x8000)
#define I2C6_BASE             (APB5_PERIPH_BASE + 0x9000)
#define TAMP_BASE             (APB5_PERIPH_BASE + 0xA000)



/*!< USB registers base address */
#define USB_OTG_GLOBAL_BASE                  ((uint32_t )0x000)
#define USB_OTG_DEVICE_BASE                  ((uint32_t )0x800)
#define USB_OTG_IN_ENDPOINT_BASE             ((uint32_t )0x900)
#define USB_OTG_OUT_ENDPOINT_BASE            ((uint32_t )0xB00)
#define USB_OTG_EP_REG_SIZE                  ((uint32_t )0x20)
#define USB_OTG_HOST_BASE                    ((uint32_t )0x400)
#define USB_OTG_HOST_PORT_BASE               ((uint32_t )0x440)
#define USB_OTG_HOST_CHANNEL_BASE            ((uint32_t )0x500)
#define USB_OTG_HOST_CHANNEL_SIZE            ((uint32_t )0x20)
#define USB_OTG_PCGCCTL_BASE                 ((uint32_t )0xE00)
#define USB_OTG_FIFO_BASE                    ((uint32_t )0x1000)
#define USB_OTG_FIFO_SIZE                    ((uint32_t )0x1000)



#define DMA1_Stream0_BASE     (DMA1_BASE + 0x010)
#define DMA1_Stream1_BASE     (DMA1_BASE + 0x028)
#define DMA1_Stream2_BASE     (DMA1_BASE + 0x040)
#define DMA1_Stream3_BASE     (DMA1_BASE + 0x058)
#define DMA1_Stream4_BASE     (DMA1_BASE + 0x070)
#define DMA1_Stream5_BASE     (DMA1_BASE + 0x088)
#define DMA1_Stream6_BASE     (DMA1_BASE + 0x0A0)
#define DMA1_Stream7_BASE     (DMA1_BASE + 0x0B8)

#define DMA2_Stream0_BASE     (DMA2_BASE + 0x010)
#define DMA2_Stream1_BASE     (DMA2_BASE + 0x028)
#define DMA2_Stream2_BASE     (DMA2_BASE + 0x040)
#define DMA2_Stream3_BASE     (DMA2_BASE + 0x058)
#define DMA2_Stream4_BASE     (DMA2_BASE + 0x070)
#define DMA2_Stream5_BASE     (DMA2_BASE + 0x088)
#define DMA2_Stream6_BASE     (DMA2_BASE + 0x0A0)
#define DMA2_Stream7_BASE     (DMA2_BASE + 0x0B8)


#define DMAMUX1_Channel0_BASE    (DMAMUX1_BASE)
#define DMAMUX1_Channel1_BASE    (DMAMUX1_BASE + 0x0004)
#define DMAMUX1_Channel2_BASE    (DMAMUX1_BASE + 0x0008)
#define DMAMUX1_Channel3_BASE    (DMAMUX1_BASE + 0x000C)
#define DMAMUX1_Channel4_BASE    (DMAMUX1_BASE + 0x0010)
#define DMAMUX1_Channel5_BASE    (DMAMUX1_BASE + 0x0014)
#define DMAMUX1_Channel6_BASE    (DMAMUX1_BASE + 0x0018)
#define DMAMUX1_Channel7_BASE    (DMAMUX1_BASE + 0x001C)
#define DMAMUX1_Channel8_BASE    (DMAMUX1_BASE + 0x0020)
#define DMAMUX1_Channel9_BASE    (DMAMUX1_BASE + 0x0024)
#define DMAMUX1_Channel10_BASE   (DMAMUX1_BASE + 0x0028)
#define DMAMUX1_Channel11_BASE   (DMAMUX1_BASE + 0x002C)
#define DMAMUX1_Channel12_BASE   (DMAMUX1_BASE + 0x0030)
#define DMAMUX1_Channel13_BASE   (DMAMUX1_BASE + 0x0034)
#define DMAMUX1_Channel14_BASE   (DMAMUX1_BASE + 0x0038)
#define DMAMUX1_Channel15_BASE   (DMAMUX1_BASE + 0x003C)

#define DMAMUX1_RequestGenerator0_BASE  (DMAMUX1_BASE + 0x0100)
#define DMAMUX1_RequestGenerator1_BASE  (DMAMUX1_BASE + 0x0104)
#define DMAMUX1_RequestGenerator2_BASE  (DMAMUX1_BASE + 0x0108)
#define DMAMUX1_RequestGenerator3_BASE  (DMAMUX1_BASE + 0x010C)

#define DMAMUX1_ChannelStatus_BASE      (DMAMUX1_BASE + 0x0080)
#define DMAMUX1_RequestGenStatus_BASE   (DMAMUX1_BASE + 0x0140)


/*!< FMC Banks registers base  address */
#define FMC_Bank1_R_BASE      (FMC_R_BASE + 0x0000)
#define FMC_Bank1E_R_BASE     (FMC_R_BASE + 0x0104)
#define FMC_Bank2_R_BASE      (FMC_R_BASE + 0x0060)
#define FMC_Bank3_R_BASE      (FMC_R_BASE + 0x0080)
#define FMC_Bank5_6_R_BASE    (FMC_R_BASE + 0x0140)

#define MDMA_NB_CHANNELS        32
#define MDMA_Channel0_BASE    (MDMA_BASE + 0x00000040)
#define MDMA_Channel1_BASE    (MDMA_BASE + 0x00000080)
#define MDMA_Channel2_BASE    (MDMA_BASE + 0x000000C0)
#define MDMA_Channel3_BASE    (MDMA_BASE + 0x00000100)
#define MDMA_Channel4_BASE    (MDMA_BASE + 0x00000140)
#define MDMA_Channel5_BASE    (MDMA_BASE + 0x00000180)
#define MDMA_Channel6_BASE    (MDMA_BASE + 0x000001C0)
#define MDMA_Channel7_BASE    (MDMA_BASE + 0x00000200)
#define MDMA_Channel8_BASE    (MDMA_BASE + 0x00000240)
#define MDMA_Channel9_BASE    (MDMA_BASE + 0x00000280)
#define MDMA_Channel10_BASE   (MDMA_BASE + 0x000002C0)
#define MDMA_Channel11_BASE   (MDMA_BASE + 0x00000300)
#define MDMA_Channel12_BASE   (MDMA_BASE + 0x00000340)
#define MDMA_Channel13_BASE   (MDMA_BASE + 0x00000380)
#define MDMA_Channel14_BASE   (MDMA_BASE + 0x000003C0)
#define MDMA_Channel15_BASE   (MDMA_BASE + 0x00000400)
#define MDMA_Channel16_BASE   (MDMA_BASE + 0x00000440)
#define MDMA_Channel17_BASE   (MDMA_BASE + 0x00000480)
#define MDMA_Channel18_BASE   (MDMA_BASE + 0x000004C0)
#define MDMA_Channel19_BASE   (MDMA_BASE + 0x00000500)
#define MDMA_Channel20_BASE   (MDMA_BASE + 0x00000540)
#define MDMA_Channel21_BASE   (MDMA_BASE + 0x00000580)
#define MDMA_Channel22_BASE   (MDMA_BASE + 0x000005C0)
#define MDMA_Channel23_BASE   (MDMA_BASE + 0x00000600)
#define MDMA_Channel24_BASE   (MDMA_BASE + 0x00000640)
#define MDMA_Channel25_BASE   (MDMA_BASE + 0x00000680)
#define MDMA_Channel26_BASE   (MDMA_BASE + 0x000006C0)
#define MDMA_Channel27_BASE   (MDMA_BASE + 0x00000700)
#define MDMA_Channel28_BASE   (MDMA_BASE + 0x00000740)
#define MDMA_Channel29_BASE   (MDMA_BASE + 0x00000780)
#define MDMA_Channel30_BASE   (MDMA_BASE + 0x000007C0)
#define MDMA_Channel31_BASE   (MDMA_BASE + 0x00000800)

/**
  * @}
  */

/** @addtogroup Peripheral_declaration
  * @{
  */
#define TIM2                ((TIM_TypeDef *) TIM2_BASE)
#define TIM3                ((TIM_TypeDef *) TIM3_BASE)
#define TIM4                ((TIM_TypeDef *) TIM4_BASE)
#define TIM5                ((TIM_TypeDef *) TIM5_BASE)
#define TIM6                ((TIM_TypeDef *) TIM6_BASE)
#define TIM7                ((TIM_TypeDef *) TIM7_BASE)
#define TIM12               ((TIM_TypeDef *) TIM12_BASE)
#define TIM13               ((TIM_TypeDef *) TIM13_BASE)
#define TIM14               ((TIM_TypeDef *) TIM14_BASE)
#define LCD                 ((LCD_TypeDef *) LCD_BASE)
#define RTC                 ((RTC_TypeDef *) RTC_BASE)
#define TAMP                 ((TAMP_TypeDef *) TAMP_BASE)
#define WWDG1               ((WWDG_TypeDef *) WWDG1_BASE)
#define IWDG1               ((IWDG_TypeDef *) IWDG1_BASE)
#define IWDG2               ((IWDG_TypeDef *) IWDG2_BASE)
#define SPI2                ((SPI_TypeDef *) SPI2_BASE)
#define SPI3                ((SPI_TypeDef *) SPI3_BASE)
#define SPI4                ((SPI_TypeDef *) SPI4_BASE)
#define SPI5                ((SPI_TypeDef *) SPI5_BASE)
#define SPI6                ((SPI_TypeDef *) SPI6_BASE)
#define USART2              ((USART_TypeDef *) USART2_BASE)
#define USART3              ((USART_TypeDef *) USART3_BASE)
#define USART6              ((USART_TypeDef *) USART6_BASE)
#define UART7               ((USART_TypeDef *) UART7_BASE)
#define UART8               ((USART_TypeDef *) UART8_BASE)
#define UART4               ((USART_TypeDef *) UART4_BASE)
#define UART5               ((USART_TypeDef *) UART5_BASE)
#define I2C1                ((I2C_TypeDef *) I2C1_BASE)
#define I2C2                ((I2C_TypeDef *) I2C2_BASE)
#define I2C3                ((I2C_TypeDef *) I2C3_BASE)
#define I2C4                ((I2C_TypeDef *) I2C4_BASE)
#define I2C5                ((I2C_TypeDef *) I2C5_BASE)
#define I2C6                ((I2C_TypeDef *) I2C6_BASE)
#define FDCAN1              ((FDCAN_GlobalTypeDef *) FDCAN1_BASE)
#define FDCAN2              ((FDCAN_GlobalTypeDef *) FDCAN2_BASE)
#define TTFDCAN1            ((TTCAN_TypeDef *) TTFDCAN1_BASE)
#define FDCAN_CCU           ((FDCAN_ClockCalibrationUnit_TypeDef *) FDCAN_CCU_BASE)
#define CEC                 ((CEC_TypeDef *) CEC_BASE)
#define LPTIM1              ((LPTIM_TypeDef *) LPTIM1_BASE)
#define PWR                 ((PWR_TypeDef *) PWR_BASE)
#define DAC1                ((DAC_TypeDef *) DAC1_BASE)
#define LPTIM2              ((LPTIM_TypeDef *) LPTIM2_BASE)
#define LPTIM3              ((LPTIM_TypeDef *) LPTIM3_BASE)
#define LPTIM4              ((LPTIM_TypeDef *) LPTIM4_BASE)
#define LPTIM5              ((LPTIM_TypeDef *) LPTIM5_BASE)
#define SYSCFG              ((SYSCFG_TypeDef *) SYSCFG_BASE)
#define VREFBUF             ((VREF_TypeDef *) VREFBUF_BASE)



#define EXTI                ((EXTI_TypeDef *) EXTI_BASE)
#define EXTI_C1             ((EXTI_Core_TypeDef *) EXTI_C1_BASE)
#define EXTI_C2             ((EXTI_Core_TypeDef *) EXTI_C2_BASE)
#define TIM1                ((TIM_TypeDef *) TIM1_BASE)
#define SPI1                ((SPI_TypeDef *) SPI1_BASE)
#define TIM8                ((TIM_TypeDef *) TIM8_BASE)
#define USART1              ((USART_TypeDef *) USART1_BASE)
#define TIM15               ((TIM_TypeDef *) TIM15_BASE)
#define TIM16               ((TIM_TypeDef *) TIM16_BASE)
#define TIM17               ((TIM_TypeDef *) TIM17_BASE)
#define SAI1                ((SAI_TypeDef *) SAI1_BASE)
#define SAI1_Block_A        ((SAI_Block_TypeDef *)SAI1_Block_A_BASE)
#define SAI1_Block_B        ((SAI_Block_TypeDef *)SAI1_Block_B_BASE)
#define SAI2                ((SAI_TypeDef *) SAI2_BASE)
#define SAI2_Block_A        ((SAI_Block_TypeDef *)SAI2_Block_A_BASE)
#define SAI2_Block_B        ((SAI_Block_TypeDef *)SAI2_Block_B_BASE)
#define SAI3                ((SAI_TypeDef *) SAI3_BASE)
#define SAI3_Block_A        ((SAI_Block_TypeDef *)SAI3_Block_A_BASE)
#define SAI3_Block_B        ((SAI_Block_TypeDef *)SAI3_Block_B_BASE)
#define SAI4                ((SAI_TypeDef *) SAI4_BASE)
#define SAI4_Block_A        ((SAI_Block_TypeDef *)SAI4_Block_A_BASE)
#define SAI4_Block_B        ((SAI_Block_TypeDef *)SAI4_Block_B_BASE)
#define DTS1                ((DTS_TypeDef *) DTS_BASE)
#define PMB                 ((PMB_TypeDef *) PMB_BASE)
#define SPDIFRX             ((SPDIFRX_TypeDef *) SPDIFRX_BASE)
#define DFSDM1              ((DFSDM_TypeDef *) DFSDM1_BASE)
#define DFSDM1_Channel0     ((DFSDM_Channel_TypeDef *) DFSDM1_Channel0_BASE)
#define DFSDM1_Channel1     ((DFSDM_Channel_TypeDef *) DFSDM1_Channel1_BASE)
#define DFSDM1_Channel2     ((DFSDM_Channel_TypeDef *) DFSDM1_Channel2_BASE)
#define DFSDM1_Channel3     ((DFSDM_Channel_TypeDef *) DFSDM1_Channel3_BASE)
#define DFSDM1_Channel4     ((DFSDM_Channel_TypeDef *) DFSDM1_Channel4_BASE)
#define DFSDM1_Channel5     ((DFSDM_Channel_TypeDef *) DFSDM1_Channel5_BASE)
#define DFSDM1_Channel6     ((DFSDM_Channel_TypeDef *) DFSDM1_Channel6_BASE)
#define DFSDM1_Channel7     ((DFSDM_Channel_TypeDef *) DFSDM1_Channel7_BASE)
#define DFSDM1_Filter0      ((DFSDM_Filter_TypeDef *) DFSDM1_Filter0_BASE)
#define DFSDM1_Filter1      ((DFSDM_Filter_TypeDef *) DFSDM1_Filter1_BASE)
#define DFSDM1_Filter2      ((DFSDM_Filter_TypeDef *) DFSDM1_Filter2_BASE)
#define DFSDM1_Filter3      ((DFSDM_Filter_TypeDef *) DFSDM1_Filter3_BASE)
#define DFSDM1_Filter4      ((DFSDM_Filter_TypeDef *) DFSDM1_Filter4_BASE)
#define DFSDM1_Filter5      ((DFSDM_Filter_TypeDef *) DFSDM1_Filter5_BASE)
#define DCMI                ((DCMI_TypeDef *) DCMI_BASE)

#define RCC                 ((RCC_TypeDef *) RCC_BASE)

#define HDP                 ((HDP_TypeDef *) HDP_BASE)

#define BSEC                ((BSEC_TypeDef *) BSEC_BASE)


#define CRC2                 ((CRC_TypeDef *) CRC2_BASE)
#define CRC1                     ((CRC_TypeDef *) CRC1_BASE)

#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF               ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG               ((GPIO_TypeDef *) GPIOG_BASE)
#define GPIOH               ((GPIO_TypeDef *) GPIOH_BASE)
#define GPIOI               ((GPIO_TypeDef *) GPIOI_BASE)
#define GPIOJ               ((GPIO_TypeDef *) GPIOJ_BASE)
#define GPIOK               ((GPIO_TypeDef *) GPIOK_BASE)
#define ADC1                ((ADC_TypeDef *) ADC1_BASE)
#define ADC2                ((ADC_TypeDef *) ADC2_BASE)
#define ADC12_COMMON        ((ADC_Common_TypeDef *) ADC12_COMMON_BASE)

#define IPCC                ((IPCC_TypeDef *) IPCC_BASE)
#define IPCC_C1             ((IPCC_CommonTypeDef *) IPCC_BASE)
#define IPCC_C2             ((IPCC_CommonTypeDef *) (IPCC_BASE + 0x10U))
#define CRYP2               ((CRYP_TypeDef *) CRYP2_BASE)
#define CRYP1               ((CRYP_TypeDef *) CRYP1_BASE)
#define HASH2               ((HASH_TypeDef *) HASH2_BASE)
#define HASH1               ((HASH_TypeDef *) HASH1_BASE)
#define HASH2_DIGEST        ((HASH_DIGEST_TypeDef *) HASH2_DIGEST_BASE)
#define HASH1_DIGEST        ((HASH_DIGEST_TypeDef *) HASH1_DIGEST_BASE)
#define HASH                ((HASH_TypeDef *) HASH1)
#define HASH_DIGEST         ((HASH_DIGEST_TypeDef *) HASH1_DIGEST)
#define RNG2                ((RNG_TypeDef *) RNG2_BASE)
#define RNG1                ((RNG_TypeDef *) RNG1_BASE)
#define GPIOZ               ((GPIO_TypeDef *) GPIOZ_BASE)
#define SDMMC2              ((SDMMC_TypeDef *) SDMMC2_BASE)

#define DLYB_SDMMC1         ((DLYB_TypeDef *) DLYB_SDMMC1_BASE)
#define DLYB_SDMMC2         ((DLYB_TypeDef *) DLYB_SDMMC2_BASE)
#define DLYB_SDMMC3         ((DLYB_TypeDef *) DLYB_SDMMC3_BASE)


#define DMA2                ((DMA_TypeDef *) DMA2_BASE)
#define DMA2_Stream0        ((DMA_Stream_TypeDef *) DMA2_Stream0_BASE)
#define DMA2_Stream1        ((DMA_Stream_TypeDef *) DMA2_Stream1_BASE)
#define DMA2_Stream2        ((DMA_Stream_TypeDef *) DMA2_Stream2_BASE)
#define DMA2_Stream3        ((DMA_Stream_TypeDef *) DMA2_Stream3_BASE)
#define DMA2_Stream4        ((DMA_Stream_TypeDef *) DMA2_Stream4_BASE)
#define DMA2_Stream5        ((DMA_Stream_TypeDef *) DMA2_Stream5_BASE)
#define DMA2_Stream6        ((DMA_Stream_TypeDef *) DMA2_Stream6_BASE)
#define DMA2_Stream7        ((DMA_Stream_TypeDef *) DMA2_Stream7_BASE)

#define DMA1                ((DMA_TypeDef *) DMA1_BASE)
#define DMA1_Stream0        ((DMA_Stream_TypeDef *) DMA1_Stream0_BASE)
#define DMA1_Stream1        ((DMA_Stream_TypeDef *) DMA1_Stream1_BASE)
#define DMA1_Stream2        ((DMA_Stream_TypeDef *) DMA1_Stream2_BASE)
#define DMA1_Stream3        ((DMA_Stream_TypeDef *) DMA1_Stream3_BASE)
#define DMA1_Stream4        ((DMA_Stream_TypeDef *) DMA1_Stream4_BASE)
#define DMA1_Stream5        ((DMA_Stream_TypeDef *) DMA1_Stream5_BASE)
#define DMA1_Stream6        ((DMA_Stream_TypeDef *) DMA1_Stream6_BASE)
#define DMA1_Stream7        ((DMA_Stream_TypeDef *) DMA1_Stream7_BASE)

#define DMAMUX1              ((DMAMUX_Channel_TypeDef *) DMAMUX1_BASE)
#define DMAMUX1_Channel0     ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel0_BASE)
#define DMAMUX1_Channel1     ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel1_BASE)
#define DMAMUX1_Channel2     ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel2_BASE)
#define DMAMUX1_Channel3     ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel3_BASE)
#define DMAMUX1_Channel4     ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel4_BASE)
#define DMAMUX1_Channel5     ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel5_BASE)
#define DMAMUX1_Channel6     ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel6_BASE)
#define DMAMUX1_Channel7     ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel7_BASE)
#define DMAMUX1_Channel8     ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel8_BASE)
#define DMAMUX1_Channel9     ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel9_BASE)
#define DMAMUX1_Channel10    ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel10_BASE)
#define DMAMUX1_Channel11    ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel11_BASE)
#define DMAMUX1_Channel12    ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel12_BASE)
#define DMAMUX1_Channel13    ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel13_BASE)
#define DMAMUX1_Channel14    ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel14_BASE)
#define DMAMUX1_Channel15    ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel15_BASE)

#define DMAMUX1_RequestGenerator0  ((DMAMUX_RequestGen_TypeDef *) DMAMUX1_RequestGenerator0_BASE)
#define DMAMUX1_RequestGenerator1  ((DMAMUX_RequestGen_TypeDef *) DMAMUX1_RequestGenerator1_BASE)
#define DMAMUX1_RequestGenerator2  ((DMAMUX_RequestGen_TypeDef *) DMAMUX1_RequestGenerator2_BASE)
#define DMAMUX1_RequestGenerator3  ((DMAMUX_RequestGen_TypeDef *) DMAMUX1_RequestGenerator3_BASE)

#define DMAMUX1_ChannelStatus      ((DMAMUX_ChannelStatus_TypeDef *)    DMAMUX1_ChannelStatus_BASE)
#define DMAMUX1_RequestGenStatus   ((DMAMUX_RequestGenStatus_TypeDef *) DMAMUX1_RequestGenStatus_BASE)


#define FMC_Bank1_R         ((FMC_Bank1_TypeDef *) FMC_Bank1_R_BASE)
#define FMC_Bank1E_R        ((FMC_Bank1E_TypeDef *) FMC_Bank1E_R_BASE)
#define FMC_Bank3_R         ((FMC_Bank3_TypeDef *) FMC_Bank3_R_BASE)

#define QUADSPI               ((QUADSPI_TypeDef *) QSPI_R_BASE)
#define DLYB_QUADSPI          ((DLYB_TypeDef *) DLYB_QSPI_BASE)

#define SDMMC1                ((SDMMC_TypeDef *) SDMMC1_BASE)
#define SDMMC3                ((SDMMC_TypeDef *) SDMMC3_BASE)

#define DBGMCU              ((DBGMCU_TypeDef *) DBGMCU_BASE)

#define JPEG                ((JPEG_TypeDef *) JPGDEC_BASE)
#define HSEM                ((HSEM_TypeDef *) HSEM_BASE)
#define HSEM_COMMON         ((HSEM_Common_TypeDef *) (HSEM_BASE + 0x100U))


#define USBPHYC             ((USBPHYC_GlobalTypeDef *)USBPHYC_BASE)
#define USBPHYC_PHY1        ((USBPHYC_InstanceTypeDef *)USBPHYC_PHY1_BASE)
#define USBPHYC_PHY2        ((USBPHYC_InstanceTypeDef *)USBPHYC_PHY2_BASE)

#define DDRCTRL             ((DDRCTRL_TypeDef *)DDRCTRL_BASE)
#define DDRPERFM            ((DDRPERFM_TypeDef *)DDRPERFM_BASE)
#define DDRPHYC             ((DDRPHYC_TypeDef *)DDRPHYC_BASE)
#define LTDC                ((LTDC_TypeDef *)LTDC_BASE)
#define LTDC_Layer1         ((LTDC_Layer_TypeDef *)LTDC_Layer1_BASE)
#define LTDC_Layer2         ((LTDC_Layer_TypeDef *)LTDC_Layer2_BASE)
#define DSI                 ((DSI_TypeDef *)DSI_BASE)

#define TZC                 ((TZC_TypeDef *)TZC_BASE)
#define TZPC                ((TZPC_TypeDef *)TZPC_BASE)
#define STGENC              ((STGENC_TypeDef *)STGENC_BASE)
#define STGENR              ((STGENR_TypeDef *)STGENR_BASE)

#define MDIOS               ((MDIOS_TypeDef *) MDIOS_BASE)

#define ETH                 ((ETH_TypeDef *) ETH_BASE)
#define MDMA                ((MDMA_TypeDef *) MDMA_BASE)
#define MDMA_Channel0       ((MDMA_Channel_TypeDef *)MDMA_Channel0_BASE)
#define MDMA_Channel1       ((MDMA_Channel_TypeDef *)MDMA_Channel1_BASE)
#define MDMA_Channel2       ((MDMA_Channel_TypeDef *)MDMA_Channel2_BASE)
#define MDMA_Channel3       ((MDMA_Channel_TypeDef *)MDMA_Channel3_BASE)
#define MDMA_Channel4       ((MDMA_Channel_TypeDef *)MDMA_Channel4_BASE)
#define MDMA_Channel5       ((MDMA_Channel_TypeDef *)MDMA_Channel5_BASE)
#define MDMA_Channel6       ((MDMA_Channel_TypeDef *)MDMA_Channel6_BASE)
#define MDMA_Channel7       ((MDMA_Channel_TypeDef *)MDMA_Channel7_BASE)
#define MDMA_Channel8       ((MDMA_Channel_TypeDef *)MDMA_Channel8_BASE)
#define MDMA_Channel9       ((MDMA_Channel_TypeDef *)MDMA_Channel9_BASE)
#define MDMA_Channel10      ((MDMA_Channel_TypeDef *)MDMA_Channel10_BASE)
#define MDMA_Channel11      ((MDMA_Channel_TypeDef *)MDMA_Channel11_BASE)
#define MDMA_Channel12      ((MDMA_Channel_TypeDef *)MDMA_Channel12_BASE)
#define MDMA_Channel13      ((MDMA_Channel_TypeDef *)MDMA_Channel13_BASE)
#define MDMA_Channel14      ((MDMA_Channel_TypeDef *)MDMA_Channel14_BASE)
#define MDMA_Channel15      ((MDMA_Channel_TypeDef *)MDMA_Channel15_BASE)
#define MDMA_Channel16      ((MDMA_Channel_TypeDef *)MDMA_Channel16_BASE)
#define MDMA_Channel17      ((MDMA_Channel_TypeDef *)MDMA_Channel17_BASE)
#define MDMA_Channel18      ((MDMA_Channel_TypeDef *)MDMA_Channel18_BASE)
#define MDMA_Channel19      ((MDMA_Channel_TypeDef *)MDMA_Channel19_BASE)
#define MDMA_Channel20      ((MDMA_Channel_TypeDef *)MDMA_Channel20_BASE)
#define MDMA_Channel21      ((MDMA_Channel_TypeDef *)MDMA_Channel21_BASE)
#define MDMA_Channel22      ((MDMA_Channel_TypeDef *)MDMA_Channel22_BASE)
#define MDMA_Channel23      ((MDMA_Channel_TypeDef *)MDMA_Channel23_BASE)
#define MDMA_Channel24      ((MDMA_Channel_TypeDef *)MDMA_Channel24_BASE)
#define MDMA_Channel25      ((MDMA_Channel_TypeDef *)MDMA_Channel25_BASE)
#define MDMA_Channel26      ((MDMA_Channel_TypeDef *)MDMA_Channel26_BASE)
#define MDMA_Channel27      ((MDMA_Channel_TypeDef *)MDMA_Channel27_BASE)
#define MDMA_Channel28      ((MDMA_Channel_TypeDef *)MDMA_Channel28_BASE)
#define MDMA_Channel29      ((MDMA_Channel_TypeDef *)MDMA_Channel29_BASE)
#define MDMA_Channel30      ((MDMA_Channel_TypeDef *)MDMA_Channel30_BASE)
#define MDMA_Channel31      ((MDMA_Channel_TypeDef *)MDMA_Channel31_BASE)

#define USB_OTG_HS            ((USB_OTG_GlobalTypeDef *) USBOTG_BASE)
/* backward compatibility */
#define USB1_OTG_HS           USB_OTG_HS
#define USB2_OTG_FS           ((USB_OTG_GlobalTypeDef *) 0x00000000)
#define USB_OTG_FS            USB2_OTG_FS

#define USB1_EHCI             ((USB_EHCI_CapabilityTypeDef *) USB1HSFSP1_BASE)

#define GPU                   ((GPU_Host_InterfaceTypeDef *) GPU_BASE)



/**
  * @}
  */
