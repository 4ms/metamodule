
/******************************************************************************/
/*                                                                            */
/*                                    TIM                                     */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for TIM_CR1 register  ********************/
#define TIM_CR1_CEN               ((uint16_t)0x0001)                           /*!<Counter enable */
#define TIM_CR1_UDIS              ((uint16_t)0x0002)                           /*!<Update disable */
#define TIM_CR1_URS               ((uint16_t)0x0004)                           /*!<Update request source */
#define TIM_CR1_OPM               ((uint16_t)0x0008)                           /*!<One pulse mode */
#define TIM_CR1_DIR               ((uint16_t)0x0010)                           /*!<Direction */

#define TIM_CR1_CMS               ((uint16_t)0x0060)                           /*!<CMS[1:0] bits (Center-aligned mode selection) */
#define TIM_CR1_CMS_0             ((uint16_t)0x0020)                           /*!<Bit 0 */
#define TIM_CR1_CMS_1             ((uint16_t)0x0040)                           /*!<Bit 1 */

#define TIM_CR1_ARPE              ((uint16_t)0x0080)                           /*!<Auto-reload preload enable */

#define TIM_CR1_CKD               ((uint16_t)0x0300)                           /*!<CKD[1:0] bits (clock division) */
#define TIM_CR1_CKD_0             ((uint16_t)0x0100)                           /*!<Bit 0 */
#define TIM_CR1_CKD_1             ((uint16_t)0x0200)                           /*!<Bit 1 */

#define TIM_CR1_UIFREMAP          ((uint16_t)0x0800)                           /*!<Update interrupt flag remap */

/*******************  Bit definition for TIM_CR2 register  ********************/
#define TIM_CR2_CCPC_Pos          (0U)
#define TIM_CR2_CCPC_Msk          (0x1U << TIM_CR2_CCPC_Pos)                   /*!< 0x00000001 */
#define TIM_CR2_CCPC              TIM_CR2_CCPC_Msk                             /*!<Capture/Compare Preloaded Control */
#define TIM_CR2_CCUS_Pos          (2U)
#define TIM_CR2_CCUS_Msk          (0x1U << TIM_CR2_CCUS_Pos)                   /*!< 0x00000004 */
#define TIM_CR2_CCUS              TIM_CR2_CCUS_Msk                             /*!<Capture/Compare Control Update Selection */
#define TIM_CR2_CCDS_Pos          (3U)
#define TIM_CR2_CCDS_Msk          (0x1U << TIM_CR2_CCDS_Pos)                   /*!< 0x00000008 */
#define TIM_CR2_CCDS              TIM_CR2_CCDS_Msk                             /*!<Capture/Compare DMA Selection */

#define TIM_CR2_MMS_Pos           (4U)
#define TIM_CR2_MMS_Msk           (0x7U << TIM_CR2_MMS_Pos)                    /*!< 0x00000070 */
#define TIM_CR2_MMS               TIM_CR2_MMS_Msk                              /*!<MMS[2:0] bits (Master Mode Selection) */
#define TIM_CR2_MMS_0             (0x1U << TIM_CR2_MMS_Pos)                    /*!< 0x00000010 */
#define TIM_CR2_MMS_1             (0x2U << TIM_CR2_MMS_Pos)                    /*!< 0x00000020 */
#define TIM_CR2_MMS_2             (0x4U << TIM_CR2_MMS_Pos)                    /*!< 0x00000040 */

#define TIM_CR2_TI1S_Pos          (7U)
#define TIM_CR2_TI1S_Msk          (0x1U << TIM_CR2_TI1S_Pos)                   /*!< 0x00000080 */
#define TIM_CR2_TI1S              TIM_CR2_TI1S_Msk                             /*!<TI1 Selection */
#define TIM_CR2_OIS1_Pos          (8U)
#define TIM_CR2_OIS1_Msk          (0x1U << TIM_CR2_OIS1_Pos)                   /*!< 0x00000100 */
#define TIM_CR2_OIS1              TIM_CR2_OIS1_Msk                             /*!<Output Idle state 1 (OC1 output) */
#define TIM_CR2_OIS1N_Pos         (9U)
#define TIM_CR2_OIS1N_Msk         (0x1U << TIM_CR2_OIS1N_Pos)                  /*!< 0x00000200 */
#define TIM_CR2_OIS1N             TIM_CR2_OIS1N_Msk                            /*!<Output Idle state 1 (OC1N output) */
#define TIM_CR2_OIS2_Pos          (10U)
#define TIM_CR2_OIS2_Msk          (0x1U << TIM_CR2_OIS2_Pos)                   /*!< 0x00000400 */
#define TIM_CR2_OIS2              TIM_CR2_OIS2_Msk                             /*!<Output Idle state 2 (OC2 output) */
#define TIM_CR2_OIS2N_Pos         (11U)
#define TIM_CR2_OIS2N_Msk         (0x1U << TIM_CR2_OIS2N_Pos)                  /*!< 0x00000800 */
#define TIM_CR2_OIS2N             TIM_CR2_OIS2N_Msk                            /*!<Output Idle state 2 (OC2N output) */
#define TIM_CR2_OIS3_Pos          (12U)
#define TIM_CR2_OIS3_Msk          (0x1U << TIM_CR2_OIS3_Pos)                   /*!< 0x00001000 */
#define TIM_CR2_OIS3              TIM_CR2_OIS3_Msk                             /*!<Output Idle state 3 (OC3 output) */
#define TIM_CR2_OIS3N_Pos         (13U)
#define TIM_CR2_OIS3N_Msk         (0x1U << TIM_CR2_OIS3N_Pos)                  /*!< 0x00002000 */
#define TIM_CR2_OIS3N             TIM_CR2_OIS3N_Msk                            /*!<Output Idle state 3 (OC3N output) */
#define TIM_CR2_OIS4_Pos          (14U)
#define TIM_CR2_OIS4_Msk          (0x1U << TIM_CR2_OIS4_Pos)                   /*!< 0x00004000 */
#define TIM_CR2_OIS4              TIM_CR2_OIS4_Msk                             /*!<Output Idle state 4 (OC4 output) */
#define TIM_CR2_OIS5_Pos          (16U)
#define TIM_CR2_OIS5_Msk          (0x1U << TIM_CR2_OIS5_Pos)                   /*!< 0x00010000 */
#define TIM_CR2_OIS5              TIM_CR2_OIS5_Msk                             /*!<Output Idle state 4 (OC4 output) */
#define TIM_CR2_OIS6_Pos          (18U)
#define TIM_CR2_OIS6_Msk          (0x1U << TIM_CR2_OIS6_Pos)                   /*!< 0x00040000 */
#define TIM_CR2_OIS6              TIM_CR2_OIS6_Msk                             /*!<Output Idle state 4 (OC4 output) */

#define TIM_CR2_MMS2_Pos          (20U)
#define TIM_CR2_MMS2_Msk          (0xFU << TIM_CR2_MMS2_Pos)                   /*!< 0x00F00000 */
#define TIM_CR2_MMS2              TIM_CR2_MMS2_Msk                             /*!<MMS[2:0] bits (Master Mode Selection) */
#define TIM_CR2_MMS2_0            (0x1U << TIM_CR2_MMS2_Pos)                   /*!< 0x00100000 */
#define TIM_CR2_MMS2_1            (0x2U << TIM_CR2_MMS2_Pos)                   /*!< 0x00200000 */
#define TIM_CR2_MMS2_2            (0x4U << TIM_CR2_MMS2_Pos)                   /*!< 0x00400000 */
#define TIM_CR2_MMS2_3            (0x8U << TIM_CR2_MMS2_Pos)                   /*!< 0x00800000 */

/*******************  Bit definition for TIM_SMCR register  *******************/
#define TIM_SMCR_SMS_Pos          (0U)
#define TIM_SMCR_SMS_Msk          (0x10007U << TIM_SMCR_SMS_Pos)               /*!< 0x00010007 */
#define TIM_SMCR_SMS              TIM_SMCR_SMS_Msk                             /*!<SMS[2:0] bits (Slave mode selection) */
#define TIM_SMCR_SMS_0            (0x00001U << TIM_SMCR_SMS_Pos)               /*!< 0x00000001 */
#define TIM_SMCR_SMS_1            (0x00002U << TIM_SMCR_SMS_Pos)               /*!< 0x00000002 */
#define TIM_SMCR_SMS_2            (0x00004U << TIM_SMCR_SMS_Pos)               /*!< 0x00000004 */
#define TIM_SMCR_SMS_3            (0x10000U << TIM_SMCR_SMS_Pos)               /*!< 0x00010000 */

#define TIM_SMCR_TS_Pos           (4U)
#define TIM_SMCR_TS_Msk           (0x30007U << TIM_SMCR_TS_Pos)                /*!< 0x00300070 */
#define TIM_SMCR_TS               TIM_SMCR_TS_Msk                              /*!<TS[4:0] bits (Trigger selection) */
#define TIM_SMCR_TS_0             (0x00001U << TIM_SMCR_TS_Pos)                /*!< 0x00000010 */
#define TIM_SMCR_TS_1             (0x00002U << TIM_SMCR_TS_Pos)                /*!< 0x00000020 */
#define TIM_SMCR_TS_2             (0x00004U << TIM_SMCR_TS_Pos)                /*!< 0x00000040 */
#define TIM_SMCR_TS_3             (0x10000U << TIM_SMCR_TS_Pos)                /*!< 0x00100000 */
#define TIM_SMCR_TS_4             (0x20000U << TIM_SMCR_TS_Pos)                /*!< 0x00200000 */

#define TIM_SMCR_MSM_Pos          (7U)
#define TIM_SMCR_MSM_Msk          (0x1U << TIM_SMCR_MSM_Pos)                   /*!< 0x00000080 */
#define TIM_SMCR_MSM              TIM_SMCR_MSM_Msk                             /*!<Master/slave mode */

#define TIM_SMCR_ETF_Pos          (8U)
#define TIM_SMCR_ETF_Msk          (0xFU << TIM_SMCR_ETF_Pos)                   /*!< 0x00000F00 */
#define TIM_SMCR_ETF              TIM_SMCR_ETF_Msk                             /*!<ETF[3:0] bits (External trigger filter) */
#define TIM_SMCR_ETF_0            (0x1U << TIM_SMCR_ETF_Pos)                   /*!< 0x00000100 */
#define TIM_SMCR_ETF_1            (0x2U << TIM_SMCR_ETF_Pos)                   /*!< 0x00000200 */
#define TIM_SMCR_ETF_2            (0x4U << TIM_SMCR_ETF_Pos)                   /*!< 0x00000400 */
#define TIM_SMCR_ETF_3            (0x8U << TIM_SMCR_ETF_Pos)                   /*!< 0x00000800 */

#define TIM_SMCR_ETPS_Pos         (12U)
#define TIM_SMCR_ETPS_Msk         (0x3U << TIM_SMCR_ETPS_Pos)                  /*!< 0x00003000 */
#define TIM_SMCR_ETPS             TIM_SMCR_ETPS_Msk                            /*!<ETPS[1:0] bits (External trigger prescaler) */
#define TIM_SMCR_ETPS_0           (0x1U << TIM_SMCR_ETPS_Pos)                  /*!< 0x00001000 */
#define TIM_SMCR_ETPS_1           (0x2U << TIM_SMCR_ETPS_Pos)                  /*!< 0x00002000 */

#define TIM_SMCR_ECE_Pos          (14U)
#define TIM_SMCR_ECE_Msk          (0x1U << TIM_SMCR_ECE_Pos)                   /*!< 0x00004000 */
#define TIM_SMCR_ECE              TIM_SMCR_ECE_Msk                             /*!<External clock enable */
#define TIM_SMCR_ETP_Pos          (15U)
#define TIM_SMCR_ETP_Msk          (0x1U << TIM_SMCR_ETP_Pos)                   /*!< 0x00008000 */
#define TIM_SMCR_ETP              TIM_SMCR_ETP_Msk                             /*!<External trigger polarity */

/*******************  Bit definition for TIM_DIER register  *******************/
#define TIM_DIER_UIE              ((uint16_t)0x0001)                           /*!<Update interrupt enable */
#define TIM_DIER_CC1IE            ((uint16_t)0x0002)                           /*!<Capture/Compare 1 interrupt enable */
#define TIM_DIER_CC2IE            ((uint16_t)0x0004)                           /*!<Capture/Compare 2 interrupt enable */
#define TIM_DIER_CC3IE            ((uint16_t)0x0008)                           /*!<Capture/Compare 3 interrupt enable */
#define TIM_DIER_CC4IE            ((uint16_t)0x0010)                           /*!<Capture/Compare 4 interrupt enable */
#define TIM_DIER_COMIE            ((uint16_t)0x0020)                           /*!<COM interrupt enable */
#define TIM_DIER_TIE              ((uint16_t)0x0040)                           /*!<Trigger interrupt enable */
#define TIM_DIER_BIE              ((uint16_t)0x0080)                           /*!<Break interrupt enable */
#define TIM_DIER_UDE              ((uint16_t)0x0100)                           /*!<Update DMA request enable */
#define TIM_DIER_CC1DE            ((uint16_t)0x0200)                           /*!<Capture/Compare 1 DMA request enable */
#define TIM_DIER_CC2DE            ((uint16_t)0x0400)                           /*!<Capture/Compare 2 DMA request enable */
#define TIM_DIER_CC3DE            ((uint16_t)0x0800)                           /*!<Capture/Compare 3 DMA request enable */
#define TIM_DIER_CC4DE            ((uint16_t)0x1000)                           /*!<Capture/Compare 4 DMA request enable */
#define TIM_DIER_COMDE            ((uint16_t)0x2000)                           /*!<COM DMA request enable */
#define TIM_DIER_TDE              ((uint16_t)0x4000)                           /*!<Trigger DMA request enable */

/********************  Bit definition for TIM_SR register  ********************/
#define TIM_SR_UIF_Pos            (0U)
#define TIM_SR_UIF_Msk            (0x1U << TIM_SR_UIF_Pos)                     /*!< 0x00000001 */
#define TIM_SR_UIF                TIM_SR_UIF_Msk                               /*!<Update interrupt Flag */
#define TIM_SR_CC1IF_Pos          (1U)
#define TIM_SR_CC1IF_Msk          (0x1U << TIM_SR_CC1IF_Pos)                   /*!< 0x00000002 */
#define TIM_SR_CC1IF              TIM_SR_CC1IF_Msk                             /*!<Capture/Compare 1 interrupt Flag */
#define TIM_SR_CC2IF_Pos          (2U)
#define TIM_SR_CC2IF_Msk          (0x1U << TIM_SR_CC2IF_Pos)                   /*!< 0x00000004 */
#define TIM_SR_CC2IF              TIM_SR_CC2IF_Msk                             /*!<Capture/Compare 2 interrupt Flag */
#define TIM_SR_CC3IF_Pos          (3U)
#define TIM_SR_CC3IF_Msk          (0x1U << TIM_SR_CC3IF_Pos)                   /*!< 0x00000008 */
#define TIM_SR_CC3IF              TIM_SR_CC3IF_Msk                             /*!<Capture/Compare 3 interrupt Flag */
#define TIM_SR_CC4IF_Pos          (4U)
#define TIM_SR_CC4IF_Msk          (0x1U << TIM_SR_CC4IF_Pos)                   /*!< 0x00000010 */
#define TIM_SR_CC4IF              TIM_SR_CC4IF_Msk                             /*!<Capture/Compare 4 interrupt Flag */
#define TIM_SR_COMIF_Pos          (5U)
#define TIM_SR_COMIF_Msk          (0x1U << TIM_SR_COMIF_Pos)                   /*!< 0x00000020 */
#define TIM_SR_COMIF              TIM_SR_COMIF_Msk                             /*!<COM interrupt Flag */
#define TIM_SR_TIF_Pos            (6U)
#define TIM_SR_TIF_Msk            (0x1U << TIM_SR_TIF_Pos)                     /*!< 0x00000040 */
#define TIM_SR_TIF                TIM_SR_TIF_Msk                               /*!<Trigger interrupt Flag */
#define TIM_SR_BIF_Pos            (7U)
#define TIM_SR_BIF_Msk            (0x1U << TIM_SR_BIF_Pos)                     /*!< 0x00000080 */
#define TIM_SR_BIF                TIM_SR_BIF_Msk                               /*!<Break interrupt Flag */
#define TIM_SR_B2IF_Pos           (8U)
#define TIM_SR_B2IF_Msk           (0x1U << TIM_SR_B2IF_Pos)                    /*!< 0x00000100 */
#define TIM_SR_B2IF               TIM_SR_B2IF_Msk                              /*!<Break2 interrupt Flag */
#define TIM_SR_CC1OF_Pos          (9U)
#define TIM_SR_CC1OF_Msk          (0x1U << TIM_SR_CC1OF_Pos)                   /*!< 0x00000200 */
#define TIM_SR_CC1OF              TIM_SR_CC1OF_Msk                             /*!<Capture/Compare 1 Overcapture Flag */
#define TIM_SR_CC2OF_Pos          (10U)
#define TIM_SR_CC2OF_Msk          (0x1U << TIM_SR_CC2OF_Pos)                   /*!< 0x00000400 */
#define TIM_SR_CC2OF              TIM_SR_CC2OF_Msk                             /*!<Capture/Compare 2 Overcapture Flag */
#define TIM_SR_CC3OF_Pos          (11U)
#define TIM_SR_CC3OF_Msk          (0x1U << TIM_SR_CC3OF_Pos)                   /*!< 0x00000800 */
#define TIM_SR_CC3OF              TIM_SR_CC3OF_Msk                             /*!<Capture/Compare 3 Overcapture Flag */
#define TIM_SR_CC4OF_Pos          (12U)
#define TIM_SR_CC4OF_Msk          (0x1U << TIM_SR_CC4OF_Pos)                   /*!< 0x00001000 */
#define TIM_SR_CC4OF              TIM_SR_CC4OF_Msk                             /*!<Capture/Compare 4 Overcapture Flag */
#define TIM_SR_CC5IF_Pos          (16U)
#define TIM_SR_CC5IF_Msk          (0x1U << TIM_SR_CC5IF_Pos)                   /*!< 0x00010000 */
#define TIM_SR_CC5IF              TIM_SR_CC5IF_Msk                             /*!<Capture/Compare 5 interrupt Flag */
#define TIM_SR_CC6IF_Pos          (17U)
#define TIM_SR_CC6IF_Msk          (0x1U << TIM_SR_CC6IF_Pos)                   /*!< 0x00020000 */
#define TIM_SR_CC6IF              TIM_SR_CC6IF_Msk                             /*!<Capture/Compare 6 interrupt Flag */
#define TIM_SR_SBIF_Pos           (13U)
#define TIM_SR_SBIF_Msk           (0x1U << TIM_SR_SBIF_Pos)                    /*!< 0x00002000 */
#define TIM_SR_SBIF               TIM_SR_SBIF_Msk                              /*!< System Break Flag */

/*******************  Bit definition for TIM_EGR register  ********************/
#define TIM_EGR_UG                ((uint16_t)0x0001)                           /*!<Update Generation */
#define TIM_EGR_CC1G              ((uint16_t)0x0002)                           /*!<Capture/Compare 1 Generation */
#define TIM_EGR_CC2G              ((uint16_t)0x0004)                           /*!<Capture/Compare 2 Generation */
#define TIM_EGR_CC3G              ((uint16_t)0x0008)                           /*!<Capture/Compare 3 Generation */
#define TIM_EGR_CC4G              ((uint16_t)0x0010)                           /*!<Capture/Compare 4 Generation */
#define TIM_EGR_COMG              ((uint16_t)0x0020)                           /*!<Capture/Compare Control Update Generation */
#define TIM_EGR_TG                ((uint16_t)0x0040)                           /*!<Trigger Generation */
#define TIM_EGR_BG                ((uint16_t)0x0080)                           /*!<Break Generation */
#define TIM_EGR_B2G               ((uint16_t)0x0100)                           /*!<Break Generation */


/******************  Bit definition for TIM_CCMR1 register  *******************/
#define TIM_CCMR1_CC1S_Pos        (0U)
#define TIM_CCMR1_CC1S_Msk        (0x3U << TIM_CCMR1_CC1S_Pos)                 /*!< 0x00000003 */
#define TIM_CCMR1_CC1S            TIM_CCMR1_CC1S_Msk                           /*!<CC1S[1:0] bits (Capture/Compare 1 Selection) */
#define TIM_CCMR1_CC1S_0          (0x1U << TIM_CCMR1_CC1S_Pos)                 /*!< 0x00000001 */
#define TIM_CCMR1_CC1S_1          (0x2U << TIM_CCMR1_CC1S_Pos)                 /*!< 0x00000002 */

#define TIM_CCMR1_OC1FE_Pos       (2U)
#define TIM_CCMR1_OC1FE_Msk       (0x1U << TIM_CCMR1_OC1FE_Pos)                /*!< 0x00000004 */
#define TIM_CCMR1_OC1FE           TIM_CCMR1_OC1FE_Msk                          /*!<Output Compare 1 Fast enable */
#define TIM_CCMR1_OC1PE_Pos       (3U)
#define TIM_CCMR1_OC1PE_Msk       (0x1U << TIM_CCMR1_OC1PE_Pos)                /*!< 0x00000008 */
#define TIM_CCMR1_OC1PE           TIM_CCMR1_OC1PE_Msk                          /*!<Output Compare 1 Preload enable */

#define TIM_CCMR1_OC1M_Pos        (4U)
#define TIM_CCMR1_OC1M_Msk        (0x1007U << TIM_CCMR1_OC1M_Pos)              /*!< 0x00010070 */
#define TIM_CCMR1_OC1M            TIM_CCMR1_OC1M_Msk                           /*!<OC1M[2:0] bits (Output Compare 1 Mode) */
#define TIM_CCMR1_OC1M_0          (0x0001U << TIM_CCMR1_OC1M_Pos)              /*!< 0x00000010 */
#define TIM_CCMR1_OC1M_1          (0x0002U << TIM_CCMR1_OC1M_Pos)              /*!< 0x00000020 */
#define TIM_CCMR1_OC1M_2          (0x0004U << TIM_CCMR1_OC1M_Pos)              /*!< 0x00000040 */
#define TIM_CCMR1_OC1M_3          (0x1000U << TIM_CCMR1_OC1M_Pos)              /*!< 0x00010000 */

#define TIM_CCMR1_OC1CE_Pos       (7U)
#define TIM_CCMR1_OC1CE_Msk       (0x1U << TIM_CCMR1_OC1CE_Pos)                /*!< 0x00000080 */
#define TIM_CCMR1_OC1CE           TIM_CCMR1_OC1CE_Msk                          /*!<Output Compare 1Clear Enable */

#define TIM_CCMR1_CC2S_Pos        (8U)
#define TIM_CCMR1_CC2S_Msk        (0x3U << TIM_CCMR1_CC2S_Pos)                 /*!< 0x00000300 */
#define TIM_CCMR1_CC2S            TIM_CCMR1_CC2S_Msk                           /*!<CC2S[1:0] bits (Capture/Compare 2 Selection) */
#define TIM_CCMR1_CC2S_0          (0x1U << TIM_CCMR1_CC2S_Pos)                 /*!< 0x00000100 */
#define TIM_CCMR1_CC2S_1          (0x2U << TIM_CCMR1_CC2S_Pos)                 /*!< 0x00000200 */

#define TIM_CCMR1_OC2FE_Pos       (10U)
#define TIM_CCMR1_OC2FE_Msk       (0x1U << TIM_CCMR1_OC2FE_Pos)                /*!< 0x00000400 */
#define TIM_CCMR1_OC2FE           TIM_CCMR1_OC2FE_Msk                          /*!<Output Compare 2 Fast enable */
#define TIM_CCMR1_OC2PE_Pos       (11U)
#define TIM_CCMR1_OC2PE_Msk       (0x1U << TIM_CCMR1_OC2PE_Pos)                /*!< 0x00000800 */
#define TIM_CCMR1_OC2PE           TIM_CCMR1_OC2PE_Msk                          /*!<Output Compare 2 Preload enable */

#define TIM_CCMR1_OC2M_Pos        (12U)
#define TIM_CCMR1_OC2M_Msk        (0x1007U << TIM_CCMR1_OC2M_Pos)              /*!< 0x01007000 */
#define TIM_CCMR1_OC2M            TIM_CCMR1_OC2M_Msk                           /*!<OC2M[2:0] bits (Output Compare 2 Mode) */
#define TIM_CCMR1_OC2M_0          (0x0001U << TIM_CCMR1_OC2M_Pos)              /*!< 0x00001000 */
#define TIM_CCMR1_OC2M_1          (0x0002U << TIM_CCMR1_OC2M_Pos)              /*!< 0x00002000 */
#define TIM_CCMR1_OC2M_2          (0x0004U << TIM_CCMR1_OC2M_Pos)              /*!< 0x00004000 */
#define TIM_CCMR1_OC2M_3          (0x1000U << TIM_CCMR1_OC2M_Pos)              /*!< 0x01000000 */

#define TIM_CCMR1_OC2CE_Pos       (15U)
#define TIM_CCMR1_OC2CE_Msk       (0x1U << TIM_CCMR1_OC2CE_Pos)                /*!< 0x00008000 */
#define TIM_CCMR1_OC2CE           TIM_CCMR1_OC2CE_Msk                          /*!<Output Compare 2 Clear Enable */

/*----------------------------------------------------------------------------*/

#define TIM_CCMR1_IC1PSC_Pos      (2U)
#define TIM_CCMR1_IC1PSC_Msk      (0x3U << TIM_CCMR1_IC1PSC_Pos)               /*!< 0x0000000C */
#define TIM_CCMR1_IC1PSC          TIM_CCMR1_IC1PSC_Msk                         /*!<IC1PSC[1:0] bits (Input Capture 1 Prescaler) */
#define TIM_CCMR1_IC1PSC_0        (0x1U << TIM_CCMR1_IC1PSC_Pos)               /*!< 0x00000004 */
#define TIM_CCMR1_IC1PSC_1        (0x2U << TIM_CCMR1_IC1PSC_Pos)               /*!< 0x00000008 */

#define TIM_CCMR1_IC1F_Pos        (4U)
#define TIM_CCMR1_IC1F_Msk        (0xFU << TIM_CCMR1_IC1F_Pos)                 /*!< 0x000000F0 */
#define TIM_CCMR1_IC1F            TIM_CCMR1_IC1F_Msk                           /*!<IC1F[3:0] bits (Input Capture 1 Filter) */
#define TIM_CCMR1_IC1F_0          (0x1U << TIM_CCMR1_IC1F_Pos)                 /*!< 0x00000010 */
#define TIM_CCMR1_IC1F_1          (0x2U << TIM_CCMR1_IC1F_Pos)                 /*!< 0x00000020 */
#define TIM_CCMR1_IC1F_2          (0x4U << TIM_CCMR1_IC1F_Pos)                 /*!< 0x00000040 */
#define TIM_CCMR1_IC1F_3          (0x8U << TIM_CCMR1_IC1F_Pos)                 /*!< 0x00000080 */

#define TIM_CCMR1_IC2PSC_Pos      (10U)
#define TIM_CCMR1_IC2PSC_Msk      (0x3U << TIM_CCMR1_IC2PSC_Pos)               /*!< 0x00000C00 */
#define TIM_CCMR1_IC2PSC          TIM_CCMR1_IC2PSC_Msk                         /*!<IC2PSC[1:0] bits (Input Capture 2 Prescaler) */
#define TIM_CCMR1_IC2PSC_0        (0x1U << TIM_CCMR1_IC2PSC_Pos)               /*!< 0x00000400 */
#define TIM_CCMR1_IC2PSC_1        (0x2U << TIM_CCMR1_IC2PSC_Pos)               /*!< 0x00000800 */

#define TIM_CCMR1_IC2F_Pos        (12U)
#define TIM_CCMR1_IC2F_Msk        (0xFU << TIM_CCMR1_IC2F_Pos)                 /*!< 0x0000F000 */
#define TIM_CCMR1_IC2F            TIM_CCMR1_IC2F_Msk                           /*!<IC2F[3:0] bits (Input Capture 2 Filter) */
#define TIM_CCMR1_IC2F_0          (0x1U << TIM_CCMR1_IC2F_Pos)                 /*!< 0x00001000 */
#define TIM_CCMR1_IC2F_1          (0x2U << TIM_CCMR1_IC2F_Pos)                 /*!< 0x00002000 */
#define TIM_CCMR1_IC2F_2          (0x4U << TIM_CCMR1_IC2F_Pos)                 /*!< 0x00004000 */
#define TIM_CCMR1_IC2F_3          (0x8U << TIM_CCMR1_IC2F_Pos)                 /*!< 0x00008000 */

/******************  Bit definition for TIM_CCMR2 register  *******************/
#define TIM_CCMR2_CC3S_Pos        (0U)
#define TIM_CCMR2_CC3S_Msk        (0x3U << TIM_CCMR2_CC3S_Pos)                 /*!< 0x00000003 */
#define TIM_CCMR2_CC3S            TIM_CCMR2_CC3S_Msk                           /*!<CC3S[1:0] bits (Capture/Compare 3 Selection) */
#define TIM_CCMR2_CC3S_0          (0x1U << TIM_CCMR2_CC3S_Pos)                 /*!< 0x00000001 */
#define TIM_CCMR2_CC3S_1          (0x2U << TIM_CCMR2_CC3S_Pos)                 /*!< 0x00000002 */

#define TIM_CCMR2_OC3FE_Pos       (2U)
#define TIM_CCMR2_OC3FE_Msk       (0x1U << TIM_CCMR2_OC3FE_Pos)                /*!< 0x00000004 */
#define TIM_CCMR2_OC3FE           TIM_CCMR2_OC3FE_Msk                          /*!<Output Compare 3 Fast enable */
#define TIM_CCMR2_OC3PE_Pos       (3U)
#define TIM_CCMR2_OC3PE_Msk       (0x1U << TIM_CCMR2_OC3PE_Pos)                /*!< 0x00000008 */
#define TIM_CCMR2_OC3PE           TIM_CCMR2_OC3PE_Msk                          /*!<Output Compare 3 Preload enable */

#define TIM_CCMR2_OC3M_Pos        (4U)
#define TIM_CCMR2_OC3M_Msk        (0x1007U << TIM_CCMR2_OC3M_Pos)              /*!< 0x00010070 */
#define TIM_CCMR2_OC3M            TIM_CCMR2_OC3M_Msk                           /*!<OC3M[2:0] bits (Output Compare 3 Mode) */
#define TIM_CCMR2_OC3M_0          (0x0001U << TIM_CCMR2_OC3M_Pos)              /*!< 0x00000010 */
#define TIM_CCMR2_OC3M_1          (0x0002U << TIM_CCMR2_OC3M_Pos)              /*!< 0x00000020 */
#define TIM_CCMR2_OC3M_2          (0x0004U << TIM_CCMR2_OC3M_Pos)              /*!< 0x00000040 */
#define TIM_CCMR2_OC3M_3          (0x1000U << TIM_CCMR2_OC3M_Pos)              /*!< 0x00010000 */

#define TIM_CCMR2_OC3CE_Pos       (7U)
#define TIM_CCMR2_OC3CE_Msk       (0x1U << TIM_CCMR2_OC3CE_Pos)                /*!< 0x00000080 */
#define TIM_CCMR2_OC3CE           TIM_CCMR2_OC3CE_Msk                          /*!<Output Compare 3 Clear Enable */

#define TIM_CCMR2_CC4S_Pos        (8U)
#define TIM_CCMR2_CC4S_Msk        (0x3U << TIM_CCMR2_CC4S_Pos)                 /*!< 0x00000300 */
#define TIM_CCMR2_CC4S            TIM_CCMR2_CC4S_Msk                           /*!<CC4S[1:0] bits (Capture/Compare 4 Selection) */
#define TIM_CCMR2_CC4S_0          (0x1U << TIM_CCMR2_CC4S_Pos)                 /*!< 0x00000100 */
#define TIM_CCMR2_CC4S_1          (0x2U << TIM_CCMR2_CC4S_Pos)                 /*!< 0x00000200 */

#define TIM_CCMR2_OC4FE_Pos       (10U)
#define TIM_CCMR2_OC4FE_Msk       (0x1U << TIM_CCMR2_OC4FE_Pos)                /*!< 0x00000400 */
#define TIM_CCMR2_OC4FE           TIM_CCMR2_OC4FE_Msk                          /*!<Output Compare 4 Fast enable */
#define TIM_CCMR2_OC4PE_Pos       (11U)
#define TIM_CCMR2_OC4PE_Msk       (0x1U << TIM_CCMR2_OC4PE_Pos)                /*!< 0x00000800 */
#define TIM_CCMR2_OC4PE           TIM_CCMR2_OC4PE_Msk                          /*!<Output Compare 4 Preload enable */

#define TIM_CCMR2_OC4M_Pos        (12U)
#define TIM_CCMR2_OC4M_Msk        (0x1007U << TIM_CCMR2_OC4M_Pos)              /*!< 0x01007000 */
#define TIM_CCMR2_OC4M            TIM_CCMR2_OC4M_Msk                           /*!<OC4M[2:0] bits (Output Compare 4 Mode) */
#define TIM_CCMR2_OC4M_0          (0x0001U << TIM_CCMR2_OC4M_Pos)              /*!< 0x00001000 */
#define TIM_CCMR2_OC4M_1          (0x0002U << TIM_CCMR2_OC4M_Pos)              /*!< 0x00002000 */
#define TIM_CCMR2_OC4M_2          (0x0004U << TIM_CCMR2_OC4M_Pos)              /*!< 0x00004000 */
#define TIM_CCMR2_OC4M_3          (0x1000U << TIM_CCMR2_OC4M_Pos)              /*!< 0x01000000 */

#define TIM_CCMR2_OC4CE_Pos       (15U)
#define TIM_CCMR2_OC4CE_Msk       (0x1U << TIM_CCMR2_OC4CE_Pos)                /*!< 0x00008000 */
#define TIM_CCMR2_OC4CE           TIM_CCMR2_OC4CE_Msk                          /*!<Output Compare 4 Clear Enable */

/*----------------------------------------------------------------------------*/

#define TIM_CCMR2_IC3PSC          ((uint16_t)0x0000000C)                       /*!<IC3PSC[1:0] bits (Input Capture 3 Prescaler) */
#define TIM_CCMR2_IC3PSC_0        ((uint16_t)0x00000004)                       /*!<Bit 0 */
#define TIM_CCMR2_IC3PSC_1        ((uint16_t)0x00000008)                       /*!<Bit 1 */

#define TIM_CCMR2_IC3F            ((uint16_t)0x000000F0)                       /*!<IC3F[3:0] bits (Input Capture 3 Filter) */
#define TIM_CCMR2_IC3F_0          ((uint16_t)0x00000010)                       /*!<Bit 0 */
#define TIM_CCMR2_IC3F_1          ((uint16_t)0x00000020)                       /*!<Bit 1 */
#define TIM_CCMR2_IC3F_2          ((uint16_t)0x00000040)                       /*!<Bit 2 */
#define TIM_CCMR2_IC3F_3          ((uint16_t)0x00000080)                       /*!<Bit 3 */

#define TIM_CCMR2_IC4PSC          ((uint16_t)0x00000C00)                       /*!<IC4PSC[1:0] bits (Input Capture 4 Prescaler) */
#define TIM_CCMR2_IC4PSC_0        ((uint16_t)0x00000400)                       /*!<Bit 0 */
#define TIM_CCMR2_IC4PSC_1        ((uint16_t)0x00000800)                       /*!<Bit 1 */

#define TIM_CCMR2_IC4F            ((uint16_t)0x0000F000)                       /*!<IC4F[3:0] bits (Input Capture 4 Filter) */
#define TIM_CCMR2_IC4F_0          ((uint16_t)0x00001000)                       /*!<Bit 0 */
#define TIM_CCMR2_IC4F_1          ((uint16_t)0x00002000)                       /*!<Bit 1 */
#define TIM_CCMR2_IC4F_2          ((uint16_t)0x00004000)                       /*!<Bit 2 */
#define TIM_CCMR2_IC4F_3          ((uint16_t)0x00008000)                       /*!<Bit 3 */

/*******************  Bit definition for TIM_CCER register  *******************/
#define TIM_CCER_CC1E_Pos         (0U)
#define TIM_CCER_CC1E_Msk         (0x1U << TIM_CCER_CC1E_Pos)                  /*!< 0x00000001 */
#define TIM_CCER_CC1E             TIM_CCER_CC1E_Msk                            /*!<Capture/Compare 1 output enable */
#define TIM_CCER_CC1P_Pos         (1U)
#define TIM_CCER_CC1P_Msk         (0x1U << TIM_CCER_CC1P_Pos)                  /*!< 0x00000002 */
#define TIM_CCER_CC1P             TIM_CCER_CC1P_Msk                            /*!<Capture/Compare 1 output Polarity */
#define TIM_CCER_CC1NE_Pos        (2U)
#define TIM_CCER_CC1NE_Msk        (0x1U << TIM_CCER_CC1NE_Pos)                 /*!< 0x00000004 */
#define TIM_CCER_CC1NE            TIM_CCER_CC1NE_Msk                           /*!<Capture/Compare 1 Complementary output enable */
#define TIM_CCER_CC1NP_Pos        (3U)
#define TIM_CCER_CC1NP_Msk        (0x1U << TIM_CCER_CC1NP_Pos)                 /*!< 0x00000008 */
#define TIM_CCER_CC1NP            TIM_CCER_CC1NP_Msk                           /*!<Capture/Compare 1 Complementary output Polarity */
#define TIM_CCER_CC2E_Pos         (4U)
#define TIM_CCER_CC2E_Msk         (0x1U << TIM_CCER_CC2E_Pos)                  /*!< 0x00000010 */
#define TIM_CCER_CC2E             TIM_CCER_CC2E_Msk                            /*!<Capture/Compare 2 output enable */
#define TIM_CCER_CC2P_Pos         (5U)
#define TIM_CCER_CC2P_Msk         (0x1U << TIM_CCER_CC2P_Pos)                  /*!< 0x00000020 */
#define TIM_CCER_CC2P             TIM_CCER_CC2P_Msk                            /*!<Capture/Compare 2 output Polarity */
#define TIM_CCER_CC2NE_Pos        (6U)
#define TIM_CCER_CC2NE_Msk        (0x1U << TIM_CCER_CC2NE_Pos)                 /*!< 0x00000040 */
#define TIM_CCER_CC2NE            TIM_CCER_CC2NE_Msk                           /*!<Capture/Compare 2 Complementary output enable */
#define TIM_CCER_CC2NP_Pos        (7U)
#define TIM_CCER_CC2NP_Msk        (0x1U << TIM_CCER_CC2NP_Pos)                 /*!< 0x00000080 */
#define TIM_CCER_CC2NP            TIM_CCER_CC2NP_Msk                           /*!<Capture/Compare 2 Complementary output Polarity */
#define TIM_CCER_CC3E_Pos         (8U)
#define TIM_CCER_CC3E_Msk         (0x1U << TIM_CCER_CC3E_Pos)                  /*!< 0x00000100 */
#define TIM_CCER_CC3E             TIM_CCER_CC3E_Msk                            /*!<Capture/Compare 3 output enable */
#define TIM_CCER_CC3P_Pos         (9U)
#define TIM_CCER_CC3P_Msk         (0x1U << TIM_CCER_CC3P_Pos)                  /*!< 0x00000200 */
#define TIM_CCER_CC3P             TIM_CCER_CC3P_Msk                            /*!<Capture/Compare 3 output Polarity */
#define TIM_CCER_CC3NE_Pos        (10U)
#define TIM_CCER_CC3NE_Msk        (0x1U << TIM_CCER_CC3NE_Pos)                 /*!< 0x00000400 */
#define TIM_CCER_CC3NE            TIM_CCER_CC3NE_Msk                           /*!<Capture/Compare 3 Complementary output enable */
#define TIM_CCER_CC3NP_Pos        (11U)
#define TIM_CCER_CC3NP_Msk        (0x1U << TIM_CCER_CC3NP_Pos)                 /*!< 0x00000800 */
#define TIM_CCER_CC3NP            TIM_CCER_CC3NP_Msk                           /*!<Capture/Compare 3 Complementary output Polarity */
#define TIM_CCER_CC4E_Pos         (12U)
#define TIM_CCER_CC4E_Msk         (0x1U << TIM_CCER_CC4E_Pos)                  /*!< 0x00001000 */
#define TIM_CCER_CC4E             TIM_CCER_CC4E_Msk                            /*!<Capture/Compare 4 output enable */
#define TIM_CCER_CC4P_Pos         (13U)
#define TIM_CCER_CC4P_Msk         (0x1U << TIM_CCER_CC4P_Pos)                  /*!< 0x00002000 */
#define TIM_CCER_CC4P             TIM_CCER_CC4P_Msk                            /*!<Capture/Compare 4 output Polarity */
#define TIM_CCER_CC4NP_Pos        (15U)
#define TIM_CCER_CC4NP_Msk        (0x1U << TIM_CCER_CC4NP_Pos)                 /*!< 0x00008000 */
#define TIM_CCER_CC4NP            TIM_CCER_CC4NP_Msk                           /*!<Capture/Compare 4 Complementary output Polarity */
#define TIM_CCER_CC5E_Pos         (16U)
#define TIM_CCER_CC5E_Msk         (0x1U << TIM_CCER_CC5E_Pos)                  /*!< 0x00010000 */
#define TIM_CCER_CC5E             TIM_CCER_CC5E_Msk                            /*!<Capture/Compare 5 output enable */
#define TIM_CCER_CC5P_Pos         (17U)
#define TIM_CCER_CC5P_Msk         (0x1U << TIM_CCER_CC5P_Pos)                  /*!< 0x00020000 */
#define TIM_CCER_CC5P             TIM_CCER_CC5P_Msk                            /*!<Capture/Compare 5 output Polarity */
#define TIM_CCER_CC6E_Pos         (20U)
#define TIM_CCER_CC6E_Msk         (0x1U << TIM_CCER_CC6E_Pos)                  /*!< 0x00100000 */
#define TIM_CCER_CC6E             TIM_CCER_CC6E_Msk                            /*!<Capture/Compare 6 output enable */
#define TIM_CCER_CC6P_Pos         (21U)
#define TIM_CCER_CC6P_Msk         (0x1U << TIM_CCER_CC6P_Pos)                  /*!< 0x00200000 */
#define TIM_CCER_CC6P             TIM_CCER_CC6P_Msk                            /*!<Capture/Compare 6 output Polarity */
/*******************  Bit definition for TIM_CNT register  ********************/
#define TIM_CNT_CNT_Pos           (0U)
#define TIM_CNT_CNT_Msk           (0xFFFFFFFFU << TIM_CNT_CNT_Pos)             /*!< 0xFFFFFFFF */
#define TIM_CNT_CNT               TIM_CNT_CNT_Msk                              /*!<Counter Value */
#define TIM_CNT_UIFCPY_Pos        (31U)
#define TIM_CNT_UIFCPY_Msk        (0x1U << TIM_CNT_UIFCPY_Pos)                 /*!< 0x80000000 */
#define TIM_CNT_UIFCPY            TIM_CNT_UIFCPY_Msk                           /*!<Update interrupt flag copy */
/*******************  Bit definition for TIM_PSC register  ********************/
#define TIM_PSC_PSC               ((uint16_t)0xFFFF)                           /*!<Prescaler Value */

/*******************  Bit definition for TIM_ARR register  ********************/
#define TIM_ARR_ARR_Pos           (0U)
#define TIM_ARR_ARR_Msk           (0xFFFFFFFFU << TIM_ARR_ARR_Pos)             /*!< 0xFFFFFFFF */
#define TIM_ARR_ARR               TIM_ARR_ARR_Msk                              /*!<actual auto-reload Value */

/*******************  Bit definition for TIM_RCR register  ********************/
#define TIM_RCR_REP               ((uint8_t)0xFF)                              /*!<Repetition Counter Value */

/*******************  Bit definition for TIM_CCR1 register  *******************/
#define TIM_CCR1_CCR1             ((uint16_t)0xFFFF)                           /*!<Capture/Compare 1 Value */

/*******************  Bit definition for TIM_CCR2 register  *******************/
#define TIM_CCR2_CCR2             ((uint16_t)0xFFFF)                           /*!<Capture/Compare 2 Value */

/*******************  Bit definition for TIM_CCR3 register  *******************/
#define TIM_CCR3_CCR3             ((uint16_t)0xFFFF)                           /*!<Capture/Compare 3 Value */

/*******************  Bit definition for TIM_CCR4 register  *******************/
#define TIM_CCR4_CCR4             ((uint16_t)0xFFFF)                           /*!<Capture/Compare 4 Value */

/*******************  Bit definition for TIM_CCR5 register  *******************/
#define TIM_CCR5_CCR5_Pos         (0U)
#define TIM_CCR5_CCR5_Msk         (0xFFFFFFFFU << TIM_CCR5_CCR5_Pos)           /*!< 0xFFFFFFFF */
#define TIM_CCR5_CCR5             TIM_CCR5_CCR5_Msk                            /*!<Capture/Compare 5 Value */
#define TIM_CCR5_GC5C1_Pos        (29U)
#define TIM_CCR5_GC5C1_Msk        (0x1U << TIM_CCR5_GC5C1_Pos)                 /*!< 0x20000000 */
#define TIM_CCR5_GC5C1            TIM_CCR5_GC5C1_Msk                           /*!<Group Channel 5 and Channel 1 */
#define TIM_CCR5_GC5C2_Pos        (30U)
#define TIM_CCR5_GC5C2_Msk        (0x1U << TIM_CCR5_GC5C2_Pos)                 /*!< 0x40000000 */
#define TIM_CCR5_GC5C2            TIM_CCR5_GC5C2_Msk                           /*!<Group Channel 5 and Channel 2 */
#define TIM_CCR5_GC5C3_Pos        (31U)
#define TIM_CCR5_GC5C3_Msk        (0x1U << TIM_CCR5_GC5C3_Pos)                 /*!< 0x80000000 */
#define TIM_CCR5_GC5C3            TIM_CCR5_GC5C3_Msk                           /*!<Group Channel 5 and Channel 3 */

/*******************  Bit definition for TIM_CCR6 register  *******************/
#define TIM_CCR6_CCR6             ((uint16_t)0xFFFF)                           /*!<Capture/Compare 6 Value */

/*******************  Bit definition for TIM_BDTR register  *******************/
#define TIM_BDTR_DTG_Pos          (0U)
#define TIM_BDTR_DTG_Msk          (0xFFU << TIM_BDTR_DTG_Pos)                  /*!< 0x000000FF */
#define TIM_BDTR_DTG              TIM_BDTR_DTG_Msk                             /*!<DTG[0:7] bits (Dead-Time Generator set-up) */
#define TIM_BDTR_DTG_0            (0x01U << TIM_BDTR_DTG_Pos)                  /*!< 0x00000001 */
#define TIM_BDTR_DTG_1            (0x02U << TIM_BDTR_DTG_Pos)                  /*!< 0x00000002 */
#define TIM_BDTR_DTG_2            (0x04U << TIM_BDTR_DTG_Pos)                  /*!< 0x00000004 */
#define TIM_BDTR_DTG_3            (0x08U << TIM_BDTR_DTG_Pos)                  /*!< 0x00000008 */
#define TIM_BDTR_DTG_4            (0x10U << TIM_BDTR_DTG_Pos)                  /*!< 0x00000010 */
#define TIM_BDTR_DTG_5            (0x20U << TIM_BDTR_DTG_Pos)                  /*!< 0x00000020 */
#define TIM_BDTR_DTG_6            (0x40U << TIM_BDTR_DTG_Pos)                  /*!< 0x00000040 */
#define TIM_BDTR_DTG_7            (0x80U << TIM_BDTR_DTG_Pos)                  /*!< 0x00000080 */

#define TIM_BDTR_LOCK_Pos         (8U)
#define TIM_BDTR_LOCK_Msk         (0x3U << TIM_BDTR_LOCK_Pos)                  /*!< 0x00000300 */
#define TIM_BDTR_LOCK             TIM_BDTR_LOCK_Msk                            /*!<LOCK[1:0] bits (Lock Configuration) */
#define TIM_BDTR_LOCK_0           (0x1U << TIM_BDTR_LOCK_Pos)                  /*!< 0x00000100 */
#define TIM_BDTR_LOCK_1           (0x2U << TIM_BDTR_LOCK_Pos)                  /*!< 0x00000200 */

#define TIM_BDTR_OSSI_Pos         (10U)
#define TIM_BDTR_OSSI_Msk         (0x1U << TIM_BDTR_OSSI_Pos)                  /*!< 0x00000400 */
#define TIM_BDTR_OSSI             TIM_BDTR_OSSI_Msk                            /*!<Off-State Selection for Idle mode */
#define TIM_BDTR_OSSR_Pos         (11U)
#define TIM_BDTR_OSSR_Msk         (0x1U << TIM_BDTR_OSSR_Pos)                  /*!< 0x00000800 */
#define TIM_BDTR_OSSR             TIM_BDTR_OSSR_Msk                            /*!<Off-State Selection for Run mode */
#define TIM_BDTR_BKE_Pos          (12U)
#define TIM_BDTR_BKE_Msk          (0x1U << TIM_BDTR_BKE_Pos)                   /*!< 0x00001000 */
#define TIM_BDTR_BKE              TIM_BDTR_BKE_Msk                             /*!<Break enable for Break1 */
#define TIM_BDTR_BKP_Pos          (13U)
#define TIM_BDTR_BKP_Msk          (0x1U << TIM_BDTR_BKP_Pos)                   /*!< 0x00002000 */
#define TIM_BDTR_BKP              TIM_BDTR_BKP_Msk                             /*!<Break Polarity for Break1 */
#define TIM_BDTR_AOE_Pos          (14U)
#define TIM_BDTR_AOE_Msk          (0x1U << TIM_BDTR_AOE_Pos)                   /*!< 0x00004000 */
#define TIM_BDTR_AOE              TIM_BDTR_AOE_Msk                             /*!<Automatic Output enable */
#define TIM_BDTR_MOE_Pos          (15U)
#define TIM_BDTR_MOE_Msk          (0x1U << TIM_BDTR_MOE_Pos)                   /*!< 0x00008000 */
#define TIM_BDTR_MOE              TIM_BDTR_MOE_Msk                             /*!<Main Output enable */

#define TIM_BDTR_BKF_Pos          (16U)
#define TIM_BDTR_BKF_Msk          (0xFU << TIM_BDTR_BKF_Pos)                   /*!< 0x000F0000 */
#define TIM_BDTR_BKF              TIM_BDTR_BKF_Msk                             /*!<Break Filter for Break1 */
#define TIM_BDTR_BK2F_Pos         (20U)
#define TIM_BDTR_BK2F_Msk         (0xFU << TIM_BDTR_BK2F_Pos)                  /*!< 0x00F00000 */
#define TIM_BDTR_BK2F             TIM_BDTR_BK2F_Msk                            /*!<Break Filter for Break2 */

#define TIM_BDTR_BK2E_Pos         (24U)
#define TIM_BDTR_BK2E_Msk         (0x1U << TIM_BDTR_BK2E_Pos)                  /*!< 0x01000000 */
#define TIM_BDTR_BK2E             TIM_BDTR_BK2E_Msk                            /*!<Break enable for Break2 */
#define TIM_BDTR_BK2P_Pos         (25U)
#define TIM_BDTR_BK2P_Msk         (0x1U << TIM_BDTR_BK2P_Pos)                  /*!< 0x02000000 */
#define TIM_BDTR_BK2P             TIM_BDTR_BK2P_Msk                            /*!<Break Polarity for Break2 */

#define TIM_BDTR_BKDSRM_Pos       (26U)
#define TIM_BDTR_BKDSRM_Msk       (0x1U << TIM_BDTR_BKDSRM_Pos)                /*!< 0x04000000 */
#define TIM_BDTR_BKDSRM           TIM_BDTR_BKDSRM_Msk                          /*!<Break Disarmed for Break1 */
#define TIM_BDTR_BK2DSRM_Pos      (27U)
#define TIM_BDTR_BK2DSRM_Msk      (0x1U << TIM_BDTR_BK2DSRM_Pos)               /*!< 0x08000000 */
#define TIM_BDTR_BK2DSRM          TIM_BDTR_BK2DSRM_Msk                         /*!<Break Disarmed for Break2 */

#define TIM_BDTR_BKBID_Pos        (28U)
#define TIM_BDTR_BKBID_Msk        (0x1U << TIM_BDTR_BKBID_Pos)                 /*!< 0x10000000 */
#define TIM_BDTR_BKBID            TIM_BDTR_BKBID_Msk                           /*!<Break Bidirectionnal for Break1 */
#define TIM_BDTR_BK2BID_Pos       (29U)
#define TIM_BDTR_BK2BID_Msk       (0x1U << TIM_BDTR_BK2BID_Pos)                /*!< 0x20000000 */
#define TIM_BDTR_BK2BID           TIM_BDTR_BK2BID_Msk                          /*!<Break Bidirectionnal for Break2 */

/*******************  Bit definition for TIM_DCR register  ********************/
#define TIM_DCR_DBA               ((uint16_t)0x001F)                           /*!<DBA[4:0] bits (DMA Base Address) */
#define TIM_DCR_DBA_0             ((uint16_t)0x0001)                           /*!<Bit 0 */
#define TIM_DCR_DBA_1             ((uint16_t)0x0002)                           /*!<Bit 1 */
#define TIM_DCR_DBA_2             ((uint16_t)0x0004)                           /*!<Bit 2 */
#define TIM_DCR_DBA_3             ((uint16_t)0x0008)                           /*!<Bit 3 */
#define TIM_DCR_DBA_4             ((uint16_t)0x0010)                           /*!<Bit 4 */

#define TIM_DCR_DBL               ((uint16_t)0x1F00)                           /*!<DBL[4:0] bits (DMA Burst Length) */
#define TIM_DCR_DBL_0             ((uint16_t)0x0100)                           /*!<Bit 0 */
#define TIM_DCR_DBL_1             ((uint16_t)0x0200)                           /*!<Bit 1 */
#define TIM_DCR_DBL_2             ((uint16_t)0x0400)                           /*!<Bit 2 */
#define TIM_DCR_DBL_3             ((uint16_t)0x0800)                           /*!<Bit 3 */
#define TIM_DCR_DBL_4             ((uint16_t)0x1000)                           /*!<Bit 4 */

/*******************  Bit definition for TIM_DMAR register  *******************/
#define TIM_DMAR_DMAB             ((uint16_t)0xFFFF)                           /*!<DMA register for burst accesses */

/*******************  Bit definition for TIM16_OR register  *********************/
#define TIM16_OR_TI1_RMP            ((uint16_t)0x00C0)                         /*!<TI1_RMP[1:0] bits (TIM16 Input 1 remap) */
#define TIM16_OR_TI1_RMP_0          ((uint16_t)0x0040)                         /*!<Bit 0 */
#define TIM16_OR_TI1_RMP_1          ((uint16_t)0x0080)                         /*!<Bit 1 */

/*******************  Bit definition for TIM1_OR register  *********************/
#define TIM1_OR_ETR_RMP            ((uint16_t)0x000F)                          /*!<ETR_RMP[3:0] bits (TIM1 ETR remap) */
#define TIM1_OR_ETR_RMP_0          ((uint16_t)0x0001)                          /*!<Bit 0 */
#define TIM1_OR_ETR_RMP_1          ((uint16_t)0x0002)                          /*!<Bit 1 */
#define TIM1_OR_ETR_RMP_2          ((uint16_t)0x0004)                          /*!<Bit 2 */
#define TIM1_OR_ETR_RMP_3          ((uint16_t)0x0008)                          /*!<Bit 3 */

/*******************  Bit definition for TIM8_OR register  *********************/
#define TIM8_OR_ETR_RMP            ((uint16_t)0x000F)                          /*!<ETR_RMP[3:0] bits (TIM8 ETR remap) */
#define TIM8_OR_ETR_RMP_0          ((uint16_t)0x0001)                          /*!<Bit 0 */
#define TIM8_OR_ETR_RMP_1          ((uint16_t)0x0002)                          /*!<Bit 1 */
#define TIM8_OR_ETR_RMP_2          ((uint16_t)0x0004)                          /*!<Bit 2 */
#define TIM8_OR_ETR_RMP_3          ((uint16_t)0x0008)                          /*!<Bit 3 */

/******************  Bit definition for TIM_CCMR3 register  *******************/
#define TIM_CCMR3_OC5FE_Pos       (2U)
#define TIM_CCMR3_OC5FE_Msk       (0x1U << TIM_CCMR3_OC5FE_Pos)                /*!< 0x00000004 */
#define TIM_CCMR3_OC5FE           TIM_CCMR3_OC5FE_Msk                          /*!<Output Compare 5 Fast enable */
#define TIM_CCMR3_OC5PE_Pos       (3U)
#define TIM_CCMR3_OC5PE_Msk       (0x1U << TIM_CCMR3_OC5PE_Pos)                /*!< 0x00000008 */
#define TIM_CCMR3_OC5PE           TIM_CCMR3_OC5PE_Msk                          /*!<Output Compare 5 Preload enable */

#define TIM_CCMR3_OC5M_Pos        (4U)
#define TIM_CCMR3_OC5M_Msk        (0x1007U << TIM_CCMR3_OC5M_Pos)              /*!< 0x00010070 */
#define TIM_CCMR3_OC5M            TIM_CCMR3_OC5M_Msk                           /*!<OC5M[2:0] bits (Output Compare 5 Mode) */
#define TIM_CCMR3_OC5M_0          (0x0001U << TIM_CCMR3_OC5M_Pos)              /*!< 0x00000010 */
#define TIM_CCMR3_OC5M_1          (0x0002U << TIM_CCMR3_OC5M_Pos)              /*!< 0x00000020 */
#define TIM_CCMR3_OC5M_2          (0x0004U << TIM_CCMR3_OC5M_Pos)              /*!< 0x00000040 */
#define TIM_CCMR3_OC5M_3          (0x1000U << TIM_CCMR3_OC5M_Pos)              /*!< 0x00010000 */

#define TIM_CCMR3_OC5CE_Pos       (7U)
#define TIM_CCMR3_OC5CE_Msk       (0x1U << TIM_CCMR3_OC5CE_Pos)                /*!< 0x00000080 */
#define TIM_CCMR3_OC5CE           TIM_CCMR3_OC5CE_Msk                          /*!<Output Compare 5 Clear Enable */

#define TIM_CCMR3_OC6FE_Pos       (10U)
#define TIM_CCMR3_OC6FE_Msk       (0x1U << TIM_CCMR3_OC6FE_Pos)                /*!< 0x00000400 */
#define TIM_CCMR3_OC6FE           TIM_CCMR3_OC6FE_Msk                          /*!<Output Compare 4 Fast enable */
#define TIM_CCMR3_OC6PE_Pos       (11U)
#define TIM_CCMR3_OC6PE_Msk       (0x1U << TIM_CCMR3_OC6PE_Pos)                /*!< 0x00000800 */
#define TIM_CCMR3_OC6PE           TIM_CCMR3_OC6PE_Msk                          /*!<Output Compare 4 Preload enable */

#define TIM_CCMR3_OC6M_Pos        (12U)
#define TIM_CCMR3_OC6M_Msk        (0x1007U << TIM_CCMR3_OC6M_Pos)              /*!< 0x01007000 */
#define TIM_CCMR3_OC6M            TIM_CCMR3_OC6M_Msk                           /*!<OC4M[2:0] bits (Output Compare 4 Mode) */
#define TIM_CCMR3_OC6M_0          (0x0001U << TIM_CCMR3_OC6M_Pos)              /*!< 0x00001000 */
#define TIM_CCMR3_OC6M_1          (0x0002U << TIM_CCMR3_OC6M_Pos)              /*!< 0x00002000 */
#define TIM_CCMR3_OC6M_2          (0x0004U << TIM_CCMR3_OC6M_Pos)              /*!< 0x00004000 */
#define TIM_CCMR3_OC6M_3          (0x1000U << TIM_CCMR3_OC6M_Pos)              /*!< 0x01000000 */

#define TIM_CCMR3_OC6CE_Pos       (15U)
#define TIM_CCMR3_OC6CE_Msk       (0x1U << TIM_CCMR3_OC6CE_Pos)                /*!< 0x00008000 */
#define TIM_CCMR3_OC6CE           TIM_CCMR3_OC6CE_Msk                          /*!<Output Compare 4 Clear Enable */
/*******************  Bit definition for TIM1_AF1 register  *********************/
#define TIM1_AF1_BKINE_Pos         (0U)
#define TIM1_AF1_BKINE_Msk         (0x1U << TIM1_AF1_BKINE_Pos)                /*!< 0x00000001 */
#define TIM1_AF1_BKINE             TIM1_AF1_BKINE_Msk                          /*!<BKINE Break input enable bit */
#define TIM1_AF1_BKDF1BK0E_Pos      (8U)
#define TIM1_AF1_BKDF1BK0E_Msk      (0x1U << TIM1_AF1_BKDF1BK0E_Pos)             /*!< 0x00000100 */
#define TIM1_AF1_BKDF1BK0E          TIM1_AF1_BKDF1BK0E_Msk                       /*!<BKDF1BK0E Break input DFSDM Break 0 */
#define TIM1_AF1_BKINP_Pos         (9U)
#define TIM1_AF1_BKINP_Msk         (0x1U << TIM1_AF1_BKINP_Pos)                /*!< 0x00000200 */
#define TIM1_AF1_BKINP             TIM1_AF1_BKINP_Msk                          /*!<BRKINP Break input polarity */

#define TIM1_AF1_ETRSEL_Pos       (14U)
#define TIM1_AF1_ETRSEL_Msk       (0xFU << TIM1_AF1_ETRSEL_Pos)              /*!< 0x0003C000 */
#define TIM1_AF1_ETRSEL           TIM1_AF1_ETRSEL_Msk                        /*!<ETRSEL[3:0] bits (TIM1 ETR SEL) */
#define TIM1_AF1_ETRSEL_0         (0x1U << TIM1_AF1_ETRSEL_Pos)              /*!< 0x00004000 */
#define TIM1_AF1_ETRSEL_1         (0x2U << TIM1_AF1_ETRSEL_Pos)              /*!< 0x00008000 */
#define TIM1_AF1_ETRSEL_2         (0x4U << TIM1_AF1_ETRSEL_Pos)              /*!< 0x00010000 */
#define TIM1_AF1_ETRSEL_3         (0x8U << TIM1_AF1_ETRSEL_Pos)              /*!< 0x00020000 */

/*******************  Bit definition for TIM1_AF2 register  *********************/
#define TIM1_AF2_BK2INE_Pos        (0U)
#define TIM1_AF2_BK2INE_Msk        (0x1U << TIM1_AF2_BK2INE_Pos)               /*!< 0x00000001 */
#define TIM1_AF2_BK2INE            TIM1_AF2_BK2INE_Msk                         /*!<BK2INE Break input 2 enable bit */
#define TIM1_AF2_BK2DF1BK1E_Pos     (8U)
#define TIM1_AF2_BK2DF1BK1E_Msk     (0x1U << TIM1_AF2_BK2DF1BK1E_Pos)            /*!< 0x00000100 */
#define TIM1_AF2_BK2DF1BK1E         TIM1_AF2_BK2DF1BK1E_Msk                      /*!<BK2DF1BK1E Break input2 DFSDM Break 1 */
#define TIM1_AF2_BK2INP_Pos        (9U)
#define TIM1_AF2_BK2INP_Msk        (0x1U << TIM1_AF2_BK2INP_Pos)               /*!< 0x00000200 */
#define TIM1_AF2_BK2INP            TIM1_AF2_BK2INP_Msk                         /*!<BRKINP Break2 input polarity */

/*******************  Bit definition for TIM1_TISEL register  *********************/
#define TIM1_TISEL_TI1SEL_Pos      (0U)
#define TIM1_TISEL_TI1SEL_Msk      (0xFU << TIM1_TISEL_TI1SEL_Pos)             /*!< 0x0000000F */
#define TIM1_TISEL_TI1SEL          TIM1_TISEL_TI1SEL_Msk                       /*!<TI1SEL[3:0] bits (TIM1 TI1 SEL)*/
#define TIM1_TISEL_TI1SEL_0        (0x1U << TIM1_TISEL_TI1SEL_Pos)             /*!< 0x00000001 */
#define TIM1_TISEL_TI1SEL_1        (0x2U << TIM1_TISEL_TI1SEL_Pos)             /*!< 0x00000002 */
#define TIM1_TISEL_TI1SEL_2        (0x4U << TIM1_TISEL_TI1SEL_Pos)             /*!< 0x00000004 */
#define TIM1_TISEL_TI1SEL_3        (0x8U << TIM1_TISEL_TI1SEL_Pos)             /*!< 0x00000008 */

#define TIM1_TISEL_TI2SEL_Pos      (8U)
#define TIM1_TISEL_TI2SEL_Msk      (0xFU << TIM1_TISEL_TI2SEL_Pos)             /*!< 0x00000F00 */
#define TIM1_TISEL_TI2SEL          TIM1_TISEL_TI2SEL_Msk                       /*!<TI2SEL[3:0] bits (TIM1 TI2 SEL)*/
#define TIM1_TISEL_TI2SEL_0        (0x1U << TIM1_TISEL_TI2SEL_Pos)             /*!< 0x00000100 */
#define TIM1_TISEL_TI2SEL_1        (0x2U << TIM1_TISEL_TI2SEL_Pos)             /*!< 0x00000200 */
#define TIM1_TISEL_TI2SEL_2        (0x4U << TIM1_TISEL_TI2SEL_Pos)             /*!< 0x00000400 */
#define TIM1_TISEL_TI2SEL_3        (0x8U << TIM1_TISEL_TI2SEL_Pos)             /*!< 0x00000800 */

#define TIM1_TISEL_TI3SEL_Pos      (16U)
#define TIM1_TISEL_TI3SEL_Msk      (0xFU << TIM1_TISEL_TI3SEL_Pos)             /*!< 0x000F0000 */
#define TIM1_TISEL_TI3SEL          TIM1_TISEL_TI3SEL_Msk                       /*!<TI3SEL[3:0] bits (TIM1 TI3 SEL)*/
#define TIM1_TISEL_TI3SEL_0        (0x1U << TIM1_TISEL_TI3SEL_Pos)             /*!< 0x00010000 */
#define TIM1_TISEL_TI3SEL_1        (0x2U << TIM1_TISEL_TI3SEL_Pos)             /*!< 0x00020000 */
#define TIM1_TISEL_TI3SEL_2        (0x4U << TIM1_TISEL_TI3SEL_Pos)             /*!< 0x00040000 */
#define TIM1_TISEL_TI3SEL_3        (0x8U << TIM1_TISEL_TI3SEL_Pos)             /*!< 0x00080000 */

#define TIM1_TISEL_TI4SEL_Pos      (24U)
#define TIM1_TISEL_TI4SEL_Msk      (0xFU << TIM1_TISEL_TI4SEL_Pos)             /*!< 0x0F000000 */
#define TIM1_TISEL_TI4SEL          TIM1_TISEL_TI4SEL_Msk                       /*!<TI4SEL[3:0] bits (TIM1 TI4 SEL)*/
#define TIM1_TISEL_TI4SEL_0        (0x1U << TIM1_TISEL_TI4SEL_Pos)             /*!< 0x01000000 */
#define TIM1_TISEL_TI4SEL_1        (0x2U << TIM1_TISEL_TI4SEL_Pos)             /*!< 0x02000000 */
#define TIM1_TISEL_TI4SEL_2        (0x4U << TIM1_TISEL_TI4SEL_Pos)             /*!< 0x04000000 */
#define TIM1_TISEL_TI4SEL_3        (0x8U << TIM1_TISEL_TI4SEL_Pos)             /*!< 0x08000000 */

/*******************  Bit definition for TIM8_AF1 register  *********************/
#define TIM8_AF1_BKINE_Pos         (0U)
#define TIM8_AF1_BKINE_Msk         (0x1U << TIM8_AF1_BKINE_Pos)                /*!< 0x00000001 */
#define TIM8_AF1_BKINE             TIM8_AF1_BKINE_Msk                          /*!<BKINE Break input enable bit */
#define TIM8_AF1_BKDFBK2E_Pos      (8U)
#define TIM8_AF1_BKDFBK2E_Msk      (0x1U << TIM8_AF1_BKDFBK2E_Pos)             /*!< 0x00000100 */
#define TIM8_AF1_BKDFBK2E          TIM8_AF1_BKDFBK2E_Msk                       /*!<BKDFBK2E Break input DFSDM Break 2 */
#define TIM8_AF1_BKINP_Pos         (9U)
#define TIM8_AF1_BKINP_Msk         (0x1U << TIM8_AF1_BKINP_Pos)                /*!< 0x00000200 */
#define TIM8_AF1_BKINP             TIM8_AF1_BKINP_Msk                          /*!<BRKINP Break input polarity */

#define TIM8_AF1_ETRSEL_Pos       (14U)
#define TIM8_AF1_ETRSEL_Msk       (0xFU << TIM8_AF1_ETRSEL_Pos)              /*!< 0x0003C000 */
#define TIM8_AF1_ETRSEL           TIM8_AF1_ETRSEL_Msk                        /*!<ETRSEL[3:0] bits (TIM8 ETR SEL) */
#define TIM8_AF1_ETRSEL_0         (0x1U << TIM8_AF1_ETRSEL_Pos)              /*!< 0x00004000 */
#define TIM8_AF1_ETRSEL_1         (0x2U << TIM8_AF1_ETRSEL_Pos)              /*!< 0x00008000 */
#define TIM8_AF1_ETRSEL_2         (0x4U << TIM8_AF1_ETRSEL_Pos)              /*!< 0x00010000 */
#define TIM8_AF1_ETRSEL_3         (0x8U << TIM8_AF1_ETRSEL_Pos)              /*!< 0x00020000 */
/*******************  Bit definition for TIM8_AF2 register  *********************/
#define TIM8_AF2_BK2INE_Pos        (0U)
#define TIM8_AF2_BK2INE_Msk        (0x1U << TIM8_AF2_BK2INE_Pos)               /*!< 0x00000001 */
#define TIM8_AF2_BK2INE            TIM8_AF2_BK2INE_Msk                         /*!<BK2INE Break input 2 enable bit */
#define TIM8_AF2_BK2DFBK3E_Pos     (8U)
#define TIM8_AF2_BK2DFBK3E_Msk     (0x1U << TIM8_AF2_BK2DFBK3E_Pos)            /*!< 0x00000100 */
#define TIM8_AF2_BK2DFBK3E         TIM8_AF2_BK2DFBK3E_Msk                      /*!<BK2DFBK1E Break input2 DFSDM Break 3 */
#define TIM8_AF2_BK2INP_Pos        (9U)
#define TIM8_AF2_BK2INP_Msk        (0x1U << TIM8_AF2_BK2INP_Pos)               /*!< 0x00000200 */
#define TIM8_AF2_BK2INP            TIM8_AF2_BK2INP_Msk                         /*!<BRKINP Break2 input polarity */

/*******************  Bit definition for TIM8_TISEL register  *********************/
#define TIM8_TISEL_TI1SEL_Pos      (0U)
#define TIM8_TISEL_TI1SEL_Msk      (0xFU << TIM8_TISEL_TI1SEL_Pos)             /*!< 0x0000000F */
#define TIM8_TISEL_TI1SEL          TIM8_TISEL_TI1SEL_Msk                       /*!<TI1SEL[3:0] bits (TIM8 TI1 SEL)*/
#define TIM8_TISEL_TI1SEL_0        (0x1U << TIM8_TISEL_TI1SEL_Pos)             /*!< 0x00000001 */
#define TIM8_TISEL_TI1SEL_1        (0x2U << TIM8_TISEL_TI1SEL_Pos)             /*!< 0x00000002 */
#define TIM8_TISEL_TI1SEL_2        (0x4U << TIM8_TISEL_TI1SEL_Pos)             /*!< 0x00000004 */
#define TIM8_TISEL_TI1SEL_3        (0x8U << TIM8_TISEL_TI1SEL_Pos)             /*!< 0x00000008 */

#define TIM8_TISEL_TI2SEL_Pos      (8U)
#define TIM8_TISEL_TI2SEL_Msk      (0xFU << TIM8_TISEL_TI2SEL_Pos)             /*!< 0x00000F00 */
#define TIM8_TISEL_TI2SEL          TIM8_TISEL_TI2SEL_Msk                       /*!<TI2SEL[3:0] bits (TIM8 TI2 SEL)*/
#define TIM8_TISEL_TI2SEL_0        (0x1U << TIM8_TISEL_TI2SEL_Pos)             /*!< 0x00000100 */
#define TIM8_TISEL_TI2SEL_1        (0x2U << TIM8_TISEL_TI2SEL_Pos)             /*!< 0x00000200 */
#define TIM8_TISEL_TI2SEL_2        (0x4U << TIM8_TISEL_TI2SEL_Pos)             /*!< 0x00000400 */
#define TIM8_TISEL_TI2SEL_3        (0x8U << TIM8_TISEL_TI2SEL_Pos)             /*!< 0x00000800 */

#define TIM8_TISEL_TI3SEL_Pos      (16U)
#define TIM8_TISEL_TI3SEL_Msk      (0xFU << TIM8_TISEL_TI3SEL_Pos)             /*!< 0x000F0000 */
#define TIM8_TISEL_TI3SEL          TIM8_TISEL_TI3SEL_Msk                       /*!<TI3SEL[3:0] bits (TIM8 TI3 SEL)*/
#define TIM8_TISEL_TI3SEL_0        (0x1U << TIM8_TISEL_TI3SEL_Pos)             /*!< 0x00010000 */
#define TIM8_TISEL_TI3SEL_1        (0x2U << TIM8_TISEL_TI3SEL_Pos)             /*!< 0x00020000 */
#define TIM8_TISEL_TI3SEL_2        (0x4U << TIM8_TISEL_TI3SEL_Pos)             /*!< 0x00040000 */
#define TIM8_TISEL_TI3SEL_3        (0x8U << TIM8_TISEL_TI3SEL_Pos)             /*!< 0x00080000 */

#define TIM8_TISEL_TI4SEL_Pos      (24U)
#define TIM8_TISEL_TI4SEL_Msk      (0xFU << TIM8_TISEL_TI4SEL_Pos)             /*!< 0x0F000000 */
#define TIM8_TISEL_TI4SEL          TIM8_TISEL_TI4SEL_Msk                       /*!<TI4SEL[3:0] bits (TIM8 TI4 SEL)*/
#define TIM8_TISEL_TI4SEL_0        (0x1U << TIM8_TISEL_TI4SEL_Pos)             /*!< 0x01000000 */
#define TIM8_TISEL_TI4SEL_1        (0x2U << TIM8_TISEL_TI4SEL_Pos)             /*!< 0x02000000 */
#define TIM8_TISEL_TI4SEL_2        (0x4U << TIM8_TISEL_TI4SEL_Pos)             /*!< 0x04000000 */
#define TIM8_TISEL_TI4SEL_3        (0x8U << TIM8_TISEL_TI4SEL_Pos)             /*!< 0x08000000 */

/*******************  Bit definition for TIM2_AF1 register  *********************/
#define TIM2_AF1_ETRSEL_Pos       (14U)
#define TIM2_AF1_ETRSEL_Msk       (0xFU << TIM2_AF1_ETRSEL_Pos)              /*!< 0x0003C000 */
#define TIM2_AF1_ETRSEL           TIM2_AF1_ETRSEL_Msk                        /*!<ETRSEL[3:0] bits (TIM2 ETR SEL) */
#define TIM2_AF1_ETRSEL_0         (0x1U << TIM2_AF1_ETRSEL_Pos)              /*!< 0x00004000 */
#define TIM2_AF1_ETRSEL_1         (0x2U << TIM2_AF1_ETRSEL_Pos)              /*!< 0x00008000 */
#define TIM2_AF1_ETRSEL_2         (0x4U << TIM2_AF1_ETRSEL_Pos)              /*!< 0x00010000 */
#define TIM2_AF1_ETRSEL_3         (0x8U << TIM2_AF1_ETRSEL_Pos)              /*!< 0x00020000 */

/*******************  Bit definition for TIM2_TISEL register  *********************/
#define TIM2_TISEL_TI1SEL_Pos      (0U)
#define TIM2_TISEL_TI1SEL_Msk      (0xFU << TIM2_TISEL_TI1SEL_Pos)             /*!< 0x0000000F */
#define TIM2_TISEL_TI1SEL          TIM2_TISEL_TI1SEL_Msk                       /*!<TI1SEL[3:0] bits (TIM1 TI1 SEL)*/
#define TIM2_TISEL_TI1SEL_0        (0x1U << TIM2_TISEL_TI1SEL_Pos)             /*!< 0x00000001 */
#define TIM2_TISEL_TI1SEL_1        (0x2U << TIM2_TISEL_TI1SEL_Pos)             /*!< 0x00000002 */
#define TIM2_TISEL_TI1SEL_2        (0x4U << TIM2_TISEL_TI1SEL_Pos)             /*!< 0x00000004 */
#define TIM2_TISEL_TI1SEL_3        (0x8U << TIM2_TISEL_TI1SEL_Pos)             /*!< 0x00000008 */

#define TIM2_TISEL_TI2SEL_Pos      (8U)
#define TIM2_TISEL_TI2SEL_Msk      (0xFU << TIM2_TISEL_TI2SEL_Pos)             /*!< 0x00000F00 */
#define TIM2_TISEL_TI2SEL          TIM2_TISEL_TI2SEL_Msk                       /*!<TI2SEL[3:0] bits (TIM2 TI2 SEL)*/
#define TIM2_TISEL_TI2SEL_0        (0x1U << TIM2_TISEL_TI2SEL_Pos)             /*!< 0x00000100 */
#define TIM2_TISEL_TI2SEL_1        (0x2U << TIM2_TISEL_TI2SEL_Pos)             /*!< 0x00000200 */
#define TIM2_TISEL_TI2SEL_2        (0x4U << TIM2_TISEL_TI2SEL_Pos)             /*!< 0x00000400 */
#define TIM2_TISEL_TI2SEL_3        (0x8U << TIM2_TISEL_TI2SEL_Pos)             /*!< 0x00000800 */

#define TIM2_TISEL_TI3SEL_Pos      (16U)
#define TIM2_TISEL_TI3SEL_Msk      (0xFU << TIM2_TISEL_TI3SEL_Pos)             /*!< 0x000F0000 */
#define TIM2_TISEL_TI3SEL          TIM2_TISEL_TI3SEL_Msk                       /*!<TI3SEL[3:0] bits (TIM2 TI3 SEL)*/
#define TIM2_TISEL_TI3SEL_0        (0x1U << TIM2_TISEL_TI3SEL_Pos)             /*!< 0x00010000 */
#define TIM2_TISEL_TI3SEL_1        (0x2U << TIM2_TISEL_TI3SEL_Pos)             /*!< 0x00020000 */
#define TIM2_TISEL_TI3SEL_2        (0x4U << TIM2_TISEL_TI3SEL_Pos)             /*!< 0x00040000 */
#define TIM2_TISEL_TI3SEL_3        (0x8U << TIM2_TISEL_TI3SEL_Pos)             /*!< 0x00080000 */

#define TIM2_TISEL_TI4SEL_Pos      (24U)
#define TIM2_TISEL_TI4SEL_Msk      (0xFU << TIM2_TISEL_TI4SEL_Pos)             /*!< 0x0F000000 */
#define TIM2_TISEL_TI4SEL          TIM2_TISEL_TI4SEL_Msk                       /*!<TI4SEL[3:0] bits (TIM2 TI4 SEL)*/
#define TIM2_TISEL_TI4SEL_0        (0x1U << TIM2_TISEL_TI4SEL_Pos)             /*!< 0x01000000 */
#define TIM2_TISEL_TI4SEL_1        (0x2U << TIM2_TISEL_TI4SEL_Pos)             /*!< 0x02000000 */
#define TIM2_TISEL_TI4SEL_2        (0x4U << TIM2_TISEL_TI4SEL_Pos)             /*!< 0x04000000 */
#define TIM2_TISEL_TI4SEL_3        (0x8U << TIM2_TISEL_TI4SEL_Pos)             /*!< 0x08000000 */

/*******************  Bit definition for TIM3_AF1 register  *********************/
#define TIM3_AF1_ETRSEL_Pos       (14U)
#define TIM3_AF1_ETRSEL_Msk       (0xFU << TIM3_AF1_ETRSEL_Pos)              /*!< 0x0003C000 */
#define TIM3_AF1_ETRSEL           TIM3_AF1_ETRSEL_Msk                        /*!<ETRSEL[3:0] bits (TIM3 ETR SEL) */
#define TIM3_AF1_ETRSEL_0         (0x1U << TIM3_AF1_ETRSEL_Pos)              /*!< 0x00004000 */
#define TIM3_AF1_ETRSEL_1         (0x2U << TIM3_AF1_ETRSEL_Pos)              /*!< 0x00008000 */
#define TIM3_AF1_ETRSEL_2         (0x4U << TIM3_AF1_ETRSEL_Pos)              /*!< 0x00010000 */
#define TIM3_AF1_ETRSEL_3         (0x8U << TIM3_AF1_ETRSEL_Pos)              /*!< 0x00020000 */

/*******************  Bit definition for TIM3_TISEL register  *********************/
#define TIM3_TISEL_TI1SEL_Pos      (0U)
#define TIM3_TISEL_TI1SEL_Msk      (0xFU << TIM3_TISEL_TI1SEL_Pos)             /*!< 0x0000000F */
#define TIM3_TISEL_TI1SEL          TIM3_TISEL_TI1SEL_Msk                       /*!<TI1SEL[3:0] bits (TIM3 TI1 SEL)*/
#define TIM3_TISEL_TI1SEL_0        (0x1U << TIM3_TISEL_TI1SEL_Pos)             /*!< 0x00000001 */
#define TIM3_TISEL_TI1SEL_1        (0x2U << TIM3_TISEL_TI1SEL_Pos)             /*!< 0x00000002 */
#define TIM3_TISEL_TI1SEL_2        (0x4U << TIM3_TISEL_TI1SEL_Pos)             /*!< 0x00000004 */
#define TIM3_TISEL_TI1SEL_3        (0x8U << TIM3_TISEL_TI1SEL_Pos)             /*!< 0x00000008 */

#define TIM3_TISEL_TI2SEL_Pos      (8U)
#define TIM3_TISEL_TI2SEL_Msk      (0xFU << TIM3_TISEL_TI2SEL_Pos)             /*!< 0x00000F00 */
#define TIM3_TISEL_TI2SEL          TIM3_TISEL_TI2SEL_Msk                       /*!<TI2SEL[3:0] bits (TIM3 TI2 SEL)*/
#define TIM3_TISEL_TI2SEL_0        (0x1U << TIM3_TISEL_TI2SEL_Pos)             /*!< 0x00000100 */
#define TIM3_TISEL_TI2SEL_1        (0x2U << TIM3_TISEL_TI2SEL_Pos)             /*!< 0x00000200 */
#define TIM3_TISEL_TI2SEL_2        (0x4U << TIM3_TISEL_TI2SEL_Pos)             /*!< 0x00000400 */
#define TIM3_TISEL_TI2SEL_3        (0x8U << TIM3_TISEL_TI2SEL_Pos)             /*!< 0x00000800 */

#define TIM3_TISEL_TI3SEL_Pos      (16U)
#define TIM3_TISEL_TI3SEL_Msk      (0xFU << TIM3_TISEL_TI3SEL_Pos)             /*!< 0x000F0000 */
#define TIM3_TISEL_TI3SEL          TIM3_TISEL_TI3SEL_Msk                       /*!<TI3SEL[3:0] bits (TIM3 TI3 SEL)*/
#define TIM3_TISEL_TI3SEL_0        (0x1U << TIM3_TISEL_TI3SEL_Pos)             /*!< 0x00010000 */
#define TIM3_TISEL_TI3SEL_1        (0x2U << TIM3_TISEL_TI3SEL_Pos)             /*!< 0x00020000 */
#define TIM3_TISEL_TI3SEL_2        (0x4U << TIM3_TISEL_TI3SEL_Pos)             /*!< 0x00040000 */
#define TIM3_TISEL_TI3SEL_3        (0x8U << TIM3_TISEL_TI3SEL_Pos)             /*!< 0x00080000 */

#define TIM3_TISEL_TI4SEL_Pos      (24U)
#define TIM3_TISEL_TI4SEL_Msk      (0xFU << TIM3_TISEL_TI4SEL_Pos)             /*!< 0x0F000000 */
#define TIM3_TISEL_TI4SEL          TIM3_TISEL_TI4SEL_Msk                       /*!<TI4SEL[3:0] bits (TIM3 TI4 SEL)*/
#define TIM3_TISEL_TI4SEL_0        (0x1U << TIM3_TISEL_TI4SEL_Pos)             /*!< 0x01000000 */
#define TIM3_TISEL_TI4SEL_1        (0x2U << TIM3_TISEL_TI4SEL_Pos)             /*!< 0x02000000 */
#define TIM3_TISEL_TI4SEL_2        (0x4U << TIM3_TISEL_TI4SEL_Pos)             /*!< 0x04000000 */
#define TIM3_TISEL_TI4SEL_3        (0x8U << TIM3_TISEL_TI4SEL_Pos)             /*!< 0x08000000 */

/*******************  Bit definition for TIM4_AF1 register  *********************/
#define TIM4_AF1_ETRSEL_Pos       (14U)
#define TIM4_AF1_ETRSEL_Msk       (0xFU << TIM4_AF1_ETRSEL_Pos)              /*!< 0x0003C000 */
#define TIM4_AF1_ETRSEL           TIM4_AF1_ETRSEL_Msk                        /*!<ETRSEL[3:0] bits (TIM4 ETR SEL) */
#define TIM4_AF1_ETRSEL_0         (0x1U << TIM4_AF1_ETRSEL_Pos)              /*!< 0x00004000 */
#define TIM4_AF1_ETRSEL_1         (0x2U << TIM4_AF1_ETRSEL_Pos)              /*!< 0x00008000 */
#define TIM4_AF1_ETRSEL_2         (0x4U << TIM4_AF1_ETRSEL_Pos)              /*!< 0x00010000 */
#define TIM4_AF1_ETRSEL_3         (0x8U << TIM4_AF1_ETRSEL_Pos)              /*!< 0x00020000 */

/*******************  Bit definition for TIM4_TISEL register  *********************/
#define TIM4_TISEL_TI1SEL_Pos      (0U)
#define TIM4_TISEL_TI1SEL_Msk      (0xFU << TIM4_TISEL_TI1SEL_Pos)             /*!< 0x0000000F */
#define TIM4_TISEL_TI1SEL          TIM4_TISEL_TI1SEL_Msk                       /*!<TI1SEL[3:0] bits (TIM4 TI1 SEL)*/
#define TIM4_TISEL_TI1SEL_0        (0x1U << TIM4_TISEL_TI1SEL_Pos)             /*!< 0x00000001 */
#define TIM4_TISEL_TI1SEL_1        (0x2U << TIM4_TISEL_TI1SEL_Pos)             /*!< 0x00000002 */
#define TIM4_TISEL_TI1SEL_2        (0x4U << TIM4_TISEL_TI1SEL_Pos)             /*!< 0x00000004 */
#define TIM4_TISEL_TI1SEL_3        (0x8U << TIM4_TISEL_TI1SEL_Pos)             /*!< 0x00000008 */

#define TIM4_TISEL_TI2SEL_Pos      (8U)
#define TIM4_TISEL_TI2SEL_Msk      (0xFU << TIM4_TISEL_TI2SEL_Pos)             /*!< 0x00000F00 */
#define TIM4_TISEL_TI2SEL          TIM4_TISEL_TI2SEL_Msk                       /*!<TI2SEL[3:0] bits (TIM4 TI2 SEL)*/
#define TIM4_TISEL_TI2SEL_0        (0x1U << TIM4_TISEL_TI2SEL_Pos)             /*!< 0x00000100 */
#define TIM4_TISEL_TI2SEL_1        (0x2U << TIM4_TISEL_TI2SEL_Pos)             /*!< 0x00000200 */
#define TIM4_TISEL_TI2SEL_2        (0x4U << TIM4_TISEL_TI2SEL_Pos)             /*!< 0x00000400 */
#define TIM4_TISEL_TI2SEL_3        (0x8U << TIM4_TISEL_TI2SEL_Pos)             /*!< 0x00000800 */

#define TIM4_TISEL_TI3SEL_Pos      (16U)
#define TIM4_TISEL_TI3SEL_Msk      (0xFU << TIM4_TISEL_TI3SEL_Pos)             /*!< 0x000F0000 */
#define TIM4_TISEL_TI3SEL          TIM4_TISEL_TI3SEL_Msk                       /*!<TI3SEL[3:0] bits (TIM4 TI3 SEL)*/
#define TIM4_TISEL_TI3SEL_0        (0x1U << TIM4_TISEL_TI3SEL_Pos)             /*!< 0x00010000 */
#define TIM4_TISEL_TI3SEL_1        (0x2U << TIM4_TISEL_TI3SEL_Pos)             /*!< 0x00020000 */
#define TIM4_TISEL_TI3SEL_2        (0x4U << TIM4_TISEL_TI3SEL_Pos)             /*!< 0x00040000 */
#define TIM4_TISEL_TI3SEL_3        (0x8U << TIM4_TISEL_TI3SEL_Pos)             /*!< 0x00080000 */

#define TIM4_TISEL_TI4SEL_Pos      (24U)
#define TIM4_TISEL_TI4SEL_Msk      (0xFU << TIM4_TISEL_TI4SEL_Pos)             /*!< 0x0F000000 */
#define TIM4_TISEL_TI4SEL          TIM4_TISEL_TI4SEL_Msk                       /*!<TI4SEL[3:0] bits (TIM4 TI4 SEL)*/
#define TIM4_TISEL_TI4SEL_0        (0x1U << TIM4_TISEL_TI4SEL_Pos)             /*!< 0x01000000 */
#define TIM4_TISEL_TI4SEL_1        (0x2U << TIM4_TISEL_TI4SEL_Pos)             /*!< 0x02000000 */
#define TIM4_TISEL_TI4SEL_2        (0x4U << TIM4_TISEL_TI4SEL_Pos)             /*!< 0x04000000 */
#define TIM4_TISEL_TI4SEL_3        (0x8U << TIM4_TISEL_TI4SEL_Pos)             /*!< 0x08000000 */

/*******************  Bit definition for TIM5_AF1 register  *********************/
#define TIM5_AF1_ETRSEL_Pos       (14U)
#define TIM5_AF1_ETRSEL_Msk       (0xFU << TIM5_AF1_ETRSEL_Pos)              /*!< 0x0003C000 */
#define TIM5_AF1_ETRSEL           TIM5_AF1_ETRSEL_Msk                        /*!<ETRSEL[3:0] bits (TIM5 ETR SEL) */
#define TIM5_AF1_ETRSEL_0         (0x1U << TIM5_AF1_ETRSEL_Pos)              /*!< 0x00004000 */
#define TIM5_AF1_ETRSEL_1         (0x2U << TIM5_AF1_ETRSEL_Pos)              /*!< 0x00008000 */
#define TIM5_AF1_ETRSEL_2         (0x4U << TIM5_AF1_ETRSEL_Pos)              /*!< 0x00010000 */
#define TIM5_AF1_ETRSEL_3         (0x8U << TIM5_AF1_ETRSEL_Pos)              /*!< 0x00020000 */

/*******************  Bit definition for TIM5_TISEL register  *********************/
#define TIM5_TISEL_TI1SEL_Pos      (0U)
#define TIM5_TISEL_TI1SEL_Msk      (0xFU << TIM5_TISEL_TI1SEL_Pos)             /*!< 0x0000000F */
#define TIM5_TISEL_TI1SEL          TIM5_TISEL_TI1SEL_Msk                       /*!<TI1SEL[3:0] bits (TIM3 TI1 SEL)*/
#define TIM5_TISEL_TI1SEL_0        (0x1U << TIM5_TISEL_TI1SEL_Pos)             /*!< 0x00000001 */
#define TIM5_TISEL_TI1SEL_1        (0x2U << TIM5_TISEL_TI1SEL_Pos)             /*!< 0x00000002 */
#define TIM5_TISEL_TI1SEL_2        (0x4U << TIM5_TISEL_TI1SEL_Pos)             /*!< 0x00000004 */
#define TIM5_TISEL_TI1SEL_3        (0x8U << TIM5_TISEL_TI1SEL_Pos)             /*!< 0x00000008 */

#define TIM5_TISEL_TI2SEL_Pos      (8U)
#define TIM5_TISEL_TI2SEL_Msk      (0xFU << TIM5_TISEL_TI2SEL_Pos)             /*!< 0x00000F00 */
#define TIM5_TISEL_TI2SEL          TIM5_TISEL_TI2SEL_Msk                       /*!<TI2SEL[3:0] bits (TIM3 TI2 SEL)*/
#define TIM5_TISEL_TI2SEL_0        (0x1U << TIM5_TISEL_TI2SEL_Pos)             /*!< 0x00000100 */
#define TIM5_TISEL_TI2SEL_1        (0x2U << TIM5_TISEL_TI2SEL_Pos)             /*!< 0x00000200 */
#define TIM5_TISEL_TI2SEL_2        (0x4U << TIM5_TISEL_TI2SEL_Pos)             /*!< 0x00000400 */
#define TIM5_TISEL_TI2SEL_3        (0x8U << TIM5_TISEL_TI2SEL_Pos)             /*!< 0x00000800 */

#define TIM5_TISEL_TI3SEL_Pos      (16U)
#define TIM5_TISEL_TI3SEL_Msk      (0xFU << TIM5_TISEL_TI3SEL_Pos)             /*!< 0x000F0000 */
#define TIM5_TISEL_TI3SEL          TIM5_TISEL_TI3SEL_Msk                       /*!<TI3SEL[3:0] bits (TIM3 TI3 SEL)*/
#define TIM5_TISEL_TI3SEL_0        (0x1U << TIM5_TISEL_TI3SEL_Pos)             /*!< 0x00010000 */
#define TIM5_TISEL_TI3SEL_1        (0x2U << TIM5_TISEL_TI3SEL_Pos)             /*!< 0x00020000 */
#define TIM5_TISEL_TI3SEL_2        (0x4U << TIM5_TISEL_TI3SEL_Pos)             /*!< 0x00040000 */
#define TIM5_TISEL_TI3SEL_3        (0x8U << TIM5_TISEL_TI3SEL_Pos)             /*!< 0x00080000 */

#define TIM5_TISEL_TI4SEL_Pos      (24U)
#define TIM5_TISEL_TI4SEL_Msk      (0xFU << TIM5_TISEL_TI4SEL_Pos)             /*!< 0x0F000000 */
#define TIM5_TISEL_TI4SEL          TIM5_TISEL_TI4SEL_Msk                       /*!<TI4SEL[3:0] bits (TIM3 TI4 SEL)*/
#define TIM5_TISEL_TI4SEL_0        (0x1U << TIM5_TISEL_TI4SEL_Pos)             /*!< 0x01000000 */
#define TIM5_TISEL_TI4SEL_1        (0x2U << TIM5_TISEL_TI4SEL_Pos)             /*!< 0x02000000 */
#define TIM5_TISEL_TI4SEL_2        (0x4U << TIM5_TISEL_TI4SEL_Pos)             /*!< 0x04000000 */
#define TIM5_TISEL_TI4SEL_3        (0x8U << TIM5_TISEL_TI4SEL_Pos)             /*!< 0x08000000 */

/*******************  Bit definition for TIM15_AF1 register  *********************/
#define TIM15_AF1_BKINE_Pos         (0U)
#define TIM15_AF1_BKINE_Msk         (0x1U << TIM15_AF1_BKINE_Pos)              /*!< 0x00000001 */
#define TIM15_AF1_BKINE             TIM15_AF1_BKINE_Msk                        /*!<BKINE Break input enable bit */
#define TIM15_AF1_BKCMP1E_Pos       (1U)
#define TIM15_AF1_BKCMP1E_Msk       (0x1U << TIM15_AF1_BKCMP1E_Pos)            /*!< 0x00000002 */
#define TIM15_AF1_BKCMP1E           TIM15_AF1_BKCMP1E_Msk                      /*!<BKCMP1E Break Compare1 Enable bit */
#define TIM15_AF1_BKCMP2E_Pos       (2U)
#define TIM15_AF1_BKCMP2E_Msk       (0x1U << TIM15_AF1_BKCMP2E_Pos)            /*!< 0x00000004 */
#define TIM15_AF1_BKCMP2E           TIM15_AF1_BKCMP2E_Msk                      /*!<BKCMP1E Break Compare2 Enable bit  */
#define TIM15_AF1_BKDF1BK2E_Pos     (8U)
#define TIM15_AF1_BKDF1BK2E_Msk     (0x1U << TIM15_AF1_BKDF1BK2E_Pos)          /*!< 0x00000100 */
#define TIM15_AF1_BKDF1BK2E         TIM15_AF1_BKDF1BK2E_Msk                    /*!<BRK dfsdm1_break[0] enable */
#define TIM15_AF1_BKINP_Pos         (9U)
#define TIM15_AF1_BKINP_Msk         (0x1U << TIM15_AF1_BKINP_Pos)              /*!< 0x00000200 */
#define TIM15_AF1_BKINP             TIM15_AF1_BKINP_Msk                        /*!<BRKINP Break input polarity */
#define TIM15_AF1_BKCMP1P_Pos       (10U)
#define TIM15_AF1_BKCMP1P_Msk       (0x1U << TIM15_AF1_BKCMP1P_Pos)            /*!< 0x00000400 */
#define TIM15_AF1_BKCMP1P           TIM15_AF1_BKCMP1P_Msk                      /*!<BKCMP1P Break COMP1 input polarity */
#define TIM15_AF1_BKCMP2P_Pos       (11U)
#define TIM15_AF1_BKCMP2P_Msk       (0x1U << TIM15_AF1_BKCMP2P_Pos)            /*!< 0x00000800 */
#define TIM15_AF1_BKCMP2P           TIM15_AF1_BKCMP2P_Msk                      /*!<BKCMP2P Break COMP2 input polarity */

/*******************  Bit definition for TIM15_TISEL register  *********************/
#define TIM15_TISEL_TI1SEL_Pos      (0U)
#define TIM15_TISEL_TI1SEL_Msk      (0xFU << TIM15_TISEL_TI1SEL_Pos)           /*!< 0x0000000F */
#define TIM15_TISEL_TI1SEL          TIM15_TISEL_TI1SEL_Msk                     /*!<TI1SEL[3:0] bits (TIM15 TI1 SEL)*/
#define TIM15_TISEL_TI1SEL_0        (0x1U << TIM15_TISEL_TI1SEL_Pos)           /*!< 0x00000001 */
#define TIM15_TISEL_TI1SEL_1        (0x2U << TIM15_TISEL_TI1SEL_Pos)           /*!< 0x00000002 */
#define TIM15_TISEL_TI1SEL_2        (0x4U << TIM15_TISEL_TI1SEL_Pos)           /*!< 0x00000004 */
#define TIM15_TISEL_TI1SEL_3        (0x8U << TIM15_TISEL_TI1SEL_Pos)           /*!< 0x00000008 */

#define TIM15_TISEL_TI2SEL_Pos      (8U)
#define TIM15_TISEL_TI2SEL_Msk      (0xFU << TIM15_TISEL_TI2SEL_Pos)           /*!< 0x00000F00 */
#define TIM15_TISEL_TI2SEL          TIM15_TISEL_TI2SEL_Msk                     /*!<TI2SEL[3:0] bits (TIM15 TI2 SEL)*/
#define TIM15_TISEL_TI2SEL_0        (0x1U << TIM15_TISEL_TI2SEL_Pos)           /*!< 0x00000100 */
#define TIM15_TISEL_TI2SEL_1        (0x2U << TIM15_TISEL_TI2SEL_Pos)           /*!< 0x00000200 */
#define TIM15_TISEL_TI2SEL_2        (0x4U << TIM15_TISEL_TI2SEL_Pos)           /*!< 0x00000400 */
#define TIM15_TISEL_TI2SEL_3        (0x8U << TIM15_TISEL_TI2SEL_Pos)           /*!< 0x00000800 */

/*******************  Bit definition for TIM12_TISEL register  *********************/
#define TIM12_TISEL_TI1SEL_Pos      (0U)
#define TIM12_TISEL_TI1SEL_Msk      (0xFU << TIM12_TISEL_TI1SEL_Pos)           /*!< 0x0000000F */
#define TIM12_TISEL_TI1SEL          TIM12_TISEL_TI1SEL_Msk                     /*!<TI1SEL[3:0] bits (TIM12 TI1 SEL)*/
#define TIM12_TISEL_TI1SEL_0        (0x1U << TIM12_TISEL_TI1SEL_Pos)           /*!< 0x00000001 */
#define TIM12_TISEL_TI1SEL_1        (0x2U << TIM12_TISEL_TI1SEL_Pos)           /*!< 0x00000002 */
#define TIM12_TISEL_TI1SEL_2        (0x4U << TIM12_TISEL_TI1SEL_Pos)           /*!< 0x00000004 */
#define TIM12_TISEL_TI1SEL_3        (0x8U << TIM12_TISEL_TI1SEL_Pos)           /*!< 0x00000008 */

#define TIM12_TISEL_TI2SEL_Pos      (8U)
#define TIM12_TISEL_TI2SEL_Msk      (0xFU << TIM12_TISEL_TI2SEL_Pos)           /*!< 0x00000F00 */
#define TIM12_TISEL_TI2SEL          TIM12_TISEL_TI2SEL_Msk                     /*!<TI2SEL[3:0] bits (TIM15 TI2 SEL)*/
#define TIM12_TISEL_TI2SEL_0        (0x1U << TIM12_TISEL_TI2SEL_Pos)           /*!< 0x00000100 */
#define TIM12_TISEL_TI2SEL_1        (0x2U << TIM12_TISEL_TI2SEL_Pos)           /*!< 0x00000200 */
#define TIM12_TISEL_TI2SEL_2        (0x4U << TIM12_TISEL_TI2SEL_Pos)           /*!< 0x00000400 */
#define TIM12_TISEL_TI2SEL_3        (0x8U << TIM12_TISEL_TI2SEL_Pos)           /*!< 0x00000800 */

/*******************  Bit definition for TIM16_ register  *********************/
#define TIM16_AF1_BKINE_Pos         (0U)
#define TIM16_AF1_BKINE_Msk         (0x1U << TIM16_AF1_BKINE_Pos)              /*!< 0x00000001 */
#define TIM16_AF1_BKINE             TIM16_AF1_BKINE_Msk                        /*!<BKINE Break input enable bit */
#define TIM16_AF1_BKDF1BK2E_Pos     (8U)
#define TIM16_AF1_BKDF1BK2E_Msk     (0x1U << TIM16_AF1_BKDF1BK2E_Pos)          /*!< 0x00000100 */
#define TIM16_AF1_BKDF1BK2E         TIM16_AF1_BKDF1BK2E_Msk                    /*!<BRK dfsdm1_break[1] enable */
#define TIM16_AF1_BKINP_Pos         (9U)
#define TIM16_AF1_BKINP_Msk         (0x1U << TIM16_AF1_BKINP_Pos)              /*!< 0x00000200 */
#define TIM16_AF1_BKINP             TIM16_AF1_BKINP_Msk                        /*!<BRKINP Break input polarity */

/*******************  Bit definition for TIM16_TISEL register  *********************/
#define TIM16_TISEL_TI1SEL_Pos      (0U)
#define TIM16_TISEL_TI1SEL_Msk      (0xFU << TIM16_TISEL_TI1SEL_Pos)           /*!< 0x0000000F */
#define TIM16_TISEL_TI1SEL          TIM16_TISEL_TI1SEL_Msk                     /*!<TI1SEL[3:0] bits (TIM16 TI1 SEL) */
#define TIM16_TISEL_TI1SEL_0        (0x1U << TIM16_TISEL_TI1SEL_Pos)           /*!< 0x00000001 */
#define TIM16_TISEL_TI1SEL_1        (0x2U << TIM16_TISEL_TI1SEL_Pos)           /*!< 0x00000002 */
#define TIM16_TISEL_TI1SEL_2        (0x4U << TIM16_TISEL_TI1SEL_Pos)           /*!< 0x00000004 */
#define TIM16_TISEL_TI1SEL_3        (0x8U << TIM16_TISEL_TI1SEL_Pos)           /*!< 0x00000008 */

/*******************  Bit definition for TIM17_AF1 register  *********************/
#define TIM17_AF1_BKINE_Pos         (0U)
#define TIM17_AF1_BKINE_Msk         (0x1U << TIM17_AF1_BKINE_Pos)              /*!< 0x00000001 */
#define TIM17_AF1_BKINE             TIM17_AF1_BKINE_Msk                        /*!<BKINE Break input enable bit */
#define TIM17_AF1_BKDF1BK2E_Pos     (8U)
#define TIM17_AF1_BKDF1BK2E_Msk     (0x1U << TIM17_AF1_BKDF1BK2E_Pos)          /*!< 0x00000100 */
#define TIM17_AF1_BKDF1BK2E         TIM17_AF1_BKDF1BK2E_Msk                    /*!<BRK dfsdm1_break[2] enable */
#define TIM17_AF1_BKINP_Pos         (9U)
#define TIM17_AF1_BKINP_Msk         (0x1U << TIM17_AF1_BKINP_Pos)              /*!< 0x00000200 */
#define TIM17_AF1_BKINP             TIM17_AF1_BKINP_Msk                        /*!<BRKINP Break input polarity */


/*******************  Bit definition for TIM17_TISEL register  *********************/
#define TIM17_TISEL_TI1SEL_Pos      (0U)
#define TIM17_TISEL_TI1SEL_Msk      (0xFU << TIM17_TISEL_TI1SEL_Pos)           /*!< 0x0000000F */
#define TIM17_TISEL_TI1SEL          TIM17_TISEL_TI1SEL_Msk                     /*!<TI1SEL[3:0] bits (TIM17 TI1 SEL) */
#define TIM17_TISEL_TI1SEL_0        (0x1U << TIM17_TISEL_TI1SEL_Pos)           /*!< 0x00000001 */
#define TIM17_TISEL_TI1SEL_1        (0x2U << TIM17_TISEL_TI1SEL_Pos)           /*!< 0x00000002 */
#define TIM17_TISEL_TI1SEL_2        (0x4U << TIM17_TISEL_TI1SEL_Pos)           /*!< 0x00000004 */
#define TIM17_TISEL_TI1SEL_3        (0x8U << TIM17_TISEL_TI1SEL_Pos)           /*!< 0x00000008 */

/*******************  Bit definition for TIM_TISEL register  *********************/
#define TIM_TISEL_TI1SEL_Pos      (0U)
#define TIM_TISEL_TI1SEL_Msk      (0xFUL << TIM_TISEL_TI1SEL_Pos)              /*!< 0x0000000F */
#define TIM_TISEL_TI1SEL          TIM_TISEL_TI1SEL_Msk                         /*!<TI1SEL[3:0] bits (TIM1 TI1 SEL)*/
#define TIM_TISEL_TI1SEL_0        (0x1UL << TIM_TISEL_TI1SEL_Pos)              /*!< 0x00000001 */
#define TIM_TISEL_TI1SEL_1        (0x2UL << TIM_TISEL_TI1SEL_Pos)              /*!< 0x00000002 */
#define TIM_TISEL_TI1SEL_2        (0x4UL << TIM_TISEL_TI1SEL_Pos)              /*!< 0x00000004 */
#define TIM_TISEL_TI1SEL_3        (0x8UL << TIM_TISEL_TI1SEL_Pos)              /*!< 0x00000008 */

#define TIM_TISEL_TI2SEL_Pos      (8U)
#define TIM_TISEL_TI2SEL_Msk      (0xFUL << TIM_TISEL_TI2SEL_Pos)              /*!< 0x00000F00 */
#define TIM_TISEL_TI2SEL          TIM_TISEL_TI2SEL_Msk                         /*!<TI2SEL[3:0] bits (TIM1 TI2 SEL)*/
#define TIM_TISEL_TI2SEL_0        (0x1UL << TIM_TISEL_TI2SEL_Pos)              /*!< 0x00000100 */
#define TIM_TISEL_TI2SEL_1        (0x2UL << TIM_TISEL_TI2SEL_Pos)              /*!< 0x00000200 */
#define TIM_TISEL_TI2SEL_2        (0x4UL << TIM_TISEL_TI2SEL_Pos)              /*!< 0x00000400 */
#define TIM_TISEL_TI2SEL_3        (0x8UL << TIM_TISEL_TI2SEL_Pos)              /*!< 0x00000800 */

#define TIM_TISEL_TI3SEL_Pos      (16U)
#define TIM_TISEL_TI3SEL_Msk      (0xFUL << TIM_TISEL_TI3SEL_Pos)              /*!< 0x000F0000 */
#define TIM_TISEL_TI3SEL          TIM_TISEL_TI3SEL_Msk                         /*!<TI3SEL[3:0] bits (TIM1 TI3 SEL)*/
#define TIM_TISEL_TI3SEL_0        (0x1UL << TIM_TISEL_TI3SEL_Pos)              /*!< 0x00010000 */
#define TIM_TISEL_TI3SEL_1        (0x2UL << TIM_TISEL_TI3SEL_Pos)              /*!< 0x00020000 */
#define TIM_TISEL_TI3SEL_2        (0x4UL << TIM_TISEL_TI3SEL_Pos)              /*!< 0x00040000 */
#define TIM_TISEL_TI3SEL_3        (0x8UL << TIM_TISEL_TI3SEL_Pos)              /*!< 0x00080000 */

#define TIM_TISEL_TI4SEL_Pos      (24U)
#define TIM_TISEL_TI4SEL_Msk      (0xFUL << TIM_TISEL_TI4SEL_Pos)              /*!< 0x0F000000 */
#define TIM_TISEL_TI4SEL          TIM_TISEL_TI4SEL_Msk                         /*!<TI4SEL[3:0] bits (TIM1 TI4 SEL)*/
#define TIM_TISEL_TI4SEL_0        (0x1UL << TIM_TISEL_TI4SEL_Pos)              /*!< 0x01000000 */
#define TIM_TISEL_TI4SEL_1        (0x2UL << TIM_TISEL_TI4SEL_Pos)              /*!< 0x02000000 */
#define TIM_TISEL_TI4SEL_2        (0x4UL << TIM_TISEL_TI4SEL_Pos)              /*!< 0x04000000 */
#define TIM_TISEL_TI4SEL_3        (0x8UL << TIM_TISEL_TI4SEL_Pos)              /*!< 0x08000000 */

/******************************************************************************/
/*                                                                            */
/*                         Low Power Timer (LPTTIM)                           */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for LPTIM_ISR register  *******************/
#define LPTIM_ISR_CMPM_Pos          (0U)
#define LPTIM_ISR_CMPM_Msk          (0x1U << LPTIM_ISR_CMPM_Pos)               /*!< 0x00000001 */
#define LPTIM_ISR_CMPM              LPTIM_ISR_CMPM_Msk                         /*!< Compare match */
#define LPTIM_ISR_ARRM_Pos          (1U)
#define LPTIM_ISR_ARRM_Msk          (0x1U << LPTIM_ISR_ARRM_Pos)               /*!< 0x00000002 */
#define LPTIM_ISR_ARRM              LPTIM_ISR_ARRM_Msk                         /*!< Autoreload match */
#define LPTIM_ISR_EXTTRIG_Pos       (2U)
#define LPTIM_ISR_EXTTRIG_Msk       (0x1U << LPTIM_ISR_EXTTRIG_Pos)            /*!< 0x00000004 */
#define LPTIM_ISR_EXTTRIG           LPTIM_ISR_EXTTRIG_Msk                      /*!< External trigger edge event */
#define LPTIM_ISR_CMPOK_Pos         (3U)
#define LPTIM_ISR_CMPOK_Msk         (0x1U << LPTIM_ISR_CMPOK_Pos)              /*!< 0x00000008 */
#define LPTIM_ISR_CMPOK             LPTIM_ISR_CMPOK_Msk                        /*!< Compare register update OK */
#define LPTIM_ISR_ARROK_Pos         (4U)
#define LPTIM_ISR_ARROK_Msk         (0x1U << LPTIM_ISR_ARROK_Pos)              /*!< 0x00000010 */
#define LPTIM_ISR_ARROK             LPTIM_ISR_ARROK_Msk                        /*!< Autoreload register update OK */
#define LPTIM_ISR_UP_Pos            (5U)
#define LPTIM_ISR_UP_Msk            (0x1U << LPTIM_ISR_UP_Pos)                 /*!< 0x00000020 */
#define LPTIM_ISR_UP                LPTIM_ISR_UP_Msk                           /*!< Counter direction change down to up */
#define LPTIM_ISR_DOWN_Pos          (6U)
#define LPTIM_ISR_DOWN_Msk          (0x1U << LPTIM_ISR_DOWN_Pos)               /*!< 0x00000040 */
#define LPTIM_ISR_DOWN              LPTIM_ISR_DOWN_Msk                         /*!< Counter direction change up to down */

/******************  Bit definition for LPTIM_ICR register  *******************/
#define LPTIM_ICR_CMPMCF_Pos        (0U)
#define LPTIM_ICR_CMPMCF_Msk        (0x1U << LPTIM_ICR_CMPMCF_Pos)             /*!< 0x00000001 */
#define LPTIM_ICR_CMPMCF            LPTIM_ICR_CMPMCF_Msk                       /*!< Compare match Clear Flag */
#define LPTIM_ICR_ARRMCF_Pos        (1U)
#define LPTIM_ICR_ARRMCF_Msk        (0x1U << LPTIM_ICR_ARRMCF_Pos)             /*!< 0x00000002 */
#define LPTIM_ICR_ARRMCF            LPTIM_ICR_ARRMCF_Msk                       /*!< Autoreload match Clear Flag */
#define LPTIM_ICR_EXTTRIGCF_Pos     (2U)
#define LPTIM_ICR_EXTTRIGCF_Msk     (0x1U << LPTIM_ICR_EXTTRIGCF_Pos)          /*!< 0x00000004 */
#define LPTIM_ICR_EXTTRIGCF         LPTIM_ICR_EXTTRIGCF_Msk                    /*!< External trigger edge event Clear Flag */
#define LPTIM_ICR_CMPOKCF_Pos       (3U)
#define LPTIM_ICR_CMPOKCF_Msk       (0x1U << LPTIM_ICR_CMPOKCF_Pos)            /*!< 0x00000008 */
#define LPTIM_ICR_CMPOKCF           LPTIM_ICR_CMPOKCF_Msk                      /*!< Compare register update OK Clear Flag */
#define LPTIM_ICR_ARROKCF_Pos       (4U)
#define LPTIM_ICR_ARROKCF_Msk       (0x1U << LPTIM_ICR_ARROKCF_Pos)            /*!< 0x00000010 */
#define LPTIM_ICR_ARROKCF           LPTIM_ICR_ARROKCF_Msk                      /*!< Autoreload register update OK Clear Flag */
#define LPTIM_ICR_UPCF_Pos          (5U)
#define LPTIM_ICR_UPCF_Msk          (0x1U << LPTIM_ICR_UPCF_Pos)               /*!< 0x00000020 */
#define LPTIM_ICR_UPCF              LPTIM_ICR_UPCF_Msk                         /*!< Counter direction change down to up Clear Flag */
#define LPTIM_ICR_DOWNCF_Pos        (6U)
#define LPTIM_ICR_DOWNCF_Msk        (0x1U << LPTIM_ICR_DOWNCF_Pos)             /*!< 0x00000040 */
#define LPTIM_ICR_DOWNCF            LPTIM_ICR_DOWNCF_Msk                       /*!< Counter direction change up to down Clear Flag */

/******************  Bit definition for LPTIM_IER register ********************/
#define LPTIM_IER_CMPMIE_Pos        (0U)
#define LPTIM_IER_CMPMIE_Msk        (0x1U << LPTIM_IER_CMPMIE_Pos)             /*!< 0x00000001 */
#define LPTIM_IER_CMPMIE            LPTIM_IER_CMPMIE_Msk                       /*!< Compare match Interrupt Enable */
#define LPTIM_IER_ARRMIE_Pos        (1U)
#define LPTIM_IER_ARRMIE_Msk        (0x1U << LPTIM_IER_ARRMIE_Pos)             /*!< 0x00000002 */
#define LPTIM_IER_ARRMIE            LPTIM_IER_ARRMIE_Msk                       /*!< Autoreload match Interrupt Enable */
#define LPTIM_IER_EXTTRIGIE_Pos     (2U)
#define LPTIM_IER_EXTTRIGIE_Msk     (0x1U << LPTIM_IER_EXTTRIGIE_Pos)          /*!< 0x00000004 */
#define LPTIM_IER_EXTTRIGIE         LPTIM_IER_EXTTRIGIE_Msk                    /*!< External trigger edge event Interrupt Enable */
#define LPTIM_IER_CMPOKIE_Pos       (3U)
#define LPTIM_IER_CMPOKIE_Msk       (0x1U << LPTIM_IER_CMPOKIE_Pos)            /*!< 0x00000008 */
#define LPTIM_IER_CMPOKIE           LPTIM_IER_CMPOKIE_Msk                      /*!< Compare register update OK Interrupt Enable */
#define LPTIM_IER_ARROKIE_Pos       (4U)
#define LPTIM_IER_ARROKIE_Msk       (0x1U << LPTIM_IER_ARROKIE_Pos)            /*!< 0x00000010 */
#define LPTIM_IER_ARROKIE           LPTIM_IER_ARROKIE_Msk                      /*!< Autoreload register update OK Interrupt Enable */
#define LPTIM_IER_UPIE_Pos          (5U)
#define LPTIM_IER_UPIE_Msk          (0x1U << LPTIM_IER_UPIE_Pos)               /*!< 0x00000020 */
#define LPTIM_IER_UPIE              LPTIM_IER_UPIE_Msk                         /*!< Counter direction change down to up Interrupt Enable */
#define LPTIM_IER_DOWNIE_Pos        (6U)
#define LPTIM_IER_DOWNIE_Msk        (0x1U << LPTIM_IER_DOWNIE_Pos)             /*!< 0x00000040 */
#define LPTIM_IER_DOWNIE            LPTIM_IER_DOWNIE_Msk                       /*!< Counter direction change up to down Interrupt Enable */

/******************  Bit definition for LPTIM_CFGR register *******************/
#define LPTIM_CFGR_CKSEL_Pos        (0U)
#define LPTIM_CFGR_CKSEL_Msk        (0x1U << LPTIM_CFGR_CKSEL_Pos)             /*!< 0x00000001 */
#define LPTIM_CFGR_CKSEL            LPTIM_CFGR_CKSEL_Msk                       /*!< Clock selector */

#define LPTIM_CFGR_CKPOL_Pos        (1U)
#define LPTIM_CFGR_CKPOL_Msk        (0x3U << LPTIM_CFGR_CKPOL_Pos)             /*!< 0x00000006 */
#define LPTIM_CFGR_CKPOL            LPTIM_CFGR_CKPOL_Msk                       /*!< CKPOL[1:0] bits (Clock polarity) */
#define LPTIM_CFGR_CKPOL_0          (0x1U << LPTIM_CFGR_CKPOL_Pos)             /*!< 0x00000002 */
#define LPTIM_CFGR_CKPOL_1          (0x2U << LPTIM_CFGR_CKPOL_Pos)             /*!< 0x00000004 */

#define LPTIM_CFGR_CKFLT_Pos        (3U)
#define LPTIM_CFGR_CKFLT_Msk        (0x3U << LPTIM_CFGR_CKFLT_Pos)             /*!< 0x00000018 */
#define LPTIM_CFGR_CKFLT            LPTIM_CFGR_CKFLT_Msk                       /*!< CKFLT[1:0] bits (Configurable digital filter for external clock) */
#define LPTIM_CFGR_CKFLT_0          (0x1U << LPTIM_CFGR_CKFLT_Pos)             /*!< 0x00000008 */
#define LPTIM_CFGR_CKFLT_1          (0x2U << LPTIM_CFGR_CKFLT_Pos)             /*!< 0x00000010 */

#define LPTIM_CFGR_TRGFLT_Pos       (6U)
#define LPTIM_CFGR_TRGFLT_Msk       (0x3U << LPTIM_CFGR_TRGFLT_Pos)            /*!< 0x000000C0 */
#define LPTIM_CFGR_TRGFLT           LPTIM_CFGR_TRGFLT_Msk                      /*!< TRGFLT[1:0] bits (Configurable digital filter for trigger) */
#define LPTIM_CFGR_TRGFLT_0         (0x1U << LPTIM_CFGR_TRGFLT_Pos)            /*!< 0x00000040 */
#define LPTIM_CFGR_TRGFLT_1         (0x2U << LPTIM_CFGR_TRGFLT_Pos)            /*!< 0x00000080 */

#define LPTIM_CFGR_PRESC_Pos        (9U)
#define LPTIM_CFGR_PRESC_Msk        (0x7U << LPTIM_CFGR_PRESC_Pos)             /*!< 0x00000E00 */
#define LPTIM_CFGR_PRESC            LPTIM_CFGR_PRESC_Msk                       /*!< PRESC[2:0] bits (Clock prescaler) */
#define LPTIM_CFGR_PRESC_0          (0x1U << LPTIM_CFGR_PRESC_Pos)             /*!< 0x00000200 */
#define LPTIM_CFGR_PRESC_1          (0x2U << LPTIM_CFGR_PRESC_Pos)             /*!< 0x00000400 */
#define LPTIM_CFGR_PRESC_2          (0x4U << LPTIM_CFGR_PRESC_Pos)             /*!< 0x00000800 */

#define LPTIM_CFGR_TRIGSEL_Pos      (13U)
#define LPTIM_CFGR_TRIGSEL_Msk      (0x7U << LPTIM_CFGR_TRIGSEL_Pos)           /*!< 0x0000E000 */
#define LPTIM_CFGR_TRIGSEL          LPTIM_CFGR_TRIGSEL_Msk                     /*!< TRIGSEL[2:0]] bits (Trigger selector) */
#define LPTIM_CFGR_TRIGSEL_0        (0x1U << LPTIM_CFGR_TRIGSEL_Pos)           /*!< 0x00002000 */
#define LPTIM_CFGR_TRIGSEL_1        (0x2U << LPTIM_CFGR_TRIGSEL_Pos)           /*!< 0x00004000 */
#define LPTIM_CFGR_TRIGSEL_2        (0x4U << LPTIM_CFGR_TRIGSEL_Pos)           /*!< 0x00008000 */

#define LPTIM_CFGR_TRIGEN_Pos       (17U)
#define LPTIM_CFGR_TRIGEN_Msk       (0x3U << LPTIM_CFGR_TRIGEN_Pos)            /*!< 0x00060000 */
#define LPTIM_CFGR_TRIGEN           LPTIM_CFGR_TRIGEN_Msk                      /*!< TRIGEN[1:0] bits (Trigger enable and polarity) */
#define LPTIM_CFGR_TRIGEN_0         (0x1U << LPTIM_CFGR_TRIGEN_Pos)            /*!< 0x00020000 */
#define LPTIM_CFGR_TRIGEN_1         (0x2U << LPTIM_CFGR_TRIGEN_Pos)            /*!< 0x00040000 */

#define LPTIM_CFGR_TIMOUT_Pos       (19U)
#define LPTIM_CFGR_TIMOUT_Msk       (0x1U << LPTIM_CFGR_TIMOUT_Pos)            /*!< 0x00080000 */
#define LPTIM_CFGR_TIMOUT           LPTIM_CFGR_TIMOUT_Msk                      /*!< Timout enable */
#define LPTIM_CFGR_WAVE_Pos         (20U)
#define LPTIM_CFGR_WAVE_Msk         (0x1U << LPTIM_CFGR_WAVE_Pos)              /*!< 0x00100000 */
#define LPTIM_CFGR_WAVE             LPTIM_CFGR_WAVE_Msk                        /*!< Waveform shape */
#define LPTIM_CFGR_WAVPOL_Pos       (21U)
#define LPTIM_CFGR_WAVPOL_Msk       (0x1U << LPTIM_CFGR_WAVPOL_Pos)            /*!< 0x00200000 */
#define LPTIM_CFGR_WAVPOL           LPTIM_CFGR_WAVPOL_Msk                      /*!< Waveform shape polarity */
#define LPTIM_CFGR_PRELOAD_Pos      (22U)
#define LPTIM_CFGR_PRELOAD_Msk      (0x1U << LPTIM_CFGR_PRELOAD_Pos)           /*!< 0x00400000 */
#define LPTIM_CFGR_PRELOAD          LPTIM_CFGR_PRELOAD_Msk                     /*!< Reg update mode */
#define LPTIM_CFGR_COUNTMODE_Pos    (23U)
#define LPTIM_CFGR_COUNTMODE_Msk    (0x1U << LPTIM_CFGR_COUNTMODE_Pos)         /*!< 0x00800000 */
#define LPTIM_CFGR_COUNTMODE        LPTIM_CFGR_COUNTMODE_Msk                   /*!< Counter mode enable */
#define LPTIM_CFGR_ENC_Pos          (24U)
#define LPTIM_CFGR_ENC_Msk          (0x1U << LPTIM_CFGR_ENC_Pos)               /*!< 0x01000000 */
#define LPTIM_CFGR_ENC              LPTIM_CFGR_ENC_Msk                         /*!< Encoder mode enable */

/******************  Bit definition for LPTIM_CR register  ********************/
#define LPTIM_CR_ENABLE_Pos         (0U)
#define LPTIM_CR_ENABLE_Msk         (0x1U << LPTIM_CR_ENABLE_Pos)              /*!< 0x00000001 */
#define LPTIM_CR_ENABLE             LPTIM_CR_ENABLE_Msk                        /*!< LPTIMer enable */
#define LPTIM_CR_SNGSTRT_Pos        (1U)
#define LPTIM_CR_SNGSTRT_Msk        (0x1U << LPTIM_CR_SNGSTRT_Pos)             /*!< 0x00000002 */
#define LPTIM_CR_SNGSTRT            LPTIM_CR_SNGSTRT_Msk                       /*!< Timer start in single mode */
#define LPTIM_CR_CNTSTRT_Pos        (2U)
#define LPTIM_CR_CNTSTRT_Msk        (0x1U << LPTIM_CR_CNTSTRT_Pos)             /*!< 0x00000004 */
#define LPTIM_CR_CNTSTRT            LPTIM_CR_CNTSTRT_Msk                       /*!< Timer start in continuous mode */
#define LPTIM_CR_COUNTRST_Pos       (3U)
#define LPTIM_CR_COUNTRST_Msk       (0x1U << LPTIM_CR_COUNTRST_Pos)            /*!< 0x00000008 */
#define LPTIM_CR_COUNTRST           LPTIM_CR_COUNTRST_Msk                      /*!< Timer Counter reset in synchronous mode*/
#define LPTIM_CR_RSTARE_Pos         (4U)
#define LPTIM_CR_RSTARE_Msk         (0x1U << LPTIM_CR_RSTARE_Pos)              /*!< 0x00000010 */
#define LPTIM_CR_RSTARE             LPTIM_CR_RSTARE_Msk                        /*!< Timer Counter reset after read enable (asynchronously)*/


/******************  Bit definition for LPTIM_CMP register  *******************/
#define LPTIM_CMP_CMP_Pos           (0U)
#define LPTIM_CMP_CMP_Msk           (0xFFFFU << LPTIM_CMP_CMP_Pos)             /*!< 0x0000FFFF */
#define LPTIM_CMP_CMP               LPTIM_CMP_CMP_Msk                          /*!< Compare register */

/******************  Bit definition for LPTIM_ARR register  *******************/
#define LPTIM_ARR_ARR_Pos           (0U)
#define LPTIM_ARR_ARR_Msk           (0xFFFFU << LPTIM_ARR_ARR_Pos)             /*!< 0x0000FFFF */
#define LPTIM_ARR_ARR               LPTIM_ARR_ARR_Msk                          /*!< Auto reload register */

/******************  Bit definition for LPTIM_CNT register  *******************/
#define LPTIM_CNT_CNT_Pos           (0U)
#define LPTIM_CNT_CNT_Msk           (0xFFFFU << LPTIM_CNT_CNT_Pos)             /*!< 0x0000FFFF */
#define LPTIM_CNT_CNT               LPTIM_CNT_CNT_Msk                          /*!< Counter register */

/******************  Bit definition for LPTIM_CFGR2 register  *******************/
#define LPTIM_CFGR2_IN1SEL_Pos      (0U)
#define LPTIM_CFGR2_IN1SEL_Msk      (0xFUL << LPTIM_CFGR2_IN1SEL_Pos)          /*!< 0x0000000F */
#define LPTIM_CFGR2_IN1SEL          LPTIM_CFGR2_IN1SEL_Msk                     /*!< CFGR2[3:0] bits (INPUT1 selection) */
#define LPTIM_CFGR2_IN1SEL_0_Pos    (LPTIM_CFGR2_IN1SEL_Pos)
#define LPTIM_CFGR2_IN1SEL_0_Msk    (0x1U << LPTIM_CFGR2_IN1SEL_0_Pos)         /*!< 0x00000001 */
#define LPTIM_CFGR2_IN1SEL_0        LPTIM_CFGR2_IN1SEL_0_Msk                   /*!< Bit 0 */
#define LPTIM_CFGR2_IN1SEL_1_Pos    (1U)
#define LPTIM_CFGR2_IN1SEL_1_Msk    (0x1U << LPTIM_CFGR2_IN1SEL_1_Pos)         /*!< 0x00000002 */
#define LPTIM_CFGR2_IN1SEL_1        LPTIM_CFGR2_IN1SEL_1_Msk                   /*!< Bit 1 */
#define LPTIM_CFGR2_IN1SEL_2_Pos    (2U)
#define LPTIM_CFGR2_IN1SEL_2_Msk    (0x1U << LPTIM_CFGR2_IN1SEL_2_Pos)         /*!< 0x00000004 */
#define LPTIM_CFGR2_IN1SEL_2        LPTIM_CFGR2_IN1SEL_2_Msk                   /*!< Bit 2 */
#define LPTIM_CFGR2_IN1SEL_3_Pos    (3U)
#define LPTIM_CFGR2_IN1SEL_3_Msk    (0x1U << LPTIM_CFGR2_IN1SEL_3_Pos)         /*!< 0x00000008 */
#define LPTIM_CFGR2_IN1SEL_3        LPTIM_CFGR2_IN1SEL_3_Msk                   /*!< Bit 3 */

#define LPTIM_CFGR2_IN2SEL_Pos      (4U)
#define LPTIM_CFGR2_IN2SEL_Msk      (0xFUL << LPTIM_CFGR2_IN2SEL_Pos)          /*!< 0x000000F0 */
#define LPTIM_CFGR2_IN2SEL          LPTIM_CFGR2_IN2SEL_Msk                     /*!< CFGR2[7:4] bits (INPUT2 selection) */
#define LPTIM_CFGR2_IN2SEL_0_Pos    (LPTIM_CFGR2_IN2SEL_Pos)
#define LPTIM_CFGR2_IN2SEL_0_Msk    (0x1U << LPTIM_CFGR2_IN2SEL_0_Pos)         /*!< 0x00000010 */
#define LPTIM_CFGR2_IN2SEL_0        LPTIM_CFGR2_IN2SEL_0_Msk                   /*!< Bit 4 */
#define LPTIM_CFGR2_IN2SEL_1_Pos    (5U)
#define LPTIM_CFGR2_IN2SEL_1_Msk    (0x1U << LPTIM_CFGR2_IN2SEL_1_Pos)         /*!< 0x00000020 */
#define LPTIM_CFGR2_IN2SEL_1        LPTIM_CFGR2_IN2SEL_1_Msk                   /*!< Bit 5 */
#define LPTIM_CFGR2_IN2SEL_2_Pos    (6U)
#define LPTIM_CFGR2_IN2SEL_2_Msk    (0x1U << LPTIM_CFGR2_IN2SEL_2_Pos)         /*!< 0x00000040 */
#define LPTIM_CFGR2_IN2SEL_2        LPTIM_CFGR2_IN2SEL_2_Msk                   /*!< Bit 6 */
#define LPTIM_CFGR2_IN2SEL_3_Pos    (7U)
#define LPTIM_CFGR2_IN2SEL_3_Msk    (0x1U << LPTIM_CFGR2_IN2SEL_3_Pos)         /*!< 0x00000080 */
#define LPTIM_CFGR2_IN2SEL_3        LPTIM_CFGR2_IN2SEL_3_Msk                   /*!< Bit 7 */

/**********************  Bit definition for LPTIM_HWCFGR register  ***************/
#define LPTIM_HWCFGR_CFG1_Pos  (0U)
#define LPTIM_HWCFGR_CFG1_Msk  (0xFFU << LPTIM_HWCFGR_CFG1_Pos)          /*!< 0x000000FF */
#define LPTIM_HWCFGR_CFG1      LPTIM_HWCFGR_CFG1_Msk                     /*!< HW CFG1 */
#define LPTIM_HWCFGR_CFG2_Pos  (8U)
#define LPTIM_HWCFGR_CFG2_Msk  (0xFFU << LPTIM_HWCFGR_CFG2_Pos)          /*!< 0x0000FF00 */
#define LPTIM_HWCFGR_CFG2      LPTIM_HWCFGR_CFG2_Msk                     /*!< HW CFG2 */
#define LPTIM_HWCFGR_CFG3_Pos  (16U)
#define LPTIM_HWCFGR_CFG3_Msk  (0xFU << LPTIM_HWCFGR_CFG3_Pos)           /*!< 0x000F0000 */
#define LPTIM_HWCFGR_CFG3      LPTIM_HWCFGR_CFG3_Msk                     /*!< HW CFG3 */
#define LPTIM_HWCFGR_CFG4_Pos  (24U)
#define LPTIM_HWCFGR_CFG4_Msk  (0xFFU << LPTIM_HWCFGR_CFG4_Pos)          /*!< 0xFF000000 */
#define LPTIM_HWCFGR_CFG4      LPTIM_HWCFGR_CFG4_Msk                     /*!< HW CFG4 */

/**********************  Bit definition for LPTIM_VERR register  *****************/
#define LPTIM_VERR_MINREV_Pos      (0U)
#define LPTIM_VERR_MINREV_Msk      (0xFU << LPTIM_VERR_MINREV_Pos)               /*!< 0x0000000F */
#define LPTIM_VERR_MINREV          LPTIM_VERR_MINREV_Msk                         /*!< Minor Revision number */
#define LPTIM_VERR_MAJREV_Pos      (4U)
#define LPTIM_VERR_MAJREV_Msk      (0xFU << LPTIM_VERR_MAJREV_Pos)               /*!< 0x000000F0 */
#define LPTIM_VERR_MAJREV          LPTIM_VERR_MAJREV_Msk                         /*!< Major Revision number */

/**********************  Bit definition for LPTIM_PIDR register  ****************/
#define LPTIM_PIDR_IPID_Pos       (0U)
#define LPTIM_PIDR_IPID_Msk       (0xFFFFFFFFU << LPTIM_PIDR_IPID_Pos)         /*!< 0xFFFFFFFF */
#define LPTIM_PIDR_IPID           LPTIM_PIDR_IPID_Msk                          /*!< IP Identification */

/**********************  Bit definition for LPTIM_SIDR register  *****************/
#define LPTIM_SIDR_SID_Pos         (0U)
#define LPTIM_SIDR_SID_Msk         (0xFFFFFFFFU << LPTIM_SIDR_SID_Pos)           /*!< 0xFFFFFFFF */
#define LPTIM_SIDR_SID             LPTIM_SIDR_SID_Msk                            /*!< IP size identification */

/******************************************************************************/
/*                                                                            */
/*                      Analog Comparators (COMP)                             */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for COMP_SR register  ********************/
#define COMP_SR_C1VAL_Pos            (0U)
#define COMP_SR_C1VAL_Msk            (0x1U << COMP_SR_C1VAL_Pos)               /*!< 0x00000001 */
#define COMP_SR_C1VAL                COMP_SR_C1VAL_Msk
#define COMP_SR_C2VAL_Pos            (1U)
#define COMP_SR_C2VAL_Msk            (0x1U << COMP_SR_C2VAL_Pos)               /*!< 0x00000002 */
#define COMP_SR_C2VAL                COMP_SR_C2VAL_Msk
#define COMP_SR_C1IF_Pos             (16U)
#define COMP_SR_C1IF_Msk             (0x1U << COMP_SR_C1IF_Pos)                /*!< 0x00010000 */
#define COMP_SR_C1IF                 COMP_SR_C1IF_Msk
#define COMP_SR_C2IF_Pos             (17U)
#define COMP_SR_C2IF_Msk             (0x1U << COMP_SR_C2IF_Pos)                /*!< 0x00020000 */
#define COMP_SR_C2IF                 COMP_SR_C2IF_Msk
/*******************  Bit definition for COMP_ICFR register  ********************/
#define COMP_ICFR_C1IF_Pos           (16U)
#define COMP_ICFR_C1IF_Msk           (0x1U << COMP_ICFR_C1IF_Pos)              /*!< 0x00010000 */
#define COMP_ICFR_C1IF               COMP_ICFR_C1IF_Msk
#define COMP_ICFR_C2IF_Pos           (17U)
#define COMP_ICFR_C2IF_Msk           (0x1U << COMP_ICFR_C2IF_Pos)              /*!< 0x00020000 */
#define COMP_ICFR_C2IF               COMP_ICFR_C2IF_Msk
/*******************  Bit definition for COMP_OR register  ********************/
#define COMP_OR_AFOPA6_Pos           (0U)
#define COMP_OR_AFOPA6_Msk           (0x1U << COMP_OR_AFOPA6_Pos)              /*!< 0x00000001 */
#define COMP_OR_AFOPA6               COMP_OR_AFOPA6_Msk
#define COMP_OR_AFOPA8_Pos           (1U)
#define COMP_OR_AFOPA8_Msk           (0x1U << COMP_OR_AFOPA8_Pos)              /*!< 0x00000002 */
#define COMP_OR_AFOPA8               COMP_OR_AFOPA8_Msk
#define COMP_OR_AFOPB12_Pos          (2U)
#define COMP_OR_AFOPB12_Msk          (0x1U << COMP_OR_AFOPB12_Pos)             /*!< 0x00000004 */
#define COMP_OR_AFOPB12              COMP_OR_AFOPB12_Msk
#define COMP_OR_AFOPE6_Pos           (3U)
#define COMP_OR_AFOPE6_Msk           (0x1U << COMP_OR_AFOPE6_Pos)              /*!< 0x00000008 */
#define COMP_OR_AFOPE6               COMP_OR_AFOPE6_Msk
#define COMP_OR_AFOPE15_Pos          (4U)
#define COMP_OR_AFOPE15_Msk          (0x1U << COMP_OR_AFOPE15_Pos)             /*!< 0x00000010 */
#define COMP_OR_AFOPE15              COMP_OR_AFOPE15_Msk
#define COMP_OR_AFOPG2_Pos           (5U)
#define COMP_OR_AFOPG2_Msk           (0x1U << COMP_OR_AFOPG2_Pos)              /*!< 0x00000020 */
#define COMP_OR_AFOPG2               COMP_OR_AFOPG2_Msk
#define COMP_OR_AFOPG3_Pos           (6U)
#define COMP_OR_AFOPG3_Msk           (0x1U << COMP_OR_AFOPG3_Pos)              /*!< 0x00000040 */
#define COMP_OR_AFOPG3               COMP_OR_AFOPG3_Msk
#define COMP_OR_AFOPG4_Pos           (7U)
#define COMP_OR_AFOPG4_Msk           (0x1U << COMP_OR_AFOPG4_Pos)              /*!< 0x00000080 */
#define COMP_OR_AFOPG4               COMP_OR_AFOPG4_Msk
#define COMP_OR_AFOPI1_Pos           (8U)
#define COMP_OR_AFOPI1_Msk           (0x1U << COMP_OR_AFOPI1_Pos)              /*!< 0x00000100 */
#define COMP_OR_AFOPI1               COMP_OR_AFOPI1_Msk
#define COMP_OR_AFOPI4_Pos           (9U)
#define COMP_OR_AFOPI4_Msk           (0x1U << COMP_OR_AFOPI4_Pos)              /*!< 0x00000200 */
#define COMP_OR_AFOPI4               COMP_OR_AFOPI4_Msk
#define COMP_OR_AFOPK2_Pos           (10U)
#define COMP_OR_AFOPK2_Msk           (0x1U << COMP_OR_AFOPK2_Pos)              /*!< 0x00000400 */
#define COMP_OR_AFOPK2               COMP_OR_AFOPK2_Msk

/*!< ******************  Bit definition for COMP_CFGRx register  ********************/
#define COMP_CFGRx_EN_Pos            (0U)
#define COMP_CFGRx_EN_Msk            (0x1U << COMP_CFGRx_EN_Pos)               /*!< 0x00000001 */
#define COMP_CFGRx_EN                COMP_CFGRx_EN_Msk                         /*!< COMPx enable bit                     */
#define COMP_CFGRx_BRGEN_Pos         (1U)
#define COMP_CFGRx_BRGEN_Msk         (0x1U << COMP_CFGRx_BRGEN_Pos)            /*!< 0x00000002 */
#define COMP_CFGRx_BRGEN             COMP_CFGRx_BRGEN_Msk                      /*!< COMPx Scaler bridge enable           */
#define COMP_CFGRx_SCALEN_Pos        (2U)
#define COMP_CFGRx_SCALEN_Msk        (0x1U << COMP_CFGRx_SCALEN_Pos)           /*!< 0x00000004 */
#define COMP_CFGRx_SCALEN            COMP_CFGRx_SCALEN_Msk                     /*!< COMPx Voltage scaler enable bit      */
#define COMP_CFGRx_POLARITY_Pos      (3U)
#define COMP_CFGRx_POLARITY_Msk      (0x1U << COMP_CFGRx_POLARITY_Pos)         /*!< 0x00000008 */
#define COMP_CFGRx_POLARITY          COMP_CFGRx_POLARITY_Msk                   /*!< COMPx  polarity selection bit        */
#define COMP_CFGRx_WINMODE_Pos       (4U)
#define COMP_CFGRx_WINMODE_Msk       (0x1U << COMP_CFGRx_WINMODE_Pos)          /*!< 0x00000010 */
#define COMP_CFGRx_WINMODE           COMP_CFGRx_WINMODE_Msk                    /*!< COMPx Windows mode selection bit     */
#define COMP_CFGRx_ITEN_Pos          (6U)
#define COMP_CFGRx_ITEN_Msk          (0x1U << COMP_CFGRx_ITEN_Pos)             /*!< 0x00000040 */
#define COMP_CFGRx_ITEN              COMP_CFGRx_ITEN_Msk                       /*!< COMPx  interrupt enable              */
#define COMP_CFGRx_HYST_Pos          (8U)
#define COMP_CFGRx_HYST_Msk          (0x3U << COMP_CFGRx_HYST_Pos)             /*!< 0x00000300 */
#define COMP_CFGRx_HYST              COMP_CFGRx_HYST_Msk                       /*!< COMPx  hysteresis selection bits     */
#define COMP_CFGRx_HYST_0            (0x1U << COMP_CFGRx_HYST_Pos)             /*!< 0x00000100 */
#define COMP_CFGRx_HYST_1            (0x2U << COMP_CFGRx_HYST_Pos)             /*!< 0x00000200 */
#define COMP_CFGRx_PWRMODE_Pos       (12U)
#define COMP_CFGRx_PWRMODE_Msk       (0x3U << COMP_CFGRx_PWRMODE_Pos)          /*!< 0x00003000 */
#define COMP_CFGRx_PWRMODE           COMP_CFGRx_PWRMODE_Msk                    /*!< COMPx Power Mode of the comparator   */
#define COMP_CFGRx_PWRMODE_0         (0x1U << COMP_CFGRx_PWRMODE_Pos)          /*!< 0x00001000 */
#define COMP_CFGRx_PWRMODE_1         (0x2U << COMP_CFGRx_PWRMODE_Pos)          /*!< 0x00002000 */
#define COMP_CFGRx_INMSEL_Pos        (16U)
#define COMP_CFGRx_INMSEL_Msk        (0x7U << COMP_CFGRx_INMSEL_Pos)           /*!< 0x00070000 */
#define COMP_CFGRx_INMSEL            COMP_CFGRx_INMSEL_Msk                     /*!< COMPx  input minus selection bit  */
#define COMP_CFGRx_INMSEL_0          (0x1U << COMP_CFGRx_INMSEL_Pos)           /*!< 0x00010000 */
#define COMP_CFGRx_INMSEL_1          (0x2U << COMP_CFGRx_INMSEL_Pos)           /*!< 0x00020000 */
#define COMP_CFGRx_INMSEL_2          (0x4U << COMP_CFGRx_INMSEL_Pos)           /*!< 0x00040000 */
#define COMP_CFGRx_INPSEL_Pos        (20U)
#define COMP_CFGRx_INPSEL_Msk        (0x1U << COMP_CFGRx_INPSEL_Pos)           /*!< 0x00100000 */
#define COMP_CFGRx_INPSEL            COMP_CFGRx_INPSEL_Msk                     /*!< COMPx  input plus selection bit       */
#define COMP_CFGRx_BLANKING_Pos      (24U)
#define COMP_CFGRx_BLANKING_Msk      (0xFU << COMP_CFGRx_BLANKING_Pos)         /*!< 0x0F000000 */
#define COMP_CFGRx_BLANKING          COMP_CFGRx_BLANKING_Msk                   /*!< COMPx  blanking source selection bits */
#define COMP_CFGRx_BLANKING_0        (0x1U << COMP_CFGRx_BLANKING_Pos)         /*!< 0x01000000 */
#define COMP_CFGRx_BLANKING_1        (0x2U << COMP_CFGRx_BLANKING_Pos)         /*!< 0x02000000 */
#define COMP_CFGRx_BLANKING_2        (0x4U << COMP_CFGRx_BLANKING_Pos)         /*!< 0x04000000 */
#define COMP_CFGRx_LOCK_Pos          (31U)
#define COMP_CFGRx_LOCK_Msk          (0x1U << COMP_CFGRx_LOCK_Pos)             /*!< 0x80000000 */
#define COMP_CFGRx_LOCK              COMP_CFGRx_LOCK_Msk                       /*!< COMPx Lock Bit                        */


/******************************************************************************/
/*                                                                            */
/*      Universal Synchronous Asynchronous Receiver Transmitter (USART)       */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for USART_CR1 register  *******************/
#define USART_CR1_UE_Pos             (0U)
#define USART_CR1_UE_Msk             (0x1U << USART_CR1_UE_Pos)                /*!< 0x00000001 */
#define USART_CR1_UE                 USART_CR1_UE_Msk                          /*!< USART Enable */
#define USART_CR1_UESM_Pos           (1U)
#define USART_CR1_UESM_Msk           (0x1U << USART_CR1_UESM_Pos)              /*!< 0x00000002 */
#define USART_CR1_UESM               USART_CR1_UESM_Msk                        /*!< USART Enable in STOP Mode */
#define USART_CR1_RE_Pos             (2U)
#define USART_CR1_RE_Msk             (0x1U << USART_CR1_RE_Pos)                /*!< 0x00000004 */
#define USART_CR1_RE                 USART_CR1_RE_Msk                          /*!< Receiver Enable */
#define USART_CR1_TE_Pos             (3U)
#define USART_CR1_TE_Msk             (0x1U << USART_CR1_TE_Pos)                /*!< 0x00000008 */
#define USART_CR1_TE                 USART_CR1_TE_Msk                          /*!< Transmitter Enable */
#define USART_CR1_IDLEIE_Pos         (4U)
#define USART_CR1_IDLEIE_Msk         (0x1U << USART_CR1_IDLEIE_Pos)            /*!< 0x00000010 */
#define USART_CR1_IDLEIE             USART_CR1_IDLEIE_Msk                      /*!< IDLE Interrupt Enable */
#define USART_CR1_RXNEIE_Pos         (5U)
#define USART_CR1_RXNEIE_Msk         (0x1U << USART_CR1_RXNEIE_Pos)            /*!< 0x00000020 */
#define USART_CR1_RXNEIE             USART_CR1_RXNEIE_Msk                      /*!< RXNE Interrupt Enable */
#define USART_CR1_RXNEIE_RXFNEIE_Pos USART_CR1_RXNEIE_Pos
#define USART_CR1_RXNEIE_RXFNEIE_Msk USART_CR1_RXNEIE_Msk                      /*!< 0x00000020 */
#define USART_CR1_RXNEIE_RXFNEIE     USART_CR1_RXNEIE_Msk                      /*!< RXNE and RX FIFO Not Empty Interrupt Enable */
#define USART_CR1_TCIE_Pos           (6U)
#define USART_CR1_TCIE_Msk           (0x1U << USART_CR1_TCIE_Pos)              /*!< 0x00000040 */
#define USART_CR1_TCIE               USART_CR1_TCIE_Msk                        /*!< Transmission Complete Interrupt Enable */
#define USART_CR1_TXEIE_Pos          (7U)
#define USART_CR1_TXEIE_Msk          (0x1U << USART_CR1_TXEIE_Pos)             /*!< 0x00000080 */
#define USART_CR1_TXEIE              USART_CR1_TXEIE_Msk                       /*!< TXE Interrupt Enable */
#define USART_CR1_TXEIE_TXFNFIE_Pos  USART_CR1_TXEIE_Pos
#define USART_CR1_TXEIE_TXFNFIE_Msk  USART_CR1_TXEIE_Msk                       /*!< 0x00000080 */
#define USART_CR1_TXEIE_TXFNFIE      USART_CR1_TXEIE_Msk                       /*!< TXE and TX FIFO Not Full Interrupt Enable */
#define USART_CR1_PEIE_Pos           (8U)
#define USART_CR1_PEIE_Msk           (0x1U << USART_CR1_PEIE_Pos)              /*!< 0x00000100 */
#define USART_CR1_PEIE               USART_CR1_PEIE_Msk                        /*!< PE Interrupt Enable */
#define USART_CR1_PS_Pos             (9U)
#define USART_CR1_PS_Msk             (0x1U << USART_CR1_PS_Pos)                /*!< 0x00000200 */
#define USART_CR1_PS                 USART_CR1_PS_Msk                          /*!< Parity Selection */
#define USART_CR1_PCE_Pos            (10U)
#define USART_CR1_PCE_Msk            (0x1U << USART_CR1_PCE_Pos)               /*!< 0x00000400 */
#define USART_CR1_PCE                USART_CR1_PCE_Msk                         /*!< Parity Control Enable */
#define USART_CR1_WAKE_Pos           (11U)
#define USART_CR1_WAKE_Msk           (0x1U << USART_CR1_WAKE_Pos)              /*!< 0x00000800 */
#define USART_CR1_WAKE               USART_CR1_WAKE_Msk                        /*!< Receiver Wakeup method */
#define USART_CR1_M_Pos              (12U)
#define USART_CR1_M_Msk              (0x10001U << USART_CR1_M_Pos)             /*!< 0x10001000 */
#define USART_CR1_M                  USART_CR1_M_Msk                           /*!< Word length */
#define USART_CR1_M0_Pos             (12U)
#define USART_CR1_M0_Msk             (0x1U << USART_CR1_M0_Pos)                /*!< 0x00001000 */
#define USART_CR1_M0                 USART_CR1_M0_Msk                          /*!< Word length - Bit 0 */
#define USART_CR1_MME_Pos            (13U)
#define USART_CR1_MME_Msk            (0x1U << USART_CR1_MME_Pos)               /*!< 0x00002000 */
#define USART_CR1_MME                USART_CR1_MME_Msk                         /*!< Mute Mode Enable */
#define USART_CR1_CMIE_Pos           (14U)
#define USART_CR1_CMIE_Msk           (0x1U << USART_CR1_CMIE_Pos)              /*!< 0x00004000 */
#define USART_CR1_CMIE               USART_CR1_CMIE_Msk                        /*!< Character match interrupt enable */
#define USART_CR1_OVER8_Pos          (15U)
#define USART_CR1_OVER8_Msk          (0x1U << USART_CR1_OVER8_Pos)             /*!< 0x00008000 */
#define USART_CR1_OVER8              USART_CR1_OVER8_Msk                       /*!< Oversampling by 8-bit or 16-bit mode */
#define USART_CR1_DEDT_Pos           (16U)
#define USART_CR1_DEDT_Msk           (0x1FU << USART_CR1_DEDT_Pos)             /*!< 0x001F0000 */
#define USART_CR1_DEDT               USART_CR1_DEDT_Msk                        /*!< DEDT[4:0] bits (Driver Enable Deassertion Time) */
#define USART_CR1_DEDT_0             (0x01U << USART_CR1_DEDT_Pos)             /*!< 0x00010000 */
#define USART_CR1_DEDT_1             (0x02U << USART_CR1_DEDT_Pos)             /*!< 0x00020000 */
#define USART_CR1_DEDT_2             (0x04U << USART_CR1_DEDT_Pos)             /*!< 0x00040000 */
#define USART_CR1_DEDT_3             (0x08U << USART_CR1_DEDT_Pos)             /*!< 0x00080000 */
#define USART_CR1_DEDT_4             (0x10U << USART_CR1_DEDT_Pos)             /*!< 0x00100000 */
#define USART_CR1_DEAT_Pos           (21U)
#define USART_CR1_DEAT_Msk           (0x1FU << USART_CR1_DEAT_Pos)             /*!< 0x03E00000 */
#define USART_CR1_DEAT               USART_CR1_DEAT_Msk                        /*!< DEAT[4:0] bits (Driver Enable Assertion Time) */
#define USART_CR1_DEAT_0             (0x01U << USART_CR1_DEAT_Pos)             /*!< 0x00200000 */
#define USART_CR1_DEAT_1             (0x02U << USART_CR1_DEAT_Pos)             /*!< 0x00400000 */
#define USART_CR1_DEAT_2             (0x04U << USART_CR1_DEAT_Pos)             /*!< 0x00800000 */
#define USART_CR1_DEAT_3             (0x08U << USART_CR1_DEAT_Pos)             /*!< 0x01000000 */
#define USART_CR1_DEAT_4             (0x10U << USART_CR1_DEAT_Pos)             /*!< 0x02000000 */
#define USART_CR1_RTOIE_Pos          (26U)
#define USART_CR1_RTOIE_Msk          (0x1U << USART_CR1_RTOIE_Pos)             /*!< 0x04000000 */
#define USART_CR1_RTOIE              USART_CR1_RTOIE_Msk                       /*!< Receive Time Out interrupt enable */
#define USART_CR1_EOBIE_Pos          (27U)
#define USART_CR1_EOBIE_Msk          (0x1U << USART_CR1_EOBIE_Pos)             /*!< 0x08000000 */
#define USART_CR1_EOBIE              USART_CR1_EOBIE_Msk                       /*!< End of Block interrupt enable */
#define USART_CR1_M1_Pos             (28U)
#define USART_CR1_M1_Msk             (0x1U << USART_CR1_M1_Pos)                /*!< 0x10000000 */
#define USART_CR1_M1                 USART_CR1_M1_Msk                          /*!< Word length - Bit 1 */
#define USART_CR1_FIFOEN_Pos         (29U)
#define USART_CR1_FIFOEN_Msk         (0x1U << USART_CR1_FIFOEN_Pos)            /*!< 0x20000000 */
#define USART_CR1_FIFOEN             USART_CR1_FIFOEN_Msk                      /*!< FIFO mode enable */
#define USART_CR1_TXFEIE_Pos         (30U)
#define USART_CR1_TXFEIE_Msk         (0x1U << USART_CR1_TXFEIE_Pos)            /*!< 0x40000000 */
#define USART_CR1_TXFEIE             USART_CR1_TXFEIE_Msk                      /*!< TXFIFO empty interrupt enable */
#define USART_CR1_RXFFIE_Pos         (31U)
#define USART_CR1_RXFFIE_Msk         (0x1U << USART_CR1_RXFFIE_Pos)            /*!< 0x80000000 */
#define USART_CR1_RXFFIE             USART_CR1_RXFFIE_Msk                      /*!< RXFIFO Full interrupt enable */

/******************  Bit definition for USART_CR2 register  *******************/
#define USART_CR2_SLVEN_Pos          (0U)
#define USART_CR2_SLVEN_Msk          (0x1U << USART_CR2_SLVEN_Pos)             /*!< 0x00000001 */
#define USART_CR2_SLVEN              USART_CR2_SLVEN_Msk                       /*!< Synchronous Slave mode enable */
#define USART_CR2_DIS_NSS_Pos        (3U)
#define USART_CR2_DIS_NSS_Msk        (0x1U << USART_CR2_DIS_NSS_Pos)           /*!< 0x00000008 */
#define USART_CR2_DIS_NSS            USART_CR2_DIS_NSS_Msk                     /*!< Slave Select (NSS) pin management */
#define USART_CR2_ADDM7_Pos          (4U)
#define USART_CR2_ADDM7_Msk          (0x1U << USART_CR2_ADDM7_Pos)             /*!< 0x00000010 */
#define USART_CR2_ADDM7              USART_CR2_ADDM7_Msk                       /*!< 7-bit or 4-bit Address Detection */
#define USART_CR2_LBDL_Pos           (5U)
#define USART_CR2_LBDL_Msk           (0x1U << USART_CR2_LBDL_Pos)              /*!< 0x00000020 */
#define USART_CR2_LBDL               USART_CR2_LBDL_Msk                        /*!< LIN Break Detection Length */
#define USART_CR2_LBDIE_Pos          (6U)
#define USART_CR2_LBDIE_Msk          (0x1U << USART_CR2_LBDIE_Pos)             /*!< 0x00000040 */
#define USART_CR2_LBDIE              USART_CR2_LBDIE_Msk                       /*!< LIN Break Detection Interrupt Enable */
#define USART_CR2_LBCL_Pos           (8U)
#define USART_CR2_LBCL_Msk           (0x1U << USART_CR2_LBCL_Pos)              /*!< 0x00000100 */
#define USART_CR2_LBCL               USART_CR2_LBCL_Msk                        /*!< Last Bit Clock pulse */
#define USART_CR2_CPHA_Pos           (9U)
#define USART_CR2_CPHA_Msk           (0x1U << USART_CR2_CPHA_Pos)              /*!< 0x00000200 */
#define USART_CR2_CPHA               USART_CR2_CPHA_Msk                        /*!< Clock Phase */
#define USART_CR2_CPOL_Pos           (10U)
#define USART_CR2_CPOL_Msk           (0x1U << USART_CR2_CPOL_Pos)              /*!< 0x00000400 */
#define USART_CR2_CPOL               USART_CR2_CPOL_Msk                        /*!< Clock Polarity */
#define USART_CR2_CLKEN_Pos          (11U)
#define USART_CR2_CLKEN_Msk          (0x1U << USART_CR2_CLKEN_Pos)             /*!< 0x00000800 */
#define USART_CR2_CLKEN              USART_CR2_CLKEN_Msk                       /*!< Clock Enable */
#define USART_CR2_STOP_Pos           (12U)
#define USART_CR2_STOP_Msk           (0x3U << USART_CR2_STOP_Pos)              /*!< 0x00003000 */
#define USART_CR2_STOP               USART_CR2_STOP_Msk                        /*!< STOP[1:0] bits (STOP bits) */
#define USART_CR2_STOP_0             (0x1U << USART_CR2_STOP_Pos)              /*!< 0x00001000 */
#define USART_CR2_STOP_1             (0x2U << USART_CR2_STOP_Pos)              /*!< 0x00002000 */
#define USART_CR2_LINEN_Pos          (14U)
#define USART_CR2_LINEN_Msk          (0x1U << USART_CR2_LINEN_Pos)             /*!< 0x00004000 */
#define USART_CR2_LINEN              USART_CR2_LINEN_Msk                       /*!< LIN mode enable */
#define USART_CR2_SWAP_Pos           (15U)
#define USART_CR2_SWAP_Msk           (0x1U << USART_CR2_SWAP_Pos)              /*!< 0x00008000 */
#define USART_CR2_SWAP               USART_CR2_SWAP_Msk                        /*!< SWAP TX/RX pins */
#define USART_CR2_RXINV_Pos          (16U)
#define USART_CR2_RXINV_Msk          (0x1U << USART_CR2_RXINV_Pos)             /*!< 0x00010000 */
#define USART_CR2_RXINV              USART_CR2_RXINV_Msk                       /*!< RX pin active level inversion */
#define USART_CR2_TXINV_Pos          (17U)
#define USART_CR2_TXINV_Msk          (0x1U << USART_CR2_TXINV_Pos)             /*!< 0x00020000 */
#define USART_CR2_TXINV              USART_CR2_TXINV_Msk                       /*!< TX pin active level inversion */
#define USART_CR2_DATAINV_Pos        (18U)
#define USART_CR2_DATAINV_Msk        (0x1U << USART_CR2_DATAINV_Pos)           /*!< 0x00040000 */
#define USART_CR2_DATAINV            USART_CR2_DATAINV_Msk                     /*!< Binary data inversion */
#define USART_CR2_MSBFIRST_Pos       (19U)
#define USART_CR2_MSBFIRST_Msk       (0x1U << USART_CR2_MSBFIRST_Pos)          /*!< 0x00080000 */
#define USART_CR2_MSBFIRST           USART_CR2_MSBFIRST_Msk                    /*!< Most Significant Bit First */
#define USART_CR2_ABREN_Pos          (20U)
#define USART_CR2_ABREN_Msk          (0x1U << USART_CR2_ABREN_Pos)             /*!< 0x00100000 */
#define USART_CR2_ABREN              USART_CR2_ABREN_Msk                       /*!< Auto Baud-Rate Enable*/
#define USART_CR2_ABRMODE_Pos        (21U)
#define USART_CR2_ABRMODE_Msk        (0x3U << USART_CR2_ABRMODE_Pos)           /*!< 0x00600000 */
#define USART_CR2_ABRMODE            USART_CR2_ABRMODE_Msk                     /*!< ABRMOD[1:0] bits (Auto Baud-Rate Mode) */
#define USART_CR2_ABRMODE_0          (0x1U << USART_CR2_ABRMODE_Pos)           /*!< 0x00200000 */
#define USART_CR2_ABRMODE_1          (0x2U << USART_CR2_ABRMODE_Pos)           /*!< 0x00400000 */
#define USART_CR2_RTOEN_Pos          (23U)
#define USART_CR2_RTOEN_Msk          (0x1U << USART_CR2_RTOEN_Pos)             /*!< 0x00800000 */
#define USART_CR2_RTOEN              USART_CR2_RTOEN_Msk                       /*!< Receiver Time-Out enable */
#define USART_CR2_ADD_Pos            (24U)
#define USART_CR2_ADD_Msk            (0xFFU << USART_CR2_ADD_Pos)              /*!< 0xFF000000 */
#define USART_CR2_ADD                USART_CR2_ADD_Msk                         /*!< Address of the USART node */

/******************  Bit definition for USART_CR3 register  *******************/
#define USART_CR3_EIE_Pos            (0U)
#define USART_CR3_EIE_Msk            (0x1U << USART_CR3_EIE_Pos)               /*!< 0x00000001 */
#define USART_CR3_EIE                USART_CR3_EIE_Msk                         /*!< Error Interrupt Enable */
#define USART_CR3_IREN_Pos           (1U)
#define USART_CR3_IREN_Msk           (0x1U << USART_CR3_IREN_Pos)              /*!< 0x00000002 */
#define USART_CR3_IREN               USART_CR3_IREN_Msk                        /*!< IrDA mode Enable */
#define USART_CR3_IRLP_Pos           (2U)
#define USART_CR3_IRLP_Msk           (0x1U << USART_CR3_IRLP_Pos)              /*!< 0x00000004 */
#define USART_CR3_IRLP               USART_CR3_IRLP_Msk                        /*!< IrDA Low-Power */
#define USART_CR3_HDSEL_Pos          (3U)
#define USART_CR3_HDSEL_Msk          (0x1U << USART_CR3_HDSEL_Pos)             /*!< 0x00000008 */
#define USART_CR3_HDSEL              USART_CR3_HDSEL_Msk                       /*!< Half-Duplex Selection */
#define USART_CR3_NACK_Pos           (4U)
#define USART_CR3_NACK_Msk           (0x1U << USART_CR3_NACK_Pos)              /*!< 0x00000010 */
#define USART_CR3_NACK               USART_CR3_NACK_Msk                        /*!< SmartCard NACK enable */
#define USART_CR3_SCEN_Pos           (5U)
#define USART_CR3_SCEN_Msk           (0x1U << USART_CR3_SCEN_Pos)              /*!< 0x00000020 */
#define USART_CR3_SCEN               USART_CR3_SCEN_Msk                        /*!< SmartCard mode enable */
#define USART_CR3_DMAR_Pos           (6U)
#define USART_CR3_DMAR_Msk           (0x1U << USART_CR3_DMAR_Pos)              /*!< 0x00000040 */
#define USART_CR3_DMAR               USART_CR3_DMAR_Msk                        /*!< DMA Enable Receiver */
#define USART_CR3_DMAT_Pos           (7U)
#define USART_CR3_DMAT_Msk           (0x1U << USART_CR3_DMAT_Pos)              /*!< 0x00000080 */
#define USART_CR3_DMAT               USART_CR3_DMAT_Msk                        /*!< DMA Enable Transmitter */
#define USART_CR3_RTSE_Pos           (8U)
#define USART_CR3_RTSE_Msk           (0x1U << USART_CR3_RTSE_Pos)              /*!< 0x00000100 */
#define USART_CR3_RTSE               USART_CR3_RTSE_Msk                        /*!< RTS Enable */
#define USART_CR3_CTSE_Pos           (9U)
#define USART_CR3_CTSE_Msk           (0x1U << USART_CR3_CTSE_Pos)              /*!< 0x00000200 */
#define USART_CR3_CTSE               USART_CR3_CTSE_Msk                        /*!< CTS Enable */
#define USART_CR3_CTSIE_Pos          (10U)
#define USART_CR3_CTSIE_Msk          (0x1U << USART_CR3_CTSIE_Pos)             /*!< 0x00000400 */
#define USART_CR3_CTSIE              USART_CR3_CTSIE_Msk                       /*!< CTS Interrupt Enable */
#define USART_CR3_ONEBIT_Pos         (11U)
#define USART_CR3_ONEBIT_Msk         (0x1U << USART_CR3_ONEBIT_Pos)            /*!< 0x00000800 */
#define USART_CR3_ONEBIT             USART_CR3_ONEBIT_Msk                      /*!< One sample bit method enable */
#define USART_CR3_OVRDIS_Pos         (12U)
#define USART_CR3_OVRDIS_Msk         (0x1U << USART_CR3_OVRDIS_Pos)            /*!< 0x00001000 */
#define USART_CR3_OVRDIS             USART_CR3_OVRDIS_Msk                      /*!< Overrun Disable */
#define USART_CR3_DDRE_Pos           (13U)
#define USART_CR3_DDRE_Msk           (0x1U << USART_CR3_DDRE_Pos)              /*!< 0x00002000 */
#define USART_CR3_DDRE               USART_CR3_DDRE_Msk                        /*!< DMA Disable on Reception Error */
#define USART_CR3_DEM_Pos            (14U)
#define USART_CR3_DEM_Msk            (0x1U << USART_CR3_DEM_Pos)               /*!< 0x00004000 */
#define USART_CR3_DEM                USART_CR3_DEM_Msk                         /*!< Driver Enable Mode */
#define USART_CR3_DEP_Pos            (15U)
#define USART_CR3_DEP_Msk            (0x1U << USART_CR3_DEP_Pos)               /*!< 0x00008000 */
#define USART_CR3_DEP                USART_CR3_DEP_Msk                         /*!< Driver Enable Polarity Selection */
#define USART_CR3_SCARCNT_Pos        (17U)
#define USART_CR3_SCARCNT_Msk        (0x7U << USART_CR3_SCARCNT_Pos)           /*!< 0x000E0000 */
#define USART_CR3_SCARCNT            USART_CR3_SCARCNT_Msk                     /*!< SCARCNT[2:0] bits (SmartCard Auto-Retry Count) */
#define USART_CR3_SCARCNT_0          (0x1U << USART_CR3_SCARCNT_Pos)           /*!< 0x00020000 */
#define USART_CR3_SCARCNT_1          (0x2U << USART_CR3_SCARCNT_Pos)           /*!< 0x00040000 */
#define USART_CR3_SCARCNT_2          (0x4U << USART_CR3_SCARCNT_Pos)           /*!< 0x00080000 */
#define USART_CR3_WUS_Pos            (20U)
#define USART_CR3_WUS_Msk            (0x3U << USART_CR3_WUS_Pos)               /*!< 0x00300000 */
#define USART_CR3_WUS                USART_CR3_WUS_Msk                         /*!< WUS[1:0] bits (Wake UP Interrupt Flag Selection) */
#define USART_CR3_WUS_0              (0x1U << USART_CR3_WUS_Pos)               /*!< 0x00100000 */
#define USART_CR3_WUS_1              (0x2U << USART_CR3_WUS_Pos)               /*!< 0x00200000 */
#define USART_CR3_WUFIE_Pos          (22U)
#define USART_CR3_WUFIE_Msk          (0x1U << USART_CR3_WUFIE_Pos)             /*!< 0x00400000 */
#define USART_CR3_WUFIE              USART_CR3_WUFIE_Msk                       /*!< Wake Up Interrupt Enable */
#define USART_CR3_TXFTIE_Pos         (23U)
#define USART_CR3_TXFTIE_Msk         (0x1U << USART_CR3_TXFTIE_Pos)            /*!< 0x00800000 */
#define USART_CR3_TXFTIE             USART_CR3_TXFTIE_Msk                      /*!< TXFIFO threshold interrupt enable */
#define USART_CR3_TCBGTIE_Pos        (24U)
#define USART_CR3_TCBGTIE_Msk        (0x1U << USART_CR3_TCBGTIE_Pos)           /*!< 0x01000000 */
#define USART_CR3_TCBGTIE            USART_CR3_TCBGTIE_Msk                     /*!< Transmission Complete Before Guard Time Interrupt Enable */
#define USART_CR3_RXFTCFG_Pos        (25U)
#define USART_CR3_RXFTCFG_Msk        (0x7U << USART_CR3_RXFTCFG_Pos)           /*!< 0x0E000000 */
#define USART_CR3_RXFTCFG            USART_CR3_RXFTCFG_Msk                     /*!< RXFIFO FIFO threshold configuration */
#define USART_CR3_RXFTCFG_0          (0x1U << USART_CR3_RXFTCFG_Pos)           /*!< 0x02000000 */
#define USART_CR3_RXFTCFG_1          (0x2U << USART_CR3_RXFTCFG_Pos)           /*!< 0x04000000 */
#define USART_CR3_RXFTCFG_2          (0x4U << USART_CR3_RXFTCFG_Pos)           /*!< 0x08000000 */
#define USART_CR3_RXFTIE_Pos         (28U)
#define USART_CR3_RXFTIE_Msk         (0x1U << USART_CR3_RXFTIE_Pos)            /*!< 0x10000000 */
#define USART_CR3_RXFTIE             USART_CR3_RXFTIE_Msk                      /*!< RXFIFO threshold interrupt enable */
#define USART_CR3_TXFTCFG_Pos        (29U)
#define USART_CR3_TXFTCFG_Msk        (0x7U << USART_CR3_TXFTCFG_Pos)           /*!< 0xE0000000 */
#define USART_CR3_TXFTCFG            USART_CR3_TXFTCFG_Msk                     /*!< TXFIFO threshold configuration */
#define USART_CR3_TXFTCFG_0          (0x1U << USART_CR3_TXFTCFG_Pos)           /*!< 0x20000000 */
#define USART_CR3_TXFTCFG_1          (0x2U << USART_CR3_TXFTCFG_Pos)           /*!< 0x40000000 */
#define USART_CR3_TXFTCFG_2          (0x4U << USART_CR3_TXFTCFG_Pos)           /*!< 0x80000000 */

/******************  Bit definition for USART_BRR register  *******************/
#define USART_BRR_LPUART_Pos         (0U)
#define USART_BRR_LPUART_Msk         (0xFFFFFU << USART_BRR_LPUART_Pos)        /*!< 0x000FFFFF */
#define USART_BRR_LPUART             USART_BRR_LPUART_Msk                      /*!< LPUART Baud rate register [19:0] */
#define USART_BRR_BRR_Pos            (0U)
#define USART_BRR_BRR_Msk            (0xFFFFU << USART_BRR_BRR_Pos)            /*!< 0x0000FFFF */
#define USART_BRR_BRR                USART_BRR_BRR_Msk                         /*!< USART Baud rate register [15:0] */

/******************  Bit definition for USART_GTPR register  ******************/
#define USART_GTPR_PSC_Pos           (0U)
#define USART_GTPR_PSC_Msk           (0xFFU << USART_GTPR_PSC_Pos)             /*!< 0x000000FF */
#define USART_GTPR_PSC               USART_GTPR_PSC_Msk                        /*!< PSC[7:0] bits (Prescaler value) */
#define USART_GTPR_GT_Pos            (8U)
#define USART_GTPR_GT_Msk            (0xFFU << USART_GTPR_GT_Pos)              /*!< 0x0000FF00 */
#define USART_GTPR_GT                USART_GTPR_GT_Msk                         /*!< GT[7:0] bits (Guard time value) */

/*******************  Bit definition for USART_RTOR register  *****************/
#define USART_RTOR_RTO_Pos           (0U)
#define USART_RTOR_RTO_Msk           (0xFFFFFFU << USART_RTOR_RTO_Pos)         /*!< 0x00FFFFFF */
#define USART_RTOR_RTO               USART_RTOR_RTO_Msk                        /*!< Receiver Time Out Value */
#define USART_RTOR_BLEN_Pos          (24U)
#define USART_RTOR_BLEN_Msk          (0xFFU << USART_RTOR_BLEN_Pos)            /*!< 0xFF000000 */
#define USART_RTOR_BLEN              USART_RTOR_BLEN_Msk                       /*!< Block Length */

/*******************  Bit definition for USART_RQR register  ******************/
#define USART_RQR_ABRRQ_Pos          (0U)
#define USART_RQR_ABRRQ_Msk          (0x1U << USART_RQR_ABRRQ_Pos)             /*!< 0x00000001 */
#define USART_RQR_ABRRQ              USART_RQR_ABRRQ_Msk                       /*!< Auto-Baud Rate Request */
#define USART_RQR_SBKRQ_Pos          (1U)
#define USART_RQR_SBKRQ_Msk          (0x1U << USART_RQR_SBKRQ_Pos)             /*!< 0x00000002 */
#define USART_RQR_SBKRQ              USART_RQR_SBKRQ_Msk                       /*!< Send Break Request */
#define USART_RQR_MMRQ_Pos           (2U)
#define USART_RQR_MMRQ_Msk           (0x1U << USART_RQR_MMRQ_Pos)              /*!< 0x00000004 */
#define USART_RQR_MMRQ               USART_RQR_MMRQ_Msk                        /*!< Mute Mode Request */
#define USART_RQR_RXFRQ_Pos          (3U)
#define USART_RQR_RXFRQ_Msk          (0x1U << USART_RQR_RXFRQ_Pos)             /*!< 0x00000008 */
#define USART_RQR_RXFRQ              USART_RQR_RXFRQ_Msk                       /*!< Receive Data flush Request */
#define USART_RQR_TXFRQ_Pos          (4U)
#define USART_RQR_TXFRQ_Msk          (0x1U << USART_RQR_TXFRQ_Pos)             /*!< 0x00000010 */
#define USART_RQR_TXFRQ              USART_RQR_TXFRQ_Msk                       /*!< Transmit data flush Request */

/*******************  Bit definition for USART_ISR register  ******************/
#define USART_ISR_PE_Pos             (0U)
#define USART_ISR_PE_Msk             (0x1U << USART_ISR_PE_Pos)                /*!< 0x00000001 */
#define USART_ISR_PE                 USART_ISR_PE_Msk                          /*!< Parity Error */
#define USART_ISR_FE_Pos             (1U)
#define USART_ISR_FE_Msk             (0x1U << USART_ISR_FE_Pos)                /*!< 0x00000002 */
#define USART_ISR_FE                 USART_ISR_FE_Msk                          /*!< Framing Error */
#define USART_ISR_NE_Pos             (2U)
#define USART_ISR_NE_Msk             (0x1U << USART_ISR_NE_Pos)                /*!< 0x00000004 */
#define USART_ISR_NE                 USART_ISR_NE_Msk                          /*!< Noise detected Flag */
#define USART_ISR_ORE_Pos            (3U)
#define USART_ISR_ORE_Msk            (0x1U << USART_ISR_ORE_Pos)               /*!< 0x00000008 */
#define USART_ISR_ORE                USART_ISR_ORE_Msk                         /*!< OverRun Error */
#define USART_ISR_IDLE_Pos           (4U)
#define USART_ISR_IDLE_Msk           (0x1U << USART_ISR_IDLE_Pos)              /*!< 0x00000010 */
#define USART_ISR_IDLE               USART_ISR_IDLE_Msk                        /*!< IDLE line detected */
#define USART_ISR_RXNE_Pos           (5U)
#define USART_ISR_RXNE_Msk           (0x1U << USART_ISR_RXNE_Pos)              /*!< 0x00000020 */
#define USART_ISR_RXNE               USART_ISR_RXNE_Msk                        /*!< Read Data Register Not Empty */
#define USART_ISR_RXNE_RXFNE_Pos     USART_ISR_RXNE_Pos
#define USART_ISR_RXNE_RXFNE_Msk     USART_ISR_RXNE_Msk                        /*!< 0x00000020 */
#define USART_ISR_RXNE_RXFNE         USART_ISR_RXNE_Msk                        /*!< Read Data Register or RX FIFO Not Empty */
#define USART_ISR_TC_Pos             (6U)
#define USART_ISR_TC_Msk             (0x1U << USART_ISR_TC_Pos)                /*!< 0x00000040 */
#define USART_ISR_TC                 USART_ISR_TC_Msk                          /*!< Transmission Complete */
#define USART_ISR_TXE_Pos            (7U)
#define USART_ISR_TXE_Msk            (0x1U << USART_ISR_TXE_Pos)               /*!< 0x00000080 */
#define USART_ISR_TXE                USART_ISR_TXE_Msk                         /*!< Transmit Data Register Empty */
#define USART_ISR_TXE_TXFNF_Pos      USART_ISR_TXE_Pos
#define USART_ISR_TXE_TXFNF_Msk      USART_ISR_TXE_Msk                       /*!< 0x00000080 */
#define USART_ISR_TXE_TXFNF          USART_ISR_TXE_Msk                       /*!< Transmit Data Register Empty or TX FIFO Not Full Flag */
#define USART_ISR_LBDF_Pos           (8U)
#define USART_ISR_LBDF_Msk           (0x1U << USART_ISR_LBDF_Pos)              /*!< 0x00000100 */
#define USART_ISR_LBDF               USART_ISR_LBDF_Msk                        /*!< LIN Break Detection Flag */
#define USART_ISR_CTSIF_Pos          (9U)
#define USART_ISR_CTSIF_Msk          (0x1U << USART_ISR_CTSIF_Pos)             /*!< 0x00000200 */
#define USART_ISR_CTSIF              USART_ISR_CTSIF_Msk                       /*!< CTS interrupt flag */
#define USART_ISR_CTS_Pos            (10U)
#define USART_ISR_CTS_Msk            (0x1U << USART_ISR_CTS_Pos)               /*!< 0x00000400 */
#define USART_ISR_CTS                USART_ISR_CTS_Msk                         /*!< CTS flag */
#define USART_ISR_RTOF_Pos           (11U)
#define USART_ISR_RTOF_Msk           (0x1U << USART_ISR_RTOF_Pos)              /*!< 0x00000800 */
#define USART_ISR_RTOF               USART_ISR_RTOF_Msk                        /*!< Receiver Time Out */
#define USART_ISR_EOBF_Pos           (12U)
#define USART_ISR_EOBF_Msk           (0x1U << USART_ISR_EOBF_Pos)              /*!< 0x00001000 */
#define USART_ISR_EOBF               USART_ISR_EOBF_Msk                        /*!< End Of Block Flag */
#define USART_ISR_UDR_Pos            (13U)
#define USART_ISR_UDR_Msk            (0x1U << USART_ISR_UDR_Pos)               /*!< 0x00002000 */
#define USART_ISR_UDR                USART_ISR_UDR_Msk                         /*!< SPI slave underrun error flag */
#define USART_ISR_ABRE_Pos           (14U)
#define USART_ISR_ABRE_Msk           (0x1U << USART_ISR_ABRE_Pos)              /*!< 0x00004000 */
#define USART_ISR_ABRE               USART_ISR_ABRE_Msk                        /*!< Auto-Baud Rate Error */
#define USART_ISR_ABRF_Pos           (15U)
#define USART_ISR_ABRF_Msk           (0x1U << USART_ISR_ABRF_Pos)              /*!< 0x00008000 */
#define USART_ISR_ABRF               USART_ISR_ABRF_Msk                        /*!< Auto-Baud Rate Flag */
#define USART_ISR_BUSY_Pos           (16U)
#define USART_ISR_BUSY_Msk           (0x1U << USART_ISR_BUSY_Pos)              /*!< 0x00010000 */
#define USART_ISR_BUSY               USART_ISR_BUSY_Msk                        /*!< Busy Flag */
#define USART_ISR_CMF_Pos            (17U)
#define USART_ISR_CMF_Msk            (0x1U << USART_ISR_CMF_Pos)               /*!< 0x00020000 */
#define USART_ISR_CMF                USART_ISR_CMF_Msk                         /*!< Character Match Flag */
#define USART_ISR_SBKF_Pos           (18U)
#define USART_ISR_SBKF_Msk           (0x1U << USART_ISR_SBKF_Pos)              /*!< 0x00040000 */
#define USART_ISR_SBKF               USART_ISR_SBKF_Msk                        /*!< Send Break Flag */
#define USART_ISR_RWU_Pos            (19U)
#define USART_ISR_RWU_Msk            (0x1U << USART_ISR_RWU_Pos)               /*!< 0x00080000 */
#define USART_ISR_RWU                USART_ISR_RWU_Msk                         /*!< Receive Wake Up from mute mode Flag */
#define USART_ISR_WUF_Pos            (20U)
#define USART_ISR_WUF_Msk            (0x1U << USART_ISR_WUF_Pos)               /*!< 0x00100000 */
#define USART_ISR_WUF                USART_ISR_WUF_Msk                         /*!< Wake Up from stop mode Flag */
#define USART_ISR_TEACK_Pos          (21U)
#define USART_ISR_TEACK_Msk          (0x1U << USART_ISR_TEACK_Pos)             /*!< 0x00200000 */
#define USART_ISR_TEACK              USART_ISR_TEACK_Msk                       /*!< Transmit Enable Acknowledge Flag */
#define USART_ISR_REACK_Pos          (22U)
#define USART_ISR_REACK_Msk          (0x1U << USART_ISR_REACK_Pos)             /*!< 0x00400000 */
#define USART_ISR_REACK              USART_ISR_REACK_Msk                       /*!< Receive Enable Acknowledge Flag */
#define USART_ISR_TXFE_Pos           (23U)
#define USART_ISR_TXFE_Msk           (0x1U << USART_ISR_TXFE_Pos)              /*!< 0x00800000 */
#define USART_ISR_TXFE               USART_ISR_TXFE_Msk                        /*!< TXFIFO Empty */
#define USART_ISR_RXFF_Pos           (24U)
#define USART_ISR_RXFF_Msk           (0x1U << USART_ISR_RXFF_Pos)              /*!< 0x01000000 */
#define USART_ISR_RXFF               USART_ISR_RXFF_Msk                        /*!< RXFIFO Full */
#define USART_ISR_TCBGT_Pos          (25U)
#define USART_ISR_TCBGT_Msk          (0x1U << USART_ISR_TCBGT_Pos)             /*!< 0x02000000 */
#define USART_ISR_TCBGT              USART_ISR_TCBGT_Msk                       /*!< Transmission Complete Before Guard Time completion */
#define USART_ISR_RXFT_Pos           (26U)
#define USART_ISR_RXFT_Msk           (0x1U << USART_ISR_RXFT_Pos)              /*!< 0x04000000 */
#define USART_ISR_RXFT               USART_ISR_RXFT_Msk                        /*!< RXFIFO threshold flag */
#define USART_ISR_TXFT_Pos           (27U)
#define USART_ISR_TXFT_Msk           (0x1U << USART_ISR_TXFT_Pos)              /*!< 0x08000000 */
#define USART_ISR_TXFT               USART_ISR_TXFT_Msk                        /*!< TXFIFO threshold flag */

/*******************  Bit definition for USART_ICR register  ******************/
#define USART_ICR_PECF_Pos           (0U)
#define USART_ICR_PECF_Msk           (0x1U << USART_ICR_PECF_Pos)              /*!< 0x00000001 */
#define USART_ICR_PECF               USART_ICR_PECF_Msk                        /*!< Parity Error Clear Flag */
#define USART_ICR_FECF_Pos           (1U)
#define USART_ICR_FECF_Msk           (0x1U << USART_ICR_FECF_Pos)              /*!< 0x00000002 */
#define USART_ICR_FECF               USART_ICR_FECF_Msk                        /*!< Framing Error Clear Flag */
#define USART_ICR_NECF_Pos           (2U)
#define USART_ICR_NECF_Msk           (0x1U << USART_ICR_NECF_Pos)              /*!< 0x00000004 */
#define USART_ICR_NECF               USART_ICR_NECF_Msk                        /*!< Noise detected Clear Flag */
#define USART_ICR_ORECF_Pos          (3U)
#define USART_ICR_ORECF_Msk          (0x1U << USART_ICR_ORECF_Pos)             /*!< 0x00000008 */
#define USART_ICR_ORECF              USART_ICR_ORECF_Msk                       /*!< OverRun Error Clear Flag */
#define USART_ICR_IDLECF_Pos         (4U)
#define USART_ICR_IDLECF_Msk         (0x1U << USART_ICR_IDLECF_Pos)            /*!< 0x00000010 */
#define USART_ICR_IDLECF             USART_ICR_IDLECF_Msk                      /*!< IDLE line detected Clear Flag */
#define USART_ICR_TXFECF_Pos         (5U)
#define USART_ICR_TXFECF_Msk         (0x1U << USART_ICR_TXFECF_Pos)            /*!< 0x00000020 */
#define USART_ICR_TXFECF             USART_ICR_TXFECF_Msk                      /*!< TXFIFO empty Clear flag */
#define USART_ICR_TCCF_Pos           (6U)
#define USART_ICR_TCCF_Msk           (0x1U << USART_ICR_TCCF_Pos)              /*!< 0x00000040 */
#define USART_ICR_TCCF               USART_ICR_TCCF_Msk                        /*!< Transmission Complete Clear Flag */
#define USART_ICR_TCBGTCF_Pos        (7U)
#define USART_ICR_TCBGTCF_Msk        (0x1U << USART_ICR_TCBGTCF_Pos)           /*!< 0x00000080 */
#define USART_ICR_TCBGTCF            USART_ICR_TCBGTCF_Msk                     /*!< Transmission Complete Before Guard Time Clear Flag */
#define USART_ICR_LBDCF_Pos          (8U)
#define USART_ICR_LBDCF_Msk          (0x1U << USART_ICR_LBDCF_Pos)             /*!< 0x00000100 */
#define USART_ICR_LBDCF              USART_ICR_LBDCF_Msk                       /*!< LIN Break Detection Clear Flag */
#define USART_ICR_CTSCF_Pos          (9U)
#define USART_ICR_CTSCF_Msk          (0x1U << USART_ICR_CTSCF_Pos)             /*!< 0x00000200 */
#define USART_ICR_CTSCF              USART_ICR_CTSCF_Msk                       /*!< CTS Interrupt Clear Flag */
#define USART_ICR_RTOCF_Pos          (11U)
#define USART_ICR_RTOCF_Msk          (0x1U << USART_ICR_RTOCF_Pos)             /*!< 0x00000800 */
#define USART_ICR_RTOCF              USART_ICR_RTOCF_Msk                       /*!< Receiver Time Out Clear Flag */
#define USART_ICR_EOBCF_Pos          (12U)
#define USART_ICR_EOBCF_Msk          (0x1U << USART_ICR_EOBCF_Pos)             /*!< 0x00001000 */
#define USART_ICR_EOBCF              USART_ICR_EOBCF_Msk                       /*!< End Of Block Clear Flag */
#define USART_ICR_UDRCF_Pos          (13U)
#define USART_ICR_UDRCF_Msk          (0x1U << USART_ICR_UDRCF_Pos)             /*!< 0x00002000 */
#define USART_ICR_UDRCF              USART_ICR_UDRCF_Msk                       /*!< SPI Slave Underrun Clear Flag */
#define USART_ICR_CMCF_Pos           (17U)
#define USART_ICR_CMCF_Msk           (0x1U << USART_ICR_CMCF_Pos)              /*!< 0x00020000 */
#define USART_ICR_CMCF               USART_ICR_CMCF_Msk                        /*!< Character Match Clear Flag */
#define USART_ICR_WUCF_Pos           (20U)
#define USART_ICR_WUCF_Msk           (0x1U << USART_ICR_WUCF_Pos)              /*!< 0x00100000 */
#define USART_ICR_WUCF               USART_ICR_WUCF_Msk                        /*!< Wake Up from stop mode Clear Flag */

/*******************  Bit definition for USART_RDR register  ******************/
#define USART_RDR_RDR_Pos            (0U)
#define USART_RDR_RDR_Msk            (0x1FF << USART_RDR_RDR_Pos)              /*!< 0x000001FF */
#define USART_RDR_RDR                 USART_RDR_RDR_Msk                        /*!< RDR[8:0] bits (Receive Data value) */

/*******************  Bit definition for USART_TDR register  ******************/
#define USART_TDR_TDR_Pos            (0U)
#define USART_TDR_TDR_Msk            (0x1FF << USART_TDR_TDR_Pos)              /*!< 0x000001FF */
#define USART_TDR_TDR                USART_TDR_TDR_Msk                         /*!< TDR[8:0] bits (Transmit Data value) */

/*******************  Bit definition for USART_PRESC register  ****************/
#define USART_PRESC_PRESCALER_Pos    (0U)
#define USART_PRESC_PRESCALER_Msk    (0xFU << USART_PRESC_PRESCALER_Pos)       /*!< 0x0000000F */
#define USART_PRESC_PRESCALER        USART_PRESC_PRESCALER_Msk                 /*!< PRESCALER[3:0] bits (Clock prescaler) */
#define USART_PRESC_PRESCALER_0      (0x1U << USART_PRESC_PRESCALER_Pos)       /*!< 0x00000001 */
#define USART_PRESC_PRESCALER_1      (0x2U << USART_PRESC_PRESCALER_Pos)       /*!< 0x00000002 */
#define USART_PRESC_PRESCALER_2      (0x4U << USART_PRESC_PRESCALER_Pos)       /*!< 0x00000004 */
#define USART_PRESC_PRESCALER_3      (0x8U << USART_PRESC_PRESCALER_Pos)       /*!< 0x00000008 */

/**********************  Bit definition for USART_HWCFGR2 register  ***************/
#define USART_HWCFGR2_CFG1_Pos  (0U)
#define USART_HWCFGR2_CFG1_Msk  (0xFU << USART_HWCFGR2_CFG1_Pos)          /*!< 0x0000000F */
#define USART_HWCFGR2_CFG1      USART_HWCFGR2_CFG1_Msk                    /*!< HW CFG1 */
#define USART_HWCFGR2_CFG2_Pos  (4U)
#define USART_HWCFGR2_CFG2_Msk  (0xFU << USART_HWCFGR2_CFG2_Pos)          /*!< 0x000000F0 */
#define USART_HWCFGR2_CFG2      USART_HWCFGR2_CFG2_Msk                    /*!< HW CFG2 */

/**********************  Bit definition for USART_HWCFGR1 register  ***************/
#define USART_HWCFGR1_CFG1_Pos  (0U)
#define USART_HWCFGR1_CFG1_Msk  (0xFU << USART_HWCFGR1_CFG1_Pos)          /*!< 0x0000000F */
#define USART_HWCFGR1_CFG1      USART_HWCFGR1_CFG1_Msk                    /*!< HW CFG1 */
#define USART_HWCFGR1_CFG2_Pos  (4U)
#define USART_HWCFGR1_CFG2_Msk  (0xFU << USART_HWCFGR1_CFG2_Pos)          /*!< 0x000000F0 */
#define USART_HWCFGR1_CFG2      USART_HWCFGR1_CFG2_Msk                    /*!< HW CFG2 */
#define USART_HWCFGR1_CFG3_Pos  (8U)
#define USART_HWCFGR1_CFG3_Msk  (0xFU << USART_HWCFGR1_CFG3_Pos)          /*!< 0x00000F00 */
#define USART_HWCFGR1_CFG3      USART_HWCFGR1_CFG3_Msk                    /*!< HW CFG3 */
#define USART_HWCFGR1_CFG4_Pos  (12U)
#define USART_HWCFGR1_CFG4_Msk  (0xFU << USART_HWCFGR1_CFG4_Pos)          /*!< 0x0000F000 */
#define USART_HWCFGR1_CFG4      USART_HWCFGR1_CFG4_Msk                    /*!< HW CFG4 */
#define USART_HWCFGR1_CFG5_Pos  (16U)
#define USART_HWCFGR1_CFG5_Msk  (0xFU << USART_HWCFGR1_CFG5_Pos)          /*!< 0x000F0000 */
#define USART_HWCFGR1_CFG5      USART_HWCFGR1_CFG5_Msk                    /*!< HW CFG5 */
#define USART_HWCFGR1_CFG6_Pos  (20U)
#define USART_HWCFGR1_CFG6_Msk  (0xFU << USART_HWCFGR1_CFG6_Pos)          /*!< 0x00F00000 */
#define USART_HWCFGR1_CFG6      USART_HWCFGR1_CFG6_Msk                    /*!< HW CFG6 */
#define USART_HWCFGR1_CFG7_Pos  (24U)
#define USART_HWCFGR1_CFG7_Msk  (0xFU << USART_HWCFGR1_CFG7_Pos)          /*!< 0x0F000000 */
#define USART_HWCFGR1_CFG7      USART_HWCFGR1_CFG7_Msk                    /*!< HW CFG7 */
#define USART_HWCFGR1_CFG8_Pos  (28U)
#define USART_HWCFGR1_CFG8_Msk  (0xFU << USART_HWCFGR1_CFG8_Pos)          /*!< 0xF0000000 */
#define USART_HWCFGR1_CFG8      USART_HWCFGR1_CFG8_Msk                    /*!< HW CFG8 */

/**********************  Bit definition for USART_VERR register  *****************/
#define USART_VERR_MINREV_Pos      (0U)
#define USART_VERR_MINREV_Msk      (0xFU << USART_VERR_MINREV_Pos)               /*!< 0x0000000F */
#define USART_VERR_MINREV          USART_VERR_MINREV_Msk                         /*!< Minor Revision number */
#define USART_VERR_MAJREV_Pos      (4U)
#define USART_VERR_MAJREV_Msk      (0xFU << USART_VERR_MAJREV_Pos)               /*!< 0x000000F0 */
#define USART_VERR_MAJREV          USART_VERR_MAJREV_Msk                         /*!< Major Revision number */

/**********************  Bit definition for USART_IPIDR register  ****************/
#define USART_IPIDR_IPID_Pos       (0U)
#define USART_IPIDR_IPID_Msk       (0xFFFFFFFFU << USART_IPIDR_IPID_Pos)         /*!< 0xFFFFFFFF */
#define USART_IPIDR_IPID           USART_IPIDR_IPID_Msk                          /*!< IP Identification */

/**********************  Bit definition for USART_SIDR register  *****************/
#define USART_SIDR_SID_Pos         (0U)
#define USART_SIDR_SID_Msk         (0xFFFFFFFFU << USART_SIDR_SID_Pos)           /*!< 0xFFFFFFFF */
#define USART_SIDR_SID             USART_SIDR_SID_Msk                            /*!< IP size identification */

/******************************************************************************/
/*                                                                            */
/*           Single Wire Protocol Master Interface (SWPMI)                    */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for SWPMI_CR register   ********************/
#define SWPMI_CR_RXDMA           ((uint16_t)0x0001)                            /*!<Reception DMA enable                                 */
#define SWPMI_CR_TXDMA           ((uint16_t)0x0002)                            /*!<Transmission DMA enable                              */
#define SWPMI_CR_RXMODE          ((uint16_t)0x0004)                            /*!<Reception buffering mode                             */
#define SWPMI_CR_TXMODE          ((uint16_t)0x0008)                            /*!<Transmission buffering mode                          */
#define SWPMI_CR_LPBK            ((uint16_t)0x0010)                            /*!<Loopback mode enable                                 */
#define SWPMI_CR_SWPACT          ((uint16_t)0x0020)                            /*!<Single wire protocol master interface activate       */
#define SWPMI_CR_DEACT           ((uint16_t)0x0400)                            /*!<Single wire protocol master interface deactivate     */
#define SWPMI_CR_SWPEN           ((uint16_t)0x0800)                            /*!<Single wire protocol master transceiver enable       */

/*******************  Bit definition for SWPMI_BRR register  ********************/
#define SWPMI_BRR_BR             ((uint16_t)0x003F)                            /*!<BR[5:0] bits (Bitrate prescaler) */

/*******************  Bit definition for SWPMI_ISR register  ********************/
#define SWPMI_ISR_RXBFF          ((uint16_t)0x0001)                            /*!<Receive buffer full flag        */
#define SWPMI_ISR_TXBEF          ((uint16_t)0x0002)                            /*!<Transmit buffer empty flag      */
#define SWPMI_ISR_RXBERF         ((uint16_t)0x0004)                            /*!<Receive CRC error flag          */
#define SWPMI_ISR_RXOVRF         ((uint16_t)0x0008)                            /*!<Receive overrun error flag      */
#define SWPMI_ISR_TXUNRF         ((uint16_t)0x0010)                            /*!<Transmit underrun error flag    */
#define SWPMI_ISR_RXNE           ((uint16_t)0x0020)                            /*!<Receive data register not empty */
#define SWPMI_ISR_TXE            ((uint16_t)0x0040)                            /*!<Transmit data register empty    */
#define SWPMI_ISR_TCF            ((uint16_t)0x0080)                            /*!<Transfer complete flag          */
#define SWPMI_ISR_SRF            ((uint16_t)0x0100)                            /*!<Slave resume flag               */
#define SWPMI_ISR_SUSP           ((uint16_t)0x0200)                            /*!<SUSPEND flag                    */
#define SWPMI_ISR_DEACTF         ((uint16_t)0x0400)                            /*!<DEACTIVATED flag                */
#define SWPMI_ISR_RDYF           ((uint16_t)0x0800)                            /*!<Transceiver ready flag          */

/*******************  Bit definition for SWPMI_ICR register  ********************/
#define SWPMI_ICR_CRXBFF         ((uint16_t)0x0001)                            /*!<Clear receive buffer full flag       */
#define SWPMI_ICR_CTXBEF         ((uint16_t)0x0002)                            /*!<Clear transmit buffer empty flag     */
#define SWPMI_ICR_CRXBERF        ((uint16_t)0x0004)                            /*!<Clear receive CRC error flag         */
#define SWPMI_ICR_CRXOVRF        ((uint16_t)0x0008)                            /*!<Clear receive overrun error flag     */
#define SWPMI_ICR_CTXUNRF        ((uint16_t)0x0010)                            /*!<Clear transmit underrun error flag   */
#define SWPMI_ICR_CTCF           ((uint16_t)0x0080)                            /*!<Clear transfer complete flag         */
#define SWPMI_ICR_CSRF           ((uint16_t)0x0100)                            /*!<Clear slave resume flag              */
#define SWPMI_ICR_CRDYF          ((uint16_t)0x0800)                            /*!<Clear transceiver ready flag         */

/*******************  Bit definition for SWPMI_IER register  ********************/
#define SWPMI_IER_RXBFIE         ((uint16_t)0x0001)                            /*!<Receive buffer full interrupt enable        */
#define SWPMI_IER_TXBEIE         ((uint16_t)0x0002)                            /*!<Transmit buffer empty interrupt enable      */
#define SWPMI_IER_RXBERIE        ((uint16_t)0x0004)                            /*!<Receive CRC error interrupt enable          */
#define SWPMI_IER_RXOVRIE        ((uint16_t)0x0008)                            /*!<Receive overrun error interrupt enable      */
#define SWPMI_IER_TXUNRIE        ((uint16_t)0x0010)                            /*!<Transmit underrun error interrupt enable    */
#define SWPMI_IER_RIE            ((uint16_t)0x0020)                            /*!<Receive interrupt enable                    */
#define SWPMI_IER_TIE            ((uint16_t)0x0040)                            /*!<Transmit interrupt enable                   */
#define SWPMI_IER_TCIE           ((uint16_t)0x0080)                            /*!<Transmit complete interrupt enable          */
#define SWPMI_IER_SRIE           ((uint16_t)0x0100)                            /*!<Slave resume interrupt enable               */
#define SWPMI_IER_RDYIE          ((uint16_t)0x0800)                            /*!<Transceiver ready interrupt enable          */

/*******************  Bit definition for SWPMI_RFL register  ********************/
#define SWPMI_RFL_RFL            ((uint16_t)0x001F)                            /*!<RFL[4:0] bits (Receive Frame length) */
#define SWPMI_RFL_RFL_0_1        ((uint16_t)0x0003)                            /*!<RFL[1:0] bits (number of relevant bytes for the last SWPMI_RDR register read.) */

/*******************  Bit definition for SWPMI_TDR register  ********************/
#define SWPMI_TDR_TD_Pos         (0U)
#define SWPMI_TDR_TD_Msk         (0xFFFFFFFFU << SWPMI_TDR_TD_Pos)             /*!< 0xFFFFFFFF */
#define SWPMI_TDR_TD             SWPMI_TDR_TD_Msk                              /*!<Transmit Data Register         */

/*******************  Bit definition for SWPMI_RDR register  ********************/
#define SWPMI_RDR_RD_Pos         (0U)
#define SWPMI_RDR_RD_Msk         (0xFFFFFFFFU << SWPMI_RDR_RD_Pos)             /*!< 0xFFFFFFFF */
#define SWPMI_RDR_RD             SWPMI_RDR_RD_Msk                              /*!<Recive Data Register           */


/*******************  Bit definition for SWPMI_OR register  ********************/
#define SWPMI_OR_TBYP            ((uint16_t)0x0001)                            /*!<SWP Transceiver Bypass */
#define SWPMI_OR_CLASS           ((uint16_t)0x0002)                            /*!<SWP CLASS selection */

/******************************************************************************/
/*                                                                            */
/*                            Window WATCHDOG                                 */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for WWDG_CR register  ********************/
#define WWDG_CR_T_Pos           (0U)
#define WWDG_CR_T_Msk           (0x7FU << WWDG_CR_T_Pos)                       /*!< 0x0000007F */
#define WWDG_CR_T               WWDG_CR_T_Msk                                  /*!<T[6:0] bits (7-Bit counter (MSB to LSB)) */
#define WWDG_CR_T_0             (0x01U << WWDG_CR_T_Pos)                       /*!< 0x00000001 */
#define WWDG_CR_T_1             (0x02U << WWDG_CR_T_Pos)                       /*!< 0x00000002 */
#define WWDG_CR_T_2             (0x04U << WWDG_CR_T_Pos)                       /*!< 0x00000004 */
#define WWDG_CR_T_3             (0x08U << WWDG_CR_T_Pos)                       /*!< 0x00000008 */
#define WWDG_CR_T_4             (0x10U << WWDG_CR_T_Pos)                       /*!< 0x00000010 */
#define WWDG_CR_T_5             (0x20U << WWDG_CR_T_Pos)                       /*!< 0x00000020 */
#define WWDG_CR_T_6             (0x40U << WWDG_CR_T_Pos)                       /*!< 0x00000040 */

#define WWDG_CR_WDGA_Pos        (7U)
#define WWDG_CR_WDGA_Msk        (0x1U << WWDG_CR_WDGA_Pos)                     /*!< 0x00000080 */
#define WWDG_CR_WDGA            WWDG_CR_WDGA_Msk                               /*!<Activation bit */

/*******************  Bit definition for WWDG_CFR register  *******************/
#define WWDG_CFR_W_Pos          (0U)
#define WWDG_CFR_W_Msk          (0x7FU << WWDG_CFR_W_Pos)                      /*!< 0x0000007F */
#define WWDG_CFR_W              WWDG_CFR_W_Msk                                 /*!<W[6:0] bits (7-bit window value) */
#define WWDG_CFR_W_0            (0x01U << WWDG_CFR_W_Pos)                      /*!< 0x00000001 */
#define WWDG_CFR_W_1            (0x02U << WWDG_CFR_W_Pos)                      /*!< 0x00000002 */
#define WWDG_CFR_W_2            (0x04U << WWDG_CFR_W_Pos)                      /*!< 0x00000004 */
#define WWDG_CFR_W_3            (0x08U << WWDG_CFR_W_Pos)                      /*!< 0x00000008 */
#define WWDG_CFR_W_4            (0x10U << WWDG_CFR_W_Pos)                      /*!< 0x00000010 */
#define WWDG_CFR_W_5            (0x20U << WWDG_CFR_W_Pos)                      /*!< 0x00000020 */
#define WWDG_CFR_W_6            (0x40U << WWDG_CFR_W_Pos)                      /*!< 0x00000040 */

#define WWDG_CFR_WDGTB_Pos      (11U)
#define WWDG_CFR_WDGTB_Msk      (0x7U << WWDG_CFR_WDGTB_Pos)                   /*!< 0x00003800 */
#define WWDG_CFR_WDGTB          WWDG_CFR_WDGTB_Msk                             /*!<WDGTB[2:0] bits (Timer Base) */
#define WWDG_CFR_WDGTB_0        (0x1U << WWDG_CFR_WDGTB_Pos)                   /*!< 0x00000800 */
#define WWDG_CFR_WDGTB_1        (0x2U << WWDG_CFR_WDGTB_Pos)                   /*!< 0x00001000 */
#define WWDG_CFR_WDGTB_2        (0x4U << WWDG_CFR_WDGTB_Pos)                   /*!< 0x00002000 */

#define WWDG_CFR_EWI_Pos        (9U)
#define WWDG_CFR_EWI_Msk        (0x1U << WWDG_CFR_EWI_Pos)                     /*!< 0x00000200 */
#define WWDG_CFR_EWI            WWDG_CFR_EWI_Msk                               /*!<Early Wakeup Interrupt */

/*******************  Bit definition for WWDG_SR register  ********************/
#define WWDG_SR_EWIF_Pos        (0U)
#define WWDG_SR_EWIF_Msk        (0x1U << WWDG_SR_EWIF_Pos)                     /*!< 0x00000001 */
#define WWDG_SR_EWIF            WWDG_SR_EWIF_Msk                               /*!<Early Wakeup Interrupt Flag */

/*******************  Bit definition for WWDG_HWCFGR register  ***************/
#define WWDG_HWCFGR_PREDIV_Pos  (0U)
#define WWDG_HWCFGR_PREDIV_Msk  (0xFFFFU << WWDG_HWCFGR_PREDIV_Pos)            /*!< 0x0000FFFF */
#define WWDG_HWCFGR_PREDIV      WWDG_HWCFGR_PREDIV_Msk                         /*!< Watchdog clock prescaler */

/*******************  Bit definition for WWDG_VERR register  *****************/
#define WWDG_VERR_MINREV_Pos      (0U)
#define WWDG_VERR_MINREV_Msk      (0xFU << WWDG_VERR_MINREV_Pos)               /*!< 0x0000000F */
#define WWDG_VERR_MINREV          WWDG_VERR_MINREV_Msk                         /*!< Minor Revision number */
#define WWDG_VERR_MAJREV_Pos      (4U)
#define WWDG_VERR_MAJREV_Msk      (0xFU << WWDG_VERR_MAJREV_Pos)               /*!< 0x000000F0 */
#define WWDG_VERR_MAJREV          WWDG_VERR_MAJREV_Msk                         /*!< Major Revision number */

/*******************  Bit definition for WWDG_IPIDR register  ****************/
#define WWDG_IPIDR_ID_Pos       (0U)
#define WWDG_IPIDR_ID_Msk       (0xFFFFFFFFU << WWDG_IPIDR_ID_Pos)             /*!< 0xFFFFFFFF */
#define WWDG_IPIDR_ID           WWDG_IPIDR_ID_Msk                              /*!< IP Identification */

/**********************  Bit definition for WWDG_SIDR register  *****************/
#define WWDG_SIDR_SID_Pos         (0U)
#define WWDG_SIDR_SID_Msk         (0xFFFFFFFFU << WWDG_SIDR_SID_Pos)           /*!< 0xFFFFFFFF */
#define WWDG_SIDR_SID             WWDG_SIDR_SID_Msk                            /*!< IP size identification */

/******************************************************************************/
/*                                                                            */
/*                                MDIOS                                        */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for MDIOS_CR register  *******************/
#define MDIOS_CR_EN_Pos                (0U)
#define MDIOS_CR_EN_Msk                (0x1U << MDIOS_CR_EN_Pos)               /*!< 0x00000001 */
#define MDIOS_CR_EN                    MDIOS_CR_EN_Msk                         /*!<  MDIOS slave peripheral enable */
#define MDIOS_CR_WRIE_Pos              (1U)
#define MDIOS_CR_WRIE_Msk              (0x1U << MDIOS_CR_WRIE_Pos)             /*!< 0x00000002 */
#define MDIOS_CR_WRIE                  MDIOS_CR_WRIE_Msk                       /*!<  MDIOS slave register write interrupt enable. */
#define MDIOS_CR_RDIE_Pos              (2U)
#define MDIOS_CR_RDIE_Msk              (0x1U << MDIOS_CR_RDIE_Pos)             /*!< 0x00000004 */
#define MDIOS_CR_RDIE                  MDIOS_CR_RDIE_Msk                       /*!<  MDIOS slave register read interrupt enable. */
#define MDIOS_CR_EIE_Pos               (3U)
#define MDIOS_CR_EIE_Msk               (0x1U << MDIOS_CR_EIE_Pos)              /*!< 0x00000008 */
#define MDIOS_CR_EIE                   MDIOS_CR_EIE_Msk                        /*!<  MDIOS slave register error interrupt enable. */
#define MDIOS_CR_DPC_Pos               (7U)
#define MDIOS_CR_DPC_Msk               (0x1U << MDIOS_CR_DPC_Pos)              /*!< 0x00000080 */
#define MDIOS_CR_DPC                   MDIOS_CR_DPC_Msk                        /*!<  MDIOS slave disable preamble check. */
#define MDIOS_CR_PORT_ADDRESS_Pos      (8U)
#define MDIOS_CR_PORT_ADDRESS_Msk      (0x1FU << MDIOS_CR_PORT_ADDRESS_Pos)    /*!< 0x00001F00 */
#define MDIOS_CR_PORT_ADDRESS          MDIOS_CR_PORT_ADDRESS_Msk               /*!<  MDIOS slave port address mask. */
#define MDIOS_CR_PORT_ADDRESS_0        (0x01U << MDIOS_CR_PORT_ADDRESS_Pos)    /*!< 0x00000100 */
#define MDIOS_CR_PORT_ADDRESS_1        (0x02U << MDIOS_CR_PORT_ADDRESS_Pos)    /*!< 0x00000200 */
#define MDIOS_CR_PORT_ADDRESS_2        (0x04U << MDIOS_CR_PORT_ADDRESS_Pos)    /*!< 0x00000400 */
#define MDIOS_CR_PORT_ADDRESS_3        (0x08U << MDIOS_CR_PORT_ADDRESS_Pos)    /*!< 0x00000800 */
#define MDIOS_CR_PORT_ADDRESS_4        (0x10U << MDIOS_CR_PORT_ADDRESS_Pos)    /*!< 0x00001000 */

/********************  Bit definition for MDIOS_SR register  *******************/
#define MDIOS_SR_PERF_Pos              (0U)
#define MDIOS_SR_PERF_Msk              (0x1U << MDIOS_SR_PERF_Pos)             /*!< 0x00000001 */
#define MDIOS_SR_PERF                  MDIOS_SR_PERF_Msk                       /*!<  MDIOS slave turnaround error flag*/
#define MDIOS_SR_SERF_Pos              (1U)
#define MDIOS_SR_SERF_Msk              (0x1U << MDIOS_SR_SERF_Pos)             /*!< 0x00000002 */
#define MDIOS_SR_SERF                  MDIOS_SR_SERF_Msk                       /*!<  MDIOS slave start error flag */
#define MDIOS_SR_TERF_Pos              (2U)
#define MDIOS_SR_TERF_Msk              (0x1U << MDIOS_SR_TERF_Pos)             /*!< 0x00000004 */
#define MDIOS_SR_TERF                  MDIOS_SR_TERF_Msk                       /*!<  MDIOS slave preamble error flag */

/********************  Bit definition for MDIOS_CLRFR register  *******************/
#define MDIOS_SR_CPERF_Pos             (0U)
#define MDIOS_SR_CPERF_Msk             (0x1U << MDIOS_SR_CPERF_Pos)            /*!< 0x00000001 */
#define MDIOS_SR_CPERF                 MDIOS_SR_CPERF_Msk                      /*!<  MDIOS slave Clear the turnaround error flag */
#define MDIOS_SR_CSERF_Pos             (1U)
#define MDIOS_SR_CSERF_Msk             (0x1U << MDIOS_SR_CSERF_Pos)            /*!< 0x00000002 */
#define MDIOS_SR_CSERF                 MDIOS_SR_CSERF_Msk                      /*!<  MDIOS slave Clear the start error flag */
#define MDIOS_SR_CTERF_Pos             (2U)
#define MDIOS_SR_CTERF_Msk             (0x1U << MDIOS_SR_CTERF_Pos)            /*!< 0x00000004 */
#define MDIOS_SR_CTERF                 MDIOS_SR_CTERF_Msk                      /*!<  MDIOS slave Clear the preamble error flag */

/**********************  Bit definition for MDIOS_HWCFGR register  ***************/
#define MDIOS_HWCFGR_NBREG_Pos  (0U)
#define MDIOS_HWCFGR_NBREG_Msk  (0xFFU << MDIOS_HWCFGR_NBREG_Pos)                /*!< 0x000000FF */
#define MDIOS_HWCFGR_NBREG      MDIOS_HWCFGR_NBREG_Msk                           /*!< IP configuration number of registers */

/**********************  Bit definition for MDIOS_VERR register  *****************/
#define MDIOS_VERR_MINREV_Pos      (0U)
#define MDIOS_VERR_MINREV_Msk      (0xFU << MDIOS_VERR_MINREV_Pos)               /*!< 0x0000000F */
#define MDIOS_VERR_MINREV          MDIOS_VERR_MINREV_Msk                         /*!< Minor Revision number */
#define MDIOS_VERR_MAJREV_Pos      (4U)
#define MDIOS_VERR_MAJREV_Msk      (0xFU << MDIOS_VERR_MAJREV_Pos)               /*!< 0x000000F0 */
#define MDIOS_VERR_MAJREV          MDIOS_VERR_MAJREV_Msk                         /*!< Major Revision number */

/**********************  Bit definition for MDIOS_IPIDR register  ****************/
#define MDIOS_IPIDR_IPID_Pos       (0U)
#define MDIOS_IPIDR_IPID_Msk       (0xFFFFFFFFU << MDIOS_IPIDR_IPID_Pos)         /*!< 0xFFFFFFFF */
#define MDIOS_IPIDR_IPID           MDIOS_IPIDR_IPID_Msk                          /*!< IP Identification */

/**********************  Bit definition for MDIOS_SIDR register  *****************/
#define MDIOS_SIDR_SID_Pos         (0U)
#define MDIOS_SIDR_SID_Msk         (0xFFFFFFFFU << MDIOS_SIDR_SID_Pos)           /*!< 0xFFFFFFFF */
#define MDIOS_SIDR_SID             MDIOS_SIDR_SID_Msk                            /*!< IP size identification */

/******************************************************************************/
/*                                                                            */
/*                                       USB_OTG                              */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition forUSB_OTG_GOTGCTL register  ********************/
#define USB_OTG_GOTGCTL_SRQSCS_Pos               (0U)
#define USB_OTG_GOTGCTL_SRQSCS_Msk               (0x1UL << USB_OTG_GOTGCTL_SRQSCS_Pos) /*!< 0x00000001 */
#define USB_OTG_GOTGCTL_SRQSCS                   USB_OTG_GOTGCTL_SRQSCS_Msk    /*!< Session request success */
#define USB_OTG_GOTGCTL_SRQ_Pos                  (1U)
#define USB_OTG_GOTGCTL_SRQ_Msk                  (0x1UL << USB_OTG_GOTGCTL_SRQ_Pos) /*!< 0x00000002 */
#define USB_OTG_GOTGCTL_SRQ                      USB_OTG_GOTGCTL_SRQ_Msk       /*!< Session request */
#define USB_OTG_GOTGCTL_VBVALOEN_Pos             (2U)
#define USB_OTG_GOTGCTL_VBVALOEN_Msk             (0x1UL << USB_OTG_GOTGCTL_VBVALOEN_Pos) /*!< 0x00000004 */
#define USB_OTG_GOTGCTL_VBVALOEN                 USB_OTG_GOTGCTL_VBVALOEN_Msk  /*!< VBUS valid override enable */
#define USB_OTG_GOTGCTL_VBVALOVAL_Pos            (3U)
#define USB_OTG_GOTGCTL_VBVALOVAL_Msk            (0x1UL << USB_OTG_GOTGCTL_VBVALOVAL_Pos) /*!< 0x00000008 */
#define USB_OTG_GOTGCTL_VBVALOVAL                USB_OTG_GOTGCTL_VBVALOVAL_Msk /*!< VBUS valid override value */
#define USB_OTG_GOTGCTL_AVALOEN_Pos              (4U)
#define USB_OTG_GOTGCTL_AVALOEN_Msk              (0x1UL << USB_OTG_GOTGCTL_AVALOEN_Pos) /*!< 0x00000010 */
#define USB_OTG_GOTGCTL_AVALOEN                  USB_OTG_GOTGCTL_AVALOEN_Msk   /*!< A-peripheral session valid override enable */
#define USB_OTG_GOTGCTL_AVALOVAL_Pos             (5U)
#define USB_OTG_GOTGCTL_AVALOVAL_Msk             (0x1UL << USB_OTG_GOTGCTL_AVALOVAL_Pos) /*!< 0x00000020 */
#define USB_OTG_GOTGCTL_AVALOVAL                 USB_OTG_GOTGCTL_AVALOVAL_Msk  /*!< A-peripheral session valid override value */
#define USB_OTG_GOTGCTL_BVALOEN_Pos              (6U)
#define USB_OTG_GOTGCTL_BVALOEN_Msk              (0x1UL << USB_OTG_GOTGCTL_BVALOEN_Pos) /*!< 0x00000040 */
#define USB_OTG_GOTGCTL_BVALOEN                  USB_OTG_GOTGCTL_BVALOEN_Msk   /*!< B-peripheral session valid override enable */
#define USB_OTG_GOTGCTL_BVALOVAL_Pos             (7U)
#define USB_OTG_GOTGCTL_BVALOVAL_Msk             (0x1UL << USB_OTG_GOTGCTL_BVALOVAL_Pos) /*!< 0x00000080 */
#define USB_OTG_GOTGCTL_BVALOVAL                 USB_OTG_GOTGCTL_BVALOVAL_Msk  /*!< B-peripheral session valid override value  */
#define USB_OTG_GOTGCTL_HNGSCS_Pos               (8U)
#define USB_OTG_GOTGCTL_HNGSCS_Msk               (0x1UL << USB_OTG_GOTGCTL_HNGSCS_Pos) /*!< 0x00000100 */
#define USB_OTG_GOTGCTL_HNGSCS                   USB_OTG_GOTGCTL_HNGSCS_Msk    /*!< Host set HNP enable */
#define USB_OTG_GOTGCTL_HNPRQ_Pos                (9U)
#define USB_OTG_GOTGCTL_HNPRQ_Msk                (0x1UL << USB_OTG_GOTGCTL_HNPRQ_Pos) /*!< 0x00000200 */
#define USB_OTG_GOTGCTL_HNPRQ                    USB_OTG_GOTGCTL_HNPRQ_Msk     /*!< HNP request */
#define USB_OTG_GOTGCTL_HSHNPEN_Pos              (10U)
#define USB_OTG_GOTGCTL_HSHNPEN_Msk              (0x1UL << USB_OTG_GOTGCTL_HSHNPEN_Pos) /*!< 0x00000400 */
#define USB_OTG_GOTGCTL_HSHNPEN                  USB_OTG_GOTGCTL_HSHNPEN_Msk   /*!< Host set HNP enable */
#define USB_OTG_GOTGCTL_DHNPEN_Pos               (11U)
#define USB_OTG_GOTGCTL_DHNPEN_Msk               (0x1UL << USB_OTG_GOTGCTL_DHNPEN_Pos) /*!< 0x00000800 */
#define USB_OTG_GOTGCTL_DHNPEN                   USB_OTG_GOTGCTL_DHNPEN_Msk    /*!< Device HNP enabled */
#define USB_OTG_GOTGCTL_EHEN_Pos                 (12U)
#define USB_OTG_GOTGCTL_EHEN_Msk                 (0x1UL << USB_OTG_GOTGCTL_EHEN_Pos) /*!< 0x00001000 */
#define USB_OTG_GOTGCTL_EHEN                     USB_OTG_GOTGCTL_EHEN_Msk      /*!< Embedded host enable */
#define USB_OTG_GOTGCTL_CIDSTS_Pos               (16U)
#define USB_OTG_GOTGCTL_CIDSTS_Msk               (0x1UL << USB_OTG_GOTGCTL_CIDSTS_Pos) /*!< 0x00010000 */
#define USB_OTG_GOTGCTL_CIDSTS                   USB_OTG_GOTGCTL_CIDSTS_Msk    /*!< Connector ID status */
#define USB_OTG_GOTGCTL_DBCT_Pos                 (17U)
#define USB_OTG_GOTGCTL_DBCT_Msk                 (0x1UL << USB_OTG_GOTGCTL_DBCT_Pos) /*!< 0x00020000 */
#define USB_OTG_GOTGCTL_DBCT                     USB_OTG_GOTGCTL_DBCT_Msk      /*!< Long/short debounce time */
#define USB_OTG_GOTGCTL_ASVLD_Pos                (18U)
#define USB_OTG_GOTGCTL_ASVLD_Msk                (0x1UL << USB_OTG_GOTGCTL_ASVLD_Pos) /*!< 0x00040000 */
#define USB_OTG_GOTGCTL_ASVLD                    USB_OTG_GOTGCTL_ASVLD_Msk     /*!< A-session valid  */
#define USB_OTG_GOTGCTL_BSESVLD_Pos              (19U)
#define USB_OTG_GOTGCTL_BSESVLD_Msk              (0x1UL << USB_OTG_GOTGCTL_BSESVLD_Pos) /*!< 0x00080000 */
#define USB_OTG_GOTGCTL_BSESVLD                  USB_OTG_GOTGCTL_BSESVLD_Msk   /*!< B-session valid */
#define USB_OTG_GOTGCTL_OTGVER_Pos               (20U)
#define USB_OTG_GOTGCTL_OTGVER_Msk               (0x1UL << USB_OTG_GOTGCTL_OTGVER_Pos) /*!< 0x00100000 */
#define USB_OTG_GOTGCTL_OTGVER                   USB_OTG_GOTGCTL_OTGVER_Msk    /*!< OTG version  */

/********************  Bit definition forUSB_OTG_HCFG register  ********************/

#define USB_OTG_HCFG_FSLSPCS_Pos                 (0U)
#define USB_OTG_HCFG_FSLSPCS_Msk                 (0x3UL << USB_OTG_HCFG_FSLSPCS_Pos) /*!< 0x00000003 */
#define USB_OTG_HCFG_FSLSPCS                     USB_OTG_HCFG_FSLSPCS_Msk      /*!< FS/LS PHY clock select  */
#define USB_OTG_HCFG_FSLSPCS_0                   (0x1UL << USB_OTG_HCFG_FSLSPCS_Pos) /*!< 0x00000001 */
#define USB_OTG_HCFG_FSLSPCS_1                   (0x2UL << USB_OTG_HCFG_FSLSPCS_Pos) /*!< 0x00000002 */
#define USB_OTG_HCFG_FSLSS_Pos                   (2U)
#define USB_OTG_HCFG_FSLSS_Msk                   (0x1UL << USB_OTG_HCFG_FSLSS_Pos) /*!< 0x00000004 */
#define USB_OTG_HCFG_FSLSS                       USB_OTG_HCFG_FSLSS_Msk        /*!< FS- and LS-only support */

/********************  Bit definition forUSB_OTG_DCFG register  ********************/

#define USB_OTG_DCFG_DSPD_Pos                    (0U)
#define USB_OTG_DCFG_DSPD_Msk                    (0x3UL << USB_OTG_DCFG_DSPD_Pos) /*!< 0x00000003 */
#define USB_OTG_DCFG_DSPD                        USB_OTG_DCFG_DSPD_Msk         /*!< Device speed */
#define USB_OTG_DCFG_DSPD_0                      (0x1UL << USB_OTG_DCFG_DSPD_Pos) /*!< 0x00000001 */
#define USB_OTG_DCFG_DSPD_1                      (0x2UL << USB_OTG_DCFG_DSPD_Pos) /*!< 0x00000002 */
#define USB_OTG_DCFG_NZLSOHSK_Pos                (2U)
#define USB_OTG_DCFG_NZLSOHSK_Msk                (0x1UL << USB_OTG_DCFG_NZLSOHSK_Pos) /*!< 0x00000004 */
#define USB_OTG_DCFG_NZLSOHSK                    USB_OTG_DCFG_NZLSOHSK_Msk     /*!< Nonzero-length status OUT handshake */

#define USB_OTG_DCFG_DAD_Pos                     (4U)
#define USB_OTG_DCFG_DAD_Msk                     (0x7FUL << USB_OTG_DCFG_DAD_Pos) /*!< 0x000007F0 */
#define USB_OTG_DCFG_DAD                         USB_OTG_DCFG_DAD_Msk          /*!< Device address */
#define USB_OTG_DCFG_DAD_0                       (0x01UL << USB_OTG_DCFG_DAD_Pos) /*!< 0x00000010 */
#define USB_OTG_DCFG_DAD_1                       (0x02UL << USB_OTG_DCFG_DAD_Pos) /*!< 0x00000020 */
#define USB_OTG_DCFG_DAD_2                       (0x04UL << USB_OTG_DCFG_DAD_Pos) /*!< 0x00000040 */
#define USB_OTG_DCFG_DAD_3                       (0x08UL << USB_OTG_DCFG_DAD_Pos) /*!< 0x00000080 */
#define USB_OTG_DCFG_DAD_4                       (0x10UL << USB_OTG_DCFG_DAD_Pos) /*!< 0x00000100 */
#define USB_OTG_DCFG_DAD_5                       (0x20UL << USB_OTG_DCFG_DAD_Pos) /*!< 0x00000200 */
#define USB_OTG_DCFG_DAD_6                       (0x40UL << USB_OTG_DCFG_DAD_Pos) /*!< 0x00000400 */

#define USB_OTG_DCFG_PFIVL_Pos                   (11U)
#define USB_OTG_DCFG_PFIVL_Msk                   (0x3UL << USB_OTG_DCFG_PFIVL_Pos) /*!< 0x00001800 */
#define USB_OTG_DCFG_PFIVL                       USB_OTG_DCFG_PFIVL_Msk        /*!< Periodic (micro)frame interval */
#define USB_OTG_DCFG_PFIVL_0                     (0x1UL << USB_OTG_DCFG_PFIVL_Pos) /*!< 0x00000800 */
#define USB_OTG_DCFG_PFIVL_1                     (0x2UL << USB_OTG_DCFG_PFIVL_Pos) /*!< 0x00001000 */

#define USB_OTG_DCFG_PERSCHIVL_Pos               (24U)
#define USB_OTG_DCFG_PERSCHIVL_Msk               (0x3UL << USB_OTG_DCFG_PERSCHIVL_Pos) /*!< 0x03000000 */
#define USB_OTG_DCFG_PERSCHIVL                   USB_OTG_DCFG_PERSCHIVL_Msk    /*!< Periodic scheduling interval */
#define USB_OTG_DCFG_PERSCHIVL_0                 (0x1UL << USB_OTG_DCFG_PERSCHIVL_Pos) /*!< 0x01000000 */
#define USB_OTG_DCFG_PERSCHIVL_1                 (0x2UL << USB_OTG_DCFG_PERSCHIVL_Pos) /*!< 0x02000000 */

/********************  Bit definition forUSB_OTG_PCGCR register  ********************/
#define USB_OTG_PCGCR_STPPCLK_Pos                (0U)
#define USB_OTG_PCGCR_STPPCLK_Msk                (0x1UL << USB_OTG_PCGCR_STPPCLK_Pos) /*!< 0x00000001 */
#define USB_OTG_PCGCR_STPPCLK                    USB_OTG_PCGCR_STPPCLK_Msk     /*!< Stop PHY clock */
#define USB_OTG_PCGCR_GATEHCLK_Pos               (1U)
#define USB_OTG_PCGCR_GATEHCLK_Msk               (0x1UL << USB_OTG_PCGCR_GATEHCLK_Pos) /*!< 0x00000002 */
#define USB_OTG_PCGCR_GATEHCLK                   USB_OTG_PCGCR_GATEHCLK_Msk    /*!< Gate HCLK */
#define USB_OTG_PCGCR_PHYSUSP_Pos                (4U)
#define USB_OTG_PCGCR_PHYSUSP_Msk                (0x1UL << USB_OTG_PCGCR_PHYSUSP_Pos) /*!< 0x00000010 */
#define USB_OTG_PCGCR_PHYSUSP                    USB_OTG_PCGCR_PHYSUSP_Msk     /*!< PHY suspended */

/********************  Bit definition forUSB_OTG_GOTGINT register  ********************/
#define USB_OTG_GOTGINT_SEDET_Pos                (2U)
#define USB_OTG_GOTGINT_SEDET_Msk                (0x1UL << USB_OTG_GOTGINT_SEDET_Pos) /*!< 0x00000004 */
#define USB_OTG_GOTGINT_SEDET                    USB_OTG_GOTGINT_SEDET_Msk     /*!< Session end detected                   */
#define USB_OTG_GOTGINT_SRSSCHG_Pos              (8U)
#define USB_OTG_GOTGINT_SRSSCHG_Msk              (0x1UL << USB_OTG_GOTGINT_SRSSCHG_Pos) /*!< 0x00000100 */
#define USB_OTG_GOTGINT_SRSSCHG                  USB_OTG_GOTGINT_SRSSCHG_Msk   /*!< Session request success status change  */
#define USB_OTG_GOTGINT_HNSSCHG_Pos              (9U)
#define USB_OTG_GOTGINT_HNSSCHG_Msk              (0x1UL << USB_OTG_GOTGINT_HNSSCHG_Pos) /*!< 0x00000200 */
#define USB_OTG_GOTGINT_HNSSCHG                  USB_OTG_GOTGINT_HNSSCHG_Msk   /*!< Host negotiation success status change */
#define USB_OTG_GOTGINT_HNGDET_Pos               (17U)
#define USB_OTG_GOTGINT_HNGDET_Msk               (0x1UL << USB_OTG_GOTGINT_HNGDET_Pos) /*!< 0x00020000 */
#define USB_OTG_GOTGINT_HNGDET                   USB_OTG_GOTGINT_HNGDET_Msk    /*!< Host negotiation detected              */
#define USB_OTG_GOTGINT_ADTOCHG_Pos              (18U)
#define USB_OTG_GOTGINT_ADTOCHG_Msk              (0x1UL << USB_OTG_GOTGINT_ADTOCHG_Pos) /*!< 0x00040000 */
#define USB_OTG_GOTGINT_ADTOCHG                  USB_OTG_GOTGINT_ADTOCHG_Msk   /*!< A-device timeout change                */
#define USB_OTG_GOTGINT_DBCDNE_Pos               (19U)
#define USB_OTG_GOTGINT_DBCDNE_Msk               (0x1UL << USB_OTG_GOTGINT_DBCDNE_Pos) /*!< 0x00080000 */
#define USB_OTG_GOTGINT_DBCDNE                   USB_OTG_GOTGINT_DBCDNE_Msk    /*!< Debounce done                          */

/********************  Bit definition forUSB_OTG_DCTL register  ********************/
#define USB_OTG_DCTL_RWUSIG_Pos                  (0U)
#define USB_OTG_DCTL_RWUSIG_Msk                  (0x1UL << USB_OTG_DCTL_RWUSIG_Pos) /*!< 0x00000001 */
#define USB_OTG_DCTL_RWUSIG                      USB_OTG_DCTL_RWUSIG_Msk       /*!< Remote wakeup signaling */
#define USB_OTG_DCTL_SDIS_Pos                    (1U)
#define USB_OTG_DCTL_SDIS_Msk                    (0x1UL << USB_OTG_DCTL_SDIS_Pos) /*!< 0x00000002 */
#define USB_OTG_DCTL_SDIS                        USB_OTG_DCTL_SDIS_Msk         /*!< Soft disconnect         */
#define USB_OTG_DCTL_GINSTS_Pos                  (2U)
#define USB_OTG_DCTL_GINSTS_Msk                  (0x1UL << USB_OTG_DCTL_GINSTS_Pos) /*!< 0x00000004 */
#define USB_OTG_DCTL_GINSTS                      USB_OTG_DCTL_GINSTS_Msk       /*!< Global IN NAK status    */
#define USB_OTG_DCTL_GONSTS_Pos                  (3U)
#define USB_OTG_DCTL_GONSTS_Msk                  (0x1UL << USB_OTG_DCTL_GONSTS_Pos) /*!< 0x00000008 */
#define USB_OTG_DCTL_GONSTS                      USB_OTG_DCTL_GONSTS_Msk       /*!< Global OUT NAK status   */

#define USB_OTG_DCTL_TCTL_Pos                    (4U)
#define USB_OTG_DCTL_TCTL_Msk                    (0x7UL << USB_OTG_DCTL_TCTL_Pos) /*!< 0x00000070 */
#define USB_OTG_DCTL_TCTL                        USB_OTG_DCTL_TCTL_Msk         /*!< Test control */
#define USB_OTG_DCTL_TCTL_0                      (0x1UL << USB_OTG_DCTL_TCTL_Pos) /*!< 0x00000010 */
#define USB_OTG_DCTL_TCTL_1                      (0x2UL << USB_OTG_DCTL_TCTL_Pos) /*!< 0x00000020 */
#define USB_OTG_DCTL_TCTL_2                      (0x4UL << USB_OTG_DCTL_TCTL_Pos) /*!< 0x00000040 */
#define USB_OTG_DCTL_SGINAK_Pos                  (7U)
#define USB_OTG_DCTL_SGINAK_Msk                  (0x1UL << USB_OTG_DCTL_SGINAK_Pos) /*!< 0x00000080 */
#define USB_OTG_DCTL_SGINAK                      USB_OTG_DCTL_SGINAK_Msk       /*!< Set global IN NAK         */
#define USB_OTG_DCTL_CGINAK_Pos                  (8U)
#define USB_OTG_DCTL_CGINAK_Msk                  (0x1UL << USB_OTG_DCTL_CGINAK_Pos) /*!< 0x00000100 */
#define USB_OTG_DCTL_CGINAK                      USB_OTG_DCTL_CGINAK_Msk       /*!< Clear global IN NAK       */
#define USB_OTG_DCTL_SGONAK_Pos                  (9U)
#define USB_OTG_DCTL_SGONAK_Msk                  (0x1UL << USB_OTG_DCTL_SGONAK_Pos) /*!< 0x00000200 */
#define USB_OTG_DCTL_SGONAK                      USB_OTG_DCTL_SGONAK_Msk       /*!< Set global OUT NAK        */
#define USB_OTG_DCTL_CGONAK_Pos                  (10U)
#define USB_OTG_DCTL_CGONAK_Msk                  (0x1UL << USB_OTG_DCTL_CGONAK_Pos) /*!< 0x00000400 */
#define USB_OTG_DCTL_CGONAK                      USB_OTG_DCTL_CGONAK_Msk       /*!< Clear global OUT NAK      */
#define USB_OTG_DCTL_POPRGDNE_Pos                (11U)
#define USB_OTG_DCTL_POPRGDNE_Msk                (0x1UL << USB_OTG_DCTL_POPRGDNE_Pos) /*!< 0x00000800 */
#define USB_OTG_DCTL_POPRGDNE                    USB_OTG_DCTL_POPRGDNE_Msk     /*!< Power-on programming done */

/********************  Bit definition forUSB_OTG_HFIR register  ********************/
#define USB_OTG_HFIR_FRIVL_Pos                   (0U)
#define USB_OTG_HFIR_FRIVL_Msk                   (0xFFFFUL << USB_OTG_HFIR_FRIVL_Pos) /*!< 0x0000FFFF */
#define USB_OTG_HFIR_FRIVL                       USB_OTG_HFIR_FRIVL_Msk        /*!< Frame interval */

/********************  Bit definition forUSB_OTG_HFNUM register  ********************/
#define USB_OTG_HFNUM_FRNUM_Pos                  (0U)
#define USB_OTG_HFNUM_FRNUM_Msk                  (0xFFFFUL << USB_OTG_HFNUM_FRNUM_Pos) /*!< 0x0000FFFF */
#define USB_OTG_HFNUM_FRNUM                      USB_OTG_HFNUM_FRNUM_Msk       /*!< Frame number         */
#define USB_OTG_HFNUM_FTREM_Pos                  (16U)
#define USB_OTG_HFNUM_FTREM_Msk                  (0xFFFFUL << USB_OTG_HFNUM_FTREM_Pos) /*!< 0xFFFF0000 */
#define USB_OTG_HFNUM_FTREM                      USB_OTG_HFNUM_FTREM_Msk       /*!< Frame time remaining */

/********************  Bit definition forUSB_OTG_DSTS register  ********************/
#define USB_OTG_DSTS_SUSPSTS_Pos                 (0U)
#define USB_OTG_DSTS_SUSPSTS_Msk                 (0x1UL << USB_OTG_DSTS_SUSPSTS_Pos) /*!< 0x00000001 */
#define USB_OTG_DSTS_SUSPSTS                     USB_OTG_DSTS_SUSPSTS_Msk      /*!< Suspend status   */

#define USB_OTG_DSTS_ENUMSPD_Pos                 (1U)
#define USB_OTG_DSTS_ENUMSPD_Msk                 (0x3UL << USB_OTG_DSTS_ENUMSPD_Pos) /*!< 0x00000006 */
#define USB_OTG_DSTS_ENUMSPD                     USB_OTG_DSTS_ENUMSPD_Msk      /*!< Enumerated speed */
#define USB_OTG_DSTS_ENUMSPD_0                   (0x1UL << USB_OTG_DSTS_ENUMSPD_Pos) /*!< 0x00000002 */
#define USB_OTG_DSTS_ENUMSPD_1                   (0x2UL << USB_OTG_DSTS_ENUMSPD_Pos) /*!< 0x00000004 */
#define USB_OTG_DSTS_EERR_Pos                    (3U)
#define USB_OTG_DSTS_EERR_Msk                    (0x1UL << USB_OTG_DSTS_EERR_Pos) /*!< 0x00000008 */
#define USB_OTG_DSTS_EERR                        USB_OTG_DSTS_EERR_Msk         /*!< Erratic error     */
#define USB_OTG_DSTS_FNSOF_Pos                   (8U)
#define USB_OTG_DSTS_FNSOF_Msk                   (0x3FFFUL << USB_OTG_DSTS_FNSOF_Pos) /*!< 0x003FFF00 */
#define USB_OTG_DSTS_FNSOF                       USB_OTG_DSTS_FNSOF_Msk        /*!< Frame number of the received SOF */

/********************  Bit definition forUSB_OTG_GAHBCFG register  ********************/
#define USB_OTG_GAHBCFG_GINT_Pos                 (0U)
#define USB_OTG_GAHBCFG_GINT_Msk                 (0x1UL << USB_OTG_GAHBCFG_GINT_Pos) /*!< 0x00000001 */
#define USB_OTG_GAHBCFG_GINT                     USB_OTG_GAHBCFG_GINT_Msk      /*!< Global interrupt mask */

#define USB_OTG_GAHBCFG_HBSTLEN_Pos              (1U)
#define USB_OTG_GAHBCFG_HBSTLEN_Msk              (0xFUL << USB_OTG_GAHBCFG_HBSTLEN_Pos) /*!< 0x0000001E */
#define USB_OTG_GAHBCFG_HBSTLEN                  USB_OTG_GAHBCFG_HBSTLEN_Msk   /*!< Burst length/type */
#define USB_OTG_GAHBCFG_HBSTLEN_0                (0x1UL << USB_OTG_GAHBCFG_HBSTLEN_Pos) /*!< 0x00000002 */
#define USB_OTG_GAHBCFG_HBSTLEN_1                (0x2UL << USB_OTG_GAHBCFG_HBSTLEN_Pos) /*!< 0x00000004 */
#define USB_OTG_GAHBCFG_HBSTLEN_2                (0x4UL << USB_OTG_GAHBCFG_HBSTLEN_Pos) /*!< 0x00000008 */
#define USB_OTG_GAHBCFG_HBSTLEN_3                (0x8UL << USB_OTG_GAHBCFG_HBSTLEN_Pos) /*!< 0x00000010 */
#define USB_OTG_GAHBCFG_DMAEN_Pos                (5U)
#define USB_OTG_GAHBCFG_DMAEN_Msk                (0x1UL << USB_OTG_GAHBCFG_DMAEN_Pos) /*!< 0x00000020 */
#define USB_OTG_GAHBCFG_DMAEN                    USB_OTG_GAHBCFG_DMAEN_Msk     /*!< DMA enable */
#define USB_OTG_GAHBCFG_TXFELVL_Pos              (7U)
#define USB_OTG_GAHBCFG_TXFELVL_Msk              (0x1UL << USB_OTG_GAHBCFG_TXFELVL_Pos) /*!< 0x00000080 */
#define USB_OTG_GAHBCFG_TXFELVL                  USB_OTG_GAHBCFG_TXFELVL_Msk   /*!< TxFIFO empty level */
#define USB_OTG_GAHBCFG_PTXFELVL_Pos             (8U)
#define USB_OTG_GAHBCFG_PTXFELVL_Msk             (0x1UL << USB_OTG_GAHBCFG_PTXFELVL_Pos) /*!< 0x00000100 */
#define USB_OTG_GAHBCFG_PTXFELVL                 USB_OTG_GAHBCFG_PTXFELVL_Msk  /*!< Periodic TxFIFO empty level */

/********************  Bit definition forUSB_OTG_GUSBCFG register  ********************/

#define USB_OTG_GUSBCFG_TOCAL_Pos                (0U)
#define USB_OTG_GUSBCFG_TOCAL_Msk                (0x7UL << USB_OTG_GUSBCFG_TOCAL_Pos) /*!< 0x00000007 */
#define USB_OTG_GUSBCFG_TOCAL                    USB_OTG_GUSBCFG_TOCAL_Msk     /*!< FS timeout calibration */
#define USB_OTG_GUSBCFG_TOCAL_0                  (0x1UL << USB_OTG_GUSBCFG_TOCAL_Pos) /*!< 0x00000001 */
#define USB_OTG_GUSBCFG_TOCAL_1                  (0x2UL << USB_OTG_GUSBCFG_TOCAL_Pos) /*!< 0x00000002 */
#define USB_OTG_GUSBCFG_TOCAL_2                  (0x4UL << USB_OTG_GUSBCFG_TOCAL_Pos) /*!< 0x00000004 */
#define USB_OTG_GUSBCFG_PHYIF_Pos                (3U)
#define USB_OTG_GUSBCFG_PHYIF_Msk                (0x1UL << USB_OTG_GUSBCFG_PHYIF_Pos) /*!< 0x00000008 */
#define USB_OTG_GUSBCFG_PHYIF                    USB_OTG_GUSBCFG_PHYIF_Msk     /*!< PHY Interface (PHYIf) */
#define USB_OTG_GUSBCFG_ULPI_UTMI_SEL_Pos        (4U)
#define USB_OTG_GUSBCFG_ULPI_UTMI_SEL_Msk        (0x1UL << USB_OTG_GUSBCFG_ULPI_UTMI_SEL_Pos) /*!< 0x00000010 */
#define USB_OTG_GUSBCFG_ULPI_UTMI_SEL            USB_OTG_GUSBCFG_ULPI_UTMI_SEL_Msk /*!< ULPI or UTMI+ Select (ULPI_UTMI_Sel) */
#define USB_OTG_GUSBCFG_PHYSEL_Pos               (6U)
#define USB_OTG_GUSBCFG_PHYSEL_Msk               (0x1UL << USB_OTG_GUSBCFG_PHYSEL_Pos) /*!< 0x00000040 */
#define USB_OTG_GUSBCFG_PHYSEL                   USB_OTG_GUSBCFG_PHYSEL_Msk    /*!< USB 2.0 high-speed ULPI PHY or USB 1.1 full-speed serial transceiver select */
#define USB_OTG_GUSBCFG_SRPCAP_Pos               (8U)
#define USB_OTG_GUSBCFG_SRPCAP_Msk               (0x1UL << USB_OTG_GUSBCFG_SRPCAP_Pos) /*!< 0x00000100 */
#define USB_OTG_GUSBCFG_SRPCAP                   USB_OTG_GUSBCFG_SRPCAP_Msk    /*!< SRP-capable */
#define USB_OTG_GUSBCFG_HNPCAP_Pos               (9U)
#define USB_OTG_GUSBCFG_HNPCAP_Msk               (0x1UL << USB_OTG_GUSBCFG_HNPCAP_Pos) /*!< 0x00000200 */
#define USB_OTG_GUSBCFG_HNPCAP                   USB_OTG_GUSBCFG_HNPCAP_Msk    /*!< HNP-capable */

#define USB_OTG_GUSBCFG_TRDT_Pos                 (10U)
#define USB_OTG_GUSBCFG_TRDT_Msk                 (0xFUL << USB_OTG_GUSBCFG_TRDT_Pos) /*!< 0x00003C00 */
#define USB_OTG_GUSBCFG_TRDT                     USB_OTG_GUSBCFG_TRDT_Msk      /*!< USB turnaround time */
#define USB_OTG_GUSBCFG_TRDT_0                   (0x1UL << USB_OTG_GUSBCFG_TRDT_Pos) /*!< 0x00000400 */
#define USB_OTG_GUSBCFG_TRDT_1                   (0x2UL << USB_OTG_GUSBCFG_TRDT_Pos) /*!< 0x00000800 */
#define USB_OTG_GUSBCFG_TRDT_2                   (0x4UL << USB_OTG_GUSBCFG_TRDT_Pos) /*!< 0x00001000 */
#define USB_OTG_GUSBCFG_TRDT_3                   (0x8UL << USB_OTG_GUSBCFG_TRDT_Pos) /*!< 0x00002000 */
#define USB_OTG_GUSBCFG_PHYLPCS_Pos              (15U)
#define USB_OTG_GUSBCFG_PHYLPCS_Msk              (0x1UL << USB_OTG_GUSBCFG_PHYLPCS_Pos) /*!< 0x00008000 */
#define USB_OTG_GUSBCFG_PHYLPCS                  USB_OTG_GUSBCFG_PHYLPCS_Msk   /*!< PHY Low-power clock select */
#define USB_OTG_GUSBCFG_ULPIFSLS_Pos             (17U)
#define USB_OTG_GUSBCFG_ULPIFSLS_Msk             (0x1UL << USB_OTG_GUSBCFG_ULPIFSLS_Pos) /*!< 0x00020000 */
#define USB_OTG_GUSBCFG_ULPIFSLS                 USB_OTG_GUSBCFG_ULPIFSLS_Msk  /*!< ULPI FS/LS select               */
#define USB_OTG_GUSBCFG_ULPIAR_Pos               (18U)
#define USB_OTG_GUSBCFG_ULPIAR_Msk               (0x1UL << USB_OTG_GUSBCFG_ULPIAR_Pos) /*!< 0x00040000 */
#define USB_OTG_GUSBCFG_ULPIAR                   USB_OTG_GUSBCFG_ULPIAR_Msk    /*!< ULPI Auto-resume                */
#define USB_OTG_GUSBCFG_ULPICSM_Pos              (19U)
#define USB_OTG_GUSBCFG_ULPICSM_Msk              (0x1UL << USB_OTG_GUSBCFG_ULPICSM_Pos) /*!< 0x00080000 */
#define USB_OTG_GUSBCFG_ULPICSM                  USB_OTG_GUSBCFG_ULPICSM_Msk   /*!< ULPI Clock SuspendM             */
#define USB_OTG_GUSBCFG_ULPIEVBUSD_Pos           (20U)
#define USB_OTG_GUSBCFG_ULPIEVBUSD_Msk           (0x1UL << USB_OTG_GUSBCFG_ULPIEVBUSD_Pos) /*!< 0x00100000 */
#define USB_OTG_GUSBCFG_ULPIEVBUSD               USB_OTG_GUSBCFG_ULPIEVBUSD_Msk /*!< ULPI External VBUS Drive        */
#define USB_OTG_GUSBCFG_ULPIEVBUSI_Pos           (21U)
#define USB_OTG_GUSBCFG_ULPIEVBUSI_Msk           (0x1UL << USB_OTG_GUSBCFG_ULPIEVBUSI_Pos) /*!< 0x00200000 */
#define USB_OTG_GUSBCFG_ULPIEVBUSI               USB_OTG_GUSBCFG_ULPIEVBUSI_Msk /*!< ULPI external VBUS indicator    */
#define USB_OTG_GUSBCFG_TSDPS_Pos                (22U)
#define USB_OTG_GUSBCFG_TSDPS_Msk                (0x1UL << USB_OTG_GUSBCFG_TSDPS_Pos) /*!< 0x00400000 */
#define USB_OTG_GUSBCFG_TSDPS                    USB_OTG_GUSBCFG_TSDPS_Msk     /*!< TermSel DLine pulsing selection */
#define USB_OTG_GUSBCFG_PCCI_Pos                 (23U)
#define USB_OTG_GUSBCFG_PCCI_Msk                 (0x1UL << USB_OTG_GUSBCFG_PCCI_Pos) /*!< 0x00800000 */
#define USB_OTG_GUSBCFG_PCCI                     USB_OTG_GUSBCFG_PCCI_Msk      /*!< Indicator complement            */
#define USB_OTG_GUSBCFG_PTCI_Pos                 (24U)
#define USB_OTG_GUSBCFG_PTCI_Msk                 (0x1UL << USB_OTG_GUSBCFG_PTCI_Pos) /*!< 0x01000000 */
#define USB_OTG_GUSBCFG_PTCI                     USB_OTG_GUSBCFG_PTCI_Msk      /*!< Indicator pass through          */
#define USB_OTG_GUSBCFG_ULPIIPD_Pos              (25U)
#define USB_OTG_GUSBCFG_ULPIIPD_Msk              (0x1UL << USB_OTG_GUSBCFG_ULPIIPD_Pos) /*!< 0x02000000 */
#define USB_OTG_GUSBCFG_ULPIIPD                  USB_OTG_GUSBCFG_ULPIIPD_Msk   /*!< ULPI interface protect disable  */
#define USB_OTG_GUSBCFG_FHMOD_Pos                (29U)
#define USB_OTG_GUSBCFG_FHMOD_Msk                (0x1UL << USB_OTG_GUSBCFG_FHMOD_Pos) /*!< 0x20000000 */
#define USB_OTG_GUSBCFG_FHMOD                    USB_OTG_GUSBCFG_FHMOD_Msk     /*!< Forced host mode                */
#define USB_OTG_GUSBCFG_FDMOD_Pos                (30U)
#define USB_OTG_GUSBCFG_FDMOD_Msk                (0x1UL << USB_OTG_GUSBCFG_FDMOD_Pos) /*!< 0x40000000 */
#define USB_OTG_GUSBCFG_FDMOD                    USB_OTG_GUSBCFG_FDMOD_Msk     /*!< Forced peripheral mode          */
#define USB_OTG_GUSBCFG_CTXPKT_Pos               (31U)
#define USB_OTG_GUSBCFG_CTXPKT_Msk               (0x1UL << USB_OTG_GUSBCFG_CTXPKT_Pos) /*!< 0x80000000 */
#define USB_OTG_GUSBCFG_CTXPKT                   USB_OTG_GUSBCFG_CTXPKT_Msk    /*!< Corrupt Tx packet               */

/********************  Bit definition forUSB_OTG_GRSTCTL register  ********************/
#define USB_OTG_GRSTCTL_CSRST_Pos                (0U)
#define USB_OTG_GRSTCTL_CSRST_Msk                (0x1UL << USB_OTG_GRSTCTL_CSRST_Pos) /*!< 0x00000001 */
#define USB_OTG_GRSTCTL_CSRST                    USB_OTG_GRSTCTL_CSRST_Msk     /*!< Core soft reset          */
#define USB_OTG_GRSTCTL_HSRST_Pos                (1U)
#define USB_OTG_GRSTCTL_HSRST_Msk                (0x1UL << USB_OTG_GRSTCTL_HSRST_Pos) /*!< 0x00000002 */
#define USB_OTG_GRSTCTL_HSRST                    USB_OTG_GRSTCTL_HSRST_Msk     /*!< HCLK soft reset          */
#define USB_OTG_GRSTCTL_FCRST_Pos                (2U)
#define USB_OTG_GRSTCTL_FCRST_Msk                (0x1UL << USB_OTG_GRSTCTL_FCRST_Pos) /*!< 0x00000004 */
#define USB_OTG_GRSTCTL_FCRST                    USB_OTG_GRSTCTL_FCRST_Msk     /*!< Host frame counter reset */
#define USB_OTG_GRSTCTL_RXFFLSH_Pos              (4U)
#define USB_OTG_GRSTCTL_RXFFLSH_Msk              (0x1UL << USB_OTG_GRSTCTL_RXFFLSH_Pos) /*!< 0x00000010 */
#define USB_OTG_GRSTCTL_RXFFLSH                  USB_OTG_GRSTCTL_RXFFLSH_Msk   /*!< RxFIFO flush             */
#define USB_OTG_GRSTCTL_TXFFLSH_Pos              (5U)
#define USB_OTG_GRSTCTL_TXFFLSH_Msk              (0x1UL << USB_OTG_GRSTCTL_TXFFLSH_Pos) /*!< 0x00000020 */
#define USB_OTG_GRSTCTL_TXFFLSH                  USB_OTG_GRSTCTL_TXFFLSH_Msk   /*!< TxFIFO flush             */

#define USB_OTG_GRSTCTL_TXFNUM_Pos               (6U)
#define USB_OTG_GRSTCTL_TXFNUM_Msk               (0x1FUL << USB_OTG_GRSTCTL_TXFNUM_Pos) /*!< 0x000007C0 */
#define USB_OTG_GRSTCTL_TXFNUM                   USB_OTG_GRSTCTL_TXFNUM_Msk    /*!< TxFIFO number */
#define USB_OTG_GRSTCTL_TXFNUM_0                 (0x01UL << USB_OTG_GRSTCTL_TXFNUM_Pos) /*!< 0x00000040 */
#define USB_OTG_GRSTCTL_TXFNUM_1                 (0x02UL << USB_OTG_GRSTCTL_TXFNUM_Pos) /*!< 0x00000080 */
#define USB_OTG_GRSTCTL_TXFNUM_2                 (0x04UL << USB_OTG_GRSTCTL_TXFNUM_Pos) /*!< 0x00000100 */
#define USB_OTG_GRSTCTL_TXFNUM_3                 (0x08UL << USB_OTG_GRSTCTL_TXFNUM_Pos) /*!< 0x00000200 */
#define USB_OTG_GRSTCTL_TXFNUM_4                 (0x10UL << USB_OTG_GRSTCTL_TXFNUM_Pos) /*!< 0x00000400 */
#define USB_OTG_GRSTCTL_DMAREQ_Pos               (30U)
#define USB_OTG_GRSTCTL_DMAREQ_Msk               (0x1UL << USB_OTG_GRSTCTL_DMAREQ_Pos) /*!< 0x40000000 */
#define USB_OTG_GRSTCTL_DMAREQ                   USB_OTG_GRSTCTL_DMAREQ_Msk    /*!< DMA request signal */
#define USB_OTG_GRSTCTL_AHBIDL_Pos               (31U)
#define USB_OTG_GRSTCTL_AHBIDL_Msk               (0x1UL << USB_OTG_GRSTCTL_AHBIDL_Pos) /*!< 0x80000000 */
#define USB_OTG_GRSTCTL_AHBIDL                   USB_OTG_GRSTCTL_AHBIDL_Msk    /*!< AHB master idle */

/********************  Bit definition forUSB_OTG_DIEPMSK register  ********************/
#define USB_OTG_DIEPMSK_XFRCM_Pos                (0U)
#define USB_OTG_DIEPMSK_XFRCM_Msk                (0x1UL << USB_OTG_DIEPMSK_XFRCM_Pos) /*!< 0x00000001 */
#define USB_OTG_DIEPMSK_XFRCM                    USB_OTG_DIEPMSK_XFRCM_Msk     /*!< Transfer completed interrupt mask                 */
#define USB_OTG_DIEPMSK_EPDM_Pos                 (1U)
#define USB_OTG_DIEPMSK_EPDM_Msk                 (0x1UL << USB_OTG_DIEPMSK_EPDM_Pos) /*!< 0x00000002 */
#define USB_OTG_DIEPMSK_EPDM                     USB_OTG_DIEPMSK_EPDM_Msk      /*!< Endpoint disabled interrupt mask                  */
#define USB_OTG_DIEPMSK_TOM_Pos                  (3U)
#define USB_OTG_DIEPMSK_TOM_Msk                  (0x1UL << USB_OTG_DIEPMSK_TOM_Pos) /*!< 0x00000008 */
#define USB_OTG_DIEPMSK_TOM                      USB_OTG_DIEPMSK_TOM_Msk       /*!< Timeout condition mask (nonisochronous endpoints) */
#define USB_OTG_DIEPMSK_ITTXFEMSK_Pos            (4U)
#define USB_OTG_DIEPMSK_ITTXFEMSK_Msk            (0x1UL << USB_OTG_DIEPMSK_ITTXFEMSK_Pos) /*!< 0x00000010 */
#define USB_OTG_DIEPMSK_ITTXFEMSK                USB_OTG_DIEPMSK_ITTXFEMSK_Msk /*!< IN token received when TxFIFO empty mask          */
#define USB_OTG_DIEPMSK_INEPNMM_Pos              (5U)
#define USB_OTG_DIEPMSK_INEPNMM_Msk              (0x1UL << USB_OTG_DIEPMSK_INEPNMM_Pos) /*!< 0x00000020 */
#define USB_OTG_DIEPMSK_INEPNMM                  USB_OTG_DIEPMSK_INEPNMM_Msk   /*!< IN token received with EP mismatch mask           */
#define USB_OTG_DIEPMSK_INEPNEM_Pos              (6U)
#define USB_OTG_DIEPMSK_INEPNEM_Msk              (0x1UL << USB_OTG_DIEPMSK_INEPNEM_Pos) /*!< 0x00000040 */
#define USB_OTG_DIEPMSK_INEPNEM                  USB_OTG_DIEPMSK_INEPNEM_Msk   /*!< IN endpoint NAK effective mask                    */
#define USB_OTG_DIEPMSK_TXFURM_Pos               (8U)
#define USB_OTG_DIEPMSK_TXFURM_Msk               (0x1UL << USB_OTG_DIEPMSK_TXFURM_Pos) /*!< 0x00000100 */
#define USB_OTG_DIEPMSK_TXFURM                   USB_OTG_DIEPMSK_TXFURM_Msk    /*!< FIFO underrun mask                                */
#define USB_OTG_DIEPMSK_BIM_Pos                  (9U)
#define USB_OTG_DIEPMSK_BIM_Msk                  (0x1UL << USB_OTG_DIEPMSK_BIM_Pos) /*!< 0x00000200 */
#define USB_OTG_DIEPMSK_BIM                      USB_OTG_DIEPMSK_BIM_Msk       /*!< BNA interrupt mask                                */

/********************  Bit definition forUSB_OTG_HPTXSTS register  ********************/
#define USB_OTG_HPTXSTS_PTXFSAVL_Pos             (0U)
#define USB_OTG_HPTXSTS_PTXFSAVL_Msk             (0xFFFFUL << USB_OTG_HPTXSTS_PTXFSAVL_Pos) /*!< 0x0000FFFF */
#define USB_OTG_HPTXSTS_PTXFSAVL                 USB_OTG_HPTXSTS_PTXFSAVL_Msk  /*!< Periodic transmit data FIFO space available     */

#define USB_OTG_HPTXSTS_PTXQSAV_Pos              (16U)
#define USB_OTG_HPTXSTS_PTXQSAV_Msk              (0xFFUL << USB_OTG_HPTXSTS_PTXQSAV_Pos) /*!< 0x00FF0000 */
#define USB_OTG_HPTXSTS_PTXQSAV                  USB_OTG_HPTXSTS_PTXQSAV_Msk   /*!< Periodic transmit request queue space available */
#define USB_OTG_HPTXSTS_PTXQSAV_0                (0x01UL << USB_OTG_HPTXSTS_PTXQSAV_Pos) /*!< 0x00010000 */
#define USB_OTG_HPTXSTS_PTXQSAV_1                (0x02UL << USB_OTG_HPTXSTS_PTXQSAV_Pos) /*!< 0x00020000 */
#define USB_OTG_HPTXSTS_PTXQSAV_2                (0x04UL << USB_OTG_HPTXSTS_PTXQSAV_Pos) /*!< 0x00040000 */
#define USB_OTG_HPTXSTS_PTXQSAV_3                (0x08UL << USB_OTG_HPTXSTS_PTXQSAV_Pos) /*!< 0x00080000 */
#define USB_OTG_HPTXSTS_PTXQSAV_4                (0x10UL << USB_OTG_HPTXSTS_PTXQSAV_Pos) /*!< 0x00100000 */
#define USB_OTG_HPTXSTS_PTXQSAV_5                (0x20UL << USB_OTG_HPTXSTS_PTXQSAV_Pos) /*!< 0x00200000 */
#define USB_OTG_HPTXSTS_PTXQSAV_6                (0x40UL << USB_OTG_HPTXSTS_PTXQSAV_Pos) /*!< 0x00400000 */
#define USB_OTG_HPTXSTS_PTXQSAV_7                (0x80UL << USB_OTG_HPTXSTS_PTXQSAV_Pos) /*!< 0x00800000 */

#define USB_OTG_HPTXSTS_PTXQTOP_Pos              (24U)
#define USB_OTG_HPTXSTS_PTXQTOP_Msk              (0xFFUL << USB_OTG_HPTXSTS_PTXQTOP_Pos) /*!< 0xFF000000 */
#define USB_OTG_HPTXSTS_PTXQTOP                  USB_OTG_HPTXSTS_PTXQTOP_Msk   /*!< Top of the periodic transmit request queue */
#define USB_OTG_HPTXSTS_PTXQTOP_0                (0x01UL << USB_OTG_HPTXSTS_PTXQTOP_Pos) /*!< 0x01000000 */
#define USB_OTG_HPTXSTS_PTXQTOP_1                (0x02UL << USB_OTG_HPTXSTS_PTXQTOP_Pos) /*!< 0x02000000 */
#define USB_OTG_HPTXSTS_PTXQTOP_2                (0x04UL << USB_OTG_HPTXSTS_PTXQTOP_Pos) /*!< 0x04000000 */
#define USB_OTG_HPTXSTS_PTXQTOP_3                (0x08UL << USB_OTG_HPTXSTS_PTXQTOP_Pos) /*!< 0x08000000 */
#define USB_OTG_HPTXSTS_PTXQTOP_4                (0x10UL << USB_OTG_HPTXSTS_PTXQTOP_Pos) /*!< 0x10000000 */
#define USB_OTG_HPTXSTS_PTXQTOP_5                (0x20UL << USB_OTG_HPTXSTS_PTXQTOP_Pos) /*!< 0x20000000 */
#define USB_OTG_HPTXSTS_PTXQTOP_6                (0x40UL << USB_OTG_HPTXSTS_PTXQTOP_Pos) /*!< 0x40000000 */
#define USB_OTG_HPTXSTS_PTXQTOP_7                (0x80UL << USB_OTG_HPTXSTS_PTXQTOP_Pos) /*!< 0x80000000 */

/********************  Bit definition forUSB_OTG_HAINT register  ********************/
#define USB_OTG_HAINT_HAINT_Pos                  (0U)
#define USB_OTG_HAINT_HAINT_Msk                  (0xFFFFUL << USB_OTG_HAINT_HAINT_Pos) /*!< 0x0000FFFF */
#define USB_OTG_HAINT_HAINT                      USB_OTG_HAINT_HAINT_Msk       /*!< Channel interrupts */

/********************  Bit definition forUSB_OTG_DOEPMSK register  ********************/
#define USB_OTG_DOEPMSK_XFRCM_Pos                (0U)
#define USB_OTG_DOEPMSK_XFRCM_Msk                (0x1UL << USB_OTG_DOEPMSK_XFRCM_Pos) /*!< 0x00000001 */
#define USB_OTG_DOEPMSK_XFRCM                    USB_OTG_DOEPMSK_XFRCM_Msk     /*!< Transfer completed interrupt mask */
#define USB_OTG_DOEPMSK_EPDM_Pos                 (1U)
#define USB_OTG_DOEPMSK_EPDM_Msk                 (0x1UL << USB_OTG_DOEPMSK_EPDM_Pos) /*!< 0x00000002 */
#define USB_OTG_DOEPMSK_EPDM                     USB_OTG_DOEPMSK_EPDM_Msk      /*!< Endpoint disabled interrupt mask               */
#define USB_OTG_DOEPMSK_STUPM_Pos                (3U)
#define USB_OTG_DOEPMSK_STUPM_Msk                (0x1UL << USB_OTG_DOEPMSK_STUPM_Pos) /*!< 0x00000008 */
#define USB_OTG_DOEPMSK_STUPM                    USB_OTG_DOEPMSK_STUPM_Msk     /*!< SETUP phase done mask                          */
#define USB_OTG_DOEPMSK_OTEPDM_Pos               (4U)
#define USB_OTG_DOEPMSK_OTEPDM_Msk               (0x1UL << USB_OTG_DOEPMSK_OTEPDM_Pos) /*!< 0x00000010 */
#define USB_OTG_DOEPMSK_OTEPDM                   USB_OTG_DOEPMSK_OTEPDM_Msk    /*!< OUT token received when endpoint disabled mask */
#define USB_OTG_DOEPMSK_B2BSTUP_Pos              (6U)
#define USB_OTG_DOEPMSK_B2BSTUP_Msk              (0x1UL << USB_OTG_DOEPMSK_B2BSTUP_Pos) /*!< 0x00000040 */
#define USB_OTG_DOEPMSK_B2BSTUP                  USB_OTG_DOEPMSK_B2BSTUP_Msk   /*!< Back-to-back SETUP packets received mask       */
#define USB_OTG_DOEPMSK_OPEM_Pos                 (8U)
#define USB_OTG_DOEPMSK_OPEM_Msk                 (0x1UL << USB_OTG_DOEPMSK_OPEM_Pos) /*!< 0x00000100 */
#define USB_OTG_DOEPMSK_OPEM                     USB_OTG_DOEPMSK_OPEM_Msk      /*!< OUT packet error mask                          */
#define USB_OTG_DOEPMSK_BOIM_Pos                 (9U)
#define USB_OTG_DOEPMSK_BOIM_Msk                 (0x1UL << USB_OTG_DOEPMSK_BOIM_Pos) /*!< 0x00000200 */
#define USB_OTG_DOEPMSK_BOIM                     USB_OTG_DOEPMSK_BOIM_Msk      /*!< BNA interrupt mask                             */

/********************  Bit definition forUSB_OTG_GINTSTS register  ********************/
#define USB_OTG_GINTSTS_CMOD_Pos                 (0U)
#define USB_OTG_GINTSTS_CMOD_Msk                 (0x1UL << USB_OTG_GINTSTS_CMOD_Pos) /*!< 0x00000001 */
#define USB_OTG_GINTSTS_CMOD                     USB_OTG_GINTSTS_CMOD_Msk      /*!< Current mode of operation                      */
#define USB_OTG_GINTSTS_MMIS_Pos                 (1U)
#define USB_OTG_GINTSTS_MMIS_Msk                 (0x1UL << USB_OTG_GINTSTS_MMIS_Pos) /*!< 0x00000002 */
#define USB_OTG_GINTSTS_MMIS                     USB_OTG_GINTSTS_MMIS_Msk      /*!< Mode mismatch interrupt                        */
#define USB_OTG_GINTSTS_OTGINT_Pos               (2U)
#define USB_OTG_GINTSTS_OTGINT_Msk               (0x1UL << USB_OTG_GINTSTS_OTGINT_Pos) /*!< 0x00000004 */
#define USB_OTG_GINTSTS_OTGINT                   USB_OTG_GINTSTS_OTGINT_Msk    /*!< OTG interrupt                                  */
#define USB_OTG_GINTSTS_SOF_Pos                  (3U)
#define USB_OTG_GINTSTS_SOF_Msk                  (0x1UL << USB_OTG_GINTSTS_SOF_Pos) /*!< 0x00000008 */
#define USB_OTG_GINTSTS_SOF                      USB_OTG_GINTSTS_SOF_Msk       /*!< Start of frame                                 */
#define USB_OTG_GINTSTS_RXFLVL_Pos               (4U)
#define USB_OTG_GINTSTS_RXFLVL_Msk               (0x1UL << USB_OTG_GINTSTS_RXFLVL_Pos) /*!< 0x00000010 */
#define USB_OTG_GINTSTS_RXFLVL                   USB_OTG_GINTSTS_RXFLVL_Msk    /*!< RxFIFO nonempty                                */
#define USB_OTG_GINTSTS_NPTXFE_Pos               (5U)
#define USB_OTG_GINTSTS_NPTXFE_Msk               (0x1UL << USB_OTG_GINTSTS_NPTXFE_Pos) /*!< 0x00000020 */
#define USB_OTG_GINTSTS_NPTXFE                   USB_OTG_GINTSTS_NPTXFE_Msk    /*!< Nonperiodic TxFIFO empty                       */
#define USB_OTG_GINTSTS_GINAKEFF_Pos             (6U)
#define USB_OTG_GINTSTS_GINAKEFF_Msk             (0x1UL << USB_OTG_GINTSTS_GINAKEFF_Pos) /*!< 0x00000040 */
#define USB_OTG_GINTSTS_GINAKEFF                 USB_OTG_GINTSTS_GINAKEFF_Msk  /*!< Global IN nonperiodic NAK effective            */
#define USB_OTG_GINTSTS_BOUTNAKEFF_Pos           (7U)
#define USB_OTG_GINTSTS_BOUTNAKEFF_Msk           (0x1UL << USB_OTG_GINTSTS_BOUTNAKEFF_Pos) /*!< 0x00000080 */
#define USB_OTG_GINTSTS_BOUTNAKEFF               USB_OTG_GINTSTS_BOUTNAKEFF_Msk /*!< Global OUT NAK effective                       */
#define USB_OTG_GINTSTS_ESUSP_Pos                (10U)
#define USB_OTG_GINTSTS_ESUSP_Msk                (0x1UL << USB_OTG_GINTSTS_ESUSP_Pos) /*!< 0x00000400 */
#define USB_OTG_GINTSTS_ESUSP                    USB_OTG_GINTSTS_ESUSP_Msk     /*!< Early suspend                                  */
#define USB_OTG_GINTSTS_USBSUSP_Pos              (11U)
#define USB_OTG_GINTSTS_USBSUSP_Msk              (0x1UL << USB_OTG_GINTSTS_USBSUSP_Pos) /*!< 0x00000800 */
#define USB_OTG_GINTSTS_USBSUSP                  USB_OTG_GINTSTS_USBSUSP_Msk   /*!< USB suspend                                    */
#define USB_OTG_GINTSTS_USBRST_Pos               (12U)
#define USB_OTG_GINTSTS_USBRST_Msk               (0x1UL << USB_OTG_GINTSTS_USBRST_Pos) /*!< 0x00001000 */
#define USB_OTG_GINTSTS_USBRST                   USB_OTG_GINTSTS_USBRST_Msk    /*!< USB reset                                      */
#define USB_OTG_GINTSTS_ENUMDNE_Pos              (13U)
#define USB_OTG_GINTSTS_ENUMDNE_Msk              (0x1UL << USB_OTG_GINTSTS_ENUMDNE_Pos) /*!< 0x00002000 */
#define USB_OTG_GINTSTS_ENUMDNE                  USB_OTG_GINTSTS_ENUMDNE_Msk   /*!< Enumeration done                               */
#define USB_OTG_GINTSTS_ISOODRP_Pos              (14U)
#define USB_OTG_GINTSTS_ISOODRP_Msk              (0x1UL << USB_OTG_GINTSTS_ISOODRP_Pos) /*!< 0x00004000 */
#define USB_OTG_GINTSTS_ISOODRP                  USB_OTG_GINTSTS_ISOODRP_Msk   /*!< Isochronous OUT packet dropped interrupt       */
#define USB_OTG_GINTSTS_EOPF_Pos                 (15U)
#define USB_OTG_GINTSTS_EOPF_Msk                 (0x1UL << USB_OTG_GINTSTS_EOPF_Pos) /*!< 0x00008000 */
#define USB_OTG_GINTSTS_EOPF                     USB_OTG_GINTSTS_EOPF_Msk      /*!< End of periodic frame interrupt                */
#define USB_OTG_GINTSTS_IEPINT_Pos               (18U)
#define USB_OTG_GINTSTS_IEPINT_Msk               (0x1UL << USB_OTG_GINTSTS_IEPINT_Pos) /*!< 0x00040000 */
#define USB_OTG_GINTSTS_IEPINT                   USB_OTG_GINTSTS_IEPINT_Msk    /*!< IN endpoint interrupt                          */
#define USB_OTG_GINTSTS_OEPINT_Pos               (19U)
#define USB_OTG_GINTSTS_OEPINT_Msk               (0x1UL << USB_OTG_GINTSTS_OEPINT_Pos) /*!< 0x00080000 */
#define USB_OTG_GINTSTS_OEPINT                   USB_OTG_GINTSTS_OEPINT_Msk    /*!< OUT endpoint interrupt                         */
#define USB_OTG_GINTSTS_IISOIXFR_Pos             (20U)
#define USB_OTG_GINTSTS_IISOIXFR_Msk             (0x1UL << USB_OTG_GINTSTS_IISOIXFR_Pos) /*!< 0x00100000 */
#define USB_OTG_GINTSTS_IISOIXFR                 USB_OTG_GINTSTS_IISOIXFR_Msk  /*!< Incomplete isochronous IN transfer             */
#define USB_OTG_GINTSTS_PXFR_INCOMPISOOUT_Pos    (21U)
#define USB_OTG_GINTSTS_PXFR_INCOMPISOOUT_Msk    (0x1UL << USB_OTG_GINTSTS_PXFR_INCOMPISOOUT_Pos) /*!< 0x00200000 */
#define USB_OTG_GINTSTS_PXFR_INCOMPISOOUT        USB_OTG_GINTSTS_PXFR_INCOMPISOOUT_Msk /*!< Incomplete periodic transfer                   */
#define USB_OTG_GINTSTS_DATAFSUSP_Pos            (22U)
#define USB_OTG_GINTSTS_DATAFSUSP_Msk            (0x1UL << USB_OTG_GINTSTS_DATAFSUSP_Pos) /*!< 0x00400000 */
#define USB_OTG_GINTSTS_DATAFSUSP                USB_OTG_GINTSTS_DATAFSUSP_Msk /*!< Data fetch suspended                           */
#define USB_OTG_GINTSTS_RSTDET_Pos               (23U)
#define USB_OTG_GINTSTS_RSTDET_Msk               (0x1UL << USB_OTG_GINTSTS_RSTDET_Pos) /*!< 0x00800000 */
#define USB_OTG_GINTSTS_RSTDET                   USB_OTG_GINTSTS_RSTDET_Msk    /*!< Reset detected interrupt                       */
#define USB_OTG_GINTSTS_HPRTINT_Pos              (24U)
#define USB_OTG_GINTSTS_HPRTINT_Msk              (0x1UL << USB_OTG_GINTSTS_HPRTINT_Pos) /*!< 0x01000000 */
#define USB_OTG_GINTSTS_HPRTINT                  USB_OTG_GINTSTS_HPRTINT_Msk   /*!< Host port interrupt                            */
#define USB_OTG_GINTSTS_HCINT_Pos                (25U)
#define USB_OTG_GINTSTS_HCINT_Msk                (0x1UL << USB_OTG_GINTSTS_HCINT_Pos) /*!< 0x02000000 */
#define USB_OTG_GINTSTS_HCINT                    USB_OTG_GINTSTS_HCINT_Msk     /*!< Host channels interrupt                        */
#define USB_OTG_GINTSTS_PTXFE_Pos                (26U)
#define USB_OTG_GINTSTS_PTXFE_Msk                (0x1UL << USB_OTG_GINTSTS_PTXFE_Pos) /*!< 0x04000000 */
#define USB_OTG_GINTSTS_PTXFE                    USB_OTG_GINTSTS_PTXFE_Msk     /*!< Periodic TxFIFO empty                          */
#define USB_OTG_GINTSTS_LPMINT_Pos               (27U)
#define USB_OTG_GINTSTS_LPMINT_Msk               (0x1UL << USB_OTG_GINTSTS_LPMINT_Pos) /*!< 0x08000000 */
#define USB_OTG_GINTSTS_LPMINT                   USB_OTG_GINTSTS_LPMINT_Msk    /*!< LPM interrupt                                  */
#define USB_OTG_GINTSTS_CIDSCHG_Pos              (28U)
#define USB_OTG_GINTSTS_CIDSCHG_Msk              (0x1UL << USB_OTG_GINTSTS_CIDSCHG_Pos) /*!< 0x10000000 */
#define USB_OTG_GINTSTS_CIDSCHG                  USB_OTG_GINTSTS_CIDSCHG_Msk   /*!< Connector ID status change                     */
#define USB_OTG_GINTSTS_DISCINT_Pos              (29U)
#define USB_OTG_GINTSTS_DISCINT_Msk              (0x1UL << USB_OTG_GINTSTS_DISCINT_Pos) /*!< 0x20000000 */
#define USB_OTG_GINTSTS_DISCINT                  USB_OTG_GINTSTS_DISCINT_Msk   /*!< Disconnect detected interrupt                  */
#define USB_OTG_GINTSTS_SRQINT_Pos               (30U)
#define USB_OTG_GINTSTS_SRQINT_Msk               (0x1UL << USB_OTG_GINTSTS_SRQINT_Pos) /*!< 0x40000000 */
#define USB_OTG_GINTSTS_SRQINT                   USB_OTG_GINTSTS_SRQINT_Msk    /*!< Session request/new session detected interrupt */
#define USB_OTG_GINTSTS_WKUINT_Pos               (31U)
#define USB_OTG_GINTSTS_WKUINT_Msk               (0x1UL << USB_OTG_GINTSTS_WKUINT_Pos) /*!< 0x80000000 */
#define USB_OTG_GINTSTS_WKUINT                   USB_OTG_GINTSTS_WKUINT_Msk    /*!< Resume/remote wakeup detected interrupt        */

/********************  Bit definition forUSB_OTG_GINTMSK register  ********************/
#define USB_OTG_GINTMSK_MMISM_Pos                (1U)
#define USB_OTG_GINTMSK_MMISM_Msk                (0x1UL << USB_OTG_GINTMSK_MMISM_Pos) /*!< 0x00000002 */
#define USB_OTG_GINTMSK_MMISM                    USB_OTG_GINTMSK_MMISM_Msk     /*!< Mode mismatch interrupt mask                        */
#define USB_OTG_GINTMSK_OTGINT_Pos               (2U)
#define USB_OTG_GINTMSK_OTGINT_Msk               (0x1UL << USB_OTG_GINTMSK_OTGINT_Pos) /*!< 0x00000004 */
#define USB_OTG_GINTMSK_OTGINT                   USB_OTG_GINTMSK_OTGINT_Msk    /*!< OTG interrupt mask                                  */
#define USB_OTG_GINTMSK_SOFM_Pos                 (3U)
#define USB_OTG_GINTMSK_SOFM_Msk                 (0x1UL << USB_OTG_GINTMSK_SOFM_Pos) /*!< 0x00000008 */
#define USB_OTG_GINTMSK_SOFM                     USB_OTG_GINTMSK_SOFM_Msk      /*!< Start of frame mask                                 */
#define USB_OTG_GINTMSK_RXFLVLM_Pos              (4U)
#define USB_OTG_GINTMSK_RXFLVLM_Msk              (0x1UL << USB_OTG_GINTMSK_RXFLVLM_Pos) /*!< 0x00000010 */
#define USB_OTG_GINTMSK_RXFLVLM                  USB_OTG_GINTMSK_RXFLVLM_Msk   /*!< Receive FIFO nonempty mask                          */
#define USB_OTG_GINTMSK_NPTXFEM_Pos              (5U)
#define USB_OTG_GINTMSK_NPTXFEM_Msk              (0x1UL << USB_OTG_GINTMSK_NPTXFEM_Pos) /*!< 0x00000020 */
#define USB_OTG_GINTMSK_NPTXFEM                  USB_OTG_GINTMSK_NPTXFEM_Msk   /*!< Nonperiodic TxFIFO empty mask                       */
#define USB_OTG_GINTMSK_GINAKEFFM_Pos            (6U)
#define USB_OTG_GINTMSK_GINAKEFFM_Msk            (0x1UL << USB_OTG_GINTMSK_GINAKEFFM_Pos) /*!< 0x00000040 */
#define USB_OTG_GINTMSK_GINAKEFFM                USB_OTG_GINTMSK_GINAKEFFM_Msk /*!< Global nonperiodic IN NAK effective mask            */
#define USB_OTG_GINTMSK_GONAKEFFM_Pos            (7U)
#define USB_OTG_GINTMSK_GONAKEFFM_Msk            (0x1UL << USB_OTG_GINTMSK_GONAKEFFM_Pos) /*!< 0x00000080 */
#define USB_OTG_GINTMSK_GONAKEFFM                USB_OTG_GINTMSK_GONAKEFFM_Msk /*!< Global OUT NAK effective mask                       */
#define USB_OTG_GINTMSK_ESUSPM_Pos               (10U)
#define USB_OTG_GINTMSK_ESUSPM_Msk               (0x1UL << USB_OTG_GINTMSK_ESUSPM_Pos) /*!< 0x00000400 */
#define USB_OTG_GINTMSK_ESUSPM                   USB_OTG_GINTMSK_ESUSPM_Msk    /*!< Early suspend mask                                  */
#define USB_OTG_GINTMSK_USBSUSPM_Pos             (11U)
#define USB_OTG_GINTMSK_USBSUSPM_Msk             (0x1UL << USB_OTG_GINTMSK_USBSUSPM_Pos) /*!< 0x00000800 */
#define USB_OTG_GINTMSK_USBSUSPM                 USB_OTG_GINTMSK_USBSUSPM_Msk  /*!< USB suspend mask                                    */
#define USB_OTG_GINTMSK_USBRST_Pos               (12U)
#define USB_OTG_GINTMSK_USBRST_Msk               (0x1UL << USB_OTG_GINTMSK_USBRST_Pos) /*!< 0x00001000 */
#define USB_OTG_GINTMSK_USBRST                   USB_OTG_GINTMSK_USBRST_Msk    /*!< USB reset mask                                      */
#define USB_OTG_GINTMSK_ENUMDNEM_Pos             (13U)
#define USB_OTG_GINTMSK_ENUMDNEM_Msk             (0x1UL << USB_OTG_GINTMSK_ENUMDNEM_Pos) /*!< 0x00002000 */
#define USB_OTG_GINTMSK_ENUMDNEM                 USB_OTG_GINTMSK_ENUMDNEM_Msk  /*!< Enumeration done mask                               */
#define USB_OTG_GINTMSK_ISOODRPM_Pos             (14U)
#define USB_OTG_GINTMSK_ISOODRPM_Msk             (0x1UL << USB_OTG_GINTMSK_ISOODRPM_Pos) /*!< 0x00004000 */
#define USB_OTG_GINTMSK_ISOODRPM                 USB_OTG_GINTMSK_ISOODRPM_Msk  /*!< Isochronous OUT packet dropped interrupt mask       */
#define USB_OTG_GINTMSK_EOPFM_Pos                (15U)
#define USB_OTG_GINTMSK_EOPFM_Msk                (0x1UL << USB_OTG_GINTMSK_EOPFM_Pos) /*!< 0x00008000 */
#define USB_OTG_GINTMSK_EOPFM                    USB_OTG_GINTMSK_EOPFM_Msk     /*!< End of periodic frame interrupt mask                */
#define USB_OTG_GINTMSK_EPMISM_Pos               (17U)
#define USB_OTG_GINTMSK_EPMISM_Msk               (0x1UL << USB_OTG_GINTMSK_EPMISM_Pos) /*!< 0x00020000 */
#define USB_OTG_GINTMSK_EPMISM                   USB_OTG_GINTMSK_EPMISM_Msk    /*!< Endpoint mismatch interrupt mask                    */
#define USB_OTG_GINTMSK_IEPINT_Pos               (18U)
#define USB_OTG_GINTMSK_IEPINT_Msk               (0x1UL << USB_OTG_GINTMSK_IEPINT_Pos) /*!< 0x00040000 */
#define USB_OTG_GINTMSK_IEPINT                   USB_OTG_GINTMSK_IEPINT_Msk    /*!< IN endpoints interrupt mask                         */
#define USB_OTG_GINTMSK_OEPINT_Pos               (19U)
#define USB_OTG_GINTMSK_OEPINT_Msk               (0x1UL << USB_OTG_GINTMSK_OEPINT_Pos) /*!< 0x00080000 */
#define USB_OTG_GINTMSK_OEPINT                   USB_OTG_GINTMSK_OEPINT_Msk    /*!< OUT endpoints interrupt mask                        */
#define USB_OTG_GINTMSK_IISOIXFRM_Pos            (20U)
#define USB_OTG_GINTMSK_IISOIXFRM_Msk            (0x1UL << USB_OTG_GINTMSK_IISOIXFRM_Pos) /*!< 0x00100000 */
#define USB_OTG_GINTMSK_IISOIXFRM                USB_OTG_GINTMSK_IISOIXFRM_Msk /*!< Incomplete isochronous IN transfer mask             */
#define USB_OTG_GINTMSK_PXFRM_IISOOXFRM_Pos      (21U)
#define USB_OTG_GINTMSK_PXFRM_IISOOXFRM_Msk      (0x1UL << USB_OTG_GINTMSK_PXFRM_IISOOXFRM_Pos) /*!< 0x00200000 */
#define USB_OTG_GINTMSK_PXFRM_IISOOXFRM          USB_OTG_GINTMSK_PXFRM_IISOOXFRM_Msk /*!< Incomplete periodic transfer mask                   */
#define USB_OTG_GINTMSK_FSUSPM_Pos               (22U)
#define USB_OTG_GINTMSK_FSUSPM_Msk               (0x1UL << USB_OTG_GINTMSK_FSUSPM_Pos) /*!< 0x00400000 */
#define USB_OTG_GINTMSK_FSUSPM                   USB_OTG_GINTMSK_FSUSPM_Msk    /*!< Data fetch suspended mask                           */
#define USB_OTG_GINTMSK_RSTDEM_Pos               (23U)
#define USB_OTG_GINTMSK_RSTDEM_Msk               (0x1UL << USB_OTG_GINTMSK_RSTDEM_Pos) /*!< 0x00800000 */
#define USB_OTG_GINTMSK_RSTDEM                   USB_OTG_GINTMSK_RSTDEM_Msk    /*!< Reset detected interrupt mask                      */
#define USB_OTG_GINTMSK_PRTIM_Pos                (24U)
#define USB_OTG_GINTMSK_PRTIM_Msk                (0x1UL << USB_OTG_GINTMSK_PRTIM_Pos) /*!< 0x01000000 */
#define USB_OTG_GINTMSK_PRTIM                    USB_OTG_GINTMSK_PRTIM_Msk     /*!< Host port interrupt mask                            */
#define USB_OTG_GINTMSK_HCIM_Pos                 (25U)
#define USB_OTG_GINTMSK_HCIM_Msk                 (0x1UL << USB_OTG_GINTMSK_HCIM_Pos) /*!< 0x02000000 */
#define USB_OTG_GINTMSK_HCIM                     USB_OTG_GINTMSK_HCIM_Msk      /*!< Host channels interrupt mask                        */
#define USB_OTG_GINTMSK_PTXFEM_Pos               (26U)
#define USB_OTG_GINTMSK_PTXFEM_Msk               (0x1UL << USB_OTG_GINTMSK_PTXFEM_Pos) /*!< 0x04000000 */
#define USB_OTG_GINTMSK_PTXFEM                   USB_OTG_GINTMSK_PTXFEM_Msk    /*!< Periodic TxFIFO empty mask                          */
#define USB_OTG_GINTMSK_LPMINTM_Pos              (27U)
#define USB_OTG_GINTMSK_LPMINTM_Msk              (0x1UL << USB_OTG_GINTMSK_LPMINTM_Pos) /*!< 0x08000000 */
#define USB_OTG_GINTMSK_LPMINTM                  USB_OTG_GINTMSK_LPMINTM_Msk   /*!< LPM interrupt Mask                                  */
#define USB_OTG_GINTMSK_CIDSCHGM_Pos             (28U)
#define USB_OTG_GINTMSK_CIDSCHGM_Msk             (0x1UL << USB_OTG_GINTMSK_CIDSCHGM_Pos) /*!< 0x10000000 */
#define USB_OTG_GINTMSK_CIDSCHGM                 USB_OTG_GINTMSK_CIDSCHGM_Msk  /*!< Connector ID status change mask                     */
#define USB_OTG_GINTMSK_DISCINT_Pos              (29U)
#define USB_OTG_GINTMSK_DISCINT_Msk              (0x1UL << USB_OTG_GINTMSK_DISCINT_Pos) /*!< 0x20000000 */
#define USB_OTG_GINTMSK_DISCINT                  USB_OTG_GINTMSK_DISCINT_Msk   /*!< Disconnect detected interrupt mask                  */
#define USB_OTG_GINTMSK_SRQIM_Pos                (30U)
#define USB_OTG_GINTMSK_SRQIM_Msk                (0x1UL << USB_OTG_GINTMSK_SRQIM_Pos) /*!< 0x40000000 */
#define USB_OTG_GINTMSK_SRQIM                    USB_OTG_GINTMSK_SRQIM_Msk     /*!< Session request/new session detected interrupt mask */
#define USB_OTG_GINTMSK_WUIM_Pos                 (31U)
#define USB_OTG_GINTMSK_WUIM_Msk                 (0x1UL << USB_OTG_GINTMSK_WUIM_Pos) /*!< 0x80000000 */
#define USB_OTG_GINTMSK_WUIM                     USB_OTG_GINTMSK_WUIM_Msk      /*!< Resume/remote wakeup detected interrupt mask        */

/********************  Bit definition forUSB_OTG_DAINT register  ********************/
#define USB_OTG_DAINT_IEPINT_Pos                 (0U)
#define USB_OTG_DAINT_IEPINT_Msk                 (0xFFFFUL << USB_OTG_DAINT_IEPINT_Pos) /*!< 0x0000FFFF */
#define USB_OTG_DAINT_IEPINT                     USB_OTG_DAINT_IEPINT_Msk      /*!< IN endpoint interrupt bits  */
#define USB_OTG_DAINT_OEPINT_Pos                 (16U)
#define USB_OTG_DAINT_OEPINT_Msk                 (0xFFFFUL << USB_OTG_DAINT_OEPINT_Pos) /*!< 0xFFFF0000 */
#define USB_OTG_DAINT_OEPINT                     USB_OTG_DAINT_OEPINT_Msk      /*!< OUT endpoint interrupt bits */

/********************  Bit definition forUSB_OTG_HAINTMSK register  ********************/
#define USB_OTG_HAINTMSK_HAINTM_Pos              (0U)
#define USB_OTG_HAINTMSK_HAINTM_Msk              (0xFFFFUL << USB_OTG_HAINTMSK_HAINTM_Pos) /*!< 0x0000FFFF */
#define USB_OTG_HAINTMSK_HAINTM                  USB_OTG_HAINTMSK_HAINTM_Msk   /*!< Channel interrupt mask */

/********************  Bit definition for USB_OTG_GRXSTSP register  ********************/
#define USB_OTG_GRXSTSP_EPNUM_Pos                (0U)
#define USB_OTG_GRXSTSP_EPNUM_Msk                (0xFUL << USB_OTG_GRXSTSP_EPNUM_Pos) /*!< 0x0000000F */
#define USB_OTG_GRXSTSP_EPNUM                    USB_OTG_GRXSTSP_EPNUM_Msk     /*!< IN EP interrupt mask bits  */
#define USB_OTG_GRXSTSP_BCNT_Pos                 (4U)
#define USB_OTG_GRXSTSP_BCNT_Msk                 (0x7FFUL << USB_OTG_GRXSTSP_BCNT_Pos) /*!< 0x00007FF0 */
#define USB_OTG_GRXSTSP_BCNT                     USB_OTG_GRXSTSP_BCNT_Msk      /*!< OUT EP interrupt mask bits */
#define USB_OTG_GRXSTSP_DPID_Pos                 (15U)
#define USB_OTG_GRXSTSP_DPID_Msk                 (0x3UL << USB_OTG_GRXSTSP_DPID_Pos) /*!< 0x00018000 */
#define USB_OTG_GRXSTSP_DPID                     USB_OTG_GRXSTSP_DPID_Msk      /*!< OUT EP interrupt mask bits */
#define USB_OTG_GRXSTSP_PKTSTS_Pos               (17U)
#define USB_OTG_GRXSTSP_PKTSTS_Msk               (0xFUL << USB_OTG_GRXSTSP_PKTSTS_Pos) /*!< 0x001E0000 */
#define USB_OTG_GRXSTSP_PKTSTS                   USB_OTG_GRXSTSP_PKTSTS_Msk    /*!< OUT EP interrupt mask bits */

/********************  Bit definition forUSB_OTG_DAINTMSK register  ********************/
#define USB_OTG_DAINTMSK_IEPM_Pos                (0U)
#define USB_OTG_DAINTMSK_IEPM_Msk                (0xFFFFUL << USB_OTG_DAINTMSK_IEPM_Pos) /*!< 0x0000FFFF */
#define USB_OTG_DAINTMSK_IEPM                    USB_OTG_DAINTMSK_IEPM_Msk     /*!< IN EP interrupt mask bits */
#define USB_OTG_DAINTMSK_OEPM_Pos                (16U)
#define USB_OTG_DAINTMSK_OEPM_Msk                (0xFFFFUL << USB_OTG_DAINTMSK_OEPM_Pos) /*!< 0xFFFF0000 */
#define USB_OTG_DAINTMSK_OEPM                    USB_OTG_DAINTMSK_OEPM_Msk     /*!< OUT EP interrupt mask bits */

/********************  Bit definition for OTG register  ********************/

#define USB_OTG_CHNUM_Pos                        (0U)
#define USB_OTG_CHNUM_Msk                        (0xFUL << USB_OTG_CHNUM_Pos)   /*!< 0x0000000F */
#define USB_OTG_CHNUM                            USB_OTG_CHNUM_Msk             /*!< Channel number */
#define USB_OTG_CHNUM_0                          (0x1UL << USB_OTG_CHNUM_Pos)   /*!< 0x00000001 */
#define USB_OTG_CHNUM_1                          (0x2UL << USB_OTG_CHNUM_Pos)   /*!< 0x00000002 */
#define USB_OTG_CHNUM_2                          (0x4UL << USB_OTG_CHNUM_Pos)   /*!< 0x00000004 */
#define USB_OTG_CHNUM_3                          (0x8UL << USB_OTG_CHNUM_Pos)   /*!< 0x00000008 */
#define USB_OTG_BCNT_Pos                         (4U)
#define USB_OTG_BCNT_Msk                         (0x7FFUL << USB_OTG_BCNT_Pos)  /*!< 0x00007FF0 */
#define USB_OTG_BCNT                             USB_OTG_BCNT_Msk              /*!< Byte count */

#define USB_OTG_DPID_Pos                         (15U)
#define USB_OTG_DPID_Msk                         (0x3UL << USB_OTG_DPID_Pos)    /*!< 0x00018000 */
#define USB_OTG_DPID                             USB_OTG_DPID_Msk              /*!< Data PID */
#define USB_OTG_DPID_0                           (0x1UL << USB_OTG_DPID_Pos)    /*!< 0x00008000 */
#define USB_OTG_DPID_1                           (0x2UL << USB_OTG_DPID_Pos)    /*!< 0x00010000 */

#define USB_OTG_PKTSTS_Pos                       (17U)
#define USB_OTG_PKTSTS_Msk                       (0xFUL << USB_OTG_PKTSTS_Pos)  /*!< 0x001E0000 */
#define USB_OTG_PKTSTS                           USB_OTG_PKTSTS_Msk            /*!< Packet status */
#define USB_OTG_PKTSTS_0                         (0x1UL << USB_OTG_PKTSTS_Pos)  /*!< 0x00020000 */
#define USB_OTG_PKTSTS_1                         (0x2UL << USB_OTG_PKTSTS_Pos)  /*!< 0x00040000 */
#define USB_OTG_PKTSTS_2                         (0x4UL << USB_OTG_PKTSTS_Pos)  /*!< 0x00080000 */
#define USB_OTG_PKTSTS_3                         (0x8UL << USB_OTG_PKTSTS_Pos)  /*!< 0x00100000 */

#define USB_OTG_EPNUM_Pos                        (0U)
#define USB_OTG_EPNUM_Msk                        (0xFUL << USB_OTG_EPNUM_Pos)   /*!< 0x0000000F */
#define USB_OTG_EPNUM                            USB_OTG_EPNUM_Msk             /*!< Endpoint number */
#define USB_OTG_EPNUM_0                          (0x1UL << USB_OTG_EPNUM_Pos)   /*!< 0x00000001 */
#define USB_OTG_EPNUM_1                          (0x2UL << USB_OTG_EPNUM_Pos)   /*!< 0x00000002 */
#define USB_OTG_EPNUM_2                          (0x4UL << USB_OTG_EPNUM_Pos)   /*!< 0x00000004 */
#define USB_OTG_EPNUM_3                          (0x8UL << USB_OTG_EPNUM_Pos)   /*!< 0x00000008 */

#define USB_OTG_FRMNUM_Pos                       (21U)
#define USB_OTG_FRMNUM_Msk                       (0xFUL << USB_OTG_FRMNUM_Pos)  /*!< 0x01E00000 */
#define USB_OTG_FRMNUM                           USB_OTG_FRMNUM_Msk            /*!< Frame number */
#define USB_OTG_FRMNUM_0                         (0x1UL << USB_OTG_FRMNUM_Pos)  /*!< 0x00200000 */
#define USB_OTG_FRMNUM_1                         (0x2UL << USB_OTG_FRMNUM_Pos)  /*!< 0x00400000 */
#define USB_OTG_FRMNUM_2                         (0x4UL << USB_OTG_FRMNUM_Pos)  /*!< 0x00800000 */
#define USB_OTG_FRMNUM_3                         (0x8UL << USB_OTG_FRMNUM_Pos)  /*!< 0x01000000 */

/********************  Bit definition forUSB_OTG_GRXFSIZ register  ********************/
#define USB_OTG_GRXFSIZ_RXFD_Pos                 (0U)
#define USB_OTG_GRXFSIZ_RXFD_Msk                 (0xFFFFUL << USB_OTG_GRXFSIZ_RXFD_Pos) /*!< 0x0000FFFF */
#define USB_OTG_GRXFSIZ_RXFD                     USB_OTG_GRXFSIZ_RXFD_Msk      /*!< RxFIFO depth */

/********************  Bit definition forUSB_OTG_DVBUSDIS register  ********************/
#define USB_OTG_DVBUSDIS_VBUSDT_Pos              (0U)
#define USB_OTG_DVBUSDIS_VBUSDT_Msk              (0xFFFFUL << USB_OTG_DVBUSDIS_VBUSDT_Pos) /*!< 0x0000FFFF */
#define USB_OTG_DVBUSDIS_VBUSDT                  USB_OTG_DVBUSDIS_VBUSDT_Msk   /*!< Device VBUS discharge time */

/********************  Bit definition for OTG register  ********************/
#define USB_OTG_NPTXFSA_Pos                      (0U)
#define USB_OTG_NPTXFSA_Msk                      (0xFFFFUL << USB_OTG_NPTXFSA_Pos) /*!< 0x0000FFFF */
#define USB_OTG_NPTXFSA                          USB_OTG_NPTXFSA_Msk           /*!< Nonperiodic transmit RAM start address */
#define USB_OTG_NPTXFD_Pos                       (16U)
#define USB_OTG_NPTXFD_Msk                       (0xFFFFUL << USB_OTG_NPTXFD_Pos) /*!< 0xFFFF0000 */
#define USB_OTG_NPTXFD                           USB_OTG_NPTXFD_Msk            /*!< Nonperiodic TxFIFO depth               */
#define USB_OTG_TX0FSA_Pos                       (0U)
#define USB_OTG_TX0FSA_Msk                       (0xFFFFUL << USB_OTG_TX0FSA_Pos) /*!< 0x0000FFFF */
#define USB_OTG_TX0FSA                           USB_OTG_TX0FSA_Msk            /*!< Endpoint 0 transmit RAM start address  */
#define USB_OTG_TX0FD_Pos                        (16U)
#define USB_OTG_TX0FD_Msk                        (0xFFFFUL << USB_OTG_TX0FD_Pos) /*!< 0xFFFF0000 */
#define USB_OTG_TX0FD                            USB_OTG_TX0FD_Msk             /*!< Endpoint 0 TxFIFO depth                */

/********************  Bit definition forUSB_OTG_DVBUSPULSE register  ********************/
#define USB_OTG_DVBUSPULSE_DVBUSP_Pos            (0U)
#define USB_OTG_DVBUSPULSE_DVBUSP_Msk            (0xFFFUL << USB_OTG_DVBUSPULSE_DVBUSP_Pos) /*!< 0x00000FFF */
#define USB_OTG_DVBUSPULSE_DVBUSP                USB_OTG_DVBUSPULSE_DVBUSP_Msk /*!< Device VBUS pulsing time */

/********************  Bit definition forUSB_OTG_GNPTXSTS register  ********************/
#define USB_OTG_GNPTXSTS_NPTXFSAV_Pos            (0U)
#define USB_OTG_GNPTXSTS_NPTXFSAV_Msk            (0xFFFFUL << USB_OTG_GNPTXSTS_NPTXFSAV_Pos) /*!< 0x0000FFFF */
#define USB_OTG_GNPTXSTS_NPTXFSAV                USB_OTG_GNPTXSTS_NPTXFSAV_Msk /*!< Nonperiodic TxFIFO space available */

#define USB_OTG_GNPTXSTS_NPTQXSAV_Pos            (16U)
#define USB_OTG_GNPTXSTS_NPTQXSAV_Msk            (0xFFUL << USB_OTG_GNPTXSTS_NPTQXSAV_Pos) /*!< 0x00FF0000 */
#define USB_OTG_GNPTXSTS_NPTQXSAV                USB_OTG_GNPTXSTS_NPTQXSAV_Msk /*!< Nonperiodic transmit request queue space available */
#define USB_OTG_GNPTXSTS_NPTQXSAV_0              (0x01UL << USB_OTG_GNPTXSTS_NPTQXSAV_Pos) /*!< 0x00010000 */
#define USB_OTG_GNPTXSTS_NPTQXSAV_1              (0x02UL << USB_OTG_GNPTXSTS_NPTQXSAV_Pos) /*!< 0x00020000 */
#define USB_OTG_GNPTXSTS_NPTQXSAV_2              (0x04UL << USB_OTG_GNPTXSTS_NPTQXSAV_Pos) /*!< 0x00040000 */
#define USB_OTG_GNPTXSTS_NPTQXSAV_3              (0x08UL << USB_OTG_GNPTXSTS_NPTQXSAV_Pos) /*!< 0x00080000 */
#define USB_OTG_GNPTXSTS_NPTQXSAV_4              (0x10UL << USB_OTG_GNPTXSTS_NPTQXSAV_Pos) /*!< 0x00100000 */
#define USB_OTG_GNPTXSTS_NPTQXSAV_5              (0x20UL << USB_OTG_GNPTXSTS_NPTQXSAV_Pos) /*!< 0x00200000 */
#define USB_OTG_GNPTXSTS_NPTQXSAV_6              (0x40UL << USB_OTG_GNPTXSTS_NPTQXSAV_Pos) /*!< 0x00400000 */
#define USB_OTG_GNPTXSTS_NPTQXSAV_7              (0x80UL << USB_OTG_GNPTXSTS_NPTQXSAV_Pos) /*!< 0x00800000 */

#define USB_OTG_GNPTXSTS_NPTXQTOP_Pos            (24U)
#define USB_OTG_GNPTXSTS_NPTXQTOP_Msk            (0x7FUL << USB_OTG_GNPTXSTS_NPTXQTOP_Pos) /*!< 0x7F000000 */
#define USB_OTG_GNPTXSTS_NPTXQTOP                USB_OTG_GNPTXSTS_NPTXQTOP_Msk /*!< Top of the nonperiodic transmit request queue */
#define USB_OTG_GNPTXSTS_NPTXQTOP_0              (0x01UL << USB_OTG_GNPTXSTS_NPTXQTOP_Pos) /*!< 0x01000000 */
#define USB_OTG_GNPTXSTS_NPTXQTOP_1              (0x02UL << USB_OTG_GNPTXSTS_NPTXQTOP_Pos) /*!< 0x02000000 */
#define USB_OTG_GNPTXSTS_NPTXQTOP_2              (0x04UL << USB_OTG_GNPTXSTS_NPTXQTOP_Pos) /*!< 0x04000000 */
#define USB_OTG_GNPTXSTS_NPTXQTOP_3              (0x08UL << USB_OTG_GNPTXSTS_NPTXQTOP_Pos) /*!< 0x08000000 */
#define USB_OTG_GNPTXSTS_NPTXQTOP_4              (0x10UL << USB_OTG_GNPTXSTS_NPTXQTOP_Pos) /*!< 0x10000000 */
#define USB_OTG_GNPTXSTS_NPTXQTOP_5              (0x20UL << USB_OTG_GNPTXSTS_NPTXQTOP_Pos) /*!< 0x20000000 */
#define USB_OTG_GNPTXSTS_NPTXQTOP_6              (0x40UL << USB_OTG_GNPTXSTS_NPTXQTOP_Pos) /*!< 0x40000000 */

/********************  Bit definition forUSB_OTG_DTHRCTL register  ********************/
#define USB_OTG_DTHRCTL_NONISOTHREN_Pos          (0U)
#define USB_OTG_DTHRCTL_NONISOTHREN_Msk          (0x1UL << USB_OTG_DTHRCTL_NONISOTHREN_Pos) /*!< 0x00000001 */
#define USB_OTG_DTHRCTL_NONISOTHREN              USB_OTG_DTHRCTL_NONISOTHREN_Msk /*!< Nonisochronous IN endpoints threshold enable */
#define USB_OTG_DTHRCTL_ISOTHREN_Pos             (1U)
#define USB_OTG_DTHRCTL_ISOTHREN_Msk             (0x1UL << USB_OTG_DTHRCTL_ISOTHREN_Pos) /*!< 0x00000002 */
#define USB_OTG_DTHRCTL_ISOTHREN                 USB_OTG_DTHRCTL_ISOTHREN_Msk  /*!< ISO IN endpoint threshold enable */

#define USB_OTG_DTHRCTL_TXTHRLEN_Pos             (2U)
#define USB_OTG_DTHRCTL_TXTHRLEN_Msk             (0x1FFUL << USB_OTG_DTHRCTL_TXTHRLEN_Pos) /*!< 0x000007FC */
#define USB_OTG_DTHRCTL_TXTHRLEN                 USB_OTG_DTHRCTL_TXTHRLEN_Msk  /*!< Transmit threshold length */
#define USB_OTG_DTHRCTL_TXTHRLEN_0               (0x001UL << USB_OTG_DTHRCTL_TXTHRLEN_Pos) /*!< 0x00000004 */
#define USB_OTG_DTHRCTL_TXTHRLEN_1               (0x002UL << USB_OTG_DTHRCTL_TXTHRLEN_Pos) /*!< 0x00000008 */
#define USB_OTG_DTHRCTL_TXTHRLEN_2               (0x004UL << USB_OTG_DTHRCTL_TXTHRLEN_Pos) /*!< 0x00000010 */
#define USB_OTG_DTHRCTL_TXTHRLEN_3               (0x008UL << USB_OTG_DTHRCTL_TXTHRLEN_Pos) /*!< 0x00000020 */
#define USB_OTG_DTHRCTL_TXTHRLEN_4               (0x010UL << USB_OTG_DTHRCTL_TXTHRLEN_Pos) /*!< 0x00000040 */
#define USB_OTG_DTHRCTL_TXTHRLEN_5               (0x020UL << USB_OTG_DTHRCTL_TXTHRLEN_Pos) /*!< 0x00000080 */
#define USB_OTG_DTHRCTL_TXTHRLEN_6               (0x040UL << USB_OTG_DTHRCTL_TXTHRLEN_Pos) /*!< 0x00000100 */
#define USB_OTG_DTHRCTL_TXTHRLEN_7               (0x080UL << USB_OTG_DTHRCTL_TXTHRLEN_Pos) /*!< 0x00000200 */
#define USB_OTG_DTHRCTL_TXTHRLEN_8               (0x100UL << USB_OTG_DTHRCTL_TXTHRLEN_Pos) /*!< 0x00000400 */
#define USB_OTG_DTHRCTL_RXTHREN_Pos              (16U)
#define USB_OTG_DTHRCTL_RXTHREN_Msk              (0x1UL << USB_OTG_DTHRCTL_RXTHREN_Pos) /*!< 0x00010000 */
#define USB_OTG_DTHRCTL_RXTHREN                  USB_OTG_DTHRCTL_RXTHREN_Msk   /*!< Receive threshold enable */

#define USB_OTG_DTHRCTL_RXTHRLEN_Pos             (17U)
#define USB_OTG_DTHRCTL_RXTHRLEN_Msk             (0x1FFUL << USB_OTG_DTHRCTL_RXTHRLEN_Pos) /*!< 0x03FE0000 */
#define USB_OTG_DTHRCTL_RXTHRLEN                 USB_OTG_DTHRCTL_RXTHRLEN_Msk  /*!< Receive threshold length */
#define USB_OTG_DTHRCTL_RXTHRLEN_0               (0x001UL << USB_OTG_DTHRCTL_RXTHRLEN_Pos) /*!< 0x00020000 */
#define USB_OTG_DTHRCTL_RXTHRLEN_1               (0x002UL << USB_OTG_DTHRCTL_RXTHRLEN_Pos) /*!< 0x00040000 */
#define USB_OTG_DTHRCTL_RXTHRLEN_2               (0x004UL << USB_OTG_DTHRCTL_RXTHRLEN_Pos) /*!< 0x00080000 */
#define USB_OTG_DTHRCTL_RXTHRLEN_3               (0x008UL << USB_OTG_DTHRCTL_RXTHRLEN_Pos) /*!< 0x00100000 */
#define USB_OTG_DTHRCTL_RXTHRLEN_4               (0x010UL << USB_OTG_DTHRCTL_RXTHRLEN_Pos) /*!< 0x00200000 */
#define USB_OTG_DTHRCTL_RXTHRLEN_5               (0x020UL << USB_OTG_DTHRCTL_RXTHRLEN_Pos) /*!< 0x00400000 */
#define USB_OTG_DTHRCTL_RXTHRLEN_6               (0x040UL << USB_OTG_DTHRCTL_RXTHRLEN_Pos) /*!< 0x00800000 */
#define USB_OTG_DTHRCTL_RXTHRLEN_7               (0x080UL << USB_OTG_DTHRCTL_RXTHRLEN_Pos) /*!< 0x01000000 */
#define USB_OTG_DTHRCTL_RXTHRLEN_8               (0x100UL << USB_OTG_DTHRCTL_RXTHRLEN_Pos) /*!< 0x02000000 */
#define USB_OTG_DTHRCTL_ARPEN_Pos                (27U)
#define USB_OTG_DTHRCTL_ARPEN_Msk                (0x1UL << USB_OTG_DTHRCTL_ARPEN_Pos) /*!< 0x08000000 */
#define USB_OTG_DTHRCTL_ARPEN                    USB_OTG_DTHRCTL_ARPEN_Msk     /*!< Arbiter parking enable */

/********************  Bit definition forUSB_OTG_DIEPEMPMSK register  ********************/
#define USB_OTG_DIEPEMPMSK_INEPTXFEM_Pos         (0U)
#define USB_OTG_DIEPEMPMSK_INEPTXFEM_Msk         (0xFFFFUL << USB_OTG_DIEPEMPMSK_INEPTXFEM_Pos) /*!< 0x0000FFFF */
#define USB_OTG_DIEPEMPMSK_INEPTXFEM             USB_OTG_DIEPEMPMSK_INEPTXFEM_Msk /*!< IN EP Tx FIFO empty interrupt mask bits */

/********************  Bit definition forUSB_OTG_DEACHINT register  ********************/
#define USB_OTG_DEACHINT_IEP1INT_Pos             (1U)
#define USB_OTG_DEACHINT_IEP1INT_Msk             (0x1UL << USB_OTG_DEACHINT_IEP1INT_Pos) /*!< 0x00000002 */
#define USB_OTG_DEACHINT_IEP1INT                 USB_OTG_DEACHINT_IEP1INT_Msk  /*!< IN endpoint 1interrupt bit   */
#define USB_OTG_DEACHINT_OEP1INT_Pos             (17U)
#define USB_OTG_DEACHINT_OEP1INT_Msk             (0x1UL << USB_OTG_DEACHINT_OEP1INT_Pos) /*!< 0x00020000 */
#define USB_OTG_DEACHINT_OEP1INT                 USB_OTG_DEACHINT_OEP1INT_Msk  /*!< OUT endpoint 1 interrupt bit */

/********************  Bit definition forUSB_OTG_GCCFG register  ********************/
#define USB_OTG_GCCFG_DCDET_Pos                  (0U)
#define USB_OTG_GCCFG_DCDET_Msk                  (0x1UL << USB_OTG_GCCFG_DCDET_Pos) /*!< 0x00000001 */
#define USB_OTG_GCCFG_DCDET                      USB_OTG_GCCFG_DCDET_Msk       /*!< Data contact detection (DCD) status */
#define USB_OTG_GCCFG_PDET_Pos                   (1U)
#define USB_OTG_GCCFG_PDET_Msk                   (0x1UL << USB_OTG_GCCFG_PDET_Pos) /*!< 0x00000002 */
#define USB_OTG_GCCFG_PDET                       USB_OTG_GCCFG_PDET_Msk        /*!< Primary detection (PD) status */
#define USB_OTG_GCCFG_SDET_Pos                   (2U)
#define USB_OTG_GCCFG_SDET_Msk                   (0x1UL << USB_OTG_GCCFG_SDET_Pos) /*!< 0x00000004 */
#define USB_OTG_GCCFG_SDET                       USB_OTG_GCCFG_SDET_Msk        /*!< Secondary detection (SD) status */
#define USB_OTG_GCCFG_PS2DET_Pos                 (3U)
#define USB_OTG_GCCFG_PS2DET_Msk                 (0x1UL << USB_OTG_GCCFG_PS2DET_Pos) /*!< 0x00000008 */
#define USB_OTG_GCCFG_PS2DET                     USB_OTG_GCCFG_PS2DET_Msk      /*!< DM pull-up detection status */
#define USB_OTG_GCCFG_PWRDWN_Pos                 (16U)
#define USB_OTG_GCCFG_PWRDWN_Msk                 (0x1UL << USB_OTG_GCCFG_PWRDWN_Pos) /*!< 0x00010000 */
#define USB_OTG_GCCFG_PWRDWN                     USB_OTG_GCCFG_PWRDWN_Msk      /*!< Power down */
#define USB_OTG_GCCFG_BCDEN_Pos                  (17U)
#define USB_OTG_GCCFG_BCDEN_Msk                  (0x1UL << USB_OTG_GCCFG_BCDEN_Pos) /*!< 0x00020000 */
#define USB_OTG_GCCFG_BCDEN                      USB_OTG_GCCFG_BCDEN_Msk       /*!< Battery charging detector (BCD) enable */
#define USB_OTG_GCCFG_DCDEN_Pos                  (18U)
#define USB_OTG_GCCFG_DCDEN_Msk                  (0x1UL << USB_OTG_GCCFG_DCDEN_Pos) /*!< 0x00040000 */
#define USB_OTG_GCCFG_DCDEN                      USB_OTG_GCCFG_DCDEN_Msk       /*!< Data contact detection (DCD) mode enable*/
#define USB_OTG_GCCFG_PDEN_Pos                   (19U)
#define USB_OTG_GCCFG_PDEN_Msk                   (0x1UL << USB_OTG_GCCFG_PDEN_Pos) /*!< 0x00080000 */
#define USB_OTG_GCCFG_PDEN                       USB_OTG_GCCFG_PDEN_Msk        /*!< Primary detection (PD) mode enable*/
#define USB_OTG_GCCFG_SDEN_Pos                   (20U)
#define USB_OTG_GCCFG_SDEN_Msk                   (0x1UL << USB_OTG_GCCFG_SDEN_Pos) /*!< 0x00100000 */
#define USB_OTG_GCCFG_SDEN                       USB_OTG_GCCFG_SDEN_Msk        /*!< Secondary detection (SD) mode enable */
#define USB_OTG_GCCFG_VBDEN_Pos                  (21U)
#define USB_OTG_GCCFG_VBDEN_Msk                  (0x1UL << USB_OTG_GCCFG_VBDEN_Pos) /*!< 0x00200000 */
#define USB_OTG_GCCFG_VBDEN                      USB_OTG_GCCFG_VBDEN_Msk       /*!< Secondary detection (SD) mode enable */
#define USB_OTG_GCCFG_OTGIDEN_Pos                (22U)
#define USB_OTG_GCCFG_OTGIDEN_Msk                (0x1UL << USB_OTG_GCCFG_OTGIDEN_Pos) /*!< 0x00400000 */
#define USB_OTG_GCCFG_OTGIDEN                    USB_OTG_GCCFG_OTGIDEN_Msk     /*!< OTG Id enable */
#define USB_OTG_GCCFG_PHYHSEN_Pos                (23U)
#define USB_OTG_GCCFG_PHYHSEN_Msk                (0x1UL << USB_OTG_GCCFG_PHYHSEN_Pos) /*!< 0x00800000 */
#define USB_OTG_GCCFG_PHYHSEN                    USB_OTG_GCCFG_PHYHSEN_Msk     /*!< HS PHY enable */

/********************  Bit definition forUSB_OTG_GPWRDN) register  ********************/
#define USB_OTG_GPWRDN_ADPMEN_Pos                (0U)
#define USB_OTG_GPWRDN_ADPMEN_Msk                (0x1UL << USB_OTG_GPWRDN_ADPMEN_Pos) /*!< 0x00000001 */
#define USB_OTG_GPWRDN_ADPMEN                    USB_OTG_GPWRDN_ADPMEN_Msk     /*!< ADP module enable */
#define USB_OTG_GPWRDN_ADPIF_Pos                 (23U)
#define USB_OTG_GPWRDN_ADPIF_Msk                 (0x1UL << USB_OTG_GPWRDN_ADPIF_Pos) /*!< 0x00800000 */
#define USB_OTG_GPWRDN_ADPIF                     USB_OTG_GPWRDN_ADPIF_Msk      /*!< ADP Interrupt flag */

/********************  Bit definition forUSB_OTG_DEACHINTMSK register  ********************/
#define USB_OTG_DEACHINTMSK_IEP1INTM_Pos         (1U)
#define USB_OTG_DEACHINTMSK_IEP1INTM_Msk         (0x1UL << USB_OTG_DEACHINTMSK_IEP1INTM_Pos) /*!< 0x00000002 */
#define USB_OTG_DEACHINTMSK_IEP1INTM             USB_OTG_DEACHINTMSK_IEP1INTM_Msk /*!< IN Endpoint 1 interrupt mask bit  */
#define USB_OTG_DEACHINTMSK_OEP1INTM_Pos         (17U)
#define USB_OTG_DEACHINTMSK_OEP1INTM_Msk         (0x1UL << USB_OTG_DEACHINTMSK_OEP1INTM_Pos) /*!< 0x00020000 */
#define USB_OTG_DEACHINTMSK_OEP1INTM             USB_OTG_DEACHINTMSK_OEP1INTM_Msk /*!< OUT Endpoint 1 interrupt mask bit */

/********************  Bit definition forUSB_OTG_CID register  ********************/
#define USB_OTG_CID_PRODUCT_ID_Pos               (0U)
#define USB_OTG_CID_PRODUCT_ID_Msk               (0xFFFFFFFFUL << USB_OTG_CID_PRODUCT_ID_Pos) /*!< 0xFFFFFFFF */
#define USB_OTG_CID_PRODUCT_ID                   USB_OTG_CID_PRODUCT_ID_Msk    /*!< Product ID field */

/********************  Bit definition for USB_OTG_GLPMCFG register  ********************/
#define USB_OTG_GLPMCFG_LPMEN_Pos                (0U)
#define USB_OTG_GLPMCFG_LPMEN_Msk                (0x1UL << USB_OTG_GLPMCFG_LPMEN_Pos) /*!< 0x00000001 */
#define USB_OTG_GLPMCFG_LPMEN                    USB_OTG_GLPMCFG_LPMEN_Msk     /*!< LPM support enable                                     */
#define USB_OTG_GLPMCFG_LPMACK_Pos               (1U)
#define USB_OTG_GLPMCFG_LPMACK_Msk               (0x1UL << USB_OTG_GLPMCFG_LPMACK_Pos) /*!< 0x00000002 */
#define USB_OTG_GLPMCFG_LPMACK                   USB_OTG_GLPMCFG_LPMACK_Msk    /*!< LPM Token acknowledge enable                           */
#define USB_OTG_GLPMCFG_BESL_Pos                 (2U)
#define USB_OTG_GLPMCFG_BESL_Msk                 (0xFUL << USB_OTG_GLPMCFG_BESL_Pos) /*!< 0x0000003C */
#define USB_OTG_GLPMCFG_BESL                     USB_OTG_GLPMCFG_BESL_Msk      /*!< BESL value received with last ACKed LPM Token          */
#define USB_OTG_GLPMCFG_REMWAKE_Pos              (6U)
#define USB_OTG_GLPMCFG_REMWAKE_Msk              (0x1UL << USB_OTG_GLPMCFG_REMWAKE_Pos) /*!< 0x00000040 */
#define USB_OTG_GLPMCFG_REMWAKE                  USB_OTG_GLPMCFG_REMWAKE_Msk   /*!< bRemoteWake value received with last ACKed LPM Token   */
#define USB_OTG_GLPMCFG_L1SSEN_Pos               (7U)
#define USB_OTG_GLPMCFG_L1SSEN_Msk               (0x1UL << USB_OTG_GLPMCFG_L1SSEN_Pos) /*!< 0x00000080 */
#define USB_OTG_GLPMCFG_L1SSEN                   USB_OTG_GLPMCFG_L1SSEN_Msk    /*!< L1 shallow sleep enable                                */
#define USB_OTG_GLPMCFG_BESLTHRS_Pos             (8U)
#define USB_OTG_GLPMCFG_BESLTHRS_Msk             (0xFUL << USB_OTG_GLPMCFG_BESLTHRS_Pos) /*!< 0x00000F00 */
#define USB_OTG_GLPMCFG_BESLTHRS                 USB_OTG_GLPMCFG_BESLTHRS_Msk  /*!< BESL threshold                                         */
#define USB_OTG_GLPMCFG_L1DSEN_Pos               (12U)
#define USB_OTG_GLPMCFG_L1DSEN_Msk               (0x1UL << USB_OTG_GLPMCFG_L1DSEN_Pos) /*!< 0x00001000 */
#define USB_OTG_GLPMCFG_L1DSEN                   USB_OTG_GLPMCFG_L1DSEN_Msk    /*!< L1 deep sleep enable                                   */
#define USB_OTG_GLPMCFG_LPMRSP_Pos               (13U)
#define USB_OTG_GLPMCFG_LPMRSP_Msk               (0x3UL << USB_OTG_GLPMCFG_LPMRSP_Pos) /*!< 0x00006000 */
#define USB_OTG_GLPMCFG_LPMRSP                   USB_OTG_GLPMCFG_LPMRSP_Msk    /*!< LPM response                                           */
#define USB_OTG_GLPMCFG_SLPSTS_Pos               (15U)
#define USB_OTG_GLPMCFG_SLPSTS_Msk               (0x1UL << USB_OTG_GLPMCFG_SLPSTS_Pos) /*!< 0x00008000 */
#define USB_OTG_GLPMCFG_SLPSTS                   USB_OTG_GLPMCFG_SLPSTS_Msk    /*!< Port sleep status                                      */
#define USB_OTG_GLPMCFG_L1RSMOK_Pos              (16U)
#define USB_OTG_GLPMCFG_L1RSMOK_Msk              (0x1UL << USB_OTG_GLPMCFG_L1RSMOK_Pos) /*!< 0x00010000 */
#define USB_OTG_GLPMCFG_L1RSMOK                  USB_OTG_GLPMCFG_L1RSMOK_Msk   /*!< Sleep State Resume OK                                  */
#define USB_OTG_GLPMCFG_LPMCHIDX_Pos             (17U)
#define USB_OTG_GLPMCFG_LPMCHIDX_Msk             (0xFUL << USB_OTG_GLPMCFG_LPMCHIDX_Pos) /*!< 0x001E0000 */
#define USB_OTG_GLPMCFG_LPMCHIDX                 USB_OTG_GLPMCFG_LPMCHIDX_Msk  /*!< LPM Channel Index                                      */
#define USB_OTG_GLPMCFG_LPMRCNT_Pos              (21U)
#define USB_OTG_GLPMCFG_LPMRCNT_Msk              (0x7UL << USB_OTG_GLPMCFG_LPMRCNT_Pos) /*!< 0x00E00000 */
#define USB_OTG_GLPMCFG_LPMRCNT                  USB_OTG_GLPMCFG_LPMRCNT_Msk   /*!< LPM retry count                                        */
#define USB_OTG_GLPMCFG_SNDLPM_Pos               (24U)
#define USB_OTG_GLPMCFG_SNDLPM_Msk               (0x1UL << USB_OTG_GLPMCFG_SNDLPM_Pos) /*!< 0x01000000 */
#define USB_OTG_GLPMCFG_SNDLPM                   USB_OTG_GLPMCFG_SNDLPM_Msk    /*!< Send LPM transaction                                   */
#define USB_OTG_GLPMCFG_LPMRCNTSTS_Pos           (25U)
#define USB_OTG_GLPMCFG_LPMRCNTSTS_Msk           (0x7UL << USB_OTG_GLPMCFG_LPMRCNTSTS_Pos) /*!< 0x0E000000 */
#define USB_OTG_GLPMCFG_LPMRCNTSTS               USB_OTG_GLPMCFG_LPMRCNTSTS_Msk /*!< LPM retry count status                                 */
#define USB_OTG_GLPMCFG_ENBESL_Pos               (28U)
#define USB_OTG_GLPMCFG_ENBESL_Msk               (0x1UL << USB_OTG_GLPMCFG_ENBESL_Pos) /*!< 0x10000000 */
#define USB_OTG_GLPMCFG_ENBESL                   USB_OTG_GLPMCFG_ENBESL_Msk    /*!< Enable best effort service latency                     */

/********************  Bit definition forUSB_OTG_DIEPEACHMSK1 register  ********************/
#define USB_OTG_DIEPEACHMSK1_XFRCM_Pos           (0U)
#define USB_OTG_DIEPEACHMSK1_XFRCM_Msk           (0x1UL << USB_OTG_DIEPEACHMSK1_XFRCM_Pos) /*!< 0x00000001 */
#define USB_OTG_DIEPEACHMSK1_XFRCM               USB_OTG_DIEPEACHMSK1_XFRCM_Msk /*!< Transfer completed interrupt mask                 */
#define USB_OTG_DIEPEACHMSK1_EPDM_Pos            (1U)
#define USB_OTG_DIEPEACHMSK1_EPDM_Msk            (0x1UL << USB_OTG_DIEPEACHMSK1_EPDM_Pos) /*!< 0x00000002 */
#define USB_OTG_DIEPEACHMSK1_EPDM                USB_OTG_DIEPEACHMSK1_EPDM_Msk /*!< Endpoint disabled interrupt mask                  */
#define USB_OTG_DIEPEACHMSK1_TOM_Pos             (3U)
#define USB_OTG_DIEPEACHMSK1_TOM_Msk             (0x1UL << USB_OTG_DIEPEACHMSK1_TOM_Pos) /*!< 0x00000008 */
#define USB_OTG_DIEPEACHMSK1_TOM                 USB_OTG_DIEPEACHMSK1_TOM_Msk  /*!< Timeout condition mask (nonisochronous endpoints) */
#define USB_OTG_DIEPEACHMSK1_ITTXFEMSK_Pos       (4U)
#define USB_OTG_DIEPEACHMSK1_ITTXFEMSK_Msk       (0x1UL << USB_OTG_DIEPEACHMSK1_ITTXFEMSK_Pos) /*!< 0x00000010 */
#define USB_OTG_DIEPEACHMSK1_ITTXFEMSK           USB_OTG_DIEPEACHMSK1_ITTXFEMSK_Msk /*!< IN token received when TxFIFO empty mask          */
#define USB_OTG_DIEPEACHMSK1_INEPNMM_Pos         (5U)
#define USB_OTG_DIEPEACHMSK1_INEPNMM_Msk         (0x1UL << USB_OTG_DIEPEACHMSK1_INEPNMM_Pos) /*!< 0x00000020 */
#define USB_OTG_DIEPEACHMSK1_INEPNMM             USB_OTG_DIEPEACHMSK1_INEPNMM_Msk /*!< IN token received with EP mismatch mask           */
#define USB_OTG_DIEPEACHMSK1_INEPNEM_Pos         (6U)
#define USB_OTG_DIEPEACHMSK1_INEPNEM_Msk         (0x1UL << USB_OTG_DIEPEACHMSK1_INEPNEM_Pos) /*!< 0x00000040 */
#define USB_OTG_DIEPEACHMSK1_INEPNEM             USB_OTG_DIEPEACHMSK1_INEPNEM_Msk /*!< IN endpoint NAK effective mask                    */
#define USB_OTG_DIEPEACHMSK1_TXFURM_Pos          (8U)
#define USB_OTG_DIEPEACHMSK1_TXFURM_Msk          (0x1UL << USB_OTG_DIEPEACHMSK1_TXFURM_Pos) /*!< 0x00000100 */
#define USB_OTG_DIEPEACHMSK1_TXFURM              USB_OTG_DIEPEACHMSK1_TXFURM_Msk /*!< FIFO underrun mask */
#define USB_OTG_DIEPEACHMSK1_BIM_Pos             (9U)
#define USB_OTG_DIEPEACHMSK1_BIM_Msk             (0x1UL << USB_OTG_DIEPEACHMSK1_BIM_Pos) /*!< 0x00000200 */
#define USB_OTG_DIEPEACHMSK1_BIM                 USB_OTG_DIEPEACHMSK1_BIM_Msk  /*!< BNA interrupt mask */
#define USB_OTG_DIEPEACHMSK1_NAKM_Pos            (13U)
#define USB_OTG_DIEPEACHMSK1_NAKM_Msk            (0x1UL << USB_OTG_DIEPEACHMSK1_NAKM_Pos) /*!< 0x00002000 */
#define USB_OTG_DIEPEACHMSK1_NAKM                USB_OTG_DIEPEACHMSK1_NAKM_Msk /*!< NAK interrupt mask */

/********************  Bit definition forUSB_OTG_HPRT register  ********************/
#define USB_OTG_HPRT_PCSTS_Pos                   (0U)
#define USB_OTG_HPRT_PCSTS_Msk                   (0x1UL << USB_OTG_HPRT_PCSTS_Pos) /*!< 0x00000001 */
#define USB_OTG_HPRT_PCSTS                       USB_OTG_HPRT_PCSTS_Msk        /*!< Port connect status        */
#define USB_OTG_HPRT_PCDET_Pos                   (1U)
#define USB_OTG_HPRT_PCDET_Msk                   (0x1UL << USB_OTG_HPRT_PCDET_Pos) /*!< 0x00000002 */
#define USB_OTG_HPRT_PCDET                       USB_OTG_HPRT_PCDET_Msk        /*!< Port connect detected      */
#define USB_OTG_HPRT_PENA_Pos                    (2U)
#define USB_OTG_HPRT_PENA_Msk                    (0x1UL << USB_OTG_HPRT_PENA_Pos) /*!< 0x00000004 */
#define USB_OTG_HPRT_PENA                        USB_OTG_HPRT_PENA_Msk         /*!< Port enable                */
#define USB_OTG_HPRT_PENCHNG_Pos                 (3U)
#define USB_OTG_HPRT_PENCHNG_Msk                 (0x1UL << USB_OTG_HPRT_PENCHNG_Pos) /*!< 0x00000008 */
#define USB_OTG_HPRT_PENCHNG                     USB_OTG_HPRT_PENCHNG_Msk      /*!< Port enable/disable change */
#define USB_OTG_HPRT_POCA_Pos                    (4U)
#define USB_OTG_HPRT_POCA_Msk                    (0x1UL << USB_OTG_HPRT_POCA_Pos) /*!< 0x00000010 */
#define USB_OTG_HPRT_POCA                        USB_OTG_HPRT_POCA_Msk         /*!< Port overcurrent active    */
#define USB_OTG_HPRT_POCCHNG_Pos                 (5U)
#define USB_OTG_HPRT_POCCHNG_Msk                 (0x1UL << USB_OTG_HPRT_POCCHNG_Pos) /*!< 0x00000020 */
#define USB_OTG_HPRT_POCCHNG                     USB_OTG_HPRT_POCCHNG_Msk      /*!< Port overcurrent change    */
#define USB_OTG_HPRT_PRES_Pos                    (6U)
#define USB_OTG_HPRT_PRES_Msk                    (0x1UL << USB_OTG_HPRT_PRES_Pos) /*!< 0x00000040 */
#define USB_OTG_HPRT_PRES                        USB_OTG_HPRT_PRES_Msk         /*!< Port resume   */
#define USB_OTG_HPRT_PSUSP_Pos                   (7U)
#define USB_OTG_HPRT_PSUSP_Msk                   (0x1UL << USB_OTG_HPRT_PSUSP_Pos) /*!< 0x00000080 */
#define USB_OTG_HPRT_PSUSP                       USB_OTG_HPRT_PSUSP_Msk        /*!< Port suspend  */
#define USB_OTG_HPRT_PRST_Pos                    (8U)
#define USB_OTG_HPRT_PRST_Msk                    (0x1UL << USB_OTG_HPRT_PRST_Pos) /*!< 0x00000100 */
#define USB_OTG_HPRT_PRST                        USB_OTG_HPRT_PRST_Msk         /*!< Port reset    */

#define USB_OTG_HPRT_PLSTS_Pos                   (10U)
#define USB_OTG_HPRT_PLSTS_Msk                   (0x3UL << USB_OTG_HPRT_PLSTS_Pos) /*!< 0x00000C00 */
#define USB_OTG_HPRT_PLSTS                       USB_OTG_HPRT_PLSTS_Msk        /*!< Port line status */
#define USB_OTG_HPRT_PLSTS_0                     (0x1UL << USB_OTG_HPRT_PLSTS_Pos) /*!< 0x00000400 */
#define USB_OTG_HPRT_PLSTS_1                     (0x2UL << USB_OTG_HPRT_PLSTS_Pos) /*!< 0x00000800 */
#define USB_OTG_HPRT_PPWR_Pos                    (12U)
#define USB_OTG_HPRT_PPWR_Msk                    (0x1UL << USB_OTG_HPRT_PPWR_Pos) /*!< 0x00001000 */
#define USB_OTG_HPRT_PPWR                        USB_OTG_HPRT_PPWR_Msk         /*!< Port power */

#define USB_OTG_HPRT_PTCTL_Pos                   (13U)
#define USB_OTG_HPRT_PTCTL_Msk                   (0xFUL << USB_OTG_HPRT_PTCTL_Pos) /*!< 0x0001E000 */
#define USB_OTG_HPRT_PTCTL                       USB_OTG_HPRT_PTCTL_Msk        /*!< Port test control */
#define USB_OTG_HPRT_PTCTL_0                     (0x1UL << USB_OTG_HPRT_PTCTL_Pos) /*!< 0x00002000 */
#define USB_OTG_HPRT_PTCTL_1                     (0x2UL << USB_OTG_HPRT_PTCTL_Pos) /*!< 0x00004000 */
#define USB_OTG_HPRT_PTCTL_2                     (0x4UL << USB_OTG_HPRT_PTCTL_Pos) /*!< 0x00008000 */
#define USB_OTG_HPRT_PTCTL_3                     (0x8UL << USB_OTG_HPRT_PTCTL_Pos) /*!< 0x00010000 */

#define USB_OTG_HPRT_PSPD_Pos                    (17U)
#define USB_OTG_HPRT_PSPD_Msk                    (0x3UL << USB_OTG_HPRT_PSPD_Pos) /*!< 0x00060000 */
#define USB_OTG_HPRT_PSPD                        USB_OTG_HPRT_PSPD_Msk         /*!< Port speed */
#define USB_OTG_HPRT_PSPD_0                      (0x1UL << USB_OTG_HPRT_PSPD_Pos) /*!< 0x00020000 */
#define USB_OTG_HPRT_PSPD_1                      (0x2UL << USB_OTG_HPRT_PSPD_Pos) /*!< 0x00040000 */

/********************  Bit definition forUSB_OTG_DOEPEACHMSK1 register  ********************/
#define USB_OTG_DOEPEACHMSK1_XFRCM_Pos           (0U)
#define USB_OTG_DOEPEACHMSK1_XFRCM_Msk           (0x1UL << USB_OTG_DOEPEACHMSK1_XFRCM_Pos) /*!< 0x00000001 */
#define USB_OTG_DOEPEACHMSK1_XFRCM               USB_OTG_DOEPEACHMSK1_XFRCM_Msk /*!< Transfer completed interrupt mask */
#define USB_OTG_DOEPEACHMSK1_EPDM_Pos            (1U)
#define USB_OTG_DOEPEACHMSK1_EPDM_Msk            (0x1UL << USB_OTG_DOEPEACHMSK1_EPDM_Pos) /*!< 0x00000002 */
#define USB_OTG_DOEPEACHMSK1_EPDM                USB_OTG_DOEPEACHMSK1_EPDM_Msk /*!< Endpoint disabled interrupt mask */
#define USB_OTG_DOEPEACHMSK1_TOM_Pos             (3U)
#define USB_OTG_DOEPEACHMSK1_TOM_Msk             (0x1UL << USB_OTG_DOEPEACHMSK1_TOM_Pos) /*!< 0x00000008 */
#define USB_OTG_DOEPEACHMSK1_TOM                 USB_OTG_DOEPEACHMSK1_TOM_Msk  /*!< Timeout condition mask */
#define USB_OTG_DOEPEACHMSK1_ITTXFEMSK_Pos       (4U)
#define USB_OTG_DOEPEACHMSK1_ITTXFEMSK_Msk       (0x1UL << USB_OTG_DOEPEACHMSK1_ITTXFEMSK_Pos) /*!< 0x00000010 */
#define USB_OTG_DOEPEACHMSK1_ITTXFEMSK           USB_OTG_DOEPEACHMSK1_ITTXFEMSK_Msk /*!< IN token received when TxFIFO empty mask */
#define USB_OTG_DOEPEACHMSK1_INEPNMM_Pos         (5U)
#define USB_OTG_DOEPEACHMSK1_INEPNMM_Msk         (0x1UL << USB_OTG_DOEPEACHMSK1_INEPNMM_Pos) /*!< 0x00000020 */
#define USB_OTG_DOEPEACHMSK1_INEPNMM             USB_OTG_DOEPEACHMSK1_INEPNMM_Msk /*!< IN token received with EP mismatch mask */
#define USB_OTG_DOEPEACHMSK1_INEPNEM_Pos         (6U)
#define USB_OTG_DOEPEACHMSK1_INEPNEM_Msk         (0x1UL << USB_OTG_DOEPEACHMSK1_INEPNEM_Pos) /*!< 0x00000040 */
#define USB_OTG_DOEPEACHMSK1_INEPNEM             USB_OTG_DOEPEACHMSK1_INEPNEM_Msk /*!< IN endpoint NAK effective mask */
#define USB_OTG_DOEPEACHMSK1_TXFURM_Pos          (8U)
#define USB_OTG_DOEPEACHMSK1_TXFURM_Msk          (0x1UL << USB_OTG_DOEPEACHMSK1_TXFURM_Pos) /*!< 0x00000100 */
#define USB_OTG_DOEPEACHMSK1_TXFURM              USB_OTG_DOEPEACHMSK1_TXFURM_Msk /*!< OUT packet error mask */
#define USB_OTG_DOEPEACHMSK1_BIM_Pos             (9U)
#define USB_OTG_DOEPEACHMSK1_BIM_Msk             (0x1UL << USB_OTG_DOEPEACHMSK1_BIM_Pos) /*!< 0x00000200 */
#define USB_OTG_DOEPEACHMSK1_BIM                 USB_OTG_DOEPEACHMSK1_BIM_Msk  /*!< BNA interrupt mask */
#define USB_OTG_DOEPEACHMSK1_BERRM_Pos           (12U)
#define USB_OTG_DOEPEACHMSK1_BERRM_Msk           (0x1UL << USB_OTG_DOEPEACHMSK1_BERRM_Pos) /*!< 0x00001000 */
#define USB_OTG_DOEPEACHMSK1_BERRM               USB_OTG_DOEPEACHMSK1_BERRM_Msk /*!< Bubble error interrupt mask */
#define USB_OTG_DOEPEACHMSK1_NAKM_Pos            (13U)
#define USB_OTG_DOEPEACHMSK1_NAKM_Msk            (0x1UL << USB_OTG_DOEPEACHMSK1_NAKM_Pos) /*!< 0x00002000 */
#define USB_OTG_DOEPEACHMSK1_NAKM                USB_OTG_DOEPEACHMSK1_NAKM_Msk /*!< NAK interrupt mask */
#define USB_OTG_DOEPEACHMSK1_NYETM_Pos           (14U)
#define USB_OTG_DOEPEACHMSK1_NYETM_Msk           (0x1UL << USB_OTG_DOEPEACHMSK1_NYETM_Pos) /*!< 0x00004000 */
#define USB_OTG_DOEPEACHMSK1_NYETM               USB_OTG_DOEPEACHMSK1_NYETM_Msk /*!< NYET interrupt mask */

/********************  Bit definition forUSB_OTG_HPTXFSIZ register  ********************/
#define USB_OTG_HPTXFSIZ_PTXSA_Pos               (0U)
#define USB_OTG_HPTXFSIZ_PTXSA_Msk               (0xFFFFUL << USB_OTG_HPTXFSIZ_PTXSA_Pos) /*!< 0x0000FFFF */
#define USB_OTG_HPTXFSIZ_PTXSA                   USB_OTG_HPTXFSIZ_PTXSA_Msk    /*!< Host periodic TxFIFO start address */
#define USB_OTG_HPTXFSIZ_PTXFD_Pos               (16U)
#define USB_OTG_HPTXFSIZ_PTXFD_Msk               (0xFFFFUL << USB_OTG_HPTXFSIZ_PTXFD_Pos) /*!< 0xFFFF0000 */
#define USB_OTG_HPTXFSIZ_PTXFD                   USB_OTG_HPTXFSIZ_PTXFD_Msk    /*!< Host periodic TxFIFO depth */

/********************  Bit definition forUSB_OTG_DIEPCTL register  ********************/
#define USB_OTG_DIEPCTL_MPSIZ_Pos                (0U)
#define USB_OTG_DIEPCTL_MPSIZ_Msk                (0x7FFUL << USB_OTG_DIEPCTL_MPSIZ_Pos) /*!< 0x000007FF */
#define USB_OTG_DIEPCTL_MPSIZ                    USB_OTG_DIEPCTL_MPSIZ_Msk     /*!< Maximum packet size */
#define USB_OTG_DIEPCTL_USBAEP_Pos               (15U)
#define USB_OTG_DIEPCTL_USBAEP_Msk               (0x1UL << USB_OTG_DIEPCTL_USBAEP_Pos) /*!< 0x00008000 */
#define USB_OTG_DIEPCTL_USBAEP                   USB_OTG_DIEPCTL_USBAEP_Msk    /*!< USB active endpoint */
#define USB_OTG_DIEPCTL_EONUM_DPID_Pos           (16U)
#define USB_OTG_DIEPCTL_EONUM_DPID_Msk           (0x1UL << USB_OTG_DIEPCTL_EONUM_DPID_Pos) /*!< 0x00010000 */
#define USB_OTG_DIEPCTL_EONUM_DPID               USB_OTG_DIEPCTL_EONUM_DPID_Msk /*!< Even/odd frame */
#define USB_OTG_DIEPCTL_NAKSTS_Pos               (17U)
#define USB_OTG_DIEPCTL_NAKSTS_Msk               (0x1UL << USB_OTG_DIEPCTL_NAKSTS_Pos) /*!< 0x00020000 */
#define USB_OTG_DIEPCTL_NAKSTS                   USB_OTG_DIEPCTL_NAKSTS_Msk    /*!< NAK status */

#define USB_OTG_DIEPCTL_EPTYP_Pos                (18U)
#define USB_OTG_DIEPCTL_EPTYP_Msk                (0x3UL << USB_OTG_DIEPCTL_EPTYP_Pos) /*!< 0x000C0000 */
#define USB_OTG_DIEPCTL_EPTYP                    USB_OTG_DIEPCTL_EPTYP_Msk     /*!< Endpoint type */
#define USB_OTG_DIEPCTL_EPTYP_0                  (0x1UL << USB_OTG_DIEPCTL_EPTYP_Pos) /*!< 0x00040000 */
#define USB_OTG_DIEPCTL_EPTYP_1                  (0x2UL << USB_OTG_DIEPCTL_EPTYP_Pos) /*!< 0x00080000 */
#define USB_OTG_DIEPCTL_STALL_Pos                (21U)
#define USB_OTG_DIEPCTL_STALL_Msk                (0x1UL << USB_OTG_DIEPCTL_STALL_Pos) /*!< 0x00200000 */
#define USB_OTG_DIEPCTL_STALL                    USB_OTG_DIEPCTL_STALL_Msk     /*!< STALL handshake */

#define USB_OTG_DIEPCTL_TXFNUM_Pos               (22U)
#define USB_OTG_DIEPCTL_TXFNUM_Msk               (0xFUL << USB_OTG_DIEPCTL_TXFNUM_Pos) /*!< 0x03C00000 */
#define USB_OTG_DIEPCTL_TXFNUM                   USB_OTG_DIEPCTL_TXFNUM_Msk    /*!< TxFIFO number */
#define USB_OTG_DIEPCTL_TXFNUM_0                 (0x1UL << USB_OTG_DIEPCTL_TXFNUM_Pos) /*!< 0x00400000 */
#define USB_OTG_DIEPCTL_TXFNUM_1                 (0x2UL << USB_OTG_DIEPCTL_TXFNUM_Pos) /*!< 0x00800000 */
#define USB_OTG_DIEPCTL_TXFNUM_2                 (0x4UL << USB_OTG_DIEPCTL_TXFNUM_Pos) /*!< 0x01000000 */
#define USB_OTG_DIEPCTL_TXFNUM_3                 (0x8UL << USB_OTG_DIEPCTL_TXFNUM_Pos) /*!< 0x02000000 */
#define USB_OTG_DIEPCTL_CNAK_Pos                 (26U)
#define USB_OTG_DIEPCTL_CNAK_Msk                 (0x1UL << USB_OTG_DIEPCTL_CNAK_Pos) /*!< 0x04000000 */
#define USB_OTG_DIEPCTL_CNAK                     USB_OTG_DIEPCTL_CNAK_Msk      /*!< Clear NAK */
#define USB_OTG_DIEPCTL_SNAK_Pos                 (27U)
#define USB_OTG_DIEPCTL_SNAK_Msk                 (0x1UL << USB_OTG_DIEPCTL_SNAK_Pos) /*!< 0x08000000 */
#define USB_OTG_DIEPCTL_SNAK                     USB_OTG_DIEPCTL_SNAK_Msk      /*!< Set NAK */
#define USB_OTG_DIEPCTL_SD0PID_SEVNFRM_Pos       (28U)
#define USB_OTG_DIEPCTL_SD0PID_SEVNFRM_Msk       (0x1UL << USB_OTG_DIEPCTL_SD0PID_SEVNFRM_Pos) /*!< 0x10000000 */
#define USB_OTG_DIEPCTL_SD0PID_SEVNFRM           USB_OTG_DIEPCTL_SD0PID_SEVNFRM_Msk /*!< Set DATA0 PID */
#define USB_OTG_DIEPCTL_SODDFRM_Pos              (29U)
#define USB_OTG_DIEPCTL_SODDFRM_Msk              (0x1UL << USB_OTG_DIEPCTL_SODDFRM_Pos) /*!< 0x20000000 */
#define USB_OTG_DIEPCTL_SODDFRM                  USB_OTG_DIEPCTL_SODDFRM_Msk   /*!< Set odd frame */
#define USB_OTG_DIEPCTL_EPDIS_Pos                (30U)
#define USB_OTG_DIEPCTL_EPDIS_Msk                (0x1UL << USB_OTG_DIEPCTL_EPDIS_Pos) /*!< 0x40000000 */
#define USB_OTG_DIEPCTL_EPDIS                    USB_OTG_DIEPCTL_EPDIS_Msk     /*!< Endpoint disable */
#define USB_OTG_DIEPCTL_EPENA_Pos                (31U)
#define USB_OTG_DIEPCTL_EPENA_Msk                (0x1UL << USB_OTG_DIEPCTL_EPENA_Pos) /*!< 0x80000000 */
#define USB_OTG_DIEPCTL_EPENA                    USB_OTG_DIEPCTL_EPENA_Msk     /*!< Endpoint enable */

/********************  Bit definition forUSB_OTG_HCCHAR register  ********************/
#define USB_OTG_HCCHAR_MPSIZ_Pos                 (0U)
#define USB_OTG_HCCHAR_MPSIZ_Msk                 (0x7FFUL << USB_OTG_HCCHAR_MPSIZ_Pos) /*!< 0x000007FF */
#define USB_OTG_HCCHAR_MPSIZ                     USB_OTG_HCCHAR_MPSIZ_Msk      /*!< Maximum packet size */

#define USB_OTG_HCCHAR_EPNUM_Pos                 (11U)
#define USB_OTG_HCCHAR_EPNUM_Msk                 (0xFUL << USB_OTG_HCCHAR_EPNUM_Pos) /*!< 0x00007800 */
#define USB_OTG_HCCHAR_EPNUM                     USB_OTG_HCCHAR_EPNUM_Msk      /*!< Endpoint number */
#define USB_OTG_HCCHAR_EPNUM_0                   (0x1UL << USB_OTG_HCCHAR_EPNUM_Pos) /*!< 0x00000800 */
#define USB_OTG_HCCHAR_EPNUM_1                   (0x2UL << USB_OTG_HCCHAR_EPNUM_Pos) /*!< 0x00001000 */
#define USB_OTG_HCCHAR_EPNUM_2                   (0x4UL << USB_OTG_HCCHAR_EPNUM_Pos) /*!< 0x00002000 */
#define USB_OTG_HCCHAR_EPNUM_3                   (0x8UL << USB_OTG_HCCHAR_EPNUM_Pos) /*!< 0x00004000 */
#define USB_OTG_HCCHAR_EPDIR_Pos                 (15U)
#define USB_OTG_HCCHAR_EPDIR_Msk                 (0x1UL << USB_OTG_HCCHAR_EPDIR_Pos) /*!< 0x00008000 */
#define USB_OTG_HCCHAR_EPDIR                     USB_OTG_HCCHAR_EPDIR_Msk      /*!< Endpoint direction */
#define USB_OTG_HCCHAR_LSDEV_Pos                 (17U)
#define USB_OTG_HCCHAR_LSDEV_Msk                 (0x1UL << USB_OTG_HCCHAR_LSDEV_Pos) /*!< 0x00020000 */
#define USB_OTG_HCCHAR_LSDEV                     USB_OTG_HCCHAR_LSDEV_Msk      /*!< Low-speed device */

#define USB_OTG_HCCHAR_EPTYP_Pos                 (18U)
#define USB_OTG_HCCHAR_EPTYP_Msk                 (0x3UL << USB_OTG_HCCHAR_EPTYP_Pos) /*!< 0x000C0000 */
#define USB_OTG_HCCHAR_EPTYP                     USB_OTG_HCCHAR_EPTYP_Msk      /*!< Endpoint type */
#define USB_OTG_HCCHAR_EPTYP_0                   (0x1UL << USB_OTG_HCCHAR_EPTYP_Pos) /*!< 0x00040000 */
#define USB_OTG_HCCHAR_EPTYP_1                   (0x2UL << USB_OTG_HCCHAR_EPTYP_Pos) /*!< 0x00080000 */

#define USB_OTG_HCCHAR_MC_Pos                    (20U)
#define USB_OTG_HCCHAR_MC_Msk                    (0x3UL << USB_OTG_HCCHAR_MC_Pos) /*!< 0x00300000 */
#define USB_OTG_HCCHAR_MC                        USB_OTG_HCCHAR_MC_Msk         /*!< Multi Count (MC) / Error Count (EC) */
#define USB_OTG_HCCHAR_MC_0                      (0x1UL << USB_OTG_HCCHAR_MC_Pos) /*!< 0x00100000 */
#define USB_OTG_HCCHAR_MC_1                      (0x2UL << USB_OTG_HCCHAR_MC_Pos) /*!< 0x00200000 */

#define USB_OTG_HCCHAR_DAD_Pos                   (22U)
#define USB_OTG_HCCHAR_DAD_Msk                   (0x7FUL << USB_OTG_HCCHAR_DAD_Pos) /*!< 0x1FC00000 */
#define USB_OTG_HCCHAR_DAD                       USB_OTG_HCCHAR_DAD_Msk        /*!< Device address */
#define USB_OTG_HCCHAR_DAD_0                     (0x01UL << USB_OTG_HCCHAR_DAD_Pos) /*!< 0x00400000 */
#define USB_OTG_HCCHAR_DAD_1                     (0x02UL << USB_OTG_HCCHAR_DAD_Pos) /*!< 0x00800000 */
#define USB_OTG_HCCHAR_DAD_2                     (0x04UL << USB_OTG_HCCHAR_DAD_Pos) /*!< 0x01000000 */
#define USB_OTG_HCCHAR_DAD_3                     (0x08UL << USB_OTG_HCCHAR_DAD_Pos) /*!< 0x02000000 */
#define USB_OTG_HCCHAR_DAD_4                     (0x10UL << USB_OTG_HCCHAR_DAD_Pos) /*!< 0x04000000 */
#define USB_OTG_HCCHAR_DAD_5                     (0x20UL << USB_OTG_HCCHAR_DAD_Pos) /*!< 0x08000000 */
#define USB_OTG_HCCHAR_DAD_6                     (0x40UL << USB_OTG_HCCHAR_DAD_Pos) /*!< 0x10000000 */
#define USB_OTG_HCCHAR_ODDFRM_Pos                (29U)
#define USB_OTG_HCCHAR_ODDFRM_Msk                (0x1UL << USB_OTG_HCCHAR_ODDFRM_Pos) /*!< 0x20000000 */
#define USB_OTG_HCCHAR_ODDFRM                    USB_OTG_HCCHAR_ODDFRM_Msk     /*!< Odd frame */
#define USB_OTG_HCCHAR_CHDIS_Pos                 (30U)
#define USB_OTG_HCCHAR_CHDIS_Msk                 (0x1UL << USB_OTG_HCCHAR_CHDIS_Pos) /*!< 0x40000000 */
#define USB_OTG_HCCHAR_CHDIS                     USB_OTG_HCCHAR_CHDIS_Msk      /*!< Channel disable */
#define USB_OTG_HCCHAR_CHENA_Pos                 (31U)
#define USB_OTG_HCCHAR_CHENA_Msk                 (0x1UL << USB_OTG_HCCHAR_CHENA_Pos) /*!< 0x80000000 */
#define USB_OTG_HCCHAR_CHENA                     USB_OTG_HCCHAR_CHENA_Msk      /*!< Channel enable */

/********************  Bit definition forUSB_OTG_HCSPLT register  ********************/

#define USB_OTG_HCSPLT_PRTADDR_Pos               (0U)
#define USB_OTG_HCSPLT_PRTADDR_Msk               (0x7FUL << USB_OTG_HCSPLT_PRTADDR_Pos) /*!< 0x0000007F */
#define USB_OTG_HCSPLT_PRTADDR                   USB_OTG_HCSPLT_PRTADDR_Msk    /*!< Port address */
#define USB_OTG_HCSPLT_PRTADDR_0                 (0x01UL << USB_OTG_HCSPLT_PRTADDR_Pos) /*!< 0x00000001 */
#define USB_OTG_HCSPLT_PRTADDR_1                 (0x02UL << USB_OTG_HCSPLT_PRTADDR_Pos) /*!< 0x00000002 */
#define USB_OTG_HCSPLT_PRTADDR_2                 (0x04UL << USB_OTG_HCSPLT_PRTADDR_Pos) /*!< 0x00000004 */
#define USB_OTG_HCSPLT_PRTADDR_3                 (0x08UL << USB_OTG_HCSPLT_PRTADDR_Pos) /*!< 0x00000008 */
#define USB_OTG_HCSPLT_PRTADDR_4                 (0x10UL << USB_OTG_HCSPLT_PRTADDR_Pos) /*!< 0x00000010 */
#define USB_OTG_HCSPLT_PRTADDR_5                 (0x20UL << USB_OTG_HCSPLT_PRTADDR_Pos) /*!< 0x00000020 */
#define USB_OTG_HCSPLT_PRTADDR_6                 (0x40UL << USB_OTG_HCSPLT_PRTADDR_Pos) /*!< 0x00000040 */

#define USB_OTG_HCSPLT_HUBADDR_Pos               (7U)
#define USB_OTG_HCSPLT_HUBADDR_Msk               (0x7FUL << USB_OTG_HCSPLT_HUBADDR_Pos) /*!< 0x00003F80 */
#define USB_OTG_HCSPLT_HUBADDR                   USB_OTG_HCSPLT_HUBADDR_Msk    /*!< Hub address */
#define USB_OTG_HCSPLT_HUBADDR_0                 (0x01UL << USB_OTG_HCSPLT_HUBADDR_Pos) /*!< 0x00000080 */
#define USB_OTG_HCSPLT_HUBADDR_1                 (0x02UL << USB_OTG_HCSPLT_HUBADDR_Pos) /*!< 0x00000100 */
#define USB_OTG_HCSPLT_HUBADDR_2                 (0x04UL << USB_OTG_HCSPLT_HUBADDR_Pos) /*!< 0x00000200 */
#define USB_OTG_HCSPLT_HUBADDR_3                 (0x08UL << USB_OTG_HCSPLT_HUBADDR_Pos) /*!< 0x00000400 */
#define USB_OTG_HCSPLT_HUBADDR_4                 (0x10UL << USB_OTG_HCSPLT_HUBADDR_Pos) /*!< 0x00000800 */
#define USB_OTG_HCSPLT_HUBADDR_5                 (0x20UL << USB_OTG_HCSPLT_HUBADDR_Pos) /*!< 0x00001000 */
#define USB_OTG_HCSPLT_HUBADDR_6                 (0x40UL << USB_OTG_HCSPLT_HUBADDR_Pos) /*!< 0x00002000 */

#define USB_OTG_HCSPLT_XACTPOS_Pos               (14U)
#define USB_OTG_HCSPLT_XACTPOS_Msk               (0x3UL << USB_OTG_HCSPLT_XACTPOS_Pos) /*!< 0x0000C000 */
#define USB_OTG_HCSPLT_XACTPOS                   USB_OTG_HCSPLT_XACTPOS_Msk    /*!< XACTPOS */
#define USB_OTG_HCSPLT_XACTPOS_0                 (0x1UL << USB_OTG_HCSPLT_XACTPOS_Pos) /*!< 0x00004000 */
#define USB_OTG_HCSPLT_XACTPOS_1                 (0x2UL << USB_OTG_HCSPLT_XACTPOS_Pos) /*!< 0x00008000 */
#define USB_OTG_HCSPLT_COMPLSPLT_Pos             (16U)
#define USB_OTG_HCSPLT_COMPLSPLT_Msk             (0x1UL << USB_OTG_HCSPLT_COMPLSPLT_Pos) /*!< 0x00010000 */
#define USB_OTG_HCSPLT_COMPLSPLT                 USB_OTG_HCSPLT_COMPLSPLT_Msk  /*!< Do complete split */
#define USB_OTG_HCSPLT_SPLITEN_Pos               (31U)
#define USB_OTG_HCSPLT_SPLITEN_Msk               (0x1UL << USB_OTG_HCSPLT_SPLITEN_Pos) /*!< 0x80000000 */
#define USB_OTG_HCSPLT_SPLITEN                   USB_OTG_HCSPLT_SPLITEN_Msk    /*!< Split enable */

/********************  Bit definition forUSB_OTG_HCINT register  ********************/
#define USB_OTG_HCINT_XFRC_Pos                   (0U)
#define USB_OTG_HCINT_XFRC_Msk                   (0x1UL << USB_OTG_HCINT_XFRC_Pos) /*!< 0x00000001 */
#define USB_OTG_HCINT_XFRC                       USB_OTG_HCINT_XFRC_Msk        /*!< Transfer completed */
#define USB_OTG_HCINT_CHH_Pos                    (1U)
#define USB_OTG_HCINT_CHH_Msk                    (0x1UL << USB_OTG_HCINT_CHH_Pos) /*!< 0x00000002 */
#define USB_OTG_HCINT_CHH                        USB_OTG_HCINT_CHH_Msk         /*!< Channel halted */
#define USB_OTG_HCINT_AHBERR_Pos                 (2U)
#define USB_OTG_HCINT_AHBERR_Msk                 (0x1UL << USB_OTG_HCINT_AHBERR_Pos) /*!< 0x00000004 */
#define USB_OTG_HCINT_AHBERR                     USB_OTG_HCINT_AHBERR_Msk      /*!< AHB error */
#define USB_OTG_HCINT_STALL_Pos                  (3U)
#define USB_OTG_HCINT_STALL_Msk                  (0x1UL << USB_OTG_HCINT_STALL_Pos) /*!< 0x00000008 */
#define USB_OTG_HCINT_STALL                      USB_OTG_HCINT_STALL_Msk       /*!< STALL response received interrupt */
#define USB_OTG_HCINT_NAK_Pos                    (4U)
#define USB_OTG_HCINT_NAK_Msk                    (0x1UL << USB_OTG_HCINT_NAK_Pos) /*!< 0x00000010 */
#define USB_OTG_HCINT_NAK                        USB_OTG_HCINT_NAK_Msk         /*!< NAK response received interrupt */
#define USB_OTG_HCINT_ACK_Pos                    (5U)
#define USB_OTG_HCINT_ACK_Msk                    (0x1UL << USB_OTG_HCINT_ACK_Pos) /*!< 0x00000020 */
#define USB_OTG_HCINT_ACK                        USB_OTG_HCINT_ACK_Msk         /*!< ACK response received/transmitted interrupt */
#define USB_OTG_HCINT_NYET_Pos                   (6U)
#define USB_OTG_HCINT_NYET_Msk                   (0x1UL << USB_OTG_HCINT_NYET_Pos) /*!< 0x00000040 */
#define USB_OTG_HCINT_NYET                       USB_OTG_HCINT_NYET_Msk        /*!< Response received interrupt */
#define USB_OTG_HCINT_TXERR_Pos                  (7U)
#define USB_OTG_HCINT_TXERR_Msk                  (0x1UL << USB_OTG_HCINT_TXERR_Pos) /*!< 0x00000080 */
#define USB_OTG_HCINT_TXERR                      USB_OTG_HCINT_TXERR_Msk       /*!< Transaction error */
#define USB_OTG_HCINT_BBERR_Pos                  (8U)
#define USB_OTG_HCINT_BBERR_Msk                  (0x1UL << USB_OTG_HCINT_BBERR_Pos) /*!< 0x00000100 */
#define USB_OTG_HCINT_BBERR                      USB_OTG_HCINT_BBERR_Msk       /*!< Babble error */
#define USB_OTG_HCINT_FRMOR_Pos                  (9U)
#define USB_OTG_HCINT_FRMOR_Msk                  (0x1UL << USB_OTG_HCINT_FRMOR_Pos) /*!< 0x00000200 */
#define USB_OTG_HCINT_FRMOR                      USB_OTG_HCINT_FRMOR_Msk       /*!< Frame overrun */
#define USB_OTG_HCINT_DTERR_Pos                  (10U)
#define USB_OTG_HCINT_DTERR_Msk                  (0x1UL << USB_OTG_HCINT_DTERR_Pos) /*!< 0x00000400 */
#define USB_OTG_HCINT_DTERR                      USB_OTG_HCINT_DTERR_Msk       /*!< Data toggle error */

/********************  Bit definition forUSB_OTG_DIEPINT register  ********************/
#define USB_OTG_DIEPINT_XFRC_Pos                 (0U)
#define USB_OTG_DIEPINT_XFRC_Msk                 (0x1UL << USB_OTG_DIEPINT_XFRC_Pos) /*!< 0x00000001 */
#define USB_OTG_DIEPINT_XFRC                     USB_OTG_DIEPINT_XFRC_Msk      /*!< Transfer completed interrupt */
#define USB_OTG_DIEPINT_EPDISD_Pos               (1U)
#define USB_OTG_DIEPINT_EPDISD_Msk               (0x1UL << USB_OTG_DIEPINT_EPDISD_Pos) /*!< 0x00000002 */
#define USB_OTG_DIEPINT_EPDISD                   USB_OTG_DIEPINT_EPDISD_Msk    /*!< Endpoint disabled interrupt */
#define USB_OTG_DIEPINT_TOC_Pos                  (3U)
#define USB_OTG_DIEPINT_TOC_Msk                  (0x1UL << USB_OTG_DIEPINT_TOC_Pos) /*!< 0x00000008 */
#define USB_OTG_DIEPINT_TOC                      USB_OTG_DIEPINT_TOC_Msk       /*!< Timeout condition */
#define USB_OTG_DIEPINT_ITTXFE_Pos               (4U)
#define USB_OTG_DIEPINT_ITTXFE_Msk               (0x1UL << USB_OTG_DIEPINT_ITTXFE_Pos) /*!< 0x00000010 */
#define USB_OTG_DIEPINT_ITTXFE                   USB_OTG_DIEPINT_ITTXFE_Msk    /*!< IN token received when TxFIFO is empty */
#define USB_OTG_DIEPINT_INEPNE_Pos               (6U)
#define USB_OTG_DIEPINT_INEPNE_Msk               (0x1UL << USB_OTG_DIEPINT_INEPNE_Pos) /*!< 0x00000040 */
#define USB_OTG_DIEPINT_INEPNE                   USB_OTG_DIEPINT_INEPNE_Msk    /*!< IN endpoint NAK effective */
#define USB_OTG_DIEPINT_TXFE_Pos                 (7U)
#define USB_OTG_DIEPINT_TXFE_Msk                 (0x1UL << USB_OTG_DIEPINT_TXFE_Pos) /*!< 0x00000080 */
#define USB_OTG_DIEPINT_TXFE                     USB_OTG_DIEPINT_TXFE_Msk      /*!< Transmit FIFO empty */
#define USB_OTG_DIEPINT_TXFIFOUDRN_Pos           (8U)
#define USB_OTG_DIEPINT_TXFIFOUDRN_Msk           (0x1UL << USB_OTG_DIEPINT_TXFIFOUDRN_Pos) /*!< 0x00000100 */
#define USB_OTG_DIEPINT_TXFIFOUDRN               USB_OTG_DIEPINT_TXFIFOUDRN_Msk /*!< Transmit Fifo Underrun */
#define USB_OTG_DIEPINT_BNA_Pos                  (9U)
#define USB_OTG_DIEPINT_BNA_Msk                  (0x1UL << USB_OTG_DIEPINT_BNA_Pos) /*!< 0x00000200 */
#define USB_OTG_DIEPINT_BNA                      USB_OTG_DIEPINT_BNA_Msk       /*!< Buffer not available interrupt */
#define USB_OTG_DIEPINT_PKTDRPSTS_Pos            (11U)
#define USB_OTG_DIEPINT_PKTDRPSTS_Msk            (0x1UL << USB_OTG_DIEPINT_PKTDRPSTS_Pos) /*!< 0x00000800 */
#define USB_OTG_DIEPINT_PKTDRPSTS                USB_OTG_DIEPINT_PKTDRPSTS_Msk /*!< Packet dropped status */
#define USB_OTG_DIEPINT_BERR_Pos                 (12U)
#define USB_OTG_DIEPINT_BERR_Msk                 (0x1UL << USB_OTG_DIEPINT_BERR_Pos) /*!< 0x00001000 */
#define USB_OTG_DIEPINT_BERR                     USB_OTG_DIEPINT_BERR_Msk      /*!< Babble error interrupt */
#define USB_OTG_DIEPINT_NAK_Pos                  (13U)
#define USB_OTG_DIEPINT_NAK_Msk                  (0x1UL << USB_OTG_DIEPINT_NAK_Pos) /*!< 0x00002000 */
#define USB_OTG_DIEPINT_NAK                      USB_OTG_DIEPINT_NAK_Msk       /*!< NAK interrupt */

/********************  Bit definition forUSB_OTG_HCINTMSK register  ********************/
#define USB_OTG_HCINTMSK_XFRCM_Pos               (0U)
#define USB_OTG_HCINTMSK_XFRCM_Msk               (0x1UL << USB_OTG_HCINTMSK_XFRCM_Pos) /*!< 0x00000001 */
#define USB_OTG_HCINTMSK_XFRCM                   USB_OTG_HCINTMSK_XFRCM_Msk    /*!< Transfer completed mask */
#define USB_OTG_HCINTMSK_CHHM_Pos                (1U)
#define USB_OTG_HCINTMSK_CHHM_Msk                (0x1UL << USB_OTG_HCINTMSK_CHHM_Pos) /*!< 0x00000002 */
#define USB_OTG_HCINTMSK_CHHM                    USB_OTG_HCINTMSK_CHHM_Msk     /*!< Channel halted mask */
#define USB_OTG_HCINTMSK_AHBERR_Pos              (2U)
#define USB_OTG_HCINTMSK_AHBERR_Msk              (0x1UL << USB_OTG_HCINTMSK_AHBERR_Pos) /*!< 0x00000004 */
#define USB_OTG_HCINTMSK_AHBERR                  USB_OTG_HCINTMSK_AHBERR_Msk   /*!< AHB error */
#define USB_OTG_HCINTMSK_STALLM_Pos              (3U)
#define USB_OTG_HCINTMSK_STALLM_Msk              (0x1UL << USB_OTG_HCINTMSK_STALLM_Pos) /*!< 0x00000008 */
#define USB_OTG_HCINTMSK_STALLM                  USB_OTG_HCINTMSK_STALLM_Msk   /*!< STALL response received interrupt mask */
#define USB_OTG_HCINTMSK_NAKM_Pos                (4U)
#define USB_OTG_HCINTMSK_NAKM_Msk                (0x1UL << USB_OTG_HCINTMSK_NAKM_Pos) /*!< 0x00000010 */
#define USB_OTG_HCINTMSK_NAKM                    USB_OTG_HCINTMSK_NAKM_Msk     /*!< NAK response received interrupt mask */
#define USB_OTG_HCINTMSK_ACKM_Pos                (5U)
#define USB_OTG_HCINTMSK_ACKM_Msk                (0x1UL << USB_OTG_HCINTMSK_ACKM_Pos) /*!< 0x00000020 */
#define USB_OTG_HCINTMSK_ACKM                    USB_OTG_HCINTMSK_ACKM_Msk     /*!< ACK response received/transmitted interrupt mask */
#define USB_OTG_HCINTMSK_NYET_Pos                (6U)
#define USB_OTG_HCINTMSK_NYET_Msk                (0x1UL << USB_OTG_HCINTMSK_NYET_Pos) /*!< 0x00000040 */
#define USB_OTG_HCINTMSK_NYET                    USB_OTG_HCINTMSK_NYET_Msk     /*!< response received interrupt mask */
#define USB_OTG_HCINTMSK_TXERRM_Pos              (7U)
#define USB_OTG_HCINTMSK_TXERRM_Msk              (0x1UL << USB_OTG_HCINTMSK_TXERRM_Pos) /*!< 0x00000080 */
#define USB_OTG_HCINTMSK_TXERRM                  USB_OTG_HCINTMSK_TXERRM_Msk   /*!< Transaction error mask */
#define USB_OTG_HCINTMSK_BBERRM_Pos              (8U)
#define USB_OTG_HCINTMSK_BBERRM_Msk              (0x1UL << USB_OTG_HCINTMSK_BBERRM_Pos) /*!< 0x00000100 */
#define USB_OTG_HCINTMSK_BBERRM                  USB_OTG_HCINTMSK_BBERRM_Msk   /*!< Babble error mask */
#define USB_OTG_HCINTMSK_FRMORM_Pos              (9U)
#define USB_OTG_HCINTMSK_FRMORM_Msk              (0x1UL << USB_OTG_HCINTMSK_FRMORM_Pos) /*!< 0x00000200 */
#define USB_OTG_HCINTMSK_FRMORM                  USB_OTG_HCINTMSK_FRMORM_Msk   /*!< Frame overrun mask */
#define USB_OTG_HCINTMSK_DTERRM_Pos              (10U)
#define USB_OTG_HCINTMSK_DTERRM_Msk              (0x1UL << USB_OTG_HCINTMSK_DTERRM_Pos) /*!< 0x00000400 */
#define USB_OTG_HCINTMSK_DTERRM                  USB_OTG_HCINTMSK_DTERRM_Msk   /*!< Data toggle error mask */

/********************  Bit definition for USB_OTG_DIEPTSIZ register  ********************/

#define USB_OTG_DIEPTSIZ_XFRSIZ_Pos              (0U)
#define USB_OTG_DIEPTSIZ_XFRSIZ_Msk              (0x7FFFFUL << USB_OTG_DIEPTSIZ_XFRSIZ_Pos) /*!< 0x0007FFFF */
#define USB_OTG_DIEPTSIZ_XFRSIZ                  USB_OTG_DIEPTSIZ_XFRSIZ_Msk   /*!< Transfer size */
#define USB_OTG_DIEPTSIZ_PKTCNT_Pos              (19U)
#define USB_OTG_DIEPTSIZ_PKTCNT_Msk              (0x3FFUL << USB_OTG_DIEPTSIZ_PKTCNT_Pos) /*!< 0x1FF80000 */
#define USB_OTG_DIEPTSIZ_PKTCNT                  USB_OTG_DIEPTSIZ_PKTCNT_Msk   /*!< Packet count */
#define USB_OTG_DIEPTSIZ_MULCNT_Pos              (29U)
#define USB_OTG_DIEPTSIZ_MULCNT_Msk              (0x3UL << USB_OTG_DIEPTSIZ_MULCNT_Pos) /*!< 0x60000000 */
#define USB_OTG_DIEPTSIZ_MULCNT                  USB_OTG_DIEPTSIZ_MULCNT_Msk   /*!< Packet count */
/********************  Bit definition forUSB_OTG_HCTSIZ register  ********************/
#define USB_OTG_HCTSIZ_XFRSIZ_Pos                (0U)
#define USB_OTG_HCTSIZ_XFRSIZ_Msk                (0x7FFFFUL << USB_OTG_HCTSIZ_XFRSIZ_Pos) /*!< 0x0007FFFF */
#define USB_OTG_HCTSIZ_XFRSIZ                    USB_OTG_HCTSIZ_XFRSIZ_Msk     /*!< Transfer size */
#define USB_OTG_HCTSIZ_PKTCNT_Pos                (19U)
#define USB_OTG_HCTSIZ_PKTCNT_Msk                (0x3FFUL << USB_OTG_HCTSIZ_PKTCNT_Pos) /*!< 0x1FF80000 */
#define USB_OTG_HCTSIZ_PKTCNT                    USB_OTG_HCTSIZ_PKTCNT_Msk     /*!< Packet count */
#define USB_OTG_HCTSIZ_DOPING_Pos                (31U)
#define USB_OTG_HCTSIZ_DOPING_Msk                (0x1UL << USB_OTG_HCTSIZ_DOPING_Pos) /*!< 0x80000000 */
#define USB_OTG_HCTSIZ_DOPING                    USB_OTG_HCTSIZ_DOPING_Msk     /*!< Do PING */
#define USB_OTG_HCTSIZ_DPID_Pos                  (29U)
#define USB_OTG_HCTSIZ_DPID_Msk                  (0x3UL << USB_OTG_HCTSIZ_DPID_Pos) /*!< 0x60000000 */
#define USB_OTG_HCTSIZ_DPID                      USB_OTG_HCTSIZ_DPID_Msk       /*!< Data PID */
#define USB_OTG_HCTSIZ_DPID_0                    (0x1UL << USB_OTG_HCTSIZ_DPID_Pos) /*!< 0x20000000 */
#define USB_OTG_HCTSIZ_DPID_1                    (0x2UL << USB_OTG_HCTSIZ_DPID_Pos) /*!< 0x40000000 */

/********************  Bit definition forUSB_OTG_DIEPDMA register  ********************/
#define USB_OTG_DIEPDMA_DMAADDR_Pos              (0U)
#define USB_OTG_DIEPDMA_DMAADDR_Msk              (0xFFFFFFFFUL << USB_OTG_DIEPDMA_DMAADDR_Pos) /*!< 0xFFFFFFFF */
#define USB_OTG_DIEPDMA_DMAADDR                  USB_OTG_DIEPDMA_DMAADDR_Msk   /*!< DMA address */

/********************  Bit definition forUSB_OTG_HCDMA register  ********************/
#define USB_OTG_HCDMA_DMAADDR_Pos                (0U)
#define USB_OTG_HCDMA_DMAADDR_Msk                (0xFFFFFFFFUL << USB_OTG_HCDMA_DMAADDR_Pos) /*!< 0xFFFFFFFF */
#define USB_OTG_HCDMA_DMAADDR                    USB_OTG_HCDMA_DMAADDR_Msk     /*!< DMA address */

/********************  Bit definition forUSB_OTG_DTXFSTS register  ********************/
#define USB_OTG_DTXFSTS_INEPTFSAV_Pos            (0U)
#define USB_OTG_DTXFSTS_INEPTFSAV_Msk            (0xFFFFUL << USB_OTG_DTXFSTS_INEPTFSAV_Pos) /*!< 0x0000FFFF */
#define USB_OTG_DTXFSTS_INEPTFSAV                USB_OTG_DTXFSTS_INEPTFSAV_Msk /*!< IN endpoint TxFIFO space available */

/********************  Bit definition forUSB_OTG_DIEPTXF register  ********************/
#define USB_OTG_DIEPTXF_INEPTXSA_Pos             (0U)
#define USB_OTG_DIEPTXF_INEPTXSA_Msk             (0xFFFFUL << USB_OTG_DIEPTXF_INEPTXSA_Pos) /*!< 0x0000FFFF */
#define USB_OTG_DIEPTXF_INEPTXSA                 USB_OTG_DIEPTXF_INEPTXSA_Msk  /*!< IN endpoint FIFOx transmit RAM start address */
#define USB_OTG_DIEPTXF_INEPTXFD_Pos             (16U)
#define USB_OTG_DIEPTXF_INEPTXFD_Msk             (0xFFFFUL << USB_OTG_DIEPTXF_INEPTXFD_Pos) /*!< 0xFFFF0000 */
#define USB_OTG_DIEPTXF_INEPTXFD                 USB_OTG_DIEPTXF_INEPTXFD_Msk  /*!< IN endpoint TxFIFO depth */

/********************  Bit definition forUSB_OTG_DOEPCTL register  ********************/

#define USB_OTG_DOEPCTL_MPSIZ_Pos                (0U)
#define USB_OTG_DOEPCTL_MPSIZ_Msk                (0x7FFUL << USB_OTG_DOEPCTL_MPSIZ_Pos) /*!< 0x000007FF */
#define USB_OTG_DOEPCTL_MPSIZ                    USB_OTG_DOEPCTL_MPSIZ_Msk     /*!< Maximum packet size */          /*!<Bit 1 */
#define USB_OTG_DOEPCTL_USBAEP_Pos               (15U)
#define USB_OTG_DOEPCTL_USBAEP_Msk               (0x1UL << USB_OTG_DOEPCTL_USBAEP_Pos) /*!< 0x00008000 */
#define USB_OTG_DOEPCTL_USBAEP                   USB_OTG_DOEPCTL_USBAEP_Msk    /*!< USB active endpoint */
#define USB_OTG_DOEPCTL_NAKSTS_Pos               (17U)
#define USB_OTG_DOEPCTL_NAKSTS_Msk               (0x1UL << USB_OTG_DOEPCTL_NAKSTS_Pos) /*!< 0x00020000 */
#define USB_OTG_DOEPCTL_NAKSTS                   USB_OTG_DOEPCTL_NAKSTS_Msk    /*!< NAK status */
#define USB_OTG_DOEPCTL_SD0PID_SEVNFRM_Pos       (28U)
#define USB_OTG_DOEPCTL_SD0PID_SEVNFRM_Msk       (0x1UL << USB_OTG_DOEPCTL_SD0PID_SEVNFRM_Pos) /*!< 0x10000000 */
#define USB_OTG_DOEPCTL_SD0PID_SEVNFRM           USB_OTG_DOEPCTL_SD0PID_SEVNFRM_Msk /*!< Set DATA0 PID */
#define USB_OTG_DOEPCTL_SODDFRM_Pos              (29U)
#define USB_OTG_DOEPCTL_SODDFRM_Msk              (0x1UL << USB_OTG_DOEPCTL_SODDFRM_Pos) /*!< 0x20000000 */
#define USB_OTG_DOEPCTL_SODDFRM                  USB_OTG_DOEPCTL_SODDFRM_Msk   /*!< Set odd frame */
#define USB_OTG_DOEPCTL_EPTYP_Pos                (18U)
#define USB_OTG_DOEPCTL_EPTYP_Msk                (0x3UL << USB_OTG_DOEPCTL_EPTYP_Pos) /*!< 0x000C0000 */
#define USB_OTG_DOEPCTL_EPTYP                    USB_OTG_DOEPCTL_EPTYP_Msk     /*!< Endpoint type */
#define USB_OTG_DOEPCTL_EPTYP_0                  (0x1UL << USB_OTG_DOEPCTL_EPTYP_Pos) /*!< 0x00040000 */
#define USB_OTG_DOEPCTL_EPTYP_1                  (0x2UL << USB_OTG_DOEPCTL_EPTYP_Pos) /*!< 0x00080000 */
#define USB_OTG_DOEPCTL_SNPM_Pos                 (20U)
#define USB_OTG_DOEPCTL_SNPM_Msk                 (0x1UL << USB_OTG_DOEPCTL_SNPM_Pos) /*!< 0x00100000 */
#define USB_OTG_DOEPCTL_SNPM                     USB_OTG_DOEPCTL_SNPM_Msk      /*!< Snoop mode */
#define USB_OTG_DOEPCTL_STALL_Pos                (21U)
#define USB_OTG_DOEPCTL_STALL_Msk                (0x1UL << USB_OTG_DOEPCTL_STALL_Pos) /*!< 0x00200000 */
#define USB_OTG_DOEPCTL_STALL                    USB_OTG_DOEPCTL_STALL_Msk     /*!< STALL handshake */
#define USB_OTG_DOEPCTL_CNAK_Pos                 (26U)
#define USB_OTG_DOEPCTL_CNAK_Msk                 (0x1UL << USB_OTG_DOEPCTL_CNAK_Pos) /*!< 0x04000000 */
#define USB_OTG_DOEPCTL_CNAK                     USB_OTG_DOEPCTL_CNAK_Msk      /*!< Clear NAK */
#define USB_OTG_DOEPCTL_SNAK_Pos                 (27U)
#define USB_OTG_DOEPCTL_SNAK_Msk                 (0x1UL << USB_OTG_DOEPCTL_SNAK_Pos) /*!< 0x08000000 */
#define USB_OTG_DOEPCTL_SNAK                     USB_OTG_DOEPCTL_SNAK_Msk      /*!< Set NAK */
#define USB_OTG_DOEPCTL_EPDIS_Pos                (30U)
#define USB_OTG_DOEPCTL_EPDIS_Msk                (0x1UL << USB_OTG_DOEPCTL_EPDIS_Pos) /*!< 0x40000000 */
#define USB_OTG_DOEPCTL_EPDIS                    USB_OTG_DOEPCTL_EPDIS_Msk     /*!< Endpoint disable */
#define USB_OTG_DOEPCTL_EPENA_Pos                (31U)
#define USB_OTG_DOEPCTL_EPENA_Msk                (0x1UL << USB_OTG_DOEPCTL_EPENA_Pos) /*!< 0x80000000 */
#define USB_OTG_DOEPCTL_EPENA                    USB_OTG_DOEPCTL_EPENA_Msk     /*!< Endpoint enable */

/********************  Bit definition forUSB_OTG_DOEPINT register  ********************/
#define USB_OTG_DOEPINT_XFRC_Pos                 (0U)
#define USB_OTG_DOEPINT_XFRC_Msk                 (0x1UL << USB_OTG_DOEPINT_XFRC_Pos) /*!< 0x00000001 */
#define USB_OTG_DOEPINT_XFRC                     USB_OTG_DOEPINT_XFRC_Msk      /*!< Transfer completed interrupt */
#define USB_OTG_DOEPINT_EPDISD_Pos               (1U)
#define USB_OTG_DOEPINT_EPDISD_Msk               (0x1UL << USB_OTG_DOEPINT_EPDISD_Pos) /*!< 0x00000002 */
#define USB_OTG_DOEPINT_EPDISD                   USB_OTG_DOEPINT_EPDISD_Msk    /*!< Endpoint disabled interrupt */
#define USB_OTG_DOEPINT_STUP_Pos                 (3U)
#define USB_OTG_DOEPINT_STUP_Msk                 (0x1UL << USB_OTG_DOEPINT_STUP_Pos) /*!< 0x00000008 */
#define USB_OTG_DOEPINT_STUP                     USB_OTG_DOEPINT_STUP_Msk      /*!< SETUP phase done */
#define USB_OTG_DOEPINT_OTEPDIS_Pos              (4U)
#define USB_OTG_DOEPINT_OTEPDIS_Msk              (0x1UL << USB_OTG_DOEPINT_OTEPDIS_Pos) /*!< 0x00000010 */
#define USB_OTG_DOEPINT_OTEPDIS                  USB_OTG_DOEPINT_OTEPDIS_Msk   /*!< OUT token received when endpoint disabled */
#define USB_OTG_DOEPINT_B2BSTUP_Pos              (6U)
#define USB_OTG_DOEPINT_B2BSTUP_Msk              (0x1UL << USB_OTG_DOEPINT_B2BSTUP_Pos) /*!< 0x00000040 */
#define USB_OTG_DOEPINT_B2BSTUP                  USB_OTG_DOEPINT_B2BSTUP_Msk   /*!< Back-to-back SETUP packets received */
#define USB_OTG_DOEPINT_NYET_Pos                 (14U)
#define USB_OTG_DOEPINT_NYET_Msk                 (0x1UL << USB_OTG_DOEPINT_NYET_Pos) /*!< 0x00004000 */
#define USB_OTG_DOEPINT_NYET                     USB_OTG_DOEPINT_NYET_Msk      /*!< NYET interrupt */

/********************  Bit definition forUSB_OTG_DOEPTSIZ register  ********************/

#define USB_OTG_DOEPTSIZ_XFRSIZ_Pos              (0U)
#define USB_OTG_DOEPTSIZ_XFRSIZ_Msk              (0x7FFFFUL << USB_OTG_DOEPTSIZ_XFRSIZ_Pos) /*!< 0x0007FFFF */
#define USB_OTG_DOEPTSIZ_XFRSIZ                  USB_OTG_DOEPTSIZ_XFRSIZ_Msk   /*!< Transfer size */
#define USB_OTG_DOEPTSIZ_PKTCNT_Pos              (19U)
#define USB_OTG_DOEPTSIZ_PKTCNT_Msk              (0x3FFUL << USB_OTG_DOEPTSIZ_PKTCNT_Pos) /*!< 0x1FF80000 */
#define USB_OTG_DOEPTSIZ_PKTCNT                  USB_OTG_DOEPTSIZ_PKTCNT_Msk   /*!< Packet count */

#define USB_OTG_DOEPTSIZ_STUPCNT_Pos             (29U)
#define USB_OTG_DOEPTSIZ_STUPCNT_Msk             (0x3UL << USB_OTG_DOEPTSIZ_STUPCNT_Pos) /*!< 0x60000000 */
#define USB_OTG_DOEPTSIZ_STUPCNT                 USB_OTG_DOEPTSIZ_STUPCNT_Msk  /*!< SETUP packet count */
#define USB_OTG_DOEPTSIZ_STUPCNT_0               (0x1UL << USB_OTG_DOEPTSIZ_STUPCNT_Pos) /*!< 0x20000000 */
#define USB_OTG_DOEPTSIZ_STUPCNT_1               (0x2UL << USB_OTG_DOEPTSIZ_STUPCNT_Pos) /*!< 0x40000000 */

/********************  Bit definition for PCGCCTL register  ********************/
#define USB_OTG_PCGCCTL_STOPCLK_Pos              (0U)
#define USB_OTG_PCGCCTL_STOPCLK_Msk              (0x1UL << USB_OTG_PCGCCTL_STOPCLK_Pos) /*!< 0x00000001 */
#define USB_OTG_PCGCCTL_STOPCLK                  USB_OTG_PCGCCTL_STOPCLK_Msk   /*!< SETUP packet count */
#define USB_OTG_PCGCCTL_GATECLK_Pos              (1U)
#define USB_OTG_PCGCCTL_GATECLK_Msk              (0x1UL << USB_OTG_PCGCCTL_GATECLK_Pos) /*!< 0x00000002 */
#define USB_OTG_PCGCCTL_GATECLK                  USB_OTG_PCGCCTL_GATECLK_Msk   /*!<Bit 0 */
#define USB_OTG_PCGCCTL_PHYSUSP_Pos              (4U)
#define USB_OTG_PCGCCTL_PHYSUSP_Msk              (0x1UL << USB_OTG_PCGCCTL_PHYSUSP_Pos) /*!< 0x00000010 */
#define USB_OTG_PCGCCTL_PHYSUSP                  USB_OTG_PCGCCTL_PHYSUSP_Msk   /*!<Bit 1 */


/******************************************************************************/
/*                                                                            */
/*                   USBPHYC block description (USBPHYC)                    */
/*                                                                            */
/******************************************************************************/
/*****************  Bit definition for USBPHYC_PLL register  *****************/
#define USBPHYC_PLL_PLLNDIV_Pos          (0U)
#define USBPHYC_PLL_PLLNDIV_Msk          (0x7FUL << USBPHYC_PLL_PLLNDIV_Pos)             /*!< 0x0000007F */
#define USBPHYC_PLL_PLLNDIV              USBPHYC_PLL_PLLNDIV_Msk                        /*!< Loop division factor of PLL (integer part) */
#define USBPHYC_PLL_PLLNDIV_0            (0x1UL << USBPHYC_PLL_PLLNDIV_Pos)              /*!< 0x00000001 */
#define USBPHYC_PLL_PLLNDIV_1            (0x2UL << USBPHYC_PLL_PLLNDIV_Pos)              /*!< 0x00000002 */
#define USBPHYC_PLL_PLLNDIV_2            (0x4UL << USBPHYC_PLL_PLLNDIV_Pos)              /*!< 0x00000004 */
#define USBPHYC_PLL_PLLNDIV_3            (0x8UL << USBPHYC_PLL_PLLNDIV_Pos)              /*!< 0x00000008 */
#define USBPHYC_PLL_PLLNDIV_4            (0x10UL << USBPHYC_PLL_PLLNDIV_Pos)             /*!< 0x00000010 */
#define USBPHYC_PLL_PLLNDIV_5            (0x20UL << USBPHYC_PLL_PLLNDIV_Pos)             /*!< 0x00000020 */
#define USBPHYC_PLL_PLLNDIV_6            (0x40UL << USBPHYC_PLL_PLLNDIV_Pos)             /*!< 0x00000040 */
#define USBPHYC_PLL_PLLODF_Pos           (7U)
#define USBPHYC_PLL_PLLODF_Msk           (0x7UL << USBPHYC_PLL_PLLODF_Pos)               /*!< 0x00000380 */
#define USBPHYC_PLL_PLLODF               USBPHYC_PLL_PLLODF_Msk                         /*!< PLL output division factor */
#define USBPHYC_PLL_PLLODF_0             (0x1UL << USBPHYC_PLL_PLLODF_Pos)              /*!< 0x00000080 */
#define USBPHYC_PLL_PLLODF_1             (0x2UL << USBPHYC_PLL_PLLODF_Pos)             /*!< 0x00000100 */
#define USBPHYC_PLL_PLLODF_2             (0x4UL << USBPHYC_PLL_PLLODF_Pos)             /*!< 0x00000200 */
#define USBPHYC_PLL_PLLFRACIN_Pos        (10U)
#define USBPHYC_PLL_PLLFRACIN_Msk        (0xFFFFUL << USBPHYC_PLL_PLLFRACIN_Pos)         /*!< 0x03FFFC00 */
#define USBPHYC_PLL_PLLFRACIN            USBPHYC_PLL_PLLFRACIN_Msk                      /*!< PLL fractional input */
#define USBPHYC_PLL_PLLFRACIN_0          (0x1UL << USBPHYC_PLL_PLLFRACIN_Pos)          /*!< 0x00000400 */
#define USBPHYC_PLL_PLLFRACIN_1          (0x2UL << USBPHYC_PLL_PLLFRACIN_Pos)          /*!< 0x00000800 */
#define USBPHYC_PLL_PLLFRACIN_2          (0x4UL << USBPHYC_PLL_PLLFRACIN_Pos)         /*!< 0x00001000 */
#define USBPHYC_PLL_PLLFRACIN_3          (0x8UL << USBPHYC_PLL_PLLFRACIN_Pos)         /*!< 0x00002000 */
#define USBPHYC_PLL_PLLFRACIN_4          (0x10UL << USBPHYC_PLL_PLLFRACIN_Pos)         /*!< 0x00004000 */
#define USBPHYC_PLL_PLLFRACIN_5          (0x20UL << USBPHYC_PLL_PLLFRACIN_Pos)         /*!< 0x00008000 */
#define USBPHYC_PLL_PLLFRACIN_6          (0x40UL << USBPHYC_PLL_PLLFRACIN_Pos)        /*!< 0x00010000 */
#define USBPHYC_PLL_PLLFRACIN_7          (0x80UL << USBPHYC_PLL_PLLFRACIN_Pos)        /*!< 0x00020000 */
#define USBPHYC_PLL_PLLFRACIN_8          (0x100UL << USBPHYC_PLL_PLLFRACIN_Pos)        /*!< 0x00040000 */
#define USBPHYC_PLL_PLLFRACIN_9          (0x200UL << USBPHYC_PLL_PLLFRACIN_Pos)        /*!< 0x00080000 */
#define USBPHYC_PLL_PLLFRACIN_10         (0x400UL << USBPHYC_PLL_PLLFRACIN_Pos)       /*!< 0x00100000 */
#define USBPHYC_PLL_PLLFRACIN_11         (0x800UL << USBPHYC_PLL_PLLFRACIN_Pos)       /*!< 0x00200000 */
#define USBPHYC_PLL_PLLFRACIN_12         (0x1000UL << USBPHYC_PLL_PLLFRACIN_Pos)       /*!< 0x00400000 */
#define USBPHYC_PLL_PLLFRACIN_13         (0x2000UL << USBPHYC_PLL_PLLFRACIN_Pos)       /*!< 0x00800000 */
#define USBPHYC_PLL_PLLFRACIN_14         (0x4000UL << USBPHYC_PLL_PLLFRACIN_Pos)      /*!< 0x01000000 */
#define USBPHYC_PLL_PLLFRACIN_15         (0x8000UL << USBPHYC_PLL_PLLFRACIN_Pos)      /*!< 0x02000000 */
#define USBPHYC_PLL_PLLEN_Pos            (26U)
#define USBPHYC_PLL_PLLEN_Msk            (0x1UL << USBPHYC_PLL_PLLEN_Pos)                /*!< 0x04000000 */
#define USBPHYC_PLL_PLLEN                USBPHYC_PLL_PLLEN_Msk                          /*!< PLL enable */
#define USBPHYC_PLL_PLLSTRB_Pos          (27U)
#define USBPHYC_PLL_PLLSTRB_Msk          (0x1UL << USBPHYC_PLL_PLLSTRB_Pos)              /*!< 0x08000000 */
#define USBPHYC_PLL_PLLSTRB              USBPHYC_PLL_PLLSTRB_Msk                        /*!< PLL strobe */
#define USBPHYC_PLL_PLLSTRBYP_Pos        (28U)
#define USBPHYC_PLL_PLLSTRBYP_Msk        (0x1UL << USBPHYC_PLL_PLLSTRBYP_Pos)            /*!< 0x10000000 */
#define USBPHYC_PLL_PLLSTRBYP            USBPHYC_PLL_PLLSTRBYP_Msk                      /*!< PLL strobe bypass */
#define USBPHYC_PLL_PLLFRACCTL_Pos       (29U)
#define USBPHYC_PLL_PLLFRACCTL_Msk       (0x1UL << USBPHYC_PLL_PLLFRACCTL_Pos)           /*!< 0x20000000 */
#define USBPHYC_PLL_PLLFRACCTL           USBPHYC_PLL_PLLFRACCTL_Msk                     /*!< PLL fractional mode control */
#define USBPHYC_PLL_PLLDITHEN0_Pos       (30U)
#define USBPHYC_PLL_PLLDITHEN0_Msk       (0x1UL << USBPHYC_PLL_PLLDITHEN0_Pos)           /*!< 0x40000000 */
#define USBPHYC_PLL_PLLDITHEN0           USBPHYC_PLL_PLLDITHEN0_Msk                     /*!< PLL dither 2 (triangular) */
#define USBPHYC_PLL_PLLDITHEN1_Pos       (31U)
#define USBPHYC_PLL_PLLDITHEN1_Msk       (0x1UL << USBPHYC_PLL_PLLDITHEN1_Pos)           /*!< 0x80000000 */
#define USBPHYC_PLL_PLLDITHEN1           USBPHYC_PLL_PLLDITHEN1_Msk                     /*!< PLL dither 1 (rectangular) */

/****************  Bit definition for USBPHYC_MISC register  *****************/
#define USBPHYC_MISC_SWITHOST_Pos        (0U)
#define USBPHYC_MISC_SWITHOST_Msk        (0x1UL << USBPHYC_MISC_SWITHOST_Pos)            /*!< 0x00000001 */
#define USBPHYC_MISC_SWITHOST            USBPHYC_MISC_SWITHOST_Msk                      /*!< Switch host */
#define USBPHYC_MISC_PPCKDIS_Pos         (1U)
#define USBPHYC_MISC_PPCKDIS_Msk         (0x3UL << USBPHYC_MISC_PPCKDIS_Pos)             /*!< 0x00000006 */
#define USBPHYC_MISC_PPCKDIS             USBPHYC_MISC_PPCKDIS_Msk                       /*!< Intelligent per HS PHY port clock gating control */
#define USBPHYC_MISC_PPCKDIS_0           (0x1UL << USBPHYC_MISC_PPCKDIS_Pos)             /*!< 0x00000002 */
#define USBPHYC_MISC_PPCKDIS_1           (0x2UL << USBPHYC_MISC_PPCKDIS_Pos)             /*!< 0x00000004 */

/****************  Bit definition for USBPHYC_TUNE1 register  ****************/
#define USBPHYC_TUNE1_INCURREN_Pos       (0U)
#define USBPHYC_TUNE1_INCURREN_Msk       (0x1UL << USBPHYC_TUNE1_INCURREN_Pos)           /*!< 0x00000001 */
#define USBPHYC_TUNE1_INCURREN           USBPHYC_TUNE1_INCURREN_Msk                     /*!< The bit enables the current boosting function. */
#define USBPHYC_TUNE1_INCURRINT_Pos      (1U)
#define USBPHYC_TUNE1_INCURRINT_Msk      (0x1UL << USBPHYC_TUNE1_INCURRINT_Pos)          /*!< 0x00000002 */
#define USBPHYC_TUNE1_INCURRINT          USBPHYC_TUNE1_INCURRINT_Msk                    /*!< Current boosting value */
#define USBPHYC_TUNE1_LFSCAPEN_Pos       (2U)
#define USBPHYC_TUNE1_LFSCAPEN_Msk       (0x1UL << USBPHYC_TUNE1_LFSCAPEN_Pos)           /*!< 0x00000004 */
#define USBPHYC_TUNE1_LFSCAPEN           USBPHYC_TUNE1_LFSCAPEN_Msk                     /*!< Low full speed enable */
#define USBPHYC_TUNE1_HSDRVSLEW_Pos      (3U)
#define USBPHYC_TUNE1_HSDRVSLEW_Msk      (0x1UL << USBPHYC_TUNE1_HSDRVSLEW_Pos)          /*!< 0x00000008 */
#define USBPHYC_TUNE1_HSDRVSLEW          USBPHYC_TUNE1_HSDRVSLEW_Msk                    /*!< HS driver slew rate */
#define USBPHYC_TUNE1_HSDRVDCCUR_Pos     (4U)
#define USBPHYC_TUNE1_HSDRVDCCUR_Msk     (0x1UL << USBPHYC_TUNE1_HSDRVDCCUR_Pos)         /*!< 0x00000010 */
#define USBPHYC_TUNE1_HSDRVDCCUR         USBPHYC_TUNE1_HSDRVDCCUR_Msk                   /*!< HS driver DC level */
#define USBPHYC_TUNE1_HSDRVDCLEV_Pos     (5U)
#define USBPHYC_TUNE1_HSDRVDCLEV_Msk     (0x1UL << USBPHYC_TUNE1_HSDRVDCLEV_Pos)         /*!< 0x00000020 */
#define USBPHYC_TUNE1_HSDRVDCLEV         USBPHYC_TUNE1_HSDRVDCLEV_Msk                   /*!< HS driver DC level */
#define USBPHYC_TUNE1_HSDRVCURINCR_Pos   (6U)
#define USBPHYC_TUNE1_HSDRVCURINCR_Msk   (0x1UL << USBPHYC_TUNE1_HSDRVCURINCR_Pos)       /*!< 0x00000040 */
#define USBPHYC_TUNE1_HSDRVCURINCR       USBPHYC_TUNE1_HSDRVCURINCR_Msk                 /*!< Enable the HS driver current increase feature */
#define USBPHYC_TUNE1_FSDRVRFADJ_Pos     (7U)
#define USBPHYC_TUNE1_FSDRVRFADJ_Msk     (0x1UL << USBPHYC_TUNE1_FSDRVRFADJ_Pos)         /*!< 0x00000080 */
#define USBPHYC_TUNE1_FSDRVRFADJ         USBPHYC_TUNE1_FSDRVRFADJ_Msk                   /*!< Tuning pin to adjust the full speed rise/fall time */
#define USBPHYC_TUNE1_HSDRVRFRED_Pos     (8U)
#define USBPHYC_TUNE1_HSDRVRFRED_Msk     (0x1UL << USBPHYC_TUNE1_HSDRVRFRED_Pos)         /*!< 0x00000100 */
#define USBPHYC_TUNE1_HSDRVRFRED         USBPHYC_TUNE1_HSDRVRFRED_Msk                   /*!< High-speed rise-fall reduction enable */
#define USBPHYC_TUNE1_HSDRVCHKITRM_Pos   (9U)
#define USBPHYC_TUNE1_HSDRVCHKITRM_Msk   (0xFUL << USBPHYC_TUNE1_HSDRVCHKITRM_Pos)       /*!< 0x00001E00 */
#define USBPHYC_TUNE1_HSDRVCHKITRM       USBPHYC_TUNE1_HSDRVCHKITRM_Msk                 /*!< HS driver choke current trim */
#define USBPHYC_TUNE1_HSDRVCHKITRM_0     (0x1UL << USBPHYC_TUNE1_HSDRVCHKITRM_Pos)     /*!< 0x00000200 */
#define USBPHYC_TUNE1_HSDRVCHKITRM_1     (0x2UL << USBPHYC_TUNE1_HSDRVCHKITRM_Pos)     /*!< 0x00000400 */
#define USBPHYC_TUNE1_HSDRVCHKITRM_2     (0x4UL << USBPHYC_TUNE1_HSDRVCHKITRM_Pos)     /*!< 0x00000800 */
#define USBPHYC_TUNE1_HSDRVCHKITRM_3     (0x8UL << USBPHYC_TUNE1_HSDRVCHKITRM_Pos)    /*!< 0x00001000 */
#define USBPHYC_TUNE1_HSDRVCHKZTRM_Pos   (13U)
#define USBPHYC_TUNE1_HSDRVCHKZTRM_Msk   (0x3UL << USBPHYC_TUNE1_HSDRVCHKZTRM_Pos)       /*!< 0x00006000 */
#define USBPHYC_TUNE1_HSDRVCHKZTRM       USBPHYC_TUNE1_HSDRVCHKZTRM_Msk                 /*!< HS driver choke impedance trim */
#define USBPHYC_TUNE1_HSDRVCHKZTRM_0     (0x1UL << USBPHYC_TUNE1_HSDRVCHKZTRM_Pos)    /*!< 0x00002000 */
#define USBPHYC_TUNE1_HSDRVCHKZTRM_1     (0x2UL << USBPHYC_TUNE1_HSDRVCHKZTRM_Pos)    /*!< 0x00004000 */
#define USBPHYC_TUNE1_OTPCOMP_Pos        (15U)
#define USBPHYC_TUNE1_OTPCOMP_Msk        (0x1FUL << USBPHYC_TUNE1_OTPCOMP_Pos)           /*!< 0x000F8000 */
#define USBPHYC_TUNE1_OTPCOMP            USBPHYC_TUNE1_OTPCOMP_Msk                      /*!< OTP compensation code */
#define USBPHYC_TUNE1_OTPCOMP_0          (0x1UL << USBPHYC_TUNE1_OTPCOMP_Pos)         /*!< 0x00008000 */
#define USBPHYC_TUNE1_OTPCOMP_1          (0x2UL << USBPHYC_TUNE1_OTPCOMP_Pos)        /*!< 0x00010000 */
#define USBPHYC_TUNE1_OTPCOMP_2          (0x4UL << USBPHYC_TUNE1_OTPCOMP_Pos)        /*!< 0x00020000 */
#define USBPHYC_TUNE1_OTPCOMP_3          (0x8UL << USBPHYC_TUNE1_OTPCOMP_Pos)        /*!< 0x00040000 */
#define USBPHYC_TUNE1_OTPCOMP_4          (0x10UL << USBPHYC_TUNE1_OTPCOMP_Pos)        /*!< 0x00080000 */
#define USBPHYC_TUNE1_SQLCHCTL_Pos       (20U)
#define USBPHYC_TUNE1_SQLCHCTL_Msk       (0x3UL << USBPHYC_TUNE1_SQLCHCTL_Pos)           /*!< 0x00300000 */
#define USBPHYC_TUNE1_SQLCHCTL           USBPHYC_TUNE1_SQLCHCTL_Msk                     /*!< Squelch control */
#define USBPHYC_TUNE1_SQLCHCTL_0         (0x1UL << USBPHYC_TUNE1_SQLCHCTL_Pos)      /*!< 0x00100000 */
#define USBPHYC_TUNE1_SQLCHCTL_1         (0x2UL << USBPHYC_TUNE1_SQLCHCTL_Pos)      /*!< 0x00200000 */
#define USBPHYC_TUNE1_HDRXGNEQEN_Pos     (22U)
#define USBPHYC_TUNE1_HDRXGNEQEN_Msk     (0x1UL << USBPHYC_TUNE1_HDRXGNEQEN_Pos)         /*!< 0x00400000 */
#define USBPHYC_TUNE1_HDRXGNEQEN         USBPHYC_TUNE1_HDRXGNEQEN_Msk                   /*!< Enable HS Rx gain equalizer */
#define USBPHYC_TUNE1_HSRXOFF_Pos        (23U)
#define USBPHYC_TUNE1_HSRXOFF_Msk        (0x3UL << USBPHYC_TUNE1_HSRXOFF_Pos)            /*!< 0x01800000 */
#define USBPHYC_TUNE1_HSRXOFF            USBPHYC_TUNE1_HSRXOFF_Msk                      /*!< HS receiver offset adjustment */
#define USBPHYC_TUNE1_HSRXOFF_0          (0x1UL << USBPHYC_TUNE1_HSRXOFF_Pos)       /*!< 0x00800000 */
#define USBPHYC_TUNE1_HSRXOFF_1          (0x2UL << USBPHYC_TUNE1_HSRXOFF_Pos)      /*!< 0x01000000 */
#define USBPHYC_TUNE1_HSFALLPREEM_Pos    (25U)
#define USBPHYC_TUNE1_HSFALLPREEM_Msk    (0x1UL << USBPHYC_TUNE1_HSFALLPREEM_Pos)        /*!< 0x02000000 */
#define USBPHYC_TUNE1_HSFALLPREEM        USBPHYC_TUNE1_HSFALLPREEM_Msk                  /*!< HS fall time pre-emphasis */
#define USBPHYC_TUNE1_SHTCCTCTLPROT_Pos  (26U)
#define USBPHYC_TUNE1_SHTCCTCTLPROT_Msk  (0x1UL << USBPHYC_TUNE1_SHTCCTCTLPROT_Pos)      /*!< 0x04000000 */
#define USBPHYC_TUNE1_SHTCCTCTLPROT      USBPHYC_TUNE1_SHTCCTCTLPROT_Msk                /*!< Short circuit control protection */
#define USBPHYC_TUNE1_STAGSEL_Pos        (27U)
#define USBPHYC_TUNE1_STAGSEL_Msk        (0x1UL << USBPHYC_TUNE1_STAGSEL_Pos)            /*!< 0x08000000 */
#define USBPHYC_TUNE1_STAGSEL            USBPHYC_TUNE1_STAGSEL_Msk                      /*!< Staggering selection */

/****************  Bit definition for USBPHYC_TUNE2 register  ****************/
#define USBPHYC_TUNE2_INCURREN_Pos       (0U)
#define USBPHYC_TUNE2_INCURREN_Msk       (0x1UL << USBPHYC_TUNE2_INCURREN_Pos)           /*!< 0x00000001 */
#define USBPHYC_TUNE2_INCURREN           USBPHYC_TUNE2_INCURREN_Msk                     /*!< The bit enables the current boosting function. */
#define USBPHYC_TUNE2_INCURRINT_Pos      (1U)
#define USBPHYC_TUNE2_INCURRINT_Msk      (0x1UL << USBPHYC_TUNE2_INCURRINT_Pos)          /*!< 0x00000002 */
#define USBPHYC_TUNE2_INCURRINT          USBPHYC_TUNE2_INCURRINT_Msk                    /*!< Current boosting value */
#define USBPHYC_TUNE2_LFSCAPEN_Pos       (2U)
#define USBPHYC_TUNE2_LFSCAPEN_Msk       (0x1UL << USBPHYC_TUNE2_LFSCAPEN_Pos)           /*!< 0x00000004 */
#define USBPHYC_TUNE2_LFSCAPEN           USBPHYC_TUNE2_LFSCAPEN_Msk                     /*!< Low full speed enable */
#define USBPHYC_TUNE2_HSDRVSLEW_Pos      (3U)
#define USBPHYC_TUNE2_HSDRVSLEW_Msk      (0x1UL << USBPHYC_TUNE2_HSDRVSLEW_Pos)          /*!< 0x00000008 */
#define USBPHYC_TUNE2_HSDRVSLEW          USBPHYC_TUNE2_HSDRVSLEW_Msk                    /*!< HS driver slew rate */
#define USBPHYC_TUNE2_HSDRVDCCUR_Pos     (4U)
#define USBPHYC_TUNE2_HSDRVDCCUR_Msk     (0x1UL << USBPHYC_TUNE2_HSDRVDCCUR_Pos)         /*!< 0x00000010 */
#define USBPHYC_TUNE2_HSDRVDCCUR         USBPHYC_TUNE2_HSDRVDCCUR_Msk                   /*!< HS driver DC level */
#define USBPHYC_TUNE2_HSDRVDCLEV_Pos     (5U)
#define USBPHYC_TUNE2_HSDRVDCLEV_Msk     (0x1UL << USBPHYC_TUNE2_HSDRVDCLEV_Pos)         /*!< 0x00000020 */
#define USBPHYC_TUNE2_HSDRVDCLEV         USBPHYC_TUNE2_HSDRVDCLEV_Msk                   /*!< HS driver DC level */
#define USBPHYC_TUNE2_HSDRVCURINCR_Pos   (6U)
#define USBPHYC_TUNE2_HSDRVCURINCR_Msk   (0x1UL << USBPHYC_TUNE2_HSDRVCURINCR_Pos)       /*!< 0x00000040 */
#define USBPHYC_TUNE2_HSDRVCURINCR       USBPHYC_TUNE2_HSDRVCURINCR_Msk                 /*!< Enable the HS driver current increase feature */
#define USBPHYC_TUNE2_FSDRVRFADJ_Pos     (7U)
#define USBPHYC_TUNE2_FSDRVRFADJ_Msk     (0x1UL << USBPHYC_TUNE2_FSDRVRFADJ_Pos)         /*!< 0x00000080 */
#define USBPHYC_TUNE2_FSDRVRFADJ         USBPHYC_TUNE2_FSDRVRFADJ_Msk                   /*!< Tuning pin to adjust the full speed rise/fall time */
#define USBPHYC_TUNE2_HSDRVRFRED_Pos     (8U)
#define USBPHYC_TUNE2_HSDRVRFRED_Msk     (0x1UL << USBPHYC_TUNE2_HSDRVRFRED_Pos)         /*!< 0x00000100 */
#define USBPHYC_TUNE2_HSDRVRFRED         USBPHYC_TUNE2_HSDRVRFRED_Msk                   /*!< High-speed rise-fall reduction enable */
#define USBPHYC_TUNE2_HSDRVCHKITRM_Pos   (9U)
#define USBPHYC_TUNE2_HSDRVCHKITRM_Msk   (0xFUL << USBPHYC_TUNE2_HSDRVCHKITRM_Pos)       /*!< 0x00001E00 */
#define USBPHYC_TUNE2_HSDRVCHKITRM       USBPHYC_TUNE2_HSDRVCHKITRM_Msk                 /*!< HS driver choke current trim */
#define USBPHYC_TUNE2_HSDRVCHKITRM_0     (0x1UL << USBPHYC_TUNE2_HSDRVCHKITRM_Pos)     /*!< 0x00000200 */
#define USBPHYC_TUNE2_HSDRVCHKITRM_1     (0x2UL << USBPHYC_TUNE2_HSDRVCHKITRM_Pos)     /*!< 0x00000400 */
#define USBPHYC_TUNE2_HSDRVCHKITRM_2     (0x4UL << USBPHYC_TUNE2_HSDRVCHKITRM_Pos)     /*!< 0x00000800 */
#define USBPHYC_TUNE2_HSDRVCHKITRM_3     (0x8UL << USBPHYC_TUNE2_HSDRVCHKITRM_Pos)    /*!< 0x00001000 */
#define USBPHYC_TUNE2_HSDRVCHKZTRM_Pos   (13U)
#define USBPHYC_TUNE2_HSDRVCHKZTRM_Msk   (0x3UL << USBPHYC_TUNE2_HSDRVCHKZTRM_Pos)       /*!< 0x00006000 */
#define USBPHYC_TUNE2_HSDRVCHKZTRM       USBPHYC_TUNE2_HSDRVCHKZTRM_Msk                 /*!< HS driver choke impedance trim */
#define USBPHYC_TUNE2_HSDRVCHKZTRM_0     (0x1UL << USBPHYC_TUNE2_HSDRVCHKZTRM_Pos)    /*!< 0x00002000 */
#define USBPHYC_TUNE2_HSDRVCHKZTRM_1     (0x2UL << USBPHYC_TUNE2_HSDRVCHKZTRM_Pos)    /*!< 0x00004000 */
#define USBPHYC_TUNE2_OTPCOMP_Pos        (15U)
#define USBPHYC_TUNE2_OTPCOMP_Msk        (0x1FUL << USBPHYC_TUNE2_OTPCOMP_Pos)           /*!< 0x000F8000 */
#define USBPHYC_TUNE2_OTPCOMP            USBPHYC_TUNE2_OTPCOMP_Msk                      /*!< OTP compensation code */
#define USBPHYC_TUNE2_OTPCOMP_0          (0x1UL << USBPHYC_TUNE2_OTPCOMP_Pos)         /*!< 0x00008000 */
#define USBPHYC_TUNE2_OTPCOMP_1          (0x2UL << USBPHYC_TUNE2_OTPCOMP_Pos)        /*!< 0x00010000 */
#define USBPHYC_TUNE2_OTPCOMP_2          (0x4UL << USBPHYC_TUNE2_OTPCOMP_Pos)        /*!< 0x00020000 */
#define USBPHYC_TUNE2_OTPCOMP_3          (0x8UL << USBPHYC_TUNE2_OTPCOMP_Pos)        /*!< 0x00040000 */
#define USBPHYC_TUNE2_OTPCOMP_4          (0x10UL << USBPHYC_TUNE2_OTPCOMP_Pos)        /*!< 0x00080000 */
#define USBPHYC_TUNE2_SQLCHCTL_Pos       (20U)
#define USBPHYC_TUNE2_SQLCHCTL_Msk       (0x3UL << USBPHYC_TUNE2_SQLCHCTL_Pos)           /*!< 0x00300000 */
#define USBPHYC_TUNE2_SQLCHCTL           USBPHYC_TUNE2_SQLCHCTL_Msk                     /*!< Squelch control */
#define USBPHYC_TUNE2_SQLCHCTL_0         (0x1UL << USBPHYC_TUNE2_SQLCHCTL_Pos)      /*!< 0x00100000 */
#define USBPHYC_TUNE2_SQLCHCTL_1         (0x2UL << USBPHYC_TUNE2_SQLCHCTL_Pos)      /*!< 0x00200000 */
#define USBPHYC_TUNE2_HDRXGNEQEN_Pos     (22U)
#define USBPHYC_TUNE2_HDRXGNEQEN_Msk     (0x1UL << USBPHYC_TUNE2_HDRXGNEQEN_Pos)         /*!< 0x00400000 */
#define USBPHYC_TUNE2_HDRXGNEQEN         USBPHYC_TUNE2_HDRXGNEQEN_Msk                   /*!< Enable HS Rx gain equalizer */
#define USBPHYC_TUNE2_HSRXOFF_Pos        (23U)
#define USBPHYC_TUNE2_HSRXOFF_Msk        (0x3UL << USBPHYC_TUNE2_HSRXOFF_Pos)            /*!< 0x01800000 */
#define USBPHYC_TUNE2_HSRXOFF            USBPHYC_TUNE2_HSRXOFF_Msk                      /*!< HS receiver offset adjustment */
#define USBPHYC_TUNE2_HSRXOFF_0          (0x1UL << USBPHYC_TUNE2_HSRXOFF_Pos)       /*!< 0x00800000 */
#define USBPHYC_TUNE2_HSRXOFF_1          (0x2UL << USBPHYC_TUNE2_HSRXOFF_Pos)      /*!< 0x01000000 */
#define USBPHYC_TUNE2_HSFALLPREEM_Pos    (25U)
#define USBPHYC_TUNE2_HSFALLPREEM_Msk    (0x1UL << USBPHYC_TUNE2_HSFALLPREEM_Pos)        /*!< 0x02000000 */
#define USBPHYC_TUNE2_HSFALLPREEM        USBPHYC_TUNE2_HSFALLPREEM_Msk                  /*!< HS fall time pre-emphasis */
#define USBPHYC_TUNE2_SHTCCTCTLPROT_Pos  (26U)
#define USBPHYC_TUNE2_SHTCCTCTLPROT_Msk  (0x1UL << USBPHYC_TUNE2_SHTCCTCTLPROT_Pos)      /*!< 0x04000000 */
#define USBPHYC_TUNE2_SHTCCTCTLPROT      USBPHYC_TUNE2_SHTCCTCTLPROT_Msk                /*!< Short circuit control protection */
#define USBPHYC_TUNE2_STAGSEL_Pos        (27U)
#define USBPHYC_TUNE2_STAGSEL_Msk        (0x1UL << USBPHYC_TUNE2_STAGSEL_Pos)            /*!< 0x08000000 */
#define USBPHYC_TUNE2_STAGSEL            USBPHYC_TUNE2_STAGSEL_Msk                      /*!< Staggering selection */

/****************  Bit definition for USBPHYC_VERR register  *****************/
#define USBPHYC_VERR_MINREV_Pos          (0U)
#define USBPHYC_VERR_MINREV_Msk          (0xFUL << USBPHYC_VERR_MINREV_Pos)              /*!< 0x0000000F */
#define USBPHYC_VERR_MINREV              USBPHYC_VERR_MINREV_Msk                        /*!< Minor revision */
#define USBPHYC_VERR_MINREV_0            (0x1UL << USBPHYC_VERR_MINREV_Pos)              /*!< 0x00000001 */
#define USBPHYC_VERR_MINREV_1            (0x2UL << USBPHYC_VERR_MINREV_Pos)              /*!< 0x00000002 */
#define USBPHYC_VERR_MINREV_2            (0x4UL << USBPHYC_VERR_MINREV_Pos)              /*!< 0x00000004 */
#define USBPHYC_VERR_MINREV_3            (0x8UL << USBPHYC_VERR_MINREV_Pos)              /*!< 0x00000008 */
#define USBPHYC_VERR_MAJREV_Pos          (4U)
#define USBPHYC_VERR_MAJREV_Msk          (0xFUL << USBPHYC_VERR_MAJREV_Pos)              /*!< 0x000000F0 */
#define USBPHYC_VERR_MAJREV              USBPHYC_VERR_MAJREV_Msk                        /*!< Major revision */
#define USBPHYC_VERR_MAJREV_0            (0x1UL << USBPHYC_VERR_MAJREV_Pos)             /*!< 0x00000010 */
#define USBPHYC_VERR_MAJREV_1            (0x2UL << USBPHYC_VERR_MAJREV_Pos)             /*!< 0x00000020 */
#define USBPHYC_VERR_MAJREV_2            (0x4UL << USBPHYC_VERR_MAJREV_Pos)             /*!< 0x00000040 */
#define USBPHYC_VERR_MAJREV_3            (0x8UL << USBPHYC_VERR_MAJREV_Pos)             /*!< 0x00000080 */

/**
  * @}
  */
/**
  * @}
  */

/**
  * @}
  */
