
/******************************************************************************/
/*                                                                            */
/*                Ethernet MAC Registers bits definitions                     */
/*                                                                            */
/******************************************************************************/
/***************  Bit definition for ETH_MACCR register  ***************/
#define ETH_MACCR_RE_Pos                    (0U)
#define ETH_MACCR_RE_Msk                    (0x1U << ETH_MACCR_RE_Pos)                          /*!< 0x00000001 */
#define ETH_MACCR_RE                        ETH_MACCR_RE_Msk                                    /*!< Receiver Enable */
#define ETH_MACCR_TE_Pos                    (1U)
#define ETH_MACCR_TE_Msk                    (0x1U << ETH_MACCR_TE_Pos)                          /*!< 0x00000002 */
#define ETH_MACCR_TE                        ETH_MACCR_TE_Msk                                    /*!< Transmitter Enable */
#define ETH_MACCR_PRELEN_Pos                (2U)
#define ETH_MACCR_PRELEN_Msk                (0x3U << ETH_MACCR_PRELEN_Pos)                      /*!< 0x0000000C */
#define ETH_MACCR_PRELEN                    ETH_MACCR_PRELEN_Msk                                /*!< Preamble Length for Transmit packets */
#define ETH_MACCR_PRELEN_0                  (0x1U << ETH_MACCR_PRELEN_Pos)                      /*!< 0x00000004 */
#define ETH_MACCR_PRELEN_1                  (0x2U << ETH_MACCR_PRELEN_Pos)                      /*!< 0x00000008 */
#define ETH_MACCR_DC_Pos                    (4U)
#define ETH_MACCR_DC_Msk                    (0x1U << ETH_MACCR_DC_Pos)                          /*!< 0x00000010 */
#define ETH_MACCR_DC                        ETH_MACCR_DC_Msk                                    /*!< Deferral Check */
#define ETH_MACCR_BL_Pos                    (5U)
#define ETH_MACCR_BL_Msk                    (0x3U << ETH_MACCR_BL_Pos)                          /*!< 0x00000060 */
#define ETH_MACCR_BL                        ETH_MACCR_BL_Msk                                    /*!< Back-Off Limit */
#define ETH_MACCR_BL_0                      (0x1U << ETH_MACCR_BL_Pos)                         /*!< 0x00000020 */
#define ETH_MACCR_BL_1                      (0x2U << ETH_MACCR_BL_Pos)                         /*!< 0x00000040 */
#define ETH_MACCR_DR_Pos                    (8U)
#define ETH_MACCR_DR_Msk                    (0x1U << ETH_MACCR_DR_Pos)                          /*!< 0x00000100 */
#define ETH_MACCR_DR                        ETH_MACCR_DR_Msk                                    /*!< Disable Retry */
#define ETH_MACCR_DCRS_Pos                  (9U)
#define ETH_MACCR_DCRS_Msk                  (0x1U << ETH_MACCR_DCRS_Pos)                        /*!< 0x00000200 */
#define ETH_MACCR_DCRS                      ETH_MACCR_DCRS_Msk                                  /*!< Disable Carrier Sense During Transmission */
#define ETH_MACCR_DO_Pos                    (10U)
#define ETH_MACCR_DO_Msk                    (0x1U << ETH_MACCR_DO_Pos)                          /*!< 0x00000400 */
#define ETH_MACCR_DO                        ETH_MACCR_DO_Msk                                    /*!< Disable Receive Own */
#define ETH_MACCR_ECRSFD_Pos                (11U)
#define ETH_MACCR_ECRSFD_Msk                (0x1U << ETH_MACCR_ECRSFD_Pos)                      /*!< 0x00000800 */
#define ETH_MACCR_ECRSFD                    ETH_MACCR_ECRSFD_Msk                                /*!< Enable Carrier Sense Before Transmission in Full-Duplex Mode */
#define ETH_MACCR_LM_Pos                    (12U)
#define ETH_MACCR_LM_Msk                    (0x1U << ETH_MACCR_LM_Pos)                          /*!< 0x00001000 */
#define ETH_MACCR_LM                        ETH_MACCR_LM_Msk                                    /*!< Loopback Mode */
#define ETH_MACCR_DM_Pos                    (13U)
#define ETH_MACCR_DM_Msk                    (0x1U << ETH_MACCR_DM_Pos)                          /*!< 0x00002000 */
#define ETH_MACCR_DM                        ETH_MACCR_DM_Msk                                    /*!< Duplex Mode */
#define ETH_MACCR_FES_Pos                   (14U)
#define ETH_MACCR_FES_Msk                   (0x1U << ETH_MACCR_FES_Pos)                         /*!< 0x00004000 */
#define ETH_MACCR_FES                       ETH_MACCR_FES_Msk                                   /*!< MAC Speed */
#define ETH_MACCR_PS_Pos                    (15U)
#define ETH_MACCR_PS_Msk                    (0x1U << ETH_MACCR_PS_Pos)                          /*!< 0x00008000 */
#define ETH_MACCR_PS                        ETH_MACCR_PS_Msk                                    /*!< Port Select */
#define ETH_MACCR_JE_Pos                    (16U)
#define ETH_MACCR_JE_Msk                    (0x1U << ETH_MACCR_JE_Pos)                          /*!< 0x00010000 */
#define ETH_MACCR_JE                        ETH_MACCR_JE_Msk                                    /*!< Jumbo Packet Enable */
#define ETH_MACCR_JD_Pos                    (17U)
#define ETH_MACCR_JD_Msk                    (0x1U << ETH_MACCR_JD_Pos)                          /*!< 0x00020000 */
#define ETH_MACCR_JD                        ETH_MACCR_JD_Msk                                    /*!< Jabber Disable */
#define ETH_MACCR_BE_Pos                    (18U)
#define ETH_MACCR_BE_Msk                    (0x1U << ETH_MACCR_BE_Pos)                          /*!< 0x00040000 */
#define ETH_MACCR_BE                        ETH_MACCR_BE_Msk                                    /*!< Packet Burst Enable */
#define ETH_MACCR_WD_Pos                    (19U)
#define ETH_MACCR_WD_Msk                    (0x1U << ETH_MACCR_WD_Pos)                          /*!< 0x00080000 */
#define ETH_MACCR_WD                        ETH_MACCR_WD_Msk                                    /*!< Watchdog Disable */
#define ETH_MACCR_ACS_Pos                   (20U)
#define ETH_MACCR_ACS_Msk                   (0x1U << ETH_MACCR_ACS_Pos)                         /*!< 0x00100000 */
#define ETH_MACCR_ACS                       ETH_MACCR_ACS_Msk                                   /*!< Automatic Pad or CRC Stripping */
#define ETH_MACCR_CST_Pos                   (21U)
#define ETH_MACCR_CST_Msk                   (0x1U << ETH_MACCR_CST_Pos)                         /*!< 0x00200000 */
#define ETH_MACCR_CST                       ETH_MACCR_CST_Msk                                   /*!< CRC stripping for Type packets */
#define ETH_MACCR_S2KP_Pos                  (22U)
#define ETH_MACCR_S2KP_Msk                  (0x1U << ETH_MACCR_S2KP_Pos)                        /*!< 0x00400000 */
#define ETH_MACCR_S2KP                      ETH_MACCR_S2KP_Msk                                  /*!< IEEE 802.3as Support for 2K Packets */
#define ETH_MACCR_GPSLCE_Pos                (23U)
#define ETH_MACCR_GPSLCE_Msk                (0x1U << ETH_MACCR_GPSLCE_Pos)                      /*!< 0x00800000 */
#define ETH_MACCR_GPSLCE                    ETH_MACCR_GPSLCE_Msk                                /*!< Giant Packet Size Limit Control Enable */
#define ETH_MACCR_IPG_Pos                   (24U)
#define ETH_MACCR_IPG_Msk                   (0x7U << ETH_MACCR_IPG_Pos)                         /*!< 0x07000000 */
#define ETH_MACCR_IPG                       ETH_MACCR_IPG_Msk                                   /*!< Inter-Packet Gap */
#define ETH_MACCR_IPG_0                     (0x1U << ETH_MACCR_IPG_Pos)                   /*!< 0x01000000 */
#define ETH_MACCR_IPG_1                     (0x2U << ETH_MACCR_IPG_Pos)                   /*!< 0x02000000 */
#define ETH_MACCR_IPG_2                     (0x4U << ETH_MACCR_IPG_Pos)                   /*!< 0x04000000 */
#define ETH_MACCR_IPC_Pos                   (27U)
#define ETH_MACCR_IPC_Msk                   (0x1U << ETH_MACCR_IPC_Pos)                         /*!< 0x08000000 */
#define ETH_MACCR_IPC                       ETH_MACCR_IPC_Msk                                   /*!< Checksum Offload */
#define ETH_MACCR_SARC_Pos                  (28U)
#define ETH_MACCR_SARC_Msk                  (0x7U << ETH_MACCR_SARC_Pos)                        /*!< 0x70000000 */
#define ETH_MACCR_SARC                      ETH_MACCR_SARC_Msk                                  /*!< Source Address Insertion or Replacement Control */
#define ETH_MACCR_SARC_0                    (0x1U << ETH_MACCR_SARC_Pos)                 /*!< 0x10000000 */
#define ETH_MACCR_SARC_1                    (0x2U << ETH_MACCR_SARC_Pos)                 /*!< 0x20000000 */
#define ETH_MACCR_SARC_2                    (0x4U << ETH_MACCR_SARC_Pos)                 /*!< 0x40000000 */
#define ETH_MACCR_ARPEN_Pos                 (31U)
#define ETH_MACCR_ARPEN_Msk                 (0x1U << ETH_MACCR_ARPEN_Pos)                       /*!< 0x80000000 */
#define ETH_MACCR_ARPEN                     ETH_MACCR_ARPEN_Msk                                 /*!< ARP Offload Enable */

/**************  Bit definition for ETH_MACECR register  ***************/
#define ETH_MACECR_GPSL_Pos                 (0U)
#define ETH_MACECR_GPSL_Msk                 (0x3FFFU << ETH_MACECR_GPSL_Pos)                    /*!< 0x00003FFF */
#define ETH_MACECR_GPSL                     ETH_MACECR_GPSL_Msk                                 /*!< Giant Packet Size Limit */
#define ETH_MACECR_GPSL_0                   (0x1U << ETH_MACECR_GPSL_Pos)                       /*!< 0x00000001 */
#define ETH_MACECR_GPSL_1                   (0x2U << ETH_MACECR_GPSL_Pos)                       /*!< 0x00000002 */
#define ETH_MACECR_GPSL_2                   (0x4U << ETH_MACECR_GPSL_Pos)                       /*!< 0x00000004 */
#define ETH_MACECR_GPSL_3                   (0x8U << ETH_MACECR_GPSL_Pos)                       /*!< 0x00000008 */
#define ETH_MACECR_GPSL_4                   (0x10U << ETH_MACECR_GPSL_Pos)                      /*!< 0x00000010 */
#define ETH_MACECR_GPSL_5                   (0x20U << ETH_MACECR_GPSL_Pos)                      /*!< 0x00000020 */
#define ETH_MACECR_GPSL_6                   (0x40U << ETH_MACECR_GPSL_Pos)                      /*!< 0x00000040 */
#define ETH_MACECR_GPSL_7                   (0x80U << ETH_MACECR_GPSL_Pos)                      /*!< 0x00000080 */
#define ETH_MACECR_GPSL_8                   (0x100U << ETH_MACECR_GPSL_Pos)                     /*!< 0x00000100 */
#define ETH_MACECR_GPSL_9                   (0x200U << ETH_MACECR_GPSL_Pos)                     /*!< 0x00000200 */
#define ETH_MACECR_GPSL_10                  (0x400U << ETH_MACECR_GPSL_Pos)                     /*!< 0x00000400 */
#define ETH_MACECR_GPSL_11                  (0x800U << ETH_MACECR_GPSL_Pos)                     /*!< 0x00000800 */
#define ETH_MACECR_GPSL_12                  (0x1000U << ETH_MACECR_GPSL_Pos)                    /*!< 0x00001000 */
#define ETH_MACECR_GPSL_13                  (0x2000U << ETH_MACECR_GPSL_Pos)                    /*!< 0x00002000 */
#define ETH_MACECR_DCRCC_Pos                (16U)
#define ETH_MACECR_DCRCC_Msk                (0x1U << ETH_MACECR_DCRCC_Pos)                      /*!< 0x00010000 */
#define ETH_MACECR_DCRCC                    ETH_MACECR_DCRCC_Msk                                /*!< Disable CRC Checking for Received Packets */
#define ETH_MACECR_SPEN_Pos                 (17U)
#define ETH_MACECR_SPEN_Msk                 (0x1U << ETH_MACECR_SPEN_Pos)                       /*!< 0x00020000 */
#define ETH_MACECR_SPEN                     ETH_MACECR_SPEN_Msk                                 /*!< Slow Protocol Detection Enable */
#define ETH_MACECR_USP_Pos                  (18U)
#define ETH_MACECR_USP_Msk                  (0x1U << ETH_MACECR_USP_Pos)                        /*!< 0x00040000 */
#define ETH_MACECR_USP                      ETH_MACECR_USP_Msk                                  /*!< Unicast Slow Protocol Packet Detect */
#define ETH_MACECR_EIPGEN_Pos               (24U)
#define ETH_MACECR_EIPGEN_Msk               (0x1U << ETH_MACECR_EIPGEN_Pos)                     /*!< 0x01000000 */
#define ETH_MACECR_EIPGEN                   ETH_MACECR_EIPGEN_Msk                               /*!< Extended Inter-Packet Gap Enable */
#define ETH_MACECR_EIPG_Pos                 (25U)
#define ETH_MACECR_EIPG_Msk                 (0x1FU << ETH_MACECR_EIPG_Pos)                      /*!< 0x3E000000 */
#define ETH_MACECR_EIPG                     ETH_MACECR_EIPG_Msk                                 /*!< Extended Inter-Packet Gap */
#define ETH_MACECR_EIPG_0                   (0x1U << ETH_MACECR_EIPG_Pos)                 /*!< 0x02000000 */
#define ETH_MACECR_EIPG_1                   (0x2U << ETH_MACECR_EIPG_Pos)                 /*!< 0x04000000 */
#define ETH_MACECR_EIPG_2                   (0x4U << ETH_MACECR_EIPG_Pos)                 /*!< 0x08000000 */
#define ETH_MACECR_EIPG_3                   (0x8U << ETH_MACECR_EIPG_Pos)                /*!< 0x10000000 */
#define ETH_MACECR_EIPG_4                   (0x10U << ETH_MACECR_EIPG_Pos)                /*!< 0x20000000 */

/**************  Bit definition for ETH_MACPFR register  ***************/
#define ETH_MACPFR_PR_Pos                   (0U)
#define ETH_MACPFR_PR_Msk                   (0x1U << ETH_MACPFR_PR_Pos)                         /*!< 0x00000001 */
#define ETH_MACPFR_PR                       ETH_MACPFR_PR_Msk                                   /*!< Promiscuous Mode */
#define ETH_MACPFR_HUC_Pos                  (1U)
#define ETH_MACPFR_HUC_Msk                  (0x1U << ETH_MACPFR_HUC_Pos)                        /*!< 0x00000002 */
#define ETH_MACPFR_HUC                      ETH_MACPFR_HUC_Msk                                  /*!< Hash Unicast */
#define ETH_MACPFR_HMC_Pos                  (2U)
#define ETH_MACPFR_HMC_Msk                  (0x1U << ETH_MACPFR_HMC_Pos)                        /*!< 0x00000004 */
#define ETH_MACPFR_HMC                      ETH_MACPFR_HMC_Msk                                  /*!< Hash Multicast */
#define ETH_MACPFR_DAIF_Pos                 (3U)
#define ETH_MACPFR_DAIF_Msk                 (0x1U << ETH_MACPFR_DAIF_Pos)                       /*!< 0x00000008 */
#define ETH_MACPFR_DAIF                     ETH_MACPFR_DAIF_Msk                                 /*!< DA Inverse Filtering */
#define ETH_MACPFR_PM_Pos                   (4U)
#define ETH_MACPFR_PM_Msk                   (0x1U << ETH_MACPFR_PM_Pos)                         /*!< 0x00000010 */
#define ETH_MACPFR_PM                       ETH_MACPFR_PM_Msk                                   /*!< Pass All Multicast */
#define ETH_MACPFR_DBF_Pos                  (5U)
#define ETH_MACPFR_DBF_Msk                  (0x1U << ETH_MACPFR_DBF_Pos)                        /*!< 0x00000020 */
#define ETH_MACPFR_DBF                      ETH_MACPFR_DBF_Msk                                  /*!< Disable Broadcast Packets */
#define ETH_MACPFR_PCF_Pos                  (6U)
#define ETH_MACPFR_PCF_Msk                  (0x3U << ETH_MACPFR_PCF_Pos)                        /*!< 0x000000C0 */
#define ETH_MACPFR_PCF                      ETH_MACPFR_PCF_Msk                                  /*!< Pass Control Packets */
#define ETH_MACPFR_PCF_0                    (0x1U << ETH_MACPFR_PCF_Pos)                       /*!< 0x00000040 */
#define ETH_MACPFR_PCF_1                    (0x2U << ETH_MACPFR_PCF_Pos)                       /*!< 0x00000080 */
#define ETH_MACPFR_SAIF_Pos                 (8U)
#define ETH_MACPFR_SAIF_Msk                 (0x1U << ETH_MACPFR_SAIF_Pos)                       /*!< 0x00000100 */
#define ETH_MACPFR_SAIF                     ETH_MACPFR_SAIF_Msk                                 /*!< SA Inverse Filtering */
#define ETH_MACPFR_SAF_Pos                  (9U)
#define ETH_MACPFR_SAF_Msk                  (0x1U << ETH_MACPFR_SAF_Pos)                        /*!< 0x00000200 */
#define ETH_MACPFR_SAF                      ETH_MACPFR_SAF_Msk                                  /*!< Source Address Filter Enable */
#define ETH_MACPFR_HPF_Pos                  (10U)
#define ETH_MACPFR_HPF_Msk                  (0x1U << ETH_MACPFR_HPF_Pos)                        /*!< 0x00000400 */
#define ETH_MACPFR_HPF                      ETH_MACPFR_HPF_Msk                                  /*!< Hash or Perfect Filter */
#define ETH_MACPFR_VTFE_Pos                 (16U)
#define ETH_MACPFR_VTFE_Msk                 (0x1U << ETH_MACPFR_VTFE_Pos)                       /*!< 0x00010000 */
#define ETH_MACPFR_VTFE                     ETH_MACPFR_VTFE_Msk                                 /*!< VLAN Tag Filter Enable */
#define ETH_MACPFR_IPFE_Pos                 (20U)
#define ETH_MACPFR_IPFE_Msk                 (0x1U << ETH_MACPFR_IPFE_Pos)                       /*!< 0x00100000 */
#define ETH_MACPFR_IPFE                     ETH_MACPFR_IPFE_Msk                                 /*!< Layer 3 and Layer 4 Filter Enable */
#define ETH_MACPFR_DNTU_Pos                 (21U)
#define ETH_MACPFR_DNTU_Msk                 (0x1U << ETH_MACPFR_DNTU_Pos)                       /*!< 0x00200000 */
#define ETH_MACPFR_DNTU                     ETH_MACPFR_DNTU_Msk                                 /*!< Drop Non-TCP/UDP over IP Packets */
#define ETH_MACPFR_RA_Pos                   (31U)
#define ETH_MACPFR_RA_Msk                   (0x1U << ETH_MACPFR_RA_Pos)                         /*!< 0x80000000 */
#define ETH_MACPFR_RA                       ETH_MACPFR_RA_Msk                                   /*!< Receive All */

/**************  Bit definition for ETH_MACWTR register  ***************/
#define ETH_MACWTR_WTO_Pos                  (0U)
#define ETH_MACWTR_WTO_Msk                  (0xFU << ETH_MACWTR_WTO_Pos)                        /*!< 0x0000000F */
#define ETH_MACWTR_WTO                      ETH_MACWTR_WTO_Msk                                  /*!< Watchdog Timeout */
#define ETH_MACWTR_WTO_0                    (0x1U << ETH_MACWTR_WTO_Pos)                        /*!< 0x00000001 */
#define ETH_MACWTR_WTO_1                    (0x2U << ETH_MACWTR_WTO_Pos)                        /*!< 0x00000002 */
#define ETH_MACWTR_WTO_2                    (0x4U << ETH_MACWTR_WTO_Pos)                        /*!< 0x00000004 */
#define ETH_MACWTR_WTO_3                    (0x8U << ETH_MACWTR_WTO_Pos)                        /*!< 0x00000008 */
#define ETH_MACWTR_PWE_Pos                  (8U)
#define ETH_MACWTR_PWE_Msk                  (0x1U << ETH_MACWTR_PWE_Pos)                        /*!< 0x00000100 */
#define ETH_MACWTR_PWE                      ETH_MACWTR_PWE_Msk                                  /*!< Programmable Watchdog Enable */

/**************  Bit definition for ETH_MACHT0R register  **************/
#define ETH_MACHT0R_HT31T0_Pos              (0U)
#define ETH_MACHT0R_HT31T0_Msk              (0xFFFFFFFFU << ETH_MACHT0R_HT31T0_Pos)             /*!< 0xFFFFFFFF */
#define ETH_MACHT0R_HT31T0                  ETH_MACHT0R_HT31T0_Msk                              /*!< MAC Hash Table First 32 Bits */
#define ETH_MACHT0R_HT31T0_0                (0x1U << ETH_MACHT0R_HT31T0_Pos)                    /*!< 0x00000001 */
#define ETH_MACHT0R_HT31T0_1                (0x2U << ETH_MACHT0R_HT31T0_Pos)                    /*!< 0x00000002 */
#define ETH_MACHT0R_HT31T0_2                (0x4U << ETH_MACHT0R_HT31T0_Pos)                    /*!< 0x00000004 */
#define ETH_MACHT0R_HT31T0_3                (0x8U << ETH_MACHT0R_HT31T0_Pos)                    /*!< 0x00000008 */
#define ETH_MACHT0R_HT31T0_4                (0x10U << ETH_MACHT0R_HT31T0_Pos)                   /*!< 0x00000010 */
#define ETH_MACHT0R_HT31T0_5                (0x20U << ETH_MACHT0R_HT31T0_Pos)                   /*!< 0x00000020 */
#define ETH_MACHT0R_HT31T0_6                (0x40U << ETH_MACHT0R_HT31T0_Pos)                   /*!< 0x00000040 */
#define ETH_MACHT0R_HT31T0_7                (0x80U << ETH_MACHT0R_HT31T0_Pos)                   /*!< 0x00000080 */
#define ETH_MACHT0R_HT31T0_8                (0x100U << ETH_MACHT0R_HT31T0_Pos)                  /*!< 0x00000100 */
#define ETH_MACHT0R_HT31T0_9                (0x200U << ETH_MACHT0R_HT31T0_Pos)                  /*!< 0x00000200 */
#define ETH_MACHT0R_HT31T0_10               (0x400U << ETH_MACHT0R_HT31T0_Pos)                  /*!< 0x00000400 */
#define ETH_MACHT0R_HT31T0_11               (0x800U << ETH_MACHT0R_HT31T0_Pos)                  /*!< 0x00000800 */
#define ETH_MACHT0R_HT31T0_12               (0x1000U << ETH_MACHT0R_HT31T0_Pos)                 /*!< 0x00001000 */
#define ETH_MACHT0R_HT31T0_13               (0x2000U << ETH_MACHT0R_HT31T0_Pos)                 /*!< 0x00002000 */
#define ETH_MACHT0R_HT31T0_14               (0x4000U << ETH_MACHT0R_HT31T0_Pos)                 /*!< 0x00004000 */
#define ETH_MACHT0R_HT31T0_15               (0x8000U << ETH_MACHT0R_HT31T0_Pos)                 /*!< 0x00008000 */
#define ETH_MACHT0R_HT31T0_16               (0x10000U << ETH_MACHT0R_HT31T0_Pos)                /*!< 0x00010000 */
#define ETH_MACHT0R_HT31T0_17               (0x20000U << ETH_MACHT0R_HT31T0_Pos)                /*!< 0x00020000 */
#define ETH_MACHT0R_HT31T0_18               (0x40000U << ETH_MACHT0R_HT31T0_Pos)                /*!< 0x00040000 */
#define ETH_MACHT0R_HT31T0_19               (0x80000U << ETH_MACHT0R_HT31T0_Pos)                /*!< 0x00080000 */
#define ETH_MACHT0R_HT31T0_20               (0x100000U << ETH_MACHT0R_HT31T0_Pos)               /*!< 0x00100000 */
#define ETH_MACHT0R_HT31T0_21               (0x200000U << ETH_MACHT0R_HT31T0_Pos)               /*!< 0x00200000 */
#define ETH_MACHT0R_HT31T0_22               (0x400000U << ETH_MACHT0R_HT31T0_Pos)               /*!< 0x00400000 */
#define ETH_MACHT0R_HT31T0_23               (0x800000U << ETH_MACHT0R_HT31T0_Pos)               /*!< 0x00800000 */
#define ETH_MACHT0R_HT31T0_24               (0x1000000U << ETH_MACHT0R_HT31T0_Pos)              /*!< 0x01000000 */
#define ETH_MACHT0R_HT31T0_25               (0x2000000U << ETH_MACHT0R_HT31T0_Pos)              /*!< 0x02000000 */
#define ETH_MACHT0R_HT31T0_26               (0x4000000U << ETH_MACHT0R_HT31T0_Pos)              /*!< 0x04000000 */
#define ETH_MACHT0R_HT31T0_27               (0x8000000U << ETH_MACHT0R_HT31T0_Pos)              /*!< 0x08000000 */
#define ETH_MACHT0R_HT31T0_28               (0x10000000U << ETH_MACHT0R_HT31T0_Pos)             /*!< 0x10000000 */
#define ETH_MACHT0R_HT31T0_29               (0x20000000U << ETH_MACHT0R_HT31T0_Pos)             /*!< 0x20000000 */
#define ETH_MACHT0R_HT31T0_30               (0x40000000U << ETH_MACHT0R_HT31T0_Pos)             /*!< 0x40000000 */
#define ETH_MACHT0R_HT31T0_31               (0x80000000U << ETH_MACHT0R_HT31T0_Pos)             /*!< 0x80000000 */

/**************  Bit definition for ETH_MACHT1R register  **************/
#define ETH_MACHT1R_HT63T32_Pos             (0U)
#define ETH_MACHT1R_HT63T32_Msk             (0xFFFFFFFFU << ETH_MACHT1R_HT63T32_Pos)            /*!< 0xFFFFFFFF */
#define ETH_MACHT1R_HT63T32                 ETH_MACHT1R_HT63T32_Msk                             /*!< MAC Hash Table Second 32 Bits */
#define ETH_MACHT1R_HT63T32_0               (0x1U << ETH_MACHT1R_HT63T32_Pos)                   /*!< 0x00000001 */
#define ETH_MACHT1R_HT63T32_1               (0x2U << ETH_MACHT1R_HT63T32_Pos)                   /*!< 0x00000002 */
#define ETH_MACHT1R_HT63T32_2               (0x4U << ETH_MACHT1R_HT63T32_Pos)                   /*!< 0x00000004 */
#define ETH_MACHT1R_HT63T32_3               (0x8U << ETH_MACHT1R_HT63T32_Pos)                   /*!< 0x00000008 */
#define ETH_MACHT1R_HT63T32_4               (0x10U << ETH_MACHT1R_HT63T32_Pos)                  /*!< 0x00000010 */
#define ETH_MACHT1R_HT63T32_5               (0x20U << ETH_MACHT1R_HT63T32_Pos)                  /*!< 0x00000020 */
#define ETH_MACHT1R_HT63T32_6               (0x40U << ETH_MACHT1R_HT63T32_Pos)                  /*!< 0x00000040 */
#define ETH_MACHT1R_HT63T32_7               (0x80U << ETH_MACHT1R_HT63T32_Pos)                  /*!< 0x00000080 */
#define ETH_MACHT1R_HT63T32_8               (0x100U << ETH_MACHT1R_HT63T32_Pos)                 /*!< 0x00000100 */
#define ETH_MACHT1R_HT63T32_9               (0x200U << ETH_MACHT1R_HT63T32_Pos)                 /*!< 0x00000200 */
#define ETH_MACHT1R_HT63T32_10              (0x400U << ETH_MACHT1R_HT63T32_Pos)                 /*!< 0x00000400 */
#define ETH_MACHT1R_HT63T32_11              (0x800U << ETH_MACHT1R_HT63T32_Pos)                 /*!< 0x00000800 */
#define ETH_MACHT1R_HT63T32_12              (0x1000U << ETH_MACHT1R_HT63T32_Pos)                /*!< 0x00001000 */
#define ETH_MACHT1R_HT63T32_13              (0x2000U << ETH_MACHT1R_HT63T32_Pos)                /*!< 0x00002000 */
#define ETH_MACHT1R_HT63T32_14              (0x4000U << ETH_MACHT1R_HT63T32_Pos)                /*!< 0x00004000 */
#define ETH_MACHT1R_HT63T32_15              (0x8000U << ETH_MACHT1R_HT63T32_Pos)                /*!< 0x00008000 */
#define ETH_MACHT1R_HT63T32_16              (0x10000U << ETH_MACHT1R_HT63T32_Pos)               /*!< 0x00010000 */
#define ETH_MACHT1R_HT63T32_17              (0x20000U << ETH_MACHT1R_HT63T32_Pos)               /*!< 0x00020000 */
#define ETH_MACHT1R_HT63T32_18              (0x40000U << ETH_MACHT1R_HT63T32_Pos)               /*!< 0x00040000 */
#define ETH_MACHT1R_HT63T32_19              (0x80000U << ETH_MACHT1R_HT63T32_Pos)               /*!< 0x00080000 */
#define ETH_MACHT1R_HT63T32_20              (0x100000U << ETH_MACHT1R_HT63T32_Pos)              /*!< 0x00100000 */
#define ETH_MACHT1R_HT63T32_21              (0x200000U << ETH_MACHT1R_HT63T32_Pos)              /*!< 0x00200000 */
#define ETH_MACHT1R_HT63T32_22              (0x400000U << ETH_MACHT1R_HT63T32_Pos)              /*!< 0x00400000 */
#define ETH_MACHT1R_HT63T32_23              (0x800000U << ETH_MACHT1R_HT63T32_Pos)              /*!< 0x00800000 */
#define ETH_MACHT1R_HT63T32_24              (0x1000000U << ETH_MACHT1R_HT63T32_Pos)             /*!< 0x01000000 */
#define ETH_MACHT1R_HT63T32_25              (0x2000000U << ETH_MACHT1R_HT63T32_Pos)             /*!< 0x02000000 */
#define ETH_MACHT1R_HT63T32_26              (0x4000000U << ETH_MACHT1R_HT63T32_Pos)             /*!< 0x04000000 */
#define ETH_MACHT1R_HT63T32_27              (0x8000000U << ETH_MACHT1R_HT63T32_Pos)             /*!< 0x08000000 */
#define ETH_MACHT1R_HT63T32_28              (0x10000000U << ETH_MACHT1R_HT63T32_Pos)            /*!< 0x10000000 */
#define ETH_MACHT1R_HT63T32_29              (0x20000000U << ETH_MACHT1R_HT63T32_Pos)            /*!< 0x20000000 */
#define ETH_MACHT1R_HT63T32_30              (0x40000000U << ETH_MACHT1R_HT63T32_Pos)            /*!< 0x40000000 */
#define ETH_MACHT1R_HT63T32_31              (0x80000000U << ETH_MACHT1R_HT63T32_Pos)            /*!< 0x80000000 */

/**************  Bit definition for ETH_MACVTR register  ***************/
#define ETH_MACVTR_VL_Pos                   (0U)
#define ETH_MACVTR_VL_Msk                   (0xFFFFU << ETH_MACVTR_VL_Pos)                      /*!< 0x0000FFFF */
#define ETH_MACVTR_VL                       ETH_MACVTR_VL_Msk                                   /*!< VLAN Tag Identifier for Receive Packets */
#define ETH_MACVTR_VL_0                     (0x1U << ETH_MACVTR_VL_Pos)                         /*!< 0x00000001 */
#define ETH_MACVTR_VL_1                     (0x2U << ETH_MACVTR_VL_Pos)                         /*!< 0x00000002 */
#define ETH_MACVTR_VL_2                     (0x4U << ETH_MACVTR_VL_Pos)                         /*!< 0x00000004 */
#define ETH_MACVTR_VL_3                     (0x8U << ETH_MACVTR_VL_Pos)                         /*!< 0x00000008 */
#define ETH_MACVTR_VL_4                     (0x10U << ETH_MACVTR_VL_Pos)                        /*!< 0x00000010 */
#define ETH_MACVTR_VL_5                     (0x20U << ETH_MACVTR_VL_Pos)                        /*!< 0x00000020 */
#define ETH_MACVTR_VL_6                     (0x40U << ETH_MACVTR_VL_Pos)                        /*!< 0x00000040 */
#define ETH_MACVTR_VL_7                     (0x80U << ETH_MACVTR_VL_Pos)                        /*!< 0x00000080 */
#define ETH_MACVTR_VL_8                     (0x100U << ETH_MACVTR_VL_Pos)                       /*!< 0x00000100 */
#define ETH_MACVTR_VL_9                     (0x200U << ETH_MACVTR_VL_Pos)                       /*!< 0x00000200 */
#define ETH_MACVTR_VL_10                    (0x400U << ETH_MACVTR_VL_Pos)                       /*!< 0x00000400 */
#define ETH_MACVTR_VL_11                    (0x800U << ETH_MACVTR_VL_Pos)                       /*!< 0x00000800 */
#define ETH_MACVTR_VL_12                    (0x1000U << ETH_MACVTR_VL_Pos)                      /*!< 0x00001000 */
#define ETH_MACVTR_VL_13                    (0x2000U << ETH_MACVTR_VL_Pos)                      /*!< 0x00002000 */
#define ETH_MACVTR_VL_14                    (0x4000U << ETH_MACVTR_VL_Pos)                      /*!< 0x00004000 */
#define ETH_MACVTR_VL_15                    (0x8000U << ETH_MACVTR_VL_Pos)                      /*!< 0x00008000 */
#define ETH_MACVTR_ETV_Pos                  (16U)
#define ETH_MACVTR_ETV_Msk                  (0x1U << ETH_MACVTR_ETV_Pos)                        /*!< 0x00010000 */
#define ETH_MACVTR_ETV                      ETH_MACVTR_ETV_Msk                                  /*!< Enable 12-Bit VLAN Tag Comparison */
#define ETH_MACVTR_VTIM_Pos                 (17U)
#define ETH_MACVTR_VTIM_Msk                 (0x1U << ETH_MACVTR_VTIM_Pos)                       /*!< 0x00020000 */
#define ETH_MACVTR_VTIM                     ETH_MACVTR_VTIM_Msk                                 /*!< VLAN Tag Inverse Match Enable */
#define ETH_MACVTR_ESVL_Pos                 (18U)
#define ETH_MACVTR_ESVL_Msk                 (0x1U << ETH_MACVTR_ESVL_Pos)                       /*!< 0x00040000 */
#define ETH_MACVTR_ESVL                     ETH_MACVTR_ESVL_Msk                                 /*!< Enable S-VLAN */
#define ETH_MACVTR_ERSVLM_Pos               (19U)
#define ETH_MACVTR_ERSVLM_Msk               (0x1U << ETH_MACVTR_ERSVLM_Pos)                     /*!< 0x00080000 */
#define ETH_MACVTR_ERSVLM                   ETH_MACVTR_ERSVLM_Msk                               /*!< Enable Receive S-VLAN Match */
#define ETH_MACVTR_DOVLTC_Pos               (20U)
#define ETH_MACVTR_DOVLTC_Msk               (0x1U << ETH_MACVTR_DOVLTC_Pos)                     /*!< 0x00100000 */
#define ETH_MACVTR_DOVLTC                   ETH_MACVTR_DOVLTC_Msk                               /*!< Disable VLAN Type Check */
#define ETH_MACVTR_EVLS_Pos                 (21U)
#define ETH_MACVTR_EVLS_Msk                 (0x3U << ETH_MACVTR_EVLS_Pos)                       /*!< 0x00600000 */
#define ETH_MACVTR_EVLS                     ETH_MACVTR_EVLS_Msk                                 /*!< Enable VLAN Tag Stripping on Receive */
#define ETH_MACVTR_EVLS_0                   (0x1U << ETH_MACVTR_EVLS_Pos)                  /*!< 0x00200000 */
#define ETH_MACVTR_EVLS_1                   (0x2U << ETH_MACVTR_EVLS_Pos)                  /*!< 0x00400000 */
#define ETH_MACVTR_EVLRXS_Pos               (24U)
#define ETH_MACVTR_EVLRXS_Msk               (0x1U << ETH_MACVTR_EVLRXS_Pos)                     /*!< 0x01000000 */
#define ETH_MACVTR_EVLRXS                   ETH_MACVTR_EVLRXS_Msk                               /*!< Enable VLAN Tag in Rx status */
#define ETH_MACVTR_VTHM_Pos                 (25U)
#define ETH_MACVTR_VTHM_Msk                 (0x1U << ETH_MACVTR_VTHM_Pos)                       /*!< 0x02000000 */
#define ETH_MACVTR_VTHM                     ETH_MACVTR_VTHM_Msk                                 /*!< VLAN Tag Hash Table Match Enable */
#define ETH_MACVTR_EDVLP_Pos                (26U)
#define ETH_MACVTR_EDVLP_Msk                (0x1U << ETH_MACVTR_EDVLP_Pos)                      /*!< 0x04000000 */
#define ETH_MACVTR_EDVLP                    ETH_MACVTR_EDVLP_Msk                                /*!< Enable Double VLAN Processing */
#define ETH_MACVTR_ERIVLT_Pos               (27U)
#define ETH_MACVTR_ERIVLT_Msk               (0x1U << ETH_MACVTR_ERIVLT_Pos)                     /*!< 0x08000000 */
#define ETH_MACVTR_ERIVLT                   ETH_MACVTR_ERIVLT_Msk                               /*!< Enable Inner VLAN Tag */
#define ETH_MACVTR_EIVLS_Pos                (28U)
#define ETH_MACVTR_EIVLS_Msk                (0x3U << ETH_MACVTR_EIVLS_Pos)                      /*!< 0x30000000 */
#define ETH_MACVTR_EIVLS                    ETH_MACVTR_EIVLS_Msk                                /*!< Enable Inner VLAN Tag Stripping on Receive */
#define ETH_MACVTR_EIVLS_0                  (0x1U << ETH_MACVTR_EIVLS_Pos)               /*!< 0x10000000 */
#define ETH_MACVTR_EIVLS_1                  (0x2U << ETH_MACVTR_EIVLS_Pos)               /*!< 0x20000000 */
#define ETH_MACVTR_EIVLRXS_Pos              (31U)
#define ETH_MACVTR_EIVLRXS_Msk              (0x1U << ETH_MACVTR_EIVLRXS_Pos)                    /*!< 0x80000000 */
#define ETH_MACVTR_EIVLRXS                  ETH_MACVTR_EIVLRXS_Msk                              /*!< Enable Inner VLAN Tag in Rx Status */

/**************  Bit definition for ETH_MACVHTR register  **************/
#define ETH_MACVHTR_VLHT_Pos                (0U)
#define ETH_MACVHTR_VLHT_Msk                (0xFFFFU << ETH_MACVHTR_VLHT_Pos)                   /*!< 0x0000FFFF */
#define ETH_MACVHTR_VLHT                    ETH_MACVHTR_VLHT_Msk                                /*!< VLAN Hash Table */
#define ETH_MACVHTR_VLHT_0                  (0x1U << ETH_MACVHTR_VLHT_Pos)                      /*!< 0x00000001 */
#define ETH_MACVHTR_VLHT_1                  (0x2U << ETH_MACVHTR_VLHT_Pos)                      /*!< 0x00000002 */
#define ETH_MACVHTR_VLHT_2                  (0x4U << ETH_MACVHTR_VLHT_Pos)                      /*!< 0x00000004 */
#define ETH_MACVHTR_VLHT_3                  (0x8U << ETH_MACVHTR_VLHT_Pos)                      /*!< 0x00000008 */
#define ETH_MACVHTR_VLHT_4                  (0x10U << ETH_MACVHTR_VLHT_Pos)                     /*!< 0x00000010 */
#define ETH_MACVHTR_VLHT_5                  (0x20U << ETH_MACVHTR_VLHT_Pos)                     /*!< 0x00000020 */
#define ETH_MACVHTR_VLHT_6                  (0x40U << ETH_MACVHTR_VLHT_Pos)                     /*!< 0x00000040 */
#define ETH_MACVHTR_VLHT_7                  (0x80U << ETH_MACVHTR_VLHT_Pos)                     /*!< 0x00000080 */
#define ETH_MACVHTR_VLHT_8                  (0x100U << ETH_MACVHTR_VLHT_Pos)                    /*!< 0x00000100 */
#define ETH_MACVHTR_VLHT_9                  (0x200U << ETH_MACVHTR_VLHT_Pos)                    /*!< 0x00000200 */
#define ETH_MACVHTR_VLHT_10                 (0x400U << ETH_MACVHTR_VLHT_Pos)                    /*!< 0x00000400 */
#define ETH_MACVHTR_VLHT_11                 (0x800U << ETH_MACVHTR_VLHT_Pos)                    /*!< 0x00000800 */
#define ETH_MACVHTR_VLHT_12                 (0x1000U << ETH_MACVHTR_VLHT_Pos)                   /*!< 0x00001000 */
#define ETH_MACVHTR_VLHT_13                 (0x2000U << ETH_MACVHTR_VLHT_Pos)                   /*!< 0x00002000 */
#define ETH_MACVHTR_VLHT_14                 (0x4000U << ETH_MACVHTR_VLHT_Pos)                   /*!< 0x00004000 */
#define ETH_MACVHTR_VLHT_15                 (0x8000U << ETH_MACVHTR_VLHT_Pos)                   /*!< 0x00008000 */

/**************  Bit definition for ETH_MACVIR register  ***************/
#define ETH_MACVIR_VLT_Pos                  (0U)
#define ETH_MACVIR_VLT_Msk                  (0xFFFFU << ETH_MACVIR_VLT_Pos)                     /*!< 0x0000FFFF */
#define ETH_MACVIR_VLT                      ETH_MACVIR_VLT_Msk                                  /*!< VLAN Tag for Transmit Packets */
#define ETH_MACVIR_VLT_0                    (0x1U << ETH_MACVIR_VLT_Pos)                        /*!< 0x00000001 */
#define ETH_MACVIR_VLT_1                    (0x2U << ETH_MACVIR_VLT_Pos)                        /*!< 0x00000002 */
#define ETH_MACVIR_VLT_2                    (0x4U << ETH_MACVIR_VLT_Pos)                        /*!< 0x00000004 */
#define ETH_MACVIR_VLT_3                    (0x8U << ETH_MACVIR_VLT_Pos)                        /*!< 0x00000008 */
#define ETH_MACVIR_VLT_4                    (0x10U << ETH_MACVIR_VLT_Pos)                       /*!< 0x00000010 */
#define ETH_MACVIR_VLT_5                    (0x20U << ETH_MACVIR_VLT_Pos)                       /*!< 0x00000020 */
#define ETH_MACVIR_VLT_6                    (0x40U << ETH_MACVIR_VLT_Pos)                       /*!< 0x00000040 */
#define ETH_MACVIR_VLT_7                    (0x80U << ETH_MACVIR_VLT_Pos)                       /*!< 0x00000080 */
#define ETH_MACVIR_VLT_8                    (0x100U << ETH_MACVIR_VLT_Pos)                      /*!< 0x00000100 */
#define ETH_MACVIR_VLT_9                    (0x200U << ETH_MACVIR_VLT_Pos)                      /*!< 0x00000200 */
#define ETH_MACVIR_VLT_10                   (0x400U << ETH_MACVIR_VLT_Pos)                      /*!< 0x00000400 */
#define ETH_MACVIR_VLT_11                   (0x800U << ETH_MACVIR_VLT_Pos)                      /*!< 0x00000800 */
#define ETH_MACVIR_VLT_12                   (0x1000U << ETH_MACVIR_VLT_Pos)                     /*!< 0x00001000 */
#define ETH_MACVIR_VLT_13                   (0x2000U << ETH_MACVIR_VLT_Pos)                     /*!< 0x00002000 */
#define ETH_MACVIR_VLT_14                   (0x4000U << ETH_MACVIR_VLT_Pos)                     /*!< 0x00004000 */
#define ETH_MACVIR_VLT_15                   (0x8000U << ETH_MACVIR_VLT_Pos)                     /*!< 0x00008000 */
#define ETH_MACVIR_VLC_Pos                  (16U)
#define ETH_MACVIR_VLC_Msk                  (0x3U << ETH_MACVIR_VLC_Pos)                        /*!< 0x00030000 */
#define ETH_MACVIR_VLC                      ETH_MACVIR_VLC_Msk                                  /*!< VLAN Tag Control in Transmit Packets */
#define ETH_MACVIR_VLC_0                    (0x1U << ETH_MACVIR_VLC_Pos)                    /*!< 0x00010000 */
#define ETH_MACVIR_VLC_1                    (0x2U << ETH_MACVIR_VLC_Pos)                    /*!< 0x00020000 */
#define ETH_MACVIR_VLP_Pos                  (18U)
#define ETH_MACVIR_VLP_Msk                  (0x1U << ETH_MACVIR_VLP_Pos)                        /*!< 0x00040000 */
#define ETH_MACVIR_VLP                      ETH_MACVIR_VLP_Msk                                  /*!< VLAN Priority Control */
#define ETH_MACVIR_CSVL_Pos                 (19U)
#define ETH_MACVIR_CSVL_Msk                 (0x1U << ETH_MACVIR_CSVL_Pos)                       /*!< 0x00080000 */
#define ETH_MACVIR_CSVL                     ETH_MACVIR_CSVL_Msk                                 /*!< C-VLAN or S-VLAN */
#define ETH_MACVIR_VLTI_Pos                 (20U)
#define ETH_MACVIR_VLTI_Msk                 (0x1U << ETH_MACVIR_VLTI_Pos)                       /*!< 0x00100000 */
#define ETH_MACVIR_VLTI                     ETH_MACVIR_VLTI_Msk                                 /*!< VLAN Tag Input */

/**************  Bit definition for ETH_MACIVIR register  **************/
#define ETH_MACIVIR_VLT_Pos                 (0U)
#define ETH_MACIVIR_VLT_Msk                 (0xFFFFU << ETH_MACIVIR_VLT_Pos)                    /*!< 0x0000FFFF */
#define ETH_MACIVIR_VLT                     ETH_MACIVIR_VLT_Msk                                 /*!< VLAN Tag for Transmit Packets */
#define ETH_MACIVIR_VLT_0                   (0x1U << ETH_MACIVIR_VLT_Pos)                       /*!< 0x00000001 */
#define ETH_MACIVIR_VLT_1                   (0x2U << ETH_MACIVIR_VLT_Pos)                       /*!< 0x00000002 */
#define ETH_MACIVIR_VLT_2                   (0x4U << ETH_MACIVIR_VLT_Pos)                       /*!< 0x00000004 */
#define ETH_MACIVIR_VLT_3                   (0x8U << ETH_MACIVIR_VLT_Pos)                       /*!< 0x00000008 */
#define ETH_MACIVIR_VLT_4                   (0x10U << ETH_MACIVIR_VLT_Pos)                      /*!< 0x00000010 */
#define ETH_MACIVIR_VLT_5                   (0x20U << ETH_MACIVIR_VLT_Pos)                      /*!< 0x00000020 */
#define ETH_MACIVIR_VLT_6                   (0x40U << ETH_MACIVIR_VLT_Pos)                      /*!< 0x00000040 */
#define ETH_MACIVIR_VLT_7                   (0x80U << ETH_MACIVIR_VLT_Pos)                      /*!< 0x00000080 */
#define ETH_MACIVIR_VLT_8                   (0x100U << ETH_MACIVIR_VLT_Pos)                     /*!< 0x00000100 */
#define ETH_MACIVIR_VLT_9                   (0x200U << ETH_MACIVIR_VLT_Pos)                     /*!< 0x00000200 */
#define ETH_MACIVIR_VLT_10                  (0x400U << ETH_MACIVIR_VLT_Pos)                     /*!< 0x00000400 */
#define ETH_MACIVIR_VLT_11                  (0x800U << ETH_MACIVIR_VLT_Pos)                     /*!< 0x00000800 */
#define ETH_MACIVIR_VLT_12                  (0x1000U << ETH_MACIVIR_VLT_Pos)                    /*!< 0x00001000 */
#define ETH_MACIVIR_VLT_13                  (0x2000U << ETH_MACIVIR_VLT_Pos)                    /*!< 0x00002000 */
#define ETH_MACIVIR_VLT_14                  (0x4000U << ETH_MACIVIR_VLT_Pos)                    /*!< 0x00004000 */
#define ETH_MACIVIR_VLT_15                  (0x8000U << ETH_MACIVIR_VLT_Pos)                    /*!< 0x00008000 */
#define ETH_MACIVIR_VLC_Pos                 (16U)
#define ETH_MACIVIR_VLC_Msk                 (0x3U << ETH_MACIVIR_VLC_Pos)                       /*!< 0x00030000 */
#define ETH_MACIVIR_VLC                     ETH_MACIVIR_VLC_Msk                                 /*!< VLAN Tag Control in Transmit Packets */
#define ETH_MACIVIR_VLC_0                   (0x1U << ETH_MACIVIR_VLC_Pos)                   /*!< 0x00010000 */
#define ETH_MACIVIR_VLC_1                   (0x2U << ETH_MACIVIR_VLC_Pos)                   /*!< 0x00020000 */
#define ETH_MACIVIR_VLP_Pos                 (18U)
#define ETH_MACIVIR_VLP_Msk                 (0x1U << ETH_MACIVIR_VLP_Pos)                       /*!< 0x00040000 */
#define ETH_MACIVIR_VLP                     ETH_MACIVIR_VLP_Msk                                 /*!< VLAN Priority Control */
#define ETH_MACIVIR_CSVL_Pos                (19U)
#define ETH_MACIVIR_CSVL_Msk                (0x1U << ETH_MACIVIR_CSVL_Pos)                      /*!< 0x00080000 */
#define ETH_MACIVIR_CSVL                    ETH_MACIVIR_CSVL_Msk                                /*!< C-VLAN or S-VLAN */
#define ETH_MACIVIR_VLTI_Pos                (20U)
#define ETH_MACIVIR_VLTI_Msk                (0x1U << ETH_MACIVIR_VLTI_Pos)                      /*!< 0x00100000 */
#define ETH_MACIVIR_VLTI                    ETH_MACIVIR_VLTI_Msk                                /*!< VLAN Tag Input */

/************  Bit definition for ETH_MACQ0TXFCR register  *************/
#define ETH_MACQ0TXFCR_FCB_BPA_Pos          (0U)
#define ETH_MACQ0TXFCR_FCB_BPA_Msk          (0x1U << ETH_MACQ0TXFCR_FCB_BPA_Pos)                /*!< 0x00000001 */
#define ETH_MACQ0TXFCR_FCB_BPA              ETH_MACQ0TXFCR_FCB_BPA_Msk                          /*!< Flow Control Busy or Backpressure Activate */
#define ETH_MACQ0TXFCR_TFE_Pos              (1U)
#define ETH_MACQ0TXFCR_TFE_Msk              (0x1U << ETH_MACQ0TXFCR_TFE_Pos)                    /*!< 0x00000002 */
#define ETH_MACQ0TXFCR_TFE                  ETH_MACQ0TXFCR_TFE_Msk                              /*!< Transmit Flow Control Enable */
#define ETH_MACQ0TXFCR_PLT_Pos              (4U)
#define ETH_MACQ0TXFCR_PLT_Msk              (0x7U << ETH_MACQ0TXFCR_PLT_Pos)                    /*!< 0x00000070 */
#define ETH_MACQ0TXFCR_PLT                  ETH_MACQ0TXFCR_PLT_Msk                              /*!< Pause Low Threshold */
#define ETH_MACQ0TXFCR_PLT_0                (0x1U << ETH_MACQ0TXFCR_PLT_Pos)                   /*!< 0x00000010 */
#define ETH_MACQ0TXFCR_PLT_1                (0x2U << ETH_MACQ0TXFCR_PLT_Pos)                   /*!< 0x00000020 */
#define ETH_MACQ0TXFCR_PLT_2                (0x4U << ETH_MACQ0TXFCR_PLT_Pos)                   /*!< 0x00000040 */
#define ETH_MACQ0TXFCR_DZPQ_Pos             (7U)
#define ETH_MACQ0TXFCR_DZPQ_Msk             (0x1U << ETH_MACQ0TXFCR_DZPQ_Pos)                   /*!< 0x00000080 */
#define ETH_MACQ0TXFCR_DZPQ                 ETH_MACQ0TXFCR_DZPQ_Msk                             /*!< Disable Zero-Quanta Pause */
#define ETH_MACQ0TXFCR_PT_Pos               (16U)
#define ETH_MACQ0TXFCR_PT_Msk               (0xFFFFU << ETH_MACQ0TXFCR_PT_Pos)                  /*!< 0xFFFF0000 */
#define ETH_MACQ0TXFCR_PT                   ETH_MACQ0TXFCR_PT_Msk                               /*!< Pause Time */
#define ETH_MACQ0TXFCR_PT_0                 (0x1U << ETH_MACQ0TXFCR_PT_Pos)                 /*!< 0x00010000 */
#define ETH_MACQ0TXFCR_PT_1                 (0x2U << ETH_MACQ0TXFCR_PT_Pos)                 /*!< 0x00020000 */
#define ETH_MACQ0TXFCR_PT_2                 (0x4U << ETH_MACQ0TXFCR_PT_Pos)                 /*!< 0x00040000 */
#define ETH_MACQ0TXFCR_PT_3                 (0x8U << ETH_MACQ0TXFCR_PT_Pos)                 /*!< 0x00080000 */
#define ETH_MACQ0TXFCR_PT_4                 (0x10U << ETH_MACQ0TXFCR_PT_Pos)                /*!< 0x00100000 */
#define ETH_MACQ0TXFCR_PT_5                 (0x20U << ETH_MACQ0TXFCR_PT_Pos)                /*!< 0x00200000 */
#define ETH_MACQ0TXFCR_PT_6                 (0x40U << ETH_MACQ0TXFCR_PT_Pos)                /*!< 0x00400000 */
#define ETH_MACQ0TXFCR_PT_7                 (0x80U << ETH_MACQ0TXFCR_PT_Pos)                /*!< 0x00800000 */
#define ETH_MACQ0TXFCR_PT_8                 (0x100U << ETH_MACQ0TXFCR_PT_Pos)               /*!< 0x01000000 */
#define ETH_MACQ0TXFCR_PT_9                 (0x200U << ETH_MACQ0TXFCR_PT_Pos)               /*!< 0x02000000 */
#define ETH_MACQ0TXFCR_PT_10                (0x400U << ETH_MACQ0TXFCR_PT_Pos)               /*!< 0x04000000 */
#define ETH_MACQ0TXFCR_PT_11                (0x800U << ETH_MACQ0TXFCR_PT_Pos)               /*!< 0x08000000 */
#define ETH_MACQ0TXFCR_PT_12                (0x1000U << ETH_MACQ0TXFCR_PT_Pos)              /*!< 0x10000000 */
#define ETH_MACQ0TXFCR_PT_13                (0x2000U << ETH_MACQ0TXFCR_PT_Pos)              /*!< 0x20000000 */
#define ETH_MACQ0TXFCR_PT_14                (0x4000U << ETH_MACQ0TXFCR_PT_Pos)              /*!< 0x40000000 */
#define ETH_MACQ0TXFCR_PT_15                (0x8000U << ETH_MACQ0TXFCR_PT_Pos)              /*!< 0x80000000 */

/*************  Bit definition for ETH_MACRXFCR register  **************/
#define ETH_MACRXFCR_RFE_Pos                (0U)
#define ETH_MACRXFCR_RFE_Msk                (0x1U << ETH_MACRXFCR_RFE_Pos)                      /*!< 0x00000001 */
#define ETH_MACRXFCR_RFE                    ETH_MACRXFCR_RFE_Msk                                /*!< Receive Flow Control Enable */
#define ETH_MACRXFCR_UP_Pos                 (1U)
#define ETH_MACRXFCR_UP_Msk                 (0x1U << ETH_MACRXFCR_UP_Pos)                       /*!< 0x00000002 */
#define ETH_MACRXFCR_UP                     ETH_MACRXFCR_UP_Msk                                 /*!< Unicast Pause Packet Detect */

/*************  Bit definition for ETH_MACTXQPMR register  *************/
#define ETH_MACTXQPMR_PSTQ0_Pos             (0U)
#define ETH_MACTXQPMR_PSTQ0_Msk             (0xFFU << ETH_MACTXQPMR_PSTQ0_Pos)                  /*!< 0x000000FF */
#define ETH_MACTXQPMR_PSTQ0                 ETH_MACTXQPMR_PSTQ0_Msk                             /*!< Priorities Selected in Transmit Queue 0 */
#define ETH_MACTXQPMR_PSTQ0_0               (0x1U << ETH_MACTXQPMR_PSTQ0_Pos)                   /*!< 0x00000001 */
#define ETH_MACTXQPMR_PSTQ0_1               (0x2U << ETH_MACTXQPMR_PSTQ0_Pos)                   /*!< 0x00000002 */
#define ETH_MACTXQPMR_PSTQ0_2               (0x4U << ETH_MACTXQPMR_PSTQ0_Pos)                   /*!< 0x00000004 */
#define ETH_MACTXQPMR_PSTQ0_3               (0x8U << ETH_MACTXQPMR_PSTQ0_Pos)                   /*!< 0x00000008 */
#define ETH_MACTXQPMR_PSTQ0_4               (0x10U << ETH_MACTXQPMR_PSTQ0_Pos)                  /*!< 0x00000010 */
#define ETH_MACTXQPMR_PSTQ0_5               (0x20U << ETH_MACTXQPMR_PSTQ0_Pos)                  /*!< 0x00000020 */
#define ETH_MACTXQPMR_PSTQ0_6               (0x40U << ETH_MACTXQPMR_PSTQ0_Pos)                  /*!< 0x00000040 */
#define ETH_MACTXQPMR_PSTQ0_7               (0x80U << ETH_MACTXQPMR_PSTQ0_Pos)                  /*!< 0x00000080 */
#define ETH_MACTXQPMR_PSTQ1_Pos             (8U)
#define ETH_MACTXQPMR_PSTQ1_Msk             (0xFFU << ETH_MACTXQPMR_PSTQ1_Pos)                  /*!< 0x0000FF00 */
#define ETH_MACTXQPMR_PSTQ1                 ETH_MACTXQPMR_PSTQ1_Msk                             /*!< Priorities Selected in Transmit Queue 1 */
#define ETH_MACTXQPMR_PSTQ1_0               (0x1U << ETH_MACTXQPMR_PSTQ1_Pos)                 /*!< 0x00000100 */
#define ETH_MACTXQPMR_PSTQ1_1               (0x2U << ETH_MACTXQPMR_PSTQ1_Pos)                 /*!< 0x00000200 */
#define ETH_MACTXQPMR_PSTQ1_2               (0x4U << ETH_MACTXQPMR_PSTQ1_Pos)                 /*!< 0x00000400 */
#define ETH_MACTXQPMR_PSTQ1_3               (0x8U << ETH_MACTXQPMR_PSTQ1_Pos)                 /*!< 0x00000800 */
#define ETH_MACTXQPMR_PSTQ1_4               (0x10U << ETH_MACTXQPMR_PSTQ1_Pos)                /*!< 0x00001000 */
#define ETH_MACTXQPMR_PSTQ1_5               (0x20U << ETH_MACTXQPMR_PSTQ1_Pos)                /*!< 0x00002000 */
#define ETH_MACTXQPMR_PSTQ1_6               (0x40U << ETH_MACTXQPMR_PSTQ1_Pos)                /*!< 0x00004000 */
#define ETH_MACTXQPMR_PSTQ1_7               (0x80U << ETH_MACTXQPMR_PSTQ1_Pos)                /*!< 0x00008000 */

/*************  Bit definition for ETH_MACRXQC0R register  *************/
#define ETH_MACRXQC0R_RXQ0EN_Pos            (0U)
#define ETH_MACRXQC0R_RXQ0EN_Msk            (0x3U << ETH_MACRXQC0R_RXQ0EN_Pos)                  /*!< 0x00000003 */
#define ETH_MACRXQC0R_RXQ0EN                ETH_MACRXQC0R_RXQ0EN_Msk                            /*!< Receive Queue 0 Enable */
#define ETH_MACRXQC0R_RXQ0EN_0              (0x1U << ETH_MACRXQC0R_RXQ0EN_Pos)                  /*!< 0x00000001 */
#define ETH_MACRXQC0R_RXQ0EN_1              (0x2U << ETH_MACRXQC0R_RXQ0EN_Pos)                  /*!< 0x00000002 */
#define ETH_MACRXQC0R_RXQ1EN_Pos            (2U)
#define ETH_MACRXQC0R_RXQ1EN_Msk            (0x3U << ETH_MACRXQC0R_RXQ1EN_Pos)                  /*!< 0x0000000C */
#define ETH_MACRXQC0R_RXQ1EN                ETH_MACRXQC0R_RXQ1EN_Msk                            /*!< Receive Queue 1 Enable */
#define ETH_MACRXQC0R_RXQ1EN_0              (0x1U << ETH_MACRXQC0R_RXQ1EN_Pos)                  /*!< 0x00000004 */
#define ETH_MACRXQC0R_RXQ1EN_1              (0x2U << ETH_MACRXQC0R_RXQ1EN_Pos)                  /*!< 0x00000008 */

/*************  Bit definition for ETH_MACRXQC1R register  *************/
#define ETH_MACRXQC1R_AVCPQ_Pos             (0U)
#define ETH_MACRXQC1R_AVCPQ_Msk             (0x7U << ETH_MACRXQC1R_AVCPQ_Pos)                   /*!< 0x00000007 */
#define ETH_MACRXQC1R_AVCPQ                 ETH_MACRXQC1R_AVCPQ_Msk                             /*!< AV Untagged Control Packets Queue */
#define ETH_MACRXQC1R_AVCPQ_0               (0x1U << ETH_MACRXQC1R_AVCPQ_Pos)                   /*!< 0x00000001 */
#define ETH_MACRXQC1R_AVCPQ_1               (0x2U << ETH_MACRXQC1R_AVCPQ_Pos)                   /*!< 0x00000002 */
#define ETH_MACRXQC1R_AVCPQ_2               (0x4U << ETH_MACRXQC1R_AVCPQ_Pos)                   /*!< 0x00000004 */
#define ETH_MACRXQC1R_AVPTPQ_Pos            (4U)
#define ETH_MACRXQC1R_AVPTPQ_Msk            (0x7U << ETH_MACRXQC1R_AVPTPQ_Pos)                  /*!< 0x00000070 */
#define ETH_MACRXQC1R_AVPTPQ                ETH_MACRXQC1R_AVPTPQ_Msk                            /*!< AV PTP Packets Queue */
#define ETH_MACRXQC1R_AVPTPQ_0              (0x1U << ETH_MACRXQC1R_AVPTPQ_Pos)                 /*!< 0x00000010 */
#define ETH_MACRXQC1R_AVPTPQ_1              (0x2U << ETH_MACRXQC1R_AVPTPQ_Pos)                 /*!< 0x00000020 */
#define ETH_MACRXQC1R_AVPTPQ_2              (0x4U << ETH_MACRXQC1R_AVPTPQ_Pos)                 /*!< 0x00000040 */
#define ETH_MACRXQC1R_UPQ_Pos               (12U)
#define ETH_MACRXQC1R_UPQ_Msk               (0x7U << ETH_MACRXQC1R_UPQ_Pos)                     /*!< 0x00007000 */
#define ETH_MACRXQC1R_UPQ                   ETH_MACRXQC1R_UPQ_Msk                               /*!< Untagged Packet Queue */
#define ETH_MACRXQC1R_UPQ_0                 (0x1U << ETH_MACRXQC1R_UPQ_Pos)                  /*!< 0x00001000 */
#define ETH_MACRXQC1R_UPQ_1                 (0x2U << ETH_MACRXQC1R_UPQ_Pos)                  /*!< 0x00002000 */
#define ETH_MACRXQC1R_UPQ_2                 (0x4U << ETH_MACRXQC1R_UPQ_Pos)                  /*!< 0x00004000 */
#define ETH_MACRXQC1R_MCBCQ_Pos             (16U)
#define ETH_MACRXQC1R_MCBCQ_Msk             (0x7U << ETH_MACRXQC1R_MCBCQ_Pos)                   /*!< 0x00070000 */
#define ETH_MACRXQC1R_MCBCQ                 ETH_MACRXQC1R_MCBCQ_Msk                             /*!< Multicast and Broadcast Queue */
#define ETH_MACRXQC1R_MCBCQ_0               (0x1U << ETH_MACRXQC1R_MCBCQ_Pos)               /*!< 0x00010000 */
#define ETH_MACRXQC1R_MCBCQ_1               (0x2U << ETH_MACRXQC1R_MCBCQ_Pos)               /*!< 0x00020000 */
#define ETH_MACRXQC1R_MCBCQ_2               (0x4U << ETH_MACRXQC1R_MCBCQ_Pos)               /*!< 0x00040000 */
#define ETH_MACRXQC1R_MCBCQEN_Pos           (20U)
#define ETH_MACRXQC1R_MCBCQEN_Msk           (0x1U << ETH_MACRXQC1R_MCBCQEN_Pos)                 /*!< 0x00100000 */
#define ETH_MACRXQC1R_MCBCQEN               ETH_MACRXQC1R_MCBCQEN_Msk                           /*!< Multicast and Broadcast Queue Enable */
#define ETH_MACRXQC1R_TACPQE_Pos            (21U)
#define ETH_MACRXQC1R_TACPQE_Msk            (0x1U << ETH_MACRXQC1R_TACPQE_Pos)                  /*!< 0x00200000 */
#define ETH_MACRXQC1R_TACPQE                ETH_MACRXQC1R_TACPQE_Msk                            /*!< Tagged AV Control Packets Queuing Enable. */

/*************  Bit definition for ETH_MACRXQC2R register  *************/
#define ETH_MACRXQC2R_PSRQ0_Pos             (0U)
#define ETH_MACRXQC2R_PSRQ0_Msk             (0xFFU << ETH_MACRXQC2R_PSRQ0_Pos)                  /*!< 0x000000FF */
#define ETH_MACRXQC2R_PSRQ0                 ETH_MACRXQC2R_PSRQ0_Msk                             /*!< Priorities Selected in the Receive Queue 0 */
#define ETH_MACRXQC2R_PSRQ0_0               (0x1U << ETH_MACRXQC2R_PSRQ0_Pos)                   /*!< 0x00000001 */
#define ETH_MACRXQC2R_PSRQ0_1               (0x2U << ETH_MACRXQC2R_PSRQ0_Pos)                   /*!< 0x00000002 */
#define ETH_MACRXQC2R_PSRQ0_2               (0x4U << ETH_MACRXQC2R_PSRQ0_Pos)                   /*!< 0x00000004 */
#define ETH_MACRXQC2R_PSRQ0_3               (0x8U << ETH_MACRXQC2R_PSRQ0_Pos)                   /*!< 0x00000008 */
#define ETH_MACRXQC2R_PSRQ0_4               (0x10U << ETH_MACRXQC2R_PSRQ0_Pos)                  /*!< 0x00000010 */
#define ETH_MACRXQC2R_PSRQ0_5               (0x20U << ETH_MACRXQC2R_PSRQ0_Pos)                  /*!< 0x00000020 */
#define ETH_MACRXQC2R_PSRQ0_6               (0x40U << ETH_MACRXQC2R_PSRQ0_Pos)                  /*!< 0x00000040 */
#define ETH_MACRXQC2R_PSRQ0_7               (0x80U << ETH_MACRXQC2R_PSRQ0_Pos)                  /*!< 0x00000080 */
#define ETH_MACRXQC2R_PSRQ1_Pos             (8U)
#define ETH_MACRXQC2R_PSRQ1_Msk             (0xFFU << ETH_MACRXQC2R_PSRQ1_Pos)                  /*!< 0x0000FF00 */
#define ETH_MACRXQC2R_PSRQ1                 ETH_MACRXQC2R_PSRQ1_Msk                             /*!< Priorities Selected in the Receive Queue 1 */
#define ETH_MACRXQC2R_PSRQ1_0               (0x1U << ETH_MACRXQC2R_PSRQ1_Pos)                 /*!< 0x00000100 */
#define ETH_MACRXQC2R_PSRQ1_1               (0x2U << ETH_MACRXQC2R_PSRQ1_Pos)                 /*!< 0x00000200 */
#define ETH_MACRXQC2R_PSRQ1_2               (0x4U << ETH_MACRXQC2R_PSRQ1_Pos)                 /*!< 0x00000400 */
#define ETH_MACRXQC2R_PSRQ1_3               (0x8U << ETH_MACRXQC2R_PSRQ1_Pos)                 /*!< 0x00000800 */
#define ETH_MACRXQC2R_PSRQ1_4               (0x10U << ETH_MACRXQC2R_PSRQ1_Pos)                /*!< 0x00001000 */
#define ETH_MACRXQC2R_PSRQ1_5               (0x20U << ETH_MACRXQC2R_PSRQ1_Pos)                /*!< 0x00002000 */
#define ETH_MACRXQC2R_PSRQ1_6               (0x40U << ETH_MACRXQC2R_PSRQ1_Pos)                /*!< 0x00004000 */
#define ETH_MACRXQC2R_PSRQ1_7               (0x80U << ETH_MACRXQC2R_PSRQ1_Pos)                /*!< 0x00008000 */

/**************  Bit definition for ETH_MACISR register  ***************/
#define ETH_MACISR_RGSMIIIS_Pos             (0U)
#define ETH_MACISR_RGSMIIIS_Msk             (0x1U << ETH_MACISR_RGSMIIIS_Pos)                   /*!< 0x00000001 */
#define ETH_MACISR_RGSMIIIS                 ETH_MACISR_RGSMIIIS_Msk                             /*!< RGMII or SMII Interrupt Status */
#define ETH_MACISR_PHYIS_Pos                (3U)
#define ETH_MACISR_PHYIS_Msk                (0x1U << ETH_MACISR_PHYIS_Pos)                      /*!< 0x00000008 */
#define ETH_MACISR_PHYIS                    ETH_MACISR_PHYIS_Msk                                /*!< PHY Interrupt */
#define ETH_MACISR_PMTIS_Pos                (4U)
#define ETH_MACISR_PMTIS_Msk                (0x1U << ETH_MACISR_PMTIS_Pos)                      /*!< 0x00000010 */
#define ETH_MACISR_PMTIS                    ETH_MACISR_PMTIS_Msk                                /*!< PMT Interrupt Status */
#define ETH_MACISR_LPIIS_Pos                (5U)
#define ETH_MACISR_LPIIS_Msk                (0x1U << ETH_MACISR_LPIIS_Pos)                      /*!< 0x00000020 */
#define ETH_MACISR_LPIIS                    ETH_MACISR_LPIIS_Msk                                /*!< LPI Interrupt Status */
#define ETH_MACISR_MMCIS_Pos                (8U)
#define ETH_MACISR_MMCIS_Msk                (0x1U << ETH_MACISR_MMCIS_Pos)                      /*!< 0x00000100 */
#define ETH_MACISR_MMCIS                    ETH_MACISR_MMCIS_Msk                                /*!< MMC Interrupt Status */
#define ETH_MACISR_MMCRXIS_Pos              (9U)
#define ETH_MACISR_MMCRXIS_Msk              (0x1U << ETH_MACISR_MMCRXIS_Pos)                    /*!< 0x00000200 */
#define ETH_MACISR_MMCRXIS                  ETH_MACISR_MMCRXIS_Msk                              /*!< MMC Receive Interrupt Status */
#define ETH_MACISR_MMCTXIS_Pos              (10U)
#define ETH_MACISR_MMCTXIS_Msk              (0x1U << ETH_MACISR_MMCTXIS_Pos)                    /*!< 0x00000400 */
#define ETH_MACISR_MMCTXIS                  ETH_MACISR_MMCTXIS_Msk                              /*!< MMC Transmit Interrupt Status */
#define ETH_MACISR_TSIS_Pos                 (12U)
#define ETH_MACISR_TSIS_Msk                 (0x1U << ETH_MACISR_TSIS_Pos)                       /*!< 0x00001000 */
#define ETH_MACISR_TSIS                     ETH_MACISR_TSIS_Msk                                 /*!< Timestamp Interrupt Status */
#define ETH_MACISR_TXSTSIS_Pos              (13U)
#define ETH_MACISR_TXSTSIS_Msk              (0x1U << ETH_MACISR_TXSTSIS_Pos)                    /*!< 0x00002000 */
#define ETH_MACISR_TXSTSIS                  ETH_MACISR_TXSTSIS_Msk                              /*!< Transmit Status Interrupt */
#define ETH_MACISR_RXSTSIS_Pos              (14U)
#define ETH_MACISR_RXSTSIS_Msk              (0x1U << ETH_MACISR_RXSTSIS_Pos)                    /*!< 0x00004000 */
#define ETH_MACISR_RXSTSIS                  ETH_MACISR_RXSTSIS_Msk                              /*!< Receive Status Interrupt */

/**************  Bit definition for ETH_MACIER register  ***************/
#define ETH_MACIER_RGSMIIIE_Pos             (0U)
#define ETH_MACIER_RGSMIIIE_Msk             (0x1U << ETH_MACIER_RGSMIIIE_Pos)                   /*!< 0x00000001 */
#define ETH_MACIER_RGSMIIIE                 ETH_MACIER_RGSMIIIE_Msk                             /*!< RGMII or SMII Interrupt Enable */
#define ETH_MACIER_PHYIE_Pos                (3U)
#define ETH_MACIER_PHYIE_Msk                (0x1U << ETH_MACIER_PHYIE_Pos)                      /*!< 0x00000008 */
#define ETH_MACIER_PHYIE                    ETH_MACIER_PHYIE_Msk                                /*!< PHY Interrupt Enable */
#define ETH_MACIER_PMTIE_Pos                (4U)
#define ETH_MACIER_PMTIE_Msk                (0x1U << ETH_MACIER_PMTIE_Pos)                      /*!< 0x00000010 */
#define ETH_MACIER_PMTIE                    ETH_MACIER_PMTIE_Msk                                /*!< PMT Interrupt Enable */
#define ETH_MACIER_LPIIE_Pos                (5U)
#define ETH_MACIER_LPIIE_Msk                (0x1U << ETH_MACIER_LPIIE_Pos)                      /*!< 0x00000020 */
#define ETH_MACIER_LPIIE                    ETH_MACIER_LPIIE_Msk                                /*!< LPI Interrupt Enable */
#define ETH_MACIER_TSIE_Pos                 (12U)
#define ETH_MACIER_TSIE_Msk                 (0x1U << ETH_MACIER_TSIE_Pos)                       /*!< 0x00001000 */
#define ETH_MACIER_TSIE                     ETH_MACIER_TSIE_Msk                                 /*!< Timestamp Interrupt Enable */
#define ETH_MACIER_TXSTSIE_Pos              (13U)
#define ETH_MACIER_TXSTSIE_Msk              (0x1U << ETH_MACIER_TXSTSIE_Pos)                    /*!< 0x00002000 */
#define ETH_MACIER_TXSTSIE                  ETH_MACIER_TXSTSIE_Msk                              /*!< Transmit Status Interrupt Enable */
#define ETH_MACIER_RXSTSIE_Pos              (14U)
#define ETH_MACIER_RXSTSIE_Msk              (0x1U << ETH_MACIER_RXSTSIE_Pos)                    /*!< 0x00004000 */
#define ETH_MACIER_RXSTSIE                  ETH_MACIER_RXSTSIE_Msk                              /*!< Receive Status Interrupt Enable */

/*************  Bit definition for ETH_MACRXTXSR register  *************/
#define ETH_MACRXTXSR_TJT_Pos               (0U)
#define ETH_MACRXTXSR_TJT_Msk               (0x1U << ETH_MACRXTXSR_TJT_Pos)                     /*!< 0x00000001 */
#define ETH_MACRXTXSR_TJT                   ETH_MACRXTXSR_TJT_Msk                               /*!< Transmit Jabber Timeout */
#define ETH_MACRXTXSR_NCARR_Pos             (1U)
#define ETH_MACRXTXSR_NCARR_Msk             (0x1U << ETH_MACRXTXSR_NCARR_Pos)                   /*!< 0x00000002 */
#define ETH_MACRXTXSR_NCARR                 ETH_MACRXTXSR_NCARR_Msk                             /*!< No Carrier */
#define ETH_MACRXTXSR_LCARR_Pos             (2U)
#define ETH_MACRXTXSR_LCARR_Msk             (0x1U << ETH_MACRXTXSR_LCARR_Pos)                   /*!< 0x00000004 */
#define ETH_MACRXTXSR_LCARR                 ETH_MACRXTXSR_LCARR_Msk                             /*!< Loss of Carrier */
#define ETH_MACRXTXSR_EXDEF_Pos             (3U)
#define ETH_MACRXTXSR_EXDEF_Msk             (0x1U << ETH_MACRXTXSR_EXDEF_Pos)                   /*!< 0x00000008 */
#define ETH_MACRXTXSR_EXDEF                 ETH_MACRXTXSR_EXDEF_Msk                             /*!< Excessive Deferral */
#define ETH_MACRXTXSR_LCOL_Pos              (4U)
#define ETH_MACRXTXSR_LCOL_Msk              (0x1U << ETH_MACRXTXSR_LCOL_Pos)                    /*!< 0x00000010 */
#define ETH_MACRXTXSR_LCOL                  ETH_MACRXTXSR_LCOL_Msk                              /*!< Late Collision */
#define ETH_MACRXTXSR_EXCOL_Pos             (5U)
#define ETH_MACRXTXSR_EXCOL_Msk             (0x1U << ETH_MACRXTXSR_EXCOL_Pos)                   /*!< 0x00000020 */
#define ETH_MACRXTXSR_EXCOL                 ETH_MACRXTXSR_EXCOL_Msk                             /*!< Excessive Collisions */
#define ETH_MACRXTXSR_RWT_Pos               (8U)
#define ETH_MACRXTXSR_RWT_Msk               (0x1U << ETH_MACRXTXSR_RWT_Pos)                     /*!< 0x00000100 */
#define ETH_MACRXTXSR_RWT                   ETH_MACRXTXSR_RWT_Msk                               /*!< Receive Watchdog Timeout */

/**************  Bit definition for ETH_MACPCSR register  **************/
#define ETH_MACPCSR_PWRDWN_Pos              (0U)
#define ETH_MACPCSR_PWRDWN_Msk              (0x1U << ETH_MACPCSR_PWRDWN_Pos)                    /*!< 0x00000001 */
#define ETH_MACPCSR_PWRDWN                  ETH_MACPCSR_PWRDWN_Msk                              /*!< Power Down */
#define ETH_MACPCSR_MGKPKTEN_Pos            (1U)
#define ETH_MACPCSR_MGKPKTEN_Msk            (0x1U << ETH_MACPCSR_MGKPKTEN_Pos)                  /*!< 0x00000002 */
#define ETH_MACPCSR_MGKPKTEN                ETH_MACPCSR_MGKPKTEN_Msk                            /*!< Magic Packet Enable */
#define ETH_MACPCSR_RWKPKTEN_Pos            (2U)
#define ETH_MACPCSR_RWKPKTEN_Msk            (0x1U << ETH_MACPCSR_RWKPKTEN_Pos)                  /*!< 0x00000004 */
#define ETH_MACPCSR_RWKPKTEN                ETH_MACPCSR_RWKPKTEN_Msk                            /*!< Remote wakeup Packet Enable */
#define ETH_MACPCSR_MGKPRCVD_Pos            (5U)
#define ETH_MACPCSR_MGKPRCVD_Msk            (0x1U << ETH_MACPCSR_MGKPRCVD_Pos)                  /*!< 0x00000020 */
#define ETH_MACPCSR_MGKPRCVD                ETH_MACPCSR_MGKPRCVD_Msk                            /*!< Magic Packet Received */
#define ETH_MACPCSR_RWKPRCVD_Pos            (6U)
#define ETH_MACPCSR_RWKPRCVD_Msk            (0x1U << ETH_MACPCSR_RWKPRCVD_Pos)                  /*!< 0x00000040 */
#define ETH_MACPCSR_RWKPRCVD                ETH_MACPCSR_RWKPRCVD_Msk                            /*!< Remote wakeup Packet Received */
#define ETH_MACPCSR_GLBLUCAST_Pos           (9U)
#define ETH_MACPCSR_GLBLUCAST_Msk           (0x1U << ETH_MACPCSR_GLBLUCAST_Pos)                 /*!< 0x00000200 */
#define ETH_MACPCSR_GLBLUCAST               ETH_MACPCSR_GLBLUCAST_Msk                           /*!< Global Unicast */
#define ETH_MACPCSR_RWKPFE_Pos              (10U)
#define ETH_MACPCSR_RWKPFE_Msk              (0x1U << ETH_MACPCSR_RWKPFE_Pos)                    /*!< 0x00000400 */
#define ETH_MACPCSR_RWKPFE                  ETH_MACPCSR_RWKPFE_Msk                              /*!< Remote wakeup Packet Forwarding Enable */
#define ETH_MACPCSR_RWKPTR_Pos              (24U)
#define ETH_MACPCSR_RWKPTR_Msk              (0x1FU << ETH_MACPCSR_RWKPTR_Pos)                   /*!< 0x1F000000 */
#define ETH_MACPCSR_RWKPTR                  ETH_MACPCSR_RWKPTR_Msk                              /*!< Remote wakeup FIFO Pointer */
#define ETH_MACPCSR_RWKPTR_0                (0x1U << ETH_MACPCSR_RWKPTR_Pos)              /*!< 0x01000000 */
#define ETH_MACPCSR_RWKPTR_1                (0x2U << ETH_MACPCSR_RWKPTR_Pos)              /*!< 0x02000000 */
#define ETH_MACPCSR_RWKPTR_2                (0x4U << ETH_MACPCSR_RWKPTR_Pos)              /*!< 0x04000000 */
#define ETH_MACPCSR_RWKPTR_3                (0x8U << ETH_MACPCSR_RWKPTR_Pos)              /*!< 0x08000000 */
#define ETH_MACPCSR_RWKPTR_4                (0x10U << ETH_MACPCSR_RWKPTR_Pos)             /*!< 0x10000000 */
#define ETH_MACPCSR_RWKFILTRST_Pos          (31U)
#define ETH_MACPCSR_RWKFILTRST_Msk          (0x1U << ETH_MACPCSR_RWKFILTRST_Pos)                /*!< 0x80000000 */
#define ETH_MACPCSR_RWKFILTRST              ETH_MACPCSR_RWKFILTRST_Msk                          /*!< Remote wakeup Packet Filter Register Pointer Reset */

/*************  Bit definition for ETH_MACRWKPFR register  *************/
#define ETH_MACRWKPFR_MACRWKPFR_Pos         (0U)
#define ETH_MACRWKPFR_MACRWKPFR_Msk         (0xFFFFFFFFU << ETH_MACRWKPFR_MACRWKPFR_Pos)        /*!< 0xFFFFFFFF */
#define ETH_MACRWKPFR_MACRWKPFR             ETH_MACRWKPFR_MACRWKPFR_Msk                         /*!< Remote wakeup packet filter */
#define ETH_MACRWKPFR_MACRWKPFR_0           (0x1U << ETH_MACRWKPFR_MACRWKPFR_Pos)               /*!< 0x00000001 */
#define ETH_MACRWKPFR_MACRWKPFR_1           (0x2U << ETH_MACRWKPFR_MACRWKPFR_Pos)               /*!< 0x00000002 */
#define ETH_MACRWKPFR_MACRWKPFR_2           (0x4U << ETH_MACRWKPFR_MACRWKPFR_Pos)               /*!< 0x00000004 */
#define ETH_MACRWKPFR_MACRWKPFR_3           (0x8U << ETH_MACRWKPFR_MACRWKPFR_Pos)               /*!< 0x00000008 */
#define ETH_MACRWKPFR_MACRWKPFR_4           (0x10U << ETH_MACRWKPFR_MACRWKPFR_Pos)              /*!< 0x00000010 */
#define ETH_MACRWKPFR_MACRWKPFR_5           (0x20U << ETH_MACRWKPFR_MACRWKPFR_Pos)              /*!< 0x00000020 */
#define ETH_MACRWKPFR_MACRWKPFR_6           (0x40U << ETH_MACRWKPFR_MACRWKPFR_Pos)              /*!< 0x00000040 */
#define ETH_MACRWKPFR_MACRWKPFR_7           (0x80U << ETH_MACRWKPFR_MACRWKPFR_Pos)              /*!< 0x00000080 */
#define ETH_MACRWKPFR_MACRWKPFR_8           (0x100U << ETH_MACRWKPFR_MACRWKPFR_Pos)             /*!< 0x00000100 */
#define ETH_MACRWKPFR_MACRWKPFR_9           (0x200U << ETH_MACRWKPFR_MACRWKPFR_Pos)             /*!< 0x00000200 */
#define ETH_MACRWKPFR_MACRWKPFR_10          (0x400U << ETH_MACRWKPFR_MACRWKPFR_Pos)             /*!< 0x00000400 */
#define ETH_MACRWKPFR_MACRWKPFR_11          (0x800U << ETH_MACRWKPFR_MACRWKPFR_Pos)             /*!< 0x00000800 */
#define ETH_MACRWKPFR_MACRWKPFR_12          (0x1000U << ETH_MACRWKPFR_MACRWKPFR_Pos)            /*!< 0x00001000 */
#define ETH_MACRWKPFR_MACRWKPFR_13          (0x2000U << ETH_MACRWKPFR_MACRWKPFR_Pos)            /*!< 0x00002000 */
#define ETH_MACRWKPFR_MACRWKPFR_14          (0x4000U << ETH_MACRWKPFR_MACRWKPFR_Pos)            /*!< 0x00004000 */
#define ETH_MACRWKPFR_MACRWKPFR_15          (0x8000U << ETH_MACRWKPFR_MACRWKPFR_Pos)            /*!< 0x00008000 */
#define ETH_MACRWKPFR_MACRWKPFR_16          (0x10000U << ETH_MACRWKPFR_MACRWKPFR_Pos)           /*!< 0x00010000 */
#define ETH_MACRWKPFR_MACRWKPFR_17          (0x20000U << ETH_MACRWKPFR_MACRWKPFR_Pos)           /*!< 0x00020000 */
#define ETH_MACRWKPFR_MACRWKPFR_18          (0x40000U << ETH_MACRWKPFR_MACRWKPFR_Pos)           /*!< 0x00040000 */
#define ETH_MACRWKPFR_MACRWKPFR_19          (0x80000U << ETH_MACRWKPFR_MACRWKPFR_Pos)           /*!< 0x00080000 */
#define ETH_MACRWKPFR_MACRWKPFR_20          (0x100000U << ETH_MACRWKPFR_MACRWKPFR_Pos)          /*!< 0x00100000 */
#define ETH_MACRWKPFR_MACRWKPFR_21          (0x200000U << ETH_MACRWKPFR_MACRWKPFR_Pos)          /*!< 0x00200000 */
#define ETH_MACRWKPFR_MACRWKPFR_22          (0x400000U << ETH_MACRWKPFR_MACRWKPFR_Pos)          /*!< 0x00400000 */
#define ETH_MACRWKPFR_MACRWKPFR_23          (0x800000U << ETH_MACRWKPFR_MACRWKPFR_Pos)          /*!< 0x00800000 */
#define ETH_MACRWKPFR_MACRWKPFR_24          (0x1000000U << ETH_MACRWKPFR_MACRWKPFR_Pos)         /*!< 0x01000000 */
#define ETH_MACRWKPFR_MACRWKPFR_25          (0x2000000U << ETH_MACRWKPFR_MACRWKPFR_Pos)         /*!< 0x02000000 */
#define ETH_MACRWKPFR_MACRWKPFR_26          (0x4000000U << ETH_MACRWKPFR_MACRWKPFR_Pos)         /*!< 0x04000000 */
#define ETH_MACRWKPFR_MACRWKPFR_27          (0x8000000U << ETH_MACRWKPFR_MACRWKPFR_Pos)         /*!< 0x08000000 */
#define ETH_MACRWKPFR_MACRWKPFR_28          (0x10000000U << ETH_MACRWKPFR_MACRWKPFR_Pos)        /*!< 0x10000000 */
#define ETH_MACRWKPFR_MACRWKPFR_29          (0x20000000U << ETH_MACRWKPFR_MACRWKPFR_Pos)        /*!< 0x20000000 */
#define ETH_MACRWKPFR_MACRWKPFR_30          (0x40000000U << ETH_MACRWKPFR_MACRWKPFR_Pos)        /*!< 0x40000000 */
#define ETH_MACRWKPFR_MACRWKPFR_31          (0x80000000U << ETH_MACRWKPFR_MACRWKPFR_Pos)        /*!< 0x80000000 */

/**************  Bit definition for ETH_MACLCSR register  **************/
#define ETH_MACLCSR_TLPIEN_Pos              (0U)
#define ETH_MACLCSR_TLPIEN_Msk              (0x1U << ETH_MACLCSR_TLPIEN_Pos)                    /*!< 0x00000001 */
#define ETH_MACLCSR_TLPIEN                  ETH_MACLCSR_TLPIEN_Msk                              /*!< Transmit LPI Entry */
#define ETH_MACLCSR_TLPIEX_Pos              (1U)
#define ETH_MACLCSR_TLPIEX_Msk              (0x1U << ETH_MACLCSR_TLPIEX_Pos)                    /*!< 0x00000002 */
#define ETH_MACLCSR_TLPIEX                  ETH_MACLCSR_TLPIEX_Msk                              /*!< Transmit LPI Exit */
#define ETH_MACLCSR_RLPIEN_Pos              (2U)
#define ETH_MACLCSR_RLPIEN_Msk              (0x1U << ETH_MACLCSR_RLPIEN_Pos)                    /*!< 0x00000004 */
#define ETH_MACLCSR_RLPIEN                  ETH_MACLCSR_RLPIEN_Msk                              /*!< Receive LPI Entry */
#define ETH_MACLCSR_RLPIEX_Pos              (3U)
#define ETH_MACLCSR_RLPIEX_Msk              (0x1U << ETH_MACLCSR_RLPIEX_Pos)                    /*!< 0x00000008 */
#define ETH_MACLCSR_RLPIEX                  ETH_MACLCSR_RLPIEX_Msk                              /*!< Receive LPI Exit */
#define ETH_MACLCSR_TLPIST_Pos              (8U)
#define ETH_MACLCSR_TLPIST_Msk              (0x1U << ETH_MACLCSR_TLPIST_Pos)                    /*!< 0x00000100 */
#define ETH_MACLCSR_TLPIST                  ETH_MACLCSR_TLPIST_Msk                              /*!< Transmit LPI State */
#define ETH_MACLCSR_RLPIST_Pos              (9U)
#define ETH_MACLCSR_RLPIST_Msk              (0x1U << ETH_MACLCSR_RLPIST_Pos)                    /*!< 0x00000200 */
#define ETH_MACLCSR_RLPIST                  ETH_MACLCSR_RLPIST_Msk                              /*!< Receive LPI State */
#define ETH_MACLCSR_LPIEN_Pos               (16U)
#define ETH_MACLCSR_LPIEN_Msk               (0x1U << ETH_MACLCSR_LPIEN_Pos)                     /*!< 0x00010000 */
#define ETH_MACLCSR_LPIEN                   ETH_MACLCSR_LPIEN_Msk                               /*!< LPI Enable */
#define ETH_MACLCSR_PLS_Pos                 (17U)
#define ETH_MACLCSR_PLS_Msk                 (0x1U << ETH_MACLCSR_PLS_Pos)                       /*!< 0x00020000 */
#define ETH_MACLCSR_PLS                     ETH_MACLCSR_PLS_Msk                                 /*!< PHY Link Status */
#define ETH_MACLCSR_PLSEN_Pos               (18U)
#define ETH_MACLCSR_PLSEN_Msk               (0x1U << ETH_MACLCSR_PLSEN_Pos)                     /*!< 0x00040000 */
#define ETH_MACLCSR_PLSEN                   ETH_MACLCSR_PLSEN_Msk                               /*!< PHY Link Status Enable */
#define ETH_MACLCSR_LPITXA_Pos              (19U)
#define ETH_MACLCSR_LPITXA_Msk              (0x1U << ETH_MACLCSR_LPITXA_Pos)                    /*!< 0x00080000 */
#define ETH_MACLCSR_LPITXA                  ETH_MACLCSR_LPITXA_Msk                              /*!< LPI Tx Automate */
#define ETH_MACLCSR_LPITE_Pos               (20U)
#define ETH_MACLCSR_LPITE_Msk               (0x1U << ETH_MACLCSR_LPITE_Pos)                     /*!< 0x00100000 */
#define ETH_MACLCSR_LPITE                   ETH_MACLCSR_LPITE_Msk                               /*!< LPI Timer Enable */

/**************  Bit definition for ETH_MACLTCR register  **************/
#define ETH_MACLTCR_TWT_Pos                 (0U)
#define ETH_MACLTCR_TWT_Msk                 (0xFFFFU << ETH_MACLTCR_TWT_Pos)                    /*!< 0x0000FFFF */
#define ETH_MACLTCR_TWT                     ETH_MACLTCR_TWT_Msk                                 /*!< LPI TW Timer */
#define ETH_MACLTCR_TWT_0                   (0x1U << ETH_MACLTCR_TWT_Pos)                       /*!< 0x00000001 */
#define ETH_MACLTCR_TWT_1                   (0x2U << ETH_MACLTCR_TWT_Pos)                       /*!< 0x00000002 */
#define ETH_MACLTCR_TWT_2                   (0x4U << ETH_MACLTCR_TWT_Pos)                       /*!< 0x00000004 */
#define ETH_MACLTCR_TWT_3                   (0x8U << ETH_MACLTCR_TWT_Pos)                       /*!< 0x00000008 */
#define ETH_MACLTCR_TWT_4                   (0x10U << ETH_MACLTCR_TWT_Pos)                      /*!< 0x00000010 */
#define ETH_MACLTCR_TWT_5                   (0x20U << ETH_MACLTCR_TWT_Pos)                      /*!< 0x00000020 */
#define ETH_MACLTCR_TWT_6                   (0x40U << ETH_MACLTCR_TWT_Pos)                      /*!< 0x00000040 */
#define ETH_MACLTCR_TWT_7                   (0x80U << ETH_MACLTCR_TWT_Pos)                      /*!< 0x00000080 */
#define ETH_MACLTCR_TWT_8                   (0x100U << ETH_MACLTCR_TWT_Pos)                     /*!< 0x00000100 */
#define ETH_MACLTCR_TWT_9                   (0x200U << ETH_MACLTCR_TWT_Pos)                     /*!< 0x00000200 */
#define ETH_MACLTCR_TWT_10                  (0x400U << ETH_MACLTCR_TWT_Pos)                     /*!< 0x00000400 */
#define ETH_MACLTCR_TWT_11                  (0x800U << ETH_MACLTCR_TWT_Pos)                     /*!< 0x00000800 */
#define ETH_MACLTCR_TWT_12                  (0x1000U << ETH_MACLTCR_TWT_Pos)                    /*!< 0x00001000 */
#define ETH_MACLTCR_TWT_13                  (0x2000U << ETH_MACLTCR_TWT_Pos)                    /*!< 0x00002000 */
#define ETH_MACLTCR_TWT_14                  (0x4000U << ETH_MACLTCR_TWT_Pos)                    /*!< 0x00004000 */
#define ETH_MACLTCR_TWT_15                  (0x8000U << ETH_MACLTCR_TWT_Pos)                    /*!< 0x00008000 */
#define ETH_MACLTCR_LST_Pos                 (16U)
#define ETH_MACLTCR_LST_Msk                 (0x3FFU << ETH_MACLTCR_LST_Pos)                     /*!< 0x03FF0000 */
#define ETH_MACLTCR_LST                     ETH_MACLTCR_LST_Msk                                 /*!< LPI LS Timer */
#define ETH_MACLTCR_LST_0                   (0x1U << ETH_MACLTCR_LST_Pos)                   /*!< 0x00010000 */
#define ETH_MACLTCR_LST_1                   (0x2U << ETH_MACLTCR_LST_Pos)                   /*!< 0x00020000 */
#define ETH_MACLTCR_LST_2                   (0x4U << ETH_MACLTCR_LST_Pos)                   /*!< 0x00040000 */
#define ETH_MACLTCR_LST_3                   (0x8U << ETH_MACLTCR_LST_Pos)                   /*!< 0x00080000 */
#define ETH_MACLTCR_LST_4                   (0x10U << ETH_MACLTCR_LST_Pos)                  /*!< 0x00100000 */
#define ETH_MACLTCR_LST_5                   (0x20U << ETH_MACLTCR_LST_Pos)                  /*!< 0x00200000 */
#define ETH_MACLTCR_LST_6                   (0x40U << ETH_MACLTCR_LST_Pos)                  /*!< 0x00400000 */
#define ETH_MACLTCR_LST_7                   (0x80U << ETH_MACLTCR_LST_Pos)                  /*!< 0x00800000 */
#define ETH_MACLTCR_LST_8                   (0x100U << ETH_MACLTCR_LST_Pos)                 /*!< 0x01000000 */
#define ETH_MACLTCR_LST_9                   (0x200U << ETH_MACLTCR_LST_Pos)                 /*!< 0x02000000 */

/**************  Bit definition for ETH_MACLETR register  **************/
#define ETH_MACLETR_LPIET_Pos               (3U)
#define ETH_MACLETR_LPIET_Msk               (0x1FFFFU << ETH_MACLETR_LPIET_Pos)                 /*!< 0x000FFFF8 */
#define ETH_MACLETR_LPIET                   ETH_MACLETR_LPIET_Msk                               /*!< LPI Entry Timer */
#define ETH_MACLETR_LPIET_0                 (0x1U << ETH_MACLETR_LPIET_Pos)                     /*!< 0x00000008 */
#define ETH_MACLETR_LPIET_1                 (0x2U << ETH_MACLETR_LPIET_Pos)                    /*!< 0x00000010 */
#define ETH_MACLETR_LPIET_2                 (0x4U << ETH_MACLETR_LPIET_Pos)                    /*!< 0x00000020 */
#define ETH_MACLETR_LPIET_3                 (0x8U << ETH_MACLETR_LPIET_Pos)                    /*!< 0x00000040 */
#define ETH_MACLETR_LPIET_4                 (0x10U << ETH_MACLETR_LPIET_Pos)                    /*!< 0x00000080 */
#define ETH_MACLETR_LPIET_5                 (0x20U << ETH_MACLETR_LPIET_Pos)                   /*!< 0x00000100 */
#define ETH_MACLETR_LPIET_6                 (0x40U << ETH_MACLETR_LPIET_Pos)                   /*!< 0x00000200 */
#define ETH_MACLETR_LPIET_7                 (0x80U << ETH_MACLETR_LPIET_Pos)                   /*!< 0x00000400 */
#define ETH_MACLETR_LPIET_8                 (0x100U << ETH_MACLETR_LPIET_Pos)                   /*!< 0x00000800 */
#define ETH_MACLETR_LPIET_9                 (0x200U << ETH_MACLETR_LPIET_Pos)                  /*!< 0x00001000 */
#define ETH_MACLETR_LPIET_10                (0x400U << ETH_MACLETR_LPIET_Pos)                  /*!< 0x00002000 */
#define ETH_MACLETR_LPIET_11                (0x800U << ETH_MACLETR_LPIET_Pos)                  /*!< 0x00004000 */
#define ETH_MACLETR_LPIET_12                (0x1000U << ETH_MACLETR_LPIET_Pos)                  /*!< 0x00008000 */
#define ETH_MACLETR_LPIET_13                (0x2000U << ETH_MACLETR_LPIET_Pos)                 /*!< 0x00010000 */
#define ETH_MACLETR_LPIET_14                (0x4000U << ETH_MACLETR_LPIET_Pos)                 /*!< 0x00020000 */
#define ETH_MACLETR_LPIET_15                (0x8000U << ETH_MACLETR_LPIET_Pos)                 /*!< 0x00040000 */
#define ETH_MACLETR_LPIET_16                (0x10000U << ETH_MACLETR_LPIET_Pos)                 /*!< 0x00080000 */

/*************  Bit definition for ETH_MAC1USTCR register  *************/
#define ETH_MAC1USTCR_TIC_1US_CNTR_Pos      (0U)
#define ETH_MAC1USTCR_TIC_1US_CNTR_Msk      (0xFFFU << ETH_MAC1USTCR_TIC_1US_CNTR_Pos)          /*!< 0x00000FFF */
#define ETH_MAC1USTCR_TIC_1US_CNTR          ETH_MAC1USTCR_TIC_1US_CNTR_Msk                      /*!< 1 ÃÂµs tick Counter */
#define ETH_MAC1USTCR_TIC_1US_CNTR_0        (0x1U << ETH_MAC1USTCR_TIC_1US_CNTR_Pos)            /*!< 0x00000001 */
#define ETH_MAC1USTCR_TIC_1US_CNTR_1        (0x2U << ETH_MAC1USTCR_TIC_1US_CNTR_Pos)            /*!< 0x00000002 */
#define ETH_MAC1USTCR_TIC_1US_CNTR_2        (0x4U << ETH_MAC1USTCR_TIC_1US_CNTR_Pos)            /*!< 0x00000004 */
#define ETH_MAC1USTCR_TIC_1US_CNTR_3        (0x8U << ETH_MAC1USTCR_TIC_1US_CNTR_Pos)            /*!< 0x00000008 */
#define ETH_MAC1USTCR_TIC_1US_CNTR_4        (0x10U << ETH_MAC1USTCR_TIC_1US_CNTR_Pos)           /*!< 0x00000010 */
#define ETH_MAC1USTCR_TIC_1US_CNTR_5        (0x20U << ETH_MAC1USTCR_TIC_1US_CNTR_Pos)           /*!< 0x00000020 */
#define ETH_MAC1USTCR_TIC_1US_CNTR_6        (0x40U << ETH_MAC1USTCR_TIC_1US_CNTR_Pos)           /*!< 0x00000040 */
#define ETH_MAC1USTCR_TIC_1US_CNTR_7        (0x80U << ETH_MAC1USTCR_TIC_1US_CNTR_Pos)           /*!< 0x00000080 */
#define ETH_MAC1USTCR_TIC_1US_CNTR_8        (0x100U << ETH_MAC1USTCR_TIC_1US_CNTR_Pos)          /*!< 0x00000100 */
#define ETH_MAC1USTCR_TIC_1US_CNTR_9        (0x200U << ETH_MAC1USTCR_TIC_1US_CNTR_Pos)          /*!< 0x00000200 */
#define ETH_MAC1USTCR_TIC_1US_CNTR_10       (0x400U << ETH_MAC1USTCR_TIC_1US_CNTR_Pos)          /*!< 0x00000400 */
#define ETH_MAC1USTCR_TIC_1US_CNTR_11       (0x800U << ETH_MAC1USTCR_TIC_1US_CNTR_Pos)          /*!< 0x00000800 */

/*************  Bit definition for ETH_MACPHYCSR register  *************/
#define ETH_MACPHYCSR_TC_Pos                (0U)
#define ETH_MACPHYCSR_TC_Msk                (0x1U << ETH_MACPHYCSR_TC_Pos)                      /*!< 0x00000001 */
#define ETH_MACPHYCSR_TC                    ETH_MACPHYCSR_TC_Msk                                /*!< Transmit Configuration in RGMII, SGMII, or SMII */
#define ETH_MACPHYCSR_LUD_Pos               (1U)
#define ETH_MACPHYCSR_LUD_Msk               (0x1U << ETH_MACPHYCSR_LUD_Pos)                     /*!< 0x00000002 */
#define ETH_MACPHYCSR_LUD                   ETH_MACPHYCSR_LUD_Msk                               /*!< Link Up or Down */
#define ETH_MACPHYCSR_LNKMOD_Pos            (16U)
#define ETH_MACPHYCSR_LNKMOD_Msk            (0x1U << ETH_MACPHYCSR_LNKMOD_Pos)                  /*!< 0x00010000 */
#define ETH_MACPHYCSR_LNKMOD                ETH_MACPHYCSR_LNKMOD_Msk                            /*!< Link Mode */
#define ETH_MACPHYCSR_LNKSPEED_Pos          (17U)
#define ETH_MACPHYCSR_LNKSPEED_Msk          (0x3U << ETH_MACPHYCSR_LNKSPEED_Pos)                /*!< 0x00060000 */
#define ETH_MACPHYCSR_LNKSPEED              ETH_MACPHYCSR_LNKSPEED_Msk                          /*!< Link Speed */
#define ETH_MACPHYCSR_LNKSPEED_0            (0x1U << ETH_MACPHYCSR_LNKSPEED_Pos)            /*!< 0x00020000 */
#define ETH_MACPHYCSR_LNKSPEED_1            (0x2U << ETH_MACPHYCSR_LNKSPEED_Pos)            /*!< 0x00040000 */
#define ETH_MACPHYCSR_LNKSTS_Pos            (19U)
#define ETH_MACPHYCSR_LNKSTS_Msk            (0x1U << ETH_MACPHYCSR_LNKSTS_Pos)                  /*!< 0x00080000 */
#define ETH_MACPHYCSR_LNKSTS                ETH_MACPHYCSR_LNKSTS_Msk                            /*!< Link Status */
#define ETH_MACPHYCSR_JABTO_Pos             (20U)
#define ETH_MACPHYCSR_JABTO_Msk             (0x1U << ETH_MACPHYCSR_JABTO_Pos)                   /*!< 0x00100000 */
#define ETH_MACPHYCSR_JABTO                 ETH_MACPHYCSR_JABTO_Msk                             /*!< Jabber Timeout */
#define ETH_MACPHYCSR_FALSCARDET_Pos        (21U)
#define ETH_MACPHYCSR_FALSCARDET_Msk        (0x1U << ETH_MACPHYCSR_FALSCARDET_Pos)              /*!< 0x00200000 */
#define ETH_MACPHYCSR_FALSCARDET            ETH_MACPHYCSR_FALSCARDET_Msk                        /*!< False Carrier Detected */

/***************  Bit definition for ETH_MACVR register  ***************/
#define ETH_MACVR_SNPSVER_Pos               (0U)
#define ETH_MACVR_SNPSVER_Msk               (0xFFU << ETH_MACVR_SNPSVER_Pos)                    /*!< 0x000000FF */
#define ETH_MACVR_SNPSVER                   ETH_MACVR_SNPSVER_Msk                               /*!< IP version */
#define ETH_MACVR_SNPSVER_0                 (0x1U << ETH_MACVR_SNPSVER_Pos)                     /*!< 0x00000001 */
#define ETH_MACVR_SNPSVER_1                 (0x2U << ETH_MACVR_SNPSVER_Pos)                     /*!< 0x00000002 */
#define ETH_MACVR_SNPSVER_2                 (0x4U << ETH_MACVR_SNPSVER_Pos)                     /*!< 0x00000004 */
#define ETH_MACVR_SNPSVER_3                 (0x8U << ETH_MACVR_SNPSVER_Pos)                     /*!< 0x00000008 */
#define ETH_MACVR_SNPSVER_4                 (0x10U << ETH_MACVR_SNPSVER_Pos)                    /*!< 0x00000010 */
#define ETH_MACVR_SNPSVER_5                 (0x20U << ETH_MACVR_SNPSVER_Pos)                    /*!< 0x00000020 */
#define ETH_MACVR_SNPSVER_6                 (0x40U << ETH_MACVR_SNPSVER_Pos)                    /*!< 0x00000040 */
#define ETH_MACVR_SNPSVER_7                 (0x80U << ETH_MACVR_SNPSVER_Pos)                    /*!< 0x00000080 */
#define ETH_MACVR_USERVER_Pos               (8U)
#define ETH_MACVR_USERVER_Msk               (0xFFU << ETH_MACVR_USERVER_Pos)                    /*!< 0x0000FF00 */
#define ETH_MACVR_USERVER                   ETH_MACVR_USERVER_Msk                               /*!< ST-defined version */
#define ETH_MACVR_USERVER_0                 (0x1U << ETH_MACVR_USERVER_Pos)                   /*!< 0x00000100 */
#define ETH_MACVR_USERVER_1                 (0x2U << ETH_MACVR_USERVER_Pos)                   /*!< 0x00000200 */
#define ETH_MACVR_USERVER_2                 (0x4U << ETH_MACVR_USERVER_Pos)                   /*!< 0x00000400 */
#define ETH_MACVR_USERVER_3                 (0x8U << ETH_MACVR_USERVER_Pos)                   /*!< 0x00000800 */
#define ETH_MACVR_USERVER_4                 (0x10U << ETH_MACVR_USERVER_Pos)                  /*!< 0x00001000 */
#define ETH_MACVR_USERVER_5                 (0x20U << ETH_MACVR_USERVER_Pos)                  /*!< 0x00002000 */
#define ETH_MACVR_USERVER_6                 (0x40U << ETH_MACVR_USERVER_Pos)                  /*!< 0x00004000 */
#define ETH_MACVR_USERVER_7                 (0x80U << ETH_MACVR_USERVER_Pos)                  /*!< 0x00008000 */

/***************  Bit definition for ETH_MACDR register  ***************/
#define ETH_MACDR_RPESTS_Pos                (0U)
#define ETH_MACDR_RPESTS_Msk                (0x1U << ETH_MACDR_RPESTS_Pos)                      /*!< 0x00000001 */
#define ETH_MACDR_RPESTS                    ETH_MACDR_RPESTS_Msk                                /*!< MAC GMII or MII Receive Protocol Engine Status */
#define ETH_MACDR_RFCFCSTS_Pos              (1U)
#define ETH_MACDR_RFCFCSTS_Msk              (0x3U << ETH_MACDR_RFCFCSTS_Pos)                    /*!< 0x00000006 */
#define ETH_MACDR_RFCFCSTS                  ETH_MACDR_RFCFCSTS_Msk                              /*!< MAC Receive Packet Controller FIFO Status */
#define ETH_MACDR_RFCFCSTS_0                (0x1U << ETH_MACDR_RFCFCSTS_Pos)                    /*!< 0x00000002 */
#define ETH_MACDR_RFCFCSTS_1                (0x2U << ETH_MACDR_RFCFCSTS_Pos)                    /*!< 0x00000004 */
#define ETH_MACDR_TPESTS_Pos                (16U)
#define ETH_MACDR_TPESTS_Msk                (0x1U << ETH_MACDR_TPESTS_Pos)                      /*!< 0x00010000 */
#define ETH_MACDR_TPESTS                    ETH_MACDR_TPESTS_Msk                                /*!< MAC GMII or MII Transmit Protocol Engine Status */
#define ETH_MACDR_TFCSTS_Pos                (17U)
#define ETH_MACDR_TFCSTS_Msk                (0x3U << ETH_MACDR_TFCSTS_Pos)                      /*!< 0x00060000 */
#define ETH_MACDR_TFCSTS                    ETH_MACDR_TFCSTS_Msk                                /*!< MAC Transmit Packet Controller Status */
#define ETH_MACDR_TFCSTS_0                  (0x1U << ETH_MACDR_TFCSTS_Pos)                  /*!< 0x00020000 */
#define ETH_MACDR_TFCSTS_1                  (0x2U << ETH_MACDR_TFCSTS_Pos)                  /*!< 0x00040000 */

/*************  Bit definition for ETH_MACHWF1R register  **************/
#define ETH_MACHWF1R_RXFIFOSIZE_Pos         (0U)
#define ETH_MACHWF1R_RXFIFOSIZE_Msk         (0x1FU << ETH_MACHWF1R_RXFIFOSIZE_Pos)              /*!< 0x0000001F */
#define ETH_MACHWF1R_RXFIFOSIZE             ETH_MACHWF1R_RXFIFOSIZE_Msk                         /*!< MTL Receive FIFO Size */
#define ETH_MACHWF1R_RXFIFOSIZE_0           (0x1U << ETH_MACHWF1R_RXFIFOSIZE_Pos)               /*!< 0x00000001 */
#define ETH_MACHWF1R_RXFIFOSIZE_1           (0x2U << ETH_MACHWF1R_RXFIFOSIZE_Pos)               /*!< 0x00000002 */
#define ETH_MACHWF1R_RXFIFOSIZE_2           (0x4U << ETH_MACHWF1R_RXFIFOSIZE_Pos)               /*!< 0x00000004 */
#define ETH_MACHWF1R_RXFIFOSIZE_3           (0x8U << ETH_MACHWF1R_RXFIFOSIZE_Pos)               /*!< 0x00000008 */
#define ETH_MACHWF1R_RXFIFOSIZE_4           (0x10U << ETH_MACHWF1R_RXFIFOSIZE_Pos)              /*!< 0x00000010 */
#define ETH_MACHWF1R_TXFIFOSIZE_Pos         (6U)
#define ETH_MACHWF1R_TXFIFOSIZE_Msk         (0x1FU << ETH_MACHWF1R_TXFIFOSIZE_Pos)              /*!< 0x000007C0 */
#define ETH_MACHWF1R_TXFIFOSIZE             ETH_MACHWF1R_TXFIFOSIZE_Msk                         /*!< MTL Transmit FIFO Size */
#define ETH_MACHWF1R_TXFIFOSIZE_0           (0x1U << ETH_MACHWF1R_TXFIFOSIZE_Pos)              /*!< 0x00000040 */
#define ETH_MACHWF1R_TXFIFOSIZE_1           (0x2U << ETH_MACHWF1R_TXFIFOSIZE_Pos)              /*!< 0x00000080 */
#define ETH_MACHWF1R_TXFIFOSIZE_2           (0x4U << ETH_MACHWF1R_TXFIFOSIZE_Pos)             /*!< 0x00000100 */
#define ETH_MACHWF1R_TXFIFOSIZE_3           (0x8U << ETH_MACHWF1R_TXFIFOSIZE_Pos)             /*!< 0x00000200 */
#define ETH_MACHWF1R_TXFIFOSIZE_4           (0x10U << ETH_MACHWF1R_TXFIFOSIZE_Pos)             /*!< 0x00000400 */
#define ETH_MACHWF1R_OSTEN_Pos              (11U)
#define ETH_MACHWF1R_OSTEN_Msk              (0x1U << ETH_MACHWF1R_OSTEN_Pos)                    /*!< 0x00000800 */
#define ETH_MACHWF1R_OSTEN                  ETH_MACHWF1R_OSTEN_Msk                              /*!< One-Step Timestamping Enable */
#define ETH_MACHWF1R_PTOEN_Pos              (12U)
#define ETH_MACHWF1R_PTOEN_Msk              (0x1U << ETH_MACHWF1R_PTOEN_Pos)                    /*!< 0x00001000 */
#define ETH_MACHWF1R_PTOEN                  ETH_MACHWF1R_PTOEN_Msk                              /*!< PTP Offload Enable */
#define ETH_MACHWF1R_ADVTHWORD_Pos          (13U)
#define ETH_MACHWF1R_ADVTHWORD_Msk          (0x1U << ETH_MACHWF1R_ADVTHWORD_Pos)                /*!< 0x00002000 */
#define ETH_MACHWF1R_ADVTHWORD              ETH_MACHWF1R_ADVTHWORD_Msk                          /*!< IEEE 1588 High Word Register Enable */
#define ETH_MACHWF1R_ADDR64_Pos             (14U)
#define ETH_MACHWF1R_ADDR64_Msk             (0x3U << ETH_MACHWF1R_ADDR64_Pos)                   /*!< 0x0000C000 */
#define ETH_MACHWF1R_ADDR64                 ETH_MACHWF1R_ADDR64_Msk                             /*!< Address width */
#define ETH_MACHWF1R_ADDR64_0               (0x1U << ETH_MACHWF1R_ADDR64_Pos)                /*!< 0x00004000 */
#define ETH_MACHWF1R_ADDR64_1               (0x2U << ETH_MACHWF1R_ADDR64_Pos)                /*!< 0x00008000 */
#define ETH_MACHWF1R_DCBEN_Pos              (16U)
#define ETH_MACHWF1R_DCBEN_Msk              (0x1U << ETH_MACHWF1R_DCBEN_Pos)                    /*!< 0x00010000 */
#define ETH_MACHWF1R_DCBEN                  ETH_MACHWF1R_DCBEN_Msk                              /*!< DCB Feature Enable */
#define ETH_MACHWF1R_SPHEN_Pos              (17U)
#define ETH_MACHWF1R_SPHEN_Msk              (0x1U << ETH_MACHWF1R_SPHEN_Pos)                    /*!< 0x00020000 */
#define ETH_MACHWF1R_SPHEN                  ETH_MACHWF1R_SPHEN_Msk                              /*!< Split Header Feature Enable */
#define ETH_MACHWF1R_TSOEN_Pos              (18U)
#define ETH_MACHWF1R_TSOEN_Msk              (0x1U << ETH_MACHWF1R_TSOEN_Pos)                    /*!< 0x00040000 */
#define ETH_MACHWF1R_TSOEN                  ETH_MACHWF1R_TSOEN_Msk                              /*!< TCP Segmentation Offload Enable */
#define ETH_MACHWF1R_DBGMEMA_Pos            (19U)
#define ETH_MACHWF1R_DBGMEMA_Msk            (0x1U << ETH_MACHWF1R_DBGMEMA_Pos)                  /*!< 0x00080000 */
#define ETH_MACHWF1R_DBGMEMA                ETH_MACHWF1R_DBGMEMA_Msk                            /*!< DMA Debug Registers Enable */
#define ETH_MACHWF1R_AVSEL_Pos              (20U)
#define ETH_MACHWF1R_AVSEL_Msk              (0x1U << ETH_MACHWF1R_AVSEL_Pos)                    /*!< 0x00100000 */
#define ETH_MACHWF1R_AVSEL                  ETH_MACHWF1R_AVSEL_Msk                              /*!< AV Feature Enable */
#define ETH_MACHWF1R_HASHTBLSZ_Pos          (24U)
#define ETH_MACHWF1R_HASHTBLSZ_Msk          (0x3U << ETH_MACHWF1R_HASHTBLSZ_Pos)                /*!< 0x03000000 */
#define ETH_MACHWF1R_HASHTBLSZ              ETH_MACHWF1R_HASHTBLSZ_Msk                          /*!< Hash Table Size */
#define ETH_MACHWF1R_HASHTBLSZ_0            (0x1U << ETH_MACHWF1R_HASHTBLSZ_Pos)          /*!< 0x01000000 */
#define ETH_MACHWF1R_HASHTBLSZ_1            (0x2U << ETH_MACHWF1R_HASHTBLSZ_Pos)          /*!< 0x02000000 */
#define ETH_MACHWF1R_L3L4FNUM_Pos           (27U)
#define ETH_MACHWF1R_L3L4FNUM_Msk           (0xFU << ETH_MACHWF1R_L3L4FNUM_Pos)                 /*!< 0x78000000 */
#define ETH_MACHWF1R_L3L4FNUM               ETH_MACHWF1R_L3L4FNUM_Msk                           /*!< Total number of L3 or L4 Filters */
#define ETH_MACHWF1R_L3L4FNUM_0             (0x1U << ETH_MACHWF1R_L3L4FNUM_Pos)           /*!< 0x08000000 */
#define ETH_MACHWF1R_L3L4FNUM_1             (0x2U << ETH_MACHWF1R_L3L4FNUM_Pos)          /*!< 0x10000000 */
#define ETH_MACHWF1R_L3L4FNUM_2             (0x4U << ETH_MACHWF1R_L3L4FNUM_Pos)          /*!< 0x20000000 */
#define ETH_MACHWF1R_L3L4FNUM_3             (0x8U << ETH_MACHWF1R_L3L4FNUM_Pos)          /*!< 0x40000000 */

/*************  Bit definition for ETH_MACHWF2R register  **************/
#define ETH_MACHWF2R_RXQCNT_Pos             (0U)
#define ETH_MACHWF2R_RXQCNT_Msk             (0xFU << ETH_MACHWF2R_RXQCNT_Pos)                   /*!< 0x0000000F */
#define ETH_MACHWF2R_RXQCNT                 ETH_MACHWF2R_RXQCNT_Msk                             /*!< Number of MTL Receive Queues */
#define ETH_MACHWF2R_RXQCNT_0               (0x1U << ETH_MACHWF2R_RXQCNT_Pos)                   /*!< 0x00000001 */
#define ETH_MACHWF2R_RXQCNT_1               (0x2U << ETH_MACHWF2R_RXQCNT_Pos)                   /*!< 0x00000002 */
#define ETH_MACHWF2R_RXQCNT_2               (0x4U << ETH_MACHWF2R_RXQCNT_Pos)                   /*!< 0x00000004 */
#define ETH_MACHWF2R_RXQCNT_3               (0x8U << ETH_MACHWF2R_RXQCNT_Pos)                   /*!< 0x00000008 */
#define ETH_MACHWF2R_TXQCNT_Pos             (6U)
#define ETH_MACHWF2R_TXQCNT_Msk             (0xFU << ETH_MACHWF2R_TXQCNT_Pos)                   /*!< 0x000003C0 */
#define ETH_MACHWF2R_TXQCNT                 ETH_MACHWF2R_TXQCNT_Msk                             /*!< Number of MTL Transmit Queues */
#define ETH_MACHWF2R_TXQCNT_0               (0x1U << ETH_MACHWF2R_TXQCNT_Pos)                  /*!< 0x00000040 */
#define ETH_MACHWF2R_TXQCNT_1               (0x2U << ETH_MACHWF2R_TXQCNT_Pos)                  /*!< 0x00000080 */
#define ETH_MACHWF2R_TXQCNT_2               (0x4U << ETH_MACHWF2R_TXQCNT_Pos)                 /*!< 0x00000100 */
#define ETH_MACHWF2R_TXQCNT_3               (0x8U << ETH_MACHWF2R_TXQCNT_Pos)                 /*!< 0x00000200 */
#define ETH_MACHWF2R_RXCHCNT_Pos            (12U)
#define ETH_MACHWF2R_RXCHCNT_Msk            (0xFU << ETH_MACHWF2R_RXCHCNT_Pos)                  /*!< 0x0000F000 */
#define ETH_MACHWF2R_RXCHCNT                ETH_MACHWF2R_RXCHCNT_Msk                            /*!< Number of DMA Receive Channels */
#define ETH_MACHWF2R_RXCHCNT_0              (0x1U << ETH_MACHWF2R_RXCHCNT_Pos)               /*!< 0x00001000 */
#define ETH_MACHWF2R_RXCHCNT_1              (0x2U << ETH_MACHWF2R_RXCHCNT_Pos)               /*!< 0x00002000 */
#define ETH_MACHWF2R_RXCHCNT_2              (0x4U << ETH_MACHWF2R_RXCHCNT_Pos)               /*!< 0x00004000 */
#define ETH_MACHWF2R_RXCHCNT_3              (0x8U << ETH_MACHWF2R_RXCHCNT_Pos)               /*!< 0x00008000 */
#define ETH_MACHWF2R_TXCHCNT_Pos            (18U)
#define ETH_MACHWF2R_TXCHCNT_Msk            (0xFU << ETH_MACHWF2R_TXCHCNT_Pos)                  /*!< 0x003C0000 */
#define ETH_MACHWF2R_TXCHCNT                ETH_MACHWF2R_TXCHCNT_Msk                            /*!< Number of DMA Transmit Channels */
#define ETH_MACHWF2R_TXCHCNT_0              (0x1U << ETH_MACHWF2R_TXCHCNT_Pos)              /*!< 0x00040000 */
#define ETH_MACHWF2R_TXCHCNT_1              (0x2U << ETH_MACHWF2R_TXCHCNT_Pos)              /*!< 0x00080000 */
#define ETH_MACHWF2R_TXCHCNT_2              (0x4U << ETH_MACHWF2R_TXCHCNT_Pos)             /*!< 0x00100000 */
#define ETH_MACHWF2R_TXCHCNT_3              (0x8U << ETH_MACHWF2R_TXCHCNT_Pos)             /*!< 0x00200000 */
#define ETH_MACHWF2R_PPSOUTNUM_Pos          (24U)
#define ETH_MACHWF2R_PPSOUTNUM_Msk          (0x7U << ETH_MACHWF2R_PPSOUTNUM_Pos)                /*!< 0x07000000 */
#define ETH_MACHWF2R_PPSOUTNUM              ETH_MACHWF2R_PPSOUTNUM_Msk                          /*!< Number of PPS Outputs */
#define ETH_MACHWF2R_PPSOUTNUM_0            (0x1U << ETH_MACHWF2R_PPSOUTNUM_Pos)          /*!< 0x01000000 */
#define ETH_MACHWF2R_PPSOUTNUM_1            (0x2U << ETH_MACHWF2R_PPSOUTNUM_Pos)          /*!< 0x02000000 */
#define ETH_MACHWF2R_PPSOUTNUM_2            (0x4U << ETH_MACHWF2R_PPSOUTNUM_Pos)          /*!< 0x04000000 */
#define ETH_MACHWF2R_AUXSNAPNUM_Pos         (28U)
#define ETH_MACHWF2R_AUXSNAPNUM_Msk         (0x7U << ETH_MACHWF2R_AUXSNAPNUM_Pos)               /*!< 0x70000000 */
#define ETH_MACHWF2R_AUXSNAPNUM             ETH_MACHWF2R_AUXSNAPNUM_Msk                         /*!< Number of Auxiliary Snapshot Inputs */
#define ETH_MACHWF2R_AUXSNAPNUM_0           (0x1U << ETH_MACHWF2R_AUXSNAPNUM_Pos)        /*!< 0x10000000 */
#define ETH_MACHWF2R_AUXSNAPNUM_1           (0x2U << ETH_MACHWF2R_AUXSNAPNUM_Pos)        /*!< 0x20000000 */
#define ETH_MACHWF2R_AUXSNAPNUM_2           (0x4U << ETH_MACHWF2R_AUXSNAPNUM_Pos)        /*!< 0x40000000 */

/*************  Bit definition for ETH_MACMDIOAR register  *************/
#define ETH_MACMDIOAR_GB_Pos                (0U)
#define ETH_MACMDIOAR_GB_Msk                (0x1U << ETH_MACMDIOAR_GB_Pos)                      /*!< 0x00000001 */
#define ETH_MACMDIOAR_GB                    ETH_MACMDIOAR_GB_Msk                                /*!< GMII Busy */
#define ETH_MACMDIOAR_C45E_Pos              (1U)
#define ETH_MACMDIOAR_C45E_Msk              (0x1U << ETH_MACMDIOAR_C45E_Pos)                    /*!< 0x00000002 */
#define ETH_MACMDIOAR_C45E                  ETH_MACMDIOAR_C45E_Msk                              /*!< Clause 45 PHY Enable */
#define ETH_MACMDIOAR_GOC_Pos               (2U)
#define ETH_MACMDIOAR_GOC_Msk               (0x3U << ETH_MACMDIOAR_GOC_Pos)                     /*!< 0x0000000C */
#define ETH_MACMDIOAR_GOC                   ETH_MACMDIOAR_GOC_Msk                               /*!< GMII Operation Command */
#define ETH_MACMDIOAR_GOC_0                 (0x1U << ETH_MACMDIOAR_GOC_Pos)                     /*!< 0x00000004 */
#define ETH_MACMDIOAR_GOC_1                 (0x2U << ETH_MACMDIOAR_GOC_Pos)                     /*!< 0x00000008 */
#define ETH_MACMDIOAR_SKAP_Pos              (4U)
#define ETH_MACMDIOAR_SKAP_Msk              (0x1U << ETH_MACMDIOAR_SKAP_Pos)                    /*!< 0x00000010 */
#define ETH_MACMDIOAR_SKAP                  ETH_MACMDIOAR_SKAP_Msk                              /*!< Skip Address Packet */
#define ETH_MACMDIOAR_CR_Pos                (8U)
#define ETH_MACMDIOAR_CR_Msk                (0xFU << ETH_MACMDIOAR_CR_Pos)                      /*!< 0x00000F00 */
#define ETH_MACMDIOAR_CR                    ETH_MACMDIOAR_CR_Msk                                /*!< CSR Clock Range */
#define ETH_MACMDIOAR_CR_0                  (0x1U << ETH_MACMDIOAR_CR_Pos)                    /*!< 0x00000100 */
#define ETH_MACMDIOAR_CR_1                  (0x2U << ETH_MACMDIOAR_CR_Pos)                    /*!< 0x00000200 */
#define ETH_MACMDIOAR_CR_2                  (0x4U << ETH_MACMDIOAR_CR_Pos)                    /*!< 0x00000400 */
#define ETH_MACMDIOAR_CR_3                  (0x8U << ETH_MACMDIOAR_CR_Pos)                    /*!< 0x00000800 */
#define ETH_MACMDIOAR_NTC_Pos               (12U)
#define ETH_MACMDIOAR_NTC_Msk               (0x7U << ETH_MACMDIOAR_NTC_Pos)                     /*!< 0x00007000 */
#define ETH_MACMDIOAR_NTC                   ETH_MACMDIOAR_NTC_Msk                               /*!< Number of Training Clocks */
#define ETH_MACMDIOAR_NTC_0                 (0x1U << ETH_MACMDIOAR_NTC_Pos)                  /*!< 0x00001000 */
#define ETH_MACMDIOAR_NTC_1                 (0x2U << ETH_MACMDIOAR_NTC_Pos)                  /*!< 0x00002000 */
#define ETH_MACMDIOAR_NTC_2                 (0x4U << ETH_MACMDIOAR_NTC_Pos)                  /*!< 0x00004000 */
#define ETH_MACMDIOAR_RDA_Pos               (16U)
#define ETH_MACMDIOAR_RDA_Msk               (0x1FU << ETH_MACMDIOAR_RDA_Pos)                    /*!< 0x001F0000 */
#define ETH_MACMDIOAR_RDA                   ETH_MACMDIOAR_RDA_Msk                               /*!< Register/Device Address */
#define ETH_MACMDIOAR_RDA_0                 (0x1U << ETH_MACMDIOAR_RDA_Pos)                 /*!< 0x00010000 */
#define ETH_MACMDIOAR_RDA_1                 (0x2U << ETH_MACMDIOAR_RDA_Pos)                 /*!< 0x00020000 */
#define ETH_MACMDIOAR_RDA_2                 (0x4U << ETH_MACMDIOAR_RDA_Pos)                 /*!< 0x00040000 */
#define ETH_MACMDIOAR_RDA_3                 (0x8U << ETH_MACMDIOAR_RDA_Pos)                 /*!< 0x00080000 */
#define ETH_MACMDIOAR_RDA_4                 (0x10U << ETH_MACMDIOAR_RDA_Pos)                /*!< 0x00100000 */
#define ETH_MACMDIOAR_PA_Pos                (21U)
#define ETH_MACMDIOAR_PA_Msk                (0x1FU << ETH_MACMDIOAR_PA_Pos)                     /*!< 0x03E00000 */
#define ETH_MACMDIOAR_PA                    ETH_MACMDIOAR_PA_Msk                                /*!< Physical Layer Address */
#define ETH_MACMDIOAR_PA_0                  (0x1U << ETH_MACMDIOAR_PA_Pos)                 /*!< 0x00200000 */
#define ETH_MACMDIOAR_PA_1                  (0x2U << ETH_MACMDIOAR_PA_Pos)                 /*!< 0x00400000 */
#define ETH_MACMDIOAR_PA_2                  (0x4U << ETH_MACMDIOAR_PA_Pos)                 /*!< 0x00800000 */
#define ETH_MACMDIOAR_PA_3                  (0x8U << ETH_MACMDIOAR_PA_Pos)                /*!< 0x01000000 */
#define ETH_MACMDIOAR_PA_4                  (0x10U << ETH_MACMDIOAR_PA_Pos)                /*!< 0x02000000 */
#define ETH_MACMDIOAR_BTB_Pos               (26U)
#define ETH_MACMDIOAR_BTB_Msk               (0x1U << ETH_MACMDIOAR_BTB_Pos)                     /*!< 0x04000000 */
#define ETH_MACMDIOAR_BTB                   ETH_MACMDIOAR_BTB_Msk                               /*!< Back to Back transactions */
#define ETH_MACMDIOAR_PSE_Pos               (27U)
#define ETH_MACMDIOAR_PSE_Msk               (0x1U << ETH_MACMDIOAR_PSE_Pos)                     /*!< 0x08000000 */
#define ETH_MACMDIOAR_PSE                   ETH_MACMDIOAR_PSE_Msk                               /*!< Preamble Suppression Enable */

/*************  Bit definition for ETH_MACMDIODR register  *************/
#define ETH_MACMDIODR_GD_Pos                (0U)
#define ETH_MACMDIODR_GD_Msk                (0xFFFFU << ETH_MACMDIODR_GD_Pos)                   /*!< 0x0000FFFF */
#define ETH_MACMDIODR_GD                    ETH_MACMDIODR_GD_Msk                                /*!< GMII Data */
#define ETH_MACMDIODR_GD_0                  (0x1U << ETH_MACMDIODR_GD_Pos)                      /*!< 0x00000001 */
#define ETH_MACMDIODR_GD_1                  (0x2U << ETH_MACMDIODR_GD_Pos)                      /*!< 0x00000002 */
#define ETH_MACMDIODR_GD_2                  (0x4U << ETH_MACMDIODR_GD_Pos)                      /*!< 0x00000004 */
#define ETH_MACMDIODR_GD_3                  (0x8U << ETH_MACMDIODR_GD_Pos)                      /*!< 0x00000008 */
#define ETH_MACMDIODR_GD_4                  (0x10U << ETH_MACMDIODR_GD_Pos)                     /*!< 0x00000010 */
#define ETH_MACMDIODR_GD_5                  (0x20U << ETH_MACMDIODR_GD_Pos)                     /*!< 0x00000020 */
#define ETH_MACMDIODR_GD_6                  (0x40U << ETH_MACMDIODR_GD_Pos)                     /*!< 0x00000040 */
#define ETH_MACMDIODR_GD_7                  (0x80U << ETH_MACMDIODR_GD_Pos)                     /*!< 0x00000080 */
#define ETH_MACMDIODR_GD_8                  (0x100U << ETH_MACMDIODR_GD_Pos)                    /*!< 0x00000100 */
#define ETH_MACMDIODR_GD_9                  (0x200U << ETH_MACMDIODR_GD_Pos)                    /*!< 0x00000200 */
#define ETH_MACMDIODR_GD_10                 (0x400U << ETH_MACMDIODR_GD_Pos)                    /*!< 0x00000400 */
#define ETH_MACMDIODR_GD_11                 (0x800U << ETH_MACMDIODR_GD_Pos)                    /*!< 0x00000800 */
#define ETH_MACMDIODR_GD_12                 (0x1000U << ETH_MACMDIODR_GD_Pos)                   /*!< 0x00001000 */
#define ETH_MACMDIODR_GD_13                 (0x2000U << ETH_MACMDIODR_GD_Pos)                   /*!< 0x00002000 */
#define ETH_MACMDIODR_GD_14                 (0x4000U << ETH_MACMDIODR_GD_Pos)                   /*!< 0x00004000 */
#define ETH_MACMDIODR_GD_15                 (0x8000U << ETH_MACMDIODR_GD_Pos)                   /*!< 0x00008000 */
#define ETH_MACMDIODR_RA_Pos                (16U)
#define ETH_MACMDIODR_RA_Msk                (0xFFFFU << ETH_MACMDIODR_RA_Pos)                   /*!< 0xFFFF0000 */
#define ETH_MACMDIODR_RA                    ETH_MACMDIODR_RA_Msk                                /*!< Register Address */
#define ETH_MACMDIODR_RA_0                  (0x1U << ETH_MACMDIODR_RA_Pos)                  /*!< 0x00010000 */
#define ETH_MACMDIODR_RA_1                  (0x2U << ETH_MACMDIODR_RA_Pos)                  /*!< 0x00020000 */
#define ETH_MACMDIODR_RA_2                  (0x4U << ETH_MACMDIODR_RA_Pos)                  /*!< 0x00040000 */
#define ETH_MACMDIODR_RA_3                  (0x8U << ETH_MACMDIODR_RA_Pos)                  /*!< 0x00080000 */
#define ETH_MACMDIODR_RA_4                  (0x10U << ETH_MACMDIODR_RA_Pos)                 /*!< 0x00100000 */
#define ETH_MACMDIODR_RA_5                  (0x20U << ETH_MACMDIODR_RA_Pos)                 /*!< 0x00200000 */
#define ETH_MACMDIODR_RA_6                  (0x40U << ETH_MACMDIODR_RA_Pos)                 /*!< 0x00400000 */
#define ETH_MACMDIODR_RA_7                  (0x80U << ETH_MACMDIODR_RA_Pos)                 /*!< 0x00800000 */
#define ETH_MACMDIODR_RA_8                  (0x100U << ETH_MACMDIODR_RA_Pos)                /*!< 0x01000000 */
#define ETH_MACMDIODR_RA_9                  (0x200U << ETH_MACMDIODR_RA_Pos)                /*!< 0x02000000 */
#define ETH_MACMDIODR_RA_10                 (0x400U << ETH_MACMDIODR_RA_Pos)                /*!< 0x04000000 */
#define ETH_MACMDIODR_RA_11                 (0x800U << ETH_MACMDIODR_RA_Pos)                /*!< 0x08000000 */
#define ETH_MACMDIODR_RA_12                 (0x1000U << ETH_MACMDIODR_RA_Pos)               /*!< 0x10000000 */
#define ETH_MACMDIODR_RA_13                 (0x2000U << ETH_MACMDIODR_RA_Pos)               /*!< 0x20000000 */
#define ETH_MACMDIODR_RA_14                 (0x4000U << ETH_MACMDIODR_RA_Pos)               /*!< 0x40000000 */
#define ETH_MACMDIODR_RA_15                 (0x8000U << ETH_MACMDIODR_RA_Pos)               /*!< 0x80000000 */

/**************  Bit definition for ETH_MACA0HR register  **************/
#define ETH_MACA0HR_ADDRHI_Pos              (0U)
#define ETH_MACA0HR_ADDRHI_Msk              (0xFFFFU << ETH_MACA0HR_ADDRHI_Pos)                 /*!< 0x0000FFFF */
#define ETH_MACA0HR_ADDRHI                  ETH_MACA0HR_ADDRHI_Msk                              /*!< MAC Address0[47:32] */
#define ETH_MACA0HR_ADDRHI_0                (0x1U << ETH_MACA0HR_ADDRHI_Pos)                    /*!< 0x00000001 */
#define ETH_MACA0HR_ADDRHI_1                (0x2U << ETH_MACA0HR_ADDRHI_Pos)                    /*!< 0x00000002 */
#define ETH_MACA0HR_ADDRHI_2                (0x4U << ETH_MACA0HR_ADDRHI_Pos)                    /*!< 0x00000004 */
#define ETH_MACA0HR_ADDRHI_3                (0x8U << ETH_MACA0HR_ADDRHI_Pos)                    /*!< 0x00000008 */
#define ETH_MACA0HR_ADDRHI_4                (0x10U << ETH_MACA0HR_ADDRHI_Pos)                   /*!< 0x00000010 */
#define ETH_MACA0HR_ADDRHI_5                (0x20U << ETH_MACA0HR_ADDRHI_Pos)                   /*!< 0x00000020 */
#define ETH_MACA0HR_ADDRHI_6                (0x40U << ETH_MACA0HR_ADDRHI_Pos)                   /*!< 0x00000040 */
#define ETH_MACA0HR_ADDRHI_7                (0x80U << ETH_MACA0HR_ADDRHI_Pos)                   /*!< 0x00000080 */
#define ETH_MACA0HR_ADDRHI_8                (0x100U << ETH_MACA0HR_ADDRHI_Pos)                  /*!< 0x00000100 */
#define ETH_MACA0HR_ADDRHI_9                (0x200U << ETH_MACA0HR_ADDRHI_Pos)                  /*!< 0x00000200 */
#define ETH_MACA0HR_ADDRHI_10               (0x400U << ETH_MACA0HR_ADDRHI_Pos)                  /*!< 0x00000400 */
#define ETH_MACA0HR_ADDRHI_11               (0x800U << ETH_MACA0HR_ADDRHI_Pos)                  /*!< 0x00000800 */
#define ETH_MACA0HR_ADDRHI_12               (0x1000U << ETH_MACA0HR_ADDRHI_Pos)                 /*!< 0x00001000 */
#define ETH_MACA0HR_ADDRHI_13               (0x2000U << ETH_MACA0HR_ADDRHI_Pos)                 /*!< 0x00002000 */
#define ETH_MACA0HR_ADDRHI_14               (0x4000U << ETH_MACA0HR_ADDRHI_Pos)                 /*!< 0x00004000 */
#define ETH_MACA0HR_ADDRHI_15               (0x8000U << ETH_MACA0HR_ADDRHI_Pos)                 /*!< 0x00008000 */
#define ETH_MACA0HR_AE_Pos                  (31U)
#define ETH_MACA0HR_AE_Msk                  (0x1U << ETH_MACA0HR_AE_Pos)                        /*!< 0x80000000 */
#define ETH_MACA0HR_AE                      ETH_MACA0HR_AE_Msk                                  /*!< Address Enable */

/**************  Bit definition for ETH_MACA0LR register  **************/
#define ETH_MACA0LR_ADDRLO_Pos              (0U)
#define ETH_MACA0LR_ADDRLO_Msk              (0xFFFFFFFFU << ETH_MACA0LR_ADDRLO_Pos)             /*!< 0xFFFFFFFF */
#define ETH_MACA0LR_ADDRLO                  ETH_MACA0LR_ADDRLO_Msk                              /*!< MAC Address x [31:0] (x = 0 to 3) */
#define ETH_MACA0LR_ADDRLO_0                (0x1U << ETH_MACA0LR_ADDRLO_Pos)                    /*!< 0x00000001 */
#define ETH_MACA0LR_ADDRLO_1                (0x2U << ETH_MACA0LR_ADDRLO_Pos)                    /*!< 0x00000002 */
#define ETH_MACA0LR_ADDRLO_2                (0x4U << ETH_MACA0LR_ADDRLO_Pos)                    /*!< 0x00000004 */
#define ETH_MACA0LR_ADDRLO_3                (0x8U << ETH_MACA0LR_ADDRLO_Pos)                    /*!< 0x00000008 */
#define ETH_MACA0LR_ADDRLO_4                (0x10U << ETH_MACA0LR_ADDRLO_Pos)                   /*!< 0x00000010 */
#define ETH_MACA0LR_ADDRLO_5                (0x20U << ETH_MACA0LR_ADDRLO_Pos)                   /*!< 0x00000020 */
#define ETH_MACA0LR_ADDRLO_6                (0x40U << ETH_MACA0LR_ADDRLO_Pos)                   /*!< 0x00000040 */
#define ETH_MACA0LR_ADDRLO_7                (0x80U << ETH_MACA0LR_ADDRLO_Pos)                   /*!< 0x00000080 */
#define ETH_MACA0LR_ADDRLO_8                (0x100U << ETH_MACA0LR_ADDRLO_Pos)                  /*!< 0x00000100 */
#define ETH_MACA0LR_ADDRLO_9                (0x200U << ETH_MACA0LR_ADDRLO_Pos)                  /*!< 0x00000200 */
#define ETH_MACA0LR_ADDRLO_10               (0x400U << ETH_MACA0LR_ADDRLO_Pos)                  /*!< 0x00000400 */
#define ETH_MACA0LR_ADDRLO_11               (0x800U << ETH_MACA0LR_ADDRLO_Pos)                  /*!< 0x00000800 */
#define ETH_MACA0LR_ADDRLO_12               (0x1000U << ETH_MACA0LR_ADDRLO_Pos)                 /*!< 0x00001000 */
#define ETH_MACA0LR_ADDRLO_13               (0x2000U << ETH_MACA0LR_ADDRLO_Pos)                 /*!< 0x00002000 */
#define ETH_MACA0LR_ADDRLO_14               (0x4000U << ETH_MACA0LR_ADDRLO_Pos)                 /*!< 0x00004000 */
#define ETH_MACA0LR_ADDRLO_15               (0x8000U << ETH_MACA0LR_ADDRLO_Pos)                 /*!< 0x00008000 */
#define ETH_MACA0LR_ADDRLO_16               (0x10000U << ETH_MACA0LR_ADDRLO_Pos)                /*!< 0x00010000 */
#define ETH_MACA0LR_ADDRLO_17               (0x20000U << ETH_MACA0LR_ADDRLO_Pos)                /*!< 0x00020000 */
#define ETH_MACA0LR_ADDRLO_18               (0x40000U << ETH_MACA0LR_ADDRLO_Pos)                /*!< 0x00040000 */
#define ETH_MACA0LR_ADDRLO_19               (0x80000U << ETH_MACA0LR_ADDRLO_Pos)                /*!< 0x00080000 */
#define ETH_MACA0LR_ADDRLO_20               (0x100000U << ETH_MACA0LR_ADDRLO_Pos)               /*!< 0x00100000 */
#define ETH_MACA0LR_ADDRLO_21               (0x200000U << ETH_MACA0LR_ADDRLO_Pos)               /*!< 0x00200000 */
#define ETH_MACA0LR_ADDRLO_22               (0x400000U << ETH_MACA0LR_ADDRLO_Pos)               /*!< 0x00400000 */
#define ETH_MACA0LR_ADDRLO_23               (0x800000U << ETH_MACA0LR_ADDRLO_Pos)               /*!< 0x00800000 */
#define ETH_MACA0LR_ADDRLO_24               (0x1000000U << ETH_MACA0LR_ADDRLO_Pos)              /*!< 0x01000000 */
#define ETH_MACA0LR_ADDRLO_25               (0x2000000U << ETH_MACA0LR_ADDRLO_Pos)              /*!< 0x02000000 */
#define ETH_MACA0LR_ADDRLO_26               (0x4000000U << ETH_MACA0LR_ADDRLO_Pos)              /*!< 0x04000000 */
#define ETH_MACA0LR_ADDRLO_27               (0x8000000U << ETH_MACA0LR_ADDRLO_Pos)              /*!< 0x08000000 */
#define ETH_MACA0LR_ADDRLO_28               (0x10000000U << ETH_MACA0LR_ADDRLO_Pos)             /*!< 0x10000000 */
#define ETH_MACA0LR_ADDRLO_29               (0x20000000U << ETH_MACA0LR_ADDRLO_Pos)             /*!< 0x20000000 */
#define ETH_MACA0LR_ADDRLO_30               (0x40000000U << ETH_MACA0LR_ADDRLO_Pos)             /*!< 0x40000000 */
#define ETH_MACA0LR_ADDRLO_31               (0x80000000U << ETH_MACA0LR_ADDRLO_Pos)             /*!< 0x80000000 */

/**************  Bit definition for ETH_MACA1HR register  **************/
#define ETH_MACA1HR_ADDRHI_Pos              (0U)
#define ETH_MACA1HR_ADDRHI_Msk              (0xFFFFU << ETH_MACA1HR_ADDRHI_Pos)                 /*!< 0x0000FFFF */
#define ETH_MACA1HR_ADDRHI                  ETH_MACA1HR_ADDRHI_Msk                              /*!< MAC Address1 [47:32] */
#define ETH_MACA1HR_ADDRHI_0                (0x1U << ETH_MACA1HR_ADDRHI_Pos)                    /*!< 0x00000001 */
#define ETH_MACA1HR_ADDRHI_1                (0x2U << ETH_MACA1HR_ADDRHI_Pos)                    /*!< 0x00000002 */
#define ETH_MACA1HR_ADDRHI_2                (0x4U << ETH_MACA1HR_ADDRHI_Pos)                    /*!< 0x00000004 */
#define ETH_MACA1HR_ADDRHI_3                (0x8U << ETH_MACA1HR_ADDRHI_Pos)                    /*!< 0x00000008 */
#define ETH_MACA1HR_ADDRHI_4                (0x10U << ETH_MACA1HR_ADDRHI_Pos)                   /*!< 0x00000010 */
#define ETH_MACA1HR_ADDRHI_5                (0x20U << ETH_MACA1HR_ADDRHI_Pos)                   /*!< 0x00000020 */
#define ETH_MACA1HR_ADDRHI_6                (0x40U << ETH_MACA1HR_ADDRHI_Pos)                   /*!< 0x00000040 */
#define ETH_MACA1HR_ADDRHI_7                (0x80U << ETH_MACA1HR_ADDRHI_Pos)                   /*!< 0x00000080 */
#define ETH_MACA1HR_ADDRHI_8                (0x100U << ETH_MACA1HR_ADDRHI_Pos)                  /*!< 0x00000100 */
#define ETH_MACA1HR_ADDRHI_9                (0x200U << ETH_MACA1HR_ADDRHI_Pos)                  /*!< 0x00000200 */
#define ETH_MACA1HR_ADDRHI_10               (0x400U << ETH_MACA1HR_ADDRHI_Pos)                  /*!< 0x00000400 */
#define ETH_MACA1HR_ADDRHI_11               (0x800U << ETH_MACA1HR_ADDRHI_Pos)                  /*!< 0x00000800 */
#define ETH_MACA1HR_ADDRHI_12               (0x1000U << ETH_MACA1HR_ADDRHI_Pos)                 /*!< 0x00001000 */
#define ETH_MACA1HR_ADDRHI_13               (0x2000U << ETH_MACA1HR_ADDRHI_Pos)                 /*!< 0x00002000 */
#define ETH_MACA1HR_ADDRHI_14               (0x4000U << ETH_MACA1HR_ADDRHI_Pos)                 /*!< 0x00004000 */
#define ETH_MACA1HR_ADDRHI_15               (0x8000U << ETH_MACA1HR_ADDRHI_Pos)                 /*!< 0x00008000 */
#define ETH_MACA1HR_MBC_Pos                 (24U)
#define ETH_MACA1HR_MBC_Msk                 (0x3FU << ETH_MACA1HR_MBC_Pos)                      /*!< 0x3F000000 */
#define ETH_MACA1HR_MBC                     ETH_MACA1HR_MBC_Msk                                 /*!< Mask Byte Control */
#define ETH_MACA1HR_MBC_0                   (0x1U << ETH_MACA1HR_MBC_Pos)                 /*!< 0x01000000 */
#define ETH_MACA1HR_MBC_1                   (0x2U << ETH_MACA1HR_MBC_Pos)                 /*!< 0x02000000 */
#define ETH_MACA1HR_MBC_2                   (0x4U << ETH_MACA1HR_MBC_Pos)                 /*!< 0x04000000 */
#define ETH_MACA1HR_MBC_3                   (0x8U << ETH_MACA1HR_MBC_Pos)                 /*!< 0x08000000 */
#define ETH_MACA1HR_MBC_4                   (0x10U << ETH_MACA1HR_MBC_Pos)                /*!< 0x10000000 */
#define ETH_MACA1HR_MBC_5                   (0x20U << ETH_MACA1HR_MBC_Pos)                /*!< 0x20000000 */
#define ETH_MACA1HR_SA_Pos                  (30U)
#define ETH_MACA1HR_SA_Msk                  (0x1U << ETH_MACA1HR_SA_Pos)                        /*!< 0x40000000 */
#define ETH_MACA1HR_SA                      ETH_MACA1HR_SA_Msk                                  /*!< Source Address */
#define ETH_MACA1HR_AE_Pos                  (31U)
#define ETH_MACA1HR_AE_Msk                  (0x1U << ETH_MACA1HR_AE_Pos)                        /*!< 0x80000000 */
#define ETH_MACA1HR_AE                      ETH_MACA1HR_AE_Msk                                  /*!< Address Enable */

/**************  Bit definition for ETH_MACA1LR register  **************/
#define ETH_MACA1LR_ADDRLO_Pos              (0U)
#define ETH_MACA1LR_ADDRLO_Msk              (0xFFFFFFFFU << ETH_MACA1LR_ADDRLO_Pos)             /*!< 0xFFFFFFFF */
#define ETH_MACA1LR_ADDRLO                  ETH_MACA1LR_ADDRLO_Msk                              /*!< MAC Address x [31:0] (x = 0 to 3) */
#define ETH_MACA1LR_ADDRLO_0                (0x1U << ETH_MACA1LR_ADDRLO_Pos)                    /*!< 0x00000001 */
#define ETH_MACA1LR_ADDRLO_1                (0x2U << ETH_MACA1LR_ADDRLO_Pos)                    /*!< 0x00000002 */
#define ETH_MACA1LR_ADDRLO_2                (0x4U << ETH_MACA1LR_ADDRLO_Pos)                    /*!< 0x00000004 */
#define ETH_MACA1LR_ADDRLO_3                (0x8U << ETH_MACA1LR_ADDRLO_Pos)                    /*!< 0x00000008 */
#define ETH_MACA1LR_ADDRLO_4                (0x10U << ETH_MACA1LR_ADDRLO_Pos)                   /*!< 0x00000010 */
#define ETH_MACA1LR_ADDRLO_5                (0x20U << ETH_MACA1LR_ADDRLO_Pos)                   /*!< 0x00000020 */
#define ETH_MACA1LR_ADDRLO_6                (0x40U << ETH_MACA1LR_ADDRLO_Pos)                   /*!< 0x00000040 */
#define ETH_MACA1LR_ADDRLO_7                (0x80U << ETH_MACA1LR_ADDRLO_Pos)                   /*!< 0x00000080 */
#define ETH_MACA1LR_ADDRLO_8                (0x100U << ETH_MACA1LR_ADDRLO_Pos)                  /*!< 0x00000100 */
#define ETH_MACA1LR_ADDRLO_9                (0x200U << ETH_MACA1LR_ADDRLO_Pos)                  /*!< 0x00000200 */
#define ETH_MACA1LR_ADDRLO_10               (0x400U << ETH_MACA1LR_ADDRLO_Pos)                  /*!< 0x00000400 */
#define ETH_MACA1LR_ADDRLO_11               (0x800U << ETH_MACA1LR_ADDRLO_Pos)                  /*!< 0x00000800 */
#define ETH_MACA1LR_ADDRLO_12               (0x1000U << ETH_MACA1LR_ADDRLO_Pos)                 /*!< 0x00001000 */
#define ETH_MACA1LR_ADDRLO_13               (0x2000U << ETH_MACA1LR_ADDRLO_Pos)                 /*!< 0x00002000 */
#define ETH_MACA1LR_ADDRLO_14               (0x4000U << ETH_MACA1LR_ADDRLO_Pos)                 /*!< 0x00004000 */
#define ETH_MACA1LR_ADDRLO_15               (0x8000U << ETH_MACA1LR_ADDRLO_Pos)                 /*!< 0x00008000 */
#define ETH_MACA1LR_ADDRLO_16               (0x10000U << ETH_MACA1LR_ADDRLO_Pos)                /*!< 0x00010000 */
#define ETH_MACA1LR_ADDRLO_17               (0x20000U << ETH_MACA1LR_ADDRLO_Pos)                /*!< 0x00020000 */
#define ETH_MACA1LR_ADDRLO_18               (0x40000U << ETH_MACA1LR_ADDRLO_Pos)                /*!< 0x00040000 */
#define ETH_MACA1LR_ADDRLO_19               (0x80000U << ETH_MACA1LR_ADDRLO_Pos)                /*!< 0x00080000 */
#define ETH_MACA1LR_ADDRLO_20               (0x100000U << ETH_MACA1LR_ADDRLO_Pos)               /*!< 0x00100000 */
#define ETH_MACA1LR_ADDRLO_21               (0x200000U << ETH_MACA1LR_ADDRLO_Pos)               /*!< 0x00200000 */
#define ETH_MACA1LR_ADDRLO_22               (0x400000U << ETH_MACA1LR_ADDRLO_Pos)               /*!< 0x00400000 */
#define ETH_MACA1LR_ADDRLO_23               (0x800000U << ETH_MACA1LR_ADDRLO_Pos)               /*!< 0x00800000 */
#define ETH_MACA1LR_ADDRLO_24               (0x1000000U << ETH_MACA1LR_ADDRLO_Pos)              /*!< 0x01000000 */
#define ETH_MACA1LR_ADDRLO_25               (0x2000000U << ETH_MACA1LR_ADDRLO_Pos)              /*!< 0x02000000 */
#define ETH_MACA1LR_ADDRLO_26               (0x4000000U << ETH_MACA1LR_ADDRLO_Pos)              /*!< 0x04000000 */
#define ETH_MACA1LR_ADDRLO_27               (0x8000000U << ETH_MACA1LR_ADDRLO_Pos)              /*!< 0x08000000 */
#define ETH_MACA1LR_ADDRLO_28               (0x10000000U << ETH_MACA1LR_ADDRLO_Pos)             /*!< 0x10000000 */
#define ETH_MACA1LR_ADDRLO_29               (0x20000000U << ETH_MACA1LR_ADDRLO_Pos)             /*!< 0x20000000 */
#define ETH_MACA1LR_ADDRLO_30               (0x40000000U << ETH_MACA1LR_ADDRLO_Pos)             /*!< 0x40000000 */
#define ETH_MACA1LR_ADDRLO_31               (0x80000000U << ETH_MACA1LR_ADDRLO_Pos)             /*!< 0x80000000 */

/**************  Bit definition for ETH_MACA2HR register  **************/
#define ETH_MACA2HR_ADDRHI_Pos              (0U)
#define ETH_MACA2HR_ADDRHI_Msk              (0xFFFFU << ETH_MACA2HR_ADDRHI_Pos)                 /*!< 0x0000FFFF */
#define ETH_MACA2HR_ADDRHI                  ETH_MACA2HR_ADDRHI_Msk                              /*!< MAC Address1 [47:32] */
#define ETH_MACA2HR_ADDRHI_0                (0x1U << ETH_MACA2HR_ADDRHI_Pos)                    /*!< 0x00000001 */
#define ETH_MACA2HR_ADDRHI_1                (0x2U << ETH_MACA2HR_ADDRHI_Pos)                    /*!< 0x00000002 */
#define ETH_MACA2HR_ADDRHI_2                (0x4U << ETH_MACA2HR_ADDRHI_Pos)                    /*!< 0x00000004 */
#define ETH_MACA2HR_ADDRHI_3                (0x8U << ETH_MACA2HR_ADDRHI_Pos)                    /*!< 0x00000008 */
#define ETH_MACA2HR_ADDRHI_4                (0x10U << ETH_MACA2HR_ADDRHI_Pos)                   /*!< 0x00000010 */
#define ETH_MACA2HR_ADDRHI_5                (0x20U << ETH_MACA2HR_ADDRHI_Pos)                   /*!< 0x00000020 */
#define ETH_MACA2HR_ADDRHI_6                (0x40U << ETH_MACA2HR_ADDRHI_Pos)                   /*!< 0x00000040 */
#define ETH_MACA2HR_ADDRHI_7                (0x80U << ETH_MACA2HR_ADDRHI_Pos)                   /*!< 0x00000080 */
#define ETH_MACA2HR_ADDRHI_8                (0x100U << ETH_MACA2HR_ADDRHI_Pos)                  /*!< 0x00000100 */
#define ETH_MACA2HR_ADDRHI_9                (0x200U << ETH_MACA2HR_ADDRHI_Pos)                  /*!< 0x00000200 */
#define ETH_MACA2HR_ADDRHI_10               (0x400U << ETH_MACA2HR_ADDRHI_Pos)                  /*!< 0x00000400 */
#define ETH_MACA2HR_ADDRHI_11               (0x800U << ETH_MACA2HR_ADDRHI_Pos)                  /*!< 0x00000800 */
#define ETH_MACA2HR_ADDRHI_12               (0x1000U << ETH_MACA2HR_ADDRHI_Pos)                 /*!< 0x00001000 */
#define ETH_MACA2HR_ADDRHI_13               (0x2000U << ETH_MACA2HR_ADDRHI_Pos)                 /*!< 0x00002000 */
#define ETH_MACA2HR_ADDRHI_14               (0x4000U << ETH_MACA2HR_ADDRHI_Pos)                 /*!< 0x00004000 */
#define ETH_MACA2HR_ADDRHI_15               (0x8000U << ETH_MACA2HR_ADDRHI_Pos)                 /*!< 0x00008000 */
#define ETH_MACA2HR_MBC_Pos                 (24U)
#define ETH_MACA2HR_MBC_Msk                 (0x3FU << ETH_MACA2HR_MBC_Pos)                      /*!< 0x3F000000 */
#define ETH_MACA2HR_MBC                     ETH_MACA2HR_MBC_Msk                                 /*!< Mask Byte Control */
#define ETH_MACA2HR_MBC_0                   (0x1U << ETH_MACA2HR_MBC_Pos)                 /*!< 0x01000000 */
#define ETH_MACA2HR_MBC_1                   (0x2U << ETH_MACA2HR_MBC_Pos)                 /*!< 0x02000000 */
#define ETH_MACA2HR_MBC_2                   (0x4U << ETH_MACA2HR_MBC_Pos)                 /*!< 0x04000000 */
#define ETH_MACA2HR_MBC_3                   (0x8U << ETH_MACA2HR_MBC_Pos)                 /*!< 0x08000000 */
#define ETH_MACA2HR_MBC_4                   (0x10U << ETH_MACA2HR_MBC_Pos)                /*!< 0x10000000 */
#define ETH_MACA2HR_MBC_5                   (0x20U << ETH_MACA2HR_MBC_Pos)                /*!< 0x20000000 */
#define ETH_MACA2HR_SA_Pos                  (30U)
#define ETH_MACA2HR_SA_Msk                  (0x1U << ETH_MACA2HR_SA_Pos)                        /*!< 0x40000000 */
#define ETH_MACA2HR_SA                      ETH_MACA2HR_SA_Msk                                  /*!< Source Address */
#define ETH_MACA2HR_AE_Pos                  (31U)
#define ETH_MACA2HR_AE_Msk                  (0x1U << ETH_MACA2HR_AE_Pos)                        /*!< 0x80000000 */
#define ETH_MACA2HR_AE                      ETH_MACA2HR_AE_Msk                                  /*!< Address Enable */

/**************  Bit definition for ETH_MACA2LR register  **************/
#define ETH_MACA2LR_ADDRLO_Pos              (0U)
#define ETH_MACA2LR_ADDRLO_Msk              (0xFFFFFFFFU << ETH_MACA2LR_ADDRLO_Pos)             /*!< 0xFFFFFFFF */
#define ETH_MACA2LR_ADDRLO                  ETH_MACA2LR_ADDRLO_Msk                              /*!< MAC Address x [31:0] (x = 0 to 3) */
#define ETH_MACA2LR_ADDRLO_0                (0x1U << ETH_MACA2LR_ADDRLO_Pos)                    /*!< 0x00000001 */
#define ETH_MACA2LR_ADDRLO_1                (0x2U << ETH_MACA2LR_ADDRLO_Pos)                    /*!< 0x00000002 */
#define ETH_MACA2LR_ADDRLO_2                (0x4U << ETH_MACA2LR_ADDRLO_Pos)                    /*!< 0x00000004 */
#define ETH_MACA2LR_ADDRLO_3                (0x8U << ETH_MACA2LR_ADDRLO_Pos)                    /*!< 0x00000008 */
#define ETH_MACA2LR_ADDRLO_4                (0x10U << ETH_MACA2LR_ADDRLO_Pos)                   /*!< 0x00000010 */
#define ETH_MACA2LR_ADDRLO_5                (0x20U << ETH_MACA2LR_ADDRLO_Pos)                   /*!< 0x00000020 */
#define ETH_MACA2LR_ADDRLO_6                (0x40U << ETH_MACA2LR_ADDRLO_Pos)                   /*!< 0x00000040 */
#define ETH_MACA2LR_ADDRLO_7                (0x80U << ETH_MACA2LR_ADDRLO_Pos)                   /*!< 0x00000080 */
#define ETH_MACA2LR_ADDRLO_8                (0x100U << ETH_MACA2LR_ADDRLO_Pos)                  /*!< 0x00000100 */
#define ETH_MACA2LR_ADDRLO_9                (0x200U << ETH_MACA2LR_ADDRLO_Pos)                  /*!< 0x00000200 */
#define ETH_MACA2LR_ADDRLO_10               (0x400U << ETH_MACA2LR_ADDRLO_Pos)                  /*!< 0x00000400 */
#define ETH_MACA2LR_ADDRLO_11               (0x800U << ETH_MACA2LR_ADDRLO_Pos)                  /*!< 0x00000800 */
#define ETH_MACA2LR_ADDRLO_12               (0x1000U << ETH_MACA2LR_ADDRLO_Pos)                 /*!< 0x00001000 */
#define ETH_MACA2LR_ADDRLO_13               (0x2000U << ETH_MACA2LR_ADDRLO_Pos)                 /*!< 0x00002000 */
#define ETH_MACA2LR_ADDRLO_14               (0x4000U << ETH_MACA2LR_ADDRLO_Pos)                 /*!< 0x00004000 */
#define ETH_MACA2LR_ADDRLO_15               (0x8000U << ETH_MACA2LR_ADDRLO_Pos)                 /*!< 0x00008000 */
#define ETH_MACA2LR_ADDRLO_16               (0x10000U << ETH_MACA2LR_ADDRLO_Pos)                /*!< 0x00010000 */
#define ETH_MACA2LR_ADDRLO_17               (0x20000U << ETH_MACA2LR_ADDRLO_Pos)                /*!< 0x00020000 */
#define ETH_MACA2LR_ADDRLO_18               (0x40000U << ETH_MACA2LR_ADDRLO_Pos)                /*!< 0x00040000 */
#define ETH_MACA2LR_ADDRLO_19               (0x80000U << ETH_MACA2LR_ADDRLO_Pos)                /*!< 0x00080000 */
#define ETH_MACA2LR_ADDRLO_20               (0x100000U << ETH_MACA2LR_ADDRLO_Pos)               /*!< 0x00100000 */
#define ETH_MACA2LR_ADDRLO_21               (0x200000U << ETH_MACA2LR_ADDRLO_Pos)               /*!< 0x00200000 */
#define ETH_MACA2LR_ADDRLO_22               (0x400000U << ETH_MACA2LR_ADDRLO_Pos)               /*!< 0x00400000 */
#define ETH_MACA2LR_ADDRLO_23               (0x800000U << ETH_MACA2LR_ADDRLO_Pos)               /*!< 0x00800000 */
#define ETH_MACA2LR_ADDRLO_24               (0x1000000U << ETH_MACA2LR_ADDRLO_Pos)              /*!< 0x01000000 */
#define ETH_MACA2LR_ADDRLO_25               (0x2000000U << ETH_MACA2LR_ADDRLO_Pos)              /*!< 0x02000000 */
#define ETH_MACA2LR_ADDRLO_26               (0x4000000U << ETH_MACA2LR_ADDRLO_Pos)              /*!< 0x04000000 */
#define ETH_MACA2LR_ADDRLO_27               (0x8000000U << ETH_MACA2LR_ADDRLO_Pos)              /*!< 0x08000000 */
#define ETH_MACA2LR_ADDRLO_28               (0x10000000U << ETH_MACA2LR_ADDRLO_Pos)             /*!< 0x10000000 */
#define ETH_MACA2LR_ADDRLO_29               (0x20000000U << ETH_MACA2LR_ADDRLO_Pos)             /*!< 0x20000000 */
#define ETH_MACA2LR_ADDRLO_30               (0x40000000U << ETH_MACA2LR_ADDRLO_Pos)             /*!< 0x40000000 */
#define ETH_MACA2LR_ADDRLO_31               (0x80000000U << ETH_MACA2LR_ADDRLO_Pos)             /*!< 0x80000000 */

/**************  Bit definition for ETH_MACA3HR register  **************/
#define ETH_MACA3HR_ADDRHI_Pos              (0U)
#define ETH_MACA3HR_ADDRHI_Msk              (0xFFFFU << ETH_MACA3HR_ADDRHI_Pos)                 /*!< 0x0000FFFF */
#define ETH_MACA3HR_ADDRHI                  ETH_MACA3HR_ADDRHI_Msk                              /*!< MAC Address1 [47:32] */
#define ETH_MACA3HR_ADDRHI_0                (0x1U << ETH_MACA3HR_ADDRHI_Pos)                    /*!< 0x00000001 */
#define ETH_MACA3HR_ADDRHI_1                (0x2U << ETH_MACA3HR_ADDRHI_Pos)                    /*!< 0x00000002 */
#define ETH_MACA3HR_ADDRHI_2                (0x4U << ETH_MACA3HR_ADDRHI_Pos)                    /*!< 0x00000004 */
#define ETH_MACA3HR_ADDRHI_3                (0x8U << ETH_MACA3HR_ADDRHI_Pos)                    /*!< 0x00000008 */
#define ETH_MACA3HR_ADDRHI_4                (0x10U << ETH_MACA3HR_ADDRHI_Pos)                   /*!< 0x00000010 */
#define ETH_MACA3HR_ADDRHI_5                (0x20U << ETH_MACA3HR_ADDRHI_Pos)                   /*!< 0x00000020 */
#define ETH_MACA3HR_ADDRHI_6                (0x40U << ETH_MACA3HR_ADDRHI_Pos)                   /*!< 0x00000040 */
#define ETH_MACA3HR_ADDRHI_7                (0x80U << ETH_MACA3HR_ADDRHI_Pos)                   /*!< 0x00000080 */
#define ETH_MACA3HR_ADDRHI_8                (0x100U << ETH_MACA3HR_ADDRHI_Pos)                  /*!< 0x00000100 */
#define ETH_MACA3HR_ADDRHI_9                (0x200U << ETH_MACA3HR_ADDRHI_Pos)                  /*!< 0x00000200 */
#define ETH_MACA3HR_ADDRHI_10               (0x400U << ETH_MACA3HR_ADDRHI_Pos)                  /*!< 0x00000400 */
#define ETH_MACA3HR_ADDRHI_11               (0x800U << ETH_MACA3HR_ADDRHI_Pos)                  /*!< 0x00000800 */
#define ETH_MACA3HR_ADDRHI_12               (0x1000U << ETH_MACA3HR_ADDRHI_Pos)                 /*!< 0x00001000 */
#define ETH_MACA3HR_ADDRHI_13               (0x2000U << ETH_MACA3HR_ADDRHI_Pos)                 /*!< 0x00002000 */
#define ETH_MACA3HR_ADDRHI_14               (0x4000U << ETH_MACA3HR_ADDRHI_Pos)                 /*!< 0x00004000 */
#define ETH_MACA3HR_ADDRHI_15               (0x8000U << ETH_MACA3HR_ADDRHI_Pos)                 /*!< 0x00008000 */
#define ETH_MACA3HR_MBC_Pos                 (24U)
#define ETH_MACA3HR_MBC_Msk                 (0x3FU << ETH_MACA3HR_MBC_Pos)                      /*!< 0x3F000000 */
#define ETH_MACA3HR_MBC                     ETH_MACA3HR_MBC_Msk                                 /*!< Mask Byte Control */
#define ETH_MACA3HR_MBC_0                   (0x1U << ETH_MACA3HR_MBC_Pos)                 /*!< 0x01000000 */
#define ETH_MACA3HR_MBC_1                   (0x2U << ETH_MACA3HR_MBC_Pos)                 /*!< 0x02000000 */
#define ETH_MACA3HR_MBC_2                   (0x4U << ETH_MACA3HR_MBC_Pos)                 /*!< 0x04000000 */
#define ETH_MACA3HR_MBC_3                   (0x8U << ETH_MACA3HR_MBC_Pos)                 /*!< 0x08000000 */
#define ETH_MACA3HR_MBC_4                   (0x10U << ETH_MACA3HR_MBC_Pos)                /*!< 0x10000000 */
#define ETH_MACA3HR_MBC_5                   (0x20U << ETH_MACA3HR_MBC_Pos)                /*!< 0x20000000 */
#define ETH_MACA3HR_SA_Pos                  (30U)
#define ETH_MACA3HR_SA_Msk                  (0x1U << ETH_MACA3HR_SA_Pos)                        /*!< 0x40000000 */
#define ETH_MACA3HR_SA                      ETH_MACA3HR_SA_Msk                                  /*!< Source Address */
#define ETH_MACA3HR_AE_Pos                  (31U)
#define ETH_MACA3HR_AE_Msk                  (0x1U << ETH_MACA3HR_AE_Pos)                        /*!< 0x80000000 */
#define ETH_MACA3HR_AE                      ETH_MACA3HR_AE_Msk                                  /*!< Address Enable */

/**************  Bit definition for ETH_MACA3LR register  **************/
#define ETH_MACA3LR_ADDRLO_Pos              (0U)
#define ETH_MACA3LR_ADDRLO_Msk              (0xFFFFFFFFU << ETH_MACA3LR_ADDRLO_Pos)             /*!< 0xFFFFFFFF */
#define ETH_MACA3LR_ADDRLO                  ETH_MACA3LR_ADDRLO_Msk                              /*!< MAC Address x [31:0] (x = 0 to 3) */
#define ETH_MACA3LR_ADDRLO_0                (0x1U << ETH_MACA3LR_ADDRLO_Pos)                    /*!< 0x00000001 */
#define ETH_MACA3LR_ADDRLO_1                (0x2U << ETH_MACA3LR_ADDRLO_Pos)                    /*!< 0x00000002 */
#define ETH_MACA3LR_ADDRLO_2                (0x4U << ETH_MACA3LR_ADDRLO_Pos)                    /*!< 0x00000004 */
#define ETH_MACA3LR_ADDRLO_3                (0x8U << ETH_MACA3LR_ADDRLO_Pos)                    /*!< 0x00000008 */
#define ETH_MACA3LR_ADDRLO_4                (0x10U << ETH_MACA3LR_ADDRLO_Pos)                   /*!< 0x00000010 */
#define ETH_MACA3LR_ADDRLO_5                (0x20U << ETH_MACA3LR_ADDRLO_Pos)                   /*!< 0x00000020 */
#define ETH_MACA3LR_ADDRLO_6                (0x40U << ETH_MACA3LR_ADDRLO_Pos)                   /*!< 0x00000040 */
#define ETH_MACA3LR_ADDRLO_7                (0x80U << ETH_MACA3LR_ADDRLO_Pos)                   /*!< 0x00000080 */
#define ETH_MACA3LR_ADDRLO_8                (0x100U << ETH_MACA3LR_ADDRLO_Pos)                  /*!< 0x00000100 */
#define ETH_MACA3LR_ADDRLO_9                (0x200U << ETH_MACA3LR_ADDRLO_Pos)                  /*!< 0x00000200 */
#define ETH_MACA3LR_ADDRLO_10               (0x400U << ETH_MACA3LR_ADDRLO_Pos)                  /*!< 0x00000400 */
#define ETH_MACA3LR_ADDRLO_11               (0x800U << ETH_MACA3LR_ADDRLO_Pos)                  /*!< 0x00000800 */
#define ETH_MACA3LR_ADDRLO_12               (0x1000U << ETH_MACA3LR_ADDRLO_Pos)                 /*!< 0x00001000 */
#define ETH_MACA3LR_ADDRLO_13               (0x2000U << ETH_MACA3LR_ADDRLO_Pos)                 /*!< 0x00002000 */
#define ETH_MACA3LR_ADDRLO_14               (0x4000U << ETH_MACA3LR_ADDRLO_Pos)                 /*!< 0x00004000 */
#define ETH_MACA3LR_ADDRLO_15               (0x8000U << ETH_MACA3LR_ADDRLO_Pos)                 /*!< 0x00008000 */
#define ETH_MACA3LR_ADDRLO_16               (0x10000U << ETH_MACA3LR_ADDRLO_Pos)                /*!< 0x00010000 */
#define ETH_MACA3LR_ADDRLO_17               (0x20000U << ETH_MACA3LR_ADDRLO_Pos)                /*!< 0x00020000 */
#define ETH_MACA3LR_ADDRLO_18               (0x40000U << ETH_MACA3LR_ADDRLO_Pos)                /*!< 0x00040000 */
#define ETH_MACA3LR_ADDRLO_19               (0x80000U << ETH_MACA3LR_ADDRLO_Pos)                /*!< 0x00080000 */
#define ETH_MACA3LR_ADDRLO_20               (0x100000U << ETH_MACA3LR_ADDRLO_Pos)               /*!< 0x00100000 */
#define ETH_MACA3LR_ADDRLO_21               (0x200000U << ETH_MACA3LR_ADDRLO_Pos)               /*!< 0x00200000 */
#define ETH_MACA3LR_ADDRLO_22               (0x400000U << ETH_MACA3LR_ADDRLO_Pos)               /*!< 0x00400000 */
#define ETH_MACA3LR_ADDRLO_23               (0x800000U << ETH_MACA3LR_ADDRLO_Pos)               /*!< 0x00800000 */
#define ETH_MACA3LR_ADDRLO_24               (0x1000000U << ETH_MACA3LR_ADDRLO_Pos)              /*!< 0x01000000 */
#define ETH_MACA3LR_ADDRLO_25               (0x2000000U << ETH_MACA3LR_ADDRLO_Pos)              /*!< 0x02000000 */
#define ETH_MACA3LR_ADDRLO_26               (0x4000000U << ETH_MACA3LR_ADDRLO_Pos)              /*!< 0x04000000 */
#define ETH_MACA3LR_ADDRLO_27               (0x8000000U << ETH_MACA3LR_ADDRLO_Pos)              /*!< 0x08000000 */
#define ETH_MACA3LR_ADDRLO_28               (0x10000000U << ETH_MACA3LR_ADDRLO_Pos)             /*!< 0x10000000 */
#define ETH_MACA3LR_ADDRLO_29               (0x20000000U << ETH_MACA3LR_ADDRLO_Pos)             /*!< 0x20000000 */
#define ETH_MACA3LR_ADDRLO_30               (0x40000000U << ETH_MACA3LR_ADDRLO_Pos)             /*!< 0x40000000 */
#define ETH_MACA3LR_ADDRLO_31               (0x80000000U << ETH_MACA3LR_ADDRLO_Pos)             /*!< 0x80000000 */

/************  Bit definition for ETH_MMC_CONTROL register  ************/
#define ETH_MMCCR_CNTRST_Pos                (0U)
#define ETH_MMCCR_CNTRST_Msk                (0x1U << ETH_MMCCR_CNTRST_Pos)                /*!< 0x00000001 */
#define ETH_MMCCR_CNTRST                    ETH_MMCCR_CNTRST_Msk                          /*!< Counters Reset */
#define ETH_MMCCR_CNTSTOPRO_Pos             (1U)
#define ETH_MMCCR_CNTSTOPRO_Msk             (0x1U << ETH_MMCCR_CNTSTOPRO_Pos)             /*!< 0x00000002 */
#define ETH_MMCCR_CNTSTOPRO                 ETH_MMCCR_CNTSTOPRO_Msk                       /*!< Counter Stop Rollover */
#define ETH_MMCCR_RSTONRD_Pos               (2U)
#define ETH_MMCCR_RSTONRD_Msk               (0x1U << ETH_MMCCR_RSTONRD_Pos)               /*!< 0x00000004 */
#define ETH_MMCCR_RSTONRD                   ETH_MMCCR_RSTONRD_Msk                         /*!< Reset on Read */
#define ETH_MMCCR_CNTFREEZ_Pos              (3U)
#define ETH_MMCCR_CNTFREEZ_Msk              (0x1U << ETH_MMCCR_CNTFREEZ_Pos)              /*!< 0x00000008 */
#define ETH_MMCCR_CNTFREEZ                  ETH_MMCCR_CNTFREEZ_Msk                        /*!< MMC Counter Freeze */
#define ETH_MMCCR_CNTPRST_Pos               (4U)
#define ETH_MMCCR_CNTPRST_Msk               (0x1U << ETH_MMCCR_CNTPRST_Pos)               /*!< 0x00000010 */
#define ETH_MMCCR_CNTPRST                   ETH_MMCCR_CNTPRST_Msk                         /*!< Counters Preset */
#define ETH_MMCCR_CNTPRSTLVL_Pos            (5U)
#define ETH_MMCCR_CNTPRSTLVL_Msk            (0x1U << ETH_MMCCR_CNTPRSTLVL_Pos)            /*!< 0x00000020 */
#define ETH_MMCCR_CNTPRSTLVL                ETH_MMCCR_CNTPRSTLVL_Msk                      /*!< Full-Half Preset */
#define ETH_MMCCR_UCDBC_Pos                 (8U)
#define ETH_MMCCR_UCDBC_Msk                 (0x1U << ETH_MMCCR_UCDBC_Pos)                 /*!< 0x00000100 */
#define ETH_MMCCR_UCDBC                     ETH_MMCCR_UCDBC_Msk                           /*!< Update MMC Counters for Dropped Broadcast Packets */

/***********  Bit definition for ETH_MMC_RX_INTERRUPT register  ************/
#define ETH_MMCRXIR_RXCRCERPIS_Pos          (5U)
#define ETH_MMCRXIR_RXCRCERPIS_Msk          (0x1U << ETH_MMCRXIR_RXCRCERPIS_Pos)         /*!< 0x00000020 */
#define ETH_MMCRXIR_RXCRCERPIS              ETH_MMCRXIR_RXCRCERPIS_Msk                   /*!< MMC Receive CRC Error Packet Counter Interrupt Status */
#define ETH_MMCRXIR_RXALGNERPIS_Pos         (6U)
#define ETH_MMCRXIR_RXALGNERPIS_Msk         (0x1U << ETH_MMCRXIR_RXALGNERPIS_Pos)        /*!< 0x00000040 */
#define ETH_MMCRXIR_RXALGNERPIS             ETH_MMCRXIR_RXALGNERPIS_Msk                  /*!< MMC Receive Alignment Error Packet Counter Interrupt Status */
#define ETH_MMCRXIR_RXUCGPIS_Pos            (17U)
#define ETH_MMCRXIR_RXUCGPIS_Msk            (0x1U << ETH_MMCRXIR_RXUCGPIS_Pos)           /*!< 0x00020000 */
#define ETH_MMCRXIR_RXUCGPIS                ETH_MMCRXIR_RXUCGPIS_Msk                     /*!< MMC Receive Unicast Good Packet Counter Interrupt Status */
#define ETH_MMCRXIR_RXLPIUSCIS_Pos          (26U)
#define ETH_MMCRXIR_RXLPIUSCIS_Msk          (0x1U << ETH_MMCRXIR_RXLPIUSCIS_Pos)         /*!< 0x04000000 */
#define ETH_MMCRXIR_RXLPIUSCIS              ETH_MMCRXIR_RXLPIUSCIS_Msk                   /*!< MMC Receive LPI microsecond counter interrupt status */
#define ETH_MMCRXIR_RXLPITRCIS_Pos          (27U)
#define ETH_MMCRXIR_RXLPITRCIS_Msk          (0x1U << ETH_MMCRXIR_RXLPITRCIS_Pos)         /*!< 0x08000000 */
#define ETH_MMCRXIR_RXLPITRCIS              ETH_MMCRXIR_RXLPITRCIS_Msk                   /*!< MMC Receive LPI transition counter interrupt status */

/***********  Bit definition for ETH_MMC_TX_INTERRUPT register  ************/
#define ETH_MMCTXIR_TXSCOLGPIS_Pos          (14U)
#define ETH_MMCTXIR_TXSCOLGPIS_Msk          (0x1U << ETH_MMCTXIR_TXSCOLGPIS_Pos)         /*!< 0x00004000 */
#define ETH_MMCTXIR_TXSCOLGPIS              ETH_MMCTXIR_TXSCOLGPIS_Msk                   /*!< MMC Transmit Single Collision Good Packet Counter Interrupt Status */
#define ETH_MMCTXIR_TXMCOLGPIS_Pos          (15U)
#define ETH_MMCTXIR_TXMCOLGPIS_Msk          (0x1U << ETH_MMCTXIR_TXMCOLGPIS_Pos)         /*!< 0x00008000 */
#define ETH_MMCTXIR_TXMCOLGPIS              ETH_MMCTXIR_TXMCOLGPIS_Msk                   /*!< MMC Transmit Multiple Collision Good Packet Counter Interrupt Status */
#define ETH_MMCTXIR_TXGPKTIS_Pos            (21U)
#define ETH_MMCTXIR_TXGPKTIS_Msk            (0x1U << ETH_MMCTXIR_TXGPKTIS_Pos)           /*!< 0x00200000 */
#define ETH_MMCTXIR_TXGPKTIS                ETH_MMCTXIR_TXGPKTIS_Msk                     /*!< MMC Transmit Good Packet Counter Interrupt Status */
#define ETH_MMCTXIR_TXLPIUSCIS_Pos          (26U)
#define ETH_MMCTXIR_TXLPIUSCIS_Msk          (0x1U << ETH_MMCTXIR_TXLPIUSCIS_Pos)         /*!< 0x04000000 */
#define ETH_MMCTXIR_TXLPIUSCIS              ETH_MMCTXIR_TXLPIUSCIS_Msk                   /*!< MMC Transmit LPI microsecond counter interrupt status */
#define ETH_MMCTXIR_TXLPITRCIS_Pos          (27U)
#define ETH_MMCTXIR_TXLPITRCIS_Msk          (0x1U << ETH_MMCTXIR_TXLPITRCIS_Pos)         /*!< 0x08000000 */
#define ETH_MMCTXIR_TXLPITRCIS              ETH_MMCTXIR_TXLPITRCIS_Msk                   /*!< MMC Transmit LPI transition counter interrupt status */

/**********  Bit definition for ETH_MMC_RX_INTERRUPT_MASK register  ***********/
#define ETH_MMCRXIMR_RXCRCERPIM_Pos         (5U)
#define ETH_MMCRXIMR_RXCRCERPIM_Msk         (0x1U << ETH_MMCRXIMR_RXCRCERPIM_Pos)         /*!< 0x00000020 */
#define ETH_MMCRXIMR_RXCRCERPIM             ETH_MMCRXIMR_RXCRCERPIM_Msk                   /*!< MMC Receive CRC Error Packet Counter Interrupt Mask */
#define ETH_MMCRXIMR_RXALGNERPIM_Pos        (6U)
#define ETH_MMCRXIMR_RXALGNERPIM_Msk        (0x1U << ETH_MMCRXIMR_RXALGNERPIM_Pos)        /*!< 0x00000040 */
#define ETH_MMCRXIMR_RXALGNERPIM            ETH_MMCRXIMR_RXALGNERPIM_Msk                  /*!< MMC Receive Alignment Error Packet Counter Interrupt Mask */
#define ETH_MMCRXIMR_RXUCGPIM_Pos           (17U)
#define ETH_MMCRXIMR_RXUCGPIM_Msk           (0x1U << ETH_MMCRXIMR_RXUCGPIM_Pos)           /*!< 0x00020000 */
#define ETH_MMCRXIMR_RXUCGPIM               ETH_MMCRXIMR_RXUCGPIM_Msk                     /*!< MMC Receive Unicast Good Packet Counter Interrupt Mask */
#define ETH_MMCRXIMR_RXLPIUSCIM_Pos         (26U)
#define ETH_MMCRXIMR_RXLPIUSCIM_Msk         (0x1U << ETH_MMCRXIMR_RXLPIUSCIM_Pos)         /*!< 0x04000000 */
#define ETH_MMCRXIMR_RXLPIUSCIM             ETH_MMCRXIMR_RXLPIUSCIM_Msk                   /*!< MMC Receive LPI microsecond counter interrupt Mask */
#define ETH_MMCRXIMR_RXLPITRCIM_Pos         (27U)
#define ETH_MMCRXIMR_RXLPITRCIM_Msk         (0x1U << ETH_MMCRXIMR_RXLPITRCIM_Pos)         /*!< 0x08000000 */
#define ETH_MMCRXIMR_RXLPITRCIM             ETH_MMCRXIMR_RXLPITRCIM_Msk                   /*!< MMC Receive LPI transition counter interrupt Mask */

/**********  Bit definition for ETH_MMC_TX_INTERRUPT_MASK register  ***********/
#define ETH_MMCTXIMR_TXSCOLGPIM_Pos         (14U)
#define ETH_MMCTXIMR_TXSCOLGPIM_Msk         (0x1U << ETH_MMCTXIMR_TXSCOLGPIM_Pos)        /*!< 0x00004000 */
#define ETH_MMCTXIMR_TXSCOLGPIM             ETH_MMCTXIMR_TXSCOLGPIM_Msk                  /*!< MMC Transmit Single Collision Good Packet Counter Interrupt Mask */
#define ETH_MMCTXIMR_TXMCOLGPIM_Pos         (15U)
#define ETH_MMCTXIMR_TXMCOLGPIM_Msk         (0x1U << ETH_MMCTXIMR_TXMCOLGPIM_Pos)        /*!< 0x00008000 */
#define ETH_MMCTXIMR_TXMCOLGPIM             ETH_MMCTXIMR_TXMCOLGPIM_Msk                  /*!< MMC Transmit Multiple Collision Good Packet Counter Interrupt Mask */
#define ETH_MMCTXIMR_TXGPKTIM_Pos           (21U)
#define ETH_MMCTXIMR_TXGPKTIM_Msk           (0x1U << ETH_MMCTXIMR_TXGPKTIM_Pos)          /*!< 0x00200000 */
#define ETH_MMCTXIMR_TXGPKTIM               ETH_MMCTXIMR_TXGPKTIM_Msk                    /*!< MMC Transmit Good Packet Counter Interrupt Mask */
#define ETH_MMCTXIMR_TXLPIUSCIM_Pos         (26U)
#define ETH_MMCTXIMR_TXLPIUSCIM_Msk         (0x1U << ETH_MMCTXIMR_TXLPIUSCIM_Pos)        /*!< 0x04000000 */
#define ETH_MMCTXIMR_TXLPIUSCIM             ETH_MMCTXIMR_TXLPIUSCIM_Msk                  /*!< MMC Transmit LPI microsecond counter interrupt Mask */
#define ETH_MMCTXIMR_TXLPITRCIM_Pos         (27U)
#define ETH_MMCTXIMR_TXLPITRCIM_Msk         (0x1U << ETH_MMCTXIMR_TXLPITRCIM_Pos)        /*!< 0x08000000 */
#define ETH_MMCTXIMR_TXLPITRCIM             ETH_MMC_INTERRUPT_MASK_TXLPITRCIM_Msk                  /*!< MMC Transmit LPI transition counter interrupt Mask */

/***********  Bit definition for ETH_MMC_TX_SINGLE_COLLISION_GOOD_PACKETS register  ************/
#define ETH_MMCTXSCGPR_TXSNGLCOLG_Pos       (0U)
#define ETH_MMCTXSCGPR_TXSNGLCOLG_Msk       (0xFFFFFFFFU << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos) /*!< 0xFFFFFFFF */
#define ETH_MMCTXSCGPR_TXSNGLCOLG           ETH_MMCTXSCGPR_TXSNGLCOLG_Msk                  /*!< Tx Single Collision Good Packets */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_0         (0x1U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)        /*!< 0x00000001 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_1         (0x2U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)        /*!< 0x00000002 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_2         (0x4U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)        /*!< 0x00000004 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_3         (0x8U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)        /*!< 0x00000008 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_4         (0x10U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)       /*!< 0x00000010 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_5         (0x20U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)       /*!< 0x00000020 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_6         (0x40U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)       /*!< 0x00000040 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_7         (0x80U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)       /*!< 0x00000080 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_8         (0x100U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)      /*!< 0x00000100 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_9         (0x200U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)      /*!< 0x00000200 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_10        (0x400U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)      /*!< 0x00000400 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_11        (0x800U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)      /*!< 0x00000800 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_12        (0x1000U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)     /*!< 0x00001000 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_13        (0x2000U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)     /*!< 0x00002000 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_14        (0x4000U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)     /*!< 0x00004000 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_15        (0x8000U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)     /*!< 0x00008000 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_16        (0x10000U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)    /*!< 0x00010000 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_17        (0x20000U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)    /*!< 0x00020000 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_18        (0x40000U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)    /*!< 0x00040000 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_19        (0x80000U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)    /*!< 0x00080000 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_20        (0x100000U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)   /*!< 0x00100000 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_21        (0x200000U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)   /*!< 0x00200000 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_22        (0x400000U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)   /*!< 0x00400000 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_23        (0x800000U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)   /*!< 0x00800000 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_24        (0x1000000U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)  /*!< 0x01000000 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_25        (0x2000000U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)  /*!< 0x02000000 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_26        (0x4000000U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)  /*!< 0x04000000 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_27        (0x8000000U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos)  /*!< 0x08000000 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_28        (0x10000000U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos) /*!< 0x10000000 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_29        (0x20000000U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos) /*!< 0x20000000 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_30        (0x40000000U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos) /*!< 0x40000000 */
#define ETH_MMCTXSCGPR_TXSNGLCOLG_31        (0x80000000U << ETH_MMCTXSCGPR_TXSNGLCOLG_Pos) /*!< 0x80000000 */

/***********  Bit definition for ETH_MMC_TX_MULTIPLE_COLLISION_GOOD_PACKETS register  ************/
#define ETH_MMCTXMCGPR_TXMULTCOLG_Pos       (0U)
#define ETH_MMCTXMCGPR_TXMULTCOLG_Msk       (0xFFFFFFFFU << ETH_MMCTXMCGPR_TXMULTCOLG_Pos) /*!< 0xFFFFFFFF */
#define ETH_MMCTXMCGPR_TXMULTCOLG           ETH_MMCTXMCGPR_TXMULTCOLG_Msk                  /*!< Tx Multiple Collision Good Packets */
#define ETH_MMCTXMCGPR_TXMULTCOLG_0         (0x1U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)        /*!< 0x00000001 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_1         (0x2U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)        /*!< 0x00000002 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_2         (0x4U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)        /*!< 0x00000004 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_3         (0x8U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)        /*!< 0x00000008 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_4         (0x10U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)       /*!< 0x00000010 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_5         (0x20U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)       /*!< 0x00000020 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_6         (0x40U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)       /*!< 0x00000040 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_7         (0x80U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)       /*!< 0x00000080 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_8         (0x100U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)      /*!< 0x00000100 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_9         (0x200U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)      /*!< 0x00000200 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_10        (0x400U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)      /*!< 0x00000400 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_11        (0x800U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)      /*!< 0x00000800 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_12        (0x1000U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)     /*!< 0x00001000 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_13        (0x2000U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)     /*!< 0x00002000 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_14        (0x4000U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)     /*!< 0x00004000 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_15        (0x8000U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)     /*!< 0x00008000 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_16        (0x10000U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)    /*!< 0x00010000 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_17        (0x20000U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)    /*!< 0x00020000 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_18        (0x40000U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)    /*!< 0x00040000 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_19        (0x80000U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)    /*!< 0x00080000 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_20        (0x100000U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)   /*!< 0x00100000 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_21        (0x200000U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)   /*!< 0x00200000 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_22        (0x400000U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)   /*!< 0x00400000 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_23        (0x800000U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)   /*!< 0x00800000 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_24        (0x1000000U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)  /*!< 0x01000000 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_25        (0x2000000U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)  /*!< 0x02000000 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_26        (0x4000000U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)  /*!< 0x04000000 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_27        (0x8000000U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos)  /*!< 0x08000000 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_28        (0x10000000U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos) /*!< 0x10000000 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_29        (0x20000000U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos) /*!< 0x20000000 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_30        (0x40000000U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos) /*!< 0x40000000 */
#define ETH_MMCTXMCGPR_TXMULTCOLG_31        (0x80000000U << ETH_MMCTXMCGPR_TXMULTCOLG_Pos) /*!< 0x80000000 */

/************  Bit definition for ETH_MMC_TX_PACKET_COUNT_GOOD register  *************/
#define ETH_MMCTXPCGR_TXPKTG_Pos            (0U)
#define ETH_MMCTXPCGR_TXPKTG_Msk            (0xFFFFFFFFU << ETH_MMCTXPCGR_TXPKTG_Pos) /*!< 0xFFFFFFFF */
#define ETH_MMCTXPCGR_TXPKTG                ETH_MMCTXPCGR_TXPKTG_Msk                  /*!< Tx Packet Count Good */
#define ETH_MMCTXPCGR_TXPKTG_0              (0x1U << ETH_MMCTXPCGR_TXPKTG_Pos)        /*!< 0x00000001 */
#define ETH_MMCTXPCGR_TXPKTG_1              (0x2U << ETH_MMCTXPCGR_TXPKTG_Pos)        /*!< 0x00000002 */
#define ETH_MMCTXPCGR_TXPKTG_2              (0x4U << ETH_MMCTXPCGR_TXPKTG_Pos)        /*!< 0x00000004 */
#define ETH_MMCTXPCGR_TXPKTG_3              (0x8U << ETH_MMCTXPCGR_TXPKTG_Pos)        /*!< 0x00000008 */
#define ETH_MMCTXPCGR_TXPKTG_4              (0x10U << ETH_MMCTXPCGR_TXPKTG_Pos)       /*!< 0x00000010 */
#define ETH_MMCTXPCGR_TXPKTG_5              (0x20U << ETH_MMCTXPCGR_TXPKTG_Pos)       /*!< 0x00000020 */
#define ETH_MMCTXPCGR_TXPKTG_6              (0x40U << ETH_MMCTXPCGR_TXPKTG_Pos)       /*!< 0x00000040 */
#define ETH_MMCTXPCGR_TXPKTG_7              (0x80U << ETH_MMCTXPCGR_TXPKTG_Pos)       /*!< 0x00000080 */
#define ETH_MMCTXPCGR_TXPKTG_8              (0x100U << ETH_MMCTXPCGR_TXPKTG_Pos)      /*!< 0x00000100 */
#define ETH_MMCTXPCGR_TXPKTG_9              (0x200U << ETH_MMCTXPCGR_TXPKTG_Pos)      /*!< 0x00000200 */
#define ETH_MMCTXPCGR_TXPKTG_10             (0x400U << ETH_MMCTXPCGR_TXPKTG_Pos)      /*!< 0x00000400 */
#define ETH_MMCTXPCGR_TXPKTG_11             (0x800U << ETH_MMCTXPCGR_TXPKTG_Pos)      /*!< 0x00000800 */
#define ETH_MMCTXPCGR_TXPKTG_12             (0x1000U << ETH_MMCTXPCGR_TXPKTG_Pos)     /*!< 0x00001000 */
#define ETH_MMCTXPCGR_TXPKTG_13             (0x2000U << ETH_MMCTXPCGR_TXPKTG_Pos)     /*!< 0x00002000 */
#define ETH_MMCTXPCGR_TXPKTG_14             (0x4000U << ETH_MMCTXPCGR_TXPKTG_Pos)     /*!< 0x00004000 */
#define ETH_MMCTXPCGR_TXPKTG_15             (0x8000U << ETH_MMCTXPCGR_TXPKTG_Pos)     /*!< 0x00008000 */
#define ETH_MMCTXPCGR_TXPKTG_16             (0x10000U << ETH_MMCTXPCGR_TXPKTG_Pos)    /*!< 0x00010000 */
#define ETH_MMCTXPCGR_TXPKTG_17             (0x20000U << ETH_MMCTXPCGR_TXPKTG_Pos)    /*!< 0x00020000 */
#define ETH_MMCTXPCGR_TXPKTG_18             (0x40000U << ETH_MMCTXPCGR_TXPKTG_Pos)    /*!< 0x00040000 */
#define ETH_MMCTXPCGR_TXPKTG_19             (0x80000U << ETH_MMCTXPCGR_TXPKTG_Pos)    /*!< 0x00080000 */
#define ETH_MMCTXPCGR_TXPKTG_20             (0x100000U << ETH_MMCTXPCGR_TXPKTG_Pos)   /*!< 0x00100000 */
#define ETH_MMCTXPCGR_TXPKTG_21             (0x200000U << ETH_MMCTXPCGR_TXPKTG_Pos)   /*!< 0x00200000 */
#define ETH_MMCTXPCGR_TXPKTG_22             (0x400000U << ETH_MMCTXPCGR_TXPKTG_Pos)   /*!< 0x00400000 */
#define ETH_MMCTXPCGR_TXPKTG_23             (0x800000U << ETH_MMCTXPCGR_TXPKTG_Pos)   /*!< 0x00800000 */
#define ETH_MMCTXPCGR_TXPKTG_24             (0x1000000U << ETH_MMCTXPCGR_TXPKTG_Pos)  /*!< 0x01000000 */
#define ETH_MMCTXPCGR_TXPKTG_25             (0x2000000U << ETH_MMCTXPCGR_TXPKTG_Pos)  /*!< 0x02000000 */
#define ETH_MMCTXPCGR_TXPKTG_26             (0x4000000U << ETH_MMCTXPCGR_TXPKTG_Pos)  /*!< 0x04000000 */
#define ETH_MMCTXPCGR_TXPKTG_27             (0x8000000U << ETH_MMCTXPCGR_TXPKTG_Pos)  /*!< 0x08000000 */
#define ETH_MMCTXPCGR_TXPKTG_28             (0x10000000U << ETH_MMCTXPCGR_TXPKTG_Pos) /*!< 0x10000000 */
#define ETH_MMCTXPCGR_TXPKTG_29             (0x20000000U << ETH_MMCTXPCGR_TXPKTG_Pos) /*!< 0x20000000 */
#define ETH_MMCTXPCGR_TXPKTG_30             (0x40000000U << ETH_MMCTXPCGR_TXPKTG_Pos) /*!< 0x40000000 */
#define ETH_MMCTXPCGR_TXPKTG_31             (0x80000000U << ETH_MMCTXPCGR_TXPKTG_Pos) /*!< 0x80000000 */

/***********  Bit definition for ETH_MMC_RX_CRC_ERROR_PACKETS register  ***********/
#define ETH_MMCRXCRCEPR_RXCRCERR_Pos        (0U)
#define ETH_MMCRXCRCEPR_RXCRCERR_Msk        (0xFFFFFFFFU << ETH_MMCRXCRCEPR_RXCRCERR_Pos) /*!< 0xFFFFFFFF */
#define ETH_MMCRXCRCEPR_RXCRCERR            ETH_MMCRXCRCEPR_RXCRCERR_Msk                  /*!< Rx CRC Error Packets */
#define ETH_MMCRXCRCEPR_RXCRCERR_0          (0x1U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)        /*!< 0x00000001 */
#define ETH_MMCRXCRCEPR_RXCRCERR_1          (0x2U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)        /*!< 0x00000002 */
#define ETH_MMCRXCRCEPR_RXCRCERR_2          (0x4U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)        /*!< 0x00000004 */
#define ETH_MMCRXCRCEPR_RXCRCERR_3          (0x8U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)        /*!< 0x00000008 */
#define ETH_MMCRXCRCEPR_RXCRCERR_4          (0x10U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)       /*!< 0x00000010 */
#define ETH_MMCRXCRCEPR_RXCRCERR_5          (0x20U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)       /*!< 0x00000020 */
#define ETH_MMCRXCRCEPR_RXCRCERR_6          (0x40U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)       /*!< 0x00000040 */
#define ETH_MMCRXCRCEPR_RXCRCERR_7          (0x80U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)       /*!< 0x00000080 */
#define ETH_MMCRXCRCEPR_RXCRCERR_8          (0x100U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)      /*!< 0x00000100 */
#define ETH_MMCRXCRCEPR_RXCRCERR_9          (0x200U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)      /*!< 0x00000200 */
#define ETH_MMCRXCRCEPR_RXCRCERR_10         (0x400U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)      /*!< 0x00000400 */
#define ETH_MMCRXCRCEPR_RXCRCERR_11         (0x800U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)      /*!< 0x00000800 */
#define ETH_MMCRXCRCEPR_RXCRCERR_12         (0x1000U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)     /*!< 0x00001000 */
#define ETH_MMCRXCRCEPR_RXCRCERR_13         (0x2000U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)     /*!< 0x00002000 */
#define ETH_MMCRXCRCEPR_RXCRCERR_14         (0x4000U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)     /*!< 0x00004000 */
#define ETH_MMCRXCRCEPR_RXCRCERR_15         (0x8000U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)     /*!< 0x00008000 */
#define ETH_MMCRXCRCEPR_RXCRCERR_16         (0x10000U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)    /*!< 0x00010000 */
#define ETH_MMCRXCRCEPR_RXCRCERR_17         (0x20000U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)    /*!< 0x00020000 */
#define ETH_MMCRXCRCEPR_RXCRCERR_18         (0x40000U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)    /*!< 0x00040000 */
#define ETH_MMCRXCRCEPR_RXCRCERR_19         (0x80000U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)    /*!< 0x00080000 */
#define ETH_MMCRXCRCEPR_RXCRCERR_20         (0x100000U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)   /*!< 0x00100000 */
#define ETH_MMCRXCRCEPR_RXCRCERR_21         (0x200000U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)   /*!< 0x00200000 */
#define ETH_MMCRXCRCEPR_RXCRCERR_22         (0x400000U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)   /*!< 0x00400000 */
#define ETH_MMCRXCRCEPR_RXCRCERR_23         (0x800000U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)   /*!< 0x00800000 */
#define ETH_MMCRXCRCEPR_RXCRCERR_24         (0x1000000U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)  /*!< 0x01000000 */
#define ETH_MMCRXCRCEPR_RXCRCERR_25         (0x2000000U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)  /*!< 0x02000000 */
#define ETH_MMCRXCRCEPR_RXCRCERR_26         (0x4000000U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)  /*!< 0x04000000 */
#define ETH_MMCRXCRCEPR_RXCRCERR_27         (0x8000000U << ETH_MMCRXCRCEPR_RXCRCERR_Pos)  /*!< 0x08000000 */
#define ETH_MMCRXCRCEPR_RXCRCERR_28         (0x10000000U << ETH_MMCRXCRCEPR_RXCRCERR_Pos) /*!< 0x10000000 */
#define ETH_MMCRXCRCEPR_RXCRCERR_29         (0x20000000U << ETH_MMCRXCRCEPR_RXCRCERR_Pos) /*!< 0x20000000 */
#define ETH_MMCRXCRCEPR_RXCRCERR_30         (0x40000000U << ETH_MMCRXCRCEPR_RXCRCERR_Pos) /*!< 0x40000000 */
#define ETH_MMCRXCRCEPR_RXCRCERR_31         (0x80000000U << ETH_MMCRXCRCEPR_RXCRCERR_Pos) /*!< 0x80000000 */

/***********  Bit definition for ETH_MMC_RX_ALIGNMENT_ERROR_PACKETS register  ***********/
#define ETH_MMCRXAEPR_RXALGNERR_Pos         (0U)
#define ETH_MMCRXAEPR_RXALGNERR_Msk         (0xFFFFFFFFU << ETH_MMCRXAEPR_RXALGNERR_Pos) /*!< 0xFFFFFFFF */
#define ETH_MMCRXAEPR_RXALGNERR             ETH_MMCRXAEPR_RXALGNERR_Msk                  /*!< Rx Alignment Error Packets */
#define ETH_MMCRXAEPR_RXALGNERR_0           (0x1U << ETH_MMCRXAEPR_RXALGNERR_Pos)        /*!< 0x00000001 */
#define ETH_MMCRXAEPR_RXALGNERR_1           (0x2U << ETH_MMCRXAEPR_RXALGNERR_Pos)        /*!< 0x00000002 */
#define ETH_MMCRXAEPR_RXALGNERR_2           (0x4U << ETH_MMCRXAEPR_RXALGNERR_Pos)        /*!< 0x00000004 */
#define ETH_MMCRXAEPR_RXALGNERR_3           (0x8U << ETH_MMCRXAEPR_RXALGNERR_Pos)        /*!< 0x00000008 */
#define ETH_MMCRXAEPR_RXALGNERR_4           (0x10U << ETH_MMCRXAEPR_RXALGNERR_Pos)       /*!< 0x00000010 */
#define ETH_MMCRXAEPR_RXALGNERR_5           (0x20U << ETH_MMCRXAEPR_RXALGNERR_Pos)       /*!< 0x00000020 */
#define ETH_MMCRXAEPR_RXALGNERR_6           (0x40U << ETH_MMCRXAEPR_RXALGNERR_Pos)       /*!< 0x00000040 */
#define ETH_MMCRXAEPR_RXALGNERR_7           (0x80U << ETH_MMCRXAEPR_RXALGNERR_Pos)       /*!< 0x00000080 */
#define ETH_MMCRXAEPR_RXALGNERR_8           (0x100U << ETH_MMCRXAEPR_RXALGNERR_Pos)      /*!< 0x00000100 */
#define ETH_MMCRXAEPR_RXALGNERR_9           (0x200U << ETH_MMCRXAEPR_RXALGNERR_Pos)      /*!< 0x00000200 */
#define ETH_MMCRXAEPR_RXALGNERR_10          (0x400U << ETH_MMCRXAEPR_RXALGNERR_Pos)      /*!< 0x00000400 */
#define ETH_MMCRXAEPR_RXALGNERR_11          (0x800U << ETH_MMCRXAEPR_RXALGNERR_Pos)      /*!< 0x00000800 */
#define ETH_MMCRXAEPR_RXALGNERR_12          (0x1000U << ETH_MMCRXAEPR_RXALGNERR_Pos)     /*!< 0x00001000 */
#define ETH_MMCRXAEPR_RXALGNERR_13          (0x2000U << ETH_MMCRXAEPR_RXALGNERR_Pos)     /*!< 0x00002000 */
#define ETH_MMCRXAEPR_RXALGNERR_14          (0x4000U << ETH_MMCRXAEPR_RXALGNERR_Pos)     /*!< 0x00004000 */
#define ETH_MMCRXAEPR_RXALGNERR_15          (0x8000U << ETH_MMCRXAEPR_RXALGNERR_Pos)     /*!< 0x00008000 */
#define ETH_MMCRXAEPR_RXALGNERR_16          (0x10000U << ETH_MMCRXAEPR_RXALGNERR_Pos)    /*!< 0x00010000 */
#define ETH_MMCRXAEPR_RXALGNERR_17          (0x20000U << ETH_MMCRXAEPR_RXALGNERR_Pos)    /*!< 0x00020000 */
#define ETH_MMCRXAEPR_RXALGNERR_18          (0x40000U << ETH_MMCRXAEPR_RXALGNERR_Pos)    /*!< 0x00040000 */
#define ETH_MMCRXAEPR_RXALGNERR_19          (0x80000U << ETH_MMCRXAEPR_RXALGNERR_Pos)    /*!< 0x00080000 */
#define ETH_MMCRXAEPR_RXALGNERR_20          (0x100000U << ETH_MMCRXAEPR_RXALGNERR_Pos)   /*!< 0x00100000 */
#define ETH_MMCRXAEPR_RXALGNERR_21          (0x200000U << ETH_MMCRXAEPR_RXALGNERR_Pos)   /*!< 0x00200000 */
#define ETH_MMCRXAEPR_RXALGNERR_22          (0x400000U << ETH_MMCRXAEPR_RXALGNERR_Pos)   /*!< 0x00400000 */
#define ETH_MMCRXAEPR_RXALGNERR_23          (0x800000U << ETH_MMCRXAEPR_RXALGNERR_Pos)   /*!< 0x00800000 */
#define ETH_MMCRXAEPR_RXALGNERR_24          (0x1000000U << ETH_MMCRXAEPR_RXALGNERR_Pos)  /*!< 0x01000000 */
#define ETH_MMCRXAEPR_RXALGNERR_25          (0x2000000U << ETH_MMCRXAEPR_RXALGNERR_Pos)  /*!< 0x02000000 */
#define ETH_MMCRXAEPR_RXALGNERR_26          (0x4000000U << ETH_MMCRXAEPR_RXALGNERR_Pos)  /*!< 0x04000000 */
#define ETH_MMCRXAEPR_RXALGNERR_27          (0x8000000U << ETH_MMCRXAEPR_RXALGNERR_Pos)  /*!< 0x08000000 */
#define ETH_MMCRXAEPR_RXALGNERR_28          (0x10000000U << ETH_MMCRXAEPR_RXALGNERR_Pos) /*!< 0x10000000 */
#define ETH_MMCRXAEPR_RXALGNERR_29          (0x20000000U << ETH_MMCRXAEPR_RXALGNERR_Pos) /*!< 0x20000000 */
#define ETH_MMCRXAEPR_RXALGNERR_30          (0x40000000U << ETH_MMCRXAEPR_RXALGNERR_Pos) /*!< 0x40000000 */
#define ETH_MMCRXAEPR_RXALGNERR_31          (0x80000000U << ETH_MMCRXAEPR_RXALGNERR_Pos) /*!< 0x80000000 */

/***********  Bit definition for ETH_MMC_RX_UNICAST_PACKETS_GOOD register  ************/
#define ETH_MMCRXUPGR_RXUCASTG_Pos          (0U)
#define ETH_MMCRXUPGR_RXUCASTG_Msk          (0xFFFFFFFFU << ETH_MMCRXUPGR_RXUCASTG_Pos) /*!< 0xFFFFFFFF */
#define ETH_MMCRXUPGR_RXUCASTG              ETH_MMCRXUPGR_RXUCASTG_Msk                  /*!< Rx Unicast Packets Good */
#define ETH_MMCRXUPGR_RXUCASTG_0            (0x1U << ETH_MMCRXUPGR_RXUCASTG_Pos)        /*!< 0x00000001 */
#define ETH_MMCRXUPGR_RXUCASTG_1            (0x2U << ETH_MMCRXUPGR_RXUCASTG_Pos)        /*!< 0x00000002 */
#define ETH_MMCRXUPGR_RXUCASTG_2            (0x4U << ETH_MMCRXUPGR_RXUCASTG_Pos)        /*!< 0x00000004 */
#define ETH_MMCRXUPGR_RXUCASTG_3            (0x8U << ETH_MMCRXUPGR_RXUCASTG_Pos)        /*!< 0x00000008 */
#define ETH_MMCRXUPGR_RXUCASTG_4            (0x10U << ETH_MMCRXUPGR_RXUCASTG_Pos)       /*!< 0x00000010 */
#define ETH_MMCRXUPGR_RXUCASTG_5            (0x20U << ETH_MMCRXUPGR_RXUCASTG_Pos)       /*!< 0x00000020 */
#define ETH_MMCRXUPGR_RXUCASTG_6            (0x40U << ETH_MMCRXUPGR_RXUCASTG_Pos)       /*!< 0x00000040 */
#define ETH_MMCRXUPGR_RXUCASTG_7            (0x80U << ETH_MMCRXUPGR_RXUCASTG_Pos)       /*!< 0x00000080 */
#define ETH_MMCRXUPGR_RXUCASTG_8            (0x100U << ETH_MMCRXUPGR_RXUCASTG_Pos)      /*!< 0x00000100 */
#define ETH_MMCRXUPGR_RXUCASTG_9            (0x200U << ETH_MMCRXUPGR_RXUCASTG_Pos)      /*!< 0x00000200 */
#define ETH_MMCRXUPGR_RXUCASTG_10           (0x400U << ETH_MMCRXUPGR_RXUCASTG_Pos)      /*!< 0x00000400 */
#define ETH_MMCRXUPGR_RXUCASTG_11           (0x800U << ETH_MMCRXUPGR_RXUCASTG_Pos)      /*!< 0x00000800 */
#define ETH_MMCRXUPGR_RXUCASTG_12           (0x1000U << ETH_MMCRXUPGR_RXUCASTG_Pos)     /*!< 0x00001000 */
#define ETH_MMCRXUPGR_RXUCASTG_13           (0x2000U << ETH_MMCRXUPGR_RXUCASTG_Pos)     /*!< 0x00002000 */
#define ETH_MMCRXUPGR_RXUCASTG_14           (0x4000U << ETH_MMCRXUPGR_RXUCASTG_Pos)     /*!< 0x00004000 */
#define ETH_MMCRXUPGR_RXUCASTG_15           (0x8000U << ETH_MMCRXUPGR_RXUCASTG_Pos)     /*!< 0x00008000 */
#define ETH_MMCRXUPGR_RXUCASTG_16           (0x10000U << ETH_MMCRXUPGR_RXUCASTG_Pos)    /*!< 0x00010000 */
#define ETH_MMCRXUPGR_RXUCASTG_17           (0x20000U << ETH_MMCRXUPGR_RXUCASTG_Pos)    /*!< 0x00020000 */
#define ETH_MMCRXUPGR_RXUCASTG_18           (0x40000U << ETH_MMCRXUPGR_RXUCASTG_Pos)    /*!< 0x00040000 */
#define ETH_MMCRXUPGR_RXUCASTG_19           (0x80000U << ETH_MMCRXUPGR_RXUCASTG_Pos)    /*!< 0x00080000 */
#define ETH_MMCRXUPGR_RXUCASTG_20           (0x100000U << ETH_MMCRXUPGR_RXUCASTG_Pos)   /*!< 0x00100000 */
#define ETH_MMCRXUPGR_RXUCASTG_21           (0x200000U << ETH_MMCRXUPGR_RXUCASTG_Pos)   /*!< 0x00200000 */
#define ETH_MMCRXUPGR_RXUCASTG_22           (0x400000U << ETH_MMCRXUPGR_RXUCASTG_Pos)   /*!< 0x00400000 */
#define ETH_MMCRXUPGR_RXUCASTG_23           (0x800000U << ETH_MMCRXUPGR_RXUCASTG_Pos)   /*!< 0x00800000 */
#define ETH_MMCRXUPGR_RXUCASTG_24           (0x1000000U << ETH_MMCRXUPGR_RXUCASTG_Pos)  /*!< 0x01000000 */
#define ETH_MMCRXUPGR_RXUCASTG_25           (0x2000000U << ETH_MMCRXUPGR_RXUCASTG_Pos)  /*!< 0x02000000 */
#define ETH_MMCRXUPGR_RXUCASTG_26           (0x4000000U << ETH_MMCRXUPGR_RXUCASTG_Pos)  /*!< 0x04000000 */
#define ETH_MMCRXUPGR_RXUCASTG_27           (0x8000000U << ETH_MMCRXUPGR_RXUCASTG_Pos)  /*!< 0x08000000 */
#define ETH_MMCRXUPGR_RXUCASTG_28           (0x10000000U << ETH_MMCRXUPGR_RXUCASTG_Pos) /*!< 0x10000000 */
#define ETH_MMCRXUPGR_RXUCASTG_29           (0x20000000U << ETH_MMCRXUPGR_RXUCASTG_Pos) /*!< 0x20000000 */
#define ETH_MMCRXUPGR_RXUCASTG_30           (0x40000000U << ETH_MMCRXUPGR_RXUCASTG_Pos) /*!< 0x40000000 */
#define ETH_MMCRXUPGR_RXUCASTG_31           (0x80000000U << ETH_MMCRXUPGR_RXUCASTG_Pos) /*!< 0x80000000 */

/*************  Bit definition for ETH_MMC_TX_LPI_USEC_CNTR register  *************/
#define ETH_MMCTXLPIMSTR_TXLPIUSC_Pos       (0U)
#define ETH_MMCTXLPIMSTR_TXLPIUSC_Msk       (0xFFFFFFFFU << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos) /*!< 0xFFFFFFFF */
#define ETH_MMCTXLPIMSTR_TXLPIUSC           ETH_MMCTXLPIMSTR_TXLPIUSC_Msk                  /*!< Tx LPI Microseconds Counter */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_0         (0x1U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)        /*!< 0x00000001 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_1         (0x2U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)        /*!< 0x00000002 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_2         (0x4U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)        /*!< 0x00000004 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_3         (0x8U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)        /*!< 0x00000008 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_4         (0x10U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)       /*!< 0x00000010 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_5         (0x20U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)       /*!< 0x00000020 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_6         (0x40U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)       /*!< 0x00000040 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_7         (0x80U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)       /*!< 0x00000080 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_8         (0x100U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)      /*!< 0x00000100 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_9         (0x200U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)      /*!< 0x00000200 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_10        (0x400U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)      /*!< 0x00000400 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_11        (0x800U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)      /*!< 0x00000800 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_12        (0x1000U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)     /*!< 0x00001000 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_13        (0x2000U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)     /*!< 0x00002000 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_14        (0x4000U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)     /*!< 0x00004000 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_15        (0x8000U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)     /*!< 0x00008000 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_16        (0x10000U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)    /*!< 0x00010000 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_17        (0x20000U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)    /*!< 0x00020000 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_18        (0x40000U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)    /*!< 0x00040000 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_19        (0x80000U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)    /*!< 0x00080000 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_20        (0x100000U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)   /*!< 0x00100000 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_21        (0x200000U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)   /*!< 0x00200000 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_22        (0x400000U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)   /*!< 0x00400000 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_23        (0x800000U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)   /*!< 0x00800000 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_24        (0x1000000U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)  /*!< 0x01000000 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_25        (0x2000000U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)  /*!< 0x02000000 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_26        (0x4000000U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)  /*!< 0x04000000 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_27        (0x8000000U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos)  /*!< 0x08000000 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_28        (0x10000000U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos) /*!< 0x10000000 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_29        (0x20000000U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos) /*!< 0x20000000 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_30        (0x40000000U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos) /*!< 0x40000000 */
#define ETH_MMCTXLPIMSTR_TXLPIUSC_31        (0x80000000U << ETH_MMCTXLPIMSTR_TXLPIUSC_Pos) /*!< 0x80000000 */

/*************  Bit definition for ETH_MMC_TX_LPI_TRAN_CNTR register  *************/
#define ETH_MMCTXLPITCR_TXLPITRC_Pos        (0U)
#define ETH_MMCTXLPITCR_TXLPITRC_Msk        (0xFFFFFFFFU << ETH_MMCTXLPITCR_TXLPITRC_Pos) /*!< 0xFFFFFFFF */
#define ETH_MMCTXLPITCR_TXLPITRC            ETH_MMCTXLPITCR_TXLPITRC_Msk                  /*!< Tx LPI Transition counter */
#define ETH_MMCTXLPITCR_TXLPITRC_0          (0x1U << ETH_MMCTXLPITCR_TXLPITRC_Pos)        /*!< 0x00000001 */
#define ETH_MMCTXLPITCR_TXLPITRC_1          (0x2U << ETH_MMCTXLPITCR_TXLPITRC_Pos)        /*!< 0x00000002 */
#define ETH_MMCTXLPITCR_TXLPITRC_2          (0x4U << ETH_MMCTXLPITCR_TXLPITRC_Pos)        /*!< 0x00000004 */
#define ETH_MMCTXLPITCR_TXLPITRC_3          (0x8U << ETH_MMCTXLPITCR_TXLPITRC_Pos)        /*!< 0x00000008 */
#define ETH_MMCTXLPITCR_TXLPITRC_4          (0x10U << ETH_MMCTXLPITCR_TXLPITRC_Pos)       /*!< 0x00000010 */
#define ETH_MMCTXLPITCR_TXLPITRC_5          (0x20U << ETH_MMCTXLPITCR_TXLPITRC_Pos)       /*!< 0x00000020 */
#define ETH_MMCTXLPITCR_TXLPITRC_6          (0x40U << ETH_MMCTXLPITCR_TXLPITRC_Pos)       /*!< 0x00000040 */
#define ETH_MMCTXLPITCR_TXLPITRC_7          (0x80U << ETH_MMCTXLPITCR_TXLPITRC_Pos)       /*!< 0x00000080 */
#define ETH_MMCTXLPITCR_TXLPITRC_8          (0x100U << ETH_MMCTXLPITCR_TXLPITRC_Pos)      /*!< 0x00000100 */
#define ETH_MMCTXLPITCR_TXLPITRC_9          (0x200U << ETH_MMCTXLPITCR_TXLPITRC_Pos)      /*!< 0x00000200 */
#define ETH_MMCTXLPITCR_TXLPITRC_10         (0x400U << ETH_MMCTXLPITCR_TXLPITRC_Pos)      /*!< 0x00000400 */
#define ETH_MMCTXLPITCR_TXLPITRC_11         (0x800U << ETH_MMCTXLPITCR_TXLPITRC_Pos)      /*!< 0x00000800 */
#define ETH_MMCTXLPITCR_TXLPITRC_12         (0x1000U << ETH_MMCTXLPITCR_TXLPITRC_Pos)     /*!< 0x00001000 */
#define ETH_MMCTXLPITCR_TXLPITRC_13         (0x2000U << ETH_MMCTXLPITCR_TXLPITRC_Pos)     /*!< 0x00002000 */
#define ETH_MMCTXLPITCR_TXLPITRC_14         (0x4000U << ETH_MMCTXLPITCR_TXLPITRC_Pos)     /*!< 0x00004000 */
#define ETH_MMCTXLPITCR_TXLPITRC_15         (0x8000U << ETH_MMCTXLPITCR_TXLPITRC_Pos)     /*!< 0x00008000 */
#define ETH_MMCTXLPITCR_TXLPITRC_16         (0x10000U << ETH_MMCTXLPITCR_TXLPITRC_Pos)    /*!< 0x00010000 */
#define ETH_MMCTXLPITCR_TXLPITRC_17         (0x20000U << ETH_MMCTXLPITCR_TXLPITRC_Pos)    /*!< 0x00020000 */
#define ETH_MMCTXLPITCR_TXLPITRC_18         (0x40000U << ETH_MMCTXLPITCR_TXLPITRC_Pos)    /*!< 0x00040000 */
#define ETH_MMCTXLPITCR_TXLPITRC_19         (0x80000U << ETH_MMCTXLPITCR_TXLPITRC_Pos)    /*!< 0x00080000 */
#define ETH_MMCTXLPITCR_TXLPITRC_20         (0x100000U << ETH_MMCTXLPITCR_TXLPITRC_Pos)   /*!< 0x00100000 */
#define ETH_MMCTXLPITCR_TXLPITRC_21         (0x200000U << ETH_MMCTXLPITCR_TXLPITRC_Pos)   /*!< 0x00200000 */
#define ETH_MMCTXLPITCR_TXLPITRC_22         (0x400000U << ETH_MMCTXLPITCR_TXLPITRC_Pos)   /*!< 0x00400000 */
#define ETH_MMCTXLPITCR_TXLPITRC_23         (0x800000U << ETH_MMCTXLPITCR_TXLPITRC_Pos)   /*!< 0x00800000 */
#define ETH_MMCTXLPITCR_TXLPITRC_24         (0x1000000U << ETH_MMCTXLPITCR_TXLPITRC_Pos)  /*!< 0x01000000 */
#define ETH_MMCTXLPITCR_TXLPITRC_25         (0x2000000U << ETH_MMCTXLPITCR_TXLPITRC_Pos)  /*!< 0x02000000 */
#define ETH_MMCTXLPITCR_TXLPITRC_26         (0x4000000U << ETH_MMCTXLPITCR_TXLPITRC_Pos)  /*!< 0x04000000 */
#define ETH_MMCTXLPITCR_TXLPITRC_27         (0x8000000U << ETH_MMCTXLPITCR_TXLPITRC_Pos)  /*!< 0x08000000 */
#define ETH_MMCTXLPITCR_TXLPITRC_28         (0x10000000U << ETH_MMCTXLPITCR_TXLPITRC_Pos) /*!< 0x10000000 */
#define ETH_MMCTXLPITCR_TXLPITRC_29         (0x20000000U << ETH_MMCTXLPITCR_TXLPITRC_Pos) /*!< 0x20000000 */
#define ETH_MMCTXLPITCR_TXLPITRC_30         (0x40000000U << ETH_MMCTXLPITCR_TXLPITRC_Pos) /*!< 0x40000000 */
#define ETH_MMCTXLPITCR_TXLPITRC_31         (0x80000000U << ETH_MMCTXLPITCR_TXLPITRC_Pos) /*!< 0x80000000 */

/*************  Bit definition for ETH_MMC_RX_LPI_USEC_CNTR register  *************/
#define ETH_MMCRXLPIMSTR_RXLPIUSC_Pos       (0U)
#define ETH_MMCRXLPIMSTR_RXLPIUSC_Msk       (0xFFFFFFFFU << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos) /*!< 0xFFFFFFFF */
#define ETH_MMCRXLPIMSTR_RXLPIUSC           ETH_MMCRXLPIMSTR_RXLPIUSC_Msk                  /*!< Rx LPI Microseconds Counter */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_0         (0x1U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)        /*!< 0x00000001 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_1         (0x2U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)        /*!< 0x00000002 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_2         (0x4U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)        /*!< 0x00000004 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_3         (0x8U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)        /*!< 0x00000008 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_4         (0x10U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)       /*!< 0x00000010 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_5         (0x20U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)       /*!< 0x00000020 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_6         (0x40U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)       /*!< 0x00000040 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_7         (0x80U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)       /*!< 0x00000080 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_8         (0x100U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)      /*!< 0x00000100 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_9         (0x200U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)      /*!< 0x00000200 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_10        (0x400U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)      /*!< 0x00000400 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_11        (0x800U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)      /*!< 0x00000800 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_12        (0x1000U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)     /*!< 0x00001000 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_13        (0x2000U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)     /*!< 0x00002000 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_14        (0x4000U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)     /*!< 0x00004000 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_15        (0x8000U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)     /*!< 0x00008000 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_16        (0x10000U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)    /*!< 0x00010000 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_17        (0x20000U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)    /*!< 0x00020000 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_18        (0x40000U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)    /*!< 0x00040000 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_19        (0x80000U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)    /*!< 0x00080000 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_20        (0x100000U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)   /*!< 0x00100000 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_21        (0x200000U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)   /*!< 0x00200000 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_22        (0x400000U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)   /*!< 0x00400000 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_23        (0x800000U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)   /*!< 0x00800000 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_24        (0x1000000U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)  /*!< 0x01000000 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_25        (0x2000000U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)  /*!< 0x02000000 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_26        (0x4000000U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)  /*!< 0x04000000 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_27        (0x8000000U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos)  /*!< 0x08000000 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_28        (0x10000000U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos) /*!< 0x10000000 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_29        (0x20000000U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos) /*!< 0x20000000 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_30        (0x40000000U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos) /*!< 0x40000000 */
#define ETH_MMCRXLPIMSTR_RXLPIUSC_31        (0x80000000U << ETH_MMCRXLPIMSTR_RXLPIUSC_Pos) /*!< 0x80000000 */

/*************  Bit definition for ETH_MMC_RX_LPI_TRAN_CNTR register  *************/
#define ETH_MMCRXLPITCR_RXLPITRC_Pos        (0U)
#define ETH_MMCRXLPITCR_RXLPITRC_Msk        (0xFFFFFFFFU << ETH_MMCRXLPITCR_RXLPITRC_Pos) /*!< 0xFFFFFFFF */
#define ETH_MMCRXLPITCR_RXLPITRC            ETH_MMCRXLPITCR_RXLPITRC_Msk                  /*!< Rx LPI Transition counter */
#define ETH_MMCRXLPITCR_RXLPITRC_0          (0x1U << ETH_MMCRXLPITCR_RXLPITRC_Pos)        /*!< 0x00000001 */
#define ETH_MMCRXLPITCR_RXLPITRC_1          (0x2U << ETH_MMCRXLPITCR_RXLPITRC_Pos)        /*!< 0x00000002 */
#define ETH_MMCRXLPITCR_RXLPITRC_2          (0x4U << ETH_MMCRXLPITCR_RXLPITRC_Pos)        /*!< 0x00000004 */
#define ETH_MMCRXLPITCR_RXLPITRC_3          (0x8U << ETH_MMCRXLPITCR_RXLPITRC_Pos)        /*!< 0x00000008 */
#define ETH_MMCRXLPITCR_RXLPITRC_4          (0x10U << ETH_MMCRXLPITCR_RXLPITRC_Pos)       /*!< 0x00000010 */
#define ETH_MMCRXLPITCR_RXLPITRC_5          (0x20U << ETH_MMCRXLPITCR_RXLPITRC_Pos)       /*!< 0x00000020 */
#define ETH_MMCRXLPITCR_RXLPITRC_6          (0x40U << ETH_MMCRXLPITCR_RXLPITRC_Pos)       /*!< 0x00000040 */
#define ETH_MMCRXLPITCR_RXLPITRC_7          (0x80U << ETH_MMCRXLPITCR_RXLPITRC_Pos)       /*!< 0x00000080 */
#define ETH_MMCRXLPITCR_RXLPITRC_8          (0x100U << ETH_MMCRXLPITCR_RXLPITRC_Pos)      /*!< 0x00000100 */
#define ETH_MMCRXLPITCR_RXLPITRC_9          (0x200U << ETH_MMCRXLPITCR_RXLPITRC_Pos)      /*!< 0x00000200 */
#define ETH_MMCRXLPITCR_RXLPITRC_10         (0x400U << ETH_MMCRXLPITCR_RXLPITRC_Pos)      /*!< 0x00000400 */
#define ETH_MMCRXLPITCR_RXLPITRC_11         (0x800U << ETH_MMCRXLPITCR_RXLPITRC_Pos)      /*!< 0x00000800 */
#define ETH_MMCRXLPITCR_RXLPITRC_12         (0x1000U << ETH_MMCRXLPITCR_RXLPITRC_Pos)     /*!< 0x00001000 */
#define ETH_MMCRXLPITCR_RXLPITRC_13         (0x2000U << ETH_MMCRXLPITCR_RXLPITRC_Pos)     /*!< 0x00002000 */
#define ETH_MMCRXLPITCR_RXLPITRC_14         (0x4000U << ETH_MMCRXLPITCR_RXLPITRC_Pos)     /*!< 0x00004000 */
#define ETH_MMCRXLPITCR_RXLPITRC_15         (0x8000U << ETH_MMCRXLPITCR_RXLPITRC_Pos)     /*!< 0x00008000 */
#define ETH_MMCRXLPITCR_RXLPITRC_16         (0x10000U << ETH_MMCRXLPITCR_RXLPITRC_Pos)    /*!< 0x00010000 */
#define ETH_MMCRXLPITCR_RXLPITRC_17         (0x20000U << ETH_MMCRXLPITCR_RXLPITRC_Pos)    /*!< 0x00020000 */
#define ETH_MMCRXLPITCR_RXLPITRC_18         (0x40000U << ETH_MMCRXLPITCR_RXLPITRC_Pos)    /*!< 0x00040000 */
#define ETH_MMCRXLPITCR_RXLPITRC_19         (0x80000U << ETH_MMCRXLPITCR_RXLPITRC_Pos)    /*!< 0x00080000 */
#define ETH_MMCRXLPITCR_RXLPITRC_20         (0x100000U << ETH_MMCRXLPITCR_RXLPITRC_Pos)   /*!< 0x00100000 */
#define ETH_MMCRXLPITCR_RXLPITRC_21         (0x200000U << ETH_MMCRXLPITCR_RXLPITRC_Pos)   /*!< 0x00200000 */
#define ETH_MMCRXLPITCR_RXLPITRC_22         (0x400000U << ETH_MMCRXLPITCR_RXLPITRC_Pos)   /*!< 0x00400000 */
#define ETH_MMCRXLPITCR_RXLPITRC_23         (0x800000U << ETH_MMCRXLPITCR_RXLPITRC_Pos)   /*!< 0x00800000 */
#define ETH_MMCRXLPITCR_RXLPITRC_24         (0x1000000U << ETH_MMCRXLPITCR_RXLPITRC_Pos)  /*!< 0x01000000 */
#define ETH_MMCRXLPITCR_RXLPITRC_25         (0x2000000U << ETH_MMCRXLPITCR_RXLPITRC_Pos)  /*!< 0x02000000 */
#define ETH_MMCRXLPITCR_RXLPITRC_26         (0x4000000U << ETH_MMCRXLPITCR_RXLPITRC_Pos)  /*!< 0x04000000 */
#define ETH_MMCRXLPITCR_RXLPITRC_27         (0x8000000U << ETH_MMCRXLPITCR_RXLPITRC_Pos)  /*!< 0x08000000 */
#define ETH_MMCRXLPITCR_RXLPITRC_28         (0x10000000U << ETH_MMCRXLPITCR_RXLPITRC_Pos) /*!< 0x10000000 */
#define ETH_MMCRXLPITCR_RXLPITRC_29         (0x20000000U << ETH_MMCRXLPITCR_RXLPITRC_Pos) /*!< 0x20000000 */
#define ETH_MMCRXLPITCR_RXLPITRC_30         (0x40000000U << ETH_MMCRXLPITCR_RXLPITRC_Pos) /*!< 0x40000000 */
#define ETH_MMCRXLPITCR_RXLPITRC_31         (0x80000000U << ETH_MMCRXLPITCR_RXLPITRC_Pos) /*!< 0x80000000 */

/************  Bit definition for ETH_MACL3L4C0R register  *************/
#define ETH_MACL3L4C0R_L3PEN0_Pos           (0U)
#define ETH_MACL3L4C0R_L3PEN0_Msk           (0x1U << ETH_MACL3L4C0R_L3PEN0_Pos)                 /*!< 0x00000001 */
#define ETH_MACL3L4C0R_L3PEN0               ETH_MACL3L4C0R_L3PEN0_Msk                           /*!< Layer 3 Protocol Enable */
#define ETH_MACL3L4C0R_L3SAM0_Pos           (2U)
#define ETH_MACL3L4C0R_L3SAM0_Msk           (0x1U << ETH_MACL3L4C0R_L3SAM0_Pos)                 /*!< 0x00000004 */
#define ETH_MACL3L4C0R_L3SAM0               ETH_MACL3L4C0R_L3SAM0_Msk                           /*!< Layer 3 IP SA Match Enable */
#define ETH_MACL3L4C0R_L3SAIM0_Pos          (3U)
#define ETH_MACL3L4C0R_L3SAIM0_Msk          (0x1U << ETH_MACL3L4C0R_L3SAIM0_Pos)                /*!< 0x00000008 */
#define ETH_MACL3L4C0R_L3SAIM0              ETH_MACL3L4C0R_L3SAIM0_Msk                          /*!< Layer 3 IP SA Inverse Match Enable */
#define ETH_MACL3L4C0R_L3DAM0_Pos           (4U)
#define ETH_MACL3L4C0R_L3DAM0_Msk           (0x1U << ETH_MACL3L4C0R_L3DAM0_Pos)                 /*!< 0x00000010 */
#define ETH_MACL3L4C0R_L3DAM0               ETH_MACL3L4C0R_L3DAM0_Msk                           /*!< Layer 3 IP DA Match Enable */
#define ETH_MACL3L4C0R_L3DAIM0_Pos          (5U)
#define ETH_MACL3L4C0R_L3DAIM0_Msk          (0x1U << ETH_MACL3L4C0R_L3DAIM0_Pos)                /*!< 0x00000020 */
#define ETH_MACL3L4C0R_L3DAIM0              ETH_MACL3L4C0R_L3DAIM0_Msk                          /*!< Layer 3 IP DA Inverse Match Enable */
#define ETH_MACL3L4C0R_L3HSBM0_Pos          (6U)
#define ETH_MACL3L4C0R_L3HSBM0_Msk          (0x1FU << ETH_MACL3L4C0R_L3HSBM0_Pos)               /*!< 0x000007C0 */
#define ETH_MACL3L4C0R_L3HSBM0              ETH_MACL3L4C0R_L3HSBM0_Msk                          /*!< Layer 3 IP SA Higher Bits Match */
#define ETH_MACL3L4C0R_L3HSBM0_0            (0x1U << ETH_MACL3L4C0R_L3HSBM0_Pos)               /*!< 0x00000040 */
#define ETH_MACL3L4C0R_L3HSBM0_1            (0x2U << ETH_MACL3L4C0R_L3HSBM0_Pos)               /*!< 0x00000080 */
#define ETH_MACL3L4C0R_L3HSBM0_2            (0x4U << ETH_MACL3L4C0R_L3HSBM0_Pos)              /*!< 0x00000100 */
#define ETH_MACL3L4C0R_L3HSBM0_3            (0x8U << ETH_MACL3L4C0R_L3HSBM0_Pos)              /*!< 0x00000200 */
#define ETH_MACL3L4C0R_L3HSBM0_4            (0x10U << ETH_MACL3L4C0R_L3HSBM0_Pos)              /*!< 0x00000400 */
#define ETH_MACL3L4C0R_L3HDBM0_Pos          (11U)
#define ETH_MACL3L4C0R_L3HDBM0_Msk          (0x1FU << ETH_MACL3L4C0R_L3HDBM0_Pos)               /*!< 0x0000F800 */
#define ETH_MACL3L4C0R_L3HDBM0              ETH_MACL3L4C0R_L3HDBM0_Msk                          /*!< Layer 3 IP DA Higher Bits Match */
#define ETH_MACL3L4C0R_L3HDBM0_0            (0x1U << ETH_MACL3L4C0R_L3HDBM0_Pos)              /*!< 0x00000800 */
#define ETH_MACL3L4C0R_L3HDBM0_1            (0x2U << ETH_MACL3L4C0R_L3HDBM0_Pos)             /*!< 0x00001000 */
#define ETH_MACL3L4C0R_L3HDBM0_2            (0x4U << ETH_MACL3L4C0R_L3HDBM0_Pos)             /*!< 0x00002000 */
#define ETH_MACL3L4C0R_L3HDBM0_3            (0x8U << ETH_MACL3L4C0R_L3HDBM0_Pos)             /*!< 0x00004000 */
#define ETH_MACL3L4C0R_L3HDBM0_4            (0x10U << ETH_MACL3L4C0R_L3HDBM0_Pos)             /*!< 0x00008000 */
#define ETH_MACL3L4C0R_L4PEN0_Pos           (16U)
#define ETH_MACL3L4C0R_L4PEN0_Msk           (0x1U << ETH_MACL3L4C0R_L4PEN0_Pos)                 /*!< 0x00010000 */
#define ETH_MACL3L4C0R_L4PEN0               ETH_MACL3L4C0R_L4PEN0_Msk                           /*!< Layer 4 Protocol Enable */
#define ETH_MACL3L4C0R_L4SPM0_Pos           (18U)
#define ETH_MACL3L4C0R_L4SPM0_Msk           (0x1U << ETH_MACL3L4C0R_L4SPM0_Pos)                 /*!< 0x00040000 */
#define ETH_MACL3L4C0R_L4SPM0               ETH_MACL3L4C0R_L4SPM0_Msk                           /*!< Layer 4 Source Port Match Enable */
#define ETH_MACL3L4C0R_L4SPIM0_Pos          (19U)
#define ETH_MACL3L4C0R_L4SPIM0_Msk          (0x1U << ETH_MACL3L4C0R_L4SPIM0_Pos)                /*!< 0x00080000 */
#define ETH_MACL3L4C0R_L4SPIM0              ETH_MACL3L4C0R_L4SPIM0_Msk                          /*!< Layer 4 Source Port Inverse Match Enable */
#define ETH_MACL3L4C0R_L4DPM0_Pos           (20U)
#define ETH_MACL3L4C0R_L4DPM0_Msk           (0x1U << ETH_MACL3L4C0R_L4DPM0_Pos)                 /*!< 0x00100000 */
#define ETH_MACL3L4C0R_L4DPM0               ETH_MACL3L4C0R_L4DPM0_Msk                           /*!< Layer 4 Destination Port Match Enable */
#define ETH_MACL3L4C0R_L4DPIM0_Pos          (21U)
#define ETH_MACL3L4C0R_L4DPIM0_Msk          (0x1U << ETH_MACL3L4C0R_L4DPIM0_Pos)                /*!< 0x00200000 */
#define ETH_MACL3L4C0R_L4DPIM0              ETH_MACL3L4C0R_L4DPIM0_Msk                          /*!< Layer 4 Destination Port Inverse Match Enable */

/*************  Bit definition for ETH_MACL4A0R register  **************/
#define ETH_MACL4A0R_L4SP0_Pos              (0U)
#define ETH_MACL4A0R_L4SP0_Msk              (0xFFFFU << ETH_MACL4A0R_L4SP0_Pos)                 /*!< 0x0000FFFF */
#define ETH_MACL4A0R_L4SP0                  ETH_MACL4A0R_L4SP0_Msk                              /*!< Layer 4 Source Port Number Field */
#define ETH_MACL4A0R_L4SP0_0                (0x1U << ETH_MACL4A0R_L4SP0_Pos)                    /*!< 0x00000001 */
#define ETH_MACL4A0R_L4SP0_1                (0x2U << ETH_MACL4A0R_L4SP0_Pos)                    /*!< 0x00000002 */
#define ETH_MACL4A0R_L4SP0_2                (0x4U << ETH_MACL4A0R_L4SP0_Pos)                    /*!< 0x00000004 */
#define ETH_MACL4A0R_L4SP0_3                (0x8U << ETH_MACL4A0R_L4SP0_Pos)                    /*!< 0x00000008 */
#define ETH_MACL4A0R_L4SP0_4                (0x10U << ETH_MACL4A0R_L4SP0_Pos)                   /*!< 0x00000010 */
#define ETH_MACL4A0R_L4SP0_5                (0x20U << ETH_MACL4A0R_L4SP0_Pos)                   /*!< 0x00000020 */
#define ETH_MACL4A0R_L4SP0_6                (0x40U << ETH_MACL4A0R_L4SP0_Pos)                   /*!< 0x00000040 */
#define ETH_MACL4A0R_L4SP0_7                (0x80U << ETH_MACL4A0R_L4SP0_Pos)                   /*!< 0x00000080 */
#define ETH_MACL4A0R_L4SP0_8                (0x100U << ETH_MACL4A0R_L4SP0_Pos)                  /*!< 0x00000100 */
#define ETH_MACL4A0R_L4SP0_9                (0x200U << ETH_MACL4A0R_L4SP0_Pos)                  /*!< 0x00000200 */
#define ETH_MACL4A0R_L4SP0_10               (0x400U << ETH_MACL4A0R_L4SP0_Pos)                  /*!< 0x00000400 */
#define ETH_MACL4A0R_L4SP0_11               (0x800U << ETH_MACL4A0R_L4SP0_Pos)                  /*!< 0x00000800 */
#define ETH_MACL4A0R_L4SP0_12               (0x1000U << ETH_MACL4A0R_L4SP0_Pos)                 /*!< 0x00001000 */
#define ETH_MACL4A0R_L4SP0_13               (0x2000U << ETH_MACL4A0R_L4SP0_Pos)                 /*!< 0x00002000 */
#define ETH_MACL4A0R_L4SP0_14               (0x4000U << ETH_MACL4A0R_L4SP0_Pos)                 /*!< 0x00004000 */
#define ETH_MACL4A0R_L4SP0_15               (0x8000U << ETH_MACL4A0R_L4SP0_Pos)                 /*!< 0x00008000 */
#define ETH_MACL4A0R_L4DP0_Pos              (16U)
#define ETH_MACL4A0R_L4DP0_Msk              (0xFFFFU << ETH_MACL4A0R_L4DP0_Pos)                 /*!< 0xFFFF0000 */
#define ETH_MACL4A0R_L4DP0                  ETH_MACL4A0R_L4DP0_Msk                              /*!< Layer 4 Destination Port Number Field */
#define ETH_MACL4A0R_L4DP0_0                (0x1U << ETH_MACL4A0R_L4DP0_Pos)                /*!< 0x00010000 */
#define ETH_MACL4A0R_L4DP0_1                (0x2U << ETH_MACL4A0R_L4DP0_Pos)                /*!< 0x00020000 */
#define ETH_MACL4A0R_L4DP0_2                (0x4U << ETH_MACL4A0R_L4DP0_Pos)                /*!< 0x00040000 */
#define ETH_MACL4A0R_L4DP0_3                (0x8U << ETH_MACL4A0R_L4DP0_Pos)                /*!< 0x00080000 */
#define ETH_MACL4A0R_L4DP0_4                (0x10U << ETH_MACL4A0R_L4DP0_Pos)               /*!< 0x00100000 */
#define ETH_MACL4A0R_L4DP0_5                (0x20U << ETH_MACL4A0R_L4DP0_Pos)               /*!< 0x00200000 */
#define ETH_MACL4A0R_L4DP0_6                (0x40U << ETH_MACL4A0R_L4DP0_Pos)               /*!< 0x00400000 */
#define ETH_MACL4A0R_L4DP0_7                (0x80U << ETH_MACL4A0R_L4DP0_Pos)               /*!< 0x00800000 */
#define ETH_MACL4A0R_L4DP0_8                (0x100U << ETH_MACL4A0R_L4DP0_Pos)              /*!< 0x01000000 */
#define ETH_MACL4A0R_L4DP0_9                (0x200U << ETH_MACL4A0R_L4DP0_Pos)              /*!< 0x02000000 */
#define ETH_MACL4A0R_L4DP0_10               (0x400U << ETH_MACL4A0R_L4DP0_Pos)              /*!< 0x04000000 */
#define ETH_MACL4A0R_L4DP0_11               (0x800U << ETH_MACL4A0R_L4DP0_Pos)              /*!< 0x08000000 */
#define ETH_MACL4A0R_L4DP0_12               (0x1000U << ETH_MACL4A0R_L4DP0_Pos)             /*!< 0x10000000 */
#define ETH_MACL4A0R_L4DP0_13               (0x2000U << ETH_MACL4A0R_L4DP0_Pos)             /*!< 0x20000000 */
#define ETH_MACL4A0R_L4DP0_14               (0x4000U << ETH_MACL4A0R_L4DP0_Pos)             /*!< 0x40000000 */
#define ETH_MACL4A0R_L4DP0_15               (0x8000U << ETH_MACL4A0R_L4DP0_Pos)             /*!< 0x80000000 */

/*************  Bit definition for ETH_MACL3A00R register  *************/
#define ETH_MACL3A00R_L3A00_Pos             (0U)
#define ETH_MACL3A00R_L3A00_Msk             (0xFFFFFFFFU << ETH_MACL3A00R_L3A00_Pos)            /*!< 0xFFFFFFFF */
#define ETH_MACL3A00R_L3A00                 ETH_MACL3A00R_L3A00_Msk                             /*!< Layer 3 Address 0 Field */
#define ETH_MACL3A00R_L3A00_0               (0x1U << ETH_MACL3A00R_L3A00_Pos)                   /*!< 0x00000001 */
#define ETH_MACL3A00R_L3A00_1               (0x2U << ETH_MACL3A00R_L3A00_Pos)                   /*!< 0x00000002 */
#define ETH_MACL3A00R_L3A00_2               (0x4U << ETH_MACL3A00R_L3A00_Pos)                   /*!< 0x00000004 */
#define ETH_MACL3A00R_L3A00_3               (0x8U << ETH_MACL3A00R_L3A00_Pos)                   /*!< 0x00000008 */
#define ETH_MACL3A00R_L3A00_4               (0x10U << ETH_MACL3A00R_L3A00_Pos)                  /*!< 0x00000010 */
#define ETH_MACL3A00R_L3A00_5               (0x20U << ETH_MACL3A00R_L3A00_Pos)                  /*!< 0x00000020 */
#define ETH_MACL3A00R_L3A00_6               (0x40U << ETH_MACL3A00R_L3A00_Pos)                  /*!< 0x00000040 */
#define ETH_MACL3A00R_L3A00_7               (0x80U << ETH_MACL3A00R_L3A00_Pos)                  /*!< 0x00000080 */
#define ETH_MACL3A00R_L3A00_8               (0x100U << ETH_MACL3A00R_L3A00_Pos)                 /*!< 0x00000100 */
#define ETH_MACL3A00R_L3A00_9               (0x200U << ETH_MACL3A00R_L3A00_Pos)                 /*!< 0x00000200 */
#define ETH_MACL3A00R_L3A00_10              (0x400U << ETH_MACL3A00R_L3A00_Pos)                 /*!< 0x00000400 */
#define ETH_MACL3A00R_L3A00_11              (0x800U << ETH_MACL3A00R_L3A00_Pos)                 /*!< 0x00000800 */
#define ETH_MACL3A00R_L3A00_12              (0x1000U << ETH_MACL3A00R_L3A00_Pos)                /*!< 0x00001000 */
#define ETH_MACL3A00R_L3A00_13              (0x2000U << ETH_MACL3A00R_L3A00_Pos)                /*!< 0x00002000 */
#define ETH_MACL3A00R_L3A00_14              (0x4000U << ETH_MACL3A00R_L3A00_Pos)                /*!< 0x00004000 */
#define ETH_MACL3A00R_L3A00_15              (0x8000U << ETH_MACL3A00R_L3A00_Pos)                /*!< 0x00008000 */
#define ETH_MACL3A00R_L3A00_16              (0x10000U << ETH_MACL3A00R_L3A00_Pos)               /*!< 0x00010000 */
#define ETH_MACL3A00R_L3A00_17              (0x20000U << ETH_MACL3A00R_L3A00_Pos)               /*!< 0x00020000 */
#define ETH_MACL3A00R_L3A00_18              (0x40000U << ETH_MACL3A00R_L3A00_Pos)               /*!< 0x00040000 */
#define ETH_MACL3A00R_L3A00_19              (0x80000U << ETH_MACL3A00R_L3A00_Pos)               /*!< 0x00080000 */
#define ETH_MACL3A00R_L3A00_20              (0x100000U << ETH_MACL3A00R_L3A00_Pos)              /*!< 0x00100000 */
#define ETH_MACL3A00R_L3A00_21              (0x200000U << ETH_MACL3A00R_L3A00_Pos)              /*!< 0x00200000 */
#define ETH_MACL3A00R_L3A00_22              (0x400000U << ETH_MACL3A00R_L3A00_Pos)              /*!< 0x00400000 */
#define ETH_MACL3A00R_L3A00_23              (0x800000U << ETH_MACL3A00R_L3A00_Pos)              /*!< 0x00800000 */
#define ETH_MACL3A00R_L3A00_24              (0x1000000U << ETH_MACL3A00R_L3A00_Pos)             /*!< 0x01000000 */
#define ETH_MACL3A00R_L3A00_25              (0x2000000U << ETH_MACL3A00R_L3A00_Pos)             /*!< 0x02000000 */
#define ETH_MACL3A00R_L3A00_26              (0x4000000U << ETH_MACL3A00R_L3A00_Pos)             /*!< 0x04000000 */
#define ETH_MACL3A00R_L3A00_27              (0x8000000U << ETH_MACL3A00R_L3A00_Pos)             /*!< 0x08000000 */
#define ETH_MACL3A00R_L3A00_28              (0x10000000U << ETH_MACL3A00R_L3A00_Pos)            /*!< 0x10000000 */
#define ETH_MACL3A00R_L3A00_29              (0x20000000U << ETH_MACL3A00R_L3A00_Pos)            /*!< 0x20000000 */
#define ETH_MACL3A00R_L3A00_30              (0x40000000U << ETH_MACL3A00R_L3A00_Pos)            /*!< 0x40000000 */
#define ETH_MACL3A00R_L3A00_31              (0x80000000U << ETH_MACL3A00R_L3A00_Pos)            /*!< 0x80000000 */

/*************  Bit definition for ETH_MACL3A10R register  *************/
#define ETH_MACL3A10R_L3A10_Pos             (0U)
#define ETH_MACL3A10R_L3A10_Msk             (0xFFFFFFFFU << ETH_MACL3A10R_L3A10_Pos)            /*!< 0xFFFFFFFF */
#define ETH_MACL3A10R_L3A10                 ETH_MACL3A10R_L3A10_Msk                             /*!< Layer 3 Address 1 Field */
#define ETH_MACL3A10R_L3A10_0               (0x1U << ETH_MACL3A10R_L3A10_Pos)                   /*!< 0x00000001 */
#define ETH_MACL3A10R_L3A10_1               (0x2U << ETH_MACL3A10R_L3A10_Pos)                   /*!< 0x00000002 */
#define ETH_MACL3A10R_L3A10_2               (0x4U << ETH_MACL3A10R_L3A10_Pos)                   /*!< 0x00000004 */
#define ETH_MACL3A10R_L3A10_3               (0x8U << ETH_MACL3A10R_L3A10_Pos)                   /*!< 0x00000008 */
#define ETH_MACL3A10R_L3A10_4               (0x10U << ETH_MACL3A10R_L3A10_Pos)                  /*!< 0x00000010 */
#define ETH_MACL3A10R_L3A10_5               (0x20U << ETH_MACL3A10R_L3A10_Pos)                  /*!< 0x00000020 */
#define ETH_MACL3A10R_L3A10_6               (0x40U << ETH_MACL3A10R_L3A10_Pos)                  /*!< 0x00000040 */
#define ETH_MACL3A10R_L3A10_7               (0x80U << ETH_MACL3A10R_L3A10_Pos)                  /*!< 0x00000080 */
#define ETH_MACL3A10R_L3A10_8               (0x100U << ETH_MACL3A10R_L3A10_Pos)                 /*!< 0x00000100 */
#define ETH_MACL3A10R_L3A10_9               (0x200U << ETH_MACL3A10R_L3A10_Pos)                 /*!< 0x00000200 */
#define ETH_MACL3A10R_L3A10_10              (0x400U << ETH_MACL3A10R_L3A10_Pos)                 /*!< 0x00000400 */
#define ETH_MACL3A10R_L3A10_11              (0x800U << ETH_MACL3A10R_L3A10_Pos)                 /*!< 0x00000800 */
#define ETH_MACL3A10R_L3A10_12              (0x1000U << ETH_MACL3A10R_L3A10_Pos)                /*!< 0x00001000 */
#define ETH_MACL3A10R_L3A10_13              (0x2000U << ETH_MACL3A10R_L3A10_Pos)                /*!< 0x00002000 */
#define ETH_MACL3A10R_L3A10_14              (0x4000U << ETH_MACL3A10R_L3A10_Pos)                /*!< 0x00004000 */
#define ETH_MACL3A10R_L3A10_15              (0x8000U << ETH_MACL3A10R_L3A10_Pos)                /*!< 0x00008000 */
#define ETH_MACL3A10R_L3A10_16              (0x10000U << ETH_MACL3A10R_L3A10_Pos)               /*!< 0x00010000 */
#define ETH_MACL3A10R_L3A10_17              (0x20000U << ETH_MACL3A10R_L3A10_Pos)               /*!< 0x00020000 */
#define ETH_MACL3A10R_L3A10_18              (0x40000U << ETH_MACL3A10R_L3A10_Pos)               /*!< 0x00040000 */
#define ETH_MACL3A10R_L3A10_19              (0x80000U << ETH_MACL3A10R_L3A10_Pos)               /*!< 0x00080000 */
#define ETH_MACL3A10R_L3A10_20              (0x100000U << ETH_MACL3A10R_L3A10_Pos)              /*!< 0x00100000 */
#define ETH_MACL3A10R_L3A10_21              (0x200000U << ETH_MACL3A10R_L3A10_Pos)              /*!< 0x00200000 */
#define ETH_MACL3A10R_L3A10_22              (0x400000U << ETH_MACL3A10R_L3A10_Pos)              /*!< 0x00400000 */
#define ETH_MACL3A10R_L3A10_23              (0x800000U << ETH_MACL3A10R_L3A10_Pos)              /*!< 0x00800000 */
#define ETH_MACL3A10R_L3A10_24              (0x1000000U << ETH_MACL3A10R_L3A10_Pos)             /*!< 0x01000000 */
#define ETH_MACL3A10R_L3A10_25              (0x2000000U << ETH_MACL3A10R_L3A10_Pos)             /*!< 0x02000000 */
#define ETH_MACL3A10R_L3A10_26              (0x4000000U << ETH_MACL3A10R_L3A10_Pos)             /*!< 0x04000000 */
#define ETH_MACL3A10R_L3A10_27              (0x8000000U << ETH_MACL3A10R_L3A10_Pos)             /*!< 0x08000000 */
#define ETH_MACL3A10R_L3A10_28              (0x10000000U << ETH_MACL3A10R_L3A10_Pos)            /*!< 0x10000000 */
#define ETH_MACL3A10R_L3A10_29              (0x20000000U << ETH_MACL3A10R_L3A10_Pos)            /*!< 0x20000000 */
#define ETH_MACL3A10R_L3A10_30              (0x40000000U << ETH_MACL3A10R_L3A10_Pos)            /*!< 0x40000000 */
#define ETH_MACL3A10R_L3A10_31              (0x80000000U << ETH_MACL3A10R_L3A10_Pos)            /*!< 0x80000000 */

/*************  Bit definition for ETH_MACL3A20 register  **************/
#define ETH_MACL3A20_L3A20_Pos              (0U)
#define ETH_MACL3A20_L3A20_Msk              (0xFFFFFFFFU << ETH_MACL3A20_L3A20_Pos)             /*!< 0xFFFFFFFF */
#define ETH_MACL3A20_L3A20                  ETH_MACL3A20_L3A20_Msk                              /*!< Layer 3 Address 2 Field */
#define ETH_MACL3A20_L3A20_0                (0x1U << ETH_MACL3A20_L3A20_Pos)                    /*!< 0x00000001 */
#define ETH_MACL3A20_L3A20_1                (0x2U << ETH_MACL3A20_L3A20_Pos)                    /*!< 0x00000002 */
#define ETH_MACL3A20_L3A20_2                (0x4U << ETH_MACL3A20_L3A20_Pos)                    /*!< 0x00000004 */
#define ETH_MACL3A20_L3A20_3                (0x8U << ETH_MACL3A20_L3A20_Pos)                    /*!< 0x00000008 */
#define ETH_MACL3A20_L3A20_4                (0x10U << ETH_MACL3A20_L3A20_Pos)                   /*!< 0x00000010 */
#define ETH_MACL3A20_L3A20_5                (0x20U << ETH_MACL3A20_L3A20_Pos)                   /*!< 0x00000020 */
#define ETH_MACL3A20_L3A20_6                (0x40U << ETH_MACL3A20_L3A20_Pos)                   /*!< 0x00000040 */
#define ETH_MACL3A20_L3A20_7                (0x80U << ETH_MACL3A20_L3A20_Pos)                   /*!< 0x00000080 */
#define ETH_MACL3A20_L3A20_8                (0x100U << ETH_MACL3A20_L3A20_Pos)                  /*!< 0x00000100 */
#define ETH_MACL3A20_L3A20_9                (0x200U << ETH_MACL3A20_L3A20_Pos)                  /*!< 0x00000200 */
#define ETH_MACL3A20_L3A20_10               (0x400U << ETH_MACL3A20_L3A20_Pos)                  /*!< 0x00000400 */
#define ETH_MACL3A20_L3A20_11               (0x800U << ETH_MACL3A20_L3A20_Pos)                  /*!< 0x00000800 */
#define ETH_MACL3A20_L3A20_12               (0x1000U << ETH_MACL3A20_L3A20_Pos)                 /*!< 0x00001000 */
#define ETH_MACL3A20_L3A20_13               (0x2000U << ETH_MACL3A20_L3A20_Pos)                 /*!< 0x00002000 */
#define ETH_MACL3A20_L3A20_14               (0x4000U << ETH_MACL3A20_L3A20_Pos)                 /*!< 0x00004000 */
#define ETH_MACL3A20_L3A20_15               (0x8000U << ETH_MACL3A20_L3A20_Pos)                 /*!< 0x00008000 */
#define ETH_MACL3A20_L3A20_16               (0x10000U << ETH_MACL3A20_L3A20_Pos)                /*!< 0x00010000 */
#define ETH_MACL3A20_L3A20_17               (0x20000U << ETH_MACL3A20_L3A20_Pos)                /*!< 0x00020000 */
#define ETH_MACL3A20_L3A20_18               (0x40000U << ETH_MACL3A20_L3A20_Pos)                /*!< 0x00040000 */
#define ETH_MACL3A20_L3A20_19               (0x80000U << ETH_MACL3A20_L3A20_Pos)                /*!< 0x00080000 */
#define ETH_MACL3A20_L3A20_20               (0x100000U << ETH_MACL3A20_L3A20_Pos)               /*!< 0x00100000 */
#define ETH_MACL3A20_L3A20_21               (0x200000U << ETH_MACL3A20_L3A20_Pos)               /*!< 0x00200000 */
#define ETH_MACL3A20_L3A20_22               (0x400000U << ETH_MACL3A20_L3A20_Pos)               /*!< 0x00400000 */
#define ETH_MACL3A20_L3A20_23               (0x800000U << ETH_MACL3A20_L3A20_Pos)               /*!< 0x00800000 */
#define ETH_MACL3A20_L3A20_24               (0x1000000U << ETH_MACL3A20_L3A20_Pos)              /*!< 0x01000000 */
#define ETH_MACL3A20_L3A20_25               (0x2000000U << ETH_MACL3A20_L3A20_Pos)              /*!< 0x02000000 */
#define ETH_MACL3A20_L3A20_26               (0x4000000U << ETH_MACL3A20_L3A20_Pos)              /*!< 0x04000000 */
#define ETH_MACL3A20_L3A20_27               (0x8000000U << ETH_MACL3A20_L3A20_Pos)              /*!< 0x08000000 */
#define ETH_MACL3A20_L3A20_28               (0x10000000U << ETH_MACL3A20_L3A20_Pos)             /*!< 0x10000000 */
#define ETH_MACL3A20_L3A20_29               (0x20000000U << ETH_MACL3A20_L3A20_Pos)             /*!< 0x20000000 */
#define ETH_MACL3A20_L3A20_30               (0x40000000U << ETH_MACL3A20_L3A20_Pos)             /*!< 0x40000000 */
#define ETH_MACL3A20_L3A20_31               (0x80000000U << ETH_MACL3A20_L3A20_Pos)             /*!< 0x80000000 */

/*************  Bit definition for ETH_MACL3A30 register  **************/
#define ETH_MACL3A30_L3A30_Pos              (0U)
#define ETH_MACL3A30_L3A30_Msk              (0xFFFFFFFFU << ETH_MACL3A30_L3A30_Pos)             /*!< 0xFFFFFFFF */
#define ETH_MACL3A30_L3A30                  ETH_MACL3A30_L3A30_Msk                              /*!< Layer 3 Address 3 Field */
#define ETH_MACL3A30_L3A30_0                (0x1U << ETH_MACL3A30_L3A30_Pos)                    /*!< 0x00000001 */
#define ETH_MACL3A30_L3A30_1                (0x2U << ETH_MACL3A30_L3A30_Pos)                    /*!< 0x00000002 */
#define ETH_MACL3A30_L3A30_2                (0x4U << ETH_MACL3A30_L3A30_Pos)                    /*!< 0x00000004 */
#define ETH_MACL3A30_L3A30_3                (0x8U << ETH_MACL3A30_L3A30_Pos)                    /*!< 0x00000008 */
#define ETH_MACL3A30_L3A30_4                (0x10U << ETH_MACL3A30_L3A30_Pos)                   /*!< 0x00000010 */
#define ETH_MACL3A30_L3A30_5                (0x20U << ETH_MACL3A30_L3A30_Pos)                   /*!< 0x00000020 */
#define ETH_MACL3A30_L3A30_6                (0x40U << ETH_MACL3A30_L3A30_Pos)                   /*!< 0x00000040 */
#define ETH_MACL3A30_L3A30_7                (0x80U << ETH_MACL3A30_L3A30_Pos)                   /*!< 0x00000080 */
#define ETH_MACL3A30_L3A30_8                (0x100U << ETH_MACL3A30_L3A30_Pos)                  /*!< 0x00000100 */
#define ETH_MACL3A30_L3A30_9                (0x200U << ETH_MACL3A30_L3A30_Pos)                  /*!< 0x00000200 */
#define ETH_MACL3A30_L3A30_10               (0x400U << ETH_MACL3A30_L3A30_Pos)                  /*!< 0x00000400 */
#define ETH_MACL3A30_L3A30_11               (0x800U << ETH_MACL3A30_L3A30_Pos)                  /*!< 0x00000800 */
#define ETH_MACL3A30_L3A30_12               (0x1000U << ETH_MACL3A30_L3A30_Pos)                 /*!< 0x00001000 */
#define ETH_MACL3A30_L3A30_13               (0x2000U << ETH_MACL3A30_L3A30_Pos)                 /*!< 0x00002000 */
#define ETH_MACL3A30_L3A30_14               (0x4000U << ETH_MACL3A30_L3A30_Pos)                 /*!< 0x00004000 */
#define ETH_MACL3A30_L3A30_15               (0x8000U << ETH_MACL3A30_L3A30_Pos)                 /*!< 0x00008000 */
#define ETH_MACL3A30_L3A30_16               (0x10000U << ETH_MACL3A30_L3A30_Pos)                /*!< 0x00010000 */
#define ETH_MACL3A30_L3A30_17               (0x20000U << ETH_MACL3A30_L3A30_Pos)                /*!< 0x00020000 */
#define ETH_MACL3A30_L3A30_18               (0x40000U << ETH_MACL3A30_L3A30_Pos)                /*!< 0x00040000 */
#define ETH_MACL3A30_L3A30_19               (0x80000U << ETH_MACL3A30_L3A30_Pos)                /*!< 0x00080000 */
#define ETH_MACL3A30_L3A30_20               (0x100000U << ETH_MACL3A30_L3A30_Pos)               /*!< 0x00100000 */
#define ETH_MACL3A30_L3A30_21               (0x200000U << ETH_MACL3A30_L3A30_Pos)               /*!< 0x00200000 */
#define ETH_MACL3A30_L3A30_22               (0x400000U << ETH_MACL3A30_L3A30_Pos)               /*!< 0x00400000 */
#define ETH_MACL3A30_L3A30_23               (0x800000U << ETH_MACL3A30_L3A30_Pos)               /*!< 0x00800000 */
#define ETH_MACL3A30_L3A30_24               (0x1000000U << ETH_MACL3A30_L3A30_Pos)              /*!< 0x01000000 */
#define ETH_MACL3A30_L3A30_25               (0x2000000U << ETH_MACL3A30_L3A30_Pos)              /*!< 0x02000000 */
#define ETH_MACL3A30_L3A30_26               (0x4000000U << ETH_MACL3A30_L3A30_Pos)              /*!< 0x04000000 */
#define ETH_MACL3A30_L3A30_27               (0x8000000U << ETH_MACL3A30_L3A30_Pos)              /*!< 0x08000000 */
#define ETH_MACL3A30_L3A30_28               (0x10000000U << ETH_MACL3A30_L3A30_Pos)             /*!< 0x10000000 */
#define ETH_MACL3A30_L3A30_29               (0x20000000U << ETH_MACL3A30_L3A30_Pos)             /*!< 0x20000000 */
#define ETH_MACL3A30_L3A30_30               (0x40000000U << ETH_MACL3A30_L3A30_Pos)             /*!< 0x40000000 */
#define ETH_MACL3A30_L3A30_31               (0x80000000U << ETH_MACL3A30_L3A30_Pos)             /*!< 0x80000000 */

/************  Bit definition for ETH_MACL3L4C1R register  *************/
#define ETH_MACL3L4C1R_L3PEN1_Pos           (0U)
#define ETH_MACL3L4C1R_L3PEN1_Msk           (0x1U << ETH_MACL3L4C1R_L3PEN1_Pos)                 /*!< 0x00000001 */
#define ETH_MACL3L4C1R_L3PEN1               ETH_MACL3L4C1R_L3PEN1_Msk                           /*!< Layer 3 Protocol Enable */
#define ETH_MACL3L4C1R_L3SAM1_Pos           (2U)
#define ETH_MACL3L4C1R_L3SAM1_Msk           (0x1U << ETH_MACL3L4C1R_L3SAM1_Pos)                 /*!< 0x00000004 */
#define ETH_MACL3L4C1R_L3SAM1               ETH_MACL3L4C1R_L3SAM1_Msk                           /*!< Layer 3 IP SA Match Enable */
#define ETH_MACL3L4C1R_L3SAIM1_Pos          (3U)
#define ETH_MACL3L4C1R_L3SAIM1_Msk          (0x1U << ETH_MACL3L4C1R_L3SAIM1_Pos)                /*!< 0x00000008 */
#define ETH_MACL3L4C1R_L3SAIM1              ETH_MACL3L4C1R_L3SAIM1_Msk                          /*!< Layer 3 IP SA Inverse Match Enable */
#define ETH_MACL3L4C1R_L3DAM1_Pos           (4U)
#define ETH_MACL3L4C1R_L3DAM1_Msk           (0x1U << ETH_MACL3L4C1R_L3DAM1_Pos)                 /*!< 0x00000010 */
#define ETH_MACL3L4C1R_L3DAM1               ETH_MACL3L4C1R_L3DAM1_Msk                           /*!< Layer 3 IP DA Match Enable */
#define ETH_MACL3L4C1R_L3DAIM1_Pos          (5U)
#define ETH_MACL3L4C1R_L3DAIM1_Msk          (0x1U << ETH_MACL3L4C1R_L3DAIM1_Pos)                /*!< 0x00000020 */
#define ETH_MACL3L4C1R_L3DAIM1              ETH_MACL3L4C1R_L3DAIM1_Msk                          /*!< Layer 3 IP DA Inverse Match Enable */
#define ETH_MACL3L4C1R_L3HSBM1_Pos          (6U)
#define ETH_MACL3L4C1R_L3HSBM1_Msk          (0x1FU << ETH_MACL3L4C1R_L3HSBM1_Pos)               /*!< 0x000007C0 */
#define ETH_MACL3L4C1R_L3HSBM1              ETH_MACL3L4C1R_L3HSBM1_Msk                          /*!< Layer 3 IP SA Higher Bits Match */
#define ETH_MACL3L4C1R_L3HSBM1_0            (0x1U << ETH_MACL3L4C1R_L3HSBM1_Pos)               /*!< 0x00000040 */
#define ETH_MACL3L4C1R_L3HSBM1_1            (0x2U << ETH_MACL3L4C1R_L3HSBM1_Pos)               /*!< 0x00000080 */
#define ETH_MACL3L4C1R_L3HSBM1_2            (0x4U << ETH_MACL3L4C1R_L3HSBM1_Pos)              /*!< 0x00000100 */
#define ETH_MACL3L4C1R_L3HSBM1_3            (0x8U << ETH_MACL3L4C1R_L3HSBM1_Pos)              /*!< 0x00000200 */
#define ETH_MACL3L4C1R_L3HSBM1_4            (0x10U << ETH_MACL3L4C1R_L3HSBM1_Pos)              /*!< 0x00000400 */
#define ETH_MACL3L4C1R_L3HDBM1_Pos          (11U)
#define ETH_MACL3L4C1R_L3HDBM1_Msk          (0x1FU << ETH_MACL3L4C1R_L3HDBM1_Pos)               /*!< 0x0000F800 */
#define ETH_MACL3L4C1R_L3HDBM1              ETH_MACL3L4C1R_L3HDBM1_Msk                          /*!< Layer 3 IP DA Higher Bits Match */
#define ETH_MACL3L4C1R_L3HDBM1_0            (0x1U << ETH_MACL3L4C1R_L3HDBM1_Pos)              /*!< 0x00000800 */
#define ETH_MACL3L4C1R_L3HDBM1_1            (0x2U << ETH_MACL3L4C1R_L3HDBM1_Pos)             /*!< 0x00001000 */
#define ETH_MACL3L4C1R_L3HDBM1_2            (0x4U << ETH_MACL3L4C1R_L3HDBM1_Pos)             /*!< 0x00002000 */
#define ETH_MACL3L4C1R_L3HDBM1_3            (0x8U << ETH_MACL3L4C1R_L3HDBM1_Pos)             /*!< 0x00004000 */
#define ETH_MACL3L4C1R_L3HDBM1_4            (0x10U << ETH_MACL3L4C1R_L3HDBM1_Pos)             /*!< 0x00008000 */
#define ETH_MACL3L4C1R_L4PEN1_Pos           (16U)
#define ETH_MACL3L4C1R_L4PEN1_Msk           (0x1U << ETH_MACL3L4C1R_L4PEN1_Pos)                 /*!< 0x00010000 */
#define ETH_MACL3L4C1R_L4PEN1               ETH_MACL3L4C1R_L4PEN1_Msk                           /*!< Layer 4 Protocol Enable */
#define ETH_MACL3L4C1R_L4SPM1_Pos           (18U)
#define ETH_MACL3L4C1R_L4SPM1_Msk           (0x1U << ETH_MACL3L4C1R_L4SPM1_Pos)                 /*!< 0x00040000 */
#define ETH_MACL3L4C1R_L4SPM1               ETH_MACL3L4C1R_L4SPM1_Msk                           /*!< Layer 4 Source Port Match Enable */
#define ETH_MACL3L4C1R_L4SPIM1_Pos          (19U)
#define ETH_MACL3L4C1R_L4SPIM1_Msk          (0x1U << ETH_MACL3L4C1R_L4SPIM1_Pos)                /*!< 0x00080000 */
#define ETH_MACL3L4C1R_L4SPIM1              ETH_MACL3L4C1R_L4SPIM1_Msk                          /*!< Layer 4 Source Port Inverse Match Enable */
#define ETH_MACL3L4C1R_L4DPM1_Pos           (20U)
#define ETH_MACL3L4C1R_L4DPM1_Msk           (0x1U << ETH_MACL3L4C1R_L4DPM1_Pos)                 /*!< 0x00100000 */
#define ETH_MACL3L4C1R_L4DPM1               ETH_MACL3L4C1R_L4DPM1_Msk                           /*!< Layer 4 Destination Port Match Enable */
#define ETH_MACL3L4C1R_L4DPIM1_Pos          (21U)
#define ETH_MACL3L4C1R_L4DPIM1_Msk          (0x1U << ETH_MACL3L4C1R_L4DPIM1_Pos)                /*!< 0x00200000 */
#define ETH_MACL3L4C1R_L4DPIM1              ETH_MACL3L4C1R_L4DPIM1_Msk                          /*!< Layer 4 Destination Port Inverse Match Enable */

/*************  Bit definition for ETH_MACL4A1R register  **************/
#define ETH_MACL4A1R_L4SP1_Pos              (0U)
#define ETH_MACL4A1R_L4SP1_Msk              (0xFFFFU << ETH_MACL4A1R_L4SP1_Pos)                 /*!< 0x0000FFFF */
#define ETH_MACL4A1R_L4SP1                  ETH_MACL4A1R_L4SP1_Msk                              /*!< Layer 4 Source Port Number Field */
#define ETH_MACL4A1R_L4SP1_0                (0x1U << ETH_MACL4A1R_L4SP1_Pos)                    /*!< 0x00000001 */
#define ETH_MACL4A1R_L4SP1_1                (0x2U << ETH_MACL4A1R_L4SP1_Pos)                    /*!< 0x00000002 */
#define ETH_MACL4A1R_L4SP1_2                (0x4U << ETH_MACL4A1R_L4SP1_Pos)                    /*!< 0x00000004 */
#define ETH_MACL4A1R_L4SP1_3                (0x8U << ETH_MACL4A1R_L4SP1_Pos)                    /*!< 0x00000008 */
#define ETH_MACL4A1R_L4SP1_4                (0x10U << ETH_MACL4A1R_L4SP1_Pos)                   /*!< 0x00000010 */
#define ETH_MACL4A1R_L4SP1_5                (0x20U << ETH_MACL4A1R_L4SP1_Pos)                   /*!< 0x00000020 */
#define ETH_MACL4A1R_L4SP1_6                (0x40U << ETH_MACL4A1R_L4SP1_Pos)                   /*!< 0x00000040 */
#define ETH_MACL4A1R_L4SP1_7                (0x80U << ETH_MACL4A1R_L4SP1_Pos)                   /*!< 0x00000080 */
#define ETH_MACL4A1R_L4SP1_8                (0x100U << ETH_MACL4A1R_L4SP1_Pos)                  /*!< 0x00000100 */
#define ETH_MACL4A1R_L4SP1_9                (0x200U << ETH_MACL4A1R_L4SP1_Pos)                  /*!< 0x00000200 */
#define ETH_MACL4A1R_L4SP1_10               (0x400U << ETH_MACL4A1R_L4SP1_Pos)                  /*!< 0x00000400 */
#define ETH_MACL4A1R_L4SP1_11               (0x800U << ETH_MACL4A1R_L4SP1_Pos)                  /*!< 0x00000800 */
#define ETH_MACL4A1R_L4SP1_12               (0x1000U << ETH_MACL4A1R_L4SP1_Pos)                 /*!< 0x00001000 */
#define ETH_MACL4A1R_L4SP1_13               (0x2000U << ETH_MACL4A1R_L4SP1_Pos)                 /*!< 0x00002000 */
#define ETH_MACL4A1R_L4SP1_14               (0x4000U << ETH_MACL4A1R_L4SP1_Pos)                 /*!< 0x00004000 */
#define ETH_MACL4A1R_L4SP1_15               (0x8000U << ETH_MACL4A1R_L4SP1_Pos)                 /*!< 0x00008000 */
#define ETH_MACL4A1R_L4DP1_Pos              (16U)
#define ETH_MACL4A1R_L4DP1_Msk              (0xFFFFU << ETH_MACL4A1R_L4DP1_Pos)                 /*!< 0xFFFF0000 */
#define ETH_MACL4A1R_L4DP1                  ETH_MACL4A1R_L4DP1_Msk                              /*!< Layer 4 Destination Port Number Field */
#define ETH_MACL4A1R_L4DP1_0                (0x1U << ETH_MACL4A1R_L4DP1_Pos)                /*!< 0x00010000 */
#define ETH_MACL4A1R_L4DP1_1                (0x2U << ETH_MACL4A1R_L4DP1_Pos)                /*!< 0x00020000 */
#define ETH_MACL4A1R_L4DP1_2                (0x4U << ETH_MACL4A1R_L4DP1_Pos)                /*!< 0x00040000 */
#define ETH_MACL4A1R_L4DP1_3                (0x8U << ETH_MACL4A1R_L4DP1_Pos)                /*!< 0x00080000 */
#define ETH_MACL4A1R_L4DP1_4                (0x10U << ETH_MACL4A1R_L4DP1_Pos)               /*!< 0x00100000 */
#define ETH_MACL4A1R_L4DP1_5                (0x20U << ETH_MACL4A1R_L4DP1_Pos)               /*!< 0x00200000 */
#define ETH_MACL4A1R_L4DP1_6                (0x40U << ETH_MACL4A1R_L4DP1_Pos)               /*!< 0x00400000 */
#define ETH_MACL4A1R_L4DP1_7                (0x80U << ETH_MACL4A1R_L4DP1_Pos)               /*!< 0x00800000 */
#define ETH_MACL4A1R_L4DP1_8                (0x100U << ETH_MACL4A1R_L4DP1_Pos)              /*!< 0x01000000 */
#define ETH_MACL4A1R_L4DP1_9                (0x200U << ETH_MACL4A1R_L4DP1_Pos)              /*!< 0x02000000 */
#define ETH_MACL4A1R_L4DP1_10               (0x400U << ETH_MACL4A1R_L4DP1_Pos)              /*!< 0x04000000 */
#define ETH_MACL4A1R_L4DP1_11               (0x800U << ETH_MACL4A1R_L4DP1_Pos)              /*!< 0x08000000 */
#define ETH_MACL4A1R_L4DP1_12               (0x1000U << ETH_MACL4A1R_L4DP1_Pos)             /*!< 0x10000000 */
#define ETH_MACL4A1R_L4DP1_13               (0x2000U << ETH_MACL4A1R_L4DP1_Pos)             /*!< 0x20000000 */
#define ETH_MACL4A1R_L4DP1_14               (0x4000U << ETH_MACL4A1R_L4DP1_Pos)             /*!< 0x40000000 */
#define ETH_MACL4A1R_L4DP1_15               (0x8000U << ETH_MACL4A1R_L4DP1_Pos)             /*!< 0x80000000 */

/*************  Bit definition for ETH_MACL3A01R register  *************/
#define ETH_MACL3A01R_L3A01_Pos             (0U)
#define ETH_MACL3A01R_L3A01_Msk             (0xFFFFFFFFU << ETH_MACL3A01R_L3A01_Pos)            /*!< 0xFFFFFFFF */
#define ETH_MACL3A01R_L3A01                 ETH_MACL3A01R_L3A01_Msk                             /*!< Layer 3 Address 0 Field */
#define ETH_MACL3A01R_L3A01_0               (0x1U << ETH_MACL3A01R_L3A01_Pos)                   /*!< 0x00000001 */
#define ETH_MACL3A01R_L3A01_1               (0x2U << ETH_MACL3A01R_L3A01_Pos)                   /*!< 0x00000002 */
#define ETH_MACL3A01R_L3A01_2               (0x4U << ETH_MACL3A01R_L3A01_Pos)                   /*!< 0x00000004 */
#define ETH_MACL3A01R_L3A01_3               (0x8U << ETH_MACL3A01R_L3A01_Pos)                   /*!< 0x00000008 */
#define ETH_MACL3A01R_L3A01_4               (0x10U << ETH_MACL3A01R_L3A01_Pos)                  /*!< 0x00000010 */
#define ETH_MACL3A01R_L3A01_5               (0x20U << ETH_MACL3A01R_L3A01_Pos)                  /*!< 0x00000020 */
#define ETH_MACL3A01R_L3A01_6               (0x40U << ETH_MACL3A01R_L3A01_Pos)                  /*!< 0x00000040 */
#define ETH_MACL3A01R_L3A01_7               (0x80U << ETH_MACL3A01R_L3A01_Pos)                  /*!< 0x00000080 */
#define ETH_MACL3A01R_L3A01_8               (0x100U << ETH_MACL3A01R_L3A01_Pos)                 /*!< 0x00000100 */
#define ETH_MACL3A01R_L3A01_9               (0x200U << ETH_MACL3A01R_L3A01_Pos)                 /*!< 0x00000200 */
#define ETH_MACL3A01R_L3A01_10              (0x400U << ETH_MACL3A01R_L3A01_Pos)                 /*!< 0x00000400 */
#define ETH_MACL3A01R_L3A01_11              (0x800U << ETH_MACL3A01R_L3A01_Pos)                 /*!< 0x00000800 */
#define ETH_MACL3A01R_L3A01_12              (0x1000U << ETH_MACL3A01R_L3A01_Pos)                /*!< 0x00001000 */
#define ETH_MACL3A01R_L3A01_13              (0x2000U << ETH_MACL3A01R_L3A01_Pos)                /*!< 0x00002000 */
#define ETH_MACL3A01R_L3A01_14              (0x4000U << ETH_MACL3A01R_L3A01_Pos)                /*!< 0x00004000 */
#define ETH_MACL3A01R_L3A01_15              (0x8000U << ETH_MACL3A01R_L3A01_Pos)                /*!< 0x00008000 */
#define ETH_MACL3A01R_L3A01_16              (0x10000U << ETH_MACL3A01R_L3A01_Pos)               /*!< 0x00010000 */
#define ETH_MACL3A01R_L3A01_17              (0x20000U << ETH_MACL3A01R_L3A01_Pos)               /*!< 0x00020000 */
#define ETH_MACL3A01R_L3A01_18              (0x40000U << ETH_MACL3A01R_L3A01_Pos)               /*!< 0x00040000 */
#define ETH_MACL3A01R_L3A01_19              (0x80000U << ETH_MACL3A01R_L3A01_Pos)               /*!< 0x00080000 */
#define ETH_MACL3A01R_L3A01_20              (0x100000U << ETH_MACL3A01R_L3A01_Pos)              /*!< 0x00100000 */
#define ETH_MACL3A01R_L3A01_21              (0x200000U << ETH_MACL3A01R_L3A01_Pos)              /*!< 0x00200000 */
#define ETH_MACL3A01R_L3A01_22              (0x400000U << ETH_MACL3A01R_L3A01_Pos)              /*!< 0x00400000 */
#define ETH_MACL3A01R_L3A01_23              (0x800000U << ETH_MACL3A01R_L3A01_Pos)              /*!< 0x00800000 */
#define ETH_MACL3A01R_L3A01_24              (0x1000000U << ETH_MACL3A01R_L3A01_Pos)             /*!< 0x01000000 */
#define ETH_MACL3A01R_L3A01_25              (0x2000000U << ETH_MACL3A01R_L3A01_Pos)             /*!< 0x02000000 */
#define ETH_MACL3A01R_L3A01_26              (0x4000000U << ETH_MACL3A01R_L3A01_Pos)             /*!< 0x04000000 */
#define ETH_MACL3A01R_L3A01_27              (0x8000000U << ETH_MACL3A01R_L3A01_Pos)             /*!< 0x08000000 */
#define ETH_MACL3A01R_L3A01_28              (0x10000000U << ETH_MACL3A01R_L3A01_Pos)            /*!< 0x10000000 */
#define ETH_MACL3A01R_L3A01_29              (0x20000000U << ETH_MACL3A01R_L3A01_Pos)            /*!< 0x20000000 */
#define ETH_MACL3A01R_L3A01_30              (0x40000000U << ETH_MACL3A01R_L3A01_Pos)            /*!< 0x40000000 */
#define ETH_MACL3A01R_L3A01_31              (0x80000000U << ETH_MACL3A01R_L3A01_Pos)            /*!< 0x80000000 */

/*************  Bit definition for ETH_MACL3A11R register  *************/
#define ETH_MACL3A11R_L3A11_Pos             (0U)
#define ETH_MACL3A11R_L3A11_Msk             (0xFFFFFFFFU << ETH_MACL3A11R_L3A11_Pos)            /*!< 0xFFFFFFFF */
#define ETH_MACL3A11R_L3A11                 ETH_MACL3A11R_L3A11_Msk                             /*!< Layer 3 Address 1 Field */
#define ETH_MACL3A11R_L3A11_0               (0x1U << ETH_MACL3A11R_L3A11_Pos)                   /*!< 0x00000001 */
#define ETH_MACL3A11R_L3A11_1               (0x2U << ETH_MACL3A11R_L3A11_Pos)                   /*!< 0x00000002 */
#define ETH_MACL3A11R_L3A11_2               (0x4U << ETH_MACL3A11R_L3A11_Pos)                   /*!< 0x00000004 */
#define ETH_MACL3A11R_L3A11_3               (0x8U << ETH_MACL3A11R_L3A11_Pos)                   /*!< 0x00000008 */
#define ETH_MACL3A11R_L3A11_4               (0x10U << ETH_MACL3A11R_L3A11_Pos)                  /*!< 0x00000010 */
#define ETH_MACL3A11R_L3A11_5               (0x20U << ETH_MACL3A11R_L3A11_Pos)                  /*!< 0x00000020 */
#define ETH_MACL3A11R_L3A11_6               (0x40U << ETH_MACL3A11R_L3A11_Pos)                  /*!< 0x00000040 */
#define ETH_MACL3A11R_L3A11_7               (0x80U << ETH_MACL3A11R_L3A11_Pos)                  /*!< 0x00000080 */
#define ETH_MACL3A11R_L3A11_8               (0x100U << ETH_MACL3A11R_L3A11_Pos)                 /*!< 0x00000100 */
#define ETH_MACL3A11R_L3A11_9               (0x200U << ETH_MACL3A11R_L3A11_Pos)                 /*!< 0x00000200 */
#define ETH_MACL3A11R_L3A11_10              (0x400U << ETH_MACL3A11R_L3A11_Pos)                 /*!< 0x00000400 */
#define ETH_MACL3A11R_L3A11_11              (0x800U << ETH_MACL3A11R_L3A11_Pos)                 /*!< 0x00000800 */
#define ETH_MACL3A11R_L3A11_12              (0x1000U << ETH_MACL3A11R_L3A11_Pos)                /*!< 0x00001000 */
#define ETH_MACL3A11R_L3A11_13              (0x2000U << ETH_MACL3A11R_L3A11_Pos)                /*!< 0x00002000 */
#define ETH_MACL3A11R_L3A11_14              (0x4000U << ETH_MACL3A11R_L3A11_Pos)                /*!< 0x00004000 */
#define ETH_MACL3A11R_L3A11_15              (0x8000U << ETH_MACL3A11R_L3A11_Pos)                /*!< 0x00008000 */
#define ETH_MACL3A11R_L3A11_16              (0x10000U << ETH_MACL3A11R_L3A11_Pos)               /*!< 0x00010000 */
#define ETH_MACL3A11R_L3A11_17              (0x20000U << ETH_MACL3A11R_L3A11_Pos)               /*!< 0x00020000 */
#define ETH_MACL3A11R_L3A11_18              (0x40000U << ETH_MACL3A11R_L3A11_Pos)               /*!< 0x00040000 */
#define ETH_MACL3A11R_L3A11_19              (0x80000U << ETH_MACL3A11R_L3A11_Pos)               /*!< 0x00080000 */
#define ETH_MACL3A11R_L3A11_20              (0x100000U << ETH_MACL3A11R_L3A11_Pos)              /*!< 0x00100000 */
#define ETH_MACL3A11R_L3A11_21              (0x200000U << ETH_MACL3A11R_L3A11_Pos)              /*!< 0x00200000 */
#define ETH_MACL3A11R_L3A11_22              (0x400000U << ETH_MACL3A11R_L3A11_Pos)              /*!< 0x00400000 */
#define ETH_MACL3A11R_L3A11_23              (0x800000U << ETH_MACL3A11R_L3A11_Pos)              /*!< 0x00800000 */
#define ETH_MACL3A11R_L3A11_24              (0x1000000U << ETH_MACL3A11R_L3A11_Pos)             /*!< 0x01000000 */
#define ETH_MACL3A11R_L3A11_25              (0x2000000U << ETH_MACL3A11R_L3A11_Pos)             /*!< 0x02000000 */
#define ETH_MACL3A11R_L3A11_26              (0x4000000U << ETH_MACL3A11R_L3A11_Pos)             /*!< 0x04000000 */
#define ETH_MACL3A11R_L3A11_27              (0x8000000U << ETH_MACL3A11R_L3A11_Pos)             /*!< 0x08000000 */
#define ETH_MACL3A11R_L3A11_28              (0x10000000U << ETH_MACL3A11R_L3A11_Pos)            /*!< 0x10000000 */
#define ETH_MACL3A11R_L3A11_29              (0x20000000U << ETH_MACL3A11R_L3A11_Pos)            /*!< 0x20000000 */
#define ETH_MACL3A11R_L3A11_30              (0x40000000U << ETH_MACL3A11R_L3A11_Pos)            /*!< 0x40000000 */
#define ETH_MACL3A11R_L3A11_31              (0x80000000U << ETH_MACL3A11R_L3A11_Pos)            /*!< 0x80000000 */

/*************  Bit definition for ETH_MACL3A21R register  *************/
#define ETH_MACL3A21R_L3A21_Pos             (0U)
#define ETH_MACL3A21R_L3A21_Msk             (0xFFFFFFFFU << ETH_MACL3A21R_L3A21_Pos)            /*!< 0xFFFFFFFF */
#define ETH_MACL3A21R_L3A21                 ETH_MACL3A21R_L3A21_Msk                             /*!< Layer 3 Address 2 Field */
#define ETH_MACL3A21R_L3A21_0               (0x1U << ETH_MACL3A21R_L3A21_Pos)                   /*!< 0x00000001 */
#define ETH_MACL3A21R_L3A21_1               (0x2U << ETH_MACL3A21R_L3A21_Pos)                   /*!< 0x00000002 */
#define ETH_MACL3A21R_L3A21_2               (0x4U << ETH_MACL3A21R_L3A21_Pos)                   /*!< 0x00000004 */
#define ETH_MACL3A21R_L3A21_3               (0x8U << ETH_MACL3A21R_L3A21_Pos)                   /*!< 0x00000008 */
#define ETH_MACL3A21R_L3A21_4               (0x10U << ETH_MACL3A21R_L3A21_Pos)                  /*!< 0x00000010 */
#define ETH_MACL3A21R_L3A21_5               (0x20U << ETH_MACL3A21R_L3A21_Pos)                  /*!< 0x00000020 */
#define ETH_MACL3A21R_L3A21_6               (0x40U << ETH_MACL3A21R_L3A21_Pos)                  /*!< 0x00000040 */
#define ETH_MACL3A21R_L3A21_7               (0x80U << ETH_MACL3A21R_L3A21_Pos)                  /*!< 0x00000080 */
#define ETH_MACL3A21R_L3A21_8               (0x100U << ETH_MACL3A21R_L3A21_Pos)                 /*!< 0x00000100 */
#define ETH_MACL3A21R_L3A21_9               (0x200U << ETH_MACL3A21R_L3A21_Pos)                 /*!< 0x00000200 */
#define ETH_MACL3A21R_L3A21_10              (0x400U << ETH_MACL3A21R_L3A21_Pos)                 /*!< 0x00000400 */
#define ETH_MACL3A21R_L3A21_11              (0x800U << ETH_MACL3A21R_L3A21_Pos)                 /*!< 0x00000800 */
#define ETH_MACL3A21R_L3A21_12              (0x1000U << ETH_MACL3A21R_L3A21_Pos)                /*!< 0x00001000 */
#define ETH_MACL3A21R_L3A21_13              (0x2000U << ETH_MACL3A21R_L3A21_Pos)                /*!< 0x00002000 */
#define ETH_MACL3A21R_L3A21_14              (0x4000U << ETH_MACL3A21R_L3A21_Pos)                /*!< 0x00004000 */
#define ETH_MACL3A21R_L3A21_15              (0x8000U << ETH_MACL3A21R_L3A21_Pos)                /*!< 0x00008000 */
#define ETH_MACL3A21R_L3A21_16              (0x10000U << ETH_MACL3A21R_L3A21_Pos)               /*!< 0x00010000 */
#define ETH_MACL3A21R_L3A21_17              (0x20000U << ETH_MACL3A21R_L3A21_Pos)               /*!< 0x00020000 */
#define ETH_MACL3A21R_L3A21_18              (0x40000U << ETH_MACL3A21R_L3A21_Pos)               /*!< 0x00040000 */
#define ETH_MACL3A21R_L3A21_19              (0x80000U << ETH_MACL3A21R_L3A21_Pos)               /*!< 0x00080000 */
#define ETH_MACL3A21R_L3A21_20              (0x100000U << ETH_MACL3A21R_L3A21_Pos)              /*!< 0x00100000 */
#define ETH_MACL3A21R_L3A21_21              (0x200000U << ETH_MACL3A21R_L3A21_Pos)              /*!< 0x00200000 */
#define ETH_MACL3A21R_L3A21_22              (0x400000U << ETH_MACL3A21R_L3A21_Pos)              /*!< 0x00400000 */
#define ETH_MACL3A21R_L3A21_23              (0x800000U << ETH_MACL3A21R_L3A21_Pos)              /*!< 0x00800000 */
#define ETH_MACL3A21R_L3A21_24              (0x1000000U << ETH_MACL3A21R_L3A21_Pos)             /*!< 0x01000000 */
#define ETH_MACL3A21R_L3A21_25              (0x2000000U << ETH_MACL3A21R_L3A21_Pos)             /*!< 0x02000000 */
#define ETH_MACL3A21R_L3A21_26              (0x4000000U << ETH_MACL3A21R_L3A21_Pos)             /*!< 0x04000000 */
#define ETH_MACL3A21R_L3A21_27              (0x8000000U << ETH_MACL3A21R_L3A21_Pos)             /*!< 0x08000000 */
#define ETH_MACL3A21R_L3A21_28              (0x10000000U << ETH_MACL3A21R_L3A21_Pos)            /*!< 0x10000000 */
#define ETH_MACL3A21R_L3A21_29              (0x20000000U << ETH_MACL3A21R_L3A21_Pos)            /*!< 0x20000000 */
#define ETH_MACL3A21R_L3A21_30              (0x40000000U << ETH_MACL3A21R_L3A21_Pos)            /*!< 0x40000000 */
#define ETH_MACL3A21R_L3A21_31              (0x80000000U << ETH_MACL3A21R_L3A21_Pos)            /*!< 0x80000000 */

/*************  Bit definition for ETH_MACL3A31R register  *************/
#define ETH_MACL3A31R_L3A31_Pos             (0U)
#define ETH_MACL3A31R_L3A31_Msk             (0xFFFFFFFFU << ETH_MACL3A31R_L3A31_Pos)            /*!< 0xFFFFFFFF */
#define ETH_MACL3A31R_L3A31                 ETH_MACL3A31R_L3A31_Msk                             /*!< Layer 3 Address 3 Field */
#define ETH_MACL3A31R_L3A31_0               (0x1U << ETH_MACL3A31R_L3A31_Pos)                   /*!< 0x00000001 */
#define ETH_MACL3A31R_L3A31_1               (0x2U << ETH_MACL3A31R_L3A31_Pos)                   /*!< 0x00000002 */
#define ETH_MACL3A31R_L3A31_2               (0x4U << ETH_MACL3A31R_L3A31_Pos)                   /*!< 0x00000004 */
#define ETH_MACL3A31R_L3A31_3               (0x8U << ETH_MACL3A31R_L3A31_Pos)                   /*!< 0x00000008 */
#define ETH_MACL3A31R_L3A31_4               (0x10U << ETH_MACL3A31R_L3A31_Pos)                  /*!< 0x00000010 */
#define ETH_MACL3A31R_L3A31_5               (0x20U << ETH_MACL3A31R_L3A31_Pos)                  /*!< 0x00000020 */
#define ETH_MACL3A31R_L3A31_6               (0x40U << ETH_MACL3A31R_L3A31_Pos)                  /*!< 0x00000040 */
#define ETH_MACL3A31R_L3A31_7               (0x80U << ETH_MACL3A31R_L3A31_Pos)                  /*!< 0x00000080 */
#define ETH_MACL3A31R_L3A31_8               (0x100U << ETH_MACL3A31R_L3A31_Pos)                 /*!< 0x00000100 */
#define ETH_MACL3A31R_L3A31_9               (0x200U << ETH_MACL3A31R_L3A31_Pos)                 /*!< 0x00000200 */
#define ETH_MACL3A31R_L3A31_10              (0x400U << ETH_MACL3A31R_L3A31_Pos)                 /*!< 0x00000400 */
#define ETH_MACL3A31R_L3A31_11              (0x800U << ETH_MACL3A31R_L3A31_Pos)                 /*!< 0x00000800 */
#define ETH_MACL3A31R_L3A31_12              (0x1000U << ETH_MACL3A31R_L3A31_Pos)                /*!< 0x00001000 */
#define ETH_MACL3A31R_L3A31_13              (0x2000U << ETH_MACL3A31R_L3A31_Pos)                /*!< 0x00002000 */
#define ETH_MACL3A31R_L3A31_14              (0x4000U << ETH_MACL3A31R_L3A31_Pos)                /*!< 0x00004000 */
#define ETH_MACL3A31R_L3A31_15              (0x8000U << ETH_MACL3A31R_L3A31_Pos)                /*!< 0x00008000 */
#define ETH_MACL3A31R_L3A31_16              (0x10000U << ETH_MACL3A31R_L3A31_Pos)               /*!< 0x00010000 */
#define ETH_MACL3A31R_L3A31_17              (0x20000U << ETH_MACL3A31R_L3A31_Pos)               /*!< 0x00020000 */
#define ETH_MACL3A31R_L3A31_18              (0x40000U << ETH_MACL3A31R_L3A31_Pos)               /*!< 0x00040000 */
#define ETH_MACL3A31R_L3A31_19              (0x80000U << ETH_MACL3A31R_L3A31_Pos)               /*!< 0x00080000 */
#define ETH_MACL3A31R_L3A31_20              (0x100000U << ETH_MACL3A31R_L3A31_Pos)              /*!< 0x00100000 */
#define ETH_MACL3A31R_L3A31_21              (0x200000U << ETH_MACL3A31R_L3A31_Pos)              /*!< 0x00200000 */
#define ETH_MACL3A31R_L3A31_22              (0x400000U << ETH_MACL3A31R_L3A31_Pos)              /*!< 0x00400000 */
#define ETH_MACL3A31R_L3A31_23              (0x800000U << ETH_MACL3A31R_L3A31_Pos)              /*!< 0x00800000 */
#define ETH_MACL3A31R_L3A31_24              (0x1000000U << ETH_MACL3A31R_L3A31_Pos)             /*!< 0x01000000 */
#define ETH_MACL3A31R_L3A31_25              (0x2000000U << ETH_MACL3A31R_L3A31_Pos)             /*!< 0x02000000 */
#define ETH_MACL3A31R_L3A31_26              (0x4000000U << ETH_MACL3A31R_L3A31_Pos)             /*!< 0x04000000 */
#define ETH_MACL3A31R_L3A31_27              (0x8000000U << ETH_MACL3A31R_L3A31_Pos)             /*!< 0x08000000 */
#define ETH_MACL3A31R_L3A31_28              (0x10000000U << ETH_MACL3A31R_L3A31_Pos)            /*!< 0x10000000 */
#define ETH_MACL3A31R_L3A31_29              (0x20000000U << ETH_MACL3A31R_L3A31_Pos)            /*!< 0x20000000 */
#define ETH_MACL3A31R_L3A31_30              (0x40000000U << ETH_MACL3A31R_L3A31_Pos)            /*!< 0x40000000 */
#define ETH_MACL3A31R_L3A31_31              (0x80000000U << ETH_MACL3A31R_L3A31_Pos)            /*!< 0x80000000 */

/*************  Bit definition for ETH_MACARPAR register  **************/
#define ETH_MACARPAR_ARPPA_Pos              (0U)
#define ETH_MACARPAR_ARPPA_Msk              (0xFFFFFFFFU << ETH_MACARPAR_ARPPA_Pos)             /*!< 0xFFFFFFFF */
#define ETH_MACARPAR_ARPPA                  ETH_MACARPAR_ARPPA_Msk                              /*!< ARP Protocol Address */
#define ETH_MACARPAR_ARPPA_0                (0x1U << ETH_MACARPAR_ARPPA_Pos)                    /*!< 0x00000001 */
#define ETH_MACARPAR_ARPPA_1                (0x2U << ETH_MACARPAR_ARPPA_Pos)                    /*!< 0x00000002 */
#define ETH_MACARPAR_ARPPA_2                (0x4U << ETH_MACARPAR_ARPPA_Pos)                    /*!< 0x00000004 */
#define ETH_MACARPAR_ARPPA_3                (0x8U << ETH_MACARPAR_ARPPA_Pos)                    /*!< 0x00000008 */
#define ETH_MACARPAR_ARPPA_4                (0x10U << ETH_MACARPAR_ARPPA_Pos)                   /*!< 0x00000010 */
#define ETH_MACARPAR_ARPPA_5                (0x20U << ETH_MACARPAR_ARPPA_Pos)                   /*!< 0x00000020 */
#define ETH_MACARPAR_ARPPA_6                (0x40U << ETH_MACARPAR_ARPPA_Pos)                   /*!< 0x00000040 */
#define ETH_MACARPAR_ARPPA_7                (0x80U << ETH_MACARPAR_ARPPA_Pos)                   /*!< 0x00000080 */
#define ETH_MACARPAR_ARPPA_8                (0x100U << ETH_MACARPAR_ARPPA_Pos)                  /*!< 0x00000100 */
#define ETH_MACARPAR_ARPPA_9                (0x200U << ETH_MACARPAR_ARPPA_Pos)                  /*!< 0x00000200 */
#define ETH_MACARPAR_ARPPA_10               (0x400U << ETH_MACARPAR_ARPPA_Pos)                  /*!< 0x00000400 */
#define ETH_MACARPAR_ARPPA_11               (0x800U << ETH_MACARPAR_ARPPA_Pos)                  /*!< 0x00000800 */
#define ETH_MACARPAR_ARPPA_12               (0x1000U << ETH_MACARPAR_ARPPA_Pos)                 /*!< 0x00001000 */
#define ETH_MACARPAR_ARPPA_13               (0x2000U << ETH_MACARPAR_ARPPA_Pos)                 /*!< 0x00002000 */
#define ETH_MACARPAR_ARPPA_14               (0x4000U << ETH_MACARPAR_ARPPA_Pos)                 /*!< 0x00004000 */
#define ETH_MACARPAR_ARPPA_15               (0x8000U << ETH_MACARPAR_ARPPA_Pos)                 /*!< 0x00008000 */
#define ETH_MACARPAR_ARPPA_16               (0x10000U << ETH_MACARPAR_ARPPA_Pos)                /*!< 0x00010000 */
#define ETH_MACARPAR_ARPPA_17               (0x20000U << ETH_MACARPAR_ARPPA_Pos)                /*!< 0x00020000 */
#define ETH_MACARPAR_ARPPA_18               (0x40000U << ETH_MACARPAR_ARPPA_Pos)                /*!< 0x00040000 */
#define ETH_MACARPAR_ARPPA_19               (0x80000U << ETH_MACARPAR_ARPPA_Pos)                /*!< 0x00080000 */
#define ETH_MACARPAR_ARPPA_20               (0x100000U << ETH_MACARPAR_ARPPA_Pos)               /*!< 0x00100000 */
#define ETH_MACARPAR_ARPPA_21               (0x200000U << ETH_MACARPAR_ARPPA_Pos)               /*!< 0x00200000 */
#define ETH_MACARPAR_ARPPA_22               (0x400000U << ETH_MACARPAR_ARPPA_Pos)               /*!< 0x00400000 */
#define ETH_MACARPAR_ARPPA_23               (0x800000U << ETH_MACARPAR_ARPPA_Pos)               /*!< 0x00800000 */
#define ETH_MACARPAR_ARPPA_24               (0x1000000U << ETH_MACARPAR_ARPPA_Pos)              /*!< 0x01000000 */
#define ETH_MACARPAR_ARPPA_25               (0x2000000U << ETH_MACARPAR_ARPPA_Pos)              /*!< 0x02000000 */
#define ETH_MACARPAR_ARPPA_26               (0x4000000U << ETH_MACARPAR_ARPPA_Pos)              /*!< 0x04000000 */
#define ETH_MACARPAR_ARPPA_27               (0x8000000U << ETH_MACARPAR_ARPPA_Pos)              /*!< 0x08000000 */
#define ETH_MACARPAR_ARPPA_28               (0x10000000U << ETH_MACARPAR_ARPPA_Pos)             /*!< 0x10000000 */
#define ETH_MACARPAR_ARPPA_29               (0x20000000U << ETH_MACARPAR_ARPPA_Pos)             /*!< 0x20000000 */
#define ETH_MACARPAR_ARPPA_30               (0x40000000U << ETH_MACARPAR_ARPPA_Pos)             /*!< 0x40000000 */
#define ETH_MACARPAR_ARPPA_31               (0x80000000U << ETH_MACARPAR_ARPPA_Pos)             /*!< 0x80000000 */

/**************  Bit definition for ETH_MACTSCR register  **************/
#define ETH_MACTSCR_TSENA_Pos               (0U)
#define ETH_MACTSCR_TSENA_Msk               (0x1U << ETH_MACTSCR_TSENA_Pos)                     /*!< 0x00000001 */
#define ETH_MACTSCR_TSENA                   ETH_MACTSCR_TSENA_Msk                               /*!< Enable Timestamp */
#define ETH_MACTSCR_TSCFUPDT_Pos            (1U)
#define ETH_MACTSCR_TSCFUPDT_Msk            (0x1U << ETH_MACTSCR_TSCFUPDT_Pos)                  /*!< 0x00000002 */
#define ETH_MACTSCR_TSCFUPDT                ETH_MACTSCR_TSCFUPDT_Msk                            /*!< Fine or Coarse Timestamp Update */
#define ETH_MACTSCR_TSINIT_Pos              (2U)
#define ETH_MACTSCR_TSINIT_Msk              (0x1U << ETH_MACTSCR_TSINIT_Pos)                    /*!< 0x00000004 */
#define ETH_MACTSCR_TSINIT                  ETH_MACTSCR_TSINIT_Msk                              /*!< Initialize Timestamp */
#define ETH_MACTSCR_TSUPDT_Pos              (3U)
#define ETH_MACTSCR_TSUPDT_Msk              (0x1U << ETH_MACTSCR_TSUPDT_Pos)                    /*!< 0x00000008 */
#define ETH_MACTSCR_TSUPDT                  ETH_MACTSCR_TSUPDT_Msk                              /*!< Update Timestamp */
#define ETH_MACTSCR_TSADDREG_Pos            (5U)
#define ETH_MACTSCR_TSADDREG_Msk            (0x1U << ETH_MACTSCR_TSADDREG_Pos)                  /*!< 0x00000020 */
#define ETH_MACTSCR_TSADDREG                ETH_MACTSCR_TSADDREG_Msk                            /*!< Update Addend Register */
#define ETH_MACTSCR_TSENALL_Pos             (8U)
#define ETH_MACTSCR_TSENALL_Msk             (0x1U << ETH_MACTSCR_TSENALL_Pos)                   /*!< 0x00000100 */
#define ETH_MACTSCR_TSENALL                 ETH_MACTSCR_TSENALL_Msk                             /*!< Enable Timestamp for All Packets */
#define ETH_MACTSCR_TSCTRLSSR_Pos           (9U)
#define ETH_MACTSCR_TSCTRLSSR_Msk           (0x1U << ETH_MACTSCR_TSCTRLSSR_Pos)                 /*!< 0x00000200 */
#define ETH_MACTSCR_TSCTRLSSR               ETH_MACTSCR_TSCTRLSSR_Msk                           /*!< Timestamp Digital or Binary Rollover Control */
#define ETH_MACTSCR_TSVER2ENA_Pos           (10U)
#define ETH_MACTSCR_TSVER2ENA_Msk           (0x1U << ETH_MACTSCR_TSVER2ENA_Pos)                 /*!< 0x00000400 */
#define ETH_MACTSCR_TSVER2ENA               ETH_MACTSCR_TSVER2ENA_Msk                           /*!< Enable PTP Packet Processing for Version 2 Format */
#define ETH_MACTSCR_TSIPENA_Pos             (11U)
#define ETH_MACTSCR_TSIPENA_Msk             (0x1U << ETH_MACTSCR_TSIPENA_Pos)                   /*!< 0x00000800 */
#define ETH_MACTSCR_TSIPENA                 ETH_MACTSCR_TSIPENA_Msk                             /*!< Enable Processing of PTP over Ethernet Packets */
#define ETH_MACTSCR_TSIPV6ENA_Pos           (12U)
#define ETH_MACTSCR_TSIPV6ENA_Msk           (0x1U << ETH_MACTSCR_TSIPV6ENA_Pos)                 /*!< 0x00001000 */
#define ETH_MACTSCR_TSIPV6ENA               ETH_MACTSCR_TSIPV6ENA_Msk                           /*!< Enable Processing of PTP Packets Sent over IPv6-UDP */
#define ETH_MACTSCR_TSIPV4ENA_Pos           (13U)
#define ETH_MACTSCR_TSIPV4ENA_Msk           (0x1U << ETH_MACTSCR_TSIPV4ENA_Pos)                 /*!< 0x00002000 */
#define ETH_MACTSCR_TSIPV4ENA               ETH_MACTSCR_TSIPV4ENA_Msk                           /*!< Enable Processing of PTP Packets Sent over IPv4-UDP */
#define ETH_MACTSCR_TSEVNTENA_Pos           (14U)
#define ETH_MACTSCR_TSEVNTENA_Msk           (0x1U << ETH_MACTSCR_TSEVNTENA_Pos)                 /*!< 0x00004000 */
#define ETH_MACTSCR_TSEVNTENA               ETH_MACTSCR_TSEVNTENA_Msk                           /*!< Enable Timestamp Snapshot for Event Messages */
#define ETH_MACTSCR_TSMSTRENA_Pos           (15U)
#define ETH_MACTSCR_TSMSTRENA_Msk           (0x1U << ETH_MACTSCR_TSMSTRENA_Pos)                 /*!< 0x00008000 */
#define ETH_MACTSCR_TSMSTRENA               ETH_MACTSCR_TSMSTRENA_Msk                           /*!< Enable Snapshot for Messages Relevant to Master */
#define ETH_MACTSCR_SNAPTYPSEL_Pos          (16U)
#define ETH_MACTSCR_SNAPTYPSEL_Msk          (0x3U << ETH_MACTSCR_SNAPTYPSEL_Pos)                /*!< 0x00030000 */
#define ETH_MACTSCR_SNAPTYPSEL              ETH_MACTSCR_SNAPTYPSEL_Msk                          /*!< Select PTP packets for Taking Snapshots */
#define ETH_MACTSCR_SNAPTYPSEL_0            (0x1U << ETH_MACTSCR_SNAPTYPSEL_Pos)            /*!< 0x00010000 */
#define ETH_MACTSCR_SNAPTYPSEL_1            (0x2U << ETH_MACTSCR_SNAPTYPSEL_Pos)            /*!< 0x00020000 */
#define ETH_MACTSCR_TSENMACADDR_Pos         (18U)
#define ETH_MACTSCR_TSENMACADDR_Msk         (0x1U << ETH_MACTSCR_TSENMACADDR_Pos)               /*!< 0x00040000 */
#define ETH_MACTSCR_TSENMACADDR             ETH_MACTSCR_TSENMACADDR_Msk                         /*!< Enable MAC Address for PTP Packet Filtering */
#define ETH_MACTSCR_CSC_Pos                 (19U)
#define ETH_MACTSCR_CSC_Msk                 (0x1U << ETH_MACTSCR_CSC_Pos)                       /*!< 0x00080000 */
#define ETH_MACTSCR_CSC                     ETH_MACTSCR_CSC_Msk                                 /*!< Enable checksum correction during OST for PTP over UDP/IPv4 packets */
#define ETH_MACTSCR_TXTSSTSM_Pos            (24U)
#define ETH_MACTSCR_TXTSSTSM_Msk            (0x1U << ETH_MACTSCR_TXTSSTSM_Pos)                  /*!< 0x01000000 */
#define ETH_MACTSCR_TXTSSTSM                ETH_MACTSCR_TXTSSTSM_Msk                            /*!< Transmit Timestamp Status Mode */
#define ETH_MACTSCR_AV8021ASMEN_Pos         (28U)
#define ETH_MACTSCR_AV8021ASMEN_Msk         (0x1U << ETH_MACTSCR_AV8021ASMEN_Pos)               /*!< 0x10000000 */
#define ETH_MACTSCR_AV8021ASMEN             ETH_MACTSCR_AV8021ASMEN_Msk                         /*!< AV 802.1AS Mode Enable */

/**************  Bit definition for ETH_MACSSIR register  **************/
#define ETH_MACSSIR_SNSINC_Pos              (8U)
#define ETH_MACSSIR_SNSINC_Msk              (0xFFU << ETH_MACSSIR_SNSINC_Pos)                   /*!< 0x0000FF00 */
#define ETH_MACSSIR_SNSINC                  ETH_MACSSIR_SNSINC_Msk                              /*!< Sub-nanosecond Increment Value */
#define ETH_MACSSIR_SNSINC_0                (0x1U << ETH_MACSSIR_SNSINC_Pos)                  /*!< 0x00000100 */
#define ETH_MACSSIR_SNSINC_1                (0x2U << ETH_MACSSIR_SNSINC_Pos)                  /*!< 0x00000200 */
#define ETH_MACSSIR_SNSINC_2                (0x4U << ETH_MACSSIR_SNSINC_Pos)                  /*!< 0x00000400 */
#define ETH_MACSSIR_SNSINC_3                (0x8U << ETH_MACSSIR_SNSINC_Pos)                  /*!< 0x00000800 */
#define ETH_MACSSIR_SNSINC_4                (0x10U << ETH_MACSSIR_SNSINC_Pos)                 /*!< 0x00001000 */
#define ETH_MACSSIR_SNSINC_5                (0x20U << ETH_MACSSIR_SNSINC_Pos)                 /*!< 0x00002000 */
#define ETH_MACSSIR_SNSINC_6                (0x40U << ETH_MACSSIR_SNSINC_Pos)                 /*!< 0x00004000 */
#define ETH_MACSSIR_SNSINC_7                (0x80U << ETH_MACSSIR_SNSINC_Pos)                 /*!< 0x00008000 */
#define ETH_MACSSIR_SSINC_Pos               (16U)
#define ETH_MACSSIR_SSINC_Msk               (0xFFU << ETH_MACSSIR_SSINC_Pos)                    /*!< 0x00FF0000 */
#define ETH_MACSSIR_SSINC                   ETH_MACSSIR_SSINC_Msk                               /*!< Sub-second Increment Value */
#define ETH_MACSSIR_SSINC_0                 (0x1U << ETH_MACSSIR_SSINC_Pos)                 /*!< 0x00010000 */
#define ETH_MACSSIR_SSINC_1                 (0x2U << ETH_MACSSIR_SSINC_Pos)                 /*!< 0x00020000 */
#define ETH_MACSSIR_SSINC_2                 (0x4U << ETH_MACSSIR_SSINC_Pos)                 /*!< 0x00040000 */
#define ETH_MACSSIR_SSINC_3                 (0x8U << ETH_MACSSIR_SSINC_Pos)                 /*!< 0x00080000 */
#define ETH_MACSSIR_SSINC_4                 (0x10U << ETH_MACSSIR_SSINC_Pos)                /*!< 0x00100000 */
#define ETH_MACSSIR_SSINC_5                 (0x20U << ETH_MACSSIR_SSINC_Pos)                /*!< 0x00200000 */
#define ETH_MACSSIR_SSINC_6                 (0x40U << ETH_MACSSIR_SSINC_Pos)                /*!< 0x00400000 */
#define ETH_MACSSIR_SSINC_7                 (0x80U << ETH_MACSSIR_SSINC_Pos)                /*!< 0x00800000 */

/**************  Bit definition for ETH_MACSTSR register  **************/
#define ETH_MACSTSR_TSS_Pos                 (0U)
#define ETH_MACSTSR_TSS_Msk                 (0xFFFFFFFFU << ETH_MACSTSR_TSS_Pos)                /*!< 0xFFFFFFFF */
#define ETH_MACSTSR_TSS                     ETH_MACSTSR_TSS_Msk                                 /*!< Timestamp Second */
#define ETH_MACSTSR_TSS_0                   (0x1U << ETH_MACSTSR_TSS_Pos)                       /*!< 0x00000001 */
#define ETH_MACSTSR_TSS_1                   (0x2U << ETH_MACSTSR_TSS_Pos)                       /*!< 0x00000002 */
#define ETH_MACSTSR_TSS_2                   (0x4U << ETH_MACSTSR_TSS_Pos)                       /*!< 0x00000004 */
#define ETH_MACSTSR_TSS_3                   (0x8U << ETH_MACSTSR_TSS_Pos)                       /*!< 0x00000008 */
#define ETH_MACSTSR_TSS_4                   (0x10U << ETH_MACSTSR_TSS_Pos)                      /*!< 0x00000010 */
#define ETH_MACSTSR_TSS_5                   (0x20U << ETH_MACSTSR_TSS_Pos)                      /*!< 0x00000020 */
#define ETH_MACSTSR_TSS_6                   (0x40U << ETH_MACSTSR_TSS_Pos)                      /*!< 0x00000040 */
#define ETH_MACSTSR_TSS_7                   (0x80U << ETH_MACSTSR_TSS_Pos)                      /*!< 0x00000080 */
#define ETH_MACSTSR_TSS_8                   (0x100U << ETH_MACSTSR_TSS_Pos)                     /*!< 0x00000100 */
#define ETH_MACSTSR_TSS_9                   (0x200U << ETH_MACSTSR_TSS_Pos)                     /*!< 0x00000200 */
#define ETH_MACSTSR_TSS_10                  (0x400U << ETH_MACSTSR_TSS_Pos)                     /*!< 0x00000400 */
#define ETH_MACSTSR_TSS_11                  (0x800U << ETH_MACSTSR_TSS_Pos)                     /*!< 0x00000800 */
#define ETH_MACSTSR_TSS_12                  (0x1000U << ETH_MACSTSR_TSS_Pos)                    /*!< 0x00001000 */
#define ETH_MACSTSR_TSS_13                  (0x2000U << ETH_MACSTSR_TSS_Pos)                    /*!< 0x00002000 */
#define ETH_MACSTSR_TSS_14                  (0x4000U << ETH_MACSTSR_TSS_Pos)                    /*!< 0x00004000 */
#define ETH_MACSTSR_TSS_15                  (0x8000U << ETH_MACSTSR_TSS_Pos)                    /*!< 0x00008000 */
#define ETH_MACSTSR_TSS_16                  (0x10000U << ETH_MACSTSR_TSS_Pos)                   /*!< 0x00010000 */
#define ETH_MACSTSR_TSS_17                  (0x20000U << ETH_MACSTSR_TSS_Pos)                   /*!< 0x00020000 */
#define ETH_MACSTSR_TSS_18                  (0x40000U << ETH_MACSTSR_TSS_Pos)                   /*!< 0x00040000 */
#define ETH_MACSTSR_TSS_19                  (0x80000U << ETH_MACSTSR_TSS_Pos)                   /*!< 0x00080000 */
#define ETH_MACSTSR_TSS_20                  (0x100000U << ETH_MACSTSR_TSS_Pos)                  /*!< 0x00100000 */
#define ETH_MACSTSR_TSS_21                  (0x200000U << ETH_MACSTSR_TSS_Pos)                  /*!< 0x00200000 */
#define ETH_MACSTSR_TSS_22                  (0x400000U << ETH_MACSTSR_TSS_Pos)                  /*!< 0x00400000 */
#define ETH_MACSTSR_TSS_23                  (0x800000U << ETH_MACSTSR_TSS_Pos)                  /*!< 0x00800000 */
#define ETH_MACSTSR_TSS_24                  (0x1000000U << ETH_MACSTSR_TSS_Pos)                 /*!< 0x01000000 */
#define ETH_MACSTSR_TSS_25                  (0x2000000U << ETH_MACSTSR_TSS_Pos)                 /*!< 0x02000000 */
#define ETH_MACSTSR_TSS_26                  (0x4000000U << ETH_MACSTSR_TSS_Pos)                 /*!< 0x04000000 */
#define ETH_MACSTSR_TSS_27                  (0x8000000U << ETH_MACSTSR_TSS_Pos)                 /*!< 0x08000000 */
#define ETH_MACSTSR_TSS_28                  (0x10000000U << ETH_MACSTSR_TSS_Pos)                /*!< 0x10000000 */
#define ETH_MACSTSR_TSS_29                  (0x20000000U << ETH_MACSTSR_TSS_Pos)                /*!< 0x20000000 */
#define ETH_MACSTSR_TSS_30                  (0x40000000U << ETH_MACSTSR_TSS_Pos)                /*!< 0x40000000 */
#define ETH_MACSTSR_TSS_31                  (0x80000000U << ETH_MACSTSR_TSS_Pos)                /*!< 0x80000000 */

/**************  Bit definition for ETH_MACSTNR register  **************/
#define ETH_MACSTNR_TSSS_Pos                (0U)
#define ETH_MACSTNR_TSSS_Msk                (0x7FFFFFFFU << ETH_MACSTNR_TSSS_Pos)               /*!< 0x7FFFFFFF */
#define ETH_MACSTNR_TSSS                    ETH_MACSTNR_TSSS_Msk                                /*!< Timestamp Sub-seconds */
#define ETH_MACSTNR_TSSS_0                  (0x1U << ETH_MACSTNR_TSSS_Pos)                      /*!< 0x00000001 */
#define ETH_MACSTNR_TSSS_1                  (0x2U << ETH_MACSTNR_TSSS_Pos)                      /*!< 0x00000002 */
#define ETH_MACSTNR_TSSS_2                  (0x4U << ETH_MACSTNR_TSSS_Pos)                      /*!< 0x00000004 */
#define ETH_MACSTNR_TSSS_3                  (0x8U << ETH_MACSTNR_TSSS_Pos)                      /*!< 0x00000008 */
#define ETH_MACSTNR_TSSS_4                  (0x10U << ETH_MACSTNR_TSSS_Pos)                     /*!< 0x00000010 */
#define ETH_MACSTNR_TSSS_5                  (0x20U << ETH_MACSTNR_TSSS_Pos)                     /*!< 0x00000020 */
#define ETH_MACSTNR_TSSS_6                  (0x40U << ETH_MACSTNR_TSSS_Pos)                     /*!< 0x00000040 */
#define ETH_MACSTNR_TSSS_7                  (0x80U << ETH_MACSTNR_TSSS_Pos)                     /*!< 0x00000080 */
#define ETH_MACSTNR_TSSS_8                  (0x100U << ETH_MACSTNR_TSSS_Pos)                    /*!< 0x00000100 */
#define ETH_MACSTNR_TSSS_9                  (0x200U << ETH_MACSTNR_TSSS_Pos)                    /*!< 0x00000200 */
#define ETH_MACSTNR_TSSS_10                 (0x400U << ETH_MACSTNR_TSSS_Pos)                    /*!< 0x00000400 */
#define ETH_MACSTNR_TSSS_11                 (0x800U << ETH_MACSTNR_TSSS_Pos)                    /*!< 0x00000800 */
#define ETH_MACSTNR_TSSS_12                 (0x1000U << ETH_MACSTNR_TSSS_Pos)                   /*!< 0x00001000 */
#define ETH_MACSTNR_TSSS_13                 (0x2000U << ETH_MACSTNR_TSSS_Pos)                   /*!< 0x00002000 */
#define ETH_MACSTNR_TSSS_14                 (0x4000U << ETH_MACSTNR_TSSS_Pos)                   /*!< 0x00004000 */
#define ETH_MACSTNR_TSSS_15                 (0x8000U << ETH_MACSTNR_TSSS_Pos)                   /*!< 0x00008000 */
#define ETH_MACSTNR_TSSS_16                 (0x10000U << ETH_MACSTNR_TSSS_Pos)                  /*!< 0x00010000 */
#define ETH_MACSTNR_TSSS_17                 (0x20000U << ETH_MACSTNR_TSSS_Pos)                  /*!< 0x00020000 */
#define ETH_MACSTNR_TSSS_18                 (0x40000U << ETH_MACSTNR_TSSS_Pos)                  /*!< 0x00040000 */
#define ETH_MACSTNR_TSSS_19                 (0x80000U << ETH_MACSTNR_TSSS_Pos)                  /*!< 0x00080000 */
#define ETH_MACSTNR_TSSS_20                 (0x100000U << ETH_MACSTNR_TSSS_Pos)                 /*!< 0x00100000 */
#define ETH_MACSTNR_TSSS_21                 (0x200000U << ETH_MACSTNR_TSSS_Pos)                 /*!< 0x00200000 */
#define ETH_MACSTNR_TSSS_22                 (0x400000U << ETH_MACSTNR_TSSS_Pos)                 /*!< 0x00400000 */
#define ETH_MACSTNR_TSSS_23                 (0x800000U << ETH_MACSTNR_TSSS_Pos)                 /*!< 0x00800000 */
#define ETH_MACSTNR_TSSS_24                 (0x1000000U << ETH_MACSTNR_TSSS_Pos)                /*!< 0x01000000 */
#define ETH_MACSTNR_TSSS_25                 (0x2000000U << ETH_MACSTNR_TSSS_Pos)                /*!< 0x02000000 */
#define ETH_MACSTNR_TSSS_26                 (0x4000000U << ETH_MACSTNR_TSSS_Pos)                /*!< 0x04000000 */
#define ETH_MACSTNR_TSSS_27                 (0x8000000U << ETH_MACSTNR_TSSS_Pos)                /*!< 0x08000000 */
#define ETH_MACSTNR_TSSS_28                 (0x10000000U << ETH_MACSTNR_TSSS_Pos)               /*!< 0x10000000 */
#define ETH_MACSTNR_TSSS_29                 (0x20000000U << ETH_MACSTNR_TSSS_Pos)               /*!< 0x20000000 */
#define ETH_MACSTNR_TSSS_30                 (0x40000000U << ETH_MACSTNR_TSSS_Pos)               /*!< 0x40000000 */

/*************  Bit definition for ETH_MACSTSUR register  **************/
#define ETH_MACSTSUR_TSS_Pos                (0U)
#define ETH_MACSTSUR_TSS_Msk                (0xFFFFFFFFU << ETH_MACSTSUR_TSS_Pos)               /*!< 0xFFFFFFFF */
#define ETH_MACSTSUR_TSS                    ETH_MACSTSUR_TSS_Msk                                /*!< Timestamp Seconds */
#define ETH_MACSTSUR_TSS_0                  (0x1U << ETH_MACSTSUR_TSS_Pos)                      /*!< 0x00000001 */
#define ETH_MACSTSUR_TSS_1                  (0x2U << ETH_MACSTSUR_TSS_Pos)                      /*!< 0x00000002 */
#define ETH_MACSTSUR_TSS_2                  (0x4U << ETH_MACSTSUR_TSS_Pos)                      /*!< 0x00000004 */
#define ETH_MACSTSUR_TSS_3                  (0x8U << ETH_MACSTSUR_TSS_Pos)                      /*!< 0x00000008 */
#define ETH_MACSTSUR_TSS_4                  (0x10U << ETH_MACSTSUR_TSS_Pos)                     /*!< 0x00000010 */
#define ETH_MACSTSUR_TSS_5                  (0x20U << ETH_MACSTSUR_TSS_Pos)                     /*!< 0x00000020 */
#define ETH_MACSTSUR_TSS_6                  (0x40U << ETH_MACSTSUR_TSS_Pos)                     /*!< 0x00000040 */
#define ETH_MACSTSUR_TSS_7                  (0x80U << ETH_MACSTSUR_TSS_Pos)                     /*!< 0x00000080 */
#define ETH_MACSTSUR_TSS_8                  (0x100U << ETH_MACSTSUR_TSS_Pos)                    /*!< 0x00000100 */
#define ETH_MACSTSUR_TSS_9                  (0x200U << ETH_MACSTSUR_TSS_Pos)                    /*!< 0x00000200 */
#define ETH_MACSTSUR_TSS_10                 (0x400U << ETH_MACSTSUR_TSS_Pos)                    /*!< 0x00000400 */
#define ETH_MACSTSUR_TSS_11                 (0x800U << ETH_MACSTSUR_TSS_Pos)                    /*!< 0x00000800 */
#define ETH_MACSTSUR_TSS_12                 (0x1000U << ETH_MACSTSUR_TSS_Pos)                   /*!< 0x00001000 */
#define ETH_MACSTSUR_TSS_13                 (0x2000U << ETH_MACSTSUR_TSS_Pos)                   /*!< 0x00002000 */
#define ETH_MACSTSUR_TSS_14                 (0x4000U << ETH_MACSTSUR_TSS_Pos)                   /*!< 0x00004000 */
#define ETH_MACSTSUR_TSS_15                 (0x8000U << ETH_MACSTSUR_TSS_Pos)                   /*!< 0x00008000 */
#define ETH_MACSTSUR_TSS_16                 (0x10000U << ETH_MACSTSUR_TSS_Pos)                  /*!< 0x00010000 */
#define ETH_MACSTSUR_TSS_17                 (0x20000U << ETH_MACSTSUR_TSS_Pos)                  /*!< 0x00020000 */
#define ETH_MACSTSUR_TSS_18                 (0x40000U << ETH_MACSTSUR_TSS_Pos)                  /*!< 0x00040000 */
#define ETH_MACSTSUR_TSS_19                 (0x80000U << ETH_MACSTSUR_TSS_Pos)                  /*!< 0x00080000 */
#define ETH_MACSTSUR_TSS_20                 (0x100000U << ETH_MACSTSUR_TSS_Pos)                 /*!< 0x00100000 */
#define ETH_MACSTSUR_TSS_21                 (0x200000U << ETH_MACSTSUR_TSS_Pos)                 /*!< 0x00200000 */
#define ETH_MACSTSUR_TSS_22                 (0x400000U << ETH_MACSTSUR_TSS_Pos)                 /*!< 0x00400000 */
#define ETH_MACSTSUR_TSS_23                 (0x800000U << ETH_MACSTSUR_TSS_Pos)                 /*!< 0x00800000 */
#define ETH_MACSTSUR_TSS_24                 (0x1000000U << ETH_MACSTSUR_TSS_Pos)                /*!< 0x01000000 */
#define ETH_MACSTSUR_TSS_25                 (0x2000000U << ETH_MACSTSUR_TSS_Pos)                /*!< 0x02000000 */
#define ETH_MACSTSUR_TSS_26                 (0x4000000U << ETH_MACSTSUR_TSS_Pos)                /*!< 0x04000000 */
#define ETH_MACSTSUR_TSS_27                 (0x8000000U << ETH_MACSTSUR_TSS_Pos)                /*!< 0x08000000 */
#define ETH_MACSTSUR_TSS_28                 (0x10000000U << ETH_MACSTSUR_TSS_Pos)               /*!< 0x10000000 */
#define ETH_MACSTSUR_TSS_29                 (0x20000000U << ETH_MACSTSUR_TSS_Pos)               /*!< 0x20000000 */
#define ETH_MACSTSUR_TSS_30                 (0x40000000U << ETH_MACSTSUR_TSS_Pos)               /*!< 0x40000000 */
#define ETH_MACSTSUR_TSS_31                 (0x80000000U << ETH_MACSTSUR_TSS_Pos)               /*!< 0x80000000 */

/*************  Bit definition for ETH_MACSTNUR register  **************/
#define ETH_MACSTNUR_TSSS_Pos               (0U)
#define ETH_MACSTNUR_TSSS_Msk               (0x7FFFFFFFU << ETH_MACSTNUR_TSSS_Pos)              /*!< 0x7FFFFFFF */
#define ETH_MACSTNUR_TSSS                   ETH_MACSTNUR_TSSS_Msk                               /*!< Timestamp Sub-seconds */
#define ETH_MACSTNUR_TSSS_0                 (0x1U << ETH_MACSTNUR_TSSS_Pos)                     /*!< 0x00000001 */
#define ETH_MACSTNUR_TSSS_1                 (0x2U << ETH_MACSTNUR_TSSS_Pos)                     /*!< 0x00000002 */
#define ETH_MACSTNUR_TSSS_2                 (0x4U << ETH_MACSTNUR_TSSS_Pos)                     /*!< 0x00000004 */
#define ETH_MACSTNUR_TSSS_3                 (0x8U << ETH_MACSTNUR_TSSS_Pos)                     /*!< 0x00000008 */
#define ETH_MACSTNUR_TSSS_4                 (0x10U << ETH_MACSTNUR_TSSS_Pos)                    /*!< 0x00000010 */
#define ETH_MACSTNUR_TSSS_5                 (0x20U << ETH_MACSTNUR_TSSS_Pos)                    /*!< 0x00000020 */
#define ETH_MACSTNUR_TSSS_6                 (0x40U << ETH_MACSTNUR_TSSS_Pos)                    /*!< 0x00000040 */
#define ETH_MACSTNUR_TSSS_7                 (0x80U << ETH_MACSTNUR_TSSS_Pos)                    /*!< 0x00000080 */
#define ETH_MACSTNUR_TSSS_8                 (0x100U << ETH_MACSTNUR_TSSS_Pos)                   /*!< 0x00000100 */
#define ETH_MACSTNUR_TSSS_9                 (0x200U << ETH_MACSTNUR_TSSS_Pos)                   /*!< 0x00000200 */
#define ETH_MACSTNUR_TSSS_10                (0x400U << ETH_MACSTNUR_TSSS_Pos)                   /*!< 0x00000400 */
#define ETH_MACSTNUR_TSSS_11                (0x800U << ETH_MACSTNUR_TSSS_Pos)                   /*!< 0x00000800 */
#define ETH_MACSTNUR_TSSS_12                (0x1000U << ETH_MACSTNUR_TSSS_Pos)                  /*!< 0x00001000 */
#define ETH_MACSTNUR_TSSS_13                (0x2000U << ETH_MACSTNUR_TSSS_Pos)                  /*!< 0x00002000 */
#define ETH_MACSTNUR_TSSS_14                (0x4000U << ETH_MACSTNUR_TSSS_Pos)                  /*!< 0x00004000 */
#define ETH_MACSTNUR_TSSS_15                (0x8000U << ETH_MACSTNUR_TSSS_Pos)                  /*!< 0x00008000 */
#define ETH_MACSTNUR_TSSS_16                (0x10000U << ETH_MACSTNUR_TSSS_Pos)                 /*!< 0x00010000 */
#define ETH_MACSTNUR_TSSS_17                (0x20000U << ETH_MACSTNUR_TSSS_Pos)                 /*!< 0x00020000 */
#define ETH_MACSTNUR_TSSS_18                (0x40000U << ETH_MACSTNUR_TSSS_Pos)                 /*!< 0x00040000 */
#define ETH_MACSTNUR_TSSS_19                (0x80000U << ETH_MACSTNUR_TSSS_Pos)                 /*!< 0x00080000 */
#define ETH_MACSTNUR_TSSS_20                (0x100000U << ETH_MACSTNUR_TSSS_Pos)                /*!< 0x00100000 */
#define ETH_MACSTNUR_TSSS_21                (0x200000U << ETH_MACSTNUR_TSSS_Pos)                /*!< 0x00200000 */
#define ETH_MACSTNUR_TSSS_22                (0x400000U << ETH_MACSTNUR_TSSS_Pos)                /*!< 0x00400000 */
#define ETH_MACSTNUR_TSSS_23                (0x800000U << ETH_MACSTNUR_TSSS_Pos)                /*!< 0x00800000 */
#define ETH_MACSTNUR_TSSS_24                (0x1000000U << ETH_MACSTNUR_TSSS_Pos)               /*!< 0x01000000 */
#define ETH_MACSTNUR_TSSS_25                (0x2000000U << ETH_MACSTNUR_TSSS_Pos)               /*!< 0x02000000 */
#define ETH_MACSTNUR_TSSS_26                (0x4000000U << ETH_MACSTNUR_TSSS_Pos)               /*!< 0x04000000 */
#define ETH_MACSTNUR_TSSS_27                (0x8000000U << ETH_MACSTNUR_TSSS_Pos)               /*!< 0x08000000 */
#define ETH_MACSTNUR_TSSS_28                (0x10000000U << ETH_MACSTNUR_TSSS_Pos)              /*!< 0x10000000 */
#define ETH_MACSTNUR_TSSS_29                (0x20000000U << ETH_MACSTNUR_TSSS_Pos)              /*!< 0x20000000 */
#define ETH_MACSTNUR_TSSS_30                (0x40000000U << ETH_MACSTNUR_TSSS_Pos)              /*!< 0x40000000 */
#define ETH_MACSTNUR_ADDSUB_Pos             (31U)
#define ETH_MACSTNUR_ADDSUB_Msk             (0x1U << ETH_MACSTNUR_ADDSUB_Pos)                   /*!< 0x80000000 */
#define ETH_MACSTNUR_ADDSUB                 ETH_MACSTNUR_ADDSUB_Msk                             /*!< Add or Subtract Time */

/**************  Bit definition for ETH_MACTSAR register  **************/
#define ETH_MACTSAR_TSAR_Pos                (0U)
#define ETH_MACTSAR_TSAR_Msk                (0xFFFFFFFFU << ETH_MACTSAR_TSAR_Pos)               /*!< 0xFFFFFFFF */
#define ETH_MACTSAR_TSAR                    ETH_MACTSAR_TSAR_Msk                                /*!< Timestamp Addend Register */
#define ETH_MACTSAR_TSAR_0                  (0x1U << ETH_MACTSAR_TSAR_Pos)                      /*!< 0x00000001 */
#define ETH_MACTSAR_TSAR_1                  (0x2U << ETH_MACTSAR_TSAR_Pos)                      /*!< 0x00000002 */
#define ETH_MACTSAR_TSAR_2                  (0x4U << ETH_MACTSAR_TSAR_Pos)                      /*!< 0x00000004 */
#define ETH_MACTSAR_TSAR_3                  (0x8U << ETH_MACTSAR_TSAR_Pos)                      /*!< 0x00000008 */
#define ETH_MACTSAR_TSAR_4                  (0x10U << ETH_MACTSAR_TSAR_Pos)                     /*!< 0x00000010 */
#define ETH_MACTSAR_TSAR_5                  (0x20U << ETH_MACTSAR_TSAR_Pos)                     /*!< 0x00000020 */
#define ETH_MACTSAR_TSAR_6                  (0x40U << ETH_MACTSAR_TSAR_Pos)                     /*!< 0x00000040 */
#define ETH_MACTSAR_TSAR_7                  (0x80U << ETH_MACTSAR_TSAR_Pos)                     /*!< 0x00000080 */
#define ETH_MACTSAR_TSAR_8                  (0x100U << ETH_MACTSAR_TSAR_Pos)                    /*!< 0x00000100 */
#define ETH_MACTSAR_TSAR_9                  (0x200U << ETH_MACTSAR_TSAR_Pos)                    /*!< 0x00000200 */
#define ETH_MACTSAR_TSAR_10                 (0x400U << ETH_MACTSAR_TSAR_Pos)                    /*!< 0x00000400 */
#define ETH_MACTSAR_TSAR_11                 (0x800U << ETH_MACTSAR_TSAR_Pos)                    /*!< 0x00000800 */
#define ETH_MACTSAR_TSAR_12                 (0x1000U << ETH_MACTSAR_TSAR_Pos)                   /*!< 0x00001000 */
#define ETH_MACTSAR_TSAR_13                 (0x2000U << ETH_MACTSAR_TSAR_Pos)                   /*!< 0x00002000 */
#define ETH_MACTSAR_TSAR_14                 (0x4000U << ETH_MACTSAR_TSAR_Pos)                   /*!< 0x00004000 */
#define ETH_MACTSAR_TSAR_15                 (0x8000U << ETH_MACTSAR_TSAR_Pos)                   /*!< 0x00008000 */
#define ETH_MACTSAR_TSAR_16                 (0x10000U << ETH_MACTSAR_TSAR_Pos)                  /*!< 0x00010000 */
#define ETH_MACTSAR_TSAR_17                 (0x20000U << ETH_MACTSAR_TSAR_Pos)                  /*!< 0x00020000 */
#define ETH_MACTSAR_TSAR_18                 (0x40000U << ETH_MACTSAR_TSAR_Pos)                  /*!< 0x00040000 */
#define ETH_MACTSAR_TSAR_19                 (0x80000U << ETH_MACTSAR_TSAR_Pos)                  /*!< 0x00080000 */
#define ETH_MACTSAR_TSAR_20                 (0x100000U << ETH_MACTSAR_TSAR_Pos)                 /*!< 0x00100000 */
#define ETH_MACTSAR_TSAR_21                 (0x200000U << ETH_MACTSAR_TSAR_Pos)                 /*!< 0x00200000 */
#define ETH_MACTSAR_TSAR_22                 (0x400000U << ETH_MACTSAR_TSAR_Pos)                 /*!< 0x00400000 */
#define ETH_MACTSAR_TSAR_23                 (0x800000U << ETH_MACTSAR_TSAR_Pos)                 /*!< 0x00800000 */
#define ETH_MACTSAR_TSAR_24                 (0x1000000U << ETH_MACTSAR_TSAR_Pos)                /*!< 0x01000000 */
#define ETH_MACTSAR_TSAR_25                 (0x2000000U << ETH_MACTSAR_TSAR_Pos)                /*!< 0x02000000 */
#define ETH_MACTSAR_TSAR_26                 (0x4000000U << ETH_MACTSAR_TSAR_Pos)                /*!< 0x04000000 */
#define ETH_MACTSAR_TSAR_27                 (0x8000000U << ETH_MACTSAR_TSAR_Pos)                /*!< 0x08000000 */
#define ETH_MACTSAR_TSAR_28                 (0x10000000U << ETH_MACTSAR_TSAR_Pos)               /*!< 0x10000000 */
#define ETH_MACTSAR_TSAR_29                 (0x20000000U << ETH_MACTSAR_TSAR_Pos)               /*!< 0x20000000 */
#define ETH_MACTSAR_TSAR_30                 (0x40000000U << ETH_MACTSAR_TSAR_Pos)               /*!< 0x40000000 */
#define ETH_MACTSAR_TSAR_31                 (0x80000000U << ETH_MACTSAR_TSAR_Pos)               /*!< 0x80000000 */

/**************  Bit definition for ETH_MACTSSR register  **************/
#define ETH_MACTSSR_TSSOVF_Pos              (0U)
#define ETH_MACTSSR_TSSOVF_Msk              (0x1U << ETH_MACTSSR_TSSOVF_Pos)                    /*!< 0x00000001 */
#define ETH_MACTSSR_TSSOVF                  ETH_MACTSSR_TSSOVF_Msk                              /*!< Timestamp Seconds Overflow */
#define ETH_MACTSSR_TSTARGT0_Pos            (1U)
#define ETH_MACTSSR_TSTARGT0_Msk            (0x1U << ETH_MACTSSR_TSTARGT0_Pos)                  /*!< 0x00000002 */
#define ETH_MACTSSR_TSTARGT0                ETH_MACTSSR_TSTARGT0_Msk                            /*!< Timestamp Target Time Reached */
#define ETH_MACTSSR_AUXTSTRIG_Pos           (2U)
#define ETH_MACTSSR_AUXTSTRIG_Msk           (0x1U << ETH_MACTSSR_AUXTSTRIG_Pos)                 /*!< 0x00000004 */
#define ETH_MACTSSR_AUXTSTRIG               ETH_MACTSSR_AUXTSTRIG_Msk                           /*!< Auxiliary Timestamp Trigger Snapshot */
#define ETH_MACTSSR_TSTRGTERR0_Pos          (3U)
#define ETH_MACTSSR_TSTRGTERR0_Msk          (0x1U << ETH_MACTSSR_TSTRGTERR0_Pos)                /*!< 0x00000008 */
#define ETH_MACTSSR_TSTRGTERR0              ETH_MACTSSR_TSTRGTERR0_Msk                          /*!< Timestamp Target Time Error */
#define ETH_MACTSSR_TXTSSIS_Pos             (15U)
#define ETH_MACTSSR_TXTSSIS_Msk             (0x1U << ETH_MACTSSR_TXTSSIS_Pos)                   /*!< 0x00008000 */
#define ETH_MACTSSR_TXTSSIS                 ETH_MACTSSR_TXTSSIS_Msk                             /*!< Tx Timestamp Status Interrupt Status */
#define ETH_MACTSSR_ATSSTN_Pos              (16U)
#define ETH_MACTSSR_ATSSTN_Msk              (0xFU << ETH_MACTSSR_ATSSTN_Pos)                    /*!< 0x000F0000 */
#define ETH_MACTSSR_ATSSTN                  ETH_MACTSSR_ATSSTN_Msk                              /*!< Auxiliary Timestamp Snapshot Trigger Identifier */
#define ETH_MACTSSR_ATSSTN_0                (0x1U << ETH_MACTSSR_ATSSTN_Pos)                /*!< 0x00010000 */
#define ETH_MACTSSR_ATSSTN_1                (0x2U << ETH_MACTSSR_ATSSTN_Pos)                /*!< 0x00020000 */
#define ETH_MACTSSR_ATSSTN_2                (0x4U << ETH_MACTSSR_ATSSTN_Pos)                /*!< 0x00040000 */
#define ETH_MACTSSR_ATSSTN_3                (0x8U << ETH_MACTSSR_ATSSTN_Pos)                /*!< 0x00080000 */
#define ETH_MACTSSR_ATSSTM_Pos              (24U)
#define ETH_MACTSSR_ATSSTM_Msk              (0x1U << ETH_MACTSSR_ATSSTM_Pos)                    /*!< 0x01000000 */
#define ETH_MACTSSR_ATSSTM                  ETH_MACTSSR_ATSSTM_Msk                              /*!< Auxiliary Timestamp Snapshot Trigger Missed */
#define ETH_MACTSSR_ATSNS_Pos               (25U)
#define ETH_MACTSSR_ATSNS_Msk               (0x1FU << ETH_MACTSSR_ATSNS_Pos)                    /*!< 0x3E000000 */
#define ETH_MACTSSR_ATSNS                   ETH_MACTSSR_ATSNS_Msk                               /*!< Number of Auxiliary Timestamp Snapshots */
#define ETH_MACTSSR_ATSNS_0                 (0x1U << ETH_MACTSSR_ATSNS_Pos)               /*!< 0x02000000 */
#define ETH_MACTSSR_ATSNS_1                 (0x2U << ETH_MACTSSR_ATSNS_Pos)               /*!< 0x04000000 */
#define ETH_MACTSSR_ATSNS_2                 (0x4U << ETH_MACTSSR_ATSNS_Pos)               /*!< 0x08000000 */
#define ETH_MACTSSR_ATSNS_3                 (0x8U << ETH_MACTSSR_ATSNS_Pos)              /*!< 0x10000000 */
#define ETH_MACTSSR_ATSNS_4                 (0x10U << ETH_MACTSSR_ATSNS_Pos)              /*!< 0x20000000 */

/************  Bit definition for ETH_MACTXTSSNR register  *************/
#define ETH_MACTXTSSNR_TXTSSLO_Pos          (0U)
#define ETH_MACTXTSSNR_TXTSSLO_Msk          (0x7FFFFFFFU << ETH_MACTXTSSNR_TXTSSLO_Pos)         /*!< 0x7FFFFFFF */
#define ETH_MACTXTSSNR_TXTSSLO              ETH_MACTXTSSNR_TXTSSLO_Msk                          /*!< Transmit Timestamp Status Low */
#define ETH_MACTXTSSNR_TXTSSLO_0            (0x1U << ETH_MACTXTSSNR_TXTSSLO_Pos)                /*!< 0x00000001 */
#define ETH_MACTXTSSNR_TXTSSLO_1            (0x2U << ETH_MACTXTSSNR_TXTSSLO_Pos)                /*!< 0x00000002 */
#define ETH_MACTXTSSNR_TXTSSLO_2            (0x4U << ETH_MACTXTSSNR_TXTSSLO_Pos)                /*!< 0x00000004 */
#define ETH_MACTXTSSNR_TXTSSLO_3            (0x8U << ETH_MACTXTSSNR_TXTSSLO_Pos)                /*!< 0x00000008 */
#define ETH_MACTXTSSNR_TXTSSLO_4            (0x10U << ETH_MACTXTSSNR_TXTSSLO_Pos)               /*!< 0x00000010 */
#define ETH_MACTXTSSNR_TXTSSLO_5            (0x20U << ETH_MACTXTSSNR_TXTSSLO_Pos)               /*!< 0x00000020 */
#define ETH_MACTXTSSNR_TXTSSLO_6            (0x40U << ETH_MACTXTSSNR_TXTSSLO_Pos)               /*!< 0x00000040 */
#define ETH_MACTXTSSNR_TXTSSLO_7            (0x80U << ETH_MACTXTSSNR_TXTSSLO_Pos)               /*!< 0x00000080 */
#define ETH_MACTXTSSNR_TXTSSLO_8            (0x100U << ETH_MACTXTSSNR_TXTSSLO_Pos)              /*!< 0x00000100 */
#define ETH_MACTXTSSNR_TXTSSLO_9            (0x200U << ETH_MACTXTSSNR_TXTSSLO_Pos)              /*!< 0x00000200 */
#define ETH_MACTXTSSNR_TXTSSLO_10           (0x400U << ETH_MACTXTSSNR_TXTSSLO_Pos)              /*!< 0x00000400 */
#define ETH_MACTXTSSNR_TXTSSLO_11           (0x800U << ETH_MACTXTSSNR_TXTSSLO_Pos)              /*!< 0x00000800 */
#define ETH_MACTXTSSNR_TXTSSLO_12           (0x1000U << ETH_MACTXTSSNR_TXTSSLO_Pos)             /*!< 0x00001000 */
#define ETH_MACTXTSSNR_TXTSSLO_13           (0x2000U << ETH_MACTXTSSNR_TXTSSLO_Pos)             /*!< 0x00002000 */
#define ETH_MACTXTSSNR_TXTSSLO_14           (0x4000U << ETH_MACTXTSSNR_TXTSSLO_Pos)             /*!< 0x00004000 */
#define ETH_MACTXTSSNR_TXTSSLO_15           (0x8000U << ETH_MACTXTSSNR_TXTSSLO_Pos)             /*!< 0x00008000 */
#define ETH_MACTXTSSNR_TXTSSLO_16           (0x10000U << ETH_MACTXTSSNR_TXTSSLO_Pos)            /*!< 0x00010000 */
#define ETH_MACTXTSSNR_TXTSSLO_17           (0x20000U << ETH_MACTXTSSNR_TXTSSLO_Pos)            /*!< 0x00020000 */
#define ETH_MACTXTSSNR_TXTSSLO_18           (0x40000U << ETH_MACTXTSSNR_TXTSSLO_Pos)            /*!< 0x00040000 */
#define ETH_MACTXTSSNR_TXTSSLO_19           (0x80000U << ETH_MACTXTSSNR_TXTSSLO_Pos)            /*!< 0x00080000 */
#define ETH_MACTXTSSNR_TXTSSLO_20           (0x100000U << ETH_MACTXTSSNR_TXTSSLO_Pos)           /*!< 0x00100000 */
#define ETH_MACTXTSSNR_TXTSSLO_21           (0x200000U << ETH_MACTXTSSNR_TXTSSLO_Pos)           /*!< 0x00200000 */
#define ETH_MACTXTSSNR_TXTSSLO_22           (0x400000U << ETH_MACTXTSSNR_TXTSSLO_Pos)           /*!< 0x00400000 */
#define ETH_MACTXTSSNR_TXTSSLO_23           (0x800000U << ETH_MACTXTSSNR_TXTSSLO_Pos)           /*!< 0x00800000 */
#define ETH_MACTXTSSNR_TXTSSLO_24           (0x1000000U << ETH_MACTXTSSNR_TXTSSLO_Pos)          /*!< 0x01000000 */
#define ETH_MACTXTSSNR_TXTSSLO_25           (0x2000000U << ETH_MACTXTSSNR_TXTSSLO_Pos)          /*!< 0x02000000 */
#define ETH_MACTXTSSNR_TXTSSLO_26           (0x4000000U << ETH_MACTXTSSNR_TXTSSLO_Pos)          /*!< 0x04000000 */
#define ETH_MACTXTSSNR_TXTSSLO_27           (0x8000000U << ETH_MACTXTSSNR_TXTSSLO_Pos)          /*!< 0x08000000 */
#define ETH_MACTXTSSNR_TXTSSLO_28           (0x10000000U << ETH_MACTXTSSNR_TXTSSLO_Pos)         /*!< 0x10000000 */
#define ETH_MACTXTSSNR_TXTSSLO_29           (0x20000000U << ETH_MACTXTSSNR_TXTSSLO_Pos)         /*!< 0x20000000 */
#define ETH_MACTXTSSNR_TXTSSLO_30           (0x40000000U << ETH_MACTXTSSNR_TXTSSLO_Pos)         /*!< 0x40000000 */
#define ETH_MACTXTSSNR_TXTSSMIS_Pos         (31U)
#define ETH_MACTXTSSNR_TXTSSMIS_Msk         (0x1U << ETH_MACTXTSSNR_TXTSSMIS_Pos)               /*!< 0x80000000 */
#define ETH_MACTXTSSNR_TXTSSMIS             ETH_MACTXTSSNR_TXTSSMIS_Msk                         /*!< Transmit Timestamp Status Missed */

/************  Bit definition for ETH_MACTXTSSSR register  *************/
#define ETH_MACTXTSSSR_TXTSSHI_Pos          (0U)
#define ETH_MACTXTSSSR_TXTSSHI_Msk          (0xFFFFFFFFU << ETH_MACTXTSSSR_TXTSSHI_Pos)         /*!< 0xFFFFFFFF */
#define ETH_MACTXTSSSR_TXTSSHI              ETH_MACTXTSSSR_TXTSSHI_Msk                          /*!< Transmit Timestamp Status High */
#define ETH_MACTXTSSSR_TXTSSHI_0            (0x1U << ETH_MACTXTSSSR_TXTSSHI_Pos)                /*!< 0x00000001 */
#define ETH_MACTXTSSSR_TXTSSHI_1            (0x2U << ETH_MACTXTSSSR_TXTSSHI_Pos)                /*!< 0x00000002 */
#define ETH_MACTXTSSSR_TXTSSHI_2            (0x4U << ETH_MACTXTSSSR_TXTSSHI_Pos)                /*!< 0x00000004 */
#define ETH_MACTXTSSSR_TXTSSHI_3            (0x8U << ETH_MACTXTSSSR_TXTSSHI_Pos)                /*!< 0x00000008 */
#define ETH_MACTXTSSSR_TXTSSHI_4            (0x10U << ETH_MACTXTSSSR_TXTSSHI_Pos)               /*!< 0x00000010 */
#define ETH_MACTXTSSSR_TXTSSHI_5            (0x20U << ETH_MACTXTSSSR_TXTSSHI_Pos)               /*!< 0x00000020 */
#define ETH_MACTXTSSSR_TXTSSHI_6            (0x40U << ETH_MACTXTSSSR_TXTSSHI_Pos)               /*!< 0x00000040 */
#define ETH_MACTXTSSSR_TXTSSHI_7            (0x80U << ETH_MACTXTSSSR_TXTSSHI_Pos)               /*!< 0x00000080 */
#define ETH_MACTXTSSSR_TXTSSHI_8            (0x100U << ETH_MACTXTSSSR_TXTSSHI_Pos)              /*!< 0x00000100 */
#define ETH_MACTXTSSSR_TXTSSHI_9            (0x200U << ETH_MACTXTSSSR_TXTSSHI_Pos)              /*!< 0x00000200 */
#define ETH_MACTXTSSSR_TXTSSHI_10           (0x400U << ETH_MACTXTSSSR_TXTSSHI_Pos)              /*!< 0x00000400 */
#define ETH_MACTXTSSSR_TXTSSHI_11           (0x800U << ETH_MACTXTSSSR_TXTSSHI_Pos)              /*!< 0x00000800 */
#define ETH_MACTXTSSSR_TXTSSHI_12           (0x1000U << ETH_MACTXTSSSR_TXTSSHI_Pos)             /*!< 0x00001000 */
#define ETH_MACTXTSSSR_TXTSSHI_13           (0x2000U << ETH_MACTXTSSSR_TXTSSHI_Pos)             /*!< 0x00002000 */
#define ETH_MACTXTSSSR_TXTSSHI_14           (0x4000U << ETH_MACTXTSSSR_TXTSSHI_Pos)             /*!< 0x00004000 */
#define ETH_MACTXTSSSR_TXTSSHI_15           (0x8000U << ETH_MACTXTSSSR_TXTSSHI_Pos)             /*!< 0x00008000 */
#define ETH_MACTXTSSSR_TXTSSHI_16           (0x10000U << ETH_MACTXTSSSR_TXTSSHI_Pos)            /*!< 0x00010000 */
#define ETH_MACTXTSSSR_TXTSSHI_17           (0x20000U << ETH_MACTXTSSSR_TXTSSHI_Pos)            /*!< 0x00020000 */
#define ETH_MACTXTSSSR_TXTSSHI_18           (0x40000U << ETH_MACTXTSSSR_TXTSSHI_Pos)            /*!< 0x00040000 */
#define ETH_MACTXTSSSR_TXTSSHI_19           (0x80000U << ETH_MACTXTSSSR_TXTSSHI_Pos)            /*!< 0x00080000 */
#define ETH_MACTXTSSSR_TXTSSHI_20           (0x100000U << ETH_MACTXTSSSR_TXTSSHI_Pos)           /*!< 0x00100000 */
#define ETH_MACTXTSSSR_TXTSSHI_21           (0x200000U << ETH_MACTXTSSSR_TXTSSHI_Pos)           /*!< 0x00200000 */
#define ETH_MACTXTSSSR_TXTSSHI_22           (0x400000U << ETH_MACTXTSSSR_TXTSSHI_Pos)           /*!< 0x00400000 */
#define ETH_MACTXTSSSR_TXTSSHI_23           (0x800000U << ETH_MACTXTSSSR_TXTSSHI_Pos)           /*!< 0x00800000 */
#define ETH_MACTXTSSSR_TXTSSHI_24           (0x1000000U << ETH_MACTXTSSSR_TXTSSHI_Pos)          /*!< 0x01000000 */
#define ETH_MACTXTSSSR_TXTSSHI_25           (0x2000000U << ETH_MACTXTSSSR_TXTSSHI_Pos)          /*!< 0x02000000 */
#define ETH_MACTXTSSSR_TXTSSHI_26           (0x4000000U << ETH_MACTXTSSSR_TXTSSHI_Pos)          /*!< 0x04000000 */
#define ETH_MACTXTSSSR_TXTSSHI_27           (0x8000000U << ETH_MACTXTSSSR_TXTSSHI_Pos)          /*!< 0x08000000 */
#define ETH_MACTXTSSSR_TXTSSHI_28           (0x10000000U << ETH_MACTXTSSSR_TXTSSHI_Pos)         /*!< 0x10000000 */
#define ETH_MACTXTSSSR_TXTSSHI_29           (0x20000000U << ETH_MACTXTSSSR_TXTSSHI_Pos)         /*!< 0x20000000 */
#define ETH_MACTXTSSSR_TXTSSHI_30           (0x40000000U << ETH_MACTXTSSSR_TXTSSHI_Pos)         /*!< 0x40000000 */
#define ETH_MACTXTSSSR_TXTSSHI_31           (0x80000000U << ETH_MACTXTSSSR_TXTSSHI_Pos)         /*!< 0x80000000 */

/**************  Bit definition for ETH_MACACR register  ***************/
#define ETH_MACACR_ATSFC_Pos                (0U)
#define ETH_MACACR_ATSFC_Msk                (0x1U << ETH_MACACR_ATSFC_Pos)                      /*!< 0x00000001 */
#define ETH_MACACR_ATSFC                    ETH_MACACR_ATSFC_Msk                                /*!< Auxiliary Snapshot FIFO Clear */
#define ETH_MACACR_ATSEN0_Pos               (4U)
#define ETH_MACACR_ATSEN0_Msk               (0x1U << ETH_MACACR_ATSEN0_Pos)                     /*!< 0x00000010 */
#define ETH_MACACR_ATSEN0                   ETH_MACACR_ATSEN0_Msk                               /*!< Auxiliary Snapshot 0 Enable */
#define ETH_MACACR_ATSEN1_Pos               (5U)
#define ETH_MACACR_ATSEN1_Msk               (0x1U << ETH_MACACR_ATSEN1_Pos)                     /*!< 0x00000020 */
#define ETH_MACACR_ATSEN1                   ETH_MACACR_ATSEN1_Msk                               /*!< Auxiliary Snapshot 1 Enable */
#define ETH_MACACR_ATSEN2_Pos               (6U)
#define ETH_MACACR_ATSEN2_Msk               (0x1U << ETH_MACACR_ATSEN2_Pos)                     /*!< 0x00000040 */
#define ETH_MACACR_ATSEN2                   ETH_MACACR_ATSEN2_Msk                               /*!< Auxiliary Snapshot 2 Enable */
#define ETH_MACACR_ATSEN3_Pos               (7U)
#define ETH_MACACR_ATSEN3_Msk               (0x1U << ETH_MACACR_ATSEN3_Pos)                     /*!< 0x00000080 */
#define ETH_MACACR_ATSEN3                   ETH_MACACR_ATSEN3_Msk                               /*!< Auxiliary Snapshot 3 Enable */

/*************  Bit definition for ETH_MACATSNR register  **************/
#define ETH_MACATSNR_AUXTSLO_Pos            (0U)
#define ETH_MACATSNR_AUXTSLO_Msk            (0x7FFFFFFFU << ETH_MACATSNR_AUXTSLO_Pos)           /*!< 0x7FFFFFFF */
#define ETH_MACATSNR_AUXTSLO                ETH_MACATSNR_AUXTSLO_Msk                            /*!< Auxiliary Timestamp */
#define ETH_MACATSNR_AUXTSLO_0              (0x1U << ETH_MACATSNR_AUXTSLO_Pos)                  /*!< 0x00000001 */
#define ETH_MACATSNR_AUXTSLO_1              (0x2U << ETH_MACATSNR_AUXTSLO_Pos)                  /*!< 0x00000002 */
#define ETH_MACATSNR_AUXTSLO_2              (0x4U << ETH_MACATSNR_AUXTSLO_Pos)                  /*!< 0x00000004 */
#define ETH_MACATSNR_AUXTSLO_3              (0x8U << ETH_MACATSNR_AUXTSLO_Pos)                  /*!< 0x00000008 */
#define ETH_MACATSNR_AUXTSLO_4              (0x10U << ETH_MACATSNR_AUXTSLO_Pos)                 /*!< 0x00000010 */
#define ETH_MACATSNR_AUXTSLO_5              (0x20U << ETH_MACATSNR_AUXTSLO_Pos)                 /*!< 0x00000020 */
#define ETH_MACATSNR_AUXTSLO_6              (0x40U << ETH_MACATSNR_AUXTSLO_Pos)                 /*!< 0x00000040 */
#define ETH_MACATSNR_AUXTSLO_7              (0x80U << ETH_MACATSNR_AUXTSLO_Pos)                 /*!< 0x00000080 */
#define ETH_MACATSNR_AUXTSLO_8              (0x100U << ETH_MACATSNR_AUXTSLO_Pos)                /*!< 0x00000100 */
#define ETH_MACATSNR_AUXTSLO_9              (0x200U << ETH_MACATSNR_AUXTSLO_Pos)                /*!< 0x00000200 */
#define ETH_MACATSNR_AUXTSLO_10             (0x400U << ETH_MACATSNR_AUXTSLO_Pos)                /*!< 0x00000400 */
#define ETH_MACATSNR_AUXTSLO_11             (0x800U << ETH_MACATSNR_AUXTSLO_Pos)                /*!< 0x00000800 */
#define ETH_MACATSNR_AUXTSLO_12             (0x1000U << ETH_MACATSNR_AUXTSLO_Pos)               /*!< 0x00001000 */
#define ETH_MACATSNR_AUXTSLO_13             (0x2000U << ETH_MACATSNR_AUXTSLO_Pos)               /*!< 0x00002000 */
#define ETH_MACATSNR_AUXTSLO_14             (0x4000U << ETH_MACATSNR_AUXTSLO_Pos)               /*!< 0x00004000 */
#define ETH_MACATSNR_AUXTSLO_15             (0x8000U << ETH_MACATSNR_AUXTSLO_Pos)               /*!< 0x00008000 */
#define ETH_MACATSNR_AUXTSLO_16             (0x10000U << ETH_MACATSNR_AUXTSLO_Pos)              /*!< 0x00010000 */
#define ETH_MACATSNR_AUXTSLO_17             (0x20000U << ETH_MACATSNR_AUXTSLO_Pos)              /*!< 0x00020000 */
#define ETH_MACATSNR_AUXTSLO_18             (0x40000U << ETH_MACATSNR_AUXTSLO_Pos)              /*!< 0x00040000 */
#define ETH_MACATSNR_AUXTSLO_19             (0x80000U << ETH_MACATSNR_AUXTSLO_Pos)              /*!< 0x00080000 */
#define ETH_MACATSNR_AUXTSLO_20             (0x100000U << ETH_MACATSNR_AUXTSLO_Pos)             /*!< 0x00100000 */
#define ETH_MACATSNR_AUXTSLO_21             (0x200000U << ETH_MACATSNR_AUXTSLO_Pos)             /*!< 0x00200000 */
#define ETH_MACATSNR_AUXTSLO_22             (0x400000U << ETH_MACATSNR_AUXTSLO_Pos)             /*!< 0x00400000 */
#define ETH_MACATSNR_AUXTSLO_23             (0x800000U << ETH_MACATSNR_AUXTSLO_Pos)             /*!< 0x00800000 */
#define ETH_MACATSNR_AUXTSLO_24             (0x1000000U << ETH_MACATSNR_AUXTSLO_Pos)            /*!< 0x01000000 */
#define ETH_MACATSNR_AUXTSLO_25             (0x2000000U << ETH_MACATSNR_AUXTSLO_Pos)            /*!< 0x02000000 */
#define ETH_MACATSNR_AUXTSLO_26             (0x4000000U << ETH_MACATSNR_AUXTSLO_Pos)            /*!< 0x04000000 */
#define ETH_MACATSNR_AUXTSLO_27             (0x8000000U << ETH_MACATSNR_AUXTSLO_Pos)            /*!< 0x08000000 */
#define ETH_MACATSNR_AUXTSLO_28             (0x10000000U << ETH_MACATSNR_AUXTSLO_Pos)           /*!< 0x10000000 */
#define ETH_MACATSNR_AUXTSLO_29             (0x20000000U << ETH_MACATSNR_AUXTSLO_Pos)           /*!< 0x20000000 */
#define ETH_MACATSNR_AUXTSLO_30             (0x40000000U << ETH_MACATSNR_AUXTSLO_Pos)           /*!< 0x40000000 */

/*************  Bit definition for ETH_MACATSSR register  **************/
#define ETH_MACATSSR_AUXTSHI_Pos            (0U)
#define ETH_MACATSSR_AUXTSHI_Msk            (0xFFFFFFFFU << ETH_MACATSSR_AUXTSHI_Pos)           /*!< 0xFFFFFFFF */
#define ETH_MACATSSR_AUXTSHI                ETH_MACATSSR_AUXTSHI_Msk                            /*!< Auxiliary Timestamp */
#define ETH_MACATSSR_AUXTSHI_0              (0x1U << ETH_MACATSSR_AUXTSHI_Pos)                  /*!< 0x00000001 */
#define ETH_MACATSSR_AUXTSHI_1              (0x2U << ETH_MACATSSR_AUXTSHI_Pos)                  /*!< 0x00000002 */
#define ETH_MACATSSR_AUXTSHI_2              (0x4U << ETH_MACATSSR_AUXTSHI_Pos)                  /*!< 0x00000004 */
#define ETH_MACATSSR_AUXTSHI_3              (0x8U << ETH_MACATSSR_AUXTSHI_Pos)                  /*!< 0x00000008 */
#define ETH_MACATSSR_AUXTSHI_4              (0x10U << ETH_MACATSSR_AUXTSHI_Pos)                 /*!< 0x00000010 */
#define ETH_MACATSSR_AUXTSHI_5              (0x20U << ETH_MACATSSR_AUXTSHI_Pos)                 /*!< 0x00000020 */
#define ETH_MACATSSR_AUXTSHI_6              (0x40U << ETH_MACATSSR_AUXTSHI_Pos)                 /*!< 0x00000040 */
#define ETH_MACATSSR_AUXTSHI_7              (0x80U << ETH_MACATSSR_AUXTSHI_Pos)                 /*!< 0x00000080 */
#define ETH_MACATSSR_AUXTSHI_8              (0x100U << ETH_MACATSSR_AUXTSHI_Pos)                /*!< 0x00000100 */
#define ETH_MACATSSR_AUXTSHI_9              (0x200U << ETH_MACATSSR_AUXTSHI_Pos)                /*!< 0x00000200 */
#define ETH_MACATSSR_AUXTSHI_10             (0x400U << ETH_MACATSSR_AUXTSHI_Pos)                /*!< 0x00000400 */
#define ETH_MACATSSR_AUXTSHI_11             (0x800U << ETH_MACATSSR_AUXTSHI_Pos)                /*!< 0x00000800 */
#define ETH_MACATSSR_AUXTSHI_12             (0x1000U << ETH_MACATSSR_AUXTSHI_Pos)               /*!< 0x00001000 */
#define ETH_MACATSSR_AUXTSHI_13             (0x2000U << ETH_MACATSSR_AUXTSHI_Pos)               /*!< 0x00002000 */
#define ETH_MACATSSR_AUXTSHI_14             (0x4000U << ETH_MACATSSR_AUXTSHI_Pos)               /*!< 0x00004000 */
#define ETH_MACATSSR_AUXTSHI_15             (0x8000U << ETH_MACATSSR_AUXTSHI_Pos)               /*!< 0x00008000 */
#define ETH_MACATSSR_AUXTSHI_16             (0x10000U << ETH_MACATSSR_AUXTSHI_Pos)              /*!< 0x00010000 */
#define ETH_MACATSSR_AUXTSHI_17             (0x20000U << ETH_MACATSSR_AUXTSHI_Pos)              /*!< 0x00020000 */
#define ETH_MACATSSR_AUXTSHI_18             (0x40000U << ETH_MACATSSR_AUXTSHI_Pos)              /*!< 0x00040000 */
#define ETH_MACATSSR_AUXTSHI_19             (0x80000U << ETH_MACATSSR_AUXTSHI_Pos)              /*!< 0x00080000 */
#define ETH_MACATSSR_AUXTSHI_20             (0x100000U << ETH_MACATSSR_AUXTSHI_Pos)             /*!< 0x00100000 */
#define ETH_MACATSSR_AUXTSHI_21             (0x200000U << ETH_MACATSSR_AUXTSHI_Pos)             /*!< 0x00200000 */
#define ETH_MACATSSR_AUXTSHI_22             (0x400000U << ETH_MACATSSR_AUXTSHI_Pos)             /*!< 0x00400000 */
#define ETH_MACATSSR_AUXTSHI_23             (0x800000U << ETH_MACATSSR_AUXTSHI_Pos)             /*!< 0x00800000 */
#define ETH_MACATSSR_AUXTSHI_24             (0x1000000U << ETH_MACATSSR_AUXTSHI_Pos)            /*!< 0x01000000 */
#define ETH_MACATSSR_AUXTSHI_25             (0x2000000U << ETH_MACATSSR_AUXTSHI_Pos)            /*!< 0x02000000 */
#define ETH_MACATSSR_AUXTSHI_26             (0x4000000U << ETH_MACATSSR_AUXTSHI_Pos)            /*!< 0x04000000 */
#define ETH_MACATSSR_AUXTSHI_27             (0x8000000U << ETH_MACATSSR_AUXTSHI_Pos)            /*!< 0x08000000 */
#define ETH_MACATSSR_AUXTSHI_28             (0x10000000U << ETH_MACATSSR_AUXTSHI_Pos)           /*!< 0x10000000 */
#define ETH_MACATSSR_AUXTSHI_29             (0x20000000U << ETH_MACATSSR_AUXTSHI_Pos)           /*!< 0x20000000 */
#define ETH_MACATSSR_AUXTSHI_30             (0x40000000U << ETH_MACATSSR_AUXTSHI_Pos)           /*!< 0x40000000 */
#define ETH_MACATSSR_AUXTSHI_31             (0x80000000U << ETH_MACATSSR_AUXTSHI_Pos)           /*!< 0x80000000 */

/*************  Bit definition for ETH_MACTSIACR register  *************/
#define ETH_MACTSIACR_OSTIAC_Pos            (0U)
#define ETH_MACTSIACR_OSTIAC_Msk            (0xFFFFFFFFU << ETH_MACTSIACR_OSTIAC_Pos)           /*!< 0xFFFFFFFF */
#define ETH_MACTSIACR_OSTIAC                ETH_MACTSIACR_OSTIAC_Msk                            /*!< One-Step Timestamp Ingress Asymmetry Correction */
#define ETH_MACTSIACR_OSTIAC_0              (0x1U << ETH_MACTSIACR_OSTIAC_Pos)                  /*!< 0x00000001 */
#define ETH_MACTSIACR_OSTIAC_1              (0x2U << ETH_MACTSIACR_OSTIAC_Pos)                  /*!< 0x00000002 */
#define ETH_MACTSIACR_OSTIAC_2              (0x4U << ETH_MACTSIACR_OSTIAC_Pos)                  /*!< 0x00000004 */
#define ETH_MACTSIACR_OSTIAC_3              (0x8U << ETH_MACTSIACR_OSTIAC_Pos)                  /*!< 0x00000008 */
#define ETH_MACTSIACR_OSTIAC_4              (0x10U << ETH_MACTSIACR_OSTIAC_Pos)                 /*!< 0x00000010 */
#define ETH_MACTSIACR_OSTIAC_5              (0x20U << ETH_MACTSIACR_OSTIAC_Pos)                 /*!< 0x00000020 */
#define ETH_MACTSIACR_OSTIAC_6              (0x40U << ETH_MACTSIACR_OSTIAC_Pos)                 /*!< 0x00000040 */
#define ETH_MACTSIACR_OSTIAC_7              (0x80U << ETH_MACTSIACR_OSTIAC_Pos)                 /*!< 0x00000080 */
#define ETH_MACTSIACR_OSTIAC_8              (0x100U << ETH_MACTSIACR_OSTIAC_Pos)                /*!< 0x00000100 */
#define ETH_MACTSIACR_OSTIAC_9              (0x200U << ETH_MACTSIACR_OSTIAC_Pos)                /*!< 0x00000200 */
#define ETH_MACTSIACR_OSTIAC_10             (0x400U << ETH_MACTSIACR_OSTIAC_Pos)                /*!< 0x00000400 */
#define ETH_MACTSIACR_OSTIAC_11             (0x800U << ETH_MACTSIACR_OSTIAC_Pos)                /*!< 0x00000800 */
#define ETH_MACTSIACR_OSTIAC_12             (0x1000U << ETH_MACTSIACR_OSTIAC_Pos)               /*!< 0x00001000 */
#define ETH_MACTSIACR_OSTIAC_13             (0x2000U << ETH_MACTSIACR_OSTIAC_Pos)               /*!< 0x00002000 */
#define ETH_MACTSIACR_OSTIAC_14             (0x4000U << ETH_MACTSIACR_OSTIAC_Pos)               /*!< 0x00004000 */
#define ETH_MACTSIACR_OSTIAC_15             (0x8000U << ETH_MACTSIACR_OSTIAC_Pos)               /*!< 0x00008000 */
#define ETH_MACTSIACR_OSTIAC_16             (0x10000U << ETH_MACTSIACR_OSTIAC_Pos)              /*!< 0x00010000 */
#define ETH_MACTSIACR_OSTIAC_17             (0x20000U << ETH_MACTSIACR_OSTIAC_Pos)              /*!< 0x00020000 */
#define ETH_MACTSIACR_OSTIAC_18             (0x40000U << ETH_MACTSIACR_OSTIAC_Pos)              /*!< 0x00040000 */
#define ETH_MACTSIACR_OSTIAC_19             (0x80000U << ETH_MACTSIACR_OSTIAC_Pos)              /*!< 0x00080000 */
#define ETH_MACTSIACR_OSTIAC_20             (0x100000U << ETH_MACTSIACR_OSTIAC_Pos)             /*!< 0x00100000 */
#define ETH_MACTSIACR_OSTIAC_21             (0x200000U << ETH_MACTSIACR_OSTIAC_Pos)             /*!< 0x00200000 */
#define ETH_MACTSIACR_OSTIAC_22             (0x400000U << ETH_MACTSIACR_OSTIAC_Pos)             /*!< 0x00400000 */
#define ETH_MACTSIACR_OSTIAC_23             (0x800000U << ETH_MACTSIACR_OSTIAC_Pos)             /*!< 0x00800000 */
#define ETH_MACTSIACR_OSTIAC_24             (0x1000000U << ETH_MACTSIACR_OSTIAC_Pos)            /*!< 0x01000000 */
#define ETH_MACTSIACR_OSTIAC_25             (0x2000000U << ETH_MACTSIACR_OSTIAC_Pos)            /*!< 0x02000000 */
#define ETH_MACTSIACR_OSTIAC_26             (0x4000000U << ETH_MACTSIACR_OSTIAC_Pos)            /*!< 0x04000000 */
#define ETH_MACTSIACR_OSTIAC_27             (0x8000000U << ETH_MACTSIACR_OSTIAC_Pos)            /*!< 0x08000000 */
#define ETH_MACTSIACR_OSTIAC_28             (0x10000000U << ETH_MACTSIACR_OSTIAC_Pos)           /*!< 0x10000000 */
#define ETH_MACTSIACR_OSTIAC_29             (0x20000000U << ETH_MACTSIACR_OSTIAC_Pos)           /*!< 0x20000000 */
#define ETH_MACTSIACR_OSTIAC_30             (0x40000000U << ETH_MACTSIACR_OSTIAC_Pos)           /*!< 0x40000000 */
#define ETH_MACTSIACR_OSTIAC_31             (0x80000000U << ETH_MACTSIACR_OSTIAC_Pos)           /*!< 0x80000000 */

/*************  Bit definition for ETH_MACTSEACR register  *************/
#define ETH_MACTSEACR_OSTEAC_Pos            (0U)
#define ETH_MACTSEACR_OSTEAC_Msk            (0xFFFFFFFFU << ETH_MACTSEACR_OSTEAC_Pos)           /*!< 0xFFFFFFFF */
#define ETH_MACTSEACR_OSTEAC                ETH_MACTSEACR_OSTEAC_Msk                            /*!< One-Step Timestamp Egress Asymmetry Correction */
#define ETH_MACTSEACR_OSTEAC_0              (0x1U << ETH_MACTSEACR_OSTEAC_Pos)                  /*!< 0x00000001 */
#define ETH_MACTSEACR_OSTEAC_1              (0x2U << ETH_MACTSEACR_OSTEAC_Pos)                  /*!< 0x00000002 */
#define ETH_MACTSEACR_OSTEAC_2              (0x4U << ETH_MACTSEACR_OSTEAC_Pos)                  /*!< 0x00000004 */
#define ETH_MACTSEACR_OSTEAC_3              (0x8U << ETH_MACTSEACR_OSTEAC_Pos)                  /*!< 0x00000008 */
#define ETH_MACTSEACR_OSTEAC_4              (0x10U << ETH_MACTSEACR_OSTEAC_Pos)                 /*!< 0x00000010 */
#define ETH_MACTSEACR_OSTEAC_5              (0x20U << ETH_MACTSEACR_OSTEAC_Pos)                 /*!< 0x00000020 */
#define ETH_MACTSEACR_OSTEAC_6              (0x40U << ETH_MACTSEACR_OSTEAC_Pos)                 /*!< 0x00000040 */
#define ETH_MACTSEACR_OSTEAC_7              (0x80U << ETH_MACTSEACR_OSTEAC_Pos)                 /*!< 0x00000080 */
#define ETH_MACTSEACR_OSTEAC_8              (0x100U << ETH_MACTSEACR_OSTEAC_Pos)                /*!< 0x00000100 */
#define ETH_MACTSEACR_OSTEAC_9              (0x200U << ETH_MACTSEACR_OSTEAC_Pos)                /*!< 0x00000200 */
#define ETH_MACTSEACR_OSTEAC_10             (0x400U << ETH_MACTSEACR_OSTEAC_Pos)                /*!< 0x00000400 */
#define ETH_MACTSEACR_OSTEAC_11             (0x800U << ETH_MACTSEACR_OSTEAC_Pos)                /*!< 0x00000800 */
#define ETH_MACTSEACR_OSTEAC_12             (0x1000U << ETH_MACTSEACR_OSTEAC_Pos)               /*!< 0x00001000 */
#define ETH_MACTSEACR_OSTEAC_13             (0x2000U << ETH_MACTSEACR_OSTEAC_Pos)               /*!< 0x00002000 */
#define ETH_MACTSEACR_OSTEAC_14             (0x4000U << ETH_MACTSEACR_OSTEAC_Pos)               /*!< 0x00004000 */
#define ETH_MACTSEACR_OSTEAC_15             (0x8000U << ETH_MACTSEACR_OSTEAC_Pos)               /*!< 0x00008000 */
#define ETH_MACTSEACR_OSTEAC_16             (0x10000U << ETH_MACTSEACR_OSTEAC_Pos)              /*!< 0x00010000 */
#define ETH_MACTSEACR_OSTEAC_17             (0x20000U << ETH_MACTSEACR_OSTEAC_Pos)              /*!< 0x00020000 */
#define ETH_MACTSEACR_OSTEAC_18             (0x40000U << ETH_MACTSEACR_OSTEAC_Pos)              /*!< 0x00040000 */
#define ETH_MACTSEACR_OSTEAC_19             (0x80000U << ETH_MACTSEACR_OSTEAC_Pos)              /*!< 0x00080000 */
#define ETH_MACTSEACR_OSTEAC_20             (0x100000U << ETH_MACTSEACR_OSTEAC_Pos)             /*!< 0x00100000 */
#define ETH_MACTSEACR_OSTEAC_21             (0x200000U << ETH_MACTSEACR_OSTEAC_Pos)             /*!< 0x00200000 */
#define ETH_MACTSEACR_OSTEAC_22             (0x400000U << ETH_MACTSEACR_OSTEAC_Pos)             /*!< 0x00400000 */
#define ETH_MACTSEACR_OSTEAC_23             (0x800000U << ETH_MACTSEACR_OSTEAC_Pos)             /*!< 0x00800000 */
#define ETH_MACTSEACR_OSTEAC_24             (0x1000000U << ETH_MACTSEACR_OSTEAC_Pos)            /*!< 0x01000000 */
#define ETH_MACTSEACR_OSTEAC_25             (0x2000000U << ETH_MACTSEACR_OSTEAC_Pos)            /*!< 0x02000000 */
#define ETH_MACTSEACR_OSTEAC_26             (0x4000000U << ETH_MACTSEACR_OSTEAC_Pos)            /*!< 0x04000000 */
#define ETH_MACTSEACR_OSTEAC_27             (0x8000000U << ETH_MACTSEACR_OSTEAC_Pos)            /*!< 0x08000000 */
#define ETH_MACTSEACR_OSTEAC_28             (0x10000000U << ETH_MACTSEACR_OSTEAC_Pos)           /*!< 0x10000000 */
#define ETH_MACTSEACR_OSTEAC_29             (0x20000000U << ETH_MACTSEACR_OSTEAC_Pos)           /*!< 0x20000000 */
#define ETH_MACTSEACR_OSTEAC_30             (0x40000000U << ETH_MACTSEACR_OSTEAC_Pos)           /*!< 0x40000000 */
#define ETH_MACTSEACR_OSTEAC_31             (0x80000000U << ETH_MACTSEACR_OSTEAC_Pos)           /*!< 0x80000000 */

/*************  Bit definition for ETH_MACTSICNR register  *************/
#define ETH_MACTSICNR_TSIC_Pos              (0U)
#define ETH_MACTSICNR_TSIC_Msk              (0xFFFFFFFFU << ETH_MACTSICNR_TSIC_Pos)             /*!< 0xFFFFFFFF */
#define ETH_MACTSICNR_TSIC                  ETH_MACTSICNR_TSIC_Msk                              /*!< Timestamp Ingress Correction */
#define ETH_MACTSICNR_TSIC_0                (0x1U << ETH_MACTSICNR_TSIC_Pos)                    /*!< 0x00000001 */
#define ETH_MACTSICNR_TSIC_1                (0x2U << ETH_MACTSICNR_TSIC_Pos)                    /*!< 0x00000002 */
#define ETH_MACTSICNR_TSIC_2                (0x4U << ETH_MACTSICNR_TSIC_Pos)                    /*!< 0x00000004 */
#define ETH_MACTSICNR_TSIC_3                (0x8U << ETH_MACTSICNR_TSIC_Pos)                    /*!< 0x00000008 */
#define ETH_MACTSICNR_TSIC_4                (0x10U << ETH_MACTSICNR_TSIC_Pos)                   /*!< 0x00000010 */
#define ETH_MACTSICNR_TSIC_5                (0x20U << ETH_MACTSICNR_TSIC_Pos)                   /*!< 0x00000020 */
#define ETH_MACTSICNR_TSIC_6                (0x40U << ETH_MACTSICNR_TSIC_Pos)                   /*!< 0x00000040 */
#define ETH_MACTSICNR_TSIC_7                (0x80U << ETH_MACTSICNR_TSIC_Pos)                   /*!< 0x00000080 */
#define ETH_MACTSICNR_TSIC_8                (0x100U << ETH_MACTSICNR_TSIC_Pos)                  /*!< 0x00000100 */
#define ETH_MACTSICNR_TSIC_9                (0x200U << ETH_MACTSICNR_TSIC_Pos)                  /*!< 0x00000200 */
#define ETH_MACTSICNR_TSIC_10               (0x400U << ETH_MACTSICNR_TSIC_Pos)                  /*!< 0x00000400 */
#define ETH_MACTSICNR_TSIC_11               (0x800U << ETH_MACTSICNR_TSIC_Pos)                  /*!< 0x00000800 */
#define ETH_MACTSICNR_TSIC_12               (0x1000U << ETH_MACTSICNR_TSIC_Pos)                 /*!< 0x00001000 */
#define ETH_MACTSICNR_TSIC_13               (0x2000U << ETH_MACTSICNR_TSIC_Pos)                 /*!< 0x00002000 */
#define ETH_MACTSICNR_TSIC_14               (0x4000U << ETH_MACTSICNR_TSIC_Pos)                 /*!< 0x00004000 */
#define ETH_MACTSICNR_TSIC_15               (0x8000U << ETH_MACTSICNR_TSIC_Pos)                 /*!< 0x00008000 */
#define ETH_MACTSICNR_TSIC_16               (0x10000U << ETH_MACTSICNR_TSIC_Pos)                /*!< 0x00010000 */
#define ETH_MACTSICNR_TSIC_17               (0x20000U << ETH_MACTSICNR_TSIC_Pos)                /*!< 0x00020000 */
#define ETH_MACTSICNR_TSIC_18               (0x40000U << ETH_MACTSICNR_TSIC_Pos)                /*!< 0x00040000 */
#define ETH_MACTSICNR_TSIC_19               (0x80000U << ETH_MACTSICNR_TSIC_Pos)                /*!< 0x00080000 */
#define ETH_MACTSICNR_TSIC_20               (0x100000U << ETH_MACTSICNR_TSIC_Pos)               /*!< 0x00100000 */
#define ETH_MACTSICNR_TSIC_21               (0x200000U << ETH_MACTSICNR_TSIC_Pos)               /*!< 0x00200000 */
#define ETH_MACTSICNR_TSIC_22               (0x400000U << ETH_MACTSICNR_TSIC_Pos)               /*!< 0x00400000 */
#define ETH_MACTSICNR_TSIC_23               (0x800000U << ETH_MACTSICNR_TSIC_Pos)               /*!< 0x00800000 */
#define ETH_MACTSICNR_TSIC_24               (0x1000000U << ETH_MACTSICNR_TSIC_Pos)              /*!< 0x01000000 */
#define ETH_MACTSICNR_TSIC_25               (0x2000000U << ETH_MACTSICNR_TSIC_Pos)              /*!< 0x02000000 */
#define ETH_MACTSICNR_TSIC_26               (0x4000000U << ETH_MACTSICNR_TSIC_Pos)              /*!< 0x04000000 */
#define ETH_MACTSICNR_TSIC_27               (0x8000000U << ETH_MACTSICNR_TSIC_Pos)              /*!< 0x08000000 */
#define ETH_MACTSICNR_TSIC_28               (0x10000000U << ETH_MACTSICNR_TSIC_Pos)             /*!< 0x10000000 */
#define ETH_MACTSICNR_TSIC_29               (0x20000000U << ETH_MACTSICNR_TSIC_Pos)             /*!< 0x20000000 */
#define ETH_MACTSICNR_TSIC_30               (0x40000000U << ETH_MACTSICNR_TSIC_Pos)             /*!< 0x40000000 */
#define ETH_MACTSICNR_TSIC_31               (0x80000000U << ETH_MACTSICNR_TSIC_Pos)             /*!< 0x80000000 */

/*************  Bit definition for ETH_MACTSECNR register  *************/
#define ETH_MACTSECNR_TSEC_Pos              (0U)
#define ETH_MACTSECNR_TSEC_Msk              (0xFFFFFFFFU << ETH_MACTSECNR_TSEC_Pos)             /*!< 0xFFFFFFFF */
#define ETH_MACTSECNR_TSEC                  ETH_MACTSECNR_TSEC_Msk                              /*!< Timestamp Egress Correction */
#define ETH_MACTSECNR_TSEC_0                (0x1U << ETH_MACTSECNR_TSEC_Pos)                    /*!< 0x00000001 */
#define ETH_MACTSECNR_TSEC_1                (0x2U << ETH_MACTSECNR_TSEC_Pos)                    /*!< 0x00000002 */
#define ETH_MACTSECNR_TSEC_2                (0x4U << ETH_MACTSECNR_TSEC_Pos)                    /*!< 0x00000004 */
#define ETH_MACTSECNR_TSEC_3                (0x8U << ETH_MACTSECNR_TSEC_Pos)                    /*!< 0x00000008 */
#define ETH_MACTSECNR_TSEC_4                (0x10U << ETH_MACTSECNR_TSEC_Pos)                   /*!< 0x00000010 */
#define ETH_MACTSECNR_TSEC_5                (0x20U << ETH_MACTSECNR_TSEC_Pos)                   /*!< 0x00000020 */
#define ETH_MACTSECNR_TSEC_6                (0x40U << ETH_MACTSECNR_TSEC_Pos)                   /*!< 0x00000040 */
#define ETH_MACTSECNR_TSEC_7                (0x80U << ETH_MACTSECNR_TSEC_Pos)                   /*!< 0x00000080 */
#define ETH_MACTSECNR_TSEC_8                (0x100U << ETH_MACTSECNR_TSEC_Pos)                  /*!< 0x00000100 */
#define ETH_MACTSECNR_TSEC_9                (0x200U << ETH_MACTSECNR_TSEC_Pos)                  /*!< 0x00000200 */
#define ETH_MACTSECNR_TSEC_10               (0x400U << ETH_MACTSECNR_TSEC_Pos)                  /*!< 0x00000400 */
#define ETH_MACTSECNR_TSEC_11               (0x800U << ETH_MACTSECNR_TSEC_Pos)                  /*!< 0x00000800 */
#define ETH_MACTSECNR_TSEC_12               (0x1000U << ETH_MACTSECNR_TSEC_Pos)                 /*!< 0x00001000 */
#define ETH_MACTSECNR_TSEC_13               (0x2000U << ETH_MACTSECNR_TSEC_Pos)                 /*!< 0x00002000 */
#define ETH_MACTSECNR_TSEC_14               (0x4000U << ETH_MACTSECNR_TSEC_Pos)                 /*!< 0x00004000 */
#define ETH_MACTSECNR_TSEC_15               (0x8000U << ETH_MACTSECNR_TSEC_Pos)                 /*!< 0x00008000 */
#define ETH_MACTSECNR_TSEC_16               (0x10000U << ETH_MACTSECNR_TSEC_Pos)                /*!< 0x00010000 */
#define ETH_MACTSECNR_TSEC_17               (0x20000U << ETH_MACTSECNR_TSEC_Pos)                /*!< 0x00020000 */
#define ETH_MACTSECNR_TSEC_18               (0x40000U << ETH_MACTSECNR_TSEC_Pos)                /*!< 0x00040000 */
#define ETH_MACTSECNR_TSEC_19               (0x80000U << ETH_MACTSECNR_TSEC_Pos)                /*!< 0x00080000 */
#define ETH_MACTSECNR_TSEC_20               (0x100000U << ETH_MACTSECNR_TSEC_Pos)               /*!< 0x00100000 */
#define ETH_MACTSECNR_TSEC_21               (0x200000U << ETH_MACTSECNR_TSEC_Pos)               /*!< 0x00200000 */
#define ETH_MACTSECNR_TSEC_22               (0x400000U << ETH_MACTSECNR_TSEC_Pos)               /*!< 0x00400000 */
#define ETH_MACTSECNR_TSEC_23               (0x800000U << ETH_MACTSECNR_TSEC_Pos)               /*!< 0x00800000 */
#define ETH_MACTSECNR_TSEC_24               (0x1000000U << ETH_MACTSECNR_TSEC_Pos)              /*!< 0x01000000 */
#define ETH_MACTSECNR_TSEC_25               (0x2000000U << ETH_MACTSECNR_TSEC_Pos)              /*!< 0x02000000 */
#define ETH_MACTSECNR_TSEC_26               (0x4000000U << ETH_MACTSECNR_TSEC_Pos)              /*!< 0x04000000 */
#define ETH_MACTSECNR_TSEC_27               (0x8000000U << ETH_MACTSECNR_TSEC_Pos)              /*!< 0x08000000 */
#define ETH_MACTSECNR_TSEC_28               (0x10000000U << ETH_MACTSECNR_TSEC_Pos)             /*!< 0x10000000 */
#define ETH_MACTSECNR_TSEC_29               (0x20000000U << ETH_MACTSECNR_TSEC_Pos)             /*!< 0x20000000 */
#define ETH_MACTSECNR_TSEC_30               (0x40000000U << ETH_MACTSECNR_TSEC_Pos)             /*!< 0x40000000 */
#define ETH_MACTSECNR_TSEC_31               (0x80000000U << ETH_MACTSECNR_TSEC_Pos)             /*!< 0x80000000 */

/*************  Bit definition for ETH_MACPPSCR register  **************/
#define ETH_MACPPSCR_PPSCTRL_Pos            (0U)
#define ETH_MACPPSCR_PPSCTRL_Msk            (0xFU << ETH_MACPPSCR_PPSCTRL_Pos)                  /*!< 0x0000000F */
#define ETH_MACPPSCR_PPSCTRL                ETH_MACPPSCR_PPSCTRL_Msk                            /*!< PPS Output Frequency Control */
#define ETH_MACPPSCR_PPSCTRL_0              (0x1U << ETH_MACPPSCR_PPSCTRL_Pos)                  /*!< 0x00000001 */
#define ETH_MACPPSCR_PPSCTRL_1              (0x2U << ETH_MACPPSCR_PPSCTRL_Pos)                  /*!< 0x00000002 */
#define ETH_MACPPSCR_PPSCTRL_2              (0x4U << ETH_MACPPSCR_PPSCTRL_Pos)                  /*!< 0x00000004 */
#define ETH_MACPPSCR_PPSCTRL_3              (0x8U << ETH_MACPPSCR_PPSCTRL_Pos)                  /*!< 0x00000008 */
#define ETH_MACPPSCR_PPSEN0_Pos             (4U)
#define ETH_MACPPSCR_PPSEN0_Msk             (0x1U << ETH_MACPPSCR_PPSEN0_Pos)                   /*!< 0x00000010 */
#define ETH_MACPPSCR_PPSEN0                 ETH_MACPPSCR_PPSEN0_Msk                             /*!< Flexible PPS Output Mode Enable */
#define ETH_MACPPSCR_TRGTMODSEL0_Pos        (5U)
#define ETH_MACPPSCR_TRGTMODSEL0_Msk        (0x3U << ETH_MACPPSCR_TRGTMODSEL0_Pos)              /*!< 0x00000060 */
#define ETH_MACPPSCR_TRGTMODSEL0            ETH_MACPPSCR_TRGTMODSEL0_Msk                        /*!< Target Time Register Mode for PPS Output */
#define ETH_MACPPSCR_TRGTMODSEL0_0          (0x1U << ETH_MACPPSCR_TRGTMODSEL0_Pos)             /*!< 0x00000020 */
#define ETH_MACPPSCR_TRGTMODSEL0_1          (0x2U << ETH_MACPPSCR_TRGTMODSEL0_Pos)             /*!< 0x00000040 */
#define ETH_MACPPSCR_PPSCMD_Pos             (0U)
#define ETH_MACPPSCR_PPSCMD_Msk             (0xFU << ETH_MACPPSCR_PPSCMD_Pos)                   /*!< 0x0000000F */
#define ETH_MACPPSCR_PPSCMD                 ETH_MACPPSCR_PPSCMD_Msk                             /*!< Flexible PPS Output (ptp_pps_o[0]) Control */
#define ETH_MACPPSCR_PPSCMD_0               (0x1U << ETH_MACPPSCR_PPSCMD_Pos)                   /*!< 0x00000001 */
#define ETH_MACPPSCR_PPSCMD_1               (0x2U << ETH_MACPPSCR_PPSCMD_Pos)                   /*!< 0x00000002 */
#define ETH_MACPPSCR_PPSCMD_2               (0x4U << ETH_MACPPSCR_PPSCMD_Pos)                   /*!< 0x00000004 */
#define ETH_MACPPSCR_PPSCMD_3               (0x8U << ETH_MACPPSCR_PPSCMD_Pos)                   /*!< 0x00000008 */
#define ETH_MACPPSCR_PPSEN0_Pos             (4U)
#define ETH_MACPPSCR_PPSEN0_Msk             (0x1U << ETH_MACPPSCR_PPSEN0_Pos)                   /*!< 0x00000010 */
#define ETH_MACPPSCR_PPSEN0                 ETH_MACPPSCR_PPSEN0_Msk                             /*!< Flexible PPS Output Mode Enable */
#define ETH_MACPPSCR_TRGTMODSEL0_Pos        (5U)
#define ETH_MACPPSCR_TRGTMODSEL0_Msk        (0x3U << ETH_MACPPSCR_TRGTMODSEL0_Pos)              /*!< 0x00000060 */
#define ETH_MACPPSCR_TRGTMODSEL0            ETH_MACPPSCR_TRGTMODSEL0_Msk                        /*!< Target Time Register Mode for PPS Output */
#define ETH_MACPPSCR_TRGTMODSEL0_0          (0x1U << ETH_MACPPSCR_TRGTMODSEL0_Pos)             /*!< 0x00000020 */
#define ETH_MACPPSCR_TRGTMODSEL0_1          (0x2U << ETH_MACPPSCR_TRGTMODSEL0_Pos)             /*!< 0x00000040 */

/************  Bit definition for ETH_MACPPSTTSR register  *************/
#define ETH_MACPPSTTSR_TSTRH0_Pos           (0U)
#define ETH_MACPPSTTSR_TSTRH0_Msk           (0xFFFFFFFFU << ETH_MACPPSTTSR_TSTRH0_Pos)          /*!< 0xFFFFFFFF */
#define ETH_MACPPSTTSR_TSTRH0               ETH_MACPPSTTSR_TSTRH0_Msk                           /*!< PPS Target Time Seconds Register */
#define ETH_MACPPSTTSR_TSTRH0_0             (0x1U << ETH_MACPPSTTSR_TSTRH0_Pos)                 /*!< 0x00000001 */
#define ETH_MACPPSTTSR_TSTRH0_1             (0x2U << ETH_MACPPSTTSR_TSTRH0_Pos)                 /*!< 0x00000002 */
#define ETH_MACPPSTTSR_TSTRH0_2             (0x4U << ETH_MACPPSTTSR_TSTRH0_Pos)                 /*!< 0x00000004 */
#define ETH_MACPPSTTSR_TSTRH0_3             (0x8U << ETH_MACPPSTTSR_TSTRH0_Pos)                 /*!< 0x00000008 */
#define ETH_MACPPSTTSR_TSTRH0_4             (0x10U << ETH_MACPPSTTSR_TSTRH0_Pos)                /*!< 0x00000010 */
#define ETH_MACPPSTTSR_TSTRH0_5             (0x20U << ETH_MACPPSTTSR_TSTRH0_Pos)                /*!< 0x00000020 */
#define ETH_MACPPSTTSR_TSTRH0_6             (0x40U << ETH_MACPPSTTSR_TSTRH0_Pos)                /*!< 0x00000040 */
#define ETH_MACPPSTTSR_TSTRH0_7             (0x80U << ETH_MACPPSTTSR_TSTRH0_Pos)                /*!< 0x00000080 */
#define ETH_MACPPSTTSR_TSTRH0_8             (0x100U << ETH_MACPPSTTSR_TSTRH0_Pos)               /*!< 0x00000100 */
#define ETH_MACPPSTTSR_TSTRH0_9             (0x200U << ETH_MACPPSTTSR_TSTRH0_Pos)               /*!< 0x00000200 */
#define ETH_MACPPSTTSR_TSTRH0_10            (0x400U << ETH_MACPPSTTSR_TSTRH0_Pos)               /*!< 0x00000400 */
#define ETH_MACPPSTTSR_TSTRH0_11            (0x800U << ETH_MACPPSTTSR_TSTRH0_Pos)               /*!< 0x00000800 */
#define ETH_MACPPSTTSR_TSTRH0_12            (0x1000U << ETH_MACPPSTTSR_TSTRH0_Pos)              /*!< 0x00001000 */
#define ETH_MACPPSTTSR_TSTRH0_13            (0x2000U << ETH_MACPPSTTSR_TSTRH0_Pos)              /*!< 0x00002000 */
#define ETH_MACPPSTTSR_TSTRH0_14            (0x4000U << ETH_MACPPSTTSR_TSTRH0_Pos)              /*!< 0x00004000 */
#define ETH_MACPPSTTSR_TSTRH0_15            (0x8000U << ETH_MACPPSTTSR_TSTRH0_Pos)              /*!< 0x00008000 */
#define ETH_MACPPSTTSR_TSTRH0_16            (0x10000U << ETH_MACPPSTTSR_TSTRH0_Pos)             /*!< 0x00010000 */
#define ETH_MACPPSTTSR_TSTRH0_17            (0x20000U << ETH_MACPPSTTSR_TSTRH0_Pos)             /*!< 0x00020000 */
#define ETH_MACPPSTTSR_TSTRH0_18            (0x40000U << ETH_MACPPSTTSR_TSTRH0_Pos)             /*!< 0x00040000 */
#define ETH_MACPPSTTSR_TSTRH0_19            (0x80000U << ETH_MACPPSTTSR_TSTRH0_Pos)             /*!< 0x00080000 */
#define ETH_MACPPSTTSR_TSTRH0_20            (0x100000U << ETH_MACPPSTTSR_TSTRH0_Pos)            /*!< 0x00100000 */
#define ETH_MACPPSTTSR_TSTRH0_21            (0x200000U << ETH_MACPPSTTSR_TSTRH0_Pos)            /*!< 0x00200000 */
#define ETH_MACPPSTTSR_TSTRH0_22            (0x400000U << ETH_MACPPSTTSR_TSTRH0_Pos)            /*!< 0x00400000 */
#define ETH_MACPPSTTSR_TSTRH0_23            (0x800000U << ETH_MACPPSTTSR_TSTRH0_Pos)            /*!< 0x00800000 */
#define ETH_MACPPSTTSR_TSTRH0_24            (0x1000000U << ETH_MACPPSTTSR_TSTRH0_Pos)           /*!< 0x01000000 */
#define ETH_MACPPSTTSR_TSTRH0_25            (0x2000000U << ETH_MACPPSTTSR_TSTRH0_Pos)           /*!< 0x02000000 */
#define ETH_MACPPSTTSR_TSTRH0_26            (0x4000000U << ETH_MACPPSTTSR_TSTRH0_Pos)           /*!< 0x04000000 */
#define ETH_MACPPSTTSR_TSTRH0_27            (0x8000000U << ETH_MACPPSTTSR_TSTRH0_Pos)           /*!< 0x08000000 */
#define ETH_MACPPSTTSR_TSTRH0_28            (0x10000000U << ETH_MACPPSTTSR_TSTRH0_Pos)          /*!< 0x10000000 */
#define ETH_MACPPSTTSR_TSTRH0_29            (0x20000000U << ETH_MACPPSTTSR_TSTRH0_Pos)          /*!< 0x20000000 */
#define ETH_MACPPSTTSR_TSTRH0_30            (0x40000000U << ETH_MACPPSTTSR_TSTRH0_Pos)          /*!< 0x40000000 */
#define ETH_MACPPSTTSR_TSTRH0_31            (0x80000000U << ETH_MACPPSTTSR_TSTRH0_Pos)          /*!< 0x80000000 */

/************  Bit definition for ETH_MACPPSTTNR register  *************/
#define ETH_MACPPSTTNR_TTSL0_Pos            (0U)
#define ETH_MACPPSTTNR_TTSL0_Msk            (0x7FFFFFFFU << ETH_MACPPSTTNR_TTSL0_Pos)           /*!< 0x7FFFFFFF */
#define ETH_MACPPSTTNR_TTSL0                ETH_MACPPSTTNR_TTSL0_Msk                            /*!< Target Time Low for PPS Register */
#define ETH_MACPPSTTNR_TTSL0_0              (0x1U << ETH_MACPPSTTNR_TTSL0_Pos)                  /*!< 0x00000001 */
#define ETH_MACPPSTTNR_TTSL0_1              (0x2U << ETH_MACPPSTTNR_TTSL0_Pos)                  /*!< 0x00000002 */
#define ETH_MACPPSTTNR_TTSL0_2              (0x4U << ETH_MACPPSTTNR_TTSL0_Pos)                  /*!< 0x00000004 */
#define ETH_MACPPSTTNR_TTSL0_3              (0x8U << ETH_MACPPSTTNR_TTSL0_Pos)                  /*!< 0x00000008 */
#define ETH_MACPPSTTNR_TTSL0_4              (0x10U << ETH_MACPPSTTNR_TTSL0_Pos)                 /*!< 0x00000010 */
#define ETH_MACPPSTTNR_TTSL0_5              (0x20U << ETH_MACPPSTTNR_TTSL0_Pos)                 /*!< 0x00000020 */
#define ETH_MACPPSTTNR_TTSL0_6              (0x40U << ETH_MACPPSTTNR_TTSL0_Pos)                 /*!< 0x00000040 */
#define ETH_MACPPSTTNR_TTSL0_7              (0x80U << ETH_MACPPSTTNR_TTSL0_Pos)                 /*!< 0x00000080 */
#define ETH_MACPPSTTNR_TTSL0_8              (0x100U << ETH_MACPPSTTNR_TTSL0_Pos)                /*!< 0x00000100 */
#define ETH_MACPPSTTNR_TTSL0_9              (0x200U << ETH_MACPPSTTNR_TTSL0_Pos)                /*!< 0x00000200 */
#define ETH_MACPPSTTNR_TTSL0_10             (0x400U << ETH_MACPPSTTNR_TTSL0_Pos)                /*!< 0x00000400 */
#define ETH_MACPPSTTNR_TTSL0_11             (0x800U << ETH_MACPPSTTNR_TTSL0_Pos)                /*!< 0x00000800 */
#define ETH_MACPPSTTNR_TTSL0_12             (0x1000U << ETH_MACPPSTTNR_TTSL0_Pos)               /*!< 0x00001000 */
#define ETH_MACPPSTTNR_TTSL0_13             (0x2000U << ETH_MACPPSTTNR_TTSL0_Pos)               /*!< 0x00002000 */
#define ETH_MACPPSTTNR_TTSL0_14             (0x4000U << ETH_MACPPSTTNR_TTSL0_Pos)               /*!< 0x00004000 */
#define ETH_MACPPSTTNR_TTSL0_15             (0x8000U << ETH_MACPPSTTNR_TTSL0_Pos)               /*!< 0x00008000 */
#define ETH_MACPPSTTNR_TTSL0_16             (0x10000U << ETH_MACPPSTTNR_TTSL0_Pos)              /*!< 0x00010000 */
#define ETH_MACPPSTTNR_TTSL0_17             (0x20000U << ETH_MACPPSTTNR_TTSL0_Pos)              /*!< 0x00020000 */
#define ETH_MACPPSTTNR_TTSL0_18             (0x40000U << ETH_MACPPSTTNR_TTSL0_Pos)              /*!< 0x00040000 */
#define ETH_MACPPSTTNR_TTSL0_19             (0x80000U << ETH_MACPPSTTNR_TTSL0_Pos)              /*!< 0x00080000 */
#define ETH_MACPPSTTNR_TTSL0_20             (0x100000U << ETH_MACPPSTTNR_TTSL0_Pos)             /*!< 0x00100000 */
#define ETH_MACPPSTTNR_TTSL0_21             (0x200000U << ETH_MACPPSTTNR_TTSL0_Pos)             /*!< 0x00200000 */
#define ETH_MACPPSTTNR_TTSL0_22             (0x400000U << ETH_MACPPSTTNR_TTSL0_Pos)             /*!< 0x00400000 */
#define ETH_MACPPSTTNR_TTSL0_23             (0x800000U << ETH_MACPPSTTNR_TTSL0_Pos)             /*!< 0x00800000 */
#define ETH_MACPPSTTNR_TTSL0_24             (0x1000000U << ETH_MACPPSTTNR_TTSL0_Pos)            /*!< 0x01000000 */
#define ETH_MACPPSTTNR_TTSL0_25             (0x2000000U << ETH_MACPPSTTNR_TTSL0_Pos)            /*!< 0x02000000 */
#define ETH_MACPPSTTNR_TTSL0_26             (0x4000000U << ETH_MACPPSTTNR_TTSL0_Pos)            /*!< 0x04000000 */
#define ETH_MACPPSTTNR_TTSL0_27             (0x8000000U << ETH_MACPPSTTNR_TTSL0_Pos)            /*!< 0x08000000 */
#define ETH_MACPPSTTNR_TTSL0_28             (0x10000000U << ETH_MACPPSTTNR_TTSL0_Pos)           /*!< 0x10000000 */
#define ETH_MACPPSTTNR_TTSL0_29             (0x20000000U << ETH_MACPPSTTNR_TTSL0_Pos)           /*!< 0x20000000 */
#define ETH_MACPPSTTNR_TTSL0_30             (0x40000000U << ETH_MACPPSTTNR_TTSL0_Pos)           /*!< 0x40000000 */
#define ETH_MACPPSTTNR_TRGTBUSY0_Pos        (31U)
#define ETH_MACPPSTTNR_TRGTBUSY0_Msk        (0x1U << ETH_MACPPSTTNR_TRGTBUSY0_Pos)              /*!< 0x80000000 */
#define ETH_MACPPSTTNR_TRGTBUSY0            ETH_MACPPSTTNR_TRGTBUSY0_Msk                        /*!< PPS Target Time Register Busy */

/*************  Bit definition for ETH_MACPPSIR register  **************/
#define ETH_MACPPSIR_PPSINT0_Pos            (0U)
#define ETH_MACPPSIR_PPSINT0_Msk            (0xFFFFFFFFU << ETH_MACPPSIR_PPSINT0_Pos)           /*!< 0xFFFFFFFF */
#define ETH_MACPPSIR_PPSINT0                ETH_MACPPSIR_PPSINT0_Msk                            /*!< PPS Output Signal Interval */
#define ETH_MACPPSIR_PPSINT0_0              (0x1U << ETH_MACPPSIR_PPSINT0_Pos)                  /*!< 0x00000001 */
#define ETH_MACPPSIR_PPSINT0_1              (0x2U << ETH_MACPPSIR_PPSINT0_Pos)                  /*!< 0x00000002 */
#define ETH_MACPPSIR_PPSINT0_2              (0x4U << ETH_MACPPSIR_PPSINT0_Pos)                  /*!< 0x00000004 */
#define ETH_MACPPSIR_PPSINT0_3              (0x8U << ETH_MACPPSIR_PPSINT0_Pos)                  /*!< 0x00000008 */
#define ETH_MACPPSIR_PPSINT0_4              (0x10U << ETH_MACPPSIR_PPSINT0_Pos)                 /*!< 0x00000010 */
#define ETH_MACPPSIR_PPSINT0_5              (0x20U << ETH_MACPPSIR_PPSINT0_Pos)                 /*!< 0x00000020 */
#define ETH_MACPPSIR_PPSINT0_6              (0x40U << ETH_MACPPSIR_PPSINT0_Pos)                 /*!< 0x00000040 */
#define ETH_MACPPSIR_PPSINT0_7              (0x80U << ETH_MACPPSIR_PPSINT0_Pos)                 /*!< 0x00000080 */
#define ETH_MACPPSIR_PPSINT0_8              (0x100U << ETH_MACPPSIR_PPSINT0_Pos)                /*!< 0x00000100 */
#define ETH_MACPPSIR_PPSINT0_9              (0x200U << ETH_MACPPSIR_PPSINT0_Pos)                /*!< 0x00000200 */
#define ETH_MACPPSIR_PPSINT0_10             (0x400U << ETH_MACPPSIR_PPSINT0_Pos)                /*!< 0x00000400 */
#define ETH_MACPPSIR_PPSINT0_11             (0x800U << ETH_MACPPSIR_PPSINT0_Pos)                /*!< 0x00000800 */
#define ETH_MACPPSIR_PPSINT0_12             (0x1000U << ETH_MACPPSIR_PPSINT0_Pos)               /*!< 0x00001000 */
#define ETH_MACPPSIR_PPSINT0_13             (0x2000U << ETH_MACPPSIR_PPSINT0_Pos)               /*!< 0x00002000 */
#define ETH_MACPPSIR_PPSINT0_14             (0x4000U << ETH_MACPPSIR_PPSINT0_Pos)               /*!< 0x00004000 */
#define ETH_MACPPSIR_PPSINT0_15             (0x8000U << ETH_MACPPSIR_PPSINT0_Pos)               /*!< 0x00008000 */
#define ETH_MACPPSIR_PPSINT0_16             (0x10000U << ETH_MACPPSIR_PPSINT0_Pos)              /*!< 0x00010000 */
#define ETH_MACPPSIR_PPSINT0_17             (0x20000U << ETH_MACPPSIR_PPSINT0_Pos)              /*!< 0x00020000 */
#define ETH_MACPPSIR_PPSINT0_18             (0x40000U << ETH_MACPPSIR_PPSINT0_Pos)              /*!< 0x00040000 */
#define ETH_MACPPSIR_PPSINT0_19             (0x80000U << ETH_MACPPSIR_PPSINT0_Pos)              /*!< 0x00080000 */
#define ETH_MACPPSIR_PPSINT0_20             (0x100000U << ETH_MACPPSIR_PPSINT0_Pos)             /*!< 0x00100000 */
#define ETH_MACPPSIR_PPSINT0_21             (0x200000U << ETH_MACPPSIR_PPSINT0_Pos)             /*!< 0x00200000 */
#define ETH_MACPPSIR_PPSINT0_22             (0x400000U << ETH_MACPPSIR_PPSINT0_Pos)             /*!< 0x00400000 */
#define ETH_MACPPSIR_PPSINT0_23             (0x800000U << ETH_MACPPSIR_PPSINT0_Pos)             /*!< 0x00800000 */
#define ETH_MACPPSIR_PPSINT0_24             (0x1000000U << ETH_MACPPSIR_PPSINT0_Pos)            /*!< 0x01000000 */
#define ETH_MACPPSIR_PPSINT0_25             (0x2000000U << ETH_MACPPSIR_PPSINT0_Pos)            /*!< 0x02000000 */
#define ETH_MACPPSIR_PPSINT0_26             (0x4000000U << ETH_MACPPSIR_PPSINT0_Pos)            /*!< 0x04000000 */
#define ETH_MACPPSIR_PPSINT0_27             (0x8000000U << ETH_MACPPSIR_PPSINT0_Pos)            /*!< 0x08000000 */
#define ETH_MACPPSIR_PPSINT0_28             (0x10000000U << ETH_MACPPSIR_PPSINT0_Pos)           /*!< 0x10000000 */
#define ETH_MACPPSIR_PPSINT0_29             (0x20000000U << ETH_MACPPSIR_PPSINT0_Pos)           /*!< 0x20000000 */
#define ETH_MACPPSIR_PPSINT0_30             (0x40000000U << ETH_MACPPSIR_PPSINT0_Pos)           /*!< 0x40000000 */
#define ETH_MACPPSIR_PPSINT0_31             (0x80000000U << ETH_MACPPSIR_PPSINT0_Pos)           /*!< 0x80000000 */

/*************  Bit definition for ETH_MACPPSWR register  **************/
#define ETH_MACPPSWR_PPSWIDTH0_Pos          (0U)
#define ETH_MACPPSWR_PPSWIDTH0_Msk          (0xFFFFFFFFU << ETH_MACPPSWR_PPSWIDTH0_Pos)         /*!< 0xFFFFFFFF */
#define ETH_MACPPSWR_PPSWIDTH0              ETH_MACPPSWR_PPSWIDTH0_Msk                          /*!< PPS Output Signal Width */
#define ETH_MACPPSWR_PPSWIDTH0_0            (0x1U << ETH_MACPPSWR_PPSWIDTH0_Pos)                /*!< 0x00000001 */
#define ETH_MACPPSWR_PPSWIDTH0_1            (0x2U << ETH_MACPPSWR_PPSWIDTH0_Pos)                /*!< 0x00000002 */
#define ETH_MACPPSWR_PPSWIDTH0_2            (0x4U << ETH_MACPPSWR_PPSWIDTH0_Pos)                /*!< 0x00000004 */
#define ETH_MACPPSWR_PPSWIDTH0_3            (0x8U << ETH_MACPPSWR_PPSWIDTH0_Pos)                /*!< 0x00000008 */
#define ETH_MACPPSWR_PPSWIDTH0_4            (0x10U << ETH_MACPPSWR_PPSWIDTH0_Pos)               /*!< 0x00000010 */
#define ETH_MACPPSWR_PPSWIDTH0_5            (0x20U << ETH_MACPPSWR_PPSWIDTH0_Pos)               /*!< 0x00000020 */
#define ETH_MACPPSWR_PPSWIDTH0_6            (0x40U << ETH_MACPPSWR_PPSWIDTH0_Pos)               /*!< 0x00000040 */
#define ETH_MACPPSWR_PPSWIDTH0_7            (0x80U << ETH_MACPPSWR_PPSWIDTH0_Pos)               /*!< 0x00000080 */
#define ETH_MACPPSWR_PPSWIDTH0_8            (0x100U << ETH_MACPPSWR_PPSWIDTH0_Pos)              /*!< 0x00000100 */
#define ETH_MACPPSWR_PPSWIDTH0_9            (0x200U << ETH_MACPPSWR_PPSWIDTH0_Pos)              /*!< 0x00000200 */
#define ETH_MACPPSWR_PPSWIDTH0_10           (0x400U << ETH_MACPPSWR_PPSWIDTH0_Pos)              /*!< 0x00000400 */
#define ETH_MACPPSWR_PPSWIDTH0_11           (0x800U << ETH_MACPPSWR_PPSWIDTH0_Pos)              /*!< 0x00000800 */
#define ETH_MACPPSWR_PPSWIDTH0_12           (0x1000U << ETH_MACPPSWR_PPSWIDTH0_Pos)             /*!< 0x00001000 */
#define ETH_MACPPSWR_PPSWIDTH0_13           (0x2000U << ETH_MACPPSWR_PPSWIDTH0_Pos)             /*!< 0x00002000 */
#define ETH_MACPPSWR_PPSWIDTH0_14           (0x4000U << ETH_MACPPSWR_PPSWIDTH0_Pos)             /*!< 0x00004000 */
#define ETH_MACPPSWR_PPSWIDTH0_15           (0x8000U << ETH_MACPPSWR_PPSWIDTH0_Pos)             /*!< 0x00008000 */
#define ETH_MACPPSWR_PPSWIDTH0_16           (0x10000U << ETH_MACPPSWR_PPSWIDTH0_Pos)            /*!< 0x00010000 */
#define ETH_MACPPSWR_PPSWIDTH0_17           (0x20000U << ETH_MACPPSWR_PPSWIDTH0_Pos)            /*!< 0x00020000 */
#define ETH_MACPPSWR_PPSWIDTH0_18           (0x40000U << ETH_MACPPSWR_PPSWIDTH0_Pos)            /*!< 0x00040000 */
#define ETH_MACPPSWR_PPSWIDTH0_19           (0x80000U << ETH_MACPPSWR_PPSWIDTH0_Pos)            /*!< 0x00080000 */
#define ETH_MACPPSWR_PPSWIDTH0_20           (0x100000U << ETH_MACPPSWR_PPSWIDTH0_Pos)           /*!< 0x00100000 */
#define ETH_MACPPSWR_PPSWIDTH0_21           (0x200000U << ETH_MACPPSWR_PPSWIDTH0_Pos)           /*!< 0x00200000 */
#define ETH_MACPPSWR_PPSWIDTH0_22           (0x400000U << ETH_MACPPSWR_PPSWIDTH0_Pos)           /*!< 0x00400000 */
#define ETH_MACPPSWR_PPSWIDTH0_23           (0x800000U << ETH_MACPPSWR_PPSWIDTH0_Pos)           /*!< 0x00800000 */
#define ETH_MACPPSWR_PPSWIDTH0_24           (0x1000000U << ETH_MACPPSWR_PPSWIDTH0_Pos)          /*!< 0x01000000 */
#define ETH_MACPPSWR_PPSWIDTH0_25           (0x2000000U << ETH_MACPPSWR_PPSWIDTH0_Pos)          /*!< 0x02000000 */
#define ETH_MACPPSWR_PPSWIDTH0_26           (0x4000000U << ETH_MACPPSWR_PPSWIDTH0_Pos)          /*!< 0x04000000 */
#define ETH_MACPPSWR_PPSWIDTH0_27           (0x8000000U << ETH_MACPPSWR_PPSWIDTH0_Pos)          /*!< 0x08000000 */
#define ETH_MACPPSWR_PPSWIDTH0_28           (0x10000000U << ETH_MACPPSWR_PPSWIDTH0_Pos)         /*!< 0x10000000 */
#define ETH_MACPPSWR_PPSWIDTH0_29           (0x20000000U << ETH_MACPPSWR_PPSWIDTH0_Pos)         /*!< 0x20000000 */
#define ETH_MACPPSWR_PPSWIDTH0_30           (0x40000000U << ETH_MACPPSWR_PPSWIDTH0_Pos)         /*!< 0x40000000 */
#define ETH_MACPPSWR_PPSWIDTH0_31           (0x80000000U << ETH_MACPPSWR_PPSWIDTH0_Pos)         /*!< 0x80000000 */

/**************  Bit definition for ETH_MACPOCR register  **************/
#define ETH_MACPOCR_PTOEN_Pos               (0U)
#define ETH_MACPOCR_PTOEN_Msk               (0x1U << ETH_MACPOCR_PTOEN_Pos)                     /*!< 0x00000001 */
#define ETH_MACPOCR_PTOEN                   ETH_MACPOCR_PTOEN_Msk                               /*!< PTP Offload Enable */
#define ETH_MACPOCR_ASYNCEN_Pos             (1U)
#define ETH_MACPOCR_ASYNCEN_Msk             (0x1U << ETH_MACPOCR_ASYNCEN_Pos)                   /*!< 0x00000002 */
#define ETH_MACPOCR_ASYNCEN                 ETH_MACPOCR_ASYNCEN_Msk                             /*!< Automatic PTP SYNC message Enable */
#define ETH_MACPOCR_APDREQEN_Pos            (2U)
#define ETH_MACPOCR_APDREQEN_Msk            (0x1U << ETH_MACPOCR_APDREQEN_Pos)                  /*!< 0x00000004 */
#define ETH_MACPOCR_APDREQEN                ETH_MACPOCR_APDREQEN_Msk                            /*!< Automatic PTP Pdelay_Req message Enable */
#define ETH_MACPOCR_ASYNCTRIG_Pos           (4U)
#define ETH_MACPOCR_ASYNCTRIG_Msk           (0x1U << ETH_MACPOCR_ASYNCTRIG_Pos)                 /*!< 0x00000010 */
#define ETH_MACPOCR_ASYNCTRIG               ETH_MACPOCR_ASYNCTRIG_Msk                           /*!< Automatic PTP SYNC message Trigger */
#define ETH_MACPOCR_APDREQTRIG_Pos          (5U)
#define ETH_MACPOCR_APDREQTRIG_Msk          (0x1U << ETH_MACPOCR_APDREQTRIG_Pos)                /*!< 0x00000020 */
#define ETH_MACPOCR_APDREQTRIG              ETH_MACPOCR_APDREQTRIG_Msk                          /*!< Automatic PTP Pdelay_Req message Trigger */
#define ETH_MACPOCR_DRRDIS_Pos              (6U)
#define ETH_MACPOCR_DRRDIS_Msk              (0x1U << ETH_MACPOCR_DRRDIS_Pos)                    /*!< 0x00000040 */
#define ETH_MACPOCR_DRRDIS                  ETH_MACPOCR_DRRDIS_Msk                              /*!< Disable PTO Delay Request/Response response generation */
#define ETH_MACPOCR_DN_Pos                  (8U)
#define ETH_MACPOCR_DN_Msk                  (0xFFU << ETH_MACPOCR_DN_Pos)                       /*!< 0x0000FF00 */
#define ETH_MACPOCR_DN                      ETH_MACPOCR_DN_Msk                                  /*!< Domain Number */
#define ETH_MACPOCR_DN_0                    (0x1U << ETH_MACPOCR_DN_Pos)                      /*!< 0x00000100 */
#define ETH_MACPOCR_DN_1                    (0x2U << ETH_MACPOCR_DN_Pos)                      /*!< 0x00000200 */
#define ETH_MACPOCR_DN_2                    (0x4U << ETH_MACPOCR_DN_Pos)                      /*!< 0x00000400 */
#define ETH_MACPOCR_DN_3                    (0x8U << ETH_MACPOCR_DN_Pos)                      /*!< 0x00000800 */
#define ETH_MACPOCR_DN_4                    (0x10U << ETH_MACPOCR_DN_Pos)                     /*!< 0x00001000 */
#define ETH_MACPOCR_DN_5                    (0x20U << ETH_MACPOCR_DN_Pos)                     /*!< 0x00002000 */
#define ETH_MACPOCR_DN_6                    (0x40U << ETH_MACPOCR_DN_Pos)                     /*!< 0x00004000 */
#define ETH_MACPOCR_DN_7                    (0x80U << ETH_MACPOCR_DN_Pos)                     /*!< 0x00008000 */

/*************  Bit definition for ETH_MACSPI0R register  **************/
#define ETH_MACSPI0R_SPI0_Pos               (0U)
#define ETH_MACSPI0R_SPI0_Msk               (0xFFFFFFFFU << ETH_MACSPI0R_SPI0_Pos)              /*!< 0xFFFFFFFF */
#define ETH_MACSPI0R_SPI0                   ETH_MACSPI0R_SPI0_Msk                               /*!< Source Port Identity 0 */
#define ETH_MACSPI0R_SPI0_0                 (0x1U << ETH_MACSPI0R_SPI0_Pos)                     /*!< 0x00000001 */
#define ETH_MACSPI0R_SPI0_1                 (0x2U << ETH_MACSPI0R_SPI0_Pos)                     /*!< 0x00000002 */
#define ETH_MACSPI0R_SPI0_2                 (0x4U << ETH_MACSPI0R_SPI0_Pos)                     /*!< 0x00000004 */
#define ETH_MACSPI0R_SPI0_3                 (0x8U << ETH_MACSPI0R_SPI0_Pos)                     /*!< 0x00000008 */
#define ETH_MACSPI0R_SPI0_4                 (0x10U << ETH_MACSPI0R_SPI0_Pos)                    /*!< 0x00000010 */
#define ETH_MACSPI0R_SPI0_5                 (0x20U << ETH_MACSPI0R_SPI0_Pos)                    /*!< 0x00000020 */
#define ETH_MACSPI0R_SPI0_6                 (0x40U << ETH_MACSPI0R_SPI0_Pos)                    /*!< 0x00000040 */
#define ETH_MACSPI0R_SPI0_7                 (0x80U << ETH_MACSPI0R_SPI0_Pos)                    /*!< 0x00000080 */
#define ETH_MACSPI0R_SPI0_8                 (0x100U << ETH_MACSPI0R_SPI0_Pos)                   /*!< 0x00000100 */
#define ETH_MACSPI0R_SPI0_9                 (0x200U << ETH_MACSPI0R_SPI0_Pos)                   /*!< 0x00000200 */
#define ETH_MACSPI0R_SPI0_10                (0x400U << ETH_MACSPI0R_SPI0_Pos)                   /*!< 0x00000400 */
#define ETH_MACSPI0R_SPI0_11                (0x800U << ETH_MACSPI0R_SPI0_Pos)                   /*!< 0x00000800 */
#define ETH_MACSPI0R_SPI0_12                (0x1000U << ETH_MACSPI0R_SPI0_Pos)                  /*!< 0x00001000 */
#define ETH_MACSPI0R_SPI0_13                (0x2000U << ETH_MACSPI0R_SPI0_Pos)                  /*!< 0x00002000 */
#define ETH_MACSPI0R_SPI0_14                (0x4000U << ETH_MACSPI0R_SPI0_Pos)                  /*!< 0x00004000 */
#define ETH_MACSPI0R_SPI0_15                (0x8000U << ETH_MACSPI0R_SPI0_Pos)                  /*!< 0x00008000 */
#define ETH_MACSPI0R_SPI0_16                (0x10000U << ETH_MACSPI0R_SPI0_Pos)                 /*!< 0x00010000 */
#define ETH_MACSPI0R_SPI0_17                (0x20000U << ETH_MACSPI0R_SPI0_Pos)                 /*!< 0x00020000 */
#define ETH_MACSPI0R_SPI0_18                (0x40000U << ETH_MACSPI0R_SPI0_Pos)                 /*!< 0x00040000 */
#define ETH_MACSPI0R_SPI0_19                (0x80000U << ETH_MACSPI0R_SPI0_Pos)                 /*!< 0x00080000 */
#define ETH_MACSPI0R_SPI0_20                (0x100000U << ETH_MACSPI0R_SPI0_Pos)                /*!< 0x00100000 */
#define ETH_MACSPI0R_SPI0_21                (0x200000U << ETH_MACSPI0R_SPI0_Pos)                /*!< 0x00200000 */
#define ETH_MACSPI0R_SPI0_22                (0x400000U << ETH_MACSPI0R_SPI0_Pos)                /*!< 0x00400000 */
#define ETH_MACSPI0R_SPI0_23                (0x800000U << ETH_MACSPI0R_SPI0_Pos)                /*!< 0x00800000 */
#define ETH_MACSPI0R_SPI0_24                (0x1000000U << ETH_MACSPI0R_SPI0_Pos)               /*!< 0x01000000 */
#define ETH_MACSPI0R_SPI0_25                (0x2000000U << ETH_MACSPI0R_SPI0_Pos)               /*!< 0x02000000 */
#define ETH_MACSPI0R_SPI0_26                (0x4000000U << ETH_MACSPI0R_SPI0_Pos)               /*!< 0x04000000 */
#define ETH_MACSPI0R_SPI0_27                (0x8000000U << ETH_MACSPI0R_SPI0_Pos)               /*!< 0x08000000 */
#define ETH_MACSPI0R_SPI0_28                (0x10000000U << ETH_MACSPI0R_SPI0_Pos)              /*!< 0x10000000 */
#define ETH_MACSPI0R_SPI0_29                (0x20000000U << ETH_MACSPI0R_SPI0_Pos)              /*!< 0x20000000 */
#define ETH_MACSPI0R_SPI0_30                (0x40000000U << ETH_MACSPI0R_SPI0_Pos)              /*!< 0x40000000 */
#define ETH_MACSPI0R_SPI0_31                (0x80000000U << ETH_MACSPI0R_SPI0_Pos)              /*!< 0x80000000 */

/*************  Bit definition for ETH_MACSPI1R register  **************/
#define ETH_MACSPI1R_SPI1_Pos               (0U)
#define ETH_MACSPI1R_SPI1_Msk               (0xFFFFFFFFU << ETH_MACSPI1R_SPI1_Pos)              /*!< 0xFFFFFFFF */
#define ETH_MACSPI1R_SPI1                   ETH_MACSPI1R_SPI1_Msk                               /*!< Source Port Identity 1 */
#define ETH_MACSPI1R_SPI1_0                 (0x1U << ETH_MACSPI1R_SPI1_Pos)                     /*!< 0x00000001 */
#define ETH_MACSPI1R_SPI1_1                 (0x2U << ETH_MACSPI1R_SPI1_Pos)                     /*!< 0x00000002 */
#define ETH_MACSPI1R_SPI1_2                 (0x4U << ETH_MACSPI1R_SPI1_Pos)                     /*!< 0x00000004 */
#define ETH_MACSPI1R_SPI1_3                 (0x8U << ETH_MACSPI1R_SPI1_Pos)                     /*!< 0x00000008 */
#define ETH_MACSPI1R_SPI1_4                 (0x10U << ETH_MACSPI1R_SPI1_Pos)                    /*!< 0x00000010 */
#define ETH_MACSPI1R_SPI1_5                 (0x20U << ETH_MACSPI1R_SPI1_Pos)                    /*!< 0x00000020 */
#define ETH_MACSPI1R_SPI1_6                 (0x40U << ETH_MACSPI1R_SPI1_Pos)                    /*!< 0x00000040 */
#define ETH_MACSPI1R_SPI1_7                 (0x80U << ETH_MACSPI1R_SPI1_Pos)                    /*!< 0x00000080 */
#define ETH_MACSPI1R_SPI1_8                 (0x100U << ETH_MACSPI1R_SPI1_Pos)                   /*!< 0x00000100 */
#define ETH_MACSPI1R_SPI1_9                 (0x200U << ETH_MACSPI1R_SPI1_Pos)                   /*!< 0x00000200 */
#define ETH_MACSPI1R_SPI1_10                (0x400U << ETH_MACSPI1R_SPI1_Pos)                   /*!< 0x00000400 */
#define ETH_MACSPI1R_SPI1_11                (0x800U << ETH_MACSPI1R_SPI1_Pos)                   /*!< 0x00000800 */
#define ETH_MACSPI1R_SPI1_12                (0x1000U << ETH_MACSPI1R_SPI1_Pos)                  /*!< 0x00001000 */
#define ETH_MACSPI1R_SPI1_13                (0x2000U << ETH_MACSPI1R_SPI1_Pos)                  /*!< 0x00002000 */
#define ETH_MACSPI1R_SPI1_14                (0x4000U << ETH_MACSPI1R_SPI1_Pos)                  /*!< 0x00004000 */
#define ETH_MACSPI1R_SPI1_15                (0x8000U << ETH_MACSPI1R_SPI1_Pos)                  /*!< 0x00008000 */
#define ETH_MACSPI1R_SPI1_16                (0x10000U << ETH_MACSPI1R_SPI1_Pos)                 /*!< 0x00010000 */
#define ETH_MACSPI1R_SPI1_17                (0x20000U << ETH_MACSPI1R_SPI1_Pos)                 /*!< 0x00020000 */
#define ETH_MACSPI1R_SPI1_18                (0x40000U << ETH_MACSPI1R_SPI1_Pos)                 /*!< 0x00040000 */
#define ETH_MACSPI1R_SPI1_19                (0x80000U << ETH_MACSPI1R_SPI1_Pos)                 /*!< 0x00080000 */
#define ETH_MACSPI1R_SPI1_20                (0x100000U << ETH_MACSPI1R_SPI1_Pos)                /*!< 0x00100000 */
#define ETH_MACSPI1R_SPI1_21                (0x200000U << ETH_MACSPI1R_SPI1_Pos)                /*!< 0x00200000 */
#define ETH_MACSPI1R_SPI1_22                (0x400000U << ETH_MACSPI1R_SPI1_Pos)                /*!< 0x00400000 */
#define ETH_MACSPI1R_SPI1_23                (0x800000U << ETH_MACSPI1R_SPI1_Pos)                /*!< 0x00800000 */
#define ETH_MACSPI1R_SPI1_24                (0x1000000U << ETH_MACSPI1R_SPI1_Pos)               /*!< 0x01000000 */
#define ETH_MACSPI1R_SPI1_25                (0x2000000U << ETH_MACSPI1R_SPI1_Pos)               /*!< 0x02000000 */
#define ETH_MACSPI1R_SPI1_26                (0x4000000U << ETH_MACSPI1R_SPI1_Pos)               /*!< 0x04000000 */
#define ETH_MACSPI1R_SPI1_27                (0x8000000U << ETH_MACSPI1R_SPI1_Pos)               /*!< 0x08000000 */
#define ETH_MACSPI1R_SPI1_28                (0x10000000U << ETH_MACSPI1R_SPI1_Pos)              /*!< 0x10000000 */
#define ETH_MACSPI1R_SPI1_29                (0x20000000U << ETH_MACSPI1R_SPI1_Pos)              /*!< 0x20000000 */
#define ETH_MACSPI1R_SPI1_30                (0x40000000U << ETH_MACSPI1R_SPI1_Pos)              /*!< 0x40000000 */
#define ETH_MACSPI1R_SPI1_31                (0x80000000U << ETH_MACSPI1R_SPI1_Pos)              /*!< 0x80000000 */

/*************  Bit definition for ETH_MACSPI2R register  **************/
#define ETH_MACSPI2R_SPI2_Pos               (0U)
#define ETH_MACSPI2R_SPI2_Msk               (0xFFFFU << ETH_MACSPI2R_SPI2_Pos)                  /*!< 0x0000FFFF */
#define ETH_MACSPI2R_SPI2                   ETH_MACSPI2R_SPI2_Msk                               /*!< Source Port Identity 2 */
#define ETH_MACSPI2R_SPI2_0                 (0x1U << ETH_MACSPI2R_SPI2_Pos)                     /*!< 0x00000001 */
#define ETH_MACSPI2R_SPI2_1                 (0x2U << ETH_MACSPI2R_SPI2_Pos)                     /*!< 0x00000002 */
#define ETH_MACSPI2R_SPI2_2                 (0x4U << ETH_MACSPI2R_SPI2_Pos)                     /*!< 0x00000004 */
#define ETH_MACSPI2R_SPI2_3                 (0x8U << ETH_MACSPI2R_SPI2_Pos)                     /*!< 0x00000008 */
#define ETH_MACSPI2R_SPI2_4                 (0x10U << ETH_MACSPI2R_SPI2_Pos)                    /*!< 0x00000010 */
#define ETH_MACSPI2R_SPI2_5                 (0x20U << ETH_MACSPI2R_SPI2_Pos)                    /*!< 0x00000020 */
#define ETH_MACSPI2R_SPI2_6                 (0x40U << ETH_MACSPI2R_SPI2_Pos)                    /*!< 0x00000040 */
#define ETH_MACSPI2R_SPI2_7                 (0x80U << ETH_MACSPI2R_SPI2_Pos)                    /*!< 0x00000080 */
#define ETH_MACSPI2R_SPI2_8                 (0x100U << ETH_MACSPI2R_SPI2_Pos)                   /*!< 0x00000100 */
#define ETH_MACSPI2R_SPI2_9                 (0x200U << ETH_MACSPI2R_SPI2_Pos)                   /*!< 0x00000200 */
#define ETH_MACSPI2R_SPI2_10                (0x400U << ETH_MACSPI2R_SPI2_Pos)                   /*!< 0x00000400 */
#define ETH_MACSPI2R_SPI2_11                (0x800U << ETH_MACSPI2R_SPI2_Pos)                   /*!< 0x00000800 */
#define ETH_MACSPI2R_SPI2_12                (0x1000U << ETH_MACSPI2R_SPI2_Pos)                  /*!< 0x00001000 */
#define ETH_MACSPI2R_SPI2_13                (0x2000U << ETH_MACSPI2R_SPI2_Pos)                  /*!< 0x00002000 */
#define ETH_MACSPI2R_SPI2_14                (0x4000U << ETH_MACSPI2R_SPI2_Pos)                  /*!< 0x00004000 */
#define ETH_MACSPI2R_SPI2_15                (0x8000U << ETH_MACSPI2R_SPI2_Pos)                  /*!< 0x00008000 */

/**************  Bit definition for ETH_MACLMIR register  **************/
#define ETH_MACLMIR_LSI_Pos                 (0U)
#define ETH_MACLMIR_LSI_Msk                 (0xFFU << ETH_MACLMIR_LSI_Pos)                      /*!< 0x000000FF */
#define ETH_MACLMIR_LSI                     ETH_MACLMIR_LSI_Msk                                 /*!< Log Sync Interval */
#define ETH_MACLMIR_LSI_0                   (0x1U << ETH_MACLMIR_LSI_Pos)                       /*!< 0x00000001 */
#define ETH_MACLMIR_LSI_1                   (0x2U << ETH_MACLMIR_LSI_Pos)                       /*!< 0x00000002 */
#define ETH_MACLMIR_LSI_2                   (0x4U << ETH_MACLMIR_LSI_Pos)                       /*!< 0x00000004 */
#define ETH_MACLMIR_LSI_3                   (0x8U << ETH_MACLMIR_LSI_Pos)                       /*!< 0x00000008 */
#define ETH_MACLMIR_LSI_4                   (0x10U << ETH_MACLMIR_LSI_Pos)                      /*!< 0x00000010 */
#define ETH_MACLMIR_LSI_5                   (0x20U << ETH_MACLMIR_LSI_Pos)                      /*!< 0x00000020 */
#define ETH_MACLMIR_LSI_6                   (0x40U << ETH_MACLMIR_LSI_Pos)                      /*!< 0x00000040 */
#define ETH_MACLMIR_LSI_7                   (0x80U << ETH_MACLMIR_LSI_Pos)                      /*!< 0x00000080 */
#define ETH_MACLMIR_DRSYNCR_Pos             (8U)
#define ETH_MACLMIR_DRSYNCR_Msk             (0x7U << ETH_MACLMIR_DRSYNCR_Pos)                   /*!< 0x00000700 */
#define ETH_MACLMIR_DRSYNCR                 ETH_MACLMIR_DRSYNCR_Msk                             /*!< Delay_Req to SYNC Ratio */
#define ETH_MACLMIR_DRSYNCR_0               (0x1U << ETH_MACLMIR_DRSYNCR_Pos)                 /*!< 0x00000100 */
#define ETH_MACLMIR_DRSYNCR_1               (0x2U << ETH_MACLMIR_DRSYNCR_Pos)                 /*!< 0x00000200 */
#define ETH_MACLMIR_DRSYNCR_2               (0x4U << ETH_MACLMIR_DRSYNCR_Pos)                 /*!< 0x00000400 */
#define ETH_MACLMIR_LMPDRI_Pos              (24U)
#define ETH_MACLMIR_LMPDRI_Msk              (0xFFU << ETH_MACLMIR_LMPDRI_Pos)                   /*!< 0xFF000000 */
#define ETH_MACLMIR_LMPDRI                  ETH_MACLMIR_LMPDRI_Msk                              /*!< Log Min Pdelay_Req Interval */
#define ETH_MACLMIR_LMPDRI_0                (0x1U << ETH_MACLMIR_LMPDRI_Pos)              /*!< 0x01000000 */
#define ETH_MACLMIR_LMPDRI_1                (0x2U << ETH_MACLMIR_LMPDRI_Pos)              /*!< 0x02000000 */
#define ETH_MACLMIR_LMPDRI_2                (0x4U << ETH_MACLMIR_LMPDRI_Pos)              /*!< 0x04000000 */
#define ETH_MACLMIR_LMPDRI_3                (0x8U << ETH_MACLMIR_LMPDRI_Pos)              /*!< 0x08000000 */
#define ETH_MACLMIR_LMPDRI_4                (0x10U << ETH_MACLMIR_LMPDRI_Pos)             /*!< 0x10000000 */
#define ETH_MACLMIR_LMPDRI_5                (0x20U << ETH_MACLMIR_LMPDRI_Pos)             /*!< 0x20000000 */
#define ETH_MACLMIR_LMPDRI_6                (0x40U << ETH_MACLMIR_LMPDRI_Pos)             /*!< 0x40000000 */
#define ETH_MACLMIR_LMPDRI_7                (0x80U << ETH_MACLMIR_LMPDRI_Pos)             /*!< 0x80000000 */

/**************  Bit definition for ETH_MTLOMR register  ***************/
#define ETH_MTLOMR_DTXSTS_Pos               (1U)
#define ETH_MTLOMR_DTXSTS_Msk               (0x1U << ETH_MTLOMR_DTXSTS_Pos)                     /*!< 0x00000002 */
#define ETH_MTLOMR_DTXSTS                   ETH_MTLOMR_DTXSTS_Msk                               /*!< Drop Transmit Status */
#define ETH_MTLOMR_RAA_Pos                  (2U)
#define ETH_MTLOMR_RAA_Msk                  (0x1U << ETH_MTLOMR_RAA_Pos)                        /*!< 0x00000004 */
#define ETH_MTLOMR_RAA                      ETH_MTLOMR_RAA_Msk                                  /*!< Receive Arbitration Algorithm */
#define ETH_MTLOMR_SCHALG_Pos               (5U)
#define ETH_MTLOMR_SCHALG_Msk               (0x3U << ETH_MTLOMR_SCHALG_Pos)                     /*!< 0x00000060 */
#define ETH_MTLOMR_SCHALG                   ETH_MTLOMR_SCHALG_Msk                               /*!< Tx Scheduling Algorithm */
#define ETH_MTLOMR_SCHALG_0                 (0x1U << ETH_MTLOMR_SCHALG_Pos)                    /*!< 0x00000020 */
#define ETH_MTLOMR_SCHALG_1                 (0x2U << ETH_MTLOMR_SCHALG_Pos)                    /*!< 0x00000040 */
#define ETH_MTLOMR_CNTPRST_Pos              (8U)
#define ETH_MTLOMR_CNTPRST_Msk              (0x1U << ETH_MTLOMR_CNTPRST_Pos)                    /*!< 0x00000100 */
#define ETH_MTLOMR_CNTPRST                  ETH_MTLOMR_CNTPRST_Msk                              /*!< Counters Preset */
#define ETH_MTLOMR_CNTCLR_Pos               (9U)
#define ETH_MTLOMR_CNTCLR_Msk               (0x1U << ETH_MTLOMR_CNTCLR_Pos)                     /*!< 0x00000200 */
#define ETH_MTLOMR_CNTCLR                   ETH_MTLOMR_CNTCLR_Msk                               /*!< Counters Reset */

/**************  Bit definition for ETH_MTLISR register  ***************/
#define ETH_MTLISR_Q0IS_Pos                 (0U)
#define ETH_MTLISR_Q0IS_Msk                 (0x1U << ETH_MTLISR_Q0IS_Pos)                       /*!< 0x00000001 */
#define ETH_MTLISR_Q0IS                     ETH_MTLISR_Q0IS_Msk                                 /*!< Queue 0 interrupt status */
#define ETH_MTLISR_Q1IS_Pos                 (1U)
#define ETH_MTLISR_Q1IS_Msk                 (0x1U << ETH_MTLISR_Q1IS_Pos)                       /*!< 0x00000002 */
#define ETH_MTLISR_Q1IS                     ETH_MTLISR_Q1IS_Msk                                 /*!< Queue 1 interrupt status */

/************  Bit definition for ETH_MTLTXQ0OMR register  *************/
#define ETH_MTLTXQ0OMR_FTQ_Pos              (0U)
#define ETH_MTLTXQ0OMR_FTQ_Msk              (0x1U << ETH_MTLTXQ0OMR_FTQ_Pos)                    /*!< 0x00000001 */
#define ETH_MTLTXQ0OMR_FTQ                  ETH_MTLTXQ0OMR_FTQ_Msk                              /*!< Flush Transmit Queue */
#define ETH_MTLTXQ0OMR_TSF_Pos              (1U)
#define ETH_MTLTXQ0OMR_TSF_Msk              (0x1U << ETH_MTLTXQ0OMR_TSF_Pos)                    /*!< 0x00000002 */
#define ETH_MTLTXQ0OMR_TSF                  ETH_MTLTXQ0OMR_TSF_Msk                              /*!< Transmit Store and Forward */
#define ETH_MTLTXQ0OMR_TXQEN_Pos            (2U)
#define ETH_MTLTXQ0OMR_TXQEN_Msk            (0x3U << ETH_MTLTXQ0OMR_TXQEN_Pos)                  /*!< 0x0000000C */
#define ETH_MTLTXQ0OMR_TXQEN                ETH_MTLTXQ0OMR_TXQEN_Msk                            /*!< Transmit Queue Enable */
#define ETH_MTLTXQ0OMR_TXQEN_0              (0x1U << ETH_MTLTXQ0OMR_TXQEN_Pos)                  /*!< 0x00000004 */
#define ETH_MTLTXQ0OMR_TXQEN_1              (0x2U << ETH_MTLTXQ0OMR_TXQEN_Pos)                  /*!< 0x00000008 */
#define ETH_MTLTXQ0OMR_TTC_Pos              (4U)
#define ETH_MTLTXQ0OMR_TTC_Msk              (0x7U << ETH_MTLTXQ0OMR_TTC_Pos)                    /*!< 0x00000070 */
#define ETH_MTLTXQ0OMR_TTC                  ETH_MTLTXQ0OMR_TTC_Msk                              /*!< Transmit Threshold Control */
#define ETH_MTLTXQ0OMR_TTC_0                (0x1U << ETH_MTLTXQ0OMR_TTC_Pos)                   /*!< 0x00000010 */
#define ETH_MTLTXQ0OMR_TTC_1                (0x2U << ETH_MTLTXQ0OMR_TTC_Pos)                   /*!< 0x00000020 */
#define ETH_MTLTXQ0OMR_TTC_2                (0x4U << ETH_MTLTXQ0OMR_TTC_Pos)                   /*!< 0x00000040 */
#define ETH_MTLTXQ0OMR_TQS_Pos              (16U)
#define ETH_MTLTXQ0OMR_TQS_Msk              (0x1FFU << ETH_MTLTXQ0OMR_TQS_Pos)                  /*!< 0x01FF0000 */
#define ETH_MTLTXQ0OMR_TQS                  ETH_MTLTXQ0OMR_TQS_Msk                              /*!< Transmit Queue Size */
#define ETH_MTLTXQ0OMR_TQS_0                (0x1U << ETH_MTLTXQ0OMR_TQS_Pos)                /*!< 0x00010000 */
#define ETH_MTLTXQ0OMR_TQS_1                (0x2U << ETH_MTLTXQ0OMR_TQS_Pos)                /*!< 0x00020000 */
#define ETH_MTLTXQ0OMR_TQS_2                (0x4U << ETH_MTLTXQ0OMR_TQS_Pos)                /*!< 0x00040000 */
#define ETH_MTLTXQ0OMR_TQS_3                (0x8U << ETH_MTLTXQ0OMR_TQS_Pos)                /*!< 0x00080000 */
#define ETH_MTLTXQ0OMR_TQS_4                (0x10U << ETH_MTLTXQ0OMR_TQS_Pos)               /*!< 0x00100000 */
#define ETH_MTLTXQ0OMR_TQS_5                (0x20U << ETH_MTLTXQ0OMR_TQS_Pos)               /*!< 0x00200000 */
#define ETH_MTLTXQ0OMR_TQS_6                (0x40U << ETH_MTLTXQ0OMR_TQS_Pos)               /*!< 0x00400000 */
#define ETH_MTLTXQ0OMR_TQS_7                (0x80U << ETH_MTLTXQ0OMR_TQS_Pos)               /*!< 0x00800000 */
#define ETH_MTLTXQ0OMR_TQS_8                (0x100U << ETH_MTLTXQ0OMR_TQS_Pos)              /*!< 0x01000000 */

/*************  Bit definition for ETH_MTLTXQ0UR register  *************/
#define ETH_MTLTXQ0UR_UFFRMCNT_Pos          (0U)
#define ETH_MTLTXQ0UR_UFFRMCNT_Msk          (0x7FFU << ETH_MTLTXQ0UR_UFFRMCNT_Pos)              /*!< 0x000007FF */
#define ETH_MTLTXQ0UR_UFFRMCNT              ETH_MTLTXQ0UR_UFFRMCNT_Msk                          /*!< Underflow Packet Counter */
#define ETH_MTLTXQ0UR_UFFRMCNT_0            (0x1U << ETH_MTLTXQ0UR_UFFRMCNT_Pos)                /*!< 0x00000001 */
#define ETH_MTLTXQ0UR_UFFRMCNT_1            (0x2U << ETH_MTLTXQ0UR_UFFRMCNT_Pos)                /*!< 0x00000002 */
#define ETH_MTLTXQ0UR_UFFRMCNT_2            (0x4U << ETH_MTLTXQ0UR_UFFRMCNT_Pos)                /*!< 0x00000004 */
#define ETH_MTLTXQ0UR_UFFRMCNT_3            (0x8U << ETH_MTLTXQ0UR_UFFRMCNT_Pos)                /*!< 0x00000008 */
#define ETH_MTLTXQ0UR_UFFRMCNT_4            (0x10U << ETH_MTLTXQ0UR_UFFRMCNT_Pos)               /*!< 0x00000010 */
#define ETH_MTLTXQ0UR_UFFRMCNT_5            (0x20U << ETH_MTLTXQ0UR_UFFRMCNT_Pos)               /*!< 0x00000020 */
#define ETH_MTLTXQ0UR_UFFRMCNT_6            (0x40U << ETH_MTLTXQ0UR_UFFRMCNT_Pos)               /*!< 0x00000040 */
#define ETH_MTLTXQ0UR_UFFRMCNT_7            (0x80U << ETH_MTLTXQ0UR_UFFRMCNT_Pos)               /*!< 0x00000080 */
#define ETH_MTLTXQ0UR_UFFRMCNT_8            (0x100U << ETH_MTLTXQ0UR_UFFRMCNT_Pos)              /*!< 0x00000100 */
#define ETH_MTLTXQ0UR_UFFRMCNT_9            (0x200U << ETH_MTLTXQ0UR_UFFRMCNT_Pos)              /*!< 0x00000200 */
#define ETH_MTLTXQ0UR_UFFRMCNT_10           (0x400U << ETH_MTLTXQ0UR_UFFRMCNT_Pos)              /*!< 0x00000400 */
#define ETH_MTLTXQ0UR_UFCNTOVF_Pos          (11U)
#define ETH_MTLTXQ0UR_UFCNTOVF_Msk          (0x1U << ETH_MTLTXQ0UR_UFCNTOVF_Pos)                /*!< 0x00000800 */
#define ETH_MTLTXQ0UR_UFCNTOVF              ETH_MTLTXQ0UR_UFCNTOVF_Msk                          /*!< Overflow Bit for Underflow Packet Counter */

/*************  Bit definition for ETH_MTLTXQ0DR register  *************/
#define ETH_MTLTXQ0DR_TXQPAUSED_Pos         (0U)
#define ETH_MTLTXQ0DR_TXQPAUSED_Msk         (0x1U << ETH_MTLTXQ0DR_TXQPAUSED_Pos)               /*!< 0x00000001 */
#define ETH_MTLTXQ0DR_TXQPAUSED             ETH_MTLTXQ0DR_TXQPAUSED_Msk                         /*!< Transmit Queue in Pause */
#define ETH_MTLTXQ0DR_TRCSTS_Pos            (1U)
#define ETH_MTLTXQ0DR_TRCSTS_Msk            (0x3U << ETH_MTLTXQ0DR_TRCSTS_Pos)                  /*!< 0x00000006 */
#define ETH_MTLTXQ0DR_TRCSTS                ETH_MTLTXQ0DR_TRCSTS_Msk                            /*!< MTL Tx Queue Read Controller Status */
#define ETH_MTLTXQ0DR_TRCSTS_0              (0x1U << ETH_MTLTXQ0DR_TRCSTS_Pos)                  /*!< 0x00000002 */
#define ETH_MTLTXQ0DR_TRCSTS_1              (0x2U << ETH_MTLTXQ0DR_TRCSTS_Pos)                  /*!< 0x00000004 */
#define ETH_MTLTXQ0DR_TWCSTS_Pos            (3U)
#define ETH_MTLTXQ0DR_TWCSTS_Msk            (0x1U << ETH_MTLTXQ0DR_TWCSTS_Pos)                  /*!< 0x00000008 */
#define ETH_MTLTXQ0DR_TWCSTS                ETH_MTLTXQ0DR_TWCSTS_Msk                            /*!< MTL Tx Queue Write Controller Status */
#define ETH_MTLTXQ0DR_TXQSTS_Pos            (4U)
#define ETH_MTLTXQ0DR_TXQSTS_Msk            (0x1U << ETH_MTLTXQ0DR_TXQSTS_Pos)                  /*!< 0x00000010 */
#define ETH_MTLTXQ0DR_TXQSTS                ETH_MTLTXQ0DR_TXQSTS_Msk                            /*!< MTL Tx Queue Not Empty Status */
#define ETH_MTLTXQ0DR_TXSTSFSTS_Pos         (5U)
#define ETH_MTLTXQ0DR_TXSTSFSTS_Msk         (0x1U << ETH_MTLTXQ0DR_TXSTSFSTS_Pos)               /*!< 0x00000020 */
#define ETH_MTLTXQ0DR_TXSTSFSTS             ETH_MTLTXQ0DR_TXSTSFSTS_Msk                         /*!< MTL Tx Status FIFO Full Status */
#define ETH_MTLTXQ0DR_PTXQ_Pos              (16U)
#define ETH_MTLTXQ0DR_PTXQ_Msk              (0x7U << ETH_MTLTXQ0DR_PTXQ_Pos)                    /*!< 0x00070000 */
#define ETH_MTLTXQ0DR_PTXQ                  ETH_MTLTXQ0DR_PTXQ_Msk                              /*!< Number of Packets in the Transmit Queue */
#define ETH_MTLTXQ0DR_PTXQ_0                (0x1U << ETH_MTLTXQ0DR_PTXQ_Pos)                /*!< 0x00010000 */
#define ETH_MTLTXQ0DR_PTXQ_1                (0x2U << ETH_MTLTXQ0DR_PTXQ_Pos)                /*!< 0x00020000 */
#define ETH_MTLTXQ0DR_PTXQ_2                (0x4U << ETH_MTLTXQ0DR_PTXQ_Pos)                /*!< 0x00040000 */
#define ETH_MTLTXQ0DR_STXSTSF_Pos           (20U)
#define ETH_MTLTXQ0DR_STXSTSF_Msk           (0x7U << ETH_MTLTXQ0DR_STXSTSF_Pos)                 /*!< 0x00700000 */
#define ETH_MTLTXQ0DR_STXSTSF               ETH_MTLTXQ0DR_STXSTSF_Msk                           /*!< Number of Status Words in Tx Status FIFO of Queue */
#define ETH_MTLTXQ0DR_STXSTSF_0             (0x1U << ETH_MTLTXQ0DR_STXSTSF_Pos)            /*!< 0x00100000 */
#define ETH_MTLTXQ0DR_STXSTSF_1             (0x2U << ETH_MTLTXQ0DR_STXSTSF_Pos)            /*!< 0x00200000 */
#define ETH_MTLTXQ0DR_STXSTSF_2             (0x4U << ETH_MTLTXQ0DR_STXSTSF_Pos)            /*!< 0x00400000 */

/************  Bit definition for ETH_MTLTXQ0ESR register  *************/
#define ETH_MTLTXQ0ESR_ABS_Pos              (0U)
#define ETH_MTLTXQ0ESR_ABS_Msk              (0xFFFFFFU << ETH_MTLTXQ0ESR_ABS_Pos)               /*!< 0x00FFFFFF */
#define ETH_MTLTXQ0ESR_ABS                  ETH_MTLTXQ0ESR_ABS_Msk                              /*!< Average Bits per Slot */
#define ETH_MTLTXQ0ESR_ABS_0                (0x1U << ETH_MTLTXQ0ESR_ABS_Pos)                    /*!< 0x00000001 */
#define ETH_MTLTXQ0ESR_ABS_1                (0x2U << ETH_MTLTXQ0ESR_ABS_Pos)                    /*!< 0x00000002 */
#define ETH_MTLTXQ0ESR_ABS_2                (0x4U << ETH_MTLTXQ0ESR_ABS_Pos)                    /*!< 0x00000004 */
#define ETH_MTLTXQ0ESR_ABS_3                (0x8U << ETH_MTLTXQ0ESR_ABS_Pos)                    /*!< 0x00000008 */
#define ETH_MTLTXQ0ESR_ABS_4                (0x10U << ETH_MTLTXQ0ESR_ABS_Pos)                   /*!< 0x00000010 */
#define ETH_MTLTXQ0ESR_ABS_5                (0x20U << ETH_MTLTXQ0ESR_ABS_Pos)                   /*!< 0x00000020 */
#define ETH_MTLTXQ0ESR_ABS_6                (0x40U << ETH_MTLTXQ0ESR_ABS_Pos)                   /*!< 0x00000040 */
#define ETH_MTLTXQ0ESR_ABS_7                (0x80U << ETH_MTLTXQ0ESR_ABS_Pos)                   /*!< 0x00000080 */
#define ETH_MTLTXQ0ESR_ABS_8                (0x100U << ETH_MTLTXQ0ESR_ABS_Pos)                  /*!< 0x00000100 */
#define ETH_MTLTXQ0ESR_ABS_9                (0x200U << ETH_MTLTXQ0ESR_ABS_Pos)                  /*!< 0x00000200 */
#define ETH_MTLTXQ0ESR_ABS_10               (0x400U << ETH_MTLTXQ0ESR_ABS_Pos)                  /*!< 0x00000400 */
#define ETH_MTLTXQ0ESR_ABS_11               (0x800U << ETH_MTLTXQ0ESR_ABS_Pos)                  /*!< 0x00000800 */
#define ETH_MTLTXQ0ESR_ABS_12               (0x1000U << ETH_MTLTXQ0ESR_ABS_Pos)                 /*!< 0x00001000 */
#define ETH_MTLTXQ0ESR_ABS_13               (0x2000U << ETH_MTLTXQ0ESR_ABS_Pos)                 /*!< 0x00002000 */
#define ETH_MTLTXQ0ESR_ABS_14               (0x4000U << ETH_MTLTXQ0ESR_ABS_Pos)                 /*!< 0x00004000 */
#define ETH_MTLTXQ0ESR_ABS_15               (0x8000U << ETH_MTLTXQ0ESR_ABS_Pos)                 /*!< 0x00008000 */
#define ETH_MTLTXQ0ESR_ABS_16               (0x10000U << ETH_MTLTXQ0ESR_ABS_Pos)                /*!< 0x00010000 */
#define ETH_MTLTXQ0ESR_ABS_17               (0x20000U << ETH_MTLTXQ0ESR_ABS_Pos)                /*!< 0x00020000 */
#define ETH_MTLTXQ0ESR_ABS_18               (0x40000U << ETH_MTLTXQ0ESR_ABS_Pos)                /*!< 0x00040000 */
#define ETH_MTLTXQ0ESR_ABS_19               (0x80000U << ETH_MTLTXQ0ESR_ABS_Pos)                /*!< 0x00080000 */
#define ETH_MTLTXQ0ESR_ABS_20               (0x100000U << ETH_MTLTXQ0ESR_ABS_Pos)               /*!< 0x00100000 */
#define ETH_MTLTXQ0ESR_ABS_21               (0x200000U << ETH_MTLTXQ0ESR_ABS_Pos)               /*!< 0x00200000 */
#define ETH_MTLTXQ0ESR_ABS_22               (0x400000U << ETH_MTLTXQ0ESR_ABS_Pos)               /*!< 0x00400000 */
#define ETH_MTLTXQ0ESR_ABS_23               (0x800000U << ETH_MTLTXQ0ESR_ABS_Pos)               /*!< 0x00800000 */

/*************  Bit definition for ETH_MTLQ0ICSR register  *************/
#define ETH_MTLQ0ICSR_TXUNFIS_Pos           (0U)
#define ETH_MTLQ0ICSR_TXUNFIS_Msk           (0x1U << ETH_MTLQ0ICSR_TXUNFIS_Pos)                 /*!< 0x00000001 */
#define ETH_MTLQ0ICSR_TXUNFIS               ETH_MTLQ0ICSR_TXUNFIS_Msk                           /*!< Transmit Queue Underflow Interrupt Status */
#define ETH_MTLQ0ICSR_ABPSIS_Pos            (1U)
#define ETH_MTLQ0ICSR_ABPSIS_Msk            (0x1U << ETH_MTLQ0ICSR_ABPSIS_Pos)                  /*!< 0x00000002 */
#define ETH_MTLQ0ICSR_ABPSIS                ETH_MTLQ0ICSR_ABPSIS_Msk                            /*!< Average Bits Per Slot Interrupt Status */
#define ETH_MTLQ0ICSR_TXUIE_Pos             (8U)
#define ETH_MTLQ0ICSR_TXUIE_Msk             (0x1U << ETH_MTLQ0ICSR_TXUIE_Pos)                   /*!< 0x00000100 */
#define ETH_MTLQ0ICSR_TXUIE                 ETH_MTLQ0ICSR_TXUIE_Msk                             /*!< Transmit Queue Underflow Interrupt Enable */
#define ETH_MTLQ0ICSR_ABPSIE_Pos            (9U)
#define ETH_MTLQ0ICSR_ABPSIE_Msk            (0x1U << ETH_MTLQ0ICSR_ABPSIE_Pos)                  /*!< 0x00000200 */
#define ETH_MTLQ0ICSR_ABPSIE                ETH_MTLQ0ICSR_ABPSIE_Msk                            /*!< Average Bits Per Slot Interrupt Enable */
#define ETH_MTLQ0ICSR_RXOVFIS_Pos           (16U)
#define ETH_MTLQ0ICSR_RXOVFIS_Msk           (0x1U << ETH_MTLQ0ICSR_RXOVFIS_Pos)                 /*!< 0x00010000 */
#define ETH_MTLQ0ICSR_RXOVFIS               ETH_MTLQ0ICSR_RXOVFIS_Msk                           /*!< Receive Queue Overflow Interrupt Status */
#define ETH_MTLQ0ICSR_RXOIE_Pos             (24U)
#define ETH_MTLQ0ICSR_RXOIE_Msk             (0x1U << ETH_MTLQ0ICSR_RXOIE_Pos)                   /*!< 0x01000000 */
#define ETH_MTLQ0ICSR_RXOIE                 ETH_MTLQ0ICSR_RXOIE_Msk                             /*!< Receive Queue Overflow Interrupt Enable */

/************  Bit definition for ETH_MTLRXQ0OMR register  *************/
#define ETH_MTLRXQ0OMR_RTC_Pos              (0U)
#define ETH_MTLRXQ0OMR_RTC_Msk              (0x3U << ETH_MTLRXQ0OMR_RTC_Pos)                    /*!< 0x00000003 */
#define ETH_MTLRXQ0OMR_RTC                  ETH_MTLRXQ0OMR_RTC_Msk                              /*!< Receive Queue Threshold Control */
#define ETH_MTLRXQ0OMR_RTC_0                (0x1U << ETH_MTLRXQ0OMR_RTC_Pos)                    /*!< 0x00000001 */
#define ETH_MTLRXQ0OMR_RTC_1                (0x2U << ETH_MTLRXQ0OMR_RTC_Pos)                    /*!< 0x00000002 */
#define ETH_MTLRXQ0OMR_FUP_Pos              (3U)
#define ETH_MTLRXQ0OMR_FUP_Msk              (0x1U << ETH_MTLRXQ0OMR_FUP_Pos)                    /*!< 0x00000008 */
#define ETH_MTLRXQ0OMR_FUP                  ETH_MTLRXQ0OMR_FUP_Msk                              /*!< Forward Undersized Good Packets */
#define ETH_MTLRXQ0OMR_FEP_Pos              (4U)
#define ETH_MTLRXQ0OMR_FEP_Msk              (0x1U << ETH_MTLRXQ0OMR_FEP_Pos)                    /*!< 0x00000010 */
#define ETH_MTLRXQ0OMR_FEP                  ETH_MTLRXQ0OMR_FEP_Msk                              /*!< Forward Error Packets */
#define ETH_MTLRXQ0OMR_RSF_Pos              (5U)
#define ETH_MTLRXQ0OMR_RSF_Msk              (0x1U << ETH_MTLRXQ0OMR_RSF_Pos)                    /*!< 0x00000020 */
#define ETH_MTLRXQ0OMR_RSF                  ETH_MTLRXQ0OMR_RSF_Msk                              /*!< Receive Queue Store and Forward */
#define ETH_MTLRXQ0OMR_DIS_TCP_EF_Pos       (6U)
#define ETH_MTLRXQ0OMR_DIS_TCP_EF_Msk       (0x1U << ETH_MTLRXQ0OMR_DIS_TCP_EF_Pos)             /*!< 0x00000040 */
#define ETH_MTLRXQ0OMR_DIS_TCP_EF           ETH_MTLRXQ0OMR_DIS_TCP_EF_Msk                       /*!< Disable Dropping of TCP/IP Checksum Error Packets */
#define ETH_MTLRXQ0OMR_EHFC_Pos             (7U)
#define ETH_MTLRXQ0OMR_EHFC_Msk             (0x1U << ETH_MTLRXQ0OMR_EHFC_Pos)                   /*!< 0x00000080 */
#define ETH_MTLRXQ0OMR_EHFC                 ETH_MTLRXQ0OMR_EHFC_Msk                             /*!< Enable Hardware Flow Control */
#define ETH_MTLRXQ0OMR_RFA_Pos              (8U)
#define ETH_MTLRXQ0OMR_RFA_Msk              (0x7U << ETH_MTLRXQ0OMR_RFA_Pos)                    /*!< 0x00000700 */
#define ETH_MTLRXQ0OMR_RFA                  ETH_MTLRXQ0OMR_RFA_Msk                              /*!< Threshold for Activating Flow Control (in half-duplex and full-duplex */
#define ETH_MTLRXQ0OMR_RFA_0                (0x1U << ETH_MTLRXQ0OMR_RFA_Pos)                  /*!< 0x00000100 */
#define ETH_MTLRXQ0OMR_RFA_1                (0x2U << ETH_MTLRXQ0OMR_RFA_Pos)                  /*!< 0x00000200 */
#define ETH_MTLRXQ0OMR_RFA_2                (0x4U << ETH_MTLRXQ0OMR_RFA_Pos)                  /*!< 0x00000400 */
#define ETH_MTLRXQ0OMR_RFD_Pos              (14U)
#define ETH_MTLRXQ0OMR_RFD_Msk              (0x7U << ETH_MTLRXQ0OMR_RFD_Pos)                    /*!< 0x0001C000 */
#define ETH_MTLRXQ0OMR_RFD                  ETH_MTLRXQ0OMR_RFD_Msk                              /*!< Threshold for Deactivating Flow Control (in half-duplex and full-duplex modes) */
#define ETH_MTLRXQ0OMR_RFD_0                (0x1U << ETH_MTLRXQ0OMR_RFD_Pos)                 /*!< 0x00004000 */
#define ETH_MTLRXQ0OMR_RFD_1                (0x2U << ETH_MTLRXQ0OMR_RFD_Pos)                 /*!< 0x00008000 */
#define ETH_MTLRXQ0OMR_RFD_2                (0x4U << ETH_MTLRXQ0OMR_RFD_Pos)                /*!< 0x00010000 */
#define ETH_MTLRXQ0OMR_RQS_Pos              (20U)
#define ETH_MTLRXQ0OMR_RQS_Msk              (0xFU << ETH_MTLRXQ0OMR_RQS_Pos)                    /*!< 0x00F00000 */
#define ETH_MTLRXQ0OMR_RQS                  ETH_MTLRXQ0OMR_RQS_Msk                              /*!< Receive Queue Size */
#define ETH_MTLRXQ0OMR_RQS_0                (0x1U << ETH_MTLRXQ0OMR_RQS_Pos)               /*!< 0x00100000 */
#define ETH_MTLRXQ0OMR_RQS_1                (0x2U << ETH_MTLRXQ0OMR_RQS_Pos)               /*!< 0x00200000 */
#define ETH_MTLRXQ0OMR_RQS_2                (0x4U << ETH_MTLRXQ0OMR_RQS_Pos)               /*!< 0x00400000 */
#define ETH_MTLRXQ0OMR_RQS_3                (0x8U << ETH_MTLRXQ0OMR_RQS_Pos)               /*!< 0x00800000 */

/***********  Bit definition for ETH_MTLRXQ0MPOCR register  ************/
#define ETH_MTLRXQ0MPOCR_OVFPKTCNT_Pos      (0U)
#define ETH_MTLRXQ0MPOCR_OVFPKTCNT_Msk      (0x7FFU << ETH_MTLRXQ0MPOCR_OVFPKTCNT_Pos)          /*!< 0x000007FF */
#define ETH_MTLRXQ0MPOCR_OVFPKTCNT          ETH_MTLRXQ0MPOCR_OVFPKTCNT_Msk                      /*!< Overflow Packet Counter */
#define ETH_MTLRXQ0MPOCR_OVFPKTCNT_0        (0x1U << ETH_MTLRXQ0MPOCR_OVFPKTCNT_Pos)            /*!< 0x00000001 */
#define ETH_MTLRXQ0MPOCR_OVFPKTCNT_1        (0x2U << ETH_MTLRXQ0MPOCR_OVFPKTCNT_Pos)            /*!< 0x00000002 */
#define ETH_MTLRXQ0MPOCR_OVFPKTCNT_2        (0x4U << ETH_MTLRXQ0MPOCR_OVFPKTCNT_Pos)            /*!< 0x00000004 */
#define ETH_MTLRXQ0MPOCR_OVFPKTCNT_3        (0x8U << ETH_MTLRXQ0MPOCR_OVFPKTCNT_Pos)            /*!< 0x00000008 */
#define ETH_MTLRXQ0MPOCR_OVFPKTCNT_4        (0x10U << ETH_MTLRXQ0MPOCR_OVFPKTCNT_Pos)           /*!< 0x00000010 */
#define ETH_MTLRXQ0MPOCR_OVFPKTCNT_5        (0x20U << ETH_MTLRXQ0MPOCR_OVFPKTCNT_Pos)           /*!< 0x00000020 */
#define ETH_MTLRXQ0MPOCR_OVFPKTCNT_6        (0x40U << ETH_MTLRXQ0MPOCR_OVFPKTCNT_Pos)           /*!< 0x00000040 */
#define ETH_MTLRXQ0MPOCR_OVFPKTCNT_7        (0x80U << ETH_MTLRXQ0MPOCR_OVFPKTCNT_Pos)           /*!< 0x00000080 */
#define ETH_MTLRXQ0MPOCR_OVFPKTCNT_8        (0x100U << ETH_MTLRXQ0MPOCR_OVFPKTCNT_Pos)          /*!< 0x00000100 */
#define ETH_MTLRXQ0MPOCR_OVFPKTCNT_9        (0x200U << ETH_MTLRXQ0MPOCR_OVFPKTCNT_Pos)          /*!< 0x00000200 */
#define ETH_MTLRXQ0MPOCR_OVFPKTCNT_10       (0x400U << ETH_MTLRXQ0MPOCR_OVFPKTCNT_Pos)          /*!< 0x00000400 */
#define ETH_MTLRXQ0MPOCR_OVFCNTOVF_Pos      (11U)
#define ETH_MTLRXQ0MPOCR_OVFCNTOVF_Msk      (0x1U << ETH_MTLRXQ0MPOCR_OVFCNTOVF_Pos)            /*!< 0x00000800 */
#define ETH_MTLRXQ0MPOCR_OVFCNTOVF          ETH_MTLRXQ0MPOCR_OVFCNTOVF_Msk                      /*!< Overflow Counter Overflow Bit */
#define ETH_MTLRXQ0MPOCR_MISPKTCNT_Pos      (16U)
#define ETH_MTLRXQ0MPOCR_MISPKTCNT_Msk      (0x7FFU << ETH_MTLRXQ0MPOCR_MISPKTCNT_Pos)          /*!< 0x07FF0000 */
#define ETH_MTLRXQ0MPOCR_MISPKTCNT          ETH_MTLRXQ0MPOCR_MISPKTCNT_Msk                      /*!< Missed Packet Counter */
#define ETH_MTLRXQ0MPOCR_MISPKTCNT_0        (0x1U << ETH_MTLRXQ0MPOCR_MISPKTCNT_Pos)        /*!< 0x00010000 */
#define ETH_MTLRXQ0MPOCR_MISPKTCNT_1        (0x2U << ETH_MTLRXQ0MPOCR_MISPKTCNT_Pos)        /*!< 0x00020000 */
#define ETH_MTLRXQ0MPOCR_MISPKTCNT_2        (0x4U << ETH_MTLRXQ0MPOCR_MISPKTCNT_Pos)        /*!< 0x00040000 */
#define ETH_MTLRXQ0MPOCR_MISPKTCNT_3        (0x8U << ETH_MTLRXQ0MPOCR_MISPKTCNT_Pos)        /*!< 0x00080000 */
#define ETH_MTLRXQ0MPOCR_MISPKTCNT_4        (0x10U << ETH_MTLRXQ0MPOCR_MISPKTCNT_Pos)       /*!< 0x00100000 */
#define ETH_MTLRXQ0MPOCR_MISPKTCNT_5        (0x20U << ETH_MTLRXQ0MPOCR_MISPKTCNT_Pos)       /*!< 0x00200000 */
#define ETH_MTLRXQ0MPOCR_MISPKTCNT_6        (0x40U << ETH_MTLRXQ0MPOCR_MISPKTCNT_Pos)       /*!< 0x00400000 */
#define ETH_MTLRXQ0MPOCR_MISPKTCNT_7        (0x80U << ETH_MTLRXQ0MPOCR_MISPKTCNT_Pos)       /*!< 0x00800000 */
#define ETH_MTLRXQ0MPOCR_MISPKTCNT_8        (0x100U << ETH_MTLRXQ0MPOCR_MISPKTCNT_Pos)      /*!< 0x01000000 */
#define ETH_MTLRXQ0MPOCR_MISPKTCNT_9        (0x200U << ETH_MTLRXQ0MPOCR_MISPKTCNT_Pos)      /*!< 0x02000000 */
#define ETH_MTLRXQ0MPOCR_MISPKTCNT_10       (0x400U << ETH_MTLRXQ0MPOCR_MISPKTCNT_Pos)      /*!< 0x04000000 */
#define ETH_MTLRXQ0MPOCR_MISCNTOVF_Pos      (27U)
#define ETH_MTLRXQ0MPOCR_MISCNTOVF_Msk      (0x1U << ETH_MTLRXQ0MPOCR_MISCNTOVF_Pos)            /*!< 0x08000000 */
#define ETH_MTLRXQ0MPOCR_MISCNTOVF          ETH_MTLRXQ0MPOCR_MISCNTOVF_Msk                      /*!< Missed Packet Counter Overflow Bit */

/*************  Bit definition for ETH_MTLRXQ0DR register  *************/
#define ETH_MTLRXQ0DR_RWCSTS_Pos            (0U)
#define ETH_MTLRXQ0DR_RWCSTS_Msk            (0x1U << ETH_MTLRXQ0DR_RWCSTS_Pos)                  /*!< 0x00000001 */
#define ETH_MTLRXQ0DR_RWCSTS                ETH_MTLRXQ0DR_RWCSTS_Msk                            /*!< MTL Rx Queue Write Controller Active Status */
#define ETH_MTLRXQ0DR_RRCSTS_Pos            (1U)
#define ETH_MTLRXQ0DR_RRCSTS_Msk            (0x3U << ETH_MTLRXQ0DR_RRCSTS_Pos)                  /*!< 0x00000006 */
#define ETH_MTLRXQ0DR_RRCSTS                ETH_MTLRXQ0DR_RRCSTS_Msk                            /*!< MTL Rx Queue Read Controller State */
#define ETH_MTLRXQ0DR_RRCSTS_0              (0x1U << ETH_MTLRXQ0DR_RRCSTS_Pos)                  /*!< 0x00000002 */
#define ETH_MTLRXQ0DR_RRCSTS_1              (0x2U << ETH_MTLRXQ0DR_RRCSTS_Pos)                  /*!< 0x00000004 */
#define ETH_MTLRXQ0DR_RXQSTS_Pos            (4U)
#define ETH_MTLRXQ0DR_RXQSTS_Msk            (0x3U << ETH_MTLRXQ0DR_RXQSTS_Pos)                  /*!< 0x00000030 */
#define ETH_MTLRXQ0DR_RXQSTS                ETH_MTLRXQ0DR_RXQSTS_Msk                            /*!< MTL Rx Queue Fill-Level Status */
#define ETH_MTLRXQ0DR_RXQSTS_0              (0x1U << ETH_MTLRXQ0DR_RXQSTS_Pos)                 /*!< 0x00000010 */
#define ETH_MTLRXQ0DR_RXQSTS_1              (0x2U << ETH_MTLRXQ0DR_RXQSTS_Pos)                 /*!< 0x00000020 */
#define ETH_MTLRXQ0DR_PRXQ_Pos              (16U)
#define ETH_MTLRXQ0DR_PRXQ_Msk              (0x3FFFU << ETH_MTLRXQ0DR_PRXQ_Pos)                 /*!< 0x3FFF0000 */
#define ETH_MTLRXQ0DR_PRXQ                  ETH_MTLRXQ0DR_PRXQ_Msk                              /*!< Number of Packets in Receive Queue */
#define ETH_MTLRXQ0DR_PRXQ_0                (0x1U << ETH_MTLRXQ0DR_PRXQ_Pos)                /*!< 0x00010000 */
#define ETH_MTLRXQ0DR_PRXQ_1                (0x2U << ETH_MTLRXQ0DR_PRXQ_Pos)                /*!< 0x00020000 */
#define ETH_MTLRXQ0DR_PRXQ_2                (0x4U << ETH_MTLRXQ0DR_PRXQ_Pos)                /*!< 0x00040000 */
#define ETH_MTLRXQ0DR_PRXQ_3                (0x8U << ETH_MTLRXQ0DR_PRXQ_Pos)                /*!< 0x00080000 */
#define ETH_MTLRXQ0DR_PRXQ_4                (0x10U << ETH_MTLRXQ0DR_PRXQ_Pos)               /*!< 0x00100000 */
#define ETH_MTLRXQ0DR_PRXQ_5                (0x20U << ETH_MTLRXQ0DR_PRXQ_Pos)               /*!< 0x00200000 */
#define ETH_MTLRXQ0DR_PRXQ_6                (0x40U << ETH_MTLRXQ0DR_PRXQ_Pos)               /*!< 0x00400000 */
#define ETH_MTLRXQ0DR_PRXQ_7                (0x80U << ETH_MTLRXQ0DR_PRXQ_Pos)               /*!< 0x00800000 */
#define ETH_MTLRXQ0DR_PRXQ_8                (0x100U << ETH_MTLRXQ0DR_PRXQ_Pos)              /*!< 0x01000000 */
#define ETH_MTLRXQ0DR_PRXQ_9                (0x200U << ETH_MTLRXQ0DR_PRXQ_Pos)              /*!< 0x02000000 */
#define ETH_MTLRXQ0DR_PRXQ_10               (0x400U << ETH_MTLRXQ0DR_PRXQ_Pos)              /*!< 0x04000000 */
#define ETH_MTLRXQ0DR_PRXQ_11               (0x800U << ETH_MTLRXQ0DR_PRXQ_Pos)              /*!< 0x08000000 */
#define ETH_MTLRXQ0DR_PRXQ_12               (0x1000U << ETH_MTLRXQ0DR_PRXQ_Pos)             /*!< 0x10000000 */
#define ETH_MTLRXQ0DR_PRXQ_13               (0x2000U << ETH_MTLRXQ0DR_PRXQ_Pos)             /*!< 0x20000000 */

/*************  Bit definition for ETH_MTLRXQ0CR register  *************/
#define ETH_MTLRXQ0CR_RXQ_WEGT_Pos          (0U)
#define ETH_MTLRXQ0CR_RXQ_WEGT_Msk          (0x7U << ETH_MTLRXQ0CR_RXQ_WEGT_Pos)                /*!< 0x00000007 */
#define ETH_MTLRXQ0CR_RXQ_WEGT              ETH_MTLRXQ0CR_RXQ_WEGT_Msk                          /*!< Receive Queue Weight */
#define ETH_MTLRXQ0CR_RXQ_WEGT_0            (0x1U << ETH_MTLRXQ0CR_RXQ_WEGT_Pos)                /*!< 0x00000001 */
#define ETH_MTLRXQ0CR_RXQ_WEGT_1            (0x2U << ETH_MTLRXQ0CR_RXQ_WEGT_Pos)                /*!< 0x00000002 */
#define ETH_MTLRXQ0CR_RXQ_WEGT_2            (0x4U << ETH_MTLRXQ0CR_RXQ_WEGT_Pos)                /*!< 0x00000004 */
#define ETH_MTLRXQ0CR_RXQ_FRM_ARBIT_Pos     (3U)
#define ETH_MTLRXQ0CR_RXQ_FRM_ARBIT_Msk     (0x1U << ETH_MTLRXQ0CR_RXQ_FRM_ARBIT_Pos)           /*!< 0x00000008 */
#define ETH_MTLRXQ0CR_RXQ_FRM_ARBIT         ETH_MTLRXQ0CR_RXQ_FRM_ARBIT_Msk                     /*!< Receive Queue Packet Arbitration */

/************  Bit definition for ETH_MTLTXQ1OMR register  *************/
#define ETH_MTLTXQ1OMR_FTQ_Pos              (0U)
#define ETH_MTLTXQ1OMR_FTQ_Msk              (0x1U << ETH_MTLTXQ1OMR_FTQ_Pos)                    /*!< 0x00000001 */
#define ETH_MTLTXQ1OMR_FTQ                  ETH_MTLTXQ1OMR_FTQ_Msk                              /*!< Flush Transmit Queue */
#define ETH_MTLTXQ1OMR_TSF_Pos              (1U)
#define ETH_MTLTXQ1OMR_TSF_Msk              (0x1U << ETH_MTLTXQ1OMR_TSF_Pos)                    /*!< 0x00000002 */
#define ETH_MTLTXQ1OMR_TSF                  ETH_MTLTXQ1OMR_TSF_Msk                              /*!< Transmit Store and Forward */
#define ETH_MTLTXQ1OMR_TXQEN_Pos            (2U)
#define ETH_MTLTXQ1OMR_TXQEN_Msk            (0x3U << ETH_MTLTXQ1OMR_TXQEN_Pos)                  /*!< 0x0000000C */
#define ETH_MTLTXQ1OMR_TXQEN                ETH_MTLTXQ1OMR_TXQEN_Msk                            /*!< Transmit Queue Enable */
#define ETH_MTLTXQ1OMR_TXQEN_0              (0x1U << ETH_MTLTXQ1OMR_TXQEN_Pos)                  /*!< 0x00000004 */
#define ETH_MTLTXQ1OMR_TXQEN_1              (0x2U << ETH_MTLTXQ1OMR_TXQEN_Pos)                  /*!< 0x00000008 */
#define ETH_MTLTXQ1OMR_TTC_Pos              (4U)
#define ETH_MTLTXQ1OMR_TTC_Msk              (0x7U << ETH_MTLTXQ1OMR_TTC_Pos)                    /*!< 0x00000070 */
#define ETH_MTLTXQ1OMR_TTC                  ETH_MTLTXQ1OMR_TTC_Msk                              /*!< Transmit Threshold Control */
#define ETH_MTLTXQ1OMR_TTC_0                (0x1U << ETH_MTLTXQ1OMR_TTC_Pos)                   /*!< 0x00000010 */
#define ETH_MTLTXQ1OMR_TTC_1                (0x2U << ETH_MTLTXQ1OMR_TTC_Pos)                   /*!< 0x00000020 */
#define ETH_MTLTXQ1OMR_TTC_2                (0x4U << ETH_MTLTXQ1OMR_TTC_Pos)                   /*!< 0x00000040 */
#define ETH_MTLTXQ1OMR_TQS_Pos              (16U)
#define ETH_MTLTXQ1OMR_TQS_Msk              (0x1FFU << ETH_MTLTXQ1OMR_TQS_Pos)                  /*!< 0x01FF0000 */
#define ETH_MTLTXQ1OMR_TQS                  ETH_MTLTXQ1OMR_TQS_Msk                              /*!< Transmit Queue Size */
#define ETH_MTLTXQ1OMR_TQS_0                (0x1U << ETH_MTLTXQ1OMR_TQS_Pos)                /*!< 0x00010000 */
#define ETH_MTLTXQ1OMR_TQS_1                (0x2U << ETH_MTLTXQ1OMR_TQS_Pos)                /*!< 0x00020000 */
#define ETH_MTLTXQ1OMR_TQS_2                (0x4U << ETH_MTLTXQ1OMR_TQS_Pos)                /*!< 0x00040000 */
#define ETH_MTLTXQ1OMR_TQS_3                (0x8U << ETH_MTLTXQ1OMR_TQS_Pos)                /*!< 0x00080000 */
#define ETH_MTLTXQ1OMR_TQS_4                (0x10U << ETH_MTLTXQ1OMR_TQS_Pos)               /*!< 0x00100000 */
#define ETH_MTLTXQ1OMR_TQS_5                (0x20U << ETH_MTLTXQ1OMR_TQS_Pos)               /*!< 0x00200000 */
#define ETH_MTLTXQ1OMR_TQS_6                (0x40U << ETH_MTLTXQ1OMR_TQS_Pos)               /*!< 0x00400000 */
#define ETH_MTLTXQ1OMR_TQS_7                (0x80U << ETH_MTLTXQ1OMR_TQS_Pos)               /*!< 0x00800000 */
#define ETH_MTLTXQ1OMR_TQS_8                (0x100U << ETH_MTLTXQ1OMR_TQS_Pos)              /*!< 0x01000000 */

/*************  Bit definition for ETH_MTLTXQ1UR register  *************/
#define ETH_MTLTXQ1UR_UFFRMCNT_Pos          (0U)
#define ETH_MTLTXQ1UR_UFFRMCNT_Msk          (0x7FFU << ETH_MTLTXQ1UR_UFFRMCNT_Pos)              /*!< 0x000007FF */
#define ETH_MTLTXQ1UR_UFFRMCNT              ETH_MTLTXQ1UR_UFFRMCNT_Msk                          /*!< Underflow Packet Counter */
#define ETH_MTLTXQ1UR_UFFRMCNT_0            (0x1U << ETH_MTLTXQ1UR_UFFRMCNT_Pos)                /*!< 0x00000001 */
#define ETH_MTLTXQ1UR_UFFRMCNT_1            (0x2U << ETH_MTLTXQ1UR_UFFRMCNT_Pos)                /*!< 0x00000002 */
#define ETH_MTLTXQ1UR_UFFRMCNT_2            (0x4U << ETH_MTLTXQ1UR_UFFRMCNT_Pos)                /*!< 0x00000004 */
#define ETH_MTLTXQ1UR_UFFRMCNT_3            (0x8U << ETH_MTLTXQ1UR_UFFRMCNT_Pos)                /*!< 0x00000008 */
#define ETH_MTLTXQ1UR_UFFRMCNT_4            (0x10U << ETH_MTLTXQ1UR_UFFRMCNT_Pos)               /*!< 0x00000010 */
#define ETH_MTLTXQ1UR_UFFRMCNT_5            (0x20U << ETH_MTLTXQ1UR_UFFRMCNT_Pos)               /*!< 0x00000020 */
#define ETH_MTLTXQ1UR_UFFRMCNT_6            (0x40U << ETH_MTLTXQ1UR_UFFRMCNT_Pos)               /*!< 0x00000040 */
#define ETH_MTLTXQ1UR_UFFRMCNT_7            (0x80U << ETH_MTLTXQ1UR_UFFRMCNT_Pos)               /*!< 0x00000080 */
#define ETH_MTLTXQ1UR_UFFRMCNT_8            (0x100U << ETH_MTLTXQ1UR_UFFRMCNT_Pos)              /*!< 0x00000100 */
#define ETH_MTLTXQ1UR_UFFRMCNT_9            (0x200U << ETH_MTLTXQ1UR_UFFRMCNT_Pos)              /*!< 0x00000200 */
#define ETH_MTLTXQ1UR_UFFRMCNT_10           (0x400U << ETH_MTLTXQ1UR_UFFRMCNT_Pos)              /*!< 0x00000400 */
#define ETH_MTLTXQ1UR_UFCNTOVF_Pos          (11U)
#define ETH_MTLTXQ1UR_UFCNTOVF_Msk          (0x1U << ETH_MTLTXQ1UR_UFCNTOVF_Pos)                /*!< 0x00000800 */
#define ETH_MTLTXQ1UR_UFCNTOVF              ETH_MTLTXQ1UR_UFCNTOVF_Msk                          /*!< Overflow Bit for Underflow Packet Counter */

/*************  Bit definition for ETH_MTLTXQ1DR register  *************/
#define ETH_MTLTXQ1DR_TXQPAUSED_Pos         (0U)
#define ETH_MTLTXQ1DR_TXQPAUSED_Msk         (0x1U << ETH_MTLTXQ1DR_TXQPAUSED_Pos)               /*!< 0x00000001 */
#define ETH_MTLTXQ1DR_TXQPAUSED             ETH_MTLTXQ1DR_TXQPAUSED_Msk                         /*!< Transmit Queue in Pause */
#define ETH_MTLTXQ1DR_TRCSTS_Pos            (1U)
#define ETH_MTLTXQ1DR_TRCSTS_Msk            (0x3U << ETH_MTLTXQ1DR_TRCSTS_Pos)                  /*!< 0x00000006 */
#define ETH_MTLTXQ1DR_TRCSTS                ETH_MTLTXQ1DR_TRCSTS_Msk                            /*!< MTL Tx Queue Read Controller Status */
#define ETH_MTLTXQ1DR_TRCSTS_0              (0x1U << ETH_MTLTXQ1DR_TRCSTS_Pos)                  /*!< 0x00000002 */
#define ETH_MTLTXQ1DR_TRCSTS_1              (0x2U << ETH_MTLTXQ1DR_TRCSTS_Pos)                  /*!< 0x00000004 */
#define ETH_MTLTXQ1DR_TWCSTS_Pos            (3U)
#define ETH_MTLTXQ1DR_TWCSTS_Msk            (0x1U << ETH_MTLTXQ1DR_TWCSTS_Pos)                  /*!< 0x00000008 */
#define ETH_MTLTXQ1DR_TWCSTS                ETH_MTLTXQ1DR_TWCSTS_Msk                            /*!< MTL Tx Queue Write Controller Status */
#define ETH_MTLTXQ1DR_TXQSTS_Pos            (4U)
#define ETH_MTLTXQ1DR_TXQSTS_Msk            (0x1U << ETH_MTLTXQ1DR_TXQSTS_Pos)                  /*!< 0x00000010 */
#define ETH_MTLTXQ1DR_TXQSTS                ETH_MTLTXQ1DR_TXQSTS_Msk                            /*!< MTL Tx Queue Not Empty Status */
#define ETH_MTLTXQ1DR_TXSTSFSTS_Pos         (5U)
#define ETH_MTLTXQ1DR_TXSTSFSTS_Msk         (0x1U << ETH_MTLTXQ1DR_TXSTSFSTS_Pos)               /*!< 0x00000020 */
#define ETH_MTLTXQ1DR_TXSTSFSTS             ETH_MTLTXQ1DR_TXSTSFSTS_Msk                         /*!< MTL Tx Status FIFO Full Status */
#define ETH_MTLTXQ1DR_PTXQ_Pos              (16U)
#define ETH_MTLTXQ1DR_PTXQ_Msk              (0x7U << ETH_MTLTXQ1DR_PTXQ_Pos)                    /*!< 0x00070000 */
#define ETH_MTLTXQ1DR_PTXQ                  ETH_MTLTXQ1DR_PTXQ_Msk                              /*!< Number of Packets in the Transmit Queue */
#define ETH_MTLTXQ1DR_PTXQ_0                (0x1U << ETH_MTLTXQ1DR_PTXQ_Pos)                /*!< 0x00010000 */
#define ETH_MTLTXQ1DR_PTXQ_1                (0x2U << ETH_MTLTXQ1DR_PTXQ_Pos)                /*!< 0x00020000 */
#define ETH_MTLTXQ1DR_PTXQ_2                (0x4U << ETH_MTLTXQ1DR_PTXQ_Pos)                /*!< 0x00040000 */
#define ETH_MTLTXQ1DR_STXSTSF_Pos           (20U)
#define ETH_MTLTXQ1DR_STXSTSF_Msk           (0x7U << ETH_MTLTXQ1DR_STXSTSF_Pos)                 /*!< 0x00700000 */
#define ETH_MTLTXQ1DR_STXSTSF               ETH_MTLTXQ1DR_STXSTSF_Msk                           /*!< Number of Status Words in Tx Status FIFO of Queue */
#define ETH_MTLTXQ1DR_STXSTSF_0             (0x1U << ETH_MTLTXQ1DR_STXSTSF_Pos)            /*!< 0x00100000 */
#define ETH_MTLTXQ1DR_STXSTSF_1             (0x2U << ETH_MTLTXQ1DR_STXSTSF_Pos)            /*!< 0x00200000 */
#define ETH_MTLTXQ1DR_STXSTSF_2             (0x4U << ETH_MTLTXQ1DR_STXSTSF_Pos)            /*!< 0x00400000 */

/************  Bit definition for ETH_MTLTXQ1ECR register  *************/
#define ETH_MTLTXQ1ECR_AVALG_Pos            (2U)
#define ETH_MTLTXQ1ECR_AVALG_Msk            (0x1U << ETH_MTLTXQ1ECR_AVALG_Pos)                  /*!< 0x00000004 */
#define ETH_MTLTXQ1ECR_AVALG                ETH_MTLTXQ1ECR_AVALG_Msk                            /*!< AV Algorithm */
#define ETH_MTLTXQ1ECR_CC_Pos               (3U)
#define ETH_MTLTXQ1ECR_CC_Msk               (0x1U << ETH_MTLTXQ1ECR_CC_Pos)                     /*!< 0x00000008 */
#define ETH_MTLTXQ1ECR_CC                   ETH_MTLTXQ1ECR_CC_Msk                               /*!< Credit Control */
#define ETH_MTLTXQ1ECR_SLC_Pos              (4U)
#define ETH_MTLTXQ1ECR_SLC_Msk              (0x7U << ETH_MTLTXQ1ECR_SLC_Pos)                    /*!< 0x00000070 */
#define ETH_MTLTXQ1ECR_SLC                  ETH_MTLTXQ1ECR_SLC_Msk                              /*!< Slot Count */
#define ETH_MTLTXQ1ECR_SLC_0                (0x1U << ETH_MTLTXQ1ECR_SLC_Pos)                   /*!< 0x00000010 */
#define ETH_MTLTXQ1ECR_SLC_1                (0x2U << ETH_MTLTXQ1ECR_SLC_Pos)                   /*!< 0x00000020 */
#define ETH_MTLTXQ1ECR_SLC_2                (0x4U << ETH_MTLTXQ1ECR_SLC_Pos)                   /*!< 0x00000040 */

/************  Bit definition for ETH_MTLTXQ1ESR register  *************/
#define ETH_MTLTXQ1ESR_ABS_Pos              (0U)
#define ETH_MTLTXQ1ESR_ABS_Msk              (0xFFFFFFU << ETH_MTLTXQ1ESR_ABS_Pos)               /*!< 0x00FFFFFF */
#define ETH_MTLTXQ1ESR_ABS                  ETH_MTLTXQ1ESR_ABS_Msk                              /*!< Average Bits per Slot */
#define ETH_MTLTXQ1ESR_ABS_0                (0x1U << ETH_MTLTXQ1ESR_ABS_Pos)                    /*!< 0x00000001 */
#define ETH_MTLTXQ1ESR_ABS_1                (0x2U << ETH_MTLTXQ1ESR_ABS_Pos)                    /*!< 0x00000002 */
#define ETH_MTLTXQ1ESR_ABS_2                (0x4U << ETH_MTLTXQ1ESR_ABS_Pos)                    /*!< 0x00000004 */
#define ETH_MTLTXQ1ESR_ABS_3                (0x8U << ETH_MTLTXQ1ESR_ABS_Pos)                    /*!< 0x00000008 */
#define ETH_MTLTXQ1ESR_ABS_4                (0x10U << ETH_MTLTXQ1ESR_ABS_Pos)                   /*!< 0x00000010 */
#define ETH_MTLTXQ1ESR_ABS_5                (0x20U << ETH_MTLTXQ1ESR_ABS_Pos)                   /*!< 0x00000020 */
#define ETH_MTLTXQ1ESR_ABS_6                (0x40U << ETH_MTLTXQ1ESR_ABS_Pos)                   /*!< 0x00000040 */
#define ETH_MTLTXQ1ESR_ABS_7                (0x80U << ETH_MTLTXQ1ESR_ABS_Pos)                   /*!< 0x00000080 */
#define ETH_MTLTXQ1ESR_ABS_8                (0x100U << ETH_MTLTXQ1ESR_ABS_Pos)                  /*!< 0x00000100 */
#define ETH_MTLTXQ1ESR_ABS_9                (0x200U << ETH_MTLTXQ1ESR_ABS_Pos)                  /*!< 0x00000200 */
#define ETH_MTLTXQ1ESR_ABS_10               (0x400U << ETH_MTLTXQ1ESR_ABS_Pos)                  /*!< 0x00000400 */
#define ETH_MTLTXQ1ESR_ABS_11               (0x800U << ETH_MTLTXQ1ESR_ABS_Pos)                  /*!< 0x00000800 */
#define ETH_MTLTXQ1ESR_ABS_12               (0x1000U << ETH_MTLTXQ1ESR_ABS_Pos)                 /*!< 0x00001000 */
#define ETH_MTLTXQ1ESR_ABS_13               (0x2000U << ETH_MTLTXQ1ESR_ABS_Pos)                 /*!< 0x00002000 */
#define ETH_MTLTXQ1ESR_ABS_14               (0x4000U << ETH_MTLTXQ1ESR_ABS_Pos)                 /*!< 0x00004000 */
#define ETH_MTLTXQ1ESR_ABS_15               (0x8000U << ETH_MTLTXQ1ESR_ABS_Pos)                 /*!< 0x00008000 */
#define ETH_MTLTXQ1ESR_ABS_16               (0x10000U << ETH_MTLTXQ1ESR_ABS_Pos)                /*!< 0x00010000 */
#define ETH_MTLTXQ1ESR_ABS_17               (0x20000U << ETH_MTLTXQ1ESR_ABS_Pos)                /*!< 0x00020000 */
#define ETH_MTLTXQ1ESR_ABS_18               (0x40000U << ETH_MTLTXQ1ESR_ABS_Pos)                /*!< 0x00040000 */
#define ETH_MTLTXQ1ESR_ABS_19               (0x80000U << ETH_MTLTXQ1ESR_ABS_Pos)                /*!< 0x00080000 */
#define ETH_MTLTXQ1ESR_ABS_20               (0x100000U << ETH_MTLTXQ1ESR_ABS_Pos)               /*!< 0x00100000 */
#define ETH_MTLTXQ1ESR_ABS_21               (0x200000U << ETH_MTLTXQ1ESR_ABS_Pos)               /*!< 0x00200000 */
#define ETH_MTLTXQ1ESR_ABS_22               (0x400000U << ETH_MTLTXQ1ESR_ABS_Pos)               /*!< 0x00400000 */
#define ETH_MTLTXQ1ESR_ABS_23               (0x800000U << ETH_MTLTXQ1ESR_ABS_Pos)               /*!< 0x00800000 */

/************  Bit definition for ETH_MTLTXQ1QWR register  *************/
#define ETH_MTLTXQ1QWR_ISCQW_Pos            (0U)
#define ETH_MTLTXQ1QWR_ISCQW_Msk            (0x1FFFFFU << ETH_MTLTXQ1QWR_ISCQW_Pos)             /*!< 0x001FFFFF */
#define ETH_MTLTXQ1QWR_ISCQW                ETH_MTLTXQ1QWR_ISCQW_Msk                            /*!< idleSlopeCredit value for queue 1 */
#define ETH_MTLTXQ1QWR_ISCQW_0              (0x1U << ETH_MTLTXQ1QWR_ISCQW_Pos)                  /*!< 0x00000001 */
#define ETH_MTLTXQ1QWR_ISCQW_1              (0x2U << ETH_MTLTXQ1QWR_ISCQW_Pos)                  /*!< 0x00000002 */
#define ETH_MTLTXQ1QWR_ISCQW_2              (0x4U << ETH_MTLTXQ1QWR_ISCQW_Pos)                  /*!< 0x00000004 */
#define ETH_MTLTXQ1QWR_ISCQW_3              (0x8U << ETH_MTLTXQ1QWR_ISCQW_Pos)                  /*!< 0x00000008 */
#define ETH_MTLTXQ1QWR_ISCQW_4              (0x10U << ETH_MTLTXQ1QWR_ISCQW_Pos)                 /*!< 0x00000010 */
#define ETH_MTLTXQ1QWR_ISCQW_5              (0x20U << ETH_MTLTXQ1QWR_ISCQW_Pos)                 /*!< 0x00000020 */
#define ETH_MTLTXQ1QWR_ISCQW_6              (0x40U << ETH_MTLTXQ1QWR_ISCQW_Pos)                 /*!< 0x00000040 */
#define ETH_MTLTXQ1QWR_ISCQW_7              (0x80U << ETH_MTLTXQ1QWR_ISCQW_Pos)                 /*!< 0x00000080 */
#define ETH_MTLTXQ1QWR_ISCQW_8              (0x100U << ETH_MTLTXQ1QWR_ISCQW_Pos)                /*!< 0x00000100 */
#define ETH_MTLTXQ1QWR_ISCQW_9              (0x200U << ETH_MTLTXQ1QWR_ISCQW_Pos)                /*!< 0x00000200 */
#define ETH_MTLTXQ1QWR_ISCQW_10             (0x400U << ETH_MTLTXQ1QWR_ISCQW_Pos)                /*!< 0x00000400 */
#define ETH_MTLTXQ1QWR_ISCQW_11             (0x800U << ETH_MTLTXQ1QWR_ISCQW_Pos)                /*!< 0x00000800 */
#define ETH_MTLTXQ1QWR_ISCQW_12             (0x1000U << ETH_MTLTXQ1QWR_ISCQW_Pos)               /*!< 0x00001000 */
#define ETH_MTLTXQ1QWR_ISCQW_13             (0x2000U << ETH_MTLTXQ1QWR_ISCQW_Pos)               /*!< 0x00002000 */
#define ETH_MTLTXQ1QWR_ISCQW_14             (0x4000U << ETH_MTLTXQ1QWR_ISCQW_Pos)               /*!< 0x00004000 */
#define ETH_MTLTXQ1QWR_ISCQW_15             (0x8000U << ETH_MTLTXQ1QWR_ISCQW_Pos)               /*!< 0x00008000 */
#define ETH_MTLTXQ1QWR_ISCQW_16             (0x10000U << ETH_MTLTXQ1QWR_ISCQW_Pos)              /*!< 0x00010000 */
#define ETH_MTLTXQ1QWR_ISCQW_17             (0x20000U << ETH_MTLTXQ1QWR_ISCQW_Pos)              /*!< 0x00020000 */
#define ETH_MTLTXQ1QWR_ISCQW_18             (0x40000U << ETH_MTLTXQ1QWR_ISCQW_Pos)              /*!< 0x00040000 */
#define ETH_MTLTXQ1QWR_ISCQW_19             (0x80000U << ETH_MTLTXQ1QWR_ISCQW_Pos)              /*!< 0x00080000 */
#define ETH_MTLTXQ1QWR_ISCQW_20             (0x100000U << ETH_MTLTXQ1QWR_ISCQW_Pos)             /*!< 0x00100000 */

/************  Bit definition for ETH_MTLTXQ1SSCR register  ************/
#define ETH_MTLTXQ1SSCR_SSC_Pos             (0U)
#define ETH_MTLTXQ1SSCR_SSC_Msk             (0x3FFFU << ETH_MTLTXQ1SSCR_SSC_Pos)                /*!< 0x00003FFF */
#define ETH_MTLTXQ1SSCR_SSC                 ETH_MTLTXQ1SSCR_SSC_Msk                             /*!< sendSlopeCredit Value */
#define ETH_MTLTXQ1SSCR_SSC_0               (0x1U << ETH_MTLTXQ1SSCR_SSC_Pos)                   /*!< 0x00000001 */
#define ETH_MTLTXQ1SSCR_SSC_1               (0x2U << ETH_MTLTXQ1SSCR_SSC_Pos)                   /*!< 0x00000002 */
#define ETH_MTLTXQ1SSCR_SSC_2               (0x4U << ETH_MTLTXQ1SSCR_SSC_Pos)                   /*!< 0x00000004 */
#define ETH_MTLTXQ1SSCR_SSC_3               (0x8U << ETH_MTLTXQ1SSCR_SSC_Pos)                   /*!< 0x00000008 */
#define ETH_MTLTXQ1SSCR_SSC_4               (0x10U << ETH_MTLTXQ1SSCR_SSC_Pos)                  /*!< 0x00000010 */
#define ETH_MTLTXQ1SSCR_SSC_5               (0x20U << ETH_MTLTXQ1SSCR_SSC_Pos)                  /*!< 0x00000020 */
#define ETH_MTLTXQ1SSCR_SSC_6               (0x40U << ETH_MTLTXQ1SSCR_SSC_Pos)                  /*!< 0x00000040 */
#define ETH_MTLTXQ1SSCR_SSC_7               (0x80U << ETH_MTLTXQ1SSCR_SSC_Pos)                  /*!< 0x00000080 */
#define ETH_MTLTXQ1SSCR_SSC_8               (0x100U << ETH_MTLTXQ1SSCR_SSC_Pos)                 /*!< 0x00000100 */
#define ETH_MTLTXQ1SSCR_SSC_9               (0x200U << ETH_MTLTXQ1SSCR_SSC_Pos)                 /*!< 0x00000200 */
#define ETH_MTLTXQ1SSCR_SSC_10              (0x400U << ETH_MTLTXQ1SSCR_SSC_Pos)                 /*!< 0x00000400 */
#define ETH_MTLTXQ1SSCR_SSC_11              (0x800U << ETH_MTLTXQ1SSCR_SSC_Pos)                 /*!< 0x00000800 */
#define ETH_MTLTXQ1SSCR_SSC_12              (0x1000U << ETH_MTLTXQ1SSCR_SSC_Pos)                /*!< 0x00001000 */
#define ETH_MTLTXQ1SSCR_SSC_13              (0x2000U << ETH_MTLTXQ1SSCR_SSC_Pos)                /*!< 0x00002000 */

/************  Bit definition for ETH_MTLTXQ1HCR register  *************/
#define ETH_MTLTXQ1HCR_HC_Pos               (0U)
#define ETH_MTLTXQ1HCR_HC_Msk               (0x1FFFFFFFU << ETH_MTLTXQ1HCR_HC_Pos)              /*!< 0x1FFFFFFF */
#define ETH_MTLTXQ1HCR_HC                   ETH_MTLTXQ1HCR_HC_Msk                               /*!< hiCredit Value */
#define ETH_MTLTXQ1HCR_HC_0                 (0x1U << ETH_MTLTXQ1HCR_HC_Pos)                     /*!< 0x00000001 */
#define ETH_MTLTXQ1HCR_HC_1                 (0x2U << ETH_MTLTXQ1HCR_HC_Pos)                     /*!< 0x00000002 */
#define ETH_MTLTXQ1HCR_HC_2                 (0x4U << ETH_MTLTXQ1HCR_HC_Pos)                     /*!< 0x00000004 */
#define ETH_MTLTXQ1HCR_HC_3                 (0x8U << ETH_MTLTXQ1HCR_HC_Pos)                     /*!< 0x00000008 */
#define ETH_MTLTXQ1HCR_HC_4                 (0x10U << ETH_MTLTXQ1HCR_HC_Pos)                    /*!< 0x00000010 */
#define ETH_MTLTXQ1HCR_HC_5                 (0x20U << ETH_MTLTXQ1HCR_HC_Pos)                    /*!< 0x00000020 */
#define ETH_MTLTXQ1HCR_HC_6                 (0x40U << ETH_MTLTXQ1HCR_HC_Pos)                    /*!< 0x00000040 */
#define ETH_MTLTXQ1HCR_HC_7                 (0x80U << ETH_MTLTXQ1HCR_HC_Pos)                    /*!< 0x00000080 */
#define ETH_MTLTXQ1HCR_HC_8                 (0x100U << ETH_MTLTXQ1HCR_HC_Pos)                   /*!< 0x00000100 */
#define ETH_MTLTXQ1HCR_HC_9                 (0x200U << ETH_MTLTXQ1HCR_HC_Pos)                   /*!< 0x00000200 */
#define ETH_MTLTXQ1HCR_HC_10                (0x400U << ETH_MTLTXQ1HCR_HC_Pos)                   /*!< 0x00000400 */
#define ETH_MTLTXQ1HCR_HC_11                (0x800U << ETH_MTLTXQ1HCR_HC_Pos)                   /*!< 0x00000800 */
#define ETH_MTLTXQ1HCR_HC_12                (0x1000U << ETH_MTLTXQ1HCR_HC_Pos)                  /*!< 0x00001000 */
#define ETH_MTLTXQ1HCR_HC_13                (0x2000U << ETH_MTLTXQ1HCR_HC_Pos)                  /*!< 0x00002000 */
#define ETH_MTLTXQ1HCR_HC_14                (0x4000U << ETH_MTLTXQ1HCR_HC_Pos)                  /*!< 0x00004000 */
#define ETH_MTLTXQ1HCR_HC_15                (0x8000U << ETH_MTLTXQ1HCR_HC_Pos)                  /*!< 0x00008000 */
#define ETH_MTLTXQ1HCR_HC_16                (0x10000U << ETH_MTLTXQ1HCR_HC_Pos)                 /*!< 0x00010000 */
#define ETH_MTLTXQ1HCR_HC_17                (0x20000U << ETH_MTLTXQ1HCR_HC_Pos)                 /*!< 0x00020000 */
#define ETH_MTLTXQ1HCR_HC_18                (0x40000U << ETH_MTLTXQ1HCR_HC_Pos)                 /*!< 0x00040000 */
#define ETH_MTLTXQ1HCR_HC_19                (0x80000U << ETH_MTLTXQ1HCR_HC_Pos)                 /*!< 0x00080000 */
#define ETH_MTLTXQ1HCR_HC_20                (0x100000U << ETH_MTLTXQ1HCR_HC_Pos)                /*!< 0x00100000 */
#define ETH_MTLTXQ1HCR_HC_21                (0x200000U << ETH_MTLTXQ1HCR_HC_Pos)                /*!< 0x00200000 */
#define ETH_MTLTXQ1HCR_HC_22                (0x400000U << ETH_MTLTXQ1HCR_HC_Pos)                /*!< 0x00400000 */
#define ETH_MTLTXQ1HCR_HC_23                (0x800000U << ETH_MTLTXQ1HCR_HC_Pos)                /*!< 0x00800000 */
#define ETH_MTLTXQ1HCR_HC_24                (0x1000000U << ETH_MTLTXQ1HCR_HC_Pos)               /*!< 0x01000000 */
#define ETH_MTLTXQ1HCR_HC_25                (0x2000000U << ETH_MTLTXQ1HCR_HC_Pos)               /*!< 0x02000000 */
#define ETH_MTLTXQ1HCR_HC_26                (0x4000000U << ETH_MTLTXQ1HCR_HC_Pos)               /*!< 0x04000000 */
#define ETH_MTLTXQ1HCR_HC_27                (0x8000000U << ETH_MTLTXQ1HCR_HC_Pos)               /*!< 0x08000000 */
#define ETH_MTLTXQ1HCR_HC_28                (0x10000000U << ETH_MTLTXQ1HCR_HC_Pos)              /*!< 0x10000000 */

/************  Bit definition for ETH_MTLTXQ1LCR register  *************/
#define ETH_MTLTXQ1LCR_LC_Pos               (0U)
#define ETH_MTLTXQ1LCR_LC_Msk               (0x1FFFFFFFU << ETH_MTLTXQ1LCR_LC_Pos)              /*!< 0x1FFFFFFF */
#define ETH_MTLTXQ1LCR_LC                   ETH_MTLTXQ1LCR_LC_Msk                               /*!< loCredit Value */
#define ETH_MTLTXQ1LCR_LC_0                 (0x1U << ETH_MTLTXQ1LCR_LC_Pos)                     /*!< 0x00000001 */
#define ETH_MTLTXQ1LCR_LC_1                 (0x2U << ETH_MTLTXQ1LCR_LC_Pos)                     /*!< 0x00000002 */
#define ETH_MTLTXQ1LCR_LC_2                 (0x4U << ETH_MTLTXQ1LCR_LC_Pos)                     /*!< 0x00000004 */
#define ETH_MTLTXQ1LCR_LC_3                 (0x8U << ETH_MTLTXQ1LCR_LC_Pos)                     /*!< 0x00000008 */
#define ETH_MTLTXQ1LCR_LC_4                 (0x10U << ETH_MTLTXQ1LCR_LC_Pos)                    /*!< 0x00000010 */
#define ETH_MTLTXQ1LCR_LC_5                 (0x20U << ETH_MTLTXQ1LCR_LC_Pos)                    /*!< 0x00000020 */
#define ETH_MTLTXQ1LCR_LC_6                 (0x40U << ETH_MTLTXQ1LCR_LC_Pos)                    /*!< 0x00000040 */
#define ETH_MTLTXQ1LCR_LC_7                 (0x80U << ETH_MTLTXQ1LCR_LC_Pos)                    /*!< 0x00000080 */
#define ETH_MTLTXQ1LCR_LC_8                 (0x100U << ETH_MTLTXQ1LCR_LC_Pos)                   /*!< 0x00000100 */
#define ETH_MTLTXQ1LCR_LC_9                 (0x200U << ETH_MTLTXQ1LCR_LC_Pos)                   /*!< 0x00000200 */
#define ETH_MTLTXQ1LCR_LC_10                (0x400U << ETH_MTLTXQ1LCR_LC_Pos)                   /*!< 0x00000400 */
#define ETH_MTLTXQ1LCR_LC_11                (0x800U << ETH_MTLTXQ1LCR_LC_Pos)                   /*!< 0x00000800 */
#define ETH_MTLTXQ1LCR_LC_12                (0x1000U << ETH_MTLTXQ1LCR_LC_Pos)                  /*!< 0x00001000 */
#define ETH_MTLTXQ1LCR_LC_13                (0x2000U << ETH_MTLTXQ1LCR_LC_Pos)                  /*!< 0x00002000 */
#define ETH_MTLTXQ1LCR_LC_14                (0x4000U << ETH_MTLTXQ1LCR_LC_Pos)                  /*!< 0x00004000 */
#define ETH_MTLTXQ1LCR_LC_15                (0x8000U << ETH_MTLTXQ1LCR_LC_Pos)                  /*!< 0x00008000 */
#define ETH_MTLTXQ1LCR_LC_16                (0x10000U << ETH_MTLTXQ1LCR_LC_Pos)                 /*!< 0x00010000 */
#define ETH_MTLTXQ1LCR_LC_17                (0x20000U << ETH_MTLTXQ1LCR_LC_Pos)                 /*!< 0x00020000 */
#define ETH_MTLTXQ1LCR_LC_18                (0x40000U << ETH_MTLTXQ1LCR_LC_Pos)                 /*!< 0x00040000 */
#define ETH_MTLTXQ1LCR_LC_19                (0x80000U << ETH_MTLTXQ1LCR_LC_Pos)                 /*!< 0x00080000 */
#define ETH_MTLTXQ1LCR_LC_20                (0x100000U << ETH_MTLTXQ1LCR_LC_Pos)                /*!< 0x00100000 */
#define ETH_MTLTXQ1LCR_LC_21                (0x200000U << ETH_MTLTXQ1LCR_LC_Pos)                /*!< 0x00200000 */
#define ETH_MTLTXQ1LCR_LC_22                (0x400000U << ETH_MTLTXQ1LCR_LC_Pos)                /*!< 0x00400000 */
#define ETH_MTLTXQ1LCR_LC_23                (0x800000U << ETH_MTLTXQ1LCR_LC_Pos)                /*!< 0x00800000 */
#define ETH_MTLTXQ1LCR_LC_24                (0x1000000U << ETH_MTLTXQ1LCR_LC_Pos)               /*!< 0x01000000 */
#define ETH_MTLTXQ1LCR_LC_25                (0x2000000U << ETH_MTLTXQ1LCR_LC_Pos)               /*!< 0x02000000 */
#define ETH_MTLTXQ1LCR_LC_26                (0x4000000U << ETH_MTLTXQ1LCR_LC_Pos)               /*!< 0x04000000 */
#define ETH_MTLTXQ1LCR_LC_27                (0x8000000U << ETH_MTLTXQ1LCR_LC_Pos)               /*!< 0x08000000 */
#define ETH_MTLTXQ1LCR_LC_28                (0x10000000U << ETH_MTLTXQ1LCR_LC_Pos)              /*!< 0x10000000 */

/*************  Bit definition for ETH_MTLQ1ICSR register  *************/
#define ETH_MTLQ1ICSR_TXUNFIS_Pos           (0U)
#define ETH_MTLQ1ICSR_TXUNFIS_Msk           (0x1U << ETH_MTLQ1ICSR_TXUNFIS_Pos)                 /*!< 0x00000001 */
#define ETH_MTLQ1ICSR_TXUNFIS               ETH_MTLQ1ICSR_TXUNFIS_Msk                           /*!< Transmit Queue Underflow Interrupt Status */
#define ETH_MTLQ1ICSR_ABPSIS_Pos            (1U)
#define ETH_MTLQ1ICSR_ABPSIS_Msk            (0x1U << ETH_MTLQ1ICSR_ABPSIS_Pos)                  /*!< 0x00000002 */
#define ETH_MTLQ1ICSR_ABPSIS                ETH_MTLQ1ICSR_ABPSIS_Msk                            /*!< Average Bits Per Slot Interrupt Status */
#define ETH_MTLQ1ICSR_TXUIE_Pos             (8U)
#define ETH_MTLQ1ICSR_TXUIE_Msk             (0x1U << ETH_MTLQ1ICSR_TXUIE_Pos)                   /*!< 0x00000100 */
#define ETH_MTLQ1ICSR_TXUIE                 ETH_MTLQ1ICSR_TXUIE_Msk                             /*!< Transmit Queue Underflow Interrupt Enable */
#define ETH_MTLQ1ICSR_ABPSIE_Pos            (9U)
#define ETH_MTLQ1ICSR_ABPSIE_Msk            (0x1U << ETH_MTLQ1ICSR_ABPSIE_Pos)                  /*!< 0x00000200 */
#define ETH_MTLQ1ICSR_ABPSIE                ETH_MTLQ1ICSR_ABPSIE_Msk                            /*!< Average Bits Per Slot Interrupt Enable */
#define ETH_MTLQ1ICSR_RXOVFIS_Pos           (16U)
#define ETH_MTLQ1ICSR_RXOVFIS_Msk           (0x1U << ETH_MTLQ1ICSR_RXOVFIS_Pos)                 /*!< 0x00010000 */
#define ETH_MTLQ1ICSR_RXOVFIS               ETH_MTLQ1ICSR_RXOVFIS_Msk                           /*!< Receive Queue Overflow Interrupt Status */
#define ETH_MTLQ1ICSR_RXOIE_Pos             (24U)
#define ETH_MTLQ1ICSR_RXOIE_Msk             (0x1U << ETH_MTLQ1ICSR_RXOIE_Pos)                   /*!< 0x01000000 */
#define ETH_MTLQ1ICSR_RXOIE                 ETH_MTLQ1ICSR_RXOIE_Msk                             /*!< Receive Queue Overflow Interrupt Enable */

/************  Bit definition for ETH_MTLRXQ1OMR register  *************/
#define ETH_MTLRXQ1OMR_RTC_Pos              (0U)
#define ETH_MTLRXQ1OMR_RTC_Msk              (0x3U << ETH_MTLRXQ1OMR_RTC_Pos)                    /*!< 0x00000003 */
#define ETH_MTLRXQ1OMR_RTC                  ETH_MTLRXQ1OMR_RTC_Msk                              /*!< Receive Queue Threshold Control */
#define ETH_MTLRXQ1OMR_RTC_0                (0x1U << ETH_MTLRXQ1OMR_RTC_Pos)                    /*!< 0x00000001 */
#define ETH_MTLRXQ1OMR_RTC_1                (0x2U << ETH_MTLRXQ1OMR_RTC_Pos)                    /*!< 0x00000002 */
#define ETH_MTLRXQ1OMR_FUP_Pos              (3U)
#define ETH_MTLRXQ1OMR_FUP_Msk              (0x1U << ETH_MTLRXQ1OMR_FUP_Pos)                    /*!< 0x00000008 */
#define ETH_MTLRXQ1OMR_FUP                  ETH_MTLRXQ1OMR_FUP_Msk                              /*!< Forward Undersized Good Packets */
#define ETH_MTLRXQ1OMR_FEP_Pos              (4U)
#define ETH_MTLRXQ1OMR_FEP_Msk              (0x1U << ETH_MTLRXQ1OMR_FEP_Pos)                    /*!< 0x00000010 */
#define ETH_MTLRXQ1OMR_FEP                  ETH_MTLRXQ1OMR_FEP_Msk                              /*!< Forward Error Packets */
#define ETH_MTLRXQ1OMR_RSF_Pos              (5U)
#define ETH_MTLRXQ1OMR_RSF_Msk              (0x1U << ETH_MTLRXQ1OMR_RSF_Pos)                    /*!< 0x00000020 */
#define ETH_MTLRXQ1OMR_RSF                  ETH_MTLRXQ1OMR_RSF_Msk                              /*!< Receive Queue Store and Forward */
#define ETH_MTLRXQ1OMR_DIS_TCP_EF_Pos       (6U)
#define ETH_MTLRXQ1OMR_DIS_TCP_EF_Msk       (0x1U << ETH_MTLRXQ1OMR_DIS_TCP_EF_Pos)             /*!< 0x00000040 */
#define ETH_MTLRXQ1OMR_DIS_TCP_EF           ETH_MTLRXQ1OMR_DIS_TCP_EF_Msk                       /*!< Disable Dropping of TCP/IP Checksum Error Packets */
#define ETH_MTLRXQ1OMR_EHFC_Pos             (7U)
#define ETH_MTLRXQ1OMR_EHFC_Msk             (0x1U << ETH_MTLRXQ1OMR_EHFC_Pos)                   /*!< 0x00000080 */
#define ETH_MTLRXQ1OMR_EHFC                 ETH_MTLRXQ1OMR_EHFC_Msk                             /*!< Enable Hardware Flow Control */
#define ETH_MTLRXQ1OMR_RFA_Pos              (8U)
#define ETH_MTLRXQ1OMR_RFA_Msk              (0x7U << ETH_MTLRXQ1OMR_RFA_Pos)                    /*!< 0x00000700 */
#define ETH_MTLRXQ1OMR_RFA                  ETH_MTLRXQ1OMR_RFA_Msk                              /*!< Threshold for Activating Flow Control (in half-duplex and full-duplex */
#define ETH_MTLRXQ1OMR_RFA_0                (0x1U << ETH_MTLRXQ1OMR_RFA_Pos)                  /*!< 0x00000100 */
#define ETH_MTLRXQ1OMR_RFA_1                (0x2U << ETH_MTLRXQ1OMR_RFA_Pos)                  /*!< 0x00000200 */
#define ETH_MTLRXQ1OMR_RFA_2                (0x4U << ETH_MTLRXQ1OMR_RFA_Pos)                  /*!< 0x00000400 */
#define ETH_MTLRXQ1OMR_RFD_Pos              (14U)
#define ETH_MTLRXQ1OMR_RFD_Msk              (0x7U << ETH_MTLRXQ1OMR_RFD_Pos)                    /*!< 0x0001C000 */
#define ETH_MTLRXQ1OMR_RFD                  ETH_MTLRXQ1OMR_RFD_Msk                              /*!< Threshold for Deactivating Flow Control (in half-duplex and full-duplex modes) */
#define ETH_MTLRXQ1OMR_RFD_0                (0x1U << ETH_MTLRXQ1OMR_RFD_Pos)                 /*!< 0x00004000 */
#define ETH_MTLRXQ1OMR_RFD_1                (0x2U << ETH_MTLRXQ1OMR_RFD_Pos)                 /*!< 0x00008000 */
#define ETH_MTLRXQ1OMR_RFD_2                (0x4U << ETH_MTLRXQ1OMR_RFD_Pos)                /*!< 0x00010000 */
#define ETH_MTLRXQ1OMR_RQS_Pos              (20U)
#define ETH_MTLRXQ1OMR_RQS_Msk              (0xFU << ETH_MTLRXQ1OMR_RQS_Pos)                    /*!< 0x00F00000 */
#define ETH_MTLRXQ1OMR_RQS                  ETH_MTLRXQ1OMR_RQS_Msk                              /*!< Receive Queue Size */
#define ETH_MTLRXQ1OMR_RQS_0                (0x1U << ETH_MTLRXQ1OMR_RQS_Pos)               /*!< 0x00100000 */
#define ETH_MTLRXQ1OMR_RQS_1                (0x2U << ETH_MTLRXQ1OMR_RQS_Pos)               /*!< 0x00200000 */
#define ETH_MTLRXQ1OMR_RQS_2                (0x4U << ETH_MTLRXQ1OMR_RQS_Pos)               /*!< 0x00400000 */
#define ETH_MTLRXQ1OMR_RQS_3                (0x8U << ETH_MTLRXQ1OMR_RQS_Pos)               /*!< 0x00800000 */

/***********  Bit definition for ETH_MTLRXQ1MPOCR register  ************/
#define ETH_MTLRXQ1MPOCR_OVFPKTCNT_Pos      (0U)
#define ETH_MTLRXQ1MPOCR_OVFPKTCNT_Msk      (0x7FFU << ETH_MTLRXQ1MPOCR_OVFPKTCNT_Pos)          /*!< 0x000007FF */
#define ETH_MTLRXQ1MPOCR_OVFPKTCNT          ETH_MTLRXQ1MPOCR_OVFPKTCNT_Msk                      /*!< Overflow Packet Counter */
#define ETH_MTLRXQ1MPOCR_OVFPKTCNT_0        (0x1U << ETH_MTLRXQ1MPOCR_OVFPKTCNT_Pos)            /*!< 0x00000001 */
#define ETH_MTLRXQ1MPOCR_OVFPKTCNT_1        (0x2U << ETH_MTLRXQ1MPOCR_OVFPKTCNT_Pos)            /*!< 0x00000002 */
#define ETH_MTLRXQ1MPOCR_OVFPKTCNT_2        (0x4U << ETH_MTLRXQ1MPOCR_OVFPKTCNT_Pos)            /*!< 0x00000004 */
#define ETH_MTLRXQ1MPOCR_OVFPKTCNT_3        (0x8U << ETH_MTLRXQ1MPOCR_OVFPKTCNT_Pos)            /*!< 0x00000008 */
#define ETH_MTLRXQ1MPOCR_OVFPKTCNT_4        (0x10U << ETH_MTLRXQ1MPOCR_OVFPKTCNT_Pos)           /*!< 0x00000010 */
#define ETH_MTLRXQ1MPOCR_OVFPKTCNT_5        (0x20U << ETH_MTLRXQ1MPOCR_OVFPKTCNT_Pos)           /*!< 0x00000020 */
#define ETH_MTLRXQ1MPOCR_OVFPKTCNT_6        (0x40U << ETH_MTLRXQ1MPOCR_OVFPKTCNT_Pos)           /*!< 0x00000040 */
#define ETH_MTLRXQ1MPOCR_OVFPKTCNT_7        (0x80U << ETH_MTLRXQ1MPOCR_OVFPKTCNT_Pos)           /*!< 0x00000080 */
#define ETH_MTLRXQ1MPOCR_OVFPKTCNT_8        (0x100U << ETH_MTLRXQ1MPOCR_OVFPKTCNT_Pos)          /*!< 0x00000100 */
#define ETH_MTLRXQ1MPOCR_OVFPKTCNT_9        (0x200U << ETH_MTLRXQ1MPOCR_OVFPKTCNT_Pos)          /*!< 0x00000200 */
#define ETH_MTLRXQ1MPOCR_OVFPKTCNT_10       (0x400U << ETH_MTLRXQ1MPOCR_OVFPKTCNT_Pos)          /*!< 0x00000400 */
#define ETH_MTLRXQ1MPOCR_OVFCNTOVF_Pos      (11U)
#define ETH_MTLRXQ1MPOCR_OVFCNTOVF_Msk      (0x1U << ETH_MTLRXQ1MPOCR_OVFCNTOVF_Pos)            /*!< 0x00000800 */
#define ETH_MTLRXQ1MPOCR_OVFCNTOVF          ETH_MTLRXQ1MPOCR_OVFCNTOVF_Msk                      /*!< Overflow Counter Overflow Bit */
#define ETH_MTLRXQ1MPOCR_MISPKTCNT_Pos      (16U)
#define ETH_MTLRXQ1MPOCR_MISPKTCNT_Msk      (0x7FFU << ETH_MTLRXQ1MPOCR_MISPKTCNT_Pos)          /*!< 0x07FF0000 */
#define ETH_MTLRXQ1MPOCR_MISPKTCNT          ETH_MTLRXQ1MPOCR_MISPKTCNT_Msk                      /*!< Missed Packet Counter */
#define ETH_MTLRXQ1MPOCR_MISPKTCNT_0        (0x1U << ETH_MTLRXQ1MPOCR_MISPKTCNT_Pos)        /*!< 0x00010000 */
#define ETH_MTLRXQ1MPOCR_MISPKTCNT_1        (0x2U << ETH_MTLRXQ1MPOCR_MISPKTCNT_Pos)        /*!< 0x00020000 */
#define ETH_MTLRXQ1MPOCR_MISPKTCNT_2        (0x4U << ETH_MTLRXQ1MPOCR_MISPKTCNT_Pos)        /*!< 0x00040000 */
#define ETH_MTLRXQ1MPOCR_MISPKTCNT_3        (0x8U << ETH_MTLRXQ1MPOCR_MISPKTCNT_Pos)        /*!< 0x00080000 */
#define ETH_MTLRXQ1MPOCR_MISPKTCNT_4        (0x10U << ETH_MTLRXQ1MPOCR_MISPKTCNT_Pos)       /*!< 0x00100000 */
#define ETH_MTLRXQ1MPOCR_MISPKTCNT_5        (0x20U << ETH_MTLRXQ1MPOCR_MISPKTCNT_Pos)       /*!< 0x00200000 */
#define ETH_MTLRXQ1MPOCR_MISPKTCNT_6        (0x40U << ETH_MTLRXQ1MPOCR_MISPKTCNT_Pos)       /*!< 0x00400000 */
#define ETH_MTLRXQ1MPOCR_MISPKTCNT_7        (0x80U << ETH_MTLRXQ1MPOCR_MISPKTCNT_Pos)       /*!< 0x00800000 */
#define ETH_MTLRXQ1MPOCR_MISPKTCNT_8        (0x100U << ETH_MTLRXQ1MPOCR_MISPKTCNT_Pos)      /*!< 0x01000000 */
#define ETH_MTLRXQ1MPOCR_MISPKTCNT_9        (0x200U << ETH_MTLRXQ1MPOCR_MISPKTCNT_Pos)      /*!< 0x02000000 */
#define ETH_MTLRXQ1MPOCR_MISPKTCNT_10       (0x400U << ETH_MTLRXQ1MPOCR_MISPKTCNT_Pos)      /*!< 0x04000000 */
#define ETH_MTLRXQ1MPOCR_MISCNTOVF_Pos      (27U)
#define ETH_MTLRXQ1MPOCR_MISCNTOVF_Msk      (0x1U << ETH_MTLRXQ1MPOCR_MISCNTOVF_Pos)            /*!< 0x08000000 */
#define ETH_MTLRXQ1MPOCR_MISCNTOVF          ETH_MTLRXQ1MPOCR_MISCNTOVF_Msk                      /*!< Missed Packet Counter Overflow Bit */

/*************  Bit definition for ETH_MTLRXQ1DR register  *************/
#define ETH_MTLRXQ1DR_RWCSTS_Pos            (0U)
#define ETH_MTLRXQ1DR_RWCSTS_Msk            (0x1U << ETH_MTLRXQ1DR_RWCSTS_Pos)                  /*!< 0x00000001 */
#define ETH_MTLRXQ1DR_RWCSTS                ETH_MTLRXQ1DR_RWCSTS_Msk                            /*!< MTL Rx Queue Write Controller Active Status */
#define ETH_MTLRXQ1DR_RRCSTS_Pos            (1U)
#define ETH_MTLRXQ1DR_RRCSTS_Msk            (0x3U << ETH_MTLRXQ1DR_RRCSTS_Pos)                  /*!< 0x00000006 */
#define ETH_MTLRXQ1DR_RRCSTS                ETH_MTLRXQ1DR_RRCSTS_Msk                            /*!< MTL Rx Queue Read Controller State */
#define ETH_MTLRXQ1DR_RRCSTS_0              (0x1U << ETH_MTLRXQ1DR_RRCSTS_Pos)                  /*!< 0x00000002 */
#define ETH_MTLRXQ1DR_RRCSTS_1              (0x2U << ETH_MTLRXQ1DR_RRCSTS_Pos)                  /*!< 0x00000004 */
#define ETH_MTLRXQ1DR_RXQSTS_Pos            (4U)
#define ETH_MTLRXQ1DR_RXQSTS_Msk            (0x3U << ETH_MTLRXQ1DR_RXQSTS_Pos)                  /*!< 0x00000030 */
#define ETH_MTLRXQ1DR_RXQSTS                ETH_MTLRXQ1DR_RXQSTS_Msk                            /*!< MTL Rx Queue Fill-Level Status */
#define ETH_MTLRXQ1DR_RXQSTS_0              (0x1U << ETH_MTLRXQ1DR_RXQSTS_Pos)                 /*!< 0x00000010 */
#define ETH_MTLRXQ1DR_RXQSTS_1              (0x2U << ETH_MTLRXQ1DR_RXQSTS_Pos)                 /*!< 0x00000020 */
#define ETH_MTLRXQ1DR_PRXQ_Pos              (16U)
#define ETH_MTLRXQ1DR_PRXQ_Msk              (0x3FFFU << ETH_MTLRXQ1DR_PRXQ_Pos)                 /*!< 0x3FFF0000 */
#define ETH_MTLRXQ1DR_PRXQ                  ETH_MTLRXQ1DR_PRXQ_Msk                              /*!< Number of Packets in Receive Queue */
#define ETH_MTLRXQ1DR_PRXQ_0                (0x1U << ETH_MTLRXQ1DR_PRXQ_Pos)                /*!< 0x00010000 */
#define ETH_MTLRXQ1DR_PRXQ_1                (0x2U << ETH_MTLRXQ1DR_PRXQ_Pos)                /*!< 0x00020000 */
#define ETH_MTLRXQ1DR_PRXQ_2                (0x4U << ETH_MTLRXQ1DR_PRXQ_Pos)                /*!< 0x00040000 */
#define ETH_MTLRXQ1DR_PRXQ_3                (0x8U << ETH_MTLRXQ1DR_PRXQ_Pos)                /*!< 0x00080000 */
#define ETH_MTLRXQ1DR_PRXQ_4                (0x10U << ETH_MTLRXQ1DR_PRXQ_Pos)               /*!< 0x00100000 */
#define ETH_MTLRXQ1DR_PRXQ_5                (0x20U << ETH_MTLRXQ1DR_PRXQ_Pos)               /*!< 0x00200000 */
#define ETH_MTLRXQ1DR_PRXQ_6                (0x40U << ETH_MTLRXQ1DR_PRXQ_Pos)               /*!< 0x00400000 */
#define ETH_MTLRXQ1DR_PRXQ_7                (0x80U << ETH_MTLRXQ1DR_PRXQ_Pos)               /*!< 0x00800000 */
#define ETH_MTLRXQ1DR_PRXQ_8                (0x100U << ETH_MTLRXQ1DR_PRXQ_Pos)              /*!< 0x01000000 */
#define ETH_MTLRXQ1DR_PRXQ_9                (0x200U << ETH_MTLRXQ1DR_PRXQ_Pos)              /*!< 0x02000000 */
#define ETH_MTLRXQ1DR_PRXQ_10               (0x400U << ETH_MTLRXQ1DR_PRXQ_Pos)              /*!< 0x04000000 */
#define ETH_MTLRXQ1DR_PRXQ_11               (0x800U << ETH_MTLRXQ1DR_PRXQ_Pos)              /*!< 0x08000000 */
#define ETH_MTLRXQ1DR_PRXQ_12               (0x1000U << ETH_MTLRXQ1DR_PRXQ_Pos)             /*!< 0x10000000 */
#define ETH_MTLRXQ1DR_PRXQ_13               (0x2000U << ETH_MTLRXQ1DR_PRXQ_Pos)             /*!< 0x20000000 */

/*************  Bit definition for ETH_MTLRXQ1CR register  *************/
#define ETH_MTLRXQ1CR_RXQ_WEGT_Pos          (0U)
#define ETH_MTLRXQ1CR_RXQ_WEGT_Msk          (0x7U << ETH_MTLRXQ1CR_RXQ_WEGT_Pos)                /*!< 0x00000007 */
#define ETH_MTLRXQ1CR_RXQ_WEGT              ETH_MTLRXQ1CR_RXQ_WEGT_Msk                          /*!< Receive Queue Weight */
#define ETH_MTLRXQ1CR_RXQ_WEGT_0            (0x1U << ETH_MTLRXQ1CR_RXQ_WEGT_Pos)                /*!< 0x00000001 */
#define ETH_MTLRXQ1CR_RXQ_WEGT_1            (0x2U << ETH_MTLRXQ1CR_RXQ_WEGT_Pos)                /*!< 0x00000002 */
#define ETH_MTLRXQ1CR_RXQ_WEGT_2            (0x4U << ETH_MTLRXQ1CR_RXQ_WEGT_Pos)                /*!< 0x00000004 */
#define ETH_MTLRXQ1CR_RXQ_FRM_ARBIT_Pos     (3U)
#define ETH_MTLRXQ1CR_RXQ_FRM_ARBIT_Msk     (0x1U << ETH_MTLRXQ1CR_RXQ_FRM_ARBIT_Pos)           /*!< 0x00000008 */
#define ETH_MTLRXQ1CR_RXQ_FRM_ARBIT         ETH_MTLRXQ1CR_RXQ_FRM_ARBIT_Msk                     /*!< Receive Queue Packet Arbitration */

/***************  Bit definition for ETH_DMAMR register  ***************/
#define ETH_DMAMR_SWR_Pos                   (0U)
#define ETH_DMAMR_SWR_Msk                   (0x1U << ETH_DMAMR_SWR_Pos)                         /*!< 0x00000001 */
#define ETH_DMAMR_SWR                       ETH_DMAMR_SWR_Msk                                   /*!< Software Reset */
#define ETH_DMAMR_TAA_Pos                   (2U)
#define ETH_DMAMR_TAA_Msk                   (0x7U << ETH_DMAMR_TAA_Pos)                         /*!< 0x0000001C */
#define ETH_DMAMR_TAA                       ETH_DMAMR_TAA_Msk                                   /*!< Transmit Arbitration Algorithm */
#define ETH_DMAMR_TAA_0                     (0x1U << ETH_DMAMR_TAA_Pos)                         /*!< 0x00000004 */
#define ETH_DMAMR_TAA_1                     (0x2U << ETH_DMAMR_TAA_Pos)                         /*!< 0x00000008 */
#define ETH_DMAMR_TAA_2                     (0x4U << ETH_DMAMR_TAA_Pos)                        /*!< 0x00000010 */
#define ETH_DMAMR_TXPR_Pos                  (11U)
#define ETH_DMAMR_TXPR_Msk                  (0x1U << ETH_DMAMR_TXPR_Pos)                        /*!< 0x00000800 */
#define ETH_DMAMR_TXPR                      ETH_DMAMR_TXPR_Msk                                  /*!< Transmit priority */
#define ETH_DMAMR_PR_Pos                    (12U)
#define ETH_DMAMR_PR_Msk                    (0x7U << ETH_DMAMR_PR_Pos)                          /*!< 0x00007000 */
#define ETH_DMAMR_PR                        ETH_DMAMR_PR_Msk                                    /*!< Priority ratio */
#define ETH_DMAMR_PR_0                      (0x1U << ETH_DMAMR_PR_Pos)                       /*!< 0x00001000 */
#define ETH_DMAMR_PR_1                      (0x2U << ETH_DMAMR_PR_Pos)                       /*!< 0x00002000 */
#define ETH_DMAMR_PR_2                      (0x4U << ETH_DMAMR_PR_Pos)                       /*!< 0x00004000 */
#define ETH_DMAMR_INTM_Pos                  (16U)
#define ETH_DMAMR_INTM_Msk                  (0x3U << ETH_DMAMR_INTM_Pos)                        /*!< 0x00030000 */
#define ETH_DMAMR_INTM                      ETH_DMAMR_INTM_Msk                                  /*!< Interrupt Mode */
#define ETH_DMAMR_INTM_0                    (0x1U << ETH_DMAMR_INTM_Pos)                    /*!< 0x00010000 */
#define ETH_DMAMR_INTM_1                    (0x2U << ETH_DMAMR_INTM_Pos)                    /*!< 0x00020000 */

/**************  Bit definition for ETH_DMASBMR register  **************/
#define ETH_DMASBMR_FB_Pos                  (0U)
#define ETH_DMASBMR_FB_Msk                  (0x1U << ETH_DMASBMR_FB_Pos)                        /*!< 0x00000001 */
#define ETH_DMASBMR_FB                      ETH_DMASBMR_FB_Msk                                  /*!< Fixed Burst Length */
#define ETH_DMASBMR_BLEN4_Pos               (1U)
#define ETH_DMASBMR_BLEN4_Msk               (0x1U << ETH_DMASBMR_BLEN4_Pos)                     /*!< 0x00000002 */
#define ETH_DMASBMR_BLEN4                   ETH_DMASBMR_BLEN4_Msk                               /*!< AXI Burst Length 4 */
#define ETH_DMASBMR_BLEN8_Pos               (2U)
#define ETH_DMASBMR_BLEN8_Msk               (0x1U << ETH_DMASBMR_BLEN8_Pos)                     /*!< 0x00000004 */
#define ETH_DMASBMR_BLEN8                   ETH_DMASBMR_BLEN8_Msk                               /*!< AXI Burst Length 8 */
#define ETH_DMASBMR_BLEN16_Pos              (3U)
#define ETH_DMASBMR_BLEN16_Msk              (0x1U << ETH_DMASBMR_BLEN16_Pos)                    /*!< 0x00000008 */
#define ETH_DMASBMR_BLEN16                  ETH_DMASBMR_BLEN16_Msk                              /*!< AXI Burst Length 16 */
#define ETH_DMASBMR_BLEN32_Pos              (4U)
#define ETH_DMASBMR_BLEN32_Msk              (0x1U << ETH_DMASBMR_BLEN32_Pos)                    /*!< 0x00000010 */
#define ETH_DMASBMR_BLEN32                  ETH_DMASBMR_BLEN32_Msk                              /*!< AXI Burst Length 32 */
#define ETH_DMASBMR_BLEN64_Pos              (5U)
#define ETH_DMASBMR_BLEN64_Msk              (0x1U << ETH_DMASBMR_BLEN64_Pos)                    /*!< 0x00000020 */
#define ETH_DMASBMR_BLEN64                  ETH_DMASBMR_BLEN64_Msk                              /*!< AXI Burst Length 64 */
#define ETH_DMASBMR_BLEN128_Pos             (6U)
#define ETH_DMASBMR_BLEN128_Msk             (0x1U << ETH_DMASBMR_BLEN128_Pos)                   /*!< 0x00000040 */
#define ETH_DMASBMR_BLEN128                 ETH_DMASBMR_BLEN128_Msk                             /*!< AXI Burst Length 128 */
#define ETH_DMASBMR_BLEN256_Pos             (7U)
#define ETH_DMASBMR_BLEN256_Msk             (0x1U << ETH_DMASBMR_BLEN256_Pos)                   /*!< 0x00000080 */
#define ETH_DMASBMR_BLEN256                 ETH_DMASBMR_BLEN256_Msk                             /*!< AXI Burst Length 256 */
#define ETH_DMASBMR_AAL_Pos                 (12U)
#define ETH_DMASBMR_AAL_Msk                 (0x1U << ETH_DMASBMR_AAL_Pos)                       /*!< 0x00001000 */
#define ETH_DMASBMR_AAL                     ETH_DMASBMR_AAL_Msk                                 /*!< Address-Aligned Beats */
#define ETH_DMASBMR_ONEKBBE_Pos             (13U)
#define ETH_DMASBMR_ONEKBBE_Msk             (0x1U << ETH_DMASBMR_ONEKBBE_Pos)                   /*!< 0x00002000 */
#define ETH_DMASBMR_ONEKBBE                 ETH_DMASBMR_ONEKBBE_Msk                             /*!< 1 Kbyte Boundary Crossing Enable for the AXI Master */
#define ETH_DMASBMR_RD_OSR_LMT_Pos          (16U)
#define ETH_DMASBMR_RD_OSR_LMT_Msk          (0x3U << ETH_DMASBMR_RD_OSR_LMT_Pos)                /*!< 0x00030000 */
#define ETH_DMASBMR_RD_OSR_LMT              ETH_DMASBMR_RD_OSR_LMT_Msk                          /*!< AXI Maximum Read Outstanding Request Limit */
#define ETH_DMASBMR_RD_OSR_LMT_0            (0x1U << ETH_DMASBMR_RD_OSR_LMT_Pos)            /*!< 0x00010000 */
#define ETH_DMASBMR_RD_OSR_LMT_1            (0x2U << ETH_DMASBMR_RD_OSR_LMT_Pos)            /*!< 0x00020000 */
#define ETH_DMASBMR_WR_OSR_LMT_Pos          (24U)
#define ETH_DMASBMR_WR_OSR_LMT_Msk          (0x3U << ETH_DMASBMR_WR_OSR_LMT_Pos)                /*!< 0x03000000 */
#define ETH_DMASBMR_WR_OSR_LMT              ETH_DMASBMR_WR_OSR_LMT_Msk                          /*!< AXI Maximum Write Outstanding Request Limit */
#define ETH_DMASBMR_WR_OSR_LMT_0            (0x1U << ETH_DMASBMR_WR_OSR_LMT_Pos)          /*!< 0x01000000 */
#define ETH_DMASBMR_WR_OSR_LMT_1            (0x2U << ETH_DMASBMR_WR_OSR_LMT_Pos)          /*!< 0x02000000 */
#define ETH_DMASBMR_LPI_XIT_PKT_Pos         (30U)
#define ETH_DMASBMR_LPI_XIT_PKT_Msk         (0x1U << ETH_DMASBMR_LPI_XIT_PKT_Pos)               /*!< 0x40000000 */
#define ETH_DMASBMR_LPI_XIT_PKT             ETH_DMASBMR_LPI_XIT_PKT_Msk                         /*!< Unlock on Magic Packet or Remote wakeup Packet */
#define ETH_DMASBMR_EN_LPI_Pos              (31U)
#define ETH_DMASBMR_EN_LPI_Msk              (0x1U << ETH_DMASBMR_EN_LPI_Pos)                    /*!< 0x80000000 */
#define ETH_DMASBMR_EN_LPI                  ETH_DMASBMR_EN_LPI_Msk                              /*!< Enable Low Power Interface (LPI) */

/**************  Bit definition for ETH_DMAISR register  ***************/
#define ETH_DMAISR_DC0IS_Pos                (0U)
#define ETH_DMAISR_DC0IS_Msk                (0x1U << ETH_DMAISR_DC0IS_Pos)                      /*!< 0x00000001 */
#define ETH_DMAISR_DC0IS                    ETH_DMAISR_DC0IS_Msk                                /*!< DMA Channel 0 Interrupt Status */
#define ETH_DMAISR_DC1IS_Pos                (1U)
#define ETH_DMAISR_DC1IS_Msk                (0x1U << ETH_DMAISR_DC1IS_Pos)                      /*!< 0x00000002 */
#define ETH_DMAISR_DC1IS                    ETH_DMAISR_DC1IS_Msk                                /*!< DMA Channel 1 Interrupt Status */
#define ETH_DMAISR_MTLIS_Pos                (16U)
#define ETH_DMAISR_MTLIS_Msk                (0x1U << ETH_DMAISR_MTLIS_Pos)                      /*!< 0x00010000 */
#define ETH_DMAISR_MTLIS                    ETH_DMAISR_MTLIS_Msk                                /*!< MTL Interrupt Status */
#define ETH_DMAISR_MACIS_Pos                (17U)
#define ETH_DMAISR_MACIS_Msk                (0x1U << ETH_DMAISR_MACIS_Pos)                      /*!< 0x00020000 */
#define ETH_DMAISR_MACIS                    ETH_DMAISR_MACIS_Msk                                /*!< MAC Interrupt Status */

/**************  Bit definition for ETH_DMADSR register  ***************/
#define ETH_DMADSR_AXWHSTS_Pos              (0U)
#define ETH_DMADSR_AXWHSTS_Msk              (0x1U << ETH_DMADSR_AXWHSTS_Pos)                    /*!< 0x00000001 */
#define ETH_DMADSR_AXWHSTS                  ETH_DMADSR_AXWHSTS_Msk                              /*!< AXI Master Write Channel */
#define ETH_DMADSR_AXRHSTS_Pos              (1U)
#define ETH_DMADSR_AXRHSTS_Msk              (0x1U << ETH_DMADSR_AXRHSTS_Pos)                    /*!< 0x00000002 */
#define ETH_DMADSR_AXRHSTS                  ETH_DMADSR_AXRHSTS_Msk                              /*!< AXI Master Read Channel Status */
#define ETH_DMADSR_RPS0_Pos                 (8U)
#define ETH_DMADSR_RPS0_Msk                 (0xFU << ETH_DMADSR_RPS0_Pos)                       /*!< 0x00000F00 */
#define ETH_DMADSR_RPS0                     ETH_DMADSR_RPS0_Msk                                 /*!< DMA Channel 0 Receive Process State */
#define ETH_DMADSR_RPS0_0                   (0x1U << ETH_DMADSR_RPS0_Pos)                     /*!< 0x00000100 */
#define ETH_DMADSR_RPS0_1                   (0x2U << ETH_DMADSR_RPS0_Pos)                     /*!< 0x00000200 */
#define ETH_DMADSR_RPS0_2                   (0x4U << ETH_DMADSR_RPS0_Pos)                     /*!< 0x00000400 */
#define ETH_DMADSR_RPS0_3                   (0x8U << ETH_DMADSR_RPS0_Pos)                     /*!< 0x00000800 */
#define ETH_DMADSR_TPS0_Pos                 (12U)
#define ETH_DMADSR_TPS0_Msk                 (0xFU << ETH_DMADSR_TPS0_Pos)                       /*!< 0x0000F000 */
#define ETH_DMADSR_TPS0                     ETH_DMADSR_TPS0_Msk                                 /*!< DMA Channel 0 Transmit Process State */
#define ETH_DMADSR_TPS0_0                   (0x1U << ETH_DMADSR_TPS0_Pos)                    /*!< 0x00001000 */
#define ETH_DMADSR_TPS0_1                   (0x2U << ETH_DMADSR_TPS0_Pos)                    /*!< 0x00002000 */
#define ETH_DMADSR_TPS0_2                   (0x4U << ETH_DMADSR_TPS0_Pos)                    /*!< 0x00004000 */
#define ETH_DMADSR_TPS0_3                   (0x8U << ETH_DMADSR_TPS0_Pos)                    /*!< 0x00008000 */
#define ETH_DMADSR_RPS1_Pos                 (16U)
#define ETH_DMADSR_RPS1_Msk                 (0xFU << ETH_DMADSR_RPS1_Pos)                       /*!< 0x000F0000 */
#define ETH_DMADSR_RPS1                     ETH_DMADSR_RPS1_Msk                                 /*!< DMA Channel 1 Receive Process State */
#define ETH_DMADSR_RPS1_0                   (0x1U << ETH_DMADSR_RPS1_Pos)                   /*!< 0x00010000 */
#define ETH_DMADSR_RPS1_1                   (0x2U << ETH_DMADSR_RPS1_Pos)                   /*!< 0x00020000 */
#define ETH_DMADSR_RPS1_2                   (0x4U << ETH_DMADSR_RPS1_Pos)                   /*!< 0x00040000 */
#define ETH_DMADSR_RPS1_3                   (0x8U << ETH_DMADSR_RPS1_Pos)                   /*!< 0x00080000 */
#define ETH_DMADSR_TPS1_Pos                 (20U)
#define ETH_DMADSR_TPS1_Msk                 (0xFU << ETH_DMADSR_TPS1_Pos)                       /*!< 0x00F00000 */
#define ETH_DMADSR_TPS1                     ETH_DMADSR_TPS1_Msk                                 /*!< DMA Channel 1 Transmit Process State */
#define ETH_DMADSR_TPS1_0                   (0x1U << ETH_DMADSR_TPS1_Pos)                  /*!< 0x00100000 */
#define ETH_DMADSR_TPS1_1                   (0x2U << ETH_DMADSR_TPS1_Pos)                  /*!< 0x00200000 */
#define ETH_DMADSR_TPS1_2                   (0x4U << ETH_DMADSR_TPS1_Pos)                  /*!< 0x00400000 */
#define ETH_DMADSR_TPS1_3                   (0x8U << ETH_DMADSR_TPS1_Pos)                  /*!< 0x00800000 */

/************  Bit definition for ETH_DMAA4TXACR register  *************/
#define ETH_DMAA4TXACR_TDRC_Pos             (0U)
#define ETH_DMAA4TXACR_TDRC_Msk             (0xFU << ETH_DMAA4TXACR_TDRC_Pos)                   /*!< 0x0000000F */
#define ETH_DMAA4TXACR_TDRC                 ETH_DMAA4TXACR_TDRC_Msk                             /*!< Transmit DMA Read Descriptor Cache Control */
#define ETH_DMAA4TXACR_TDRC_0               (0x1U << ETH_DMAA4TXACR_TDRC_Pos)                   /*!< 0x00000001 */
#define ETH_DMAA4TXACR_TDRC_1               (0x2U << ETH_DMAA4TXACR_TDRC_Pos)                   /*!< 0x00000002 */
#define ETH_DMAA4TXACR_TDRC_2               (0x4U << ETH_DMAA4TXACR_TDRC_Pos)                   /*!< 0x00000004 */
#define ETH_DMAA4TXACR_TDRC_3               (0x8U << ETH_DMAA4TXACR_TDRC_Pos)                   /*!< 0x00000008 */
#define ETH_DMAA4TXACR_TEC_Pos              (8U)
#define ETH_DMAA4TXACR_TEC_Msk              (0xFU << ETH_DMAA4TXACR_TEC_Pos)                    /*!< 0x00000F00 */
#define ETH_DMAA4TXACR_TEC                  ETH_DMAA4TXACR_TEC_Msk                              /*!< Transmit DMA Extended Packet Buffer or TSO Payload Cache Control */
#define ETH_DMAA4TXACR_TEC_0                (0x1U << ETH_DMAA4TXACR_TEC_Pos)                  /*!< 0x00000100 */
#define ETH_DMAA4TXACR_TEC_1                (0x2U << ETH_DMAA4TXACR_TEC_Pos)                  /*!< 0x00000200 */
#define ETH_DMAA4TXACR_TEC_2                (0x4U << ETH_DMAA4TXACR_TEC_Pos)                  /*!< 0x00000400 */
#define ETH_DMAA4TXACR_TEC_3                (0x8U << ETH_DMAA4TXACR_TEC_Pos)                  /*!< 0x00000800 */
#define ETH_DMAA4TXACR_THC_Pos              (16U)
#define ETH_DMAA4TXACR_THC_Msk              (0xFU << ETH_DMAA4TXACR_THC_Pos)                    /*!< 0x000F0000 */
#define ETH_DMAA4TXACR_THC                  ETH_DMAA4TXACR_THC_Msk                              /*!< Transmit DMA First Packet Buffer or TSO Header Cache Control */
#define ETH_DMAA4TXACR_THC_0                (0x1U << ETH_DMAA4TXACR_THC_Pos)                /*!< 0x00010000 */
#define ETH_DMAA4TXACR_THC_1                (0x2U << ETH_DMAA4TXACR_THC_Pos)                /*!< 0x00020000 */
#define ETH_DMAA4TXACR_THC_2                (0x4U << ETH_DMAA4TXACR_THC_Pos)                /*!< 0x00040000 */
#define ETH_DMAA4TXACR_THC_3                (0x8U << ETH_DMAA4TXACR_THC_Pos)                /*!< 0x00080000 */

/************  Bit definition for ETH_DMAA4RXACR register  *************/
#define ETH_DMAA4RXACR_RDWC_Pos             (0U)
#define ETH_DMAA4RXACR_RDWC_Msk             (0xFU << ETH_DMAA4RXACR_RDWC_Pos)                   /*!< 0x0000000F */
#define ETH_DMAA4RXACR_RDWC                 ETH_DMAA4RXACR_RDWC_Msk                             /*!< Receive DMA Write Descriptor Cache Control */
#define ETH_DMAA4RXACR_RDWC_0               (0x1U << ETH_DMAA4RXACR_RDWC_Pos)                   /*!< 0x00000001 */
#define ETH_DMAA4RXACR_RDWC_1               (0x2U << ETH_DMAA4RXACR_RDWC_Pos)                   /*!< 0x00000002 */
#define ETH_DMAA4RXACR_RDWC_2               (0x4U << ETH_DMAA4RXACR_RDWC_Pos)                   /*!< 0x00000004 */
#define ETH_DMAA4RXACR_RDWC_3               (0x8U << ETH_DMAA4RXACR_RDWC_Pos)                   /*!< 0x00000008 */
#define ETH_DMAA4RXACR_RPC_Pos              (8U)
#define ETH_DMAA4RXACR_RPC_Msk              (0xFU << ETH_DMAA4RXACR_RPC_Pos)                    /*!< 0x00000F00 */
#define ETH_DMAA4RXACR_RPC                  ETH_DMAA4RXACR_RPC_Msk                              /*!< Receive DMA Payload Cache Control */
#define ETH_DMAA4RXACR_RPC_0                (0x1U << ETH_DMAA4RXACR_RPC_Pos)                  /*!< 0x00000100 */
#define ETH_DMAA4RXACR_RPC_1                (0x2U << ETH_DMAA4RXACR_RPC_Pos)                  /*!< 0x00000200 */
#define ETH_DMAA4RXACR_RPC_2                (0x4U << ETH_DMAA4RXACR_RPC_Pos)                  /*!< 0x00000400 */
#define ETH_DMAA4RXACR_RPC_3                (0x8U << ETH_DMAA4RXACR_RPC_Pos)                  /*!< 0x00000800 */
#define ETH_DMAA4RXACR_RHC_Pos              (16U)
#define ETH_DMAA4RXACR_RHC_Msk              (0xFU << ETH_DMAA4RXACR_RHC_Pos)                    /*!< 0x000F0000 */
#define ETH_DMAA4RXACR_RHC                  ETH_DMAA4RXACR_RHC_Msk                              /*!< Receive DMA Header Cache Control */
#define ETH_DMAA4RXACR_RHC_0                (0x1U << ETH_DMAA4RXACR_RHC_Pos)                /*!< 0x00010000 */
#define ETH_DMAA4RXACR_RHC_1                (0x2U << ETH_DMAA4RXACR_RHC_Pos)                /*!< 0x00020000 */
#define ETH_DMAA4RXACR_RHC_2                (0x4U << ETH_DMAA4RXACR_RHC_Pos)                /*!< 0x00040000 */
#define ETH_DMAA4RXACR_RHC_3                (0x8U << ETH_DMAA4RXACR_RHC_Pos)                /*!< 0x00080000 */
#define ETH_DMAA4RXACR_RDC_Pos              (24U)
#define ETH_DMAA4RXACR_RDC_Msk              (0xFU << ETH_DMAA4RXACR_RDC_Pos)                    /*!< 0x0F000000 */
#define ETH_DMAA4RXACR_RDC                  ETH_DMAA4RXACR_RDC_Msk                              /*!< Receive DMA Buffer Cache Control */
#define ETH_DMAA4RXACR_RDC_0                (0x1U << ETH_DMAA4RXACR_RDC_Pos)              /*!< 0x01000000 */
#define ETH_DMAA4RXACR_RDC_1                (0x2U << ETH_DMAA4RXACR_RDC_Pos)              /*!< 0x02000000 */
#define ETH_DMAA4RXACR_RDC_2                (0x4U << ETH_DMAA4RXACR_RDC_Pos)              /*!< 0x04000000 */
#define ETH_DMAA4RXACR_RDC_3                (0x8U << ETH_DMAA4RXACR_RDC_Pos)              /*!< 0x08000000 */

/*************  Bit definition for ETH_DMAA4DACR register  *************/
#define ETH_DMAA4DACR_TDWC_Pos              (0U)
#define ETH_DMAA4DACR_TDWC_Msk              (0xFU << ETH_DMAA4DACR_TDWC_Pos)                    /*!< 0x0000000F */
#define ETH_DMAA4DACR_TDWC                  ETH_DMAA4DACR_TDWC_Msk                              /*!< Transmit DMA Write Descriptor Cache control */
#define ETH_DMAA4DACR_TDWC_0                (0x1U << ETH_DMAA4DACR_TDWC_Pos)                    /*!< 0x00000001 */
#define ETH_DMAA4DACR_TDWC_1                (0x2U << ETH_DMAA4DACR_TDWC_Pos)                    /*!< 0x00000002 */
#define ETH_DMAA4DACR_TDWC_2                (0x4U << ETH_DMAA4DACR_TDWC_Pos)                    /*!< 0x00000004 */
#define ETH_DMAA4DACR_TDWC_3                (0x8U << ETH_DMAA4DACR_TDWC_Pos)                    /*!< 0x00000008 */
#define ETH_DMAA4DACR_TDWD_Pos              (4U)
#define ETH_DMAA4DACR_TDWD_Msk              (0x3U << ETH_DMAA4DACR_TDWD_Pos)                    /*!< 0x00000030 */
#define ETH_DMAA4DACR_TDWD                  ETH_DMAA4DACR_TDWD_Msk                              /*!< Transmit DMA Write Descriptor Domain control */
#define ETH_DMAA4DACR_TDWD_0                (0x1U << ETH_DMAA4DACR_TDWD_Pos)                   /*!< 0x00000010 */
#define ETH_DMAA4DACR_TDWD_1                (0x2U << ETH_DMAA4DACR_TDWD_Pos)                   /*!< 0x00000020 */
#define ETH_DMAA4DACR_RDRC_Pos              (8U)
#define ETH_DMAA4DACR_RDRC_Msk              (0xFU << ETH_DMAA4DACR_RDRC_Pos)                    /*!< 0x00000F00 */
#define ETH_DMAA4DACR_RDRC                  ETH_DMAA4DACR_RDRC_Msk                              /*!< Receive DMA Read Descriptor Cache control */
#define ETH_DMAA4DACR_RDRC_0                (0x1U << ETH_DMAA4DACR_RDRC_Pos)                  /*!< 0x00000100 */
#define ETH_DMAA4DACR_RDRC_1                (0x2U << ETH_DMAA4DACR_RDRC_Pos)                  /*!< 0x00000200 */
#define ETH_DMAA4DACR_RDRC_2                (0x4U << ETH_DMAA4DACR_RDRC_Pos)                  /*!< 0x00000400 */
#define ETH_DMAA4DACR_RDRC_3                (0x8U << ETH_DMAA4DACR_RDRC_Pos)                  /*!< 0x00000800 */

/**************  Bit definition for ETH_DMAC0CR register  **************/
#define ETH_DMAC0CR_MSS_Pos                 (0U)
#define ETH_DMAC0CR_MSS_Msk                 (0x3FFFU << ETH_DMAC0CR_MSS_Pos)                    /*!< 0x00003FFF */
#define ETH_DMAC0CR_MSS                     ETH_DMAC0CR_MSS_Msk                                 /*!< Maximum Segment Size */
#define ETH_DMAC0CR_MSS_0                   (0x1U << ETH_DMAC0CR_MSS_Pos)                       /*!< 0x00000001 */
#define ETH_DMAC0CR_MSS_1                   (0x2U << ETH_DMAC0CR_MSS_Pos)                       /*!< 0x00000002 */
#define ETH_DMAC0CR_MSS_2                   (0x4U << ETH_DMAC0CR_MSS_Pos)                       /*!< 0x00000004 */
#define ETH_DMAC0CR_MSS_3                   (0x8U << ETH_DMAC0CR_MSS_Pos)                       /*!< 0x00000008 */
#define ETH_DMAC0CR_MSS_4                   (0x10U << ETH_DMAC0CR_MSS_Pos)                      /*!< 0x00000010 */
#define ETH_DMAC0CR_MSS_5                   (0x20U << ETH_DMAC0CR_MSS_Pos)                      /*!< 0x00000020 */
#define ETH_DMAC0CR_MSS_6                   (0x40U << ETH_DMAC0CR_MSS_Pos)                      /*!< 0x00000040 */
#define ETH_DMAC0CR_MSS_7                   (0x80U << ETH_DMAC0CR_MSS_Pos)                      /*!< 0x00000080 */
#define ETH_DMAC0CR_MSS_8                   (0x100U << ETH_DMAC0CR_MSS_Pos)                     /*!< 0x00000100 */
#define ETH_DMAC0CR_MSS_9                   (0x200U << ETH_DMAC0CR_MSS_Pos)                     /*!< 0x00000200 */
#define ETH_DMAC0CR_MSS_10                  (0x400U << ETH_DMAC0CR_MSS_Pos)                     /*!< 0x00000400 */
#define ETH_DMAC0CR_MSS_11                  (0x800U << ETH_DMAC0CR_MSS_Pos)                     /*!< 0x00000800 */
#define ETH_DMAC0CR_MSS_12                  (0x1000U << ETH_DMAC0CR_MSS_Pos)                    /*!< 0x00001000 */
#define ETH_DMAC0CR_MSS_13                  (0x2000U << ETH_DMAC0CR_MSS_Pos)                    /*!< 0x00002000 */
#define ETH_DMAC0CR_PBLX8_Pos               (16U)
#define ETH_DMAC0CR_PBLX8_Msk               (0x1U << ETH_DMAC0CR_PBLX8_Pos)                     /*!< 0x00010000 */
#define ETH_DMAC0CR_PBLX8                   ETH_DMAC0CR_PBLX8_Msk                               /*!< 8xPBL mode */
#define ETH_DMAC0CR_DSL_Pos                 (18U)
#define ETH_DMAC0CR_DSL_Msk                 (0x7U << ETH_DMAC0CR_DSL_Pos)                       /*!< 0x001C0000 */
#define ETH_DMAC0CR_DSL                     ETH_DMAC0CR_DSL_Msk                                 /*!< Descriptor Skip Length */
#define ETH_DMAC0CR_DSL_0                   (0x1U << ETH_DMAC0CR_DSL_Pos)                   /*!< 0x00040000 */
#define ETH_DMAC0CR_DSL_1                   (0x2U << ETH_DMAC0CR_DSL_Pos)                   /*!< 0x00080000 */
#define ETH_DMAC0CR_DSL_2                   (0x4U << ETH_DMAC0CR_DSL_Pos)                  /*!< 0x00100000 */

/*************  Bit definition for ETH_DMAC0TXCR register  *************/
#define ETH_DMAC0TXCR_ST_Pos                (0U)
#define ETH_DMAC0TXCR_ST_Msk                (0x1U << ETH_DMAC0TXCR_ST_Pos)                      /*!< 0x00000001 */
#define ETH_DMAC0TXCR_ST                    ETH_DMAC0TXCR_ST_Msk                                /*!< Start or Stop Transmission Command */
#define ETH_DMAC0TXCR_TCW_Pos               (1U)
#define ETH_DMAC0TXCR_TCW_Msk               (0x7U << ETH_DMAC0TXCR_TCW_Pos)                     /*!< 0x0000000E */
#define ETH_DMAC0TXCR_TCW                   ETH_DMAC0TXCR_TCW_Msk                               /*!< Transmit Channel Weight */
#define ETH_DMAC0TXCR_TCW_0                 (0x1U << ETH_DMAC0TXCR_TCW_Pos)                     /*!< 0x00000002 */
#define ETH_DMAC0TXCR_TCW_1                 (0x2U << ETH_DMAC0TXCR_TCW_Pos)                     /*!< 0x00000004 */
#define ETH_DMAC0TXCR_TCW_2                 (0x4U << ETH_DMAC0TXCR_TCW_Pos)                     /*!< 0x00000008 */
#define ETH_DMAC0TXCR_OSF_Pos               (4U)
#define ETH_DMAC0TXCR_OSF_Msk               (0x1U << ETH_DMAC0TXCR_OSF_Pos)                     /*!< 0x00000010 */
#define ETH_DMAC0TXCR_OSF                   ETH_DMAC0TXCR_OSF_Msk                               /*!< Operate on Second Packet */
#define ETH_DMAC0TXCR_TSE_Pos               (12U)
#define ETH_DMAC0TXCR_TSE_Msk               (0x1U << ETH_DMAC0TXCR_TSE_Pos)                     /*!< 0x00001000 */
#define ETH_DMAC0TXCR_TSE                   ETH_DMAC0TXCR_TSE_Msk                               /*!< TCP Segmentation Enabled */
#define ETH_DMAC0TXCR_TXPBL_Pos             (16U)
#define ETH_DMAC0TXCR_TXPBL_Msk             (0x3FU << ETH_DMAC0TXCR_TXPBL_Pos)                  /*!< 0x003F0000 */
#define ETH_DMAC0TXCR_TXPBL                 ETH_DMAC0TXCR_TXPBL_Msk                             /*!< Transmit Programmable Burst Length */
#define ETH_DMAC0TXCR_TXPBL_0               (0x1U << ETH_DMAC0TXCR_TXPBL_Pos)               /*!< 0x00010000 */
#define ETH_DMAC0TXCR_TXPBL_1               (0x2U << ETH_DMAC0TXCR_TXPBL_Pos)               /*!< 0x00020000 */
#define ETH_DMAC0TXCR_TXPBL_2               (0x4U << ETH_DMAC0TXCR_TXPBL_Pos)               /*!< 0x00040000 */
#define ETH_DMAC0TXCR_TXPBL_3               (0x8U << ETH_DMAC0TXCR_TXPBL_Pos)               /*!< 0x00080000 */
#define ETH_DMAC0TXCR_TXPBL_4               (0x10U << ETH_DMAC0TXCR_TXPBL_Pos)              /*!< 0x00100000 */
#define ETH_DMAC0TXCR_TXPBL_5               (0x20U << ETH_DMAC0TXCR_TXPBL_Pos)              /*!< 0x00200000 */
#define ETH_DMAC0TXCR_TQOS_Pos              (24U)
#define ETH_DMAC0TXCR_TQOS_Msk              (0xFU << ETH_DMAC0TXCR_TQOS_Pos)                    /*!< 0x0F000000 */
#define ETH_DMAC0TXCR_TQOS                  ETH_DMAC0TXCR_TQOS_Msk                              /*!< Transmit QOS. */
#define ETH_DMAC0TXCR_TQOS_0                (0x1U << ETH_DMAC0TXCR_TQOS_Pos)              /*!< 0x01000000 */
#define ETH_DMAC0TXCR_TQOS_1                (0x2U << ETH_DMAC0TXCR_TQOS_Pos)              /*!< 0x02000000 */
#define ETH_DMAC0TXCR_TQOS_2                (0x4U << ETH_DMAC0TXCR_TQOS_Pos)              /*!< 0x04000000 */
#define ETH_DMAC0TXCR_TQOS_3                (0x8U << ETH_DMAC0TXCR_TQOS_Pos)              /*!< 0x08000000 */

/*************  Bit definition for ETH_DMAC0RXCR register  *************/
#define ETH_DMAC0RXCR_SR_Pos                (0U)
#define ETH_DMAC0RXCR_SR_Msk                (0x1U << ETH_DMAC0RXCR_SR_Pos)                      /*!< 0x00000001 */
#define ETH_DMAC0RXCR_SR                    ETH_DMAC0RXCR_SR_Msk                                /*!< Start or Stop Receive */
#define ETH_DMAC0RXCR_RBSZ_Pos              (1U)
#define ETH_DMAC0RXCR_RBSZ_Msk              (0x3FFFU << ETH_DMAC0RXCR_RBSZ_Pos)                 /*!< 0x00007FFE */
#define ETH_DMAC0RXCR_RBSZ                  ETH_DMAC0RXCR_RBSZ_Msk                              /*!< Receive Buffer size */
#define ETH_DMAC0RXCR_RBSZ_0                (0x1U << ETH_DMAC0RXCR_RBSZ_Pos)                    /*!< 0x00000002 */
#define ETH_DMAC0RXCR_RBSZ_1                (0x2U << ETH_DMAC0RXCR_RBSZ_Pos)                    /*!< 0x00000004 */
#define ETH_DMAC0RXCR_RBSZ_2                (0x4U << ETH_DMAC0RXCR_RBSZ_Pos)                    /*!< 0x00000008 */
#define ETH_DMAC0RXCR_RBSZ_3                (0x8U << ETH_DMAC0RXCR_RBSZ_Pos)                   /*!< 0x00000010 */
#define ETH_DMAC0RXCR_RBSZ_4                (0x10U << ETH_DMAC0RXCR_RBSZ_Pos)                   /*!< 0x00000020 */
#define ETH_DMAC0RXCR_RBSZ_5                (0x20U << ETH_DMAC0RXCR_RBSZ_Pos)                   /*!< 0x00000040 */
#define ETH_DMAC0RXCR_RBSZ_6                (0x40U << ETH_DMAC0RXCR_RBSZ_Pos)                   /*!< 0x00000080 */
#define ETH_DMAC0RXCR_RBSZ_7                (0x80U << ETH_DMAC0RXCR_RBSZ_Pos)                  /*!< 0x00000100 */
#define ETH_DMAC0RXCR_RBSZ_8                (0x100U << ETH_DMAC0RXCR_RBSZ_Pos)                  /*!< 0x00000200 */
#define ETH_DMAC0RXCR_RBSZ_9                (0x200U << ETH_DMAC0RXCR_RBSZ_Pos)                  /*!< 0x00000400 */
#define ETH_DMAC0RXCR_RBSZ_10               (0x400U << ETH_DMAC0RXCR_RBSZ_Pos)                  /*!< 0x00000800 */
#define ETH_DMAC0RXCR_RBSZ_11               (0x800U << ETH_DMAC0RXCR_RBSZ_Pos)                 /*!< 0x00001000 */
#define ETH_DMAC0RXCR_RBSZ_12               (0x1000U << ETH_DMAC0RXCR_RBSZ_Pos)                 /*!< 0x00002000 */
#define ETH_DMAC0RXCR_RBSZ_13               (0x2000U << ETH_DMAC0RXCR_RBSZ_Pos)                 /*!< 0x00004000 */
#define ETH_DMAC0RXCR_RXPBL_Pos             (16U)
#define ETH_DMAC0RXCR_RXPBL_Msk             (0x3FU << ETH_DMAC0RXCR_RXPBL_Pos)                  /*!< 0x003F0000 */
#define ETH_DMAC0RXCR_RXPBL                 ETH_DMAC0RXCR_RXPBL_Msk                             /*!< Receive Programmable Burst Length */
#define ETH_DMAC0RXCR_RXPBL_0               (0x1U << ETH_DMAC0RXCR_RXPBL_Pos)               /*!< 0x00010000 */
#define ETH_DMAC0RXCR_RXPBL_1               (0x2U << ETH_DMAC0RXCR_RXPBL_Pos)               /*!< 0x00020000 */
#define ETH_DMAC0RXCR_RXPBL_2               (0x4U << ETH_DMAC0RXCR_RXPBL_Pos)               /*!< 0x00040000 */
#define ETH_DMAC0RXCR_RXPBL_3               (0x8U << ETH_DMAC0RXCR_RXPBL_Pos)               /*!< 0x00080000 */
#define ETH_DMAC0RXCR_RXPBL_4               (0x10U << ETH_DMAC0RXCR_RXPBL_Pos)              /*!< 0x00100000 */
#define ETH_DMAC0RXCR_RXPBL_5               (0x20U << ETH_DMAC0RXCR_RXPBL_Pos)              /*!< 0x00200000 */
#define ETH_DMAC0RXCR_RQOS_Pos              (24U)
#define ETH_DMAC0RXCR_RQOS_Msk              (0xFU << ETH_DMAC0RXCR_RQOS_Pos)                    /*!< 0x0F000000 */
#define ETH_DMAC0RXCR_RQOS                  ETH_DMAC0RXCR_RQOS_Msk                              /*!< Rx AXI4 QOS. */
#define ETH_DMAC0RXCR_RQOS_0                (0x1U << ETH_DMAC0RXCR_RQOS_Pos)              /*!< 0x01000000 */
#define ETH_DMAC0RXCR_RQOS_1                (0x2U << ETH_DMAC0RXCR_RQOS_Pos)              /*!< 0x02000000 */
#define ETH_DMAC0RXCR_RQOS_2                (0x4U << ETH_DMAC0RXCR_RQOS_Pos)              /*!< 0x04000000 */
#define ETH_DMAC0RXCR_RQOS_3                (0x8U << ETH_DMAC0RXCR_RQOS_Pos)              /*!< 0x08000000 */
#define ETH_DMAC0RXCR_RPF_Pos               (31U)
#define ETH_DMAC0RXCR_RPF_Msk               (0x1U << ETH_DMAC0RXCR_RPF_Pos)                     /*!< 0x80000000 */
#define ETH_DMAC0RXCR_RPF                   ETH_DMAC0RXCR_RPF_Msk                               /*!< DMA Rx Channel0 Packet Flush */

/************  Bit definition for ETH_DMAC0TXDLAR register  ************/
#define ETH_DMAC0TXDLAR_TDESLA_Pos          (3U)
#define ETH_DMAC0TXDLAR_TDESLA_Msk          (0x1FFFFFFFU << ETH_DMAC0TXDLAR_TDESLA_Pos)         /*!< 0xFFFFFFF8 */
#define ETH_DMAC0TXDLAR_TDESLA              ETH_DMAC0TXDLAR_TDESLA_Msk                          /*!< Start of Transmit List */
#define ETH_DMAC0TXDLAR_TDESLA_0            (0x1U << ETH_DMAC0TXDLAR_TDESLA_Pos)                /*!< 0x00000008 */
#define ETH_DMAC0TXDLAR_TDESLA_1            (0x2U << ETH_DMAC0TXDLAR_TDESLA_Pos)               /*!< 0x00000010 */
#define ETH_DMAC0TXDLAR_TDESLA_2            (0x4U << ETH_DMAC0TXDLAR_TDESLA_Pos)               /*!< 0x00000020 */
#define ETH_DMAC0TXDLAR_TDESLA_3            (0x8U << ETH_DMAC0TXDLAR_TDESLA_Pos)               /*!< 0x00000040 */
#define ETH_DMAC0TXDLAR_TDESLA_4            (0x10U << ETH_DMAC0TXDLAR_TDESLA_Pos)               /*!< 0x00000080 */
#define ETH_DMAC0TXDLAR_TDESLA_5            (0x20U << ETH_DMAC0TXDLAR_TDESLA_Pos)              /*!< 0x00000100 */
#define ETH_DMAC0TXDLAR_TDESLA_6            (0x40U << ETH_DMAC0TXDLAR_TDESLA_Pos)              /*!< 0x00000200 */
#define ETH_DMAC0TXDLAR_TDESLA_7            (0x80U << ETH_DMAC0TXDLAR_TDESLA_Pos)              /*!< 0x00000400 */
#define ETH_DMAC0TXDLAR_TDESLA_8            (0x100U << ETH_DMAC0TXDLAR_TDESLA_Pos)              /*!< 0x00000800 */
#define ETH_DMAC0TXDLAR_TDESLA_9            (0x200U << ETH_DMAC0TXDLAR_TDESLA_Pos)             /*!< 0x00001000 */
#define ETH_DMAC0TXDLAR_TDESLA_10           (0x400U << ETH_DMAC0TXDLAR_TDESLA_Pos)             /*!< 0x00002000 */
#define ETH_DMAC0TXDLAR_TDESLA_11           (0x800U << ETH_DMAC0TXDLAR_TDESLA_Pos)             /*!< 0x00004000 */
#define ETH_DMAC0TXDLAR_TDESLA_12           (0x1000U << ETH_DMAC0TXDLAR_TDESLA_Pos)             /*!< 0x00008000 */
#define ETH_DMAC0TXDLAR_TDESLA_13           (0x2000U << ETH_DMAC0TXDLAR_TDESLA_Pos)            /*!< 0x00010000 */
#define ETH_DMAC0TXDLAR_TDESLA_14           (0x4000U << ETH_DMAC0TXDLAR_TDESLA_Pos)            /*!< 0x00020000 */
#define ETH_DMAC0TXDLAR_TDESLA_15           (0x8000U << ETH_DMAC0TXDLAR_TDESLA_Pos)            /*!< 0x00040000 */
#define ETH_DMAC0TXDLAR_TDESLA_16           (0x10000U << ETH_DMAC0TXDLAR_TDESLA_Pos)            /*!< 0x00080000 */
#define ETH_DMAC0TXDLAR_TDESLA_17           (0x20000U << ETH_DMAC0TXDLAR_TDESLA_Pos)           /*!< 0x00100000 */
#define ETH_DMAC0TXDLAR_TDESLA_18           (0x40000U << ETH_DMAC0TXDLAR_TDESLA_Pos)           /*!< 0x00200000 */
#define ETH_DMAC0TXDLAR_TDESLA_19           (0x80000U << ETH_DMAC0TXDLAR_TDESLA_Pos)           /*!< 0x00400000 */
#define ETH_DMAC0TXDLAR_TDESLA_20           (0x100000U << ETH_DMAC0TXDLAR_TDESLA_Pos)           /*!< 0x00800000 */
#define ETH_DMAC0TXDLAR_TDESLA_21           (0x200000U << ETH_DMAC0TXDLAR_TDESLA_Pos)          /*!< 0x01000000 */
#define ETH_DMAC0TXDLAR_TDESLA_22           (0x400000U << ETH_DMAC0TXDLAR_TDESLA_Pos)          /*!< 0x02000000 */
#define ETH_DMAC0TXDLAR_TDESLA_23           (0x800000U << ETH_DMAC0TXDLAR_TDESLA_Pos)          /*!< 0x04000000 */
#define ETH_DMAC0TXDLAR_TDESLA_24           (0x1000000U << ETH_DMAC0TXDLAR_TDESLA_Pos)          /*!< 0x08000000 */
#define ETH_DMAC0TXDLAR_TDESLA_25           (0x2000000U << ETH_DMAC0TXDLAR_TDESLA_Pos)         /*!< 0x10000000 */
#define ETH_DMAC0TXDLAR_TDESLA_26           (0x4000000U << ETH_DMAC0TXDLAR_TDESLA_Pos)         /*!< 0x20000000 */
#define ETH_DMAC0TXDLAR_TDESLA_27           (0x8000000U << ETH_DMAC0TXDLAR_TDESLA_Pos)         /*!< 0x40000000 */
#define ETH_DMAC0TXDLAR_TDESLA_28           (0x10000000U << ETH_DMAC0TXDLAR_TDESLA_Pos)         /*!< 0x80000000 */

/************  Bit definition for ETH_DMAC0RXDLAR register  ************/
#define ETH_DMAC0RXDLAR_RDESLA_Pos          (3U)
#define ETH_DMAC0RXDLAR_RDESLA_Msk          (0x1FFFFFFFU << ETH_DMAC0RXDLAR_RDESLA_Pos)         /*!< 0xFFFFFFF8 */
#define ETH_DMAC0RXDLAR_RDESLA              ETH_DMAC0RXDLAR_RDESLA_Msk                          /*!< Start of Receive List */
#define ETH_DMAC0RXDLAR_RDESLA_0            (0x1U << ETH_DMAC0RXDLAR_RDESLA_Pos)                /*!< 0x00000008 */
#define ETH_DMAC0RXDLAR_RDESLA_1            (0x2U << ETH_DMAC0RXDLAR_RDESLA_Pos)               /*!< 0x00000010 */
#define ETH_DMAC0RXDLAR_RDESLA_2            (0x4U << ETH_DMAC0RXDLAR_RDESLA_Pos)               /*!< 0x00000020 */
#define ETH_DMAC0RXDLAR_RDESLA_3            (0x8U << ETH_DMAC0RXDLAR_RDESLA_Pos)               /*!< 0x00000040 */
#define ETH_DMAC0RXDLAR_RDESLA_4            (0x10U << ETH_DMAC0RXDLAR_RDESLA_Pos)               /*!< 0x00000080 */
#define ETH_DMAC0RXDLAR_RDESLA_5            (0x20U << ETH_DMAC0RXDLAR_RDESLA_Pos)              /*!< 0x00000100 */
#define ETH_DMAC0RXDLAR_RDESLA_6            (0x40U << ETH_DMAC0RXDLAR_RDESLA_Pos)              /*!< 0x00000200 */
#define ETH_DMAC0RXDLAR_RDESLA_7            (0x80U << ETH_DMAC0RXDLAR_RDESLA_Pos)              /*!< 0x00000400 */
#define ETH_DMAC0RXDLAR_RDESLA_8            (0x100U << ETH_DMAC0RXDLAR_RDESLA_Pos)              /*!< 0x00000800 */
#define ETH_DMAC0RXDLAR_RDESLA_9            (0x200U << ETH_DMAC0RXDLAR_RDESLA_Pos)             /*!< 0x00001000 */
#define ETH_DMAC0RXDLAR_RDESLA_10           (0x400U << ETH_DMAC0RXDLAR_RDESLA_Pos)             /*!< 0x00002000 */
#define ETH_DMAC0RXDLAR_RDESLA_11           (0x800U << ETH_DMAC0RXDLAR_RDESLA_Pos)             /*!< 0x00004000 */
#define ETH_DMAC0RXDLAR_RDESLA_12           (0x1000U << ETH_DMAC0RXDLAR_RDESLA_Pos)             /*!< 0x00008000 */
#define ETH_DMAC0RXDLAR_RDESLA_13           (0x2000U << ETH_DMAC0RXDLAR_RDESLA_Pos)            /*!< 0x00010000 */
#define ETH_DMAC0RXDLAR_RDESLA_14           (0x4000U << ETH_DMAC0RXDLAR_RDESLA_Pos)            /*!< 0x00020000 */
#define ETH_DMAC0RXDLAR_RDESLA_15           (0x8000U << ETH_DMAC0RXDLAR_RDESLA_Pos)            /*!< 0x00040000 */
#define ETH_DMAC0RXDLAR_RDESLA_16           (0x10000U << ETH_DMAC0RXDLAR_RDESLA_Pos)            /*!< 0x00080000 */
#define ETH_DMAC0RXDLAR_RDESLA_17           (0x20000U << ETH_DMAC0RXDLAR_RDESLA_Pos)           /*!< 0x00100000 */
#define ETH_DMAC0RXDLAR_RDESLA_18           (0x40000U << ETH_DMAC0RXDLAR_RDESLA_Pos)           /*!< 0x00200000 */
#define ETH_DMAC0RXDLAR_RDESLA_19           (0x80000U << ETH_DMAC0RXDLAR_RDESLA_Pos)           /*!< 0x00400000 */
#define ETH_DMAC0RXDLAR_RDESLA_20           (0x100000U << ETH_DMAC0RXDLAR_RDESLA_Pos)           /*!< 0x00800000 */
#define ETH_DMAC0RXDLAR_RDESLA_21           (0x200000U << ETH_DMAC0RXDLAR_RDESLA_Pos)          /*!< 0x01000000 */
#define ETH_DMAC0RXDLAR_RDESLA_22           (0x400000U << ETH_DMAC0RXDLAR_RDESLA_Pos)          /*!< 0x02000000 */
#define ETH_DMAC0RXDLAR_RDESLA_23           (0x800000U << ETH_DMAC0RXDLAR_RDESLA_Pos)          /*!< 0x04000000 */
#define ETH_DMAC0RXDLAR_RDESLA_24           (0x1000000U << ETH_DMAC0RXDLAR_RDESLA_Pos)          /*!< 0x08000000 */
#define ETH_DMAC0RXDLAR_RDESLA_25           (0x2000000U << ETH_DMAC0RXDLAR_RDESLA_Pos)         /*!< 0x10000000 */
#define ETH_DMAC0RXDLAR_RDESLA_26           (0x4000000U << ETH_DMAC0RXDLAR_RDESLA_Pos)         /*!< 0x20000000 */
#define ETH_DMAC0RXDLAR_RDESLA_27           (0x8000000U << ETH_DMAC0RXDLAR_RDESLA_Pos)         /*!< 0x40000000 */
#define ETH_DMAC0RXDLAR_RDESLA_28           (0x10000000U << ETH_DMAC0RXDLAR_RDESLA_Pos)         /*!< 0x80000000 */

/************  Bit definition for ETH_DMAC0TXDTPR register  ************/
#define ETH_DMAC0TXDTPR_TDT_Pos             (3U)
#define ETH_DMAC0TXDTPR_TDT_Msk             (0x1FFFFFFFU << ETH_DMAC0TXDTPR_TDT_Pos)            /*!< 0xFFFFFFF8 */
#define ETH_DMAC0TXDTPR_TDT                 ETH_DMAC0TXDTPR_TDT_Msk                             /*!< Transmit Descriptor Tail Pointer */
#define ETH_DMAC0TXDTPR_TDT_0               (0x1U << ETH_DMAC0TXDTPR_TDT_Pos)                   /*!< 0x00000008 */
#define ETH_DMAC0TXDTPR_TDT_1               (0x2U << ETH_DMAC0TXDTPR_TDT_Pos)                  /*!< 0x00000010 */
#define ETH_DMAC0TXDTPR_TDT_2               (0x4U << ETH_DMAC0TXDTPR_TDT_Pos)                  /*!< 0x00000020 */
#define ETH_DMAC0TXDTPR_TDT_3               (0x8U << ETH_DMAC0TXDTPR_TDT_Pos)                  /*!< 0x00000040 */
#define ETH_DMAC0TXDTPR_TDT_4               (0x10U << ETH_DMAC0TXDTPR_TDT_Pos)                  /*!< 0x00000080 */
#define ETH_DMAC0TXDTPR_TDT_5               (0x20U << ETH_DMAC0TXDTPR_TDT_Pos)                 /*!< 0x00000100 */
#define ETH_DMAC0TXDTPR_TDT_6               (0x40U << ETH_DMAC0TXDTPR_TDT_Pos)                 /*!< 0x00000200 */
#define ETH_DMAC0TXDTPR_TDT_7               (0x80U << ETH_DMAC0TXDTPR_TDT_Pos)                 /*!< 0x00000400 */
#define ETH_DMAC0TXDTPR_TDT_8               (0x100U << ETH_DMAC0TXDTPR_TDT_Pos)                 /*!< 0x00000800 */
#define ETH_DMAC0TXDTPR_TDT_9               (0x200U << ETH_DMAC0TXDTPR_TDT_Pos)                /*!< 0x00001000 */
#define ETH_DMAC0TXDTPR_TDT_10              (0x400U << ETH_DMAC0TXDTPR_TDT_Pos)                /*!< 0x00002000 */
#define ETH_DMAC0TXDTPR_TDT_11              (0x800U << ETH_DMAC0TXDTPR_TDT_Pos)                /*!< 0x00004000 */
#define ETH_DMAC0TXDTPR_TDT_12              (0x1000U << ETH_DMAC0TXDTPR_TDT_Pos)                /*!< 0x00008000 */
#define ETH_DMAC0TXDTPR_TDT_13              (0x2000U << ETH_DMAC0TXDTPR_TDT_Pos)               /*!< 0x00010000 */
#define ETH_DMAC0TXDTPR_TDT_14              (0x4000U << ETH_DMAC0TXDTPR_TDT_Pos)               /*!< 0x00020000 */
#define ETH_DMAC0TXDTPR_TDT_15              (0x8000U << ETH_DMAC0TXDTPR_TDT_Pos)               /*!< 0x00040000 */
#define ETH_DMAC0TXDTPR_TDT_16              (0x10000U << ETH_DMAC0TXDTPR_TDT_Pos)               /*!< 0x00080000 */
#define ETH_DMAC0TXDTPR_TDT_17              (0x20000U << ETH_DMAC0TXDTPR_TDT_Pos)              /*!< 0x00100000 */
#define ETH_DMAC0TXDTPR_TDT_18              (0x40000U << ETH_DMAC0TXDTPR_TDT_Pos)              /*!< 0x00200000 */
#define ETH_DMAC0TXDTPR_TDT_19              (0x80000U << ETH_DMAC0TXDTPR_TDT_Pos)              /*!< 0x00400000 */
#define ETH_DMAC0TXDTPR_TDT_20              (0x100000U << ETH_DMAC0TXDTPR_TDT_Pos)              /*!< 0x00800000 */
#define ETH_DMAC0TXDTPR_TDT_21              (0x200000U << ETH_DMAC0TXDTPR_TDT_Pos)             /*!< 0x01000000 */
#define ETH_DMAC0TXDTPR_TDT_22              (0x400000U << ETH_DMAC0TXDTPR_TDT_Pos)             /*!< 0x02000000 */
#define ETH_DMAC0TXDTPR_TDT_23              (0x800000U << ETH_DMAC0TXDTPR_TDT_Pos)             /*!< 0x04000000 */
#define ETH_DMAC0TXDTPR_TDT_24              (0x1000000U << ETH_DMAC0TXDTPR_TDT_Pos)             /*!< 0x08000000 */
#define ETH_DMAC0TXDTPR_TDT_25              (0x2000000U << ETH_DMAC0TXDTPR_TDT_Pos)            /*!< 0x10000000 */
#define ETH_DMAC0TXDTPR_TDT_26              (0x4000000U << ETH_DMAC0TXDTPR_TDT_Pos)            /*!< 0x20000000 */
#define ETH_DMAC0TXDTPR_TDT_27              (0x8000000U << ETH_DMAC0TXDTPR_TDT_Pos)            /*!< 0x40000000 */
#define ETH_DMAC0TXDTPR_TDT_28              (0x10000000U << ETH_DMAC0TXDTPR_TDT_Pos)            /*!< 0x80000000 */

/************  Bit definition for ETH_DMAC0RXDTPR register  ************/
#define ETH_DMAC0RXDTPR_RDT_Pos             (3U)
#define ETH_DMAC0RXDTPR_RDT_Msk             (0x1FFFFFFFU << ETH_DMAC0RXDTPR_RDT_Pos)            /*!< 0xFFFFFFF8 */
#define ETH_DMAC0RXDTPR_RDT                 ETH_DMAC0RXDTPR_RDT_Msk                             /*!< Receive Descriptor Tail Pointer */
#define ETH_DMAC0RXDTPR_RDT_0               (0x1U << ETH_DMAC0RXDTPR_RDT_Pos)                   /*!< 0x00000008 */
#define ETH_DMAC0RXDTPR_RDT_1               (0x2U << ETH_DMAC0RXDTPR_RDT_Pos)                  /*!< 0x00000010 */
#define ETH_DMAC0RXDTPR_RDT_2               (0x4U << ETH_DMAC0RXDTPR_RDT_Pos)                  /*!< 0x00000020 */
#define ETH_DMAC0RXDTPR_RDT_3               (0x8U << ETH_DMAC0RXDTPR_RDT_Pos)                  /*!< 0x00000040 */
#define ETH_DMAC0RXDTPR_RDT_4               (0x10U << ETH_DMAC0RXDTPR_RDT_Pos)                  /*!< 0x00000080 */
#define ETH_DMAC0RXDTPR_RDT_5               (0x20U << ETH_DMAC0RXDTPR_RDT_Pos)                 /*!< 0x00000100 */
#define ETH_DMAC0RXDTPR_RDT_6               (0x40U << ETH_DMAC0RXDTPR_RDT_Pos)                 /*!< 0x00000200 */
#define ETH_DMAC0RXDTPR_RDT_7               (0x80U << ETH_DMAC0RXDTPR_RDT_Pos)                 /*!< 0x00000400 */
#define ETH_DMAC0RXDTPR_RDT_8               (0x100U << ETH_DMAC0RXDTPR_RDT_Pos)                 /*!< 0x00000800 */
#define ETH_DMAC0RXDTPR_RDT_9               (0x200U << ETH_DMAC0RXDTPR_RDT_Pos)                /*!< 0x00001000 */
#define ETH_DMAC0RXDTPR_RDT_10              (0x400U << ETH_DMAC0RXDTPR_RDT_Pos)                /*!< 0x00002000 */
#define ETH_DMAC0RXDTPR_RDT_11              (0x800U << ETH_DMAC0RXDTPR_RDT_Pos)                /*!< 0x00004000 */
#define ETH_DMAC0RXDTPR_RDT_12              (0x1000U << ETH_DMAC0RXDTPR_RDT_Pos)                /*!< 0x00008000 */
#define ETH_DMAC0RXDTPR_RDT_13              (0x2000U << ETH_DMAC0RXDTPR_RDT_Pos)               /*!< 0x00010000 */
#define ETH_DMAC0RXDTPR_RDT_14              (0x4000U << ETH_DMAC0RXDTPR_RDT_Pos)               /*!< 0x00020000 */
#define ETH_DMAC0RXDTPR_RDT_15              (0x8000U << ETH_DMAC0RXDTPR_RDT_Pos)               /*!< 0x00040000 */
#define ETH_DMAC0RXDTPR_RDT_16              (0x10000U << ETH_DMAC0RXDTPR_RDT_Pos)               /*!< 0x00080000 */
#define ETH_DMAC0RXDTPR_RDT_17              (0x20000U << ETH_DMAC0RXDTPR_RDT_Pos)              /*!< 0x00100000 */
#define ETH_DMAC0RXDTPR_RDT_18              (0x40000U << ETH_DMAC0RXDTPR_RDT_Pos)              /*!< 0x00200000 */
#define ETH_DMAC0RXDTPR_RDT_19              (0x80000U << ETH_DMAC0RXDTPR_RDT_Pos)              /*!< 0x00400000 */
#define ETH_DMAC0RXDTPR_RDT_20              (0x100000U << ETH_DMAC0RXDTPR_RDT_Pos)              /*!< 0x00800000 */
#define ETH_DMAC0RXDTPR_RDT_21              (0x200000U << ETH_DMAC0RXDTPR_RDT_Pos)             /*!< 0x01000000 */
#define ETH_DMAC0RXDTPR_RDT_22              (0x400000U << ETH_DMAC0RXDTPR_RDT_Pos)             /*!< 0x02000000 */
#define ETH_DMAC0RXDTPR_RDT_23              (0x800000U << ETH_DMAC0RXDTPR_RDT_Pos)             /*!< 0x04000000 */
#define ETH_DMAC0RXDTPR_RDT_24              (0x1000000U << ETH_DMAC0RXDTPR_RDT_Pos)             /*!< 0x08000000 */
#define ETH_DMAC0RXDTPR_RDT_25              (0x2000000U << ETH_DMAC0RXDTPR_RDT_Pos)            /*!< 0x10000000 */
#define ETH_DMAC0RXDTPR_RDT_26              (0x4000000U << ETH_DMAC0RXDTPR_RDT_Pos)            /*!< 0x20000000 */
#define ETH_DMAC0RXDTPR_RDT_27              (0x8000000U << ETH_DMAC0RXDTPR_RDT_Pos)            /*!< 0x40000000 */
#define ETH_DMAC0RXDTPR_RDT_28              (0x10000000U << ETH_DMAC0RXDTPR_RDT_Pos)            /*!< 0x80000000 */

/************  Bit definition for ETH_DMAC0TXRLR register  *************/
#define ETH_DMAC0TXRLR_TDRL_Pos             (0U)
#define ETH_DMAC0TXRLR_TDRL_Msk             (0x3FFU << ETH_DMAC0TXRLR_TDRL_Pos)                 /*!< 0x000003FF */
#define ETH_DMAC0TXRLR_TDRL                 ETH_DMAC0TXRLR_TDRL_Msk                             /*!< Transmit Descriptor Ring Length */
#define ETH_DMAC0TXRLR_TDRL_0               (0x1U << ETH_DMAC0TXRLR_TDRL_Pos)                   /*!< 0x00000001 */
#define ETH_DMAC0TXRLR_TDRL_1               (0x2U << ETH_DMAC0TXRLR_TDRL_Pos)                   /*!< 0x00000002 */
#define ETH_DMAC0TXRLR_TDRL_2               (0x4U << ETH_DMAC0TXRLR_TDRL_Pos)                   /*!< 0x00000004 */
#define ETH_DMAC0TXRLR_TDRL_3               (0x8U << ETH_DMAC0TXRLR_TDRL_Pos)                   /*!< 0x00000008 */
#define ETH_DMAC0TXRLR_TDRL_4               (0x10U << ETH_DMAC0TXRLR_TDRL_Pos)                  /*!< 0x00000010 */
#define ETH_DMAC0TXRLR_TDRL_5               (0x20U << ETH_DMAC0TXRLR_TDRL_Pos)                  /*!< 0x00000020 */
#define ETH_DMAC0TXRLR_TDRL_6               (0x40U << ETH_DMAC0TXRLR_TDRL_Pos)                  /*!< 0x00000040 */
#define ETH_DMAC0TXRLR_TDRL_7               (0x80U << ETH_DMAC0TXRLR_TDRL_Pos)                  /*!< 0x00000080 */
#define ETH_DMAC0TXRLR_TDRL_8               (0x100U << ETH_DMAC0TXRLR_TDRL_Pos)                 /*!< 0x00000100 */
#define ETH_DMAC0TXRLR_TDRL_9               (0x200U << ETH_DMAC0TXRLR_TDRL_Pos)                 /*!< 0x00000200 */

/************  Bit definition for ETH_DMAC0RXRLR register  *************/
#define ETH_DMAC0RXRLR_RDRL_Pos             (0U)
#define ETH_DMAC0RXRLR_RDRL_Msk             (0x3FFU << ETH_DMAC0RXRLR_RDRL_Pos)                 /*!< 0x000003FF */
#define ETH_DMAC0RXRLR_RDRL                 ETH_DMAC0RXRLR_RDRL_Msk                             /*!< Receive Descriptor Ring Length */
#define ETH_DMAC0RXRLR_RDRL_0               (0x1U << ETH_DMAC0RXRLR_RDRL_Pos)                   /*!< 0x00000001 */
#define ETH_DMAC0RXRLR_RDRL_1               (0x2U << ETH_DMAC0RXRLR_RDRL_Pos)                   /*!< 0x00000002 */
#define ETH_DMAC0RXRLR_RDRL_2               (0x4U << ETH_DMAC0RXRLR_RDRL_Pos)                   /*!< 0x00000004 */
#define ETH_DMAC0RXRLR_RDRL_3               (0x8U << ETH_DMAC0RXRLR_RDRL_Pos)                   /*!< 0x00000008 */
#define ETH_DMAC0RXRLR_RDRL_4               (0x10U << ETH_DMAC0RXRLR_RDRL_Pos)                  /*!< 0x00000010 */
#define ETH_DMAC0RXRLR_RDRL_5               (0x20U << ETH_DMAC0RXRLR_RDRL_Pos)                  /*!< 0x00000020 */
#define ETH_DMAC0RXRLR_RDRL_6               (0x40U << ETH_DMAC0RXRLR_RDRL_Pos)                  /*!< 0x00000040 */
#define ETH_DMAC0RXRLR_RDRL_7               (0x80U << ETH_DMAC0RXRLR_RDRL_Pos)                  /*!< 0x00000080 */
#define ETH_DMAC0RXRLR_RDRL_8               (0x100U << ETH_DMAC0RXRLR_RDRL_Pos)                 /*!< 0x00000100 */
#define ETH_DMAC0RXRLR_RDRL_9               (0x200U << ETH_DMAC0RXRLR_RDRL_Pos)                 /*!< 0x00000200 */

/*************  Bit definition for ETH_DMAC0IER register  **************/
#define ETH_DMAC0IER_TIE_Pos                (0U)
#define ETH_DMAC0IER_TIE_Msk                (0x1U << ETH_DMAC0IER_TIE_Pos)                      /*!< 0x00000001 */
#define ETH_DMAC0IER_TIE                    ETH_DMAC0IER_TIE_Msk                                /*!< Transmit Interrupt Enable */
#define ETH_DMAC0IER_TXSE_Pos               (1U)
#define ETH_DMAC0IER_TXSE_Msk               (0x1U << ETH_DMAC0IER_TXSE_Pos)                     /*!< 0x00000002 */
#define ETH_DMAC0IER_TXSE                   ETH_DMAC0IER_TXSE_Msk                               /*!< Transmit Stopped Enable */
#define ETH_DMAC0IER_TBUE_Pos               (2U)
#define ETH_DMAC0IER_TBUE_Msk               (0x1U << ETH_DMAC0IER_TBUE_Pos)                     /*!< 0x00000004 */
#define ETH_DMAC0IER_TBUE                   ETH_DMAC0IER_TBUE_Msk                               /*!< Transmit Buffer Unavailable Enable */
#define ETH_DMAC0IER_RIE_Pos                (6U)
#define ETH_DMAC0IER_RIE_Msk                (0x1U << ETH_DMAC0IER_RIE_Pos)                      /*!< 0x00000040 */
#define ETH_DMAC0IER_RIE                    ETH_DMAC0IER_RIE_Msk                                /*!< Receive Interrupt Enable */
#define ETH_DMAC0IER_RBUE_Pos               (7U)
#define ETH_DMAC0IER_RBUE_Msk               (0x1U << ETH_DMAC0IER_RBUE_Pos)                     /*!< 0x00000080 */
#define ETH_DMAC0IER_RBUE                   ETH_DMAC0IER_RBUE_Msk                               /*!< Receive Buffer Unavailable Enable */
#define ETH_DMAC0IER_RSE_Pos                (8U)
#define ETH_DMAC0IER_RSE_Msk                (0x1U << ETH_DMAC0IER_RSE_Pos)                      /*!< 0x00000100 */
#define ETH_DMAC0IER_RSE                    ETH_DMAC0IER_RSE_Msk                                /*!< Receive Stopped Enable */
#define ETH_DMAC0IER_RWTE_Pos               (9U)
#define ETH_DMAC0IER_RWTE_Msk               (0x1U << ETH_DMAC0IER_RWTE_Pos)                     /*!< 0x00000200 */
#define ETH_DMAC0IER_RWTE                   ETH_DMAC0IER_RWTE_Msk                               /*!< Receive Watchdog Timeout Enable */
#define ETH_DMAC0IER_ETIE_Pos               (10U)
#define ETH_DMAC0IER_ETIE_Msk               (0x1U << ETH_DMAC0IER_ETIE_Pos)                     /*!< 0x00000400 */
#define ETH_DMAC0IER_ETIE                   ETH_DMAC0IER_ETIE_Msk                               /*!< Early Transmit Interrupt Enable */
#define ETH_DMAC0IER_ERIE_Pos               (11U)
#define ETH_DMAC0IER_ERIE_Msk               (0x1U << ETH_DMAC0IER_ERIE_Pos)                     /*!< 0x00000800 */
#define ETH_DMAC0IER_ERIE                   ETH_DMAC0IER_ERIE_Msk                               /*!< Early Receive Interrupt Enable */
#define ETH_DMAC0IER_FBEE_Pos               (12U)
#define ETH_DMAC0IER_FBEE_Msk               (0x1U << ETH_DMAC0IER_FBEE_Pos)                     /*!< 0x00001000 */
#define ETH_DMAC0IER_FBEE                   ETH_DMAC0IER_FBEE_Msk                               /*!< Fatal Bus Error Enable */
#define ETH_DMAC0IER_CDEE_Pos               (13U)
#define ETH_DMAC0IER_CDEE_Msk               (0x1U << ETH_DMAC0IER_CDEE_Pos)                     /*!< 0x00002000 */
#define ETH_DMAC0IER_CDEE                   ETH_DMAC0IER_CDEE_Msk                               /*!< Context Descriptor Error Enable */
#define ETH_DMAC0IER_AIE_Pos                (14U)
#define ETH_DMAC0IER_AIE_Msk                (0x1U << ETH_DMAC0IER_AIE_Pos)                      /*!< 0x00004000 */
#define ETH_DMAC0IER_AIE                    ETH_DMAC0IER_AIE_Msk                                /*!< Abnormal Interrupt Summary Enable */
#define ETH_DMAC0IER_NIE_Pos                (15U)
#define ETH_DMAC0IER_NIE_Msk                (0x1U << ETH_DMAC0IER_NIE_Pos)                      /*!< 0x00008000 */
#define ETH_DMAC0IER_NIE                    ETH_DMAC0IER_NIE_Msk                                /*!< Normal Interrupt Summary Enable */

/************  Bit definition for ETH_DMAC0RXIWTR register  ************/
#define ETH_DMAC0RXIWTR_RWT_Pos             (0U)
#define ETH_DMAC0RXIWTR_RWT_Msk             (0xFFU << ETH_DMAC0RXIWTR_RWT_Pos)                  /*!< 0x000000FF */
#define ETH_DMAC0RXIWTR_RWT                 ETH_DMAC0RXIWTR_RWT_Msk                             /*!< Receive Interrupt Watchdog Timer Count */
#define ETH_DMAC0RXIWTR_RWT_0               (0x1U << ETH_DMAC0RXIWTR_RWT_Pos)                   /*!< 0x00000001 */
#define ETH_DMAC0RXIWTR_RWT_1               (0x2U << ETH_DMAC0RXIWTR_RWT_Pos)                   /*!< 0x00000002 */
#define ETH_DMAC0RXIWTR_RWT_2               (0x4U << ETH_DMAC0RXIWTR_RWT_Pos)                   /*!< 0x00000004 */
#define ETH_DMAC0RXIWTR_RWT_3               (0x8U << ETH_DMAC0RXIWTR_RWT_Pos)                   /*!< 0x00000008 */
#define ETH_DMAC0RXIWTR_RWT_4               (0x10U << ETH_DMAC0RXIWTR_RWT_Pos)                  /*!< 0x00000010 */
#define ETH_DMAC0RXIWTR_RWT_5               (0x20U << ETH_DMAC0RXIWTR_RWT_Pos)                  /*!< 0x00000020 */
#define ETH_DMAC0RXIWTR_RWT_6               (0x40U << ETH_DMAC0RXIWTR_RWT_Pos)                  /*!< 0x00000040 */
#define ETH_DMAC0RXIWTR_RWT_7               (0x80U << ETH_DMAC0RXIWTR_RWT_Pos)                  /*!< 0x00000080 */

/************  Bit definition for ETH_DMAC0SFCSR register  *************/
#define ETH_DMAC0SFCSR_ESC_Pos              (0U)
#define ETH_DMAC0SFCSR_ESC_Msk              (0x1U << ETH_DMAC0SFCSR_ESC_Pos)                    /*!< 0x00000001 */
#define ETH_DMAC0SFCSR_ESC                  ETH_DMAC0SFCSR_ESC_Msk                              /*!< Enable Slot Comparison */
#define ETH_DMAC0SFCSR_ASC_Pos              (1U)
#define ETH_DMAC0SFCSR_ASC_Msk              (0x1U << ETH_DMAC0SFCSR_ASC_Pos)                    /*!< 0x00000002 */
#define ETH_DMAC0SFCSR_ASC                  ETH_DMAC0SFCSR_ASC_Msk                              /*!< Advance Slot Check */
#define ETH_DMAC0SFCSR_RSN_Pos              (16U)
#define ETH_DMAC0SFCSR_RSN_Msk              (0xFU << ETH_DMAC0SFCSR_RSN_Pos)                    /*!< 0x000F0000 */
#define ETH_DMAC0SFCSR_RSN                  ETH_DMAC0SFCSR_RSN_Msk                              /*!< Reference Slot Number */
#define ETH_DMAC0SFCSR_RSN_0                (0x1U << ETH_DMAC0SFCSR_RSN_Pos)                /*!< 0x00010000 */
#define ETH_DMAC0SFCSR_RSN_1                (0x2U << ETH_DMAC0SFCSR_RSN_Pos)                /*!< 0x00020000 */
#define ETH_DMAC0SFCSR_RSN_2                (0x4U << ETH_DMAC0SFCSR_RSN_Pos)                /*!< 0x00040000 */
#define ETH_DMAC0SFCSR_RSN_3                (0x8U << ETH_DMAC0SFCSR_RSN_Pos)                /*!< 0x00080000 */

/************  Bit definition for ETH_DMAC0CATXDR register  ************/
#define ETH_DMAC0CATXDR_CURTDESAPTR_Pos     (0U)
#define ETH_DMAC0CATXDR_CURTDESAPTR_Msk     (0xFFFFFFFFU << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)    /*!< 0xFFFFFFFF */
#define ETH_DMAC0CATXDR_CURTDESAPTR         ETH_DMAC0CATXDR_CURTDESAPTR_Msk                     /*!< Application Transmit Descriptor Address Pointer */
#define ETH_DMAC0CATXDR_CURTDESAPTR_0       (0x1U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)           /*!< 0x00000001 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_1       (0x2U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)           /*!< 0x00000002 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_2       (0x4U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)           /*!< 0x00000004 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_3       (0x8U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)           /*!< 0x00000008 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_4       (0x10U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)          /*!< 0x00000010 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_5       (0x20U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)          /*!< 0x00000020 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_6       (0x40U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)          /*!< 0x00000040 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_7       (0x80U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)          /*!< 0x00000080 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_8       (0x100U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)         /*!< 0x00000100 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_9       (0x200U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)         /*!< 0x00000200 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_10      (0x400U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)         /*!< 0x00000400 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_11      (0x800U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)         /*!< 0x00000800 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_12      (0x1000U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)        /*!< 0x00001000 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_13      (0x2000U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)        /*!< 0x00002000 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_14      (0x4000U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)        /*!< 0x00004000 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_15      (0x8000U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)        /*!< 0x00008000 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_16      (0x10000U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)       /*!< 0x00010000 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_17      (0x20000U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)       /*!< 0x00020000 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_18      (0x40000U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)       /*!< 0x00040000 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_19      (0x80000U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)       /*!< 0x00080000 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_20      (0x100000U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)      /*!< 0x00100000 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_21      (0x200000U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)      /*!< 0x00200000 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_22      (0x400000U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)      /*!< 0x00400000 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_23      (0x800000U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)      /*!< 0x00800000 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_24      (0x1000000U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)     /*!< 0x01000000 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_25      (0x2000000U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)     /*!< 0x02000000 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_26      (0x4000000U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)     /*!< 0x04000000 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_27      (0x8000000U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)     /*!< 0x08000000 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_28      (0x10000000U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)    /*!< 0x10000000 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_29      (0x20000000U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)    /*!< 0x20000000 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_30      (0x40000000U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)    /*!< 0x40000000 */
#define ETH_DMAC0CATXDR_CURTDESAPTR_31      (0x80000000U << ETH_DMAC0CATXDR_CURTDESAPTR_Pos)    /*!< 0x80000000 */

/************  Bit definition for ETH_DMAC0CARXDR register  ************/
#define ETH_DMAC0CARXDR_CURRDESAPTR_Pos     (0U)
#define ETH_DMAC0CARXDR_CURRDESAPTR_Msk     (0xFFFFFFFFU << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)    /*!< 0xFFFFFFFF */
#define ETH_DMAC0CARXDR_CURRDESAPTR         ETH_DMAC0CARXDR_CURRDESAPTR_Msk                     /*!< Application Receive Descriptor Address Pointer */
#define ETH_DMAC0CARXDR_CURRDESAPTR_0       (0x1U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)           /*!< 0x00000001 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_1       (0x2U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)           /*!< 0x00000002 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_2       (0x4U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)           /*!< 0x00000004 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_3       (0x8U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)           /*!< 0x00000008 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_4       (0x10U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)          /*!< 0x00000010 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_5       (0x20U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)          /*!< 0x00000020 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_6       (0x40U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)          /*!< 0x00000040 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_7       (0x80U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)          /*!< 0x00000080 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_8       (0x100U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)         /*!< 0x00000100 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_9       (0x200U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)         /*!< 0x00000200 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_10      (0x400U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)         /*!< 0x00000400 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_11      (0x800U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)         /*!< 0x00000800 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_12      (0x1000U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)        /*!< 0x00001000 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_13      (0x2000U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)        /*!< 0x00002000 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_14      (0x4000U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)        /*!< 0x00004000 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_15      (0x8000U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)        /*!< 0x00008000 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_16      (0x10000U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)       /*!< 0x00010000 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_17      (0x20000U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)       /*!< 0x00020000 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_18      (0x40000U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)       /*!< 0x00040000 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_19      (0x80000U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)       /*!< 0x00080000 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_20      (0x100000U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)      /*!< 0x00100000 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_21      (0x200000U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)      /*!< 0x00200000 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_22      (0x400000U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)      /*!< 0x00400000 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_23      (0x800000U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)      /*!< 0x00800000 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_24      (0x1000000U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)     /*!< 0x01000000 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_25      (0x2000000U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)     /*!< 0x02000000 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_26      (0x4000000U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)     /*!< 0x04000000 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_27      (0x8000000U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)     /*!< 0x08000000 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_28      (0x10000000U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)    /*!< 0x10000000 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_29      (0x20000000U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)    /*!< 0x20000000 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_30      (0x40000000U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)    /*!< 0x40000000 */
#define ETH_DMAC0CARXDR_CURRDESAPTR_31      (0x80000000U << ETH_DMAC0CARXDR_CURRDESAPTR_Pos)    /*!< 0x80000000 */

/************  Bit definition for ETH_DMAC0CATXBR register  ************/
#define ETH_DMAC0CATXBR_CURTBUFAPTR_Pos     (0U)
#define ETH_DMAC0CATXBR_CURTBUFAPTR_Msk     (0xFFFFFFFFU << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)    /*!< 0xFFFFFFFF */
#define ETH_DMAC0CATXBR_CURTBUFAPTR         ETH_DMAC0CATXBR_CURTBUFAPTR_Msk                     /*!< Application Transmit Buffer Address Pointer */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_0       (0x1U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)           /*!< 0x00000001 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_1       (0x2U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)           /*!< 0x00000002 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_2       (0x4U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)           /*!< 0x00000004 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_3       (0x8U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)           /*!< 0x00000008 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_4       (0x10U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)          /*!< 0x00000010 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_5       (0x20U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)          /*!< 0x00000020 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_6       (0x40U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)          /*!< 0x00000040 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_7       (0x80U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)          /*!< 0x00000080 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_8       (0x100U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)         /*!< 0x00000100 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_9       (0x200U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)         /*!< 0x00000200 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_10      (0x400U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)         /*!< 0x00000400 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_11      (0x800U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)         /*!< 0x00000800 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_12      (0x1000U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)        /*!< 0x00001000 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_13      (0x2000U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)        /*!< 0x00002000 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_14      (0x4000U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)        /*!< 0x00004000 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_15      (0x8000U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)        /*!< 0x00008000 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_16      (0x10000U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)       /*!< 0x00010000 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_17      (0x20000U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)       /*!< 0x00020000 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_18      (0x40000U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)       /*!< 0x00040000 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_19      (0x80000U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)       /*!< 0x00080000 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_20      (0x100000U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)      /*!< 0x00100000 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_21      (0x200000U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)      /*!< 0x00200000 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_22      (0x400000U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)      /*!< 0x00400000 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_23      (0x800000U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)      /*!< 0x00800000 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_24      (0x1000000U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)     /*!< 0x01000000 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_25      (0x2000000U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)     /*!< 0x02000000 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_26      (0x4000000U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)     /*!< 0x04000000 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_27      (0x8000000U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)     /*!< 0x08000000 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_28      (0x10000000U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)    /*!< 0x10000000 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_29      (0x20000000U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)    /*!< 0x20000000 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_30      (0x40000000U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)    /*!< 0x40000000 */
#define ETH_DMAC0CATXBR_CURTBUFAPTR_31      (0x80000000U << ETH_DMAC0CATXBR_CURTBUFAPTR_Pos)    /*!< 0x80000000 */

/************  Bit definition for ETH_DMAC0CARXBR register  ************/
#define ETH_DMAC0CARXBR_CURRBUFAPTR_Pos     (0U)
#define ETH_DMAC0CARXBR_CURRBUFAPTR_Msk     (0xFFFFFFFFU << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)    /*!< 0xFFFFFFFF */
#define ETH_DMAC0CARXBR_CURRBUFAPTR         ETH_DMAC0CARXBR_CURRBUFAPTR_Msk                     /*!< Application Receive Buffer Address Pointer */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_0       (0x1U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)           /*!< 0x00000001 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_1       (0x2U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)           /*!< 0x00000002 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_2       (0x4U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)           /*!< 0x00000004 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_3       (0x8U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)           /*!< 0x00000008 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_4       (0x10U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)          /*!< 0x00000010 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_5       (0x20U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)          /*!< 0x00000020 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_6       (0x40U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)          /*!< 0x00000040 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_7       (0x80U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)          /*!< 0x00000080 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_8       (0x100U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)         /*!< 0x00000100 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_9       (0x200U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)         /*!< 0x00000200 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_10      (0x400U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)         /*!< 0x00000400 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_11      (0x800U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)         /*!< 0x00000800 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_12      (0x1000U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)        /*!< 0x00001000 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_13      (0x2000U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)        /*!< 0x00002000 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_14      (0x4000U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)        /*!< 0x00004000 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_15      (0x8000U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)        /*!< 0x00008000 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_16      (0x10000U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)       /*!< 0x00010000 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_17      (0x20000U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)       /*!< 0x00020000 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_18      (0x40000U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)       /*!< 0x00040000 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_19      (0x80000U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)       /*!< 0x00080000 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_20      (0x100000U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)      /*!< 0x00100000 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_21      (0x200000U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)      /*!< 0x00200000 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_22      (0x400000U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)      /*!< 0x00400000 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_23      (0x800000U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)      /*!< 0x00800000 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_24      (0x1000000U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)     /*!< 0x01000000 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_25      (0x2000000U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)     /*!< 0x02000000 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_26      (0x4000000U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)     /*!< 0x04000000 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_27      (0x8000000U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)     /*!< 0x08000000 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_28      (0x10000000U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)    /*!< 0x10000000 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_29      (0x20000000U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)    /*!< 0x20000000 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_30      (0x40000000U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)    /*!< 0x40000000 */
#define ETH_DMAC0CARXBR_CURRBUFAPTR_31      (0x80000000U << ETH_DMAC0CARXBR_CURRBUFAPTR_Pos)    /*!< 0x80000000 */

/**************  Bit definition for ETH_DMAC0SR register  **************/
#define ETH_DMAC0SR_TI_Pos                  (0U)
#define ETH_DMAC0SR_TI_Msk                  (0x1U << ETH_DMAC0SR_TI_Pos)                        /*!< 0x00000001 */
#define ETH_DMAC0SR_TI                      ETH_DMAC0SR_TI_Msk                                  /*!< Transmit Interrupt */
#define ETH_DMAC0SR_TPS_Pos                 (1U)
#define ETH_DMAC0SR_TPS_Msk                 (0x1U << ETH_DMAC0SR_TPS_Pos)                       /*!< 0x00000002 */
#define ETH_DMAC0SR_TPS                     ETH_DMAC0SR_TPS_Msk                                 /*!< Transmit Process Stopped */
#define ETH_DMAC0SR_TBU_Pos                 (2U)
#define ETH_DMAC0SR_TBU_Msk                 (0x1U << ETH_DMAC0SR_TBU_Pos)                       /*!< 0x00000004 */
#define ETH_DMAC0SR_TBU                     ETH_DMAC0SR_TBU_Msk                                 /*!< Transmit Buffer Unavailable */
#define ETH_DMAC0SR_RI_Pos                  (6U)
#define ETH_DMAC0SR_RI_Msk                  (0x1U << ETH_DMAC0SR_RI_Pos)                        /*!< 0x00000040 */
#define ETH_DMAC0SR_RI                      ETH_DMAC0SR_RI_Msk                                  /*!< Receive Interrupt */
#define ETH_DMAC0SR_RBU_Pos                 (7U)
#define ETH_DMAC0SR_RBU_Msk                 (0x1U << ETH_DMAC0SR_RBU_Pos)                       /*!< 0x00000080 */
#define ETH_DMAC0SR_RBU                     ETH_DMAC0SR_RBU_Msk                                 /*!< Receive Buffer Unavailable */
#define ETH_DMAC0SR_RPS_Pos                 (8U)
#define ETH_DMAC0SR_RPS_Msk                 (0x1U << ETH_DMAC0SR_RPS_Pos)                       /*!< 0x00000100 */
#define ETH_DMAC0SR_RPS                     ETH_DMAC0SR_RPS_Msk                                 /*!< Receive Process Stopped */
#define ETH_DMAC0SR_RWT_Pos                 (9U)
#define ETH_DMAC0SR_RWT_Msk                 (0x1U << ETH_DMAC0SR_RWT_Pos)                       /*!< 0x00000200 */
#define ETH_DMAC0SR_RWT                     ETH_DMAC0SR_RWT_Msk                                 /*!< Receive Watchdog Timeout */
#define ETH_DMAC0SR_ETI_Pos                 (10U)
#define ETH_DMAC0SR_ETI_Msk                 (0x1U << ETH_DMAC0SR_ETI_Pos)                       /*!< 0x00000400 */
#define ETH_DMAC0SR_ETI                     ETH_DMAC0SR_ETI_Msk                                 /*!< Early Transmit Interrupt */
#define ETH_DMAC0SR_ERI_Pos                 (11U)
#define ETH_DMAC0SR_ERI_Msk                 (0x1U << ETH_DMAC0SR_ERI_Pos)                       /*!< 0x00000800 */
#define ETH_DMAC0SR_ERI                     ETH_DMAC0SR_ERI_Msk                                 /*!< Early Receive Interrupt */
#define ETH_DMAC0SR_FBE_Pos                 (12U)
#define ETH_DMAC0SR_FBE_Msk                 (0x1U << ETH_DMAC0SR_FBE_Pos)                       /*!< 0x00001000 */
#define ETH_DMAC0SR_FBE                     ETH_DMAC0SR_FBE_Msk                                 /*!< Fatal Bus Error */
#define ETH_DMAC0SR_CDE_Pos                 (13U)
#define ETH_DMAC0SR_CDE_Msk                 (0x1U << ETH_DMAC0SR_CDE_Pos)                       /*!< 0x00002000 */
#define ETH_DMAC0SR_CDE                     ETH_DMAC0SR_CDE_Msk                                 /*!< Context Descriptor Error */
#define ETH_DMAC0SR_AIS_Pos                 (14U)
#define ETH_DMAC0SR_AIS_Msk                 (0x1U << ETH_DMAC0SR_AIS_Pos)                       /*!< 0x00004000 */
#define ETH_DMAC0SR_AIS                     ETH_DMAC0SR_AIS_Msk                                 /*!< Abnormal Interrupt Summary */
#define ETH_DMAC0SR_NIS_Pos                 (15U)
#define ETH_DMAC0SR_NIS_Msk                 (0x1U << ETH_DMAC0SR_NIS_Pos)                       /*!< 0x00008000 */
#define ETH_DMAC0SR_NIS                     ETH_DMAC0SR_NIS_Msk                                 /*!< Normal Interrupt Summary */
#define ETH_DMAC0SR_TEB_Pos                 (16U)
#define ETH_DMAC0SR_TEB_Msk                 (0x7U << ETH_DMAC0SR_TEB_Pos)                       /*!< 0x00070000 */
#define ETH_DMAC0SR_TEB                     ETH_DMAC0SR_TEB_Msk                                 /*!< Tx DMA Error Bits */
#define ETH_DMAC0SR_TEB_0                   (0x1U << ETH_DMAC0SR_TEB_Pos)                   /*!< 0x00010000 */
#define ETH_DMAC0SR_TEB_1                   (0x2U << ETH_DMAC0SR_TEB_Pos)                   /*!< 0x00020000 */
#define ETH_DMAC0SR_TEB_2                   (0x4U << ETH_DMAC0SR_TEB_Pos)                   /*!< 0x00040000 */
#define ETH_DMAC0SR_REB_Pos                 (19U)
#define ETH_DMAC0SR_REB_Msk                 (0x7U << ETH_DMAC0SR_REB_Pos)                       /*!< 0x00380000 */
#define ETH_DMAC0SR_REB                     ETH_DMAC0SR_REB_Msk                                 /*!< Rx DMA Error Bits */
#define ETH_DMAC0SR_REB_0                   (0x1U << ETH_DMAC0SR_REB_Pos)                   /*!< 0x00080000 */
#define ETH_DMAC0SR_REB_1                   (0x2U << ETH_DMAC0SR_REB_Pos)                  /*!< 0x00100000 */
#define ETH_DMAC0SR_REB_2                   (0x4U << ETH_DMAC0SR_REB_Pos)                  /*!< 0x00200000 */

/*************  Bit definition for ETH_DMAC0MFCR register  *************/
#define ETH_DMAC0MFCR_MFC_Pos               (0U)
#define ETH_DMAC0MFCR_MFC_Msk               (0x7FFU << ETH_DMAC0MFCR_MFC_Pos)                   /*!< 0x000007FF */
#define ETH_DMAC0MFCR_MFC                   ETH_DMAC0MFCR_MFC_Msk                               /*!< Dropped Packet Counters */
#define ETH_DMAC0MFCR_MFC_0                 (0x1U << ETH_DMAC0MFCR_MFC_Pos)                     /*!< 0x00000001 */
#define ETH_DMAC0MFCR_MFC_1                 (0x2U << ETH_DMAC0MFCR_MFC_Pos)                     /*!< 0x00000002 */
#define ETH_DMAC0MFCR_MFC_2                 (0x4U << ETH_DMAC0MFCR_MFC_Pos)                     /*!< 0x00000004 */
#define ETH_DMAC0MFCR_MFC_3                 (0x8U << ETH_DMAC0MFCR_MFC_Pos)                     /*!< 0x00000008 */
#define ETH_DMAC0MFCR_MFC_4                 (0x10U << ETH_DMAC0MFCR_MFC_Pos)                    /*!< 0x00000010 */
#define ETH_DMAC0MFCR_MFC_5                 (0x20U << ETH_DMAC0MFCR_MFC_Pos)                    /*!< 0x00000020 */
#define ETH_DMAC0MFCR_MFC_6                 (0x40U << ETH_DMAC0MFCR_MFC_Pos)                    /*!< 0x00000040 */
#define ETH_DMAC0MFCR_MFC_7                 (0x80U << ETH_DMAC0MFCR_MFC_Pos)                    /*!< 0x00000080 */
#define ETH_DMAC0MFCR_MFC_8                 (0x100U << ETH_DMAC0MFCR_MFC_Pos)                   /*!< 0x00000100 */
#define ETH_DMAC0MFCR_MFC_9                 (0x200U << ETH_DMAC0MFCR_MFC_Pos)                   /*!< 0x00000200 */
#define ETH_DMAC0MFCR_MFC_10                (0x400U << ETH_DMAC0MFCR_MFC_Pos)                   /*!< 0x00000400 */
#define ETH_DMAC0MFCR_MFCO_Pos              (15U)
#define ETH_DMAC0MFCR_MFCO_Msk              (0x1U << ETH_DMAC0MFCR_MFCO_Pos)                    /*!< 0x00008000 */
#define ETH_DMAC0MFCR_MFCO                  ETH_DMAC0MFCR_MFCO_Msk                              /*!< Overflow status of the MFC Counter */

/**************  Bit definition for ETH_DMAC1CR register  **************/
#define ETH_DMAC1CR_MSS_Pos                 (0U)
#define ETH_DMAC1CR_MSS_Msk                 (0x3FFFU << ETH_DMAC1CR_MSS_Pos)                    /*!< 0x00003FFF */
#define ETH_DMAC1CR_MSS                     ETH_DMAC1CR_MSS_Msk                                 /*!< Maximum Segment Size */
#define ETH_DMAC1CR_MSS_0                   (0x1U << ETH_DMAC1CR_MSS_Pos)                       /*!< 0x00000001 */
#define ETH_DMAC1CR_MSS_1                   (0x2U << ETH_DMAC1CR_MSS_Pos)                       /*!< 0x00000002 */
#define ETH_DMAC1CR_MSS_2                   (0x4U << ETH_DMAC1CR_MSS_Pos)                       /*!< 0x00000004 */
#define ETH_DMAC1CR_MSS_3                   (0x8U << ETH_DMAC1CR_MSS_Pos)                       /*!< 0x00000008 */
#define ETH_DMAC1CR_MSS_4                   (0x10U << ETH_DMAC1CR_MSS_Pos)                      /*!< 0x00000010 */
#define ETH_DMAC1CR_MSS_5                   (0x20U << ETH_DMAC1CR_MSS_Pos)                      /*!< 0x00000020 */
#define ETH_DMAC1CR_MSS_6                   (0x40U << ETH_DMAC1CR_MSS_Pos)                      /*!< 0x00000040 */
#define ETH_DMAC1CR_MSS_7                   (0x80U << ETH_DMAC1CR_MSS_Pos)                      /*!< 0x00000080 */
#define ETH_DMAC1CR_MSS_8                   (0x100U << ETH_DMAC1CR_MSS_Pos)                     /*!< 0x00000100 */
#define ETH_DMAC1CR_MSS_9                   (0x200U << ETH_DMAC1CR_MSS_Pos)                     /*!< 0x00000200 */
#define ETH_DMAC1CR_MSS_10                  (0x400U << ETH_DMAC1CR_MSS_Pos)                     /*!< 0x00000400 */
#define ETH_DMAC1CR_MSS_11                  (0x800U << ETH_DMAC1CR_MSS_Pos)                     /*!< 0x00000800 */
#define ETH_DMAC1CR_MSS_12                  (0x1000U << ETH_DMAC1CR_MSS_Pos)                    /*!< 0x00001000 */
#define ETH_DMAC1CR_MSS_13                  (0x2000U << ETH_DMAC1CR_MSS_Pos)                    /*!< 0x00002000 */
#define ETH_DMAC1CR_PBLX8_Pos               (16U)
#define ETH_DMAC1CR_PBLX8_Msk               (0x1U << ETH_DMAC1CR_PBLX8_Pos)                     /*!< 0x00010000 */
#define ETH_DMAC1CR_PBLX8                   ETH_DMAC1CR_PBLX8_Msk                               /*!< 8xPBL mode */
#define ETH_DMAC1CR_DSL_Pos                 (18U)
#define ETH_DMAC1CR_DSL_Msk                 (0x7U << ETH_DMAC1CR_DSL_Pos)                       /*!< 0x001C0000 */
#define ETH_DMAC1CR_DSL                     ETH_DMAC1CR_DSL_Msk                                 /*!< Descriptor Skip Length */
#define ETH_DMAC1CR_DSL_0                   (0x1U << ETH_DMAC1CR_DSL_Pos)                   /*!< 0x00040000 */
#define ETH_DMAC1CR_DSL_1                   (0x2U << ETH_DMAC1CR_DSL_Pos)                   /*!< 0x00080000 */
#define ETH_DMAC1CR_DSL_2                   (0x4U << ETH_DMAC1CR_DSL_Pos)                  /*!< 0x00100000 */

/*************  Bit definition for ETH_DMAC1TXCR register  *************/
#define ETH_DMAC1TXCR_ST_Pos                (0U)
#define ETH_DMAC1TXCR_ST_Msk                (0x1U << ETH_DMAC1TXCR_ST_Pos)                      /*!< 0x00000001 */
#define ETH_DMAC1TXCR_ST                    ETH_DMAC1TXCR_ST_Msk                                /*!< Start or Stop Transmission Command */
#define ETH_DMAC1TXCR_TCW_Pos               (1U)
#define ETH_DMAC1TXCR_TCW_Msk               (0x7U << ETH_DMAC1TXCR_TCW_Pos)                     /*!< 0x0000000E */
#define ETH_DMAC1TXCR_TCW                   ETH_DMAC1TXCR_TCW_Msk                               /*!< Transmit Channel Weight */
#define ETH_DMAC1TXCR_TCW_0                 (0x1U << ETH_DMAC1TXCR_TCW_Pos)                     /*!< 0x00000002 */
#define ETH_DMAC1TXCR_TCW_1                 (0x2U << ETH_DMAC1TXCR_TCW_Pos)                     /*!< 0x00000004 */
#define ETH_DMAC1TXCR_TCW_2                 (0x4U << ETH_DMAC1TXCR_TCW_Pos)                     /*!< 0x00000008 */
#define ETH_DMAC1TXCR_OSF_Pos               (4U)
#define ETH_DMAC1TXCR_OSF_Msk               (0x1U << ETH_DMAC1TXCR_OSF_Pos)                     /*!< 0x00000010 */
#define ETH_DMAC1TXCR_OSF                   ETH_DMAC1TXCR_OSF_Msk                               /*!< Operate on Second Packet */
#define ETH_DMAC1TXCR_TSE_Pos               (12U)
#define ETH_DMAC1TXCR_TSE_Msk               (0x1U << ETH_DMAC1TXCR_TSE_Pos)                     /*!< 0x00001000 */
#define ETH_DMAC1TXCR_TSE                   ETH_DMAC1TXCR_TSE_Msk                               /*!< TCP Segmentation Enabled */
#define ETH_DMAC1TXCR_TXPBL_Pos             (16U)
#define ETH_DMAC1TXCR_TXPBL_Msk             (0x3FU << ETH_DMAC1TXCR_TXPBL_Pos)                  /*!< 0x003F0000 */
#define ETH_DMAC1TXCR_TXPBL                 ETH_DMAC1TXCR_TXPBL_Msk                             /*!< Transmit Programmable Burst Length */
#define ETH_DMAC1TXCR_TXPBL_0               (0x1U << ETH_DMAC1TXCR_TXPBL_Pos)               /*!< 0x00010000 */
#define ETH_DMAC1TXCR_TXPBL_1               (0x2U << ETH_DMAC1TXCR_TXPBL_Pos)               /*!< 0x00020000 */
#define ETH_DMAC1TXCR_TXPBL_2               (0x4U << ETH_DMAC1TXCR_TXPBL_Pos)               /*!< 0x00040000 */
#define ETH_DMAC1TXCR_TXPBL_3               (0x8U << ETH_DMAC1TXCR_TXPBL_Pos)               /*!< 0x00080000 */
#define ETH_DMAC1TXCR_TXPBL_4               (0x10U << ETH_DMAC1TXCR_TXPBL_Pos)              /*!< 0x00100000 */
#define ETH_DMAC1TXCR_TXPBL_5               (0x20U << ETH_DMAC1TXCR_TXPBL_Pos)              /*!< 0x00200000 */
#define ETH_DMAC1TXCR_TQOS_Pos              (24U)
#define ETH_DMAC1TXCR_TQOS_Msk              (0xFU << ETH_DMAC1TXCR_TQOS_Pos)                    /*!< 0x0F000000 */
#define ETH_DMAC1TXCR_TQOS                  ETH_DMAC1TXCR_TQOS_Msk                              /*!< Transmit QOS. */
#define ETH_DMAC1TXCR_TQOS_0                (0x1U << ETH_DMAC1TXCR_TQOS_Pos)              /*!< 0x01000000 */
#define ETH_DMAC1TXCR_TQOS_1                (0x2U << ETH_DMAC1TXCR_TQOS_Pos)              /*!< 0x02000000 */
#define ETH_DMAC1TXCR_TQOS_2                (0x4U << ETH_DMAC1TXCR_TQOS_Pos)              /*!< 0x04000000 */
#define ETH_DMAC1TXCR_TQOS_3                (0x8U << ETH_DMAC1TXCR_TQOS_Pos)              /*!< 0x08000000 */

/************  Bit definition for ETH_DMAC1TXDLAR register  ************/
#define ETH_DMAC1TXDLAR_TDESLA_Pos          (3U)
#define ETH_DMAC1TXDLAR_TDESLA_Msk          (0x1FFFFFFFU << ETH_DMAC1TXDLAR_TDESLA_Pos)         /*!< 0xFFFFFFF8 */
#define ETH_DMAC1TXDLAR_TDESLA              ETH_DMAC1TXDLAR_TDESLA_Msk                          /*!< Start of Transmit List */
#define ETH_DMAC1TXDLAR_TDESLA_0            (0x1U << ETH_DMAC1TXDLAR_TDESLA_Pos)                /*!< 0x00000008 */
#define ETH_DMAC1TXDLAR_TDESLA_1            (0x2U << ETH_DMAC1TXDLAR_TDESLA_Pos)               /*!< 0x00000010 */
#define ETH_DMAC1TXDLAR_TDESLA_2            (0x4U << ETH_DMAC1TXDLAR_TDESLA_Pos)               /*!< 0x00000020 */
#define ETH_DMAC1TXDLAR_TDESLA_3            (0x8U << ETH_DMAC1TXDLAR_TDESLA_Pos)               /*!< 0x00000040 */
#define ETH_DMAC1TXDLAR_TDESLA_4            (0x10U << ETH_DMAC1TXDLAR_TDESLA_Pos)               /*!< 0x00000080 */
#define ETH_DMAC1TXDLAR_TDESLA_5            (0x20U << ETH_DMAC1TXDLAR_TDESLA_Pos)              /*!< 0x00000100 */
#define ETH_DMAC1TXDLAR_TDESLA_6            (0x40U << ETH_DMAC1TXDLAR_TDESLA_Pos)              /*!< 0x00000200 */
#define ETH_DMAC1TXDLAR_TDESLA_7            (0x80U << ETH_DMAC1TXDLAR_TDESLA_Pos)              /*!< 0x00000400 */
#define ETH_DMAC1TXDLAR_TDESLA_8            (0x100U << ETH_DMAC1TXDLAR_TDESLA_Pos)              /*!< 0x00000800 */
#define ETH_DMAC1TXDLAR_TDESLA_9            (0x200U << ETH_DMAC1TXDLAR_TDESLA_Pos)             /*!< 0x00001000 */
#define ETH_DMAC1TXDLAR_TDESLA_10           (0x400U << ETH_DMAC1TXDLAR_TDESLA_Pos)             /*!< 0x00002000 */
#define ETH_DMAC1TXDLAR_TDESLA_11           (0x800U << ETH_DMAC1TXDLAR_TDESLA_Pos)             /*!< 0x00004000 */
#define ETH_DMAC1TXDLAR_TDESLA_12           (0x1000U << ETH_DMAC1TXDLAR_TDESLA_Pos)             /*!< 0x00008000 */
#define ETH_DMAC1TXDLAR_TDESLA_13           (0x2000U << ETH_DMAC1TXDLAR_TDESLA_Pos)            /*!< 0x00010000 */
#define ETH_DMAC1TXDLAR_TDESLA_14           (0x4000U << ETH_DMAC1TXDLAR_TDESLA_Pos)            /*!< 0x00020000 */
#define ETH_DMAC1TXDLAR_TDESLA_15           (0x8000U << ETH_DMAC1TXDLAR_TDESLA_Pos)            /*!< 0x00040000 */
#define ETH_DMAC1TXDLAR_TDESLA_16           (0x10000U << ETH_DMAC1TXDLAR_TDESLA_Pos)            /*!< 0x00080000 */
#define ETH_DMAC1TXDLAR_TDESLA_17           (0x20000U << ETH_DMAC1TXDLAR_TDESLA_Pos)           /*!< 0x00100000 */
#define ETH_DMAC1TXDLAR_TDESLA_18           (0x40000U << ETH_DMAC1TXDLAR_TDESLA_Pos)           /*!< 0x00200000 */
#define ETH_DMAC1TXDLAR_TDESLA_19           (0x80000U << ETH_DMAC1TXDLAR_TDESLA_Pos)           /*!< 0x00400000 */
#define ETH_DMAC1TXDLAR_TDESLA_20           (0x100000U << ETH_DMAC1TXDLAR_TDESLA_Pos)           /*!< 0x00800000 */
#define ETH_DMAC1TXDLAR_TDESLA_21           (0x200000U << ETH_DMAC1TXDLAR_TDESLA_Pos)          /*!< 0x01000000 */
#define ETH_DMAC1TXDLAR_TDESLA_22           (0x400000U << ETH_DMAC1TXDLAR_TDESLA_Pos)          /*!< 0x02000000 */
#define ETH_DMAC1TXDLAR_TDESLA_23           (0x800000U << ETH_DMAC1TXDLAR_TDESLA_Pos)          /*!< 0x04000000 */
#define ETH_DMAC1TXDLAR_TDESLA_24           (0x1000000U << ETH_DMAC1TXDLAR_TDESLA_Pos)          /*!< 0x08000000 */
#define ETH_DMAC1TXDLAR_TDESLA_25           (0x2000000U << ETH_DMAC1TXDLAR_TDESLA_Pos)         /*!< 0x10000000 */
#define ETH_DMAC1TXDLAR_TDESLA_26           (0x4000000U << ETH_DMAC1TXDLAR_TDESLA_Pos)         /*!< 0x20000000 */
#define ETH_DMAC1TXDLAR_TDESLA_27           (0x8000000U << ETH_DMAC1TXDLAR_TDESLA_Pos)         /*!< 0x40000000 */
#define ETH_DMAC1TXDLAR_TDESLA_28           (0x10000000U << ETH_DMAC1TXDLAR_TDESLA_Pos)         /*!< 0x80000000 */

/************  Bit definition for ETH_DMAC1TXDTPR register  ************/
#define ETH_DMAC1TXDTPR_TDT_Pos             (3U)
#define ETH_DMAC1TXDTPR_TDT_Msk             (0x1FFFFFFFU << ETH_DMAC1TXDTPR_TDT_Pos)            /*!< 0xFFFFFFF8 */
#define ETH_DMAC1TXDTPR_TDT                 ETH_DMAC1TXDTPR_TDT_Msk                             /*!< Transmit Descriptor Tail Pointer */
#define ETH_DMAC1TXDTPR_TDT_0               (0x1U << ETH_DMAC1TXDTPR_TDT_Pos)                   /*!< 0x00000008 */
#define ETH_DMAC1TXDTPR_TDT_1               (0x2U << ETH_DMAC1TXDTPR_TDT_Pos)                  /*!< 0x00000010 */
#define ETH_DMAC1TXDTPR_TDT_2               (0x4U << ETH_DMAC1TXDTPR_TDT_Pos)                  /*!< 0x00000020 */
#define ETH_DMAC1TXDTPR_TDT_3               (0x8U << ETH_DMAC1TXDTPR_TDT_Pos)                  /*!< 0x00000040 */
#define ETH_DMAC1TXDTPR_TDT_4               (0x10U << ETH_DMAC1TXDTPR_TDT_Pos)                  /*!< 0x00000080 */
#define ETH_DMAC1TXDTPR_TDT_5               (0x20U << ETH_DMAC1TXDTPR_TDT_Pos)                 /*!< 0x00000100 */
#define ETH_DMAC1TXDTPR_TDT_6               (0x40U << ETH_DMAC1TXDTPR_TDT_Pos)                 /*!< 0x00000200 */
#define ETH_DMAC1TXDTPR_TDT_7               (0x80U << ETH_DMAC1TXDTPR_TDT_Pos)                 /*!< 0x00000400 */
#define ETH_DMAC1TXDTPR_TDT_8               (0x100U << ETH_DMAC1TXDTPR_TDT_Pos)                 /*!< 0x00000800 */
#define ETH_DMAC1TXDTPR_TDT_9               (0x200U << ETH_DMAC1TXDTPR_TDT_Pos)                /*!< 0x00001000 */
#define ETH_DMAC1TXDTPR_TDT_10              (0x400U << ETH_DMAC1TXDTPR_TDT_Pos)                /*!< 0x00002000 */
#define ETH_DMAC1TXDTPR_TDT_11              (0x800U << ETH_DMAC1TXDTPR_TDT_Pos)                /*!< 0x00004000 */
#define ETH_DMAC1TXDTPR_TDT_12              (0x1000U << ETH_DMAC1TXDTPR_TDT_Pos)                /*!< 0x00008000 */
#define ETH_DMAC1TXDTPR_TDT_13              (0x2000U << ETH_DMAC1TXDTPR_TDT_Pos)               /*!< 0x00010000 */
#define ETH_DMAC1TXDTPR_TDT_14              (0x4000U << ETH_DMAC1TXDTPR_TDT_Pos)               /*!< 0x00020000 */
#define ETH_DMAC1TXDTPR_TDT_15              (0x8000U << ETH_DMAC1TXDTPR_TDT_Pos)               /*!< 0x00040000 */
#define ETH_DMAC1TXDTPR_TDT_16              (0x10000U << ETH_DMAC1TXDTPR_TDT_Pos)               /*!< 0x00080000 */
#define ETH_DMAC1TXDTPR_TDT_17              (0x20000U << ETH_DMAC1TXDTPR_TDT_Pos)              /*!< 0x00100000 */
#define ETH_DMAC1TXDTPR_TDT_18              (0x40000U << ETH_DMAC1TXDTPR_TDT_Pos)              /*!< 0x00200000 */
#define ETH_DMAC1TXDTPR_TDT_19              (0x80000U << ETH_DMAC1TXDTPR_TDT_Pos)              /*!< 0x00400000 */
#define ETH_DMAC1TXDTPR_TDT_20              (0x100000U << ETH_DMAC1TXDTPR_TDT_Pos)              /*!< 0x00800000 */
#define ETH_DMAC1TXDTPR_TDT_21              (0x200000U << ETH_DMAC1TXDTPR_TDT_Pos)             /*!< 0x01000000 */
#define ETH_DMAC1TXDTPR_TDT_22              (0x400000U << ETH_DMAC1TXDTPR_TDT_Pos)             /*!< 0x02000000 */
#define ETH_DMAC1TXDTPR_TDT_23              (0x800000U << ETH_DMAC1TXDTPR_TDT_Pos)             /*!< 0x04000000 */
#define ETH_DMAC1TXDTPR_TDT_24              (0x1000000U << ETH_DMAC1TXDTPR_TDT_Pos)             /*!< 0x08000000 */
#define ETH_DMAC1TXDTPR_TDT_25              (0x2000000U << ETH_DMAC1TXDTPR_TDT_Pos)            /*!< 0x10000000 */
#define ETH_DMAC1TXDTPR_TDT_26              (0x4000000U << ETH_DMAC1TXDTPR_TDT_Pos)            /*!< 0x20000000 */
#define ETH_DMAC1TXDTPR_TDT_27              (0x8000000U << ETH_DMAC1TXDTPR_TDT_Pos)            /*!< 0x40000000 */
#define ETH_DMAC1TXDTPR_TDT_28              (0x10000000U << ETH_DMAC1TXDTPR_TDT_Pos)            /*!< 0x80000000 */

/************  Bit definition for ETH_DMAC1TXRLR register  *************/
#define ETH_DMAC1TXRLR_TDRL_Pos             (0U)
#define ETH_DMAC1TXRLR_TDRL_Msk             (0x3FFU << ETH_DMAC1TXRLR_TDRL_Pos)                 /*!< 0x000003FF */
#define ETH_DMAC1TXRLR_TDRL                 ETH_DMAC1TXRLR_TDRL_Msk                             /*!< Transmit Descriptor Ring Length */
#define ETH_DMAC1TXRLR_TDRL_0               (0x1U << ETH_DMAC1TXRLR_TDRL_Pos)                   /*!< 0x00000001 */
#define ETH_DMAC1TXRLR_TDRL_1               (0x2U << ETH_DMAC1TXRLR_TDRL_Pos)                   /*!< 0x00000002 */
#define ETH_DMAC1TXRLR_TDRL_2               (0x4U << ETH_DMAC1TXRLR_TDRL_Pos)                   /*!< 0x00000004 */
#define ETH_DMAC1TXRLR_TDRL_3               (0x8U << ETH_DMAC1TXRLR_TDRL_Pos)                   /*!< 0x00000008 */
#define ETH_DMAC1TXRLR_TDRL_4               (0x10U << ETH_DMAC1TXRLR_TDRL_Pos)                  /*!< 0x00000010 */
#define ETH_DMAC1TXRLR_TDRL_5               (0x20U << ETH_DMAC1TXRLR_TDRL_Pos)                  /*!< 0x00000020 */
#define ETH_DMAC1TXRLR_TDRL_6               (0x40U << ETH_DMAC1TXRLR_TDRL_Pos)                  /*!< 0x00000040 */
#define ETH_DMAC1TXRLR_TDRL_7               (0x80U << ETH_DMAC1TXRLR_TDRL_Pos)                  /*!< 0x00000080 */
#define ETH_DMAC1TXRLR_TDRL_8               (0x100U << ETH_DMAC1TXRLR_TDRL_Pos)                 /*!< 0x00000100 */
#define ETH_DMAC1TXRLR_TDRL_9               (0x200U << ETH_DMAC1TXRLR_TDRL_Pos)                 /*!< 0x00000200 */

/*************  Bit definition for ETH_DMAC1IER register  **************/
#define ETH_DMAC1IER_TIE_Pos                (0U)
#define ETH_DMAC1IER_TIE_Msk                (0x1U << ETH_DMAC1IER_TIE_Pos)                      /*!< 0x00000001 */
#define ETH_DMAC1IER_TIE                    ETH_DMAC1IER_TIE_Msk                                /*!< Transmit Interrupt Enable */
#define ETH_DMAC1IER_TXSE_Pos               (1U)
#define ETH_DMAC1IER_TXSE_Msk               (0x1U << ETH_DMAC1IER_TXSE_Pos)                     /*!< 0x00000002 */
#define ETH_DMAC1IER_TXSE                   ETH_DMAC1IER_TXSE_Msk                               /*!< Transmit Stopped Enable */
#define ETH_DMAC1IER_TBUE_Pos               (2U)
#define ETH_DMAC1IER_TBUE_Msk               (0x1U << ETH_DMAC1IER_TBUE_Pos)                     /*!< 0x00000004 */
#define ETH_DMAC1IER_TBUE                   ETH_DMAC1IER_TBUE_Msk                               /*!< Transmit Buffer Unavailable Enable */
#define ETH_DMAC1IER_RIE_Pos                (6U)
#define ETH_DMAC1IER_RIE_Msk                (0x1U << ETH_DMAC1IER_RIE_Pos)                      /*!< 0x00000040 */
#define ETH_DMAC1IER_RIE                    ETH_DMAC1IER_RIE_Msk                                /*!< Receive Interrupt Enable */
#define ETH_DMAC1IER_RBUE_Pos               (7U)
#define ETH_DMAC1IER_RBUE_Msk               (0x1U << ETH_DMAC1IER_RBUE_Pos)                     /*!< 0x00000080 */
#define ETH_DMAC1IER_RBUE                   ETH_DMAC1IER_RBUE_Msk                               /*!< Receive Buffer Unavailable Enable */
#define ETH_DMAC1IER_RSE_Pos                (8U)
#define ETH_DMAC1IER_RSE_Msk                (0x1U << ETH_DMAC1IER_RSE_Pos)                      /*!< 0x00000100 */
#define ETH_DMAC1IER_RSE                    ETH_DMAC1IER_RSE_Msk                                /*!< Receive Stopped Enable */
#define ETH_DMAC1IER_RWTE_Pos               (9U)
#define ETH_DMAC1IER_RWTE_Msk               (0x1U << ETH_DMAC1IER_RWTE_Pos)                     /*!< 0x00000200 */
#define ETH_DMAC1IER_RWTE                   ETH_DMAC1IER_RWTE_Msk                               /*!< Receive Watchdog Timeout Enable */
#define ETH_DMAC1IER_ETIE_Pos               (10U)
#define ETH_DMAC1IER_ETIE_Msk               (0x1U << ETH_DMAC1IER_ETIE_Pos)                     /*!< 0x00000400 */
#define ETH_DMAC1IER_ETIE                   ETH_DMAC1IER_ETIE_Msk                               /*!< Early Transmit Interrupt Enable */
#define ETH_DMAC1IER_ERIE_Pos               (11U)
#define ETH_DMAC1IER_ERIE_Msk               (0x1U << ETH_DMAC1IER_ERIE_Pos)                     /*!< 0x00000800 */
#define ETH_DMAC1IER_ERIE                   ETH_DMAC1IER_ERIE_Msk                               /*!< Early Receive Interrupt Enable */
#define ETH_DMAC1IER_FBEE_Pos               (12U)
#define ETH_DMAC1IER_FBEE_Msk               (0x1U << ETH_DMAC1IER_FBEE_Pos)                     /*!< 0x00001000 */
#define ETH_DMAC1IER_FBEE                   ETH_DMAC1IER_FBEE_Msk                               /*!< Fatal Bus Error Enable */
#define ETH_DMAC1IER_CDEE_Pos               (13U)
#define ETH_DMAC1IER_CDEE_Msk               (0x1U << ETH_DMAC1IER_CDEE_Pos)                     /*!< 0x00002000 */
#define ETH_DMAC1IER_CDEE                   ETH_DMAC1IER_CDEE_Msk                               /*!< Context Descriptor Error Enable */
#define ETH_DMAC1IER_AIE_Pos                (14U)
#define ETH_DMAC1IER_AIE_Msk                (0x1U << ETH_DMAC1IER_AIE_Pos)                      /*!< 0x00004000 */
#define ETH_DMAC1IER_AIE                    ETH_DMAC1IER_AIE_Msk                                /*!< Abnormal Interrupt Summary Enable */
#define ETH_DMAC1IER_NIE_Pos                (15U)
#define ETH_DMAC1IER_NIE_Msk                (0x1U << ETH_DMAC1IER_NIE_Pos)                      /*!< 0x00008000 */
#define ETH_DMAC1IER_NIE                    ETH_DMAC1IER_NIE_Msk                                /*!< Normal Interrupt Summary Enable */

/************  Bit definition for ETH_DMAC1SFCSR register  *************/
#define ETH_DMAC1SFCSR_ESC_Pos              (0U)
#define ETH_DMAC1SFCSR_ESC_Msk              (0x1U << ETH_DMAC1SFCSR_ESC_Pos)                    /*!< 0x00000001 */
#define ETH_DMAC1SFCSR_ESC                  ETH_DMAC1SFCSR_ESC_Msk                              /*!< Enable Slot Comparison */
#define ETH_DMAC1SFCSR_ASC_Pos              (1U)
#define ETH_DMAC1SFCSR_ASC_Msk              (0x1U << ETH_DMAC1SFCSR_ASC_Pos)                    /*!< 0x00000002 */
#define ETH_DMAC1SFCSR_ASC                  ETH_DMAC1SFCSR_ASC_Msk                              /*!< Advance Slot Check */
#define ETH_DMAC1SFCSR_RSN_Pos              (16U)
#define ETH_DMAC1SFCSR_RSN_Msk              (0xFU << ETH_DMAC1SFCSR_RSN_Pos)                    /*!< 0x000F0000 */
#define ETH_DMAC1SFCSR_RSN                  ETH_DMAC1SFCSR_RSN_Msk                              /*!< Reference Slot Number */
#define ETH_DMAC1SFCSR_RSN_0                (0x1U << ETH_DMAC1SFCSR_RSN_Pos)                /*!< 0x00010000 */
#define ETH_DMAC1SFCSR_RSN_1                (0x2U << ETH_DMAC1SFCSR_RSN_Pos)                /*!< 0x00020000 */
#define ETH_DMAC1SFCSR_RSN_2                (0x4U << ETH_DMAC1SFCSR_RSN_Pos)                /*!< 0x00040000 */
#define ETH_DMAC1SFCSR_RSN_3                (0x8U << ETH_DMAC1SFCSR_RSN_Pos)                /*!< 0x00080000 */

/************  Bit definition for ETH_DMAC1CATXDR register  ************/
#define ETH_DMAC1CATXDR_CURTDESAPTR_Pos     (0U)
#define ETH_DMAC1CATXDR_CURTDESAPTR_Msk     (0xFFFFFFFFU << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)    /*!< 0xFFFFFFFF */
#define ETH_DMAC1CATXDR_CURTDESAPTR         ETH_DMAC1CATXDR_CURTDESAPTR_Msk                     /*!< Application Transmit Descriptor Address Pointer */
#define ETH_DMAC1CATXDR_CURTDESAPTR_0       (0x1U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)           /*!< 0x00000001 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_1       (0x2U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)           /*!< 0x00000002 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_2       (0x4U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)           /*!< 0x00000004 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_3       (0x8U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)           /*!< 0x00000008 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_4       (0x10U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)          /*!< 0x00000010 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_5       (0x20U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)          /*!< 0x00000020 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_6       (0x40U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)          /*!< 0x00000040 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_7       (0x80U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)          /*!< 0x00000080 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_8       (0x100U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)         /*!< 0x00000100 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_9       (0x200U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)         /*!< 0x00000200 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_10      (0x400U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)         /*!< 0x00000400 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_11      (0x800U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)         /*!< 0x00000800 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_12      (0x1000U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)        /*!< 0x00001000 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_13      (0x2000U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)        /*!< 0x00002000 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_14      (0x4000U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)        /*!< 0x00004000 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_15      (0x8000U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)        /*!< 0x00008000 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_16      (0x10000U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)       /*!< 0x00010000 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_17      (0x20000U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)       /*!< 0x00020000 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_18      (0x40000U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)       /*!< 0x00040000 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_19      (0x80000U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)       /*!< 0x00080000 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_20      (0x100000U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)      /*!< 0x00100000 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_21      (0x200000U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)      /*!< 0x00200000 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_22      (0x400000U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)      /*!< 0x00400000 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_23      (0x800000U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)      /*!< 0x00800000 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_24      (0x1000000U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)     /*!< 0x01000000 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_25      (0x2000000U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)     /*!< 0x02000000 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_26      (0x4000000U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)     /*!< 0x04000000 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_27      (0x8000000U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)     /*!< 0x08000000 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_28      (0x10000000U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)    /*!< 0x10000000 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_29      (0x20000000U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)    /*!< 0x20000000 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_30      (0x40000000U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)    /*!< 0x40000000 */
#define ETH_DMAC1CATXDR_CURTDESAPTR_31      (0x80000000U << ETH_DMAC1CATXDR_CURTDESAPTR_Pos)    /*!< 0x80000000 */

/************  Bit definition for ETH_DMAC1CATXBR register  ************/
#define ETH_DMAC1CATXBR_CURTBUFAPTR_Pos     (0U)
#define ETH_DMAC1CATXBR_CURTBUFAPTR_Msk     (0xFFFFFFFFU << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)    /*!< 0xFFFFFFFF */
#define ETH_DMAC1CATXBR_CURTBUFAPTR         ETH_DMAC1CATXBR_CURTBUFAPTR_Msk                     /*!< Application Transmit Buffer Address Pointer */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_0       (0x1U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)           /*!< 0x00000001 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_1       (0x2U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)           /*!< 0x00000002 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_2       (0x4U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)           /*!< 0x00000004 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_3       (0x8U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)           /*!< 0x00000008 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_4       (0x10U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)          /*!< 0x00000010 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_5       (0x20U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)          /*!< 0x00000020 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_6       (0x40U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)          /*!< 0x00000040 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_7       (0x80U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)          /*!< 0x00000080 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_8       (0x100U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)         /*!< 0x00000100 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_9       (0x200U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)         /*!< 0x00000200 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_10      (0x400U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)         /*!< 0x00000400 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_11      (0x800U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)         /*!< 0x00000800 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_12      (0x1000U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)        /*!< 0x00001000 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_13      (0x2000U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)        /*!< 0x00002000 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_14      (0x4000U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)        /*!< 0x00004000 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_15      (0x8000U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)        /*!< 0x00008000 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_16      (0x10000U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)       /*!< 0x00010000 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_17      (0x20000U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)       /*!< 0x00020000 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_18      (0x40000U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)       /*!< 0x00040000 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_19      (0x80000U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)       /*!< 0x00080000 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_20      (0x100000U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)      /*!< 0x00100000 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_21      (0x200000U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)      /*!< 0x00200000 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_22      (0x400000U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)      /*!< 0x00400000 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_23      (0x800000U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)      /*!< 0x00800000 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_24      (0x1000000U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)     /*!< 0x01000000 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_25      (0x2000000U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)     /*!< 0x02000000 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_26      (0x4000000U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)     /*!< 0x04000000 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_27      (0x8000000U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)     /*!< 0x08000000 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_28      (0x10000000U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)    /*!< 0x10000000 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_29      (0x20000000U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)    /*!< 0x20000000 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_30      (0x40000000U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)    /*!< 0x40000000 */
#define ETH_DMAC1CATXBR_CURTBUFAPTR_31      (0x80000000U << ETH_DMAC1CATXBR_CURTBUFAPTR_Pos)    /*!< 0x80000000 */

/**************  Bit definition for ETH_DMAC1SR register  **************/
#define ETH_DMAC1SR_TI_Pos                  (0U)
#define ETH_DMAC1SR_TI_Msk                  (0x1U << ETH_DMAC1SR_TI_Pos)                        /*!< 0x00000001 */
#define ETH_DMAC1SR_TI                      ETH_DMAC1SR_TI_Msk                                  /*!< Transmit Interrupt */
#define ETH_DMAC1SR_TPS_Pos                 (1U)
#define ETH_DMAC1SR_TPS_Msk                 (0x1U << ETH_DMAC1SR_TPS_Pos)                       /*!< 0x00000002 */
#define ETH_DMAC1SR_TPS                     ETH_DMAC1SR_TPS_Msk                                 /*!< Transmit Process Stopped */
#define ETH_DMAC1SR_TBU_Pos                 (2U)
#define ETH_DMAC1SR_TBU_Msk                 (0x1U << ETH_DMAC1SR_TBU_Pos)                       /*!< 0x00000004 */
#define ETH_DMAC1SR_TBU                     ETH_DMAC1SR_TBU_Msk                                 /*!< Transmit Buffer Unavailable */
#define ETH_DMAC1SR_RI_Pos                  (6U)
#define ETH_DMAC1SR_RI_Msk                  (0x1U << ETH_DMAC1SR_RI_Pos)                        /*!< 0x00000040 */
#define ETH_DMAC1SR_RI                      ETH_DMAC1SR_RI_Msk                                  /*!< Receive Interrupt */
#define ETH_DMAC1SR_RBU_Pos                 (7U)
#define ETH_DMAC1SR_RBU_Msk                 (0x1U << ETH_DMAC1SR_RBU_Pos)                       /*!< 0x00000080 */
#define ETH_DMAC1SR_RBU                     ETH_DMAC1SR_RBU_Msk                                 /*!< Receive Buffer Unavailable */
#define ETH_DMAC1SR_RPS_Pos                 (8U)
#define ETH_DMAC1SR_RPS_Msk                 (0x1U << ETH_DMAC1SR_RPS_Pos)                       /*!< 0x00000100 */
#define ETH_DMAC1SR_RPS                     ETH_DMAC1SR_RPS_Msk                                 /*!< Receive Process Stopped */
#define ETH_DMAC1SR_RWT_Pos                 (9U)
#define ETH_DMAC1SR_RWT_Msk                 (0x1U << ETH_DMAC1SR_RWT_Pos)                       /*!< 0x00000200 */
#define ETH_DMAC1SR_RWT                     ETH_DMAC1SR_RWT_Msk                                 /*!< Receive Watchdog Timeout */
#define ETH_DMAC1SR_ETI_Pos                 (10U)
#define ETH_DMAC1SR_ETI_Msk                 (0x1U << ETH_DMAC1SR_ETI_Pos)                       /*!< 0x00000400 */
#define ETH_DMAC1SR_ETI                     ETH_DMAC1SR_ETI_Msk                                 /*!< Early Transmit Interrupt */
#define ETH_DMAC1SR_ERI_Pos                 (11U)
#define ETH_DMAC1SR_ERI_Msk                 (0x1U << ETH_DMAC1SR_ERI_Pos)                       /*!< 0x00000800 */
#define ETH_DMAC1SR_ERI                     ETH_DMAC1SR_ERI_Msk                                 /*!< Early Receive Interrupt */
#define ETH_DMAC1SR_FBE_Pos                 (12U)
#define ETH_DMAC1SR_FBE_Msk                 (0x1U << ETH_DMAC1SR_FBE_Pos)                       /*!< 0x00001000 */
#define ETH_DMAC1SR_FBE                     ETH_DMAC1SR_FBE_Msk                                 /*!< Fatal Bus Error */
#define ETH_DMAC1SR_CDE_Pos                 (13U)
#define ETH_DMAC1SR_CDE_Msk                 (0x1U << ETH_DMAC1SR_CDE_Pos)                       /*!< 0x00002000 */
#define ETH_DMAC1SR_CDE                     ETH_DMAC1SR_CDE_Msk                                 /*!< Context Descriptor Error */
#define ETH_DMAC1SR_AIS_Pos                 (14U)
#define ETH_DMAC1SR_AIS_Msk                 (0x1U << ETH_DMAC1SR_AIS_Pos)                       /*!< 0x00004000 */
#define ETH_DMAC1SR_AIS                     ETH_DMAC1SR_AIS_Msk                                 /*!< Abnormal Interrupt Summary */
#define ETH_DMAC1SR_NIS_Pos                 (15U)
#define ETH_DMAC1SR_NIS_Msk                 (0x1U << ETH_DMAC1SR_NIS_Pos)                       /*!< 0x00008000 */
#define ETH_DMAC1SR_NIS                     ETH_DMAC1SR_NIS_Msk                                 /*!< Normal Interrupt Summary */
#define ETH_DMAC1SR_TEB_Pos                 (16U)
#define ETH_DMAC1SR_TEB_Msk                 (0x7U << ETH_DMAC1SR_TEB_Pos)                       /*!< 0x00070000 */
#define ETH_DMAC1SR_TEB                     ETH_DMAC1SR_TEB_Msk                                 /*!< Tx DMA Error Bits */
#define ETH_DMAC1SR_TEB_0                   (0x1U << ETH_DMAC1SR_TEB_Pos)                   /*!< 0x00010000 */
#define ETH_DMAC1SR_TEB_1                   (0x2U << ETH_DMAC1SR_TEB_Pos)                   /*!< 0x00020000 */
#define ETH_DMAC1SR_TEB_2                   (0x4U << ETH_DMAC1SR_TEB_Pos)                   /*!< 0x00040000 */
#define ETH_DMAC1SR_REB_Pos                 (19U)
#define ETH_DMAC1SR_REB_Msk                 (0x7U << ETH_DMAC1SR_REB_Pos)                       /*!< 0x00380000 */
#define ETH_DMAC1SR_REB                     ETH_DMAC1SR_REB_Msk                                 /*!< Rx DMA Error Bits */
#define ETH_DMAC1SR_REB_0                   (0x1U << ETH_DMAC1SR_REB_Pos)                   /*!< 0x00080000 */
#define ETH_DMAC1SR_REB_1                   (0x2U << ETH_DMAC1SR_REB_Pos)                  /*!< 0x00100000 */
#define ETH_DMAC1SR_REB_2                   (0x4U << ETH_DMAC1SR_REB_Pos)                  /*!< 0x00200000 */

/*************  Bit definition for ETH_DMAC1MFCR register  *************/
#define ETH_DMAC1MFCR_MFC_Pos               (0U)
#define ETH_DMAC1MFCR_MFC_Msk               (0x7FFU << ETH_DMAC1MFCR_MFC_Pos)                   /*!< 0x000007FF */
#define ETH_DMAC1MFCR_MFC                   ETH_DMAC1MFCR_MFC_Msk                               /*!< Dropped Packet Counters */
#define ETH_DMAC1MFCR_MFC_0                 (0x1U << ETH_DMAC1MFCR_MFC_Pos)                     /*!< 0x00000001 */
#define ETH_DMAC1MFCR_MFC_1                 (0x2U << ETH_DMAC1MFCR_MFC_Pos)                     /*!< 0x00000002 */
#define ETH_DMAC1MFCR_MFC_2                 (0x4U << ETH_DMAC1MFCR_MFC_Pos)                     /*!< 0x00000004 */
#define ETH_DMAC1MFCR_MFC_3                 (0x8U << ETH_DMAC1MFCR_MFC_Pos)                     /*!< 0x00000008 */
#define ETH_DMAC1MFCR_MFC_4                 (0x10U << ETH_DMAC1MFCR_MFC_Pos)                    /*!< 0x00000010 */
#define ETH_DMAC1MFCR_MFC_5                 (0x20U << ETH_DMAC1MFCR_MFC_Pos)                    /*!< 0x00000020 */
#define ETH_DMAC1MFCR_MFC_6                 (0x40U << ETH_DMAC1MFCR_MFC_Pos)                    /*!< 0x00000040 */
#define ETH_DMAC1MFCR_MFC_7                 (0x80U << ETH_DMAC1MFCR_MFC_Pos)                    /*!< 0x00000080 */
#define ETH_DMAC1MFCR_MFC_8                 (0x100U << ETH_DMAC1MFCR_MFC_Pos)                   /*!< 0x00000100 */
#define ETH_DMAC1MFCR_MFC_9                 (0x200U << ETH_DMAC1MFCR_MFC_Pos)                   /*!< 0x00000200 */
#define ETH_DMAC1MFCR_MFC_10                (0x400U << ETH_DMAC1MFCR_MFC_Pos)                   /*!< 0x00000400 */
#define ETH_DMAC1MFCR_MFCO_Pos              (15U)
#define ETH_DMAC1MFCR_MFCO_Msk              (0x1U << ETH_DMAC1MFCR_MFCO_Pos)                    /*!< 0x00008000 */
#define ETH_DMAC1MFCR_MFCO                  ETH_DMAC1MFCR_MFCO_Msk                              /*!< Overflow status of the MFC Counter */
