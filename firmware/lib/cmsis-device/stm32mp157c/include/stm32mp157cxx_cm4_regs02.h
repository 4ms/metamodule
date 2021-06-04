
/******************************************************************************/
/*                                                                            */
/*                    DDRCTRL block description (DDRCTRL)                     */
/*                                                                            */
/******************************************************************************/

/*****************  Bit definition for DDRCTRL_MSTR register  *****************/
#define DDRCTRL_MSTR_DDR3_Pos              (0U)
#define DDRCTRL_MSTR_DDR3_Msk              (0x1U << DDRCTRL_MSTR_DDR3_Pos)              /*!< 0x00000001 */
#define DDRCTRL_MSTR_DDR3                  DDRCTRL_MSTR_DDR3_Msk                        /*!< Selects DDR3 SDRAM */
#define DDRCTRL_MSTR_LPDDR2_Pos            (2U)
#define DDRCTRL_MSTR_LPDDR2_Msk            (0x1U << DDRCTRL_MSTR_LPDDR2_Pos)            /*!< 0x00000004 */
#define DDRCTRL_MSTR_LPDDR2                DDRCTRL_MSTR_LPDDR2_Msk                      /*!< Selects LPDDR2 SDRAM */
#define DDRCTRL_MSTR_LPDDR3_Pos            (3U)
#define DDRCTRL_MSTR_LPDDR3_Msk            (0x1U << DDRCTRL_MSTR_LPDDR3_Pos)            /*!< 0x00000008 */
#define DDRCTRL_MSTR_LPDDR3                DDRCTRL_MSTR_LPDDR3_Msk                      /*!< Selects LPDDR3 SDRAM */
#define DDRCTRL_MSTR_BURSTCHOP_Pos         (9U)
#define DDRCTRL_MSTR_BURSTCHOP_Msk         (0x1U << DDRCTRL_MSTR_BURSTCHOP_Pos)         /*!< 0x00000200 */
#define DDRCTRL_MSTR_BURSTCHOP             DDRCTRL_MSTR_BURSTCHOP_Msk                   /*!< When set, enable burst-chop (BC4 or 8 on-the-fly) in DDR3/DDR4. the burst-chop for Reads is exercised only in HIF configurations (UMCTL2_INCL_ARB not set) and if in full bus width mode (MSTR.data_bus_width = 00) and if MEMC_BURST_LENGTH=8 or 16. The burst-chop for writes is exercised only if partial writes enabled (UMCTL2_PARTIAL_WR=1) and if CRC is disabled (CRCPARCTL1.crc_enable = 0). */
#define DDRCTRL_MSTR_EN_2T_TIMING_MODE_Pos (10U)
#define DDRCTRL_MSTR_EN_2T_TIMING_MODE_Msk (0x1U << DDRCTRL_MSTR_EN_2T_TIMING_MODE_Pos) /*!< 0x00000400 */
#define DDRCTRL_MSTR_EN_2T_TIMING_MODE     DDRCTRL_MSTR_EN_2T_TIMING_MODE_Msk           /*!< If 1, then the DDRCTRL uses 2T timing. Otherwise, uses 1T timing. In 2T timing, all command signals (except chip select) are held for 2 clocks on the SDRAM bus. The chip select is asserted on the second cycle of the command */
#define DDRCTRL_MSTR_DATA_BUS_WIDTH_Pos    (12U)
#define DDRCTRL_MSTR_DATA_BUS_WIDTH_Msk    (0x3U << DDRCTRL_MSTR_DATA_BUS_WIDTH_Pos)    /*!< 0x00003000 */
#define DDRCTRL_MSTR_DATA_BUS_WIDTH        DDRCTRL_MSTR_DATA_BUS_WIDTH_Msk              /*!< Selects proportion of DQ bus width that is used by the SDRAM */
#define DDRCTRL_MSTR_DATA_BUS_WIDTH_0      (0x1U << DDRCTRL_MSTR_DATA_BUS_WIDTH_Pos)    /*!< 0x00001000 */
#define DDRCTRL_MSTR_DATA_BUS_WIDTH_1      (0x2U << DDRCTRL_MSTR_DATA_BUS_WIDTH_Pos)    /*!< 0x00002000 */
#define DDRCTRL_MSTR_DLL_OFF_MODE_Pos      (15U)
#define DDRCTRL_MSTR_DLL_OFF_MODE_Msk      (0x1U << DDRCTRL_MSTR_DLL_OFF_MODE_Pos)      /*!< 0x00008000 */
#define DDRCTRL_MSTR_DLL_OFF_MODE          DDRCTRL_MSTR_DLL_OFF_MODE_Msk                /*!< Set to 1 when the DDRCTRL and DRAM has to be put in DLL-off mode for low frequency operation. */
#define DDRCTRL_MSTR_BURST_RDWR_Pos        (16U)
#define DDRCTRL_MSTR_BURST_RDWR_Msk        (0xFU << DDRCTRL_MSTR_BURST_RDWR_Pos)        /*!< 0x000F0000 */
#define DDRCTRL_MSTR_BURST_RDWR            DDRCTRL_MSTR_BURST_RDWR_Msk                  /*!< SDRAM burst length used: */
#define DDRCTRL_MSTR_BURST_RDWR_0          (0x1U << DDRCTRL_MSTR_BURST_RDWR_Pos)        /*!< 0x00010000 */
#define DDRCTRL_MSTR_BURST_RDWR_1          (0x2U << DDRCTRL_MSTR_BURST_RDWR_Pos)        /*!< 0x00020000 */
#define DDRCTRL_MSTR_BURST_RDWR_2          (0x4U << DDRCTRL_MSTR_BURST_RDWR_Pos)        /*!< 0x00040000 */
#define DDRCTRL_MSTR_BURST_RDWR_3          (0x8U << DDRCTRL_MSTR_BURST_RDWR_Pos)        /*!< 0x00080000 */

/*****************  Bit definition for DDRCTRL_STAT register  *****************/
#define DDRCTRL_STAT_OPERATING_MODE_Pos        (0U)
#define DDRCTRL_STAT_OPERATING_MODE_Msk        (0x7U << DDRCTRL_STAT_OPERATING_MODE_Pos)        /*!< 0x00000007 */
#define DDRCTRL_STAT_OPERATING_MODE            DDRCTRL_STAT_OPERATING_MODE_Msk                  /*!< Operating mode. This is 3-bits wide in configurations with mDDR/LPDDR2/LPDDR3/LPDDR4/DDR4 support and 2-bits in all other configurations. */
#define DDRCTRL_STAT_OPERATING_MODE_0          (0x1U << DDRCTRL_STAT_OPERATING_MODE_Pos)        /*!< 0x00000001 */
#define DDRCTRL_STAT_OPERATING_MODE_1          (0x2U << DDRCTRL_STAT_OPERATING_MODE_Pos)        /*!< 0x00000002 */
#define DDRCTRL_STAT_OPERATING_MODE_2          (0x4U << DDRCTRL_STAT_OPERATING_MODE_Pos)        /*!< 0x00000004 */
#define DDRCTRL_STAT_SELFREF_TYPE_Pos          (4U)
#define DDRCTRL_STAT_SELFREF_TYPE_Msk          (0x3U << DDRCTRL_STAT_SELFREF_TYPE_Pos)          /*!< 0x00000030 */
#define DDRCTRL_STAT_SELFREF_TYPE              DDRCTRL_STAT_SELFREF_TYPE_Msk                    /*!< Flags if Self Refresh (except LPDDR4) or SR-Powerdown (LPDDR4) is entered and if it was under Automatic Self Refresh control only or not. */
#define DDRCTRL_STAT_SELFREF_TYPE_0            (0x1U << DDRCTRL_STAT_SELFREF_TYPE_Pos)          /*!< 0x00000010 */
#define DDRCTRL_STAT_SELFREF_TYPE_1            (0x2U << DDRCTRL_STAT_SELFREF_TYPE_Pos)          /*!< 0x00000020 */
#define DDRCTRL_STAT_SELFREF_CAM_NOT_EMPTY_Pos (12U)
#define DDRCTRL_STAT_SELFREF_CAM_NOT_EMPTY_Msk (0x1U << DDRCTRL_STAT_SELFREF_CAM_NOT_EMPTY_Pos) /*!< 0x00001000 */
#define DDRCTRL_STAT_SELFREF_CAM_NOT_EMPTY     DDRCTRL_STAT_SELFREF_CAM_NOT_EMPTY_Msk           /*!< Self refresh with CAMs not empty. Set to 1 when Self Refresh is entered but CAMs are not drained. Cleared after exiting Self Refresh. */

/***************  Bit definition for DDRCTRL_MRCTRL0 register  ****************/
#define DDRCTRL_MRCTRL0_MR_TYPE_Pos (0U)
#define DDRCTRL_MRCTRL0_MR_TYPE_Msk (0x1U << DDRCTRL_MRCTRL0_MR_TYPE_Pos) /*!< 0x00000001 */
#define DDRCTRL_MRCTRL0_MR_TYPE     DDRCTRL_MRCTRL0_MR_TYPE_Msk           /*!< Indicates whether the mode register operation is read or write. Only used for LPDDR2/LPDDR3/LPDDR4/DDR4. */
#define DDRCTRL_MRCTRL0_MR_RANK_Pos (4U)
#define DDRCTRL_MRCTRL0_MR_RANK_Msk (0x1U << DDRCTRL_MRCTRL0_MR_RANK_Pos) /*!< 0x00000010 */
#define DDRCTRL_MRCTRL0_MR_RANK     DDRCTRL_MRCTRL0_MR_RANK_Msk           /*!< Controls which rank is accessed by MRCTRL0.mr_wr. Normally, it is desired to access all ranks, so all bits should be set to 1. However, for multi-rank UDIMMs/RDIMMs/LRDIMMs which implement address mirroring, it may be necessary to access ranks individually. */
#define DDRCTRL_MRCTRL0_MR_ADDR_Pos (12U)
#define DDRCTRL_MRCTRL0_MR_ADDR_Msk (0xFU << DDRCTRL_MRCTRL0_MR_ADDR_Pos) /*!< 0x0000F000 */
#define DDRCTRL_MRCTRL0_MR_ADDR     DDRCTRL_MRCTRL0_MR_ADDR_Msk           /*!< Address of the mode register that is to be written to. */
#define DDRCTRL_MRCTRL0_MR_ADDR_0   (0x1U << DDRCTRL_MRCTRL0_MR_ADDR_Pos) /*!< 0x00001000 */
#define DDRCTRL_MRCTRL0_MR_ADDR_1   (0x2U << DDRCTRL_MRCTRL0_MR_ADDR_Pos) /*!< 0x00002000 */
#define DDRCTRL_MRCTRL0_MR_ADDR_2   (0x4U << DDRCTRL_MRCTRL0_MR_ADDR_Pos) /*!< 0x00004000 */
#define DDRCTRL_MRCTRL0_MR_ADDR_3   (0x8U << DDRCTRL_MRCTRL0_MR_ADDR_Pos) /*!< 0x00008000 */
#define DDRCTRL_MRCTRL0_MR_WR_Pos   (31U)
#define DDRCTRL_MRCTRL0_MR_WR_Msk   (0x1U << DDRCTRL_MRCTRL0_MR_WR_Pos)   /*!< 0x80000000 */
#define DDRCTRL_MRCTRL0_MR_WR       DDRCTRL_MRCTRL0_MR_WR_Msk             /*!< Setting this register bit to 1 triggers a mode register read or write operation. When the MR operation is complete, the DDRCTRL automatically clears this bit. The other register fields of this register must be written in a separate APB transaction, before setting this mr_wr bit. It is recommended NOT to set this signal if in Init, Deep power-down or MPSM operating modes. */

/***************  Bit definition for DDRCTRL_MRCTRL1 register  ****************/
#define DDRCTRL_MRCTRL1_MR_DATA_Pos (0U)
#define DDRCTRL_MRCTRL1_MR_DATA_Msk (0xFFFFU << DDRCTRL_MRCTRL1_MR_DATA_Pos) /*!< 0x0000FFFF */
#define DDRCTRL_MRCTRL1_MR_DATA     DDRCTRL_MRCTRL1_MR_DATA_Msk              /*!< Mode register write data for all non-LPDDR2/non-LPDDR3/non-LPDDR4 modes. */
#define DDRCTRL_MRCTRL1_MR_DATA_0   (0x1U << DDRCTRL_MRCTRL1_MR_DATA_Pos)    /*!< 0x00000001 */
#define DDRCTRL_MRCTRL1_MR_DATA_1   (0x2U << DDRCTRL_MRCTRL1_MR_DATA_Pos)    /*!< 0x00000002 */
#define DDRCTRL_MRCTRL1_MR_DATA_2   (0x4U << DDRCTRL_MRCTRL1_MR_DATA_Pos)    /*!< 0x00000004 */
#define DDRCTRL_MRCTRL1_MR_DATA_3   (0x8U << DDRCTRL_MRCTRL1_MR_DATA_Pos)    /*!< 0x00000008 */
#define DDRCTRL_MRCTRL1_MR_DATA_4   (0x10U << DDRCTRL_MRCTRL1_MR_DATA_Pos)   /*!< 0x00000010 */
#define DDRCTRL_MRCTRL1_MR_DATA_5   (0x20U << DDRCTRL_MRCTRL1_MR_DATA_Pos)   /*!< 0x00000020 */
#define DDRCTRL_MRCTRL1_MR_DATA_6   (0x40U << DDRCTRL_MRCTRL1_MR_DATA_Pos)   /*!< 0x00000040 */
#define DDRCTRL_MRCTRL1_MR_DATA_7   (0x80U << DDRCTRL_MRCTRL1_MR_DATA_Pos)   /*!< 0x00000080 */
#define DDRCTRL_MRCTRL1_MR_DATA_8   (0x100U << DDRCTRL_MRCTRL1_MR_DATA_Pos)  /*!< 0x00000100 */
#define DDRCTRL_MRCTRL1_MR_DATA_9   (0x200U << DDRCTRL_MRCTRL1_MR_DATA_Pos)  /*!< 0x00000200 */
#define DDRCTRL_MRCTRL1_MR_DATA_10  (0x400U << DDRCTRL_MRCTRL1_MR_DATA_Pos)  /*!< 0x00000400 */
#define DDRCTRL_MRCTRL1_MR_DATA_11  (0x800U << DDRCTRL_MRCTRL1_MR_DATA_Pos)  /*!< 0x00000800 */
#define DDRCTRL_MRCTRL1_MR_DATA_12  (0x1000U << DDRCTRL_MRCTRL1_MR_DATA_Pos) /*!< 0x00001000 */
#define DDRCTRL_MRCTRL1_MR_DATA_13  (0x2000U << DDRCTRL_MRCTRL1_MR_DATA_Pos) /*!< 0x00002000 */
#define DDRCTRL_MRCTRL1_MR_DATA_14  (0x4000U << DDRCTRL_MRCTRL1_MR_DATA_Pos) /*!< 0x00004000 */
#define DDRCTRL_MRCTRL1_MR_DATA_15  (0x8000U << DDRCTRL_MRCTRL1_MR_DATA_Pos) /*!< 0x00008000 */

/****************  Bit definition for DDRCTRL_MRSTAT register  ****************/
#define DDRCTRL_MRSTAT_MR_WR_BUSY_Pos (0U)
#define DDRCTRL_MRSTAT_MR_WR_BUSY_Msk (0x1U << DDRCTRL_MRSTAT_MR_WR_BUSY_Pos) /*!< 0x00000001 */
#define DDRCTRL_MRSTAT_MR_WR_BUSY     DDRCTRL_MRSTAT_MR_WR_BUSY_Msk           /*!< The SoC core may initiate a MR write operation only if this signal is low. This signal goes high in the clock after the DDRCTRL accepts the MRW/MRR request. It goes low when the MRW/MRR command is issued to the SDRAM. It is recommended not to perform MRW/MRR commands when \qMRSTAT.mr_wr_busy\q is high. */

/***************  Bit definition for DDRCTRL_DERATEEN register  ***************/
#define DDRCTRL_DERATEEN_DERATE_ENABLE_Pos (0U)
#define DDRCTRL_DERATEEN_DERATE_ENABLE_Msk (0x1U << DDRCTRL_DERATEEN_DERATE_ENABLE_Pos) /*!< 0x00000001 */
#define DDRCTRL_DERATEEN_DERATE_ENABLE     DDRCTRL_DERATEEN_DERATE_ENABLE_Msk           /*!< Enables derating */
#define DDRCTRL_DERATEEN_DERATE_VALUE_Pos  (1U)
#define DDRCTRL_DERATEEN_DERATE_VALUE_Msk  (0x3U << DDRCTRL_DERATEEN_DERATE_VALUE_Pos)  /*!< 0x00000006 */
#define DDRCTRL_DERATEEN_DERATE_VALUE      DDRCTRL_DERATEEN_DERATE_VALUE_Msk            /*!< Derate value */
#define DDRCTRL_DERATEEN_DERATE_VALUE_0    (0x1U << DDRCTRL_DERATEEN_DERATE_VALUE_Pos)  /*!< 0x00000002 */
#define DDRCTRL_DERATEEN_DERATE_VALUE_1    (0x2U << DDRCTRL_DERATEEN_DERATE_VALUE_Pos)  /*!< 0x00000004 */
#define DDRCTRL_DERATEEN_DERATE_BYTE_Pos   (4U)
#define DDRCTRL_DERATEEN_DERATE_BYTE_Msk   (0xFU << DDRCTRL_DERATEEN_DERATE_BYTE_Pos)   /*!< 0x000000F0 */
#define DDRCTRL_DERATEEN_DERATE_BYTE       DDRCTRL_DERATEEN_DERATE_BYTE_Msk             /*!< Derate byte */
#define DDRCTRL_DERATEEN_DERATE_BYTE_0     (0x1U << DDRCTRL_DERATEEN_DERATE_BYTE_Pos)   /*!< 0x00000010 */
#define DDRCTRL_DERATEEN_DERATE_BYTE_1     (0x2U << DDRCTRL_DERATEEN_DERATE_BYTE_Pos)   /*!< 0x00000020 */
#define DDRCTRL_DERATEEN_DERATE_BYTE_2     (0x4U << DDRCTRL_DERATEEN_DERATE_BYTE_Pos)   /*!< 0x00000040 */
#define DDRCTRL_DERATEEN_DERATE_BYTE_3     (0x8U << DDRCTRL_DERATEEN_DERATE_BYTE_Pos)   /*!< 0x00000080 */

/**************  Bit definition for DDRCTRL_DERATEINT register  ***************/
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos (0U)
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Msk (0xFFFFFFFFU << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos) /*!< 0xFFFFFFFF */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL     DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Msk                  /*!< Interval between two MR4 reads, used to derate the timing parameters. */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_0   (0x1U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)        /*!< 0x00000001 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_1   (0x2U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)        /*!< 0x00000002 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_2   (0x4U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)        /*!< 0x00000004 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_3   (0x8U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)        /*!< 0x00000008 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_4   (0x10U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)       /*!< 0x00000010 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_5   (0x20U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)       /*!< 0x00000020 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_6   (0x40U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)       /*!< 0x00000040 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_7   (0x80U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)       /*!< 0x00000080 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_8   (0x100U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)      /*!< 0x00000100 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_9   (0x200U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)      /*!< 0x00000200 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_10  (0x400U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)      /*!< 0x00000400 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_11  (0x800U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)      /*!< 0x00000800 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_12  (0x1000U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)     /*!< 0x00001000 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_13  (0x2000U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)     /*!< 0x00002000 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_14  (0x4000U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)     /*!< 0x00004000 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_15  (0x8000U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)     /*!< 0x00008000 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_16  (0x10000U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)    /*!< 0x00010000 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_17  (0x20000U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)    /*!< 0x00020000 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_18  (0x40000U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)    /*!< 0x00040000 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_19  (0x80000U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)    /*!< 0x00080000 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_20  (0x100000U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)   /*!< 0x00100000 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_21  (0x200000U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)   /*!< 0x00200000 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_22  (0x400000U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)   /*!< 0x00400000 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_23  (0x800000U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)   /*!< 0x00800000 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_24  (0x1000000U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)  /*!< 0x01000000 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_25  (0x2000000U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)  /*!< 0x02000000 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_26  (0x4000000U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)  /*!< 0x04000000 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_27  (0x8000000U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos)  /*!< 0x08000000 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_28  (0x10000000U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos) /*!< 0x10000000 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_29  (0x20000000U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos) /*!< 0x20000000 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_30  (0x40000000U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos) /*!< 0x40000000 */
#define DDRCTRL_DERATEINT_MR4_READ_INTERVAL_31  (0x80000000U << DDRCTRL_DERATEINT_MR4_READ_INTERVAL_Pos) /*!< 0x80000000 */

/****************  Bit definition for DDRCTRL_PWRCTL register  ****************/
#define DDRCTRL_PWRCTL_SELFREF_EN_Pos              (0U)
#define DDRCTRL_PWRCTL_SELFREF_EN_Msk              (0x1U << DDRCTRL_PWRCTL_SELFREF_EN_Pos)              /*!< 0x00000001 */
#define DDRCTRL_PWRCTL_SELFREF_EN                  DDRCTRL_PWRCTL_SELFREF_EN_Msk                        /*!< If true then the DDRCTRL puts the SDRAM into Self Refresh after a programmable number of cycles "maximum idle clocks before Self Refresh (PWRTMG.selfref_to_x32)". This register bit may be re-programmed during the course of normal operation. */
#define DDRCTRL_PWRCTL_POWERDOWN_EN_Pos            (1U)
#define DDRCTRL_PWRCTL_POWERDOWN_EN_Msk            (0x1U << DDRCTRL_PWRCTL_POWERDOWN_EN_Pos)            /*!< 0x00000002 */
#define DDRCTRL_PWRCTL_POWERDOWN_EN                DDRCTRL_PWRCTL_POWERDOWN_EN_Msk                      /*!< If true then the DDRCTRL goes into power-down after a programmable number of cycles "maximum idle clocks before power down" (PWRTMG.powerdown_to_x32). */
#define DDRCTRL_PWRCTL_DEEPPOWERDOWN_EN_Pos        (2U)
#define DDRCTRL_PWRCTL_DEEPPOWERDOWN_EN_Msk        (0x1U << DDRCTRL_PWRCTL_DEEPPOWERDOWN_EN_Pos)        /*!< 0x00000004 */
#define DDRCTRL_PWRCTL_DEEPPOWERDOWN_EN            DDRCTRL_PWRCTL_DEEPPOWERDOWN_EN_Msk                  /*!< When this is 1, DDRCTRL puts the SDRAM into deep power-down mode when the transaction store is empty. */
#define DDRCTRL_PWRCTL_EN_DFI_DRAM_CLK_DISABLE_Pos (3U)
#define DDRCTRL_PWRCTL_EN_DFI_DRAM_CLK_DISABLE_Msk (0x1U << DDRCTRL_PWRCTL_EN_DFI_DRAM_CLK_DISABLE_Pos) /*!< 0x00000008 */
#define DDRCTRL_PWRCTL_EN_DFI_DRAM_CLK_DISABLE     DDRCTRL_PWRCTL_EN_DFI_DRAM_CLK_DISABLE_Msk           /*!< Enable the assertion of dfi_dram_clk_disable whenever a clock is not required by the SDRAM. */
#define DDRCTRL_PWRCTL_SELFREF_SW_Pos              (5U)
#define DDRCTRL_PWRCTL_SELFREF_SW_Msk              (0x1U << DDRCTRL_PWRCTL_SELFREF_SW_Pos)              /*!< 0x00000020 */
#define DDRCTRL_PWRCTL_SELFREF_SW                  DDRCTRL_PWRCTL_SELFREF_SW_Msk                        /*!< A value of 1 to this register causes system to move to Self Refresh state immediately, as long as it is not in INIT or DPD/MPSM operating_mode. This is referred to as Software Entry/Exit to Self Refresh. */
#define DDRCTRL_PWRCTL_DIS_CAM_DRAIN_SELFREF_Pos   (7U)
#define DDRCTRL_PWRCTL_DIS_CAM_DRAIN_SELFREF_Msk   (0x1U << DDRCTRL_PWRCTL_DIS_CAM_DRAIN_SELFREF_Pos)   /*!< 0x00000080 */
#define DDRCTRL_PWRCTL_DIS_CAM_DRAIN_SELFREF       DDRCTRL_PWRCTL_DIS_CAM_DRAIN_SELFREF_Msk             /*!< Indicates whether skipping CAM draining is allowed when entering Self-Refresh. */

/****************  Bit definition for DDRCTRL_PWRTMG register  ****************/
#define DDRCTRL_PWRTMG_POWERDOWN_TO_X32_Pos (0U)
#define DDRCTRL_PWRTMG_POWERDOWN_TO_X32_Msk (0x1FU << DDRCTRL_PWRTMG_POWERDOWN_TO_X32_Pos) /*!< 0x0000001F */
#define DDRCTRL_PWRTMG_POWERDOWN_TO_X32     DDRCTRL_PWRTMG_POWERDOWN_TO_X32_Msk            /*!< After this many clocks of the DDRC command channel being idle the DDRCTRL automatically puts the SDRAM into power-down. The DDRC command channel is considered idle when there are no HIF commands outstanding. This must be enabled in the PWRCTL.powerdown_en. */
#define DDRCTRL_PWRTMG_POWERDOWN_TO_X32_0   (0x1U << DDRCTRL_PWRTMG_POWERDOWN_TO_X32_Pos)  /*!< 0x00000001 */
#define DDRCTRL_PWRTMG_POWERDOWN_TO_X32_1   (0x2U << DDRCTRL_PWRTMG_POWERDOWN_TO_X32_Pos)  /*!< 0x00000002 */
#define DDRCTRL_PWRTMG_POWERDOWN_TO_X32_2   (0x4U << DDRCTRL_PWRTMG_POWERDOWN_TO_X32_Pos)  /*!< 0x00000004 */
#define DDRCTRL_PWRTMG_POWERDOWN_TO_X32_3   (0x8U << DDRCTRL_PWRTMG_POWERDOWN_TO_X32_Pos)  /*!< 0x00000008 */
#define DDRCTRL_PWRTMG_POWERDOWN_TO_X32_4   (0x10U << DDRCTRL_PWRTMG_POWERDOWN_TO_X32_Pos) /*!< 0x00000010 */
#define DDRCTRL_PWRTMG_T_DPD_X4096_Pos      (8U)
#define DDRCTRL_PWRTMG_T_DPD_X4096_Msk      (0xFFU << DDRCTRL_PWRTMG_T_DPD_X4096_Pos)      /*!< 0x0000FF00 */
#define DDRCTRL_PWRTMG_T_DPD_X4096          DDRCTRL_PWRTMG_T_DPD_X4096_Msk                 /*!< Minimum deep power-down time. */
#define DDRCTRL_PWRTMG_T_DPD_X4096_0        (0x1U << DDRCTRL_PWRTMG_T_DPD_X4096_Pos)       /*!< 0x00000100 */
#define DDRCTRL_PWRTMG_T_DPD_X4096_1        (0x2U << DDRCTRL_PWRTMG_T_DPD_X4096_Pos)       /*!< 0x00000200 */
#define DDRCTRL_PWRTMG_T_DPD_X4096_2        (0x4U << DDRCTRL_PWRTMG_T_DPD_X4096_Pos)       /*!< 0x00000400 */
#define DDRCTRL_PWRTMG_T_DPD_X4096_3        (0x8U << DDRCTRL_PWRTMG_T_DPD_X4096_Pos)       /*!< 0x00000800 */
#define DDRCTRL_PWRTMG_T_DPD_X4096_4        (0x10U << DDRCTRL_PWRTMG_T_DPD_X4096_Pos)      /*!< 0x00001000 */
#define DDRCTRL_PWRTMG_T_DPD_X4096_5        (0x20U << DDRCTRL_PWRTMG_T_DPD_X4096_Pos)      /*!< 0x00002000 */
#define DDRCTRL_PWRTMG_T_DPD_X4096_6        (0x40U << DDRCTRL_PWRTMG_T_DPD_X4096_Pos)      /*!< 0x00004000 */
#define DDRCTRL_PWRTMG_T_DPD_X4096_7        (0x80U << DDRCTRL_PWRTMG_T_DPD_X4096_Pos)      /*!< 0x00008000 */
#define DDRCTRL_PWRTMG_SELFREF_TO_X32_Pos   (16U)
#define DDRCTRL_PWRTMG_SELFREF_TO_X32_Msk   (0xFFU << DDRCTRL_PWRTMG_SELFREF_TO_X32_Pos)   /*!< 0x00FF0000 */
#define DDRCTRL_PWRTMG_SELFREF_TO_X32       DDRCTRL_PWRTMG_SELFREF_TO_X32_Msk              /*!< After this many clocks of the DDRC command channel being idle the DDRCTRL automatically puts the SDRAM into Self Refresh. The DDRC command channel is considered idle when there are no HIF commands outstanding. This must be enabled in the PWRCTL.selfref_en. */
#define DDRCTRL_PWRTMG_SELFREF_TO_X32_0     (0x1U << DDRCTRL_PWRTMG_SELFREF_TO_X32_Pos)    /*!< 0x00010000 */
#define DDRCTRL_PWRTMG_SELFREF_TO_X32_1     (0x2U << DDRCTRL_PWRTMG_SELFREF_TO_X32_Pos)    /*!< 0x00020000 */
#define DDRCTRL_PWRTMG_SELFREF_TO_X32_2     (0x4U << DDRCTRL_PWRTMG_SELFREF_TO_X32_Pos)    /*!< 0x00040000 */
#define DDRCTRL_PWRTMG_SELFREF_TO_X32_3     (0x8U << DDRCTRL_PWRTMG_SELFREF_TO_X32_Pos)    /*!< 0x00080000 */
#define DDRCTRL_PWRTMG_SELFREF_TO_X32_4     (0x10U << DDRCTRL_PWRTMG_SELFREF_TO_X32_Pos)   /*!< 0x00100000 */
#define DDRCTRL_PWRTMG_SELFREF_TO_X32_5     (0x20U << DDRCTRL_PWRTMG_SELFREF_TO_X32_Pos)   /*!< 0x00200000 */
#define DDRCTRL_PWRTMG_SELFREF_TO_X32_6     (0x40U << DDRCTRL_PWRTMG_SELFREF_TO_X32_Pos)   /*!< 0x00400000 */
#define DDRCTRL_PWRTMG_SELFREF_TO_X32_7     (0x80U << DDRCTRL_PWRTMG_SELFREF_TO_X32_Pos)   /*!< 0x00800000 */

/***************  Bit definition for DDRCTRL_HWLPCTL register  ****************/
#define DDRCTRL_HWLPCTL_HW_LP_EN_Pos           (0U)
#define DDRCTRL_HWLPCTL_HW_LP_EN_Msk           (0x1U << DDRCTRL_HWLPCTL_HW_LP_EN_Pos)           /*!< 0x00000001 */
#define DDRCTRL_HWLPCTL_HW_LP_EN               DDRCTRL_HWLPCTL_HW_LP_EN_Msk                     /*!< Enable for hardware low power interface. */
#define DDRCTRL_HWLPCTL_HW_LP_EXIT_IDLE_EN_Pos (1U)
#define DDRCTRL_HWLPCTL_HW_LP_EXIT_IDLE_EN_Msk (0x1U << DDRCTRL_HWLPCTL_HW_LP_EXIT_IDLE_EN_Pos) /*!< 0x00000002 */
#define DDRCTRL_HWLPCTL_HW_LP_EXIT_IDLE_EN     DDRCTRL_HWLPCTL_HW_LP_EXIT_IDLE_EN_Msk           /*!< When this bit is programmed to 1 the cactive_in_ddrc pin of the DDRC can be used to exit from the automatic clock stop, automatic power down or automatic self-refresh modes. Note, it does not cause exit of Self-Refresh that is caused by Hardware Low power interface and/or software (PWRCTL.selfref_sw). */
#define DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_Pos     (16U)
#define DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_Msk     (0xFFFU << DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_Pos)   /*!< 0x0FFF0000 */
#define DDRCTRL_HWLPCTL_HW_LP_IDLE_X32         DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_Msk               /*!< Hardware idle period. The cactive_ddrc output is driven low if the DDRC command channel is idle for hw_lp_idle * 32 cycles if not in INIT or DPD/MPSM operating_mode. The DDRC command channel is considered idle when there are no HIF commands outstanding. The hardware idle function is disabled when hw_lp_idle_x32=0. */
#define DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_0       (0x1U << DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_Pos)     /*!< 0x00010000 */
#define DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_1       (0x2U << DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_Pos)     /*!< 0x00020000 */
#define DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_2       (0x4U << DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_Pos)     /*!< 0x00040000 */
#define DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_3       (0x8U << DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_Pos)     /*!< 0x00080000 */
#define DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_4       (0x10U << DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_Pos)    /*!< 0x00100000 */
#define DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_5       (0x20U << DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_Pos)    /*!< 0x00200000 */
#define DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_6       (0x40U << DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_Pos)    /*!< 0x00400000 */
#define DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_7       (0x80U << DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_Pos)    /*!< 0x00800000 */
#define DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_8       (0x100U << DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_Pos)   /*!< 0x01000000 */
#define DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_9       (0x200U << DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_Pos)   /*!< 0x02000000 */
#define DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_10      (0x400U << DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_Pos)   /*!< 0x04000000 */
#define DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_11      (0x800U << DDRCTRL_HWLPCTL_HW_LP_IDLE_X32_Pos)   /*!< 0x08000000 */

/***************  Bit definition for DDRCTRL_RFSHCTL0 register  ***************/
#define DDRCTRL_RFSHCTL0_PER_BANK_REFRESH_Pos (2U)
#define DDRCTRL_RFSHCTL0_PER_BANK_REFRESH_Msk (0x1U << DDRCTRL_RFSHCTL0_PER_BANK_REFRESH_Pos) /*!< 0x00000004 */
#define DDRCTRL_RFSHCTL0_PER_BANK_REFRESH     DDRCTRL_RFSHCTL0_PER_BANK_REFRESH_Msk           /*!< - 1 - Per bank refresh; */
#define DDRCTRL_RFSHCTL0_REFRESH_BURST_Pos    (4U)
#define DDRCTRL_RFSHCTL0_REFRESH_BURST_Msk    (0x1FU << DDRCTRL_RFSHCTL0_REFRESH_BURST_Pos)   /*!< 0x000001F0 */
#define DDRCTRL_RFSHCTL0_REFRESH_BURST        DDRCTRL_RFSHCTL0_REFRESH_BURST_Msk              /*!< The programmed value + 1 is the number of refresh timeouts that is allowed to accumulate before traffic is blocked and the refreshes are forced to execute. Closing pages to perform a refresh is a one-time penalty that must be paid for each group of refreshes. Therefore, performing refreshes in a burst reduces the per-refresh penalty of these page closings. Higher numbers for RFSHCTL.refresh_burst slightly increases utilization; lower numbers decreases the worst-case latency associated with refreshes. */
#define DDRCTRL_RFSHCTL0_REFRESH_BURST_0      (0x1U << DDRCTRL_RFSHCTL0_REFRESH_BURST_Pos)    /*!< 0x00000010 */
#define DDRCTRL_RFSHCTL0_REFRESH_BURST_1      (0x2U << DDRCTRL_RFSHCTL0_REFRESH_BURST_Pos)    /*!< 0x00000020 */
#define DDRCTRL_RFSHCTL0_REFRESH_BURST_2      (0x4U << DDRCTRL_RFSHCTL0_REFRESH_BURST_Pos)    /*!< 0x00000040 */
#define DDRCTRL_RFSHCTL0_REFRESH_BURST_3      (0x8U << DDRCTRL_RFSHCTL0_REFRESH_BURST_Pos)    /*!< 0x00000080 */
#define DDRCTRL_RFSHCTL0_REFRESH_BURST_4      (0x10U << DDRCTRL_RFSHCTL0_REFRESH_BURST_Pos)   /*!< 0x00000100 */
#define DDRCTRL_RFSHCTL0_REFRESH_TO_X32_Pos   (12U)
#define DDRCTRL_RFSHCTL0_REFRESH_TO_X32_Msk   (0x1FU << DDRCTRL_RFSHCTL0_REFRESH_TO_X32_Pos)  /*!< 0x0001F000 */
#define DDRCTRL_RFSHCTL0_REFRESH_TO_X32       DDRCTRL_RFSHCTL0_REFRESH_TO_X32_Msk             /*!< If the refresh timer (tRFCnom, also known as tREFI) has expired at least once, but it has not expired (RFSHCTL0.refresh_burst+1) times yet, then a speculative refresh may be performed. A speculative refresh is a refresh performed at a time when refresh would be useful, but before it is absolutely required. When the SDRAM bus is idle for a period of time determined by this RFSHCTL0.refresh_to_x32 and the refresh timer has expired at least once since the last refresh, then a speculative refresh is performed. Speculative refreshes continues successively until there are no refreshes pending or until new reads or writes are issued to the DDRCTRL. */
#define DDRCTRL_RFSHCTL0_REFRESH_TO_X32_0     (0x1U << DDRCTRL_RFSHCTL0_REFRESH_TO_X32_Pos)   /*!< 0x00001000 */
#define DDRCTRL_RFSHCTL0_REFRESH_TO_X32_1     (0x2U << DDRCTRL_RFSHCTL0_REFRESH_TO_X32_Pos)   /*!< 0x00002000 */
#define DDRCTRL_RFSHCTL0_REFRESH_TO_X32_2     (0x4U << DDRCTRL_RFSHCTL0_REFRESH_TO_X32_Pos)   /*!< 0x00004000 */
#define DDRCTRL_RFSHCTL0_REFRESH_TO_X32_3     (0x8U << DDRCTRL_RFSHCTL0_REFRESH_TO_X32_Pos)   /*!< 0x00008000 */
#define DDRCTRL_RFSHCTL0_REFRESH_TO_X32_4     (0x10U << DDRCTRL_RFSHCTL0_REFRESH_TO_X32_Pos)  /*!< 0x00010000 */
#define DDRCTRL_RFSHCTL0_REFRESH_MARGIN_Pos   (20U)
#define DDRCTRL_RFSHCTL0_REFRESH_MARGIN_Msk   (0xFU << DDRCTRL_RFSHCTL0_REFRESH_MARGIN_Pos)   /*!< 0x00F00000 */
#define DDRCTRL_RFSHCTL0_REFRESH_MARGIN       DDRCTRL_RFSHCTL0_REFRESH_MARGIN_Msk             /*!< Threshold value in number of DFI clock cycles before the critical refresh or page timer expires. A critical refresh is to be issued before this threshold is reached. It is recommended that this not be changed from the default value, currently shown as 0x2. It must always be less than internally used t_rfc_nom/32. Note that internally used t_rfc_nom is equal to RFSHTMG.t_rfc_nom_x1_x32 * 32 if RFSHTMG.t_rfc_nom_x1_sel=0. If RFSHTMG.t_rfc_nom_x1_sel=1 (for LPDDR2/LPDDR3/LPDDR4 per-bank refresh only), internally used t_rfc_nom is equal to RFSHTMG.t_rfc_nom_x1_x32. Note that, in LPDDR2/LPDDR3/LPDDR4, internally used t_rfc_nom may be divided by four if derating is enabled (DERATEEN.derate_enable=1). */
#define DDRCTRL_RFSHCTL0_REFRESH_MARGIN_0     (0x1U << DDRCTRL_RFSHCTL0_REFRESH_MARGIN_Pos)   /*!< 0x00100000 */
#define DDRCTRL_RFSHCTL0_REFRESH_MARGIN_1     (0x2U << DDRCTRL_RFSHCTL0_REFRESH_MARGIN_Pos)   /*!< 0x00200000 */
#define DDRCTRL_RFSHCTL0_REFRESH_MARGIN_2     (0x4U << DDRCTRL_RFSHCTL0_REFRESH_MARGIN_Pos)   /*!< 0x00400000 */
#define DDRCTRL_RFSHCTL0_REFRESH_MARGIN_3     (0x8U << DDRCTRL_RFSHCTL0_REFRESH_MARGIN_Pos)   /*!< 0x00800000 */

/***************  Bit definition for DDRCTRL_RFSHCTL3 register  ***************/
#define DDRCTRL_RFSHCTL3_DIS_AUTO_REFRESH_Pos     (0U)
#define DDRCTRL_RFSHCTL3_DIS_AUTO_REFRESH_Msk     (0x1U << DDRCTRL_RFSHCTL3_DIS_AUTO_REFRESH_Pos)     /*!< 0x00000001 */
#define DDRCTRL_RFSHCTL3_DIS_AUTO_REFRESH         DDRCTRL_RFSHCTL3_DIS_AUTO_REFRESH_Msk               /*!< When \q1\q, disable auto-refresh generated by the DDRCTRL. When auto-refresh is disabled, the SoC core must generate refreshes using the registers DBGCMD.rankn_refresh. */
#define DDRCTRL_RFSHCTL3_REFRESH_UPDATE_LEVEL_Pos (1U)
#define DDRCTRL_RFSHCTL3_REFRESH_UPDATE_LEVEL_Msk (0x1U << DDRCTRL_RFSHCTL3_REFRESH_UPDATE_LEVEL_Pos) /*!< 0x00000002 */
#define DDRCTRL_RFSHCTL3_REFRESH_UPDATE_LEVEL     DDRCTRL_RFSHCTL3_REFRESH_UPDATE_LEVEL_Msk           /*!< Toggles this signal (either from 0 to 1 or from 1 to 0) to indicate that the refresh register(s) have been updated. */

/***************  Bit definition for DDRCTRL_RFSHTMG register  ****************/
#define DDRCTRL_RFSHTMG_T_RFC_MIN_Pos        (0U)
#define DDRCTRL_RFSHTMG_T_RFC_MIN_Msk        (0x3FFU << DDRCTRL_RFSHTMG_T_RFC_MIN_Pos)        /*!< 0x000003FF */
#define DDRCTRL_RFSHTMG_T_RFC_MIN            DDRCTRL_RFSHTMG_T_RFC_MIN_Msk                    /*!< tRFC (min): Minimum time from refresh to refresh or activate. */
#define DDRCTRL_RFSHTMG_T_RFC_MIN_0          (0x1U << DDRCTRL_RFSHTMG_T_RFC_MIN_Pos)          /*!< 0x00000001 */
#define DDRCTRL_RFSHTMG_T_RFC_MIN_1          (0x2U << DDRCTRL_RFSHTMG_T_RFC_MIN_Pos)          /*!< 0x00000002 */
#define DDRCTRL_RFSHTMG_T_RFC_MIN_2          (0x4U << DDRCTRL_RFSHTMG_T_RFC_MIN_Pos)          /*!< 0x00000004 */
#define DDRCTRL_RFSHTMG_T_RFC_MIN_3          (0x8U << DDRCTRL_RFSHTMG_T_RFC_MIN_Pos)          /*!< 0x00000008 */
#define DDRCTRL_RFSHTMG_T_RFC_MIN_4          (0x10U << DDRCTRL_RFSHTMG_T_RFC_MIN_Pos)         /*!< 0x00000010 */
#define DDRCTRL_RFSHTMG_T_RFC_MIN_5          (0x20U << DDRCTRL_RFSHTMG_T_RFC_MIN_Pos)         /*!< 0x00000020 */
#define DDRCTRL_RFSHTMG_T_RFC_MIN_6          (0x40U << DDRCTRL_RFSHTMG_T_RFC_MIN_Pos)         /*!< 0x00000040 */
#define DDRCTRL_RFSHTMG_T_RFC_MIN_7          (0x80U << DDRCTRL_RFSHTMG_T_RFC_MIN_Pos)         /*!< 0x00000080 */
#define DDRCTRL_RFSHTMG_T_RFC_MIN_8          (0x100U << DDRCTRL_RFSHTMG_T_RFC_MIN_Pos)        /*!< 0x00000100 */
#define DDRCTRL_RFSHTMG_T_RFC_MIN_9          (0x200U << DDRCTRL_RFSHTMG_T_RFC_MIN_Pos)        /*!< 0x00000200 */
#define DDRCTRL_RFSHTMG_LPDDR3_TREFBW_EN_Pos (15U)
#define DDRCTRL_RFSHTMG_LPDDR3_TREFBW_EN_Msk (0x1U << DDRCTRL_RFSHTMG_LPDDR3_TREFBW_EN_Pos)   /*!< 0x00008000 */
#define DDRCTRL_RFSHTMG_LPDDR3_TREFBW_EN     DDRCTRL_RFSHTMG_LPDDR3_TREFBW_EN_Msk             /*!< Used only when LPDDR3 memory type is connected. Should only be changed when DDRCTRL is in reset. Specifies whether to use the tREFBW parameter (required by some LPDDR3 devices which comply with earlier versions of the LPDDR3 JEDEC specification) or not: */
#define DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_Pos (16U)
#define DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_Msk (0xFFFU << DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_Pos) /*!< 0x0FFF0000 */
#define DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32     DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_Msk             /*!< tREFI: Average time interval between refreshes per rank (Specification: 7.8us for DDR2, DDR3 and DDR4. See JEDEC specification for mDDR, LPDDR2, LPDDR3 and LPDDR4). */
#define DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_0   (0x1U << DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_Pos)   /*!< 0x00010000 */
#define DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_1   (0x2U << DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_Pos)   /*!< 0x00020000 */
#define DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_2   (0x4U << DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_Pos)   /*!< 0x00040000 */
#define DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_3   (0x8U << DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_Pos)   /*!< 0x00080000 */
#define DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_4   (0x10U << DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_Pos)  /*!< 0x00100000 */
#define DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_5   (0x20U << DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_Pos)  /*!< 0x00200000 */
#define DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_6   (0x40U << DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_Pos)  /*!< 0x00400000 */
#define DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_7   (0x80U << DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_Pos)  /*!< 0x00800000 */
#define DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_8   (0x100U << DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_Pos) /*!< 0x01000000 */
#define DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_9   (0x200U << DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_Pos) /*!< 0x02000000 */
#define DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_10  (0x400U << DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_Pos) /*!< 0x04000000 */
#define DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_11  (0x800U << DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_Pos) /*!< 0x08000000 */
#define DDRCTRL_RFSHTMG_T_RFC_NOM_X1_SEL_Pos (31U)
#define DDRCTRL_RFSHTMG_T_RFC_NOM_X1_SEL_Msk (0x1U << DDRCTRL_RFSHTMG_T_RFC_NOM_X1_SEL_Pos)  /*!< 0x80000000 */
#define DDRCTRL_RFSHTMG_T_RFC_NOM_X1_SEL     DDRCTRL_RFSHTMG_T_RFC_NOM_X1_SEL_Msk         /*!< Specifies whether the t_rfc_nom_x1_x32 register value is x1 or x32. */

/**************  Bit definition for DDRCTRL_CRCPARCTL0 register  **************/
#define DDRCTRL_CRCPARCTL0_DFI_ALERT_ERR_INT_EN_Pos  (0U)
#define DDRCTRL_CRCPARCTL0_DFI_ALERT_ERR_INT_EN_Msk  (0x1U << DDRCTRL_CRCPARCTL0_DFI_ALERT_ERR_INT_EN_Pos)  /*!< 0x00000001 */
#define DDRCTRL_CRCPARCTL0_DFI_ALERT_ERR_INT_EN      DDRCTRL_CRCPARCTL0_DFI_ALERT_ERR_INT_EN_Msk            /*!< Interrupt enable bit for DFI alert error. If this bit is set, any parity/CRC error detected on the dfi_alert_n input results in an interrupt being set on CRCPARSTAT.dfi_alert_err_int. */
#define DDRCTRL_CRCPARCTL0_DFI_ALERT_ERR_INT_CLR_Pos (1U)
#define DDRCTRL_CRCPARCTL0_DFI_ALERT_ERR_INT_CLR_Msk (0x1U << DDRCTRL_CRCPARCTL0_DFI_ALERT_ERR_INT_CLR_Pos) /*!< 0x00000002 */
#define DDRCTRL_CRCPARCTL0_DFI_ALERT_ERR_INT_CLR     DDRCTRL_CRCPARCTL0_DFI_ALERT_ERR_INT_CLR_Msk           /*!< Interrupt clear bit for DFI alert error. If this bit is set, the alert error interrupt on CRCPARSTAT.dfi_alert_err_int is cleared. When the clear operation is complete, the DDRCTRL automatically clears this bit. */
#define DDRCTRL_CRCPARCTL0_DFI_ALERT_ERR_CNT_CLR_Pos (2U)
#define DDRCTRL_CRCPARCTL0_DFI_ALERT_ERR_CNT_CLR_Msk (0x1U << DDRCTRL_CRCPARCTL0_DFI_ALERT_ERR_CNT_CLR_Pos) /*!< 0x00000004 */
#define DDRCTRL_CRCPARCTL0_DFI_ALERT_ERR_CNT_CLR     DDRCTRL_CRCPARCTL0_DFI_ALERT_ERR_CNT_CLR_Msk           /*!< DFI alert error count clear. Clear bit for DFI alert error counter. Asserting this bit, clears the DFI alert error counter, CRCPARSTAT.dfi_alert_err_cnt. When the clear operation is complete, the DDRCTRL automatically clears this bit. */

/**************  Bit definition for DDRCTRL_CRCPARSTAT register  **************/
#define DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_Pos (0U)
#define DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_Msk (0xFFFFU << DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_Pos) /*!< 0x0000FFFF */
#define DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT     DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_Msk              /*!< DFI alert error count. */
#define DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_0   (0x1U << DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_Pos)    /*!< 0x00000001 */
#define DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_1   (0x2U << DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_Pos)    /*!< 0x00000002 */
#define DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_2   (0x4U << DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_Pos)    /*!< 0x00000004 */
#define DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_3   (0x8U << DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_Pos)    /*!< 0x00000008 */
#define DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_4   (0x10U << DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_Pos)   /*!< 0x00000010 */
#define DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_5   (0x20U << DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_Pos)   /*!< 0x00000020 */
#define DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_6   (0x40U << DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_Pos)   /*!< 0x00000040 */
#define DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_7   (0x80U << DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_Pos)   /*!< 0x00000080 */
#define DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_8   (0x100U << DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_Pos)  /*!< 0x00000100 */
#define DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_9   (0x200U << DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_Pos)  /*!< 0x00000200 */
#define DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_10  (0x400U << DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_Pos)  /*!< 0x00000400 */
#define DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_11  (0x800U << DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_Pos)  /*!< 0x00000800 */
#define DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_12  (0x1000U << DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_Pos) /*!< 0x00001000 */
#define DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_13  (0x2000U << DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_Pos) /*!< 0x00002000 */
#define DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_14  (0x4000U << DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_Pos) /*!< 0x00004000 */
#define DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_15  (0x8000U << DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_CNT_Pos) /*!< 0x00008000 */
#define DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_INT_Pos (16U)
#define DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_INT_Msk (0x1U << DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_INT_Pos)    /*!< 0x00010000 */
#define DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_INT     DDRCTRL_CRCPARSTAT_DFI_ALERT_ERR_INT_Msk              /*!< DFI alert error interrupt. */

/****************  Bit definition for DDRCTRL_INIT0 register  *****************/
#define DDRCTRL_INIT0_PRE_CKE_X1024_Pos  (0U)
#define DDRCTRL_INIT0_PRE_CKE_X1024_Msk  (0xFFFU << DDRCTRL_INIT0_PRE_CKE_X1024_Pos)  /*!< 0x00000FFF */
#define DDRCTRL_INIT0_PRE_CKE_X1024      DDRCTRL_INIT0_PRE_CKE_X1024_Msk              /*!< Cycles to wait after reset before driving CKE high to start the SDRAM initialization sequence. */
#define DDRCTRL_INIT0_PRE_CKE_X1024_0    (0x1U << DDRCTRL_INIT0_PRE_CKE_X1024_Pos)    /*!< 0x00000001 */
#define DDRCTRL_INIT0_PRE_CKE_X1024_1    (0x2U << DDRCTRL_INIT0_PRE_CKE_X1024_Pos)    /*!< 0x00000002 */
#define DDRCTRL_INIT0_PRE_CKE_X1024_2    (0x4U << DDRCTRL_INIT0_PRE_CKE_X1024_Pos)    /*!< 0x00000004 */
#define DDRCTRL_INIT0_PRE_CKE_X1024_3    (0x8U << DDRCTRL_INIT0_PRE_CKE_X1024_Pos)    /*!< 0x00000008 */
#define DDRCTRL_INIT0_PRE_CKE_X1024_4    (0x10U << DDRCTRL_INIT0_PRE_CKE_X1024_Pos)   /*!< 0x00000010 */
#define DDRCTRL_INIT0_PRE_CKE_X1024_5    (0x20U << DDRCTRL_INIT0_PRE_CKE_X1024_Pos)   /*!< 0x00000020 */
#define DDRCTRL_INIT0_PRE_CKE_X1024_6    (0x40U << DDRCTRL_INIT0_PRE_CKE_X1024_Pos)   /*!< 0x00000040 */
#define DDRCTRL_INIT0_PRE_CKE_X1024_7    (0x80U << DDRCTRL_INIT0_PRE_CKE_X1024_Pos)   /*!< 0x00000080 */
#define DDRCTRL_INIT0_PRE_CKE_X1024_8    (0x100U << DDRCTRL_INIT0_PRE_CKE_X1024_Pos)  /*!< 0x00000100 */
#define DDRCTRL_INIT0_PRE_CKE_X1024_9    (0x200U << DDRCTRL_INIT0_PRE_CKE_X1024_Pos)  /*!< 0x00000200 */
#define DDRCTRL_INIT0_PRE_CKE_X1024_10   (0x400U << DDRCTRL_INIT0_PRE_CKE_X1024_Pos)  /*!< 0x00000400 */
#define DDRCTRL_INIT0_PRE_CKE_X1024_11   (0x800U << DDRCTRL_INIT0_PRE_CKE_X1024_Pos)  /*!< 0x00000800 */
#define DDRCTRL_INIT0_POST_CKE_X1024_Pos (16U)
#define DDRCTRL_INIT0_POST_CKE_X1024_Msk (0x3FFU << DDRCTRL_INIT0_POST_CKE_X1024_Pos) /*!< 0x03FF0000 */
#define DDRCTRL_INIT0_POST_CKE_X1024     DDRCTRL_INIT0_POST_CKE_X1024_Msk             /*!< Cycles to wait after driving CKE high to start the SDRAM initialization sequence. */
#define DDRCTRL_INIT0_POST_CKE_X1024_0   (0x1U << DDRCTRL_INIT0_POST_CKE_X1024_Pos)   /*!< 0x00010000 */
#define DDRCTRL_INIT0_POST_CKE_X1024_1   (0x2U << DDRCTRL_INIT0_POST_CKE_X1024_Pos)   /*!< 0x00020000 */
#define DDRCTRL_INIT0_POST_CKE_X1024_2   (0x4U << DDRCTRL_INIT0_POST_CKE_X1024_Pos)   /*!< 0x00040000 */
#define DDRCTRL_INIT0_POST_CKE_X1024_3   (0x8U << DDRCTRL_INIT0_POST_CKE_X1024_Pos)   /*!< 0x00080000 */
#define DDRCTRL_INIT0_POST_CKE_X1024_4   (0x10U << DDRCTRL_INIT0_POST_CKE_X1024_Pos)  /*!< 0x00100000 */
#define DDRCTRL_INIT0_POST_CKE_X1024_5   (0x20U << DDRCTRL_INIT0_POST_CKE_X1024_Pos)  /*!< 0x00200000 */
#define DDRCTRL_INIT0_POST_CKE_X1024_6   (0x40U << DDRCTRL_INIT0_POST_CKE_X1024_Pos)  /*!< 0x00400000 */
#define DDRCTRL_INIT0_POST_CKE_X1024_7   (0x80U << DDRCTRL_INIT0_POST_CKE_X1024_Pos)  /*!< 0x00800000 */
#define DDRCTRL_INIT0_POST_CKE_X1024_8   (0x100U << DDRCTRL_INIT0_POST_CKE_X1024_Pos) /*!< 0x01000000 */
#define DDRCTRL_INIT0_POST_CKE_X1024_9   (0x200U << DDRCTRL_INIT0_POST_CKE_X1024_Pos) /*!< 0x02000000 */
#define DDRCTRL_INIT0_SKIP_DRAM_INIT_Pos (30U)
#define DDRCTRL_INIT0_SKIP_DRAM_INIT_Msk (0x3U << DDRCTRL_INIT0_SKIP_DRAM_INIT_Pos)   /*!< 0xC0000000 */
#define DDRCTRL_INIT0_SKIP_DRAM_INIT     DDRCTRL_INIT0_SKIP_DRAM_INIT_Msk             /*!< If lower bit is enabled the SDRAM initialization routine is skipped. The upper bit decides what state the controller starts up in when reset is removed */
#define DDRCTRL_INIT0_SKIP_DRAM_INIT_0   (0x1U << DDRCTRL_INIT0_SKIP_DRAM_INIT_Pos)   /*!< 0x40000000 */
#define DDRCTRL_INIT0_SKIP_DRAM_INIT_1   (0x2U << DDRCTRL_INIT0_SKIP_DRAM_INIT_Pos)   /*!< 0x80000000 */

/****************  Bit definition for DDRCTRL_INIT1 register  *****************/
#define DDRCTRL_INIT1_PRE_OCD_X32_Pos     (0U)
#define DDRCTRL_INIT1_PRE_OCD_X32_Msk     (0xFU << DDRCTRL_INIT1_PRE_OCD_X32_Pos)       /*!< 0x0000000F */
#define DDRCTRL_INIT1_PRE_OCD_X32         DDRCTRL_INIT1_PRE_OCD_X32_Msk                 /*!< Wait period before driving the OCD complete command to SDRAM. */
#define DDRCTRL_INIT1_PRE_OCD_X32_0       (0x1U << DDRCTRL_INIT1_PRE_OCD_X32_Pos)       /*!< 0x00000001 */
#define DDRCTRL_INIT1_PRE_OCD_X32_1       (0x2U << DDRCTRL_INIT1_PRE_OCD_X32_Pos)       /*!< 0x00000002 */
#define DDRCTRL_INIT1_PRE_OCD_X32_2       (0x4U << DDRCTRL_INIT1_PRE_OCD_X32_Pos)       /*!< 0x00000004 */
#define DDRCTRL_INIT1_PRE_OCD_X32_3       (0x8U << DDRCTRL_INIT1_PRE_OCD_X32_Pos)       /*!< 0x00000008 */
#define DDRCTRL_INIT1_DRAM_RSTN_X1024_Pos (16U)
#define DDRCTRL_INIT1_DRAM_RSTN_X1024_Msk (0x1FFU << DDRCTRL_INIT1_DRAM_RSTN_X1024_Pos) /*!< 0x01FF0000 */
#define DDRCTRL_INIT1_DRAM_RSTN_X1024     DDRCTRL_INIT1_DRAM_RSTN_X1024_Msk             /*!< Number of cycles to assert SDRAM reset signal during init sequence. */
#define DDRCTRL_INIT1_DRAM_RSTN_X1024_0   (0x1U << DDRCTRL_INIT1_DRAM_RSTN_X1024_Pos)   /*!< 0x00010000 */
#define DDRCTRL_INIT1_DRAM_RSTN_X1024_1   (0x2U << DDRCTRL_INIT1_DRAM_RSTN_X1024_Pos)   /*!< 0x00020000 */
#define DDRCTRL_INIT1_DRAM_RSTN_X1024_2   (0x4U << DDRCTRL_INIT1_DRAM_RSTN_X1024_Pos)   /*!< 0x00040000 */
#define DDRCTRL_INIT1_DRAM_RSTN_X1024_3   (0x8U << DDRCTRL_INIT1_DRAM_RSTN_X1024_Pos)   /*!< 0x00080000 */
#define DDRCTRL_INIT1_DRAM_RSTN_X1024_4   (0x10U << DDRCTRL_INIT1_DRAM_RSTN_X1024_Pos)  /*!< 0x00100000 */
#define DDRCTRL_INIT1_DRAM_RSTN_X1024_5   (0x20U << DDRCTRL_INIT1_DRAM_RSTN_X1024_Pos)  /*!< 0x00200000 */
#define DDRCTRL_INIT1_DRAM_RSTN_X1024_6   (0x40U << DDRCTRL_INIT1_DRAM_RSTN_X1024_Pos)  /*!< 0x00400000 */
#define DDRCTRL_INIT1_DRAM_RSTN_X1024_7   (0x80U << DDRCTRL_INIT1_DRAM_RSTN_X1024_Pos)  /*!< 0x00800000 */
#define DDRCTRL_INIT1_DRAM_RSTN_X1024_8   (0x100U << DDRCTRL_INIT1_DRAM_RSTN_X1024_Pos) /*!< 0x01000000 */

/****************  Bit definition for DDRCTRL_INIT2 register  *****************/
#define DDRCTRL_INIT2_MIN_STABLE_CLOCK_X1_Pos  (0U)
#define DDRCTRL_INIT2_MIN_STABLE_CLOCK_X1_Msk  (0xFU << DDRCTRL_INIT2_MIN_STABLE_CLOCK_X1_Pos)   /*!< 0x0000000F */
#define DDRCTRL_INIT2_MIN_STABLE_CLOCK_X1      DDRCTRL_INIT2_MIN_STABLE_CLOCK_X1_Msk             /*!< Time to wait after the first CKE high, tINIT2. Present only in designs configured to support LPDDR2/LPDDR3. */
#define DDRCTRL_INIT2_MIN_STABLE_CLOCK_X1_0    (0x1U << DDRCTRL_INIT2_MIN_STABLE_CLOCK_X1_Pos)   /*!< 0x00000001 */
#define DDRCTRL_INIT2_MIN_STABLE_CLOCK_X1_1    (0x2U << DDRCTRL_INIT2_MIN_STABLE_CLOCK_X1_Pos)   /*!< 0x00000002 */
#define DDRCTRL_INIT2_MIN_STABLE_CLOCK_X1_2    (0x4U << DDRCTRL_INIT2_MIN_STABLE_CLOCK_X1_Pos)   /*!< 0x00000004 */
#define DDRCTRL_INIT2_MIN_STABLE_CLOCK_X1_3    (0x8U << DDRCTRL_INIT2_MIN_STABLE_CLOCK_X1_Pos)   /*!< 0x00000008 */
#define DDRCTRL_INIT2_IDLE_AFTER_RESET_X32_Pos (8U)
#define DDRCTRL_INIT2_IDLE_AFTER_RESET_X32_Msk (0xFFU << DDRCTRL_INIT2_IDLE_AFTER_RESET_X32_Pos) /*!< 0x0000FF00 */
#define DDRCTRL_INIT2_IDLE_AFTER_RESET_X32     DDRCTRL_INIT2_IDLE_AFTER_RESET_X32_Msk            /*!< Idle time after the reset command, tINIT4. Present only in designs configured to support LPDDR2. */
#define DDRCTRL_INIT2_IDLE_AFTER_RESET_X32_0   (0x1U << DDRCTRL_INIT2_IDLE_AFTER_RESET_X32_Pos)  /*!< 0x00000100 */
#define DDRCTRL_INIT2_IDLE_AFTER_RESET_X32_1   (0x2U << DDRCTRL_INIT2_IDLE_AFTER_RESET_X32_Pos)  /*!< 0x00000200 */
#define DDRCTRL_INIT2_IDLE_AFTER_RESET_X32_2   (0x4U << DDRCTRL_INIT2_IDLE_AFTER_RESET_X32_Pos)  /*!< 0x00000400 */
#define DDRCTRL_INIT2_IDLE_AFTER_RESET_X32_3   (0x8U << DDRCTRL_INIT2_IDLE_AFTER_RESET_X32_Pos)  /*!< 0x00000800 */
#define DDRCTRL_INIT2_IDLE_AFTER_RESET_X32_4   (0x10U << DDRCTRL_INIT2_IDLE_AFTER_RESET_X32_Pos) /*!< 0x00001000 */
#define DDRCTRL_INIT2_IDLE_AFTER_RESET_X32_5   (0x20U << DDRCTRL_INIT2_IDLE_AFTER_RESET_X32_Pos) /*!< 0x00002000 */
#define DDRCTRL_INIT2_IDLE_AFTER_RESET_X32_6   (0x40U << DDRCTRL_INIT2_IDLE_AFTER_RESET_X32_Pos) /*!< 0x00004000 */
#define DDRCTRL_INIT2_IDLE_AFTER_RESET_X32_7   (0x80U << DDRCTRL_INIT2_IDLE_AFTER_RESET_X32_Pos) /*!< 0x00008000 */

/****************  Bit definition for DDRCTRL_INIT3 register  *****************/
#define DDRCTRL_INIT3_EMR_Pos (0U)
#define DDRCTRL_INIT3_EMR_Msk (0xFFFFU << DDRCTRL_INIT3_EMR_Pos) /*!< 0x0000FFFF */
#define DDRCTRL_INIT3_EMR     DDRCTRL_INIT3_EMR_Msk              /*!< DDR2: Value to write to EMR register. Bits 9:7 are for OCD and the setting in this register is ignored. The DDRCTRL sets those bits appropriately. */
#define DDRCTRL_INIT3_EMR_0   (0x1U << DDRCTRL_INIT3_EMR_Pos)    /*!< 0x00000001 */
#define DDRCTRL_INIT3_EMR_1   (0x2U << DDRCTRL_INIT3_EMR_Pos)    /*!< 0x00000002 */
#define DDRCTRL_INIT3_EMR_2   (0x4U << DDRCTRL_INIT3_EMR_Pos)    /*!< 0x00000004 */
#define DDRCTRL_INIT3_EMR_3   (0x8U << DDRCTRL_INIT3_EMR_Pos)    /*!< 0x00000008 */
#define DDRCTRL_INIT3_EMR_4   (0x10U << DDRCTRL_INIT3_EMR_Pos)   /*!< 0x00000010 */
#define DDRCTRL_INIT3_EMR_5   (0x20U << DDRCTRL_INIT3_EMR_Pos)   /*!< 0x00000020 */
#define DDRCTRL_INIT3_EMR_6   (0x40U << DDRCTRL_INIT3_EMR_Pos)   /*!< 0x00000040 */
#define DDRCTRL_INIT3_EMR_7   (0x80U << DDRCTRL_INIT3_EMR_Pos)   /*!< 0x00000080 */
#define DDRCTRL_INIT3_EMR_8   (0x100U << DDRCTRL_INIT3_EMR_Pos)  /*!< 0x00000100 */
#define DDRCTRL_INIT3_EMR_9   (0x200U << DDRCTRL_INIT3_EMR_Pos)  /*!< 0x00000200 */
#define DDRCTRL_INIT3_EMR_10  (0x400U << DDRCTRL_INIT3_EMR_Pos)  /*!< 0x00000400 */
#define DDRCTRL_INIT3_EMR_11  (0x800U << DDRCTRL_INIT3_EMR_Pos)  /*!< 0x00000800 */
#define DDRCTRL_INIT3_EMR_12  (0x1000U << DDRCTRL_INIT3_EMR_Pos) /*!< 0x00001000 */
#define DDRCTRL_INIT3_EMR_13  (0x2000U << DDRCTRL_INIT3_EMR_Pos) /*!< 0x00002000 */
#define DDRCTRL_INIT3_EMR_14  (0x4000U << DDRCTRL_INIT3_EMR_Pos) /*!< 0x00004000 */
#define DDRCTRL_INIT3_EMR_15  (0x8000U << DDRCTRL_INIT3_EMR_Pos) /*!< 0x00008000 */
#define DDRCTRL_INIT3_MR_Pos  (16U)
#define DDRCTRL_INIT3_MR_Msk  (0xFFFFU << DDRCTRL_INIT3_MR_Pos)  /*!< 0xFFFF0000 */
#define DDRCTRL_INIT3_MR      DDRCTRL_INIT3_MR_Msk               /*!< DDR2: Value to write to MR register. Bit 8 is for DLL and the setting here is ignored. The DDRCTRL sets this bit appropriately. */
#define DDRCTRL_INIT3_MR_0    (0x1U << DDRCTRL_INIT3_MR_Pos)     /*!< 0x00010000 */
#define DDRCTRL_INIT3_MR_1    (0x2U << DDRCTRL_INIT3_MR_Pos)     /*!< 0x00020000 */
#define DDRCTRL_INIT3_MR_2    (0x4U << DDRCTRL_INIT3_MR_Pos)     /*!< 0x00040000 */
#define DDRCTRL_INIT3_MR_3    (0x8U << DDRCTRL_INIT3_MR_Pos)     /*!< 0x00080000 */
#define DDRCTRL_INIT3_MR_4    (0x10U << DDRCTRL_INIT3_MR_Pos)    /*!< 0x00100000 */
#define DDRCTRL_INIT3_MR_5    (0x20U << DDRCTRL_INIT3_MR_Pos)    /*!< 0x00200000 */
#define DDRCTRL_INIT3_MR_6    (0x40U << DDRCTRL_INIT3_MR_Pos)    /*!< 0x00400000 */
#define DDRCTRL_INIT3_MR_7    (0x80U << DDRCTRL_INIT3_MR_Pos)    /*!< 0x00800000 */
#define DDRCTRL_INIT3_MR_8    (0x100U << DDRCTRL_INIT3_MR_Pos)   /*!< 0x01000000 */
#define DDRCTRL_INIT3_MR_9    (0x200U << DDRCTRL_INIT3_MR_Pos)   /*!< 0x02000000 */
#define DDRCTRL_INIT3_MR_10   (0x400U << DDRCTRL_INIT3_MR_Pos)   /*!< 0x04000000 */
#define DDRCTRL_INIT3_MR_11   (0x800U << DDRCTRL_INIT3_MR_Pos)   /*!< 0x08000000 */
#define DDRCTRL_INIT3_MR_12   (0x1000U << DDRCTRL_INIT3_MR_Pos)  /*!< 0x10000000 */
#define DDRCTRL_INIT3_MR_13   (0x2000U << DDRCTRL_INIT3_MR_Pos)  /*!< 0x20000000 */
#define DDRCTRL_INIT3_MR_14   (0x4000U << DDRCTRL_INIT3_MR_Pos)  /*!< 0x40000000 */
#define DDRCTRL_INIT3_MR_15   (0x8000U << DDRCTRL_INIT3_MR_Pos)  /*!< 0x80000000 */

/****************  Bit definition for DDRCTRL_INIT4 register  *****************/
#define DDRCTRL_INIT4_EMR3_Pos (0U)
#define DDRCTRL_INIT4_EMR3_Msk (0xFFFFU << DDRCTRL_INIT4_EMR3_Pos) /*!< 0x0000FFFF */
#define DDRCTRL_INIT4_EMR3     DDRCTRL_INIT4_EMR3_Msk              /*!< DDR2: Value to write to EMR3 register. */
#define DDRCTRL_INIT4_EMR3_0   (0x1U << DDRCTRL_INIT4_EMR3_Pos)    /*!< 0x00000001 */
#define DDRCTRL_INIT4_EMR3_1   (0x2U << DDRCTRL_INIT4_EMR3_Pos)    /*!< 0x00000002 */
#define DDRCTRL_INIT4_EMR3_2   (0x4U << DDRCTRL_INIT4_EMR3_Pos)    /*!< 0x00000004 */
#define DDRCTRL_INIT4_EMR3_3   (0x8U << DDRCTRL_INIT4_EMR3_Pos)    /*!< 0x00000008 */
#define DDRCTRL_INIT4_EMR3_4   (0x10U << DDRCTRL_INIT4_EMR3_Pos)   /*!< 0x00000010 */
#define DDRCTRL_INIT4_EMR3_5   (0x20U << DDRCTRL_INIT4_EMR3_Pos)   /*!< 0x00000020 */
#define DDRCTRL_INIT4_EMR3_6   (0x40U << DDRCTRL_INIT4_EMR3_Pos)   /*!< 0x00000040 */
#define DDRCTRL_INIT4_EMR3_7   (0x80U << DDRCTRL_INIT4_EMR3_Pos)   /*!< 0x00000080 */
#define DDRCTRL_INIT4_EMR3_8   (0x100U << DDRCTRL_INIT4_EMR3_Pos)  /*!< 0x00000100 */
#define DDRCTRL_INIT4_EMR3_9   (0x200U << DDRCTRL_INIT4_EMR3_Pos)  /*!< 0x00000200 */
#define DDRCTRL_INIT4_EMR3_10  (0x400U << DDRCTRL_INIT4_EMR3_Pos)  /*!< 0x00000400 */
#define DDRCTRL_INIT4_EMR3_11  (0x800U << DDRCTRL_INIT4_EMR3_Pos)  /*!< 0x00000800 */
#define DDRCTRL_INIT4_EMR3_12  (0x1000U << DDRCTRL_INIT4_EMR3_Pos) /*!< 0x00001000 */
#define DDRCTRL_INIT4_EMR3_13  (0x2000U << DDRCTRL_INIT4_EMR3_Pos) /*!< 0x00002000 */
#define DDRCTRL_INIT4_EMR3_14  (0x4000U << DDRCTRL_INIT4_EMR3_Pos) /*!< 0x00004000 */
#define DDRCTRL_INIT4_EMR3_15  (0x8000U << DDRCTRL_INIT4_EMR3_Pos) /*!< 0x00008000 */
#define DDRCTRL_INIT4_EMR2_Pos (16U)
#define DDRCTRL_INIT4_EMR2_Msk (0xFFFFU << DDRCTRL_INIT4_EMR2_Pos) /*!< 0xFFFF0000 */
#define DDRCTRL_INIT4_EMR2     DDRCTRL_INIT4_EMR2_Msk              /*!< DDR2: Value to write to EMR2 register. */
#define DDRCTRL_INIT4_EMR2_0   (0x1U << DDRCTRL_INIT4_EMR2_Pos)    /*!< 0x00010000 */
#define DDRCTRL_INIT4_EMR2_1   (0x2U << DDRCTRL_INIT4_EMR2_Pos)    /*!< 0x00020000 */
#define DDRCTRL_INIT4_EMR2_2   (0x4U << DDRCTRL_INIT4_EMR2_Pos)    /*!< 0x00040000 */
#define DDRCTRL_INIT4_EMR2_3   (0x8U << DDRCTRL_INIT4_EMR2_Pos)    /*!< 0x00080000 */
#define DDRCTRL_INIT4_EMR2_4   (0x10U << DDRCTRL_INIT4_EMR2_Pos)   /*!< 0x00100000 */
#define DDRCTRL_INIT4_EMR2_5   (0x20U << DDRCTRL_INIT4_EMR2_Pos)   /*!< 0x00200000 */
#define DDRCTRL_INIT4_EMR2_6   (0x40U << DDRCTRL_INIT4_EMR2_Pos)   /*!< 0x00400000 */
#define DDRCTRL_INIT4_EMR2_7   (0x80U << DDRCTRL_INIT4_EMR2_Pos)   /*!< 0x00800000 */
#define DDRCTRL_INIT4_EMR2_8   (0x100U << DDRCTRL_INIT4_EMR2_Pos)  /*!< 0x01000000 */
#define DDRCTRL_INIT4_EMR2_9   (0x200U << DDRCTRL_INIT4_EMR2_Pos)  /*!< 0x02000000 */
#define DDRCTRL_INIT4_EMR2_10  (0x400U << DDRCTRL_INIT4_EMR2_Pos)  /*!< 0x04000000 */
#define DDRCTRL_INIT4_EMR2_11  (0x800U << DDRCTRL_INIT4_EMR2_Pos)  /*!< 0x08000000 */
#define DDRCTRL_INIT4_EMR2_12  (0x1000U << DDRCTRL_INIT4_EMR2_Pos) /*!< 0x10000000 */
#define DDRCTRL_INIT4_EMR2_13  (0x2000U << DDRCTRL_INIT4_EMR2_Pos) /*!< 0x20000000 */
#define DDRCTRL_INIT4_EMR2_14  (0x4000U << DDRCTRL_INIT4_EMR2_Pos) /*!< 0x40000000 */
#define DDRCTRL_INIT4_EMR2_15  (0x8000U << DDRCTRL_INIT4_EMR2_Pos) /*!< 0x80000000 */

/****************  Bit definition for DDRCTRL_INIT5 register  *****************/
#define DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_Pos (0U)
#define DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_Msk (0x3FFU << DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_Pos) /*!< 0x000003FF */
#define DDRCTRL_INIT5_MAX_AUTO_INIT_X1024     DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_Msk             /*!< Maximum duration of the auto initialization, tINIT5. Present only in designs configured to support LPDDR2/LPDDR3. */
#define DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_0   (0x1U << DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_Pos)   /*!< 0x00000001 */
#define DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_1   (0x2U << DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_Pos)   /*!< 0x00000002 */
#define DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_2   (0x4U << DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_Pos)   /*!< 0x00000004 */
#define DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_3   (0x8U << DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_Pos)   /*!< 0x00000008 */
#define DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_4   (0x10U << DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_Pos)  /*!< 0x00000010 */
#define DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_5   (0x20U << DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_Pos)  /*!< 0x00000020 */
#define DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_6   (0x40U << DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_Pos)  /*!< 0x00000040 */
#define DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_7   (0x80U << DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_Pos)  /*!< 0x00000080 */
#define DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_8   (0x100U << DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_Pos) /*!< 0x00000100 */
#define DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_9   (0x200U << DDRCTRL_INIT5_MAX_AUTO_INIT_X1024_Pos) /*!< 0x00000200 */
#define DDRCTRL_INIT5_DEV_ZQINIT_X32_Pos      (16U)
#define DDRCTRL_INIT5_DEV_ZQINIT_X32_Msk      (0xFFU << DDRCTRL_INIT5_DEV_ZQINIT_X32_Pos)       /*!< 0x00FF0000 */
#define DDRCTRL_INIT5_DEV_ZQINIT_X32          DDRCTRL_INIT5_DEV_ZQINIT_X32_Msk                  /*!< ZQ initial calibration, tZQINIT. Present only in designs configured to support DDR3 or DDR4 or LPDDR2/LPDDR3. */
#define DDRCTRL_INIT5_DEV_ZQINIT_X32_0        (0x1U << DDRCTRL_INIT5_DEV_ZQINIT_X32_Pos)        /*!< 0x00010000 */
#define DDRCTRL_INIT5_DEV_ZQINIT_X32_1        (0x2U << DDRCTRL_INIT5_DEV_ZQINIT_X32_Pos)        /*!< 0x00020000 */
#define DDRCTRL_INIT5_DEV_ZQINIT_X32_2        (0x4U << DDRCTRL_INIT5_DEV_ZQINIT_X32_Pos)        /*!< 0x00040000 */
#define DDRCTRL_INIT5_DEV_ZQINIT_X32_3        (0x8U << DDRCTRL_INIT5_DEV_ZQINIT_X32_Pos)        /*!< 0x00080000 */
#define DDRCTRL_INIT5_DEV_ZQINIT_X32_4        (0x10U << DDRCTRL_INIT5_DEV_ZQINIT_X32_Pos)       /*!< 0x00100000 */
#define DDRCTRL_INIT5_DEV_ZQINIT_X32_5        (0x20U << DDRCTRL_INIT5_DEV_ZQINIT_X32_Pos)       /*!< 0x00200000 */
#define DDRCTRL_INIT5_DEV_ZQINIT_X32_6        (0x40U << DDRCTRL_INIT5_DEV_ZQINIT_X32_Pos)       /*!< 0x00400000 */
#define DDRCTRL_INIT5_DEV_ZQINIT_X32_7        (0x80U << DDRCTRL_INIT5_DEV_ZQINIT_X32_Pos)       /*!< 0x00800000 */

/***************  Bit definition for DDRCTRL_DIMMCTL register  ****************/
#define DDRCTRL_DIMMCTL_DIMM_STAGGER_CS_EN_Pos (0U)
#define DDRCTRL_DIMMCTL_DIMM_STAGGER_CS_EN_Msk (0x1U << DDRCTRL_DIMMCTL_DIMM_STAGGER_CS_EN_Pos) /*!< 0x00000001 */
#define DDRCTRL_DIMMCTL_DIMM_STAGGER_CS_EN     DDRCTRL_DIMMCTL_DIMM_STAGGER_CS_EN_Msk           /*!< Staggering enable for multi-rank accesses (for multi-rank UDIMM, RDIMM and LRDIMM implementations only). This is not supported for mDDR, LPDDR2, LPDDR3 or LPDDR4 SDRAMs. */
#define DDRCTRL_DIMMCTL_DIMM_ADDR_MIRR_EN_Pos  (1U)
#define DDRCTRL_DIMMCTL_DIMM_ADDR_MIRR_EN_Msk  (0x1U << DDRCTRL_DIMMCTL_DIMM_ADDR_MIRR_EN_Pos)  /*!< 0x00000002 */
#define DDRCTRL_DIMMCTL_DIMM_ADDR_MIRR_EN      DDRCTRL_DIMMCTL_DIMM_ADDR_MIRR_EN_Msk            /*!< Address Mirroring Enable (for multi-rank UDIMM implementations and multi-rank DDR4 RDIMM/LRDIMM implementations). */

/***************  Bit definition for DDRCTRL_DRAMTMG0 register  ***************/
#define DDRCTRL_DRAMTMG0_T_RAS_MIN_Pos (0U)
#define DDRCTRL_DRAMTMG0_T_RAS_MIN_Msk (0x3FU << DDRCTRL_DRAMTMG0_T_RAS_MIN_Pos) /*!< 0x0000003F */
#define DDRCTRL_DRAMTMG0_T_RAS_MIN     DDRCTRL_DRAMTMG0_T_RAS_MIN_Msk            /*!< tRAS(min): Minimum time between activate and precharge to the same bank. */
#define DDRCTRL_DRAMTMG0_T_RAS_MIN_0   (0x1U << DDRCTRL_DRAMTMG0_T_RAS_MIN_Pos)  /*!< 0x00000001 */
#define DDRCTRL_DRAMTMG0_T_RAS_MIN_1   (0x2U << DDRCTRL_DRAMTMG0_T_RAS_MIN_Pos)  /*!< 0x00000002 */
#define DDRCTRL_DRAMTMG0_T_RAS_MIN_2   (0x4U << DDRCTRL_DRAMTMG0_T_RAS_MIN_Pos)  /*!< 0x00000004 */
#define DDRCTRL_DRAMTMG0_T_RAS_MIN_3   (0x8U << DDRCTRL_DRAMTMG0_T_RAS_MIN_Pos)  /*!< 0x00000008 */
#define DDRCTRL_DRAMTMG0_T_RAS_MIN_4   (0x10U << DDRCTRL_DRAMTMG0_T_RAS_MIN_Pos) /*!< 0x00000010 */
#define DDRCTRL_DRAMTMG0_T_RAS_MIN_5   (0x20U << DDRCTRL_DRAMTMG0_T_RAS_MIN_Pos) /*!< 0x00000020 */
#define DDRCTRL_DRAMTMG0_T_RAS_MAX_Pos (8U)
#define DDRCTRL_DRAMTMG0_T_RAS_MAX_Msk (0x7FU << DDRCTRL_DRAMTMG0_T_RAS_MAX_Pos) /*!< 0x00007F00 */
#define DDRCTRL_DRAMTMG0_T_RAS_MAX     DDRCTRL_DRAMTMG0_T_RAS_MAX_Msk            /*!< tRAS(max): Maximum time between activate and precharge to same bank. This is the maximum time that a page can be kept open */
#define DDRCTRL_DRAMTMG0_T_RAS_MAX_0   (0x1U << DDRCTRL_DRAMTMG0_T_RAS_MAX_Pos)  /*!< 0x00000100 */
#define DDRCTRL_DRAMTMG0_T_RAS_MAX_1   (0x2U << DDRCTRL_DRAMTMG0_T_RAS_MAX_Pos)  /*!< 0x00000200 */
#define DDRCTRL_DRAMTMG0_T_RAS_MAX_2   (0x4U << DDRCTRL_DRAMTMG0_T_RAS_MAX_Pos)  /*!< 0x00000400 */
#define DDRCTRL_DRAMTMG0_T_RAS_MAX_3   (0x8U << DDRCTRL_DRAMTMG0_T_RAS_MAX_Pos)  /*!< 0x00000800 */
#define DDRCTRL_DRAMTMG0_T_RAS_MAX_4   (0x10U << DDRCTRL_DRAMTMG0_T_RAS_MAX_Pos) /*!< 0x00001000 */
#define DDRCTRL_DRAMTMG0_T_RAS_MAX_5   (0x20U << DDRCTRL_DRAMTMG0_T_RAS_MAX_Pos) /*!< 0x00002000 */
#define DDRCTRL_DRAMTMG0_T_RAS_MAX_6   (0x40U << DDRCTRL_DRAMTMG0_T_RAS_MAX_Pos) /*!< 0x00004000 */
#define DDRCTRL_DRAMTMG0_T_FAW_Pos     (16U)
#define DDRCTRL_DRAMTMG0_T_FAW_Msk     (0x3FU << DDRCTRL_DRAMTMG0_T_FAW_Pos)     /*!< 0x003F0000 */
#define DDRCTRL_DRAMTMG0_T_FAW         DDRCTRL_DRAMTMG0_T_FAW_Msk                /*!< tFAW Valid only when 8 or more banks(or banks x bank groups) are present. */
#define DDRCTRL_DRAMTMG0_T_FAW_0       (0x1U << DDRCTRL_DRAMTMG0_T_FAW_Pos)      /*!< 0x00010000 */
#define DDRCTRL_DRAMTMG0_T_FAW_1       (0x2U << DDRCTRL_DRAMTMG0_T_FAW_Pos)      /*!< 0x00020000 */
#define DDRCTRL_DRAMTMG0_T_FAW_2       (0x4U << DDRCTRL_DRAMTMG0_T_FAW_Pos)      /*!< 0x00040000 */
#define DDRCTRL_DRAMTMG0_T_FAW_3       (0x8U << DDRCTRL_DRAMTMG0_T_FAW_Pos)      /*!< 0x00080000 */
#define DDRCTRL_DRAMTMG0_T_FAW_4       (0x10U << DDRCTRL_DRAMTMG0_T_FAW_Pos)     /*!< 0x00100000 */
#define DDRCTRL_DRAMTMG0_T_FAW_5       (0x20U << DDRCTRL_DRAMTMG0_T_FAW_Pos)     /*!< 0x00200000 */
#define DDRCTRL_DRAMTMG0_WR2PRE_Pos    (24U)
#define DDRCTRL_DRAMTMG0_WR2PRE_Msk    (0x7FU << DDRCTRL_DRAMTMG0_WR2PRE_Pos)    /*!< 0x7F000000 */
#define DDRCTRL_DRAMTMG0_WR2PRE        DDRCTRL_DRAMTMG0_WR2PRE_Msk               /*!< Minimum time between write and precharge to same bank. */
#define DDRCTRL_DRAMTMG0_WR2PRE_0      (0x1U << DDRCTRL_DRAMTMG0_WR2PRE_Pos)     /*!< 0x01000000 */
#define DDRCTRL_DRAMTMG0_WR2PRE_1      (0x2U << DDRCTRL_DRAMTMG0_WR2PRE_Pos)     /*!< 0x02000000 */
#define DDRCTRL_DRAMTMG0_WR2PRE_2      (0x4U << DDRCTRL_DRAMTMG0_WR2PRE_Pos)     /*!< 0x04000000 */
#define DDRCTRL_DRAMTMG0_WR2PRE_3      (0x8U << DDRCTRL_DRAMTMG0_WR2PRE_Pos)     /*!< 0x08000000 */
#define DDRCTRL_DRAMTMG0_WR2PRE_4      (0x10U << DDRCTRL_DRAMTMG0_WR2PRE_Pos)    /*!< 0x10000000 */
#define DDRCTRL_DRAMTMG0_WR2PRE_5      (0x20U << DDRCTRL_DRAMTMG0_WR2PRE_Pos)    /*!< 0x20000000 */
#define DDRCTRL_DRAMTMG0_WR2PRE_6      (0x40U << DDRCTRL_DRAMTMG0_WR2PRE_Pos)    /*!< 0x40000000 */

/***************  Bit definition for DDRCTRL_DRAMTMG1 register  ***************/
#define DDRCTRL_DRAMTMG1_T_RC_Pos   (0U)
#define DDRCTRL_DRAMTMG1_T_RC_Msk   (0x7FU << DDRCTRL_DRAMTMG1_T_RC_Pos)   /*!< 0x0000007F */
#define DDRCTRL_DRAMTMG1_T_RC       DDRCTRL_DRAMTMG1_T_RC_Msk              /*!< tRC: Minimum time between activates to same bank. */
#define DDRCTRL_DRAMTMG1_T_RC_0     (0x1U << DDRCTRL_DRAMTMG1_T_RC_Pos)    /*!< 0x00000001 */
#define DDRCTRL_DRAMTMG1_T_RC_1     (0x2U << DDRCTRL_DRAMTMG1_T_RC_Pos)    /*!< 0x00000002 */
#define DDRCTRL_DRAMTMG1_T_RC_2     (0x4U << DDRCTRL_DRAMTMG1_T_RC_Pos)    /*!< 0x00000004 */
#define DDRCTRL_DRAMTMG1_T_RC_3     (0x8U << DDRCTRL_DRAMTMG1_T_RC_Pos)    /*!< 0x00000008 */
#define DDRCTRL_DRAMTMG1_T_RC_4     (0x10U << DDRCTRL_DRAMTMG1_T_RC_Pos)   /*!< 0x00000010 */
#define DDRCTRL_DRAMTMG1_T_RC_5     (0x20U << DDRCTRL_DRAMTMG1_T_RC_Pos)   /*!< 0x00000020 */
#define DDRCTRL_DRAMTMG1_T_RC_6     (0x40U << DDRCTRL_DRAMTMG1_T_RC_Pos)   /*!< 0x00000040 */
#define DDRCTRL_DRAMTMG1_RD2PRE_Pos (8U)
#define DDRCTRL_DRAMTMG1_RD2PRE_Msk (0x3FU << DDRCTRL_DRAMTMG1_RD2PRE_Pos) /*!< 0x00003F00 */
#define DDRCTRL_DRAMTMG1_RD2PRE     DDRCTRL_DRAMTMG1_RD2PRE_Msk            /*!< tRTP: Minimum time from read to precharge of same bank. */
#define DDRCTRL_DRAMTMG1_RD2PRE_0   (0x1U << DDRCTRL_DRAMTMG1_RD2PRE_Pos)  /*!< 0x00000100 */
#define DDRCTRL_DRAMTMG1_RD2PRE_1   (0x2U << DDRCTRL_DRAMTMG1_RD2PRE_Pos)  /*!< 0x00000200 */
#define DDRCTRL_DRAMTMG1_RD2PRE_2   (0x4U << DDRCTRL_DRAMTMG1_RD2PRE_Pos)  /*!< 0x00000400 */
#define DDRCTRL_DRAMTMG1_RD2PRE_3   (0x8U << DDRCTRL_DRAMTMG1_RD2PRE_Pos)  /*!< 0x00000800 */
#define DDRCTRL_DRAMTMG1_RD2PRE_4   (0x10U << DDRCTRL_DRAMTMG1_RD2PRE_Pos) /*!< 0x00001000 */
#define DDRCTRL_DRAMTMG1_RD2PRE_5   (0x20U << DDRCTRL_DRAMTMG1_RD2PRE_Pos) /*!< 0x00002000 */
#define DDRCTRL_DRAMTMG1_T_XP_Pos   (16U)
#define DDRCTRL_DRAMTMG1_T_XP_Msk   (0x1FU << DDRCTRL_DRAMTMG1_T_XP_Pos)   /*!< 0x001F0000 */
#define DDRCTRL_DRAMTMG1_T_XP       DDRCTRL_DRAMTMG1_T_XP_Msk              /*!< tXP: Minimum time after power-down exit to any operation. For DDR3, this should be programmed to tXPDLL if slow powerdown exit is selected in MR0[12]. */
#define DDRCTRL_DRAMTMG1_T_XP_0     (0x1U << DDRCTRL_DRAMTMG1_T_XP_Pos)    /*!< 0x00010000 */
#define DDRCTRL_DRAMTMG1_T_XP_1     (0x2U << DDRCTRL_DRAMTMG1_T_XP_Pos)    /*!< 0x00020000 */
#define DDRCTRL_DRAMTMG1_T_XP_2     (0x4U << DDRCTRL_DRAMTMG1_T_XP_Pos)    /*!< 0x00040000 */
#define DDRCTRL_DRAMTMG1_T_XP_3     (0x8U << DDRCTRL_DRAMTMG1_T_XP_Pos)    /*!< 0x00080000 */
#define DDRCTRL_DRAMTMG1_T_XP_4     (0x10U << DDRCTRL_DRAMTMG1_T_XP_Pos)   /*!< 0x00100000 */

/***************  Bit definition for DDRCTRL_DRAMTMG2 register  ***************/
#define DDRCTRL_DRAMTMG2_WR2RD_Pos         (0U)
#define DDRCTRL_DRAMTMG2_WR2RD_Msk         (0x3FU << DDRCTRL_DRAMTMG2_WR2RD_Pos)         /*!< 0x0000003F */
#define DDRCTRL_DRAMTMG2_WR2RD             DDRCTRL_DRAMTMG2_WR2RD_Msk                    /*!< DDR4: CWL + PL + BL/2 + tWTR_L */
#define DDRCTRL_DRAMTMG2_WR2RD_0           (0x1U << DDRCTRL_DRAMTMG2_WR2RD_Pos)          /*!< 0x00000001 */
#define DDRCTRL_DRAMTMG2_WR2RD_1           (0x2U << DDRCTRL_DRAMTMG2_WR2RD_Pos)          /*!< 0x00000002 */
#define DDRCTRL_DRAMTMG2_WR2RD_2           (0x4U << DDRCTRL_DRAMTMG2_WR2RD_Pos)          /*!< 0x00000004 */
#define DDRCTRL_DRAMTMG2_WR2RD_3           (0x8U << DDRCTRL_DRAMTMG2_WR2RD_Pos)          /*!< 0x00000008 */
#define DDRCTRL_DRAMTMG2_WR2RD_4           (0x10U << DDRCTRL_DRAMTMG2_WR2RD_Pos)         /*!< 0x00000010 */
#define DDRCTRL_DRAMTMG2_WR2RD_5           (0x20U << DDRCTRL_DRAMTMG2_WR2RD_Pos)         /*!< 0x00000020 */
#define DDRCTRL_DRAMTMG2_RD2WR_Pos         (8U)
#define DDRCTRL_DRAMTMG2_RD2WR_Msk         (0x3FU << DDRCTRL_DRAMTMG2_RD2WR_Pos)         /*!< 0x00003F00 */
#define DDRCTRL_DRAMTMG2_RD2WR             DDRCTRL_DRAMTMG2_RD2WR_Msk                    /*!< DDR2/3/mDDR: RL + BL/2 + 2 - WL */
#define DDRCTRL_DRAMTMG2_RD2WR_0           (0x1U << DDRCTRL_DRAMTMG2_RD2WR_Pos)          /*!< 0x00000100 */
#define DDRCTRL_DRAMTMG2_RD2WR_1           (0x2U << DDRCTRL_DRAMTMG2_RD2WR_Pos)          /*!< 0x00000200 */
#define DDRCTRL_DRAMTMG2_RD2WR_2           (0x4U << DDRCTRL_DRAMTMG2_RD2WR_Pos)          /*!< 0x00000400 */
#define DDRCTRL_DRAMTMG2_RD2WR_3           (0x8U << DDRCTRL_DRAMTMG2_RD2WR_Pos)          /*!< 0x00000800 */
#define DDRCTRL_DRAMTMG2_RD2WR_4           (0x10U << DDRCTRL_DRAMTMG2_RD2WR_Pos)         /*!< 0x00001000 */
#define DDRCTRL_DRAMTMG2_RD2WR_5           (0x20U << DDRCTRL_DRAMTMG2_RD2WR_Pos)         /*!< 0x00002000 */
#define DDRCTRL_DRAMTMG2_READ_LATENCY_Pos  (16U)
#define DDRCTRL_DRAMTMG2_READ_LATENCY_Msk  (0x3FU << DDRCTRL_DRAMTMG2_READ_LATENCY_Pos)  /*!< 0x003F0000 */
#define DDRCTRL_DRAMTMG2_READ_LATENCY      DDRCTRL_DRAMTMG2_READ_LATENCY_Msk             /*!< Set to RL */
#define DDRCTRL_DRAMTMG2_READ_LATENCY_0    (0x1U << DDRCTRL_DRAMTMG2_READ_LATENCY_Pos)   /*!< 0x00010000 */
#define DDRCTRL_DRAMTMG2_READ_LATENCY_1    (0x2U << DDRCTRL_DRAMTMG2_READ_LATENCY_Pos)   /*!< 0x00020000 */
#define DDRCTRL_DRAMTMG2_READ_LATENCY_2    (0x4U << DDRCTRL_DRAMTMG2_READ_LATENCY_Pos)   /*!< 0x00040000 */
#define DDRCTRL_DRAMTMG2_READ_LATENCY_3    (0x8U << DDRCTRL_DRAMTMG2_READ_LATENCY_Pos)   /*!< 0x00080000 */
#define DDRCTRL_DRAMTMG2_READ_LATENCY_4    (0x10U << DDRCTRL_DRAMTMG2_READ_LATENCY_Pos)  /*!< 0x00100000 */
#define DDRCTRL_DRAMTMG2_READ_LATENCY_5    (0x20U << DDRCTRL_DRAMTMG2_READ_LATENCY_Pos)  /*!< 0x00200000 */
#define DDRCTRL_DRAMTMG2_WRITE_LATENCY_Pos (24U)
#define DDRCTRL_DRAMTMG2_WRITE_LATENCY_Msk (0x3FU << DDRCTRL_DRAMTMG2_WRITE_LATENCY_Pos) /*!< 0x3F000000 */
#define DDRCTRL_DRAMTMG2_WRITE_LATENCY     DDRCTRL_DRAMTMG2_WRITE_LATENCY_Msk            /*!< Set to WL */
#define DDRCTRL_DRAMTMG2_WRITE_LATENCY_0   (0x1U << DDRCTRL_DRAMTMG2_WRITE_LATENCY_Pos)  /*!< 0x01000000 */
#define DDRCTRL_DRAMTMG2_WRITE_LATENCY_1   (0x2U << DDRCTRL_DRAMTMG2_WRITE_LATENCY_Pos)  /*!< 0x02000000 */
#define DDRCTRL_DRAMTMG2_WRITE_LATENCY_2   (0x4U << DDRCTRL_DRAMTMG2_WRITE_LATENCY_Pos)  /*!< 0x04000000 */
#define DDRCTRL_DRAMTMG2_WRITE_LATENCY_3   (0x8U << DDRCTRL_DRAMTMG2_WRITE_LATENCY_Pos)  /*!< 0x08000000 */
#define DDRCTRL_DRAMTMG2_WRITE_LATENCY_4   (0x10U << DDRCTRL_DRAMTMG2_WRITE_LATENCY_Pos) /*!< 0x10000000 */
#define DDRCTRL_DRAMTMG2_WRITE_LATENCY_5   (0x20U << DDRCTRL_DRAMTMG2_WRITE_LATENCY_Pos) /*!< 0x20000000 */

/***************  Bit definition for DDRCTRL_DRAMTMG3 register  ***************/
#define DDRCTRL_DRAMTMG3_T_MOD_Pos (0U)
#define DDRCTRL_DRAMTMG3_T_MOD_Msk (0x3FFU << DDRCTRL_DRAMTMG3_T_MOD_Pos) /*!< 0x000003FF */
#define DDRCTRL_DRAMTMG3_T_MOD     DDRCTRL_DRAMTMG3_T_MOD_Msk             /*!< tMOD: Parameter used only in DDR3 and DDR4. Cycles between load mode command and following non-load mode command. */
#define DDRCTRL_DRAMTMG3_T_MOD_0   (0x1U << DDRCTRL_DRAMTMG3_T_MOD_Pos)   /*!< 0x00000001 */
#define DDRCTRL_DRAMTMG3_T_MOD_1   (0x2U << DDRCTRL_DRAMTMG3_T_MOD_Pos)   /*!< 0x00000002 */
#define DDRCTRL_DRAMTMG3_T_MOD_2   (0x4U << DDRCTRL_DRAMTMG3_T_MOD_Pos)   /*!< 0x00000004 */
#define DDRCTRL_DRAMTMG3_T_MOD_3   (0x8U << DDRCTRL_DRAMTMG3_T_MOD_Pos)   /*!< 0x00000008 */
#define DDRCTRL_DRAMTMG3_T_MOD_4   (0x10U << DDRCTRL_DRAMTMG3_T_MOD_Pos)  /*!< 0x00000010 */
#define DDRCTRL_DRAMTMG3_T_MOD_5   (0x20U << DDRCTRL_DRAMTMG3_T_MOD_Pos)  /*!< 0x00000020 */
#define DDRCTRL_DRAMTMG3_T_MOD_6   (0x40U << DDRCTRL_DRAMTMG3_T_MOD_Pos)  /*!< 0x00000040 */
#define DDRCTRL_DRAMTMG3_T_MOD_7   (0x80U << DDRCTRL_DRAMTMG3_T_MOD_Pos)  /*!< 0x00000080 */
#define DDRCTRL_DRAMTMG3_T_MOD_8   (0x100U << DDRCTRL_DRAMTMG3_T_MOD_Pos) /*!< 0x00000100 */
#define DDRCTRL_DRAMTMG3_T_MOD_9   (0x200U << DDRCTRL_DRAMTMG3_T_MOD_Pos) /*!< 0x00000200 */
#define DDRCTRL_DRAMTMG3_T_MRD_Pos (12U)
#define DDRCTRL_DRAMTMG3_T_MRD_Msk (0x3FU << DDRCTRL_DRAMTMG3_T_MRD_Pos)  /*!< 0x0003F000 */
#define DDRCTRL_DRAMTMG3_T_MRD     DDRCTRL_DRAMTMG3_T_MRD_Msk             /*!< tMRD: Cycles to wait after a mode register write or read. Depending on the connected SDRAM, tMRD represents: */
#define DDRCTRL_DRAMTMG3_T_MRD_0   (0x1U << DDRCTRL_DRAMTMG3_T_MRD_Pos)   /*!< 0x00001000 */
#define DDRCTRL_DRAMTMG3_T_MRD_1   (0x2U << DDRCTRL_DRAMTMG3_T_MRD_Pos)   /*!< 0x00002000 */
#define DDRCTRL_DRAMTMG3_T_MRD_2   (0x4U << DDRCTRL_DRAMTMG3_T_MRD_Pos)   /*!< 0x00004000 */
#define DDRCTRL_DRAMTMG3_T_MRD_3   (0x8U << DDRCTRL_DRAMTMG3_T_MRD_Pos)   /*!< 0x00008000 */
#define DDRCTRL_DRAMTMG3_T_MRD_4   (0x10U << DDRCTRL_DRAMTMG3_T_MRD_Pos)  /*!< 0x00010000 */
#define DDRCTRL_DRAMTMG3_T_MRD_5   (0x20U << DDRCTRL_DRAMTMG3_T_MRD_Pos)  /*!< 0x00020000 */
#define DDRCTRL_DRAMTMG3_T_MRW_Pos (20U)
#define DDRCTRL_DRAMTMG3_T_MRW_Msk (0x3FFU << DDRCTRL_DRAMTMG3_T_MRW_Pos) /*!< 0x3FF00000 */
#define DDRCTRL_DRAMTMG3_T_MRW     DDRCTRL_DRAMTMG3_T_MRW_Msk             /*!< Time to wait after a mode register write or read (MRW or MRR). */
#define DDRCTRL_DRAMTMG3_T_MRW_0   (0x1U << DDRCTRL_DRAMTMG3_T_MRW_Pos)   /*!< 0x00100000 */
#define DDRCTRL_DRAMTMG3_T_MRW_1   (0x2U << DDRCTRL_DRAMTMG3_T_MRW_Pos)   /*!< 0x00200000 */
#define DDRCTRL_DRAMTMG3_T_MRW_2   (0x4U << DDRCTRL_DRAMTMG3_T_MRW_Pos)   /*!< 0x00400000 */
#define DDRCTRL_DRAMTMG3_T_MRW_3   (0x8U << DDRCTRL_DRAMTMG3_T_MRW_Pos)   /*!< 0x00800000 */
#define DDRCTRL_DRAMTMG3_T_MRW_4   (0x10U << DDRCTRL_DRAMTMG3_T_MRW_Pos)  /*!< 0x01000000 */
#define DDRCTRL_DRAMTMG3_T_MRW_5   (0x20U << DDRCTRL_DRAMTMG3_T_MRW_Pos)  /*!< 0x02000000 */
#define DDRCTRL_DRAMTMG3_T_MRW_6   (0x40U << DDRCTRL_DRAMTMG3_T_MRW_Pos)  /*!< 0x04000000 */
#define DDRCTRL_DRAMTMG3_T_MRW_7   (0x80U << DDRCTRL_DRAMTMG3_T_MRW_Pos)  /*!< 0x08000000 */
#define DDRCTRL_DRAMTMG3_T_MRW_8   (0x100U << DDRCTRL_DRAMTMG3_T_MRW_Pos) /*!< 0x10000000 */
#define DDRCTRL_DRAMTMG3_T_MRW_9   (0x200U << DDRCTRL_DRAMTMG3_T_MRW_Pos) /*!< 0x20000000 */

/***************  Bit definition for DDRCTRL_DRAMTMG4 register  ***************/
#define DDRCTRL_DRAMTMG4_T_RP_Pos  (0U)
#define DDRCTRL_DRAMTMG4_T_RP_Msk  (0x1FU << DDRCTRL_DRAMTMG4_T_RP_Pos)  /*!< 0x0000001F */
#define DDRCTRL_DRAMTMG4_T_RP      DDRCTRL_DRAMTMG4_T_RP_Msk             /*!< tRP: Minimum time from precharge to activate of same bank. */
#define DDRCTRL_DRAMTMG4_T_RP_0    (0x1U << DDRCTRL_DRAMTMG4_T_RP_Pos)   /*!< 0x00000001 */
#define DDRCTRL_DRAMTMG4_T_RP_1    (0x2U << DDRCTRL_DRAMTMG4_T_RP_Pos)   /*!< 0x00000002 */
#define DDRCTRL_DRAMTMG4_T_RP_2    (0x4U << DDRCTRL_DRAMTMG4_T_RP_Pos)   /*!< 0x00000004 */
#define DDRCTRL_DRAMTMG4_T_RP_3    (0x8U << DDRCTRL_DRAMTMG4_T_RP_Pos)   /*!< 0x00000008 */
#define DDRCTRL_DRAMTMG4_T_RP_4    (0x10U << DDRCTRL_DRAMTMG4_T_RP_Pos)  /*!< 0x00000010 */
#define DDRCTRL_DRAMTMG4_T_RRD_Pos (8U)
#define DDRCTRL_DRAMTMG4_T_RRD_Msk (0xFU << DDRCTRL_DRAMTMG4_T_RRD_Pos)  /*!< 0x00000F00 */
#define DDRCTRL_DRAMTMG4_T_RRD     DDRCTRL_DRAMTMG4_T_RRD_Msk            /*!< DDR4: tRRD_L: Minimum time between activates from bank "a" to bank "b" for same bank group. */
#define DDRCTRL_DRAMTMG4_T_RRD_0   (0x1U << DDRCTRL_DRAMTMG4_T_RRD_Pos)  /*!< 0x00000100 */
#define DDRCTRL_DRAMTMG4_T_RRD_1   (0x2U << DDRCTRL_DRAMTMG4_T_RRD_Pos)  /*!< 0x00000200 */
#define DDRCTRL_DRAMTMG4_T_RRD_2   (0x4U << DDRCTRL_DRAMTMG4_T_RRD_Pos)  /*!< 0x00000400 */
#define DDRCTRL_DRAMTMG4_T_RRD_3   (0x8U << DDRCTRL_DRAMTMG4_T_RRD_Pos)  /*!< 0x00000800 */
#define DDRCTRL_DRAMTMG4_T_CCD_Pos (16U)
#define DDRCTRL_DRAMTMG4_T_CCD_Msk (0xFU << DDRCTRL_DRAMTMG4_T_CCD_Pos)  /*!< 0x000F0000 */
#define DDRCTRL_DRAMTMG4_T_CCD     DDRCTRL_DRAMTMG4_T_CCD_Msk            /*!< DDR4: tCCD_L: This is the minimum time between two reads or two writes for same bank group. */
#define DDRCTRL_DRAMTMG4_T_CCD_0   (0x1U << DDRCTRL_DRAMTMG4_T_CCD_Pos)  /*!< 0x00010000 */
#define DDRCTRL_DRAMTMG4_T_CCD_1   (0x2U << DDRCTRL_DRAMTMG4_T_CCD_Pos)  /*!< 0x00020000 */
#define DDRCTRL_DRAMTMG4_T_CCD_2   (0x4U << DDRCTRL_DRAMTMG4_T_CCD_Pos)  /*!< 0x00040000 */
#define DDRCTRL_DRAMTMG4_T_CCD_3   (0x8U << DDRCTRL_DRAMTMG4_T_CCD_Pos)  /*!< 0x00080000 */
#define DDRCTRL_DRAMTMG4_T_RCD_Pos (24U)
#define DDRCTRL_DRAMTMG4_T_RCD_Msk (0x1FU << DDRCTRL_DRAMTMG4_T_RCD_Pos) /*!< 0x1F000000 */
#define DDRCTRL_DRAMTMG4_T_RCD     DDRCTRL_DRAMTMG4_T_RCD_Msk            /*!< tRCD - tAL: Minimum time from activate to read or write command to same bank. */
#define DDRCTRL_DRAMTMG4_T_RCD_0   (0x1U << DDRCTRL_DRAMTMG4_T_RCD_Pos)  /*!< 0x01000000 */
#define DDRCTRL_DRAMTMG4_T_RCD_1   (0x2U << DDRCTRL_DRAMTMG4_T_RCD_Pos)  /*!< 0x02000000 */
#define DDRCTRL_DRAMTMG4_T_RCD_2   (0x4U << DDRCTRL_DRAMTMG4_T_RCD_Pos)  /*!< 0x04000000 */
#define DDRCTRL_DRAMTMG4_T_RCD_3   (0x8U << DDRCTRL_DRAMTMG4_T_RCD_Pos)  /*!< 0x08000000 */
#define DDRCTRL_DRAMTMG4_T_RCD_4   (0x10U << DDRCTRL_DRAMTMG4_T_RCD_Pos) /*!< 0x10000000 */

/***************  Bit definition for DDRCTRL_DRAMTMG5 register  ***************/
#define DDRCTRL_DRAMTMG5_T_CKE_Pos   (0U)
#define DDRCTRL_DRAMTMG5_T_CKE_Msk   (0x1FU << DDRCTRL_DRAMTMG5_T_CKE_Pos)   /*!< 0x0000001F */
#define DDRCTRL_DRAMTMG5_T_CKE       DDRCTRL_DRAMTMG5_T_CKE_Msk              /*!< Minimum number of cycles of CKE HIGH/LOW during power-down and self refresh. */
#define DDRCTRL_DRAMTMG5_T_CKE_0     (0x1U << DDRCTRL_DRAMTMG5_T_CKE_Pos)    /*!< 0x00000001 */
#define DDRCTRL_DRAMTMG5_T_CKE_1     (0x2U << DDRCTRL_DRAMTMG5_T_CKE_Pos)    /*!< 0x00000002 */
#define DDRCTRL_DRAMTMG5_T_CKE_2     (0x4U << DDRCTRL_DRAMTMG5_T_CKE_Pos)    /*!< 0x00000004 */
#define DDRCTRL_DRAMTMG5_T_CKE_3     (0x8U << DDRCTRL_DRAMTMG5_T_CKE_Pos)    /*!< 0x00000008 */
#define DDRCTRL_DRAMTMG5_T_CKE_4     (0x10U << DDRCTRL_DRAMTMG5_T_CKE_Pos)   /*!< 0x00000010 */
#define DDRCTRL_DRAMTMG5_T_CKESR_Pos (8U)
#define DDRCTRL_DRAMTMG5_T_CKESR_Msk (0x3FU << DDRCTRL_DRAMTMG5_T_CKESR_Pos) /*!< 0x00003F00 */
#define DDRCTRL_DRAMTMG5_T_CKESR     DDRCTRL_DRAMTMG5_T_CKESR_Msk            /*!< Minimum CKE low width for Self refresh or Self refresh power down entry to exit timing in memory clock cycles. */
#define DDRCTRL_DRAMTMG5_T_CKESR_0   (0x1U << DDRCTRL_DRAMTMG5_T_CKESR_Pos)  /*!< 0x00000100 */
#define DDRCTRL_DRAMTMG5_T_CKESR_1   (0x2U << DDRCTRL_DRAMTMG5_T_CKESR_Pos)  /*!< 0x00000200 */
#define DDRCTRL_DRAMTMG5_T_CKESR_2   (0x4U << DDRCTRL_DRAMTMG5_T_CKESR_Pos)  /*!< 0x00000400 */
#define DDRCTRL_DRAMTMG5_T_CKESR_3   (0x8U << DDRCTRL_DRAMTMG5_T_CKESR_Pos)  /*!< 0x00000800 */
#define DDRCTRL_DRAMTMG5_T_CKESR_4   (0x10U << DDRCTRL_DRAMTMG5_T_CKESR_Pos) /*!< 0x00001000 */
#define DDRCTRL_DRAMTMG5_T_CKESR_5   (0x20U << DDRCTRL_DRAMTMG5_T_CKESR_Pos) /*!< 0x00002000 */
#define DDRCTRL_DRAMTMG5_T_CKSRE_Pos (16U)
#define DDRCTRL_DRAMTMG5_T_CKSRE_Msk (0xFU << DDRCTRL_DRAMTMG5_T_CKSRE_Pos)  /*!< 0x000F0000 */
#define DDRCTRL_DRAMTMG5_T_CKSRE     DDRCTRL_DRAMTMG5_T_CKSRE_Msk            /*!< This is the time after Self Refresh Down Entry that CK is maintained as a valid clock. Specifies the clock disable delay after SRE. */
#define DDRCTRL_DRAMTMG5_T_CKSRE_0   (0x1U << DDRCTRL_DRAMTMG5_T_CKSRE_Pos)  /*!< 0x00010000 */
#define DDRCTRL_DRAMTMG5_T_CKSRE_1   (0x2U << DDRCTRL_DRAMTMG5_T_CKSRE_Pos)  /*!< 0x00020000 */
#define DDRCTRL_DRAMTMG5_T_CKSRE_2   (0x4U << DDRCTRL_DRAMTMG5_T_CKSRE_Pos)  /*!< 0x00040000 */
#define DDRCTRL_DRAMTMG5_T_CKSRE_3   (0x8U << DDRCTRL_DRAMTMG5_T_CKSRE_Pos)  /*!< 0x00080000 */
#define DDRCTRL_DRAMTMG5_T_CKSRX_Pos (24U)
#define DDRCTRL_DRAMTMG5_T_CKSRX_Msk (0xFU << DDRCTRL_DRAMTMG5_T_CKSRX_Pos)       /*!< 0x0F000000 */
#define DDRCTRL_DRAMTMG5_T_CKSRX     DDRCTRL_DRAMTMG5_T_CKSRX_Msk            /*!< This is the time before Self Refresh Exit that CK is maintained as a valid clock before issuing SRX. Specifies the clock stable time before SRX. */
#define DDRCTRL_DRAMTMG5_T_CKSRX_0   (0x1U << DDRCTRL_DRAMTMG5_T_CKSRX_Pos)  /*!< 0x01000000 */
#define DDRCTRL_DRAMTMG5_T_CKSRX_1   (0x2U << DDRCTRL_DRAMTMG5_T_CKSRX_Pos)  /*!< 0x02000000 */
#define DDRCTRL_DRAMTMG5_T_CKSRX_2   (0x4U << DDRCTRL_DRAMTMG5_T_CKSRX_Pos)  /*!< 0x04000000 */
#define DDRCTRL_DRAMTMG5_T_CKSRX_3   (0x8U << DDRCTRL_DRAMTMG5_T_CKSRX_Pos)  /*!< 0x08000000 */

/***************  Bit definition for DDRCTRL_DRAMTMG6 register  ***************/
#define DDRCTRL_DRAMTMG6_T_CKCSX_Pos  (0U)
#define DDRCTRL_DRAMTMG6_T_CKCSX_Msk  (0xFU << DDRCTRL_DRAMTMG6_T_CKCSX_Pos)  /*!< 0x0000000F */
#define DDRCTRL_DRAMTMG6_T_CKCSX      DDRCTRL_DRAMTMG6_T_CKCSX_Msk            /*!< This is the time before Clock Stop Exit that CK is maintained as a valid clock before issuing Clock Stop Exit. Specifies the clock stable time before next command after Clock Stop Exit. */
#define DDRCTRL_DRAMTMG6_T_CKCSX_0    (0x1U << DDRCTRL_DRAMTMG6_T_CKCSX_Pos)  /*!< 0x00000001 */
#define DDRCTRL_DRAMTMG6_T_CKCSX_1    (0x2U << DDRCTRL_DRAMTMG6_T_CKCSX_Pos)  /*!< 0x00000002 */
#define DDRCTRL_DRAMTMG6_T_CKCSX_2    (0x4U << DDRCTRL_DRAMTMG6_T_CKCSX_Pos)  /*!< 0x00000004 */
#define DDRCTRL_DRAMTMG6_T_CKCSX_3    (0x8U << DDRCTRL_DRAMTMG6_T_CKCSX_Pos)  /*!< 0x00000008 */
#define DDRCTRL_DRAMTMG6_T_CKDPDX_Pos (16U)
#define DDRCTRL_DRAMTMG6_T_CKDPDX_Msk (0xFU << DDRCTRL_DRAMTMG6_T_CKDPDX_Pos) /*!< 0x000F0000 */
#define DDRCTRL_DRAMTMG6_T_CKDPDX     DDRCTRL_DRAMTMG6_T_CKDPDX_Msk           /*!< This is the time before Deep Power Down Exit that CK is maintained as a valid clock before issuing DPDX. Specifies the clock stable time before DPDX. */
#define DDRCTRL_DRAMTMG6_T_CKDPDX_0   (0x1U << DDRCTRL_DRAMTMG6_T_CKDPDX_Pos) /*!< 0x00010000 */
#define DDRCTRL_DRAMTMG6_T_CKDPDX_1   (0x2U << DDRCTRL_DRAMTMG6_T_CKDPDX_Pos) /*!< 0x00020000 */
#define DDRCTRL_DRAMTMG6_T_CKDPDX_2   (0x4U << DDRCTRL_DRAMTMG6_T_CKDPDX_Pos) /*!< 0x00040000 */
#define DDRCTRL_DRAMTMG6_T_CKDPDX_3   (0x8U << DDRCTRL_DRAMTMG6_T_CKDPDX_Pos) /*!< 0x00080000 */
#define DDRCTRL_DRAMTMG6_T_CKDPDE_Pos (24U)
#define DDRCTRL_DRAMTMG6_T_CKDPDE_Msk (0xFU << DDRCTRL_DRAMTMG6_T_CKDPDE_Pos) /*!< 0x0F000000 */
#define DDRCTRL_DRAMTMG6_T_CKDPDE     DDRCTRL_DRAMTMG6_T_CKDPDE_Msk           /*!< This is the time after Deep Power Down Entry that CK is maintained as a valid clock. Specifies the clock disable delay after DPDE. */
#define DDRCTRL_DRAMTMG6_T_CKDPDE_0   (0x1U << DDRCTRL_DRAMTMG6_T_CKDPDE_Pos) /*!< 0x01000000 */
#define DDRCTRL_DRAMTMG6_T_CKDPDE_1   (0x2U << DDRCTRL_DRAMTMG6_T_CKDPDE_Pos) /*!< 0x02000000 */
#define DDRCTRL_DRAMTMG6_T_CKDPDE_2   (0x4U << DDRCTRL_DRAMTMG6_T_CKDPDE_Pos) /*!< 0x04000000 */
#define DDRCTRL_DRAMTMG6_T_CKDPDE_3   (0x8U << DDRCTRL_DRAMTMG6_T_CKDPDE_Pos) /*!< 0x08000000 */

/***************  Bit definition for DDRCTRL_DRAMTMG7 register  ***************/
#define DDRCTRL_DRAMTMG7_T_CKPDX_Pos (0U)
#define DDRCTRL_DRAMTMG7_T_CKPDX_Msk (0xFU << DDRCTRL_DRAMTMG7_T_CKPDX_Pos) /*!< 0x0000000F */
#define DDRCTRL_DRAMTMG7_T_CKPDX     DDRCTRL_DRAMTMG7_T_CKPDX_Msk           /*!< This is the time before Power Down Exit that CK is maintained as a valid clock before issuing PDX. Specifies the clock stable time before PDX. */
#define DDRCTRL_DRAMTMG7_T_CKPDX_0   (0x1U << DDRCTRL_DRAMTMG7_T_CKPDX_Pos) /*!< 0x00000001 */
#define DDRCTRL_DRAMTMG7_T_CKPDX_1   (0x2U << DDRCTRL_DRAMTMG7_T_CKPDX_Pos) /*!< 0x00000002 */
#define DDRCTRL_DRAMTMG7_T_CKPDX_2   (0x4U << DDRCTRL_DRAMTMG7_T_CKPDX_Pos) /*!< 0x00000004 */
#define DDRCTRL_DRAMTMG7_T_CKPDX_3   (0x8U << DDRCTRL_DRAMTMG7_T_CKPDX_Pos) /*!< 0x00000008 */
#define DDRCTRL_DRAMTMG7_T_CKPDE_Pos (8U)
#define DDRCTRL_DRAMTMG7_T_CKPDE_Msk (0xFU << DDRCTRL_DRAMTMG7_T_CKPDE_Pos) /*!< 0x00000F00 */
#define DDRCTRL_DRAMTMG7_T_CKPDE     DDRCTRL_DRAMTMG7_T_CKPDE_Msk           /*!< This is the time after Power Down Entry that CK is maintained as a valid clock. Specifies the clock disable delay after PDE. */
#define DDRCTRL_DRAMTMG7_T_CKPDE_0   (0x1U << DDRCTRL_DRAMTMG7_T_CKPDE_Pos) /*!< 0x00000100 */
#define DDRCTRL_DRAMTMG7_T_CKPDE_1   (0x2U << DDRCTRL_DRAMTMG7_T_CKPDE_Pos) /*!< 0x00000200 */
#define DDRCTRL_DRAMTMG7_T_CKPDE_2   (0x4U << DDRCTRL_DRAMTMG7_T_CKPDE_Pos) /*!< 0x00000400 */
#define DDRCTRL_DRAMTMG7_T_CKPDE_3   (0x8U << DDRCTRL_DRAMTMG7_T_CKPDE_Pos) /*!< 0x00000800 */

/***************  Bit definition for DDRCTRL_DRAMTMG8 register  ***************/
#define DDRCTRL_DRAMTMG8_T_XS_X32_Pos     (0U)
#define DDRCTRL_DRAMTMG8_T_XS_X32_Msk     (0x7FU << DDRCTRL_DRAMTMG8_T_XS_X32_Pos)     /*!< 0x0000007F */
#define DDRCTRL_DRAMTMG8_T_XS_X32         DDRCTRL_DRAMTMG8_T_XS_X32_Msk                /*!< tXS: Exit Self Refresh to commands not requiring a locked DLL. */
#define DDRCTRL_DRAMTMG8_T_XS_X32_0       (0x1U << DDRCTRL_DRAMTMG8_T_XS_X32_Pos)      /*!< 0x00000001 */
#define DDRCTRL_DRAMTMG8_T_XS_X32_1       (0x2U << DDRCTRL_DRAMTMG8_T_XS_X32_Pos)      /*!< 0x00000002 */
#define DDRCTRL_DRAMTMG8_T_XS_X32_2       (0x4U << DDRCTRL_DRAMTMG8_T_XS_X32_Pos)      /*!< 0x00000004 */
#define DDRCTRL_DRAMTMG8_T_XS_X32_3       (0x8U << DDRCTRL_DRAMTMG8_T_XS_X32_Pos)      /*!< 0x00000008 */
#define DDRCTRL_DRAMTMG8_T_XS_X32_4       (0x10U << DDRCTRL_DRAMTMG8_T_XS_X32_Pos)     /*!< 0x00000010 */
#define DDRCTRL_DRAMTMG8_T_XS_X32_5       (0x20U << DDRCTRL_DRAMTMG8_T_XS_X32_Pos)     /*!< 0x00000020 */
#define DDRCTRL_DRAMTMG8_T_XS_X32_6       (0x40U << DDRCTRL_DRAMTMG8_T_XS_X32_Pos)     /*!< 0x00000040 */
#define DDRCTRL_DRAMTMG8_T_XS_DLL_X32_Pos (8U)
#define DDRCTRL_DRAMTMG8_T_XS_DLL_X32_Msk (0x7FU << DDRCTRL_DRAMTMG8_T_XS_DLL_X32_Pos) /*!< 0x00007F00 */
#define DDRCTRL_DRAMTMG8_T_XS_DLL_X32     DDRCTRL_DRAMTMG8_T_XS_DLL_X32_Msk            /*!< tXSDLL: Exit Self Refresh to the commands requiring a locked DLL. */
#define DDRCTRL_DRAMTMG8_T_XS_DLL_X32_0   (0x1U << DDRCTRL_DRAMTMG8_T_XS_DLL_X32_Pos)  /*!< 0x00000100 */
#define DDRCTRL_DRAMTMG8_T_XS_DLL_X32_1   (0x2U << DDRCTRL_DRAMTMG8_T_XS_DLL_X32_Pos)  /*!< 0x00000200 */
#define DDRCTRL_DRAMTMG8_T_XS_DLL_X32_2   (0x4U << DDRCTRL_DRAMTMG8_T_XS_DLL_X32_Pos)  /*!< 0x00000400 */
#define DDRCTRL_DRAMTMG8_T_XS_DLL_X32_3   (0x8U << DDRCTRL_DRAMTMG8_T_XS_DLL_X32_Pos)  /*!< 0x00000800 */
#define DDRCTRL_DRAMTMG8_T_XS_DLL_X32_4   (0x10U << DDRCTRL_DRAMTMG8_T_XS_DLL_X32_Pos) /*!< 0x00001000 */
#define DDRCTRL_DRAMTMG8_T_XS_DLL_X32_5   (0x20U << DDRCTRL_DRAMTMG8_T_XS_DLL_X32_Pos) /*!< 0x00002000 */
#define DDRCTRL_DRAMTMG8_T_XS_DLL_X32_6   (0x40U << DDRCTRL_DRAMTMG8_T_XS_DLL_X32_Pos) /*!< 0x00004000 */

/**************  Bit definition for DDRCTRL_DRAMTMG14 register  ***************/
#define DDRCTRL_DRAMTMG14_T_XSR_Pos (0U)
#define DDRCTRL_DRAMTMG14_T_XSR_Msk (0xFFFU << DDRCTRL_DRAMTMG14_T_XSR_Pos) /*!< 0x00000FFF */
#define DDRCTRL_DRAMTMG14_T_XSR     DDRCTRL_DRAMTMG14_T_XSR_Msk             /*!< tXSR: Exit Self Refresh to any command. */
#define DDRCTRL_DRAMTMG14_T_XSR_0   (0x1U << DDRCTRL_DRAMTMG14_T_XSR_Pos)   /*!< 0x00000001 */
#define DDRCTRL_DRAMTMG14_T_XSR_1   (0x2U << DDRCTRL_DRAMTMG14_T_XSR_Pos)   /*!< 0x00000002 */
#define DDRCTRL_DRAMTMG14_T_XSR_2   (0x4U << DDRCTRL_DRAMTMG14_T_XSR_Pos)   /*!< 0x00000004 */
#define DDRCTRL_DRAMTMG14_T_XSR_3   (0x8U << DDRCTRL_DRAMTMG14_T_XSR_Pos)   /*!< 0x00000008 */
#define DDRCTRL_DRAMTMG14_T_XSR_4   (0x10U << DDRCTRL_DRAMTMG14_T_XSR_Pos)  /*!< 0x00000010 */
#define DDRCTRL_DRAMTMG14_T_XSR_5   (0x20U << DDRCTRL_DRAMTMG14_T_XSR_Pos)  /*!< 0x00000020 */
#define DDRCTRL_DRAMTMG14_T_XSR_6   (0x40U << DDRCTRL_DRAMTMG14_T_XSR_Pos)  /*!< 0x00000040 */
#define DDRCTRL_DRAMTMG14_T_XSR_7   (0x80U << DDRCTRL_DRAMTMG14_T_XSR_Pos)  /*!< 0x00000080 */
#define DDRCTRL_DRAMTMG14_T_XSR_8   (0x100U << DDRCTRL_DRAMTMG14_T_XSR_Pos) /*!< 0x00000100 */
#define DDRCTRL_DRAMTMG14_T_XSR_9   (0x200U << DDRCTRL_DRAMTMG14_T_XSR_Pos) /*!< 0x00000200 */
#define DDRCTRL_DRAMTMG14_T_XSR_10  (0x400U << DDRCTRL_DRAMTMG14_T_XSR_Pos) /*!< 0x00000400 */
#define DDRCTRL_DRAMTMG14_T_XSR_11  (0x800U << DDRCTRL_DRAMTMG14_T_XSR_Pos) /*!< 0x00000800 */

/**************  Bit definition for DDRCTRL_DRAMTMG15 register  ***************/
#define DDRCTRL_DRAMTMG15_T_STAB_X32_Pos       (0U)
#define DDRCTRL_DRAMTMG15_T_STAB_X32_Msk       (0xFFU << DDRCTRL_DRAMTMG15_T_STAB_X32_Pos)      /*!< 0x000000FF */
#define DDRCTRL_DRAMTMG15_T_STAB_X32           DDRCTRL_DRAMTMG15_T_STAB_X32_Msk                 /*!< tSTAB: Stabilization time. */
#define DDRCTRL_DRAMTMG15_T_STAB_X32_0         (0x1U << DDRCTRL_DRAMTMG15_T_STAB_X32_Pos)       /*!< 0x00000001 */
#define DDRCTRL_DRAMTMG15_T_STAB_X32_1         (0x2U << DDRCTRL_DRAMTMG15_T_STAB_X32_Pos)       /*!< 0x00000002 */
#define DDRCTRL_DRAMTMG15_T_STAB_X32_2         (0x4U << DDRCTRL_DRAMTMG15_T_STAB_X32_Pos)       /*!< 0x00000004 */
#define DDRCTRL_DRAMTMG15_T_STAB_X32_3         (0x8U << DDRCTRL_DRAMTMG15_T_STAB_X32_Pos)       /*!< 0x00000008 */
#define DDRCTRL_DRAMTMG15_T_STAB_X32_4         (0x10U << DDRCTRL_DRAMTMG15_T_STAB_X32_Pos)      /*!< 0x00000010 */
#define DDRCTRL_DRAMTMG15_T_STAB_X32_5         (0x20U << DDRCTRL_DRAMTMG15_T_STAB_X32_Pos)      /*!< 0x00000020 */
#define DDRCTRL_DRAMTMG15_T_STAB_X32_6         (0x40U << DDRCTRL_DRAMTMG15_T_STAB_X32_Pos)      /*!< 0x00000040 */
#define DDRCTRL_DRAMTMG15_T_STAB_X32_7         (0x80U << DDRCTRL_DRAMTMG15_T_STAB_X32_Pos)      /*!< 0x00000080 */
#define DDRCTRL_DRAMTMG15_EN_DFI_LP_T_STAB_Pos (31U)
#define DDRCTRL_DRAMTMG15_EN_DFI_LP_T_STAB_Msk (0x1U << DDRCTRL_DRAMTMG15_EN_DFI_LP_T_STAB_Pos) /*!< 0x80000000 */
#define DDRCTRL_DRAMTMG15_EN_DFI_LP_T_STAB     DDRCTRL_DRAMTMG15_EN_DFI_LP_T_STAB_Msk           /*!< - 1 - Enable using tSTAB when exiting DFI LP. Needs to be set when the PHY is stopping the clock during DFI LP to save maximum power. */

/****************  Bit definition for DDRCTRL_ZQCTL0 register  ****************/
#define DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_Pos     (0U)
#define DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_Msk     (0x3FFU << DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_Pos)   /*!< 0x000003FF */
#define DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP         DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_Msk               /*!< tZQCS for DDR3/DD4/LPDDR2/LPDDR3, tZQLAT for LPDDR4: Number of DFI clock cycles of NOP required after a ZQCS (ZQ calibration short)/MPC(ZQ Latch) command is issued to SDRAM. */
#define DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_0       (0x1U << DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_Pos)     /*!< 0x00000001 */
#define DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_1       (0x2U << DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_Pos)     /*!< 0x00000002 */
#define DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_2       (0x4U << DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_Pos)     /*!< 0x00000004 */
#define DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_3       (0x8U << DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_Pos)     /*!< 0x00000008 */
#define DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_4       (0x10U << DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_Pos)    /*!< 0x00000010 */
#define DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_5       (0x20U << DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_Pos)    /*!< 0x00000020 */
#define DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_6       (0x40U << DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_Pos)    /*!< 0x00000040 */
#define DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_7       (0x80U << DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_Pos)    /*!< 0x00000080 */
#define DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_8       (0x100U << DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_Pos)   /*!< 0x00000100 */
#define DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_9       (0x200U << DDRCTRL_ZQCTL0_T_ZQ_SHORT_NOP_Pos)   /*!< 0x00000200 */
#define DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_Pos      (16U)
#define DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_Msk      (0x7FFU << DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_Pos)    /*!< 0x07FF0000 */
#define DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP          DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_Msk                /*!< tZQoper for DDR3/DDR4, tZQCL for LPDDR2/LPDDR3, tZQCAL for LPDDR4: Number of DFI clock cycles of NOP required after a ZQCL (ZQ calibration long)/MPC(ZQ Start) command is issued to SDRAM. */
#define DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_0        (0x1U << DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_Pos)      /*!< 0x00010000 */
#define DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_1        (0x2U << DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_Pos)      /*!< 0x00020000 */
#define DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_2        (0x4U << DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_Pos)      /*!< 0x00040000 */
#define DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_3        (0x8U << DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_Pos)      /*!< 0x00080000 */
#define DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_4        (0x10U << DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_Pos)     /*!< 0x00100000 */
#define DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_5        (0x20U << DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_Pos)     /*!< 0x00200000 */
#define DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_6        (0x40U << DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_Pos)     /*!< 0x00400000 */
#define DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_7        (0x80U << DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_Pos)     /*!< 0x00800000 */
#define DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_8        (0x100U << DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_Pos)    /*!< 0x01000000 */
#define DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_9        (0x200U << DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_Pos)    /*!< 0x02000000 */
#define DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_10       (0x400U << DDRCTRL_ZQCTL0_T_ZQ_LONG_NOP_Pos)    /*!< 0x04000000 */
#define DDRCTRL_ZQCTL0_ZQ_RESISTOR_SHARED_Pos (29U)
#define DDRCTRL_ZQCTL0_ZQ_RESISTOR_SHARED_Msk (0x1U << DDRCTRL_ZQCTL0_ZQ_RESISTOR_SHARED_Pos) /*!< 0x20000000 */
#define DDRCTRL_ZQCTL0_ZQ_RESISTOR_SHARED     DDRCTRL_ZQCTL0_ZQ_RESISTOR_SHARED_Msk           /*!< - 1 - Denotes that ZQ resistor is shared between ranks. Means ZQinit/ZQCL/ZQCS/MPC(ZQ calibration) commands are sent to one rank at a time with tZQinit/tZQCL/tZQCS/tZQCAL/tZQLAT timing met between commands so that commands to different ranks do not overlap. */
#define DDRCTRL_ZQCTL0_DIS_SRX_ZQCL_Pos       (30U)
#define DDRCTRL_ZQCTL0_DIS_SRX_ZQCL_Msk       (0x1U << DDRCTRL_ZQCTL0_DIS_SRX_ZQCL_Pos)       /*!< 0x40000000 */
#define DDRCTRL_ZQCTL0_DIS_SRX_ZQCL           DDRCTRL_ZQCTL0_DIS_SRX_ZQCL_Msk                 /*!< - 1 - Disable issuing of ZQCL/MPC(ZQ calibration) command at Self-Refresh/SR-Powerdown exit. Only applicable when run in DDR3 or DDR4 or LPDDR2 or LPDDR3 or LPDDR4 mode. */
#define DDRCTRL_ZQCTL0_DIS_AUTO_ZQ_Pos        (31U)
#define DDRCTRL_ZQCTL0_DIS_AUTO_ZQ_Msk        (0x1U << DDRCTRL_ZQCTL0_DIS_AUTO_ZQ_Pos)        /*!< 0x80000000 */
#define DDRCTRL_ZQCTL0_DIS_AUTO_ZQ            DDRCTRL_ZQCTL0_DIS_AUTO_ZQ_Msk                  /*!< - 1 - Disable DDRCTRL generation of ZQCS/MPC(ZQ calibration) command. Register DBGCMD.zq_calib_short can be used instead to issue ZQ calibration request from APB module. */

/****************  Bit definition for DDRCTRL_ZQCTL1 register  ****************/
#define DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Pos (0U)
#define DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Msk (0xFFFFFU << DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Pos) /*!< 0x000FFFFF */
#define DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024     DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Msk               /*!< Average interval to wait between automatically issuing ZQCS (ZQ calibration short)/MPC(ZQ calibration) commands to DDR3/DDR4/LPDDR2/LPDDR3/LPDDR4 devices. */
#define DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_0   (0x1U << DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Pos)     /*!< 0x00000001 */
#define DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_1   (0x2U << DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Pos)     /*!< 0x00000002 */
#define DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_2   (0x4U << DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Pos)     /*!< 0x00000004 */
#define DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_3   (0x8U << DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Pos)     /*!< 0x00000008 */
#define DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_4   (0x10U << DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Pos)    /*!< 0x00000010 */
#define DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_5   (0x20U << DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Pos)    /*!< 0x00000020 */
#define DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_6   (0x40U << DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Pos)    /*!< 0x00000040 */
#define DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_7   (0x80U << DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Pos)    /*!< 0x00000080 */
#define DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_8   (0x100U << DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Pos)   /*!< 0x00000100 */
#define DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_9   (0x200U << DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Pos)   /*!< 0x00000200 */
#define DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_10  (0x400U << DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Pos)   /*!< 0x00000400 */
#define DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_11  (0x800U << DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Pos)   /*!< 0x00000800 */
#define DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_12  (0x1000U << DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Pos)  /*!< 0x00001000 */
#define DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_13  (0x2000U << DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Pos)  /*!< 0x00002000 */
#define DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_14  (0x4000U << DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Pos)  /*!< 0x00004000 */
#define DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_15  (0x8000U << DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Pos)  /*!< 0x00008000 */
#define DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_16  (0x10000U << DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Pos) /*!< 0x00010000 */
#define DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_17  (0x20000U << DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Pos) /*!< 0x00020000 */
#define DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_18  (0x40000U << DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Pos) /*!< 0x00040000 */
#define DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_19  (0x80000U << DDRCTRL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_Pos) /*!< 0x00080000 */
#define DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_Pos            (20U)
#define DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_Msk            (0x3FFU << DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_Pos)              /*!< 0x3FF00000 */
#define DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP                DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_Msk                          /*!< tZQReset: Number of DFI clock cycles of NOP required after a ZQReset (ZQ calibration Reset) command is issued to SDRAM. */
#define DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_0              (0x1U << DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_Pos)                /*!< 0x00100000 */
#define DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_1              (0x2U << DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_Pos)                /*!< 0x00200000 */
#define DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_2              (0x4U << DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_Pos)                /*!< 0x00400000 */
#define DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_3              (0x8U << DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_Pos)                /*!< 0x00800000 */
#define DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_4              (0x10U << DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_Pos)               /*!< 0x01000000 */
#define DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_5              (0x20U << DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_Pos)               /*!< 0x02000000 */
#define DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_6              (0x40U << DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_Pos)               /*!< 0x04000000 */
#define DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_7              (0x80U << DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_Pos)               /*!< 0x08000000 */
#define DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_8              (0x100U << DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_Pos)              /*!< 0x10000000 */
#define DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_9              (0x200U << DDRCTRL_ZQCTL1_T_ZQ_RESET_NOP_Pos)              /*!< 0x20000000 */

/****************  Bit definition for DDRCTRL_ZQCTL2 register  ****************/
#define DDRCTRL_ZQCTL2_ZQ_RESET_Pos (0U)
#define DDRCTRL_ZQCTL2_ZQ_RESET_Msk (0x1U << DDRCTRL_ZQCTL2_ZQ_RESET_Pos) /*!< 0x00000001 */
#define DDRCTRL_ZQCTL2_ZQ_RESET     DDRCTRL_ZQCTL2_ZQ_RESET_Msk           /*!< Setting this register bit to 1 triggers a ZQ Reset operation. When the ZQ Reset operation is complete, the DDRCTRL automatically clears this bit. It is recommended NOT to set this register bit if in Init, in Self-Refresh(except LPDDR4) or SR-Powerdown(LPDDR4) or Deep power-down operating modes. */

/****************  Bit definition for DDRCTRL_ZQSTAT register  ****************/
#define DDRCTRL_ZQSTAT_ZQ_RESET_BUSY_Pos (0U)
#define DDRCTRL_ZQSTAT_ZQ_RESET_BUSY_Msk (0x1U << DDRCTRL_ZQSTAT_ZQ_RESET_BUSY_Pos) /*!< 0x00000001 */
#define DDRCTRL_ZQSTAT_ZQ_RESET_BUSY     DDRCTRL_ZQSTAT_ZQ_RESET_BUSY_Msk           /*!< SoC core may initiate a ZQ Reset operation only if this signal is low. This signal goes high in the clock after the DDRCTRL accepts the ZQ Reset request. It goes low when the ZQ Reset command is issued to the SDRAM and the associated NOP period is over. It is recommended not to perform ZQ Reset commands when this signal is high. */

/***************  Bit definition for DDRCTRL_DFITMG0 register  ****************/
#define DDRCTRL_DFITMG0_DFI_TPHY_WRLAT_Pos   (0U)
#define DDRCTRL_DFITMG0_DFI_TPHY_WRLAT_Msk   (0x3FU << DDRCTRL_DFITMG0_DFI_TPHY_WRLAT_Pos)   /*!< 0x0000003F */
#define DDRCTRL_DFITMG0_DFI_TPHY_WRLAT       DDRCTRL_DFITMG0_DFI_TPHY_WRLAT_Msk              /*!< Write latency */
#define DDRCTRL_DFITMG0_DFI_TPHY_WRLAT_0     (0x1U << DDRCTRL_DFITMG0_DFI_TPHY_WRLAT_Pos)    /*!< 0x00000001 */
#define DDRCTRL_DFITMG0_DFI_TPHY_WRLAT_1     (0x2U << DDRCTRL_DFITMG0_DFI_TPHY_WRLAT_Pos)    /*!< 0x00000002 */
#define DDRCTRL_DFITMG0_DFI_TPHY_WRLAT_2     (0x4U << DDRCTRL_DFITMG0_DFI_TPHY_WRLAT_Pos)    /*!< 0x00000004 */
#define DDRCTRL_DFITMG0_DFI_TPHY_WRLAT_3     (0x8U << DDRCTRL_DFITMG0_DFI_TPHY_WRLAT_Pos)    /*!< 0x00000008 */
#define DDRCTRL_DFITMG0_DFI_TPHY_WRLAT_4     (0x10U << DDRCTRL_DFITMG0_DFI_TPHY_WRLAT_Pos)   /*!< 0x00000010 */
#define DDRCTRL_DFITMG0_DFI_TPHY_WRLAT_5     (0x20U << DDRCTRL_DFITMG0_DFI_TPHY_WRLAT_Pos)   /*!< 0x00000020 */
#define DDRCTRL_DFITMG0_DFI_TPHY_WRDATA_Pos  (8U)
#define DDRCTRL_DFITMG0_DFI_TPHY_WRDATA_Msk  (0x3FU << DDRCTRL_DFITMG0_DFI_TPHY_WRDATA_Pos)  /*!< 0x00003F00 */
#define DDRCTRL_DFITMG0_DFI_TPHY_WRDATA      DDRCTRL_DFITMG0_DFI_TPHY_WRDATA_Msk             /*!< Specifies the number of clock cycles between when dfi_wrdata_en is asserted to when the associated write data is driven on the dfi_wrdata signal. This corresponds to the DFI timing parameter tphy_wrdata. Refer to PHY specification for correct value. Note, max supported value is 8. */
#define DDRCTRL_DFITMG0_DFI_TPHY_WRDATA_0    (0x1U << DDRCTRL_DFITMG0_DFI_TPHY_WRDATA_Pos)   /*!< 0x00000100 */
#define DDRCTRL_DFITMG0_DFI_TPHY_WRDATA_1    (0x2U << DDRCTRL_DFITMG0_DFI_TPHY_WRDATA_Pos)   /*!< 0x00000200 */
#define DDRCTRL_DFITMG0_DFI_TPHY_WRDATA_2    (0x4U << DDRCTRL_DFITMG0_DFI_TPHY_WRDATA_Pos)   /*!< 0x00000400 */
#define DDRCTRL_DFITMG0_DFI_TPHY_WRDATA_3    (0x8U << DDRCTRL_DFITMG0_DFI_TPHY_WRDATA_Pos)   /*!< 0x00000800 */
#define DDRCTRL_DFITMG0_DFI_TPHY_WRDATA_4    (0x10U << DDRCTRL_DFITMG0_DFI_TPHY_WRDATA_Pos)  /*!< 0x00001000 */
#define DDRCTRL_DFITMG0_DFI_TPHY_WRDATA_5    (0x20U << DDRCTRL_DFITMG0_DFI_TPHY_WRDATA_Pos)  /*!< 0x00002000 */
#define DDRCTRL_DFITMG0_DFI_T_RDDATA_EN_Pos  (16U)
#define DDRCTRL_DFITMG0_DFI_T_RDDATA_EN_Msk  (0x7FU << DDRCTRL_DFITMG0_DFI_T_RDDATA_EN_Pos)  /*!< 0x007F0000 */
#define DDRCTRL_DFITMG0_DFI_T_RDDATA_EN      DDRCTRL_DFITMG0_DFI_T_RDDATA_EN_Msk             /*!< Time from the assertion of a read command on the DFI interface to the assertion of the dfi_rddata_en signal. */
#define DDRCTRL_DFITMG0_DFI_T_RDDATA_EN_0    (0x1U << DDRCTRL_DFITMG0_DFI_T_RDDATA_EN_Pos)   /*!< 0x00010000 */
#define DDRCTRL_DFITMG0_DFI_T_RDDATA_EN_1    (0x2U << DDRCTRL_DFITMG0_DFI_T_RDDATA_EN_Pos)   /*!< 0x00020000 */
#define DDRCTRL_DFITMG0_DFI_T_RDDATA_EN_2    (0x4U << DDRCTRL_DFITMG0_DFI_T_RDDATA_EN_Pos)   /*!< 0x00040000 */
#define DDRCTRL_DFITMG0_DFI_T_RDDATA_EN_3    (0x8U << DDRCTRL_DFITMG0_DFI_T_RDDATA_EN_Pos)   /*!< 0x00080000 */
#define DDRCTRL_DFITMG0_DFI_T_RDDATA_EN_4    (0x10U << DDRCTRL_DFITMG0_DFI_T_RDDATA_EN_Pos)  /*!< 0x00100000 */
#define DDRCTRL_DFITMG0_DFI_T_RDDATA_EN_5    (0x20U << DDRCTRL_DFITMG0_DFI_T_RDDATA_EN_Pos)  /*!< 0x00200000 */
#define DDRCTRL_DFITMG0_DFI_T_RDDATA_EN_6    (0x40U << DDRCTRL_DFITMG0_DFI_T_RDDATA_EN_Pos)  /*!< 0x00400000 */
#define DDRCTRL_DFITMG0_DFI_T_CTRL_DELAY_Pos (24U)
#define DDRCTRL_DFITMG0_DFI_T_CTRL_DELAY_Msk (0x1FU << DDRCTRL_DFITMG0_DFI_T_CTRL_DELAY_Pos) /*!< 0x1F000000 */
#define DDRCTRL_DFITMG0_DFI_T_CTRL_DELAY     DDRCTRL_DFITMG0_DFI_T_CTRL_DELAY_Msk            /*!< Specifies the number of DFI clock cycles after an assertion or de-assertion of the DFI control signals that the control signals at the PHY-DRAM interface reflect the assertion or de-assertion. If the DFI clock and the memory clock are not phase-aligned, this timing parameter should be rounded up to the next integer value. Note that if using RDIMM/LRDIMM, it is necessary to increment this parameter by RDIMM\qs/LRDIMM\qs extra cycle of latency in terms of DFI clock. */
#define DDRCTRL_DFITMG0_DFI_T_CTRL_DELAY_0   (0x1U << DDRCTRL_DFITMG0_DFI_T_CTRL_DELAY_Pos)  /*!< 0x01000000 */
#define DDRCTRL_DFITMG0_DFI_T_CTRL_DELAY_1   (0x2U << DDRCTRL_DFITMG0_DFI_T_CTRL_DELAY_Pos)  /*!< 0x02000000 */
#define DDRCTRL_DFITMG0_DFI_T_CTRL_DELAY_2   (0x4U << DDRCTRL_DFITMG0_DFI_T_CTRL_DELAY_Pos)  /*!< 0x04000000 */
#define DDRCTRL_DFITMG0_DFI_T_CTRL_DELAY_3   (0x8U << DDRCTRL_DFITMG0_DFI_T_CTRL_DELAY_Pos)  /*!< 0x08000000 */
#define DDRCTRL_DFITMG0_DFI_T_CTRL_DELAY_4   (0x10U << DDRCTRL_DFITMG0_DFI_T_CTRL_DELAY_Pos) /*!< 0x10000000 */

/***************  Bit definition for DDRCTRL_DFITMG1 register  ****************/
#define DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_ENABLE_Pos  (0U)
#define DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_ENABLE_Msk  (0x1FU << DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_ENABLE_Pos)  /*!< 0x0000001F */
#define DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_ENABLE      DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_ENABLE_Msk             /*!< Specifies the number of DFI clock cycles from the de-assertion of the dfi_dram_clk_disable signal on the DFI until the first valid rising edge of the clock to the DRAM memory devices, at the PHY-DRAM boundary. If the DFI clock and the memory clock are not phase aligned, this timing parameter should be rounded up to the next integer value. */
#define DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_ENABLE_0    (0x1U << DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_ENABLE_Pos)   /*!< 0x00000001 */
#define DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_ENABLE_1    (0x2U << DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_ENABLE_Pos)   /*!< 0x00000002 */
#define DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_ENABLE_2    (0x4U << DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_ENABLE_Pos)   /*!< 0x00000004 */
#define DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_ENABLE_3    (0x8U << DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_ENABLE_Pos)   /*!< 0x00000008 */
#define DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_ENABLE_4    (0x10U << DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_ENABLE_Pos)  /*!< 0x00000010 */
#define DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_DISABLE_Pos (8U)
#define DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_DISABLE_Msk (0x1FU << DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_DISABLE_Pos) /*!< 0x00001F00 */
#define DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_DISABLE     DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_DISABLE_Msk            /*!< Specifies the number of DFI clock cycles from the assertion of the dfi_dram_clk_disable signal on the DFI until the clock to the DRAM memory devices, at the PHY-DRAM boundary, maintains a low value. If the DFI clock and the memory clock are not phase aligned, this timing parameter should be rounded up to the next integer value. */
#define DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_DISABLE_0   (0x1U << DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_DISABLE_Pos)  /*!< 0x00000100 */
#define DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_DISABLE_1   (0x2U << DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_DISABLE_Pos)  /*!< 0x00000200 */
#define DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_DISABLE_2   (0x4U << DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_DISABLE_Pos)  /*!< 0x00000400 */
#define DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_DISABLE_3   (0x8U << DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_DISABLE_Pos)  /*!< 0x00000800 */
#define DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_DISABLE_4   (0x10U << DDRCTRL_DFITMG1_DFI_T_DRAM_CLK_DISABLE_Pos) /*!< 0x00001000 */
#define DDRCTRL_DFITMG1_DFI_T_WRDATA_DELAY_Pos     (16U)
#define DDRCTRL_DFITMG1_DFI_T_WRDATA_DELAY_Msk     (0x1FU << DDRCTRL_DFITMG1_DFI_T_WRDATA_DELAY_Pos)     /*!< 0x001F0000 */
#define DDRCTRL_DFITMG1_DFI_T_WRDATA_DELAY         DDRCTRL_DFITMG1_DFI_T_WRDATA_DELAY_Msk                /*!< Specifies the number of DFI clock cycles between when the dfi_wrdata_en */
#define DDRCTRL_DFITMG1_DFI_T_WRDATA_DELAY_0       (0x1U << DDRCTRL_DFITMG1_DFI_T_WRDATA_DELAY_Pos)      /*!< 0x00010000 */
#define DDRCTRL_DFITMG1_DFI_T_WRDATA_DELAY_1       (0x2U << DDRCTRL_DFITMG1_DFI_T_WRDATA_DELAY_Pos)      /*!< 0x00020000 */
#define DDRCTRL_DFITMG1_DFI_T_WRDATA_DELAY_2       (0x4U << DDRCTRL_DFITMG1_DFI_T_WRDATA_DELAY_Pos)      /*!< 0x00040000 */
#define DDRCTRL_DFITMG1_DFI_T_WRDATA_DELAY_3       (0x8U << DDRCTRL_DFITMG1_DFI_T_WRDATA_DELAY_Pos)      /*!< 0x00080000 */
#define DDRCTRL_DFITMG1_DFI_T_WRDATA_DELAY_4       (0x10U << DDRCTRL_DFITMG1_DFI_T_WRDATA_DELAY_Pos)     /*!< 0x00100000 */

/**************  Bit definition for DDRCTRL_DFILPCFG0 register  ***************/
#define DDRCTRL_DFILPCFG0_DFI_LP_EN_PD_Pos      (0U)
#define DDRCTRL_DFILPCFG0_DFI_LP_EN_PD_Msk      (0x1U << DDRCTRL_DFILPCFG0_DFI_LP_EN_PD_Pos)      /*!< 0x00000001 */
#define DDRCTRL_DFILPCFG0_DFI_LP_EN_PD          DDRCTRL_DFILPCFG0_DFI_LP_EN_PD_Msk                /*!< Enables DFI Low Power interface handshaking during Power Down Entry/Exit. */
#define DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_PD_Pos  (4U)
#define DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_PD_Msk  (0xFU << DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_PD_Pos)  /*!< 0x000000F0 */
#define DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_PD      DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_PD_Msk            /*!< Value in DFI clock cycles to drive on dfi_lp_wakeup signal when Power Down mode is entered. */
#define DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_PD_0    (0x1U << DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_PD_Pos)  /*!< 0x00000010 */
#define DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_PD_1    (0x2U << DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_PD_Pos)  /*!< 0x00000020 */
#define DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_PD_2    (0x4U << DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_PD_Pos)  /*!< 0x00000040 */
#define DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_PD_3    (0x8U << DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_PD_Pos)  /*!< 0x00000080 */
#define DDRCTRL_DFILPCFG0_DFI_LP_EN_SR_Pos      (8U)
#define DDRCTRL_DFILPCFG0_DFI_LP_EN_SR_Msk      (0x1U << DDRCTRL_DFILPCFG0_DFI_LP_EN_SR_Pos)      /*!< 0x00000100 */
#define DDRCTRL_DFILPCFG0_DFI_LP_EN_SR          DDRCTRL_DFILPCFG0_DFI_LP_EN_SR_Msk                /*!< Enables DFI Low Power interface handshaking during Self Refresh Entry/Exit. */
#define DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_SR_Pos  (12U)
#define DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_SR_Msk  (0xFU << DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_SR_Pos)  /*!< 0x0000F000 */
#define DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_SR      DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_SR_Msk            /*!< Value in DFI clpck cycles to drive on dfi_lp_wakeup signal when Self Refresh mode is entered. */
#define DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_SR_0    (0x1U << DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_SR_Pos)  /*!< 0x00001000 */
#define DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_SR_1    (0x2U << DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_SR_Pos)  /*!< 0x00002000 */
#define DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_SR_2    (0x4U << DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_SR_Pos)  /*!< 0x00004000 */
#define DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_SR_3    (0x8U << DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_SR_Pos)  /*!< 0x00008000 */
#define DDRCTRL_DFILPCFG0_DFI_LP_EN_DPD_Pos     (16U)
#define DDRCTRL_DFILPCFG0_DFI_LP_EN_DPD_Msk     (0x1U << DDRCTRL_DFILPCFG0_DFI_LP_EN_DPD_Pos)     /*!< 0x00010000 */
#define DDRCTRL_DFILPCFG0_DFI_LP_EN_DPD         DDRCTRL_DFILPCFG0_DFI_LP_EN_DPD_Msk               /*!< Enables DFI Low-power interface handshaking during Deep Power Down Entry/Exit. */
#define DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_DPD_Pos (20U)
#define DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_DPD_Msk (0xFU << DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_DPD_Pos) /*!< 0x00F00000 */
#define DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_DPD     DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_DPD_Msk           /*!< Value in DFI clock cycles to drive on dfi_lp_wakeup signal when Deep Power Down mode is entered. */
#define DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_DPD_0   (0x1U << DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_DPD_Pos) /*!< 0x00100000 */
#define DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_DPD_1   (0x2U << DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_DPD_Pos) /*!< 0x00200000 */
#define DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_DPD_2   (0x4U << DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_DPD_Pos) /*!< 0x00400000 */
#define DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_DPD_3   (0x8U << DDRCTRL_DFILPCFG0_DFI_LP_WAKEUP_DPD_Pos) /*!< 0x00800000 */
#define DDRCTRL_DFILPCFG0_DFI_TLP_RESP_Pos      (24U)
#define DDRCTRL_DFILPCFG0_DFI_TLP_RESP_Msk      (0x1FU << DDRCTRL_DFILPCFG0_DFI_TLP_RESP_Pos)     /*!< 0x1F000000 */
#define DDRCTRL_DFILPCFG0_DFI_TLP_RESP          DDRCTRL_DFILPCFG0_DFI_TLP_RESP_Msk                /*!< Setting in DFI clock cycles for DFI\qs tlp_resp time. */
#define DDRCTRL_DFILPCFG0_DFI_TLP_RESP_0        (0x1U << DDRCTRL_DFILPCFG0_DFI_TLP_RESP_Pos)      /*!< 0x01000000 */
#define DDRCTRL_DFILPCFG0_DFI_TLP_RESP_1        (0x2U << DDRCTRL_DFILPCFG0_DFI_TLP_RESP_Pos)      /*!< 0x02000000 */
#define DDRCTRL_DFILPCFG0_DFI_TLP_RESP_2        (0x4U << DDRCTRL_DFILPCFG0_DFI_TLP_RESP_Pos)      /*!< 0x04000000 */
#define DDRCTRL_DFILPCFG0_DFI_TLP_RESP_3        (0x8U << DDRCTRL_DFILPCFG0_DFI_TLP_RESP_Pos)      /*!< 0x08000000 */
#define DDRCTRL_DFILPCFG0_DFI_TLP_RESP_4        (0x10U << DDRCTRL_DFILPCFG0_DFI_TLP_RESP_Pos)     /*!< 0x10000000 */

/***************  Bit definition for DDRCTRL_DFIUPD0 register  ****************/
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_Pos     (0U)
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_Msk     (0x3FFU << DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_Pos)   /*!< 0x000003FF */
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN         DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_Msk               /*!< Specifies the minimum number of DFI clock cycles that the dfi_ctrlupd_req signal must be asserted. The DDRCTRL expects the PHY to respond within this time. If the PHY does not respond, the DDRCTRL de-asserts dfi_ctrlupd_req after dfi_t_ctrlup_min + 2 cycles. Lowest value to assign to this variable is 0x3. */
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_0       (0x1U << DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_Pos)     /*!< 0x00000001 */
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_1       (0x2U << DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_Pos)     /*!< 0x00000002 */
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_2       (0x4U << DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_Pos)     /*!< 0x00000004 */
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_3       (0x8U << DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_Pos)     /*!< 0x00000008 */
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_4       (0x10U << DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_Pos)    /*!< 0x00000010 */
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_5       (0x20U << DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_Pos)    /*!< 0x00000020 */
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_6       (0x40U << DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_Pos)    /*!< 0x00000040 */
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_7       (0x80U << DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_Pos)    /*!< 0x00000080 */
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_8       (0x100U << DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_Pos)   /*!< 0x00000100 */
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_9       (0x200U << DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MIN_Pos)   /*!< 0x00000200 */
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_Pos     (16U)
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_Msk     (0x3FFU << DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_Pos)   /*!< 0x03FF0000 */
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX         DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_Msk               /*!< Specifies the maximum number of DFI clock cycles that the dfi_ctrlupd_req signal can assert. Lowest value to assign to this variable is 0x40. */
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_0       (0x1U << DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_Pos)     /*!< 0x00010000 */
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_1       (0x2U << DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_Pos)     /*!< 0x00020000 */
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_2       (0x4U << DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_Pos)     /*!< 0x00040000 */
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_3       (0x8U << DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_Pos)     /*!< 0x00080000 */
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_4       (0x10U << DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_Pos)    /*!< 0x00100000 */
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_5       (0x20U << DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_Pos)    /*!< 0x00200000 */
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_6       (0x40U << DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_Pos)    /*!< 0x00400000 */
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_7       (0x80U << DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_Pos)    /*!< 0x00800000 */
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_8       (0x100U << DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_Pos)   /*!< 0x01000000 */
#define DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_9       (0x200U << DDRCTRL_DFIUPD0_DFI_T_CTRLUP_MAX_Pos)   /*!< 0x02000000 */
#define DDRCTRL_DFIUPD0_CTRLUPD_PRE_SRX_Pos      (29U)
#define DDRCTRL_DFIUPD0_CTRLUPD_PRE_SRX_Msk      (0x1U << DDRCTRL_DFIUPD0_CTRLUPD_PRE_SRX_Pos)      /*!< 0x20000000 */
#define DDRCTRL_DFIUPD0_CTRLUPD_PRE_SRX          DDRCTRL_DFIUPD0_CTRLUPD_PRE_SRX_Msk                /*!< Selects dfi_ctrlupd_req requirements at SRX: */
#define DDRCTRL_DFIUPD0_DIS_AUTO_CTRLUPD_SRX_Pos (30U)
#define DDRCTRL_DFIUPD0_DIS_AUTO_CTRLUPD_SRX_Msk (0x1U << DDRCTRL_DFIUPD0_DIS_AUTO_CTRLUPD_SRX_Pos) /*!< 0x40000000 */
#define DDRCTRL_DFIUPD0_DIS_AUTO_CTRLUPD_SRX     DDRCTRL_DFIUPD0_DIS_AUTO_CTRLUPD_SRX_Msk           /*!< When \q1\q, disable the automatic dfi_ctrlupd_req generation by the DDRCTRL at self-refresh exit. */
#define DDRCTRL_DFIUPD0_DIS_AUTO_CTRLUPD_Pos     (31U)
#define DDRCTRL_DFIUPD0_DIS_AUTO_CTRLUPD_Msk     (0x1U << DDRCTRL_DFIUPD0_DIS_AUTO_CTRLUPD_Pos)     /*!< 0x80000000 */
#define DDRCTRL_DFIUPD0_DIS_AUTO_CTRLUPD         DDRCTRL_DFIUPD0_DIS_AUTO_CTRLUPD_Msk               /*!< When \q1\q, disable the automatic dfi_ctrlupd_req generation by the DDRCTRL. The core must issue the dfi_ctrlupd_req signal using register DBGCMD.ctrlupd. */

/***************  Bit definition for DDRCTRL_DFIUPD1 register  ****************/
#define DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_Pos (0U)
#define DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_Msk (0xFFU << DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_Pos) /*!< 0x000000FF */
#define DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024     DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_Msk            /*!< This is the maximum amount of time between DDRCTRL initiated DFI update requests. This timer resets with each update request; when the timer expires dfi_ctrlupd_req is sent and traffic is blocked until the dfi_ctrlupd_ackx is received. PHY can use this idle time to recalibrate the delay lines to the DLLs. The DFI controller update is also used to reset PHY FIFO pointers in case of data capture errors. Updates are required to maintain calibration over PVT, but frequent updates may impact performance. Minimum allowed value for this field is 1. */
#define DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_0   (0x1U << DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_Pos)  /*!< 0x00000001 */
#define DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_1   (0x2U << DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_Pos)  /*!< 0x00000002 */
#define DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_2   (0x4U << DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_Pos)  /*!< 0x00000004 */
#define DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_3   (0x8U << DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_Pos)  /*!< 0x00000008 */
#define DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_4   (0x10U << DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_Pos) /*!< 0x00000010 */
#define DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_5   (0x20U << DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_Pos) /*!< 0x00000020 */
#define DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_6   (0x40U << DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_Pos) /*!< 0x00000040 */
#define DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_7   (0x80U << DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_Pos) /*!< 0x00000080 */
#define DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_Pos (16U)
#define DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_Msk (0xFFU << DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_Pos) /*!< 0x00FF0000 */
#define DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024     DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_Msk            /*!< This is the minimum amount of time between DDRCTRL initiated DFI update requests (which is executed whenever the DDRCTRL is idle). Set this number higher to reduce the frequency of update requests, which can have a small impact on the latency of the first read request when the DDRCTRL is idle. Minimum allowed value for this field is 1. */
#define DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_0   (0x1U << DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_Pos)  /*!< 0x00010000 */
#define DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_1   (0x2U << DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_Pos)  /*!< 0x00020000 */
#define DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_2   (0x4U << DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_Pos)  /*!< 0x00040000 */
#define DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_3   (0x8U << DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_Pos)  /*!< 0x00080000 */
#define DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_4   (0x10U << DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_Pos) /*!< 0x00100000 */
#define DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_5   (0x20U << DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_Pos) /*!< 0x00200000 */
#define DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_6   (0x40U << DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_Pos) /*!< 0x00400000 */
#define DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_7   (0x80U << DDRCTRL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_Pos) /*!< 0x00800000 */

/***************  Bit definition for DDRCTRL_DFIUPD2 register  ****************/
#define DDRCTRL_DFIUPD2_DFI_PHYUPD_EN_Pos (31U)
#define DDRCTRL_DFIUPD2_DFI_PHYUPD_EN_Msk (0x1U << DDRCTRL_DFIUPD2_DFI_PHYUPD_EN_Pos) /*!< 0x80000000 */
#define DDRCTRL_DFIUPD2_DFI_PHYUPD_EN     DDRCTRL_DFIUPD2_DFI_PHYUPD_EN_Msk           /*!< Enables the support for acknowledging PHY-initiated updates: */

/***************  Bit definition for DDRCTRL_DFIMISC register  ****************/
#define DDRCTRL_DFIMISC_DFI_INIT_COMPLETE_EN_Pos (0U)
#define DDRCTRL_DFIMISC_DFI_INIT_COMPLETE_EN_Msk (0x1U << DDRCTRL_DFIMISC_DFI_INIT_COMPLETE_EN_Pos) /*!< 0x00000001 */
#define DDRCTRL_DFIMISC_DFI_INIT_COMPLETE_EN     DDRCTRL_DFIMISC_DFI_INIT_COMPLETE_EN_Msk           /*!< PHY initialization complete enable signal. */
#define DDRCTRL_DFIMISC_CTL_IDLE_EN_Pos          (4U)
#define DDRCTRL_DFIMISC_CTL_IDLE_EN_Msk          (0x1U << DDRCTRL_DFIMISC_CTL_IDLE_EN_Pos)          /*!< 0x00000010 */
#define DDRCTRL_DFIMISC_CTL_IDLE_EN              DDRCTRL_DFIMISC_CTL_IDLE_EN_Msk                    /*!< Enables support of ctl_idle signal */
#define DDRCTRL_DFIMISC_DFI_INIT_START_Pos       (5U)
#define DDRCTRL_DFIMISC_DFI_INIT_START_Msk       (0x1U << DDRCTRL_DFIMISC_DFI_INIT_START_Pos)       /*!< 0x00000020 */
#define DDRCTRL_DFIMISC_DFI_INIT_START           DDRCTRL_DFIMISC_DFI_INIT_START_Msk                 /*!< PHY init start request signal.When asserted it triggers the PHY init start request */
#define DDRCTRL_DFIMISC_DFI_FREQUENCY_Pos        (8U)
#define DDRCTRL_DFIMISC_DFI_FREQUENCY_Msk        (0x1FU << DDRCTRL_DFIMISC_DFI_FREQUENCY_Pos)       /*!< 0x00001F00 */
#define DDRCTRL_DFIMISC_DFI_FREQUENCY            DDRCTRL_DFIMISC_DFI_FREQUENCY_Msk                  /*!< Indicates the operating frequency of the system. The number of supported frequencies and the mapping of signal values to clock frequencies are defined by the PHY. */
#define DDRCTRL_DFIMISC_DFI_FREQUENCY_0          (0x1U << DDRCTRL_DFIMISC_DFI_FREQUENCY_Pos)        /*!< 0x00000100 */
#define DDRCTRL_DFIMISC_DFI_FREQUENCY_1          (0x2U << DDRCTRL_DFIMISC_DFI_FREQUENCY_Pos)        /*!< 0x00000200 */
#define DDRCTRL_DFIMISC_DFI_FREQUENCY_2          (0x4U << DDRCTRL_DFIMISC_DFI_FREQUENCY_Pos)        /*!< 0x00000400 */
#define DDRCTRL_DFIMISC_DFI_FREQUENCY_3          (0x8U << DDRCTRL_DFIMISC_DFI_FREQUENCY_Pos)        /*!< 0x00000800 */
#define DDRCTRL_DFIMISC_DFI_FREQUENCY_4          (0x10U << DDRCTRL_DFIMISC_DFI_FREQUENCY_Pos)       /*!< 0x00001000 */

/***************  Bit definition for DDRCTRL_DFISTAT register  ****************/
#define DDRCTRL_DFISTAT_DFI_INIT_COMPLETE_Pos (0U)
#define DDRCTRL_DFISTAT_DFI_INIT_COMPLETE_Msk (0x1U << DDRCTRL_DFISTAT_DFI_INIT_COMPLETE_Pos) /*!< 0x00000001 */
#define DDRCTRL_DFISTAT_DFI_INIT_COMPLETE     DDRCTRL_DFISTAT_DFI_INIT_COMPLETE_Msk           /*!< The status flag register which announces when the DFI initialization has been completed. The DFI INIT triggered by dfi_init_start signal and then the dfi_init_complete flag is polled to know when the initialization is done. */
#define DDRCTRL_DFISTAT_DFI_LP_ACK_Pos        (1U)
#define DDRCTRL_DFISTAT_DFI_LP_ACK_Msk        (0x1U << DDRCTRL_DFISTAT_DFI_LP_ACK_Pos)        /*!< 0x00000002 */
#define DDRCTRL_DFISTAT_DFI_LP_ACK            DDRCTRL_DFISTAT_DFI_LP_ACK_Msk                  /*!< Stores the value of the dfi_lp_ack input to the controller. */

/**************  Bit definition for DDRCTRL_DFIPHYMSTR register  **************/
#define DDRCTRL_DFIPHYMSTR_DFI_PHYMSTR_EN_Pos (0U)
#define DDRCTRL_DFIPHYMSTR_DFI_PHYMSTR_EN_Msk (0x1U << DDRCTRL_DFIPHYMSTR_DFI_PHYMSTR_EN_Pos) /*!< 0x00000001 */
#define DDRCTRL_DFIPHYMSTR_DFI_PHYMSTR_EN     DDRCTRL_DFIPHYMSTR_DFI_PHYMSTR_EN_Msk           /*!< Enables the PHY Master Interface: */

/***************  Bit definition for DDRCTRL_ADDRMAP1 register  ***************/
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B0_Pos (0U)
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B0_Msk (0x3FU << DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B0_Pos) /*!< 0x0000003F */
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B0     DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B0_Msk            /*!< Selects the HIF address bits used as bank address bit 0. */
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B0_0   (0x1U << DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B0_Pos)  /*!< 0x00000001 */
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B0_1   (0x2U << DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B0_Pos)  /*!< 0x00000002 */
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B0_2   (0x4U << DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B0_Pos)  /*!< 0x00000004 */
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B0_3   (0x8U << DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B0_Pos)  /*!< 0x00000008 */
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B0_4   (0x10U << DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B0_Pos) /*!< 0x00000010 */
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B0_5   (0x20U << DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B0_Pos) /*!< 0x00000020 */
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B1_Pos (8U)
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B1_Msk (0x3FU << DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B1_Pos) /*!< 0x00003F00 */
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B1     DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B1_Msk            /*!< Selects the HIF address bits used as bank address bit 1. */
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B1_0   (0x1U << DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B1_Pos)  /*!< 0x00000100 */
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B1_1   (0x2U << DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B1_Pos)  /*!< 0x00000200 */
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B1_2   (0x4U << DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B1_Pos)  /*!< 0x00000400 */
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B1_3   (0x8U << DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B1_Pos)  /*!< 0x00000800 */
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B1_4   (0x10U << DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B1_Pos) /*!< 0x00001000 */
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B1_5   (0x20U << DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B1_Pos) /*!< 0x00002000 */
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B2_Pos (16U)
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B2_Msk (0x3FU << DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B2_Pos) /*!< 0x003F0000 */
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B2     DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B2_Msk            /*!< Selects the HIF address bit used as bank address bit 2. */
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B2_0   (0x1U << DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B2_Pos)  /*!< 0x00010000 */
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B2_1   (0x2U << DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B2_Pos)  /*!< 0x00020000 */
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B2_2   (0x4U << DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B2_Pos)  /*!< 0x00040000 */
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B2_3   (0x8U << DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B2_Pos)  /*!< 0x00080000 */
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B2_4   (0x10U << DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B2_Pos) /*!< 0x00100000 */
#define DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B2_5   (0x20U << DDRCTRL_ADDRMAP1_ADDRMAP_BANK_B2_Pos) /*!< 0x00200000 */

/***************  Bit definition for DDRCTRL_ADDRMAP2 register  ***************/
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B2_Pos (0U)
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B2_Msk (0xFU << DDRCTRL_ADDRMAP2_ADDRMAP_COL_B2_Pos) /*!< 0x0000000F */
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B2     DDRCTRL_ADDRMAP2_ADDRMAP_COL_B2_Msk           /*!< - Full bus width mode: Selects the HIF address bit used as column address bit 2. */
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B2_0   (0x1U << DDRCTRL_ADDRMAP2_ADDRMAP_COL_B2_Pos) /*!< 0x00000001 */
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B2_1   (0x2U << DDRCTRL_ADDRMAP2_ADDRMAP_COL_B2_Pos) /*!< 0x00000002 */
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B2_2   (0x4U << DDRCTRL_ADDRMAP2_ADDRMAP_COL_B2_Pos) /*!< 0x00000004 */
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B2_3   (0x8U << DDRCTRL_ADDRMAP2_ADDRMAP_COL_B2_Pos) /*!< 0x00000008 */
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B3_Pos (8U)
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B3_Msk (0xFU << DDRCTRL_ADDRMAP2_ADDRMAP_COL_B3_Pos) /*!< 0x00000F00 */
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B3     DDRCTRL_ADDRMAP2_ADDRMAP_COL_B3_Msk           /*!< - Full bus width mode: Selects the HIF address bit used as column address bit 3. */
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B3_0   (0x1U << DDRCTRL_ADDRMAP2_ADDRMAP_COL_B3_Pos) /*!< 0x00000100 */
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B3_1   (0x2U << DDRCTRL_ADDRMAP2_ADDRMAP_COL_B3_Pos) /*!< 0x00000200 */
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B3_2   (0x4U << DDRCTRL_ADDRMAP2_ADDRMAP_COL_B3_Pos) /*!< 0x00000400 */
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B3_3   (0x8U << DDRCTRL_ADDRMAP2_ADDRMAP_COL_B3_Pos) /*!< 0x00000800 */
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B4_Pos (16U)
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B4_Msk (0xFU << DDRCTRL_ADDRMAP2_ADDRMAP_COL_B4_Pos) /*!< 0x000F0000 */
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B4     DDRCTRL_ADDRMAP2_ADDRMAP_COL_B4_Msk           /*!< - Full bus width mode: Selects the HIF address bit used as column address bit 4. */
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B4_0   (0x1U << DDRCTRL_ADDRMAP2_ADDRMAP_COL_B4_Pos) /*!< 0x00010000 */
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B4_1   (0x2U << DDRCTRL_ADDRMAP2_ADDRMAP_COL_B4_Pos) /*!< 0x00020000 */
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B4_2   (0x4U << DDRCTRL_ADDRMAP2_ADDRMAP_COL_B4_Pos) /*!< 0x00040000 */
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B4_3   (0x8U << DDRCTRL_ADDRMAP2_ADDRMAP_COL_B4_Pos) /*!< 0x00080000 */
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B5_Pos (24U)
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B5_Msk (0xFU << DDRCTRL_ADDRMAP2_ADDRMAP_COL_B5_Pos) /*!< 0x0F000000 */
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B5     DDRCTRL_ADDRMAP2_ADDRMAP_COL_B5_Msk           /*!< - Full bus width mode: Selects the HIF address bit used as column address bit 5. */
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B5_0   (0x1U << DDRCTRL_ADDRMAP2_ADDRMAP_COL_B5_Pos) /*!< 0x01000000 */
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B5_1   (0x2U << DDRCTRL_ADDRMAP2_ADDRMAP_COL_B5_Pos) /*!< 0x02000000 */
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B5_2   (0x4U << DDRCTRL_ADDRMAP2_ADDRMAP_COL_B5_Pos) /*!< 0x04000000 */
#define DDRCTRL_ADDRMAP2_ADDRMAP_COL_B5_3   (0x8U << DDRCTRL_ADDRMAP2_ADDRMAP_COL_B5_Pos) /*!< 0x08000000 */

/***************  Bit definition for DDRCTRL_ADDRMAP3 register  ***************/
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B6_Pos (0U)
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B6_Msk (0xFU << DDRCTRL_ADDRMAP3_ADDRMAP_COL_B6_Pos)  /*!< 0x0000000F */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B6     DDRCTRL_ADDRMAP3_ADDRMAP_COL_B6_Msk            /*!< - Full bus width mode: Selects the HIF address bit used as column address bit 6. */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B6_0   (0x1U << DDRCTRL_ADDRMAP3_ADDRMAP_COL_B6_Pos)  /*!< 0x00000001 */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B6_1   (0x2U << DDRCTRL_ADDRMAP3_ADDRMAP_COL_B6_Pos)  /*!< 0x00000002 */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B6_2   (0x4U << DDRCTRL_ADDRMAP3_ADDRMAP_COL_B6_Pos)  /*!< 0x00000004 */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B6_3   (0x8U << DDRCTRL_ADDRMAP3_ADDRMAP_COL_B6_Pos)  /*!< 0x00000008 */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B7_Pos (8U)
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B7_Msk (0x1FU << DDRCTRL_ADDRMAP3_ADDRMAP_COL_B7_Pos) /*!< 0x00001F00 */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B7     DDRCTRL_ADDRMAP3_ADDRMAP_COL_B7_Msk            /*!< - Full bus width mode: Selects the HIF address bit used as column address bit 7. */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B7_0   (0x1U << DDRCTRL_ADDRMAP3_ADDRMAP_COL_B7_Pos)  /*!< 0x00000100 */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B7_1   (0x2U << DDRCTRL_ADDRMAP3_ADDRMAP_COL_B7_Pos)  /*!< 0x00000200 */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B7_2   (0x4U << DDRCTRL_ADDRMAP3_ADDRMAP_COL_B7_Pos)  /*!< 0x00000400 */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B7_3   (0x8U << DDRCTRL_ADDRMAP3_ADDRMAP_COL_B7_Pos)  /*!< 0x00000800 */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B7_4   (0x10U << DDRCTRL_ADDRMAP3_ADDRMAP_COL_B7_Pos) /*!< 0x00001000 */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B8_Pos (16U)
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B8_Msk (0x1FU << DDRCTRL_ADDRMAP3_ADDRMAP_COL_B8_Pos) /*!< 0x001F0000 */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B8     DDRCTRL_ADDRMAP3_ADDRMAP_COL_B8_Msk            /*!< - Full bus width mode: Selects the HIF address bit used as column address bit 8. */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B8_0   (0x1U << DDRCTRL_ADDRMAP3_ADDRMAP_COL_B8_Pos)  /*!< 0x00010000 */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B8_1   (0x2U << DDRCTRL_ADDRMAP3_ADDRMAP_COL_B8_Pos)  /*!< 0x00020000 */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B8_2   (0x4U << DDRCTRL_ADDRMAP3_ADDRMAP_COL_B8_Pos)  /*!< 0x00040000 */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B8_3   (0x8U << DDRCTRL_ADDRMAP3_ADDRMAP_COL_B8_Pos)  /*!< 0x00080000 */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B8_4   (0x10U << DDRCTRL_ADDRMAP3_ADDRMAP_COL_B8_Pos) /*!< 0x00100000 */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B9_Pos (24U)
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B9_Msk (0x1FU << DDRCTRL_ADDRMAP3_ADDRMAP_COL_B9_Pos) /*!< 0x1F000000 */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B9     DDRCTRL_ADDRMAP3_ADDRMAP_COL_B9_Msk            /*!< - Full bus width mode: Selects the HIF address bit used as column address bit 9. */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B9_0   (0x1U << DDRCTRL_ADDRMAP3_ADDRMAP_COL_B9_Pos)  /*!< 0x01000000 */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B9_1   (0x2U << DDRCTRL_ADDRMAP3_ADDRMAP_COL_B9_Pos)  /*!< 0x02000000 */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B9_2   (0x4U << DDRCTRL_ADDRMAP3_ADDRMAP_COL_B9_Pos)  /*!< 0x04000000 */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B9_3   (0x8U << DDRCTRL_ADDRMAP3_ADDRMAP_COL_B9_Pos)  /*!< 0x08000000 */
#define DDRCTRL_ADDRMAP3_ADDRMAP_COL_B9_4   (0x10U << DDRCTRL_ADDRMAP3_ADDRMAP_COL_B9_Pos) /*!< 0x10000000 */

/***************  Bit definition for DDRCTRL_ADDRMAP4 register  ***************/
#define DDRCTRL_ADDRMAP4_ADDRMAP_COL_B10_Pos (0U)
#define DDRCTRL_ADDRMAP4_ADDRMAP_COL_B10_Msk (0x1FU << DDRCTRL_ADDRMAP4_ADDRMAP_COL_B10_Pos) /*!< 0x0000001F */
#define DDRCTRL_ADDRMAP4_ADDRMAP_COL_B10     DDRCTRL_ADDRMAP4_ADDRMAP_COL_B10_Msk            /*!< - Full bus width mode: Selects the HIF address bit used as column address bit 11 (10 in LPDDR2/LPDDR3 mode). */
#define DDRCTRL_ADDRMAP4_ADDRMAP_COL_B10_0   (0x1U << DDRCTRL_ADDRMAP4_ADDRMAP_COL_B10_Pos)  /*!< 0x00000001 */
#define DDRCTRL_ADDRMAP4_ADDRMAP_COL_B10_1   (0x2U << DDRCTRL_ADDRMAP4_ADDRMAP_COL_B10_Pos)  /*!< 0x00000002 */
#define DDRCTRL_ADDRMAP4_ADDRMAP_COL_B10_2   (0x4U << DDRCTRL_ADDRMAP4_ADDRMAP_COL_B10_Pos)  /*!< 0x00000004 */
#define DDRCTRL_ADDRMAP4_ADDRMAP_COL_B10_3   (0x8U << DDRCTRL_ADDRMAP4_ADDRMAP_COL_B10_Pos)  /*!< 0x00000008 */
#define DDRCTRL_ADDRMAP4_ADDRMAP_COL_B10_4   (0x10U << DDRCTRL_ADDRMAP4_ADDRMAP_COL_B10_Pos) /*!< 0x00000010 */
#define DDRCTRL_ADDRMAP4_ADDRMAP_COL_B11_Pos (8U)
#define DDRCTRL_ADDRMAP4_ADDRMAP_COL_B11_Msk (0x1FU << DDRCTRL_ADDRMAP4_ADDRMAP_COL_B11_Pos) /*!< 0x00001F00 */
#define DDRCTRL_ADDRMAP4_ADDRMAP_COL_B11     DDRCTRL_ADDRMAP4_ADDRMAP_COL_B11_Msk            /*!< - Full bus width mode: Selects the HIF address bit used as column address bit 13 (11 in LPDDR2/LPDDR3 mode). */
#define DDRCTRL_ADDRMAP4_ADDRMAP_COL_B11_0   (0x1U << DDRCTRL_ADDRMAP4_ADDRMAP_COL_B11_Pos)  /*!< 0x00000100 */
#define DDRCTRL_ADDRMAP4_ADDRMAP_COL_B11_1   (0x2U << DDRCTRL_ADDRMAP4_ADDRMAP_COL_B11_Pos)  /*!< 0x00000200 */
#define DDRCTRL_ADDRMAP4_ADDRMAP_COL_B11_2   (0x4U << DDRCTRL_ADDRMAP4_ADDRMAP_COL_B11_Pos)  /*!< 0x00000400 */
#define DDRCTRL_ADDRMAP4_ADDRMAP_COL_B11_3   (0x8U << DDRCTRL_ADDRMAP4_ADDRMAP_COL_B11_Pos)  /*!< 0x00000800 */
#define DDRCTRL_ADDRMAP4_ADDRMAP_COL_B11_4   (0x10U << DDRCTRL_ADDRMAP4_ADDRMAP_COL_B11_Pos) /*!< 0x00001000 */

/***************  Bit definition for DDRCTRL_ADDRMAP5 register  ***************/
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B0_Pos    (0U)
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B0_Msk    (0xFU << DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B0_Pos)    /*!< 0x0000000F */
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B0        DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B0_Msk              /*!< Selects the HIF address bits used as row address bit 0. */
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B0_0      (0x1U << DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B0_Pos)    /*!< 0x00000001 */
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B0_1      (0x2U << DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B0_Pos)    /*!< 0x00000002 */
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B0_2      (0x4U << DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B0_Pos)    /*!< 0x00000004 */
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B0_3      (0x8U << DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B0_Pos)    /*!< 0x00000008 */
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B1_Pos    (8U)
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B1_Msk    (0xFU << DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B1_Pos)    /*!< 0x00000F00 */
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B1        DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B1_Msk              /*!< Selects the HIF address bits used as row address bit 1. */
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B1_0      (0x1U << DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B1_Pos)    /*!< 0x00000100 */
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B1_1      (0x2U << DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B1_Pos)    /*!< 0x00000200 */
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B1_2      (0x4U << DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B1_Pos)    /*!< 0x00000400 */
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B1_3      (0x8U << DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B1_Pos)    /*!< 0x00000800 */
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B2_10_Pos (16U)
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B2_10_Msk (0xFU << DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B2_10_Pos) /*!< 0x000F0000 */
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B2_10     DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B2_10_Msk           /*!< Selects the HIF address bits used as row address bits 2 to 10. */
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B2_10_0   (0x1U << DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B2_10_Pos) /*!< 0x00010000 */
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B2_10_1   (0x2U << DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B2_10_Pos) /*!< 0x00020000 */
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B2_10_2   (0x4U << DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B2_10_Pos) /*!< 0x00040000 */
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B2_10_3   (0x8U << DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B2_10_Pos) /*!< 0x00080000 */
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B11_Pos   (24U)
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B11_Msk   (0xFU << DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B11_Pos)   /*!< 0x0F000000 */
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B11       DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B11_Msk             /*!< Selects the HIF address bit used as row address bit 11. */
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B11_0     (0x1U << DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B11_Pos)   /*!< 0x01000000 */
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B11_1     (0x2U << DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B11_Pos)   /*!< 0x02000000 */
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B11_2     (0x4U << DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B11_Pos)   /*!< 0x04000000 */
#define DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B11_3     (0x8U << DDRCTRL_ADDRMAP5_ADDRMAP_ROW_B11_Pos)   /*!< 0x08000000 */

/***************  Bit definition for DDRCTRL_ADDRMAP6 register  ***************/
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B12_Pos (0U)
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B12_Msk (0xFU << DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B12_Pos) /*!< 0x0000000F */
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B12     DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B12_Msk           /*!< Selects the HIF address bit used as row address bit 12. */
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B12_0   (0x1U << DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B12_Pos) /*!< 0x00000001 */
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B12_1   (0x2U << DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B12_Pos) /*!< 0x00000002 */
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B12_2   (0x4U << DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B12_Pos) /*!< 0x00000004 */
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B12_3   (0x8U << DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B12_Pos) /*!< 0x00000008 */
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B13_Pos (8U)
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B13_Msk (0xFU << DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B13_Pos) /*!< 0x00000F00 */
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B13     DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B13_Msk           /*!< Selects the HIF address bit used as row address bit 13. */
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B13_0   (0x1U << DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B13_Pos) /*!< 0x00000100 */
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B13_1   (0x2U << DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B13_Pos) /*!< 0x00000200 */
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B13_2   (0x4U << DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B13_Pos) /*!< 0x00000400 */
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B13_3   (0x8U << DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B13_Pos) /*!< 0x00000800 */
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B14_Pos (16U)
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B14_Msk (0xFU << DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B14_Pos) /*!< 0x000F0000 */
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B14     DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B14_Msk           /*!< Selects the HIF address bit used as row address bit 14. */
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B14_0   (0x1U << DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B14_Pos) /*!< 0x00010000 */
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B14_1   (0x2U << DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B14_Pos) /*!< 0x00020000 */
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B14_2   (0x4U << DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B14_Pos) /*!< 0x00040000 */
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B14_3   (0x8U << DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B14_Pos) /*!< 0x00080000 */
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B15_Pos (24U)
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B15_Msk (0xFU << DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B15_Pos) /*!< 0x0F000000 */
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B15     DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B15_Msk           /*!< Selects the HIF address bit used as row address bit 15. */
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B15_0   (0x1U << DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B15_Pos) /*!< 0x01000000 */
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B15_1   (0x2U << DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B15_Pos) /*!< 0x02000000 */
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B15_2   (0x4U << DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B15_Pos) /*!< 0x04000000 */
#define DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B15_3   (0x8U << DDRCTRL_ADDRMAP6_ADDRMAP_ROW_B15_Pos) /*!< 0x08000000 */
#define DDRCTRL_ADDRMAP6_LPDDR3_6GB_12GB_Pos (31U)
#define DDRCTRL_ADDRMAP6_LPDDR3_6GB_12GB_Msk (0x1U << DDRCTRL_ADDRMAP6_LPDDR3_6GB_12GB_Pos) /*!< 0x80000000 */
#define DDRCTRL_ADDRMAP6_LPDDR3_6GB_12GB     DDRCTRL_ADDRMAP6_LPDDR3_6GB_12GB_Msk           /*!< Set this to 1 if there is an LPDDR3 SDRAM 6Gb or 12Gb device in use. */

/***************  Bit definition for DDRCTRL_ADDRMAP9 register  ***************/
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B2_Pos (0U)
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B2_Msk (0xFU << DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B2_Pos) /*!< 0x0000000F */
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B2     DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B2_Msk           /*!< Selects the HIF address bits used as row address bit 2. */
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B2_0   (0x1U << DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B2_Pos) /*!< 0x00000001 */
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B2_1   (0x2U << DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B2_Pos) /*!< 0x00000002 */
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B2_2   (0x4U << DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B2_Pos) /*!< 0x00000004 */
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B2_3   (0x8U << DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B2_Pos) /*!< 0x00000008 */
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B3_Pos (8U)
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B3_Msk (0xFU << DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B3_Pos) /*!< 0x00000F00 */
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B3     DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B3_Msk           /*!< Selects the HIF address bits used as row address bit 3. */
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B3_0   (0x1U << DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B3_Pos) /*!< 0x00000100 */
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B3_1   (0x2U << DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B3_Pos) /*!< 0x00000200 */
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B3_2   (0x4U << DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B3_Pos) /*!< 0x00000400 */
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B3_3   (0x8U << DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B3_Pos) /*!< 0x00000800 */
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B4_Pos (16U)
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B4_Msk (0xFU << DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B4_Pos) /*!< 0x000F0000 */
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B4     DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B4_Msk           /*!< Selects the HIF address bits used as row address bit 4. */
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B4_0   (0x1U << DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B4_Pos) /*!< 0x00010000 */
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B4_1   (0x2U << DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B4_Pos) /*!< 0x00020000 */
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B4_2   (0x4U << DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B4_Pos) /*!< 0x00040000 */
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B4_3   (0x8U << DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B4_Pos) /*!< 0x00080000 */
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B5_Pos (24U)
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B5_Msk (0xFU << DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B5_Pos) /*!< 0x0F000000 */
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B5     DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B5_Msk           /*!< Selects the HIF address bits used as row address bit 5. */
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B5_0   (0x1U << DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B5_Pos) /*!< 0x01000000 */
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B5_1   (0x2U << DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B5_Pos) /*!< 0x02000000 */
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B5_2   (0x4U << DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B5_Pos) /*!< 0x04000000 */
#define DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B5_3   (0x8U << DDRCTRL_ADDRMAP9_ADDRMAP_ROW_B5_Pos) /*!< 0x08000000 */

/**************  Bit definition for DDRCTRL_ADDRMAP10 register  ***************/
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B6_Pos (0U)
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B6_Msk (0xFU << DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B6_Pos) /*!< 0x0000000F */
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B6     DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B6_Msk           /*!< Selects the HIF address bits used as row address bit 6. */
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B6_0   (0x1U << DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B6_Pos) /*!< 0x00000001 */
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B6_1   (0x2U << DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B6_Pos) /*!< 0x00000002 */
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B6_2   (0x4U << DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B6_Pos) /*!< 0x00000004 */
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B6_3   (0x8U << DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B6_Pos) /*!< 0x00000008 */
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B7_Pos (8U)
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B7_Msk (0xFU << DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B7_Pos) /*!< 0x00000F00 */
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B7     DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B7_Msk           /*!< Selects the HIF address bits used as row address bit 7. */
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B7_0   (0x1U << DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B7_Pos) /*!< 0x00000100 */
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B7_1   (0x2U << DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B7_Pos) /*!< 0x00000200 */
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B7_2   (0x4U << DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B7_Pos) /*!< 0x00000400 */
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B7_3   (0x8U << DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B7_Pos) /*!< 0x00000800 */
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B8_Pos (16U)
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B8_Msk (0xFU << DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B8_Pos) /*!< 0x000F0000 */
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B8     DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B8_Msk           /*!< Selects the HIF address bits used as row address bit 8. */
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B8_0   (0x1U << DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B8_Pos) /*!< 0x00010000 */
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B8_1   (0x2U << DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B8_Pos) /*!< 0x00020000 */
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B8_2   (0x4U << DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B8_Pos) /*!< 0x00040000 */
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B8_3   (0x8U << DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B8_Pos) /*!< 0x00080000 */
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B9_Pos (24U)
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B9_Msk (0xFU << DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B9_Pos) /*!< 0x0F000000 */
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B9     DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B9_Msk           /*!< Selects the HIF address bits used as row address bit 9. */
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B9_0   (0x1U << DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B9_Pos) /*!< 0x01000000 */
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B9_1   (0x2U << DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B9_Pos) /*!< 0x02000000 */
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B9_2   (0x4U << DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B9_Pos) /*!< 0x04000000 */
#define DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B9_3   (0x8U << DDRCTRL_ADDRMAP10_ADDRMAP_ROW_B9_Pos) /*!< 0x08000000 */

/**************  Bit definition for DDRCTRL_ADDRMAP11 register  ***************/
#define DDRCTRL_ADDRMAP11_ADDRMAP_ROW_B10_Pos (0U)
#define DDRCTRL_ADDRMAP11_ADDRMAP_ROW_B10_Msk (0xFU << DDRCTRL_ADDRMAP11_ADDRMAP_ROW_B10_Pos) /*!< 0x0000000F */
#define DDRCTRL_ADDRMAP11_ADDRMAP_ROW_B10     DDRCTRL_ADDRMAP11_ADDRMAP_ROW_B10_Msk           /*!< Selects the HIF address bits used as row address bit 10. */
#define DDRCTRL_ADDRMAP11_ADDRMAP_ROW_B10_0   (0x1U << DDRCTRL_ADDRMAP11_ADDRMAP_ROW_B10_Pos) /*!< 0x00000001 */
#define DDRCTRL_ADDRMAP11_ADDRMAP_ROW_B10_1   (0x2U << DDRCTRL_ADDRMAP11_ADDRMAP_ROW_B10_Pos) /*!< 0x00000002 */
#define DDRCTRL_ADDRMAP11_ADDRMAP_ROW_B10_2   (0x4U << DDRCTRL_ADDRMAP11_ADDRMAP_ROW_B10_Pos) /*!< 0x00000004 */
#define DDRCTRL_ADDRMAP11_ADDRMAP_ROW_B10_3   (0x8U << DDRCTRL_ADDRMAP11_ADDRMAP_ROW_B10_Pos) /*!< 0x00000008 */

/****************  Bit definition for DDRCTRL_ODTCFG register  ****************/
#define DDRCTRL_ODTCFG_RD_ODT_DELAY_Pos (2U)
#define DDRCTRL_ODTCFG_RD_ODT_DELAY_Msk (0x1FU << DDRCTRL_ODTCFG_RD_ODT_DELAY_Pos) /*!< 0x0000007C */
#define DDRCTRL_ODTCFG_RD_ODT_DELAY     DDRCTRL_ODTCFG_RD_ODT_DELAY_Msk            /*!< The delay, in DFI PHY clock cycles, from issuing a read command to setting ODT values associated with that command. ODT setting must remain constant for the entire time that DQS is driven by the DDRCTRL. */
#define DDRCTRL_ODTCFG_RD_ODT_DELAY_0   (0x1U << DDRCTRL_ODTCFG_RD_ODT_DELAY_Pos)  /*!< 0x00000004 */
#define DDRCTRL_ODTCFG_RD_ODT_DELAY_1   (0x2U << DDRCTRL_ODTCFG_RD_ODT_DELAY_Pos)  /*!< 0x00000008 */
#define DDRCTRL_ODTCFG_RD_ODT_DELAY_2   (0x4U << DDRCTRL_ODTCFG_RD_ODT_DELAY_Pos)  /*!< 0x00000010 */
#define DDRCTRL_ODTCFG_RD_ODT_DELAY_3   (0x8U << DDRCTRL_ODTCFG_RD_ODT_DELAY_Pos)  /*!< 0x00000020 */
#define DDRCTRL_ODTCFG_RD_ODT_DELAY_4   (0x10U << DDRCTRL_ODTCFG_RD_ODT_DELAY_Pos) /*!< 0x00000040 */
#define DDRCTRL_ODTCFG_RD_ODT_HOLD_Pos  (8U)
#define DDRCTRL_ODTCFG_RD_ODT_HOLD_Msk  (0xFU << DDRCTRL_ODTCFG_RD_ODT_HOLD_Pos)   /*!< 0x00000F00 */
#define DDRCTRL_ODTCFG_RD_ODT_HOLD      DDRCTRL_ODTCFG_RD_ODT_HOLD_Msk             /*!< DFI PHY clock cycles to hold ODT for a read command. The minimum supported value is 2. */
#define DDRCTRL_ODTCFG_RD_ODT_HOLD_0    (0x1U << DDRCTRL_ODTCFG_RD_ODT_HOLD_Pos)   /*!< 0x00000100 */
#define DDRCTRL_ODTCFG_RD_ODT_HOLD_1    (0x2U << DDRCTRL_ODTCFG_RD_ODT_HOLD_Pos)   /*!< 0x00000200 */
#define DDRCTRL_ODTCFG_RD_ODT_HOLD_2    (0x4U << DDRCTRL_ODTCFG_RD_ODT_HOLD_Pos)   /*!< 0x00000400 */
#define DDRCTRL_ODTCFG_RD_ODT_HOLD_3    (0x8U << DDRCTRL_ODTCFG_RD_ODT_HOLD_Pos)   /*!< 0x00000800 */
#define DDRCTRL_ODTCFG_WR_ODT_DELAY_Pos (16U)
#define DDRCTRL_ODTCFG_WR_ODT_DELAY_Msk (0x1FU << DDRCTRL_ODTCFG_WR_ODT_DELAY_Pos) /*!< 0x001F0000 */
#define DDRCTRL_ODTCFG_WR_ODT_DELAY     DDRCTRL_ODTCFG_WR_ODT_DELAY_Msk            /*!< The delay, in DFI PHY clock cycles, from issuing a write command to setting ODT values associated with that command. ODT setting must remain constant for the entire time that DQS is driven by the DDRCTRL. */
#define DDRCTRL_ODTCFG_WR_ODT_DELAY_0   (0x1U << DDRCTRL_ODTCFG_WR_ODT_DELAY_Pos)  /*!< 0x00010000 */
#define DDRCTRL_ODTCFG_WR_ODT_DELAY_1   (0x2U << DDRCTRL_ODTCFG_WR_ODT_DELAY_Pos)  /*!< 0x00020000 */
#define DDRCTRL_ODTCFG_WR_ODT_DELAY_2   (0x4U << DDRCTRL_ODTCFG_WR_ODT_DELAY_Pos)  /*!< 0x00040000 */
#define DDRCTRL_ODTCFG_WR_ODT_DELAY_3   (0x8U << DDRCTRL_ODTCFG_WR_ODT_DELAY_Pos)  /*!< 0x00080000 */
#define DDRCTRL_ODTCFG_WR_ODT_DELAY_4   (0x10U << DDRCTRL_ODTCFG_WR_ODT_DELAY_Pos) /*!< 0x00100000 */
#define DDRCTRL_ODTCFG_WR_ODT_HOLD_Pos  (24U)
#define DDRCTRL_ODTCFG_WR_ODT_HOLD_Msk  (0xFU << DDRCTRL_ODTCFG_WR_ODT_HOLD_Pos)   /*!< 0x0F000000 */
#define DDRCTRL_ODTCFG_WR_ODT_HOLD      DDRCTRL_ODTCFG_WR_ODT_HOLD_Msk             /*!< DFI PHY clock cycles to hold ODT for a write command. The minimum supported value is 2. */
#define DDRCTRL_ODTCFG_WR_ODT_HOLD_0    (0x1U << DDRCTRL_ODTCFG_WR_ODT_HOLD_Pos)   /*!< 0x01000000 */
#define DDRCTRL_ODTCFG_WR_ODT_HOLD_1    (0x2U << DDRCTRL_ODTCFG_WR_ODT_HOLD_Pos)   /*!< 0x02000000 */
#define DDRCTRL_ODTCFG_WR_ODT_HOLD_2    (0x4U << DDRCTRL_ODTCFG_WR_ODT_HOLD_Pos)   /*!< 0x04000000 */
#define DDRCTRL_ODTCFG_WR_ODT_HOLD_3    (0x8U << DDRCTRL_ODTCFG_WR_ODT_HOLD_Pos)   /*!< 0x08000000 */

/****************  Bit definition for DDRCTRL_ODTMAP register  ****************/
#define DDRCTRL_ODTMAP_RANK0_WR_ODT_Pos (0U)
#define DDRCTRL_ODTMAP_RANK0_WR_ODT_Msk (0x1U << DDRCTRL_ODTMAP_RANK0_WR_ODT_Pos) /*!< 0x00000001 */
#define DDRCTRL_ODTMAP_RANK0_WR_ODT     DDRCTRL_ODTMAP_RANK0_WR_ODT_Msk           /*!< Indicates which remote ODTs must be turned on during a write to rank 0. */
#define DDRCTRL_ODTMAP_RANK0_RD_ODT_Pos (4U)
#define DDRCTRL_ODTMAP_RANK0_RD_ODT_Msk (0x1U << DDRCTRL_ODTMAP_RANK0_RD_ODT_Pos) /*!< 0x00000010 */
#define DDRCTRL_ODTMAP_RANK0_RD_ODT     DDRCTRL_ODTMAP_RANK0_RD_ODT_Msk           /*!< Indicates which remote ODTs must be turned on during a read from rank 0. */

/****************  Bit definition for DDRCTRL_SCHED register  *****************/
#define DDRCTRL_SCHED_FORCE_LOW_PRI_N_Pos        (0U)
#define DDRCTRL_SCHED_FORCE_LOW_PRI_N_Msk        (0x1U << DDRCTRL_SCHED_FORCE_LOW_PRI_N_Pos)         /*!< 0x00000001 */
#define DDRCTRL_SCHED_FORCE_LOW_PRI_N            DDRCTRL_SCHED_FORCE_LOW_PRI_N_Msk                   /*!< Active low signal. When asserted (\q0\q), all incoming transactions are forced to low priority. This implies that all high priority read (HPR) and variable priority read commands (VPR) are treated as low priority read (LPR) commands. On the write side, all variable priority write (VPW) commands are treated as normal priority write (NPW) commands. Forcing the incoming transactions to low priority implicitly turns off bypass path for read commands. */
#define DDRCTRL_SCHED_PREFER_WRITE_Pos           (1U)
#define DDRCTRL_SCHED_PREFER_WRITE_Msk           (0x1U << DDRCTRL_SCHED_PREFER_WRITE_Pos)            /*!< 0x00000002 */
#define DDRCTRL_SCHED_PREFER_WRITE               DDRCTRL_SCHED_PREFER_WRITE_Msk                      /*!< If set then the bank selector prefers writes over reads. */
#define DDRCTRL_SCHED_PAGECLOSE_Pos              (2U)
#define DDRCTRL_SCHED_PAGECLOSE_Msk              (0x1U << DDRCTRL_SCHED_PAGECLOSE_Pos)               /*!< 0x00000004 */
#define DDRCTRL_SCHED_PAGECLOSE                  DDRCTRL_SCHED_PAGECLOSE_Msk                         /*!< If true, bank is kept open only while there are page hit transactions available in the CAM to that bank. The last read or write command in the CAM with a bank and page hit is executed with auto-precharge if SCHED1.pageclose_timer=0. Even if this register set to 1 and SCHED1.pageclose_timer is set to 0, explicit precharge (and not auto-precharge) may be issued in some cases where there is a mode switch between write and read or between LPR and HPR. The Read and Write commands that are executed as part of the ECC scrub requests are also executed without auto-precharge. */
#define DDRCTRL_SCHED_LPR_NUM_ENTRIES_Pos        (8U)
#define DDRCTRL_SCHED_LPR_NUM_ENTRIES_Msk        (0xFU << DDRCTRL_SCHED_LPR_NUM_ENTRIES_Pos)         /*!< 0x00000F00 */
#define DDRCTRL_SCHED_LPR_NUM_ENTRIES            DDRCTRL_SCHED_LPR_NUM_ENTRIES_Msk                   /*!< Number of entries in the low priority transaction store is this value + 1. */
#define DDRCTRL_SCHED_LPR_NUM_ENTRIES_0          (0x1U << DDRCTRL_SCHED_LPR_NUM_ENTRIES_Pos)         /*!< 0x00000100 */
#define DDRCTRL_SCHED_LPR_NUM_ENTRIES_1          (0x2U << DDRCTRL_SCHED_LPR_NUM_ENTRIES_Pos)         /*!< 0x00000200 */
#define DDRCTRL_SCHED_LPR_NUM_ENTRIES_2          (0x4U << DDRCTRL_SCHED_LPR_NUM_ENTRIES_Pos)         /*!< 0x00000400 */
#define DDRCTRL_SCHED_LPR_NUM_ENTRIES_3          (0x8U << DDRCTRL_SCHED_LPR_NUM_ENTRIES_Pos)         /*!< 0x00000800 */
#define DDRCTRL_SCHED_GO2CRITICAL_HYSTERESIS_Pos (16U)
#define DDRCTRL_SCHED_GO2CRITICAL_HYSTERESIS_Msk (0xFFU << DDRCTRL_SCHED_GO2CRITICAL_HYSTERESIS_Pos) /*!< 0x00FF0000 */
#define DDRCTRL_SCHED_GO2CRITICAL_HYSTERESIS     DDRCTRL_SCHED_GO2CRITICAL_HYSTERESIS_Msk            /*!< UNUSED */
#define DDRCTRL_SCHED_GO2CRITICAL_HYSTERESIS_0   (0x1U << DDRCTRL_SCHED_GO2CRITICAL_HYSTERESIS_Pos)  /*!< 0x00010000 */
#define DDRCTRL_SCHED_GO2CRITICAL_HYSTERESIS_1   (0x2U << DDRCTRL_SCHED_GO2CRITICAL_HYSTERESIS_Pos)  /*!< 0x00020000 */
#define DDRCTRL_SCHED_GO2CRITICAL_HYSTERESIS_2   (0x4U << DDRCTRL_SCHED_GO2CRITICAL_HYSTERESIS_Pos)  /*!< 0x00040000 */
#define DDRCTRL_SCHED_GO2CRITICAL_HYSTERESIS_3   (0x8U << DDRCTRL_SCHED_GO2CRITICAL_HYSTERESIS_Pos)  /*!< 0x00080000 */
#define DDRCTRL_SCHED_GO2CRITICAL_HYSTERESIS_4   (0x10U << DDRCTRL_SCHED_GO2CRITICAL_HYSTERESIS_Pos) /*!< 0x00100000 */
#define DDRCTRL_SCHED_GO2CRITICAL_HYSTERESIS_5   (0x20U << DDRCTRL_SCHED_GO2CRITICAL_HYSTERESIS_Pos) /*!< 0x00200000 */
#define DDRCTRL_SCHED_GO2CRITICAL_HYSTERESIS_6   (0x40U << DDRCTRL_SCHED_GO2CRITICAL_HYSTERESIS_Pos) /*!< 0x00400000 */
#define DDRCTRL_SCHED_GO2CRITICAL_HYSTERESIS_7   (0x80U << DDRCTRL_SCHED_GO2CRITICAL_HYSTERESIS_Pos) /*!< 0x00800000 */
#define DDRCTRL_SCHED_RDWR_IDLE_GAP_Pos          (24U)
#define DDRCTRL_SCHED_RDWR_IDLE_GAP_Msk          (0x7FU << DDRCTRL_SCHED_RDWR_IDLE_GAP_Pos)          /*!< 0x7F000000 */
#define DDRCTRL_SCHED_RDWR_IDLE_GAP              DDRCTRL_SCHED_RDWR_IDLE_GAP_Msk                     /*!< When the preferred transaction store is empty for these many clock cycles, switch to the alternate transaction store if it is non-empty. */
#define DDRCTRL_SCHED_RDWR_IDLE_GAP_0            (0x1U << DDRCTRL_SCHED_RDWR_IDLE_GAP_Pos)           /*!< 0x01000000 */
#define DDRCTRL_SCHED_RDWR_IDLE_GAP_1            (0x2U << DDRCTRL_SCHED_RDWR_IDLE_GAP_Pos)           /*!< 0x02000000 */
#define DDRCTRL_SCHED_RDWR_IDLE_GAP_2            (0x4U << DDRCTRL_SCHED_RDWR_IDLE_GAP_Pos)           /*!< 0x04000000 */
#define DDRCTRL_SCHED_RDWR_IDLE_GAP_3            (0x8U << DDRCTRL_SCHED_RDWR_IDLE_GAP_Pos)           /*!< 0x08000000 */
#define DDRCTRL_SCHED_RDWR_IDLE_GAP_4            (0x10U << DDRCTRL_SCHED_RDWR_IDLE_GAP_Pos)          /*!< 0x10000000 */
#define DDRCTRL_SCHED_RDWR_IDLE_GAP_5            (0x20U << DDRCTRL_SCHED_RDWR_IDLE_GAP_Pos)          /*!< 0x20000000 */
#define DDRCTRL_SCHED_RDWR_IDLE_GAP_6            (0x40U << DDRCTRL_SCHED_RDWR_IDLE_GAP_Pos)          /*!< 0x40000000 */

/****************  Bit definition for DDRCTRL_SCHED1 register  ****************/
#define DDRCTRL_SCHED1_PAGECLOSE_TIMER_Pos (0U)
#define DDRCTRL_SCHED1_PAGECLOSE_TIMER_Msk (0xFFU << DDRCTRL_SCHED1_PAGECLOSE_TIMER_Pos) /*!< 0x000000FF */
#define DDRCTRL_SCHED1_PAGECLOSE_TIMER     DDRCTRL_SCHED1_PAGECLOSE_TIMER_Msk            /*!< This field works in conjunction with SCHED.pageclose. */
#define DDRCTRL_SCHED1_PAGECLOSE_TIMER_0   (0x1U << DDRCTRL_SCHED1_PAGECLOSE_TIMER_Pos)  /*!< 0x00000001 */
#define DDRCTRL_SCHED1_PAGECLOSE_TIMER_1   (0x2U << DDRCTRL_SCHED1_PAGECLOSE_TIMER_Pos)  /*!< 0x00000002 */
#define DDRCTRL_SCHED1_PAGECLOSE_TIMER_2   (0x4U << DDRCTRL_SCHED1_PAGECLOSE_TIMER_Pos)  /*!< 0x00000004 */
#define DDRCTRL_SCHED1_PAGECLOSE_TIMER_3   (0x8U << DDRCTRL_SCHED1_PAGECLOSE_TIMER_Pos)  /*!< 0x00000008 */
#define DDRCTRL_SCHED1_PAGECLOSE_TIMER_4   (0x10U << DDRCTRL_SCHED1_PAGECLOSE_TIMER_Pos) /*!< 0x00000010 */
#define DDRCTRL_SCHED1_PAGECLOSE_TIMER_5   (0x20U << DDRCTRL_SCHED1_PAGECLOSE_TIMER_Pos) /*!< 0x00000020 */
#define DDRCTRL_SCHED1_PAGECLOSE_TIMER_6   (0x40U << DDRCTRL_SCHED1_PAGECLOSE_TIMER_Pos) /*!< 0x00000040 */
#define DDRCTRL_SCHED1_PAGECLOSE_TIMER_7   (0x80U << DDRCTRL_SCHED1_PAGECLOSE_TIMER_Pos) /*!< 0x00000080 */

/***************  Bit definition for DDRCTRL_PERFHPR1 register  ***************/
#define DDRCTRL_PERFHPR1_HPR_MAX_STARVE_Pos      (0U)
#define DDRCTRL_PERFHPR1_HPR_MAX_STARVE_Msk      (0xFFFFU << DDRCTRL_PERFHPR1_HPR_MAX_STARVE_Pos)    /*!< 0x0000FFFF */
#define DDRCTRL_PERFHPR1_HPR_MAX_STARVE          DDRCTRL_PERFHPR1_HPR_MAX_STARVE_Msk                 /*!< Number of DFI clocks that the HPR queue can be starved before it goes critical. The minimum valid functional value for this register is 0x1. Programming it to 0x0 disables the starvation functionality; during normal operation, this function must not be disabled as it causes excessive latencies. */
#define DDRCTRL_PERFHPR1_HPR_MAX_STARVE_0        (0x1U << DDRCTRL_PERFHPR1_HPR_MAX_STARVE_Pos)       /*!< 0x00000001 */
#define DDRCTRL_PERFHPR1_HPR_MAX_STARVE_1        (0x2U << DDRCTRL_PERFHPR1_HPR_MAX_STARVE_Pos)       /*!< 0x00000002 */
#define DDRCTRL_PERFHPR1_HPR_MAX_STARVE_2        (0x4U << DDRCTRL_PERFHPR1_HPR_MAX_STARVE_Pos)       /*!< 0x00000004 */
#define DDRCTRL_PERFHPR1_HPR_MAX_STARVE_3        (0x8U << DDRCTRL_PERFHPR1_HPR_MAX_STARVE_Pos)       /*!< 0x00000008 */
#define DDRCTRL_PERFHPR1_HPR_MAX_STARVE_4        (0x10U << DDRCTRL_PERFHPR1_HPR_MAX_STARVE_Pos)      /*!< 0x00000010 */
#define DDRCTRL_PERFHPR1_HPR_MAX_STARVE_5        (0x20U << DDRCTRL_PERFHPR1_HPR_MAX_STARVE_Pos)      /*!< 0x00000020 */
#define DDRCTRL_PERFHPR1_HPR_MAX_STARVE_6        (0x40U << DDRCTRL_PERFHPR1_HPR_MAX_STARVE_Pos)      /*!< 0x00000040 */
#define DDRCTRL_PERFHPR1_HPR_MAX_STARVE_7        (0x80U << DDRCTRL_PERFHPR1_HPR_MAX_STARVE_Pos)      /*!< 0x00000080 */
#define DDRCTRL_PERFHPR1_HPR_MAX_STARVE_8        (0x100U << DDRCTRL_PERFHPR1_HPR_MAX_STARVE_Pos)     /*!< 0x00000100 */
#define DDRCTRL_PERFHPR1_HPR_MAX_STARVE_9        (0x200U << DDRCTRL_PERFHPR1_HPR_MAX_STARVE_Pos)     /*!< 0x00000200 */
#define DDRCTRL_PERFHPR1_HPR_MAX_STARVE_10       (0x400U << DDRCTRL_PERFHPR1_HPR_MAX_STARVE_Pos)     /*!< 0x00000400 */
#define DDRCTRL_PERFHPR1_HPR_MAX_STARVE_11       (0x800U << DDRCTRL_PERFHPR1_HPR_MAX_STARVE_Pos)     /*!< 0x00000800 */
#define DDRCTRL_PERFHPR1_HPR_MAX_STARVE_12       (0x1000U << DDRCTRL_PERFHPR1_HPR_MAX_STARVE_Pos)    /*!< 0x00001000 */
#define DDRCTRL_PERFHPR1_HPR_MAX_STARVE_13       (0x2000U << DDRCTRL_PERFHPR1_HPR_MAX_STARVE_Pos)    /*!< 0x00002000 */
#define DDRCTRL_PERFHPR1_HPR_MAX_STARVE_14       (0x4000U << DDRCTRL_PERFHPR1_HPR_MAX_STARVE_Pos)    /*!< 0x00004000 */
#define DDRCTRL_PERFHPR1_HPR_MAX_STARVE_15       (0x8000U << DDRCTRL_PERFHPR1_HPR_MAX_STARVE_Pos)    /*!< 0x00008000 */
#define DDRCTRL_PERFHPR1_HPR_XACT_RUN_LENGTH_Pos (24U)
#define DDRCTRL_PERFHPR1_HPR_XACT_RUN_LENGTH_Msk (0xFFU << DDRCTRL_PERFHPR1_HPR_XACT_RUN_LENGTH_Pos) /*!< 0xFF000000 */
#define DDRCTRL_PERFHPR1_HPR_XACT_RUN_LENGTH      DDRCTRL_PERFHPR1_HPR_XACT_RUN_LENGTH_Msk           /*!< Number of transactions that are serviced once the HPR queue goes critical is the smaller of: */
#define DDRCTRL_PERFHPR1_HPR_XACT_RUN_LENGTH_0   (0x1U << DDRCTRL_PERFHPR1_HPR_XACT_RUN_LENGTH_Pos)  /*!< 0x01000000 */
#define DDRCTRL_PERFHPR1_HPR_XACT_RUN_LENGTH_1   (0x2U << DDRCTRL_PERFHPR1_HPR_XACT_RUN_LENGTH_Pos)  /*!< 0x02000000 */
#define DDRCTRL_PERFHPR1_HPR_XACT_RUN_LENGTH_2   (0x4U << DDRCTRL_PERFHPR1_HPR_XACT_RUN_LENGTH_Pos)  /*!< 0x04000000 */
#define DDRCTRL_PERFHPR1_HPR_XACT_RUN_LENGTH_3   (0x8U << DDRCTRL_PERFHPR1_HPR_XACT_RUN_LENGTH_Pos)  /*!< 0x08000000 */
#define DDRCTRL_PERFHPR1_HPR_XACT_RUN_LENGTH_4   (0x10U << DDRCTRL_PERFHPR1_HPR_XACT_RUN_LENGTH_Pos) /*!< 0x10000000 */
#define DDRCTRL_PERFHPR1_HPR_XACT_RUN_LENGTH_5   (0x20U << DDRCTRL_PERFHPR1_HPR_XACT_RUN_LENGTH_Pos) /*!< 0x20000000 */
#define DDRCTRL_PERFHPR1_HPR_XACT_RUN_LENGTH_6   (0x40U << DDRCTRL_PERFHPR1_HPR_XACT_RUN_LENGTH_Pos) /*!< 0x40000000 */
#define DDRCTRL_PERFHPR1_HPR_XACT_RUN_LENGTH_7   (0x80U << DDRCTRL_PERFHPR1_HPR_XACT_RUN_LENGTH_Pos) /*!< 0x80000000 */

/***************  Bit definition for DDRCTRL_PERFLPR1 register  ***************/
#define DDRCTRL_PERFLPR1_LPR_MAX_STARVE_Pos      (0U)
#define DDRCTRL_PERFLPR1_LPR_MAX_STARVE_Msk      (0xFFFFU << DDRCTRL_PERFLPR1_LPR_MAX_STARVE_Pos)    /*!< 0x0000FFFF */
#define DDRCTRL_PERFLPR1_LPR_MAX_STARVE          DDRCTRL_PERFLPR1_LPR_MAX_STARVE_Msk                 /*!< Number of DFI clocks that the LPR queue can be starved before it goes critical. The minimum valid functional value for this register is 0x1. Programming it to 0x0 disables the starvation functionality; during normal operation, this function must be disabled as it causes excessive latencies. */
#define DDRCTRL_PERFLPR1_LPR_MAX_STARVE_0        (0x1U << DDRCTRL_PERFLPR1_LPR_MAX_STARVE_Pos)       /*!< 0x00000001 */
#define DDRCTRL_PERFLPR1_LPR_MAX_STARVE_1        (0x2U << DDRCTRL_PERFLPR1_LPR_MAX_STARVE_Pos)       /*!< 0x00000002 */
#define DDRCTRL_PERFLPR1_LPR_MAX_STARVE_2        (0x4U << DDRCTRL_PERFLPR1_LPR_MAX_STARVE_Pos)       /*!< 0x00000004 */
#define DDRCTRL_PERFLPR1_LPR_MAX_STARVE_3        (0x8U << DDRCTRL_PERFLPR1_LPR_MAX_STARVE_Pos)       /*!< 0x00000008 */
#define DDRCTRL_PERFLPR1_LPR_MAX_STARVE_4        (0x10U << DDRCTRL_PERFLPR1_LPR_MAX_STARVE_Pos)      /*!< 0x00000010 */
#define DDRCTRL_PERFLPR1_LPR_MAX_STARVE_5        (0x20U << DDRCTRL_PERFLPR1_LPR_MAX_STARVE_Pos)      /*!< 0x00000020 */
#define DDRCTRL_PERFLPR1_LPR_MAX_STARVE_6        (0x40U << DDRCTRL_PERFLPR1_LPR_MAX_STARVE_Pos)      /*!< 0x00000040 */
#define DDRCTRL_PERFLPR1_LPR_MAX_STARVE_7        (0x80U << DDRCTRL_PERFLPR1_LPR_MAX_STARVE_Pos)      /*!< 0x00000080 */
#define DDRCTRL_PERFLPR1_LPR_MAX_STARVE_8        (0x100U << DDRCTRL_PERFLPR1_LPR_MAX_STARVE_Pos)     /*!< 0x00000100 */
#define DDRCTRL_PERFLPR1_LPR_MAX_STARVE_9        (0x200U << DDRCTRL_PERFLPR1_LPR_MAX_STARVE_Pos)     /*!< 0x00000200 */
#define DDRCTRL_PERFLPR1_LPR_MAX_STARVE_10       (0x400U << DDRCTRL_PERFLPR1_LPR_MAX_STARVE_Pos)     /*!< 0x00000400 */
#define DDRCTRL_PERFLPR1_LPR_MAX_STARVE_11       (0x800U << DDRCTRL_PERFLPR1_LPR_MAX_STARVE_Pos)     /*!< 0x00000800 */
#define DDRCTRL_PERFLPR1_LPR_MAX_STARVE_12       (0x1000U << DDRCTRL_PERFLPR1_LPR_MAX_STARVE_Pos)    /*!< 0x00001000 */
#define DDRCTRL_PERFLPR1_LPR_MAX_STARVE_13       (0x2000U << DDRCTRL_PERFLPR1_LPR_MAX_STARVE_Pos)    /*!< 0x00002000 */
#define DDRCTRL_PERFLPR1_LPR_MAX_STARVE_14       (0x4000U << DDRCTRL_PERFLPR1_LPR_MAX_STARVE_Pos)    /*!< 0x00004000 */
#define DDRCTRL_PERFLPR1_LPR_MAX_STARVE_15       (0x8000U << DDRCTRL_PERFLPR1_LPR_MAX_STARVE_Pos)    /*!< 0x00008000 */
#define DDRCTRL_PERFLPR1_LPR_XACT_RUN_LENGTH_Pos (24U)
#define DDRCTRL_PERFLPR1_LPR_XACT_RUN_LENGTH_Msk (0xFFU << DDRCTRL_PERFLPR1_LPR_XACT_RUN_LENGTH_Pos) /*!< 0xFF000000 */
#define DDRCTRL_PERFLPR1_LPR_XACT_RUN_LENGTH     DDRCTRL_PERFLPR1_LPR_XACT_RUN_LENGTH_Msk            /*!< Number of transactions that are serviced once the LPR queue goes critical is the smaller of: */
#define DDRCTRL_PERFLPR1_LPR_XACT_RUN_LENGTH_0   (0x1U << DDRCTRL_PERFLPR1_LPR_XACT_RUN_LENGTH_Pos)  /*!< 0x01000000 */
#define DDRCTRL_PERFLPR1_LPR_XACT_RUN_LENGTH_1   (0x2U << DDRCTRL_PERFLPR1_LPR_XACT_RUN_LENGTH_Pos)  /*!< 0x02000000 */
#define DDRCTRL_PERFLPR1_LPR_XACT_RUN_LENGTH_2   (0x4U << DDRCTRL_PERFLPR1_LPR_XACT_RUN_LENGTH_Pos)  /*!< 0x04000000 */
#define DDRCTRL_PERFLPR1_LPR_XACT_RUN_LENGTH_3   (0x8U << DDRCTRL_PERFLPR1_LPR_XACT_RUN_LENGTH_Pos)  /*!< 0x08000000 */
#define DDRCTRL_PERFLPR1_LPR_XACT_RUN_LENGTH_4   (0x10U << DDRCTRL_PERFLPR1_LPR_XACT_RUN_LENGTH_Pos) /*!< 0x10000000 */
#define DDRCTRL_PERFLPR1_LPR_XACT_RUN_LENGTH_5   (0x20U << DDRCTRL_PERFLPR1_LPR_XACT_RUN_LENGTH_Pos) /*!< 0x20000000 */
#define DDRCTRL_PERFLPR1_LPR_XACT_RUN_LENGTH_6   (0x40U << DDRCTRL_PERFLPR1_LPR_XACT_RUN_LENGTH_Pos) /*!< 0x40000000 */
#define DDRCTRL_PERFLPR1_LPR_XACT_RUN_LENGTH_7   (0x80U << DDRCTRL_PERFLPR1_LPR_XACT_RUN_LENGTH_Pos) /*!< 0x80000000 */

/***************  Bit definition for DDRCTRL_PERFWR1 register  ****************/
#define DDRCTRL_PERFWR1_W_MAX_STARVE_Pos      (0U)
#define DDRCTRL_PERFWR1_W_MAX_STARVE_Msk      (0xFFFFU << DDRCTRL_PERFWR1_W_MAX_STARVE_Pos)    /*!< 0x0000FFFF */
#define DDRCTRL_PERFWR1_W_MAX_STARVE          DDRCTRL_PERFWR1_W_MAX_STARVE_Msk                 /*!< Number of DFI clocks that the WR queue can be starved before it goes critical. The minimum valid functional value for this register is 0x1. Programming it to 0x0 disables the starvation functionality; during normal operation, this function must not be disabled as it causes excessive latencies. */
#define DDRCTRL_PERFWR1_W_MAX_STARVE_0        (0x1U << DDRCTRL_PERFWR1_W_MAX_STARVE_Pos)       /*!< 0x00000001 */
#define DDRCTRL_PERFWR1_W_MAX_STARVE_1        (0x2U << DDRCTRL_PERFWR1_W_MAX_STARVE_Pos)       /*!< 0x00000002 */
#define DDRCTRL_PERFWR1_W_MAX_STARVE_2        (0x4U << DDRCTRL_PERFWR1_W_MAX_STARVE_Pos)       /*!< 0x00000004 */
#define DDRCTRL_PERFWR1_W_MAX_STARVE_3        (0x8U << DDRCTRL_PERFWR1_W_MAX_STARVE_Pos)       /*!< 0x00000008 */
#define DDRCTRL_PERFWR1_W_MAX_STARVE_4        (0x10U << DDRCTRL_PERFWR1_W_MAX_STARVE_Pos)      /*!< 0x00000010 */
#define DDRCTRL_PERFWR1_W_MAX_STARVE_5        (0x20U << DDRCTRL_PERFWR1_W_MAX_STARVE_Pos)      /*!< 0x00000020 */
#define DDRCTRL_PERFWR1_W_MAX_STARVE_6        (0x40U << DDRCTRL_PERFWR1_W_MAX_STARVE_Pos)      /*!< 0x00000040 */
#define DDRCTRL_PERFWR1_W_MAX_STARVE_7        (0x80U << DDRCTRL_PERFWR1_W_MAX_STARVE_Pos)      /*!< 0x00000080 */
#define DDRCTRL_PERFWR1_W_MAX_STARVE_8        (0x100U << DDRCTRL_PERFWR1_W_MAX_STARVE_Pos)     /*!< 0x00000100 */
#define DDRCTRL_PERFWR1_W_MAX_STARVE_9        (0x200U << DDRCTRL_PERFWR1_W_MAX_STARVE_Pos)     /*!< 0x00000200 */
#define DDRCTRL_PERFWR1_W_MAX_STARVE_10       (0x400U << DDRCTRL_PERFWR1_W_MAX_STARVE_Pos)     /*!< 0x00000400 */
#define DDRCTRL_PERFWR1_W_MAX_STARVE_11       (0x800U << DDRCTRL_PERFWR1_W_MAX_STARVE_Pos)     /*!< 0x00000800 */
#define DDRCTRL_PERFWR1_W_MAX_STARVE_12       (0x1000U << DDRCTRL_PERFWR1_W_MAX_STARVE_Pos)    /*!< 0x00001000 */
#define DDRCTRL_PERFWR1_W_MAX_STARVE_13       (0x2000U << DDRCTRL_PERFWR1_W_MAX_STARVE_Pos)    /*!< 0x00002000 */
#define DDRCTRL_PERFWR1_W_MAX_STARVE_14       (0x4000U << DDRCTRL_PERFWR1_W_MAX_STARVE_Pos)    /*!< 0x00004000 */
#define DDRCTRL_PERFWR1_W_MAX_STARVE_15       (0x8000U << DDRCTRL_PERFWR1_W_MAX_STARVE_Pos)    /*!< 0x00008000 */
#define DDRCTRL_PERFWR1_W_XACT_RUN_LENGTH_Pos (24U)
#define DDRCTRL_PERFWR1_W_XACT_RUN_LENGTH_Msk (0xFFU << DDRCTRL_PERFWR1_W_XACT_RUN_LENGTH_Pos) /*!< 0xFF000000 */
#define DDRCTRL_PERFWR1_W_XACT_RUN_LENGTH     DDRCTRL_PERFWR1_W_XACT_RUN_LENGTH_Msk            /*!< Number of transactions that are serviced once the WR queue goes critical is the smaller of: */
#define DDRCTRL_PERFWR1_W_XACT_RUN_LENGTH_0   (0x1U << DDRCTRL_PERFWR1_W_XACT_RUN_LENGTH_Pos)  /*!< 0x01000000 */
#define DDRCTRL_PERFWR1_W_XACT_RUN_LENGTH_1   (0x2U << DDRCTRL_PERFWR1_W_XACT_RUN_LENGTH_Pos)  /*!< 0x02000000 */
#define DDRCTRL_PERFWR1_W_XACT_RUN_LENGTH_2   (0x4U << DDRCTRL_PERFWR1_W_XACT_RUN_LENGTH_Pos)  /*!< 0x04000000 */
#define DDRCTRL_PERFWR1_W_XACT_RUN_LENGTH_3   (0x8U << DDRCTRL_PERFWR1_W_XACT_RUN_LENGTH_Pos)  /*!< 0x08000000 */
#define DDRCTRL_PERFWR1_W_XACT_RUN_LENGTH_4   (0x10U << DDRCTRL_PERFWR1_W_XACT_RUN_LENGTH_Pos) /*!< 0x10000000 */
#define DDRCTRL_PERFWR1_W_XACT_RUN_LENGTH_5   (0x20U << DDRCTRL_PERFWR1_W_XACT_RUN_LENGTH_Pos) /*!< 0x20000000 */
#define DDRCTRL_PERFWR1_W_XACT_RUN_LENGTH_6   (0x40U << DDRCTRL_PERFWR1_W_XACT_RUN_LENGTH_Pos) /*!< 0x40000000 */
#define DDRCTRL_PERFWR1_W_XACT_RUN_LENGTH_7   (0x80U << DDRCTRL_PERFWR1_W_XACT_RUN_LENGTH_Pos) /*!< 0x80000000 */

/*****************  Bit definition for DDRCTRL_DBG0 register  *****************/
#define DDRCTRL_DBG0_DIS_WC_Pos                 (0U)
#define DDRCTRL_DBG0_DIS_WC_Msk                 (0x1U << DDRCTRL_DBG0_DIS_WC_Pos)                 /*!< 0x00000001 */
#define DDRCTRL_DBG0_DIS_WC                     DDRCTRL_DBG0_DIS_WC_Msk                           /*!< When 1, disable write combine. */
#define DDRCTRL_DBG0_DIS_COLLISION_PAGE_OPT_Pos (4U)
#define DDRCTRL_DBG0_DIS_COLLISION_PAGE_OPT_Msk (0x1U << DDRCTRL_DBG0_DIS_COLLISION_PAGE_OPT_Pos) /*!< 0x00000010 */
#define DDRCTRL_DBG0_DIS_COLLISION_PAGE_OPT     DDRCTRL_DBG0_DIS_COLLISION_PAGE_OPT_Msk           /*!< When this is set to \q0\q, auto-precharge is disabled for the flushed command in a collision case. Collision cases are write followed by read to same address, read followed by write to same address, or write followed by write to same address with DBG0.dis_wc bit = 1 (where same address comparisons exclude the two address bits representing critical word). */

/*****************  Bit definition for DDRCTRL_DBG1 register  *****************/
#define DDRCTRL_DBG1_DIS_DQ_Pos  (0U)
#define DDRCTRL_DBG1_DIS_DQ_Msk  (0x1U << DDRCTRL_DBG1_DIS_DQ_Pos)  /*!< 0x00000001 */
#define DDRCTRL_DBG1_DIS_DQ      DDRCTRL_DBG1_DIS_DQ_Msk            /*!< When 1, DDRCTRL does not de-queue any transactions from the CAM. Bypass is also disabled. All transactions are queued in the CAM. No reads or writes are issued to SDRAM as long as this is asserted. */
#define DDRCTRL_DBG1_DIS_HIF_Pos (1U)
#define DDRCTRL_DBG1_DIS_HIF_Msk (0x1U << DDRCTRL_DBG1_DIS_HIF_Pos) /*!< 0x00000002 */
#define DDRCTRL_DBG1_DIS_HIF     DDRCTRL_DBG1_DIS_HIF_Msk           /*!< When 1, DDRCTRL asserts the HIF command signal hif_cmd_stall. DDRCTRL ignores the hif_cmd_valid and all other associated request signals. */

/****************  Bit definition for DDRCTRL_DBGCAM register  ****************/
#define DDRCTRL_DBGCAM_DBG_HPR_Q_DEPTH_Pos        (0U)
#define DDRCTRL_DBGCAM_DBG_HPR_Q_DEPTH_Msk        (0x1FU << DDRCTRL_DBGCAM_DBG_HPR_Q_DEPTH_Pos)       /*!< 0x0000001F */
#define DDRCTRL_DBGCAM_DBG_HPR_Q_DEPTH            DDRCTRL_DBGCAM_DBG_HPR_Q_DEPTH_Msk                  /*!< High priority read queue depth */
#define DDRCTRL_DBGCAM_DBG_HPR_Q_DEPTH_0          (0x1U << DDRCTRL_DBGCAM_DBG_HPR_Q_DEPTH_Pos)        /*!< 0x00000001 */
#define DDRCTRL_DBGCAM_DBG_HPR_Q_DEPTH_1          (0x2U << DDRCTRL_DBGCAM_DBG_HPR_Q_DEPTH_Pos)        /*!< 0x00000002 */
#define DDRCTRL_DBGCAM_DBG_HPR_Q_DEPTH_2          (0x4U << DDRCTRL_DBGCAM_DBG_HPR_Q_DEPTH_Pos)        /*!< 0x00000004 */
#define DDRCTRL_DBGCAM_DBG_HPR_Q_DEPTH_3          (0x8U << DDRCTRL_DBGCAM_DBG_HPR_Q_DEPTH_Pos)        /*!< 0x00000008 */
#define DDRCTRL_DBGCAM_DBG_HPR_Q_DEPTH_4          (0x10U << DDRCTRL_DBGCAM_DBG_HPR_Q_DEPTH_Pos)       /*!< 0x00000010 */
#define DDRCTRL_DBGCAM_DBG_LPR_Q_DEPTH_Pos        (8U)
#define DDRCTRL_DBGCAM_DBG_LPR_Q_DEPTH_Msk        (0x1FU << DDRCTRL_DBGCAM_DBG_LPR_Q_DEPTH_Pos)       /*!< 0x00001F00 */
#define DDRCTRL_DBGCAM_DBG_LPR_Q_DEPTH            DDRCTRL_DBGCAM_DBG_LPR_Q_DEPTH_Msk                  /*!< Low priority read queue depth */
#define DDRCTRL_DBGCAM_DBG_LPR_Q_DEPTH_0          (0x1U << DDRCTRL_DBGCAM_DBG_LPR_Q_DEPTH_Pos)        /*!< 0x00000100 */
#define DDRCTRL_DBGCAM_DBG_LPR_Q_DEPTH_1          (0x2U << DDRCTRL_DBGCAM_DBG_LPR_Q_DEPTH_Pos)        /*!< 0x00000200 */
#define DDRCTRL_DBGCAM_DBG_LPR_Q_DEPTH_2          (0x4U << DDRCTRL_DBGCAM_DBG_LPR_Q_DEPTH_Pos)        /*!< 0x00000400 */
#define DDRCTRL_DBGCAM_DBG_LPR_Q_DEPTH_3          (0x8U << DDRCTRL_DBGCAM_DBG_LPR_Q_DEPTH_Pos)        /*!< 0x00000800 */
#define DDRCTRL_DBGCAM_DBG_LPR_Q_DEPTH_4          (0x10U << DDRCTRL_DBGCAM_DBG_LPR_Q_DEPTH_Pos)       /*!< 0x00001000 */
#define DDRCTRL_DBGCAM_DBG_W_Q_DEPTH_Pos          (16U)
#define DDRCTRL_DBGCAM_DBG_W_Q_DEPTH_Msk          (0x1FU << DDRCTRL_DBGCAM_DBG_W_Q_DEPTH_Pos)         /*!< 0x001F0000 */
#define DDRCTRL_DBGCAM_DBG_W_Q_DEPTH              DDRCTRL_DBGCAM_DBG_W_Q_DEPTH_Msk                    /*!< Write queue depth */
#define DDRCTRL_DBGCAM_DBG_W_Q_DEPTH_0            (0x1U << DDRCTRL_DBGCAM_DBG_W_Q_DEPTH_Pos)          /*!< 0x00010000 */
#define DDRCTRL_DBGCAM_DBG_W_Q_DEPTH_1            (0x2U << DDRCTRL_DBGCAM_DBG_W_Q_DEPTH_Pos)          /*!< 0x00020000 */
#define DDRCTRL_DBGCAM_DBG_W_Q_DEPTH_2            (0x4U << DDRCTRL_DBGCAM_DBG_W_Q_DEPTH_Pos)          /*!< 0x00040000 */
#define DDRCTRL_DBGCAM_DBG_W_Q_DEPTH_3            (0x8U << DDRCTRL_DBGCAM_DBG_W_Q_DEPTH_Pos)          /*!< 0x00080000 */
#define DDRCTRL_DBGCAM_DBG_W_Q_DEPTH_4            (0x10U << DDRCTRL_DBGCAM_DBG_W_Q_DEPTH_Pos)         /*!< 0x00100000 */
#define DDRCTRL_DBGCAM_DBG_STALL_Pos              (24U)
#define DDRCTRL_DBGCAM_DBG_STALL_Msk              (0x1U << DDRCTRL_DBGCAM_DBG_STALL_Pos)              /*!< 0x01000000 */
#define DDRCTRL_DBGCAM_DBG_STALL                  DDRCTRL_DBGCAM_DBG_STALL_Msk                        /*!< Stall */
#define DDRCTRL_DBGCAM_DBG_RD_Q_EMPTY_Pos         (25U)
#define DDRCTRL_DBGCAM_DBG_RD_Q_EMPTY_Msk         (0x1U << DDRCTRL_DBGCAM_DBG_RD_Q_EMPTY_Pos)         /*!< 0x02000000 */
#define DDRCTRL_DBGCAM_DBG_RD_Q_EMPTY             DDRCTRL_DBGCAM_DBG_RD_Q_EMPTY_Msk                   /*!< When 1, all the Read command queues and Read data buffers inside DDRC are empty. This register is to be used for debug purpose. */
#define DDRCTRL_DBGCAM_DBG_WR_Q_EMPTY_Pos         (26U)
#define DDRCTRL_DBGCAM_DBG_WR_Q_EMPTY_Msk         (0x1U << DDRCTRL_DBGCAM_DBG_WR_Q_EMPTY_Pos)         /*!< 0x04000000 */
#define DDRCTRL_DBGCAM_DBG_WR_Q_EMPTY             DDRCTRL_DBGCAM_DBG_WR_Q_EMPTY_Msk                   /*!< When 1, all the Write command queues and Write data buffers inside DDRC are empty. This register is to be used for debug purpose. */
#define DDRCTRL_DBGCAM_RD_DATA_PIPELINE_EMPTY_Pos (28U)
#define DDRCTRL_DBGCAM_RD_DATA_PIPELINE_EMPTY_Msk (0x1U << DDRCTRL_DBGCAM_RD_DATA_PIPELINE_EMPTY_Pos) /*!< 0x10000000 */
#define DDRCTRL_DBGCAM_RD_DATA_PIPELINE_EMPTY     DDRCTRL_DBGCAM_RD_DATA_PIPELINE_EMPTY_Msk           /*!< This bit indicates that the read data pipeline on the DFI interface is empty. This register is intended to be polled at least twice after setting DBG1.dis_dq, to ensure that all remaining commands/data have completed. */
#define DDRCTRL_DBGCAM_WR_DATA_PIPELINE_EMPTY_Pos (29U)
#define DDRCTRL_DBGCAM_WR_DATA_PIPELINE_EMPTY_Msk (0x1U << DDRCTRL_DBGCAM_WR_DATA_PIPELINE_EMPTY_Pos) /*!< 0x20000000 */
#define DDRCTRL_DBGCAM_WR_DATA_PIPELINE_EMPTY     DDRCTRL_DBGCAM_WR_DATA_PIPELINE_EMPTY_Msk           /*!< This bit indicates that the write data pipeline on the DFI interface is empty. This register is intended to be polled at least twice after setting DBG1.dis_dq, to ensure that all remaining commands/data have completed. */

/****************  Bit definition for DDRCTRL_DBGCMD register  ****************/
#define DDRCTRL_DBGCMD_RANK0_REFRESH_Pos  (0U)
#define DDRCTRL_DBGCMD_RANK0_REFRESH_Msk  (0x1U << DDRCTRL_DBGCMD_RANK0_REFRESH_Pos)  /*!< 0x00000001 */
#define DDRCTRL_DBGCMD_RANK0_REFRESH      DDRCTRL_DBGCMD_RANK0_REFRESH_Msk            /*!< Setting this register bit to 1 indicates to the DDRCTRL to issue a refresh to rank 0. Writing to this bit causes DBGSTAT.rank0_refresh_busy to be set. When DBGSTAT.rank0_refresh_busy is cleared, the command has been stored in DDRCTRL. */
#define DDRCTRL_DBGCMD_ZQ_CALIB_SHORT_Pos (4U)
#define DDRCTRL_DBGCMD_ZQ_CALIB_SHORT_Msk (0x1U << DDRCTRL_DBGCMD_ZQ_CALIB_SHORT_Pos) /*!< 0x00000010 */
#define DDRCTRL_DBGCMD_ZQ_CALIB_SHORT     DDRCTRL_DBGCMD_ZQ_CALIB_SHORT_Msk           /*!< Setting this register bit to 1 indicates to the DDRCTRL to issue a ZQCS (ZQ calibration short)/MPC(ZQ calibration) command to the SDRAM. When this request is stored in the DDRCTRL, the bit is automatically cleared. This operation can be performed only when ZQCTL0.dis_auto_zq=1. It is recommended NOT to set this register bit if in Init, in Self-Refresh(except LPDDR4) or SR-Powerdown(LPDDR4) or Deep power-down operating modes or maximum power saving mode. */
#define DDRCTRL_DBGCMD_CTRLUPD_Pos        (5U)
#define DDRCTRL_DBGCMD_CTRLUPD_Msk        (0x1U << DDRCTRL_DBGCMD_CTRLUPD_Pos)        /*!< 0x00000020 */
#define DDRCTRL_DBGCMD_CTRLUPD            DDRCTRL_DBGCMD_CTRLUPD_Msk                  /*!< Setting this register bit to 1 indicates to the DDRCTRL to issue a dfi_ctrlupd_req to the PHY. When this request is stored in the DDRCTRL, the bit is automatically cleared. This operation must only be performed when DFIUPD0.dis_auto_ctrlupd=1. */

/***************  Bit definition for DDRCTRL_DBGSTAT register  ****************/
#define DDRCTRL_DBGSTAT_RANK0_REFRESH_BUSY_Pos  (0U)
#define DDRCTRL_DBGSTAT_RANK0_REFRESH_BUSY_Msk  (0x1U << DDRCTRL_DBGSTAT_RANK0_REFRESH_BUSY_Pos)  /*!< 0x00000001 */
#define DDRCTRL_DBGSTAT_RANK0_REFRESH_BUSY      DDRCTRL_DBGSTAT_RANK0_REFRESH_BUSY_Msk            /*!< SoC core may initiate a rank0_refresh operation (refresh operation to rank 0) only if this signal is low. This signal goes high in the clock after DBGCMD.rank0_refresh is set to one. It goes low when the rank0_refresh operation is stored in the DDRCTRL. It is recommended not to perform rank0_refresh operations when this signal is high. */
#define DDRCTRL_DBGSTAT_ZQ_CALIB_SHORT_BUSY_Pos (4U)
#define DDRCTRL_DBGSTAT_ZQ_CALIB_SHORT_BUSY_Msk (0x1U << DDRCTRL_DBGSTAT_ZQ_CALIB_SHORT_BUSY_Pos) /*!< 0x00000010 */
#define DDRCTRL_DBGSTAT_ZQ_CALIB_SHORT_BUSY     DDRCTRL_DBGSTAT_ZQ_CALIB_SHORT_BUSY_Msk           /*!< SoC core may initiate a ZQCS (ZQ calibration short) operation only if this signal is low. This signal goes high in the clock after the DDRCTRL accepts the ZQCS request. It goes low when the ZQCS operation is initiated in the DDRCTRL. It is recommended not to perform ZQCS operations when this signal is high. */
#define DDRCTRL_DBGSTAT_CTRLUPD_BUSY_Pos        (5U)
#define DDRCTRL_DBGSTAT_CTRLUPD_BUSY_Msk        (0x1U << DDRCTRL_DBGSTAT_CTRLUPD_BUSY_Pos)        /*!< 0x00000020 */
#define DDRCTRL_DBGSTAT_CTRLUPD_BUSY            DDRCTRL_DBGSTAT_CTRLUPD_BUSY_Msk                  /*!< SoC core may initiate a ctrlupd operation only if this signal is low. This signal goes high in the clock after the DDRCTRL accepts the ctrlupd request. It goes low when the ctrlupd operation is initiated in the DDRCTRL. It is recommended not to perform ctrlupd operations when this signal is high. */

/****************  Bit definition for DDRCTRL_SWCTL register  *****************/
#define DDRCTRL_SWCTL_SW_DONE_Pos (0U)
#define DDRCTRL_SWCTL_SW_DONE_Msk (0x1U << DDRCTRL_SWCTL_SW_DONE_Pos) /*!< 0x00000001 */
#define DDRCTRL_SWCTL_SW_DONE     DDRCTRL_SWCTL_SW_DONE_Msk           /*!< Enable quasi-dynamic register programming outside reset. Program register to 0 to enable quasi-dynamic programming. Set back register to 1 once programming is done. */

/****************  Bit definition for DDRCTRL_SWSTAT register  ****************/
#define DDRCTRL_SWSTAT_SW_DONE_ACK_Pos (0U)
#define DDRCTRL_SWSTAT_SW_DONE_ACK_Msk (0x1U << DDRCTRL_SWSTAT_SW_DONE_ACK_Pos) /*!< 0x00000001 */
#define DDRCTRL_SWSTAT_SW_DONE_ACK     DDRCTRL_SWSTAT_SW_DONE_ACK_Msk           /*!< Register programming done. This register is the echo of SWCTL.sw_done. Wait for sw_done value 1 to propagate to sw_done_ack at the end of the programming sequence to ensure that the correct registers values are propagated to the destination clock domains. */

/**************  Bit definition for DDRCTRL_POISONCFG register  ***************/
#define DDRCTRL_POISONCFG_WR_POISON_SLVERR_EN_Pos (0U)
#define DDRCTRL_POISONCFG_WR_POISON_SLVERR_EN_Msk (0x1U << DDRCTRL_POISONCFG_WR_POISON_SLVERR_EN_Pos) /*!< 0x00000001 */
#define DDRCTRL_POISONCFG_WR_POISON_SLVERR_EN     DDRCTRL_POISONCFG_WR_POISON_SLVERR_EN_Msk           /*!< If set to 1, enables SLVERR response for write transaction poisoning */
#define DDRCTRL_POISONCFG_WR_POISON_INTR_EN_Pos   (4U)
#define DDRCTRL_POISONCFG_WR_POISON_INTR_EN_Msk   (0x1U << DDRCTRL_POISONCFG_WR_POISON_INTR_EN_Pos)   /*!< 0x00000010 */
#define DDRCTRL_POISONCFG_WR_POISON_INTR_EN       DDRCTRL_POISONCFG_WR_POISON_INTR_EN_Msk             /*!< If set to 1, enables interrupts for write transaction poisoning */
#define DDRCTRL_POISONCFG_WR_POISON_INTR_CLR_Pos  (8U)
#define DDRCTRL_POISONCFG_WR_POISON_INTR_CLR_Msk  (0x1U << DDRCTRL_POISONCFG_WR_POISON_INTR_CLR_Pos)  /*!< 0x00000100 */
#define DDRCTRL_POISONCFG_WR_POISON_INTR_CLR      DDRCTRL_POISONCFG_WR_POISON_INTR_CLR_Msk            /*!< Interrupt clear for write transaction poisoning. Allow 2/3 clock cycles for correct value to propagate to core logic and clear the interrupts. */
#define DDRCTRL_POISONCFG_RD_POISON_SLVERR_EN_Pos (16U)
#define DDRCTRL_POISONCFG_RD_POISON_SLVERR_EN_Msk (0x1U << DDRCTRL_POISONCFG_RD_POISON_SLVERR_EN_Pos) /*!< 0x00010000 */
#define DDRCTRL_POISONCFG_RD_POISON_SLVERR_EN     DDRCTRL_POISONCFG_RD_POISON_SLVERR_EN_Msk           /*!< If set to 1, enables SLVERR response for read transaction poisoning */
#define DDRCTRL_POISONCFG_RD_POISON_INTR_EN_Pos   (20U)
#define DDRCTRL_POISONCFG_RD_POISON_INTR_EN_Msk   (0x1U << DDRCTRL_POISONCFG_RD_POISON_INTR_EN_Pos)   /*!< 0x00100000 */
#define DDRCTRL_POISONCFG_RD_POISON_INTR_EN       DDRCTRL_POISONCFG_RD_POISON_INTR_EN_Msk             /*!< If set to 1, enables interrupts for read transaction poisoning */
#define DDRCTRL_POISONCFG_RD_POISON_INTR_CLR_Pos  (24U)
#define DDRCTRL_POISONCFG_RD_POISON_INTR_CLR_Msk  (0x1U << DDRCTRL_POISONCFG_RD_POISON_INTR_CLR_Pos)  /*!< 0x01000000 */
#define DDRCTRL_POISONCFG_RD_POISON_INTR_CLR      DDRCTRL_POISONCFG_RD_POISON_INTR_CLR_Msk            /*!< Interrupt clear for read transaction poisoning. Allow 2/3 clock cycles for correct value to propagate to core logic and clear the interrupts. */

/**************  Bit definition for DDRCTRL_POISONSTAT register  **************/
#define DDRCTRL_POISONSTAT_WR_POISON_INTR_0_Pos (0U)
#define DDRCTRL_POISONSTAT_WR_POISON_INTR_0_Msk (0x1U << DDRCTRL_POISONSTAT_WR_POISON_INTR_0_Pos) /*!< 0x00000001 */
#define DDRCTRL_POISONSTAT_WR_POISON_INTR_0     DDRCTRL_POISONSTAT_WR_POISON_INTR_0_Msk           /*!< Write transaction poisoning error interrupt for port 0. This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port\qs write address channel. Bit 0 corresponds to Port 0, and so on. Interrupt is cleared by register wr_poison_intr_clr, then value propagated to APB clock. */
#define DDRCTRL_POISONSTAT_WR_POISON_INTR_1_Pos (1U)
#define DDRCTRL_POISONSTAT_WR_POISON_INTR_1_Msk (0x1U << DDRCTRL_POISONSTAT_WR_POISON_INTR_1_Pos) /*!< 0x00000002 */
#define DDRCTRL_POISONSTAT_WR_POISON_INTR_1     DDRCTRL_POISONSTAT_WR_POISON_INTR_1_Msk           /*!< Write transaction poisoning error interrupt for port 1. This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port\qs write address channel. Bit 0 corresponds to Port 0, and so on. Interrupt is cleared by register wr_poison_intr_clr, then value propagated to APB clock. */
#define DDRCTRL_POISONSTAT_RD_POISON_INTR_0_Pos (16U)
#define DDRCTRL_POISONSTAT_RD_POISON_INTR_0_Msk (0x1U << DDRCTRL_POISONSTAT_RD_POISON_INTR_0_Pos) /*!< 0x00010000 */
#define DDRCTRL_POISONSTAT_RD_POISON_INTR_0     DDRCTRL_POISONSTAT_RD_POISON_INTR_0_Msk           /*!< Read transaction poisoning error interrupt for port 0. This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port\qs read address channel. Bit 0 corresponds to Port 0, and so on. Interrupt is cleared by register rd_poison_intr_clr, then value propagated to APB clock. */
#define DDRCTRL_POISONSTAT_RD_POISON_INTR_1_Pos (17U)
#define DDRCTRL_POISONSTAT_RD_POISON_INTR_1_Msk (0x1U << DDRCTRL_POISONSTAT_RD_POISON_INTR_1_Pos) /*!< 0x00020000 */
#define DDRCTRL_POISONSTAT_RD_POISON_INTR_1     DDRCTRL_POISONSTAT_RD_POISON_INTR_1_Msk           /*!< Read transaction poisoning error interrupt for port 1. This register is a APB clock copy (double register synchronizer) of the interrupt asserted when a transaction is poisoned on the corresponding AXI port\qs read address channel. Bit 0 corresponds to Port 0, and so on. Interrupt is cleared by register rd_poison_intr_clr, then value propagated to APB clock. */

/****************  Bit definition for DDRCTRL_PSTAT register  *****************/
#define DDRCTRL_PSTAT_RD_PORT_BUSY_0_Pos (0U)
#define DDRCTRL_PSTAT_RD_PORT_BUSY_0_Msk (0x1U << DDRCTRL_PSTAT_RD_PORT_BUSY_0_Pos) /*!< 0x00000001 */
#define DDRCTRL_PSTAT_RD_PORT_BUSY_0     DDRCTRL_PSTAT_RD_PORT_BUSY_0_Msk           /*!< Indicates if there are outstanding reads for AXI port 0. */
#define DDRCTRL_PSTAT_RD_PORT_BUSY_1_Pos (1U)
#define DDRCTRL_PSTAT_RD_PORT_BUSY_1_Msk (0x1U << DDRCTRL_PSTAT_RD_PORT_BUSY_1_Pos) /*!< 0x00000002 */
#define DDRCTRL_PSTAT_RD_PORT_BUSY_1     DDRCTRL_PSTAT_RD_PORT_BUSY_1_Msk           /*!< Indicates if there are outstanding reads for AXI port 1. */
#define DDRCTRL_PSTAT_WR_PORT_BUSY_0_Pos (16U)
#define DDRCTRL_PSTAT_WR_PORT_BUSY_0_Msk (0x1U << DDRCTRL_PSTAT_WR_PORT_BUSY_0_Pos) /*!< 0x00010000 */
#define DDRCTRL_PSTAT_WR_PORT_BUSY_0     DDRCTRL_PSTAT_WR_PORT_BUSY_0_Msk           /*!< Indicates if there are outstanding writes for AXI port 0. */
#define DDRCTRL_PSTAT_WR_PORT_BUSY_1_Pos (17U)
#define DDRCTRL_PSTAT_WR_PORT_BUSY_1_Msk (0x1U << DDRCTRL_PSTAT_WR_PORT_BUSY_1_Pos) /*!< 0x00020000 */
#define DDRCTRL_PSTAT_WR_PORT_BUSY_1     DDRCTRL_PSTAT_WR_PORT_BUSY_1_Msk           /*!< Indicates if there are outstanding writes for AXI port 1. */

/****************  Bit definition for DDRCTRL_PCCFG register  *****************/
#define DDRCTRL_PCCFG_GO2CRITICAL_EN_Pos  (0U)
#define DDRCTRL_PCCFG_GO2CRITICAL_EN_Msk  (0x1U << DDRCTRL_PCCFG_GO2CRITICAL_EN_Pos) /*!< 0x00000001 */
#define DDRCTRL_PCCFG_GO2CRITICAL_EN      DDRCTRL_PCCFG_GO2CRITICAL_EN_Msk           /*!< If set to 1 (enabled), sets co_gs_go2critical_wr and co_gs_go2critical_lpr/co_gs_go2critical_hpr signals going to DDRC based on urgent input (awurgent, arurgent) coming from AXI master. If set to 0 (disabled), co_gs_go2critical_wr and co_gs_go2critical_lpr/co_gs_go2critical_hpr signals at DDRC are driven to 1b\q0. */
#define DDRCTRL_PCCFG_PAGEMATCH_LIMIT_Pos (4U)
#define DDRCTRL_PCCFG_PAGEMATCH_LIMIT_Msk (0x1U << DDRCTRL_PCCFG_PAGEMATCH_LIMIT_Pos) /*!< 0x00000010 */
#define DDRCTRL_PCCFG_PAGEMATCH_LIMIT     DDRCTRL_PCCFG_PAGEMATCH_LIMIT_Msk           /*!< Page match four limit. If set to 1, limits the number of consecutive same page DDRC transactions that can be granted by the Port Arbiter to four when Page Match feature is enabled. If set to 0, there is no limit imposed on number of consecutive same page DDRC transactions. */
#define DDRCTRL_PCCFG_BL_EXP_MODE_Pos     (8U)
#define DDRCTRL_PCCFG_BL_EXP_MODE_Msk     (0x1U << DDRCTRL_PCCFG_BL_EXP_MODE_Pos)     /*!< 0x00000100 */
#define DDRCTRL_PCCFG_BL_EXP_MODE         DDRCTRL_PCCFG_BL_EXP_MODE_Msk               /*!< Burst length expansion mode. By default (i.e. bl_exp_mode==0) XPI expands every AXI burst into multiple HIF commands, using the memory burst length as a unit. If set to 1, then XPI uses half of the memory burst length as a unit. */

/***************  Bit definition for DDRCTRL_PCFGR_0 register  ****************/
#define DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_Pos     (0U)
#define DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_Msk     (0x3FFU << DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_Pos)   /*!< 0x000003FF */
#define DDRCTRL_PCFGR_0_RD_PORT_PRIORITY         DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_Msk               /*!< Determines the initial load value of read aging counters. These counters are parallel loaded after reset, or after each grant to the corresponding port. The aging counters down-count every clock cycle where the port is requesting but not granted. The higher significant 5-bits of the read aging counter sets the priority of the read channel of a given port. Port\qs priority increases as the higher significant 5-bits of the counter starts to decrease. When the aging counter becomes 0, the corresponding port channel has the highest priority level (timeout condition - Priority0). For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority inputs (arqos) are enabled (timeout is still applicable). For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching. In this case, external dynamic priority input, arqos (for reads only) can still be used to set the DDRC read priority (2 priority levels: low priority read - LPR, high priority read - HPR) on a command by command basis. */
#define DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_0       (0x1U << DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_Pos)     /*!< 0x00000001 */
#define DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_1       (0x2U << DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_Pos)     /*!< 0x00000002 */
#define DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_2       (0x4U << DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_Pos)     /*!< 0x00000004 */
#define DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_3       (0x8U << DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_Pos)     /*!< 0x00000008 */
#define DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_4       (0x10U << DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_Pos)    /*!< 0x00000010 */
#define DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_5       (0x20U << DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_Pos)    /*!< 0x00000020 */
#define DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_6       (0x40U << DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_Pos)    /*!< 0x00000040 */
#define DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_7       (0x80U << DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_Pos)    /*!< 0x00000080 */
#define DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_8       (0x100U << DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_Pos)   /*!< 0x00000100 */
#define DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_9       (0x200U << DDRCTRL_PCFGR_0_RD_PORT_PRIORITY_Pos)   /*!< 0x00000200 */
#define DDRCTRL_PCFGR_0_RD_PORT_AGING_EN_Pos     (12U)
#define DDRCTRL_PCFGR_0_RD_PORT_AGING_EN_Msk     (0x1U << DDRCTRL_PCFGR_0_RD_PORT_AGING_EN_Pos)     /*!< 0x00001000 */
#define DDRCTRL_PCFGR_0_RD_PORT_AGING_EN         DDRCTRL_PCFGR_0_RD_PORT_AGING_EN_Msk               /*!< If set to 1, enables aging function for the read channel of the port. */
#define DDRCTRL_PCFGR_0_RD_PORT_URGENT_EN_Pos    (13U)
#define DDRCTRL_PCFGR_0_RD_PORT_URGENT_EN_Msk    (0x1U << DDRCTRL_PCFGR_0_RD_PORT_URGENT_EN_Pos)    /*!< 0x00002000 */
#define DDRCTRL_PCFGR_0_RD_PORT_URGENT_EN        DDRCTRL_PCFGR_0_RD_PORT_URGENT_EN_Msk              /*!< If set to 1, enables the AXI urgent sideband signal (arurgent). When enabled and arurgent is asserted by the master, that port becomes the highest priority and co_gs_go2critical_lpr/co_gs_go2critical_hpr signal to DDRC is asserted if enabled in PCCFG.go2critical_en register. Note that arurgent signal can be asserted anytime and as long as required which is independent of address handshaking (it is not associated with any particular command). */
#define DDRCTRL_PCFGR_0_RD_PORT_PAGEMATCH_EN_Pos (14U)
#define DDRCTRL_PCFGR_0_RD_PORT_PAGEMATCH_EN_Msk (0x1U << DDRCTRL_PCFGR_0_RD_PORT_PAGEMATCH_EN_Pos) /*!< 0x00004000 */
#define DDRCTRL_PCFGR_0_RD_PORT_PAGEMATCH_EN     DDRCTRL_PCFGR_0_RD_PORT_PAGEMATCH_EN_Msk           /*!< If set to 1, enables the Page Match feature. If enabled, once a requesting port is granted, the port is continued to be granted if the following immediate commands are to the same memory page (same bank and same row). See also related PCCFG.pagematch_limit register. */
#define DDRCTRL_PCFGR_0_RDWR_ORDERED_EN_Pos      (16U)
#define DDRCTRL_PCFGR_0_RDWR_ORDERED_EN_Msk      (0x1U << DDRCTRL_PCFGR_0_RDWR_ORDERED_EN_Pos)      /*!< 0x00010000 */
#define DDRCTRL_PCFGR_0_RDWR_ORDERED_EN          DDRCTRL_PCFGR_0_RDWR_ORDERED_EN_Msk                /*!< Enables ordered read/writes. If set to 1, preserves the ordering between read transaction and write transaction issued to the same address, on a given port. In other words, the controller ensures that all same address read and write commands from the application port interface are transported to the DFI interface in the order of acceptance. This feature is useful in cases where software coherency is desired for masters issuing back-to-back read/write transactions without waiting for write/read responses. Note that this register has an effect only if necessary logic is instantiated via the UMCTL2_RDWR_ORDERED_n parameter. */

/***************  Bit definition for DDRCTRL_PCFGW_0 register  ****************/
#define DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_Pos     (0U)
#define DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_Msk     (0x3FFU << DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_Pos)   /*!< 0x000003FF */
#define DDRCTRL_PCFGW_0_WR_PORT_PRIORITY         DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_Msk               /*!< Determines the initial load value of write aging counters. These counters are parallel loaded after reset, or after each grant to the corresponding port. The aging counters down-count every clock cycle where the port is requesting but not granted. The higher significant 5-bits of the write aging counter sets the initial priority of the write channel of a given port. Port\qs priority increases as the higher significant 5-bits of the counter starts to decrease. When the aging counter becomes 0, the corresponding port channel has the highest priority level. */
#define DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_0       (0x1U << DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_Pos)     /*!< 0x00000001 */
#define DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_1       (0x2U << DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_Pos)     /*!< 0x00000002 */
#define DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_2       (0x4U << DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_Pos)     /*!< 0x00000004 */
#define DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_3       (0x8U << DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_Pos)     /*!< 0x00000008 */
#define DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_4       (0x10U << DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_Pos)    /*!< 0x00000010 */
#define DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_5       (0x20U << DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_Pos)    /*!< 0x00000020 */
#define DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_6       (0x40U << DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_Pos)    /*!< 0x00000040 */
#define DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_7       (0x80U << DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_Pos)    /*!< 0x00000080 */
#define DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_8       (0x100U << DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_Pos)   /*!< 0x00000100 */
#define DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_9       (0x200U << DDRCTRL_PCFGW_0_WR_PORT_PRIORITY_Pos)   /*!< 0x00000200 */
#define DDRCTRL_PCFGW_0_WR_PORT_AGING_EN_Pos     (12U)
#define DDRCTRL_PCFGW_0_WR_PORT_AGING_EN_Msk     (0x1U << DDRCTRL_PCFGW_0_WR_PORT_AGING_EN_Pos)     /*!< 0x00001000 */
#define DDRCTRL_PCFGW_0_WR_PORT_AGING_EN         DDRCTRL_PCFGW_0_WR_PORT_AGING_EN_Msk               /*!< If set to 1, enables aging function for the write channel of the port. */
#define DDRCTRL_PCFGW_0_WR_PORT_URGENT_EN_Pos    (13U)
#define DDRCTRL_PCFGW_0_WR_PORT_URGENT_EN_Msk    (0x1U << DDRCTRL_PCFGW_0_WR_PORT_URGENT_EN_Pos)    /*!< 0x00002000 */
#define DDRCTRL_PCFGW_0_WR_PORT_URGENT_EN        DDRCTRL_PCFGW_0_WR_PORT_URGENT_EN_Msk              /*!< If set to 1, enables the AXI urgent sideband signal (awurgent). When enabled and awurgent is asserted by the master, that port becomes the highest priority and co_gs_go2critical_wr signal to DDRC is asserted if enabled in PCCFG.go2critical_en register. */
#define DDRCTRL_PCFGW_0_WR_PORT_PAGEMATCH_EN_Pos (14U)
#define DDRCTRL_PCFGW_0_WR_PORT_PAGEMATCH_EN_Msk (0x1U << DDRCTRL_PCFGW_0_WR_PORT_PAGEMATCH_EN_Pos) /*!< 0x00004000 */
#define DDRCTRL_PCFGW_0_WR_PORT_PAGEMATCH_EN     DDRCTRL_PCFGW_0_WR_PORT_PAGEMATCH_EN_Msk           /*!< If set to 1, enables the Page Match feature. If enabled, once a requesting port is granted, the port is continued to be granted if the following immediate commands are to the same memory page (same bank and same row). See also related PCCFG.pagematch_limit register. */

/***************  Bit definition for DDRCTRL_PCTRL_0 register  ****************/
#define DDRCTRL_PCTRL_0_PORT_EN_Pos (0U)
#define DDRCTRL_PCTRL_0_PORT_EN_Msk (0x1U << DDRCTRL_PCTRL_0_PORT_EN_Pos) /*!< 0x00000001 */
#define DDRCTRL_PCTRL_0_PORT_EN     DDRCTRL_PCTRL_0_PORT_EN_Msk           /*!< Enables AXI port n. */

/**************  Bit definition for DDRCTRL_PCFGQOS0_0 register  **************/
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL1_Pos  (0U)
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL1_Msk  (0xFU << DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL1_Pos)  /*!< 0x0000000F */
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL1      DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL1_Msk            /*!< Separation level1 indicating the end of region0 mapping; start of region0 is 0. Possible values for level1 are 0 to 13 (for dual RAQ) or 0 to 14 (for single RAQ) which corresponds to arqos. */
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL1_0    (0x1U << DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL1_Pos)  /*!< 0x00000001 */
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL1_1    (0x2U << DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL1_Pos)  /*!< 0x00000002 */
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL1_2    (0x4U << DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL1_Pos)  /*!< 0x00000004 */
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL1_3    (0x8U << DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL1_Pos)  /*!< 0x00000008 */
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL2_Pos  (8U)
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL2_Msk  (0xFU << DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL2_Pos)  /*!< 0x00000F00 */
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL2      DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL2_Msk            /*!< Separation level2 indicating the end of region1 mapping; start of region1 is (level1 + 1). Possible values for level2 are (level1 + 1) to 14 which corresponds to arqos. */
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL2_0    (0x1U << DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL2_Pos)  /*!< 0x00000100 */
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL2_1    (0x2U << DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL2_Pos)  /*!< 0x00000200 */
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL2_2    (0x4U << DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL2_Pos)  /*!< 0x00000400 */
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL2_3    (0x8U << DDRCTRL_PCFGQOS0_0_RQOS_MAP_LEVEL2_Pos)  /*!< 0x00000800 */
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION0_Pos (16U)
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION0_Msk (0x3U << DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION0_Pos) /*!< 0x00030000 */
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION0     DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION0_Msk           /*!< This bitfield indicates the traffic class of region 0. */
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION0_0   (0x1U << DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION0_Pos) /*!< 0x00010000 */
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION0_1   (0x2U << DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION0_Pos) /*!< 0x00020000 */
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION1_Pos (20U)
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION1_Msk (0x3U << DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION1_Pos) /*!< 0x00300000 */
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION1     DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION1_Msk           /*!< This bitfield indicates the traffic class of region 1. */
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION1_0   (0x1U << DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION1_Pos) /*!< 0x00100000 */
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION1_1   (0x2U << DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION1_Pos) /*!< 0x00200000 */
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION2_Pos (24U)
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION2_Msk (0x3U << DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION2_Pos) /*!< 0x03000000 */
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION2     DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION2_Msk           /*!< This bitfield indicates the traffic class of region2. */
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION2_0   (0x1U << DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION2_Pos) /*!< 0x01000000 */
#define DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION2_1   (0x2U << DDRCTRL_PCFGQOS0_0_RQOS_MAP_REGION2_Pos) /*!< 0x02000000 */

/**************  Bit definition for DDRCTRL_PCFGQOS1_0 register  **************/
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_Pos (0U)
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_Msk (0x7FFU << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_Pos) /*!< 0x000007FF */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB     DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_Msk             /*!< Specifies the timeout value for transactions mapped to the blue address queue. */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_0   (0x1U << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_Pos)   /*!< 0x00000001 */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_1   (0x2U << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_Pos)   /*!< 0x00000002 */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_2   (0x4U << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_Pos)   /*!< 0x00000004 */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_3   (0x8U << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_Pos)   /*!< 0x00000008 */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_4   (0x10U << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_Pos)  /*!< 0x00000010 */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_5   (0x20U << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_Pos)  /*!< 0x00000020 */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_6   (0x40U << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_Pos)  /*!< 0x00000040 */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_7   (0x80U << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_Pos)  /*!< 0x00000080 */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_8   (0x100U << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_Pos) /*!< 0x00000100 */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_9   (0x200U << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_Pos) /*!< 0x00000200 */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_10  (0x400U << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTB_Pos) /*!< 0x00000400 */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_Pos (16U)
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_Msk (0x7FFU << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_Pos) /*!< 0x07FF0000 */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR     DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_Msk             /*!< Specifies the timeout value for transactions mapped to the red address queue. */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_0   (0x1U << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_Pos)   /*!< 0x00010000 */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_1   (0x2U << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_Pos)   /*!< 0x00020000 */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_2   (0x4U << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_Pos)   /*!< 0x00040000 */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_3   (0x8U << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_Pos)   /*!< 0x00080000 */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_4   (0x10U << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_Pos)  /*!< 0x00100000 */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_5   (0x20U << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_Pos)  /*!< 0x00200000 */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_6   (0x40U << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_Pos)  /*!< 0x00400000 */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_7   (0x80U << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_Pos)  /*!< 0x00800000 */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_8   (0x100U << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_Pos) /*!< 0x01000000 */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_9   (0x200U << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_Pos) /*!< 0x02000000 */
#define DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_10  (0x400U << DDRCTRL_PCFGQOS1_0_RQOS_MAP_TIMEOUTR_Pos) /*!< 0x04000000 */

/*************  Bit definition for DDRCTRL_PCFGWQOS0_0 register  **************/
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL1_Pos  (0U)
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL1_Msk  (0xFU << DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL1_Pos)  /*!< 0x0000000F */
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL1      DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL1_Msk            /*!< Separation level indicating the end of region0 mapping; start of region0 is 0. Possible values for level1 are 0 to 13 which corresponds to awqos. */
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL1_0    (0x1U << DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL1_Pos)  /*!< 0x00000001 */
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL1_1    (0x2U << DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL1_Pos)  /*!< 0x00000002 */
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL1_2    (0x4U << DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL1_Pos)  /*!< 0x00000004 */
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL1_3    (0x8U << DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL1_Pos)  /*!< 0x00000008 */
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL2_Pos  (8U)
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL2_Msk  (0xFU << DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL2_Pos)  /*!< 0x00000F00 */
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL2      DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL2_Msk            /*!< Separation level2 indicating the end of region1 mapping; start of region1 is (level1 + 1). Possible values for level2 are (level1 + 1) to 14 which corresponds to awqos. */
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL2_0    (0x1U << DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL2_Pos)  /*!< 0x00000100 */
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL2_1    (0x2U << DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL2_Pos)  /*!< 0x00000200 */
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL2_2    (0x4U << DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL2_Pos)  /*!< 0x00000400 */
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL2_3    (0x8U << DDRCTRL_PCFGWQOS0_0_WQOS_MAP_LEVEL2_Pos)  /*!< 0x00000800 */
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION0_Pos (16U)
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION0_Msk (0x3U << DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION0_Pos) /*!< 0x00030000 */
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION0     DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION0_Msk           /*!< This bitfield indicates the traffic class of region 0. */
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION0_0   (0x1U << DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION0_Pos) /*!< 0x00010000 */
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION0_1   (0x2U << DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION0_Pos) /*!< 0x00020000 */
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION1_Pos (20U)
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION1_Msk (0x3U << DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION1_Pos) /*!< 0x00300000 */
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION1     DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION1_Msk           /*!< This bitfield indicates the traffic class of region 1. */
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION1_0   (0x1U << DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION1_Pos) /*!< 0x00100000 */
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION1_1   (0x2U << DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION1_Pos) /*!< 0x00200000 */
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION2_Pos (24U)
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION2_Msk (0x3U << DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION2_Pos) /*!< 0x03000000 */
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION2     DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION2_Msk           /*!< This bitfield indicates the traffic class of region 2. */
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION2_0   (0x1U << DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION2_Pos) /*!< 0x01000000 */
#define DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION2_1   (0x2U << DDRCTRL_PCFGWQOS0_0_WQOS_MAP_REGION2_Pos) /*!< 0x02000000 */

/*************  Bit definition for DDRCTRL_PCFGWQOS1_0 register  **************/
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_Pos (0U)
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_Msk (0x7FFU << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_Pos) /*!< 0x000007FF */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1     DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_Msk             /*!< Specifies the timeout value for write transactions in region 0 and 1. */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_0   (0x1U << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_Pos)   /*!< 0x00000001 */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_1   (0x2U << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_Pos)   /*!< 0x00000002 */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_2   (0x4U << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_Pos)   /*!< 0x00000004 */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_3   (0x8U << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_Pos)   /*!< 0x00000008 */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_4   (0x10U << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_Pos)  /*!< 0x00000010 */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_5   (0x20U << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_Pos)  /*!< 0x00000020 */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_6   (0x40U << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_Pos)  /*!< 0x00000040 */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_7   (0x80U << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_Pos)  /*!< 0x00000080 */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_8   (0x100U << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_Pos) /*!< 0x00000100 */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_9   (0x200U << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_Pos) /*!< 0x00000200 */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_10  (0x400U << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1_Pos) /*!< 0x00000400 */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_Pos (16U)
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_Msk (0x7FFU << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_Pos) /*!< 0x07FF0000 */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2     DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_Msk             /*!< Specifies the timeout value for write transactions in region 2. */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_0   (0x1U << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_Pos)   /*!< 0x00010000 */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_1   (0x2U << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_Pos)   /*!< 0x00020000 */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_2   (0x4U << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_Pos)   /*!< 0x00040000 */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_3   (0x8U << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_Pos)   /*!< 0x00080000 */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_4   (0x10U << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_Pos)  /*!< 0x00100000 */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_5   (0x20U << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_Pos)  /*!< 0x00200000 */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_6   (0x40U << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_Pos)  /*!< 0x00400000 */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_7   (0x80U << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_Pos)  /*!< 0x00800000 */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_8   (0x100U << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_Pos) /*!< 0x01000000 */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_9   (0x200U << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_Pos) /*!< 0x02000000 */
#define DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_10  (0x400U << DDRCTRL_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2_Pos) /*!< 0x04000000 */

/***************  Bit definition for DDRCTRL_PCFGR_1 register  ****************/
#define DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_Pos     (0U)
#define DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_Msk     (0x3FFU << DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_Pos)   /*!< 0x000003FF */
#define DDRCTRL_PCFGR_1_RD_PORT_PRIORITY         DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_Msk               /*!< Determines the initial load value of read aging counters. These counters are parallel loaded after reset, or after each grant to the corresponding port. The aging counters down-count every clock cycle where the port is requesting but not granted. The higher significant 5-bits of the read aging counter sets the priority of the read channel of a given port. Port\qs priority increases as the higher significant 5-bits of the counter starts to decrease. When the aging counter becomes 0, the corresponding port channel has the highest priority level (timeout condition - Priority0). For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority inputs (arqos) are enabled (timeout is still applicable). For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching. In this case, external dynamic priority input, arqos (for reads only) can still be used to set the DDRC read priority (2 priority levels: low priority read - LPR, high priority read - HPR) on a command by command basis. */
#define DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_0       (0x1U << DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_Pos)     /*!< 0x00000001 */
#define DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_1       (0x2U << DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_Pos)     /*!< 0x00000002 */
#define DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_2       (0x4U << DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_Pos)     /*!< 0x00000004 */
#define DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_3       (0x8U << DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_Pos)     /*!< 0x00000008 */
#define DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_4       (0x10U << DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_Pos)    /*!< 0x00000010 */
#define DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_5       (0x20U << DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_Pos)    /*!< 0x00000020 */
#define DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_6       (0x40U << DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_Pos)    /*!< 0x00000040 */
#define DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_7       (0x80U << DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_Pos)    /*!< 0x00000080 */
#define DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_8       (0x100U << DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_Pos)   /*!< 0x00000100 */
#define DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_9       (0x200U << DDRCTRL_PCFGR_1_RD_PORT_PRIORITY_Pos)   /*!< 0x00000200 */
#define DDRCTRL_PCFGR_1_RD_PORT_AGING_EN_Pos     (12U)
#define DDRCTRL_PCFGR_1_RD_PORT_AGING_EN_Msk     (0x1U << DDRCTRL_PCFGR_1_RD_PORT_AGING_EN_Pos)     /*!< 0x00001000 */
#define DDRCTRL_PCFGR_1_RD_PORT_AGING_EN         DDRCTRL_PCFGR_1_RD_PORT_AGING_EN_Msk               /*!< If set to 1, enables aging function for the read channel of the port. */
#define DDRCTRL_PCFGR_1_RD_PORT_URGENT_EN_Pos    (13U)
#define DDRCTRL_PCFGR_1_RD_PORT_URGENT_EN_Msk    (0x1U << DDRCTRL_PCFGR_1_RD_PORT_URGENT_EN_Pos)    /*!< 0x00002000 */
#define DDRCTRL_PCFGR_1_RD_PORT_URGENT_EN        DDRCTRL_PCFGR_1_RD_PORT_URGENT_EN_Msk              /*!< If set to 1, enables the AXI urgent sideband signal (arurgent). When enabled and arurgent is asserted by the master, that port becomes the highest priority and co_gs_go2critical_lpr/co_gs_go2critical_hpr signal to DDRC is asserted if enabled in PCCFG.go2critical_en register. Note that arurgent signal can be asserted anytime and as long as required which is independent of address handshaking (it is not associated with any particular command). */
#define DDRCTRL_PCFGR_1_RD_PORT_PAGEMATCH_EN_Pos (14U)
#define DDRCTRL_PCFGR_1_RD_PORT_PAGEMATCH_EN_Msk (0x1U << DDRCTRL_PCFGR_1_RD_PORT_PAGEMATCH_EN_Pos) /*!< 0x00004000 */
#define DDRCTRL_PCFGR_1_RD_PORT_PAGEMATCH_EN     DDRCTRL_PCFGR_1_RD_PORT_PAGEMATCH_EN_Msk           /*!< If set to 1, enables the Page Match feature. If enabled, once a requesting port is granted, the port is continued to be granted if the following immediate commands are to the same memory page (same bank and same row). See also related PCCFG.pagematch_limit register. */
#define DDRCTRL_PCFGR_1_RDWR_ORDERED_EN_Pos      (16U)
#define DDRCTRL_PCFGR_1_RDWR_ORDERED_EN_Msk      (0x1U << DDRCTRL_PCFGR_1_RDWR_ORDERED_EN_Pos)      /*!< 0x00010000 */
#define DDRCTRL_PCFGR_1_RDWR_ORDERED_EN          DDRCTRL_PCFGR_1_RDWR_ORDERED_EN_Msk                /*!< Enables ordered read/writes. If set to 1, preserves the ordering between read transaction and write transaction issued to the same address, on a given port. In other words, the controller ensures that all same address read and write commands from the application port interface are transported to the DFI interface in the order of acceptance. This feature is useful in cases where software coherency is desired for masters issuing back-to-back read/write transactions without waiting for write/read responses. Note that this register has an effect only if necessary logic is instantiated via the UMCTL2_RDWR_ORDERED_n parameter. */

/***************  Bit definition for DDRCTRL_PCFGW_1 register  ****************/
#define DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_Pos     (0U)
#define DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_Msk     (0x3FFU << DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_Pos)   /*!< 0x000003FF */
#define DDRCTRL_PCFGW_1_WR_PORT_PRIORITY         DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_Msk               /*!< Determines the initial load value of write aging counters. These counters are parallel loaded after reset, or after each grant to the corresponding port. The aging counters down-count every clock cycle where the port is requesting but not granted. The higher significant 5-bits of the write aging counter sets the initial priority of the write channel of a given port. Port\qs priority increases as the higher significant 5-bits of the counter starts to decrease. When the aging counter becomes 0, the corresponding port channel has the highest priority level. */
#define DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_0       (0x1U << DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_Pos)     /*!< 0x00000001 */
#define DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_1       (0x2U << DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_Pos)     /*!< 0x00000002 */
#define DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_2       (0x4U << DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_Pos)     /*!< 0x00000004 */
#define DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_3       (0x8U << DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_Pos)     /*!< 0x00000008 */
#define DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_4       (0x10U << DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_Pos)    /*!< 0x00000010 */
#define DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_5       (0x20U << DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_Pos)    /*!< 0x00000020 */
#define DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_6       (0x40U << DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_Pos)    /*!< 0x00000040 */
#define DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_7       (0x80U << DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_Pos)    /*!< 0x00000080 */
#define DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_8       (0x100U << DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_Pos)   /*!< 0x00000100 */
#define DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_9       (0x200U << DDRCTRL_PCFGW_1_WR_PORT_PRIORITY_Pos)   /*!< 0x00000200 */
#define DDRCTRL_PCFGW_1_WR_PORT_AGING_EN_Pos     (12U)
#define DDRCTRL_PCFGW_1_WR_PORT_AGING_EN_Msk     (0x1U << DDRCTRL_PCFGW_1_WR_PORT_AGING_EN_Pos)     /*!< 0x00001000 */
#define DDRCTRL_PCFGW_1_WR_PORT_AGING_EN         DDRCTRL_PCFGW_1_WR_PORT_AGING_EN_Msk               /*!< If set to 1, enables aging function for the write channel of the port. */
#define DDRCTRL_PCFGW_1_WR_PORT_URGENT_EN_Pos    (13U)
#define DDRCTRL_PCFGW_1_WR_PORT_URGENT_EN_Msk    (0x1U << DDRCTRL_PCFGW_1_WR_PORT_URGENT_EN_Pos)    /*!< 0x00002000 */
#define DDRCTRL_PCFGW_1_WR_PORT_URGENT_EN        DDRCTRL_PCFGW_1_WR_PORT_URGENT_EN_Msk              /*!< If set to 1, enables the AXI urgent sideband signal (awurgent). When enabled and awurgent is asserted by the master, that port becomes the highest priority and co_gs_go2critical_wr signal to DDRC is asserted if enabled in PCCFG.go2critical_en register. */
#define DDRCTRL_PCFGW_1_WR_PORT_PAGEMATCH_EN_Pos (14U)
#define DDRCTRL_PCFGW_1_WR_PORT_PAGEMATCH_EN_Msk (0x1U << DDRCTRL_PCFGW_1_WR_PORT_PAGEMATCH_EN_Pos) /*!< 0x00004000 */
#define DDRCTRL_PCFGW_1_WR_PORT_PAGEMATCH_EN     DDRCTRL_PCFGW_1_WR_PORT_PAGEMATCH_EN_Msk           /*!< If set to 1, enables the Page Match feature. If enabled, once a requesting port is granted, the port is continued to be granted if the following immediate commands are to the same memory page (same bank and same row). See also related PCCFG.pagematch_limit register. */

/***************  Bit definition for DDRCTRL_PCTRL_1 register  ****************/
#define DDRCTRL_PCTRL_1_PORT_EN_Pos (0U)
#define DDRCTRL_PCTRL_1_PORT_EN_Msk (0x1U << DDRCTRL_PCTRL_1_PORT_EN_Pos) /*!< 0x00000001 */
#define DDRCTRL_PCTRL_1_PORT_EN     DDRCTRL_PCTRL_1_PORT_EN_Msk           /*!< Enables AXI port n. */

/**************  Bit definition for DDRCTRL_PCFGQOS0_1 register  **************/
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL1_Pos  (0U)
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL1_Msk  (0xFU << DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL1_Pos)  /*!< 0x0000000F */
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL1      DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL1_Msk            /*!< Separation level1 indicating the end of region0 mapping; start of region0 is 0. Possible values for level1 are 0 to 13 (for dual RAQ) or 0 to 14 (for single RAQ) which corresponds to arqos. */
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL1_0    (0x1U << DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL1_Pos)  /*!< 0x00000001 */
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL1_1    (0x2U << DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL1_Pos)  /*!< 0x00000002 */
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL1_2    (0x4U << DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL1_Pos)  /*!< 0x00000004 */
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL1_3    (0x8U << DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL1_Pos)  /*!< 0x00000008 */
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL2_Pos  (8U)
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL2_Msk  (0xFU << DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL2_Pos)  /*!< 0x00000F00 */
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL2      DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL2_Msk            /*!< Separation level2 indicating the end of region1 mapping; start of region1 is (level1 + 1). Possible values for level2 are (level1 + 1) to 14 which corresponds to arqos. */
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL2_0    (0x1U << DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL2_Pos)  /*!< 0x00000100 */
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL2_1    (0x2U << DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL2_Pos)  /*!< 0x00000200 */
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL2_2    (0x4U << DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL2_Pos)  /*!< 0x00000400 */
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL2_3    (0x8U << DDRCTRL_PCFGQOS0_1_RQOS_MAP_LEVEL2_Pos)  /*!< 0x00000800 */
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION0_Pos (16U)
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION0_Msk (0x3U << DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION0_Pos) /*!< 0x00030000 */
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION0     DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION0_Msk           /*!< This bitfield indicates the traffic class of region 0. */
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION0_0   (0x1U << DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION0_Pos) /*!< 0x00010000 */
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION0_1   (0x2U << DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION0_Pos) /*!< 0x00020000 */
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION1_Pos (20U)
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION1_Msk (0x3U << DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION1_Pos) /*!< 0x00300000 */
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION1     DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION1_Msk           /*!< This bitfield indicates the traffic class of region 1. */
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION1_0   (0x1U << DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION1_Pos) /*!< 0x00100000 */
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION1_1   (0x2U << DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION1_Pos) /*!< 0x00200000 */
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION2_Pos (24U)
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION2_Msk (0x3U << DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION2_Pos) /*!< 0x03000000 */
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION2     DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION2_Msk           /*!< This bitfield indicates the traffic class of region2. */
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION2_0   (0x1U << DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION2_Pos) /*!< 0x01000000 */
#define DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION2_1   (0x2U << DDRCTRL_PCFGQOS0_1_RQOS_MAP_REGION2_Pos) /*!< 0x02000000 */

/**************  Bit definition for DDRCTRL_PCFGQOS1_1 register  **************/
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_Pos (0U)
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_Msk (0x7FFU << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_Pos) /*!< 0x000007FF */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB     DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_Msk             /*!< Specifies the timeout value for transactions mapped to the blue address queue. */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_0   (0x1U << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_Pos)   /*!< 0x00000001 */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_1   (0x2U << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_Pos)   /*!< 0x00000002 */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_2   (0x4U << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_Pos)   /*!< 0x00000004 */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_3   (0x8U << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_Pos)   /*!< 0x00000008 */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_4   (0x10U << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_Pos)  /*!< 0x00000010 */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_5   (0x20U << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_Pos)  /*!< 0x00000020 */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_6   (0x40U << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_Pos)  /*!< 0x00000040 */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_7   (0x80U << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_Pos)  /*!< 0x00000080 */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_8   (0x100U << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_Pos) /*!< 0x00000100 */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_9   (0x200U << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_Pos) /*!< 0x00000200 */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_10  (0x400U << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTB_Pos) /*!< 0x00000400 */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_Pos (16U)
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_Msk (0x7FFU << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_Pos) /*!< 0x07FF0000 */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR     DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_Msk             /*!< Specifies the timeout value for transactions mapped to the red address queue. */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_0   (0x1U << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_Pos)   /*!< 0x00010000 */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_1   (0x2U << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_Pos)   /*!< 0x00020000 */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_2   (0x4U << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_Pos)   /*!< 0x00040000 */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_3   (0x8U << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_Pos)   /*!< 0x00080000 */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_4   (0x10U << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_Pos)  /*!< 0x00100000 */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_5   (0x20U << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_Pos)  /*!< 0x00200000 */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_6   (0x40U << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_Pos)  /*!< 0x00400000 */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_7   (0x80U << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_Pos)  /*!< 0x00800000 */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_8   (0x100U << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_Pos) /*!< 0x01000000 */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_9   (0x200U << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_Pos) /*!< 0x02000000 */
#define DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_10  (0x400U << DDRCTRL_PCFGQOS1_1_RQOS_MAP_TIMEOUTR_Pos) /*!< 0x04000000 */

/*************  Bit definition for DDRCTRL_PCFGWQOS0_1 register  **************/
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL1_Pos  (0U)
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL1_Msk  (0xFU << DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL1_Pos)  /*!< 0x0000000F */
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL1      DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL1_Msk            /*!< Separation level indicating the end of region0 mapping; start of region0 is 0. Possible values for level1 are 0 to 13 which corresponds to awqos. */
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL1_0    (0x1U << DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL1_Pos)  /*!< 0x00000001 */
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL1_1    (0x2U << DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL1_Pos)  /*!< 0x00000002 */
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL1_2    (0x4U << DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL1_Pos)  /*!< 0x00000004 */
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL1_3    (0x8U << DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL1_Pos)  /*!< 0x00000008 */
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL2_Pos  (8U)
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL2_Msk  (0xFU << DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL2_Pos)  /*!< 0x00000F00 */
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL2      DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL2_Msk            /*!< Separation level2 indicating the end of region1 mapping; start of region1 is (level1 + 1). Possible values for level2 are (level1 + 1) to 14 which corresponds to awqos. */
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL2_0    (0x1U << DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL2_Pos)  /*!< 0x00000100 */
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL2_1    (0x2U << DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL2_Pos)  /*!< 0x00000200 */
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL2_2    (0x4U << DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL2_Pos)  /*!< 0x00000400 */
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL2_3    (0x8U << DDRCTRL_PCFGWQOS0_1_WQOS_MAP_LEVEL2_Pos)  /*!< 0x00000800 */
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION0_Pos (16U)
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION0_Msk (0x3U << DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION0_Pos) /*!< 0x00030000 */
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION0     DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION0_Msk           /*!< This bitfield indicates the traffic class of region 0. */
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION0_0   (0x1U << DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION0_Pos) /*!< 0x00010000 */
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION0_1   (0x2U << DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION0_Pos) /*!< 0x00020000 */
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION1_Pos (20U)
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION1_Msk (0x3U << DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION1_Pos) /*!< 0x00300000 */
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION1     DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION1_Msk           /*!< This bitfield indicates the traffic class of region 1. */
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION1_0   (0x1U << DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION1_Pos) /*!< 0x00100000 */
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION1_1   (0x2U << DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION1_Pos) /*!< 0x00200000 */
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION2_Pos (24U)
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION2_Msk (0x3U << DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION2_Pos) /*!< 0x03000000 */
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION2     DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION2_Msk           /*!< This bitfield indicates the traffic class of region 2. */
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION2_0   (0x1U << DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION2_Pos) /*!< 0x01000000 */
#define DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION2_1   (0x2U << DDRCTRL_PCFGWQOS0_1_WQOS_MAP_REGION2_Pos) /*!< 0x02000000 */

/*************  Bit definition for DDRCTRL_PCFGWQOS1_1 register  **************/
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_Pos (0U)
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_Msk (0x7FFU << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_Pos) /*!< 0x000007FF */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1     DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_Msk             /*!< Specifies the timeout value for write transactions in region 0 and 1. */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_0   (0x1U << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_Pos)   /*!< 0x00000001 */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_1   (0x2U << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_Pos)   /*!< 0x00000002 */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_2   (0x4U << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_Pos)   /*!< 0x00000004 */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_3   (0x8U << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_Pos)   /*!< 0x00000008 */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_4   (0x10U << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_Pos)  /*!< 0x00000010 */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_5   (0x20U << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_Pos)  /*!< 0x00000020 */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_6   (0x40U << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_Pos)  /*!< 0x00000040 */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_7   (0x80U << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_Pos)  /*!< 0x00000080 */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_8   (0x100U << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_Pos) /*!< 0x00000100 */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_9   (0x200U << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_Pos) /*!< 0x00000200 */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_10  (0x400U << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1_Pos) /*!< 0x00000400 */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_Pos (16U)
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_Msk (0x7FFU << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_Pos) /*!< 0x07FF0000 */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2     DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_Msk             /*!< Specifies the timeout value for write transactions in region 2. */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_0   (0x1U << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_Pos)   /*!< 0x00010000 */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_1   (0x2U << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_Pos)   /*!< 0x00020000 */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_2   (0x4U << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_Pos)   /*!< 0x00040000 */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_3   (0x8U << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_Pos)   /*!< 0x00080000 */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_4   (0x10U << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_Pos)  /*!< 0x00100000 */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_5   (0x20U << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_Pos)  /*!< 0x00200000 */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_6   (0x40U << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_Pos)  /*!< 0x00400000 */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_7   (0x80U << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_Pos)  /*!< 0x00800000 */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_8   (0x100U << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_Pos) /*!< 0x01000000 */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_9   (0x200U << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_Pos) /*!< 0x02000000 */
#define DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_10  (0x400U << DDRCTRL_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2_Pos) /*!< 0x04000000 */

/******************************************************************************/
/*                                                                            */
/*                   DDRPERFM block description (DDRPERFM)                    */
/*                                                                            */
/******************************************************************************/
/*****************  Bit definition for DDRPERFM_CTL register  *****************/
#define DDRPERFM_CTL_START_Pos (0U)
#define DDRPERFM_CTL_START_Msk (0x1U << DDRPERFM_CTL_START_Pos) /*!< 0x00000001 */
#define DDRPERFM_CTL_START     DDRPERFM_CTL_START_Msk           /*!< Start counters which are enabled, the time counter (TCNT) is always enabled. */
#define DDRPERFM_CTL_STOP_Pos  (1U)
#define DDRPERFM_CTL_STOP_Msk  (0x1U << DDRPERFM_CTL_STOP_Pos)  /*!< 0x00000002 */
#define DDRPERFM_CTL_STOP      DDRPERFM_CTL_STOP_Msk            /*!< stop all the counters. */

/*****************  Bit definition for DDRPERFM_CFG register  *****************/
#define DDRPERFM_CFG_EN_Pos  (0U)
#define DDRPERFM_CFG_EN_Msk  (0xFU << DDRPERFM_CFG_EN_Pos)  /*!< 0x0000000F */
#define DDRPERFM_CFG_EN      DDRPERFM_CFG_EN_Msk            /*!< enable counter x (from 0 to 3) */
#define DDRPERFM_CFG_EN_0    (0x1U << DDRPERFM_CFG_EN_Pos)  /*!< 0x00000001 */
#define DDRPERFM_CFG_EN_1    (0x2U << DDRPERFM_CFG_EN_Pos)  /*!< 0x00000002 */
#define DDRPERFM_CFG_EN_2    (0x4U << DDRPERFM_CFG_EN_Pos)  /*!< 0x00000004 */
#define DDRPERFM_CFG_EN_3    (0x8U << DDRPERFM_CFG_EN_Pos)  /*!< 0x00000008 */
#define DDRPERFM_CFG_SEL_Pos (16U)
#define DDRPERFM_CFG_SEL_Msk (0x3U << DDRPERFM_CFG_SEL_Pos) /*!< 0x00030000 */
#define DDRPERFM_CFG_SEL     DDRPERFM_CFG_SEL_Msk           /*!< select set of signals to be monitored (from 0 to 3) (see signal set description in Table 34: DDRPERFM signal sets) and counters to be enabled */
#define DDRPERFM_CFG_SEL_0   (0x1U << DDRPERFM_CFG_SEL_Pos) /*!< 0x00010000 */
#define DDRPERFM_CFG_SEL_1   (0x2U << DDRPERFM_CFG_SEL_Pos) /*!< 0x00020000 */

/***************  Bit definition for DDRPERFM_STATUS register  ****************/
#define DDRPERFM_STATUS_COVF_Pos (0U)
#define DDRPERFM_STATUS_COVF_Msk (0xFU << DDRPERFM_STATUS_COVF_Pos) /*!< 0x0000000F */
#define DDRPERFM_STATUS_COVF     DDRPERFM_STATUS_COVF_Msk           /*!< Counter x Overflow (with x from 0 to 3) */
#define DDRPERFM_STATUS_COVF_0   (0x1U << DDRPERFM_STATUS_COVF_Pos) /*!< 0x00000001 */
#define DDRPERFM_STATUS_COVF_1   (0x2U << DDRPERFM_STATUS_COVF_Pos) /*!< 0x00000002 */
#define DDRPERFM_STATUS_COVF_2   (0x4U << DDRPERFM_STATUS_COVF_Pos) /*!< 0x00000004 */
#define DDRPERFM_STATUS_COVF_3   (0x8U << DDRPERFM_STATUS_COVF_Pos) /*!< 0x00000008 */
#define DDRPERFM_STATUS_BUSY_Pos (16U)
#define DDRPERFM_STATUS_BUSY_Msk (0x1U << DDRPERFM_STATUS_BUSY_Pos) /*!< 0x00010000 */
#define DDRPERFM_STATUS_BUSY     DDRPERFM_STATUS_BUSY_Msk           /*!< Busy Status */
#define DDRPERFM_STATUS_TOVF_Pos (31U)
#define DDRPERFM_STATUS_TOVF_Msk (0x1U << DDRPERFM_STATUS_TOVF_Pos) /*!< 0x80000000 */
#define DDRPERFM_STATUS_TOVF     DDRPERFM_STATUS_TOVF_Msk           /*!< total counter overflow */

/*****************  Bit definition for DDRPERFM_CCR register  *****************/
#define DDRPERFM_CCR_CCLR_Pos (0U)
#define DDRPERFM_CCR_CCLR_Msk (0xFU << DDRPERFM_CCR_CCLR_Pos) /*!< 0x0000000F */
#define DDRPERFM_CCR_CCLR     DDRPERFM_CCR_CCLR_Msk           /*!< counter x Clear (with x from 0 to 3) */
#define DDRPERFM_CCR_CCLR_0   (0x1U << DDRPERFM_CCR_CCLR_Pos) /*!< 0x00000001 */
#define DDRPERFM_CCR_CCLR_1   (0x2U << DDRPERFM_CCR_CCLR_Pos) /*!< 0x00000002 */
#define DDRPERFM_CCR_CCLR_2   (0x4U << DDRPERFM_CCR_CCLR_Pos) /*!< 0x00000004 */
#define DDRPERFM_CCR_CCLR_3   (0x8U << DDRPERFM_CCR_CCLR_Pos) /*!< 0x00000008 */
#define DDRPERFM_CCR_TCLR_Pos (31U)
#define DDRPERFM_CCR_TCLR_Msk (0x1U << DDRPERFM_CCR_TCLR_Pos) /*!< 0x80000000 */
#define DDRPERFM_CCR_TCLR     DDRPERFM_CCR_TCLR_Msk           /*!< time counter clear */

/*****************  Bit definition for DDRPERFM_IER register  *****************/
#define DDRPERFM_IER_OVFIE_Pos (0U)
#define DDRPERFM_IER_OVFIE_Msk (0x1U << DDRPERFM_IER_OVFIE_Pos) /*!< 0x00000001 */
#define DDRPERFM_IER_OVFIE     DDRPERFM_IER_OVFIE_Msk           /*!< overflow interrupt enable */

/*****************  Bit definition for DDRPERFM_ISR register  *****************/
#define DDRPERFM_ISR_OVFF_Pos (0U)
#define DDRPERFM_ISR_OVFF_Msk (0x1U << DDRPERFM_ISR_OVFF_Pos) /*!< 0x00000001 */
#define DDRPERFM_ISR_OVFF     DDRPERFM_ISR_OVFF_Msk           /*!< overflow flag */

/*****************  Bit definition for DDRPERFM_ICR register  *****************/
#define DDRPERFM_ICR_OVF_Pos (0U)
#define DDRPERFM_ICR_OVF_Msk (0x1U << DDRPERFM_ICR_OVF_Pos) /*!< 0x00000001 */
#define DDRPERFM_ICR_OVF     DDRPERFM_ICR_OVF_Msk           /*!< overflow flag */

/****************  Bit definition for DDRPERFM_TCNT register  *****************/
#define DDRPERFM_TCNT_CNT_Pos (0U)
#define DDRPERFM_TCNT_CNT_Msk (0xFFFFFFFFU << DDRPERFM_TCNT_CNT_Pos) /*!< 0xFFFFFFFF */
#define DDRPERFM_TCNT_CNT     DDRPERFM_TCNT_CNT_Msk                  /*!< total time, this is number of DDR controller clocks elapsed while DDRPERFM has been running. */
#define DDRPERFM_TCNT_CNT_0   (0x1U << DDRPERFM_TCNT_CNT_Pos)        /*!< 0x00000001 */
#define DDRPERFM_TCNT_CNT_1   (0x2U << DDRPERFM_TCNT_CNT_Pos)        /*!< 0x00000002 */
#define DDRPERFM_TCNT_CNT_2   (0x4U << DDRPERFM_TCNT_CNT_Pos)        /*!< 0x00000004 */
#define DDRPERFM_TCNT_CNT_3   (0x8U << DDRPERFM_TCNT_CNT_Pos)        /*!< 0x00000008 */
#define DDRPERFM_TCNT_CNT_4   (0x10U << DDRPERFM_TCNT_CNT_Pos)       /*!< 0x00000010 */
#define DDRPERFM_TCNT_CNT_5   (0x20U << DDRPERFM_TCNT_CNT_Pos)       /*!< 0x00000020 */
#define DDRPERFM_TCNT_CNT_6   (0x40U << DDRPERFM_TCNT_CNT_Pos)       /*!< 0x00000040 */
#define DDRPERFM_TCNT_CNT_7   (0x80U << DDRPERFM_TCNT_CNT_Pos)       /*!< 0x00000080 */
#define DDRPERFM_TCNT_CNT_8   (0x100U << DDRPERFM_TCNT_CNT_Pos)      /*!< 0x00000100 */
#define DDRPERFM_TCNT_CNT_9   (0x200U << DDRPERFM_TCNT_CNT_Pos)      /*!< 0x00000200 */
#define DDRPERFM_TCNT_CNT_10  (0x400U << DDRPERFM_TCNT_CNT_Pos)      /*!< 0x00000400 */
#define DDRPERFM_TCNT_CNT_11  (0x800U << DDRPERFM_TCNT_CNT_Pos)      /*!< 0x00000800 */
#define DDRPERFM_TCNT_CNT_12  (0x1000U << DDRPERFM_TCNT_CNT_Pos)     /*!< 0x00001000 */
#define DDRPERFM_TCNT_CNT_13  (0x2000U << DDRPERFM_TCNT_CNT_Pos)     /*!< 0x00002000 */
#define DDRPERFM_TCNT_CNT_14  (0x4000U << DDRPERFM_TCNT_CNT_Pos)     /*!< 0x00004000 */
#define DDRPERFM_TCNT_CNT_15  (0x8000U << DDRPERFM_TCNT_CNT_Pos)     /*!< 0x00008000 */
#define DDRPERFM_TCNT_CNT_16  (0x10000U << DDRPERFM_TCNT_CNT_Pos)    /*!< 0x00010000 */
#define DDRPERFM_TCNT_CNT_17  (0x20000U << DDRPERFM_TCNT_CNT_Pos)    /*!< 0x00020000 */
#define DDRPERFM_TCNT_CNT_18  (0x40000U << DDRPERFM_TCNT_CNT_Pos)    /*!< 0x00040000 */
#define DDRPERFM_TCNT_CNT_19  (0x80000U << DDRPERFM_TCNT_CNT_Pos)    /*!< 0x00080000 */
#define DDRPERFM_TCNT_CNT_20  (0x100000U << DDRPERFM_TCNT_CNT_Pos)   /*!< 0x00100000 */
#define DDRPERFM_TCNT_CNT_21  (0x200000U << DDRPERFM_TCNT_CNT_Pos)   /*!< 0x00200000 */
#define DDRPERFM_TCNT_CNT_22  (0x400000U << DDRPERFM_TCNT_CNT_Pos)   /*!< 0x00400000 */
#define DDRPERFM_TCNT_CNT_23  (0x800000U << DDRPERFM_TCNT_CNT_Pos)   /*!< 0x00800000 */
#define DDRPERFM_TCNT_CNT_24  (0x1000000U << DDRPERFM_TCNT_CNT_Pos)  /*!< 0x01000000 */
#define DDRPERFM_TCNT_CNT_25  (0x2000000U << DDRPERFM_TCNT_CNT_Pos)  /*!< 0x02000000 */
#define DDRPERFM_TCNT_CNT_26  (0x4000000U << DDRPERFM_TCNT_CNT_Pos)  /*!< 0x04000000 */
#define DDRPERFM_TCNT_CNT_27  (0x8000000U << DDRPERFM_TCNT_CNT_Pos)  /*!< 0x08000000 */
#define DDRPERFM_TCNT_CNT_28  (0x10000000U << DDRPERFM_TCNT_CNT_Pos) /*!< 0x10000000 */
#define DDRPERFM_TCNT_CNT_29  (0x20000000U << DDRPERFM_TCNT_CNT_Pos) /*!< 0x20000000 */
#define DDRPERFM_TCNT_CNT_30  (0x40000000U << DDRPERFM_TCNT_CNT_Pos) /*!< 0x40000000 */
#define DDRPERFM_TCNT_CNT_31  (0x80000000U << DDRPERFM_TCNT_CNT_Pos) /*!< 0x80000000 */

/****************  Bit definition for DDRPERFM_CNT0 register  *****************/
#define DDRPERFM_CNT0_CNT_Pos (0U)
#define DDRPERFM_CNT0_CNT_Msk (0xFFFFFFFFU << DDRPERFM_CNT0_CNT_Pos) /*!< 0xFFFFFFFF */
#define DDRPERFM_CNT0_CNT     DDRPERFM_CNT0_CNT_Msk                  /*!< event counter value. */
#define DDRPERFM_CNT0_CNT_0   (0x1U << DDRPERFM_CNT0_CNT_Pos)        /*!< 0x00000001 */
#define DDRPERFM_CNT0_CNT_1   (0x2U << DDRPERFM_CNT0_CNT_Pos)        /*!< 0x00000002 */
#define DDRPERFM_CNT0_CNT_2   (0x4U << DDRPERFM_CNT0_CNT_Pos)        /*!< 0x00000004 */
#define DDRPERFM_CNT0_CNT_3   (0x8U << DDRPERFM_CNT0_CNT_Pos)        /*!< 0x00000008 */
#define DDRPERFM_CNT0_CNT_4   (0x10U << DDRPERFM_CNT0_CNT_Pos)       /*!< 0x00000010 */
#define DDRPERFM_CNT0_CNT_5   (0x20U << DDRPERFM_CNT0_CNT_Pos)       /*!< 0x00000020 */
#define DDRPERFM_CNT0_CNT_6   (0x40U << DDRPERFM_CNT0_CNT_Pos)       /*!< 0x00000040 */
#define DDRPERFM_CNT0_CNT_7   (0x80U << DDRPERFM_CNT0_CNT_Pos)       /*!< 0x00000080 */
#define DDRPERFM_CNT0_CNT_8   (0x100U << DDRPERFM_CNT0_CNT_Pos)      /*!< 0x00000100 */
#define DDRPERFM_CNT0_CNT_9   (0x200U << DDRPERFM_CNT0_CNT_Pos)      /*!< 0x00000200 */
#define DDRPERFM_CNT0_CNT_10  (0x400U << DDRPERFM_CNT0_CNT_Pos)      /*!< 0x00000400 */
#define DDRPERFM_CNT0_CNT_11  (0x800U << DDRPERFM_CNT0_CNT_Pos)      /*!< 0x00000800 */
#define DDRPERFM_CNT0_CNT_12  (0x1000U << DDRPERFM_CNT0_CNT_Pos)     /*!< 0x00001000 */
#define DDRPERFM_CNT0_CNT_13  (0x2000U << DDRPERFM_CNT0_CNT_Pos)     /*!< 0x00002000 */
#define DDRPERFM_CNT0_CNT_14  (0x4000U << DDRPERFM_CNT0_CNT_Pos)     /*!< 0x00004000 */
#define DDRPERFM_CNT0_CNT_15  (0x8000U << DDRPERFM_CNT0_CNT_Pos)     /*!< 0x00008000 */
#define DDRPERFM_CNT0_CNT_16  (0x10000U << DDRPERFM_CNT0_CNT_Pos)    /*!< 0x00010000 */
#define DDRPERFM_CNT0_CNT_17  (0x20000U << DDRPERFM_CNT0_CNT_Pos)    /*!< 0x00020000 */
#define DDRPERFM_CNT0_CNT_18  (0x40000U << DDRPERFM_CNT0_CNT_Pos)    /*!< 0x00040000 */
#define DDRPERFM_CNT0_CNT_19  (0x80000U << DDRPERFM_CNT0_CNT_Pos)    /*!< 0x00080000 */
#define DDRPERFM_CNT0_CNT_20  (0x100000U << DDRPERFM_CNT0_CNT_Pos)   /*!< 0x00100000 */
#define DDRPERFM_CNT0_CNT_21  (0x200000U << DDRPERFM_CNT0_CNT_Pos)   /*!< 0x00200000 */
#define DDRPERFM_CNT0_CNT_22  (0x400000U << DDRPERFM_CNT0_CNT_Pos)   /*!< 0x00400000 */
#define DDRPERFM_CNT0_CNT_23  (0x800000U << DDRPERFM_CNT0_CNT_Pos)   /*!< 0x00800000 */
#define DDRPERFM_CNT0_CNT_24  (0x1000000U << DDRPERFM_CNT0_CNT_Pos)  /*!< 0x01000000 */
#define DDRPERFM_CNT0_CNT_25  (0x2000000U << DDRPERFM_CNT0_CNT_Pos)  /*!< 0x02000000 */
#define DDRPERFM_CNT0_CNT_26  (0x4000000U << DDRPERFM_CNT0_CNT_Pos)  /*!< 0x04000000 */
#define DDRPERFM_CNT0_CNT_27  (0x8000000U << DDRPERFM_CNT0_CNT_Pos)  /*!< 0x08000000 */
#define DDRPERFM_CNT0_CNT_28  (0x10000000U << DDRPERFM_CNT0_CNT_Pos) /*!< 0x10000000 */
#define DDRPERFM_CNT0_CNT_29  (0x20000000U << DDRPERFM_CNT0_CNT_Pos) /*!< 0x20000000 */
#define DDRPERFM_CNT0_CNT_30  (0x40000000U << DDRPERFM_CNT0_CNT_Pos) /*!< 0x40000000 */
#define DDRPERFM_CNT0_CNT_31  (0x80000000U << DDRPERFM_CNT0_CNT_Pos) /*!< 0x80000000 */

/****************  Bit definition for DDRPERFM_CNT1 register  *****************/
#define DDRPERFM_CNT1_CNT_Pos (0U)
#define DDRPERFM_CNT1_CNT_Msk (0xFFFFFFFFU << DDRPERFM_CNT1_CNT_Pos) /*!< 0xFFFFFFFF */
#define DDRPERFM_CNT1_CNT     DDRPERFM_CNT1_CNT_Msk                  /*!< event counter value. */
#define DDRPERFM_CNT1_CNT_0   (0x1U << DDRPERFM_CNT1_CNT_Pos)        /*!< 0x00000001 */
#define DDRPERFM_CNT1_CNT_1   (0x2U << DDRPERFM_CNT1_CNT_Pos)        /*!< 0x00000002 */
#define DDRPERFM_CNT1_CNT_2   (0x4U << DDRPERFM_CNT1_CNT_Pos)        /*!< 0x00000004 */
#define DDRPERFM_CNT1_CNT_3   (0x8U << DDRPERFM_CNT1_CNT_Pos)        /*!< 0x00000008 */
#define DDRPERFM_CNT1_CNT_4   (0x10U << DDRPERFM_CNT1_CNT_Pos)       /*!< 0x00000010 */
#define DDRPERFM_CNT1_CNT_5   (0x20U << DDRPERFM_CNT1_CNT_Pos)       /*!< 0x00000020 */
#define DDRPERFM_CNT1_CNT_6   (0x40U << DDRPERFM_CNT1_CNT_Pos)       /*!< 0x00000040 */
#define DDRPERFM_CNT1_CNT_7   (0x80U << DDRPERFM_CNT1_CNT_Pos)       /*!< 0x00000080 */
#define DDRPERFM_CNT1_CNT_8   (0x100U << DDRPERFM_CNT1_CNT_Pos)      /*!< 0x00000100 */
#define DDRPERFM_CNT1_CNT_9   (0x200U << DDRPERFM_CNT1_CNT_Pos)      /*!< 0x00000200 */
#define DDRPERFM_CNT1_CNT_10  (0x400U << DDRPERFM_CNT1_CNT_Pos)      /*!< 0x00000400 */
#define DDRPERFM_CNT1_CNT_11  (0x800U << DDRPERFM_CNT1_CNT_Pos)      /*!< 0x00000800 */
#define DDRPERFM_CNT1_CNT_12  (0x1000U << DDRPERFM_CNT1_CNT_Pos)     /*!< 0x00001000 */
#define DDRPERFM_CNT1_CNT_13  (0x2000U << DDRPERFM_CNT1_CNT_Pos)     /*!< 0x00002000 */
#define DDRPERFM_CNT1_CNT_14  (0x4000U << DDRPERFM_CNT1_CNT_Pos)     /*!< 0x00004000 */
#define DDRPERFM_CNT1_CNT_15  (0x8000U << DDRPERFM_CNT1_CNT_Pos)     /*!< 0x00008000 */
#define DDRPERFM_CNT1_CNT_16  (0x10000U << DDRPERFM_CNT1_CNT_Pos)    /*!< 0x00010000 */
#define DDRPERFM_CNT1_CNT_17  (0x20000U << DDRPERFM_CNT1_CNT_Pos)    /*!< 0x00020000 */
#define DDRPERFM_CNT1_CNT_18  (0x40000U << DDRPERFM_CNT1_CNT_Pos)    /*!< 0x00040000 */
#define DDRPERFM_CNT1_CNT_19  (0x80000U << DDRPERFM_CNT1_CNT_Pos)    /*!< 0x00080000 */
#define DDRPERFM_CNT1_CNT_20  (0x100000U << DDRPERFM_CNT1_CNT_Pos)   /*!< 0x00100000 */
#define DDRPERFM_CNT1_CNT_21  (0x200000U << DDRPERFM_CNT1_CNT_Pos)   /*!< 0x00200000 */
#define DDRPERFM_CNT1_CNT_22  (0x400000U << DDRPERFM_CNT1_CNT_Pos)   /*!< 0x00400000 */
#define DDRPERFM_CNT1_CNT_23  (0x800000U << DDRPERFM_CNT1_CNT_Pos)   /*!< 0x00800000 */
#define DDRPERFM_CNT1_CNT_24  (0x1000000U << DDRPERFM_CNT1_CNT_Pos)  /*!< 0x01000000 */
#define DDRPERFM_CNT1_CNT_25  (0x2000000U << DDRPERFM_CNT1_CNT_Pos)  /*!< 0x02000000 */
#define DDRPERFM_CNT1_CNT_26  (0x4000000U << DDRPERFM_CNT1_CNT_Pos)  /*!< 0x04000000 */
#define DDRPERFM_CNT1_CNT_27  (0x8000000U << DDRPERFM_CNT1_CNT_Pos)  /*!< 0x08000000 */
#define DDRPERFM_CNT1_CNT_28  (0x10000000U << DDRPERFM_CNT1_CNT_Pos) /*!< 0x10000000 */
#define DDRPERFM_CNT1_CNT_29  (0x20000000U << DDRPERFM_CNT1_CNT_Pos) /*!< 0x20000000 */
#define DDRPERFM_CNT1_CNT_30  (0x40000000U << DDRPERFM_CNT1_CNT_Pos) /*!< 0x40000000 */
#define DDRPERFM_CNT1_CNT_31  (0x80000000U << DDRPERFM_CNT1_CNT_Pos) /*!< 0x80000000 */

/****************  Bit definition for DDRPERFM_CNT2 register  *****************/
#define DDRPERFM_CNT2_CNT_Pos (0U)
#define DDRPERFM_CNT2_CNT_Msk (0xFFFFFFFFU << DDRPERFM_CNT2_CNT_Pos) /*!< 0xFFFFFFFF */
#define DDRPERFM_CNT2_CNT     DDRPERFM_CNT2_CNT_Msk                  /*!< event counter value. */
#define DDRPERFM_CNT2_CNT_0   (0x1U << DDRPERFM_CNT2_CNT_Pos)        /*!< 0x00000001 */
#define DDRPERFM_CNT2_CNT_1   (0x2U << DDRPERFM_CNT2_CNT_Pos)        /*!< 0x00000002 */
#define DDRPERFM_CNT2_CNT_2   (0x4U << DDRPERFM_CNT2_CNT_Pos)        /*!< 0x00000004 */
#define DDRPERFM_CNT2_CNT_3   (0x8U << DDRPERFM_CNT2_CNT_Pos)        /*!< 0x00000008 */
#define DDRPERFM_CNT2_CNT_4   (0x10U << DDRPERFM_CNT2_CNT_Pos)       /*!< 0x00000010 */
#define DDRPERFM_CNT2_CNT_5   (0x20U << DDRPERFM_CNT2_CNT_Pos)       /*!< 0x00000020 */
#define DDRPERFM_CNT2_CNT_6   (0x40U << DDRPERFM_CNT2_CNT_Pos)       /*!< 0x00000040 */
#define DDRPERFM_CNT2_CNT_7   (0x80U << DDRPERFM_CNT2_CNT_Pos)       /*!< 0x00000080 */
#define DDRPERFM_CNT2_CNT_8   (0x100U << DDRPERFM_CNT2_CNT_Pos)      /*!< 0x00000100 */
#define DDRPERFM_CNT2_CNT_9   (0x200U << DDRPERFM_CNT2_CNT_Pos)      /*!< 0x00000200 */
#define DDRPERFM_CNT2_CNT_10  (0x400U << DDRPERFM_CNT2_CNT_Pos)      /*!< 0x00000400 */
#define DDRPERFM_CNT2_CNT_11  (0x800U << DDRPERFM_CNT2_CNT_Pos)      /*!< 0x00000800 */
#define DDRPERFM_CNT2_CNT_12  (0x1000U << DDRPERFM_CNT2_CNT_Pos)     /*!< 0x00001000 */
#define DDRPERFM_CNT2_CNT_13  (0x2000U << DDRPERFM_CNT2_CNT_Pos)     /*!< 0x00002000 */
#define DDRPERFM_CNT2_CNT_14  (0x4000U << DDRPERFM_CNT2_CNT_Pos)     /*!< 0x00004000 */
#define DDRPERFM_CNT2_CNT_15  (0x8000U << DDRPERFM_CNT2_CNT_Pos)     /*!< 0x00008000 */
#define DDRPERFM_CNT2_CNT_16  (0x10000U << DDRPERFM_CNT2_CNT_Pos)    /*!< 0x00010000 */
#define DDRPERFM_CNT2_CNT_17  (0x20000U << DDRPERFM_CNT2_CNT_Pos)    /*!< 0x00020000 */
#define DDRPERFM_CNT2_CNT_18  (0x40000U << DDRPERFM_CNT2_CNT_Pos)    /*!< 0x00040000 */
#define DDRPERFM_CNT2_CNT_19  (0x80000U << DDRPERFM_CNT2_CNT_Pos)    /*!< 0x00080000 */
#define DDRPERFM_CNT2_CNT_20  (0x100000U << DDRPERFM_CNT2_CNT_Pos)   /*!< 0x00100000 */
#define DDRPERFM_CNT2_CNT_21  (0x200000U << DDRPERFM_CNT2_CNT_Pos)   /*!< 0x00200000 */
#define DDRPERFM_CNT2_CNT_22  (0x400000U << DDRPERFM_CNT2_CNT_Pos)   /*!< 0x00400000 */
#define DDRPERFM_CNT2_CNT_23  (0x800000U << DDRPERFM_CNT2_CNT_Pos)   /*!< 0x00800000 */
#define DDRPERFM_CNT2_CNT_24  (0x1000000U << DDRPERFM_CNT2_CNT_Pos)  /*!< 0x01000000 */
#define DDRPERFM_CNT2_CNT_25  (0x2000000U << DDRPERFM_CNT2_CNT_Pos)  /*!< 0x02000000 */
#define DDRPERFM_CNT2_CNT_26  (0x4000000U << DDRPERFM_CNT2_CNT_Pos)  /*!< 0x04000000 */
#define DDRPERFM_CNT2_CNT_27  (0x8000000U << DDRPERFM_CNT2_CNT_Pos)  /*!< 0x08000000 */
#define DDRPERFM_CNT2_CNT_28  (0x10000000U << DDRPERFM_CNT2_CNT_Pos) /*!< 0x10000000 */
#define DDRPERFM_CNT2_CNT_29  (0x20000000U << DDRPERFM_CNT2_CNT_Pos) /*!< 0x20000000 */
#define DDRPERFM_CNT2_CNT_30  (0x40000000U << DDRPERFM_CNT2_CNT_Pos) /*!< 0x40000000 */
#define DDRPERFM_CNT2_CNT_31  (0x80000000U << DDRPERFM_CNT2_CNT_Pos) /*!< 0x80000000 */

/****************  Bit definition for DDRPERFM_CNT3 register  *****************/
#define DDRPERFM_CNT3_CNT_Pos (0U)
#define DDRPERFM_CNT3_CNT_Msk (0xFFFFFFFFU << DDRPERFM_CNT3_CNT_Pos) /*!< 0xFFFFFFFF */
#define DDRPERFM_CNT3_CNT     DDRPERFM_CNT3_CNT_Msk                  /*!< event counter value. */
#define DDRPERFM_CNT3_CNT_0   (0x1U << DDRPERFM_CNT3_CNT_Pos)        /*!< 0x00000001 */
#define DDRPERFM_CNT3_CNT_1   (0x2U << DDRPERFM_CNT3_CNT_Pos)        /*!< 0x00000002 */
#define DDRPERFM_CNT3_CNT_2   (0x4U << DDRPERFM_CNT3_CNT_Pos)        /*!< 0x00000004 */
#define DDRPERFM_CNT3_CNT_3   (0x8U << DDRPERFM_CNT3_CNT_Pos)        /*!< 0x00000008 */
#define DDRPERFM_CNT3_CNT_4   (0x10U << DDRPERFM_CNT3_CNT_Pos)       /*!< 0x00000010 */
#define DDRPERFM_CNT3_CNT_5   (0x20U << DDRPERFM_CNT3_CNT_Pos)       /*!< 0x00000020 */
#define DDRPERFM_CNT3_CNT_6   (0x40U << DDRPERFM_CNT3_CNT_Pos)       /*!< 0x00000040 */
#define DDRPERFM_CNT3_CNT_7   (0x80U << DDRPERFM_CNT3_CNT_Pos)       /*!< 0x00000080 */
#define DDRPERFM_CNT3_CNT_8   (0x100U << DDRPERFM_CNT3_CNT_Pos)      /*!< 0x00000100 */
#define DDRPERFM_CNT3_CNT_9   (0x200U << DDRPERFM_CNT3_CNT_Pos)      /*!< 0x00000200 */
#define DDRPERFM_CNT3_CNT_10  (0x400U << DDRPERFM_CNT3_CNT_Pos)      /*!< 0x00000400 */
#define DDRPERFM_CNT3_CNT_11  (0x800U << DDRPERFM_CNT3_CNT_Pos)      /*!< 0x00000800 */
#define DDRPERFM_CNT3_CNT_12  (0x1000U << DDRPERFM_CNT3_CNT_Pos)     /*!< 0x00001000 */
#define DDRPERFM_CNT3_CNT_13  (0x2000U << DDRPERFM_CNT3_CNT_Pos)     /*!< 0x00002000 */
#define DDRPERFM_CNT3_CNT_14  (0x4000U << DDRPERFM_CNT3_CNT_Pos)     /*!< 0x00004000 */
#define DDRPERFM_CNT3_CNT_15  (0x8000U << DDRPERFM_CNT3_CNT_Pos)     /*!< 0x00008000 */
#define DDRPERFM_CNT3_CNT_16  (0x10000U << DDRPERFM_CNT3_CNT_Pos)    /*!< 0x00010000 */
#define DDRPERFM_CNT3_CNT_17  (0x20000U << DDRPERFM_CNT3_CNT_Pos)    /*!< 0x00020000 */
#define DDRPERFM_CNT3_CNT_18  (0x40000U << DDRPERFM_CNT3_CNT_Pos)    /*!< 0x00040000 */
#define DDRPERFM_CNT3_CNT_19  (0x80000U << DDRPERFM_CNT3_CNT_Pos)    /*!< 0x00080000 */
#define DDRPERFM_CNT3_CNT_20  (0x100000U << DDRPERFM_CNT3_CNT_Pos)   /*!< 0x00100000 */
#define DDRPERFM_CNT3_CNT_21  (0x200000U << DDRPERFM_CNT3_CNT_Pos)   /*!< 0x00200000 */
#define DDRPERFM_CNT3_CNT_22  (0x400000U << DDRPERFM_CNT3_CNT_Pos)   /*!< 0x00400000 */
#define DDRPERFM_CNT3_CNT_23  (0x800000U << DDRPERFM_CNT3_CNT_Pos)   /*!< 0x00800000 */
#define DDRPERFM_CNT3_CNT_24  (0x1000000U << DDRPERFM_CNT3_CNT_Pos)  /*!< 0x01000000 */
#define DDRPERFM_CNT3_CNT_25  (0x2000000U << DDRPERFM_CNT3_CNT_Pos)  /*!< 0x02000000 */
#define DDRPERFM_CNT3_CNT_26  (0x4000000U << DDRPERFM_CNT3_CNT_Pos)  /*!< 0x04000000 */
#define DDRPERFM_CNT3_CNT_27  (0x8000000U << DDRPERFM_CNT3_CNT_Pos)  /*!< 0x08000000 */
#define DDRPERFM_CNT3_CNT_28  (0x10000000U << DDRPERFM_CNT3_CNT_Pos) /*!< 0x10000000 */
#define DDRPERFM_CNT3_CNT_29  (0x20000000U << DDRPERFM_CNT3_CNT_Pos) /*!< 0x20000000 */
#define DDRPERFM_CNT3_CNT_30  (0x40000000U << DDRPERFM_CNT3_CNT_Pos) /*!< 0x40000000 */
#define DDRPERFM_CNT3_CNT_31  (0x80000000U << DDRPERFM_CNT3_CNT_Pos) /*!< 0x80000000 */

/****************  Bit definition for DDRPERFM_HWCFG register  ****************/
#define DDRPERFM_HWCFG_NCNT_Pos (0U)
#define DDRPERFM_HWCFG_NCNT_Msk (0xFU << DDRPERFM_HWCFG_NCNT_Pos) /*!< 0x0000000F */
#define DDRPERFM_HWCFG_NCNT     DDRPERFM_HWCFG_NCNT_Msk           /*!< number of counters for this configuration (4) */
#define DDRPERFM_HWCFG_NCNT_0   (0x1U << DDRPERFM_HWCFG_NCNT_Pos) /*!< 0x00000001 */
#define DDRPERFM_HWCFG_NCNT_1   (0x2U << DDRPERFM_HWCFG_NCNT_Pos) /*!< 0x00000002 */
#define DDRPERFM_HWCFG_NCNT_2   (0x4U << DDRPERFM_HWCFG_NCNT_Pos) /*!< 0x00000004 */
#define DDRPERFM_HWCFG_NCNT_3   (0x8U << DDRPERFM_HWCFG_NCNT_Pos) /*!< 0x00000008 */

/*****************  Bit definition for DDRPERFM_VER register  *****************/
#define DDRPERFM_VER_MINREV_Pos (0U)
#define DDRPERFM_VER_MINREV_Msk (0xFU << DDRPERFM_VER_MINREV_Pos) /*!< 0x0000000F */
#define DDRPERFM_VER_MINREV     DDRPERFM_VER_MINREV_Msk           /*!< Minor revision number. */
#define DDRPERFM_VER_MINREV_0   (0x1U << DDRPERFM_VER_MINREV_Pos) /*!< 0x00000001 */
#define DDRPERFM_VER_MINREV_1   (0x2U << DDRPERFM_VER_MINREV_Pos) /*!< 0x00000002 */
#define DDRPERFM_VER_MINREV_2   (0x4U << DDRPERFM_VER_MINREV_Pos) /*!< 0x00000004 */
#define DDRPERFM_VER_MINREV_3   (0x8U << DDRPERFM_VER_MINREV_Pos) /*!< 0x00000008 */
#define DDRPERFM_VER_MAJREV_Pos (4U)
#define DDRPERFM_VER_MAJREV_Msk (0xFU << DDRPERFM_VER_MAJREV_Pos) /*!< 0x000000F0 */
#define DDRPERFM_VER_MAJREV     DDRPERFM_VER_MAJREV_Msk           /*!< Major revision number. */
#define DDRPERFM_VER_MAJREV_0   (0x1U << DDRPERFM_VER_MAJREV_Pos) /*!< 0x00000010 */
#define DDRPERFM_VER_MAJREV_1   (0x2U << DDRPERFM_VER_MAJREV_Pos) /*!< 0x00000020 */
#define DDRPERFM_VER_MAJREV_2   (0x4U << DDRPERFM_VER_MAJREV_Pos) /*!< 0x00000040 */
#define DDRPERFM_VER_MAJREV_3   (0x8U << DDRPERFM_VER_MAJREV_Pos) /*!< 0x00000080 */

/*****************  Bit definition for DDRPERFM_ID register  ******************/
#define DDRPERFM_ID_ID_Pos (0U)
#define DDRPERFM_ID_ID_Msk (0xFFFFFFFFU << DDRPERFM_ID_ID_Pos) /*!< 0xFFFFFFFF */
#define DDRPERFM_ID_ID     DDRPERFM_ID_ID_Msk                  /*!< DDRPERFM unique identification. */
#define DDRPERFM_ID_ID_0   (0x1U << DDRPERFM_ID_ID_Pos)        /*!< 0x00000001 */
#define DDRPERFM_ID_ID_1   (0x2U << DDRPERFM_ID_ID_Pos)        /*!< 0x00000002 */
#define DDRPERFM_ID_ID_2   (0x4U << DDRPERFM_ID_ID_Pos)        /*!< 0x00000004 */
#define DDRPERFM_ID_ID_3   (0x8U << DDRPERFM_ID_ID_Pos)        /*!< 0x00000008 */
#define DDRPERFM_ID_ID_4   (0x10U << DDRPERFM_ID_ID_Pos)       /*!< 0x00000010 */
#define DDRPERFM_ID_ID_5   (0x20U << DDRPERFM_ID_ID_Pos)       /*!< 0x00000020 */
#define DDRPERFM_ID_ID_6   (0x40U << DDRPERFM_ID_ID_Pos)       /*!< 0x00000040 */
#define DDRPERFM_ID_ID_7   (0x80U << DDRPERFM_ID_ID_Pos)       /*!< 0x00000080 */
#define DDRPERFM_ID_ID_8   (0x100U << DDRPERFM_ID_ID_Pos)      /*!< 0x00000100 */
#define DDRPERFM_ID_ID_9   (0x200U << DDRPERFM_ID_ID_Pos)      /*!< 0x00000200 */
#define DDRPERFM_ID_ID_10  (0x400U << DDRPERFM_ID_ID_Pos)      /*!< 0x00000400 */
#define DDRPERFM_ID_ID_11  (0x800U << DDRPERFM_ID_ID_Pos)      /*!< 0x00000800 */
#define DDRPERFM_ID_ID_12  (0x1000U << DDRPERFM_ID_ID_Pos)     /*!< 0x00001000 */
#define DDRPERFM_ID_ID_13  (0x2000U << DDRPERFM_ID_ID_Pos)     /*!< 0x00002000 */
#define DDRPERFM_ID_ID_14  (0x4000U << DDRPERFM_ID_ID_Pos)     /*!< 0x00004000 */
#define DDRPERFM_ID_ID_15  (0x8000U << DDRPERFM_ID_ID_Pos)     /*!< 0x00008000 */
#define DDRPERFM_ID_ID_16  (0x10000U << DDRPERFM_ID_ID_Pos)    /*!< 0x00010000 */
#define DDRPERFM_ID_ID_17  (0x20000U << DDRPERFM_ID_ID_Pos)    /*!< 0x00020000 */
#define DDRPERFM_ID_ID_18  (0x40000U << DDRPERFM_ID_ID_Pos)    /*!< 0x00040000 */
#define DDRPERFM_ID_ID_19  (0x80000U << DDRPERFM_ID_ID_Pos)    /*!< 0x00080000 */
#define DDRPERFM_ID_ID_20  (0x100000U << DDRPERFM_ID_ID_Pos)   /*!< 0x00100000 */
#define DDRPERFM_ID_ID_21  (0x200000U << DDRPERFM_ID_ID_Pos)   /*!< 0x00200000 */
#define DDRPERFM_ID_ID_22  (0x400000U << DDRPERFM_ID_ID_Pos)   /*!< 0x00400000 */
#define DDRPERFM_ID_ID_23  (0x800000U << DDRPERFM_ID_ID_Pos)   /*!< 0x00800000 */
#define DDRPERFM_ID_ID_24  (0x1000000U << DDRPERFM_ID_ID_Pos)  /*!< 0x01000000 */
#define DDRPERFM_ID_ID_25  (0x2000000U << DDRPERFM_ID_ID_Pos)  /*!< 0x02000000 */
#define DDRPERFM_ID_ID_26  (0x4000000U << DDRPERFM_ID_ID_Pos)  /*!< 0x04000000 */
#define DDRPERFM_ID_ID_27  (0x8000000U << DDRPERFM_ID_ID_Pos)  /*!< 0x08000000 */
#define DDRPERFM_ID_ID_28  (0x10000000U << DDRPERFM_ID_ID_Pos) /*!< 0x10000000 */
#define DDRPERFM_ID_ID_29  (0x20000000U << DDRPERFM_ID_ID_Pos) /*!< 0x20000000 */
#define DDRPERFM_ID_ID_30  (0x40000000U << DDRPERFM_ID_ID_Pos) /*!< 0x40000000 */
#define DDRPERFM_ID_ID_31  (0x80000000U << DDRPERFM_ID_ID_Pos) /*!< 0x80000000 */

/*****************  Bit definition for DDRPERFM_SID register  *****************/
#define DDRPERFM_SID_SID_Pos (0U)
#define DDRPERFM_SID_SID_Msk (0xFFFFFFFFU << DDRPERFM_SID_SID_Pos) /*!< 0xFFFFFFFF */
#define DDRPERFM_SID_SID     DDRPERFM_SID_SID_Msk                  /*!< magic ID for automatic IP discovery. */
#define DDRPERFM_SID_SID_0   (0x1U << DDRPERFM_SID_SID_Pos)        /*!< 0x00000001 */
#define DDRPERFM_SID_SID_1   (0x2U << DDRPERFM_SID_SID_Pos)        /*!< 0x00000002 */
#define DDRPERFM_SID_SID_2   (0x4U << DDRPERFM_SID_SID_Pos)        /*!< 0x00000004 */
#define DDRPERFM_SID_SID_3   (0x8U << DDRPERFM_SID_SID_Pos)        /*!< 0x00000008 */
#define DDRPERFM_SID_SID_4   (0x10U << DDRPERFM_SID_SID_Pos)       /*!< 0x00000010 */
#define DDRPERFM_SID_SID_5   (0x20U << DDRPERFM_SID_SID_Pos)       /*!< 0x00000020 */
#define DDRPERFM_SID_SID_6   (0x40U << DDRPERFM_SID_SID_Pos)       /*!< 0x00000040 */
#define DDRPERFM_SID_SID_7   (0x80U << DDRPERFM_SID_SID_Pos)       /*!< 0x00000080 */
#define DDRPERFM_SID_SID_8   (0x100U << DDRPERFM_SID_SID_Pos)      /*!< 0x00000100 */
#define DDRPERFM_SID_SID_9   (0x200U << DDRPERFM_SID_SID_Pos)      /*!< 0x00000200 */
#define DDRPERFM_SID_SID_10  (0x400U << DDRPERFM_SID_SID_Pos)      /*!< 0x00000400 */
#define DDRPERFM_SID_SID_11  (0x800U << DDRPERFM_SID_SID_Pos)      /*!< 0x00000800 */
#define DDRPERFM_SID_SID_12  (0x1000U << DDRPERFM_SID_SID_Pos)     /*!< 0x00001000 */
#define DDRPERFM_SID_SID_13  (0x2000U << DDRPERFM_SID_SID_Pos)     /*!< 0x00002000 */
#define DDRPERFM_SID_SID_14  (0x4000U << DDRPERFM_SID_SID_Pos)     /*!< 0x00004000 */
#define DDRPERFM_SID_SID_15  (0x8000U << DDRPERFM_SID_SID_Pos)     /*!< 0x00008000 */
#define DDRPERFM_SID_SID_16  (0x10000U << DDRPERFM_SID_SID_Pos)    /*!< 0x00010000 */
#define DDRPERFM_SID_SID_17  (0x20000U << DDRPERFM_SID_SID_Pos)    /*!< 0x00020000 */
#define DDRPERFM_SID_SID_18  (0x40000U << DDRPERFM_SID_SID_Pos)    /*!< 0x00040000 */
#define DDRPERFM_SID_SID_19  (0x80000U << DDRPERFM_SID_SID_Pos)    /*!< 0x00080000 */
#define DDRPERFM_SID_SID_20  (0x100000U << DDRPERFM_SID_SID_Pos)   /*!< 0x00100000 */
#define DDRPERFM_SID_SID_21  (0x200000U << DDRPERFM_SID_SID_Pos)   /*!< 0x00200000 */
#define DDRPERFM_SID_SID_22  (0x400000U << DDRPERFM_SID_SID_Pos)   /*!< 0x00400000 */
#define DDRPERFM_SID_SID_23  (0x800000U << DDRPERFM_SID_SID_Pos)   /*!< 0x00800000 */
#define DDRPERFM_SID_SID_24  (0x1000000U << DDRPERFM_SID_SID_Pos)  /*!< 0x01000000 */
#define DDRPERFM_SID_SID_25  (0x2000000U << DDRPERFM_SID_SID_Pos)  /*!< 0x02000000 */
#define DDRPERFM_SID_SID_26  (0x4000000U << DDRPERFM_SID_SID_Pos)  /*!< 0x04000000 */
#define DDRPERFM_SID_SID_27  (0x8000000U << DDRPERFM_SID_SID_Pos)  /*!< 0x08000000 */
#define DDRPERFM_SID_SID_28  (0x10000000U << DDRPERFM_SID_SID_Pos) /*!< 0x10000000 */
#define DDRPERFM_SID_SID_29  (0x20000000U << DDRPERFM_SID_SID_Pos) /*!< 0x20000000 */
#define DDRPERFM_SID_SID_30  (0x40000000U << DDRPERFM_SID_SID_Pos) /*!< 0x40000000 */
#define DDRPERFM_SID_SID_31  (0x80000000U << DDRPERFM_SID_SID_Pos) /*!< 0x80000000 */

/******************************************************************************/
/*                                                                            */
/*                    DDRPHYC block description (DDRPHYC)                     */
/*                                                                            */
/******************************************************************************/

/*****************  Bit definition for DDRPHYC_RIDR register  *****************/
#define DDRPHYC_RIDR_PUBMNR_Pos (0U)
#define DDRPHYC_RIDR_PUBMNR_Msk (0xFU << DDRPHYC_RIDR_PUBMNR_Pos) /*!< 0x0000000F */
#define DDRPHYC_RIDR_PUBMNR     DDRPHYC_RIDR_PUBMNR_Msk           /*!< PUB minor rev */
#define DDRPHYC_RIDR_PUBMNR_0   (0x1U << DDRPHYC_RIDR_PUBMNR_Pos) /*!< 0x00000001 */
#define DDRPHYC_RIDR_PUBMNR_1   (0x2U << DDRPHYC_RIDR_PUBMNR_Pos) /*!< 0x00000002 */
#define DDRPHYC_RIDR_PUBMNR_2   (0x4U << DDRPHYC_RIDR_PUBMNR_Pos) /*!< 0x00000004 */
#define DDRPHYC_RIDR_PUBMNR_3   (0x8U << DDRPHYC_RIDR_PUBMNR_Pos) /*!< 0x00000008 */
#define DDRPHYC_RIDR_PUBMDR_Pos (4U)
#define DDRPHYC_RIDR_PUBMDR_Msk (0xFU << DDRPHYC_RIDR_PUBMDR_Pos) /*!< 0x000000F0 */
#define DDRPHYC_RIDR_PUBMDR     DDRPHYC_RIDR_PUBMDR_Msk           /*!< PUB moderate rev */
#define DDRPHYC_RIDR_PUBMDR_0   (0x1U << DDRPHYC_RIDR_PUBMDR_Pos) /*!< 0x00000010 */
#define DDRPHYC_RIDR_PUBMDR_1   (0x2U << DDRPHYC_RIDR_PUBMDR_Pos) /*!< 0x00000020 */
#define DDRPHYC_RIDR_PUBMDR_2   (0x4U << DDRPHYC_RIDR_PUBMDR_Pos) /*!< 0x00000040 */
#define DDRPHYC_RIDR_PUBMDR_3   (0x8U << DDRPHYC_RIDR_PUBMDR_Pos) /*!< 0x00000080 */
#define DDRPHYC_RIDR_PUBMJR_Pos (8U)
#define DDRPHYC_RIDR_PUBMJR_Msk (0xFU << DDRPHYC_RIDR_PUBMJR_Pos) /*!< 0x00000F00 */
#define DDRPHYC_RIDR_PUBMJR     DDRPHYC_RIDR_PUBMJR_Msk           /*!< PUB maj rev */
#define DDRPHYC_RIDR_PUBMJR_0   (0x1U << DDRPHYC_RIDR_PUBMJR_Pos) /*!< 0x00000100 */
#define DDRPHYC_RIDR_PUBMJR_1   (0x2U << DDRPHYC_RIDR_PUBMJR_Pos) /*!< 0x00000200 */
#define DDRPHYC_RIDR_PUBMJR_2   (0x4U << DDRPHYC_RIDR_PUBMJR_Pos) /*!< 0x00000400 */
#define DDRPHYC_RIDR_PUBMJR_3   (0x8U << DDRPHYC_RIDR_PUBMJR_Pos) /*!< 0x00000800 */
#define DDRPHYC_RIDR_PHYMNR_Pos (12U)
#define DDRPHYC_RIDR_PHYMNR_Msk (0xFU << DDRPHYC_RIDR_PHYMNR_Pos) /*!< 0x0000F000 */
#define DDRPHYC_RIDR_PHYMNR     DDRPHYC_RIDR_PHYMNR_Msk           /*!< PHY minor rev */
#define DDRPHYC_RIDR_PHYMNR_0   (0x1U << DDRPHYC_RIDR_PHYMNR_Pos) /*!< 0x00001000 */
#define DDRPHYC_RIDR_PHYMNR_1   (0x2U << DDRPHYC_RIDR_PHYMNR_Pos) /*!< 0x00002000 */
#define DDRPHYC_RIDR_PHYMNR_2   (0x4U << DDRPHYC_RIDR_PHYMNR_Pos) /*!< 0x00004000 */
#define DDRPHYC_RIDR_PHYMNR_3   (0x8U << DDRPHYC_RIDR_PHYMNR_Pos) /*!< 0x00008000 */
#define DDRPHYC_RIDR_PHYMDR_Pos (16U)
#define DDRPHYC_RIDR_PHYMDR_Msk (0xFU << DDRPHYC_RIDR_PHYMDR_Pos) /*!< 0x000F0000 */
#define DDRPHYC_RIDR_PHYMDR     DDRPHYC_RIDR_PHYMDR_Msk           /*!< PHY moderate rev */
#define DDRPHYC_RIDR_PHYMDR_0   (0x1U << DDRPHYC_RIDR_PHYMDR_Pos) /*!< 0x00010000 */
#define DDRPHYC_RIDR_PHYMDR_1   (0x2U << DDRPHYC_RIDR_PHYMDR_Pos) /*!< 0x00020000 */
#define DDRPHYC_RIDR_PHYMDR_2   (0x4U << DDRPHYC_RIDR_PHYMDR_Pos) /*!< 0x00040000 */
#define DDRPHYC_RIDR_PHYMDR_3   (0x8U << DDRPHYC_RIDR_PHYMDR_Pos) /*!< 0x00080000 */
#define DDRPHYC_RIDR_PHYMJR_Pos (20U)
#define DDRPHYC_RIDR_PHYMJR_Msk (0xFU << DDRPHYC_RIDR_PHYMJR_Pos) /*!< 0x00F00000 */
#define DDRPHYC_RIDR_PHYMJR     DDRPHYC_RIDR_PHYMJR_Msk           /*!< PHY maj rev */
#define DDRPHYC_RIDR_PHYMJR_0   (0x1U << DDRPHYC_RIDR_PHYMJR_Pos) /*!< 0x00100000 */
#define DDRPHYC_RIDR_PHYMJR_1   (0x2U << DDRPHYC_RIDR_PHYMJR_Pos) /*!< 0x00200000 */
#define DDRPHYC_RIDR_PHYMJR_2   (0x4U << DDRPHYC_RIDR_PHYMJR_Pos) /*!< 0x00400000 */
#define DDRPHYC_RIDR_PHYMJR_3   (0x8U << DDRPHYC_RIDR_PHYMJR_Pos) /*!< 0x00800000 */
#define DDRPHYC_RIDR_UDRID_Pos  (24U)
#define DDRPHYC_RIDR_UDRID_Msk  (0xFFU << DDRPHYC_RIDR_UDRID_Pos) /*!< 0xFF000000 */
#define DDRPHYC_RIDR_UDRID      DDRPHYC_RIDR_UDRID_Msk            /*!< User-defined rev ID */
#define DDRPHYC_RIDR_UDRID_0    (0x1U << DDRPHYC_RIDR_UDRID_Pos)  /*!< 0x01000000 */
#define DDRPHYC_RIDR_UDRID_1    (0x2U << DDRPHYC_RIDR_UDRID_Pos)  /*!< 0x02000000 */
#define DDRPHYC_RIDR_UDRID_2    (0x4U << DDRPHYC_RIDR_UDRID_Pos)  /*!< 0x04000000 */
#define DDRPHYC_RIDR_UDRID_3    (0x8U << DDRPHYC_RIDR_UDRID_Pos)  /*!< 0x08000000 */
#define DDRPHYC_RIDR_UDRID_4    (0x10U << DDRPHYC_RIDR_UDRID_Pos) /*!< 0x10000000 */
#define DDRPHYC_RIDR_UDRID_5    (0x20U << DDRPHYC_RIDR_UDRID_Pos) /*!< 0x20000000 */
#define DDRPHYC_RIDR_UDRID_6    (0x40U << DDRPHYC_RIDR_UDRID_Pos) /*!< 0x40000000 */
#define DDRPHYC_RIDR_UDRID_7    (0x80U << DDRPHYC_RIDR_UDRID_Pos) /*!< 0x80000000 */

/*****************  Bit definition for DDRPHYC_PIR register  ******************/
#define DDRPHYC_PIR_INIT_Pos     (0U)
#define DDRPHYC_PIR_INIT_Msk     (0x1U << DDRPHYC_PIR_INIT_Pos)     /*!< 0x00000001 */
#define DDRPHYC_PIR_INIT         DDRPHYC_PIR_INIT_Msk               /*!< Initialization trigger */
#define DDRPHYC_PIR_DLLSRST_Pos  (1U)
#define DDRPHYC_PIR_DLLSRST_Msk  (0x1U << DDRPHYC_PIR_DLLSRST_Pos)  /*!< 0x00000002 */
#define DDRPHYC_PIR_DLLSRST      DDRPHYC_PIR_DLLSRST_Msk            /*!< DLL soft reset */
#define DDRPHYC_PIR_DLLLOCK_Pos  (2U)
#define DDRPHYC_PIR_DLLLOCK_Msk  (0x1U << DDRPHYC_PIR_DLLLOCK_Pos)  /*!< 0x00000004 */
#define DDRPHYC_PIR_DLLLOCK      DDRPHYC_PIR_DLLLOCK_Msk            /*!< DLL lock */
#define DDRPHYC_PIR_ZCAL_Pos     (3U)
#define DDRPHYC_PIR_ZCAL_Msk     (0x1U << DDRPHYC_PIR_ZCAL_Pos)     /*!< 0x00000008 */
#define DDRPHYC_PIR_ZCAL         DDRPHYC_PIR_ZCAL_Msk               /*!< Impedance calibration (Driver and ODT) */
#define DDRPHYC_PIR_ITMSRST_Pos  (4U)
#define DDRPHYC_PIR_ITMSRST_Msk  (0x1U << DDRPHYC_PIR_ITMSRST_Pos)  /*!< 0x00000010 */
#define DDRPHYC_PIR_ITMSRST      DDRPHYC_PIR_ITMSRST_Msk            /*!< ITM reset */
#define DDRPHYC_PIR_DRAMRST_Pos  (5U)
#define DDRPHYC_PIR_DRAMRST_Msk  (0x1U << DDRPHYC_PIR_DRAMRST_Pos)  /*!< 0x00000020 */
#define DDRPHYC_PIR_DRAMRST      DDRPHYC_PIR_DRAMRST_Msk            /*!< DRAM reset (DDR3 only) */
#define DDRPHYC_PIR_DRAMINIT_Pos (6U)
#define DDRPHYC_PIR_DRAMINIT_Msk (0x1U << DDRPHYC_PIR_DRAMINIT_Pos) /*!< 0x00000040 */
#define DDRPHYC_PIR_DRAMINIT     DDRPHYC_PIR_DRAMINIT_Msk           /*!< DRAM initialization */
#define DDRPHYC_PIR_QSTRN_Pos    (7U)
#define DDRPHYC_PIR_QSTRN_Msk    (0x1U << DDRPHYC_PIR_QSTRN_Pos)    /*!< 0x00000080 */
#define DDRPHYC_PIR_QSTRN        DDRPHYC_PIR_QSTRN_Msk              /*!< Read DQS training */
#define DDRPHYC_PIR_RVTRN_Pos    (8U)
#define DDRPHYC_PIR_RVTRN_Msk    (0x1U << DDRPHYC_PIR_RVTRN_Pos)    /*!< 0x00000100 */
#define DDRPHYC_PIR_RVTRN        DDRPHYC_PIR_RVTRN_Msk              /*!< Read DQS gate training DQSTRN) and RV training (RVTRN) should normally be run */
#define DDRPHYC_PIR_ICPC_Pos     (16U)
#define DDRPHYC_PIR_ICPC_Msk     (0x1U << DDRPHYC_PIR_ICPC_Pos)     /*!< 0x00010000 */
#define DDRPHYC_PIR_ICPC         DDRPHYC_PIR_ICPC_Msk               /*!< Initialization complete pin configuration */
#define DDRPHYC_PIR_DLLBYP_Pos   (17U)
#define DDRPHYC_PIR_DLLBYP_Msk   (0x1U << DDRPHYC_PIR_DLLBYP_Pos)   /*!< 0x00020000 */
#define DDRPHYC_PIR_DLLBYP       DDRPHYC_PIR_DLLBYP_Msk             /*!< DLL bypass */
#define DDRPHYC_PIR_CTLDINIT_Pos (18U)
#define DDRPHYC_PIR_CTLDINIT_Msk (0x1U << DDRPHYC_PIR_CTLDINIT_Pos) /*!< 0x00040000 */
#define DDRPHYC_PIR_CTLDINIT     DDRPHYC_PIR_CTLDINIT_Msk           /*!< Controller DRAM initialization */
#define DDRPHYC_PIR_CLRSR_Pos    (28U)
#define DDRPHYC_PIR_CLRSR_Msk    (0x1U << DDRPHYC_PIR_CLRSR_Pos)    /*!< 0x10000000 */
#define DDRPHYC_PIR_CLRSR        DDRPHYC_PIR_CLRSR_Msk              /*!< clear status register */
#define DDRPHYC_PIR_LOCKBYP_Pos  (29U)
#define DDRPHYC_PIR_LOCKBYP_Msk  (0x1U << DDRPHYC_PIR_LOCKBYP_Pos)  /*!< 0x20000000 */
#define DDRPHYC_PIR_LOCKBYP      DDRPHYC_PIR_LOCKBYP_Msk            /*!< DLL lock bypass */
#define DDRPHYC_PIR_ZCALBYP_Pos  (30U)
#define DDRPHYC_PIR_ZCALBYP_Msk  (0x1U << DDRPHYC_PIR_ZCALBYP_Pos)  /*!< 0x40000000 */
#define DDRPHYC_PIR_ZCALBYP      DDRPHYC_PIR_ZCALBYP_Msk            /*!< zcal bypass */
#define DDRPHYC_PIR_INITBYP_Pos  (31U)
#define DDRPHYC_PIR_INITBYP_Msk  (0x1U << DDRPHYC_PIR_INITBYP_Pos)  /*!< 0x80000000 */
#define DDRPHYC_PIR_INITBYP      DDRPHYC_PIR_INITBYP_Msk            /*!< Initialization bypass */

/*****************  Bit definition for DDRPHYC_PGCR register  *****************/
#define DDRPHYC_PGCR_ITMDMD_Pos  (0U)
#define DDRPHYC_PGCR_ITMDMD_Msk  (0x1U << DDRPHYC_PGCR_ITMDMD_Pos)  /*!< 0x00000001 */
#define DDRPHYC_PGCR_ITMDMD      DDRPHYC_PGCR_ITMDMD_Msk            /*!< ITM DDR mode */
#define DDRPHYC_PGCR_DQSCFG_Pos  (1U)
#define DDRPHYC_PGCR_DQSCFG_Msk  (0x1U << DDRPHYC_PGCR_DQSCFG_Pos)  /*!< 0x00000002 */
#define DDRPHYC_PGCR_DQSCFG      DDRPHYC_PGCR_DQSCFG_Msk            /*!< DQS gating configuration */
#define DDRPHYC_PGCR_DFTCMP_Pos  (2U)
#define DDRPHYC_PGCR_DFTCMP_Msk  (0x1U << DDRPHYC_PGCR_DFTCMP_Pos)  /*!< 0x00000004 */
#define DDRPHYC_PGCR_DFTCMP      DDRPHYC_PGCR_DFTCMP_Msk            /*!< DQS drift compensation */
#define DDRPHYC_PGCR_DFTLMT_Pos  (3U)
#define DDRPHYC_PGCR_DFTLMT_Msk  (0x3U << DDRPHYC_PGCR_DFTLMT_Pos)  /*!< 0x00000018 */
#define DDRPHYC_PGCR_DFTLMT      DDRPHYC_PGCR_DFTLMT_Msk            /*!< DQS drift limit */
#define DDRPHYC_PGCR_DFTLMT_0    (0x1U << DDRPHYC_PGCR_DFTLMT_Pos)  /*!< 0x00000008 */
#define DDRPHYC_PGCR_DFTLMT_1    (0x2U << DDRPHYC_PGCR_DFTLMT_Pos)  /*!< 0x00000010 */
#define DDRPHYC_PGCR_DTOSEL_Pos  (5U)
#define DDRPHYC_PGCR_DTOSEL_Msk  (0xFU << DDRPHYC_PGCR_DTOSEL_Pos)  /*!< 0x000001E0 */
#define DDRPHYC_PGCR_DTOSEL      DDRPHYC_PGCR_DTOSEL_Msk            /*!< Digital test output select */
#define DDRPHYC_PGCR_DTOSEL_0    (0x1U << DDRPHYC_PGCR_DTOSEL_Pos)  /*!< 0x00000020 */
#define DDRPHYC_PGCR_DTOSEL_1    (0x2U << DDRPHYC_PGCR_DTOSEL_Pos)  /*!< 0x00000040 */
#define DDRPHYC_PGCR_DTOSEL_2    (0x4U << DDRPHYC_PGCR_DTOSEL_Pos)  /*!< 0x00000080 */
#define DDRPHYC_PGCR_DTOSEL_3    (0x8U << DDRPHYC_PGCR_DTOSEL_Pos)  /*!< 0x00000100 */
#define DDRPHYC_PGCR_CKEN_Pos    (9U)
#define DDRPHYC_PGCR_CKEN_Msk    (0x7U << DDRPHYC_PGCR_CKEN_Pos)    /*!< 0x00000E00 */
#define DDRPHYC_PGCR_CKEN        DDRPHYC_PGCR_CKEN_Msk              /*!< CK enable */
#define DDRPHYC_PGCR_CKEN_0      (0x1U << DDRPHYC_PGCR_CKEN_Pos)    /*!< 0x00000200 */
#define DDRPHYC_PGCR_CKEN_1      (0x2U << DDRPHYC_PGCR_CKEN_Pos)    /*!< 0x00000400 */
#define DDRPHYC_PGCR_CKEN_2      (0x4U << DDRPHYC_PGCR_CKEN_Pos)    /*!< 0x00000800 */
#define DDRPHYC_PGCR_CKDV_Pos    (12U)
#define DDRPHYC_PGCR_CKDV_Msk    (0x3U << DDRPHYC_PGCR_CKDV_Pos)    /*!< 0x00003000 */
#define DDRPHYC_PGCR_CKDV        DDRPHYC_PGCR_CKDV_Msk              /*!< CK disable value */
#define DDRPHYC_PGCR_CKDV_0      (0x1U << DDRPHYC_PGCR_CKDV_Pos)    /*!< 0x00001000 */
#define DDRPHYC_PGCR_CKDV_1      (0x2U << DDRPHYC_PGCR_CKDV_Pos)    /*!< 0x00002000 */
#define DDRPHYC_PGCR_CKINV_Pos   (14U)
#define DDRPHYC_PGCR_CKINV_Msk   (0x1U << DDRPHYC_PGCR_CKINV_Pos)   /*!< 0x00004000 */
#define DDRPHYC_PGCR_CKINV       DDRPHYC_PGCR_CKINV_Msk             /*!< CK invert */
#define DDRPHYC_PGCR_IOLB_Pos    (15U)
#define DDRPHYC_PGCR_IOLB_Msk    (0x1U << DDRPHYC_PGCR_IOLB_Pos)    /*!< 0x00008000 */
#define DDRPHYC_PGCR_IOLB        DDRPHYC_PGCR_IOLB_Msk              /*!< I/O loop back select */
#define DDRPHYC_PGCR_IODDRM_Pos  (16U)
#define DDRPHYC_PGCR_IODDRM_Msk  (0x3U << DDRPHYC_PGCR_IODDRM_Pos)  /*!< 0x00030000 */
#define DDRPHYC_PGCR_IODDRM      DDRPHYC_PGCR_IODDRM_Msk            /*!< I/O DDR mode */
#define DDRPHYC_PGCR_IODDRM_0    (0x1U << DDRPHYC_PGCR_IODDRM_Pos)  /*!< 0x00010000 */
#define DDRPHYC_PGCR_IODDRM_1    (0x2U << DDRPHYC_PGCR_IODDRM_Pos)  /*!< 0x00020000 */
#define DDRPHYC_PGCR_RANKEN_Pos  (18U)
#define DDRPHYC_PGCR_RANKEN_Msk  (0xFU << DDRPHYC_PGCR_RANKEN_Pos)  /*!< 0x003C0000 */
#define DDRPHYC_PGCR_RANKEN      DDRPHYC_PGCR_RANKEN_Msk            /*!< Rank enable */
#define DDRPHYC_PGCR_RANKEN_0    (0x1U << DDRPHYC_PGCR_RANKEN_Pos)  /*!< 0x00040000 */
#define DDRPHYC_PGCR_RANKEN_1    (0x2U << DDRPHYC_PGCR_RANKEN_Pos)  /*!< 0x00080000 */
#define DDRPHYC_PGCR_RANKEN_2    (0x4U << DDRPHYC_PGCR_RANKEN_Pos)  /*!< 0x00100000 */
#define DDRPHYC_PGCR_RANKEN_3    (0x8U << DDRPHYC_PGCR_RANKEN_Pos)  /*!< 0x00200000 */
#define DDRPHYC_PGCR_ZKSEL_Pos   (22U)
#define DDRPHYC_PGCR_ZKSEL_Msk   (0x3U << DDRPHYC_PGCR_ZKSEL_Pos)   /*!< 0x00C00000 */
#define DDRPHYC_PGCR_ZKSEL       DDRPHYC_PGCR_ZKSEL_Msk             /*!< Impedance clock divider selection */
#define DDRPHYC_PGCR_ZKSEL_0     (0x1U << DDRPHYC_PGCR_ZKSEL_Pos)   /*!< 0x00400000 */
#define DDRPHYC_PGCR_ZKSEL_1     (0x2U << DDRPHYC_PGCR_ZKSEL_Pos)   /*!< 0x00800000 */
#define DDRPHYC_PGCR_PDDISDX_Pos (24U)
#define DDRPHYC_PGCR_PDDISDX_Msk (0x1U << DDRPHYC_PGCR_PDDISDX_Pos) /*!< 0x01000000 */
#define DDRPHYC_PGCR_PDDISDX     DDRPHYC_PGCR_PDDISDX_Msk           /*!< Power down disabled byte */
#define DDRPHYC_PGCR_RFSHDT_Pos  (25U)
#define DDRPHYC_PGCR_RFSHDT_Msk  (0xFU << DDRPHYC_PGCR_RFSHDT_Pos)  /*!< 0x1E000000 */
#define DDRPHYC_PGCR_RFSHDT      DDRPHYC_PGCR_RFSHDT_Msk            /*!< Refresh during training */
#define DDRPHYC_PGCR_RFSHDT_0    (0x1U << DDRPHYC_PGCR_RFSHDT_Pos)  /*!< 0x02000000 */
#define DDRPHYC_PGCR_RFSHDT_1    (0x2U << DDRPHYC_PGCR_RFSHDT_Pos)  /*!< 0x04000000 */
#define DDRPHYC_PGCR_RFSHDT_2    (0x4U << DDRPHYC_PGCR_RFSHDT_Pos)  /*!< 0x08000000 */
#define DDRPHYC_PGCR_RFSHDT_3    (0x8U << DDRPHYC_PGCR_RFSHDT_Pos)  /*!< 0x10000000 */
#define DDRPHYC_PGCR_LBDQSS_Pos  (29U)
#define DDRPHYC_PGCR_LBDQSS_Msk  (0x1U << DDRPHYC_PGCR_LBDQSS_Pos)  /*!< 0x20000000 */
#define DDRPHYC_PGCR_LBDQSS      DDRPHYC_PGCR_LBDQSS_Msk            /*!< Loop back DQS shift */
#define DDRPHYC_PGCR_LBGDQS_Pos  (30U)
#define DDRPHYC_PGCR_LBGDQS_Msk  (0x1U << DDRPHYC_PGCR_LBGDQS_Pos)  /*!< 0x40000000 */
#define DDRPHYC_PGCR_LBGDQS      DDRPHYC_PGCR_LBGDQS_Msk            /*!< Loop back DQS gating */
#define DDRPHYC_PGCR_LBMODE_Pos  (31U)
#define DDRPHYC_PGCR_LBMODE_Msk  (0x1U << DDRPHYC_PGCR_LBMODE_Pos)  /*!< 0x80000000 */
#define DDRPHYC_PGCR_LBMODE      DDRPHYC_PGCR_LBMODE_Msk            /*!< Loop back mode */

/*****************  Bit definition for DDRPHYC_PGSR register  *****************/
#define DDRPHYC_PGSR_IDONE_Pos   (0U)
#define DDRPHYC_PGSR_IDONE_Msk   (0x1U << DDRPHYC_PGSR_IDONE_Pos)   /*!< 0x00000001 */
#define DDRPHYC_PGSR_IDONE       DDRPHYC_PGSR_IDONE_Msk             /*!< Initialization done */
#define DDRPHYC_PGSR_DLDONE_Pos  (1U)
#define DDRPHYC_PGSR_DLDONE_Msk  (0x1U << DDRPHYC_PGSR_DLDONE_Pos)  /*!< 0x00000002 */
#define DDRPHYC_PGSR_DLDONE      DDRPHYC_PGSR_DLDONE_Msk            /*!< DLL lock done */
#define DDRPHYC_PGSR_ZCDDONE_Pos (2U)
#define DDRPHYC_PGSR_ZCDDONE_Msk (0x1U << DDRPHYC_PGSR_ZCDDONE_Pos) /*!< 0x00000004 */
#define DDRPHYC_PGSR_ZCDDONE     DDRPHYC_PGSR_ZCDDONE_Msk           /*!< zcal done */
#define DDRPHYC_PGSR_DIDONE_Pos  (3U)
#define DDRPHYC_PGSR_DIDONE_Msk  (0x1U << DDRPHYC_PGSR_DIDONE_Pos)  /*!< 0x00000008 */
#define DDRPHYC_PGSR_DIDONE      DDRPHYC_PGSR_DIDONE_Msk            /*!< DRAM initialization done */
#define DDRPHYC_PGSR_DTDONE_Pos  (4U)
#define DDRPHYC_PGSR_DTDONE_Msk  (0x1U << DDRPHYC_PGSR_DTDONE_Pos)  /*!< 0x00000010 */
#define DDRPHYC_PGSR_DTDONE      DDRPHYC_PGSR_DTDONE_Msk            /*!< Data training done */
#define DDRPHYC_PGSR_DTERR_Pos   (5U)
#define DDRPHYC_PGSR_DTERR_Msk   (0x1U << DDRPHYC_PGSR_DTERR_Pos)   /*!< 0x00000020 */
#define DDRPHYC_PGSR_DTERR       DDRPHYC_PGSR_DTERR_Msk             /*!< DQS gate training error */
#define DDRPHYC_PGSR_DTIERR_Pos  (6U)
#define DDRPHYC_PGSR_DTIERR_Msk  (0x1U << DDRPHYC_PGSR_DTIERR_Pos)  /*!< 0x00000040 */
#define DDRPHYC_PGSR_DTIERR      DDRPHYC_PGSR_DTIERR_Msk            /*!< DQS gate training intermittent error */
#define DDRPHYC_PGSR_DFTERR_Pos  (7U)
#define DDRPHYC_PGSR_DFTERR_Msk  (0x1U << DDRPHYC_PGSR_DFTERR_Pos)  /*!< 0x00000080 */
#define DDRPHYC_PGSR_DFTERR      DDRPHYC_PGSR_DFTERR_Msk            /*!< DQS drift error */
#define DDRPHYC_PGSR_RVERR_Pos   (8U)
#define DDRPHYC_PGSR_RVERR_Msk   (0x1U << DDRPHYC_PGSR_RVERR_Pos)   /*!< 0x00000100 */
#define DDRPHYC_PGSR_RVERR       DDRPHYC_PGSR_RVERR_Msk             /*!< Read valid training error */
#define DDRPHYC_PGSR_RVEIRR_Pos  (9U)
#define DDRPHYC_PGSR_RVEIRR_Msk  (0x1U << DDRPHYC_PGSR_RVEIRR_Pos)  /*!< 0x00000200 */
#define DDRPHYC_PGSR_RVEIRR      DDRPHYC_PGSR_RVEIRR_Msk            /*!< Read valid training intermittent error */
#define DDRPHYC_PGSR_TQ_Pos      (31U)
#define DDRPHYC_PGSR_TQ_Msk      (0x1U << DDRPHYC_PGSR_TQ_Pos)      /*!< 0x80000000 */
#define DDRPHYC_PGSR_TQ          DDRPHYC_PGSR_TQ_Msk                /*!< Temperature output (LPDDR only) N/A */

/****************  Bit definition for DDRPHYC_DLLGCR register  ****************/
#define DDRPHYC_DLLGCR_DRES_Pos     (0U)
#define DDRPHYC_DLLGCR_DRES_Msk     (0x3U << DDRPHYC_DLLGCR_DRES_Pos)     /*!< 0x00000003 */
#define DDRPHYC_DLLGCR_DRES         DDRPHYC_DLLGCR_DRES_Msk               /*!< Trim reference current versus resistor value variation */
#define DDRPHYC_DLLGCR_DRES_0       (0x1U << DDRPHYC_DLLGCR_DRES_Pos)     /*!< 0x00000001 */
#define DDRPHYC_DLLGCR_DRES_1       (0x2U << DDRPHYC_DLLGCR_DRES_Pos)     /*!< 0x00000002 */
#define DDRPHYC_DLLGCR_IPUMP_Pos    (2U)
#define DDRPHYC_DLLGCR_IPUMP_Msk    (0x7U << DDRPHYC_DLLGCR_IPUMP_Pos)    /*!< 0x0000001C */
#define DDRPHYC_DLLGCR_IPUMP        DDRPHYC_DLLGCR_IPUMP_Msk              /*!< Charge pump current trim */
#define DDRPHYC_DLLGCR_IPUMP_0      (0x1U << DDRPHYC_DLLGCR_IPUMP_Pos)    /*!< 0x00000004 */
#define DDRPHYC_DLLGCR_IPUMP_1      (0x2U << DDRPHYC_DLLGCR_IPUMP_Pos)    /*!< 0x00000008 */
#define DDRPHYC_DLLGCR_IPUMP_2      (0x4U << DDRPHYC_DLLGCR_IPUMP_Pos)    /*!< 0x00000010 */
#define DDRPHYC_DLLGCR_TESTEN_Pos   (5U)
#define DDRPHYC_DLLGCR_TESTEN_Msk   (0x1U << DDRPHYC_DLLGCR_TESTEN_Pos)   /*!< 0x00000020 */
#define DDRPHYC_DLLGCR_TESTEN       DDRPHYC_DLLGCR_TESTEN_Msk             /*!< Test enable */
#define DDRPHYC_DLLGCR_DTC_Pos      (6U)
#define DDRPHYC_DLLGCR_DTC_Msk      (0x7U << DDRPHYC_DLLGCR_DTC_Pos)      /*!< 0x000001C0 */
#define DDRPHYC_DLLGCR_DTC          DDRPHYC_DLLGCR_DTC_Msk                /*!< Digital test control */
#define DDRPHYC_DLLGCR_DTC_0        (0x1U << DDRPHYC_DLLGCR_DTC_Pos)      /*!< 0x00000040 */
#define DDRPHYC_DLLGCR_DTC_1        (0x2U << DDRPHYC_DLLGCR_DTC_Pos)      /*!< 0x00000080 */
#define DDRPHYC_DLLGCR_DTC_2        (0x4U << DDRPHYC_DLLGCR_DTC_Pos)      /*!< 0x00000100 */
#define DDRPHYC_DLLGCR_ATC_Pos      (9U)
#define DDRPHYC_DLLGCR_ATC_Msk      (0x3U << DDRPHYC_DLLGCR_ATC_Pos)      /*!< 0x00000600 */
#define DDRPHYC_DLLGCR_ATC          DDRPHYC_DLLGCR_ATC_Msk                /*!< Analog test control */
#define DDRPHYC_DLLGCR_ATC_0        (0x1U << DDRPHYC_DLLGCR_ATC_Pos)      /*!< 0x00000200 */
#define DDRPHYC_DLLGCR_ATC_1        (0x2U << DDRPHYC_DLLGCR_ATC_Pos)      /*!< 0x00000400 */
#define DDRPHYC_DLLGCR_TESTSW_Pos   (11U)
#define DDRPHYC_DLLGCR_TESTSW_Msk   (0x1U << DDRPHYC_DLLGCR_TESTSW_Pos)   /*!< 0x00000800 */
#define DDRPHYC_DLLGCR_TESTSW       DDRPHYC_DLLGCR_TESTSW_Msk             /*!< Test switch */
#define DDRPHYC_DLLGCR_MBIAS_Pos    (12U)
#define DDRPHYC_DLLGCR_MBIAS_Msk    (0xFFU << DDRPHYC_DLLGCR_MBIAS_Pos)   /*!< 0x000FF000 */
#define DDRPHYC_DLLGCR_MBIAS        DDRPHYC_DLLGCR_MBIAS_Msk              /*!< Master bias trim */
#define DDRPHYC_DLLGCR_MBIAS_0      (0x1U << DDRPHYC_DLLGCR_MBIAS_Pos)    /*!< 0x00001000 */
#define DDRPHYC_DLLGCR_MBIAS_1      (0x2U << DDRPHYC_DLLGCR_MBIAS_Pos)    /*!< 0x00002000 */
#define DDRPHYC_DLLGCR_MBIAS_2      (0x4U << DDRPHYC_DLLGCR_MBIAS_Pos)    /*!< 0x00004000 */
#define DDRPHYC_DLLGCR_MBIAS_3      (0x8U << DDRPHYC_DLLGCR_MBIAS_Pos)    /*!< 0x00008000 */
#define DDRPHYC_DLLGCR_MBIAS_4      (0x10U << DDRPHYC_DLLGCR_MBIAS_Pos)   /*!< 0x00010000 */
#define DDRPHYC_DLLGCR_MBIAS_5      (0x20U << DDRPHYC_DLLGCR_MBIAS_Pos)   /*!< 0x00020000 */
#define DDRPHYC_DLLGCR_MBIAS_6      (0x40U << DDRPHYC_DLLGCR_MBIAS_Pos)   /*!< 0x00040000 */
#define DDRPHYC_DLLGCR_MBIAS_7      (0x80U << DDRPHYC_DLLGCR_MBIAS_Pos)   /*!< 0x00080000 */
#define DDRPHYC_DLLGCR_SBIAS2_0_Pos (20U)
#define DDRPHYC_DLLGCR_SBIAS2_0_Msk (0x7U << DDRPHYC_DLLGCR_SBIAS2_0_Pos) /*!< 0x00700000 */
#define DDRPHYC_DLLGCR_SBIAS2_0     DDRPHYC_DLLGCR_SBIAS2_0_Msk           /*!< Slave bias trim */
#define DDRPHYC_DLLGCR_SBIAS2_0_0   (0x1U << DDRPHYC_DLLGCR_SBIAS2_0_Pos) /*!< 0x00100000 */
#define DDRPHYC_DLLGCR_SBIAS2_0_1   (0x2U << DDRPHYC_DLLGCR_SBIAS2_0_Pos) /*!< 0x00200000 */
#define DDRPHYC_DLLGCR_SBIAS2_0_2   (0x4U << DDRPHYC_DLLGCR_SBIAS2_0_Pos) /*!< 0x00400000 */
#define DDRPHYC_DLLGCR_BPS200_Pos   (23U)
#define DDRPHYC_DLLGCR_BPS200_Msk   (0x1U << DDRPHYC_DLLGCR_BPS200_Pos)   /*!< 0x00800000 */
#define DDRPHYC_DLLGCR_BPS200       DDRPHYC_DLLGCR_BPS200_Msk             /*!< Bypass mode frequency range */
#define DDRPHYC_DLLGCR_SBIAS5_3_Pos (24U)
#define DDRPHYC_DLLGCR_SBIAS5_3_Msk (0x7U << DDRPHYC_DLLGCR_SBIAS5_3_Pos) /*!< 0x07000000 */
#define DDRPHYC_DLLGCR_SBIAS5_3     DDRPHYC_DLLGCR_SBIAS5_3_Msk           /*!< Slave bias trim */
#define DDRPHYC_DLLGCR_SBIAS5_3_0   (0x1U << DDRPHYC_DLLGCR_SBIAS5_3_Pos) /*!< 0x01000000 */
#define DDRPHYC_DLLGCR_SBIAS5_3_1   (0x2U << DDRPHYC_DLLGCR_SBIAS5_3_Pos) /*!< 0x02000000 */
#define DDRPHYC_DLLGCR_SBIAS5_3_2   (0x4U << DDRPHYC_DLLGCR_SBIAS5_3_Pos) /*!< 0x04000000 */
#define DDRPHYC_DLLGCR_FDTRMSL_Pos  (27U)
#define DDRPHYC_DLLGCR_FDTRMSL_Msk  (0x3U << DDRPHYC_DLLGCR_FDTRMSL_Pos)  /*!< 0x18000000 */
#define DDRPHYC_DLLGCR_FDTRMSL      DDRPHYC_DLLGCR_FDTRMSL_Msk            /*!< Slave bypass fixed delay trim */
#define DDRPHYC_DLLGCR_FDTRMSL_0    (0x1U << DDRPHYC_DLLGCR_FDTRMSL_Pos)  /*!< 0x08000000 */
#define DDRPHYC_DLLGCR_FDTRMSL_1    (0x2U << DDRPHYC_DLLGCR_FDTRMSL_Pos)  /*!< 0x10000000 */
#define DDRPHYC_DLLGCR_LOCKDET_Pos  (29U)
#define DDRPHYC_DLLGCR_LOCKDET_Msk  (0x1U << DDRPHYC_DLLGCR_LOCKDET_Pos)  /*!< 0x20000000 */
#define DDRPHYC_DLLGCR_LOCKDET      DDRPHYC_DLLGCR_LOCKDET_Msk            /*!< Master lock detect enable */
#define DDRPHYC_DLLGCR_DLLRSVD2_Pos (30U)
#define DDRPHYC_DLLGCR_DLLRSVD2_Msk (0x3U << DDRPHYC_DLLGCR_DLLRSVD2_Pos) /*!< 0xC0000000 */
#define DDRPHYC_DLLGCR_DLLRSVD2     DDRPHYC_DLLGCR_DLLRSVD2_Msk           /*!< These bit are connected to the DLL control bus and reserved for future use. */
#define DDRPHYC_DLLGCR_DLLRSVD2_0   (0x1U << DDRPHYC_DLLGCR_DLLRSVD2_Pos) /*!< 0x40000000 */
#define DDRPHYC_DLLGCR_DLLRSVD2_1   (0x2U << DDRPHYC_DLLGCR_DLLRSVD2_Pos) /*!< 0x80000000 */

/***************  Bit definition for DDRPHYC_ACDLLCR register  ****************/
#define DDRPHYC_ACDLLCR_MFBDLY_Pos  (6U)
#define DDRPHYC_ACDLLCR_MFBDLY_Msk  (0x7U << DDRPHYC_ACDLLCR_MFBDLY_Pos)  /*!< 0x000001C0 */
#define DDRPHYC_ACDLLCR_MFBDLY      DDRPHYC_ACDLLCR_MFBDLY_Msk            /*!< Master DLL feed-back delay trim */
#define DDRPHYC_ACDLLCR_MFBDLY_0    (0x1U << DDRPHYC_ACDLLCR_MFBDLY_Pos)  /*!< 0x00000040 */
#define DDRPHYC_ACDLLCR_MFBDLY_1    (0x2U << DDRPHYC_ACDLLCR_MFBDLY_Pos)  /*!< 0x00000080 */
#define DDRPHYC_ACDLLCR_MFBDLY_2    (0x4U << DDRPHYC_ACDLLCR_MFBDLY_Pos)  /*!< 0x00000100 */
#define DDRPHYC_ACDLLCR_MFWDLY_Pos  (9U)
#define DDRPHYC_ACDLLCR_MFWDLY_Msk  (0x7U << DDRPHYC_ACDLLCR_MFWDLY_Pos)  /*!< 0x00000E00 */
#define DDRPHYC_ACDLLCR_MFWDLY      DDRPHYC_ACDLLCR_MFWDLY_Msk            /*!< Master DLL feed-forward delay trim */
#define DDRPHYC_ACDLLCR_MFWDLY_0    (0x1U << DDRPHYC_ACDLLCR_MFWDLY_Pos)  /*!< 0x00000200 */
#define DDRPHYC_ACDLLCR_MFWDLY_1    (0x2U << DDRPHYC_ACDLLCR_MFWDLY_Pos)  /*!< 0x00000400 */
#define DDRPHYC_ACDLLCR_MFWDLY_2    (0x4U << DDRPHYC_ACDLLCR_MFWDLY_Pos)  /*!< 0x00000800 */
#define DDRPHYC_ACDLLCR_ATESTEN_Pos (18U)
#define DDRPHYC_ACDLLCR_ATESTEN_Msk (0x1U << DDRPHYC_ACDLLCR_ATESTEN_Pos) /*!< 0x00040000 */
#define DDRPHYC_ACDLLCR_ATESTEN     DDRPHYC_ACDLLCR_ATESTEN_Msk           /*!< Analog test enable */
#define DDRPHYC_ACDLLCR_DLLSRST_Pos (30U)
#define DDRPHYC_ACDLLCR_DLLSRST_Msk (0x1U << DDRPHYC_ACDLLCR_DLLSRST_Pos) /*!< 0x40000000 */
#define DDRPHYC_ACDLLCR_DLLSRST     DDRPHYC_ACDLLCR_DLLSRST_Msk           /*!< DLL soft reset */
#define DDRPHYC_ACDLLCR_DLLDIS_Pos  (31U)
#define DDRPHYC_ACDLLCR_DLLDIS_Msk  (0x1U << DDRPHYC_ACDLLCR_DLLDIS_Pos)  /*!< 0x80000000 */
#define DDRPHYC_ACDLLCR_DLLDIS      DDRPHYC_ACDLLCR_DLLDIS_Msk            /*!< DLL disable */

/*****************  Bit definition for DDRPHYC_PTR0 register  *****************/
#define DDRPHYC_PTR0_TDLLSRST_Pos (0U)
#define DDRPHYC_PTR0_TDLLSRST_Msk (0x3FU << DDRPHYC_PTR0_TDLLSRST_Pos)  /*!< 0x0000003F */
#define DDRPHYC_PTR0_TDLLSRST     DDRPHYC_PTR0_TDLLSRST_Msk             /*!< DLL soft reset */
#define DDRPHYC_PTR0_TDLLSRST_0   (0x1U << DDRPHYC_PTR0_TDLLSRST_Pos)   /*!< 0x00000001 */
#define DDRPHYC_PTR0_TDLLSRST_1   (0x2U << DDRPHYC_PTR0_TDLLSRST_Pos)   /*!< 0x00000002 */
#define DDRPHYC_PTR0_TDLLSRST_2   (0x4U << DDRPHYC_PTR0_TDLLSRST_Pos)   /*!< 0x00000004 */
#define DDRPHYC_PTR0_TDLLSRST_3   (0x8U << DDRPHYC_PTR0_TDLLSRST_Pos)   /*!< 0x00000008 */
#define DDRPHYC_PTR0_TDLLSRST_4   (0x10U << DDRPHYC_PTR0_TDLLSRST_Pos)  /*!< 0x00000010 */
#define DDRPHYC_PTR0_TDLLSRST_5   (0x20U << DDRPHYC_PTR0_TDLLSRST_Pos)  /*!< 0x00000020 */
#define DDRPHYC_PTR0_TDLLLOCK_Pos (6U)
#define DDRPHYC_PTR0_TDLLLOCK_Msk (0xFFFU << DDRPHYC_PTR0_TDLLLOCK_Pos) /*!< 0x0003FFC0 */
#define DDRPHYC_PTR0_TDLLLOCK     DDRPHYC_PTR0_TDLLLOCK_Msk             /*!< DLL lock time */
#define DDRPHYC_PTR0_TDLLLOCK_0   (0x1U << DDRPHYC_PTR0_TDLLLOCK_Pos)   /*!< 0x00000040 */
#define DDRPHYC_PTR0_TDLLLOCK_1   (0x2U << DDRPHYC_PTR0_TDLLLOCK_Pos)   /*!< 0x00000080 */
#define DDRPHYC_PTR0_TDLLLOCK_2   (0x4U << DDRPHYC_PTR0_TDLLLOCK_Pos)   /*!< 0x00000100 */
#define DDRPHYC_PTR0_TDLLLOCK_3   (0x8U << DDRPHYC_PTR0_TDLLLOCK_Pos)   /*!< 0x00000200 */
#define DDRPHYC_PTR0_TDLLLOCK_4   (0x10U << DDRPHYC_PTR0_TDLLLOCK_Pos)  /*!< 0x00000400 */
#define DDRPHYC_PTR0_TDLLLOCK_5   (0x20U << DDRPHYC_PTR0_TDLLLOCK_Pos)  /*!< 0x00000800 */
#define DDRPHYC_PTR0_TDLLLOCK_6   (0x40U << DDRPHYC_PTR0_TDLLLOCK_Pos)  /*!< 0x00001000 */
#define DDRPHYC_PTR0_TDLLLOCK_7   (0x80U << DDRPHYC_PTR0_TDLLLOCK_Pos)  /*!< 0x00002000 */
#define DDRPHYC_PTR0_TDLLLOCK_8   (0x100U << DDRPHYC_PTR0_TDLLLOCK_Pos) /*!< 0x00004000 */
#define DDRPHYC_PTR0_TDLLLOCK_9   (0x200U << DDRPHYC_PTR0_TDLLLOCK_Pos) /*!< 0x00008000 */
#define DDRPHYC_PTR0_TDLLLOCK_10  (0x400U << DDRPHYC_PTR0_TDLLLOCK_Pos) /*!< 0x00010000 */
#define DDRPHYC_PTR0_TDLLLOCK_11  (0x800U << DDRPHYC_PTR0_TDLLLOCK_Pos) /*!< 0x00020000 */
#define DDRPHYC_PTR0_TITMSRST_Pos (18U)
#define DDRPHYC_PTR0_TITMSRST_Msk (0xFU << DDRPHYC_PTR0_TITMSRST_Pos)   /*!< 0x003C0000 */
#define DDRPHYC_PTR0_TITMSRST     DDRPHYC_PTR0_TITMSRST_Msk             /*!< ITM soft reset */
#define DDRPHYC_PTR0_TITMSRST_0   (0x1U << DDRPHYC_PTR0_TITMSRST_Pos)   /*!< 0x00040000 */
#define DDRPHYC_PTR0_TITMSRST_1   (0x2U << DDRPHYC_PTR0_TITMSRST_Pos)   /*!< 0x00080000 */
#define DDRPHYC_PTR0_TITMSRST_2   (0x4U << DDRPHYC_PTR0_TITMSRST_Pos)   /*!< 0x00100000 */
#define DDRPHYC_PTR0_TITMSRST_3   (0x8U << DDRPHYC_PTR0_TITMSRST_Pos)   /*!< 0x00200000 */

/*****************  Bit definition for DDRPHYC_PTR1 register  *****************/
#define DDRPHYC_PTR1_TDINIT0_Pos (0U)
#define DDRPHYC_PTR1_TDINIT0_Msk (0x7FFFFU << DDRPHYC_PTR1_TDINIT0_Pos) /*!< 0x0007FFFF */
#define DDRPHYC_PTR1_TDINIT0     DDRPHYC_PTR1_TDINIT0_Msk               /*!< tDINIT0 */
#define DDRPHYC_PTR1_TDINIT0_0   (0x1U << DDRPHYC_PTR1_TDINIT0_Pos)     /*!< 0x00000001 */
#define DDRPHYC_PTR1_TDINIT0_1   (0x2U << DDRPHYC_PTR1_TDINIT0_Pos)     /*!< 0x00000002 */
#define DDRPHYC_PTR1_TDINIT0_2   (0x4U << DDRPHYC_PTR1_TDINIT0_Pos)     /*!< 0x00000004 */
#define DDRPHYC_PTR1_TDINIT0_3   (0x8U << DDRPHYC_PTR1_TDINIT0_Pos)     /*!< 0x00000008 */
#define DDRPHYC_PTR1_TDINIT0_4   (0x10U << DDRPHYC_PTR1_TDINIT0_Pos)    /*!< 0x00000010 */
#define DDRPHYC_PTR1_TDINIT0_5   (0x20U << DDRPHYC_PTR1_TDINIT0_Pos)    /*!< 0x00000020 */
#define DDRPHYC_PTR1_TDINIT0_6   (0x40U << DDRPHYC_PTR1_TDINIT0_Pos)    /*!< 0x00000040 */
#define DDRPHYC_PTR1_TDINIT0_7   (0x80U << DDRPHYC_PTR1_TDINIT0_Pos)    /*!< 0x00000080 */
#define DDRPHYC_PTR1_TDINIT0_8   (0x100U << DDRPHYC_PTR1_TDINIT0_Pos)   /*!< 0x00000100 */
#define DDRPHYC_PTR1_TDINIT0_9   (0x200U << DDRPHYC_PTR1_TDINIT0_Pos)   /*!< 0x00000200 */
#define DDRPHYC_PTR1_TDINIT0_10  (0x400U << DDRPHYC_PTR1_TDINIT0_Pos)   /*!< 0x00000400 */
#define DDRPHYC_PTR1_TDINIT0_11  (0x800U << DDRPHYC_PTR1_TDINIT0_Pos)   /*!< 0x00000800 */
#define DDRPHYC_PTR1_TDINIT0_12  (0x1000U << DDRPHYC_PTR1_TDINIT0_Pos)  /*!< 0x00001000 */
#define DDRPHYC_PTR1_TDINIT0_13  (0x2000U << DDRPHYC_PTR1_TDINIT0_Pos)  /*!< 0x00002000 */
#define DDRPHYC_PTR1_TDINIT0_14  (0x4000U << DDRPHYC_PTR1_TDINIT0_Pos)  /*!< 0x00004000 */
#define DDRPHYC_PTR1_TDINIT0_15  (0x8000U << DDRPHYC_PTR1_TDINIT0_Pos)  /*!< 0x00008000 */
#define DDRPHYC_PTR1_TDINIT0_16  (0x10000U << DDRPHYC_PTR1_TDINIT0_Pos) /*!< 0x00010000 */
#define DDRPHYC_PTR1_TDINIT0_17  (0x20000U << DDRPHYC_PTR1_TDINIT0_Pos) /*!< 0x00020000 */
#define DDRPHYC_PTR1_TDINIT0_18  (0x40000U << DDRPHYC_PTR1_TDINIT0_Pos) /*!< 0x00040000 */
#define DDRPHYC_PTR1_TDINIT1_Pos (19U)
#define DDRPHYC_PTR1_TDINIT1_Msk (0xFFU << DDRPHYC_PTR1_TDINIT1_Pos)    /*!< 0x07F80000 */
#define DDRPHYC_PTR1_TDINIT1     DDRPHYC_PTR1_TDINIT1_Msk               /*!< tDINIT1 */
#define DDRPHYC_PTR1_TDINIT1_0   (0x1U << DDRPHYC_PTR1_TDINIT1_Pos)     /*!< 0x00080000 */
#define DDRPHYC_PTR1_TDINIT1_1   (0x2U << DDRPHYC_PTR1_TDINIT1_Pos)     /*!< 0x00100000 */
#define DDRPHYC_PTR1_TDINIT1_2   (0x4U << DDRPHYC_PTR1_TDINIT1_Pos)     /*!< 0x00200000 */
#define DDRPHYC_PTR1_TDINIT1_3   (0x8U << DDRPHYC_PTR1_TDINIT1_Pos)     /*!< 0x00400000 */
#define DDRPHYC_PTR1_TDINIT1_4   (0x10U << DDRPHYC_PTR1_TDINIT1_Pos)    /*!< 0x00800000 */
#define DDRPHYC_PTR1_TDINIT1_5   (0x20U << DDRPHYC_PTR1_TDINIT1_Pos)    /*!< 0x01000000 */
#define DDRPHYC_PTR1_TDINIT1_6   (0x40U << DDRPHYC_PTR1_TDINIT1_Pos)    /*!< 0x02000000 */
#define DDRPHYC_PTR1_TDINIT1_7   (0x80U << DDRPHYC_PTR1_TDINIT1_Pos)    /*!< 0x04000000 */

/*****************  Bit definition for DDRPHYC_PTR2 register  *****************/
#define DDRPHYC_PTR2_TDINIT2_Pos (0U)
#define DDRPHYC_PTR2_TDINIT2_Msk (0x1FFFFU << DDRPHYC_PTR2_TDINIT2_Pos) /*!< 0x0001FFFF */
#define DDRPHYC_PTR2_TDINIT2     DDRPHYC_PTR2_TDINIT2_Msk               /*!< tDINIT2 */
#define DDRPHYC_PTR2_TDINIT2_0   (0x1U << DDRPHYC_PTR2_TDINIT2_Pos)     /*!< 0x00000001 */
#define DDRPHYC_PTR2_TDINIT2_1   (0x2U << DDRPHYC_PTR2_TDINIT2_Pos)     /*!< 0x00000002 */
#define DDRPHYC_PTR2_TDINIT2_2   (0x4U << DDRPHYC_PTR2_TDINIT2_Pos)     /*!< 0x00000004 */
#define DDRPHYC_PTR2_TDINIT2_3   (0x8U << DDRPHYC_PTR2_TDINIT2_Pos)     /*!< 0x00000008 */
#define DDRPHYC_PTR2_TDINIT2_4   (0x10U << DDRPHYC_PTR2_TDINIT2_Pos)    /*!< 0x00000010 */
#define DDRPHYC_PTR2_TDINIT2_5   (0x20U << DDRPHYC_PTR2_TDINIT2_Pos)    /*!< 0x00000020 */
#define DDRPHYC_PTR2_TDINIT2_6   (0x40U << DDRPHYC_PTR2_TDINIT2_Pos)    /*!< 0x00000040 */
#define DDRPHYC_PTR2_TDINIT2_7   (0x80U << DDRPHYC_PTR2_TDINIT2_Pos)    /*!< 0x00000080 */
#define DDRPHYC_PTR2_TDINIT2_8   (0x100U << DDRPHYC_PTR2_TDINIT2_Pos)   /*!< 0x00000100 */
#define DDRPHYC_PTR2_TDINIT2_9   (0x200U << DDRPHYC_PTR2_TDINIT2_Pos)   /*!< 0x00000200 */
#define DDRPHYC_PTR2_TDINIT2_10  (0x400U << DDRPHYC_PTR2_TDINIT2_Pos)   /*!< 0x00000400 */
#define DDRPHYC_PTR2_TDINIT2_11  (0x800U << DDRPHYC_PTR2_TDINIT2_Pos)   /*!< 0x00000800 */
#define DDRPHYC_PTR2_TDINIT2_12  (0x1000U << DDRPHYC_PTR2_TDINIT2_Pos)  /*!< 0x00001000 */
#define DDRPHYC_PTR2_TDINIT2_13  (0x2000U << DDRPHYC_PTR2_TDINIT2_Pos)  /*!< 0x00002000 */
#define DDRPHYC_PTR2_TDINIT2_14  (0x4000U << DDRPHYC_PTR2_TDINIT2_Pos)  /*!< 0x00004000 */
#define DDRPHYC_PTR2_TDINIT2_15  (0x8000U << DDRPHYC_PTR2_TDINIT2_Pos)  /*!< 0x00008000 */
#define DDRPHYC_PTR2_TDINIT2_16  (0x10000U << DDRPHYC_PTR2_TDINIT2_Pos) /*!< 0x00010000 */
#define DDRPHYC_PTR2_TDINIT3_Pos (17U)
#define DDRPHYC_PTR2_TDINIT3_Msk (0x3FFU << DDRPHYC_PTR2_TDINIT3_Pos)   /*!< 0x07FE0000 */
#define DDRPHYC_PTR2_TDINIT3     DDRPHYC_PTR2_TDINIT3_Msk               /*!< tDINIT3 */
#define DDRPHYC_PTR2_TDINIT3_0   (0x1U << DDRPHYC_PTR2_TDINIT3_Pos)     /*!< 0x00020000 */
#define DDRPHYC_PTR2_TDINIT3_1   (0x2U << DDRPHYC_PTR2_TDINIT3_Pos)     /*!< 0x00040000 */
#define DDRPHYC_PTR2_TDINIT3_2   (0x4U << DDRPHYC_PTR2_TDINIT3_Pos)     /*!< 0x00080000 */
#define DDRPHYC_PTR2_TDINIT3_3   (0x8U << DDRPHYC_PTR2_TDINIT3_Pos)     /*!< 0x00100000 */
#define DDRPHYC_PTR2_TDINIT3_4   (0x10U << DDRPHYC_PTR2_TDINIT3_Pos)    /*!< 0x00200000 */
#define DDRPHYC_PTR2_TDINIT3_5   (0x20U << DDRPHYC_PTR2_TDINIT3_Pos)    /*!< 0x00400000 */
#define DDRPHYC_PTR2_TDINIT3_6   (0x40U << DDRPHYC_PTR2_TDINIT3_Pos)    /*!< 0x00800000 */
#define DDRPHYC_PTR2_TDINIT3_7   (0x80U << DDRPHYC_PTR2_TDINIT3_Pos)    /*!< 0x01000000 */
#define DDRPHYC_PTR2_TDINIT3_8   (0x100U << DDRPHYC_PTR2_TDINIT3_Pos)   /*!< 0x02000000 */
#define DDRPHYC_PTR2_TDINIT3_9   (0x200U << DDRPHYC_PTR2_TDINIT3_Pos)   /*!< 0x04000000 */

/****************  Bit definition for DDRPHYC_ACIOCR register  ****************/
#define DDRPHYC_ACIOCR_ACIOM_Pos   (0U)
#define DDRPHYC_ACIOCR_ACIOM_Msk   (0x1U << DDRPHYC_ACIOCR_ACIOM_Pos)   /*!< 0x00000001 */
#define DDRPHYC_ACIOCR_ACIOM       DDRPHYC_ACIOCR_ACIOM_Msk             /*!< AC pins I/O mode */
#define DDRPHYC_ACIOCR_ACOE_Pos    (1U)
#define DDRPHYC_ACIOCR_ACOE_Msk    (0x1U << DDRPHYC_ACIOCR_ACOE_Pos)    /*!< 0x00000002 */
#define DDRPHYC_ACIOCR_ACOE        DDRPHYC_ACIOCR_ACOE_Msk              /*!< AC pins output enable */
#define DDRPHYC_ACIOCR_ACODT_Pos   (2U)
#define DDRPHYC_ACIOCR_ACODT_Msk   (0x1U << DDRPHYC_ACIOCR_ACODT_Pos)   /*!< 0x00000004 */
#define DDRPHYC_ACIOCR_ACODT       DDRPHYC_ACIOCR_ACODT_Msk             /*!< AC pins ODT */
#define DDRPHYC_ACIOCR_ACPDD_Pos   (3U)
#define DDRPHYC_ACIOCR_ACPDD_Msk   (0x1U << DDRPHYC_ACIOCR_ACPDD_Pos)   /*!< 0x00000008 */
#define DDRPHYC_ACIOCR_ACPDD       DDRPHYC_ACIOCR_ACPDD_Msk             /*!< AC pins power down drivers */
#define DDRPHYC_ACIOCR_ACPDR_Pos   (4U)
#define DDRPHYC_ACIOCR_ACPDR_Msk   (0x1U << DDRPHYC_ACIOCR_ACPDR_Pos)   /*!< 0x00000010 */
#define DDRPHYC_ACIOCR_ACPDR       DDRPHYC_ACIOCR_ACPDR_Msk             /*!< AC pins power down receivers */
#define DDRPHYC_ACIOCR_CKODT_Pos   (5U)
#define DDRPHYC_ACIOCR_CKODT_Msk   (0x7U << DDRPHYC_ACIOCR_CKODT_Pos)   /*!< 0x000000E0 */
#define DDRPHYC_ACIOCR_CKODT       DDRPHYC_ACIOCR_CKODT_Msk             /*!< CK pin ODT */
#define DDRPHYC_ACIOCR_CKODT_0     (0x1U << DDRPHYC_ACIOCR_CKODT_Pos)   /*!< 0x00000020 */
#define DDRPHYC_ACIOCR_CKODT_1     (0x2U << DDRPHYC_ACIOCR_CKODT_Pos)   /*!< 0x00000040 */
#define DDRPHYC_ACIOCR_CKODT_2     (0x4U << DDRPHYC_ACIOCR_CKODT_Pos)   /*!< 0x00000080 */
#define DDRPHYC_ACIOCR_CKPDD_Pos   (8U)
#define DDRPHYC_ACIOCR_CKPDD_Msk   (0x7U << DDRPHYC_ACIOCR_CKPDD_Pos)   /*!< 0x00000700 */
#define DDRPHYC_ACIOCR_CKPDD       DDRPHYC_ACIOCR_CKPDD_Msk             /*!< CK pin power down driver */
#define DDRPHYC_ACIOCR_CKPDD_0     (0x1U << DDRPHYC_ACIOCR_CKPDD_Pos)   /*!< 0x00000100 */
#define DDRPHYC_ACIOCR_CKPDD_1     (0x2U << DDRPHYC_ACIOCR_CKPDD_Pos)   /*!< 0x00000200 */
#define DDRPHYC_ACIOCR_CKPDD_2     (0x4U << DDRPHYC_ACIOCR_CKPDD_Pos)   /*!< 0x00000400 */
#define DDRPHYC_ACIOCR_CKPDR_Pos   (11U)
#define DDRPHYC_ACIOCR_CKPDR_Msk   (0x7U << DDRPHYC_ACIOCR_CKPDR_Pos)   /*!< 0x00003800 */
#define DDRPHYC_ACIOCR_CKPDR       DDRPHYC_ACIOCR_CKPDR_Msk             /*!< CK pin power down receiver */
#define DDRPHYC_ACIOCR_CKPDR_0     (0x1U << DDRPHYC_ACIOCR_CKPDR_Pos)   /*!< 0x00000800 */
#define DDRPHYC_ACIOCR_CKPDR_1     (0x2U << DDRPHYC_ACIOCR_CKPDR_Pos)   /*!< 0x00001000 */
#define DDRPHYC_ACIOCR_CKPDR_2     (0x4U << DDRPHYC_ACIOCR_CKPDR_Pos)   /*!< 0x00002000 */
#define DDRPHYC_ACIOCR_RANKODT_Pos (14U)
#define DDRPHYC_ACIOCR_RANKODT_Msk (0x1U << DDRPHYC_ACIOCR_RANKODT_Pos) /*!< 0x00004000 */
#define DDRPHYC_ACIOCR_RANKODT     DDRPHYC_ACIOCR_RANKODT_Msk           /*!< Rank ODT */
#define DDRPHYC_ACIOCR_CSPDD_Pos   (18U)
#define DDRPHYC_ACIOCR_CSPDD_Msk   (0x1U << DDRPHYC_ACIOCR_CSPDD_Pos)   /*!< 0x00040000 */
#define DDRPHYC_ACIOCR_CSPDD       DDRPHYC_ACIOCR_CSPDD_Msk             /*!< CS power down driver */
#define DDRPHYC_ACIOCR_RANKPDR_Pos (22U)
#define DDRPHYC_ACIOCR_RANKPDR_Msk (0x1U << DDRPHYC_ACIOCR_RANKPDR_Pos) /*!< 0x00400000 */
#define DDRPHYC_ACIOCR_RANKPDR     DDRPHYC_ACIOCR_RANKPDR_Msk           /*!< Rank power down receiver */
#define DDRPHYC_ACIOCR_RSTODT_Pos  (26U)
#define DDRPHYC_ACIOCR_RSTODT_Msk  (0x1U << DDRPHYC_ACIOCR_RSTODT_Pos)  /*!< 0x04000000 */
#define DDRPHYC_ACIOCR_RSTODT      DDRPHYC_ACIOCR_RSTODT_Msk            /*!< RST pin ODT */
#define DDRPHYC_ACIOCR_RSTPDD_Pos  (27U)
#define DDRPHYC_ACIOCR_RSTPDD_Msk  (0x1U << DDRPHYC_ACIOCR_RSTPDD_Pos)  /*!< 0x08000000 */
#define DDRPHYC_ACIOCR_RSTPDD      DDRPHYC_ACIOCR_RSTPDD_Msk            /*!< RST pin power down driver */
#define DDRPHYC_ACIOCR_RSTPDR_Pos  (28U)
#define DDRPHYC_ACIOCR_RSTPDR_Msk  (0x1U << DDRPHYC_ACIOCR_RSTPDR_Pos)  /*!< 0x10000000 */
#define DDRPHYC_ACIOCR_RSTPDR      DDRPHYC_ACIOCR_RSTPDR_Msk            /*!< RST pin power down receiver */
#define DDRPHYC_ACIOCR_RSTIOM_Pos  (29U)
#define DDRPHYC_ACIOCR_RSTIOM_Msk  (0x1U << DDRPHYC_ACIOCR_RSTIOM_Pos)  /*!< 0x20000000 */
#define DDRPHYC_ACIOCR_RSTIOM      DDRPHYC_ACIOCR_RSTIOM_Msk            /*!< Reset I/O mode */
#define DDRPHYC_ACIOCR_ACSR_Pos    (30U)
#define DDRPHYC_ACIOCR_ACSR_Msk    (0x3U << DDRPHYC_ACIOCR_ACSR_Pos)    /*!< 0xC0000000 */
#define DDRPHYC_ACIOCR_ACSR        DDRPHYC_ACIOCR_ACSR_Msk              /*!< AC slew rate */
#define DDRPHYC_ACIOCR_ACSR_0      (0x1U << DDRPHYC_ACIOCR_ACSR_Pos)    /*!< 0x40000000 */
#define DDRPHYC_ACIOCR_ACSR_1      (0x2U << DDRPHYC_ACIOCR_ACSR_Pos)    /*!< 0x80000000 */

/****************  Bit definition for DDRPHYC_DXCCR register  *****************/
#define DDRPHYC_DXCCR_DXODT_Pos   (0U)
#define DDRPHYC_DXCCR_DXODT_Msk   (0x1U << DDRPHYC_DXCCR_DXODT_Pos)   /*!< 0x00000001 */
#define DDRPHYC_DXCCR_DXODT       DDRPHYC_DXCCR_DXODT_Msk             /*!< Data on die termination */
#define DDRPHYC_DXCCR_DXIOM_Pos   (1U)
#define DDRPHYC_DXCCR_DXIOM_Msk   (0x1U << DDRPHYC_DXCCR_DXIOM_Pos)   /*!< 0x00000002 */
#define DDRPHYC_DXCCR_DXIOM       DDRPHYC_DXCCR_DXIOM_Msk             /*!< Data I/O mode */
#define DDRPHYC_DXCCR_DXPDD_Pos   (2U)
#define DDRPHYC_DXCCR_DXPDD_Msk   (0x1U << DDRPHYC_DXCCR_DXPDD_Pos)   /*!< 0x00000004 */
#define DDRPHYC_DXCCR_DXPDD       DDRPHYC_DXCCR_DXPDD_Msk             /*!< Data power down driver */
#define DDRPHYC_DXCCR_DXPDR_Pos   (3U)
#define DDRPHYC_DXCCR_DXPDR_Msk   (0x1U << DDRPHYC_DXCCR_DXPDR_Pos)   /*!< 0x00000008 */
#define DDRPHYC_DXCCR_DXPDR       DDRPHYC_DXCCR_DXPDR_Msk             /*!< Data power down receiver */
#define DDRPHYC_DXCCR_DQSRES_Pos  (4U)
#define DDRPHYC_DXCCR_DQSRES_Msk  (0xFU << DDRPHYC_DXCCR_DQSRES_Pos)  /*!< 0x000000F0 */
#define DDRPHYC_DXCCR_DQSRES      DDRPHYC_DXCCR_DQSRES_Msk            /*!< DQS resistor */
#define DDRPHYC_DXCCR_DQSRES_0    (0x1U << DDRPHYC_DXCCR_DQSRES_Pos)  /*!< 0x00000010 */
#define DDRPHYC_DXCCR_DQSRES_1    (0x2U << DDRPHYC_DXCCR_DQSRES_Pos)  /*!< 0x00000020 */
#define DDRPHYC_DXCCR_DQSRES_2    (0x4U << DDRPHYC_DXCCR_DQSRES_Pos)  /*!< 0x00000040 */
#define DDRPHYC_DXCCR_DQSRES_3    (0x8U << DDRPHYC_DXCCR_DQSRES_Pos)  /*!< 0x00000080 */
#define DDRPHYC_DXCCR_DQSNRES_Pos (8U)
#define DDRPHYC_DXCCR_DQSNRES_Msk (0xFU << DDRPHYC_DXCCR_DQSNRES_Pos) /*!< 0x00000F00 */
#define DDRPHYC_DXCCR_DQSNRES     DDRPHYC_DXCCR_DQSNRES_Msk           /*!< DQS# resistor */
#define DDRPHYC_DXCCR_DQSNRES_0   (0x1U << DDRPHYC_DXCCR_DQSNRES_Pos) /*!< 0x00000100 */
#define DDRPHYC_DXCCR_DQSNRES_1   (0x2U << DDRPHYC_DXCCR_DQSNRES_Pos) /*!< 0x00000200 */
#define DDRPHYC_DXCCR_DQSNRES_2   (0x4U << DDRPHYC_DXCCR_DQSNRES_Pos) /*!< 0x00000400 */
#define DDRPHYC_DXCCR_DQSNRES_3   (0x8U << DDRPHYC_DXCCR_DQSNRES_Pos) /*!< 0x00000800 */
#define DDRPHYC_DXCCR_DQSNRST_Pos (14U)
#define DDRPHYC_DXCCR_DQSNRST_Msk (0x1U << DDRPHYC_DXCCR_DQSNRST_Pos) /*!< 0x00004000 */
#define DDRPHYC_DXCCR_DQSNRST     DDRPHYC_DXCCR_DQSNRST_Msk           /*!< DQS reset */
#define DDRPHYC_DXCCR_RVSEL_Pos   (15U)
#define DDRPHYC_DXCCR_RVSEL_Msk   (0x1U << DDRPHYC_DXCCR_RVSEL_Pos)   /*!< 0x00008000 */
#define DDRPHYC_DXCCR_RVSEL       DDRPHYC_DXCCR_RVSEL_Msk             /*!< ITMD read valid select */
#define DDRPHYC_DXCCR_AWDT_Pos    (16U)
#define DDRPHYC_DXCCR_AWDT_Msk    (0x1U << DDRPHYC_DXCCR_AWDT_Pos)    /*!< 0x00010000 */
#define DDRPHYC_DXCCR_AWDT        DDRPHYC_DXCCR_AWDT_Msk              /*!< Active window data train */

/****************  Bit definition for DDRPHYC_DSGCR register  *****************/
#define DDRPHYC_DSGCR_PUREN_Pos   (0U)
#define DDRPHYC_DSGCR_PUREN_Msk   (0x1U << DDRPHYC_DSGCR_PUREN_Pos)   /*!< 0x00000001 */
#define DDRPHYC_DSGCR_PUREN       DDRPHYC_DSGCR_PUREN_Msk             /*!< PHY update request enable */
#define DDRPHYC_DSGCR_BDISEN_Pos  (1U)
#define DDRPHYC_DSGCR_BDISEN_Msk  (0x1U << DDRPHYC_DSGCR_BDISEN_Pos)  /*!< 0x00000002 */
#define DDRPHYC_DSGCR_BDISEN      DDRPHYC_DSGCR_BDISEN_Msk            /*!< Byte disable enable */
#define DDRPHYC_DSGCR_ZUEN_Pos    (2U)
#define DDRPHYC_DSGCR_ZUEN_Msk    (0x1U << DDRPHYC_DSGCR_ZUEN_Pos)    /*!< 0x00000004 */
#define DDRPHYC_DSGCR_ZUEN        DDRPHYC_DSGCR_ZUEN_Msk              /*!< zcal on DFI update request */
#define DDRPHYC_DSGCR_LPIOPD_Pos  (3U)
#define DDRPHYC_DSGCR_LPIOPD_Msk  (0x1U << DDRPHYC_DSGCR_LPIOPD_Pos)  /*!< 0x00000008 */
#define DDRPHYC_DSGCR_LPIOPD      DDRPHYC_DSGCR_LPIOPD_Msk            /*!< Low power I/O power down */
#define DDRPHYC_DSGCR_LPDLLPD_Pos (4U)
#define DDRPHYC_DSGCR_LPDLLPD_Msk (0x1U << DDRPHYC_DSGCR_LPDLLPD_Pos) /*!< 0x00000010 */
#define DDRPHYC_DSGCR_LPDLLPD     DDRPHYC_DSGCR_LPDLLPD_Msk           /*!< Low power DLL power down */
#define DDRPHYC_DSGCR_DQSGX_Pos   (5U)
#define DDRPHYC_DSGCR_DQSGX_Msk   (0x7U << DDRPHYC_DSGCR_DQSGX_Pos)   /*!< 0x000000E0 */
#define DDRPHYC_DSGCR_DQSGX       DDRPHYC_DSGCR_DQSGX_Msk             /*!< DQS gate extension */
#define DDRPHYC_DSGCR_DQSGX_0     (0x1U << DDRPHYC_DSGCR_DQSGX_Pos)   /*!< 0x00000020 */
#define DDRPHYC_DSGCR_DQSGX_1     (0x2U << DDRPHYC_DSGCR_DQSGX_Pos)   /*!< 0x00000040 */
#define DDRPHYC_DSGCR_DQSGX_2     (0x4U << DDRPHYC_DSGCR_DQSGX_Pos)   /*!< 0x00000080 */
#define DDRPHYC_DSGCR_DQSGE_Pos   (8U)
#define DDRPHYC_DSGCR_DQSGE_Msk   (0x7U << DDRPHYC_DSGCR_DQSGE_Pos)   /*!< 0x00000700 */
#define DDRPHYC_DSGCR_DQSGE       DDRPHYC_DSGCR_DQSGE_Msk             /*!< DQS gate early */
#define DDRPHYC_DSGCR_DQSGE_0     (0x1U << DDRPHYC_DSGCR_DQSGE_Pos)   /*!< 0x00000100 */
#define DDRPHYC_DSGCR_DQSGE_1     (0x2U << DDRPHYC_DSGCR_DQSGE_Pos)   /*!< 0x00000200 */
#define DDRPHYC_DSGCR_DQSGE_2     (0x4U << DDRPHYC_DSGCR_DQSGE_Pos)   /*!< 0x00000400 */
#define DDRPHYC_DSGCR_NOBUB_Pos   (11U)
#define DDRPHYC_DSGCR_NOBUB_Msk   (0x1U << DDRPHYC_DSGCR_NOBUB_Pos)   /*!< 0x00000800 */
#define DDRPHYC_DSGCR_NOBUB       DDRPHYC_DSGCR_NOBUB_Msk             /*!< No bubble */
#define DDRPHYC_DSGCR_FXDLAT_Pos  (12U)
#define DDRPHYC_DSGCR_FXDLAT_Msk  (0x1U << DDRPHYC_DSGCR_FXDLAT_Pos)  /*!< 0x00001000 */
#define DDRPHYC_DSGCR_FXDLAT      DDRPHYC_DSGCR_FXDLAT_Msk            /*!< Fixed latency */
#define DDRPHYC_DSGCR_CKEPDD_Pos  (16U)
#define DDRPHYC_DSGCR_CKEPDD_Msk  (0x1U << DDRPHYC_DSGCR_CKEPDD_Pos)  /*!< 0x00010000 */
#define DDRPHYC_DSGCR_CKEPDD      DDRPHYC_DSGCR_CKEPDD_Msk            /*!< CKE power down driver */
#define DDRPHYC_DSGCR_ODTPDD_Pos  (20U)
#define DDRPHYC_DSGCR_ODTPDD_Msk  (0x1U << DDRPHYC_DSGCR_ODTPDD_Pos)  /*!< 0x00100000 */
#define DDRPHYC_DSGCR_ODTPDD      DDRPHYC_DSGCR_ODTPDD_Msk            /*!< ODT power down driver */
#define DDRPHYC_DSGCR_NL2PD_Pos   (24U)
#define DDRPHYC_DSGCR_NL2PD_Msk   (0x1U << DDRPHYC_DSGCR_NL2PD_Pos)   /*!< 0x01000000 */
#define DDRPHYC_DSGCR_NL2PD       DDRPHYC_DSGCR_NL2PD_Msk             /*!< Non LPDDR2 power down */
#define DDRPHYC_DSGCR_NL2OE_Pos   (25U)
#define DDRPHYC_DSGCR_NL2OE_Msk   (0x1U << DDRPHYC_DSGCR_NL2OE_Pos)   /*!< 0x02000000 */
#define DDRPHYC_DSGCR_NL2OE       DDRPHYC_DSGCR_NL2OE_Msk             /*!< Non LPDDR2 output enable */
#define DDRPHYC_DSGCR_TPDPD_Pos   (26U)
#define DDRPHYC_DSGCR_TPDPD_Msk   (0x1U << DDRPHYC_DSGCR_TPDPD_Pos)   /*!< 0x04000000 */
#define DDRPHYC_DSGCR_TPDPD       DDRPHYC_DSGCR_TPDPD_Msk             /*!< TPD power down driver (N/A LPDDR only) */
#define DDRPHYC_DSGCR_TPDOE_Pos   (27U)
#define DDRPHYC_DSGCR_TPDOE_Msk   (0x1U << DDRPHYC_DSGCR_TPDOE_Pos)   /*!< 0x08000000 */
#define DDRPHYC_DSGCR_TPDOE       DDRPHYC_DSGCR_TPDOE_Msk             /*!< TPD output enable (N/A LPDDR only) */
#define DDRPHYC_DSGCR_CKOE_Pos    (28U)
#define DDRPHYC_DSGCR_CKOE_Msk    (0x1U << DDRPHYC_DSGCR_CKOE_Pos)    /*!< 0x10000000 */
#define DDRPHYC_DSGCR_CKOE        DDRPHYC_DSGCR_CKOE_Msk              /*!< CK output enable */
#define DDRPHYC_DSGCR_ODTOE_Pos   (29U)
#define DDRPHYC_DSGCR_ODTOE_Msk   (0x1U << DDRPHYC_DSGCR_ODTOE_Pos)   /*!< 0x20000000 */
#define DDRPHYC_DSGCR_ODTOE       DDRPHYC_DSGCR_ODTOE_Msk             /*!< ODT output enable */
#define DDRPHYC_DSGCR_RSTOE_Pos   (30U)
#define DDRPHYC_DSGCR_RSTOE_Msk   (0x1U << DDRPHYC_DSGCR_RSTOE_Pos)   /*!< 0x40000000 */
#define DDRPHYC_DSGCR_RSTOE       DDRPHYC_DSGCR_RSTOE_Msk             /*!< RST output enable */
#define DDRPHYC_DSGCR_CKEOE_Pos   (31U)
#define DDRPHYC_DSGCR_CKEOE_Msk   (0x1U << DDRPHYC_DSGCR_CKEOE_Pos)   /*!< 0x80000000 */
#define DDRPHYC_DSGCR_CKEOE       DDRPHYC_DSGCR_CKEOE_Msk             /*!< CKE output enable */

/*****************  Bit definition for DDRPHYC_DCR register  ******************/
#define DDRPHYC_DCR_DDRMD_Pos   (0U)
#define DDRPHYC_DCR_DDRMD_Msk   (0x7U << DDRPHYC_DCR_DDRMD_Pos)   /*!< 0x00000007 */
#define DDRPHYC_DCR_DDRMD       DDRPHYC_DCR_DDRMD_Msk             /*!< SDRAM DDR mode */
#define DDRPHYC_DCR_DDRMD_0     (0x1U << DDRPHYC_DCR_DDRMD_Pos)   /*!< 0x00000001 */
#define DDRPHYC_DCR_DDRMD_1     (0x2U << DDRPHYC_DCR_DDRMD_Pos)   /*!< 0x00000002 */
#define DDRPHYC_DCR_DDRMD_2     (0x4U << DDRPHYC_DCR_DDRMD_Pos)   /*!< 0x00000004 */
#define DDRPHYC_DCR_DDR8BNK_Pos (3U)
#define DDRPHYC_DCR_DDR8BNK_Msk (0x1U << DDRPHYC_DCR_DDR8BNK_Pos) /*!< 0x00000008 */
#define DDRPHYC_DCR_DDR8BNK     DDRPHYC_DCR_DDR8BNK_Msk           /*!< DDR 8 banks */
#define DDRPHYC_DCR_PDQ_Pos     (4U)
#define DDRPHYC_DCR_PDQ_Msk     (0x7U << DDRPHYC_DCR_PDQ_Pos)     /*!< 0x00000070 */
#define DDRPHYC_DCR_PDQ         DDRPHYC_DCR_PDQ_Msk               /*!< Primary DQ(DDR3 Only) */
#define DDRPHYC_DCR_PDQ_0       (0x1U << DDRPHYC_DCR_PDQ_Pos)     /*!< 0x00000010 */
#define DDRPHYC_DCR_PDQ_1       (0x2U << DDRPHYC_DCR_PDQ_Pos)     /*!< 0x00000020 */
#define DDRPHYC_DCR_PDQ_2       (0x4U << DDRPHYC_DCR_PDQ_Pos)     /*!< 0x00000040 */
#define DDRPHYC_DCR_MPRDQ_Pos   (7U)
#define DDRPHYC_DCR_MPRDQ_Msk   (0x1U << DDRPHYC_DCR_MPRDQ_Pos)   /*!< 0x00000080 */
#define DDRPHYC_DCR_MPRDQ       DDRPHYC_DCR_MPRDQ_Msk             /*!< MPR DQ */
#define DDRPHYC_DCR_DDRTYPE_Pos (8U)
#define DDRPHYC_DCR_DDRTYPE_Msk (0x3U << DDRPHYC_DCR_DDRTYPE_Pos) /*!< 0x00000300 */
#define DDRPHYC_DCR_DDRTYPE     DDRPHYC_DCR_DDRTYPE_Msk           /*!< DDR type (LPDDR2 S4) */
#define DDRPHYC_DCR_DDRTYPE_0   (0x1U << DDRPHYC_DCR_DDRTYPE_Pos) /*!< 0x00000100 */
#define DDRPHYC_DCR_DDRTYPE_1   (0x2U << DDRPHYC_DCR_DDRTYPE_Pos) /*!< 0x00000200 */
#define DDRPHYC_DCR_NOSRA_Pos   (27U)
#define DDRPHYC_DCR_NOSRA_Msk   (0x1U << DDRPHYC_DCR_NOSRA_Pos)   /*!< 0x08000000 */
#define DDRPHYC_DCR_NOSRA       DDRPHYC_DCR_NOSRA_Msk             /*!< No simultaneous rank access */
#define DDRPHYC_DCR_DDR2T_Pos   (28U)
#define DDRPHYC_DCR_DDR2T_Msk   (0x1U << DDRPHYC_DCR_DDR2T_Pos)   /*!< 0x10000000 */
#define DDRPHYC_DCR_DDR2T       DDRPHYC_DCR_DDR2T_Msk             /*!< 2T timing */
#define DDRPHYC_DCR_UDIMM_Pos   (29U)
#define DDRPHYC_DCR_UDIMM_Msk   (0x1U << DDRPHYC_DCR_UDIMM_Pos)   /*!< 0x20000000 */
#define DDRPHYC_DCR_UDIMM       DDRPHYC_DCR_UDIMM_Msk             /*!< Unbuffered DIMM */
#define DDRPHYC_DCR_RDIMM_Pos   (30U)
#define DDRPHYC_DCR_RDIMM_Msk   (0x1U << DDRPHYC_DCR_RDIMM_Pos)   /*!< 0x40000000 */
#define DDRPHYC_DCR_RDIMM       DDRPHYC_DCR_RDIMM_Msk             /*!< Registered DIMM */
#define DDRPHYC_DCR_TPD_Pos     (31U)
#define DDRPHYC_DCR_TPD_Msk     (0x1U << DDRPHYC_DCR_TPD_Pos)     /*!< 0x80000000 */
#define DDRPHYC_DCR_TPD         DDRPHYC_DCR_TPD_Msk               /*!< Test power down (N/A LPDDR only) */

/****************  Bit definition for DDRPHYC_DTPR0 register  *****************/
#define DDRPHYC_DTPR0_TMRD_Pos (0U)
#define DDRPHYC_DTPR0_TMRD_Msk (0x3U << DDRPHYC_DTPR0_TMRD_Pos)  /*!< 0x00000003 */
#define DDRPHYC_DTPR0_TMRD     DDRPHYC_DTPR0_TMRD_Msk            /*!< tMRD */
#define DDRPHYC_DTPR0_TMRD_0   (0x1U << DDRPHYC_DTPR0_TMRD_Pos)  /*!< 0x00000001 */
#define DDRPHYC_DTPR0_TMRD_1   (0x2U << DDRPHYC_DTPR0_TMRD_Pos)  /*!< 0x00000002 */
#define DDRPHYC_DTPR0_TRTP_Pos (2U)
#define DDRPHYC_DTPR0_TRTP_Msk (0x7U << DDRPHYC_DTPR0_TRTP_Pos)  /*!< 0x0000001C */
#define DDRPHYC_DTPR0_TRTP     DDRPHYC_DTPR0_TRTP_Msk            /*!< tRTP */
#define DDRPHYC_DTPR0_TRTP_0   (0x1U << DDRPHYC_DTPR0_TRTP_Pos)  /*!< 0x00000004 */
#define DDRPHYC_DTPR0_TRTP_1   (0x2U << DDRPHYC_DTPR0_TRTP_Pos)  /*!< 0x00000008 */
#define DDRPHYC_DTPR0_TRTP_2   (0x4U << DDRPHYC_DTPR0_TRTP_Pos)  /*!< 0x00000010 */
#define DDRPHYC_DTPR0_TWTR_Pos (5U)
#define DDRPHYC_DTPR0_TWTR_Msk (0x7U << DDRPHYC_DTPR0_TWTR_Pos)  /*!< 0x000000E0 */
#define DDRPHYC_DTPR0_TWTR     DDRPHYC_DTPR0_TWTR_Msk            /*!< tWTR */
#define DDRPHYC_DTPR0_TWTR_0   (0x1U << DDRPHYC_DTPR0_TWTR_Pos)  /*!< 0x00000020 */
#define DDRPHYC_DTPR0_TWTR_1   (0x2U << DDRPHYC_DTPR0_TWTR_Pos)  /*!< 0x00000040 */
#define DDRPHYC_DTPR0_TWTR_2   (0x4U << DDRPHYC_DTPR0_TWTR_Pos)  /*!< 0x00000080 */
#define DDRPHYC_DTPR0_TRP_Pos  (8U)
#define DDRPHYC_DTPR0_TRP_Msk  (0xFU << DDRPHYC_DTPR0_TRP_Pos)   /*!< 0x00000F00 */
#define DDRPHYC_DTPR0_TRP      DDRPHYC_DTPR0_TRP_Msk             /*!< tRP */
#define DDRPHYC_DTPR0_TRP_0    (0x1U << DDRPHYC_DTPR0_TRP_Pos)   /*!< 0x00000100 */
#define DDRPHYC_DTPR0_TRP_1    (0x2U << DDRPHYC_DTPR0_TRP_Pos)   /*!< 0x00000200 */
#define DDRPHYC_DTPR0_TRP_2    (0x4U << DDRPHYC_DTPR0_TRP_Pos)   /*!< 0x00000400 */
#define DDRPHYC_DTPR0_TRP_3    (0x8U << DDRPHYC_DTPR0_TRP_Pos)   /*!< 0x00000800 */
#define DDRPHYC_DTPR0_TRCD_Pos (12U)
#define DDRPHYC_DTPR0_TRCD_Msk (0xFU << DDRPHYC_DTPR0_TRCD_Pos)  /*!< 0x0000F000 */
#define DDRPHYC_DTPR0_TRCD     DDRPHYC_DTPR0_TRCD_Msk            /*!< tRCD */
#define DDRPHYC_DTPR0_TRCD_0   (0x1U << DDRPHYC_DTPR0_TRCD_Pos)  /*!< 0x00001000 */
#define DDRPHYC_DTPR0_TRCD_1   (0x2U << DDRPHYC_DTPR0_TRCD_Pos)  /*!< 0x00002000 */
#define DDRPHYC_DTPR0_TRCD_2   (0x4U << DDRPHYC_DTPR0_TRCD_Pos)  /*!< 0x00004000 */
#define DDRPHYC_DTPR0_TRCD_3   (0x8U << DDRPHYC_DTPR0_TRCD_Pos)  /*!< 0x00008000 */
#define DDRPHYC_DTPR0_TRAS_Pos (16U)
#define DDRPHYC_DTPR0_TRAS_Msk (0x1FU << DDRPHYC_DTPR0_TRAS_Pos) /*!< 0x001F0000 */
#define DDRPHYC_DTPR0_TRAS     DDRPHYC_DTPR0_TRAS_Msk            /*!< tRAS */
#define DDRPHYC_DTPR0_TRAS_0   (0x1U << DDRPHYC_DTPR0_TRAS_Pos)  /*!< 0x00010000 */
#define DDRPHYC_DTPR0_TRAS_1   (0x2U << DDRPHYC_DTPR0_TRAS_Pos)  /*!< 0x00020000 */
#define DDRPHYC_DTPR0_TRAS_2   (0x4U << DDRPHYC_DTPR0_TRAS_Pos)  /*!< 0x00040000 */
#define DDRPHYC_DTPR0_TRAS_3   (0x8U << DDRPHYC_DTPR0_TRAS_Pos)  /*!< 0x00080000 */
#define DDRPHYC_DTPR0_TRAS_4   (0x10U << DDRPHYC_DTPR0_TRAS_Pos) /*!< 0x00100000 */
#define DDRPHYC_DTPR0_TRRD_Pos (21U)
#define DDRPHYC_DTPR0_TRRD_Msk (0xFU << DDRPHYC_DTPR0_TRRD_Pos)  /*!< 0x01E00000 */
#define DDRPHYC_DTPR0_TRRD     DDRPHYC_DTPR0_TRRD_Msk            /*!< tRRD */
#define DDRPHYC_DTPR0_TRRD_0   (0x1U << DDRPHYC_DTPR0_TRRD_Pos)  /*!< 0x00200000 */
#define DDRPHYC_DTPR0_TRRD_1   (0x2U << DDRPHYC_DTPR0_TRRD_Pos)  /*!< 0x00400000 */
#define DDRPHYC_DTPR0_TRRD_2   (0x4U << DDRPHYC_DTPR0_TRRD_Pos)  /*!< 0x00800000 */
#define DDRPHYC_DTPR0_TRRD_3   (0x8U << DDRPHYC_DTPR0_TRRD_Pos)  /*!< 0x01000000 */
#define DDRPHYC_DTPR0_TRC_Pos  (25U)
#define DDRPHYC_DTPR0_TRC_Msk  (0x3FU << DDRPHYC_DTPR0_TRC_Pos)  /*!< 0x7E000000 */
#define DDRPHYC_DTPR0_TRC      DDRPHYC_DTPR0_TRC_Msk             /*!< tRC */
#define DDRPHYC_DTPR0_TRC_0    (0x1U << DDRPHYC_DTPR0_TRC_Pos)   /*!< 0x02000000 */
#define DDRPHYC_DTPR0_TRC_1    (0x2U << DDRPHYC_DTPR0_TRC_Pos)   /*!< 0x04000000 */
#define DDRPHYC_DTPR0_TRC_2    (0x4U << DDRPHYC_DTPR0_TRC_Pos)   /*!< 0x08000000 */
#define DDRPHYC_DTPR0_TRC_3    (0x8U << DDRPHYC_DTPR0_TRC_Pos)   /*!< 0x10000000 */
#define DDRPHYC_DTPR0_TRC_4    (0x10U << DDRPHYC_DTPR0_TRC_Pos)  /*!< 0x20000000 */
#define DDRPHYC_DTPR0_TRC_5    (0x20U << DDRPHYC_DTPR0_TRC_Pos)  /*!< 0x40000000 */
#define DDRPHYC_DTPR0_TCCD_Pos (31U)
#define DDRPHYC_DTPR0_TCCD_Msk (0x1U << DDRPHYC_DTPR0_TCCD_Pos)  /*!< 0x80000000 */
#define DDRPHYC_DTPR0_TCCD     DDRPHYC_DTPR0_TCCD_Msk            /*!< tCCDRead to read and write to write command delay */

/****************  Bit definition for DDRPHYC_DTPR1 register  *****************/
#define DDRPHYC_DTPR1_TAOND_Pos     (0U)
#define DDRPHYC_DTPR1_TAOND_Msk     (0x3U << DDRPHYC_DTPR1_TAOND_Pos)     /*!< 0x00000003 */
#define DDRPHYC_DTPR1_TAOND         DDRPHYC_DTPR1_TAOND_Msk               /*!< tAOND/tAOFD */
#define DDRPHYC_DTPR1_TAOND_0       (0x1U << DDRPHYC_DTPR1_TAOND_Pos)     /*!< 0x00000001 */
#define DDRPHYC_DTPR1_TAOND_1       (0x2U << DDRPHYC_DTPR1_TAOND_Pos)     /*!< 0x00000002 */
#define DDRPHYC_DTPR1_TRTW_Pos      (2U)
#define DDRPHYC_DTPR1_TRTW_Msk      (0x1U << DDRPHYC_DTPR1_TRTW_Pos)      /*!< 0x00000004 */
#define DDRPHYC_DTPR1_TRTW          DDRPHYC_DTPR1_TRTW_Msk                /*!< tRTW */
#define DDRPHYC_DTPR1_TFAW_Pos      (3U)
#define DDRPHYC_DTPR1_TFAW_Msk      (0x3FU << DDRPHYC_DTPR1_TFAW_Pos)     /*!< 0x000001F8 */
#define DDRPHYC_DTPR1_TFAW          DDRPHYC_DTPR1_TFAW_Msk                /*!< tFAW */
#define DDRPHYC_DTPR1_TFAW_0        (0x1U << DDRPHYC_DTPR1_TFAW_Pos)      /*!< 0x00000008 */
#define DDRPHYC_DTPR1_TFAW_1        (0x2U << DDRPHYC_DTPR1_TFAW_Pos)      /*!< 0x00000010 */
#define DDRPHYC_DTPR1_TFAW_2        (0x4U << DDRPHYC_DTPR1_TFAW_Pos)      /*!< 0x00000020 */
#define DDRPHYC_DTPR1_TFAW_3        (0x8U << DDRPHYC_DTPR1_TFAW_Pos)      /*!< 0x00000040 */
#define DDRPHYC_DTPR1_TFAW_4        (0x10U << DDRPHYC_DTPR1_TFAW_Pos)     /*!< 0x00000080 */
#define DDRPHYC_DTPR1_TFAW_5        (0x20U << DDRPHYC_DTPR1_TFAW_Pos)     /*!< 0x00000100 */
#define DDRPHYC_DTPR1_TMOD_Pos      (9U)
#define DDRPHYC_DTPR1_TMOD_Msk      (0x3U << DDRPHYC_DTPR1_TMOD_Pos)      /*!< 0x00000600 */
#define DDRPHYC_DTPR1_TMOD          DDRPHYC_DTPR1_TMOD_Msk                /*!< tMOD */
#define DDRPHYC_DTPR1_TMOD_0        (0x1U << DDRPHYC_DTPR1_TMOD_Pos)      /*!< 0x00000200 */
#define DDRPHYC_DTPR1_TMOD_1        (0x2U << DDRPHYC_DTPR1_TMOD_Pos)      /*!< 0x00000400 */
#define DDRPHYC_DTPR1_TRTODT_Pos    (11U)
#define DDRPHYC_DTPR1_TRTODT_Msk    (0x1U << DDRPHYC_DTPR1_TRTODT_Pos)    /*!< 0x00000800 */
#define DDRPHYC_DTPR1_TRTODT        DDRPHYC_DTPR1_TRTODT_Msk              /*!< tRTODT */
#define DDRPHYC_DTPR1_TRFC_Pos      (16U)
#define DDRPHYC_DTPR1_TRFC_Msk      (0xFFU << DDRPHYC_DTPR1_TRFC_Pos)     /*!< 0x00FF0000 */
#define DDRPHYC_DTPR1_TRFC          DDRPHYC_DTPR1_TRFC_Msk                /*!< tRFC */
#define DDRPHYC_DTPR1_TRFC_0        (0x1U << DDRPHYC_DTPR1_TRFC_Pos)      /*!< 0x00010000 */
#define DDRPHYC_DTPR1_TRFC_1        (0x2U << DDRPHYC_DTPR1_TRFC_Pos)      /*!< 0x00020000 */
#define DDRPHYC_DTPR1_TRFC_2        (0x4U << DDRPHYC_DTPR1_TRFC_Pos)      /*!< 0x00040000 */
#define DDRPHYC_DTPR1_TRFC_3        (0x8U << DDRPHYC_DTPR1_TRFC_Pos)      /*!< 0x00080000 */
#define DDRPHYC_DTPR1_TRFC_4        (0x10U << DDRPHYC_DTPR1_TRFC_Pos)     /*!< 0x00100000 */
#define DDRPHYC_DTPR1_TRFC_5        (0x20U << DDRPHYC_DTPR1_TRFC_Pos)     /*!< 0x00200000 */
#define DDRPHYC_DTPR1_TRFC_6        (0x40U << DDRPHYC_DTPR1_TRFC_Pos)     /*!< 0x00400000 */
#define DDRPHYC_DTPR1_TRFC_7        (0x80U << DDRPHYC_DTPR1_TRFC_Pos)     /*!< 0x00800000 */
#define DDRPHYC_DTPR1_TDQSCKMIN_Pos (24U)
#define DDRPHYC_DTPR1_TDQSCKMIN_Msk (0x7U << DDRPHYC_DTPR1_TDQSCKMIN_Pos) /*!< 0x07000000 */
#define DDRPHYC_DTPR1_TDQSCKMIN     DDRPHYC_DTPR1_TDQSCKMIN_Msk           /*!< tDQSCKmin */
#define DDRPHYC_DTPR1_TDQSCKMIN_0   (0x1U << DDRPHYC_DTPR1_TDQSCKMIN_Pos) /*!< 0x01000000 */
#define DDRPHYC_DTPR1_TDQSCKMIN_1   (0x2U << DDRPHYC_DTPR1_TDQSCKMIN_Pos) /*!< 0x02000000 */
#define DDRPHYC_DTPR1_TDQSCKMIN_2   (0x4U << DDRPHYC_DTPR1_TDQSCKMIN_Pos) /*!< 0x04000000 */
#define DDRPHYC_DTPR1_TDQSCKMAX_Pos (27U)
#define DDRPHYC_DTPR1_TDQSCKMAX_Msk (0x7U << DDRPHYC_DTPR1_TDQSCKMAX_Pos) /*!< 0x38000000 */
#define DDRPHYC_DTPR1_TDQSCKMAX     DDRPHYC_DTPR1_TDQSCKMAX_Msk           /*!< tDQSCKmax */
#define DDRPHYC_DTPR1_TDQSCKMAX_0   (0x1U << DDRPHYC_DTPR1_TDQSCKMAX_Pos) /*!< 0x08000000 */
#define DDRPHYC_DTPR1_TDQSCKMAX_1   (0x2U << DDRPHYC_DTPR1_TDQSCKMAX_Pos) /*!< 0x10000000 */
#define DDRPHYC_DTPR1_TDQSCKMAX_2   (0x4U << DDRPHYC_DTPR1_TDQSCKMAX_Pos) /*!< 0x20000000 */

/****************  Bit definition for DDRPHYC_DTPR2 register  *****************/
#define DDRPHYC_DTPR2_TXS_Pos   (0U)
#define DDRPHYC_DTPR2_TXS_Msk   (0x3FFU << DDRPHYC_DTPR2_TXS_Pos)   /*!< 0x000003FF */
#define DDRPHYC_DTPR2_TXS       DDRPHYC_DTPR2_TXS_Msk               /*!< tXS */
#define DDRPHYC_DTPR2_TXS_0     (0x1U << DDRPHYC_DTPR2_TXS_Pos)     /*!< 0x00000001 */
#define DDRPHYC_DTPR2_TXS_1     (0x2U << DDRPHYC_DTPR2_TXS_Pos)     /*!< 0x00000002 */
#define DDRPHYC_DTPR2_TXS_2     (0x4U << DDRPHYC_DTPR2_TXS_Pos)     /*!< 0x00000004 */
#define DDRPHYC_DTPR2_TXS_3     (0x8U << DDRPHYC_DTPR2_TXS_Pos)     /*!< 0x00000008 */
#define DDRPHYC_DTPR2_TXS_4     (0x10U << DDRPHYC_DTPR2_TXS_Pos)    /*!< 0x00000010 */
#define DDRPHYC_DTPR2_TXS_5     (0x20U << DDRPHYC_DTPR2_TXS_Pos)    /*!< 0x00000020 */
#define DDRPHYC_DTPR2_TXS_6     (0x40U << DDRPHYC_DTPR2_TXS_Pos)    /*!< 0x00000040 */
#define DDRPHYC_DTPR2_TXS_7     (0x80U << DDRPHYC_DTPR2_TXS_Pos)    /*!< 0x00000080 */
#define DDRPHYC_DTPR2_TXS_8     (0x100U << DDRPHYC_DTPR2_TXS_Pos)   /*!< 0x00000100 */
#define DDRPHYC_DTPR2_TXS_9     (0x200U << DDRPHYC_DTPR2_TXS_Pos)   /*!< 0x00000200 */
#define DDRPHYC_DTPR2_TXP_Pos   (10U)                             
#define DDRPHYC_DTPR2_TXP_Msk   (0x1FU << DDRPHYC_DTPR2_TXP_Pos)    /*!< 0x00007C00 */
#define DDRPHYC_DTPR2_TXP       DDRPHYC_DTPR2_TXP_Msk               /*!< tXP */
#define DDRPHYC_DTPR2_TXP_0     (0x1U << DDRPHYC_DTPR2_TXP_Pos)     /*!< 0x00000400 */
#define DDRPHYC_DTPR2_TXP_1     (0x2U << DDRPHYC_DTPR2_TXP_Pos)     /*!< 0x00000800 */
#define DDRPHYC_DTPR2_TXP_2     (0x4U << DDRPHYC_DTPR2_TXP_Pos)     /*!< 0x00001000 */
#define DDRPHYC_DTPR2_TXP_3     (0x8U << DDRPHYC_DTPR2_TXP_Pos)     /*!< 0x00002000 */
#define DDRPHYC_DTPR2_TXP_4     (0x10U << DDRPHYC_DTPR2_TXP_Pos)    /*!< 0x00004000 */
#define DDRPHYC_DTPR2_TCKE_Pos  (15U)                             
#define DDRPHYC_DTPR2_TCKE_Msk  (0xFU << DDRPHYC_DTPR2_TCKE_Pos)    /*!< 0x00078000 */
#define DDRPHYC_DTPR2_TCKE      DDRPHYC_DTPR2_TCKE_Msk              /*!< tCKE */
#define DDRPHYC_DTPR2_TCKE_0    (0x1U << DDRPHYC_DTPR2_TCKE_Pos)    /*!< 0x00008000 */
#define DDRPHYC_DTPR2_TCKE_1    (0x2U << DDRPHYC_DTPR2_TCKE_Pos)    /*!< 0x00010000 */
#define DDRPHYC_DTPR2_TCKE_2    (0x4U << DDRPHYC_DTPR2_TCKE_Pos)    /*!< 0x00020000 */
#define DDRPHYC_DTPR2_TCKE_3    (0x8U << DDRPHYC_DTPR2_TCKE_Pos)    /*!< 0x00040000 */
#define DDRPHYC_DTPR2_TDLLK_Pos (19U)
#define DDRPHYC_DTPR2_TDLLK_Msk (0x3FFU << DDRPHYC_DTPR2_TDLLK_Pos) /*!< 0x1FF80000 */
#define DDRPHYC_DTPR2_TDLLK     DDRPHYC_DTPR2_TDLLK_Msk             /*!< tDLLK */
#define DDRPHYC_DTPR2_TDLLK_0   (0x1U << DDRPHYC_DTPR2_TDLLK_Pos)   /*!< 0x00080000 */
#define DDRPHYC_DTPR2_TDLLK_1   (0x2U << DDRPHYC_DTPR2_TDLLK_Pos)   /*!< 0x00100000 */
#define DDRPHYC_DTPR2_TDLLK_2   (0x4U << DDRPHYC_DTPR2_TDLLK_Pos)   /*!< 0x00200000 */
#define DDRPHYC_DTPR2_TDLLK_3   (0x8U << DDRPHYC_DTPR2_TDLLK_Pos)   /*!< 0x00400000 */
#define DDRPHYC_DTPR2_TDLLK_4   (0x10U << DDRPHYC_DTPR2_TDLLK_Pos)  /*!< 0x00800000 */
#define DDRPHYC_DTPR2_TDLLK_5   (0x20U << DDRPHYC_DTPR2_TDLLK_Pos)  /*!< 0x01000000 */
#define DDRPHYC_DTPR2_TDLLK_6   (0x40U << DDRPHYC_DTPR2_TDLLK_Pos)  /*!< 0x02000000 */
#define DDRPHYC_DTPR2_TDLLK_7   (0x80U << DDRPHYC_DTPR2_TDLLK_Pos)  /*!< 0x04000000 */
#define DDRPHYC_DTPR2_TDLLK_8   (0x100U << DDRPHYC_DTPR2_TDLLK_Pos) /*!< 0x08000000 */
#define DDRPHYC_DTPR2_TDLLK_9   (0x200U << DDRPHYC_DTPR2_TDLLK_Pos) /*!< 0x10000000 */

/***************  Bit definition for DDRPHYC_DDR3_MR0 register  ***************/
#define DDRPHYC_DDR3_MR0_BL_Pos   (0U)
#define DDRPHYC_DDR3_MR0_BL_Msk   (0x3U << DDRPHYC_DDR3_MR0_BL_Pos)   /*!< 0x00000003 */
#define DDRPHYC_DDR3_MR0_BL       DDRPHYC_DDR3_MR0_BL_Msk             /*!< Burst length */
#define DDRPHYC_DDR3_MR0_BL_0     (0x1U << DDRPHYC_DDR3_MR0_BL_Pos)   /*!< 0x00000001 */
#define DDRPHYC_DDR3_MR0_BL_1     (0x2U << DDRPHYC_DDR3_MR0_BL_Pos)   /*!< 0x00000002 */
#define DDRPHYC_DDR3_MR0_CL0_Pos  (2U)
#define DDRPHYC_DDR3_MR0_CL0_Msk  (0x1U << DDRPHYC_DDR3_MR0_CL0_Pos)  /*!< 0x00000004 */
#define DDRPHYC_DDR3_MR0_CL0      DDRPHYC_DDR3_MR0_CL0_Msk            /*!< CAS latency */
#define DDRPHYC_DDR3_MR0_BT_Pos   (3U)
#define DDRPHYC_DDR3_MR0_BT_Msk   (0x1U << DDRPHYC_DDR3_MR0_BT_Pos)   /*!< 0x00000008 */
#define DDRPHYC_DDR3_MR0_BT       DDRPHYC_DDR3_MR0_BT_Msk             /*!< Burst type */
#define DDRPHYC_DDR3_MR0_CL_Pos   (4U)
#define DDRPHYC_DDR3_MR0_CL_Msk   (0x7U << DDRPHYC_DDR3_MR0_CL_Pos)   /*!< 0x00000070 */
#define DDRPHYC_DDR3_MR0_CL       DDRPHYC_DDR3_MR0_CL_Msk             /*!< CAS latency */
#define DDRPHYC_DDR3_MR0_CL_0     (0x1U << DDRPHYC_DDR3_MR0_CL_Pos)   /*!< 0x00000010 */
#define DDRPHYC_DDR3_MR0_CL_1     (0x2U << DDRPHYC_DDR3_MR0_CL_Pos)   /*!< 0x00000020 */
#define DDRPHYC_DDR3_MR0_CL_2     (0x4U << DDRPHYC_DDR3_MR0_CL_Pos)   /*!< 0x00000040 */
#define DDRPHYC_DDR3_MR0_TM_Pos   (7U)
#define DDRPHYC_DDR3_MR0_TM_Msk   (0x1U << DDRPHYC_DDR3_MR0_TM_Pos)   /*!< 0x00000080 */
#define DDRPHYC_DDR3_MR0_TM       DDRPHYC_DDR3_MR0_TM_Msk             /*!< Operating mode */
#define DDRPHYC_DDR3_MR0_DR_Pos   (8U)
#define DDRPHYC_DDR3_MR0_DR_Msk   (0x1U << DDRPHYC_DDR3_MR0_DR_Pos)   /*!< 0x00000100 */
#define DDRPHYC_DDR3_MR0_DR       DDRPHYC_DDR3_MR0_DR_Msk             /*!< DLL reset (autoclear) */
#define DDRPHYC_DDR3_MR0_WR_Pos   (9U)
#define DDRPHYC_DDR3_MR0_WR_Msk   (0x7U << DDRPHYC_DDR3_MR0_WR_Pos)   /*!< 0x00000E00 */
#define DDRPHYC_DDR3_MR0_WR       DDRPHYC_DDR3_MR0_WR_Msk             /*!< Write recovery */
#define DDRPHYC_DDR3_MR0_WR_0     (0x1U << DDRPHYC_DDR3_MR0_WR_Pos)   /*!< 0x00000200 */
#define DDRPHYC_DDR3_MR0_WR_1     (0x2U << DDRPHYC_DDR3_MR0_WR_Pos)   /*!< 0x00000400 */
#define DDRPHYC_DDR3_MR0_WR_2     (0x4U << DDRPHYC_DDR3_MR0_WR_Pos)   /*!< 0x00000800 */
#define DDRPHYC_DDR3_MR0_PD_Pos   (12U)
#define DDRPHYC_DDR3_MR0_PD_Msk   (0x1U << DDRPHYC_DDR3_MR0_PD_Pos)   /*!< 0x00001000 */
#define DDRPHYC_DDR3_MR0_PD       DDRPHYC_DDR3_MR0_PD_Msk             /*!< Power-down control */
#define DDRPHYC_DDR3_MR0_RSVD_Pos (13U)
#define DDRPHYC_DDR3_MR0_RSVD_Msk (0x7U << DDRPHYC_DDR3_MR0_RSVD_Pos) /*!< 0x0000E000 */
#define DDRPHYC_DDR3_MR0_RSVD     DDRPHYC_DDR3_MR0_RSVD_Msk           /*!< JEDEC reserved. */
#define DDRPHYC_DDR3_MR0_RSVD_0   (0x1U << DDRPHYC_DDR3_MR0_RSVD_Pos) /*!< 0x00002000 */
#define DDRPHYC_DDR3_MR0_RSVD_1   (0x2U << DDRPHYC_DDR3_MR0_RSVD_Pos) /*!< 0x00004000 */
#define DDRPHYC_DDR3_MR0_RSVD_2   (0x4U << DDRPHYC_DDR3_MR0_RSVD_Pos) /*!< 0x00008000 */

/***************  Bit definition for DDRPHYC_DDR3_MR1 register  ***************/
#define DDRPHYC_DDR3_MR1_DE_Pos    (0U)
#define DDRPHYC_DDR3_MR1_DE_Msk    (0x1U << DDRPHYC_DDR3_MR1_DE_Pos)    /*!< 0x00000001 */
#define DDRPHYC_DDR3_MR1_DE        DDRPHYC_DDR3_MR1_DE_Msk              /*!< DLL enable/disable */
#define DDRPHYC_DDR3_MR1_DIC0_Pos  (1U)
#define DDRPHYC_DDR3_MR1_DIC0_Msk  (0x1U << DDRPHYC_DDR3_MR1_DIC0_Pos)  /*!< 0x00000002 */
#define DDRPHYC_DDR3_MR1_DIC0      DDRPHYC_DDR3_MR1_DIC0_Msk            /*!< Output driver impedance control */
#define DDRPHYC_DDR3_MR1_RTT0_Pos  (2U)
#define DDRPHYC_DDR3_MR1_RTT0_Msk  (0x1U << DDRPHYC_DDR3_MR1_RTT0_Pos)  /*!< 0x00000004 */
#define DDRPHYC_DDR3_MR1_RTT0      DDRPHYC_DDR3_MR1_RTT0_Msk            /*!< On die termination */
#define DDRPHYC_DDR3_MR1_AL_Pos    (3U)
#define DDRPHYC_DDR3_MR1_AL_Msk    (0x3U << DDRPHYC_DDR3_MR1_AL_Pos)    /*!< 0x00000018 */
#define DDRPHYC_DDR3_MR1_AL        DDRPHYC_DDR3_MR1_AL_Msk              /*!< Posted CAS Additive Latency: */
#define DDRPHYC_DDR3_MR1_AL_0      (0x1U << DDRPHYC_DDR3_MR1_AL_Pos)    /*!< 0x00000008 */
#define DDRPHYC_DDR3_MR1_AL_1      (0x2U << DDRPHYC_DDR3_MR1_AL_Pos)    /*!< 0x00000010 */
#define DDRPHYC_DDR3_MR1_DIC1_Pos  (5U)
#define DDRPHYC_DDR3_MR1_DIC1_Msk  (0x1U << DDRPHYC_DDR3_MR1_DIC1_Pos)  /*!< 0x00000020 */
#define DDRPHYC_DDR3_MR1_DIC1      DDRPHYC_DDR3_MR1_DIC1_Msk            /*!< Output driver impedance control */
#define DDRPHYC_DDR3_MR1_RTT1_Pos  (6U)
#define DDRPHYC_DDR3_MR1_RTT1_Msk  (0x1U << DDRPHYC_DDR3_MR1_RTT1_Pos)  /*!< 0x00000040 */
#define DDRPHYC_DDR3_MR1_RTT1      DDRPHYC_DDR3_MR1_RTT1_Msk            /*!< On die termination */
#define DDRPHYC_DDR3_MR1_LEVEL_Pos (7U)
#define DDRPHYC_DDR3_MR1_LEVEL_Msk (0x1U << DDRPHYC_DDR3_MR1_LEVEL_Pos) /*!< 0x00000080 */
#define DDRPHYC_DDR3_MR1_LEVEL     DDRPHYC_DDR3_MR1_LEVEL_Msk           /*!< Write leveling enable (N/A) */
#define DDRPHYC_DDR3_MR1_RTT2_Pos  (9U)
#define DDRPHYC_DDR3_MR1_RTT2_Msk  (0x1U << DDRPHYC_DDR3_MR1_RTT2_Pos)  /*!< 0x00000200 */
#define DDRPHYC_DDR3_MR1_RTT2      DDRPHYC_DDR3_MR1_RTT2_Msk            /*!< On die termination */
#define DDRPHYC_DDR3_MR1_TDQS_Pos  (11U)
#define DDRPHYC_DDR3_MR1_TDQS_Msk  (0x1U << DDRPHYC_DDR3_MR1_TDQS_Pos)  /*!< 0x00000800 */
#define DDRPHYC_DDR3_MR1_TDQS      DDRPHYC_DDR3_MR1_TDQS_Msk            /*!< Termination data strobe */
#define DDRPHYC_DDR3_MR1_QOFF_Pos  (12U)
#define DDRPHYC_DDR3_MR1_QOFF_Msk  (0x1U << DDRPHYC_DDR3_MR1_QOFF_Pos)  /*!< 0x00001000 */
#define DDRPHYC_DDR3_MR1_QOFF      DDRPHYC_DDR3_MR1_QOFF_Msk            /*!< Output enable/disable */
#define DDRPHYC_DDR3_MR1_BL_Pos    (0U)
#define DDRPHYC_DDR3_MR1_BL_Msk    (0x7U << DDRPHYC_DDR3_MR1_BL_Pos)    /*!< 0x00000007 */
#define DDRPHYC_DDR3_MR1_BL        DDRPHYC_DDR3_MR1_BL_Msk              /*!< Burst length */
#define DDRPHYC_DDR3_MR1_BL_0      (0x1U << DDRPHYC_DDR3_MR1_BL_Pos)    /*!< 0x00000001 */
#define DDRPHYC_DDR3_MR1_BL_1      (0x2U << DDRPHYC_DDR3_MR1_BL_Pos)    /*!< 0x00000002 */
#define DDRPHYC_DDR3_MR1_BL_2      (0x4U << DDRPHYC_DDR3_MR1_BL_Pos)    /*!< 0x00000004 */
#define DDRPHYC_DDR3_MR1_BT_Pos    (3U)
#define DDRPHYC_DDR3_MR1_BT_Msk    (0x1U << DDRPHYC_DDR3_MR1_BT_Pos)    /*!< 0x00000008 */
#define DDRPHYC_DDR3_MR1_BT        DDRPHYC_DDR3_MR1_BT_Msk              /*!< Burst Type: Indicates whether a burst is sequential (0) or interleaved (1). , */
#define DDRPHYC_DDR3_MR1_WC_Pos    (4U)
#define DDRPHYC_DDR3_MR1_WC_Msk    (0x1U << DDRPHYC_DDR3_MR1_WC_Pos)    /*!< 0x00000010 */
#define DDRPHYC_DDR3_MR1_WC        DDRPHYC_DDR3_MR1_WC_Msk              /*!< Wrap control */
#define DDRPHYC_DDR3_MR1_NWR_Pos   (5U)
#define DDRPHYC_DDR3_MR1_NWR_Msk   (0x7U << DDRPHYC_DDR3_MR1_NWR_Pos)   /*!< 0x000000E0 */
#define DDRPHYC_DDR3_MR1_NWR       DDRPHYC_DDR3_MR1_NWR_Msk             /*!< Write recovery */
#define DDRPHYC_DDR3_MR1_NWR_0     (0x1U << DDRPHYC_DDR3_MR1_NWR_Pos)   /*!< 0x00000020 */
#define DDRPHYC_DDR3_MR1_NWR_1     (0x2U << DDRPHYC_DDR3_MR1_NWR_Pos)   /*!< 0x00000040 */
#define DDRPHYC_DDR3_MR1_NWR_2     (0x4U << DDRPHYC_DDR3_MR1_NWR_Pos)   /*!< 0x00000080 */
#define DDRPHYC_DDR3_MR1_BL_Pos    (0U)
#define DDRPHYC_DDR3_MR1_BL_Msk    (0x7U << DDRPHYC_DDR3_MR1_BL_Pos)    /*!< 0x00000007 */
#define DDRPHYC_DDR3_MR1_BL        DDRPHYC_DDR3_MR1_BL_Msk              /*!< Burst length */
#define DDRPHYC_DDR3_MR1_BL_0      (0x1U << DDRPHYC_DDR3_MR1_BL_Pos)    /*!< 0x00000001 */
#define DDRPHYC_DDR3_MR1_BL_1      (0x2U << DDRPHYC_DDR3_MR1_BL_Pos)    /*!< 0x00000002 */
#define DDRPHYC_DDR3_MR1_BL_2      (0x4U << DDRPHYC_DDR3_MR1_BL_Pos)    /*!< 0x00000004 */
#define DDRPHYC_DDR3_MR1_NWR_Pos   (5U)
#define DDRPHYC_DDR3_MR1_NWR_Msk   (0x7U << DDRPHYC_DDR3_MR1_NWR_Pos)   /*!< 0x000000E0 */
#define DDRPHYC_DDR3_MR1_NWR       DDRPHYC_DDR3_MR1_NWR_Msk             /*!< Write recovery */
#define DDRPHYC_DDR3_MR1_NWR_0     (0x1U << DDRPHYC_DDR3_MR1_NWR_Pos)   /*!< 0x00000020 */
#define DDRPHYC_DDR3_MR1_NWR_1     (0x2U << DDRPHYC_DDR3_MR1_NWR_Pos)   /*!< 0x00000040 */
#define DDRPHYC_DDR3_MR1_NWR_2     (0x4U << DDRPHYC_DDR3_MR1_NWR_Pos)   /*!< 0x00000080 */

/***************  Bit definition for DDRPHYC_DDR3_MR2 register  ***************/
#define DDRPHYC_DDR3_MR2_PASR_Pos  (0U)
#define DDRPHYC_DDR3_MR2_PASR_Msk  (0x7U << DDRPHYC_DDR3_MR2_PASR_Pos)  /*!< 0x00000007 */
#define DDRPHYC_DDR3_MR2_PASR      DDRPHYC_DDR3_MR2_PASR_Msk            /*!< Partial array self-refresh */
#define DDRPHYC_DDR3_MR2_PASR_0    (0x1U << DDRPHYC_DDR3_MR2_PASR_Pos)  /*!< 0x00000001 */
#define DDRPHYC_DDR3_MR2_PASR_1    (0x2U << DDRPHYC_DDR3_MR2_PASR_Pos)  /*!< 0x00000002 */
#define DDRPHYC_DDR3_MR2_PASR_2    (0x4U << DDRPHYC_DDR3_MR2_PASR_Pos)  /*!< 0x00000004 */
#define DDRPHYC_DDR3_MR2_CWL_Pos   (3U)
#define DDRPHYC_DDR3_MR2_CWL_Msk   (0x7U << DDRPHYC_DDR3_MR2_CWL_Pos)   /*!< 0x00000038 */
#define DDRPHYC_DDR3_MR2_CWL       DDRPHYC_DDR3_MR2_CWL_Msk             /*!< CAS write latency */
#define DDRPHYC_DDR3_MR2_CWL_0     (0x1U << DDRPHYC_DDR3_MR2_CWL_Pos)   /*!< 0x00000008 */
#define DDRPHYC_DDR3_MR2_CWL_1     (0x2U << DDRPHYC_DDR3_MR2_CWL_Pos)   /*!< 0x00000010 */
#define DDRPHYC_DDR3_MR2_CWL_2     (0x4U << DDRPHYC_DDR3_MR2_CWL_Pos)   /*!< 0x00000020 */
#define DDRPHYC_DDR3_MR2_ASR_Pos   (6U)
#define DDRPHYC_DDR3_MR2_ASR_Msk   (0x1U << DDRPHYC_DDR3_MR2_ASR_Pos)   /*!< 0x00000040 */
#define DDRPHYC_DDR3_MR2_ASR       DDRPHYC_DDR3_MR2_ASR_Msk             /*!< Auto self-refresh */
#define DDRPHYC_DDR3_MR2_SRT_Pos   (7U)
#define DDRPHYC_DDR3_MR2_SRT_Msk   (0x1U << DDRPHYC_DDR3_MR2_SRT_Pos)   /*!< 0x00000080 */
#define DDRPHYC_DDR3_MR2_SRT       DDRPHYC_DDR3_MR2_SRT_Msk             /*!< Self-refresh temperature range */
#define DDRPHYC_DDR3_MR2_RTTWR_Pos (9U)
#define DDRPHYC_DDR3_MR2_RTTWR_Msk (0x3U << DDRPHYC_DDR3_MR2_RTTWR_Pos) /*!< 0x00000600 */
#define DDRPHYC_DDR3_MR2_RTTWR     DDRPHYC_DDR3_MR2_RTTWR_Msk           /*!< Dynamic ODT */
#define DDRPHYC_DDR3_MR2_RTTWR_0   (0x1U << DDRPHYC_DDR3_MR2_RTTWR_Pos) /*!< 0x00000200 */
#define DDRPHYC_DDR3_MR2_RTTWR_1   (0x2U << DDRPHYC_DDR3_MR2_RTTWR_Pos) /*!< 0x00000400 */
#define DDRPHYC_DDR3_MR2_RLWL_Pos  (0U)
#define DDRPHYC_DDR3_MR2_RLWL_Msk  (0x7U << DDRPHYC_DDR3_MR2_RLWL_Pos)  /*!< 0x00000007 */
#define DDRPHYC_DDR3_MR2_RLWL      DDRPHYC_DDR3_MR2_RLWL_Msk            /*!< Read and write latency */
#define DDRPHYC_DDR3_MR2_RLWL_0    (0x1U << DDRPHYC_DDR3_MR2_RLWL_Pos)  /*!< 0x00000001 */
#define DDRPHYC_DDR3_MR2_RLWL_1    (0x2U << DDRPHYC_DDR3_MR2_RLWL_Pos)  /*!< 0x00000002 */
#define DDRPHYC_DDR3_MR2_RLWL_2    (0x4U << DDRPHYC_DDR3_MR2_RLWL_Pos)  /*!< 0x00000004 */
#define DDRPHYC_DDR3_MR2_RLWL_Pos  (0U)
#define DDRPHYC_DDR3_MR2_RLWL_Msk  (0x7U << DDRPHYC_DDR3_MR2_RLWL_Pos)  /*!< 0x00000007 */
#define DDRPHYC_DDR3_MR2_RLWL      DDRPHYC_DDR3_MR2_RLWL_Msk            /*!< Read and write latency */
#define DDRPHYC_DDR3_MR2_RLWL_0    (0x1U << DDRPHYC_DDR3_MR2_RLWL_Pos)  /*!< 0x00000001 */
#define DDRPHYC_DDR3_MR2_RLWL_1    (0x2U << DDRPHYC_DDR3_MR2_RLWL_Pos)  /*!< 0x00000002 */
#define DDRPHYC_DDR3_MR2_RLWL_2    (0x4U << DDRPHYC_DDR3_MR2_RLWL_Pos)  /*!< 0x00000004 */
#define DDRPHYC_DDR3_MR2_NWRE_Pos  (4U)
#define DDRPHYC_DDR3_MR2_NWRE_Msk  (0x1U << DDRPHYC_DDR3_MR2_NWRE_Pos)  /*!< 0x00000010 */
#define DDRPHYC_DDR3_MR2_NWRE      DDRPHYC_DDR3_MR2_NWRE_Msk            /*!< New for LPDDR3 (not used by this PHY, leave at zero) */
#define DDRPHYC_DDR3_MR2_WL_Pos    (6U)
#define DDRPHYC_DDR3_MR2_WL_Msk    (0x1U << DDRPHYC_DDR3_MR2_WL_Pos)    /*!< 0x00000040 */
#define DDRPHYC_DDR3_MR2_WL        DDRPHYC_DDR3_MR2_WL_Msk              /*!< New for LPDDR3 (not used by this PHY, leave at zero) */
#define DDRPHYC_DDR3_MR2_WR_Pos    (7U)
#define DDRPHYC_DDR3_MR2_WR_Msk    (0x1U << DDRPHYC_DDR3_MR2_WR_Pos)    /*!< 0x00000080 */
#define DDRPHYC_DDR3_MR2_WR        DDRPHYC_DDR3_MR2_WR_Msk              /*!< New for LPDDR3 (not used by this PHY, leave at zero) */

/***************  Bit definition for DDRPHYC_DDR3_MR3 register  ***************/
#define DDRPHYC_DDR3_MR3_MPRLOC_Pos (0U)
#define DDRPHYC_DDR3_MR3_MPRLOC_Msk (0x3U << DDRPHYC_DDR3_MR3_MPRLOC_Pos) /*!< 0x00000003 */
#define DDRPHYC_DDR3_MR3_MPRLOC     DDRPHYC_DDR3_MR3_MPRLOC_Msk           /*!< Multi-purpose register (MPR) location */
#define DDRPHYC_DDR3_MR3_MPRLOC_0   (0x1U << DDRPHYC_DDR3_MR3_MPRLOC_Pos) /*!< 0x00000001 */
#define DDRPHYC_DDR3_MR3_MPRLOC_1   (0x2U << DDRPHYC_DDR3_MR3_MPRLOC_Pos) /*!< 0x00000002 */
#define DDRPHYC_DDR3_MR3_MPR_Pos    (2U)
#define DDRPHYC_DDR3_MR3_MPR_Msk    (0x1U << DDRPHYC_DDR3_MR3_MPR_Pos)    /*!< 0x00000004 */
#define DDRPHYC_DDR3_MR3_MPR        DDRPHYC_DDR3_MR3_MPR_Msk              /*!< Multi-purpose register enable */

/****************  Bit definition for DDRPHYC_ODTCR register  *****************/
#define DDRPHYC_ODTCR_RDODT_Pos (0U)
#define DDRPHYC_ODTCR_RDODT_Msk (0x1U << DDRPHYC_ODTCR_RDODT_Pos) /*!< 0x00000001 */
#define DDRPHYC_ODTCR_RDODT     DDRPHYC_ODTCR_RDODT_Msk           /*!< Specifies whether ODT should be enabled ('1') or disabled ('0') on read */
#define DDRPHYC_ODTCR_WRODT_Pos (16U)
#define DDRPHYC_ODTCR_WRODT_Msk (0x1U << DDRPHYC_ODTCR_WRODT_Pos) /*!< 0x00010000 */
#define DDRPHYC_ODTCR_WRODT     DDRPHYC_ODTCR_WRODT_Msk           /*!< Specifies whether ODT should be enabled ('1') or disabled ('0') on write */

/*****************  Bit definition for DDRPHYC_DTAR register  *****************/
#define DDRPHYC_DTAR_DTCOL_Pos  (0U)
#define DDRPHYC_DTAR_DTCOL_Msk  (0xFFFU << DDRPHYC_DTAR_DTCOL_Pos)  /*!< 0x00000FFF */
#define DDRPHYC_DTAR_DTCOL      DDRPHYC_DTAR_DTCOL_Msk              /*!< Data training column address: */
#define DDRPHYC_DTAR_DTCOL_0    (0x1U << DDRPHYC_DTAR_DTCOL_Pos)    /*!< 0x00000001 */
#define DDRPHYC_DTAR_DTCOL_1    (0x2U << DDRPHYC_DTAR_DTCOL_Pos)    /*!< 0x00000002 */
#define DDRPHYC_DTAR_DTCOL_2    (0x4U << DDRPHYC_DTAR_DTCOL_Pos)    /*!< 0x00000004 */
#define DDRPHYC_DTAR_DTCOL_3    (0x8U << DDRPHYC_DTAR_DTCOL_Pos)    /*!< 0x00000008 */
#define DDRPHYC_DTAR_DTCOL_4    (0x10U << DDRPHYC_DTAR_DTCOL_Pos)   /*!< 0x00000010 */
#define DDRPHYC_DTAR_DTCOL_5    (0x20U << DDRPHYC_DTAR_DTCOL_Pos)   /*!< 0x00000020 */
#define DDRPHYC_DTAR_DTCOL_6    (0x40U << DDRPHYC_DTAR_DTCOL_Pos)   /*!< 0x00000040 */
#define DDRPHYC_DTAR_DTCOL_7    (0x80U << DDRPHYC_DTAR_DTCOL_Pos)   /*!< 0x00000080 */
#define DDRPHYC_DTAR_DTCOL_8    (0x100U << DDRPHYC_DTAR_DTCOL_Pos)  /*!< 0x00000100 */
#define DDRPHYC_DTAR_DTCOL_9    (0x200U << DDRPHYC_DTAR_DTCOL_Pos)  /*!< 0x00000200 */
#define DDRPHYC_DTAR_DTCOL_10   (0x400U << DDRPHYC_DTAR_DTCOL_Pos)  /*!< 0x00000400 */
#define DDRPHYC_DTAR_DTCOL_11   (0x800U << DDRPHYC_DTAR_DTCOL_Pos)  /*!< 0x00000800 */
#define DDRPHYC_DTAR_DTROW_Pos  (12U)
#define DDRPHYC_DTAR_DTROW_Msk  (0xFFFFU << DDRPHYC_DTAR_DTROW_Pos) /*!< 0x0FFFF000 */
#define DDRPHYC_DTAR_DTROW      DDRPHYC_DTAR_DTROW_Msk              /*!< Data training row address: */
#define DDRPHYC_DTAR_DTROW_0    (0x1U << DDRPHYC_DTAR_DTROW_Pos)    /*!< 0x00001000 */
#define DDRPHYC_DTAR_DTROW_1    (0x2U << DDRPHYC_DTAR_DTROW_Pos)    /*!< 0x00002000 */
#define DDRPHYC_DTAR_DTROW_2    (0x4U << DDRPHYC_DTAR_DTROW_Pos)    /*!< 0x00004000 */
#define DDRPHYC_DTAR_DTROW_3    (0x8U << DDRPHYC_DTAR_DTROW_Pos)    /*!< 0x00008000 */
#define DDRPHYC_DTAR_DTROW_4    (0x10U << DDRPHYC_DTAR_DTROW_Pos)   /*!< 0x00010000 */
#define DDRPHYC_DTAR_DTROW_5    (0x20U << DDRPHYC_DTAR_DTROW_Pos)   /*!< 0x00020000 */
#define DDRPHYC_DTAR_DTROW_6    (0x40U << DDRPHYC_DTAR_DTROW_Pos)   /*!< 0x00040000 */
#define DDRPHYC_DTAR_DTROW_7    (0x80U << DDRPHYC_DTAR_DTROW_Pos)   /*!< 0x00080000 */
#define DDRPHYC_DTAR_DTROW_8    (0x100U << DDRPHYC_DTAR_DTROW_Pos)  /*!< 0x00100000 */
#define DDRPHYC_DTAR_DTROW_9    (0x200U << DDRPHYC_DTAR_DTROW_Pos)  /*!< 0x00200000 */
#define DDRPHYC_DTAR_DTROW_10   (0x400U << DDRPHYC_DTAR_DTROW_Pos)  /*!< 0x00400000 */
#define DDRPHYC_DTAR_DTROW_11   (0x800U << DDRPHYC_DTAR_DTROW_Pos)  /*!< 0x00800000 */
#define DDRPHYC_DTAR_DTROW_12   (0x1000U << DDRPHYC_DTAR_DTROW_Pos) /*!< 0x01000000 */
#define DDRPHYC_DTAR_DTROW_13   (0x2000U << DDRPHYC_DTAR_DTROW_Pos) /*!< 0x02000000 */
#define DDRPHYC_DTAR_DTROW_14   (0x4000U << DDRPHYC_DTAR_DTROW_Pos) /*!< 0x04000000 */
#define DDRPHYC_DTAR_DTROW_15   (0x8000U << DDRPHYC_DTAR_DTROW_Pos) /*!< 0x08000000 */
#define DDRPHYC_DTAR_DTBANK_Pos (28U)
#define DDRPHYC_DTAR_DTBANK_Msk (0x7U << DDRPHYC_DTAR_DTBANK_Pos)   /*!< 0x70000000 */
#define DDRPHYC_DTAR_DTBANK     DDRPHYC_DTAR_DTBANK_Msk             /*!< Data training bank address: */
#define DDRPHYC_DTAR_DTBANK_0   (0x1U << DDRPHYC_DTAR_DTBANK_Pos)   /*!< 0x10000000 */
#define DDRPHYC_DTAR_DTBANK_1   (0x2U << DDRPHYC_DTAR_DTBANK_Pos)   /*!< 0x20000000 */
#define DDRPHYC_DTAR_DTBANK_2   (0x4U << DDRPHYC_DTAR_DTBANK_Pos)   /*!< 0x40000000 */
#define DDRPHYC_DTAR_DTMPR_Pos  (31U)
#define DDRPHYC_DTAR_DTMPR_Msk  (0x1U << DDRPHYC_DTAR_DTMPR_Pos)    /*!< 0x80000000 */
#define DDRPHYC_DTAR_DTMPR      DDRPHYC_DTAR_DTMPR_Msk              /*!< Data training using MPR (DDR3 Only): */

/****************  Bit definition for DDRPHYC_DTDR0 register  *****************/
#define DDRPHYC_DTDR0_DTBYTE0_Pos (0U)
#define DDRPHYC_DTDR0_DTBYTE0_Msk (0xFFU << DDRPHYC_DTDR0_DTBYTE0_Pos) /*!< 0x000000FF */
#define DDRPHYC_DTDR0_DTBYTE0     DDRPHYC_DTDR0_DTBYTE0_Msk            /*!< Data Training Data */
#define DDRPHYC_DTDR0_DTBYTE0_0   (0x1U << DDRPHYC_DTDR0_DTBYTE0_Pos)  /*!< 0x00000001 */
#define DDRPHYC_DTDR0_DTBYTE0_1   (0x2U << DDRPHYC_DTDR0_DTBYTE0_Pos)  /*!< 0x00000002 */
#define DDRPHYC_DTDR0_DTBYTE0_2   (0x4U << DDRPHYC_DTDR0_DTBYTE0_Pos)  /*!< 0x00000004 */
#define DDRPHYC_DTDR0_DTBYTE0_3   (0x8U << DDRPHYC_DTDR0_DTBYTE0_Pos)  /*!< 0x00000008 */
#define DDRPHYC_DTDR0_DTBYTE0_4   (0x10U << DDRPHYC_DTDR0_DTBYTE0_Pos) /*!< 0x00000010 */
#define DDRPHYC_DTDR0_DTBYTE0_5   (0x20U << DDRPHYC_DTDR0_DTBYTE0_Pos) /*!< 0x00000020 */
#define DDRPHYC_DTDR0_DTBYTE0_6   (0x40U << DDRPHYC_DTDR0_DTBYTE0_Pos) /*!< 0x00000040 */
#define DDRPHYC_DTDR0_DTBYTE0_7   (0x80U << DDRPHYC_DTDR0_DTBYTE0_Pos) /*!< 0x00000080 */
#define DDRPHYC_DTDR0_DTBYTE1_Pos (8U)
#define DDRPHYC_DTDR0_DTBYTE1_Msk (0xFFU << DDRPHYC_DTDR0_DTBYTE1_Pos) /*!< 0x0000FF00 */
#define DDRPHYC_DTDR0_DTBYTE1     DDRPHYC_DTDR0_DTBYTE1_Msk            /*!< Data Training Data */
#define DDRPHYC_DTDR0_DTBYTE1_0   (0x1U << DDRPHYC_DTDR0_DTBYTE1_Pos)  /*!< 0x00000100 */
#define DDRPHYC_DTDR0_DTBYTE1_1   (0x2U << DDRPHYC_DTDR0_DTBYTE1_Pos)  /*!< 0x00000200 */
#define DDRPHYC_DTDR0_DTBYTE1_2   (0x4U << DDRPHYC_DTDR0_DTBYTE1_Pos)  /*!< 0x00000400 */
#define DDRPHYC_DTDR0_DTBYTE1_3   (0x8U << DDRPHYC_DTDR0_DTBYTE1_Pos)  /*!< 0x00000800 */
#define DDRPHYC_DTDR0_DTBYTE1_4   (0x10U << DDRPHYC_DTDR0_DTBYTE1_Pos) /*!< 0x00001000 */
#define DDRPHYC_DTDR0_DTBYTE1_5   (0x20U << DDRPHYC_DTDR0_DTBYTE1_Pos) /*!< 0x00002000 */
#define DDRPHYC_DTDR0_DTBYTE1_6   (0x40U << DDRPHYC_DTDR0_DTBYTE1_Pos) /*!< 0x00004000 */
#define DDRPHYC_DTDR0_DTBYTE1_7   (0x80U << DDRPHYC_DTDR0_DTBYTE1_Pos) /*!< 0x00008000 */
#define DDRPHYC_DTDR0_DTBYTE2_Pos (16U)
#define DDRPHYC_DTDR0_DTBYTE2_Msk (0xFFU << DDRPHYC_DTDR0_DTBYTE2_Pos) /*!< 0x00FF0000 */
#define DDRPHYC_DTDR0_DTBYTE2     DDRPHYC_DTDR0_DTBYTE2_Msk            /*!< Data Training Data */
#define DDRPHYC_DTDR0_DTBYTE2_0   (0x1U << DDRPHYC_DTDR0_DTBYTE2_Pos)  /*!< 0x00010000 */
#define DDRPHYC_DTDR0_DTBYTE2_1   (0x2U << DDRPHYC_DTDR0_DTBYTE2_Pos)  /*!< 0x00020000 */
#define DDRPHYC_DTDR0_DTBYTE2_2   (0x4U << DDRPHYC_DTDR0_DTBYTE2_Pos)  /*!< 0x00040000 */
#define DDRPHYC_DTDR0_DTBYTE2_3   (0x8U << DDRPHYC_DTDR0_DTBYTE2_Pos)  /*!< 0x00080000 */
#define DDRPHYC_DTDR0_DTBYTE2_4   (0x10U << DDRPHYC_DTDR0_DTBYTE2_Pos) /*!< 0x00100000 */
#define DDRPHYC_DTDR0_DTBYTE2_5   (0x20U << DDRPHYC_DTDR0_DTBYTE2_Pos) /*!< 0x00200000 */
#define DDRPHYC_DTDR0_DTBYTE2_6   (0x40U << DDRPHYC_DTDR0_DTBYTE2_Pos) /*!< 0x00400000 */
#define DDRPHYC_DTDR0_DTBYTE2_7   (0x80U << DDRPHYC_DTDR0_DTBYTE2_Pos) /*!< 0x00800000 */
#define DDRPHYC_DTDR0_DTBYTE3_Pos (24U)
#define DDRPHYC_DTDR0_DTBYTE3_Msk (0xFFU << DDRPHYC_DTDR0_DTBYTE3_Pos) /*!< 0xFF000000 */
#define DDRPHYC_DTDR0_DTBYTE3     DDRPHYC_DTDR0_DTBYTE3_Msk            /*!< Data training data */
#define DDRPHYC_DTDR0_DTBYTE3_0   (0x1U << DDRPHYC_DTDR0_DTBYTE3_Pos)  /*!< 0x01000000 */
#define DDRPHYC_DTDR0_DTBYTE3_1   (0x2U << DDRPHYC_DTDR0_DTBYTE3_Pos)  /*!< 0x02000000 */
#define DDRPHYC_DTDR0_DTBYTE3_2   (0x4U << DDRPHYC_DTDR0_DTBYTE3_Pos)  /*!< 0x04000000 */
#define DDRPHYC_DTDR0_DTBYTE3_3   (0x8U << DDRPHYC_DTDR0_DTBYTE3_Pos)  /*!< 0x08000000 */
#define DDRPHYC_DTDR0_DTBYTE3_4   (0x10U << DDRPHYC_DTDR0_DTBYTE3_Pos) /*!< 0x10000000 */
#define DDRPHYC_DTDR0_DTBYTE3_5   (0x20U << DDRPHYC_DTDR0_DTBYTE3_Pos) /*!< 0x20000000 */
#define DDRPHYC_DTDR0_DTBYTE3_6   (0x40U << DDRPHYC_DTDR0_DTBYTE3_Pos) /*!< 0x40000000 */
#define DDRPHYC_DTDR0_DTBYTE3_7   (0x80U << DDRPHYC_DTDR0_DTBYTE3_Pos) /*!< 0x80000000 */

/****************  Bit definition for DDRPHYC_DTDR1 register  *****************/
#define DDRPHYC_DTDR1_DTBYTE4_Pos (0U)
#define DDRPHYC_DTDR1_DTBYTE4_Msk (0xFFU << DDRPHYC_DTDR1_DTBYTE4_Pos) /*!< 0x000000FF */
#define DDRPHYC_DTDR1_DTBYTE4     DDRPHYC_DTDR1_DTBYTE4_Msk            /*!< Data Training Data */
#define DDRPHYC_DTDR1_DTBYTE4_0   (0x1U << DDRPHYC_DTDR1_DTBYTE4_Pos)  /*!< 0x00000001 */
#define DDRPHYC_DTDR1_DTBYTE4_1   (0x2U << DDRPHYC_DTDR1_DTBYTE4_Pos)  /*!< 0x00000002 */
#define DDRPHYC_DTDR1_DTBYTE4_2   (0x4U << DDRPHYC_DTDR1_DTBYTE4_Pos)  /*!< 0x00000004 */
#define DDRPHYC_DTDR1_DTBYTE4_3   (0x8U << DDRPHYC_DTDR1_DTBYTE4_Pos)  /*!< 0x00000008 */
#define DDRPHYC_DTDR1_DTBYTE4_4   (0x10U << DDRPHYC_DTDR1_DTBYTE4_Pos) /*!< 0x00000010 */
#define DDRPHYC_DTDR1_DTBYTE4_5   (0x20U << DDRPHYC_DTDR1_DTBYTE4_Pos) /*!< 0x00000020 */
#define DDRPHYC_DTDR1_DTBYTE4_6   (0x40U << DDRPHYC_DTDR1_DTBYTE4_Pos) /*!< 0x00000040 */
#define DDRPHYC_DTDR1_DTBYTE4_7   (0x80U << DDRPHYC_DTDR1_DTBYTE4_Pos) /*!< 0x00000080 */
#define DDRPHYC_DTDR1_DTBYTE5_Pos (8U)
#define DDRPHYC_DTDR1_DTBYTE5_Msk (0xFFU << DDRPHYC_DTDR1_DTBYTE5_Pos) /*!< 0x0000FF00 */
#define DDRPHYC_DTDR1_DTBYTE5     DDRPHYC_DTDR1_DTBYTE5_Msk            /*!< Data Training Data */
#define DDRPHYC_DTDR1_DTBYTE5_0   (0x1U << DDRPHYC_DTDR1_DTBYTE5_Pos)  /*!< 0x00000100 */
#define DDRPHYC_DTDR1_DTBYTE5_1   (0x2U << DDRPHYC_DTDR1_DTBYTE5_Pos)  /*!< 0x00000200 */
#define DDRPHYC_DTDR1_DTBYTE5_2   (0x4U << DDRPHYC_DTDR1_DTBYTE5_Pos)  /*!< 0x00000400 */
#define DDRPHYC_DTDR1_DTBYTE5_3   (0x8U << DDRPHYC_DTDR1_DTBYTE5_Pos)  /*!< 0x00000800 */
#define DDRPHYC_DTDR1_DTBYTE5_4   (0x10U << DDRPHYC_DTDR1_DTBYTE5_Pos) /*!< 0x00001000 */
#define DDRPHYC_DTDR1_DTBYTE5_5   (0x20U << DDRPHYC_DTDR1_DTBYTE5_Pos) /*!< 0x00002000 */
#define DDRPHYC_DTDR1_DTBYTE5_6   (0x40U << DDRPHYC_DTDR1_DTBYTE5_Pos) /*!< 0x00004000 */
#define DDRPHYC_DTDR1_DTBYTE5_7   (0x80U << DDRPHYC_DTDR1_DTBYTE5_Pos) /*!< 0x00008000 */
#define DDRPHYC_DTDR1_DTBYTE6_Pos (16U)
#define DDRPHYC_DTDR1_DTBYTE6_Msk (0xFFU << DDRPHYC_DTDR1_DTBYTE6_Pos) /*!< 0x00FF0000 */
#define DDRPHYC_DTDR1_DTBYTE6     DDRPHYC_DTDR1_DTBYTE6_Msk            /*!< Data Training Data */
#define DDRPHYC_DTDR1_DTBYTE6_0   (0x1U << DDRPHYC_DTDR1_DTBYTE6_Pos)  /*!< 0x00010000 */
#define DDRPHYC_DTDR1_DTBYTE6_1   (0x2U << DDRPHYC_DTDR1_DTBYTE6_Pos)  /*!< 0x00020000 */
#define DDRPHYC_DTDR1_DTBYTE6_2   (0x4U << DDRPHYC_DTDR1_DTBYTE6_Pos)  /*!< 0x00040000 */
#define DDRPHYC_DTDR1_DTBYTE6_3   (0x8U << DDRPHYC_DTDR1_DTBYTE6_Pos)  /*!< 0x00080000 */
#define DDRPHYC_DTDR1_DTBYTE6_4   (0x10U << DDRPHYC_DTDR1_DTBYTE6_Pos) /*!< 0x00100000 */
#define DDRPHYC_DTDR1_DTBYTE6_5   (0x20U << DDRPHYC_DTDR1_DTBYTE6_Pos) /*!< 0x00200000 */
#define DDRPHYC_DTDR1_DTBYTE6_6   (0x40U << DDRPHYC_DTDR1_DTBYTE6_Pos) /*!< 0x00400000 */
#define DDRPHYC_DTDR1_DTBYTE6_7   (0x80U << DDRPHYC_DTDR1_DTBYTE6_Pos) /*!< 0x00800000 */
#define DDRPHYC_DTDR1_DTBYTE7_Pos (24U)
#define DDRPHYC_DTDR1_DTBYTE7_Msk (0xFFU << DDRPHYC_DTDR1_DTBYTE7_Pos) /*!< 0xFF000000 */
#define DDRPHYC_DTDR1_DTBYTE7     DDRPHYC_DTDR1_DTBYTE7_Msk            /*!< Data training data: */
#define DDRPHYC_DTDR1_DTBYTE7_0   (0x1U << DDRPHYC_DTDR1_DTBYTE7_Pos)  /*!< 0x01000000 */
#define DDRPHYC_DTDR1_DTBYTE7_1   (0x2U << DDRPHYC_DTDR1_DTBYTE7_Pos)  /*!< 0x02000000 */
#define DDRPHYC_DTDR1_DTBYTE7_2   (0x4U << DDRPHYC_DTDR1_DTBYTE7_Pos)  /*!< 0x04000000 */
#define DDRPHYC_DTDR1_DTBYTE7_3   (0x8U << DDRPHYC_DTDR1_DTBYTE7_Pos)  /*!< 0x08000000 */
#define DDRPHYC_DTDR1_DTBYTE7_4   (0x10U << DDRPHYC_DTDR1_DTBYTE7_Pos) /*!< 0x10000000 */
#define DDRPHYC_DTDR1_DTBYTE7_5   (0x20U << DDRPHYC_DTDR1_DTBYTE7_Pos) /*!< 0x20000000 */
#define DDRPHYC_DTDR1_DTBYTE7_6   (0x40U << DDRPHYC_DTDR1_DTBYTE7_Pos) /*!< 0x40000000 */
#define DDRPHYC_DTDR1_DTBYTE7_7   (0x80U << DDRPHYC_DTDR1_DTBYTE7_Pos) /*!< 0x80000000 */

/*****************  Bit definition for DDRPHYC_GPR0 register  *****************/
#define DDRPHYC_GPR0_GPR0_Pos (0U)
#define DDRPHYC_GPR0_GPR0_Msk (0xFFFFFFFFU << DDRPHYC_GPR0_GPR0_Pos) /*!< 0xFFFFFFFF */
#define DDRPHYC_GPR0_GPR0     DDRPHYC_GPR0_GPR0_Msk                  /*!< General purpose register 0 bits */
#define DDRPHYC_GPR0_GPR0_0   (0x1U << DDRPHYC_GPR0_GPR0_Pos)        /*!< 0x00000001 */
#define DDRPHYC_GPR0_GPR0_1   (0x2U << DDRPHYC_GPR0_GPR0_Pos)        /*!< 0x00000002 */
#define DDRPHYC_GPR0_GPR0_2   (0x4U << DDRPHYC_GPR0_GPR0_Pos)        /*!< 0x00000004 */
#define DDRPHYC_GPR0_GPR0_3   (0x8U << DDRPHYC_GPR0_GPR0_Pos)        /*!< 0x00000008 */
#define DDRPHYC_GPR0_GPR0_4   (0x10U << DDRPHYC_GPR0_GPR0_Pos)       /*!< 0x00000010 */
#define DDRPHYC_GPR0_GPR0_5   (0x20U << DDRPHYC_GPR0_GPR0_Pos)       /*!< 0x00000020 */
#define DDRPHYC_GPR0_GPR0_6   (0x40U << DDRPHYC_GPR0_GPR0_Pos)       /*!< 0x00000040 */
#define DDRPHYC_GPR0_GPR0_7   (0x80U << DDRPHYC_GPR0_GPR0_Pos)       /*!< 0x00000080 */
#define DDRPHYC_GPR0_GPR0_8   (0x100U << DDRPHYC_GPR0_GPR0_Pos)      /*!< 0x00000100 */
#define DDRPHYC_GPR0_GPR0_9   (0x200U << DDRPHYC_GPR0_GPR0_Pos)      /*!< 0x00000200 */
#define DDRPHYC_GPR0_GPR0_10  (0x400U << DDRPHYC_GPR0_GPR0_Pos)      /*!< 0x00000400 */
#define DDRPHYC_GPR0_GPR0_11  (0x800U << DDRPHYC_GPR0_GPR0_Pos)      /*!< 0x00000800 */
#define DDRPHYC_GPR0_GPR0_12  (0x1000U << DDRPHYC_GPR0_GPR0_Pos)     /*!< 0x00001000 */
#define DDRPHYC_GPR0_GPR0_13  (0x2000U << DDRPHYC_GPR0_GPR0_Pos)     /*!< 0x00002000 */
#define DDRPHYC_GPR0_GPR0_14  (0x4000U << DDRPHYC_GPR0_GPR0_Pos)     /*!< 0x00004000 */
#define DDRPHYC_GPR0_GPR0_15  (0x8000U << DDRPHYC_GPR0_GPR0_Pos)     /*!< 0x00008000 */
#define DDRPHYC_GPR0_GPR0_16  (0x10000U << DDRPHYC_GPR0_GPR0_Pos)    /*!< 0x00010000 */
#define DDRPHYC_GPR0_GPR0_17  (0x20000U << DDRPHYC_GPR0_GPR0_Pos)    /*!< 0x00020000 */
#define DDRPHYC_GPR0_GPR0_18  (0x40000U << DDRPHYC_GPR0_GPR0_Pos)    /*!< 0x00040000 */
#define DDRPHYC_GPR0_GPR0_19  (0x80000U << DDRPHYC_GPR0_GPR0_Pos)    /*!< 0x00080000 */
#define DDRPHYC_GPR0_GPR0_20  (0x100000U << DDRPHYC_GPR0_GPR0_Pos)   /*!< 0x00100000 */
#define DDRPHYC_GPR0_GPR0_21  (0x200000U << DDRPHYC_GPR0_GPR0_Pos)   /*!< 0x00200000 */
#define DDRPHYC_GPR0_GPR0_22  (0x400000U << DDRPHYC_GPR0_GPR0_Pos)   /*!< 0x00400000 */
#define DDRPHYC_GPR0_GPR0_23  (0x800000U << DDRPHYC_GPR0_GPR0_Pos)   /*!< 0x00800000 */
#define DDRPHYC_GPR0_GPR0_24  (0x1000000U << DDRPHYC_GPR0_GPR0_Pos)  /*!< 0x01000000 */
#define DDRPHYC_GPR0_GPR0_25  (0x2000000U << DDRPHYC_GPR0_GPR0_Pos)  /*!< 0x02000000 */
#define DDRPHYC_GPR0_GPR0_26  (0x4000000U << DDRPHYC_GPR0_GPR0_Pos)  /*!< 0x04000000 */
#define DDRPHYC_GPR0_GPR0_27  (0x8000000U << DDRPHYC_GPR0_GPR0_Pos)  /*!< 0x08000000 */
#define DDRPHYC_GPR0_GPR0_28  (0x10000000U << DDRPHYC_GPR0_GPR0_Pos) /*!< 0x10000000 */
#define DDRPHYC_GPR0_GPR0_29  (0x20000000U << DDRPHYC_GPR0_GPR0_Pos) /*!< 0x20000000 */
#define DDRPHYC_GPR0_GPR0_30  (0x40000000U << DDRPHYC_GPR0_GPR0_Pos) /*!< 0x40000000 */
#define DDRPHYC_GPR0_GPR0_31  (0x80000000U << DDRPHYC_GPR0_GPR0_Pos) /*!< 0x80000000 */

/*****************  Bit definition for DDRPHYC_GPR1 register  *****************/
#define DDRPHYC_GPR1_GPR1_Pos (0U)
#define DDRPHYC_GPR1_GPR1_Msk (0xFFFFFFFFU << DDRPHYC_GPR1_GPR1_Pos) /*!< 0xFFFFFFFF */
#define DDRPHYC_GPR1_GPR1     DDRPHYC_GPR1_GPR1_Msk                  /*!< General purpose register 1 bits */
#define DDRPHYC_GPR1_GPR1_0   (0x1U << DDRPHYC_GPR1_GPR1_Pos)        /*!< 0x00000001 */
#define DDRPHYC_GPR1_GPR1_1   (0x2U << DDRPHYC_GPR1_GPR1_Pos)        /*!< 0x00000002 */
#define DDRPHYC_GPR1_GPR1_2   (0x4U << DDRPHYC_GPR1_GPR1_Pos)        /*!< 0x00000004 */
#define DDRPHYC_GPR1_GPR1_3   (0x8U << DDRPHYC_GPR1_GPR1_Pos)        /*!< 0x00000008 */
#define DDRPHYC_GPR1_GPR1_4   (0x10U << DDRPHYC_GPR1_GPR1_Pos)       /*!< 0x00000010 */
#define DDRPHYC_GPR1_GPR1_5   (0x20U << DDRPHYC_GPR1_GPR1_Pos)       /*!< 0x00000020 */
#define DDRPHYC_GPR1_GPR1_6   (0x40U << DDRPHYC_GPR1_GPR1_Pos)       /*!< 0x00000040 */
#define DDRPHYC_GPR1_GPR1_7   (0x80U << DDRPHYC_GPR1_GPR1_Pos)       /*!< 0x00000080 */
#define DDRPHYC_GPR1_GPR1_8   (0x100U << DDRPHYC_GPR1_GPR1_Pos)      /*!< 0x00000100 */
#define DDRPHYC_GPR1_GPR1_9   (0x200U << DDRPHYC_GPR1_GPR1_Pos)      /*!< 0x00000200 */
#define DDRPHYC_GPR1_GPR1_10  (0x400U << DDRPHYC_GPR1_GPR1_Pos)      /*!< 0x00000400 */
#define DDRPHYC_GPR1_GPR1_11  (0x800U << DDRPHYC_GPR1_GPR1_Pos)      /*!< 0x00000800 */
#define DDRPHYC_GPR1_GPR1_12  (0x1000U << DDRPHYC_GPR1_GPR1_Pos)     /*!< 0x00001000 */
#define DDRPHYC_GPR1_GPR1_13  (0x2000U << DDRPHYC_GPR1_GPR1_Pos)     /*!< 0x00002000 */
#define DDRPHYC_GPR1_GPR1_14  (0x4000U << DDRPHYC_GPR1_GPR1_Pos)     /*!< 0x00004000 */
#define DDRPHYC_GPR1_GPR1_15  (0x8000U << DDRPHYC_GPR1_GPR1_Pos)     /*!< 0x00008000 */
#define DDRPHYC_GPR1_GPR1_16  (0x10000U << DDRPHYC_GPR1_GPR1_Pos)    /*!< 0x00010000 */
#define DDRPHYC_GPR1_GPR1_17  (0x20000U << DDRPHYC_GPR1_GPR1_Pos)    /*!< 0x00020000 */
#define DDRPHYC_GPR1_GPR1_18  (0x40000U << DDRPHYC_GPR1_GPR1_Pos)    /*!< 0x00040000 */
#define DDRPHYC_GPR1_GPR1_19  (0x80000U << DDRPHYC_GPR1_GPR1_Pos)    /*!< 0x00080000 */
#define DDRPHYC_GPR1_GPR1_20  (0x100000U << DDRPHYC_GPR1_GPR1_Pos)   /*!< 0x00100000 */
#define DDRPHYC_GPR1_GPR1_21  (0x200000U << DDRPHYC_GPR1_GPR1_Pos)   /*!< 0x00200000 */
#define DDRPHYC_GPR1_GPR1_22  (0x400000U << DDRPHYC_GPR1_GPR1_Pos)   /*!< 0x00400000 */
#define DDRPHYC_GPR1_GPR1_23  (0x800000U << DDRPHYC_GPR1_GPR1_Pos)   /*!< 0x00800000 */
#define DDRPHYC_GPR1_GPR1_24  (0x1000000U << DDRPHYC_GPR1_GPR1_Pos)  /*!< 0x01000000 */
#define DDRPHYC_GPR1_GPR1_25  (0x2000000U << DDRPHYC_GPR1_GPR1_Pos)  /*!< 0x02000000 */
#define DDRPHYC_GPR1_GPR1_26  (0x4000000U << DDRPHYC_GPR1_GPR1_Pos)  /*!< 0x04000000 */
#define DDRPHYC_GPR1_GPR1_27  (0x8000000U << DDRPHYC_GPR1_GPR1_Pos)  /*!< 0x08000000 */
#define DDRPHYC_GPR1_GPR1_28  (0x10000000U << DDRPHYC_GPR1_GPR1_Pos) /*!< 0x10000000 */
#define DDRPHYC_GPR1_GPR1_29  (0x20000000U << DDRPHYC_GPR1_GPR1_Pos) /*!< 0x20000000 */
#define DDRPHYC_GPR1_GPR1_30  (0x40000000U << DDRPHYC_GPR1_GPR1_Pos) /*!< 0x40000000 */
#define DDRPHYC_GPR1_GPR1_31  (0x80000000U << DDRPHYC_GPR1_GPR1_Pos) /*!< 0x80000000 */

/****************  Bit definition for DDRPHYC_ZQ0CR0 register  ****************/
#define DDRPHYC_ZQ0CR0_ZDATA_Pos   (0U)
#define DDRPHYC_ZQ0CR0_ZDATA_Msk   (0xFFFFFU << DDRPHYC_ZQ0CR0_ZDATA_Pos) /*!< 0x000FFFFF */
#define DDRPHYC_ZQ0CR0_ZDATA       DDRPHYC_ZQ0CR0_ZDATA_Msk               /*!< Impedance override */
#define DDRPHYC_ZQ0CR0_ZDATA_0     (0x1U << DDRPHYC_ZQ0CR0_ZDATA_Pos)     /*!< 0x00000001 */
#define DDRPHYC_ZQ0CR0_ZDATA_1     (0x2U << DDRPHYC_ZQ0CR0_ZDATA_Pos)     /*!< 0x00000002 */
#define DDRPHYC_ZQ0CR0_ZDATA_2     (0x4U << DDRPHYC_ZQ0CR0_ZDATA_Pos)     /*!< 0x00000004 */
#define DDRPHYC_ZQ0CR0_ZDATA_3     (0x8U << DDRPHYC_ZQ0CR0_ZDATA_Pos)     /*!< 0x00000008 */
#define DDRPHYC_ZQ0CR0_ZDATA_4     (0x10U << DDRPHYC_ZQ0CR0_ZDATA_Pos)    /*!< 0x00000010 */
#define DDRPHYC_ZQ0CR0_ZDATA_5     (0x20U << DDRPHYC_ZQ0CR0_ZDATA_Pos)    /*!< 0x00000020 */
#define DDRPHYC_ZQ0CR0_ZDATA_6     (0x40U << DDRPHYC_ZQ0CR0_ZDATA_Pos)    /*!< 0x00000040 */
#define DDRPHYC_ZQ0CR0_ZDATA_7     (0x80U << DDRPHYC_ZQ0CR0_ZDATA_Pos)    /*!< 0x00000080 */
#define DDRPHYC_ZQ0CR0_ZDATA_8     (0x100U << DDRPHYC_ZQ0CR0_ZDATA_Pos)   /*!< 0x00000100 */
#define DDRPHYC_ZQ0CR0_ZDATA_9     (0x200U << DDRPHYC_ZQ0CR0_ZDATA_Pos)   /*!< 0x00000200 */
#define DDRPHYC_ZQ0CR0_ZDATA_10    (0x400U << DDRPHYC_ZQ0CR0_ZDATA_Pos)   /*!< 0x00000400 */
#define DDRPHYC_ZQ0CR0_ZDATA_11    (0x800U << DDRPHYC_ZQ0CR0_ZDATA_Pos)   /*!< 0x00000800 */
#define DDRPHYC_ZQ0CR0_ZDATA_12    (0x1000U << DDRPHYC_ZQ0CR0_ZDATA_Pos)  /*!< 0x00001000 */
#define DDRPHYC_ZQ0CR0_ZDATA_13    (0x2000U << DDRPHYC_ZQ0CR0_ZDATA_Pos)  /*!< 0x00002000 */
#define DDRPHYC_ZQ0CR0_ZDATA_14    (0x4000U << DDRPHYC_ZQ0CR0_ZDATA_Pos)  /*!< 0x00004000 */
#define DDRPHYC_ZQ0CR0_ZDATA_15    (0x8000U << DDRPHYC_ZQ0CR0_ZDATA_Pos)  /*!< 0x00008000 */
#define DDRPHYC_ZQ0CR0_ZDATA_16    (0x10000U << DDRPHYC_ZQ0CR0_ZDATA_Pos) /*!< 0x00010000 */
#define DDRPHYC_ZQ0CR0_ZDATA_17    (0x20000U << DDRPHYC_ZQ0CR0_ZDATA_Pos) /*!< 0x00020000 */
#define DDRPHYC_ZQ0CR0_ZDATA_18    (0x40000U << DDRPHYC_ZQ0CR0_ZDATA_Pos) /*!< 0x00040000 */
#define DDRPHYC_ZQ0CR0_ZDATA_19    (0x80000U << DDRPHYC_ZQ0CR0_ZDATA_Pos) /*!< 0x00080000 */
#define DDRPHYC_ZQ0CR0_ZDEN_Pos    (28U)
#define DDRPHYC_ZQ0CR0_ZDEN_Msk    (0x1U << DDRPHYC_ZQ0CR0_ZDEN_Pos)      /*!< 0x10000000 */
#define DDRPHYC_ZQ0CR0_ZDEN        DDRPHYC_ZQ0CR0_ZDEN_Msk                /*!< Impedance override enable */
#define DDRPHYC_ZQ0CR0_ZCALBYP_Pos (29U)
#define DDRPHYC_ZQ0CR0_ZCALBYP_Msk (0x1U << DDRPHYC_ZQ0CR0_ZCALBYP_Pos)   /*!< 0x20000000 */
#define DDRPHYC_ZQ0CR0_ZCALBYP     DDRPHYC_ZQ0CR0_ZCALBYP_Msk             /*!< Impedance calibration bypass */
#define DDRPHYC_ZQ0CR0_ZCAL_Pos    (30U)
#define DDRPHYC_ZQ0CR0_ZCAL_Msk    (0x1U << DDRPHYC_ZQ0CR0_ZCAL_Pos)      /*!< 0x40000000 */
#define DDRPHYC_ZQ0CR0_ZCAL        DDRPHYC_ZQ0CR0_ZCAL_Msk                /*!< ZCAL trigger */
#define DDRPHYC_ZQ0CR0_ZQPD_Pos    (31U)
#define DDRPHYC_ZQ0CR0_ZQPD_Msk    (0x1U << DDRPHYC_ZQ0CR0_ZQPD_Pos)      /*!< 0x80000000 */
#define DDRPHYC_ZQ0CR0_ZQPD        DDRPHYC_ZQ0CR0_ZQPD_Msk                /*!< ZCAL power down */

/****************  Bit definition for DDRPHYC_ZQ0CR1 register  ****************/
#define DDRPHYC_ZQ0CR1_ZPROG_Pos (0U)
#define DDRPHYC_ZQ0CR1_ZPROG_Msk (0xFFU << DDRPHYC_ZQ0CR1_ZPROG_Pos) /*!< 0x000000FF */
#define DDRPHYC_ZQ0CR1_ZPROG     DDRPHYC_ZQ0CR1_ZPROG_Msk            /*!< Impedance divide ratio to ext R */
#define DDRPHYC_ZQ0CR1_ZPROG_0   (0x1U << DDRPHYC_ZQ0CR1_ZPROG_Pos)  /*!< 0x00000001 */
#define DDRPHYC_ZQ0CR1_ZPROG_1   (0x2U << DDRPHYC_ZQ0CR1_ZPROG_Pos)  /*!< 0x00000002 */
#define DDRPHYC_ZQ0CR1_ZPROG_2   (0x4U << DDRPHYC_ZQ0CR1_ZPROG_Pos)  /*!< 0x00000004 */
#define DDRPHYC_ZQ0CR1_ZPROG_3   (0x8U << DDRPHYC_ZQ0CR1_ZPROG_Pos)  /*!< 0x00000008 */
#define DDRPHYC_ZQ0CR1_ZPROG_4   (0x10U << DDRPHYC_ZQ0CR1_ZPROG_Pos) /*!< 0x00000010 */
#define DDRPHYC_ZQ0CR1_ZPROG_5   (0x20U << DDRPHYC_ZQ0CR1_ZPROG_Pos) /*!< 0x00000020 */
#define DDRPHYC_ZQ0CR1_ZPROG_6   (0x40U << DDRPHYC_ZQ0CR1_ZPROG_Pos) /*!< 0x00000040 */
#define DDRPHYC_ZQ0CR1_ZPROG_7   (0x80U << DDRPHYC_ZQ0CR1_ZPROG_Pos) /*!< 0x00000080 */

/****************  Bit definition for DDRPHYC_ZQ0SR0 register  ****************/
#define DDRPHYC_ZQ0SR0_ZCTRL_Pos (0U)
#define DDRPHYC_ZQ0SR0_ZCTRL_Msk (0xFFFFFU << DDRPHYC_ZQ0SR0_ZCTRL_Pos) /*!< 0x000FFFFF */
#define DDRPHYC_ZQ0SR0_ZCTRL     DDRPHYC_ZQ0SR0_ZCTRL_Msk               /*!< Impedance control */
#define DDRPHYC_ZQ0SR0_ZCTRL_0   (0x1U << DDRPHYC_ZQ0SR0_ZCTRL_Pos)     /*!< 0x00000001 */
#define DDRPHYC_ZQ0SR0_ZCTRL_1   (0x2U << DDRPHYC_ZQ0SR0_ZCTRL_Pos)     /*!< 0x00000002 */
#define DDRPHYC_ZQ0SR0_ZCTRL_2   (0x4U << DDRPHYC_ZQ0SR0_ZCTRL_Pos)     /*!< 0x00000004 */
#define DDRPHYC_ZQ0SR0_ZCTRL_3   (0x8U << DDRPHYC_ZQ0SR0_ZCTRL_Pos)     /*!< 0x00000008 */
#define DDRPHYC_ZQ0SR0_ZCTRL_4   (0x10U << DDRPHYC_ZQ0SR0_ZCTRL_Pos)    /*!< 0x00000010 */
#define DDRPHYC_ZQ0SR0_ZCTRL_5   (0x20U << DDRPHYC_ZQ0SR0_ZCTRL_Pos)    /*!< 0x00000020 */
#define DDRPHYC_ZQ0SR0_ZCTRL_6   (0x40U << DDRPHYC_ZQ0SR0_ZCTRL_Pos)    /*!< 0x00000040 */
#define DDRPHYC_ZQ0SR0_ZCTRL_7   (0x80U << DDRPHYC_ZQ0SR0_ZCTRL_Pos)    /*!< 0x00000080 */
#define DDRPHYC_ZQ0SR0_ZCTRL_8   (0x100U << DDRPHYC_ZQ0SR0_ZCTRL_Pos)   /*!< 0x00000100 */
#define DDRPHYC_ZQ0SR0_ZCTRL_9   (0x200U << DDRPHYC_ZQ0SR0_ZCTRL_Pos)   /*!< 0x00000200 */
#define DDRPHYC_ZQ0SR0_ZCTRL_10  (0x400U << DDRPHYC_ZQ0SR0_ZCTRL_Pos)   /*!< 0x00000400 */
#define DDRPHYC_ZQ0SR0_ZCTRL_11  (0x800U << DDRPHYC_ZQ0SR0_ZCTRL_Pos)   /*!< 0x00000800 */
#define DDRPHYC_ZQ0SR0_ZCTRL_12  (0x1000U << DDRPHYC_ZQ0SR0_ZCTRL_Pos)  /*!< 0x00001000 */
#define DDRPHYC_ZQ0SR0_ZCTRL_13  (0x2000U << DDRPHYC_ZQ0SR0_ZCTRL_Pos)  /*!< 0x00002000 */
#define DDRPHYC_ZQ0SR0_ZCTRL_14  (0x4000U << DDRPHYC_ZQ0SR0_ZCTRL_Pos)  /*!< 0x00004000 */
#define DDRPHYC_ZQ0SR0_ZCTRL_15  (0x8000U << DDRPHYC_ZQ0SR0_ZCTRL_Pos)  /*!< 0x00008000 */
#define DDRPHYC_ZQ0SR0_ZCTRL_16  (0x10000U << DDRPHYC_ZQ0SR0_ZCTRL_Pos) /*!< 0x00010000 */
#define DDRPHYC_ZQ0SR0_ZCTRL_17  (0x20000U << DDRPHYC_ZQ0SR0_ZCTRL_Pos) /*!< 0x00020000 */
#define DDRPHYC_ZQ0SR0_ZCTRL_18  (0x40000U << DDRPHYC_ZQ0SR0_ZCTRL_Pos) /*!< 0x00040000 */
#define DDRPHYC_ZQ0SR0_ZCTRL_19  (0x80000U << DDRPHYC_ZQ0SR0_ZCTRL_Pos) /*!< 0x00080000 */
#define DDRPHYC_ZQ0SR0_ZERR_Pos  (30U)
#define DDRPHYC_ZQ0SR0_ZERR_Msk  (0x1U << DDRPHYC_ZQ0SR0_ZERR_Pos)      /*!< 0x40000000 */
#define DDRPHYC_ZQ0SR0_ZERR      DDRPHYC_ZQ0SR0_ZERR_Msk                /*!< Impedance calibration error */
#define DDRPHYC_ZQ0SR0_ZDONE_Pos (31U)
#define DDRPHYC_ZQ0SR0_ZDONE_Msk (0x1U << DDRPHYC_ZQ0SR0_ZDONE_Pos)     /*!< 0x80000000 */
#define DDRPHYC_ZQ0SR0_ZDONE     DDRPHYC_ZQ0SR0_ZDONE_Msk               /*!< Impedance calibration done */

/****************  Bit definition for DDRPHYC_ZQ0SR1 register  ****************/
#define DDRPHYC_ZQ0SR1_ZPD_Pos (0U)
#define DDRPHYC_ZQ0SR1_ZPD_Msk (0x3U << DDRPHYC_ZQ0SR1_ZPD_Pos) /*!< 0x00000003 */
#define DDRPHYC_ZQ0SR1_ZPD     DDRPHYC_ZQ0SR1_ZPD_Msk           /*!< zpd calibration status */
#define DDRPHYC_ZQ0SR1_ZPD_0   (0x1U << DDRPHYC_ZQ0SR1_ZPD_Pos) /*!< 0x00000001 */
#define DDRPHYC_ZQ0SR1_ZPD_1   (0x2U << DDRPHYC_ZQ0SR1_ZPD_Pos) /*!< 0x00000002 */
#define DDRPHYC_ZQ0SR1_ZPU_Pos (2U)
#define DDRPHYC_ZQ0SR1_ZPU_Msk (0x3U << DDRPHYC_ZQ0SR1_ZPU_Pos) /*!< 0x0000000C */
#define DDRPHYC_ZQ0SR1_ZPU     DDRPHYC_ZQ0SR1_ZPU_Msk           /*!< zpu calibration status */
#define DDRPHYC_ZQ0SR1_ZPU_0   (0x1U << DDRPHYC_ZQ0SR1_ZPU_Pos) /*!< 0x00000004 */
#define DDRPHYC_ZQ0SR1_ZPU_1   (0x2U << DDRPHYC_ZQ0SR1_ZPU_Pos) /*!< 0x00000008 */
#define DDRPHYC_ZQ0SR1_OPD_Pos (4U)
#define DDRPHYC_ZQ0SR1_OPD_Msk (0x3U << DDRPHYC_ZQ0SR1_OPD_Pos) /*!< 0x00000030 */
#define DDRPHYC_ZQ0SR1_OPD     DDRPHYC_ZQ0SR1_OPD_Msk           /*!< opd calibration status */
#define DDRPHYC_ZQ0SR1_OPD_0   (0x1U << DDRPHYC_ZQ0SR1_OPD_Pos) /*!< 0x00000010 */
#define DDRPHYC_ZQ0SR1_OPD_1   (0x2U << DDRPHYC_ZQ0SR1_OPD_Pos) /*!< 0x00000020 */
#define DDRPHYC_ZQ0SR1_OPU_Pos (6U)
#define DDRPHYC_ZQ0SR1_OPU_Msk (0x3U << DDRPHYC_ZQ0SR1_OPU_Pos) /*!< 0x000000C0 */
#define DDRPHYC_ZQ0SR1_OPU     DDRPHYC_ZQ0SR1_OPU_Msk           /*!< opu calibration status */
#define DDRPHYC_ZQ0SR1_OPU_0   (0x1U << DDRPHYC_ZQ0SR1_OPU_Pos) /*!< 0x00000040 */
#define DDRPHYC_ZQ0SR1_OPU_1   (0x2U << DDRPHYC_ZQ0SR1_OPU_Pos) /*!< 0x00000080 */

/****************  Bit definition for DDRPHYC_DX0GCR register  ****************/
#define DDRPHYC_DX0GCR_DXEN_Pos   (0U)
#define DDRPHYC_DX0GCR_DXEN_Msk   (0x1U << DDRPHYC_DX0GCR_DXEN_Pos)   /*!< 0x00000001 */
#define DDRPHYC_DX0GCR_DXEN       DDRPHYC_DX0GCR_DXEN_Msk             /*!< DATA byte enable */
#define DDRPHYC_DX0GCR_DQSODT_Pos (1U)
#define DDRPHYC_DX0GCR_DQSODT_Msk (0x1U << DDRPHYC_DX0GCR_DQSODT_Pos) /*!< 0x00000002 */
#define DDRPHYC_DX0GCR_DQSODT     DDRPHYC_DX0GCR_DQSODT_Msk           /*!< DQS ODT enable */
#define DDRPHYC_DX0GCR_DQODT_Pos  (2U)
#define DDRPHYC_DX0GCR_DQODT_Msk  (0x1U << DDRPHYC_DX0GCR_DQODT_Pos)  /*!< 0x00000004 */
#define DDRPHYC_DX0GCR_DQODT      DDRPHYC_DX0GCR_DQODT_Msk            /*!< DQ ODT enable */
#define DDRPHYC_DX0GCR_DXIOM_Pos  (3U)
#define DDRPHYC_DX0GCR_DXIOM_Msk  (0x1U << DDRPHYC_DX0GCR_DXIOM_Pos)  /*!< 0x00000008 */
#define DDRPHYC_DX0GCR_DXIOM      DDRPHYC_DX0GCR_DXIOM_Msk            /*!< Data I/O mode */
#define DDRPHYC_DX0GCR_DXPDD_Pos  (4U)
#define DDRPHYC_DX0GCR_DXPDD_Msk  (0x1U << DDRPHYC_DX0GCR_DXPDD_Pos)  /*!< 0x00000010 */
#define DDRPHYC_DX0GCR_DXPDD      DDRPHYC_DX0GCR_DXPDD_Msk            /*!< Data power-down driver */
#define DDRPHYC_DX0GCR_DXPDR_Pos  (5U)
#define DDRPHYC_DX0GCR_DXPDR_Msk  (0x1U << DDRPHYC_DX0GCR_DXPDR_Pos)  /*!< 0x00000020 */
#define DDRPHYC_DX0GCR_DXPDR      DDRPHYC_DX0GCR_DXPDR_Msk            /*!< Data power-down receiver */
#define DDRPHYC_DX0GCR_DQSRPD_Pos (6U)
#define DDRPHYC_DX0GCR_DQSRPD_Msk (0x1U << DDRPHYC_DX0GCR_DQSRPD_Pos) /*!< 0x00000040 */
#define DDRPHYC_DX0GCR_DQSRPD     DDRPHYC_DX0GCR_DQSRPD_Msk           /*!< DQSR power-down */
#define DDRPHYC_DX0GCR_DSEN_Pos   (7U)
#define DDRPHYC_DX0GCR_DSEN_Msk   (0x3U << DDRPHYC_DX0GCR_DSEN_Pos)   /*!< 0x00000180 */
#define DDRPHYC_DX0GCR_DSEN       DDRPHYC_DX0GCR_DSEN_Msk             /*!< Write DQS enable */
#define DDRPHYC_DX0GCR_DSEN_0     (0x1U << DDRPHYC_DX0GCR_DSEN_Pos)   /*!< 0x00000080 */
#define DDRPHYC_DX0GCR_DSEN_1     (0x2U << DDRPHYC_DX0GCR_DSEN_Pos)   /*!< 0x00000100 */
#define DDRPHYC_DX0GCR_DQSRTT_Pos (9U)
#define DDRPHYC_DX0GCR_DQSRTT_Msk (0x1U << DDRPHYC_DX0GCR_DQSRTT_Pos) /*!< 0x00000200 */
#define DDRPHYC_DX0GCR_DQSRTT     DDRPHYC_DX0GCR_DQSRTT_Msk           /*!< DQS dynamic RTT control */
#define DDRPHYC_DX0GCR_DQRTT_Pos  (10U)
#define DDRPHYC_DX0GCR_DQRTT_Msk  (0x1U << DDRPHYC_DX0GCR_DQRTT_Pos)  /*!< 0x00000400 */
#define DDRPHYC_DX0GCR_DQRTT      DDRPHYC_DX0GCR_DQRTT_Msk            /*!< DQ dynamic RTT control */
#define DDRPHYC_DX0GCR_RTTOH_Pos  (11U)
#define DDRPHYC_DX0GCR_RTTOH_Msk  (0x3U << DDRPHYC_DX0GCR_RTTOH_Pos)  /*!< 0x00001800 */
#define DDRPHYC_DX0GCR_RTTOH      DDRPHYC_DX0GCR_RTTOH_Msk            /*!< RTT output hold */
#define DDRPHYC_DX0GCR_RTTOH_0    (0x1U << DDRPHYC_DX0GCR_RTTOH_Pos)  /*!< 0x00000800 */
#define DDRPHYC_DX0GCR_RTTOH_1    (0x2U << DDRPHYC_DX0GCR_RTTOH_Pos)  /*!< 0x00001000 */
#define DDRPHYC_DX0GCR_RTTOAL_Pos (13U)
#define DDRPHYC_DX0GCR_RTTOAL_Msk (0x1U << DDRPHYC_DX0GCR_RTTOAL_Pos) /*!< 0x00002000 */
#define DDRPHYC_DX0GCR_RTTOAL     DDRPHYC_DX0GCR_RTTOAL_Msk           /*!< RTT ON additive latency */
#define DDRPHYC_DX0GCR_R0RVSL_Pos (14U)
#define DDRPHYC_DX0GCR_R0RVSL_Msk (0x7U << DDRPHYC_DX0GCR_R0RVSL_Pos) /*!< 0x0001C000 */
#define DDRPHYC_DX0GCR_R0RVSL     DDRPHYC_DX0GCR_R0RVSL_Msk           /*!< Read valid system latency in steps */
#define DDRPHYC_DX0GCR_R0RVSL_0   (0x1U << DDRPHYC_DX0GCR_R0RVSL_Pos) /*!< 0x00004000 */
#define DDRPHYC_DX0GCR_R0RVSL_1   (0x2U << DDRPHYC_DX0GCR_R0RVSL_Pos) /*!< 0x00008000 */
#define DDRPHYC_DX0GCR_R0RVSL_2   (0x4U << DDRPHYC_DX0GCR_R0RVSL_Pos) /*!< 0x00010000 */

/***************  Bit definition for DDRPHYC_DX0GSR0 register  ****************/
#define DDRPHYC_DX0GSR0_DTDONE_Pos (0U)
#define DDRPHYC_DX0GSR0_DTDONE_Msk (0x1U << DDRPHYC_DX0GSR0_DTDONE_Pos) /*!< 0x00000001 */
#define DDRPHYC_DX0GSR0_DTDONE     DDRPHYC_DX0GSR0_DTDONE_Msk           /*!< Data training done */
#define DDRPHYC_DX0GSR0_DTERR_Pos  (4U)
#define DDRPHYC_DX0GSR0_DTERR_Msk  (0x1U << DDRPHYC_DX0GSR0_DTERR_Pos)  /*!< 0x00000010 */
#define DDRPHYC_DX0GSR0_DTERR      DDRPHYC_DX0GSR0_DTERR_Msk            /*!< DQS gate training error */
#define DDRPHYC_DX0GSR0_DTIERR_Pos (8U)
#define DDRPHYC_DX0GSR0_DTIERR_Msk (0x1U << DDRPHYC_DX0GSR0_DTIERR_Pos) /*!< 0x00000100 */
#define DDRPHYC_DX0GSR0_DTIERR     DDRPHYC_DX0GSR0_DTIERR_Msk           /*!< DQS gate training intermittent error */
#define DDRPHYC_DX0GSR0_DTPASS_Pos (13U)
#define DDRPHYC_DX0GSR0_DTPASS_Msk (0x7U << DDRPHYC_DX0GSR0_DTPASS_Pos) /*!< 0x0000E000 */
#define DDRPHYC_DX0GSR0_DTPASS     DDRPHYC_DX0GSR0_DTPASS_Msk           /*!< DQS training pass count */
#define DDRPHYC_DX0GSR0_DTPASS_0   (0x1U << DDRPHYC_DX0GSR0_DTPASS_Pos) /*!< 0x00002000 */
#define DDRPHYC_DX0GSR0_DTPASS_1   (0x2U << DDRPHYC_DX0GSR0_DTPASS_Pos) /*!< 0x00004000 */
#define DDRPHYC_DX0GSR0_DTPASS_2   (0x4U << DDRPHYC_DX0GSR0_DTPASS_Pos) /*!< 0x00008000 */

/***************  Bit definition for DDRPHYC_DX0GSR1 register  ****************/
#define DDRPHYC_DX0GSR1_DFTERR_Pos (0U)
#define DDRPHYC_DX0GSR1_DFTERR_Msk (0x1U << DDRPHYC_DX0GSR1_DFTERR_Pos) /*!< 0x00000001 */
#define DDRPHYC_DX0GSR1_DFTERR     DDRPHYC_DX0GSR1_DFTERR_Msk           /*!< DQS drift error */
#define DDRPHYC_DX0GSR1_DQSDFT_Pos (4U)
#define DDRPHYC_DX0GSR1_DQSDFT_Msk (0x3U << DDRPHYC_DX0GSR1_DQSDFT_Pos) /*!< 0x00000030 */
#define DDRPHYC_DX0GSR1_DQSDFT     DDRPHYC_DX0GSR1_DQSDFT_Msk           /*!< DQS drift value */
#define DDRPHYC_DX0GSR1_DQSDFT_0   (0x1U << DDRPHYC_DX0GSR1_DQSDFT_Pos) /*!< 0x00000010 */
#define DDRPHYC_DX0GSR1_DQSDFT_1   (0x2U << DDRPHYC_DX0GSR1_DQSDFT_Pos) /*!< 0x00000020 */
#define DDRPHYC_DX0GSR1_RVERR_Pos  (12U)
#define DDRPHYC_DX0GSR1_RVERR_Msk  (0x1U << DDRPHYC_DX0GSR1_RVERR_Pos)  /*!< 0x00001000 */
#define DDRPHYC_DX0GSR1_RVERR      DDRPHYC_DX0GSR1_RVERR_Msk            /*!< RV training error */
#define DDRPHYC_DX0GSR1_RVIERR_Pos (16U)
#define DDRPHYC_DX0GSR1_RVIERR_Msk (0x1U << DDRPHYC_DX0GSR1_RVIERR_Pos) /*!< 0x00010000 */
#define DDRPHYC_DX0GSR1_RVIERR     DDRPHYC_DX0GSR1_RVIERR_Msk           /*!< RV intermittent error for rank */
#define DDRPHYC_DX0GSR1_RVPASS_Pos (20U)
#define DDRPHYC_DX0GSR1_RVPASS_Msk (0x7U << DDRPHYC_DX0GSR1_RVPASS_Pos) /*!< 0x00700000 */
#define DDRPHYC_DX0GSR1_RVPASS     DDRPHYC_DX0GSR1_RVPASS_Msk           /*!< Read valid training pass count */
#define DDRPHYC_DX0GSR1_RVPASS_0   (0x1U << DDRPHYC_DX0GSR1_RVPASS_Pos) /*!< 0x00100000 */
#define DDRPHYC_DX0GSR1_RVPASS_1   (0x2U << DDRPHYC_DX0GSR1_RVPASS_Pos) /*!< 0x00200000 */
#define DDRPHYC_DX0GSR1_RVPASS_2   (0x4U << DDRPHYC_DX0GSR1_RVPASS_Pos) /*!< 0x00400000 */

/***************  Bit definition for DDRPHYC_DX0DLLCR register  ***************/
#define DDRPHYC_DX0DLLCR_SFBDLY_Pos   (0U)
#define DDRPHYC_DX0DLLCR_SFBDLY_Msk   (0x7U << DDRPHYC_DX0DLLCR_SFBDLY_Pos)   /*!< 0x00000007 */
#define DDRPHYC_DX0DLLCR_SFBDLY       DDRPHYC_DX0DLLCR_SFBDLY_Msk             /*!< Slave DLL feed-back trim */
#define DDRPHYC_DX0DLLCR_SFBDLY_0     (0x1U << DDRPHYC_DX0DLLCR_SFBDLY_Pos)   /*!< 0x00000001 */
#define DDRPHYC_DX0DLLCR_SFBDLY_1     (0x2U << DDRPHYC_DX0DLLCR_SFBDLY_Pos)   /*!< 0x00000002 */
#define DDRPHYC_DX0DLLCR_SFBDLY_2     (0x4U << DDRPHYC_DX0DLLCR_SFBDLY_Pos)   /*!< 0x00000004 */
#define DDRPHYC_DX0DLLCR_SFWDLY_Pos   (3U)
#define DDRPHYC_DX0DLLCR_SFWDLY_Msk   (0x7U << DDRPHYC_DX0DLLCR_SFWDLY_Pos)   /*!< 0x00000038 */
#define DDRPHYC_DX0DLLCR_SFWDLY       DDRPHYC_DX0DLLCR_SFWDLY_Msk             /*!< Slave DLL feed-forward trim */
#define DDRPHYC_DX0DLLCR_SFWDLY_0     (0x1U << DDRPHYC_DX0DLLCR_SFWDLY_Pos)   /*!< 0x00000008 */
#define DDRPHYC_DX0DLLCR_SFWDLY_1     (0x2U << DDRPHYC_DX0DLLCR_SFWDLY_Pos)   /*!< 0x00000010 */
#define DDRPHYC_DX0DLLCR_SFWDLY_2     (0x4U << DDRPHYC_DX0DLLCR_SFWDLY_Pos)   /*!< 0x00000020 */
#define DDRPHYC_DX0DLLCR_MFBDLY_Pos   (6U)
#define DDRPHYC_DX0DLLCR_MFBDLY_Msk   (0x7U << DDRPHYC_DX0DLLCR_MFBDLY_Pos)   /*!< 0x000001C0 */
#define DDRPHYC_DX0DLLCR_MFBDLY       DDRPHYC_DX0DLLCR_MFBDLY_Msk             /*!< Master DLL feed-back trim */
#define DDRPHYC_DX0DLLCR_MFBDLY_0     (0x1U << DDRPHYC_DX0DLLCR_MFBDLY_Pos)   /*!< 0x00000040 */
#define DDRPHYC_DX0DLLCR_MFBDLY_1     (0x2U << DDRPHYC_DX0DLLCR_MFBDLY_Pos)   /*!< 0x00000080 */
#define DDRPHYC_DX0DLLCR_MFBDLY_2     (0x4U << DDRPHYC_DX0DLLCR_MFBDLY_Pos)   /*!< 0x00000100 */
#define DDRPHYC_DX0DLLCR_MFWDLY_Pos   (9U)
#define DDRPHYC_DX0DLLCR_MFWDLY_Msk   (0x7U << DDRPHYC_DX0DLLCR_MFWDLY_Pos)   /*!< 0x00000E00 */
#define DDRPHYC_DX0DLLCR_MFWDLY       DDRPHYC_DX0DLLCR_MFWDLY_Msk             /*!< Master DLL feed-forward trim */
#define DDRPHYC_DX0DLLCR_MFWDLY_0     (0x1U << DDRPHYC_DX0DLLCR_MFWDLY_Pos)   /*!< 0x00000200 */
#define DDRPHYC_DX0DLLCR_MFWDLY_1     (0x2U << DDRPHYC_DX0DLLCR_MFWDLY_Pos)   /*!< 0x00000400 */
#define DDRPHYC_DX0DLLCR_MFWDLY_2     (0x4U << DDRPHYC_DX0DLLCR_MFWDLY_Pos)   /*!< 0x00000800 */
#define DDRPHYC_DX0DLLCR_SSTART_Pos   (12U)
#define DDRPHYC_DX0DLLCR_SSTART_Msk   (0x3U << DDRPHYC_DX0DLLCR_SSTART_Pos)   /*!< 0x00003000 */
#define DDRPHYC_DX0DLLCR_SSTART       DDRPHYC_DX0DLLCR_SSTART_Msk             /*!< Slave DLL autostart */
#define DDRPHYC_DX0DLLCR_SSTART_0     (0x1U << DDRPHYC_DX0DLLCR_SSTART_Pos)   /*!< 0x00001000 */
#define DDRPHYC_DX0DLLCR_SSTART_1     (0x2U << DDRPHYC_DX0DLLCR_SSTART_Pos)   /*!< 0x00002000 */
#define DDRPHYC_DX0DLLCR_SDPHASE_Pos  (14U)
#define DDRPHYC_DX0DLLCR_SDPHASE_Msk  (0xFU << DDRPHYC_DX0DLLCR_SDPHASE_Pos)  /*!< 0x0003C000 */
#define DDRPHYC_DX0DLLCR_SDPHASE      DDRPHYC_DX0DLLCR_SDPHASE_Msk            /*!< Slave DLL phase */
#define DDRPHYC_DX0DLLCR_SDPHASE_0    (0x1U << DDRPHYC_DX0DLLCR_SDPHASE_Pos)  /*!< 0x00004000 */
#define DDRPHYC_DX0DLLCR_SDPHASE_1    (0x2U << DDRPHYC_DX0DLLCR_SDPHASE_Pos)  /*!< 0x00008000 */
#define DDRPHYC_DX0DLLCR_SDPHASE_2    (0x4U << DDRPHYC_DX0DLLCR_SDPHASE_Pos)  /*!< 0x00010000 */
#define DDRPHYC_DX0DLLCR_SDPHASE_3    (0x8U << DDRPHYC_DX0DLLCR_SDPHASE_Pos)  /*!< 0x00020000 */
#define DDRPHYC_DX0DLLCR_ATESTEN_Pos  (18U)
#define DDRPHYC_DX0DLLCR_ATESTEN_Msk  (0x1U << DDRPHYC_DX0DLLCR_ATESTEN_Pos)  /*!< 0x00040000 */
#define DDRPHYC_DX0DLLCR_ATESTEN      DDRPHYC_DX0DLLCR_ATESTEN_Msk            /*!< Enable path to pin 'ATO' */
#define DDRPHYC_DX0DLLCR_SDLBMODE_Pos (19U)
#define DDRPHYC_DX0DLLCR_SDLBMODE_Msk (0x1U << DDRPHYC_DX0DLLCR_SDLBMODE_Pos) /*!< 0x00080000 */
#define DDRPHYC_DX0DLLCR_SDLBMODE     DDRPHYC_DX0DLLCR_SDLBMODE_Msk           /*!< Bypass slave DLL during loopback */
#define DDRPHYC_DX0DLLCR_DLLSRST_Pos  (30U)
#define DDRPHYC_DX0DLLCR_DLLSRST_Msk  (0x1U << DDRPHYC_DX0DLLCR_DLLSRST_Pos)  /*!< 0x40000000 */
#define DDRPHYC_DX0DLLCR_DLLSRST      DDRPHYC_DX0DLLCR_DLLSRST_Msk            /*!< DLL reset */
#define DDRPHYC_DX0DLLCR_DLLDIS_Pos   (31U)
#define DDRPHYC_DX0DLLCR_DLLDIS_Msk   (0x1U << DDRPHYC_DX0DLLCR_DLLDIS_Pos)   /*!< 0x80000000 */
#define DDRPHYC_DX0DLLCR_DLLDIS       DDRPHYC_DX0DLLCR_DLLDIS_Msk             /*!< DLL bypass */

/***************  Bit definition for DDRPHYC_DX0DQTR register  ****************/
#define DDRPHYC_DX0DQTR_DQDLY0_Pos (0U)
#define DDRPHYC_DX0DQTR_DQDLY0_Msk (0xFU << DDRPHYC_DX0DQTR_DQDLY0_Pos) /*!< 0x0000000F */
#define DDRPHYC_DX0DQTR_DQDLY0     DDRPHYC_DX0DQTR_DQDLY0_Msk           /*!< DQ delay for bit 0 */
#define DDRPHYC_DX0DQTR_DQDLY0_0   (0x1U << DDRPHYC_DX0DQTR_DQDLY0_Pos) /*!< 0x00000001 */
#define DDRPHYC_DX0DQTR_DQDLY0_1   (0x2U << DDRPHYC_DX0DQTR_DQDLY0_Pos) /*!< 0x00000002 */
#define DDRPHYC_DX0DQTR_DQDLY0_2   (0x4U << DDRPHYC_DX0DQTR_DQDLY0_Pos) /*!< 0x00000004 */
#define DDRPHYC_DX0DQTR_DQDLY0_3   (0x8U << DDRPHYC_DX0DQTR_DQDLY0_Pos) /*!< 0x00000008 */
#define DDRPHYC_DX0DQTR_DQDLY1_Pos (4U)
#define DDRPHYC_DX0DQTR_DQDLY1_Msk (0xFU << DDRPHYC_DX0DQTR_DQDLY1_Pos) /*!< 0x000000F0 */
#define DDRPHYC_DX0DQTR_DQDLY1     DDRPHYC_DX0DQTR_DQDLY1_Msk           /*!< DQ delay for bit 1 */
#define DDRPHYC_DX0DQTR_DQDLY1_0   (0x1U << DDRPHYC_DX0DQTR_DQDLY1_Pos) /*!< 0x00000010 */
#define DDRPHYC_DX0DQTR_DQDLY1_1   (0x2U << DDRPHYC_DX0DQTR_DQDLY1_Pos) /*!< 0x00000020 */
#define DDRPHYC_DX0DQTR_DQDLY1_2   (0x4U << DDRPHYC_DX0DQTR_DQDLY1_Pos) /*!< 0x00000040 */
#define DDRPHYC_DX0DQTR_DQDLY1_3   (0x8U << DDRPHYC_DX0DQTR_DQDLY1_Pos) /*!< 0x00000080 */
#define DDRPHYC_DX0DQTR_DQDLY2_Pos (8U)
#define DDRPHYC_DX0DQTR_DQDLY2_Msk (0xFU << DDRPHYC_DX0DQTR_DQDLY2_Pos) /*!< 0x00000F00 */
#define DDRPHYC_DX0DQTR_DQDLY2     DDRPHYC_DX0DQTR_DQDLY2_Msk           /*!< DQ delay for bit 2 */
#define DDRPHYC_DX0DQTR_DQDLY2_0   (0x1U << DDRPHYC_DX0DQTR_DQDLY2_Pos) /*!< 0x00000100 */
#define DDRPHYC_DX0DQTR_DQDLY2_1   (0x2U << DDRPHYC_DX0DQTR_DQDLY2_Pos) /*!< 0x00000200 */
#define DDRPHYC_DX0DQTR_DQDLY2_2   (0x4U << DDRPHYC_DX0DQTR_DQDLY2_Pos) /*!< 0x00000400 */
#define DDRPHYC_DX0DQTR_DQDLY2_3   (0x8U << DDRPHYC_DX0DQTR_DQDLY2_Pos) /*!< 0x00000800 */
#define DDRPHYC_DX0DQTR_DQDLY3_Pos (12U)
#define DDRPHYC_DX0DQTR_DQDLY3_Msk (0xFU << DDRPHYC_DX0DQTR_DQDLY3_Pos) /*!< 0x0000F000 */
#define DDRPHYC_DX0DQTR_DQDLY3     DDRPHYC_DX0DQTR_DQDLY3_Msk           /*!< DQ delay for bit 3 */
#define DDRPHYC_DX0DQTR_DQDLY3_0   (0x1U << DDRPHYC_DX0DQTR_DQDLY3_Pos) /*!< 0x00001000 */
#define DDRPHYC_DX0DQTR_DQDLY3_1   (0x2U << DDRPHYC_DX0DQTR_DQDLY3_Pos) /*!< 0x00002000 */
#define DDRPHYC_DX0DQTR_DQDLY3_2   (0x4U << DDRPHYC_DX0DQTR_DQDLY3_Pos) /*!< 0x00004000 */
#define DDRPHYC_DX0DQTR_DQDLY3_3   (0x8U << DDRPHYC_DX0DQTR_DQDLY3_Pos) /*!< 0x00008000 */
#define DDRPHYC_DX0DQTR_DQDLY4_Pos (16U)
#define DDRPHYC_DX0DQTR_DQDLY4_Msk (0xFU << DDRPHYC_DX0DQTR_DQDLY4_Pos) /*!< 0x000F0000 */
#define DDRPHYC_DX0DQTR_DQDLY4     DDRPHYC_DX0DQTR_DQDLY4_Msk           /*!< DQ delay for bit 4 */
#define DDRPHYC_DX0DQTR_DQDLY4_0   (0x1U << DDRPHYC_DX0DQTR_DQDLY4_Pos) /*!< 0x00010000 */
#define DDRPHYC_DX0DQTR_DQDLY4_1   (0x2U << DDRPHYC_DX0DQTR_DQDLY4_Pos) /*!< 0x00020000 */
#define DDRPHYC_DX0DQTR_DQDLY4_2   (0x4U << DDRPHYC_DX0DQTR_DQDLY4_Pos) /*!< 0x00040000 */
#define DDRPHYC_DX0DQTR_DQDLY4_3   (0x8U << DDRPHYC_DX0DQTR_DQDLY4_Pos) /*!< 0x00080000 */
#define DDRPHYC_DX0DQTR_DQDLY5_Pos (20U)
#define DDRPHYC_DX0DQTR_DQDLY5_Msk (0xFU << DDRPHYC_DX0DQTR_DQDLY5_Pos) /*!< 0x00F00000 */
#define DDRPHYC_DX0DQTR_DQDLY5     DDRPHYC_DX0DQTR_DQDLY5_Msk           /*!< DQ delay for bit 5 */
#define DDRPHYC_DX0DQTR_DQDLY5_0   (0x1U << DDRPHYC_DX0DQTR_DQDLY5_Pos) /*!< 0x00100000 */
#define DDRPHYC_DX0DQTR_DQDLY5_1   (0x2U << DDRPHYC_DX0DQTR_DQDLY5_Pos) /*!< 0x00200000 */
#define DDRPHYC_DX0DQTR_DQDLY5_2   (0x4U << DDRPHYC_DX0DQTR_DQDLY5_Pos) /*!< 0x00400000 */
#define DDRPHYC_DX0DQTR_DQDLY5_3   (0x8U << DDRPHYC_DX0DQTR_DQDLY5_Pos) /*!< 0x00800000 */
#define DDRPHYC_DX0DQTR_DQDLY6_Pos (24U)
#define DDRPHYC_DX0DQTR_DQDLY6_Msk (0xFU << DDRPHYC_DX0DQTR_DQDLY6_Pos) /*!< 0x0F000000 */
#define DDRPHYC_DX0DQTR_DQDLY6     DDRPHYC_DX0DQTR_DQDLY6_Msk           /*!< DQ delay for bit 6 */
#define DDRPHYC_DX0DQTR_DQDLY6_0   (0x1U << DDRPHYC_DX0DQTR_DQDLY6_Pos) /*!< 0x01000000 */
#define DDRPHYC_DX0DQTR_DQDLY6_1   (0x2U << DDRPHYC_DX0DQTR_DQDLY6_Pos) /*!< 0x02000000 */
#define DDRPHYC_DX0DQTR_DQDLY6_2   (0x4U << DDRPHYC_DX0DQTR_DQDLY6_Pos) /*!< 0x04000000 */
#define DDRPHYC_DX0DQTR_DQDLY6_3   (0x8U << DDRPHYC_DX0DQTR_DQDLY6_Pos) /*!< 0x08000000 */
#define DDRPHYC_DX0DQTR_DQDLY7_Pos (28U)
#define DDRPHYC_DX0DQTR_DQDLY7_Msk (0xFU << DDRPHYC_DX0DQTR_DQDLY7_Pos) /*!< 0xF0000000 */
#define DDRPHYC_DX0DQTR_DQDLY7     DDRPHYC_DX0DQTR_DQDLY7_Msk           /*!< DQ delay for bit 7 */
#define DDRPHYC_DX0DQTR_DQDLY7_0   (0x1U << DDRPHYC_DX0DQTR_DQDLY7_Pos) /*!< 0x10000000 */
#define DDRPHYC_DX0DQTR_DQDLY7_1   (0x2U << DDRPHYC_DX0DQTR_DQDLY7_Pos) /*!< 0x20000000 */
#define DDRPHYC_DX0DQTR_DQDLY7_2   (0x4U << DDRPHYC_DX0DQTR_DQDLY7_Pos) /*!< 0x40000000 */
#define DDRPHYC_DX0DQTR_DQDLY7_3   (0x8U << DDRPHYC_DX0DQTR_DQDLY7_Pos) /*!< 0x80000000 */

/***************  Bit definition for DDRPHYC_DX0DQSTR register  ***************/
#define DDRPHYC_DX0DQSTR_R0DGSL_Pos  (0U)
#define DDRPHYC_DX0DQSTR_R0DGSL_Msk  (0x7U << DDRPHYC_DX0DQSTR_R0DGSL_Pos)  /*!< 0x00000007 */
#define DDRPHYC_DX0DQSTR_R0DGSL      DDRPHYC_DX0DQSTR_R0DGSL_Msk            /*!< Rank 0 DQS gating system latency */
#define DDRPHYC_DX0DQSTR_R0DGSL_0    (0x1U << DDRPHYC_DX0DQSTR_R0DGSL_Pos)  /*!< 0x00000001 */
#define DDRPHYC_DX0DQSTR_R0DGSL_1    (0x2U << DDRPHYC_DX0DQSTR_R0DGSL_Pos)  /*!< 0x00000002 */
#define DDRPHYC_DX0DQSTR_R0DGSL_2    (0x4U << DDRPHYC_DX0DQSTR_R0DGSL_Pos)  /*!< 0x00000004 */
#define DDRPHYC_DX0DQSTR_R0DGPS_Pos  (12U)
#define DDRPHYC_DX0DQSTR_R0DGPS_Msk  (0x3U << DDRPHYC_DX0DQSTR_R0DGPS_Pos)  /*!< 0x00003000 */
#define DDRPHYC_DX0DQSTR_R0DGPS      DDRPHYC_DX0DQSTR_R0DGPS_Msk            /*!< Rank 0 DQS gating phase select */
#define DDRPHYC_DX0DQSTR_R0DGPS_0    (0x1U << DDRPHYC_DX0DQSTR_R0DGPS_Pos)  /*!< 0x00001000 */
#define DDRPHYC_DX0DQSTR_R0DGPS_1    (0x2U << DDRPHYC_DX0DQSTR_R0DGPS_Pos)  /*!< 0x00002000 */
#define DDRPHYC_DX0DQSTR_DQSDLY_Pos  (20U)
#define DDRPHYC_DX0DQSTR_DQSDLY_Msk  (0x7U << DDRPHYC_DX0DQSTR_DQSDLY_Pos)  /*!< 0x00700000 */
#define DDRPHYC_DX0DQSTR_DQSDLY      DDRPHYC_DX0DQSTR_DQSDLY_Msk            /*!< DQS delay */
#define DDRPHYC_DX0DQSTR_DQSDLY_0    (0x1U << DDRPHYC_DX0DQSTR_DQSDLY_Pos)  /*!< 0x00100000 */
#define DDRPHYC_DX0DQSTR_DQSDLY_1    (0x2U << DDRPHYC_DX0DQSTR_DQSDLY_Pos)  /*!< 0x00200000 */
#define DDRPHYC_DX0DQSTR_DQSDLY_2    (0x4U << DDRPHYC_DX0DQSTR_DQSDLY_Pos)  /*!< 0x00400000 */
#define DDRPHYC_DX0DQSTR_DQSNDLY_Pos (23U)
#define DDRPHYC_DX0DQSTR_DQSNDLY_Msk (0x7U << DDRPHYC_DX0DQSTR_DQSNDLY_Pos) /*!< 0x03800000 */
#define DDRPHYC_DX0DQSTR_DQSNDLY     DDRPHYC_DX0DQSTR_DQSNDLY_Msk           /*!< DQS# delay */
#define DDRPHYC_DX0DQSTR_DQSNDLY_0   (0x1U << DDRPHYC_DX0DQSTR_DQSNDLY_Pos) /*!< 0x00800000 */
#define DDRPHYC_DX0DQSTR_DQSNDLY_1   (0x2U << DDRPHYC_DX0DQSTR_DQSNDLY_Pos) /*!< 0x01000000 */
#define DDRPHYC_DX0DQSTR_DQSNDLY_2   (0x4U << DDRPHYC_DX0DQSTR_DQSNDLY_Pos) /*!< 0x02000000 */
#define DDRPHYC_DX0DQSTR_DMDLY_Pos   (26U)
#define DDRPHYC_DX0DQSTR_DMDLY_Msk   (0xFU << DDRPHYC_DX0DQSTR_DMDLY_Pos)   /*!< 0x3C000000 */
#define DDRPHYC_DX0DQSTR_DMDLY       DDRPHYC_DX0DQSTR_DMDLY_Msk             /*!< DM delay */
#define DDRPHYC_DX0DQSTR_DMDLY_0     (0x1U << DDRPHYC_DX0DQSTR_DMDLY_Pos)   /*!< 0x04000000 */
#define DDRPHYC_DX0DQSTR_DMDLY_1     (0x2U << DDRPHYC_DX0DQSTR_DMDLY_Pos)   /*!< 0x08000000 */
#define DDRPHYC_DX0DQSTR_DMDLY_2     (0x4U << DDRPHYC_DX0DQSTR_DMDLY_Pos)   /*!< 0x10000000 */
#define DDRPHYC_DX0DQSTR_DMDLY_3     (0x8U << DDRPHYC_DX0DQSTR_DMDLY_Pos)   /*!< 0x20000000 */

/****************  Bit definition for DDRPHYC_DX1GCR register  ****************/
#define DDRPHYC_DX1GCR_DXEN_Pos   (0U)
#define DDRPHYC_DX1GCR_DXEN_Msk   (0x1U << DDRPHYC_DX1GCR_DXEN_Pos)   /*!< 0x00000001 */
#define DDRPHYC_DX1GCR_DXEN       DDRPHYC_DX1GCR_DXEN_Msk             /*!< DATA byte enable */
#define DDRPHYC_DX1GCR_DQSODT_Pos (1U)
#define DDRPHYC_DX1GCR_DQSODT_Msk (0x1U << DDRPHYC_DX1GCR_DQSODT_Pos) /*!< 0x00000002 */
#define DDRPHYC_DX1GCR_DQSODT     DDRPHYC_DX1GCR_DQSODT_Msk           /*!< DQS ODT enable */
#define DDRPHYC_DX1GCR_DQODT_Pos  (2U)
#define DDRPHYC_DX1GCR_DQODT_Msk  (0x1U << DDRPHYC_DX1GCR_DQODT_Pos)  /*!< 0x00000004 */
#define DDRPHYC_DX1GCR_DQODT      DDRPHYC_DX1GCR_DQODT_Msk            /*!< DQ ODT enable */
#define DDRPHYC_DX1GCR_DXIOM_Pos  (3U)
#define DDRPHYC_DX1GCR_DXIOM_Msk  (0x1U << DDRPHYC_DX1GCR_DXIOM_Pos)  /*!< 0x00000008 */
#define DDRPHYC_DX1GCR_DXIOM      DDRPHYC_DX1GCR_DXIOM_Msk            /*!< Data I/O mode */
#define DDRPHYC_DX1GCR_DXPDD_Pos  (4U)
#define DDRPHYC_DX1GCR_DXPDD_Msk  (0x1U << DDRPHYC_DX1GCR_DXPDD_Pos)  /*!< 0x00000010 */
#define DDRPHYC_DX1GCR_DXPDD      DDRPHYC_DX1GCR_DXPDD_Msk            /*!< Data power-down driver */
#define DDRPHYC_DX1GCR_DXPDR_Pos  (5U)
#define DDRPHYC_DX1GCR_DXPDR_Msk  (0x1U << DDRPHYC_DX1GCR_DXPDR_Pos)  /*!< 0x00000020 */
#define DDRPHYC_DX1GCR_DXPDR      DDRPHYC_DX1GCR_DXPDR_Msk            /*!< Data power-down receiver */
#define DDRPHYC_DX1GCR_DQSRPD_Pos (6U)
#define DDRPHYC_DX1GCR_DQSRPD_Msk (0x1U << DDRPHYC_DX1GCR_DQSRPD_Pos) /*!< 0x00000040 */
#define DDRPHYC_DX1GCR_DQSRPD     DDRPHYC_DX1GCR_DQSRPD_Msk           /*!< DQSR power-down */
#define DDRPHYC_DX1GCR_DSEN_Pos   (7U)
#define DDRPHYC_DX1GCR_DSEN_Msk   (0x3U << DDRPHYC_DX1GCR_DSEN_Pos)   /*!< 0x00000180 */
#define DDRPHYC_DX1GCR_DSEN       DDRPHYC_DX1GCR_DSEN_Msk             /*!< Write DQS enable */
#define DDRPHYC_DX1GCR_DSEN_0     (0x1U << DDRPHYC_DX1GCR_DSEN_Pos)   /*!< 0x00000080 */
#define DDRPHYC_DX1GCR_DSEN_1     (0x2U << DDRPHYC_DX1GCR_DSEN_Pos)   /*!< 0x00000100 */
#define DDRPHYC_DX1GCR_DQSRTT_Pos (9U)
#define DDRPHYC_DX1GCR_DQSRTT_Msk (0x1U << DDRPHYC_DX1GCR_DQSRTT_Pos) /*!< 0x00000200 */
#define DDRPHYC_DX1GCR_DQSRTT     DDRPHYC_DX1GCR_DQSRTT_Msk           /*!< DQS dynamic RTT control */
#define DDRPHYC_DX1GCR_DQRTT_Pos  (10U)
#define DDRPHYC_DX1GCR_DQRTT_Msk  (0x1U << DDRPHYC_DX1GCR_DQRTT_Pos)  /*!< 0x00000400 */
#define DDRPHYC_DX1GCR_DQRTT      DDRPHYC_DX1GCR_DQRTT_Msk            /*!< DQ dynamic RTT control */
#define DDRPHYC_DX1GCR_RTTOH_Pos  (11U)
#define DDRPHYC_DX1GCR_RTTOH_Msk  (0x3U << DDRPHYC_DX1GCR_RTTOH_Pos)  /*!< 0x00001800 */
#define DDRPHYC_DX1GCR_RTTOH      DDRPHYC_DX1GCR_RTTOH_Msk            /*!< RTT output hold */
#define DDRPHYC_DX1GCR_RTTOH_0    (0x1U << DDRPHYC_DX1GCR_RTTOH_Pos)  /*!< 0x00000800 */
#define DDRPHYC_DX1GCR_RTTOH_1    (0x2U << DDRPHYC_DX1GCR_RTTOH_Pos)  /*!< 0x00001000 */
#define DDRPHYC_DX1GCR_RTTOAL_Pos (13U)
#define DDRPHYC_DX1GCR_RTTOAL_Msk (0x1U << DDRPHYC_DX1GCR_RTTOAL_Pos) /*!< 0x00002000 */
#define DDRPHYC_DX1GCR_RTTOAL     DDRPHYC_DX1GCR_RTTOAL_Msk           /*!< RTT ON additive latency */
#define DDRPHYC_DX1GCR_R0RVSL_Pos (14U)
#define DDRPHYC_DX1GCR_R0RVSL_Msk (0x7U << DDRPHYC_DX1GCR_R0RVSL_Pos) /*!< 0x0001C000 */
#define DDRPHYC_DX1GCR_R0RVSL     DDRPHYC_DX1GCR_R0RVSL_Msk           /*!< Read valid system latency in steps */
#define DDRPHYC_DX1GCR_R0RVSL_0   (0x1U << DDRPHYC_DX1GCR_R0RVSL_Pos) /*!< 0x00004000 */
#define DDRPHYC_DX1GCR_R0RVSL_1   (0x2U << DDRPHYC_DX1GCR_R0RVSL_Pos) /*!< 0x00008000 */
#define DDRPHYC_DX1GCR_R0RVSL_2   (0x4U << DDRPHYC_DX1GCR_R0RVSL_Pos) /*!< 0x00010000 */

/***************  Bit definition for DDRPHYC_DX1GSR0 register  ****************/
#define DDRPHYC_DX1GSR0_DTDONE_Pos (0U)
#define DDRPHYC_DX1GSR0_DTDONE_Msk (0x1U << DDRPHYC_DX1GSR0_DTDONE_Pos) /*!< 0x00000001 */
#define DDRPHYC_DX1GSR0_DTDONE     DDRPHYC_DX1GSR0_DTDONE_Msk           /*!< Data training done */
#define DDRPHYC_DX1GSR0_DTERR_Pos  (4U)
#define DDRPHYC_DX1GSR0_DTERR_Msk  (0x1U << DDRPHYC_DX1GSR0_DTERR_Pos)  /*!< 0x00000010 */
#define DDRPHYC_DX1GSR0_DTERR      DDRPHYC_DX1GSR0_DTERR_Msk            /*!< DQS gate training error */
#define DDRPHYC_DX1GSR0_DTIERR_Pos (8U)
#define DDRPHYC_DX1GSR0_DTIERR_Msk (0x1U << DDRPHYC_DX1GSR0_DTIERR_Pos) /*!< 0x00000100 */
#define DDRPHYC_DX1GSR0_DTIERR     DDRPHYC_DX1GSR0_DTIERR_Msk           /*!< DQS gate training intermittent error */
#define DDRPHYC_DX1GSR0_DTPASS_Pos (13U)
#define DDRPHYC_DX1GSR0_DTPASS_Msk (0x7U << DDRPHYC_DX1GSR0_DTPASS_Pos) /*!< 0x0000E000 */
#define DDRPHYC_DX1GSR0_DTPASS     DDRPHYC_DX1GSR0_DTPASS_Msk           /*!< DQS training pass count */
#define DDRPHYC_DX1GSR0_DTPASS_0   (0x1U << DDRPHYC_DX1GSR0_DTPASS_Pos) /*!< 0x00002000 */
#define DDRPHYC_DX1GSR0_DTPASS_1   (0x2U << DDRPHYC_DX1GSR0_DTPASS_Pos) /*!< 0x00004000 */
#define DDRPHYC_DX1GSR0_DTPASS_2   (0x4U << DDRPHYC_DX1GSR0_DTPASS_Pos) /*!< 0x00008000 */

/***************  Bit definition for DDRPHYC_DX1GSR1 register  ****************/
#define DDRPHYC_DX1GSR1_DFTERR_Pos (0U)
#define DDRPHYC_DX1GSR1_DFTERR_Msk (0x1U << DDRPHYC_DX1GSR1_DFTERR_Pos) /*!< 0x00000001 */
#define DDRPHYC_DX1GSR1_DFTERR     DDRPHYC_DX1GSR1_DFTERR_Msk           /*!< DQS drift error */
#define DDRPHYC_DX1GSR1_DQSDFT_Pos (4U)
#define DDRPHYC_DX1GSR1_DQSDFT_Msk (0x3U << DDRPHYC_DX1GSR1_DQSDFT_Pos) /*!< 0x00000030 */
#define DDRPHYC_DX1GSR1_DQSDFT     DDRPHYC_DX1GSR1_DQSDFT_Msk           /*!< DQS drift value */
#define DDRPHYC_DX1GSR1_DQSDFT_0   (0x1U << DDRPHYC_DX1GSR1_DQSDFT_Pos) /*!< 0x00000010 */
#define DDRPHYC_DX1GSR1_DQSDFT_1   (0x2U << DDRPHYC_DX1GSR1_DQSDFT_Pos) /*!< 0x00000020 */
#define DDRPHYC_DX1GSR1_RVERR_Pos  (12U)
#define DDRPHYC_DX1GSR1_RVERR_Msk  (0x1U << DDRPHYC_DX1GSR1_RVERR_Pos)  /*!< 0x00001000 */
#define DDRPHYC_DX1GSR1_RVERR      DDRPHYC_DX1GSR1_RVERR_Msk            /*!< RV training error */
#define DDRPHYC_DX1GSR1_RVIERR_Pos (16U)
#define DDRPHYC_DX1GSR1_RVIERR_Msk (0x1U << DDRPHYC_DX1GSR1_RVIERR_Pos) /*!< 0x00010000 */
#define DDRPHYC_DX1GSR1_RVIERR     DDRPHYC_DX1GSR1_RVIERR_Msk           /*!< RV intermittent error for rank */
#define DDRPHYC_DX1GSR1_RVPASS_Pos (20U)
#define DDRPHYC_DX1GSR1_RVPASS_Msk (0x7U << DDRPHYC_DX1GSR1_RVPASS_Pos) /*!< 0x00700000 */
#define DDRPHYC_DX1GSR1_RVPASS     DDRPHYC_DX1GSR1_RVPASS_Msk           /*!< Read valid training pass count */
#define DDRPHYC_DX1GSR1_RVPASS_0   (0x1U << DDRPHYC_DX1GSR1_RVPASS_Pos) /*!< 0x00100000 */
#define DDRPHYC_DX1GSR1_RVPASS_1   (0x2U << DDRPHYC_DX1GSR1_RVPASS_Pos) /*!< 0x00200000 */
#define DDRPHYC_DX1GSR1_RVPASS_2   (0x4U << DDRPHYC_DX1GSR1_RVPASS_Pos) /*!< 0x00400000 */

/***************  Bit definition for DDRPHYC_DX1DLLCR register  ***************/
#define DDRPHYC_DX1DLLCR_SFBDLY_Pos   (0U)
#define DDRPHYC_DX1DLLCR_SFBDLY_Msk   (0x7U << DDRPHYC_DX1DLLCR_SFBDLY_Pos)   /*!< 0x00000007 */
#define DDRPHYC_DX1DLLCR_SFBDLY       DDRPHYC_DX1DLLCR_SFBDLY_Msk             /*!< Slave DLL feed-back trim */
#define DDRPHYC_DX1DLLCR_SFBDLY_0     (0x1U << DDRPHYC_DX1DLLCR_SFBDLY_Pos)   /*!< 0x00000001 */
#define DDRPHYC_DX1DLLCR_SFBDLY_1     (0x2U << DDRPHYC_DX1DLLCR_SFBDLY_Pos)   /*!< 0x00000002 */
#define DDRPHYC_DX1DLLCR_SFBDLY_2     (0x4U << DDRPHYC_DX1DLLCR_SFBDLY_Pos)   /*!< 0x00000004 */
#define DDRPHYC_DX1DLLCR_SFWDLY_Pos   (3U)
#define DDRPHYC_DX1DLLCR_SFWDLY_Msk   (0x7U << DDRPHYC_DX1DLLCR_SFWDLY_Pos)   /*!< 0x00000038 */
#define DDRPHYC_DX1DLLCR_SFWDLY       DDRPHYC_DX1DLLCR_SFWDLY_Msk             /*!< Slave DLL feed-forward trim */
#define DDRPHYC_DX1DLLCR_SFWDLY_0     (0x1U << DDRPHYC_DX1DLLCR_SFWDLY_Pos)   /*!< 0x00000008 */
#define DDRPHYC_DX1DLLCR_SFWDLY_1     (0x2U << DDRPHYC_DX1DLLCR_SFWDLY_Pos)   /*!< 0x00000010 */
#define DDRPHYC_DX1DLLCR_SFWDLY_2     (0x4U << DDRPHYC_DX1DLLCR_SFWDLY_Pos)   /*!< 0x00000020 */
#define DDRPHYC_DX1DLLCR_MFBDLY_Pos   (6U)
#define DDRPHYC_DX1DLLCR_MFBDLY_Msk   (0x7U << DDRPHYC_DX1DLLCR_MFBDLY_Pos)   /*!< 0x000001C0 */
#define DDRPHYC_DX1DLLCR_MFBDLY       DDRPHYC_DX1DLLCR_MFBDLY_Msk             /*!< Master DLL feed-back trim */
#define DDRPHYC_DX1DLLCR_MFBDLY_0     (0x1U << DDRPHYC_DX1DLLCR_MFBDLY_Pos)   /*!< 0x00000040 */
#define DDRPHYC_DX1DLLCR_MFBDLY_1     (0x2U << DDRPHYC_DX1DLLCR_MFBDLY_Pos)   /*!< 0x00000080 */
#define DDRPHYC_DX1DLLCR_MFBDLY_2     (0x4U << DDRPHYC_DX1DLLCR_MFBDLY_Pos)   /*!< 0x00000100 */
#define DDRPHYC_DX1DLLCR_MFWDLY_Pos   (9U)
#define DDRPHYC_DX1DLLCR_MFWDLY_Msk   (0x7U << DDRPHYC_DX1DLLCR_MFWDLY_Pos)   /*!< 0x00000E00 */
#define DDRPHYC_DX1DLLCR_MFWDLY       DDRPHYC_DX1DLLCR_MFWDLY_Msk             /*!< Master DLL feed-forward trim */
#define DDRPHYC_DX1DLLCR_MFWDLY_0     (0x1U << DDRPHYC_DX1DLLCR_MFWDLY_Pos)   /*!< 0x00000200 */
#define DDRPHYC_DX1DLLCR_MFWDLY_1     (0x2U << DDRPHYC_DX1DLLCR_MFWDLY_Pos)   /*!< 0x00000400 */
#define DDRPHYC_DX1DLLCR_MFWDLY_2     (0x4U << DDRPHYC_DX1DLLCR_MFWDLY_Pos)   /*!< 0x00000800 */
#define DDRPHYC_DX1DLLCR_SSTART_Pos   (12U)
#define DDRPHYC_DX1DLLCR_SSTART_Msk   (0x3U << DDRPHYC_DX1DLLCR_SSTART_Pos)   /*!< 0x00003000 */
#define DDRPHYC_DX1DLLCR_SSTART       DDRPHYC_DX1DLLCR_SSTART_Msk             /*!< Slave DLL autostart */
#define DDRPHYC_DX1DLLCR_SSTART_0     (0x1U << DDRPHYC_DX1DLLCR_SSTART_Pos)   /*!< 0x00001000 */
#define DDRPHYC_DX1DLLCR_SSTART_1     (0x2U << DDRPHYC_DX1DLLCR_SSTART_Pos)   /*!< 0x00002000 */
#define DDRPHYC_DX1DLLCR_SDPHASE_Pos  (14U)
#define DDRPHYC_DX1DLLCR_SDPHASE_Msk  (0xFU << DDRPHYC_DX1DLLCR_SDPHASE_Pos)  /*!< 0x0003C000 */
#define DDRPHYC_DX1DLLCR_SDPHASE      DDRPHYC_DX1DLLCR_SDPHASE_Msk            /*!< Slave DLL phase */
#define DDRPHYC_DX1DLLCR_SDPHASE_0    (0x1U << DDRPHYC_DX1DLLCR_SDPHASE_Pos)  /*!< 0x00004000 */
#define DDRPHYC_DX1DLLCR_SDPHASE_1    (0x2U << DDRPHYC_DX1DLLCR_SDPHASE_Pos)  /*!< 0x00008000 */
#define DDRPHYC_DX1DLLCR_SDPHASE_2    (0x4U << DDRPHYC_DX1DLLCR_SDPHASE_Pos)  /*!< 0x00010000 */
#define DDRPHYC_DX1DLLCR_SDPHASE_3    (0x8U << DDRPHYC_DX1DLLCR_SDPHASE_Pos)  /*!< 0x00020000 */
#define DDRPHYC_DX1DLLCR_ATESTEN_Pos  (18U)
#define DDRPHYC_DX1DLLCR_ATESTEN_Msk  (0x1U << DDRPHYC_DX1DLLCR_ATESTEN_Pos)  /*!< 0x00040000 */
#define DDRPHYC_DX1DLLCR_ATESTEN      DDRPHYC_DX1DLLCR_ATESTEN_Msk            /*!< Enable path to pin 'ATO' */
#define DDRPHYC_DX1DLLCR_SDLBMODE_Pos (19U)
#define DDRPHYC_DX1DLLCR_SDLBMODE_Msk (0x1U << DDRPHYC_DX1DLLCR_SDLBMODE_Pos) /*!< 0x00080000 */
#define DDRPHYC_DX1DLLCR_SDLBMODE     DDRPHYC_DX1DLLCR_SDLBMODE_Msk           /*!< Bypass slave DLL during loopback */
#define DDRPHYC_DX1DLLCR_DLLSRST_Pos  (30U)
#define DDRPHYC_DX1DLLCR_DLLSRST_Msk  (0x1U << DDRPHYC_DX1DLLCR_DLLSRST_Pos)  /*!< 0x40000000 */
#define DDRPHYC_DX1DLLCR_DLLSRST      DDRPHYC_DX1DLLCR_DLLSRST_Msk            /*!< DLL reset */
#define DDRPHYC_DX1DLLCR_DLLDIS_Pos   (31U)
#define DDRPHYC_DX1DLLCR_DLLDIS_Msk   (0x1U << DDRPHYC_DX1DLLCR_DLLDIS_Pos)   /*!< 0x80000000 */
#define DDRPHYC_DX1DLLCR_DLLDIS       DDRPHYC_DX1DLLCR_DLLDIS_Msk             /*!< DLL bypass */

/***************  Bit definition for DDRPHYC_DX1DQTR register  ****************/
#define DDRPHYC_DX1DQTR_DQDLY0_Pos (0U)
#define DDRPHYC_DX1DQTR_DQDLY0_Msk (0xFU << DDRPHYC_DX1DQTR_DQDLY0_Pos) /*!< 0x0000000F */
#define DDRPHYC_DX1DQTR_DQDLY0     DDRPHYC_DX1DQTR_DQDLY0_Msk           /*!< DQ delay for bit 0 */
#define DDRPHYC_DX1DQTR_DQDLY0_0   (0x1U << DDRPHYC_DX1DQTR_DQDLY0_Pos) /*!< 0x00000001 */
#define DDRPHYC_DX1DQTR_DQDLY0_1   (0x2U << DDRPHYC_DX1DQTR_DQDLY0_Pos) /*!< 0x00000002 */
#define DDRPHYC_DX1DQTR_DQDLY0_2   (0x4U << DDRPHYC_DX1DQTR_DQDLY0_Pos) /*!< 0x00000004 */
#define DDRPHYC_DX1DQTR_DQDLY0_3   (0x8U << DDRPHYC_DX1DQTR_DQDLY0_Pos) /*!< 0x00000008 */
#define DDRPHYC_DX1DQTR_DQDLY1_Pos (4U)
#define DDRPHYC_DX1DQTR_DQDLY1_Msk (0xFU << DDRPHYC_DX1DQTR_DQDLY1_Pos) /*!< 0x000000F0 */
#define DDRPHYC_DX1DQTR_DQDLY1     DDRPHYC_DX1DQTR_DQDLY1_Msk           /*!< DQ delay for bit 1 */
#define DDRPHYC_DX1DQTR_DQDLY1_0   (0x1U << DDRPHYC_DX1DQTR_DQDLY1_Pos) /*!< 0x00000010 */
#define DDRPHYC_DX1DQTR_DQDLY1_1   (0x2U << DDRPHYC_DX1DQTR_DQDLY1_Pos) /*!< 0x00000020 */
#define DDRPHYC_DX1DQTR_DQDLY1_2   (0x4U << DDRPHYC_DX1DQTR_DQDLY1_Pos) /*!< 0x00000040 */
#define DDRPHYC_DX1DQTR_DQDLY1_3   (0x8U << DDRPHYC_DX1DQTR_DQDLY1_Pos) /*!< 0x00000080 */
#define DDRPHYC_DX1DQTR_DQDLY2_Pos (8U)
#define DDRPHYC_DX1DQTR_DQDLY2_Msk (0xFU << DDRPHYC_DX1DQTR_DQDLY2_Pos) /*!< 0x00000F00 */
#define DDRPHYC_DX1DQTR_DQDLY2     DDRPHYC_DX1DQTR_DQDLY2_Msk           /*!< DQ delay for bit 2 */
#define DDRPHYC_DX1DQTR_DQDLY2_0   (0x1U << DDRPHYC_DX1DQTR_DQDLY2_Pos) /*!< 0x00000100 */
#define DDRPHYC_DX1DQTR_DQDLY2_1   (0x2U << DDRPHYC_DX1DQTR_DQDLY2_Pos) /*!< 0x00000200 */
#define DDRPHYC_DX1DQTR_DQDLY2_2   (0x4U << DDRPHYC_DX1DQTR_DQDLY2_Pos) /*!< 0x00000400 */
#define DDRPHYC_DX1DQTR_DQDLY2_3   (0x8U << DDRPHYC_DX1DQTR_DQDLY2_Pos) /*!< 0x00000800 */
#define DDRPHYC_DX1DQTR_DQDLY3_Pos (12U)
#define DDRPHYC_DX1DQTR_DQDLY3_Msk (0xFU << DDRPHYC_DX1DQTR_DQDLY3_Pos) /*!< 0x0000F000 */
#define DDRPHYC_DX1DQTR_DQDLY3     DDRPHYC_DX1DQTR_DQDLY3_Msk           /*!< DQ delay for bit 3 */
#define DDRPHYC_DX1DQTR_DQDLY3_0   (0x1U << DDRPHYC_DX1DQTR_DQDLY3_Pos) /*!< 0x00001000 */
#define DDRPHYC_DX1DQTR_DQDLY3_1   (0x2U << DDRPHYC_DX1DQTR_DQDLY3_Pos) /*!< 0x00002000 */
#define DDRPHYC_DX1DQTR_DQDLY3_2   (0x4U << DDRPHYC_DX1DQTR_DQDLY3_Pos) /*!< 0x00004000 */
#define DDRPHYC_DX1DQTR_DQDLY3_3   (0x8U << DDRPHYC_DX1DQTR_DQDLY3_Pos) /*!< 0x00008000 */
#define DDRPHYC_DX1DQTR_DQDLY4_Pos (16U)
#define DDRPHYC_DX1DQTR_DQDLY4_Msk (0xFU << DDRPHYC_DX1DQTR_DQDLY4_Pos) /*!< 0x000F0000 */
#define DDRPHYC_DX1DQTR_DQDLY4     DDRPHYC_DX1DQTR_DQDLY4_Msk           /*!< DQ delay for bit 4 */
#define DDRPHYC_DX1DQTR_DQDLY4_0   (0x1U << DDRPHYC_DX1DQTR_DQDLY4_Pos) /*!< 0x00010000 */
#define DDRPHYC_DX1DQTR_DQDLY4_1   (0x2U << DDRPHYC_DX1DQTR_DQDLY4_Pos) /*!< 0x00020000 */
#define DDRPHYC_DX1DQTR_DQDLY4_2   (0x4U << DDRPHYC_DX1DQTR_DQDLY4_Pos) /*!< 0x00040000 */
#define DDRPHYC_DX1DQTR_DQDLY4_3   (0x8U << DDRPHYC_DX1DQTR_DQDLY4_Pos) /*!< 0x00080000 */
#define DDRPHYC_DX1DQTR_DQDLY5_Pos (20U)
#define DDRPHYC_DX1DQTR_DQDLY5_Msk (0xFU << DDRPHYC_DX1DQTR_DQDLY5_Pos) /*!< 0x00F00000 */
#define DDRPHYC_DX1DQTR_DQDLY5     DDRPHYC_DX1DQTR_DQDLY5_Msk           /*!< DQ delay for bit 5 */
#define DDRPHYC_DX1DQTR_DQDLY5_0   (0x1U << DDRPHYC_DX1DQTR_DQDLY5_Pos) /*!< 0x00100000 */
#define DDRPHYC_DX1DQTR_DQDLY5_1   (0x2U << DDRPHYC_DX1DQTR_DQDLY5_Pos) /*!< 0x00200000 */
#define DDRPHYC_DX1DQTR_DQDLY5_2   (0x4U << DDRPHYC_DX1DQTR_DQDLY5_Pos) /*!< 0x00400000 */
#define DDRPHYC_DX1DQTR_DQDLY5_3   (0x8U << DDRPHYC_DX1DQTR_DQDLY5_Pos) /*!< 0x00800000 */
#define DDRPHYC_DX1DQTR_DQDLY6_Pos (24U)
#define DDRPHYC_DX1DQTR_DQDLY6_Msk (0xFU << DDRPHYC_DX1DQTR_DQDLY6_Pos) /*!< 0x0F000000 */
#define DDRPHYC_DX1DQTR_DQDLY6     DDRPHYC_DX1DQTR_DQDLY6_Msk           /*!< DQ delay for bit 6 */
#define DDRPHYC_DX1DQTR_DQDLY6_0   (0x1U << DDRPHYC_DX1DQTR_DQDLY6_Pos) /*!< 0x01000000 */
#define DDRPHYC_DX1DQTR_DQDLY6_1   (0x2U << DDRPHYC_DX1DQTR_DQDLY6_Pos) /*!< 0x02000000 */
#define DDRPHYC_DX1DQTR_DQDLY6_2   (0x4U << DDRPHYC_DX1DQTR_DQDLY6_Pos) /*!< 0x04000000 */
#define DDRPHYC_DX1DQTR_DQDLY6_3   (0x8U << DDRPHYC_DX1DQTR_DQDLY6_Pos) /*!< 0x08000000 */
#define DDRPHYC_DX1DQTR_DQDLY7_Pos (28U)
#define DDRPHYC_DX1DQTR_DQDLY7_Msk (0xFU << DDRPHYC_DX1DQTR_DQDLY7_Pos) /*!< 0xF0000000 */
#define DDRPHYC_DX1DQTR_DQDLY7     DDRPHYC_DX1DQTR_DQDLY7_Msk           /*!< DQ delay for bit 7 */
#define DDRPHYC_DX1DQTR_DQDLY7_0   (0x1U << DDRPHYC_DX1DQTR_DQDLY7_Pos) /*!< 0x10000000 */
#define DDRPHYC_DX1DQTR_DQDLY7_1   (0x2U << DDRPHYC_DX1DQTR_DQDLY7_Pos) /*!< 0x20000000 */
#define DDRPHYC_DX1DQTR_DQDLY7_2   (0x4U << DDRPHYC_DX1DQTR_DQDLY7_Pos) /*!< 0x40000000 */
#define DDRPHYC_DX1DQTR_DQDLY7_3   (0x8U << DDRPHYC_DX1DQTR_DQDLY7_Pos) /*!< 0x80000000 */

/***************  Bit definition for DDRPHYC_DX1DQSTR register  ***************/
#define DDRPHYC_DX1DQSTR_R0DGSL_Pos  (0U)
#define DDRPHYC_DX1DQSTR_R0DGSL_Msk  (0x7U << DDRPHYC_DX1DQSTR_R0DGSL_Pos)  /*!< 0x00000007 */
#define DDRPHYC_DX1DQSTR_R0DGSL      DDRPHYC_DX1DQSTR_R0DGSL_Msk            /*!< Rank 0 DQS gating system latency */
#define DDRPHYC_DX1DQSTR_R0DGSL_0    (0x1U << DDRPHYC_DX1DQSTR_R0DGSL_Pos)  /*!< 0x00000001 */
#define DDRPHYC_DX1DQSTR_R0DGSL_1    (0x2U << DDRPHYC_DX1DQSTR_R0DGSL_Pos)  /*!< 0x00000002 */
#define DDRPHYC_DX1DQSTR_R0DGSL_2    (0x4U << DDRPHYC_DX1DQSTR_R0DGSL_Pos)  /*!< 0x00000004 */
#define DDRPHYC_DX1DQSTR_R0DGPS_Pos  (12U)
#define DDRPHYC_DX1DQSTR_R0DGPS_Msk  (0x3U << DDRPHYC_DX1DQSTR_R0DGPS_Pos)  /*!< 0x00003000 */
#define DDRPHYC_DX1DQSTR_R0DGPS      DDRPHYC_DX1DQSTR_R0DGPS_Msk            /*!< Rank 0 DQS gating phase select */
#define DDRPHYC_DX1DQSTR_R0DGPS_0    (0x1U << DDRPHYC_DX1DQSTR_R0DGPS_Pos)  /*!< 0x00001000 */
#define DDRPHYC_DX1DQSTR_R0DGPS_1    (0x2U << DDRPHYC_DX1DQSTR_R0DGPS_Pos)  /*!< 0x00002000 */
#define DDRPHYC_DX1DQSTR_DQSDLY_Pos  (20U)
#define DDRPHYC_DX1DQSTR_DQSDLY_Msk  (0x7U << DDRPHYC_DX1DQSTR_DQSDLY_Pos)  /*!< 0x00700000 */
#define DDRPHYC_DX1DQSTR_DQSDLY      DDRPHYC_DX1DQSTR_DQSDLY_Msk            /*!< DQS delay */
#define DDRPHYC_DX1DQSTR_DQSDLY_0    (0x1U << DDRPHYC_DX1DQSTR_DQSDLY_Pos)  /*!< 0x00100000 */
#define DDRPHYC_DX1DQSTR_DQSDLY_1    (0x2U << DDRPHYC_DX1DQSTR_DQSDLY_Pos)  /*!< 0x00200000 */
#define DDRPHYC_DX1DQSTR_DQSDLY_2    (0x4U << DDRPHYC_DX1DQSTR_DQSDLY_Pos)  /*!< 0x00400000 */
#define DDRPHYC_DX1DQSTR_DQSNDLY_Pos (23U)
#define DDRPHYC_DX1DQSTR_DQSNDLY_Msk (0x7U << DDRPHYC_DX1DQSTR_DQSNDLY_Pos) /*!< 0x03800000 */
#define DDRPHYC_DX1DQSTR_DQSNDLY     DDRPHYC_DX1DQSTR_DQSNDLY_Msk           /*!< DQS# delay */
#define DDRPHYC_DX1DQSTR_DQSNDLY_0   (0x1U << DDRPHYC_DX1DQSTR_DQSNDLY_Pos) /*!< 0x00800000 */
#define DDRPHYC_DX1DQSTR_DQSNDLY_1   (0x2U << DDRPHYC_DX1DQSTR_DQSNDLY_Pos) /*!< 0x01000000 */
#define DDRPHYC_DX1DQSTR_DQSNDLY_2   (0x4U << DDRPHYC_DX1DQSTR_DQSNDLY_Pos) /*!< 0x02000000 */
#define DDRPHYC_DX1DQSTR_DMDLY_Pos   (26U)
#define DDRPHYC_DX1DQSTR_DMDLY_Msk   (0xFU << DDRPHYC_DX1DQSTR_DMDLY_Pos)   /*!< 0x3C000000 */
#define DDRPHYC_DX1DQSTR_DMDLY       DDRPHYC_DX1DQSTR_DMDLY_Msk             /*!< DM delay */
#define DDRPHYC_DX1DQSTR_DMDLY_0     (0x1U << DDRPHYC_DX1DQSTR_DMDLY_Pos)   /*!< 0x04000000 */
#define DDRPHYC_DX1DQSTR_DMDLY_1     (0x2U << DDRPHYC_DX1DQSTR_DMDLY_Pos)   /*!< 0x08000000 */
#define DDRPHYC_DX1DQSTR_DMDLY_2     (0x4U << DDRPHYC_DX1DQSTR_DMDLY_Pos)   /*!< 0x10000000 */
#define DDRPHYC_DX1DQSTR_DMDLY_3     (0x8U << DDRPHYC_DX1DQSTR_DMDLY_Pos)   /*!< 0x20000000 */

/****************  Bit definition for DDRPHYC_DX2GCR register  ****************/
#define DDRPHYC_DX2GCR_DXEN_Pos   (0U)
#define DDRPHYC_DX2GCR_DXEN_Msk   (0x1U << DDRPHYC_DX2GCR_DXEN_Pos)   /*!< 0x00000001 */
#define DDRPHYC_DX2GCR_DXEN       DDRPHYC_DX2GCR_DXEN_Msk             /*!< DATA byte enable */
#define DDRPHYC_DX2GCR_DQSODT_Pos (1U)
#define DDRPHYC_DX2GCR_DQSODT_Msk (0x1U << DDRPHYC_DX2GCR_DQSODT_Pos) /*!< 0x00000002 */
#define DDRPHYC_DX2GCR_DQSODT     DDRPHYC_DX2GCR_DQSODT_Msk           /*!< DQS ODT enable */
#define DDRPHYC_DX2GCR_DQODT_Pos  (2U)
#define DDRPHYC_DX2GCR_DQODT_Msk  (0x1U << DDRPHYC_DX2GCR_DQODT_Pos)  /*!< 0x00000004 */
#define DDRPHYC_DX2GCR_DQODT      DDRPHYC_DX2GCR_DQODT_Msk            /*!< DQ ODT enable */
#define DDRPHYC_DX2GCR_DXIOM_Pos  (3U)
#define DDRPHYC_DX2GCR_DXIOM_Msk  (0x1U << DDRPHYC_DX2GCR_DXIOM_Pos)  /*!< 0x00000008 */
#define DDRPHYC_DX2GCR_DXIOM      DDRPHYC_DX2GCR_DXIOM_Msk            /*!< Data I/O mode */
#define DDRPHYC_DX2GCR_DXPDD_Pos  (4U)
#define DDRPHYC_DX2GCR_DXPDD_Msk  (0x1U << DDRPHYC_DX2GCR_DXPDD_Pos)  /*!< 0x00000010 */
#define DDRPHYC_DX2GCR_DXPDD      DDRPHYC_DX2GCR_DXPDD_Msk            /*!< Data power-down driver */
#define DDRPHYC_DX2GCR_DXPDR_Pos  (5U)
#define DDRPHYC_DX2GCR_DXPDR_Msk  (0x1U << DDRPHYC_DX2GCR_DXPDR_Pos)  /*!< 0x00000020 */
#define DDRPHYC_DX2GCR_DXPDR      DDRPHYC_DX2GCR_DXPDR_Msk            /*!< Data power-down receiver */
#define DDRPHYC_DX2GCR_DQSRPD_Pos (6U)
#define DDRPHYC_DX2GCR_DQSRPD_Msk (0x1U << DDRPHYC_DX2GCR_DQSRPD_Pos) /*!< 0x00000040 */
#define DDRPHYC_DX2GCR_DQSRPD     DDRPHYC_DX2GCR_DQSRPD_Msk           /*!< DQSR power-down */
#define DDRPHYC_DX2GCR_DSEN_Pos   (7U)
#define DDRPHYC_DX2GCR_DSEN_Msk   (0x3U << DDRPHYC_DX2GCR_DSEN_Pos)   /*!< 0x00000180 */
#define DDRPHYC_DX2GCR_DSEN       DDRPHYC_DX2GCR_DSEN_Msk             /*!< Write DQS enable */
#define DDRPHYC_DX2GCR_DSEN_0     (0x1U << DDRPHYC_DX2GCR_DSEN_Pos)   /*!< 0x00000080 */
#define DDRPHYC_DX2GCR_DSEN_1     (0x2U << DDRPHYC_DX2GCR_DSEN_Pos)   /*!< 0x00000100 */
#define DDRPHYC_DX2GCR_DQSRTT_Pos (9U)
#define DDRPHYC_DX2GCR_DQSRTT_Msk (0x1U << DDRPHYC_DX2GCR_DQSRTT_Pos) /*!< 0x00000200 */
#define DDRPHYC_DX2GCR_DQSRTT     DDRPHYC_DX2GCR_DQSRTT_Msk           /*!< DQS dynamic RTT control */
#define DDRPHYC_DX2GCR_DQRTT_Pos  (10U)
#define DDRPHYC_DX2GCR_DQRTT_Msk  (0x1U << DDRPHYC_DX2GCR_DQRTT_Pos)  /*!< 0x00000400 */
#define DDRPHYC_DX2GCR_DQRTT      DDRPHYC_DX2GCR_DQRTT_Msk            /*!< DQ dynamic RTT control */
#define DDRPHYC_DX2GCR_RTTOH_Pos  (11U)
#define DDRPHYC_DX2GCR_RTTOH_Msk  (0x3U << DDRPHYC_DX2GCR_RTTOH_Pos)  /*!< 0x00001800 */
#define DDRPHYC_DX2GCR_RTTOH      DDRPHYC_DX2GCR_RTTOH_Msk            /*!< RTT output hold */
#define DDRPHYC_DX2GCR_RTTOH_0    (0x1U << DDRPHYC_DX2GCR_RTTOH_Pos)  /*!< 0x00000800 */
#define DDRPHYC_DX2GCR_RTTOH_1    (0x2U << DDRPHYC_DX2GCR_RTTOH_Pos)  /*!< 0x00001000 */
#define DDRPHYC_DX2GCR_RTTOAL_Pos (13U)
#define DDRPHYC_DX2GCR_RTTOAL_Msk (0x1U << DDRPHYC_DX2GCR_RTTOAL_Pos) /*!< 0x00002000 */
#define DDRPHYC_DX2GCR_RTTOAL     DDRPHYC_DX2GCR_RTTOAL_Msk           /*!< RTT ON additive latency */
#define DDRPHYC_DX2GCR_R0RVSL_Pos (14U)
#define DDRPHYC_DX2GCR_R0RVSL_Msk (0x7U << DDRPHYC_DX2GCR_R0RVSL_Pos) /*!< 0x0001C000 */
#define DDRPHYC_DX2GCR_R0RVSL     DDRPHYC_DX2GCR_R0RVSL_Msk           /*!< Read valid system latency in steps */
#define DDRPHYC_DX2GCR_R0RVSL_0   (0x1U << DDRPHYC_DX2GCR_R0RVSL_Pos) /*!< 0x00004000 */
#define DDRPHYC_DX2GCR_R0RVSL_1   (0x2U << DDRPHYC_DX2GCR_R0RVSL_Pos) /*!< 0x00008000 */
#define DDRPHYC_DX2GCR_R0RVSL_2   (0x4U << DDRPHYC_DX2GCR_R0RVSL_Pos) /*!< 0x00010000 */

/***************  Bit definition for DDRPHYC_DX2GSR0 register  ****************/
#define DDRPHYC_DX2GSR0_DTDONE_Pos (0U)
#define DDRPHYC_DX2GSR0_DTDONE_Msk (0x1U << DDRPHYC_DX2GSR0_DTDONE_Pos) /*!< 0x00000001 */
#define DDRPHYC_DX2GSR0_DTDONE     DDRPHYC_DX2GSR0_DTDONE_Msk           /*!< Data training done */
#define DDRPHYC_DX2GSR0_DTERR_Pos  (4U)
#define DDRPHYC_DX2GSR0_DTERR_Msk  (0x1U << DDRPHYC_DX2GSR0_DTERR_Pos)  /*!< 0x00000010 */
#define DDRPHYC_DX2GSR0_DTERR      DDRPHYC_DX2GSR0_DTERR_Msk            /*!< DQS gate training error */
#define DDRPHYC_DX2GSR0_DTIERR_Pos (8U)
#define DDRPHYC_DX2GSR0_DTIERR_Msk (0x1U << DDRPHYC_DX2GSR0_DTIERR_Pos) /*!< 0x00000100 */
#define DDRPHYC_DX2GSR0_DTIERR     DDRPHYC_DX2GSR0_DTIERR_Msk           /*!< DQS gate training intermittent error */
#define DDRPHYC_DX2GSR0_DTPASS_Pos (13U)
#define DDRPHYC_DX2GSR0_DTPASS_Msk (0x7U << DDRPHYC_DX2GSR0_DTPASS_Pos) /*!< 0x0000E000 */
#define DDRPHYC_DX2GSR0_DTPASS     DDRPHYC_DX2GSR0_DTPASS_Msk           /*!< DQS training pass count */
#define DDRPHYC_DX2GSR0_DTPASS_0   (0x1U << DDRPHYC_DX2GSR0_DTPASS_Pos) /*!< 0x00002000 */
#define DDRPHYC_DX2GSR0_DTPASS_1   (0x2U << DDRPHYC_DX2GSR0_DTPASS_Pos) /*!< 0x00004000 */
#define DDRPHYC_DX2GSR0_DTPASS_2   (0x4U << DDRPHYC_DX2GSR0_DTPASS_Pos) /*!< 0x00008000 */

/***************  Bit definition for DDRPHYC_DX2GSR1 register  ****************/
#define DDRPHYC_DX2GSR1_DFTERR_Pos (0U)
#define DDRPHYC_DX2GSR1_DFTERR_Msk (0x1U << DDRPHYC_DX2GSR1_DFTERR_Pos) /*!< 0x00000001 */
#define DDRPHYC_DX2GSR1_DFTERR     DDRPHYC_DX2GSR1_DFTERR_Msk           /*!< DQS drift error */
#define DDRPHYC_DX2GSR1_DQSDFT_Pos (4U)
#define DDRPHYC_DX2GSR1_DQSDFT_Msk (0x3U << DDRPHYC_DX2GSR1_DQSDFT_Pos) /*!< 0x00000030 */
#define DDRPHYC_DX2GSR1_DQSDFT     DDRPHYC_DX2GSR1_DQSDFT_Msk           /*!< DQS drift value */
#define DDRPHYC_DX2GSR1_DQSDFT_0   (0x1U << DDRPHYC_DX2GSR1_DQSDFT_Pos) /*!< 0x00000010 */
#define DDRPHYC_DX2GSR1_DQSDFT_1   (0x2U << DDRPHYC_DX2GSR1_DQSDFT_Pos) /*!< 0x00000020 */
#define DDRPHYC_DX2GSR1_RVERR_Pos  (12U)
#define DDRPHYC_DX2GSR1_RVERR_Msk  (0x1U << DDRPHYC_DX2GSR1_RVERR_Pos)  /*!< 0x00001000 */
#define DDRPHYC_DX2GSR1_RVERR      DDRPHYC_DX2GSR1_RVERR_Msk            /*!< RV training error */
#define DDRPHYC_DX2GSR1_RVIERR_Pos (16U)
#define DDRPHYC_DX2GSR1_RVIERR_Msk (0x1U << DDRPHYC_DX2GSR1_RVIERR_Pos) /*!< 0x00010000 */
#define DDRPHYC_DX2GSR1_RVIERR     DDRPHYC_DX2GSR1_RVIERR_Msk           /*!< RV intermittent error for rank */
#define DDRPHYC_DX2GSR1_RVPASS_Pos (20U)
#define DDRPHYC_DX2GSR1_RVPASS_Msk (0x7U << DDRPHYC_DX2GSR1_RVPASS_Pos) /*!< 0x00700000 */
#define DDRPHYC_DX2GSR1_RVPASS     DDRPHYC_DX2GSR1_RVPASS_Msk           /*!< Read valid training pass count */
#define DDRPHYC_DX2GSR1_RVPASS_0   (0x1U << DDRPHYC_DX2GSR1_RVPASS_Pos) /*!< 0x00100000 */
#define DDRPHYC_DX2GSR1_RVPASS_1   (0x2U << DDRPHYC_DX2GSR1_RVPASS_Pos) /*!< 0x00200000 */
#define DDRPHYC_DX2GSR1_RVPASS_2   (0x4U << DDRPHYC_DX2GSR1_RVPASS_Pos) /*!< 0x00400000 */

/***************  Bit definition for DDRPHYC_DX2DLLCR register  ***************/
#define DDRPHYC_DX2DLLCR_SFBDLY_Pos   (0U)
#define DDRPHYC_DX2DLLCR_SFBDLY_Msk   (0x7U << DDRPHYC_DX2DLLCR_SFBDLY_Pos)   /*!< 0x00000007 */
#define DDRPHYC_DX2DLLCR_SFBDLY       DDRPHYC_DX2DLLCR_SFBDLY_Msk             /*!< Slave DLL feed-back trim */
#define DDRPHYC_DX2DLLCR_SFBDLY_0     (0x1U << DDRPHYC_DX2DLLCR_SFBDLY_Pos)   /*!< 0x00000001 */
#define DDRPHYC_DX2DLLCR_SFBDLY_1     (0x2U << DDRPHYC_DX2DLLCR_SFBDLY_Pos)   /*!< 0x00000002 */
#define DDRPHYC_DX2DLLCR_SFBDLY_2     (0x4U << DDRPHYC_DX2DLLCR_SFBDLY_Pos)   /*!< 0x00000004 */
#define DDRPHYC_DX2DLLCR_SFWDLY_Pos   (3U)
#define DDRPHYC_DX2DLLCR_SFWDLY_Msk   (0x7U << DDRPHYC_DX2DLLCR_SFWDLY_Pos)   /*!< 0x00000038 */
#define DDRPHYC_DX2DLLCR_SFWDLY       DDRPHYC_DX2DLLCR_SFWDLY_Msk             /*!< Slave DLL feed-forward trim */
#define DDRPHYC_DX2DLLCR_SFWDLY_0     (0x1U << DDRPHYC_DX2DLLCR_SFWDLY_Pos)   /*!< 0x00000008 */
#define DDRPHYC_DX2DLLCR_SFWDLY_1     (0x2U << DDRPHYC_DX2DLLCR_SFWDLY_Pos)   /*!< 0x00000010 */
#define DDRPHYC_DX2DLLCR_SFWDLY_2     (0x4U << DDRPHYC_DX2DLLCR_SFWDLY_Pos)   /*!< 0x00000020 */
#define DDRPHYC_DX2DLLCR_MFBDLY_Pos   (6U)
#define DDRPHYC_DX2DLLCR_MFBDLY_Msk   (0x7U << DDRPHYC_DX2DLLCR_MFBDLY_Pos)   /*!< 0x000001C0 */
#define DDRPHYC_DX2DLLCR_MFBDLY       DDRPHYC_DX2DLLCR_MFBDLY_Msk             /*!< Master DLL feed-back trim */
#define DDRPHYC_DX2DLLCR_MFBDLY_0     (0x1U << DDRPHYC_DX2DLLCR_MFBDLY_Pos)   /*!< 0x00000040 */
#define DDRPHYC_DX2DLLCR_MFBDLY_1     (0x2U << DDRPHYC_DX2DLLCR_MFBDLY_Pos)   /*!< 0x00000080 */
#define DDRPHYC_DX2DLLCR_MFBDLY_2     (0x4U << DDRPHYC_DX2DLLCR_MFBDLY_Pos)   /*!< 0x00000100 */
#define DDRPHYC_DX2DLLCR_MFWDLY_Pos   (9U)
#define DDRPHYC_DX2DLLCR_MFWDLY_Msk   (0x7U << DDRPHYC_DX2DLLCR_MFWDLY_Pos)   /*!< 0x00000E00 */
#define DDRPHYC_DX2DLLCR_MFWDLY       DDRPHYC_DX2DLLCR_MFWDLY_Msk             /*!< Master DLL feed-forward trim */
#define DDRPHYC_DX2DLLCR_MFWDLY_0     (0x1U << DDRPHYC_DX2DLLCR_MFWDLY_Pos)   /*!< 0x00000200 */
#define DDRPHYC_DX2DLLCR_MFWDLY_1     (0x2U << DDRPHYC_DX2DLLCR_MFWDLY_Pos)   /*!< 0x00000400 */
#define DDRPHYC_DX2DLLCR_MFWDLY_2     (0x4U << DDRPHYC_DX2DLLCR_MFWDLY_Pos)   /*!< 0x00000800 */
#define DDRPHYC_DX2DLLCR_SSTART_Pos   (12U)
#define DDRPHYC_DX2DLLCR_SSTART_Msk   (0x3U << DDRPHYC_DX2DLLCR_SSTART_Pos)   /*!< 0x00003000 */
#define DDRPHYC_DX2DLLCR_SSTART       DDRPHYC_DX2DLLCR_SSTART_Msk             /*!< Slave DLL autostart */
#define DDRPHYC_DX2DLLCR_SSTART_0     (0x1U << DDRPHYC_DX2DLLCR_SSTART_Pos)   /*!< 0x00001000 */
#define DDRPHYC_DX2DLLCR_SSTART_1     (0x2U << DDRPHYC_DX2DLLCR_SSTART_Pos)   /*!< 0x00002000 */
#define DDRPHYC_DX2DLLCR_SDPHASE_Pos  (14U)
#define DDRPHYC_DX2DLLCR_SDPHASE_Msk  (0xFU << DDRPHYC_DX2DLLCR_SDPHASE_Pos)  /*!< 0x0003C000 */
#define DDRPHYC_DX2DLLCR_SDPHASE      DDRPHYC_DX2DLLCR_SDPHASE_Msk            /*!< Slave DLL phase */
#define DDRPHYC_DX2DLLCR_SDPHASE_0    (0x1U << DDRPHYC_DX2DLLCR_SDPHASE_Pos)  /*!< 0x00004000 */
#define DDRPHYC_DX2DLLCR_SDPHASE_1    (0x2U << DDRPHYC_DX2DLLCR_SDPHASE_Pos)  /*!< 0x00008000 */
#define DDRPHYC_DX2DLLCR_SDPHASE_2    (0x4U << DDRPHYC_DX2DLLCR_SDPHASE_Pos)  /*!< 0x00010000 */
#define DDRPHYC_DX2DLLCR_SDPHASE_3    (0x8U << DDRPHYC_DX2DLLCR_SDPHASE_Pos)  /*!< 0x00020000 */
#define DDRPHYC_DX2DLLCR_ATESTEN_Pos  (18U)
#define DDRPHYC_DX2DLLCR_ATESTEN_Msk  (0x1U << DDRPHYC_DX2DLLCR_ATESTEN_Pos)  /*!< 0x00040000 */
#define DDRPHYC_DX2DLLCR_ATESTEN      DDRPHYC_DX2DLLCR_ATESTEN_Msk            /*!< Enable path to pin 'ATO' */
#define DDRPHYC_DX2DLLCR_SDLBMODE_Pos (19U)
#define DDRPHYC_DX2DLLCR_SDLBMODE_Msk (0x1U << DDRPHYC_DX2DLLCR_SDLBMODE_Pos) /*!< 0x00080000 */
#define DDRPHYC_DX2DLLCR_SDLBMODE     DDRPHYC_DX2DLLCR_SDLBMODE_Msk           /*!< Bypass slave DLL during loopback */
#define DDRPHYC_DX2DLLCR_DLLSRST_Pos  (30U)
#define DDRPHYC_DX2DLLCR_DLLSRST_Msk  (0x1U << DDRPHYC_DX2DLLCR_DLLSRST_Pos)  /*!< 0x40000000 */
#define DDRPHYC_DX2DLLCR_DLLSRST      DDRPHYC_DX2DLLCR_DLLSRST_Msk            /*!< DLL reset */
#define DDRPHYC_DX2DLLCR_DLLDIS_Pos   (31U)
#define DDRPHYC_DX2DLLCR_DLLDIS_Msk   (0x1U << DDRPHYC_DX2DLLCR_DLLDIS_Pos)   /*!< 0x80000000 */
#define DDRPHYC_DX2DLLCR_DLLDIS       DDRPHYC_DX2DLLCR_DLLDIS_Msk             /*!< DLL bypass */

/***************  Bit definition for DDRPHYC_DX2DQTR register  ****************/
#define DDRPHYC_DX2DQTR_DQDLY0_Pos (0U)
#define DDRPHYC_DX2DQTR_DQDLY0_Msk (0xFU << DDRPHYC_DX2DQTR_DQDLY0_Pos) /*!< 0x0000000F */
#define DDRPHYC_DX2DQTR_DQDLY0     DDRPHYC_DX2DQTR_DQDLY0_Msk           /*!< DQ delay for bit 0 */
#define DDRPHYC_DX2DQTR_DQDLY0_0   (0x1U << DDRPHYC_DX2DQTR_DQDLY0_Pos) /*!< 0x00000001 */
#define DDRPHYC_DX2DQTR_DQDLY0_1   (0x2U << DDRPHYC_DX2DQTR_DQDLY0_Pos) /*!< 0x00000002 */
#define DDRPHYC_DX2DQTR_DQDLY0_2   (0x4U << DDRPHYC_DX2DQTR_DQDLY0_Pos) /*!< 0x00000004 */
#define DDRPHYC_DX2DQTR_DQDLY0_3   (0x8U << DDRPHYC_DX2DQTR_DQDLY0_Pos) /*!< 0x00000008 */
#define DDRPHYC_DX2DQTR_DQDLY1_Pos (4U)
#define DDRPHYC_DX2DQTR_DQDLY1_Msk (0xFU << DDRPHYC_DX2DQTR_DQDLY1_Pos) /*!< 0x000000F0 */
#define DDRPHYC_DX2DQTR_DQDLY1     DDRPHYC_DX2DQTR_DQDLY1_Msk           /*!< DQ delay for bit 1 */
#define DDRPHYC_DX2DQTR_DQDLY1_0   (0x1U << DDRPHYC_DX2DQTR_DQDLY1_Pos) /*!< 0x00000010 */
#define DDRPHYC_DX2DQTR_DQDLY1_1   (0x2U << DDRPHYC_DX2DQTR_DQDLY1_Pos) /*!< 0x00000020 */
#define DDRPHYC_DX2DQTR_DQDLY1_2   (0x4U << DDRPHYC_DX2DQTR_DQDLY1_Pos) /*!< 0x00000040 */
#define DDRPHYC_DX2DQTR_DQDLY1_3   (0x8U << DDRPHYC_DX2DQTR_DQDLY1_Pos) /*!< 0x00000080 */
#define DDRPHYC_DX2DQTR_DQDLY2_Pos (8U)
#define DDRPHYC_DX2DQTR_DQDLY2_Msk (0xFU << DDRPHYC_DX2DQTR_DQDLY2_Pos) /*!< 0x00000F00 */
#define DDRPHYC_DX2DQTR_DQDLY2     DDRPHYC_DX2DQTR_DQDLY2_Msk           /*!< DQ delay for bit 2 */
#define DDRPHYC_DX2DQTR_DQDLY2_0   (0x1U << DDRPHYC_DX2DQTR_DQDLY2_Pos) /*!< 0x00000100 */
#define DDRPHYC_DX2DQTR_DQDLY2_1   (0x2U << DDRPHYC_DX2DQTR_DQDLY2_Pos) /*!< 0x00000200 */
#define DDRPHYC_DX2DQTR_DQDLY2_2   (0x4U << DDRPHYC_DX2DQTR_DQDLY2_Pos) /*!< 0x00000400 */
#define DDRPHYC_DX2DQTR_DQDLY2_3   (0x8U << DDRPHYC_DX2DQTR_DQDLY2_Pos) /*!< 0x00000800 */
#define DDRPHYC_DX2DQTR_DQDLY3_Pos (12U)
#define DDRPHYC_DX2DQTR_DQDLY3_Msk (0xFU << DDRPHYC_DX2DQTR_DQDLY3_Pos) /*!< 0x0000F000 */
#define DDRPHYC_DX2DQTR_DQDLY3     DDRPHYC_DX2DQTR_DQDLY3_Msk           /*!< DQ delay for bit 3 */
#define DDRPHYC_DX2DQTR_DQDLY3_0   (0x1U << DDRPHYC_DX2DQTR_DQDLY3_Pos) /*!< 0x00001000 */
#define DDRPHYC_DX2DQTR_DQDLY3_1   (0x2U << DDRPHYC_DX2DQTR_DQDLY3_Pos) /*!< 0x00002000 */
#define DDRPHYC_DX2DQTR_DQDLY3_2   (0x4U << DDRPHYC_DX2DQTR_DQDLY3_Pos) /*!< 0x00004000 */
#define DDRPHYC_DX2DQTR_DQDLY3_3   (0x8U << DDRPHYC_DX2DQTR_DQDLY3_Pos) /*!< 0x00008000 */
#define DDRPHYC_DX2DQTR_DQDLY4_Pos (16U)
#define DDRPHYC_DX2DQTR_DQDLY4_Msk (0xFU << DDRPHYC_DX2DQTR_DQDLY4_Pos) /*!< 0x000F0000 */
#define DDRPHYC_DX2DQTR_DQDLY4     DDRPHYC_DX2DQTR_DQDLY4_Msk           /*!< DQ delay for bit 4 */
#define DDRPHYC_DX2DQTR_DQDLY4_0   (0x1U << DDRPHYC_DX2DQTR_DQDLY4_Pos) /*!< 0x00010000 */
#define DDRPHYC_DX2DQTR_DQDLY4_1   (0x2U << DDRPHYC_DX2DQTR_DQDLY4_Pos) /*!< 0x00020000 */
#define DDRPHYC_DX2DQTR_DQDLY4_2   (0x4U << DDRPHYC_DX2DQTR_DQDLY4_Pos) /*!< 0x00040000 */
#define DDRPHYC_DX2DQTR_DQDLY4_3   (0x8U << DDRPHYC_DX2DQTR_DQDLY4_Pos) /*!< 0x00080000 */
#define DDRPHYC_DX2DQTR_DQDLY5_Pos (20U)
#define DDRPHYC_DX2DQTR_DQDLY5_Msk (0xFU << DDRPHYC_DX2DQTR_DQDLY5_Pos) /*!< 0x00F00000 */
#define DDRPHYC_DX2DQTR_DQDLY5     DDRPHYC_DX2DQTR_DQDLY5_Msk           /*!< DQ delay for bit 5 */
#define DDRPHYC_DX2DQTR_DQDLY5_0   (0x1U << DDRPHYC_DX2DQTR_DQDLY5_Pos) /*!< 0x00100000 */
#define DDRPHYC_DX2DQTR_DQDLY5_1   (0x2U << DDRPHYC_DX2DQTR_DQDLY5_Pos) /*!< 0x00200000 */
#define DDRPHYC_DX2DQTR_DQDLY5_2   (0x4U << DDRPHYC_DX2DQTR_DQDLY5_Pos) /*!< 0x00400000 */
#define DDRPHYC_DX2DQTR_DQDLY5_3   (0x8U << DDRPHYC_DX2DQTR_DQDLY5_Pos) /*!< 0x00800000 */
#define DDRPHYC_DX2DQTR_DQDLY6_Pos (24U)
#define DDRPHYC_DX2DQTR_DQDLY6_Msk (0xFU << DDRPHYC_DX2DQTR_DQDLY6_Pos) /*!< 0x0F000000 */
#define DDRPHYC_DX2DQTR_DQDLY6     DDRPHYC_DX2DQTR_DQDLY6_Msk           /*!< DQ delay for bit 6 */
#define DDRPHYC_DX2DQTR_DQDLY6_0   (0x1U << DDRPHYC_DX2DQTR_DQDLY6_Pos) /*!< 0x01000000 */
#define DDRPHYC_DX2DQTR_DQDLY6_1   (0x2U << DDRPHYC_DX2DQTR_DQDLY6_Pos) /*!< 0x02000000 */
#define DDRPHYC_DX2DQTR_DQDLY6_2   (0x4U << DDRPHYC_DX2DQTR_DQDLY6_Pos) /*!< 0x04000000 */
#define DDRPHYC_DX2DQTR_DQDLY6_3   (0x8U << DDRPHYC_DX2DQTR_DQDLY6_Pos) /*!< 0x08000000 */
#define DDRPHYC_DX2DQTR_DQDLY7_Pos (28U)
#define DDRPHYC_DX2DQTR_DQDLY7_Msk (0xFU << DDRPHYC_DX2DQTR_DQDLY7_Pos) /*!< 0xF0000000 */
#define DDRPHYC_DX2DQTR_DQDLY7     DDRPHYC_DX2DQTR_DQDLY7_Msk           /*!< DQ delay for bit 7 */
#define DDRPHYC_DX2DQTR_DQDLY7_0   (0x1U << DDRPHYC_DX2DQTR_DQDLY7_Pos) /*!< 0x10000000 */
#define DDRPHYC_DX2DQTR_DQDLY7_1   (0x2U << DDRPHYC_DX2DQTR_DQDLY7_Pos) /*!< 0x20000000 */
#define DDRPHYC_DX2DQTR_DQDLY7_2   (0x4U << DDRPHYC_DX2DQTR_DQDLY7_Pos) /*!< 0x40000000 */
#define DDRPHYC_DX2DQTR_DQDLY7_3   (0x8U << DDRPHYC_DX2DQTR_DQDLY7_Pos) /*!< 0x80000000 */

/***************  Bit definition for DDRPHYC_DX2DQSTR register  ***************/
#define DDRPHYC_DX2DQSTR_R0DGSL_Pos  (0U)
#define DDRPHYC_DX2DQSTR_R0DGSL_Msk  (0x7U << DDRPHYC_DX2DQSTR_R0DGSL_Pos)  /*!< 0x00000007 */
#define DDRPHYC_DX2DQSTR_R0DGSL      DDRPHYC_DX2DQSTR_R0DGSL_Msk            /*!< Rank 0 DQS gating system latency */
#define DDRPHYC_DX2DQSTR_R0DGSL_0    (0x1U << DDRPHYC_DX2DQSTR_R0DGSL_Pos)  /*!< 0x00000001 */
#define DDRPHYC_DX2DQSTR_R0DGSL_1    (0x2U << DDRPHYC_DX2DQSTR_R0DGSL_Pos)  /*!< 0x00000002 */
#define DDRPHYC_DX2DQSTR_R0DGSL_2    (0x4U << DDRPHYC_DX2DQSTR_R0DGSL_Pos)  /*!< 0x00000004 */
#define DDRPHYC_DX2DQSTR_R0DGPS_Pos  (12U)
#define DDRPHYC_DX2DQSTR_R0DGPS_Msk  (0x3U << DDRPHYC_DX2DQSTR_R0DGPS_Pos)  /*!< 0x00003000 */
#define DDRPHYC_DX2DQSTR_R0DGPS      DDRPHYC_DX2DQSTR_R0DGPS_Msk            /*!< Rank 0 DQS gating phase select */
#define DDRPHYC_DX2DQSTR_R0DGPS_0    (0x1U << DDRPHYC_DX2DQSTR_R0DGPS_Pos)  /*!< 0x00001000 */
#define DDRPHYC_DX2DQSTR_R0DGPS_1    (0x2U << DDRPHYC_DX2DQSTR_R0DGPS_Pos)  /*!< 0x00002000 */
#define DDRPHYC_DX2DQSTR_DQSDLY_Pos  (20U)
#define DDRPHYC_DX2DQSTR_DQSDLY_Msk  (0x7U << DDRPHYC_DX2DQSTR_DQSDLY_Pos)  /*!< 0x00700000 */
#define DDRPHYC_DX2DQSTR_DQSDLY      DDRPHYC_DX2DQSTR_DQSDLY_Msk            /*!< DQS delay */
#define DDRPHYC_DX2DQSTR_DQSDLY_0    (0x1U << DDRPHYC_DX2DQSTR_DQSDLY_Pos)  /*!< 0x00100000 */
#define DDRPHYC_DX2DQSTR_DQSDLY_1    (0x2U << DDRPHYC_DX2DQSTR_DQSDLY_Pos)  /*!< 0x00200000 */
#define DDRPHYC_DX2DQSTR_DQSDLY_2    (0x4U << DDRPHYC_DX2DQSTR_DQSDLY_Pos)  /*!< 0x00400000 */
#define DDRPHYC_DX2DQSTR_DQSNDLY_Pos (23U)
#define DDRPHYC_DX2DQSTR_DQSNDLY_Msk (0x7U << DDRPHYC_DX2DQSTR_DQSNDLY_Pos) /*!< 0x03800000 */
#define DDRPHYC_DX2DQSTR_DQSNDLY     DDRPHYC_DX2DQSTR_DQSNDLY_Msk           /*!< DQS# delay */
#define DDRPHYC_DX2DQSTR_DQSNDLY_0   (0x1U << DDRPHYC_DX2DQSTR_DQSNDLY_Pos) /*!< 0x00800000 */
#define DDRPHYC_DX2DQSTR_DQSNDLY_1   (0x2U << DDRPHYC_DX2DQSTR_DQSNDLY_Pos) /*!< 0x01000000 */
#define DDRPHYC_DX2DQSTR_DQSNDLY_2   (0x4U << DDRPHYC_DX2DQSTR_DQSNDLY_Pos) /*!< 0x02000000 */
#define DDRPHYC_DX2DQSTR_DMDLY_Pos   (26U)
#define DDRPHYC_DX2DQSTR_DMDLY_Msk   (0xFU << DDRPHYC_DX2DQSTR_DMDLY_Pos)   /*!< 0x3C000000 */
#define DDRPHYC_DX2DQSTR_DMDLY       DDRPHYC_DX2DQSTR_DMDLY_Msk             /*!< DM delay */
#define DDRPHYC_DX2DQSTR_DMDLY_0     (0x1U << DDRPHYC_DX2DQSTR_DMDLY_Pos)   /*!< 0x04000000 */
#define DDRPHYC_DX2DQSTR_DMDLY_1     (0x2U << DDRPHYC_DX2DQSTR_DMDLY_Pos)   /*!< 0x08000000 */
#define DDRPHYC_DX2DQSTR_DMDLY_2     (0x4U << DDRPHYC_DX2DQSTR_DMDLY_Pos)   /*!< 0x10000000 */
#define DDRPHYC_DX2DQSTR_DMDLY_3     (0x8U << DDRPHYC_DX2DQSTR_DMDLY_Pos)   /*!< 0x20000000 */

/****************  Bit definition for DDRPHYC_DX3GCR register  ****************/
#define DDRPHYC_DX3GCR_DXEN_Pos   (0U)
#define DDRPHYC_DX3GCR_DXEN_Msk   (0x1U << DDRPHYC_DX3GCR_DXEN_Pos)   /*!< 0x00000001 */
#define DDRPHYC_DX3GCR_DXEN       DDRPHYC_DX3GCR_DXEN_Msk             /*!< DATA byte enable */
#define DDRPHYC_DX3GCR_DQSODT_Pos (1U)
#define DDRPHYC_DX3GCR_DQSODT_Msk (0x1U << DDRPHYC_DX3GCR_DQSODT_Pos) /*!< 0x00000002 */
#define DDRPHYC_DX3GCR_DQSODT     DDRPHYC_DX3GCR_DQSODT_Msk           /*!< DQS ODT enable */
#define DDRPHYC_DX3GCR_DQODT_Pos  (2U)
#define DDRPHYC_DX3GCR_DQODT_Msk  (0x1U << DDRPHYC_DX3GCR_DQODT_Pos)  /*!< 0x00000004 */
#define DDRPHYC_DX3GCR_DQODT      DDRPHYC_DX3GCR_DQODT_Msk            /*!< DQ ODT enable */
#define DDRPHYC_DX3GCR_DXIOM_Pos  (3U)
#define DDRPHYC_DX3GCR_DXIOM_Msk  (0x1U << DDRPHYC_DX3GCR_DXIOM_Pos)  /*!< 0x00000008 */
#define DDRPHYC_DX3GCR_DXIOM      DDRPHYC_DX3GCR_DXIOM_Msk            /*!< Data I/O mode */
#define DDRPHYC_DX3GCR_DXPDD_Pos  (4U)
#define DDRPHYC_DX3GCR_DXPDD_Msk  (0x1U << DDRPHYC_DX3GCR_DXPDD_Pos)  /*!< 0x00000010 */
#define DDRPHYC_DX3GCR_DXPDD      DDRPHYC_DX3GCR_DXPDD_Msk            /*!< Data power-down driver */
#define DDRPHYC_DX3GCR_DXPDR_Pos  (5U)
#define DDRPHYC_DX3GCR_DXPDR_Msk  (0x1U << DDRPHYC_DX3GCR_DXPDR_Pos)  /*!< 0x00000020 */
#define DDRPHYC_DX3GCR_DXPDR      DDRPHYC_DX3GCR_DXPDR_Msk            /*!< Data power-down receiver */
#define DDRPHYC_DX3GCR_DQSRPD_Pos (6U)
#define DDRPHYC_DX3GCR_DQSRPD_Msk (0x1U << DDRPHYC_DX3GCR_DQSRPD_Pos) /*!< 0x00000040 */
#define DDRPHYC_DX3GCR_DQSRPD     DDRPHYC_DX3GCR_DQSRPD_Msk           /*!< DQSR power-down */
#define DDRPHYC_DX3GCR_DSEN_Pos   (7U)
#define DDRPHYC_DX3GCR_DSEN_Msk   (0x3U << DDRPHYC_DX3GCR_DSEN_Pos)   /*!< 0x00000180 */
#define DDRPHYC_DX3GCR_DSEN       DDRPHYC_DX3GCR_DSEN_Msk             /*!< Write DQS enable */
#define DDRPHYC_DX3GCR_DSEN_0     (0x1U << DDRPHYC_DX3GCR_DSEN_Pos)   /*!< 0x00000080 */
#define DDRPHYC_DX3GCR_DSEN_1     (0x2U << DDRPHYC_DX3GCR_DSEN_Pos)   /*!< 0x00000100 */
#define DDRPHYC_DX3GCR_DQSRTT_Pos (9U)
#define DDRPHYC_DX3GCR_DQSRTT_Msk (0x1U << DDRPHYC_DX3GCR_DQSRTT_Pos) /*!< 0x00000200 */
#define DDRPHYC_DX3GCR_DQSRTT     DDRPHYC_DX3GCR_DQSRTT_Msk           /*!< DQS dynamic RTT control */
#define DDRPHYC_DX3GCR_DQRTT_Pos  (10U)
#define DDRPHYC_DX3GCR_DQRTT_Msk  (0x1U << DDRPHYC_DX3GCR_DQRTT_Pos)  /*!< 0x00000400 */
#define DDRPHYC_DX3GCR_DQRTT      DDRPHYC_DX3GCR_DQRTT_Msk            /*!< DQ dynamic RTT control */
#define DDRPHYC_DX3GCR_RTTOH_Pos  (11U)
#define DDRPHYC_DX3GCR_RTTOH_Msk  (0x3U << DDRPHYC_DX3GCR_RTTOH_Pos)  /*!< 0x00001800 */
#define DDRPHYC_DX3GCR_RTTOH      DDRPHYC_DX3GCR_RTTOH_Msk            /*!< RTT output hold */
#define DDRPHYC_DX3GCR_RTTOH_0    (0x1U << DDRPHYC_DX3GCR_RTTOH_Pos)  /*!< 0x00000800 */
#define DDRPHYC_DX3GCR_RTTOH_1    (0x2U << DDRPHYC_DX3GCR_RTTOH_Pos)  /*!< 0x00001000 */
#define DDRPHYC_DX3GCR_RTTOAL_Pos (13U)
#define DDRPHYC_DX3GCR_RTTOAL_Msk (0x1U << DDRPHYC_DX3GCR_RTTOAL_Pos) /*!< 0x00002000 */
#define DDRPHYC_DX3GCR_RTTOAL     DDRPHYC_DX3GCR_RTTOAL_Msk           /*!< RTT ON additive latency */
#define DDRPHYC_DX3GCR_R0RVSL_Pos (14U)
#define DDRPHYC_DX3GCR_R0RVSL_Msk (0x7U << DDRPHYC_DX3GCR_R0RVSL_Pos) /*!< 0x0001C000 */
#define DDRPHYC_DX3GCR_R0RVSL     DDRPHYC_DX3GCR_R0RVSL_Msk           /*!< Read valid system latency in steps */
#define DDRPHYC_DX3GCR_R0RVSL_0   (0x1U << DDRPHYC_DX3GCR_R0RVSL_Pos) /*!< 0x00004000 */
#define DDRPHYC_DX3GCR_R0RVSL_1   (0x2U << DDRPHYC_DX3GCR_R0RVSL_Pos) /*!< 0x00008000 */
#define DDRPHYC_DX3GCR_R0RVSL_2   (0x4U << DDRPHYC_DX3GCR_R0RVSL_Pos) /*!< 0x00010000 */

/***************  Bit definition for DDRPHYC_DX3GSR0 register  ****************/
#define DDRPHYC_DX3GSR0_DTDONE_Pos (0U)
#define DDRPHYC_DX3GSR0_DTDONE_Msk (0x1U << DDRPHYC_DX3GSR0_DTDONE_Pos) /*!< 0x00000001 */
#define DDRPHYC_DX3GSR0_DTDONE     DDRPHYC_DX3GSR0_DTDONE_Msk           /*!< Data training done */
#define DDRPHYC_DX3GSR0_DTERR_Pos  (4U)
#define DDRPHYC_DX3GSR0_DTERR_Msk  (0x1U << DDRPHYC_DX3GSR0_DTERR_Pos)  /*!< 0x00000010 */
#define DDRPHYC_DX3GSR0_DTERR      DDRPHYC_DX3GSR0_DTERR_Msk            /*!< DQS gate training error */
#define DDRPHYC_DX3GSR0_DTIERR_Pos (8U)
#define DDRPHYC_DX3GSR0_DTIERR_Msk (0x1U << DDRPHYC_DX3GSR0_DTIERR_Pos) /*!< 0x00000100 */
#define DDRPHYC_DX3GSR0_DTIERR     DDRPHYC_DX3GSR0_DTIERR_Msk           /*!< DQS gate training intermittent error */
#define DDRPHYC_DX3GSR0_DTPASS_Pos (13U)
#define DDRPHYC_DX3GSR0_DTPASS_Msk (0x7U << DDRPHYC_DX3GSR0_DTPASS_Pos) /*!< 0x0000E000 */
#define DDRPHYC_DX3GSR0_DTPASS     DDRPHYC_DX3GSR0_DTPASS_Msk           /*!< DQS training pass count */
#define DDRPHYC_DX3GSR0_DTPASS_0   (0x1U << DDRPHYC_DX3GSR0_DTPASS_Pos) /*!< 0x00002000 */
#define DDRPHYC_DX3GSR0_DTPASS_1   (0x2U << DDRPHYC_DX3GSR0_DTPASS_Pos) /*!< 0x00004000 */
#define DDRPHYC_DX3GSR0_DTPASS_2   (0x4U << DDRPHYC_DX3GSR0_DTPASS_Pos) /*!< 0x00008000 */

/***************  Bit definition for DDRPHYC_DX3GSR1 register  ****************/
#define DDRPHYC_DX3GSR1_DFTERR_Pos (0U)
#define DDRPHYC_DX3GSR1_DFTERR_Msk (0x1U << DDRPHYC_DX3GSR1_DFTERR_Pos) /*!< 0x00000001 */
#define DDRPHYC_DX3GSR1_DFTERR     DDRPHYC_DX3GSR1_DFTERR_Msk           /*!< DQS drift error */
#define DDRPHYC_DX3GSR1_DQSDFT_Pos (4U)
#define DDRPHYC_DX3GSR1_DQSDFT_Msk (0x3U << DDRPHYC_DX3GSR1_DQSDFT_Pos) /*!< 0x00000030 */
#define DDRPHYC_DX3GSR1_DQSDFT     DDRPHYC_DX3GSR1_DQSDFT_Msk           /*!< DQS drift value */
#define DDRPHYC_DX3GSR1_DQSDFT_0   (0x1U << DDRPHYC_DX3GSR1_DQSDFT_Pos) /*!< 0x00000010 */
#define DDRPHYC_DX3GSR1_DQSDFT_1   (0x2U << DDRPHYC_DX3GSR1_DQSDFT_Pos) /*!< 0x00000020 */
#define DDRPHYC_DX3GSR1_RVERR_Pos  (12U)
#define DDRPHYC_DX3GSR1_RVERR_Msk  (0x1U << DDRPHYC_DX3GSR1_RVERR_Pos)  /*!< 0x00001000 */
#define DDRPHYC_DX3GSR1_RVERR      DDRPHYC_DX3GSR1_RVERR_Msk            /*!< RV training error */
#define DDRPHYC_DX3GSR1_RVIERR_Pos (16U)
#define DDRPHYC_DX3GSR1_RVIERR_Msk (0x1U << DDRPHYC_DX3GSR1_RVIERR_Pos) /*!< 0x00010000 */
#define DDRPHYC_DX3GSR1_RVIERR     DDRPHYC_DX3GSR1_RVIERR_Msk           /*!< RV intermittent error for rank */
#define DDRPHYC_DX3GSR1_RVPASS_Pos (20U)
#define DDRPHYC_DX3GSR1_RVPASS_Msk (0x7U << DDRPHYC_DX3GSR1_RVPASS_Pos) /*!< 0x00700000 */
#define DDRPHYC_DX3GSR1_RVPASS     DDRPHYC_DX3GSR1_RVPASS_Msk           /*!< Read valid training pass count */
#define DDRPHYC_DX3GSR1_RVPASS_0   (0x1U << DDRPHYC_DX3GSR1_RVPASS_Pos) /*!< 0x00100000 */
#define DDRPHYC_DX3GSR1_RVPASS_1   (0x2U << DDRPHYC_DX3GSR1_RVPASS_Pos) /*!< 0x00200000 */
#define DDRPHYC_DX3GSR1_RVPASS_2   (0x4U << DDRPHYC_DX3GSR1_RVPASS_Pos) /*!< 0x00400000 */

/***************  Bit definition for DDRPHYC_DX3DLLCR register  ***************/
#define DDRPHYC_DX3DLLCR_SFBDLY_Pos   (0U)
#define DDRPHYC_DX3DLLCR_SFBDLY_Msk   (0x7U << DDRPHYC_DX3DLLCR_SFBDLY_Pos)   /*!< 0x00000007 */
#define DDRPHYC_DX3DLLCR_SFBDLY       DDRPHYC_DX3DLLCR_SFBDLY_Msk             /*!< Slave DLL feed-back trim */
#define DDRPHYC_DX3DLLCR_SFBDLY_0     (0x1U << DDRPHYC_DX3DLLCR_SFBDLY_Pos)   /*!< 0x00000001 */
#define DDRPHYC_DX3DLLCR_SFBDLY_1     (0x2U << DDRPHYC_DX3DLLCR_SFBDLY_Pos)   /*!< 0x00000002 */
#define DDRPHYC_DX3DLLCR_SFBDLY_2     (0x4U << DDRPHYC_DX3DLLCR_SFBDLY_Pos)   /*!< 0x00000004 */
#define DDRPHYC_DX3DLLCR_SFWDLY_Pos   (3U)
#define DDRPHYC_DX3DLLCR_SFWDLY_Msk   (0x7U << DDRPHYC_DX3DLLCR_SFWDLY_Pos)   /*!< 0x00000038 */
#define DDRPHYC_DX3DLLCR_SFWDLY       DDRPHYC_DX3DLLCR_SFWDLY_Msk             /*!< Slave DLL feed-forward trim */
#define DDRPHYC_DX3DLLCR_SFWDLY_0     (0x1U << DDRPHYC_DX3DLLCR_SFWDLY_Pos)   /*!< 0x00000008 */
#define DDRPHYC_DX3DLLCR_SFWDLY_1     (0x2U << DDRPHYC_DX3DLLCR_SFWDLY_Pos)   /*!< 0x00000010 */
#define DDRPHYC_DX3DLLCR_SFWDLY_2     (0x4U << DDRPHYC_DX3DLLCR_SFWDLY_Pos)   /*!< 0x00000020 */
#define DDRPHYC_DX3DLLCR_MFBDLY_Pos   (6U)
#define DDRPHYC_DX3DLLCR_MFBDLY_Msk   (0x7U << DDRPHYC_DX3DLLCR_MFBDLY_Pos)   /*!< 0x000001C0 */
#define DDRPHYC_DX3DLLCR_MFBDLY       DDRPHYC_DX3DLLCR_MFBDLY_Msk             /*!< Master DLL feed-back trim */
#define DDRPHYC_DX3DLLCR_MFBDLY_0     (0x1U << DDRPHYC_DX3DLLCR_MFBDLY_Pos)   /*!< 0x00000040 */
#define DDRPHYC_DX3DLLCR_MFBDLY_1     (0x2U << DDRPHYC_DX3DLLCR_MFBDLY_Pos)   /*!< 0x00000080 */
#define DDRPHYC_DX3DLLCR_MFBDLY_2     (0x4U << DDRPHYC_DX3DLLCR_MFBDLY_Pos)   /*!< 0x00000100 */
#define DDRPHYC_DX3DLLCR_MFWDLY_Pos   (9U)
#define DDRPHYC_DX3DLLCR_MFWDLY_Msk   (0x7U << DDRPHYC_DX3DLLCR_MFWDLY_Pos)   /*!< 0x00000E00 */
#define DDRPHYC_DX3DLLCR_MFWDLY       DDRPHYC_DX3DLLCR_MFWDLY_Msk             /*!< Master DLL feed-forward trim */
#define DDRPHYC_DX3DLLCR_MFWDLY_0     (0x1U << DDRPHYC_DX3DLLCR_MFWDLY_Pos)   /*!< 0x00000200 */
#define DDRPHYC_DX3DLLCR_MFWDLY_1     (0x2U << DDRPHYC_DX3DLLCR_MFWDLY_Pos)   /*!< 0x00000400 */
#define DDRPHYC_DX3DLLCR_MFWDLY_2     (0x4U << DDRPHYC_DX3DLLCR_MFWDLY_Pos)   /*!< 0x00000800 */
#define DDRPHYC_DX3DLLCR_SSTART_Pos   (12U)
#define DDRPHYC_DX3DLLCR_SSTART_Msk   (0x3U << DDRPHYC_DX3DLLCR_SSTART_Pos)   /*!< 0x00003000 */
#define DDRPHYC_DX3DLLCR_SSTART       DDRPHYC_DX3DLLCR_SSTART_Msk             /*!< Slave DLL autostart */
#define DDRPHYC_DX3DLLCR_SSTART_0     (0x1U << DDRPHYC_DX3DLLCR_SSTART_Pos)   /*!< 0x00001000 */
#define DDRPHYC_DX3DLLCR_SSTART_1     (0x2U << DDRPHYC_DX3DLLCR_SSTART_Pos)   /*!< 0x00002000 */
#define DDRPHYC_DX3DLLCR_SDPHASE_Pos  (14U)
#define DDRPHYC_DX3DLLCR_SDPHASE_Msk  (0xFU << DDRPHYC_DX3DLLCR_SDPHASE_Pos)  /*!< 0x0003C000 */
#define DDRPHYC_DX3DLLCR_SDPHASE      DDRPHYC_DX3DLLCR_SDPHASE_Msk            /*!< Slave DLL phase */
#define DDRPHYC_DX3DLLCR_SDPHASE_0    (0x1U << DDRPHYC_DX3DLLCR_SDPHASE_Pos)  /*!< 0x00004000 */
#define DDRPHYC_DX3DLLCR_SDPHASE_1    (0x2U << DDRPHYC_DX3DLLCR_SDPHASE_Pos)  /*!< 0x00008000 */
#define DDRPHYC_DX3DLLCR_SDPHASE_2    (0x4U << DDRPHYC_DX3DLLCR_SDPHASE_Pos)  /*!< 0x00010000 */
#define DDRPHYC_DX3DLLCR_SDPHASE_3    (0x8U << DDRPHYC_DX3DLLCR_SDPHASE_Pos)  /*!< 0x00020000 */
#define DDRPHYC_DX3DLLCR_ATESTEN_Pos  (18U)
#define DDRPHYC_DX3DLLCR_ATESTEN_Msk  (0x1U << DDRPHYC_DX3DLLCR_ATESTEN_Pos)  /*!< 0x00040000 */
#define DDRPHYC_DX3DLLCR_ATESTEN      DDRPHYC_DX3DLLCR_ATESTEN_Msk            /*!< Enable path to pin 'ATO' */
#define DDRPHYC_DX3DLLCR_SDLBMODE_Pos (19U)
#define DDRPHYC_DX3DLLCR_SDLBMODE_Msk (0x1U << DDRPHYC_DX3DLLCR_SDLBMODE_Pos) /*!< 0x00080000 */
#define DDRPHYC_DX3DLLCR_SDLBMODE     DDRPHYC_DX3DLLCR_SDLBMODE_Msk           /*!< Bypass slave DLL during loopback */
#define DDRPHYC_DX3DLLCR_DLLSRST_Pos  (30U)
#define DDRPHYC_DX3DLLCR_DLLSRST_Msk  (0x1U << DDRPHYC_DX3DLLCR_DLLSRST_Pos)  /*!< 0x40000000 */
#define DDRPHYC_DX3DLLCR_DLLSRST      DDRPHYC_DX3DLLCR_DLLSRST_Msk            /*!< DLL reset */
#define DDRPHYC_DX3DLLCR_DLLDIS_Pos   (31U)
#define DDRPHYC_DX3DLLCR_DLLDIS_Msk   (0x1U << DDRPHYC_DX3DLLCR_DLLDIS_Pos)   /*!< 0x80000000 */
#define DDRPHYC_DX3DLLCR_DLLDIS       DDRPHYC_DX3DLLCR_DLLDIS_Msk             /*!< DLL bypass */

/***************  Bit definition for DDRPHYC_DX3DQTR register  ****************/
#define DDRPHYC_DX3DQTR_DQDLY0_Pos (0U)
#define DDRPHYC_DX3DQTR_DQDLY0_Msk (0xFU << DDRPHYC_DX3DQTR_DQDLY0_Pos) /*!< 0x0000000F */
#define DDRPHYC_DX3DQTR_DQDLY0     DDRPHYC_DX3DQTR_DQDLY0_Msk           /*!< DQ delay for bit 0 */
#define DDRPHYC_DX3DQTR_DQDLY0_0   (0x1U << DDRPHYC_DX3DQTR_DQDLY0_Pos) /*!< 0x00000001 */
#define DDRPHYC_DX3DQTR_DQDLY0_1   (0x2U << DDRPHYC_DX3DQTR_DQDLY0_Pos) /*!< 0x00000002 */
#define DDRPHYC_DX3DQTR_DQDLY0_2   (0x4U << DDRPHYC_DX3DQTR_DQDLY0_Pos) /*!< 0x00000004 */
#define DDRPHYC_DX3DQTR_DQDLY0_3   (0x8U << DDRPHYC_DX3DQTR_DQDLY0_Pos) /*!< 0x00000008 */
#define DDRPHYC_DX3DQTR_DQDLY1_Pos (4U)
#define DDRPHYC_DX3DQTR_DQDLY1_Msk (0xFU << DDRPHYC_DX3DQTR_DQDLY1_Pos) /*!< 0x000000F0 */
#define DDRPHYC_DX3DQTR_DQDLY1     DDRPHYC_DX3DQTR_DQDLY1_Msk           /*!< DQ delay for bit 1 */
#define DDRPHYC_DX3DQTR_DQDLY1_0   (0x1U << DDRPHYC_DX3DQTR_DQDLY1_Pos) /*!< 0x00000010 */
#define DDRPHYC_DX3DQTR_DQDLY1_1   (0x2U << DDRPHYC_DX3DQTR_DQDLY1_Pos) /*!< 0x00000020 */
#define DDRPHYC_DX3DQTR_DQDLY1_2   (0x4U << DDRPHYC_DX3DQTR_DQDLY1_Pos) /*!< 0x00000040 */
#define DDRPHYC_DX3DQTR_DQDLY1_3   (0x8U << DDRPHYC_DX3DQTR_DQDLY1_Pos) /*!< 0x00000080 */
#define DDRPHYC_DX3DQTR_DQDLY2_Pos (8U)
#define DDRPHYC_DX3DQTR_DQDLY2_Msk (0xFU << DDRPHYC_DX3DQTR_DQDLY2_Pos) /*!< 0x00000F00 */
#define DDRPHYC_DX3DQTR_DQDLY2     DDRPHYC_DX3DQTR_DQDLY2_Msk           /*!< DQ delay for bit 2 */
#define DDRPHYC_DX3DQTR_DQDLY2_0   (0x1U << DDRPHYC_DX3DQTR_DQDLY2_Pos) /*!< 0x00000100 */
#define DDRPHYC_DX3DQTR_DQDLY2_1   (0x2U << DDRPHYC_DX3DQTR_DQDLY2_Pos) /*!< 0x00000200 */
#define DDRPHYC_DX3DQTR_DQDLY2_2   (0x4U << DDRPHYC_DX3DQTR_DQDLY2_Pos) /*!< 0x00000400 */
#define DDRPHYC_DX3DQTR_DQDLY2_3   (0x8U << DDRPHYC_DX3DQTR_DQDLY2_Pos) /*!< 0x00000800 */
#define DDRPHYC_DX3DQTR_DQDLY3_Pos (12U)
#define DDRPHYC_DX3DQTR_DQDLY3_Msk (0xFU << DDRPHYC_DX3DQTR_DQDLY3_Pos) /*!< 0x0000F000 */
#define DDRPHYC_DX3DQTR_DQDLY3     DDRPHYC_DX3DQTR_DQDLY3_Msk           /*!< DQ delay for bit 3 */
#define DDRPHYC_DX3DQTR_DQDLY3_0   (0x1U << DDRPHYC_DX3DQTR_DQDLY3_Pos) /*!< 0x00001000 */
#define DDRPHYC_DX3DQTR_DQDLY3_1   (0x2U << DDRPHYC_DX3DQTR_DQDLY3_Pos) /*!< 0x00002000 */
#define DDRPHYC_DX3DQTR_DQDLY3_2   (0x4U << DDRPHYC_DX3DQTR_DQDLY3_Pos) /*!< 0x00004000 */
#define DDRPHYC_DX3DQTR_DQDLY3_3   (0x8U << DDRPHYC_DX3DQTR_DQDLY3_Pos) /*!< 0x00008000 */
#define DDRPHYC_DX3DQTR_DQDLY4_Pos (16U)
#define DDRPHYC_DX3DQTR_DQDLY4_Msk (0xFU << DDRPHYC_DX3DQTR_DQDLY4_Pos) /*!< 0x000F0000 */
#define DDRPHYC_DX3DQTR_DQDLY4     DDRPHYC_DX3DQTR_DQDLY4_Msk           /*!< DQ delay for bit 4 */
#define DDRPHYC_DX3DQTR_DQDLY4_0   (0x1U << DDRPHYC_DX3DQTR_DQDLY4_Pos) /*!< 0x00010000 */
#define DDRPHYC_DX3DQTR_DQDLY4_1   (0x2U << DDRPHYC_DX3DQTR_DQDLY4_Pos) /*!< 0x00020000 */
#define DDRPHYC_DX3DQTR_DQDLY4_2   (0x4U << DDRPHYC_DX3DQTR_DQDLY4_Pos) /*!< 0x00040000 */
#define DDRPHYC_DX3DQTR_DQDLY4_3   (0x8U << DDRPHYC_DX3DQTR_DQDLY4_Pos) /*!< 0x00080000 */
#define DDRPHYC_DX3DQTR_DQDLY5_Pos (20U)
#define DDRPHYC_DX3DQTR_DQDLY5_Msk (0xFU << DDRPHYC_DX3DQTR_DQDLY5_Pos) /*!< 0x00F00000 */
#define DDRPHYC_DX3DQTR_DQDLY5     DDRPHYC_DX3DQTR_DQDLY5_Msk           /*!< DQ delay for bit 5 */
#define DDRPHYC_DX3DQTR_DQDLY5_0   (0x1U << DDRPHYC_DX3DQTR_DQDLY5_Pos) /*!< 0x00100000 */
#define DDRPHYC_DX3DQTR_DQDLY5_1   (0x2U << DDRPHYC_DX3DQTR_DQDLY5_Pos) /*!< 0x00200000 */
#define DDRPHYC_DX3DQTR_DQDLY5_2   (0x4U << DDRPHYC_DX3DQTR_DQDLY5_Pos) /*!< 0x00400000 */
#define DDRPHYC_DX3DQTR_DQDLY5_3   (0x8U << DDRPHYC_DX3DQTR_DQDLY5_Pos) /*!< 0x00800000 */
#define DDRPHYC_DX3DQTR_DQDLY6_Pos (24U)
#define DDRPHYC_DX3DQTR_DQDLY6_Msk (0xFU << DDRPHYC_DX3DQTR_DQDLY6_Pos) /*!< 0x0F000000 */
#define DDRPHYC_DX3DQTR_DQDLY6     DDRPHYC_DX3DQTR_DQDLY6_Msk           /*!< DQ delay for bit 6 */
#define DDRPHYC_DX3DQTR_DQDLY6_0   (0x1U << DDRPHYC_DX3DQTR_DQDLY6_Pos) /*!< 0x01000000 */
#define DDRPHYC_DX3DQTR_DQDLY6_1   (0x2U << DDRPHYC_DX3DQTR_DQDLY6_Pos) /*!< 0x02000000 */
#define DDRPHYC_DX3DQTR_DQDLY6_2   (0x4U << DDRPHYC_DX3DQTR_DQDLY6_Pos) /*!< 0x04000000 */
#define DDRPHYC_DX3DQTR_DQDLY6_3   (0x8U << DDRPHYC_DX3DQTR_DQDLY6_Pos) /*!< 0x08000000 */
#define DDRPHYC_DX3DQTR_DQDLY7_Pos (28U)
#define DDRPHYC_DX3DQTR_DQDLY7_Msk (0xFU << DDRPHYC_DX3DQTR_DQDLY7_Pos) /*!< 0xF0000000 */
#define DDRPHYC_DX3DQTR_DQDLY7     DDRPHYC_DX3DQTR_DQDLY7_Msk           /*!< DQ delay for bit 7 */
#define DDRPHYC_DX3DQTR_DQDLY7_0   (0x1U << DDRPHYC_DX3DQTR_DQDLY7_Pos) /*!< 0x10000000 */
#define DDRPHYC_DX3DQTR_DQDLY7_1   (0x2U << DDRPHYC_DX3DQTR_DQDLY7_Pos) /*!< 0x20000000 */
#define DDRPHYC_DX3DQTR_DQDLY7_2   (0x4U << DDRPHYC_DX3DQTR_DQDLY7_Pos) /*!< 0x40000000 */
#define DDRPHYC_DX3DQTR_DQDLY7_3   (0x8U << DDRPHYC_DX3DQTR_DQDLY7_Pos) /*!< 0x80000000 */

/***************  Bit definition for DDRPHYC_DX3DQSTR register  ***************/
#define DDRPHYC_DX3DQSTR_R0DGSL_Pos  (0U)
#define DDRPHYC_DX3DQSTR_R0DGSL_Msk  (0x7U << DDRPHYC_DX3DQSTR_R0DGSL_Pos)  /*!< 0x00000007 */
#define DDRPHYC_DX3DQSTR_R0DGSL      DDRPHYC_DX3DQSTR_R0DGSL_Msk            /*!< Rank 0 DQS gating system latency */
#define DDRPHYC_DX3DQSTR_R0DGSL_0    (0x1U << DDRPHYC_DX3DQSTR_R0DGSL_Pos)  /*!< 0x00000001 */
#define DDRPHYC_DX3DQSTR_R0DGSL_1    (0x2U << DDRPHYC_DX3DQSTR_R0DGSL_Pos)  /*!< 0x00000002 */
#define DDRPHYC_DX3DQSTR_R0DGSL_2    (0x4U << DDRPHYC_DX3DQSTR_R0DGSL_Pos)  /*!< 0x00000004 */
#define DDRPHYC_DX3DQSTR_R0DGPS_Pos  (12U)
#define DDRPHYC_DX3DQSTR_R0DGPS_Msk  (0x3U << DDRPHYC_DX3DQSTR_R0DGPS_Pos)  /*!< 0x00003000 */
#define DDRPHYC_DX3DQSTR_R0DGPS      DDRPHYC_DX3DQSTR_R0DGPS_Msk            /*!< Rank 0 DQS gating phase select */
#define DDRPHYC_DX3DQSTR_R0DGPS_0    (0x1U << DDRPHYC_DX3DQSTR_R0DGPS_Pos)  /*!< 0x00001000 */
#define DDRPHYC_DX3DQSTR_R0DGPS_1    (0x2U << DDRPHYC_DX3DQSTR_R0DGPS_Pos)  /*!< 0x00002000 */
#define DDRPHYC_DX3DQSTR_DQSDLY_Pos  (20U)
#define DDRPHYC_DX3DQSTR_DQSDLY_Msk  (0x7U << DDRPHYC_DX3DQSTR_DQSDLY_Pos)  /*!< 0x00700000 */
#define DDRPHYC_DX3DQSTR_DQSDLY      DDRPHYC_DX3DQSTR_DQSDLY_Msk            /*!< DQS delay */
#define DDRPHYC_DX3DQSTR_DQSDLY_0    (0x1U << DDRPHYC_DX3DQSTR_DQSDLY_Pos)  /*!< 0x00100000 */
#define DDRPHYC_DX3DQSTR_DQSDLY_1    (0x2U << DDRPHYC_DX3DQSTR_DQSDLY_Pos)  /*!< 0x00200000 */
#define DDRPHYC_DX3DQSTR_DQSDLY_2    (0x4U << DDRPHYC_DX3DQSTR_DQSDLY_Pos)  /*!< 0x00400000 */
#define DDRPHYC_DX3DQSTR_DQSNDLY_Pos (23U)
#define DDRPHYC_DX3DQSTR_DQSNDLY_Msk (0x7U << DDRPHYC_DX3DQSTR_DQSNDLY_Pos) /*!< 0x03800000 */
#define DDRPHYC_DX3DQSTR_DQSNDLY     DDRPHYC_DX3DQSTR_DQSNDLY_Msk           /*!< DQS# delay */
#define DDRPHYC_DX3DQSTR_DQSNDLY_0   (0x1U << DDRPHYC_DX3DQSTR_DQSNDLY_Pos) /*!< 0x00800000 */
#define DDRPHYC_DX3DQSTR_DQSNDLY_1   (0x2U << DDRPHYC_DX3DQSTR_DQSNDLY_Pos) /*!< 0x01000000 */
#define DDRPHYC_DX3DQSTR_DQSNDLY_2   (0x4U << DDRPHYC_DX3DQSTR_DQSNDLY_Pos) /*!< 0x02000000 */
#define DDRPHYC_DX3DQSTR_DMDLY_Pos   (26U)
#define DDRPHYC_DX3DQSTR_DMDLY_Msk   (0xFU << DDRPHYC_DX3DQSTR_DMDLY_Pos)   /*!< 0x3C000000 */
#define DDRPHYC_DX3DQSTR_DMDLY       DDRPHYC_DX3DQSTR_DMDLY_Msk             /*!< DM delay */
#define DDRPHYC_DX3DQSTR_DMDLY_0     (0x1U << DDRPHYC_DX3DQSTR_DMDLY_Pos)   /*!< 0x04000000 */
#define DDRPHYC_DX3DQSTR_DMDLY_1     (0x2U << DDRPHYC_DX3DQSTR_DMDLY_Pos)   /*!< 0x08000000 */
#define DDRPHYC_DX3DQSTR_DMDLY_2     (0x4U << DDRPHYC_DX3DQSTR_DMDLY_Pos)   /*!< 0x10000000 */
#define DDRPHYC_DX3DQSTR_DMDLY_3     (0x8U << DDRPHYC_DX3DQSTR_DMDLY_Pos)   /*!< 0x20000000 */

/******************************************************************************/
/*                                                                            */
/*                 Digital Filter for Sigma Delta Modulators                  */
/*                                                                            */
/******************************************************************************/

/****************   DFSDM channel configuration registers  ********************/

/***************  Bit definition for DFSDM_CHCFGR1 register  ******************/
#define DFSDM_CHCFGR1_DFSDMEN_Pos       (31U)
#define DFSDM_CHCFGR1_DFSDMEN_Msk       (0x1UL << DFSDM_CHCFGR1_DFSDMEN_Pos)   /*!< 0x80000000 */
#define DFSDM_CHCFGR1_DFSDMEN           DFSDM_CHCFGR1_DFSDMEN_Msk              /*!< Global enable for DFSDM interface */
#define DFSDM_CHCFGR1_CKOUTSRC_Pos      (30U)
#define DFSDM_CHCFGR1_CKOUTSRC_Msk      (0x1UL << DFSDM_CHCFGR1_CKOUTSRC_Pos)  /*!< 0x40000000 */
#define DFSDM_CHCFGR1_CKOUTSRC          DFSDM_CHCFGR1_CKOUTSRC_Msk             /*!< Output serial clock source selection */
#define DFSDM_CHCFGR1_CKOUTDIV_Pos      (16U)
#define DFSDM_CHCFGR1_CKOUTDIV_Msk      (0xFFUL << DFSDM_CHCFGR1_CKOUTDIV_Pos) /*!< 0x00FF0000 */
#define DFSDM_CHCFGR1_CKOUTDIV          DFSDM_CHCFGR1_CKOUTDIV_Msk             /*!< CKOUTDIV[7:0] output serial clock divider */
#define DFSDM_CHCFGR1_DATPACK_Pos       (14U)
#define DFSDM_CHCFGR1_DATPACK_Msk       (0x3UL << DFSDM_CHCFGR1_DATPACK_Pos)   /*!< 0x0000C000 */
#define DFSDM_CHCFGR1_DATPACK           DFSDM_CHCFGR1_DATPACK_Msk              /*!< DATPACK[1:0] Data packing mode */
#define DFSDM_CHCFGR1_DATPACK_1         (0x2UL << DFSDM_CHCFGR1_DATPACK_Pos)   /*!< 0x00008000 */
#define DFSDM_CHCFGR1_DATPACK_0         (0x1UL << DFSDM_CHCFGR1_DATPACK_Pos)   /*!< 0x00004000 */
#define DFSDM_CHCFGR1_DATMPX_Pos        (12U)
#define DFSDM_CHCFGR1_DATMPX_Msk        (0x3UL << DFSDM_CHCFGR1_DATMPX_Pos)    /*!< 0x00003000 */
#define DFSDM_CHCFGR1_DATMPX            DFSDM_CHCFGR1_DATMPX_Msk               /*!< DATMPX[1:0] Input data multiplexer for channel y */
#define DFSDM_CHCFGR1_DATMPX_1          (0x2UL << DFSDM_CHCFGR1_DATMPX_Pos)    /*!< 0x00002000 */
#define DFSDM_CHCFGR1_DATMPX_0          (0x1UL << DFSDM_CHCFGR1_DATMPX_Pos)    /*!< 0x00001000 */
#define DFSDM_CHCFGR1_CHINSEL_Pos       (8U)
#define DFSDM_CHCFGR1_CHINSEL_Msk       (0x1UL << DFSDM_CHCFGR1_CHINSEL_Pos)   /*!< 0x00000100 */
#define DFSDM_CHCFGR1_CHINSEL           DFSDM_CHCFGR1_CHINSEL_Msk              /*!< Serial inputs selection for channel y */
#define DFSDM_CHCFGR1_CHEN_Pos          (7U)
#define DFSDM_CHCFGR1_CHEN_Msk          (0x1UL << DFSDM_CHCFGR1_CHEN_Pos)      /*!< 0x00000080 */
#define DFSDM_CHCFGR1_CHEN              DFSDM_CHCFGR1_CHEN_Msk                 /*!< Channel y enable */
#define DFSDM_CHCFGR1_CKABEN_Pos        (6U)
#define DFSDM_CHCFGR1_CKABEN_Msk        (0x1UL << DFSDM_CHCFGR1_CKABEN_Pos)    /*!< 0x00000040 */
#define DFSDM_CHCFGR1_CKABEN            DFSDM_CHCFGR1_CKABEN_Msk               /*!< Clock absence detector enable on channel y */
#define DFSDM_CHCFGR1_SCDEN_Pos         (5U)
#define DFSDM_CHCFGR1_SCDEN_Msk         (0x1UL << DFSDM_CHCFGR1_SCDEN_Pos)     /*!< 0x00000020 */
#define DFSDM_CHCFGR1_SCDEN             DFSDM_CHCFGR1_SCDEN_Msk                /*!< Short circuit detector enable on channel y */
#define DFSDM_CHCFGR1_SPICKSEL_Pos      (2U)
#define DFSDM_CHCFGR1_SPICKSEL_Msk      (0x3UL << DFSDM_CHCFGR1_SPICKSEL_Pos)  /*!< 0x0000000C */
#define DFSDM_CHCFGR1_SPICKSEL          DFSDM_CHCFGR1_SPICKSEL_Msk             /*!< SPICKSEL[1:0] SPI clock select for channel y */
#define DFSDM_CHCFGR1_SPICKSEL_1        (0x2UL << DFSDM_CHCFGR1_SPICKSEL_Pos)  /*!< 0x00000008 */
#define DFSDM_CHCFGR1_SPICKSEL_0        (0x1UL << DFSDM_CHCFGR1_SPICKSEL_Pos)  /*!< 0x00000004 */
#define DFSDM_CHCFGR1_SITP_Pos          (0U)
#define DFSDM_CHCFGR1_SITP_Msk          (0x3UL << DFSDM_CHCFGR1_SITP_Pos)      /*!< 0x00000003 */
#define DFSDM_CHCFGR1_SITP              DFSDM_CHCFGR1_SITP_Msk                 /*!< SITP[1:0] Serial interface type for channel y */
#define DFSDM_CHCFGR1_SITP_1            (0x2UL << DFSDM_CHCFGR1_SITP_Pos)      /*!< 0x00000002 */
#define DFSDM_CHCFGR1_SITP_0            (0x1UL << DFSDM_CHCFGR1_SITP_Pos)      /*!< 0x00000001 */

/***************  Bit definition for DFSDM_CHCFGR2 register  ******************/
#define DFSDM_CHCFGR2_OFFSET_Pos        (8U)
#define DFSDM_CHCFGR2_OFFSET_Msk        (0xFFFFFFUL << DFSDM_CHCFGR2_OFFSET_Pos)/*!< 0xFFFFFF00 */
#define DFSDM_CHCFGR2_OFFSET            DFSDM_CHCFGR2_OFFSET_Msk               /*!< OFFSET[23:0] 24-bit calibration offset for channel y */
#define DFSDM_CHCFGR2_DTRBS_Pos         (3U)
#define DFSDM_CHCFGR2_DTRBS_Msk         (0x1FUL << DFSDM_CHCFGR2_DTRBS_Pos)    /*!< 0x000000F8 */
#define DFSDM_CHCFGR2_DTRBS             DFSDM_CHCFGR2_DTRBS_Msk                /*!< DTRBS[4:0] Data right bit-shift for channel y */

/****************  Bit definition for DFSDM_CHAWSCDR register *****************/
#define DFSDM_CHAWSCDR_AWFORD_Pos       (22U)
#define DFSDM_CHAWSCDR_AWFORD_Msk       (0x3UL << DFSDM_CHAWSCDR_AWFORD_Pos)   /*!< 0x00C00000 */
#define DFSDM_CHAWSCDR_AWFORD           DFSDM_CHAWSCDR_AWFORD_Msk              /*!< AWFORD[1:0] Analog watchdog Sinc filter order on channel y */
#define DFSDM_CHAWSCDR_AWFORD_1         (0x2UL << DFSDM_CHAWSCDR_AWFORD_Pos)   /*!< 0x00800000 */
#define DFSDM_CHAWSCDR_AWFORD_0         (0x1UL << DFSDM_CHAWSCDR_AWFORD_Pos)   /*!< 0x00400000 */
#define DFSDM_CHAWSCDR_AWFOSR_Pos       (16U)
#define DFSDM_CHAWSCDR_AWFOSR_Msk       (0x1FUL << DFSDM_CHAWSCDR_AWFOSR_Pos)  /*!< 0x001F0000 */
#define DFSDM_CHAWSCDR_AWFOSR           DFSDM_CHAWSCDR_AWFOSR_Msk              /*!< AWFOSR[4:0] Analog watchdog filter oversampling ratio on channel y */
#define DFSDM_CHAWSCDR_BKSCD_Pos        (12U)
#define DFSDM_CHAWSCDR_BKSCD_Msk        (0xFUL << DFSDM_CHAWSCDR_BKSCD_Pos)    /*!< 0x0000F000 */
#define DFSDM_CHAWSCDR_BKSCD            DFSDM_CHAWSCDR_BKSCD_Msk               /*!< BKSCD[3:0] Break signal assignment for short circuit detector on channel y */
#define DFSDM_CHAWSCDR_SCDT_Pos         (0U)
#define DFSDM_CHAWSCDR_SCDT_Msk         (0xFFUL << DFSDM_CHAWSCDR_SCDT_Pos)    /*!< 0x000000FF */
#define DFSDM_CHAWSCDR_SCDT             DFSDM_CHAWSCDR_SCDT_Msk                /*!< SCDT[7:0] Short circuit detector threshold for channel y */

/****************  Bit definition for DFSDM_CHWDATR register *******************/
#define DFSDM_CHWDATR_WDATA_Pos         (0U)
#define DFSDM_CHWDATR_WDATA_Msk         (0xFFFFUL << DFSDM_CHWDATR_WDATA_Pos)  /*!< 0x0000FFFF */
#define DFSDM_CHWDATR_WDATA             DFSDM_CHWDATR_WDATA_Msk                /*!< WDATA[15:0] Input channel y watchdog data */

/****************  Bit definition for DFSDM_CHDATINR register *****************/
#define DFSDM_CHDATINR_INDAT0_Pos       (0U)
#define DFSDM_CHDATINR_INDAT0_Msk       (0xFFFFUL << DFSDM_CHDATINR_INDAT0_Pos)/*!< 0x0000FFFF */
#define DFSDM_CHDATINR_INDAT0           DFSDM_CHDATINR_INDAT0_Msk              /*!< INDAT0[31:16] Input data for channel y or channel (y+1) */
#define DFSDM_CHDATINR_INDAT1_Pos       (16U)
#define DFSDM_CHDATINR_INDAT1_Msk       (0xFFFFUL << DFSDM_CHDATINR_INDAT1_Pos)/*!< 0xFFFF0000 */
#define DFSDM_CHDATINR_INDAT1           DFSDM_CHDATINR_INDAT1_Msk              /*!< INDAT0[15:0] Input data for channel y */

/****************  Bit definition for DFSDM_CHDLYR register *******************/
#define DFSDM_CHDLYR_PLSSKP_Pos         (0U)
#define DFSDM_CHDLYR_PLSSKP_Msk         (0x3FUL << DFSDM_CHDLYR_PLSSKP_Pos)    /*!< 0x0000003F */
#define DFSDM_CHDLYR_PLSSKP             DFSDM_CHDLYR_PLSSKP_Msk                /*!< PLSSKP[5:0] Number of input serial samples that will be skipped */

/************************   DFSDM module registers  ****************************/

/*****************  Bit definition for DFSDM_FLTCR1 register *******************/
#define DFSDM_FLTCR1_AWFSEL_Pos         (30U)
#define DFSDM_FLTCR1_AWFSEL_Msk         (0x1UL << DFSDM_FLTCR1_AWFSEL_Pos)     /*!< 0x40000000 */
#define DFSDM_FLTCR1_AWFSEL             DFSDM_FLTCR1_AWFSEL_Msk                /*!< Analog watchdog fast mode select */
#define DFSDM_FLTCR1_FAST_Pos           (29U)
#define DFSDM_FLTCR1_FAST_Msk           (0x1UL << DFSDM_FLTCR1_FAST_Pos)       /*!< 0x20000000 */
#define DFSDM_FLTCR1_FAST               DFSDM_FLTCR1_FAST_Msk                  /*!< Fast conversion mode selection */
#define DFSDM_FLTCR1_RCH_Pos            (24U)
#define DFSDM_FLTCR1_RCH_Msk            (0x7UL << DFSDM_FLTCR1_RCH_Pos)        /*!< 0x07000000 */
#define DFSDM_FLTCR1_RCH                DFSDM_FLTCR1_RCH_Msk                   /*!< RCH[2:0] Regular channel selection */
#define DFSDM_FLTCR1_RDMAEN_Pos         (21U)
#define DFSDM_FLTCR1_RDMAEN_Msk         (0x1UL << DFSDM_FLTCR1_RDMAEN_Pos)     /*!< 0x00200000 */
#define DFSDM_FLTCR1_RDMAEN             DFSDM_FLTCR1_RDMAEN_Msk                /*!< DMA channel enabled to read data for the regular conversion */
#define DFSDM_FLTCR1_RSYNC_Pos          (19U)
#define DFSDM_FLTCR1_RSYNC_Msk          (0x1UL << DFSDM_FLTCR1_RSYNC_Pos)      /*!< 0x00080000 */
#define DFSDM_FLTCR1_RSYNC              DFSDM_FLTCR1_RSYNC_Msk                 /*!< Launch regular conversion synchronously with DFSDMx */
#define DFSDM_FLTCR1_RCONT_Pos          (18U)
#define DFSDM_FLTCR1_RCONT_Msk          (0x1UL << DFSDM_FLTCR1_RCONT_Pos)      /*!< 0x00040000 */
#define DFSDM_FLTCR1_RCONT              DFSDM_FLTCR1_RCONT_Msk                 /*!< Continuous mode selection for regular conversions */
#define DFSDM_FLTCR1_RSWSTART_Pos       (17U)
#define DFSDM_FLTCR1_RSWSTART_Msk       (0x1UL << DFSDM_FLTCR1_RSWSTART_Pos)   /*!< 0x00020000 */
#define DFSDM_FLTCR1_RSWSTART           DFSDM_FLTCR1_RSWSTART_Msk              /*!< Software start of a conversion on the regular channel */
#define DFSDM_FLTCR1_JEXTEN_Pos         (13U)
#define DFSDM_FLTCR1_JEXTEN_Msk         (0x3UL << DFSDM_FLTCR1_JEXTEN_Pos)     /*!< 0x00006000 */
#define DFSDM_FLTCR1_JEXTEN             DFSDM_FLTCR1_JEXTEN_Msk                /*!< JEXTEN[1:0] Trigger enable and trigger edge selection for injected conversions */
#define DFSDM_FLTCR1_JEXTEN_1           (0x2UL << DFSDM_FLTCR1_JEXTEN_Pos)     /*!< 0x00004000 */
#define DFSDM_FLTCR1_JEXTEN_0           (0x1UL << DFSDM_FLTCR1_JEXTEN_Pos)     /*!< 0x00002000 */
#define DFSDM_FLTCR1_JEXTSEL_Pos        (8U)
#define DFSDM_FLTCR1_JEXTSEL_Msk        (0x1FUL << DFSDM_FLTCR1_JEXTSEL_Pos)   /*!< 0x00001F00 */
#define DFSDM_FLTCR1_JEXTSEL            DFSDM_FLTCR1_JEXTSEL_Msk               /*!< JEXTSEL[4:0]Trigger signal selection for launching injected conversions */
#define DFSDM_FLTCR1_JEXTSEL_4          (0x10UL << DFSDM_FLTCR1_JEXTSEL_Pos)   /*!< 0x00001000 */
#define DFSDM_FLTCR1_JEXTSEL_3          (0x08UL << DFSDM_FLTCR1_JEXTSEL_Pos)   /*!< 0x00000800 */
#define DFSDM_FLTCR1_JEXTSEL_2          (0x04UL << DFSDM_FLTCR1_JEXTSEL_Pos)   /*!< 0x00000400 */
#define DFSDM_FLTCR1_JEXTSEL_1          (0x02UL << DFSDM_FLTCR1_JEXTSEL_Pos)   /*!< 0x00000200 */
#define DFSDM_FLTCR1_JEXTSEL_0          (0x01UL << DFSDM_FLTCR1_JEXTSEL_Pos)   /*!< 0x00000100 */
#define DFSDM_FLTCR1_JDMAEN_Pos         (5U)
#define DFSDM_FLTCR1_JDMAEN_Msk         (0x1UL << DFSDM_FLTCR1_JDMAEN_Pos)     /*!< 0x00000020 */
#define DFSDM_FLTCR1_JDMAEN             DFSDM_FLTCR1_JDMAEN_Msk                /*!< DMA channel enabled to read data for the injected channel group */
#define DFSDM_FLTCR1_JSCAN_Pos          (4U)
#define DFSDM_FLTCR1_JSCAN_Msk          (0x1UL << DFSDM_FLTCR1_JSCAN_Pos)      /*!< 0x00000010 */
#define DFSDM_FLTCR1_JSCAN              DFSDM_FLTCR1_JSCAN_Msk                 /*!< Scanning conversion in continuous mode selection for injected conversions */
#define DFSDM_FLTCR1_JSYNC_Pos          (3U)
#define DFSDM_FLTCR1_JSYNC_Msk          (0x1UL << DFSDM_FLTCR1_JSYNC_Pos)      /*!< 0x00000008 */
#define DFSDM_FLTCR1_JSYNC              DFSDM_FLTCR1_JSYNC_Msk                 /*!< Launch an injected conversion synchronously with DFSDMx JSWSTART trigger  */
#define DFSDM_FLTCR1_JSWSTART_Pos       (1U)
#define DFSDM_FLTCR1_JSWSTART_Msk       (0x1UL << DFSDM_FLTCR1_JSWSTART_Pos)   /*!< 0x00000002 */
#define DFSDM_FLTCR1_JSWSTART           DFSDM_FLTCR1_JSWSTART_Msk              /*!< Start the conversion of the injected group of channels */
#define DFSDM_FLTCR1_DFEN_Pos           (0U)
#define DFSDM_FLTCR1_DFEN_Msk           (0x1UL << DFSDM_FLTCR1_DFEN_Pos)       /*!< 0x00000001 */
#define DFSDM_FLTCR1_DFEN               DFSDM_FLTCR1_DFEN_Msk                  /*!< DFSDM enable */

/*****************  Bit definition for DFSDM_FLTCR2 register *******************/
#define DFSDM_FLTCR2_AWDCH_Pos          (16U)
#define DFSDM_FLTCR2_AWDCH_Msk          (0xFFUL << DFSDM_FLTCR2_AWDCH_Pos)     /*!< 0x00FF0000 */
#define DFSDM_FLTCR2_AWDCH              DFSDM_FLTCR2_AWDCH_Msk                 /*!< AWDCH[7:0] Analog watchdog channel selection */
#define DFSDM_FLTCR2_EXCH_Pos           (8U)
#define DFSDM_FLTCR2_EXCH_Msk           (0xFFUL << DFSDM_FLTCR2_EXCH_Pos)      /*!< 0x0000FF00 */
#define DFSDM_FLTCR2_EXCH               DFSDM_FLTCR2_EXCH_Msk                  /*!< EXCH[7:0] Extreme detector channel selection */
#define DFSDM_FLTCR2_CKABIE_Pos         (6U)
#define DFSDM_FLTCR2_CKABIE_Msk         (0x1UL << DFSDM_FLTCR2_CKABIE_Pos)     /*!< 0x00000040 */
#define DFSDM_FLTCR2_CKABIE             DFSDM_FLTCR2_CKABIE_Msk                /*!< Clock absence interrupt enable */
#define DFSDM_FLTCR2_SCDIE_Pos          (5U)
#define DFSDM_FLTCR2_SCDIE_Msk          (0x1UL << DFSDM_FLTCR2_SCDIE_Pos)      /*!< 0x00000020 */
#define DFSDM_FLTCR2_SCDIE              DFSDM_FLTCR2_SCDIE_Msk                 /*!< Short circuit detector interrupt enable */
#define DFSDM_FLTCR2_AWDIE_Pos          (4U)
#define DFSDM_FLTCR2_AWDIE_Msk          (0x1UL << DFSDM_FLTCR2_AWDIE_Pos)      /*!< 0x00000010 */
#define DFSDM_FLTCR2_AWDIE              DFSDM_FLTCR2_AWDIE_Msk                 /*!< Analog watchdog interrupt enable */
#define DFSDM_FLTCR2_ROVRIE_Pos         (3U)
#define DFSDM_FLTCR2_ROVRIE_Msk         (0x1UL << DFSDM_FLTCR2_ROVRIE_Pos)     /*!< 0x00000008 */
#define DFSDM_FLTCR2_ROVRIE             DFSDM_FLTCR2_ROVRIE_Msk                /*!< Regular data overrun interrupt enable */
#define DFSDM_FLTCR2_JOVRIE_Pos         (2U)
#define DFSDM_FLTCR2_JOVRIE_Msk         (0x1UL << DFSDM_FLTCR2_JOVRIE_Pos)     /*!< 0x00000004 */
#define DFSDM_FLTCR2_JOVRIE             DFSDM_FLTCR2_JOVRIE_Msk                /*!< Injected data overrun interrupt enable */
#define DFSDM_FLTCR2_REOCIE_Pos         (1U)
#define DFSDM_FLTCR2_REOCIE_Msk         (0x1UL << DFSDM_FLTCR2_REOCIE_Pos)     /*!< 0x00000002 */
#define DFSDM_FLTCR2_REOCIE             DFSDM_FLTCR2_REOCIE_Msk                /*!< Regular end of conversion interrupt enable */
#define DFSDM_FLTCR2_JEOCIE_Pos         (0U)
#define DFSDM_FLTCR2_JEOCIE_Msk         (0x1UL << DFSDM_FLTCR2_JEOCIE_Pos)     /*!< 0x00000001 */
#define DFSDM_FLTCR2_JEOCIE             DFSDM_FLTCR2_JEOCIE_Msk                /*!< Injected end of conversion interrupt enable */

/*****************  Bit definition for DFSDM_FLTISR register *******************/
#define DFSDM_FLTISR_SCDF_Pos           (24U)
#define DFSDM_FLTISR_SCDF_Msk           (0xFFUL << DFSDM_FLTISR_SCDF_Pos)      /*!< 0xFF000000 */
#define DFSDM_FLTISR_SCDF               DFSDM_FLTISR_SCDF_Msk                  /*!< SCDF[7:0] Short circuit detector flag */
#define DFSDM_FLTISR_CKABF_Pos          (16U)
#define DFSDM_FLTISR_CKABF_Msk          (0xFFUL << DFSDM_FLTISR_CKABF_Pos)     /*!< 0x00FF0000 */
#define DFSDM_FLTISR_CKABF              DFSDM_FLTISR_CKABF_Msk                 /*!< CKABF[7:0] Clock absence flag */
#define DFSDM_FLTISR_RCIP_Pos           (14U)
#define DFSDM_FLTISR_RCIP_Msk           (0x1UL << DFSDM_FLTISR_RCIP_Pos)       /*!< 0x00004000 */
#define DFSDM_FLTISR_RCIP               DFSDM_FLTISR_RCIP_Msk                  /*!< Regular conversion in progress status */
#define DFSDM_FLTISR_JCIP_Pos           (13U)
#define DFSDM_FLTISR_JCIP_Msk           (0x1UL << DFSDM_FLTISR_JCIP_Pos)       /*!< 0x00002000 */
#define DFSDM_FLTISR_JCIP               DFSDM_FLTISR_JCIP_Msk                  /*!< Injected conversion in progress status */
#define DFSDM_FLTISR_AWDF_Pos           (4U)
#define DFSDM_FLTISR_AWDF_Msk           (0x1UL << DFSDM_FLTISR_AWDF_Pos)       /*!< 0x00000010 */
#define DFSDM_FLTISR_AWDF               DFSDM_FLTISR_AWDF_Msk                  /*!< Analog watchdog */
#define DFSDM_FLTISR_ROVRF_Pos          (3U)
#define DFSDM_FLTISR_ROVRF_Msk          (0x1UL << DFSDM_FLTISR_ROVRF_Pos)      /*!< 0x00000008 */
#define DFSDM_FLTISR_ROVRF              DFSDM_FLTISR_ROVRF_Msk                 /*!< Regular conversion overrun flag */
#define DFSDM_FLTISR_JOVRF_Pos          (2U)
#define DFSDM_FLTISR_JOVRF_Msk          (0x1UL << DFSDM_FLTISR_JOVRF_Pos)      /*!< 0x00000004 */
#define DFSDM_FLTISR_JOVRF              DFSDM_FLTISR_JOVRF_Msk                 /*!< Injected conversion overrun flag */
#define DFSDM_FLTISR_REOCF_Pos          (1U)
#define DFSDM_FLTISR_REOCF_Msk          (0x1UL << DFSDM_FLTISR_REOCF_Pos)      /*!< 0x00000002 */
#define DFSDM_FLTISR_REOCF              DFSDM_FLTISR_REOCF_Msk                 /*!< End of regular conversion flag */
#define DFSDM_FLTISR_JEOCF_Pos          (0U)
#define DFSDM_FLTISR_JEOCF_Msk          (0x1UL << DFSDM_FLTISR_JEOCF_Pos)      /*!< 0x00000001 */
#define DFSDM_FLTISR_JEOCF              DFSDM_FLTISR_JEOCF_Msk                 /*!< End of injected conversion flag */

/*****************  Bit definition for DFSDM_FLTICR register *******************/
#define DFSDM_FLTICR_CLRSCDF_Pos        (24U)
#define DFSDM_FLTICR_CLRSCDF_Msk        (0xFFUL << DFSDM_FLTICR_CLRSCDF_Pos)   /*!< 0xFF000000 */
#define DFSDM_FLTICR_CLRSCDF            DFSDM_FLTICR_CLRSCDF_Msk               /*!< CLRSCDF[7:0] Clear the short circuit detector flag */
#define DFSDM_FLTICR_CLRCKABF_Pos       (16U)
#define DFSDM_FLTICR_CLRCKABF_Msk       (0xFFUL << DFSDM_FLTICR_CLRCKABF_Pos)  /*!< 0x00FF0000 */
#define DFSDM_FLTICR_CLRCKABF           DFSDM_FLTICR_CLRCKABF_Msk              /*!< CLRCKABF[7:0] Clear the clock absence flag */
#define DFSDM_FLTICR_CLRROVRF_Pos       (3U)
#define DFSDM_FLTICR_CLRROVRF_Msk       (0x1UL << DFSDM_FLTICR_CLRROVRF_Pos)   /*!< 0x00000008 */
#define DFSDM_FLTICR_CLRROVRF           DFSDM_FLTICR_CLRROVRF_Msk              /*!< Clear the regular conversion overrun flag */
#define DFSDM_FLTICR_CLRJOVRF_Pos       (2U)
#define DFSDM_FLTICR_CLRJOVRF_Msk       (0x1UL << DFSDM_FLTICR_CLRJOVRF_Pos)   /*!< 0x00000004 */
#define DFSDM_FLTICR_CLRJOVRF           DFSDM_FLTICR_CLRJOVRF_Msk              /*!< Clear the injected conversion overrun flag */

/****************  Bit definition for DFSDM_FLTJCHGR register ******************/
#define DFSDM_FLTJCHGR_JCHG_Pos         (0U)
#define DFSDM_FLTJCHGR_JCHG_Msk         (0xFFUL << DFSDM_FLTJCHGR_JCHG_Pos)    /*!< 0x000000FF */
#define DFSDM_FLTJCHGR_JCHG             DFSDM_FLTJCHGR_JCHG_Msk                /*!< JCHG[7:0] Injected channel group selection */

/*****************  Bit definition for DFSDM_FLTFCR register *******************/
#define DFSDM_FLTFCR_FORD_Pos           (29U)
#define DFSDM_FLTFCR_FORD_Msk           (0x7UL << DFSDM_FLTFCR_FORD_Pos)       /*!< 0xE0000000 */
#define DFSDM_FLTFCR_FORD               DFSDM_FLTFCR_FORD_Msk                  /*!< FORD[2:0] Sinc filter order */
#define DFSDM_FLTFCR_FORD_2             (0x4UL << DFSDM_FLTFCR_FORD_Pos)       /*!< 0x80000000 */
#define DFSDM_FLTFCR_FORD_1             (0x2UL << DFSDM_FLTFCR_FORD_Pos)       /*!< 0x40000000 */
#define DFSDM_FLTFCR_FORD_0             (0x1UL << DFSDM_FLTFCR_FORD_Pos)       /*!< 0x20000000 */
#define DFSDM_FLTFCR_FOSR_Pos           (16U)
#define DFSDM_FLTFCR_FOSR_Msk           (0x3FFUL << DFSDM_FLTFCR_FOSR_Pos)     /*!< 0x03FF0000 */
#define DFSDM_FLTFCR_FOSR               DFSDM_FLTFCR_FOSR_Msk                  /*!< FOSR[9:0] Sinc filter oversampling ratio (decimation rate) */
#define DFSDM_FLTFCR_IOSR_Pos           (0U)
#define DFSDM_FLTFCR_IOSR_Msk           (0xFFUL << DFSDM_FLTFCR_IOSR_Pos)      /*!< 0x000000FF */
#define DFSDM_FLTFCR_IOSR               DFSDM_FLTFCR_IOSR_Msk                  /*!< IOSR[7:0] Integrator oversampling ratio (averaging length) */

/***************  Bit definition for DFSDM_FLTJDATAR register *****************/
#define DFSDM_FLTJDATAR_JDATA_Pos       (8U)
#define DFSDM_FLTJDATAR_JDATA_Msk       (0xFFFFFFUL << DFSDM_FLTJDATAR_JDATA_Pos)/*!< 0xFFFFFF00 */
#define DFSDM_FLTJDATAR_JDATA           DFSDM_FLTJDATAR_JDATA_Msk              /*!< JDATA[23:0] Injected group conversion data */
#define DFSDM_FLTJDATAR_JDATACH_Pos     (0U)
#define DFSDM_FLTJDATAR_JDATACH_Msk     (0x7UL << DFSDM_FLTJDATAR_JDATACH_Pos) /*!< 0x00000007 */
#define DFSDM_FLTJDATAR_JDATACH         DFSDM_FLTJDATAR_JDATACH_Msk            /*!< JDATACH[2:0] Injected channel most recently converted */

/***************  Bit definition for DFSDM_FLTRDATAR register *****************/
#define DFSDM_FLTRDATAR_RDATA_Pos       (8U)
#define DFSDM_FLTRDATAR_RDATA_Msk       (0xFFFFFFUL << DFSDM_FLTRDATAR_RDATA_Pos)/*!< 0xFFFFFF00 */
#define DFSDM_FLTRDATAR_RDATA           DFSDM_FLTRDATAR_RDATA_Msk              /*!< RDATA[23:0] Regular channel conversion data */
#define DFSDM_FLTRDATAR_RPEND_Pos       (4U)
#define DFSDM_FLTRDATAR_RPEND_Msk       (0x1UL << DFSDM_FLTRDATAR_RPEND_Pos)   /*!< 0x00000010 */
#define DFSDM_FLTRDATAR_RPEND           DFSDM_FLTRDATAR_RPEND_Msk              /*!< RPEND Regular channel pending data */
#define DFSDM_FLTRDATAR_RDATACH_Pos     (0U)
#define DFSDM_FLTRDATAR_RDATACH_Msk     (0x7UL << DFSDM_FLTRDATAR_RDATACH_Pos) /*!< 0x00000007 */
#define DFSDM_FLTRDATAR_RDATACH         DFSDM_FLTRDATAR_RDATACH_Msk            /*!< RDATACH[2:0] Regular channel most recently converted */

/***************  Bit definition for DFSDM_FLTAWHTR register ******************/
#define DFSDM_FLTAWHTR_AWHT_Pos         (8U)
#define DFSDM_FLTAWHTR_AWHT_Msk         (0xFFFFFFUL << DFSDM_FLTAWHTR_AWHT_Pos)/*!< 0xFFFFFF00 */
#define DFSDM_FLTAWHTR_AWHT             DFSDM_FLTAWHTR_AWHT_Msk                /*!< AWHT[23:0] Analog watchdog high threshold */
#define DFSDM_FLTAWHTR_BKAWH_Pos        (0U)
#define DFSDM_FLTAWHTR_BKAWH_Msk        (0xFUL << DFSDM_FLTAWHTR_BKAWH_Pos)    /*!< 0x0000000F */
#define DFSDM_FLTAWHTR_BKAWH            DFSDM_FLTAWHTR_BKAWH_Msk               /*!< BKAWH[3:0] Break signal assignment to analog watchdog high threshold event */

/***************  Bit definition for DFSDM_FLTAWLTR register ******************/
#define DFSDM_FLTAWLTR_AWLT_Pos         (8U)
#define DFSDM_FLTAWLTR_AWLT_Msk         (0xFFFFFFUL << DFSDM_FLTAWLTR_AWLT_Pos)/*!< 0xFFFFFF00 */
#define DFSDM_FLTAWLTR_AWLT             DFSDM_FLTAWLTR_AWLT_Msk                /*!< AWLT[23:0] Analog watchdog low threshold */
#define DFSDM_FLTAWLTR_BKAWL_Pos        (0U)
#define DFSDM_FLTAWLTR_BKAWL_Msk        (0xFUL << DFSDM_FLTAWLTR_BKAWL_Pos)    /*!< 0x0000000F */
#define DFSDM_FLTAWLTR_BKAWL            DFSDM_FLTAWLTR_BKAWL_Msk               /*!< BKAWL[3:0] Break signal assignment to analog watchdog low threshold event */

/***************  Bit definition for DFSDM_FLTAWSR register *******************/
#define DFSDM_FLTAWSR_AWHTF_Pos         (8U)
#define DFSDM_FLTAWSR_AWHTF_Msk         (0xFFUL << DFSDM_FLTAWSR_AWHTF_Pos)    /*!< 0x0000FF00 */
#define DFSDM_FLTAWSR_AWHTF             DFSDM_FLTAWSR_AWHTF_Msk                /*!< AWHTF[15:8] Analog watchdog high threshold error on given channels */
#define DFSDM_FLTAWSR_AWLTF_Pos         (0U)
#define DFSDM_FLTAWSR_AWLTF_Msk         (0xFFUL << DFSDM_FLTAWSR_AWLTF_Pos)    /*!< 0x000000FF */
#define DFSDM_FLTAWSR_AWLTF             DFSDM_FLTAWSR_AWLTF_Msk                /*!< AWLTF[7:0] Analog watchdog low threshold error on given channels */

/***************  Bit definition for DFSDM_FLTAWCFR register ******************/
#define DFSDM_FLTAWCFR_CLRAWHTF_Pos     (8U)
#define DFSDM_FLTAWCFR_CLRAWHTF_Msk     (0xFFUL << DFSDM_FLTAWCFR_CLRAWHTF_Pos)/*!< 0x0000FF00 */
#define DFSDM_FLTAWCFR_CLRAWHTF         DFSDM_FLTAWCFR_CLRAWHTF_Msk            /*!< CLRAWHTF[15:8] Clear the Analog watchdog high threshold flag */
#define DFSDM_FLTAWCFR_CLRAWLTF_Pos     (0U)
#define DFSDM_FLTAWCFR_CLRAWLTF_Msk     (0xFFUL << DFSDM_FLTAWCFR_CLRAWLTF_Pos)/*!< 0x000000FF */
#define DFSDM_FLTAWCFR_CLRAWLTF         DFSDM_FLTAWCFR_CLRAWLTF_Msk            /*!< CLRAWLTF[7:0] Clear the Analog watchdog low threshold flag */

/***************  Bit definition for DFSDM_FLTEXMAX register ******************/
#define DFSDM_FLTEXMAX_EXMAX_Pos        (8U)
#define DFSDM_FLTEXMAX_EXMAX_Msk        (0xFFFFFFUL << DFSDM_FLTEXMAX_EXMAX_Pos)/*!< 0xFFFFFF00 */
#define DFSDM_FLTEXMAX_EXMAX            DFSDM_FLTEXMAX_EXMAX_Msk               /*!< EXMAX[23:0] Extreme detector maximum value */
#define DFSDM_FLTEXMAX_EXMAXCH_Pos      (0U)
#define DFSDM_FLTEXMAX_EXMAXCH_Msk      (0x7UL << DFSDM_FLTEXMAX_EXMAXCH_Pos)  /*!< 0x00000007 */
#define DFSDM_FLTEXMAX_EXMAXCH          DFSDM_FLTEXMAX_EXMAXCH_Msk             /*!< EXMAXCH[2:0] Extreme detector maximum data channel */

/***************  Bit definition for DFSDM_FLTEXMIN register ******************/
#define DFSDM_FLTEXMIN_EXMIN_Pos        (8U)
#define DFSDM_FLTEXMIN_EXMIN_Msk        (0xFFFFFFUL << DFSDM_FLTEXMIN_EXMIN_Pos)/*!< 0xFFFFFF00 */
#define DFSDM_FLTEXMIN_EXMIN            DFSDM_FLTEXMIN_EXMIN_Msk               /*!< EXMIN[23:0] Extreme detector minimum value */
#define DFSDM_FLTEXMIN_EXMINCH_Pos      (0U)
#define DFSDM_FLTEXMIN_EXMINCH_Msk      (0x7UL << DFSDM_FLTEXMIN_EXMINCH_Pos)  /*!< 0x00000007 */
#define DFSDM_FLTEXMIN_EXMINCH          DFSDM_FLTEXMIN_EXMINCH_Msk             /*!< EXMINCH[2:0] Extreme detector minimum data channel */

/***************  Bit definition for DFSDM_FLTCNVTIMR register ****************/
#define DFSDM_FLTCNVTIMR_CNVCNT_Pos     (4U)
#define DFSDM_FLTCNVTIMR_CNVCNT_Msk     (0xFFFFFFFUL << DFSDM_FLTCNVTIMR_CNVCNT_Pos)/*!< 0xFFFFFFF0 */
#define DFSDM_FLTCNVTIMR_CNVCNT         DFSDM_FLTCNVTIMR_CNVCNT_Msk            /*!< CNVCNT[27:0]: 28-bit timer counting conversion time */

/**********************  Bit definition for DFSDM_HWCFGR register  ***************/
#define DFSDM_HWCFGR_NBT_Pos  (0U)
#define DFSDM_HWCFGR_NBT_Msk  (0xFFU << DFSDM_HWCFGR_NBT_Pos)          /*!< 0x000000FF */
#define DFSDM_HWCFGR_NBT      DFSDM_HWCFGR_NBT_Msk                     /*!< Number of implemented transceivers */
#define DFSDM_HWCFGR_NBF_Pos  (8U)
#define DFSDM_HWCFGR_NBF_Msk  (0xFFU << DFSDM_HWCFGR_NBF_Pos)          /*!< 0x0000FF00 */
#define DFSDM_HWCFGR_NBF      DFSDM_HWCFGR_NBF_Msk                     /*!< NNumber of implemented filters */

/**********************  Bit definition for DFSDM_VERR register  *****************/
#define DFSDM_VERR_MINREV_Pos      (0U)
#define DFSDM_VERR_MINREV_Msk      (0xFU << DFSDM_VERR_MINREV_Pos)               /*!< 0x0000000F */
#define DFSDM_VERR_MINREV          DFSDM_VERR_MINREV_Msk                         /*!< Minor Revision number */
#define DFSDM_VERR_MAJREV_Pos      (4U)
#define DFSDM_VERR_MAJREV_Msk      (0xFU << DFSDM_VERR_MAJREV_Pos)               /*!< 0x000000F0 */
#define DFSDM_VERR_MAJREV          DFSDM_VERR_MAJREV_Msk                         /*!< Major Revision number */

/**********************  Bit definition for DFSDM_IPIDR register  ****************/
#define DFSDM_IPIDR_IPID_Pos       (0U)
#define DFSDM_IPIDR_IPID_Msk       (0xFFFFFFFFU << DFSDM_IPIDR_IPID_Pos)         /*!< 0xFFFFFFFF */
#define DFSDM_IPIDR_IPID           DFSDM_IPIDR_IPID_Msk                          /*!< IP Identification */

/**********************  Bit definition for DFSDM_SIDR register  *****************/
#define DFSDM_SIDR_SID_Pos         (0U)
#define DFSDM_SIDR_SID_Msk         (0xFFFFFFFFU << DFSDM_SIDR_SID_Pos)           /*!< 0xFFFFFFFF */
#define DFSDM_SIDR_SID             DFSDM_SIDR_SID_Msk                            /*!< IP size identification */
