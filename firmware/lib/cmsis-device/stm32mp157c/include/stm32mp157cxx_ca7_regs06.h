
/******************************************************************************/
/*                                                                            */
/*                         Reset and Clock Control                            */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for RCC_TZCR register********************/
#define RCC_TZCR_TZEN_Pos                         (0U)
#define RCC_TZCR_TZEN_Msk                         (0x1U << RCC_TZCR_TZEN_Pos)                        /*!< 0x00000001 */
#define RCC_TZCR_TZEN                             RCC_TZCR_TZEN_Msk                                  /*!< RCC TrustZone (secure) Enable */
#define RCC_TZCR_MCKPROT_Pos                      (1U)
#define RCC_TZCR_MCKPROT_Msk                      (0x1U << RCC_TZCR_MCKPROT_Pos)                     /*!< 0x00000002 */
#define RCC_TZCR_MCKPROT                          RCC_TZCR_MCKPROT_Msk                               /*!< Protection of the generation of mcuss_ck clock (secure) Enable */

/*****************  Bit definition for RCC_OCENSETR register  *****************/
#define RCC_OCENSETR_HSION_Pos                    (0U)
#define RCC_OCENSETR_HSION_Msk                    (0x1U << RCC_OCENSETR_HSION_Pos)                   /*!< 0x00000001 */
#define RCC_OCENSETR_HSION                        RCC_OCENSETR_HSION_Msk                             /*!< Set HSION bit */
#define RCC_OCENSETR_HSIKERON_Pos                 (1U)
#define RCC_OCENSETR_HSIKERON_Msk                 (0x1U << RCC_OCENSETR_HSIKERON_Pos)                /*!< 0x00000002 */
#define RCC_OCENSETR_HSIKERON                     RCC_OCENSETR_HSIKERON_Msk                          /*!< Set HSIKERON bit */
#define RCC_OCENSETR_CSION_Pos                    (4U)
#define RCC_OCENSETR_CSION_Msk                    (0x1U << RCC_OCENSETR_CSION_Pos)                   /*!< 0x00000010 */
#define RCC_OCENSETR_CSION                        RCC_OCENSETR_CSION_Msk                             /*!< Set CSION bit */
#define RCC_OCENSETR_CSIKERON_Pos                 (5U)
#define RCC_OCENSETR_CSIKERON_Msk                 (0x1U << RCC_OCENSETR_CSIKERON_Pos)                /*!< 0x00000020 */
#define RCC_OCENSETR_CSIKERON                     RCC_OCENSETR_CSIKERON_Msk                          /*!< Set CSIKERON bit */
#define RCC_OCENSETR_DIGBYP_Pos                   (7U)
#define RCC_OCENSETR_DIGBYP_Msk                   (0x1U << RCC_OCENSETR_DIGBYP_Pos)                  /*!< 0x00000080 */
#define RCC_OCENSETR_DIGBYP                       RCC_OCENSETR_DIGBYP_Msk                            /*!< Set DIGBYP bit */
#define RCC_OCENSETR_HSEON_Pos                    (8U)
#define RCC_OCENSETR_HSEON_Msk                    (0x1U << RCC_OCENSETR_HSEON_Pos)                   /*!< 0x00000100 */
#define RCC_OCENSETR_HSEON                        RCC_OCENSETR_HSEON_Msk                             /*!< Set HSEON bit */
#define RCC_OCENSETR_HSEKERON_Pos                 (9U)
#define RCC_OCENSETR_HSEKERON_Msk                 (0x1U << RCC_OCENSETR_HSEKERON_Pos)                /*!< 0x00000200 */
#define RCC_OCENSETR_HSEKERON                     RCC_OCENSETR_HSEKERON_Msk                          /*!< Set HSEKERON bit */
#define RCC_OCENSETR_HSEBYP_Pos                   (10U)
#define RCC_OCENSETR_HSEBYP_Msk                   (0x1U << RCC_OCENSETR_HSEBYP_Pos)                  /*!< 0x00000400 */
#define RCC_OCENSETR_HSEBYP                       RCC_OCENSETR_HSEBYP_Msk                            /*!< Set HSEBYP bit */
#define RCC_OCENSETR_HSECSSON_Pos                 (11U)
#define RCC_OCENSETR_HSECSSON_Msk                 (0x1U << RCC_OCENSETR_HSECSSON_Pos)                /*!< 0x00000800 */
#define RCC_OCENSETR_HSECSSON                     RCC_OCENSETR_HSECSSON_Msk                          /*!< Set the HSECSSON bit */

/*****************  Bit definition for RCC_OCENCLRR register  *****************/
#define RCC_OCENCLRR_HSION_Pos                    (0U)
#define RCC_OCENCLRR_HSION_Msk                    (0x1U << RCC_OCENCLRR_HSION_Pos)                   /*!< 0x00000001 */
#define RCC_OCENCLRR_HSION                        RCC_OCENCLRR_HSION_Msk                             /*!< Clear of HSION bit */
#define RCC_OCENCLRR_HSIKERON_Pos                 (1U)
#define RCC_OCENCLRR_HSIKERON_Msk                 (0x1U << RCC_OCENCLRR_HSIKERON_Pos)                /*!< 0x00000002 */
#define RCC_OCENCLRR_HSIKERON                     RCC_OCENCLRR_HSIKERON_Msk                          /*!< Clear of HSIKERON bit */
#define RCC_OCENCLRR_CSION_Pos                    (4U)
#define RCC_OCENCLRR_CSION_Msk                    (0x1U << RCC_OCENCLRR_CSION_Pos)                   /*!< 0x00000010 */
#define RCC_OCENCLRR_CSION                        RCC_OCENCLRR_CSION_Msk                             /*!< Clear of CSION bit */
#define RCC_OCENCLRR_CSIKERON_Pos                 (5U)
#define RCC_OCENCLRR_CSIKERON_Msk                 (0x1U << RCC_OCENCLRR_CSIKERON_Pos)                /*!< 0x00000020 */
#define RCC_OCENCLRR_CSIKERON                     RCC_OCENCLRR_CSIKERON_Msk                          /*!< Clear of CSIKERON bit */
#define RCC_OCENCLRR_DIGBYP_Pos                   (7U)
#define RCC_OCENCLRR_DIGBYP_Msk                   (0x1U << RCC_OCENCLRR_DIGBYP_Pos)                  /*!< 0x00000080 */
#define RCC_OCENCLRR_DIGBYP                       RCC_OCENCLRR_DIGBYP_Msk                            /*!< Clear of DIGBYP bit */
#define RCC_OCENCLRR_HSEON_Pos                    (8U)
#define RCC_OCENCLRR_HSEON_Msk                    (0x1U << RCC_OCENCLRR_HSEON_Pos)                   /*!< 0x00000100 */
#define RCC_OCENCLRR_HSEON                        RCC_OCENCLRR_HSEON_Msk                             /*!< Clear of HSEON bit */
#define RCC_OCENCLRR_HSEKERON_Pos                 (9U)
#define RCC_OCENCLRR_HSEKERON_Msk                 (0x1U << RCC_OCENCLRR_HSEKERON_Pos)                /*!< 0x00000200 */
#define RCC_OCENCLRR_HSEKERON                     RCC_OCENCLRR_HSEKERON_Msk                          /*!< Clear HSEKERON bit */
#define RCC_OCENCLRR_HSEBYP_Pos                   (10U)
#define RCC_OCENCLRR_HSEBYP_Msk                   (0x1U << RCC_OCENCLRR_HSEBYP_Pos)                  /*!< 0x00000400 */
#define RCC_OCENCLRR_HSEBYP                       RCC_OCENCLRR_HSEBYP_Msk                            /*!< Clear the HSEBYP bit */

/*****************  Bit definition for RCC_HSICFGR register  ******************/
#define RCC_HSICFGR_HSIDIV_Pos                    (0U)
#define RCC_HSICFGR_HSIDIV_Msk                    (0x3U << RCC_HSICFGR_HSIDIV_Pos)                   /*!< 0x00000003 */
#define RCC_HSICFGR_HSIDIV                        RCC_HSICFGR_HSIDIV_Msk                             /*!< HSI clock divider */
#define RCC_HSICFGR_HSIDIV_0                      (0x1U << RCC_HSICFGR_HSIDIV_Pos)                   /*!< 0x00000001 */
#define RCC_HSICFGR_HSIDIV_1                      (0x2U << RCC_HSICFGR_HSIDIV_Pos)                   /*!< 0x00000002 */
#define RCC_HSICFGR_HSITRIM_Pos                   (8U)
#define RCC_HSICFGR_HSITRIM_Msk                   (0x7FU << RCC_HSICFGR_HSITRIM_Pos)                 /*!< 0x00007F00 */
#define RCC_HSICFGR_HSITRIM                       RCC_HSICFGR_HSITRIM_Msk                            /*!< HSI clock trimming */
#define RCC_HSICFGR_HSITRIM_0                     (0x1U << RCC_HSICFGR_HSITRIM_Pos)                /*!< 0x00000100 */
#define RCC_HSICFGR_HSITRIM_1                     (0x2U << RCC_HSICFGR_HSITRIM_Pos)                /*!< 0x00000200 */
#define RCC_HSICFGR_HSITRIM_2                     (0x4U << RCC_HSICFGR_HSITRIM_Pos)                /*!< 0x00000400 */
#define RCC_HSICFGR_HSITRIM_3                     (0x8U << RCC_HSICFGR_HSITRIM_Pos)                /*!< 0x00000800 */
#define RCC_HSICFGR_HSITRIM_4                     (0x10U << RCC_HSICFGR_HSITRIM_Pos)               /*!< 0x00001000 */
#define RCC_HSICFGR_HSITRIM_5                     (0x20U << RCC_HSICFGR_HSITRIM_Pos)               /*!< 0x00002000 */
#define RCC_HSICFGR_HSITRIM_6                     (0x40U << RCC_HSICFGR_HSITRIM_Pos)               /*!< 0x00004000 */
#define RCC_HSICFGR_HSICAL_Pos                    (16U)
#define RCC_HSICFGR_HSICAL_Msk                    (0xFFFU << RCC_HSICFGR_HSICAL_Pos)                 /*!< 0x0FFF0000 */
#define RCC_HSICFGR_HSICAL                        RCC_HSICFGR_HSICAL_Msk                             /*!< HSI clock calibration */
#define RCC_HSICFGR_HSICAL_0                      (0x1U << RCC_HSICFGR_HSICAL_Pos)               /*!< 0x00010000 */
#define RCC_HSICFGR_HSICAL_1                      (0x2U << RCC_HSICFGR_HSICAL_Pos)               /*!< 0x00020000 */
#define RCC_HSICFGR_HSICAL_2                      (0x4U << RCC_HSICFGR_HSICAL_Pos)               /*!< 0x00040000 */
#define RCC_HSICFGR_HSICAL_3                      (0x8U << RCC_HSICFGR_HSICAL_Pos)               /*!< 0x00080000 */
#define RCC_HSICFGR_HSICAL_4                      (0x10U << RCC_HSICFGR_HSICAL_Pos)              /*!< 0x00100000 */
#define RCC_HSICFGR_HSICAL_5                      (0x20U << RCC_HSICFGR_HSICAL_Pos)              /*!< 0x00200000 */
#define RCC_HSICFGR_HSICAL_6                      (0x40U << RCC_HSICFGR_HSICAL_Pos)              /*!< 0x00400000 */
#define RCC_HSICFGR_HSICAL_7                      (0x80U << RCC_HSICFGR_HSICAL_Pos)              /*!< 0x00800000 */
#define RCC_HSICFGR_HSICAL_8                      (0x100U << RCC_HSICFGR_HSICAL_Pos)             /*!< 0x01000000 */
#define RCC_HSICFGR_HSICAL_9                      (0x200U << RCC_HSICFGR_HSICAL_Pos)             /*!< 0x02000000 */
#define RCC_HSICFGR_HSICAL_10                     (0x400U << RCC_HSICFGR_HSICAL_Pos)             /*!< 0x04000000 */
#define RCC_HSICFGR_HSICAL_11                     (0x800U << RCC_HSICFGR_HSICAL_Pos)             /*!< 0x08000000 */

/*****************  Bit definition for RCC_CSICFGR register  ******************/
#define RCC_CSICFGR_CSITRIM_Pos                   (8U)
#define RCC_CSICFGR_CSITRIM_Msk                   (0x1FU << RCC_CSICFGR_CSITRIM_Pos)                 /*!< 0x00001F00 */
#define RCC_CSICFGR_CSITRIM                       RCC_CSICFGR_CSITRIM_Msk                            /*!< CSI clock trimming */
#define RCC_CSICFGR_CSITRIM_0                     (0x1U << RCC_CSICFGR_CSITRIM_Pos)                /*!< 0x00000100 */
#define RCC_CSICFGR_CSITRIM_1                     (0x2U << RCC_CSICFGR_CSITRIM_Pos)                /*!< 0x00000200 */
#define RCC_CSICFGR_CSITRIM_2                     (0x4U << RCC_CSICFGR_CSITRIM_Pos)                /*!< 0x00000400 */
#define RCC_CSICFGR_CSITRIM_3                     (0x8U << RCC_CSICFGR_CSITRIM_Pos)                /*!< 0x00000800 */
#define RCC_CSICFGR_CSITRIM_4                     (0x10U << RCC_CSICFGR_CSITRIM_Pos)               /*!< 0x00001000 */
#define RCC_CSICFGR_CSICAL_Pos                    (16U)
#define RCC_CSICFGR_CSICAL_Msk                    (0xFFU << RCC_CSICFGR_CSICAL_Pos)                  /*!< 0x00FF0000 */
#define RCC_CSICFGR_CSICAL                        RCC_CSICFGR_CSICAL_Msk                             /*!< CSI clock calibration */
#define RCC_CSICFGR_CSICAL_0                      (0x1U << RCC_CSICFGR_CSICAL_Pos)               /*!< 0x00010000 */
#define RCC_CSICFGR_CSICAL_1                      (0x2U << RCC_CSICFGR_CSICAL_Pos)               /*!< 0x00020000 */
#define RCC_CSICFGR_CSICAL_2                      (0x4U << RCC_CSICFGR_CSICAL_Pos)               /*!< 0x00040000 */
#define RCC_CSICFGR_CSICAL_3                      (0x8U << RCC_CSICFGR_CSICAL_Pos)               /*!< 0x00080000 */
#define RCC_CSICFGR_CSICAL_4                      (0x10U << RCC_CSICFGR_CSICAL_Pos)              /*!< 0x00100000 */
#define RCC_CSICFGR_CSICAL_5                      (0x20U << RCC_CSICFGR_CSICAL_Pos)              /*!< 0x00200000 */
#define RCC_CSICFGR_CSICAL_6                      (0x40U << RCC_CSICFGR_CSICAL_Pos)              /*!< 0x00400000 */
#define RCC_CSICFGR_CSICAL_7                      (0x80U << RCC_CSICFGR_CSICAL_Pos)              /*!< 0x00800000 */

/*****************  Bit definition for RCC_MPCKSELR register  *****************/
#define RCC_MPCKSELR_MPUSRC_Pos                   (0U)
#define RCC_MPCKSELR_MPUSRC_Msk                   (0x3U << RCC_MPCKSELR_MPUSRC_Pos)                  /*!< 0x00000003 */
#define RCC_MPCKSELR_MPUSRC                       RCC_MPCKSELR_MPUSRC_Msk                            /*!< MPU clock switch */
#define RCC_MPCKSELR_MPUSRC_0                     (0x1U << RCC_MPCKSELR_MPUSRC_Pos)                  /*!< 0x00000001 */
#define RCC_MPCKSELR_MPUSRC_1                     (0x2U << RCC_MPCKSELR_MPUSRC_Pos)                  /*!< 0x00000002 */
#define RCC_MPCKSELR_MPUSRCRDY_Pos                (31U)
#define RCC_MPCKSELR_MPUSRCRDY_Msk                (0x1U << RCC_MPCKSELR_MPUSRCRDY_Pos)               /*!< 0x80000000 */
#define RCC_MPCKSELR_MPUSRCRDY                    RCC_MPCKSELR_MPUSRCRDY_Msk                         /*!< MPU clock switch status */

/****************  Bit definition for RCC_ASSCKSELR register  *****************/
#define RCC_ASSCKSELR_AXISSRC_Pos                 (0U)
#define RCC_ASSCKSELR_AXISSRC_Msk                 (0x7U << RCC_ASSCKSELR_AXISSRC_Pos)                /*!< 0x00000007 */
#define RCC_ASSCKSELR_AXISSRC                     RCC_ASSCKSELR_AXISSRC_Msk                          /*!< AXI sub-system clock switch */
#define RCC_ASSCKSELR_AXISSRC_0                   (0x1U << RCC_ASSCKSELR_AXISSRC_Pos)                /*!< 0x00000001 */
#define RCC_ASSCKSELR_AXISSRC_1                   (0x2U << RCC_ASSCKSELR_AXISSRC_Pos)                /*!< 0x00000002 */
#define RCC_ASSCKSELR_AXISSRC_2                   (0x4U << RCC_ASSCKSELR_AXISSRC_Pos)                /*!< 0x00000004 */
#define RCC_ASSCKSELR_AXISSRCRDY_Pos              (31U)
#define RCC_ASSCKSELR_AXISSRCRDY_Msk              (0x1U << RCC_ASSCKSELR_AXISSRCRDY_Pos)             /*!< 0x80000000 */
#define RCC_ASSCKSELR_AXISSRCRDY                  RCC_ASSCKSELR_AXISSRCRDY_Msk                       /*!< AXI sub-system clock switch status */

/****************  Bit definition for RCC_RCK12SELR register  *****************/
#define RCC_RCK12SELR_PLL12SRC_Pos                (0U)
#define RCC_RCK12SELR_PLL12SRC_Msk                (0x3U << RCC_RCK12SELR_PLL12SRC_Pos)               /*!< 0x00000003 */
#define RCC_RCK12SELR_PLL12SRC                    RCC_RCK12SELR_PLL12SRC_Msk                         /*!< Reference clock selection for PLL1 and PLL2 */
#define RCC_RCK12SELR_PLL12SRC_0                  (0x1U << RCC_RCK12SELR_PLL12SRC_Pos)               /*!< 0x00000001 */
#define RCC_RCK12SELR_PLL12SRC_1                  (0x2U << RCC_RCK12SELR_PLL12SRC_Pos)               /*!< 0x00000002 */
#define RCC_RCK12SELR_PLL12SRCRDY_Pos             (31U)
#define RCC_RCK12SELR_PLL12SRCRDY_Msk             (0x1U << RCC_RCK12SELR_PLL12SRCRDY_Pos)            /*!< 0x80000000 */
#define RCC_RCK12SELR_PLL12SRCRDY                 RCC_RCK12SELR_PLL12SRCRDY_Msk                      /*!< PLL12 reference clock switch status */

/*****************  Bit definition for RCC_MPCKDIVR register  *****************/
#define RCC_MPCKDIVR_MPUDIV_Pos                   (0U)
#define RCC_MPCKDIVR_MPUDIV_Msk                   (0x7U << RCC_MPCKDIVR_MPUDIV_Pos)                  /*!< 0x00000007 */
#define RCC_MPCKDIVR_MPUDIV                       RCC_MPCKDIVR_MPUDIV_Msk                            /*!< MPU Core clock divider */
#define RCC_MPCKDIVR_MPUDIV_0                     (0x1U << RCC_MPCKDIVR_MPUDIV_Pos)                  /*!< 0x00000001 */
#define RCC_MPCKDIVR_MPUDIV_1                     (0x2U << RCC_MPCKDIVR_MPUDIV_Pos)                  /*!< 0x00000002 */
#define RCC_MPCKDIVR_MPUDIV_2                     (0x4U << RCC_MPCKDIVR_MPUDIV_Pos)                  /*!< 0x00000004 */
#define RCC_MPCKDIVR_MPUDIVRDY_Pos                (31U)
#define RCC_MPCKDIVR_MPUDIVRDY_Msk                (0x1U << RCC_MPCKDIVR_MPUDIVRDY_Pos)               /*!< 0x80000000 */
#define RCC_MPCKDIVR_MPUDIVRDY                    RCC_MPCKDIVR_MPUDIVRDY_Msk                         /*!< MPU sub-system clock divider status */

/*****************  Bit definition for RCC_AXIDIVR register  ******************/
#define RCC_AXIDIVR_AXIDIV_Pos                    (0U)
#define RCC_AXIDIVR_AXIDIV_Msk                    (0x7U << RCC_AXIDIVR_AXIDIV_Pos)                   /*!< 0x00000007 */
#define RCC_AXIDIVR_AXIDIV                        RCC_AXIDIVR_AXIDIV_Msk                             /*!< AXI, AHB5 and AHB6 clock divider */
#define RCC_AXIDIVR_AXIDIV_0                      (0x1U << RCC_AXIDIVR_AXIDIV_Pos)                   /*!< 0x00000001 */
#define RCC_AXIDIVR_AXIDIV_1                      (0x2U << RCC_AXIDIVR_AXIDIV_Pos)                   /*!< 0x00000002 */
#define RCC_AXIDIVR_AXIDIV_2                      (0x4U << RCC_AXIDIVR_AXIDIV_Pos)                   /*!< 0x00000004 */
#define RCC_AXIDIVR_AXIDIVRDY_Pos                 (31U)
#define RCC_AXIDIVR_AXIDIVRDY_Msk                 (0x1U << RCC_AXIDIVR_AXIDIVRDY_Pos)                /*!< 0x80000000 */
#define RCC_AXIDIVR_AXIDIVRDY                     RCC_AXIDIVR_AXIDIVRDY_Msk                          /*!< AXI sub-system clock divider status */

/*****************  Bit definition for RCC_APB4DIVR register  *****************/
#define RCC_APB4DIVR_APB4DIV_Pos                  (0U)
#define RCC_APB4DIVR_APB4DIV_Msk                  (0x7U << RCC_APB4DIVR_APB4DIV_Pos)                 /*!< 0x00000007 */
#define RCC_APB4DIVR_APB4DIV                      RCC_APB4DIVR_APB4DIV_Msk                           /*!< APB4 clock divider */
#define RCC_APB4DIVR_APB4DIV_0                    (0x1U << RCC_APB4DIVR_APB4DIV_Pos)                 /*!< 0x00000001 */
#define RCC_APB4DIVR_APB4DIV_1                    (0x2U << RCC_APB4DIVR_APB4DIV_Pos)                 /*!< 0x00000002 */
#define RCC_APB4DIVR_APB4DIV_2                    (0x4U << RCC_APB4DIVR_APB4DIV_Pos)                 /*!< 0x00000004 */
#define RCC_APB4DIVR_APB4DIVRDY_Pos               (31U)
#define RCC_APB4DIVR_APB4DIVRDY_Msk               (0x1U << RCC_APB4DIVR_APB4DIVRDY_Pos)              /*!< 0x80000000 */
#define RCC_APB4DIVR_APB4DIVRDY                   RCC_APB4DIVR_APB4DIVRDY_Msk                        /*!< APB4 clock divider status */

/*****************  Bit definition for RCC_APB5DIVR register  *****************/
#define RCC_APB5DIVR_APB5DIV_Pos                  (0U)
#define RCC_APB5DIVR_APB5DIV_Msk                  (0x7U << RCC_APB5DIVR_APB5DIV_Pos)                 /*!< 0x00000007 */
#define RCC_APB5DIVR_APB5DIV                      RCC_APB5DIVR_APB5DIV_Msk                           /*!< APB5 clock divider */
#define RCC_APB5DIVR_APB5DIV_0                    (0x1U << RCC_APB5DIVR_APB5DIV_Pos)                 /*!< 0x00000001 */
#define RCC_APB5DIVR_APB5DIV_1                    (0x2U << RCC_APB5DIVR_APB5DIV_Pos)                 /*!< 0x00000002 */
#define RCC_APB5DIVR_APB5DIV_2                    (0x4U << RCC_APB5DIVR_APB5DIV_Pos)                 /*!< 0x00000004 */
#define RCC_APB5DIVR_APB5DIVRDY_Pos               (31U)
#define RCC_APB5DIVR_APB5DIVRDY_Msk               (0x1U << RCC_APB5DIVR_APB5DIVRDY_Pos)              /*!< 0x80000000 */
#define RCC_APB5DIVR_APB5DIVRDY                   RCC_APB5DIVR_APB5DIVRDY_Msk                        /*!< APB5 clock divider status */

/*****************  Bit definition for RCC_RTCDIVR register  ******************/
#define RCC_RTCDIVR_RTCDIV_Pos                    (0U)
#define RCC_RTCDIVR_RTCDIV_Msk                    (0x3FU << RCC_RTCDIVR_RTCDIV_Pos)                  /*!< 0x0000003F */
#define RCC_RTCDIVR_RTCDIV                        RCC_RTCDIVR_RTCDIV_Msk                             /*!< HSE division factor for RTC clock */
#define RCC_RTCDIVR_RTCDIV_0                      (0x1U << RCC_RTCDIVR_RTCDIV_Pos)                   /*!< 0x00000001 */
#define RCC_RTCDIVR_RTCDIV_1                      (0x2U << RCC_RTCDIVR_RTCDIV_Pos)                   /*!< 0x00000002 */
#define RCC_RTCDIVR_RTCDIV_2                      (0x4U << RCC_RTCDIVR_RTCDIV_Pos)                   /*!< 0x00000004 */
#define RCC_RTCDIVR_RTCDIV_3                      (0x8U << RCC_RTCDIVR_RTCDIV_Pos)                   /*!< 0x00000008 */
#define RCC_RTCDIVR_RTCDIV_4                      (0x10U << RCC_RTCDIVR_RTCDIV_Pos)                  /*!< 0x00000010 */
#define RCC_RTCDIVR_RTCDIV_5                      (0x20U << RCC_RTCDIVR_RTCDIV_Pos)                  /*!< 0x00000020 */

/****************  Bit definition for RCC_MSSCKSELR register  *****************/
#define RCC_MSSCKSELR_MCUSSRC_Pos                 (0U)
#define RCC_MSSCKSELR_MCUSSRC_Msk                 (0x3U << RCC_MSSCKSELR_MCUSSRC_Pos)                /*!< 0x00000003 */
#define RCC_MSSCKSELR_MCUSSRC                     RCC_MSSCKSELR_MCUSSRC_Msk                          /*!< MCUSS clock switch */
#define RCC_MSSCKSELR_MCUSSRC_0                   (0x1U << RCC_MSSCKSELR_MCUSSRC_Pos)                /*!< 0x00000001 */
#define RCC_MSSCKSELR_MCUSSRC_1                   (0x2U << RCC_MSSCKSELR_MCUSSRC_Pos)                /*!< 0x00000002 */
#define RCC_MSSCKSELR_MCUSSRCRDY_Pos              (31U)
#define RCC_MSSCKSELR_MCUSSRCRDY_Msk              (0x1U << RCC_MSSCKSELR_MCUSSRCRDY_Pos)             /*!< 0x80000000 */
#define RCC_MSSCKSELR_MCUSSRCRDY                  RCC_MSSCKSELR_MCUSSRCRDY_Msk                       /*!< MCU sub-system clock switch status */

/******************  Bit definition for RCC_PLL1CR register  ******************/
#define RCC_PLL1CR_PLLON_Pos                      (0U)
#define RCC_PLL1CR_PLLON_Msk                      (0x1U << RCC_PLL1CR_PLLON_Pos)                     /*!< 0x00000001 */
#define RCC_PLL1CR_PLLON                          RCC_PLL1CR_PLLON_Msk                               /*!< PLL1 enable */
#define RCC_PLL1CR_PLL1RDY_Pos                    (1U)
#define RCC_PLL1CR_PLL1RDY_Msk                    (0x1U << RCC_PLL1CR_PLL1RDY_Pos)                   /*!< 0x00000002 */
#define RCC_PLL1CR_PLL1RDY                        RCC_PLL1CR_PLL1RDY_Msk                             /*!< PLL1 clock ready flag */
#define RCC_PLL1CR_SSCG_CTRL_Pos                  (2U)
#define RCC_PLL1CR_SSCG_CTRL_Msk                  (0x1U << RCC_PLL1CR_SSCG_CTRL_Pos)                 /*!< 0x00000004 */
#define RCC_PLL1CR_SSCG_CTRL                      RCC_PLL1CR_SSCG_CTRL_Msk                           /*!< Spread Spectrum Clock Generator of PLL1 enable */
#define RCC_PLL1CR_DIVPEN_Pos                     (4U)
#define RCC_PLL1CR_DIVPEN_Msk                     (0x1U << RCC_PLL1CR_DIVPEN_Pos)                    /*!< 0x00000010 */
#define RCC_PLL1CR_DIVPEN                         RCC_PLL1CR_DIVPEN_Msk                              /*!< PLL1 DIVP divider output enable */
#define RCC_PLL1CR_DIVQEN_Pos                     (5U)
#define RCC_PLL1CR_DIVQEN_Msk                     (0x1U << RCC_PLL1CR_DIVQEN_Pos)                    /*!< 0x00000020 */
#define RCC_PLL1CR_DIVQEN                         RCC_PLL1CR_DIVQEN_Msk                              /*!< PLL1 DIVQ divider output enable */
#define RCC_PLL1CR_DIVREN_Pos                     (6U)
#define RCC_PLL1CR_DIVREN_Msk                     (0x1U << RCC_PLL1CR_DIVREN_Pos)                    /*!< 0x00000040 */
#define RCC_PLL1CR_DIVREN                         RCC_PLL1CR_DIVREN_Msk                              /*!< PLL1 DIVR divider output enable */

/****************  Bit definition for RCC_PLL1CFGR1 register  *****************/
#define RCC_PLL1CFGR1_DIVN_Pos                    (0U)
#define RCC_PLL1CFGR1_DIVN_Msk                    (0x1FFU << RCC_PLL1CFGR1_DIVN_Pos)                 /*!< 0x000001FF */
#define RCC_PLL1CFGR1_DIVN                        RCC_PLL1CFGR1_DIVN_Msk                             /*!< Multiplication factor for PLL1 VCO */
#define RCC_PLL1CFGR1_DIVN_0                      (0x1U << RCC_PLL1CFGR1_DIVN_Pos)                   /*!< 0x00000001 */
#define RCC_PLL1CFGR1_DIVN_1                      (0x2U << RCC_PLL1CFGR1_DIVN_Pos)                   /*!< 0x00000002 */
#define RCC_PLL1CFGR1_DIVN_2                      (0x4U << RCC_PLL1CFGR1_DIVN_Pos)                   /*!< 0x00000004 */
#define RCC_PLL1CFGR1_DIVN_3                      (0x8U << RCC_PLL1CFGR1_DIVN_Pos)                   /*!< 0x00000008 */
#define RCC_PLL1CFGR1_DIVN_4                      (0x10U << RCC_PLL1CFGR1_DIVN_Pos)                  /*!< 0x00000010 */
#define RCC_PLL1CFGR1_DIVN_5                      (0x20U << RCC_PLL1CFGR1_DIVN_Pos)                  /*!< 0x00000020 */
#define RCC_PLL1CFGR1_DIVN_6                      (0x40U << RCC_PLL1CFGR1_DIVN_Pos)                  /*!< 0x00000040 */
#define RCC_PLL1CFGR1_DIVN_7                      (0x80U << RCC_PLL1CFGR1_DIVN_Pos)                  /*!< 0x00000080 */
#define RCC_PLL1CFGR1_DIVN_8                      (0x100U << RCC_PLL1CFGR1_DIVN_Pos)                 /*!< 0x00000100 */
#define RCC_PLL1CFGR1_DIVM1_Pos                   (16U)
#define RCC_PLL1CFGR1_DIVM1_Msk                   (0x3FU << RCC_PLL1CFGR1_DIVM1_Pos)                 /*!< 0x003F0000 */
#define RCC_PLL1CFGR1_DIVM1                       RCC_PLL1CFGR1_DIVM1_Msk                            /*!< Prescaler for PLL1 */
#define RCC_PLL1CFGR1_DIVM1_0                     (0x1U << RCC_PLL1CFGR1_DIVM1_Pos)              /*!< 0x00010000 */
#define RCC_PLL1CFGR1_DIVM1_1                     (0x2U << RCC_PLL1CFGR1_DIVM1_Pos)              /*!< 0x00020000 */
#define RCC_PLL1CFGR1_DIVM1_2                     (0x4U << RCC_PLL1CFGR1_DIVM1_Pos)              /*!< 0x00040000 */
#define RCC_PLL1CFGR1_DIVM1_3                     (0x8U << RCC_PLL1CFGR1_DIVM1_Pos)              /*!< 0x00080000 */
#define RCC_PLL1CFGR1_DIVM1_4                     (0x10U << RCC_PLL1CFGR1_DIVM1_Pos)             /*!< 0x00100000 */
#define RCC_PLL1CFGR1_DIVM1_5                     (0x20U << RCC_PLL1CFGR1_DIVM1_Pos)             /*!< 0x00200000 */

/****************  Bit definition for RCC_PLL1CFGR2 register  *****************/
#define RCC_PLL1CFGR2_DIVP_Pos                    (0U)
#define RCC_PLL1CFGR2_DIVP_Msk                    (0x7FU << RCC_PLL1CFGR2_DIVP_Pos)                  /*!< 0x0000007F */
#define RCC_PLL1CFGR2_DIVP                        RCC_PLL1CFGR2_DIVP_Msk                             /*!< PLL1 DIVP division factor */
#define RCC_PLL1CFGR2_DIVP_0                      (0x1U << RCC_PLL1CFGR2_DIVP_Pos)                   /*!< 0x00000001 */
#define RCC_PLL1CFGR2_DIVP_1                      (0x2U << RCC_PLL1CFGR2_DIVP_Pos)                   /*!< 0x00000002 */
#define RCC_PLL1CFGR2_DIVP_2                      (0x4U << RCC_PLL1CFGR2_DIVP_Pos)                   /*!< 0x00000004 */
#define RCC_PLL1CFGR2_DIVP_3                      (0x8U << RCC_PLL1CFGR2_DIVP_Pos)                   /*!< 0x00000008 */
#define RCC_PLL1CFGR2_DIVP_4                      (0x10U << RCC_PLL1CFGR2_DIVP_Pos)                  /*!< 0x00000010 */
#define RCC_PLL1CFGR2_DIVP_5                      (0x20U << RCC_PLL1CFGR2_DIVP_Pos)                  /*!< 0x00000020 */
#define RCC_PLL1CFGR2_DIVP_6                      (0x40U << RCC_PLL1CFGR2_DIVP_Pos)                  /*!< 0x00000040 */
#define RCC_PLL1CFGR2_DIVQ_Pos                    (8U)
#define RCC_PLL1CFGR2_DIVQ_Msk                    (0x7FU << RCC_PLL1CFGR2_DIVQ_Pos)                  /*!< 0x00007F00 */
#define RCC_PLL1CFGR2_DIVQ                        RCC_PLL1CFGR2_DIVQ_Msk                             /*!< PLL1 DIVQ division factor */
#define RCC_PLL1CFGR2_DIVQ_0                      (0x1U << RCC_PLL1CFGR2_DIVQ_Pos)                 /*!< 0x00000100 */
#define RCC_PLL1CFGR2_DIVQ_1                      (0x2U << RCC_PLL1CFGR2_DIVQ_Pos)                 /*!< 0x00000200 */
#define RCC_PLL1CFGR2_DIVQ_2                      (0x4U << RCC_PLL1CFGR2_DIVQ_Pos)                 /*!< 0x00000400 */
#define RCC_PLL1CFGR2_DIVQ_3                      (0x8U << RCC_PLL1CFGR2_DIVQ_Pos)                 /*!< 0x00000800 */
#define RCC_PLL1CFGR2_DIVQ_4                      (0x10U << RCC_PLL1CFGR2_DIVQ_Pos)                /*!< 0x00001000 */
#define RCC_PLL1CFGR2_DIVQ_5                      (0x20U << RCC_PLL1CFGR2_DIVQ_Pos)                /*!< 0x00002000 */
#define RCC_PLL1CFGR2_DIVQ_6                      (0x40U << RCC_PLL1CFGR2_DIVQ_Pos)                /*!< 0x00004000 */
#define RCC_PLL1CFGR2_DIVR_Pos                    (16U)
#define RCC_PLL1CFGR2_DIVR_Msk                    (0x7FU << RCC_PLL1CFGR2_DIVR_Pos)                  /*!< 0x007F0000 */
#define RCC_PLL1CFGR2_DIVR                        RCC_PLL1CFGR2_DIVR_Msk                             /*!< PLL1 DIVR division factor */
#define RCC_PLL1CFGR2_DIVR_0                      (0x1U << RCC_PLL1CFGR2_DIVR_Pos)               /*!< 0x00010000 */
#define RCC_PLL1CFGR2_DIVR_1                      (0x2U << RCC_PLL1CFGR2_DIVR_Pos)               /*!< 0x00020000 */
#define RCC_PLL1CFGR2_DIVR_2                      (0x4U << RCC_PLL1CFGR2_DIVR_Pos)               /*!< 0x00040000 */
#define RCC_PLL1CFGR2_DIVR_3                      (0x8U << RCC_PLL1CFGR2_DIVR_Pos)               /*!< 0x00080000 */
#define RCC_PLL1CFGR2_DIVR_4                      (0x10U << RCC_PLL1CFGR2_DIVR_Pos)              /*!< 0x00100000 */
#define RCC_PLL1CFGR2_DIVR_5                      (0x20U << RCC_PLL1CFGR2_DIVR_Pos)              /*!< 0x00200000 */
#define RCC_PLL1CFGR2_DIVR_6                      (0x40U << RCC_PLL1CFGR2_DIVR_Pos)              /*!< 0x00400000 */

/****************  Bit definition for RCC_PLL1FRACR register  *****************/
#define RCC_PLL1FRACR_FRACV_Pos                   (3U)
#define RCC_PLL1FRACR_FRACV_Msk                   (0x1FFFU << RCC_PLL1FRACR_FRACV_Pos)               /*!< 0x0000FFF8 */
#define RCC_PLL1FRACR_FRACV                       RCC_PLL1FRACR_FRACV_Msk                            /*!< Fractional part of the multiplication factor for PLL1 VCO */
#define RCC_PLL1FRACR_FRACV_0                     (0x1U << RCC_PLL1FRACR_FRACV_Pos)                  /*!< 0x00000008 */
#define RCC_PLL1FRACR_FRACV_1                     (0x2U << RCC_PLL1FRACR_FRACV_Pos)                 /*!< 0x00000010 */
#define RCC_PLL1FRACR_FRACV_2                     (0x4U << RCC_PLL1FRACR_FRACV_Pos)                 /*!< 0x00000020 */
#define RCC_PLL1FRACR_FRACV_3                     (0x8U << RCC_PLL1FRACR_FRACV_Pos)                 /*!< 0x00000040 */
#define RCC_PLL1FRACR_FRACV_4                     (0x10U << RCC_PLL1FRACR_FRACV_Pos)                 /*!< 0x00000080 */
#define RCC_PLL1FRACR_FRACV_5                     (0x20U << RCC_PLL1FRACR_FRACV_Pos)                /*!< 0x00000100 */
#define RCC_PLL1FRACR_FRACV_6                     (0x40U << RCC_PLL1FRACR_FRACV_Pos)                /*!< 0x00000200 */
#define RCC_PLL1FRACR_FRACV_7                     (0x80U << RCC_PLL1FRACR_FRACV_Pos)                /*!< 0x00000400 */
#define RCC_PLL1FRACR_FRACV_8                     (0x100U << RCC_PLL1FRACR_FRACV_Pos)                /*!< 0x00000800 */
#define RCC_PLL1FRACR_FRACV_9                     (0x200U << RCC_PLL1FRACR_FRACV_Pos)               /*!< 0x00001000 */
#define RCC_PLL1FRACR_FRACV_10                    (0x400U << RCC_PLL1FRACR_FRACV_Pos)               /*!< 0x00002000 */
#define RCC_PLL1FRACR_FRACV_11                    (0x800U << RCC_PLL1FRACR_FRACV_Pos)               /*!< 0x00004000 */
#define RCC_PLL1FRACR_FRACV_12                    (0x1000U << RCC_PLL1FRACR_FRACV_Pos)               /*!< 0x00008000 */
#define RCC_PLL1FRACR_FRACLE_Pos                  (16U)
#define RCC_PLL1FRACR_FRACLE_Msk                  (0x1U << RCC_PLL1FRACR_FRACLE_Pos)                 /*!< 0x00010000 */
#define RCC_PLL1FRACR_FRACLE                      RCC_PLL1FRACR_FRACLE_Msk                           /*!< PLL1 fractional latch enable */

/*****************  Bit definition for RCC_PLL1CSGR register  *****************/
#define RCC_PLL1CSGR_MOD_PER_Pos                  (0U)
#define RCC_PLL1CSGR_MOD_PER_Msk                  (0x1FFFU << RCC_PLL1CSGR_MOD_PER_Pos)              /*!< 0x00001FFF */
#define RCC_PLL1CSGR_MOD_PER                      RCC_PLL1CSGR_MOD_PER_Msk                           /*!< Modulation Period Adjustment for PLL1 */
#define RCC_PLL1CSGR_MOD_PER_0                    (0x1U << RCC_PLL1CSGR_MOD_PER_Pos)                 /*!< 0x00000001 */
#define RCC_PLL1CSGR_MOD_PER_1                    (0x2U << RCC_PLL1CSGR_MOD_PER_Pos)                 /*!< 0x00000002 */
#define RCC_PLL1CSGR_MOD_PER_2                    (0x4U << RCC_PLL1CSGR_MOD_PER_Pos)                 /*!< 0x00000004 */
#define RCC_PLL1CSGR_MOD_PER_3                    (0x8U << RCC_PLL1CSGR_MOD_PER_Pos)                 /*!< 0x00000008 */
#define RCC_PLL1CSGR_MOD_PER_4                    (0x10U << RCC_PLL1CSGR_MOD_PER_Pos)                /*!< 0x00000010 */
#define RCC_PLL1CSGR_MOD_PER_5                    (0x20U << RCC_PLL1CSGR_MOD_PER_Pos)                /*!< 0x00000020 */
#define RCC_PLL1CSGR_MOD_PER_6                    (0x40U << RCC_PLL1CSGR_MOD_PER_Pos)                /*!< 0x00000040 */
#define RCC_PLL1CSGR_MOD_PER_7                    (0x80U << RCC_PLL1CSGR_MOD_PER_Pos)                /*!< 0x00000080 */
#define RCC_PLL1CSGR_MOD_PER_8                    (0x100U << RCC_PLL1CSGR_MOD_PER_Pos)               /*!< 0x00000100 */
#define RCC_PLL1CSGR_MOD_PER_9                    (0x200U << RCC_PLL1CSGR_MOD_PER_Pos)               /*!< 0x00000200 */
#define RCC_PLL1CSGR_MOD_PER_10                   (0x400U << RCC_PLL1CSGR_MOD_PER_Pos)               /*!< 0x00000400 */
#define RCC_PLL1CSGR_MOD_PER_11                   (0x800U << RCC_PLL1CSGR_MOD_PER_Pos)               /*!< 0x00000800 */
#define RCC_PLL1CSGR_MOD_PER_12                   (0x1000U << RCC_PLL1CSGR_MOD_PER_Pos)              /*!< 0x00001000 */
#define RCC_PLL1CSGR_TPDFN_DIS_Pos                (13U)
#define RCC_PLL1CSGR_TPDFN_DIS_Msk                (0x1U << RCC_PLL1CSGR_TPDFN_DIS_Pos)               /*!< 0x00002000 */
#define RCC_PLL1CSGR_TPDFN_DIS                    RCC_PLL1CSGR_TPDFN_DIS_Msk                         /*!< Dithering TPDF noise control */
#define RCC_PLL1CSGR_RPDFN_DIS_Pos                (14U)
#define RCC_PLL1CSGR_RPDFN_DIS_Msk                (0x1U << RCC_PLL1CSGR_RPDFN_DIS_Pos)               /*!< 0x00004000 */
#define RCC_PLL1CSGR_RPDFN_DIS                    RCC_PLL1CSGR_RPDFN_DIS_Msk                         /*!< Dithering RPDF noise control */
#define RCC_PLL1CSGR_SSCG_MODE_Pos                (15U)
#define RCC_PLL1CSGR_SSCG_MODE_Msk                (0x1U << RCC_PLL1CSGR_SSCG_MODE_Pos)               /*!< 0x00008000 */
#define RCC_PLL1CSGR_SSCG_MODE                    RCC_PLL1CSGR_SSCG_MODE_Msk                         /*!< Spread spectrum clock generator mode */
#define RCC_PLL1CSGR_INC_STEP_Pos                 (16U)
#define RCC_PLL1CSGR_INC_STEP_Msk                 (0x7FFFU << RCC_PLL1CSGR_INC_STEP_Pos)             /*!< 0x7FFF0000 */
#define RCC_PLL1CSGR_INC_STEP                     RCC_PLL1CSGR_INC_STEP_Msk                          /*!< Modulation Depth Adjustment for PLL1 */
#define RCC_PLL1CSGR_INC_STEP_0                   (0x1U << RCC_PLL1CSGR_INC_STEP_Pos)            /*!< 0x00010000 */
#define RCC_PLL1CSGR_INC_STEP_1                   (0x2U << RCC_PLL1CSGR_INC_STEP_Pos)            /*!< 0x00020000 */
#define RCC_PLL1CSGR_INC_STEP_2                   (0x4U << RCC_PLL1CSGR_INC_STEP_Pos)            /*!< 0x00040000 */
#define RCC_PLL1CSGR_INC_STEP_3                   (0x8U << RCC_PLL1CSGR_INC_STEP_Pos)            /*!< 0x00080000 */
#define RCC_PLL1CSGR_INC_STEP_4                   (0x10U << RCC_PLL1CSGR_INC_STEP_Pos)           /*!< 0x00100000 */
#define RCC_PLL1CSGR_INC_STEP_5                   (0x20U << RCC_PLL1CSGR_INC_STEP_Pos)           /*!< 0x00200000 */
#define RCC_PLL1CSGR_INC_STEP_6                   (0x40U << RCC_PLL1CSGR_INC_STEP_Pos)           /*!< 0x00400000 */
#define RCC_PLL1CSGR_INC_STEP_7                   (0x80U << RCC_PLL1CSGR_INC_STEP_Pos)           /*!< 0x00800000 */
#define RCC_PLL1CSGR_INC_STEP_8                   (0x100U << RCC_PLL1CSGR_INC_STEP_Pos)          /*!< 0x01000000 */
#define RCC_PLL1CSGR_INC_STEP_9                   (0x200U << RCC_PLL1CSGR_INC_STEP_Pos)          /*!< 0x02000000 */
#define RCC_PLL1CSGR_INC_STEP_10                  (0x400U << RCC_PLL1CSGR_INC_STEP_Pos)          /*!< 0x04000000 */
#define RCC_PLL1CSGR_INC_STEP_11                  (0x800U << RCC_PLL1CSGR_INC_STEP_Pos)          /*!< 0x08000000 */
#define RCC_PLL1CSGR_INC_STEP_12                  (0x1000U << RCC_PLL1CSGR_INC_STEP_Pos)         /*!< 0x10000000 */
#define RCC_PLL1CSGR_INC_STEP_13                  (0x2000U << RCC_PLL1CSGR_INC_STEP_Pos)         /*!< 0x20000000 */
#define RCC_PLL1CSGR_INC_STEP_14                  (0x4000U << RCC_PLL1CSGR_INC_STEP_Pos)         /*!< 0x40000000 */

/******************  Bit definition for RCC_PLL2CR register  ******************/
#define RCC_PLL2CR_PLLON_Pos                      (0U)
#define RCC_PLL2CR_PLLON_Msk                      (0x1U << RCC_PLL2CR_PLLON_Pos)                     /*!< 0x00000001 */
#define RCC_PLL2CR_PLLON                          RCC_PLL2CR_PLLON_Msk                               /*!< PLL2 enable */
#define RCC_PLL2CR_PLL2RDY_Pos                    (1U)
#define RCC_PLL2CR_PLL2RDY_Msk                    (0x1U << RCC_PLL2CR_PLL2RDY_Pos)                   /*!< 0x00000002 */
#define RCC_PLL2CR_PLL2RDY                        RCC_PLL2CR_PLL2RDY_Msk                             /*!< PLL2 clock ready flag */
#define RCC_PLL2CR_SSCG_CTRL_Pos                  (2U)
#define RCC_PLL2CR_SSCG_CTRL_Msk                  (0x1U << RCC_PLL2CR_SSCG_CTRL_Pos)                 /*!< 0x00000004 */
#define RCC_PLL2CR_SSCG_CTRL                      RCC_PLL2CR_SSCG_CTRL_Msk                           /*!< Clock Spreading Generator of PLL2 enable */
#define RCC_PLL2CR_DIVPEN_Pos                     (4U)
#define RCC_PLL2CR_DIVPEN_Msk                     (0x1U << RCC_PLL2CR_DIVPEN_Pos)                    /*!< 0x00000010 */
#define RCC_PLL2CR_DIVPEN                         RCC_PLL2CR_DIVPEN_Msk                              /*!< PLL2 DIVP divider output enable */
#define RCC_PLL2CR_DIVQEN_Pos                     (5U)
#define RCC_PLL2CR_DIVQEN_Msk                     (0x1U << RCC_PLL2CR_DIVQEN_Pos)                    /*!< 0x00000020 */
#define RCC_PLL2CR_DIVQEN                         RCC_PLL2CR_DIVQEN_Msk                              /*!< PLL2 DIVQ divider output enable */
#define RCC_PLL2CR_DIVREN_Pos                     (6U)
#define RCC_PLL2CR_DIVREN_Msk                     (0x1U << RCC_PLL2CR_DIVREN_Pos)                    /*!< 0x00000040 */
#define RCC_PLL2CR_DIVREN                         RCC_PLL2CR_DIVREN_Msk                              /*!< PLL2 DIVR divider output enable */

/****************  Bit definition for RCC_PLL2CFGR1 register  *****************/
#define RCC_PLL2CFGR1_DIVN_Pos                    (0U)
#define RCC_PLL2CFGR1_DIVN_Msk                    (0x1FFU << RCC_PLL2CFGR1_DIVN_Pos)                 /*!< 0x000001FF */
#define RCC_PLL2CFGR1_DIVN                        RCC_PLL2CFGR1_DIVN_Msk                             /*!< Multiplication factor for PLL2 VCO */
#define RCC_PLL2CFGR1_DIVN_0                      (0x1U << RCC_PLL2CFGR1_DIVN_Pos)                   /*!< 0x00000001 */
#define RCC_PLL2CFGR1_DIVN_1                      (0x2U << RCC_PLL2CFGR1_DIVN_Pos)                   /*!< 0x00000002 */
#define RCC_PLL2CFGR1_DIVN_2                      (0x4U << RCC_PLL2CFGR1_DIVN_Pos)                   /*!< 0x00000004 */
#define RCC_PLL2CFGR1_DIVN_3                      (0x8U << RCC_PLL2CFGR1_DIVN_Pos)                   /*!< 0x00000008 */
#define RCC_PLL2CFGR1_DIVN_4                      (0x10U << RCC_PLL2CFGR1_DIVN_Pos)                  /*!< 0x00000010 */
#define RCC_PLL2CFGR1_DIVN_5                      (0x20U << RCC_PLL2CFGR1_DIVN_Pos)                  /*!< 0x00000020 */
#define RCC_PLL2CFGR1_DIVN_6                      (0x40U << RCC_PLL2CFGR1_DIVN_Pos)                  /*!< 0x00000040 */
#define RCC_PLL2CFGR1_DIVN_7                      (0x80U << RCC_PLL2CFGR1_DIVN_Pos)                  /*!< 0x00000080 */
#define RCC_PLL2CFGR1_DIVN_8                      (0x100U << RCC_PLL2CFGR1_DIVN_Pos)                 /*!< 0x00000100 */
#define RCC_PLL2CFGR1_DIVM2_Pos                   (16U)
#define RCC_PLL2CFGR1_DIVM2_Msk                   (0x3FU << RCC_PLL2CFGR1_DIVM2_Pos)                 /*!< 0x003F0000 */
#define RCC_PLL2CFGR1_DIVM2                       RCC_PLL2CFGR1_DIVM2_Msk                            /*!< Prescaler for PLL2 */
#define RCC_PLL2CFGR1_DIVM2_0                     (0x1U << RCC_PLL2CFGR1_DIVM2_Pos)              /*!< 0x00010000 */
#define RCC_PLL2CFGR1_DIVM2_1                     (0x2U << RCC_PLL2CFGR1_DIVM2_Pos)              /*!< 0x00020000 */
#define RCC_PLL2CFGR1_DIVM2_2                     (0x4U << RCC_PLL2CFGR1_DIVM2_Pos)              /*!< 0x00040000 */
#define RCC_PLL2CFGR1_DIVM2_3                     (0x8U << RCC_PLL2CFGR1_DIVM2_Pos)              /*!< 0x00080000 */
#define RCC_PLL2CFGR1_DIVM2_4                     (0x10U << RCC_PLL2CFGR1_DIVM2_Pos)             /*!< 0x00100000 */
#define RCC_PLL2CFGR1_DIVM2_5                     (0x20U << RCC_PLL2CFGR1_DIVM2_Pos)             /*!< 0x00200000 */

/****************  Bit definition for RCC_PLL2CFGR2 register  *****************/
#define RCC_PLL2CFGR2_DIVP_Pos                    (0U)
#define RCC_PLL2CFGR2_DIVP_Msk                    (0x7FU << RCC_PLL2CFGR2_DIVP_Pos)                  /*!< 0x0000007F */
#define RCC_PLL2CFGR2_DIVP                        RCC_PLL2CFGR2_DIVP_Msk                             /*!< PLL2 DIVP division factor */
#define RCC_PLL2CFGR2_DIVP_0                      (0x1U << RCC_PLL2CFGR2_DIVP_Pos)                   /*!< 0x00000001 */
#define RCC_PLL2CFGR2_DIVP_1                      (0x2U << RCC_PLL2CFGR2_DIVP_Pos)                   /*!< 0x00000002 */
#define RCC_PLL2CFGR2_DIVP_2                      (0x4U << RCC_PLL2CFGR2_DIVP_Pos)                   /*!< 0x00000004 */
#define RCC_PLL2CFGR2_DIVP_3                      (0x8U << RCC_PLL2CFGR2_DIVP_Pos)                   /*!< 0x00000008 */
#define RCC_PLL2CFGR2_DIVP_4                      (0x10U << RCC_PLL2CFGR2_DIVP_Pos)                  /*!< 0x00000010 */
#define RCC_PLL2CFGR2_DIVP_5                      (0x20U << RCC_PLL2CFGR2_DIVP_Pos)                  /*!< 0x00000020 */
#define RCC_PLL2CFGR2_DIVP_6                      (0x40U << RCC_PLL2CFGR2_DIVP_Pos)                  /*!< 0x00000040 */
#define RCC_PLL2CFGR2_DIVQ_Pos                    (8U)
#define RCC_PLL2CFGR2_DIVQ_Msk                    (0x7FU << RCC_PLL2CFGR2_DIVQ_Pos)                  /*!< 0x00007F00 */
#define RCC_PLL2CFGR2_DIVQ                        RCC_PLL2CFGR2_DIVQ_Msk                             /*!< PLL2 DIVQ division factor */
#define RCC_PLL2CFGR2_DIVQ_0                      (0x1U << RCC_PLL2CFGR2_DIVQ_Pos)                 /*!< 0x00000100 */
#define RCC_PLL2CFGR2_DIVQ_1                      (0x2U << RCC_PLL2CFGR2_DIVQ_Pos)                 /*!< 0x00000200 */
#define RCC_PLL2CFGR2_DIVQ_2                      (0x4U << RCC_PLL2CFGR2_DIVQ_Pos)                 /*!< 0x00000400 */
#define RCC_PLL2CFGR2_DIVQ_3                      (0x8U << RCC_PLL2CFGR2_DIVQ_Pos)                 /*!< 0x00000800 */
#define RCC_PLL2CFGR2_DIVQ_4                      (0x10U << RCC_PLL2CFGR2_DIVQ_Pos)                /*!< 0x00001000 */
#define RCC_PLL2CFGR2_DIVQ_5                      (0x20U << RCC_PLL2CFGR2_DIVQ_Pos)                /*!< 0x00002000 */
#define RCC_PLL2CFGR2_DIVQ_6                      (0x40U << RCC_PLL2CFGR2_DIVQ_Pos)                /*!< 0x00004000 */
#define RCC_PLL2CFGR2_DIVR_Pos                    (16U)
#define RCC_PLL2CFGR2_DIVR_Msk                    (0x7FU << RCC_PLL2CFGR2_DIVR_Pos)                  /*!< 0x007F0000 */
#define RCC_PLL2CFGR2_DIVR                        RCC_PLL2CFGR2_DIVR_Msk                             /*!< PLL2 DIVR division factor */
#define RCC_PLL2CFGR2_DIVR_0                      (0x1U << RCC_PLL2CFGR2_DIVR_Pos)               /*!< 0x00010000 */
#define RCC_PLL2CFGR2_DIVR_1                      (0x2U << RCC_PLL2CFGR2_DIVR_Pos)               /*!< 0x00020000 */
#define RCC_PLL2CFGR2_DIVR_2                      (0x4U << RCC_PLL2CFGR2_DIVR_Pos)               /*!< 0x00040000 */
#define RCC_PLL2CFGR2_DIVR_3                      (0x8U << RCC_PLL2CFGR2_DIVR_Pos)               /*!< 0x00080000 */
#define RCC_PLL2CFGR2_DIVR_4                      (0x10U << RCC_PLL2CFGR2_DIVR_Pos)              /*!< 0x00100000 */
#define RCC_PLL2CFGR2_DIVR_5                      (0x20U << RCC_PLL2CFGR2_DIVR_Pos)              /*!< 0x00200000 */
#define RCC_PLL2CFGR2_DIVR_6                      (0x40U << RCC_PLL2CFGR2_DIVR_Pos)              /*!< 0x00400000 */

/****************  Bit definition for RCC_PLL2FRACR register  *****************/
#define RCC_PLL2FRACR_FRACV_Pos                   (3U)
#define RCC_PLL2FRACR_FRACV_Msk                   (0x1FFFU << RCC_PLL2FRACR_FRACV_Pos)               /*!< 0x0000FFF8 */
#define RCC_PLL2FRACR_FRACV                       RCC_PLL2FRACR_FRACV_Msk                            /*!< Fractional part of the multiplication factor for PLL2 VCO */
#define RCC_PLL2FRACR_FRACV_0                     (0x1U << RCC_PLL2FRACR_FRACV_Pos)                  /*!< 0x00000008 */
#define RCC_PLL2FRACR_FRACV_1                     (0x2U << RCC_PLL2FRACR_FRACV_Pos)                 /*!< 0x00000010 */
#define RCC_PLL2FRACR_FRACV_2                     (0x4U << RCC_PLL2FRACR_FRACV_Pos)                 /*!< 0x00000020 */
#define RCC_PLL2FRACR_FRACV_3                     (0x8U << RCC_PLL2FRACR_FRACV_Pos)                 /*!< 0x00000040 */
#define RCC_PLL2FRACR_FRACV_4                     (0x10U << RCC_PLL2FRACR_FRACV_Pos)                 /*!< 0x00000080 */
#define RCC_PLL2FRACR_FRACV_5                     (0x20U << RCC_PLL2FRACR_FRACV_Pos)                /*!< 0x00000100 */
#define RCC_PLL2FRACR_FRACV_6                     (0x40U << RCC_PLL2FRACR_FRACV_Pos)                /*!< 0x00000200 */
#define RCC_PLL2FRACR_FRACV_7                     (0x80U << RCC_PLL2FRACR_FRACV_Pos)                /*!< 0x00000400 */
#define RCC_PLL2FRACR_FRACV_8                     (0x100U << RCC_PLL2FRACR_FRACV_Pos)                /*!< 0x00000800 */
#define RCC_PLL2FRACR_FRACV_9                     (0x200U << RCC_PLL2FRACR_FRACV_Pos)               /*!< 0x00001000 */
#define RCC_PLL2FRACR_FRACV_10                    (0x400U << RCC_PLL2FRACR_FRACV_Pos)               /*!< 0x00002000 */
#define RCC_PLL2FRACR_FRACV_11                    (0x800U << RCC_PLL2FRACR_FRACV_Pos)               /*!< 0x00004000 */
#define RCC_PLL2FRACR_FRACV_12                    (0x1000U << RCC_PLL2FRACR_FRACV_Pos)               /*!< 0x00008000 */
#define RCC_PLL2FRACR_FRACLE_Pos                  (16U)
#define RCC_PLL2FRACR_FRACLE_Msk                  (0x1U << RCC_PLL2FRACR_FRACLE_Pos)                 /*!< 0x00010000 */
#define RCC_PLL2FRACR_FRACLE                      RCC_PLL2FRACR_FRACLE_Msk                           /*!< PLL2 fractional latch enable */

/*****************  Bit definition for RCC_PLL2CSGR register  *****************/
#define RCC_PLL2CSGR_MOD_PER_Pos                  (0U)
#define RCC_PLL2CSGR_MOD_PER_Msk                  (0x1FFFU << RCC_PLL2CSGR_MOD_PER_Pos)              /*!< 0x00001FFF */
#define RCC_PLL2CSGR_MOD_PER                      RCC_PLL2CSGR_MOD_PER_Msk                           /*!< Modulation Period Adjustment for PLL2 */
#define RCC_PLL2CSGR_MOD_PER_0                    (0x1U << RCC_PLL2CSGR_MOD_PER_Pos)                 /*!< 0x00000001 */
#define RCC_PLL2CSGR_MOD_PER_1                    (0x2U << RCC_PLL2CSGR_MOD_PER_Pos)                 /*!< 0x00000002 */
#define RCC_PLL2CSGR_MOD_PER_2                    (0x4U << RCC_PLL2CSGR_MOD_PER_Pos)                 /*!< 0x00000004 */
#define RCC_PLL2CSGR_MOD_PER_3                    (0x8U << RCC_PLL2CSGR_MOD_PER_Pos)                 /*!< 0x00000008 */
#define RCC_PLL2CSGR_MOD_PER_4                    (0x10U << RCC_PLL2CSGR_MOD_PER_Pos)                /*!< 0x00000010 */
#define RCC_PLL2CSGR_MOD_PER_5                    (0x20U << RCC_PLL2CSGR_MOD_PER_Pos)                /*!< 0x00000020 */
#define RCC_PLL2CSGR_MOD_PER_6                    (0x40U << RCC_PLL2CSGR_MOD_PER_Pos)                /*!< 0x00000040 */
#define RCC_PLL2CSGR_MOD_PER_7                    (0x80U << RCC_PLL2CSGR_MOD_PER_Pos)                /*!< 0x00000080 */
#define RCC_PLL2CSGR_MOD_PER_8                    (0x100U << RCC_PLL2CSGR_MOD_PER_Pos)               /*!< 0x00000100 */
#define RCC_PLL2CSGR_MOD_PER_9                    (0x200U << RCC_PLL2CSGR_MOD_PER_Pos)               /*!< 0x00000200 */
#define RCC_PLL2CSGR_MOD_PER_10                   (0x400U << RCC_PLL2CSGR_MOD_PER_Pos)               /*!< 0x00000400 */
#define RCC_PLL2CSGR_MOD_PER_11                   (0x800U << RCC_PLL2CSGR_MOD_PER_Pos)               /*!< 0x00000800 */
#define RCC_PLL2CSGR_MOD_PER_12                   (0x1000U << RCC_PLL2CSGR_MOD_PER_Pos)              /*!< 0x00001000 */
#define RCC_PLL2CSGR_TPDFN_DIS_Pos                (13U)
#define RCC_PLL2CSGR_TPDFN_DIS_Msk                (0x1U << RCC_PLL2CSGR_TPDFN_DIS_Pos)               /*!< 0x00002000 */
#define RCC_PLL2CSGR_TPDFN_DIS                    RCC_PLL2CSGR_TPDFN_DIS_Msk                         /*!< Dithering TPDF noise control */
#define RCC_PLL2CSGR_RPDFN_DIS_Pos                (14U)
#define RCC_PLL2CSGR_RPDFN_DIS_Msk                (0x1U << RCC_PLL2CSGR_RPDFN_DIS_Pos)               /*!< 0x00004000 */
#define RCC_PLL2CSGR_RPDFN_DIS                    RCC_PLL2CSGR_RPDFN_DIS_Msk                         /*!< Dithering RPDF noise control */
#define RCC_PLL2CSGR_SSCG_MODE_Pos                (15U)
#define RCC_PLL2CSGR_SSCG_MODE_Msk                (0x1U << RCC_PLL2CSGR_SSCG_MODE_Pos)               /*!< 0x00008000 */
#define RCC_PLL2CSGR_SSCG_MODE                    RCC_PLL2CSGR_SSCG_MODE_Msk                         /*!< Spread spectrum clock generator mode */
#define RCC_PLL2CSGR_INC_STEP_Pos                 (16U)
#define RCC_PLL2CSGR_INC_STEP_Msk                 (0x7FFFU << RCC_PLL2CSGR_INC_STEP_Pos)             /*!< 0x7FFF0000 */
#define RCC_PLL2CSGR_INC_STEP                     RCC_PLL2CSGR_INC_STEP_Msk                          /*!< Modulation Depth Adjustment for PLL2 */
#define RCC_PLL2CSGR_INC_STEP_0                   (0x1U << RCC_PLL2CSGR_INC_STEP_Pos)            /*!< 0x00010000 */
#define RCC_PLL2CSGR_INC_STEP_1                   (0x2U << RCC_PLL2CSGR_INC_STEP_Pos)            /*!< 0x00020000 */
#define RCC_PLL2CSGR_INC_STEP_2                   (0x4U << RCC_PLL2CSGR_INC_STEP_Pos)            /*!< 0x00040000 */
#define RCC_PLL2CSGR_INC_STEP_3                   (0x8U << RCC_PLL2CSGR_INC_STEP_Pos)            /*!< 0x00080000 */
#define RCC_PLL2CSGR_INC_STEP_4                   (0x10U << RCC_PLL2CSGR_INC_STEP_Pos)           /*!< 0x00100000 */
#define RCC_PLL2CSGR_INC_STEP_5                   (0x20U << RCC_PLL2CSGR_INC_STEP_Pos)           /*!< 0x00200000 */
#define RCC_PLL2CSGR_INC_STEP_6                   (0x40U << RCC_PLL2CSGR_INC_STEP_Pos)           /*!< 0x00400000 */
#define RCC_PLL2CSGR_INC_STEP_7                   (0x80U << RCC_PLL2CSGR_INC_STEP_Pos)           /*!< 0x00800000 */
#define RCC_PLL2CSGR_INC_STEP_8                   (0x100U << RCC_PLL2CSGR_INC_STEP_Pos)          /*!< 0x01000000 */
#define RCC_PLL2CSGR_INC_STEP_9                   (0x200U << RCC_PLL2CSGR_INC_STEP_Pos)          /*!< 0x02000000 */
#define RCC_PLL2CSGR_INC_STEP_10                  (0x400U << RCC_PLL2CSGR_INC_STEP_Pos)          /*!< 0x04000000 */
#define RCC_PLL2CSGR_INC_STEP_11                  (0x800U << RCC_PLL2CSGR_INC_STEP_Pos)          /*!< 0x08000000 */
#define RCC_PLL2CSGR_INC_STEP_12                  (0x1000U << RCC_PLL2CSGR_INC_STEP_Pos)         /*!< 0x10000000 */
#define RCC_PLL2CSGR_INC_STEP_13                  (0x2000U << RCC_PLL2CSGR_INC_STEP_Pos)         /*!< 0x20000000 */
#define RCC_PLL2CSGR_INC_STEP_14                  (0x4000U << RCC_PLL2CSGR_INC_STEP_Pos)         /*!< 0x40000000 */

/***************  Bit definition for RCC_I2C46CKSELR register  ****************/
#define RCC_I2C46CKSELR_I2C46SRC_Pos              (0U)
#define RCC_I2C46CKSELR_I2C46SRC_Msk              (0x7U << RCC_I2C46CKSELR_I2C46SRC_Pos)             /*!< 0x00000007 */
#define RCC_I2C46CKSELR_I2C46SRC                  RCC_I2C46CKSELR_I2C46SRC_Msk                       /*!< I2C4 and I2C6 kernel clock source selection */
#define RCC_I2C46CKSELR_I2C46SRC_0                (0x1U << RCC_I2C46CKSELR_I2C46SRC_Pos)             /*!< 0x00000001 */
#define RCC_I2C46CKSELR_I2C46SRC_1                (0x2U << RCC_I2C46CKSELR_I2C46SRC_Pos)             /*!< 0x00000002 */
#define RCC_I2C46CKSELR_I2C46SRC_2                (0x4U << RCC_I2C46CKSELR_I2C46SRC_Pos)             /*!< 0x00000004 */

/****************  Bit definition for RCC_SPI6CKSELR register  ****************/
#define RCC_SPI6CKSELR_SPI6SRC_Pos                (0U)
#define RCC_SPI6CKSELR_SPI6SRC_Msk                (0x7U << RCC_SPI6CKSELR_SPI6SRC_Pos)               /*!< 0x00000007 */
#define RCC_SPI6CKSELR_SPI6SRC                    RCC_SPI6CKSELR_SPI6SRC_Msk                         /*!< SPI6 kernel clock source selection */
#define RCC_SPI6CKSELR_SPI6SRC_0                  (0x1U << RCC_SPI6CKSELR_SPI6SRC_Pos)               /*!< 0x00000001 */
#define RCC_SPI6CKSELR_SPI6SRC_1                  (0x2U << RCC_SPI6CKSELR_SPI6SRC_Pos)               /*!< 0x00000002 */
#define RCC_SPI6CKSELR_SPI6SRC_2                  (0x4U << RCC_SPI6CKSELR_SPI6SRC_Pos)               /*!< 0x00000004 */

/***************  Bit definition for RCC_UART1CKSELR register  ****************/
#define RCC_UART1CKSELR_UART1SRC_Pos              (0U)
#define RCC_UART1CKSELR_UART1SRC_Msk              (0x7U << RCC_UART1CKSELR_UART1SRC_Pos)             /*!< 0x00000007 */
#define RCC_UART1CKSELR_UART1SRC                  RCC_UART1CKSELR_UART1SRC_Msk                       /*!< UART1 kernel clock source selection */
#define RCC_UART1CKSELR_UART1SRC_0                (0x1U << RCC_UART1CKSELR_UART1SRC_Pos)             /*!< 0x00000001 */
#define RCC_UART1CKSELR_UART1SRC_1                (0x2U << RCC_UART1CKSELR_UART1SRC_Pos)             /*!< 0x00000002 */
#define RCC_UART1CKSELR_UART1SRC_2                (0x4U << RCC_UART1CKSELR_UART1SRC_Pos)             /*!< 0x00000004 */

/****************  Bit definition for RCC_RNG1CKSELR register  ****************/
#define RCC_RNG1CKSELR_RNG1SRC_Pos                (0U)
#define RCC_RNG1CKSELR_RNG1SRC_Msk                (0x3U << RCC_RNG1CKSELR_RNG1SRC_Pos)               /*!< 0x00000003 */
#define RCC_RNG1CKSELR_RNG1SRC                    RCC_RNG1CKSELR_RNG1SRC_Msk                         /*!< RNG1 kernel clock source selection */
#define RCC_RNG1CKSELR_RNG1SRC_0                  (0x1U << RCC_RNG1CKSELR_RNG1SRC_Pos)               /*!< 0x00000001 */
#define RCC_RNG1CKSELR_RNG1SRC_1                  (0x2U << RCC_RNG1CKSELR_RNG1SRC_Pos)               /*!< 0x00000002 */

/****************  Bit definition for RCC_CPERCKSELR register  ****************/
#define RCC_CPERCKSELR_CKPERSRC_Pos               (0U)
#define RCC_CPERCKSELR_CKPERSRC_Msk               (0x3U << RCC_CPERCKSELR_CKPERSRC_Pos)              /*!< 0x00000003 */
#define RCC_CPERCKSELR_CKPERSRC                   RCC_CPERCKSELR_CKPERSRC_Msk                        /*!< Oscillator selection for kernel clock */
#define RCC_CPERCKSELR_CKPERSRC_0                 (0x1U << RCC_CPERCKSELR_CKPERSRC_Pos)              /*!< 0x00000001 */
#define RCC_CPERCKSELR_CKPERSRC_1                 (0x2U << RCC_CPERCKSELR_CKPERSRC_Pos)              /*!< 0x00000002 */

/***************  Bit definition for RCC_STGENCKSELR register  ****************/
#define RCC_STGENCKSELR_STGENSRC_Pos              (0U)
#define RCC_STGENCKSELR_STGENSRC_Msk              (0x3U << RCC_STGENCKSELR_STGENSRC_Pos)             /*!< 0x00000003 */
#define RCC_STGENCKSELR_STGENSRC                  RCC_STGENCKSELR_STGENSRC_Msk                       /*!< Oscillator selection for kernel clock */
#define RCC_STGENCKSELR_STGENSRC_0                (0x1U << RCC_STGENCKSELR_STGENSRC_Pos)             /*!< 0x00000001 */
#define RCC_STGENCKSELR_STGENSRC_1                (0x2U << RCC_STGENCKSELR_STGENSRC_Pos)             /*!< 0x00000002 */

/*****************  Bit definition for RCC_DDRITFCR register  *****************/
#define RCC_DDRITFCR_DDRC1EN_Pos                  (0U)
#define RCC_DDRITFCR_DDRC1EN_Msk                  (0x1U << RCC_DDRITFCR_DDRC1EN_Pos)                 /*!< 0x00000001 */
#define RCC_DDRITFCR_DDRC1EN                      RCC_DDRITFCR_DDRC1EN_Msk                           /*!< DDRC port 1 peripheral clocks enable */
#define RCC_DDRITFCR_DDRC1LPEN_Pos                (1U)
#define RCC_DDRITFCR_DDRC1LPEN_Msk                (0x1U << RCC_DDRITFCR_DDRC1LPEN_Pos)               /*!< 0x00000002 */
#define RCC_DDRITFCR_DDRC1LPEN                    RCC_DDRITFCR_DDRC1LPEN_Msk                         /*!< DDRC port 1 peripheral clocks enable during CSleep mode */
#define RCC_DDRITFCR_DDRC2EN_Pos                  (2U)
#define RCC_DDRITFCR_DDRC2EN_Msk                  (0x1U << RCC_DDRITFCR_DDRC2EN_Pos)                 /*!< 0x00000004 */
#define RCC_DDRITFCR_DDRC2EN                      RCC_DDRITFCR_DDRC2EN_Msk                           /*!< DDRC port 2 peripheral clocks enable */
#define RCC_DDRITFCR_DDRC2LPEN_Pos                (3U)
#define RCC_DDRITFCR_DDRC2LPEN_Msk                (0x1U << RCC_DDRITFCR_DDRC2LPEN_Pos)               /*!< 0x00000008 */
#define RCC_DDRITFCR_DDRC2LPEN                    RCC_DDRITFCR_DDRC2LPEN_Msk                         /*!< DDRC port 2 peripheral clocks enable during CSleep mode */
#define RCC_DDRITFCR_DDRPHYCEN_Pos                (4U)
#define RCC_DDRITFCR_DDRPHYCEN_Msk                (0x1U << RCC_DDRITFCR_DDRPHYCEN_Pos)               /*!< 0x00000010 */
#define RCC_DDRITFCR_DDRPHYCEN                    RCC_DDRITFCR_DDRPHYCEN_Msk                         /*!< DDRPHYC peripheral clocks enable */
#define RCC_DDRITFCR_DDRPHYCLPEN_Pos              (5U)
#define RCC_DDRITFCR_DDRPHYCLPEN_Msk              (0x1U << RCC_DDRITFCR_DDRPHYCLPEN_Pos)             /*!< 0x00000020 */
#define RCC_DDRITFCR_DDRPHYCLPEN                  RCC_DDRITFCR_DDRPHYCLPEN_Msk                       /*!< DDRPHYC peripheral clocks enable during CSleep mode */
#define RCC_DDRITFCR_DDRCAPBEN_Pos                (6U)
#define RCC_DDRITFCR_DDRCAPBEN_Msk                (0x1U << RCC_DDRITFCR_DDRCAPBEN_Pos)               /*!< 0x00000040 */
#define RCC_DDRITFCR_DDRCAPBEN                    RCC_DDRITFCR_DDRCAPBEN_Msk                         /*!< DDRC APB clock enable */
#define RCC_DDRITFCR_DDRCAPBLPEN_Pos              (7U)
#define RCC_DDRITFCR_DDRCAPBLPEN_Msk              (0x1U << RCC_DDRITFCR_DDRCAPBLPEN_Pos)             /*!< 0x00000080 */
#define RCC_DDRITFCR_DDRCAPBLPEN                  RCC_DDRITFCR_DDRCAPBLPEN_Msk                       /*!< DDRC APB clock enable during CSleep mode */
#define RCC_DDRITFCR_AXIDCGEN_Pos                 (8U)
#define RCC_DDRITFCR_AXIDCGEN_Msk                 (0x1U << RCC_DDRITFCR_AXIDCGEN_Pos)                /*!< 0x00000100 */
#define RCC_DDRITFCR_AXIDCGEN                     RCC_DDRITFCR_AXIDCGEN_Msk                          /*!< AXIDCG enable during MPU CRun mode */
#define RCC_DDRITFCR_DDRPHYCAPBEN_Pos             (9U)
#define RCC_DDRITFCR_DDRPHYCAPBEN_Msk             (0x1U << RCC_DDRITFCR_DDRPHYCAPBEN_Pos)            /*!< 0x00000200 */
#define RCC_DDRITFCR_DDRPHYCAPBEN                 RCC_DDRITFCR_DDRPHYCAPBEN_Msk                      /*!< DDRPHYC APB clock enable */
#define RCC_DDRITFCR_DDRPHYCAPBLPEN_Pos           (10U)
#define RCC_DDRITFCR_DDRPHYCAPBLPEN_Msk           (0x1U << RCC_DDRITFCR_DDRPHYCAPBLPEN_Pos)          /*!< 0x00000400 */
#define RCC_DDRITFCR_DDRPHYCAPBLPEN               RCC_DDRITFCR_DDRPHYCAPBLPEN_Msk                    /*!< DDRPHYC APB clock enable during CSleep mode */
#define RCC_DDRITFCR_KERDCG_DLY_Pos               (11U)
#define RCC_DDRITFCR_KERDCG_DLY_Msk               (0x7U << RCC_DDRITFCR_KERDCG_DLY_Pos)              /*!< 0x00003800 */
#define RCC_DDRITFCR_KERDCG_DLY                   RCC_DDRITFCR_KERDCG_DLY_Msk                        /*!< AXIDCG delay */
#define RCC_DDRITFCR_KERDCG_DLY_0                 (0x1U << RCC_DDRITFCR_KERDCG_DLY_Pos)            /*!< 0x00000800 */
#define RCC_DDRITFCR_KERDCG_DLY_1                 (0x2U << RCC_DDRITFCR_KERDCG_DLY_Pos)           /*!< 0x00001000 */
#define RCC_DDRITFCR_KERDCG_DLY_2                 (0x4U << RCC_DDRITFCR_KERDCG_DLY_Pos)           /*!< 0x00002000 */
#define RCC_DDRITFCR_DDRCAPBRST_Pos               (14U)
#define RCC_DDRITFCR_DDRCAPBRST_Msk               (0x1U << RCC_DDRITFCR_DDRCAPBRST_Pos)              /*!< 0x00004000 */
#define RCC_DDRITFCR_DDRCAPBRST                   RCC_DDRITFCR_DDRCAPBRST_Msk                        /*!< DDRC APB interface reset */
#define RCC_DDRITFCR_DDRCAXIRST_Pos               (15U)
#define RCC_DDRITFCR_DDRCAXIRST_Msk               (0x1U << RCC_DDRITFCR_DDRCAXIRST_Pos)              /*!< 0x00008000 */
#define RCC_DDRITFCR_DDRCAXIRST                   RCC_DDRITFCR_DDRCAXIRST_Msk                        /*!< DDRC AXI interface reset */
#define RCC_DDRITFCR_DDRCORERST_Pos               (16U)
#define RCC_DDRITFCR_DDRCORERST_Msk               (0x1U << RCC_DDRITFCR_DDRCORERST_Pos)              /*!< 0x00010000 */
#define RCC_DDRITFCR_DDRCORERST                   RCC_DDRITFCR_DDRCORERST_Msk                        /*!< DDRC core reset */
#define RCC_DDRITFCR_DPHYAPBRST_Pos               (17U)
#define RCC_DDRITFCR_DPHYAPBRST_Msk               (0x1U << RCC_DDRITFCR_DPHYAPBRST_Pos)              /*!< 0x00020000 */
#define RCC_DDRITFCR_DPHYAPBRST                   RCC_DDRITFCR_DPHYAPBRST_Msk                        /*!< DDRPHYC APB interface reset */
#define RCC_DDRITFCR_DPHYRST_Pos                  (18U)
#define RCC_DDRITFCR_DPHYRST_Msk                  (0x1U << RCC_DDRITFCR_DPHYRST_Pos)                 /*!< 0x00040000 */
#define RCC_DDRITFCR_DPHYRST                      RCC_DDRITFCR_DPHYRST_Msk                           /*!< DDRPHYC reset */
#define RCC_DDRITFCR_DPHYCTLRST_Pos               (19U)
#define RCC_DDRITFCR_DPHYCTLRST_Msk               (0x1U << RCC_DDRITFCR_DPHYCTLRST_Pos)              /*!< 0x00080000 */
#define RCC_DDRITFCR_DPHYCTLRST                   RCC_DDRITFCR_DPHYCTLRST_Msk                        /*!< DDRPHYC Control reset */
#define RCC_DDRITFCR_DDRCKMOD_Pos                 (20U)
#define RCC_DDRITFCR_DDRCKMOD_Msk                 (0x7U << RCC_DDRITFCR_DDRCKMOD_Pos)                /*!< 0x00700000 */
#define RCC_DDRITFCR_DDRCKMOD                     RCC_DDRITFCR_DDRCKMOD_Msk                          /*!< RCC mode for DDR clock control */
#define RCC_DDRITFCR_DDRCKMOD_0                   (0x1U << RCC_DDRITFCR_DDRCKMOD_Pos)           /*!< 0x00100000 */
#define RCC_DDRITFCR_DDRCKMOD_1                   (0x2U << RCC_DDRITFCR_DDRCKMOD_Pos)           /*!< 0x00200000 */
#define RCC_DDRITFCR_DDRCKMOD_2                   (0x4U << RCC_DDRITFCR_DDRCKMOD_Pos)           /*!< 0x00400000 */
#define RCC_DDRITFCR_GSKPMOD_Pos                  (23U)
#define RCC_DDRITFCR_GSKPMOD_Msk                  (0x1U << RCC_DDRITFCR_GSKPMOD_Pos)                 /*!< 0x00800000 */
#define RCC_DDRITFCR_GSKPMOD                      RCC_DDRITFCR_GSKPMOD_Msk                           /*!< Glitch Skipper (GSKP) Mode */
#define RCC_DDRITFCR_GSKPCTRL_Pos                 (24U)
#define RCC_DDRITFCR_GSKPCTRL_Msk                 (0x1U << RCC_DDRITFCR_GSKPCTRL_Pos)                /*!< 0x01000000 */
#define RCC_DDRITFCR_GSKPCTRL                     RCC_DDRITFCR_GSKPCTRL_Msk                          /*!< Glitch Skipper (GSKP) control */
#define RCC_DDRITFCR_DFILP_WIDTH_Pos              (25U)
#define RCC_DDRITFCR_DFILP_WIDTH_Msk              (0x7U << RCC_DDRITFCR_DFILP_WIDTH_Pos)             /*!< 0x0E000000 */
#define RCC_DDRITFCR_DFILP_WIDTH                  RCC_DDRITFCR_DFILP_WIDTH_Msk                       /*!< Minimum duration of low-power request command */
#define RCC_DDRITFCR_DFILP_WIDTH_0                (0x1U << RCC_DDRITFCR_DFILP_WIDTH_Pos)       /*!< 0x02000000 */
#define RCC_DDRITFCR_DFILP_WIDTH_1                (0x2U << RCC_DDRITFCR_DFILP_WIDTH_Pos)       /*!< 0x04000000 */
#define RCC_DDRITFCR_DFILP_WIDTH_2                (0x4U << RCC_DDRITFCR_DFILP_WIDTH_Pos)       /*!< 0x08000000 */
#define RCC_DDRITFCR_GSKP_DUR_Pos                 (28U)
#define RCC_DDRITFCR_GSKP_DUR_Msk                 (0xFU << RCC_DDRITFCR_GSKP_DUR_Pos)                /*!< 0xF0000000 */
#define RCC_DDRITFCR_GSKP_DUR                     RCC_DDRITFCR_GSKP_DUR_Msk                          /*!< Glitch skipper duration in automatic mode */
#define RCC_DDRITFCR_GSKP_DUR_0                   (0x1U << RCC_DDRITFCR_GSKP_DUR_Pos)         /*!< 0x10000000 */
#define RCC_DDRITFCR_GSKP_DUR_1                   (0x2U << RCC_DDRITFCR_GSKP_DUR_Pos)         /*!< 0x20000000 */
#define RCC_DDRITFCR_GSKP_DUR_2                   (0x4U << RCC_DDRITFCR_GSKP_DUR_Pos)         /*!< 0x40000000 */
#define RCC_DDRITFCR_GSKP_DUR_3                   (0x8U << RCC_DDRITFCR_GSKP_DUR_Pos)         /*!< 0x80000000 */

/****************  Bit definition for RCC_MP_BOOTCR register  *****************/
#define RCC_MP_BOOTCR_MCU_BEN_Pos                 (0U)
#define RCC_MP_BOOTCR_MCU_BEN_Msk                 (0x1U << RCC_MP_BOOTCR_MCU_BEN_Pos)                /*!< 0x00000001 */
#define RCC_MP_BOOTCR_MCU_BEN                     RCC_MP_BOOTCR_MCU_BEN_Msk                          /*!< MCU Boot Enable after Standby */
#define RCC_MP_BOOTCR_MPU_BEN_Pos                 (1U)
#define RCC_MP_BOOTCR_MPU_BEN_Msk                 (0x1U << RCC_MP_BOOTCR_MPU_BEN_Pos)                /*!< 0x00000002 */
#define RCC_MP_BOOTCR_MPU_BEN                     RCC_MP_BOOTCR_MPU_BEN_Msk                          /*!< MPU Boot Enable after Standby */

/***************  Bit definition for RCC_MP_SREQSETR register  ****************/
#define RCC_MP_SREQSETR_STPREQ_P0_Pos             (0U)
#define RCC_MP_SREQSETR_STPREQ_P0_Msk             (0x1U << RCC_MP_SREQSETR_STPREQ_P0_Pos)            /*!< 0x00000001 */
#define RCC_MP_SREQSETR_STPREQ_P0                 RCC_MP_SREQSETR_STPREQ_P0_Msk                      /*!< Stop Request for MPU processor number 0 */
#define RCC_MP_SREQSETR_STPREQ_P1_Pos             (1U)
#define RCC_MP_SREQSETR_STPREQ_P1_Msk             (0x1U << RCC_MP_SREQSETR_STPREQ_P1_Pos)            /*!< 0x00000002 */
#define RCC_MP_SREQSETR_STPREQ_P1                 RCC_MP_SREQSETR_STPREQ_P1_Msk                      /*!< Stop Request for MPU processor number 1 */

/***************  Bit definition for RCC_MP_SREQCLRR register  ****************/
#define RCC_MP_SREQCLRR_STPREQ_P0_Pos             (0U)
#define RCC_MP_SREQCLRR_STPREQ_P0_Msk             (0x1U << RCC_MP_SREQCLRR_STPREQ_P0_Pos)            /*!< 0x00000001 */
#define RCC_MP_SREQCLRR_STPREQ_P0                 RCC_MP_SREQCLRR_STPREQ_P0_Msk                      /*!< Stop Request for MPU processor number 0 */
#define RCC_MP_SREQCLRR_STPREQ_P1_Pos             (1U)
#define RCC_MP_SREQCLRR_STPREQ_P1_Msk             (0x1U << RCC_MP_SREQCLRR_STPREQ_P1_Pos)            /*!< 0x00000002 */
#define RCC_MP_SREQCLRR_STPREQ_P1                 RCC_MP_SREQCLRR_STPREQ_P1_Msk                      /*!< Stop Request for MPU processor number 1 */

/******************  Bit definition for RCC_MP_GCR register  ******************/
#define RCC_MP_GCR_BOOT_MCU_Pos                   (0U)
#define RCC_MP_GCR_BOOT_MCU_Msk                   (0x1U << RCC_MP_GCR_BOOT_MCU_Pos)                  /*!< 0x00000001 */
#define RCC_MP_GCR_BOOT_MCU                       RCC_MP_GCR_BOOT_MCU_Msk                            /*!< Allows the MCU to boot */

/****************  Bit definition for RCC_MP_APRSTCR register  ****************/
#define RCC_MP_APRSTCR_RDCTLEN_Pos                (0U)
#define RCC_MP_APRSTCR_RDCTLEN_Msk                (0x1U << RCC_MP_APRSTCR_RDCTLEN_Pos)               /*!< 0x00000001 */
#define RCC_MP_APRSTCR_RDCTLEN                    RCC_MP_APRSTCR_RDCTLEN_Msk                         /*!< Reset Delay Control Enable */
#define RCC_MP_APRSTCR_RSTTO_Pos                  (8U)
#define RCC_MP_APRSTCR_RSTTO_Msk                  (0x7FU << RCC_MP_APRSTCR_RSTTO_Pos)                /*!< 0x00007F00 */
#define RCC_MP_APRSTCR_RSTTO                      RCC_MP_APRSTCR_RSTTO_Msk                           /*!< Reset Timeout Delay Adjust */
#define RCC_MP_APRSTCR_RSTTO_0                    (0x1U << RCC_MP_APRSTCR_RSTTO_Pos)               /*!< 0x00000100 */
#define RCC_MP_APRSTCR_RSTTO_1                    (0x2U << RCC_MP_APRSTCR_RSTTO_Pos)               /*!< 0x00000200 */
#define RCC_MP_APRSTCR_RSTTO_2                    (0x4U << RCC_MP_APRSTCR_RSTTO_Pos)               /*!< 0x00000400 */
#define RCC_MP_APRSTCR_RSTTO_3                    (0x8U << RCC_MP_APRSTCR_RSTTO_Pos)               /*!< 0x00000800 */
#define RCC_MP_APRSTCR_RSTTO_4                    (0x10U << RCC_MP_APRSTCR_RSTTO_Pos)              /*!< 0x00001000 */
#define RCC_MP_APRSTCR_RSTTO_5                    (0x20U << RCC_MP_APRSTCR_RSTTO_Pos)              /*!< 0x00002000 */
#define RCC_MP_APRSTCR_RSTTO_6                    (0x40U << RCC_MP_APRSTCR_RSTTO_Pos)              /*!< 0x00004000 */

/****************  Bit definition for RCC_MP_APRSTSR register  ****************/
#define RCC_MP_APRSTSR_RSTTOV_Pos                 (8U)
#define RCC_MP_APRSTSR_RSTTOV_Msk                 (0x7FU << RCC_MP_APRSTSR_RSTTOV_Pos)               /*!< 0x00007F00 */
#define RCC_MP_APRSTSR_RSTTOV                     RCC_MP_APRSTSR_RSTTOV_Msk                          /*!< Reset Timeout Delay Value */
#define RCC_MP_APRSTSR_RSTTOV_0                   (0x1U << RCC_MP_APRSTSR_RSTTOV_Pos)              /*!< 0x00000100 */
#define RCC_MP_APRSTSR_RSTTOV_1                   (0x2U << RCC_MP_APRSTSR_RSTTOV_Pos)              /*!< 0x00000200 */
#define RCC_MP_APRSTSR_RSTTOV_2                   (0x4U << RCC_MP_APRSTSR_RSTTOV_Pos)              /*!< 0x00000400 */
#define RCC_MP_APRSTSR_RSTTOV_3                   (0x8U << RCC_MP_APRSTSR_RSTTOV_Pos)              /*!< 0x00000800 */
#define RCC_MP_APRSTSR_RSTTOV_4                   (0x10U << RCC_MP_APRSTSR_RSTTOV_Pos)             /*!< 0x00001000 */
#define RCC_MP_APRSTSR_RSTTOV_5                   (0x20U << RCC_MP_APRSTSR_RSTTOV_Pos)             /*!< 0x00002000 */
#define RCC_MP_APRSTSR_RSTTOV_6                   (0x40U << RCC_MP_APRSTSR_RSTTOV_Pos)             /*!< 0x00004000 */

/*******************  Bit definition for RCC_BDCR register  *******************/
#define RCC_BDCR_LSEON_Pos                        (0U)
#define RCC_BDCR_LSEON_Msk                        (0x1U << RCC_BDCR_LSEON_Pos)                       /*!< 0x00000001 */
#define RCC_BDCR_LSEON                            RCC_BDCR_LSEON_Msk                                 /*!< LSE oscillator enabled */
#define RCC_BDCR_LSEBYP_Pos                       (1U)
#define RCC_BDCR_LSEBYP_Msk                       (0x1U << RCC_BDCR_LSEBYP_Pos)                      /*!< 0x00000002 */
#define RCC_BDCR_LSEBYP                           RCC_BDCR_LSEBYP_Msk                                /*!< LSE oscillator bypass */
#define RCC_BDCR_LSERDY_Pos                       (2U)
#define RCC_BDCR_LSERDY_Msk                       (0x1U << RCC_BDCR_LSERDY_Pos)                      /*!< 0x00000004 */
#define RCC_BDCR_LSERDY                           RCC_BDCR_LSERDY_Msk                                /*!< LSE oscillator ready */
#define RCC_BDCR_DIGBYP_Pos                       (3U)
#define RCC_BDCR_DIGBYP_Msk                       (0x1U << RCC_BDCR_DIGBYP_Pos)                      /*!< 0x00000008 */
#define RCC_BDCR_DIGBYP                           RCC_BDCR_DIGBYP_Msk                                /*!< LSE digital bypass */
#define RCC_BDCR_LSEDRV_Pos                       (4U)
#define RCC_BDCR_LSEDRV_Msk                       (0x3U << RCC_BDCR_LSEDRV_Pos)                      /*!< 0x00000030 */
#define RCC_BDCR_LSEDRV                           RCC_BDCR_LSEDRV_Msk                                /*!< LSE oscillator driving capability */
#define RCC_BDCR_LSEDRV_0                         (0x1U << RCC_BDCR_LSEDRV_Pos)                     /*!< 0x00000010 */
#define RCC_BDCR_LSEDRV_1                         (0x2U << RCC_BDCR_LSEDRV_Pos)                     /*!< 0x00000020 */
#define RCC_BDCR_LSECSSON_Pos                     (8U)
#define RCC_BDCR_LSECSSON_Msk                     (0x1U << RCC_BDCR_LSECSSON_Pos)                    /*!< 0x00000100 */
#define RCC_BDCR_LSECSSON                         RCC_BDCR_LSECSSON_Msk                              /*!< LSE clock security system enable */
#define RCC_BDCR_LSECSSD_Pos                      (9U)
#define RCC_BDCR_LSECSSD_Msk                      (0x1U << RCC_BDCR_LSECSSD_Pos)                     /*!< 0x00000200 */
#define RCC_BDCR_LSECSSD                          RCC_BDCR_LSECSSD_Msk                               /*!< LSE clock security system failure detection */
#define RCC_BDCR_RTCSRC_Pos                       (16U)
#define RCC_BDCR_RTCSRC_Msk                       (0x3U << RCC_BDCR_RTCSRC_Pos)                      /*!< 0x00030000 */
#define RCC_BDCR_RTCSRC                           RCC_BDCR_RTCSRC_Msk                                /*!< RTC clock source selection */
#define RCC_BDCR_RTCSRC_0                         (0x1U << RCC_BDCR_RTCSRC_Pos)                  /*!< 0x00010000 */
#define RCC_BDCR_RTCSRC_1                         (0x2U << RCC_BDCR_RTCSRC_Pos)                  /*!< 0x00020000 */
#define RCC_BDCR_RTCCKEN_Pos                      (20U)
#define RCC_BDCR_RTCCKEN_Msk                      (0x1U << RCC_BDCR_RTCCKEN_Pos)                     /*!< 0x00100000 */
#define RCC_BDCR_RTCCKEN                          RCC_BDCR_RTCCKEN_Msk                               /*!< RTC clock enable */
#define RCC_BDCR_VSWRST_Pos                       (31U)
#define RCC_BDCR_VSWRST_Msk                       (0x1U << RCC_BDCR_VSWRST_Pos)                      /*!< 0x80000000 */
#define RCC_BDCR_VSWRST                           RCC_BDCR_VSWRST_Msk                                /*!< V Switch domain software reset */

/*****************  Bit definition for RCC_RDLSICR register  ******************/
#define RCC_RDLSICR_LSION_Pos                     (0U)
#define RCC_RDLSICR_LSION_Msk                     (0x1U << RCC_RDLSICR_LSION_Pos)                    /*!< 0x00000001 */
#define RCC_RDLSICR_LSION                         RCC_RDLSICR_LSION_Msk                              /*!< LSI oscillator enabled */
#define RCC_RDLSICR_LSIRDY_Pos                    (1U)
#define RCC_RDLSICR_LSIRDY_Msk                    (0x1U << RCC_RDLSICR_LSIRDY_Pos)                   /*!< 0x00000002 */
#define RCC_RDLSICR_LSIRDY                        RCC_RDLSICR_LSIRDY_Msk                             /*!< LSI oscillator ready */
#define RCC_RDLSICR_MRD_Pos                       (16U)
#define RCC_RDLSICR_MRD_Msk                       (0x1FU << RCC_RDLSICR_MRD_Pos)                     /*!< 0x001F0000 */
#define RCC_RDLSICR_MRD                           RCC_RDLSICR_MRD_Msk                                /*!< Minimum Reset Duration */
#define RCC_RDLSICR_MRD_0                         (0x1U << RCC_RDLSICR_MRD_Pos)                  /*!< 0x00010000 */
#define RCC_RDLSICR_MRD_1                         (0x2U << RCC_RDLSICR_MRD_Pos)                  /*!< 0x00020000 */
#define RCC_RDLSICR_MRD_2                         (0x4U << RCC_RDLSICR_MRD_Pos)                  /*!< 0x00040000 */
#define RCC_RDLSICR_MRD_3                         (0x8U << RCC_RDLSICR_MRD_Pos)                  /*!< 0x00080000 */
#define RCC_RDLSICR_MRD_4                         (0x10U << RCC_RDLSICR_MRD_Pos)                 /*!< 0x00100000 */
#define RCC_RDLSICR_EADLY_Pos                     (24U)
#define RCC_RDLSICR_EADLY_Msk                     (0x7U << RCC_RDLSICR_EADLY_Pos)                    /*!< 0x07000000 */
#define RCC_RDLSICR_EADLY                         RCC_RDLSICR_EADLY_Msk                              /*!< External access delays */
#define RCC_RDLSICR_EADLY_0                       (0x1U << RCC_RDLSICR_EADLY_Pos)              /*!< 0x01000000 */
#define RCC_RDLSICR_EADLY_1                       (0x2U << RCC_RDLSICR_EADLY_Pos)              /*!< 0x02000000 */
#define RCC_RDLSICR_EADLY_2                       (0x4U << RCC_RDLSICR_EADLY_Pos)              /*!< 0x04000000 */
#define RCC_RDLSICR_SPARE_Pos                     (27U)
#define RCC_RDLSICR_SPARE_Msk                     (0x1FU << RCC_RDLSICR_SPARE_Pos)                   /*!< 0xF8000000 */
#define RCC_RDLSICR_SPARE                         RCC_RDLSICR_SPARE_Msk                              /*!< Spare bits */
#define RCC_RDLSICR_SPARE_0                       (0x1U << RCC_RDLSICR_SPARE_Pos)              /*!< 0x08000000 */
#define RCC_RDLSICR_SPARE_1                       (0x2U << RCC_RDLSICR_SPARE_Pos)             /*!< 0x10000000 */
#define RCC_RDLSICR_SPARE_2                       (0x4U << RCC_RDLSICR_SPARE_Pos)             /*!< 0x20000000 */
#define RCC_RDLSICR_SPARE_3                       (0x8U << RCC_RDLSICR_SPARE_Pos)             /*!< 0x40000000 */
#define RCC_RDLSICR_SPARE_4                       (0x10U << RCC_RDLSICR_SPARE_Pos)             /*!< 0x80000000 */

/***************  Bit definition for RCC_APB4RSTSETR register  ****************/
#define RCC_APB4RSTSETR_LTDCRST_Pos               (0U)
#define RCC_APB4RSTSETR_LTDCRST_Msk               (0x1U << RCC_APB4RSTSETR_LTDCRST_Pos)              /*!< 0x00000001 */
#define RCC_APB4RSTSETR_LTDCRST                   RCC_APB4RSTSETR_LTDCRST_Msk                        /*!< LTDC block reset */
#define RCC_APB4RSTSETR_DSIRST_Pos                (4U)
#define RCC_APB4RSTSETR_DSIRST_Msk                (0x1U << RCC_APB4RSTSETR_DSIRST_Pos)               /*!< 0x00000010 */
#define RCC_APB4RSTSETR_DSIRST                    RCC_APB4RSTSETR_DSIRST_Msk                         /*!< DSI block reset */
#define RCC_APB4RSTSETR_DDRPERFMRST_Pos           (8U)
#define RCC_APB4RSTSETR_DDRPERFMRST_Msk           (0x1U << RCC_APB4RSTSETR_DDRPERFMRST_Pos)          /*!< 0x00000100 */
#define RCC_APB4RSTSETR_DDRPERFMRST               RCC_APB4RSTSETR_DDRPERFMRST_Msk                    /*!< DDRPERFM block reset */
#define RCC_APB4RSTSETR_USBPHYRST_Pos             (16U)
#define RCC_APB4RSTSETR_USBPHYRST_Msk             (0x1U << RCC_APB4RSTSETR_USBPHYRST_Pos)            /*!< 0x00010000 */
#define RCC_APB4RSTSETR_USBPHYRST                 RCC_APB4RSTSETR_USBPHYRST_Msk                      /*!< USBPHYC block reset */

/***************  Bit definition for RCC_APB4RSTCLRR register  ****************/
#define RCC_APB4RSTCLRR_LTDCRST_Pos               (0U)
#define RCC_APB4RSTCLRR_LTDCRST_Msk               (0x1U << RCC_APB4RSTCLRR_LTDCRST_Pos)              /*!< 0x00000001 */
#define RCC_APB4RSTCLRR_LTDCRST                   RCC_APB4RSTCLRR_LTDCRST_Msk                        /*!< LTDC block reset */
#define RCC_APB4RSTCLRR_DSIRST_Pos                (4U)
#define RCC_APB4RSTCLRR_DSIRST_Msk                (0x1U << RCC_APB4RSTCLRR_DSIRST_Pos)               /*!< 0x00000010 */
#define RCC_APB4RSTCLRR_DSIRST                    RCC_APB4RSTCLRR_DSIRST_Msk                         /*!< DSI block reset */
#define RCC_APB4RSTCLRR_DDRPERFMRST_Pos           (8U)
#define RCC_APB4RSTCLRR_DDRPERFMRST_Msk           (0x1U << RCC_APB4RSTCLRR_DDRPERFMRST_Pos)          /*!< 0x00000100 */
#define RCC_APB4RSTCLRR_DDRPERFMRST               RCC_APB4RSTCLRR_DDRPERFMRST_Msk                    /*!< DDRPERFM block reset */
#define RCC_APB4RSTCLRR_USBPHYRST_Pos             (16U)
#define RCC_APB4RSTCLRR_USBPHYRST_Msk             (0x1U << RCC_APB4RSTCLRR_USBPHYRST_Pos)            /*!< 0x00010000 */
#define RCC_APB4RSTCLRR_USBPHYRST                 RCC_APB4RSTCLRR_USBPHYRST_Msk                      /*!< USBPHYC block reset */

/***************  Bit definition for RCC_APB5RSTSETR register  ****************/
#define RCC_APB5RSTSETR_SPI6RST_Pos               (0U)
#define RCC_APB5RSTSETR_SPI6RST_Msk               (0x1U << RCC_APB5RSTSETR_SPI6RST_Pos)              /*!< 0x00000001 */
#define RCC_APB5RSTSETR_SPI6RST                   RCC_APB5RSTSETR_SPI6RST_Msk                        /*!< SPI6 block reset */
#define RCC_APB5RSTSETR_I2C4RST_Pos               (2U)
#define RCC_APB5RSTSETR_I2C4RST_Msk               (0x1U << RCC_APB5RSTSETR_I2C4RST_Pos)              /*!< 0x00000004 */
#define RCC_APB5RSTSETR_I2C4RST                   RCC_APB5RSTSETR_I2C4RST_Msk                        /*!< I2C4 block reset */
#define RCC_APB5RSTSETR_I2C6RST_Pos               (3U)
#define RCC_APB5RSTSETR_I2C6RST_Msk               (0x1U << RCC_APB5RSTSETR_I2C6RST_Pos)              /*!< 0x00000008 */
#define RCC_APB5RSTSETR_I2C6RST                   RCC_APB5RSTSETR_I2C6RST_Msk                        /*!< I2C6 block reset */
#define RCC_APB5RSTSETR_USART1RST_Pos             (4U)
#define RCC_APB5RSTSETR_USART1RST_Msk             (0x1U << RCC_APB5RSTSETR_USART1RST_Pos)            /*!< 0x00000010 */
#define RCC_APB5RSTSETR_USART1RST                 RCC_APB5RSTSETR_USART1RST_Msk                      /*!< USART1 block reset */
#define RCC_APB5RSTSETR_STGENRST_Pos              (20U)
#define RCC_APB5RSTSETR_STGENRST_Msk              (0x1U << RCC_APB5RSTSETR_STGENRST_Pos)             /*!< 0x00100000 */
#define RCC_APB5RSTSETR_STGENRST                  RCC_APB5RSTSETR_STGENRST_Msk                       /*!< STGEN block reset */

/***************  Bit definition for RCC_APB5RSTCLRR register  ****************/
#define RCC_APB5RSTCLRR_SPI6RST_Pos               (0U)
#define RCC_APB5RSTCLRR_SPI6RST_Msk               (0x1U << RCC_APB5RSTCLRR_SPI6RST_Pos)              /*!< 0x00000001 */
#define RCC_APB5RSTCLRR_SPI6RST                   RCC_APB5RSTCLRR_SPI6RST_Msk                        /*!< SPI6 block reset */
#define RCC_APB5RSTCLRR_I2C4RST_Pos               (2U)
#define RCC_APB5RSTCLRR_I2C4RST_Msk               (0x1U << RCC_APB5RSTCLRR_I2C4RST_Pos)              /*!< 0x00000004 */
#define RCC_APB5RSTCLRR_I2C4RST                   RCC_APB5RSTCLRR_I2C4RST_Msk                        /*!< I2C4 block reset */
#define RCC_APB5RSTCLRR_I2C6RST_Pos               (3U)
#define RCC_APB5RSTCLRR_I2C6RST_Msk               (0x1U << RCC_APB5RSTCLRR_I2C6RST_Pos)              /*!< 0x00000008 */
#define RCC_APB5RSTCLRR_I2C6RST                   RCC_APB5RSTCLRR_I2C6RST_Msk                        /*!< I2C6 block reset */
#define RCC_APB5RSTCLRR_USART1RST_Pos             (4U)
#define RCC_APB5RSTCLRR_USART1RST_Msk             (0x1U << RCC_APB5RSTCLRR_USART1RST_Pos)            /*!< 0x00000010 */
#define RCC_APB5RSTCLRR_USART1RST                 RCC_APB5RSTCLRR_USART1RST_Msk                      /*!< USART1 block reset */
#define RCC_APB5RSTCLRR_STGENRST_Pos              (20U)
#define RCC_APB5RSTCLRR_STGENRST_Msk              (0x1U << RCC_APB5RSTCLRR_STGENRST_Pos)             /*!< 0x00100000 */
#define RCC_APB5RSTCLRR_STGENRST                  RCC_APB5RSTCLRR_STGENRST_Msk                       /*!< STGEN block reset */

/***************  Bit definition for RCC_AHB5RSTSETR register  ****************/
#define RCC_AHB5RSTSETR_GPIOZRST_Pos              (0U)
#define RCC_AHB5RSTSETR_GPIOZRST_Msk              (0x1U << RCC_AHB5RSTSETR_GPIOZRST_Pos)             /*!< 0x00000001 */
#define RCC_AHB5RSTSETR_GPIOZRST                  RCC_AHB5RSTSETR_GPIOZRST_Msk                       /*!< GPIOZ secure block reset */
#define RCC_AHB5RSTSETR_CRYP1RST_Pos              (4U)
#define RCC_AHB5RSTSETR_CRYP1RST_Msk              (0x1U << RCC_AHB5RSTSETR_CRYP1RST_Pos)             /*!< 0x00000010 */
#define RCC_AHB5RSTSETR_CRYP1RST                  RCC_AHB5RSTSETR_CRYP1RST_Msk                       /*!< CRYP1 (3DES/AES1) block reset */
#define RCC_AHB5RSTSETR_HASH1RST_Pos              (5U)
#define RCC_AHB5RSTSETR_HASH1RST_Msk              (0x1U << RCC_AHB5RSTSETR_HASH1RST_Pos)             /*!< 0x00000020 */
#define RCC_AHB5RSTSETR_HASH1RST                  RCC_AHB5RSTSETR_HASH1RST_Msk                       /*!< HASH1 block reset */
#define RCC_AHB5RSTSETR_RNG1RST_Pos               (6U)
#define RCC_AHB5RSTSETR_RNG1RST_Msk               (0x1U << RCC_AHB5RSTSETR_RNG1RST_Pos)              /*!< 0x00000040 */
#define RCC_AHB5RSTSETR_RNG1RST                   RCC_AHB5RSTSETR_RNG1RST_Msk                        /*!< RNG1 block reset */
#define RCC_AHB5RSTSETR_AXIMCRST_Pos              (16U)
#define RCC_AHB5RSTSETR_AXIMCRST_Msk              (0x1U << RCC_AHB5RSTSETR_AXIMCRST_Pos)             /*!< 0x00010000 */
#define RCC_AHB5RSTSETR_AXIMCRST                  RCC_AHB5RSTSETR_AXIMCRST_Msk                       /*!< AXIMC block reset */

/***************  Bit definition for RCC_AHB5RSTCLRR register  ****************/
#define RCC_AHB5RSTCLRR_GPIOZRST_Pos              (0U)
#define RCC_AHB5RSTCLRR_GPIOZRST_Msk              (0x1U << RCC_AHB5RSTCLRR_GPIOZRST_Pos)             /*!< 0x00000001 */
#define RCC_AHB5RSTCLRR_GPIOZRST                  RCC_AHB5RSTCLRR_GPIOZRST_Msk                       /*!< GPIOZ secure block reset */
#define RCC_AHB5RSTCLRR_CRYP1RST_Pos              (4U)
#define RCC_AHB5RSTCLRR_CRYP1RST_Msk              (0x1U << RCC_AHB5RSTCLRR_CRYP1RST_Pos)             /*!< 0x00000010 */
#define RCC_AHB5RSTCLRR_CRYP1RST                  RCC_AHB5RSTCLRR_CRYP1RST_Msk                       /*!< CRYP1 (3DES/AES1) block reset */
#define RCC_AHB5RSTCLRR_HASH1RST_Pos              (5U)
#define RCC_AHB5RSTCLRR_HASH1RST_Msk              (0x1U << RCC_AHB5RSTCLRR_HASH1RST_Pos)             /*!< 0x00000020 */
#define RCC_AHB5RSTCLRR_HASH1RST                  RCC_AHB5RSTCLRR_HASH1RST_Msk                       /*!< HASH1 block reset */
#define RCC_AHB5RSTCLRR_RNG1RST_Pos               (6U)
#define RCC_AHB5RSTCLRR_RNG1RST_Msk               (0x1U << RCC_AHB5RSTCLRR_RNG1RST_Pos)              /*!< 0x00000040 */
#define RCC_AHB5RSTCLRR_RNG1RST                   RCC_AHB5RSTCLRR_RNG1RST_Msk                        /*!< RNG1 block reset */
#define RCC_AHB5RSTCLRR_AXIMCRST_Pos              (16U)
#define RCC_AHB5RSTCLRR_AXIMCRST_Msk              (0x1U << RCC_AHB5RSTCLRR_AXIMCRST_Pos)             /*!< 0x00010000 */
#define RCC_AHB5RSTCLRR_AXIMCRST                  RCC_AHB5RSTCLRR_AXIMCRST_Msk                       /*!< AXIMC block reset */

/***************  Bit definition for RCC_AHB6RSTSETR register  ****************/
#define RCC_AHB6RSTSETR_GPURST_Pos                (5U)
#define RCC_AHB6RSTSETR_GPURST_Msk                (0x1U << RCC_AHB6RSTSETR_GPURST_Pos)               /*!< 0x00000020 */
#define RCC_AHB6RSTSETR_GPURST                    RCC_AHB6RSTSETR_GPURST_Msk                         /*!< GPU block reset */
#define RCC_AHB6RSTSETR_ETHMACRST_Pos             (10U)
#define RCC_AHB6RSTSETR_ETHMACRST_Msk             (0x1U << RCC_AHB6RSTSETR_ETHMACRST_Pos)            /*!< 0x00000400 */
#define RCC_AHB6RSTSETR_ETHMACRST                 RCC_AHB6RSTSETR_ETHMACRST_Msk                      /*!< ETH block reset */
#define RCC_AHB6RSTSETR_FMCRST_Pos                (12U)
#define RCC_AHB6RSTSETR_FMCRST_Msk                (0x1U << RCC_AHB6RSTSETR_FMCRST_Pos)               /*!< 0x00001000 */
#define RCC_AHB6RSTSETR_FMCRST                    RCC_AHB6RSTSETR_FMCRST_Msk                         /*!< FMC block reset */
#define RCC_AHB6RSTSETR_QSPIRST_Pos               (14U)
#define RCC_AHB6RSTSETR_QSPIRST_Msk               (0x1U << RCC_AHB6RSTSETR_QSPIRST_Pos)              /*!< 0x00004000 */
#define RCC_AHB6RSTSETR_QSPIRST                   RCC_AHB6RSTSETR_QSPIRST_Msk                        /*!< QUADSPI and the QUADSPI delay block reset */
#define RCC_AHB6RSTSETR_SDMMC1RST_Pos             (16U)
#define RCC_AHB6RSTSETR_SDMMC1RST_Msk             (0x1U << RCC_AHB6RSTSETR_SDMMC1RST_Pos)            /*!< 0x00010000 */
#define RCC_AHB6RSTSETR_SDMMC1RST                 RCC_AHB6RSTSETR_SDMMC1RST_Msk                      /*!< SDMMC1 and the SDMMC1 delay (DLYBSD1) block reset */
#define RCC_AHB6RSTSETR_SDMMC2RST_Pos             (17U)
#define RCC_AHB6RSTSETR_SDMMC2RST_Msk             (0x1U << RCC_AHB6RSTSETR_SDMMC2RST_Pos)            /*!< 0x00020000 */
#define RCC_AHB6RSTSETR_SDMMC2RST                 RCC_AHB6RSTSETR_SDMMC2RST_Msk                      /*!< SDMMC2 and the SDMMC2 delay (DLYBSD2) block reset */
#define RCC_AHB6RSTSETR_CRC1RST_Pos               (20U)
#define RCC_AHB6RSTSETR_CRC1RST_Msk               (0x1U << RCC_AHB6RSTSETR_CRC1RST_Pos)              /*!< 0x00100000 */
#define RCC_AHB6RSTSETR_CRC1RST                   RCC_AHB6RSTSETR_CRC1RST_Msk                        /*!< CRC1 block reset */
#define RCC_AHB6RSTSETR_USBHRST_Pos               (24U)
#define RCC_AHB6RSTSETR_USBHRST_Msk               (0x1U << RCC_AHB6RSTSETR_USBHRST_Pos)              /*!< 0x01000000 */
#define RCC_AHB6RSTSETR_USBHRST                   RCC_AHB6RSTSETR_USBHRST_Msk                        /*!< USBH block reset */

/***************  Bit definition for RCC_AHB6RSTCLRR register  ****************/
#define RCC_AHB6RSTCLRR_ETHMACRST_Pos             (10U)
#define RCC_AHB6RSTCLRR_ETHMACRST_Msk             (0x1U << RCC_AHB6RSTCLRR_ETHMACRST_Pos)            /*!< 0x00000400 */
#define RCC_AHB6RSTCLRR_ETHMACRST                 RCC_AHB6RSTCLRR_ETHMACRST_Msk                      /*!< ETH block reset */
#define RCC_AHB6RSTCLRR_FMCRST_Pos                (12U)
#define RCC_AHB6RSTCLRR_FMCRST_Msk                (0x1U << RCC_AHB6RSTCLRR_FMCRST_Pos)               /*!< 0x00001000 */
#define RCC_AHB6RSTCLRR_FMCRST                    RCC_AHB6RSTCLRR_FMCRST_Msk                         /*!< FMC block reset */
#define RCC_AHB6RSTCLRR_QSPIRST_Pos               (14U)
#define RCC_AHB6RSTCLRR_QSPIRST_Msk               (0x1U << RCC_AHB6RSTCLRR_QSPIRST_Pos)              /*!< 0x00004000 */
#define RCC_AHB6RSTCLRR_QSPIRST                   RCC_AHB6RSTCLRR_QSPIRST_Msk                        /*!< QUADSPI and the QUADSPI delay block reset */
#define RCC_AHB6RSTCLRR_SDMMC1RST_Pos             (16U)
#define RCC_AHB6RSTCLRR_SDMMC1RST_Msk             (0x1U << RCC_AHB6RSTCLRR_SDMMC1RST_Pos)            /*!< 0x00010000 */
#define RCC_AHB6RSTCLRR_SDMMC1RST                 RCC_AHB6RSTCLRR_SDMMC1RST_Msk                      /*!< SDMMC1 and the SDMMC1 delay (DLYBSD1) block reset */
#define RCC_AHB6RSTCLRR_SDMMC2RST_Pos             (17U)
#define RCC_AHB6RSTCLRR_SDMMC2RST_Msk             (0x1U << RCC_AHB6RSTCLRR_SDMMC2RST_Pos)            /*!< 0x00020000 */
#define RCC_AHB6RSTCLRR_SDMMC2RST                 RCC_AHB6RSTCLRR_SDMMC2RST_Msk                      /*!< SDMMC2 and the SDMMC2 delay (DLYBSD2) block reset */
#define RCC_AHB6RSTCLRR_CRC1RST_Pos               (20U)
#define RCC_AHB6RSTCLRR_CRC1RST_Msk               (0x1U << RCC_AHB6RSTCLRR_CRC1RST_Pos)              /*!< 0x00100000 */
#define RCC_AHB6RSTCLRR_CRC1RST                   RCC_AHB6RSTCLRR_CRC1RST_Msk                        /*!< CRC1 block reset */
#define RCC_AHB6RSTCLRR_USBHRST_Pos               (24U)
#define RCC_AHB6RSTCLRR_USBHRST_Msk               (0x1U << RCC_AHB6RSTCLRR_USBHRST_Pos)              /*!< 0x01000000 */
#define RCC_AHB6RSTCLRR_USBHRST                   RCC_AHB6RSTCLRR_USBHRST_Msk                        /*!< USBH block reset */

/**************  Bit definition for RCC_TZAHB6RSTSETR register  ***************/
#define RCC_TZAHB6RSTSETR_MDMARST_Pos             (0U)
#define RCC_TZAHB6RSTSETR_MDMARST_Msk             (0x1U << RCC_TZAHB6RSTSETR_MDMARST_Pos)            /*!< 0x00000001 */
#define RCC_TZAHB6RSTSETR_MDMARST                 RCC_TZAHB6RSTSETR_MDMARST_Msk                      /*!< MDMA block reset */

/**************  Bit definition for RCC_TZAHB6RSTCLRR register  ***************/
#define RCC_TZAHB6RSTCLRR_MDMARST_Pos             (0U)
#define RCC_TZAHB6RSTCLRR_MDMARST_Msk             (0x1U << RCC_TZAHB6RSTCLRR_MDMARST_Pos)            /*!< 0x00000001 */
#define RCC_TZAHB6RSTCLRR_MDMARST                 RCC_TZAHB6RSTCLRR_MDMARST_Msk                      /*!< MDMA block reset */

/**************  Bit definition for RCC_MP_APB4ENSETR register  ***************/
#define RCC_MP_APB4ENSETR_LTDCEN_Pos              (0U)
#define RCC_MP_APB4ENSETR_LTDCEN_Msk              (0x1U << RCC_MP_APB4ENSETR_LTDCEN_Pos)             /*!< 0x00000001 */
#define RCC_MP_APB4ENSETR_LTDCEN                  RCC_MP_APB4ENSETR_LTDCEN_Msk                       /*!< LTDC peripheral clocks enable */
#define RCC_MP_APB4ENSETR_DSIEN_Pos               (4U)
#define RCC_MP_APB4ENSETR_DSIEN_Msk               (0x1U << RCC_MP_APB4ENSETR_DSIEN_Pos)              /*!< 0x00000010 */
#define RCC_MP_APB4ENSETR_DSIEN                   RCC_MP_APB4ENSETR_DSIEN_Msk                        /*!< DSI peripheral clocks enable */
#define RCC_MP_APB4ENSETR_DDRPERFMEN_Pos          (8U)
#define RCC_MP_APB4ENSETR_DDRPERFMEN_Msk          (0x1U << RCC_MP_APB4ENSETR_DDRPERFMEN_Pos)         /*!< 0x00000100 */
#define RCC_MP_APB4ENSETR_DDRPERFMEN              RCC_MP_APB4ENSETR_DDRPERFMEN_Msk                   /*!< DDRPERFM APB clock enable */
#define RCC_MP_APB4ENSETR_IWDG2APBEN_Pos          (15U)
#define RCC_MP_APB4ENSETR_IWDG2APBEN_Msk          (0x1U << RCC_MP_APB4ENSETR_IWDG2APBEN_Pos)         /*!< 0x00008000 */
#define RCC_MP_APB4ENSETR_IWDG2APBEN              RCC_MP_APB4ENSETR_IWDG2APBEN_Msk                   /*!< IWDG2 APB clock enable */
#define RCC_MP_APB4ENSETR_USBPHYEN_Pos            (16U)
#define RCC_MP_APB4ENSETR_USBPHYEN_Msk            (0x1U << RCC_MP_APB4ENSETR_USBPHYEN_Pos)           /*!< 0x00010000 */
#define RCC_MP_APB4ENSETR_USBPHYEN                RCC_MP_APB4ENSETR_USBPHYEN_Msk                     /*!< USBPHYC peripheral clocks enable */
#define RCC_MP_APB4ENSETR_STGENROEN_Pos           (20U)
#define RCC_MP_APB4ENSETR_STGENROEN_Msk           (0x1U << RCC_MP_APB4ENSETR_STGENROEN_Pos)          /*!< 0x00100000 */
#define RCC_MP_APB4ENSETR_STGENROEN               RCC_MP_APB4ENSETR_STGENROEN_Msk                    /*!< STGEN Read-Only interface peripheral clocks enable */

/**************  Bit definition for RCC_MP_APB4ENCLRR register  ***************/
#define RCC_MP_APB4ENCLRR_LTDCEN_Pos              (0U)
#define RCC_MP_APB4ENCLRR_LTDCEN_Msk              (0x1U << RCC_MP_APB4ENCLRR_LTDCEN_Pos)             /*!< 0x00000001 */
#define RCC_MP_APB4ENCLRR_LTDCEN                  RCC_MP_APB4ENCLRR_LTDCEN_Msk                       /*!< LTDC peripheral clocks disable */
#define RCC_MP_APB4ENCLRR_DSIEN_Pos               (4U)
#define RCC_MP_APB4ENCLRR_DSIEN_Msk               (0x1U << RCC_MP_APB4ENCLRR_DSIEN_Pos)              /*!< 0x00000010 */
#define RCC_MP_APB4ENCLRR_DSIEN                   RCC_MP_APB4ENCLRR_DSIEN_Msk                        /*!< DSI peripheral clocks disable */
#define RCC_MP_APB4ENCLRR_DDRPERFMEN_Pos          (8U)
#define RCC_MP_APB4ENCLRR_DDRPERFMEN_Msk          (0x1U << RCC_MP_APB4ENCLRR_DDRPERFMEN_Pos)         /*!< 0x00000100 */
#define RCC_MP_APB4ENCLRR_DDRPERFMEN              RCC_MP_APB4ENCLRR_DDRPERFMEN_Msk                   /*!< DDRPERFM APB clock enable */
#define RCC_MP_APB4ENCLRR_IWDG2APBEN_Pos          (15U)
#define RCC_MP_APB4ENCLRR_IWDG2APBEN_Msk          (0x1U << RCC_MP_APB4ENCLRR_IWDG2APBEN_Pos)         /*!< 0x00008000 */
#define RCC_MP_APB4ENCLRR_IWDG2APBEN              RCC_MP_APB4ENCLRR_IWDG2APBEN_Msk                   /*!< IWDG2 APB clock disable */
#define RCC_MP_APB4ENCLRR_USBPHYEN_Pos            (16U)
#define RCC_MP_APB4ENCLRR_USBPHYEN_Msk            (0x1U << RCC_MP_APB4ENCLRR_USBPHYEN_Pos)           /*!< 0x00010000 */
#define RCC_MP_APB4ENCLRR_USBPHYEN                RCC_MP_APB4ENCLRR_USBPHYEN_Msk                     /*!< USBPHYC peripheral clocks disable */
#define RCC_MP_APB4ENCLRR_STGENROEN_Pos           (20U)
#define RCC_MP_APB4ENCLRR_STGENROEN_Msk           (0x1U << RCC_MP_APB4ENCLRR_STGENROEN_Pos)          /*!< 0x00100000 */
#define RCC_MP_APB4ENCLRR_STGENROEN               RCC_MP_APB4ENCLRR_STGENROEN_Msk                    /*!< STGEN Read-Only interface peripheral clocks disable */

/**************  Bit definition for RCC_MP_APB5ENSETR register  ***************/
#define RCC_MP_APB5ENSETR_SPI6EN_Pos              (0U)
#define RCC_MP_APB5ENSETR_SPI6EN_Msk              (0x1U << RCC_MP_APB5ENSETR_SPI6EN_Pos)             /*!< 0x00000001 */
#define RCC_MP_APB5ENSETR_SPI6EN                  RCC_MP_APB5ENSETR_SPI6EN_Msk                       /*!< SPI6 peripheral clocks enable */
#define RCC_MP_APB5ENSETR_I2C4EN_Pos              (2U)
#define RCC_MP_APB5ENSETR_I2C4EN_Msk              (0x1U << RCC_MP_APB5ENSETR_I2C4EN_Pos)             /*!< 0x00000004 */
#define RCC_MP_APB5ENSETR_I2C4EN                  RCC_MP_APB5ENSETR_I2C4EN_Msk                       /*!< I2C4 peripheral clocks enable */
#define RCC_MP_APB5ENSETR_I2C6EN_Pos              (3U)
#define RCC_MP_APB5ENSETR_I2C6EN_Msk              (0x1U << RCC_MP_APB5ENSETR_I2C6EN_Pos)             /*!< 0x00000008 */
#define RCC_MP_APB5ENSETR_I2C6EN                  RCC_MP_APB5ENSETR_I2C6EN_Msk                       /*!< I2C6 peripheral clocks enable */
#define RCC_MP_APB5ENSETR_USART1EN_Pos            (4U)
#define RCC_MP_APB5ENSETR_USART1EN_Msk            (0x1U << RCC_MP_APB5ENSETR_USART1EN_Pos)           /*!< 0x00000010 */
#define RCC_MP_APB5ENSETR_USART1EN                RCC_MP_APB5ENSETR_USART1EN_Msk                     /*!< USART1 peripheral clocks enable */
#define RCC_MP_APB5ENSETR_RTCAPBEN_Pos            (8U)
#define RCC_MP_APB5ENSETR_RTCAPBEN_Msk            (0x1U << RCC_MP_APB5ENSETR_RTCAPBEN_Pos)           /*!< 0x00000100 */
#define RCC_MP_APB5ENSETR_RTCAPBEN                RCC_MP_APB5ENSETR_RTCAPBEN_Msk                     /*!< RTC APB clock enable */
#define RCC_MP_APB5ENSETR_TZC1EN_Pos              (11U)
#define RCC_MP_APB5ENSETR_TZC1EN_Msk              (0x1U << RCC_MP_APB5ENSETR_TZC1EN_Pos)             /*!< 0x00000800 */
#define RCC_MP_APB5ENSETR_TZC1EN                  RCC_MP_APB5ENSETR_TZC1EN_Msk                       /*!< TZC AXI port 1 clocks enable */
#define RCC_MP_APB5ENSETR_TZC2EN_Pos              (12U)
#define RCC_MP_APB5ENSETR_TZC2EN_Msk              (0x1U << RCC_MP_APB5ENSETR_TZC2EN_Pos)             /*!< 0x00001000 */
#define RCC_MP_APB5ENSETR_TZC2EN                  RCC_MP_APB5ENSETR_TZC2EN_Msk                       /*!< TZC AXI port 2 clocks enable */
#define RCC_MP_APB5ENSETR_TZPCEN_Pos              (13U)
#define RCC_MP_APB5ENSETR_TZPCEN_Msk              (0x1U << RCC_MP_APB5ENSETR_TZPCEN_Pos)             /*!< 0x00002000 */
#define RCC_MP_APB5ENSETR_TZPCEN                  RCC_MP_APB5ENSETR_TZPCEN_Msk                       /*!< TZPC peripheral clocks enable */
#define RCC_MP_APB5ENSETR_IWDG1APBEN_Pos          (15U)
#define RCC_MP_APB5ENSETR_IWDG1APBEN_Msk          (0x1U << RCC_MP_APB5ENSETR_IWDG1APBEN_Pos)         /*!< 0x00008000 */
#define RCC_MP_APB5ENSETR_IWDG1APBEN              RCC_MP_APB5ENSETR_IWDG1APBEN_Msk                   /*!< IWDG1 APB clock enable */
#define RCC_MP_APB5ENSETR_BSECEN_Pos              (16U)
#define RCC_MP_APB5ENSETR_BSECEN_Msk              (0x1U << RCC_MP_APB5ENSETR_BSECEN_Pos)             /*!< 0x00010000 */
#define RCC_MP_APB5ENSETR_BSECEN                  RCC_MP_APB5ENSETR_BSECEN_Msk                       /*!< BSEC peripheral clocks enable */
#define RCC_MP_APB5ENSETR_STGENEN_Pos             (20U)
#define RCC_MP_APB5ENSETR_STGENEN_Msk             (0x1U << RCC_MP_APB5ENSETR_STGENEN_Pos)            /*!< 0x00100000 */
#define RCC_MP_APB5ENSETR_STGENEN                 RCC_MP_APB5ENSETR_STGENEN_Msk                      /*!< STGEN Controller part, peripheral clocks enable */

/**************  Bit definition for RCC_MP_APB5ENCLRR register  ***************/
#define RCC_MP_APB5ENCLRR_SPI6EN_Pos              (0U)
#define RCC_MP_APB5ENCLRR_SPI6EN_Msk              (0x1U << RCC_MP_APB5ENCLRR_SPI6EN_Pos)             /*!< 0x00000001 */
#define RCC_MP_APB5ENCLRR_SPI6EN                  RCC_MP_APB5ENCLRR_SPI6EN_Msk                       /*!< SPI6 peripheral clocks disable */
#define RCC_MP_APB5ENCLRR_I2C4EN_Pos              (2U)
#define RCC_MP_APB5ENCLRR_I2C4EN_Msk              (0x1U << RCC_MP_APB5ENCLRR_I2C4EN_Pos)             /*!< 0x00000004 */
#define RCC_MP_APB5ENCLRR_I2C4EN                  RCC_MP_APB5ENCLRR_I2C4EN_Msk                       /*!< I2C4 peripheral clocks disable */
#define RCC_MP_APB5ENCLRR_I2C6EN_Pos              (3U)
#define RCC_MP_APB5ENCLRR_I2C6EN_Msk              (0x1U << RCC_MP_APB5ENCLRR_I2C6EN_Pos)             /*!< 0x00000008 */
#define RCC_MP_APB5ENCLRR_I2C6EN                  RCC_MP_APB5ENCLRR_I2C6EN_Msk                       /*!< I2C6 peripheral clocks disable */
#define RCC_MP_APB5ENCLRR_USART1EN_Pos            (4U)
#define RCC_MP_APB5ENCLRR_USART1EN_Msk            (0x1U << RCC_MP_APB5ENCLRR_USART1EN_Pos)           /*!< 0x00000010 */
#define RCC_MP_APB5ENCLRR_USART1EN                RCC_MP_APB5ENCLRR_USART1EN_Msk                     /*!< USART1 peripheral clocks disable */
#define RCC_MP_APB5ENCLRR_RTCAPBEN_Pos            (8U)
#define RCC_MP_APB5ENCLRR_RTCAPBEN_Msk            (0x1U << RCC_MP_APB5ENCLRR_RTCAPBEN_Pos)           /*!< 0x00000100 */
#define RCC_MP_APB5ENCLRR_RTCAPBEN                RCC_MP_APB5ENCLRR_RTCAPBEN_Msk                     /*!< RTC APB clock disable */
#define RCC_MP_APB5ENCLRR_TZC1EN_Pos              (11U)
#define RCC_MP_APB5ENCLRR_TZC1EN_Msk              (0x1U << RCC_MP_APB5ENCLRR_TZC1EN_Pos)             /*!< 0x00000800 */
#define RCC_MP_APB5ENCLRR_TZC1EN                  RCC_MP_APB5ENCLRR_TZC1EN_Msk                       /*!< TZC AXI port 1 clocks disable */
#define RCC_MP_APB5ENCLRR_TZC2EN_Pos              (12U)
#define RCC_MP_APB5ENCLRR_TZC2EN_Msk              (0x1U << RCC_MP_APB5ENCLRR_TZC2EN_Pos)             /*!< 0x00001000 */
#define RCC_MP_APB5ENCLRR_TZC2EN                  RCC_MP_APB5ENCLRR_TZC2EN_Msk                       /*!< TZC AXI port 2 clocks disable */
#define RCC_MP_APB5ENCLRR_TZPCEN_Pos              (13U)
#define RCC_MP_APB5ENCLRR_TZPCEN_Msk              (0x1U << RCC_MP_APB5ENCLRR_TZPCEN_Pos)             /*!< 0x00002000 */
#define RCC_MP_APB5ENCLRR_TZPCEN                  RCC_MP_APB5ENCLRR_TZPCEN_Msk                       /*!< TZPC peripheral clocks disable */
#define RCC_MP_APB5ENCLRR_IWDG1APBEN_Pos          (15U)
#define RCC_MP_APB5ENCLRR_IWDG1APBEN_Msk          (0x1U << RCC_MP_APB5ENCLRR_IWDG1APBEN_Pos)         /*!< 0x00008000 */
#define RCC_MP_APB5ENCLRR_IWDG1APBEN              RCC_MP_APB5ENCLRR_IWDG1APBEN_Msk                   /*!< IWDG1 APB clock disable */
#define RCC_MP_APB5ENCLRR_BSECEN_Pos              (16U)
#define RCC_MP_APB5ENCLRR_BSECEN_Msk              (0x1U << RCC_MP_APB5ENCLRR_BSECEN_Pos)             /*!< 0x00010000 */
#define RCC_MP_APB5ENCLRR_BSECEN                  RCC_MP_APB5ENCLRR_BSECEN_Msk                       /*!< BSEC peripheral clocks disable */
#define RCC_MP_APB5ENCLRR_STGENEN_Pos             (20U)
#define RCC_MP_APB5ENCLRR_STGENEN_Msk             (0x1U << RCC_MP_APB5ENCLRR_STGENEN_Pos)            /*!< 0x00100000 */
#define RCC_MP_APB5ENCLRR_STGENEN                 RCC_MP_APB5ENCLRR_STGENEN_Msk                      /*!< STGEN Controller part, peripheral clocks disable */

/**************  Bit definition for RCC_MP_AHB5ENSETR register  ***************/
#define RCC_MP_AHB5ENSETR_GPIOZEN_Pos             (0U)
#define RCC_MP_AHB5ENSETR_GPIOZEN_Msk             (0x1U << RCC_MP_AHB5ENSETR_GPIOZEN_Pos)            /*!< 0x00000001 */
#define RCC_MP_AHB5ENSETR_GPIOZEN                 RCC_MP_AHB5ENSETR_GPIOZEN_Msk                      /*!< GPIOZ Secure peripheral clocks enable */
#define RCC_MP_AHB5ENSETR_CRYP1EN_Pos             (4U)
#define RCC_MP_AHB5ENSETR_CRYP1EN_Msk             (0x1U << RCC_MP_AHB5ENSETR_CRYP1EN_Pos)            /*!< 0x00000010 */
#define RCC_MP_AHB5ENSETR_CRYP1EN                 RCC_MP_AHB5ENSETR_CRYP1EN_Msk                      /*!< CRYP1 (3DES/AES1) peripheral clocks enable */
#define RCC_MP_AHB5ENSETR_HASH1EN_Pos             (5U)
#define RCC_MP_AHB5ENSETR_HASH1EN_Msk             (0x1U << RCC_MP_AHB5ENSETR_HASH1EN_Pos)            /*!< 0x00000020 */
#define RCC_MP_AHB5ENSETR_HASH1EN                 RCC_MP_AHB5ENSETR_HASH1EN_Msk                      /*!< HASH1 peripheral clocks enable */
#define RCC_MP_AHB5ENSETR_RNG1EN_Pos              (6U)
#define RCC_MP_AHB5ENSETR_RNG1EN_Msk              (0x1U << RCC_MP_AHB5ENSETR_RNG1EN_Pos)             /*!< 0x00000040 */
#define RCC_MP_AHB5ENSETR_RNG1EN                  RCC_MP_AHB5ENSETR_RNG1EN_Msk                       /*!< RNG1 peripheral clocks enable */
#define RCC_MP_AHB5ENSETR_BKPSRAMEN_Pos           (8U)
#define RCC_MP_AHB5ENSETR_BKPSRAMEN_Msk           (0x1U << RCC_MP_AHB5ENSETR_BKPSRAMEN_Pos)          /*!< 0x00000100 */
#define RCC_MP_AHB5ENSETR_BKPSRAMEN               RCC_MP_AHB5ENSETR_BKPSRAMEN_Msk                    /*!< BKPSRAM clocks enable */
#define RCC_MP_AHB5ENSETR_AXIMCEN_Pos             (16U)
#define RCC_MP_AHB5ENSETR_AXIMCEN_Msk             (0x1U << RCC_MP_AHB5ENSETR_AXIMCEN_Pos)            /*!< 0x00010000 */
#define RCC_MP_AHB5ENSETR_AXIMCEN                 RCC_MP_AHB5ENSETR_AXIMCEN_Msk                      /*!< AXIMC clocks enable */

/**************  Bit definition for RCC_MP_AHB5ENCLRR register  ***************/
#define RCC_MP_AHB5ENCLRR_GPIOZEN_Pos             (0U)
#define RCC_MP_AHB5ENCLRR_GPIOZEN_Msk             (0x1U << RCC_MP_AHB5ENCLRR_GPIOZEN_Pos)            /*!< 0x00000001 */
#define RCC_MP_AHB5ENCLRR_GPIOZEN                 RCC_MP_AHB5ENCLRR_GPIOZEN_Msk                      /*!< GPIOZ Secure peripheral clocks enable */
#define RCC_MP_AHB5ENCLRR_CRYP1EN_Pos             (4U)
#define RCC_MP_AHB5ENCLRR_CRYP1EN_Msk             (0x1U << RCC_MP_AHB5ENCLRR_CRYP1EN_Pos)            /*!< 0x00000010 */
#define RCC_MP_AHB5ENCLRR_CRYP1EN                 RCC_MP_AHB5ENCLRR_CRYP1EN_Msk                      /*!< CRYP1 (3DES/AES1) peripheral clocks enable */
#define RCC_MP_AHB5ENCLRR_HASH1EN_Pos             (5U)
#define RCC_MP_AHB5ENCLRR_HASH1EN_Msk             (0x1U << RCC_MP_AHB5ENCLRR_HASH1EN_Pos)            /*!< 0x00000020 */
#define RCC_MP_AHB5ENCLRR_HASH1EN                 RCC_MP_AHB5ENCLRR_HASH1EN_Msk                      /*!< HASH1 peripheral clocks enable */
#define RCC_MP_AHB5ENCLRR_RNG1EN_Pos              (6U)
#define RCC_MP_AHB5ENCLRR_RNG1EN_Msk              (0x1U << RCC_MP_AHB5ENCLRR_RNG1EN_Pos)             /*!< 0x00000040 */
#define RCC_MP_AHB5ENCLRR_RNG1EN                  RCC_MP_AHB5ENCLRR_RNG1EN_Msk                       /*!< RNG1 peripheral clocks enable */
#define RCC_MP_AHB5ENCLRR_BKPSRAMEN_Pos           (8U)
#define RCC_MP_AHB5ENCLRR_BKPSRAMEN_Msk           (0x1U << RCC_MP_AHB5ENCLRR_BKPSRAMEN_Pos)          /*!< 0x00000100 */
#define RCC_MP_AHB5ENCLRR_BKPSRAMEN               RCC_MP_AHB5ENCLRR_BKPSRAMEN_Msk                    /*!< BKPSRAM clocks enable */
#define RCC_MP_AHB5ENCLRR_AXIMCEN_Pos             (16U)
#define RCC_MP_AHB5ENCLRR_AXIMCEN_Msk             (0x1U << RCC_MP_AHB5ENCLRR_AXIMCEN_Pos)            /*!< 0x00010000 */
#define RCC_MP_AHB5ENCLRR_AXIMCEN                 RCC_MP_AHB5ENCLRR_AXIMCEN_Msk                      /*!< AXIMC clocks enable */

/**************  Bit definition for RCC_MP_AHB6ENSETR register  ***************/
#define RCC_MP_AHB6ENSETR_MDMAEN_Pos              (0U)
#define RCC_MP_AHB6ENSETR_MDMAEN_Msk              (0x1U << RCC_MP_AHB6ENSETR_MDMAEN_Pos)             /*!< 0x00000001 */
#define RCC_MP_AHB6ENSETR_MDMAEN                  RCC_MP_AHB6ENSETR_MDMAEN_Msk                       /*!< MDMA peripheral clocks enable */
#define RCC_MP_AHB6ENSETR_GPUEN_Pos               (5U)
#define RCC_MP_AHB6ENSETR_GPUEN_Msk               (0x1U << RCC_MP_AHB6ENSETR_GPUEN_Pos)              /*!< 0x00000020 */
#define RCC_MP_AHB6ENSETR_GPUEN                   RCC_MP_AHB6ENSETR_GPUEN_Msk                        /*!< GPU peripheral clocks enable */
#define RCC_MP_AHB6ENSETR_ETHCKEN_Pos             (7U)
#define RCC_MP_AHB6ENSETR_ETHCKEN_Msk             (0x1U << RCC_MP_AHB6ENSETR_ETHCKEN_Pos)            /*!< 0x00000080 */
#define RCC_MP_AHB6ENSETR_ETHCKEN                 RCC_MP_AHB6ENSETR_ETHCKEN_Msk                      /*!< Enable of the Ethernet clock generated by the RCC (eth_ker_ck) */
#define RCC_MP_AHB6ENSETR_ETHTXEN_Pos             (8U)
#define RCC_MP_AHB6ENSETR_ETHTXEN_Msk             (0x1U << RCC_MP_AHB6ENSETR_ETHTXEN_Pos)            /*!< 0x00000100 */
#define RCC_MP_AHB6ENSETR_ETHTXEN                 RCC_MP_AHB6ENSETR_ETHTXEN_Msk                      /*!< Ethernet Transmission Clock Enable */
#define RCC_MP_AHB6ENSETR_ETHRXEN_Pos             (9U)
#define RCC_MP_AHB6ENSETR_ETHRXEN_Msk             (0x1U << RCC_MP_AHB6ENSETR_ETHRXEN_Pos)            /*!< 0x00000200 */
#define RCC_MP_AHB6ENSETR_ETHRXEN                 RCC_MP_AHB6ENSETR_ETHRXEN_Msk                      /*!< Ethernet Reception Clock Enable */
#define RCC_MP_AHB6ENSETR_ETHMACEN_Pos            (10U)
#define RCC_MP_AHB6ENSETR_ETHMACEN_Msk            (0x1U << RCC_MP_AHB6ENSETR_ETHMACEN_Pos)           /*!< 0x00000400 */
#define RCC_MP_AHB6ENSETR_ETHMACEN                RCC_MP_AHB6ENSETR_ETHMACEN_Msk                     /*!< Ethernet MAC bus interface Clock Enable (hclk6 and aclk) */
#define RCC_MP_AHB6ENSETR_FMCEN_Pos               (12U)
#define RCC_MP_AHB6ENSETR_FMCEN_Msk               (0x1U << RCC_MP_AHB6ENSETR_FMCEN_Pos)              /*!< 0x00001000 */
#define RCC_MP_AHB6ENSETR_FMCEN                   RCC_MP_AHB6ENSETR_FMCEN_Msk                        /*!< FMC peripheral clocks enable */
#define RCC_MP_AHB6ENSETR_QSPIEN_Pos              (14U)
#define RCC_MP_AHB6ENSETR_QSPIEN_Msk              (0x1U << RCC_MP_AHB6ENSETR_QSPIEN_Pos)             /*!< 0x00004000 */
#define RCC_MP_AHB6ENSETR_QSPIEN                  RCC_MP_AHB6ENSETR_QSPIEN_Msk                       /*!< QUADSPI peripheral clocks enable */
#define RCC_MP_AHB6ENSETR_SDMMC1EN_Pos            (16U)
#define RCC_MP_AHB6ENSETR_SDMMC1EN_Msk            (0x1U << RCC_MP_AHB6ENSETR_SDMMC1EN_Pos)           /*!< 0x00010000 */
#define RCC_MP_AHB6ENSETR_SDMMC1EN                RCC_MP_AHB6ENSETR_SDMMC1EN_Msk                     /*!< SDMMC1 and SDMMC1 delay (DLYBSD1) block peripheral clocks enable */
#define RCC_MP_AHB6ENSETR_SDMMC2EN_Pos            (17U)
#define RCC_MP_AHB6ENSETR_SDMMC2EN_Msk            (0x1U << RCC_MP_AHB6ENSETR_SDMMC2EN_Pos)           /*!< 0x00020000 */
#define RCC_MP_AHB6ENSETR_SDMMC2EN                RCC_MP_AHB6ENSETR_SDMMC2EN_Msk                     /*!< SDMMC2 and SDMMC2 delay (DLYBSD2) block peripheral clocks enable */
#define RCC_MP_AHB6ENSETR_CRC1EN_Pos              (20U)
#define RCC_MP_AHB6ENSETR_CRC1EN_Msk              (0x1U << RCC_MP_AHB6ENSETR_CRC1EN_Pos)             /*!< 0x00100000 */
#define RCC_MP_AHB6ENSETR_CRC1EN                  RCC_MP_AHB6ENSETR_CRC1EN_Msk                       /*!< CRC1 peripheral clocks enable */
#define RCC_MP_AHB6ENSETR_USBHEN_Pos              (24U)
#define RCC_MP_AHB6ENSETR_USBHEN_Msk              (0x1U << RCC_MP_AHB6ENSETR_USBHEN_Pos)             /*!< 0x01000000 */
#define RCC_MP_AHB6ENSETR_USBHEN                  RCC_MP_AHB6ENSETR_USBHEN_Msk                       /*!< USBH peripheral clocks enable */

/**************  Bit definition for RCC_MP_AHB6ENCLRR register  ***************/
#define RCC_MP_AHB6ENCLRR_MDMAEN_Pos              (0U)
#define RCC_MP_AHB6ENCLRR_MDMAEN_Msk              (0x1U << RCC_MP_AHB6ENCLRR_MDMAEN_Pos)             /*!< 0x00000001 */
#define RCC_MP_AHB6ENCLRR_MDMAEN                  RCC_MP_AHB6ENCLRR_MDMAEN_Msk                       /*!< MDMA peripheral clocks enable */
#define RCC_MP_AHB6ENCLRR_GPUEN_Pos               (5U)
#define RCC_MP_AHB6ENCLRR_GPUEN_Msk               (0x1U << RCC_MP_AHB6ENCLRR_GPUEN_Pos)              /*!< 0x00000020 */
#define RCC_MP_AHB6ENCLRR_GPUEN                   RCC_MP_AHB6ENCLRR_GPUEN_Msk                        /*!< GPU peripheral clocks enable */
#define RCC_MP_AHB6ENCLRR_ETHCKEN_Pos             (7U)
#define RCC_MP_AHB6ENCLRR_ETHCKEN_Msk             (0x1U << RCC_MP_AHB6ENCLRR_ETHCKEN_Pos)            /*!< 0x00000080 */
#define RCC_MP_AHB6ENCLRR_ETHCKEN                 RCC_MP_AHB6ENCLRR_ETHCKEN_Msk                      /*!< Disable of the Ethernet clock generated by the RCC (eth_ker_ck) */
#define RCC_MP_AHB6ENCLRR_ETHTXEN_Pos             (8U)
#define RCC_MP_AHB6ENCLRR_ETHTXEN_Msk             (0x1U << RCC_MP_AHB6ENCLRR_ETHTXEN_Pos)            /*!< 0x00000100 */
#define RCC_MP_AHB6ENCLRR_ETHTXEN                 RCC_MP_AHB6ENCLRR_ETHTXEN_Msk                      /*!< Disable of the Ethernet Transmission Clock */
#define RCC_MP_AHB6ENCLRR_ETHRXEN_Pos             (9U)
#define RCC_MP_AHB6ENCLRR_ETHRXEN_Msk             (0x1U << RCC_MP_AHB6ENCLRR_ETHRXEN_Pos)            /*!< 0x00000200 */
#define RCC_MP_AHB6ENCLRR_ETHRXEN                 RCC_MP_AHB6ENCLRR_ETHRXEN_Msk                      /*!< Disable of the Ethernet Reception Clock */
#define RCC_MP_AHB6ENCLRR_ETHMACEN_Pos            (10U)
#define RCC_MP_AHB6ENCLRR_ETHMACEN_Msk            (0x1U << RCC_MP_AHB6ENCLRR_ETHMACEN_Pos)           /*!< 0x00000400 */
#define RCC_MP_AHB6ENCLRR_ETHMACEN                RCC_MP_AHB6ENCLRR_ETHMACEN_Msk                     /*!< Disable of the bus interface clock for ETH block (hclk6 and aclk) */
#define RCC_MP_AHB6ENCLRR_FMCEN_Pos               (12U)
#define RCC_MP_AHB6ENCLRR_FMCEN_Msk               (0x1U << RCC_MP_AHB6ENCLRR_FMCEN_Pos)              /*!< 0x00001000 */
#define RCC_MP_AHB6ENCLRR_FMCEN                   RCC_MP_AHB6ENCLRR_FMCEN_Msk                        /*!< FMC peripheral clocks enable */
#define RCC_MP_AHB6ENCLRR_QSPIEN_Pos              (14U)
#define RCC_MP_AHB6ENCLRR_QSPIEN_Msk              (0x1U << RCC_MP_AHB6ENCLRR_QSPIEN_Pos)             /*!< 0x00004000 */
#define RCC_MP_AHB6ENCLRR_QSPIEN                  RCC_MP_AHB6ENCLRR_QSPIEN_Msk                       /*!< QUADSPI and QUADSPI delay block peripheral clocks enable */
#define RCC_MP_AHB6ENCLRR_SDMMC1EN_Pos            (16U)
#define RCC_MP_AHB6ENCLRR_SDMMC1EN_Msk            (0x1U << RCC_MP_AHB6ENCLRR_SDMMC1EN_Pos)           /*!< 0x00010000 */
#define RCC_MP_AHB6ENCLRR_SDMMC1EN                RCC_MP_AHB6ENCLRR_SDMMC1EN_Msk                     /*!< SDMMC1 and SDMMC1 delay (DLYBSD1) block peripheral clocks enable */
#define RCC_MP_AHB6ENCLRR_SDMMC2EN_Pos            (17U)
#define RCC_MP_AHB6ENCLRR_SDMMC2EN_Msk            (0x1U << RCC_MP_AHB6ENCLRR_SDMMC2EN_Pos)           /*!< 0x00020000 */
#define RCC_MP_AHB6ENCLRR_SDMMC2EN                RCC_MP_AHB6ENCLRR_SDMMC2EN_Msk                     /*!< SDMMC2 and SDMMC2 delay (DLYBSD2) block peripheral clocks enable */
#define RCC_MP_AHB6ENCLRR_CRC1EN_Pos              (20U)
#define RCC_MP_AHB6ENCLRR_CRC1EN_Msk              (0x1U << RCC_MP_AHB6ENCLRR_CRC1EN_Pos)             /*!< 0x00100000 */
#define RCC_MP_AHB6ENCLRR_CRC1EN                  RCC_MP_AHB6ENCLRR_CRC1EN_Msk                       /*!< CRC1 peripheral clocks enable */
#define RCC_MP_AHB6ENCLRR_USBHEN_Pos              (24U)
#define RCC_MP_AHB6ENCLRR_USBHEN_Msk              (0x1U << RCC_MP_AHB6ENCLRR_USBHEN_Pos)             /*!< 0x01000000 */
#define RCC_MP_AHB6ENCLRR_USBHEN                  RCC_MP_AHB6ENCLRR_USBHEN_Msk                       /*!< USBH peripheral clocks enable */

/*************  Bit definition for RCC_MP_TZAHB6ENSETR register  **************/
#define RCC_MP_TZAHB6ENSETR_MDMAEN_Pos            (0U)
#define RCC_MP_TZAHB6ENSETR_MDMAEN_Msk            (0x1U << RCC_MP_TZAHB6ENSETR_MDMAEN_Pos)           /*!< 0x00000001 */
#define RCC_MP_TZAHB6ENSETR_MDMAEN                RCC_MP_TZAHB6ENSETR_MDMAEN_Msk                     /*!< MDMA peripheral clocks enable */

/*************  Bit definition for RCC_MP_TZAHB6ENCLRR register  **************/
#define RCC_MP_TZAHB6ENCLRR_MDMAEN_Pos            (0U)
#define RCC_MP_TZAHB6ENCLRR_MDMAEN_Msk            (0x1U << RCC_MP_TZAHB6ENCLRR_MDMAEN_Pos)           /*!< 0x00000001 */
#define RCC_MP_TZAHB6ENCLRR_MDMAEN                RCC_MP_TZAHB6ENCLRR_MDMAEN_Msk                     /*!< MDMA peripheral clocks enable */

/**************  Bit definition for RCC_MC_APB4ENSETR register  ***************/
#define RCC_MC_APB4ENSETR_LTDCEN_Pos              (0U)
#define RCC_MC_APB4ENSETR_LTDCEN_Msk              (0x1U << RCC_MC_APB4ENSETR_LTDCEN_Pos)             /*!< 0x00000001 */
#define RCC_MC_APB4ENSETR_LTDCEN                  RCC_MC_APB4ENSETR_LTDCEN_Msk                       /*!< LTDC peripheral clocks enable */
#define RCC_MC_APB4ENSETR_DSIEN_Pos               (4U)
#define RCC_MC_APB4ENSETR_DSIEN_Msk               (0x1U << RCC_MC_APB4ENSETR_DSIEN_Pos)              /*!< 0x00000010 */
#define RCC_MC_APB4ENSETR_DSIEN                   RCC_MC_APB4ENSETR_DSIEN_Msk                        /*!< DSI peripheral clocks enable */
#define RCC_MC_APB4ENSETR_DDRPERFMEN_Pos          (8U)
#define RCC_MC_APB4ENSETR_DDRPERFMEN_Msk          (0x1U << RCC_MC_APB4ENSETR_DDRPERFMEN_Pos)         /*!< 0x00000100 */
#define RCC_MC_APB4ENSETR_DDRPERFMEN              RCC_MC_APB4ENSETR_DDRPERFMEN_Msk                   /*!< DDRPERFM APB clock enable */
#define RCC_MC_APB4ENSETR_USBPHYEN_Pos            (16U)
#define RCC_MC_APB4ENSETR_USBPHYEN_Msk            (0x1U << RCC_MC_APB4ENSETR_USBPHYEN_Pos)           /*!< 0x00010000 */
#define RCC_MC_APB4ENSETR_USBPHYEN                RCC_MC_APB4ENSETR_USBPHYEN_Msk                     /*!< USBPHYC peripheral clocks enable */
#define RCC_MC_APB4ENSETR_STGENROEN_Pos           (20U)
#define RCC_MC_APB4ENSETR_STGENROEN_Msk           (0x1U << RCC_MC_APB4ENSETR_STGENROEN_Pos)          /*!< 0x00100000 */
#define RCC_MC_APB4ENSETR_STGENROEN               RCC_MC_APB4ENSETR_STGENROEN_Msk                    /*!< STGEN Read-Only interface peripheral clocks enable */

/**************  Bit definition for RCC_MC_APB4ENCLRR register  ***************/
#define RCC_MC_APB4ENCLRR_LTDCEN_Pos              (0U)
#define RCC_MC_APB4ENCLRR_LTDCEN_Msk              (0x1U << RCC_MC_APB4ENCLRR_LTDCEN_Pos)             /*!< 0x00000001 */
#define RCC_MC_APB4ENCLRR_LTDCEN                  RCC_MC_APB4ENCLRR_LTDCEN_Msk                       /*!< LTDC peripheral clocks disable */
#define RCC_MC_APB4ENCLRR_DSIEN_Pos               (4U)
#define RCC_MC_APB4ENCLRR_DSIEN_Msk               (0x1U << RCC_MC_APB4ENCLRR_DSIEN_Pos)              /*!< 0x00000010 */
#define RCC_MC_APB4ENCLRR_DSIEN                   RCC_MC_APB4ENCLRR_DSIEN_Msk                        /*!< DSI peripheral clocks disable */
#define RCC_MC_APB4ENCLRR_DDRPERFMEN_Pos          (8U)
#define RCC_MC_APB4ENCLRR_DDRPERFMEN_Msk          (0x1U << RCC_MC_APB4ENCLRR_DDRPERFMEN_Pos)         /*!< 0x00000100 */
#define RCC_MC_APB4ENCLRR_DDRPERFMEN              RCC_MC_APB4ENCLRR_DDRPERFMEN_Msk                   /*!< DDRPERFM APB clock enable */
#define RCC_MC_APB4ENCLRR_USBPHYEN_Pos            (16U)
#define RCC_MC_APB4ENCLRR_USBPHYEN_Msk            (0x1U << RCC_MC_APB4ENCLRR_USBPHYEN_Pos)           /*!< 0x00010000 */
#define RCC_MC_APB4ENCLRR_USBPHYEN                RCC_MC_APB4ENCLRR_USBPHYEN_Msk                     /*!< USBPHYC peripheral clocks disable */
#define RCC_MC_APB4ENCLRR_STGENROEN_Pos           (20U)
#define RCC_MC_APB4ENCLRR_STGENROEN_Msk           (0x1U << RCC_MC_APB4ENCLRR_STGENROEN_Pos)          /*!< 0x00100000 */
#define RCC_MC_APB4ENCLRR_STGENROEN               RCC_MC_APB4ENCLRR_STGENROEN_Msk                    /*!< STGEN Read-Only interface peripheral clocks disable */

/**************  Bit definition for RCC_MC_APB5ENSETR register  ***************/
#define RCC_MC_APB5ENSETR_SPI6EN_Pos              (0U)
#define RCC_MC_APB5ENSETR_SPI6EN_Msk              (0x1U << RCC_MC_APB5ENSETR_SPI6EN_Pos)             /*!< 0x00000001 */
#define RCC_MC_APB5ENSETR_SPI6EN                  RCC_MC_APB5ENSETR_SPI6EN_Msk                       /*!< SPI6 peripheral clocks enable */
#define RCC_MC_APB5ENSETR_I2C4EN_Pos              (2U)
#define RCC_MC_APB5ENSETR_I2C4EN_Msk              (0x1U << RCC_MC_APB5ENSETR_I2C4EN_Pos)             /*!< 0x00000004 */
#define RCC_MC_APB5ENSETR_I2C4EN                  RCC_MC_APB5ENSETR_I2C4EN_Msk                       /*!< I2C4 peripheral clocks enable */
#define RCC_MC_APB5ENSETR_I2C6EN_Pos              (3U)
#define RCC_MC_APB5ENSETR_I2C6EN_Msk              (0x1U << RCC_MC_APB5ENSETR_I2C6EN_Pos)             /*!< 0x00000008 */
#define RCC_MC_APB5ENSETR_I2C6EN                  RCC_MC_APB5ENSETR_I2C6EN_Msk                       /*!< I2C6 peripheral clocks enable */
#define RCC_MC_APB5ENSETR_USART1EN_Pos            (4U)
#define RCC_MC_APB5ENSETR_USART1EN_Msk            (0x1U << RCC_MC_APB5ENSETR_USART1EN_Pos)           /*!< 0x00000010 */
#define RCC_MC_APB5ENSETR_USART1EN                RCC_MC_APB5ENSETR_USART1EN_Msk                     /*!< USART1 peripheral clocks enable */
#define RCC_MC_APB5ENSETR_RTCAPBEN_Pos            (8U)
#define RCC_MC_APB5ENSETR_RTCAPBEN_Msk            (0x1U << RCC_MC_APB5ENSETR_RTCAPBEN_Pos)           /*!< 0x00000100 */
#define RCC_MC_APB5ENSETR_RTCAPBEN                RCC_MC_APB5ENSETR_RTCAPBEN_Msk                     /*!< RTC APB clock enable */
#define RCC_MC_APB5ENSETR_TZC1EN_Pos              (11U)
#define RCC_MC_APB5ENSETR_TZC1EN_Msk              (0x1U << RCC_MC_APB5ENSETR_TZC1EN_Pos)             /*!< 0x00000800 */
#define RCC_MC_APB5ENSETR_TZC1EN                  RCC_MC_APB5ENSETR_TZC1EN_Msk                       /*!< TZC AXI port 1 clocks enable */
#define RCC_MC_APB5ENSETR_TZC2EN_Pos              (12U)
#define RCC_MC_APB5ENSETR_TZC2EN_Msk              (0x1U << RCC_MC_APB5ENSETR_TZC2EN_Pos)             /*!< 0x00001000 */
#define RCC_MC_APB5ENSETR_TZC2EN                  RCC_MC_APB5ENSETR_TZC2EN_Msk                       /*!< TZC AXI port 2 clocks enable */
#define RCC_MC_APB5ENSETR_TZPCEN_Pos              (13U)
#define RCC_MC_APB5ENSETR_TZPCEN_Msk              (0x1U << RCC_MC_APB5ENSETR_TZPCEN_Pos)             /*!< 0x00002000 */
#define RCC_MC_APB5ENSETR_TZPCEN                  RCC_MC_APB5ENSETR_TZPCEN_Msk                       /*!< TZPC peripheral clocks enable */
#define RCC_MC_APB5ENSETR_BSECEN_Pos              (16U)
#define RCC_MC_APB5ENSETR_BSECEN_Msk              (0x1U << RCC_MC_APB5ENSETR_BSECEN_Pos)             /*!< 0x00010000 */
#define RCC_MC_APB5ENSETR_BSECEN                  RCC_MC_APB5ENSETR_BSECEN_Msk                       /*!< BSEC peripheral clocks enable */
#define RCC_MC_APB5ENSETR_STGENEN_Pos             (20U)
#define RCC_MC_APB5ENSETR_STGENEN_Msk             (0x1U << RCC_MC_APB5ENSETR_STGENEN_Pos)            /*!< 0x00100000 */
#define RCC_MC_APB5ENSETR_STGENEN                 RCC_MC_APB5ENSETR_STGENEN_Msk                      /*!< STGEN Controller part, peripheral clocks enable */

/**************  Bit definition for RCC_MC_APB5ENCLRR register  ***************/
#define RCC_MC_APB5ENCLRR_SPI6EN_Pos              (0U)
#define RCC_MC_APB5ENCLRR_SPI6EN_Msk              (0x1U << RCC_MC_APB5ENCLRR_SPI6EN_Pos)             /*!< 0x00000001 */
#define RCC_MC_APB5ENCLRR_SPI6EN                  RCC_MC_APB5ENCLRR_SPI6EN_Msk                       /*!< SPI6 peripheral clocks disable */
#define RCC_MC_APB5ENCLRR_I2C4EN_Pos              (2U)
#define RCC_MC_APB5ENCLRR_I2C4EN_Msk              (0x1U << RCC_MC_APB5ENCLRR_I2C4EN_Pos)             /*!< 0x00000004 */
#define RCC_MC_APB5ENCLRR_I2C4EN                  RCC_MC_APB5ENCLRR_I2C4EN_Msk                       /*!< I2C4 peripheral clocks disable */
#define RCC_MC_APB5ENCLRR_I2C6EN_Pos              (3U)
#define RCC_MC_APB5ENCLRR_I2C6EN_Msk              (0x1U << RCC_MC_APB5ENCLRR_I2C6EN_Pos)             /*!< 0x00000008 */
#define RCC_MC_APB5ENCLRR_I2C6EN                  RCC_MC_APB5ENCLRR_I2C6EN_Msk                       /*!< I2C6 peripheral clocks disable */
#define RCC_MC_APB5ENCLRR_USART1EN_Pos            (4U)
#define RCC_MC_APB5ENCLRR_USART1EN_Msk            (0x1U << RCC_MC_APB5ENCLRR_USART1EN_Pos)           /*!< 0x00000010 */
#define RCC_MC_APB5ENCLRR_USART1EN                RCC_MC_APB5ENCLRR_USART1EN_Msk                     /*!< USART1 peripheral clocks disable */
#define RCC_MC_APB5ENCLRR_RTCAPBEN_Pos            (8U)
#define RCC_MC_APB5ENCLRR_RTCAPBEN_Msk            (0x1U << RCC_MC_APB5ENCLRR_RTCAPBEN_Pos)           /*!< 0x00000100 */
#define RCC_MC_APB5ENCLRR_RTCAPBEN                RCC_MC_APB5ENCLRR_RTCAPBEN_Msk                     /*!< RTC APB clock disable */
#define RCC_MC_APB5ENCLRR_TZC1EN_Pos              (11U)
#define RCC_MC_APB5ENCLRR_TZC1EN_Msk              (0x1U << RCC_MC_APB5ENCLRR_TZC1EN_Pos)             /*!< 0x00000800 */
#define RCC_MC_APB5ENCLRR_TZC1EN                  RCC_MC_APB5ENCLRR_TZC1EN_Msk                       /*!< TZC AXI port 1 clocks disable */
#define RCC_MC_APB5ENCLRR_TZC2EN_Pos              (12U)
#define RCC_MC_APB5ENCLRR_TZC2EN_Msk              (0x1U << RCC_MC_APB5ENCLRR_TZC2EN_Pos)             /*!< 0x00001000 */
#define RCC_MC_APB5ENCLRR_TZC2EN                  RCC_MC_APB5ENCLRR_TZC2EN_Msk                       /*!< TZC AXI port 2 clocks disable */
#define RCC_MC_APB5ENCLRR_TZPCEN_Pos              (13U)
#define RCC_MC_APB5ENCLRR_TZPCEN_Msk              (0x1U << RCC_MC_APB5ENCLRR_TZPCEN_Pos)             /*!< 0x00002000 */
#define RCC_MC_APB5ENCLRR_TZPCEN                  RCC_MC_APB5ENCLRR_TZPCEN_Msk                       /*!< TZPC peripheral clocks disable */
#define RCC_MC_APB5ENCLRR_BSECEN_Pos              (16U)
#define RCC_MC_APB5ENCLRR_BSECEN_Msk              (0x1U << RCC_MC_APB5ENCLRR_BSECEN_Pos)             /*!< 0x00010000 */
#define RCC_MC_APB5ENCLRR_BSECEN                  RCC_MC_APB5ENCLRR_BSECEN_Msk                       /*!< BSEC peripheral clocks disable */
#define RCC_MC_APB5ENCLRR_STGENEN_Pos             (20U)
#define RCC_MC_APB5ENCLRR_STGENEN_Msk             (0x1U << RCC_MC_APB5ENCLRR_STGENEN_Pos)            /*!< 0x00100000 */
#define RCC_MC_APB5ENCLRR_STGENEN                 RCC_MC_APB5ENCLRR_STGENEN_Msk                      /*!< STGEN Controller part, peripheral clocks disable */

/**************  Bit definition for RCC_MC_AHB5ENSETR register  ***************/
#define RCC_MC_AHB5ENSETR_GPIOZEN_Pos             (0U)
#define RCC_MC_AHB5ENSETR_GPIOZEN_Msk             (0x1U << RCC_MC_AHB5ENSETR_GPIOZEN_Pos)            /*!< 0x00000001 */
#define RCC_MC_AHB5ENSETR_GPIOZEN                 RCC_MC_AHB5ENSETR_GPIOZEN_Msk                      /*!< GPIOZ Secure peripheral clocks enable */
#define RCC_MC_AHB5ENSETR_CRYP1EN_Pos             (4U)
#define RCC_MC_AHB5ENSETR_CRYP1EN_Msk             (0x1U << RCC_MC_AHB5ENSETR_CRYP1EN_Pos)            /*!< 0x00000010 */
#define RCC_MC_AHB5ENSETR_CRYP1EN                 RCC_MC_AHB5ENSETR_CRYP1EN_Msk                      /*!< CRYP1 (3DES/AES1) peripheral clocks enable */
#define RCC_MC_AHB5ENSETR_HASH1EN_Pos             (5U)
#define RCC_MC_AHB5ENSETR_HASH1EN_Msk             (0x1U << RCC_MC_AHB5ENSETR_HASH1EN_Pos)            /*!< 0x00000020 */
#define RCC_MC_AHB5ENSETR_HASH1EN                 RCC_MC_AHB5ENSETR_HASH1EN_Msk                      /*!< HASH1 peripheral clocks enable */
#define RCC_MC_AHB5ENSETR_RNG1EN_Pos              (6U)
#define RCC_MC_AHB5ENSETR_RNG1EN_Msk              (0x1U << RCC_MC_AHB5ENSETR_RNG1EN_Pos)             /*!< 0x00000040 */
#define RCC_MC_AHB5ENSETR_RNG1EN                  RCC_MC_AHB5ENSETR_RNG1EN_Msk                       /*!< RNG1 peripheral clocks enable */
#define RCC_MC_AHB5ENSETR_BKPSRAMEN_Pos           (8U)
#define RCC_MC_AHB5ENSETR_BKPSRAMEN_Msk           (0x1U << RCC_MC_AHB5ENSETR_BKPSRAMEN_Pos)          /*!< 0x00000100 */
#define RCC_MC_AHB5ENSETR_BKPSRAMEN               RCC_MC_AHB5ENSETR_BKPSRAMEN_Msk                    /*!< BKPSRAM clocks enable */

/**************  Bit definition for RCC_MC_AHB5ENCLRR register  ***************/
#define RCC_MC_AHB5ENCLRR_GPIOZEN_Pos             (0U)
#define RCC_MC_AHB5ENCLRR_GPIOZEN_Msk             (0x1U << RCC_MC_AHB5ENCLRR_GPIOZEN_Pos)            /*!< 0x00000001 */
#define RCC_MC_AHB5ENCLRR_GPIOZEN                 RCC_MC_AHB5ENCLRR_GPIOZEN_Msk                      /*!< GPIOZ Secure peripheral clocks enable */
#define RCC_MC_AHB5ENCLRR_CRYP1EN_Pos             (4U)
#define RCC_MC_AHB5ENCLRR_CRYP1EN_Msk             (0x1U << RCC_MC_AHB5ENCLRR_CRYP1EN_Pos)            /*!< 0x00000010 */
#define RCC_MC_AHB5ENCLRR_CRYP1EN                 RCC_MC_AHB5ENCLRR_CRYP1EN_Msk                      /*!< CRYP1 (3DES/AES1) peripheral clocks enable */
#define RCC_MC_AHB5ENCLRR_HASH1EN_Pos             (5U)
#define RCC_MC_AHB5ENCLRR_HASH1EN_Msk             (0x1U << RCC_MC_AHB5ENCLRR_HASH1EN_Pos)            /*!< 0x00000020 */
#define RCC_MC_AHB5ENCLRR_HASH1EN                 RCC_MC_AHB5ENCLRR_HASH1EN_Msk                      /*!< HASH1 peripheral clocks enable */
#define RCC_MC_AHB5ENCLRR_RNG1EN_Pos              (6U)
#define RCC_MC_AHB5ENCLRR_RNG1EN_Msk              (0x1U << RCC_MC_AHB5ENCLRR_RNG1EN_Pos)             /*!< 0x00000040 */
#define RCC_MC_AHB5ENCLRR_RNG1EN                  RCC_MC_AHB5ENCLRR_RNG1EN_Msk                       /*!< RNG1 peripheral clocks enable */
#define RCC_MC_AHB5ENCLRR_BKPSRAMEN_Pos           (8U)
#define RCC_MC_AHB5ENCLRR_BKPSRAMEN_Msk           (0x1U << RCC_MC_AHB5ENCLRR_BKPSRAMEN_Pos)          /*!< 0x00000100 */
#define RCC_MC_AHB5ENCLRR_BKPSRAMEN               RCC_MC_AHB5ENCLRR_BKPSRAMEN_Msk                    /*!< BKPSRAM clocks enable */

/**************  Bit definition for RCC_MC_AHB6ENSETR register  ***************/
#define RCC_MC_AHB6ENSETR_MDMAEN_Pos              (0U)
#define RCC_MC_AHB6ENSETR_MDMAEN_Msk              (0x1U << RCC_MC_AHB6ENSETR_MDMAEN_Pos)             /*!< 0x00000001 */
#define RCC_MC_AHB6ENSETR_MDMAEN                  RCC_MC_AHB6ENSETR_MDMAEN_Msk                       /*!< MDMA peripheral clocks enable */
#define RCC_MC_AHB6ENSETR_GPUEN_Pos               (5U)
#define RCC_MC_AHB6ENSETR_GPUEN_Msk               (0x1U << RCC_MC_AHB6ENSETR_GPUEN_Pos)              /*!< 0x00000020 */
#define RCC_MC_AHB6ENSETR_GPUEN                   RCC_MC_AHB6ENSETR_GPUEN_Msk                        /*!< GPU peripheral clocks enable */
#define RCC_MC_AHB6ENSETR_ETHCKEN_Pos             (7U)
#define RCC_MC_AHB6ENSETR_ETHCKEN_Msk             (0x1U << RCC_MC_AHB6ENSETR_ETHCKEN_Pos)            /*!< 0x00000080 */
#define RCC_MC_AHB6ENSETR_ETHCKEN                 RCC_MC_AHB6ENSETR_ETHCKEN_Msk                      /*!< Enable of the Ethernet clock generated by the RCC (eth_ker_ck) */
#define RCC_MC_AHB6ENSETR_ETHTXEN_Pos             (8U)
#define RCC_MC_AHB6ENSETR_ETHTXEN_Msk             (0x1U << RCC_MC_AHB6ENSETR_ETHTXEN_Pos)            /*!< 0x00000100 */
#define RCC_MC_AHB6ENSETR_ETHTXEN                 RCC_MC_AHB6ENSETR_ETHTXEN_Msk                      /*!< Ethernet Transmission Clock Enable */
#define RCC_MC_AHB6ENSETR_ETHRXEN_Pos             (9U)
#define RCC_MC_AHB6ENSETR_ETHRXEN_Msk             (0x1U << RCC_MC_AHB6ENSETR_ETHRXEN_Pos)            /*!< 0x00000200 */
#define RCC_MC_AHB6ENSETR_ETHRXEN                 RCC_MC_AHB6ENSETR_ETHRXEN_Msk                      /*!< Ethernet Reception Clock Enable */
#define RCC_MC_AHB6ENSETR_ETHMACEN_Pos            (10U)
#define RCC_MC_AHB6ENSETR_ETHMACEN_Msk            (0x1U << RCC_MC_AHB6ENSETR_ETHMACEN_Pos)           /*!< 0x00000400 */
#define RCC_MC_AHB6ENSETR_ETHMACEN                RCC_MC_AHB6ENSETR_ETHMACEN_Msk                     /*!< Ethernet MAC bus interface Clock Enable (hclk6 and aclk) */
#define RCC_MC_AHB6ENSETR_FMCEN_Pos               (12U)
#define RCC_MC_AHB6ENSETR_FMCEN_Msk               (0x1U << RCC_MC_AHB6ENSETR_FMCEN_Pos)              /*!< 0x00001000 */
#define RCC_MC_AHB6ENSETR_FMCEN                   RCC_MC_AHB6ENSETR_FMCEN_Msk                        /*!< FMC peripheral clocks enable */
#define RCC_MC_AHB6ENSETR_QSPIEN_Pos              (14U)
#define RCC_MC_AHB6ENSETR_QSPIEN_Msk              (0x1U << RCC_MC_AHB6ENSETR_QSPIEN_Pos)             /*!< 0x00004000 */
#define RCC_MC_AHB6ENSETR_QSPIEN                  RCC_MC_AHB6ENSETR_QSPIEN_Msk                       /*!< QUADSPI peripheral clocks enable */
#define RCC_MC_AHB6ENSETR_SDMMC1EN_Pos            (16U)
#define RCC_MC_AHB6ENSETR_SDMMC1EN_Msk            (0x1U << RCC_MC_AHB6ENSETR_SDMMC1EN_Pos)           /*!< 0x00010000 */
#define RCC_MC_AHB6ENSETR_SDMMC1EN                RCC_MC_AHB6ENSETR_SDMMC1EN_Msk                     /*!< SDMMC1 and SDMMC1 delay (DLYBSD1) block peripheral clocks enable */
#define RCC_MC_AHB6ENSETR_SDMMC2EN_Pos            (17U)
#define RCC_MC_AHB6ENSETR_SDMMC2EN_Msk            (0x1U << RCC_MC_AHB6ENSETR_SDMMC2EN_Pos)           /*!< 0x00020000 */
#define RCC_MC_AHB6ENSETR_SDMMC2EN                RCC_MC_AHB6ENSETR_SDMMC2EN_Msk                     /*!< SDMMC2 and SDMMC2 delay (DLYBSD2) block peripheral clocks enable */
#define RCC_MC_AHB6ENSETR_CRC1EN_Pos              (20U)
#define RCC_MC_AHB6ENSETR_CRC1EN_Msk              (0x1U << RCC_MC_AHB6ENSETR_CRC1EN_Pos)             /*!< 0x00100000 */
#define RCC_MC_AHB6ENSETR_CRC1EN                  RCC_MC_AHB6ENSETR_CRC1EN_Msk                       /*!< CRC1 peripheral clocks enable */
#define RCC_MC_AHB6ENSETR_USBHEN_Pos              (24U)
#define RCC_MC_AHB6ENSETR_USBHEN_Msk              (0x1U << RCC_MC_AHB6ENSETR_USBHEN_Pos)             /*!< 0x01000000 */
#define RCC_MC_AHB6ENSETR_USBHEN                  RCC_MC_AHB6ENSETR_USBHEN_Msk                       /*!< USBH peripheral clocks enable */

/**************  Bit definition for RCC_MC_AHB6ENCLRR register  ***************/
#define RCC_MC_AHB6ENCLRR_MDMAEN_Pos              (0U)
#define RCC_MC_AHB6ENCLRR_MDMAEN_Msk              (0x1U << RCC_MC_AHB6ENCLRR_MDMAEN_Pos)             /*!< 0x00000001 */
#define RCC_MC_AHB6ENCLRR_MDMAEN                  RCC_MC_AHB6ENCLRR_MDMAEN_Msk                       /*!< MDMA peripheral clocks enable */
#define RCC_MC_AHB6ENCLRR_GPUEN_Pos               (5U)
#define RCC_MC_AHB6ENCLRR_GPUEN_Msk               (0x1U << RCC_MC_AHB6ENCLRR_GPUEN_Pos)              /*!< 0x00000020 */
#define RCC_MC_AHB6ENCLRR_GPUEN                   RCC_MC_AHB6ENCLRR_GPUEN_Msk                        /*!< GPU peripheral clocks enable */
#define RCC_MC_AHB6ENCLRR_ETHCKEN_Pos             (7U)
#define RCC_MC_AHB6ENCLRR_ETHCKEN_Msk             (0x1U << RCC_MC_AHB6ENCLRR_ETHCKEN_Pos)            /*!< 0x00000080 */
#define RCC_MC_AHB6ENCLRR_ETHCKEN                 RCC_MC_AHB6ENCLRR_ETHCKEN_Msk                      /*!< Disable of the Ethernet clock generated by the RCC (eth_ker_ck) */
#define RCC_MC_AHB6ENCLRR_ETHTXEN_Pos             (8U)
#define RCC_MC_AHB6ENCLRR_ETHTXEN_Msk             (0x1U << RCC_MC_AHB6ENCLRR_ETHTXEN_Pos)            /*!< 0x00000100 */
#define RCC_MC_AHB6ENCLRR_ETHTXEN                 RCC_MC_AHB6ENCLRR_ETHTXEN_Msk                      /*!< Disable of the Ethernet Transmission Clock */
#define RCC_MC_AHB6ENCLRR_ETHRXEN_Pos             (9U)
#define RCC_MC_AHB6ENCLRR_ETHRXEN_Msk             (0x1U << RCC_MC_AHB6ENCLRR_ETHRXEN_Pos)            /*!< 0x00000200 */
#define RCC_MC_AHB6ENCLRR_ETHRXEN                 RCC_MC_AHB6ENCLRR_ETHRXEN_Msk                      /*!< Disable of the Ethernet Reception Clock */
#define RCC_MC_AHB6ENCLRR_ETHMACEN_Pos            (10U)
#define RCC_MC_AHB6ENCLRR_ETHMACEN_Msk            (0x1U << RCC_MC_AHB6ENCLRR_ETHMACEN_Pos)           /*!< 0x00000400 */
#define RCC_MC_AHB6ENCLRR_ETHMACEN                RCC_MC_AHB6ENCLRR_ETHMACEN_Msk                     /*!< Disable of the bus interface clock for ETH block (hclk6 and aclk) */
#define RCC_MC_AHB6ENCLRR_FMCEN_Pos               (12U)
#define RCC_MC_AHB6ENCLRR_FMCEN_Msk               (0x1U << RCC_MC_AHB6ENCLRR_FMCEN_Pos)              /*!< 0x00001000 */
#define RCC_MC_AHB6ENCLRR_FMCEN                   RCC_MC_AHB6ENCLRR_FMCEN_Msk                        /*!< FMC peripheral clocks enable */
#define RCC_MC_AHB6ENCLRR_QSPIEN_Pos              (14U)
#define RCC_MC_AHB6ENCLRR_QSPIEN_Msk              (0x1U << RCC_MC_AHB6ENCLRR_QSPIEN_Pos)             /*!< 0x00004000 */
#define RCC_MC_AHB6ENCLRR_QSPIEN                  RCC_MC_AHB6ENCLRR_QSPIEN_Msk                       /*!< QUADSPI and QUADSPI delay block peripheral clocks enable */
#define RCC_MC_AHB6ENCLRR_SDMMC1EN_Pos            (16U)
#define RCC_MC_AHB6ENCLRR_SDMMC1EN_Msk            (0x1U << RCC_MC_AHB6ENCLRR_SDMMC1EN_Pos)           /*!< 0x00010000 */
#define RCC_MC_AHB6ENCLRR_SDMMC1EN                RCC_MC_AHB6ENCLRR_SDMMC1EN_Msk                     /*!< SDMMC1 and SDMMC1 delay (DLYBSD1) block peripheral clocks enable */
#define RCC_MC_AHB6ENCLRR_SDMMC2EN_Pos            (17U)
#define RCC_MC_AHB6ENCLRR_SDMMC2EN_Msk            (0x1U << RCC_MC_AHB6ENCLRR_SDMMC2EN_Pos)           /*!< 0x00020000 */
#define RCC_MC_AHB6ENCLRR_SDMMC2EN                RCC_MC_AHB6ENCLRR_SDMMC2EN_Msk                     /*!< SDMMC2 and SDMMC2 delay (DLYBSD2) block peripheral clocks enable */
#define RCC_MC_AHB6ENCLRR_CRC1EN_Pos              (20U)
#define RCC_MC_AHB6ENCLRR_CRC1EN_Msk              (0x1U << RCC_MC_AHB6ENCLRR_CRC1EN_Pos)             /*!< 0x00100000 */
#define RCC_MC_AHB6ENCLRR_CRC1EN                  RCC_MC_AHB6ENCLRR_CRC1EN_Msk                       /*!< CRC1 peripheral clocks enable */
#define RCC_MC_AHB6ENCLRR_USBHEN_Pos              (24U)
#define RCC_MC_AHB6ENCLRR_USBHEN_Msk              (0x1U << RCC_MC_AHB6ENCLRR_USBHEN_Pos)             /*!< 0x01000000 */
#define RCC_MC_AHB6ENCLRR_USBHEN                  RCC_MC_AHB6ENCLRR_USBHEN_Msk                       /*!< USBH peripheral clocks enable */

/*************  Bit definition for RCC_MP_APB4LPENSETR register  **************/
#define RCC_MP_APB4LPENSETR_LTDCLPEN_Pos          (0U)
#define RCC_MP_APB4LPENSETR_LTDCLPEN_Msk          (0x1U << RCC_MP_APB4LPENSETR_LTDCLPEN_Pos)         /*!< 0x00000001 */
#define RCC_MP_APB4LPENSETR_LTDCLPEN              RCC_MP_APB4LPENSETR_LTDCLPEN_Msk                   /*!< LTDC peripheral clocks enable during CSleep mode */
#define RCC_MP_APB4LPENSETR_DSILPEN_Pos           (4U)
#define RCC_MP_APB4LPENSETR_DSILPEN_Msk           (0x1U << RCC_MP_APB4LPENSETR_DSILPEN_Pos)          /*!< 0x00000010 */
#define RCC_MP_APB4LPENSETR_DSILPEN               RCC_MP_APB4LPENSETR_DSILPEN_Msk                    /*!< DSI peripheral clocks enable during CSleep mode */
#define RCC_MP_APB4LPENSETR_DDRPERFMLPEN_Pos      (8U)
#define RCC_MP_APB4LPENSETR_DDRPERFMLPEN_Msk      (0x1U << RCC_MP_APB4LPENSETR_DDRPERFMLPEN_Pos)     /*!< 0x00000100 */
#define RCC_MP_APB4LPENSETR_DDRPERFMLPEN          RCC_MP_APB4LPENSETR_DDRPERFMLPEN_Msk               /*!< DDRPERFM APB clock enable during CSleep mode */
#define RCC_MP_APB4LPENSETR_IWDG2APBLPEN_Pos      (15U)
#define RCC_MP_APB4LPENSETR_IWDG2APBLPEN_Msk      (0x1U << RCC_MP_APB4LPENSETR_IWDG2APBLPEN_Pos)     /*!< 0x00008000 */
#define RCC_MP_APB4LPENSETR_IWDG2APBLPEN          RCC_MP_APB4LPENSETR_IWDG2APBLPEN_Msk               /*!< IWDG2 APB clock enable during CSleep mode */
#define RCC_MP_APB4LPENSETR_USBPHYLPEN_Pos        (16U)
#define RCC_MP_APB4LPENSETR_USBPHYLPEN_Msk        (0x1U << RCC_MP_APB4LPENSETR_USBPHYLPEN_Pos)       /*!< 0x00010000 */
#define RCC_MP_APB4LPENSETR_USBPHYLPEN            RCC_MP_APB4LPENSETR_USBPHYLPEN_Msk                 /*!< USBPHYC peripheral clocks enable during CSleep mode */
#define RCC_MP_APB4LPENSETR_STGENROLPEN_Pos       (20U)
#define RCC_MP_APB4LPENSETR_STGENROLPEN_Msk       (0x1U << RCC_MP_APB4LPENSETR_STGENROLPEN_Pos)      /*!< 0x00100000 */
#define RCC_MP_APB4LPENSETR_STGENROLPEN           RCC_MP_APB4LPENSETR_STGENROLPEN_Msk                /*!< STGEN Read-Only Interface peripheral clocks enable during CSleep mode */
#define RCC_MP_APB4LPENSETR_STGENROSTPEN_Pos      (21U)
#define RCC_MP_APB4LPENSETR_STGENROSTPEN_Msk      (0x1U << RCC_MP_APB4LPENSETR_STGENROSTPEN_Pos)     /*!< 0x00200000 */
#define RCC_MP_APB4LPENSETR_STGENROSTPEN          RCC_MP_APB4LPENSETR_STGENROSTPEN_Msk               /*!< STGEN Read-Only Interface, clock enable during CStop mode */

/*************  Bit definition for RCC_MP_APB4LPENCLRR register  **************/
#define RCC_MP_APB4LPENCLRR_LTDCLPEN_Pos          (0U)
#define RCC_MP_APB4LPENCLRR_LTDCLPEN_Msk          (0x1U << RCC_MP_APB4LPENCLRR_LTDCLPEN_Pos)         /*!< 0x00000001 */
#define RCC_MP_APB4LPENCLRR_LTDCLPEN              RCC_MP_APB4LPENCLRR_LTDCLPEN_Msk                   /*!< LTDC peripheral clocks enable during CSleep mode */
#define RCC_MP_APB4LPENCLRR_DSILPEN_Pos           (4U)
#define RCC_MP_APB4LPENCLRR_DSILPEN_Msk           (0x1U << RCC_MP_APB4LPENCLRR_DSILPEN_Pos)          /*!< 0x00000010 */
#define RCC_MP_APB4LPENCLRR_DSILPEN               RCC_MP_APB4LPENCLRR_DSILPEN_Msk                    /*!< DSI peripheral clocks enable during CSleep mode */
#define RCC_MP_APB4LPENCLRR_DDRPERFMLPEN_Pos      (8U)
#define RCC_MP_APB4LPENCLRR_DDRPERFMLPEN_Msk      (0x1U << RCC_MP_APB4LPENCLRR_DDRPERFMLPEN_Pos)     /*!< 0x00000100 */
#define RCC_MP_APB4LPENCLRR_DDRPERFMLPEN          RCC_MP_APB4LPENCLRR_DDRPERFMLPEN_Msk               /*!< DDRPERFM APB clock enable during CSleep mode */
#define RCC_MP_APB4LPENCLRR_IWDG2APBLPEN_Pos      (15U)
#define RCC_MP_APB4LPENCLRR_IWDG2APBLPEN_Msk      (0x1U << RCC_MP_APB4LPENCLRR_IWDG2APBLPEN_Pos)     /*!< 0x00008000 */
#define RCC_MP_APB4LPENCLRR_IWDG2APBLPEN          RCC_MP_APB4LPENCLRR_IWDG2APBLPEN_Msk               /*!< IWDG2 APB clock enable during CSleep mode */
#define RCC_MP_APB4LPENCLRR_USBPHYLPEN_Pos        (16U)
#define RCC_MP_APB4LPENCLRR_USBPHYLPEN_Msk        (0x1U << RCC_MP_APB4LPENCLRR_USBPHYLPEN_Pos)       /*!< 0x00010000 */
#define RCC_MP_APB4LPENCLRR_USBPHYLPEN            RCC_MP_APB4LPENCLRR_USBPHYLPEN_Msk                 /*!< USBPHYC peripheral clocks enable during CSleep mode */
#define RCC_MP_APB4LPENCLRR_STGENROLPEN_Pos       (20U)
#define RCC_MP_APB4LPENCLRR_STGENROLPEN_Msk       (0x1U << RCC_MP_APB4LPENCLRR_STGENROLPEN_Pos)      /*!< 0x00100000 */
#define RCC_MP_APB4LPENCLRR_STGENROLPEN           RCC_MP_APB4LPENCLRR_STGENROLPEN_Msk                /*!< STGEN Read-Only Interface peripheral clocks enable during CSleep mode */
#define RCC_MP_APB4LPENCLRR_STGENROSTPEN_Pos      (21U)
#define RCC_MP_APB4LPENCLRR_STGENROSTPEN_Msk      (0x1U << RCC_MP_APB4LPENCLRR_STGENROSTPEN_Pos)     /*!< 0x00200000 */
#define RCC_MP_APB4LPENCLRR_STGENROSTPEN          RCC_MP_APB4LPENCLRR_STGENROSTPEN_Msk               /*!< STGEN Read-Only Interface clock enable during CStop mode */

/*************  Bit definition for RCC_MP_APB5LPENSETR register  **************/
#define RCC_MP_APB5LPENSETR_SPI6LPEN_Pos          (0U)
#define RCC_MP_APB5LPENSETR_SPI6LPEN_Msk          (0x1U << RCC_MP_APB5LPENSETR_SPI6LPEN_Pos)         /*!< 0x00000001 */
#define RCC_MP_APB5LPENSETR_SPI6LPEN              RCC_MP_APB5LPENSETR_SPI6LPEN_Msk                   /*!< SPI6 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB5LPENSETR_I2C4LPEN_Pos          (2U)
#define RCC_MP_APB5LPENSETR_I2C4LPEN_Msk          (0x1U << RCC_MP_APB5LPENSETR_I2C4LPEN_Pos)         /*!< 0x00000004 */
#define RCC_MP_APB5LPENSETR_I2C4LPEN              RCC_MP_APB5LPENSETR_I2C4LPEN_Msk                   /*!< I2C4 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB5LPENSETR_I2C6LPEN_Pos          (3U)
#define RCC_MP_APB5LPENSETR_I2C6LPEN_Msk          (0x1U << RCC_MP_APB5LPENSETR_I2C6LPEN_Pos)         /*!< 0x00000008 */
#define RCC_MP_APB5LPENSETR_I2C6LPEN              RCC_MP_APB5LPENSETR_I2C6LPEN_Msk                   /*!< I2C6 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB5LPENSETR_USART1LPEN_Pos        (4U)
#define RCC_MP_APB5LPENSETR_USART1LPEN_Msk        (0x1U << RCC_MP_APB5LPENSETR_USART1LPEN_Pos)       /*!< 0x00000010 */
#define RCC_MP_APB5LPENSETR_USART1LPEN            RCC_MP_APB5LPENSETR_USART1LPEN_Msk                 /*!< USART1 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB5LPENSETR_RTCAPBLPEN_Pos        (8U)
#define RCC_MP_APB5LPENSETR_RTCAPBLPEN_Msk        (0x1U << RCC_MP_APB5LPENSETR_RTCAPBLPEN_Pos)       /*!< 0x00000100 */
#define RCC_MP_APB5LPENSETR_RTCAPBLPEN            RCC_MP_APB5LPENSETR_RTCAPBLPEN_Msk                 /*!< RTC APB clock enable during CSleep mode */
#define RCC_MP_APB5LPENSETR_TZC1LPEN_Pos          (11U)
#define RCC_MP_APB5LPENSETR_TZC1LPEN_Msk          (0x1U << RCC_MP_APB5LPENSETR_TZC1LPEN_Pos)         /*!< 0x00000800 */
#define RCC_MP_APB5LPENSETR_TZC1LPEN              RCC_MP_APB5LPENSETR_TZC1LPEN_Msk                   /*!< TZC AXI port 1 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB5LPENSETR_TZC2LPEN_Pos          (12U)
#define RCC_MP_APB5LPENSETR_TZC2LPEN_Msk          (0x1U << RCC_MP_APB5LPENSETR_TZC2LPEN_Pos)         /*!< 0x00001000 */
#define RCC_MP_APB5LPENSETR_TZC2LPEN              RCC_MP_APB5LPENSETR_TZC2LPEN_Msk                   /*!< TZC AXI port 2 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB5LPENSETR_TZPCLPEN_Pos          (13U)
#define RCC_MP_APB5LPENSETR_TZPCLPEN_Msk          (0x1U << RCC_MP_APB5LPENSETR_TZPCLPEN_Pos)         /*!< 0x00002000 */
#define RCC_MP_APB5LPENSETR_TZPCLPEN              RCC_MP_APB5LPENSETR_TZPCLPEN_Msk                   /*!< TZPC peripheral clocks enable during CSleep mode */
#define RCC_MP_APB5LPENSETR_IWDG1APBLPEN_Pos      (15U)
#define RCC_MP_APB5LPENSETR_IWDG1APBLPEN_Msk      (0x1U << RCC_MP_APB5LPENSETR_IWDG1APBLPEN_Pos)     /*!< 0x00008000 */
#define RCC_MP_APB5LPENSETR_IWDG1APBLPEN          RCC_MP_APB5LPENSETR_IWDG1APBLPEN_Msk               /*!< IWDG1 APB clock enable during CSleep mode */
#define RCC_MP_APB5LPENSETR_BSECLPEN_Pos          (16U)
#define RCC_MP_APB5LPENSETR_BSECLPEN_Msk          (0x1U << RCC_MP_APB5LPENSETR_BSECLPEN_Pos)         /*!< 0x00010000 */
#define RCC_MP_APB5LPENSETR_BSECLPEN              RCC_MP_APB5LPENSETR_BSECLPEN_Msk                   /*!< BSEC peripheral clocks enable during CSleep mode */
#define RCC_MP_APB5LPENSETR_STGENLPEN_Pos         (20U)
#define RCC_MP_APB5LPENSETR_STGENLPEN_Msk         (0x1U << RCC_MP_APB5LPENSETR_STGENLPEN_Pos)        /*!< 0x00100000 */
#define RCC_MP_APB5LPENSETR_STGENLPEN             RCC_MP_APB5LPENSETR_STGENLPEN_Msk                  /*!< STGEN Controller part, peripheral clocks enable during CSleep mode */
#define RCC_MP_APB5LPENSETR_STGENSTPEN_Pos        (21U)
#define RCC_MP_APB5LPENSETR_STGENSTPEN_Msk        (0x1U << RCC_MP_APB5LPENSETR_STGENSTPEN_Pos)       /*!< 0x00200000 */
#define RCC_MP_APB5LPENSETR_STGENSTPEN            RCC_MP_APB5LPENSETR_STGENSTPEN_Msk                 /*!< STGEN Controller part, peripheral clocks enable during CStop mode */

/*************  Bit definition for RCC_MP_APB5LPENCLRR register  **************/
#define RCC_MP_APB5LPENCLRR_SPI6LPEN_Pos          (0U)
#define RCC_MP_APB5LPENCLRR_SPI6LPEN_Msk          (0x1U << RCC_MP_APB5LPENCLRR_SPI6LPEN_Pos)         /*!< 0x00000001 */
#define RCC_MP_APB5LPENCLRR_SPI6LPEN              RCC_MP_APB5LPENCLRR_SPI6LPEN_Msk                   /*!< SPI6 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB5LPENCLRR_I2C4LPEN_Pos          (2U)
#define RCC_MP_APB5LPENCLRR_I2C4LPEN_Msk          (0x1U << RCC_MP_APB5LPENCLRR_I2C4LPEN_Pos)         /*!< 0x00000004 */
#define RCC_MP_APB5LPENCLRR_I2C4LPEN              RCC_MP_APB5LPENCLRR_I2C4LPEN_Msk                   /*!< I2C4 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB5LPENCLRR_I2C6LPEN_Pos          (3U)
#define RCC_MP_APB5LPENCLRR_I2C6LPEN_Msk          (0x1U << RCC_MP_APB5LPENCLRR_I2C6LPEN_Pos)         /*!< 0x00000008 */
#define RCC_MP_APB5LPENCLRR_I2C6LPEN              RCC_MP_APB5LPENCLRR_I2C6LPEN_Msk                   /*!< I2C6 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB5LPENCLRR_USART1LPEN_Pos        (4U)
#define RCC_MP_APB5LPENCLRR_USART1LPEN_Msk        (0x1U << RCC_MP_APB5LPENCLRR_USART1LPEN_Pos)       /*!< 0x00000010 */
#define RCC_MP_APB5LPENCLRR_USART1LPEN            RCC_MP_APB5LPENCLRR_USART1LPEN_Msk                 /*!< USART1 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB5LPENCLRR_RTCAPBLPEN_Pos        (8U)
#define RCC_MP_APB5LPENCLRR_RTCAPBLPEN_Msk        (0x1U << RCC_MP_APB5LPENCLRR_RTCAPBLPEN_Pos)       /*!< 0x00000100 */
#define RCC_MP_APB5LPENCLRR_RTCAPBLPEN            RCC_MP_APB5LPENCLRR_RTCAPBLPEN_Msk                 /*!< RTC APB clock enable during CSleep mode */
#define RCC_MP_APB5LPENCLRR_TZC1LPEN_Pos          (11U)
#define RCC_MP_APB5LPENCLRR_TZC1LPEN_Msk          (0x1U << RCC_MP_APB5LPENCLRR_TZC1LPEN_Pos)         /*!< 0x00000800 */
#define RCC_MP_APB5LPENCLRR_TZC1LPEN              RCC_MP_APB5LPENCLRR_TZC1LPEN_Msk                   /*!< TZC AXI port 1 peripheral clocks disable during CSleep mode */
#define RCC_MP_APB5LPENCLRR_TZC2LPEN_Pos          (12U)
#define RCC_MP_APB5LPENCLRR_TZC2LPEN_Msk          (0x1U << RCC_MP_APB5LPENCLRR_TZC2LPEN_Pos)         /*!< 0x00001000 */
#define RCC_MP_APB5LPENCLRR_TZC2LPEN              RCC_MP_APB5LPENCLRR_TZC2LPEN_Msk                   /*!< TZC AXI port 2 peripheral clocks disable during CSleep mode */
#define RCC_MP_APB5LPENCLRR_TZPCLPEN_Pos          (13U)
#define RCC_MP_APB5LPENCLRR_TZPCLPEN_Msk          (0x1U << RCC_MP_APB5LPENCLRR_TZPCLPEN_Pos)         /*!< 0x00002000 */
#define RCC_MP_APB5LPENCLRR_TZPCLPEN              RCC_MP_APB5LPENCLRR_TZPCLPEN_Msk                   /*!< TZPC peripheral clocks enable during CSleep mode */
#define RCC_MP_APB5LPENCLRR_IWDG1APBLPEN_Pos      (15U)
#define RCC_MP_APB5LPENCLRR_IWDG1APBLPEN_Msk      (0x1U << RCC_MP_APB5LPENCLRR_IWDG1APBLPEN_Pos)     /*!< 0x00008000 */
#define RCC_MP_APB5LPENCLRR_IWDG1APBLPEN          RCC_MP_APB5LPENCLRR_IWDG1APBLPEN_Msk               /*!< IWDG1 APB clock enable during CSleep mode */
#define RCC_MP_APB5LPENCLRR_BSECLPEN_Pos          (16U)
#define RCC_MP_APB5LPENCLRR_BSECLPEN_Msk          (0x1U << RCC_MP_APB5LPENCLRR_BSECLPEN_Pos)         /*!< 0x00010000 */
#define RCC_MP_APB5LPENCLRR_BSECLPEN              RCC_MP_APB5LPENCLRR_BSECLPEN_Msk                   /*!< BSEC peripheral clocks enable during CSleep mode */
#define RCC_MP_APB5LPENCLRR_STGENLPEN_Pos         (20U)
#define RCC_MP_APB5LPENCLRR_STGENLPEN_Msk         (0x1U << RCC_MP_APB5LPENCLRR_STGENLPEN_Pos)        /*!< 0x00100000 */
#define RCC_MP_APB5LPENCLRR_STGENLPEN             RCC_MP_APB5LPENCLRR_STGENLPEN_Msk                  /*!< STGEN peripheral clocks enable during CSleep mode */
#define RCC_MP_APB5LPENCLRR_STGENSTPEN_Pos        (21U)
#define RCC_MP_APB5LPENCLRR_STGENSTPEN_Msk        (0x1U << RCC_MP_APB5LPENCLRR_STGENSTPEN_Pos)       /*!< 0x00200000 */
#define RCC_MP_APB5LPENCLRR_STGENSTPEN            RCC_MP_APB5LPENCLRR_STGENSTPEN_Msk                 /*!< STGEN peripheral clocks enable during CStop mode */

/*************  Bit definition for RCC_MP_AHB5LPENSETR register  **************/
#define RCC_MP_AHB5LPENSETR_GPIOZLPEN_Pos         (0U)
#define RCC_MP_AHB5LPENSETR_GPIOZLPEN_Msk         (0x1U << RCC_MP_AHB5LPENSETR_GPIOZLPEN_Pos)        /*!< 0x00000001 */
#define RCC_MP_AHB5LPENSETR_GPIOZLPEN             RCC_MP_AHB5LPENSETR_GPIOZLPEN_Msk                  /*!< GPIOZ Secure peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB5LPENSETR_CRYP1LPEN_Pos         (4U)
#define RCC_MP_AHB5LPENSETR_CRYP1LPEN_Msk         (0x1U << RCC_MP_AHB5LPENSETR_CRYP1LPEN_Pos)        /*!< 0x00000010 */
#define RCC_MP_AHB5LPENSETR_CRYP1LPEN             RCC_MP_AHB5LPENSETR_CRYP1LPEN_Msk                  /*!< CRYP1 (3DES/AES1) peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB5LPENSETR_HASH1LPEN_Pos         (5U)
#define RCC_MP_AHB5LPENSETR_HASH1LPEN_Msk         (0x1U << RCC_MP_AHB5LPENSETR_HASH1LPEN_Pos)        /*!< 0x00000020 */
#define RCC_MP_AHB5LPENSETR_HASH1LPEN             RCC_MP_AHB5LPENSETR_HASH1LPEN_Msk                  /*!< HASH1 peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB5LPENSETR_RNG1LPEN_Pos          (6U)
#define RCC_MP_AHB5LPENSETR_RNG1LPEN_Msk          (0x1U << RCC_MP_AHB5LPENSETR_RNG1LPEN_Pos)         /*!< 0x00000040 */
#define RCC_MP_AHB5LPENSETR_RNG1LPEN              RCC_MP_AHB5LPENSETR_RNG1LPEN_Msk                   /*!< RNG1 peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB5LPENSETR_BKPSRAMLPEN_Pos       (8U)
#define RCC_MP_AHB5LPENSETR_BKPSRAMLPEN_Msk       (0x1U << RCC_MP_AHB5LPENSETR_BKPSRAMLPEN_Pos)      /*!< 0x00000100 */
#define RCC_MP_AHB5LPENSETR_BKPSRAMLPEN           RCC_MP_AHB5LPENSETR_BKPSRAMLPEN_Msk                /*!< BKPSRAM clock enable during CSleep mode */

/*************  Bit definition for RCC_MP_AHB5LPENCLRR register  **************/
#define RCC_MP_AHB5LPENCLRR_GPIOZLPEN_Pos         (0U)
#define RCC_MP_AHB5LPENCLRR_GPIOZLPEN_Msk         (0x1U << RCC_MP_AHB5LPENCLRR_GPIOZLPEN_Pos)        /*!< 0x00000001 */
#define RCC_MP_AHB5LPENCLRR_GPIOZLPEN             RCC_MP_AHB5LPENCLRR_GPIOZLPEN_Msk                  /*!< GPIOZ Secure peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB5LPENCLRR_CRYP1LPEN_Pos         (4U)
#define RCC_MP_AHB5LPENCLRR_CRYP1LPEN_Msk         (0x1U << RCC_MP_AHB5LPENCLRR_CRYP1LPEN_Pos)        /*!< 0x00000010 */
#define RCC_MP_AHB5LPENCLRR_CRYP1LPEN             RCC_MP_AHB5LPENCLRR_CRYP1LPEN_Msk                  /*!< CRYP1 (3DES/AES1) peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB5LPENCLRR_HASH1LPEN_Pos         (5U)
#define RCC_MP_AHB5LPENCLRR_HASH1LPEN_Msk         (0x1U << RCC_MP_AHB5LPENCLRR_HASH1LPEN_Pos)        /*!< 0x00000020 */
#define RCC_MP_AHB5LPENCLRR_HASH1LPEN             RCC_MP_AHB5LPENCLRR_HASH1LPEN_Msk                  /*!< HASH1 peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB5LPENCLRR_RNG1LPEN_Pos          (6U)
#define RCC_MP_AHB5LPENCLRR_RNG1LPEN_Msk          (0x1U << RCC_MP_AHB5LPENCLRR_RNG1LPEN_Pos)         /*!< 0x00000040 */
#define RCC_MP_AHB5LPENCLRR_RNG1LPEN              RCC_MP_AHB5LPENCLRR_RNG1LPEN_Msk                   /*!< RNG1 peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB5LPENCLRR_BKPSRAMLPEN_Pos       (8U)
#define RCC_MP_AHB5LPENCLRR_BKPSRAMLPEN_Msk       (0x1U << RCC_MP_AHB5LPENCLRR_BKPSRAMLPEN_Pos)      /*!< 0x00000100 */
#define RCC_MP_AHB5LPENCLRR_BKPSRAMLPEN           RCC_MP_AHB5LPENCLRR_BKPSRAMLPEN_Msk                /*!< BKPSRAM clock enable during CSleep mode */

/*************  Bit definition for RCC_MP_AHB6LPENSETR register  **************/
#define RCC_MP_AHB6LPENSETR_MDMALPEN_Pos          (0U)
#define RCC_MP_AHB6LPENSETR_MDMALPEN_Msk          (0x1U << RCC_MP_AHB6LPENSETR_MDMALPEN_Pos)         /*!< 0x00000001 */
#define RCC_MP_AHB6LPENSETR_MDMALPEN              RCC_MP_AHB6LPENSETR_MDMALPEN_Msk                   /*!< MDMA peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB6LPENSETR_GPULPEN_Pos           (5U)
#define RCC_MP_AHB6LPENSETR_GPULPEN_Msk           (0x1U << RCC_MP_AHB6LPENSETR_GPULPEN_Pos)          /*!< 0x00000020 */
#define RCC_MP_AHB6LPENSETR_GPULPEN               RCC_MP_AHB6LPENSETR_GPULPEN_Msk                    /*!< GPU peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB6LPENSETR_ETHCKLPEN_Pos         (7U)
#define RCC_MP_AHB6LPENSETR_ETHCKLPEN_Msk         (0x1U << RCC_MP_AHB6LPENSETR_ETHCKLPEN_Pos)        /*!< 0x00000080 */
#define RCC_MP_AHB6LPENSETR_ETHCKLPEN             RCC_MP_AHB6LPENSETR_ETHCKLPEN_Msk                  /*!< Enable of the Ethernet clock generated by the RCC (eth_ker_ck) during CSleep mode */
#define RCC_MP_AHB6LPENSETR_ETHTXLPEN_Pos         (8U)
#define RCC_MP_AHB6LPENSETR_ETHTXLPEN_Msk         (0x1U << RCC_MP_AHB6LPENSETR_ETHTXLPEN_Pos)        /*!< 0x00000100 */
#define RCC_MP_AHB6LPENSETR_ETHTXLPEN             RCC_MP_AHB6LPENSETR_ETHTXLPEN_Msk                  /*!< Enable of the Ethernet Transmission Clock during CSleep mode */
#define RCC_MP_AHB6LPENSETR_ETHRXLPEN_Pos         (9U)
#define RCC_MP_AHB6LPENSETR_ETHRXLPEN_Msk         (0x1U << RCC_MP_AHB6LPENSETR_ETHRXLPEN_Pos)        /*!< 0x00000200 */
#define RCC_MP_AHB6LPENSETR_ETHRXLPEN             RCC_MP_AHB6LPENSETR_ETHRXLPEN_Msk                  /*!< Enable of the Ethernet Reception Clock during CSleep mode */
#define RCC_MP_AHB6LPENSETR_ETHMACLPEN_Pos        (10U)
#define RCC_MP_AHB6LPENSETR_ETHMACLPEN_Msk        (0x1U << RCC_MP_AHB6LPENSETR_ETHMACLPEN_Pos)       /*!< 0x00000400 */
#define RCC_MP_AHB6LPENSETR_ETHMACLPEN            RCC_MP_AHB6LPENSETR_ETHMACLPEN_Msk                 /*!< Enable of the bus interface clocks for ETH block during CSleep mode */
#define RCC_MP_AHB6LPENSETR_ETHSTPEN_Pos          (11U)
#define RCC_MP_AHB6LPENSETR_ETHSTPEN_Msk          (0x1U << RCC_MP_AHB6LPENSETR_ETHSTPEN_Pos)         /*!< 0x00000800 */
#define RCC_MP_AHB6LPENSETR_ETHSTPEN              RCC_MP_AHB6LPENSETR_ETHSTPEN_Msk                   /*!< ETH peripheral clock enable during CStop mode */
#define RCC_MP_AHB6LPENSETR_FMCLPEN_Pos           (12U)
#define RCC_MP_AHB6LPENSETR_FMCLPEN_Msk           (0x1U << RCC_MP_AHB6LPENSETR_FMCLPEN_Pos)          /*!< 0x00001000 */
#define RCC_MP_AHB6LPENSETR_FMCLPEN               RCC_MP_AHB6LPENSETR_FMCLPEN_Msk                    /*!< FMC peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB6LPENSETR_QSPILPEN_Pos          (14U)
#define RCC_MP_AHB6LPENSETR_QSPILPEN_Msk          (0x1U << RCC_MP_AHB6LPENSETR_QSPILPEN_Pos)         /*!< 0x00004000 */
#define RCC_MP_AHB6LPENSETR_QSPILPEN              RCC_MP_AHB6LPENSETR_QSPILPEN_Msk                   /*!< QUADSPI peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB6LPENSETR_SDMMC1LPEN_Pos        (16U)
#define RCC_MP_AHB6LPENSETR_SDMMC1LPEN_Msk        (0x1U << RCC_MP_AHB6LPENSETR_SDMMC1LPEN_Pos)       /*!< 0x00010000 */
#define RCC_MP_AHB6LPENSETR_SDMMC1LPEN            RCC_MP_AHB6LPENSETR_SDMMC1LPEN_Msk                 /*!< SDMMC1 and SDMMC1 delay (DLYBSD1) block peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB6LPENSETR_SDMMC2LPEN_Pos        (17U)
#define RCC_MP_AHB6LPENSETR_SDMMC2LPEN_Msk        (0x1U << RCC_MP_AHB6LPENSETR_SDMMC2LPEN_Pos)       /*!< 0x00020000 */
#define RCC_MP_AHB6LPENSETR_SDMMC2LPEN            RCC_MP_AHB6LPENSETR_SDMMC2LPEN_Msk                 /*!< SDMMC2 and SDMMC2 delay (DLYBSD2) block peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB6LPENSETR_CRC1LPEN_Pos          (20U)
#define RCC_MP_AHB6LPENSETR_CRC1LPEN_Msk          (0x1U << RCC_MP_AHB6LPENSETR_CRC1LPEN_Pos)         /*!< 0x00100000 */
#define RCC_MP_AHB6LPENSETR_CRC1LPEN              RCC_MP_AHB6LPENSETR_CRC1LPEN_Msk                   /*!< CRC1 peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB6LPENSETR_USBHLPEN_Pos          (24U)
#define RCC_MP_AHB6LPENSETR_USBHLPEN_Msk          (0x1U << RCC_MP_AHB6LPENSETR_USBHLPEN_Pos)         /*!< 0x01000000 */
#define RCC_MP_AHB6LPENSETR_USBHLPEN              RCC_MP_AHB6LPENSETR_USBHLPEN_Msk                   /*!< USBH peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MP_AHB6LPENCLRR register  **************/
#define RCC_MP_AHB6LPENCLRR_MDMALPEN_Pos          (0U)
#define RCC_MP_AHB6LPENCLRR_MDMALPEN_Msk          (0x1U << RCC_MP_AHB6LPENCLRR_MDMALPEN_Pos)         /*!< 0x00000001 */
#define RCC_MP_AHB6LPENCLRR_MDMALPEN              RCC_MP_AHB6LPENCLRR_MDMALPEN_Msk                   /*!< MDMA peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB6LPENCLRR_GPULPEN_Pos           (5U)
#define RCC_MP_AHB6LPENCLRR_GPULPEN_Msk           (0x1U << RCC_MP_AHB6LPENCLRR_GPULPEN_Pos)          /*!< 0x00000020 */
#define RCC_MP_AHB6LPENCLRR_GPULPEN               RCC_MP_AHB6LPENCLRR_GPULPEN_Msk                    /*!< GPU peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB6LPENCLRR_ETHCKLPEN_Pos         (7U)
#define RCC_MP_AHB6LPENCLRR_ETHCKLPEN_Msk         (0x1U << RCC_MP_AHB6LPENCLRR_ETHCKLPEN_Pos)        /*!< 0x00000080 */
#define RCC_MP_AHB6LPENCLRR_ETHCKLPEN             RCC_MP_AHB6LPENCLRR_ETHCKLPEN_Msk                  /*!< Disable of the Ethernet clock generated by the RCC (eth_ker_ck) during CSleep mode */
#define RCC_MP_AHB6LPENCLRR_ETHTXLPEN_Pos         (8U)
#define RCC_MP_AHB6LPENCLRR_ETHTXLPEN_Msk         (0x1U << RCC_MP_AHB6LPENCLRR_ETHTXLPEN_Pos)        /*!< 0x00000100 */
#define RCC_MP_AHB6LPENCLRR_ETHTXLPEN             RCC_MP_AHB6LPENCLRR_ETHTXLPEN_Msk                  /*!< Disable of the Ethernet Transmission Clock during CSleep mode */
#define RCC_MP_AHB6LPENCLRR_ETHRXLPEN_Pos         (9U)
#define RCC_MP_AHB6LPENCLRR_ETHRXLPEN_Msk         (0x1U << RCC_MP_AHB6LPENCLRR_ETHRXLPEN_Pos)        /*!< 0x00000200 */
#define RCC_MP_AHB6LPENCLRR_ETHRXLPEN             RCC_MP_AHB6LPENCLRR_ETHRXLPEN_Msk                  /*!< Disable of the Ethernet Reception Clock during CSleep mode */
#define RCC_MP_AHB6LPENCLRR_ETHMACLPEN_Pos        (10U)
#define RCC_MP_AHB6LPENCLRR_ETHMACLPEN_Msk        (0x1U << RCC_MP_AHB6LPENCLRR_ETHMACLPEN_Pos)       /*!< 0x00000400 */
#define RCC_MP_AHB6LPENCLRR_ETHMACLPEN            RCC_MP_AHB6LPENCLRR_ETHMACLPEN_Msk                 /*!< Disable of the bus interface clocks for ETH block during CSleep mode */
#define RCC_MP_AHB6LPENCLRR_ETHSTPEN_Pos          (11U)
#define RCC_MP_AHB6LPENCLRR_ETHSTPEN_Msk          (0x1U << RCC_MP_AHB6LPENCLRR_ETHSTPEN_Pos)         /*!< 0x00000800 */
#define RCC_MP_AHB6LPENCLRR_ETHSTPEN              RCC_MP_AHB6LPENCLRR_ETHSTPEN_Msk                   /*!< ETH peripheral clock enable during CStop mode */
#define RCC_MP_AHB6LPENCLRR_FMCLPEN_Pos           (12U)
#define RCC_MP_AHB6LPENCLRR_FMCLPEN_Msk           (0x1U << RCC_MP_AHB6LPENCLRR_FMCLPEN_Pos)          /*!< 0x00001000 */
#define RCC_MP_AHB6LPENCLRR_FMCLPEN               RCC_MP_AHB6LPENCLRR_FMCLPEN_Msk                    /*!< FMC peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB6LPENCLRR_QSPILPEN_Pos          (14U)
#define RCC_MP_AHB6LPENCLRR_QSPILPEN_Msk          (0x1U << RCC_MP_AHB6LPENCLRR_QSPILPEN_Pos)         /*!< 0x00004000 */
#define RCC_MP_AHB6LPENCLRR_QSPILPEN              RCC_MP_AHB6LPENCLRR_QSPILPEN_Msk                   /*!< QUADSPI peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB6LPENCLRR_SDMMC1LPEN_Pos        (16U)
#define RCC_MP_AHB6LPENCLRR_SDMMC1LPEN_Msk        (0x1U << RCC_MP_AHB6LPENCLRR_SDMMC1LPEN_Pos)       /*!< 0x00010000 */
#define RCC_MP_AHB6LPENCLRR_SDMMC1LPEN            RCC_MP_AHB6LPENCLRR_SDMMC1LPEN_Msk                 /*!< SDMMC1 and SDMMC1 delay (DLYBSD1) block peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB6LPENCLRR_SDMMC2LPEN_Pos        (17U)
#define RCC_MP_AHB6LPENCLRR_SDMMC2LPEN_Msk        (0x1U << RCC_MP_AHB6LPENCLRR_SDMMC2LPEN_Pos)       /*!< 0x00020000 */
#define RCC_MP_AHB6LPENCLRR_SDMMC2LPEN            RCC_MP_AHB6LPENCLRR_SDMMC2LPEN_Msk                 /*!< SDMMC2 and SDMMC2 delay (DLYBSD2) block peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB6LPENCLRR_CRC1LPEN_Pos          (20U)
#define RCC_MP_AHB6LPENCLRR_CRC1LPEN_Msk          (0x1U << RCC_MP_AHB6LPENCLRR_CRC1LPEN_Pos)         /*!< 0x00100000 */
#define RCC_MP_AHB6LPENCLRR_CRC1LPEN              RCC_MP_AHB6LPENCLRR_CRC1LPEN_Msk                   /*!< CRC1 peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB6LPENCLRR_USBHLPEN_Pos          (24U)
#define RCC_MP_AHB6LPENCLRR_USBHLPEN_Msk          (0x1U << RCC_MP_AHB6LPENCLRR_USBHLPEN_Pos)         /*!< 0x01000000 */
#define RCC_MP_AHB6LPENCLRR_USBHLPEN              RCC_MP_AHB6LPENCLRR_USBHLPEN_Msk                   /*!< USBH peripheral clocks enable during CSleep mode */

/************  Bit definition for RCC_MP_TZAHB6LPENSETR register  *************/
#define RCC_MP_TZAHB6LPENSETR_MDMALPEN_Pos        (0U)
#define RCC_MP_TZAHB6LPENSETR_MDMALPEN_Msk        (0x1U << RCC_MP_TZAHB6LPENSETR_MDMALPEN_Pos)       /*!< 0x00000001 */
#define RCC_MP_TZAHB6LPENSETR_MDMALPEN            RCC_MP_TZAHB6LPENSETR_MDMALPEN_Msk                 /*!< MDMA peripheral clocks enable during CSleep mode */

/************  Bit definition for RCC_MP_TZAHB6LPENCLRR register  *************/
#define RCC_MP_TZAHB6LPENCLRR_MDMALPEN_Pos        (0U)
#define RCC_MP_TZAHB6LPENCLRR_MDMALPEN_Msk        (0x1U << RCC_MP_TZAHB6LPENCLRR_MDMALPEN_Pos)       /*!< 0x00000001 */
#define RCC_MP_TZAHB6LPENCLRR_MDMALPEN            RCC_MP_TZAHB6LPENCLRR_MDMALPEN_Msk                 /*!< MDMA peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MC_APB4LPENSETR register  **************/
#define RCC_MC_APB4LPENSETR_LTDCLPEN_Pos          (0U)
#define RCC_MC_APB4LPENSETR_LTDCLPEN_Msk          (0x1U << RCC_MC_APB4LPENSETR_LTDCLPEN_Pos)         /*!< 0x00000001 */
#define RCC_MC_APB4LPENSETR_LTDCLPEN              RCC_MC_APB4LPENSETR_LTDCLPEN_Msk                   /*!< LTDC peripheral clocks enable during CSleep mode */
#define RCC_MC_APB4LPENSETR_DSILPEN_Pos           (4U)
#define RCC_MC_APB4LPENSETR_DSILPEN_Msk           (0x1U << RCC_MC_APB4LPENSETR_DSILPEN_Pos)          /*!< 0x00000010 */
#define RCC_MC_APB4LPENSETR_DSILPEN               RCC_MC_APB4LPENSETR_DSILPEN_Msk                    /*!< DSI peripheral clocks enable during CSleep mode */
#define RCC_MC_APB4LPENSETR_DDRPERFMLPEN_Pos      (8U)
#define RCC_MC_APB4LPENSETR_DDRPERFMLPEN_Msk      (0x1U << RCC_MC_APB4LPENSETR_DDRPERFMLPEN_Pos)     /*!< 0x00000100 */
#define RCC_MC_APB4LPENSETR_DDRPERFMLPEN          RCC_MC_APB4LPENSETR_DDRPERFMLPEN_Msk               /*!< DDRPERFM APB clock enable during CSleep mode */
#define RCC_MC_APB4LPENSETR_USBPHYLPEN_Pos        (16U)
#define RCC_MC_APB4LPENSETR_USBPHYLPEN_Msk        (0x1U << RCC_MC_APB4LPENSETR_USBPHYLPEN_Pos)       /*!< 0x00010000 */
#define RCC_MC_APB4LPENSETR_USBPHYLPEN            RCC_MC_APB4LPENSETR_USBPHYLPEN_Msk                 /*!< USBPHYC peripheral clocks enable during CSleep mode */
#define RCC_MC_APB4LPENSETR_STGENROLPEN_Pos       (20U)
#define RCC_MC_APB4LPENSETR_STGENROLPEN_Msk       (0x1U << RCC_MC_APB4LPENSETR_STGENROLPEN_Pos)      /*!< 0x00100000 */
#define RCC_MC_APB4LPENSETR_STGENROLPEN           RCC_MC_APB4LPENSETR_STGENROLPEN_Msk                /*!< STGEN Read-Only Interface peripheral clocks enable during CSleep mode */
#define RCC_MC_APB4LPENSETR_STGENROSTPEN_Pos      (21U)
#define RCC_MC_APB4LPENSETR_STGENROSTPEN_Msk      (0x1U << RCC_MC_APB4LPENSETR_STGENROSTPEN_Pos)     /*!< 0x00200000 */
#define RCC_MC_APB4LPENSETR_STGENROSTPEN          RCC_MC_APB4LPENSETR_STGENROSTPEN_Msk               /*!< STGEN Read-Only Interface, clock enable during CStop mode */

/*************  Bit definition for RCC_MC_APB4LPENCLRR register  **************/
#define RCC_MC_APB4LPENCLRR_LTDCLPEN_Pos          (0U)
#define RCC_MC_APB4LPENCLRR_LTDCLPEN_Msk          (0x1U << RCC_MC_APB4LPENCLRR_LTDCLPEN_Pos)         /*!< 0x00000001 */
#define RCC_MC_APB4LPENCLRR_LTDCLPEN              RCC_MC_APB4LPENCLRR_LTDCLPEN_Msk                   /*!< LTDC peripheral clocks enable during CSleep mode */
#define RCC_MC_APB4LPENCLRR_DSILPEN_Pos           (4U)
#define RCC_MC_APB4LPENCLRR_DSILPEN_Msk           (0x1U << RCC_MC_APB4LPENCLRR_DSILPEN_Pos)          /*!< 0x00000010 */
#define RCC_MC_APB4LPENCLRR_DSILPEN               RCC_MC_APB4LPENCLRR_DSILPEN_Msk                    /*!< DSI peripheral clocks enable during CSleep mode */
#define RCC_MC_APB4LPENCLRR_DDRPERFMLPEN_Pos      (8U)
#define RCC_MC_APB4LPENCLRR_DDRPERFMLPEN_Msk      (0x1U << RCC_MC_APB4LPENCLRR_DDRPERFMLPEN_Pos)     /*!< 0x00000100 */
#define RCC_MC_APB4LPENCLRR_DDRPERFMLPEN          RCC_MC_APB4LPENCLRR_DDRPERFMLPEN_Msk               /*!< DDRPERFM APB clock enable during CSleep mode */
#define RCC_MC_APB4LPENCLRR_USBPHYLPEN_Pos        (16U)
#define RCC_MC_APB4LPENCLRR_USBPHYLPEN_Msk        (0x1U << RCC_MC_APB4LPENCLRR_USBPHYLPEN_Pos)       /*!< 0x00010000 */
#define RCC_MC_APB4LPENCLRR_USBPHYLPEN            RCC_MC_APB4LPENCLRR_USBPHYLPEN_Msk                 /*!< USBPHYC peripheral clocks enable during CSleep mode */
#define RCC_MC_APB4LPENCLRR_STGENROLPEN_Pos       (20U)
#define RCC_MC_APB4LPENCLRR_STGENROLPEN_Msk       (0x1U << RCC_MC_APB4LPENCLRR_STGENROLPEN_Pos)      /*!< 0x00100000 */
#define RCC_MC_APB4LPENCLRR_STGENROLPEN           RCC_MC_APB4LPENCLRR_STGENROLPEN_Msk                /*!< STGEN Read-Only Interface peripheral clocks enable during CSleep mode */
#define RCC_MC_APB4LPENCLRR_STGENROSTPEN_Pos      (21U)
#define RCC_MC_APB4LPENCLRR_STGENROSTPEN_Msk      (0x1U << RCC_MC_APB4LPENCLRR_STGENROSTPEN_Pos)     /*!< 0x00200000 */
#define RCC_MC_APB4LPENCLRR_STGENROSTPEN          RCC_MC_APB4LPENCLRR_STGENROSTPEN_Msk               /*!< STGEN Read-Only Interface clock enable during CStop mode */

/*************  Bit definition for RCC_MC_APB5LPENSETR register  **************/
#define RCC_MC_APB5LPENSETR_SPI6LPEN_Pos          (0U)
#define RCC_MC_APB5LPENSETR_SPI6LPEN_Msk          (0x1U << RCC_MC_APB5LPENSETR_SPI6LPEN_Pos)         /*!< 0x00000001 */
#define RCC_MC_APB5LPENSETR_SPI6LPEN              RCC_MC_APB5LPENSETR_SPI6LPEN_Msk                   /*!< SPI6 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB5LPENSETR_I2C4LPEN_Pos          (2U)
#define RCC_MC_APB5LPENSETR_I2C4LPEN_Msk          (0x1U << RCC_MC_APB5LPENSETR_I2C4LPEN_Pos)         /*!< 0x00000004 */
#define RCC_MC_APB5LPENSETR_I2C4LPEN              RCC_MC_APB5LPENSETR_I2C4LPEN_Msk                   /*!< I2C4 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB5LPENSETR_I2C6LPEN_Pos          (3U)
#define RCC_MC_APB5LPENSETR_I2C6LPEN_Msk          (0x1U << RCC_MC_APB5LPENSETR_I2C6LPEN_Pos)         /*!< 0x00000008 */
#define RCC_MC_APB5LPENSETR_I2C6LPEN              RCC_MC_APB5LPENSETR_I2C6LPEN_Msk                   /*!< I2C6 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB5LPENSETR_USART1LPEN_Pos        (4U)
#define RCC_MC_APB5LPENSETR_USART1LPEN_Msk        (0x1U << RCC_MC_APB5LPENSETR_USART1LPEN_Pos)       /*!< 0x00000010 */
#define RCC_MC_APB5LPENSETR_USART1LPEN            RCC_MC_APB5LPENSETR_USART1LPEN_Msk                 /*!< USART1 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB5LPENSETR_RTCAPBLPEN_Pos        (8U)
#define RCC_MC_APB5LPENSETR_RTCAPBLPEN_Msk        (0x1U << RCC_MC_APB5LPENSETR_RTCAPBLPEN_Pos)       /*!< 0x00000100 */
#define RCC_MC_APB5LPENSETR_RTCAPBLPEN            RCC_MC_APB5LPENSETR_RTCAPBLPEN_Msk                 /*!< RTC APB clock enable during CSleep mode */
#define RCC_MC_APB5LPENSETR_TZC1LPEN_Pos          (11U)
#define RCC_MC_APB5LPENSETR_TZC1LPEN_Msk          (0x1U << RCC_MC_APB5LPENSETR_TZC1LPEN_Pos)         /*!< 0x00000800 */
#define RCC_MC_APB5LPENSETR_TZC1LPEN              RCC_MC_APB5LPENSETR_TZC1LPEN_Msk                   /*!< TZC AXI port 1 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB5LPENSETR_TZC2LPEN_Pos          (12U)
#define RCC_MC_APB5LPENSETR_TZC2LPEN_Msk          (0x1U << RCC_MC_APB5LPENSETR_TZC2LPEN_Pos)         /*!< 0x00001000 */
#define RCC_MC_APB5LPENSETR_TZC2LPEN              RCC_MC_APB5LPENSETR_TZC2LPEN_Msk                   /*!< TZC AXI port 2 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB5LPENSETR_TZPCLPEN_Pos          (13U)
#define RCC_MC_APB5LPENSETR_TZPCLPEN_Msk          (0x1U << RCC_MC_APB5LPENSETR_TZPCLPEN_Pos)         /*!< 0x00002000 */
#define RCC_MC_APB5LPENSETR_TZPCLPEN              RCC_MC_APB5LPENSETR_TZPCLPEN_Msk                   /*!< TZPC peripheral clocks enable during CSleep mode */
#define RCC_MC_APB5LPENSETR_BSECLPEN_Pos          (16U)
#define RCC_MC_APB5LPENSETR_BSECLPEN_Msk          (0x1U << RCC_MC_APB5LPENSETR_BSECLPEN_Pos)         /*!< 0x00010000 */
#define RCC_MC_APB5LPENSETR_BSECLPEN              RCC_MC_APB5LPENSETR_BSECLPEN_Msk                   /*!< BSEC peripheral clocks enable during CSleep mode */
#define RCC_MC_APB5LPENSETR_STGENLPEN_Pos         (20U)
#define RCC_MC_APB5LPENSETR_STGENLPEN_Msk         (0x1U << RCC_MC_APB5LPENSETR_STGENLPEN_Pos)        /*!< 0x00100000 */
#define RCC_MC_APB5LPENSETR_STGENLPEN             RCC_MC_APB5LPENSETR_STGENLPEN_Msk                  /*!< STGEN Controller part, peripheral clocks enable during CSleep mode */
#define RCC_MC_APB5LPENSETR_STGENSTPEN_Pos        (21U)
#define RCC_MC_APB5LPENSETR_STGENSTPEN_Msk        (0x1U << RCC_MC_APB5LPENSETR_STGENSTPEN_Pos)       /*!< 0x00200000 */
#define RCC_MC_APB5LPENSETR_STGENSTPEN            RCC_MC_APB5LPENSETR_STGENSTPEN_Msk                 /*!< STGEN Controller part, peripheral clocks enable during CStop mode */

/*************  Bit definition for RCC_MC_APB5LPENCLRR register  **************/
#define RCC_MC_APB5LPENCLRR_SPI6LPEN_Pos          (0U)
#define RCC_MC_APB5LPENCLRR_SPI6LPEN_Msk          (0x1U << RCC_MC_APB5LPENCLRR_SPI6LPEN_Pos)         /*!< 0x00000001 */
#define RCC_MC_APB5LPENCLRR_SPI6LPEN              RCC_MC_APB5LPENCLRR_SPI6LPEN_Msk                   /*!< SPI6 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB5LPENCLRR_I2C4LPEN_Pos          (2U)
#define RCC_MC_APB5LPENCLRR_I2C4LPEN_Msk          (0x1U << RCC_MC_APB5LPENCLRR_I2C4LPEN_Pos)         /*!< 0x00000004 */
#define RCC_MC_APB5LPENCLRR_I2C4LPEN              RCC_MC_APB5LPENCLRR_I2C4LPEN_Msk                   /*!< I2C4 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB5LPENCLRR_I2C6LPEN_Pos          (3U)
#define RCC_MC_APB5LPENCLRR_I2C6LPEN_Msk          (0x1U << RCC_MC_APB5LPENCLRR_I2C6LPEN_Pos)         /*!< 0x00000008 */
#define RCC_MC_APB5LPENCLRR_I2C6LPEN              RCC_MC_APB5LPENCLRR_I2C6LPEN_Msk                   /*!< I2C6 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB5LPENCLRR_USART1LPEN_Pos        (4U)
#define RCC_MC_APB5LPENCLRR_USART1LPEN_Msk        (0x1U << RCC_MC_APB5LPENCLRR_USART1LPEN_Pos)       /*!< 0x00000010 */
#define RCC_MC_APB5LPENCLRR_USART1LPEN            RCC_MC_APB5LPENCLRR_USART1LPEN_Msk                 /*!< USART1 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB5LPENCLRR_RTCAPBLPEN_Pos        (8U)
#define RCC_MC_APB5LPENCLRR_RTCAPBLPEN_Msk        (0x1U << RCC_MC_APB5LPENCLRR_RTCAPBLPEN_Pos)       /*!< 0x00000100 */
#define RCC_MC_APB5LPENCLRR_RTCAPBLPEN            RCC_MC_APB5LPENCLRR_RTCAPBLPEN_Msk                 /*!< RTC APB clock enable during CSleep mode */
#define RCC_MC_APB5LPENCLRR_TZC1LPEN_Pos          (11U)
#define RCC_MC_APB5LPENCLRR_TZC1LPEN_Msk          (0x1U << RCC_MC_APB5LPENCLRR_TZC1LPEN_Pos)         /*!< 0x00000800 */
#define RCC_MC_APB5LPENCLRR_TZC1LPEN              RCC_MC_APB5LPENCLRR_TZC1LPEN_Msk                   /*!< TZC AXI port 1 peripheral clocks disable during CSleep mode */
#define RCC_MC_APB5LPENCLRR_TZC2LPEN_Pos          (12U)
#define RCC_MC_APB5LPENCLRR_TZC2LPEN_Msk          (0x1U << RCC_MC_APB5LPENCLRR_TZC2LPEN_Pos)         /*!< 0x00001000 */
#define RCC_MC_APB5LPENCLRR_TZC2LPEN              RCC_MC_APB5LPENCLRR_TZC2LPEN_Msk                   /*!< TZC AXI port 2 peripheral clocks disable during CSleep mode */
#define RCC_MC_APB5LPENCLRR_TZPCLPEN_Pos          (13U)
#define RCC_MC_APB5LPENCLRR_TZPCLPEN_Msk          (0x1U << RCC_MC_APB5LPENCLRR_TZPCLPEN_Pos)         /*!< 0x00002000 */
#define RCC_MC_APB5LPENCLRR_TZPCLPEN              RCC_MC_APB5LPENCLRR_TZPCLPEN_Msk                   /*!< TZPC peripheral clocks enable during CSleep mode */
#define RCC_MC_APB5LPENCLRR_BSECLPEN_Pos          (16U)
#define RCC_MC_APB5LPENCLRR_BSECLPEN_Msk          (0x1U << RCC_MC_APB5LPENCLRR_BSECLPEN_Pos)         /*!< 0x00010000 */
#define RCC_MC_APB5LPENCLRR_BSECLPEN              RCC_MC_APB5LPENCLRR_BSECLPEN_Msk                   /*!< BSEC peripheral clocks enable during CSleep mode */
#define RCC_MC_APB5LPENCLRR_STGENLPEN_Pos         (20U)
#define RCC_MC_APB5LPENCLRR_STGENLPEN_Msk         (0x1U << RCC_MC_APB5LPENCLRR_STGENLPEN_Pos)        /*!< 0x00100000 */
#define RCC_MC_APB5LPENCLRR_STGENLPEN             RCC_MC_APB5LPENCLRR_STGENLPEN_Msk                  /*!< STGEN peripheral clocks enable during CSleep mode */
#define RCC_MC_APB5LPENCLRR_STGENSTPEN_Pos        (21U)
#define RCC_MC_APB5LPENCLRR_STGENSTPEN_Msk        (0x1U << RCC_MC_APB5LPENCLRR_STGENSTPEN_Pos)       /*!< 0x00200000 */
#define RCC_MC_APB5LPENCLRR_STGENSTPEN            RCC_MC_APB5LPENCLRR_STGENSTPEN_Msk                 /*!< STGEN peripheral clocks enable during CStop mode */

/*************  Bit definition for RCC_MC_AHB5LPENSETR register  **************/
#define RCC_MC_AHB5LPENSETR_GPIOZLPEN_Pos         (0U)
#define RCC_MC_AHB5LPENSETR_GPIOZLPEN_Msk         (0x1U << RCC_MC_AHB5LPENSETR_GPIOZLPEN_Pos)        /*!< 0x00000001 */
#define RCC_MC_AHB5LPENSETR_GPIOZLPEN             RCC_MC_AHB5LPENSETR_GPIOZLPEN_Msk                  /*!< GPIOZ Secure peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB5LPENSETR_CRYP1LPEN_Pos         (4U)
#define RCC_MC_AHB5LPENSETR_CRYP1LPEN_Msk         (0x1U << RCC_MC_AHB5LPENSETR_CRYP1LPEN_Pos)        /*!< 0x00000010 */
#define RCC_MC_AHB5LPENSETR_CRYP1LPEN             RCC_MC_AHB5LPENSETR_CRYP1LPEN_Msk                  /*!< CRYP1 (3DES/AES1) peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB5LPENSETR_HASH1LPEN_Pos         (5U)
#define RCC_MC_AHB5LPENSETR_HASH1LPEN_Msk         (0x1U << RCC_MC_AHB5LPENSETR_HASH1LPEN_Pos)        /*!< 0x00000020 */
#define RCC_MC_AHB5LPENSETR_HASH1LPEN             RCC_MC_AHB5LPENSETR_HASH1LPEN_Msk                  /*!< HASH1 peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB5LPENSETR_RNG1LPEN_Pos          (6U)
#define RCC_MC_AHB5LPENSETR_RNG1LPEN_Msk          (0x1U << RCC_MC_AHB5LPENSETR_RNG1LPEN_Pos)         /*!< 0x00000040 */
#define RCC_MC_AHB5LPENSETR_RNG1LPEN              RCC_MC_AHB5LPENSETR_RNG1LPEN_Msk                   /*!< RNG1 peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB5LPENSETR_BKPSRAMLPEN_Pos       (8U)
#define RCC_MC_AHB5LPENSETR_BKPSRAMLPEN_Msk       (0x1U << RCC_MC_AHB5LPENSETR_BKPSRAMLPEN_Pos)      /*!< 0x00000100 */
#define RCC_MC_AHB5LPENSETR_BKPSRAMLPEN           RCC_MC_AHB5LPENSETR_BKPSRAMLPEN_Msk                /*!< BKPSRAM clock enable during CSleep mode */

/*************  Bit definition for RCC_MC_AHB5LPENCLRR register  **************/
#define RCC_MC_AHB5LPENCLRR_GPIOZLPEN_Pos         (0U)
#define RCC_MC_AHB5LPENCLRR_GPIOZLPEN_Msk         (0x1U << RCC_MC_AHB5LPENCLRR_GPIOZLPEN_Pos)        /*!< 0x00000001 */
#define RCC_MC_AHB5LPENCLRR_GPIOZLPEN             RCC_MC_AHB5LPENCLRR_GPIOZLPEN_Msk                  /*!< GPIOZ Secure peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB5LPENCLRR_CRYP1LPEN_Pos         (4U)
#define RCC_MC_AHB5LPENCLRR_CRYP1LPEN_Msk         (0x1U << RCC_MC_AHB5LPENCLRR_CRYP1LPEN_Pos)        /*!< 0x00000010 */
#define RCC_MC_AHB5LPENCLRR_CRYP1LPEN             RCC_MC_AHB5LPENCLRR_CRYP1LPEN_Msk                  /*!< CRYP1 (3DES/AES1) peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB5LPENCLRR_HASH1LPEN_Pos         (5U)
#define RCC_MC_AHB5LPENCLRR_HASH1LPEN_Msk         (0x1U << RCC_MC_AHB5LPENCLRR_HASH1LPEN_Pos)        /*!< 0x00000020 */
#define RCC_MC_AHB5LPENCLRR_HASH1LPEN             RCC_MC_AHB5LPENCLRR_HASH1LPEN_Msk                  /*!< HASH1 peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB5LPENCLRR_RNG1LPEN_Pos          (6U)
#define RCC_MC_AHB5LPENCLRR_RNG1LPEN_Msk          (0x1U << RCC_MC_AHB5LPENCLRR_RNG1LPEN_Pos)         /*!< 0x00000040 */
#define RCC_MC_AHB5LPENCLRR_RNG1LPEN              RCC_MC_AHB5LPENCLRR_RNG1LPEN_Msk                   /*!< RNG1 peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB5LPENCLRR_BKPSRAMLPEN_Pos       (8U)
#define RCC_MC_AHB5LPENCLRR_BKPSRAMLPEN_Msk       (0x1U << RCC_MC_AHB5LPENCLRR_BKPSRAMLPEN_Pos)      /*!< 0x00000100 */
#define RCC_MC_AHB5LPENCLRR_BKPSRAMLPEN           RCC_MC_AHB5LPENCLRR_BKPSRAMLPEN_Msk                /*!< BKPSRAM clock enable during CSleep mode */

/*************  Bit definition for RCC_MC_AHB6LPENSETR register  **************/
#define RCC_MC_AHB6LPENSETR_MDMALPEN_Pos          (0U)
#define RCC_MC_AHB6LPENSETR_MDMALPEN_Msk          (0x1U << RCC_MC_AHB6LPENSETR_MDMALPEN_Pos)         /*!< 0x00000001 */
#define RCC_MC_AHB6LPENSETR_MDMALPEN              RCC_MC_AHB6LPENSETR_MDMALPEN_Msk                   /*!< MDMA peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB6LPENSETR_GPULPEN_Pos           (5U)
#define RCC_MC_AHB6LPENSETR_GPULPEN_Msk           (0x1U << RCC_MC_AHB6LPENSETR_GPULPEN_Pos)          /*!< 0x00000020 */
#define RCC_MC_AHB6LPENSETR_GPULPEN               RCC_MC_AHB6LPENSETR_GPULPEN_Msk                    /*!< GPU peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB6LPENSETR_ETHCKLPEN_Pos         (7U)
#define RCC_MC_AHB6LPENSETR_ETHCKLPEN_Msk         (0x1U << RCC_MC_AHB6LPENSETR_ETHCKLPEN_Pos)        /*!< 0x00000080 */
#define RCC_MC_AHB6LPENSETR_ETHCKLPEN             RCC_MC_AHB6LPENSETR_ETHCKLPEN_Msk                  /*!< Enable of the Ethernet clock generated by the RCC (eth_ker_ck) during CSleep mode */
#define RCC_MC_AHB6LPENSETR_ETHTXLPEN_Pos         (8U)
#define RCC_MC_AHB6LPENSETR_ETHTXLPEN_Msk         (0x1U << RCC_MC_AHB6LPENSETR_ETHTXLPEN_Pos)        /*!< 0x00000100 */
#define RCC_MC_AHB6LPENSETR_ETHTXLPEN             RCC_MC_AHB6LPENSETR_ETHTXLPEN_Msk                  /*!< Enable of the Ethernet Transmission Clock during CSleep mode */
#define RCC_MC_AHB6LPENSETR_ETHRXLPEN_Pos         (9U)
#define RCC_MC_AHB6LPENSETR_ETHRXLPEN_Msk         (0x1U << RCC_MC_AHB6LPENSETR_ETHRXLPEN_Pos)        /*!< 0x00000200 */
#define RCC_MC_AHB6LPENSETR_ETHRXLPEN             RCC_MC_AHB6LPENSETR_ETHRXLPEN_Msk                  /*!< Enable of the Ethernet Reception Clock during CSleep mode */
#define RCC_MC_AHB6LPENSETR_ETHMACLPEN_Pos        (10U)
#define RCC_MC_AHB6LPENSETR_ETHMACLPEN_Msk        (0x1U << RCC_MC_AHB6LPENSETR_ETHMACLPEN_Pos)       /*!< 0x00000400 */
#define RCC_MC_AHB6LPENSETR_ETHMACLPEN            RCC_MC_AHB6LPENSETR_ETHMACLPEN_Msk                 /*!< Enable of the bus interface clocks for ETH block during CSleep mode */
#define RCC_MC_AHB6LPENSETR_ETHSTPEN_Pos          (11U)
#define RCC_MC_AHB6LPENSETR_ETHSTPEN_Msk          (0x1U << RCC_MC_AHB6LPENSETR_ETHSTPEN_Pos)         /*!< 0x00000800 */
#define RCC_MC_AHB6LPENSETR_ETHSTPEN              RCC_MC_AHB6LPENSETR_ETHSTPEN_Msk                   /*!< ETH peripheral clock enable during CStop mode */
#define RCC_MC_AHB6LPENSETR_FMCLPEN_Pos           (12U)
#define RCC_MC_AHB6LPENSETR_FMCLPEN_Msk           (0x1U << RCC_MC_AHB6LPENSETR_FMCLPEN_Pos)          /*!< 0x00001000 */
#define RCC_MC_AHB6LPENSETR_FMCLPEN               RCC_MC_AHB6LPENSETR_FMCLPEN_Msk                    /*!< FMC peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB6LPENSETR_QSPILPEN_Pos          (14U)
#define RCC_MC_AHB6LPENSETR_QSPILPEN_Msk          (0x1U << RCC_MC_AHB6LPENSETR_QSPILPEN_Pos)         /*!< 0x00004000 */
#define RCC_MC_AHB6LPENSETR_QSPILPEN              RCC_MC_AHB6LPENSETR_QSPILPEN_Msk                   /*!< QUADSPI peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB6LPENSETR_SDMMC1LPEN_Pos        (16U)
#define RCC_MC_AHB6LPENSETR_SDMMC1LPEN_Msk        (0x1U << RCC_MC_AHB6LPENSETR_SDMMC1LPEN_Pos)       /*!< 0x00010000 */
#define RCC_MC_AHB6LPENSETR_SDMMC1LPEN            RCC_MC_AHB6LPENSETR_SDMMC1LPEN_Msk                 /*!< SDMMC1 and SDMMC1 delay (DLYBSD1) block peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB6LPENSETR_SDMMC2LPEN_Pos        (17U)
#define RCC_MC_AHB6LPENSETR_SDMMC2LPEN_Msk        (0x1U << RCC_MC_AHB6LPENSETR_SDMMC2LPEN_Pos)       /*!< 0x00020000 */
#define RCC_MC_AHB6LPENSETR_SDMMC2LPEN            RCC_MC_AHB6LPENSETR_SDMMC2LPEN_Msk                 /*!< SDMMC2 and SDMMC2 delay (DLYBSD2) block peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB6LPENSETR_CRC1LPEN_Pos          (20U)
#define RCC_MC_AHB6LPENSETR_CRC1LPEN_Msk          (0x1U << RCC_MC_AHB6LPENSETR_CRC1LPEN_Pos)         /*!< 0x00100000 */
#define RCC_MC_AHB6LPENSETR_CRC1LPEN              RCC_MC_AHB6LPENSETR_CRC1LPEN_Msk                   /*!< CRC1 peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB6LPENSETR_USBHLPEN_Pos          (24U)
#define RCC_MC_AHB6LPENSETR_USBHLPEN_Msk          (0x1U << RCC_MC_AHB6LPENSETR_USBHLPEN_Pos)         /*!< 0x01000000 */
#define RCC_MC_AHB6LPENSETR_USBHLPEN              RCC_MC_AHB6LPENSETR_USBHLPEN_Msk                   /*!< USBH peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MC_AHB6LPENCLRR register  **************/
#define RCC_MC_AHB6LPENCLRR_MDMALPEN_Pos          (0U)
#define RCC_MC_AHB6LPENCLRR_MDMALPEN_Msk          (0x1U << RCC_MC_AHB6LPENCLRR_MDMALPEN_Pos)         /*!< 0x00000001 */
#define RCC_MC_AHB6LPENCLRR_MDMALPEN              RCC_MC_AHB6LPENCLRR_MDMALPEN_Msk                   /*!< MDMA peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB6LPENCLRR_GPULPEN_Pos           (5U)
#define RCC_MC_AHB6LPENCLRR_GPULPEN_Msk           (0x1U << RCC_MC_AHB6LPENCLRR_GPULPEN_Pos)          /*!< 0x00000020 */
#define RCC_MC_AHB6LPENCLRR_GPULPEN               RCC_MC_AHB6LPENCLRR_GPULPEN_Msk                    /*!< GPU peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB6LPENCLRR_ETHCKLPEN_Pos         (7U)
#define RCC_MC_AHB6LPENCLRR_ETHCKLPEN_Msk         (0x1U << RCC_MC_AHB6LPENCLRR_ETHCKLPEN_Pos)        /*!< 0x00000080 */
#define RCC_MC_AHB6LPENCLRR_ETHCKLPEN             RCC_MC_AHB6LPENCLRR_ETHCKLPEN_Msk                  /*!< Disable of the Ethernet clock generated by the RCC (eth_ker_ck) during CSleep mode */
#define RCC_MC_AHB6LPENCLRR_ETHTXLPEN_Pos         (8U)
#define RCC_MC_AHB6LPENCLRR_ETHTXLPEN_Msk         (0x1U << RCC_MC_AHB6LPENCLRR_ETHTXLPEN_Pos)        /*!< 0x00000100 */
#define RCC_MC_AHB6LPENCLRR_ETHTXLPEN             RCC_MC_AHB6LPENCLRR_ETHTXLPEN_Msk                  /*!< Disable of the Ethernet Transmission Clock during CSleep mode */
#define RCC_MC_AHB6LPENCLRR_ETHRXLPEN_Pos         (9U)
#define RCC_MC_AHB6LPENCLRR_ETHRXLPEN_Msk         (0x1U << RCC_MC_AHB6LPENCLRR_ETHRXLPEN_Pos)        /*!< 0x00000200 */
#define RCC_MC_AHB6LPENCLRR_ETHRXLPEN             RCC_MC_AHB6LPENCLRR_ETHRXLPEN_Msk                  /*!< Disable of the Ethernet Reception Clock during CSleep mode */
#define RCC_MC_AHB6LPENCLRR_ETHMACLPEN_Pos        (10U)
#define RCC_MC_AHB6LPENCLRR_ETHMACLPEN_Msk        (0x1U << RCC_MC_AHB6LPENCLRR_ETHMACLPEN_Pos)       /*!< 0x00000400 */
#define RCC_MC_AHB6LPENCLRR_ETHMACLPEN            RCC_MC_AHB6LPENCLRR_ETHMACLPEN_Msk                 /*!< Disable of the bus interface clocks for ETH block during CSleep mode */
#define RCC_MC_AHB6LPENCLRR_ETHSTPEN_Pos          (11U)
#define RCC_MC_AHB6LPENCLRR_ETHSTPEN_Msk          (0x1U << RCC_MC_AHB6LPENCLRR_ETHSTPEN_Pos)         /*!< 0x00000800 */
#define RCC_MC_AHB6LPENCLRR_ETHSTPEN              RCC_MC_AHB6LPENCLRR_ETHSTPEN_Msk                   /*!< ETH peripheral clock enable during CStop mode */
#define RCC_MC_AHB6LPENCLRR_FMCLPEN_Pos           (12U)
#define RCC_MC_AHB6LPENCLRR_FMCLPEN_Msk           (0x1U << RCC_MC_AHB6LPENCLRR_FMCLPEN_Pos)          /*!< 0x00001000 */
#define RCC_MC_AHB6LPENCLRR_FMCLPEN               RCC_MC_AHB6LPENCLRR_FMCLPEN_Msk                    /*!< FMC peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB6LPENCLRR_QSPILPEN_Pos          (14U)
#define RCC_MC_AHB6LPENCLRR_QSPILPEN_Msk          (0x1U << RCC_MC_AHB6LPENCLRR_QSPILPEN_Pos)         /*!< 0x00004000 */
#define RCC_MC_AHB6LPENCLRR_QSPILPEN              RCC_MC_AHB6LPENCLRR_QSPILPEN_Msk                   /*!< QUADSPI peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB6LPENCLRR_SDMMC1LPEN_Pos        (16U)
#define RCC_MC_AHB6LPENCLRR_SDMMC1LPEN_Msk        (0x1U << RCC_MC_AHB6LPENCLRR_SDMMC1LPEN_Pos)       /*!< 0x00010000 */
#define RCC_MC_AHB6LPENCLRR_SDMMC1LPEN            RCC_MC_AHB6LPENCLRR_SDMMC1LPEN_Msk                 /*!< SDMMC1 and SDMMC1 delay (DLYBSD1) block peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB6LPENCLRR_SDMMC2LPEN_Pos        (17U)
#define RCC_MC_AHB6LPENCLRR_SDMMC2LPEN_Msk        (0x1U << RCC_MC_AHB6LPENCLRR_SDMMC2LPEN_Pos)       /*!< 0x00020000 */
#define RCC_MC_AHB6LPENCLRR_SDMMC2LPEN            RCC_MC_AHB6LPENCLRR_SDMMC2LPEN_Msk                 /*!< SDMMC2 and SDMMC2 delay (DLYBSD2) block peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB6LPENCLRR_CRC1LPEN_Pos          (20U)
#define RCC_MC_AHB6LPENCLRR_CRC1LPEN_Msk          (0x1U << RCC_MC_AHB6LPENCLRR_CRC1LPEN_Pos)         /*!< 0x00100000 */
#define RCC_MC_AHB6LPENCLRR_CRC1LPEN              RCC_MC_AHB6LPENCLRR_CRC1LPEN_Msk                   /*!< CRC1 peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB6LPENCLRR_USBHLPEN_Pos          (24U)
#define RCC_MC_AHB6LPENCLRR_USBHLPEN_Msk          (0x1U << RCC_MC_AHB6LPENCLRR_USBHLPEN_Pos)         /*!< 0x01000000 */
#define RCC_MC_AHB6LPENCLRR_USBHLPEN              RCC_MC_AHB6LPENCLRR_USBHLPEN_Msk                   /*!< USBH peripheral clocks enable during CSleep mode */

/***************  Bit definition for RCC_BR_RSTSCLRR register  ****************/
#define RCC_BR_RSTSCLRR_PORRSTF_Pos               (0U)
#define RCC_BR_RSTSCLRR_PORRSTF_Msk               (0x1U << RCC_BR_RSTSCLRR_PORRSTF_Pos)              /*!< 0x00000001 */
#define RCC_BR_RSTSCLRR_PORRSTF                   RCC_BR_RSTSCLRR_PORRSTF_Msk                        /*!< POR/PDR reset flag */
#define RCC_BR_RSTSCLRR_BORRSTF_Pos               (1U)
#define RCC_BR_RSTSCLRR_BORRSTF_Msk               (0x1U << RCC_BR_RSTSCLRR_BORRSTF_Pos)              /*!< 0x00000002 */
#define RCC_BR_RSTSCLRR_BORRSTF                   RCC_BR_RSTSCLRR_BORRSTF_Msk                        /*!< BOR reset flag */
#define RCC_BR_RSTSCLRR_PADRSTF_Pos               (2U)
#define RCC_BR_RSTSCLRR_PADRSTF_Msk               (0x1U << RCC_BR_RSTSCLRR_PADRSTF_Pos)              /*!< 0x00000004 */
#define RCC_BR_RSTSCLRR_PADRSTF                   RCC_BR_RSTSCLRR_PADRSTF_Msk                        /*!< NRST reset flag */
#define RCC_BR_RSTSCLRR_HCSSRSTF_Pos              (3U)
#define RCC_BR_RSTSCLRR_HCSSRSTF_Msk              (0x1U << RCC_BR_RSTSCLRR_HCSSRSTF_Pos)             /*!< 0x00000008 */
#define RCC_BR_RSTSCLRR_HCSSRSTF                  RCC_BR_RSTSCLRR_HCSSRSTF_Msk                       /*!< HSE CSS reset flag */
#define RCC_BR_RSTSCLRR_VCORERSTF_Pos             (4U)
#define RCC_BR_RSTSCLRR_VCORERSTF_Msk             (0x1U << RCC_BR_RSTSCLRR_VCORERSTF_Pos)            /*!< 0x00000010 */
#define RCC_BR_RSTSCLRR_VCORERSTF                 RCC_BR_RSTSCLRR_VCORERSTF_Msk                      /*!< VDDCORE reset flag */
#define RCC_BR_RSTSCLRR_MPSYSRSTF_Pos             (6U)
#define RCC_BR_RSTSCLRR_MPSYSRSTF_Msk             (0x1U << RCC_BR_RSTSCLRR_MPSYSRSTF_Pos)            /*!< 0x00000040 */
#define RCC_BR_RSTSCLRR_MPSYSRSTF                 RCC_BR_RSTSCLRR_MPSYSRSTF_Msk                      /*!< MPU System reset flag */
#define RCC_BR_RSTSCLRR_MCSYSRSTF_Pos             (7U)
#define RCC_BR_RSTSCLRR_MCSYSRSTF_Msk             (0x1U << RCC_BR_RSTSCLRR_MCSYSRSTF_Pos)            /*!< 0x00000080 */
#define RCC_BR_RSTSCLRR_MCSYSRSTF                 RCC_BR_RSTSCLRR_MCSYSRSTF_Msk                      /*!< MCU System reset flag */
#define RCC_BR_RSTSCLRR_IWDG1RSTF_Pos             (8U)
#define RCC_BR_RSTSCLRR_IWDG1RSTF_Msk             (0x1U << RCC_BR_RSTSCLRR_IWDG1RSTF_Pos)            /*!< 0x00000100 */
#define RCC_BR_RSTSCLRR_IWDG1RSTF                 RCC_BR_RSTSCLRR_IWDG1RSTF_Msk                      /*!< IWDG1 reset flag */
#define RCC_BR_RSTSCLRR_IWDG2RSTF_Pos             (9U)
#define RCC_BR_RSTSCLRR_IWDG2RSTF_Msk             (0x1U << RCC_BR_RSTSCLRR_IWDG2RSTF_Pos)            /*!< 0x00000200 */
#define RCC_BR_RSTSCLRR_IWDG2RSTF                 RCC_BR_RSTSCLRR_IWDG2RSTF_Msk                      /*!< IWDG2 reset flag */
#define RCC_BR_RSTSCLRR_MPUP0RSTF_Pos             (13U)
#define RCC_BR_RSTSCLRR_MPUP0RSTF_Msk             (0x1U << RCC_BR_RSTSCLRR_MPUP0RSTF_Pos)            /*!< 0x00002000 */
#define RCC_BR_RSTSCLRR_MPUP0RSTF                 RCC_BR_RSTSCLRR_MPUP0RSTF_Msk                      /*!< MPU processor 0 reset flag */
#define RCC_BR_RSTSCLRR_MPUP1RSTF_Pos             (14U)
#define RCC_BR_RSTSCLRR_MPUP1RSTF_Msk             (0x1U << RCC_BR_RSTSCLRR_MPUP1RSTF_Pos)            /*!< 0x00004000 */
#define RCC_BR_RSTSCLRR_MPUP1RSTF                 RCC_BR_RSTSCLRR_MPUP1RSTF_Msk                      /*!< MPU processor 1 reset flag */

/***************  Bit definition for RCC_MP_GRSTCSETR register  ***************/
#define RCC_MP_GRSTCSETR_MPSYSRST_Pos             (0U)
#define RCC_MP_GRSTCSETR_MPSYSRST_Msk             (0x1U << RCC_MP_GRSTCSETR_MPSYSRST_Pos)            /*!< 0x00000001 */
#define RCC_MP_GRSTCSETR_MPSYSRST                 RCC_MP_GRSTCSETR_MPSYSRST_Msk                      /*!< System reset */
#define RCC_MP_GRSTCSETR_MCURST_Pos               (1U)
#define RCC_MP_GRSTCSETR_MCURST_Msk               (0x1U << RCC_MP_GRSTCSETR_MCURST_Pos)              /*!< 0x00000002 */
#define RCC_MP_GRSTCSETR_MCURST                   RCC_MP_GRSTCSETR_MCURST_Msk                        /*!< MCU reset */
#define RCC_MP_GRSTCSETR_MPUP0RST_Pos             (4U)
#define RCC_MP_GRSTCSETR_MPUP0RST_Msk             (0x1U << RCC_MP_GRSTCSETR_MPUP0RST_Pos)            /*!< 0x00000010 */
#define RCC_MP_GRSTCSETR_MPUP0RST                 RCC_MP_GRSTCSETR_MPUP0RST_Msk                      /*!< MPU processor 0 reset */
#define RCC_MP_GRSTCSETR_MPUP1RST_Pos             (5U)
#define RCC_MP_GRSTCSETR_MPUP1RST_Msk             (0x1U << RCC_MP_GRSTCSETR_MPUP1RST_Pos)            /*!< 0x00000020 */
#define RCC_MP_GRSTCSETR_MPUP1RST                 RCC_MP_GRSTCSETR_MPUP1RST_Msk                      /*!< MPU processor 1 reset */

/***************  Bit definition for RCC_MP_RSTSCLRR register  ****************/
#define RCC_MP_RSTSCLRR_PORRSTF_Pos               (0U)
#define RCC_MP_RSTSCLRR_PORRSTF_Msk               (0x1U << RCC_MP_RSTSCLRR_PORRSTF_Pos)              /*!< 0x00000001 */
#define RCC_MP_RSTSCLRR_PORRSTF                   RCC_MP_RSTSCLRR_PORRSTF_Msk                        /*!< POR/PDR reset flag */
#define RCC_MP_RSTSCLRR_BORRSTF_Pos               (1U)
#define RCC_MP_RSTSCLRR_BORRSTF_Msk               (0x1U << RCC_MP_RSTSCLRR_BORRSTF_Pos)              /*!< 0x00000002 */
#define RCC_MP_RSTSCLRR_BORRSTF                   RCC_MP_RSTSCLRR_BORRSTF_Msk                        /*!< BOR reset flag */
#define RCC_MP_RSTSCLRR_PADRSTF_Pos               (2U)
#define RCC_MP_RSTSCLRR_PADRSTF_Msk               (0x1U << RCC_MP_RSTSCLRR_PADRSTF_Pos)              /*!< 0x00000004 */
#define RCC_MP_RSTSCLRR_PADRSTF                   RCC_MP_RSTSCLRR_PADRSTF_Msk                        /*!< NRST reset flag */
#define RCC_MP_RSTSCLRR_HCSSRSTF_Pos              (3U)
#define RCC_MP_RSTSCLRR_HCSSRSTF_Msk              (0x1U << RCC_MP_RSTSCLRR_HCSSRSTF_Pos)             /*!< 0x00000008 */
#define RCC_MP_RSTSCLRR_HCSSRSTF                  RCC_MP_RSTSCLRR_HCSSRSTF_Msk                       /*!< HSE CSS reset flag */
#define RCC_MP_RSTSCLRR_VCORERSTF_Pos             (4U)
#define RCC_MP_RSTSCLRR_VCORERSTF_Msk             (0x1U << RCC_MP_RSTSCLRR_VCORERSTF_Pos)            /*!< 0x00000010 */
#define RCC_MP_RSTSCLRR_VCORERSTF                 RCC_MP_RSTSCLRR_VCORERSTF_Msk                      /*!< VDDCORE reset flag */
#define RCC_MP_RSTSCLRR_MPSYSRSTF_Pos             (6U)
#define RCC_MP_RSTSCLRR_MPSYSRSTF_Msk             (0x1U << RCC_MP_RSTSCLRR_MPSYSRSTF_Pos)            /*!< 0x00000040 */
#define RCC_MP_RSTSCLRR_MPSYSRSTF                 RCC_MP_RSTSCLRR_MPSYSRSTF_Msk                      /*!< MPU System reset flag */
#define RCC_MP_RSTSCLRR_MCSYSRSTF_Pos             (7U)
#define RCC_MP_RSTSCLRR_MCSYSRSTF_Msk             (0x1U << RCC_MP_RSTSCLRR_MCSYSRSTF_Pos)            /*!< 0x00000080 */
#define RCC_MP_RSTSCLRR_MCSYSRSTF                 RCC_MP_RSTSCLRR_MCSYSRSTF_Msk                      /*!< MCU System reset flag */
#define RCC_MP_RSTSCLRR_IWDG1RSTF_Pos             (8U)
#define RCC_MP_RSTSCLRR_IWDG1RSTF_Msk             (0x1U << RCC_MP_RSTSCLRR_IWDG1RSTF_Pos)            /*!< 0x00000100 */
#define RCC_MP_RSTSCLRR_IWDG1RSTF                 RCC_MP_RSTSCLRR_IWDG1RSTF_Msk                      /*!< IWDG1 reset flag */
#define RCC_MP_RSTSCLRR_IWDG2RSTF_Pos             (9U)
#define RCC_MP_RSTSCLRR_IWDG2RSTF_Msk             (0x1U << RCC_MP_RSTSCLRR_IWDG2RSTF_Pos)            /*!< 0x00000200 */
#define RCC_MP_RSTSCLRR_IWDG2RSTF                 RCC_MP_RSTSCLRR_IWDG2RSTF_Msk                      /*!< IWDG2 reset flag */
#define RCC_MP_RSTSCLRR_STDBYRSTF_Pos             (11U)
#define RCC_MP_RSTSCLRR_STDBYRSTF_Msk             (0x1U << RCC_MP_RSTSCLRR_STDBYRSTF_Pos)            /*!< 0x00000800 */
#define RCC_MP_RSTSCLRR_STDBYRSTF                 RCC_MP_RSTSCLRR_STDBYRSTF_Msk                      /*!< System Standby reset flag */
#define RCC_MP_RSTSCLRR_CSTDBYRSTF_Pos            (12U)
#define RCC_MP_RSTSCLRR_CSTDBYRSTF_Msk            (0x1U << RCC_MP_RSTSCLRR_CSTDBYRSTF_Pos)           /*!< 0x00001000 */
#define RCC_MP_RSTSCLRR_CSTDBYRSTF                RCC_MP_RSTSCLRR_CSTDBYRSTF_Msk                     /*!< MPU CStandby reset flag */
#define RCC_MP_RSTSCLRR_MPUP0RSTF_Pos             (13U)
#define RCC_MP_RSTSCLRR_MPUP0RSTF_Msk             (0x1U << RCC_MP_RSTSCLRR_MPUP0RSTF_Pos)            /*!< 0x00002000 */
#define RCC_MP_RSTSCLRR_MPUP0RSTF                 RCC_MP_RSTSCLRR_MPUP0RSTF_Msk                      /*!< MPU processor 0 reset flag */
#define RCC_MP_RSTSCLRR_MPUP1RSTF_Pos             (14U)
#define RCC_MP_RSTSCLRR_MPUP1RSTF_Msk             (0x1U << RCC_MP_RSTSCLRR_MPUP1RSTF_Pos)            /*!< 0x00004000 */
#define RCC_MP_RSTSCLRR_MPUP1RSTF                 RCC_MP_RSTSCLRR_MPUP1RSTF_Msk                      /*!< MPU processor 1 reset flag */
#define RCC_MP_RSTSCLRR_SPARE_Pos                 (15U)
#define RCC_MP_RSTSCLRR_SPARE_Msk                 (0x1U << RCC_MP_RSTSCLRR_SPARE_Pos)                /*!< 0x00008000 */
#define RCC_MP_RSTSCLRR_SPARE                     RCC_MP_RSTSCLRR_SPARE_Msk                          /*!< Spare bits */

/**************  Bit definition for RCC_MP_IWDGFZSETR register  ***************/
#define RCC_MP_IWDGFZSETR_FZ_IWDG1_Pos            (0U)
#define RCC_MP_IWDGFZSETR_FZ_IWDG1_Msk            (0x1U << RCC_MP_IWDGFZSETR_FZ_IWDG1_Pos)           /*!< 0x00000001 */
#define RCC_MP_IWDGFZSETR_FZ_IWDG1                RCC_MP_IWDGFZSETR_FZ_IWDG1_Msk                     /*!< Freeze the IWDG1 clock */
#define RCC_MP_IWDGFZSETR_FZ_IWDG2_Pos            (1U)
#define RCC_MP_IWDGFZSETR_FZ_IWDG2_Msk            (0x1U << RCC_MP_IWDGFZSETR_FZ_IWDG2_Pos)           /*!< 0x00000002 */
#define RCC_MP_IWDGFZSETR_FZ_IWDG2                RCC_MP_IWDGFZSETR_FZ_IWDG2_Msk                     /*!< Freeze the IWDG2 clock */

/**************  Bit definition for RCC_MP_IWDGFZCLRR register  ***************/
#define RCC_MP_IWDGFZCLRR_FZ_IWDG1_Pos            (0U)
#define RCC_MP_IWDGFZCLRR_FZ_IWDG1_Msk            (0x1U << RCC_MP_IWDGFZCLRR_FZ_IWDG1_Pos)           /*!< 0x00000001 */
#define RCC_MP_IWDGFZCLRR_FZ_IWDG1                RCC_MP_IWDGFZCLRR_FZ_IWDG1_Msk                     /*!< Unfreeze the IWDG1 clock */
#define RCC_MP_IWDGFZCLRR_FZ_IWDG2_Pos            (1U)
#define RCC_MP_IWDGFZCLRR_FZ_IWDG2_Msk            (0x1U << RCC_MP_IWDGFZCLRR_FZ_IWDG2_Pos)           /*!< 0x00000002 */
#define RCC_MP_IWDGFZCLRR_FZ_IWDG2                RCC_MP_IWDGFZCLRR_FZ_IWDG2_Msk                     /*!< Unfreeze the IWDG2 clock */

/*****************  Bit definition for RCC_MP_CIER register  ******************/
#define RCC_MP_CIER_LSIRDYIE_Pos                  (0U)
#define RCC_MP_CIER_LSIRDYIE_Msk                  (0x1U << RCC_MP_CIER_LSIRDYIE_Pos)                 /*!< 0x00000001 */
#define RCC_MP_CIER_LSIRDYIE                      RCC_MP_CIER_LSIRDYIE_Msk                           /*!< LSI ready Interrupt Enable */
#define RCC_MP_CIER_LSERDYIE_Pos                  (1U)
#define RCC_MP_CIER_LSERDYIE_Msk                  (0x1U << RCC_MP_CIER_LSERDYIE_Pos)                 /*!< 0x00000002 */
#define RCC_MP_CIER_LSERDYIE                      RCC_MP_CIER_LSERDYIE_Msk                           /*!< LSE ready Interrupt Enable */
#define RCC_MP_CIER_HSIRDYIE_Pos                  (2U)
#define RCC_MP_CIER_HSIRDYIE_Msk                  (0x1U << RCC_MP_CIER_HSIRDYIE_Pos)                 /*!< 0x00000004 */
#define RCC_MP_CIER_HSIRDYIE                      RCC_MP_CIER_HSIRDYIE_Msk                           /*!< HSI ready Interrupt Enable */
#define RCC_MP_CIER_HSERDYIE_Pos                  (3U)
#define RCC_MP_CIER_HSERDYIE_Msk                  (0x1U << RCC_MP_CIER_HSERDYIE_Pos)                 /*!< 0x00000008 */
#define RCC_MP_CIER_HSERDYIE                      RCC_MP_CIER_HSERDYIE_Msk                           /*!< HSE ready Interrupt Enable */
#define RCC_MP_CIER_CSIRDYIE_Pos                  (4U)
#define RCC_MP_CIER_CSIRDYIE_Msk                  (0x1U << RCC_MP_CIER_CSIRDYIE_Pos)                 /*!< 0x00000010 */
#define RCC_MP_CIER_CSIRDYIE                      RCC_MP_CIER_CSIRDYIE_Msk                           /*!< CSI ready Interrupt Enable */
#define RCC_MP_CIER_PLL1DYIE_Pos                  (8U)
#define RCC_MP_CIER_PLL1DYIE_Msk                  (0x1U << RCC_MP_CIER_PLL1DYIE_Pos)                 /*!< 0x00000100 */
#define RCC_MP_CIER_PLL1DYIE                      RCC_MP_CIER_PLL1DYIE_Msk                           /*!< PLL1 ready Interrupt Enable */
#define RCC_MP_CIER_PLL2DYIE_Pos                  (9U)
#define RCC_MP_CIER_PLL2DYIE_Msk                  (0x1U << RCC_MP_CIER_PLL2DYIE_Pos)                 /*!< 0x00000200 */
#define RCC_MP_CIER_PLL2DYIE                      RCC_MP_CIER_PLL2DYIE_Msk                           /*!< PLL2 ready Interrupt Enable */
#define RCC_MP_CIER_PLL3DYIE_Pos                  (10U)
#define RCC_MP_CIER_PLL3DYIE_Msk                  (0x1U << RCC_MP_CIER_PLL3DYIE_Pos)                 /*!< 0x00000400 */
#define RCC_MP_CIER_PLL3DYIE                      RCC_MP_CIER_PLL3DYIE_Msk                           /*!< PLL3 ready Interrupt Enable */
#define RCC_MP_CIER_PLL4DYIE_Pos                  (11U)
#define RCC_MP_CIER_PLL4DYIE_Msk                  (0x1U << RCC_MP_CIER_PLL4DYIE_Pos)                 /*!< 0x00000800 */
#define RCC_MP_CIER_PLL4DYIE                      RCC_MP_CIER_PLL4DYIE_Msk                           /*!< PLL4 ready Interrupt Enable */
#define RCC_MP_CIER_LSECSSIE_Pos                  (16U)
#define RCC_MP_CIER_LSECSSIE_Msk                  (0x1U << RCC_MP_CIER_LSECSSIE_Pos)                 /*!< 0x00010000 */
#define RCC_MP_CIER_LSECSSIE                      RCC_MP_CIER_LSECSSIE_Msk                           /*!< LSE clock security system Interrupt Enable */
#define RCC_MP_CIER_WKUPIE_Pos                    (20U)
#define RCC_MP_CIER_WKUPIE_Msk                    (0x1U << RCC_MP_CIER_WKUPIE_Pos)                   /*!< 0x00100000 */
#define RCC_MP_CIER_WKUPIE                        RCC_MP_CIER_WKUPIE_Msk                             /*!< Wake up from CStop Interrupt Enable */

/*****************  Bit definition for RCC_MP_CIFR register  ******************/
#define RCC_MP_CIFR_LSIRDYF_Pos                   (0U)
#define RCC_MP_CIFR_LSIRDYF_Msk                   (0x1U << RCC_MP_CIFR_LSIRDYF_Pos)                  /*!< 0x00000001 */
#define RCC_MP_CIFR_LSIRDYF                       RCC_MP_CIFR_LSIRDYF_Msk                            /*!< LSI ready Interrupt Flag */
#define RCC_MP_CIFR_LSERDYF_Pos                   (1U)
#define RCC_MP_CIFR_LSERDYF_Msk                   (0x1U << RCC_MP_CIFR_LSERDYF_Pos)                  /*!< 0x00000002 */
#define RCC_MP_CIFR_LSERDYF                       RCC_MP_CIFR_LSERDYF_Msk                            /*!< LSE ready Interrupt Flag */
#define RCC_MP_CIFR_HSIRDYF_Pos                   (2U)
#define RCC_MP_CIFR_HSIRDYF_Msk                   (0x1U << RCC_MP_CIFR_HSIRDYF_Pos)                  /*!< 0x00000004 */
#define RCC_MP_CIFR_HSIRDYF                       RCC_MP_CIFR_HSIRDYF_Msk                            /*!< HSI ready Interrupt Flag */
#define RCC_MP_CIFR_HSERDYF_Pos                   (3U)
#define RCC_MP_CIFR_HSERDYF_Msk                   (0x1U << RCC_MP_CIFR_HSERDYF_Pos)                  /*!< 0x00000008 */
#define RCC_MP_CIFR_HSERDYF                       RCC_MP_CIFR_HSERDYF_Msk                            /*!< HSE ready Interrupt Flag */
#define RCC_MP_CIFR_CSIRDYF_Pos                   (4U)
#define RCC_MP_CIFR_CSIRDYF_Msk                   (0x1U << RCC_MP_CIFR_CSIRDYF_Pos)                  /*!< 0x00000010 */
#define RCC_MP_CIFR_CSIRDYF                       RCC_MP_CIFR_CSIRDYF_Msk                            /*!< CSI ready Interrupt Flag */
#define RCC_MP_CIFR_PLL1DYF_Pos                   (8U)
#define RCC_MP_CIFR_PLL1DYF_Msk                   (0x1U << RCC_MP_CIFR_PLL1DYF_Pos)                  /*!< 0x00000100 */
#define RCC_MP_CIFR_PLL1DYF                       RCC_MP_CIFR_PLL1DYF_Msk                            /*!< PLL1 ready Interrupt Flag */
#define RCC_MP_CIFR_PLL2DYF_Pos                   (9U)
#define RCC_MP_CIFR_PLL2DYF_Msk                   (0x1U << RCC_MP_CIFR_PLL2DYF_Pos)                  /*!< 0x00000200 */
#define RCC_MP_CIFR_PLL2DYF                       RCC_MP_CIFR_PLL2DYF_Msk                            /*!< PLL2 ready Interrupt Flag */
#define RCC_MP_CIFR_PLL3DYF_Pos                   (10U)
#define RCC_MP_CIFR_PLL3DYF_Msk                   (0x1U << RCC_MP_CIFR_PLL3DYF_Pos)                  /*!< 0x00000400 */
#define RCC_MP_CIFR_PLL3DYF                       RCC_MP_CIFR_PLL3DYF_Msk                            /*!< PLL3 ready Interrupt Flag */
#define RCC_MP_CIFR_PLL4DYF_Pos                   (11U)
#define RCC_MP_CIFR_PLL4DYF_Msk                   (0x1U << RCC_MP_CIFR_PLL4DYF_Pos)                  /*!< 0x00000800 */
#define RCC_MP_CIFR_PLL4DYF                       RCC_MP_CIFR_PLL4DYF_Msk                            /*!< PLL4 ready Interrupt Flag */
#define RCC_MP_CIFR_LSECSSF_Pos                   (16U)
#define RCC_MP_CIFR_LSECSSF_Msk                   (0x1U << RCC_MP_CIFR_LSECSSF_Pos)                  /*!< 0x00010000 */
#define RCC_MP_CIFR_LSECSSF                       RCC_MP_CIFR_LSECSSF_Msk                            /*!< LSE clock security system Interrupt Flag */
#define RCC_MP_CIFR_WKUPF_Pos                     (20U)
#define RCC_MP_CIFR_WKUPF_Msk                     (0x1U << RCC_MP_CIFR_WKUPF_Pos)                    /*!< 0x00100000 */
#define RCC_MP_CIFR_WKUPF                         RCC_MP_CIFR_WKUPF_Msk                              /*!< Wake up from CStop Interrupt Flag */

/****************  Bit definition for RCC_PWRLPDLYCR register  ****************/
#define RCC_PWRLPDLYCR_PWRLP_DLY_Pos              (0U)
#define RCC_PWRLPDLYCR_PWRLP_DLY_Msk              (0x3FFFFFU << RCC_PWRLPDLYCR_PWRLP_DLY_Pos)        /*!< 0x003FFFFF */
#define RCC_PWRLPDLYCR_PWRLP_DLY                  RCC_PWRLPDLYCR_PWRLP_DLY_Msk                       /*!< PWRLP_TEMPO value */
#define RCC_PWRLPDLYCR_PWRLP_DLY_0                (0x1U << RCC_PWRLPDLYCR_PWRLP_DLY_Pos)             /*!< 0x00000001 */
#define RCC_PWRLPDLYCR_PWRLP_DLY_1                (0x2U << RCC_PWRLPDLYCR_PWRLP_DLY_Pos)             /*!< 0x00000002 */
#define RCC_PWRLPDLYCR_PWRLP_DLY_2                (0x4U << RCC_PWRLPDLYCR_PWRLP_DLY_Pos)             /*!< 0x00000004 */
#define RCC_PWRLPDLYCR_PWRLP_DLY_3                (0x8U << RCC_PWRLPDLYCR_PWRLP_DLY_Pos)             /*!< 0x00000008 */
#define RCC_PWRLPDLYCR_PWRLP_DLY_4                (0x10U << RCC_PWRLPDLYCR_PWRLP_DLY_Pos)            /*!< 0x00000010 */
#define RCC_PWRLPDLYCR_PWRLP_DLY_5                (0x20U << RCC_PWRLPDLYCR_PWRLP_DLY_Pos)            /*!< 0x00000020 */
#define RCC_PWRLPDLYCR_PWRLP_DLY_6                (0x40U << RCC_PWRLPDLYCR_PWRLP_DLY_Pos)            /*!< 0x00000040 */
#define RCC_PWRLPDLYCR_PWRLP_DLY_7                (0x80U << RCC_PWRLPDLYCR_PWRLP_DLY_Pos)            /*!< 0x00000080 */
#define RCC_PWRLPDLYCR_PWRLP_DLY_8                (0x100U << RCC_PWRLPDLYCR_PWRLP_DLY_Pos)           /*!< 0x00000100 */
#define RCC_PWRLPDLYCR_PWRLP_DLY_9                (0x200U << RCC_PWRLPDLYCR_PWRLP_DLY_Pos)           /*!< 0x00000200 */
#define RCC_PWRLPDLYCR_PWRLP_DLY_10               (0x400U << RCC_PWRLPDLYCR_PWRLP_DLY_Pos)           /*!< 0x00000400 */
#define RCC_PWRLPDLYCR_PWRLP_DLY_11               (0x800U << RCC_PWRLPDLYCR_PWRLP_DLY_Pos)           /*!< 0x00000800 */
#define RCC_PWRLPDLYCR_PWRLP_DLY_12               (0x1000U << RCC_PWRLPDLYCR_PWRLP_DLY_Pos)          /*!< 0x00001000 */
#define RCC_PWRLPDLYCR_PWRLP_DLY_13               (0x2000U << RCC_PWRLPDLYCR_PWRLP_DLY_Pos)          /*!< 0x00002000 */
#define RCC_PWRLPDLYCR_PWRLP_DLY_14               (0x4000U << RCC_PWRLPDLYCR_PWRLP_DLY_Pos)          /*!< 0x00004000 */
#define RCC_PWRLPDLYCR_PWRLP_DLY_15               (0x8000U << RCC_PWRLPDLYCR_PWRLP_DLY_Pos)          /*!< 0x00008000 */
#define RCC_PWRLPDLYCR_PWRLP_DLY_16               (0x10000U << RCC_PWRLPDLYCR_PWRLP_DLY_Pos)         /*!< 0x00010000 */
#define RCC_PWRLPDLYCR_PWRLP_DLY_17               (0x20000U << RCC_PWRLPDLYCR_PWRLP_DLY_Pos)         /*!< 0x00020000 */
#define RCC_PWRLPDLYCR_PWRLP_DLY_18               (0x40000U << RCC_PWRLPDLYCR_PWRLP_DLY_Pos)         /*!< 0x00040000 */
#define RCC_PWRLPDLYCR_PWRLP_DLY_19               (0x80000U << RCC_PWRLPDLYCR_PWRLP_DLY_Pos)         /*!< 0x00080000 */
#define RCC_PWRLPDLYCR_PWRLP_DLY_20               (0x100000U << RCC_PWRLPDLYCR_PWRLP_DLY_Pos)        /*!< 0x00100000 */
#define RCC_PWRLPDLYCR_PWRLP_DLY_21               (0x200000U << RCC_PWRLPDLYCR_PWRLP_DLY_Pos)        /*!< 0x00200000 */
#define RCC_PWRLPDLYCR_MCTMPSKP_Pos               (24U)
#define RCC_PWRLPDLYCR_MCTMPSKP_Msk               (0x1U << RCC_PWRLPDLYCR_MCTMPSKP_Pos)              /*!< 0x01000000 */
#define RCC_PWRLPDLYCR_MCTMPSKP                   RCC_PWRLPDLYCR_MCTMPSKP_Msk                        /*!< Skip the PWR_DLY for MCU */

/***************  Bit definition for RCC_MP_RSTSSETR register  ****************/
#define RCC_MP_RSTSSETR_PORRSTF_Pos               (0U)
#define RCC_MP_RSTSSETR_PORRSTF_Msk               (0x1U << RCC_MP_RSTSSETR_PORRSTF_Pos)              /*!< 0x00000001 */
#define RCC_MP_RSTSSETR_PORRSTF                   RCC_MP_RSTSSETR_PORRSTF_Msk                        /*!< POR/PDR reset flag */
#define RCC_MP_RSTSSETR_BORRSTF_Pos               (1U)
#define RCC_MP_RSTSSETR_BORRSTF_Msk               (0x1U << RCC_MP_RSTSSETR_BORRSTF_Pos)              /*!< 0x00000002 */
#define RCC_MP_RSTSSETR_BORRSTF                   RCC_MP_RSTSSETR_BORRSTF_Msk                        /*!< BOR reset flag */
#define RCC_MP_RSTSSETR_PADRSTF_Pos               (2U)
#define RCC_MP_RSTSSETR_PADRSTF_Msk               (0x1U << RCC_MP_RSTSSETR_PADRSTF_Pos)              /*!< 0x00000004 */
#define RCC_MP_RSTSSETR_PADRSTF                   RCC_MP_RSTSSETR_PADRSTF_Msk                        /*!< NRST reset flag */
#define RCC_MP_RSTSSETR_HCSSRSTF_Pos              (3U)
#define RCC_MP_RSTSSETR_HCSSRSTF_Msk              (0x1U << RCC_MP_RSTSSETR_HCSSRSTF_Pos)             /*!< 0x00000008 */
#define RCC_MP_RSTSSETR_HCSSRSTF                  RCC_MP_RSTSSETR_HCSSRSTF_Msk                       /*!< HSE CSS reset flag */
#define RCC_MP_RSTSSETR_VCORERSTF_Pos             (4U)
#define RCC_MP_RSTSSETR_VCORERSTF_Msk             (0x1U << RCC_MP_RSTSSETR_VCORERSTF_Pos)            /*!< 0x00000010 */
#define RCC_MP_RSTSSETR_VCORERSTF                 RCC_MP_RSTSSETR_VCORERSTF_Msk                      /*!< VDDCORE reset flag */
#define RCC_MP_RSTSSETR_MPSYSRSTF_Pos             (6U)
#define RCC_MP_RSTSSETR_MPSYSRSTF_Msk             (0x1U << RCC_MP_RSTSSETR_MPSYSRSTF_Pos)            /*!< 0x00000040 */
#define RCC_MP_RSTSSETR_MPSYSRSTF                 RCC_MP_RSTSSETR_MPSYSRSTF_Msk                      /*!< MPU System reset flag */
#define RCC_MP_RSTSSETR_MCSYSRSTF_Pos             (7U)
#define RCC_MP_RSTSSETR_MCSYSRSTF_Msk             (0x1U << RCC_MP_RSTSSETR_MCSYSRSTF_Pos)            /*!< 0x00000080 */
#define RCC_MP_RSTSSETR_MCSYSRSTF                 RCC_MP_RSTSSETR_MCSYSRSTF_Msk                      /*!< MCU System reset flag */
#define RCC_MP_RSTSSETR_IWDG1RSTF_Pos             (8U)
#define RCC_MP_RSTSSETR_IWDG1RSTF_Msk             (0x1U << RCC_MP_RSTSSETR_IWDG1RSTF_Pos)            /*!< 0x00000100 */
#define RCC_MP_RSTSSETR_IWDG1RSTF                 RCC_MP_RSTSSETR_IWDG1RSTF_Msk                      /*!< IWDG1 reset flag */
#define RCC_MP_RSTSSETR_IWDG2RSTF_Pos             (9U)
#define RCC_MP_RSTSSETR_IWDG2RSTF_Msk             (0x1U << RCC_MP_RSTSSETR_IWDG2RSTF_Pos)            /*!< 0x00000200 */
#define RCC_MP_RSTSSETR_IWDG2RSTF                 RCC_MP_RSTSSETR_IWDG2RSTF_Msk                      /*!< IWDG2 reset flag */
#define RCC_MP_RSTSSETR_STDBYRSTF_Pos             (11U)
#define RCC_MP_RSTSSETR_STDBYRSTF_Msk             (0x1U << RCC_MP_RSTSSETR_STDBYRSTF_Pos)            /*!< 0x00000800 */
#define RCC_MP_RSTSSETR_STDBYRSTF                 RCC_MP_RSTSSETR_STDBYRSTF_Msk                      /*!< System Standby reset flag */
#define RCC_MP_RSTSSETR_CSTDBYRSTF_Pos            (12U)
#define RCC_MP_RSTSSETR_CSTDBYRSTF_Msk            (0x1U << RCC_MP_RSTSSETR_CSTDBYRSTF_Pos)           /*!< 0x00001000 */
#define RCC_MP_RSTSSETR_CSTDBYRSTF                RCC_MP_RSTSSETR_CSTDBYRSTF_Msk                     /*!< MPU CStandby reset flag */
#define RCC_MP_RSTSSETR_MPUP0RSTF_Pos             (13U)
#define RCC_MP_RSTSSETR_MPUP0RSTF_Msk             (0x1U << RCC_MP_RSTSSETR_MPUP0RSTF_Pos)            /*!< 0x00002000 */
#define RCC_MP_RSTSSETR_MPUP0RSTF                 RCC_MP_RSTSSETR_MPUP0RSTF_Msk                      /*!< MPU processor 0 reset flag */
#define RCC_MP_RSTSSETR_MPUP1RSTF_Pos             (14U)
#define RCC_MP_RSTSSETR_MPUP1RSTF_Msk             (0x1U << RCC_MP_RSTSSETR_MPUP1RSTF_Pos)            /*!< 0x00004000 */
#define RCC_MP_RSTSSETR_MPUP1RSTF                 RCC_MP_RSTSSETR_MPUP1RSTF_Msk                      /*!< MPU processor 1 reset flag */
#define RCC_MP_RSTSSETR_SPARE_Pos                 (15U)
#define RCC_MP_RSTSSETR_SPARE_Msk                 (0x1U << RCC_MP_RSTSSETR_SPARE_Pos)                /*!< 0x00008000 */
#define RCC_MP_RSTSSETR_SPARE                     RCC_MP_RSTSSETR_SPARE_Msk                          /*!< Spare bits */

/*****************  Bit definition for RCC_MCO1CFGR register  *****************/
#define RCC_MCO1CFGR_MCO1SEL_Pos                  (0U)
#define RCC_MCO1CFGR_MCO1SEL_Msk                  (0x7U << RCC_MCO1CFGR_MCO1SEL_Pos)                 /*!< 0x00000007 */
#define RCC_MCO1CFGR_MCO1SEL                      RCC_MCO1CFGR_MCO1SEL_Msk                           /*!< MCO1 clock output selection */
#define RCC_MCO1CFGR_MCO1SEL_0                    (0x1U << RCC_MCO1CFGR_MCO1SEL_Pos)                 /*!< 0x00000001 */
#define RCC_MCO1CFGR_MCO1SEL_1                    (0x2U << RCC_MCO1CFGR_MCO1SEL_Pos)                 /*!< 0x00000002 */
#define RCC_MCO1CFGR_MCO1SEL_2                    (0x4U << RCC_MCO1CFGR_MCO1SEL_Pos)                 /*!< 0x00000004 */
#define RCC_MCO1CFGR_MCO1DIV_Pos                  (4U)
#define RCC_MCO1CFGR_MCO1DIV_Msk                  (0xFU << RCC_MCO1CFGR_MCO1DIV_Pos)                 /*!< 0x000000F0 */
#define RCC_MCO1CFGR_MCO1DIV                      RCC_MCO1CFGR_MCO1DIV_Msk                           /*!< MCO1 prescaler */
#define RCC_MCO1CFGR_MCO1DIV_0                    (0x1U << RCC_MCO1CFGR_MCO1DIV_Pos)                /*!< 0x00000010 */
#define RCC_MCO1CFGR_MCO1DIV_1                    (0x2U << RCC_MCO1CFGR_MCO1DIV_Pos)                /*!< 0x00000020 */
#define RCC_MCO1CFGR_MCO1DIV_2                    (0x4U << RCC_MCO1CFGR_MCO1DIV_Pos)                /*!< 0x00000040 */
#define RCC_MCO1CFGR_MCO1DIV_3                    (0x8U << RCC_MCO1CFGR_MCO1DIV_Pos)                /*!< 0x00000080 */
#define RCC_MCO1CFGR_MCO1ON_Pos                   (12U)
#define RCC_MCO1CFGR_MCO1ON_Msk                   (0x1U << RCC_MCO1CFGR_MCO1ON_Pos)                  /*!< 0x00001000 */
#define RCC_MCO1CFGR_MCO1ON                       RCC_MCO1CFGR_MCO1ON_Msk                            /*!< Control of the MCO1 output */

/*****************  Bit definition for RCC_MCO2CFGR register  *****************/
#define RCC_MCO2CFGR_MCO2SEL_Pos                  (0U)
#define RCC_MCO2CFGR_MCO2SEL_Msk                  (0x7U << RCC_MCO2CFGR_MCO2SEL_Pos)                 /*!< 0x00000007 */
#define RCC_MCO2CFGR_MCO2SEL                      RCC_MCO2CFGR_MCO2SEL_Msk                           /*!< Micro-controller clock output 2 */
#define RCC_MCO2CFGR_MCO2SEL_0                    (0x1U << RCC_MCO2CFGR_MCO2SEL_Pos)                 /*!< 0x00000001 */
#define RCC_MCO2CFGR_MCO2SEL_1                    (0x2U << RCC_MCO2CFGR_MCO2SEL_Pos)                 /*!< 0x00000002 */
#define RCC_MCO2CFGR_MCO2SEL_2                    (0x4U << RCC_MCO2CFGR_MCO2SEL_Pos)                 /*!< 0x00000004 */
#define RCC_MCO2CFGR_MCO2DIV_Pos                  (4U)
#define RCC_MCO2CFGR_MCO2DIV_Msk                  (0xFU << RCC_MCO2CFGR_MCO2DIV_Pos)                 /*!< 0x000000F0 */
#define RCC_MCO2CFGR_MCO2DIV                      RCC_MCO2CFGR_MCO2DIV_Msk                           /*!< MCO2 prescaler */
#define RCC_MCO2CFGR_MCO2DIV_0                    (0x1U << RCC_MCO2CFGR_MCO2DIV_Pos)                /*!< 0x00000010 */
#define RCC_MCO2CFGR_MCO2DIV_1                    (0x2U << RCC_MCO2CFGR_MCO2DIV_Pos)                /*!< 0x00000020 */
#define RCC_MCO2CFGR_MCO2DIV_2                    (0x4U << RCC_MCO2CFGR_MCO2DIV_Pos)                /*!< 0x00000040 */
#define RCC_MCO2CFGR_MCO2DIV_3                    (0x8U << RCC_MCO2CFGR_MCO2DIV_Pos)                /*!< 0x00000080 */
#define RCC_MCO2CFGR_MCO2ON_Pos                   (12U)
#define RCC_MCO2CFGR_MCO2ON_Msk                   (0x1U << RCC_MCO2CFGR_MCO2ON_Pos)                  /*!< 0x00001000 */
#define RCC_MCO2CFGR_MCO2ON                       RCC_MCO2CFGR_MCO2ON_Msk                            /*!< Control of the MCO2 output */

/******************  Bit definition for RCC_OCRDYR register  ******************/
#define RCC_OCRDYR_HSIRDY_Pos                     (0U)
#define RCC_OCRDYR_HSIRDY_Msk                     (0x1U << RCC_OCRDYR_HSIRDY_Pos)                    /*!< 0x00000001 */
#define RCC_OCRDYR_HSIRDY                         RCC_OCRDYR_HSIRDY_Msk                              /*!< HSI clock ready flag */
#define RCC_OCRDYR_HSIDIVRDY_Pos                  (2U)
#define RCC_OCRDYR_HSIDIVRDY_Msk                  (0x1U << RCC_OCRDYR_HSIDIVRDY_Pos)                 /*!< 0x00000004 */
#define RCC_OCRDYR_HSIDIVRDY                      RCC_OCRDYR_HSIDIVRDY_Msk                           /*!< HSI divider ready flag */
#define RCC_OCRDYR_CSIRDY_Pos                     (4U)
#define RCC_OCRDYR_CSIRDY_Msk                     (0x1U << RCC_OCRDYR_CSIRDY_Pos)                    /*!< 0x00000010 */
#define RCC_OCRDYR_CSIRDY                         RCC_OCRDYR_CSIRDY_Msk                              /*!< CSI clock ready flag */
#define RCC_OCRDYR_HSERDY_Pos                     (8U)
#define RCC_OCRDYR_HSERDY_Msk                     (0x1U << RCC_OCRDYR_HSERDY_Pos)                    /*!< 0x00000100 */
#define RCC_OCRDYR_HSERDY                         RCC_OCRDYR_HSERDY_Msk                              /*!< HSE clock ready flag */
#define RCC_OCRDYR_MPUCKRDY_Pos                   (23U)
#define RCC_OCRDYR_MPUCKRDY_Msk                   (0x1U << RCC_OCRDYR_MPUCKRDY_Pos)                  /*!< 0x00800000 */
#define RCC_OCRDYR_MPUCKRDY                       RCC_OCRDYR_MPUCKRDY_Msk                            /*!< MPU clock ready flag */
#define RCC_OCRDYR_AXICKRDY_Pos                   (24U)
#define RCC_OCRDYR_AXICKRDY_Msk                   (0x1U << RCC_OCRDYR_AXICKRDY_Pos)                  /*!< 0x01000000 */
#define RCC_OCRDYR_AXICKRDY                       RCC_OCRDYR_AXICKRDY_Msk                            /*!< AXI sub-system clock ready flag */
#define RCC_OCRDYR_CKREST_Pos                     (25U)
#define RCC_OCRDYR_CKREST_Msk                     (0x1U << RCC_OCRDYR_CKREST_Pos)                    /*!< 0x02000000 */
#define RCC_OCRDYR_CKREST                         RCC_OCRDYR_CKREST_Msk                              /*!< Clock Restore State Machine Status */

/*****************  Bit definition for RCC_DBGCFGR register  ******************/
#define RCC_DBGCFGR_TRACEDIV_Pos                  (0U)
#define RCC_DBGCFGR_TRACEDIV_Msk                  (0x7U << RCC_DBGCFGR_TRACEDIV_Pos)                 /*!< 0x00000007 */
#define RCC_DBGCFGR_TRACEDIV                      RCC_DBGCFGR_TRACEDIV_Msk                           /*!< Clock divider for the trace clock (ck_trace) */
#define RCC_DBGCFGR_TRACEDIV_0                    (0x1U << RCC_DBGCFGR_TRACEDIV_Pos)                 /*!< 0x00000001 */
#define RCC_DBGCFGR_TRACEDIV_1                    (0x2U << RCC_DBGCFGR_TRACEDIV_Pos)                 /*!< 0x00000002 */
#define RCC_DBGCFGR_TRACEDIV_2                    (0x4U << RCC_DBGCFGR_TRACEDIV_Pos)                 /*!< 0x00000004 */
#define RCC_DBGCFGR_DBGCKEN_Pos                   (8U)
#define RCC_DBGCFGR_DBGCKEN_Msk                   (0x1U << RCC_DBGCFGR_DBGCKEN_Pos)                  /*!< 0x00000100 */
#define RCC_DBGCFGR_DBGCKEN                       RCC_DBGCFGR_DBGCKEN_Msk                            /*!< Clock enable for debug function */
#define RCC_DBGCFGR_TRACECKEN_Pos                 (9U)
#define RCC_DBGCFGR_TRACECKEN_Msk                 (0x1U << RCC_DBGCFGR_TRACECKEN_Pos)                /*!< 0x00000200 */
#define RCC_DBGCFGR_TRACECKEN                     RCC_DBGCFGR_TRACECKEN_Msk                          /*!< Clock enable for trace function */
#define RCC_DBGCFGR_DBGRST_Pos                    (12U)
#define RCC_DBGCFGR_DBGRST_Msk                    (0x1U << RCC_DBGCFGR_DBGRST_Pos)                   /*!< 0x00001000 */
#define RCC_DBGCFGR_DBGRST                        RCC_DBGCFGR_DBGRST_Msk                             /*!< Reset of the debug function */

/*****************  Bit definition for RCC_RCK3SELR register  *****************/
#define RCC_RCK3SELR_PLL3SRC_Pos                  (0U)
#define RCC_RCK3SELR_PLL3SRC_Msk                  (0x3U << RCC_RCK3SELR_PLL3SRC_Pos)                 /*!< 0x00000003 */
#define RCC_RCK3SELR_PLL3SRC                      RCC_RCK3SELR_PLL3SRC_Msk                           /*!< Reference clock selection for PLL3 */
#define RCC_RCK3SELR_PLL3SRC_0                    (0x1U << RCC_RCK3SELR_PLL3SRC_Pos)                 /*!< 0x00000001 */
#define RCC_RCK3SELR_PLL3SRC_1                    (0x2U << RCC_RCK3SELR_PLL3SRC_Pos)                 /*!< 0x00000002 */
#define RCC_RCK3SELR_PLL3SRCRDY_Pos               (31U)
#define RCC_RCK3SELR_PLL3SRCRDY_Msk               (0x1U << RCC_RCK3SELR_PLL3SRCRDY_Pos)              /*!< 0x80000000 */
#define RCC_RCK3SELR_PLL3SRCRDY                   RCC_RCK3SELR_PLL3SRCRDY_Msk                        /*!< PLL3 reference clock switch status */

/*****************  Bit definition for RCC_RCK4SELR register  *****************/
#define RCC_RCK4SELR_PLL4SRC_Pos                  (0U)
#define RCC_RCK4SELR_PLL4SRC_Msk                  (0x3U << RCC_RCK4SELR_PLL4SRC_Pos)                 /*!< 0x00000003 */
#define RCC_RCK4SELR_PLL4SRC                      RCC_RCK4SELR_PLL4SRC_Msk                           /*!< Reference clock selection for PLL4 */
#define RCC_RCK4SELR_PLL4SRC_0                    (0x1U << RCC_RCK4SELR_PLL4SRC_Pos)                 /*!< 0x00000001 */
#define RCC_RCK4SELR_PLL4SRC_1                    (0x2U << RCC_RCK4SELR_PLL4SRC_Pos)                 /*!< 0x00000002 */
#define RCC_RCK4SELR_PLL4SRCRDY_Pos               (31U)
#define RCC_RCK4SELR_PLL4SRCRDY_Msk               (0x1U << RCC_RCK4SELR_PLL4SRCRDY_Pos)              /*!< 0x80000000 */
#define RCC_RCK4SELR_PLL4SRCRDY                   RCC_RCK4SELR_PLL4SRCRDY_Msk                        /*!< PLL4 reference clock switch status */

/****************  Bit definition for RCC_TIMG1PRER register  *****************/
#define RCC_TIMG1PRER_TIMG1PRE_Pos                (0U)
#define RCC_TIMG1PRER_TIMG1PRE_Msk                (0x1U << RCC_TIMG1PRER_TIMG1PRE_Pos)               /*!< 0x00000001 */
#define RCC_TIMG1PRER_TIMG1PRE                    RCC_TIMG1PRER_TIMG1PRE_Msk                         /*!< Timers clocks prescaler selection */
#define RCC_TIMG1PRER_TIMG1PRERDY_Pos             (31U)
#define RCC_TIMG1PRER_TIMG1PRERDY_Msk             (0x1U << RCC_TIMG1PRER_TIMG1PRERDY_Pos)            /*!< 0x80000000 */
#define RCC_TIMG1PRER_TIMG1PRERDY                 RCC_TIMG1PRER_TIMG1PRERDY_Msk                      /*!< Timers clocks prescaler status */

/****************  Bit definition for RCC_TIMG2PRER register  *****************/
#define RCC_TIMG2PRER_TIMG2PRE_Pos                (0U)
#define RCC_TIMG2PRER_TIMG2PRE_Msk                (0x1U << RCC_TIMG2PRER_TIMG2PRE_Pos)               /*!< 0x00000001 */
#define RCC_TIMG2PRER_TIMG2PRE                    RCC_TIMG2PRER_TIMG2PRE_Msk                         /*!< Timers clocks prescaler selection */
#define RCC_TIMG2PRER_TIMG2PRERDY_Pos             (31U)
#define RCC_TIMG2PRER_TIMG2PRERDY_Msk             (0x1U << RCC_TIMG2PRER_TIMG2PRERDY_Pos)            /*!< 0x80000000 */
#define RCC_TIMG2PRER_TIMG2PRERDY                 RCC_TIMG2PRER_TIMG2PRERDY_Msk                      /*!< Timers clocks prescaler status */

/*****************  Bit definition for RCC_MCUDIVR register  ******************/
#define RCC_MCUDIVR_MCUDIV_Pos                    (0U)
#define RCC_MCUDIVR_MCUDIV_Msk                    (0xFU << RCC_MCUDIVR_MCUDIV_Pos)                   /*!< 0x0000000F */
#define RCC_MCUDIVR_MCUDIV                        RCC_MCUDIVR_MCUDIV_Msk                             /*!< MCU clock divider */
#define RCC_MCUDIVR_MCUDIV_0                      (0x1U << RCC_MCUDIVR_MCUDIV_Pos)                   /*!< 0x00000001 */
#define RCC_MCUDIVR_MCUDIV_1                      (0x2U << RCC_MCUDIVR_MCUDIV_Pos)                   /*!< 0x00000002 */
#define RCC_MCUDIVR_MCUDIV_2                      (0x4U << RCC_MCUDIVR_MCUDIV_Pos)                   /*!< 0x00000004 */
#define RCC_MCUDIVR_MCUDIV_3                      (0x8U << RCC_MCUDIVR_MCUDIV_Pos)                   /*!< 0x00000008 */
#define RCC_MCUDIVR_MCUDIVRDY_Pos                 (31U)
#define RCC_MCUDIVR_MCUDIVRDY_Msk                 (0x1U << RCC_MCUDIVR_MCUDIVRDY_Pos)                /*!< 0x80000000 */
#define RCC_MCUDIVR_MCUDIVRDY                     RCC_MCUDIVR_MCUDIVRDY_Msk                          /*!< MCU clock prescaler status */

/*****************  Bit definition for RCC_APB1DIVR register  *****************/
#define RCC_APB1DIVR_APB1DIV_Pos                  (0U)
#define RCC_APB1DIVR_APB1DIV_Msk                  (0x7U << RCC_APB1DIVR_APB1DIV_Pos)                 /*!< 0x00000007 */
#define RCC_APB1DIVR_APB1DIV                      RCC_APB1DIVR_APB1DIV_Msk                           /*!< APB1 clock divider */
#define RCC_APB1DIVR_APB1DIV_0                    (0x1U << RCC_APB1DIVR_APB1DIV_Pos)                 /*!< 0x00000001 */
#define RCC_APB1DIVR_APB1DIV_1                    (0x2U << RCC_APB1DIVR_APB1DIV_Pos)                 /*!< 0x00000002 */
#define RCC_APB1DIVR_APB1DIV_2                    (0x4U << RCC_APB1DIVR_APB1DIV_Pos)                 /*!< 0x00000004 */
#define RCC_APB1DIVR_APB1DIVRDY_Pos               (31U)
#define RCC_APB1DIVR_APB1DIVRDY_Msk               (0x1U << RCC_APB1DIVR_APB1DIVRDY_Pos)              /*!< 0x80000000 */
#define RCC_APB1DIVR_APB1DIVRDY                   RCC_APB1DIVR_APB1DIVRDY_Msk                        /*!< APB1 clock prescaler status */

/*****************  Bit definition for RCC_APB2DIVR register  *****************/
#define RCC_APB2DIVR_APB2DIV_Pos                  (0U)
#define RCC_APB2DIVR_APB2DIV_Msk                  (0x7U << RCC_APB2DIVR_APB2DIV_Pos)                 /*!< 0x00000007 */
#define RCC_APB2DIVR_APB2DIV                      RCC_APB2DIVR_APB2DIV_Msk                           /*!< APB2 clock divider */
#define RCC_APB2DIVR_APB2DIV_0                    (0x1U << RCC_APB2DIVR_APB2DIV_Pos)                 /*!< 0x00000001 */
#define RCC_APB2DIVR_APB2DIV_1                    (0x2U << RCC_APB2DIVR_APB2DIV_Pos)                 /*!< 0x00000002 */
#define RCC_APB2DIVR_APB2DIV_2                    (0x4U << RCC_APB2DIVR_APB2DIV_Pos)                 /*!< 0x00000004 */
#define RCC_APB2DIVR_APB2DIVRDY_Pos               (31U)
#define RCC_APB2DIVR_APB2DIVRDY_Msk               (0x1U << RCC_APB2DIVR_APB2DIVRDY_Pos)              /*!< 0x80000000 */
#define RCC_APB2DIVR_APB2DIVRDY                   RCC_APB2DIVR_APB2DIVRDY_Msk                        /*!< APB2 clock prescaler status */

/*****************  Bit definition for RCC_APB3DIVR register  *****************/
#define RCC_APB3DIVR_APB3DIV_Pos                  (0U)
#define RCC_APB3DIVR_APB3DIV_Msk                  (0x7U << RCC_APB3DIVR_APB3DIV_Pos)                 /*!< 0x00000007 */
#define RCC_APB3DIVR_APB3DIV                      RCC_APB3DIVR_APB3DIV_Msk                           /*!< APB3 clock divider */
#define RCC_APB3DIVR_APB3DIV_0                    (0x1U << RCC_APB3DIVR_APB3DIV_Pos)                 /*!< 0x00000001 */
#define RCC_APB3DIVR_APB3DIV_1                    (0x2U << RCC_APB3DIVR_APB3DIV_Pos)                 /*!< 0x00000002 */
#define RCC_APB3DIVR_APB3DIV_2                    (0x4U << RCC_APB3DIVR_APB3DIV_Pos)                 /*!< 0x00000004 */
#define RCC_APB3DIVR_APB3DIVRDY_Pos               (31U)
#define RCC_APB3DIVR_APB3DIVRDY_Msk               (0x1U << RCC_APB3DIVR_APB3DIVRDY_Pos)              /*!< 0x80000000 */
#define RCC_APB3DIVR_APB3DIVRDY                   RCC_APB3DIVR_APB3DIVRDY_Msk                        /*!< APB3 clock prescaler status */

/******************  Bit definition for RCC_PLL3CR register  ******************/
#define RCC_PLL3CR_PLLON_Pos                      (0U)
#define RCC_PLL3CR_PLLON_Msk                      (0x1U << RCC_PLL3CR_PLLON_Pos)                     /*!< 0x00000001 */
#define RCC_PLL3CR_PLLON                          RCC_PLL3CR_PLLON_Msk                               /*!< PLL3 enable */
#define RCC_PLL3CR_PLL3RDY_Pos                    (1U)
#define RCC_PLL3CR_PLL3RDY_Msk                    (0x1U << RCC_PLL3CR_PLL3RDY_Pos)                   /*!< 0x00000002 */
#define RCC_PLL3CR_PLL3RDY                        RCC_PLL3CR_PLL3RDY_Msk                             /*!< PLL3 clock ready flag */
#define RCC_PLL3CR_SSCG_CTRL_Pos                  (2U)
#define RCC_PLL3CR_SSCG_CTRL_Msk                  (0x1U << RCC_PLL3CR_SSCG_CTRL_Pos)                 /*!< 0x00000004 */
#define RCC_PLL3CR_SSCG_CTRL                      RCC_PLL3CR_SSCG_CTRL_Msk                           /*!< Clock Spreading Generator of PLL3 enable */
#define RCC_PLL3CR_DIVPEN_Pos                     (4U)
#define RCC_PLL3CR_DIVPEN_Msk                     (0x1U << RCC_PLL3CR_DIVPEN_Pos)                    /*!< 0x00000010 */
#define RCC_PLL3CR_DIVPEN                         RCC_PLL3CR_DIVPEN_Msk                              /*!< PLL3 DIVP divider output enable */
#define RCC_PLL3CR_DIVQEN_Pos                     (5U)
#define RCC_PLL3CR_DIVQEN_Msk                     (0x1U << RCC_PLL3CR_DIVQEN_Pos)                    /*!< 0x00000020 */
#define RCC_PLL3CR_DIVQEN                         RCC_PLL3CR_DIVQEN_Msk                              /*!< PLL3 DIVQ divider output enable */
#define RCC_PLL3CR_DIVREN_Pos                     (6U)
#define RCC_PLL3CR_DIVREN_Msk                     (0x1U << RCC_PLL3CR_DIVREN_Pos)                    /*!< 0x00000040 */
#define RCC_PLL3CR_DIVREN                         RCC_PLL3CR_DIVREN_Msk                              /*!< PLL3 DIVR divider output enable */

/****************  Bit definition for RCC_PLL3CFGR1 register  *****************/
#define RCC_PLL3CFGR1_DIVN_Pos                    (0U)
#define RCC_PLL3CFGR1_DIVN_Msk                    (0x1FFU << RCC_PLL3CFGR1_DIVN_Pos)                 /*!< 0x000001FF */
#define RCC_PLL3CFGR1_DIVN                        RCC_PLL3CFGR1_DIVN_Msk                             /*!< Multiplication factor for PLL3 VCO */
#define RCC_PLL3CFGR1_DIVN_0                      (0x1U << RCC_PLL3CFGR1_DIVN_Pos)                   /*!< 0x00000001 */
#define RCC_PLL3CFGR1_DIVN_1                      (0x2U << RCC_PLL3CFGR1_DIVN_Pos)                   /*!< 0x00000002 */
#define RCC_PLL3CFGR1_DIVN_2                      (0x4U << RCC_PLL3CFGR1_DIVN_Pos)                   /*!< 0x00000004 */
#define RCC_PLL3CFGR1_DIVN_3                      (0x8U << RCC_PLL3CFGR1_DIVN_Pos)                   /*!< 0x00000008 */
#define RCC_PLL3CFGR1_DIVN_4                      (0x10U << RCC_PLL3CFGR1_DIVN_Pos)                  /*!< 0x00000010 */
#define RCC_PLL3CFGR1_DIVN_5                      (0x20U << RCC_PLL3CFGR1_DIVN_Pos)                  /*!< 0x00000020 */
#define RCC_PLL3CFGR1_DIVN_6                      (0x40U << RCC_PLL3CFGR1_DIVN_Pos)                  /*!< 0x00000040 */
#define RCC_PLL3CFGR1_DIVN_7                      (0x80U << RCC_PLL3CFGR1_DIVN_Pos)                  /*!< 0x00000080 */
#define RCC_PLL3CFGR1_DIVN_8                      (0x100U << RCC_PLL3CFGR1_DIVN_Pos)                 /*!< 0x00000100 */
#define RCC_PLL3CFGR1_DIVM3_Pos                   (16U)
#define RCC_PLL3CFGR1_DIVM3_Msk                   (0x3FU << RCC_PLL3CFGR1_DIVM3_Pos)                 /*!< 0x003F0000 */
#define RCC_PLL3CFGR1_DIVM3                       RCC_PLL3CFGR1_DIVM3_Msk                            /*!< Prescaler for PLL3 */
#define RCC_PLL3CFGR1_DIVM3_0                     (0x1U << RCC_PLL3CFGR1_DIVM3_Pos)              /*!< 0x00010000 */
#define RCC_PLL3CFGR1_DIVM3_1                     (0x2U << RCC_PLL3CFGR1_DIVM3_Pos)              /*!< 0x00020000 */
#define RCC_PLL3CFGR1_DIVM3_2                     (0x4U << RCC_PLL3CFGR1_DIVM3_Pos)              /*!< 0x00040000 */
#define RCC_PLL3CFGR1_DIVM3_3                     (0x8U << RCC_PLL3CFGR1_DIVM3_Pos)              /*!< 0x00080000 */
#define RCC_PLL3CFGR1_DIVM3_4                     (0x10U << RCC_PLL3CFGR1_DIVM3_Pos)             /*!< 0x00100000 */
#define RCC_PLL3CFGR1_DIVM3_5                     (0x20U << RCC_PLL3CFGR1_DIVM3_Pos)             /*!< 0x00200000 */
#define RCC_PLL3CFGR1_IFRGE_Pos                   (24U)
#define RCC_PLL3CFGR1_IFRGE_Msk                   (0x3U << RCC_PLL3CFGR1_IFRGE_Pos)                  /*!< 0x03000000 */
#define RCC_PLL3CFGR1_IFRGE                       RCC_PLL3CFGR1_IFRGE_Msk                            /*!< PLL3 input frequency range */
#define RCC_PLL3CFGR1_IFRGE_0                     (0x1U << RCC_PLL3CFGR1_IFRGE_Pos)            /*!< 0x01000000 */
#define RCC_PLL3CFGR1_IFRGE_1                     (0x2U << RCC_PLL3CFGR1_IFRGE_Pos)            /*!< 0x02000000 */

/****************  Bit definition for RCC_PLL3CFGR2 register  *****************/
#define RCC_PLL3CFGR2_DIVP_Pos                    (0U)
#define RCC_PLL3CFGR2_DIVP_Msk                    (0x7FU << RCC_PLL3CFGR2_DIVP_Pos)                  /*!< 0x0000007F */
#define RCC_PLL3CFGR2_DIVP                        RCC_PLL3CFGR2_DIVP_Msk                             /*!< PLL3 DIVP division factor */
#define RCC_PLL3CFGR2_DIVP_0                      (0x1U << RCC_PLL3CFGR2_DIVP_Pos)                   /*!< 0x00000001 */
#define RCC_PLL3CFGR2_DIVP_1                      (0x2U << RCC_PLL3CFGR2_DIVP_Pos)                   /*!< 0x00000002 */
#define RCC_PLL3CFGR2_DIVP_2                      (0x4U << RCC_PLL3CFGR2_DIVP_Pos)                   /*!< 0x00000004 */
#define RCC_PLL3CFGR2_DIVP_3                      (0x8U << RCC_PLL3CFGR2_DIVP_Pos)                   /*!< 0x00000008 */
#define RCC_PLL3CFGR2_DIVP_4                      (0x10U << RCC_PLL3CFGR2_DIVP_Pos)                  /*!< 0x00000010 */
#define RCC_PLL3CFGR2_DIVP_5                      (0x20U << RCC_PLL3CFGR2_DIVP_Pos)                  /*!< 0x00000020 */
#define RCC_PLL3CFGR2_DIVP_6                      (0x40U << RCC_PLL3CFGR2_DIVP_Pos)                  /*!< 0x00000040 */
#define RCC_PLL3CFGR2_DIVQ_Pos                    (8U)
#define RCC_PLL3CFGR2_DIVQ_Msk                    (0x7FU << RCC_PLL3CFGR2_DIVQ_Pos)                  /*!< 0x00007F00 */
#define RCC_PLL3CFGR2_DIVQ                        RCC_PLL3CFGR2_DIVQ_Msk                             /*!< PLL3 DIVQ division factor */
#define RCC_PLL3CFGR2_DIVQ_0                      (0x1U << RCC_PLL3CFGR2_DIVQ_Pos)                 /*!< 0x00000100 */
#define RCC_PLL3CFGR2_DIVQ_1                      (0x2U << RCC_PLL3CFGR2_DIVQ_Pos)                 /*!< 0x00000200 */
#define RCC_PLL3CFGR2_DIVQ_2                      (0x4U << RCC_PLL3CFGR2_DIVQ_Pos)                 /*!< 0x00000400 */
#define RCC_PLL3CFGR2_DIVQ_3                      (0x8U << RCC_PLL3CFGR2_DIVQ_Pos)                 /*!< 0x00000800 */
#define RCC_PLL3CFGR2_DIVQ_4                      (0x10U << RCC_PLL3CFGR2_DIVQ_Pos)                /*!< 0x00001000 */
#define RCC_PLL3CFGR2_DIVQ_5                      (0x20U << RCC_PLL3CFGR2_DIVQ_Pos)                /*!< 0x00002000 */
#define RCC_PLL3CFGR2_DIVQ_6                      (0x40U << RCC_PLL3CFGR2_DIVQ_Pos)                /*!< 0x00004000 */
#define RCC_PLL3CFGR2_DIVR_Pos                    (16U)
#define RCC_PLL3CFGR2_DIVR_Msk                    (0x7FU << RCC_PLL3CFGR2_DIVR_Pos)                  /*!< 0x007F0000 */
#define RCC_PLL3CFGR2_DIVR                        RCC_PLL3CFGR2_DIVR_Msk                             /*!< PLL3 DIVR division factor */
#define RCC_PLL3CFGR2_DIVR_0                      (0x1U << RCC_PLL3CFGR2_DIVR_Pos)               /*!< 0x00010000 */
#define RCC_PLL3CFGR2_DIVR_1                      (0x2U << RCC_PLL3CFGR2_DIVR_Pos)               /*!< 0x00020000 */
#define RCC_PLL3CFGR2_DIVR_2                      (0x4U << RCC_PLL3CFGR2_DIVR_Pos)               /*!< 0x00040000 */
#define RCC_PLL3CFGR2_DIVR_3                      (0x8U << RCC_PLL3CFGR2_DIVR_Pos)               /*!< 0x00080000 */
#define RCC_PLL3CFGR2_DIVR_4                      (0x10U << RCC_PLL3CFGR2_DIVR_Pos)              /*!< 0x00100000 */
#define RCC_PLL3CFGR2_DIVR_5                      (0x20U << RCC_PLL3CFGR2_DIVR_Pos)              /*!< 0x00200000 */
#define RCC_PLL3CFGR2_DIVR_6                      (0x40U << RCC_PLL3CFGR2_DIVR_Pos)              /*!< 0x00400000 */

/****************  Bit definition for RCC_PLL3FRACR register  *****************/
#define RCC_PLL3FRACR_FRACV_Pos                   (3U)
#define RCC_PLL3FRACR_FRACV_Msk                   (0x1FFFU << RCC_PLL3FRACR_FRACV_Pos)               /*!< 0x0000FFF8 */
#define RCC_PLL3FRACR_FRACV                       RCC_PLL3FRACR_FRACV_Msk                            /*!< Fractional part of the multiplication factor for PLL3 VCO */
#define RCC_PLL3FRACR_FRACV_0                     (0x1U << RCC_PLL3FRACR_FRACV_Pos)                  /*!< 0x00000008 */
#define RCC_PLL3FRACR_FRACV_1                     (0x2U << RCC_PLL3FRACR_FRACV_Pos)                 /*!< 0x00000010 */
#define RCC_PLL3FRACR_FRACV_2                     (0x4U << RCC_PLL3FRACR_FRACV_Pos)                 /*!< 0x00000020 */
#define RCC_PLL3FRACR_FRACV_3                     (0x8U << RCC_PLL3FRACR_FRACV_Pos)                 /*!< 0x00000040 */
#define RCC_PLL3FRACR_FRACV_4                     (0x10U << RCC_PLL3FRACR_FRACV_Pos)                 /*!< 0x00000080 */
#define RCC_PLL3FRACR_FRACV_5                     (0x20U << RCC_PLL3FRACR_FRACV_Pos)                /*!< 0x00000100 */
#define RCC_PLL3FRACR_FRACV_6                     (0x40U << RCC_PLL3FRACR_FRACV_Pos)                /*!< 0x00000200 */
#define RCC_PLL3FRACR_FRACV_7                     (0x80U << RCC_PLL3FRACR_FRACV_Pos)                /*!< 0x00000400 */
#define RCC_PLL3FRACR_FRACV_8                     (0x100U << RCC_PLL3FRACR_FRACV_Pos)                /*!< 0x00000800 */
#define RCC_PLL3FRACR_FRACV_9                     (0x200U << RCC_PLL3FRACR_FRACV_Pos)               /*!< 0x00001000 */
#define RCC_PLL3FRACR_FRACV_10                    (0x400U << RCC_PLL3FRACR_FRACV_Pos)               /*!< 0x00002000 */
#define RCC_PLL3FRACR_FRACV_11                    (0x800U << RCC_PLL3FRACR_FRACV_Pos)               /*!< 0x00004000 */
#define RCC_PLL3FRACR_FRACV_12                    (0x1000U << RCC_PLL3FRACR_FRACV_Pos)               /*!< 0x00008000 */
#define RCC_PLL3FRACR_FRACLE_Pos                  (16U)
#define RCC_PLL3FRACR_FRACLE_Msk                  (0x1U << RCC_PLL3FRACR_FRACLE_Pos)                 /*!< 0x00010000 */
#define RCC_PLL3FRACR_FRACLE                      RCC_PLL3FRACR_FRACLE_Msk                           /*!< PLL3 fractional latch enable */

/********************  Bit definition for RCC_PLL3CSGR register********************/
#define RCC_PLL3CSGR_MOD_PER_Pos              (0U)
#define RCC_PLL3CSGR_MOD_PER_Msk              (0x1FFFU << RCC_PLL3CSGR_MOD_PER_Pos) /*!< 0x00001FFF */
#define RCC_PLL3CSGR_MOD_PER                  RCC_PLL3CSGR_MOD_PER_Msk         /*Modulation Period Adjustment for PLL3*/
#define RCC_PLL3CSGR_TPDFN_DIS_Pos            (13U)
#define RCC_PLL3CSGR_TPDFN_DIS_Msk            (0x1U << RCC_PLL3CSGR_TPDFN_DIS_Pos) /*!< 0x00002000 */
#define RCC_PLL3CSGR_TPDFN_DIS                RCC_PLL3CSGR_TPDFN_DIS_Msk       /*Dithering TPDF noise control*/
#define RCC_PLL3CSGR_RPDFN_DIS_Pos            (14U)
#define RCC_PLL3CSGR_RPDFN_DIS_Msk            (0x1U << RCC_PLL3CSGR_RPDFN_DIS_Pos) /*!< 0x00004000 */
#define RCC_PLL3CSGR_RPDFN_DIS                RCC_PLL3CSGR_RPDFN_DIS_Msk       /*Dithering RPDF noise control*/
#define RCC_PLL3CSGR_SSCG_MODE_Pos            (15U)
#define RCC_PLL3CSGR_SSCG_MODE_Msk            (0x1U << RCC_PLL3CSGR_SSCG_MODE_Pos) /*!< 0x00008000 */
#define RCC_PLL3CSGR_SSCG_MODE                RCC_PLL3CSGR_SSCG_MODE_Msk       /*Spread spectrum clock generator mode*/
#define RCC_PLL3CSGR_INC_STEP_Pos             (16U)
#define RCC_PLL3CSGR_INC_STEP_Msk             (0x7FFFU << RCC_PLL3CSGR_INC_STEP_Pos) /*!< 0x7FFF0000 */
#define RCC_PLL3CSGR_INC_STEP_Pos             (16U)
#define RCC_PLL3CSGR_INC_STEP_Msk             (0x7FFFU << RCC_PLL3CSGR_INC_STEP_Pos) /*!< 0x7FFF0000 */
#define RCC_PLL3CSGR_INC_STEP                 RCC_PLL3CSGR_INC_STEP_Msk        /*Modulation Depth Adjustment for PLL3*/

/******************  Bit definition for RCC_PLL4CR register  ******************/
#define RCC_PLL4CR_PLLON_Pos                      (0U)
#define RCC_PLL4CR_PLLON_Msk                      (0x1U << RCC_PLL4CR_PLLON_Pos)                     /*!< 0x00000001 */
#define RCC_PLL4CR_PLLON                          RCC_PLL4CR_PLLON_Msk                               /*!< PLL4 enable */
#define RCC_PLL4CR_PLL4RDY_Pos                    (1U)
#define RCC_PLL4CR_PLL4RDY_Msk                    (0x1U << RCC_PLL4CR_PLL4RDY_Pos)                   /*!< 0x00000002 */
#define RCC_PLL4CR_PLL4RDY                        RCC_PLL4CR_PLL4RDY_Msk                             /*!< PLL4 clock ready flag */
#define RCC_PLL4CR_SSCG_CTRL_Pos                  (2U)
#define RCC_PLL4CR_SSCG_CTRL_Msk                  (0x1U << RCC_PLL4CR_SSCG_CTRL_Pos)                 /*!< 0x00000004 */
#define RCC_PLL4CR_SSCG_CTRL                      RCC_PLL4CR_SSCG_CTRL_Msk                           /*Spread Spectrum Clock Generator of PLL4 enable*/
#define RCC_PLL4CR_DIVPEN_Pos                     (4U)
#define RCC_PLL4CR_DIVPEN_Msk                     (0x1U << RCC_PLL4CR_DIVPEN_Pos)                    /*!< 0x00000010 */
#define RCC_PLL4CR_DIVPEN                         RCC_PLL4CR_DIVPEN_Msk                              /*!< PLL4 DIVP divider output enable */
#define RCC_PLL4CR_DIVQEN_Pos                     (5U)
#define RCC_PLL4CR_DIVQEN_Msk                     (0x1U << RCC_PLL4CR_DIVQEN_Pos)                    /*!< 0x00000020 */
#define RCC_PLL4CR_DIVQEN                         RCC_PLL4CR_DIVQEN_Msk                              /*!< PLL4 DIVQ divider output enable */
#define RCC_PLL4CR_DIVREN_Pos                     (6U)
#define RCC_PLL4CR_DIVREN_Msk                     (0x1U << RCC_PLL4CR_DIVREN_Pos)                    /*!< 0x00000040 */
#define RCC_PLL4CR_DIVREN                         RCC_PLL4CR_DIVREN_Msk                              /*!< PLL4 DIVR divider output enable */

/****************  Bit definition for RCC_PLL4CFGR1 register  *****************/
#define RCC_PLL4CFGR1_DIVN_Pos                    (0U)
#define RCC_PLL4CFGR1_DIVN_Msk                    (0x1FFU << RCC_PLL4CFGR1_DIVN_Pos)                 /*!< 0x000001FF */
#define RCC_PLL4CFGR1_DIVN                        RCC_PLL4CFGR1_DIVN_Msk                             /*!< Multiplication factor for PLL4 VCO */
#define RCC_PLL4CFGR1_DIVN_0                      (0x1U << RCC_PLL4CFGR1_DIVN_Pos)                   /*!< 0x00000001 */
#define RCC_PLL4CFGR1_DIVN_1                      (0x2U << RCC_PLL4CFGR1_DIVN_Pos)                   /*!< 0x00000002 */
#define RCC_PLL4CFGR1_DIVN_2                      (0x4U << RCC_PLL4CFGR1_DIVN_Pos)                   /*!< 0x00000004 */
#define RCC_PLL4CFGR1_DIVN_3                      (0x8U << RCC_PLL4CFGR1_DIVN_Pos)                   /*!< 0x00000008 */
#define RCC_PLL4CFGR1_DIVN_4                      (0x10U << RCC_PLL4CFGR1_DIVN_Pos)                  /*!< 0x00000010 */
#define RCC_PLL4CFGR1_DIVN_5                      (0x20U << RCC_PLL4CFGR1_DIVN_Pos)                  /*!< 0x00000020 */
#define RCC_PLL4CFGR1_DIVN_6                      (0x40U << RCC_PLL4CFGR1_DIVN_Pos)                  /*!< 0x00000040 */
#define RCC_PLL4CFGR1_DIVN_7                      (0x80U << RCC_PLL4CFGR1_DIVN_Pos)                  /*!< 0x00000080 */
#define RCC_PLL4CFGR1_DIVN_8                      (0x100U << RCC_PLL4CFGR1_DIVN_Pos)                 /*!< 0x00000100 */
#define RCC_PLL4CFGR1_DIVM4_Pos                   (16U)
#define RCC_PLL4CFGR1_DIVM4_Msk                   (0x3FU << RCC_PLL4CFGR1_DIVM4_Pos)                 /*!< 0x003F0000 */
#define RCC_PLL4CFGR1_DIVM4                       RCC_PLL4CFGR1_DIVM4_Msk                            /*!< Prescaler for PLL4 */
#define RCC_PLL4CFGR1_DIVM4_0                     (0x1U << RCC_PLL4CFGR1_DIVM4_Pos)              /*!< 0x00010000 */
#define RCC_PLL4CFGR1_DIVM4_1                     (0x2U << RCC_PLL4CFGR1_DIVM4_Pos)              /*!< 0x00020000 */
#define RCC_PLL4CFGR1_DIVM4_2                     (0x4U << RCC_PLL4CFGR1_DIVM4_Pos)              /*!< 0x00040000 */
#define RCC_PLL4CFGR1_DIVM4_3                     (0x8U << RCC_PLL4CFGR1_DIVM4_Pos)              /*!< 0x00080000 */
#define RCC_PLL4CFGR1_DIVM4_4                     (0x10U << RCC_PLL4CFGR1_DIVM4_Pos)             /*!< 0x00100000 */
#define RCC_PLL4CFGR1_DIVM4_5                     (0x20U << RCC_PLL4CFGR1_DIVM4_Pos)             /*!< 0x00200000 */
#define RCC_PLL4CFGR1_IFRGE_Pos                   (24U)
#define RCC_PLL4CFGR1_IFRGE_Msk                   (0x3U << RCC_PLL4CFGR1_IFRGE_Pos)                  /*!< 0x03000000 */
#define RCC_PLL4CFGR1_IFRGE                       RCC_PLL4CFGR1_IFRGE_Msk                            /*!< PLL4 input frequency range */
#define RCC_PLL4CFGR1_IFRGE_0                     (0x1U << RCC_PLL4CFGR1_IFRGE_Pos)            /*!< 0x01000000 */
#define RCC_PLL4CFGR1_IFRGE_1                     (0x2U << RCC_PLL4CFGR1_IFRGE_Pos)            /*!< 0x02000000 */

/****************  Bit definition for RCC_PLL4CFGR2 register  *****************/
#define RCC_PLL4CFGR2_DIVP_Pos                    (0U)
#define RCC_PLL4CFGR2_DIVP_Msk                    (0x7FU << RCC_PLL4CFGR2_DIVP_Pos)                  /*!< 0x0000007F */
#define RCC_PLL4CFGR2_DIVP                        RCC_PLL4CFGR2_DIVP_Msk                             /*!< PLL4 DIVP division factor */
#define RCC_PLL4CFGR2_DIVP_0                      (0x1U << RCC_PLL4CFGR2_DIVP_Pos)                   /*!< 0x00000001 */
#define RCC_PLL4CFGR2_DIVP_1                      (0x2U << RCC_PLL4CFGR2_DIVP_Pos)                   /*!< 0x00000002 */
#define RCC_PLL4CFGR2_DIVP_2                      (0x4U << RCC_PLL4CFGR2_DIVP_Pos)                   /*!< 0x00000004 */
#define RCC_PLL4CFGR2_DIVP_3                      (0x8U << RCC_PLL4CFGR2_DIVP_Pos)                   /*!< 0x00000008 */
#define RCC_PLL4CFGR2_DIVP_4                      (0x10U << RCC_PLL4CFGR2_DIVP_Pos)                  /*!< 0x00000010 */
#define RCC_PLL4CFGR2_DIVP_5                      (0x20U << RCC_PLL4CFGR2_DIVP_Pos)                  /*!< 0x00000020 */
#define RCC_PLL4CFGR2_DIVP_6                      (0x40U << RCC_PLL4CFGR2_DIVP_Pos)                  /*!< 0x00000040 */
#define RCC_PLL4CFGR2_DIVQ_Pos                    (8U)
#define RCC_PLL4CFGR2_DIVQ_Msk                    (0x7FU << RCC_PLL4CFGR2_DIVQ_Pos)                  /*!< 0x00007F00 */
#define RCC_PLL4CFGR2_DIVQ                        RCC_PLL4CFGR2_DIVQ_Msk                             /*!< PLL4 DIVQ division factor */
#define RCC_PLL4CFGR2_DIVQ_0                      (0x1U << RCC_PLL4CFGR2_DIVQ_Pos)                 /*!< 0x00000100 */
#define RCC_PLL4CFGR2_DIVQ_1                      (0x2U << RCC_PLL4CFGR2_DIVQ_Pos)                 /*!< 0x00000200 */
#define RCC_PLL4CFGR2_DIVQ_2                      (0x4U << RCC_PLL4CFGR2_DIVQ_Pos)                 /*!< 0x00000400 */
#define RCC_PLL4CFGR2_DIVQ_3                      (0x8U << RCC_PLL4CFGR2_DIVQ_Pos)                 /*!< 0x00000800 */
#define RCC_PLL4CFGR2_DIVQ_4                      (0x10U << RCC_PLL4CFGR2_DIVQ_Pos)                /*!< 0x00001000 */
#define RCC_PLL4CFGR2_DIVQ_5                      (0x20U << RCC_PLL4CFGR2_DIVQ_Pos)                /*!< 0x00002000 */
#define RCC_PLL4CFGR2_DIVQ_6                      (0x40U << RCC_PLL4CFGR2_DIVQ_Pos)                /*!< 0x00004000 */
#define RCC_PLL4CFGR2_DIVR_Pos                    (16U)
#define RCC_PLL4CFGR2_DIVR_Msk                    (0x7FU << RCC_PLL4CFGR2_DIVR_Pos)                  /*!< 0x007F0000 */
#define RCC_PLL4CFGR2_DIVR                        RCC_PLL4CFGR2_DIVR_Msk                             /*!< PLL4 DIVR division factor */
#define RCC_PLL4CFGR2_DIVR_0                      (0x1U << RCC_PLL4CFGR2_DIVR_Pos)               /*!< 0x00010000 */
#define RCC_PLL4CFGR2_DIVR_1                      (0x2U << RCC_PLL4CFGR2_DIVR_Pos)               /*!< 0x00020000 */
#define RCC_PLL4CFGR2_DIVR_2                      (0x4U << RCC_PLL4CFGR2_DIVR_Pos)               /*!< 0x00040000 */
#define RCC_PLL4CFGR2_DIVR_3                      (0x8U << RCC_PLL4CFGR2_DIVR_Pos)               /*!< 0x00080000 */
#define RCC_PLL4CFGR2_DIVR_4                      (0x10U << RCC_PLL4CFGR2_DIVR_Pos)              /*!< 0x00100000 */
#define RCC_PLL4CFGR2_DIVR_5                      (0x20U << RCC_PLL4CFGR2_DIVR_Pos)              /*!< 0x00200000 */
#define RCC_PLL4CFGR2_DIVR_6                      (0x40U << RCC_PLL4CFGR2_DIVR_Pos)              /*!< 0x00400000 */

/****************  Bit definition for RCC_PLL4FRACR register  *****************/
#define RCC_PLL4FRACR_FRACV_Pos                   (3U)
#define RCC_PLL4FRACR_FRACV_Msk                   (0x1FFFU << RCC_PLL4FRACR_FRACV_Pos)               /*!< 0x0000FFF8 */
#define RCC_PLL4FRACR_FRACV                       RCC_PLL4FRACR_FRACV_Msk                            /*!< Fractional part of the multiplication factor for PLL4 VCO */
#define RCC_PLL4FRACR_FRACV_0                     (0x1U << RCC_PLL4FRACR_FRACV_Pos)                  /*!< 0x00000008 */
#define RCC_PLL4FRACR_FRACV_1                     (0x2U << RCC_PLL4FRACR_FRACV_Pos)                 /*!< 0x00000010 */
#define RCC_PLL4FRACR_FRACV_2                     (0x4U << RCC_PLL4FRACR_FRACV_Pos)                 /*!< 0x00000020 */
#define RCC_PLL4FRACR_FRACV_3                     (0x8U << RCC_PLL4FRACR_FRACV_Pos)                 /*!< 0x00000040 */
#define RCC_PLL4FRACR_FRACV_4                     (0x10U << RCC_PLL4FRACR_FRACV_Pos)                 /*!< 0x00000080 */
#define RCC_PLL4FRACR_FRACV_5                     (0x20U << RCC_PLL4FRACR_FRACV_Pos)                /*!< 0x00000100 */
#define RCC_PLL4FRACR_FRACV_6                     (0x40U << RCC_PLL4FRACR_FRACV_Pos)                /*!< 0x00000200 */
#define RCC_PLL4FRACR_FRACV_7                     (0x80U << RCC_PLL4FRACR_FRACV_Pos)                /*!< 0x00000400 */
#define RCC_PLL4FRACR_FRACV_8                     (0x100U << RCC_PLL4FRACR_FRACV_Pos)                /*!< 0x00000800 */
#define RCC_PLL4FRACR_FRACV_9                     (0x200U << RCC_PLL4FRACR_FRACV_Pos)               /*!< 0x00001000 */
#define RCC_PLL4FRACR_FRACV_10                    (0x400U << RCC_PLL4FRACR_FRACV_Pos)               /*!< 0x00002000 */
#define RCC_PLL4FRACR_FRACV_11                    (0x800U << RCC_PLL4FRACR_FRACV_Pos)               /*!< 0x00004000 */
#define RCC_PLL4FRACR_FRACV_12                    (0x1000U << RCC_PLL4FRACR_FRACV_Pos)               /*!< 0x00008000 */
#define RCC_PLL4FRACR_FRACLE_Pos                  (16U)
#define RCC_PLL4FRACR_FRACLE_Msk                  (0x1U << RCC_PLL4FRACR_FRACLE_Pos)                 /*!< 0x00010000 */
#define RCC_PLL4FRACR_FRACLE                      RCC_PLL4FRACR_FRACLE_Msk                           /*!< PLL4 fractional latch enable */

/********************  Bit definition for RCC_PLL4CSGR register********************/
#define RCC_PLL4CSGR_MOD_PER_Pos              (0U)
#define RCC_PLL4CSGR_MOD_PER_Msk              (0x1FFFU << RCC_PLL4CSGR_MOD_PER_Pos) /*!< 0x00001FFF */
#define RCC_PLL4CSGR_MOD_PER                  RCC_PLL4CSGR_MOD_PER_Msk         /*Modulation Period Adjustment for PLL4*/
#define RCC_PLL4CSGR_TPDFN_DIS_Pos            (13U)
#define RCC_PLL4CSGR_TPDFN_DIS_Msk            (0x1U << RCC_PLL4CSGR_TPDFN_DIS_Pos) /*!< 0x00002000 */
#define RCC_PLL4CSGR_TPDFN_DIS                RCC_PLL4CSGR_TPDFN_DIS_Msk       /*Dithering TPDF noise control*/
#define RCC_PLL4CSGR_RPDFN_DIS_Pos            (14U)
#define RCC_PLL4CSGR_RPDFN_DIS_Msk            (0x1U << RCC_PLL4CSGR_RPDFN_DIS_Pos) /*!< 0x00004000 */
#define RCC_PLL4CSGR_RPDFN_DIS                RCC_PLL4CSGR_RPDFN_DIS_Msk       /*Dithering RPDF noise control*/
#define RCC_PLL4CSGR_SSCG_MODE_Pos            (15U)
#define RCC_PLL4CSGR_SSCG_MODE_Msk            (0x1U << RCC_PLL4CSGR_SSCG_MODE_Pos) /*!< 0x00008000 */
#define RCC_PLL4CSGR_SSCG_MODE                RCC_PLL4CSGR_SSCG_MODE_Msk       /*Spread spectrum clock generator mode*/
#define RCC_PLL4CSGR_INC_STEP_Pos             (16U)
#define RCC_PLL4CSGR_INC_STEP_Msk             (0x7FFFU << RCC_PLL4CSGR_INC_STEP_Pos) /*!< 0x7FFF0000 */
#define RCC_PLL4CSGR_INC_STEP                 RCC_PLL4CSGR_INC_STEP_Msk        /*Modulation Depth Adjustment for PLL4*/

/***************  Bit definition for RCC_I2C12CKSELR register  ****************/
#define RCC_I2C12CKSELR_I2C12SRC_Pos              (0U)
#define RCC_I2C12CKSELR_I2C12SRC_Msk              (0x7U << RCC_I2C12CKSELR_I2C12SRC_Pos)             /*!< 0x00000007 */
#define RCC_I2C12CKSELR_I2C12SRC                  RCC_I2C12CKSELR_I2C12SRC_Msk                       /*!< I2C1 and I2C2 kernel clock source selection */
#define RCC_I2C12CKSELR_I2C12SRC_0                (0x1U << RCC_I2C12CKSELR_I2C12SRC_Pos)             /*!< 0x00000001 */
#define RCC_I2C12CKSELR_I2C12SRC_1                (0x2U << RCC_I2C12CKSELR_I2C12SRC_Pos)             /*!< 0x00000002 */
#define RCC_I2C12CKSELR_I2C12SRC_2                (0x4U << RCC_I2C12CKSELR_I2C12SRC_Pos)             /*!< 0x00000004 */

/***************  Bit definition for RCC_I2C35CKSELR register  ****************/
#define RCC_I2C35CKSELR_I2C35SRC_Pos              (0U)
#define RCC_I2C35CKSELR_I2C35SRC_Msk              (0x7U << RCC_I2C35CKSELR_I2C35SRC_Pos)             /*!< 0x00000007 */
#define RCC_I2C35CKSELR_I2C35SRC                  RCC_I2C35CKSELR_I2C35SRC_Msk                       /*!< I2C3 and I2C5 kernel clock source selection */
#define RCC_I2C35CKSELR_I2C35SRC_0                (0x1U << RCC_I2C35CKSELR_I2C35SRC_Pos)             /*!< 0x00000001 */
#define RCC_I2C35CKSELR_I2C35SRC_1                (0x2U << RCC_I2C35CKSELR_I2C35SRC_Pos)             /*!< 0x00000002 */
#define RCC_I2C35CKSELR_I2C35SRC_2                (0x4U << RCC_I2C35CKSELR_I2C35SRC_Pos)             /*!< 0x00000004 */

/****************  Bit definition for RCC_SAI1CKSELR register  ****************/
#define RCC_SAI1CKSELR_SAI1SRC_Pos                (0U)
#define RCC_SAI1CKSELR_SAI1SRC_Msk                (0x7U << RCC_SAI1CKSELR_SAI1SRC_Pos)               /*!< 0x00000007 */
#define RCC_SAI1CKSELR_SAI1SRC                    RCC_SAI1CKSELR_SAI1SRC_Msk                         /*!< SAI1 and DFSDM kernel clock source selection */
#define RCC_SAI1CKSELR_SAI1SRC_0                  (0x1U << RCC_SAI1CKSELR_SAI1SRC_Pos)               /*!< 0x00000001 */
#define RCC_SAI1CKSELR_SAI1SRC_1                  (0x2U << RCC_SAI1CKSELR_SAI1SRC_Pos)               /*!< 0x00000002 */
#define RCC_SAI1CKSELR_SAI1SRC_2                  (0x4U << RCC_SAI1CKSELR_SAI1SRC_Pos)               /*!< 0x00000004 */

/****************  Bit definition for RCC_SAI2CKSELR register  ****************/
#define RCC_SAI2CKSELR_SAI2SRC_Pos                (0U)
#define RCC_SAI2CKSELR_SAI2SRC_Msk                (0x7U << RCC_SAI2CKSELR_SAI2SRC_Pos)               /*!< 0x00000007 */
#define RCC_SAI2CKSELR_SAI2SRC                    RCC_SAI2CKSELR_SAI2SRC_Msk                         /*!< SAI2 kernel clock source selection */
#define RCC_SAI2CKSELR_SAI2SRC_0                  (0x1U << RCC_SAI2CKSELR_SAI2SRC_Pos)               /*!< 0x00000001 */
#define RCC_SAI2CKSELR_SAI2SRC_1                  (0x2U << RCC_SAI2CKSELR_SAI2SRC_Pos)               /*!< 0x00000002 */
#define RCC_SAI2CKSELR_SAI2SRC_2                  (0x4U << RCC_SAI2CKSELR_SAI2SRC_Pos)               /*!< 0x00000004 */

/****************  Bit definition for RCC_SAI3CKSELR register  ****************/
#define RCC_SAI3CKSELR_SAI3SRC_Pos                (0U)
#define RCC_SAI3CKSELR_SAI3SRC_Msk                (0x7U << RCC_SAI3CKSELR_SAI3SRC_Pos)               /*!< 0x00000007 */
#define RCC_SAI3CKSELR_SAI3SRC                    RCC_SAI3CKSELR_SAI3SRC_Msk                         /*!< SAI3 kernel clock source selection */
#define RCC_SAI3CKSELR_SAI3SRC_0                  (0x1U << RCC_SAI3CKSELR_SAI3SRC_Pos)               /*!< 0x00000001 */
#define RCC_SAI3CKSELR_SAI3SRC_1                  (0x2U << RCC_SAI3CKSELR_SAI3SRC_Pos)               /*!< 0x00000002 */
#define RCC_SAI3CKSELR_SAI3SRC_2                  (0x4U << RCC_SAI3CKSELR_SAI3SRC_Pos)               /*!< 0x00000004 */

/****************  Bit definition for RCC_SAI4CKSELR register  ****************/
#define RCC_SAI4CKSELR_SAI4SRC_Pos                (0U)
#define RCC_SAI4CKSELR_SAI4SRC_Msk                (0x7U << RCC_SAI4CKSELR_SAI4SRC_Pos)               /*!< 0x00000007 */
#define RCC_SAI4CKSELR_SAI4SRC                    RCC_SAI4CKSELR_SAI4SRC_Msk                         /*!< SAI4 kernel clock source selection */
#define RCC_SAI4CKSELR_SAI4SRC_0                  (0x1U << RCC_SAI4CKSELR_SAI4SRC_Pos)               /*!< 0x00000001 */
#define RCC_SAI4CKSELR_SAI4SRC_1                  (0x2U << RCC_SAI4CKSELR_SAI4SRC_Pos)               /*!< 0x00000002 */
#define RCC_SAI4CKSELR_SAI4SRC_2                  (0x4U << RCC_SAI4CKSELR_SAI4SRC_Pos)               /*!< 0x00000004 */

/***************  Bit definition for RCC_SPI2S1CKSELR register  ***************/
#define RCC_SPI2S1CKSELR_SPI1SRC_Pos              (0U)
#define RCC_SPI2S1CKSELR_SPI1SRC_Msk              (0x7U << RCC_SPI2S1CKSELR_SPI1SRC_Pos)             /*!< 0x00000007 */
#define RCC_SPI2S1CKSELR_SPI1SRC                  RCC_SPI2S1CKSELR_SPI1SRC_Msk                       /*!< SPI/I2S1 kernel clock source selection */
#define RCC_SPI2S1CKSELR_SPI1SRC_0                (0x1U << RCC_SPI2S1CKSELR_SPI1SRC_Pos)             /*!< 0x00000001 */
#define RCC_SPI2S1CKSELR_SPI1SRC_1                (0x2U << RCC_SPI2S1CKSELR_SPI1SRC_Pos)             /*!< 0x00000002 */
#define RCC_SPI2S1CKSELR_SPI1SRC_2                (0x4U << RCC_SPI2S1CKSELR_SPI1SRC_Pos)             /*!< 0x00000004 */

/**************  Bit definition for RCC_SPI2S23CKSELR register  ***************/
#define RCC_SPI2S23CKSELR_SPI23SRC_Pos            (0U)
#define RCC_SPI2S23CKSELR_SPI23SRC_Msk            (0x7U << RCC_SPI2S23CKSELR_SPI23SRC_Pos)           /*!< 0x00000007 */
#define RCC_SPI2S23CKSELR_SPI23SRC                RCC_SPI2S23CKSELR_SPI23SRC_Msk                     /*!< SPI/I2S2,3 kernel clock source selection */
#define RCC_SPI2S23CKSELR_SPI23SRC_0              (0x1U << RCC_SPI2S23CKSELR_SPI23SRC_Pos)           /*!< 0x00000001 */
#define RCC_SPI2S23CKSELR_SPI23SRC_1              (0x2U << RCC_SPI2S23CKSELR_SPI23SRC_Pos)           /*!< 0x00000002 */
#define RCC_SPI2S23CKSELR_SPI23SRC_2              (0x4U << RCC_SPI2S23CKSELR_SPI23SRC_Pos)           /*!< 0x00000004 */

/***************  Bit definition for RCC_SPI45CKSELR register  ****************/
#define RCC_SPI45CKSELR_SPI45SRC_Pos              (0U)
#define RCC_SPI45CKSELR_SPI45SRC_Msk              (0x7U << RCC_SPI45CKSELR_SPI45SRC_Pos)             /*!< 0x00000007 */
#define RCC_SPI45CKSELR_SPI45SRC                  RCC_SPI45CKSELR_SPI45SRC_Msk                       /*!< SPI4,5 kernel clock source selection */
#define RCC_SPI45CKSELR_SPI45SRC_0                (0x1U << RCC_SPI45CKSELR_SPI45SRC_Pos)             /*!< 0x00000001 */
#define RCC_SPI45CKSELR_SPI45SRC_1                (0x2U << RCC_SPI45CKSELR_SPI45SRC_Pos)             /*!< 0x00000002 */
#define RCC_SPI45CKSELR_SPI45SRC_2                (0x4U << RCC_SPI45CKSELR_SPI45SRC_Pos)             /*!< 0x00000004 */

/***************  Bit definition for RCC_UART6CKSELR register  ****************/
#define RCC_UART6CKSELR_UART6SRC_Pos              (0U)
#define RCC_UART6CKSELR_UART6SRC_Msk              (0x7U << RCC_UART6CKSELR_UART6SRC_Pos)             /*!< 0x00000007 */
#define RCC_UART6CKSELR_UART6SRC                  RCC_UART6CKSELR_UART6SRC_Msk                       /*!< USART6 kernel clock source selection */
#define RCC_UART6CKSELR_UART6SRC_0                (0x1U << RCC_UART6CKSELR_UART6SRC_Pos)             /*!< 0x00000001 */
#define RCC_UART6CKSELR_UART6SRC_1                (0x2U << RCC_UART6CKSELR_UART6SRC_Pos)             /*!< 0x00000002 */
#define RCC_UART6CKSELR_UART6SRC_2                (0x4U << RCC_UART6CKSELR_UART6SRC_Pos)             /*!< 0x00000004 */

/***************  Bit definition for RCC_UART24CKSELR register  ***************/
#define RCC_UART24CKSELR_UART24SRC_Pos            (0U)
#define RCC_UART24CKSELR_UART24SRC_Msk            (0x7U << RCC_UART24CKSELR_UART24SRC_Pos)           /*!< 0x00000007 */
#define RCC_UART24CKSELR_UART24SRC                RCC_UART24CKSELR_UART24SRC_Msk                     /*!< USART2 and UART4 kernel clock source selection */
#define RCC_UART24CKSELR_UART24SRC_0              (0x1U << RCC_UART24CKSELR_UART24SRC_Pos)           /*!< 0x00000001 */
#define RCC_UART24CKSELR_UART24SRC_1              (0x2U << RCC_UART24CKSELR_UART24SRC_Pos)           /*!< 0x00000002 */
#define RCC_UART24CKSELR_UART24SRC_2              (0x4U << RCC_UART24CKSELR_UART24SRC_Pos)           /*!< 0x00000004 */

/***************  Bit definition for RCC_UART35CKSELR register  ***************/
#define RCC_UART35CKSELR_UART35SRC_Pos            (0U)
#define RCC_UART35CKSELR_UART35SRC_Msk            (0x7U << RCC_UART35CKSELR_UART35SRC_Pos)           /*!< 0x00000007 */
#define RCC_UART35CKSELR_UART35SRC                RCC_UART35CKSELR_UART35SRC_Msk                     /*!< USART3 and UART5 kernel clock source selection */
#define RCC_UART35CKSELR_UART35SRC_0              (0x1U << RCC_UART35CKSELR_UART35SRC_Pos)           /*!< 0x00000001 */
#define RCC_UART35CKSELR_UART35SRC_1              (0x2U << RCC_UART35CKSELR_UART35SRC_Pos)           /*!< 0x00000002 */
#define RCC_UART35CKSELR_UART35SRC_2              (0x4U << RCC_UART35CKSELR_UART35SRC_Pos)           /*!< 0x00000004 */

/***************  Bit definition for RCC_UART78CKSELR register  ***************/
#define RCC_UART78CKSELR_UART78SRC_Pos            (0U)
#define RCC_UART78CKSELR_UART78SRC_Msk            (0x7U << RCC_UART78CKSELR_UART78SRC_Pos)           /*!< 0x00000007 */
#define RCC_UART78CKSELR_UART78SRC                RCC_UART78CKSELR_UART78SRC_Msk                     /*!< UART7 and UART8 kernel clock source selection */
#define RCC_UART78CKSELR_UART78SRC_0              (0x1U << RCC_UART78CKSELR_UART78SRC_Pos)           /*!< 0x00000001 */
#define RCC_UART78CKSELR_UART78SRC_1              (0x2U << RCC_UART78CKSELR_UART78SRC_Pos)           /*!< 0x00000002 */
#define RCC_UART78CKSELR_UART78SRC_2              (0x4U << RCC_UART78CKSELR_UART78SRC_Pos)           /*!< 0x00000004 */

/**************  Bit definition for RCC_SDMMC12CKSELR register  ***************/
#define RCC_SDMMC12CKSELR_SDMMC12SRC_Pos          (0U)
#define RCC_SDMMC12CKSELR_SDMMC12SRC_Msk          (0x7U << RCC_SDMMC12CKSELR_SDMMC12SRC_Pos)         /*!< 0x00000007 */
#define RCC_SDMMC12CKSELR_SDMMC12SRC              RCC_SDMMC12CKSELR_SDMMC12SRC_Msk                   /*!< SDMMC1 and SDMMC2 kernel clock source selection */
#define RCC_SDMMC12CKSELR_SDMMC12SRC_0            (0x1U << RCC_SDMMC12CKSELR_SDMMC12SRC_Pos)         /*!< 0x00000001 */
#define RCC_SDMMC12CKSELR_SDMMC12SRC_1            (0x2U << RCC_SDMMC12CKSELR_SDMMC12SRC_Pos)         /*!< 0x00000002 */
#define RCC_SDMMC12CKSELR_SDMMC12SRC_2            (0x4U << RCC_SDMMC12CKSELR_SDMMC12SRC_Pos)         /*!< 0x00000004 */

/***************  Bit definition for RCC_SDMMC3CKSELR register  ***************/
#define RCC_SDMMC3CKSELR_SDMMC3SRC_Pos            (0U)
#define RCC_SDMMC3CKSELR_SDMMC3SRC_Msk            (0x7U << RCC_SDMMC3CKSELR_SDMMC3SRC_Pos)           /*!< 0x00000007 */
#define RCC_SDMMC3CKSELR_SDMMC3SRC                RCC_SDMMC3CKSELR_SDMMC3SRC_Msk                     /*!< SDMMC3 kernel clock source selection */
#define RCC_SDMMC3CKSELR_SDMMC3SRC_0              (0x1U << RCC_SDMMC3CKSELR_SDMMC3SRC_Pos)           /*!< 0x00000001 */
#define RCC_SDMMC3CKSELR_SDMMC3SRC_1              (0x2U << RCC_SDMMC3CKSELR_SDMMC3SRC_Pos)           /*!< 0x00000002 */
#define RCC_SDMMC3CKSELR_SDMMC3SRC_2              (0x4U << RCC_SDMMC3CKSELR_SDMMC3SRC_Pos)           /*!< 0x00000004 */

/****************  Bit definition for RCC_ETHCKSELR register  *****************/
#define RCC_ETHCKSELR_ETHSRC_Pos                  (0U)
#define RCC_ETHCKSELR_ETHSRC_Msk                  (0x3U << RCC_ETHCKSELR_ETHSRC_Pos)                 /*!< 0x00000003 */
#define RCC_ETHCKSELR_ETHSRC                      RCC_ETHCKSELR_ETHSRC_Msk                           /*!< ETH kernel clock source selection */
#define RCC_ETHCKSELR_ETHSRC_0                    (0x1U << RCC_ETHCKSELR_ETHSRC_Pos)                 /*!< 0x00000001 */
#define RCC_ETHCKSELR_ETHSRC_1                    (0x2U << RCC_ETHCKSELR_ETHSRC_Pos)                 /*!< 0x00000002 */
#define RCC_ETHCKSELR_ETHPTPDIV_Pos               (4U)
#define RCC_ETHCKSELR_ETHPTPDIV_Msk               (0xFU << RCC_ETHCKSELR_ETHPTPDIV_Pos)              /*!< 0x000000F0 */
#define RCC_ETHCKSELR_ETHPTPDIV                   RCC_ETHCKSELR_ETHPTPDIV_Msk                        /*!< Clock divider for Ethernet Precision Time Protocol (PTP) */
#define RCC_ETHCKSELR_ETHPTPDIV_0                 (0x1U << RCC_ETHCKSELR_ETHPTPDIV_Pos)             /*!< 0x00000010 */
#define RCC_ETHCKSELR_ETHPTPDIV_1                 (0x2U << RCC_ETHCKSELR_ETHPTPDIV_Pos)             /*!< 0x00000020 */
#define RCC_ETHCKSELR_ETHPTPDIV_2                 (0x4U << RCC_ETHCKSELR_ETHPTPDIV_Pos)             /*!< 0x00000040 */
#define RCC_ETHCKSELR_ETHPTPDIV_3                 (0x8U << RCC_ETHCKSELR_ETHPTPDIV_Pos)             /*!< 0x00000080 */

/****************  Bit definition for RCC_QSPICKSELR register  ****************/
#define RCC_QSPICKSELR_QSPISRC_Pos                (0U)
#define RCC_QSPICKSELR_QSPISRC_Msk                (0x3U << RCC_QSPICKSELR_QSPISRC_Pos)               /*!< 0x00000003 */
#define RCC_QSPICKSELR_QSPISRC                    RCC_QSPICKSELR_QSPISRC_Msk                         /*!< QUADSPI kernel clock source selection */
#define RCC_QSPICKSELR_QSPISRC_0                  (0x1U << RCC_QSPICKSELR_QSPISRC_Pos)               /*!< 0x00000001 */
#define RCC_QSPICKSELR_QSPISRC_1                  (0x2U << RCC_QSPICKSELR_QSPISRC_Pos)               /*!< 0x00000002 */

/****************  Bit definition for RCC_FMCCKSELR register  *****************/
#define RCC_FMCCKSELR_FMCSRC_Pos                  (0U)
#define RCC_FMCCKSELR_FMCSRC_Msk                  (0x3U << RCC_FMCCKSELR_FMCSRC_Pos)                 /*!< 0x00000003 */
#define RCC_FMCCKSELR_FMCSRC                      RCC_FMCCKSELR_FMCSRC_Msk                           /*!< FMC kernel clock source selection */
#define RCC_FMCCKSELR_FMCSRC_0                    (0x1U << RCC_FMCCKSELR_FMCSRC_Pos)                 /*!< 0x00000001 */
#define RCC_FMCCKSELR_FMCSRC_1                    (0x2U << RCC_FMCCKSELR_FMCSRC_Pos)                 /*!< 0x00000002 */

/***************  Bit definition for RCC_FDCANCKSELR register  ****************/
#define RCC_FDCANCKSELR_FDCANSRC_Pos              (0U)
#define RCC_FDCANCKSELR_FDCANSRC_Msk              (0x3U << RCC_FDCANCKSELR_FDCANSRC_Pos)             /*!< 0x00000003 */
#define RCC_FDCANCKSELR_FDCANSRC                  RCC_FDCANCKSELR_FDCANSRC_Msk                       /*!< FDCAN kernel clock source selection */
#define RCC_FDCANCKSELR_FDCANSRC_0                (0x1U << RCC_FDCANCKSELR_FDCANSRC_Pos)             /*!< 0x00000001 */
#define RCC_FDCANCKSELR_FDCANSRC_1                (0x2U << RCC_FDCANCKSELR_FDCANSRC_Pos)             /*!< 0x00000002 */

/***************  Bit definition for RCC_SPDIFCKSELR register  ****************/
#define RCC_SPDIFCKSELR_SPDIFSRC_Pos              (0U)
#define RCC_SPDIFCKSELR_SPDIFSRC_Msk              (0x3U << RCC_SPDIFCKSELR_SPDIFSRC_Pos)             /*!< 0x00000003 */
#define RCC_SPDIFCKSELR_SPDIFSRC                  RCC_SPDIFCKSELR_SPDIFSRC_Msk                       /*!< SPDIFRX kernel clock source selection */
#define RCC_SPDIFCKSELR_SPDIFSRC_0                (0x1U << RCC_SPDIFCKSELR_SPDIFSRC_Pos)             /*!< 0x00000001 */
#define RCC_SPDIFCKSELR_SPDIFSRC_1                (0x2U << RCC_SPDIFCKSELR_SPDIFSRC_Pos)             /*!< 0x00000002 */

/****************  Bit definition for RCC_CECCKSELR register  *****************/
#define RCC_CECCKSELR_CECSRC_Pos                  (0U)
#define RCC_CECCKSELR_CECSRC_Msk                  (0x3U << RCC_CECCKSELR_CECSRC_Pos)                 /*!< 0x00000003 */
#define RCC_CECCKSELR_CECSRC                      RCC_CECCKSELR_CECSRC_Msk                           /*!< CEC-HDMI kernel clock source selection */
#define RCC_CECCKSELR_CECSRC_0                    (0x1U << RCC_CECCKSELR_CECSRC_Pos)                 /*!< 0x00000001 */
#define RCC_CECCKSELR_CECSRC_1                    (0x2U << RCC_CECCKSELR_CECSRC_Pos)                 /*!< 0x00000002 */

/****************  Bit definition for RCC_USBCKSELR register  *****************/
#define RCC_USBCKSELR_USBPHYSRC_Pos               (0U)
#define RCC_USBCKSELR_USBPHYSRC_Msk               (0x3U << RCC_USBCKSELR_USBPHYSRC_Pos)              /*!< 0x00000003 */
#define RCC_USBCKSELR_USBPHYSRC                   RCC_USBCKSELR_USBPHYSRC_Msk                        /*!< USB PHY kernel clock source selection */
#define RCC_USBCKSELR_USBPHYSRC_0                 (0x1U << RCC_USBCKSELR_USBPHYSRC_Pos)              /*!< 0x00000001 */
#define RCC_USBCKSELR_USBPHYSRC_1                 (0x2U << RCC_USBCKSELR_USBPHYSRC_Pos)              /*!< 0x00000002 */
#define RCC_USBCKSELR_USBOSRC_Pos                 (4U)
#define RCC_USBCKSELR_USBOSRC_Msk                 (0x1U << RCC_USBCKSELR_USBOSRC_Pos)                /*!< 0x00000010 */
#define RCC_USBCKSELR_USBOSRC                     RCC_USBCKSELR_USBOSRC_Msk                          /*!< USB OTG kernel clock source selection */

/****************  Bit definition for RCC_RNG2CKSELR register  ****************/
#define RCC_RNG2CKSELR_RNG2SRC_Pos                (0U)
#define RCC_RNG2CKSELR_RNG2SRC_Msk                (0x3U << RCC_RNG2CKSELR_RNG2SRC_Pos)               /*!< 0x00000003 */
#define RCC_RNG2CKSELR_RNG2SRC                    RCC_RNG2CKSELR_RNG2SRC_Msk                         /*!< RNG2 kernel clock source selection */
#define RCC_RNG2CKSELR_RNG2SRC_0                  (0x1U << RCC_RNG2CKSELR_RNG2SRC_Pos)               /*!< 0x00000001 */
#define RCC_RNG2CKSELR_RNG2SRC_1                  (0x2U << RCC_RNG2CKSELR_RNG2SRC_Pos)               /*!< 0x00000002 */

/****************  Bit definition for RCC_DSICKSELR register  *****************/
#define RCC_DSICKSELR_DSISRC_Pos                  (0U)
#define RCC_DSICKSELR_DSISRC_Msk                  (0x1U << RCC_DSICKSELR_DSISRC_Pos)                 /*!< 0x00000001 */
#define RCC_DSICKSELR_DSISRC                      RCC_DSICKSELR_DSISRC_Msk                           /*!< DSI kernel clock source selection */

/****************  Bit definition for RCC_ADCCKSELR register  *****************/
#define RCC_ADCCKSELR_ADCSRC_Pos                  (0U)
#define RCC_ADCCKSELR_ADCSRC_Msk                  (0x3U << RCC_ADCCKSELR_ADCSRC_Pos)                 /*!< 0x00000003 */
#define RCC_ADCCKSELR_ADCSRC                      RCC_ADCCKSELR_ADCSRC_Msk                           /*!< ADC1&amp;2 kernel clock source selection */
#define RCC_ADCCKSELR_ADCSRC_0                    (0x1U << RCC_ADCCKSELR_ADCSRC_Pos)                 /*!< 0x00000001 */
#define RCC_ADCCKSELR_ADCSRC_1                    (0x2U << RCC_ADCCKSELR_ADCSRC_Pos)                 /*!< 0x00000002 */

/**************  Bit definition for RCC_LPTIM45CKSELR register  ***************/
#define RCC_LPTIM45CKSELR_LPTIM45SRC_Pos          (0U)
#define RCC_LPTIM45CKSELR_LPTIM45SRC_Msk          (0x7U << RCC_LPTIM45CKSELR_LPTIM45SRC_Pos)         /*!< 0x00000007 */
#define RCC_LPTIM45CKSELR_LPTIM45SRC              RCC_LPTIM45CKSELR_LPTIM45SRC_Msk                   /*!< LPTIM4 and LPTIM5 kernel clock source selection */
#define RCC_LPTIM45CKSELR_LPTIM45SRC_0            (0x1U << RCC_LPTIM45CKSELR_LPTIM45SRC_Pos)         /*!< 0x00000001 */
#define RCC_LPTIM45CKSELR_LPTIM45SRC_1            (0x2U << RCC_LPTIM45CKSELR_LPTIM45SRC_Pos)         /*!< 0x00000002 */
#define RCC_LPTIM45CKSELR_LPTIM45SRC_2            (0x4U << RCC_LPTIM45CKSELR_LPTIM45SRC_Pos)         /*!< 0x00000004 */

/**************  Bit definition for RCC_LPTIM23CKSELR register  ***************/
#define RCC_LPTIM23CKSELR_LPTIM23SRC_Pos          (0U)
#define RCC_LPTIM23CKSELR_LPTIM23SRC_Msk          (0x7U << RCC_LPTIM23CKSELR_LPTIM23SRC_Pos)         /*!< 0x00000007 */
#define RCC_LPTIM23CKSELR_LPTIM23SRC              RCC_LPTIM23CKSELR_LPTIM23SRC_Msk                   /*!< LPTIM2 and LPTIM3 kernel clock source selection */
#define RCC_LPTIM23CKSELR_LPTIM23SRC_0            (0x1U << RCC_LPTIM23CKSELR_LPTIM23SRC_Pos)         /*!< 0x00000001 */
#define RCC_LPTIM23CKSELR_LPTIM23SRC_1            (0x2U << RCC_LPTIM23CKSELR_LPTIM23SRC_Pos)         /*!< 0x00000002 */
#define RCC_LPTIM23CKSELR_LPTIM23SRC_2            (0x4U << RCC_LPTIM23CKSELR_LPTIM23SRC_Pos)         /*!< 0x00000004 */

/***************  Bit definition for RCC_LPTIM1CKSELR register  ***************/
#define RCC_LPTIM1CKSELR_LPTIM1SRC_Pos            (0U)
#define RCC_LPTIM1CKSELR_LPTIM1SRC_Msk            (0x7U << RCC_LPTIM1CKSELR_LPTIM1SRC_Pos)           /*!< 0x00000007 */
#define RCC_LPTIM1CKSELR_LPTIM1SRC                RCC_LPTIM1CKSELR_LPTIM1SRC_Msk                     /*!< LPTIM1 kernel clock source selection */
#define RCC_LPTIM1CKSELR_LPTIM1SRC_0              (0x1U << RCC_LPTIM1CKSELR_LPTIM1SRC_Pos)           /*!< 0x00000001 */
#define RCC_LPTIM1CKSELR_LPTIM1SRC_1              (0x2U << RCC_LPTIM1CKSELR_LPTIM1SRC_Pos)           /*!< 0x00000002 */
#define RCC_LPTIM1CKSELR_LPTIM1SRC_2              (0x4U << RCC_LPTIM1CKSELR_LPTIM1SRC_Pos)           /*!< 0x00000004 */

/***************  Bit definition for RCC_APB1RSTSETR register  ****************/
#define RCC_APB1RSTSETR_TIM2RST_Pos               (0U)
#define RCC_APB1RSTSETR_TIM2RST_Msk               (0x1U << RCC_APB1RSTSETR_TIM2RST_Pos)              /*!< 0x00000001 */
#define RCC_APB1RSTSETR_TIM2RST                   RCC_APB1RSTSETR_TIM2RST_Msk                        /*!< TIM2 block reset */
#define RCC_APB1RSTSETR_TIM3RST_Pos               (1U)
#define RCC_APB1RSTSETR_TIM3RST_Msk               (0x1U << RCC_APB1RSTSETR_TIM3RST_Pos)              /*!< 0x00000002 */
#define RCC_APB1RSTSETR_TIM3RST                   RCC_APB1RSTSETR_TIM3RST_Msk                        /*!< TIM3 block reset */
#define RCC_APB1RSTSETR_TIM4RST_Pos               (2U)
#define RCC_APB1RSTSETR_TIM4RST_Msk               (0x1U << RCC_APB1RSTSETR_TIM4RST_Pos)              /*!< 0x00000004 */
#define RCC_APB1RSTSETR_TIM4RST                   RCC_APB1RSTSETR_TIM4RST_Msk                        /*!< TIM4 block reset */
#define RCC_APB1RSTSETR_TIM5RST_Pos               (3U)
#define RCC_APB1RSTSETR_TIM5RST_Msk               (0x1U << RCC_APB1RSTSETR_TIM5RST_Pos)              /*!< 0x00000008 */
#define RCC_APB1RSTSETR_TIM5RST                   RCC_APB1RSTSETR_TIM5RST_Msk                        /*!< TIM5 block reset */
#define RCC_APB1RSTSETR_TIM6RST_Pos               (4U)
#define RCC_APB1RSTSETR_TIM6RST_Msk               (0x1U << RCC_APB1RSTSETR_TIM6RST_Pos)              /*!< 0x00000010 */
#define RCC_APB1RSTSETR_TIM6RST                   RCC_APB1RSTSETR_TIM6RST_Msk                        /*!< TIM6 block reset */
#define RCC_APB1RSTSETR_TIM7RST_Pos               (5U)
#define RCC_APB1RSTSETR_TIM7RST_Msk               (0x1U << RCC_APB1RSTSETR_TIM7RST_Pos)              /*!< 0x00000020 */
#define RCC_APB1RSTSETR_TIM7RST                   RCC_APB1RSTSETR_TIM7RST_Msk                        /*!< TIM7 block reset */
#define RCC_APB1RSTSETR_TIM12RST_Pos              (6U)
#define RCC_APB1RSTSETR_TIM12RST_Msk              (0x1U << RCC_APB1RSTSETR_TIM12RST_Pos)             /*!< 0x00000040 */
#define RCC_APB1RSTSETR_TIM12RST                  RCC_APB1RSTSETR_TIM12RST_Msk                       /*!< TIM12 block reset */
#define RCC_APB1RSTSETR_TIM13RST_Pos              (7U)
#define RCC_APB1RSTSETR_TIM13RST_Msk              (0x1U << RCC_APB1RSTSETR_TIM13RST_Pos)             /*!< 0x00000080 */
#define RCC_APB1RSTSETR_TIM13RST                  RCC_APB1RSTSETR_TIM13RST_Msk                       /*!< TIM13 block reset */
#define RCC_APB1RSTSETR_TIM14RST_Pos              (8U)
#define RCC_APB1RSTSETR_TIM14RST_Msk              (0x1U << RCC_APB1RSTSETR_TIM14RST_Pos)             /*!< 0x00000100 */
#define RCC_APB1RSTSETR_TIM14RST                  RCC_APB1RSTSETR_TIM14RST_Msk                       /*!< TIM14 block reset */
#define RCC_APB1RSTSETR_LPTIM1RST_Pos             (9U)
#define RCC_APB1RSTSETR_LPTIM1RST_Msk             (0x1U << RCC_APB1RSTSETR_LPTIM1RST_Pos)            /*!< 0x00000200 */
#define RCC_APB1RSTSETR_LPTIM1RST                 RCC_APB1RSTSETR_LPTIM1RST_Msk                      /*!< LPTIM1 block reset */
#define RCC_APB1RSTSETR_SPI2RST_Pos               (11U)
#define RCC_APB1RSTSETR_SPI2RST_Msk               (0x1U << RCC_APB1RSTSETR_SPI2RST_Pos)              /*!< 0x00000800 */
#define RCC_APB1RSTSETR_SPI2RST                   RCC_APB1RSTSETR_SPI2RST_Msk                        /*!< SPI2 block reset */
#define RCC_APB1RSTSETR_SPI3RST_Pos               (12U)
#define RCC_APB1RSTSETR_SPI3RST_Msk               (0x1U << RCC_APB1RSTSETR_SPI3RST_Pos)              /*!< 0x00001000 */
#define RCC_APB1RSTSETR_SPI3RST                   RCC_APB1RSTSETR_SPI3RST_Msk                        /*!< SPI3 block reset */
#define RCC_APB1RSTSETR_USART2RST_Pos             (14U)
#define RCC_APB1RSTSETR_USART2RST_Msk             (0x1U << RCC_APB1RSTSETR_USART2RST_Pos)            /*!< 0x00004000 */
#define RCC_APB1RSTSETR_USART2RST                 RCC_APB1RSTSETR_USART2RST_Msk                      /*!< USART2 block reset */
#define RCC_APB1RSTSETR_USART3RST_Pos             (15U)
#define RCC_APB1RSTSETR_USART3RST_Msk             (0x1U << RCC_APB1RSTSETR_USART3RST_Pos)            /*!< 0x00008000 */
#define RCC_APB1RSTSETR_USART3RST                 RCC_APB1RSTSETR_USART3RST_Msk                      /*!< USART3 block reset */
#define RCC_APB1RSTSETR_UART4RST_Pos              (16U)
#define RCC_APB1RSTSETR_UART4RST_Msk              (0x1U << RCC_APB1RSTSETR_UART4RST_Pos)             /*!< 0x00010000 */
#define RCC_APB1RSTSETR_UART4RST                  RCC_APB1RSTSETR_UART4RST_Msk                       /*!< UART4 block reset */
#define RCC_APB1RSTSETR_UART5RST_Pos              (17U)
#define RCC_APB1RSTSETR_UART5RST_Msk              (0x1U << RCC_APB1RSTSETR_UART5RST_Pos)             /*!< 0x00020000 */
#define RCC_APB1RSTSETR_UART5RST                  RCC_APB1RSTSETR_UART5RST_Msk                       /*!< UART5 block reset */
#define RCC_APB1RSTSETR_UART7RST_Pos              (18U)
#define RCC_APB1RSTSETR_UART7RST_Msk              (0x1U << RCC_APB1RSTSETR_UART7RST_Pos)             /*!< 0x00040000 */
#define RCC_APB1RSTSETR_UART7RST                  RCC_APB1RSTSETR_UART7RST_Msk                       /*!< UART7 block reset */
#define RCC_APB1RSTSETR_UART8RST_Pos              (19U)
#define RCC_APB1RSTSETR_UART8RST_Msk              (0x1U << RCC_APB1RSTSETR_UART8RST_Pos)             /*!< 0x00080000 */
#define RCC_APB1RSTSETR_UART8RST                  RCC_APB1RSTSETR_UART8RST_Msk                       /*!< UART8 block reset */
#define RCC_APB1RSTSETR_I2C1RST_Pos               (21U)
#define RCC_APB1RSTSETR_I2C1RST_Msk               (0x1U << RCC_APB1RSTSETR_I2C1RST_Pos)              /*!< 0x00200000 */
#define RCC_APB1RSTSETR_I2C1RST                   RCC_APB1RSTSETR_I2C1RST_Msk                        /*!< I2C1 block reset */
#define RCC_APB1RSTSETR_I2C2RST_Pos               (22U)
#define RCC_APB1RSTSETR_I2C2RST_Msk               (0x1U << RCC_APB1RSTSETR_I2C2RST_Pos)              /*!< 0x00400000 */
#define RCC_APB1RSTSETR_I2C2RST                   RCC_APB1RSTSETR_I2C2RST_Msk                        /*!< I2C2 block reset */
#define RCC_APB1RSTSETR_I2C3RST_Pos               (23U)
#define RCC_APB1RSTSETR_I2C3RST_Msk               (0x1U << RCC_APB1RSTSETR_I2C3RST_Pos)              /*!< 0x00800000 */
#define RCC_APB1RSTSETR_I2C3RST                   RCC_APB1RSTSETR_I2C3RST_Msk                        /*!< I2C3 block reset */
#define RCC_APB1RSTSETR_I2C5RST_Pos               (24U)
#define RCC_APB1RSTSETR_I2C5RST_Msk               (0x1U << RCC_APB1RSTSETR_I2C5RST_Pos)              /*!< 0x01000000 */
#define RCC_APB1RSTSETR_I2C5RST                   RCC_APB1RSTSETR_I2C5RST_Msk                        /*!< I2C5 block reset */
#define RCC_APB1RSTSETR_SPDIFRST_Pos              (26U)
#define RCC_APB1RSTSETR_SPDIFRST_Msk              (0x1U << RCC_APB1RSTSETR_SPDIFRST_Pos)             /*!< 0x04000000 */
#define RCC_APB1RSTSETR_SPDIFRST                  RCC_APB1RSTSETR_SPDIFRST_Msk                       /*!< SPDIFRX block reset */
#define RCC_APB1RSTSETR_CECRST_Pos                (27U)
#define RCC_APB1RSTSETR_CECRST_Msk                (0x1U << RCC_APB1RSTSETR_CECRST_Pos)               /*!< 0x08000000 */
#define RCC_APB1RSTSETR_CECRST                    RCC_APB1RSTSETR_CECRST_Msk                         /*!< HDMI-CEC block reset */
#define RCC_APB1RSTSETR_DAC12RST_Pos              (29U)
#define RCC_APB1RSTSETR_DAC12RST_Msk              (0x1U << RCC_APB1RSTSETR_DAC12RST_Pos)             /*!< 0x20000000 */
#define RCC_APB1RSTSETR_DAC12RST                  RCC_APB1RSTSETR_DAC12RST_Msk                       /*!< DAC1&amp;2 block reset */
#define RCC_APB1RSTSETR_MDIOSRST_Pos              (31U)
#define RCC_APB1RSTSETR_MDIOSRST_Msk              (0x1U << RCC_APB1RSTSETR_MDIOSRST_Pos)             /*!< 0x80000000 */
#define RCC_APB1RSTSETR_MDIOSRST                  RCC_APB1RSTSETR_MDIOSRST_Msk                       /*!< MDIOS block reset */

/***************  Bit definition for RCC_APB1RSTCLRR register  ****************/
#define RCC_APB1RSTCLRR_TIM2RST_Pos               (0U)
#define RCC_APB1RSTCLRR_TIM2RST_Msk               (0x1U << RCC_APB1RSTCLRR_TIM2RST_Pos)              /*!< 0x00000001 */
#define RCC_APB1RSTCLRR_TIM2RST                   RCC_APB1RSTCLRR_TIM2RST_Msk                        /*!< TIM2 block reset */
#define RCC_APB1RSTCLRR_TIM3RST_Pos               (1U)
#define RCC_APB1RSTCLRR_TIM3RST_Msk               (0x1U << RCC_APB1RSTCLRR_TIM3RST_Pos)              /*!< 0x00000002 */
#define RCC_APB1RSTCLRR_TIM3RST                   RCC_APB1RSTCLRR_TIM3RST_Msk                        /*!< TIM3 block reset */
#define RCC_APB1RSTCLRR_TIM4RST_Pos               (2U)
#define RCC_APB1RSTCLRR_TIM4RST_Msk               (0x1U << RCC_APB1RSTCLRR_TIM4RST_Pos)              /*!< 0x00000004 */
#define RCC_APB1RSTCLRR_TIM4RST                   RCC_APB1RSTCLRR_TIM4RST_Msk                        /*!< TIM4 block reset */
#define RCC_APB1RSTCLRR_TIM5RST_Pos               (3U)
#define RCC_APB1RSTCLRR_TIM5RST_Msk               (0x1U << RCC_APB1RSTCLRR_TIM5RST_Pos)              /*!< 0x00000008 */
#define RCC_APB1RSTCLRR_TIM5RST                   RCC_APB1RSTCLRR_TIM5RST_Msk                        /*!< TIM5 block reset */
#define RCC_APB1RSTCLRR_TIM6RST_Pos               (4U)
#define RCC_APB1RSTCLRR_TIM6RST_Msk               (0x1U << RCC_APB1RSTCLRR_TIM6RST_Pos)              /*!< 0x00000010 */
#define RCC_APB1RSTCLRR_TIM6RST                   RCC_APB1RSTCLRR_TIM6RST_Msk                        /*!< TIM6 block reset */
#define RCC_APB1RSTCLRR_TIM7RST_Pos               (5U)
#define RCC_APB1RSTCLRR_TIM7RST_Msk               (0x1U << RCC_APB1RSTCLRR_TIM7RST_Pos)              /*!< 0x00000020 */
#define RCC_APB1RSTCLRR_TIM7RST                   RCC_APB1RSTCLRR_TIM7RST_Msk                        /*!< TIM7 block reset */
#define RCC_APB1RSTCLRR_TIM12RST_Pos              (6U)
#define RCC_APB1RSTCLRR_TIM12RST_Msk              (0x1U << RCC_APB1RSTCLRR_TIM12RST_Pos)             /*!< 0x00000040 */
#define RCC_APB1RSTCLRR_TIM12RST                  RCC_APB1RSTCLRR_TIM12RST_Msk                       /*!< TIM12 block reset */
#define RCC_APB1RSTCLRR_TIM13RST_Pos              (7U)
#define RCC_APB1RSTCLRR_TIM13RST_Msk              (0x1U << RCC_APB1RSTCLRR_TIM13RST_Pos)             /*!< 0x00000080 */
#define RCC_APB1RSTCLRR_TIM13RST                  RCC_APB1RSTCLRR_TIM13RST_Msk                       /*!< TIM13 block reset */
#define RCC_APB1RSTCLRR_TIM14RST_Pos              (8U)
#define RCC_APB1RSTCLRR_TIM14RST_Msk              (0x1U << RCC_APB1RSTCLRR_TIM14RST_Pos)             /*!< 0x00000100 */
#define RCC_APB1RSTCLRR_TIM14RST                  RCC_APB1RSTCLRR_TIM14RST_Msk                       /*!< TIM14 block reset */
#define RCC_APB1RSTCLRR_LPTIM1RST_Pos             (9U)
#define RCC_APB1RSTCLRR_LPTIM1RST_Msk             (0x1U << RCC_APB1RSTCLRR_LPTIM1RST_Pos)            /*!< 0x00000200 */
#define RCC_APB1RSTCLRR_LPTIM1RST                 RCC_APB1RSTCLRR_LPTIM1RST_Msk                      /*!< LPTIM1 block reset */
#define RCC_APB1RSTCLRR_SPI2RST_Pos               (11U)
#define RCC_APB1RSTCLRR_SPI2RST_Msk               (0x1U << RCC_APB1RSTCLRR_SPI2RST_Pos)              /*!< 0x00000800 */
#define RCC_APB1RSTCLRR_SPI2RST                   RCC_APB1RSTCLRR_SPI2RST_Msk                        /*!< SPI2 block reset */
#define RCC_APB1RSTCLRR_SPI3RST_Pos               (12U)
#define RCC_APB1RSTCLRR_SPI3RST_Msk               (0x1U << RCC_APB1RSTCLRR_SPI3RST_Pos)              /*!< 0x00001000 */
#define RCC_APB1RSTCLRR_SPI3RST                   RCC_APB1RSTCLRR_SPI3RST_Msk                        /*!< SPI3 block reset */
#define RCC_APB1RSTCLRR_USART2RST_Pos             (14U)
#define RCC_APB1RSTCLRR_USART2RST_Msk             (0x1U << RCC_APB1RSTCLRR_USART2RST_Pos)            /*!< 0x00004000 */
#define RCC_APB1RSTCLRR_USART2RST                 RCC_APB1RSTCLRR_USART2RST_Msk                      /*!< USART2 block reset */
#define RCC_APB1RSTCLRR_USART3RST_Pos             (15U)
#define RCC_APB1RSTCLRR_USART3RST_Msk             (0x1U << RCC_APB1RSTCLRR_USART3RST_Pos)            /*!< 0x00008000 */
#define RCC_APB1RSTCLRR_USART3RST                 RCC_APB1RSTCLRR_USART3RST_Msk                      /*!< USART3 block reset */
#define RCC_APB1RSTCLRR_UART4RST_Pos              (16U)
#define RCC_APB1RSTCLRR_UART4RST_Msk              (0x1U << RCC_APB1RSTCLRR_UART4RST_Pos)             /*!< 0x00010000 */
#define RCC_APB1RSTCLRR_UART4RST                  RCC_APB1RSTCLRR_UART4RST_Msk                       /*!< UART4 block reset */
#define RCC_APB1RSTCLRR_UART5RST_Pos              (17U)
#define RCC_APB1RSTCLRR_UART5RST_Msk              (0x1U << RCC_APB1RSTCLRR_UART5RST_Pos)             /*!< 0x00020000 */
#define RCC_APB1RSTCLRR_UART5RST                  RCC_APB1RSTCLRR_UART5RST_Msk                       /*!< UART5 block reset */
#define RCC_APB1RSTCLRR_UART7RST_Pos              (18U)
#define RCC_APB1RSTCLRR_UART7RST_Msk              (0x1U << RCC_APB1RSTCLRR_UART7RST_Pos)             /*!< 0x00040000 */
#define RCC_APB1RSTCLRR_UART7RST                  RCC_APB1RSTCLRR_UART7RST_Msk                       /*!< UART7 block reset */
#define RCC_APB1RSTCLRR_UART8RST_Pos              (19U)
#define RCC_APB1RSTCLRR_UART8RST_Msk              (0x1U << RCC_APB1RSTCLRR_UART8RST_Pos)             /*!< 0x00080000 */
#define RCC_APB1RSTCLRR_UART8RST                  RCC_APB1RSTCLRR_UART8RST_Msk                       /*!< UART8 block reset */
#define RCC_APB1RSTCLRR_I2C1RST_Pos               (21U)
#define RCC_APB1RSTCLRR_I2C1RST_Msk               (0x1U << RCC_APB1RSTCLRR_I2C1RST_Pos)              /*!< 0x00200000 */
#define RCC_APB1RSTCLRR_I2C1RST                   RCC_APB1RSTCLRR_I2C1RST_Msk                        /*!< I2C1 block reset */
#define RCC_APB1RSTCLRR_I2C2RST_Pos               (22U)
#define RCC_APB1RSTCLRR_I2C2RST_Msk               (0x1U << RCC_APB1RSTCLRR_I2C2RST_Pos)              /*!< 0x00400000 */
#define RCC_APB1RSTCLRR_I2C2RST                   RCC_APB1RSTCLRR_I2C2RST_Msk                        /*!< I2C2 block reset */
#define RCC_APB1RSTCLRR_I2C3RST_Pos               (23U)
#define RCC_APB1RSTCLRR_I2C3RST_Msk               (0x1U << RCC_APB1RSTCLRR_I2C3RST_Pos)              /*!< 0x00800000 */
#define RCC_APB1RSTCLRR_I2C3RST                   RCC_APB1RSTCLRR_I2C3RST_Msk                        /*!< I2C3 block reset */
#define RCC_APB1RSTCLRR_I2C5RST_Pos               (24U)
#define RCC_APB1RSTCLRR_I2C5RST_Msk               (0x1U << RCC_APB1RSTCLRR_I2C5RST_Pos)              /*!< 0x01000000 */
#define RCC_APB1RSTCLRR_I2C5RST                   RCC_APB1RSTCLRR_I2C5RST_Msk                        /*!< I2C5 block reset */
#define RCC_APB1RSTCLRR_SPDIFRST_Pos              (26U)
#define RCC_APB1RSTCLRR_SPDIFRST_Msk              (0x1U << RCC_APB1RSTCLRR_SPDIFRST_Pos)             /*!< 0x04000000 */
#define RCC_APB1RSTCLRR_SPDIFRST                  RCC_APB1RSTCLRR_SPDIFRST_Msk                       /*!< SPDIFRX block reset */
#define RCC_APB1RSTCLRR_CECRST_Pos                (27U)
#define RCC_APB1RSTCLRR_CECRST_Msk                (0x1U << RCC_APB1RSTCLRR_CECRST_Pos)               /*!< 0x08000000 */
#define RCC_APB1RSTCLRR_CECRST                    RCC_APB1RSTCLRR_CECRST_Msk                         /*!< HDMI-CEC block reset */
#define RCC_APB1RSTCLRR_DAC12RST_Pos              (29U)
#define RCC_APB1RSTCLRR_DAC12RST_Msk              (0x1U << RCC_APB1RSTCLRR_DAC12RST_Pos)             /*!< 0x20000000 */
#define RCC_APB1RSTCLRR_DAC12RST                  RCC_APB1RSTCLRR_DAC12RST_Msk                       /*!< DAC1&amp;2 block reset */
#define RCC_APB1RSTCLRR_MDIOSRST_Pos              (31U)
#define RCC_APB1RSTCLRR_MDIOSRST_Msk              (0x1U << RCC_APB1RSTCLRR_MDIOSRST_Pos)             /*!< 0x80000000 */
#define RCC_APB1RSTCLRR_MDIOSRST                  RCC_APB1RSTCLRR_MDIOSRST_Msk                       /*!< MDIOS block reset */

/***************  Bit definition for RCC_APB2RSTSETR register  ****************/
#define RCC_APB2RSTSETR_TIM1RST_Pos               (0U)
#define RCC_APB2RSTSETR_TIM1RST_Msk               (0x1U << RCC_APB2RSTSETR_TIM1RST_Pos)              /*!< 0x00000001 */
#define RCC_APB2RSTSETR_TIM1RST                   RCC_APB2RSTSETR_TIM1RST_Msk                        /*!< TIM1 block reset */
#define RCC_APB2RSTSETR_TIM8RST_Pos               (1U)
#define RCC_APB2RSTSETR_TIM8RST_Msk               (0x1U << RCC_APB2RSTSETR_TIM8RST_Pos)              /*!< 0x00000002 */
#define RCC_APB2RSTSETR_TIM8RST                   RCC_APB2RSTSETR_TIM8RST_Msk                        /*!< TIM8 block reset */
#define RCC_APB2RSTSETR_TIM15RST_Pos              (2U)
#define RCC_APB2RSTSETR_TIM15RST_Msk              (0x1U << RCC_APB2RSTSETR_TIM15RST_Pos)             /*!< 0x00000004 */
#define RCC_APB2RSTSETR_TIM15RST                  RCC_APB2RSTSETR_TIM15RST_Msk                       /*!< TIM15 block reset */
#define RCC_APB2RSTSETR_TIM16RST_Pos              (3U)
#define RCC_APB2RSTSETR_TIM16RST_Msk              (0x1U << RCC_APB2RSTSETR_TIM16RST_Pos)             /*!< 0x00000008 */
#define RCC_APB2RSTSETR_TIM16RST                  RCC_APB2RSTSETR_TIM16RST_Msk                       /*!< TIM16 block reset */
#define RCC_APB2RSTSETR_TIM17RST_Pos              (4U)
#define RCC_APB2RSTSETR_TIM17RST_Msk              (0x1U << RCC_APB2RSTSETR_TIM17RST_Pos)             /*!< 0x00000010 */
#define RCC_APB2RSTSETR_TIM17RST                  RCC_APB2RSTSETR_TIM17RST_Msk                       /*!< TIM17 block reset */
#define RCC_APB2RSTSETR_SPI1RST_Pos               (8U)
#define RCC_APB2RSTSETR_SPI1RST_Msk               (0x1U << RCC_APB2RSTSETR_SPI1RST_Pos)              /*!< 0x00000100 */
#define RCC_APB2RSTSETR_SPI1RST                   RCC_APB2RSTSETR_SPI1RST_Msk                        /*!< SPI/I2S1 block reset */
#define RCC_APB2RSTSETR_SPI4RST_Pos               (9U)
#define RCC_APB2RSTSETR_SPI4RST_Msk               (0x1U << RCC_APB2RSTSETR_SPI4RST_Pos)              /*!< 0x00000200 */
#define RCC_APB2RSTSETR_SPI4RST                   RCC_APB2RSTSETR_SPI4RST_Msk                        /*!< SPI4 block reset */
#define RCC_APB2RSTSETR_SPI5RST_Pos               (10U)
#define RCC_APB2RSTSETR_SPI5RST_Msk               (0x1U << RCC_APB2RSTSETR_SPI5RST_Pos)              /*!< 0x00000400 */
#define RCC_APB2RSTSETR_SPI5RST                   RCC_APB2RSTSETR_SPI5RST_Msk                        /*!< SPI5 block reset */
#define RCC_APB2RSTSETR_USART6RST_Pos             (13U)
#define RCC_APB2RSTSETR_USART6RST_Msk             (0x1U << RCC_APB2RSTSETR_USART6RST_Pos)            /*!< 0x00002000 */
#define RCC_APB2RSTSETR_USART6RST                 RCC_APB2RSTSETR_USART6RST_Msk                      /*!< USART6 block reset */
#define RCC_APB2RSTSETR_SAI1RST_Pos               (16U)
#define RCC_APB2RSTSETR_SAI1RST_Msk               (0x1U << RCC_APB2RSTSETR_SAI1RST_Pos)              /*!< 0x00010000 */
#define RCC_APB2RSTSETR_SAI1RST                   RCC_APB2RSTSETR_SAI1RST_Msk                        /*!< SAI1 block reset */
#define RCC_APB2RSTSETR_SAI2RST_Pos               (17U)
#define RCC_APB2RSTSETR_SAI2RST_Msk               (0x1U << RCC_APB2RSTSETR_SAI2RST_Pos)              /*!< 0x00020000 */
#define RCC_APB2RSTSETR_SAI2RST                   RCC_APB2RSTSETR_SAI2RST_Msk                        /*!< SAI2 block reset */
#define RCC_APB2RSTSETR_SAI3RST_Pos               (18U)
#define RCC_APB2RSTSETR_SAI3RST_Msk               (0x1U << RCC_APB2RSTSETR_SAI3RST_Pos)              /*!< 0x00040000 */
#define RCC_APB2RSTSETR_SAI3RST                   RCC_APB2RSTSETR_SAI3RST_Msk                        /*!< SAI3 block reset */
#define RCC_APB2RSTSETR_DFSDMRST_Pos              (20U)
#define RCC_APB2RSTSETR_DFSDMRST_Msk              (0x1U << RCC_APB2RSTSETR_DFSDMRST_Pos)             /*!< 0x00100000 */
#define RCC_APB2RSTSETR_DFSDMRST                  RCC_APB2RSTSETR_DFSDMRST_Msk                       /*!< DFSDM block reset */
#define RCC_APB2RSTSETR_FDCANRST_Pos              (24U)
#define RCC_APB2RSTSETR_FDCANRST_Msk              (0x1U << RCC_APB2RSTSETR_FDCANRST_Pos)             /*!< 0x01000000 */
#define RCC_APB2RSTSETR_FDCANRST                  RCC_APB2RSTSETR_FDCANRST_Msk                       /*!< FDCAN block reset */

/***************  Bit definition for RCC_APB2RSTCLRR register  ****************/
#define RCC_APB2RSTCLRR_TIM1RST_Pos               (0U)
#define RCC_APB2RSTCLRR_TIM1RST_Msk               (0x1U << RCC_APB2RSTCLRR_TIM1RST_Pos)              /*!< 0x00000001 */
#define RCC_APB2RSTCLRR_TIM1RST                   RCC_APB2RSTCLRR_TIM1RST_Msk                        /*!< TIM1 block reset */
#define RCC_APB2RSTCLRR_TIM8RST_Pos               (1U)
#define RCC_APB2RSTCLRR_TIM8RST_Msk               (0x1U << RCC_APB2RSTCLRR_TIM8RST_Pos)              /*!< 0x00000002 */
#define RCC_APB2RSTCLRR_TIM8RST                   RCC_APB2RSTCLRR_TIM8RST_Msk                        /*!< TIM8 block reset */
#define RCC_APB2RSTCLRR_TIM15RST_Pos              (2U)
#define RCC_APB2RSTCLRR_TIM15RST_Msk              (0x1U << RCC_APB2RSTCLRR_TIM15RST_Pos)             /*!< 0x00000004 */
#define RCC_APB2RSTCLRR_TIM15RST                  RCC_APB2RSTCLRR_TIM15RST_Msk                       /*!< TIM15 block reset */
#define RCC_APB2RSTCLRR_TIM16RST_Pos              (3U)
#define RCC_APB2RSTCLRR_TIM16RST_Msk              (0x1U << RCC_APB2RSTCLRR_TIM16RST_Pos)             /*!< 0x00000008 */
#define RCC_APB2RSTCLRR_TIM16RST                  RCC_APB2RSTCLRR_TIM16RST_Msk                       /*!< TIM16 block reset */
#define RCC_APB2RSTCLRR_TIM17RST_Pos              (4U)
#define RCC_APB2RSTCLRR_TIM17RST_Msk              (0x1U << RCC_APB2RSTCLRR_TIM17RST_Pos)             /*!< 0x00000010 */
#define RCC_APB2RSTCLRR_TIM17RST                  RCC_APB2RSTCLRR_TIM17RST_Msk                       /*!< TIM17 block reset */
#define RCC_APB2RSTCLRR_SPI1RST_Pos               (8U)
#define RCC_APB2RSTCLRR_SPI1RST_Msk               (0x1U << RCC_APB2RSTCLRR_SPI1RST_Pos)              /*!< 0x00000100 */
#define RCC_APB2RSTCLRR_SPI1RST                   RCC_APB2RSTCLRR_SPI1RST_Msk                        /*!< SPI/I2S1 block reset */
#define RCC_APB2RSTCLRR_SPI4RST_Pos               (9U)
#define RCC_APB2RSTCLRR_SPI4RST_Msk               (0x1U << RCC_APB2RSTCLRR_SPI4RST_Pos)              /*!< 0x00000200 */
#define RCC_APB2RSTCLRR_SPI4RST                   RCC_APB2RSTCLRR_SPI4RST_Msk                        /*!< SPI4 block reset */
#define RCC_APB2RSTCLRR_SPI5RST_Pos               (10U)
#define RCC_APB2RSTCLRR_SPI5RST_Msk               (0x1U << RCC_APB2RSTCLRR_SPI5RST_Pos)              /*!< 0x00000400 */
#define RCC_APB2RSTCLRR_SPI5RST                   RCC_APB2RSTCLRR_SPI5RST_Msk                        /*!< SPI5 block reset */
#define RCC_APB2RSTCLRR_USART6RST_Pos             (13U)
#define RCC_APB2RSTCLRR_USART6RST_Msk             (0x1U << RCC_APB2RSTCLRR_USART6RST_Pos)            /*!< 0x00002000 */
#define RCC_APB2RSTCLRR_USART6RST                 RCC_APB2RSTCLRR_USART6RST_Msk                      /*!< USART6 block reset */
#define RCC_APB2RSTCLRR_SAI1RST_Pos               (16U)
#define RCC_APB2RSTCLRR_SAI1RST_Msk               (0x1U << RCC_APB2RSTCLRR_SAI1RST_Pos)              /*!< 0x00010000 */
#define RCC_APB2RSTCLRR_SAI1RST                   RCC_APB2RSTCLRR_SAI1RST_Msk                        /*!< SAI1 block reset */
#define RCC_APB2RSTCLRR_SAI2RST_Pos               (17U)
#define RCC_APB2RSTCLRR_SAI2RST_Msk               (0x1U << RCC_APB2RSTCLRR_SAI2RST_Pos)              /*!< 0x00020000 */
#define RCC_APB2RSTCLRR_SAI2RST                   RCC_APB2RSTCLRR_SAI2RST_Msk                        /*!< SAI2 block reset */
#define RCC_APB2RSTCLRR_SAI3RST_Pos               (18U)
#define RCC_APB2RSTCLRR_SAI3RST_Msk               (0x1U << RCC_APB2RSTCLRR_SAI3RST_Pos)              /*!< 0x00040000 */
#define RCC_APB2RSTCLRR_SAI3RST                   RCC_APB2RSTCLRR_SAI3RST_Msk                        /*!< SAI3 block reset */
#define RCC_APB2RSTCLRR_DFSDMRST_Pos              (20U)
#define RCC_APB2RSTCLRR_DFSDMRST_Msk              (0x1U << RCC_APB2RSTCLRR_DFSDMRST_Pos)             /*!< 0x00100000 */
#define RCC_APB2RSTCLRR_DFSDMRST                  RCC_APB2RSTCLRR_DFSDMRST_Msk                       /*!< DFSDM block reset */
#define RCC_APB2RSTCLRR_FDCANRST_Pos              (24U)
#define RCC_APB2RSTCLRR_FDCANRST_Msk              (0x1U << RCC_APB2RSTCLRR_FDCANRST_Pos)             /*!< 0x01000000 */
#define RCC_APB2RSTCLRR_FDCANRST                  RCC_APB2RSTCLRR_FDCANRST_Msk                       /*!< FDCAN block reset */

/***************  Bit definition for RCC_APB3RSTSETR register  ****************/
#define RCC_APB3RSTSETR_LPTIM2RST_Pos             (0U)
#define RCC_APB3RSTSETR_LPTIM2RST_Msk             (0x1U << RCC_APB3RSTSETR_LPTIM2RST_Pos)            /*!< 0x00000001 */
#define RCC_APB3RSTSETR_LPTIM2RST                 RCC_APB3RSTSETR_LPTIM2RST_Msk                      /*!< LPTIM2 block reset */
#define RCC_APB3RSTSETR_LPTIM3RST_Pos             (1U)
#define RCC_APB3RSTSETR_LPTIM3RST_Msk             (0x1U << RCC_APB3RSTSETR_LPTIM3RST_Pos)            /*!< 0x00000002 */
#define RCC_APB3RSTSETR_LPTIM3RST                 RCC_APB3RSTSETR_LPTIM3RST_Msk                      /*!< LPTIM3 block reset */
#define RCC_APB3RSTSETR_LPTIM4RST_Pos             (2U)
#define RCC_APB3RSTSETR_LPTIM4RST_Msk             (0x1U << RCC_APB3RSTSETR_LPTIM4RST_Pos)            /*!< 0x00000004 */
#define RCC_APB3RSTSETR_LPTIM4RST                 RCC_APB3RSTSETR_LPTIM4RST_Msk                      /*!< LPTIM4 block reset */
#define RCC_APB3RSTSETR_LPTIM5RST_Pos             (3U)
#define RCC_APB3RSTSETR_LPTIM5RST_Msk             (0x1U << RCC_APB3RSTSETR_LPTIM5RST_Pos)            /*!< 0x00000008 */
#define RCC_APB3RSTSETR_LPTIM5RST                 RCC_APB3RSTSETR_LPTIM5RST_Msk                      /*!< LPTIM5 block reset */
#define RCC_APB3RSTSETR_SAI4RST_Pos               (8U)
#define RCC_APB3RSTSETR_SAI4RST_Msk               (0x1U << RCC_APB3RSTSETR_SAI4RST_Pos)              /*!< 0x00000100 */
#define RCC_APB3RSTSETR_SAI4RST                   RCC_APB3RSTSETR_SAI4RST_Msk                        /*!< SAI4 block reset */
#define RCC_APB3RSTSETR_SYSCFGRST_Pos             (11U)
#define RCC_APB3RSTSETR_SYSCFGRST_Msk             (0x1U << RCC_APB3RSTSETR_SYSCFGRST_Pos)            /*!< 0x00000800 */
#define RCC_APB3RSTSETR_SYSCFGRST                 RCC_APB3RSTSETR_SYSCFGRST_Msk                      /*!< SYSCFG block reset */
#define RCC_APB3RSTSETR_VREFRST_Pos               (13U)
#define RCC_APB3RSTSETR_VREFRST_Msk               (0x1U << RCC_APB3RSTSETR_VREFRST_Pos)              /*!< 0x00002000 */
#define RCC_APB3RSTSETR_VREFRST                   RCC_APB3RSTSETR_VREFRST_Msk                        /*!< VREF block reset */
#define RCC_APB3RSTSETR_DTSRST_Pos                (16U)
#define RCC_APB3RSTSETR_DTSRST_Msk                (0x1U << RCC_APB3RSTSETR_DTSRST_Pos)               /*!< 0x00010000 */
#define RCC_APB3RSTSETR_DTSRST                    RCC_APB3RSTSETR_DTSRST_Msk                         /*!< DTS block reset */

/***************  Bit definition for RCC_APB3RSTCLRR register  ****************/
#define RCC_APB3RSTCLRR_LPTIM2RST_Pos             (0U)
#define RCC_APB3RSTCLRR_LPTIM2RST_Msk             (0x1U << RCC_APB3RSTCLRR_LPTIM2RST_Pos)            /*!< 0x00000001 */
#define RCC_APB3RSTCLRR_LPTIM2RST                 RCC_APB3RSTCLRR_LPTIM2RST_Msk                      /*!< LPTIM2 block reset */
#define RCC_APB3RSTCLRR_LPTIM3RST_Pos             (1U)
#define RCC_APB3RSTCLRR_LPTIM3RST_Msk             (0x1U << RCC_APB3RSTCLRR_LPTIM3RST_Pos)            /*!< 0x00000002 */
#define RCC_APB3RSTCLRR_LPTIM3RST                 RCC_APB3RSTCLRR_LPTIM3RST_Msk                      /*!< LPTIM3 block reset */
#define RCC_APB3RSTCLRR_LPTIM4RST_Pos             (2U)
#define RCC_APB3RSTCLRR_LPTIM4RST_Msk             (0x1U << RCC_APB3RSTCLRR_LPTIM4RST_Pos)            /*!< 0x00000004 */
#define RCC_APB3RSTCLRR_LPTIM4RST                 RCC_APB3RSTCLRR_LPTIM4RST_Msk                      /*!< LPTIM4 block reset */
#define RCC_APB3RSTCLRR_LPTIM5RST_Pos             (3U)
#define RCC_APB3RSTCLRR_LPTIM5RST_Msk             (0x1U << RCC_APB3RSTCLRR_LPTIM5RST_Pos)            /*!< 0x00000008 */
#define RCC_APB3RSTCLRR_LPTIM5RST                 RCC_APB3RSTCLRR_LPTIM5RST_Msk                      /*!< LPTIM5 block reset */
#define RCC_APB3RSTCLRR_SAI4RST_Pos               (8U)
#define RCC_APB3RSTCLRR_SAI4RST_Msk               (0x1U << RCC_APB3RSTCLRR_SAI4RST_Pos)              /*!< 0x00000100 */
#define RCC_APB3RSTCLRR_SAI4RST                   RCC_APB3RSTCLRR_SAI4RST_Msk                        /*!< SAI4 block reset */
#define RCC_APB3RSTCLRR_SYSCFGRST_Pos             (11U)
#define RCC_APB3RSTCLRR_SYSCFGRST_Msk             (0x1U << RCC_APB3RSTCLRR_SYSCFGRST_Pos)            /*!< 0x00000800 */
#define RCC_APB3RSTCLRR_SYSCFGRST                 RCC_APB3RSTCLRR_SYSCFGRST_Msk                      /*!< SYSCFG block reset */
#define RCC_APB3RSTCLRR_VREFRST_Pos               (13U)
#define RCC_APB3RSTCLRR_VREFRST_Msk               (0x1U << RCC_APB3RSTCLRR_VREFRST_Pos)              /*!< 0x00002000 */
#define RCC_APB3RSTCLRR_VREFRST                   RCC_APB3RSTCLRR_VREFRST_Msk                        /*!< VREF block reset */
#define RCC_APB3RSTCLRR_DTSRST_Pos                (16U)
#define RCC_APB3RSTCLRR_DTSRST_Msk                (0x1U << RCC_APB3RSTCLRR_DTSRST_Pos)               /*!< 0x00010000 */
#define RCC_APB3RSTCLRR_DTSRST                    RCC_APB3RSTCLRR_DTSRST_Msk                         /*!< DTS block reset */

/***************  Bit definition for RCC_AHB2RSTSETR register  ****************/
#define RCC_AHB2RSTSETR_DMA1RST_Pos               (0U)
#define RCC_AHB2RSTSETR_DMA1RST_Msk               (0x1U << RCC_AHB2RSTSETR_DMA1RST_Pos)              /*!< 0x00000001 */
#define RCC_AHB2RSTSETR_DMA1RST                   RCC_AHB2RSTSETR_DMA1RST_Msk                        /*!< DMA1 block reset */
#define RCC_AHB2RSTSETR_DMA2RST_Pos               (1U)
#define RCC_AHB2RSTSETR_DMA2RST_Msk               (0x1U << RCC_AHB2RSTSETR_DMA2RST_Pos)              /*!< 0x00000002 */
#define RCC_AHB2RSTSETR_DMA2RST                   RCC_AHB2RSTSETR_DMA2RST_Msk                        /*!< DMA2 block reset */
#define RCC_AHB2RSTSETR_DMAMUXRST_Pos             (2U)
#define RCC_AHB2RSTSETR_DMAMUXRST_Msk             (0x1U << RCC_AHB2RSTSETR_DMAMUXRST_Pos)            /*!< 0x00000004 */
#define RCC_AHB2RSTSETR_DMAMUXRST                 RCC_AHB2RSTSETR_DMAMUXRST_Msk                      /*!< DMAMUX block reset */
#define RCC_AHB2RSTSETR_ADC12RST_Pos              (5U)
#define RCC_AHB2RSTSETR_ADC12RST_Msk              (0x1U << RCC_AHB2RSTSETR_ADC12RST_Pos)             /*!< 0x00000020 */
#define RCC_AHB2RSTSETR_ADC12RST                  RCC_AHB2RSTSETR_ADC12RST_Msk                       /*!< ADC1&amp;2 block reset */
#define RCC_AHB2RSTSETR_USBORST_Pos               (8U)
#define RCC_AHB2RSTSETR_USBORST_Msk               (0x1U << RCC_AHB2RSTSETR_USBORST_Pos)              /*!< 0x00000100 */
#define RCC_AHB2RSTSETR_USBORST                   RCC_AHB2RSTSETR_USBORST_Msk                        /*!< USBO block reset */
#define RCC_AHB2RSTSETR_SDMMC3RST_Pos             (16U)
#define RCC_AHB2RSTSETR_SDMMC3RST_Msk             (0x1U << RCC_AHB2RSTSETR_SDMMC3RST_Pos)            /*!< 0x00010000 */
#define RCC_AHB2RSTSETR_SDMMC3RST                 RCC_AHB2RSTSETR_SDMMC3RST_Msk                      /*!< SDMMC3 and the SDMMC3 delay (DLYBSD3) block reset */

/***************  Bit definition for RCC_AHB2RSTCLRR register  ****************/
#define RCC_AHB2RSTCLRR_DMA1RST_Pos               (0U)
#define RCC_AHB2RSTCLRR_DMA1RST_Msk               (0x1U << RCC_AHB2RSTCLRR_DMA1RST_Pos)              /*!< 0x00000001 */
#define RCC_AHB2RSTCLRR_DMA1RST                   RCC_AHB2RSTCLRR_DMA1RST_Msk                        /*!< DMA1 block reset */
#define RCC_AHB2RSTCLRR_DMA2RST_Pos               (1U)
#define RCC_AHB2RSTCLRR_DMA2RST_Msk               (0x1U << RCC_AHB2RSTCLRR_DMA2RST_Pos)              /*!< 0x00000002 */
#define RCC_AHB2RSTCLRR_DMA2RST                   RCC_AHB2RSTCLRR_DMA2RST_Msk                        /*!< DMA2 block reset */
#define RCC_AHB2RSTCLRR_DMAMUXRST_Pos             (2U)
#define RCC_AHB2RSTCLRR_DMAMUXRST_Msk             (0x1U << RCC_AHB2RSTCLRR_DMAMUXRST_Pos)            /*!< 0x00000004 */
#define RCC_AHB2RSTCLRR_DMAMUXRST                 RCC_AHB2RSTCLRR_DMAMUXRST_Msk                      /*!< DMAMUX block reset */
#define RCC_AHB2RSTCLRR_ADC12RST_Pos              (5U)
#define RCC_AHB2RSTCLRR_ADC12RST_Msk              (0x1U << RCC_AHB2RSTCLRR_ADC12RST_Pos)             /*!< 0x00000020 */
#define RCC_AHB2RSTCLRR_ADC12RST                  RCC_AHB2RSTCLRR_ADC12RST_Msk                       /*!< ADC1&amp;2 block reset */
#define RCC_AHB2RSTCLRR_USBORST_Pos               (8U)
#define RCC_AHB2RSTCLRR_USBORST_Msk               (0x1U << RCC_AHB2RSTCLRR_USBORST_Pos)              /*!< 0x00000100 */
#define RCC_AHB2RSTCLRR_USBORST                   RCC_AHB2RSTCLRR_USBORST_Msk                        /*!< USBO block reset */
#define RCC_AHB2RSTCLRR_SDMMC3RST_Pos             (16U)
#define RCC_AHB2RSTCLRR_SDMMC3RST_Msk             (0x1U << RCC_AHB2RSTCLRR_SDMMC3RST_Pos)            /*!< 0x00010000 */
#define RCC_AHB2RSTCLRR_SDMMC3RST                 RCC_AHB2RSTCLRR_SDMMC3RST_Msk                      /*!< SDMMC3 and the SDMMC3 delay (DLYBSD3) block reset */

/***************  Bit definition for RCC_AHB3RSTSETR register  ****************/
#define RCC_AHB3RSTSETR_DCMIRST_Pos               (0U)
#define RCC_AHB3RSTSETR_DCMIRST_Msk               (0x1U << RCC_AHB3RSTSETR_DCMIRST_Pos)              /*!< 0x00000001 */
#define RCC_AHB3RSTSETR_DCMIRST                   RCC_AHB3RSTSETR_DCMIRST_Msk                        /*!< DCMI block reset */
#define RCC_AHB3RSTSETR_CRYP2RST_Pos              (4U)
#define RCC_AHB3RSTSETR_CRYP2RST_Msk              (0x1U << RCC_AHB3RSTSETR_CRYP2RST_Pos)             /*!< 0x00000010 */
#define RCC_AHB3RSTSETR_CRYP2RST                  RCC_AHB3RSTSETR_CRYP2RST_Msk                       /*!< CRYP2 (3DES/AES2) block reset */
#define RCC_AHB3RSTSETR_HASH2RST_Pos              (5U)
#define RCC_AHB3RSTSETR_HASH2RST_Msk              (0x1U << RCC_AHB3RSTSETR_HASH2RST_Pos)             /*!< 0x00000020 */
#define RCC_AHB3RSTSETR_HASH2RST                  RCC_AHB3RSTSETR_HASH2RST_Msk                       /*!< HASH2 block reset */
#define RCC_AHB3RSTSETR_RNG2RST_Pos               (6U)
#define RCC_AHB3RSTSETR_RNG2RST_Msk               (0x1U << RCC_AHB3RSTSETR_RNG2RST_Pos)              /*!< 0x00000040 */
#define RCC_AHB3RSTSETR_RNG2RST                   RCC_AHB3RSTSETR_RNG2RST_Msk                        /*!< RNG2 block reset */
#define RCC_AHB3RSTSETR_CRC2RST_Pos               (7U)
#define RCC_AHB3RSTSETR_CRC2RST_Msk               (0x1U << RCC_AHB3RSTSETR_CRC2RST_Pos)              /*!< 0x00000080 */
#define RCC_AHB3RSTSETR_CRC2RST                   RCC_AHB3RSTSETR_CRC2RST_Msk                        /*!< CRC2 block reset */
#define RCC_AHB3RSTSETR_HSEMRST_Pos               (11U)
#define RCC_AHB3RSTSETR_HSEMRST_Msk               (0x1U << RCC_AHB3RSTSETR_HSEMRST_Pos)              /*!< 0x00000800 */
#define RCC_AHB3RSTSETR_HSEMRST                   RCC_AHB3RSTSETR_HSEMRST_Msk                        /*!< HSEM block reset */
#define RCC_AHB3RSTSETR_IPCCRST_Pos               (12U)
#define RCC_AHB3RSTSETR_IPCCRST_Msk               (0x1U << RCC_AHB3RSTSETR_IPCCRST_Pos)              /*!< 0x00001000 */
#define RCC_AHB3RSTSETR_IPCCRST                   RCC_AHB3RSTSETR_IPCCRST_Msk                        /*!< IPCC block reset */

/***************  Bit definition for RCC_AHB3RSTCLRR register  ****************/
#define RCC_AHB3RSTCLRR_DCMIRST_Pos               (0U)
#define RCC_AHB3RSTCLRR_DCMIRST_Msk               (0x1U << RCC_AHB3RSTCLRR_DCMIRST_Pos)              /*!< 0x00000001 */
#define RCC_AHB3RSTCLRR_DCMIRST                   RCC_AHB3RSTCLRR_DCMIRST_Msk                        /*!< DCMI block reset */
#define RCC_AHB3RSTCLRR_CRYP2RST_Pos              (4U)
#define RCC_AHB3RSTCLRR_CRYP2RST_Msk              (0x1U << RCC_AHB3RSTCLRR_CRYP2RST_Pos)             /*!< 0x00000010 */
#define RCC_AHB3RSTCLRR_CRYP2RST                  RCC_AHB3RSTCLRR_CRYP2RST_Msk                       /*!< CRYP2 (3DES/AES2) block reset */
#define RCC_AHB3RSTCLRR_HASH2RST_Pos              (5U)
#define RCC_AHB3RSTCLRR_HASH2RST_Msk              (0x1U << RCC_AHB3RSTCLRR_HASH2RST_Pos)             /*!< 0x00000020 */
#define RCC_AHB3RSTCLRR_HASH2RST                  RCC_AHB3RSTCLRR_HASH2RST_Msk                       /*!< HASH2 block reset */
#define RCC_AHB3RSTCLRR_RNG2RST_Pos               (6U)
#define RCC_AHB3RSTCLRR_RNG2RST_Msk               (0x1U << RCC_AHB3RSTCLRR_RNG2RST_Pos)              /*!< 0x00000040 */
#define RCC_AHB3RSTCLRR_RNG2RST                   RCC_AHB3RSTCLRR_RNG2RST_Msk                        /*!< RNG2 block reset */
#define RCC_AHB3RSTCLRR_CRC2RST_Pos               (7U)
#define RCC_AHB3RSTCLRR_CRC2RST_Msk               (0x1U << RCC_AHB3RSTCLRR_CRC2RST_Pos)              /*!< 0x00000080 */
#define RCC_AHB3RSTCLRR_CRC2RST                   RCC_AHB3RSTCLRR_CRC2RST_Msk                        /*!< CRC2 block reset */
#define RCC_AHB3RSTCLRR_HSEMRST_Pos               (11U)
#define RCC_AHB3RSTCLRR_HSEMRST_Msk               (0x1U << RCC_AHB3RSTCLRR_HSEMRST_Pos)              /*!< 0x00000800 */
#define RCC_AHB3RSTCLRR_HSEMRST                   RCC_AHB3RSTCLRR_HSEMRST_Msk                        /*!< HSEM block reset */
#define RCC_AHB3RSTCLRR_IPCCRST_Pos               (12U)
#define RCC_AHB3RSTCLRR_IPCCRST_Msk               (0x1U << RCC_AHB3RSTCLRR_IPCCRST_Pos)              /*!< 0x00001000 */
#define RCC_AHB3RSTCLRR_IPCCRST                   RCC_AHB3RSTCLRR_IPCCRST_Msk                        /*!< IPCC block reset */

/***************  Bit definition for RCC_AHB4RSTSETR register  ****************/
#define RCC_AHB4RSTSETR_GPIOARST_Pos              (0U)
#define RCC_AHB4RSTSETR_GPIOARST_Msk              (0x1U << RCC_AHB4RSTSETR_GPIOARST_Pos)             /*!< 0x00000001 */
#define RCC_AHB4RSTSETR_GPIOARST                  RCC_AHB4RSTSETR_GPIOARST_Msk                       /*!< GPIOA block reset */
#define RCC_AHB4RSTSETR_GPIOBRST_Pos              (1U)
#define RCC_AHB4RSTSETR_GPIOBRST_Msk              (0x1U << RCC_AHB4RSTSETR_GPIOBRST_Pos)             /*!< 0x00000002 */
#define RCC_AHB4RSTSETR_GPIOBRST                  RCC_AHB4RSTSETR_GPIOBRST_Msk                       /*!< GPIOB block reset */
#define RCC_AHB4RSTSETR_GPIOCRST_Pos              (2U)
#define RCC_AHB4RSTSETR_GPIOCRST_Msk              (0x1U << RCC_AHB4RSTSETR_GPIOCRST_Pos)             /*!< 0x00000004 */
#define RCC_AHB4RSTSETR_GPIOCRST                  RCC_AHB4RSTSETR_GPIOCRST_Msk                       /*!< GPIOC block reset */
#define RCC_AHB4RSTSETR_GPIODRST_Pos              (3U)
#define RCC_AHB4RSTSETR_GPIODRST_Msk              (0x1U << RCC_AHB4RSTSETR_GPIODRST_Pos)             /*!< 0x00000008 */
#define RCC_AHB4RSTSETR_GPIODRST                  RCC_AHB4RSTSETR_GPIODRST_Msk                       /*!< GPIOD block reset */
#define RCC_AHB4RSTSETR_GPIOERST_Pos              (4U)
#define RCC_AHB4RSTSETR_GPIOERST_Msk              (0x1U << RCC_AHB4RSTSETR_GPIOERST_Pos)             /*!< 0x00000010 */
#define RCC_AHB4RSTSETR_GPIOERST                  RCC_AHB4RSTSETR_GPIOERST_Msk                       /*!< GPIOE block reset */
#define RCC_AHB4RSTSETR_GPIOFRST_Pos              (5U)
#define RCC_AHB4RSTSETR_GPIOFRST_Msk              (0x1U << RCC_AHB4RSTSETR_GPIOFRST_Pos)             /*!< 0x00000020 */
#define RCC_AHB4RSTSETR_GPIOFRST                  RCC_AHB4RSTSETR_GPIOFRST_Msk                       /*!< GPIOF block reset */
#define RCC_AHB4RSTSETR_GPIOGRST_Pos              (6U)
#define RCC_AHB4RSTSETR_GPIOGRST_Msk              (0x1U << RCC_AHB4RSTSETR_GPIOGRST_Pos)             /*!< 0x00000040 */
#define RCC_AHB4RSTSETR_GPIOGRST                  RCC_AHB4RSTSETR_GPIOGRST_Msk                       /*!< GPIOG block reset */
#define RCC_AHB4RSTSETR_GPIOHRST_Pos              (7U)
#define RCC_AHB4RSTSETR_GPIOHRST_Msk              (0x1U << RCC_AHB4RSTSETR_GPIOHRST_Pos)             /*!< 0x00000080 */
#define RCC_AHB4RSTSETR_GPIOHRST                  RCC_AHB4RSTSETR_GPIOHRST_Msk                       /*!< GPIOH block reset */
#define RCC_AHB4RSTSETR_GPIOIRST_Pos              (8U)
#define RCC_AHB4RSTSETR_GPIOIRST_Msk              (0x1U << RCC_AHB4RSTSETR_GPIOIRST_Pos)             /*!< 0x00000100 */
#define RCC_AHB4RSTSETR_GPIOIRST                  RCC_AHB4RSTSETR_GPIOIRST_Msk                       /*!< GPIOI block reset */
#define RCC_AHB4RSTSETR_GPIOJRST_Pos              (9U)
#define RCC_AHB4RSTSETR_GPIOJRST_Msk              (0x1U << RCC_AHB4RSTSETR_GPIOJRST_Pos)             /*!< 0x00000200 */
#define RCC_AHB4RSTSETR_GPIOJRST                  RCC_AHB4RSTSETR_GPIOJRST_Msk                       /*!< GPIOJ block reset */
#define RCC_AHB4RSTSETR_GPIOKRST_Pos              (10U)
#define RCC_AHB4RSTSETR_GPIOKRST_Msk              (0x1U << RCC_AHB4RSTSETR_GPIOKRST_Pos)             /*!< 0x00000400 */
#define RCC_AHB4RSTSETR_GPIOKRST                  RCC_AHB4RSTSETR_GPIOKRST_Msk                       /*!< GPIOK block reset */

/***************  Bit definition for RCC_AHB4RSTCLRR register  ****************/
#define RCC_AHB4RSTCLRR_GPIOARST_Pos              (0U)
#define RCC_AHB4RSTCLRR_GPIOARST_Msk              (0x1U << RCC_AHB4RSTCLRR_GPIOARST_Pos)             /*!< 0x00000001 */
#define RCC_AHB4RSTCLRR_GPIOARST                  RCC_AHB4RSTCLRR_GPIOARST_Msk                       /*!< GPIOA block reset */
#define RCC_AHB4RSTCLRR_GPIOBRST_Pos              (1U)
#define RCC_AHB4RSTCLRR_GPIOBRST_Msk              (0x1U << RCC_AHB4RSTCLRR_GPIOBRST_Pos)             /*!< 0x00000002 */
#define RCC_AHB4RSTCLRR_GPIOBRST                  RCC_AHB4RSTCLRR_GPIOBRST_Msk                       /*!< GPIOB block reset */
#define RCC_AHB4RSTCLRR_GPIOCRST_Pos              (2U)
#define RCC_AHB4RSTCLRR_GPIOCRST_Msk              (0x1U << RCC_AHB4RSTCLRR_GPIOCRST_Pos)             /*!< 0x00000004 */
#define RCC_AHB4RSTCLRR_GPIOCRST                  RCC_AHB4RSTCLRR_GPIOCRST_Msk                       /*!< GPIOC block reset */
#define RCC_AHB4RSTCLRR_GPIODRST_Pos              (3U)
#define RCC_AHB4RSTCLRR_GPIODRST_Msk              (0x1U << RCC_AHB4RSTCLRR_GPIODRST_Pos)             /*!< 0x00000008 */
#define RCC_AHB4RSTCLRR_GPIODRST                  RCC_AHB4RSTCLRR_GPIODRST_Msk                       /*!< GPIOD block reset */
#define RCC_AHB4RSTCLRR_GPIOERST_Pos              (4U)
#define RCC_AHB4RSTCLRR_GPIOERST_Msk              (0x1U << RCC_AHB4RSTCLRR_GPIOERST_Pos)             /*!< 0x00000010 */
#define RCC_AHB4RSTCLRR_GPIOERST                  RCC_AHB4RSTCLRR_GPIOERST_Msk                       /*!< GPIOE block reset */
#define RCC_AHB4RSTCLRR_GPIOFRST_Pos              (5U)
#define RCC_AHB4RSTCLRR_GPIOFRST_Msk              (0x1U << RCC_AHB4RSTCLRR_GPIOFRST_Pos)             /*!< 0x00000020 */
#define RCC_AHB4RSTCLRR_GPIOFRST                  RCC_AHB4RSTCLRR_GPIOFRST_Msk                       /*!< GPIOF block reset */
#define RCC_AHB4RSTCLRR_GPIOGRST_Pos              (6U)
#define RCC_AHB4RSTCLRR_GPIOGRST_Msk              (0x1U << RCC_AHB4RSTCLRR_GPIOGRST_Pos)             /*!< 0x00000040 */
#define RCC_AHB4RSTCLRR_GPIOGRST                  RCC_AHB4RSTCLRR_GPIOGRST_Msk                       /*!< GPIOG block reset */
#define RCC_AHB4RSTCLRR_GPIOHRST_Pos              (7U)
#define RCC_AHB4RSTCLRR_GPIOHRST_Msk              (0x1U << RCC_AHB4RSTCLRR_GPIOHRST_Pos)             /*!< 0x00000080 */
#define RCC_AHB4RSTCLRR_GPIOHRST                  RCC_AHB4RSTCLRR_GPIOHRST_Msk                       /*!< GPIOH block reset */
#define RCC_AHB4RSTCLRR_GPIOIRST_Pos              (8U)
#define RCC_AHB4RSTCLRR_GPIOIRST_Msk              (0x1U << RCC_AHB4RSTCLRR_GPIOIRST_Pos)             /*!< 0x00000100 */
#define RCC_AHB4RSTCLRR_GPIOIRST                  RCC_AHB4RSTCLRR_GPIOIRST_Msk                       /*!< GPIOI block reset */
#define RCC_AHB4RSTCLRR_GPIOJRST_Pos              (9U)
#define RCC_AHB4RSTCLRR_GPIOJRST_Msk              (0x1U << RCC_AHB4RSTCLRR_GPIOJRST_Pos)             /*!< 0x00000200 */
#define RCC_AHB4RSTCLRR_GPIOJRST                  RCC_AHB4RSTCLRR_GPIOJRST_Msk                       /*!< GPIOJ block reset */
#define RCC_AHB4RSTCLRR_GPIOKRST_Pos              (10U)
#define RCC_AHB4RSTCLRR_GPIOKRST_Msk              (0x1U << RCC_AHB4RSTCLRR_GPIOKRST_Pos)             /*!< 0x00000400 */
#define RCC_AHB4RSTCLRR_GPIOKRST                  RCC_AHB4RSTCLRR_GPIOKRST_Msk                       /*!< GPIOK block reset */

/**************  Bit definition for RCC_MP_APB1ENSETR register  ***************/
#define RCC_MP_APB1ENSETR_TIM2EN_Pos              (0U)
#define RCC_MP_APB1ENSETR_TIM2EN_Msk              (0x1U << RCC_MP_APB1ENSETR_TIM2EN_Pos)             /*!< 0x00000001 */
#define RCC_MP_APB1ENSETR_TIM2EN                  RCC_MP_APB1ENSETR_TIM2EN_Msk                       /*!< TIM2 peripheral clocks enable */
#define RCC_MP_APB1ENSETR_TIM3EN_Pos              (1U)
#define RCC_MP_APB1ENSETR_TIM3EN_Msk              (0x1U << RCC_MP_APB1ENSETR_TIM3EN_Pos)             /*!< 0x00000002 */
#define RCC_MP_APB1ENSETR_TIM3EN                  RCC_MP_APB1ENSETR_TIM3EN_Msk                       /*!< TIM3 peripheral clocks enable */
#define RCC_MP_APB1ENSETR_TIM4EN_Pos              (2U)
#define RCC_MP_APB1ENSETR_TIM4EN_Msk              (0x1U << RCC_MP_APB1ENSETR_TIM4EN_Pos)             /*!< 0x00000004 */
#define RCC_MP_APB1ENSETR_TIM4EN                  RCC_MP_APB1ENSETR_TIM4EN_Msk                       /*!< TIM4 peripheral clocks enable */
#define RCC_MP_APB1ENSETR_TIM5EN_Pos              (3U)
#define RCC_MP_APB1ENSETR_TIM5EN_Msk              (0x1U << RCC_MP_APB1ENSETR_TIM5EN_Pos)             /*!< 0x00000008 */
#define RCC_MP_APB1ENSETR_TIM5EN                  RCC_MP_APB1ENSETR_TIM5EN_Msk                       /*!< TIM5 peripheral clocks enable */
#define RCC_MP_APB1ENSETR_TIM6EN_Pos              (4U)
#define RCC_MP_APB1ENSETR_TIM6EN_Msk              (0x1U << RCC_MP_APB1ENSETR_TIM6EN_Pos)             /*!< 0x00000010 */
#define RCC_MP_APB1ENSETR_TIM6EN                  RCC_MP_APB1ENSETR_TIM6EN_Msk                       /*!< TIM6 peripheral clocks enable */
#define RCC_MP_APB1ENSETR_TIM7EN_Pos              (5U)
#define RCC_MP_APB1ENSETR_TIM7EN_Msk              (0x1U << RCC_MP_APB1ENSETR_TIM7EN_Pos)             /*!< 0x00000020 */
#define RCC_MP_APB1ENSETR_TIM7EN                  RCC_MP_APB1ENSETR_TIM7EN_Msk                       /*!< TIM7 peripheral clocks enable */
#define RCC_MP_APB1ENSETR_TIM12EN_Pos             (6U)
#define RCC_MP_APB1ENSETR_TIM12EN_Msk             (0x1U << RCC_MP_APB1ENSETR_TIM12EN_Pos)            /*!< 0x00000040 */
#define RCC_MP_APB1ENSETR_TIM12EN                 RCC_MP_APB1ENSETR_TIM12EN_Msk                      /*!< TIM12 peripheral clocks enable */
#define RCC_MP_APB1ENSETR_TIM13EN_Pos             (7U)
#define RCC_MP_APB1ENSETR_TIM13EN_Msk             (0x1U << RCC_MP_APB1ENSETR_TIM13EN_Pos)            /*!< 0x00000080 */
#define RCC_MP_APB1ENSETR_TIM13EN                 RCC_MP_APB1ENSETR_TIM13EN_Msk                      /*!< TIM13 peripheral clocks enable */
#define RCC_MP_APB1ENSETR_TIM14EN_Pos             (8U)
#define RCC_MP_APB1ENSETR_TIM14EN_Msk             (0x1U << RCC_MP_APB1ENSETR_TIM14EN_Pos)            /*!< 0x00000100 */
#define RCC_MP_APB1ENSETR_TIM14EN                 RCC_MP_APB1ENSETR_TIM14EN_Msk                      /*!< TIM14 peripheral clocks enable */
#define RCC_MP_APB1ENSETR_LPTIM1EN_Pos            (9U)
#define RCC_MP_APB1ENSETR_LPTIM1EN_Msk            (0x1U << RCC_MP_APB1ENSETR_LPTIM1EN_Pos)           /*!< 0x00000200 */
#define RCC_MP_APB1ENSETR_LPTIM1EN                RCC_MP_APB1ENSETR_LPTIM1EN_Msk                     /*!< LPTIM1 peripheral clocks enable */
#define RCC_MP_APB1ENSETR_SPI2EN_Pos              (11U)
#define RCC_MP_APB1ENSETR_SPI2EN_Msk              (0x1U << RCC_MP_APB1ENSETR_SPI2EN_Pos)             /*!< 0x00000800 */
#define RCC_MP_APB1ENSETR_SPI2EN                  RCC_MP_APB1ENSETR_SPI2EN_Msk                       /*!< SPI2 peripheral clocks enable */
#define RCC_MP_APB1ENSETR_SPI3EN_Pos              (12U)
#define RCC_MP_APB1ENSETR_SPI3EN_Msk              (0x1U << RCC_MP_APB1ENSETR_SPI3EN_Pos)             /*!< 0x00001000 */
#define RCC_MP_APB1ENSETR_SPI3EN                  RCC_MP_APB1ENSETR_SPI3EN_Msk                       /*!< SPI3 peripheral clocks enable */
#define RCC_MP_APB1ENSETR_USART2EN_Pos            (14U)
#define RCC_MP_APB1ENSETR_USART2EN_Msk            (0x1U << RCC_MP_APB1ENSETR_USART2EN_Pos)           /*!< 0x00004000 */
#define RCC_MP_APB1ENSETR_USART2EN                RCC_MP_APB1ENSETR_USART2EN_Msk                     /*!< USART2 peripheral clocks enable */
#define RCC_MP_APB1ENSETR_USART3EN_Pos            (15U)
#define RCC_MP_APB1ENSETR_USART3EN_Msk            (0x1U << RCC_MP_APB1ENSETR_USART3EN_Pos)           /*!< 0x00008000 */
#define RCC_MP_APB1ENSETR_USART3EN                RCC_MP_APB1ENSETR_USART3EN_Msk                     /*!< USART3 peripheral clocks enable */
#define RCC_MP_APB1ENSETR_UART4EN_Pos             (16U)
#define RCC_MP_APB1ENSETR_UART4EN_Msk             (0x1U << RCC_MP_APB1ENSETR_UART4EN_Pos)            /*!< 0x00010000 */
#define RCC_MP_APB1ENSETR_UART4EN                 RCC_MP_APB1ENSETR_UART4EN_Msk                      /*!< UART4 peripheral clocks enable */
#define RCC_MP_APB1ENSETR_UART5EN_Pos             (17U)
#define RCC_MP_APB1ENSETR_UART5EN_Msk             (0x1U << RCC_MP_APB1ENSETR_UART5EN_Pos)            /*!< 0x00020000 */
#define RCC_MP_APB1ENSETR_UART5EN                 RCC_MP_APB1ENSETR_UART5EN_Msk                      /*!< UART5 peripheral clocks enable */
#define RCC_MP_APB1ENSETR_UART7EN_Pos             (18U)
#define RCC_MP_APB1ENSETR_UART7EN_Msk             (0x1U << RCC_MP_APB1ENSETR_UART7EN_Pos)            /*!< 0x00040000 */
#define RCC_MP_APB1ENSETR_UART7EN                 RCC_MP_APB1ENSETR_UART7EN_Msk                      /*!< UART7 peripheral clocks enable */
#define RCC_MP_APB1ENSETR_UART8EN_Pos             (19U)
#define RCC_MP_APB1ENSETR_UART8EN_Msk             (0x1U << RCC_MP_APB1ENSETR_UART8EN_Pos)            /*!< 0x00080000 */
#define RCC_MP_APB1ENSETR_UART8EN                 RCC_MP_APB1ENSETR_UART8EN_Msk                      /*!< UART8 peripheral clocks enable */
#define RCC_MP_APB1ENSETR_I2C1EN_Pos              (21U)
#define RCC_MP_APB1ENSETR_I2C1EN_Msk              (0x1U << RCC_MP_APB1ENSETR_I2C1EN_Pos)             /*!< 0x00200000 */
#define RCC_MP_APB1ENSETR_I2C1EN                  RCC_MP_APB1ENSETR_I2C1EN_Msk                       /*!< I2C1 peripheral clocks enable */
#define RCC_MP_APB1ENSETR_I2C2EN_Pos              (22U)
#define RCC_MP_APB1ENSETR_I2C2EN_Msk              (0x1U << RCC_MP_APB1ENSETR_I2C2EN_Pos)             /*!< 0x00400000 */
#define RCC_MP_APB1ENSETR_I2C2EN                  RCC_MP_APB1ENSETR_I2C2EN_Msk                       /*!< I2C2 peripheral clocks enable */
#define RCC_MP_APB1ENSETR_I2C3EN_Pos              (23U)
#define RCC_MP_APB1ENSETR_I2C3EN_Msk              (0x1U << RCC_MP_APB1ENSETR_I2C3EN_Pos)             /*!< 0x00800000 */
#define RCC_MP_APB1ENSETR_I2C3EN                  RCC_MP_APB1ENSETR_I2C3EN_Msk                       /*!< I2C3 peripheral clocks enable */
#define RCC_MP_APB1ENSETR_I2C5EN_Pos              (24U)
#define RCC_MP_APB1ENSETR_I2C5EN_Msk              (0x1U << RCC_MP_APB1ENSETR_I2C5EN_Pos)             /*!< 0x01000000 */
#define RCC_MP_APB1ENSETR_I2C5EN                  RCC_MP_APB1ENSETR_I2C5EN_Msk                       /*!< I2C5 peripheral clocks enable */
#define RCC_MP_APB1ENSETR_SPDIFEN_Pos             (26U)
#define RCC_MP_APB1ENSETR_SPDIFEN_Msk             (0x1U << RCC_MP_APB1ENSETR_SPDIFEN_Pos)            /*!< 0x04000000 */
#define RCC_MP_APB1ENSETR_SPDIFEN                 RCC_MP_APB1ENSETR_SPDIFEN_Msk                      /*!< SPDIFRX peripheral clocks enable */
#define RCC_MP_APB1ENSETR_CECEN_Pos               (27U)
#define RCC_MP_APB1ENSETR_CECEN_Msk               (0x1U << RCC_MP_APB1ENSETR_CECEN_Pos)              /*!< 0x08000000 */
#define RCC_MP_APB1ENSETR_CECEN                   RCC_MP_APB1ENSETR_CECEN_Msk                        /*!< HDMI-CEC peripheral clocks enable */
#define RCC_MP_APB1ENSETR_DAC12EN_Pos             (29U)
#define RCC_MP_APB1ENSETR_DAC12EN_Msk             (0x1U << RCC_MP_APB1ENSETR_DAC12EN_Pos)            /*!< 0x20000000 */
#define RCC_MP_APB1ENSETR_DAC12EN                 RCC_MP_APB1ENSETR_DAC12EN_Msk                      /*!< DAC1&amp;2 peripheral clocks enable */
#define RCC_MP_APB1ENSETR_MDIOSEN_Pos             (31U)
#define RCC_MP_APB1ENSETR_MDIOSEN_Msk             (0x1U << RCC_MP_APB1ENSETR_MDIOSEN_Pos)            /*!< 0x80000000 */
#define RCC_MP_APB1ENSETR_MDIOSEN                 RCC_MP_APB1ENSETR_MDIOSEN_Msk                      /*!< MDIOS peripheral clocks enable */

/**************  Bit definition for RCC_MP_APB1ENCLRR register  ***************/
#define RCC_MP_APB1ENCLRR_TIM2EN_Pos              (0U)
#define RCC_MP_APB1ENCLRR_TIM2EN_Msk              (0x1U << RCC_MP_APB1ENCLRR_TIM2EN_Pos)             /*!< 0x00000001 */
#define RCC_MP_APB1ENCLRR_TIM2EN                  RCC_MP_APB1ENCLRR_TIM2EN_Msk                       /*!< TIM2 peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_TIM3EN_Pos              (1U)
#define RCC_MP_APB1ENCLRR_TIM3EN_Msk              (0x1U << RCC_MP_APB1ENCLRR_TIM3EN_Pos)             /*!< 0x00000002 */
#define RCC_MP_APB1ENCLRR_TIM3EN                  RCC_MP_APB1ENCLRR_TIM3EN_Msk                       /*!< TIM3 peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_TIM4EN_Pos              (2U)
#define RCC_MP_APB1ENCLRR_TIM4EN_Msk              (0x1U << RCC_MP_APB1ENCLRR_TIM4EN_Pos)             /*!< 0x00000004 */
#define RCC_MP_APB1ENCLRR_TIM4EN                  RCC_MP_APB1ENCLRR_TIM4EN_Msk                       /*!< TIM4 peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_TIM5EN_Pos              (3U)
#define RCC_MP_APB1ENCLRR_TIM5EN_Msk              (0x1U << RCC_MP_APB1ENCLRR_TIM5EN_Pos)             /*!< 0x00000008 */
#define RCC_MP_APB1ENCLRR_TIM5EN                  RCC_MP_APB1ENCLRR_TIM5EN_Msk                       /*!< TIM5 peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_TIM6EN_Pos              (4U)
#define RCC_MP_APB1ENCLRR_TIM6EN_Msk              (0x1U << RCC_MP_APB1ENCLRR_TIM6EN_Pos)             /*!< 0x00000010 */
#define RCC_MP_APB1ENCLRR_TIM6EN                  RCC_MP_APB1ENCLRR_TIM6EN_Msk                       /*!< TIM6 peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_TIM7EN_Pos              (5U)
#define RCC_MP_APB1ENCLRR_TIM7EN_Msk              (0x1U << RCC_MP_APB1ENCLRR_TIM7EN_Pos)             /*!< 0x00000020 */
#define RCC_MP_APB1ENCLRR_TIM7EN                  RCC_MP_APB1ENCLRR_TIM7EN_Msk                       /*!< TIM7 peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_TIM12EN_Pos             (6U)
#define RCC_MP_APB1ENCLRR_TIM12EN_Msk             (0x1U << RCC_MP_APB1ENCLRR_TIM12EN_Pos)            /*!< 0x00000040 */
#define RCC_MP_APB1ENCLRR_TIM12EN                 RCC_MP_APB1ENCLRR_TIM12EN_Msk                      /*!< TIM12 peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_TIM13EN_Pos             (7U)
#define RCC_MP_APB1ENCLRR_TIM13EN_Msk             (0x1U << RCC_MP_APB1ENCLRR_TIM13EN_Pos)            /*!< 0x00000080 */
#define RCC_MP_APB1ENCLRR_TIM13EN                 RCC_MP_APB1ENCLRR_TIM13EN_Msk                      /*!< TIM13 peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_TIM14EN_Pos             (8U)
#define RCC_MP_APB1ENCLRR_TIM14EN_Msk             (0x1U << RCC_MP_APB1ENCLRR_TIM14EN_Pos)            /*!< 0x00000100 */
#define RCC_MP_APB1ENCLRR_TIM14EN                 RCC_MP_APB1ENCLRR_TIM14EN_Msk                      /*!< TIM14 peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_LPTIM1EN_Pos            (9U)
#define RCC_MP_APB1ENCLRR_LPTIM1EN_Msk            (0x1U << RCC_MP_APB1ENCLRR_LPTIM1EN_Pos)           /*!< 0x00000200 */
#define RCC_MP_APB1ENCLRR_LPTIM1EN                RCC_MP_APB1ENCLRR_LPTIM1EN_Msk                     /*!< LPTIM1 peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_SPI2EN_Pos              (11U)
#define RCC_MP_APB1ENCLRR_SPI2EN_Msk              (0x1U << RCC_MP_APB1ENCLRR_SPI2EN_Pos)             /*!< 0x00000800 */
#define RCC_MP_APB1ENCLRR_SPI2EN                  RCC_MP_APB1ENCLRR_SPI2EN_Msk                       /*!< SPI2 peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_SPI3EN_Pos              (12U)
#define RCC_MP_APB1ENCLRR_SPI3EN_Msk              (0x1U << RCC_MP_APB1ENCLRR_SPI3EN_Pos)             /*!< 0x00001000 */
#define RCC_MP_APB1ENCLRR_SPI3EN                  RCC_MP_APB1ENCLRR_SPI3EN_Msk                       /*!< SPI3 peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_USART2EN_Pos            (14U)
#define RCC_MP_APB1ENCLRR_USART2EN_Msk            (0x1U << RCC_MP_APB1ENCLRR_USART2EN_Pos)           /*!< 0x00004000 */
#define RCC_MP_APB1ENCLRR_USART2EN                RCC_MP_APB1ENCLRR_USART2EN_Msk                     /*!< USART2 peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_USART3EN_Pos            (15U)
#define RCC_MP_APB1ENCLRR_USART3EN_Msk            (0x1U << RCC_MP_APB1ENCLRR_USART3EN_Pos)           /*!< 0x00008000 */
#define RCC_MP_APB1ENCLRR_USART3EN                RCC_MP_APB1ENCLRR_USART3EN_Msk                     /*!< USART3 peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_UART4EN_Pos             (16U)
#define RCC_MP_APB1ENCLRR_UART4EN_Msk             (0x1U << RCC_MP_APB1ENCLRR_UART4EN_Pos)            /*!< 0x00010000 */
#define RCC_MP_APB1ENCLRR_UART4EN                 RCC_MP_APB1ENCLRR_UART4EN_Msk                      /*!< UART4 peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_UART5EN_Pos             (17U)
#define RCC_MP_APB1ENCLRR_UART5EN_Msk             (0x1U << RCC_MP_APB1ENCLRR_UART5EN_Pos)            /*!< 0x00020000 */
#define RCC_MP_APB1ENCLRR_UART5EN                 RCC_MP_APB1ENCLRR_UART5EN_Msk                      /*!< UART5 peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_UART7EN_Pos             (18U)
#define RCC_MP_APB1ENCLRR_UART7EN_Msk             (0x1U << RCC_MP_APB1ENCLRR_UART7EN_Pos)            /*!< 0x00040000 */
#define RCC_MP_APB1ENCLRR_UART7EN                 RCC_MP_APB1ENCLRR_UART7EN_Msk                      /*!< UART7 peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_UART8EN_Pos             (19U)
#define RCC_MP_APB1ENCLRR_UART8EN_Msk             (0x1U << RCC_MP_APB1ENCLRR_UART8EN_Pos)            /*!< 0x00080000 */
#define RCC_MP_APB1ENCLRR_UART8EN                 RCC_MP_APB1ENCLRR_UART8EN_Msk                      /*!< UART8 peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_I2C1EN_Pos              (21U)
#define RCC_MP_APB1ENCLRR_I2C1EN_Msk              (0x1U << RCC_MP_APB1ENCLRR_I2C1EN_Pos)             /*!< 0x00200000 */
#define RCC_MP_APB1ENCLRR_I2C1EN                  RCC_MP_APB1ENCLRR_I2C1EN_Msk                       /*!< I2C1 peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_I2C2EN_Pos              (22U)
#define RCC_MP_APB1ENCLRR_I2C2EN_Msk              (0x1U << RCC_MP_APB1ENCLRR_I2C2EN_Pos)             /*!< 0x00400000 */
#define RCC_MP_APB1ENCLRR_I2C2EN                  RCC_MP_APB1ENCLRR_I2C2EN_Msk                       /*!< I2C2 peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_I2C3EN_Pos              (23U)
#define RCC_MP_APB1ENCLRR_I2C3EN_Msk              (0x1U << RCC_MP_APB1ENCLRR_I2C3EN_Pos)             /*!< 0x00800000 */
#define RCC_MP_APB1ENCLRR_I2C3EN                  RCC_MP_APB1ENCLRR_I2C3EN_Msk                       /*!< I2C3 peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_I2C5EN_Pos              (24U)
#define RCC_MP_APB1ENCLRR_I2C5EN_Msk              (0x1U << RCC_MP_APB1ENCLRR_I2C5EN_Pos)             /*!< 0x01000000 */
#define RCC_MP_APB1ENCLRR_I2C5EN                  RCC_MP_APB1ENCLRR_I2C5EN_Msk                       /*!< I2C5 peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_SPDIFEN_Pos             (26U)
#define RCC_MP_APB1ENCLRR_SPDIFEN_Msk             (0x1U << RCC_MP_APB1ENCLRR_SPDIFEN_Pos)            /*!< 0x04000000 */
#define RCC_MP_APB1ENCLRR_SPDIFEN                 RCC_MP_APB1ENCLRR_SPDIFEN_Msk                      /*!< SPDIFRX peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_CECEN_Pos               (27U)
#define RCC_MP_APB1ENCLRR_CECEN_Msk               (0x1U << RCC_MP_APB1ENCLRR_CECEN_Pos)              /*!< 0x08000000 */
#define RCC_MP_APB1ENCLRR_CECEN                   RCC_MP_APB1ENCLRR_CECEN_Msk                        /*!< HDMI-CEC peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_DAC12EN_Pos             (29U)
#define RCC_MP_APB1ENCLRR_DAC12EN_Msk             (0x1U << RCC_MP_APB1ENCLRR_DAC12EN_Pos)            /*!< 0x20000000 */
#define RCC_MP_APB1ENCLRR_DAC12EN                 RCC_MP_APB1ENCLRR_DAC12EN_Msk                      /*!< DAC1&amp;2 peripheral clocks enable */
#define RCC_MP_APB1ENCLRR_MDIOSEN_Pos             (31U)
#define RCC_MP_APB1ENCLRR_MDIOSEN_Msk             (0x1U << RCC_MP_APB1ENCLRR_MDIOSEN_Pos)            /*!< 0x80000000 */
#define RCC_MP_APB1ENCLRR_MDIOSEN                 RCC_MP_APB1ENCLRR_MDIOSEN_Msk                      /*!< MDIOS peripheral clocks enable */

/**************  Bit definition for RCC_MP_APB2ENSETR register  ***************/
#define RCC_MP_APB2ENSETR_TIM1EN_Pos              (0U)
#define RCC_MP_APB2ENSETR_TIM1EN_Msk              (0x1U << RCC_MP_APB2ENSETR_TIM1EN_Pos)             /*!< 0x00000001 */
#define RCC_MP_APB2ENSETR_TIM1EN                  RCC_MP_APB2ENSETR_TIM1EN_Msk                       /*!< TIM1 peripheral clocks enable */
#define RCC_MP_APB2ENSETR_TIM8EN_Pos              (1U)
#define RCC_MP_APB2ENSETR_TIM8EN_Msk              (0x1U << RCC_MP_APB2ENSETR_TIM8EN_Pos)             /*!< 0x00000002 */
#define RCC_MP_APB2ENSETR_TIM8EN                  RCC_MP_APB2ENSETR_TIM8EN_Msk                       /*!< TIM8 peripheral clocks enable */
#define RCC_MP_APB2ENSETR_TIM15EN_Pos             (2U)
#define RCC_MP_APB2ENSETR_TIM15EN_Msk             (0x1U << RCC_MP_APB2ENSETR_TIM15EN_Pos)            /*!< 0x00000004 */
#define RCC_MP_APB2ENSETR_TIM15EN                 RCC_MP_APB2ENSETR_TIM15EN_Msk                      /*!< TIM15 peripheral clocks enable */
#define RCC_MP_APB2ENSETR_TIM16EN_Pos             (3U)
#define RCC_MP_APB2ENSETR_TIM16EN_Msk             (0x1U << RCC_MP_APB2ENSETR_TIM16EN_Pos)            /*!< 0x00000008 */
#define RCC_MP_APB2ENSETR_TIM16EN                 RCC_MP_APB2ENSETR_TIM16EN_Msk                      /*!< TIM16 peripheral clocks enable */
#define RCC_MP_APB2ENSETR_TIM17EN_Pos             (4U)
#define RCC_MP_APB2ENSETR_TIM17EN_Msk             (0x1U << RCC_MP_APB2ENSETR_TIM17EN_Pos)            /*!< 0x00000010 */
#define RCC_MP_APB2ENSETR_TIM17EN                 RCC_MP_APB2ENSETR_TIM17EN_Msk                      /*!< TIM17 peripheral clocks enable */
#define RCC_MP_APB2ENSETR_SPI1EN_Pos              (8U)
#define RCC_MP_APB2ENSETR_SPI1EN_Msk              (0x1U << RCC_MP_APB2ENSETR_SPI1EN_Pos)             /*!< 0x00000100 */
#define RCC_MP_APB2ENSETR_SPI1EN                  RCC_MP_APB2ENSETR_SPI1EN_Msk                       /*!< SPI/I2S1 peripheral clocks enable */
#define RCC_MP_APB2ENSETR_SPI4EN_Pos              (9U)
#define RCC_MP_APB2ENSETR_SPI4EN_Msk              (0x1U << RCC_MP_APB2ENSETR_SPI4EN_Pos)             /*!< 0x00000200 */
#define RCC_MP_APB2ENSETR_SPI4EN                  RCC_MP_APB2ENSETR_SPI4EN_Msk                       /*!< SPI4 peripheral clocks enable */
#define RCC_MP_APB2ENSETR_SPI5EN_Pos              (10U)
#define RCC_MP_APB2ENSETR_SPI5EN_Msk              (0x1U << RCC_MP_APB2ENSETR_SPI5EN_Pos)             /*!< 0x00000400 */
#define RCC_MP_APB2ENSETR_SPI5EN                  RCC_MP_APB2ENSETR_SPI5EN_Msk                       /*!< SPI5 peripheral clocks enable */
#define RCC_MP_APB2ENSETR_USART6EN_Pos            (13U)
#define RCC_MP_APB2ENSETR_USART6EN_Msk            (0x1U << RCC_MP_APB2ENSETR_USART6EN_Pos)           /*!< 0x00002000 */
#define RCC_MP_APB2ENSETR_USART6EN                RCC_MP_APB2ENSETR_USART6EN_Msk                     /*!< USART6 peripheral clocks enable */
#define RCC_MP_APB2ENSETR_SAI1EN_Pos              (16U)
#define RCC_MP_APB2ENSETR_SAI1EN_Msk              (0x1U << RCC_MP_APB2ENSETR_SAI1EN_Pos)             /*!< 0x00010000 */
#define RCC_MP_APB2ENSETR_SAI1EN                  RCC_MP_APB2ENSETR_SAI1EN_Msk                       /*!< SAI1 peripheral clocks enable */
#define RCC_MP_APB2ENSETR_SAI2EN_Pos              (17U)
#define RCC_MP_APB2ENSETR_SAI2EN_Msk              (0x1U << RCC_MP_APB2ENSETR_SAI2EN_Pos)             /*!< 0x00020000 */
#define RCC_MP_APB2ENSETR_SAI2EN                  RCC_MP_APB2ENSETR_SAI2EN_Msk                       /*!< SAI2 peripheral clocks enable */
#define RCC_MP_APB2ENSETR_SAI3EN_Pos              (18U)
#define RCC_MP_APB2ENSETR_SAI3EN_Msk              (0x1U << RCC_MP_APB2ENSETR_SAI3EN_Pos)             /*!< 0x00040000 */
#define RCC_MP_APB2ENSETR_SAI3EN                  RCC_MP_APB2ENSETR_SAI3EN_Msk                       /*!< SAI3 peripheral clocks enable */
#define RCC_MP_APB2ENSETR_DFSDMEN_Pos             (20U)
#define RCC_MP_APB2ENSETR_DFSDMEN_Msk             (0x1U << RCC_MP_APB2ENSETR_DFSDMEN_Pos)            /*!< 0x00100000 */
#define RCC_MP_APB2ENSETR_DFSDMEN                 RCC_MP_APB2ENSETR_DFSDMEN_Msk                      /*!< DFSDM peripheral clocks enable */
#define RCC_MP_APB2ENSETR_ADFSDMEN_Pos            (21U)
#define RCC_MP_APB2ENSETR_ADFSDMEN_Msk            (0x1U << RCC_MP_APB2ENSETR_ADFSDMEN_Pos)           /*!< 0x00200000 */
#define RCC_MP_APB2ENSETR_ADFSDMEN                RCC_MP_APB2ENSETR_ADFSDMEN_Msk                     /*!< Audio DFSDM peripheral clocks enable */
#define RCC_MP_APB2ENSETR_FDCANEN_Pos             (24U)
#define RCC_MP_APB2ENSETR_FDCANEN_Msk             (0x1U << RCC_MP_APB2ENSETR_FDCANEN_Pos)            /*!< 0x01000000 */
#define RCC_MP_APB2ENSETR_FDCANEN                 RCC_MP_APB2ENSETR_FDCANEN_Msk                      /*!< FDCAN and CANRAM peripheral clocks enable */

/**************  Bit definition for RCC_MP_APB2ENCLRR register  ***************/
#define RCC_MP_APB2ENCLRR_TIM1EN_Pos              (0U)
#define RCC_MP_APB2ENCLRR_TIM1EN_Msk              (0x1U << RCC_MP_APB2ENCLRR_TIM1EN_Pos)             /*!< 0x00000001 */
#define RCC_MP_APB2ENCLRR_TIM1EN                  RCC_MP_APB2ENCLRR_TIM1EN_Msk                       /*!< TIM1 peripheral clocks enable */
#define RCC_MP_APB2ENCLRR_TIM8EN_Pos              (1U)
#define RCC_MP_APB2ENCLRR_TIM8EN_Msk              (0x1U << RCC_MP_APB2ENCLRR_TIM8EN_Pos)             /*!< 0x00000002 */
#define RCC_MP_APB2ENCLRR_TIM8EN                  RCC_MP_APB2ENCLRR_TIM8EN_Msk                       /*!< TIM8 peripheral clocks enable */
#define RCC_MP_APB2ENCLRR_TIM15EN_Pos             (2U)
#define RCC_MP_APB2ENCLRR_TIM15EN_Msk             (0x1U << RCC_MP_APB2ENCLRR_TIM15EN_Pos)            /*!< 0x00000004 */
#define RCC_MP_APB2ENCLRR_TIM15EN                 RCC_MP_APB2ENCLRR_TIM15EN_Msk                      /*!< TIM15 peripheral clocks enable */
#define RCC_MP_APB2ENCLRR_TIM16EN_Pos             (3U)
#define RCC_MP_APB2ENCLRR_TIM16EN_Msk             (0x1U << RCC_MP_APB2ENCLRR_TIM16EN_Pos)            /*!< 0x00000008 */
#define RCC_MP_APB2ENCLRR_TIM16EN                 RCC_MP_APB2ENCLRR_TIM16EN_Msk                      /*!< TIM16 peripheral clocks enable */
#define RCC_MP_APB2ENCLRR_TIM17EN_Pos             (4U)
#define RCC_MP_APB2ENCLRR_TIM17EN_Msk             (0x1U << RCC_MP_APB2ENCLRR_TIM17EN_Pos)            /*!< 0x00000010 */
#define RCC_MP_APB2ENCLRR_TIM17EN                 RCC_MP_APB2ENCLRR_TIM17EN_Msk                      /*!< TIM17 peripheral clocks enable */
#define RCC_MP_APB2ENCLRR_SPI1EN_Pos              (8U)
#define RCC_MP_APB2ENCLRR_SPI1EN_Msk              (0x1U << RCC_MP_APB2ENCLRR_SPI1EN_Pos)             /*!< 0x00000100 */
#define RCC_MP_APB2ENCLRR_SPI1EN                  RCC_MP_APB2ENCLRR_SPI1EN_Msk                       /*!< SPI/I2S1 peripheral clocks enable */
#define RCC_MP_APB2ENCLRR_SPI4EN_Pos              (9U)
#define RCC_MP_APB2ENCLRR_SPI4EN_Msk              (0x1U << RCC_MP_APB2ENCLRR_SPI4EN_Pos)             /*!< 0x00000200 */
#define RCC_MP_APB2ENCLRR_SPI4EN                  RCC_MP_APB2ENCLRR_SPI4EN_Msk                       /*!< SPI4 peripheral clocks enable */
#define RCC_MP_APB2ENCLRR_SPI5EN_Pos              (10U)
#define RCC_MP_APB2ENCLRR_SPI5EN_Msk              (0x1U << RCC_MP_APB2ENCLRR_SPI5EN_Pos)             /*!< 0x00000400 */
#define RCC_MP_APB2ENCLRR_SPI5EN                  RCC_MP_APB2ENCLRR_SPI5EN_Msk                       /*!< SPI5 peripheral clocks enable */
#define RCC_MP_APB2ENCLRR_USART6EN_Pos            (13U)
#define RCC_MP_APB2ENCLRR_USART6EN_Msk            (0x1U << RCC_MP_APB2ENCLRR_USART6EN_Pos)           /*!< 0x00002000 */
#define RCC_MP_APB2ENCLRR_USART6EN                RCC_MP_APB2ENCLRR_USART6EN_Msk                     /*!< USART6 peripheral clocks enable */
#define RCC_MP_APB2ENCLRR_SAI1EN_Pos              (16U)
#define RCC_MP_APB2ENCLRR_SAI1EN_Msk              (0x1U << RCC_MP_APB2ENCLRR_SAI1EN_Pos)             /*!< 0x00010000 */
#define RCC_MP_APB2ENCLRR_SAI1EN                  RCC_MP_APB2ENCLRR_SAI1EN_Msk                       /*!< SAI1 peripheral clocks enable */
#define RCC_MP_APB2ENCLRR_SAI2EN_Pos              (17U)
#define RCC_MP_APB2ENCLRR_SAI2EN_Msk              (0x1U << RCC_MP_APB2ENCLRR_SAI2EN_Pos)             /*!< 0x00020000 */
#define RCC_MP_APB2ENCLRR_SAI2EN                  RCC_MP_APB2ENCLRR_SAI2EN_Msk                       /*!< SAI2 peripheral clocks enable */
#define RCC_MP_APB2ENCLRR_SAI3EN_Pos              (18U)
#define RCC_MP_APB2ENCLRR_SAI3EN_Msk              (0x1U << RCC_MP_APB2ENCLRR_SAI3EN_Pos)             /*!< 0x00040000 */
#define RCC_MP_APB2ENCLRR_SAI3EN                  RCC_MP_APB2ENCLRR_SAI3EN_Msk                       /*!< SAI3 peripheral clocks enable */
#define RCC_MP_APB2ENCLRR_DFSDMEN_Pos             (20U)
#define RCC_MP_APB2ENCLRR_DFSDMEN_Msk             (0x1U << RCC_MP_APB2ENCLRR_DFSDMEN_Pos)            /*!< 0x00100000 */
#define RCC_MP_APB2ENCLRR_DFSDMEN                 RCC_MP_APB2ENCLRR_DFSDMEN_Msk                      /*!< DFSDM peripheral clocks enable */
#define RCC_MP_APB2ENCLRR_ADFSDMEN_Pos            (21U)
#define RCC_MP_APB2ENCLRR_ADFSDMEN_Msk            (0x1U << RCC_MP_APB2ENCLRR_ADFSDMEN_Pos)           /*!< 0x00200000 */
#define RCC_MP_APB2ENCLRR_ADFSDMEN                RCC_MP_APB2ENCLRR_ADFSDMEN_Msk                     /*!< Audio DFSDM peripheral clocks enable */
#define RCC_MP_APB2ENCLRR_FDCANEN_Pos             (24U)
#define RCC_MP_APB2ENCLRR_FDCANEN_Msk             (0x1U << RCC_MP_APB2ENCLRR_FDCANEN_Pos)            /*!< 0x01000000 */
#define RCC_MP_APB2ENCLRR_FDCANEN                 RCC_MP_APB2ENCLRR_FDCANEN_Msk                      /*!< FDCAN and CANRAM peripheral clocks enable */

/**************  Bit definition for RCC_MP_APB3ENSETR register  ***************/
#define RCC_MP_APB3ENSETR_LPTIM2EN_Pos            (0U)
#define RCC_MP_APB3ENSETR_LPTIM2EN_Msk            (0x1U << RCC_MP_APB3ENSETR_LPTIM2EN_Pos)           /*!< 0x00000001 */
#define RCC_MP_APB3ENSETR_LPTIM2EN                RCC_MP_APB3ENSETR_LPTIM2EN_Msk                     /*!< LPTIM2 peripheral clocks enable */
#define RCC_MP_APB3ENSETR_LPTIM3EN_Pos            (1U)
#define RCC_MP_APB3ENSETR_LPTIM3EN_Msk            (0x1U << RCC_MP_APB3ENSETR_LPTIM3EN_Pos)           /*!< 0x00000002 */
#define RCC_MP_APB3ENSETR_LPTIM3EN                RCC_MP_APB3ENSETR_LPTIM3EN_Msk                     /*!< LPTIM3 peripheral clocks enable */
#define RCC_MP_APB3ENSETR_LPTIM4EN_Pos            (2U)
#define RCC_MP_APB3ENSETR_LPTIM4EN_Msk            (0x1U << RCC_MP_APB3ENSETR_LPTIM4EN_Pos)           /*!< 0x00000004 */
#define RCC_MP_APB3ENSETR_LPTIM4EN                RCC_MP_APB3ENSETR_LPTIM4EN_Msk                     /*!< LPTIM4 peripheral clocks enable */
#define RCC_MP_APB3ENSETR_LPTIM5EN_Pos            (3U)
#define RCC_MP_APB3ENSETR_LPTIM5EN_Msk            (0x1U << RCC_MP_APB3ENSETR_LPTIM5EN_Pos)           /*!< 0x00000008 */
#define RCC_MP_APB3ENSETR_LPTIM5EN                RCC_MP_APB3ENSETR_LPTIM5EN_Msk                     /*!< LPTIM5 peripheral clocks enable */
#define RCC_MP_APB3ENSETR_SAI4EN_Pos              (8U)
#define RCC_MP_APB3ENSETR_SAI4EN_Msk              (0x1U << RCC_MP_APB3ENSETR_SAI4EN_Pos)             /*!< 0x00000100 */
#define RCC_MP_APB3ENSETR_SAI4EN                  RCC_MP_APB3ENSETR_SAI4EN_Msk                       /*!< SAI4 peripheral clocks enable */
#define RCC_MP_APB3ENSETR_SYSCFGEN_Pos            (11U)
#define RCC_MP_APB3ENSETR_SYSCFGEN_Msk            (0x1U << RCC_MP_APB3ENSETR_SYSCFGEN_Pos)           /*!< 0x00000800 */
#define RCC_MP_APB3ENSETR_SYSCFGEN                RCC_MP_APB3ENSETR_SYSCFGEN_Msk                     /*!< SYSCFG peripheral clocks enable */
#define RCC_MP_APB3ENSETR_VREFEN_Pos              (13U)
#define RCC_MP_APB3ENSETR_VREFEN_Msk              (0x1U << RCC_MP_APB3ENSETR_VREFEN_Pos)             /*!< 0x00002000 */
#define RCC_MP_APB3ENSETR_VREFEN                  RCC_MP_APB3ENSETR_VREFEN_Msk                       /*!< VREF peripheral clocks enable */
#define RCC_MP_APB3ENSETR_DTSEN_Pos               (16U)
#define RCC_MP_APB3ENSETR_DTSEN_Msk               (0x1U << RCC_MP_APB3ENSETR_DTSEN_Pos)              /*!< 0x00010000 */
#define RCC_MP_APB3ENSETR_DTSEN                   RCC_MP_APB3ENSETR_DTSEN_Msk                        /*!< DTS peripheral clocks enable */
#define RCC_MP_APB3ENSETR_HDPEN_Pos               (20U)
#define RCC_MP_APB3ENSETR_HDPEN_Msk               (0x1U << RCC_MP_APB3ENSETR_HDPEN_Pos)              /*!< 0x00100000 */
#define RCC_MP_APB3ENSETR_HDPEN                   RCC_MP_APB3ENSETR_HDPEN_Msk                        /*!< HDP peripheral clocks enable */

/**************  Bit definition for RCC_MP_APB3ENCLRR register  ***************/
#define RCC_MP_APB3ENCLRR_LPTIM2EN_Pos            (0U)
#define RCC_MP_APB3ENCLRR_LPTIM2EN_Msk            (0x1U << RCC_MP_APB3ENCLRR_LPTIM2EN_Pos)           /*!< 0x00000001 */
#define RCC_MP_APB3ENCLRR_LPTIM2EN                RCC_MP_APB3ENCLRR_LPTIM2EN_Msk                     /*!< LPTIM2 peripheral clocks enable */
#define RCC_MP_APB3ENCLRR_LPTIM3EN_Pos            (1U)
#define RCC_MP_APB3ENCLRR_LPTIM3EN_Msk            (0x1U << RCC_MP_APB3ENCLRR_LPTIM3EN_Pos)           /*!< 0x00000002 */
#define RCC_MP_APB3ENCLRR_LPTIM3EN                RCC_MP_APB3ENCLRR_LPTIM3EN_Msk                     /*!< LPTIM3 peripheral clocks enable */
#define RCC_MP_APB3ENCLRR_LPTIM4EN_Pos            (2U)
#define RCC_MP_APB3ENCLRR_LPTIM4EN_Msk            (0x1U << RCC_MP_APB3ENCLRR_LPTIM4EN_Pos)           /*!< 0x00000004 */
#define RCC_MP_APB3ENCLRR_LPTIM4EN                RCC_MP_APB3ENCLRR_LPTIM4EN_Msk                     /*!< LPTIM4 peripheral clocks enable */
#define RCC_MP_APB3ENCLRR_LPTIM5EN_Pos            (3U)
#define RCC_MP_APB3ENCLRR_LPTIM5EN_Msk            (0x1U << RCC_MP_APB3ENCLRR_LPTIM5EN_Pos)           /*!< 0x00000008 */
#define RCC_MP_APB3ENCLRR_LPTIM5EN                RCC_MP_APB3ENCLRR_LPTIM5EN_Msk                     /*!< LPTIM5 peripheral clocks enable */
#define RCC_MP_APB3ENCLRR_SAI4EN_Pos              (8U)
#define RCC_MP_APB3ENCLRR_SAI4EN_Msk              (0x1U << RCC_MP_APB3ENCLRR_SAI4EN_Pos)             /*!< 0x00000100 */
#define RCC_MP_APB3ENCLRR_SAI4EN                  RCC_MP_APB3ENCLRR_SAI4EN_Msk                       /*!< SAI4 peripheral clocks enable */
#define RCC_MP_APB3ENCLRR_SYSCFGEN_Pos            (11U)
#define RCC_MP_APB3ENCLRR_SYSCFGEN_Msk            (0x1U << RCC_MP_APB3ENCLRR_SYSCFGEN_Pos)           /*!< 0x00000800 */
#define RCC_MP_APB3ENCLRR_SYSCFGEN                RCC_MP_APB3ENCLRR_SYSCFGEN_Msk                     /*!< SYSCFG peripheral clocks enable */
#define RCC_MP_APB3ENCLRR_VREFEN_Pos              (13U)
#define RCC_MP_APB3ENCLRR_VREFEN_Msk              (0x1U << RCC_MP_APB3ENCLRR_VREFEN_Pos)             /*!< 0x00002000 */
#define RCC_MP_APB3ENCLRR_VREFEN                  RCC_MP_APB3ENCLRR_VREFEN_Msk                       /*!< VREF peripheral clocks enable */
#define RCC_MP_APB3ENCLRR_DTSEN_Pos               (16U)
#define RCC_MP_APB3ENCLRR_DTSEN_Msk               (0x1U << RCC_MP_APB3ENCLRR_DTSEN_Pos)              /*!< 0x00010000 */
#define RCC_MP_APB3ENCLRR_DTSEN                   RCC_MP_APB3ENCLRR_DTSEN_Msk                        /*!< DTS peripheral clocks enable */
#define RCC_MP_APB3ENCLRR_HDPEN_Pos               (20U)
#define RCC_MP_APB3ENCLRR_HDPEN_Msk               (0x1U << RCC_MP_APB3ENCLRR_HDPEN_Pos)              /*!< 0x00100000 */
#define RCC_MP_APB3ENCLRR_HDPEN                   RCC_MP_APB3ENCLRR_HDPEN_Msk                        /*!< HDP peripheral clocks enable */

/**************  Bit definition for RCC_MP_AHB2ENSETR register  ***************/
#define RCC_MP_AHB2ENSETR_DMA1EN_Pos              (0U)
#define RCC_MP_AHB2ENSETR_DMA1EN_Msk              (0x1U << RCC_MP_AHB2ENSETR_DMA1EN_Pos)             /*!< 0x00000001 */
#define RCC_MP_AHB2ENSETR_DMA1EN                  RCC_MP_AHB2ENSETR_DMA1EN_Msk                       /*!< DMA1 peripheral clocks enable */
#define RCC_MP_AHB2ENSETR_DMA2EN_Pos              (1U)
#define RCC_MP_AHB2ENSETR_DMA2EN_Msk              (0x1U << RCC_MP_AHB2ENSETR_DMA2EN_Pos)             /*!< 0x00000002 */
#define RCC_MP_AHB2ENSETR_DMA2EN                  RCC_MP_AHB2ENSETR_DMA2EN_Msk                       /*!< DMA2 peripheral clocks enable */
#define RCC_MP_AHB2ENSETR_DMAMUXEN_Pos            (2U)
#define RCC_MP_AHB2ENSETR_DMAMUXEN_Msk            (0x1U << RCC_MP_AHB2ENSETR_DMAMUXEN_Pos)           /*!< 0x00000004 */
#define RCC_MP_AHB2ENSETR_DMAMUXEN                RCC_MP_AHB2ENSETR_DMAMUXEN_Msk                     /*!< DMAMUX peripheral clocks enable */
#define RCC_MP_AHB2ENSETR_ADC12EN_Pos             (5U)
#define RCC_MP_AHB2ENSETR_ADC12EN_Msk             (0x1U << RCC_MP_AHB2ENSETR_ADC12EN_Pos)            /*!< 0x00000020 */
#define RCC_MP_AHB2ENSETR_ADC12EN                 RCC_MP_AHB2ENSETR_ADC12EN_Msk                      /*!< ADC1&amp;2 peripheral clocks enable */
#define RCC_MP_AHB2ENSETR_USBOEN_Pos              (8U)
#define RCC_MP_AHB2ENSETR_USBOEN_Msk              (0x1U << RCC_MP_AHB2ENSETR_USBOEN_Pos)             /*!< 0x00000100 */
#define RCC_MP_AHB2ENSETR_USBOEN                  RCC_MP_AHB2ENSETR_USBOEN_Msk                       /*!< USBO peripheral clocks enable */
#define RCC_MP_AHB2ENSETR_SDMMC3EN_Pos            (16U)
#define RCC_MP_AHB2ENSETR_SDMMC3EN_Msk            (0x1U << RCC_MP_AHB2ENSETR_SDMMC3EN_Pos)           /*!< 0x00010000 */
#define RCC_MP_AHB2ENSETR_SDMMC3EN                RCC_MP_AHB2ENSETR_SDMMC3EN_Msk                     /*!< SDMMC3 and SDMMC3 delay (DLYBSD3) block peripheral clocks enable */

/**************  Bit definition for RCC_MP_AHB2ENCLRR register  ***************/
#define RCC_MP_AHB2ENCLRR_DMA1EN_Pos              (0U)
#define RCC_MP_AHB2ENCLRR_DMA1EN_Msk              (0x1U << RCC_MP_AHB2ENCLRR_DMA1EN_Pos)             /*!< 0x00000001 */
#define RCC_MP_AHB2ENCLRR_DMA1EN                  RCC_MP_AHB2ENCLRR_DMA1EN_Msk                       /*!< DMA1 peripheral clocks enable */
#define RCC_MP_AHB2ENCLRR_DMA2EN_Pos              (1U)
#define RCC_MP_AHB2ENCLRR_DMA2EN_Msk              (0x1U << RCC_MP_AHB2ENCLRR_DMA2EN_Pos)             /*!< 0x00000002 */
#define RCC_MP_AHB2ENCLRR_DMA2EN                  RCC_MP_AHB2ENCLRR_DMA2EN_Msk                       /*!< DMA2 peripheral clocks enable */
#define RCC_MP_AHB2ENCLRR_DMAMUXEN_Pos            (2U)
#define RCC_MP_AHB2ENCLRR_DMAMUXEN_Msk            (0x1U << RCC_MP_AHB2ENCLRR_DMAMUXEN_Pos)           /*!< 0x00000004 */
#define RCC_MP_AHB2ENCLRR_DMAMUXEN                RCC_MP_AHB2ENCLRR_DMAMUXEN_Msk                     /*!< DMAMUX peripheral clocks enable */
#define RCC_MP_AHB2ENCLRR_ADC12EN_Pos             (5U)
#define RCC_MP_AHB2ENCLRR_ADC12EN_Msk             (0x1U << RCC_MP_AHB2ENCLRR_ADC12EN_Pos)            /*!< 0x00000020 */
#define RCC_MP_AHB2ENCLRR_ADC12EN                 RCC_MP_AHB2ENCLRR_ADC12EN_Msk                      /*!< ADC1&amp;2 peripheral clocks enable */
#define RCC_MP_AHB2ENCLRR_USBOEN_Pos              (8U)
#define RCC_MP_AHB2ENCLRR_USBOEN_Msk              (0x1U << RCC_MP_AHB2ENCLRR_USBOEN_Pos)             /*!< 0x00000100 */
#define RCC_MP_AHB2ENCLRR_USBOEN                  RCC_MP_AHB2ENCLRR_USBOEN_Msk                       /*!< USBO peripheral clocks enable */
#define RCC_MP_AHB2ENCLRR_SDMMC3EN_Pos            (16U)
#define RCC_MP_AHB2ENCLRR_SDMMC3EN_Msk            (0x1U << RCC_MP_AHB2ENCLRR_SDMMC3EN_Pos)           /*!< 0x00010000 */
#define RCC_MP_AHB2ENCLRR_SDMMC3EN                RCC_MP_AHB2ENCLRR_SDMMC3EN_Msk                     /*!< SDMMC3 and SDMMC3 delay (DLYBSD3) block peripheral clocks enable */

/**************  Bit definition for RCC_MP_AHB3ENSETR register  ***************/
#define RCC_MP_AHB3ENSETR_DCMIEN_Pos              (0U)
#define RCC_MP_AHB3ENSETR_DCMIEN_Msk              (0x1U << RCC_MP_AHB3ENSETR_DCMIEN_Pos)             /*!< 0x00000001 */
#define RCC_MP_AHB3ENSETR_DCMIEN                  RCC_MP_AHB3ENSETR_DCMIEN_Msk                       /*!< DCMI peripheral clocks enable */
#define RCC_MP_AHB3ENSETR_CRYP2EN_Pos             (4U)
#define RCC_MP_AHB3ENSETR_CRYP2EN_Msk             (0x1U << RCC_MP_AHB3ENSETR_CRYP2EN_Pos)            /*!< 0x00000010 */
#define RCC_MP_AHB3ENSETR_CRYP2EN                 RCC_MP_AHB3ENSETR_CRYP2EN_Msk                      /*!< CRYP2 (3DES/AES2) peripheral clocks enable */
#define RCC_MP_AHB3ENSETR_HASH2EN_Pos             (5U)
#define RCC_MP_AHB3ENSETR_HASH2EN_Msk             (0x1U << RCC_MP_AHB3ENSETR_HASH2EN_Pos)            /*!< 0x00000020 */
#define RCC_MP_AHB3ENSETR_HASH2EN                 RCC_MP_AHB3ENSETR_HASH2EN_Msk                      /*!< HASH2 peripheral clocks enable */
#define RCC_MP_AHB3ENSETR_RNG2EN_Pos              (6U)
#define RCC_MP_AHB3ENSETR_RNG2EN_Msk              (0x1U << RCC_MP_AHB3ENSETR_RNG2EN_Pos)             /*!< 0x00000040 */
#define RCC_MP_AHB3ENSETR_RNG2EN                  RCC_MP_AHB3ENSETR_RNG2EN_Msk                       /*!< RNG2 peripheral clocks enable */
#define RCC_MP_AHB3ENSETR_CRC2EN_Pos              (7U)
#define RCC_MP_AHB3ENSETR_CRC2EN_Msk              (0x1U << RCC_MP_AHB3ENSETR_CRC2EN_Pos)             /*!< 0x00000080 */
#define RCC_MP_AHB3ENSETR_CRC2EN                  RCC_MP_AHB3ENSETR_CRC2EN_Msk                       /*!< CRC2 peripheral clocks enable */
#define RCC_MP_AHB3ENSETR_HSEMEN_Pos              (11U)
#define RCC_MP_AHB3ENSETR_HSEMEN_Msk              (0x1U << RCC_MP_AHB3ENSETR_HSEMEN_Pos)             /*!< 0x00000800 */
#define RCC_MP_AHB3ENSETR_HSEMEN                  RCC_MP_AHB3ENSETR_HSEMEN_Msk                       /*!< HSEM peripheral clocks enable */
#define RCC_MP_AHB3ENSETR_IPCCEN_Pos              (12U)
#define RCC_MP_AHB3ENSETR_IPCCEN_Msk              (0x1U << RCC_MP_AHB3ENSETR_IPCCEN_Pos)             /*!< 0x00001000 */
#define RCC_MP_AHB3ENSETR_IPCCEN                  RCC_MP_AHB3ENSETR_IPCCEN_Msk                       /*!< IPCC peripheral clocks enable */

/**************  Bit definition for RCC_MP_AHB3ENCLRR register  ***************/
#define RCC_MP_AHB3ENCLRR_DCMIEN_Pos              (0U)
#define RCC_MP_AHB3ENCLRR_DCMIEN_Msk              (0x1U << RCC_MP_AHB3ENCLRR_DCMIEN_Pos)             /*!< 0x00000001 */
#define RCC_MP_AHB3ENCLRR_DCMIEN                  RCC_MP_AHB3ENCLRR_DCMIEN_Msk                       /*!< DCMI peripheral clocks enable */
#define RCC_MP_AHB3ENCLRR_CRYP2EN_Pos             (4U)
#define RCC_MP_AHB3ENCLRR_CRYP2EN_Msk             (0x1U << RCC_MP_AHB3ENCLRR_CRYP2EN_Pos)            /*!< 0x00000010 */
#define RCC_MP_AHB3ENCLRR_CRYP2EN                 RCC_MP_AHB3ENCLRR_CRYP2EN_Msk                      /*!< CRYP2 (3DES/AES2) peripheral clocks enable */
#define RCC_MP_AHB3ENCLRR_HASH2EN_Pos             (5U)
#define RCC_MP_AHB3ENCLRR_HASH2EN_Msk             (0x1U << RCC_MP_AHB3ENCLRR_HASH2EN_Pos)            /*!< 0x00000020 */
#define RCC_MP_AHB3ENCLRR_HASH2EN                 RCC_MP_AHB3ENCLRR_HASH2EN_Msk                      /*!< HASH2 peripheral clocks enable */
#define RCC_MP_AHB3ENCLRR_RNG2EN_Pos              (6U)
#define RCC_MP_AHB3ENCLRR_RNG2EN_Msk              (0x1U << RCC_MP_AHB3ENCLRR_RNG2EN_Pos)             /*!< 0x00000040 */
#define RCC_MP_AHB3ENCLRR_RNG2EN                  RCC_MP_AHB3ENCLRR_RNG2EN_Msk                       /*!< RNG2 peripheral clocks enable */
#define RCC_MP_AHB3ENCLRR_CRC2EN_Pos              (7U)
#define RCC_MP_AHB3ENCLRR_CRC2EN_Msk              (0x1U << RCC_MP_AHB3ENCLRR_CRC2EN_Pos)             /*!< 0x00000080 */
#define RCC_MP_AHB3ENCLRR_CRC2EN                  RCC_MP_AHB3ENCLRR_CRC2EN_Msk                       /*!< CRC2 peripheral clocks enable */
#define RCC_MP_AHB3ENCLRR_HSEMEN_Pos              (11U)
#define RCC_MP_AHB3ENCLRR_HSEMEN_Msk              (0x1U << RCC_MP_AHB3ENCLRR_HSEMEN_Pos)             /*!< 0x00000800 */
#define RCC_MP_AHB3ENCLRR_HSEMEN                  RCC_MP_AHB3ENCLRR_HSEMEN_Msk                       /*!< HSEM peripheral clocks enable */
#define RCC_MP_AHB3ENCLRR_IPCCEN_Pos              (12U)
#define RCC_MP_AHB3ENCLRR_IPCCEN_Msk              (0x1U << RCC_MP_AHB3ENCLRR_IPCCEN_Pos)             /*!< 0x00001000 */
#define RCC_MP_AHB3ENCLRR_IPCCEN                  RCC_MP_AHB3ENCLRR_IPCCEN_Msk                       /*!< IPCC peripheral clocks enable */

/**************  Bit definition for RCC_MP_AHB4ENSETR register  ***************/
#define RCC_MP_AHB4ENSETR_GPIOAEN_Pos             (0U)
#define RCC_MP_AHB4ENSETR_GPIOAEN_Msk             (0x1U << RCC_MP_AHB4ENSETR_GPIOAEN_Pos)            /*!< 0x00000001 */
#define RCC_MP_AHB4ENSETR_GPIOAEN                 RCC_MP_AHB4ENSETR_GPIOAEN_Msk                      /*!< GPIOA peripheral clocks enable */
#define RCC_MP_AHB4ENSETR_GPIOBEN_Pos             (1U)
#define RCC_MP_AHB4ENSETR_GPIOBEN_Msk             (0x1U << RCC_MP_AHB4ENSETR_GPIOBEN_Pos)            /*!< 0x00000002 */
#define RCC_MP_AHB4ENSETR_GPIOBEN                 RCC_MP_AHB4ENSETR_GPIOBEN_Msk                      /*!< GPIOB peripheral clocks enable */
#define RCC_MP_AHB4ENSETR_GPIOCEN_Pos             (2U)
#define RCC_MP_AHB4ENSETR_GPIOCEN_Msk             (0x1U << RCC_MP_AHB4ENSETR_GPIOCEN_Pos)            /*!< 0x00000004 */
#define RCC_MP_AHB4ENSETR_GPIOCEN                 RCC_MP_AHB4ENSETR_GPIOCEN_Msk                      /*!< GPIOC peripheral clocks enable */
#define RCC_MP_AHB4ENSETR_GPIODEN_Pos             (3U)
#define RCC_MP_AHB4ENSETR_GPIODEN_Msk             (0x1U << RCC_MP_AHB4ENSETR_GPIODEN_Pos)            /*!< 0x00000008 */
#define RCC_MP_AHB4ENSETR_GPIODEN                 RCC_MP_AHB4ENSETR_GPIODEN_Msk                      /*!< GPIOD peripheral clocks enable */
#define RCC_MP_AHB4ENSETR_GPIOEEN_Pos             (4U)
#define RCC_MP_AHB4ENSETR_GPIOEEN_Msk             (0x1U << RCC_MP_AHB4ENSETR_GPIOEEN_Pos)            /*!< 0x00000010 */
#define RCC_MP_AHB4ENSETR_GPIOEEN                 RCC_MP_AHB4ENSETR_GPIOEEN_Msk                      /*!< GPIOE peripheral clocks enable */
#define RCC_MP_AHB4ENSETR_GPIOFEN_Pos             (5U)
#define RCC_MP_AHB4ENSETR_GPIOFEN_Msk             (0x1U << RCC_MP_AHB4ENSETR_GPIOFEN_Pos)            /*!< 0x00000020 */
#define RCC_MP_AHB4ENSETR_GPIOFEN                 RCC_MP_AHB4ENSETR_GPIOFEN_Msk                      /*!< GPIOF peripheral clocks enable */
#define RCC_MP_AHB4ENSETR_GPIOGEN_Pos             (6U)
#define RCC_MP_AHB4ENSETR_GPIOGEN_Msk             (0x1U << RCC_MP_AHB4ENSETR_GPIOGEN_Pos)            /*!< 0x00000040 */
#define RCC_MP_AHB4ENSETR_GPIOGEN                 RCC_MP_AHB4ENSETR_GPIOGEN_Msk                      /*!< GPIOG peripheral clocks enable */
#define RCC_MP_AHB4ENSETR_GPIOHEN_Pos             (7U)
#define RCC_MP_AHB4ENSETR_GPIOHEN_Msk             (0x1U << RCC_MP_AHB4ENSETR_GPIOHEN_Pos)            /*!< 0x00000080 */
#define RCC_MP_AHB4ENSETR_GPIOHEN                 RCC_MP_AHB4ENSETR_GPIOHEN_Msk                      /*!< GPIOH peripheral clocks enable */
#define RCC_MP_AHB4ENSETR_GPIOIEN_Pos             (8U)
#define RCC_MP_AHB4ENSETR_GPIOIEN_Msk             (0x1U << RCC_MP_AHB4ENSETR_GPIOIEN_Pos)            /*!< 0x00000100 */
#define RCC_MP_AHB4ENSETR_GPIOIEN                 RCC_MP_AHB4ENSETR_GPIOIEN_Msk                      /*!< GPIOI peripheral clocks enable */
#define RCC_MP_AHB4ENSETR_GPIOJEN_Pos             (9U)
#define RCC_MP_AHB4ENSETR_GPIOJEN_Msk             (0x1U << RCC_MP_AHB4ENSETR_GPIOJEN_Pos)            /*!< 0x00000200 */
#define RCC_MP_AHB4ENSETR_GPIOJEN                 RCC_MP_AHB4ENSETR_GPIOJEN_Msk                      /*!< GPIOJ peripheral clocks enable */
#define RCC_MP_AHB4ENSETR_GPIOKEN_Pos             (10U)
#define RCC_MP_AHB4ENSETR_GPIOKEN_Msk             (0x1U << RCC_MP_AHB4ENSETR_GPIOKEN_Pos)            /*!< 0x00000400 */
#define RCC_MP_AHB4ENSETR_GPIOKEN                 RCC_MP_AHB4ENSETR_GPIOKEN_Msk                      /*!< GPIOK peripheral clocks enable */

/**************  Bit definition for RCC_MP_AHB4ENCLRR register  ***************/
#define RCC_MP_AHB4ENCLRR_GPIOAEN_Pos             (0U)
#define RCC_MP_AHB4ENCLRR_GPIOAEN_Msk             (0x1U << RCC_MP_AHB4ENCLRR_GPIOAEN_Pos)            /*!< 0x00000001 */
#define RCC_MP_AHB4ENCLRR_GPIOAEN                 RCC_MP_AHB4ENCLRR_GPIOAEN_Msk                      /*!< GPIOA peripheral clocks enable */
#define RCC_MP_AHB4ENCLRR_GPIOBEN_Pos             (1U)
#define RCC_MP_AHB4ENCLRR_GPIOBEN_Msk             (0x1U << RCC_MP_AHB4ENCLRR_GPIOBEN_Pos)            /*!< 0x00000002 */
#define RCC_MP_AHB4ENCLRR_GPIOBEN                 RCC_MP_AHB4ENCLRR_GPIOBEN_Msk                      /*!< GPIOB peripheral clocks enable */
#define RCC_MP_AHB4ENCLRR_GPIOCEN_Pos             (2U)
#define RCC_MP_AHB4ENCLRR_GPIOCEN_Msk             (0x1U << RCC_MP_AHB4ENCLRR_GPIOCEN_Pos)            /*!< 0x00000004 */
#define RCC_MP_AHB4ENCLRR_GPIOCEN                 RCC_MP_AHB4ENCLRR_GPIOCEN_Msk                      /*!< GPIOC peripheral clocks enable */
#define RCC_MP_AHB4ENCLRR_GPIODEN_Pos             (3U)
#define RCC_MP_AHB4ENCLRR_GPIODEN_Msk             (0x1U << RCC_MP_AHB4ENCLRR_GPIODEN_Pos)            /*!< 0x00000008 */
#define RCC_MP_AHB4ENCLRR_GPIODEN                 RCC_MP_AHB4ENCLRR_GPIODEN_Msk                      /*!< GPIOD peripheral clocks enable */
#define RCC_MP_AHB4ENCLRR_GPIOEEN_Pos             (4U)
#define RCC_MP_AHB4ENCLRR_GPIOEEN_Msk             (0x1U << RCC_MP_AHB4ENCLRR_GPIOEEN_Pos)            /*!< 0x00000010 */
#define RCC_MP_AHB4ENCLRR_GPIOEEN                 RCC_MP_AHB4ENCLRR_GPIOEEN_Msk                      /*!< GPIOE peripheral clocks enable */
#define RCC_MP_AHB4ENCLRR_GPIOFEN_Pos             (5U)
#define RCC_MP_AHB4ENCLRR_GPIOFEN_Msk             (0x1U << RCC_MP_AHB4ENCLRR_GPIOFEN_Pos)            /*!< 0x00000020 */
#define RCC_MP_AHB4ENCLRR_GPIOFEN                 RCC_MP_AHB4ENCLRR_GPIOFEN_Msk                      /*!< GPIOF peripheral clocks enable */
#define RCC_MP_AHB4ENCLRR_GPIOGEN_Pos             (6U)
#define RCC_MP_AHB4ENCLRR_GPIOGEN_Msk             (0x1U << RCC_MP_AHB4ENCLRR_GPIOGEN_Pos)            /*!< 0x00000040 */
#define RCC_MP_AHB4ENCLRR_GPIOGEN                 RCC_MP_AHB4ENCLRR_GPIOGEN_Msk                      /*!< GPIOG peripheral clocks enable */
#define RCC_MP_AHB4ENCLRR_GPIOHEN_Pos             (7U)
#define RCC_MP_AHB4ENCLRR_GPIOHEN_Msk             (0x1U << RCC_MP_AHB4ENCLRR_GPIOHEN_Pos)            /*!< 0x00000080 */
#define RCC_MP_AHB4ENCLRR_GPIOHEN                 RCC_MP_AHB4ENCLRR_GPIOHEN_Msk                      /*!< GPIOH peripheral clocks enable */
#define RCC_MP_AHB4ENCLRR_GPIOIEN_Pos             (8U)
#define RCC_MP_AHB4ENCLRR_GPIOIEN_Msk             (0x1U << RCC_MP_AHB4ENCLRR_GPIOIEN_Pos)            /*!< 0x00000100 */
#define RCC_MP_AHB4ENCLRR_GPIOIEN                 RCC_MP_AHB4ENCLRR_GPIOIEN_Msk                      /*!< GPIOI peripheral clocks enable */
#define RCC_MP_AHB4ENCLRR_GPIOJEN_Pos             (9U)
#define RCC_MP_AHB4ENCLRR_GPIOJEN_Msk             (0x1U << RCC_MP_AHB4ENCLRR_GPIOJEN_Pos)            /*!< 0x00000200 */
#define RCC_MP_AHB4ENCLRR_GPIOJEN                 RCC_MP_AHB4ENCLRR_GPIOJEN_Msk                      /*!< GPIOJ peripheral clocks enable */
#define RCC_MP_AHB4ENCLRR_GPIOKEN_Pos             (10U)
#define RCC_MP_AHB4ENCLRR_GPIOKEN_Msk             (0x1U << RCC_MP_AHB4ENCLRR_GPIOKEN_Pos)            /*!< 0x00000400 */
#define RCC_MP_AHB4ENCLRR_GPIOKEN                 RCC_MP_AHB4ENCLRR_GPIOKEN_Msk                      /*!< GPIOK peripheral clocks enable */

/**************  Bit definition for RCC_MP_MLAHBENSETR register  **************/
#define RCC_MP_MLAHBENSETR_RETRAMEN_Pos           (4U)
#define RCC_MP_MLAHBENSETR_RETRAMEN_Msk           (0x1U << RCC_MP_MLAHBENSETR_RETRAMEN_Pos)          /*!< 0x00000010 */
#define RCC_MP_MLAHBENSETR_RETRAMEN               RCC_MP_MLAHBENSETR_RETRAMEN_Msk                    /*!< RETRAM peripheral clocks enable */

/**************  Bit definition for RCC_MP_MLAHBENCLRR register  **************/
#define RCC_MP_MLAHBENCLRR_RETRAMEN_Pos           (4U)
#define RCC_MP_MLAHBENCLRR_RETRAMEN_Msk           (0x1U << RCC_MP_MLAHBENCLRR_RETRAMEN_Pos)          /*!< 0x00000010 */
#define RCC_MP_MLAHBENCLRR_RETRAMEN               RCC_MP_MLAHBENCLRR_RETRAMEN_Msk                    /*!< RETRAM peripheral clocks enable */

/**************  Bit definition for RCC_MC_APB1ENSETR register  ***************/
#define RCC_MC_APB1ENSETR_TIM2EN_Pos              (0U)
#define RCC_MC_APB1ENSETR_TIM2EN_Msk              (0x1U << RCC_MC_APB1ENSETR_TIM2EN_Pos)             /*!< 0x00000001 */
#define RCC_MC_APB1ENSETR_TIM2EN                  RCC_MC_APB1ENSETR_TIM2EN_Msk                       /*!< TIM2 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_TIM3EN_Pos              (1U)
#define RCC_MC_APB1ENSETR_TIM3EN_Msk              (0x1U << RCC_MC_APB1ENSETR_TIM3EN_Pos)             /*!< 0x00000002 */
#define RCC_MC_APB1ENSETR_TIM3EN                  RCC_MC_APB1ENSETR_TIM3EN_Msk                       /*!< TIM3 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_TIM4EN_Pos              (2U)
#define RCC_MC_APB1ENSETR_TIM4EN_Msk              (0x1U << RCC_MC_APB1ENSETR_TIM4EN_Pos)             /*!< 0x00000004 */
#define RCC_MC_APB1ENSETR_TIM4EN                  RCC_MC_APB1ENSETR_TIM4EN_Msk                       /*!< TIM4 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_TIM5EN_Pos              (3U)
#define RCC_MC_APB1ENSETR_TIM5EN_Msk              (0x1U << RCC_MC_APB1ENSETR_TIM5EN_Pos)             /*!< 0x00000008 */
#define RCC_MC_APB1ENSETR_TIM5EN                  RCC_MC_APB1ENSETR_TIM5EN_Msk                       /*!< TIM5 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_TIM6EN_Pos              (4U)
#define RCC_MC_APB1ENSETR_TIM6EN_Msk              (0x1U << RCC_MC_APB1ENSETR_TIM6EN_Pos)             /*!< 0x00000010 */
#define RCC_MC_APB1ENSETR_TIM6EN                  RCC_MC_APB1ENSETR_TIM6EN_Msk                       /*!< TIM6 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_TIM7EN_Pos              (5U)
#define RCC_MC_APB1ENSETR_TIM7EN_Msk              (0x1U << RCC_MC_APB1ENSETR_TIM7EN_Pos)             /*!< 0x00000020 */
#define RCC_MC_APB1ENSETR_TIM7EN                  RCC_MC_APB1ENSETR_TIM7EN_Msk                       /*!< TIM7 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_TIM12EN_Pos             (6U)
#define RCC_MC_APB1ENSETR_TIM12EN_Msk             (0x1U << RCC_MC_APB1ENSETR_TIM12EN_Pos)            /*!< 0x00000040 */
#define RCC_MC_APB1ENSETR_TIM12EN                 RCC_MC_APB1ENSETR_TIM12EN_Msk                      /*!< TIM12 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_TIM13EN_Pos             (7U)
#define RCC_MC_APB1ENSETR_TIM13EN_Msk             (0x1U << RCC_MC_APB1ENSETR_TIM13EN_Pos)            /*!< 0x00000080 */
#define RCC_MC_APB1ENSETR_TIM13EN                 RCC_MC_APB1ENSETR_TIM13EN_Msk                      /*!< TIM13 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_TIM14EN_Pos             (8U)
#define RCC_MC_APB1ENSETR_TIM14EN_Msk             (0x1U << RCC_MC_APB1ENSETR_TIM14EN_Pos)            /*!< 0x00000100 */
#define RCC_MC_APB1ENSETR_TIM14EN                 RCC_MC_APB1ENSETR_TIM14EN_Msk                      /*!< TIM14 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_LPTIM1EN_Pos            (9U)
#define RCC_MC_APB1ENSETR_LPTIM1EN_Msk            (0x1U << RCC_MC_APB1ENSETR_LPTIM1EN_Pos)           /*!< 0x00000200 */
#define RCC_MC_APB1ENSETR_LPTIM1EN                RCC_MC_APB1ENSETR_LPTIM1EN_Msk                     /*!< LPTIM1 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_SPI2EN_Pos              (11U)
#define RCC_MC_APB1ENSETR_SPI2EN_Msk              (0x1U << RCC_MC_APB1ENSETR_SPI2EN_Pos)             /*!< 0x00000800 */
#define RCC_MC_APB1ENSETR_SPI2EN                  RCC_MC_APB1ENSETR_SPI2EN_Msk                       /*!< SPI2 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_SPI3EN_Pos              (12U)
#define RCC_MC_APB1ENSETR_SPI3EN_Msk              (0x1U << RCC_MC_APB1ENSETR_SPI3EN_Pos)             /*!< 0x00001000 */
#define RCC_MC_APB1ENSETR_SPI3EN                  RCC_MC_APB1ENSETR_SPI3EN_Msk                       /*!< SPI3 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_USART2EN_Pos            (14U)
#define RCC_MC_APB1ENSETR_USART2EN_Msk            (0x1U << RCC_MC_APB1ENSETR_USART2EN_Pos)           /*!< 0x00004000 */
#define RCC_MC_APB1ENSETR_USART2EN                RCC_MC_APB1ENSETR_USART2EN_Msk                     /*!< USART2 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_USART3EN_Pos            (15U)
#define RCC_MC_APB1ENSETR_USART3EN_Msk            (0x1U << RCC_MC_APB1ENSETR_USART3EN_Pos)           /*!< 0x00008000 */
#define RCC_MC_APB1ENSETR_USART3EN                RCC_MC_APB1ENSETR_USART3EN_Msk                     /*!< USART3 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_UART4EN_Pos             (16U)
#define RCC_MC_APB1ENSETR_UART4EN_Msk             (0x1U << RCC_MC_APB1ENSETR_UART4EN_Pos)            /*!< 0x00010000 */
#define RCC_MC_APB1ENSETR_UART4EN                 RCC_MC_APB1ENSETR_UART4EN_Msk                      /*!< UART4 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_UART5EN_Pos             (17U)
#define RCC_MC_APB1ENSETR_UART5EN_Msk             (0x1U << RCC_MC_APB1ENSETR_UART5EN_Pos)            /*!< 0x00020000 */
#define RCC_MC_APB1ENSETR_UART5EN                 RCC_MC_APB1ENSETR_UART5EN_Msk                      /*!< UART5 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_UART7EN_Pos             (18U)
#define RCC_MC_APB1ENSETR_UART7EN_Msk             (0x1U << RCC_MC_APB1ENSETR_UART7EN_Pos)            /*!< 0x00040000 */
#define RCC_MC_APB1ENSETR_UART7EN                 RCC_MC_APB1ENSETR_UART7EN_Msk                      /*!< UART7 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_UART8EN_Pos             (19U)
#define RCC_MC_APB1ENSETR_UART8EN_Msk             (0x1U << RCC_MC_APB1ENSETR_UART8EN_Pos)            /*!< 0x00080000 */
#define RCC_MC_APB1ENSETR_UART8EN                 RCC_MC_APB1ENSETR_UART8EN_Msk                      /*!< UART8 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_I2C1EN_Pos              (21U)
#define RCC_MC_APB1ENSETR_I2C1EN_Msk              (0x1U << RCC_MC_APB1ENSETR_I2C1EN_Pos)             /*!< 0x00200000 */
#define RCC_MC_APB1ENSETR_I2C1EN                  RCC_MC_APB1ENSETR_I2C1EN_Msk                       /*!< I2C1 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_I2C2EN_Pos              (22U)
#define RCC_MC_APB1ENSETR_I2C2EN_Msk              (0x1U << RCC_MC_APB1ENSETR_I2C2EN_Pos)             /*!< 0x00400000 */
#define RCC_MC_APB1ENSETR_I2C2EN                  RCC_MC_APB1ENSETR_I2C2EN_Msk                       /*!< I2C2 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_I2C3EN_Pos              (23U)
#define RCC_MC_APB1ENSETR_I2C3EN_Msk              (0x1U << RCC_MC_APB1ENSETR_I2C3EN_Pos)             /*!< 0x00800000 */
#define RCC_MC_APB1ENSETR_I2C3EN                  RCC_MC_APB1ENSETR_I2C3EN_Msk                       /*!< I2C3 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_I2C5EN_Pos              (24U)
#define RCC_MC_APB1ENSETR_I2C5EN_Msk              (0x1U << RCC_MC_APB1ENSETR_I2C5EN_Pos)             /*!< 0x01000000 */
#define RCC_MC_APB1ENSETR_I2C5EN                  RCC_MC_APB1ENSETR_I2C5EN_Msk                       /*!< I2C5 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_SPDIFEN_Pos             (26U)
#define RCC_MC_APB1ENSETR_SPDIFEN_Msk             (0x1U << RCC_MC_APB1ENSETR_SPDIFEN_Pos)            /*!< 0x04000000 */
#define RCC_MC_APB1ENSETR_SPDIFEN                 RCC_MC_APB1ENSETR_SPDIFEN_Msk                      /*!< SPDIFRX peripheral clocks enable */
#define RCC_MC_APB1ENSETR_CECEN_Pos               (27U)
#define RCC_MC_APB1ENSETR_CECEN_Msk               (0x1U << RCC_MC_APB1ENSETR_CECEN_Pos)              /*!< 0x08000000 */
#define RCC_MC_APB1ENSETR_CECEN                   RCC_MC_APB1ENSETR_CECEN_Msk                        /*!< HDMI-CEC peripheral clocks enable */
#define RCC_MC_APB1ENSETR_WWDG1EN_Pos             (28U)
#define RCC_MC_APB1ENSETR_WWDG1EN_Msk             (0x1U << RCC_MC_APB1ENSETR_WWDG1EN_Pos)            /*!< 0x10000000 */
#define RCC_MC_APB1ENSETR_WWDG1EN                 RCC_MC_APB1ENSETR_WWDG1EN_Msk                      /*!< WWDG1 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_DAC12EN_Pos             (29U)
#define RCC_MC_APB1ENSETR_DAC12EN_Msk             (0x1U << RCC_MC_APB1ENSETR_DAC12EN_Pos)            /*!< 0x20000000 */
#define RCC_MC_APB1ENSETR_DAC12EN                 RCC_MC_APB1ENSETR_DAC12EN_Msk                      /*!< DAC1&amp;2 peripheral clocks enable */
#define RCC_MC_APB1ENSETR_MDIOSEN_Pos             (31U)
#define RCC_MC_APB1ENSETR_MDIOSEN_Msk             (0x1U << RCC_MC_APB1ENSETR_MDIOSEN_Pos)            /*!< 0x80000000 */
#define RCC_MC_APB1ENSETR_MDIOSEN                 RCC_MC_APB1ENSETR_MDIOSEN_Msk                      /*!< MDIOS peripheral clocks enable */

/**************  Bit definition for RCC_MC_APB1ENCLRR register  ***************/
#define RCC_MC_APB1ENCLRR_TIM2EN_Pos              (0U)
#define RCC_MC_APB1ENCLRR_TIM2EN_Msk              (0x1U << RCC_MC_APB1ENCLRR_TIM2EN_Pos)             /*!< 0x00000001 */
#define RCC_MC_APB1ENCLRR_TIM2EN                  RCC_MC_APB1ENCLRR_TIM2EN_Msk                       /*!< TIM2 peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_TIM3EN_Pos              (1U)
#define RCC_MC_APB1ENCLRR_TIM3EN_Msk              (0x1U << RCC_MC_APB1ENCLRR_TIM3EN_Pos)             /*!< 0x00000002 */
#define RCC_MC_APB1ENCLRR_TIM3EN                  RCC_MC_APB1ENCLRR_TIM3EN_Msk                       /*!< TIM3 peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_TIM4EN_Pos              (2U)
#define RCC_MC_APB1ENCLRR_TIM4EN_Msk              (0x1U << RCC_MC_APB1ENCLRR_TIM4EN_Pos)             /*!< 0x00000004 */
#define RCC_MC_APB1ENCLRR_TIM4EN                  RCC_MC_APB1ENCLRR_TIM4EN_Msk                       /*!< TIM4 peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_TIM5EN_Pos              (3U)
#define RCC_MC_APB1ENCLRR_TIM5EN_Msk              (0x1U << RCC_MC_APB1ENCLRR_TIM5EN_Pos)             /*!< 0x00000008 */
#define RCC_MC_APB1ENCLRR_TIM5EN                  RCC_MC_APB1ENCLRR_TIM5EN_Msk                       /*!< TIM5 peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_TIM6EN_Pos              (4U)
#define RCC_MC_APB1ENCLRR_TIM6EN_Msk              (0x1U << RCC_MC_APB1ENCLRR_TIM6EN_Pos)             /*!< 0x00000010 */
#define RCC_MC_APB1ENCLRR_TIM6EN                  RCC_MC_APB1ENCLRR_TIM6EN_Msk                       /*!< TIM6 peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_TIM7EN_Pos              (5U)
#define RCC_MC_APB1ENCLRR_TIM7EN_Msk              (0x1U << RCC_MC_APB1ENCLRR_TIM7EN_Pos)             /*!< 0x00000020 */
#define RCC_MC_APB1ENCLRR_TIM7EN                  RCC_MC_APB1ENCLRR_TIM7EN_Msk                       /*!< TIM7 peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_TIM12EN_Pos             (6U)
#define RCC_MC_APB1ENCLRR_TIM12EN_Msk             (0x1U << RCC_MC_APB1ENCLRR_TIM12EN_Pos)            /*!< 0x00000040 */
#define RCC_MC_APB1ENCLRR_TIM12EN                 RCC_MC_APB1ENCLRR_TIM12EN_Msk                      /*!< TIM12 peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_TIM13EN_Pos             (7U)
#define RCC_MC_APB1ENCLRR_TIM13EN_Msk             (0x1U << RCC_MC_APB1ENCLRR_TIM13EN_Pos)            /*!< 0x00000080 */
#define RCC_MC_APB1ENCLRR_TIM13EN                 RCC_MC_APB1ENCLRR_TIM13EN_Msk                      /*!< TIM13 peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_TIM14EN_Pos             (8U)
#define RCC_MC_APB1ENCLRR_TIM14EN_Msk             (0x1U << RCC_MC_APB1ENCLRR_TIM14EN_Pos)            /*!< 0x00000100 */
#define RCC_MC_APB1ENCLRR_TIM14EN                 RCC_MC_APB1ENCLRR_TIM14EN_Msk                      /*!< TIM14 peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_LPTIM1EN_Pos            (9U)
#define RCC_MC_APB1ENCLRR_LPTIM1EN_Msk            (0x1U << RCC_MC_APB1ENCLRR_LPTIM1EN_Pos)           /*!< 0x00000200 */
#define RCC_MC_APB1ENCLRR_LPTIM1EN                RCC_MC_APB1ENCLRR_LPTIM1EN_Msk                     /*!< LPTIM1 peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_SPI2EN_Pos              (11U)
#define RCC_MC_APB1ENCLRR_SPI2EN_Msk              (0x1U << RCC_MC_APB1ENCLRR_SPI2EN_Pos)             /*!< 0x00000800 */
#define RCC_MC_APB1ENCLRR_SPI2EN                  RCC_MC_APB1ENCLRR_SPI2EN_Msk                       /*!< SPI2 peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_SPI3EN_Pos              (12U)
#define RCC_MC_APB1ENCLRR_SPI3EN_Msk              (0x1U << RCC_MC_APB1ENCLRR_SPI3EN_Pos)             /*!< 0x00001000 */
#define RCC_MC_APB1ENCLRR_SPI3EN                  RCC_MC_APB1ENCLRR_SPI3EN_Msk                       /*!< SPI3 peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_USART2EN_Pos            (14U)
#define RCC_MC_APB1ENCLRR_USART2EN_Msk            (0x1U << RCC_MC_APB1ENCLRR_USART2EN_Pos)           /*!< 0x00004000 */
#define RCC_MC_APB1ENCLRR_USART2EN                RCC_MC_APB1ENCLRR_USART2EN_Msk                     /*!< USART2 peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_USART3EN_Pos            (15U)
#define RCC_MC_APB1ENCLRR_USART3EN_Msk            (0x1U << RCC_MC_APB1ENCLRR_USART3EN_Pos)           /*!< 0x00008000 */
#define RCC_MC_APB1ENCLRR_USART3EN                RCC_MC_APB1ENCLRR_USART3EN_Msk                     /*!< USART3 peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_UART4EN_Pos             (16U)
#define RCC_MC_APB1ENCLRR_UART4EN_Msk             (0x1U << RCC_MC_APB1ENCLRR_UART4EN_Pos)            /*!< 0x00010000 */
#define RCC_MC_APB1ENCLRR_UART4EN                 RCC_MC_APB1ENCLRR_UART4EN_Msk                      /*!< UART4 peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_UART5EN_Pos             (17U)
#define RCC_MC_APB1ENCLRR_UART5EN_Msk             (0x1U << RCC_MC_APB1ENCLRR_UART5EN_Pos)            /*!< 0x00020000 */
#define RCC_MC_APB1ENCLRR_UART5EN                 RCC_MC_APB1ENCLRR_UART5EN_Msk                      /*!< UART5 peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_UART7EN_Pos             (18U)
#define RCC_MC_APB1ENCLRR_UART7EN_Msk             (0x1U << RCC_MC_APB1ENCLRR_UART7EN_Pos)            /*!< 0x00040000 */
#define RCC_MC_APB1ENCLRR_UART7EN                 RCC_MC_APB1ENCLRR_UART7EN_Msk                      /*!< UART7 peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_UART8EN_Pos             (19U)
#define RCC_MC_APB1ENCLRR_UART8EN_Msk             (0x1U << RCC_MC_APB1ENCLRR_UART8EN_Pos)            /*!< 0x00080000 */
#define RCC_MC_APB1ENCLRR_UART8EN                 RCC_MC_APB1ENCLRR_UART8EN_Msk                      /*!< UART8 peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_I2C1EN_Pos              (21U)
#define RCC_MC_APB1ENCLRR_I2C1EN_Msk              (0x1U << RCC_MC_APB1ENCLRR_I2C1EN_Pos)             /*!< 0x00200000 */
#define RCC_MC_APB1ENCLRR_I2C1EN                  RCC_MC_APB1ENCLRR_I2C1EN_Msk                       /*!< I2C1 peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_I2C2EN_Pos              (22U)
#define RCC_MC_APB1ENCLRR_I2C2EN_Msk              (0x1U << RCC_MC_APB1ENCLRR_I2C2EN_Pos)             /*!< 0x00400000 */
#define RCC_MC_APB1ENCLRR_I2C2EN                  RCC_MC_APB1ENCLRR_I2C2EN_Msk                       /*!< I2C2 peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_I2C3EN_Pos              (23U)
#define RCC_MC_APB1ENCLRR_I2C3EN_Msk              (0x1U << RCC_MC_APB1ENCLRR_I2C3EN_Pos)             /*!< 0x00800000 */
#define RCC_MC_APB1ENCLRR_I2C3EN                  RCC_MC_APB1ENCLRR_I2C3EN_Msk                       /*!< I2C3 peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_I2C5EN_Pos              (24U)
#define RCC_MC_APB1ENCLRR_I2C5EN_Msk              (0x1U << RCC_MC_APB1ENCLRR_I2C5EN_Pos)             /*!< 0x01000000 */
#define RCC_MC_APB1ENCLRR_I2C5EN                  RCC_MC_APB1ENCLRR_I2C5EN_Msk                       /*!< I2C5 peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_SPDIFEN_Pos             (26U)
#define RCC_MC_APB1ENCLRR_SPDIFEN_Msk             (0x1U << RCC_MC_APB1ENCLRR_SPDIFEN_Pos)            /*!< 0x04000000 */
#define RCC_MC_APB1ENCLRR_SPDIFEN                 RCC_MC_APB1ENCLRR_SPDIFEN_Msk                      /*!< SPDIFRX peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_CECEN_Pos               (27U)
#define RCC_MC_APB1ENCLRR_CECEN_Msk               (0x1U << RCC_MC_APB1ENCLRR_CECEN_Pos)              /*!< 0x08000000 */
#define RCC_MC_APB1ENCLRR_CECEN                   RCC_MC_APB1ENCLRR_CECEN_Msk                        /*!< HDMI-CEC peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_DAC12EN_Pos             (29U)
#define RCC_MC_APB1ENCLRR_DAC12EN_Msk             (0x1U << RCC_MC_APB1ENCLRR_DAC12EN_Pos)            /*!< 0x20000000 */
#define RCC_MC_APB1ENCLRR_DAC12EN                 RCC_MC_APB1ENCLRR_DAC12EN_Msk                      /*!< DAC1&amp;2 peripheral clocks enable */
#define RCC_MC_APB1ENCLRR_MDIOSEN_Pos             (31U)
#define RCC_MC_APB1ENCLRR_MDIOSEN_Msk             (0x1U << RCC_MC_APB1ENCLRR_MDIOSEN_Pos)            /*!< 0x80000000 */
#define RCC_MC_APB1ENCLRR_MDIOSEN                 RCC_MC_APB1ENCLRR_MDIOSEN_Msk                      /*!< MDIOS peripheral clocks enable */

/**************  Bit definition for RCC_MC_APB2ENSETR register  ***************/
#define RCC_MC_APB2ENSETR_TIM1EN_Pos              (0U)
#define RCC_MC_APB2ENSETR_TIM1EN_Msk              (0x1U << RCC_MC_APB2ENSETR_TIM1EN_Pos)             /*!< 0x00000001 */
#define RCC_MC_APB2ENSETR_TIM1EN                  RCC_MC_APB2ENSETR_TIM1EN_Msk                       /*!< TIM1 peripheral clocks enable */
#define RCC_MC_APB2ENSETR_TIM8EN_Pos              (1U)
#define RCC_MC_APB2ENSETR_TIM8EN_Msk              (0x1U << RCC_MC_APB2ENSETR_TIM8EN_Pos)             /*!< 0x00000002 */
#define RCC_MC_APB2ENSETR_TIM8EN                  RCC_MC_APB2ENSETR_TIM8EN_Msk                       /*!< TIM8 peripheral clocks enable */
#define RCC_MC_APB2ENSETR_TIM15EN_Pos             (2U)
#define RCC_MC_APB2ENSETR_TIM15EN_Msk             (0x1U << RCC_MC_APB2ENSETR_TIM15EN_Pos)            /*!< 0x00000004 */
#define RCC_MC_APB2ENSETR_TIM15EN                 RCC_MC_APB2ENSETR_TIM15EN_Msk                      /*!< TIM15 peripheral clocks enable */
#define RCC_MC_APB2ENSETR_TIM16EN_Pos             (3U)
#define RCC_MC_APB2ENSETR_TIM16EN_Msk             (0x1U << RCC_MC_APB2ENSETR_TIM16EN_Pos)            /*!< 0x00000008 */
#define RCC_MC_APB2ENSETR_TIM16EN                 RCC_MC_APB2ENSETR_TIM16EN_Msk                      /*!< TIM16 peripheral clocks enable */
#define RCC_MC_APB2ENSETR_TIM17EN_Pos             (4U)
#define RCC_MC_APB2ENSETR_TIM17EN_Msk             (0x1U << RCC_MC_APB2ENSETR_TIM17EN_Pos)            /*!< 0x00000010 */
#define RCC_MC_APB2ENSETR_TIM17EN                 RCC_MC_APB2ENSETR_TIM17EN_Msk                      /*!< TIM17 peripheral clocks enable */
#define RCC_MC_APB2ENSETR_SPI1EN_Pos              (8U)
#define RCC_MC_APB2ENSETR_SPI1EN_Msk              (0x1U << RCC_MC_APB2ENSETR_SPI1EN_Pos)             /*!< 0x00000100 */
#define RCC_MC_APB2ENSETR_SPI1EN                  RCC_MC_APB2ENSETR_SPI1EN_Msk                       /*!< SPI/I2S1 peripheral clocks enable */
#define RCC_MC_APB2ENSETR_SPI4EN_Pos              (9U)
#define RCC_MC_APB2ENSETR_SPI4EN_Msk              (0x1U << RCC_MC_APB2ENSETR_SPI4EN_Pos)             /*!< 0x00000200 */
#define RCC_MC_APB2ENSETR_SPI4EN                  RCC_MC_APB2ENSETR_SPI4EN_Msk                       /*!< SPI4 peripheral clocks enable */
#define RCC_MC_APB2ENSETR_SPI5EN_Pos              (10U)
#define RCC_MC_APB2ENSETR_SPI5EN_Msk              (0x1U << RCC_MC_APB2ENSETR_SPI5EN_Pos)             /*!< 0x00000400 */
#define RCC_MC_APB2ENSETR_SPI5EN                  RCC_MC_APB2ENSETR_SPI5EN_Msk                       /*!< SPI5 peripheral clocks enable */
#define RCC_MC_APB2ENSETR_USART6EN_Pos            (13U)
#define RCC_MC_APB2ENSETR_USART6EN_Msk            (0x1U << RCC_MC_APB2ENSETR_USART6EN_Pos)           /*!< 0x00002000 */
#define RCC_MC_APB2ENSETR_USART6EN                RCC_MC_APB2ENSETR_USART6EN_Msk                     /*!< USART6 peripheral clocks enable */
#define RCC_MC_APB2ENSETR_SAI1EN_Pos              (16U)
#define RCC_MC_APB2ENSETR_SAI1EN_Msk              (0x1U << RCC_MC_APB2ENSETR_SAI1EN_Pos)             /*!< 0x00010000 */
#define RCC_MC_APB2ENSETR_SAI1EN                  RCC_MC_APB2ENSETR_SAI1EN_Msk                       /*!< SAI1 peripheral clocks enable */
#define RCC_MC_APB2ENSETR_SAI2EN_Pos              (17U)
#define RCC_MC_APB2ENSETR_SAI2EN_Msk              (0x1U << RCC_MC_APB2ENSETR_SAI2EN_Pos)             /*!< 0x00020000 */
#define RCC_MC_APB2ENSETR_SAI2EN                  RCC_MC_APB2ENSETR_SAI2EN_Msk                       /*!< SAI2 peripheral clocks enable */
#define RCC_MC_APB2ENSETR_SAI3EN_Pos              (18U)
#define RCC_MC_APB2ENSETR_SAI3EN_Msk              (0x1U << RCC_MC_APB2ENSETR_SAI3EN_Pos)             /*!< 0x00040000 */
#define RCC_MC_APB2ENSETR_SAI3EN                  RCC_MC_APB2ENSETR_SAI3EN_Msk                       /*!< SAI3 peripheral clocks enable */
#define RCC_MC_APB2ENSETR_DFSDMEN_Pos             (20U)
#define RCC_MC_APB2ENSETR_DFSDMEN_Msk             (0x1U << RCC_MC_APB2ENSETR_DFSDMEN_Pos)            /*!< 0x00100000 */
#define RCC_MC_APB2ENSETR_DFSDMEN                 RCC_MC_APB2ENSETR_DFSDMEN_Msk                      /*!< DFSDM peripheral clocks enable */
#define RCC_MC_APB2ENSETR_ADFSDMEN_Pos            (21U)
#define RCC_MC_APB2ENSETR_ADFSDMEN_Msk            (0x1U << RCC_MC_APB2ENSETR_ADFSDMEN_Pos)           /*!< 0x00200000 */
#define RCC_MC_APB2ENSETR_ADFSDMEN                RCC_MC_APB2ENSETR_ADFSDMEN_Msk                     /*!< Audio DFSDM peripheral clocks enable */
#define RCC_MC_APB2ENSETR_FDCANEN_Pos             (24U)
#define RCC_MC_APB2ENSETR_FDCANEN_Msk             (0x1U << RCC_MC_APB2ENSETR_FDCANEN_Pos)            /*!< 0x01000000 */
#define RCC_MC_APB2ENSETR_FDCANEN                 RCC_MC_APB2ENSETR_FDCANEN_Msk                      /*!< FDCAN and CANRAM peripheral clocks enable */

/**************  Bit definition for RCC_MC_APB2ENCLRR register  ***************/
#define RCC_MC_APB2ENCLRR_TIM1EN_Pos              (0U)
#define RCC_MC_APB2ENCLRR_TIM1EN_Msk              (0x1U << RCC_MC_APB2ENCLRR_TIM1EN_Pos)             /*!< 0x00000001 */
#define RCC_MC_APB2ENCLRR_TIM1EN                  RCC_MC_APB2ENCLRR_TIM1EN_Msk                       /*!< TIM1 peripheral clocks enable */
#define RCC_MC_APB2ENCLRR_TIM8EN_Pos              (1U)
#define RCC_MC_APB2ENCLRR_TIM8EN_Msk              (0x1U << RCC_MC_APB2ENCLRR_TIM8EN_Pos)             /*!< 0x00000002 */
#define RCC_MC_APB2ENCLRR_TIM8EN                  RCC_MC_APB2ENCLRR_TIM8EN_Msk                       /*!< TIM8 peripheral clocks enable */
#define RCC_MC_APB2ENCLRR_TIM15EN_Pos             (2U)
#define RCC_MC_APB2ENCLRR_TIM15EN_Msk             (0x1U << RCC_MC_APB2ENCLRR_TIM15EN_Pos)            /*!< 0x00000004 */
#define RCC_MC_APB2ENCLRR_TIM15EN                 RCC_MC_APB2ENCLRR_TIM15EN_Msk                      /*!< TIM15 peripheral clocks enable */
#define RCC_MC_APB2ENCLRR_TIM16EN_Pos             (3U)
#define RCC_MC_APB2ENCLRR_TIM16EN_Msk             (0x1U << RCC_MC_APB2ENCLRR_TIM16EN_Pos)            /*!< 0x00000008 */
#define RCC_MC_APB2ENCLRR_TIM16EN                 RCC_MC_APB2ENCLRR_TIM16EN_Msk                      /*!< TIM16 peripheral clocks enable */
#define RCC_MC_APB2ENCLRR_TIM17EN_Pos             (4U)
#define RCC_MC_APB2ENCLRR_TIM17EN_Msk             (0x1U << RCC_MC_APB2ENCLRR_TIM17EN_Pos)            /*!< 0x00000010 */
#define RCC_MC_APB2ENCLRR_TIM17EN                 RCC_MC_APB2ENCLRR_TIM17EN_Msk                      /*!< TIM17 peripheral clocks enable */
#define RCC_MC_APB2ENCLRR_SPI1EN_Pos              (8U)
#define RCC_MC_APB2ENCLRR_SPI1EN_Msk              (0x1U << RCC_MC_APB2ENCLRR_SPI1EN_Pos)             /*!< 0x00000100 */
#define RCC_MC_APB2ENCLRR_SPI1EN                  RCC_MC_APB2ENCLRR_SPI1EN_Msk                       /*!< SPI/I2S1 peripheral clocks enable */
#define RCC_MC_APB2ENCLRR_SPI4EN_Pos              (9U)
#define RCC_MC_APB2ENCLRR_SPI4EN_Msk              (0x1U << RCC_MC_APB2ENCLRR_SPI4EN_Pos)             /*!< 0x00000200 */
#define RCC_MC_APB2ENCLRR_SPI4EN                  RCC_MC_APB2ENCLRR_SPI4EN_Msk                       /*!< SPI4 peripheral clocks enable */
#define RCC_MC_APB2ENCLRR_SPI5EN_Pos              (10U)
#define RCC_MC_APB2ENCLRR_SPI5EN_Msk              (0x1U << RCC_MC_APB2ENCLRR_SPI5EN_Pos)             /*!< 0x00000400 */
#define RCC_MC_APB2ENCLRR_SPI5EN                  RCC_MC_APB2ENCLRR_SPI5EN_Msk                       /*!< SPI5 peripheral clocks enable */
#define RCC_MC_APB2ENCLRR_USART6EN_Pos            (13U)
#define RCC_MC_APB2ENCLRR_USART6EN_Msk            (0x1U << RCC_MC_APB2ENCLRR_USART6EN_Pos)           /*!< 0x00002000 */
#define RCC_MC_APB2ENCLRR_USART6EN                RCC_MC_APB2ENCLRR_USART6EN_Msk                     /*!< USART6 peripheral clocks enable */
#define RCC_MC_APB2ENCLRR_SAI1EN_Pos              (16U)
#define RCC_MC_APB2ENCLRR_SAI1EN_Msk              (0x1U << RCC_MC_APB2ENCLRR_SAI1EN_Pos)             /*!< 0x00010000 */
#define RCC_MC_APB2ENCLRR_SAI1EN                  RCC_MC_APB2ENCLRR_SAI1EN_Msk                       /*!< SAI1 peripheral clocks enable */
#define RCC_MC_APB2ENCLRR_SAI2EN_Pos              (17U)
#define RCC_MC_APB2ENCLRR_SAI2EN_Msk              (0x1U << RCC_MC_APB2ENCLRR_SAI2EN_Pos)             /*!< 0x00020000 */
#define RCC_MC_APB2ENCLRR_SAI2EN                  RCC_MC_APB2ENCLRR_SAI2EN_Msk                       /*!< SAI2 peripheral clocks enable */
#define RCC_MC_APB2ENCLRR_SAI3EN_Pos              (18U)
#define RCC_MC_APB2ENCLRR_SAI3EN_Msk              (0x1U << RCC_MC_APB2ENCLRR_SAI3EN_Pos)             /*!< 0x00040000 */
#define RCC_MC_APB2ENCLRR_SAI3EN                  RCC_MC_APB2ENCLRR_SAI3EN_Msk                       /*!< SAI3 peripheral clocks enable */
#define RCC_MC_APB2ENCLRR_DFSDMEN_Pos             (20U)
#define RCC_MC_APB2ENCLRR_DFSDMEN_Msk             (0x1U << RCC_MC_APB2ENCLRR_DFSDMEN_Pos)            /*!< 0x00100000 */
#define RCC_MC_APB2ENCLRR_DFSDMEN                 RCC_MC_APB2ENCLRR_DFSDMEN_Msk                      /*!< DFSDM peripheral clocks enable */
#define RCC_MC_APB2ENCLRR_ADFSDMEN_Pos            (21U)
#define RCC_MC_APB2ENCLRR_ADFSDMEN_Msk            (0x1U << RCC_MC_APB2ENCLRR_ADFSDMEN_Pos)           /*!< 0x00200000 */
#define RCC_MC_APB2ENCLRR_ADFSDMEN                RCC_MC_APB2ENCLRR_ADFSDMEN_Msk                     /*!< Audio DFSDM peripheral clocks enable */
#define RCC_MC_APB2ENCLRR_FDCANEN_Pos             (24U)
#define RCC_MC_APB2ENCLRR_FDCANEN_Msk             (0x1U << RCC_MC_APB2ENCLRR_FDCANEN_Pos)            /*!< 0x01000000 */
#define RCC_MC_APB2ENCLRR_FDCANEN                 RCC_MC_APB2ENCLRR_FDCANEN_Msk                      /*!< FDCAN and CANRAM peripheral clocks enable */

/**************  Bit definition for RCC_MC_APB3ENSETR register  ***************/
#define RCC_MC_APB3ENSETR_LPTIM2EN_Pos            (0U)
#define RCC_MC_APB3ENSETR_LPTIM2EN_Msk            (0x1U << RCC_MC_APB3ENSETR_LPTIM2EN_Pos)           /*!< 0x00000001 */
#define RCC_MC_APB3ENSETR_LPTIM2EN                RCC_MC_APB3ENSETR_LPTIM2EN_Msk                     /*!< LPTIM2 peripheral clocks enable */
#define RCC_MC_APB3ENSETR_LPTIM3EN_Pos            (1U)
#define RCC_MC_APB3ENSETR_LPTIM3EN_Msk            (0x1U << RCC_MC_APB3ENSETR_LPTIM3EN_Pos)           /*!< 0x00000002 */
#define RCC_MC_APB3ENSETR_LPTIM3EN                RCC_MC_APB3ENSETR_LPTIM3EN_Msk                     /*!< LPTIM3 peripheral clocks enable */
#define RCC_MC_APB3ENSETR_LPTIM4EN_Pos            (2U)
#define RCC_MC_APB3ENSETR_LPTIM4EN_Msk            (0x1U << RCC_MC_APB3ENSETR_LPTIM4EN_Pos)           /*!< 0x00000004 */
#define RCC_MC_APB3ENSETR_LPTIM4EN                RCC_MC_APB3ENSETR_LPTIM4EN_Msk                     /*!< LPTIM4 peripheral clocks enable */
#define RCC_MC_APB3ENSETR_LPTIM5EN_Pos            (3U)
#define RCC_MC_APB3ENSETR_LPTIM5EN_Msk            (0x1U << RCC_MC_APB3ENSETR_LPTIM5EN_Pos)           /*!< 0x00000008 */
#define RCC_MC_APB3ENSETR_LPTIM5EN                RCC_MC_APB3ENSETR_LPTIM5EN_Msk                     /*!< LPTIM5 peripheral clocks enable */
#define RCC_MC_APB3ENSETR_SAI4EN_Pos              (8U)
#define RCC_MC_APB3ENSETR_SAI4EN_Msk              (0x1U << RCC_MC_APB3ENSETR_SAI4EN_Pos)             /*!< 0x00000100 */
#define RCC_MC_APB3ENSETR_SAI4EN                  RCC_MC_APB3ENSETR_SAI4EN_Msk                       /*!< SAI4 peripheral clocks enable */
#define RCC_MC_APB3ENSETR_SYSCFGEN_Pos            (11U)
#define RCC_MC_APB3ENSETR_SYSCFGEN_Msk            (0x1U << RCC_MC_APB3ENSETR_SYSCFGEN_Pos)           /*!< 0x00000800 */
#define RCC_MC_APB3ENSETR_SYSCFGEN                RCC_MC_APB3ENSETR_SYSCFGEN_Msk                     /*!< SYSCFG peripheral clocks enable */
#define RCC_MC_APB3ENSETR_VREFEN_Pos              (13U)
#define RCC_MC_APB3ENSETR_VREFEN_Msk              (0x1U << RCC_MC_APB3ENSETR_VREFEN_Pos)             /*!< 0x00002000 */
#define RCC_MC_APB3ENSETR_VREFEN                  RCC_MC_APB3ENSETR_VREFEN_Msk                       /*!< VREF peripheral clocks enable */
#define RCC_MC_APB3ENSETR_DTSEN_Pos               (16U)
#define RCC_MC_APB3ENSETR_DTSEN_Msk               (0x1U << RCC_MC_APB3ENSETR_DTSEN_Pos)              /*!< 0x00010000 */
#define RCC_MC_APB3ENSETR_DTSEN                   RCC_MC_APB3ENSETR_DTSEN_Msk                        /*!< DTS peripheral clocks enable */
#define RCC_MC_APB3ENSETR_HDPEN_Pos               (20U)
#define RCC_MC_APB3ENSETR_HDPEN_Msk               (0x1U << RCC_MC_APB3ENSETR_HDPEN_Pos)              /*!< 0x00100000 */
#define RCC_MC_APB3ENSETR_HDPEN                   RCC_MC_APB3ENSETR_HDPEN_Msk                        /*!< HDP peripheral clocks enable */

/**************  Bit definition for RCC_MC_APB3ENCLRR register  ***************/
#define RCC_MC_APB3ENCLRR_LPTIM2EN_Pos            (0U)
#define RCC_MC_APB3ENCLRR_LPTIM2EN_Msk            (0x1U << RCC_MC_APB3ENCLRR_LPTIM2EN_Pos)           /*!< 0x00000001 */
#define RCC_MC_APB3ENCLRR_LPTIM2EN                RCC_MC_APB3ENCLRR_LPTIM2EN_Msk                     /*!< LPTIM2 peripheral clocks enable */
#define RCC_MC_APB3ENCLRR_LPTIM3EN_Pos            (1U)
#define RCC_MC_APB3ENCLRR_LPTIM3EN_Msk            (0x1U << RCC_MC_APB3ENCLRR_LPTIM3EN_Pos)           /*!< 0x00000002 */
#define RCC_MC_APB3ENCLRR_LPTIM3EN                RCC_MC_APB3ENCLRR_LPTIM3EN_Msk                     /*!< LPTIM3 peripheral clocks enable */
#define RCC_MC_APB3ENCLRR_LPTIM4EN_Pos            (2U)
#define RCC_MC_APB3ENCLRR_LPTIM4EN_Msk            (0x1U << RCC_MC_APB3ENCLRR_LPTIM4EN_Pos)           /*!< 0x00000004 */
#define RCC_MC_APB3ENCLRR_LPTIM4EN                RCC_MC_APB3ENCLRR_LPTIM4EN_Msk                     /*!< LPTIM4 peripheral clocks enable */
#define RCC_MC_APB3ENCLRR_LPTIM5EN_Pos            (3U)
#define RCC_MC_APB3ENCLRR_LPTIM5EN_Msk            (0x1U << RCC_MC_APB3ENCLRR_LPTIM5EN_Pos)           /*!< 0x00000008 */
#define RCC_MC_APB3ENCLRR_LPTIM5EN                RCC_MC_APB3ENCLRR_LPTIM5EN_Msk                     /*!< LPTIM5 peripheral clocks enable */
#define RCC_MC_APB3ENCLRR_SAI4EN_Pos              (8U)
#define RCC_MC_APB3ENCLRR_SAI4EN_Msk              (0x1U << RCC_MC_APB3ENCLRR_SAI4EN_Pos)             /*!< 0x00000100 */
#define RCC_MC_APB3ENCLRR_SAI4EN                  RCC_MC_APB3ENCLRR_SAI4EN_Msk                       /*!< SAI4 peripheral clocks enable */
#define RCC_MC_APB3ENCLRR_SYSCFGEN_Pos            (11U)
#define RCC_MC_APB3ENCLRR_SYSCFGEN_Msk            (0x1U << RCC_MC_APB3ENCLRR_SYSCFGEN_Pos)           /*!< 0x00000800 */
#define RCC_MC_APB3ENCLRR_SYSCFGEN                RCC_MC_APB3ENCLRR_SYSCFGEN_Msk                     /*!< SYSCFG peripheral clocks enable */
#define RCC_MC_APB3ENCLRR_VREFEN_Pos              (13U)
#define RCC_MC_APB3ENCLRR_VREFEN_Msk              (0x1U << RCC_MC_APB3ENCLRR_VREFEN_Pos)             /*!< 0x00002000 */
#define RCC_MC_APB3ENCLRR_VREFEN                  RCC_MC_APB3ENCLRR_VREFEN_Msk                       /*!< VREF peripheral clocks enable */
#define RCC_MC_APB3ENCLRR_DTSEN_Pos               (16U)
#define RCC_MC_APB3ENCLRR_DTSEN_Msk               (0x1U << RCC_MC_APB3ENCLRR_DTSEN_Pos)              /*!< 0x00010000 */
#define RCC_MC_APB3ENCLRR_DTSEN                   RCC_MC_APB3ENCLRR_DTSEN_Msk                        /*!< DTS peripheral clocks enable */
#define RCC_MC_APB3ENCLRR_HDPEN_Pos               (20U)
#define RCC_MC_APB3ENCLRR_HDPEN_Msk               (0x1U << RCC_MC_APB3ENCLRR_HDPEN_Pos)              /*!< 0x00100000 */
#define RCC_MC_APB3ENCLRR_HDPEN                   RCC_MC_APB3ENCLRR_HDPEN_Msk                        /*!< HDP peripheral clocks enable */

/**************  Bit definition for RCC_MC_AHB2ENSETR register  ***************/
#define RCC_MC_AHB2ENSETR_DMA1EN_Pos              (0U)
#define RCC_MC_AHB2ENSETR_DMA1EN_Msk              (0x1U << RCC_MC_AHB2ENSETR_DMA1EN_Pos)             /*!< 0x00000001 */
#define RCC_MC_AHB2ENSETR_DMA1EN                  RCC_MC_AHB2ENSETR_DMA1EN_Msk                       /*!< DMA1 peripheral clocks enable */
#define RCC_MC_AHB2ENSETR_DMA2EN_Pos              (1U)
#define RCC_MC_AHB2ENSETR_DMA2EN_Msk              (0x1U << RCC_MC_AHB2ENSETR_DMA2EN_Pos)             /*!< 0x00000002 */
#define RCC_MC_AHB2ENSETR_DMA2EN                  RCC_MC_AHB2ENSETR_DMA2EN_Msk                       /*!< DMA2 peripheral clocks enable */
#define RCC_MC_AHB2ENSETR_DMAMUXEN_Pos            (2U)
#define RCC_MC_AHB2ENSETR_DMAMUXEN_Msk            (0x1U << RCC_MC_AHB2ENSETR_DMAMUXEN_Pos)           /*!< 0x00000004 */
#define RCC_MC_AHB2ENSETR_DMAMUXEN                RCC_MC_AHB2ENSETR_DMAMUXEN_Msk                     /*!< DMAMUX peripheral clocks enable */
#define RCC_MC_AHB2ENSETR_ADC12EN_Pos             (5U)
#define RCC_MC_AHB2ENSETR_ADC12EN_Msk             (0x1U << RCC_MC_AHB2ENSETR_ADC12EN_Pos)            /*!< 0x00000020 */
#define RCC_MC_AHB2ENSETR_ADC12EN                 RCC_MC_AHB2ENSETR_ADC12EN_Msk                      /*!< ADC1&amp;2 peripheral clocks enable */
#define RCC_MC_AHB2ENSETR_USBOEN_Pos              (8U)
#define RCC_MC_AHB2ENSETR_USBOEN_Msk              (0x1U << RCC_MC_AHB2ENSETR_USBOEN_Pos)             /*!< 0x00000100 */
#define RCC_MC_AHB2ENSETR_USBOEN                  RCC_MC_AHB2ENSETR_USBOEN_Msk                       /*!< USBO peripheral clocks enable */
#define RCC_MC_AHB2ENSETR_SDMMC3EN_Pos            (16U)
#define RCC_MC_AHB2ENSETR_SDMMC3EN_Msk            (0x1U << RCC_MC_AHB2ENSETR_SDMMC3EN_Pos)           /*!< 0x00010000 */
#define RCC_MC_AHB2ENSETR_SDMMC3EN                RCC_MC_AHB2ENSETR_SDMMC3EN_Msk                     /*!< SDMMC3 and SDMMC3 delay (DLYBSD3) block peripheral clocks enable */

/**************  Bit definition for RCC_MC_AHB2ENCLRR register  ***************/
#define RCC_MC_AHB2ENCLRR_DMA1EN_Pos              (0U)
#define RCC_MC_AHB2ENCLRR_DMA1EN_Msk              (0x1U << RCC_MC_AHB2ENCLRR_DMA1EN_Pos)             /*!< 0x00000001 */
#define RCC_MC_AHB2ENCLRR_DMA1EN                  RCC_MC_AHB2ENCLRR_DMA1EN_Msk                       /*!< DMA1 peripheral clocks enable */
#define RCC_MC_AHB2ENCLRR_DMA2EN_Pos              (1U)
#define RCC_MC_AHB2ENCLRR_DMA2EN_Msk              (0x1U << RCC_MC_AHB2ENCLRR_DMA2EN_Pos)             /*!< 0x00000002 */
#define RCC_MC_AHB2ENCLRR_DMA2EN                  RCC_MC_AHB2ENCLRR_DMA2EN_Msk                       /*!< DMA2 peripheral clocks enable */
#define RCC_MC_AHB2ENCLRR_DMAMUXEN_Pos            (2U)
#define RCC_MC_AHB2ENCLRR_DMAMUXEN_Msk            (0x1U << RCC_MC_AHB2ENCLRR_DMAMUXEN_Pos)           /*!< 0x00000004 */
#define RCC_MC_AHB2ENCLRR_DMAMUXEN                RCC_MC_AHB2ENCLRR_DMAMUXEN_Msk                     /*!< DMAMUX peripheral clocks enable */
#define RCC_MC_AHB2ENCLRR_ADC12EN_Pos             (5U)
#define RCC_MC_AHB2ENCLRR_ADC12EN_Msk             (0x1U << RCC_MC_AHB2ENCLRR_ADC12EN_Pos)            /*!< 0x00000020 */
#define RCC_MC_AHB2ENCLRR_ADC12EN                 RCC_MC_AHB2ENCLRR_ADC12EN_Msk                      /*!< ADC1&amp;2 peripheral clocks enable */
#define RCC_MC_AHB2ENCLRR_USBOEN_Pos              (8U)
#define RCC_MC_AHB2ENCLRR_USBOEN_Msk              (0x1U << RCC_MC_AHB2ENCLRR_USBOEN_Pos)             /*!< 0x00000100 */
#define RCC_MC_AHB2ENCLRR_USBOEN                  RCC_MC_AHB2ENCLRR_USBOEN_Msk                       /*!< USBO peripheral clocks enable */
#define RCC_MC_AHB2ENCLRR_SDMMC3EN_Pos            (16U)
#define RCC_MC_AHB2ENCLRR_SDMMC3EN_Msk            (0x1U << RCC_MC_AHB2ENCLRR_SDMMC3EN_Pos)           /*!< 0x00010000 */
#define RCC_MC_AHB2ENCLRR_SDMMC3EN                RCC_MC_AHB2ENCLRR_SDMMC3EN_Msk                     /*!< SDMMC3 and SDMMC3 delay (DLYBSD3) block peripheral clocks enable */

/**************  Bit definition for RCC_MC_AHB3ENSETR register  ***************/
#define RCC_MC_AHB3ENSETR_DCMIEN_Pos              (0U)
#define RCC_MC_AHB3ENSETR_DCMIEN_Msk              (0x1U << RCC_MC_AHB3ENSETR_DCMIEN_Pos)             /*!< 0x00000001 */
#define RCC_MC_AHB3ENSETR_DCMIEN                  RCC_MC_AHB3ENSETR_DCMIEN_Msk                       /*!< DCMI peripheral clocks enable */
#define RCC_MC_AHB3ENSETR_CRYP2EN_Pos             (4U)
#define RCC_MC_AHB3ENSETR_CRYP2EN_Msk             (0x1U << RCC_MC_AHB3ENSETR_CRYP2EN_Pos)            /*!< 0x00000010 */
#define RCC_MC_AHB3ENSETR_CRYP2EN                 RCC_MC_AHB3ENSETR_CRYP2EN_Msk                      /*!< CRYP2 (3DES/AES2) peripheral clocks enable */
#define RCC_MC_AHB3ENSETR_HASH2EN_Pos             (5U)
#define RCC_MC_AHB3ENSETR_HASH2EN_Msk             (0x1U << RCC_MC_AHB3ENSETR_HASH2EN_Pos)            /*!< 0x00000020 */
#define RCC_MC_AHB3ENSETR_HASH2EN                 RCC_MC_AHB3ENSETR_HASH2EN_Msk                      /*!< HASH2 peripheral clocks enable */
#define RCC_MC_AHB3ENSETR_RNG2EN_Pos              (6U)
#define RCC_MC_AHB3ENSETR_RNG2EN_Msk              (0x1U << RCC_MC_AHB3ENSETR_RNG2EN_Pos)             /*!< 0x00000040 */
#define RCC_MC_AHB3ENSETR_RNG2EN                  RCC_MC_AHB3ENSETR_RNG2EN_Msk                       /*!< RNG2 peripheral clocks enable */
#define RCC_MC_AHB3ENSETR_CRC2EN_Pos              (7U)
#define RCC_MC_AHB3ENSETR_CRC2EN_Msk              (0x1U << RCC_MC_AHB3ENSETR_CRC2EN_Pos)             /*!< 0x00000080 */
#define RCC_MC_AHB3ENSETR_CRC2EN                  RCC_MC_AHB3ENSETR_CRC2EN_Msk                       /*!< CRC2 peripheral clocks enable */
#define RCC_MC_AHB3ENSETR_HSEMEN_Pos              (11U)
#define RCC_MC_AHB3ENSETR_HSEMEN_Msk              (0x1U << RCC_MC_AHB3ENSETR_HSEMEN_Pos)             /*!< 0x00000800 */
#define RCC_MC_AHB3ENSETR_HSEMEN                  RCC_MC_AHB3ENSETR_HSEMEN_Msk                       /*!< HSEM peripheral clocks enable */
#define RCC_MC_AHB3ENSETR_IPCCEN_Pos              (12U)
#define RCC_MC_AHB3ENSETR_IPCCEN_Msk              (0x1U << RCC_MC_AHB3ENSETR_IPCCEN_Pos)             /*!< 0x00001000 */
#define RCC_MC_AHB3ENSETR_IPCCEN                  RCC_MC_AHB3ENSETR_IPCCEN_Msk                       /*!< IPCC peripheral clocks enable */

/**************  Bit definition for RCC_MC_AHB3ENCLRR register  ***************/
#define RCC_MC_AHB3ENCLRR_DCMIEN_Pos              (0U)
#define RCC_MC_AHB3ENCLRR_DCMIEN_Msk              (0x1U << RCC_MC_AHB3ENCLRR_DCMIEN_Pos)             /*!< 0x00000001 */
#define RCC_MC_AHB3ENCLRR_DCMIEN                  RCC_MC_AHB3ENCLRR_DCMIEN_Msk                       /*!< DCMI peripheral clocks enable */
#define RCC_MC_AHB3ENCLRR_CRYP2EN_Pos             (4U)
#define RCC_MC_AHB3ENCLRR_CRYP2EN_Msk             (0x1U << RCC_MC_AHB3ENCLRR_CRYP2EN_Pos)            /*!< 0x00000010 */
#define RCC_MC_AHB3ENCLRR_CRYP2EN                 RCC_MC_AHB3ENCLRR_CRYP2EN_Msk                      /*!< CRYP2 (3DES/AES2) peripheral clocks enable */
#define RCC_MC_AHB3ENCLRR_HASH2EN_Pos             (5U)
#define RCC_MC_AHB3ENCLRR_HASH2EN_Msk             (0x1U << RCC_MC_AHB3ENCLRR_HASH2EN_Pos)            /*!< 0x00000020 */
#define RCC_MC_AHB3ENCLRR_HASH2EN                 RCC_MC_AHB3ENCLRR_HASH2EN_Msk                      /*!< HASH2 peripheral clocks enable */
#define RCC_MC_AHB3ENCLRR_RNG2EN_Pos              (6U)
#define RCC_MC_AHB3ENCLRR_RNG2EN_Msk              (0x1U << RCC_MC_AHB3ENCLRR_RNG2EN_Pos)             /*!< 0x00000040 */
#define RCC_MC_AHB3ENCLRR_RNG2EN                  RCC_MC_AHB3ENCLRR_RNG2EN_Msk                       /*!< RNG2 peripheral clocks enable */
#define RCC_MC_AHB3ENCLRR_CRC2EN_Pos              (7U)
#define RCC_MC_AHB3ENCLRR_CRC2EN_Msk              (0x1U << RCC_MC_AHB3ENCLRR_CRC2EN_Pos)             /*!< 0x00000080 */
#define RCC_MC_AHB3ENCLRR_CRC2EN                  RCC_MC_AHB3ENCLRR_CRC2EN_Msk                       /*!< CRC2 peripheral clocks enable */
#define RCC_MC_AHB3ENCLRR_HSEMEN_Pos              (11U)
#define RCC_MC_AHB3ENCLRR_HSEMEN_Msk              (0x1U << RCC_MC_AHB3ENCLRR_HSEMEN_Pos)             /*!< 0x00000800 */
#define RCC_MC_AHB3ENCLRR_HSEMEN                  RCC_MC_AHB3ENCLRR_HSEMEN_Msk                       /*!< HSEM peripheral clocks enable */
#define RCC_MC_AHB3ENCLRR_IPCCEN_Pos              (12U)
#define RCC_MC_AHB3ENCLRR_IPCCEN_Msk              (0x1U << RCC_MC_AHB3ENCLRR_IPCCEN_Pos)             /*!< 0x00001000 */
#define RCC_MC_AHB3ENCLRR_IPCCEN                  RCC_MC_AHB3ENCLRR_IPCCEN_Msk                       /*!< IPCC peripheral clocks enable */

/**************  Bit definition for RCC_MC_AHB4ENSETR register  ***************/
#define RCC_MC_AHB4ENSETR_GPIOAEN_Pos             (0U)
#define RCC_MC_AHB4ENSETR_GPIOAEN_Msk             (0x1U << RCC_MC_AHB4ENSETR_GPIOAEN_Pos)            /*!< 0x00000001 */
#define RCC_MC_AHB4ENSETR_GPIOAEN                 RCC_MC_AHB4ENSETR_GPIOAEN_Msk                      /*!< GPIOA peripheral clocks enable */
#define RCC_MC_AHB4ENSETR_GPIOBEN_Pos             (1U)
#define RCC_MC_AHB4ENSETR_GPIOBEN_Msk             (0x1U << RCC_MC_AHB4ENSETR_GPIOBEN_Pos)            /*!< 0x00000002 */
#define RCC_MC_AHB4ENSETR_GPIOBEN                 RCC_MC_AHB4ENSETR_GPIOBEN_Msk                      /*!< GPIOB peripheral clocks enable */
#define RCC_MC_AHB4ENSETR_GPIOCEN_Pos             (2U)
#define RCC_MC_AHB4ENSETR_GPIOCEN_Msk             (0x1U << RCC_MC_AHB4ENSETR_GPIOCEN_Pos)            /*!< 0x00000004 */
#define RCC_MC_AHB4ENSETR_GPIOCEN                 RCC_MC_AHB4ENSETR_GPIOCEN_Msk                      /*!< GPIOC peripheral clocks enable */
#define RCC_MC_AHB4ENSETR_GPIODEN_Pos             (3U)
#define RCC_MC_AHB4ENSETR_GPIODEN_Msk             (0x1U << RCC_MC_AHB4ENSETR_GPIODEN_Pos)            /*!< 0x00000008 */
#define RCC_MC_AHB4ENSETR_GPIODEN                 RCC_MC_AHB4ENSETR_GPIODEN_Msk                      /*!< GPIOD peripheral clocks enable */
#define RCC_MC_AHB4ENSETR_GPIOEEN_Pos             (4U)
#define RCC_MC_AHB4ENSETR_GPIOEEN_Msk             (0x1U << RCC_MC_AHB4ENSETR_GPIOEEN_Pos)            /*!< 0x00000010 */
#define RCC_MC_AHB4ENSETR_GPIOEEN                 RCC_MC_AHB4ENSETR_GPIOEEN_Msk                      /*!< GPIOE peripheral clocks enable */
#define RCC_MC_AHB4ENSETR_GPIOFEN_Pos             (5U)
#define RCC_MC_AHB4ENSETR_GPIOFEN_Msk             (0x1U << RCC_MC_AHB4ENSETR_GPIOFEN_Pos)            /*!< 0x00000020 */
#define RCC_MC_AHB4ENSETR_GPIOFEN                 RCC_MC_AHB4ENSETR_GPIOFEN_Msk                      /*!< GPIOF peripheral clocks enable */
#define RCC_MC_AHB4ENSETR_GPIOGEN_Pos             (6U)
#define RCC_MC_AHB4ENSETR_GPIOGEN_Msk             (0x1U << RCC_MC_AHB4ENSETR_GPIOGEN_Pos)            /*!< 0x00000040 */
#define RCC_MC_AHB4ENSETR_GPIOGEN                 RCC_MC_AHB4ENSETR_GPIOGEN_Msk                      /*!< GPIOG peripheral clocks enable */
#define RCC_MC_AHB4ENSETR_GPIOHEN_Pos             (7U)
#define RCC_MC_AHB4ENSETR_GPIOHEN_Msk             (0x1U << RCC_MC_AHB4ENSETR_GPIOHEN_Pos)            /*!< 0x00000080 */
#define RCC_MC_AHB4ENSETR_GPIOHEN                 RCC_MC_AHB4ENSETR_GPIOHEN_Msk                      /*!< GPIOH peripheral clocks enable */
#define RCC_MC_AHB4ENSETR_GPIOIEN_Pos             (8U)
#define RCC_MC_AHB4ENSETR_GPIOIEN_Msk             (0x1U << RCC_MC_AHB4ENSETR_GPIOIEN_Pos)            /*!< 0x00000100 */
#define RCC_MC_AHB4ENSETR_GPIOIEN                 RCC_MC_AHB4ENSETR_GPIOIEN_Msk                      /*!< GPIOI peripheral clocks enable */
#define RCC_MC_AHB4ENSETR_GPIOJEN_Pos             (9U)
#define RCC_MC_AHB4ENSETR_GPIOJEN_Msk             (0x1U << RCC_MC_AHB4ENSETR_GPIOJEN_Pos)            /*!< 0x00000200 */
#define RCC_MC_AHB4ENSETR_GPIOJEN                 RCC_MC_AHB4ENSETR_GPIOJEN_Msk                      /*!< GPIOJ peripheral clocks enable */
#define RCC_MC_AHB4ENSETR_GPIOKEN_Pos             (10U)
#define RCC_MC_AHB4ENSETR_GPIOKEN_Msk             (0x1U << RCC_MC_AHB4ENSETR_GPIOKEN_Pos)            /*!< 0x00000400 */
#define RCC_MC_AHB4ENSETR_GPIOKEN                 RCC_MC_AHB4ENSETR_GPIOKEN_Msk                      /*!< GPIOK peripheral clocks enable */

/**************  Bit definition for RCC_MC_AHB4ENCLRR register  ***************/
#define RCC_MC_AHB4ENCLRR_GPIOAEN_Pos             (0U)
#define RCC_MC_AHB4ENCLRR_GPIOAEN_Msk             (0x1U << RCC_MC_AHB4ENCLRR_GPIOAEN_Pos)            /*!< 0x00000001 */
#define RCC_MC_AHB4ENCLRR_GPIOAEN                 RCC_MC_AHB4ENCLRR_GPIOAEN_Msk                      /*!< GPIOA peripheral clocks enable */
#define RCC_MC_AHB4ENCLRR_GPIOBEN_Pos             (1U)
#define RCC_MC_AHB4ENCLRR_GPIOBEN_Msk             (0x1U << RCC_MC_AHB4ENCLRR_GPIOBEN_Pos)            /*!< 0x00000002 */
#define RCC_MC_AHB4ENCLRR_GPIOBEN                 RCC_MC_AHB4ENCLRR_GPIOBEN_Msk                      /*!< GPIOB peripheral clocks enable */
#define RCC_MC_AHB4ENCLRR_GPIOCEN_Pos             (2U)
#define RCC_MC_AHB4ENCLRR_GPIOCEN_Msk             (0x1U << RCC_MC_AHB4ENCLRR_GPIOCEN_Pos)            /*!< 0x00000004 */
#define RCC_MC_AHB4ENCLRR_GPIOCEN                 RCC_MC_AHB4ENCLRR_GPIOCEN_Msk                      /*!< GPIOC peripheral clocks enable */
#define RCC_MC_AHB4ENCLRR_GPIODEN_Pos             (3U)
#define RCC_MC_AHB4ENCLRR_GPIODEN_Msk             (0x1U << RCC_MC_AHB4ENCLRR_GPIODEN_Pos)            /*!< 0x00000008 */
#define RCC_MC_AHB4ENCLRR_GPIODEN                 RCC_MC_AHB4ENCLRR_GPIODEN_Msk                      /*!< GPIOD peripheral clocks enable */
#define RCC_MC_AHB4ENCLRR_GPIOEEN_Pos             (4U)
#define RCC_MC_AHB4ENCLRR_GPIOEEN_Msk             (0x1U << RCC_MC_AHB4ENCLRR_GPIOEEN_Pos)            /*!< 0x00000010 */
#define RCC_MC_AHB4ENCLRR_GPIOEEN                 RCC_MC_AHB4ENCLRR_GPIOEEN_Msk                      /*!< GPIOE peripheral clocks enable */
#define RCC_MC_AHB4ENCLRR_GPIOFEN_Pos             (5U)
#define RCC_MC_AHB4ENCLRR_GPIOFEN_Msk             (0x1U << RCC_MC_AHB4ENCLRR_GPIOFEN_Pos)            /*!< 0x00000020 */
#define RCC_MC_AHB4ENCLRR_GPIOFEN                 RCC_MC_AHB4ENCLRR_GPIOFEN_Msk                      /*!< GPIOF peripheral clocks enable */
#define RCC_MC_AHB4ENCLRR_GPIOGEN_Pos             (6U)
#define RCC_MC_AHB4ENCLRR_GPIOGEN_Msk             (0x1U << RCC_MC_AHB4ENCLRR_GPIOGEN_Pos)            /*!< 0x00000040 */
#define RCC_MC_AHB4ENCLRR_GPIOGEN                 RCC_MC_AHB4ENCLRR_GPIOGEN_Msk                      /*!< GPIOG peripheral clocks enable */
#define RCC_MC_AHB4ENCLRR_GPIOHEN_Pos             (7U)
#define RCC_MC_AHB4ENCLRR_GPIOHEN_Msk             (0x1U << RCC_MC_AHB4ENCLRR_GPIOHEN_Pos)            /*!< 0x00000080 */
#define RCC_MC_AHB4ENCLRR_GPIOHEN                 RCC_MC_AHB4ENCLRR_GPIOHEN_Msk                      /*!< GPIOH peripheral clocks enable */
#define RCC_MC_AHB4ENCLRR_GPIOIEN_Pos             (8U)
#define RCC_MC_AHB4ENCLRR_GPIOIEN_Msk             (0x1U << RCC_MC_AHB4ENCLRR_GPIOIEN_Pos)            /*!< 0x00000100 */
#define RCC_MC_AHB4ENCLRR_GPIOIEN                 RCC_MC_AHB4ENCLRR_GPIOIEN_Msk                      /*!< GPIOI peripheral clocks enable */
#define RCC_MC_AHB4ENCLRR_GPIOJEN_Pos             (9U)
#define RCC_MC_AHB4ENCLRR_GPIOJEN_Msk             (0x1U << RCC_MC_AHB4ENCLRR_GPIOJEN_Pos)            /*!< 0x00000200 */
#define RCC_MC_AHB4ENCLRR_GPIOJEN                 RCC_MC_AHB4ENCLRR_GPIOJEN_Msk                      /*!< GPIOJ peripheral clocks enable */
#define RCC_MC_AHB4ENCLRR_GPIOKEN_Pos             (10U)
#define RCC_MC_AHB4ENCLRR_GPIOKEN_Msk             (0x1U << RCC_MC_AHB4ENCLRR_GPIOKEN_Pos)            /*!< 0x00000400 */
#define RCC_MC_AHB4ENCLRR_GPIOKEN                 RCC_MC_AHB4ENCLRR_GPIOKEN_Msk                      /*!< GPIOK peripheral clocks enable */

/**************  Bit definition for RCC_MC_AXIMENSETR register  ***************/
#define RCC_MC_AXIMENSETR_SYSRAMEN_Pos            (0U)
#define RCC_MC_AXIMENSETR_SYSRAMEN_Msk            (0x1U << RCC_MC_AXIMENSETR_SYSRAMEN_Pos)           /*!< 0x00000001 */
#define RCC_MC_AXIMENSETR_SYSRAMEN                RCC_MC_AXIMENSETR_SYSRAMEN_Msk                     /*!< SYSRAM peripheral clocks enable */

/**************  Bit definition for RCC_MC_AXIMENCLRR register  ***************/
#define RCC_MC_AXIMENCLRR_SYSRAMEN_Pos            (0U)
#define RCC_MC_AXIMENCLRR_SYSRAMEN_Msk            (0x1U << RCC_MC_AXIMENCLRR_SYSRAMEN_Pos)           /*!< 0x00000001 */
#define RCC_MC_AXIMENCLRR_SYSRAMEN                RCC_MC_AXIMENCLRR_SYSRAMEN_Msk                     /*!< SYSRAM peripheral clocks enable */

/**************  Bit definition for RCC_MC_MLAHBENSETR register  **************/
#define RCC_MC_MLAHBENSETR_RETRAMEN_Pos           (4U)
#define RCC_MC_MLAHBENSETR_RETRAMEN_Msk           (0x1U << RCC_MC_MLAHBENSETR_RETRAMEN_Pos)          /*!< 0x00000010 */
#define RCC_MC_MLAHBENSETR_RETRAMEN               RCC_MC_MLAHBENSETR_RETRAMEN_Msk                    /*!< RETRAM peripheral clocks enable */

/**************  Bit definition for RCC_MC_MLAHBENCLRR register  **************/
#define RCC_MC_MLAHBENCLRR_RETRAMEN_Pos           (4U)
#define RCC_MC_MLAHBENCLRR_RETRAMEN_Msk           (0x1U << RCC_MC_MLAHBENCLRR_RETRAMEN_Pos)          /*!< 0x00000010 */
#define RCC_MC_MLAHBENCLRR_RETRAMEN               RCC_MC_MLAHBENCLRR_RETRAMEN_Msk                    /*!< RETRAM peripheral clocks enable */

/*************  Bit definition for RCC_MP_APB1LPENSETR register  **************/
#define RCC_MP_APB1LPENSETR_TIM2LPEN_Pos          (0U)
#define RCC_MP_APB1LPENSETR_TIM2LPEN_Msk          (0x1U << RCC_MP_APB1LPENSETR_TIM2LPEN_Pos)         /*!< 0x00000001 */
#define RCC_MP_APB1LPENSETR_TIM2LPEN              RCC_MP_APB1LPENSETR_TIM2LPEN_Msk                   /*!< TIM2 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_TIM3LPEN_Pos          (1U)
#define RCC_MP_APB1LPENSETR_TIM3LPEN_Msk          (0x1U << RCC_MP_APB1LPENSETR_TIM3LPEN_Pos)         /*!< 0x00000002 */
#define RCC_MP_APB1LPENSETR_TIM3LPEN              RCC_MP_APB1LPENSETR_TIM3LPEN_Msk                   /*!< TIM3 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_TIM4LPEN_Pos          (2U)
#define RCC_MP_APB1LPENSETR_TIM4LPEN_Msk          (0x1U << RCC_MP_APB1LPENSETR_TIM4LPEN_Pos)         /*!< 0x00000004 */
#define RCC_MP_APB1LPENSETR_TIM4LPEN              RCC_MP_APB1LPENSETR_TIM4LPEN_Msk                   /*!< TIM4 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_TIM5LPEN_Pos          (3U)
#define RCC_MP_APB1LPENSETR_TIM5LPEN_Msk          (0x1U << RCC_MP_APB1LPENSETR_TIM5LPEN_Pos)         /*!< 0x00000008 */
#define RCC_MP_APB1LPENSETR_TIM5LPEN              RCC_MP_APB1LPENSETR_TIM5LPEN_Msk                   /*!< TIM5 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_TIM6LPEN_Pos          (4U)
#define RCC_MP_APB1LPENSETR_TIM6LPEN_Msk          (0x1U << RCC_MP_APB1LPENSETR_TIM6LPEN_Pos)         /*!< 0x00000010 */
#define RCC_MP_APB1LPENSETR_TIM6LPEN              RCC_MP_APB1LPENSETR_TIM6LPEN_Msk                   /*!< TIM6 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_TIM7LPEN_Pos          (5U)
#define RCC_MP_APB1LPENSETR_TIM7LPEN_Msk          (0x1U << RCC_MP_APB1LPENSETR_TIM7LPEN_Pos)         /*!< 0x00000020 */
#define RCC_MP_APB1LPENSETR_TIM7LPEN              RCC_MP_APB1LPENSETR_TIM7LPEN_Msk                   /*!< TIM7 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_TIM12LPEN_Pos         (6U)
#define RCC_MP_APB1LPENSETR_TIM12LPEN_Msk         (0x1U << RCC_MP_APB1LPENSETR_TIM12LPEN_Pos)        /*!< 0x00000040 */
#define RCC_MP_APB1LPENSETR_TIM12LPEN             RCC_MP_APB1LPENSETR_TIM12LPEN_Msk                  /*!< TIM12 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_TIM13LPEN_Pos         (7U)
#define RCC_MP_APB1LPENSETR_TIM13LPEN_Msk         (0x1U << RCC_MP_APB1LPENSETR_TIM13LPEN_Pos)        /*!< 0x00000080 */
#define RCC_MP_APB1LPENSETR_TIM13LPEN             RCC_MP_APB1LPENSETR_TIM13LPEN_Msk                  /*!< TIM13 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_TIM14LPEN_Pos         (8U)
#define RCC_MP_APB1LPENSETR_TIM14LPEN_Msk         (0x1U << RCC_MP_APB1LPENSETR_TIM14LPEN_Pos)        /*!< 0x00000100 */
#define RCC_MP_APB1LPENSETR_TIM14LPEN             RCC_MP_APB1LPENSETR_TIM14LPEN_Msk                  /*!< TIM14 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_LPTIM1LPEN_Pos        (9U)
#define RCC_MP_APB1LPENSETR_LPTIM1LPEN_Msk        (0x1U << RCC_MP_APB1LPENSETR_LPTIM1LPEN_Pos)       /*!< 0x00000200 */
#define RCC_MP_APB1LPENSETR_LPTIM1LPEN            RCC_MP_APB1LPENSETR_LPTIM1LPEN_Msk                 /*!< LPTIM1 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_SPI2LPEN_Pos          (11U)
#define RCC_MP_APB1LPENSETR_SPI2LPEN_Msk          (0x1U << RCC_MP_APB1LPENSETR_SPI2LPEN_Pos)         /*!< 0x00000800 */
#define RCC_MP_APB1LPENSETR_SPI2LPEN              RCC_MP_APB1LPENSETR_SPI2LPEN_Msk                   /*!< SPI2 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_SPI3LPEN_Pos          (12U)
#define RCC_MP_APB1LPENSETR_SPI3LPEN_Msk          (0x1U << RCC_MP_APB1LPENSETR_SPI3LPEN_Pos)         /*!< 0x00001000 */
#define RCC_MP_APB1LPENSETR_SPI3LPEN              RCC_MP_APB1LPENSETR_SPI3LPEN_Msk                   /*!< SPI3 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_USART2LPEN_Pos        (14U)
#define RCC_MP_APB1LPENSETR_USART2LPEN_Msk        (0x1U << RCC_MP_APB1LPENSETR_USART2LPEN_Pos)       /*!< 0x00004000 */
#define RCC_MP_APB1LPENSETR_USART2LPEN            RCC_MP_APB1LPENSETR_USART2LPEN_Msk                 /*!< USART2 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_USART3LPEN_Pos        (15U)
#define RCC_MP_APB1LPENSETR_USART3LPEN_Msk        (0x1U << RCC_MP_APB1LPENSETR_USART3LPEN_Pos)       /*!< 0x00008000 */
#define RCC_MP_APB1LPENSETR_USART3LPEN            RCC_MP_APB1LPENSETR_USART3LPEN_Msk                 /*!< USART3 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_UART4LPEN_Pos         (16U)
#define RCC_MP_APB1LPENSETR_UART4LPEN_Msk         (0x1U << RCC_MP_APB1LPENSETR_UART4LPEN_Pos)        /*!< 0x00010000 */
#define RCC_MP_APB1LPENSETR_UART4LPEN             RCC_MP_APB1LPENSETR_UART4LPEN_Msk                  /*!< UART4 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_UART5LPEN_Pos         (17U)
#define RCC_MP_APB1LPENSETR_UART5LPEN_Msk         (0x1U << RCC_MP_APB1LPENSETR_UART5LPEN_Pos)        /*!< 0x00020000 */
#define RCC_MP_APB1LPENSETR_UART5LPEN             RCC_MP_APB1LPENSETR_UART5LPEN_Msk                  /*!< UART5 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_UART7LPEN_Pos         (18U)
#define RCC_MP_APB1LPENSETR_UART7LPEN_Msk         (0x1U << RCC_MP_APB1LPENSETR_UART7LPEN_Pos)        /*!< 0x00040000 */
#define RCC_MP_APB1LPENSETR_UART7LPEN             RCC_MP_APB1LPENSETR_UART7LPEN_Msk                  /*!< UART7 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_UART8LPEN_Pos         (19U)
#define RCC_MP_APB1LPENSETR_UART8LPEN_Msk         (0x1U << RCC_MP_APB1LPENSETR_UART8LPEN_Pos)        /*!< 0x00080000 */
#define RCC_MP_APB1LPENSETR_UART8LPEN             RCC_MP_APB1LPENSETR_UART8LPEN_Msk                  /*!< UART8 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_I2C1LPEN_Pos          (21U)
#define RCC_MP_APB1LPENSETR_I2C1LPEN_Msk          (0x1U << RCC_MP_APB1LPENSETR_I2C1LPEN_Pos)         /*!< 0x00200000 */
#define RCC_MP_APB1LPENSETR_I2C1LPEN              RCC_MP_APB1LPENSETR_I2C1LPEN_Msk                   /*!< I2C1 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_I2C2LPEN_Pos          (22U)
#define RCC_MP_APB1LPENSETR_I2C2LPEN_Msk          (0x1U << RCC_MP_APB1LPENSETR_I2C2LPEN_Pos)         /*!< 0x00400000 */
#define RCC_MP_APB1LPENSETR_I2C2LPEN              RCC_MP_APB1LPENSETR_I2C2LPEN_Msk                   /*!< I2C2 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_I2C3LPEN_Pos          (23U)
#define RCC_MP_APB1LPENSETR_I2C3LPEN_Msk          (0x1U << RCC_MP_APB1LPENSETR_I2C3LPEN_Pos)         /*!< 0x00800000 */
#define RCC_MP_APB1LPENSETR_I2C3LPEN              RCC_MP_APB1LPENSETR_I2C3LPEN_Msk                   /*!< I2C3 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_I2C5LPEN_Pos          (24U)
#define RCC_MP_APB1LPENSETR_I2C5LPEN_Msk          (0x1U << RCC_MP_APB1LPENSETR_I2C5LPEN_Pos)         /*!< 0x01000000 */
#define RCC_MP_APB1LPENSETR_I2C5LPEN              RCC_MP_APB1LPENSETR_I2C5LPEN_Msk                   /*!< I2C5 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_SPDIFLPEN_Pos         (26U)
#define RCC_MP_APB1LPENSETR_SPDIFLPEN_Msk         (0x1U << RCC_MP_APB1LPENSETR_SPDIFLPEN_Pos)        /*!< 0x04000000 */
#define RCC_MP_APB1LPENSETR_SPDIFLPEN             RCC_MP_APB1LPENSETR_SPDIFLPEN_Msk                  /*!< SPDIFRX peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_CECLPEN_Pos           (27U)
#define RCC_MP_APB1LPENSETR_CECLPEN_Msk           (0x1U << RCC_MP_APB1LPENSETR_CECLPEN_Pos)          /*!< 0x08000000 */
#define RCC_MP_APB1LPENSETR_CECLPEN               RCC_MP_APB1LPENSETR_CECLPEN_Msk                    /*!< HDMI-CEC peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_DAC12LPEN_Pos         (29U)
#define RCC_MP_APB1LPENSETR_DAC12LPEN_Msk         (0x1U << RCC_MP_APB1LPENSETR_DAC12LPEN_Pos)        /*!< 0x20000000 */
#define RCC_MP_APB1LPENSETR_DAC12LPEN             RCC_MP_APB1LPENSETR_DAC12LPEN_Msk                  /*!< DAC1&amp;2 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENSETR_MDIOSLPEN_Pos         (31U)
#define RCC_MP_APB1LPENSETR_MDIOSLPEN_Msk         (0x1U << RCC_MP_APB1LPENSETR_MDIOSLPEN_Pos)        /*!< 0x80000000 */
#define RCC_MP_APB1LPENSETR_MDIOSLPEN             RCC_MP_APB1LPENSETR_MDIOSLPEN_Msk                  /*!< MDIOS peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MP_APB1LPENCLRR register  **************/
#define RCC_MP_APB1LPENCLRR_TIM2LPEN_Pos          (0U)
#define RCC_MP_APB1LPENCLRR_TIM2LPEN_Msk          (0x1U << RCC_MP_APB1LPENCLRR_TIM2LPEN_Pos)         /*!< 0x00000001 */
#define RCC_MP_APB1LPENCLRR_TIM2LPEN              RCC_MP_APB1LPENCLRR_TIM2LPEN_Msk                   /*!< TIM2 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_TIM3LPEN_Pos          (1U)
#define RCC_MP_APB1LPENCLRR_TIM3LPEN_Msk          (0x1U << RCC_MP_APB1LPENCLRR_TIM3LPEN_Pos)         /*!< 0x00000002 */
#define RCC_MP_APB1LPENCLRR_TIM3LPEN              RCC_MP_APB1LPENCLRR_TIM3LPEN_Msk                   /*!< TIM3 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_TIM4LPEN_Pos          (2U)
#define RCC_MP_APB1LPENCLRR_TIM4LPEN_Msk          (0x1U << RCC_MP_APB1LPENCLRR_TIM4LPEN_Pos)         /*!< 0x00000004 */
#define RCC_MP_APB1LPENCLRR_TIM4LPEN              RCC_MP_APB1LPENCLRR_TIM4LPEN_Msk                   /*!< TIM4 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_TIM5LPEN_Pos          (3U)
#define RCC_MP_APB1LPENCLRR_TIM5LPEN_Msk          (0x1U << RCC_MP_APB1LPENCLRR_TIM5LPEN_Pos)         /*!< 0x00000008 */
#define RCC_MP_APB1LPENCLRR_TIM5LPEN              RCC_MP_APB1LPENCLRR_TIM5LPEN_Msk                   /*!< TIM5 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_TIM6LPEN_Pos          (4U)
#define RCC_MP_APB1LPENCLRR_TIM6LPEN_Msk          (0x1U << RCC_MP_APB1LPENCLRR_TIM6LPEN_Pos)         /*!< 0x00000010 */
#define RCC_MP_APB1LPENCLRR_TIM6LPEN              RCC_MP_APB1LPENCLRR_TIM6LPEN_Msk                   /*!< TIM6 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_TIM7LPEN_Pos          (5U)
#define RCC_MP_APB1LPENCLRR_TIM7LPEN_Msk          (0x1U << RCC_MP_APB1LPENCLRR_TIM7LPEN_Pos)         /*!< 0x00000020 */
#define RCC_MP_APB1LPENCLRR_TIM7LPEN              RCC_MP_APB1LPENCLRR_TIM7LPEN_Msk                   /*!< TIM7 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_TIM12LPEN_Pos         (6U)
#define RCC_MP_APB1LPENCLRR_TIM12LPEN_Msk         (0x1U << RCC_MP_APB1LPENCLRR_TIM12LPEN_Pos)        /*!< 0x00000040 */
#define RCC_MP_APB1LPENCLRR_TIM12LPEN             RCC_MP_APB1LPENCLRR_TIM12LPEN_Msk                  /*!< TIM12 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_TIM13LPEN_Pos         (7U)
#define RCC_MP_APB1LPENCLRR_TIM13LPEN_Msk         (0x1U << RCC_MP_APB1LPENCLRR_TIM13LPEN_Pos)        /*!< 0x00000080 */
#define RCC_MP_APB1LPENCLRR_TIM13LPEN             RCC_MP_APB1LPENCLRR_TIM13LPEN_Msk                  /*!< TIM13 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_TIM14LPEN_Pos         (8U)
#define RCC_MP_APB1LPENCLRR_TIM14LPEN_Msk         (0x1U << RCC_MP_APB1LPENCLRR_TIM14LPEN_Pos)        /*!< 0x00000100 */
#define RCC_MP_APB1LPENCLRR_TIM14LPEN             RCC_MP_APB1LPENCLRR_TIM14LPEN_Msk                  /*!< TIM14 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_LPTIM1LPEN_Pos        (9U)
#define RCC_MP_APB1LPENCLRR_LPTIM1LPEN_Msk        (0x1U << RCC_MP_APB1LPENCLRR_LPTIM1LPEN_Pos)       /*!< 0x00000200 */
#define RCC_MP_APB1LPENCLRR_LPTIM1LPEN            RCC_MP_APB1LPENCLRR_LPTIM1LPEN_Msk                 /*!< LPTIM1 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_SPI2LPEN_Pos          (11U)
#define RCC_MP_APB1LPENCLRR_SPI2LPEN_Msk          (0x1U << RCC_MP_APB1LPENCLRR_SPI2LPEN_Pos)         /*!< 0x00000800 */
#define RCC_MP_APB1LPENCLRR_SPI2LPEN              RCC_MP_APB1LPENCLRR_SPI2LPEN_Msk                   /*!< SPI2 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_SPI3LPEN_Pos          (12U)
#define RCC_MP_APB1LPENCLRR_SPI3LPEN_Msk          (0x1U << RCC_MP_APB1LPENCLRR_SPI3LPEN_Pos)         /*!< 0x00001000 */
#define RCC_MP_APB1LPENCLRR_SPI3LPEN              RCC_MP_APB1LPENCLRR_SPI3LPEN_Msk                   /*!< SPI3 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_USART2LPEN_Pos        (14U)
#define RCC_MP_APB1LPENCLRR_USART2LPEN_Msk        (0x1U << RCC_MP_APB1LPENCLRR_USART2LPEN_Pos)       /*!< 0x00004000 */
#define RCC_MP_APB1LPENCLRR_USART2LPEN            RCC_MP_APB1LPENCLRR_USART2LPEN_Msk                 /*!< USART2 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_USART3LPEN_Pos        (15U)
#define RCC_MP_APB1LPENCLRR_USART3LPEN_Msk        (0x1U << RCC_MP_APB1LPENCLRR_USART3LPEN_Pos)       /*!< 0x00008000 */
#define RCC_MP_APB1LPENCLRR_USART3LPEN            RCC_MP_APB1LPENCLRR_USART3LPEN_Msk                 /*!< USART3 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_UART4LPEN_Pos         (16U)
#define RCC_MP_APB1LPENCLRR_UART4LPEN_Msk         (0x1U << RCC_MP_APB1LPENCLRR_UART4LPEN_Pos)        /*!< 0x00010000 */
#define RCC_MP_APB1LPENCLRR_UART4LPEN             RCC_MP_APB1LPENCLRR_UART4LPEN_Msk                  /*!< UART4 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_UART5LPEN_Pos         (17U)
#define RCC_MP_APB1LPENCLRR_UART5LPEN_Msk         (0x1U << RCC_MP_APB1LPENCLRR_UART5LPEN_Pos)        /*!< 0x00020000 */
#define RCC_MP_APB1LPENCLRR_UART5LPEN             RCC_MP_APB1LPENCLRR_UART5LPEN_Msk                  /*!< UART5 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_UART7LPEN_Pos         (18U)
#define RCC_MP_APB1LPENCLRR_UART7LPEN_Msk         (0x1U << RCC_MP_APB1LPENCLRR_UART7LPEN_Pos)        /*!< 0x00040000 */
#define RCC_MP_APB1LPENCLRR_UART7LPEN             RCC_MP_APB1LPENCLRR_UART7LPEN_Msk                  /*!< UART7 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_UART8LPEN_Pos         (19U)
#define RCC_MP_APB1LPENCLRR_UART8LPEN_Msk         (0x1U << RCC_MP_APB1LPENCLRR_UART8LPEN_Pos)        /*!< 0x00080000 */
#define RCC_MP_APB1LPENCLRR_UART8LPEN             RCC_MP_APB1LPENCLRR_UART8LPEN_Msk                  /*!< UART8 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_I2C1LPEN_Pos          (21U)
#define RCC_MP_APB1LPENCLRR_I2C1LPEN_Msk          (0x1U << RCC_MP_APB1LPENCLRR_I2C1LPEN_Pos)         /*!< 0x00200000 */
#define RCC_MP_APB1LPENCLRR_I2C1LPEN              RCC_MP_APB1LPENCLRR_I2C1LPEN_Msk                   /*!< I2C1 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_I2C2LPEN_Pos          (22U)
#define RCC_MP_APB1LPENCLRR_I2C2LPEN_Msk          (0x1U << RCC_MP_APB1LPENCLRR_I2C2LPEN_Pos)         /*!< 0x00400000 */
#define RCC_MP_APB1LPENCLRR_I2C2LPEN              RCC_MP_APB1LPENCLRR_I2C2LPEN_Msk                   /*!< I2C2 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_I2C3LPEN_Pos          (23U)
#define RCC_MP_APB1LPENCLRR_I2C3LPEN_Msk          (0x1U << RCC_MP_APB1LPENCLRR_I2C3LPEN_Pos)         /*!< 0x00800000 */
#define RCC_MP_APB1LPENCLRR_I2C3LPEN              RCC_MP_APB1LPENCLRR_I2C3LPEN_Msk                   /*!< I2C3 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_I2C5LPEN_Pos          (24U)
#define RCC_MP_APB1LPENCLRR_I2C5LPEN_Msk          (0x1U << RCC_MP_APB1LPENCLRR_I2C5LPEN_Pos)         /*!< 0x01000000 */
#define RCC_MP_APB1LPENCLRR_I2C5LPEN              RCC_MP_APB1LPENCLRR_I2C5LPEN_Msk                   /*!< I2C5 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_SPDIFLPEN_Pos         (26U)
#define RCC_MP_APB1LPENCLRR_SPDIFLPEN_Msk         (0x1U << RCC_MP_APB1LPENCLRR_SPDIFLPEN_Pos)        /*!< 0x04000000 */
#define RCC_MP_APB1LPENCLRR_SPDIFLPEN             RCC_MP_APB1LPENCLRR_SPDIFLPEN_Msk                  /*!< SPDIFRX peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_CECLPEN_Pos           (27U)
#define RCC_MP_APB1LPENCLRR_CECLPEN_Msk           (0x1U << RCC_MP_APB1LPENCLRR_CECLPEN_Pos)          /*!< 0x08000000 */
#define RCC_MP_APB1LPENCLRR_CECLPEN               RCC_MP_APB1LPENCLRR_CECLPEN_Msk                    /*!< HDMI-CEC peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_DAC12LPEN_Pos         (29U)
#define RCC_MP_APB1LPENCLRR_DAC12LPEN_Msk         (0x1U << RCC_MP_APB1LPENCLRR_DAC12LPEN_Pos)        /*!< 0x20000000 */
#define RCC_MP_APB1LPENCLRR_DAC12LPEN             RCC_MP_APB1LPENCLRR_DAC12LPEN_Msk                  /*!< DAC1&amp;2 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB1LPENCLRR_MDIOSLPEN_Pos         (31U)
#define RCC_MP_APB1LPENCLRR_MDIOSLPEN_Msk         (0x1U << RCC_MP_APB1LPENCLRR_MDIOSLPEN_Pos)        /*!< 0x80000000 */
#define RCC_MP_APB1LPENCLRR_MDIOSLPEN             RCC_MP_APB1LPENCLRR_MDIOSLPEN_Msk                  /*!< MDIOS peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MP_APB2LPENSETR register  **************/
#define RCC_MP_APB2LPENSETR_TIM1LPEN_Pos          (0U)
#define RCC_MP_APB2LPENSETR_TIM1LPEN_Msk          (0x1U << RCC_MP_APB2LPENSETR_TIM1LPEN_Pos)         /*!< 0x00000001 */
#define RCC_MP_APB2LPENSETR_TIM1LPEN              RCC_MP_APB2LPENSETR_TIM1LPEN_Msk                   /*!< TIM1 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENSETR_TIM8LPEN_Pos          (1U)
#define RCC_MP_APB2LPENSETR_TIM8LPEN_Msk          (0x1U << RCC_MP_APB2LPENSETR_TIM8LPEN_Pos)         /*!< 0x00000002 */
#define RCC_MP_APB2LPENSETR_TIM8LPEN              RCC_MP_APB2LPENSETR_TIM8LPEN_Msk                   /*!< TIM8 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENSETR_TIM15LPEN_Pos         (2U)
#define RCC_MP_APB2LPENSETR_TIM15LPEN_Msk         (0x1U << RCC_MP_APB2LPENSETR_TIM15LPEN_Pos)        /*!< 0x00000004 */
#define RCC_MP_APB2LPENSETR_TIM15LPEN             RCC_MP_APB2LPENSETR_TIM15LPEN_Msk                  /*!< TIM15 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENSETR_TIM16LPEN_Pos         (3U)
#define RCC_MP_APB2LPENSETR_TIM16LPEN_Msk         (0x1U << RCC_MP_APB2LPENSETR_TIM16LPEN_Pos)        /*!< 0x00000008 */
#define RCC_MP_APB2LPENSETR_TIM16LPEN             RCC_MP_APB2LPENSETR_TIM16LPEN_Msk                  /*!< TIM16 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENSETR_TIM17LPEN_Pos         (4U)
#define RCC_MP_APB2LPENSETR_TIM17LPEN_Msk         (0x1U << RCC_MP_APB2LPENSETR_TIM17LPEN_Pos)        /*!< 0x00000010 */
#define RCC_MP_APB2LPENSETR_TIM17LPEN             RCC_MP_APB2LPENSETR_TIM17LPEN_Msk                  /*!< TIM17 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENSETR_SPI1LPEN_Pos          (8U)
#define RCC_MP_APB2LPENSETR_SPI1LPEN_Msk          (0x1U << RCC_MP_APB2LPENSETR_SPI1LPEN_Pos)         /*!< 0x00000100 */
#define RCC_MP_APB2LPENSETR_SPI1LPEN              RCC_MP_APB2LPENSETR_SPI1LPEN_Msk                   /*!< SPI/I2S1 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENSETR_SPI4LPEN_Pos          (9U)
#define RCC_MP_APB2LPENSETR_SPI4LPEN_Msk          (0x1U << RCC_MP_APB2LPENSETR_SPI4LPEN_Pos)         /*!< 0x00000200 */
#define RCC_MP_APB2LPENSETR_SPI4LPEN              RCC_MP_APB2LPENSETR_SPI4LPEN_Msk                   /*!< SPI4 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENSETR_SPI5LPEN_Pos          (10U)
#define RCC_MP_APB2LPENSETR_SPI5LPEN_Msk          (0x1U << RCC_MP_APB2LPENSETR_SPI5LPEN_Pos)         /*!< 0x00000400 */
#define RCC_MP_APB2LPENSETR_SPI5LPEN              RCC_MP_APB2LPENSETR_SPI5LPEN_Msk                   /*!< SPI5 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENSETR_USART6LPEN_Pos        (13U)
#define RCC_MP_APB2LPENSETR_USART6LPEN_Msk        (0x1U << RCC_MP_APB2LPENSETR_USART6LPEN_Pos)       /*!< 0x00002000 */
#define RCC_MP_APB2LPENSETR_USART6LPEN            RCC_MP_APB2LPENSETR_USART6LPEN_Msk                 /*!< USART6 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENSETR_SAI1LPEN_Pos          (16U)
#define RCC_MP_APB2LPENSETR_SAI1LPEN_Msk          (0x1U << RCC_MP_APB2LPENSETR_SAI1LPEN_Pos)         /*!< 0x00010000 */
#define RCC_MP_APB2LPENSETR_SAI1LPEN              RCC_MP_APB2LPENSETR_SAI1LPEN_Msk                   /*!< SAI1 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENSETR_SAI2LPEN_Pos          (17U)
#define RCC_MP_APB2LPENSETR_SAI2LPEN_Msk          (0x1U << RCC_MP_APB2LPENSETR_SAI2LPEN_Pos)         /*!< 0x00020000 */
#define RCC_MP_APB2LPENSETR_SAI2LPEN              RCC_MP_APB2LPENSETR_SAI2LPEN_Msk                   /*!< SAI2 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENSETR_SAI3LPEN_Pos          (18U)
#define RCC_MP_APB2LPENSETR_SAI3LPEN_Msk          (0x1U << RCC_MP_APB2LPENSETR_SAI3LPEN_Pos)         /*!< 0x00040000 */
#define RCC_MP_APB2LPENSETR_SAI3LPEN              RCC_MP_APB2LPENSETR_SAI3LPEN_Msk                   /*!< SAI3 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENSETR_DFSDMLPEN_Pos         (20U)
#define RCC_MP_APB2LPENSETR_DFSDMLPEN_Msk         (0x1U << RCC_MP_APB2LPENSETR_DFSDMLPEN_Pos)        /*!< 0x00100000 */
#define RCC_MP_APB2LPENSETR_DFSDMLPEN             RCC_MP_APB2LPENSETR_DFSDMLPEN_Msk                  /*!< DFSDM peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENSETR_ADFSDMLPEN_Pos        (21U)
#define RCC_MP_APB2LPENSETR_ADFSDMLPEN_Msk        (0x1U << RCC_MP_APB2LPENSETR_ADFSDMLPEN_Pos)       /*!< 0x00200000 */
#define RCC_MP_APB2LPENSETR_ADFSDMLPEN            RCC_MP_APB2LPENSETR_ADFSDMLPEN_Msk                 /*!< Audio DFSDM peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENSETR_FDCANLPEN_Pos         (24U)
#define RCC_MP_APB2LPENSETR_FDCANLPEN_Msk         (0x1U << RCC_MP_APB2LPENSETR_FDCANLPEN_Pos)        /*!< 0x01000000 */
#define RCC_MP_APB2LPENSETR_FDCANLPEN             RCC_MP_APB2LPENSETR_FDCANLPEN_Msk                  /*!< FDCAN and CANRAM peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MP_APB2LPENCLRR register  **************/
#define RCC_MP_APB2LPENCLRR_TIM1LPEN_Pos          (0U)
#define RCC_MP_APB2LPENCLRR_TIM1LPEN_Msk          (0x1U << RCC_MP_APB2LPENCLRR_TIM1LPEN_Pos)         /*!< 0x00000001 */
#define RCC_MP_APB2LPENCLRR_TIM1LPEN              RCC_MP_APB2LPENCLRR_TIM1LPEN_Msk                   /*!< TIM1 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENCLRR_TIM8LPEN_Pos          (1U)
#define RCC_MP_APB2LPENCLRR_TIM8LPEN_Msk          (0x1U << RCC_MP_APB2LPENCLRR_TIM8LPEN_Pos)         /*!< 0x00000002 */
#define RCC_MP_APB2LPENCLRR_TIM8LPEN              RCC_MP_APB2LPENCLRR_TIM8LPEN_Msk                   /*!< TIM8 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENCLRR_TIM15LPEN_Pos         (2U)
#define RCC_MP_APB2LPENCLRR_TIM15LPEN_Msk         (0x1U << RCC_MP_APB2LPENCLRR_TIM15LPEN_Pos)        /*!< 0x00000004 */
#define RCC_MP_APB2LPENCLRR_TIM15LPEN             RCC_MP_APB2LPENCLRR_TIM15LPEN_Msk                  /*!< TIM15 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENCLRR_TIM16LPEN_Pos         (3U)
#define RCC_MP_APB2LPENCLRR_TIM16LPEN_Msk         (0x1U << RCC_MP_APB2LPENCLRR_TIM16LPEN_Pos)        /*!< 0x00000008 */
#define RCC_MP_APB2LPENCLRR_TIM16LPEN             RCC_MP_APB2LPENCLRR_TIM16LPEN_Msk                  /*!< TIM16 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENCLRR_TIM17LPEN_Pos         (4U)
#define RCC_MP_APB2LPENCLRR_TIM17LPEN_Msk         (0x1U << RCC_MP_APB2LPENCLRR_TIM17LPEN_Pos)        /*!< 0x00000010 */
#define RCC_MP_APB2LPENCLRR_TIM17LPEN             RCC_MP_APB2LPENCLRR_TIM17LPEN_Msk                  /*!< TIM17 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENCLRR_SPI1LPEN_Pos          (8U)
#define RCC_MP_APB2LPENCLRR_SPI1LPEN_Msk          (0x1U << RCC_MP_APB2LPENCLRR_SPI1LPEN_Pos)         /*!< 0x00000100 */
#define RCC_MP_APB2LPENCLRR_SPI1LPEN              RCC_MP_APB2LPENCLRR_SPI1LPEN_Msk                   /*!< SPI/I2S1 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENCLRR_SPI4LPEN_Pos          (9U)
#define RCC_MP_APB2LPENCLRR_SPI4LPEN_Msk          (0x1U << RCC_MP_APB2LPENCLRR_SPI4LPEN_Pos)         /*!< 0x00000200 */
#define RCC_MP_APB2LPENCLRR_SPI4LPEN              RCC_MP_APB2LPENCLRR_SPI4LPEN_Msk                   /*!< SPI4 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENCLRR_SPI5LPEN_Pos          (10U)
#define RCC_MP_APB2LPENCLRR_SPI5LPEN_Msk          (0x1U << RCC_MP_APB2LPENCLRR_SPI5LPEN_Pos)         /*!< 0x00000400 */
#define RCC_MP_APB2LPENCLRR_SPI5LPEN              RCC_MP_APB2LPENCLRR_SPI5LPEN_Msk                   /*!< SPI5 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENCLRR_USART6LPEN_Pos        (13U)
#define RCC_MP_APB2LPENCLRR_USART6LPEN_Msk        (0x1U << RCC_MP_APB2LPENCLRR_USART6LPEN_Pos)       /*!< 0x00002000 */
#define RCC_MP_APB2LPENCLRR_USART6LPEN            RCC_MP_APB2LPENCLRR_USART6LPEN_Msk                 /*!< USART6 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENCLRR_SAI1LPEN_Pos          (16U)
#define RCC_MP_APB2LPENCLRR_SAI1LPEN_Msk          (0x1U << RCC_MP_APB2LPENCLRR_SAI1LPEN_Pos)         /*!< 0x00010000 */
#define RCC_MP_APB2LPENCLRR_SAI1LPEN              RCC_MP_APB2LPENCLRR_SAI1LPEN_Msk                   /*!< SAI1 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENCLRR_SAI2LPEN_Pos          (17U)
#define RCC_MP_APB2LPENCLRR_SAI2LPEN_Msk          (0x1U << RCC_MP_APB2LPENCLRR_SAI2LPEN_Pos)         /*!< 0x00020000 */
#define RCC_MP_APB2LPENCLRR_SAI2LPEN              RCC_MP_APB2LPENCLRR_SAI2LPEN_Msk                   /*!< SAI2 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENCLRR_SAI3LPEN_Pos          (18U)
#define RCC_MP_APB2LPENCLRR_SAI3LPEN_Msk          (0x1U << RCC_MP_APB2LPENCLRR_SAI3LPEN_Pos)         /*!< 0x00040000 */
#define RCC_MP_APB2LPENCLRR_SAI3LPEN              RCC_MP_APB2LPENCLRR_SAI3LPEN_Msk                   /*!< SAI3 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENCLRR_DFSDMLPEN_Pos         (20U)
#define RCC_MP_APB2LPENCLRR_DFSDMLPEN_Msk         (0x1U << RCC_MP_APB2LPENCLRR_DFSDMLPEN_Pos)        /*!< 0x00100000 */
#define RCC_MP_APB2LPENCLRR_DFSDMLPEN             RCC_MP_APB2LPENCLRR_DFSDMLPEN_Msk                  /*!< DFSDM peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENCLRR_ADFSDMLPEN_Pos        (21U)
#define RCC_MP_APB2LPENCLRR_ADFSDMLPEN_Msk        (0x1U << RCC_MP_APB2LPENCLRR_ADFSDMLPEN_Pos)       /*!< 0x00200000 */
#define RCC_MP_APB2LPENCLRR_ADFSDMLPEN            RCC_MP_APB2LPENCLRR_ADFSDMLPEN_Msk                 /*!< Audio DFSDM peripheral clocks enable during CSleep mode */
#define RCC_MP_APB2LPENCLRR_FDCANLPEN_Pos         (24U)
#define RCC_MP_APB2LPENCLRR_FDCANLPEN_Msk         (0x1U << RCC_MP_APB2LPENCLRR_FDCANLPEN_Pos)        /*!< 0x01000000 */
#define RCC_MP_APB2LPENCLRR_FDCANLPEN             RCC_MP_APB2LPENCLRR_FDCANLPEN_Msk                  /*!< FDCAN and CANRAM peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MP_APB3LPENSETR register  **************/
#define RCC_MP_APB3LPENSETR_LPTIM2LPEN_Pos        (0U)
#define RCC_MP_APB3LPENSETR_LPTIM2LPEN_Msk        (0x1U << RCC_MP_APB3LPENSETR_LPTIM2LPEN_Pos)       /*!< 0x00000001 */
#define RCC_MP_APB3LPENSETR_LPTIM2LPEN            RCC_MP_APB3LPENSETR_LPTIM2LPEN_Msk                 /*!< LPTIM2 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB3LPENSETR_LPTIM3LPEN_Pos        (1U)
#define RCC_MP_APB3LPENSETR_LPTIM3LPEN_Msk        (0x1U << RCC_MP_APB3LPENSETR_LPTIM3LPEN_Pos)       /*!< 0x00000002 */
#define RCC_MP_APB3LPENSETR_LPTIM3LPEN            RCC_MP_APB3LPENSETR_LPTIM3LPEN_Msk                 /*!< LPTIM3 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB3LPENSETR_LPTIM4LPEN_Pos        (2U)
#define RCC_MP_APB3LPENSETR_LPTIM4LPEN_Msk        (0x1U << RCC_MP_APB3LPENSETR_LPTIM4LPEN_Pos)       /*!< 0x00000004 */
#define RCC_MP_APB3LPENSETR_LPTIM4LPEN            RCC_MP_APB3LPENSETR_LPTIM4LPEN_Msk                 /*!< LPTIM4 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB3LPENSETR_LPTIM5LPEN_Pos        (3U)
#define RCC_MP_APB3LPENSETR_LPTIM5LPEN_Msk        (0x1U << RCC_MP_APB3LPENSETR_LPTIM5LPEN_Pos)       /*!< 0x00000008 */
#define RCC_MP_APB3LPENSETR_LPTIM5LPEN            RCC_MP_APB3LPENSETR_LPTIM5LPEN_Msk                 /*!< LPTIM5 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB3LPENSETR_SAI4LPEN_Pos          (8U)
#define RCC_MP_APB3LPENSETR_SAI4LPEN_Msk          (0x1U << RCC_MP_APB3LPENSETR_SAI4LPEN_Pos)         /*!< 0x00000100 */
#define RCC_MP_APB3LPENSETR_SAI4LPEN              RCC_MP_APB3LPENSETR_SAI4LPEN_Msk                   /*!< SAI4 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB3LPENSETR_SYSCFGLPEN_Pos        (11U)
#define RCC_MP_APB3LPENSETR_SYSCFGLPEN_Msk        (0x1U << RCC_MP_APB3LPENSETR_SYSCFGLPEN_Pos)       /*!< 0x00000800 */
#define RCC_MP_APB3LPENSETR_SYSCFGLPEN            RCC_MP_APB3LPENSETR_SYSCFGLPEN_Msk                 /*!< SYSCFG peripheral clocks enable during CSleep mode */
#define RCC_MP_APB3LPENSETR_VREFLPEN_Pos          (13U)
#define RCC_MP_APB3LPENSETR_VREFLPEN_Msk          (0x1U << RCC_MP_APB3LPENSETR_VREFLPEN_Pos)         /*!< 0x00002000 */
#define RCC_MP_APB3LPENSETR_VREFLPEN              RCC_MP_APB3LPENSETR_VREFLPEN_Msk                   /*!< VREF peripheral clocks enable during CSleep mode */
#define RCC_MP_APB3LPENSETR_DTSLPEN_Pos           (16U)
#define RCC_MP_APB3LPENSETR_DTSLPEN_Msk           (0x1U << RCC_MP_APB3LPENSETR_DTSLPEN_Pos)          /*!< 0x00010000 */
#define RCC_MP_APB3LPENSETR_DTSLPEN               RCC_MP_APB3LPENSETR_DTSLPEN_Msk                    /*!< DTS peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MP_APB3LPENCLRR register  **************/
#define RCC_MP_APB3LPENCLRR_LPTIM2LPEN_Pos        (0U)
#define RCC_MP_APB3LPENCLRR_LPTIM2LPEN_Msk        (0x1U << RCC_MP_APB3LPENCLRR_LPTIM2LPEN_Pos)       /*!< 0x00000001 */
#define RCC_MP_APB3LPENCLRR_LPTIM2LPEN            RCC_MP_APB3LPENCLRR_LPTIM2LPEN_Msk                 /*!< LPTIM2 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB3LPENCLRR_LPTIM3LPEN_Pos        (1U)
#define RCC_MP_APB3LPENCLRR_LPTIM3LPEN_Msk        (0x1U << RCC_MP_APB3LPENCLRR_LPTIM3LPEN_Pos)       /*!< 0x00000002 */
#define RCC_MP_APB3LPENCLRR_LPTIM3LPEN            RCC_MP_APB3LPENCLRR_LPTIM3LPEN_Msk                 /*!< LPTIM3 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB3LPENCLRR_LPTIM4LPEN_Pos        (2U)
#define RCC_MP_APB3LPENCLRR_LPTIM4LPEN_Msk        (0x1U << RCC_MP_APB3LPENCLRR_LPTIM4LPEN_Pos)       /*!< 0x00000004 */
#define RCC_MP_APB3LPENCLRR_LPTIM4LPEN            RCC_MP_APB3LPENCLRR_LPTIM4LPEN_Msk                 /*!< LPTIM4 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB3LPENCLRR_LPTIM5LPEN_Pos        (3U)
#define RCC_MP_APB3LPENCLRR_LPTIM5LPEN_Msk        (0x1U << RCC_MP_APB3LPENCLRR_LPTIM5LPEN_Pos)       /*!< 0x00000008 */
#define RCC_MP_APB3LPENCLRR_LPTIM5LPEN            RCC_MP_APB3LPENCLRR_LPTIM5LPEN_Msk                 /*!< LPTIM5 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB3LPENCLRR_SAI4LPEN_Pos          (8U)
#define RCC_MP_APB3LPENCLRR_SAI4LPEN_Msk          (0x1U << RCC_MP_APB3LPENCLRR_SAI4LPEN_Pos)         /*!< 0x00000100 */
#define RCC_MP_APB3LPENCLRR_SAI4LPEN              RCC_MP_APB3LPENCLRR_SAI4LPEN_Msk                   /*!< SAI4 peripheral clocks enable during CSleep mode */
#define RCC_MP_APB3LPENCLRR_SYSCFGLPEN_Pos        (11U)
#define RCC_MP_APB3LPENCLRR_SYSCFGLPEN_Msk        (0x1U << RCC_MP_APB3LPENCLRR_SYSCFGLPEN_Pos)       /*!< 0x00000800 */
#define RCC_MP_APB3LPENCLRR_SYSCFGLPEN            RCC_MP_APB3LPENCLRR_SYSCFGLPEN_Msk                 /*!< SYSCFG peripheral clocks enable during CSleep mode */
#define RCC_MP_APB3LPENCLRR_VREFLPEN_Pos          (13U)
#define RCC_MP_APB3LPENCLRR_VREFLPEN_Msk          (0x1U << RCC_MP_APB3LPENCLRR_VREFLPEN_Pos)         /*!< 0x00002000 */
#define RCC_MP_APB3LPENCLRR_VREFLPEN              RCC_MP_APB3LPENCLRR_VREFLPEN_Msk                   /*!< VREF peripheral clocks enable during CSleep mode */
#define RCC_MP_APB3LPENCLRR_DTSLPEN_Pos           (16U)
#define RCC_MP_APB3LPENCLRR_DTSLPEN_Msk           (0x1U << RCC_MP_APB3LPENCLRR_DTSLPEN_Pos)          /*!< 0x00010000 */
#define RCC_MP_APB3LPENCLRR_DTSLPEN               RCC_MP_APB3LPENCLRR_DTSLPEN_Msk                    /*!< DTS peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MP_AHB2LPENSETR register  **************/
#define RCC_MP_AHB2LPENSETR_DMA1LPEN_Pos          (0U)
#define RCC_MP_AHB2LPENSETR_DMA1LPEN_Msk          (0x1U << RCC_MP_AHB2LPENSETR_DMA1LPEN_Pos)         /*!< 0x00000001 */
#define RCC_MP_AHB2LPENSETR_DMA1LPEN              RCC_MP_AHB2LPENSETR_DMA1LPEN_Msk                   /*!< DMA1 peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB2LPENSETR_DMA2LPEN_Pos          (1U)
#define RCC_MP_AHB2LPENSETR_DMA2LPEN_Msk          (0x1U << RCC_MP_AHB2LPENSETR_DMA2LPEN_Pos)         /*!< 0x00000002 */
#define RCC_MP_AHB2LPENSETR_DMA2LPEN              RCC_MP_AHB2LPENSETR_DMA2LPEN_Msk                   /*!< DMA2 peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB2LPENSETR_DMAMUXLPEN_Pos        (2U)
#define RCC_MP_AHB2LPENSETR_DMAMUXLPEN_Msk        (0x1U << RCC_MP_AHB2LPENSETR_DMAMUXLPEN_Pos)       /*!< 0x00000004 */
#define RCC_MP_AHB2LPENSETR_DMAMUXLPEN            RCC_MP_AHB2LPENSETR_DMAMUXLPEN_Msk                 /*!< DMAMUX peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB2LPENSETR_ADC12LPEN_Pos         (5U)
#define RCC_MP_AHB2LPENSETR_ADC12LPEN_Msk         (0x1U << RCC_MP_AHB2LPENSETR_ADC12LPEN_Pos)        /*!< 0x00000020 */
#define RCC_MP_AHB2LPENSETR_ADC12LPEN             RCC_MP_AHB2LPENSETR_ADC12LPEN_Msk                  /*!< ADC1&amp;2 peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB2LPENSETR_USBOLPEN_Pos          (8U)
#define RCC_MP_AHB2LPENSETR_USBOLPEN_Msk          (0x1U << RCC_MP_AHB2LPENSETR_USBOLPEN_Pos)         /*!< 0x00000100 */
#define RCC_MP_AHB2LPENSETR_USBOLPEN              RCC_MP_AHB2LPENSETR_USBOLPEN_Msk                   /*!< USBO peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB2LPENSETR_SDMMC3LPEN_Pos        (16U)
#define RCC_MP_AHB2LPENSETR_SDMMC3LPEN_Msk        (0x1U << RCC_MP_AHB2LPENSETR_SDMMC3LPEN_Pos)       /*!< 0x00010000 */
#define RCC_MP_AHB2LPENSETR_SDMMC3LPEN            RCC_MP_AHB2LPENSETR_SDMMC3LPEN_Msk                 /*!< SDMMC3 and SDMMC3 delay (DLYBSD3) block peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MP_AHB2LPENCLRR register  **************/
#define RCC_MP_AHB2LPENCLRR_DMA1LPEN_Pos          (0U)
#define RCC_MP_AHB2LPENCLRR_DMA1LPEN_Msk          (0x1U << RCC_MP_AHB2LPENCLRR_DMA1LPEN_Pos)         /*!< 0x00000001 */
#define RCC_MP_AHB2LPENCLRR_DMA1LPEN              RCC_MP_AHB2LPENCLRR_DMA1LPEN_Msk                   /*!< DMA1 peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB2LPENCLRR_DMA2LPEN_Pos          (1U)
#define RCC_MP_AHB2LPENCLRR_DMA2LPEN_Msk          (0x1U << RCC_MP_AHB2LPENCLRR_DMA2LPEN_Pos)         /*!< 0x00000002 */
#define RCC_MP_AHB2LPENCLRR_DMA2LPEN              RCC_MP_AHB2LPENCLRR_DMA2LPEN_Msk                   /*!< DMA2 peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB2LPENCLRR_DMAMUXLPEN_Pos        (2U)
#define RCC_MP_AHB2LPENCLRR_DMAMUXLPEN_Msk        (0x1U << RCC_MP_AHB2LPENCLRR_DMAMUXLPEN_Pos)       /*!< 0x00000004 */
#define RCC_MP_AHB2LPENCLRR_DMAMUXLPEN            RCC_MP_AHB2LPENCLRR_DMAMUXLPEN_Msk                 /*!< DMAMUX peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB2LPENCLRR_ADC12LPEN_Pos         (5U)
#define RCC_MP_AHB2LPENCLRR_ADC12LPEN_Msk         (0x1U << RCC_MP_AHB2LPENCLRR_ADC12LPEN_Pos)        /*!< 0x00000020 */
#define RCC_MP_AHB2LPENCLRR_ADC12LPEN             RCC_MP_AHB2LPENCLRR_ADC12LPEN_Msk                  /*!< ADC1&amp;2 peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB2LPENCLRR_USBOLPEN_Pos          (8U)
#define RCC_MP_AHB2LPENCLRR_USBOLPEN_Msk          (0x1U << RCC_MP_AHB2LPENCLRR_USBOLPEN_Pos)         /*!< 0x00000100 */
#define RCC_MP_AHB2LPENCLRR_USBOLPEN              RCC_MP_AHB2LPENCLRR_USBOLPEN_Msk                   /*!< USBO peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB2LPENCLRR_SDMMC3LPEN_Pos        (16U)
#define RCC_MP_AHB2LPENCLRR_SDMMC3LPEN_Msk        (0x1U << RCC_MP_AHB2LPENCLRR_SDMMC3LPEN_Pos)       /*!< 0x00010000 */
#define RCC_MP_AHB2LPENCLRR_SDMMC3LPEN            RCC_MP_AHB2LPENCLRR_SDMMC3LPEN_Msk                 /*!< SDMMC3 and SDMMC3 delay (DLYBSD3) block peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MP_AHB3LPENSETR register  **************/
#define RCC_MP_AHB3LPENSETR_DCMILPEN_Pos          (0U)
#define RCC_MP_AHB3LPENSETR_DCMILPEN_Msk          (0x1U << RCC_MP_AHB3LPENSETR_DCMILPEN_Pos)         /*!< 0x00000001 */
#define RCC_MP_AHB3LPENSETR_DCMILPEN              RCC_MP_AHB3LPENSETR_DCMILPEN_Msk                   /*!< DCMI peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB3LPENSETR_CRYP2LPEN_Pos         (4U)
#define RCC_MP_AHB3LPENSETR_CRYP2LPEN_Msk         (0x1U << RCC_MP_AHB3LPENSETR_CRYP2LPEN_Pos)        /*!< 0x00000010 */
#define RCC_MP_AHB3LPENSETR_CRYP2LPEN             RCC_MP_AHB3LPENSETR_CRYP2LPEN_Msk                  /*!< CRYP2 (3DES/AES2) peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB3LPENSETR_HASH2LPEN_Pos         (5U)
#define RCC_MP_AHB3LPENSETR_HASH2LPEN_Msk         (0x1U << RCC_MP_AHB3LPENSETR_HASH2LPEN_Pos)        /*!< 0x00000020 */
#define RCC_MP_AHB3LPENSETR_HASH2LPEN             RCC_MP_AHB3LPENSETR_HASH2LPEN_Msk                  /*!< HASH2 peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB3LPENSETR_RNG2LPEN_Pos          (6U)
#define RCC_MP_AHB3LPENSETR_RNG2LPEN_Msk          (0x1U << RCC_MP_AHB3LPENSETR_RNG2LPEN_Pos)         /*!< 0x00000040 */
#define RCC_MP_AHB3LPENSETR_RNG2LPEN              RCC_MP_AHB3LPENSETR_RNG2LPEN_Msk                   /*!< RNG2 peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB3LPENSETR_CRC2LPEN_Pos          (7U)
#define RCC_MP_AHB3LPENSETR_CRC2LPEN_Msk          (0x1U << RCC_MP_AHB3LPENSETR_CRC2LPEN_Pos)         /*!< 0x00000080 */
#define RCC_MP_AHB3LPENSETR_CRC2LPEN              RCC_MP_AHB3LPENSETR_CRC2LPEN_Msk                   /*!< CRC2 peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB3LPENSETR_HSEMLPEN_Pos          (11U)
#define RCC_MP_AHB3LPENSETR_HSEMLPEN_Msk          (0x1U << RCC_MP_AHB3LPENSETR_HSEMLPEN_Pos)         /*!< 0x00000800 */
#define RCC_MP_AHB3LPENSETR_HSEMLPEN              RCC_MP_AHB3LPENSETR_HSEMLPEN_Msk                   /*!< HSEM peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB3LPENSETR_IPCCLPEN_Pos          (12U)
#define RCC_MP_AHB3LPENSETR_IPCCLPEN_Msk          (0x1U << RCC_MP_AHB3LPENSETR_IPCCLPEN_Pos)         /*!< 0x00001000 */
#define RCC_MP_AHB3LPENSETR_IPCCLPEN              RCC_MP_AHB3LPENSETR_IPCCLPEN_Msk                   /*!< IPCC peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MP_AHB3LPENCLRR register  **************/
#define RCC_MP_AHB3LPENCLRR_DCMILPEN_Pos          (0U)
#define RCC_MP_AHB3LPENCLRR_DCMILPEN_Msk          (0x1U << RCC_MP_AHB3LPENCLRR_DCMILPEN_Pos)         /*!< 0x00000001 */
#define RCC_MP_AHB3LPENCLRR_DCMILPEN              RCC_MP_AHB3LPENCLRR_DCMILPEN_Msk                   /*!< DCMI peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB3LPENCLRR_CRYP2LPEN_Pos         (4U)
#define RCC_MP_AHB3LPENCLRR_CRYP2LPEN_Msk         (0x1U << RCC_MP_AHB3LPENCLRR_CRYP2LPEN_Pos)        /*!< 0x00000010 */
#define RCC_MP_AHB3LPENCLRR_CRYP2LPEN             RCC_MP_AHB3LPENCLRR_CRYP2LPEN_Msk                  /*!< CRYP2 (3DES/AES2) peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB3LPENCLRR_HASH2LPEN_Pos         (5U)
#define RCC_MP_AHB3LPENCLRR_HASH2LPEN_Msk         (0x1U << RCC_MP_AHB3LPENCLRR_HASH2LPEN_Pos)        /*!< 0x00000020 */
#define RCC_MP_AHB3LPENCLRR_HASH2LPEN             RCC_MP_AHB3LPENCLRR_HASH2LPEN_Msk                  /*!< HASH2 peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB3LPENCLRR_RNG2LPEN_Pos          (6U)
#define RCC_MP_AHB3LPENCLRR_RNG2LPEN_Msk          (0x1U << RCC_MP_AHB3LPENCLRR_RNG2LPEN_Pos)         /*!< 0x00000040 */
#define RCC_MP_AHB3LPENCLRR_RNG2LPEN              RCC_MP_AHB3LPENCLRR_RNG2LPEN_Msk                   /*!< RNG2 peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB3LPENCLRR_CRC2LPEN_Pos          (7U)
#define RCC_MP_AHB3LPENCLRR_CRC2LPEN_Msk          (0x1U << RCC_MP_AHB3LPENCLRR_CRC2LPEN_Pos)         /*!< 0x00000080 */
#define RCC_MP_AHB3LPENCLRR_CRC2LPEN              RCC_MP_AHB3LPENCLRR_CRC2LPEN_Msk                   /*!< CRC2 peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB3LPENCLRR_HSEMLPEN_Pos          (11U)
#define RCC_MP_AHB3LPENCLRR_HSEMLPEN_Msk          (0x1U << RCC_MP_AHB3LPENCLRR_HSEMLPEN_Pos)         /*!< 0x00000800 */
#define RCC_MP_AHB3LPENCLRR_HSEMLPEN              RCC_MP_AHB3LPENCLRR_HSEMLPEN_Msk                   /*!< HSEM peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB3LPENCLRR_IPCCLPEN_Pos          (12U)
#define RCC_MP_AHB3LPENCLRR_IPCCLPEN_Msk          (0x1U << RCC_MP_AHB3LPENCLRR_IPCCLPEN_Pos)         /*!< 0x00001000 */
#define RCC_MP_AHB3LPENCLRR_IPCCLPEN              RCC_MP_AHB3LPENCLRR_IPCCLPEN_Msk                   /*!< IPCC peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MP_AHB4LPENSETR register  **************/
#define RCC_MP_AHB4LPENSETR_GPIOALPEN_Pos         (0U)
#define RCC_MP_AHB4LPENSETR_GPIOALPEN_Msk         (0x1U << RCC_MP_AHB4LPENSETR_GPIOALPEN_Pos)        /*!< 0x00000001 */
#define RCC_MP_AHB4LPENSETR_GPIOALPEN             RCC_MP_AHB4LPENSETR_GPIOALPEN_Msk                  /*!< GPIOA peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB4LPENSETR_GPIOBLPEN_Pos         (1U)
#define RCC_MP_AHB4LPENSETR_GPIOBLPEN_Msk         (0x1U << RCC_MP_AHB4LPENSETR_GPIOBLPEN_Pos)        /*!< 0x00000002 */
#define RCC_MP_AHB4LPENSETR_GPIOBLPEN             RCC_MP_AHB4LPENSETR_GPIOBLPEN_Msk                  /*!< GPIOB peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB4LPENSETR_GPIOCLPEN_Pos         (2U)
#define RCC_MP_AHB4LPENSETR_GPIOCLPEN_Msk         (0x1U << RCC_MP_AHB4LPENSETR_GPIOCLPEN_Pos)        /*!< 0x00000004 */
#define RCC_MP_AHB4LPENSETR_GPIOCLPEN             RCC_MP_AHB4LPENSETR_GPIOCLPEN_Msk                  /*!< GPIOC peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB4LPENSETR_GPIODLPEN_Pos         (3U)
#define RCC_MP_AHB4LPENSETR_GPIODLPEN_Msk         (0x1U << RCC_MP_AHB4LPENSETR_GPIODLPEN_Pos)        /*!< 0x00000008 */
#define RCC_MP_AHB4LPENSETR_GPIODLPEN             RCC_MP_AHB4LPENSETR_GPIODLPEN_Msk                  /*!< GPIOD peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB4LPENSETR_GPIOELPEN_Pos         (4U)
#define RCC_MP_AHB4LPENSETR_GPIOELPEN_Msk         (0x1U << RCC_MP_AHB4LPENSETR_GPIOELPEN_Pos)        /*!< 0x00000010 */
#define RCC_MP_AHB4LPENSETR_GPIOELPEN             RCC_MP_AHB4LPENSETR_GPIOELPEN_Msk                  /*!< GPIOE peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB4LPENSETR_GPIOFLPEN_Pos         (5U)
#define RCC_MP_AHB4LPENSETR_GPIOFLPEN_Msk         (0x1U << RCC_MP_AHB4LPENSETR_GPIOFLPEN_Pos)        /*!< 0x00000020 */
#define RCC_MP_AHB4LPENSETR_GPIOFLPEN             RCC_MP_AHB4LPENSETR_GPIOFLPEN_Msk                  /*!< GPIOF peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB4LPENSETR_GPIOGLPEN_Pos         (6U)
#define RCC_MP_AHB4LPENSETR_GPIOGLPEN_Msk         (0x1U << RCC_MP_AHB4LPENSETR_GPIOGLPEN_Pos)        /*!< 0x00000040 */
#define RCC_MP_AHB4LPENSETR_GPIOGLPEN             RCC_MP_AHB4LPENSETR_GPIOGLPEN_Msk                  /*!< GPIOG peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB4LPENSETR_GPIOHLPEN_Pos         (7U)
#define RCC_MP_AHB4LPENSETR_GPIOHLPEN_Msk         (0x1U << RCC_MP_AHB4LPENSETR_GPIOHLPEN_Pos)        /*!< 0x00000080 */
#define RCC_MP_AHB4LPENSETR_GPIOHLPEN             RCC_MP_AHB4LPENSETR_GPIOHLPEN_Msk                  /*!< GPIOH peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB4LPENSETR_GPIOILPEN_Pos         (8U)
#define RCC_MP_AHB4LPENSETR_GPIOILPEN_Msk         (0x1U << RCC_MP_AHB4LPENSETR_GPIOILPEN_Pos)        /*!< 0x00000100 */
#define RCC_MP_AHB4LPENSETR_GPIOILPEN             RCC_MP_AHB4LPENSETR_GPIOILPEN_Msk                  /*!< GPIOI peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB4LPENSETR_GPIOJLPEN_Pos         (9U)
#define RCC_MP_AHB4LPENSETR_GPIOJLPEN_Msk         (0x1U << RCC_MP_AHB4LPENSETR_GPIOJLPEN_Pos)        /*!< 0x00000200 */
#define RCC_MP_AHB4LPENSETR_GPIOJLPEN             RCC_MP_AHB4LPENSETR_GPIOJLPEN_Msk                  /*!< GPIOJ peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB4LPENSETR_GPIOKLPEN_Pos         (10U)
#define RCC_MP_AHB4LPENSETR_GPIOKLPEN_Msk         (0x1U << RCC_MP_AHB4LPENSETR_GPIOKLPEN_Pos)        /*!< 0x00000400 */
#define RCC_MP_AHB4LPENSETR_GPIOKLPEN             RCC_MP_AHB4LPENSETR_GPIOKLPEN_Msk                  /*!< GPIOK peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MP_AHB4LPENCLRR register  **************/
#define RCC_MP_AHB4LPENCLRR_GPIOALPEN_Pos         (0U)
#define RCC_MP_AHB4LPENCLRR_GPIOALPEN_Msk         (0x1U << RCC_MP_AHB4LPENCLRR_GPIOALPEN_Pos)        /*!< 0x00000001 */
#define RCC_MP_AHB4LPENCLRR_GPIOALPEN             RCC_MP_AHB4LPENCLRR_GPIOALPEN_Msk                  /*!< GPIOA peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB4LPENCLRR_GPIOBLPEN_Pos         (1U)
#define RCC_MP_AHB4LPENCLRR_GPIOBLPEN_Msk         (0x1U << RCC_MP_AHB4LPENCLRR_GPIOBLPEN_Pos)        /*!< 0x00000002 */
#define RCC_MP_AHB4LPENCLRR_GPIOBLPEN             RCC_MP_AHB4LPENCLRR_GPIOBLPEN_Msk                  /*!< GPIOB peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB4LPENCLRR_GPIOCLPEN_Pos         (2U)
#define RCC_MP_AHB4LPENCLRR_GPIOCLPEN_Msk         (0x1U << RCC_MP_AHB4LPENCLRR_GPIOCLPEN_Pos)        /*!< 0x00000004 */
#define RCC_MP_AHB4LPENCLRR_GPIOCLPEN             RCC_MP_AHB4LPENCLRR_GPIOCLPEN_Msk                  /*!< GPIOC peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB4LPENCLRR_GPIODLPEN_Pos         (3U)
#define RCC_MP_AHB4LPENCLRR_GPIODLPEN_Msk         (0x1U << RCC_MP_AHB4LPENCLRR_GPIODLPEN_Pos)        /*!< 0x00000008 */
#define RCC_MP_AHB4LPENCLRR_GPIODLPEN             RCC_MP_AHB4LPENCLRR_GPIODLPEN_Msk                  /*!< GPIOD peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB4LPENCLRR_GPIOELPEN_Pos         (4U)
#define RCC_MP_AHB4LPENCLRR_GPIOELPEN_Msk         (0x1U << RCC_MP_AHB4LPENCLRR_GPIOELPEN_Pos)        /*!< 0x00000010 */
#define RCC_MP_AHB4LPENCLRR_GPIOELPEN             RCC_MP_AHB4LPENCLRR_GPIOELPEN_Msk                  /*!< GPIOE peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB4LPENCLRR_GPIOFLPEN_Pos         (5U)
#define RCC_MP_AHB4LPENCLRR_GPIOFLPEN_Msk         (0x1U << RCC_MP_AHB4LPENCLRR_GPIOFLPEN_Pos)        /*!< 0x00000020 */
#define RCC_MP_AHB4LPENCLRR_GPIOFLPEN             RCC_MP_AHB4LPENCLRR_GPIOFLPEN_Msk                  /*!< GPIOF peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB4LPENCLRR_GPIOGLPEN_Pos         (6U)
#define RCC_MP_AHB4LPENCLRR_GPIOGLPEN_Msk         (0x1U << RCC_MP_AHB4LPENCLRR_GPIOGLPEN_Pos)        /*!< 0x00000040 */
#define RCC_MP_AHB4LPENCLRR_GPIOGLPEN             RCC_MP_AHB4LPENCLRR_GPIOGLPEN_Msk                  /*!< GPIOG peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB4LPENCLRR_GPIOHLPEN_Pos         (7U)
#define RCC_MP_AHB4LPENCLRR_GPIOHLPEN_Msk         (0x1U << RCC_MP_AHB4LPENCLRR_GPIOHLPEN_Pos)        /*!< 0x00000080 */
#define RCC_MP_AHB4LPENCLRR_GPIOHLPEN             RCC_MP_AHB4LPENCLRR_GPIOHLPEN_Msk                  /*!< GPIOH peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB4LPENCLRR_GPIOILPEN_Pos         (8U)
#define RCC_MP_AHB4LPENCLRR_GPIOILPEN_Msk         (0x1U << RCC_MP_AHB4LPENCLRR_GPIOILPEN_Pos)        /*!< 0x00000100 */
#define RCC_MP_AHB4LPENCLRR_GPIOILPEN             RCC_MP_AHB4LPENCLRR_GPIOILPEN_Msk                  /*!< GPIOI peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB4LPENCLRR_GPIOJLPEN_Pos         (9U)
#define RCC_MP_AHB4LPENCLRR_GPIOJLPEN_Msk         (0x1U << RCC_MP_AHB4LPENCLRR_GPIOJLPEN_Pos)        /*!< 0x00000200 */
#define RCC_MP_AHB4LPENCLRR_GPIOJLPEN             RCC_MP_AHB4LPENCLRR_GPIOJLPEN_Msk                  /*!< GPIOJ peripheral clocks enable during CSleep mode */
#define RCC_MP_AHB4LPENCLRR_GPIOKLPEN_Pos         (10U)
#define RCC_MP_AHB4LPENCLRR_GPIOKLPEN_Msk         (0x1U << RCC_MP_AHB4LPENCLRR_GPIOKLPEN_Pos)        /*!< 0x00000400 */
#define RCC_MP_AHB4LPENCLRR_GPIOKLPEN             RCC_MP_AHB4LPENCLRR_GPIOKLPEN_Msk                  /*!< GPIOK peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MP_AXIMLPENSETR register  **************/
#define RCC_MP_AXIMLPENSETR_SYSRAMLPEN_Pos        (0U)
#define RCC_MP_AXIMLPENSETR_SYSRAMLPEN_Msk        (0x1U << RCC_MP_AXIMLPENSETR_SYSRAMLPEN_Pos)       /*!< 0x00000001 */
#define RCC_MP_AXIMLPENSETR_SYSRAMLPEN            RCC_MP_AXIMLPENSETR_SYSRAMLPEN_Msk                 /*!< SYSRAM interface clock enable during CSleep mode */

/*************  Bit definition for RCC_MP_AXIMLPENCLRR register  **************/
#define RCC_MP_AXIMLPENCLRR_SYSRAMLPEN_Pos        (0U)
#define RCC_MP_AXIMLPENCLRR_SYSRAMLPEN_Msk        (0x1U << RCC_MP_AXIMLPENCLRR_SYSRAMLPEN_Pos)       /*!< 0x00000001 */
#define RCC_MP_AXIMLPENCLRR_SYSRAMLPEN            RCC_MP_AXIMLPENCLRR_SYSRAMLPEN_Msk                 /*!< SYSRAM interface clock enable during CSleep mode */

/*************  Bit definition for RCC_MP_MLAHBLPENSETR register  *************/
#define RCC_MP_MLAHBLPENSETR_SRAM1LPEN_Pos        (0U)
#define RCC_MP_MLAHBLPENSETR_SRAM1LPEN_Msk        (0x1U << RCC_MP_MLAHBLPENSETR_SRAM1LPEN_Pos)       /*!< 0x00000001 */
#define RCC_MP_MLAHBLPENSETR_SRAM1LPEN            RCC_MP_MLAHBLPENSETR_SRAM1LPEN_Msk                 /*!< SRAM1 interface clock enable during CSleep mode */
#define RCC_MP_MLAHBLPENSETR_SRAM2LPEN_Pos        (1U)
#define RCC_MP_MLAHBLPENSETR_SRAM2LPEN_Msk        (0x1U << RCC_MP_MLAHBLPENSETR_SRAM2LPEN_Pos)       /*!< 0x00000002 */
#define RCC_MP_MLAHBLPENSETR_SRAM2LPEN            RCC_MP_MLAHBLPENSETR_SRAM2LPEN_Msk                 /*!< SRAM2 interface clock enable during CSleep mode */
#define RCC_MP_MLAHBLPENSETR_SRAM34LPEN_Pos       (2U)
#define RCC_MP_MLAHBLPENSETR_SRAM34LPEN_Msk       (0x1U << RCC_MP_MLAHBLPENSETR_SRAM34LPEN_Pos)      /*!< 0x00000004 */
#define RCC_MP_MLAHBLPENSETR_SRAM34LPEN           RCC_MP_MLAHBLPENSETR_SRAM34LPEN_Msk                /*!< SRAM3 and SRAM4 interface clock enable during CSleep mode */
#define RCC_MP_MLAHBLPENSETR_RETRAMLPEN_Pos       (4U)
#define RCC_MP_MLAHBLPENSETR_RETRAMLPEN_Msk       (0x1U << RCC_MP_MLAHBLPENSETR_RETRAMLPEN_Pos)      /*!< 0x00000010 */
#define RCC_MP_MLAHBLPENSETR_RETRAMLPEN           RCC_MP_MLAHBLPENSETR_RETRAMLPEN_Msk                /*!< RETRAM interface clock enable during CSleep mode */

/*************  Bit definition for RCC_MP_MLAHBLPENCLRR register  *************/
#define RCC_MP_MLAHBLPENCLRR_SRAM1LPEN_Pos        (0U)
#define RCC_MP_MLAHBLPENCLRR_SRAM1LPEN_Msk        (0x1U << RCC_MP_MLAHBLPENCLRR_SRAM1LPEN_Pos)       /*!< 0x00000001 */
#define RCC_MP_MLAHBLPENCLRR_SRAM1LPEN            RCC_MP_MLAHBLPENCLRR_SRAM1LPEN_Msk                 /*!< SRAM1 interface clock enable during CSleep mode */
#define RCC_MP_MLAHBLPENCLRR_SRAM2LPEN_Pos        (1U)
#define RCC_MP_MLAHBLPENCLRR_SRAM2LPEN_Msk        (0x1U << RCC_MP_MLAHBLPENCLRR_SRAM2LPEN_Pos)       /*!< 0x00000002 */
#define RCC_MP_MLAHBLPENCLRR_SRAM2LPEN            RCC_MP_MLAHBLPENCLRR_SRAM2LPEN_Msk                 /*!< SRAM2 interface clock enable during CSleep mode */
#define RCC_MP_MLAHBLPENCLRR_SRAM34LPEN_Pos       (2U)
#define RCC_MP_MLAHBLPENCLRR_SRAM34LPEN_Msk       (0x1U << RCC_MP_MLAHBLPENCLRR_SRAM34LPEN_Pos)      /*!< 0x00000004 */
#define RCC_MP_MLAHBLPENCLRR_SRAM34LPEN           RCC_MP_MLAHBLPENCLRR_SRAM34LPEN_Msk                /*!< SRAM3 and SRAM4 interface clock enable during CSleep mode */
#define RCC_MP_MLAHBLPENCLRR_RETRAMLPEN_Pos       (4U)
#define RCC_MP_MLAHBLPENCLRR_RETRAMLPEN_Msk       (0x1U << RCC_MP_MLAHBLPENCLRR_RETRAMLPEN_Pos)      /*!< 0x00000010 */
#define RCC_MP_MLAHBLPENCLRR_RETRAMLPEN           RCC_MP_MLAHBLPENCLRR_RETRAMLPEN_Msk                /*!< RETRAM interface clock enable during CSleep mode */

/*************  Bit definition for RCC_MC_APB1LPENSETR register  **************/
#define RCC_MC_APB1LPENSETR_TIM2LPEN_Pos          (0U)
#define RCC_MC_APB1LPENSETR_TIM2LPEN_Msk          (0x1U << RCC_MC_APB1LPENSETR_TIM2LPEN_Pos)         /*!< 0x00000001 */
#define RCC_MC_APB1LPENSETR_TIM2LPEN              RCC_MC_APB1LPENSETR_TIM2LPEN_Msk                   /*!< TIM2 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_TIM3LPEN_Pos          (1U)
#define RCC_MC_APB1LPENSETR_TIM3LPEN_Msk          (0x1U << RCC_MC_APB1LPENSETR_TIM3LPEN_Pos)         /*!< 0x00000002 */
#define RCC_MC_APB1LPENSETR_TIM3LPEN              RCC_MC_APB1LPENSETR_TIM3LPEN_Msk                   /*!< TIM3 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_TIM4LPEN_Pos          (2U)
#define RCC_MC_APB1LPENSETR_TIM4LPEN_Msk          (0x1U << RCC_MC_APB1LPENSETR_TIM4LPEN_Pos)         /*!< 0x00000004 */
#define RCC_MC_APB1LPENSETR_TIM4LPEN              RCC_MC_APB1LPENSETR_TIM4LPEN_Msk                   /*!< TIM4 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_TIM5LPEN_Pos          (3U)
#define RCC_MC_APB1LPENSETR_TIM5LPEN_Msk          (0x1U << RCC_MC_APB1LPENSETR_TIM5LPEN_Pos)         /*!< 0x00000008 */
#define RCC_MC_APB1LPENSETR_TIM5LPEN              RCC_MC_APB1LPENSETR_TIM5LPEN_Msk                   /*!< TIM5 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_TIM6LPEN_Pos          (4U)
#define RCC_MC_APB1LPENSETR_TIM6LPEN_Msk          (0x1U << RCC_MC_APB1LPENSETR_TIM6LPEN_Pos)         /*!< 0x00000010 */
#define RCC_MC_APB1LPENSETR_TIM6LPEN              RCC_MC_APB1LPENSETR_TIM6LPEN_Msk                   /*!< TIM6 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_TIM7LPEN_Pos          (5U)
#define RCC_MC_APB1LPENSETR_TIM7LPEN_Msk          (0x1U << RCC_MC_APB1LPENSETR_TIM7LPEN_Pos)         /*!< 0x00000020 */
#define RCC_MC_APB1LPENSETR_TIM7LPEN              RCC_MC_APB1LPENSETR_TIM7LPEN_Msk                   /*!< TIM7 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_TIM12LPEN_Pos         (6U)
#define RCC_MC_APB1LPENSETR_TIM12LPEN_Msk         (0x1U << RCC_MC_APB1LPENSETR_TIM12LPEN_Pos)        /*!< 0x00000040 */
#define RCC_MC_APB1LPENSETR_TIM12LPEN             RCC_MC_APB1LPENSETR_TIM12LPEN_Msk                  /*!< TIM12 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_TIM13LPEN_Pos         (7U)
#define RCC_MC_APB1LPENSETR_TIM13LPEN_Msk         (0x1U << RCC_MC_APB1LPENSETR_TIM13LPEN_Pos)        /*!< 0x00000080 */
#define RCC_MC_APB1LPENSETR_TIM13LPEN             RCC_MC_APB1LPENSETR_TIM13LPEN_Msk                  /*!< TIM13 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_TIM14LPEN_Pos         (8U)
#define RCC_MC_APB1LPENSETR_TIM14LPEN_Msk         (0x1U << RCC_MC_APB1LPENSETR_TIM14LPEN_Pos)        /*!< 0x00000100 */
#define RCC_MC_APB1LPENSETR_TIM14LPEN             RCC_MC_APB1LPENSETR_TIM14LPEN_Msk                  /*!< TIM14 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_LPTIM1LPEN_Pos        (9U)
#define RCC_MC_APB1LPENSETR_LPTIM1LPEN_Msk        (0x1U << RCC_MC_APB1LPENSETR_LPTIM1LPEN_Pos)       /*!< 0x00000200 */
#define RCC_MC_APB1LPENSETR_LPTIM1LPEN            RCC_MC_APB1LPENSETR_LPTIM1LPEN_Msk                 /*!< LPTIM1 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_SPI2LPEN_Pos          (11U)
#define RCC_MC_APB1LPENSETR_SPI2LPEN_Msk          (0x1U << RCC_MC_APB1LPENSETR_SPI2LPEN_Pos)         /*!< 0x00000800 */
#define RCC_MC_APB1LPENSETR_SPI2LPEN              RCC_MC_APB1LPENSETR_SPI2LPEN_Msk                   /*!< SPI2 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_SPI3LPEN_Pos          (12U)
#define RCC_MC_APB1LPENSETR_SPI3LPEN_Msk          (0x1U << RCC_MC_APB1LPENSETR_SPI3LPEN_Pos)         /*!< 0x00001000 */
#define RCC_MC_APB1LPENSETR_SPI3LPEN              RCC_MC_APB1LPENSETR_SPI3LPEN_Msk                   /*!< SPI3 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_USART2LPEN_Pos        (14U)
#define RCC_MC_APB1LPENSETR_USART2LPEN_Msk        (0x1U << RCC_MC_APB1LPENSETR_USART2LPEN_Pos)       /*!< 0x00004000 */
#define RCC_MC_APB1LPENSETR_USART2LPEN            RCC_MC_APB1LPENSETR_USART2LPEN_Msk                 /*!< USART2 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_USART3LPEN_Pos        (15U)
#define RCC_MC_APB1LPENSETR_USART3LPEN_Msk        (0x1U << RCC_MC_APB1LPENSETR_USART3LPEN_Pos)       /*!< 0x00008000 */
#define RCC_MC_APB1LPENSETR_USART3LPEN            RCC_MC_APB1LPENSETR_USART3LPEN_Msk                 /*!< USART3 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_UART4LPEN_Pos         (16U)
#define RCC_MC_APB1LPENSETR_UART4LPEN_Msk         (0x1U << RCC_MC_APB1LPENSETR_UART4LPEN_Pos)        /*!< 0x00010000 */
#define RCC_MC_APB1LPENSETR_UART4LPEN             RCC_MC_APB1LPENSETR_UART4LPEN_Msk                  /*!< UART4 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_UART5LPEN_Pos         (17U)
#define RCC_MC_APB1LPENSETR_UART5LPEN_Msk         (0x1U << RCC_MC_APB1LPENSETR_UART5LPEN_Pos)        /*!< 0x00020000 */
#define RCC_MC_APB1LPENSETR_UART5LPEN             RCC_MC_APB1LPENSETR_UART5LPEN_Msk                  /*!< UART5 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_UART7LPEN_Pos         (18U)
#define RCC_MC_APB1LPENSETR_UART7LPEN_Msk         (0x1U << RCC_MC_APB1LPENSETR_UART7LPEN_Pos)        /*!< 0x00040000 */
#define RCC_MC_APB1LPENSETR_UART7LPEN             RCC_MC_APB1LPENSETR_UART7LPEN_Msk                  /*!< UART7 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_UART8LPEN_Pos         (19U)
#define RCC_MC_APB1LPENSETR_UART8LPEN_Msk         (0x1U << RCC_MC_APB1LPENSETR_UART8LPEN_Pos)        /*!< 0x00080000 */
#define RCC_MC_APB1LPENSETR_UART8LPEN             RCC_MC_APB1LPENSETR_UART8LPEN_Msk                  /*!< UART8 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_I2C1LPEN_Pos          (21U)
#define RCC_MC_APB1LPENSETR_I2C1LPEN_Msk          (0x1U << RCC_MC_APB1LPENSETR_I2C1LPEN_Pos)         /*!< 0x00200000 */
#define RCC_MC_APB1LPENSETR_I2C1LPEN              RCC_MC_APB1LPENSETR_I2C1LPEN_Msk                   /*!< I2C1 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_I2C2LPEN_Pos          (22U)
#define RCC_MC_APB1LPENSETR_I2C2LPEN_Msk          (0x1U << RCC_MC_APB1LPENSETR_I2C2LPEN_Pos)         /*!< 0x00400000 */
#define RCC_MC_APB1LPENSETR_I2C2LPEN              RCC_MC_APB1LPENSETR_I2C2LPEN_Msk                   /*!< I2C2 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_I2C3LPEN_Pos          (23U)
#define RCC_MC_APB1LPENSETR_I2C3LPEN_Msk          (0x1U << RCC_MC_APB1LPENSETR_I2C3LPEN_Pos)         /*!< 0x00800000 */
#define RCC_MC_APB1LPENSETR_I2C3LPEN              RCC_MC_APB1LPENSETR_I2C3LPEN_Msk                   /*!< I2C3 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_I2C5LPEN_Pos          (24U)
#define RCC_MC_APB1LPENSETR_I2C5LPEN_Msk          (0x1U << RCC_MC_APB1LPENSETR_I2C5LPEN_Pos)         /*!< 0x01000000 */
#define RCC_MC_APB1LPENSETR_I2C5LPEN              RCC_MC_APB1LPENSETR_I2C5LPEN_Msk                   /*!< I2C5 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_SPDIFLPEN_Pos         (26U)
#define RCC_MC_APB1LPENSETR_SPDIFLPEN_Msk         (0x1U << RCC_MC_APB1LPENSETR_SPDIFLPEN_Pos)        /*!< 0x04000000 */
#define RCC_MC_APB1LPENSETR_SPDIFLPEN             RCC_MC_APB1LPENSETR_SPDIFLPEN_Msk                  /*!< SPDIFRX peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_CECLPEN_Pos           (27U)
#define RCC_MC_APB1LPENSETR_CECLPEN_Msk           (0x1U << RCC_MC_APB1LPENSETR_CECLPEN_Pos)          /*!< 0x08000000 */
#define RCC_MC_APB1LPENSETR_CECLPEN               RCC_MC_APB1LPENSETR_CECLPEN_Msk                    /*!< HDMI-CEC peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_WWDG1LPEN_Pos         (28U)
#define RCC_MC_APB1LPENSETR_WWDG1LPEN_Msk         (0x1U << RCC_MC_APB1LPENSETR_WWDG1LPEN_Pos)        /*!< 0x10000000 */
#define RCC_MC_APB1LPENSETR_WWDG1LPEN             RCC_MC_APB1LPENSETR_WWDG1LPEN_Msk                  /*!< WWDG1 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_DAC12LPEN_Pos         (29U)
#define RCC_MC_APB1LPENSETR_DAC12LPEN_Msk         (0x1U << RCC_MC_APB1LPENSETR_DAC12LPEN_Pos)        /*!< 0x20000000 */
#define RCC_MC_APB1LPENSETR_DAC12LPEN             RCC_MC_APB1LPENSETR_DAC12LPEN_Msk                  /*!< DAC1&amp;2 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENSETR_MDIOSLPEN_Pos         (31U)
#define RCC_MC_APB1LPENSETR_MDIOSLPEN_Msk         (0x1U << RCC_MC_APB1LPENSETR_MDIOSLPEN_Pos)        /*!< 0x80000000 */
#define RCC_MC_APB1LPENSETR_MDIOSLPEN             RCC_MC_APB1LPENSETR_MDIOSLPEN_Msk                  /*!< MDIOS peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MC_APB1LPENCLRR register  **************/
#define RCC_MC_APB1LPENCLRR_TIM2LPEN_Pos          (0U)
#define RCC_MC_APB1LPENCLRR_TIM2LPEN_Msk          (0x1U << RCC_MC_APB1LPENCLRR_TIM2LPEN_Pos)         /*!< 0x00000001 */
#define RCC_MC_APB1LPENCLRR_TIM2LPEN              RCC_MC_APB1LPENCLRR_TIM2LPEN_Msk                   /*!< TIM2 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_TIM3LPEN_Pos          (1U)
#define RCC_MC_APB1LPENCLRR_TIM3LPEN_Msk          (0x1U << RCC_MC_APB1LPENCLRR_TIM3LPEN_Pos)         /*!< 0x00000002 */
#define RCC_MC_APB1LPENCLRR_TIM3LPEN              RCC_MC_APB1LPENCLRR_TIM3LPEN_Msk                   /*!< TIM3 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_TIM4LPEN_Pos          (2U)
#define RCC_MC_APB1LPENCLRR_TIM4LPEN_Msk          (0x1U << RCC_MC_APB1LPENCLRR_TIM4LPEN_Pos)         /*!< 0x00000004 */
#define RCC_MC_APB1LPENCLRR_TIM4LPEN              RCC_MC_APB1LPENCLRR_TIM4LPEN_Msk                   /*!< TIM4 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_TIM5LPEN_Pos          (3U)
#define RCC_MC_APB1LPENCLRR_TIM5LPEN_Msk          (0x1U << RCC_MC_APB1LPENCLRR_TIM5LPEN_Pos)         /*!< 0x00000008 */
#define RCC_MC_APB1LPENCLRR_TIM5LPEN              RCC_MC_APB1LPENCLRR_TIM5LPEN_Msk                   /*!< TIM5 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_TIM6LPEN_Pos          (4U)
#define RCC_MC_APB1LPENCLRR_TIM6LPEN_Msk          (0x1U << RCC_MC_APB1LPENCLRR_TIM6LPEN_Pos)         /*!< 0x00000010 */
#define RCC_MC_APB1LPENCLRR_TIM6LPEN              RCC_MC_APB1LPENCLRR_TIM6LPEN_Msk                   /*!< TIM6 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_TIM7LPEN_Pos          (5U)
#define RCC_MC_APB1LPENCLRR_TIM7LPEN_Msk          (0x1U << RCC_MC_APB1LPENCLRR_TIM7LPEN_Pos)         /*!< 0x00000020 */
#define RCC_MC_APB1LPENCLRR_TIM7LPEN              RCC_MC_APB1LPENCLRR_TIM7LPEN_Msk                   /*!< TIM7 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_TIM12LPEN_Pos         (6U)
#define RCC_MC_APB1LPENCLRR_TIM12LPEN_Msk         (0x1U << RCC_MC_APB1LPENCLRR_TIM12LPEN_Pos)        /*!< 0x00000040 */
#define RCC_MC_APB1LPENCLRR_TIM12LPEN             RCC_MC_APB1LPENCLRR_TIM12LPEN_Msk                  /*!< TIM12 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_TIM13LPEN_Pos         (7U)
#define RCC_MC_APB1LPENCLRR_TIM13LPEN_Msk         (0x1U << RCC_MC_APB1LPENCLRR_TIM13LPEN_Pos)        /*!< 0x00000080 */
#define RCC_MC_APB1LPENCLRR_TIM13LPEN             RCC_MC_APB1LPENCLRR_TIM13LPEN_Msk                  /*!< TIM13 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_TIM14LPEN_Pos         (8U)
#define RCC_MC_APB1LPENCLRR_TIM14LPEN_Msk         (0x1U << RCC_MC_APB1LPENCLRR_TIM14LPEN_Pos)        /*!< 0x00000100 */
#define RCC_MC_APB1LPENCLRR_TIM14LPEN             RCC_MC_APB1LPENCLRR_TIM14LPEN_Msk                  /*!< TIM14 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_LPTIM1LPEN_Pos        (9U)
#define RCC_MC_APB1LPENCLRR_LPTIM1LPEN_Msk        (0x1U << RCC_MC_APB1LPENCLRR_LPTIM1LPEN_Pos)       /*!< 0x00000200 */
#define RCC_MC_APB1LPENCLRR_LPTIM1LPEN            RCC_MC_APB1LPENCLRR_LPTIM1LPEN_Msk                 /*!< LPTIM1 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_SPI2LPEN_Pos          (11U)
#define RCC_MC_APB1LPENCLRR_SPI2LPEN_Msk          (0x1U << RCC_MC_APB1LPENCLRR_SPI2LPEN_Pos)         /*!< 0x00000800 */
#define RCC_MC_APB1LPENCLRR_SPI2LPEN              RCC_MC_APB1LPENCLRR_SPI2LPEN_Msk                   /*!< SPI2 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_SPI3LPEN_Pos          (12U)
#define RCC_MC_APB1LPENCLRR_SPI3LPEN_Msk          (0x1U << RCC_MC_APB1LPENCLRR_SPI3LPEN_Pos)         /*!< 0x00001000 */
#define RCC_MC_APB1LPENCLRR_SPI3LPEN              RCC_MC_APB1LPENCLRR_SPI3LPEN_Msk                   /*!< SPI3 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_USART2LPEN_Pos        (14U)
#define RCC_MC_APB1LPENCLRR_USART2LPEN_Msk        (0x1U << RCC_MC_APB1LPENCLRR_USART2LPEN_Pos)       /*!< 0x00004000 */
#define RCC_MC_APB1LPENCLRR_USART2LPEN            RCC_MC_APB1LPENCLRR_USART2LPEN_Msk                 /*!< USART2 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_USART3LPEN_Pos        (15U)
#define RCC_MC_APB1LPENCLRR_USART3LPEN_Msk        (0x1U << RCC_MC_APB1LPENCLRR_USART3LPEN_Pos)       /*!< 0x00008000 */
#define RCC_MC_APB1LPENCLRR_USART3LPEN            RCC_MC_APB1LPENCLRR_USART3LPEN_Msk                 /*!< USART3 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_UART4LPEN_Pos         (16U)
#define RCC_MC_APB1LPENCLRR_UART4LPEN_Msk         (0x1U << RCC_MC_APB1LPENCLRR_UART4LPEN_Pos)        /*!< 0x00010000 */
#define RCC_MC_APB1LPENCLRR_UART4LPEN             RCC_MC_APB1LPENCLRR_UART4LPEN_Msk                  /*!< UART4 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_UART5LPEN_Pos         (17U)
#define RCC_MC_APB1LPENCLRR_UART5LPEN_Msk         (0x1U << RCC_MC_APB1LPENCLRR_UART5LPEN_Pos)        /*!< 0x00020000 */
#define RCC_MC_APB1LPENCLRR_UART5LPEN             RCC_MC_APB1LPENCLRR_UART5LPEN_Msk                  /*!< UART5 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_UART7LPEN_Pos         (18U)
#define RCC_MC_APB1LPENCLRR_UART7LPEN_Msk         (0x1U << RCC_MC_APB1LPENCLRR_UART7LPEN_Pos)        /*!< 0x00040000 */
#define RCC_MC_APB1LPENCLRR_UART7LPEN             RCC_MC_APB1LPENCLRR_UART7LPEN_Msk                  /*!< UART7 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_UART8LPEN_Pos         (19U)
#define RCC_MC_APB1LPENCLRR_UART8LPEN_Msk         (0x1U << RCC_MC_APB1LPENCLRR_UART8LPEN_Pos)        /*!< 0x00080000 */
#define RCC_MC_APB1LPENCLRR_UART8LPEN             RCC_MC_APB1LPENCLRR_UART8LPEN_Msk                  /*!< UART8 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_I2C1LPEN_Pos          (21U)
#define RCC_MC_APB1LPENCLRR_I2C1LPEN_Msk          (0x1U << RCC_MC_APB1LPENCLRR_I2C1LPEN_Pos)         /*!< 0x00200000 */
#define RCC_MC_APB1LPENCLRR_I2C1LPEN              RCC_MC_APB1LPENCLRR_I2C1LPEN_Msk                   /*!< I2C1 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_I2C2LPEN_Pos          (22U)
#define RCC_MC_APB1LPENCLRR_I2C2LPEN_Msk          (0x1U << RCC_MC_APB1LPENCLRR_I2C2LPEN_Pos)         /*!< 0x00400000 */
#define RCC_MC_APB1LPENCLRR_I2C2LPEN              RCC_MC_APB1LPENCLRR_I2C2LPEN_Msk                   /*!< I2C2 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_I2C3LPEN_Pos          (23U)
#define RCC_MC_APB1LPENCLRR_I2C3LPEN_Msk          (0x1U << RCC_MC_APB1LPENCLRR_I2C3LPEN_Pos)         /*!< 0x00800000 */
#define RCC_MC_APB1LPENCLRR_I2C3LPEN              RCC_MC_APB1LPENCLRR_I2C3LPEN_Msk                   /*!< I2C3 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_I2C5LPEN_Pos          (24U)
#define RCC_MC_APB1LPENCLRR_I2C5LPEN_Msk          (0x1U << RCC_MC_APB1LPENCLRR_I2C5LPEN_Pos)         /*!< 0x01000000 */
#define RCC_MC_APB1LPENCLRR_I2C5LPEN              RCC_MC_APB1LPENCLRR_I2C5LPEN_Msk                   /*!< I2C5 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_SPDIFLPEN_Pos         (26U)
#define RCC_MC_APB1LPENCLRR_SPDIFLPEN_Msk         (0x1U << RCC_MC_APB1LPENCLRR_SPDIFLPEN_Pos)        /*!< 0x04000000 */
#define RCC_MC_APB1LPENCLRR_SPDIFLPEN             RCC_MC_APB1LPENCLRR_SPDIFLPEN_Msk                  /*!< SPDIFRX peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_CECLPEN_Pos           (27U)
#define RCC_MC_APB1LPENCLRR_CECLPEN_Msk           (0x1U << RCC_MC_APB1LPENCLRR_CECLPEN_Pos)          /*!< 0x08000000 */
#define RCC_MC_APB1LPENCLRR_CECLPEN               RCC_MC_APB1LPENCLRR_CECLPEN_Msk                    /*!< HDMI-CEC peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_WWDG1LPEN_Pos         (28U)
#define RCC_MC_APB1LPENCLRR_WWDG1LPEN_Msk         (0x1U << RCC_MC_APB1LPENCLRR_WWDG1LPEN_Pos)        /*!< 0x10000000 */
#define RCC_MC_APB1LPENCLRR_WWDG1LPEN             RCC_MC_APB1LPENCLRR_WWDG1LPEN_Msk                  /*!< WWDG1 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_DAC12LPEN_Pos         (29U)
#define RCC_MC_APB1LPENCLRR_DAC12LPEN_Msk         (0x1U << RCC_MC_APB1LPENCLRR_DAC12LPEN_Pos)        /*!< 0x20000000 */
#define RCC_MC_APB1LPENCLRR_DAC12LPEN             RCC_MC_APB1LPENCLRR_DAC12LPEN_Msk                  /*!< DAC1&amp;2 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB1LPENCLRR_MDIOSLPEN_Pos         (31U)
#define RCC_MC_APB1LPENCLRR_MDIOSLPEN_Msk         (0x1U << RCC_MC_APB1LPENCLRR_MDIOSLPEN_Pos)        /*!< 0x80000000 */
#define RCC_MC_APB1LPENCLRR_MDIOSLPEN             RCC_MC_APB1LPENCLRR_MDIOSLPEN_Msk                  /*!< MDIOS peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MC_APB2LPENSETR register  **************/
#define RCC_MC_APB2LPENSETR_TIM1LPEN_Pos          (0U)
#define RCC_MC_APB2LPENSETR_TIM1LPEN_Msk          (0x1U << RCC_MC_APB2LPENSETR_TIM1LPEN_Pos)         /*!< 0x00000001 */
#define RCC_MC_APB2LPENSETR_TIM1LPEN              RCC_MC_APB2LPENSETR_TIM1LPEN_Msk                   /*!< TIM1 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENSETR_TIM8LPEN_Pos          (1U)
#define RCC_MC_APB2LPENSETR_TIM8LPEN_Msk          (0x1U << RCC_MC_APB2LPENSETR_TIM8LPEN_Pos)         /*!< 0x00000002 */
#define RCC_MC_APB2LPENSETR_TIM8LPEN              RCC_MC_APB2LPENSETR_TIM8LPEN_Msk                   /*!< TIM8 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENSETR_TIM15LPEN_Pos         (2U)
#define RCC_MC_APB2LPENSETR_TIM15LPEN_Msk         (0x1U << RCC_MC_APB2LPENSETR_TIM15LPEN_Pos)        /*!< 0x00000004 */
#define RCC_MC_APB2LPENSETR_TIM15LPEN             RCC_MC_APB2LPENSETR_TIM15LPEN_Msk                  /*!< TIM15 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENSETR_TIM16LPEN_Pos         (3U)
#define RCC_MC_APB2LPENSETR_TIM16LPEN_Msk         (0x1U << RCC_MC_APB2LPENSETR_TIM16LPEN_Pos)        /*!< 0x00000008 */
#define RCC_MC_APB2LPENSETR_TIM16LPEN             RCC_MC_APB2LPENSETR_TIM16LPEN_Msk                  /*!< TIM16 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENSETR_TIM17LPEN_Pos         (4U)
#define RCC_MC_APB2LPENSETR_TIM17LPEN_Msk         (0x1U << RCC_MC_APB2LPENSETR_TIM17LPEN_Pos)        /*!< 0x00000010 */
#define RCC_MC_APB2LPENSETR_TIM17LPEN             RCC_MC_APB2LPENSETR_TIM17LPEN_Msk                  /*!< TIM17 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENSETR_SPI1LPEN_Pos          (8U)
#define RCC_MC_APB2LPENSETR_SPI1LPEN_Msk          (0x1U << RCC_MC_APB2LPENSETR_SPI1LPEN_Pos)         /*!< 0x00000100 */
#define RCC_MC_APB2LPENSETR_SPI1LPEN              RCC_MC_APB2LPENSETR_SPI1LPEN_Msk                   /*!< SPI/I2S1 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENSETR_SPI4LPEN_Pos          (9U)
#define RCC_MC_APB2LPENSETR_SPI4LPEN_Msk          (0x1U << RCC_MC_APB2LPENSETR_SPI4LPEN_Pos)         /*!< 0x00000200 */
#define RCC_MC_APB2LPENSETR_SPI4LPEN              RCC_MC_APB2LPENSETR_SPI4LPEN_Msk                   /*!< SPI4 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENSETR_SPI5LPEN_Pos          (10U)
#define RCC_MC_APB2LPENSETR_SPI5LPEN_Msk          (0x1U << RCC_MC_APB2LPENSETR_SPI5LPEN_Pos)         /*!< 0x00000400 */
#define RCC_MC_APB2LPENSETR_SPI5LPEN              RCC_MC_APB2LPENSETR_SPI5LPEN_Msk                   /*!< SPI5 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENSETR_USART6LPEN_Pos        (13U)
#define RCC_MC_APB2LPENSETR_USART6LPEN_Msk        (0x1U << RCC_MC_APB2LPENSETR_USART6LPEN_Pos)       /*!< 0x00002000 */
#define RCC_MC_APB2LPENSETR_USART6LPEN            RCC_MC_APB2LPENSETR_USART6LPEN_Msk                 /*!< USART6 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENSETR_SAI1LPEN_Pos          (16U)
#define RCC_MC_APB2LPENSETR_SAI1LPEN_Msk          (0x1U << RCC_MC_APB2LPENSETR_SAI1LPEN_Pos)         /*!< 0x00010000 */
#define RCC_MC_APB2LPENSETR_SAI1LPEN              RCC_MC_APB2LPENSETR_SAI1LPEN_Msk                   /*!< SAI1 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENSETR_SAI2LPEN_Pos          (17U)
#define RCC_MC_APB2LPENSETR_SAI2LPEN_Msk          (0x1U << RCC_MC_APB2LPENSETR_SAI2LPEN_Pos)         /*!< 0x00020000 */
#define RCC_MC_APB2LPENSETR_SAI2LPEN              RCC_MC_APB2LPENSETR_SAI2LPEN_Msk                   /*!< SAI2 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENSETR_SAI3LPEN_Pos          (18U)
#define RCC_MC_APB2LPENSETR_SAI3LPEN_Msk          (0x1U << RCC_MC_APB2LPENSETR_SAI3LPEN_Pos)         /*!< 0x00040000 */
#define RCC_MC_APB2LPENSETR_SAI3LPEN              RCC_MC_APB2LPENSETR_SAI3LPEN_Msk                   /*!< SAI3 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENSETR_DFSDMLPEN_Pos         (20U)
#define RCC_MC_APB2LPENSETR_DFSDMLPEN_Msk         (0x1U << RCC_MC_APB2LPENSETR_DFSDMLPEN_Pos)        /*!< 0x00100000 */
#define RCC_MC_APB2LPENSETR_DFSDMLPEN             RCC_MC_APB2LPENSETR_DFSDMLPEN_Msk                  /*!< DFSDM peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENSETR_ADFSDMLPEN_Pos        (21U)
#define RCC_MC_APB2LPENSETR_ADFSDMLPEN_Msk        (0x1U << RCC_MC_APB2LPENSETR_ADFSDMLPEN_Pos)       /*!< 0x00200000 */
#define RCC_MC_APB2LPENSETR_ADFSDMLPEN            RCC_MC_APB2LPENSETR_ADFSDMLPEN_Msk                 /*!< Audio DFSDM peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENSETR_FDCANLPEN_Pos         (24U)
#define RCC_MC_APB2LPENSETR_FDCANLPEN_Msk         (0x1U << RCC_MC_APB2LPENSETR_FDCANLPEN_Pos)        /*!< 0x01000000 */
#define RCC_MC_APB2LPENSETR_FDCANLPEN             RCC_MC_APB2LPENSETR_FDCANLPEN_Msk                  /*!< FDCAN and CANRAM peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MC_APB2LPENCLRR register  **************/
#define RCC_MC_APB2LPENCLRR_TIM1LPEN_Pos          (0U)
#define RCC_MC_APB2LPENCLRR_TIM1LPEN_Msk          (0x1U << RCC_MC_APB2LPENCLRR_TIM1LPEN_Pos)         /*!< 0x00000001 */
#define RCC_MC_APB2LPENCLRR_TIM1LPEN              RCC_MC_APB2LPENCLRR_TIM1LPEN_Msk                   /*!< TIM1 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENCLRR_TIM8LPEN_Pos          (1U)
#define RCC_MC_APB2LPENCLRR_TIM8LPEN_Msk          (0x1U << RCC_MC_APB2LPENCLRR_TIM8LPEN_Pos)         /*!< 0x00000002 */
#define RCC_MC_APB2LPENCLRR_TIM8LPEN              RCC_MC_APB2LPENCLRR_TIM8LPEN_Msk                   /*!< TIM8 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENCLRR_TIM15LPEN_Pos         (2U)
#define RCC_MC_APB2LPENCLRR_TIM15LPEN_Msk         (0x1U << RCC_MC_APB2LPENCLRR_TIM15LPEN_Pos)        /*!< 0x00000004 */
#define RCC_MC_APB2LPENCLRR_TIM15LPEN             RCC_MC_APB2LPENCLRR_TIM15LPEN_Msk                  /*!< TIM15 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENCLRR_TIM16LPEN_Pos         (3U)
#define RCC_MC_APB2LPENCLRR_TIM16LPEN_Msk         (0x1U << RCC_MC_APB2LPENCLRR_TIM16LPEN_Pos)        /*!< 0x00000008 */
#define RCC_MC_APB2LPENCLRR_TIM16LPEN             RCC_MC_APB2LPENCLRR_TIM16LPEN_Msk                  /*!< TIM16 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENCLRR_TIM17LPEN_Pos         (4U)
#define RCC_MC_APB2LPENCLRR_TIM17LPEN_Msk         (0x1U << RCC_MC_APB2LPENCLRR_TIM17LPEN_Pos)        /*!< 0x00000010 */
#define RCC_MC_APB2LPENCLRR_TIM17LPEN             RCC_MC_APB2LPENCLRR_TIM17LPEN_Msk                  /*!< TIM17 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENCLRR_SPI1LPEN_Pos          (8U)
#define RCC_MC_APB2LPENCLRR_SPI1LPEN_Msk          (0x1U << RCC_MC_APB2LPENCLRR_SPI1LPEN_Pos)         /*!< 0x00000100 */
#define RCC_MC_APB2LPENCLRR_SPI1LPEN              RCC_MC_APB2LPENCLRR_SPI1LPEN_Msk                   /*!< SPI/I2S1 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENCLRR_SPI4LPEN_Pos          (9U)
#define RCC_MC_APB2LPENCLRR_SPI4LPEN_Msk          (0x1U << RCC_MC_APB2LPENCLRR_SPI4LPEN_Pos)         /*!< 0x00000200 */
#define RCC_MC_APB2LPENCLRR_SPI4LPEN              RCC_MC_APB2LPENCLRR_SPI4LPEN_Msk                   /*!< SPI4 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENCLRR_SPI5LPEN_Pos          (10U)
#define RCC_MC_APB2LPENCLRR_SPI5LPEN_Msk          (0x1U << RCC_MC_APB2LPENCLRR_SPI5LPEN_Pos)         /*!< 0x00000400 */
#define RCC_MC_APB2LPENCLRR_SPI5LPEN              RCC_MC_APB2LPENCLRR_SPI5LPEN_Msk                   /*!< SPI5 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENCLRR_USART6LPEN_Pos        (13U)
#define RCC_MC_APB2LPENCLRR_USART6LPEN_Msk        (0x1U << RCC_MC_APB2LPENCLRR_USART6LPEN_Pos)       /*!< 0x00002000 */
#define RCC_MC_APB2LPENCLRR_USART6LPEN            RCC_MC_APB2LPENCLRR_USART6LPEN_Msk                 /*!< USART6 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENCLRR_SAI1LPEN_Pos          (16U)
#define RCC_MC_APB2LPENCLRR_SAI1LPEN_Msk          (0x1U << RCC_MC_APB2LPENCLRR_SAI1LPEN_Pos)         /*!< 0x00010000 */
#define RCC_MC_APB2LPENCLRR_SAI1LPEN              RCC_MC_APB2LPENCLRR_SAI1LPEN_Msk                   /*!< SAI1 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENCLRR_SAI2LPEN_Pos          (17U)
#define RCC_MC_APB2LPENCLRR_SAI2LPEN_Msk          (0x1U << RCC_MC_APB2LPENCLRR_SAI2LPEN_Pos)         /*!< 0x00020000 */
#define RCC_MC_APB2LPENCLRR_SAI2LPEN              RCC_MC_APB2LPENCLRR_SAI2LPEN_Msk                   /*!< SAI2 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENCLRR_SAI3LPEN_Pos          (18U)
#define RCC_MC_APB2LPENCLRR_SAI3LPEN_Msk          (0x1U << RCC_MC_APB2LPENCLRR_SAI3LPEN_Pos)         /*!< 0x00040000 */
#define RCC_MC_APB2LPENCLRR_SAI3LPEN              RCC_MC_APB2LPENCLRR_SAI3LPEN_Msk                   /*!< SAI3 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENCLRR_DFSDMLPEN_Pos         (20U)
#define RCC_MC_APB2LPENCLRR_DFSDMLPEN_Msk         (0x1U << RCC_MC_APB2LPENCLRR_DFSDMLPEN_Pos)        /*!< 0x00100000 */
#define RCC_MC_APB2LPENCLRR_DFSDMLPEN             RCC_MC_APB2LPENCLRR_DFSDMLPEN_Msk                  /*!< DFSDM peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENCLRR_ADFSDMLPEN_Pos        (21U)
#define RCC_MC_APB2LPENCLRR_ADFSDMLPEN_Msk        (0x1U << RCC_MC_APB2LPENCLRR_ADFSDMLPEN_Pos)       /*!< 0x00200000 */
#define RCC_MC_APB2LPENCLRR_ADFSDMLPEN            RCC_MC_APB2LPENCLRR_ADFSDMLPEN_Msk                 /*!< Audio DFSDM peripheral clocks enable during CSleep mode */
#define RCC_MC_APB2LPENCLRR_FDCANLPEN_Pos         (24U)
#define RCC_MC_APB2LPENCLRR_FDCANLPEN_Msk         (0x1U << RCC_MC_APB2LPENCLRR_FDCANLPEN_Pos)        /*!< 0x01000000 */
#define RCC_MC_APB2LPENCLRR_FDCANLPEN             RCC_MC_APB2LPENCLRR_FDCANLPEN_Msk                  /*!< FDCAN and CANRAM peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MC_APB3LPENSETR register  **************/
#define RCC_MC_APB3LPENSETR_LPTIM2LPEN_Pos        (0U)
#define RCC_MC_APB3LPENSETR_LPTIM2LPEN_Msk        (0x1U << RCC_MC_APB3LPENSETR_LPTIM2LPEN_Pos)       /*!< 0x00000001 */
#define RCC_MC_APB3LPENSETR_LPTIM2LPEN            RCC_MC_APB3LPENSETR_LPTIM2LPEN_Msk                 /*!< LPTIM2 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB3LPENSETR_LPTIM3LPEN_Pos        (1U)
#define RCC_MC_APB3LPENSETR_LPTIM3LPEN_Msk        (0x1U << RCC_MC_APB3LPENSETR_LPTIM3LPEN_Pos)       /*!< 0x00000002 */
#define RCC_MC_APB3LPENSETR_LPTIM3LPEN            RCC_MC_APB3LPENSETR_LPTIM3LPEN_Msk                 /*!< LPTIM3 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB3LPENSETR_LPTIM4LPEN_Pos        (2U)
#define RCC_MC_APB3LPENSETR_LPTIM4LPEN_Msk        (0x1U << RCC_MC_APB3LPENSETR_LPTIM4LPEN_Pos)       /*!< 0x00000004 */
#define RCC_MC_APB3LPENSETR_LPTIM4LPEN            RCC_MC_APB3LPENSETR_LPTIM4LPEN_Msk                 /*!< LPTIM4 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB3LPENSETR_LPTIM5LPEN_Pos        (3U)
#define RCC_MC_APB3LPENSETR_LPTIM5LPEN_Msk        (0x1U << RCC_MC_APB3LPENSETR_LPTIM5LPEN_Pos)       /*!< 0x00000008 */
#define RCC_MC_APB3LPENSETR_LPTIM5LPEN            RCC_MC_APB3LPENSETR_LPTIM5LPEN_Msk                 /*!< LPTIM5 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB3LPENSETR_SAI4LPEN_Pos          (8U)
#define RCC_MC_APB3LPENSETR_SAI4LPEN_Msk          (0x1U << RCC_MC_APB3LPENSETR_SAI4LPEN_Pos)         /*!< 0x00000100 */
#define RCC_MC_APB3LPENSETR_SAI4LPEN              RCC_MC_APB3LPENSETR_SAI4LPEN_Msk                   /*!< SAI4 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB3LPENSETR_SYSCFGLPEN_Pos        (11U)
#define RCC_MC_APB3LPENSETR_SYSCFGLPEN_Msk        (0x1U << RCC_MC_APB3LPENSETR_SYSCFGLPEN_Pos)       /*!< 0x00000800 */
#define RCC_MC_APB3LPENSETR_SYSCFGLPEN            RCC_MC_APB3LPENSETR_SYSCFGLPEN_Msk                 /*!< SYSCFG peripheral clocks enable during CSleep mode */
#define RCC_MC_APB3LPENSETR_VREFLPEN_Pos          (13U)
#define RCC_MC_APB3LPENSETR_VREFLPEN_Msk          (0x1U << RCC_MC_APB3LPENSETR_VREFLPEN_Pos)         /*!< 0x00002000 */
#define RCC_MC_APB3LPENSETR_VREFLPEN              RCC_MC_APB3LPENSETR_VREFLPEN_Msk                   /*!< VREF peripheral clocks enable during CSleep mode */
#define RCC_MC_APB3LPENSETR_DTSLPEN_Pos           (16U)
#define RCC_MC_APB3LPENSETR_DTSLPEN_Msk           (0x1U << RCC_MC_APB3LPENSETR_DTSLPEN_Pos)          /*!< 0x00010000 */
#define RCC_MC_APB3LPENSETR_DTSLPEN               RCC_MC_APB3LPENSETR_DTSLPEN_Msk                    /*!< DTS peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MC_APB3LPENCLRR register  **************/
#define RCC_MC_APB3LPENCLRR_LPTIM2LPEN_Pos        (0U)
#define RCC_MC_APB3LPENCLRR_LPTIM2LPEN_Msk        (0x1U << RCC_MC_APB3LPENCLRR_LPTIM2LPEN_Pos)       /*!< 0x00000001 */
#define RCC_MC_APB3LPENCLRR_LPTIM2LPEN            RCC_MC_APB3LPENCLRR_LPTIM2LPEN_Msk                 /*!< LPTIM2 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB3LPENCLRR_LPTIM3LPEN_Pos        (1U)
#define RCC_MC_APB3LPENCLRR_LPTIM3LPEN_Msk        (0x1U << RCC_MC_APB3LPENCLRR_LPTIM3LPEN_Pos)       /*!< 0x00000002 */
#define RCC_MC_APB3LPENCLRR_LPTIM3LPEN            RCC_MC_APB3LPENCLRR_LPTIM3LPEN_Msk                 /*!< LPTIM3 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB3LPENCLRR_LPTIM4LPEN_Pos        (2U)
#define RCC_MC_APB3LPENCLRR_LPTIM4LPEN_Msk        (0x1U << RCC_MC_APB3LPENCLRR_LPTIM4LPEN_Pos)       /*!< 0x00000004 */
#define RCC_MC_APB3LPENCLRR_LPTIM4LPEN            RCC_MC_APB3LPENCLRR_LPTIM4LPEN_Msk                 /*!< LPTIM4 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB3LPENCLRR_LPTIM5LPEN_Pos        (3U)
#define RCC_MC_APB3LPENCLRR_LPTIM5LPEN_Msk        (0x1U << RCC_MC_APB3LPENCLRR_LPTIM5LPEN_Pos)       /*!< 0x00000008 */
#define RCC_MC_APB3LPENCLRR_LPTIM5LPEN            RCC_MC_APB3LPENCLRR_LPTIM5LPEN_Msk                 /*!< LPTIM5 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB3LPENCLRR_SAI4LPEN_Pos          (8U)
#define RCC_MC_APB3LPENCLRR_SAI4LPEN_Msk          (0x1U << RCC_MC_APB3LPENCLRR_SAI4LPEN_Pos)         /*!< 0x00000100 */
#define RCC_MC_APB3LPENCLRR_SAI4LPEN              RCC_MC_APB3LPENCLRR_SAI4LPEN_Msk                   /*!< SAI4 peripheral clocks enable during CSleep mode */
#define RCC_MC_APB3LPENCLRR_SYSCFGLPEN_Pos        (11U)
#define RCC_MC_APB3LPENCLRR_SYSCFGLPEN_Msk        (0x1U << RCC_MC_APB3LPENCLRR_SYSCFGLPEN_Pos)       /*!< 0x00000800 */
#define RCC_MC_APB3LPENCLRR_SYSCFGLPEN            RCC_MC_APB3LPENCLRR_SYSCFGLPEN_Msk                 /*!< SYSCFG peripheral clocks enable during CSleep mode */
#define RCC_MC_APB3LPENCLRR_VREFLPEN_Pos          (13U)
#define RCC_MC_APB3LPENCLRR_VREFLPEN_Msk          (0x1U << RCC_MC_APB3LPENCLRR_VREFLPEN_Pos)         /*!< 0x00002000 */
#define RCC_MC_APB3LPENCLRR_VREFLPEN              RCC_MC_APB3LPENCLRR_VREFLPEN_Msk                   /*!< VREF peripheral clocks enable during CSleep mode */
#define RCC_MC_APB3LPENCLRR_DTSLPEN_Pos           (16U)
#define RCC_MC_APB3LPENCLRR_DTSLPEN_Msk           (0x1U << RCC_MC_APB3LPENCLRR_DTSLPEN_Pos)          /*!< 0x00010000 */
#define RCC_MC_APB3LPENCLRR_DTSLPEN               RCC_MC_APB3LPENCLRR_DTSLPEN_Msk                    /*!< DTS peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MC_AHB2LPENSETR register  **************/
#define RCC_MC_AHB2LPENSETR_DMA1LPEN_Pos          (0U)
#define RCC_MC_AHB2LPENSETR_DMA1LPEN_Msk          (0x1U << RCC_MC_AHB2LPENSETR_DMA1LPEN_Pos)         /*!< 0x00000001 */
#define RCC_MC_AHB2LPENSETR_DMA1LPEN              RCC_MC_AHB2LPENSETR_DMA1LPEN_Msk                   /*!< DMA1 peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB2LPENSETR_DMA2LPEN_Pos          (1U)
#define RCC_MC_AHB2LPENSETR_DMA2LPEN_Msk          (0x1U << RCC_MC_AHB2LPENSETR_DMA2LPEN_Pos)         /*!< 0x00000002 */
#define RCC_MC_AHB2LPENSETR_DMA2LPEN              RCC_MC_AHB2LPENSETR_DMA2LPEN_Msk                   /*!< DMA2 peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB2LPENSETR_DMAMUXLPEN_Pos        (2U)
#define RCC_MC_AHB2LPENSETR_DMAMUXLPEN_Msk        (0x1U << RCC_MC_AHB2LPENSETR_DMAMUXLPEN_Pos)       /*!< 0x00000004 */
#define RCC_MC_AHB2LPENSETR_DMAMUXLPEN            RCC_MC_AHB2LPENSETR_DMAMUXLPEN_Msk                 /*!< DMAMUX peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB2LPENSETR_ADC12LPEN_Pos         (5U)
#define RCC_MC_AHB2LPENSETR_ADC12LPEN_Msk         (0x1U << RCC_MC_AHB2LPENSETR_ADC12LPEN_Pos)        /*!< 0x00000020 */
#define RCC_MC_AHB2LPENSETR_ADC12LPEN             RCC_MC_AHB2LPENSETR_ADC12LPEN_Msk                  /*!< ADC1&amp;2 peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB2LPENSETR_USBOLPEN_Pos          (8U)
#define RCC_MC_AHB2LPENSETR_USBOLPEN_Msk          (0x1U << RCC_MC_AHB2LPENSETR_USBOLPEN_Pos)         /*!< 0x00000100 */
#define RCC_MC_AHB2LPENSETR_USBOLPEN              RCC_MC_AHB2LPENSETR_USBOLPEN_Msk                   /*!< USBO peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB2LPENSETR_SDMMC3LPEN_Pos        (16U)
#define RCC_MC_AHB2LPENSETR_SDMMC3LPEN_Msk        (0x1U << RCC_MC_AHB2LPENSETR_SDMMC3LPEN_Pos)       /*!< 0x00010000 */
#define RCC_MC_AHB2LPENSETR_SDMMC3LPEN            RCC_MC_AHB2LPENSETR_SDMMC3LPEN_Msk                 /*!< SDMMC3 and SDMMC3 delay (DLYBSD3) block peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MC_AHB2LPENCLRR register  **************/
#define RCC_MC_AHB2LPENCLRR_DMA1LPEN_Pos          (0U)
#define RCC_MC_AHB2LPENCLRR_DMA1LPEN_Msk          (0x1U << RCC_MC_AHB2LPENCLRR_DMA1LPEN_Pos)         /*!< 0x00000001 */
#define RCC_MC_AHB2LPENCLRR_DMA1LPEN              RCC_MC_AHB2LPENCLRR_DMA1LPEN_Msk                   /*!< DMA1 peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB2LPENCLRR_DMA2LPEN_Pos          (1U)
#define RCC_MC_AHB2LPENCLRR_DMA2LPEN_Msk          (0x1U << RCC_MC_AHB2LPENCLRR_DMA2LPEN_Pos)         /*!< 0x00000002 */
#define RCC_MC_AHB2LPENCLRR_DMA2LPEN              RCC_MC_AHB2LPENCLRR_DMA2LPEN_Msk                   /*!< DMA2 peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB2LPENCLRR_DMAMUXLPEN_Pos        (2U)
#define RCC_MC_AHB2LPENCLRR_DMAMUXLPEN_Msk        (0x1U << RCC_MC_AHB2LPENCLRR_DMAMUXLPEN_Pos)       /*!< 0x00000004 */
#define RCC_MC_AHB2LPENCLRR_DMAMUXLPEN            RCC_MC_AHB2LPENCLRR_DMAMUXLPEN_Msk                 /*!< DMAMUX peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB2LPENCLRR_ADC12LPEN_Pos         (5U)
#define RCC_MC_AHB2LPENCLRR_ADC12LPEN_Msk         (0x1U << RCC_MC_AHB2LPENCLRR_ADC12LPEN_Pos)        /*!< 0x00000020 */
#define RCC_MC_AHB2LPENCLRR_ADC12LPEN             RCC_MC_AHB2LPENCLRR_ADC12LPEN_Msk                  /*!< ADC1&amp;2 peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB2LPENCLRR_USBOLPEN_Pos          (8U)
#define RCC_MC_AHB2LPENCLRR_USBOLPEN_Msk          (0x1U << RCC_MC_AHB2LPENCLRR_USBOLPEN_Pos)         /*!< 0x00000100 */
#define RCC_MC_AHB2LPENCLRR_USBOLPEN              RCC_MC_AHB2LPENCLRR_USBOLPEN_Msk                   /*!< USBO peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB2LPENCLRR_SDMMC3LPEN_Pos        (16U)
#define RCC_MC_AHB2LPENCLRR_SDMMC3LPEN_Msk        (0x1U << RCC_MC_AHB2LPENCLRR_SDMMC3LPEN_Pos)       /*!< 0x00010000 */
#define RCC_MC_AHB2LPENCLRR_SDMMC3LPEN            RCC_MC_AHB2LPENCLRR_SDMMC3LPEN_Msk                 /*!< SDMMC3 and SDMMC3 delay (DLYBSD3) block peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MC_AHB3LPENSETR register  **************/
#define RCC_MC_AHB3LPENSETR_DCMILPEN_Pos          (0U)
#define RCC_MC_AHB3LPENSETR_DCMILPEN_Msk          (0x1U << RCC_MC_AHB3LPENSETR_DCMILPEN_Pos)         /*!< 0x00000001 */
#define RCC_MC_AHB3LPENSETR_DCMILPEN              RCC_MC_AHB3LPENSETR_DCMILPEN_Msk                   /*!< DCMI peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB3LPENSETR_CRYP2LPEN_Pos         (4U)
#define RCC_MC_AHB3LPENSETR_CRYP2LPEN_Msk         (0x1U << RCC_MC_AHB3LPENSETR_CRYP2LPEN_Pos)        /*!< 0x00000010 */
#define RCC_MC_AHB3LPENSETR_CRYP2LPEN             RCC_MC_AHB3LPENSETR_CRYP2LPEN_Msk                  /*!< CRYP2 (3DES/AES2) peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB3LPENSETR_HASH2LPEN_Pos         (5U)
#define RCC_MC_AHB3LPENSETR_HASH2LPEN_Msk         (0x1U << RCC_MC_AHB3LPENSETR_HASH2LPEN_Pos)        /*!< 0x00000020 */
#define RCC_MC_AHB3LPENSETR_HASH2LPEN             RCC_MC_AHB3LPENSETR_HASH2LPEN_Msk                  /*!< HASH2 peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB3LPENSETR_RNG2LPEN_Pos          (6U)
#define RCC_MC_AHB3LPENSETR_RNG2LPEN_Msk          (0x1U << RCC_MC_AHB3LPENSETR_RNG2LPEN_Pos)         /*!< 0x00000040 */
#define RCC_MC_AHB3LPENSETR_RNG2LPEN              RCC_MC_AHB3LPENSETR_RNG2LPEN_Msk                   /*!< RNG2 peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB3LPENSETR_CRC2LPEN_Pos          (7U)
#define RCC_MC_AHB3LPENSETR_CRC2LPEN_Msk          (0x1U << RCC_MC_AHB3LPENSETR_CRC2LPEN_Pos)         /*!< 0x00000080 */
#define RCC_MC_AHB3LPENSETR_CRC2LPEN              RCC_MC_AHB3LPENSETR_CRC2LPEN_Msk                   /*!< CRC2 peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB3LPENSETR_HSEMLPEN_Pos          (11U)
#define RCC_MC_AHB3LPENSETR_HSEMLPEN_Msk          (0x1U << RCC_MC_AHB3LPENSETR_HSEMLPEN_Pos)         /*!< 0x00000800 */
#define RCC_MC_AHB3LPENSETR_HSEMLPEN              RCC_MC_AHB3LPENSETR_HSEMLPEN_Msk                   /*!< HSEM peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB3LPENSETR_IPCCLPEN_Pos          (12U)
#define RCC_MC_AHB3LPENSETR_IPCCLPEN_Msk          (0x1U << RCC_MC_AHB3LPENSETR_IPCCLPEN_Pos)         /*!< 0x00001000 */
#define RCC_MC_AHB3LPENSETR_IPCCLPEN              RCC_MC_AHB3LPENSETR_IPCCLPEN_Msk                   /*!< IPCC peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MC_AHB3LPENCLRR register  **************/
#define RCC_MC_AHB3LPENCLRR_DCMILPEN_Pos          (0U)
#define RCC_MC_AHB3LPENCLRR_DCMILPEN_Msk          (0x1U << RCC_MC_AHB3LPENCLRR_DCMILPEN_Pos)         /*!< 0x00000001 */
#define RCC_MC_AHB3LPENCLRR_DCMILPEN              RCC_MC_AHB3LPENCLRR_DCMILPEN_Msk                   /*!< DCMI peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB3LPENCLRR_CRYP2LPEN_Pos         (4U)
#define RCC_MC_AHB3LPENCLRR_CRYP2LPEN_Msk         (0x1U << RCC_MC_AHB3LPENCLRR_CRYP2LPEN_Pos)        /*!< 0x00000010 */
#define RCC_MC_AHB3LPENCLRR_CRYP2LPEN             RCC_MC_AHB3LPENCLRR_CRYP2LPEN_Msk                  /*!< CRYP2 (3DES/AES2) peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB3LPENCLRR_HASH2LPEN_Pos         (5U)
#define RCC_MC_AHB3LPENCLRR_HASH2LPEN_Msk         (0x1U << RCC_MC_AHB3LPENCLRR_HASH2LPEN_Pos)        /*!< 0x00000020 */
#define RCC_MC_AHB3LPENCLRR_HASH2LPEN             RCC_MC_AHB3LPENCLRR_HASH2LPEN_Msk                  /*!< HASH2 peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB3LPENCLRR_RNG2LPEN_Pos          (6U)
#define RCC_MC_AHB3LPENCLRR_RNG2LPEN_Msk          (0x1U << RCC_MC_AHB3LPENCLRR_RNG2LPEN_Pos)         /*!< 0x00000040 */
#define RCC_MC_AHB3LPENCLRR_RNG2LPEN              RCC_MC_AHB3LPENCLRR_RNG2LPEN_Msk                   /*!< RNG2 peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB3LPENCLRR_CRC2LPEN_Pos          (7U)
#define RCC_MC_AHB3LPENCLRR_CRC2LPEN_Msk          (0x1U << RCC_MC_AHB3LPENCLRR_CRC2LPEN_Pos)         /*!< 0x00000080 */
#define RCC_MC_AHB3LPENCLRR_CRC2LPEN              RCC_MC_AHB3LPENCLRR_CRC2LPEN_Msk                   /*!< CRC2 peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB3LPENCLRR_HSEMLPEN_Pos          (11U)
#define RCC_MC_AHB3LPENCLRR_HSEMLPEN_Msk          (0x1U << RCC_MC_AHB3LPENCLRR_HSEMLPEN_Pos)         /*!< 0x00000800 */
#define RCC_MC_AHB3LPENCLRR_HSEMLPEN              RCC_MC_AHB3LPENCLRR_HSEMLPEN_Msk                   /*!< HSEM peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB3LPENCLRR_IPCCLPEN_Pos          (12U)
#define RCC_MC_AHB3LPENCLRR_IPCCLPEN_Msk          (0x1U << RCC_MC_AHB3LPENCLRR_IPCCLPEN_Pos)         /*!< 0x00001000 */
#define RCC_MC_AHB3LPENCLRR_IPCCLPEN              RCC_MC_AHB3LPENCLRR_IPCCLPEN_Msk                   /*!< IPCC peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MC_AHB4LPENSETR register  **************/
#define RCC_MC_AHB4LPENSETR_GPIOALPEN_Pos         (0U)
#define RCC_MC_AHB4LPENSETR_GPIOALPEN_Msk         (0x1U << RCC_MC_AHB4LPENSETR_GPIOALPEN_Pos)        /*!< 0x00000001 */
#define RCC_MC_AHB4LPENSETR_GPIOALPEN             RCC_MC_AHB4LPENSETR_GPIOALPEN_Msk                  /*!< GPIOA peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB4LPENSETR_GPIOBLPEN_Pos         (1U)
#define RCC_MC_AHB4LPENSETR_GPIOBLPEN_Msk         (0x1U << RCC_MC_AHB4LPENSETR_GPIOBLPEN_Pos)        /*!< 0x00000002 */
#define RCC_MC_AHB4LPENSETR_GPIOBLPEN             RCC_MC_AHB4LPENSETR_GPIOBLPEN_Msk                  /*!< GPIOB peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB4LPENSETR_GPIOCLPEN_Pos         (2U)
#define RCC_MC_AHB4LPENSETR_GPIOCLPEN_Msk         (0x1U << RCC_MC_AHB4LPENSETR_GPIOCLPEN_Pos)        /*!< 0x00000004 */
#define RCC_MC_AHB4LPENSETR_GPIOCLPEN             RCC_MC_AHB4LPENSETR_GPIOCLPEN_Msk                  /*!< GPIOC peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB4LPENSETR_GPIODLPEN_Pos         (3U)
#define RCC_MC_AHB4LPENSETR_GPIODLPEN_Msk         (0x1U << RCC_MC_AHB4LPENSETR_GPIODLPEN_Pos)        /*!< 0x00000008 */
#define RCC_MC_AHB4LPENSETR_GPIODLPEN             RCC_MC_AHB4LPENSETR_GPIODLPEN_Msk                  /*!< GPIOD peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB4LPENSETR_GPIOELPEN_Pos         (4U)
#define RCC_MC_AHB4LPENSETR_GPIOELPEN_Msk         (0x1U << RCC_MC_AHB4LPENSETR_GPIOELPEN_Pos)        /*!< 0x00000010 */
#define RCC_MC_AHB4LPENSETR_GPIOELPEN             RCC_MC_AHB4LPENSETR_GPIOELPEN_Msk                  /*!< GPIOE peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB4LPENSETR_GPIOFLPEN_Pos         (5U)
#define RCC_MC_AHB4LPENSETR_GPIOFLPEN_Msk         (0x1U << RCC_MC_AHB4LPENSETR_GPIOFLPEN_Pos)        /*!< 0x00000020 */
#define RCC_MC_AHB4LPENSETR_GPIOFLPEN             RCC_MC_AHB4LPENSETR_GPIOFLPEN_Msk                  /*!< GPIOF peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB4LPENSETR_GPIOGLPEN_Pos         (6U)
#define RCC_MC_AHB4LPENSETR_GPIOGLPEN_Msk         (0x1U << RCC_MC_AHB4LPENSETR_GPIOGLPEN_Pos)        /*!< 0x00000040 */
#define RCC_MC_AHB4LPENSETR_GPIOGLPEN             RCC_MC_AHB4LPENSETR_GPIOGLPEN_Msk                  /*!< GPIOG peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB4LPENSETR_GPIOHLPEN_Pos         (7U)
#define RCC_MC_AHB4LPENSETR_GPIOHLPEN_Msk         (0x1U << RCC_MC_AHB4LPENSETR_GPIOHLPEN_Pos)        /*!< 0x00000080 */
#define RCC_MC_AHB4LPENSETR_GPIOHLPEN             RCC_MC_AHB4LPENSETR_GPIOHLPEN_Msk                  /*!< GPIOH peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB4LPENSETR_GPIOILPEN_Pos         (8U)
#define RCC_MC_AHB4LPENSETR_GPIOILPEN_Msk         (0x1U << RCC_MC_AHB4LPENSETR_GPIOILPEN_Pos)        /*!< 0x00000100 */
#define RCC_MC_AHB4LPENSETR_GPIOILPEN             RCC_MC_AHB4LPENSETR_GPIOILPEN_Msk                  /*!< GPIOI peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB4LPENSETR_GPIOJLPEN_Pos         (9U)
#define RCC_MC_AHB4LPENSETR_GPIOJLPEN_Msk         (0x1U << RCC_MC_AHB4LPENSETR_GPIOJLPEN_Pos)        /*!< 0x00000200 */
#define RCC_MC_AHB4LPENSETR_GPIOJLPEN             RCC_MC_AHB4LPENSETR_GPIOJLPEN_Msk                  /*!< GPIOJ peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB4LPENSETR_GPIOKLPEN_Pos         (10U)
#define RCC_MC_AHB4LPENSETR_GPIOKLPEN_Msk         (0x1U << RCC_MC_AHB4LPENSETR_GPIOKLPEN_Pos)        /*!< 0x00000400 */
#define RCC_MC_AHB4LPENSETR_GPIOKLPEN             RCC_MC_AHB4LPENSETR_GPIOKLPEN_Msk                  /*!< GPIOK peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MC_AHB4LPENCLRR register  **************/
#define RCC_MC_AHB4LPENCLRR_GPIOALPEN_Pos         (0U)
#define RCC_MC_AHB4LPENCLRR_GPIOALPEN_Msk         (0x1U << RCC_MC_AHB4LPENCLRR_GPIOALPEN_Pos)        /*!< 0x00000001 */
#define RCC_MC_AHB4LPENCLRR_GPIOALPEN             RCC_MC_AHB4LPENCLRR_GPIOALPEN_Msk                  /*!< GPIOA peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB4LPENCLRR_GPIOBLPEN_Pos         (1U)
#define RCC_MC_AHB4LPENCLRR_GPIOBLPEN_Msk         (0x1U << RCC_MC_AHB4LPENCLRR_GPIOBLPEN_Pos)        /*!< 0x00000002 */
#define RCC_MC_AHB4LPENCLRR_GPIOBLPEN             RCC_MC_AHB4LPENCLRR_GPIOBLPEN_Msk                  /*!< GPIOB peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB4LPENCLRR_GPIOCLPEN_Pos         (2U)
#define RCC_MC_AHB4LPENCLRR_GPIOCLPEN_Msk         (0x1U << RCC_MC_AHB4LPENCLRR_GPIOCLPEN_Pos)        /*!< 0x00000004 */
#define RCC_MC_AHB4LPENCLRR_GPIOCLPEN             RCC_MC_AHB4LPENCLRR_GPIOCLPEN_Msk                  /*!< GPIOC peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB4LPENCLRR_GPIODLPEN_Pos         (3U)
#define RCC_MC_AHB4LPENCLRR_GPIODLPEN_Msk         (0x1U << RCC_MC_AHB4LPENCLRR_GPIODLPEN_Pos)        /*!< 0x00000008 */
#define RCC_MC_AHB4LPENCLRR_GPIODLPEN             RCC_MC_AHB4LPENCLRR_GPIODLPEN_Msk                  /*!< GPIOD peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB4LPENCLRR_GPIOELPEN_Pos         (4U)
#define RCC_MC_AHB4LPENCLRR_GPIOELPEN_Msk         (0x1U << RCC_MC_AHB4LPENCLRR_GPIOELPEN_Pos)        /*!< 0x00000010 */
#define RCC_MC_AHB4LPENCLRR_GPIOELPEN             RCC_MC_AHB4LPENCLRR_GPIOELPEN_Msk                  /*!< GPIOE peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB4LPENCLRR_GPIOFLPEN_Pos         (5U)
#define RCC_MC_AHB4LPENCLRR_GPIOFLPEN_Msk         (0x1U << RCC_MC_AHB4LPENCLRR_GPIOFLPEN_Pos)        /*!< 0x00000020 */
#define RCC_MC_AHB4LPENCLRR_GPIOFLPEN             RCC_MC_AHB4LPENCLRR_GPIOFLPEN_Msk                  /*!< GPIOF peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB4LPENCLRR_GPIOGLPEN_Pos         (6U)
#define RCC_MC_AHB4LPENCLRR_GPIOGLPEN_Msk         (0x1U << RCC_MC_AHB4LPENCLRR_GPIOGLPEN_Pos)        /*!< 0x00000040 */
#define RCC_MC_AHB4LPENCLRR_GPIOGLPEN             RCC_MC_AHB4LPENCLRR_GPIOGLPEN_Msk                  /*!< GPIOG peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB4LPENCLRR_GPIOHLPEN_Pos         (7U)
#define RCC_MC_AHB4LPENCLRR_GPIOHLPEN_Msk         (0x1U << RCC_MC_AHB4LPENCLRR_GPIOHLPEN_Pos)        /*!< 0x00000080 */
#define RCC_MC_AHB4LPENCLRR_GPIOHLPEN             RCC_MC_AHB4LPENCLRR_GPIOHLPEN_Msk                  /*!< GPIOH peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB4LPENCLRR_GPIOILPEN_Pos         (8U)
#define RCC_MC_AHB4LPENCLRR_GPIOILPEN_Msk         (0x1U << RCC_MC_AHB4LPENCLRR_GPIOILPEN_Pos)        /*!< 0x00000100 */
#define RCC_MC_AHB4LPENCLRR_GPIOILPEN             RCC_MC_AHB4LPENCLRR_GPIOILPEN_Msk                  /*!< GPIOI peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB4LPENCLRR_GPIOJLPEN_Pos         (9U)
#define RCC_MC_AHB4LPENCLRR_GPIOJLPEN_Msk         (0x1U << RCC_MC_AHB4LPENCLRR_GPIOJLPEN_Pos)        /*!< 0x00000200 */
#define RCC_MC_AHB4LPENCLRR_GPIOJLPEN             RCC_MC_AHB4LPENCLRR_GPIOJLPEN_Msk                  /*!< GPIOJ peripheral clocks enable during CSleep mode */
#define RCC_MC_AHB4LPENCLRR_GPIOKLPEN_Pos         (10U)
#define RCC_MC_AHB4LPENCLRR_GPIOKLPEN_Msk         (0x1U << RCC_MC_AHB4LPENCLRR_GPIOKLPEN_Pos)        /*!< 0x00000400 */
#define RCC_MC_AHB4LPENCLRR_GPIOKLPEN             RCC_MC_AHB4LPENCLRR_GPIOKLPEN_Msk                  /*!< GPIOK peripheral clocks enable during CSleep mode */

/*************  Bit definition for RCC_MC_AXIMLPENSETR register  **************/
#define RCC_MC_AXIMLPENSETR_SYSRAMLPEN_Pos        (0U)
#define RCC_MC_AXIMLPENSETR_SYSRAMLPEN_Msk        (0x1U << RCC_MC_AXIMLPENSETR_SYSRAMLPEN_Pos)       /*!< 0x00000001 */
#define RCC_MC_AXIMLPENSETR_SYSRAMLPEN            RCC_MC_AXIMLPENSETR_SYSRAMLPEN_Msk                 /*!< SYSRAM interface clock enable during CSleep mode */

/*************  Bit definition for RCC_MC_AXIMLPENCLRR register  **************/
#define RCC_MC_AXIMLPENCLRR_SYSRAMLPEN_Pos        (0U)
#define RCC_MC_AXIMLPENCLRR_SYSRAMLPEN_Msk        (0x1U << RCC_MC_AXIMLPENCLRR_SYSRAMLPEN_Pos)       /*!< 0x00000001 */
#define RCC_MC_AXIMLPENCLRR_SYSRAMLPEN            RCC_MC_AXIMLPENCLRR_SYSRAMLPEN_Msk                 /*!< SYSRAM interface clock enable during CSleep mode */

/*************  Bit definition for RCC_MC_MLAHBLPENSETR register  *************/
#define RCC_MC_MLAHBLPENSETR_SRAM1LPEN_Pos        (0U)
#define RCC_MC_MLAHBLPENSETR_SRAM1LPEN_Msk        (0x1U << RCC_MC_MLAHBLPENSETR_SRAM1LPEN_Pos)       /*!< 0x00000001 */
#define RCC_MC_MLAHBLPENSETR_SRAM1LPEN            RCC_MC_MLAHBLPENSETR_SRAM1LPEN_Msk                 /*!< SRAM1 interface clock enable during CSleep mode */
#define RCC_MC_MLAHBLPENSETR_SRAM2LPEN_Pos        (1U)
#define RCC_MC_MLAHBLPENSETR_SRAM2LPEN_Msk        (0x1U << RCC_MC_MLAHBLPENSETR_SRAM2LPEN_Pos)       /*!< 0x00000002 */
#define RCC_MC_MLAHBLPENSETR_SRAM2LPEN            RCC_MC_MLAHBLPENSETR_SRAM2LPEN_Msk                 /*!< SRAM2 interface clock enable during CSleep mode */
#define RCC_MC_MLAHBLPENSETR_SRAM34LPEN_Pos       (2U)
#define RCC_MC_MLAHBLPENSETR_SRAM34LPEN_Msk       (0x1U << RCC_MC_MLAHBLPENSETR_SRAM34LPEN_Pos)      /*!< 0x00000004 */
#define RCC_MC_MLAHBLPENSETR_SRAM34LPEN           RCC_MC_MLAHBLPENSETR_SRAM34LPEN_Msk                /*!< SRAM3 and SRAM4 interface clock enable during CSleep mode */
#define RCC_MC_MLAHBLPENSETR_RETRAMLPEN_Pos       (4U)
#define RCC_MC_MLAHBLPENSETR_RETRAMLPEN_Msk       (0x1U << RCC_MC_MLAHBLPENSETR_RETRAMLPEN_Pos)      /*!< 0x00000010 */
#define RCC_MC_MLAHBLPENSETR_RETRAMLPEN           RCC_MC_MLAHBLPENSETR_RETRAMLPEN_Msk                /*!< RETRAM interface clock enable during CSleep mode */

/*************  Bit definition for RCC_MC_MLAHBLPENCLRR register  *************/
#define RCC_MC_MLAHBLPENCLRR_SRAM1LPEN_Pos        (0U)
#define RCC_MC_MLAHBLPENCLRR_SRAM1LPEN_Msk        (0x1U << RCC_MC_MLAHBLPENCLRR_SRAM1LPEN_Pos)       /*!< 0x00000001 */
#define RCC_MC_MLAHBLPENCLRR_SRAM1LPEN            RCC_MC_MLAHBLPENCLRR_SRAM1LPEN_Msk                 /*!< SRAM1 interface clock enable during CSleep mode */
#define RCC_MC_MLAHBLPENCLRR_SRAM2LPEN_Pos        (1U)
#define RCC_MC_MLAHBLPENCLRR_SRAM2LPEN_Msk        (0x1U << RCC_MC_MLAHBLPENCLRR_SRAM2LPEN_Pos)       /*!< 0x00000002 */
#define RCC_MC_MLAHBLPENCLRR_SRAM2LPEN            RCC_MC_MLAHBLPENCLRR_SRAM2LPEN_Msk                 /*!< SRAM2 interface clock enable during CSleep mode */
#define RCC_MC_MLAHBLPENCLRR_SRAM34LPEN_Pos       (2U)
#define RCC_MC_MLAHBLPENCLRR_SRAM34LPEN_Msk       (0x1U << RCC_MC_MLAHBLPENCLRR_SRAM34LPEN_Pos)      /*!< 0x00000004 */
#define RCC_MC_MLAHBLPENCLRR_SRAM34LPEN           RCC_MC_MLAHBLPENCLRR_SRAM34LPEN_Msk                /*!< SRAM3 and SRAM4 interface clock enable during CSleep mode */
#define RCC_MC_MLAHBLPENCLRR_RETRAMLPEN_Pos       (4U)
#define RCC_MC_MLAHBLPENCLRR_RETRAMLPEN_Msk       (0x1U << RCC_MC_MLAHBLPENCLRR_RETRAMLPEN_Pos)      /*!< 0x00000010 */
#define RCC_MC_MLAHBLPENCLRR_RETRAMLPEN           RCC_MC_MLAHBLPENCLRR_RETRAMLPEN_Msk                /*!< RETRAM interface clock enable during CSleep mode */

/***************  Bit definition for RCC_MC_RSTSCLRR register  ****************/
#define RCC_MC_RSTSCLRR_PORRSTF_Pos               (0U)
#define RCC_MC_RSTSCLRR_PORRSTF_Msk               (0x1U << RCC_MC_RSTSCLRR_PORRSTF_Pos)              /*!< 0x00000001 */
#define RCC_MC_RSTSCLRR_PORRSTF                   RCC_MC_RSTSCLRR_PORRSTF_Msk                        /*!< POR/PDR reset flag */
#define RCC_MC_RSTSCLRR_BORRSTF_Pos               (1U)
#define RCC_MC_RSTSCLRR_BORRSTF_Msk               (0x1U << RCC_MC_RSTSCLRR_BORRSTF_Pos)              /*!< 0x00000002 */
#define RCC_MC_RSTSCLRR_BORRSTF                   RCC_MC_RSTSCLRR_BORRSTF_Msk                        /*!< BOR reset flag */
#define RCC_MC_RSTSCLRR_PADRSTF_Pos               (2U)
#define RCC_MC_RSTSCLRR_PADRSTF_Msk               (0x1U << RCC_MC_RSTSCLRR_PADRSTF_Pos)              /*!< 0x00000004 */
#define RCC_MC_RSTSCLRR_PADRSTF                   RCC_MC_RSTSCLRR_PADRSTF_Msk                        /*!< NRST reset flag */
#define RCC_MC_RSTSCLRR_HCSSRSTF_Pos              (3U)
#define RCC_MC_RSTSCLRR_HCSSRSTF_Msk              (0x1U << RCC_MC_RSTSCLRR_HCSSRSTF_Pos)             /*!< 0x00000008 */
#define RCC_MC_RSTSCLRR_HCSSRSTF                  RCC_MC_RSTSCLRR_HCSSRSTF_Msk                       /*!< HSE CSS reset flag */
#define RCC_MC_RSTSCLRR_VCORERSTF_Pos             (4U)
#define RCC_MC_RSTSCLRR_VCORERSTF_Msk             (0x1U << RCC_MC_RSTSCLRR_VCORERSTF_Pos)            /*!< 0x00000010 */
#define RCC_MC_RSTSCLRR_VCORERSTF                 RCC_MC_RSTSCLRR_VCORERSTF_Msk                      /*!< VDDCORE reset flag */
#define RCC_MC_RSTSCLRR_MCURSTF_Pos               (5U)
#define RCC_MC_RSTSCLRR_MCURSTF_Msk               (0x1U << RCC_MC_RSTSCLRR_MCURSTF_Pos)              /*!< 0x00000020 */
#define RCC_MC_RSTSCLRR_MCURSTF                   RCC_MC_RSTSCLRR_MCURSTF_Msk                        /*!< MCU reset flag */
#define RCC_MC_RSTSCLRR_MPSYSRSTF_Pos             (6U)
#define RCC_MC_RSTSCLRR_MPSYSRSTF_Msk             (0x1U << RCC_MC_RSTSCLRR_MPSYSRSTF_Pos)            /*!< 0x00000040 */
#define RCC_MC_RSTSCLRR_MPSYSRSTF                 RCC_MC_RSTSCLRR_MPSYSRSTF_Msk                      /*!< MPU System reset flag */
#define RCC_MC_RSTSCLRR_MCSYSRSTF_Pos             (7U)
#define RCC_MC_RSTSCLRR_MCSYSRSTF_Msk             (0x1U << RCC_MC_RSTSCLRR_MCSYSRSTF_Pos)            /*!< 0x00000080 */
#define RCC_MC_RSTSCLRR_MCSYSRSTF                 RCC_MC_RSTSCLRR_MCSYSRSTF_Msk                      /*!< MCU System reset flag */
#define RCC_MC_RSTSCLRR_IWDG1RSTF_Pos             (8U)
#define RCC_MC_RSTSCLRR_IWDG1RSTF_Msk             (0x1U << RCC_MC_RSTSCLRR_IWDG1RSTF_Pos)            /*!< 0x00000100 */
#define RCC_MC_RSTSCLRR_IWDG1RSTF                 RCC_MC_RSTSCLRR_IWDG1RSTF_Msk                      /*!< IWDG1 reset flag */
#define RCC_MC_RSTSCLRR_IWDG2RSTF_Pos             (9U)
#define RCC_MC_RSTSCLRR_IWDG2RSTF_Msk             (0x1U << RCC_MC_RSTSCLRR_IWDG2RSTF_Pos)            /*!< 0x00000200 */
#define RCC_MC_RSTSCLRR_IWDG2RSTF                 RCC_MC_RSTSCLRR_IWDG2RSTF_Msk                      /*!< IWDG2 reset flag */
#define RCC_MC_RSTSCLRR_WWDG1RSTF_Pos             (10U)
#define RCC_MC_RSTSCLRR_WWDG1RSTF_Msk             (0x1U << RCC_MC_RSTSCLRR_WWDG1RSTF_Pos)            /*!< 0x00000400 */
#define RCC_MC_RSTSCLRR_WWDG1RSTF                 RCC_MC_RSTSCLRR_WWDG1RSTF_Msk                      /*!< WWDG1 reset flag */

/*****************  Bit definition for RCC_MC_CIER register  ******************/
#define RCC_MC_CIER_LSIRDYIE_Pos                  (0U)
#define RCC_MC_CIER_LSIRDYIE_Msk                  (0x1U << RCC_MC_CIER_LSIRDYIE_Pos)                 /*!< 0x00000001 */
#define RCC_MC_CIER_LSIRDYIE                      RCC_MC_CIER_LSIRDYIE_Msk                           /*!< LSI ready Interrupt Enable */
#define RCC_MC_CIER_LSERDYIE_Pos                  (1U)
#define RCC_MC_CIER_LSERDYIE_Msk                  (0x1U << RCC_MC_CIER_LSERDYIE_Pos)                 /*!< 0x00000002 */
#define RCC_MC_CIER_LSERDYIE                      RCC_MC_CIER_LSERDYIE_Msk                           /*!< LSE ready Interrupt Enable */
#define RCC_MC_CIER_HSIRDYIE_Pos                  (2U)
#define RCC_MC_CIER_HSIRDYIE_Msk                  (0x1U << RCC_MC_CIER_HSIRDYIE_Pos)                 /*!< 0x00000004 */
#define RCC_MC_CIER_HSIRDYIE                      RCC_MC_CIER_HSIRDYIE_Msk                           /*!< HSI ready Interrupt Enable */
#define RCC_MC_CIER_HSERDYIE_Pos                  (3U)
#define RCC_MC_CIER_HSERDYIE_Msk                  (0x1U << RCC_MC_CIER_HSERDYIE_Pos)                 /*!< 0x00000008 */
#define RCC_MC_CIER_HSERDYIE                      RCC_MC_CIER_HSERDYIE_Msk                           /*!< HSE ready Interrupt Enable */
#define RCC_MC_CIER_CSIRDYIE_Pos                  (4U)
#define RCC_MC_CIER_CSIRDYIE_Msk                  (0x1U << RCC_MC_CIER_CSIRDYIE_Pos)                 /*!< 0x00000010 */
#define RCC_MC_CIER_CSIRDYIE                      RCC_MC_CIER_CSIRDYIE_Msk                           /*!< CSI ready Interrupt Enable */
#define RCC_MC_CIER_PLL1DYIE_Pos                  (8U)
#define RCC_MC_CIER_PLL1DYIE_Msk                  (0x1U << RCC_MC_CIER_PLL1DYIE_Pos)                 /*!< 0x00000100 */
#define RCC_MC_CIER_PLL1DYIE                      RCC_MC_CIER_PLL1DYIE_Msk                           /*!< PLL1 ready Interrupt Enable */
#define RCC_MC_CIER_PLL2DYIE_Pos                  (9U)
#define RCC_MC_CIER_PLL2DYIE_Msk                  (0x1U << RCC_MC_CIER_PLL2DYIE_Pos)                 /*!< 0x00000200 */
#define RCC_MC_CIER_PLL2DYIE                      RCC_MC_CIER_PLL2DYIE_Msk                           /*!< PLL2 ready Interrupt Enable */
#define RCC_MC_CIER_PLL3DYIE_Pos                  (10U)
#define RCC_MC_CIER_PLL3DYIE_Msk                  (0x1U << RCC_MC_CIER_PLL3DYIE_Pos)                 /*!< 0x00000400 */
#define RCC_MC_CIER_PLL3DYIE                      RCC_MC_CIER_PLL3DYIE_Msk                           /*!< PLL3 ready Interrupt Enable */
#define RCC_MC_CIER_PLL4DYIE_Pos                  (11U)
#define RCC_MC_CIER_PLL4DYIE_Msk                  (0x1U << RCC_MC_CIER_PLL4DYIE_Pos)                 /*!< 0x00000800 */
#define RCC_MC_CIER_PLL4DYIE                      RCC_MC_CIER_PLL4DYIE_Msk                           /*!< PLL4 ready Interrupt Enable */
#define RCC_MC_CIER_LSECSSIE_Pos                  (16U)
#define RCC_MC_CIER_LSECSSIE_Msk                  (0x1U << RCC_MC_CIER_LSECSSIE_Pos)                 /*!< 0x00010000 */
#define RCC_MC_CIER_LSECSSIE                      RCC_MC_CIER_LSECSSIE_Msk                           /*!< LSE clock security system Interrupt Enable */
#define RCC_MC_CIER_WKUPIE_Pos                    (20U)
#define RCC_MC_CIER_WKUPIE_Msk                    (0x1U << RCC_MC_CIER_WKUPIE_Pos)                   /*!< 0x00100000 */
#define RCC_MC_CIER_WKUPIE                        RCC_MC_CIER_WKUPIE_Msk                             /*!< Wake up from CStop Interrupt Enable */

/*****************  Bit definition for RCC_MC_CIFR register  ******************/
#define RCC_MC_CIFR_LSIRDYF_Pos                   (0U)
#define RCC_MC_CIFR_LSIRDYF_Msk                   (0x1U << RCC_MC_CIFR_LSIRDYF_Pos)                  /*!< 0x00000001 */
#define RCC_MC_CIFR_LSIRDYF                       RCC_MC_CIFR_LSIRDYF_Msk                            /*!< LSI ready Interrupt Flag */
#define RCC_MC_CIFR_LSERDYF_Pos                   (1U)
#define RCC_MC_CIFR_LSERDYF_Msk                   (0x1U << RCC_MC_CIFR_LSERDYF_Pos)                  /*!< 0x00000002 */
#define RCC_MC_CIFR_LSERDYF                       RCC_MC_CIFR_LSERDYF_Msk                            /*!< LSE ready Interrupt Flag */
#define RCC_MC_CIFR_HSIRDYF_Pos                   (2U)
#define RCC_MC_CIFR_HSIRDYF_Msk                   (0x1U << RCC_MC_CIFR_HSIRDYF_Pos)                  /*!< 0x00000004 */
#define RCC_MC_CIFR_HSIRDYF                       RCC_MC_CIFR_HSIRDYF_Msk                            /*!< HSI ready Interrupt Flag */
#define RCC_MC_CIFR_HSERDYF_Pos                   (3U)
#define RCC_MC_CIFR_HSERDYF_Msk                   (0x1U << RCC_MC_CIFR_HSERDYF_Pos)                  /*!< 0x00000008 */
#define RCC_MC_CIFR_HSERDYF                       RCC_MC_CIFR_HSERDYF_Msk                            /*!< HSE ready Interrupt Flag */
#define RCC_MC_CIFR_CSIRDYF_Pos                   (4U)
#define RCC_MC_CIFR_CSIRDYF_Msk                   (0x1U << RCC_MC_CIFR_CSIRDYF_Pos)                  /*!< 0x00000010 */
#define RCC_MC_CIFR_CSIRDYF                       RCC_MC_CIFR_CSIRDYF_Msk                            /*!< CSI ready Interrupt Flag */
#define RCC_MC_CIFR_PLL1DYF_Pos                   (8U)
#define RCC_MC_CIFR_PLL1DYF_Msk                   (0x1U << RCC_MC_CIFR_PLL1DYF_Pos)                  /*!< 0x00000100 */
#define RCC_MC_CIFR_PLL1DYF                       RCC_MC_CIFR_PLL1DYF_Msk                            /*!< PLL1 ready Interrupt Flag */
#define RCC_MC_CIFR_PLL2DYF_Pos                   (9U)
#define RCC_MC_CIFR_PLL2DYF_Msk                   (0x1U << RCC_MC_CIFR_PLL2DYF_Pos)                  /*!< 0x00000200 */
#define RCC_MC_CIFR_PLL2DYF                       RCC_MC_CIFR_PLL2DYF_Msk                            /*!< PLL2 ready Interrupt Flag */
#define RCC_MC_CIFR_PLL3DYF_Pos                   (10U)
#define RCC_MC_CIFR_PLL3DYF_Msk                   (0x1U << RCC_MC_CIFR_PLL3DYF_Pos)                  /*!< 0x00000400 */
#define RCC_MC_CIFR_PLL3DYF                       RCC_MC_CIFR_PLL3DYF_Msk                            /*!< PLL3 ready Interrupt Flag */
#define RCC_MC_CIFR_PLL4DYF_Pos                   (11U)
#define RCC_MC_CIFR_PLL4DYF_Msk                   (0x1U << RCC_MC_CIFR_PLL4DYF_Pos)                  /*!< 0x00000800 */
#define RCC_MC_CIFR_PLL4DYF                       RCC_MC_CIFR_PLL4DYF_Msk                            /*!< PLL4 ready Interrupt Flag */
#define RCC_MC_CIFR_LSECSSF_Pos                   (16U)
#define RCC_MC_CIFR_LSECSSF_Msk                   (0x1U << RCC_MC_CIFR_LSECSSF_Pos)                  /*!< 0x00010000 */
#define RCC_MC_CIFR_LSECSSF                       RCC_MC_CIFR_LSECSSF_Msk                            /*!< LSE clock security system Interrupt Flag */
#define RCC_MC_CIFR_WKUPF_Pos                     (20U)
#define RCC_MC_CIFR_WKUPF_Msk                     (0x1U << RCC_MC_CIFR_WKUPF_Pos)                    /*!< 0x00100000 */
#define RCC_MC_CIFR_WKUPF                         RCC_MC_CIFR_WKUPF_Msk                              /*!< Wake up from CStop Interrupt Flag */

/*******************  Bit definition for RCC_VERR register  *******************/
#define RCC_VERR_MINREV_Pos                       (0U)
#define RCC_VERR_MINREV_Msk                       (0xFU << RCC_VERR_MINREV_Pos)                      /*!< 0x0000000F */
#define RCC_VERR_MINREV                           RCC_VERR_MINREV_Msk                                /*!< Minor Revision of the IP */
#define RCC_VERR_MINREV_0                         (0x1U << RCC_VERR_MINREV_Pos)                      /*!< 0x00000001 */
#define RCC_VERR_MINREV_1                         (0x2U << RCC_VERR_MINREV_Pos)                      /*!< 0x00000002 */
#define RCC_VERR_MINREV_2                         (0x4U << RCC_VERR_MINREV_Pos)                      /*!< 0x00000004 */
#define RCC_VERR_MINREV_3                         (0x8U << RCC_VERR_MINREV_Pos)                      /*!< 0x00000008 */
#define RCC_VERR_MAJREV_Pos                       (4U)
#define RCC_VERR_MAJREV_Msk                       (0xFU << RCC_VERR_MAJREV_Pos)                      /*!< 0x000000F0 */
#define RCC_VERR_MAJREV                           RCC_VERR_MAJREV_Msk                                /*!< Major Revision of the IP */
#define RCC_VERR_MAJREV_0                         (0x1U << RCC_VERR_MAJREV_Pos)                     /*!< 0x00000010 */
#define RCC_VERR_MAJREV_1                         (0x2U << RCC_VERR_MAJREV_Pos)                     /*!< 0x00000020 */
#define RCC_VERR_MAJREV_2                         (0x4U << RCC_VERR_MAJREV_Pos)                     /*!< 0x00000040 */
#define RCC_VERR_MAJREV_3                         (0x8U << RCC_VERR_MAJREV_Pos)                     /*!< 0x00000080 */

/*******************  Bit definition for RCC_IDR register  ********************/
#define RCC_IDR_ID_Pos                            (0U)
#define RCC_IDR_ID_Msk                            (0xFFFFFFFFU << RCC_IDR_ID_Pos)                    /*!< 0xFFFFFFFF */
#define RCC_IDR_ID                                RCC_IDR_ID_Msk                                     /*!< Identifier of the RCC */
#define RCC_IDR_ID_0                              (0x1U << RCC_IDR_ID_Pos)                           /*!< 0x00000001 */
#define RCC_IDR_ID_1                              (0x2U << RCC_IDR_ID_Pos)                           /*!< 0x00000002 */
#define RCC_IDR_ID_2                              (0x4U << RCC_IDR_ID_Pos)                           /*!< 0x00000004 */
#define RCC_IDR_ID_3                              (0x8U << RCC_IDR_ID_Pos)                           /*!< 0x00000008 */
#define RCC_IDR_ID_4                              (0x10U << RCC_IDR_ID_Pos)                          /*!< 0x00000010 */
#define RCC_IDR_ID_5                              (0x20U << RCC_IDR_ID_Pos)                          /*!< 0x00000020 */
#define RCC_IDR_ID_6                              (0x40U << RCC_IDR_ID_Pos)                          /*!< 0x00000040 */
#define RCC_IDR_ID_7                              (0x80U << RCC_IDR_ID_Pos)                          /*!< 0x00000080 */
#define RCC_IDR_ID_8                              (0x100U << RCC_IDR_ID_Pos)                         /*!< 0x00000100 */
#define RCC_IDR_ID_9                              (0x200U << RCC_IDR_ID_Pos)                         /*!< 0x00000200 */
#define RCC_IDR_ID_10                             (0x400U << RCC_IDR_ID_Pos)                         /*!< 0x00000400 */
#define RCC_IDR_ID_11                             (0x800U << RCC_IDR_ID_Pos)                         /*!< 0x00000800 */
#define RCC_IDR_ID_12                             (0x1000U << RCC_IDR_ID_Pos)                        /*!< 0x00001000 */
#define RCC_IDR_ID_13                             (0x2000U << RCC_IDR_ID_Pos)                        /*!< 0x00002000 */
#define RCC_IDR_ID_14                             (0x4000U << RCC_IDR_ID_Pos)                        /*!< 0x00004000 */
#define RCC_IDR_ID_15                             (0x8000U << RCC_IDR_ID_Pos)                        /*!< 0x00008000 */
#define RCC_IDR_ID_16                             (0x10000U << RCC_IDR_ID_Pos)                       /*!< 0x00010000 */
#define RCC_IDR_ID_17                             (0x20000U << RCC_IDR_ID_Pos)                       /*!< 0x00020000 */
#define RCC_IDR_ID_18                             (0x40000U << RCC_IDR_ID_Pos)                       /*!< 0x00040000 */
#define RCC_IDR_ID_19                             (0x80000U << RCC_IDR_ID_Pos)                       /*!< 0x00080000 */
#define RCC_IDR_ID_20                             (0x100000U << RCC_IDR_ID_Pos)                      /*!< 0x00100000 */
#define RCC_IDR_ID_21                             (0x200000U << RCC_IDR_ID_Pos)                      /*!< 0x00200000 */
#define RCC_IDR_ID_22                             (0x400000U << RCC_IDR_ID_Pos)                      /*!< 0x00400000 */
#define RCC_IDR_ID_23                             (0x800000U << RCC_IDR_ID_Pos)                      /*!< 0x00800000 */
#define RCC_IDR_ID_24                             (0x1000000U << RCC_IDR_ID_Pos)                     /*!< 0x01000000 */
#define RCC_IDR_ID_25                             (0x2000000U << RCC_IDR_ID_Pos)                     /*!< 0x02000000 */
#define RCC_IDR_ID_26                             (0x4000000U << RCC_IDR_ID_Pos)                     /*!< 0x04000000 */
#define RCC_IDR_ID_27                             (0x8000000U << RCC_IDR_ID_Pos)                     /*!< 0x08000000 */
#define RCC_IDR_ID_28                             (0x10000000U << RCC_IDR_ID_Pos)                    /*!< 0x10000000 */
#define RCC_IDR_ID_29                             (0x20000000U << RCC_IDR_ID_Pos)                    /*!< 0x20000000 */
#define RCC_IDR_ID_30                             (0x40000000U << RCC_IDR_ID_Pos)                    /*!< 0x40000000 */
#define RCC_IDR_ID_31                             (0x80000000U << RCC_IDR_ID_Pos)                    /*!< 0x80000000 */

/*******************  Bit definition for RCC_SIDR register  *******************/
#define RCC_SIDR_SID_Pos                          (0U)
#define RCC_SIDR_SID_Msk                          (0xFFFFFFFFU << RCC_SIDR_SID_Pos)                  /*!< 0xFFFFFFFF */
#define RCC_SIDR_SID                              RCC_SIDR_SID_Msk                                   /*!< Decoding space is 4 kbytes */
#define RCC_SIDR_SID_0                            (0x1U << RCC_SIDR_SID_Pos)                         /*!< 0x00000001 */
#define RCC_SIDR_SID_1                            (0x2U << RCC_SIDR_SID_Pos)                         /*!< 0x00000002 */
#define RCC_SIDR_SID_2                            (0x4U << RCC_SIDR_SID_Pos)                         /*!< 0x00000004 */
#define RCC_SIDR_SID_3                            (0x8U << RCC_SIDR_SID_Pos)                         /*!< 0x00000008 */
#define RCC_SIDR_SID_4                            (0x10U << RCC_SIDR_SID_Pos)                        /*!< 0x00000010 */
#define RCC_SIDR_SID_5                            (0x20U << RCC_SIDR_SID_Pos)                        /*!< 0x00000020 */
#define RCC_SIDR_SID_6                            (0x40U << RCC_SIDR_SID_Pos)                        /*!< 0x00000040 */
#define RCC_SIDR_SID_7                            (0x80U << RCC_SIDR_SID_Pos)                        /*!< 0x00000080 */
#define RCC_SIDR_SID_8                            (0x100U << RCC_SIDR_SID_Pos)                       /*!< 0x00000100 */
#define RCC_SIDR_SID_9                            (0x200U << RCC_SIDR_SID_Pos)                       /*!< 0x00000200 */
#define RCC_SIDR_SID_10                           (0x400U << RCC_SIDR_SID_Pos)                       /*!< 0x00000400 */
#define RCC_SIDR_SID_11                           (0x800U << RCC_SIDR_SID_Pos)                       /*!< 0x00000800 */
#define RCC_SIDR_SID_12                           (0x1000U << RCC_SIDR_SID_Pos)                      /*!< 0x00001000 */
#define RCC_SIDR_SID_13                           (0x2000U << RCC_SIDR_SID_Pos)                      /*!< 0x00002000 */
#define RCC_SIDR_SID_14                           (0x4000U << RCC_SIDR_SID_Pos)                      /*!< 0x00004000 */
#define RCC_SIDR_SID_15                           (0x8000U << RCC_SIDR_SID_Pos)                      /*!< 0x00008000 */
#define RCC_SIDR_SID_16                           (0x10000U << RCC_SIDR_SID_Pos)                     /*!< 0x00010000 */
#define RCC_SIDR_SID_17                           (0x20000U << RCC_SIDR_SID_Pos)                     /*!< 0x00020000 */
#define RCC_SIDR_SID_18                           (0x40000U << RCC_SIDR_SID_Pos)                     /*!< 0x00040000 */
#define RCC_SIDR_SID_19                           (0x80000U << RCC_SIDR_SID_Pos)                     /*!< 0x00080000 */
#define RCC_SIDR_SID_20                           (0x100000U << RCC_SIDR_SID_Pos)                    /*!< 0x00100000 */
#define RCC_SIDR_SID_21                           (0x200000U << RCC_SIDR_SID_Pos)                    /*!< 0x00200000 */
#define RCC_SIDR_SID_22                           (0x400000U << RCC_SIDR_SID_Pos)                    /*!< 0x00400000 */
#define RCC_SIDR_SID_23                           (0x800000U << RCC_SIDR_SID_Pos)                    /*!< 0x00800000 */
#define RCC_SIDR_SID_24                           (0x1000000U << RCC_SIDR_SID_Pos)                   /*!< 0x01000000 */
#define RCC_SIDR_SID_25                           (0x2000000U << RCC_SIDR_SID_Pos)                   /*!< 0x02000000 */
#define RCC_SIDR_SID_26                           (0x4000000U << RCC_SIDR_SID_Pos)                   /*!< 0x04000000 */
#define RCC_SIDR_SID_27                           (0x8000000U << RCC_SIDR_SID_Pos)                   /*!< 0x08000000 */
#define RCC_SIDR_SID_28                           (0x10000000U << RCC_SIDR_SID_Pos)                  /*!< 0x10000000 */
#define RCC_SIDR_SID_29                           (0x20000000U << RCC_SIDR_SID_Pos)                  /*!< 0x20000000 */
#define RCC_SIDR_SID_30                           (0x40000000U << RCC_SIDR_SID_Pos)                  /*!< 0x40000000 */
#define RCC_SIDR_SID_31                           (0x80000000U << RCC_SIDR_SID_Pos)                  /*!< 0x80000000 */
