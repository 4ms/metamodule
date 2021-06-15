/******************************************************************************/
/*                                                                            */
/*                             DMA Controller                                 */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for DMA_SxCR register  *****************/
#define DMA_SxCR_MBURST_Pos      (23U)
#define DMA_SxCR_MBURST_Msk      (0x3U << DMA_SxCR_MBURST_Pos)                 /*!< 0x01800000 */
#define DMA_SxCR_MBURST          DMA_SxCR_MBURST_Msk
#define DMA_SxCR_MBURST_0        (0x1U << DMA_SxCR_MBURST_Pos)                 /*!< 0x00800000 */
#define DMA_SxCR_MBURST_1        (0x2U << DMA_SxCR_MBURST_Pos)                 /*!< 0x01000000 */
#define DMA_SxCR_PBURST_Pos      (21U)
#define DMA_SxCR_PBURST_Msk      (0x3U << DMA_SxCR_PBURST_Pos)                 /*!< 0x00600000 */
#define DMA_SxCR_PBURST          DMA_SxCR_PBURST_Msk
#define DMA_SxCR_PBURST_0        (0x1U << DMA_SxCR_PBURST_Pos)                 /*!< 0x00200000 */
#define DMA_SxCR_PBURST_1        (0x2U << DMA_SxCR_PBURST_Pos)                 /*!< 0x00400000 */
#define DMA_SxCR_ACK_Pos         (20U)
#define DMA_SxCR_ACK_Msk         (0x1U << DMA_SxCR_ACK_Pos)                    /*!< 0x00100000 */
#define DMA_SxCR_ACK             DMA_SxCR_ACK_Msk
#define DMA_SxCR_CT_Pos          (19U)
#define DMA_SxCR_CT_Msk          (0x1U << DMA_SxCR_CT_Pos)                     /*!< 0x00080000 */
#define DMA_SxCR_CT              DMA_SxCR_CT_Msk
#define DMA_SxCR_DBM_Pos         (18U)
#define DMA_SxCR_DBM_Msk         (0x1U << DMA_SxCR_DBM_Pos)                    /*!< 0x00040000 */
#define DMA_SxCR_DBM             DMA_SxCR_DBM_Msk
#define DMA_SxCR_PL_Pos          (16U)
#define DMA_SxCR_PL_Msk          (0x3U << DMA_SxCR_PL_Pos)                     /*!< 0x00030000 */
#define DMA_SxCR_PL              DMA_SxCR_PL_Msk
#define DMA_SxCR_PL_0            (0x1U << DMA_SxCR_PL_Pos)                     /*!< 0x00010000 */
#define DMA_SxCR_PL_1            (0x2U << DMA_SxCR_PL_Pos)                     /*!< 0x00020000 */
#define DMA_SxCR_PINCOS_Pos      (15U)
#define DMA_SxCR_PINCOS_Msk      (0x1U << DMA_SxCR_PINCOS_Pos)                 /*!< 0x00008000 */
#define DMA_SxCR_PINCOS          DMA_SxCR_PINCOS_Msk
#define DMA_SxCR_MSIZE_Pos       (13U)
#define DMA_SxCR_MSIZE_Msk       (0x3U << DMA_SxCR_MSIZE_Pos)                  /*!< 0x00006000 */
#define DMA_SxCR_MSIZE           DMA_SxCR_MSIZE_Msk
#define DMA_SxCR_MSIZE_0         (0x1U << DMA_SxCR_MSIZE_Pos)                  /*!< 0x00002000 */
#define DMA_SxCR_MSIZE_1         (0x2U << DMA_SxCR_MSIZE_Pos)                  /*!< 0x00004000 */
#define DMA_SxCR_PSIZE_Pos       (11U)
#define DMA_SxCR_PSIZE_Msk       (0x3U << DMA_SxCR_PSIZE_Pos)                  /*!< 0x00001800 */
#define DMA_SxCR_PSIZE           DMA_SxCR_PSIZE_Msk
#define DMA_SxCR_PSIZE_0         (0x1U << DMA_SxCR_PSIZE_Pos)                  /*!< 0x00000800 */
#define DMA_SxCR_PSIZE_1         (0x2U << DMA_SxCR_PSIZE_Pos)                  /*!< 0x00001000 */
#define DMA_SxCR_MINC_Pos        (10U)
#define DMA_SxCR_MINC_Msk        (0x1U << DMA_SxCR_MINC_Pos)                   /*!< 0x00000400 */
#define DMA_SxCR_MINC            DMA_SxCR_MINC_Msk
#define DMA_SxCR_PINC_Pos        (9U)
#define DMA_SxCR_PINC_Msk        (0x1U << DMA_SxCR_PINC_Pos)                   /*!< 0x00000200 */
#define DMA_SxCR_PINC            DMA_SxCR_PINC_Msk
#define DMA_SxCR_CIRC_Pos        (8U)
#define DMA_SxCR_CIRC_Msk        (0x1U << DMA_SxCR_CIRC_Pos)                   /*!< 0x00000100 */
#define DMA_SxCR_CIRC            DMA_SxCR_CIRC_Msk
#define DMA_SxCR_DIR_Pos         (6U)
#define DMA_SxCR_DIR_Msk         (0x3U << DMA_SxCR_DIR_Pos)                    /*!< 0x000000C0 */
#define DMA_SxCR_DIR             DMA_SxCR_DIR_Msk
#define DMA_SxCR_DIR_0           (0x1U << DMA_SxCR_DIR_Pos)                    /*!< 0x00000040 */
#define DMA_SxCR_DIR_1           (0x2U << DMA_SxCR_DIR_Pos)                    /*!< 0x00000080 */
#define DMA_SxCR_PFCTRL_Pos      (5U)
#define DMA_SxCR_PFCTRL_Msk      (0x1U << DMA_SxCR_PFCTRL_Pos)                 /*!< 0x00000020 */
#define DMA_SxCR_PFCTRL          DMA_SxCR_PFCTRL_Msk
#define DMA_SxCR_TCIE_Pos        (4U)
#define DMA_SxCR_TCIE_Msk        (0x1U << DMA_SxCR_TCIE_Pos)                   /*!< 0x00000010 */
#define DMA_SxCR_TCIE            DMA_SxCR_TCIE_Msk
#define DMA_SxCR_HTIE_Pos        (3U)
#define DMA_SxCR_HTIE_Msk        (0x1U << DMA_SxCR_HTIE_Pos)                   /*!< 0x00000008 */
#define DMA_SxCR_HTIE            DMA_SxCR_HTIE_Msk
#define DMA_SxCR_TEIE_Pos        (2U)
#define DMA_SxCR_TEIE_Msk        (0x1U << DMA_SxCR_TEIE_Pos)                   /*!< 0x00000004 */
#define DMA_SxCR_TEIE            DMA_SxCR_TEIE_Msk
#define DMA_SxCR_DMEIE_Pos       (1U)
#define DMA_SxCR_DMEIE_Msk       (0x1U << DMA_SxCR_DMEIE_Pos)                  /*!< 0x00000002 */
#define DMA_SxCR_DMEIE           DMA_SxCR_DMEIE_Msk
#define DMA_SxCR_EN_Pos          (0U)
#define DMA_SxCR_EN_Msk          (0x1U << DMA_SxCR_EN_Pos)                     /*!< 0x00000001 */
#define DMA_SxCR_EN              DMA_SxCR_EN_Msk

/********************  Bits definition for DMA_SxCNDTR register  **************/
#define DMA_SxNDT_Pos            (0U)
#define DMA_SxNDT_Msk            (0xFFFFU << DMA_SxNDT_Pos)                    /*!< 0x0000FFFF */
#define DMA_SxNDT                DMA_SxNDT_Msk
#define DMA_SxNDT_0              (0x0001U << DMA_SxNDT_Pos)                    /*!< 0x00000001 */
#define DMA_SxNDT_1              (0x0002U << DMA_SxNDT_Pos)                    /*!< 0x00000002 */
#define DMA_SxNDT_2              (0x0004U << DMA_SxNDT_Pos)                    /*!< 0x00000004 */
#define DMA_SxNDT_3              (0x0008U << DMA_SxNDT_Pos)                    /*!< 0x00000008 */
#define DMA_SxNDT_4              (0x0010U << DMA_SxNDT_Pos)                    /*!< 0x00000010 */
#define DMA_SxNDT_5              (0x0020U << DMA_SxNDT_Pos)                    /*!< 0x00000020 */
#define DMA_SxNDT_6              (0x0040U << DMA_SxNDT_Pos)                    /*!< 0x00000040 */
#define DMA_SxNDT_7              (0x0080U << DMA_SxNDT_Pos)                    /*!< 0x00000080 */
#define DMA_SxNDT_8              (0x0100U << DMA_SxNDT_Pos)                    /*!< 0x00000100 */
#define DMA_SxNDT_9              (0x0200U << DMA_SxNDT_Pos)                    /*!< 0x00000200 */
#define DMA_SxNDT_10             (0x0400U << DMA_SxNDT_Pos)                    /*!< 0x00000400 */
#define DMA_SxNDT_11             (0x0800U << DMA_SxNDT_Pos)                    /*!< 0x00000800 */
#define DMA_SxNDT_12             (0x1000U << DMA_SxNDT_Pos)                    /*!< 0x00001000 */
#define DMA_SxNDT_13             (0x2000U << DMA_SxNDT_Pos)                    /*!< 0x00002000 */
#define DMA_SxNDT_14             (0x4000U << DMA_SxNDT_Pos)                    /*!< 0x00004000 */
#define DMA_SxNDT_15             (0x8000U << DMA_SxNDT_Pos)                    /*!< 0x00008000 */

/********************  Bits definition for DMA_SxFCR register  ****************/
#define DMA_SxFCR_FEIE_Pos       (7U)
#define DMA_SxFCR_FEIE_Msk       (0x1U << DMA_SxFCR_FEIE_Pos)                  /*!< 0x00000080 */
#define DMA_SxFCR_FEIE           DMA_SxFCR_FEIE_Msk
#define DMA_SxFCR_FS_Pos         (3U)
#define DMA_SxFCR_FS_Msk         (0x7U << DMA_SxFCR_FS_Pos)                    /*!< 0x00000038 */
#define DMA_SxFCR_FS             DMA_SxFCR_FS_Msk
#define DMA_SxFCR_FS_0           (0x1U << DMA_SxFCR_FS_Pos)                    /*!< 0x00000008 */
#define DMA_SxFCR_FS_1           (0x2U << DMA_SxFCR_FS_Pos)                    /*!< 0x00000010 */
#define DMA_SxFCR_FS_2           (0x4U << DMA_SxFCR_FS_Pos)                    /*!< 0x00000020 */
#define DMA_SxFCR_DMDIS_Pos      (2U)
#define DMA_SxFCR_DMDIS_Msk      (0x1U << DMA_SxFCR_DMDIS_Pos)                 /*!< 0x00000004 */
#define DMA_SxFCR_DMDIS          DMA_SxFCR_DMDIS_Msk
#define DMA_SxFCR_FTH_Pos        (0U)
#define DMA_SxFCR_FTH_Msk        (0x3U << DMA_SxFCR_FTH_Pos)                   /*!< 0x00000003 */
#define DMA_SxFCR_FTH            DMA_SxFCR_FTH_Msk
#define DMA_SxFCR_FTH_0          (0x1U << DMA_SxFCR_FTH_Pos)                   /*!< 0x00000001 */
#define DMA_SxFCR_FTH_1          (0x2U << DMA_SxFCR_FTH_Pos)                   /*!< 0x00000002 */

/******************  Bit definition for DMA_CPAR register  ********************/
#define DMA_SxPAR_PA_Pos         (0U)
#define DMA_SxPAR_PA_Msk         (0xFFFFFFFFU << DMA_SxPAR_PA_Pos)             /*!< 0xFFFFFFFF */
#define DMA_SxPAR_PA             DMA_SxPAR_PA_Msk                              /*!< Peripheral Address */

/******************  Bit definition for DMA_CMAR register  ********************/
#define DMA_SxM0AR_M0A_Pos        (0U)
#define DMA_SxM0AR_M0A_Msk        (0xFFFFFFFFU << DMA_SxM0AR_M0A_Pos)            /*!< 0xFFFFFFFF */
#define DMA_SxM0AR_M0A            DMA_SxM0AR_M0A_Msk                             /*!< Memory Address    */
#define DMA_SxM1AR_M1A_Pos        (0U)
#define DMA_SxM1AR_M1A_Msk        (0xFFFFFFFFU << DMA_SxM1AR_M1A_Pos)            /*!< 0xFFFFFFFF */
#define DMA_SxM1AR_M1A            DMA_SxM1AR_M1A_Msk                             /*!< Memory Address    */

/********************  Bits definition for DMA_LISR register  *****************/
#define DMA_LISR_TCIF3_Pos       (27U)
#define DMA_LISR_TCIF3_Msk       (0x1U << DMA_LISR_TCIF3_Pos)                  /*!< 0x08000000 */
#define DMA_LISR_TCIF3           DMA_LISR_TCIF3_Msk
#define DMA_LISR_HTIF3_Pos       (26U)
#define DMA_LISR_HTIF3_Msk       (0x1U << DMA_LISR_HTIF3_Pos)                  /*!< 0x04000000 */
#define DMA_LISR_HTIF3           DMA_LISR_HTIF3_Msk
#define DMA_LISR_TEIF3_Pos       (25U)
#define DMA_LISR_TEIF3_Msk       (0x1U << DMA_LISR_TEIF3_Pos)                  /*!< 0x02000000 */
#define DMA_LISR_TEIF3           DMA_LISR_TEIF3_Msk
#define DMA_LISR_DMEIF3_Pos      (24U)
#define DMA_LISR_DMEIF3_Msk      (0x1U << DMA_LISR_DMEIF3_Pos)                 /*!< 0x01000000 */
#define DMA_LISR_DMEIF3          DMA_LISR_DMEIF3_Msk
#define DMA_LISR_FEIF3_Pos       (22U)
#define DMA_LISR_FEIF3_Msk       (0x1U << DMA_LISR_FEIF3_Pos)                  /*!< 0x00400000 */
#define DMA_LISR_FEIF3           DMA_LISR_FEIF3_Msk
#define DMA_LISR_TCIF2_Pos       (21U)
#define DMA_LISR_TCIF2_Msk       (0x1U << DMA_LISR_TCIF2_Pos)                  /*!< 0x00200000 */
#define DMA_LISR_TCIF2           DMA_LISR_TCIF2_Msk
#define DMA_LISR_HTIF2_Pos       (20U)
#define DMA_LISR_HTIF2_Msk       (0x1U << DMA_LISR_HTIF2_Pos)                  /*!< 0x00100000 */
#define DMA_LISR_HTIF2           DMA_LISR_HTIF2_Msk
#define DMA_LISR_TEIF2_Pos       (19U)
#define DMA_LISR_TEIF2_Msk       (0x1U << DMA_LISR_TEIF2_Pos)                  /*!< 0x00080000 */
#define DMA_LISR_TEIF2           DMA_LISR_TEIF2_Msk
#define DMA_LISR_DMEIF2_Pos      (18U)
#define DMA_LISR_DMEIF2_Msk      (0x1U << DMA_LISR_DMEIF2_Pos)                 /*!< 0x00040000 */
#define DMA_LISR_DMEIF2          DMA_LISR_DMEIF2_Msk
#define DMA_LISR_FEIF2_Pos       (16U)
#define DMA_LISR_FEIF2_Msk       (0x1U << DMA_LISR_FEIF2_Pos)                  /*!< 0x00010000 */
#define DMA_LISR_FEIF2           DMA_LISR_FEIF2_Msk
#define DMA_LISR_TCIF1_Pos       (11U)
#define DMA_LISR_TCIF1_Msk       (0x1U << DMA_LISR_TCIF1_Pos)                  /*!< 0x00000800 */
#define DMA_LISR_TCIF1           DMA_LISR_TCIF1_Msk
#define DMA_LISR_HTIF1_Pos       (10U)
#define DMA_LISR_HTIF1_Msk       (0x1U << DMA_LISR_HTIF1_Pos)                  /*!< 0x00000400 */
#define DMA_LISR_HTIF1           DMA_LISR_HTIF1_Msk
#define DMA_LISR_TEIF1_Pos       (9U)
#define DMA_LISR_TEIF1_Msk       (0x1U << DMA_LISR_TEIF1_Pos)                  /*!< 0x00000200 */
#define DMA_LISR_TEIF1           DMA_LISR_TEIF1_Msk
#define DMA_LISR_DMEIF1_Pos      (8U)
#define DMA_LISR_DMEIF1_Msk      (0x1U << DMA_LISR_DMEIF1_Pos)                 /*!< 0x00000100 */
#define DMA_LISR_DMEIF1          DMA_LISR_DMEIF1_Msk
#define DMA_LISR_FEIF1_Pos       (6U)
#define DMA_LISR_FEIF1_Msk       (0x1U << DMA_LISR_FEIF1_Pos)                  /*!< 0x00000040 */
#define DMA_LISR_FEIF1           DMA_LISR_FEIF1_Msk
#define DMA_LISR_TCIF0_Pos       (5U)
#define DMA_LISR_TCIF0_Msk       (0x1U << DMA_LISR_TCIF0_Pos)                  /*!< 0x00000020 */
#define DMA_LISR_TCIF0           DMA_LISR_TCIF0_Msk
#define DMA_LISR_HTIF0_Pos       (4U)
#define DMA_LISR_HTIF0_Msk       (0x1U << DMA_LISR_HTIF0_Pos)                  /*!< 0x00000010 */
#define DMA_LISR_HTIF0           DMA_LISR_HTIF0_Msk
#define DMA_LISR_TEIF0_Pos       (3U)
#define DMA_LISR_TEIF0_Msk       (0x1U << DMA_LISR_TEIF0_Pos)                  /*!< 0x00000008 */
#define DMA_LISR_TEIF0           DMA_LISR_TEIF0_Msk
#define DMA_LISR_DMEIF0_Pos      (2U)
#define DMA_LISR_DMEIF0_Msk      (0x1U << DMA_LISR_DMEIF0_Pos)                 /*!< 0x00000004 */
#define DMA_LISR_DMEIF0          DMA_LISR_DMEIF0_Msk
#define DMA_LISR_FEIF0_Pos       (0U)
#define DMA_LISR_FEIF0_Msk       (0x1U << DMA_LISR_FEIF0_Pos)                  /*!< 0x00000001 */
#define DMA_LISR_FEIF0           DMA_LISR_FEIF0_Msk

/********************  Bits definition for DMA_HISR register  *****************/
#define DMA_HISR_TCIF7_Pos       (27U)
#define DMA_HISR_TCIF7_Msk       (0x1U << DMA_HISR_TCIF7_Pos)                  /*!< 0x08000000 */
#define DMA_HISR_TCIF7           DMA_HISR_TCIF7_Msk
#define DMA_HISR_HTIF7_Pos       (26U)
#define DMA_HISR_HTIF7_Msk       (0x1U << DMA_HISR_HTIF7_Pos)                  /*!< 0x04000000 */
#define DMA_HISR_HTIF7           DMA_HISR_HTIF7_Msk
#define DMA_HISR_TEIF7_Pos       (25U)
#define DMA_HISR_TEIF7_Msk       (0x1U << DMA_HISR_TEIF7_Pos)                  /*!< 0x02000000 */
#define DMA_HISR_TEIF7           DMA_HISR_TEIF7_Msk
#define DMA_HISR_DMEIF7_Pos      (24U)
#define DMA_HISR_DMEIF7_Msk      (0x1U << DMA_HISR_DMEIF7_Pos)                 /*!< 0x01000000 */
#define DMA_HISR_DMEIF7          DMA_HISR_DMEIF7_Msk
#define DMA_HISR_FEIF7_Pos       (22U)
#define DMA_HISR_FEIF7_Msk       (0x1U << DMA_HISR_FEIF7_Pos)                  /*!< 0x00400000 */
#define DMA_HISR_FEIF7           DMA_HISR_FEIF7_Msk
#define DMA_HISR_TCIF6_Pos       (21U)
#define DMA_HISR_TCIF6_Msk       (0x1U << DMA_HISR_TCIF6_Pos)                  /*!< 0x00200000 */
#define DMA_HISR_TCIF6           DMA_HISR_TCIF6_Msk
#define DMA_HISR_HTIF6_Pos       (20U)
#define DMA_HISR_HTIF6_Msk       (0x1U << DMA_HISR_HTIF6_Pos)                  /*!< 0x00100000 */
#define DMA_HISR_HTIF6           DMA_HISR_HTIF6_Msk
#define DMA_HISR_TEIF6_Pos       (19U)
#define DMA_HISR_TEIF6_Msk       (0x1U << DMA_HISR_TEIF6_Pos)                  /*!< 0x00080000 */
#define DMA_HISR_TEIF6           DMA_HISR_TEIF6_Msk
#define DMA_HISR_DMEIF6_Pos      (18U)
#define DMA_HISR_DMEIF6_Msk      (0x1U << DMA_HISR_DMEIF6_Pos)                 /*!< 0x00040000 */
#define DMA_HISR_DMEIF6          DMA_HISR_DMEIF6_Msk
#define DMA_HISR_FEIF6_Pos       (16U)
#define DMA_HISR_FEIF6_Msk       (0x1U << DMA_HISR_FEIF6_Pos)                  /*!< 0x00010000 */
#define DMA_HISR_FEIF6           DMA_HISR_FEIF6_Msk
#define DMA_HISR_TCIF5_Pos       (11U)
#define DMA_HISR_TCIF5_Msk       (0x1U << DMA_HISR_TCIF5_Pos)                  /*!< 0x00000800 */
#define DMA_HISR_TCIF5           DMA_HISR_TCIF5_Msk
#define DMA_HISR_HTIF5_Pos       (10U)
#define DMA_HISR_HTIF5_Msk       (0x1U << DMA_HISR_HTIF5_Pos)                  /*!< 0x00000400 */
#define DMA_HISR_HTIF5           DMA_HISR_HTIF5_Msk
#define DMA_HISR_TEIF5_Pos       (9U)
#define DMA_HISR_TEIF5_Msk       (0x1U << DMA_HISR_TEIF5_Pos)                  /*!< 0x00000200 */
#define DMA_HISR_TEIF5           DMA_HISR_TEIF5_Msk
#define DMA_HISR_DMEIF5_Pos      (8U)
#define DMA_HISR_DMEIF5_Msk      (0x1U << DMA_HISR_DMEIF5_Pos)                 /*!< 0x00000100 */
#define DMA_HISR_DMEIF5          DMA_HISR_DMEIF5_Msk
#define DMA_HISR_FEIF5_Pos       (6U)
#define DMA_HISR_FEIF5_Msk       (0x1U << DMA_HISR_FEIF5_Pos)                  /*!< 0x00000040 */
#define DMA_HISR_FEIF5           DMA_HISR_FEIF5_Msk
#define DMA_HISR_TCIF4_Pos       (5U)
#define DMA_HISR_TCIF4_Msk       (0x1U << DMA_HISR_TCIF4_Pos)                  /*!< 0x00000020 */
#define DMA_HISR_TCIF4           DMA_HISR_TCIF4_Msk
#define DMA_HISR_HTIF4_Pos       (4U)
#define DMA_HISR_HTIF4_Msk       (0x1U << DMA_HISR_HTIF4_Pos)                  /*!< 0x00000010 */
#define DMA_HISR_HTIF4           DMA_HISR_HTIF4_Msk
#define DMA_HISR_TEIF4_Pos       (3U)
#define DMA_HISR_TEIF4_Msk       (0x1U << DMA_HISR_TEIF4_Pos)                  /*!< 0x00000008 */
#define DMA_HISR_TEIF4           DMA_HISR_TEIF4_Msk
#define DMA_HISR_DMEIF4_Pos      (2U)
#define DMA_HISR_DMEIF4_Msk      (0x1U << DMA_HISR_DMEIF4_Pos)                 /*!< 0x00000004 */
#define DMA_HISR_DMEIF4          DMA_HISR_DMEIF4_Msk
#define DMA_HISR_FEIF4_Pos       (0U)
#define DMA_HISR_FEIF4_Msk       (0x1U << DMA_HISR_FEIF4_Pos)                  /*!< 0x00000001 */
#define DMA_HISR_FEIF4           DMA_HISR_FEIF4_Msk

/********************  Bits definition for DMA_LIFCR register  ****************/
#define DMA_LIFCR_CTCIF3_Pos     (27U)
#define DMA_LIFCR_CTCIF3_Msk     (0x1U << DMA_LIFCR_CTCIF3_Pos)                /*!< 0x08000000 */
#define DMA_LIFCR_CTCIF3         DMA_LIFCR_CTCIF3_Msk
#define DMA_LIFCR_CHTIF3_Pos     (26U)
#define DMA_LIFCR_CHTIF3_Msk     (0x1U << DMA_LIFCR_CHTIF3_Pos)                /*!< 0x04000000 */
#define DMA_LIFCR_CHTIF3         DMA_LIFCR_CHTIF3_Msk
#define DMA_LIFCR_CTEIF3_Pos     (25U)
#define DMA_LIFCR_CTEIF3_Msk     (0x1U << DMA_LIFCR_CTEIF3_Pos)                /*!< 0x02000000 */
#define DMA_LIFCR_CTEIF3         DMA_LIFCR_CTEIF3_Msk
#define DMA_LIFCR_CDMEIF3_Pos    (24U)
#define DMA_LIFCR_CDMEIF3_Msk    (0x1U << DMA_LIFCR_CDMEIF3_Pos)               /*!< 0x01000000 */
#define DMA_LIFCR_CDMEIF3        DMA_LIFCR_CDMEIF3_Msk
#define DMA_LIFCR_CFEIF3_Pos     (22U)
#define DMA_LIFCR_CFEIF3_Msk     (0x1U << DMA_LIFCR_CFEIF3_Pos)                /*!< 0x00400000 */
#define DMA_LIFCR_CFEIF3         DMA_LIFCR_CFEIF3_Msk
#define DMA_LIFCR_CTCIF2_Pos     (21U)
#define DMA_LIFCR_CTCIF2_Msk     (0x1U << DMA_LIFCR_CTCIF2_Pos)                /*!< 0x00200000 */
#define DMA_LIFCR_CTCIF2         DMA_LIFCR_CTCIF2_Msk
#define DMA_LIFCR_CHTIF2_Pos     (20U)
#define DMA_LIFCR_CHTIF2_Msk     (0x1U << DMA_LIFCR_CHTIF2_Pos)                /*!< 0x00100000 */
#define DMA_LIFCR_CHTIF2         DMA_LIFCR_CHTIF2_Msk
#define DMA_LIFCR_CTEIF2_Pos     (19U)
#define DMA_LIFCR_CTEIF2_Msk     (0x1U << DMA_LIFCR_CTEIF2_Pos)                /*!< 0x00080000 */
#define DMA_LIFCR_CTEIF2         DMA_LIFCR_CTEIF2_Msk
#define DMA_LIFCR_CDMEIF2_Pos    (18U)
#define DMA_LIFCR_CDMEIF2_Msk    (0x1U << DMA_LIFCR_CDMEIF2_Pos)               /*!< 0x00040000 */
#define DMA_LIFCR_CDMEIF2        DMA_LIFCR_CDMEIF2_Msk
#define DMA_LIFCR_CFEIF2_Pos     (16U)
#define DMA_LIFCR_CFEIF2_Msk     (0x1U << DMA_LIFCR_CFEIF2_Pos)                /*!< 0x00010000 */
#define DMA_LIFCR_CFEIF2         DMA_LIFCR_CFEIF2_Msk
#define DMA_LIFCR_CTCIF1_Pos     (11U)
#define DMA_LIFCR_CTCIF1_Msk     (0x1U << DMA_LIFCR_CTCIF1_Pos)                /*!< 0x00000800 */
#define DMA_LIFCR_CTCIF1         DMA_LIFCR_CTCIF1_Msk
#define DMA_LIFCR_CHTIF1_Pos     (10U)
#define DMA_LIFCR_CHTIF1_Msk     (0x1U << DMA_LIFCR_CHTIF1_Pos)                /*!< 0x00000400 */
#define DMA_LIFCR_CHTIF1         DMA_LIFCR_CHTIF1_Msk
#define DMA_LIFCR_CTEIF1_Pos     (9U)
#define DMA_LIFCR_CTEIF1_Msk     (0x1U << DMA_LIFCR_CTEIF1_Pos)                /*!< 0x00000200 */
#define DMA_LIFCR_CTEIF1         DMA_LIFCR_CTEIF1_Msk
#define DMA_LIFCR_CDMEIF1_Pos    (8U)
#define DMA_LIFCR_CDMEIF1_Msk    (0x1U << DMA_LIFCR_CDMEIF1_Pos)               /*!< 0x00000100 */
#define DMA_LIFCR_CDMEIF1        DMA_LIFCR_CDMEIF1_Msk
#define DMA_LIFCR_CFEIF1_Pos     (6U)
#define DMA_LIFCR_CFEIF1_Msk     (0x1U << DMA_LIFCR_CFEIF1_Pos)                /*!< 0x00000040 */
#define DMA_LIFCR_CFEIF1         DMA_LIFCR_CFEIF1_Msk
#define DMA_LIFCR_CTCIF0_Pos     (5U)
#define DMA_LIFCR_CTCIF0_Msk     (0x1U << DMA_LIFCR_CTCIF0_Pos)                /*!< 0x00000020 */
#define DMA_LIFCR_CTCIF0         DMA_LIFCR_CTCIF0_Msk
#define DMA_LIFCR_CHTIF0_Pos     (4U)
#define DMA_LIFCR_CHTIF0_Msk     (0x1U << DMA_LIFCR_CHTIF0_Pos)                /*!< 0x00000010 */
#define DMA_LIFCR_CHTIF0         DMA_LIFCR_CHTIF0_Msk
#define DMA_LIFCR_CTEIF0_Pos     (3U)
#define DMA_LIFCR_CTEIF0_Msk     (0x1U << DMA_LIFCR_CTEIF0_Pos)                /*!< 0x00000008 */
#define DMA_LIFCR_CTEIF0         DMA_LIFCR_CTEIF0_Msk
#define DMA_LIFCR_CDMEIF0_Pos    (2U)
#define DMA_LIFCR_CDMEIF0_Msk    (0x1U << DMA_LIFCR_CDMEIF0_Pos)               /*!< 0x00000004 */
#define DMA_LIFCR_CDMEIF0        DMA_LIFCR_CDMEIF0_Msk
#define DMA_LIFCR_CFEIF0_Pos     (0U)
#define DMA_LIFCR_CFEIF0_Msk     (0x1U << DMA_LIFCR_CFEIF0_Pos)                /*!< 0x00000001 */
#define DMA_LIFCR_CFEIF0         DMA_LIFCR_CFEIF0_Msk

/********************  Bits definition for DMA_HIFCR  register  ****************/
#define DMA_HIFCR_CTCIF7_Pos     (27U)
#define DMA_HIFCR_CTCIF7_Msk     (0x1U << DMA_HIFCR_CTCIF7_Pos)                /*!< 0x08000000 */
#define DMA_HIFCR_CTCIF7         DMA_HIFCR_CTCIF7_Msk
#define DMA_HIFCR_CHTIF7_Pos     (26U)
#define DMA_HIFCR_CHTIF7_Msk     (0x1U << DMA_HIFCR_CHTIF7_Pos)                /*!< 0x04000000 */
#define DMA_HIFCR_CHTIF7         DMA_HIFCR_CHTIF7_Msk
#define DMA_HIFCR_CTEIF7_Pos     (25U)
#define DMA_HIFCR_CTEIF7_Msk     (0x1U << DMA_HIFCR_CTEIF7_Pos)                /*!< 0x02000000 */
#define DMA_HIFCR_CTEIF7         DMA_HIFCR_CTEIF7_Msk
#define DMA_HIFCR_CDMEIF7_Pos    (24U)
#define DMA_HIFCR_CDMEIF7_Msk    (0x1U << DMA_HIFCR_CDMEIF7_Pos)               /*!< 0x01000000 */
#define DMA_HIFCR_CDMEIF7        DMA_HIFCR_CDMEIF7_Msk
#define DMA_HIFCR_CFEIF7_Pos     (22U)
#define DMA_HIFCR_CFEIF7_Msk     (0x1U << DMA_HIFCR_CFEIF7_Pos)                /*!< 0x00400000 */
#define DMA_HIFCR_CFEIF7         DMA_HIFCR_CFEIF7_Msk
#define DMA_HIFCR_CTCIF6_Pos     (21U)
#define DMA_HIFCR_CTCIF6_Msk     (0x1U << DMA_HIFCR_CTCIF6_Pos)                /*!< 0x00200000 */
#define DMA_HIFCR_CTCIF6         DMA_HIFCR_CTCIF6_Msk
#define DMA_HIFCR_CHTIF6_Pos     (20U)
#define DMA_HIFCR_CHTIF6_Msk     (0x1U << DMA_HIFCR_CHTIF6_Pos)                /*!< 0x00100000 */
#define DMA_HIFCR_CHTIF6         DMA_HIFCR_CHTIF6_Msk
#define DMA_HIFCR_CTEIF6_Pos     (19U)
#define DMA_HIFCR_CTEIF6_Msk     (0x1U << DMA_HIFCR_CTEIF6_Pos)                /*!< 0x00080000 */
#define DMA_HIFCR_CTEIF6         DMA_HIFCR_CTEIF6_Msk
#define DMA_HIFCR_CDMEIF6_Pos    (18U)
#define DMA_HIFCR_CDMEIF6_Msk    (0x1U << DMA_HIFCR_CDMEIF6_Pos)               /*!< 0x00040000 */
#define DMA_HIFCR_CDMEIF6        DMA_HIFCR_CDMEIF6_Msk
#define DMA_HIFCR_CFEIF6_Pos     (16U)
#define DMA_HIFCR_CFEIF6_Msk     (0x1U << DMA_HIFCR_CFEIF6_Pos)                /*!< 0x00010000 */
#define DMA_HIFCR_CFEIF6         DMA_HIFCR_CFEIF6_Msk
#define DMA_HIFCR_CTCIF5_Pos     (11U)
#define DMA_HIFCR_CTCIF5_Msk     (0x1U << DMA_HIFCR_CTCIF5_Pos)                /*!< 0x00000800 */
#define DMA_HIFCR_CTCIF5         DMA_HIFCR_CTCIF5_Msk
#define DMA_HIFCR_CHTIF5_Pos     (10U)
#define DMA_HIFCR_CHTIF5_Msk     (0x1U << DMA_HIFCR_CHTIF5_Pos)                /*!< 0x00000400 */
#define DMA_HIFCR_CHTIF5         DMA_HIFCR_CHTIF5_Msk
#define DMA_HIFCR_CTEIF5_Pos     (9U)
#define DMA_HIFCR_CTEIF5_Msk     (0x1U << DMA_HIFCR_CTEIF5_Pos)                /*!< 0x00000200 */
#define DMA_HIFCR_CTEIF5         DMA_HIFCR_CTEIF5_Msk
#define DMA_HIFCR_CDMEIF5_Pos    (8U)
#define DMA_HIFCR_CDMEIF5_Msk    (0x1U << DMA_HIFCR_CDMEIF5_Pos)               /*!< 0x00000100 */
#define DMA_HIFCR_CDMEIF5        DMA_HIFCR_CDMEIF5_Msk
#define DMA_HIFCR_CFEIF5_Pos     (6U)
#define DMA_HIFCR_CFEIF5_Msk     (0x1U << DMA_HIFCR_CFEIF5_Pos)                /*!< 0x00000040 */
#define DMA_HIFCR_CFEIF5         DMA_HIFCR_CFEIF5_Msk
#define DMA_HIFCR_CTCIF4_Pos     (5U)
#define DMA_HIFCR_CTCIF4_Msk     (0x1U << DMA_HIFCR_CTCIF4_Pos)                /*!< 0x00000020 */
#define DMA_HIFCR_CTCIF4         DMA_HIFCR_CTCIF4_Msk
#define DMA_HIFCR_CHTIF4_Pos     (4U)
#define DMA_HIFCR_CHTIF4_Msk     (0x1U << DMA_HIFCR_CHTIF4_Pos)                /*!< 0x00000010 */
#define DMA_HIFCR_CHTIF4         DMA_HIFCR_CHTIF4_Msk
#define DMA_HIFCR_CTEIF4_Pos     (3U)
#define DMA_HIFCR_CTEIF4_Msk     (0x1U << DMA_HIFCR_CTEIF4_Pos)                /*!< 0x00000008 */
#define DMA_HIFCR_CTEIF4         DMA_HIFCR_CTEIF4_Msk
#define DMA_HIFCR_CDMEIF4_Pos    (2U)
#define DMA_HIFCR_CDMEIF4_Msk    (0x1U << DMA_HIFCR_CDMEIF4_Pos)               /*!< 0x00000004 */
#define DMA_HIFCR_CDMEIF4        DMA_HIFCR_CDMEIF4_Msk
#define DMA_HIFCR_CFEIF4_Pos     (0U)
#define DMA_HIFCR_CFEIF4_Msk     (0x1U << DMA_HIFCR_CFEIF4_Pos)                /*!< 0x00000001 */
#define DMA_HIFCR_CFEIF4         DMA_HIFCR_CFEIF4_Msk

/**********************  Bit definition for DMA_HWCFGR2 register  ***************/
#define DMA_HWCFGR2_FIFO_SIZE_Pos         (0U)
#define DMA_HWCFGR2_FIFO_SIZE_Msk         (0x3U << DMA_HWCFGR2_FIFO_SIZE_Pos)          /*!< 0x00000003 */
#define DMA_HWCFGR2_FIFO_SIZE              DMA_HWCFGR2_FIFO_SIZE_Msk                   /*!< FIFO size, common to all streams*/
#define DMA_HWCFGR2_WRITE_BUFFERABLE_Pos  (4U)
#define DMA_HWCFGR2_WRITE_BUFFERABLE_Msk  (0x1U << DMA_HWCFGR2_WRITE_BUFFERABLE_Pos)   /*!< 0x00000010 */
#define DMA_HWCFGR2_WRITE_BUFFERABLE       DMA_HWCFGR2_WRITE_BUFFERABLE_Msk            /*!< Write bufferable*/
#define DMA_HWCFGR2_CHSEL_WIDTH_Pos       (8U)
#define DMA_HWCFGR2_CHSEL_WIDTH_Msk       (0x7U << DMA_HWCFGR2_CHSEL_WIDTH_Pos)        /*!< 0x00000700 */
#define DMA_HWCFGR2_CHSEL_WIDTH            DMA_HWCFGR2_CHSEL_WIDTH_Msk                 /*!< width of the CHSEL field */

/**********************  Bit definition for DMA_HWCFGR1 register  ***************/
#define DMA_HWCFGR1_DMA_DEF0_Pos  (0U)
#define DMA_HWCFGR1_DMA_DEF0_Msk  (0x3U << DMA_HWCFGR1_DMA_DEF0_Pos)          /*!< 0x00000003 */
#define DMA_HWCFGR1_DMA_DEF0      DMA_HWCFGR1_DMA_DEF0_Msk                     /*!< Type of the stream 0 */
#define DMA_HWCFGR1_DMA_DEF1_Pos  (4U)
#define DMA_HWCFGR1_DMA_DEF1_Msk  (0x3U << DMA_HWCFGR1_DMA_DEF1_Pos)          /*!< 0x00000030 */
#define DMA_HWCFGR1_DMA_DEF1      DMA_HWCFGR1_DMA_DEF1_Msk                     /*!< Type of the stream 1 */
#define DMA_HWCFGR1_DMA_DEF2_Pos  (8U)
#define DMA_HWCFGR1_DMA_DEF2_Msk  (0x3U << DMA_HWCFGR1_DMA_DEF2_Pos)          /*!< 0x00000300 */
#define DMA_HWCFGR1_DMA_DEF2      DMA_HWCFGR1_DMA_DEF2_Msk                     /*!< Type of the stream 2 */
#define DMA_HWCFGR1_DMA_DEF3_Pos  (12U)
#define DMA_HWCFGR1_DMA_DEF3_Msk  (0x3U << DMA_HWCFGR1_DMA_DEF3_Pos)          /*!< 0x00003000 */
#define DMA_HWCFGR1_DMA_DEF3      DMA_HWCFGR1_DMA_DEF3_Msk                     /*!< Type of the stream 3 */
#define DMA_HWCFGR1_DMA_DEF4_Pos  (16U)
#define DMA_HWCFGR1_DMA_DEF4_Msk  (0x3U << DMA_HWCFGR1_DMA_DEF4_Pos)          /*!< 0x00030000 */
#define DMA_HWCFGR1_DMA_DEF4      DMA_HWCFGR1_DMA_DEF4_Msk                     /*!< Type of the stream 4 */
#define DMA_HWCFGR1_DMA_DEF5_Pos  (20U)
#define DMA_HWCFGR1_DMA_DEF5_Msk  (0x3U << DMA_HWCFGR1_DMA_DEF5_Pos)          /*!< 0x00300000 */
#define DMA_HWCFGR1_DMA_DEF5      DMA_HWCFGR1_DMA_DEF5_Msk                     /*!< Type of the stream 5 */
#define DMA_HWCFGR1_DMA_DEF6_Pos  (24U)
#define DMA_HWCFGR1_DMA_DEF6_Msk  (0x3U << DMA_HWCFGR1_DMA_DEF6_Pos)          /*!< 0x03000000 */
#define DMA_HWCFGR1_DMA_DEF6      DMA_HWCFGR1_DMA_DEF6_Msk                     /*!< Type of the stream 6 */
#define DMA_HWCFGR1_DMA_DEF7_Pos  (28U)
#define DMA_HWCFGR1_DMA_DEF7_Msk  (0x3U << DMA_HWCFGR1_DMA_DEF7_Pos)          /*!< 0x30000000 */
#define DMA_HWCFGR1_DMA_DEF7      DMA_HWCFGR1_DMA_DEF7_Msk                     /*!< Type of the stream 7 */

/**********************  Bit definition for DMA_VERR register  *****************/
#define DMA_VERR_MINREV_Pos      (0U)
#define DMA_VERR_MINREV_Msk      (0xFU << DMA_VERR_MINREV_Pos)               /*!< 0x0000000F */
#define DMA_VERR_MINREV          DMA_VERR_MINREV_Msk                         /*!< Minor Revision number */
#define DMA_VERR_MAJREV_Pos      (4U)
#define DMA_VERR_MAJREV_Msk      (0xFU << DMA_VERR_MAJREV_Pos)               /*!< 0x000000F0 */
#define DMA_VERR_MAJREV          DMA_VERR_MAJREV_Msk                         /*!< Major Revision number */

/**********************  Bit definition for DMA_IPIDR register  ****************/
#define DMA_IPIDR_ID_Pos         (0U)
#define DMA_IPIDR_ID_Msk         (0xFFFFFFFFU << DMA_IPIDR_ID_Pos)         /*!< 0xFFFFFFFF */
#define DMA_IPIDR_ID             DMA_IPIDR_ID_Msk                          /*!< IP Identification */

/**********************  Bit definition for DMA_SIDR register  *****************/
#define DMA_SIDR_SID_Pos         (0U)
#define DMA_SIDR_SID_Msk         (0xFFFFFFFFU << DMA_SIDR_SID_Pos)           /*!< 0xFFFFFFFF */
#define DMA_SIDR_SID             DMA_SIDR_SID_Msk                            /*!< IP size identification */

/******************************************************************************/
/*                                                                            */
/*                             DMAMUX Controller                              */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for DMAMUX_CxCR register  **************/
#define DMAMUX_CxCR_DMAREQ_ID_Pos      (0U)
#define DMAMUX_CxCR_DMAREQ_ID_Msk      (0xFFU << DMAMUX_CxCR_DMAREQ_ID_Pos)    /*!< 0x000000FF */
#define DMAMUX_CxCR_DMAREQ_ID          DMAMUX_CxCR_DMAREQ_ID_Msk
#define DMAMUX_CxCR_DMAREQ_ID_0        (0x01U << DMAMUX_CxCR_DMAREQ_ID_Pos)    /*!< 0x00000001 */
#define DMAMUX_CxCR_DMAREQ_ID_1        (0x02U << DMAMUX_CxCR_DMAREQ_ID_Pos)    /*!< 0x00000002 */
#define DMAMUX_CxCR_DMAREQ_ID_2        (0x04U << DMAMUX_CxCR_DMAREQ_ID_Pos)    /*!< 0x00000004 */
#define DMAMUX_CxCR_DMAREQ_ID_3        (0x08U << DMAMUX_CxCR_DMAREQ_ID_Pos)    /*!< 0x00000008 */
#define DMAMUX_CxCR_DMAREQ_ID_4        (0x10U << DMAMUX_CxCR_DMAREQ_ID_Pos)    /*!< 0x00000010 */
#define DMAMUX_CxCR_DMAREQ_ID_5        (0x20U << DMAMUX_CxCR_DMAREQ_ID_Pos)    /*!< 0x00000020 */
#define DMAMUX_CxCR_DMAREQ_ID_6        (0x40U << DMAMUX_CxCR_DMAREQ_ID_Pos)    /*!< 0x00000040 */
#define DMAMUX_CxCR_DMAREQ_ID_7        (0x80U << DMAMUX_CxCR_DMAREQ_ID_Pos)    /*!< 0x00000080 */
#define DMAMUX_CxCR_SOIE_Pos           (8U)
#define DMAMUX_CxCR_SOIE_Msk           (0x1U << DMAMUX_CxCR_SOIE_Pos)          /*!< 0x00000100 */
#define DMAMUX_CxCR_SOIE               DMAMUX_CxCR_SOIE_Msk
#define DMAMUX_CxCR_EGE_Pos            (9U)
#define DMAMUX_CxCR_EGE_Msk            (0x1U << DMAMUX_CxCR_EGE_Pos)           /*!< 0x00000200 */
#define DMAMUX_CxCR_EGE                DMAMUX_CxCR_EGE_Msk
#define DMAMUX_CxCR_SE_Pos             (16U)
#define DMAMUX_CxCR_SE_Msk             (0x1U << DMAMUX_CxCR_SE_Pos)            /*!< 0x00010000 */
#define DMAMUX_CxCR_SE                 DMAMUX_CxCR_SE_Msk
#define DMAMUX_CxCR_SPOL_Pos           (17U)
#define DMAMUX_CxCR_SPOL_Msk           (0x3U << DMAMUX_CxCR_SPOL_Pos)          /*!< 0x00060000 */
#define DMAMUX_CxCR_SPOL               DMAMUX_CxCR_SPOL_Msk
#define DMAMUX_CxCR_SPOL_0             (0x1U << DMAMUX_CxCR_SPOL_Pos)          /*!< 0x00020000 */
#define DMAMUX_CxCR_SPOL_1             (0x2U << DMAMUX_CxCR_SPOL_Pos)          /*!< 0x00040000 */
#define DMAMUX_CxCR_NBREQ_Pos          (19U)
#define DMAMUX_CxCR_NBREQ_Msk          (0x1FU << DMAMUX_CxCR_NBREQ_Pos)        /*!< 0x00F80000 */
#define DMAMUX_CxCR_NBREQ              DMAMUX_CxCR_NBREQ_Msk
#define DMAMUX_CxCR_NBREQ_0            (0x01U << DMAMUX_CxCR_NBREQ_Pos)        /*!< 0x00080000 */
#define DMAMUX_CxCR_NBREQ_1            (0x02U << DMAMUX_CxCR_NBREQ_Pos)        /*!< 0x00100000 */
#define DMAMUX_CxCR_NBREQ_2            (0x04U << DMAMUX_CxCR_NBREQ_Pos)        /*!< 0x00200000 */
#define DMAMUX_CxCR_NBREQ_3            (0x08U << DMAMUX_CxCR_NBREQ_Pos)        /*!< 0x00400000 */
#define DMAMUX_CxCR_NBREQ_4            (0x10U << DMAMUX_CxCR_NBREQ_Pos)        /*!< 0x00800000 */
#define DMAMUX_CxCR_SYNC_ID_Pos        (24U)
#define DMAMUX_CxCR_SYNC_ID_Msk        (0x1FU << DMAMUX_CxCR_SYNC_ID_Pos)      /*!< 0x1F000000 */
#define DMAMUX_CxCR_SYNC_ID            DMAMUX_CxCR_SYNC_ID_Msk
#define DMAMUX_CxCR_SYNC_ID_0          (0x01U << DMAMUX_CxCR_SYNC_ID_Pos)      /*!< 0x01000000 */
#define DMAMUX_CxCR_SYNC_ID_1          (0x02U << DMAMUX_CxCR_SYNC_ID_Pos)      /*!< 0x02000000 */
#define DMAMUX_CxCR_SYNC_ID_2          (0x04U << DMAMUX_CxCR_SYNC_ID_Pos)      /*!< 0x04000000 */
#define DMAMUX_CxCR_SYNC_ID_3          (0x08U << DMAMUX_CxCR_SYNC_ID_Pos)      /*!< 0x08000000 */
#define DMAMUX_CxCR_SYNC_ID_4          (0x10U << DMAMUX_CxCR_SYNC_ID_Pos)      /*!< 0x10000000 */

/********************  Bits definition for DMAMUX_CSR register  **************/
#define DMAMUX_CSR_SOF0_Pos            (0U)
#define DMAMUX_CSR_SOF0_Msk            (0x1U << DMAMUX_CSR_SOF0_Pos)           /*!< 0x00000001 */
#define DMAMUX_CSR_SOF0                DMAMUX_CSR_SOF0_Msk
#define DMAMUX_CSR_SOF1_Pos            (1U)
#define DMAMUX_CSR_SOF1_Msk            (0x1U << DMAMUX_CSR_SOF1_Pos)           /*!< 0x00000002 */
#define DMAMUX_CSR_SOF1                DMAMUX_CSR_SOF1_Msk
#define DMAMUX_CSR_SOF2_Pos            (2U)
#define DMAMUX_CSR_SOF2_Msk            (0x1U << DMAMUX_CSR_SOF2_Pos)           /*!< 0x00000004 */
#define DMAMUX_CSR_SOF2                DMAMUX_CSR_SOF2_Msk
#define DMAMUX_CSR_SOF3_Pos            (3U)
#define DMAMUX_CSR_SOF3_Msk            (0x1U << DMAMUX_CSR_SOF3_Pos)           /*!< 0x00000008 */
#define DMAMUX_CSR_SOF3                DMAMUX_CSR_SOF3_Msk
#define DMAMUX_CSR_SOF4_Pos            (4U)
#define DMAMUX_CSR_SOF4_Msk            (0x1U << DMAMUX_CSR_SOF4_Pos)           /*!< 0x00000010 */
#define DMAMUX_CSR_SOF4                DMAMUX_CSR_SOF4_Msk
#define DMAMUX_CSR_SOF5_Pos            (5U)
#define DMAMUX_CSR_SOF5_Msk            (0x1U << DMAMUX_CSR_SOF5_Pos)           /*!< 0x00000020 */
#define DMAMUX_CSR_SOF5                DMAMUX_CSR_SOF5_Msk
#define DMAMUX_CSR_SOF6_Pos            (6U)
#define DMAMUX_CSR_SOF6_Msk            (0x1U << DMAMUX_CSR_SOF6_Pos)           /*!< 0x00000040 */
#define DMAMUX_CSR_SOF6                DMAMUX_CSR_SOF6_Msk
#define DMAMUX_CSR_SOF7_Pos            (7U)
#define DMAMUX_CSR_SOF7_Msk            (0x1U << DMAMUX_CSR_SOF7_Pos)           /*!< 0x00000080 */
#define DMAMUX_CSR_SOF7                DMAMUX_CSR_SOF7_Msk
#define DMAMUX_CSR_SOF8_Pos            (8U)
#define DMAMUX_CSR_SOF8_Msk            (0x1U << DMAMUX_CSR_SOF8_Pos)           /*!< 0x00000100 */
#define DMAMUX_CSR_SOF8                DMAMUX_CSR_SOF8_Msk
#define DMAMUX_CSR_SOF9_Pos            (9U)
#define DMAMUX_CSR_SOF9_Msk            (0x1U << DMAMUX_CSR_SOF9_Pos)           /*!< 0x00000200 */
#define DMAMUX_CSR_SOF9                DMAMUX_CSR_SOF9_Msk
#define DMAMUX_CSR_SOF10_Pos           (10U)
#define DMAMUX_CSR_SOF10_Msk           (0x1U << DMAMUX_CSR_SOF10_Pos)          /*!< 0x00000400 */
#define DMAMUX_CSR_SOF10               DMAMUX_CSR_SOF10_Msk
#define DMAMUX_CSR_SOF11_Pos           (11U)
#define DMAMUX_CSR_SOF11_Msk           (0x1U << DMAMUX_CSR_SOF11_Pos)          /*!< 0x00000800 */
#define DMAMUX_CSR_SOF11               DMAMUX_CSR_SOF11_Msk
#define DMAMUX_CSR_SOF12_Pos           (12U)
#define DMAMUX_CSR_SOF12_Msk           (0x1U << DMAMUX_CSR_SOF12_Pos)          /*!< 0x00001000 */
#define DMAMUX_CSR_SOF12               DMAMUX_CSR_SOF12_Msk
#define DMAMUX_CSR_SOF13_Pos           (13U)
#define DMAMUX_CSR_SOF13_Msk           (0x1U << DMAMUX_CSR_SOF13_Pos)          /*!< 0x00002000 */
#define DMAMUX_CSR_SOF13               DMAMUX_CSR_SOF13_Msk
#define DMAMUX_CSR_SOF14_Pos           (14U)
#define DMAMUX_CSR_SOF14_Msk           (0x1U << DMAMUX_CSR_SOF14_Pos)          /*!< 0x00004000 */
#define DMAMUX_CSR_SOF14               DMAMUX_CSR_SOF14_Msk
#define DMAMUX_CSR_SOF15_Pos           (15U)
#define DMAMUX_CSR_SOF15_Msk           (0x1U << DMAMUX_CSR_SOF15_Pos)          /*!< 0x00008000 */
#define DMAMUX_CSR_SOF15               DMAMUX_CSR_SOF15_Msk

/********************  Bits definition for DMAMUX_CFR register  **************/
#define DMAMUX_CFR_CSOF0_Pos           (0U)
#define DMAMUX_CFR_CSOF0_Msk           (0x1U << DMAMUX_CFR_CSOF0_Pos)          /*!< 0x00000001 */
#define DMAMUX_CFR_CSOF0               DMAMUX_CFR_CSOF0_Msk
#define DMAMUX_CFR_CSOF1_Pos           (1U)
#define DMAMUX_CFR_CSOF1_Msk           (0x1U << DMAMUX_CFR_CSOF1_Pos)          /*!< 0x00000002 */
#define DMAMUX_CFR_CSOF1               DMAMUX_CFR_CSOF1_Msk
#define DMAMUX_CFR_CSOF2_Pos           (2U)
#define DMAMUX_CFR_CSOF2_Msk           (0x1U << DMAMUX_CFR_CSOF2_Pos)          /*!< 0x00000004 */
#define DMAMUX_CFR_CSOF2               DMAMUX_CFR_CSOF2_Msk
#define DMAMUX_CFR_CSOF3_Pos           (3U)
#define DMAMUX_CFR_CSOF3_Msk           (0x1U << DMAMUX_CFR_CSOF3_Pos)          /*!< 0x00000008 */
#define DMAMUX_CFR_CSOF3               DMAMUX_CFR_CSOF3_Msk
#define DMAMUX_CFR_CSOF4_Pos           (4U)
#define DMAMUX_CFR_CSOF4_Msk           (0x1U << DMAMUX_CFR_CSOF4_Pos)          /*!< 0x00000010 */
#define DMAMUX_CFR_CSOF4               DMAMUX_CFR_CSOF4_Msk
#define DMAMUX_CFR_CSOF5_Pos           (5U)
#define DMAMUX_CFR_CSOF5_Msk           (0x1U << DMAMUX_CFR_CSOF5_Pos)          /*!< 0x00000020 */
#define DMAMUX_CFR_CSOF5               DMAMUX_CFR_CSOF5_Msk
#define DMAMUX_CFR_CSOF6_Pos           (6U)
#define DMAMUX_CFR_CSOF6_Msk           (0x1U << DMAMUX_CFR_CSOF6_Pos)          /*!< 0x00000040 */
#define DMAMUX_CFR_CSOF6               DMAMUX_CFR_CSOF6_Msk
#define DMAMUX_CFR_CSOF7_Pos           (7U)
#define DMAMUX_CFR_CSOF7_Msk           (0x1U << DMAMUX_CFR_CSOF7_Pos)          /*!< 0x00000080 */
#define DMAMUX_CFR_CSOF7               DMAMUX_CFR_CSOF7_Msk
#define DMAMUX_CFR_CSOF8_Pos           (8U)
#define DMAMUX_CFR_CSOF8_Msk           (0x1U << DMAMUX_CFR_CSOF8_Pos)          /*!< 0x00000100 */
#define DMAMUX_CFR_CSOF8               DMAMUX_CFR_CSOF8_Msk
#define DMAMUX_CFR_CSOF9_Pos           (9U)
#define DMAMUX_CFR_CSOF9_Msk           (0x1U << DMAMUX_CFR_CSOF9_Pos)          /*!< 0x00000200 */
#define DMAMUX_CFR_CSOF9               DMAMUX_CFR_CSOF9_Msk
#define DMAMUX_CFR_CSOF10_Pos          (10U)
#define DMAMUX_CFR_CSOF10_Msk          (0x1U << DMAMUX_CFR_CSOF10_Pos)         /*!< 0x00000400 */
#define DMAMUX_CFR_CSOF10              DMAMUX_CFR_CSOF10_Msk
#define DMAMUX_CFR_CSOF11_Pos          (11U)
#define DMAMUX_CFR_CSOF11_Msk          (0x1U << DMAMUX_CFR_CSOF11_Pos)         /*!< 0x00000800 */
#define DMAMUX_CFR_CSOF11              DMAMUX_CFR_CSOF11_Msk
#define DMAMUX_CFR_CSOF12_Pos          (12U)
#define DMAMUX_CFR_CSOF12_Msk          (0x1U << DMAMUX_CFR_CSOF12_Pos)         /*!< 0x00001000 */
#define DMAMUX_CFR_CSOF12              DMAMUX_CFR_CSOF12_Msk
#define DMAMUX_CFR_CSOF13_Pos          (13U)
#define DMAMUX_CFR_CSOF13_Msk          (0x1U << DMAMUX_CFR_CSOF13_Pos)         /*!< 0x00002000 */
#define DMAMUX_CFR_CSOF13              DMAMUX_CFR_CSOF13_Msk
#define DMAMUX_CFR_CSOF14_Pos          (14U)
#define DMAMUX_CFR_CSOF14_Msk          (0x1U << DMAMUX_CFR_CSOF14_Pos)         /*!< 0x00004000 */
#define DMAMUX_CFR_CSOF14              DMAMUX_CFR_CSOF14_Msk
#define DMAMUX_CFR_CSOF15_Pos          (15U)
#define DMAMUX_CFR_CSOF15_Msk          (0x1U << DMAMUX_CFR_CSOF15_Pos)         /*!< 0x00008000 */
#define DMAMUX_CFR_CSOF15              DMAMUX_CFR_CSOF15_Msk

/********************  Bits definition for DMAMUX_RGxCR register  ************/
#define DMAMUX_RGxCR_SIG_ID_Pos        (0U)
#define DMAMUX_RGxCR_SIG_ID_Msk        (0x1FU << DMAMUX_RGxCR_SIG_ID_Pos)      /*!< 0x0000001F */
#define DMAMUX_RGxCR_SIG_ID            DMAMUX_RGxCR_SIG_ID_Msk
#define DMAMUX_RGxCR_SIG_ID_0          (0x01U << DMAMUX_RGxCR_SIG_ID_Pos)      /*!< 0x00000001 */
#define DMAMUX_RGxCR_SIG_ID_1          (0x02U << DMAMUX_RGxCR_SIG_ID_Pos)      /*!< 0x00000002 */
#define DMAMUX_RGxCR_SIG_ID_2          (0x04U << DMAMUX_RGxCR_SIG_ID_Pos)      /*!< 0x00000004 */
#define DMAMUX_RGxCR_SIG_ID_3          (0x08U << DMAMUX_RGxCR_SIG_ID_Pos)      /*!< 0x00000008 */
#define DMAMUX_RGxCR_SIG_ID_4          (0x10U << DMAMUX_RGxCR_SIG_ID_Pos)      /*!< 0x00000010 */
#define DMAMUX_RGxCR_OIE_Pos           (8U)
#define DMAMUX_RGxCR_OIE_Msk           (0x1U << DMAMUX_RGxCR_OIE_Pos)          /*!< 0x00000100 */
#define DMAMUX_RGxCR_OIE               DMAMUX_RGxCR_OIE_Msk
#define DMAMUX_RGxCR_GE_Pos            (16U)
#define DMAMUX_RGxCR_GE_Msk            (0x1U << DMAMUX_RGxCR_GE_Pos)           /*!< 0x00010000 */
#define DMAMUX_RGxCR_GE                DMAMUX_RGxCR_GE_Msk
#define DMAMUX_RGxCR_GPOL_Pos          (17U)
#define DMAMUX_RGxCR_GPOL_Msk          (0x3U << DMAMUX_RGxCR_GPOL_Pos)         /*!< 0x00060000 */
#define DMAMUX_RGxCR_GPOL              DMAMUX_RGxCR_GPOL_Msk
#define DMAMUX_RGxCR_GPOL_0            (0x1U << DMAMUX_RGxCR_GPOL_Pos)         /*!< 0x00020000 */
#define DMAMUX_RGxCR_GPOL_1            (0x2U << DMAMUX_RGxCR_GPOL_Pos)         /*!< 0x00040000 */
#define DMAMUX_RGxCR_GNBREQ_Pos        (19U)                                   
#define DMAMUX_RGxCR_GNBREQ_Msk        (0x1FU << DMAMUX_RGxCR_GNBREQ_Pos)      /*!< 0x00F80000 */
#define DMAMUX_RGxCR_GNBREQ            DMAMUX_RGxCR_GNBREQ_Msk                 /*!< Number of DMA requests to be generated */
#define DMAMUX_RGxCR_GNBREQ_0          (0x01U << DMAMUX_RGxCR_GNBREQ_Pos)      /*!< 0x00080000 */
#define DMAMUX_RGxCR_GNBREQ_1          (0x02U << DMAMUX_RGxCR_GNBREQ_Pos)      /*!< 0x00100000 */
#define DMAMUX_RGxCR_GNBREQ_2          (0x04U << DMAMUX_RGxCR_GNBREQ_Pos)      /*!< 0x00200000 */
#define DMAMUX_RGxCR_GNBREQ_3          (0x08U << DMAMUX_RGxCR_GNBREQ_Pos)      /*!< 0x00400000 */
#define DMAMUX_RGxCR_GNBREQ_4          (0x10U << DMAMUX_RGxCR_GNBREQ_Pos)      /*!< 0x00800000 */

/********************  Bits definition for DMAMUX_RGSR register  **************/
#define DMAMUX_RGSR_OF0_Pos            (0U)
#define DMAMUX_RGSR_OF0_Msk            (0x1U << DMAMUX_RGSR_OF0_Pos)           /*!< 0x00000001 */
#define DMAMUX_RGSR_OF0                DMAMUX_RGSR_OF0_Msk
#define DMAMUX_RGSR_OF1_Pos            (1U)
#define DMAMUX_RGSR_OF1_Msk            (0x1U << DMAMUX_RGSR_OF1_Pos)           /*!< 0x00000002 */
#define DMAMUX_RGSR_OF1                DMAMUX_RGSR_OF1_Msk
#define DMAMUX_RGSR_OF2_Pos            (2U)
#define DMAMUX_RGSR_OF2_Msk            (0x1U << DMAMUX_RGSR_OF2_Pos)           /*!< 0x00000004 */
#define DMAMUX_RGSR_OF2                DMAMUX_RGSR_OF2_Msk
#define DMAMUX_RGSR_OF3_Pos            (3U)
#define DMAMUX_RGSR_OF3_Msk            (0x1U << DMAMUX_RGSR_OF3_Pos)           /*!< 0x00000008 */
#define DMAMUX_RGSR_OF3                DMAMUX_RGSR_OF3_Msk
#define DMAMUX_RGSR_OF4_Pos            (4U)
#define DMAMUX_RGSR_OF4_Msk            (0x1U << DMAMUX_RGSR_OF4_Pos)           /*!< 0x00000010 */
#define DMAMUX_RGSR_OF4                DMAMUX_RGSR_OF4_Msk
#define DMAMUX_RGSR_OF5_Pos            (5U)
#define DMAMUX_RGSR_OF5_Msk            (0x1U << DMAMUX_RGSR_OF5_Pos)           /*!< 0x00000020 */
#define DMAMUX_RGSR_OF5                DMAMUX_RGSR_OF5_Msk
#define DMAMUX_RGSR_OF6_Pos            (6U)
#define DMAMUX_RGSR_OF6_Msk            (0x1U << DMAMUX_RGSR_OF6_Pos)           /*!< 0x00000040 */
#define DMAMUX_RGSR_OF6                DMAMUX_RGSR_OF6_Msk
#define DMAMUX_RGSR_OF7_Pos            (7U)
#define DMAMUX_RGSR_OF7_Msk            (0x1U << DMAMUX_RGSR_OF7_Pos)           /*!< 0x00000080 */
#define DMAMUX_RGSR_OF7                DMAMUX_RGSR_OF7_Msk

/********************  Bits definition for DMAMUX_RGCFR register  **************/
#define DMAMUX_RGCFR_COF0_Pos          (0U)
#define DMAMUX_RGCFR_COF0_Msk          (0x1U << DMAMUX_RGCFR_COF0_Pos)         /*!< 0x00000001 */
#define DMAMUX_RGCFR_COF0              DMAMUX_RGCFR_COF0_Msk
#define DMAMUX_RGCFR_COF1_Pos          (1U)
#define DMAMUX_RGCFR_COF1_Msk          (0x1U << DMAMUX_RGCFR_COF1_Pos)         /*!< 0x00000002 */
#define DMAMUX_RGCFR_COF1              DMAMUX_RGCFR_COF1_Msk
#define DMAMUX_RGCFR_COF2_Pos          (2U)
#define DMAMUX_RGCFR_COF2_Msk          (0x1U << DMAMUX_RGCFR_COF2_Pos)         /*!< 0x00000004 */
#define DMAMUX_RGCFR_COF2              DMAMUX_RGCFR_COF2_Msk
#define DMAMUX_RGCFR_COF3_Pos          (3U)
#define DMAMUX_RGCFR_COF3_Msk          (0x1U << DMAMUX_RGCFR_COF3_Pos)         /*!< 0x00000008 */
#define DMAMUX_RGCFR_COF3              DMAMUX_RGCFR_COF3_Msk
#define DMAMUX_RGCFR_COF4_Pos          (4U)
#define DMAMUX_RGCFR_COF4_Msk          (0x1U << DMAMUX_RGCFR_COF4_Pos)         /*!< 0x00000010 */
#define DMAMUX_RGCFR_COF4              DMAMUX_RGCFR_COF4_Msk
#define DMAMUX_RGCFR_COF5_Pos          (5U)
#define DMAMUX_RGCFR_COF5_Msk          (0x1U << DMAMUX_RGCFR_COF5_Pos)         /*!< 0x00000020 */
#define DMAMUX_RGCFR_COF5              DMAMUX_RGCFR_COF5_Msk
#define DMAMUX_RGCFR_COF6_Pos          (6U)
#define DMAMUX_RGCFR_COF6_Msk          (0x1U << DMAMUX_RGCFR_COF6_Pos)         /*!< 0x00000040 */
#define DMAMUX_RGCFR_COF6              DMAMUX_RGCFR_COF6_Msk
#define DMAMUX_RGCFR_COF7_Pos          (7U)
#define DMAMUX_RGCFR_COF7_Msk          (0x1U << DMAMUX_RGCFR_COF7_Pos)         /*!< 0x00000080 */
#define DMAMUX_RGCFR_COF7              DMAMUX_RGCFR_COF7_Msk

/**********************  Bit definition for DMAMUX_VERR register  *****************/
#define DMAMUX_VERR_MINREV_Pos      (0U)
#define DMAMUX_VERR_MINREV_Msk      (0xFU << DMAMUX_VERR_MINREV_Pos)               /*!< 0x0000000F */
#define DMAMUX_VERR_MINREV          DMAMUX_VERR_MINREV_Msk                         /*!< Minor Revision number */
#define DMAMUX_VERR_MAJREV_Pos      (4U)
#define DMAMUX_VERR_MAJREV_Msk      (0xFU << DMAMUX_VERR_MAJREV_Pos)               /*!< 0x000000F0 */
#define DMAMUX_VERR_MAJREV          DMAMUX_VERR_MAJREV_Msk                         /*!< Major Revision number */

/**********************  Bit definition for DMAMUX_IPIDR register  ****************/
#define DMAMUX_IPIDR_IPID_Pos       (0U)
#define DMAMUX_IPIDR_IPID_Msk       (0xFFFFFFFFU << DMAMUX_IPIDR_IPID_Pos)         /*!< 0xFFFFFFFF */
#define DMAMUX_IPIDR_IPID           DMAMUX_IPIDR_IPID_Msk                          /*!< IP Identification */

/**********************  Bit definition for DMAMUX_SIDR register  *****************/
#define DMAMUX_SIDR_SID_Pos         (0U)
#define DMAMUX_SIDR_SID_Msk         (0xFFFFFFFFU << DMAMUX_SIDR_SID_Pos)           /*!< 0xFFFFFFFF */
#define DMAMUX_SIDR_SID             DMAMUX_SIDR_SID_Msk                            /*!< IP size identification */

/******************************************************************************/
/*                                                                            */
/*                     Display Serial Interface (DSI)                         */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for DSI_VR register  *****************/
#define DSI_VR                         ((uint32_t)0x3133312AU)               /*!< DSI Host Version */

/*******************  Bit definition for DSI_CR register  *****************/
#define DSI_CR_EN                      ((uint32_t)0x00000001U)               /*!< DSI Host power up and reset */

/*******************  Bit definition for DSI_CCR register  ****************/
#define DSI_CCR_TXECKDIV               ((uint32_t)0x000000FFU)               /*!< TX Escape Clock Division */
#define DSI_CCR_TXECKDIV0              ((uint32_t)0x00000001U)
#define DSI_CCR_TXECKDIV1              ((uint32_t)0x00000002U)
#define DSI_CCR_TXECKDIV2              ((uint32_t)0x00000004U)
#define DSI_CCR_TXECKDIV3              ((uint32_t)0x00000008U)
#define DSI_CCR_TXECKDIV4              ((uint32_t)0x00000010U)
#define DSI_CCR_TXECKDIV5              ((uint32_t)0x00000020U)
#define DSI_CCR_TXECKDIV6              ((uint32_t)0x00000040U)
#define DSI_CCR_TXECKDIV7              ((uint32_t)0x00000080U)

#define DSI_CCR_TOCKDIV                ((uint32_t)0x0000FF00U)               /*!< Timeout Clock Division */
#define DSI_CCR_TOCKDIV0               ((uint32_t)0x00000100U)
#define DSI_CCR_TOCKDIV1               ((uint32_t)0x00000200U)
#define DSI_CCR_TOCKDIV2               ((uint32_t)0x00000400U)
#define DSI_CCR_TOCKDIV3               ((uint32_t)0x00000800U)
#define DSI_CCR_TOCKDIV4               ((uint32_t)0x00001000U)
#define DSI_CCR_TOCKDIV5               ((uint32_t)0x00002000U)
#define DSI_CCR_TOCKDIV6               ((uint32_t)0x00004000U)
#define DSI_CCR_TOCKDIV7               ((uint32_t)0x00008000U)

/*******************  Bit definition for DSI_LVCIDR register  *************/
#define DSI_LVCIDR_VCID                ((uint32_t)0x00000003U)               /*!< Virtual Channel ID */
#define DSI_LVCIDR_VCID0               ((uint32_t)0x00000001U)
#define DSI_LVCIDR_VCID1               ((uint32_t)0x00000002U)

/*******************  Bit definition for DSI_LCOLCR register  *************/
#define DSI_LCOLCR_COLC                ((uint32_t)0x0000000FU)               /*!< Color Coding */
#define DSI_LCOLCR_COLC0               ((uint32_t)0x00000001U)
#define DSI_LCOLCR_COLC1               ((uint32_t)0x00000002U)
#define DSI_LCOLCR_COLC2               ((uint32_t)0x00000004U)
#define DSI_LCOLCR_COLC3               ((uint32_t)0x00000008U)

#define DSI_LCOLCR_LPE                 ((uint32_t)0x00000100U)               /*!< Loosly Packet Enable */

/*******************  Bit definition for DSI_LPCR register  ***************/
#define DSI_LPCR_DEP                   ((uint32_t)0x00000001U)               /*!< Data Enable Polarity */
#define DSI_LPCR_VSP                   ((uint32_t)0x00000002U)               /*!< VSYNC Polarity */
#define DSI_LPCR_HSP                   ((uint32_t)0x00000004U)               /*!< HSYNC Polarity */

/*******************  Bit definition for DSI_LPMCR register  **************/
#define DSI_LPMCR_VLPSIZE              ((uint32_t)0x000000FFU)               /*!< VACT Largest Packet Size */
#define DSI_LPMCR_VLPSIZE0             ((uint32_t)0x00000001U)
#define DSI_LPMCR_VLPSIZE1             ((uint32_t)0x00000002U)
#define DSI_LPMCR_VLPSIZE2             ((uint32_t)0x00000004U)
#define DSI_LPMCR_VLPSIZE3             ((uint32_t)0x00000008U)
#define DSI_LPMCR_VLPSIZE4             ((uint32_t)0x00000010U)
#define DSI_LPMCR_VLPSIZE5             ((uint32_t)0x00000020U)
#define DSI_LPMCR_VLPSIZE6             ((uint32_t)0x00000040U)
#define DSI_LPMCR_VLPSIZE7             ((uint32_t)0x00000080U)

#define DSI_LPMCR_LPSIZE               ((uint32_t)0x00FF0000U)               /*!< Largest Packet Size */
#define DSI_LPMCR_LPSIZE0              ((uint32_t)0x00010000U)
#define DSI_LPMCR_LPSIZE1              ((uint32_t)0x00020000U)
#define DSI_LPMCR_LPSIZE2              ((uint32_t)0x00040000U)
#define DSI_LPMCR_LPSIZE3              ((uint32_t)0x00080000U)
#define DSI_LPMCR_LPSIZE4              ((uint32_t)0x00100000U)
#define DSI_LPMCR_LPSIZE5              ((uint32_t)0x00200000U)
#define DSI_LPMCR_LPSIZE6              ((uint32_t)0x00400000U)
#define DSI_LPMCR_LPSIZE7              ((uint32_t)0x00800000U)

/*******************  Bit definition for DSI_PCR register  ****************/
#define DSI_PCR_ETTXE                  ((uint32_t)0x00000001U)               /*!< EoTp Transmission Enable */
#define DSI_PCR_ETRXE                  ((uint32_t)0x00000002U)               /*!< EoTp Reception Enable */
#define DSI_PCR_BTAE                   ((uint32_t)0x00000004U)               /*!< Bus Turn Around Enable */
#define DSI_PCR_ECCRXE                 ((uint32_t)0x00000008U)               /*!< ECC Reception Enable */
#define DSI_PCR_CRCRXE                 ((uint32_t)0x00000010U)               /*!< CRC Reception Enable */

/*******************  Bit definition for DSI_GVCIDR register  *************/
#define DSI_GVCIDR_VCID                ((uint32_t)0x00000003U)               /*!< Virtual Channel ID */
#define DSI_GVCIDR_VCID0               ((uint32_t)0x00000001U)
#define DSI_GVCIDR_VCID1               ((uint32_t)0x00000002U)

/*******************  Bit definition for DSI_MCR register  ****************/
#define DSI_MCR_CMDM                   ((uint32_t)0x00000001U)               /*!< Command Mode */

/*******************  Bit definition for DSI_VMCR register  ***************/
#define DSI_VMCR_VMT                   ((uint32_t)0x00000003U)               /*!< Video Mode Type */
#define DSI_VMCR_VMT0                  ((uint32_t)0x00000001U)
#define DSI_VMCR_VMT1                  ((uint32_t)0x00000002U)

#define DSI_VMCR_LPVSAE                ((uint32_t)0x00000100U)               /*!< Low-Power Vertical Sync Active Enable */
#define DSI_VMCR_LPVBPE                ((uint32_t)0x00000200U)               /*!< Low-power Vertical Back-Porch Enable */
#define DSI_VMCR_LPVFPE                ((uint32_t)0x00000400U)               /*!< Low-power Vertical Front-porch Enable */
#define DSI_VMCR_LPVAE                 ((uint32_t)0x00000800U)               /*!< Low-Power Vertical Active Enable */
#define DSI_VMCR_LPHBPE                ((uint32_t)0x00001000U)               /*!< Low-Power Horizontal Back-Porch Enable */
#define DSI_VMCR_LPHFPE                ((uint32_t)0x00002000U)               /*!< Low-Power Horizontal Front-Porch Enable */
#define DSI_VMCR_FBTAAE                ((uint32_t)0x00004000U)               /*!< Frame Bus-Turn-Around Acknowledge Enable */
#define DSI_VMCR_LPCE                  ((uint32_t)0x00008000U)               /*!< Low-Power Command Enable */
#define DSI_VMCR_PGE                   ((uint32_t)0x00010000U)               /*!< Pattern Generator Enable */
#define DSI_VMCR_PGM                   ((uint32_t)0x00100000U)               /*!< Pattern Generator Mode */
#define DSI_VMCR_PGO                   ((uint32_t)0x01000000U)               /*!< Pattern Generator Orientation */

/*******************  Bit definition for DSI_VPCR register  ***************/
#define DSI_VPCR_VPSIZE                ((uint32_t)0x00003FFFU)               /*!< Video Packet Size */
#define DSI_VPCR_VPSIZE0               ((uint32_t)0x00000001U)
#define DSI_VPCR_VPSIZE1               ((uint32_t)0x00000002U)
#define DSI_VPCR_VPSIZE2               ((uint32_t)0x00000004U)
#define DSI_VPCR_VPSIZE3               ((uint32_t)0x00000008U)
#define DSI_VPCR_VPSIZE4               ((uint32_t)0x00000010U)
#define DSI_VPCR_VPSIZE5               ((uint32_t)0x00000020U)
#define DSI_VPCR_VPSIZE6               ((uint32_t)0x00000040U)
#define DSI_VPCR_VPSIZE7               ((uint32_t)0x00000080U)
#define DSI_VPCR_VPSIZE8               ((uint32_t)0x00000100U)
#define DSI_VPCR_VPSIZE9               ((uint32_t)0x00000200U)
#define DSI_VPCR_VPSIZE10              ((uint32_t)0x00000400U)
#define DSI_VPCR_VPSIZE11              ((uint32_t)0x00000800U)
#define DSI_VPCR_VPSIZE12              ((uint32_t)0x00001000U)
#define DSI_VPCR_VPSIZE13              ((uint32_t)0x00002000U)

/*******************  Bit definition for DSI_VCCR register  ***************/
#define DSI_VCCR_NUMC                  ((uint32_t)0x00001FFFU)               /*!< Number of Chunks */
#define DSI_VCCR_NUMC0                 ((uint32_t)0x00000001U)
#define DSI_VCCR_NUMC1                 ((uint32_t)0x00000002U)
#define DSI_VCCR_NUMC2                 ((uint32_t)0x00000004U)
#define DSI_VCCR_NUMC3                 ((uint32_t)0x00000008U)
#define DSI_VCCR_NUMC4                 ((uint32_t)0x00000010U)
#define DSI_VCCR_NUMC5                 ((uint32_t)0x00000020U)
#define DSI_VCCR_NUMC6                 ((uint32_t)0x00000040U)
#define DSI_VCCR_NUMC7                 ((uint32_t)0x00000080U)
#define DSI_VCCR_NUMC8                 ((uint32_t)0x00000100U)
#define DSI_VCCR_NUMC9                 ((uint32_t)0x00000200U)
#define DSI_VCCR_NUMC10                ((uint32_t)0x00000400U)
#define DSI_VCCR_NUMC11                ((uint32_t)0x00000800U)
#define DSI_VCCR_NUMC12                ((uint32_t)0x00001000U)

/*******************  Bit definition for DSI_VNPCR register  **************/
#define DSI_VNPCR_NPSIZE               ((uint32_t)0x00001FFFU)               /*!< Null Packet Size */
#define DSI_VNPCR_NPSIZE0              ((uint32_t)0x00000001U)
#define DSI_VNPCR_NPSIZE1              ((uint32_t)0x00000002U)
#define DSI_VNPCR_NPSIZE2              ((uint32_t)0x00000004U)
#define DSI_VNPCR_NPSIZE3              ((uint32_t)0x00000008U)
#define DSI_VNPCR_NPSIZE4              ((uint32_t)0x00000010U)
#define DSI_VNPCR_NPSIZE5              ((uint32_t)0x00000020U)
#define DSI_VNPCR_NPSIZE6              ((uint32_t)0x00000040U)
#define DSI_VNPCR_NPSIZE7              ((uint32_t)0x00000080U)
#define DSI_VNPCR_NPSIZE8              ((uint32_t)0x00000100U)
#define DSI_VNPCR_NPSIZE9              ((uint32_t)0x00000200U)
#define DSI_VNPCR_NPSIZE10             ((uint32_t)0x00000400U)
#define DSI_VNPCR_NPSIZE11             ((uint32_t)0x00000800U)
#define DSI_VNPCR_NPSIZE12             ((uint32_t)0x00001000U)

/*******************  Bit definition for DSI_VHSACR register  *************/
#define DSI_VHSACR_HSA                 ((uint32_t)0x00000FFFU)               /*!< Horizontal Synchronism Active duration */
#define DSI_VHSACR_HSA0                ((uint32_t)0x00000001U)
#define DSI_VHSACR_HSA1                ((uint32_t)0x00000002U)
#define DSI_VHSACR_HSA2                ((uint32_t)0x00000004U)
#define DSI_VHSACR_HSA3                ((uint32_t)0x00000008U)
#define DSI_VHSACR_HSA4                ((uint32_t)0x00000010U)
#define DSI_VHSACR_HSA5                ((uint32_t)0x00000020U)
#define DSI_VHSACR_HSA6                ((uint32_t)0x00000040U)
#define DSI_VHSACR_HSA7                ((uint32_t)0x00000080U)
#define DSI_VHSACR_HSA8                ((uint32_t)0x00000100U)
#define DSI_VHSACR_HSA9                ((uint32_t)0x00000200U)
#define DSI_VHSACR_HSA10               ((uint32_t)0x00000400U)
#define DSI_VHSACR_HSA11               ((uint32_t)0x00000800U)

/*******************  Bit definition for DSI_VHBPCR register  *************/
#define DSI_VHBPCR_HBP                 ((uint32_t)0x00000FFFU)               /*!< Horizontal Back-Porch duration */
#define DSI_VHBPCR_HBP0                ((uint32_t)0x00000001U)
#define DSI_VHBPCR_HBP1                ((uint32_t)0x00000002U)
#define DSI_VHBPCR_HBP2                ((uint32_t)0x00000004U)
#define DSI_VHBPCR_HBP3                ((uint32_t)0x00000008U)
#define DSI_VHBPCR_HBP4                ((uint32_t)0x00000010U)
#define DSI_VHBPCR_HBP5                ((uint32_t)0x00000020U)
#define DSI_VHBPCR_HBP6                ((uint32_t)0x00000040U)
#define DSI_VHBPCR_HBP7                ((uint32_t)0x00000080U)
#define DSI_VHBPCR_HBP8                ((uint32_t)0x00000100U)
#define DSI_VHBPCR_HBP9                ((uint32_t)0x00000200U)
#define DSI_VHBPCR_HBP10               ((uint32_t)0x00000400U)
#define DSI_VHBPCR_HBP11               ((uint32_t)0x00000800U)

/*******************  Bit definition for DSI_VLCR register  ***************/
#define DSI_VLCR_HLINE                 ((uint32_t)0x00007FFFU)               /*!< Horizontal Line duration */
#define DSI_VLCR_HLINE0                ((uint32_t)0x00000001U)
#define DSI_VLCR_HLINE1                ((uint32_t)0x00000002U)
#define DSI_VLCR_HLINE2                ((uint32_t)0x00000004U)
#define DSI_VLCR_HLINE3                ((uint32_t)0x00000008U)
#define DSI_VLCR_HLINE4                ((uint32_t)0x00000010U)
#define DSI_VLCR_HLINE5                ((uint32_t)0x00000020U)
#define DSI_VLCR_HLINE6                ((uint32_t)0x00000040U)
#define DSI_VLCR_HLINE7                ((uint32_t)0x00000080U)
#define DSI_VLCR_HLINE8                ((uint32_t)0x00000100U)
#define DSI_VLCR_HLINE9                ((uint32_t)0x00000200U)
#define DSI_VLCR_HLINE10               ((uint32_t)0x00000400U)
#define DSI_VLCR_HLINE11               ((uint32_t)0x00000800U)
#define DSI_VLCR_HLINE12               ((uint32_t)0x00001000U)
#define DSI_VLCR_HLINE13               ((uint32_t)0x00002000U)
#define DSI_VLCR_HLINE14               ((uint32_t)0x00004000U)

/*******************  Bit definition for DSI_VVSACR register  *************/
#define DSI_VVSACR_VSA                 ((uint32_t)0x000003FFU)               /*!< Vertical Synchronism Active duration */
#define DSI_VVSACR_VSA0                ((uint32_t)0x00000001U)
#define DSI_VVSACR_VSA1                ((uint32_t)0x00000002U)
#define DSI_VVSACR_VSA2                ((uint32_t)0x00000004U)
#define DSI_VVSACR_VSA3                ((uint32_t)0x00000008U)
#define DSI_VVSACR_VSA4                ((uint32_t)0x00000010U)
#define DSI_VVSACR_VSA5                ((uint32_t)0x00000020U)
#define DSI_VVSACR_VSA6                ((uint32_t)0x00000040U)
#define DSI_VVSACR_VSA7                ((uint32_t)0x00000080U)
#define DSI_VVSACR_VSA8                ((uint32_t)0x00000100U)
#define DSI_VVSACR_VSA9                ((uint32_t)0x00000200U)

/*******************  Bit definition for DSI_VVBPCR register  *************/
#define DSI_VVBPCR_VBP                 ((uint32_t)0x000003FFU)               /*!< Vertical Back-Porch duration */
#define DSI_VVBPCR_VBP0                ((uint32_t)0x00000001U)
#define DSI_VVBPCR_VBP1                ((uint32_t)0x00000002U)
#define DSI_VVBPCR_VBP2                ((uint32_t)0x00000004U)
#define DSI_VVBPCR_VBP3                ((uint32_t)0x00000008U)
#define DSI_VVBPCR_VBP4                ((uint32_t)0x00000010U)
#define DSI_VVBPCR_VBP5                ((uint32_t)0x00000020U)
#define DSI_VVBPCR_VBP6                ((uint32_t)0x00000040U)
#define DSI_VVBPCR_VBP7                ((uint32_t)0x00000080U)
#define DSI_VVBPCR_VBP8                ((uint32_t)0x00000100U)
#define DSI_VVBPCR_VBP9                ((uint32_t)0x00000200U)

/*******************  Bit definition for DSI_VVFPCR register  *************/
#define DSI_VVFPCR_VFP                 ((uint32_t)0x000003FFU)               /*!< Vertical Front-Porch duration */
#define DSI_VVFPCR_VFP0                ((uint32_t)0x00000001U)
#define DSI_VVFPCR_VFP1                ((uint32_t)0x00000002U)
#define DSI_VVFPCR_VFP2                ((uint32_t)0x00000004U)
#define DSI_VVFPCR_VFP3                ((uint32_t)0x00000008U)
#define DSI_VVFPCR_VFP4                ((uint32_t)0x00000010U)
#define DSI_VVFPCR_VFP5                ((uint32_t)0x00000020U)
#define DSI_VVFPCR_VFP6                ((uint32_t)0x00000040U)
#define DSI_VVFPCR_VFP7                ((uint32_t)0x00000080U)
#define DSI_VVFPCR_VFP8                ((uint32_t)0x00000100U)
#define DSI_VVFPCR_VFP9                ((uint32_t)0x00000200U)

/*******************  Bit definition for DSI_VVACR register  **************/
#define DSI_VVACR_VA                   ((uint32_t)0x00003FFFU)               /*!< Vertical Active duration */
#define DSI_VVACR_VA0                  ((uint32_t)0x00000001U)
#define DSI_VVACR_VA1                  ((uint32_t)0x00000002U)
#define DSI_VVACR_VA2                  ((uint32_t)0x00000004U)
#define DSI_VVACR_VA3                  ((uint32_t)0x00000008U)
#define DSI_VVACR_VA4                  ((uint32_t)0x00000010U)
#define DSI_VVACR_VA5                  ((uint32_t)0x00000020U)
#define DSI_VVACR_VA6                  ((uint32_t)0x00000040U)
#define DSI_VVACR_VA7                  ((uint32_t)0x00000080U)
#define DSI_VVACR_VA8                  ((uint32_t)0x00000100U)
#define DSI_VVACR_VA9                  ((uint32_t)0x00000200U)
#define DSI_VVACR_VA10                 ((uint32_t)0x00000400U)
#define DSI_VVACR_VA11                 ((uint32_t)0x00000800U)
#define DSI_VVACR_VA12                 ((uint32_t)0x00001000U)
#define DSI_VVACR_VA13                 ((uint32_t)0x00002000U)

/*******************  Bit definition for DSI_LCCR register  ***************/
#define DSI_LCCR_CMDSIZE               ((uint32_t)0x0000FFFFU)               /*!< Command Size */
#define DSI_LCCR_CMDSIZE0              ((uint32_t)0x00000001U)
#define DSI_LCCR_CMDSIZE1              ((uint32_t)0x00000002U)
#define DSI_LCCR_CMDSIZE2              ((uint32_t)0x00000004U)
#define DSI_LCCR_CMDSIZE3              ((uint32_t)0x00000008U)
#define DSI_LCCR_CMDSIZE4              ((uint32_t)0x00000010U)
#define DSI_LCCR_CMDSIZE5              ((uint32_t)0x00000020U)
#define DSI_LCCR_CMDSIZE6              ((uint32_t)0x00000040U)
#define DSI_LCCR_CMDSIZE7              ((uint32_t)0x00000080U)
#define DSI_LCCR_CMDSIZE8              ((uint32_t)0x00000100U)
#define DSI_LCCR_CMDSIZE9              ((uint32_t)0x00000200U)
#define DSI_LCCR_CMDSIZE10             ((uint32_t)0x00000400U)
#define DSI_LCCR_CMDSIZE11             ((uint32_t)0x00000800U)
#define DSI_LCCR_CMDSIZE12             ((uint32_t)0x00001000U)
#define DSI_LCCR_CMDSIZE13             ((uint32_t)0x00002000U)
#define DSI_LCCR_CMDSIZE14             ((uint32_t)0x00004000U)
#define DSI_LCCR_CMDSIZE15             ((uint32_t)0x00008000U)

/*******************  Bit definition for DSI_CMCR register  ***************/
#define DSI_CMCR_TEARE                 ((uint32_t)0x00000001U)               /*!< Tearing Effect Acknowledge Request Enable */
#define DSI_CMCR_ARE                   ((uint32_t)0x00000002U)               /*!< Acknowledge Request Enable */
#define DSI_CMCR_GSW0TX                ((uint32_t)0x00000100U)               /*!< Generic Short Write Zero parameters Transmission */
#define DSI_CMCR_GSW1TX                ((uint32_t)0x00000200U)               /*!< Generic Short Write One parameters Transmission */
#define DSI_CMCR_GSW2TX                ((uint32_t)0x00000400U)               /*!< Generic Short Write Two parameters Transmission */
#define DSI_CMCR_GSR0TX                ((uint32_t)0x00000800U)               /*!< Generic Short Read Zero parameters Transmission */
#define DSI_CMCR_GSR1TX                ((uint32_t)0x00001000U)               /*!< Generic Short Read One parameters Transmission */
#define DSI_CMCR_GSR2TX                ((uint32_t)0x00002000U)               /*!< Generic Short Read Two parameters Transmission */
#define DSI_CMCR_GLWTX                 ((uint32_t)0x00004000U)               /*!< Generic Long Write Transmission */
#define DSI_CMCR_DSW0TX                ((uint32_t)0x00010000U)               /*!< DCS Short Write Zero parameter Transmission */
#define DSI_CMCR_DSW1TX                ((uint32_t)0x00020000U)               /*!< DCS Short Read One parameter Transmission */
#define DSI_CMCR_DSR0TX                ((uint32_t)0x00040000U)               /*!< DCS Short Read Zero parameter Transmission */
#define DSI_CMCR_DLWTX                 ((uint32_t)0x00080000U)               /*!< DCS Long Write Transmission */
#define DSI_CMCR_MRDPS                 ((uint32_t)0x01000000U)               /*!< Maximum Read Packet Size */

/*******************  Bit definition for DSI_GHCR register  ***************/
#define DSI_GHCR_DT                    ((uint32_t)0x0000003FU)               /*!< Type */
#define DSI_GHCR_DT0                   ((uint32_t)0x00000001U)
#define DSI_GHCR_DT1                   ((uint32_t)0x00000002U)
#define DSI_GHCR_DT2                   ((uint32_t)0x00000004U)
#define DSI_GHCR_DT3                   ((uint32_t)0x00000008U)
#define DSI_GHCR_DT4                   ((uint32_t)0x00000010U)
#define DSI_GHCR_DT5                   ((uint32_t)0x00000020U)

#define DSI_GHCR_VCID                  ((uint32_t)0x000000C0U)               /*!< Channel */
#define DSI_GHCR_VCID0                 ((uint32_t)0x00000040U)
#define DSI_GHCR_VCID1                 ((uint32_t)0x00000080U)

#define DSI_GHCR_WCLSB                 ((uint32_t)0x0000FF00U)               /*!< WordCount LSB */
#define DSI_GHCR_WCLSB0                ((uint32_t)0x00000100U)
#define DSI_GHCR_WCLSB1                ((uint32_t)0x00000200U)
#define DSI_GHCR_WCLSB2                ((uint32_t)0x00000400U)
#define DSI_GHCR_WCLSB3                ((uint32_t)0x00000800U)
#define DSI_GHCR_WCLSB4                ((uint32_t)0x00001000U)
#define DSI_GHCR_WCLSB5                ((uint32_t)0x00002000U)
#define DSI_GHCR_WCLSB6                ((uint32_t)0x00004000U)
#define DSI_GHCR_WCLSB7                ((uint32_t)0x00008000U)

#define DSI_GHCR_WCMSB                 ((uint32_t)0x00FF0000U)               /*!< WordCount MSB */
#define DSI_GHCR_WCMSB0                ((uint32_t)0x00010000U)
#define DSI_GHCR_WCMSB1                ((uint32_t)0x00020000U)
#define DSI_GHCR_WCMSB2                ((uint32_t)0x00040000U)
#define DSI_GHCR_WCMSB3                ((uint32_t)0x00080000U)
#define DSI_GHCR_WCMSB4                ((uint32_t)0x00100000U)
#define DSI_GHCR_WCMSB5                ((uint32_t)0x00200000U)
#define DSI_GHCR_WCMSB6                ((uint32_t)0x00400000U)
#define DSI_GHCR_WCMSB7                ((uint32_t)0x00800000U)

/*******************  Bit definition for DSI_GPDR register  ***************/
#define DSI_GPDR_DATA1                 ((uint32_t)0x000000FFU)               /*!< Payload Byte 1 */
#define DSI_GPDR_DATA1_0               ((uint32_t)0x00000001U)
#define DSI_GPDR_DATA1_1               ((uint32_t)0x00000002U)
#define DSI_GPDR_DATA1_2               ((uint32_t)0x00000004U)
#define DSI_GPDR_DATA1_3               ((uint32_t)0x00000008U)
#define DSI_GPDR_DATA1_4               ((uint32_t)0x00000010U)
#define DSI_GPDR_DATA1_5               ((uint32_t)0x00000020U)
#define DSI_GPDR_DATA1_6               ((uint32_t)0x00000040U)
#define DSI_GPDR_DATA1_7               ((uint32_t)0x00000080U)

#define DSI_GPDR_DATA2                 ((uint32_t)0x0000FF00U)               /*!< Payload Byte 2 */
#define DSI_GPDR_DATA2_0               ((uint32_t)0x00000100U)
#define DSI_GPDR_DATA2_1               ((uint32_t)0x00000200U)
#define DSI_GPDR_DATA2_2               ((uint32_t)0x00000400U)
#define DSI_GPDR_DATA2_3               ((uint32_t)0x00000800U)
#define DSI_GPDR_DATA2_4               ((uint32_t)0x00001000U)
#define DSI_GPDR_DATA2_5               ((uint32_t)0x00002000U)
#define DSI_GPDR_DATA2_6               ((uint32_t)0x00004000U)
#define DSI_GPDR_DATA2_7               ((uint32_t)0x00008000U)

#define DSI_GPDR_DATA3                 ((uint32_t)0x00FF0000U)               /*!< Payload Byte 3 */
#define DSI_GPDR_DATA3_0               ((uint32_t)0x00010000U)
#define DSI_GPDR_DATA3_1               ((uint32_t)0x00020000U)
#define DSI_GPDR_DATA3_2               ((uint32_t)0x00040000U)
#define DSI_GPDR_DATA3_3               ((uint32_t)0x00080000U)
#define DSI_GPDR_DATA3_4               ((uint32_t)0x00100000U)
#define DSI_GPDR_DATA3_5               ((uint32_t)0x00200000U)
#define DSI_GPDR_DATA3_6               ((uint32_t)0x00400000U)
#define DSI_GPDR_DATA3_7               ((uint32_t)0x00800000U)

#define DSI_GPDR_DATA4                 ((uint32_t)0xFF000000U)               /*!< Payload Byte 4 */
#define DSI_GPDR_DATA4_0               ((uint32_t)0x01000000U)
#define DSI_GPDR_DATA4_1               ((uint32_t)0x02000000U)
#define DSI_GPDR_DATA4_2               ((uint32_t)0x04000000U)
#define DSI_GPDR_DATA4_3               ((uint32_t)0x08000000U)
#define DSI_GPDR_DATA4_4               ((uint32_t)0x10000000U)
#define DSI_GPDR_DATA4_5               ((uint32_t)0x20000000U)
#define DSI_GPDR_DATA4_6               ((uint32_t)0x40000000U)
#define DSI_GPDR_DATA4_7               ((uint32_t)0x80000000U)

/*******************  Bit definition for DSI_GPSR register  ***************/
#define DSI_GPSR_CMDFE                 ((uint32_t)0x00000001U)               /*!< Command FIFO Empty */
#define DSI_GPSR_CMDFF                 ((uint32_t)0x00000002U)               /*!< Command FIFO Full */
#define DSI_GPSR_PWRFE                 ((uint32_t)0x00000004U)               /*!< Payload Write FIFO Empty */
#define DSI_GPSR_PWRFF                 ((uint32_t)0x00000008U)               /*!< Payload Write FIFO Full */
#define DSI_GPSR_PRDFE                 ((uint32_t)0x00000010U)               /*!< Payload Read FIFO Empty */
#define DSI_GPSR_PRDFF                 ((uint32_t)0x00000020U)               /*!< Payload Read FIFO Full */
#define DSI_GPSR_RCB                   ((uint32_t)0x00000040U)               /*!< Read Command Busy */

/*******************  Bit definition for DSI_TCCR0 register  **************/
#define DSI_TCCR0_LPRX_TOCNT           ((uint32_t)0x0000FFFFU)               /*!< Low-power Reception Timeout Counter */
#define DSI_TCCR0_LPRX_TOCNT0          ((uint32_t)0x00000001U)
#define DSI_TCCR0_LPRX_TOCNT1          ((uint32_t)0x00000002U)
#define DSI_TCCR0_LPRX_TOCNT2          ((uint32_t)0x00000004U)
#define DSI_TCCR0_LPRX_TOCNT3          ((uint32_t)0x00000008U)
#define DSI_TCCR0_LPRX_TOCNT4          ((uint32_t)0x00000010U)
#define DSI_TCCR0_LPRX_TOCNT5          ((uint32_t)0x00000020U)
#define DSI_TCCR0_LPRX_TOCNT6          ((uint32_t)0x00000040U)
#define DSI_TCCR0_LPRX_TOCNT7          ((uint32_t)0x00000080U)
#define DSI_TCCR0_LPRX_TOCNT8          ((uint32_t)0x00000100U)
#define DSI_TCCR0_LPRX_TOCNT9          ((uint32_t)0x00000200U)
#define DSI_TCCR0_LPRX_TOCNT10         ((uint32_t)0x00000400U)
#define DSI_TCCR0_LPRX_TOCNT11         ((uint32_t)0x00000800U)
#define DSI_TCCR0_LPRX_TOCNT12         ((uint32_t)0x00001000U)
#define DSI_TCCR0_LPRX_TOCNT13         ((uint32_t)0x00002000U)
#define DSI_TCCR0_LPRX_TOCNT14         ((uint32_t)0x00004000U)
#define DSI_TCCR0_LPRX_TOCNT15         ((uint32_t)0x00008000U)

#define DSI_TCCR0_HSTX_TOCNT           ((uint32_t)0xFFFF0000U)               /*!< High-Speed Transmission Timeout Counter */
#define DSI_TCCR0_HSTX_TOCNT0          ((uint32_t)0x00010000U)
#define DSI_TCCR0_HSTX_TOCNT1          ((uint32_t)0x00020000U)
#define DSI_TCCR0_HSTX_TOCNT2          ((uint32_t)0x00040000U)
#define DSI_TCCR0_HSTX_TOCNT3          ((uint32_t)0x00080000U)
#define DSI_TCCR0_HSTX_TOCNT4          ((uint32_t)0x00100000U)
#define DSI_TCCR0_HSTX_TOCNT5          ((uint32_t)0x00200000U)
#define DSI_TCCR0_HSTX_TOCNT6          ((uint32_t)0x00400000U)
#define DSI_TCCR0_HSTX_TOCNT7          ((uint32_t)0x00800000U)
#define DSI_TCCR0_HSTX_TOCNT8          ((uint32_t)0x01000000U)
#define DSI_TCCR0_HSTX_TOCNT9          ((uint32_t)0x02000000U)
#define DSI_TCCR0_HSTX_TOCNT10         ((uint32_t)0x04000000U)
#define DSI_TCCR0_HSTX_TOCNT11         ((uint32_t)0x08000000U)
#define DSI_TCCR0_HSTX_TOCNT12         ((uint32_t)0x10000000U)
#define DSI_TCCR0_HSTX_TOCNT13         ((uint32_t)0x20000000U)
#define DSI_TCCR0_HSTX_TOCNT14         ((uint32_t)0x40000000U)
#define DSI_TCCR0_HSTX_TOCNT15         ((uint32_t)0x80000000U)

/*******************  Bit definition for DSI_TCCR1 register  **************/
#define DSI_TCCR1_HSRD_TOCNT           ((uint32_t)0x0000FFFFU)               /*!< High-Speed Read Timeout Counter */
#define DSI_TCCR1_HSRD_TOCNT0          ((uint32_t)0x00000001U)
#define DSI_TCCR1_HSRD_TOCNT1          ((uint32_t)0x00000002U)
#define DSI_TCCR1_HSRD_TOCNT2          ((uint32_t)0x00000004U)
#define DSI_TCCR1_HSRD_TOCNT3          ((uint32_t)0x00000008U)
#define DSI_TCCR1_HSRD_TOCNT4          ((uint32_t)0x00000010U)
#define DSI_TCCR1_HSRD_TOCNT5          ((uint32_t)0x00000020U)
#define DSI_TCCR1_HSRD_TOCNT6          ((uint32_t)0x00000040U)
#define DSI_TCCR1_HSRD_TOCNT7          ((uint32_t)0x00000080U)
#define DSI_TCCR1_HSRD_TOCNT8          ((uint32_t)0x00000100U)
#define DSI_TCCR1_HSRD_TOCNT9          ((uint32_t)0x00000200U)
#define DSI_TCCR1_HSRD_TOCNT10         ((uint32_t)0x00000400U)
#define DSI_TCCR1_HSRD_TOCNT11         ((uint32_t)0x00000800U)
#define DSI_TCCR1_HSRD_TOCNT12         ((uint32_t)0x00001000U)
#define DSI_TCCR1_HSRD_TOCNT13         ((uint32_t)0x00002000U)
#define DSI_TCCR1_HSRD_TOCNT14         ((uint32_t)0x00004000U)
#define DSI_TCCR1_HSRD_TOCNT15         ((uint32_t)0x00008000U)

/*******************  Bit definition for DSI_TCCR2 register  **************/
#define DSI_TCCR2_LPRD_TOCNT           ((uint32_t)0x0000FFFFU)               /*!< Low-Power Read Timeout Counter */
#define DSI_TCCR2_LPRD_TOCNT0          ((uint32_t)0x00000001U)
#define DSI_TCCR2_LPRD_TOCNT1          ((uint32_t)0x00000002U)
#define DSI_TCCR2_LPRD_TOCNT2          ((uint32_t)0x00000004U)
#define DSI_TCCR2_LPRD_TOCNT3          ((uint32_t)0x00000008U)
#define DSI_TCCR2_LPRD_TOCNT4          ((uint32_t)0x00000010U)
#define DSI_TCCR2_LPRD_TOCNT5          ((uint32_t)0x00000020U)
#define DSI_TCCR2_LPRD_TOCNT6          ((uint32_t)0x00000040U)
#define DSI_TCCR2_LPRD_TOCNT7          ((uint32_t)0x00000080U)
#define DSI_TCCR2_LPRD_TOCNT8          ((uint32_t)0x00000100U)
#define DSI_TCCR2_LPRD_TOCNT9          ((uint32_t)0x00000200U)
#define DSI_TCCR2_LPRD_TOCNT10         ((uint32_t)0x00000400U)
#define DSI_TCCR2_LPRD_TOCNT11         ((uint32_t)0x00000800U)
#define DSI_TCCR2_LPRD_TOCNT12         ((uint32_t)0x00001000U)
#define DSI_TCCR2_LPRD_TOCNT13         ((uint32_t)0x00002000U)
#define DSI_TCCR2_LPRD_TOCNT14         ((uint32_t)0x00004000U)
#define DSI_TCCR2_LPRD_TOCNT15         ((uint32_t)0x00008000U)

/*******************  Bit definition for DSI_TCCR3 register  **************/
#define DSI_TCCR3_HSWR_TOCNT           ((uint32_t)0x0000FFFFU)               /*!< High-Speed Write Timeout Counter */
#define DSI_TCCR3_HSWR_TOCNT0          ((uint32_t)0x00000001U)
#define DSI_TCCR3_HSWR_TOCNT1          ((uint32_t)0x00000002U)
#define DSI_TCCR3_HSWR_TOCNT2          ((uint32_t)0x00000004U)
#define DSI_TCCR3_HSWR_TOCNT3          ((uint32_t)0x00000008U)
#define DSI_TCCR3_HSWR_TOCNT4          ((uint32_t)0x00000010U)
#define DSI_TCCR3_HSWR_TOCNT5          ((uint32_t)0x00000020U)
#define DSI_TCCR3_HSWR_TOCNT6          ((uint32_t)0x00000040U)
#define DSI_TCCR3_HSWR_TOCNT7          ((uint32_t)0x00000080U)
#define DSI_TCCR3_HSWR_TOCNT8          ((uint32_t)0x00000100U)
#define DSI_TCCR3_HSWR_TOCNT9          ((uint32_t)0x00000200U)
#define DSI_TCCR3_HSWR_TOCNT10         ((uint32_t)0x00000400U)
#define DSI_TCCR3_HSWR_TOCNT11         ((uint32_t)0x00000800U)
#define DSI_TCCR3_HSWR_TOCNT12         ((uint32_t)0x00001000U)
#define DSI_TCCR3_HSWR_TOCNT13         ((uint32_t)0x00002000U)
#define DSI_TCCR3_HSWR_TOCNT14         ((uint32_t)0x00004000U)
#define DSI_TCCR3_HSWR_TOCNT15         ((uint32_t)0x00008000U)

#define DSI_TCCR3_PM                   ((uint32_t)0x01000000U)               /*!< Presp Mode */

/*******************  Bit definition for DSI_TCCR4 register  **************/
#define DSI_TCCR4_LPWR_TOCNT           ((uint32_t)0x0000FFFFU)               /*!< Low-Power Write Timeout Counter */
#define DSI_TCCR4_LPWR_TOCNT0          ((uint32_t)0x00000001U)
#define DSI_TCCR4_LPWR_TOCNT1          ((uint32_t)0x00000002U)
#define DSI_TCCR4_LPWR_TOCNT2          ((uint32_t)0x00000004U)
#define DSI_TCCR4_LPWR_TOCNT3          ((uint32_t)0x00000008U)
#define DSI_TCCR4_LPWR_TOCNT4          ((uint32_t)0x00000010U)
#define DSI_TCCR4_LPWR_TOCNT5          ((uint32_t)0x00000020U)
#define DSI_TCCR4_LPWR_TOCNT6          ((uint32_t)0x00000040U)
#define DSI_TCCR4_LPWR_TOCNT7          ((uint32_t)0x00000080U)
#define DSI_TCCR4_LPWR_TOCNT8          ((uint32_t)0x00000100U)
#define DSI_TCCR4_LPWR_TOCNT9          ((uint32_t)0x00000200U)
#define DSI_TCCR4_LPWR_TOCNT10         ((uint32_t)0x00000400U)
#define DSI_TCCR4_LPWR_TOCNT11         ((uint32_t)0x00000800U)
#define DSI_TCCR4_LPWR_TOCNT12         ((uint32_t)0x00001000U)
#define DSI_TCCR4_LPWR_TOCNT13         ((uint32_t)0x00002000U)
#define DSI_TCCR4_LPWR_TOCNT14         ((uint32_t)0x00004000U)
#define DSI_TCCR4_LPWR_TOCNT15         ((uint32_t)0x00008000U)

/*******************  Bit definition for DSI_TCCR5 register  **************/
#define DSI_TCCR5_BTA_TOCNT            ((uint32_t)0x0000FFFFU)               /*!< Bus-Turn-Around Timeout Counter */
#define DSI_TCCR5_BTA_TOCNT0           ((uint32_t)0x00000001U)
#define DSI_TCCR5_BTA_TOCNT1           ((uint32_t)0x00000002U)
#define DSI_TCCR5_BTA_TOCNT2           ((uint32_t)0x00000004U)
#define DSI_TCCR5_BTA_TOCNT3           ((uint32_t)0x00000008U)
#define DSI_TCCR5_BTA_TOCNT4           ((uint32_t)0x00000010U)
#define DSI_TCCR5_BTA_TOCNT5           ((uint32_t)0x00000020U)
#define DSI_TCCR5_BTA_TOCNT6           ((uint32_t)0x00000040U)
#define DSI_TCCR5_BTA_TOCNT7           ((uint32_t)0x00000080U)
#define DSI_TCCR5_BTA_TOCNT8           ((uint32_t)0x00000100U)
#define DSI_TCCR5_BTA_TOCNT9           ((uint32_t)0x00000200U)
#define DSI_TCCR5_BTA_TOCNT10          ((uint32_t)0x00000400U)
#define DSI_TCCR5_BTA_TOCNT11          ((uint32_t)0x00000800U)
#define DSI_TCCR5_BTA_TOCNT12          ((uint32_t)0x00001000U)
#define DSI_TCCR5_BTA_TOCNT13          ((uint32_t)0x00002000U)
#define DSI_TCCR5_BTA_TOCNT14          ((uint32_t)0x00004000U)
#define DSI_TCCR5_BTA_TOCNT15          ((uint32_t)0x00008000U)

/*******************  Bit definition for DSI_TDCR register  ***************/
#define DSI_TDCR_3DM                   ((uint32_t)0x00000003U)               /*!< 3D Mode */
#define DSI_TDCR_3DM0                  ((uint32_t)0x00000001U)
#define DSI_TDCR_3DM1                  ((uint32_t)0x00000002U)

#define DSI_TDCR_3DF                   ((uint32_t)0x0000000CU)               /*!< 3D Format */
#define DSI_TDCR_3DF0                  ((uint32_t)0x00000004U)
#define DSI_TDCR_3DF1                  ((uint32_t)0x00000008U)

#define DSI_TDCR_SVS                   ((uint32_t)0x00000010U)               /*!< Second VSYNC */
#define DSI_TDCR_RF                    ((uint32_t)0x00000020U)               /*!< Right First */
#define DSI_TDCR_S3DC                  ((uint32_t)0x00010000U)               /*!< Send 3D Control */

/*******************  Bit definition for DSI_CLCR register  ***************/
#define DSI_CLCR_DPCC                  ((uint32_t)0x00000001U)               /*!< D-PHY Clock Control */
#define DSI_CLCR_ACR                   ((uint32_t)0x00000002U)               /*!< Automatic Clocklane Control */

/*******************  Bit definition for DSI_CLTCR register  **************/
#define DSI_CLTCR_LP2HS_TIME           ((uint32_t)0x000003FFU)               /*!< Low-Power to High-Speed Time */
#define DSI_CLTCR_LP2HS_TIME0          ((uint32_t)0x00000001U)
#define DSI_CLTCR_LP2HS_TIME1          ((uint32_t)0x00000002U)
#define DSI_CLTCR_LP2HS_TIME2          ((uint32_t)0x00000004U)
#define DSI_CLTCR_LP2HS_TIME3          ((uint32_t)0x00000008U)
#define DSI_CLTCR_LP2HS_TIME4          ((uint32_t)0x00000010U)
#define DSI_CLTCR_LP2HS_TIME5          ((uint32_t)0x00000020U)
#define DSI_CLTCR_LP2HS_TIME6          ((uint32_t)0x00000040U)
#define DSI_CLTCR_LP2HS_TIME7          ((uint32_t)0x00000080U)
#define DSI_CLTCR_LP2HS_TIME8          ((uint32_t)0x00000100U)
#define DSI_CLTCR_LP2HS_TIME9          ((uint32_t)0x00000200U)

#define DSI_CLTCR_HS2LP_TIME           ((uint32_t)0x03FF0000U)               /*!< High-Speed to Low-Power Time */
#define DSI_CLTCR_HS2LP_TIME0          ((uint32_t)0x00010000U)
#define DSI_CLTCR_HS2LP_TIME1          ((uint32_t)0x00020000U)
#define DSI_CLTCR_HS2LP_TIME2          ((uint32_t)0x00040000U)
#define DSI_CLTCR_HS2LP_TIME3          ((uint32_t)0x00080000U)
#define DSI_CLTCR_HS2LP_TIME4          ((uint32_t)0x00100000U)
#define DSI_CLTCR_HS2LP_TIME5          ((uint32_t)0x00200000U)
#define DSI_CLTCR_HS2LP_TIME6          ((uint32_t)0x00400000U)
#define DSI_CLTCR_HS2LP_TIME7          ((uint32_t)0x00800000U)
#define DSI_CLTCR_HS2LP_TIME8          ((uint32_t)0x01000000U)
#define DSI_CLTCR_HS2LP_TIME9          ((uint32_t)0x02000000U)

/*******************  Bit definition for DSI_DLTCR register  **************/
#define DSI_DLTCR_LP2HS_TIME           ((uint32_t)0x000003FFU)               /*!< Low-Power to High-Speed Time */
#define DSI_DLTCR_LP2HS_TIME0          ((uint32_t)0x00000001U)
#define DSI_DLTCR_LP2HS_TIME1          ((uint32_t)0x00000002U)
#define DSI_DLTCR_LP2HS_TIME2          ((uint32_t)0x00000004U)
#define DSI_DLTCR_LP2HS_TIME3          ((uint32_t)0x00000008U)
#define DSI_DLTCR_LP2HS_TIME4          ((uint32_t)0x00000010U)
#define DSI_DLTCR_LP2HS_TIME5          ((uint32_t)0x00000020U)
#define DSI_DLTCR_LP2HS_TIME6          ((uint32_t)0x00000040U)
#define DSI_DLTCR_LP2HS_TIME7          ((uint32_t)0x00000080U)
#define DSI_DLTCR_LP2HS_TIME8          ((uint32_t)0x00000100U)
#define DSI_DLTCR_LP2HS_TIME9          ((uint32_t)0x00000200U)

#define DSI_DLTCR_HS2LP_TIME           ((uint32_t)0x03FF0000U)               /*!< High-Speed to Low-Power Time */
#define DSI_DLTCR_HS2LP_TIME0          ((uint32_t)0x00010000U)
#define DSI_DLTCR_HS2LP_TIME1          ((uint32_t)0x00020000U)
#define DSI_DLTCR_HS2LP_TIME2          ((uint32_t)0x00040000U)
#define DSI_DLTCR_HS2LP_TIME3          ((uint32_t)0x00080000U)
#define DSI_DLTCR_HS2LP_TIME4          ((uint32_t)0x00100000U)
#define DSI_DLTCR_HS2LP_TIME5          ((uint32_t)0x00200000U)
#define DSI_DLTCR_HS2LP_TIME6          ((uint32_t)0x00400000U)
#define DSI_DLTCR_HS2LP_TIME7          ((uint32_t)0x00800000U)
#define DSI_DLTCR_HS2LP_TIME8          ((uint32_t)0x01000000U)
#define DSI_DLTCR_HS2LP_TIME9          ((uint32_t)0x02000000U)

/*******************  Bit definition for DSI_PCTLR register  **************/
#define DSI_PCTLR_DEN                  ((uint32_t)0x00000002U)               /*!< Digital Enable */
#define DSI_PCTLR_CKE                  ((uint32_t)0x00000004U)               /*!< Clock Enable */

/*******************  Bit definition for DSI_PCONFR register  *************/
#define DSI_PCONFR_NL                  ((uint32_t)0x00000003U)               /*!< Number of Lanes */
#define DSI_PCONFR_NL0                 ((uint32_t)0x00000001U)
#define DSI_PCONFR_NL1                 ((uint32_t)0x00000002U)
                                     
#define DSI_PCONFR_SW_TIME             ((uint32_t)0x0000FF00U)               /*!< Stop Wait Time */
#define DSI_PCONFR_SW_TIME0            ((uint32_t)0x00000100U)
#define DSI_PCONFR_SW_TIME1            ((uint32_t)0x00000200U)
#define DSI_PCONFR_SW_TIME2            ((uint32_t)0x00000400U)
#define DSI_PCONFR_SW_TIME3            ((uint32_t)0x00000800U)
#define DSI_PCONFR_SW_TIME4            ((uint32_t)0x00001000U)
#define DSI_PCONFR_SW_TIME5            ((uint32_t)0x00002000U)
#define DSI_PCONFR_SW_TIME6            ((uint32_t)0x00004000U)
#define DSI_PCONFR_SW_TIME7            ((uint32_t)0x00008000U)

/*******************  Bit definition for DSI_PUCR register  ***************/
#define DSI_PUCR_URCL                  ((uint32_t)0x00000001U)               /*!< ULPS Request on Clock Lane */
#define DSI_PUCR_UECL                  ((uint32_t)0x00000002U)               /*!< ULPS Exit on Clock Lane */
#define DSI_PUCR_URDL                  ((uint32_t)0x00000004U)               /*!< ULPS Request on Data Lane */
#define DSI_PUCR_UEDL                  ((uint32_t)0x00000008U)               /*!< ULPS Exit on Data Lane */

/*******************  Bit definition for DSI_PTTCR register  **************/
#define DSI_PTTCR_TX_TRIG              ((uint32_t)0x0000000FU)               /*!< Transmission Trigger */
#define DSI_PTTCR_TX_TRIG0             ((uint32_t)0x00000001U)
#define DSI_PTTCR_TX_TRIG1             ((uint32_t)0x00000002U)
#define DSI_PTTCR_TX_TRIG2             ((uint32_t)0x00000004U)
#define DSI_PTTCR_TX_TRIG3             ((uint32_t)0x00000008U)

/*******************  Bit definition for DSI_PSR register  ****************/
#define DSI_PSR_PD                     ((uint32_t)0x00000002U)               /*!< PHY Direction */
#define DSI_PSR_PSSC                   ((uint32_t)0x00000004U)               /*!< PHY Stop State Clock lane */
#define DSI_PSR_UANC                   ((uint32_t)0x00000008U)               /*!< ULPS Active Not Clock lane */
#define DSI_PSR_PSS0                   ((uint32_t)0x00000010U)               /*!< PHY Stop State lane 0 */
#define DSI_PSR_UAN0                   ((uint32_t)0x00000020U)               /*!< ULPS Active Not lane 0 */
#define DSI_PSR_RUE0                   ((uint32_t)0x00000040U)               /*!< RX ULPS Escape lane 0 */
#define DSI_PSR_PSS1                   ((uint32_t)0x00000080U)               /*!< PHY Stop State lane 1 */
#define DSI_PSR_UAN1                   ((uint32_t)0x00000100U)               /*!< ULPS Active Not lane 1 */

/*******************  Bit definition for DSI_ISR0 register  ***************/
#define DSI_ISR0_AE0                   ((uint32_t)0x00000001U)               /*!< Acknowledge Error 0 */
#define DSI_ISR0_AE1                   ((uint32_t)0x00000002U)               /*!< Acknowledge Error 1 */
#define DSI_ISR0_AE2                   ((uint32_t)0x00000004U)               /*!< Acknowledge Error 2 */
#define DSI_ISR0_AE3                   ((uint32_t)0x00000008U)               /*!< Acknowledge Error 3 */
#define DSI_ISR0_AE4                   ((uint32_t)0x00000010U)               /*!< Acknowledge Error 4 */
#define DSI_ISR0_AE5                   ((uint32_t)0x00000020U)               /*!< Acknowledge Error 5 */
#define DSI_ISR0_AE6                   ((uint32_t)0x00000040U)               /*!< Acknowledge Error 6 */
#define DSI_ISR0_AE7                   ((uint32_t)0x00000080U)               /*!< Acknowledge Error 7 */
#define DSI_ISR0_AE8                   ((uint32_t)0x00000100U)               /*!< Acknowledge Error 8 */
#define DSI_ISR0_AE9                   ((uint32_t)0x00000200U)               /*!< Acknowledge Error 9 */
#define DSI_ISR0_AE10                  ((uint32_t)0x00000400U)               /*!< Acknowledge Error 10 */
#define DSI_ISR0_AE11                  ((uint32_t)0x00000800U)               /*!< Acknowledge Error 11 */
#define DSI_ISR0_AE12                  ((uint32_t)0x00001000U)               /*!< Acknowledge Error 12 */
#define DSI_ISR0_AE13                  ((uint32_t)0x00002000U)               /*!< Acknowledge Error 13 */
#define DSI_ISR0_AE14                  ((uint32_t)0x00004000U)               /*!< Acknowledge Error 14 */
#define DSI_ISR0_AE15                  ((uint32_t)0x00008000U)               /*!< Acknowledge Error 15 */
#define DSI_ISR0_PE0                   ((uint32_t)0x00010000U)               /*!< PHY Error 0 */
#define DSI_ISR0_PE1                   ((uint32_t)0x00020000U)               /*!< PHY Error 1 */
#define DSI_ISR0_PE2                   ((uint32_t)0x00040000U)               /*!< PHY Error 2 */
#define DSI_ISR0_PE3                   ((uint32_t)0x00080000U)               /*!< PHY Error 3 */
#define DSI_ISR0_PE4                   ((uint32_t)0x00100000U)               /*!< PHY Error 4 */

/*******************  Bit definition for DSI_ISR1 register  ***************/
#define DSI_ISR1_TOHSTX                ((uint32_t)0x00000001U)               /*!< Timeout High-Speed Transmission */
#define DSI_ISR1_TOLPRX                ((uint32_t)0x00000002U)               /*!< Timeout Low-Power Reception */
#define DSI_ISR1_ECCSE                 ((uint32_t)0x00000004U)               /*!< ECC Single-bit Error */
#define DSI_ISR1_ECCME                 ((uint32_t)0x00000008U)               /*!< ECC Multi-bit Error */
#define DSI_ISR1_CRCE                  ((uint32_t)0x00000010U)               /*!< CRC Error */
#define DSI_ISR1_PSE                   ((uint32_t)0x00000020U)               /*!< Packet Size Error */
#define DSI_ISR1_EOTPE                 ((uint32_t)0x00000040U)               /*!< EoTp Error */
#define DSI_ISR1_LPWRE                 ((uint32_t)0x00000080U)               /*!< LTDC Payload Write Error */
#define DSI_ISR1_GCWRE                 ((uint32_t)0x00000100U)               /*!< Generic Command Write Error */
#define DSI_ISR1_GPWRE                 ((uint32_t)0x00000200U)               /*!< Generic Payload Write Error */
#define DSI_ISR1_GPTXE                 ((uint32_t)0x00000400U)               /*!< Generic Payload Transmit Error */
#define DSI_ISR1_GPRDE                 ((uint32_t)0x00000800U)               /*!< Generic Payload Read Error */
#define DSI_ISR1_GPRXE                 ((uint32_t)0x00001000U)               /*!< Generic Payload Receive Error */

/*******************  Bit definition for DSI_IER0 register  ***************/
#define DSI_IER0_AE0IE                 ((uint32_t)0x00000001U)               /*!< Acknowledge Error 0 Interrupt Enable */
#define DSI_IER0_AE1IE                 ((uint32_t)0x00000002U)               /*!< Acknowledge Error 1 Interrupt Enable */
#define DSI_IER0_AE2IE                 ((uint32_t)0x00000004U)               /*!< Acknowledge Error 2 Interrupt Enable */
#define DSI_IER0_AE3IE                 ((uint32_t)0x00000008U)               /*!< Acknowledge Error 3 Interrupt Enable */
#define DSI_IER0_AE4IE                 ((uint32_t)0x00000010U)               /*!< Acknowledge Error 4 Interrupt Enable */
#define DSI_IER0_AE5IE                 ((uint32_t)0x00000020U)               /*!< Acknowledge Error 5 Interrupt Enable */
#define DSI_IER0_AE6IE                 ((uint32_t)0x00000040U)               /*!< Acknowledge Error 6 Interrupt Enable */
#define DSI_IER0_AE7IE                 ((uint32_t)0x00000080U)               /*!< Acknowledge Error 7 Interrupt Enable */
#define DSI_IER0_AE8IE                 ((uint32_t)0x00000100U)               /*!< Acknowledge Error 8 Interrupt Enable */
#define DSI_IER0_AE9IE                 ((uint32_t)0x00000200U)               /*!< Acknowledge Error 9 Interrupt Enable */
#define DSI_IER0_AE10IE                ((uint32_t)0x00000400U)               /*!< Acknowledge Error 10 Interrupt Enable */
#define DSI_IER0_AE11IE                ((uint32_t)0x00000800U)               /*!< Acknowledge Error 11 Interrupt Enable */
#define DSI_IER0_AE12IE                ((uint32_t)0x00001000U)               /*!< Acknowledge Error 12 Interrupt Enable */
#define DSI_IER0_AE13IE                ((uint32_t)0x00002000U)               /*!< Acknowledge Error 13 Interrupt Enable */
#define DSI_IER0_AE14IE                ((uint32_t)0x00004000U)               /*!< Acknowledge Error 14 Interrupt Enable */
#define DSI_IER0_AE15IE                ((uint32_t)0x00008000U)               /*!< Acknowledge Error 15 Interrupt Enable */
#define DSI_IER0_PE0IE                 ((uint32_t)0x00010000U)               /*!< PHY Error 0 Interrupt Enable */
#define DSI_IER0_PE1IE                 ((uint32_t)0x00020000U)               /*!< PHY Error 1 Interrupt Enable */
#define DSI_IER0_PE2IE                 ((uint32_t)0x00040000U)               /*!< PHY Error 2 Interrupt Enable */
#define DSI_IER0_PE3IE                 ((uint32_t)0x00080000U)               /*!< PHY Error 3 Interrupt Enable */
#define DSI_IER0_PE4IE                 ((uint32_t)0x00100000U)               /*!< PHY Error 4 Interrupt Enable */

/*******************  Bit definition for DSI_IER1 register  ***************/
#define DSI_IER1_TOHSTXIE              ((uint32_t)0x00000001U)               /*!< Timeout High-Speed Transmission Interrupt Enable */
#define DSI_IER1_TOLPRXIE              ((uint32_t)0x00000002U)               /*!< Timeout Low-Power Reception Interrupt Enable */
#define DSI_IER1_ECCSEIE               ((uint32_t)0x00000004U)               /*!< ECC Single-bit Error Interrupt Enable */
#define DSI_IER1_ECCMEIE               ((uint32_t)0x00000008U)               /*!< ECC Multi-bit Error Interrupt Enable */
#define DSI_IER1_CRCEIE                ((uint32_t)0x00000010U)               /*!< CRC Error Interrupt Enable */
#define DSI_IER1_PSEIE                 ((uint32_t)0x00000020U)               /*!< Packet Size Error Interrupt Enable */
#define DSI_IER1_EOTPEIE               ((uint32_t)0x00000040U)               /*!< EoTp Error Interrupt Enable */
#define DSI_IER1_LPWREIE               ((uint32_t)0x00000080U)               /*!< LTDC Payload Write Error Interrupt Enable */
#define DSI_IER1_GCWREIE               ((uint32_t)0x00000100U)               /*!< Generic Command Write Error Interrupt Enable */
#define DSI_IER1_GPWREIE               ((uint32_t)0x00000200U)               /*!< Generic Payload Write Error Interrupt Enable */
#define DSI_IER1_GPTXEIE               ((uint32_t)0x00000400U)               /*!< Generic Payload Transmit Error Interrupt Enable */
#define DSI_IER1_GPRDEIE               ((uint32_t)0x00000800U)               /*!< Generic Payload Read Error Interrupt Enable */
#define DSI_IER1_GPRXEIE               ((uint32_t)0x00001000U)               /*!< Generic Payload Receive Error Interrupt Enable */

/*******************  Bit definition for DSI_FIR0 register  ***************/
#define DSI_FIR0_FAE0                  ((uint32_t)0x00000001U)               /*!< Force Acknowledge Error 0 */
#define DSI_FIR0_FAE1                  ((uint32_t)0x00000002U)               /*!< Force Acknowledge Error 1 */
#define DSI_FIR0_FAE2                  ((uint32_t)0x00000004U)               /*!< Force Acknowledge Error 2 */
#define DSI_FIR0_FAE3                  ((uint32_t)0x00000008U)               /*!< Force Acknowledge Error 3 */
#define DSI_FIR0_FAE4                  ((uint32_t)0x00000010U)               /*!< Force Acknowledge Error 4 */
#define DSI_FIR0_FAE5                  ((uint32_t)0x00000020U)               /*!< Force Acknowledge Error 5 */
#define DSI_FIR0_FAE6                  ((uint32_t)0x00000040U)               /*!< Force Acknowledge Error 6 */
#define DSI_FIR0_FAE7                  ((uint32_t)0x00000080U)               /*!< Force Acknowledge Error 7 */
#define DSI_FIR0_FAE8                  ((uint32_t)0x00000100U)               /*!< Force Acknowledge Error 8 */
#define DSI_FIR0_FAE9                  ((uint32_t)0x00000200U)               /*!< Force Acknowledge Error 9 */
#define DSI_FIR0_FAE10                 ((uint32_t)0x00000400U)               /*!< Force Acknowledge Error 10 */
#define DSI_FIR0_FAE11                 ((uint32_t)0x00000800U)               /*!< Force Acknowledge Error 11 */
#define DSI_FIR0_FAE12                 ((uint32_t)0x00001000U)               /*!< Force Acknowledge Error 12 */
#define DSI_FIR0_FAE13                 ((uint32_t)0x00002000U)               /*!< Force Acknowledge Error 13 */
#define DSI_FIR0_FAE14                 ((uint32_t)0x00004000U)               /*!< Force Acknowledge Error 14 */
#define DSI_FIR0_FAE15                 ((uint32_t)0x00008000U)               /*!< Force Acknowledge Error 15 */
#define DSI_FIR0_FPE0                  ((uint32_t)0x00010000U)               /*!< Force PHY Error 0 */
#define DSI_FIR0_FPE1                  ((uint32_t)0x00020000U)               /*!< Force PHY Error 1 */
#define DSI_FIR0_FPE2                  ((uint32_t)0x00040000U)               /*!< Force PHY Error 2 */
#define DSI_FIR0_FPE3                  ((uint32_t)0x00080000U)               /*!< Force PHY Error 3 */
#define DSI_FIR0_FPE4                  ((uint32_t)0x00100000U)               /*!< Force PHY Error 4 */

/*******************  Bit definition for DSI_FIR1 register  ***************/
#define DSI_FIR1_FTOHSTX               ((uint32_t)0x00000001U)               /*!< Force Timeout High-Speed Transmission */
#define DSI_FIR1_FTOLPRX               ((uint32_t)0x00000002U)               /*!< Force Timeout Low-Power Reception */
#define DSI_FIR1_FECCSE                ((uint32_t)0x00000004U)               /*!< Force ECC Single-bit Error */
#define DSI_FIR1_FECCME                ((uint32_t)0x00000008U)               /*!< Force ECC Multi-bit Error */
#define DSI_FIR1_FCRCE                 ((uint32_t)0x00000010U)               /*!< Force CRC Error */
#define DSI_FIR1_FPSE                  ((uint32_t)0x00000020U)               /*!< Force Packet Size Error */
#define DSI_FIR1_FEOTPE                ((uint32_t)0x00000040U)               /*!< Force EoTp Error */
#define DSI_FIR1_FLPWRE                ((uint32_t)0x00000080U)               /*!< Force LTDC Payload Write Error */
#define DSI_FIR1_FGCWRE                ((uint32_t)0x00000100U)               /*!< Force Generic Command Write Error */
#define DSI_FIR1_FGPWRE                ((uint32_t)0x00000200U)               /*!< Force Generic Payload Write Error */
#define DSI_FIR1_FGPTXE                ((uint32_t)0x00000400U)               /*!< Force Generic Payload Transmit Error */
#define DSI_FIR1_FGPRDE                ((uint32_t)0x00000800U)               /*!< Force Generic Payload Read Error */
#define DSI_FIR1_FGPRXE                ((uint32_t)0x00001000U)               /*!< Force Generic Payload Receive Error */

/*******************  Bit definition for DSI_DLTRCR register  *************/
#define DSI_DLTRCR_MRD_TIME            ((uint32_t)0x00007FFFU)               /*!< Maximum Read Time */
#define DSI_DLTRCR_MRD_TIME0           ((uint32_t)0x00000001U)
#define DSI_DLTRCR_MRD_TIME1           ((uint32_t)0x00000002U)
#define DSI_DLTRCR_MRD_TIME2           ((uint32_t)0x00000004U)
#define DSI_DLTRCR_MRD_TIME3           ((uint32_t)0x00000008U)
#define DSI_DLTRCR_MRD_TIME4           ((uint32_t)0x00000010U)
#define DSI_DLTRCR_MRD_TIME5           ((uint32_t)0x00000020U)
#define DSI_DLTRCR_MRD_TIME6           ((uint32_t)0x00000040U)
#define DSI_DLTRCR_MRD_TIME7           ((uint32_t)0x00000080U)
#define DSI_DLTRCR_MRD_TIME8           ((uint32_t)0x00000100U)
#define DSI_DLTRCR_MRD_TIME9           ((uint32_t)0x00000200U)
#define DSI_DLTRCR_MRD_TIME10          ((uint32_t)0x00000400U)
#define DSI_DLTRCR_MRD_TIME11          ((uint32_t)0x00000800U)
#define DSI_DLTRCR_MRD_TIME12          ((uint32_t)0x00001000U)
#define DSI_DLTRCR_MRD_TIME13          ((uint32_t)0x00002000U)
#define DSI_DLTRCR_MRD_TIME14          ((uint32_t)0x00004000U)

/*******************  Bit definition for DSI_VSCR register  ***************/
#define DSI_VSCR_EN                    ((uint32_t)0x00000001U)               /*!< Enable */
#define DSI_VSCR_UR                    ((uint32_t)0x00000100U)               /*!< Update Register */

/*******************  Bit definition for DSI_LCVCIDR register  ************/
#define DSI_LCVCIDR_VCID               ((uint32_t)0x00000003U)               /*!< Virtual Channel ID */
#define DSI_LCVCIDR_VCID0              ((uint32_t)0x00000001U)
#define DSI_LCVCIDR_VCID1              ((uint32_t)0x00000002U)

/*******************  Bit definition for DSI_LCCCR register  **************/
#define DSI_LCCCR_COLC                 ((uint32_t)0x0000000FU)               /*!< Color Coding */
#define DSI_LCCCR_COLC0                ((uint32_t)0x00000001U)
#define DSI_LCCCR_COLC1                ((uint32_t)0x00000002U)
#define DSI_LCCCR_COLC2                ((uint32_t)0x00000004U)
#define DSI_LCCCR_COLC3                ((uint32_t)0x00000008U)

#define DSI_LCCCR_LPE                  ((uint32_t)0x00000100U)               /*!< Loosely Packed Enable */

/*******************  Bit definition for DSI_LPMCCR register  *************/
#define DSI_LPMCCR_VLPSIZE             ((uint32_t)0x000000FFU)               /*!< VACT Largest Packet Size */
#define DSI_LPMCCR_VLPSIZE0            ((uint32_t)0x00000001U)
#define DSI_LPMCCR_VLPSIZE1            ((uint32_t)0x00000002U)
#define DSI_LPMCCR_VLPSIZE2            ((uint32_t)0x00000004U)
#define DSI_LPMCCR_VLPSIZE3            ((uint32_t)0x00000008U)
#define DSI_LPMCCR_VLPSIZE4            ((uint32_t)0x00000010U)
#define DSI_LPMCCR_VLPSIZE5            ((uint32_t)0x00000020U)
#define DSI_LPMCCR_VLPSIZE6            ((uint32_t)0x00000040U)
#define DSI_LPMCCR_VLPSIZE7            ((uint32_t)0x00000080U)

#define DSI_LPMCCR_LPSIZE              ((uint32_t)0x00FF0000U)               /*!< Largest Packet Size */
#define DSI_LPMCCR_LPSIZE0             ((uint32_t)0x00010000U)
#define DSI_LPMCCR_LPSIZE1             ((uint32_t)0x00020000U)
#define DSI_LPMCCR_LPSIZE2             ((uint32_t)0x00040000U)
#define DSI_LPMCCR_LPSIZE3             ((uint32_t)0x00080000U)
#define DSI_LPMCCR_LPSIZE4             ((uint32_t)0x00100000U)
#define DSI_LPMCCR_LPSIZE5             ((uint32_t)0x00200000U)
#define DSI_LPMCCR_LPSIZE6             ((uint32_t)0x00400000U)
#define DSI_LPMCCR_LPSIZE7             ((uint32_t)0x00800000U)

/*******************  Bit definition for DSI_VMCCR register  **************/
#define DSI_VMCCR_VMT                  ((uint32_t)0x00000003U)               /*!< Video Mode Type */
#define DSI_VMCCR_VMT0                 ((uint32_t)0x00000001U)
#define DSI_VMCCR_VMT1                 ((uint32_t)0x00000002U)

#define DSI_VMCCR_LPVSAE               ((uint32_t)0x00000100U)               /*!< Low-power Vertical Sync time Enable */
#define DSI_VMCCR_LPVBPE               ((uint32_t)0x00000200U)               /*!< Low-power Vertical Back-porch Enable */
#define DSI_VMCCR_LPVFPE               ((uint32_t)0x00000400U)               /*!< Low-power Vertical Front-porch Enable */
#define DSI_VMCCR_LPVAE                ((uint32_t)0x00000800U)               /*!< Low-power Vertical Active Enable */
#define DSI_VMCCR_LPHBPE               ((uint32_t)0x00001000U)               /*!< Low-power Horizontal Back-porch Enable */
#define DSI_VMCCR_LPHFE                ((uint32_t)0x00002000U)               /*!< Low-power Horizontal Front-porch Enable */
#define DSI_VMCCR_FBTAAE               ((uint32_t)0x00004000U)               /*!< Frame BTA Acknowledge Enable */
#define DSI_VMCCR_LPCE                 ((uint32_t)0x00008000U)               /*!< Low-power Command Enable */

/*******************  Bit definition for DSI_VPCCR register  **************/
#define DSI_VPCCR_VPSIZE               ((uint32_t)0x00003FFFU)               /*!< Video Packet Size */
#define DSI_VPCCR_VPSIZE0              ((uint32_t)0x00000001U)
#define DSI_VPCCR_VPSIZE1              ((uint32_t)0x00000002U)
#define DSI_VPCCR_VPSIZE2              ((uint32_t)0x00000004U)
#define DSI_VPCCR_VPSIZE3              ((uint32_t)0x00000008U)
#define DSI_VPCCR_VPSIZE4              ((uint32_t)0x00000010U)
#define DSI_VPCCR_VPSIZE5              ((uint32_t)0x00000020U)
#define DSI_VPCCR_VPSIZE6              ((uint32_t)0x00000040U)
#define DSI_VPCCR_VPSIZE7              ((uint32_t)0x00000080U)
#define DSI_VPCCR_VPSIZE8              ((uint32_t)0x00000100U)
#define DSI_VPCCR_VPSIZE9              ((uint32_t)0x00000200U)
#define DSI_VPCCR_VPSIZE10             ((uint32_t)0x00000400U)
#define DSI_VPCCR_VPSIZE11             ((uint32_t)0x00000800U)
#define DSI_VPCCR_VPSIZE12             ((uint32_t)0x00001000U)
#define DSI_VPCCR_VPSIZE13             ((uint32_t)0x00002000U)

/*******************  Bit definition for DSI_VCCCR register  **************/
#define DSI_VCCCR_NUMC                 ((uint32_t)0x00001FFFU)               /*!< Number of Chunks */
#define DSI_VCCCR_NUMC0                ((uint32_t)0x00000001U)
#define DSI_VCCCR_NUMC1                ((uint32_t)0x00000002U)
#define DSI_VCCCR_NUMC2                ((uint32_t)0x00000004U)
#define DSI_VCCCR_NUMC3                ((uint32_t)0x00000008U)
#define DSI_VCCCR_NUMC4                ((uint32_t)0x00000010U)
#define DSI_VCCCR_NUMC5                ((uint32_t)0x00000020U)
#define DSI_VCCCR_NUMC6                ((uint32_t)0x00000040U)
#define DSI_VCCCR_NUMC7                ((uint32_t)0x00000080U)
#define DSI_VCCCR_NUMC8                ((uint32_t)0x00000100U)
#define DSI_VCCCR_NUMC9                ((uint32_t)0x00000200U)
#define DSI_VCCCR_NUMC10               ((uint32_t)0x00000400U)
#define DSI_VCCCR_NUMC11               ((uint32_t)0x00000800U)
#define DSI_VCCCR_NUMC12               ((uint32_t)0x00001000U)

/*******************  Bit definition for DSI_VNPCCR register  *************/
#define DSI_VNPCCR_NPSIZE              ((uint32_t)0x00001FFFU)               /*!< Number of Chunks */
#define DSI_VNPCCR_NPSIZE0             ((uint32_t)0x00000001U)
#define DSI_VNPCCR_NPSIZE1             ((uint32_t)0x00000002U)
#define DSI_VNPCCR_NPSIZE2             ((uint32_t)0x00000004U)
#define DSI_VNPCCR_NPSIZE3             ((uint32_t)0x00000008U)
#define DSI_VNPCCR_NPSIZE4             ((uint32_t)0x00000010U)
#define DSI_VNPCCR_NPSIZE5             ((uint32_t)0x00000020U)
#define DSI_VNPCCR_NPSIZE6             ((uint32_t)0x00000040U)
#define DSI_VNPCCR_NPSIZE7             ((uint32_t)0x00000080U)
#define DSI_VNPCCR_NPSIZE8             ((uint32_t)0x00000100U)
#define DSI_VNPCCR_NPSIZE9             ((uint32_t)0x00000200U)
#define DSI_VNPCCR_NPSIZE10            ((uint32_t)0x00000400U)
#define DSI_VNPCCR_NPSIZE11            ((uint32_t)0x00000800U)
#define DSI_VNPCCR_NPSIZE12            ((uint32_t)0x00001000U)

/*******************  Bit definition for DSI_VHSACCR register  ************/
#define DSI_VHSACCR_HSA                ((uint32_t)0x00000FFFU)               /*!< Horizontal Synchronism Active duration */
#define DSI_VHSACCR_HSA0               ((uint32_t)0x00000001U)
#define DSI_VHSACCR_HSA1               ((uint32_t)0x00000002U)
#define DSI_VHSACCR_HSA2               ((uint32_t)0x00000004U)
#define DSI_VHSACCR_HSA3               ((uint32_t)0x00000008U)
#define DSI_VHSACCR_HSA4               ((uint32_t)0x00000010U)
#define DSI_VHSACCR_HSA5               ((uint32_t)0x00000020U)
#define DSI_VHSACCR_HSA6               ((uint32_t)0x00000040U)
#define DSI_VHSACCR_HSA7               ((uint32_t)0x00000080U)
#define DSI_VHSACCR_HSA8               ((uint32_t)0x00000100U)
#define DSI_VHSACCR_HSA9               ((uint32_t)0x00000200U)
#define DSI_VHSACCR_HSA10              ((uint32_t)0x00000400U)
#define DSI_VHSACCR_HSA11              ((uint32_t)0x00000800U)

/*******************  Bit definition for DSI_VHBPCCR register  ************/
#define DSI_VHBPCCR_HBP                ((uint32_t)0x00000FFFU)               /*!< Horizontal Back-Porch duration */
#define DSI_VHBPCCR_HBP0               ((uint32_t)0x00000001U)
#define DSI_VHBPCCR_HBP1               ((uint32_t)0x00000002U)
#define DSI_VHBPCCR_HBP2               ((uint32_t)0x00000004U)
#define DSI_VHBPCCR_HBP3               ((uint32_t)0x00000008U)
#define DSI_VHBPCCR_HBP4               ((uint32_t)0x00000010U)
#define DSI_VHBPCCR_HBP5               ((uint32_t)0x00000020U)
#define DSI_VHBPCCR_HBP6               ((uint32_t)0x00000040U)
#define DSI_VHBPCCR_HBP7               ((uint32_t)0x00000080U)
#define DSI_VHBPCCR_HBP8               ((uint32_t)0x00000100U)
#define DSI_VHBPCCR_HBP9               ((uint32_t)0x00000200U)
#define DSI_VHBPCCR_HBP10              ((uint32_t)0x00000400U)
#define DSI_VHBPCCR_HBP11              ((uint32_t)0x00000800U)

/*******************  Bit definition for DSI_VLCCR register  **************/
#define DSI_VLCCR_HLINE                ((uint32_t)0x00007FFFU)               /*!< Horizontal Line duration */
#define DSI_VLCCR_HLINE0               ((uint32_t)0x00000001U)
#define DSI_VLCCR_HLINE1               ((uint32_t)0x00000002U)
#define DSI_VLCCR_HLINE2               ((uint32_t)0x00000004U)
#define DSI_VLCCR_HLINE3               ((uint32_t)0x00000008U)
#define DSI_VLCCR_HLINE4               ((uint32_t)0x00000010U)
#define DSI_VLCCR_HLINE5               ((uint32_t)0x00000020U)
#define DSI_VLCCR_HLINE6               ((uint32_t)0x00000040U)
#define DSI_VLCCR_HLINE7               ((uint32_t)0x00000080U)
#define DSI_VLCCR_HLINE8               ((uint32_t)0x00000100U)
#define DSI_VLCCR_HLINE9               ((uint32_t)0x00000200U)
#define DSI_VLCCR_HLINE10              ((uint32_t)0x00000400U)
#define DSI_VLCCR_HLINE11              ((uint32_t)0x00000800U)
#define DSI_VLCCR_HLINE12              ((uint32_t)0x00001000U)
#define DSI_VLCCR_HLINE13              ((uint32_t)0x00002000U)
#define DSI_VLCCR_HLINE14              ((uint32_t)0x00004000U)

/*******************  Bit definition for DSI_VVSACCR register  ***************/
#define DSI_VVSACCR_VSA                ((uint32_t)0x000003FFU)               /*!< Vertical Synchronism Active duration */
#define DSI_VVSACCR_VSA0               ((uint32_t)0x00000001U)
#define DSI_VVSACCR_VSA1               ((uint32_t)0x00000002U)
#define DSI_VVSACCR_VSA2               ((uint32_t)0x00000004U)
#define DSI_VVSACCR_VSA3               ((uint32_t)0x00000008U)
#define DSI_VVSACCR_VSA4               ((uint32_t)0x00000010U)
#define DSI_VVSACCR_VSA5               ((uint32_t)0x00000020U)
#define DSI_VVSACCR_VSA6               ((uint32_t)0x00000040U)
#define DSI_VVSACCR_VSA7               ((uint32_t)0x00000080U)
#define DSI_VVSACCR_VSA8               ((uint32_t)0x00000100U)
#define DSI_VVSACCR_VSA9               ((uint32_t)0x00000200U)

/*******************  Bit definition for DSI_VVBPCCR register  ************/
#define DSI_VVBPCCR_VBP                ((uint32_t)0x000003FFU)               /*!< Vertical Back-Porch duration */
#define DSI_VVBPCCR_VBP0               ((uint32_t)0x00000001U)
#define DSI_VVBPCCR_VBP1               ((uint32_t)0x00000002U)
#define DSI_VVBPCCR_VBP2               ((uint32_t)0x00000004U)
#define DSI_VVBPCCR_VBP3               ((uint32_t)0x00000008U)
#define DSI_VVBPCCR_VBP4               ((uint32_t)0x00000010U)
#define DSI_VVBPCCR_VBP5               ((uint32_t)0x00000020U)
#define DSI_VVBPCCR_VBP6               ((uint32_t)0x00000040U)
#define DSI_VVBPCCR_VBP7               ((uint32_t)0x00000080U)
#define DSI_VVBPCCR_VBP8               ((uint32_t)0x00000100U)
#define DSI_VVBPCCR_VBP9               ((uint32_t)0x00000200U)

/*******************  Bit definition for DSI_VVFPCCR register  ************/
#define DSI_VVFPCCR_VFP                ((uint32_t)0x000003FFU)               /*!< Vertical Front-Porch duration */
#define DSI_VVFPCCR_VFP0               ((uint32_t)0x00000001U)
#define DSI_VVFPCCR_VFP1               ((uint32_t)0x00000002U)
#define DSI_VVFPCCR_VFP2               ((uint32_t)0x00000004U)
#define DSI_VVFPCCR_VFP3               ((uint32_t)0x00000008U)
#define DSI_VVFPCCR_VFP4               ((uint32_t)0x00000010U)
#define DSI_VVFPCCR_VFP5               ((uint32_t)0x00000020U)
#define DSI_VVFPCCR_VFP6               ((uint32_t)0x00000040U)
#define DSI_VVFPCCR_VFP7               ((uint32_t)0x00000080U)
#define DSI_VVFPCCR_VFP8               ((uint32_t)0x00000100U)
#define DSI_VVFPCCR_VFP9               ((uint32_t)0x00000200U)

/*******************  Bit definition for DSI_VVACCR register  *************/
#define DSI_VVACCR_VA                  ((uint32_t)0x00003FFFU)               /*!< Vertical Active duration */
#define DSI_VVACCR_VA0                 ((uint32_t)0x00000001U)
#define DSI_VVACCR_VA1                 ((uint32_t)0x00000002U)
#define DSI_VVACCR_VA2                 ((uint32_t)0x00000004U)
#define DSI_VVACCR_VA3                 ((uint32_t)0x00000008U)
#define DSI_VVACCR_VA4                 ((uint32_t)0x00000010U)
#define DSI_VVACCR_VA5                 ((uint32_t)0x00000020U)
#define DSI_VVACCR_VA6                 ((uint32_t)0x00000040U)
#define DSI_VVACCR_VA7                 ((uint32_t)0x00000080U)
#define DSI_VVACCR_VA8                 ((uint32_t)0x00000100U)
#define DSI_VVACCR_VA9                 ((uint32_t)0x00000200U)
#define DSI_VVACCR_VA10                ((uint32_t)0x00000400U)
#define DSI_VVACCR_VA11                ((uint32_t)0x00000800U)
#define DSI_VVACCR_VA12                ((uint32_t)0x00001000U)
#define DSI_VVACCR_VA13                ((uint32_t)0x00002000U)

/*******************  Bit definition for DSI_TDCCR register  **************/
#define DSI_TDCCR_3DM                  ((uint32_t)0x00000003U)               /*!< 3D Mode */
#define DSI_TDCCR_3DM0                 ((uint32_t)0x00000001U)
#define DSI_TDCCR_3DM1                 ((uint32_t)0x00000002U)

#define DSI_TDCCR_3DF                  ((uint32_t)0x0000000CU)               /*!< 3D Format */
#define DSI_TDCCR_3DF0                 ((uint32_t)0x00000004U)
#define DSI_TDCCR_3DF1                 ((uint32_t)0x00000008U)

#define DSI_TDCCR_SVS                  ((uint32_t)0x00000010U)               /*!< Second VSYNC */
#define DSI_TDCCR_RF                   ((uint32_t)0x00000020U)               /*!< Right First */
#define DSI_TDCCR_S3DC                 ((uint32_t)0x00010000U)               /*!< Send 3D Control */

/*******************  Bit definition for DSI_WCFGR register  ***************/
#define DSI_WCFGR_DSIM                 ((uint32_t)0x00000001U)               /*!< DSI Mode */

#define DSI_WCFGR_COLMUX               ((uint32_t)0x0000000EU)               /*!< Color Multiplexing */
#define DSI_WCFGR_COLMUX0              ((uint32_t)0x00000002U)
#define DSI_WCFGR_COLMUX1              ((uint32_t)0x00000004U)
#define DSI_WCFGR_COLMUX2              ((uint32_t)0x00000008U)
 
#define DSI_WCFGR_TESRC                ((uint32_t)0x00000010U)               /*!< Tearing Effect Source */
#define DSI_WCFGR_TEPOL                ((uint32_t)0x00000020U)               /*!< Tearing Effect Polarity */
#define DSI_WCFGR_AR                   ((uint32_t)0x00000040U)               /*!< Automatic Refresh */
#define DSI_WCFGR_VSPOL                ((uint32_t)0x00000080U)               /*!< VSync Polarity */

/*******************  Bit definition for DSI_WCR register  *****************/
#define DSI_WCR_COLM                   ((uint32_t)0x00000001U)               /*!< Color Mode */
#define DSI_WCR_SHTDN                  ((uint32_t)0x00000002U)               /*!< Shutdown */
#define DSI_WCR_LTDCEN                 ((uint32_t)0x00000004U)               /*!< LTDC Enable */
#define DSI_WCR_DSIEN                  ((uint32_t)0x00000008U)               /*!< DSI Enable */

/*******************  Bit definition for DSI_WIER register  ****************/
#define DSI_WIER_TEIE                  ((uint32_t)0x00000001U)               /*!< Tearing Effect Interrupt Enable */
#define DSI_WIER_ERIE                  ((uint32_t)0x00000002U)               /*!< End of Refresh Interrupt Enable */
#define DSI_WIER_PLLLIE                ((uint32_t)0x00000200U)               /*!< PLL Lock Interrupt Enable */
#define DSI_WIER_PLLUIE                ((uint32_t)0x00000400U)               /*!< PLL Unlock Interrupt Enable */
#define DSI_WIER_RRIE                  ((uint32_t)0x00002000U)               /*!< Regulator Ready Interrupt Enable */

/*******************  Bit definition for DSI_WISR register  ****************/
#define DSI_WISR_TEIF                  ((uint32_t)0x00000001U)               /*!< Tearing Effect Interrupt Flag */
#define DSI_WISR_ERIF                  ((uint32_t)0x00000002U)               /*!< End of Refresh Interrupt Flag */
#define DSI_WISR_BUSY                  ((uint32_t)0x00000004U)               /*!< Busy Flag */
#define DSI_WISR_PLLLS                 ((uint32_t)0x00000100U)               /*!< PLL Lock Status */
#define DSI_WISR_PLLLIF                ((uint32_t)0x00000200U)               /*!< PLL Lock Interrupt Flag */
#define DSI_WISR_PLLUIF                ((uint32_t)0x00000400U)               /*!< PLL Unlock Interrupt Flag */
#define DSI_WISR_RRS                   ((uint32_t)0x00001000U)               /*!< Regulator Ready Flag */
#define DSI_WISR_RRIF                  ((uint32_t)0x00002000U)               /*!< Regulator Ready Interrupt Flag */

/*******************  Bit definition for DSI_WIFCR register  ***************/
#define DSI_WIFCR_CTEIF                ((uint32_t)0x00000001U)               /*!< Clear Tearing Effect Interrupt Flag */
#define DSI_WIFCR_CERIF                ((uint32_t)0x00000002U)               /*!< Clear End of Refresh Interrupt Flag */
#define DSI_WIFCR_CPLLLIF              ((uint32_t)0x00000200U)               /*!< Clear PLL Lock Interrupt Flag */
#define DSI_WIFCR_CPLLUIF              ((uint32_t)0x00000400U)               /*!< Clear PLL Unlock Interrupt Flag */
#define DSI_WIFCR_CRRIF                ((uint32_t)0x00002000U)               /*!< Clear Regulator Ready Interrupt Flag */

/*******************  Bit definition for DSI_WPCR0 register  ***************/
#define DSI_WPCR0_UIX4                 ((uint32_t)0x0000003FU)               /*!< Unit Interval multiplied by 4 */
#define DSI_WPCR0_UIX4_0               ((uint32_t)0x00000001U)
#define DSI_WPCR0_UIX4_1               ((uint32_t)0x00000002U)
#define DSI_WPCR0_UIX4_2               ((uint32_t)0x00000004U)
#define DSI_WPCR0_UIX4_3               ((uint32_t)0x00000008U)
#define DSI_WPCR0_UIX4_4               ((uint32_t)0x00000010U)
#define DSI_WPCR0_UIX4_5               ((uint32_t)0x00000020U)

#define DSI_WPCR0_SWCL                 ((uint32_t)0x00000040U)               /*!< Swap pins on clock lane */
#define DSI_WPCR0_SWDL0                ((uint32_t)0x00000080U)               /*!< Swap pins on data lane 1 */
#define DSI_WPCR0_SWDL1                ((uint32_t)0x00000100U)               /*!< Swap pins on data lane 2 */
#define DSI_WPCR0_HSICL                ((uint32_t)0x00000200U)               /*!< Invert the high-speed data signal on clock lane */
#define DSI_WPCR0_HSIDL0               ((uint32_t)0x00000400U)               /*!< Invert the high-speed data signal on lane 1 */
#define DSI_WPCR0_HSIDL1               ((uint32_t)0x00000800U)               /*!< Invert the high-speed data signal on lane 2 */
#define DSI_WPCR0_FTXSMCL              ((uint32_t)0x00001000U)               /*!< Force clock lane in TX stop mode */
#define DSI_WPCR0_FTXSMDL              ((uint32_t)0x00002000U)               /*!< Force data lanes in TX stop mode */
#define DSI_WPCR0_CDOFFDL              ((uint32_t)0x00004000U)               /*!< Contention detection OFF */
#define DSI_WPCR0_TDDL                 ((uint32_t)0x00010000U)               /*!< Turn Disable Data Lanes */

/*******************  Bit definition for DSI_WPCR1 register  ***************/
#define DSI_WPCR1_SKEWCL               ((uint32_t)0x00000003U)               /*!< Skew on Clock Lanes */
#define DSI_WPCR1_SKEWCL0              ((uint32_t)0x00000001U)
#define DSI_WPCR1_SKEWCL1              ((uint32_t)0x00000002U)

#define DSI_WPCR1_SKEWDL               ((uint32_t)0x0000000CU)               /*!< Skew on Data Lanes */
#define DSI_WPCR1_SKEWDL0              ((uint32_t)0x00000004U)
#define DSI_WPCR1_SKEWDL1              ((uint32_t)0x00000008U)

#define DSI_WPCR1_LPTXSRCL             ((uint32_t)0x000000C0U)               /*!< Low-Power TX Slew Rate on Clock Lanes */
#define DSI_WPCR1_LPTXSRCL0            ((uint32_t)0x00000040U)
#define DSI_WPCR1_LPTXSRCL1            ((uint32_t)0x00000080U)

#define DSI_WPCR1_LPTXSRDL             ((uint32_t)0x00000300U)               /*!< Low-Power TX Slew Rate on Data Lanes */
#define DSI_WPCR1_LPTXSRDL0            ((uint32_t)0x00000100U)
#define DSI_WPCR1_LPTXSRDL1            ((uint32_t)0x00000200U)

#define DSI_WPCR1_SDDCCL               ((uint32_t)0x00001000U)               /*!< SDD Control Clock Lane */
#define DSI_WPCR1_SDDCDL               ((uint32_t)0x00002000U)               /*!< SDD Control Data Lanes */
#define DSI_WPCR1_HSTXSRUCL            ((uint32_t)0x00010000U)               /*!< High-Speed TX Slew-Rate Up Clock Lane */
#define DSI_WPCR1_HSTXSRDCL            ((uint32_t)0x00020000U)               /*!< High-Speed TX Slew-Rate Down Clock Lane */
#define DSI_WPCR1_HSTXSRUDL            ((uint32_t)0x00040000U)               /*!< High-Speed TX Slew-Rate Up Data Lane */
#define DSI_WPCR1_HSTXSRDDL            ((uint32_t)0x00080000U)               /*!< High-Speed TX Slew-Rate Down Data Lane */

/*******************  Bit definition for DSI_WRPCR register  ***************/
#define DSI_WRPCR_PLLEN                ((uint32_t)0x00000001U)               /*!< PLL Enable */

#define DSI_WRPCR_PLL_NDIV             ((uint32_t)0x000001FCU)               /*!< PLL Loop Division Factor */
#define DSI_WRPCR_PLL_NDIV0            ((uint32_t)0x00000004U)
#define DSI_WRPCR_PLL_NDIV1            ((uint32_t)0x00000008U)
#define DSI_WRPCR_PLL_NDIV2            ((uint32_t)0x00000010U)
#define DSI_WRPCR_PLL_NDIV3            ((uint32_t)0x00000020U)
#define DSI_WRPCR_PLL_NDIV4            ((uint32_t)0x00000040U)
#define DSI_WRPCR_PLL_NDIV5            ((uint32_t)0x00000080U)
#define DSI_WRPCR_PLL_NDIV6            ((uint32_t)0x00000100U)

#define DSI_WRPCR_PLL_IDF              ((uint32_t)0x00007800U)               /*!< PLL Input Division Factor */
#define DSI_WRPCR_PLL_IDF0             ((uint32_t)0x00000800U)
#define DSI_WRPCR_PLL_IDF1             ((uint32_t)0x00001000U)
#define DSI_WRPCR_PLL_IDF2             ((uint32_t)0x00002000U)
#define DSI_WRPCR_PLL_IDF3             ((uint32_t)0x00004000U)

#define DSI_WRPCR_PLL_ODF              ((uint32_t)0x00030000U)               /*!< PLL Output Division Factor */
#define DSI_WRPCR_PLL_ODF0             ((uint32_t)0x00010000U)
#define DSI_WRPCR_PLL_ODF1             ((uint32_t)0x00020000U)

#define DSI_WRPCR_REGEN                ((uint32_t)0x01000000U)               /*!< Regulator Enable */

#define DSI_WRPCR_BGREN                ((uint32_t)0x10000000U)               /*!< Bandgap Enable */

/**********************  Bit definition for DSI_HWCFGR register  ***************/
#define DSI_HWCFGR_TECHNO_Pos    (0U)
#define DSI_HWCFGR_TECHNO_Msk    (0xFU << DSI_HWCFGR_TECHNO_Pos)            /*!< 0x0000000F */
#define DSI_HWCFGR_TECHNO        DSI_HWCFGR_TECHNO_Msk                      /*!< Size of the payload FIFO */
#define DSI_HWCFGR_FIFOSIZE_Pos  (4U)
#define DSI_HWCFGR_FIFOSIZE_Msk  (0xFFFU << DSI_HWCFGR_FIFOSIZE_Pos)         /*!< 0x0000FFF0 */
#define DSI_HWCFGR_FIFOSIZE      DSI_HWCFGR_FIFOSIZE_Msk                     /*!< Technology used. */


/**********************  Bit definition for DSI_VERR register  *****************/
#define DSI_VERR_MINREV_Pos      (0U)
#define DSI_VERR_MINREV_Msk      (0xFU << DSI_VERR_MINREV_Pos)               /*!< 0x0000000F */
#define DSI_VERR_MINREV          DSI_VERR_MINREV_Msk                         /*!< Minor Revision number */
#define DSI_VERR_MAJREV_Pos      (4U)
#define DSI_VERR_MAJREV_Msk      (0xFU << DSI_VERR_MAJREV_Pos)               /*!< 0x000000F0 */
#define DSI_VERR_MAJREV          DSI_VERR_MAJREV_Msk                         /*!< Major Revision number */

/**********************  Bit definition for DSI_IPIDR register  ****************/
#define DSI_IPIDR_IPID_Pos       (0U)
#define DSI_IPIDR_IPID_Msk       (0xFFFFFFFFU << DSI_IPIDR_IPID_Pos)         /*!< 0xFFFFFFFF */
#define DSI_IPIDR_IPID           DSI_IPIDR_IPID_Msk                          /*!< IP Identification */

/**********************  Bit definition for DSI_SIDR register  *****************/
#define DSI_SIDR_SID_Pos         (0U)
#define DSI_SIDR_SID_Msk         (0xFFFFFFFFU << DSI_SIDR_SID_Pos)           /*!< 0xFFFFFFFF */
#define DSI_SIDR_SID             DSI_SIDR_SID_Msk                            /*!< IP size identification */

/******************************************************************************/
/*                                                                            */
/*                    External Interrupt/Event Controller                     */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for EXTI_IMR1 register  *******************/
#define EXTI_IMR1_IM0_Pos          (0U)
#define EXTI_IMR1_IM0_Msk          (0x1U << EXTI_IMR1_IM0_Pos)                 /*!< 0x00000001 */
#define EXTI_IMR1_IM0              EXTI_IMR1_IM0_Msk                           /*!< Interrupt Mask on line 0 */
#define EXTI_IMR1_IM1_Pos          (1U)
#define EXTI_IMR1_IM1_Msk          (0x1U << EXTI_IMR1_IM1_Pos)                 /*!< 0x00000002 */
#define EXTI_IMR1_IM1              EXTI_IMR1_IM1_Msk                           /*!< Interrupt Mask on line 1 */
#define EXTI_IMR1_IM2_Pos          (2U)
#define EXTI_IMR1_IM2_Msk          (0x1U << EXTI_IMR1_IM2_Pos)                 /*!< 0x00000004 */
#define EXTI_IMR1_IM2              EXTI_IMR1_IM2_Msk                           /*!< Interrupt Mask on line 2 */
#define EXTI_IMR1_IM3_Pos          (3U)
#define EXTI_IMR1_IM3_Msk          (0x1U << EXTI_IMR1_IM3_Pos)                 /*!< 0x00000008 */
#define EXTI_IMR1_IM3              EXTI_IMR1_IM3_Msk                           /*!< Interrupt Mask on line 3 */
#define EXTI_IMR1_IM4_Pos          (4U)
#define EXTI_IMR1_IM4_Msk          (0x1U << EXTI_IMR1_IM4_Pos)                 /*!< 0x00000010 */
#define EXTI_IMR1_IM4              EXTI_IMR1_IM4_Msk                           /*!< Interrupt Mask on line 4 */
#define EXTI_IMR1_IM5_Pos          (5U)
#define EXTI_IMR1_IM5_Msk          (0x1U << EXTI_IMR1_IM5_Pos)                 /*!< 0x00000020 */
#define EXTI_IMR1_IM5              EXTI_IMR1_IM5_Msk                           /*!< Interrupt Mask on line 5 */
#define EXTI_IMR1_IM6_Pos          (6U)
#define EXTI_IMR1_IM6_Msk          (0x1U << EXTI_IMR1_IM6_Pos)                 /*!< 0x00000040 */
#define EXTI_IMR1_IM6              EXTI_IMR1_IM6_Msk                           /*!< Interrupt Mask on line 6 */
#define EXTI_IMR1_IM7_Pos          (7U)
#define EXTI_IMR1_IM7_Msk          (0x1U << EXTI_IMR1_IM7_Pos)                 /*!< 0x00000080 */
#define EXTI_IMR1_IM7              EXTI_IMR1_IM7_Msk                           /*!< Interrupt Mask on line 7 */
#define EXTI_IMR1_IM8_Pos          (8U)
#define EXTI_IMR1_IM8_Msk          (0x1U << EXTI_IMR1_IM8_Pos)                 /*!< 0x00000100 */
#define EXTI_IMR1_IM8              EXTI_IMR1_IM8_Msk                           /*!< Interrupt Mask on line 8 */
#define EXTI_IMR1_IM9_Pos          (9U)
#define EXTI_IMR1_IM9_Msk          (0x1U << EXTI_IMR1_IM9_Pos)                 /*!< 0x00000200 */
#define EXTI_IMR1_IM9              EXTI_IMR1_IM9_Msk                           /*!< Interrupt Mask on line 9 */
#define EXTI_IMR1_IM10_Pos         (10U)
#define EXTI_IMR1_IM10_Msk         (0x1U << EXTI_IMR1_IM10_Pos)                /*!< 0x00000400 */
#define EXTI_IMR1_IM10             EXTI_IMR1_IM10_Msk                          /*!< Interrupt Mask on line 10 */
#define EXTI_IMR1_IM11_Pos         (11U)
#define EXTI_IMR1_IM11_Msk         (0x1U << EXTI_IMR1_IM11_Pos)                /*!< 0x00000800 */
#define EXTI_IMR1_IM11             EXTI_IMR1_IM11_Msk                          /*!< Interrupt Mask on line 11 */
#define EXTI_IMR1_IM12_Pos         (12U)
#define EXTI_IMR1_IM12_Msk         (0x1U << EXTI_IMR1_IM12_Pos)                /*!< 0x00001000 */
#define EXTI_IMR1_IM12             EXTI_IMR1_IM12_Msk                          /*!< Interrupt Mask on line 12 */
#define EXTI_IMR1_IM13_Pos         (13U)
#define EXTI_IMR1_IM13_Msk         (0x1U << EXTI_IMR1_IM13_Pos)                /*!< 0x00002000 */
#define EXTI_IMR1_IM13             EXTI_IMR1_IM13_Msk                          /*!< Interrupt Mask on line 13 */
#define EXTI_IMR1_IM14_Pos         (14U)
#define EXTI_IMR1_IM14_Msk         (0x1U << EXTI_IMR1_IM14_Pos)                /*!< 0x00004000 */
#define EXTI_IMR1_IM14             EXTI_IMR1_IM14_Msk                          /*!< Interrupt Mask on line 14 */
#define EXTI_IMR1_IM15_Pos         (15U)
#define EXTI_IMR1_IM15_Msk         (0x1U << EXTI_IMR1_IM15_Pos)                /*!< 0x00008000 */
#define EXTI_IMR1_IM15             EXTI_IMR1_IM15_Msk                          /*!< Interrupt Mask on line 15 */
#define EXTI_IMR1_IM16_Pos         (16U)
#define EXTI_IMR1_IM16_Msk         (0x1U << EXTI_IMR1_IM16_Pos)                /*!< 0x00010000 */
#define EXTI_IMR1_IM16             EXTI_IMR1_IM16_Msk                          /*!< Interrupt Mask on line 16 */
#define EXTI_IMR1_IM17_Pos         (17U)
#define EXTI_IMR1_IM17_Msk         (0x1U << EXTI_IMR1_IM17_Pos)                /*!< 0x00020000 */
#define EXTI_IMR1_IM17             EXTI_IMR1_IM17_Msk                          /*!< Interrupt Mask on line 17 */
#define EXTI_IMR1_IM18_Pos         (18U)
#define EXTI_IMR1_IM18_Msk         (0x1U << EXTI_IMR1_IM18_Pos)                /*!< 0x00040000 */
#define EXTI_IMR1_IM18             EXTI_IMR1_IM18_Msk                          /*!< Interrupt Mask on line 18 */
#define EXTI_IMR1_IM19_Pos         (19U)
#define EXTI_IMR1_IM19_Msk         (0x1U << EXTI_IMR1_IM19_Pos)                /*!< 0x00080000 */
#define EXTI_IMR1_IM19             EXTI_IMR1_IM19_Msk                          /*!< Interrupt Mask on line 19 */
#define EXTI_IMR1_IM20_Pos         (20U)
#define EXTI_IMR1_IM20_Msk         (0x1U << EXTI_IMR1_IM20_Pos)                /*!< 0x00100000 */
#define EXTI_IMR1_IM20             EXTI_IMR1_IM20_Msk                          /*!< Interrupt Mask on line 20 */
#define EXTI_IMR1_IM21_Pos         (21U)
#define EXTI_IMR1_IM21_Msk         (0x1U << EXTI_IMR1_IM21_Pos)                /*!< 0x00200000 */
#define EXTI_IMR1_IM21             EXTI_IMR1_IM21_Msk                          /*!< Interrupt Mask on line 21 */
#define EXTI_IMR1_IM22_Pos         (22U)
#define EXTI_IMR1_IM22_Msk         (0x1U << EXTI_IMR1_IM22_Pos)                /*!< 0x00400000 */
#define EXTI_IMR1_IM22             EXTI_IMR1_IM22_Msk                          /*!< Interrupt Mask on line 22 */
#define EXTI_IMR1_IM23_Pos         (23U)
#define EXTI_IMR1_IM23_Msk         (0x1U << EXTI_IMR1_IM23_Pos)                /*!< 0x00800000 */
#define EXTI_IMR1_IM23             EXTI_IMR1_IM23_Msk                          /*!< Interrupt Mask on line 23 */
#define EXTI_IMR1_IM24_Pos         (24U)
#define EXTI_IMR1_IM24_Msk         (0x1U << EXTI_IMR1_IM24_Pos)                /*!< 0x01000000 */
#define EXTI_IMR1_IM24             EXTI_IMR1_IM24_Msk                          /*!< Interrupt Mask on line 24 */
#define EXTI_IMR1_IM25_Pos         (25U)
#define EXTI_IMR1_IM25_Msk         (0x1U << EXTI_IMR1_IM25_Pos)                /*!< 0x02000000 */
#define EXTI_IMR1_IM25             EXTI_IMR1_IM25_Msk                          /*!< Interrupt Mask on line 25 */
#define EXTI_IMR1_IM26_Pos         (26U)
#define EXTI_IMR1_IM26_Msk         (0x1U << EXTI_IMR1_IM26_Pos)                /*!< 0x04000000 */
#define EXTI_IMR1_IM26             EXTI_IMR1_IM26_Msk                          /*!< Interrupt Mask on line 26 */
#define EXTI_IMR1_IM27_Pos         (27U)
#define EXTI_IMR1_IM27_Msk         (0x1U << EXTI_IMR1_IM27_Pos)                /*!< 0x08000000 */
#define EXTI_IMR1_IM27             EXTI_IMR1_IM27_Msk                          /*!< Interrupt Mask on line 27 */
#define EXTI_IMR1_IM28_Pos         (28U)
#define EXTI_IMR1_IM28_Msk         (0x1U << EXTI_IMR1_IM28_Pos)                /*!< 0x10000000 */
#define EXTI_IMR1_IM28             EXTI_IMR1_IM28_Msk                          /*!< Interrupt Mask on line 28 */
#define EXTI_IMR1_IM29_Pos         (29U)
#define EXTI_IMR1_IM29_Msk         (0x1U << EXTI_IMR1_IM29_Pos)                /*!< 0x20000000 */
#define EXTI_IMR1_IM29             EXTI_IMR1_IM29_Msk                          /*!< Interrupt Mask on line 29 */
#define EXTI_IMR1_IM30_Pos         (30U)
#define EXTI_IMR1_IM30_Msk         (0x1U << EXTI_IMR1_IM30_Pos)                /*!< 0x40000000 */
#define EXTI_IMR1_IM30             EXTI_IMR1_IM30_Msk                          /*!< Interrupt Mask on line 30 */
#define EXTI_IMR1_IM31_Pos         (31U)
#define EXTI_IMR1_IM31_Msk         (0x1U << EXTI_IMR1_IM31_Pos)                /*!< 0x80000000 */
#define EXTI_IMR1_IM31             EXTI_IMR1_IM31_Msk                          /*!< Interrupt Mask on line 31 */
/*******************  Bit definition for EXTI_IMR2 register  *******************/
#define EXTI_IMR2_IM32_Pos         (0U)
#define EXTI_IMR2_IM32_Msk         (0x1U << EXTI_IMR2_IM32_Pos)                /*!< 0x00000001 */
#define EXTI_IMR2_IM32             EXTI_IMR2_IM32_Msk                          /*!< Interrupt Mask on line 32 */
#define EXTI_IMR2_IM33_Pos         (1U)
#define EXTI_IMR2_IM33_Msk         (0x1U << EXTI_IMR2_IM33_Pos)                /*!< 0x00000002 */
#define EXTI_IMR2_IM33             EXTI_IMR2_IM33_Msk                          /*!< Interrupt Mask on line 33 */
#define EXTI_IMR2_IM34_Pos         (2U)
#define EXTI_IMR2_IM34_Msk         (0x1U << EXTI_IMR2_IM34_Pos)                /*!< 0x00000004 */
#define EXTI_IMR2_IM34             EXTI_IMR2_IM34_Msk                          /*!< Interrupt Mask on line 34 */
#define EXTI_IMR2_IM35_Pos         (3U)
#define EXTI_IMR2_IM35_Msk         (0x1U << EXTI_IMR2_IM35_Pos)                /*!< 0x00000008 */
#define EXTI_IMR2_IM35             EXTI_IMR2_IM35_Msk                          /*!< Interrupt Mask on line 35 */
#define EXTI_IMR2_IM36_Pos         (4U)
#define EXTI_IMR2_IM36_Msk         (0x1U << EXTI_IMR2_IM36_Pos)                /*!< 0x00000010 */
#define EXTI_IMR2_IM36             EXTI_IMR2_IM36_Msk                          /*!< Interrupt Mask on line 36 */
#define EXTI_IMR2_IM37_Pos         (5U)
#define EXTI_IMR2_IM37_Msk         (0x1U << EXTI_IMR2_IM37_Pos)                /*!< 0x00000020 */
#define EXTI_IMR2_IM37             EXTI_IMR2_IM37_Msk                          /*!< Interrupt Mask on line 37 */
#define EXTI_IMR2_IM38_Pos         (6U)
#define EXTI_IMR2_IM38_Msk         (0x1U << EXTI_IMR2_IM38_Pos)                /*!< 0x00000040 */
#define EXTI_IMR2_IM38             EXTI_IMR2_IM38_Msk                          /*!< Interrupt Mask on line 38 */
#define EXTI_IMR2_IM39_Pos         (7U)
#define EXTI_IMR2_IM39_Msk         (0x1U << EXTI_IMR2_IM39_Pos)                /*!< 0x00000080 */
#define EXTI_IMR2_IM39             EXTI_IMR2_IM39_Msk                          /*!< Interrupt Mask on line 39 */
#define EXTI_IMR2_IM40_Pos         (8U)
#define EXTI_IMR2_IM40_Msk         (0x1U << EXTI_IMR2_IM40_Pos)                /*!< 0x00000100 */
#define EXTI_IMR2_IM40             EXTI_IMR2_IM40_Msk                          /*!< Interrupt Mask on line 40 */
#define EXTI_IMR2_IM41_Pos         (9U)
#define EXTI_IMR2_IM41_Msk         (0x1U << EXTI_IMR2_IM41_Pos)                /*!< 0x00000200 */
#define EXTI_IMR2_IM41             EXTI_IMR2_IM41_Msk                          /*!< Interrupt Mask on line 41 */
#define EXTI_IMR2_IM42_Pos         (10U)
#define EXTI_IMR2_IM42_Msk         (0x1U << EXTI_IMR2_IM42_Pos)                /*!< 0x00000400 */
#define EXTI_IMR2_IM42             EXTI_IMR2_IM42_Msk                          /*!< Interrupt Mask on line 42 */
#define EXTI_IMR2_IM43_Pos         (11U)
#define EXTI_IMR2_IM43_Msk         (0x1U << EXTI_IMR2_IM43_Pos)                /*!< 0x00000800 */
#define EXTI_IMR2_IM43             EXTI_IMR2_IM43_Msk                          /*!< Interrupt Mask on line 43 */
#define EXTI_IMR2_IM44_Pos         (12U)
#define EXTI_IMR2_IM44_Msk         (0x1U << EXTI_IMR2_IM44_Pos)                /*!< 0x00001000 */
#define EXTI_IMR2_IM44             EXTI_IMR2_IM44_Msk                          /*!< Interrupt Mask on line 44 */
#define EXTI_IMR2_IM45_Pos         (13U)
#define EXTI_IMR2_IM45_Msk         (0x1U << EXTI_IMR2_IM45_Pos)                /*!< 0x00002000 */
#define EXTI_IMR2_IM45             EXTI_IMR2_IM45_Msk                          /*!< Interrupt Mask on line 45 */
#define EXTI_IMR2_IM46_Pos         (14U)
#define EXTI_IMR2_IM46_Msk         (0x1U << EXTI_IMR2_IM46_Pos)                /*!< 0x00004000 */
#define EXTI_IMR2_IM46             EXTI_IMR2_IM46_Msk                          /*!< Interrupt Mask on line 46 */
#define EXTI_IMR2_IM47_Pos         (15U)
#define EXTI_IMR2_IM47_Msk         (0x1U << EXTI_IMR2_IM47_Pos)                /*!< 0x00008000 */
#define EXTI_IMR2_IM47             EXTI_IMR2_IM47_Msk                          /*!< Interrupt Mask on line 47 */
#define EXTI_IMR2_IM48_Pos         (16U)
#define EXTI_IMR2_IM48_Msk         (0x1U << EXTI_IMR2_IM48_Pos)                /*!< 0x00010000 */
#define EXTI_IMR2_IM48             EXTI_IMR2_IM48_Msk                          /*!< Interrupt Mask on line 48 */
#define EXTI_IMR2_IM49_Pos         (17U)
#define EXTI_IMR2_IM49_Msk         (0x1U << EXTI_IMR2_IM49_Pos)                /*!< 0x00020000 */
#define EXTI_IMR2_IM49             EXTI_IMR2_IM49_Msk                          /*!< Interrupt Mask on line 49 */
#define EXTI_IMR2_IM50_Pos         (18U)
#define EXTI_IMR2_IM50_Msk         (0x1U << EXTI_IMR2_IM50_Pos)                /*!< 0x00040000 */
#define EXTI_IMR2_IM50             EXTI_IMR2_IM50_Msk                          /*!< Interrupt Mask on line 50 */
#define EXTI_IMR2_IM51_Pos         (19U)
#define EXTI_IMR2_IM51_Msk         (0x1U << EXTI_IMR2_IM51_Pos)                /*!< 0x00080000 */
#define EXTI_IMR2_IM51             EXTI_IMR2_IM51_Msk                          /*!< Interrupt Mask on line 51 */
#define EXTI_IMR2_IM52_Pos         (20U)
#define EXTI_IMR2_IM52_Msk         (0x1U << EXTI_IMR2_IM52_Pos)                /*!< 0x00100000 */
#define EXTI_IMR2_IM52             EXTI_IMR2_IM52_Msk                          /*!< Interrupt Mask on line 52 */
#define EXTI_IMR2_IM53_Pos         (21U)
#define EXTI_IMR2_IM53_Msk         (0x1U << EXTI_IMR2_IM53_Pos)                /*!< 0x00200000 */
#define EXTI_IMR2_IM53             EXTI_IMR2_IM53_Msk                          /*!< Interrupt Mask on line 53 */
#define EXTI_IMR2_IM54_Pos         (22U)
#define EXTI_IMR2_IM54_Msk         (0x1U << EXTI_IMR2_IM54_Pos)                /*!< 0x00400000 */
#define EXTI_IMR2_IM54             EXTI_IMR2_IM54_Msk                          /*!< Interrupt Mask on line 54 */
#define EXTI_IMR2_IM55_Pos         (23U)
#define EXTI_IMR2_IM55_Msk         (0x1U << EXTI_IMR2_IM55_Pos)                /*!< 0x00800000 */
#define EXTI_IMR2_IM55             EXTI_IMR2_IM55_Msk                          /*!< Interrupt Mask on line 55 */
#define EXTI_IMR2_IM56_Pos         (24U)
#define EXTI_IMR2_IM56_Msk         (0x1U << EXTI_IMR2_IM56_Pos)                /*!< 0x01000000 */
#define EXTI_IMR2_IM56             EXTI_IMR2_IM56_Msk                          /*!< Interrupt Mask on line 56 */
#define EXTI_IMR2_IM57_Pos         (25U)
#define EXTI_IMR2_IM57_Msk         (0x1U << EXTI_IMR2_IM57_Pos)                /*!< 0x02000000 */
#define EXTI_IMR2_IM57             EXTI_IMR2_IM57_Msk                          /*!< Interrupt Mask on line 57 */
#define EXTI_IMR2_IM58_Pos         (26U)
#define EXTI_IMR2_IM58_Msk         (0x1U << EXTI_IMR2_IM58_Pos)                /*!< 0x04000000 */
#define EXTI_IMR2_IM58             EXTI_IMR2_IM58_Msk                          /*!< Interrupt Mask on line 58 */
#define EXTI_IMR2_IM59_Pos         (27U)
#define EXTI_IMR2_IM59_Msk         (0x1U << EXTI_IMR2_IM59_Pos)                /*!< 0x08000000 */
#define EXTI_IMR2_IM59             EXTI_IMR2_IM59_Msk                          /*!< Interrupt Mask on line 59 */
#define EXTI_IMR2_IM60_Pos         (28U)
#define EXTI_IMR2_IM60_Msk         (0x1U << EXTI_IMR2_IM60_Pos)                /*!< 0x10000000 */
#define EXTI_IMR2_IM60             EXTI_IMR2_IM60_Msk                          /*!< Interrupt Mask on line 60 */
#define EXTI_IMR2_IM61_Pos         (29U)
#define EXTI_IMR2_IM61_Msk         (0x1U << EXTI_IMR2_IM61_Pos)                /*!< 0x20000000 */
#define EXTI_IMR2_IM61             EXTI_IMR2_IM61_Msk                          /*!< Interrupt Mask on line 61 */
#define EXTI_IMR2_IM62_Pos         (30U)
#define EXTI_IMR2_IM62_Msk         (0x1U << EXTI_IMR2_IM62_Pos)                /*!< 0x40000000 */
#define EXTI_IMR2_IM62             EXTI_IMR2_IM62_Msk                          /*!< Interrupt Mask on line 62 */
#define EXTI_IMR2_IM63_Pos         (31U)
#define EXTI_IMR2_IM63_Msk         (0x1U << EXTI_IMR2_IM63_Pos)                /*!< 0x80000000 */
#define EXTI_IMR2_IM63             EXTI_IMR2_IM63_Msk                          /*!< Interrupt Mask on line 63 */
/*******************  Bit definition for EXTI_IMR3 register  *******************/
#define EXTI_IMR3_IM64_Pos         (0U)
#define EXTI_IMR3_IM64_Msk         (0x1U << EXTI_IMR3_IM64_Pos)                /*!< 0x00000001 */
#define EXTI_IMR3_IM64             EXTI_IMR3_IM64_Msk                          /*!< Interrupt Mask on line 64 */
#define EXTI_IMR3_IM65_Pos         (1U)
#define EXTI_IMR3_IM65_Msk         (0x1U << EXTI_IMR3_IM65_Pos)                /*!< 0x00000002 */
#define EXTI_IMR3_IM65             EXTI_IMR3_IM65_Msk                          /*!< Interrupt Mask on line 65 */
#define EXTI_IMR3_IM66_Pos         (2U)
#define EXTI_IMR3_IM66_Msk         (0x1U << EXTI_IMR3_IM66_Pos)                /*!< 0x00000004 */
#define EXTI_IMR3_IM66             EXTI_IMR3_IM66_Msk                          /*!< Interrupt Mask on line 66 */
#define EXTI_IMR3_IM67_Pos         (3U)
#define EXTI_IMR3_IM67_Msk         (0x1U << EXTI_IMR3_IM67_Pos)                /*!< 0x00000008 */
#define EXTI_IMR3_IM67             EXTI_IMR3_IM67_Msk                          /*!< Interrupt Mask on line 67 */
#define EXTI_IMR3_IM68_Pos         (4U)
#define EXTI_IMR3_IM68_Msk         (0x1U << EXTI_IMR3_IM68_Pos)                /*!< 0x00000010 */
#define EXTI_IMR3_IM68             EXTI_IMR3_IM68_Msk                          /*!< Interrupt Mask on line 68 */
#define EXTI_IMR3_IM69_Pos         (5U)
#define EXTI_IMR3_IM69_Msk         (0x1U << EXTI_IMR3_IM69_Pos)                /*!< 0x00000020 */
#define EXTI_IMR3_IM69             EXTI_IMR3_IM69_Msk                          /*!< Interrupt Mask on line 69 */
#define EXTI_IMR3_IM70_Pos         (6U)
#define EXTI_IMR3_IM70_Msk         (0x1U << EXTI_IMR3_IM70_Pos)                /*!< 0x00000040 */
#define EXTI_IMR3_IM70             EXTI_IMR3_IM70_Msk                          /*!< Interrupt Mask on line 70 */
#define EXTI_IMR3_IM71_Pos         (7U)
#define EXTI_IMR3_IM71_Msk         (0x1U << EXTI_IMR3_IM71_Pos)                /*!< 0x00000080 */
#define EXTI_IMR3_IM71             EXTI_IMR3_IM71_Msk                          /*!< Interrupt Mask on line 71 */
#define EXTI_IMR3_IM72_Pos         (8U)
#define EXTI_IMR3_IM72_Msk         (0x1U << EXTI_IMR3_IM72_Pos)                /*!< 0x00000100 */
#define EXTI_IMR3_IM72             EXTI_IMR3_IM72_Msk                          /*!< Interrupt Mask on line 72 */
#define EXTI_IMR3_IM73_Pos         (9U)
#define EXTI_IMR3_IM73_Msk         (0x1U << EXTI_IMR3_IM73_Pos)                /*!< 0x00000200 */
#define EXTI_IMR3_IM73             EXTI_IMR3_IM73_Msk                          /*!< Interrupt Mask on line 73 */
#define EXTI_IMR3_IM74_Pos         (10U)
#define EXTI_IMR3_IM74_Msk         (0x1U << EXTI_IMR3_IM74_Pos)                /*!< 0x00000400 */
#define EXTI_IMR3_IM74             EXTI_IMR3_IM74_Msk                          /*!< Interrupt Mask on line 74 */
#define EXTI_IMR3_IM75_Pos         (11U)
#define EXTI_IMR3_IM75_Msk         (0x1U << EXTI_IMR3_IM75_Pos)                /*!< 0x00000800 */
#define EXTI_IMR3_IM75             EXTI_IMR3_IM75_Msk                          /*!< Interrupt Mask on line 75 */
#define EXTI_IMR3_IM76_Pos         (12U)
#define EXTI_IMR3_IM76_Msk         (0x1U << EXTI_IMR3_IM76_Pos)                /*!< 0x00001000 */
#define EXTI_IMR3_IM76             EXTI_IMR3_IM76_Msk                          /*!< Interrupt Mask on line 76 */
#define EXTI_IMR3_IM77_Pos         (13U)
#define EXTI_IMR3_IM77_Msk         (0x1U << EXTI_IMR3_IM77_Pos)                /*!< 0x00002000 */
#define EXTI_IMR3_IM77             EXTI_IMR3_IM77_Msk                          /*!< Interrupt Mask on line 77 */
#define EXTI_IMR3_IM78_Pos         (14U)
#define EXTI_IMR3_IM78_Msk         (0x1U << EXTI_IMR3_IM78_Pos)                /*!< 0x00004000 */
#define EXTI_IMR3_IM78             EXTI_IMR3_IM78_Msk                          /*!< Interrupt Mask on line 78 */
#define EXTI_IMR3_IM79_Pos         (15U)
#define EXTI_IMR3_IM79_Msk         (0x1U << EXTI_IMR3_IM79_Pos)                /*!< 0x00008000 */
#define EXTI_IMR3_IM79             EXTI_IMR3_IM79_Msk                          /*!< Interrupt Mask on line 79 */
#define EXTI_IMR3_IM80_Pos         (16U)
#define EXTI_IMR3_IM80_Msk         (0x1U << EXTI_IMR3_IM80_Pos)                /*!< 0x00010000 */
#define EXTI_IMR3_IM80             EXTI_IMR3_IM80_Msk                          /*!< Interrupt Mask on line 80 */
#define EXTI_IMR3_IM81_Pos         (17U)
#define EXTI_IMR3_IM81_Msk         (0x1U << EXTI_IMR3_IM81_Pos)                /*!< 0x00020000 */
#define EXTI_IMR3_IM81             EXTI_IMR3_IM81_Msk                          /*!< Interrupt Mask on line 81 */
#define EXTI_IMR3_IM82_Pos         (18U)
#define EXTI_IMR3_IM82_Msk         (0x1U << EXTI_IMR3_IM82_Pos)                /*!< 0x00040000 */
#define EXTI_IMR3_IM82             EXTI_IMR3_IM82_Msk                          /*!< Interrupt Mask on line 82 */
#define EXTI_IMR3_IM84_Pos         (20U)
#define EXTI_IMR3_IM84_Msk         (0x1U << EXTI_IMR3_IM84_Pos)                /*!< 0x00100000 */
#define EXTI_IMR3_IM84             EXTI_IMR3_IM84_Msk                          /*!< Interrupt Mask on line 84 */
#define EXTI_IMR3_IM85_Pos         (21U)
#define EXTI_IMR3_IM85_Msk         (0x1U << EXTI_IMR3_IM85_Pos)                /*!< 0x00200000 */
#define EXTI_IMR3_IM85             EXTI_IMR3_IM85_Msk                          /*!< Interrupt Mask on line 85 */
#define EXTI_IMR3_IM86_Pos         (22U)
#define EXTI_IMR3_IM86_Msk         (0x1U << EXTI_IMR3_IM86_Pos)                /*!< 0x00400000 */
#define EXTI_IMR3_IM86             EXTI_IMR3_IM86_Msk                          /*!< Interrupt Mask on line 86 */
#define EXTI_IMR3_IM87_Pos         (23U)
#define EXTI_IMR3_IM87_Msk         (0x1U << EXTI_IMR3_IM87_Pos)                /*!< 0x00800000 */
#define EXTI_IMR3_IM87             EXTI_IMR3_IM87_Msk                          /*!< Interrupt Mask on line 87 */
#define EXTI_IMR3_IM88_Pos         (24U)
#define EXTI_IMR3_IM88_Msk         (0x1U << EXTI_IMR3_IM88_Pos)                /*!< 0x01000000 */
#define EXTI_IMR3_IM88             EXTI_IMR3_IM88_Msk                          /*!< Interrupt Mask on line 88 */
/*******************  Bit definition for EXTI_EMR1 register  *******************/
#define EXTI_EMR1_EM0_Pos          (0U)
#define EXTI_EMR1_EM0_Msk          (0x1U << EXTI_EMR1_EM0_Pos)                 /*!< 0x00000001 */
#define EXTI_EMR1_EM0              EXTI_EMR1_EM0_Msk                           /*!< Event Mask on line 0 */
#define EXTI_EMR1_EM1_Pos          (1U)
#define EXTI_EMR1_EM1_Msk          (0x1U << EXTI_EMR1_EM1_Pos)                 /*!< 0x00000002 */
#define EXTI_EMR1_EM1              EXTI_EMR1_EM1_Msk                           /*!< Event Mask on line 1 */
#define EXTI_EMR1_EM2_Pos          (2U)
#define EXTI_EMR1_EM2_Msk          (0x1U << EXTI_EMR1_EM2_Pos)                 /*!< 0x00000004 */
#define EXTI_EMR1_EM2              EXTI_EMR1_EM2_Msk                           /*!< Event Mask on line 2 */
#define EXTI_EMR1_EM3_Pos          (3U)
#define EXTI_EMR1_EM3_Msk          (0x1U << EXTI_EMR1_EM3_Pos)                 /*!< 0x00000008 */
#define EXTI_EMR1_EM3              EXTI_EMR1_EM3_Msk                           /*!< Event Mask on line 3 */
#define EXTI_EMR1_EM4_Pos          (4U)
#define EXTI_EMR1_EM4_Msk          (0x1U << EXTI_EMR1_EM4_Pos)                 /*!< 0x00000010 */
#define EXTI_EMR1_EM4              EXTI_EMR1_EM4_Msk                           /*!< Event Mask on line 4 */
#define EXTI_EMR1_EM5_Pos          (5U)
#define EXTI_EMR1_EM5_Msk          (0x1U << EXTI_EMR1_EM5_Pos)                 /*!< 0x00000020 */
#define EXTI_EMR1_EM5              EXTI_EMR1_EM5_Msk                           /*!< Event Mask on line 5 */
#define EXTI_EMR1_EM6_Pos          (6U)
#define EXTI_EMR1_EM6_Msk          (0x1U << EXTI_EMR1_EM6_Pos)                 /*!< 0x00000040 */
#define EXTI_EMR1_EM6              EXTI_EMR1_EM6_Msk                           /*!< Event Mask on line 6 */
#define EXTI_EMR1_EM7_Pos          (7U)
#define EXTI_EMR1_EM7_Msk          (0x1U << EXTI_EMR1_EM7_Pos)                 /*!< 0x00000080 */
#define EXTI_EMR1_EM7              EXTI_EMR1_EM7_Msk                           /*!< Event Mask on line 7 */
#define EXTI_EMR1_EM8_Pos          (8U)
#define EXTI_EMR1_EM8_Msk          (0x1U << EXTI_EMR1_EM8_Pos)                 /*!< 0x00000100 */
#define EXTI_EMR1_EM8              EXTI_EMR1_EM8_Msk                           /*!< Event Mask on line 8 */
#define EXTI_EMR1_EM9_Pos          (9U)
#define EXTI_EMR1_EM9_Msk          (0x1U << EXTI_EMR1_EM9_Pos)                 /*!< 0x00000200 */
#define EXTI_EMR1_EM9              EXTI_EMR1_EM9_Msk                           /*!< Event Mask on line 9 */
#define EXTI_EMR1_EM10_Pos         (10U)
#define EXTI_EMR1_EM10_Msk         (0x1U << EXTI_EMR1_EM10_Pos)                /*!< 0x00000400 */
#define EXTI_EMR1_EM10             EXTI_EMR1_EM10_Msk                          /*!< Event Mask on line 10 */
#define EXTI_EMR1_EM11_Pos         (11U)
#define EXTI_EMR1_EM11_Msk         (0x1U << EXTI_EMR1_EM11_Pos)                /*!< 0x00000800 */
#define EXTI_EMR1_EM11             EXTI_EMR1_EM11_Msk                          /*!< Event Mask on line 11 */
#define EXTI_EMR1_EM12_Pos         (12U)
#define EXTI_EMR1_EM12_Msk         (0x1U << EXTI_EMR1_EM12_Pos)                /*!< 0x00001000 */
#define EXTI_EMR1_EM12             EXTI_EMR1_EM12_Msk                          /*!< Event Mask on line 12 */
#define EXTI_EMR1_EM13_Pos         (13U)
#define EXTI_EMR1_EM13_Msk         (0x1U << EXTI_EMR1_EM13_Pos)                /*!< 0x00002000 */
#define EXTI_EMR1_EM13             EXTI_EMR1_EM13_Msk                          /*!< Event Mask on line 13 */
#define EXTI_EMR1_EM14_Pos         (14U)
#define EXTI_EMR1_EM14_Msk         (0x1U << EXTI_EMR1_EM14_Pos)                /*!< 0x00004000 */
#define EXTI_EMR1_EM14             EXTI_EMR1_EM14_Msk                          /*!< Event Mask on line 14 */
#define EXTI_EMR1_EM15_Pos         (15U)
#define EXTI_EMR1_EM15_Msk         (0x1U << EXTI_EMR1_EM15_Pos)                /*!< 0x00008000 */
#define EXTI_EMR1_EM15             EXTI_EMR1_EM15_Msk                          /*!< Event Mask on line 15 */
#define EXTI_EMR1_EM16_Pos         (16U)
#define EXTI_EMR1_EM16_Msk         (0x1U << EXTI_EMR1_EM16_Pos)                /*!< 0x00010000 */
#define EXTI_EMR1_EM16             EXTI_EMR1_EM16_Msk                          /*!< Event Mask on line 16 */
#define EXTI_EMR1_EM17_Pos         (17U)
#define EXTI_EMR1_EM17_Msk         (0x1U << EXTI_EMR1_EM17_Pos)                /*!< 0x00020000 */
#define EXTI_EMR1_EM17             EXTI_EMR1_EM17_Msk                          /*!< Event Mask on line 17 */
#define EXTI_EMR1_EM18_Pos         (18U)
#define EXTI_EMR1_EM18_Msk         (0x1U << EXTI_EMR1_EM18_Pos)                /*!< 0x00040000 */
#define EXTI_EMR1_EM18             EXTI_EMR1_EM18_Msk                          /*!< Event Mask on line 18 */
#define EXTI_EMR1_EM20_Pos         (20U)
#define EXTI_EMR1_EM20_Msk         (0x1U << EXTI_EMR1_EM20_Pos)                /*!< 0x00100000 */
#define EXTI_EMR1_EM20             EXTI_EMR1_EM20_Msk                          /*!< Event Mask on line 20 */
#define EXTI_EMR1_EM21_Pos         (21U)
#define EXTI_EMR1_EM21_Msk         (0x1U << EXTI_EMR1_EM21_Pos)                /*!< 0x00200000 */
#define EXTI_EMR1_EM21             EXTI_EMR1_EM21_Msk                          /*!< Event Mask on line 21 */
#define EXTI_EMR1_EM22_Pos         (22U)
#define EXTI_EMR1_EM22_Msk         (0x1U << EXTI_EMR1_EM22_Pos)                /*!< 0x00400000 */
#define EXTI_EMR1_EM22             EXTI_EMR1_EM22_Msk                          /*!< Event Mask on line 22 */
#define EXTI_EMR1_EM23_Pos         (23U)
#define EXTI_EMR1_EM23_Msk         (0x1U << EXTI_EMR1_EM23_Pos)                /*!< 0x00800000 */
#define EXTI_EMR1_EM23             EXTI_EMR1_EM23_Msk                          /*!< Event Mask on line 23 */
#define EXTI_EMR1_EM24_Pos         (24U)
#define EXTI_EMR1_EM24_Msk         (0x1U << EXTI_EMR1_EM24_Pos)                /*!< 0x01000000 */
#define EXTI_EMR1_EM24             EXTI_EMR1_EM24_Msk                          /*!< Event Mask on line 24 */
#define EXTI_EMR1_EM25_Pos         (25U)
#define EXTI_EMR1_EM25_Msk         (0x1U << EXTI_EMR1_EM25_Pos)                /*!< 0x02000000 */
#define EXTI_EMR1_EM25             EXTI_EMR1_EM25_Msk                          /*!< Event Mask on line 25 */
#define EXTI_EMR1_EM26_Pos         (26U)
#define EXTI_EMR1_EM26_Msk         (0x1U << EXTI_EMR1_EM26_Pos)                /*!< 0x04000000 */
#define EXTI_EMR1_EM26             EXTI_EMR1_EM26_Msk                          /*!< Event Mask on line 26 */
#define EXTI_EMR1_EM27_Pos         (27U)
#define EXTI_EMR1_EM27_Msk         (0x1U << EXTI_EMR1_EM27_Pos)                /*!< 0x08000000 */
#define EXTI_EMR1_EM27             EXTI_EMR1_EM27_Msk                          /*!< Event Mask on line 27 */
#define EXTI_EMR1_EM28_Pos         (28U)
#define EXTI_EMR1_EM28_Msk         (0x1U << EXTI_EMR1_EM28_Pos)                /*!< 0x10000000 */
#define EXTI_EMR1_EM28             EXTI_EMR1_EM28_Msk                          /*!< Event Mask on line 28 */
#define EXTI_EMR1_EM29_Pos         (29U)
#define EXTI_EMR1_EM29_Msk         (0x1U << EXTI_EMR1_EM29_Pos)                /*!< 0x20000000 */
#define EXTI_EMR1_EM29             EXTI_EMR1_EM29_Msk                          /*!< Event Mask on line 29 */
#define EXTI_EMR1_EM30_Pos         (30U)
#define EXTI_EMR1_EM30_Msk         (0x1U << EXTI_EMR1_EM30_Pos)                /*!< 0x40000000 */
#define EXTI_EMR1_EM30             EXTI_EMR1_EM30_Msk                          /*!< Event Mask on line 30 */
#define EXTI_EMR1_EM31_Pos         (31U)
#define EXTI_EMR1_EM31_Msk         (0x1U << EXTI_EMR1_EM31_Pos)                /*!< 0x80000000 */
#define EXTI_EMR1_EM31             EXTI_EMR1_EM31_Msk                          /*!< Event Mask on line 31 */
/*******************  Bit definition for EXTI_EMR2 register  *******************/
#define EXTI_EMR2_EM32_Pos         (0U)
#define EXTI_EMR2_EM32_Msk         (0x1U << EXTI_EMR2_EM32_Pos)                /*!< 0x00000001 */
#define EXTI_EMR2_EM32             EXTI_EMR2_EM32_Msk                          /*!< Event Mask on line 32*/
#define EXTI_EMR2_EM33_Pos         (1U)
#define EXTI_EMR2_EM33_Msk         (0x1U << EXTI_EMR2_EM33_Pos)                /*!< 0x00000002 */
#define EXTI_EMR2_EM33             EXTI_EMR2_EM33_Msk                          /*!< Event Mask on line 33*/
#define EXTI_EMR2_EM34_Pos         (2U)
#define EXTI_EMR2_EM34_Msk         (0x1U << EXTI_EMR2_EM34_Pos)                /*!< 0x00000004 */
#define EXTI_EMR2_EM34             EXTI_EMR2_EM34_Msk                          /*!< Event Mask on line 34*/
#define EXTI_EMR2_EM35_Pos         (3U)
#define EXTI_EMR2_EM35_Msk         (0x1U << EXTI_EMR2_EM35_Pos)                /*!< 0x00000008 */
#define EXTI_EMR2_EM35             EXTI_EMR2_EM35_Msk                          /*!< Event Mask on line 35*/
#define EXTI_EMR2_EM36_Pos         (4U)
#define EXTI_EMR2_EM36_Msk         (0x1U << EXTI_EMR2_EM36_Pos)                /*!< 0x00000010 */
#define EXTI_EMR2_EM36             EXTI_EMR2_EM36_Msk                          /*!< Event Mask on line 36*/
#define EXTI_EMR2_EM37_Pos         (5U)
#define EXTI_EMR2_EM37_Msk         (0x1U << EXTI_EMR2_EM37_Pos)                /*!< 0x00000020 */
#define EXTI_EMR2_EM37             EXTI_EMR2_EM37_Msk                          /*!< Event Mask on line 37*/
#define EXTI_EMR2_EM38_Pos         (6U)
#define EXTI_EMR2_EM38_Msk         (0x1U << EXTI_EMR2_EM38_Pos)                /*!< 0x00000040 */
#define EXTI_EMR2_EM38             EXTI_EMR2_EM38_Msk                          /*!< Event Mask on line 38*/
#define EXTI_EMR2_EM39_Pos         (7U)
#define EXTI_EMR2_EM39_Msk         (0x1U << EXTI_EMR2_EM39_Pos)                /*!< 0x00000080 */
#define EXTI_EMR2_EM39             EXTI_EMR2_EM39_Msk                          /*!< Event Mask on line 39*/
#define EXTI_EMR2_EM40_Pos         (8U)
#define EXTI_EMR2_EM40_Msk         (0x1U << EXTI_EMR2_EM40_Pos)                /*!< 0x00000100 */
#define EXTI_EMR2_EM40             EXTI_EMR2_EM40_Msk                          /*!< Event Mask on line 40*/
#define EXTI_EMR2_EM41_Pos         (9U)
#define EXTI_EMR2_EM41_Msk         (0x1U << EXTI_EMR2_EM41_Pos)                /*!< 0x00000200 */
#define EXTI_EMR2_EM41             EXTI_EMR2_EM41_Msk                          /*!< Event Mask on line 41*/
#define EXTI_EMR2_EM42_Pos         (10U)
#define EXTI_EMR2_EM42_Msk         (0x1U << EXTI_EMR2_EM42_Pos)                /*!< 0x00000400 */
#define EXTI_EMR2_EM42             EXTI_EMR2_EM42_Msk                          /*!< Event Mask on line 42 */
#define EXTI_EMR2_EM43_Pos         (11U)
#define EXTI_EMR2_EM43_Msk         (0x1U << EXTI_EMR2_EM43_Pos)                /*!< 0x00000800 */
#define EXTI_EMR2_EM43             EXTI_EMR2_EM43_Msk                          /*!< Event Mask on line 43 */
#define EXTI_EMR2_EM44_Pos         (12U)
#define EXTI_EMR2_EM44_Msk         (0x1U << EXTI_EMR2_EM44_Pos)                /*!< 0x00001000 */
#define EXTI_EMR2_EM44             EXTI_EMR2_EM44_Msk                          /*!< Event Mask on line 44 */
#define EXTI_EMR2_EM45_Pos         (13U)
#define EXTI_EMR2_EM45_Msk         (0x1U << EXTI_EMR2_EM45_Pos)                /*!< 0x00002000 */
#define EXTI_EMR2_EM45             EXTI_EMR2_EM45_Msk                          /*!< Event Mask on line 45 */
#define EXTI_EMR2_EM46_Pos         (14U)
#define EXTI_EMR2_EM46_Msk         (0x1U << EXTI_EMR2_EM46_Pos)                /*!< 0x00004000 */
#define EXTI_EMR2_EM46             EXTI_EMR2_EM46_Msk                          /*!< Event Mask on line 46 */
#define EXTI_EMR2_EM47_Pos         (15U)
#define EXTI_EMR2_EM47_Msk         (0x1U << EXTI_EMR2_EM47_Pos)                /*!< 0x00008000 */
#define EXTI_EMR2_EM47             EXTI_EMR2_EM47_Msk                          /*!< Event Mask on line 47 */
#define EXTI_EMR2_EM48_Pos         (16U)
#define EXTI_EMR2_EM48_Msk         (0x1U << EXTI_EMR2_EM48_Pos)                /*!< 0x00010000 */
#define EXTI_EMR2_EM48             EXTI_EMR2_EM48_Msk                          /*!< Event Mask on line 48 */
#define EXTI_EMR2_EM49_Pos         (17U)
#define EXTI_EMR2_EM49_Msk         (0x1U << EXTI_EMR2_EM49_Pos)                /*!< 0x00020000 */
#define EXTI_EMR2_EM49             EXTI_EMR2_EM49_Msk                          /*!< Event Mask on line 49 */
#define EXTI_EMR2_EM50_Pos         (18U)
#define EXTI_EMR2_EM50_Msk         (0x1U << EXTI_EMR2_EM50_Pos)                /*!< 0x00040000 */
#define EXTI_EMR2_EM50             EXTI_EMR2_EM50_Msk                          /*!< Event Mask on line 50 */
#define EXTI_EMR2_EM51_Pos         (19U)
#define EXTI_EMR2_EM51_Msk         (0x1U << EXTI_EMR2_EM51_Pos)                /*!< 0x00080000 */
#define EXTI_EMR2_EM51             EXTI_EMR2_EM51_Msk                          /*!< Event Mask on line 51 */
#define EXTI_EMR2_EM52_Pos         (20U)
#define EXTI_EMR2_EM52_Msk         (0x1U << EXTI_EMR2_EM52_Pos)                /*!< 0x00100000 */
#define EXTI_EMR2_EM52             EXTI_EMR2_EM52_Msk                          /*!< Event Mask on line 52 */
#define EXTI_EMR2_EM53_Pos         (21U)
#define EXTI_EMR2_EM53_Msk         (0x1U << EXTI_EMR2_EM53_Pos)                /*!< 0x00200000 */
#define EXTI_EMR2_EM53             EXTI_EMR2_EM53_Msk                          /*!< Event Mask on line 53 */
#define EXTI_EMR2_EM54_Pos         (22U)
#define EXTI_EMR2_EM54_Msk         (0x1U << EXTI_EMR2_EM54_Pos)                /*!< 0x00400000 */
#define EXTI_EMR2_EM54             EXTI_EMR2_EM54_Msk                          /*!< Event Mask on line 54 */
#define EXTI_EMR2_EM55_Pos         (23U)
#define EXTI_EMR2_EM55_Msk         (0x1U << EXTI_EMR2_EM55_Pos)                /*!< 0x00800000 */
#define EXTI_EMR2_EM55             EXTI_EMR2_EM55_Msk                          /*!< Event Mask on line 55 */
#define EXTI_EMR2_EM56_Pos         (24U)
#define EXTI_EMR2_EM56_Msk         (0x1U << EXTI_EMR2_EM56_Pos)                /*!< 0x01000000 */
#define EXTI_EMR2_EM56             EXTI_EMR2_EM56_Msk                          /*!< Event Mask on line 56 */
#define EXTI_EMR2_EM57_Pos         (25U)
#define EXTI_EMR2_EM57_Msk         (0x1U << EXTI_EMR2_EM57_Pos)                /*!< 0x02000000 */
#define EXTI_EMR2_EM57             EXTI_EMR2_EM57_Msk                          /*!< Event Mask on line 57 */
#define EXTI_EMR2_EM58_Pos         (26U)
#define EXTI_EMR2_EM58_Msk         (0x1U << EXTI_EMR2_EM58_Pos)                /*!< 0x04000000 */
#define EXTI_EMR2_EM58             EXTI_EMR2_EM58_Msk                          /*!< Event Mask on line 58 */
#define EXTI_EMR2_EM59_Pos         (27U)
#define EXTI_EMR2_EM59_Msk         (0x1U << EXTI_EMR2_EM59_Pos)                /*!< 0x08000000 */
#define EXTI_EMR2_EM59             EXTI_EMR2_EM59_Msk                          /*!< Event Mask on line 59 */
#define EXTI_EMR2_EM60_Pos         (28U)
#define EXTI_EMR2_EM60_Msk         (0x1U << EXTI_EMR2_EM60_Pos)                /*!< 0x10000000 */
#define EXTI_EMR2_EM60             EXTI_EMR2_EM60_Msk                          /*!< Event Mask on line 60 */
#define EXTI_EMR2_EM61_Pos         (29U)
#define EXTI_EMR2_EM61_Msk         (0x1U << EXTI_EMR2_EM61_Pos)                /*!< 0x20000000 */
#define EXTI_EMR2_EM61             EXTI_EMR2_EM61_Msk                          /*!< Event Mask on line 61 */
#define EXTI_EMR2_EM62_Pos         (30U)
#define EXTI_EMR2_EM62_Msk         (0x1U << EXTI_EMR2_EM62_Pos)                /*!< 0x40000000 */
#define EXTI_EMR2_EM62             EXTI_EMR2_EM62_Msk                          /*!< Event Mask on line 62 */
#define EXTI_EMR2_EM63_Pos         (31U)
#define EXTI_EMR2_EM63_Msk         (0x1U << EXTI_EMR2_EM63_Pos)                /*!< 0x80000000 */
#define EXTI_EMR2_EM63             EXTI_EMR2_EM63_Msk                          /*!< Event Mask on line 63 */
/*******************  Bit definition for EXTI_EMR3 register  *******************/
#define EXTI_EMR3_EM64_Pos         (0U)
#define EXTI_EMR3_EM64_Msk         (0x1U << EXTI_EMR3_EM64_Pos)                /*!< 0x00000001 */
#define EXTI_EMR3_EM64             EXTI_EMR3_EM64_Msk                          /*!< Event Mask on line 64*/
#define EXTI_EMR3_EM65_Pos         (1U)
#define EXTI_EMR3_EM65_Msk         (0x1U << EXTI_EMR3_EM65_Pos)                /*!< 0x00000002 */
#define EXTI_EMR3_EM65             EXTI_EMR3_EM65_Msk                          /*!< Event Mask on line 65*/
#define EXTI_EMR3_EM66_Pos         (2U)
#define EXTI_EMR3_EM66_Msk         (0x1U << EXTI_EMR3_EM66_Pos)                /*!< 0x00000004 */
#define EXTI_EMR3_EM66             EXTI_EMR3_EM66_Msk                          /*!< Event Mask on line 66*/
#define EXTI_EMR3_EM67_Pos         (3U)
#define EXTI_EMR3_EM67_Msk         (0x1U << EXTI_EMR3_EM67_Pos)                /*!< 0x00000008 */
#define EXTI_EMR3_EM67             EXTI_EMR3_EM67_Msk                          /*!< Event Mask on line 67*/
#define EXTI_EMR3_EM68_Pos         (4U)
#define EXTI_EMR3_EM68_Msk         (0x1U << EXTI_EMR3_EM68_Pos)                /*!< 0x00000010 */
#define EXTI_EMR3_EM68             EXTI_EMR3_EM68_Msk                          /*!< Event Mask on line 68*/
#define EXTI_EMR3_EM69_Pos         (5U)
#define EXTI_EMR3_EM69_Msk         (0x1U << EXTI_EMR3_EM69_Pos)                /*!< 0x00000020 */
#define EXTI_EMR3_EM69             EXTI_EMR3_EM69_Msk                          /*!< Event Mask on line 69*/
#define EXTI_EMR3_EM70_Pos         (6U)
#define EXTI_EMR3_EM70_Msk         (0x1U << EXTI_EMR3_EM70_Pos)                /*!< 0x00000040 */
#define EXTI_EMR3_EM70             EXTI_EMR3_EM70_Msk                          /*!< Event Mask on line 70*/
#define EXTI_EMR3_EM71_Pos         (7U)
#define EXTI_EMR3_EM71_Msk         (0x1U << EXTI_EMR3_EM71_Pos)                /*!< 0x00000080 */
#define EXTI_EMR3_EM71             EXTI_EMR3_EM71_Msk                          /*!< Event Mask on line 71*/
#define EXTI_EMR3_EM72_Pos         (8U)
#define EXTI_EMR3_EM72_Msk         (0x1U << EXTI_EMR3_EM72_Pos)                /*!< 0x00000100 */
#define EXTI_EMR3_EM72             EXTI_EMR3_EM72_Msk                          /*!< Event Mask on line 72*/
#define EXTI_EMR3_EM73_Pos         (9U)
#define EXTI_EMR3_EM73_Msk         (0x1U << EXTI_EMR3_EM73_Pos)                /*!< 0x00000200 */
#define EXTI_EMR3_EM73             EXTI_EMR3_EM73_Msk                          /*!< Event Mask on line 73*/
#define EXTI_EMR3_EM74_Pos         (10U)
#define EXTI_EMR3_EM74_Msk         (0x1U << EXTI_EMR3_EM74_Pos)                /*!< 0x00000400 */
#define EXTI_EMR3_EM74             EXTI_EMR3_EM74_Msk                          /*!< Event Mask on line 74 */
#define EXTI_EMR3_EM75_Pos         (11U)
#define EXTI_EMR3_EM75_Msk         (0x1U << EXTI_EMR3_EM75_Pos)                /*!< 0x00000800 */
#define EXTI_EMR3_EM75             EXTI_EMR3_EM75_Msk                          /*!< Event Mask on line 75 */
#define EXTI_EMR3_EM76_Pos         (12U)
#define EXTI_EMR3_EM76_Msk         (0x1U << EXTI_EMR3_EM76_Pos)                /*!< 0x00001000 */
#define EXTI_EMR3_EM76             EXTI_EMR3_EM76_Msk                          /*!< Event Mask on line 76 */
#define EXTI_EMR3_EM77_Pos         (13U)
#define EXTI_EMR3_EM77_Msk         (0x1U << EXTI_EMR3_EM77_Pos)                /*!< 0x00002000 */
#define EXTI_EMR3_EM77             EXTI_EMR3_EM77_Msk                          /*!< Event Mask on line 77 */
#define EXTI_EMR3_EM78_Pos         (14U)
#define EXTI_EMR3_EM78_Msk         (0x1U << EXTI_EMR3_EM78_Pos)                /*!< 0x00004000 */
#define EXTI_EMR3_EM78             EXTI_EMR3_EM78_Msk                          /*!< Event Mask on line 78 */
#define EXTI_EMR3_EM79_Pos         (15U)
#define EXTI_EMR3_EM79_Msk         (0x1U << EXTI_EMR3_EM79_Pos)                /*!< 0x00008000 */
#define EXTI_EMR3_EM79             EXTI_EMR3_EM79_Msk                          /*!< Event Mask on line 79 */
#define EXTI_EMR3_EM80_Pos         (16U)
#define EXTI_EMR3_EM80_Msk         (0x1U << EXTI_EMR3_EM80_Pos)                /*!< 0x00010000 */
#define EXTI_EMR3_EM80             EXTI_EMR3_EM80_Msk                          /*!< Event Mask on line 80 */
#define EXTI_EMR3_EM81_Pos         (17U)
#define EXTI_EMR3_EM81_Msk         (0x1U << EXTI_EMR3_EM81_Pos)                /*!< 0x00020000 */
#define EXTI_EMR3_EM81             EXTI_EMR3_EM81_Msk                          /*!< Event Mask on line 81 */
#define EXTI_EMR3_EM82_Pos         (18U)
#define EXTI_EMR3_EM82_Msk         (0x1U << EXTI_EMR3_EM82_Pos)                /*!< 0x00040000 */
#define EXTI_EMR3_EM82             EXTI_EMR3_EM82_Msk                          /*!< Event Mask on line 82 */
#define EXTI_EMR3_EM84_Pos         (20U)
#define EXTI_EMR3_EM84_Msk         (0x1U << EXTI_EMR3_EM84_Pos)                /*!< 0x00100000 */
#define EXTI_EMR3_EM84             EXTI_EMR3_EM84_Msk                          /*!< Event Mask on line 84 */
#define EXTI_EMR3_EM85_Pos         (21U)
#define EXTI_EMR3_EM85_Msk         (0x1U << EXTI_EMR3_EM85_Pos)                /*!< 0x00200000 */
#define EXTI_EMR3_EM85             EXTI_EMR3_EM85_Msk                          /*!< Event Mask on line 85 */
#define EXTI_EMR3_EM86_Pos         (22U)
#define EXTI_EMR3_EM86_Msk         (0x1U << EXTI_EMR3_EM86_Pos)                /*!< 0x00400000 */
#define EXTI_EMR3_EM86             EXTI_EMR3_EM86_Msk                          /*!< Event Mask on line 86 */
#define EXTI_EMR3_EM87_Pos         (23U)
#define EXTI_EMR3_EM87_Msk         (0x1U << EXTI_EMR3_EM87_Pos)                /*!< 0x00800000 */
#define EXTI_EMR3_EM87             EXTI_EMR3_EM87_Msk                          /*!< Event Mask on line 87 */
#define EXTI_EMR3_EM88_Pos         (24U)
#define EXTI_EMR3_EM88_Msk         (0x1U << EXTI_EMR3_EM88_Pos)                /*!< 0x01000000 */
#define EXTI_EMR3_EM88             EXTI_EMR3_EM88_Msk                          /*!< Event Mask on line 88 */
/******************  Bit definition for EXTI_RTSR1 register  *******************/
#define EXTI_RTSR1_TR0_Pos         (0U)
#define EXTI_RTSR1_TR0_Msk         (0x1U << EXTI_RTSR1_TR0_Pos)                /*!< 0x00000001 */
#define EXTI_RTSR1_TR0             EXTI_RTSR1_TR0_Msk                          /*!< Rising trigger event configuration bit of line 0 */
#define EXTI_RTSR1_TR1_Pos         (1U)
#define EXTI_RTSR1_TR1_Msk         (0x1U << EXTI_RTSR1_TR1_Pos)                /*!< 0x00000002 */
#define EXTI_RTSR1_TR1             EXTI_RTSR1_TR1_Msk                          /*!< Rising trigger event configuration bit of line 1 */
#define EXTI_RTSR1_TR2_Pos         (2U)
#define EXTI_RTSR1_TR2_Msk         (0x1U << EXTI_RTSR1_TR2_Pos)                /*!< 0x00000004 */
#define EXTI_RTSR1_TR2             EXTI_RTSR1_TR2_Msk                          /*!< Rising trigger event configuration bit of line 2 */
#define EXTI_RTSR1_TR3_Pos         (3U)
#define EXTI_RTSR1_TR3_Msk         (0x1U << EXTI_RTSR1_TR3_Pos)                /*!< 0x00000008 */
#define EXTI_RTSR1_TR3             EXTI_RTSR1_TR3_Msk                          /*!< Rising trigger event configuration bit of line 3 */
#define EXTI_RTSR1_TR4_Pos         (4U)
#define EXTI_RTSR1_TR4_Msk         (0x1U << EXTI_RTSR1_TR4_Pos)                /*!< 0x00000010 */
#define EXTI_RTSR1_TR4             EXTI_RTSR1_TR4_Msk                          /*!< Rising trigger event configuration bit of line 4 */
#define EXTI_RTSR1_TR5_Pos         (5U)
#define EXTI_RTSR1_TR5_Msk         (0x1U << EXTI_RTSR1_TR5_Pos)                /*!< 0x00000020 */
#define EXTI_RTSR1_TR5             EXTI_RTSR1_TR5_Msk                          /*!< Rising trigger event configuration bit of line 5 */
#define EXTI_RTSR1_TR6_Pos         (6U)
#define EXTI_RTSR1_TR6_Msk         (0x1U << EXTI_RTSR1_TR6_Pos)                /*!< 0x00000040 */
#define EXTI_RTSR1_TR6             EXTI_RTSR1_TR6_Msk                          /*!< Rising trigger event configuration bit of line 6 */
#define EXTI_RTSR1_TR7_Pos         (7U)
#define EXTI_RTSR1_TR7_Msk         (0x1U << EXTI_RTSR1_TR7_Pos)                /*!< 0x00000080 */
#define EXTI_RTSR1_TR7             EXTI_RTSR1_TR7_Msk                          /*!< Rising trigger event configuration bit of line 7 */
#define EXTI_RTSR1_TR8_Pos         (8U)
#define EXTI_RTSR1_TR8_Msk         (0x1U << EXTI_RTSR1_TR8_Pos)                /*!< 0x00000100 */
#define EXTI_RTSR1_TR8             EXTI_RTSR1_TR8_Msk                          /*!< Rising trigger event configuration bit of line 8 */
#define EXTI_RTSR1_TR9_Pos         (9U)
#define EXTI_RTSR1_TR9_Msk         (0x1U << EXTI_RTSR1_TR9_Pos)                /*!< 0x00000200 */
#define EXTI_RTSR1_TR9             EXTI_RTSR1_TR9_Msk                          /*!< Rising trigger event configuration bit of line 9 */
#define EXTI_RTSR1_TR10_Pos        (10U)
#define EXTI_RTSR1_TR10_Msk        (0x1U << EXTI_RTSR1_TR10_Pos)               /*!< 0x00000400 */
#define EXTI_RTSR1_TR10            EXTI_RTSR1_TR10_Msk                         /*!< Rising trigger event configuration bit of line 10 */
#define EXTI_RTSR1_TR11_Pos        (11U)
#define EXTI_RTSR1_TR11_Msk        (0x1U << EXTI_RTSR1_TR11_Pos)               /*!< 0x00000800 */
#define EXTI_RTSR1_TR11            EXTI_RTSR1_TR11_Msk                         /*!< Rising trigger event configuration bit of line 11 */
#define EXTI_RTSR1_TR12_Pos        (12U)
#define EXTI_RTSR1_TR12_Msk        (0x1U << EXTI_RTSR1_TR12_Pos)               /*!< 0x00001000 */
#define EXTI_RTSR1_TR12            EXTI_RTSR1_TR12_Msk                         /*!< Rising trigger event configuration bit of line 12 */
#define EXTI_RTSR1_TR13_Pos        (13U)
#define EXTI_RTSR1_TR13_Msk        (0x1U << EXTI_RTSR1_TR13_Pos)               /*!< 0x00002000 */
#define EXTI_RTSR1_TR13            EXTI_RTSR1_TR13_Msk                         /*!< Rising trigger event configuration bit of line 13 */
#define EXTI_RTSR1_TR14_Pos        (14U)
#define EXTI_RTSR1_TR14_Msk        (0x1U << EXTI_RTSR1_TR14_Pos)               /*!< 0x00004000 */
#define EXTI_RTSR1_TR14            EXTI_RTSR1_TR14_Msk                         /*!< Rising trigger event configuration bit of line 14 */
#define EXTI_RTSR1_TR15_Pos        (15U)
#define EXTI_RTSR1_TR15_Msk        (0x1U << EXTI_RTSR1_TR15_Pos)               /*!< 0x00008000 */
#define EXTI_RTSR1_TR15            EXTI_RTSR1_TR15_Msk                         /*!< Rising trigger event configuration bit of line 15 */
#define EXTI_RTSR1_TR16_Pos        (16U)
#define EXTI_RTSR1_TR16_Msk        (0x1U << EXTI_RTSR1_TR16_Pos)               /*!< 0x00010000 */
#define EXTI_RTSR1_TR16            EXTI_RTSR1_TR16_Msk                         /*!< Rising trigger event configuration bit of line 16 */
#define EXTI_RTSR1_TR17_Pos        (17U)
#define EXTI_RTSR1_TR17_Msk        (0x1U << EXTI_RTSR1_TR17_Pos)               /*!< 0x00020000 */
#define EXTI_RTSR1_TR17            EXTI_RTSR1_TR17_Msk                         /*!< Rising trigger event configuration bit of line 17 */
#define EXTI_RTSR1_TR18_Pos        (18U)
#define EXTI_RTSR1_TR18_Msk        (0x1U << EXTI_RTSR1_TR18_Pos)               /*!< 0x00040000 */
#define EXTI_RTSR1_TR18            EXTI_RTSR1_TR18_Msk                         /*!< Rising trigger event configuration bit of line 18 */
#define EXTI_RTSR1_TR19_Pos        (19U)
#define EXTI_RTSR1_TR19_Msk        (0x1U << EXTI_RTSR1_TR19_Pos)               /*!< 0x00080000 */
#define EXTI_RTSR1_TR19            EXTI_RTSR1_TR19_Msk                         /*!< Rising trigger event configuration bit of line 19 */
#define EXTI_RTSR1_TR20_Pos        (20U)
#define EXTI_RTSR1_TR20_Msk        (0x1U << EXTI_RTSR1_TR20_Pos)               /*!< 0x00100000 */
#define EXTI_RTSR1_TR20            EXTI_RTSR1_TR20_Msk                         /*!< Rising trigger event configuration bit of line 20 */
#define EXTI_RTSR1_TR21_Pos        (21U)
#define EXTI_RTSR1_TR21_Msk        (0x1U << EXTI_RTSR1_TR21_Pos)               /*!< 0x00200000 */
#define EXTI_RTSR1_TR21            EXTI_RTSR1_TR21_Msk                         /*!< Rising trigger event configuration bit of line 21 */
/******************  Bit definition for EXTI_RTSR2 register  *******************/
#define EXTI_RTSR2_TR49_Pos        (17U)
#define EXTI_RTSR2_TR49_Msk        (0x1U << EXTI_RTSR2_TR49_Pos)               /*!< 0x00020000 */
#define EXTI_RTSR2_TR49            EXTI_RTSR2_TR49_Msk                         /*!< Rising trigger event configuration bit of line 49 */
#define EXTI_RTSR2_TR51_Pos        (19U)
#define EXTI_RTSR2_TR51_Msk        (0x1U << EXTI_RTSR2_TR51_Pos)               /*!< 0x00080000 */
#define EXTI_RTSR2_TR51            EXTI_RTSR2_TR51_Msk                         /*!< Rising trigger event configuration bit of line 51 */
/******************  Bit definition for EXTI_RTSR3 register  *******************/
#define EXTI_RTSR3_TR85_Pos        (21U)
#define EXTI_RTSR3_TR85_Msk        (0x1U << EXTI_RTSR3_TR85_Pos)               /*!< 0x00200000 */
#define EXTI_RTSR3_TR85            EXTI_RTSR3_TR85_Msk                         /*!< Rising trigger event configuration bit of line 85 */
#define EXTI_RTSR3_TR86_Pos        (22U)
#define EXTI_RTSR3_TR86_Msk        (0x1U << EXTI_RTSR3_TR86_Pos)               /*!< 0x00400000 */
#define EXTI_RTSR3_TR86            EXTI_RTSR3_TR86_Msk                         /*!< Rising trigger event configuration bit of line 86 */

/******************  Bit definition for EXTI_FTSR1 register  *******************/
#define EXTI_FTSR1_TR0_Pos         (0U)
#define EXTI_FTSR1_TR0_Msk         (0x1U << EXTI_FTSR1_TR0_Pos)                /*!< 0x00000001 */
#define EXTI_FTSR1_TR0             EXTI_FTSR1_TR0_Msk                          /*!< Falling trigger event configuration bit of line 0 */
#define EXTI_FTSR1_TR1_Pos         (1U)
#define EXTI_FTSR1_TR1_Msk         (0x1U << EXTI_FTSR1_TR1_Pos)                /*!< 0x00000002 */
#define EXTI_FTSR1_TR1             EXTI_FTSR1_TR1_Msk                          /*!< Falling trigger event configuration bit of line 1 */
#define EXTI_FTSR1_TR2_Pos         (2U)
#define EXTI_FTSR1_TR2_Msk         (0x1U << EXTI_FTSR1_TR2_Pos)                /*!< 0x00000004 */
#define EXTI_FTSR1_TR2             EXTI_FTSR1_TR2_Msk                          /*!< Falling trigger event configuration bit of line 2 */
#define EXTI_FTSR1_TR3_Pos         (3U)
#define EXTI_FTSR1_TR3_Msk         (0x1U << EXTI_FTSR1_TR3_Pos)                /*!< 0x00000008 */
#define EXTI_FTSR1_TR3             EXTI_FTSR1_TR3_Msk                          /*!< Falling trigger event configuration bit of line 3 */
#define EXTI_FTSR1_TR4_Pos         (4U)
#define EXTI_FTSR1_TR4_Msk         (0x1U << EXTI_FTSR1_TR4_Pos)                /*!< 0x00000010 */
#define EXTI_FTSR1_TR4             EXTI_FTSR1_TR4_Msk                          /*!< Falling trigger event configuration bit of line 4 */
#define EXTI_FTSR1_TR5_Pos         (5U)
#define EXTI_FTSR1_TR5_Msk         (0x1U << EXTI_FTSR1_TR5_Pos)                /*!< 0x00000020 */
#define EXTI_FTSR1_TR5             EXTI_FTSR1_TR5_Msk                          /*!< Falling trigger event configuration bit of line 5 */
#define EXTI_FTSR1_TR6_Pos         (6U)
#define EXTI_FTSR1_TR6_Msk         (0x1U << EXTI_FTSR1_TR6_Pos)                /*!< 0x00000040 */
#define EXTI_FTSR1_TR6             EXTI_FTSR1_TR6_Msk                          /*!< Falling trigger event configuration bit of line 6 */
#define EXTI_FTSR1_TR7_Pos         (7U)
#define EXTI_FTSR1_TR7_Msk         (0x1U << EXTI_FTSR1_TR7_Pos)                /*!< 0x00000080 */
#define EXTI_FTSR1_TR7             EXTI_FTSR1_TR7_Msk                          /*!< Falling trigger event configuration bit of line 7 */
#define EXTI_FTSR1_TR8_Pos         (8U)
#define EXTI_FTSR1_TR8_Msk         (0x1U << EXTI_FTSR1_TR8_Pos)                /*!< 0x00000100 */
#define EXTI_FTSR1_TR8             EXTI_FTSR1_TR8_Msk                          /*!< Falling trigger event configuration bit of line 8 */
#define EXTI_FTSR1_TR9_Pos         (9U)
#define EXTI_FTSR1_TR9_Msk         (0x1U << EXTI_FTSR1_TR9_Pos)                /*!< 0x00000200 */
#define EXTI_FTSR1_TR9             EXTI_FTSR1_TR9_Msk                          /*!< Falling trigger event configuration bit of line 9 */
#define EXTI_FTSR1_TR10_Pos        (10U)
#define EXTI_FTSR1_TR10_Msk        (0x1U << EXTI_FTSR1_TR10_Pos)               /*!< 0x00000400 */
#define EXTI_FTSR1_TR10            EXTI_FTSR1_TR10_Msk                         /*!< Falling trigger event configuration bit of line 10 */
#define EXTI_FTSR1_TR11_Pos        (11U)
#define EXTI_FTSR1_TR11_Msk        (0x1U << EXTI_FTSR1_TR11_Pos)               /*!< 0x00000800 */
#define EXTI_FTSR1_TR11            EXTI_FTSR1_TR11_Msk                         /*!< Falling trigger event configuration bit of line 11 */
#define EXTI_FTSR1_TR12_Pos        (12U)
#define EXTI_FTSR1_TR12_Msk        (0x1U << EXTI_FTSR1_TR12_Pos)               /*!< 0x00001000 */
#define EXTI_FTSR1_TR12            EXTI_FTSR1_TR12_Msk                         /*!< Falling trigger event configuration bit of line 12 */
#define EXTI_FTSR1_TR13_Pos        (13U)
#define EXTI_FTSR1_TR13_Msk        (0x1U << EXTI_FTSR1_TR13_Pos)               /*!< 0x00002000 */
#define EXTI_FTSR1_TR13            EXTI_FTSR1_TR13_Msk                         /*!< Falling trigger event configuration bit of line 13 */
#define EXTI_FTSR1_TR14_Pos        (14U)
#define EXTI_FTSR1_TR14_Msk        (0x1U << EXTI_FTSR1_TR14_Pos)               /*!< 0x00004000 */
#define EXTI_FTSR1_TR14            EXTI_FTSR1_TR14_Msk                         /*!< Falling trigger event configuration bit of line 14 */
#define EXTI_FTSR1_TR15_Pos        (15U)
#define EXTI_FTSR1_TR15_Msk        (0x1U << EXTI_FTSR1_TR15_Pos)               /*!< 0x00008000 */
#define EXTI_FTSR1_TR15            EXTI_FTSR1_TR15_Msk                         /*!< Falling trigger event configuration bit of line 15 */
#define EXTI_FTSR1_TR16_Pos        (16U)
#define EXTI_FTSR1_TR16_Msk        (0x1U << EXTI_FTSR1_TR16_Pos)               /*!< 0x00010000 */
#define EXTI_FTSR1_TR16            EXTI_FTSR1_TR16_Msk                         /*!< Falling trigger event configuration bit of line 16 */
#define EXTI_FTSR1_TR17_Pos        (17U)
#define EXTI_FTSR1_TR17_Msk        (0x1U << EXTI_FTSR1_TR17_Pos)               /*!< 0x00020000 */
#define EXTI_FTSR1_TR17            EXTI_FTSR1_TR17_Msk                         /*!< Falling trigger event configuration bit of line 17 */
#define EXTI_FTSR1_TR18_Pos        (18U)
#define EXTI_FTSR1_TR18_Msk        (0x1U << EXTI_FTSR1_TR18_Pos)               /*!< 0x00040000 */
#define EXTI_FTSR1_TR18            EXTI_FTSR1_TR18_Msk                         /*!< Falling trigger event configuration bit of line 18 */
#define EXTI_FTSR1_TR19_Pos        (19U)
#define EXTI_FTSR1_TR19_Msk        (0x1U << EXTI_FTSR1_TR19_Pos)               /*!< 0x00080000 */
#define EXTI_FTSR1_TR19            EXTI_FTSR1_TR19_Msk                         /*!< Falling trigger event configuration bit of line 19 */
#define EXTI_FTSR1_TR20_Pos        (20U)
#define EXTI_FTSR1_TR20_Msk        (0x1U << EXTI_FTSR1_TR20_Pos)               /*!< 0x00100000 */
#define EXTI_FTSR1_TR20            EXTI_FTSR1_TR20_Msk                         /*!< Falling trigger event configuration bit of line 20 */
#define EXTI_FTSR1_TR21_Pos        (21U)
#define EXTI_FTSR1_TR21_Msk        (0x1U << EXTI_FTSR1_TR21_Pos)               /*!< 0x00200000 */
#define EXTI_FTSR1_TR21            EXTI_FTSR1_TR21_Msk                         /*!< Falling trigger event configuration bit of line 21 */
/******************  Bit definition for EXTI_FTSR2 register  *******************/
#define EXTI_FTSR2_TR49_Pos        (17U)
#define EXTI_FTSR2_TR49_Msk        (0x1U << EXTI_FTSR2_TR49_Pos)               /*!< 0x00020000 */
#define EXTI_FTSR2_TR49            EXTI_FTSR2_TR49_Msk                         /*!< Falling trigger event configuration bit of line 49 */
#define EXTI_FTSR2_TR51_Pos        (19U)
#define EXTI_FTSR2_TR51_Msk        (0x1U << EXTI_FTSR2_TR51_Pos)               /*!< 0x00080000 */
#define EXTI_FTSR2_TR51            EXTI_FTSR2_TR51_Msk                         /*!< Falling trigger event configuration bit of line 51 */

/******************  Bit definition for EXTI_FTSR3 register  *******************/
#define EXTI_FTSR3_TR85_Pos        (21U)
#define EXTI_FTSR3_TR85_Msk        (0x1U << EXTI_FTSR3_TR85_Pos)               /*!< 0x00200000 */
#define EXTI_FTSR3_TR85            EXTI_FTSR3_TR85_Msk                         /*!< Falling trigger event configuration bit of line 85 */
#define EXTI_FTSR3_TR86_Pos        (22U)
#define EXTI_FTSR3_TR86_Msk        (0x1U << EXTI_FTSR3_TR86_Pos)               /*!< 0x00400000 */
#define EXTI_FTSR3_TR86            EXTI_FTSR3_TR86_Msk                         /*!< Falling trigger event configuration bit of line 86 */
/******************  Bit definition for EXTI_SWIER1 register  ******************/
#define EXTI_SWIER1_SWIER0_Pos     (0U)
#define EXTI_SWIER1_SWIER0_Msk     (0x1U << EXTI_SWIER1_SWIER0_Pos)            /*!< 0x00000001 */
#define EXTI_SWIER1_SWIER0         EXTI_SWIER1_SWIER0_Msk                      /*!< Software Interrupt on line 0 */
#define EXTI_SWIER1_SWIER1_Pos     (1U)
#define EXTI_SWIER1_SWIER1_Msk     (0x1U << EXTI_SWIER1_SWIER1_Pos)            /*!< 0x00000002 */
#define EXTI_SWIER1_SWIER1         EXTI_SWIER1_SWIER1_Msk                      /*!< Software Interrupt on line 1 */
#define EXTI_SWIER1_SWIER2_Pos     (2U)
#define EXTI_SWIER1_SWIER2_Msk     (0x1U << EXTI_SWIER1_SWIER2_Pos)            /*!< 0x00000004 */
#define EXTI_SWIER1_SWIER2         EXTI_SWIER1_SWIER2_Msk                      /*!< Software Interrupt on line 2 */
#define EXTI_SWIER1_SWIER3_Pos     (3U)
#define EXTI_SWIER1_SWIER3_Msk     (0x1U << EXTI_SWIER1_SWIER3_Pos)            /*!< 0x00000008 */
#define EXTI_SWIER1_SWIER3         EXTI_SWIER1_SWIER3_Msk                      /*!< Software Interrupt on line 3 */
#define EXTI_SWIER1_SWIER4_Pos     (4U)
#define EXTI_SWIER1_SWIER4_Msk     (0x1U << EXTI_SWIER1_SWIER4_Pos)            /*!< 0x00000010 */
#define EXTI_SWIER1_SWIER4         EXTI_SWIER1_SWIER4_Msk                      /*!< Software Interrupt on line 4 */
#define EXTI_SWIER1_SWIER5_Pos     (5U)
#define EXTI_SWIER1_SWIER5_Msk     (0x1U << EXTI_SWIER1_SWIER5_Pos)            /*!< 0x00000020 */
#define EXTI_SWIER1_SWIER5         EXTI_SWIER1_SWIER5_Msk                      /*!< Software Interrupt on line 5 */
#define EXTI_SWIER1_SWIER6_Pos     (6U)
#define EXTI_SWIER1_SWIER6_Msk     (0x1U << EXTI_SWIER1_SWIER6_Pos)            /*!< 0x00000040 */
#define EXTI_SWIER1_SWIER6         EXTI_SWIER1_SWIER6_Msk                      /*!< Software Interrupt on line 6 */
#define EXTI_SWIER1_SWIER7_Pos     (7U)
#define EXTI_SWIER1_SWIER7_Msk     (0x1U << EXTI_SWIER1_SWIER7_Pos)            /*!< 0x00000080 */
#define EXTI_SWIER1_SWIER7         EXTI_SWIER1_SWIER7_Msk                      /*!< Software Interrupt on line 7 */
#define EXTI_SWIER1_SWIER8_Pos     (8U)
#define EXTI_SWIER1_SWIER8_Msk     (0x1U << EXTI_SWIER1_SWIER8_Pos)            /*!< 0x00000100 */
#define EXTI_SWIER1_SWIER8         EXTI_SWIER1_SWIER8_Msk                      /*!< Software Interrupt on line 8 */
#define EXTI_SWIER1_SWIER9_Pos     (9U)
#define EXTI_SWIER1_SWIER9_Msk     (0x1U << EXTI_SWIER1_SWIER9_Pos)            /*!< 0x00000200 */
#define EXTI_SWIER1_SWIER9         EXTI_SWIER1_SWIER9_Msk                      /*!< Software Interrupt on line 9 */
#define EXTI_SWIER1_SWIER10_Pos    (10U)
#define EXTI_SWIER1_SWIER10_Msk    (0x1U << EXTI_SWIER1_SWIER10_Pos)           /*!< 0x00000400 */
#define EXTI_SWIER1_SWIER10        EXTI_SWIER1_SWIER10_Msk                     /*!< Software Interrupt on line 10 */
#define EXTI_SWIER1_SWIER11_Pos    (11U)
#define EXTI_SWIER1_SWIER11_Msk    (0x1U << EXTI_SWIER1_SWIER11_Pos)           /*!< 0x00000800 */
#define EXTI_SWIER1_SWIER11        EXTI_SWIER1_SWIER11_Msk                     /*!< Software Interrupt on line 11 */
#define EXTI_SWIER1_SWIER12_Pos    (12U)
#define EXTI_SWIER1_SWIER12_Msk    (0x1U << EXTI_SWIER1_SWIER12_Pos)           /*!< 0x00001000 */
#define EXTI_SWIER1_SWIER12        EXTI_SWIER1_SWIER12_Msk                     /*!< Software Interrupt on line 12 */
#define EXTI_SWIER1_SWIER13_Pos    (13U)
#define EXTI_SWIER1_SWIER13_Msk    (0x1U << EXTI_SWIER1_SWIER13_Pos)           /*!< 0x00002000 */
#define EXTI_SWIER1_SWIER13        EXTI_SWIER1_SWIER13_Msk                     /*!< Software Interrupt on line 13 */
#define EXTI_SWIER1_SWIER14_Pos    (14U)
#define EXTI_SWIER1_SWIER14_Msk    (0x1U << EXTI_SWIER1_SWIER14_Pos)           /*!< 0x00004000 */
#define EXTI_SWIER1_SWIER14        EXTI_SWIER1_SWIER14_Msk                     /*!< Software Interrupt on line 14 */
#define EXTI_SWIER1_SWIER15_Pos    (15U)
#define EXTI_SWIER1_SWIER15_Msk    (0x1U << EXTI_SWIER1_SWIER15_Pos)           /*!< 0x00008000 */
#define EXTI_SWIER1_SWIER15        EXTI_SWIER1_SWIER15_Msk                     /*!< Software Interrupt on line 15 */
#define EXTI_SWIER1_SWIER16_Pos    (16U)
#define EXTI_SWIER1_SWIER16_Msk    (0x1U << EXTI_SWIER1_SWIER16_Pos)           /*!< 0x00010000 */
#define EXTI_SWIER1_SWIER16        EXTI_SWIER1_SWIER16_Msk                     /*!< Software Interrupt on line 16 */
#define EXTI_SWIER1_SWIER17_Pos    (17U)
#define EXTI_SWIER1_SWIER17_Msk    (0x1U << EXTI_SWIER1_SWIER17_Pos)           /*!< 0x00020000 */
#define EXTI_SWIER1_SWIER17        EXTI_SWIER1_SWIER17_Msk                     /*!< Software Interrupt on line 17 */
#define EXTI_SWIER1_SWIER18_Pos    (18U)
#define EXTI_SWIER1_SWIER18_Msk    (0x1U << EXTI_SWIER1_SWIER18_Pos)           /*!< 0x00040000 */
#define EXTI_SWIER1_SWIER18        EXTI_SWIER1_SWIER18_Msk                     /*!< Software Interrupt on line 18 */
#define EXTI_SWIER1_SWIER19_Pos    (19U)
#define EXTI_SWIER1_SWIER19_Msk    (0x1U << EXTI_SWIER1_SWIER19_Pos)           /*!< 0x00080000 */
#define EXTI_SWIER1_SWIER19        EXTI_SWIER1_SWIER19_Msk                     /*!< Software Interrupt on line 19 */
#define EXTI_SWIER1_SWIER20_Pos    (20U)
#define EXTI_SWIER1_SWIER20_Msk    (0x1U << EXTI_SWIER1_SWIER20_Pos)           /*!< 0x00100000 */
#define EXTI_SWIER1_SWIER20        EXTI_SWIER1_SWIER20_Msk                     /*!< Software Interrupt on line 20 */
#define EXTI_SWIER1_SWIER21_Pos    (21U)
#define EXTI_SWIER1_SWIER21_Msk    (0x1U << EXTI_SWIER1_SWIER21_Pos)           /*!< 0x00200000 */
#define EXTI_SWIER1_SWIER21        EXTI_SWIER1_SWIER21_Msk                     /*!< Software Interrupt on line 21 */

/******************  Bit definition for EXTI_SWIER2 register  ******************/
#define EXTI_SWIER2_SWIER49_Pos    (17U)
#define EXTI_SWIER2_SWIER49_Msk    (0x1U << EXTI_SWIER2_SWIER49_Pos)           /*!< 0x00020000 */
#define EXTI_SWIER2_SWIER49        EXTI_SWIER2_SWIER49_Msk                     /*!< Software Interrupt on line 49 */
#define EXTI_SWIER2_SWIER51_Pos    (19U)
#define EXTI_SWIER2_SWIER51_Msk    (0x1U << EXTI_SWIER2_SWIER51_Pos)           /*!< 0x00080000 */
#define EXTI_SWIER2_SWIER51        EXTI_SWIER2_SWIER51_Msk                     /*!< Software Interrupt on line 51 */

/******************  Bit definition for EXTI_SWIER3 register  ******************/
#define EXTI_SWIER3_SWIER85_Pos    (21U)
#define EXTI_SWIER3_SWIER85_Msk    (0x1U << EXTI_SWIER3_SWIER85_Pos)           /*!< 0x00200000 */
#define EXTI_SWIER3_SWIER85        EXTI_SWIER3_SWIER85_Msk                     /*!< Software Interrupt on line 85 */
#define EXTI_SWIER3_SWIER86_Pos    (22U)
#define EXTI_SWIER3_SWIER86_Msk    (0x1U << EXTI_SWIER3_SWIER86_Pos)           /*!< 0x00400000 */
#define EXTI_SWIER3_SWIER86        EXTI_SWIER3_SWIER86_Msk                     /*!< Software Interrupt on line 86 */

/*******************  Bit definition for EXTI_PR1 register  ********************/
#define EXTI_PR1_PR0_Pos           (0U)
#define EXTI_PR1_PR0_Msk           (0x1U << EXTI_PR1_PR0_Pos)                  /*!< 0x00000001 */
#define EXTI_PR1_PR0               EXTI_PR1_PR0_Msk                            /*!< Pending bit for line 0 */
#define EXTI_PR1_PR1_Pos           (1U)
#define EXTI_PR1_PR1_Msk           (0x1U << EXTI_PR1_PR1_Pos)                  /*!< 0x00000002 */
#define EXTI_PR1_PR1               EXTI_PR1_PR1_Msk                            /*!< Pending bit for line 1 */
#define EXTI_PR1_PR2_Pos           (2U)
#define EXTI_PR1_PR2_Msk           (0x1U << EXTI_PR1_PR2_Pos)                  /*!< 0x00000004 */
#define EXTI_PR1_PR2               EXTI_PR1_PR2_Msk                            /*!< Pending bit for line 2 */
#define EXTI_PR1_PR3_Pos           (3U)
#define EXTI_PR1_PR3_Msk           (0x1U << EXTI_PR1_PR3_Pos)                  /*!< 0x00000008 */
#define EXTI_PR1_PR3               EXTI_PR1_PR3_Msk                            /*!< Pending bit for line 3 */
#define EXTI_PR1_PR4_Pos           (4U)
#define EXTI_PR1_PR4_Msk           (0x1U << EXTI_PR1_PR4_Pos)                  /*!< 0x00000010 */
#define EXTI_PR1_PR4               EXTI_PR1_PR4_Msk                            /*!< Pending bit for line 4 */
#define EXTI_PR1_PR5_Pos           (5U)
#define EXTI_PR1_PR5_Msk           (0x1U << EXTI_PR1_PR5_Pos)                  /*!< 0x00000020 */
#define EXTI_PR1_PR5               EXTI_PR1_PR5_Msk                            /*!< Pending bit for line 5 */
#define EXTI_PR1_PR6_Pos           (6U)
#define EXTI_PR1_PR6_Msk           (0x1U << EXTI_PR1_PR6_Pos)                  /*!< 0x00000040 */
#define EXTI_PR1_PR6               EXTI_PR1_PR6_Msk                            /*!< Pending bit for line 6 */
#define EXTI_PR1_PR7_Pos           (7U)
#define EXTI_PR1_PR7_Msk           (0x1U << EXTI_PR1_PR7_Pos)                  /*!< 0x00000080 */
#define EXTI_PR1_PR7               EXTI_PR1_PR7_Msk                            /*!< Pending bit for line 7 */
#define EXTI_PR1_PR8_Pos           (8U)
#define EXTI_PR1_PR8_Msk           (0x1U << EXTI_PR1_PR8_Pos)                  /*!< 0x00000100 */
#define EXTI_PR1_PR8               EXTI_PR1_PR8_Msk                            /*!< Pending bit for line 8 */
#define EXTI_PR1_PR9_Pos           (9U)
#define EXTI_PR1_PR9_Msk           (0x1U << EXTI_PR1_PR9_Pos)                  /*!< 0x00000200 */
#define EXTI_PR1_PR9               EXTI_PR1_PR9_Msk                            /*!< Pending bit for line 9 */
#define EXTI_PR1_PR10_Pos          (10U)
#define EXTI_PR1_PR10_Msk          (0x1U << EXTI_PR1_PR10_Pos)                 /*!< 0x00000400 */
#define EXTI_PR1_PR10              EXTI_PR1_PR10_Msk                           /*!< Pending bit for line 10 */
#define EXTI_PR1_PR11_Pos          (11U)
#define EXTI_PR1_PR11_Msk          (0x1U << EXTI_PR1_PR11_Pos)                 /*!< 0x00000800 */
#define EXTI_PR1_PR11              EXTI_PR1_PR11_Msk                           /*!< Pending bit for line 11 */
#define EXTI_PR1_PR12_Pos          (12U)
#define EXTI_PR1_PR12_Msk          (0x1U << EXTI_PR1_PR12_Pos)                 /*!< 0x00001000 */
#define EXTI_PR1_PR12              EXTI_PR1_PR12_Msk                           /*!< Pending bit for line 12 */
#define EXTI_PR1_PR13_Pos          (13U)
#define EXTI_PR1_PR13_Msk          (0x1U << EXTI_PR1_PR13_Pos)                 /*!< 0x00002000 */
#define EXTI_PR1_PR13              EXTI_PR1_PR13_Msk                           /*!< Pending bit for line 13 */
#define EXTI_PR1_PR14_Pos          (14U)
#define EXTI_PR1_PR14_Msk          (0x1U << EXTI_PR1_PR14_Pos)                 /*!< 0x00004000 */
#define EXTI_PR1_PR14              EXTI_PR1_PR14_Msk                           /*!< Pending bit for line 14 */
#define EXTI_PR1_PR15_Pos          (15U)
#define EXTI_PR1_PR15_Msk          (0x1U << EXTI_PR1_PR15_Pos)                 /*!< 0x00008000 */
#define EXTI_PR1_PR15              EXTI_PR1_PR15_Msk                           /*!< Pending bit for line 15 */
#define EXTI_PR1_PR16_Pos          (16U)
#define EXTI_PR1_PR16_Msk          (0x1U << EXTI_PR1_PR16_Pos)                 /*!< 0x00010000 */
#define EXTI_PR1_PR16              EXTI_PR1_PR16_Msk                           /*!< Pending bit for line 16 */

/*******************  Bit definition for EXTI_PR3 register  ********************/
#define EXTI_PR3_PR65_Pos          (1U)
#define EXTI_PR3_PR65_Msk          (0x1U << EXTI_PR3_PR65_Pos)                 /*!< 0x00000002 */
#define EXTI_PR3_PR65              EXTI_PR3_PR65_Msk                           /*!< Pending bit for line 65 */
#define EXTI_PR3_PR66_Pos          (2U)
#define EXTI_PR3_PR66_Msk          (0x1U << EXTI_PR3_PR66_Pos)                 /*!< 0x00000004 */
#define EXTI_PR3_PR66              EXTI_PR3_PR66_Msk                           /*!< Pending bit for line 66 */
#define EXTI_PR3_PR68_Pos          (4U)
#define EXTI_PR3_PR68_Msk          (0x1U << EXTI_PR3_PR68_Pos)                 /*!< 0x00000010 */
#define EXTI_PR3_PR68              EXTI_PR3_PR68_Msk                           /*!< Pending bit for line 68 */
#define EXTI_PR3_PR73_Pos          (9U)
#define EXTI_PR3_PR73_Msk          (0x1U << EXTI_PR3_PR73_Pos)                 /*!< 0x00000200 */
#define EXTI_PR3_PR73              EXTI_PR3_PR73_Msk                           /*!< Pending bit for line 73 */
#define EXTI_PR3_PR74_Pos          (10U)
#define EXTI_PR3_PR74_Msk          (0x1U << EXTI_PR3_PR74_Pos)                 /*!< 0x00000400 */
#define EXTI_PR3_PR74              EXTI_PR3_PR74_Msk                           /*!< Pending bit for line 74 */

/*****************  Bit definition for EXTI_EXTICR1 register  ***************/
#define EXTI_EXTICR1_EXTI0_Pos        (0U)
#define EXTI_EXTICR1_EXTI0_Msk        (0x0FU << EXTI_EXTICR1_EXTI0_Pos)        /*!< 0x0000000F */
#define EXTI_EXTICR1_EXTI0            EXTI_EXTICR1_EXTI0_Msk                   /*!<EXTI 0 configuration */
#define EXTI_EXTICR1_EXTI1_Pos        (8U)
#define EXTI_EXTICR1_EXTI1_Msk        (0x0FU << EXTI_EXTICR1_EXTI1_Pos)        /*!< 0x00000F00 */
#define EXTI_EXTICR1_EXTI1            EXTI_EXTICR1_EXTI1_Msk                   /*!<EXTI 1 configuration */
#define EXTI_EXTICR1_EXTI2_Pos        (16U)
#define EXTI_EXTICR1_EXTI2_Msk        (0x0FU << EXTI_EXTICR1_EXTI2_Pos)        /*!< 0x000F0000 */
#define EXTI_EXTICR1_EXTI2            EXTI_EXTICR1_EXTI2_Msk                   /*!<EXTI 2 configuration */
#define EXTI_EXTICR1_EXTI3_Pos        (24U)
#define EXTI_EXTICR1_EXTI3_Msk        (0x0FU << EXTI_EXTICR1_EXTI3_Pos)        /*!< 0x0F000000 */
#define EXTI_EXTICR1_EXTI3            EXTI_EXTICR1_EXTI3_Msk                   /*!<EXTI 3 configuration */
/**
  * @brief   EXTI0 configuration
  */
#define EXTI_EXTICR1_EXTI0_PA         ((uint32_t)0x00000000)                   /*!<PA[0] pin */
#define EXTI_EXTICR1_EXTI0_PB_Pos     (0U)
#define EXTI_EXTICR1_EXTI0_PB_Msk     (0x1U << EXTI_EXTICR1_EXTI0_PB_Pos)      /*!< 0x00000001 */
#define EXTI_EXTICR1_EXTI0_PB         EXTI_EXTICR1_EXTI0_PB_Msk                /*!<PB[0] pin */
#define EXTI_EXTICR1_EXTI0_PC_Pos     (1U)
#define EXTI_EXTICR1_EXTI0_PC_Msk     (0x1U << EXTI_EXTICR1_EXTI0_PC_Pos)      /*!< 0x00000002 */
#define EXTI_EXTICR1_EXTI0_PC         EXTI_EXTICR1_EXTI0_PC_Msk                /*!<PC[0] pin */
#define EXTI_EXTICR1_EXTI0_PD_Pos     (0U)
#define EXTI_EXTICR1_EXTI0_PD_Msk     (0x3U << EXTI_EXTICR1_EXTI0_PD_Pos)      /*!< 0x00000003 */
#define EXTI_EXTICR1_EXTI0_PD         EXTI_EXTICR1_EXTI0_PD_Msk                /*!<PD[0] pin */
#define EXTI_EXTICR1_EXTI0_PE_Pos     (2U)
#define EXTI_EXTICR1_EXTI0_PE_Msk     (0x1U << EXTI_EXTICR1_EXTI0_PE_Pos)      /*!< 0x00000004 */
#define EXTI_EXTICR1_EXTI0_PE         EXTI_EXTICR1_EXTI0_PE_Msk                /*!<PE[0] pin */
#define EXTI_EXTICR1_EXTI0_PF_Pos     (0U)
#define EXTI_EXTICR1_EXTI0_PF_Msk     (0x5U << EXTI_EXTICR1_EXTI0_PF_Pos)      /*!< 0x00000005 */
#define EXTI_EXTICR1_EXTI0_PF         EXTI_EXTICR1_EXTI0_PF_Msk                /*!<PF[0] pin */
#define EXTI_EXTICR1_EXTI0_PG_Pos     (1U)
#define EXTI_EXTICR1_EXTI0_PG_Msk     (0x3U << EXTI_EXTICR1_EXTI0_PG_Pos)      /*!< 0x00000006 */
#define EXTI_EXTICR1_EXTI0_PG         EXTI_EXTICR1_EXTI0_PG_Msk                /*!<PG[0] pin */
#define EXTI_EXTICR1_EXTI0_PH_Pos     (0U)
#define EXTI_EXTICR1_EXTI0_PH_Msk     (0x7U << EXTI_EXTICR1_EXTI0_PH_Pos)      /*!< 0x00000007 */
#define EXTI_EXTICR1_EXTI0_PH         EXTI_EXTICR1_EXTI0_PH_Msk                /*!<PH[0] pin */
#define EXTI_EXTICR1_EXTI0_PI_Pos     (3U)
#define EXTI_EXTICR1_EXTI0_PI_Msk     (0x1U << EXTI_EXTICR1_EXTI0_PI_Pos)      /*!< 0x00000008 */
#define EXTI_EXTICR1_EXTI0_PI         EXTI_EXTICR1_EXTI0_PI_Msk                /*!<PI[0] pin */
#define EXTI_EXTICR1_EXTI0_PJ_Pos     (0U)
#define EXTI_EXTICR1_EXTI0_PJ_Msk     (0x9U << EXTI_EXTICR1_EXTI0_PJ_Pos)      /*!< 0x00000009 */
#define EXTI_EXTICR1_EXTI0_PJ         EXTI_EXTICR1_EXTI0_PJ_Msk                /*!<PJ[0] pin */
#define EXTI_EXTICR1_EXTI0_PK_Pos     (1U)
#define EXTI_EXTICR1_EXTI0_PK_Msk     (0x5U << EXTI_EXTICR1_EXTI0_PK_Pos)      /*!< 0x0000000A */
#define EXTI_EXTICR1_EXTI0_PK         EXTI_EXTICR1_EXTI0_PK_Msk                /*!<PK[0] pin */
#define EXTI_EXTICR1_EXTI0_PZ_Pos     (0U)
#define EXTI_EXTICR1_EXTI0_PZ_Msk     (0xBU << EXTI_EXTICR1_EXTI0_PZ_Pos)      /*!< 0x0000000B */
#define EXTI_EXTICR1_EXTI0_PZ         EXTI_EXTICR1_EXTI0_PZ_Msk                /*!<PZ[0] pin */



/**
  * @brief   EXTI1 configuration
  */
#define EXTI_EXTICR1_EXTI1_PA         ((uint32_t)0x00000000)                   /*!<PA[1] pin */
#define EXTI_EXTICR1_EXTI1_PB_Pos     (8U)
#define EXTI_EXTICR1_EXTI1_PB_Msk     (0x1U << EXTI_EXTICR1_EXTI1_PB_Pos)      /*!< 0x00000100 */
#define EXTI_EXTICR1_EXTI1_PB         EXTI_EXTICR1_EXTI1_PB_Msk                /*!<PB[1] pin */
#define EXTI_EXTICR1_EXTI1_PC_Pos     (9U)
#define EXTI_EXTICR1_EXTI1_PC_Msk     (0x1U << EXTI_EXTICR1_EXTI1_PC_Pos)      /*!< 0x00000200 */
#define EXTI_EXTICR1_EXTI1_PC         EXTI_EXTICR1_EXTI1_PC_Msk                /*!<PC[1] pin */
#define EXTI_EXTICR1_EXTI1_PD_Pos     (8U)
#define EXTI_EXTICR1_EXTI1_PD_Msk     (0x3U << EXTI_EXTICR1_EXTI1_PD_Pos)      /*!< 0x00000300 */
#define EXTI_EXTICR1_EXTI1_PD         EXTI_EXTICR1_EXTI1_PD_Msk                /*!<PD[1] pin */
#define EXTI_EXTICR1_EXTI1_PE_Pos     (10U)
#define EXTI_EXTICR1_EXTI1_PE_Msk     (0x1U << EXTI_EXTICR1_EXTI1_PE_Pos)      /*!< 0x00000400 */
#define EXTI_EXTICR1_EXTI1_PE         EXTI_EXTICR1_EXTI1_PE_Msk                /*!<PE[1] pin */
#define EXTI_EXTICR1_EXTI1_PF_Pos     (8U)
#define EXTI_EXTICR1_EXTI1_PF_Msk     (0x5U << EXTI_EXTICR1_EXTI1_PF_Pos)      /*!< 0x00000500 */
#define EXTI_EXTICR1_EXTI1_PF         EXTI_EXTICR1_EXTI1_PF_Msk                /*!<PF[1] pin */
#define EXTI_EXTICR1_EXTI1_PG_Pos     (9U)
#define EXTI_EXTICR1_EXTI1_PG_Msk     (0x3U << EXTI_EXTICR1_EXTI1_PG_Pos)      /*!< 0x00000600 */
#define EXTI_EXTICR1_EXTI1_PG         EXTI_EXTICR1_EXTI1_PG_Msk                /*!<PG[1] pin */
#define EXTI_EXTICR1_EXTI1_PH_Pos     (8U)
#define EXTI_EXTICR1_EXTI1_PH_Msk     (0x7U << EXTI_EXTICR1_EXTI1_PH_Pos)      /*!< 0x00000700 */
#define EXTI_EXTICR1_EXTI1_PH         EXTI_EXTICR1_EXTI1_PH_Msk                /*!<PH[1] pin */
#define EXTI_EXTICR1_EXTI1_PI_Pos     (11U)
#define EXTI_EXTICR1_EXTI1_PI_Msk     (0x1U << EXTI_EXTICR1_EXTI1_PI_Pos)      /*!< 0x00000800 */
#define EXTI_EXTICR1_EXTI1_PI         EXTI_EXTICR1_EXTI1_PI_Msk                /*!<PI[1] pin */
#define EXTI_EXTICR1_EXTI1_PJ_Pos     (8U)
#define EXTI_EXTICR1_EXTI1_PJ_Msk     (0x9U << EXTI_EXTICR1_EXTI1_PJ_Pos)      /*!< 0x00000900 */
#define EXTI_EXTICR1_EXTI1_PJ         EXTI_EXTICR1_EXTI1_PJ_Msk                /*!<PJ[1] pin */
#define EXTI_EXTICR1_EXTI1_PK_Pos     (9U)
#define EXTI_EXTICR1_EXTI1_PK_Msk     (0x5U << EXTI_EXTICR1_EXTI1_PK_Pos)      /*!< 0x00000A00 */
#define EXTI_EXTICR1_EXTI1_PK         EXTI_EXTICR1_EXTI1_PK_Msk                /*!<PK[1] pin */
#define EXTI_EXTICR1_EXTI1_PZ_Pos     (8U)
#define EXTI_EXTICR1_EXTI1_PZ_Msk     (0xBU << EXTI_EXTICR1_EXTI1_PZ_Pos)      /*!< 0x00000B00 */
#define EXTI_EXTICR1_EXTI1_PZ         EXTI_EXTICR1_EXTI1_PZ_Msk                /*!<PZ[1] pin */

/**
  * @brief   EXTI2 configuration
  */
#define EXTI_EXTICR1_EXTI2_PA         ((uint32_t)0x00000000)                   /*!<PA[2] pin */
#define EXTI_EXTICR1_EXTI2_PB_Pos     (16U)
#define EXTI_EXTICR1_EXTI2_PB_Msk     (0x1U << EXTI_EXTICR1_EXTI2_PB_Pos)      /*!< 0x00010000 */
#define EXTI_EXTICR1_EXTI2_PB         EXTI_EXTICR1_EXTI2_PB_Msk                /*!<PB[2] pin */
#define EXTI_EXTICR1_EXTI2_PC_Pos     (17U)
#define EXTI_EXTICR1_EXTI2_PC_Msk     (0x1U << EXTI_EXTICR1_EXTI2_PC_Pos)      /*!< 0x00020000 */
#define EXTI_EXTICR1_EXTI2_PC         EXTI_EXTICR1_EXTI2_PC_Msk                /*!<PC[2] pin */
#define EXTI_EXTICR1_EXTI2_PD_Pos     (16U)
#define EXTI_EXTICR1_EXTI2_PD_Msk     (0x3U << EXTI_EXTICR1_EXTI2_PD_Pos)      /*!< 0x00030000 */
#define EXTI_EXTICR1_EXTI2_PD         EXTI_EXTICR1_EXTI2_PD_Msk                /*!<PD[2] pin */
#define EXTI_EXTICR1_EXTI2_PE_Pos     (18U)
#define EXTI_EXTICR1_EXTI2_PE_Msk     (0x1U << EXTI_EXTICR1_EXTI2_PE_Pos)      /*!< 0x00040000 */
#define EXTI_EXTICR1_EXTI2_PE         EXTI_EXTICR1_EXTI2_PE_Msk                /*!<PE[2] pin */
#define EXTI_EXTICR1_EXTI2_PF_Pos     (16U)
#define EXTI_EXTICR1_EXTI2_PF_Msk     (0x5U << EXTI_EXTICR1_EXTI2_PF_Pos)      /*!< 0x00050000 */
#define EXTI_EXTICR1_EXTI2_PF         EXTI_EXTICR1_EXTI2_PF_Msk                /*!<PF[2] pin */
#define EXTI_EXTICR1_EXTI2_PG_Pos     (17U)
#define EXTI_EXTICR1_EXTI2_PG_Msk     (0x3U << EXTI_EXTICR1_EXTI2_PG_Pos)      /*!< 0x00060000 */
#define EXTI_EXTICR1_EXTI2_PG         EXTI_EXTICR1_EXTI2_PG_Msk                /*!<PG[2] pin */
#define EXTI_EXTICR1_EXTI2_PH_Pos     (16U)
#define EXTI_EXTICR1_EXTI2_PH_Msk     (0x7U << EXTI_EXTICR1_EXTI2_PH_Pos)      /*!< 0x00070000 */
#define EXTI_EXTICR1_EXTI2_PH         EXTI_EXTICR1_EXTI2_PH_Msk                /*!<PH[2] pin */
#define EXTI_EXTICR1_EXTI2_PI_Pos     (19U)
#define EXTI_EXTICR1_EXTI2_PI_Msk     (0x1U << EXTI_EXTICR1_EXTI2_PI_Pos)      /*!< 0x00080000 */
#define EXTI_EXTICR1_EXTI2_PI         EXTI_EXTICR1_EXTI2_PI_Msk                /*!<PI[2] pin */
#define EXTI_EXTICR1_EXTI2_PJ_Pos     (16U)
#define EXTI_EXTICR1_EXTI2_PJ_Msk     (0x9U << EXTI_EXTICR1_EXTI2_PJ_Pos)      /*!< 0x00090000 */
#define EXTI_EXTICR1_EXTI2_PJ         EXTI_EXTICR1_EXTI2_PJ_Msk                /*!<PJ[2] pin */
#define EXTI_EXTICR1_EXTI2_PK_Pos     (17U)
#define EXTI_EXTICR1_EXTI2_PK_Msk     (0x5U << EXTI_EXTICR1_EXTI2_PK_Pos)      /*!< 0x000A0000 */
#define EXTI_EXTICR1_EXTI2_PK         EXTI_EXTICR1_EXTI2_PK_Msk                /*!<PK[2] pin */
#define EXTI_EXTICR1_EXTI2_PZ_Pos     (16U)
#define EXTI_EXTICR1_EXTI2_PZ_Msk     (0xBU << EXTI_EXTICR1_EXTI2_PZ_Pos)      /*!< 0x000B0000 */
#define EXTI_EXTICR1_EXTI2_PZ         EXTI_EXTICR1_EXTI2_PZ_Msk                /*!<PZ[2] pin */

/**
  * @brief   EXTI3 configuration
  */
#define EXTI_EXTICR1_EXTI3_PA         ((uint32_t)0x00000000)                   /*!<PA[3] pin */
#define EXTI_EXTICR1_EXTI3_PB_Pos     (24U)
#define EXTI_EXTICR1_EXTI3_PB_Msk     (0x1U << EXTI_EXTICR1_EXTI3_PB_Pos)      /*!< 0x01000000 */
#define EXTI_EXTICR1_EXTI3_PB         EXTI_EXTICR1_EXTI3_PB_Msk                /*!<PB[3] pin */
#define EXTI_EXTICR1_EXTI3_PC_Pos     (25U)
#define EXTI_EXTICR1_EXTI3_PC_Msk     (0x1U << EXTI_EXTICR1_EXTI3_PC_Pos)      /*!< 0x02000000 */
#define EXTI_EXTICR1_EXTI3_PC         EXTI_EXTICR1_EXTI3_PC_Msk                /*!<PC[3] pin */
#define EXTI_EXTICR1_EXTI3_PD_Pos     (24U)
#define EXTI_EXTICR1_EXTI3_PD_Msk     (0x3U << EXTI_EXTICR1_EXTI3_PD_Pos)      /*!< 0x03000000 */
#define EXTI_EXTICR1_EXTI3_PD         EXTI_EXTICR1_EXTI3_PD_Msk                /*!<PD[3] pin */
#define EXTI_EXTICR1_EXTI3_PE_Pos     (26U)
#define EXTI_EXTICR1_EXTI3_PE_Msk     (0x1U << EXTI_EXTICR1_EXTI3_PE_Pos)      /*!< 0x04000000 */
#define EXTI_EXTICR1_EXTI3_PE         EXTI_EXTICR1_EXTI3_PE_Msk                /*!<PE[3] pin */
#define EXTI_EXTICR1_EXTI3_PF_Pos     (24U)
#define EXTI_EXTICR1_EXTI3_PF_Msk     (0x5U << EXTI_EXTICR1_EXTI3_PF_Pos)      /*!< 0x05000000 */
#define EXTI_EXTICR1_EXTI3_PF         EXTI_EXTICR1_EXTI3_PF_Msk                /*!<PF[3] pin */
#define EXTI_EXTICR1_EXTI3_PG_Pos     (25U)
#define EXTI_EXTICR1_EXTI3_PG_Msk     (0x3U << EXTI_EXTICR1_EXTI3_PG_Pos)      /*!< 0x06000000 */
#define EXTI_EXTICR1_EXTI3_PG         EXTI_EXTICR1_EXTI3_PG_Msk                /*!<PG[3] pin */
#define EXTI_EXTICR1_EXTI3_PH_Pos     (24U)
#define EXTI_EXTICR1_EXTI3_PH_Msk     (0x7U << EXTI_EXTICR1_EXTI3_PH_Pos)      /*!< 0x07000000 */
#define EXTI_EXTICR1_EXTI3_PH         EXTI_EXTICR1_EXTI3_PH_Msk                /*!<PH[3] pin */
#define EXTI_EXTICR1_EXTI3_PI_Pos     (27U)
#define EXTI_EXTICR1_EXTI3_PI_Msk     (0x1U << EXTI_EXTICR1_EXTI3_PI_Pos)      /*!< 0x08000000 */
#define EXTI_EXTICR1_EXTI3_PI         EXTI_EXTICR1_EXTI3_PI_Msk                /*!<PI[3] pin */
#define EXTI_EXTICR1_EXTI3_PJ_Pos     (24U)
#define EXTI_EXTICR1_EXTI3_PJ_Msk     (0x9U << EXTI_EXTICR1_EXTI3_PJ_Pos)      /*!< 0x09000000 */
#define EXTI_EXTICR1_EXTI3_PJ         EXTI_EXTICR1_EXTI3_PJ_Msk                /*!<PJ[3] pin */
#define EXTI_EXTICR1_EXTI3_PK_Pos     (25U)
#define EXTI_EXTICR1_EXTI3_PK_Msk     (0x5U << EXTI_EXTICR1_EXTI3_PK_Pos)      /*!< 0x0A000000 */
#define EXTI_EXTICR1_EXTI3_PK         EXTI_EXTICR1_EXTI3_PK_Msk                /*!<PK[3] pin */
#define EXTI_EXTICR1_EXTI3_PZ_Pos     (24U)
#define EXTI_EXTICR1_EXTI3_PZ_Msk     (0xBU << EXTI_EXTICR1_EXTI3_PZ_Pos)      /*!< 0x0B000000 */
#define EXTI_EXTICR1_EXTI3_PZ         EXTI_EXTICR1_EXTI3_PZ_Msk                /*!<PZ[3] pin */


/*****************  Bit definition for EXTI_EXTICR2 register  ***************/
#define EXTI_EXTICR2_EXTI4_Pos        (0U)
#define EXTI_EXTICR2_EXTI4_Msk        (0x0FU << EXTI_EXTICR2_EXTI4_Pos)        /*!< 0x000000F */
#define EXTI_EXTICR2_EXTI4            EXTI_EXTICR2_EXTI4_Msk                   /*!<EXTI 4 configuration */
#define EXTI_EXTICR2_EXTI5_Pos        (8U)
#define EXTI_EXTICR2_EXTI5_Msk        (0x0FU << EXTI_EXTICR2_EXTI5_Pos)        /*!< 0x00000F00 */
#define EXTI_EXTICR2_EXTI5            EXTI_EXTICR2_EXTI5_Msk                   /*!<EXTI 5 configuration */
#define EXTI_EXTICR2_EXTI6_Pos        (16U)
#define EXTI_EXTICR2_EXTI6_Msk        (0x0FU << EXTI_EXTICR2_EXTI6_Pos)        /*!< 0x000F0000 */
#define EXTI_EXTICR2_EXTI6            EXTI_EXTICR2_EXTI6_Msk                   /*!<EXTI 6 configuration */
#define EXTI_EXTICR2_EXTI7_Pos        (24U)
#define EXTI_EXTICR2_EXTI7_Msk        (0x0FU << EXTI_EXTICR2_EXTI7_Pos)        /*!< 0x0F000000 */
#define EXTI_EXTICR2_EXTI7            EXTI_EXTICR2_EXTI7_Msk                   /*!<EXTI 7 configuration */

/**
  * @brief   EXTI4 configuration
  */
#define EXTI_EXTICR2_EXTI4_PA         ((uint32_t)0x00000000)                   /*!<PA[4] pin */
#define EXTI_EXTICR2_EXTI4_PB_Pos     (0U)
#define EXTI_EXTICR2_EXTI4_PB_Msk     (0x1U << EXTI_EXTICR2_EXTI4_PB_Pos)      /*!< 0x00000001 */
#define EXTI_EXTICR2_EXTI4_PB         EXTI_EXTICR2_EXTI4_PB_Msk                /*!<PB[4] pin */
#define EXTI_EXTICR2_EXTI4_PC_Pos     (1U)
#define EXTI_EXTICR2_EXTI4_PC_Msk     (0x1U << EXTI_EXTICR2_EXTI4_PC_Pos)      /*!< 0x00000002 */
#define EXTI_EXTICR2_EXTI4_PC         EXTI_EXTICR2_EXTI4_PC_Msk                /*!<PC[4] pin */
#define EXTI_EXTICR2_EXTI4_PD_Pos     (0U)
#define EXTI_EXTICR2_EXTI4_PD_Msk     (0x3U << EXTI_EXTICR2_EXTI4_PD_Pos)      /*!< 0x00000003 */
#define EXTI_EXTICR2_EXTI4_PD         EXTI_EXTICR2_EXTI4_PD_Msk                /*!<PD[4] pin */
#define EXTI_EXTICR2_EXTI4_PE_Pos     (2U)
#define EXTI_EXTICR2_EXTI4_PE_Msk     (0x1U << EXTI_EXTICR2_EXTI4_PE_Pos)      /*!< 0x00000004 */
#define EXTI_EXTICR2_EXTI4_PE         EXTI_EXTICR2_EXTI4_PE_Msk                /*!<PE[4] pin */
#define EXTI_EXTICR2_EXTI4_PF_Pos     (0U)
#define EXTI_EXTICR2_EXTI4_PF_Msk     (0x5U << EXTI_EXTICR2_EXTI4_PF_Pos)      /*!< 0x00000005 */
#define EXTI_EXTICR2_EXTI4_PF         EXTI_EXTICR2_EXTI4_PF_Msk                /*!<PF[4] pin */
#define EXTI_EXTICR2_EXTI4_PG_Pos     (1U)
#define EXTI_EXTICR2_EXTI4_PG_Msk     (0x3U << EXTI_EXTICR2_EXTI4_PG_Pos)      /*!< 0x00000006 */
#define EXTI_EXTICR2_EXTI4_PG         EXTI_EXTICR2_EXTI4_PG_Msk                /*!<PG[4] pin */
#define EXTI_EXTICR2_EXTI4_PH_Pos     (0U)
#define EXTI_EXTICR2_EXTI4_PH_Msk     (0x7U << EXTI_EXTICR2_EXTI4_PH_Pos)      /*!< 0x00000007 */
#define EXTI_EXTICR2_EXTI4_PH         EXTI_EXTICR2_EXTI4_PH_Msk                /*!<PH[4] pin */
#define EXTI_EXTICR2_EXTI4_PI_Pos     (3U)
#define EXTI_EXTICR2_EXTI4_PI_Msk     (0x1U << EXTI_EXTICR2_EXTI4_PI_Pos)      /*!< 0x00000008 */
#define EXTI_EXTICR2_EXTI4_PI         EXTI_EXTICR2_EXTI4_PI_Msk                /*!<PI[4] pin */
#define EXTI_EXTICR2_EXTI4_PJ_Pos     (0U)
#define EXTI_EXTICR2_EXTI4_PJ_Msk     (0x9U << EXTI_EXTICR2_EXTI4_PJ_Pos)      /*!< 0x00000009 */
#define EXTI_EXTICR2_EXTI4_PJ         EXTI_EXTICR2_EXTI4_PJ_Msk                /*!<PJ[4] pin */
#define EXTI_EXTICR2_EXTI4_PK_Pos     (1U)
#define EXTI_EXTICR2_EXTI4_PK_Msk     (0x5U << EXTI_EXTICR2_EXTI4_PK_Pos)      /*!< 0x0000000A */
#define EXTI_EXTICR2_EXTI4_PK         EXTI_EXTICR2_EXTI4_PK_Msk                /*!<PK[4] pin */
#define EXTI_EXTICR2_EXTI4_PZ_Pos     (0U)
#define EXTI_EXTICR2_EXTI4_PZ_Msk     (0xBU << EXTI_EXTICR2_EXTI4_PZ_Pos)      /*!< 0x0000000B */
#define EXTI_EXTICR2_EXTI4_PZ         EXTI_EXTICR2_EXTI4_PZ_Msk                /*!<PZ[4] pin */

/**
  * @brief   EXTI5 configuration
  */
#define EXTI_EXTICR2_EXTI5_PA         ((uint32_t)0x00000000)                   /*!<PA[5] pin */
#define EXTI_EXTICR2_EXTI5_PB_Pos     (8U)
#define EXTI_EXTICR2_EXTI5_PB_Msk     (0x1U << EXTI_EXTICR2_EXTI5_PB_Pos)      /*!< 0x00000100 */
#define EXTI_EXTICR2_EXTI5_PB         EXTI_EXTICR2_EXTI5_PB_Msk                /*!<PB[5] pin */
#define EXTI_EXTICR2_EXTI5_PC_Pos     (9U)
#define EXTI_EXTICR2_EXTI5_PC_Msk     (0x1U << EXTI_EXTICR2_EXTI5_PC_Pos)      /*!< 0x00000200 */
#define EXTI_EXTICR2_EXTI5_PC         EXTI_EXTICR2_EXTI5_PC_Msk                /*!<PC[5] pin */
#define EXTI_EXTICR2_EXTI5_PD_Pos     (8U)
#define EXTI_EXTICR2_EXTI5_PD_Msk     (0x3U << EXTI_EXTICR2_EXTI5_PD_Pos)      /*!< 0x00000300 */
#define EXTI_EXTICR2_EXTI5_PD         EXTI_EXTICR2_EXTI5_PD_Msk                /*!<PD[5] pin */
#define EXTI_EXTICR2_EXTI5_PE_Pos     (10U)
#define EXTI_EXTICR2_EXTI5_PE_Msk     (0x1U << EXTI_EXTICR2_EXTI5_PE_Pos)      /*!< 0x00000400 */
#define EXTI_EXTICR2_EXTI5_PE         EXTI_EXTICR2_EXTI5_PE_Msk                /*!<PE[5] pin */
#define EXTI_EXTICR2_EXTI5_PF_Pos     (8U)
#define EXTI_EXTICR2_EXTI5_PF_Msk     (0x5U << EXTI_EXTICR2_EXTI5_PF_Pos)      /*!< 0x00000500 */
#define EXTI_EXTICR2_EXTI5_PF         EXTI_EXTICR2_EXTI5_PF_Msk                /*!<PF[5] pin */
#define EXTI_EXTICR2_EXTI5_PG_Pos     (9U)
#define EXTI_EXTICR2_EXTI5_PG_Msk     (0x3U << EXTI_EXTICR2_EXTI5_PG_Pos)      /*!< 0x00000600 */
#define EXTI_EXTICR2_EXTI5_PG         EXTI_EXTICR2_EXTI5_PG_Msk                /*!<PG[5] pin */
#define EXTI_EXTICR2_EXTI5_PH_Pos     (8U)
#define EXTI_EXTICR2_EXTI5_PH_Msk     (0x7U << EXTI_EXTICR2_EXTI5_PH_Pos)      /*!< 0x00000700 */
#define EXTI_EXTICR2_EXTI5_PH         EXTI_EXTICR2_EXTI5_PH_Msk                /*!<PH[5] pin */
#define EXTI_EXTICR2_EXTI5_PI_Pos     (11U)
#define EXTI_EXTICR2_EXTI5_PI_Msk     (0x1U << EXTI_EXTICR2_EXTI5_PI_Pos)      /*!< 0x00000800 */
#define EXTI_EXTICR2_EXTI5_PI         EXTI_EXTICR2_EXTI5_PI_Msk                /*!<PI[5] pin */
#define EXTI_EXTICR2_EXTI5_PJ_Pos     (8U)
#define EXTI_EXTICR2_EXTI5_PJ_Msk     (0x9U << EXTI_EXTICR2_EXTI5_PJ_Pos)      /*!< 0x00000900 */
#define EXTI_EXTICR2_EXTI5_PJ         EXTI_EXTICR2_EXTI5_PJ_Msk                /*!<PJ[5] pin */
#define EXTI_EXTICR2_EXTI5_PK_Pos     (9U)
#define EXTI_EXTICR2_EXTI5_PK_Msk     (0x5U << EXTI_EXTICR2_EXTI5_PK_Pos)      /*!< 0x00000A00 */
#define EXTI_EXTICR2_EXTI5_PK         EXTI_EXTICR2_EXTI5_PK_Msk                /*!<PK[5] pin */
#define EXTI_EXTICR2_EXTI5_PZ_Pos     (8U)
#define EXTI_EXTICR2_EXTI5_PZ_Msk     (0xBU << EXTI_EXTICR2_EXTI5_PZ_Pos)      /*!< 0x00000B00 */
#define EXTI_EXTICR2_EXTI5_PZ         EXTI_EXTICR2_EXTI5_PZ_Msk                /*!<PZ[5] pin */

/**
  * @brief   EXTI6 configuration
  */
#define EXTI_EXTICR2_EXTI6_PA         ((uint32_t)0x00000000)                   /*!<PA[6] pin */
#define EXTI_EXTICR2_EXTI6_PB_Pos     (16U)
#define EXTI_EXTICR2_EXTI6_PB_Msk     (0x1U << EXTI_EXTICR2_EXTI6_PB_Pos)      /*!< 0x00010000 */
#define EXTI_EXTICR2_EXTI6_PB         EXTI_EXTICR2_EXTI6_PB_Msk                /*!<PB[6] pin */
#define EXTI_EXTICR2_EXTI6_PC_Pos     (17U)
#define EXTI_EXTICR2_EXTI6_PC_Msk     (0x1U << EXTI_EXTICR2_EXTI6_PC_Pos)      /*!< 0x00020000 */
#define EXTI_EXTICR2_EXTI6_PC         EXTI_EXTICR2_EXTI6_PC_Msk                /*!<PC[6] pin */
#define EXTI_EXTICR2_EXTI6_PD_Pos     (16U)
#define EXTI_EXTICR2_EXTI6_PD_Msk     (0x3U << EXTI_EXTICR2_EXTI6_PD_Pos)      /*!< 0x00030000 */
#define EXTI_EXTICR2_EXTI6_PD         EXTI_EXTICR2_EXTI6_PD_Msk                /*!<PD[6] pin */
#define EXTI_EXTICR2_EXTI6_PE_Pos     (18U)
#define EXTI_EXTICR2_EXTI6_PE_Msk     (0x1U << EXTI_EXTICR2_EXTI6_PE_Pos)      /*!< 0x00040000 */
#define EXTI_EXTICR2_EXTI6_PE         EXTI_EXTICR2_EXTI6_PE_Msk                /*!<PE[6] pin */
#define EXTI_EXTICR2_EXTI6_PF_Pos     (16U)
#define EXTI_EXTICR2_EXTI6_PF_Msk     (0x5U << EXTI_EXTICR2_EXTI6_PF_Pos)      /*!< 0x00050000 */
#define EXTI_EXTICR2_EXTI6_PF         EXTI_EXTICR2_EXTI6_PF_Msk                /*!<PF[6] pin */
#define EXTI_EXTICR2_EXTI6_PG_Pos     (17U)
#define EXTI_EXTICR2_EXTI6_PG_Msk     (0x3U << EXTI_EXTICR2_EXTI6_PG_Pos)      /*!< 0x00060000 */
#define EXTI_EXTICR2_EXTI6_PG         EXTI_EXTICR2_EXTI6_PG_Msk                /*!<PG[6] pin */
#define EXTI_EXTICR2_EXTI6_PH_Pos     (16U)
#define EXTI_EXTICR2_EXTI6_PH_Msk     (0x7U << EXTI_EXTICR2_EXTI6_PH_Pos)      /*!< 0x00070000 */
#define EXTI_EXTICR2_EXTI6_PH         EXTI_EXTICR2_EXTI6_PH_Msk                /*!<PH[6] pin */
#define EXTI_EXTICR2_EXTI6_PI_Pos     (19U)
#define EXTI_EXTICR2_EXTI6_PI_Msk     (0x1U << EXTI_EXTICR2_EXTI6_PI_Pos)      /*!< 0x00080000 */
#define EXTI_EXTICR2_EXTI6_PI         EXTI_EXTICR2_EXTI6_PI_Msk                /*!<PI[6] pin */
#define EXTI_EXTICR2_EXTI6_PJ_Pos     (16U)
#define EXTI_EXTICR2_EXTI6_PJ_Msk     (0x9U << EXTI_EXTICR2_EXTI6_PJ_Pos)      /*!< 0x00090000 */
#define EXTI_EXTICR2_EXTI6_PJ         EXTI_EXTICR2_EXTI6_PJ_Msk                /*!<PJ[6] pin */
#define EXTI_EXTICR2_EXTI6_PK_Pos     (17U)
#define EXTI_EXTICR2_EXTI6_PK_Msk     (0x5U << EXTI_EXTICR2_EXTI6_PK_Pos)      /*!< 0x000A0000 */
#define EXTI_EXTICR2_EXTI6_PK         EXTI_EXTICR2_EXTI6_PK_Msk                /*!<PK[6] pin */
#define EXTI_EXTICR2_EXTI6_PZ_Pos     (16U)
#define EXTI_EXTICR2_EXTI6_PZ_Msk     (0xBU << EXTI_EXTICR2_EXTI6_PZ_Pos)      /*!< 0x000B0000 */
#define EXTI_EXTICR2_EXTI6_PZ         EXTI_EXTICR2_EXTI6_PZ_Msk                /*!<PZ[6] pin */

/**
  * @brief   EXTI7 configuration
  */
#define EXTI_EXTICR2_EXTI7_PA         ((uint32_t)0x00000000)                   /*!<PA[7] pin */
#define EXTI_EXTICR2_EXTI7_PB_Pos     (24U)
#define EXTI_EXTICR2_EXTI7_PB_Msk     (0x1U << EXTI_EXTICR2_EXTI7_PB_Pos)      /*!< 0x01000000 */
#define EXTI_EXTICR2_EXTI7_PB         EXTI_EXTICR2_EXTI7_PB_Msk                /*!<PB[7] pin */
#define EXTI_EXTICR2_EXTI7_PC_Pos     (25U)
#define EXTI_EXTICR2_EXTI7_PC_Msk     (0x1U << EXTI_EXTICR2_EXTI7_PC_Pos)      /*!< 0x02000000 */
#define EXTI_EXTICR2_EXTI7_PC         EXTI_EXTICR2_EXTI7_PC_Msk                /*!<PC[7] pin */
#define EXTI_EXTICR2_EXTI7_PD_Pos     (24U)
#define EXTI_EXTICR2_EXTI7_PD_Msk     (0x3U << EXTI_EXTICR2_EXTI7_PD_Pos)      /*!< 0x03000000 */
#define EXTI_EXTICR2_EXTI7_PD         EXTI_EXTICR2_EXTI7_PD_Msk                /*!<PD[7] pin */
#define EXTI_EXTICR2_EXTI7_PE_Pos     (26U)
#define EXTI_EXTICR2_EXTI7_PE_Msk     (0x1U << EXTI_EXTICR2_EXTI7_PE_Pos)      /*!< 0x04000000 */
#define EXTI_EXTICR2_EXTI7_PE         EXTI_EXTICR2_EXTI7_PE_Msk                /*!<PE[7] pin */
#define EXTI_EXTICR2_EXTI7_PF_Pos     (24U)
#define EXTI_EXTICR2_EXTI7_PF_Msk     (0x5U << EXTI_EXTICR2_EXTI7_PF_Pos)      /*!< 0x05000000 */
#define EXTI_EXTICR2_EXTI7_PF         EXTI_EXTICR2_EXTI7_PF_Msk                /*!<PF[7] pin */
#define EXTI_EXTICR2_EXTI7_PG_Pos     (25U)
#define EXTI_EXTICR2_EXTI7_PG_Msk     (0x3U << EXTI_EXTICR2_EXTI7_PG_Pos)      /*!< 0x06000000 */
#define EXTI_EXTICR2_EXTI7_PG         EXTI_EXTICR2_EXTI7_PG_Msk                /*!<PG[7] pin */
#define EXTI_EXTICR2_EXTI7_PH_Pos     (24U)
#define EXTI_EXTICR2_EXTI7_PH_Msk     (0x7U << EXTI_EXTICR2_EXTI7_PH_Pos)      /*!< 0x07000000 */
#define EXTI_EXTICR2_EXTI7_PH         EXTI_EXTICR2_EXTI7_PH_Msk                /*!<PH[7] pin */
#define EXTI_EXTICR2_EXTI7_PI_Pos     (27U)
#define EXTI_EXTICR2_EXTI7_PI_Msk     (0x1U << EXTI_EXTICR2_EXTI7_PI_Pos)      /*!< 0x08000000 */
#define EXTI_EXTICR2_EXTI7_PI         EXTI_EXTICR2_EXTI7_PI_Msk                /*!<PI[7] pin */
#define EXTI_EXTICR2_EXTI7_PJ_Pos     (24U)
#define EXTI_EXTICR2_EXTI7_PJ_Msk     (0x9U << EXTI_EXTICR2_EXTI7_PJ_Pos)      /*!< 0x09000000 */
#define EXTI_EXTICR2_EXTI7_PJ         EXTI_EXTICR2_EXTI7_PJ_Msk                /*!<PJ[7] pin */
#define EXTI_EXTICR2_EXTI7_PK_Pos     (25U)
#define EXTI_EXTICR2_EXTI7_PK_Msk     (0x5U << EXTI_EXTICR2_EXTI7_PK_Pos)      /*!< 0x0A000000 */
#define EXTI_EXTICR2_EXTI7_PK         EXTI_EXTICR2_EXTI7_PK_Msk                /*!<PK[7] pin */
#define EXTI_EXTICR2_EXTI7_PZ_Pos     (24U)
#define EXTI_EXTICR2_EXTI7_PZ_Msk     (0xBU << EXTI_EXTICR2_EXTI7_PZ_Pos)      /*!< 0x0B000000 */
#define EXTI_EXTICR2_EXTI7_PZ         EXTI_EXTICR2_EXTI7_PZ_Msk                /*!<PZ[7] pin */


/*****************  Bit definition for EXTI_EXTICR3 register  ***************/
#define EXTI_EXTICR3_EXTI8_Pos        (0U)
#define EXTI_EXTICR3_EXTI8_Msk        (0x0FU << EXTI_EXTICR3_EXTI8_Pos)        /*!< 0x0000000F */
#define EXTI_EXTICR3_EXTI8            EXTI_EXTICR3_EXTI8_Msk                   /*!<EXTI 8 configuration */
#define EXTI_EXTICR3_EXTI9_Pos        (8U)
#define EXTI_EXTICR3_EXTI9_Msk        (0x0FU << EXTI_EXTICR3_EXTI9_Pos)        /*!< 0x00000F00 */
#define EXTI_EXTICR3_EXTI9            EXTI_EXTICR3_EXTI9_Msk                   /*!<EXTI 9 configuration */
#define EXTI_EXTICR3_EXTI10_Pos       (16U)
#define EXTI_EXTICR3_EXTI10_Msk       (0x0FU << EXTI_EXTICR3_EXTI10_Pos)       /*!< 0x000F0000 */
#define EXTI_EXTICR3_EXTI10           EXTI_EXTICR3_EXTI10_Msk                  /*!<EXTI 10 configuration */
#define EXTI_EXTICR3_EXTI11_Pos       (24U)
#define EXTI_EXTICR3_EXTI11_Msk       (0x0FU << EXTI_EXTICR3_EXTI11_Pos)       /*!< 0x0F000000 */
#define EXTI_EXTICR3_EXTI11           EXTI_EXTICR3_EXTI11_Msk                  /*!<EXTI 11 configuration */

/**
  * @brief   EXTI8 configuration
  */
#define EXTI_EXTICR3_EXTI8_PA         ((uint32_t)0x00000000)                   /*!<PA[8] pin */
#define EXTI_EXTICR3_EXTI8_PB_Pos     (0U)
#define EXTI_EXTICR3_EXTI8_PB_Msk     (0x1U << EXTI_EXTICR3_EXTI8_PB_Pos)      /*!< 0x00000001 */
#define EXTI_EXTICR3_EXTI8_PB         EXTI_EXTICR3_EXTI8_PB_Msk                /*!<PB[8] pin */
#define EXTI_EXTICR3_EXTI8_PC_Pos     (1U)
#define EXTI_EXTICR3_EXTI8_PC_Msk     (0x1U << EXTI_EXTICR3_EXTI8_PC_Pos)      /*!< 0x00000002 */
#define EXTI_EXTICR3_EXTI8_PC         EXTI_EXTICR3_EXTI8_PC_Msk                /*!<PC[8] pin */
#define EXTI_EXTICR3_EXTI8_PD_Pos     (0U)
#define EXTI_EXTICR3_EXTI8_PD_Msk     (0x3U << EXTI_EXTICR3_EXTI8_PD_Pos)      /*!< 0x00000003 */
#define EXTI_EXTICR3_EXTI8_PD         EXTI_EXTICR3_EXTI8_PD_Msk                /*!<PD[8] pin */
#define EXTI_EXTICR3_EXTI8_PE_Pos     (2U)
#define EXTI_EXTICR3_EXTI8_PE_Msk     (0x1U << EXTI_EXTICR3_EXTI8_PE_Pos)      /*!< 0x00000004 */
#define EXTI_EXTICR3_EXTI8_PE         EXTI_EXTICR3_EXTI8_PE_Msk                /*!<PE[8] pin */
#define EXTI_EXTICR3_EXTI8_PF_Pos     (0U)
#define EXTI_EXTICR3_EXTI8_PF_Msk     (0x5U << EXTI_EXTICR3_EXTI8_PF_Pos)      /*!< 0x00000005 */
#define EXTI_EXTICR3_EXTI8_PF         EXTI_EXTICR3_EXTI8_PF_Msk                /*!<PF[8] pin */
#define EXTI_EXTICR3_EXTI8_PG_Pos     (1U)
#define EXTI_EXTICR3_EXTI8_PG_Msk     (0x3U << EXTI_EXTICR3_EXTI8_PG_Pos)      /*!< 0x00000006 */
#define EXTI_EXTICR3_EXTI8_PG         EXTI_EXTICR3_EXTI8_PG_Msk                /*!<PG[8] pin */
#define EXTI_EXTICR3_EXTI8_PH_Pos     (0U)
#define EXTI_EXTICR3_EXTI8_PH_Msk     (0x7U << EXTI_EXTICR3_EXTI8_PH_Pos)      /*!< 0x00000007 */
#define EXTI_EXTICR3_EXTI8_PH         EXTI_EXTICR3_EXTI8_PH_Msk                /*!<PH[8] pin */
#define EXTI_EXTICR3_EXTI8_PI_Pos     (3U)
#define EXTI_EXTICR3_EXTI8_PI_Msk     (0x1U << EXTI_EXTICR3_EXTI8_PI_Pos)      /*!< 0x00000008 */
#define EXTI_EXTICR3_EXTI8_PI         EXTI_EXTICR3_EXTI8_PI_Msk                /*!<PI[8] pin */
#define EXTI_EXTICR3_EXTI8_PJ_Pos     (0U)
#define EXTI_EXTICR3_EXTI8_PJ_Msk     (0x9U << EXTI_EXTICR3_EXTI8_PJ_Pos)      /*!< 0x00000009 */
#define EXTI_EXTICR3_EXTI8_PJ         EXTI_EXTICR3_EXTI8_PJ_Msk                /*!<PJ[8] pin */

/**
  * @brief   EXTI9 configuration
  */
#define EXTI_EXTICR3_EXTI9_PA         ((uint32_t)0x00000000)                   /*!<PA[9] pin */
#define EXTI_EXTICR3_EXTI9_PB_Pos     (8U)
#define EXTI_EXTICR3_EXTI9_PB_Msk     (0x1U << EXTI_EXTICR3_EXTI9_PB_Pos)      /*!< 0x00000100 */
#define EXTI_EXTICR3_EXTI9_PB         EXTI_EXTICR3_EXTI9_PB_Msk                /*!<PB[9] pin */
#define EXTI_EXTICR3_EXTI9_PC_Pos     (9U)
#define EXTI_EXTICR3_EXTI9_PC_Msk     (0x1U << EXTI_EXTICR3_EXTI9_PC_Pos)      /*!< 0x00000200 */
#define EXTI_EXTICR3_EXTI9_PC         EXTI_EXTICR3_EXTI9_PC_Msk                /*!<PC[9] pin */
#define EXTI_EXTICR3_EXTI9_PD_Pos     (8U)
#define EXTI_EXTICR3_EXTI9_PD_Msk     (0x3U << EXTI_EXTICR3_EXTI9_PD_Pos)      /*!< 0x00000300 */
#define EXTI_EXTICR3_EXTI9_PD         EXTI_EXTICR3_EXTI9_PD_Msk                /*!<PD[9] pin */
#define EXTI_EXTICR3_EXTI9_PE_Pos     (10U)
#define EXTI_EXTICR3_EXTI9_PE_Msk     (0x1U << EXTI_EXTICR3_EXTI9_PE_Pos)      /*!< 0x00000400 */
#define EXTI_EXTICR3_EXTI9_PE         EXTI_EXTICR3_EXTI9_PE_Msk                /*!<PE[9] pin */
#define EXTI_EXTICR3_EXTI9_PF_Pos     (8U)
#define EXTI_EXTICR3_EXTI9_PF_Msk     (0x5U << EXTI_EXTICR3_EXTI9_PF_Pos)      /*!< 0x00000500 */
#define EXTI_EXTICR3_EXTI9_PF         EXTI_EXTICR3_EXTI9_PF_Msk                /*!<PF[9] pin */
#define EXTI_EXTICR3_EXTI9_PG_Pos     (9U)
#define EXTI_EXTICR3_EXTI9_PG_Msk     (0x3U << EXTI_EXTICR3_EXTI9_PG_Pos)      /*!< 0x00000600 */
#define EXTI_EXTICR3_EXTI9_PG         EXTI_EXTICR3_EXTI9_PG_Msk                /*!<PG[9] pin */
#define EXTI_EXTICR3_EXTI9_PH_Pos     (8U)
#define EXTI_EXTICR3_EXTI9_PH_Msk     (0x7U << EXTI_EXTICR3_EXTI9_PH_Pos)      /*!< 0x00000700 */
#define EXTI_EXTICR3_EXTI9_PH         EXTI_EXTICR3_EXTI9_PH_Msk                /*!<PH[9] pin */
#define EXTI_EXTICR3_EXTI9_PI_Pos     (11U)
#define EXTI_EXTICR3_EXTI9_PI_Msk     (0x1U << EXTI_EXTICR3_EXTI9_PI_Pos)      /*!< 0x00000800 */
#define EXTI_EXTICR3_EXTI9_PI         EXTI_EXTICR3_EXTI9_PI_Msk                /*!<PI[9] pin */
#define EXTI_EXTICR3_EXTI9_PJ_Pos     (8U)
#define EXTI_EXTICR3_EXTI9_PJ_Msk     (0x9U << EXTI_EXTICR3_EXTI9_PJ_Pos)      /*!< 0x00000900 */
#define EXTI_EXTICR3_EXTI9_PJ         EXTI_EXTICR3_EXTI9_PJ_Msk                /*!<PJ[9] pin */

/**
  * @brief   EXTI10 configuration
  */
#define EXTI_EXTICR3_EXTI10_PA        ((uint32_t)0x00000000)                   /*!<PA[10] pin */
#define EXTI_EXTICR3_EXTI10_PB_Pos    (16U)
#define EXTI_EXTICR3_EXTI10_PB_Msk    (0x1U << EXTI_EXTICR3_EXTI10_PB_Pos)     /*!< 0x00010000 */
#define EXTI_EXTICR3_EXTI10_PB        EXTI_EXTICR3_EXTI10_PB_Msk               /*!<PB[10] pin */
#define EXTI_EXTICR3_EXTI10_PC_Pos    (17U)
#define EXTI_EXTICR3_EXTI10_PC_Msk    (0x1U << EXTI_EXTICR3_EXTI10_PC_Pos)     /*!< 0x00020000 */
#define EXTI_EXTICR3_EXTI10_PC        EXTI_EXTICR3_EXTI10_PC_Msk               /*!<PC[10] pin */
#define EXTI_EXTICR3_EXTI10_PD_Pos    (16U)
#define EXTI_EXTICR3_EXTI10_PD_Msk    (0x3U << EXTI_EXTICR3_EXTI10_PD_Pos)     /*!< 0x00030000 */
#define EXTI_EXTICR3_EXTI10_PD        EXTI_EXTICR3_EXTI10_PD_Msk               /*!<PD[10] pin */
#define EXTI_EXTICR3_EXTI10_PE_Pos    (18U)
#define EXTI_EXTICR3_EXTI10_PE_Msk    (0x1U << EXTI_EXTICR3_EXTI10_PE_Pos)     /*!< 0x00040000 */
#define EXTI_EXTICR3_EXTI10_PE        EXTI_EXTICR3_EXTI10_PE_Msk               /*!<PE[10] pin */
#define EXTI_EXTICR3_EXTI10_PF_Pos    (16U)
#define EXTI_EXTICR3_EXTI10_PF_Msk    (0x5U << EXTI_EXTICR3_EXTI10_PF_Pos)     /*!< 0x00050000 */
#define EXTI_EXTICR3_EXTI10_PF        EXTI_EXTICR3_EXTI10_PF_Msk               /*!<PF[10] pin */
#define EXTI_EXTICR3_EXTI10_PG_Pos    (17U)
#define EXTI_EXTICR3_EXTI10_PG_Msk    (0x3U << EXTI_EXTICR3_EXTI10_PG_Pos)     /*!< 0x00060000 */
#define EXTI_EXTICR3_EXTI10_PG        EXTI_EXTICR3_EXTI10_PG_Msk               /*!<PG[10] pin */
#define EXTI_EXTICR3_EXTI10_PH_Pos    (16U)
#define EXTI_EXTICR3_EXTI10_PH_Msk    (0x7U << EXTI_EXTICR3_EXTI10_PH_Pos)     /*!< 0x00070000 */
#define EXTI_EXTICR3_EXTI10_PH        EXTI_EXTICR3_EXTI10_PH_Msk               /*!<PH[10] pin */
#define EXTI_EXTICR3_EXTI10_PI_Pos    (19U)
#define EXTI_EXTICR3_EXTI10_PI_Msk    (0x1U << EXTI_EXTICR3_EXTI10_PI_Pos)     /*!< 0x00080000 */
#define EXTI_EXTICR3_EXTI10_PI        EXTI_EXTICR3_EXTI10_PI_Msk               /*!<PI[10] pin */
#define EXTI_EXTICR3_EXTI10_PJ_Pos    (16U)
#define EXTI_EXTICR3_EXTI10_PJ_Msk    (0x9U << EXTI_EXTICR3_EXTI10_PJ_Pos)     /*!< 0x00090000 */
#define EXTI_EXTICR3_EXTI10_PJ        EXTI_EXTICR3_EXTI10_PJ_Msk               /*!<PJ[10] pin */

/**
  * @brief   EXTI11 configuration
  */
#define EXTI_EXTICR3_EXTI11_PA        ((uint32_t)0x00000000)                   /*!<PA[11] pin */
#define EXTI_EXTICR3_EXTI11_PB_Pos    (24U)
#define EXTI_EXTICR3_EXTI11_PB_Msk    (0x1U << EXTI_EXTICR3_EXTI11_PB_Pos)     /*!< 0x01000000 */
#define EXTI_EXTICR3_EXTI11_PB        EXTI_EXTICR3_EXTI11_PB_Msk               /*!<PB[11] pin */
#define EXTI_EXTICR3_EXTI11_PC_Pos    (25U)
#define EXTI_EXTICR3_EXTI11_PC_Msk    (0x1U << EXTI_EXTICR3_EXTI11_PC_Pos)     /*!< 0x02000000 */
#define EXTI_EXTICR3_EXTI11_PC        EXTI_EXTICR3_EXTI11_PC_Msk               /*!<PC[11] pin */
#define EXTI_EXTICR3_EXTI11_PD_Pos    (24U)
#define EXTI_EXTICR3_EXTI11_PD_Msk    (0x3U << EXTI_EXTICR3_EXTI11_PD_Pos)     /*!< 0x03000000 */
#define EXTI_EXTICR3_EXTI11_PD        EXTI_EXTICR3_EXTI11_PD_Msk               /*!<PD[11] pin */
#define EXTI_EXTICR3_EXTI11_PE_Pos    (26U)
#define EXTI_EXTICR3_EXTI11_PE_Msk    (0x1U << EXTI_EXTICR3_EXTI11_PE_Pos)     /*!< 0x04000000 */
#define EXTI_EXTICR3_EXTI11_PE        EXTI_EXTICR3_EXTI11_PE_Msk               /*!<PE[11] pin */
#define EXTI_EXTICR3_EXTI11_PF_Pos    (24U)
#define EXTI_EXTICR3_EXTI11_PF_Msk    (0x5U << EXTI_EXTICR3_EXTI11_PF_Pos)     /*!< 0x05000000 */
#define EXTI_EXTICR3_EXTI11_PF        EXTI_EXTICR3_EXTI11_PF_Msk               /*!<PF[11] pin */
#define EXTI_EXTICR3_EXTI11_PG_Pos    (25U)
#define EXTI_EXTICR3_EXTI11_PG_Msk    (0x3U << EXTI_EXTICR3_EXTI11_PG_Pos)     /*!< 0x06000000 */
#define EXTI_EXTICR3_EXTI11_PG        EXTI_EXTICR3_EXTI11_PG_Msk               /*!<PG[11] pin */
#define EXTI_EXTICR3_EXTI11_PH_Pos    (24U)
#define EXTI_EXTICR3_EXTI11_PH_Msk    (0x7U << EXTI_EXTICR3_EXTI11_PH_Pos)     /*!< 0x07000000 */
#define EXTI_EXTICR3_EXTI11_PH        EXTI_EXTICR3_EXTI11_PH_Msk               /*!<PH[11] pin */
#define EXTI_EXTICR3_EXTI11_PI_Pos    (27U)
#define EXTI_EXTICR3_EXTI11_PI_Msk    (0x1U << EXTI_EXTICR3_EXTI11_PI_Pos)     /*!< 0x08000000 */
#define EXTI_EXTICR3_EXTI11_PI        EXTI_EXTICR3_EXTI11_PI_Msk               /*!<PI[11] pin */
#define EXTI_EXTICR3_EXTI11_PJ_Pos    (24U)
#define EXTI_EXTICR3_EXTI11_PJ_Msk    (0x9U << EXTI_EXTICR3_EXTI11_PJ_Pos)     /*!< 0x09000000 */
#define EXTI_EXTICR3_EXTI11_PJ        EXTI_EXTICR3_EXTI11_PJ_Msk               /*!<PJ[11] pin */


/*****************  Bit definition for EXTI_EXTICR4 register  ***************/
#define EXTI_EXTICR4_EXTI12_Pos       (0U)
#define EXTI_EXTICR4_EXTI12_Msk       (0x0FU << EXTI_EXTICR4_EXTI12_Pos)       /*!< 0x0000000F */
#define EXTI_EXTICR4_EXTI12           EXTI_EXTICR4_EXTI12_Msk                  /*!<EXTI 12 configuration */
#define EXTI_EXTICR4_EXTI13_Pos       (8U)
#define EXTI_EXTICR4_EXTI13_Msk       (0x0FU << EXTI_EXTICR4_EXTI13_Pos)       /*!< 0x00000F00 */
#define EXTI_EXTICR4_EXTI13           EXTI_EXTICR4_EXTI13_Msk                  /*!<EXTI 13 configuration */
#define EXTI_EXTICR4_EXTI14_Pos       (16U)
#define EXTI_EXTICR4_EXTI14_Msk       (0x0FU << EXTI_EXTICR4_EXTI14_Pos)       /*!< 0x000F0000 */
#define EXTI_EXTICR4_EXTI14           EXTI_EXTICR4_EXTI14_Msk                  /*!<EXTI 14 configuration */
#define EXTI_EXTICR4_EXTI15_Pos       (24U)
#define EXTI_EXTICR4_EXTI15_Msk       (0x0FU << EXTI_EXTICR4_EXTI15_Pos)       /*!< 0x0F000000 */
#define EXTI_EXTICR4_EXTI15           EXTI_EXTICR4_EXTI15_Msk                  /*!<EXTI 15 configuration */

/**
  * @brief   EXTI12 configuration
  */
#define EXTI_EXTICR4_EXTI12_PA        ((uint32_t)0x00000000)                   /*!<PA[12] pin */
#define EXTI_EXTICR4_EXTI12_PB_Pos    (0U)
#define EXTI_EXTICR4_EXTI12_PB_Msk    (0x1U << EXTI_EXTICR4_EXTI12_PB_Pos)     /*!< 0x00000001 */
#define EXTI_EXTICR4_EXTI12_PB        EXTI_EXTICR4_EXTI12_PB_Msk               /*!<PB[12] pin */
#define EXTI_EXTICR4_EXTI12_PC_Pos    (1U)
#define EXTI_EXTICR4_EXTI12_PC_Msk    (0x1U << EXTI_EXTICR4_EXTI12_PC_Pos)     /*!< 0x00000002 */
#define EXTI_EXTICR4_EXTI12_PC        EXTI_EXTICR4_EXTI12_PC_Msk               /*!<PC[12] pin */
#define EXTI_EXTICR4_EXTI12_PD_Pos    (0U)
#define EXTI_EXTICR4_EXTI12_PD_Msk    (0x3U << EXTI_EXTICR4_EXTI12_PD_Pos)     /*!< 0x00000003 */
#define EXTI_EXTICR4_EXTI12_PD        EXTI_EXTICR4_EXTI12_PD_Msk               /*!<PD[12] pin */
#define EXTI_EXTICR4_EXTI12_PE_Pos    (2U)
#define EXTI_EXTICR4_EXTI12_PE_Msk    (0x1U << EXTI_EXTICR4_EXTI12_PE_Pos)     /*!< 0x00000004 */
#define EXTI_EXTICR4_EXTI12_PE        EXTI_EXTICR4_EXTI12_PE_Msk               /*!<PE[12] pin */
#define EXTI_EXTICR4_EXTI12_PF_Pos    (0U)
#define EXTI_EXTICR4_EXTI12_PF_Msk    (0x5U << EXTI_EXTICR4_EXTI12_PF_Pos)     /*!< 0x00000005 */
#define EXTI_EXTICR4_EXTI12_PF        EXTI_EXTICR4_EXTI12_PF_Msk               /*!<PF[12] pin */
#define EXTI_EXTICR4_EXTI12_PG_Pos    (1U)
#define EXTI_EXTICR4_EXTI12_PG_Msk    (0x3U << EXTI_EXTICR4_EXTI12_PG_Pos)     /*!< 0x00000006 */
#define EXTI_EXTICR4_EXTI12_PG        EXTI_EXTICR4_EXTI12_PG_Msk               /*!<PG[12] pin */
#define EXTI_EXTICR4_EXTI12_PH_Pos    (0U)
#define EXTI_EXTICR4_EXTI12_PH_Msk    (0x7U << EXTI_EXTICR4_EXTI12_PH_Pos)     /*!< 0x00000007 */
#define EXTI_EXTICR4_EXTI12_PH        EXTI_EXTICR4_EXTI12_PH_Msk               /*!<PH[12] pin */
#define EXTI_EXTICR4_EXTI12_PI_Pos    (3U)
#define EXTI_EXTICR4_EXTI12_PI_Msk    (0x1U << EXTI_EXTICR4_EXTI12_PI_Pos)     /*!< 0x00000008 */
#define EXTI_EXTICR4_EXTI12_PI        EXTI_EXTICR4_EXTI12_PI_Msk               /*!<PI[12] pin */
#define EXTI_EXTICR4_EXTI12_PJ_Pos    (0U)
#define EXTI_EXTICR4_EXTI12_PJ_Msk    (0x9U << EXTI_EXTICR4_EXTI12_PJ_Pos)     /*!< 0x00000009 */
#define EXTI_EXTICR4_EXTI12_PJ        EXTI_EXTICR4_EXTI12_PJ_Msk               /*!<PJ[12] pin */

/**
  * @brief   EXTI13 configuration
  */
#define EXTI_EXTICR4_EXTI13_PA        ((uint32_t)0x00000000)                   /*!<PA[13] pin */
#define EXTI_EXTICR4_EXTI13_PB_Pos    (8U)
#define EXTI_EXTICR4_EXTI13_PB_Msk    (0x1U << EXTI_EXTICR4_EXTI13_PB_Pos)     /*!< 0x00000100 */
#define EXTI_EXTICR4_EXTI13_PB        EXTI_EXTICR4_EXTI13_PB_Msk               /*!<PB[13] pin */
#define EXTI_EXTICR4_EXTI13_PC_Pos    (9U)
#define EXTI_EXTICR4_EXTI13_PC_Msk    (0x1U << EXTI_EXTICR4_EXTI13_PC_Pos)     /*!< 0x00000200 */
#define EXTI_EXTICR4_EXTI13_PC        EXTI_EXTICR4_EXTI13_PC_Msk               /*!<PC[13] pin */
#define EXTI_EXTICR4_EXTI13_PD_Pos    (8U)
#define EXTI_EXTICR4_EXTI13_PD_Msk    (0x3U << EXTI_EXTICR4_EXTI13_PD_Pos)     /*!< 0x00000300 */
#define EXTI_EXTICR4_EXTI13_PD        EXTI_EXTICR4_EXTI13_PD_Msk               /*!<PD[13] pin */
#define EXTI_EXTICR4_EXTI13_PE_Pos    (10U)
#define EXTI_EXTICR4_EXTI13_PE_Msk    (0x1U << EXTI_EXTICR4_EXTI13_PE_Pos)     /*!< 0x00000400 */
#define EXTI_EXTICR4_EXTI13_PE        EXTI_EXTICR4_EXTI13_PE_Msk               /*!<PE[13] pin */
#define EXTI_EXTICR4_EXTI13_PF_Pos    (8U)
#define EXTI_EXTICR4_EXTI13_PF_Msk    (0x5U << EXTI_EXTICR4_EXTI13_PF_Pos)     /*!< 0x00000500 */
#define EXTI_EXTICR4_EXTI13_PF        EXTI_EXTICR4_EXTI13_PF_Msk               /*!<PF[13] pin */
#define EXTI_EXTICR4_EXTI13_PG_Pos    (9U)
#define EXTI_EXTICR4_EXTI13_PG_Msk    (0x3U << EXTI_EXTICR4_EXTI13_PG_Pos)     /*!< 0x00000600 */
#define EXTI_EXTICR4_EXTI13_PG        EXTI_EXTICR4_EXTI13_PG_Msk               /*!<PG[13] pin */
#define EXTI_EXTICR4_EXTI13_PH_Pos    (8U)
#define EXTI_EXTICR4_EXTI13_PH_Msk    (0x7U << EXTI_EXTICR4_EXTI13_PH_Pos)     /*!< 0x00000700 */
#define EXTI_EXTICR4_EXTI13_PH        EXTI_EXTICR4_EXTI13_PH_Msk               /*!<PH[13] pin */
#define EXTI_EXTICR4_EXTI13_PI_Pos    (11U)
#define EXTI_EXTICR4_EXTI13_PI_Msk    (0x1U << EXTI_EXTICR4_EXTI13_PI_Pos)     /*!< 0x00000800 */
#define EXTI_EXTICR4_EXTI13_PI        EXTI_EXTICR4_EXTI13_PI_Msk               /*!<PI[13] pin */
#define EXTI_EXTICR4_EXTI13_PJ_Pos    (8U)
#define EXTI_EXTICR4_EXTI13_PJ_Msk    (0x9U << EXTI_EXTICR4_EXTI13_PJ_Pos)     /*!< 0x00000900 */
#define EXTI_EXTICR4_EXTI13_PJ        EXTI_EXTICR4_EXTI13_PJ_Msk               /*!<PJ[13] pin */

/**
  * @brief   EXTI14 configuration
  */
#define EXTI_EXTICR4_EXTI14_PA        ((uint32_t)0x00000000)                   /*!<PA[14] pin */
#define EXTI_EXTICR4_EXTI14_PB_Pos    (16U)
#define EXTI_EXTICR4_EXTI14_PB_Msk    (0x1U << EXTI_EXTICR4_EXTI14_PB_Pos)     /*!< 0x00010000 */
#define EXTI_EXTICR4_EXTI14_PB        EXTI_EXTICR4_EXTI14_PB_Msk               /*!<PB[14] pin */
#define EXTI_EXTICR4_EXTI14_PC_Pos    (17U)
#define EXTI_EXTICR4_EXTI14_PC_Msk    (0x1U << EXTI_EXTICR4_EXTI14_PC_Pos)     /*!< 0x00020000 */
#define EXTI_EXTICR4_EXTI14_PC        EXTI_EXTICR4_EXTI14_PC_Msk               /*!<PC[14] pin */
#define EXTI_EXTICR4_EXTI14_PD_Pos    (16U)
#define EXTI_EXTICR4_EXTI14_PD_Msk    (0x3U << EXTI_EXTICR4_EXTI14_PD_Pos)     /*!< 0x00030000 */
#define EXTI_EXTICR4_EXTI14_PD        EXTI_EXTICR4_EXTI14_PD_Msk               /*!<PD[14] pin */
#define EXTI_EXTICR4_EXTI14_PE_Pos    (18U)
#define EXTI_EXTICR4_EXTI14_PE_Msk    (0x1U << EXTI_EXTICR4_EXTI14_PE_Pos)     /*!< 0x00040000 */
#define EXTI_EXTICR4_EXTI14_PE        EXTI_EXTICR4_EXTI14_PE_Msk               /*!<PE[14] pin */
#define EXTI_EXTICR4_EXTI14_PF_Pos    (16U)
#define EXTI_EXTICR4_EXTI14_PF_Msk    (0x5U << EXTI_EXTICR4_EXTI14_PF_Pos)     /*!< 0x00050000 */
#define EXTI_EXTICR4_EXTI14_PF        EXTI_EXTICR4_EXTI14_PF_Msk               /*!<PF[14] pin */
#define EXTI_EXTICR4_EXTI14_PG_Pos    (17U)
#define EXTI_EXTICR4_EXTI14_PG_Msk    (0x3U << EXTI_EXTICR4_EXTI14_PG_Pos)     /*!< 0x00060000 */
#define EXTI_EXTICR4_EXTI14_PG        EXTI_EXTICR4_EXTI14_PG_Msk               /*!<PG[14] pin */
#define EXTI_EXTICR4_EXTI14_PH_Pos    (16U)
#define EXTI_EXTICR4_EXTI14_PH_Msk    (0x7U << EXTI_EXTICR4_EXTI14_PH_Pos)     /*!< 0x00070000 */
#define EXTI_EXTICR4_EXTI14_PH        EXTI_EXTICR4_EXTI14_PH_Msk               /*!<PH[14] pin */
#define EXTI_EXTICR4_EXTI14_PI_Pos    (19U)
#define EXTI_EXTICR4_EXTI14_PI_Msk    (0x1U << EXTI_EXTICR4_EXTI14_PI_Pos)     /*!< 0x00080000 */
#define EXTI_EXTICR4_EXTI14_PI        EXTI_EXTICR4_EXTI14_PI_Msk               /*!<PI[14] pin */
#define EXTI_EXTICR4_EXTI14_PJ_Pos    (16U)
#define EXTI_EXTICR4_EXTI14_PJ_Msk    (0x9U << EXTI_EXTICR4_EXTI14_PJ_Pos)     /*!< 0x00090000 */
#define EXTI_EXTICR4_EXTI14_PJ        EXTI_EXTICR4_EXTI14_PJ_Msk               /*!<PJ[14] pin */

/**
  * @brief   EXTI15 configuration
  */
#define EXTI_EXTICR4_EXTI15_PA        ((uint32_t)0x00000000)                   /*!<PA[15] pin */
#define EXTI_EXTICR4_EXTI15_PB_Pos    (24U)
#define EXTI_EXTICR4_EXTI15_PB_Msk    (0x1U << EXTI_EXTICR4_EXTI15_PB_Pos)     /*!< 0x01000000 */
#define EXTI_EXTICR4_EXTI15_PB        EXTI_EXTICR4_EXTI15_PB_Msk               /*!<PB[15] pin */
#define EXTI_EXTICR4_EXTI15_PC_Pos    (25U)
#define EXTI_EXTICR4_EXTI15_PC_Msk    (0x1U << EXTI_EXTICR4_EXTI15_PC_Pos)     /*!< 0x02000000 */
#define EXTI_EXTICR4_EXTI15_PC        EXTI_EXTICR4_EXTI15_PC_Msk               /*!<PC[15] pin */
#define EXTI_EXTICR4_EXTI15_PD_Pos    (24U)
#define EXTI_EXTICR4_EXTI15_PD_Msk    (0x3U << EXTI_EXTICR4_EXTI15_PD_Pos)     /*!< 0x03000000 */
#define EXTI_EXTICR4_EXTI15_PD        EXTI_EXTICR4_EXTI15_PD_Msk               /*!<PD[15] pin */
#define EXTI_EXTICR4_EXTI15_PE_Pos    (26U)
#define EXTI_EXTICR4_EXTI15_PE_Msk    (0x1U << EXTI_EXTICR4_EXTI15_PE_Pos)     /*!< 0x04000000 */
#define EXTI_EXTICR4_EXTI15_PE        EXTI_EXTICR4_EXTI15_PE_Msk               /*!<PE[15] pin */
#define EXTI_EXTICR4_EXTI15_PF_Pos    (24U)
#define EXTI_EXTICR4_EXTI15_PF_Msk    (0x5U << EXTI_EXTICR4_EXTI15_PF_Pos)     /*!< 0x05000000 */
#define EXTI_EXTICR4_EXTI15_PF        EXTI_EXTICR4_EXTI15_PF_Msk               /*!<PF[15] pin */
#define EXTI_EXTICR4_EXTI15_PG_Pos    (25U)
#define EXTI_EXTICR4_EXTI15_PG_Msk    (0x3U << EXTI_EXTICR4_EXTI15_PG_Pos)     /*!< 0x06000000 */
#define EXTI_EXTICR4_EXTI15_PG        EXTI_EXTICR4_EXTI15_PG_Msk               /*!<PG[15] pin */
#define EXTI_EXTICR4_EXTI15_PH_Pos    (24U)
#define EXTI_EXTICR4_EXTI15_PH_Msk    (0x7U << EXTI_EXTICR4_EXTI15_PH_Pos)     /*!< 0x07000000 */
#define EXTI_EXTICR4_EXTI15_PH        EXTI_EXTICR4_EXTI15_PH_Msk               /*!<PH[15] pin */
#define EXTI_EXTICR4_EXTI15_PI_Pos    (27U)
#define EXTI_EXTICR4_EXTI15_PI_Msk    (0x1U << EXTI_EXTICR4_EXTI15_PI_Pos)     /*!< 0x08000000 */
#define EXTI_EXTICR4_EXTI15_PI        EXTI_EXTICR4_EXTI15_PI_Msk               /*!<PI[15] pin */
#define EXTI_EXTICR4_EXTI15_PJ_Pos    (24U)
#define EXTI_EXTICR4_EXTI15_PJ_Msk    (0x9U << EXTI_EXTICR4_EXTI15_PJ_Pos)     /*!< 0x09000000 */
#define EXTI_EXTICR4_EXTI15_PJ        EXTI_EXTICR4_EXTI15_PJ_Msk               /*!<PJ[15] pin */

/**********************  Bit definition for EXTI_HWCFGR1 register  ***************/
#define EXTI_HWCFGR1_NBEVENTS_Pos  (0U)
#define EXTI_HWCFGR1_NBEVENTS_Msk  (0xFFU << EXTI_HWCFGR1_NBEVENTS_Pos)          /*!< 0x000000FF */
#define EXTI_HWCFGR1_NBEVENTS       EXTI_HWCFGR1_NBEVENTS_Msk                    /*!< Number of EVENT */
#define EXTI_HWCFGR1_NBCPUS_Pos    (8U)
#define EXTI_HWCFGR1_NBCPUS_Msk    (0xFU << EXTI_HWCFGR1_NBCPUS_Pos)             /*!< 0x00000F00 */
#define EXTI_HWCFGR1_NBCPUS         EXTI_HWCFGR1_NBCPUS_Msk                      /*!< Number of CPUs */
#define EXTI_HWCFGR1_CPUEVTEN_Pos  (12U)
#define EXTI_HWCFGR1_CPUEVTEN_Msk  (0xFU << EXTI_HWCFGR1_CPUEVTEN_Pos)           /*!< 0x0000F000 */
#define EXTI_HWCFGR1_CPUEVTEN       EXTI_HWCFGR1_CPUEVTEN_Msk                    /*!< CPU(m) event output enable */
#define EXTI_HWCFGR1_NBIOPORT_Pos  (16U)
#define EXTI_HWCFGR1_NBIOPORT_Msk  (0xFFU << EXTI_HWCFGR1_NBIOPORT_Pos)          /*!< 0x00FF0000 */
#define EXTI_HWCFGR1_NBIOPORT       EXTI_HWCFGR1_NBIOPORT_Msk                    /*!< Number of IO ports on EXTI */

/**********************  Bit definition for EXTI_VERR register  *****************/
#define EXTI_VERR_MINREV_Pos      (0U)
#define EXTI_VERR_MINREV_Msk      (0xFU << EXTI_VERR_MINREV_Pos)               /*!< 0x0000000F */
#define EXTI_VERR_MINREV          EXTI_VERR_MINREV_Msk                         /*!< Minor Revision number */
#define EXTI_VERR_MAJREV_Pos      (4U)
#define EXTI_VERR_MAJREV_Msk      (0xFU << EXTI_VERR_MAJREV_Pos)               /*!< 0x000000F0 */
#define EXTI_VERR_MAJREV          EXTI_VERR_MAJREV_Msk                         /*!< Major Revision number */

/**********************  Bit definition for EXTI_IPIDR register  ****************/
#define EXTI_IPIDR_IPID_Pos       (0U)
#define EXTI_IPIDR_IPID_Msk       (0xFFFFFFFFU << EXTI_IPIDR_IPID_Pos)         /*!< 0xFFFFFFFF */
#define EXTI_IPIDR_IPID           EXTI_IPIDR_IPID_Msk                          /*!< IP Identification */

/**********************  Bit definition for EXTI_SIDR register  *****************/
#define EXTI_SIDR_SID_Pos         (0U)
#define EXTI_SIDR_SID_Msk         (0xFFFFFFFFU << EXTI_SIDR_SID_Pos)           /*!< 0xFFFFFFFF */
#define EXTI_SIDR_SID             EXTI_SIDR_SID_Msk                            /*!< IP size identification */

/******************************************************************************/
/*                                                                            */
/*                           FDCAN Controller                                 */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for FDCAN_CCCR register  *****************/
#define FDCAN_CCCR_INIT_Pos       (0U)
#define FDCAN_CCCR_INIT_Msk       (0x1U << FDCAN_CCCR_INIT_Pos)                /*!< 0x00000001 */
#define FDCAN_CCCR_INIT           FDCAN_CCCR_INIT_Msk                          /*!< Initialization bit */
#define FDCAN_CCCR_CCCE_Pos       (1U)
#define FDCAN_CCCR_CCCE_Msk       (0x1U << FDCAN_CCCR_CCCE_Pos)                /*!< 0x00000002 */
#define FDCAN_CCCR_CCCE           FDCAN_CCCR_CCCE_Msk                          /*!< Configuration Change Enable bit */


/******************************************************************************/
/*                                                                            */
/*                          Flexible Memory Controller                        */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for FMC_BCR1 register  *******************/
#define FMC_BCR1_MBKEN_Pos         (0U)
#define FMC_BCR1_MBKEN_Msk         (0x1U << FMC_BCR1_MBKEN_Pos)                /*!< 0x00000001 */
#define FMC_BCR1_MBKEN             FMC_BCR1_MBKEN_Msk                          /*!<Memory bank enable bit                 */
#define FMC_BCR1_MUXEN_Pos         (1U)
#define FMC_BCR1_MUXEN_Msk         (0x1U << FMC_BCR1_MUXEN_Pos)                /*!< 0x00000002 */
#define FMC_BCR1_MUXEN             FMC_BCR1_MUXEN_Msk                          /*!<Address/data multiplexing enable bit   */

#define FMC_BCR1_MTYP_Pos          (2U)
#define FMC_BCR1_MTYP_Msk          (0x3U << FMC_BCR1_MTYP_Pos)                 /*!< 0x0000000C */
#define FMC_BCR1_MTYP              FMC_BCR1_MTYP_Msk                           /*!<MTYP[1:0] bits (Memory type)           */
#define FMC_BCR1_MTYP_0            (0x1U << FMC_BCR1_MTYP_Pos)                 /*!< 0x00000004 */
#define FMC_BCR1_MTYP_1            (0x2U << FMC_BCR1_MTYP_Pos)                 /*!< 0x00000008 */

#define FMC_BCR1_MWID_Pos          (4U)
#define FMC_BCR1_MWID_Msk          (0x3U << FMC_BCR1_MWID_Pos)                 /*!< 0x00000030 */
#define FMC_BCR1_MWID              FMC_BCR1_MWID_Msk                           /*!<MWID[1:0] bits (Memory data bus width) */
#define FMC_BCR1_MWID_0            (0x1U << FMC_BCR1_MWID_Pos)                 /*!< 0x00000010 */
#define FMC_BCR1_MWID_1            (0x2U << FMC_BCR1_MWID_Pos)                 /*!< 0x00000020 */

#define FMC_BCR1_FACCEN_Pos        (6U)
#define FMC_BCR1_FACCEN_Msk        (0x1U << FMC_BCR1_FACCEN_Pos)               /*!< 0x00000040 */
#define FMC_BCR1_FACCEN            FMC_BCR1_FACCEN_Msk                         /*!<Flash access enable        */
#define FMC_BCR1_BURSTEN_Pos       (8U)
#define FMC_BCR1_BURSTEN_Msk       (0x1U << FMC_BCR1_BURSTEN_Pos)              /*!< 0x00000100 */
#define FMC_BCR1_BURSTEN           FMC_BCR1_BURSTEN_Msk                        /*!<Burst enable bit           */
#define FMC_BCR1_WAITPOL_Pos       (9U)
#define FMC_BCR1_WAITPOL_Msk       (0x1U << FMC_BCR1_WAITPOL_Pos)              /*!< 0x00000200 */
#define FMC_BCR1_WAITPOL           FMC_BCR1_WAITPOL_Msk                        /*!<Wait signal polarity bit   */
#define FMC_BCR1_WRAPMOD_Pos       (10U)
#define FMC_BCR1_WRAPMOD_Msk       (0x1U << FMC_BCR1_WRAPMOD_Pos)              /*!< 0x00000400 */
#define FMC_BCR1_WRAPMOD           FMC_BCR1_WRAPMOD_Msk                        /*!<Wrapped burst mode support */
#define FMC_BCR1_WAITCFG_Pos       (11U)
#define FMC_BCR1_WAITCFG_Msk       (0x1U << FMC_BCR1_WAITCFG_Pos)              /*!< 0x00000800 */
#define FMC_BCR1_WAITCFG           FMC_BCR1_WAITCFG_Msk                        /*!<Wait timing configuration  */
#define FMC_BCR1_WREN_Pos          (12U)
#define FMC_BCR1_WREN_Msk          (0x1U << FMC_BCR1_WREN_Pos)                 /*!< 0x00001000 */
#define FMC_BCR1_WREN              FMC_BCR1_WREN_Msk                           /*!<Write enable bit           */
#define FMC_BCR1_WAITEN_Pos        (13U)
#define FMC_BCR1_WAITEN_Msk        (0x1U << FMC_BCR1_WAITEN_Pos)               /*!< 0x00002000 */
#define FMC_BCR1_WAITEN            FMC_BCR1_WAITEN_Msk                         /*!<Wait enable bit            */
#define FMC_BCR1_EXTMOD_Pos        (14U)
#define FMC_BCR1_EXTMOD_Msk        (0x1U << FMC_BCR1_EXTMOD_Pos)               /*!< 0x00004000 */
#define FMC_BCR1_EXTMOD            FMC_BCR1_EXTMOD_Msk                         /*!<Extended mode enable       */
#define FMC_BCR1_ASYNCWAIT_Pos     (15U)
#define FMC_BCR1_ASYNCWAIT_Msk     (0x1U << FMC_BCR1_ASYNCWAIT_Pos)            /*!< 0x00008000 */
#define FMC_BCR1_ASYNCWAIT         FMC_BCR1_ASYNCWAIT_Msk                      /*!<Asynchronous wait          */

#define FMC_BCR1_CPSIZE_Pos        (16U)
#define FMC_BCR1_CPSIZE_Msk        (0x7U << FMC_BCR1_CPSIZE_Pos)               /*!< 0x00070000 */
#define FMC_BCR1_CPSIZE            FMC_BCR1_CPSIZE_Msk                         /*!<PSIZE[2:0] bits CRAM Page Size */
#define FMC_BCR1_CPSIZE_0          (0x1U << FMC_BCR1_CPSIZE_Pos)               /*!< 0x00010000 */
#define FMC_BCR1_CPSIZE_1          (0x2U << FMC_BCR1_CPSIZE_Pos)               /*!< 0x00020000 */
#define FMC_BCR1_CPSIZE_2          (0x4U << FMC_BCR1_CPSIZE_Pos)               /*!< 0x00040000 */

#define FMC_BCR1_CBURSTRW_Pos      (19U)
#define FMC_BCR1_CBURSTRW_Msk      (0x1U << FMC_BCR1_CBURSTRW_Pos)             /*!< 0x00080000 */
#define FMC_BCR1_CBURSTRW          FMC_BCR1_CBURSTRW_Msk                       /*!<Write burst enable         */
#define FMC_BCR1_CCLKEN_Pos        (20U)
#define FMC_BCR1_CCLKEN_Msk        (0x1U << FMC_BCR1_CCLKEN_Pos)               /*!< 0x00100000 */
#define FMC_BCR1_CCLKEN            FMC_BCR1_CCLKEN_Msk                         /*!<Continous clock enable     */

#define FMC_BCR1_NBLSET_Pos        (22U)
#define FMC_BCR1_NBLSET_Msk        (0x3U << FMC_BCR1_NBLSET_Pos)                /*!< 0x00C00000 */
#define FMC_BCR1_NBLSET            FMC_BCR1_NBLSET_Msk                          /*!< NBLSET[1:0] bits Byte lane (NBL) SETUP */
#define FMC_BCR1_NBLSET_0          (0x1U << FMC_BCR1_NBLSET_Pos)                /*!< 0x00400000 */
#define FMC_BCR1_NBLSET_1          (0x2U << FMC_BCR1_NBLSET_Pos)                /*!< 0x00800000 */

#define FMC_BCR1_FMCEN_Pos         (31U)
#define FMC_BCR1_FMCEN_Msk         (0x1UL << FMC_BCR1_FMCEN_Pos)                /*!< 0x80000000 */
#define FMC_BCR1_FMCEN             FMC_BCR1_FMCEN_Msk                           /*!<FMC controller enable*/

/******************  Bit definition for FMC_BCR2 register  *******************/
#define FMC_BCR2_MBKEN_Pos         (0U)
#define FMC_BCR2_MBKEN_Msk         (0x1U << FMC_BCR2_MBKEN_Pos)                /*!< 0x00000001 */
#define FMC_BCR2_MBKEN             FMC_BCR2_MBKEN_Msk                          /*!<Memory bank enable bit                 */
#define FMC_BCR2_MUXEN_Pos         (1U)
#define FMC_BCR2_MUXEN_Msk         (0x1U << FMC_BCR2_MUXEN_Pos)                /*!< 0x00000002 */
#define FMC_BCR2_MUXEN             FMC_BCR2_MUXEN_Msk                          /*!<Address/data multiplexing enable bit   */

#define FMC_BCR2_MTYP_Pos          (2U)
#define FMC_BCR2_MTYP_Msk          (0x3U << FMC_BCR2_MTYP_Pos)                 /*!< 0x0000000C */
#define FMC_BCR2_MTYP              FMC_BCR2_MTYP_Msk                           /*!<MTYP[1:0] bits (Memory type)           */
#define FMC_BCR2_MTYP_0            (0x1U << FMC_BCR2_MTYP_Pos)                 /*!< 0x00000004 */
#define FMC_BCR2_MTYP_1            (0x2U << FMC_BCR2_MTYP_Pos)                 /*!< 0x00000008 */

#define FMC_BCR2_MWID_Pos          (4U)
#define FMC_BCR2_MWID_Msk          (0x3U << FMC_BCR2_MWID_Pos)                 /*!< 0x00000030 */
#define FMC_BCR2_MWID              FMC_BCR2_MWID_Msk                           /*!<MWID[1:0] bits (Memory data bus width) */
#define FMC_BCR2_MWID_0            (0x1U << FMC_BCR2_MWID_Pos)                 /*!< 0x00000010 */
#define FMC_BCR2_MWID_1            (0x2U << FMC_BCR2_MWID_Pos)                 /*!< 0x00000020 */

#define FMC_BCR2_FACCEN_Pos        (6U)
#define FMC_BCR2_FACCEN_Msk        (0x1U << FMC_BCR2_FACCEN_Pos)               /*!< 0x00000040 */
#define FMC_BCR2_FACCEN            FMC_BCR2_FACCEN_Msk                         /*!<Flash access enable        */
#define FMC_BCR2_BURSTEN_Pos       (8U)
#define FMC_BCR2_BURSTEN_Msk       (0x1U << FMC_BCR2_BURSTEN_Pos)              /*!< 0x00000100 */
#define FMC_BCR2_BURSTEN           FMC_BCR2_BURSTEN_Msk                        /*!<Burst enable bit           */
#define FMC_BCR2_WAITPOL_Pos       (9U)
#define FMC_BCR2_WAITPOL_Msk       (0x1U << FMC_BCR2_WAITPOL_Pos)              /*!< 0x00000200 */
#define FMC_BCR2_WAITPOL           FMC_BCR2_WAITPOL_Msk                        /*!<Wait signal polarity bit   */
#define FMC_BCR2_WRAPMOD_Pos       (10U)
#define FMC_BCR2_WRAPMOD_Msk       (0x1U << FMC_BCR2_WRAPMOD_Pos)              /*!< 0x00000400 */
#define FMC_BCR2_WRAPMOD           FMC_BCR2_WRAPMOD_Msk                        /*!<Wrapped burst mode support */
#define FMC_BCR2_WAITCFG_Pos       (11U)
#define FMC_BCR2_WAITCFG_Msk       (0x1U << FMC_BCR2_WAITCFG_Pos)              /*!< 0x00000800 */
#define FMC_BCR2_WAITCFG           FMC_BCR2_WAITCFG_Msk                        /*!<Wait timing configuration  */
#define FMC_BCR2_WREN_Pos          (12U)
#define FMC_BCR2_WREN_Msk          (0x1U << FMC_BCR2_WREN_Pos)                 /*!< 0x00001000 */
#define FMC_BCR2_WREN              FMC_BCR2_WREN_Msk                           /*!<Write enable bit           */
#define FMC_BCR2_WAITEN_Pos        (13U)
#define FMC_BCR2_WAITEN_Msk        (0x1U << FMC_BCR2_WAITEN_Pos)               /*!< 0x00002000 */
#define FMC_BCR2_WAITEN            FMC_BCR2_WAITEN_Msk                         /*!<Wait enable bit            */
#define FMC_BCR2_EXTMOD_Pos        (14U)
#define FMC_BCR2_EXTMOD_Msk        (0x1U << FMC_BCR2_EXTMOD_Pos)               /*!< 0x00004000 */
#define FMC_BCR2_EXTMOD            FMC_BCR2_EXTMOD_Msk                         /*!<Extended mode enable       */
#define FMC_BCR2_ASYNCWAIT_Pos     (15U)
#define FMC_BCR2_ASYNCWAIT_Msk     (0x1U << FMC_BCR2_ASYNCWAIT_Pos)            /*!< 0x00008000 */
#define FMC_BCR2_ASYNCWAIT         FMC_BCR2_ASYNCWAIT_Msk                      /*!<Asynchronous wait          */

#define FMC_BCR2_PSIZE_Pos         (16U)
#define FMC_BCR2_PSIZE_Msk         (0x7U << FMC_BCR2_PSIZE_Pos)                /*!< 0x00070000 */
#define FMC_BCR2_PSIZE             FMC_BCR2_PSIZE_Msk                          /*!<PSIZE[2:0] bits CRAM Page Size */
#define FMC_BCR2_PSIZE_0           (0x1U << FMC_BCR2_PSIZE_Pos)                /*!< 0x00010000 */
#define FMC_BCR2_PSIZE_1           (0x2U << FMC_BCR2_PSIZE_Pos)                /*!< 0x00020000 */
#define FMC_BCR2_PSIZE_2           (0x4U << FMC_BCR2_PSIZE_Pos)                /*!< 0x00040000 */

#define FMC_BCR2_CBURSTRW_Pos      (19U)
#define FMC_BCR2_CBURSTRW_Msk      (0x1U << FMC_BCR2_CBURSTRW_Pos)             /*!< 0x00080000 */
#define FMC_BCR2_CBURSTRW          FMC_BCR2_CBURSTRW_Msk                       /*!<Write burst enable         */

#define FMC_BCR2_NBLSET_Pos        (22U)
#define FMC_BCR2_NBLSET_Msk        (0x3U << FMC_BCR1_NBLSET_Pos)                /*!< 0x00C00000 */
#define FMC_BCR2_NBLSET            FMC_BCR1_NBLSET_Msk                          /*!< NBLSET[1:0] bits Byte lane (NBL) SETUP */
#define FMC_BCR2_NBLSET_0          (0x1U << FMC_BCR1_NBLSET_Pos)                /*!< 0x00400000 */
#define FMC_BCR2_NBLSET_1          (0x2U << FMC_BCR1_NBLSET_Pos)                /*!< 0x00800000 */

/******************  Bit definition for FMC_BCR3 register  *******************/
#define FMC_BCR3_MBKEN_Pos         (0U)
#define FMC_BCR3_MBKEN_Msk         (0x1U << FMC_BCR3_MBKEN_Pos)                /*!< 0x00000001 */
#define FMC_BCR3_MBKEN             FMC_BCR3_MBKEN_Msk                          /*!<Memory bank enable bit                 */
#define FMC_BCR3_MUXEN_Pos         (1U)
#define FMC_BCR3_MUXEN_Msk         (0x1U << FMC_BCR3_MUXEN_Pos)                /*!< 0x00000002 */
#define FMC_BCR3_MUXEN             FMC_BCR3_MUXEN_Msk                          /*!<Address/data multiplexing enable bit   */

#define FMC_BCR3_MTYP_Pos          (2U)
#define FMC_BCR3_MTYP_Msk          (0x3U << FMC_BCR3_MTYP_Pos)                 /*!< 0x0000000C */
#define FMC_BCR3_MTYP              FMC_BCR3_MTYP_Msk                           /*!<MTYP[1:0] bits (Memory type)           */
#define FMC_BCR3_MTYP_0            (0x1U << FMC_BCR3_MTYP_Pos)                 /*!< 0x00000004 */
#define FMC_BCR3_MTYP_1            (0x2U << FMC_BCR3_MTYP_Pos)                 /*!< 0x00000008 */

#define FMC_BCR3_MWID_Pos          (4U)
#define FMC_BCR3_MWID_Msk          (0x3U << FMC_BCR3_MWID_Pos)                 /*!< 0x00000030 */
#define FMC_BCR3_MWID              FMC_BCR3_MWID_Msk                           /*!<MWID[1:0] bits (Memory data bus width) */
#define FMC_BCR3_MWID_0            (0x1U << FMC_BCR3_MWID_Pos)                 /*!< 0x00000010 */
#define FMC_BCR3_MWID_1            (0x2U << FMC_BCR3_MWID_Pos)                 /*!< 0x00000020 */

#define FMC_BCR3_FACCEN_Pos        (6U)
#define FMC_BCR3_FACCEN_Msk        (0x1U << FMC_BCR3_FACCEN_Pos)               /*!< 0x00000040 */
#define FMC_BCR3_FACCEN            FMC_BCR3_FACCEN_Msk                         /*!<Flash access enable        */
#define FMC_BCR3_BURSTEN_Pos       (8U)
#define FMC_BCR3_BURSTEN_Msk       (0x1U << FMC_BCR3_BURSTEN_Pos)              /*!< 0x00000100 */
#define FMC_BCR3_BURSTEN           FMC_BCR3_BURSTEN_Msk                        /*!<Burst enable bit           */
#define FMC_BCR3_WAITPOL_Pos       (9U)
#define FMC_BCR3_WAITPOL_Msk       (0x1U << FMC_BCR3_WAITPOL_Pos)              /*!< 0x00000200 */
#define FMC_BCR3_WAITPOL           FMC_BCR3_WAITPOL_Msk                        /*!<Wait signal polarity bit   */
#define FMC_BCR3_WRAPMOD_Pos       (10U)
#define FMC_BCR3_WRAPMOD_Msk       (0x1U << FMC_BCR3_WRAPMOD_Pos)              /*!< 0x00000400 */
#define FMC_BCR3_WRAPMOD           FMC_BCR3_WRAPMOD_Msk                        /*!<Wrapped burst mode support */
#define FMC_BCR3_WAITCFG_Pos       (11U)
#define FMC_BCR3_WAITCFG_Msk       (0x1U << FMC_BCR3_WAITCFG_Pos)              /*!< 0x00000800 */
#define FMC_BCR3_WAITCFG           FMC_BCR3_WAITCFG_Msk                        /*!<Wait timing configuration  */
#define FMC_BCR3_WREN_Pos          (12U)
#define FMC_BCR3_WREN_Msk          (0x1U << FMC_BCR3_WREN_Pos)                 /*!< 0x00001000 */
#define FMC_BCR3_WREN              FMC_BCR3_WREN_Msk                           /*!<Write enable bit           */
#define FMC_BCR3_WAITEN_Pos        (13U)
#define FMC_BCR3_WAITEN_Msk        (0x1U << FMC_BCR3_WAITEN_Pos)               /*!< 0x00002000 */
#define FMC_BCR3_WAITEN            FMC_BCR3_WAITEN_Msk                         /*!<Wait enable bit            */
#define FMC_BCR3_EXTMOD_Pos        (14U)
#define FMC_BCR3_EXTMOD_Msk        (0x1U << FMC_BCR3_EXTMOD_Pos)               /*!< 0x00004000 */
#define FMC_BCR3_EXTMOD            FMC_BCR3_EXTMOD_Msk                         /*!<Extended mode enable       */
#define FMC_BCR3_ASYNCWAIT_Pos     (15U)
#define FMC_BCR3_ASYNCWAIT_Msk     (0x1U << FMC_BCR3_ASYNCWAIT_Pos)            /*!< 0x00008000 */
#define FMC_BCR3_ASYNCWAIT         FMC_BCR3_ASYNCWAIT_Msk                      /*!<Asynchronous wait          */

#define FMC_BCR3_PSIZE_Pos         (16U)
#define FMC_BCR3_PSIZE_Msk         (0x7U << FMC_BCR3_PSIZE_Pos)                /*!< 0x00070000 */
#define FMC_BCR3_PSIZE             FMC_BCR3_PSIZE_Msk                          /*!<PSIZE[2:0] bits CRAM Page Size */
#define FMC_BCR3_PSIZE_0           (0x1U << FMC_BCR3_PSIZE_Pos)                /*!< 0x00010000 */
#define FMC_BCR3_PSIZE_1           (0x2U << FMC_BCR3_PSIZE_Pos)                /*!< 0x00020000 */
#define FMC_BCR3_PSIZE_2           (0x4U << FMC_BCR3_PSIZE_Pos)                /*!< 0x00040000 */

#define FMC_BCR3_CBURSTRW_Pos      (19U)
#define FMC_BCR3_CBURSTRW_Msk      (0x1U << FMC_BCR3_CBURSTRW_Pos)             /*!< 0x00080000 */
#define FMC_BCR3_CBURSTRW          FMC_BCR3_CBURSTRW_Msk                       /*!<Write burst enable         */

#define FMC_BCR3_NBLSET_Pos        (22U)
#define FMC_BCR3_NBLSET_Msk        (0x3U << FMC_BCR1_NBLSET_Pos)                /*!< 0x00C00000 */
#define FMC_BCR3_NBLSET            FMC_BCR1_NBLSET_Msk                          /*!< NBLSET[1:0] bits Byte lane (NBL) SETUP */
#define FMC_BCR3_NBLSET_0          (0x1U << FMC_BCR1_NBLSET_Pos)                /*!< 0x00400000 */
#define FMC_BCR3_NBLSET_1          (0x2U << FMC_BCR1_NBLSET_Pos)                /*!< 0x00800000 */

/******************  Bit definition for FMC_BCR4 register  *******************/
#define FMC_BCR4_MBKEN_Pos         (0U)
#define FMC_BCR4_MBKEN_Msk         (0x1U << FMC_BCR4_MBKEN_Pos)                /*!< 0x00000001 */
#define FMC_BCR4_MBKEN             FMC_BCR4_MBKEN_Msk                          /*!<Memory bank enable bit                 */
#define FMC_BCR4_MUXEN_Pos         (1U)
#define FMC_BCR4_MUXEN_Msk         (0x1U << FMC_BCR4_MUXEN_Pos)                /*!< 0x00000002 */
#define FMC_BCR4_MUXEN             FMC_BCR4_MUXEN_Msk                          /*!<Address/data multiplexing enable bit   */

#define FMC_BCR4_MTYP_Pos          (2U)
#define FMC_BCR4_MTYP_Msk          (0x3U << FMC_BCR4_MTYP_Pos)                 /*!< 0x0000000C */
#define FMC_BCR4_MTYP              FMC_BCR4_MTYP_Msk                           /*!<MTYP[1:0] bits (Memory type)           */
#define FMC_BCR4_MTYP_0            (0x1U << FMC_BCR4_MTYP_Pos)                 /*!< 0x00000004 */
#define FMC_BCR4_MTYP_1            (0x2U << FMC_BCR4_MTYP_Pos)                 /*!< 0x00000008 */

#define FMC_BCR4_MWID_Pos          (4U)
#define FMC_BCR4_MWID_Msk          (0x3U << FMC_BCR4_MWID_Pos)                 /*!< 0x00000030 */
#define FMC_BCR4_MWID              FMC_BCR4_MWID_Msk                           /*!<MWID[1:0] bits (Memory data bus width) */
#define FMC_BCR4_MWID_0            (0x1U << FMC_BCR4_MWID_Pos)                 /*!< 0x00000010 */
#define FMC_BCR4_MWID_1            (0x2U << FMC_BCR4_MWID_Pos)                 /*!< 0x00000020 */

#define FMC_BCR4_FACCEN_Pos        (6U)
#define FMC_BCR4_FACCEN_Msk        (0x1U << FMC_BCR4_FACCEN_Pos)               /*!< 0x00000040 */
#define FMC_BCR4_FACCEN            FMC_BCR4_FACCEN_Msk                         /*!<Flash access enable        */
#define FMC_BCR4_BURSTEN_Pos       (8U)
#define FMC_BCR4_BURSTEN_Msk       (0x1U << FMC_BCR4_BURSTEN_Pos)              /*!< 0x00000100 */
#define FMC_BCR4_BURSTEN           FMC_BCR4_BURSTEN_Msk                        /*!<Burst enable bit           */
#define FMC_BCR4_WAITPOL_Pos       (9U)
#define FMC_BCR4_WAITPOL_Msk       (0x1U << FMC_BCR4_WAITPOL_Pos)              /*!< 0x00000200 */
#define FMC_BCR4_WAITPOL           FMC_BCR4_WAITPOL_Msk                        /*!<Wait signal polarity bit   */
#define FMC_BCR4_WRAPMOD_Pos       (10U)
#define FMC_BCR4_WRAPMOD_Msk       (0x1U << FMC_BCR4_WRAPMOD_Pos)              /*!< 0x00000400 */
#define FMC_BCR4_WRAPMOD           FMC_BCR4_WRAPMOD_Msk                        /*!<Wrapped burst mode support */
#define FMC_BCR4_WAITCFG_Pos       (11U)
#define FMC_BCR4_WAITCFG_Msk       (0x1U << FMC_BCR4_WAITCFG_Pos)              /*!< 0x00000800 */
#define FMC_BCR4_WAITCFG           FMC_BCR4_WAITCFG_Msk                        /*!<Wait timing configuration  */
#define FMC_BCR4_WREN_Pos          (12U)
#define FMC_BCR4_WREN_Msk          (0x1U << FMC_BCR4_WREN_Pos)                 /*!< 0x00001000 */
#define FMC_BCR4_WREN              FMC_BCR4_WREN_Msk                           /*!<Write enable bit           */
#define FMC_BCR4_WAITEN_Pos        (13U)
#define FMC_BCR4_WAITEN_Msk        (0x1U << FMC_BCR4_WAITEN_Pos)               /*!< 0x00002000 */
#define FMC_BCR4_WAITEN            FMC_BCR4_WAITEN_Msk                         /*!<Wait enable bit            */
#define FMC_BCR4_EXTMOD_Pos        (14U)
#define FMC_BCR4_EXTMOD_Msk        (0x1U << FMC_BCR4_EXTMOD_Pos)               /*!< 0x00004000 */
#define FMC_BCR4_EXTMOD            FMC_BCR4_EXTMOD_Msk                         /*!<Extended mode enable       */
#define FMC_BCR4_ASYNCWAIT_Pos     (15U)
#define FMC_BCR4_ASYNCWAIT_Msk     (0x1U << FMC_BCR4_ASYNCWAIT_Pos)            /*!< 0x00008000 */
#define FMC_BCR4_ASYNCWAIT         FMC_BCR4_ASYNCWAIT_Msk                      /*!<Asynchronous wait          */

#define FMC_BCR4_PSIZE_Pos         (16U)
#define FMC_BCR4_PSIZE_Msk         (0x7U << FMC_BCR4_PSIZE_Pos)                /*!< 0x00070000 */
#define FMC_BCR4_PSIZE             FMC_BCR4_PSIZE_Msk                          /*!<PSIZE[2:0] bits CRAM Page Size */
#define FMC_BCR4_PSIZE_0           (0x1U << FMC_BCR4_PSIZE_Pos)                /*!< 0x00010000 */
#define FMC_BCR4_PSIZE_1           (0x2U << FMC_BCR4_PSIZE_Pos)                /*!< 0x00020000 */
#define FMC_BCR4_PSIZE_2           (0x4U << FMC_BCR4_PSIZE_Pos)                /*!< 0x00040000 */

#define FMC_BCR4_CBURSTRW_Pos      (19U)
#define FMC_BCR4_CBURSTRW_Msk      (0x1U << FMC_BCR4_CBURSTRW_Pos)             /*!< 0x00080000 */
#define FMC_BCR4_CBURSTRW          FMC_BCR4_CBURSTRW_Msk                       /*!<Write burst enable         */

#define FMC_BCR4_NBLSET_Pos        (22U)
#define FMC_BCR4_NBLSET_Msk        (0x3U << FMC_BCR1_NBLSET_Pos)                /*!< 0x00C00000 */
#define FMC_BCR4_NBLSET            FMC_BCR1_NBLSET_Msk                          /*!< NBLSET[1:0] bits Byte lane (NBL) SETUP */
#define FMC_BCR4_NBLSET_0          (0x1U << FMC_BCR1_NBLSET_Pos)                /*!< 0x00400000 */
#define FMC_BCR4_NBLSET_1          (0x2U << FMC_BCR1_NBLSET_Pos)                /*!< 0x00800000 */

/******************  Bit definition for FMC_BTR1 register  ******************/
#define FMC_BTR1_ADDSET_Pos        (0U)
#define FMC_BTR1_ADDSET_Msk        (0xFU << FMC_BTR1_ADDSET_Pos)               /*!< 0x0000000F */
#define FMC_BTR1_ADDSET            FMC_BTR1_ADDSET_Msk                         /*!<ADDSET[3:0] bits (Address setup phase duration) */
#define FMC_BTR1_ADDSET_0          (0x1U << FMC_BTR1_ADDSET_Pos)               /*!< 0x00000001 */
#define FMC_BTR1_ADDSET_1          (0x2U << FMC_BTR1_ADDSET_Pos)               /*!< 0x00000002 */
#define FMC_BTR1_ADDSET_2          (0x4U << FMC_BTR1_ADDSET_Pos)               /*!< 0x00000004 */
#define FMC_BTR1_ADDSET_3          (0x8U << FMC_BTR1_ADDSET_Pos)               /*!< 0x00000008 */

#define FMC_BTR1_ADDHLD_Pos        (4U)
#define FMC_BTR1_ADDHLD_Msk        (0xFU << FMC_BTR1_ADDHLD_Pos)               /*!< 0x000000F0 */
#define FMC_BTR1_ADDHLD            FMC_BTR1_ADDHLD_Msk                         /*!<ADDHLD[3:0] bits (Address-hold phase duration)  */
#define FMC_BTR1_ADDHLD_0          (0x1U << FMC_BTR1_ADDHLD_Pos)               /*!< 0x00000010 */
#define FMC_BTR1_ADDHLD_1          (0x2U << FMC_BTR1_ADDHLD_Pos)               /*!< 0x00000020 */
#define FMC_BTR1_ADDHLD_2          (0x4U << FMC_BTR1_ADDHLD_Pos)               /*!< 0x00000040 */
#define FMC_BTR1_ADDHLD_3          (0x8U << FMC_BTR1_ADDHLD_Pos)               /*!< 0x00000080 */

#define FMC_BTR1_DATAST_Pos        (8U)
#define FMC_BTR1_DATAST_Msk        (0xFFU << FMC_BTR1_DATAST_Pos)              /*!< 0x0000FF00 */
#define FMC_BTR1_DATAST            FMC_BTR1_DATAST_Msk                         /*!<DATAST [3:0] bits (Data-phase duration) */
#define FMC_BTR1_DATAST_0          (0x01U << FMC_BTR1_DATAST_Pos)              /*!< 0x00000100 */
#define FMC_BTR1_DATAST_1          (0x02U << FMC_BTR1_DATAST_Pos)              /*!< 0x00000200 */
#define FMC_BTR1_DATAST_2          (0x04U << FMC_BTR1_DATAST_Pos)              /*!< 0x00000400 */
#define FMC_BTR1_DATAST_3          (0x08U << FMC_BTR1_DATAST_Pos)              /*!< 0x00000800 */
#define FMC_BTR1_DATAST_4          (0x10U << FMC_BTR1_DATAST_Pos)              /*!< 0x00001000 */
#define FMC_BTR1_DATAST_5          (0x20U << FMC_BTR1_DATAST_Pos)              /*!< 0x00002000 */
#define FMC_BTR1_DATAST_6          (0x40U << FMC_BTR1_DATAST_Pos)              /*!< 0x00004000 */
#define FMC_BTR1_DATAST_7          (0x80U << FMC_BTR1_DATAST_Pos)              /*!< 0x00008000 */

#define FMC_BTR1_BUSTURN_Pos       (16U)
#define FMC_BTR1_BUSTURN_Msk       (0xFU << FMC_BTR1_BUSTURN_Pos)              /*!< 0x000F0000 */
#define FMC_BTR1_BUSTURN           FMC_BTR1_BUSTURN_Msk                        /*!<BUSTURN[3:0] bits (Bus turnaround phase duration) */
#define FMC_BTR1_BUSTURN_0         (0x1U << FMC_BTR1_BUSTURN_Pos)              /*!< 0x00010000 */
#define FMC_BTR1_BUSTURN_1         (0x2U << FMC_BTR1_BUSTURN_Pos)              /*!< 0x00020000 */
#define FMC_BTR1_BUSTURN_2         (0x4U << FMC_BTR1_BUSTURN_Pos)              /*!< 0x00040000 */
#define FMC_BTR1_BUSTURN_3         (0x8U << FMC_BTR1_BUSTURN_Pos)              /*!< 0x00080000 */

#define FMC_BTR1_CLKDIV_Pos        (20U)
#define FMC_BTR1_CLKDIV_Msk        (0xFU << FMC_BTR1_CLKDIV_Pos)               /*!< 0x00F00000 */
#define FMC_BTR1_CLKDIV            FMC_BTR1_CLKDIV_Msk                         /*!<CLKDIV[3:0] bits (Clock divide ratio) */
#define FMC_BTR1_CLKDIV_0          (0x1U << FMC_BTR1_CLKDIV_Pos)               /*!< 0x00100000 */
#define FMC_BTR1_CLKDIV_1          (0x2U << FMC_BTR1_CLKDIV_Pos)               /*!< 0x00200000 */
#define FMC_BTR1_CLKDIV_2          (0x4U << FMC_BTR1_CLKDIV_Pos)               /*!< 0x00400000 */
#define FMC_BTR1_CLKDIV_3          (0x8U << FMC_BTR1_CLKDIV_Pos)               /*!< 0x00800000 */

#define FMC_BTR1_DATLAT_Pos        (24U)
#define FMC_BTR1_DATLAT_Msk        (0xFU << FMC_BTR1_DATLAT_Pos)               /*!< 0x0F000000 */
#define FMC_BTR1_DATLAT            FMC_BTR1_DATLAT_Msk                         /*!<DATLA[3:0] bits (Data latency) */
#define FMC_BTR1_DATLAT_0          (0x1U << FMC_BTR1_DATLAT_Pos)               /*!< 0x01000000 */
#define FMC_BTR1_DATLAT_1          (0x2U << FMC_BTR1_DATLAT_Pos)               /*!< 0x02000000 */
#define FMC_BTR1_DATLAT_2          (0x4U << FMC_BTR1_DATLAT_Pos)               /*!< 0x04000000 */
#define FMC_BTR1_DATLAT_3          (0x8U << FMC_BTR1_DATLAT_Pos)               /*!< 0x08000000 */

#define FMC_BTR1_ACCMOD_Pos        (28U)
#define FMC_BTR1_ACCMOD_Msk        (0x3U << FMC_BTR1_ACCMOD_Pos)               /*!< 0x30000000 */
#define FMC_BTR1_ACCMOD            FMC_BTR1_ACCMOD_Msk                         /*!<ACCMOD[1:0] bits (Access mode) */
#define FMC_BTR1_ACCMOD_0          (0x1U << FMC_BTR1_ACCMOD_Pos)               /*!< 0x10000000 */
#define FMC_BTR1_ACCMOD_1          (0x2U << FMC_BTR1_ACCMOD_Pos)               /*!< 0x20000000 */

#define FMC_BTR1_DATAHLD_Pos       (30U)
#define FMC_BTR1_DATAHLD_Msk       (0x3U << FMC_BTR1_DATAHLD_Pos)              /*!< 0xC0000000 */
#define FMC_BTR1_DATAHLD           FMC_BTR1_DATAHLD_Msk                        /*!<DATAHLD[1:0] bits (Data Hold phase duration) */
#define FMC_BTR1_DATAHLD_0         (0x1U << FMC_BTR1_DATAHLD_Pos)              /*!< 0x40000000 */
#define FMC_BTR1_DATAHLD_1         (0x2U << FMC_BTR1_DATAHLD_Pos)              /*!< 0x80000000 */

/******************  Bit definition for FMC_BTR2 register  *******************/
#define FMC_BTR2_ADDSET_Pos        (0U)
#define FMC_BTR2_ADDSET_Msk        (0xFU << FMC_BTR2_ADDSET_Pos)               /*!< 0x0000000F */
#define FMC_BTR2_ADDSET            FMC_BTR2_ADDSET_Msk                         /*!<ADDSET[3:0] bits (Address setup phase duration) */
#define FMC_BTR2_ADDSET_0          (0x1U << FMC_BTR2_ADDSET_Pos)               /*!< 0x00000001 */
#define FMC_BTR2_ADDSET_1          (0x2U << FMC_BTR2_ADDSET_Pos)               /*!< 0x00000002 */
#define FMC_BTR2_ADDSET_2          (0x4U << FMC_BTR2_ADDSET_Pos)               /*!< 0x00000004 */
#define FMC_BTR2_ADDSET_3          (0x8U << FMC_BTR2_ADDSET_Pos)               /*!< 0x00000008 */

#define FMC_BTR2_ADDHLD_Pos        (4U)
#define FMC_BTR2_ADDHLD_Msk        (0xFU << FMC_BTR2_ADDHLD_Pos)               /*!< 0x000000F0 */
#define FMC_BTR2_ADDHLD            FMC_BTR2_ADDHLD_Msk                         /*!<ADDHLD[3:0] bits (Address-hold phase duration) */
#define FMC_BTR2_ADDHLD_0          (0x1U << FMC_BTR2_ADDHLD_Pos)               /*!< 0x00000010 */
#define FMC_BTR2_ADDHLD_1          (0x2U << FMC_BTR2_ADDHLD_Pos)               /*!< 0x00000020 */
#define FMC_BTR2_ADDHLD_2          (0x4U << FMC_BTR2_ADDHLD_Pos)               /*!< 0x00000040 */
#define FMC_BTR2_ADDHLD_3          (0x8U << FMC_BTR2_ADDHLD_Pos)               /*!< 0x00000080 */

#define FMC_BTR2_DATAST_Pos        (8U)
#define FMC_BTR2_DATAST_Msk        (0xFFU << FMC_BTR2_DATAST_Pos)              /*!< 0x0000FF00 */
#define FMC_BTR2_DATAST            FMC_BTR2_DATAST_Msk                         /*!<DATAST [3:0] bits (Data-phase duration) */
#define FMC_BTR2_DATAST_0          (0x01U << FMC_BTR2_DATAST_Pos)              /*!< 0x00000100 */
#define FMC_BTR2_DATAST_1          (0x02U << FMC_BTR2_DATAST_Pos)              /*!< 0x00000200 */
#define FMC_BTR2_DATAST_2          (0x04U << FMC_BTR2_DATAST_Pos)              /*!< 0x00000400 */
#define FMC_BTR2_DATAST_3          (0x08U << FMC_BTR2_DATAST_Pos)              /*!< 0x00000800 */
#define FMC_BTR2_DATAST_4          (0x10U << FMC_BTR2_DATAST_Pos)              /*!< 0x00001000 */
#define FMC_BTR2_DATAST_5          (0x20U << FMC_BTR2_DATAST_Pos)              /*!< 0x00002000 */
#define FMC_BTR2_DATAST_6          (0x40U << FMC_BTR2_DATAST_Pos)              /*!< 0x00004000 */
#define FMC_BTR2_DATAST_7          (0x80U << FMC_BTR2_DATAST_Pos)              /*!< 0x00008000 */

#define FMC_BTR2_BUSTURN_Pos       (16U)
#define FMC_BTR2_BUSTURN_Msk       (0xFU << FMC_BTR2_BUSTURN_Pos)              /*!< 0x000F0000 */
#define FMC_BTR2_BUSTURN           FMC_BTR2_BUSTURN_Msk                        /*!<BUSTURN[3:0] bits (Bus turnaround phase duration) */
#define FMC_BTR2_BUSTURN_0         (0x1U << FMC_BTR2_BUSTURN_Pos)              /*!< 0x00010000 */
#define FMC_BTR2_BUSTURN_1         (0x2U << FMC_BTR2_BUSTURN_Pos)              /*!< 0x00020000 */
#define FMC_BTR2_BUSTURN_2         (0x4U << FMC_BTR2_BUSTURN_Pos)              /*!< 0x00040000 */
#define FMC_BTR2_BUSTURN_3         (0x8U << FMC_BTR2_BUSTURN_Pos)              /*!< 0x00080000 */

#define FMC_BTR2_CLKDIV_Pos        (20U)
#define FMC_BTR2_CLKDIV_Msk        (0xFU << FMC_BTR2_CLKDIV_Pos)               /*!< 0x00F00000 */
#define FMC_BTR2_CLKDIV            FMC_BTR2_CLKDIV_Msk                         /*!<CLKDIV[3:0] bits (Clock divide ratio) */
#define FMC_BTR2_CLKDIV_0          (0x1U << FMC_BTR2_CLKDIV_Pos)               /*!< 0x00100000 */
#define FMC_BTR2_CLKDIV_1          (0x2U << FMC_BTR2_CLKDIV_Pos)               /*!< 0x00200000 */
#define FMC_BTR2_CLKDIV_2          (0x4U << FMC_BTR2_CLKDIV_Pos)               /*!< 0x00400000 */
#define FMC_BTR2_CLKDIV_3          (0x8U << FMC_BTR2_CLKDIV_Pos)               /*!< 0x00800000 */

#define FMC_BTR2_DATLAT_Pos        (24U)
#define FMC_BTR2_DATLAT_Msk        (0xFU << FMC_BTR2_DATLAT_Pos)               /*!< 0x0F000000 */
#define FMC_BTR2_DATLAT            FMC_BTR2_DATLAT_Msk                         /*!<DATLA[3:0] bits (Data latency) */
#define FMC_BTR2_DATLAT_0          (0x1U << FMC_BTR2_DATLAT_Pos)               /*!< 0x01000000 */
#define FMC_BTR2_DATLAT_1          (0x2U << FMC_BTR2_DATLAT_Pos)               /*!< 0x02000000 */
#define FMC_BTR2_DATLAT_2          (0x4U << FMC_BTR2_DATLAT_Pos)               /*!< 0x04000000 */
#define FMC_BTR2_DATLAT_3          (0x8U << FMC_BTR2_DATLAT_Pos)               /*!< 0x08000000 */

#define FMC_BTR2_ACCMOD_Pos        (28U)
#define FMC_BTR2_ACCMOD_Msk        (0x3U << FMC_BTR2_ACCMOD_Pos)               /*!< 0x30000000 */
#define FMC_BTR2_ACCMOD            FMC_BTR2_ACCMOD_Msk                         /*!<ACCMOD[1:0] bits (Access mode) */
#define FMC_BTR2_ACCMOD_0          (0x1U << FMC_BTR2_ACCMOD_Pos)               /*!< 0x10000000 */
#define FMC_BTR2_ACCMOD_1          (0x2U << FMC_BTR2_ACCMOD_Pos)               /*!< 0x20000000 */

#define FMC_BTR2_DATAHLD_Pos       (30U)
#define FMC_BTR2_DATAHLD_Msk       (0x3U << FMC_BTR2_DATAHLD_Pos)              /*!< 0xC0000000 */
#define FMC_BTR2_DATAHLD           FMC_BTR2_DATAHLD_Msk                        /*!<DATAHLD[1:0] bits (Data Hold phase duration) */
#define FMC_BTR2_DATAHLD_0         (0x1U << FMC_BTR2_DATAHLD_Pos)              /*!< 0x40000000 */
#define FMC_BTR2_DATAHLD_1         (0x2U << FMC_BTR2_DATAHLD_Pos)              /*!< 0x80000000 */

/*******************  Bit definition for FMC_BTR3 register  *******************/
#define FMC_BTR3_ADDSET_Pos        (0U)
#define FMC_BTR3_ADDSET_Msk        (0xFU << FMC_BTR3_ADDSET_Pos)               /*!< 0x0000000F */
#define FMC_BTR3_ADDSET            FMC_BTR3_ADDSET_Msk                         /*!<ADDSET[3:0] bits (Address setup phase duration) */
#define FMC_BTR3_ADDSET_0          (0x1U << FMC_BTR3_ADDSET_Pos)               /*!< 0x00000001 */
#define FMC_BTR3_ADDSET_1          (0x2U << FMC_BTR3_ADDSET_Pos)               /*!< 0x00000002 */
#define FMC_BTR3_ADDSET_2          (0x4U << FMC_BTR3_ADDSET_Pos)               /*!< 0x00000004 */
#define FMC_BTR3_ADDSET_3          (0x8U << FMC_BTR3_ADDSET_Pos)               /*!< 0x00000008 */

#define FMC_BTR3_ADDHLD_Pos        (4U)
#define FMC_BTR3_ADDHLD_Msk        (0xFU << FMC_BTR3_ADDHLD_Pos)               /*!< 0x000000F0 */
#define FMC_BTR3_ADDHLD            FMC_BTR3_ADDHLD_Msk                         /*!<ADDHLD[3:0] bits (Address-hold phase duration) */
#define FMC_BTR3_ADDHLD_0          (0x1U << FMC_BTR3_ADDHLD_Pos)               /*!< 0x00000010 */
#define FMC_BTR3_ADDHLD_1          (0x2U << FMC_BTR3_ADDHLD_Pos)               /*!< 0x00000020 */
#define FMC_BTR3_ADDHLD_2          (0x4U << FMC_BTR3_ADDHLD_Pos)               /*!< 0x00000040 */
#define FMC_BTR3_ADDHLD_3          (0x8U << FMC_BTR3_ADDHLD_Pos)               /*!< 0x00000080 */

#define FMC_BTR3_DATAST_Pos        (8U)
#define FMC_BTR3_DATAST_Msk        (0xFFU << FMC_BTR3_DATAST_Pos)              /*!< 0x0000FF00 */
#define FMC_BTR3_DATAST            FMC_BTR3_DATAST_Msk                         /*!<DATAST [3:0] bits (Data-phase duration) */
#define FMC_BTR3_DATAST_0          (0x01U << FMC_BTR3_DATAST_Pos)              /*!< 0x00000100 */
#define FMC_BTR3_DATAST_1          (0x02U << FMC_BTR3_DATAST_Pos)              /*!< 0x00000200 */
#define FMC_BTR3_DATAST_2          (0x04U << FMC_BTR3_DATAST_Pos)              /*!< 0x00000400 */
#define FMC_BTR3_DATAST_3          (0x08U << FMC_BTR3_DATAST_Pos)              /*!< 0x00000800 */
#define FMC_BTR3_DATAST_4          (0x10U << FMC_BTR3_DATAST_Pos)              /*!< 0x00001000 */
#define FMC_BTR3_DATAST_5          (0x20U << FMC_BTR3_DATAST_Pos)              /*!< 0x00002000 */
#define FMC_BTR3_DATAST_6          (0x40U << FMC_BTR3_DATAST_Pos)              /*!< 0x00004000 */
#define FMC_BTR3_DATAST_7          (0x80U << FMC_BTR3_DATAST_Pos)              /*!< 0x00008000 */

#define FMC_BTR3_BUSTURN_Pos       (16U)
#define FMC_BTR3_BUSTURN_Msk       (0xFU << FMC_BTR3_BUSTURN_Pos)              /*!< 0x000F0000 */
#define FMC_BTR3_BUSTURN           FMC_BTR3_BUSTURN_Msk                        /*!<BUSTURN[3:0] bits (Bus turnaround phase duration) */
#define FMC_BTR3_BUSTURN_0         (0x1U << FMC_BTR3_BUSTURN_Pos)              /*!< 0x00010000 */
#define FMC_BTR3_BUSTURN_1         (0x2U << FMC_BTR3_BUSTURN_Pos)              /*!< 0x00020000 */
#define FMC_BTR3_BUSTURN_2         (0x4U << FMC_BTR3_BUSTURN_Pos)              /*!< 0x00040000 */
#define FMC_BTR3_BUSTURN_3         (0x8U << FMC_BTR3_BUSTURN_Pos)              /*!< 0x00080000 */

#define FMC_BTR3_CLKDIV_Pos        (20U)
#define FMC_BTR3_CLKDIV_Msk        (0xFU << FMC_BTR3_CLKDIV_Pos)               /*!< 0x00F00000 */
#define FMC_BTR3_CLKDIV            FMC_BTR3_CLKDIV_Msk                         /*!<CLKDIV[3:0] bits (Clock divide ratio) */
#define FMC_BTR3_CLKDIV_0          (0x1U << FMC_BTR3_CLKDIV_Pos)               /*!< 0x00100000 */
#define FMC_BTR3_CLKDIV_1          (0x2U << FMC_BTR3_CLKDIV_Pos)               /*!< 0x00200000 */
#define FMC_BTR3_CLKDIV_2          (0x4U << FMC_BTR3_CLKDIV_Pos)               /*!< 0x00400000 */
#define FMC_BTR3_CLKDIV_3          (0x8U << FMC_BTR3_CLKDIV_Pos)               /*!< 0x00800000 */

#define FMC_BTR3_DATLAT_Pos        (24U)
#define FMC_BTR3_DATLAT_Msk        (0xFU << FMC_BTR3_DATLAT_Pos)               /*!< 0x0F000000 */
#define FMC_BTR3_DATLAT            FMC_BTR3_DATLAT_Msk                         /*!<DATLA[3:0] bits (Data latency) */
#define FMC_BTR3_DATLAT_0          (0x1U << FMC_BTR3_DATLAT_Pos)               /*!< 0x01000000 */
#define FMC_BTR3_DATLAT_1          (0x2U << FMC_BTR3_DATLAT_Pos)               /*!< 0x02000000 */
#define FMC_BTR3_DATLAT_2          (0x4U << FMC_BTR3_DATLAT_Pos)               /*!< 0x04000000 */
#define FMC_BTR3_DATLAT_3          (0x8U << FMC_BTR3_DATLAT_Pos)               /*!< 0x08000000 */

#define FMC_BTR3_ACCMOD_Pos        (28U)
#define FMC_BTR3_ACCMOD_Msk        (0x3U << FMC_BTR3_ACCMOD_Pos)               /*!< 0x30000000 */
#define FMC_BTR3_ACCMOD            FMC_BTR3_ACCMOD_Msk                         /*!<ACCMOD[1:0] bits (Access mode) */
#define FMC_BTR3_ACCMOD_0          (0x1U << FMC_BTR3_ACCMOD_Pos)               /*!< 0x10000000 */
#define FMC_BTR3_ACCMOD_1          (0x2U << FMC_BTR3_ACCMOD_Pos)               /*!< 0x20000000 */

#define FMC_BTR3_DATAHLD_Pos       (30U)
#define FMC_BTR3_DATAHLD_Msk       (0x3U << FMC_BTR3_DATAHLD_Pos)              /*!< 0xC0000000 */
#define FMC_BTR3_DATAHLD           FMC_BTR3_DATAHLD_Msk                        /*!<DATAHLD[1:0] bits (Data Hold phase duration) */
#define FMC_BTR3_DATAHLD_0         (0x1U << FMC_BTR3_DATAHLD_Pos)              /*!< 0x40000000 */
#define FMC_BTR3_DATAHLD_1         (0x2U << FMC_BTR3_DATAHLD_Pos)              /*!< 0x80000000 */

/******************  Bit definition for FMC_BTR4 register  *******************/
#define FMC_BTR4_ADDSET_Pos        (0U)
#define FMC_BTR4_ADDSET_Msk        (0xFU << FMC_BTR4_ADDSET_Pos)               /*!< 0x0000000F */
#define FMC_BTR4_ADDSET            FMC_BTR4_ADDSET_Msk                         /*!<ADDSET[3:0] bits (Address setup phase duration) */
#define FMC_BTR4_ADDSET_0          (0x1U << FMC_BTR4_ADDSET_Pos)               /*!< 0x00000001 */
#define FMC_BTR4_ADDSET_1          (0x2U << FMC_BTR4_ADDSET_Pos)               /*!< 0x00000002 */
#define FMC_BTR4_ADDSET_2          (0x4U << FMC_BTR4_ADDSET_Pos)               /*!< 0x00000004 */
#define FMC_BTR4_ADDSET_3          (0x8U << FMC_BTR4_ADDSET_Pos)               /*!< 0x00000008 */

#define FMC_BTR4_ADDHLD_Pos        (4U)
#define FMC_BTR4_ADDHLD_Msk        (0xFU << FMC_BTR4_ADDHLD_Pos)               /*!< 0x000000F0 */
#define FMC_BTR4_ADDHLD            FMC_BTR4_ADDHLD_Msk                         /*!<ADDHLD[3:0] bits (Address-hold phase duration) */
#define FMC_BTR4_ADDHLD_0          (0x1U << FMC_BTR4_ADDHLD_Pos)               /*!< 0x00000010 */
#define FMC_BTR4_ADDHLD_1          (0x2U << FMC_BTR4_ADDHLD_Pos)               /*!< 0x00000020 */
#define FMC_BTR4_ADDHLD_2          (0x4U << FMC_BTR4_ADDHLD_Pos)               /*!< 0x00000040 */
#define FMC_BTR4_ADDHLD_3          (0x8U << FMC_BTR4_ADDHLD_Pos)               /*!< 0x00000080 */

#define FMC_BTR4_DATAST_Pos        (8U)
#define FMC_BTR4_DATAST_Msk        (0xFFU << FMC_BTR4_DATAST_Pos)              /*!< 0x0000FF00 */
#define FMC_BTR4_DATAST            FMC_BTR4_DATAST_Msk                         /*!<DATAST [3:0] bits (Data-phase duration) */
#define FMC_BTR4_DATAST_0          (0x01U << FMC_BTR4_DATAST_Pos)              /*!< 0x00000100 */
#define FMC_BTR4_DATAST_1          (0x02U << FMC_BTR4_DATAST_Pos)              /*!< 0x00000200 */
#define FMC_BTR4_DATAST_2          (0x04U << FMC_BTR4_DATAST_Pos)              /*!< 0x00000400 */
#define FMC_BTR4_DATAST_3          (0x08U << FMC_BTR4_DATAST_Pos)              /*!< 0x00000800 */
#define FMC_BTR4_DATAST_4          (0x10U << FMC_BTR4_DATAST_Pos)              /*!< 0x00001000 */
#define FMC_BTR4_DATAST_5          (0x20U << FMC_BTR4_DATAST_Pos)              /*!< 0x00002000 */
#define FMC_BTR4_DATAST_6          (0x40U << FMC_BTR4_DATAST_Pos)              /*!< 0x00004000 */
#define FMC_BTR4_DATAST_7          (0x80U << FMC_BTR4_DATAST_Pos)              /*!< 0x00008000 */

#define FMC_BTR4_BUSTURN_Pos       (16U)
#define FMC_BTR4_BUSTURN_Msk       (0xFU << FMC_BTR4_BUSTURN_Pos)              /*!< 0x000F0000 */
#define FMC_BTR4_BUSTURN           FMC_BTR4_BUSTURN_Msk                        /*!<BUSTURN[3:0] bits (Bus turnaround phase duration) */
#define FMC_BTR4_BUSTURN_0         (0x1U << FMC_BTR4_BUSTURN_Pos)              /*!< 0x00010000 */
#define FMC_BTR4_BUSTURN_1         (0x2U << FMC_BTR4_BUSTURN_Pos)              /*!< 0x00020000 */
#define FMC_BTR4_BUSTURN_2         (0x4U << FMC_BTR4_BUSTURN_Pos)              /*!< 0x00040000 */
#define FMC_BTR4_BUSTURN_3         (0x8U << FMC_BTR4_BUSTURN_Pos)              /*!< 0x00080000 */

#define FMC_BTR4_CLKDIV_Pos        (20U)
#define FMC_BTR4_CLKDIV_Msk        (0xFU << FMC_BTR4_CLKDIV_Pos)               /*!< 0x00F00000 */
#define FMC_BTR4_CLKDIV            FMC_BTR4_CLKDIV_Msk                         /*!<CLKDIV[3:0] bits (Clock divide ratio) */
#define FMC_BTR4_CLKDIV_0          (0x1U << FMC_BTR4_CLKDIV_Pos)               /*!< 0x00100000 */
#define FMC_BTR4_CLKDIV_1          (0x2U << FMC_BTR4_CLKDIV_Pos)               /*!< 0x00200000 */
#define FMC_BTR4_CLKDIV_2          (0x4U << FMC_BTR4_CLKDIV_Pos)               /*!< 0x00400000 */
#define FMC_BTR4_CLKDIV_3          (0x8U << FMC_BTR4_CLKDIV_Pos)               /*!< 0x00800000 */

#define FMC_BTR4_DATLAT_Pos        (24U)
#define FMC_BTR4_DATLAT_Msk        (0xFU << FMC_BTR4_DATLAT_Pos)               /*!< 0x0F000000 */
#define FMC_BTR4_DATLAT            FMC_BTR4_DATLAT_Msk                         /*!<DATLA[3:0] bits (Data latency) */
#define FMC_BTR4_DATLAT_0          (0x1U << FMC_BTR4_DATLAT_Pos)               /*!< 0x01000000 */
#define FMC_BTR4_DATLAT_1          (0x2U << FMC_BTR4_DATLAT_Pos)               /*!< 0x02000000 */
#define FMC_BTR4_DATLAT_2          (0x4U << FMC_BTR4_DATLAT_Pos)               /*!< 0x04000000 */
#define FMC_BTR4_DATLAT_3          (0x8U << FMC_BTR4_DATLAT_Pos)               /*!< 0x08000000 */

#define FMC_BTR4_ACCMOD_Pos        (28U)
#define FMC_BTR4_ACCMOD_Msk        (0x3U << FMC_BTR4_ACCMOD_Pos)               /*!< 0x30000000 */
#define FMC_BTR4_ACCMOD            FMC_BTR4_ACCMOD_Msk                         /*!<ACCMOD[1:0] bits (Access mode) */
#define FMC_BTR4_ACCMOD_0          (0x1U << FMC_BTR4_ACCMOD_Pos)               /*!< 0x10000000 */
#define FMC_BTR4_ACCMOD_1          (0x2U << FMC_BTR4_ACCMOD_Pos)               /*!< 0x20000000 */

#define FMC_BTR4_DATAHLD_Pos       (30U)
#define FMC_BTR4_DATAHLD_Msk       (0x3U << FMC_BTR4_DATAHLD_Pos)              /*!< 0xC0000000 */
#define FMC_BTR4_DATAHLD           FMC_BTR4_DATAHLD_Msk                        /*!<DATAHLD[1:0] bits (Data Hold phase duration) */
#define FMC_BTR4_DATAHLD_0         (0x1U << FMC_BTR4_DATAHLD_Pos)              /*!< 0x40000000 */
#define FMC_BTR4_DATAHLD_1         (0x2U << FMC_BTR4_DATAHLD_Pos)              /*!< 0x80000000 */

/******************  Bit definition for FMC_PCSCNTR register  *****************/
#define FMC_PCSCNTR_CSCOUNT_Pos        (0U)
#define FMC_PCSCNTR_CSCOUNT_Msk        (0xFFFFU << FMC_PCSCNTR_CSCOUNT_Pos)    /*!< 0x0000FFFF */
#define FMC_PCSCNTR_CSCOUNT            FMC_PCSCNTR_CSCOUNT_Msk                 /*!<CSCOUNT[15:0] bits Chip Select (CS) counter */

#define FMC_PCSCNTR_CNTB1EN_Pos        (16U)
#define FMC_PCSCNTR_CNTB1EN_Msk        (0x1U << FMC_PCSCNTR_CNTB1EN_Pos)       /*!< 0x00010000 */
#define FMC_PCSCNTR_CNTB1EN            FMC_PCSCNTR_CNTB1EN_Msk                 /*!<CNTB1EN bit Counter Bank1 enable */

#define FMC_PCSCNTR_CNTB2EN_Pos        (17U)
#define FMC_PCSCNTR_CNTB2EN_Msk        (0x1U << FMC_PCSCNTR_CNTB2EN_Pos)       /*!< 0x00020000 */
#define FMC_PCSCNTR_CNTB2EN            FMC_PCSCNTR_CNTB2EN_Msk                 /*!<CNTB2EN bit Counter Bank2 enable */

#define FMC_PCSCNTR_CNTB3EN_Pos        (18U)
#define FMC_PCSCNTR_CNTB3EN_Msk        (0x1U << FMC_PCSCNTR_CNTB3EN_Pos)       /*!< 0x00040000 */
#define FMC_PCSCNTR_CNTB3EN            FMC_PCSCNTR_CNTB3EN_Msk                 /*!<CNTB3EN bit Counter Bank3 enable */

#define FMC_PCSCNTR_CNTB4EN_Pos        (19U)
#define FMC_PCSCNTR_CNTB4EN_Msk        (0x1U << FMC_PCSCNTR_CNTB4EN_Pos)       /*!< 0x00080000 */
#define FMC_PCSCNTR_CNTB4EN            FMC_PCSCNTR_CNTB4EN_Msk                 /*!<CNTB4EN bit Counter Bank4 enable */

/******************  Bit definition for FMC_BWTR1 register  ******************/
#define FMC_BWTR1_ADDSET_Pos       (0U)
#define FMC_BWTR1_ADDSET_Msk       (0xFU << FMC_BWTR1_ADDSET_Pos)              /*!< 0x0000000F */
#define FMC_BWTR1_ADDSET           FMC_BWTR1_ADDSET_Msk                        /*!<ADDSET[3:0] bits (Address setup phase duration) */
#define FMC_BWTR1_ADDSET_0         (0x1U << FMC_BWTR1_ADDSET_Pos)              /*!< 0x00000001 */
#define FMC_BWTR1_ADDSET_1         (0x2U << FMC_BWTR1_ADDSET_Pos)              /*!< 0x00000002 */
#define FMC_BWTR1_ADDSET_2         (0x4U << FMC_BWTR1_ADDSET_Pos)              /*!< 0x00000004 */
#define FMC_BWTR1_ADDSET_3         (0x8U << FMC_BWTR1_ADDSET_Pos)              /*!< 0x00000008 */

#define FMC_BWTR1_ADDHLD_Pos       (4U)
#define FMC_BWTR1_ADDHLD_Msk       (0xFU << FMC_BWTR1_ADDHLD_Pos)              /*!< 0x000000F0 */
#define FMC_BWTR1_ADDHLD           FMC_BWTR1_ADDHLD_Msk                        /*!<ADDHLD[3:0] bits (Address-hold phase duration) */
#define FMC_BWTR1_ADDHLD_0         (0x1U << FMC_BWTR1_ADDHLD_Pos)              /*!< 0x00000010 */
#define FMC_BWTR1_ADDHLD_1         (0x2U << FMC_BWTR1_ADDHLD_Pos)              /*!< 0x00000020 */
#define FMC_BWTR1_ADDHLD_2         (0x4U << FMC_BWTR1_ADDHLD_Pos)              /*!< 0x00000040 */
#define FMC_BWTR1_ADDHLD_3         (0x8U << FMC_BWTR1_ADDHLD_Pos)              /*!< 0x00000080 */

#define FMC_BWTR1_DATAST_Pos       (8U)
#define FMC_BWTR1_DATAST_Msk       (0xFFU << FMC_BWTR1_DATAST_Pos)             /*!< 0x0000FF00 */
#define FMC_BWTR1_DATAST           FMC_BWTR1_DATAST_Msk                        /*!<DATAST [3:0] bits (Data-phase duration) */
#define FMC_BWTR1_DATAST_0         (0x01U << FMC_BWTR1_DATAST_Pos)             /*!< 0x00000100 */
#define FMC_BWTR1_DATAST_1         (0x02U << FMC_BWTR1_DATAST_Pos)             /*!< 0x00000200 */
#define FMC_BWTR1_DATAST_2         (0x04U << FMC_BWTR1_DATAST_Pos)             /*!< 0x00000400 */
#define FMC_BWTR1_DATAST_3         (0x08U << FMC_BWTR1_DATAST_Pos)             /*!< 0x00000800 */
#define FMC_BWTR1_DATAST_4         (0x10U << FMC_BWTR1_DATAST_Pos)             /*!< 0x00001000 */
#define FMC_BWTR1_DATAST_5         (0x20U << FMC_BWTR1_DATAST_Pos)             /*!< 0x00002000 */
#define FMC_BWTR1_DATAST_6         (0x40U << FMC_BWTR1_DATAST_Pos)             /*!< 0x00004000 */
#define FMC_BWTR1_DATAST_7         (0x80U << FMC_BWTR1_DATAST_Pos)             /*!< 0x00008000 */

#define FMC_BWTR1_CLKDIV_Pos       (20U)
#define FMC_BWTR1_CLKDIV_Msk       (0xFU << FMC_BWTR1_CLKDIV_Pos)              /*!< 0x00F00000 */
#define FMC_BWTR1_CLKDIV           FMC_BWTR1_CLKDIV_Msk                        /*!<CLKDIV[3:0] bits (Clock divide ratio) */
#define FMC_BWTR1_CLKDIV_0         (0x1U << FMC_BWTR1_CLKDIV_Pos)              /*!< 0x00100000 */
#define FMC_BWTR1_CLKDIV_1         (0x2U << FMC_BWTR1_CLKDIV_Pos)              /*!< 0x00200000 */
#define FMC_BWTR1_CLKDIV_2         (0x4U << FMC_BWTR1_CLKDIV_Pos)              /*!< 0x00400000 */
#define FMC_BWTR1_CLKDIV_3         (0x8U << FMC_BWTR1_CLKDIV_Pos)              /*!< 0x00800000 */

#define FMC_BWTR1_DATLAT_Pos       (24U)
#define FMC_BWTR1_DATLAT_Msk       (0xFU << FMC_BWTR1_DATLAT_Pos)              /*!< 0x0F000000 */
#define FMC_BWTR1_DATLAT           FMC_BWTR1_DATLAT_Msk                        /*!<DATLA[3:0] bits (Data latency) */
#define FMC_BWTR1_DATLAT_0         (0x1U << FMC_BWTR1_DATLAT_Pos)              /*!< 0x01000000 */
#define FMC_BWTR1_DATLAT_1         (0x2U << FMC_BWTR1_DATLAT_Pos)              /*!< 0x02000000 */
#define FMC_BWTR1_DATLAT_2         (0x4U << FMC_BWTR1_DATLAT_Pos)              /*!< 0x04000000 */
#define FMC_BWTR1_DATLAT_3         (0x8U << FMC_BWTR1_DATLAT_Pos)              /*!< 0x08000000 */

#define FMC_BWTR1_BUSTURN_Pos      (16U)
#define FMC_BWTR1_BUSTURN_Msk      (0xFU << FMC_BWTR1_BUSTURN_Pos)             /*!< 0x000F0000 */
#define FMC_BWTR1_BUSTURN          FMC_BWTR1_BUSTURN_Msk                       /*!<BUSTURN[3:0] bits (Bus turnaround phase duration) */
#define FMC_BWTR1_BUSTURN_0        (0x1U << FMC_BWTR1_BUSTURN_Pos)             /*!< 0x00010000 */
#define FMC_BWTR1_BUSTURN_1        (0x2U << FMC_BWTR1_BUSTURN_Pos)             /*!< 0x00020000 */
#define FMC_BWTR1_BUSTURN_2        (0x4U << FMC_BWTR1_BUSTURN_Pos)             /*!< 0x00040000 */
#define FMC_BWTR1_BUSTURN_3        (0x8U << FMC_BWTR1_BUSTURN_Pos)             /*!< 0x00080000 */


#define FMC_BWTR1_ACCMOD_Pos       (28U)
#define FMC_BWTR1_ACCMOD_Msk       (0x3U << FMC_BWTR1_ACCMOD_Pos)              /*!< 0x30000000 */
#define FMC_BWTR1_ACCMOD           FMC_BWTR1_ACCMOD_Msk                        /*!<ACCMOD[1:0] bits (Access mode) */
#define FMC_BWTR1_ACCMOD_0         (0x1U << FMC_BWTR1_ACCMOD_Pos)              /*!< 0x10000000 */
#define FMC_BWTR1_ACCMOD_1         (0x2U << FMC_BWTR1_ACCMOD_Pos)              /*!< 0x20000000 */

#define FMC_BWTR1_DATAHLD_Pos       (30U)
#define FMC_BWTR1_DATAHLD_Msk       (0x3U << FMC_BWTR1_DATAHLD_Pos)            /*!< 0xC0000000 */
#define FMC_BWTR1_DATAHLD           FMC_BWTR1_DATAHLD_Msk                      /*!<DATAHLD[1:0] bits (Data Hold phase duration) */
#define FMC_BWTR1_DATAHLD_0         (0x1U << FMC_BWTR1_DATAHLD_Pos)            /*!< 0x40000000 */
#define FMC_BWTR1_DATAHLD_1         (0x2U << FMC_BWTR1_DATAHLD_Pos)            /*!< 0x80000000 */

/******************  Bit definition for FMC_BWTR2 register  ******************/
#define FMC_BWTR2_ADDSET_Pos       (0U)
#define FMC_BWTR2_ADDSET_Msk       (0xFU << FMC_BWTR2_ADDSET_Pos)              /*!< 0x0000000F */
#define FMC_BWTR2_ADDSET           FMC_BWTR2_ADDSET_Msk                        /*!<ADDSET[3:0] bits (Address setup phase duration) */
#define FMC_BWTR2_ADDSET_0         (0x1U << FMC_BWTR2_ADDSET_Pos)              /*!< 0x00000001 */
#define FMC_BWTR2_ADDSET_1         (0x2U << FMC_BWTR2_ADDSET_Pos)              /*!< 0x00000002 */
#define FMC_BWTR2_ADDSET_2         (0x4U << FMC_BWTR2_ADDSET_Pos)              /*!< 0x00000004 */
#define FMC_BWTR2_ADDSET_3         (0x8U << FMC_BWTR2_ADDSET_Pos)              /*!< 0x00000008 */

#define FMC_BWTR2_ADDHLD_Pos       (4U)
#define FMC_BWTR2_ADDHLD_Msk       (0xFU << FMC_BWTR2_ADDHLD_Pos)              /*!< 0x000000F0 */
#define FMC_BWTR2_ADDHLD           FMC_BWTR2_ADDHLD_Msk                        /*!<ADDHLD[3:0] bits (Address-hold phase duration) */
#define FMC_BWTR2_ADDHLD_0         (0x1U << FMC_BWTR2_ADDHLD_Pos)              /*!< 0x00000010 */
#define FMC_BWTR2_ADDHLD_1         (0x2U << FMC_BWTR2_ADDHLD_Pos)              /*!< 0x00000020 */
#define FMC_BWTR2_ADDHLD_2         (0x4U << FMC_BWTR2_ADDHLD_Pos)              /*!< 0x00000040 */
#define FMC_BWTR2_ADDHLD_3         (0x8U << FMC_BWTR2_ADDHLD_Pos)              /*!< 0x00000080 */

#define FMC_BWTR2_DATAST_Pos       (8U)
#define FMC_BWTR2_DATAST_Msk       (0xFFU << FMC_BWTR2_DATAST_Pos)             /*!< 0x0000FF00 */
#define FMC_BWTR2_DATAST           FMC_BWTR2_DATAST_Msk                        /*!<DATAST [3:0] bits (Data-phase duration) */
#define FMC_BWTR2_DATAST_0         (0x01U << FMC_BWTR2_DATAST_Pos)             /*!< 0x00000100 */
#define FMC_BWTR2_DATAST_1         (0x02U << FMC_BWTR2_DATAST_Pos)             /*!< 0x00000200 */
#define FMC_BWTR2_DATAST_2         (0x04U << FMC_BWTR2_DATAST_Pos)             /*!< 0x00000400 */
#define FMC_BWTR2_DATAST_3         (0x08U << FMC_BWTR2_DATAST_Pos)             /*!< 0x00000800 */
#define FMC_BWTR2_DATAST_4         (0x10U << FMC_BWTR2_DATAST_Pos)             /*!< 0x00001000 */
#define FMC_BWTR2_DATAST_5         (0x20U << FMC_BWTR2_DATAST_Pos)             /*!< 0x00002000 */
#define FMC_BWTR2_DATAST_6         (0x40U << FMC_BWTR2_DATAST_Pos)             /*!< 0x00004000 */
#define FMC_BWTR2_DATAST_7         (0x80U << FMC_BWTR2_DATAST_Pos)             /*!< 0x00008000 */

#define FMC_BWTR2_CLKDIV_Pos       (20U)
#define FMC_BWTR2_CLKDIV_Msk       (0xFU << FMC_BWTR2_CLKDIV_Pos)              /*!< 0x00F00000 */
#define FMC_BWTR2_CLKDIV           FMC_BWTR2_CLKDIV_Msk                        /*!<CLKDIV[3:0] bits (Clock divide ratio) */
#define FMC_BWTR2_CLKDIV_0         (0x1U << FMC_BWTR2_CLKDIV_Pos)              /*!< 0x00100000 */
#define FMC_BWTR2_CLKDIV_1         (0x2U << FMC_BWTR2_CLKDIV_Pos)              /*!< 0x00200000 */
#define FMC_BWTR2_CLKDIV_2         (0x4U << FMC_BWTR2_CLKDIV_Pos)              /*!< 0x00400000 */
#define FMC_BWTR2_CLKDIV_3         (0x8U << FMC_BWTR2_CLKDIV_Pos)              /*!< 0x00800000 */

#define FMC_BWTR2_DATLAT_Pos       (24U)
#define FMC_BWTR2_DATLAT_Msk       (0xFU << FMC_BWTR2_DATLAT_Pos)              /*!< 0x0F000000 */
#define FMC_BWTR2_DATLAT           FMC_BWTR2_DATLAT_Msk                        /*!<DATLA[3:0] bits (Data latency) */
#define FMC_BWTR2_DATLAT_0         (0x1U << FMC_BWTR2_DATLAT_Pos)              /*!< 0x01000000 */
#define FMC_BWTR2_DATLAT_1         (0x2U << FMC_BWTR2_DATLAT_Pos)              /*!< 0x02000000 */
#define FMC_BWTR2_DATLAT_2         (0x4U << FMC_BWTR2_DATLAT_Pos)              /*!< 0x04000000 */
#define FMC_BWTR2_DATLAT_3         (0x8U << FMC_BWTR2_DATLAT_Pos)              /*!< 0x08000000 */

#define FMC_BWTR2_ACCMOD_Pos       (28U)
#define FMC_BWTR2_ACCMOD_Msk       (0x3U << FMC_BWTR2_ACCMOD_Pos)              /*!< 0x30000000 */
#define FMC_BWTR2_ACCMOD           FMC_BWTR2_ACCMOD_Msk                        /*!<ACCMOD[1:0] bits (Access mode) */
#define FMC_BWTR2_ACCMOD_0         (0x1U << FMC_BWTR2_ACCMOD_Pos)              /*!< 0x10000000 */
#define FMC_BWTR2_ACCMOD_1         (0x2U << FMC_BWTR2_ACCMOD_Pos)              /*!< 0x20000000 */

#define FMC_BWTR2_DATAHLD_Pos       (30U)
#define FMC_BWTR2_DATAHLD_Msk       (0x3U << FMC_BWTR2_DATAHLD_Pos)            /*!< 0xC0000000 */
#define FMC_BWTR2_DATAHLD           FMC_BWTR2_DATAHLD_Msk                      /*!<DATAHLD[1:0] bits (Data Hold phase duration) */
#define FMC_BWTR2_DATAHLD_0         (0x1U << FMC_BWTR2_DATAHLD_Pos)            /*!< 0x40000000 */
#define FMC_BWTR2_DATAHLD_1         (0x2U << FMC_BWTR2_DATAHLD_Pos)            /*!< 0x80000000 */

/******************  Bit definition for FMC_BWTR3 register  ******************/
#define FMC_BWTR3_ADDSET_Pos       (0U)
#define FMC_BWTR3_ADDSET_Msk       (0xFU << FMC_BWTR3_ADDSET_Pos)              /*!< 0x0000000F */
#define FMC_BWTR3_ADDSET           FMC_BWTR3_ADDSET_Msk                        /*!<ADDSET[3:0] bits (Address setup phase duration) */
#define FMC_BWTR3_ADDSET_0         (0x1U << FMC_BWTR3_ADDSET_Pos)              /*!< 0x00000001 */
#define FMC_BWTR3_ADDSET_1         (0x2U << FMC_BWTR3_ADDSET_Pos)              /*!< 0x00000002 */
#define FMC_BWTR3_ADDSET_2         (0x4U << FMC_BWTR3_ADDSET_Pos)              /*!< 0x00000004 */
#define FMC_BWTR3_ADDSET_3         (0x8U << FMC_BWTR3_ADDSET_Pos)              /*!< 0x00000008 */

#define FMC_BWTR3_ADDHLD_Pos       (4U)
#define FMC_BWTR3_ADDHLD_Msk       (0xFU << FMC_BWTR3_ADDHLD_Pos)              /*!< 0x000000F0 */
#define FMC_BWTR3_ADDHLD           FMC_BWTR3_ADDHLD_Msk                        /*!<ADDHLD[3:0] bits (Address-hold phase duration) */
#define FMC_BWTR3_ADDHLD_0         (0x1U << FMC_BWTR3_ADDHLD_Pos)              /*!< 0x00000010 */
#define FMC_BWTR3_ADDHLD_1         (0x2U << FMC_BWTR3_ADDHLD_Pos)              /*!< 0x00000020 */
#define FMC_BWTR3_ADDHLD_2         (0x4U << FMC_BWTR3_ADDHLD_Pos)              /*!< 0x00000040 */
#define FMC_BWTR3_ADDHLD_3         (0x8U << FMC_BWTR3_ADDHLD_Pos)              /*!< 0x00000080 */

#define FMC_BWTR3_DATAST_Pos       (8U)
#define FMC_BWTR3_DATAST_Msk       (0xFFU << FMC_BWTR3_DATAST_Pos)             /*!< 0x0000FF00 */
#define FMC_BWTR3_DATAST           FMC_BWTR3_DATAST_Msk                        /*!<DATAST [3:0] bits (Data-phase duration) */
#define FMC_BWTR3_DATAST_0         (0x01U << FMC_BWTR3_DATAST_Pos)             /*!< 0x00000100 */
#define FMC_BWTR3_DATAST_1         (0x02U << FMC_BWTR3_DATAST_Pos)             /*!< 0x00000200 */
#define FMC_BWTR3_DATAST_2         (0x04U << FMC_BWTR3_DATAST_Pos)             /*!< 0x00000400 */
#define FMC_BWTR3_DATAST_3         (0x08U << FMC_BWTR3_DATAST_Pos)             /*!< 0x00000800 */
#define FMC_BWTR3_DATAST_4         (0x10U << FMC_BWTR3_DATAST_Pos)             /*!< 0x00001000 */
#define FMC_BWTR3_DATAST_5         (0x20U << FMC_BWTR3_DATAST_Pos)             /*!< 0x00002000 */
#define FMC_BWTR3_DATAST_6         (0x40U << FMC_BWTR3_DATAST_Pos)             /*!< 0x00004000 */
#define FMC_BWTR3_DATAST_7         (0x80U << FMC_BWTR3_DATAST_Pos)             /*!< 0x00008000 */

#define FMC_BWTR3_CLKDIV_Pos       (20U)
#define FMC_BWTR3_CLKDIV_Msk       (0xFU << FMC_BWTR3_CLKDIV_Pos)              /*!< 0x00F00000 */
#define FMC_BWTR3_CLKDIV           FMC_BWTR3_CLKDIV_Msk                        /*!<CLKDIV[3:0] bits (Clock divide ratio) */
#define FMC_BWTR3_CLKDIV_0         (0x1U << FMC_BWTR3_CLKDIV_Pos)              /*!< 0x00100000 */
#define FMC_BWTR3_CLKDIV_1         (0x2U << FMC_BWTR3_CLKDIV_Pos)              /*!< 0x00200000 */
#define FMC_BWTR3_CLKDIV_2         (0x4U << FMC_BWTR3_CLKDIV_Pos)              /*!< 0x00400000 */
#define FMC_BWTR3_CLKDIV_3         (0x8U << FMC_BWTR3_CLKDIV_Pos)              /*!< 0x00800000 */

#define FMC_BWTR3_DATLAT_Pos       (24U)
#define FMC_BWTR3_DATLAT_Msk       (0xFU << FMC_BWTR3_DATLAT_Pos)              /*!< 0x0F000000 */
#define FMC_BWTR3_DATLAT           FMC_BWTR3_DATLAT_Msk                        /*!<DATLA[3:0] bits (Data latency) */
#define FMC_BWTR3_DATLAT_0         (0x1U << FMC_BWTR3_DATLAT_Pos)              /*!< 0x01000000 */
#define FMC_BWTR3_DATLAT_1         (0x2U << FMC_BWTR3_DATLAT_Pos)              /*!< 0x02000000 */
#define FMC_BWTR3_DATLAT_2         (0x4U << FMC_BWTR3_DATLAT_Pos)              /*!< 0x04000000 */
#define FMC_BWTR3_DATLAT_3         (0x8U << FMC_BWTR3_DATLAT_Pos)              /*!< 0x08000000 */

#define FMC_BWTR3_ACCMOD_Pos       (28U)
#define FMC_BWTR3_ACCMOD_Msk       (0x3U << FMC_BWTR3_ACCMOD_Pos)              /*!< 0x30000000 */
#define FMC_BWTR3_ACCMOD           FMC_BWTR3_ACCMOD_Msk                        /*!<ACCMOD[1:0] bits (Access mode) */
#define FMC_BWTR3_ACCMOD_0         (0x1U << FMC_BWTR3_ACCMOD_Pos)              /*!< 0x10000000 */
#define FMC_BWTR3_ACCMOD_1         (0x2U << FMC_BWTR3_ACCMOD_Pos)              /*!< 0x20000000 */

#define FMC_BWTR3_DATAHLD_Pos       (30U)
#define FMC_BWTR3_DATAHLD_Msk       (0x3U << FMC_BWTR3_DATAHLD_Pos)            /*!< 0xC0000000 */
#define FMC_BWTR3_DATAHLD           FMC_BWTR3_DATAHLD_Msk                      /*!<DATAHLD[1:0] bits (Data Hold phase duration) */
#define FMC_BWTR3_DATAHLD_0         (0x1U << FMC_BWTR3_DATAHLD_Pos)            /*!< 0x40000000 */
#define FMC_BWTR3_DATAHLD_1         (0x2U << FMC_BWTR3_DATAHLD_Pos)            /*!< 0x80000000 */

/******************  Bit definition for FMC_BWTR4 register  ******************/
#define FMC_BWTR4_ADDSET_Pos       (0U)
#define FMC_BWTR4_ADDSET_Msk       (0xFU << FMC_BWTR4_ADDSET_Pos)              /*!< 0x0000000F */
#define FMC_BWTR4_ADDSET           FMC_BWTR4_ADDSET_Msk                        /*!<ADDSET[3:0] bits (Address setup phase duration) */
#define FMC_BWTR4_ADDSET_0         (0x1U << FMC_BWTR4_ADDSET_Pos)              /*!< 0x00000001 */
#define FMC_BWTR4_ADDSET_1         (0x2U << FMC_BWTR4_ADDSET_Pos)              /*!< 0x00000002 */
#define FMC_BWTR4_ADDSET_2         (0x4U << FMC_BWTR4_ADDSET_Pos)              /*!< 0x00000004 */
#define FMC_BWTR4_ADDSET_3         (0x8U << FMC_BWTR4_ADDSET_Pos)              /*!< 0x00000008 */

#define FMC_BWTR4_ADDHLD_Pos       (4U)
#define FMC_BWTR4_ADDHLD_Msk       (0xFU << FMC_BWTR4_ADDHLD_Pos)              /*!< 0x000000F0 */
#define FMC_BWTR4_ADDHLD           FMC_BWTR4_ADDHLD_Msk                        /*!<ADDHLD[3:0] bits (Address-hold phase duration) */
#define FMC_BWTR4_ADDHLD_0         (0x1U << FMC_BWTR4_ADDHLD_Pos)              /*!< 0x00000010 */
#define FMC_BWTR4_ADDHLD_1         (0x2U << FMC_BWTR4_ADDHLD_Pos)              /*!< 0x00000020 */
#define FMC_BWTR4_ADDHLD_2         (0x4U << FMC_BWTR4_ADDHLD_Pos)              /*!< 0x00000040 */
#define FMC_BWTR4_ADDHLD_3         (0x8U << FMC_BWTR4_ADDHLD_Pos)              /*!< 0x00000080 */

#define FMC_BWTR4_DATAST_Pos       (8U)
#define FMC_BWTR4_DATAST_Msk       (0xFFU << FMC_BWTR4_DATAST_Pos)             /*!< 0x0000FF00 */
#define FMC_BWTR4_DATAST           FMC_BWTR4_DATAST_Msk                        /*!<DATAST [3:0] bits (Data-phase duration) */
#define FMC_BWTR4_DATAST_0         (0x01U << FMC_BWTR4_DATAST_Pos)             /*!< 0x00000100 */
#define FMC_BWTR4_DATAST_1         (0x02U << FMC_BWTR4_DATAST_Pos)             /*!< 0x00000200 */
#define FMC_BWTR4_DATAST_2         (0x04U << FMC_BWTR4_DATAST_Pos)             /*!< 0x00000400 */
#define FMC_BWTR4_DATAST_3         (0x08U << FMC_BWTR4_DATAST_Pos)             /*!< 0x00000800 */
#define FMC_BWTR4_DATAST_4         (0x10U << FMC_BWTR4_DATAST_Pos)             /*!< 0x00001000 */
#define FMC_BWTR4_DATAST_5         (0x20U << FMC_BWTR4_DATAST_Pos)             /*!< 0x00002000 */
#define FMC_BWTR4_DATAST_6         (0x40U << FMC_BWTR4_DATAST_Pos)             /*!< 0x00004000 */
#define FMC_BWTR4_DATAST_7         (0x80U << FMC_BWTR4_DATAST_Pos)             /*!< 0x00008000 */

#define FMC_BWTR4_CLKDIV_Pos       (20U)
#define FMC_BWTR4_CLKDIV_Msk       (0xFU << FMC_BWTR4_CLKDIV_Pos)              /*!< 0x00F00000 */
#define FMC_BWTR4_CLKDIV           FMC_BWTR4_CLKDIV_Msk                        /*!<CLKDIV[3:0] bits (Clock divide ratio) */
#define FMC_BWTR4_CLKDIV_0         (0x1U << FMC_BWTR4_CLKDIV_Pos)              /*!< 0x00100000 */
#define FMC_BWTR4_CLKDIV_1         (0x2U << FMC_BWTR4_CLKDIV_Pos)              /*!< 0x00200000 */
#define FMC_BWTR4_CLKDIV_2         (0x4U << FMC_BWTR4_CLKDIV_Pos)              /*!< 0x00400000 */
#define FMC_BWTR4_CLKDIV_3         (0x8U << FMC_BWTR4_CLKDIV_Pos)              /*!< 0x00800000 */

#define FMC_BWTR4_DATLAT_Pos       (24U)
#define FMC_BWTR4_DATLAT_Msk       (0xFU << FMC_BWTR4_DATLAT_Pos)              /*!< 0x0F000000 */
#define FMC_BWTR4_DATLAT           FMC_BWTR4_DATLAT_Msk                        /*!<DATLA[3:0] bits (Data latency) */
#define FMC_BWTR4_DATLAT_0         (0x1U << FMC_BWTR4_DATLAT_Pos)              /*!< 0x01000000 */
#define FMC_BWTR4_DATLAT_1         (0x2U << FMC_BWTR4_DATLAT_Pos)              /*!< 0x02000000 */
#define FMC_BWTR4_DATLAT_2         (0x4U << FMC_BWTR4_DATLAT_Pos)              /*!< 0x04000000 */
#define FMC_BWTR4_DATLAT_3         (0x8U << FMC_BWTR4_DATLAT_Pos)              /*!< 0x08000000 */

#define FMC_BWTR4_ACCMOD_Pos       (28U)
#define FMC_BWTR4_ACCMOD_Msk       (0x3U << FMC_BWTR4_ACCMOD_Pos)              /*!< 0x30000000 */
#define FMC_BWTR4_ACCMOD           FMC_BWTR4_ACCMOD_Msk                        /*!<ACCMOD[1:0] bits (Access mode) */
#define FMC_BWTR4_ACCMOD_0         (0x1U << FMC_BWTR4_ACCMOD_Pos)              /*!< 0x10000000 */
#define FMC_BWTR4_ACCMOD_1         (0x2U << FMC_BWTR4_ACCMOD_Pos)              /*!< 0x20000000 */

#define FMC_BWTR4_DATAHLD_Pos       (30U)
#define FMC_BWTR4_DATAHLD_Msk       (0x3U << FMC_BWTR4_DATAHLD_Pos)            /*!< 0xC0000000 */
#define FMC_BWTR4_DATAHLD           FMC_BWTR4_DATAHLD_Msk                      /*!<DATAHLD[1:0] bits (Data Hold phase duration) */
#define FMC_BWTR4_DATAHLD_0         (0x1U << FMC_BWTR4_DATAHLD_Pos)            /*!< 0x40000000 */
#define FMC_BWTR4_DATAHLD_1         (0x2U << FMC_BWTR4_DATAHLD_Pos)            /*!< 0x80000000 */

/******************  Bit definition for FMC_PCR register  *******************/
#define FMC_PCR_PWAITEN_Pos        (1U)
#define FMC_PCR_PWAITEN_Msk        (0x1U << FMC_PCR_PWAITEN_Pos)               /*!< 0x00000002 */
#define FMC_PCR_PWAITEN            FMC_PCR_PWAITEN_Msk                         /*!<Wait feature enable bit                   */
#define FMC_PCR_PBKEN_Pos          (2U)
#define FMC_PCR_PBKEN_Msk          (0x1U << FMC_PCR_PBKEN_Pos)                 /*!< 0x00000004 */
#define FMC_PCR_PBKEN              FMC_PCR_PBKEN_Msk                           /*!<NAND Flash memory bank enable bit         */

#define FMC_PCR_PWID_Pos           (4U)
#define FMC_PCR_PWID_Msk           (0x3U << FMC_PCR_PWID_Pos)                  /*!< 0x00000030 */
#define FMC_PCR_PWID               FMC_PCR_PWID_Msk                            /*!<PWID[1:0] bits (NAND Flash databus width) */
#define FMC_PCR_PWID_0             (0x1U << FMC_PCR_PWID_Pos)                  /*!< 0x00000010 */
#define FMC_PCR_PWID_1             (0x2U << FMC_PCR_PWID_Pos)                  /*!< 0x00000020 */

#define FMC_PCR_ECCEN_Pos          (6U)
#define FMC_PCR_ECCEN_Msk          (0x1U << FMC_PCR_ECCEN_Pos)                 /*!< 0x00000040 */
#define FMC_PCR_ECCEN              FMC_PCR_ECCEN_Msk                           /*!<ECC computation logic enable bit          */

#define FMC_PCR_ECCALG_Pos         (8U)
#define FMC_PCR_ECCALG_Msk         (0x1U << FMC_PCR_ECCALG_Pos)                /*!< 0x00000100 */
#define FMC_PCR_ECCALG             FMC_PCR_ECCEN_Msk                           /*!<ECC algorithm                             */

#define FMC_PCR_TCLR_Pos           (9U)
#define FMC_PCR_TCLR_Msk           (0xFU << FMC_PCR_TCLR_Pos)                  /*!< 0x00001E00 */
#define FMC_PCR_TCLR               FMC_PCR_TCLR_Msk                            /*!<TCLR[3:0] bits (CLE to RE delay)          */
#define FMC_PCR_TCLR_0             (0x1U << FMC_PCR_TCLR_Pos)                  /*!< 0x00000200 */
#define FMC_PCR_TCLR_1             (0x2U << FMC_PCR_TCLR_Pos)                  /*!< 0x00000400 */
#define FMC_PCR_TCLR_2             (0x4U << FMC_PCR_TCLR_Pos)                  /*!< 0x00000800 */
#define FMC_PCR_TCLR_3             (0x8U << FMC_PCR_TCLR_Pos)                  /*!< 0x00001000 */

#define FMC_PCR_TAR_Pos            (13U)
#define FMC_PCR_TAR_Msk            (0xFU << FMC_PCR_TAR_Pos)                   /*!< 0x0001E000 */
#define FMC_PCR_TAR                FMC_PCR_TAR_Msk                             /*!<TAR[3:0] bits (ALE to RE delay)           */
#define FMC_PCR_TAR_0              (0x1U << FMC_PCR_TAR_Pos)                   /*!< 0x00002000 */
#define FMC_PCR_TAR_1              (0x2U << FMC_PCR_TAR_Pos)                   /*!< 0x00004000 */
#define FMC_PCR_TAR_2              (0x4U << FMC_PCR_TAR_Pos)                   /*!< 0x00008000 */
#define FMC_PCR_TAR_3              (0x8U << FMC_PCR_TAR_Pos)                   /*!< 0x00010000 */

#define FMC_PCR_ECCSS_Pos          (17U)
#define FMC_PCR_ECCSS_Msk          (0x7U << FMC_PCR_ECCSS_Pos)                 /*!< 0x000E0000 */
#define FMC_PCR_ECCSS              FMC_PCR_ECCSS_Msk                           /*!<ECCSS[1:0] bits (ECC sector size)         */
#define FMC_PCR_ECCSS_0            (0x1U << FMC_PCR_ECCSS_Pos)                 /*!< 0x00020000 */
#define FMC_PCR_ECCSS_1            (0x2U << FMC_PCR_ECCSS_Pos)                 /*!< 0x00040000 */
#define FMC_PCR_ECCSS_2            (0x4U << FMC_PCR_ECCSS_Pos)                 /*!< 0x00080000 */

#define FMC_PCR_TCEH_Pos          (20U)
#define FMC_PCR_TCEH_Msk          (0xFU << FMC_PCR_TCEH_Pos)                   /*!< 0x00F00000 */
#define FMC_PCR_TCEH              FMC_PCR_TCEH_Msk                             /*!<TCEH[3:0] bits (Chip select high timing)  */

#define FMC_PCR_BCHECC_Pos        (24U)
#define FMC_PCR_BCHECC_Msk        (0x1U << FMC_PCR_BCHECC_Pos)                 /*!< 0x01000000 */
#define FMC_PCR_BCHECC            FMC_PCR_BCHECC_Msk                           /*!<BCHECC bit (BCH error correction capability) */

#define FMC_PCR_WEN_Pos           (25U)
#define FMC_PCR_WEN_Msk           (0x1U << FMC_PCR_WEN_Pos)                    /*!< 0x02000000 */
#define FMC_PCR_WEN               FMC_PCR_WEN_Msk                              /*!<WEN bit (Write enable)                    */

/*******************  Bit definition for FMC_SR register  *******************/
#define FMC_SR_ISOST_Pos          (0U)
#define FMC_SR_ISOST_Msk          (0x3U << FMC_SR_ISOST_Pos)                   /*!< 0x00000003 */
#define FMC_SR_ISOST              FMC_SR_ISOST_Msk                             /*!<ISOST[1:0] bits (FMC isolation state with respect to the AXI interface) */

#define FMC_SR_PEF_Pos            (4U)
#define FMC_SR_PEF_Msk            (0x1U << FMC_SR_PEF_Pos)                     /*!< 0x00000010 */
#define FMC_SR_PEF                FMC_SR_PEF_Msk                               /*!<Pipe Empty Flag                           */

#define FMC_SR_NWRF_Pos           (6U)
#define FMC_SR_NWRF_Msk           (0x1U << FMC_SR_NWRF_Pos)                     /*!< 0x00000040 */
#define FMC_SR_NWRF               FMC_SR_NWRF_Msk                               /*!<NAND write request flag                  */


/******************  Bit definition for FMC_PMEM register  ******************/
#define FMC_PMEM_MEMSET3_Pos       (0U)
#define FMC_PMEM_MEMSET3_Msk       (0xFFU << FMC_PMEM_MEMSET3_Pos)             /*!< 0x000000FF */
#define FMC_PMEM_MEMSET3           FMC_PMEM_MEMSET3_Msk                        /*!<MEMSET2[7:0] bits (Common memory 2 setup time) */
#define FMC_PMEM_MEMSET3_0         (0x01U << FMC_PMEM_MEMSET3_Pos)             /*!< 0x00000001 */
#define FMC_PMEM_MEMSET3_1         (0x02U << FMC_PMEM_MEMSET3_Pos)             /*!< 0x00000002 */
#define FMC_PMEM_MEMSET3_2         (0x04U << FMC_PMEM_MEMSET3_Pos)             /*!< 0x00000004 */
#define FMC_PMEM_MEMSET3_3         (0x08U << FMC_PMEM_MEMSET3_Pos)             /*!< 0x00000008 */
#define FMC_PMEM_MEMSET3_4         (0x10U << FMC_PMEM_MEMSET3_Pos)             /*!< 0x00000010 */
#define FMC_PMEM_MEMSET3_5         (0x20U << FMC_PMEM_MEMSET3_Pos)             /*!< 0x00000020 */
#define FMC_PMEM_MEMSET3_6         (0x40U << FMC_PMEM_MEMSET3_Pos)             /*!< 0x00000040 */
#define FMC_PMEM_MEMSET3_7         (0x80U << FMC_PMEM_MEMSET3_Pos)             /*!< 0x00000080 */

#define FMC_PMEM_MEMWAIT3_Pos      (8U)
#define FMC_PMEM_MEMWAIT3_Msk      (0xFFU << FMC_PMEM_MEMWAIT3_Pos)            /*!< 0x0000FF00 */
#define FMC_PMEM_MEMWAIT3          FMC_PMEM_MEMWAIT3_Msk                       /*!<MEMWAIT2[7:0] bits (Common memory 2 wait time) */
#define FMC_PMEM_MEMWAIT3_0        (0x01U << FMC_PMEM_MEMWAIT3_Pos)            /*!< 0x00000100 */
#define FMC_PMEM_MEMWAIT3_1        (0x02U << FMC_PMEM_MEMWAIT3_Pos)            /*!< 0x00000200 */
#define FMC_PMEM_MEMWAIT3_2        (0x04U << FMC_PMEM_MEMWAIT3_Pos)            /*!< 0x00000400 */
#define FMC_PMEM_MEMWAIT3_3        (0x08U << FMC_PMEM_MEMWAIT3_Pos)            /*!< 0x00000800 */
#define FMC_PMEM_MEMWAIT3_4        (0x10U << FMC_PMEM_MEMWAIT3_Pos)            /*!< 0x00001000 */
#define FMC_PMEM_MEMWAIT3_5        (0x20U << FMC_PMEM_MEMWAIT3_Pos)            /*!< 0x00002000 */
#define FMC_PMEM_MEMWAIT3_6        (0x40U << FMC_PMEM_MEMWAIT3_Pos)            /*!< 0x00004000 */
#define FMC_PMEM_MEMWAIT3_7        (0x80U << FMC_PMEM_MEMWAIT3_Pos)            /*!< 0x00008000 */

#define FMC_PMEM_MEMHOLD3_Pos      (16U)
#define FMC_PMEM_MEMHOLD3_Msk      (0xFFU << FMC_PMEM_MEMHOLD3_Pos)            /*!< 0x00FF0000 */
#define FMC_PMEM_MEMHOLD3          FMC_PMEM_MEMHOLD3_Msk                       /*!<MEMHOLD2[7:0] bits (Common memory 2 hold time) */
#define FMC_PMEM_MEMHOLD3_0        (0x01U << FMC_PMEM_MEMHOLD3_Pos)            /*!< 0x00010000 */
#define FMC_PMEM_MEMHOLD3_1        (0x02U << FMC_PMEM_MEMHOLD3_Pos)            /*!< 0x00020000 */
#define FMC_PMEM_MEMHOLD3_2        (0x04U << FMC_PMEM_MEMHOLD3_Pos)            /*!< 0x00040000 */
#define FMC_PMEM_MEMHOLD3_3        (0x08U << FMC_PMEM_MEMHOLD3_Pos)            /*!< 0x00080000 */
#define FMC_PMEM_MEMHOLD3_4        (0x10U << FMC_PMEM_MEMHOLD3_Pos)            /*!< 0x00100000 */
#define FMC_PMEM_MEMHOLD3_5        (0x20U << FMC_PMEM_MEMHOLD3_Pos)            /*!< 0x00200000 */
#define FMC_PMEM_MEMHOLD3_6        (0x40U << FMC_PMEM_MEMHOLD3_Pos)            /*!< 0x00400000 */
#define FMC_PMEM_MEMHOLD3_7        (0x80U << FMC_PMEM_MEMHOLD3_Pos)            /*!< 0x00800000 */

#define FMC_PMEM_MEMHIZ3_Pos       (24U)
#define FMC_PMEM_MEMHIZ3_Msk       (0xFFU << FMC_PMEM_MEMHIZ3_Pos)             /*!< 0xFF000000 */
#define FMC_PMEM_MEMHIZ3           FMC_PMEM_MEMHIZ3_Msk                        /*!<MEMHIZ2[7:0] bits (Common memory 2 databus HiZ time) */
#define FMC_PMEM_MEMHIZ3_0         (0x01U << FMC_PMEM_MEMHIZ3_Pos)             /*!< 0x01000000 */
#define FMC_PMEM_MEMHIZ3_1         (0x02U << FMC_PMEM_MEMHIZ3_Pos)             /*!< 0x02000000 */
#define FMC_PMEM_MEMHIZ3_2         (0x04U << FMC_PMEM_MEMHIZ3_Pos)             /*!< 0x04000000 */
#define FMC_PMEM_MEMHIZ3_3         (0x08U << FMC_PMEM_MEMHIZ3_Pos)             /*!< 0x08000000 */
#define FMC_PMEM_MEMHIZ3_4         (0x10U << FMC_PMEM_MEMHIZ3_Pos)             /*!< 0x10000000 */
#define FMC_PMEM_MEMHIZ3_5         (0x20U << FMC_PMEM_MEMHIZ3_Pos)             /*!< 0x20000000 */
#define FMC_PMEM_MEMHIZ3_6         (0x40U << FMC_PMEM_MEMHIZ3_Pos)             /*!< 0x40000000 */
#define FMC_PMEM_MEMHIZ3_7         (0x80U << FMC_PMEM_MEMHIZ3_Pos)             /*!< 0x80000000 */

/******************  Bit definition for FMC_PATT register  ******************/
#define FMC_PATT_ATTSET3_Pos       (0U)
#define FMC_PATT_ATTSET3_Msk       (0xFFU << FMC_PATT_ATTSET3_Pos)             /*!< 0x000000FF */
#define FMC_PATT_ATTSET3           FMC_PATT_ATTSET3_Msk                        /*!<ATTSET2[7:0] bits (Attribute memory 2 setup time) */
#define FMC_PATT_ATTSET3_0         (0x01U << FMC_PATT_ATTSET3_Pos)             /*!< 0x00000001 */
#define FMC_PATT_ATTSET3_1         (0x02U << FMC_PATT_ATTSET3_Pos)             /*!< 0x00000002 */
#define FMC_PATT_ATTSET3_2         (0x04U << FMC_PATT_ATTSET3_Pos)             /*!< 0x00000004 */
#define FMC_PATT_ATTSET3_3         (0x08U << FMC_PATT_ATTSET3_Pos)             /*!< 0x00000008 */
#define FMC_PATT_ATTSET3_4         (0x10U << FMC_PATT_ATTSET3_Pos)             /*!< 0x00000010 */
#define FMC_PATT_ATTSET3_5         (0x20U << FMC_PATT_ATTSET3_Pos)             /*!< 0x00000020 */
#define FMC_PATT_ATTSET3_6         (0x40U << FMC_PATT_ATTSET3_Pos)             /*!< 0x00000040 */
#define FMC_PATT_ATTSET3_7         (0x80U << FMC_PATT_ATTSET3_Pos)             /*!< 0x00000080 */

#define FMC_PATT_ATTWAIT3_Pos      (8U)
#define FMC_PATT_ATTWAIT3_Msk      (0xFFU << FMC_PATT_ATTWAIT3_Pos)            /*!< 0x0000FF00 */
#define FMC_PATT_ATTWAIT3          FMC_PATT_ATTWAIT3_Msk                       /*!<ATTWAIT2[7:0] bits (Attribute memory 2 wait time) */
#define FMC_PATT_ATTWAIT3_0        (0x01U << FMC_PATT_ATTWAIT3_Pos)            /*!< 0x00000100 */
#define FMC_PATT_ATTWAIT3_1        (0x02U << FMC_PATT_ATTWAIT3_Pos)            /*!< 0x00000200 */
#define FMC_PATT_ATTWAIT3_2        (0x04U << FMC_PATT_ATTWAIT3_Pos)            /*!< 0x00000400 */
#define FMC_PATT_ATTWAIT3_3        (0x08U << FMC_PATT_ATTWAIT3_Pos)            /*!< 0x00000800 */
#define FMC_PATT_ATTWAIT3_4        (0x10U << FMC_PATT_ATTWAIT3_Pos)            /*!< 0x00001000 */
#define FMC_PATT_ATTWAIT3_5        (0x20U << FMC_PATT_ATTWAIT3_Pos)            /*!< 0x00002000 */
#define FMC_PATT_ATTWAIT3_6        (0x40U << FMC_PATT_ATTWAIT3_Pos)            /*!< 0x00004000 */
#define FMC_PATT_ATTWAIT3_7        (0x80U << FMC_PATT_ATTWAIT3_Pos)            /*!< 0x00008000 */

#define FMC_PATT_ATTHOLD3_Pos      (16U)
#define FMC_PATT_ATTHOLD3_Msk      (0xFFU << FMC_PATT_ATTHOLD3_Pos)            /*!< 0x00FF0000 */
#define FMC_PATT_ATTHOLD3          FMC_PATT_ATTHOLD3_Msk                       /*!<ATTHOLD2[7:0] bits (Attribute memory 2 hold time) */
#define FMC_PATT_ATTHOLD3_0        (0x01U << FMC_PATT_ATTHOLD3_Pos)            /*!< 0x00010000 */
#define FMC_PATT_ATTHOLD3_1        (0x02U << FMC_PATT_ATTHOLD3_Pos)            /*!< 0x00020000 */
#define FMC_PATT_ATTHOLD3_2        (0x04U << FMC_PATT_ATTHOLD3_Pos)            /*!< 0x00040000 */
#define FMC_PATT_ATTHOLD3_3        (0x08U << FMC_PATT_ATTHOLD3_Pos)            /*!< 0x00080000 */
#define FMC_PATT_ATTHOLD3_4        (0x10U << FMC_PATT_ATTHOLD3_Pos)            /*!< 0x00100000 */
#define FMC_PATT_ATTHOLD3_5        (0x20U << FMC_PATT_ATTHOLD3_Pos)            /*!< 0x00200000 */
#define FMC_PATT_ATTHOLD3_6        (0x40U << FMC_PATT_ATTHOLD3_Pos)            /*!< 0x00400000 */
#define FMC_PATT_ATTHOLD3_7        (0x80U << FMC_PATT_ATTHOLD3_Pos)            /*!< 0x00800000 */

#define FMC_PATT_ATTHIZ3_Pos       (24U)
#define FMC_PATT_ATTHIZ3_Msk       (0xFFU << FMC_PATT_ATTHIZ3_Pos)             /*!< 0xFF000000 */
#define FMC_PATT_ATTHIZ3           FMC_PATT_ATTHIZ3_Msk                        /*!<ATTHIZ2[7:0] bits (Attribute memory 2 databus HiZ time) */
#define FMC_PATT_ATTHIZ3_0         (0x01U << FMC_PATT_ATTHIZ3_Pos)             /*!< 0x01000000 */
#define FMC_PATT_ATTHIZ3_1         (0x02U << FMC_PATT_ATTHIZ3_Pos)             /*!< 0x02000000 */
#define FMC_PATT_ATTHIZ3_2         (0x04U << FMC_PATT_ATTHIZ3_Pos)             /*!< 0x04000000 */
#define FMC_PATT_ATTHIZ3_3         (0x08U << FMC_PATT_ATTHIZ3_Pos)             /*!< 0x08000000 */
#define FMC_PATT_ATTHIZ3_4         (0x10U << FMC_PATT_ATTHIZ3_Pos)             /*!< 0x10000000 */
#define FMC_PATT_ATTHIZ3_5         (0x20U << FMC_PATT_ATTHIZ3_Pos)             /*!< 0x20000000 */
#define FMC_PATT_ATTHIZ3_6         (0x40U << FMC_PATT_ATTHIZ3_Pos)             /*!< 0x40000000 */
#define FMC_PATT_ATTHIZ3_7         (0x80U << FMC_PATT_ATTHIZ3_Pos)             /*!< 0x80000000 */

/******************  Bit definition for FMC_PIO4 register  *******************/
#define FMC_PIO4_IOSET4_Pos        (0U)
#define FMC_PIO4_IOSET4_Msk        (0xFFU << FMC_PIO4_IOSET4_Pos)              /*!< 0x000000FF */
#define FMC_PIO4_IOSET4            FMC_PIO4_IOSET4_Msk                         /*!<IOSET4[7:0] bits (I/O 4 setup time) */
#define FMC_PIO4_IOSET4_0          (0x01U << FMC_PIO4_IOSET4_Pos)              /*!< 0x00000001 */
#define FMC_PIO4_IOSET4_1          (0x02U << FMC_PIO4_IOSET4_Pos)              /*!< 0x00000002 */
#define FMC_PIO4_IOSET4_2          (0x04U << FMC_PIO4_IOSET4_Pos)              /*!< 0x00000004 */
#define FMC_PIO4_IOSET4_3          (0x08U << FMC_PIO4_IOSET4_Pos)              /*!< 0x00000008 */
#define FMC_PIO4_IOSET4_4          (0x10U << FMC_PIO4_IOSET4_Pos)              /*!< 0x00000010 */
#define FMC_PIO4_IOSET4_5          (0x20U << FMC_PIO4_IOSET4_Pos)              /*!< 0x00000020 */
#define FMC_PIO4_IOSET4_6          (0x40U << FMC_PIO4_IOSET4_Pos)              /*!< 0x00000040 */
#define FMC_PIO4_IOSET4_7          (0x80U << FMC_PIO4_IOSET4_Pos)              /*!< 0x00000080 */

#define FMC_PIO4_IOWAIT4_Pos       (8U)
#define FMC_PIO4_IOWAIT4_Msk       (0xFFU << FMC_PIO4_IOWAIT4_Pos)             /*!< 0x0000FF00 */
#define FMC_PIO4_IOWAIT4           FMC_PIO4_IOWAIT4_Msk                        /*!<IOWAIT4[7:0] bits (I/O 4 wait time) */
#define FMC_PIO4_IOWAIT4_0         (0x01U << FMC_PIO4_IOWAIT4_Pos)             /*!< 0x00000100 */
#define FMC_PIO4_IOWAIT4_1         (0x02U << FMC_PIO4_IOWAIT4_Pos)             /*!< 0x00000200 */
#define FMC_PIO4_IOWAIT4_2         (0x04U << FMC_PIO4_IOWAIT4_Pos)             /*!< 0x00000400 */
#define FMC_PIO4_IOWAIT4_3         (0x08U << FMC_PIO4_IOWAIT4_Pos)             /*!< 0x00000800 */
#define FMC_PIO4_IOWAIT4_4         (0x10U << FMC_PIO4_IOWAIT4_Pos)             /*!< 0x00001000 */
#define FMC_PIO4_IOWAIT4_5         (0x20U << FMC_PIO4_IOWAIT4_Pos)             /*!< 0x00002000 */
#define FMC_PIO4_IOWAIT4_6         (0x40U << FMC_PIO4_IOWAIT4_Pos)             /*!< 0x00004000 */
#define FMC_PIO4_IOWAIT4_7         (0x80U << FMC_PIO4_IOWAIT4_Pos)             /*!< 0x00008000 */

#define FMC_PIO4_IOHOLD4_Pos       (16U)
#define FMC_PIO4_IOHOLD4_Msk       (0xFFU << FMC_PIO4_IOHOLD4_Pos)             /*!< 0x00FF0000 */
#define FMC_PIO4_IOHOLD4           FMC_PIO4_IOHOLD4_Msk                        /*!<IOHOLD4[7:0] bits (I/O 4 hold time) */
#define FMC_PIO4_IOHOLD4_0         (0x01U << FMC_PIO4_IOHOLD4_Pos)             /*!< 0x00010000 */
#define FMC_PIO4_IOHOLD4_1         (0x02U << FMC_PIO4_IOHOLD4_Pos)             /*!< 0x00020000 */
#define FMC_PIO4_IOHOLD4_2         (0x04U << FMC_PIO4_IOHOLD4_Pos)             /*!< 0x00040000 */
#define FMC_PIO4_IOHOLD4_3         (0x08U << FMC_PIO4_IOHOLD4_Pos)             /*!< 0x00080000 */
#define FMC_PIO4_IOHOLD4_4         (0x10U << FMC_PIO4_IOHOLD4_Pos)             /*!< 0x00100000 */
#define FMC_PIO4_IOHOLD4_5         (0x20U << FMC_PIO4_IOHOLD4_Pos)             /*!< 0x00200000 */
#define FMC_PIO4_IOHOLD4_6         (0x40U << FMC_PIO4_IOHOLD4_Pos)             /*!< 0x00400000 */
#define FMC_PIO4_IOHOLD4_7         (0x80U << FMC_PIO4_IOHOLD4_Pos)             /*!< 0x00800000 */

#define FMC_PIO4_IOHIZ4_Pos        (24U)
#define FMC_PIO4_IOHIZ4_Msk        (0xFFU << FMC_PIO4_IOHIZ4_Pos)              /*!< 0xFF000000 */
#define FMC_PIO4_IOHIZ4            FMC_PIO4_IOHIZ4_Msk                         /*!<IOHIZ4[7:0] bits (I/O 4 databus HiZ time) */
#define FMC_PIO4_IOHIZ4_0          (0x01U << FMC_PIO4_IOHIZ4_Pos)              /*!< 0x01000000 */
#define FMC_PIO4_IOHIZ4_1          (0x02U << FMC_PIO4_IOHIZ4_Pos)              /*!< 0x02000000 */
#define FMC_PIO4_IOHIZ4_2          (0x04U << FMC_PIO4_IOHIZ4_Pos)              /*!< 0x04000000 */
#define FMC_PIO4_IOHIZ4_3          (0x08U << FMC_PIO4_IOHIZ4_Pos)              /*!< 0x08000000 */
#define FMC_PIO4_IOHIZ4_4          (0x10U << FMC_PIO4_IOHIZ4_Pos)              /*!< 0x10000000 */
#define FMC_PIO4_IOHIZ4_5          (0x20U << FMC_PIO4_IOHIZ4_Pos)              /*!< 0x20000000 */
#define FMC_PIO4_IOHIZ4_6          (0x40U << FMC_PIO4_IOHIZ4_Pos)              /*!< 0x40000000 */
#define FMC_PIO4_IOHIZ4_7          (0x80U << FMC_PIO4_IOHIZ4_Pos)              /*!< 0x80000000 */

/**********************  Bit definition for FMC_VERR register  *****************/
#define FMC_VERR_MINREV_Pos      (0U)
#define FMC_VERR_MINREV_Msk      (0xFU << FMC_VERR_MINREV_Pos)               /*!< 0x0000000F */
#define FMC_VERR_MINREV          FMC_VERR_MINREV_Msk                         /*!< Minor Revision number */
#define FMC_VERR_MAJREV_Pos      (4U)
#define FMC_VERR_MAJREV_Msk      (0xFU << FMC_VERR_MAJREV_Pos)               /*!< 0x000000F0 */
#define FMC_VERR_MAJREV          FMC_VERR_MAJREV_Msk                         /*!< Major Revision number */

/**********************  Bit definition for FMC_IPIDR register  ****************/
#define FMC_IPIDR_IPID_Pos       (0U)
#define FMC_IPIDR_IPID_Msk       (0xFFFFFFFFU << FMC_IPIDR_IPID_Pos)         /*!< 0xFFFFFFFF */
#define FMC_IPIDR_IPID           FMC_IPIDR_IPID_Msk                          /*!< IP Identification */

/**********************  Bit definition for FMC_SIDR register  *****************/
#define FMC_SIDR_SID_Pos         (0U)
#define FMC_SIDR_SID_Msk         (0xFFFFFFFFU << FMC_SIDR_SID_Pos)           /*!< 0xFFFFFFFF */
#define FMC_SIDR_SID             FMC_SIDR_SID_Msk                            /*!< IP size identification */
