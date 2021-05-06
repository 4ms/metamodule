
/******************************************************************************/
/*                                                                            */
/*                                    RNG                                     */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for RNG_CR register  *******************/
#define RNG_CR_RNGEN_Pos    (2U)
#define RNG_CR_RNGEN_Msk    (0x1U << RNG_CR_RNGEN_Pos)                         /*!< 0x00000004 */
#define RNG_CR_RNGEN        RNG_CR_RNGEN_Msk
#define RNG_CR_IE_Pos       (3U)
#define RNG_CR_IE_Msk       (0x1U << RNG_CR_IE_Pos)                            /*!< 0x00000008 */
#define RNG_CR_IE           RNG_CR_IE_Msk
#define RNG_CR_CED_Pos      (5U)
#define RNG_CR_CED_Msk      (0x1U << RNG_CR_CED_Pos)                           /*!< 0x00000020 */
#define RNG_CR_CED          RNG_CR_CED_Msk

/********************  Bits definition for RNG_SR register  *******************/
#define RNG_SR_DRDY_Pos     (0U)
#define RNG_SR_DRDY_Msk     (0x1U << RNG_SR_DRDY_Pos)                          /*!< 0x00000001 */
#define RNG_SR_DRDY         RNG_SR_DRDY_Msk
#define RNG_SR_CECS_Pos     (1U)
#define RNG_SR_CECS_Msk     (0x1U << RNG_SR_CECS_Pos)                          /*!< 0x00000002 */
#define RNG_SR_CECS         RNG_SR_CECS_Msk
#define RNG_SR_SECS_Pos     (2U)
#define RNG_SR_SECS_Msk     (0x1U << RNG_SR_SECS_Pos)                          /*!< 0x00000004 */
#define RNG_SR_SECS         RNG_SR_SECS_Msk
#define RNG_SR_CEIS_Pos     (5U)
#define RNG_SR_CEIS_Msk     (0x1U << RNG_SR_CEIS_Pos)                          /*!< 0x00000020 */
#define RNG_SR_CEIS         RNG_SR_CEIS_Msk
#define RNG_SR_SEIS_Pos     (6U)
#define RNG_SR_SEIS_Msk     (0x1U << RNG_SR_SEIS_Pos)                          /*!< 0x00000040 */
#define RNG_SR_SEIS         RNG_SR_SEIS_Msk

/**********************  Bit definition for RNG_VERR register  *****************/
#define RNG_VERR_MINREV_Pos      (0U)
#define RNG_VERR_MINREV_Msk      (0xFU << RNG_VERR_MINREV_Pos)               /*!< 0x0000000F */
#define RNG_VERR_MINREV          RNG_VERR_MINREV_Msk                         /*!< Minor Revision number */
#define RNG_VERR_MAJREV_Pos      (4U)
#define RNG_VERR_MAJREV_Msk      (0xFU << RNG_VERR_MAJREV_Pos)               /*!< 0x000000F0 */
#define RNG_VERR_MAJREV          RNG_VERR_MAJREV_Msk                         /*!< Major Revision number */

/**********************  Bit definition for RNG_IPIDR register  ****************/
#define RNG_IPIDR_ID_Pos       (0U)
#define RNG_IPIDR_ID_Msk       (0xFFFFFFFFU << RNG_IPIDR_ID_Pos)         /*!< 0xFFFFFFFF */
#define RNG_IPIDR_ID           RNG_IPIDR_ID_Msk                          /*!< IP Identification */

/**********************  Bit definition for RNG_SIDR register  *****************/
#define RNG_SIDR_SID_Pos         (0U)
#define RNG_SIDR_SID_Msk         (0xFFFFFFFFU << RNG_SIDR_SID_Pos)           /*!< 0xFFFFFFFF */
#define RNG_SIDR_SID             RNG_SIDR_SID_Msk                            /*!< IP size identification */

/******************************************************************************/
/*                                                                            */
/*                           Real-Time Clock (RTC)                            */
/*                                                                            */
/******************************************************************************/
/*
* @brief Specific device feature definitions
*/

/********************  Bits definition for RTC_TR register  *******************/
#define RTC_TR_PM_Pos                     (22U)
#define RTC_TR_PM_Msk                     (0x1U << RTC_TR_PM_Pos)              /*!< 0x00400000 */
#define RTC_TR_PM                         RTC_TR_PM_Msk
#define RTC_TR_HT_Pos                     (20U)
#define RTC_TR_HT_Msk                     (0x3U << RTC_TR_HT_Pos)              /*!< 0x00300000 */
#define RTC_TR_HT                         RTC_TR_HT_Msk
#define RTC_TR_HT_0                       (0x1U << RTC_TR_HT_Pos)              /*!< 0x00100000 */
#define RTC_TR_HT_1                       (0x2U << RTC_TR_HT_Pos)              /*!< 0x00200000 */
#define RTC_TR_HU_Pos                     (16U)
#define RTC_TR_HU_Msk                     (0xFU << RTC_TR_HU_Pos)              /*!< 0x000F0000 */
#define RTC_TR_HU                         RTC_TR_HU_Msk
#define RTC_TR_HU_0                       (0x1U << RTC_TR_HU_Pos)              /*!< 0x00010000 */
#define RTC_TR_HU_1                       (0x2U << RTC_TR_HU_Pos)              /*!< 0x00020000 */
#define RTC_TR_HU_2                       (0x4U << RTC_TR_HU_Pos)              /*!< 0x00040000 */
#define RTC_TR_HU_3                       (0x8U << RTC_TR_HU_Pos)              /*!< 0x00080000 */
#define RTC_TR_MNT_Pos                    (12U)
#define RTC_TR_MNT_Msk                    (0x7U << RTC_TR_MNT_Pos)             /*!< 0x00007000 */
#define RTC_TR_MNT                        RTC_TR_MNT_Msk
#define RTC_TR_MNT_0                      (0x1U << RTC_TR_MNT_Pos)             /*!< 0x00001000 */
#define RTC_TR_MNT_1                      (0x2U << RTC_TR_MNT_Pos)             /*!< 0x00002000 */
#define RTC_TR_MNT_2                      (0x4U << RTC_TR_MNT_Pos)             /*!< 0x00004000 */
#define RTC_TR_MNU_Pos                    (8U)
#define RTC_TR_MNU_Msk                    (0xFU << RTC_TR_MNU_Pos)             /*!< 0x00000F00 */
#define RTC_TR_MNU                        RTC_TR_MNU_Msk
#define RTC_TR_MNU_0                      (0x1U << RTC_TR_MNU_Pos)             /*!< 0x00000100 */
#define RTC_TR_MNU_1                      (0x2U << RTC_TR_MNU_Pos)             /*!< 0x00000200 */
#define RTC_TR_MNU_2                      (0x4U << RTC_TR_MNU_Pos)             /*!< 0x00000400 */
#define RTC_TR_MNU_3                      (0x8U << RTC_TR_MNU_Pos)             /*!< 0x00000800 */
#define RTC_TR_ST_Pos                     (4U)
#define RTC_TR_ST_Msk                     (0x7U << RTC_TR_ST_Pos)              /*!< 0x00000070 */
#define RTC_TR_ST                         RTC_TR_ST_Msk
#define RTC_TR_ST_0                       (0x1U << RTC_TR_ST_Pos)              /*!< 0x00000010 */
#define RTC_TR_ST_1                       (0x2U << RTC_TR_ST_Pos)              /*!< 0x00000020 */
#define RTC_TR_ST_2                       (0x4U << RTC_TR_ST_Pos)              /*!< 0x00000040 */
#define RTC_TR_SU_Pos                     (0U)
#define RTC_TR_SU_Msk                     (0xFU << RTC_TR_SU_Pos)              /*!< 0x0000000F */
#define RTC_TR_SU                         RTC_TR_SU_Msk
#define RTC_TR_SU_0                       (0x1U << RTC_TR_SU_Pos)              /*!< 0x00000001 */
#define RTC_TR_SU_1                       (0x2U << RTC_TR_SU_Pos)              /*!< 0x00000002 */
#define RTC_TR_SU_2                       (0x4U << RTC_TR_SU_Pos)              /*!< 0x00000004 */
#define RTC_TR_SU_3                       (0x8U << RTC_TR_SU_Pos)              /*!< 0x00000008 */

/********************  Bits definition for RTC_DR register  *******************/
#define RTC_DR_YT_Pos                     (20U)
#define RTC_DR_YT_Msk                     (0xFU << RTC_DR_YT_Pos)              /*!< 0x00F00000 */
#define RTC_DR_YT                         RTC_DR_YT_Msk
#define RTC_DR_YT_0                       (0x1U << RTC_DR_YT_Pos)              /*!< 0x00100000 */
#define RTC_DR_YT_1                       (0x2U << RTC_DR_YT_Pos)              /*!< 0x00200000 */
#define RTC_DR_YT_2                       (0x4U << RTC_DR_YT_Pos)              /*!< 0x00400000 */
#define RTC_DR_YT_3                       (0x8U << RTC_DR_YT_Pos)              /*!< 0x00800000 */
#define RTC_DR_YU_Pos                     (16U)
#define RTC_DR_YU_Msk                     (0xFU << RTC_DR_YU_Pos)              /*!< 0x000F0000 */
#define RTC_DR_YU                         RTC_DR_YU_Msk
#define RTC_DR_YU_0                       (0x1U << RTC_DR_YU_Pos)              /*!< 0x00010000 */
#define RTC_DR_YU_1                       (0x2U << RTC_DR_YU_Pos)              /*!< 0x00020000 */
#define RTC_DR_YU_2                       (0x4U << RTC_DR_YU_Pos)              /*!< 0x00040000 */
#define RTC_DR_YU_3                       (0x8U << RTC_DR_YU_Pos)              /*!< 0x00080000 */
#define RTC_DR_WDU_Pos                    (13U)
#define RTC_DR_WDU_Msk                    (0x7U << RTC_DR_WDU_Pos)             /*!< 0x0000E000 */
#define RTC_DR_WDU                        RTC_DR_WDU_Msk
#define RTC_DR_WDU_0                      (0x1U << RTC_DR_WDU_Pos)             /*!< 0x00002000 */
#define RTC_DR_WDU_1                      (0x2U << RTC_DR_WDU_Pos)             /*!< 0x00004000 */
#define RTC_DR_WDU_2                      (0x4U << RTC_DR_WDU_Pos)             /*!< 0x00008000 */
#define RTC_DR_MT_Pos                     (12U)
#define RTC_DR_MT_Msk                     (0x1U << RTC_DR_MT_Pos)              /*!< 0x00001000 */
#define RTC_DR_MT                         RTC_DR_MT_Msk
#define RTC_DR_MU_Pos                     (8U)
#define RTC_DR_MU_Msk                     (0xFU << RTC_DR_MU_Pos)              /*!< 0x00000F00 */
#define RTC_DR_MU                         RTC_DR_MU_Msk
#define RTC_DR_MU_0                       (0x1U << RTC_DR_MU_Pos)              /*!< 0x00000100 */
#define RTC_DR_MU_1                       (0x2U << RTC_DR_MU_Pos)              /*!< 0x00000200 */
#define RTC_DR_MU_2                       (0x4U << RTC_DR_MU_Pos)              /*!< 0x00000400 */
#define RTC_DR_MU_3                       (0x8U << RTC_DR_MU_Pos)              /*!< 0x00000800 */
#define RTC_DR_DT_Pos                     (4U)
#define RTC_DR_DT_Msk                     (0x3U << RTC_DR_DT_Pos)              /*!< 0x00000030 */
#define RTC_DR_DT                         RTC_DR_DT_Msk
#define RTC_DR_DT_0                       (0x1U << RTC_DR_DT_Pos)              /*!< 0x00000010 */
#define RTC_DR_DT_1                       (0x2U << RTC_DR_DT_Pos)              /*!< 0x00000020 */
#define RTC_DR_DU_Pos                     (0U)
#define RTC_DR_DU_Msk                     (0xFU << RTC_DR_DU_Pos)              /*!< 0x0000000F */
#define RTC_DR_DU                         RTC_DR_DU_Msk
#define RTC_DR_DU_0                       (0x1U << RTC_DR_DU_Pos)              /*!< 0x00000001 */
#define RTC_DR_DU_1                       (0x2U << RTC_DR_DU_Pos)              /*!< 0x00000002 */
#define RTC_DR_DU_2                       (0x4U << RTC_DR_DU_Pos)              /*!< 0x00000004 */
#define RTC_DR_DU_3                       (0x8U << RTC_DR_DU_Pos)              /*!< 0x00000008 */

/********************  Bits definition for RTC_SSR register  ******************/
#define RTC_SSR_SS_Pos                    (0U)
#define RTC_SSR_SS_Msk                    (0xFFFFU << RTC_SSR_SS_Pos)          /*!< 0x0000FFFF */
#define RTC_SSR_SS                        RTC_SSR_SS_Msk

/****************  Bits definition for RTC_ICSR (RTC_ISR) register *************/
#define RTC_ICSR_RECALPF_Pos         (16U)
#define RTC_ICSR_RECALPF_Msk         (0x1UL << RTC_ICSR_RECALPF_Pos)           /*!< 0x00010000 */
#define RTC_ICSR_RECALPF             RTC_ICSR_RECALPF_Msk
#define RTC_ICSR_INIT_Pos            (7U)
#define RTC_ICSR_INIT_Msk            (0x1UL << RTC_ICSR_INIT_Pos)              /*!< 0x00000080 */
#define RTC_ICSR_INIT                RTC_ICSR_INIT_Msk
#define RTC_ICSR_INITF_Pos           (6U)
#define RTC_ICSR_INITF_Msk           (0x1UL << RTC_ICSR_INITF_Pos)             /*!< 0x00000040 */
#define RTC_ICSR_INITF               RTC_ICSR_INITF_Msk
#define RTC_ICSR_RSF_Pos             (5U)
#define RTC_ICSR_RSF_Msk             (0x1UL << RTC_ICSR_RSF_Pos)               /*!< 0x00000020 */
#define RTC_ICSR_RSF                 RTC_ICSR_RSF_Msk
#define RTC_ICSR_INITS_Pos           (4U)
#define RTC_ICSR_INITS_Msk           (0x1UL << RTC_ICSR_INITS_Pos)             /*!< 0x00000010 */
#define RTC_ICSR_INITS               RTC_ICSR_INITS_Msk
#define RTC_ICSR_SHPF_Pos            (3U)
#define RTC_ICSR_SHPF_Msk            (0x1UL << RTC_ICSR_SHPF_Pos)              /*!< 0x00000008 */
#define RTC_ICSR_SHPF                RTC_ICSR_SHPF_Msk
#define RTC_ICSR_WUTWF_Pos           (2U)
#define RTC_ICSR_WUTWF_Msk           (0x1UL << RTC_ICSR_WUTWF_Pos)             /*!< 0x00000004 */
#define RTC_ICSR_WUTWF               RTC_ICSR_WUTWF_Msk
#define RTC_ICSR_ALRBWF_Pos          (1U)
#define RTC_ICSR_ALRBWF_Msk          (0x1UL << RTC_ICSR_ALRBWF_Pos)            /*!< 0x00000002 */
#define RTC_ICSR_ALRBWF              RTC_ICSR_ALRBWF_Msk
#define RTC_ICSR_ALRAWF_Pos          (0U)
#define RTC_ICSR_ALRAWF_Msk          (0x1UL << RTC_ICSR_ALRAWF_Pos)            /*!< 0x00000001 */
#define RTC_ICSR_ALRAWF              RTC_ICSR_ALRAWF_Msk

/********************  Bits definition for RTC_PRER register  *****************/
#define RTC_PRER_PREDIV_A_Pos             (16U)
#define RTC_PRER_PREDIV_A_Msk             (0x7FU << RTC_PRER_PREDIV_A_Pos)     /*!< 0x007F0000 */
#define RTC_PRER_PREDIV_A                 RTC_PRER_PREDIV_A_Msk
#define RTC_PRER_PREDIV_S_Pos             (0U)
#define RTC_PRER_PREDIV_S_Msk             (0x7FFFU << RTC_PRER_PREDIV_S_Pos)   /*!< 0x00007FFF */
#define RTC_PRER_PREDIV_S                 RTC_PRER_PREDIV_S_Msk

/********************  Bits definition for RTC_WUTR register  *****************/
#define RTC_WUTR_WUT_Pos                  (0U)
#define RTC_WUTR_WUT_Msk                  (0xFFFFU << RTC_WUTR_WUT_Pos)        /*!< 0x0000FFFF */
#define RTC_WUTR_WUT                      RTC_WUTR_WUT_Msk

/********************  Bits definition for RTC_CR register  *******************/
#define RTC_CR_OUT2EN_Pos                 (31U)
#define RTC_CR_OUT2EN_Msk                 (0x1U << RTC_CR_OUT2EN_Pos)          /*!< 0x80000000 */
#define RTC_CR_OUT2EN                     RTC_CR_OUT2EN_Msk
#define RTC_CR_TAMPALRM_TYPE_Pos          (30U)
#define RTC_CR_TAMPALRM_TYPE_Msk          (0x1U << RTC_CR_TAMPALRM_TYPE_Pos)   /*!< 0x40000000 */
#define RTC_CR_TAMPALRM_TYPE              RTC_CR_TAMPALRM_TYPE_Msk
#define RTC_CR_TAMPALRM_PU_Pos            (29U)
#define RTC_CR_TAMPALRM_PU_Msk            (0x1U << RTC_CR_TAMPALRM_PU_Pos)     /*!< 0x20000000 */
#define RTC_CR_TAMPALRM_PU                RTC_CR_TAMPALRM_PU_Msk
#define RTC_CR_TAMPOE_Pos                 (26U)
#define RTC_CR_TAMPOE_Msk                 (0x1U << RTC_CR_TAMPOE_Pos)          /*!< 0x04000000 */
#define RTC_CR_TAMPOE                     RTC_CR_TAMPOE_Msk
#define RTC_CR_TAMPTS_Pos                 (25U)
#define RTC_CR_TAMPTS_Msk                 (0x1U << RTC_CR_TAMPTS_Pos)          /*!< 0x02000000 */
#define RTC_CR_TAMPTS                     RTC_CR_TAMPTS_Msk
#define RTC_CR_ITSE_Pos                   (24U)
#define RTC_CR_ITSE_Msk                   (0x1U << RTC_CR_ITSE_Pos)            /*!< 0x01000000 */
#define RTC_CR_ITSE                       RTC_CR_ITSE_Msk
#define RTC_CR_COE_Pos                    (23U)
#define RTC_CR_COE_Msk                    (0x1U << RTC_CR_COE_Pos)             /*!< 0x00800000 */
#define RTC_CR_COE                        RTC_CR_COE_Msk
#define RTC_CR_OSEL_Pos                   (21U)
#define RTC_CR_OSEL_Msk                   (0x3U << RTC_CR_OSEL_Pos)            /*!< 0x00600000 */
#define RTC_CR_OSEL                       RTC_CR_OSEL_Msk
#define RTC_CR_OSEL_0                     (0x1U << RTC_CR_OSEL_Pos)            /*!< 0x00200000 */
#define RTC_CR_OSEL_1                     (0x2U << RTC_CR_OSEL_Pos)            /*!< 0x00400000 */
#define RTC_CR_POL_Pos                    (20U)
#define RTC_CR_POL_Msk                    (0x1U << RTC_CR_POL_Pos)             /*!< 0x00100000 */
#define RTC_CR_POL                        RTC_CR_POL_Msk
#define RTC_CR_COSEL_Pos                  (19U)
#define RTC_CR_COSEL_Msk                  (0x1U << RTC_CR_COSEL_Pos)           /*!< 0x00080000 */
#define RTC_CR_COSEL                      RTC_CR_COSEL_Msk
#define RTC_CR_BKP_Pos                    (18U)
#define RTC_CR_BKP_Msk                    (0x1U << RTC_CR_BKP_Pos)             /*!< 0x00040000 */
#define RTC_CR_BKP                        RTC_CR_BKP_Msk
#define RTC_CR_SUB1H_Pos                  (17U)
#define RTC_CR_SUB1H_Msk                  (0x1U << RTC_CR_SUB1H_Pos)           /*!< 0x00020000 */
#define RTC_CR_SUB1H                      RTC_CR_SUB1H_Msk
#define RTC_CR_ADD1H_Pos                  (16U)
#define RTC_CR_ADD1H_Msk                  (0x1U << RTC_CR_ADD1H_Pos)           /*!< 0x00010000 */
#define RTC_CR_ADD1H                      RTC_CR_ADD1H_Msk
#define RTC_CR_TSIE_Pos                   (15U)
#define RTC_CR_TSIE_Msk                   (0x1U << RTC_CR_TSIE_Pos)            /*!< 0x00008000 */
#define RTC_CR_TSIE                       RTC_CR_TSIE_Msk
#define RTC_CR_WUTIE_Pos                  (14U)
#define RTC_CR_WUTIE_Msk                  (0x1U << RTC_CR_WUTIE_Pos)           /*!< 0x00004000 */
#define RTC_CR_WUTIE                      RTC_CR_WUTIE_Msk
#define RTC_CR_ALRBIE_Pos                 (13U)
#define RTC_CR_ALRBIE_Msk                 (0x1U << RTC_CR_ALRBIE_Pos)          /*!< 0x00002000 */
#define RTC_CR_ALRBIE                     RTC_CR_ALRBIE_Msk
#define RTC_CR_ALRAIE_Pos                 (12U)
#define RTC_CR_ALRAIE_Msk                 (0x1U << RTC_CR_ALRAIE_Pos)          /*!< 0x00001000 */
#define RTC_CR_ALRAIE                     RTC_CR_ALRAIE_Msk
#define RTC_CR_TSE_Pos                    (11U)
#define RTC_CR_TSE_Msk                    (0x1U << RTC_CR_TSE_Pos)             /*!< 0x00000800 */
#define RTC_CR_TSE                        RTC_CR_TSE_Msk
#define RTC_CR_WUTE_Pos                   (10U)
#define RTC_CR_WUTE_Msk                   (0x1U << RTC_CR_WUTE_Pos)            /*!< 0x00000400 */
#define RTC_CR_WUTE                       RTC_CR_WUTE_Msk
#define RTC_CR_ALRBE_Pos                  (9U)
#define RTC_CR_ALRBE_Msk                  (0x1U << RTC_CR_ALRBE_Pos)           /*!< 0x00000200 */
#define RTC_CR_ALRBE                      RTC_CR_ALRBE_Msk
#define RTC_CR_ALRAE_Pos                  (8U)
#define RTC_CR_ALRAE_Msk                  (0x1U << RTC_CR_ALRAE_Pos)           /*!< 0x00000100 */
#define RTC_CR_ALRAE                      RTC_CR_ALRAE_Msk
#define RTC_CR_FMT_Pos                    (6U)
#define RTC_CR_FMT_Msk                    (0x1U << RTC_CR_FMT_Pos)             /*!< 0x00000040 */
#define RTC_CR_FMT                        RTC_CR_FMT_Msk
#define RTC_CR_BYPSHAD_Pos                (5U)
#define RTC_CR_BYPSHAD_Msk                (0x1U << RTC_CR_BYPSHAD_Pos)         /*!< 0x00000020 */
#define RTC_CR_BYPSHAD                    RTC_CR_BYPSHAD_Msk
#define RTC_CR_REFCKON_Pos                (4U)
#define RTC_CR_REFCKON_Msk                (0x1U << RTC_CR_REFCKON_Pos)         /*!< 0x00000010 */
#define RTC_CR_REFCKON                    RTC_CR_REFCKON_Msk
#define RTC_CR_TSEDGE_Pos                 (3U)
#define RTC_CR_TSEDGE_Msk                 (0x1U << RTC_CR_TSEDGE_Pos)          /*!< 0x00000008 */
#define RTC_CR_TSEDGE                     RTC_CR_TSEDGE_Msk
#define RTC_CR_WUCKSEL_Pos                (0U)
#define RTC_CR_WUCKSEL_Msk                (0x7U << RTC_CR_WUCKSEL_Pos)         /*!< 0x00000007 */
#define RTC_CR_WUCKSEL                    RTC_CR_WUCKSEL_Msk
#define RTC_CR_WUCKSEL_0                  (0x1U << RTC_CR_WUCKSEL_Pos)         /*!< 0x00000001 */
#define RTC_CR_WUCKSEL_1                  (0x2U << RTC_CR_WUCKSEL_Pos)         /*!< 0x00000002 */
#define RTC_CR_WUCKSEL_2                  (0x4U << RTC_CR_WUCKSEL_Pos)         /*!< 0x00000004 */

/********************  Bits definition for RTC_SMCR register  *******************/
#define RTC_SMCR_DECPROT_Pos              (15U)
#define RTC_SMCR_DECPROT_Msk              (0x1U << RTC_SMCR_DECPROT_Pos)       /*!< 0x00008000 */
#define RTC_SMCR_DECPROT                  RTC_SMCR_DECPROT_Msk
#define RTC_SMCR_INITDPROT_Pos            (14U)
#define RTC_SMCR_INITDPROT_Msk            (0x1U << RTC_SMCR_INITDPROT_Pos)     /*!< 0x00004000 */
#define RTC_SMCR_INITDPROT                RTC_SMCR_INITDPROT_Msk
#define RTC_SMCR_CALDPROT_Pos             (13U)
#define RTC_SMCR_CALDPROT_Msk             (0x1U << RTC_SMCR_CALDPROT_Pos)      /*!< 0x00002000 */
#define RTC_SMCR_CALDPROT                 RTC_SMCR_CALDPROT_Msk
#define RTC_SMCR_TSDPROT_Pos              (3U)
#define RTC_SMCR_TSDPROT_Msk              (0x1U << RTC_SMCR_TSDPROT_Pos)       /*!< 0x00000008 */
#define RTC_SMCR_TSDPROT                  RTC_SMCR_TSDPROT_Msk
#define RTC_SMCR_WUTDPROT_Pos             (2U)
#define RTC_SMCR_WUTDPROT_Msk             (0x1U << RTC_SMCR_WUTDPROT_Pos)      /*!< 0x00000004 */
#define RTC_SMCR_WUTDPROT                 RTC_SMCR_WUTDPROT_Msk
#define RTC_SMCR_ALRBDPROT_Pos            (1U)
#define RTC_SMCR_ALRBDPROT_Msk            (0x1U << RTC_SMCR_ALRBDPROT_Pos)     /*!< 0x00000002 */
#define RTC_SMCR_ALRBDPROT                RTC_SMCR_ALRBDPROT_Msk
#define RTC_SMCR_ALRADPROT_Pos            (0U)
#define RTC_SMCR_ALRADPROT_Msk            (0x1U << RTC_SMCR_ALRADPROT_Pos)     /*!< 0x00000001 */
#define RTC_SMCR_ALRADPROT                RTC_SMCR_ALRADPROT_Msk

/********************  Bits definition for RTC_WPR register  ******************/
#define RTC_WPR_KEY_Pos                   (0U)
#define RTC_WPR_KEY_Msk                   (0xFFU << RTC_WPR_KEY_Pos)           /*!< 0x000000FF */
#define RTC_WPR_KEY                       RTC_WPR_KEY_Msk

/********************  Bits definition for RTC_CALR register  *****************/
#define RTC_CALR_CALP_Pos                 (15U)
#define RTC_CALR_CALP_Msk                 (0x1U << RTC_CALR_CALP_Pos)          /*!< 0x00008000 */
#define RTC_CALR_CALP                     RTC_CALR_CALP_Msk
#define RTC_CALR_CALW8_Pos                (14U)
#define RTC_CALR_CALW8_Msk                (0x1U << RTC_CALR_CALW8_Pos)         /*!< 0x00004000 */
#define RTC_CALR_CALW8                    RTC_CALR_CALW8_Msk
#define RTC_CALR_CALW16_Pos               (13U)
#define RTC_CALR_CALW16_Msk               (0x1U << RTC_CALR_CALW16_Pos)        /*!< 0x00002000 */
#define RTC_CALR_CALW16                   RTC_CALR_CALW16_Msk
#define RTC_CALR_CALM_Pos                 (0U)
#define RTC_CALR_CALM_Msk                 (0x1FFU << RTC_CALR_CALM_Pos)        /*!< 0x000001FF */
#define RTC_CALR_CALM                     RTC_CALR_CALM_Msk
#define RTC_CALR_CALM_0                   (0x001U << RTC_CALR_CALM_Pos)        /*!< 0x00000001 */
#define RTC_CALR_CALM_1                   (0x002U << RTC_CALR_CALM_Pos)        /*!< 0x00000002 */
#define RTC_CALR_CALM_2                   (0x004U << RTC_CALR_CALM_Pos)        /*!< 0x00000004 */
#define RTC_CALR_CALM_3                   (0x008U << RTC_CALR_CALM_Pos)        /*!< 0x00000008 */
#define RTC_CALR_CALM_4                   (0x010U << RTC_CALR_CALM_Pos)        /*!< 0x00000010 */
#define RTC_CALR_CALM_5                   (0x020U << RTC_CALR_CALM_Pos)        /*!< 0x00000020 */
#define RTC_CALR_CALM_6                   (0x040U << RTC_CALR_CALM_Pos)        /*!< 0x00000040 */
#define RTC_CALR_CALM_7                   (0x080U << RTC_CALR_CALM_Pos)        /*!< 0x00000080 */
#define RTC_CALR_CALM_8                   (0x100U << RTC_CALR_CALM_Pos)        /*!< 0x00000100 */

/********************  Bits definition for RTC_SHIFTR register  ***************/
#define RTC_SHIFTR_SUBFS_Pos              (0U)
#define RTC_SHIFTR_SUBFS_Msk              (0x7FFFU << RTC_SHIFTR_SUBFS_Pos)    /*!< 0x00007FFF */
#define RTC_SHIFTR_SUBFS                  RTC_SHIFTR_SUBFS_Msk
#define RTC_SHIFTR_ADD1S_Pos              (31U)
#define RTC_SHIFTR_ADD1S_Msk              (0x1U << RTC_SHIFTR_ADD1S_Pos)       /*!< 0x80000000 */
#define RTC_SHIFTR_ADD1S                  RTC_SHIFTR_ADD1S_Msk

/********************  Bits definition for RTC_TSTR register  *****************/
#define RTC_TSTR_PM_Pos                   (22U)
#define RTC_TSTR_PM_Msk                   (0x1U << RTC_TSTR_PM_Pos)            /*!< 0x00400000 */
#define RTC_TSTR_PM                       RTC_TSTR_PM_Msk
#define RTC_TSTR_HT_Pos                   (20U)
#define RTC_TSTR_HT_Msk                   (0x3U << RTC_TSTR_HT_Pos)            /*!< 0x00300000 */
#define RTC_TSTR_HT                       RTC_TSTR_HT_Msk
#define RTC_TSTR_HT_0                     (0x1U << RTC_TSTR_HT_Pos)            /*!< 0x00100000 */
#define RTC_TSTR_HT_1                     (0x2U << RTC_TSTR_HT_Pos)            /*!< 0x00200000 */
#define RTC_TSTR_HU_Pos                   (16U)
#define RTC_TSTR_HU_Msk                   (0xFU << RTC_TSTR_HU_Pos)            /*!< 0x000F0000 */
#define RTC_TSTR_HU                       RTC_TSTR_HU_Msk
#define RTC_TSTR_HU_0                     (0x1U << RTC_TSTR_HU_Pos)            /*!< 0x00010000 */
#define RTC_TSTR_HU_1                     (0x2U << RTC_TSTR_HU_Pos)            /*!< 0x00020000 */
#define RTC_TSTR_HU_2                     (0x4U << RTC_TSTR_HU_Pos)            /*!< 0x00040000 */
#define RTC_TSTR_HU_3                     (0x8U << RTC_TSTR_HU_Pos)            /*!< 0x00080000 */
#define RTC_TSTR_MNT_Pos                  (12U)
#define RTC_TSTR_MNT_Msk                  (0x7U << RTC_TSTR_MNT_Pos)           /*!< 0x00007000 */
#define RTC_TSTR_MNT                      RTC_TSTR_MNT_Msk
#define RTC_TSTR_MNT_0                    (0x1U << RTC_TSTR_MNT_Pos)           /*!< 0x00001000 */
#define RTC_TSTR_MNT_1                    (0x2U << RTC_TSTR_MNT_Pos)           /*!< 0x00002000 */
#define RTC_TSTR_MNT_2                    (0x4U << RTC_TSTR_MNT_Pos)           /*!< 0x00004000 */
#define RTC_TSTR_MNU_Pos                  (8U)
#define RTC_TSTR_MNU_Msk                  (0xFU << RTC_TSTR_MNU_Pos)           /*!< 0x00000F00 */
#define RTC_TSTR_MNU                      RTC_TSTR_MNU_Msk
#define RTC_TSTR_MNU_0                    (0x1U << RTC_TSTR_MNU_Pos)           /*!< 0x00000100 */
#define RTC_TSTR_MNU_1                    (0x2U << RTC_TSTR_MNU_Pos)           /*!< 0x00000200 */
#define RTC_TSTR_MNU_2                    (0x4U << RTC_TSTR_MNU_Pos)           /*!< 0x00000400 */
#define RTC_TSTR_MNU_3                    (0x8U << RTC_TSTR_MNU_Pos)           /*!< 0x00000800 */
#define RTC_TSTR_ST_Pos                   (4U)
#define RTC_TSTR_ST_Msk                   (0x7U << RTC_TSTR_ST_Pos)            /*!< 0x00000070 */
#define RTC_TSTR_ST                       RTC_TSTR_ST_Msk
#define RTC_TSTR_ST_0                     (0x1U << RTC_TSTR_ST_Pos)            /*!< 0x00000010 */
#define RTC_TSTR_ST_1                     (0x2U << RTC_TSTR_ST_Pos)            /*!< 0x00000020 */
#define RTC_TSTR_ST_2                     (0x4U << RTC_TSTR_ST_Pos)            /*!< 0x00000040 */
#define RTC_TSTR_SU_Pos                   (0U)
#define RTC_TSTR_SU_Msk                   (0xFU << RTC_TSTR_SU_Pos)            /*!< 0x0000000F */
#define RTC_TSTR_SU                       RTC_TSTR_SU_Msk
#define RTC_TSTR_SU_0                     (0x1U << RTC_TSTR_SU_Pos)            /*!< 0x00000001 */
#define RTC_TSTR_SU_1                     (0x2U << RTC_TSTR_SU_Pos)            /*!< 0x00000002 */
#define RTC_TSTR_SU_2                     (0x4U << RTC_TSTR_SU_Pos)            /*!< 0x00000004 */
#define RTC_TSTR_SU_3                     (0x8U << RTC_TSTR_SU_Pos)            /*!< 0x00000008 */

/********************  Bits definition for RTC_TSDR register  *****************/
#define RTC_TSDR_WDU_Pos                  (13U)
#define RTC_TSDR_WDU_Msk                  (0x7U << RTC_TSDR_WDU_Pos)           /*!< 0x0000E000 */
#define RTC_TSDR_WDU                      RTC_TSDR_WDU_Msk
#define RTC_TSDR_WDU_0                    (0x1U << RTC_TSDR_WDU_Pos)           /*!< 0x00002000 */
#define RTC_TSDR_WDU_1                    (0x2U << RTC_TSDR_WDU_Pos)           /*!< 0x00004000 */
#define RTC_TSDR_WDU_2                    (0x4U << RTC_TSDR_WDU_Pos)           /*!< 0x00008000 */
#define RTC_TSDR_MT_Pos                   (12U)
#define RTC_TSDR_MT_Msk                   (0x1U << RTC_TSDR_MT_Pos)            /*!< 0x00001000 */
#define RTC_TSDR_MT                       RTC_TSDR_MT_Msk
#define RTC_TSDR_MU_Pos                   (8U)
#define RTC_TSDR_MU_Msk                   (0xFU << RTC_TSDR_MU_Pos)            /*!< 0x00000F00 */
#define RTC_TSDR_MU                       RTC_TSDR_MU_Msk
#define RTC_TSDR_MU_0                     (0x1U << RTC_TSDR_MU_Pos)            /*!< 0x00000100 */
#define RTC_TSDR_MU_1                     (0x2U << RTC_TSDR_MU_Pos)            /*!< 0x00000200 */
#define RTC_TSDR_MU_2                     (0x4U << RTC_TSDR_MU_Pos)            /*!< 0x00000400 */
#define RTC_TSDR_MU_3                     (0x8U << RTC_TSDR_MU_Pos)            /*!< 0x00000800 */
#define RTC_TSDR_DT_Pos                   (4U)
#define RTC_TSDR_DT_Msk                   (0x3U << RTC_TSDR_DT_Pos)            /*!< 0x00000030 */
#define RTC_TSDR_DT                       RTC_TSDR_DT_Msk
#define RTC_TSDR_DT_0                     (0x1U << RTC_TSDR_DT_Pos)            /*!< 0x00000010 */
#define RTC_TSDR_DT_1                     (0x2U << RTC_TSDR_DT_Pos)            /*!< 0x00000020 */
#define RTC_TSDR_DU_Pos                   (0U)
#define RTC_TSDR_DU_Msk                   (0xFU << RTC_TSDR_DU_Pos)            /*!< 0x0000000F */
#define RTC_TSDR_DU                       RTC_TSDR_DU_Msk
#define RTC_TSDR_DU_0                     (0x1U << RTC_TSDR_DU_Pos)            /*!< 0x00000001 */
#define RTC_TSDR_DU_1                     (0x2U << RTC_TSDR_DU_Pos)            /*!< 0x00000002 */
#define RTC_TSDR_DU_2                     (0x4U << RTC_TSDR_DU_Pos)            /*!< 0x00000004 */
#define RTC_TSDR_DU_3                     (0x8U << RTC_TSDR_DU_Pos)            /*!< 0x00000008 */

/********************  Bits definition for RTC_TSSSR register  ******************/
#define RTC_TSSSR_SS_Pos                  (0U)
#define RTC_TSSSR_SS_Msk                  (0xFFFFU << RTC_TSSSR_SS_Pos)        /*!< 0x0000FFFF */
#define RTC_TSSSR_SS                      RTC_TSSSR_SS_Msk

/********************  Bits definition for RTC_ALRMAR register  ***************/
#define RTC_ALRMAR_MSK4_Pos               (31U)
#define RTC_ALRMAR_MSK4_Msk               (0x1U << RTC_ALRMAR_MSK4_Pos)        /*!< 0x80000000 */
#define RTC_ALRMAR_MSK4                   RTC_ALRMAR_MSK4_Msk
#define RTC_ALRMAR_WDSEL_Pos              (30U)
#define RTC_ALRMAR_WDSEL_Msk              (0x1U << RTC_ALRMAR_WDSEL_Pos)       /*!< 0x40000000 */
#define RTC_ALRMAR_WDSEL                  RTC_ALRMAR_WDSEL_Msk
#define RTC_ALRMAR_DT_Pos                 (28U)
#define RTC_ALRMAR_DT_Msk                 (0x3U << RTC_ALRMAR_DT_Pos)          /*!< 0x30000000 */
#define RTC_ALRMAR_DT                     RTC_ALRMAR_DT_Msk
#define RTC_ALRMAR_DT_0                   (0x1U << RTC_ALRMAR_DT_Pos)          /*!< 0x10000000 */
#define RTC_ALRMAR_DT_1                   (0x2U << RTC_ALRMAR_DT_Pos)          /*!< 0x20000000 */
#define RTC_ALRMAR_DU_Pos                 (24U)
#define RTC_ALRMAR_DU_Msk                 (0xFU << RTC_ALRMAR_DU_Pos)          /*!< 0x0F000000 */
#define RTC_ALRMAR_DU                     RTC_ALRMAR_DU_Msk
#define RTC_ALRMAR_DU_0                   (0x1U << RTC_ALRMAR_DU_Pos)          /*!< 0x01000000 */
#define RTC_ALRMAR_DU_1                   (0x2U << RTC_ALRMAR_DU_Pos)          /*!< 0x02000000 */
#define RTC_ALRMAR_DU_2                   (0x4U << RTC_ALRMAR_DU_Pos)          /*!< 0x04000000 */
#define RTC_ALRMAR_DU_3                   (0x8U << RTC_ALRMAR_DU_Pos)          /*!< 0x08000000 */
#define RTC_ALRMAR_MSK3_Pos               (23U)
#define RTC_ALRMAR_MSK3_Msk               (0x1U << RTC_ALRMAR_MSK3_Pos)        /*!< 0x00800000 */
#define RTC_ALRMAR_MSK3                   RTC_ALRMAR_MSK3_Msk
#define RTC_ALRMAR_PM_Pos                 (22U)
#define RTC_ALRMAR_PM_Msk                 (0x1U << RTC_ALRMAR_PM_Pos)          /*!< 0x00400000 */
#define RTC_ALRMAR_PM                     RTC_ALRMAR_PM_Msk
#define RTC_ALRMAR_HT_Pos                 (20U)
#define RTC_ALRMAR_HT_Msk                 (0x3U << RTC_ALRMAR_HT_Pos)          /*!< 0x00300000 */
#define RTC_ALRMAR_HT                     RTC_ALRMAR_HT_Msk
#define RTC_ALRMAR_HT_0                   (0x1U << RTC_ALRMAR_HT_Pos)          /*!< 0x00100000 */
#define RTC_ALRMAR_HT_1                   (0x2U << RTC_ALRMAR_HT_Pos)          /*!< 0x00200000 */
#define RTC_ALRMAR_HU_Pos                 (16U)
#define RTC_ALRMAR_HU_Msk                 (0xFU << RTC_ALRMAR_HU_Pos)          /*!< 0x000F0000 */
#define RTC_ALRMAR_HU                     RTC_ALRMAR_HU_Msk
#define RTC_ALRMAR_HU_0                   (0x1U << RTC_ALRMAR_HU_Pos)          /*!< 0x00010000 */
#define RTC_ALRMAR_HU_1                   (0x2U << RTC_ALRMAR_HU_Pos)          /*!< 0x00020000 */
#define RTC_ALRMAR_HU_2                   (0x4U << RTC_ALRMAR_HU_Pos)          /*!< 0x00040000 */
#define RTC_ALRMAR_HU_3                   (0x8U << RTC_ALRMAR_HU_Pos)          /*!< 0x00080000 */
#define RTC_ALRMAR_MSK2_Pos               (15U)
#define RTC_ALRMAR_MSK2_Msk               (0x1U << RTC_ALRMAR_MSK2_Pos)        /*!< 0x00008000 */
#define RTC_ALRMAR_MSK2                   RTC_ALRMAR_MSK2_Msk
#define RTC_ALRMAR_MNT_Pos                (12U)
#define RTC_ALRMAR_MNT_Msk                (0x7U << RTC_ALRMAR_MNT_Pos)         /*!< 0x00007000 */
#define RTC_ALRMAR_MNT                    RTC_ALRMAR_MNT_Msk
#define RTC_ALRMAR_MNT_0                  (0x1U << RTC_ALRMAR_MNT_Pos)         /*!< 0x00001000 */
#define RTC_ALRMAR_MNT_1                  (0x2U << RTC_ALRMAR_MNT_Pos)         /*!< 0x00002000 */
#define RTC_ALRMAR_MNT_2                  (0x4U << RTC_ALRMAR_MNT_Pos)         /*!< 0x00004000 */
#define RTC_ALRMAR_MNU_Pos                (8U)
#define RTC_ALRMAR_MNU_Msk                (0xFU << RTC_ALRMAR_MNU_Pos)         /*!< 0x00000F00 */
#define RTC_ALRMAR_MNU                    RTC_ALRMAR_MNU_Msk
#define RTC_ALRMAR_MNU_0                  (0x1U << RTC_ALRMAR_MNU_Pos)         /*!< 0x00000100 */
#define RTC_ALRMAR_MNU_1                  (0x2U << RTC_ALRMAR_MNU_Pos)         /*!< 0x00000200 */
#define RTC_ALRMAR_MNU_2                  (0x4U << RTC_ALRMAR_MNU_Pos)         /*!< 0x00000400 */
#define RTC_ALRMAR_MNU_3                  (0x8U << RTC_ALRMAR_MNU_Pos)         /*!< 0x00000800 */
#define RTC_ALRMAR_MSK1_Pos               (7U)
#define RTC_ALRMAR_MSK1_Msk               (0x1U << RTC_ALRMAR_MSK1_Pos)        /*!< 0x00000080 */
#define RTC_ALRMAR_MSK1                   RTC_ALRMAR_MSK1_Msk
#define RTC_ALRMAR_ST_Pos                 (4U)
#define RTC_ALRMAR_ST_Msk                 (0x7U << RTC_ALRMAR_ST_Pos)          /*!< 0x00000070 */
#define RTC_ALRMAR_ST                     RTC_ALRMAR_ST_Msk
#define RTC_ALRMAR_ST_0                   (0x1U << RTC_ALRMAR_ST_Pos)          /*!< 0x00000010 */
#define RTC_ALRMAR_ST_1                   (0x2U << RTC_ALRMAR_ST_Pos)          /*!< 0x00000020 */
#define RTC_ALRMAR_ST_2                   (0x4U << RTC_ALRMAR_ST_Pos)          /*!< 0x00000040 */
#define RTC_ALRMAR_SU_Pos                 (0U)
#define RTC_ALRMAR_SU_Msk                 (0xFU << RTC_ALRMAR_SU_Pos)          /*!< 0x0000000F */
#define RTC_ALRMAR_SU                     RTC_ALRMAR_SU_Msk
#define RTC_ALRMAR_SU_0                   (0x1U << RTC_ALRMAR_SU_Pos)          /*!< 0x00000001 */
#define RTC_ALRMAR_SU_1                   (0x2U << RTC_ALRMAR_SU_Pos)          /*!< 0x00000002 */
#define RTC_ALRMAR_SU_2                   (0x4U << RTC_ALRMAR_SU_Pos)          /*!< 0x00000004 */
#define RTC_ALRMAR_SU_3                   (0x8U << RTC_ALRMAR_SU_Pos)          /*!< 0x00000008 */

/********************  Bits definition for RTC_ALRMASSR register  *************/
#define RTC_ALRMASSR_MASKSS_Pos           (24U)
#define RTC_ALRMASSR_MASKSS_Msk           (0xFU << RTC_ALRMASSR_MASKSS_Pos)    /*!< 0x0F000000 */
#define RTC_ALRMASSR_MASKSS               RTC_ALRMASSR_MASKSS_Msk
#define RTC_ALRMASSR_MASKSS_0             (0x1U << RTC_ALRMASSR_MASKSS_Pos)    /*!< 0x01000000 */
#define RTC_ALRMASSR_MASKSS_1             (0x2U << RTC_ALRMASSR_MASKSS_Pos)    /*!< 0x02000000 */
#define RTC_ALRMASSR_MASKSS_2             (0x4U << RTC_ALRMASSR_MASKSS_Pos)    /*!< 0x04000000 */
#define RTC_ALRMASSR_MASKSS_3             (0x8U << RTC_ALRMASSR_MASKSS_Pos)    /*!< 0x08000000 */
#define RTC_ALRMASSR_SS_Pos               (0U)
#define RTC_ALRMASSR_SS_Msk               (0x7FFFU << RTC_ALRMASSR_SS_Pos)     /*!< 0x00007FFF */
#define RTC_ALRMASSR_SS                   RTC_ALRMASSR_SS_Msk

/********************  Bits definition for RTC_ALRMBR register  ***************/
#define RTC_ALRMBR_MSK4_Pos               (31U)
#define RTC_ALRMBR_MSK4_Msk               (0x1U << RTC_ALRMBR_MSK4_Pos)        /*!< 0x80000000 */
#define RTC_ALRMBR_MSK4                   RTC_ALRMBR_MSK4_Msk
#define RTC_ALRMBR_WDSEL_Pos              (30U)
#define RTC_ALRMBR_WDSEL_Msk              (0x1U << RTC_ALRMBR_WDSEL_Pos)       /*!< 0x40000000 */
#define RTC_ALRMBR_WDSEL                  RTC_ALRMBR_WDSEL_Msk
#define RTC_ALRMBR_DT_Pos                 (28U)
#define RTC_ALRMBR_DT_Msk                 (0x3U << RTC_ALRMBR_DT_Pos)          /*!< 0x30000000 */
#define RTC_ALRMBR_DT                     RTC_ALRMBR_DT_Msk
#define RTC_ALRMBR_DT_0                   (0x1U << RTC_ALRMBR_DT_Pos)          /*!< 0x10000000 */
#define RTC_ALRMBR_DT_1                   (0x2U << RTC_ALRMBR_DT_Pos)          /*!< 0x20000000 */
#define RTC_ALRMBR_DU_Pos                 (24U)
#define RTC_ALRMBR_DU_Msk                 (0xFU << RTC_ALRMBR_DU_Pos)          /*!< 0x0F000000 */
#define RTC_ALRMBR_DU                     RTC_ALRMBR_DU_Msk
#define RTC_ALRMBR_DU_0                   (0x1U << RTC_ALRMBR_DU_Pos)          /*!< 0x01000000 */
#define RTC_ALRMBR_DU_1                   (0x2U << RTC_ALRMBR_DU_Pos)          /*!< 0x02000000 */
#define RTC_ALRMBR_DU_2                   (0x4U << RTC_ALRMBR_DU_Pos)          /*!< 0x04000000 */
#define RTC_ALRMBR_DU_3                   (0x8U << RTC_ALRMBR_DU_Pos)          /*!< 0x08000000 */
#define RTC_ALRMBR_MSK3_Pos               (23U)
#define RTC_ALRMBR_MSK3_Msk               (0x1U << RTC_ALRMBR_MSK3_Pos)        /*!< 0x00800000 */
#define RTC_ALRMBR_MSK3                   RTC_ALRMBR_MSK3_Msk
#define RTC_ALRMBR_PM_Pos                 (22U)
#define RTC_ALRMBR_PM_Msk                 (0x1U << RTC_ALRMBR_PM_Pos)          /*!< 0x00400000 */
#define RTC_ALRMBR_PM                     RTC_ALRMBR_PM_Msk
#define RTC_ALRMBR_HT_Pos                 (20U)
#define RTC_ALRMBR_HT_Msk                 (0x3U << RTC_ALRMBR_HT_Pos)          /*!< 0x00300000 */
#define RTC_ALRMBR_HT                     RTC_ALRMBR_HT_Msk
#define RTC_ALRMBR_HT_0                   (0x1U << RTC_ALRMBR_HT_Pos)          /*!< 0x00100000 */
#define RTC_ALRMBR_HT_1                   (0x2U << RTC_ALRMBR_HT_Pos)          /*!< 0x00200000 */
#define RTC_ALRMBR_HU_Pos                 (16U)
#define RTC_ALRMBR_HU_Msk                 (0xFU << RTC_ALRMBR_HU_Pos)          /*!< 0x000F0000 */
#define RTC_ALRMBR_HU                     RTC_ALRMBR_HU_Msk
#define RTC_ALRMBR_HU_0                   (0x1U << RTC_ALRMBR_HU_Pos)          /*!< 0x00010000 */
#define RTC_ALRMBR_HU_1                   (0x2U << RTC_ALRMBR_HU_Pos)          /*!< 0x00020000 */
#define RTC_ALRMBR_HU_2                   (0x4U << RTC_ALRMBR_HU_Pos)          /*!< 0x00040000 */
#define RTC_ALRMBR_HU_3                   (0x8U << RTC_ALRMBR_HU_Pos)          /*!< 0x00080000 */
#define RTC_ALRMBR_MSK2_Pos               (15U)
#define RTC_ALRMBR_MSK2_Msk               (0x1U << RTC_ALRMBR_MSK2_Pos)        /*!< 0x00008000 */
#define RTC_ALRMBR_MSK2                   RTC_ALRMBR_MSK2_Msk
#define RTC_ALRMBR_MNT_Pos                (12U)
#define RTC_ALRMBR_MNT_Msk                (0x7U << RTC_ALRMBR_MNT_Pos)         /*!< 0x00007000 */
#define RTC_ALRMBR_MNT                    RTC_ALRMBR_MNT_Msk
#define RTC_ALRMBR_MNT_0                  (0x1U << RTC_ALRMBR_MNT_Pos)         /*!< 0x00001000 */
#define RTC_ALRMBR_MNT_1                  (0x2U << RTC_ALRMBR_MNT_Pos)         /*!< 0x00002000 */
#define RTC_ALRMBR_MNT_2                  (0x4U << RTC_ALRMBR_MNT_Pos)         /*!< 0x00004000 */
#define RTC_ALRMBR_MNU_Pos                (8U)
#define RTC_ALRMBR_MNU_Msk                (0xFU << RTC_ALRMBR_MNU_Pos)         /*!< 0x00000F00 */
#define RTC_ALRMBR_MNU                    RTC_ALRMBR_MNU_Msk
#define RTC_ALRMBR_MNU_0                  (0x1U << RTC_ALRMBR_MNU_Pos)         /*!< 0x00000100 */
#define RTC_ALRMBR_MNU_1                  (0x2U << RTC_ALRMBR_MNU_Pos)         /*!< 0x00000200 */
#define RTC_ALRMBR_MNU_2                  (0x4U << RTC_ALRMBR_MNU_Pos)         /*!< 0x00000400 */
#define RTC_ALRMBR_MNU_3                  (0x8U << RTC_ALRMBR_MNU_Pos)         /*!< 0x00000800 */
#define RTC_ALRMBR_MSK1_Pos               (7U)
#define RTC_ALRMBR_MSK1_Msk               (0x1U << RTC_ALRMBR_MSK1_Pos)        /*!< 0x00000080 */
#define RTC_ALRMBR_MSK1                   RTC_ALRMBR_MSK1_Msk
#define RTC_ALRMBR_ST_Pos                 (4U)
#define RTC_ALRMBR_ST_Msk                 (0x7U << RTC_ALRMBR_ST_Pos)          /*!< 0x00000070 */
#define RTC_ALRMBR_ST                     RTC_ALRMBR_ST_Msk
#define RTC_ALRMBR_ST_0                   (0x1U << RTC_ALRMBR_ST_Pos)          /*!< 0x00000010 */
#define RTC_ALRMBR_ST_1                   (0x2U << RTC_ALRMBR_ST_Pos)          /*!< 0x00000020 */
#define RTC_ALRMBR_ST_2                   (0x4U << RTC_ALRMBR_ST_Pos)          /*!< 0x00000040 */
#define RTC_ALRMBR_SU_Pos                 (0U)
#define RTC_ALRMBR_SU_Msk                 (0xFU << RTC_ALRMBR_SU_Pos)          /*!< 0x0000000F */
#define RTC_ALRMBR_SU                     RTC_ALRMBR_SU_Msk
#define RTC_ALRMBR_SU_0                   (0x1U << RTC_ALRMBR_SU_Pos)          /*!< 0x00000001 */
#define RTC_ALRMBR_SU_1                   (0x2U << RTC_ALRMBR_SU_Pos)          /*!< 0x00000002 */
#define RTC_ALRMBR_SU_2                   (0x4U << RTC_ALRMBR_SU_Pos)          /*!< 0x00000004 */
#define RTC_ALRMBR_SU_3                   (0x8U << RTC_ALRMBR_SU_Pos)          /*!< 0x00000008 */

/********************  Bits definition for RTC_ALRMBSSR register  *************/
#define RTC_ALRMBSSR_MASKSS_Pos           (24U)
#define RTC_ALRMBSSR_MASKSS_Msk           (0xFU << RTC_ALRMBSSR_MASKSS_Pos)    /*!< 0x0F000000 */
#define RTC_ALRMBSSR_MASKSS               RTC_ALRMBSSR_MASKSS_Msk
#define RTC_ALRMBSSR_MASKSS_0             (0x1U << RTC_ALRMBSSR_MASKSS_Pos)    /*!< 0x01000000 */
#define RTC_ALRMBSSR_MASKSS_1             (0x2U << RTC_ALRMBSSR_MASKSS_Pos)    /*!< 0x02000000 */
#define RTC_ALRMBSSR_MASKSS_2             (0x4U << RTC_ALRMBSSR_MASKSS_Pos)    /*!< 0x04000000 */
#define RTC_ALRMBSSR_MASKSS_3             (0x8U << RTC_ALRMBSSR_MASKSS_Pos)    /*!< 0x08000000 */
#define RTC_ALRMBSSR_SS_Pos               (0U)
#define RTC_ALRMBSSR_SS_Msk               (0x7FFFU << RTC_ALRMBSSR_SS_Pos)     /*!< 0x00007FFF */
#define RTC_ALRMBSSR_SS                   RTC_ALRMBSSR_SS_Msk

/********************  Bits definition for RTC_SR register  *************/
#define RTC_SR_ITSF_Pos                   (5U)
#define RTC_SR_ITSF_Msk                   (0x1U << RTC_SR_ITSF_Pos)            /*!< 0x00000020 */
#define RTC_SR_ITSF                       RTC_SR_ITSF_Msk
#define RTC_SR_TSOVF_Pos                  (4U)
#define RTC_SR_TSOVF_Msk                  (0x1U << RTC_SR_TSOVF_Pos)           /*!< 0x00000010 */
#define RTC_SR_TSOVF                      RTC_SR_TSOVF_Msk
#define RTC_SR_TSF_Pos                    (3U)
#define RTC_SR_TSF_Msk                    (0x1U << RTC_SR_TSF_Pos)             /*!< 0x00000008 */
#define RTC_SR_TSF                        RTC_SR_TSF_Msk
#define RTC_SR_WUTF_Pos                   (2U)
#define RTC_SR_WUTF_Msk                   (0x1U << RTC_SR_WUTF_Pos)            /*!< 0x00000004 */
#define RTC_SR_WUTF                       RTC_SR_WUTF_Msk
#define RTC_SR_ALRBF_Pos                  (1U)
#define RTC_SR_ALRBF_Msk                  (0x1U << RTC_SR_ALRBF_Pos)           /*!< 0x00000002 */
#define RTC_SR_ALRBF                      RTC_SR_ALRBF_Msk
#define RTC_SR_ALRAF_Pos                  (0U)
#define RTC_SR_ALRAF_Msk                  (0x1U << RTC_SR_ALRAF_Pos)           /*!< 0x00000001 */
#define RTC_SR_ALRAF                      RTC_SR_ALRAF_Msk

/********************  Bits definition for RTC_MISR register  *************/
#define RTC_MISR_ITSMF_Pos                (5U)
#define RTC_MISR_ITSMF_Msk                (0x1U << RTC_MISR_ITSMF_Pos)         /*!< 0x00000020 */
#define RTC_MISR_ITSMF                    RTC_MISR_ITSMF_Msk
#define RTC_MISR_TSOVMF_Pos               (4U)
#define RTC_MISR_TSOVMF_Msk               (0x1U << RTC_MISR_TSOVMF_Pos)        /*!< 0x00000010 */
#define RTC_MISR_TSOVMF                   RTC_MISR_TSOVMF_Msk
#define RTC_MISR_TSMF_Pos                 (3U)
#define RTC_MISR_TSMF_Msk                 (0x1U << RTC_MISR_TSMF_Pos)          /*!< 0x00000008 */
#define RTC_MISR_TSMF                     RTC_MISR_TSMF_Msk
#define RTC_MISR_WUTMF_Pos                (2U)
#define RTC_MISR_WUTMF_Msk                (0x1U << RTC_MISR_WUTMF_Pos)         /*!< 0x00000004 */
#define RTC_MISR_WUTMF                    RTC_MISR_WUTMF_Msk
#define RTC_MISR_ALRBMF_Pos               (1U)
#define RTC_MISR_ALRBMF_Msk               (0x1U << RTC_MISR_ALRBMF_Pos)        /*!< 0x00000002 */
#define RTC_MISR_ALRBMF                   RTC_MISR_ALRBMF_Msk
#define RTC_MISR_ALRAMF_Pos               (0U)
#define RTC_MISR_ALRAMF_Msk               (0x1U << RTC_MISR_ALRAMF_Pos)        /*!< 0x00000001 */
#define RTC_MISR_ALRAMF                   RTC_MISR_ALRAMF_Msk

/********************  Bits definition for RTC_SMISR register  *************/
#define RTC_SMISR_ITSMF_Pos               (5U)
#define RTC_SMISR_ITSMF_Msk               (0x1U << RTC_SMISR_ITSMF_Pos)        /*!< 0x00000020 */
#define RTC_SMISR_ITSMF                   RTC_SMISR_ITSMF_Msk
#define RTC_SMISR_TSOVMF_Pos              (4U)
#define RTC_SMISR_TSOVMF_Msk              (0x1U << RTC_SMISR_TSOVMF_Pos)       /*!< 0x00000010 */
#define RTC_SMISR_TSOVMF                  RTC_SMISR_TSOVMF_Msk
#define RTC_SMISR_TSMF_Pos                (3U)
#define RTC_SMISR_TSMF_Msk                (0x1U << RTC_SMISR_TSMF_Pos)         /*!< 0x00000008 */
#define RTC_SMISR_TSMF                    RTC_SMISR_TSMF_Msk
#define RTC_SMISR_WUTMF_Pos               (2U)
#define RTC_SMISR_WUTMF_Msk               (0x1U << RTC_SMISR_WUTMF_Pos)        /*!< 0x00000004 */
#define RTC_SMISR_WUTMF                   RTC_SMISR_WUTMF_Msk
#define RTC_SMISR_ALRBMF_Pos              (1U)
#define RTC_SMISR_ALRBMF_Msk              (0x1U << RTC_SMISR_ALRBMF_Pos)       /*!< 0x00000002 */
#define RTC_SMISR_ALRBMF                  RTC_SMISR_ALRBMF_Msk
#define RTC_SMISR_ALRAMF_Pos              (0U)
#define RTC_SMISR_ALRAMF_Msk              (0x1U << RTC_SMISR_ALRAMF_Pos)       /*!< 0x00000001 */
#define RTC_SMISR_ALRAMF                  RTC_SMISR_ALRAMF_Msk

/********************  Bits definition for RTC_SCR register  *************/
#define RTC_SCR_CITSF_Pos                 (5U)
#define RTC_SCR_CITSF_Msk                 (0x1U << RTC_SCR_CITSF_Pos)          /*!< 0x00000020 */
#define RTC_SCR_CITSF                     RTC_SCR_CITSF_Msk
#define RTC_SCR_CTSOVF_Pos                (4U)
#define RTC_SCR_CTSOVF_Msk                (0x1U << RTC_SCR_CTSOVF_Pos)         /*!< 0x00000010 */
#define RTC_SCR_CTSOVF                    RTC_SCR_CTSOVF_Msk
#define RTC_SCR_CTSF_Pos                  (3U)
#define RTC_SCR_CTSF_Msk                  (0x1U << RTC_SCR_CTSF_Pos)           /*!< 0x00000008 */
#define RTC_SCR_CTSF                      RTC_SCR_CTSF_Msk
#define RTC_SCR_CWUTF_Pos                 (2U)
#define RTC_SCR_CWUTF_Msk                 (0x1U << RTC_SCR_CWUTF_Pos)          /*!< 0x00000004 */
#define RTC_SCR_CWUTF                     RTC_SCR_CWUTF_Msk
#define RTC_SCR_CALRBF_Pos                (1U)
#define RTC_SCR_CALRBF_Msk                (0x1U << RTC_SCR_CALRBF_Pos)         /*!< 0x00000002 */
#define RTC_SCR_CALRBF                    RTC_SCR_CALRBF_Msk
#define RTC_SCR_CALRAF_Pos                (0U)
#define RTC_SCR_CALRAF_Msk                (0x1U << RTC_SCR_CALRAF_Pos)         /*!< 0x00000001 */
#define RTC_SCR_CALRAF                    RTC_SCR_CALRAF_Msk

/********************  Bits definition for RTC_OR register  ****************/
#define RTC_CFGR_LSCOEN_Pos               (1U)
#define RTC_CFGR_LSCOEN_Msk               (0x3U << RTC_CFGR_LSCOEN_Pos)        /*!< 0x00000006 */
#define RTC_CFGR_LSCOEN                   RTC_CFGR_LSCOEN_Msk
#define RTC_CFGR_LSCOEN_0                 (0x1U << RTC_CFGR_LSCOEN_Pos)        /*!< 0x00000002 */
#define RTC_CFGR_LSCOEN_1                 (0x2U << RTC_CFGR_LSCOEN_Pos)        /*!< 0x00000004 */
#define RTC_CFGR_OUT2_RMP_Pos             (0U)
#define RTC_CFGR_OUT2_RMP_Msk             (0x1U << RTC_OR_OUT2_RMP_Pos)        /*!< 0x00000001 */
#define RTC_CFGR_OUT2_RMP                 RTC_OR_OUT2_RMP_Msk

/********************  Bits definition for RTC_HWCFGR register  *************/

#define RTC_HWCFGR_TRUST_ZONE_Pos         (24U)
#define RTC_HWCFGR_TRUST_ZONE_Msk         (0xFU << RTC_HWCFGR_TRUST_ZONE_Pos)  /*!< 0x0F000000 */
#define RTC_HWCFGR_TRUST_ZONE             RTC_HWCFGR_TRUST_ZONE_Msk
#define RTC_HWCFGR_TRUST_ZONE_0           (0x1U << RTC_HWCFGR_TRUST_ZONE_Pos)  /*!< 0x01000000 */
#define RTC_HWCFGR_TRUST_ZONE_1           (0x2U << RTC_HWCFGR_TRUST_ZONE_Pos)  /*!< 0x02000000 */
#define RTC_HWCFGR_TRUST_ZONE_2           (0x4U << RTC_HWCFGR_TRUST_ZONE_Pos)  /*!< 0x04000000 */
#define RTC_HWCFGR_TRUST_ZONE_3           (0x8U << RTC_HWCFGR_TRUST_ZONE_Pos)  /*!< 0x08000000 */

#define RTC_HWCFGR_OPTIONREG_OUT_Pos      (16U)
#define RTC_HWCFGR_OPTIONREG_OUT_Msk      (0xFFU << RTC_HWCFGR_OPTIONREG_OUT_Pos) /*!< 0x00FF0000 */
#define RTC_HWCFGR_OPTIONREG_OUT          RTC_HWCFGR_OPTIONREG_OUT_Msk
#define RTC_HWCFGR_OPTIONREG_OUT_0        (0x01U << RTC_HWCFGR_OPTIONREG_OUT_Pos) /*!< 0x00010000 */
#define RTC_HWCFGR_OPTIONREG_OUT_1        (0x02U << RTC_HWCFGR_OPTIONREG_OUT_Pos) /*!< 0x00020000 */
#define RTC_HWCFGR_OPTIONREG_OUT_2        (0x04U << RTC_HWCFGR_OPTIONREG_OUT_Pos) /*!< 0x00040000 */
#define RTC_HWCFGR_OPTIONREG_OUT_3        (0x08U << RTC_HWCFGR_OPTIONREG_OUT_Pos) /*!< 0x00080000 */
#define RTC_HWCFGR_OPTIONREG_OUT_4        (0x10U << RTC_HWCFGR_OPTIONREG_OUT_Pos) /*!< 0x00100000 */
#define RTC_HWCFGR_OPTIONREG_OUT_5        (0x20U << RTC_HWCFGR_OPTIONREG_OUT_Pos) /*!< 0x00200000 */
#define RTC_HWCFGR_OPTIONREG_OUT_6        (0x40U << RTC_HWCFGR_OPTIONREG_OUT_Pos) /*!< 0x00400000 */
#define RTC_HWCFGR_OPTIONREG_OUT_7        (0x80U << RTC_HWCFGR_OPTIONREG_OUT_Pos) /*!< 0x00800000 */

#define RTC_HWCFGR_TIMESTAMP_Pos          (12U)
#define RTC_HWCFGR_TIMESTAMP_Msk          (0xFU << RTC_HWCFGR_TIMESTAMP_Pos)   /*!< 0x0000F000 */
#define RTC_HWCFGR_TIMESTAMP              RTC_HWCFGR_TIMESTAMP_Msk
#define RTC_HWCFGR_TIMESTAMP_0            (0x1U << RTC_HWCFGR_TIMESTAMP_Pos)   /*!< 0x00001000 */
#define RTC_HWCFGR_TIMESTAMP_1            (0x2U << RTC_HWCFGR_TIMESTAMP_Pos)   /*!< 0x00002000 */
#define RTC_HWCFGR_TIMESTAMP_2            (0x4U << RTC_HWCFGR_TIMESTAMP_Pos)   /*!< 0x00004000 */
#define RTC_HWCFGR_TIMESTAMP_3            (0x8U << RTC_HWCFGR_TIMESTAMP_Pos)   /*!< 0x00008000 */

#define RTC_HWCFGR_SMOOTH_CALIB_Pos       (8U)
#define RTC_HWCFGR_SMOOTH_CALIB_Msk       (0xFU << RTC_HWCFGR_SMOOTH_CALIB_Pos) /*!< 0x00000F00 */
#define RTC_HWCFGR_SMOOTH_CALIB           RTC_HWCFGR_SMOOTH_CALIB_Msk
#define RTC_HWCFGR_SMOOTH_CALIB_0         (0x1U << RTC_HWCFGR_SMOOTH_CALIB_Pos) /*!< 0x00000100 */
#define RTC_HWCFGR_SMOOTH_CALIB_1         (0x2U << RTC_HWCFGR_SMOOTH_CALIB_Pos) /*!< 0x00000200 */
#define RTC_HWCFGR_SMOOTH_CALIB_2         (0x4U << RTC_HWCFGR_SMOOTH_CALIB_Pos) /*!< 0x00000400 */
#define RTC_HWCFGR_SMOOTH_CALIB_3         (0x8U << RTC_HWCFGR_SMOOTH_CALIB_Pos) /*!< 0x00000800 */

#define RTC_HWCFGR_WAKEUP_Pos             (4U)
#define RTC_HWCFGR_WAKEUP_Msk             (0xFU << RTC_HWCFGR_WAKEUP_Pos)      /*!< 0x000000F0 */
#define RTC_HWCFGR_WAKEUP                 RTC_HWCFGR_WAKEUP_Msk
#define RTC_HWCFGR_WAKEUP_0               (0x1U << RTC_HWCFGR_WAKEUP_Pos)      /*!< 0x00000010 */
#define RTC_HWCFGR_WAKEUP_1               (0x2U << RTC_HWCFGR_WAKEUP_Pos)      /*!< 0x00000020 */
#define RTC_HWCFGR_WAKEUP_2               (0x4U << RTC_HWCFGR_WAKEUP_Pos)      /*!< 0x00000040 */
#define RTC_HWCFGR_WAKEUP_3               (0x8U << RTC_HWCFGR_WAKEUP_Pos)      /*!< 0x00000080 */

#define RTC_HWCFGR_ALARMB_Pos             (0U)
#define RTC_HWCFGR_ALARMB_Msk             (0xFU << RTC_HWCFGR_ALARMB_Pos)      /*!< 0x0000000F */
#define RTC_HWCFGR_ALARMB                 RTC_HWCFGR_ALARMB_Msk
#define RTC_HWCFGR_ALARMB_0               (0x1U << RTC_HWCFGR_ALARMB_Pos)      /*!< 0x00000001 */
#define RTC_HWCFGR_ALARMB_1               (0x2U << RTC_HWCFGR_ALARMB_Pos)      /*!< 0x00000002 */
#define RTC_HWCFGR_ALARMB_2               (0x4U << RTC_HWCFGR_ALARMB_Pos)      /*!< 0x00000004 */
#define RTC_HWCFGR_ALARMB_3               (0x8U << RTC_HWCFGR_ALARMB_Pos)      /*!< 0x00000008 */


/********************  Bits definition for RTC_VERR register  ****************/
#define RTC_VERR_MAJREV_Pos               (4U)
#define RTC_VERR_MAJREV_Msk               (0xFU << RTC_VERR_MAJREV_Pos)        /*!< 0x000000F0 */
#define RTC_VERR_MAJREV                   RTC_VERR_MAJREV_Msk
#define RTC_VERR_MAJREV_0                 (0x1U << RTC_VERR_MAJREV_Pos)        /*!< 0x00000010 */
#define RTC_VERR_MAJREV_1                 (0x2U << RTC_VERR_MAJREV_Pos)        /*!< 0x00000020 */
#define RTC_VERR_MAJREV_2                 (0x4U << RTC_VERR_MAJREV_Pos)        /*!< 0x00000040 */
#define RTC_VERR_MAJREV_3                 (0x8U << RTC_VERR_MAJREV_Pos)        /*!< 0x00000080 */
#define RTC_VERR_MINREV_Pos               (0U)
#define RTC_VERR_MINREV_Msk               (0xFU << RTC_VERR_MINREV_Pos)        /*!< 0x0000000F */
#define RTC_VERR_MINREV                   RTC_VERR_MINREV_Msk
#define RTC_VERR_MINREV_0                 (0x1U << RTC_VERR_MINREV_Pos)        /*!< 0x00000001 */
#define RTC_VERR_MINREV_1                 (0x2U << RTC_VERR_MINREV_Pos)        /*!< 0x00000002 */
#define RTC_VERR_MINREV_2                 (0x4U << RTC_VERR_MINREV_Pos)        /*!< 0x00000004 */
#define RTC_VERR_MINREV_3                 (0x8U << RTC_VERR_MINREV_Pos)        /*!< 0x00000008 */

/********************  Bits definition for RTC_IPIDR register  ****************/
#define RTC_IPIDR_ID_Pos                  (0U)
#define RTC_IPIDR_ID_Msk                  (0xFFFFFFFFU << RTC_IPIDR_ID_Pos)    /*!< 0xFFFFFFFF */
#define RTC_IPIDR_ID                      RTC_IPIDR_ID_Msk

/********************  Bits definition for RTC_SIDR register  ****************/
#define RTC_SIDR_SID_Pos                  (0U)
#define RTC_SIDR_SID_Msk                  (0xFFFFFFFFU << RTC_SIDR_SID_Pos)    /*!< 0xFFFFFFFF */
#define RTC_SIDR_SID                      RTC_SIDR_SID_Msk

/******************************************************************************/
/*                                                                            */
/*                           Tamper and Backup registers (TAMP)               */
/*                                                                            */
/******************************************************************************/

/********************  Bits definition for TAMP_CR1 register  ***************/
#define TAMP_CR1_TAMPE_Pos                  (0U)
#define TAMP_CR1_TAMPE_Msk                  (0x7U << TAMP_CR1_TAMPE_Pos)      /*!< 0x000000FF */
#define TAMP_CR1_TAMPE                      TAMP_CR1_TAMPE_Msk
#define TAMP_CR1_TAMP1E_Pos                 (0U)
#define TAMP_CR1_TAMP1E_Msk                 (0x1U << TAMP_CR1_TAMP1E_Pos)      /*!< 0x00000001 */
#define TAMP_CR1_TAMP1E                     TAMP_CR1_TAMP1E_Msk
#define TAMP_CR1_TAMP2E_Pos                 (1U)
#define TAMP_CR1_TAMP2E_Msk                 (0x1U << TAMP_CR1_TAMP2E_Pos)      /*!< 0x00000002 */
#define TAMP_CR1_TAMP2E                     TAMP_CR1_TAMP2E_Msk
#define TAMP_CR1_TAMP3E_Pos                 (2U)
#define TAMP_CR1_TAMP3E_Msk                 (0x1U << TAMP_CR1_TAMP3E_Pos)      /*!< 0x00000004 */
#define TAMP_CR1_TAMP3E                     TAMP_CR1_TAMP3E_Msk
#define TAMP_CR1_ITAMPE_Pos                 (16U)
#define TAMP_CR1_ITAMPE_Msk                 (0x9FU << TAMP_CR1_ITAMPE_Pos)   /*!< 0xFFFF0000 */
#define TAMP_CR1_ITAMPE                     TAMP_CR1_ITAMPE_Msk
#define TAMP_CR1_ITAMP1E_Pos                (16U)
#define TAMP_CR1_ITAMP1E_Msk                (0x1U << TAMP_CR1_ITAMP1E_Pos)     /*!< 0x00010000 */
#define TAMP_CR1_ITAMP1E                    TAMP_CR1_ITAMP1E_Msk
#define TAMP_CR1_ITAMP2E_Pos                (17U)
#define TAMP_CR1_ITAMP2E_Msk                (0x1U << TAMP_CR1_ITAMP2E_Pos)     /*!< 0x00020000 */
#define TAMP_CR1_ITAMP2E                    TAMP_CR1_ITAMP2E_Msk
#define TAMP_CR1_ITAMP3E_Pos                (18U)
#define TAMP_CR1_ITAMP3E_Msk                (0x1U << TAMP_CR1_ITAMP3E_Pos)     /*!< 0x00040000 */
#define TAMP_CR1_ITAMP3E                    TAMP_CR1_ITAMP3E_Msk
#define TAMP_CR1_ITAMP4E_Pos                (19U)
#define TAMP_CR1_ITAMP4E_Msk                (0x1U << TAMP_CR1_ITAMP4E_Pos)     /*!< 0x00080000 */
#define TAMP_CR1_ITAMP4E                    TAMP_CR1_ITAMP4E_Msk
#define TAMP_CR1_ITAMP5E_Pos                (20U)
#define TAMP_CR1_ITAMP5E_Msk                (0x1U << TAMP_CR1_ITAMP5E_Pos)     /*!< 0x00100000 */
#define TAMP_CR1_ITAMP5E                    TAMP_CR1_ITAMP5E_Msk
#define TAMP_CR1_ITAMP8E_Pos                (23U)
#define TAMP_CR1_ITAMP8E_Msk                (0x1U << TAMP_CR1_ITAMP8E_Pos)     /*!< 0x00800000 */
#define TAMP_CR1_ITAMP8E                    TAMP_CR1_ITAMP8E_Msk


/********************  Bits definition for TAMP_CR2 register  ***************/
#define TAMP_CR2_TAMPNOERASE_Pos            (0U)
#define TAMP_CR2_TAMPNOERase_Msk            (0x7U << TAMP_CR2_TAMPNOERASE_Pos)   /*!< 0x000000FF */
#define TAMP_CR2_TAMPNOER                   TAMP_CR2_TAMPNOERase_Msk
#define TAMP_CR2_TAMP1NOERASE_Pos           (0U)
#define TAMP_CR2_TAMP1NOERASE_Msk           (0x1UL << TAMP_CR2_TAMP1NOERASE_Pos) /*!< 0x00000001 */
#define TAMP_CR2_TAMP1NOERASE               TAMP_CR2_TAMP1NOERASE_Msk
#define TAMP_CR2_TAMP2NOERASE_Pos           (1U)
#define TAMP_CR2_TAMP2NOERASE_Msk           (0x1UL << TAMP_CR2_TAMP2NOERASE_Pos) /*!< 0x00000002 */
#define TAMP_CR2_TAMP2NOERASE               TAMP_CR2_TAMP2NOERASE_Msk
#define TAMP_CR2_TAMP3NOERASE_Pos           (2U)
#define TAMP_CR2_TAMP3NOERASE_Msk           (0x1UL << TAMP_CR2_TAMP3NOERASE_Pos) /*!< 0x00000004 */
#define TAMP_CR2_TAMP3NOERASE               TAMP_CR2_TAMP3NOERASE_Msk
#define TAMP_CR2_TAMPMSK_Pos                (16U)
#define TAMP_CR2_TAMPMSK_Msk                (0x7U << TAMP_CR2_TAMPMSK_Pos)       /*!< 0x00FF0000 */
#define TAMP_CR2_TAMPMSK                    TAMP_CR2_TAMPMSK_Msk
#define TAMP_CR2_TAMP1MSK_Pos               (16U)
#define TAMP_CR2_TAMP1MSK_Msk               (0x1UL << TAMP_CR2_TAMP1MSK_Pos)     /*!< 0x00010000 */
#define TAMP_CR2_TAMP1MSK                   TAMP_CR2_TAMP1MSK_Msk
#define TAMP_CR2_TAMP2MSK_Pos               (17U)
#define TAMP_CR2_TAMP2MSK_Msk               (0x1UL << TAMP_CR2_TAMP2MSK_Pos)     /*!< 0x00020000 */
#define TAMP_CR2_TAMP2MSK                   TAMP_CR2_TAMP2MSK_Msk
#define TAMP_CR2_TAMP3MSK_Pos               (18U)
#define TAMP_CR2_TAMP3MSK_Msk               (0x1UL << TAMP_CR2_TAMP3MSK_Pos)     /*!< 0x00040000 */
#define TAMP_CR2_TAMP3MSK                   TAMP_CR2_TAMP3MSK_Msk
#define TAMP_CR2_TAMPTRG_Pos                (24U)
#define TAMP_CR2_TAMPTRG_Msk                (0xFFU << TAMP_CR2_TAMPTRG_Pos)      /*!< 0xFF000000 */
#define TAMP_CR2_TAMPTRG                    TAMP_CR2_TAMPTRG_Msk
#define TAMP_CR2_TAMP1TRG_Pos               (24U)
#define TAMP_CR2_TAMP1TRG_Msk               (0x1U << TAMP_CR2_TAMP1TRG_Pos)      /*!< 0x01000000 */
#define TAMP_CR2_TAMP1TRG                   TAMP_CR2_TAMP1TRG_Msk
#define TAMP_CR2_TAMP2TRG_Pos               (25U)
#define TAMP_CR2_TAMP2TRG_Msk               (0x1U << TAMP_CR2_TAMP2TRG_Pos)      /*!< 0x02000000 */
#define TAMP_CR2_TAMP2TRG                   TAMP_CR2_TAMP2TRG_Msk
#define TAMP_CR2_TAMP3TRG_Pos               (26U)
#define TAMP_CR2_TAMP3TRG_Msk               (0x1U << TAMP_CR2_TAMP3TRG_Pos)      /*!< 0x04000000 */
#define TAMP_CR2_TAMP3TRG                   TAMP_CR2_TAMP3TRG_Msk


/********************  Bits definition for TAMP_FLTCR register  ***************/
#define TAMP_FLTCR_TAMPFREQ_Pos             (0U)
#define TAMP_FLTCR_TAMPFREQ_Msk             (0x7U << TAMP_FLTCR_TAMPFREQ_Pos)  /*!< 0x00000007 */
#define TAMP_FLTCR_TAMPFREQ                 TAMP_FLTCR_TAMPFREQ_Msk
#define TAMP_FLTCR_TAMPFREQ_0               (0x1U << TAMP_FLTCR_TAMPFREQ_Pos)  /*!< 0x00000001 */
#define TAMP_FLTCR_TAMPFREQ_1               (0x2U << TAMP_FLTCR_TAMPFREQ_Pos)  /*!< 0x00000002 */
#define TAMP_FLTCR_TAMPFREQ_2               (0x4U << TAMP_FLTCR_TAMPFREQ_Pos)  /*!< 0x00000004 */
#define TAMP_FLTCR_TAMPFLT_Pos              (3U)
#define TAMP_FLTCR_TAMPFLT_Msk              (0x3U << TAMP_FLTCR_TAMPFLT_Pos)   /*!< 0x00000018 */
#define TAMP_FLTCR_TAMPFLT                  TAMP_FLTCR_TAMPFLT_Msk
#define TAMP_FLTCR_TAMPFLT_0                (0x1U << TAMP_FLTCR_TAMPFLT_Pos)   /*!< 0x00000008 */
#define TAMP_FLTCR_TAMPFLT_1                (0x2U << TAMP_FLTCR_TAMPFLT_Pos)   /*!< 0x00000010 */
#define TAMP_FLTCR_TAMPPRCH_Pos             (5U)
#define TAMP_FLTCR_TAMPPRCH_Msk             (0x3U << TAMP_FLTCR_TAMPPRCH_Pos)  /*!< 0x00000060 */
#define TAMP_FLTCR_TAMPPRCH                 TAMP_FLTCR_TAMPPRCH_Msk
#define TAMP_FLTCR_TAMPPRCH_0               (0x1U << TAMP_FLTCR_TAMPPRCH_Pos)  /*!< 0x00000020 */
#define TAMP_FLTCR_TAMPPRCH_1               (0x2U << TAMP_FLTCR_TAMPPRCH_Pos)  /*!< 0x00000040 */
#define TAMP_FLTCR_TAMPPUDIS_Pos            (7U)
#define TAMP_FLTCR_TAMPPUDIS_Msk            (0x1U << TAMP_FLTCR_TAMPPUDIS_Pos) /*!< 0x00000080 */
#define TAMP_FLTCR_TAMPPUDIS                TAMP_FLTCR_TAMPPUDIS_Msk


/********************  Bits definition for TAMP_ATCR1 register  ***************/
#define TAMP_ATCR1_TAMPAM_Pos               (0U)
#define TAMP_ATCR1_TAMPAM_Msk               (0xFFU << TAMP_ATCR1_TAMPAM_Pos)    /*!< 0x000000FF */
#define TAMP_ATCR1_TAMPAM                   TAMP_ATCR1_TAMPAM_Msk
#define TAMP_ATCR1_TAMP1AM_Pos              (0U)
#define TAMP_ATCR1_TAMP1AM_Msk              (0x1UL <<TAMP_ATCR1_TAMP1AM_Pos)    /*!< 0x00000001 */
#define TAMP_ATCR1_TAMP1AM                  TAMP_ATCR1_TAMP1AM_Msk
#define TAMP_ATCR1_TAMP2AM_Pos              (1U)
#define TAMP_ATCR1_TAMP2AM_Msk              (0x1UL <<TAMP_ATCR1_TAMP2AM_Pos)    /*!< 0x00000002 */
#define TAMP_ATCR1_TAMP2AM                  TAMP_ATCR1_TAMP2AM_Msk
#define TAMP_ATCR1_TAMP3AM_Pos              (2U)
#define TAMP_ATCR1_TAMP3AM_Msk              (0x1UL <<TAMP_ATCR1_TAMP3AM_Pos)    /*!< 0x00000004 */
#define TAMP_ATCR1_TAMP3AM                  TAMP_ATCR1_TAMP3AM_Msk
#define TAMP_ATCR1_TAMP4AM_Pos              (3U)
#define TAMP_ATCR1_TAMP4AM_Msk              (0x1UL <<TAMP_ATCR1_TAMP4AM_Pos)    /*!< 0x00000008 */
#define TAMP_ATCR1_TAMP4AM                  TAMP_ATCR1_TAMP4AM_Msk
#define TAMP_ATCR1_TAMP5AM_Pos              (4U)
#define TAMP_ATCR1_TAMP5AM_Msk              (0x1UL <<TAMP_ATCR1_TAMP5AM_Pos)    /*!< 0x00000010 */
#define TAMP_ATCR1_TAMP5AM                  TAMP_ATCR1_TAMP5AM_Msk
#define TAMP_ATCR1_TAMP6AM_Pos              (6U)
#define TAMP_ATCR1_TAMP6AM_Msk              (0x1UL <<TAMP_ATCR1_TAMP6AM_Pos)    /*!< 0x00000020 */
#define TAMP_ATCR1_TAMP6AM                  TAMP_ATCR1_TAMP6AM_Msk
#define TAMP_ATCR1_TAMP7AM_Pos              (6U)
#define TAMP_ATCR1_TAMP7AM_Msk              (0x1UL <<TAMP_ATCR1_TAMP7AM_Pos)    /*!< 0x00000040 */
#define TAMP_ATCR1_TAMP7AM                  TAMP_ATCR1_TAMP7AM_Msk
#define TAMP_ATCR1_TAMP8AM_Pos              (7U)
#define TAMP_ATCR1_TAMP8AM_Msk              (0x1UL <<TAMP_ATCR1_TAMP8AM_Pos)    /*!< 0x00000080 */
#define TAMP_ATCR1_TAMP8AM                  TAMP_ATCR1_TAMP8AM_Msk
#define TAMP_ATCR1_ATOSEL1_Pos              (8U)
#define TAMP_ATCR1_ATOSEL1_Msk              (0x3UL <<TAMP_ATCR1_ATOSEL1_Pos)    /*!< 0x00000300 */
#define TAMP_ATCR1_ATOSEL1                   TAMP_ATCR1_ATOSEL1_Msk
#define TAMP_ATCR1_ATOSEL1_0                (0x1UL << TAMP_ATCR1_ATOSEL1_Pos)   /*!< 0x00000100 */
#define TAMP_ATCR1_ATOSEL1_1                (0x2UL << TAMP_ATCR1_ATOSEL1_Pos)   /*!< 0x00000200 */
#define TAMP_ATCR1_ATOSEL2_Pos              (10U)
#define TAMP_ATCR1_ATOSEL2_Msk              (0x3UL <<TAMP_ATCR1_ATOSEL2_Pos)          /*!< 0x00000C00 */
#define TAMP_ATCR1_ATOSEL2                   TAMP_ATCR1_ATOSEL2_Msk
#define TAMP_ATCR1_ATOSEL2_0                (0x1UL << TAMP_ATCR1_ATOSEL2_Pos)   /*!< 0x00000400 */
#define TAMP_ATCR1_ATOSEL2_1                (0x2UL << TAMP_ATCR1_ATOSEL2_Pos)   /*!< 0x00000800 */
#define TAMP_ATCR1_ATOSEL3_Pos              (12U)
#define TAMP_ATCR1_ATOSEL3_Msk              (0x3UL <<TAMP_ATCR1_ATOSEL3_Pos)    /*!< 0x00003000 */
#define TAMP_ATCR1_ATOSEL3                   TAMP_ATCR1_ATOSEL3_Msk
#define TAMP_ATCR1_ATOSEL3_0                (0x1UL << TAMP_ATCR1_ATOSEL3_Pos)   /*!< 0x00001000 */
#define TAMP_ATCR1_ATOSEL3_1                (0x2UL << TAMP_ATCR1_ATOSEL3_Pos)   /*!< 0x00002000 */
#define TAMP_ATCR1_ATOSEL4_Pos              (14U)
#define TAMP_ATCR1_ATOSEL4_Msk              (0x3UL <<TAMP_ATCR1_ATOSEL4_Pos)    /*!< 0x0000C000 */
#define TAMP_ATCR1_ATOSEL4                   TAMP_ATCR1_ATOSEL4_Msk
#define TAMP_ATCR1_ATOSEL4_0                (0x1UL << TAMP_ATCR1_ATOSEL4_Pos)   /*!< 0x00004000 */
#define TAMP_ATCR1_ATOSEL4_1                (0x2UL << TAMP_ATCR1_ATOSEL4_Pos)   /*!< 0x00008000 */
#define TAMP_ATCR1_ATCKSEL_Pos              (16U)
#define TAMP_ATCR1_ATCKSEL_Msk              (0x7UL <<TAMP_ATCR1_ATCKSEL_Pos)    /*!< 0x00070000 */
#define TAMP_ATCR1_ATCKSEL                   TAMP_ATCR1_ATCKSEL_Msk
#define TAMP_ATCR1_ATCKSEL_0                (0x1UL << TAMP_ATCR1_ATCKSEL_Pos)   /*!< 0x00010000 */
#define TAMP_ATCR1_ATCKSEL_1                (0x2UL << TAMP_ATCR1_ATCKSEL_Pos)   /*!< 0x00020000 */
#define TAMP_ATCR1_ATCKSEL_2                (0x4UL << TAMP_ATCR1_ATCKSEL_Pos)   /*!< 0x00040000 */
#define TAMP_ATCR1_ATPER_Pos                (24U)
#define TAMP_ATCR1_ATPER_Msk                (0x7UL <<TAMP_ATCR1_ATPER_Pos)      /*!< 0x07000000 */
#define TAMP_ATCR1_ATPER                     TAMP_ATCR1_ATPER_Msk
#define TAMP_ATCR1_ATPER_0                  (0x1UL << TAMP_ATCR1_ATPER_Pos)     /*!< 0x01000000 */
#define TAMP_ATCR1_ATPER_1                  (0x2UL << TAMP_ATCR1_ATPER_Pos)     /*!< 0x02000000 */
#define TAMP_ATCR1_ATPER_2                  (0x4UL << TAMP_ATCR1_ATPER_Pos)     /*!< 0x04000000 */
#define TAMP_ATCR1_ATOSHARE_Pos             (30U)
#define TAMP_ATCR1_ATOSHARE_Msk             (0x1UL <<TAMP_ATCR1_ATOSHARE_Pos)   /*!< 0x40000000 */
#define TAMP_ATCR1_ATOSHARE                 TAMP_ATCR1_ATOSHARE_Msk
#define TAMP_ATCR1_FLTEN_Pos                (31U)
#define TAMP_ATCR1_FLTEN_Msk                (0x1UL <<TAMP_ATCR1_FLTEN_Pos)      /*!< 0x80000000 */
#define TAMP_ATCR1_FLTEN                    TAMP_ATCR1_FLTEN_Msk


/********************  Bits definition for TAMP_ATSEEDR register  ***************/
#define TAMP_ATSEEDR_SEED_Pos               (0U)
#define TAMP_ATSEEDR_SEED_Msk               (0xFFFFFFFFU << TAMP_ATSEEDR_SEED_Pos) /*!< 0xFFFFFFFF */
#define TAMP_ATSEEDR_SEED                   TAMP_ATSEEDR_SEED_Msk


/********************  Bits definition for TAMP_ATOR register  ***************/
#define TAMP_ATOR_PRNG_Pos                  (0U)
#define TAMP_ATOR_PRNG_Msk                  (0xFFU << TAMP_ATOR_PRNG_Pos)      /*!< 0x000000FF */
#define TAMP_ATOR_PRNG                      TAMP_ATOR_PRNG_Msk
#define TAMP_ATOR_PRNG_0                    (0x01U << TAMP_ATOR_PRNG_Pos)      /*!< 0x00000001 */
#define TAMP_ATOR_PRNG_1                    (0x02U << TAMP_ATOR_PRNG_Pos)      /*!< 0x00000002 */
#define TAMP_ATOR_PRNG_2                    (0x04U << TAMP_ATOR_PRNG_Pos)      /*!< 0x00000004 */
#define TAMP_ATOR_PRNG_3                    (0x08U << TAMP_ATOR_PRNG_Pos)      /*!< 0x00000008 */
#define TAMP_ATOR_PRNG_4                    (0x10U << TAMP_ATOR_PRNG_Pos)      /*!< 0x00000010 */
#define TAMP_ATOR_PRNG_5                    (0x20U << TAMP_ATOR_PRNG_Pos)      /*!< 0x00000020 */
#define TAMP_ATOR_PRNG_6                    (0x40U << TAMP_ATOR_PRNG_Pos)      /*!< 0x00000040 */
#define TAMP_ATOR_PRNG_7                    (0x80U << TAMP_ATOR_PRNG_Pos)      /*!< 0x00000080 */
#define TAMP_ATOR_SEEDF_Pos                 (14U)
#define TAMP_ATOR_SEEDF_Msk                 (0x1U << TAMP_ATOR_SEEDF_Pos)      /*!< 0x00004000 */
#define TAMP_ATOR_SEEDF                     TAMP_ATOR_SEEDF_Msk
#define TAMP_ATOR_INITS_Pos                 (15U)
#define TAMP_ATOR_INITS_Msk                 (0x1U << TAMP_ATOR_INITS_Pos)      /*!< 0x00008000 */
#define TAMP_ATOR_INITS                     TAMP_ATOR_INITS_Msk


/********************  Bits definition for TAMP_SMCR register  ***************/
#define TAMP_SMCR_BKPRWDPROT_Pos            (0U)
#define TAMP_SMCR_BKPRWDPROT_Msk            (0xFFU << TAMP_SMCR_BKPRWDPROT_Pos) /*!< 0x000000FF */
#define TAMP_SMCR_BKPRWDPROT                TAMP_SMCR_BKPRWDPROT_Msk
#define TAMP_SMCR_BKPRWDPROT_0              (0x01U << TAMP_SMCR_BKPRWDPROT_Pos) /*!< 0x00000001 */
#define TAMP_SMCR_BKPRWDPROT_1              (0x02U << TAMP_SMCR_BKPRWDPROT_Pos) /*!< 0x00000002 */
#define TAMP_SMCR_BKPRWDPROT_2              (0x04U << TAMP_SMCR_BKPRWDPROT_Pos) /*!< 0x00000004 */
#define TAMP_SMCR_BKPRWDPROT_3              (0x08U << TAMP_SMCR_BKPRWDPROT_Pos) /*!< 0x00000008 */
#define TAMP_SMCR_BKPRWDPROT_4              (0x10U << TAMP_SMCR_BKPRWDPROT_Pos) /*!< 0x00000010 */
#define TAMP_SMCR_BKPRWDPROT_5              (0x20U << TAMP_SMCR_BKPRWDPROT_Pos) /*!< 0x00000020 */
#define TAMP_SMCR_BKPRWDPROT_6              (0x40U << TAMP_SMCR_BKPRWDPROT_Pos) /*!< 0x00000040 */
#define TAMP_SMCR_BKPRWDPROT_7              (0x80U << TAMP_SMCR_BKPRWDPROT_Pos) /*!< 0x00000080 */
#define TAMP_SMCR_BKPWDPROT_Pos             (16U)
#define TAMP_SMCR_BKPWDPROT_Msk             (0xFFU << TAMP_SMCR_BKPWDPROT_Pos) /*!< 0x00FF0000 */
#define TAMP_SMCR_BKPWDPROT                 TAMP_SMCR_BKPWDPROT_Msk
#define TAMP_SMCR_BKPWDPROT_0               (0x01U << TAMP_SMCR_BKPWDPROT_Pos) /*!< 0x00010000 */
#define TAMP_SMCR_BKPWDPROT_1               (0x02U << TAMP_SMCR_BKPWDPROT_Pos) /*!< 0x00020000 */
#define TAMP_SMCR_BKPWDPROT_2               (0x04U << TAMP_SMCR_BKPWDPROT_Pos) /*!< 0x00040000 */
#define TAMP_SMCR_BKPWDPROT_3               (0x08U << TAMP_SMCR_BKPWDPROT_Pos) /*!< 0x00080000 */
#define TAMP_SMCR_BKPWDPROT_4               (0x10U << TAMP_SMCR_BKPWDPROT_Pos) /*!< 0x00100000 */
#define TAMP_SMCR_BKPWDPROT_5               (0x20U << TAMP_SMCR_BKPWDPROT_Pos) /*!< 0x00200000 */
#define TAMP_SMCR_BKPWDPROT_6               (0x40U << TAMP_SMCR_BKPWDPROT_Pos) /*!< 0x00400000 */
#define TAMP_SMCR_BKPWDPROT_7               (0x80U << TAMP_SMCR_BKPWDPROT_Pos) /*!< 0x00800000 */
#define TAMP_SMCR_TAMPDPROT_Pos             (31U)
#define TAMP_SMCR_TAMPDPROT_Msk             (0x1U << TAMP_SMCR_TAMPDPROT_Pos)  /*!< 0x80000000 */
#define TAMP_SMCR_TAMPDPROT                 TAMP_SMCR_TAMPDPROT_Msk


/********************  Bits definition for TAMP_IER register  ***************/
#define TAMP_IER_TAMPIE_Pos                 (0U)
#define TAMP_IER_TAMPIE_Msk                 (0x7U << TAMP_IER_TAMPIE_Pos)     /*!< 0x000000FF */
#define TAMP_IER_TAMPIE                     TAMP_IER_TAMPIE_Msk
#define TAMP_IER_TAMP1IE_Pos                (0U)
#define TAMP_IER_TAMP1IE_Msk                (0x1U << TAMP_IER_TAMP1IE_Pos)     /*!< 0x00000001 */
#define TAMP_IER_TAMP1IE                    TAMP_IER_TAMP1IE_Msk
#define TAMP_IER_TAMP2IE_Pos                (1U)
#define TAMP_IER_TAMP2IE_Msk                (0x1U << TAMP_IER_TAMP2IE_Pos)     /*!< 0x00000002 */
#define TAMP_IER_TAMP2IE                    TAMP_IER_TAMP2IE_Msk
#define TAMP_IER_TAMP3IE_Pos                (2U)
#define TAMP_IER_TAMP3IE_Msk                (0x1U << TAMP_IER_TAMP3IE_Pos)     /*!< 0x00000004 */
#define TAMP_IER_TAMP3IE                    TAMP_IER_TAMP3IE_Msk
#define TAMP_IER_ITAMPIE_Pos                (16U)
#define TAMP_IER_ITAMPIE_Msk                (0x9FU << TAMP_IER_ITAMPIE_Pos)  /*!< 0xFFFF0000 */
#define TAMP_IER_ITAMPIE                    TAMP_IER_ITAMPIE_Msk
#define TAMP_IER_ITAMP1IE_Pos               (16U)
#define TAMP_IER_ITAMP1IE_Msk               (0x1U << TAMP_IER_ITAMP1IE_Pos)    /*!< 0x00010000 */
#define TAMP_IER_ITAMP1IE                   TAMP_IER_ITAMP1IE_Msk
#define TAMP_IER_ITAMP2IE_Pos               (17U)
#define TAMP_IER_ITAMP2IE_Msk               (0x1U << TAMP_IER_ITAMP2IE_Pos)    /*!< 0x00020000 */
#define TAMP_IER_ITAMP2IE                   TAMP_IER_ITAMP2IE_Msk
#define TAMP_IER_ITAMP3IE_Pos               (18U)
#define TAMP_IER_ITAMP3IE_Msk               (0x1U << TAMP_IER_ITAMP3IE_Pos)    /*!< 0x00040000 */
#define TAMP_IER_ITAMP3IE                   TAMP_IER_ITAMP3IE_Msk
#define TAMP_IER_ITAMP4IE_Pos               (19U)
#define TAMP_IER_ITAMP4IE_Msk               (0x1U << TAMP_IER_ITAMP4IE_Pos)    /*!< 0x00080000 */
#define TAMP_IER_ITAMP4IE                   TAMP_IER_ITAMP4IE_Msk
#define TAMP_IER_ITAMP5IE_Pos               (20U)
#define TAMP_IER_ITAMP5IE_Msk               (0x1U << TAMP_IER_ITAMP5IE_Pos)    /*!< 0x00100000 */
#define TAMP_IER_ITAMP5IE                   TAMP_IER_ITAMP5IE_Msk
#define TAMP_IER_ITAMP8IE_Pos               (23U)
#define TAMP_IER_ITAMP8IE_Msk               (0x1U << TAMP_IER_ITAMP8IE_Pos)    /*!< 0x00800000 */
#define TAMP_IER_ITAMP8IE                   TAMP_IER_ITAMP8IE_Msk


/********************  Bits definition for TAMP_SR register  ***************/
#define TAMP_SR_TAMPF_Pos                   (0U)
#define TAMP_SR_TAMPF_Msk                   (0x7U << TAMP_SR_TAMPF_Pos)       /*!< 0x000000FF */
#define TAMP_SR_TAMPF                       TAMP_SR_TAMPF_Msk
#define TAMP_SR_TAMP1F_Pos                  (0U)
#define TAMP_SR_TAMP1F_Msk                  (0x1U << TAMP_SR_TAMP1F_Pos)       /*!< 0x00000001 */
#define TAMP_SR_TAMP1F                      TAMP_SR_TAMP1F_Msk
#define TAMP_SR_TAMP2F_Pos                  (1U)
#define TAMP_SR_TAMP2F_Msk                  (0x1U << TAMP_SR_TAMP2F_Pos)       /*!< 0x00000002 */
#define TAMP_SR_TAMP2F                      TAMP_SR_TAMP2F_Msk
#define TAMP_SR_TAMP3F_Pos                  (2U)
#define TAMP_SR_TAMP3F_Msk                  (0x1U << TAMP_SR_TAMP3F_Pos)       /*!< 0x00000004 */
#define TAMP_SR_TAMP3F                      TAMP_SR_TAMP3F_Msk
#define TAMP_SR_ITAMPF_Pos                  (16U)
#define TAMP_SR_ITAMPF_Msk                  (0x9FU << TAMP_SR_ITAMPF_Pos)      /*!< 0xFFFF0000 */
#define TAMP_SR_ITAMPF                      TAMP_SR_ITAMPF_Msk
#define TAMP_SR_ITAMP1F_Pos                 (16U)
#define TAMP_SR_ITAMP1F_Msk                 (0x1U << TAMP_SR_ITAMP1F_Pos)      /*!< 0x00010000 */
#define TAMP_SR_ITAMP1F                     TAMP_SR_ITAMP1F_Msk
#define TAMP_SR_ITAMP2F_Pos                 (17U)
#define TAMP_SR_ITAMP2F_Msk                 (0x1U << TAMP_SR_ITAMP2F_Pos)      /*!< 0x00020000 */
#define TAMP_SR_ITAMP2F                     TAMP_SR_ITAMP2F_Msk
#define TAMP_SR_ITAMP3F_Pos                 (18U)
#define TAMP_SR_ITAMP3F_Msk                 (0x1U << TAMP_SR_ITAMP3F_Pos)      /*!< 0x00040000 */
#define TAMP_SR_ITAMP3F                     TAMP_SR_ITAMP3F_Msk
#define TAMP_SR_ITAMP4F_Pos                 (19U)
#define TAMP_SR_ITAMP4F_Msk                 (0x1U << TAMP_SR_ITAMP4F_Pos)      /*!< 0x00080000 */
#define TAMP_SR_ITAMP4F                     TAMP_SR_ITAMP4F_Msk
#define TAMP_SR_ITAMP5F_Pos                 (20U)
#define TAMP_SR_ITAMP5F_Msk                 (0x1U << TAMP_SR_ITAMP5F_Pos)      /*!< 0x00100000 */
#define TAMP_SR_ITAMP5F                     TAMP_SR_ITAMP5F_Msk
#define TAMP_SR_ITAMP8F_Pos                 (23U)
#define TAMP_SR_ITAMP8F_Msk                 (0x1U << TAMP_SR_ITAMP8F_Pos)      /*!< 0x00800000 */
#define TAMP_SR_ITAMP8F                     TAMP_SR_ITAMP8F_Msk


/********************  Bits definition for TAMP_MISR register  ***************/
#define TAMP_MISR_TAMPMF_Pos                (0U)
#define TAMP_MISR_TAMPMF_Msk                (0x7U << TAMP_MISR_TAMPMF_Pos)    /*!< 0x000000FF */
#define TAMP_MISR_TAMPMF                    TAMP_MISR_TAMPMF_Msk
#define TAMP_MISR_TAMP1MF_Pos               (0U)
#define TAMP_MISR_TAMP1MF_Msk               (0x1U << TAMP_MISR_TAMP1MF_Pos)    /*!< 0x00000001 */
#define TAMP_MISR_TAMP1MF                   TAMP_MISR_TAMP1MF_Msk
#define TAMP_MISR_TAMP2MF_Pos               (1U)
#define TAMP_MISR_TAMP2MF_Msk               (0x1U << TAMP_MISR_TAMP2MF_Pos)    /*!< 0x00000002 */
#define TAMP_MISR_TAMP2MF                   TAMP_MISR_TAMP2MF_Msk
#define TAMP_MISR_TAMP3MF_Pos               (2U)
#define TAMP_MISR_TAMP3MF_Msk               (0x1U << TAMP_MISR_TAMP3MF_Pos)    /*!< 0x00000004 */
#define TAMP_MISR_TAMP3MF                   TAMP_MISR_TAMP3MF_Msk
#define TAMP_MISR_ITAMPMF_Pos               (16U)
#define TAMP_MISR_ITAMPMF_Msk               (0x9FU << TAMP_MISR_ITAMPMF_Pos)   /*!< 0xFFFF0000 */
#define TAMP_MISR_ITAMPMF                   TAMP_MISR_ITAMPMF_Msk
#define TAMP_MISR_ITAMP1MF_Pos              (16U)
#define TAMP_MISR_ITAMP1MF_Msk              (0x1U << TAMP_MISR_ITAMP1MF_Pos)   /*!< 0x00010000 */
#define TAMP_MISR_ITAMP1MF                  TAMP_MISR_ITAMP1MF_Msk
#define TAMP_MISR_ITAMP2MF_Pos              (17U)
#define TAMP_MISR_ITAMP2MF_Msk              (0x1U << TAMP_MISR_ITAMP2MF_Pos)   /*!< 0x00020000 */
#define TAMP_MISR_ITAMP2MF                  TAMP_MISR_ITAMP2MF_Msk
#define TAMP_MISR_ITAMP3MF_Pos              (18U)
#define TAMP_MISR_ITAMP3MF_Msk              (0x1U << TAMP_MISR_ITAMP3MF_Pos)   /*!< 0x00040000 */
#define TAMP_MISR_ITAMP3MF                  TAMP_MISR_ITAMP3MF_Msk
#define TAMP_MISR_ITAMP4MF_Pos              (19U)
#define TAMP_MISR_ITAMP4MF_Msk              (0x1U << TAMP_MISR_ITAMP4MF_Pos)   /*!< 0x00080000 */
#define TAMP_MISR_ITAMP4MF                  TAMP_MISR_ITAMP4MF_Msk
#define TAMP_MISR_ITAMP5MF_Pos              (20U)
#define TAMP_MISR_ITAMP5MF_Msk              (0x1U << TAMP_MISR_ITAMP5MF_Pos)   /*!< 0x00100000 */
#define TAMP_MISR_ITAMP5MF                  TAMP_MISR_ITAMP5MF_Msk
#define TAMP_MISR_ITAMP8MF_Pos              (23U)
#define TAMP_MISR_ITAMP8MF_Msk              (0x1U << TAMP_MISR_ITAMP8MF_Pos)   /*!< 0x00800000 */
#define TAMP_MISR_ITAMP8MF                  TAMP_MISR_ITAMP8MF_Msk


/********************  Bits definition for TAMP_SMISR register  ***************/
#define TAMP_SMISR_TAMPMF_Pos               (0U)
#define TAMP_SMISR_TAMPMF_Msk               (0x7U << TAMP_SMISR_TAMPMF_Pos)   /*!< 0x000000FF */
#define TAMP_SMISR_TAMPMF                   TAMP_SMISR_TAMPMF_Msk
#define TAMP_SMISR_TAMP1MF_Pos              (0U)
#define TAMP_SMISR_TAMP1MF_Msk              (0x1U << TAMP_SMISR_TAMP1MF_Pos)   /*!< 0x00000001 */
#define TAMP_SMISR_TAMP1MF                  TAMP_SMISR_TAMP1MF_Msk
#define TAMP_SMISR_TAMP2MF_Pos              (1U)
#define TAMP_SMISR_TAMP2MF_Msk              (0x1U << TAMP_SMISR_TAMP2MF_Pos)   /*!< 0x00000002 */
#define TAMP_SMISR_TAMP2MF                  TAMP_SMISR_TAMP2MF_Msk
#define TAMP_SMISR_TAMP3MF_Pos              (2U)
#define TAMP_SMISR_TAMP3MF_Msk              (0x1U << TAMP_SMISR_TAMP3MF_Pos)   /*!< 0x00000004 */
#define TAMP_SMISR_TAMP3MF                  TAMP_SMISR_TAMP3MF_Msk
#define TAMP_SMISR_ITAMPMF_Pos              (16U)
#define TAMP_SMISR_ITAMPMF_Msk              (0x9FU << TAMP_SMISR_ITAMPMF_Pos) /*!< 0xFFFF0000 */
#define TAMP_SMISR_ITAMPMF                  TAMP_SMISR_ITAMPMF_Msk
#define TAMP_SMISR_ITAMP1MF_Pos             (16U)
#define TAMP_SMISR_ITAMP1MF_Msk             (0x1U << TAMP_SMISR_ITAMP1MF_Pos)  /*!< 0x00010000 */
#define TAMP_SMISR_ITAMP1MF                 TAMP_SMISR_ITAMP1MF_Msk
#define TAMP_SMISR_ITAMP2MF_Pos             (17U)
#define TAMP_SMISR_ITAMP2MF_Msk             (0x1U << TAMP_SMISR_ITAMP2MF_Pos)  /*!< 0x00020000 */
#define TAMP_SMISR_ITAMP2MF                 TAMP_SMISR_ITAMP2MF_Msk
#define TAMP_SMISR_ITAMP3MF_Pos             (18U)
#define TAMP_SMISR_ITAMP3MF_Msk             (0x1U << TAMP_SMISR_ITAMP3MF_Pos)  /*!< 0x00040000 */
#define TAMP_SMISR_ITAMP3MF                 TAMP_SMISR_ITAMP3MF_Msk
#define TAMP_SMISR_ITAMP4MF_Pos             (19U)
#define TAMP_SMISR_ITAMP4MF_Msk             (0x1U << TAMP_SMISR_ITAMP4MF_Pos)  /*!< 0x00080000 */
#define TAMP_SMISR_ITAMP4MF                 TAMP_SMISR_ITAMP4MF_Msk
#define TAMP_SMISR_ITAMP5MF_Pos             (20U)
#define TAMP_SMISR_ITAMP5MF_Msk             (0x1U << TAMP_SMISR_ITAMP5MF_Pos)  /*!< 0x00100000 */
#define TAMP_SMISR_ITAMP5MF                 TAMP_SMISR_ITAMP5MF_Msk
#define TAMP_SMISR_ITAMP8MF_Pos             (23U)
#define TAMP_SMISR_ITAMP8MF_Msk             (0x1U << TAMP_SMISR_ITAMP8MF_Pos)  /*!< 0x00800000 */
#define TAMP_SMISR_ITAMP8MF                 TAMP_SMISR_ITAMP8MF_Msk


/********************  Bits definition for TAMP_SCR register  ***************/
#define TAMP_SCR_CTAMPF_Pos                 (0U)
#define TAMP_SCR_CTAMPF_Msk                 (0x7U << TAMP_SCR_CTAMPF_Pos)     /*!< 0x000000FF */
#define TAMP_SCR_CTAMPF                     TAMP_SCR_CTAMPF_Msk
#define TAMP_SCR_CTAMP1F_Pos                (0U)
#define TAMP_SCR_CTAMP1F_Msk                (0x1U << TAMP_SCR_CTAMP1F_Pos)     /*!< 0x00000001 */
#define TAMP_SCR_CTAMP1F                    TAMP_SCR_CTAMP1F_Msk
#define TAMP_SCR_CTAMP2F_Pos                (1U)
#define TAMP_SCR_CTAMP2F_Msk                (0x1U << TAMP_SCR_CTAMP2F_Pos)     /*!< 0x00000002 */
#define TAMP_SCR_CTAMP2F                    TAMP_SCR_CTAMP2F_Msk
#define TAMP_SCR_CTAMP3F_Pos                (2U)
#define TAMP_SCR_CTAMP3F_Msk                (0x1U << TAMP_SCR_CTAMP3F_Pos)     /*!< 0x00000004 */
#define TAMP_SCR_CTAMP3F                    TAMP_SCR_CTAMP3F_Msk
#define TAMP_SCR_CITAMPF_Pos                (16U)
#define TAMP_SCR_CITAMPF_Msk                (0x9FU << TAMP_SCR_CITAMPF_Pos)    /*!< 0xFFFF0000 */
#define TAMP_SCR_CITAMPF                    TAMP_SCR_CITAMPF_Msk
#define TAMP_SCR_CITAMP1F_Pos               (16U)
#define TAMP_SCR_CITAMP1F_Msk               (0x1U << TAMP_SCR_CITAMP1F_Pos)    /*!< 0x00010000 */
#define TAMP_SCR_CITAMP1F                   TAMP_SCR_CITAMP1F_Msk
#define TAMP_SCR_CITAMP2F_Pos               (17U)
#define TAMP_SCR_CITAMP2F_Msk               (0x1U << TAMP_SCR_CITAMP2F_Pos)    /*!< 0x00020000 */
#define TAMP_SCR_CITAMP2F                   TAMP_SCR_CITAMP2F_Msk
#define TAMP_SCR_CITAMP3F_Pos               (18U)
#define TAMP_SCR_CITAMP3F_Msk               (0x1U << TAMP_SCR_CITAMP3F_Pos)    /*!< 0x00040000 */
#define TAMP_SCR_CITAMP3F                   TAMP_SCR_CITAMP3F_Msk
#define TAMP_SCR_CITAMP4F_Pos               (19U)
#define TAMP_SCR_CITAMP4F_Msk               (0x1U << TAMP_SCR_CITAMP4F_Pos)    /*!< 0x00080000 */
#define TAMP_SCR_CITAMP4F                   TAMP_SCR_CITAMP4F_Msk
#define TAMP_SCR_CITAMP5F_Pos               (20U)
#define TAMP_SCR_CITAMP5F_Msk               (0x1U << TAMP_SCR_CITAMP5F_Pos)    /*!< 0x00100000 */
#define TAMP_SCR_CITAMP5F                   TAMP_SCR_CITAMP5F_Msk
#define TAMP_SCR_CITAMP8F_Pos               (23U)
#define TAMP_SCR_CITAMP8F_Msk               (0x1U << TAMP_SCR_CITAMP8F_Pos)    /*!< 0x00800000 */
#define TAMP_SCR_CITAMP8F                   TAMP_SCR_CITAMP8F_Msk


/********************  Bits definition for TAMP_OR register (TAMP_CFGR)  ****************/
#define TAMP_CFGR_OUT3_RMP_Pos              (0U)
#define TAMP_CFGR_OUT3_RMP_Msk              (0x1U << TAMP_CFGR_OUT3_RMP_Pos)       /*!< 0x00000001 */
#define TAMP_CFGR_OUT3_RMP                  TAMP_CFGR_OUT3_RMP_Msk


/********************  Bits definition for TAMP_COUNTR register  ****************/
#define TAMP_COUNTR_COUNT_Pos               (0U)
#define TAMP_COUNTR_COUNT_Msk               (0xFFFFFFFFU << TAMP_COUNTR_COUNT_Pos) /*!< 0xFFFFFFFF */
#define TAMP_COUNTR_COUNT                   TAMP_COUNTR_COUNT_Msk


/********************  Bits definition for TAMP_BKPxR register  ****************/
#define TAMP_BKP0R_Pos                      (0U)
#define TAMP_BKP0R_Msk                      (0xFFFFFFFFU << TAMP_BKP0R_Pos)    /*!< 0xFFFFFFFF */
#define TAMP_BKP0R                          TAMP_BKP0R_Msk
#define TAMP_BKP1R_Pos                      (0U)
#define TAMP_BKP1R_Msk                      (0xFFFFFFFFU << TAMP_BKP1R_Pos)    /*!< 0xFFFFFFFF */
#define TAMP_BKP1R                          TAMP_BKP1R_Msk
#define TAMP_BKP2R_Pos                      (0U)
#define TAMP_BKP2R_Msk                      (0xFFFFFFFFU << TAMP_BKP2R_Pos)    /*!< 0xFFFFFFFF */
#define TAMP_BKP2R                          TAMP_BKP2R_Msk
#define TAMP_BKP3R_Pos                      (0U)
#define TAMP_BKP3R_Msk                      (0xFFFFFFFFU << TAMP_BKP3R_Pos)    /*!< 0xFFFFFFFF */
#define TAMP_BKP3R                          TAMP_BKP3R_Msk
#define TAMP_BKP4R_Pos                      (0U)
#define TAMP_BKP4R_Msk                      (0xFFFFFFFFU << TAMP_BKP4R_Pos)    /*!< 0xFFFFFFFF */
#define TAMP_BKP4R                          TAMP_BKP4R_Msk
#define TAMP_BKP5R_Pos                      (0U)
#define TAMP_BKP5R_Msk                      (0xFFFFFFFFU << TAMP_BKP5R_Pos)    /*!< 0xFFFFFFFF */
#define TAMP_BKP5R                          TAMP_BKP5R_Msk
#define TAMP_BKP6R_Pos                      (0U)
#define TAMP_BKP6R_Msk                      (0xFFFFFFFFU << TAMP_BKP6R_Pos)    /*!< 0xFFFFFFFF */
#define TAMP_BKP6R                          TAMP_BKP6R_Msk
#define TAMP_BKP7R_Pos                      (0U)
#define TAMP_BKP7R_Msk                      (0xFFFFFFFFU << TAMP_BKP7R_Pos)    /*!< 0xFFFFFFFF */
#define TAMP_BKP7R                          TAMP_BKP7R_Msk
#define TAMP_BKP8R_Pos                      (0U)
#define TAMP_BKP8R_Msk                      (0xFFFFFFFFU << TAMP_BKP8R_Pos)    /*!< 0xFFFFFFFF */
#define TAMP_BKP8R                          TAMP_BKP8R_Msk
#define TAMP_BKP9R_Pos                      (0U)
#define TAMP_BKP9R_Msk                      (0xFFFFFFFFU << TAMP_BKP9R_Pos)    /*!< 0xFFFFFFFF */
#define TAMP_BKP9R                          TAMP_BKP9R_Msk
#define TAMP_BKP10R_Pos                     (0U)
#define TAMP_BKP10R_Msk                     (0xFFFFFFFFU << TAMP_BKP10R_Pos)   /*!< 0xFFFFFFFF */
#define TAMP_BKP10R                         TAMP_BKP10R_Msk
#define TAMP_BKP11R_Pos                     (0U)
#define TAMP_BKP11R_Msk                     (0xFFFFFFFFU << TAMP_BKP11R_Pos)   /*!< 0xFFFFFFFF */
#define TAMP_BKP11R                         TAMP_BKP11R_Msk
#define TAMP_BKP12R_Pos                     (0U)
#define TAMP_BKP12R_Msk                     (0xFFFFFFFFU << TAMP_BKP12R_Pos)   /*!< 0xFFFFFFFF */
#define TAMP_BKP12R                         TAMP_BKP12R_Msk
#define TAMP_BKP13R_Pos                     (0U)
#define TAMP_BKP13R_Msk                     (0xFFFFFFFFU << TAMP_BKP13R_Pos)   /*!< 0xFFFFFFFF */
#define TAMP_BKP13R                         TAMP_BKP13R_Msk
#define TAMP_BKP14R_Pos                     (0U)
#define TAMP_BKP14R_Msk                     (0xFFFFFFFFU << TAMP_BKP14R_Pos)   /*!< 0xFFFFFFFF */
#define TAMP_BKP14R                         TAMP_BKP14R_Msk
#define TAMP_BKP15R_Pos                     (0U)
#define TAMP_BKP15R_Msk                     (0xFFFFFFFFU << TAMP_BKP15R_Pos)   /*!< 0xFFFFFFFF */
#define TAMP_BKP15R                         TAMP_BKP15R_Msk
#define TAMP_BKP16R_Pos                     (0U)
#define TAMP_BKP16R_Msk                     (0xFFFFFFFFU << TAMP_BKP16R_Pos)   /*!< 0xFFFFFFFF */
#define TAMP_BKP16R                         TAMP_BKP16R_Msk
#define TAMP_BKP17R_Pos                     (0U)
#define TAMP_BKP17R_Msk                     (0xFFFFFFFFU << TAMP_BKP17R_Pos)   /*!< 0xFFFFFFFF */
#define TAMP_BKP17R                         TAMP_BKP17R_Msk
#define TAMP_BKP18R_Pos                     (0U)
#define TAMP_BKP18R_Msk                     (0xFFFFFFFFU << TAMP_BKP18R_Pos)   /*!< 0xFFFFFFFF */
#define TAMP_BKP18R                         TAMP_BKP18R_Msk
#define TAMP_BKP19R_Pos                     (0U)
#define TAMP_BKP19R_Msk                     (0xFFFFFFFFU << TAMP_BKP19R_Pos)   /*!< 0xFFFFFFFF */
#define TAMP_BKP19R                         TAMP_BKP19R_Msk
#define TAMP_BKP20R_Pos                     (0U)
#define TAMP_BKP20R_Msk                     (0xFFFFFFFFU << TAMP_BKP20R_Pos)   /*!< 0xFFFFFFFF */
#define TAMP_BKP20R                         TAMP_BKP20R_Msk
#define TAMP_BKP21R_Pos                     (0U)
#define TAMP_BKP21R_Msk                     (0xFFFFFFFFU << TAMP_BKP21R_Pos)   /*!< 0xFFFFFFFF */
#define TAMP_BKP21R                         TAMP_BKP21R_Msk
#define TAMP_BKP22R_Pos                     (0U)
#define TAMP_BKP22R_Msk                     (0xFFFFFFFFU << TAMP_BKP22R_Pos)   /*!< 0xFFFFFFFF */
#define TAMP_BKP22R                         TAMP_BKP22R_Msk
#define TAMP_BKP23R_Pos                     (0U)
#define TAMP_BKP23R_Msk                     (0xFFFFFFFFU << TAMP_BKP23R_Pos)   /*!< 0xFFFFFFFF */
#define TAMP_BKP23R                         TAMP_BKP23R_Msk
#define TAMP_BKP24R_Pos                     (0U)
#define TAMP_BKP24R_Msk                     (0xFFFFFFFFU << TAMP_BKP24R_Pos)   /*!< 0xFFFFFFFF */
#define TAMP_BKP24R                         TAMP_BKP24R_Msk
#define TAMP_BKP25R_Pos                     (0U)
#define TAMP_BKP25R_Msk                     (0xFFFFFFFFU << TAMP_BKP25R_Pos)   /*!< 0xFFFFFFFF */
#define TAMP_BKP25R                         TAMP_BKP25R_Msk
#define TAMP_BKP26R_Pos                     (0U)
#define TAMP_BKP26R_Msk                     (0xFFFFFFFFU << TAMP_BKP26R_Pos)   /*!< 0xFFFFFFFF */
#define TAMP_BKP26R                         TAMP_BKP26R_Msk
#define TAMP_BKP27R_Pos                     (0U)
#define TAMP_BKP27R_Msk                     (0xFFFFFFFFU << TAMP_BKP27R_Pos)   /*!< 0xFFFFFFFF */
#define TAMP_BKP27R                         TAMP_BKP27R_Msk
#define TAMP_BKP28R_Pos                     (0U)
#define TAMP_BKP28R_Msk                     (0xFFFFFFFFU << TAMP_BKP28R_Pos)   /*!< 0xFFFFFFFF */
#define TAMP_BKP28R                         TAMP_BKP28R_Msk
#define TAMP_BKP29R_Pos                     (0U)
#define TAMP_BKP29R_Msk                     (0xFFFFFFFFU << TAMP_BKP29R_Pos)   /*!< 0xFFFFFFFF */
#define TAMP_BKP29R                         TAMP_BKP29R_Msk
#define TAMP_BKP30R_Pos                     (0U)
#define TAMP_BKP30R_Msk                     (0xFFFFFFFFU << TAMP_BKP30R_Pos)   /*!< 0xFFFFFFFF */
#define TAMP_BKP30R                         TAMP_BKP30R_Msk
#define TAMP_BKP31R_Pos                     (0U)
#define TAMP_BKP31R_Msk                     (0xFFFFFFFFU << TAMP_BKP31R_Pos)   /*!< 0xFFFFFFFF */
#define TAMP_BKP31R                         TAMP_BKP31R_Msk


/********************  Bits definition for TAMP_HWCFGR2 register  *************/
#define TAMP_HWCFGR2_TRUST_ZONE_Pos         (8U)
#define TAMP_HWCFGR2_TRUST_ZONE_Msk         (0xFU << TAMP_HWCFGR2_TRUST_ZONE_Pos) /*!< 0x00000F00 */
#define TAMP_HWCFGR2_TRUST_ZONE             TAMP_HWCFGR2_TRUST_ZONE_Msk
#define TAMP_HWCFGR2_TRUST_ZONE_0           (0x1U << TAMP_HWCFGR2_TRUST_ZONE_Pos) /*!< 0x00000100 */
#define TAMP_HWCFGR2_TRUST_ZONE_1           (0x2U << TAMP_HWCFGR2_TRUST_ZONE_Pos) /*!< 0x00000200 */
#define TAMP_HWCFGR2_TRUST_ZONE_2           (0x4U << TAMP_HWCFGR2_TRUST_ZONE_Pos) /*!< 0x00000400 */
#define TAMP_HWCFGR2_TRUST_ZONE_3           (0x8U << TAMP_HWCFGR2_TRUST_ZONE_Pos) /*!< 0x00000800 */

#define TAMP_HWCFGR2_OPTIONREG_OUT_Pos      (0U)
#define TAMP_HWCFGR2_OPTIONREG_OUT_Msk      (0xFFU << TAMP_HWCFGR2_OPTIONREG_OUT_Pos) /*!< 0x000000FF */
#define TAMP_HWCFGR2_OPTIONREG_OUT          TAMP_HWCFGR2_OPTIONREG_OUT_Msk
#define TAMP_HWCFGR2_OPTIONREG_OUT_0        (0x01U << TAMP_HWCFGR2_OPTIONREG_OUT_Pos) /*!< 0x00000001 */
#define TAMP_HWCFGR2_OPTIONREG_OUT_1        (0x02U << TAMP_HWCFGR2_OPTIONREG_OUT_Pos) /*!< 0x00000002 */
#define TAMP_HWCFGR2_OPTIONREG_OUT_2        (0x04U << TAMP_HWCFGR2_OPTIONREG_OUT_Pos) /*!< 0x00000004 */
#define TAMP_HWCFGR2_OPTIONREG_OUT_3        (0x08U << TAMP_HWCFGR2_OPTIONREG_OUT_Pos) /*!< 0x00000008 */
#define TAMP_HWCFGR2_OPTIONREG_OUT_4        (0x10U << TAMP_HWCFGR2_OPTIONREG_OUT_Pos) /*!< 0x00000010 */
#define TAMP_HWCFGR2_OPTIONREG_OUT_5        (0x20U << TAMP_HWCFGR2_OPTIONREG_OUT_Pos) /*!< 0x00000020 */
#define TAMP_HWCFGR2_OPTIONREG_OUT_6        (0x40U << TAMP_HWCFGR2_OPTIONREG_OUT_Pos) /*!< 0x00000040 */
#define TAMP_HWCFGR2_OPTIONREG_OUT_7        (0x80U << TAMP_HWCFGR2_OPTIONREG_OUT_Pos) /*!< 0x00000080 */

/********************  Bits definition for TAMP_HWCFGR1 register  *************/
#define TAMP_HWCFGR1_INT_TAMPER_Pos         (16U)
#define TAMP_HWCFGR1_INT_TAMPER_Msk         (0xFFFFU << TAMP_HWCFGR1_INT_TAMPER_Pos) /*!< 0xFFFF0000 */
#define TAMP_HWCFGR1_INT_TAMPER             TAMP_HWCFGR1_INT_TAMPER_Msk
#define TAMP_HWCFGR1_INT_TAMPER_0           (0x0001U << TAMP_HWCFGR1_INT_TAMPER_Pos) /*!< 0x00010000 */
#define TAMP_HWCFGR1_INT_TAMPER_1           (0x0002U << TAMP_HWCFGR1_INT_TAMPER_Pos) /*!< 0x00020000 */
#define TAMP_HWCFGR1_INT_TAMPER_2           (0x0004U << TAMP_HWCFGR1_INT_TAMPER_Pos) /*!< 0x00040000 */
#define TAMP_HWCFGR1_INT_TAMPER_3           (0x0008U << TAMP_HWCFGR1_INT_TAMPER_Pos) /*!< 0x00080000 */
#define TAMP_HWCFGR1_INT_TAMPER_4           (0x0010U << TAMP_HWCFGR1_INT_TAMPER_Pos) /*!< 0x00100000 */
#define TAMP_HWCFGR1_INT_TAMPER_5           (0x0020U << TAMP_HWCFGR1_INT_TAMPER_Pos) /*!< 0x00200000 */
#define TAMP_HWCFGR1_INT_TAMPER_6           (0x0040U << TAMP_HWCFGR1_INT_TAMPER_Pos) /*!< 0x00400000 */
#define TAMP_HWCFGR1_INT_TAMPER_7           (0x0080U << TAMP_HWCFGR1_INT_TAMPER_Pos) /*!< 0x00800000 */
#define TAMP_HWCFGR1_INT_TAMPER_8           (0x0100U << TAMP_HWCFGR1_INT_TAMPER_Pos) /*!< 0x01000000 */
#define TAMP_HWCFGR1_INT_TAMPER_9           (0x0200U << TAMP_HWCFGR1_INT_TAMPER_Pos) /*!< 0x02000000 */
#define TAMP_HWCFGR1_INT_TAMPER_10          (0x0400U << TAMP_HWCFGR1_INT_TAMPER_Pos) /*!< 0x04000000 */
#define TAMP_HWCFGR1_INT_TAMPER_11          (0x0800U << TAMP_HWCFGR1_INT_TAMPER_Pos) /*!< 0x08000000 */
#define TAMP_HWCFGR1_INT_TAMPER_12          (0x1000U << TAMP_HWCFGR1_INT_TAMPER_Pos) /*!< 0x10000000 */
#define TAMP_HWCFGR1_INT_TAMPER_13          (0x2000U << TAMP_HWCFGR1_INT_TAMPER_Pos) /*!< 0x20000000 */
#define TAMP_HWCFGR1_INT_TAMPER_14          (0x4000U << TAMP_HWCFGR1_INT_TAMPER_Pos) /*!< 0x40000000 */
#define TAMP_HWCFGR1_INT_TAMPER_15          (0x8000U << TAMP_HWCFGR1_INT_TAMPER_Pos) /*!< 0x80000000 */

#define TAMP_HWCFGR1_ACTIVE_TAMPER_Pos      (12U)
#define TAMP_HWCFGR1_ACTIVE_TAMPER_Msk      (0xFU << TAMP_HWCFGR1_ACTIVE_TAMPER_Pos) /*!< 0x0000F000 */
#define TAMP_HWCFGR1_ACTIVE_TAMPER          TAMP_HWCFGR1_ACTIVE_TAMPER_Msk
#define TAMP_HWCFGR1_ACTIVE_TAMPER_0        (0x1U << TAMP_HWCFGR1_ACTIVE_TAMPER_Pos) /*!< 0x00001000 */
#define TAMP_HWCFGR1_ACTIVE_TAMPER_1        (0x2U << TAMP_HWCFGR1_ACTIVE_TAMPER_Pos) /*!< 0x00002000 */
#define TAMP_HWCFGR1_ACTIVE_TAMPER_2        (0x4U << TAMP_HWCFGR1_ACTIVE_TAMPER_Pos) /*!< 0x00004000 */
#define TAMP_HWCFGR1_ACTIVE_TAMPER_3        (0x8U << TAMP_HWCFGR1_ACTIVE_TAMPER_Pos) /*!< 0x00008000 */

#define TAMP_HWCFGR1_TAMPER_Pos             (8U)
#define TAMP_HWCFGR1_TAMPER_Msk             (0xFU << TAMP_HWCFGR1_TAMPER_Pos)  /*!< 0x00000F00 */
#define TAMP_HWCFGR1_TAMPER                 TAMP_HWCFGR1_TAMPER_Msk
#define TAMP_HWCFGR1_TAMPER_0               (0x1U << TAMP_HWCFGR1_TAMPER_Pos)  /*!< 0x00000100 */
#define TAMP_HWCFGR1_TAMPER_1               (0x2U << TAMP_HWCFGR1_TAMPER_Pos)  /*!< 0x00000200 */
#define TAMP_HWCFGR1_TAMPER_2               (0x4U << TAMP_HWCFGR1_TAMPER_Pos)  /*!< 0x00000400 */
#define TAMP_HWCFGR1_TAMPER_3               (0x8U << TAMP_HWCFGR1_TAMPER_Pos)  /*!< 0x00000800 */

#define TAMP_HWCFGR1_BACKUP_REGS_Pos        (0U)
#define TAMP_HWCFGR1_BACKUP_REGS_Msk        (0xFFU << TAMP_HWCFGR1_BACKUP_REGS_Pos) /*!< 0x000000FF */
#define TAMP_HWCFGR1_BACKUP_REGS            TAMP_HWCFGR1_BACKUP_REGS_Msk
#define TAMP_HWCFGR1_BACKUP_REGS_0          (0x01U << TAMP_HWCFGR1_BACKUP_REGS_Pos) /*!< 0x00000001 */
#define TAMP_HWCFGR1_BACKUP_REGS_1          (0x02U << TAMP_HWCFGR1_BACKUP_REGS_Pos) /*!< 0x00000002 */
#define TAMP_HWCFGR1_BACKUP_REGS_2          (0x04U << TAMP_HWCFGR1_BACKUP_REGS_Pos) /*!< 0x00000004 */
#define TAMP_HWCFGR1_BACKUP_REGS_3          (0x08U << TAMP_HWCFGR1_BACKUP_REGS_Pos) /*!< 0x00000008 */
#define TAMP_HWCFGR1_BACKUP_REGS_4          (0x10U << TAMP_HWCFGR1_BACKUP_REGS_Pos) /*!< 0x00000010 */
#define TAMP_HWCFGR1_BACKUP_REGS_5          (0x20U << TAMP_HWCFGR1_BACKUP_REGS_Pos) /*!< 0x00000020 */
#define TAMP_HWCFGR1_BACKUP_REGS_6          (0x40U << TAMP_HWCFGR1_BACKUP_REGS_Pos) /*!< 0x00000040 */
#define TAMP_HWCFGR1_BACKUP_REGS_7          (0x80U << TAMP_HWCFGR1_BACKUP_REGS_Pos) /*!< 0x00000080 */

/********************  Bits definition for TAMP_VERR register  ****************/
#define TAMP_VERR_MAJREV_Pos                (4U)
#define TAMP_VERR_MAJREV_Msk                (0xFU << TAMP_VERR_MAJREV_Pos)     /*!< 0x000000F0 */
#define TAMP_VERR_MAJREV                    TAMP_VERR_MAJREV_Msk
#define TAMP_VERR_MAJREV_0                  (0x1U << TAMP_VERR_MAJREV_Pos)     /*!< 0x00000010 */
#define TAMP_VERR_MAJREV_1                  (0x2U << TAMP_VERR_MAJREV_Pos)     /*!< 0x00000020 */
#define TAMP_VERR_MAJREV_2                  (0x4U << TAMP_VERR_MAJREV_Pos)     /*!< 0x00000040 */
#define TAMP_VERR_MAJREV_3                  (0x8U << TAMP_VERR_MAJREV_Pos)     /*!< 0x00000080 */
#define TAMP_VERR_MINREV_Pos                (0U)
#define TAMP_VERR_MINREV_Msk                (0xFU << TAMP_VERR_MINREV_Pos)     /*!< 0x0000000F */
#define TAMP_VERR_MINREV                    TAMP_VERR_MINREV_Msk
#define TAMP_VERR_MINREV_0                  (0x1U << TAMP_VERR_MINREV_Pos)     /*!< 0x00000001 */
#define TAMP_VERR_MINREV_1                  (0x2U << TAMP_VERR_MINREV_Pos)     /*!< 0x00000002 */
#define TAMP_VERR_MINREV_2                  (0x4U << TAMP_VERR_MINREV_Pos)     /*!< 0x00000004 */
#define TAMP_VERR_MINREV_3                  (0x8U << TAMP_VERR_MINREV_Pos)     /*!< 0x00000008 */

/********************  Bits definition for TAMP_IPIDR register  ****************/
#define TAMP_IPIDR_ID_Pos                   (0U)
#define TAMP_IPIDR_ID_Msk                   (0xFFFFFFFFU << TAMP_IPIDR_ID_Pos) /*!< 0xFFFFFFFF */
#define TAMP_IPIDR_ID                       TAMP_IPIDR_ID_Msk

/********************  Bits definition for TAMP_SIDR register  ****************/
#define TAMP_SIDR_SID_Pos                   (0U)
#define TAMP_SIDR_SID_Msk                   (0xFFFFFFFFU << TAMP_SIDR_SID_Pos) /*!< 0xFFFFFFFF */
#define TAMP_SIDR_SID                       TAMP_SIDR_SID_Msk

/******************** Number of backup registers ******************************/
#define TAMP_BKP_NUMBER_Pos                 (5U)
#define TAMP_BKP_NUMBER_Msk                 (0x1U << TAMP_BKP_NUMBER_Pos)      /*!< 0x00000020 */
#define TAMP_BKP_NUMBER                     TAMP_BKP_NUMBER_Msk

/******************** Number of tamper registers ******************************/
#define TAMP_TAMPER_NUMBER_Pos              (0U)
#define TAMP_TAMPER_NUMBER_Msk              (0x3U << TAMP_TAMPER_NUMBER_Pos)   /*!< 0x00000003 */
#define TAMP_TAMPER_NUMBER                  TAMP_TAMPER_NUMBER_Msk

/******************************************************************************/
/*                                                                            */
/*                              SPDIF-RX Interface                            */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for SPDIF_CR register  *******************/
#define SPDIFRX_CR_SPDIFEN_Pos      (0U)
#define SPDIFRX_CR_SPDIFEN_Msk      (0x3U << SPDIFRX_CR_SPDIFEN_Pos)           /*!< 0x00000003 */
#define SPDIFRX_CR_SPDIFEN          SPDIFRX_CR_SPDIFEN_Msk                     /*!<Peripheral Block Enable                      */
#define SPDIFRX_CR_RXDMAEN_Pos      (2U)
#define SPDIFRX_CR_RXDMAEN_Msk      (0x1U << SPDIFRX_CR_RXDMAEN_Pos)           /*!< 0x00000004 */
#define SPDIFRX_CR_RXDMAEN          SPDIFRX_CR_RXDMAEN_Msk                     /*!<Receiver DMA Enable for data flow            */
#define SPDIFRX_CR_RXSTEO_Pos       (3U)
#define SPDIFRX_CR_RXSTEO_Msk       (0x1U << SPDIFRX_CR_RXSTEO_Pos)            /*!< 0x00000008 */
#define SPDIFRX_CR_RXSTEO           SPDIFRX_CR_RXSTEO_Msk                      /*!<Stereo Mode                                  */
#define SPDIFRX_CR_DRFMT_Pos        (4U)
#define SPDIFRX_CR_DRFMT_Msk        (0x3U << SPDIFRX_CR_DRFMT_Pos)             /*!< 0x00000030 */
#define SPDIFRX_CR_DRFMT            SPDIFRX_CR_DRFMT_Msk                       /*!<RX Data format                               */
#define SPDIFRX_CR_PMSK_Pos         (6U)
#define SPDIFRX_CR_PMSK_Msk         (0x1U << SPDIFRX_CR_PMSK_Pos)              /*!< 0x00000040 */
#define SPDIFRX_CR_PMSK             SPDIFRX_CR_PMSK_Msk                        /*!<Mask Parity error bit                        */
#define SPDIFRX_CR_VMSK_Pos         (7U)
#define SPDIFRX_CR_VMSK_Msk         (0x1U << SPDIFRX_CR_VMSK_Pos)              /*!< 0x00000080 */
#define SPDIFRX_CR_VMSK             SPDIFRX_CR_VMSK_Msk                        /*!<Mask of Validity bit                         */
#define SPDIFRX_CR_CUMSK_Pos        (8U)
#define SPDIFRX_CR_CUMSK_Msk        (0x1U << SPDIFRX_CR_CUMSK_Pos)             /*!< 0x00000100 */
#define SPDIFRX_CR_CUMSK            SPDIFRX_CR_CUMSK_Msk                       /*!<Mask of channel status and user bits         */
#define SPDIFRX_CR_PTMSK_Pos        (9U)
#define SPDIFRX_CR_PTMSK_Msk        (0x1U << SPDIFRX_CR_PTMSK_Pos)             /*!< 0x00000200 */
#define SPDIFRX_CR_PTMSK            SPDIFRX_CR_PTMSK_Msk                       /*!<Mask of Preamble Type bits                   */
#define SPDIFRX_CR_CBDMAEN_Pos      (10U)
#define SPDIFRX_CR_CBDMAEN_Msk      (0x1U << SPDIFRX_CR_CBDMAEN_Pos)           /*!< 0x00000400 */
#define SPDIFRX_CR_CBDMAEN          SPDIFRX_CR_CBDMAEN_Msk                     /*!<Control Buffer DMA ENable for control flow   */
#define SPDIFRX_CR_CHSEL_Pos        (11U)
#define SPDIFRX_CR_CHSEL_Msk        (0x1U << SPDIFRX_CR_CHSEL_Pos)             /*!< 0x00000800 */
#define SPDIFRX_CR_CHSEL            SPDIFRX_CR_CHSEL_Msk                       /*!<Channel Selection                            */
#define SPDIFRX_CR_NBTR_Pos         (12U)
#define SPDIFRX_CR_NBTR_Msk         (0x3U << SPDIFRX_CR_NBTR_Pos)              /*!< 0x00003000 */
#define SPDIFRX_CR_NBTR             SPDIFRX_CR_NBTR_Msk                        /*!<Maximum allowed re-tries during synchronization phase */
#define SPDIFRX_CR_WFA_Pos          (14U)
#define SPDIFRX_CR_WFA_Msk          (0x1U << SPDIFRX_CR_WFA_Pos)               /*!< 0x00004000 */
#define SPDIFRX_CR_WFA              SPDIFRX_CR_WFA_Msk                         /*!<Wait For Activity     */
#define SPDIFRX_CR_INSEL_Pos        (16U)
#define SPDIFRX_CR_INSEL_Msk        (0x7U << SPDIFRX_CR_INSEL_Pos)             /*!< 0x00070000 */
#define SPDIFRX_CR_INSEL            SPDIFRX_CR_INSEL_Msk                       /*!<SPDIF input selection */

/*******************  Bit definition for SPDIFRX_IMR register  *******************/
#define SPDIFRX_IMR_RXNEIE_Pos      (0U)
#define SPDIFRX_IMR_RXNEIE_Msk      (0x1U << SPDIFRX_IMR_RXNEIE_Pos)           /*!< 0x00000001 */
#define SPDIFRX_IMR_RXNEIE          SPDIFRX_IMR_RXNEIE_Msk                     /*!<RXNE interrupt enable                              */
#define SPDIFRX_IMR_CSRNEIE_Pos     (1U)
#define SPDIFRX_IMR_CSRNEIE_Msk     (0x1U << SPDIFRX_IMR_CSRNEIE_Pos)          /*!< 0x00000002 */
#define SPDIFRX_IMR_CSRNEIE         SPDIFRX_IMR_CSRNEIE_Msk                    /*!<Control Buffer Ready Interrupt Enable              */
#define SPDIFRX_IMR_PERRIE_Pos      (2U)
#define SPDIFRX_IMR_PERRIE_Msk      (0x1U << SPDIFRX_IMR_PERRIE_Pos)           /*!< 0x00000004 */
#define SPDIFRX_IMR_PERRIE          SPDIFRX_IMR_PERRIE_Msk                     /*!<Parity error interrupt enable                      */
#define SPDIFRX_IMR_OVRIE_Pos       (3U)
#define SPDIFRX_IMR_OVRIE_Msk       (0x1U << SPDIFRX_IMR_OVRIE_Pos)            /*!< 0x00000008 */
#define SPDIFRX_IMR_OVRIE           SPDIFRX_IMR_OVRIE_Msk                      /*!<Overrun error Interrupt Enable                     */
#define SPDIFRX_IMR_SBLKIE_Pos      (4U)
#define SPDIFRX_IMR_SBLKIE_Msk      (0x1U << SPDIFRX_IMR_SBLKIE_Pos)           /*!< 0x00000010 */
#define SPDIFRX_IMR_SBLKIE          SPDIFRX_IMR_SBLKIE_Msk                     /*!<Synchronization Block Detected Interrupt Enable    */
#define SPDIFRX_IMR_SYNCDIE_Pos     (5U)
#define SPDIFRX_IMR_SYNCDIE_Msk     (0x1U << SPDIFRX_IMR_SYNCDIE_Pos)          /*!< 0x00000020 */
#define SPDIFRX_IMR_SYNCDIE         SPDIFRX_IMR_SYNCDIE_Msk                    /*!<Synchronization Done                               */
#define SPDIFRX_IMR_IFEIE_Pos       (6U)
#define SPDIFRX_IMR_IFEIE_Msk       (0x1U << SPDIFRX_IMR_IFEIE_Pos)            /*!< 0x00000040 */
#define SPDIFRX_IMR_IFEIE           SPDIFRX_IMR_IFEIE_Msk                      /*!<Serial Interface Error Interrupt Enable            */

/*******************  Bit definition for SPDIFRX_SR register  *******************/
#define SPDIFRX_SR_RXNE_Pos         (0U)
#define SPDIFRX_SR_RXNE_Msk         (0x1U << SPDIFRX_SR_RXNE_Pos)              /*!< 0x00000001 */
#define SPDIFRX_SR_RXNE             SPDIFRX_SR_RXNE_Msk                        /*!<Read data register not empty                          */
#define SPDIFRX_SR_CSRNE_Pos        (1U)
#define SPDIFRX_SR_CSRNE_Msk        (0x1U << SPDIFRX_SR_CSRNE_Pos)             /*!< 0x00000002 */
#define SPDIFRX_SR_CSRNE            SPDIFRX_SR_CSRNE_Msk                       /*!<The Control Buffer register is not empty              */
#define SPDIFRX_SR_PERR_Pos         (2U)
#define SPDIFRX_SR_PERR_Msk         (0x1U << SPDIFRX_SR_PERR_Pos)              /*!< 0x00000004 */
#define SPDIFRX_SR_PERR             SPDIFRX_SR_PERR_Msk                        /*!<Parity error                                          */
#define SPDIFRX_SR_OVR_Pos          (3U)
#define SPDIFRX_SR_OVR_Msk          (0x1U << SPDIFRX_SR_OVR_Pos)               /*!< 0x00000008 */
#define SPDIFRX_SR_OVR              SPDIFRX_SR_OVR_Msk                         /*!<Overrun error                                         */
#define SPDIFRX_SR_SBD_Pos          (4U)
#define SPDIFRX_SR_SBD_Msk          (0x1U << SPDIFRX_SR_SBD_Pos)               /*!< 0x00000010 */
#define SPDIFRX_SR_SBD              SPDIFRX_SR_SBD_Msk                         /*!<Synchronization Block Detected                        */
#define SPDIFRX_SR_SYNCD_Pos        (5U)
#define SPDIFRX_SR_SYNCD_Msk        (0x1U << SPDIFRX_SR_SYNCD_Pos)             /*!< 0x00000020 */
#define SPDIFRX_SR_SYNCD            SPDIFRX_SR_SYNCD_Msk                       /*!<Synchronization Done                                  */
#define SPDIFRX_SR_FERR_Pos         (6U)
#define SPDIFRX_SR_FERR_Msk         (0x1U << SPDIFRX_SR_FERR_Pos)              /*!< 0x00000040 */
#define SPDIFRX_SR_FERR             SPDIFRX_SR_FERR_Msk                        /*!<Framing error                                         */
#define SPDIFRX_SR_SERR_Pos         (7U)
#define SPDIFRX_SR_SERR_Msk         (0x1U << SPDIFRX_SR_SERR_Pos)              /*!< 0x00000080 */
#define SPDIFRX_SR_SERR             SPDIFRX_SR_SERR_Msk                        /*!<Synchronization error                                 */
#define SPDIFRX_SR_TERR_Pos         (8U)
#define SPDIFRX_SR_TERR_Msk         (0x1U << SPDIFRX_SR_TERR_Pos)              /*!< 0x00000100 */
#define SPDIFRX_SR_TERR             SPDIFRX_SR_TERR_Msk                        /*!<Time-out error                                        */
#define SPDIFRX_SR_WIDTH5_Pos       (16U)
#define SPDIFRX_SR_WIDTH5_Msk       (0x7FFFU << SPDIFRX_SR_WIDTH5_Pos)         /*!< 0x7FFF0000 */
#define SPDIFRX_SR_WIDTH5           SPDIFRX_SR_WIDTH5_Msk                      /*!<Duration of 5 symbols counted with spdif_clk          */

/*******************  Bit definition for SPDIFRX_IFCR register  *******************/
#define SPDIFRX_IFCR_PERRCF_Pos     (2U)
#define SPDIFRX_IFCR_PERRCF_Msk     (0x1U << SPDIFRX_IFCR_PERRCF_Pos)          /*!< 0x00000004 */
#define SPDIFRX_IFCR_PERRCF         SPDIFRX_IFCR_PERRCF_Msk                    /*!<Clears the Parity error flag                         */
#define SPDIFRX_IFCR_OVRCF_Pos      (3U)
#define SPDIFRX_IFCR_OVRCF_Msk      (0x1U << SPDIFRX_IFCR_OVRCF_Pos)           /*!< 0x00000008 */
#define SPDIFRX_IFCR_OVRCF          SPDIFRX_IFCR_OVRCF_Msk                     /*!<Clears the Overrun error flag                        */
#define SPDIFRX_IFCR_SBDCF_Pos      (4U)
#define SPDIFRX_IFCR_SBDCF_Msk      (0x1U << SPDIFRX_IFCR_SBDCF_Pos)           /*!< 0x00000010 */
#define SPDIFRX_IFCR_SBDCF          SPDIFRX_IFCR_SBDCF_Msk                     /*!<Clears the Synchronization Block Detected flag       */
#define SPDIFRX_IFCR_SYNCDCF_Pos    (5U)
#define SPDIFRX_IFCR_SYNCDCF_Msk    (0x1U << SPDIFRX_IFCR_SYNCDCF_Pos)         /*!< 0x00000020 */
#define SPDIFRX_IFCR_SYNCDCF        SPDIFRX_IFCR_SYNCDCF_Msk                   /*!<Clears the Synchronization Done flag                 */

/*******************  Bit definition for SPDIFRX_DR register  (DRFMT = 0b00 case) *******************/
#define SPDIFRX_DR0_DR_Pos          (0U)
#define SPDIFRX_DR0_DR_Msk          (0xFFFFFFU << SPDIFRX_DR0_DR_Pos)          /*!< 0x00FFFFFF */
#define SPDIFRX_DR0_DR              SPDIFRX_DR0_DR_Msk                         /*!<Data value            */
#define SPDIFRX_DR0_PE_Pos          (24U)
#define SPDIFRX_DR0_PE_Msk          (0x1U << SPDIFRX_DR0_PE_Pos)               /*!< 0x01000000 */
#define SPDIFRX_DR0_PE              SPDIFRX_DR0_PE_Msk                         /*!<Parity Error bit      */
#define SPDIFRX_DR0_V_Pos           (25U)
#define SPDIFRX_DR0_V_Msk           (0x1U << SPDIFRX_DR0_V_Pos)                /*!< 0x02000000 */
#define SPDIFRX_DR0_V               SPDIFRX_DR0_V_Msk                          /*!<Validity bit          */
#define SPDIFRX_DR0_U_Pos           (26U)
#define SPDIFRX_DR0_U_Msk           (0x1U << SPDIFRX_DR0_U_Pos)                /*!< 0x04000000 */
#define SPDIFRX_DR0_U               SPDIFRX_DR0_U_Msk                          /*!<User bit              */
#define SPDIFRX_DR0_C_Pos           (27U)
#define SPDIFRX_DR0_C_Msk           (0x1U << SPDIFRX_DR0_C_Pos)                /*!< 0x08000000 */
#define SPDIFRX_DR0_C               SPDIFRX_DR0_C_Msk                          /*!<Channel Status bit    */
#define SPDIFRX_DR0_PT_Pos          (28U)
#define SPDIFRX_DR0_PT_Msk          (0x3U << SPDIFRX_DR0_PT_Pos)               /*!< 0x30000000 */
#define SPDIFRX_DR0_PT              SPDIFRX_DR0_PT_Msk                         /*!<Preamble Type         */

/*******************  Bit definition for SPDIFRX_DR register  (DRFMT = 0b01 case) *******************/
#define SPDIFRX_DR1_DR_Pos          (8U)
#define SPDIFRX_DR1_DR_Msk          (0xFFFFFFU << SPDIFRX_DR1_DR_Pos)          /*!< 0xFFFFFF00 */
#define SPDIFRX_DR1_DR              SPDIFRX_DR1_DR_Msk                         /*!<Data value            */
#define SPDIFRX_DR1_PT_Pos          (4U)
#define SPDIFRX_DR1_PT_Msk          (0x3U << SPDIFRX_DR1_PT_Pos)               /*!< 0x00000030 */
#define SPDIFRX_DR1_PT              SPDIFRX_DR1_PT_Msk                         /*!<Preamble Type         */
#define SPDIFRX_DR1_C_Pos           (3U)
#define SPDIFRX_DR1_C_Msk           (0x1U << SPDIFRX_DR1_C_Pos)                /*!< 0x00000008 */
#define SPDIFRX_DR1_C               SPDIFRX_DR1_C_Msk                          /*!<Channel Status bit    */
#define SPDIFRX_DR1_U_Pos           (2U)
#define SPDIFRX_DR1_U_Msk           (0x1U << SPDIFRX_DR1_U_Pos)                /*!< 0x00000004 */
#define SPDIFRX_DR1_U               SPDIFRX_DR1_U_Msk                          /*!<User bit              */
#define SPDIFRX_DR1_V_Pos           (1U)
#define SPDIFRX_DR1_V_Msk           (0x1U << SPDIFRX_DR1_V_Pos)                /*!< 0x00000002 */
#define SPDIFRX_DR1_V               SPDIFRX_DR1_V_Msk                          /*!<Validity bit          */
#define SPDIFRX_DR1_PE_Pos          (0U)
#define SPDIFRX_DR1_PE_Msk          (0x1U << SPDIFRX_DR1_PE_Pos)               /*!< 0x00000001 */
#define SPDIFRX_DR1_PE              SPDIFRX_DR1_PE_Msk                         /*!<Parity Error bit      */

/*******************  Bit definition for SPDIFRX_DR register  (DRFMT = 0b10 case) *******************/
#define SPDIFRX_DR1_DRNL1_Pos       (16U)
#define SPDIFRX_DR1_DRNL1_Msk       (0xFFFFU << SPDIFRX_DR1_DRNL1_Pos)         /*!< 0xFFFF0000 */
#define SPDIFRX_DR1_DRNL1           SPDIFRX_DR1_DRNL1_Msk                      /*!<Data value Channel B      */
#define SPDIFRX_DR1_DRNL2_Pos       (0U)
#define SPDIFRX_DR1_DRNL2_Msk       (0xFFFFU << SPDIFRX_DR1_DRNL2_Pos)         /*!< 0x0000FFFF */
#define SPDIFRX_DR1_DRNL2           SPDIFRX_DR1_DRNL2_Msk                      /*!<Data value Channel A      */

/*******************  Bit definition for SPDIFRX_CSR register   *******************/
#define SPDIFRX_CSR_USR_Pos         (0U)
#define SPDIFRX_CSR_USR_Msk         (0xFFFFU << SPDIFRX_CSR_USR_Pos)           /*!< 0x0000FFFF */
#define SPDIFRX_CSR_USR             SPDIFRX_CSR_USR_Msk                        /*!<User data information           */
#define SPDIFRX_CSR_CS_Pos          (16U)
#define SPDIFRX_CSR_CS_Msk          (0xFFU << SPDIFRX_CSR_CS_Pos)              /*!< 0x00FF0000 */
#define SPDIFRX_CSR_CS              SPDIFRX_CSR_CS_Msk                         /*!<Channel A status information    */
#define SPDIFRX_CSR_SOB_Pos         (24U)
#define SPDIFRX_CSR_SOB_Msk         (0x1U << SPDIFRX_CSR_SOB_Pos)              /*!< 0x01000000 */
#define SPDIFRX_CSR_SOB             SPDIFRX_CSR_SOB_Msk                        /*!<Start Of Block                  */

/*******************  Bit definition for SPDIFRX_DIR register    *******************/
#define SPDIFRX_DIR_THI_Pos         (0U)
#define SPDIFRX_DIR_THI_Msk         (0x1FFFU << SPDIFRX_DIR_THI_Pos)           /*!< 0x00001FFF */
#define SPDIFRX_DIR_THI             SPDIFRX_DIR_THI_Msk                        /*!<Threshold LOW      */
#define SPDIFRX_DIR_TLO_Pos         (16U)
#define SPDIFRX_DIR_TLO_Msk         (0x1FFFU << SPDIFRX_DIR_TLO_Pos)           /*!< 0x1FFF0000 */
#define SPDIFRX_DIR_TLO             SPDIFRX_DIR_TLO_Msk                        /*!<Threshold HIGH     */

/**********************  Bit definition for SPDIFRX_VERR register  *****************/
#define SPDIFRX_VERR_MINREV_Pos      (0U)
#define SPDIFRX_VERR_MINREV_Msk      (0xFU << SPDIFRX_VERR_MINREV_Pos)               /*!< 0x0000000F */
#define SPDIFRX_VERR_MINREV          SPDIFRX_VERR_MINREV_Msk                         /*!< Minor Revision number */
#define SPDIFRX_VERR_MAJREV_Pos      (4U)
#define SPDIFRX_VERR_MAJREV_Msk      (0xFU << SPDIFRX_VERR_MAJREV_Pos)               /*!< 0x000000F0 */
#define SPDIFRX_VERR_MAJREV          SPDIFRX_VERR_MAJREV_Msk                         /*!< Major Revision number */

/**********************  Bit definition for SPDIFRX_IPIDR register  ****************/
#define SPDIFRX_IPIDR_IPID_Pos       (0U)
#define SPDIFRX_IPIDR_IPID_Msk       (0xFFFFFFFFU << SPDIFRX_IPIDR_IPID_Pos)         /*!< 0xFFFFFFFF */
#define SPDIFRX_IPIDR_IPID           SPDIFRX_IPIDR_IPID_Msk                          /*!< IP Identification */

/**********************  Bit definition for SPDIFRX_SIDR register  *****************/
#define SPDIFRX_SIDR_SID_Pos         (0U)
#define SPDIFRX_SIDR_SID_Msk         (0xFFFFFFFFU << SPDIFRX_SIDR_SID_Pos)           /*!< 0xFFFFFFFF */
#define SPDIFRX_SIDR_SID             SPDIFRX_SIDR_SID_Msk                            /*!< IP size identification */

/******************************************************************************/
/*                                                                            */
/*                          Serial Audio Interface                            */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for SAI_GCR register  *******************/
#define SAI_GCR_SYNCIN_Pos         (0U)
#define SAI_GCR_SYNCIN_Msk         (0x3UL << SAI_GCR_SYNCIN_Pos)               /*!< 0x00000003 */
#define SAI_GCR_SYNCIN             SAI_GCR_SYNCIN_Msk                          /*!<SYNCIN[1:0] bits (Synchronization Inputs)   */
#define SAI_GCR_SYNCIN_0           (0x1U << SAI_GCR_SYNCIN_Pos)                /*!< 0x00000001 */
#define SAI_GCR_SYNCIN_1           (0x2U << SAI_GCR_SYNCIN_Pos)                /*!< 0x00000002 */

#define SAI_GCR_SYNCOUT_Pos        (4U)
#define SAI_GCR_SYNCOUT_Msk        (0x3UL << SAI_GCR_SYNCOUT_Pos)              /*!< 0x00000030 */
#define SAI_GCR_SYNCOUT            SAI_GCR_SYNCOUT_Msk                         /*!<SYNCOUT[1:0] bits (Synchronization Outputs) */
#define SAI_GCR_SYNCOUT_0          (0x1U << SAI_GCR_SYNCOUT_Pos)               /*!< 0x00000010 */
#define SAI_GCR_SYNCOUT_1          (0x2U << SAI_GCR_SYNCOUT_Pos)               /*!< 0x00000020 */

/*******************  Bit definition for SAI_xCR1 register  *******************/
#define SAI_xCR1_MODE_Pos          (0U)
#define SAI_xCR1_MODE_Msk          (0x3UL << SAI_xCR1_MODE_Pos)                /*!< 0x00000003 */
#define SAI_xCR1_MODE              SAI_xCR1_MODE_Msk                           /*!<MODE[1:0] bits (Audio Block Mode)           */
#define SAI_xCR1_MODE_0            (0x1U << SAI_xCR1_MODE_Pos)                 /*!< 0x00000001 */
#define SAI_xCR1_MODE_1            (0x2U << SAI_xCR1_MODE_Pos)                 /*!< 0x00000002 */

#define SAI_xCR1_PRTCFG_Pos        (2U)
#define SAI_xCR1_PRTCFG_Msk        (0x3UL << SAI_xCR1_PRTCFG_Pos)              /*!< 0x0000000C */
#define SAI_xCR1_PRTCFG            SAI_xCR1_PRTCFG_Msk                         /*!<PRTCFG[1:0] bits (Protocol Configuration)   */
#define SAI_xCR1_PRTCFG_0          (0x1U << SAI_xCR1_PRTCFG_Pos)               /*!< 0x00000004 */
#define SAI_xCR1_PRTCFG_1          (0x2U << SAI_xCR1_PRTCFG_Pos)               /*!< 0x00000008 */

#define SAI_xCR1_DS_Pos            (5U)
#define SAI_xCR1_DS_Msk            (0x7UL << SAI_xCR1_DS_Pos)                  /*!< 0x000000E0 */
#define SAI_xCR1_DS                SAI_xCR1_DS_Msk                             /*!<DS[1:0] bits (Data Size) */
#define SAI_xCR1_DS_0              (0x1U << SAI_xCR1_DS_Pos)                   /*!< 0x00000020 */
#define SAI_xCR1_DS_1              (0x2U << SAI_xCR1_DS_Pos)                   /*!< 0x00000040 */
#define SAI_xCR1_DS_2              (0x4U << SAI_xCR1_DS_Pos)                   /*!< 0x00000080 */

#define SAI_xCR1_LSBFIRST_Pos      (8U)
#define SAI_xCR1_LSBFIRST_Msk      (0x1UL << SAI_xCR1_LSBFIRST_Pos)            /*!< 0x00000100 */
#define SAI_xCR1_LSBFIRST          SAI_xCR1_LSBFIRST_Msk                       /*!<LSB First Configuration  */
#define SAI_xCR1_CKSTR_Pos         (9U)
#define SAI_xCR1_CKSTR_Msk         (0x1UL << SAI_xCR1_CKSTR_Pos)               /*!< 0x00000200 */
#define SAI_xCR1_CKSTR             SAI_xCR1_CKSTR_Msk                          /*!<ClocK STRobing edge      */

#define SAI_xCR1_SYNCEN_Pos        (10U)
#define SAI_xCR1_SYNCEN_Msk        (0x3UL << SAI_xCR1_SYNCEN_Pos)              /*!< 0x00000C00 */
#define SAI_xCR1_SYNCEN            SAI_xCR1_SYNCEN_Msk                         /*!<SYNCEN[1:0](SYNChronization ENable) */
#define SAI_xCR1_SYNCEN_0          (0x1U << SAI_xCR1_SYNCEN_Pos)               /*!< 0x00000400 */
#define SAI_xCR1_SYNCEN_1          (0x2U << SAI_xCR1_SYNCEN_Pos)               /*!< 0x00000800 */

#define SAI_xCR1_MONO_Pos          (12U)
#define SAI_xCR1_MONO_Msk          (0x1UL << SAI_xCR1_MONO_Pos)                /*!< 0x00001000 */
#define SAI_xCR1_MONO              SAI_xCR1_MONO_Msk                           /*!<Mono mode                  */
#define SAI_xCR1_OUTDRIV_Pos       (13U)
#define SAI_xCR1_OUTDRIV_Msk       (0x1UL << SAI_xCR1_OUTDRIV_Pos)             /*!< 0x00002000 */
#define SAI_xCR1_OUTDRIV           SAI_xCR1_OUTDRIV_Msk                        /*!<Output Drive               */
#define SAI_xCR1_SAIEN_Pos         (16U)
#define SAI_xCR1_SAIEN_Msk         (0x1UL << SAI_xCR1_SAIEN_Pos)               /*!< 0x00010000 */
#define SAI_xCR1_SAIEN             SAI_xCR1_SAIEN_Msk                          /*!<Audio Block enable         */
#define SAI_xCR1_DMAEN_Pos         (17U)
#define SAI_xCR1_DMAEN_Msk         (0x1UL << SAI_xCR1_DMAEN_Pos)               /*!< 0x00020000 */
#define SAI_xCR1_DMAEN             SAI_xCR1_DMAEN_Msk                          /*!<DMA enable                 */
#define SAI_xCR1_NODIV_Pos         (19U)
#define SAI_xCR1_NODIV_Msk         (0x1UL << SAI_xCR1_NODIV_Pos)               /*!< 0x00080000 */
#define SAI_xCR1_NODIV             SAI_xCR1_NODIV_Msk                          /*!<No Divider Configuration   */

#define SAI_xCR1_MCKDIV_Pos        (20U)
#define SAI_xCR1_MCKDIV_Msk        (0x3FUL << SAI_xCR1_MCKDIV_Pos)             /*!< 0x03F00000 */
#define SAI_xCR1_MCKDIV            SAI_xCR1_MCKDIV_Msk                         /*!<MCKDIV[5:0] (Master ClocK Divider)  */
#define SAI_xCR1_MCKDIV_0          (0x01U << SAI_xCR1_MCKDIV_Pos)              /*!< 0x00100000 */
#define SAI_xCR1_MCKDIV_1          (0x02U << SAI_xCR1_MCKDIV_Pos)              /*!< 0x00200000 */
#define SAI_xCR1_MCKDIV_2          (0x04U << SAI_xCR1_MCKDIV_Pos)              /*!< 0x00400000 */
#define SAI_xCR1_MCKDIV_3          (0x08U << SAI_xCR1_MCKDIV_Pos)              /*!< 0x00800000 */
#define SAI_xCR1_MCKDIV_4          (0x10U << SAI_xCR1_MCKDIV_Pos)              /*!< 0x01000000 */
#define SAI_xCR1_MCKDIV_5          (0x20U << SAI_xCR1_MCKDIV_Pos)              /*!< 0x02000000 */

#define SAI_xCR1_MCKEN_Pos         (27U)
#define SAI_xCR1_MCKEN_Msk         (0x1UL << SAI_xCR1_MCKEN_Pos)               /*!< 0x08000000 */
#define SAI_xCR1_MCKEN             SAI_xCR1_MCKEN_Msk                          /*!<Master ClocK enable */

#define SAI_xCR1_OSR_Pos           (26U)
#define SAI_xCR1_OSR_Msk           (0x1UL << SAI_xCR1_OSR_Pos)                 /*!< 0x04000000 */
#define SAI_xCR1_OSR               SAI_xCR1_OSR_Msk                            /*!<OverSampling Ratio for master clock  */

/* Legacy define */
#define  SAI_xCR1_NOMCK               SAI_xCR1_NODIV

/*******************  Bit definition for SAI_xCR2 register  *******************/
#define SAI_xCR2_FTH_Pos           (0U)
#define SAI_xCR2_FTH_Msk           (0x7UL << SAI_xCR2_FTH_Pos)                 /*!< 0x00000007 */
#define SAI_xCR2_FTH               SAI_xCR2_FTH_Msk                            /*!<FTH[2:0](Fifo THreshold)  */
#define SAI_xCR2_FTH_0             (0x1U << SAI_xCR2_FTH_Pos)                  /*!< 0x00000001 */
#define SAI_xCR2_FTH_1             (0x2U << SAI_xCR2_FTH_Pos)                  /*!< 0x00000002 */
#define SAI_xCR2_FTH_2             (0x4U << SAI_xCR2_FTH_Pos)                  /*!< 0x00000004 */

#define SAI_xCR2_FFLUSH_Pos        (3U)
#define SAI_xCR2_FFLUSH_Msk        (0x1UL << SAI_xCR2_FFLUSH_Pos)              /*!< 0x00000008 */
#define SAI_xCR2_FFLUSH            SAI_xCR2_FFLUSH_Msk                         /*!<Fifo FLUSH                       */
#define SAI_xCR2_TRIS_Pos          (4U)
#define SAI_xCR2_TRIS_Msk          (0x1UL << SAI_xCR2_TRIS_Pos)                /*!< 0x00000010 */
#define SAI_xCR2_TRIS              SAI_xCR2_TRIS_Msk                           /*!<TRIState Management on data line */
#define SAI_xCR2_MUTE_Pos          (5U)
#define SAI_xCR2_MUTE_Msk          (0x1UL << SAI_xCR2_MUTE_Pos)                /*!< 0x00000020 */
#define SAI_xCR2_MUTE              SAI_xCR2_MUTE_Msk                           /*!<Mute mode                        */
#define SAI_xCR2_MUTEVAL_Pos       (6U)
#define SAI_xCR2_MUTEVAL_Msk       (0x1UL << SAI_xCR2_MUTEVAL_Pos)             /*!< 0x00000040 */
#define SAI_xCR2_MUTEVAL           SAI_xCR2_MUTEVAL_Msk                        /*!<Muate value                      */

#define SAI_xCR2_MUTECNT_Pos       (7U)
#define SAI_xCR2_MUTECNT_Msk       (0x3FUL << SAI_xCR2_MUTECNT_Pos)            /*!< 0x00001F80 */
#define SAI_xCR2_MUTECNT           SAI_xCR2_MUTECNT_Msk                        /*!<MUTECNT[5:0] (MUTE counter) */
#define SAI_xCR2_MUTECNT_0         (0x01U << SAI_xCR2_MUTECNT_Pos)             /*!< 0x00000080 */
#define SAI_xCR2_MUTECNT_1         (0x02U << SAI_xCR2_MUTECNT_Pos)             /*!< 0x00000100 */
#define SAI_xCR2_MUTECNT_2         (0x04U << SAI_xCR2_MUTECNT_Pos)             /*!< 0x00000200 */
#define SAI_xCR2_MUTECNT_3         (0x08U << SAI_xCR2_MUTECNT_Pos)             /*!< 0x00000400 */
#define SAI_xCR2_MUTECNT_4         (0x10U << SAI_xCR2_MUTECNT_Pos)             /*!< 0x00000800 */
#define SAI_xCR2_MUTECNT_5         (0x20U << SAI_xCR2_MUTECNT_Pos)             /*!< 0x00001000 */

#define SAI_xCR2_CPL_Pos           (13U)
#define SAI_xCR2_CPL_Msk           (0x1UL << SAI_xCR2_CPL_Pos)                 /*!< 0x00002000 */
#define SAI_xCR2_CPL               SAI_xCR2_CPL_Msk                            /*!< Complement Bit             */

#define SAI_xCR2_COMP_Pos          (14U)
#define SAI_xCR2_COMP_Msk          (0x3UL << SAI_xCR2_COMP_Pos)                /*!< 0x0000C000 */
#define SAI_xCR2_COMP              SAI_xCR2_COMP_Msk                           /*!<COMP[1:0] (Companding mode) */
#define SAI_xCR2_COMP_0            (0x1U << SAI_xCR2_COMP_Pos)                 /*!< 0x00004000 */
#define SAI_xCR2_COMP_1            (0x2U << SAI_xCR2_COMP_Pos)                 /*!< 0x00008000 */

/******************  Bit definition for SAI_xFRCR register  *******************/
#define SAI_xFRCR_FRL_Pos          (0U)
#define SAI_xFRCR_FRL_Msk          (0xFFUL << SAI_xFRCR_FRL_Pos)               /*!< 0x000000FF */
#define SAI_xFRCR_FRL              SAI_xFRCR_FRL_Msk                           /*!<FRL[7:0](FRame Length)  */
#define SAI_xFRCR_FRL_0            (0x01U << SAI_xFRCR_FRL_Pos)                /*!< 0x00000001 */
#define SAI_xFRCR_FRL_1            (0x02U << SAI_xFRCR_FRL_Pos)                /*!< 0x00000002 */
#define SAI_xFRCR_FRL_2            (0x04U << SAI_xFRCR_FRL_Pos)                /*!< 0x00000004 */
#define SAI_xFRCR_FRL_3            (0x08U << SAI_xFRCR_FRL_Pos)                /*!< 0x00000008 */
#define SAI_xFRCR_FRL_4            (0x10U << SAI_xFRCR_FRL_Pos)                /*!< 0x00000010 */
#define SAI_xFRCR_FRL_5            (0x20U << SAI_xFRCR_FRL_Pos)                /*!< 0x00000020 */
#define SAI_xFRCR_FRL_6            (0x40U << SAI_xFRCR_FRL_Pos)                /*!< 0x00000040 */
#define SAI_xFRCR_FRL_7            (0x80U << SAI_xFRCR_FRL_Pos)                /*!< 0x00000080 */

#define SAI_xFRCR_FSALL_Pos        (8U)
#define SAI_xFRCR_FSALL_Msk        (0x7FUL << SAI_xFRCR_FSALL_Pos)             /*!< 0x00007F00 */
#define SAI_xFRCR_FSALL            SAI_xFRCR_FSALL_Msk                         /*!<FSALL[6:0] (Frame Synchronization Active Level Length)  */
#define SAI_xFRCR_FSALL_0          (0x01U << SAI_xFRCR_FSALL_Pos)              /*!< 0x00000100 */
#define SAI_xFRCR_FSALL_1          (0x02U << SAI_xFRCR_FSALL_Pos)              /*!< 0x00000200 */
#define SAI_xFRCR_FSALL_2          (0x04U << SAI_xFRCR_FSALL_Pos)              /*!< 0x00000400 */
#define SAI_xFRCR_FSALL_3          (0x08U << SAI_xFRCR_FSALL_Pos)              /*!< 0x00000800 */
#define SAI_xFRCR_FSALL_4          (0x10U << SAI_xFRCR_FSALL_Pos)              /*!< 0x00001000 */
#define SAI_xFRCR_FSALL_5          (0x20U << SAI_xFRCR_FSALL_Pos)              /*!< 0x00002000 */
#define SAI_xFRCR_FSALL_6          (0x40U << SAI_xFRCR_FSALL_Pos)              /*!< 0x00004000 */

#define SAI_xFRCR_FSDEF_Pos        (16U)
#define SAI_xFRCR_FSDEF_Msk        (0x1UL << SAI_xFRCR_FSDEF_Pos)              /*!< 0x00010000 */
#define SAI_xFRCR_FSDEF            SAI_xFRCR_FSDEF_Msk                         /*!<Frame Synchronization Definition  */
#define SAI_xFRCR_FSPOL_Pos        (17U)
#define SAI_xFRCR_FSPOL_Msk        (0x1UL << SAI_xFRCR_FSPOL_Pos)              /*!< 0x00020000 */
#define SAI_xFRCR_FSPOL            SAI_xFRCR_FSPOL_Msk                         /*!<Frame Synchronization POLarity    */
#define SAI_xFRCR_FSOFF_Pos        (18U)
#define SAI_xFRCR_FSOFF_Msk        (0x1UL << SAI_xFRCR_FSOFF_Pos)              /*!< 0x00040000 */
#define SAI_xFRCR_FSOFF            SAI_xFRCR_FSOFF_Msk                         /*!<Frame Synchronization OFFset      */

/* Legacy define */
#define  SAI_xFRCR_FSPO                      SAI_xFRCR_FSPOL

/******************  Bit definition for SAI_xSLOTR register  *******************/
#define SAI_xSLOTR_FBOFF_Pos       (0U)
#define SAI_xSLOTR_FBOFF_Msk       (0x1FUL << SAI_xSLOTR_FBOFF_Pos)            /*!< 0x0000001F */
#define SAI_xSLOTR_FBOFF           SAI_xSLOTR_FBOFF_Msk                        /*!<FBOFF[4:0](First Bit Offset)  */
#define SAI_xSLOTR_FBOFF_0         (0x01U << SAI_xSLOTR_FBOFF_Pos)             /*!< 0x00000001 */
#define SAI_xSLOTR_FBOFF_1         (0x02U << SAI_xSLOTR_FBOFF_Pos)             /*!< 0x00000002 */
#define SAI_xSLOTR_FBOFF_2         (0x04U << SAI_xSLOTR_FBOFF_Pos)             /*!< 0x00000004 */
#define SAI_xSLOTR_FBOFF_3         (0x08U << SAI_xSLOTR_FBOFF_Pos)             /*!< 0x00000008 */
#define SAI_xSLOTR_FBOFF_4         (0x10U << SAI_xSLOTR_FBOFF_Pos)             /*!< 0x00000010 */

#define SAI_xSLOTR_SLOTSZ_Pos      (6U)
#define SAI_xSLOTR_SLOTSZ_Msk      (0x3UL << SAI_xSLOTR_SLOTSZ_Pos)            /*!< 0x000000C0 */
#define SAI_xSLOTR_SLOTSZ          SAI_xSLOTR_SLOTSZ_Msk                       /*!<SLOTSZ[1:0] (Slot size)  */
#define SAI_xSLOTR_SLOTSZ_0        (0x1U << SAI_xSLOTR_SLOTSZ_Pos)             /*!< 0x00000040 */
#define SAI_xSLOTR_SLOTSZ_1        (0x2U << SAI_xSLOTR_SLOTSZ_Pos)             /*!< 0x00000080 */

#define SAI_xSLOTR_NBSLOT_Pos      (8U)
#define SAI_xSLOTR_NBSLOT_Msk      (0xFUL << SAI_xSLOTR_NBSLOT_Pos)            /*!< 0x00000F00 */
#define SAI_xSLOTR_NBSLOT          SAI_xSLOTR_NBSLOT_Msk                       /*!<NBSLOT[3:0] (Number of Slot in audio Frame)  */
#define SAI_xSLOTR_NBSLOT_0        (0x1U << SAI_xSLOTR_NBSLOT_Pos)             /*!< 0x00000100 */
#define SAI_xSLOTR_NBSLOT_1        (0x2U << SAI_xSLOTR_NBSLOT_Pos)             /*!< 0x00000200 */
#define SAI_xSLOTR_NBSLOT_2        (0x4U << SAI_xSLOTR_NBSLOT_Pos)             /*!< 0x00000400 */
#define SAI_xSLOTR_NBSLOT_3        (0x8U << SAI_xSLOTR_NBSLOT_Pos)             /*!< 0x00000800 */

#define SAI_xSLOTR_SLOTEN_Pos      (16U)
#define SAI_xSLOTR_SLOTEN_Msk      (0xFFFFUL << SAI_xSLOTR_SLOTEN_Pos)         /*!< 0xFFFF0000 */
#define SAI_xSLOTR_SLOTEN          SAI_xSLOTR_SLOTEN_Msk                       /*!<SLOTEN[15:0] (Slot Enable)  */

/*******************  Bit definition for SAI_xIMR register  *******************/
#define SAI_xIMR_OVRUDRIE_Pos      (0U)
#define SAI_xIMR_OVRUDRIE_Msk      (0x1UL << SAI_xIMR_OVRUDRIE_Pos)            /*!< 0x00000001 */
#define SAI_xIMR_OVRUDRIE          SAI_xIMR_OVRUDRIE_Msk                       /*!<Overrun underrun interrupt enable                              */
#define SAI_xIMR_MUTEDETIE_Pos     (1U)
#define SAI_xIMR_MUTEDETIE_Msk     (0x1UL << SAI_xIMR_MUTEDETIE_Pos)           /*!< 0x00000002 */
#define SAI_xIMR_MUTEDETIE         SAI_xIMR_MUTEDETIE_Msk                      /*!<Mute detection interrupt enable                                */
#define SAI_xIMR_WCKCFGIE_Pos      (2U)
#define SAI_xIMR_WCKCFGIE_Msk      (0x1UL << SAI_xIMR_WCKCFGIE_Pos)            /*!< 0x00000004 */
#define SAI_xIMR_WCKCFGIE          SAI_xIMR_WCKCFGIE_Msk                       /*!<Wrong Clock Configuration interrupt enable                     */
#define SAI_xIMR_FREQIE_Pos        (3U)
#define SAI_xIMR_FREQIE_Msk        (0x1UL << SAI_xIMR_FREQIE_Pos)              /*!< 0x00000008 */
#define SAI_xIMR_FREQIE            SAI_xIMR_FREQIE_Msk                         /*!<FIFO request interrupt enable                                  */
#define SAI_xIMR_CNRDYIE_Pos       (4U)
#define SAI_xIMR_CNRDYIE_Msk       (0x1UL << SAI_xIMR_CNRDYIE_Pos)             /*!< 0x00000010 */
#define SAI_xIMR_CNRDYIE           SAI_xIMR_CNRDYIE_Msk                        /*!<Codec not ready interrupt enable                               */
#define SAI_xIMR_AFSDETIE_Pos      (5U)
#define SAI_xIMR_AFSDETIE_Msk      (0x1UL << SAI_xIMR_AFSDETIE_Pos)            /*!< 0x00000020 */
#define SAI_xIMR_AFSDETIE          SAI_xIMR_AFSDETIE_Msk                       /*!<Anticipated frame synchronization detection interrupt enable   */
#define SAI_xIMR_LFSDETIE_Pos      (6U)
#define SAI_xIMR_LFSDETIE_Msk      (0x1UL << SAI_xIMR_LFSDETIE_Pos)            /*!< 0x00000040 */
#define SAI_xIMR_LFSDETIE          SAI_xIMR_LFSDETIE_Msk                       /*!<Late frame synchronization detection interrupt enable          */

/********************  Bit definition for SAI_xSR register  *******************/
#define SAI_xSR_OVRUDR_Pos         (0U)
#define SAI_xSR_OVRUDR_Msk         (0x1UL << SAI_xSR_OVRUDR_Pos)               /*!< 0x00000001 */
#define SAI_xSR_OVRUDR             SAI_xSR_OVRUDR_Msk                          /*!<Overrun underrun                               */
#define SAI_xSR_MUTEDET_Pos        (1U)
#define SAI_xSR_MUTEDET_Msk        (0x1UL << SAI_xSR_MUTEDET_Pos)              /*!< 0x00000002 */
#define SAI_xSR_MUTEDET            SAI_xSR_MUTEDET_Msk                         /*!<Mute detection                                 */
#define SAI_xSR_WCKCFG_Pos         (2U)
#define SAI_xSR_WCKCFG_Msk         (0x1UL << SAI_xSR_WCKCFG_Pos)               /*!< 0x00000004 */
#define SAI_xSR_WCKCFG             SAI_xSR_WCKCFG_Msk                          /*!<Wrong Clock Configuration                      */
#define SAI_xSR_FREQ_Pos           (3U)
#define SAI_xSR_FREQ_Msk           (0x1UL << SAI_xSR_FREQ_Pos)                 /*!< 0x00000008 */
#define SAI_xSR_FREQ               SAI_xSR_FREQ_Msk                            /*!<FIFO request                                   */
#define SAI_xSR_CNRDY_Pos          (4U)
#define SAI_xSR_CNRDY_Msk          (0x1UL << SAI_xSR_CNRDY_Pos)                /*!< 0x00000010 */
#define SAI_xSR_CNRDY              SAI_xSR_CNRDY_Msk                           /*!<Codec not ready                                */
#define SAI_xSR_AFSDET_Pos         (5U)
#define SAI_xSR_AFSDET_Msk         (0x1UL << SAI_xSR_AFSDET_Pos)               /*!< 0x00000020 */
#define SAI_xSR_AFSDET             SAI_xSR_AFSDET_Msk                          /*!<Anticipated frame synchronization detection    */
#define SAI_xSR_LFSDET_Pos         (6U)
#define SAI_xSR_LFSDET_Msk         (0x1UL << SAI_xSR_LFSDET_Pos)               /*!< 0x00000040 */
#define SAI_xSR_LFSDET             SAI_xSR_LFSDET_Msk                          /*!<Late frame synchronization detection           */

#define SAI_xSR_FLVL_Pos           (16U)
#define SAI_xSR_FLVL_Msk           (0x7UL << SAI_xSR_FLVL_Pos)                 /*!< 0x00070000 */
#define SAI_xSR_FLVL               SAI_xSR_FLVL_Msk                            /*!<FLVL[2:0] (FIFO Level Threshold)               */
#define SAI_xSR_FLVL_0             (0x1U << SAI_xSR_FLVL_Pos)                  /*!< 0x00010000 */
#define SAI_xSR_FLVL_1             (0x2U << SAI_xSR_FLVL_Pos)                  /*!< 0x00020000 */
#define SAI_xSR_FLVL_2             (0x4U << SAI_xSR_FLVL_Pos)                  /*!< 0x00040000 */

/******************  Bit definition for SAI_xCLRFR register  ******************/
#define SAI_xCLRFR_COVRUDR_Pos     (0U)
#define SAI_xCLRFR_COVRUDR_Msk     (0x1UL << SAI_xCLRFR_COVRUDR_Pos)           /*!< 0x00000001 */
#define SAI_xCLRFR_COVRUDR         SAI_xCLRFR_COVRUDR_Msk                      /*!<Clear Overrun underrun                               */
#define SAI_xCLRFR_CMUTEDET_Pos    (1U)
#define SAI_xCLRFR_CMUTEDET_Msk    (0x1UL << SAI_xCLRFR_CMUTEDET_Pos)          /*!< 0x00000002 */
#define SAI_xCLRFR_CMUTEDET        SAI_xCLRFR_CMUTEDET_Msk                     /*!<Clear Mute detection                                 */
#define SAI_xCLRFR_CWCKCFG_Pos     (2U)
#define SAI_xCLRFR_CWCKCFG_Msk     (0x1UL << SAI_xCLRFR_CWCKCFG_Pos)           /*!< 0x00000004 */
#define SAI_xCLRFR_CWCKCFG         SAI_xCLRFR_CWCKCFG_Msk                      /*!<Clear Wrong Clock Configuration                      */
#define SAI_xCLRFR_CFREQ_Pos       (3U)
#define SAI_xCLRFR_CFREQ_Msk       (0x1UL << SAI_xCLRFR_CFREQ_Pos)             /*!< 0x00000008 */
#define SAI_xCLRFR_CFREQ           SAI_xCLRFR_CFREQ_Msk                        /*!<Clear FIFO request                                   */
#define SAI_xCLRFR_CCNRDY_Pos      (4U)
#define SAI_xCLRFR_CCNRDY_Msk      (0x1UL << SAI_xCLRFR_CCNRDY_Pos)            /*!< 0x00000010 */
#define SAI_xCLRFR_CCNRDY          SAI_xCLRFR_CCNRDY_Msk                       /*!<Clear Codec not ready                                */
#define SAI_xCLRFR_CAFSDET_Pos     (5U)
#define SAI_xCLRFR_CAFSDET_Msk     (0x1UL << SAI_xCLRFR_CAFSDET_Pos)           /*!< 0x00000020 */
#define SAI_xCLRFR_CAFSDET         SAI_xCLRFR_CAFSDET_Msk                      /*!<Clear Anticipated frame synchronization detection    */
#define SAI_xCLRFR_CLFSDET_Pos     (6U)
#define SAI_xCLRFR_CLFSDET_Msk     (0x1UL << SAI_xCLRFR_CLFSDET_Pos)           /*!< 0x00000040 */
#define SAI_xCLRFR_CLFSDET         SAI_xCLRFR_CLFSDET_Msk                      /*!<Clear Late frame synchronization detection           */

/******************  Bit definition for SAI_xDR register  *********************/
#define SAI_xDR_DATA_Pos           (0U)
#define SAI_xDR_DATA_Msk           (0xFFFFFFFFUL << SAI_xDR_DATA_Pos)          /*!< 0xFFFFFFFF */
#define SAI_xDR_DATA               SAI_xDR_DATA_Msk

/*******************  Bit definition for SAI_PDMCR register  ******************/
#define SAI_PDMCR_PDMEN_Pos        (0U)
#define SAI_PDMCR_PDMEN_Msk        (0x1UL << SAI_PDMCR_PDMEN_Pos)              /*!< 0x00000001 */
#define SAI_PDMCR_PDMEN            SAI_PDMCR_PDMEN_Msk                         /*!<PDM Enable                                          */

#define SAI_PDMCR_MICNBR_Pos       (4U)
#define SAI_PDMCR_MICNBR_Msk       (0x3UL << SAI_PDMCR_MICNBR_Pos)             /*!< 0x00000030 */
#define SAI_PDMCR_MICNBR           SAI_PDMCR_MICNBR_Msk                        /*!<Number of microphones                               */
#define SAI_PDMCR_MICNBR_0         (0x1U << SAI_PDMCR_MICNBR_Pos)              /*!< 0x00000010 */
#define SAI_PDMCR_MICNBR_1         (0x2U << SAI_PDMCR_MICNBR_Pos)              /*!< 0x00000020 */

#define SAI_PDMCR_CKEN1_Pos        (8U)
#define SAI_PDMCR_CKEN1_Msk        (0x1UL << SAI_PDMCR_CKEN1_Pos)              /*!< 0x00000100 */
#define SAI_PDMCR_CKEN1            SAI_PDMCR_CKEN1_Msk                         /*!<Clock enable of bitstream clock number 1            */
#define SAI_PDMCR_CKEN2_Pos        (9U)
#define SAI_PDMCR_CKEN2_Msk        (0x1UL << SAI_PDMCR_CKEN2_Pos)              /*!< 0x00000200 */
#define SAI_PDMCR_CKEN2            SAI_PDMCR_CKEN2_Msk                         /*!<Clock enable of bitstream clock number 2            */
#define SAI_PDMCR_CKEN3_Pos        (10U)
#define SAI_PDMCR_CKEN3_Msk        (0x1UL << SAI_PDMCR_CKEN3_Pos)              /*!< 0x00000400 */
#define SAI_PDMCR_CKEN3            SAI_PDMCR_CKEN3_Msk                         /*!<Clock enable of bitstream clock number 3            */
#define SAI_PDMCR_CKEN4_Pos        (11U)
#define SAI_PDMCR_CKEN4_Msk        (0x1UL << SAI_PDMCR_CKEN4_Pos)              /*!< 0x00000800 */
#define SAI_PDMCR_CKEN4            SAI_PDMCR_CKEN4_Msk                         /*!<Clock enable of bitstream clock number 4            */

/******************  Bit definition for SAI_PDMDLY register  ******************/
#define SAI_PDMDLY_DLYM1L_Pos      (0U)
#define SAI_PDMDLY_DLYM1L_Msk      (0x7UL << SAI_PDMDLY_DLYM1L_Pos)            /*!< 0x00000007 */
#define SAI_PDMDLY_DLYM1L          SAI_PDMDLY_DLYM1L_Msk                       /*!<DLYM1L[2:0] (Delay line adjust for left microphone of pair 1) */
#define SAI_PDMDLY_DLYM1L_0        (0x1U << SAI_PDMDLY_DLYM1L_Pos)             /*!< 0x00000001 */
#define SAI_PDMDLY_DLYM1L_1        (0x2U << SAI_PDMDLY_DLYM1L_Pos)             /*!< 0x00000002 */
#define SAI_PDMDLY_DLYM1L_2        (0x4U << SAI_PDMDLY_DLYM1L_Pos)             /*!< 0x00000004 */

#define SAI_PDMDLY_DLYM1R_Pos      (4U)
#define SAI_PDMDLY_DLYM1R_Msk      (0x7UL << SAI_PDMDLY_DLYM1R_Pos)            /*!< 0x00000070 */
#define SAI_PDMDLY_DLYM1R          SAI_PDMDLY_DLYM1R_Msk                       /*!<DLYM1R[2:0] (Delay line adjust for right microphone of pair 1) */
#define SAI_PDMDLY_DLYM1R_0        (0x1U << SAI_PDMDLY_DLYM1R_Pos)             /*!< 0x00000010 */
#define SAI_PDMDLY_DLYM1R_1        (0x2U << SAI_PDMDLY_DLYM1R_Pos)             /*!< 0x00000020 */
#define SAI_PDMDLY_DLYM1R_2        (0x4U << SAI_PDMDLY_DLYM1R_Pos)             /*!< 0x00000040 */

#define SAI_PDMDLY_DLYM2L_Pos      (8U)
#define SAI_PDMDLY_DLYM2L_Msk      (0x7UL << SAI_PDMDLY_DLYM2L_Pos)            /*!< 0x00000700 */
#define SAI_PDMDLY_DLYM2L          SAI_PDMDLY_DLYM2L_Msk                       /*!<DLYM2L[2:0] (Delay line adjust for left microphone of pair 2) */
#define SAI_PDMDLY_DLYM2L_0        (0x1U << SAI_PDMDLY_DLYM2L_Pos)             /*!< 0x00000100 */
#define SAI_PDMDLY_DLYM2L_1        (0x2U << SAI_PDMDLY_DLYM2L_Pos)             /*!< 0x00000200 */
#define SAI_PDMDLY_DLYM2L_2        (0x4U << SAI_PDMDLY_DLYM2L_Pos)             /*!< 0x00000400 */

#define SAI_PDMDLY_DLYM2R_Pos      (12U)
#define SAI_PDMDLY_DLYM2R_Msk      (0x7UL << SAI_PDMDLY_DLYM2R_Pos)            /*!< 0x00007000 */
#define SAI_PDMDLY_DLYM2R          SAI_PDMDLY_DLYM2R_Msk                       /*!<DLYM2R[2:0] (Delay line adjust for right microphone of pair 2)*/
#define SAI_PDMDLY_DLYM2R_0        (0x1U << SAI_PDMDLY_DLYM2R_Pos)             /*!< 0x00001000 */
#define SAI_PDMDLY_DLYM2R_1        (0x2U << SAI_PDMDLY_DLYM2R_Pos)             /*!< 0x00002000 */
#define SAI_PDMDLY_DLYM2R_2        (0x4U << SAI_PDMDLY_DLYM2R_Pos)             /*!< 0x00004000 */

#define SAI_PDMDLY_DLYM3L_Pos      (16U)
#define SAI_PDMDLY_DLYM3L_Msk      (0x7UL << SAI_PDMDLY_DLYM3L_Pos)            /*!< 0x00070000 */
#define SAI_PDMDLY_DLYM3L          SAI_PDMDLY_DLYM3L_Msk                       /*!<DLYM3L[2:0] (Delay line adjust for left microphone of pair 3)*/
#define SAI_PDMDLY_DLYM3L_0        (0x1U << SAI_PDMDLY_DLYM3L_Pos)             /*!< 0x00010000 */
#define SAI_PDMDLY_DLYM3L_1        (0x2U << SAI_PDMDLY_DLYM3L_Pos)             /*!< 0x00020000 */
#define SAI_PDMDLY_DLYM3L_2        (0x4U << SAI_PDMDLY_DLYM3L_Pos)             /*!< 0x00040000 */

#define SAI_PDMDLY_DLYM3R_Pos      (20U)
#define SAI_PDMDLY_DLYM3R_Msk      (0x7UL << SAI_PDMDLY_DLYM3R_Pos)            /*!< 0x00700000 */
#define SAI_PDMDLY_DLYM3R          SAI_PDMDLY_DLYM3R_Msk                       /*!<DLYM3R[2:0] (Delay line adjust for right microphone of pair 3)*/
#define SAI_PDMDLY_DLYM3R_0        (0x1U << SAI_PDMDLY_DLYM3R_Pos)             /*!< 0x00100000 */
#define SAI_PDMDLY_DLYM3R_1        (0x2U << SAI_PDMDLY_DLYM3R_Pos)             /*!< 0x00200000 */
#define SAI_PDMDLY_DLYM3R_2        (0x4U << SAI_PDMDLY_DLYM3R_Pos)             /*!< 0x00400000 */

#define SAI_PDMDLY_DLYM4L_Pos      (24U)
#define SAI_PDMDLY_DLYM4L_Msk      (0x7UL << SAI_PDMDLY_DLYM4L_Pos)            /*!< 0x07000000 */
#define SAI_PDMDLY_DLYM4L          SAI_PDMDLY_DLYM4L_Msk                       /*!<DLYM4L[2:0] (Delay line adjust for left microphone of pair 4)*/
#define SAI_PDMDLY_DLYM4L_0        (0x1U << SAI_PDMDLY_DLYM4L_Pos)             /*!< 0x01000000 */
#define SAI_PDMDLY_DLYM4L_1        (0x2U << SAI_PDMDLY_DLYM4L_Pos)             /*!< 0x02000000 */
#define SAI_PDMDLY_DLYM4L_2        (0x4U << SAI_PDMDLY_DLYM4L_Pos)             /*!< 0x04000000 */

#define SAI_PDMDLY_DLYM4R_Pos      (28U)
#define SAI_PDMDLY_DLYM4R_Msk      (0x7UL << SAI_PDMDLY_DLYM4R_Pos)            /*!< 0x70000000 */
#define SAI_PDMDLY_DLYM4R          SAI_PDMDLY_DLYM4R_Msk                       /*!<DLYM4R[2:0] (Delay line adjust for right microphone of pair 4)*/
#define SAI_PDMDLY_DLYM4R_0        (0x1U << SAI_PDMDLY_DLYM4R_Pos)             /*!< 0x10000000 */
#define SAI_PDMDLY_DLYM4R_1        (0x2U << SAI_PDMDLY_DLYM4R_Pos)             /*!< 0x20000000 */
#define SAI_PDMDLY_DLYM4R_2        (0x4U << SAI_PDMDLY_DLYM4R_Pos)             /*!< 0x40000000 */

/**********************  Bit definition for SAI_HWCFGR register  ***************/
#define SAI_HWCFGR_FIFO_SIZE_Pos      (0U)
#define SAI_HWCFGR_FIFO_SIZE_Msk      (0xFFU << SAI_HWCFGR_FIFO_SIZE_Pos)          /*!< 0x000000FF */
#define SAI_HWCFGR_FIFO_SIZE          SAI_HWCFGR_FIFO_SIZE_Msk                    /*!< FIFO size for SAIA and SAIB */
#define SAI_HWCFGR_SPDIF_PDM_Pos      (8U)
#define SAI_HWCFGR_SPDIF_PDM_Msk      (0xFU << SAI_HWCFGR_SPDIF_PDM_Pos)          /*!< 0x00000F00 */
#define SAI_HWCFGR_SPDIF_PDM          SAI_HWCFGR_SPDIF_PDM_Msk                    /*!< Support of SPDIF-OUT and PDM interfaces */
#define SAI_HWCFGR_OPTION_REGOUT_Pos  (12U)
#define SAI_HWCFGR_OPTION_REGOUT_Msk  (0xFFU << SAI_HWCFGR_OPTION_REGOUT_Pos)     /*!< 0x000FF000 */
#define SAI_HWCFGR_OPTION_REGOUT      SAI_HWCFGR_OPTION_REGOUT_Msk                /*!< Support of SAI_IOR register */

/**********************  Bit definition for SAI_VERR register  *****************/
#define SAI_VERR_MINREV_Pos      (0U)
#define SAI_VERR_MINREV_Msk      (0xFU << SAI_VERR_MINREV_Pos)               /*!< 0x0000000F */
#define SAI_VERR_MINREV          SAI_VERR_MINREV_Msk                         /*!< Minor Revision number */
#define SAI_VERR_MAJREV_Pos      (4U)
#define SAI_VERR_MAJREV_Msk      (0xFU << SAI_VERR_MAJREV_Pos)               /*!< 0x000000F0 */
#define SAI_VERR_MAJREV          SAI_VERR_MAJREV_Msk                         /*!< Major Revision number */

/**********************  Bit definition for SAI_IPIDR register  ****************/
#define SAI_IPIDR_IPID_Pos       (0U)
#define SAI_IPIDR_IPID_Msk       (0xFFFFFFFFU << SAI_IPIDR_IPID_Pos)         /*!< 0xFFFFFFFF */
#define SAI_IPIDR_IPID           SAI_IPIDR_IPID_Msk                          /*!< IP Identification */

/**********************  Bit definition for SAI_SIDR register  *****************/
#define SAI_SIDR_SID_Pos         (0U)
#define SAI_SIDR_SID_Msk         (0xFFFFFFFFU << SAI_SIDR_SID_Pos)           /*!< 0xFFFFFFFF */
#define SAI_SIDR_SID             SAI_SIDR_SID_Msk                            /*!< IP size identification */

/******************************************************************************/
/*                                                                            */
/*                          LCD Controller (LCD)                              */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for LCD_CR register  *********************/
#define LCD_CR_LCDEN_Pos            (0U)
#define LCD_CR_LCDEN_Msk            (0x1U << LCD_CR_LCDEN_Pos)                 /*!< 0x00000001 */
#define LCD_CR_LCDEN                LCD_CR_LCDEN_Msk                           /*!< LCD Enable Bit */
#define LCD_CR_VSEL_Pos             (1U)
#define LCD_CR_VSEL_Msk             (0x1U << LCD_CR_VSEL_Pos)                  /*!< 0x00000002 */
#define LCD_CR_VSEL                 LCD_CR_VSEL_Msk                            /*!< Voltage source selector Bit */

#define LCD_CR_DUTY_Pos             (2U)
#define LCD_CR_DUTY_Msk             (0x7U << LCD_CR_DUTY_Pos)                  /*!< 0x0000001C */
#define LCD_CR_DUTY                 LCD_CR_DUTY_Msk                            /*!< DUTY[2:0] bits (Duty selector) */
#define LCD_CR_DUTY_0               (0x1U << LCD_CR_DUTY_Pos)                  /*!< 0x00000004 */
#define LCD_CR_DUTY_1               (0x2U << LCD_CR_DUTY_Pos)                  /*!< 0x00000008 */
#define LCD_CR_DUTY_2               (0x4U << LCD_CR_DUTY_Pos)                  /*!< 0x00000010 */

#define LCD_CR_BIAS_Pos             (5U)
#define LCD_CR_BIAS_Msk             (0x3U << LCD_CR_BIAS_Pos)                  /*!< 0x00000060 */
#define LCD_CR_BIAS                 LCD_CR_BIAS_Msk                            /*!< BIAS[1:0] bits (Bias selector) */
#define LCD_CR_BIAS_0               (0x1U << LCD_CR_BIAS_Pos)                  /*!< 0x00000020 */
#define LCD_CR_BIAS_1               (0x2U << LCD_CR_BIAS_Pos)                  /*!< 0x00000040 */

#define LCD_CR_MUX_SEG_Pos          (7U)
#define LCD_CR_MUX_SEG_Msk          (0x1U << LCD_CR_MUX_SEG_Pos)               /*!< 0x00000080 */
#define LCD_CR_MUX_SEG              LCD_CR_MUX_SEG_Msk                         /*!< Mux Segment Enable Bit */
#define LCD_CR_BUFEN_Pos            (8U)
#define LCD_CR_BUFEN_Msk            (0x1U << LCD_CR_BUFEN_Pos)                 /*!< 0x00000100 */
#define LCD_CR_BUFEN                LCD_CR_BUFEN_Msk                           /*!< Voltage output buffer enable */
/*******************  Bit definition for LCD_FCR register  ********************/
#define LCD_FCR_HD_Pos              (0U)
#define LCD_FCR_HD_Msk              (0x1U << LCD_FCR_HD_Pos)                   /*!< 0x00000001 */
#define LCD_FCR_HD                  LCD_FCR_HD_Msk                             /*!< High Drive Enable Bit */
#define LCD_FCR_SOFIE_Pos           (1U)
#define LCD_FCR_SOFIE_Msk           (0x1U << LCD_FCR_SOFIE_Pos)                /*!< 0x00000002 */
#define LCD_FCR_SOFIE               LCD_FCR_SOFIE_Msk                          /*!< Start of Frame Interrupt Enable Bit */
#define LCD_FCR_UDDIE_Pos           (3U)
#define LCD_FCR_UDDIE_Msk           (0x1U << LCD_FCR_UDDIE_Pos)                /*!< 0x00000008 */
#define LCD_FCR_UDDIE               LCD_FCR_UDDIE_Msk                          /*!< Update Display Done Interrupt Enable Bit */

#define LCD_FCR_PON_Pos             (4U)
#define LCD_FCR_PON_Msk             (0x7U << LCD_FCR_PON_Pos)                  /*!< 0x00000070 */
#define LCD_FCR_PON                 LCD_FCR_PON_Msk                            /*!< PON[2:0] bits (Puls ON Duration) */
#define LCD_FCR_PON_0               (0x1U << LCD_FCR_PON_Pos)                  /*!< 0x00000010 */
#define LCD_FCR_PON_1               (0x2U << LCD_FCR_PON_Pos)                  /*!< 0x00000020 */
#define LCD_FCR_PON_2               (0x4U << LCD_FCR_PON_Pos)                  /*!< 0x00000040 */

#define LCD_FCR_DEAD_Pos            (7U)
#define LCD_FCR_DEAD_Msk            (0x7U << LCD_FCR_DEAD_Pos)                 /*!< 0x00000380 */
#define LCD_FCR_DEAD                LCD_FCR_DEAD_Msk                           /*!< DEAD[2:0] bits (DEAD Time) */
#define LCD_FCR_DEAD_0              (0x1U << LCD_FCR_DEAD_Pos)                 /*!< 0x00000080 */
#define LCD_FCR_DEAD_1              (0x2U << LCD_FCR_DEAD_Pos)                 /*!< 0x00000100 */
#define LCD_FCR_DEAD_2              (0x4U << LCD_FCR_DEAD_Pos)                 /*!< 0x00000200 */

#define LCD_FCR_CC_Pos              (10U)
#define LCD_FCR_CC_Msk              (0x7U << LCD_FCR_CC_Pos)                   /*!< 0x00001C00 */
#define LCD_FCR_CC                  LCD_FCR_CC_Msk                             /*!< CC[2:0] bits (Contrast Control) */
#define LCD_FCR_CC_0                (0x1U << LCD_FCR_CC_Pos)                   /*!< 0x00000400 */
#define LCD_FCR_CC_1                (0x2U << LCD_FCR_CC_Pos)                   /*!< 0x00000800 */
#define LCD_FCR_CC_2                (0x4U << LCD_FCR_CC_Pos)                   /*!< 0x00001000 */

#define LCD_FCR_BLINKF_Pos          (13U)
#define LCD_FCR_BLINKF_Msk          (0x7U << LCD_FCR_BLINKF_Pos)               /*!< 0x0000E000 */
#define LCD_FCR_BLINKF              LCD_FCR_BLINKF_Msk                         /*!< BLINKF[2:0] bits (Blink Frequency) */
#define LCD_FCR_BLINKF_0            (0x1U << LCD_FCR_BLINKF_Pos)               /*!< 0x00002000 */
#define LCD_FCR_BLINKF_1            (0x2U << LCD_FCR_BLINKF_Pos)               /*!< 0x00004000 */
#define LCD_FCR_BLINKF_2            (0x4U << LCD_FCR_BLINKF_Pos)               /*!< 0x00008000 */

#define LCD_FCR_BLINK_Pos           (16U)
#define LCD_FCR_BLINK_Msk           (0x3U << LCD_FCR_BLINK_Pos)                /*!< 0x00030000 */
#define LCD_FCR_BLINK               LCD_FCR_BLINK_Msk                          /*!< BLINK[1:0] bits (Blink Enable) */
#define LCD_FCR_BLINK_0             (0x1U << LCD_FCR_BLINK_Pos)                /*!< 0x00010000 */
#define LCD_FCR_BLINK_1             (0x2U << LCD_FCR_BLINK_Pos)                /*!< 0x00020000 */

#define LCD_FCR_DIV_Pos             (18U)
#define LCD_FCR_DIV_Msk             (0xFU << LCD_FCR_DIV_Pos)                  /*!< 0x003C0000 */
#define LCD_FCR_DIV                 LCD_FCR_DIV_Msk                            /*!< DIV[3:0] bits (Divider) */
#define LCD_FCR_PS_Pos              (22U)
#define LCD_FCR_PS_Msk              (0xFU << LCD_FCR_PS_Pos)                   /*!< 0x03C00000 */
#define LCD_FCR_PS                  LCD_FCR_PS_Msk                             /*!< PS[3:0] bits (Prescaler) */

/*******************  Bit definition for LCD_SR register  *********************/
#define LCD_SR_ENS_Pos              (0U)
#define LCD_SR_ENS_Msk              (0x1U << LCD_SR_ENS_Pos)                   /*!< 0x00000001 */
#define LCD_SR_ENS                  LCD_SR_ENS_Msk                             /*!< LCD Enabled Bit */
#define LCD_SR_SOF_Pos              (1U)
#define LCD_SR_SOF_Msk              (0x1U << LCD_SR_SOF_Pos)                   /*!< 0x00000002 */
#define LCD_SR_SOF                  LCD_SR_SOF_Msk                             /*!< Start Of Frame Flag Bit */
#define LCD_SR_UDR_Pos              (2U)
#define LCD_SR_UDR_Msk              (0x1U << LCD_SR_UDR_Pos)                   /*!< 0x00000004 */
#define LCD_SR_UDR                  LCD_SR_UDR_Msk                             /*!< Update Display Request Bit */
#define LCD_SR_UDD_Pos              (3U)
#define LCD_SR_UDD_Msk              (0x1U << LCD_SR_UDD_Pos)                   /*!< 0x00000008 */
#define LCD_SR_UDD                  LCD_SR_UDD_Msk                             /*!< Update Display Done Flag Bit */
#define LCD_SR_RDY_Pos              (4U)
#define LCD_SR_RDY_Msk              (0x1U << LCD_SR_RDY_Pos)                   /*!< 0x00000010 */
#define LCD_SR_RDY                  LCD_SR_RDY_Msk                             /*!< Ready Flag Bit */
#define LCD_SR_FCRSR_Pos            (5U)
#define LCD_SR_FCRSR_Msk            (0x1U << LCD_SR_FCRSR_Pos)                 /*!< 0x00000020 */
#define LCD_SR_FCRSR                LCD_SR_FCRSR_Msk                           /*!< LCD FCR Register Synchronization Flag Bit */

/*******************  Bit definition for LCD_CLR register  ********************/
#define LCD_CLR_SOFC_Pos            (1U)
#define LCD_CLR_SOFC_Msk            (0x1U << LCD_CLR_SOFC_Pos)                 /*!< 0x00000002 */
#define LCD_CLR_SOFC                LCD_CLR_SOFC_Msk                           /*!< Start Of Frame Flag Clear Bit */
#define LCD_CLR_UDDC_Pos            (3U)
#define LCD_CLR_UDDC_Msk            (0x1U << LCD_CLR_UDDC_Pos)                 /*!< 0x00000008 */
#define LCD_CLR_UDDC                LCD_CLR_UDDC_Msk                           /*!< Update Display Done Flag Clear Bit */

/*******************  Bit definition for LCD_RAM register  ********************/
#define LCD_RAM_SEGMENT_DATA_Pos    (0U)
#define LCD_RAM_SEGMENT_DATA_Msk    (0xFFFFFFFFU << LCD_RAM_SEGMENT_DATA_Pos)  /*!< 0xFFFFFFFF */
#define LCD_RAM_SEGMENT_DATA        LCD_RAM_SEGMENT_DATA_Msk                   /*!< Segment Data Bits */

/******************************************************************************/
/*                                                                            */
/*                           SDMMC Interface                                  */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for SDMMC_POWER register  ******************/
#define SDMMC_POWER_PWRCTRL_Pos         (0U)
#define SDMMC_POWER_PWRCTRL_Msk         (0x3U << SDMMC_POWER_PWRCTRL_Pos)      /*!< 0x00000003 */
#define SDMMC_POWER_PWRCTRL             SDMMC_POWER_PWRCTRL_Msk                /*!<PWRCTRL[1:0] bits (Power supply control bits) */
#define SDMMC_POWER_PWRCTRL_0           (0x1U << SDMMC_POWER_PWRCTRL_Pos)      /*!< 0x00000001 */
#define SDMMC_POWER_PWRCTRL_1           (0x2U << SDMMC_POWER_PWRCTRL_Pos)      /*!< 0x00000002 */
#define SDMMC_POWER_VSWITCH_Pos         (2U)
#define SDMMC_POWER_VSWITCH_Msk         (0x1U << SDMMC_POWER_VSWITCH_Pos)      /*!< 0x00000004 */
#define SDMMC_POWER_VSWITCH             SDMMC_POWER_VSWITCH_Msk                /*!<Voltage switch sequence start */
#define SDMMC_POWER_VSWITCHEN_Pos       (3U)
#define SDMMC_POWER_VSWITCHEN_Msk       (0x1U << SDMMC_POWER_VSWITCHEN_Pos)    /*!< 0x00000008 */
#define SDMMC_POWER_VSWITCHEN           SDMMC_POWER_VSWITCHEN_Msk              /*!<Voltage switch procedure enable */
#define SDMMC_POWER_DIRPOL_Pos          (4U)
#define SDMMC_POWER_DIRPOL_Msk          (0x1U << SDMMC_POWER_DIRPOL_Pos)       /*!< 0x00000010 */
#define SDMMC_POWER_DIRPOL              SDMMC_POWER_DIRPOL_Msk                 /*!<Data and Command direction signals polarity selection */

/******************  Bit definition for SDMMC_CLKCR register  ******************/
#define SDMMC_CLKCR_CLKDIV_Pos          (0U)
#define SDMMC_CLKCR_CLKDIV_Msk          (0x3FFU << SDMMC_CLKCR_CLKDIV_Pos)     /*!< 0x000003FF */
#define SDMMC_CLKCR_CLKDIV              SDMMC_CLKCR_CLKDIV_Msk                 /*!<Clock divide factor             */
#define SDMMC_CLKCR_PWRSAV_Pos          (12U)
#define SDMMC_CLKCR_PWRSAV_Msk          (0x1U << SDMMC_CLKCR_PWRSAV_Pos)       /*!< 0x00001000 */
#define SDMMC_CLKCR_PWRSAV              SDMMC_CLKCR_PWRSAV_Msk                 /*!<Power saving configuration bit  */

#define SDMMC_CLKCR_WIDBUS_Pos          (14U)
#define SDMMC_CLKCR_WIDBUS_Msk          (0x3U << SDMMC_CLKCR_WIDBUS_Pos)       /*!< 0x0000C000 */
#define SDMMC_CLKCR_WIDBUS              SDMMC_CLKCR_WIDBUS_Msk                 /*!<WIDBUS[1:0] bits (Wide bus mode enable bit) */
#define SDMMC_CLKCR_WIDBUS_0            (0x1U << SDMMC_CLKCR_WIDBUS_Pos)       /*!< 0x00004000 */
#define SDMMC_CLKCR_WIDBUS_1            (0x2U << SDMMC_CLKCR_WIDBUS_Pos)       /*!< 0x00008000 */

#define SDMMC_CLKCR_NEGEDGE_Pos         (16U)
#define SDMMC_CLKCR_NEGEDGE_Msk         (0x1U << SDMMC_CLKCR_NEGEDGE_Pos)      /*!< 0x00010000 */
#define SDMMC_CLKCR_NEGEDGE             SDMMC_CLKCR_NEGEDGE_Msk                /*!<SDMMC_CK dephasing selection bit */
#define SDMMC_CLKCR_HWFC_EN_Pos         (17U)
#define SDMMC_CLKCR_HWFC_EN_Msk         (0x1U << SDMMC_CLKCR_HWFC_EN_Pos)      /*!< 0x00020000 */
#define SDMMC_CLKCR_HWFC_EN             SDMMC_CLKCR_HWFC_EN_Msk                /*!<HW Flow Control enable           */
#define SDMMC_CLKCR_DDR_Pos             (18U)
#define SDMMC_CLKCR_DDR_Msk             (0x1U << SDMMC_CLKCR_DDR_Pos)          /*!< 0x00040000 */
#define SDMMC_CLKCR_DDR                 SDMMC_CLKCR_DDR_Msk                    /*!<Data rate signaling selection    */
#define SDMMC_CLKCR_BUSSPEED_Pos        (19U)
#define SDMMC_CLKCR_BUSSPEED_Msk        (0x1U << SDMMC_CLKCR_BUSSPEED_Pos)     /*!< 0x00080000 */
#define SDMMC_CLKCR_BUSSPEED            SDMMC_CLKCR_BUSSPEED_Msk               /*!<Bus speed mode selection         */
#define SDMMC_CLKCR_SELCLKRX_Pos        (20U)
#define SDMMC_CLKCR_SELCLKRX_Msk        (0x3U << SDMMC_CLKCR_SELCLKRX_Pos)     /*!< 0x00300000 */
#define SDMMC_CLKCR_SELCLKRX            SDMMC_CLKCR_SELCLKRX_Msk               /*!<SELCLKRX[1:0] bits (Receive clock selection) */
#define SDMMC_CLKCR_SELCLKRX_0          (0x1U << SDMMC_CLKCR_SELCLKRX_Pos)     /*!< 0x00100000 */
#define SDMMC_CLKCR_SELCLKRX_1          (0x2U << SDMMC_CLKCR_SELCLKRX_Pos)     /*!< 0x00200000 */

/*******************  Bit definition for SDMMC_ARG register  *******************/
#define SDMMC_ARG_CMDARG_Pos            (0U)
#define SDMMC_ARG_CMDARG_Msk            (0xFFFFFFFFU << SDMMC_ARG_CMDARG_Pos)  /*!< 0xFFFFFFFF */
#define SDMMC_ARG_CMDARG                SDMMC_ARG_CMDARG_Msk                   /*!<Command argument */

/*******************  Bit definition for SDMMC_CMD register  *******************/
#define SDMMC_CMD_CMDINDEX_Pos          (0U)
#define SDMMC_CMD_CMDINDEX_Msk          (0x3FU << SDMMC_CMD_CMDINDEX_Pos)      /*!< 0x0000003F */
#define SDMMC_CMD_CMDINDEX              SDMMC_CMD_CMDINDEX_Msk                 /*!<Command Index                               */
#define SDMMC_CMD_CMDTRANS_Pos          (6U)
#define SDMMC_CMD_CMDTRANS_Msk          (0x1U << SDMMC_CMD_CMDTRANS_Pos)       /*!< 0x00000040 */
#define SDMMC_CMD_CMDTRANS              SDMMC_CMD_CMDTRANS_Msk                 /*!<CPSM Treats command as a Data Transfer      */
#define SDMMC_CMD_CMDSTOP_Pos           (7U)
#define SDMMC_CMD_CMDSTOP_Msk           (0x1U << SDMMC_CMD_CMDSTOP_Pos)        /*!< 0x00000080 */
#define SDMMC_CMD_CMDSTOP               SDMMC_CMD_CMDSTOP_Msk                  /*!<CPSM Treats command as a Stop               */

#define SDMMC_CMD_WAITRESP_Pos          (8U)
#define SDMMC_CMD_WAITRESP_Msk          (0x3U << SDMMC_CMD_WAITRESP_Pos)       /*!< 0x00000300 */
#define SDMMC_CMD_WAITRESP              SDMMC_CMD_WAITRESP_Msk                 /*!<WAITRESP[1:0] bits (Wait for response bits) */
#define SDMMC_CMD_WAITRESP_0            (0x1U << SDMMC_CMD_WAITRESP_Pos)       /*!< 0x00000100 */
#define SDMMC_CMD_WAITRESP_1            (0x2U << SDMMC_CMD_WAITRESP_Pos)       /*!< 0x00000200 */

#define SDMMC_CMD_WAITINT_Pos           (10U)
#define SDMMC_CMD_WAITINT_Msk           (0x1U << SDMMC_CMD_WAITINT_Pos)        /*!< 0x00000400 */
#define SDMMC_CMD_WAITINT               SDMMC_CMD_WAITINT_Msk                  /*!<CPSM Waits for Interrupt Request                               */
#define SDMMC_CMD_WAITPEND_Pos          (11U)
#define SDMMC_CMD_WAITPEND_Msk          (0x1U << SDMMC_CMD_WAITPEND_Pos)       /*!< 0x00000800 */
#define SDMMC_CMD_WAITPEND              SDMMC_CMD_WAITPEND_Msk                 /*!<CPSM Waits for ends of data transfer (CmdPend internal signal) */
#define SDMMC_CMD_CPSMEN_Pos            (12U)
#define SDMMC_CMD_CPSMEN_Msk            (0x1U << SDMMC_CMD_CPSMEN_Pos)         /*!< 0x00001000 */
#define SDMMC_CMD_CPSMEN                SDMMC_CMD_CPSMEN_Msk                   /*!<Command path state machine (CPSM) Enable bit                   */
#define SDMMC_CMD_DTHOLD_Pos            (13U)
#define SDMMC_CMD_DTHOLD_Msk            (0x1U << SDMMC_CMD_DTHOLD_Pos)         /*!< 0x00002000 */
#define SDMMC_CMD_DTHOLD                SDMMC_CMD_DTHOLD_Msk                   /*!<Hold new data block transmission and reception in the DPSM     */
#define SDMMC_CMD_BOOTMODE_Pos          (14U)
#define SDMMC_CMD_BOOTMODE_Msk          (0x1U << SDMMC_CMD_BOOTMODE_Pos)       /*!< 0x00004000 */
#define SDMMC_CMD_BOOTMODE              SDMMC_CMD_BOOTMODE_Msk                 /*!<Boot mode                                                      */
#define SDMMC_CMD_BOOTEN_Pos            (15U)
#define SDMMC_CMD_BOOTEN_Msk            (0x1U << SDMMC_CMD_BOOTEN_Pos)         /*!< 0x00008000 */
#define SDMMC_CMD_BOOTEN                SDMMC_CMD_BOOTEN_Msk                   /*!<Enable Boot mode procedure                                     */
#define SDMMC_CMD_CMDSUSPEND_Pos        (16U)
#define SDMMC_CMD_CMDSUSPEND_Msk        (0x1U << SDMMC_CMD_CMDSUSPEND_Pos)    /*!< 0x00010000 */
#define SDMMC_CMD_CMDSUSPEND            SDMMC_CMD_CMDSUSPEND_Msk              /*!<CPSM Treats command as a Suspend or Resume command             */

/*****************  Bit definition for SDMMC_RESPCMD register  *****************/
#define SDMMC_RESPCMD_RESPCMD_Pos       (0U)
#define SDMMC_RESPCMD_RESPCMD_Msk       (0x3FU << SDMMC_RESPCMD_RESPCMD_Pos)   /*!< 0x0000003F */
#define SDMMC_RESPCMD_RESPCMD           SDMMC_RESPCMD_RESPCMD_Msk              /*!<Response command index */

/******************  Bit definition for SDMMC_RESP0 register  ******************/
#define SDMMC_RESP0_CARDSTATUS0_Pos     (0U)
#define SDMMC_RESP0_CARDSTATUS0_Msk     (0xFFFFFFFFU << SDMMC_RESP0_CARDSTATUS0_Pos) /*!< 0xFFFFFFFF */
#define SDMMC_RESP0_CARDSTATUS0         SDMMC_RESP0_CARDSTATUS0_Msk            /*!<Card Status */

/******************  Bit definition for SDMMC_RESP1 register  ******************/
#define SDMMC_RESP1_CARDSTATUS1_Pos     (0U)
#define SDMMC_RESP1_CARDSTATUS1_Msk     (0xFFFFFFFFU << SDMMC_RESP1_CARDSTATUS1_Pos) /*!< 0xFFFFFFFF */
#define SDMMC_RESP1_CARDSTATUS1         SDMMC_RESP1_CARDSTATUS1_Msk            /*!<Card Status */

/******************  Bit definition for SDMMC_RESP2 register  ******************/
#define SDMMC_RESP2_CARDSTATUS2_Pos     (0U)
#define SDMMC_RESP2_CARDSTATUS2_Msk     (0xFFFFFFFFU << SDMMC_RESP2_CARDSTATUS2_Pos) /*!< 0xFFFFFFFF */
#define SDMMC_RESP2_CARDSTATUS2         SDMMC_RESP2_CARDSTATUS2_Msk            /*!<Card Status */

/******************  Bit definition for SDMMC_RESP3 register  ******************/
#define SDMMC_RESP3_CARDSTATUS3_Pos     (0U)
#define SDMMC_RESP3_CARDSTATUS3_Msk     (0xFFFFFFFFU << SDMMC_RESP3_CARDSTATUS3_Pos) /*!< 0xFFFFFFFF */
#define SDMMC_RESP3_CARDSTATUS3         SDMMC_RESP3_CARDSTATUS3_Msk            /*!<Card Status */

/******************  Bit definition for SDMMC_RESP4 register  ******************/
#define SDMMC_RESP4_CARDSTATUS4_Pos     (0U)
#define SDMMC_RESP4_CARDSTATUS4_Msk     (0xFFFFFFFFU << SDMMC_RESP4_CARDSTATUS4_Pos) /*!< 0xFFFFFFFF */
#define SDMMC_RESP4_CARDSTATUS4         SDMMC_RESP4_CARDSTATUS4_Msk            /*!<Card Status */

/******************  Bit definition for SDMMC_DTIMER register  *****************/
#define SDMMC_DTIMER_DATATIME_Pos       (0U)
#define SDMMC_DTIMER_DATATIME_Msk       (0xFFFFFFFFU << SDMMC_DTIMER_DATATIME_Pos) /*!< 0xFFFFFFFF */
#define SDMMC_DTIMER_DATATIME           SDMMC_DTIMER_DATATIME_Msk              /*!<Data timeout period. */

/******************  Bit definition for SDMMC_DLEN register  *******************/
#define SDMMC_DLEN_DATALENGTH_Pos       (0U)
#define SDMMC_DLEN_DATALENGTH_Msk       (0x1FFFFFFU << SDMMC_DLEN_DATALENGTH_Pos) /*!< 0x01FFFFFF */
#define SDMMC_DLEN_DATALENGTH           SDMMC_DLEN_DATALENGTH_Msk              /*!<Data length value    */

/******************  Bit definition for SDMMC_DCTRL register  ******************/
#define SDMMC_DCTRL_DTEN_Pos            (0U)
#define SDMMC_DCTRL_DTEN_Msk            (0x1U << SDMMC_DCTRL_DTEN_Pos)         /*!< 0x00000001 */
#define SDMMC_DCTRL_DTEN                SDMMC_DCTRL_DTEN_Msk                   /*!<Data transfer enabled bit                */
#define SDMMC_DCTRL_DTDIR_Pos           (1U)
#define SDMMC_DCTRL_DTDIR_Msk           (0x1U << SDMMC_DCTRL_DTDIR_Pos)        /*!< 0x00000002 */
#define SDMMC_DCTRL_DTDIR               SDMMC_DCTRL_DTDIR_Msk                  /*!<Data transfer direction selection        */
#define SDMMC_DCTRL_DTMODE_Pos          (2U)
#define SDMMC_DCTRL_DTMODE_Msk          (0x3U << SDMMC_DCTRL_DTMODE_Pos)       /*!< 0x0000000C */
#define SDMMC_DCTRL_DTMODE              SDMMC_DCTRL_DTMODE_Msk                 /*!<DTMODE[1:0] Data transfer mode selection */
#define SDMMC_DCTRL_DTMODE_0            (0x1U << SDMMC_DCTRL_DTMODE_Pos)       /*!< 0x0004 */
#define SDMMC_DCTRL_DTMODE_1            (0x2U << SDMMC_DCTRL_DTMODE_Pos)       /*!< 0x0008 */

#define SDMMC_DCTRL_DBLOCKSIZE_Pos      (4U)
#define SDMMC_DCTRL_DBLOCKSIZE_Msk      (0xFU << SDMMC_DCTRL_DBLOCKSIZE_Pos)   /*!< 0x000000F0 */
#define SDMMC_DCTRL_DBLOCKSIZE          SDMMC_DCTRL_DBLOCKSIZE_Msk             /*!<DBLOCKSIZE[3:0] bits (Data block size) */
#define SDMMC_DCTRL_DBLOCKSIZE_0        (0x1U << SDMMC_DCTRL_DBLOCKSIZE_Pos)   /*!< 0x0010 */
#define SDMMC_DCTRL_DBLOCKSIZE_1        (0x2U << SDMMC_DCTRL_DBLOCKSIZE_Pos)   /*!< 0x0020 */
#define SDMMC_DCTRL_DBLOCKSIZE_2        (0x4U << SDMMC_DCTRL_DBLOCKSIZE_Pos)   /*!< 0x0040 */
#define SDMMC_DCTRL_DBLOCKSIZE_3        (0x8U << SDMMC_DCTRL_DBLOCKSIZE_Pos)   /*!< 0x0080 */

#define SDMMC_DCTRL_RWSTART_Pos         (8U)
#define SDMMC_DCTRL_RWSTART_Msk         (0x1U << SDMMC_DCTRL_RWSTART_Pos)      /*!< 0x00000100 */
#define SDMMC_DCTRL_RWSTART             SDMMC_DCTRL_RWSTART_Msk                /*!<Read wait start                                 */
#define SDMMC_DCTRL_RWSTOP_Pos          (9U)
#define SDMMC_DCTRL_RWSTOP_Msk          (0x1U << SDMMC_DCTRL_RWSTOP_Pos)       /*!< 0x00000200 */
#define SDMMC_DCTRL_RWSTOP              SDMMC_DCTRL_RWSTOP_Msk                 /*!<Read wait stop                                  */
#define SDMMC_DCTRL_RWMOD_Pos           (10U)
#define SDMMC_DCTRL_RWMOD_Msk           (0x1U << SDMMC_DCTRL_RWMOD_Pos)        /*!< 0x00000400 */
#define SDMMC_DCTRL_RWMOD               SDMMC_DCTRL_RWMOD_Msk                  /*!<Read wait mode                                  */
#define SDMMC_DCTRL_SDIOEN_Pos          (11U)
#define SDMMC_DCTRL_SDIOEN_Msk          (0x1U << SDMMC_DCTRL_SDIOEN_Pos)       /*!< 0x00000800 */
#define SDMMC_DCTRL_SDIOEN              SDMMC_DCTRL_SDIOEN_Msk                 /*!<SD I/O enable functions                         */
#define SDMMC_DCTRL_BOOTACKEN_Pos       (12U)
#define SDMMC_DCTRL_BOOTACKEN_Msk       (0x1U << SDMMC_DCTRL_BOOTACKEN_Pos)    /*!< 0x00001000 */
#define SDMMC_DCTRL_BOOTACKEN           SDMMC_DCTRL_BOOTACKEN_Msk              /*!<Enable the reception of the Boot Acknowledgment */
#define SDMMC_DCTRL_FIFORST_Pos         (13U)
#define SDMMC_DCTRL_FIFORST_Msk         (0x1U << SDMMC_DCTRL_FIFORST_Pos)      /*!< 0x00002000 */
#define SDMMC_DCTRL_FIFORST             SDMMC_DCTRL_FIFORST_Msk                /*!<FIFO reset                                      */

/******************  Bit definition for SDMMC_DCOUNT register  *****************/
#define SDMMC_DCOUNT_DATACOUNT_Pos      (0U)
#define SDMMC_DCOUNT_DATACOUNT_Msk      (0x1FFFFFFU << SDMMC_DCOUNT_DATACOUNT_Pos) /*!< 0x01FFFFFF */
#define SDMMC_DCOUNT_DATACOUNT          SDMMC_DCOUNT_DATACOUNT_Msk             /*!<Data count value */

/******************  Bit definition for SDMMC_STA register  ********************/
#define SDMMC_STA_CCRCFAIL_Pos          (0U)
#define SDMMC_STA_CCRCFAIL_Msk          (0x1U << SDMMC_STA_CCRCFAIL_Pos)       /*!< 0x00000001 */
#define SDMMC_STA_CCRCFAIL              SDMMC_STA_CCRCFAIL_Msk                 /*!<Command response received (CRC check failed)  */
#define SDMMC_STA_DCRCFAIL_Pos          (1U)
#define SDMMC_STA_DCRCFAIL_Msk          (0x1U << SDMMC_STA_DCRCFAIL_Pos)       /*!< 0x00000002 */
#define SDMMC_STA_DCRCFAIL              SDMMC_STA_DCRCFAIL_Msk                 /*!<Data block sent/received (CRC check failed)   */
#define SDMMC_STA_CTIMEOUT_Pos          (2U)
#define SDMMC_STA_CTIMEOUT_Msk          (0x1U << SDMMC_STA_CTIMEOUT_Pos)       /*!< 0x00000004 */
#define SDMMC_STA_CTIMEOUT              SDMMC_STA_CTIMEOUT_Msk                 /*!<Command response timeout                      */
#define SDMMC_STA_DTIMEOUT_Pos          (3U)
#define SDMMC_STA_DTIMEOUT_Msk          (0x1U << SDMMC_STA_DTIMEOUT_Pos)       /*!< 0x00000008 */
#define SDMMC_STA_DTIMEOUT              SDMMC_STA_DTIMEOUT_Msk                 /*!<Data timeout                                  */
#define SDMMC_STA_TXUNDERR_Pos          (4U)
#define SDMMC_STA_TXUNDERR_Msk          (0x1U << SDMMC_STA_TXUNDERR_Pos)       /*!< 0x00000010 */
#define SDMMC_STA_TXUNDERR              SDMMC_STA_TXUNDERR_Msk                 /*!<Transmit FIFO underrun error                  */
#define SDMMC_STA_RXOVERR_Pos           (5U)
#define SDMMC_STA_RXOVERR_Msk           (0x1U << SDMMC_STA_RXOVERR_Pos)        /*!< 0x00000020 */
#define SDMMC_STA_RXOVERR               SDMMC_STA_RXOVERR_Msk                  /*!<Received FIFO overrun error                   */
#define SDMMC_STA_CMDREND_Pos           (6U)
#define SDMMC_STA_CMDREND_Msk           (0x1U << SDMMC_STA_CMDREND_Pos)        /*!< 0x00000040 */
#define SDMMC_STA_CMDREND               SDMMC_STA_CMDREND_Msk                  /*!<Command response received (CRC check passed)  */
#define SDMMC_STA_CMDSENT_Pos           (7U)
#define SDMMC_STA_CMDSENT_Msk           (0x1U << SDMMC_STA_CMDSENT_Pos)        /*!< 0x00000080 */
#define SDMMC_STA_CMDSENT               SDMMC_STA_CMDSENT_Msk                  /*!<Command sent (no response required)           */
#define SDMMC_STA_DATAEND_Pos           (8U)
#define SDMMC_STA_DATAEND_Msk           (0x1U << SDMMC_STA_DATAEND_Pos)        /*!< 0x00000100 */
#define SDMMC_STA_DATAEND               SDMMC_STA_DATAEND_Msk                  /*!<Data end (data counter, SDIDCOUNT, is zero)   */
#define SDMMC_STA_DHOLD_Pos             (9U)
#define SDMMC_STA_DHOLD_Msk             (0x1U << SDMMC_STA_DHOLD_Pos)          /*!< 0x00000200 */
#define SDMMC_STA_DHOLD                 SDMMC_STA_DHOLD_Msk                    /*!<Data transfer Hold                                                      */
#define SDMMC_STA_DBCKEND_Pos           (10U)
#define SDMMC_STA_DBCKEND_Msk           (0x1U << SDMMC_STA_DBCKEND_Pos)        /*!< 0x00000400 */
#define SDMMC_STA_DBCKEND               SDMMC_STA_DBCKEND_Msk                  /*!<Data block sent/received (CRC check passed)   */
#define SDMMC_STA_DABORT_Pos            (11U)
#define SDMMC_STA_DABORT_Msk            (0x1U << SDMMC_STA_DABORT_Pos)         /*!< 0x00000800 */
#define SDMMC_STA_DABORT                SDMMC_STA_DABORT_Msk                   /*!<Data transfer aborted by CMD12                                          */
#define SDMMC_STA_DPSMACT_Pos           (12U)
#define SDMMC_STA_DPSMACT_Msk           (0x1U << SDMMC_STA_DPSMACT_Pos)        /*!< 0x00001000 */
#define SDMMC_STA_DPSMACT               SDMMC_STA_DPSMACT_Msk                  /*!< Data path state machine active                                       */
#define SDMMC_STA_CPSMACT_Pos           (13U)
#define SDMMC_STA_CPSMACT_Msk           (0x1U << SDMMC_STA_CPSMACT_Pos)        /*!< 0x00002000 */
#define SDMMC_STA_CPSMACT               SDMMC_STA_CPSMACT_Msk                  /*!<Command path state machine active                                          */
#define SDMMC_STA_TXFIFOHE_Pos          (14U)
#define SDMMC_STA_TXFIFOHE_Msk          (0x1U << SDMMC_STA_TXFIFOHE_Pos)       /*!< 0x00004000 */
#define SDMMC_STA_TXFIFOHE              SDMMC_STA_TXFIFOHE_Msk                 /*!<Transmit FIFO Half Empty: at least 8 words can be written into the FIFO */
#define SDMMC_STA_RXFIFOHF_Pos          (15U)
#define SDMMC_STA_RXFIFOHF_Msk          (0x1U << SDMMC_STA_RXFIFOHF_Pos)       /*!< 0x00008000 */
#define SDMMC_STA_RXFIFOHF              SDMMC_STA_RXFIFOHF_Msk                 /*!<Receive FIFO Half Full: there are at least 8 words in the FIFO */
#define SDMMC_STA_TXFIFOF_Pos           (16U)
#define SDMMC_STA_TXFIFOF_Msk           (0x1U << SDMMC_STA_TXFIFOF_Pos)        /*!< 0x00010000 */
#define SDMMC_STA_TXFIFOF               SDMMC_STA_TXFIFOF_Msk                  /*!<Transmit FIFO full                            */
#define SDMMC_STA_RXFIFOF_Pos           (17U)
#define SDMMC_STA_RXFIFOF_Msk           (0x1U << SDMMC_STA_RXFIFOF_Pos)        /*!< 0x00020000 */
#define SDMMC_STA_RXFIFOF               SDMMC_STA_RXFIFOF_Msk                  /*!<Receive FIFO full                             */
#define SDMMC_STA_TXFIFOE_Pos           (18U)
#define SDMMC_STA_TXFIFOE_Msk           (0x1U << SDMMC_STA_TXFIFOE_Pos)        /*!< 0x00040000 */
#define SDMMC_STA_TXFIFOE               SDMMC_STA_TXFIFOE_Msk                  /*!<Transmit FIFO empty                           */
#define SDMMC_STA_RXFIFOE_Pos           (19U)
#define SDMMC_STA_RXFIFOE_Msk           (0x1U << SDMMC_STA_RXFIFOE_Pos)        /*!< 0x00080000 */
#define SDMMC_STA_RXFIFOE               SDMMC_STA_RXFIFOE_Msk                  /*!<Receive FIFO empty                            */
#define SDMMC_STA_BUSYD0_Pos            (20U)
#define SDMMC_STA_BUSYD0_Msk            (0x1U << SDMMC_STA_BUSYD0_Pos)         /*!< 0x00100000 */
#define SDMMC_STA_BUSYD0                SDMMC_STA_BUSYD0_Msk                   /*!<Inverted value of SDMMC_D0 line (Busy)                                  */
#define SDMMC_STA_BUSYD0END_Pos         (21U)
#define SDMMC_STA_BUSYD0END_Msk         (0x1U << SDMMC_STA_BUSYD0END_Pos)      /*!< 0x00200000 */
#define SDMMC_STA_BUSYD0END             SDMMC_STA_BUSYD0END_Msk                /*!<End of SDMMC_D0 Busy following a CMD response detected                  */
#define SDMMC_STA_SDIOIT_Pos            (22U)
#define SDMMC_STA_SDIOIT_Msk            (0x1U << SDMMC_STA_SDIOIT_Pos)        /*!< 0x00400000 */
#define SDMMC_STA_SDIOIT                SDMMC_STA_SDIOIT_Msk                  /*!<SDIO interrupt received                                                 */
#define SDMMC_STA_ACKFAIL_Pos           (23U)
#define SDMMC_STA_ACKFAIL_Msk           (0x1U << SDMMC_STA_ACKFAIL_Pos)        /*!< 0x00800000 */
#define SDMMC_STA_ACKFAIL               SDMMC_STA_ACKFAIL_Msk                  /*!<Boot Acknowledgment received (BootAck check fail)                       */
#define SDMMC_STA_ACKTIMEOUT_Pos        (24U)
#define SDMMC_STA_ACKTIMEOUT_Msk        (0x1U << SDMMC_STA_ACKTIMEOUT_Pos)     /*!< 0x01000000 */
#define SDMMC_STA_ACKTIMEOUT            SDMMC_STA_ACKTIMEOUT_Msk               /*!<Boot Acknowledgment timeout                                             */
#define SDMMC_STA_VSWEND_Pos            (25U)
#define SDMMC_STA_VSWEND_Msk            (0x1U << SDMMC_STA_VSWEND_Pos)         /*!< 0x02000000 */
#define SDMMC_STA_VSWEND                SDMMC_STA_VSWEND_Msk                   /*!<Voltage switch critical timing section completion                       */
#define SDMMC_STA_CKSTOP_Pos            (26U)
#define SDMMC_STA_CKSTOP_Msk            (0x1U << SDMMC_STA_CKSTOP_Pos)         /*!< 0x04000000 */
#define SDMMC_STA_CKSTOP                SDMMC_STA_CKSTOP_Msk                   /*!<SDMMC_CK stopped in Voltage switch procedure                            */
#define SDMMC_STA_IDMATE_Pos            (27U)
#define SDMMC_STA_IDMATE_Msk            (0x1U << SDMMC_STA_IDMATE_Pos)         /*!< 0x08000000 */
#define SDMMC_STA_IDMATE                SDMMC_STA_IDMATE_Msk                   /*!<IDMA transfer error                                                     */
#define SDMMC_STA_IDMABTC_Pos           (28U)
#define SDMMC_STA_IDMABTC_Msk           (0x1U << SDMMC_STA_IDMABTC_Pos)        /*!< 0x10000000 */
#define SDMMC_STA_IDMABTC               SDMMC_STA_IDMABTC_Msk                  /*!<IDMA buffer transfer complete                                           */

/*******************  Bit definition for SDMMC_ICR register  *******************/
#define SDMMC_ICR_CCRCFAILC_Pos         (0U)
#define SDMMC_ICR_CCRCFAILC_Msk         (0x1U << SDMMC_ICR_CCRCFAILC_Pos)      /*!< 0x00000001 */
#define SDMMC_ICR_CCRCFAILC             SDMMC_ICR_CCRCFAILC_Msk                /*!<CCRCFAIL flag clear bit */
#define SDMMC_ICR_DCRCFAILC_Pos         (1U)
#define SDMMC_ICR_DCRCFAILC_Msk         (0x1U << SDMMC_ICR_DCRCFAILC_Pos)      /*!< 0x00000002 */
#define SDMMC_ICR_DCRCFAILC             SDMMC_ICR_DCRCFAILC_Msk                /*!<DCRCFAIL flag clear bit */
#define SDMMC_ICR_CTIMEOUTC_Pos         (2U)
#define SDMMC_ICR_CTIMEOUTC_Msk         (0x1U << SDMMC_ICR_CTIMEOUTC_Pos)      /*!< 0x00000004 */
#define SDMMC_ICR_CTIMEOUTC             SDMMC_ICR_CTIMEOUTC_Msk                /*!<CTIMEOUT flag clear bit */
#define SDMMC_ICR_DTIMEOUTC_Pos         (3U)
#define SDMMC_ICR_DTIMEOUTC_Msk         (0x1U << SDMMC_ICR_DTIMEOUTC_Pos)      /*!< 0x00000008 */
#define SDMMC_ICR_DTIMEOUTC             SDMMC_ICR_DTIMEOUTC_Msk                /*!<DTIMEOUT flag clear bit */
#define SDMMC_ICR_TXUNDERRC_Pos         (4U)
#define SDMMC_ICR_TXUNDERRC_Msk         (0x1U << SDMMC_ICR_TXUNDERRC_Pos)      /*!< 0x00000010 */
#define SDMMC_ICR_TXUNDERRC             SDMMC_ICR_TXUNDERRC_Msk                /*!<TXUNDERR flag clear bit */
#define SDMMC_ICR_RXOVERRC_Pos          (5U)
#define SDMMC_ICR_RXOVERRC_Msk          (0x1U << SDMMC_ICR_RXOVERRC_Pos)       /*!< 0x00000020 */
#define SDMMC_ICR_RXOVERRC              SDMMC_ICR_RXOVERRC_Msk                 /*!<RXOVERR flag clear bit  */
#define SDMMC_ICR_CMDRENDC_Pos          (6U)
#define SDMMC_ICR_CMDRENDC_Msk          (0x1U << SDMMC_ICR_CMDRENDC_Pos)       /*!< 0x00000040 */
#define SDMMC_ICR_CMDRENDC              SDMMC_ICR_CMDRENDC_Msk                 /*!<CMDREND flag clear bit  */
#define SDMMC_ICR_CMDSENTC_Pos          (7U)
#define SDMMC_ICR_CMDSENTC_Msk          (0x1U << SDMMC_ICR_CMDSENTC_Pos)       /*!< 0x00000080 */
#define SDMMC_ICR_CMDSENTC              SDMMC_ICR_CMDSENTC_Msk                 /*!<CMDSENT flag clear bit  */
#define SDMMC_ICR_DATAENDC_Pos          (8U)
#define SDMMC_ICR_DATAENDC_Msk          (0x1U << SDMMC_ICR_DATAENDC_Pos)       /*!< 0x00000100 */
#define SDMMC_ICR_DATAENDC              SDMMC_ICR_DATAENDC_Msk                 /*!<DATAEND flag clear bit  */
#define SDMMC_ICR_DHOLDC_Pos            (9U)
#define SDMMC_ICR_DHOLDC_Msk            (0x1U << SDMMC_ICR_DHOLDC_Pos)         /*!< 0x00000200 */
#define SDMMC_ICR_DHOLDC                SDMMC_ICR_DHOLDC_Msk                   /*!<DHOLD flag clear bit       */
#define SDMMC_ICR_DBCKENDC_Pos          (10U)
#define SDMMC_ICR_DBCKENDC_Msk          (0x1U << SDMMC_ICR_DBCKENDC_Pos)       /*!< 0x00000400 */
#define SDMMC_ICR_DBCKENDC              SDMMC_ICR_DBCKENDC_Msk                 /*!<DBCKEND flag clear bit  */
#define SDMMC_ICR_DABORTC_Pos           (11U)
#define SDMMC_ICR_DABORTC_Msk           (0x1U << SDMMC_ICR_DABORTC_Pos)        /*!< 0x00000800 */
#define SDMMC_ICR_DABORTC               SDMMC_ICR_DABORTC_Msk                  /*!<DABORTC flag clear bit     */
#define SDMMC_ICR_BUSYD0ENDC_Pos        (21U)
#define SDMMC_ICR_BUSYD0ENDC_Msk        (0x1U << SDMMC_ICR_BUSYD0ENDC_Pos)     /*!< 0x00200000 */
#define SDMMC_ICR_BUSYD0ENDC            SDMMC_ICR_BUSYD0ENDC_Msk               /*!<BUSYD0ENDC flag clear bit  */
#define SDMMC_ICR_SDIOITC_Pos           (22U)
#define SDMMC_ICR_SDIOITC_Msk           (0x1U << SDMMC_ICR_SDIOITC_Pos)       /*!< 0x00400000 */
#define SDMMC_ICR_SDIOITC               SDMMC_ICR_SDIOITC_Msk                 /*!<SDIOIT flag clear bit      */
#define SDMMC_ICR_ACKFAILC_Pos          (23U)
#define SDMMC_ICR_ACKFAILC_Msk          (0x1U << SDMMC_ICR_ACKFAILC_Pos)       /*!< 0x00800000 */
#define SDMMC_ICR_ACKFAILC              SDMMC_ICR_ACKFAILC_Msk                 /*!<ACKFAILC flag clear bit    */
#define SDMMC_ICR_ACKTIMEOUTC_Pos       (24U)
#define SDMMC_ICR_ACKTIMEOUTC_Msk       (0x1U << SDMMC_ICR_ACKTIMEOUTC_Pos)    /*!< 0x01000000 */
#define SDMMC_ICR_ACKTIMEOUTC           SDMMC_ICR_ACKTIMEOUTC_Msk              /*!<ACKTIMEOUTC flag clear bit */
#define SDMMC_ICR_VSWENDC_Pos           (25U)
#define SDMMC_ICR_VSWENDC_Msk           (0x1U << SDMMC_ICR_VSWENDC_Pos)        /*!< 0x02000000 */
#define SDMMC_ICR_VSWENDC               SDMMC_ICR_VSWENDC_Msk                  /*!<VSWENDC flag clear bit     */
#define SDMMC_ICR_CKSTOPC_Pos           (26U)
#define SDMMC_ICR_CKSTOPC_Msk           (0x1U << SDMMC_ICR_CKSTOPC_Pos)        /*!< 0x04000000 */
#define SDMMC_ICR_CKSTOPC               SDMMC_ICR_CKSTOPC_Msk                  /*!<CKSTOPC flag clear bit     */
#define SDMMC_ICR_IDMATEC_Pos           (27U)
#define SDMMC_ICR_IDMATEC_Msk           (0x1U << SDMMC_ICR_IDMATEC_Pos)        /*!< 0x08000000 */
#define SDMMC_ICR_IDMATEC               SDMMC_ICR_IDMATEC_Msk                  /*!<IDMATEC flag clear bit     */
#define SDMMC_ICR_IDMABTCC_Pos          (28U)
#define SDMMC_ICR_IDMABTCC_Msk          (0x1U << SDMMC_ICR_IDMABTCC_Pos)       /*!< 0x10000000 */
#define SDMMC_ICR_IDMABTCC              SDMMC_ICR_IDMABTCC_Msk                 /*!<IDMABTCC flag clear bit    */

/******************  Bit definition for SDMMC_MASK register  *******************/
#define SDMMC_MASK_CCRCFAILIE_Pos       (0U)
#define SDMMC_MASK_CCRCFAILIE_Msk       (0x1U << SDMMC_MASK_CCRCFAILIE_Pos)    /*!< 0x00000001 */
#define SDMMC_MASK_CCRCFAILIE           SDMMC_MASK_CCRCFAILIE_Msk              /*!<Command CRC Fail Interrupt Enable          */
#define SDMMC_MASK_DCRCFAILIE_Pos       (1U)
#define SDMMC_MASK_DCRCFAILIE_Msk       (0x1U << SDMMC_MASK_DCRCFAILIE_Pos)    /*!< 0x00000002 */
#define SDMMC_MASK_DCRCFAILIE           SDMMC_MASK_DCRCFAILIE_Msk              /*!<Data CRC Fail Interrupt Enable             */
#define SDMMC_MASK_CTIMEOUTIE_Pos       (2U)
#define SDMMC_MASK_CTIMEOUTIE_Msk       (0x1U << SDMMC_MASK_CTIMEOUTIE_Pos)    /*!< 0x00000004 */
#define SDMMC_MASK_CTIMEOUTIE           SDMMC_MASK_CTIMEOUTIE_Msk              /*!<Command TimeOut Interrupt Enable           */
#define SDMMC_MASK_DTIMEOUTIE_Pos       (3U)
#define SDMMC_MASK_DTIMEOUTIE_Msk       (0x1U << SDMMC_MASK_DTIMEOUTIE_Pos)    /*!< 0x00000008 */
#define SDMMC_MASK_DTIMEOUTIE           SDMMC_MASK_DTIMEOUTIE_Msk              /*!<Data TimeOut Interrupt Enable              */
#define SDMMC_MASK_TXUNDERRIE_Pos       (4U)
#define SDMMC_MASK_TXUNDERRIE_Msk       (0x1U << SDMMC_MASK_TXUNDERRIE_Pos)    /*!< 0x00000010 */
#define SDMMC_MASK_TXUNDERRIE           SDMMC_MASK_TXUNDERRIE_Msk              /*!<Tx FIFO UnderRun Error Interrupt Enable    */
#define SDMMC_MASK_RXOVERRIE_Pos        (5U)
#define SDMMC_MASK_RXOVERRIE_Msk        (0x1U << SDMMC_MASK_RXOVERRIE_Pos)     /*!< 0x00000020 */
#define SDMMC_MASK_RXOVERRIE            SDMMC_MASK_RXOVERRIE_Msk               /*!<Rx FIFO OverRun Error Interrupt Enable     */
#define SDMMC_MASK_CMDRENDIE_Pos        (6U)
#define SDMMC_MASK_CMDRENDIE_Msk        (0x1U << SDMMC_MASK_CMDRENDIE_Pos)     /*!< 0x00000040 */
#define SDMMC_MASK_CMDRENDIE            SDMMC_MASK_CMDRENDIE_Msk               /*!<Command Response Received Interrupt Enable */
#define SDMMC_MASK_CMDSENTIE_Pos        (7U)
#define SDMMC_MASK_CMDSENTIE_Msk        (0x1U << SDMMC_MASK_CMDSENTIE_Pos)     /*!< 0x00000080 */
#define SDMMC_MASK_CMDSENTIE            SDMMC_MASK_CMDSENTIE_Msk               /*!<Command Sent Interrupt Enable              */
#define SDMMC_MASK_DATAENDIE_Pos        (8U)
#define SDMMC_MASK_DATAENDIE_Msk        (0x1U << SDMMC_MASK_DATAENDIE_Pos)     /*!< 0x00000100 */
#define SDMMC_MASK_DATAENDIE            SDMMC_MASK_DATAENDIE_Msk               /*!<Data End Interrupt Enable                  */
#define SDMMC_MASK_DHOLDIE_Pos          (9U)
#define SDMMC_MASK_DHOLDIE_Msk          (0x1U << SDMMC_MASK_DHOLDIE_Pos)       /*!< 0x00000200 */
#define SDMMC_MASK_DHOLDIE              SDMMC_MASK_DHOLDIE_Msk                 /*!<Data Hold Interrupt Enable                 */
#define SDMMC_MASK_DBCKENDIE_Pos        (10U)
#define SDMMC_MASK_DBCKENDIE_Msk        (0x1U << SDMMC_MASK_DBCKENDIE_Pos)     /*!< 0x00000400 */
#define SDMMC_MASK_DBCKENDIE            SDMMC_MASK_DBCKENDIE_Msk               /*!<Data Block End Interrupt Enable            */
#define SDMMC_MASK_DABORTIE_Pos         (11U)
#define SDMMC_MASK_DABORTIE_Msk         (0x1U << SDMMC_MASK_DABORTIE_Pos)      /*!< 0x00000800 */
#define SDMMC_MASK_DABORTIE             SDMMC_MASK_DABORTIE_Msk                /*!<Data transfer aborted interrupt enable     */

#define SDMMC_MASK_TXFIFOHEIE_Pos       (14U)
#define SDMMC_MASK_TXFIFOHEIE_Msk       (0x1U << SDMMC_MASK_TXFIFOHEIE_Pos)    /*!< 0x00004000 */
#define SDMMC_MASK_TXFIFOHEIE           SDMMC_MASK_TXFIFOHEIE_Msk              /*!<Tx FIFO Half Empty interrupt Enable        */
#define SDMMC_MASK_RXFIFOHFIE_Pos       (15U)
#define SDMMC_MASK_RXFIFOHFIE_Msk       (0x1U << SDMMC_MASK_RXFIFOHFIE_Pos)    /*!< 0x00008000 */
#define SDMMC_MASK_RXFIFOHFIE           SDMMC_MASK_RXFIFOHFIE_Msk              /*!<Rx FIFO Half Full interrupt Enable         */

#define SDMMC_MASK_RXFIFOFIE_Pos        (17U)
#define SDMMC_MASK_RXFIFOFIE_Msk        (0x1U << SDMMC_MASK_RXFIFOFIE_Pos)     /*!< 0x00020000 */
#define SDMMC_MASK_RXFIFOFIE            SDMMC_MASK_RXFIFOFIE_Msk               /*!<Rx FIFO Full interrupt Enable              */
#define SDMMC_MASK_TXFIFOEIE_Pos        (18U)
#define SDMMC_MASK_TXFIFOEIE_Msk        (0x1U << SDMMC_MASK_TXFIFOEIE_Pos)     /*!< 0x00040000 */
#define SDMMC_MASK_TXFIFOEIE            SDMMC_MASK_TXFIFOEIE_Msk               /*!<Tx FIFO Empty interrupt Enable             */

#define SDMMC_MASK_BUSYD0ENDIE_Pos      (21U)
#define SDMMC_MASK_BUSYD0ENDIE_Msk      (0x1U << SDMMC_MASK_BUSYD0ENDIE_Pos)   /*!< 0x00200000 */
#define SDMMC_MASK_BUSYD0ENDIE          SDMMC_MASK_BUSYD0ENDIE_Msk             /*!<BUSYD0ENDIE interrupt Enable */
#define SDMMC_MASK_SDIOITIE_Pos         (22U)
#define SDMMC_MASK_SDIOITIE_Msk         (0x1U << SDMMC_MASK_SDIOITIE_Pos)     /*!< 0x00400000 */
#define SDMMC_MASK_SDIOITIE             SDMMC_MASK_SDIOITIE_Msk               /*!<SDMMC Mode Interrupt Received interrupt Enable */
#define SDMMC_MASK_ACKFAILIE_Pos        (23U)
#define SDMMC_MASK_ACKFAILIE_Msk        (0x1U << SDMMC_MASK_ACKFAILIE_Pos)     /*!< 0x00800000 */
#define SDMMC_MASK_ACKFAILIE            SDMMC_MASK_ACKFAILIE_Msk               /*!<Acknowledgment Fail Interrupt Enable */
#define SDMMC_MASK_ACKTIMEOUTIE_Pos     (24U)
#define SDMMC_MASK_ACKTIMEOUTIE_Msk     (0x1U << SDMMC_MASK_ACKTIMEOUTIE_Pos)  /*!< 0x01000000 */
#define SDMMC_MASK_ACKTIMEOUTIE         SDMMC_MASK_ACKTIMEOUTIE_Msk            /*!<Acknowledgment timeout Interrupt Enable */
#define SDMMC_MASK_VSWENDIE_Pos         (25U)
#define SDMMC_MASK_VSWENDIE_Msk         (0x1U << SDMMC_MASK_VSWENDIE_Pos)      /*!< 0x02000000 */
#define SDMMC_MASK_VSWENDIE             SDMMC_MASK_VSWENDIE_Msk                /*!<Voltage switch critical timing section completion Interrupt Enable */
#define SDMMC_MASK_CKSTOPIE_Pos         (26U)
#define SDMMC_MASK_CKSTOPIE_Msk         (0x1U << SDMMC_MASK_CKSTOPIE_Pos)      /*!< 0x04000000 */
#define SDMMC_MASK_CKSTOPIE             SDMMC_MASK_CKSTOPIE_Msk                /*!<Voltage Switch clock stopped Interrupt Enable */
#define SDMMC_MASK_IDMABTCIE_Pos        (28U)
#define SDMMC_MASK_IDMABTCIE_Msk        (0x1U << SDMMC_MASK_IDMABTCIE_Pos)     /*!< 0x10000000 */
#define SDMMC_MASK_IDMABTCIE            SDMMC_MASK_IDMABTCIE_Msk               /*!<IDMA buffer transfer complete Interrupt Enable */

/*****************  Bit definition for SDMMC_FIFOCNT register  *****************/
#define SDMMC_FIFOCNT_FIFOCOUNT_Pos     (0U)
#define SDMMC_FIFOCNT_FIFOCOUNT_Msk     (0xFFFFFFU << SDMMC_FIFOCNT_FIFOCOUNT_Pos) /*!< 0x00FFFFFF */
#define SDMMC_FIFOCNT_FIFOCOUNT         SDMMC_FIFOCNT_FIFOCOUNT_Msk            /*!<Remaining number of words to be written to or read from the FIFO */

/******************  Bit definition for SDMMC_FIFO register  *******************/
#define SDMMC_FIFO_FIFODATA_Pos         (0U)
#define SDMMC_FIFO_FIFODATA_Msk         (0xFFFFFFFFU << SDMMC_FIFO_FIFODATA_Pos) /*!< 0xFFFFFFFF */
#define SDMMC_FIFO_FIFODATA             SDMMC_FIFO_FIFODATA_Msk                /*!<Receive and transmit FIFO data */

/******************  Bit definition for SDMMC_IDMACTRL register ****************/
#define SDMMC_IDMA_IDMAEN_Pos           (0U)
#define SDMMC_IDMA_IDMAEN_Msk           (0x1U << SDMMC_IDMA_IDMAEN_Pos)        /*!< 0x00000001 */
#define SDMMC_IDMA_IDMAEN               SDMMC_IDMA_IDMAEN_Msk                  /*!< Enable the internal DMA of the SDMMC peripheral */
#define SDMMC_IDMA_IDMABMODE_Pos        (1U)
#define SDMMC_IDMA_IDMABMODE_Msk        (0x1U << SDMMC_IDMA_IDMABMODE_Pos)     /*!< 0x00000002 */
#define SDMMC_IDMA_IDMABMODE            SDMMC_IDMA_IDMABMODE_Msk               /*!< Enable double buffer mode for IDMA */
#define SDMMC_IDMA_IDMABACT_Pos         (2U)
#define SDMMC_IDMA_IDMABACT_Msk         (0x1U << SDMMC_IDMA_IDMABACT_Pos)      /*!< 0x00000004 */
#define SDMMC_IDMA_IDMABACT             SDMMC_IDMA_IDMABACT_Msk                /*!< Uses buffer 1 when double buffer mode is selected */

/*****************  Bit definition for SDMMC_IDMABSIZER register  **************/
#define SDMMC_IDMABSIZE_IDMABNDT_Pos     (5U)
#define SDMMC_IDMABSIZE_IDMABNDT_Msk     (0xFFFL << SDMMC_IDMABSIZE_IDMABNDT_Pos) /*!< 0x0001FFE0 */
#define SDMMC_IDMABSIZE_IDMABNDT         SDMMC_IDMABSIZE_IDMABNDT_Msk          /*!< Number of bytes per buffer */

/*****************  Bit definition for SDMMC_IDMALAR register  ***************/
#define SDMMC_IDMALAR_IDMALA_Pos         (0U)
#define SDMMC_IDMALAR_IDMALA_Msk         (0x3FFFUL << SDMMC_IDMALAR_IDMALA_Pos)  /*!< 0x00003FFF */
#define SDMMC_IDMALAR_IDMALA             SDMMC_IDMALAR_IDMALA_Msk                /*!< Linked list item address offset */
#define SDMMC_IDMALAR_ABR_Pos            (29U)
#define SDMMC_IDMALAR_ABR_Msk            (0x1UL << SDMMC_IDMALAR_ABR_Pos)        /*!< 0x20000000 */
#define SDMMC_IDMALAR_ABR                SDMMC_IDMALAR_ABR_Msk                   /*!< Acknowledge linked list buffer ready */
#define SDMMC_IDMALAR_ULS_Pos            (30U)
#define SDMMC_IDMALAR_ULS_Msk            (0x1UL << SDMMC_IDMALAR_ULS_Pos)        /*!< 0x40000000 */
#define SDMMC_IDMALAR_ULS                SDMMC_IDMALAR_ULS_Msk                   /*!< Update Size from linked list */
#define SDMMC_IDMALAR_ULA_Pos            (31U)
#define SDMMC_IDMALAR_ULA_Msk            (0x1UL << SDMMC_IDMALAR_ULA_Pos)        /*!< 0x80000000 */
#define SDMMC_IDMALAR_ULA                SDMMC_IDMALAR_ULA_Msk                   /*!< Update Address from linked list */

/*****************  Bit definition for SDMMC_IDMABAR register  ***************/
#define SDMMC_IDMABAR_IDMABAR_Pos        (0U)
#define SDMMC_IDMABAR_IDMABAR_Msk        (0xFFFFFFFFUL << SDMMC_IDMABAR_IDMABAR_Pos)/*!< 0xFFFFFFFF */
#define SDMMC_IDMABAR_IDMABAR            SDMMC_IDMABAR_IDMABAR_Msk             /*!< linked list memory base register */

/**********************  Bit definition for SDMMC_VERR register  *****************/
#define SDMMC_VERR_MINREV_Pos      (0U)
#define SDMMC_VERR_MINREV_Msk      (0xFU << SDMMC_VERR_MINREV_Pos)               /*!< 0x0000000F */
#define SDMMC_VERR_MINREV          SDMMC_VERR_MINREV_Msk                         /*!< Minor Revision number */
#define SDMMC_VERR_MAJREV_Pos      (4U)
#define SDMMC_VERR_MAJREV_Msk      (0xFU << SDMMC_VERR_MAJREV_Pos)               /*!< 0x000000F0 */
#define SDMMC_VERR_MAJREV          SDMMC_VERR_MAJREV_Msk                         /*!< Major Revision number */

/**********************  Bit definition for SDMMC_IPIDR register  ****************/
#define SDMMC_IPIDR_IPID_Pos       (0U)
#define SDMMC_IPIDR_IPID_Msk       (0xFFFFFFFFU << SDMMC_IPIDR_IPID_Pos)         /*!< 0xFFFFFFFF */
#define SDMMC_IPIDR_IPID           SDMMC_IPIDR_IPID_Msk                          /*!< IP Identification */

/**********************  Bit definition for SDMMC_SIDR register  *****************/
#define SDMMC_SIDR_SID_Pos         (0U)
#define SDMMC_SIDR_SID_Msk         (0xFFFFFFFFU << SDMMC_SIDR_SID_Pos)           /*!< 0xFFFFFFFF */
#define SDMMC_SIDR_SID             SDMMC_SIDR_SID_Msk                            /*!< IP size identification */

/******************************************************************************/
/*                                                                            */
/*                        Delay Block Interface (DLYB)                        */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for DLYB_CR register  ********************/
#define DLYB_CR_DEN_Pos         (0U)
#define DLYB_CR_DEN_Msk         (0x1U << DLYB_CR_DEN_Pos)                      /*!< 0x00000001 */
#define DLYB_CR_DEN             DLYB_CR_DEN_Msk                                /*!<Delay Block enable */
#define DLYB_CR_SEN_Pos         (1U)
#define DLYB_CR_SEN_Msk         (0x1U << DLYB_CR_SEN_Pos)                      /*!< 0x00000002 */
#define DLYB_CR_SEN             DLYB_CR_SEN_Msk                                /*!<Sampler length enable */


/*******************  Bit definition for DLYB_CFGR register  ********************/
#define DLYB_CFGR_SEL_Pos       (0U)
#define DLYB_CFGR_SEL_Msk       (0xFU << DLYB_CFGR_SEL_Pos)                    /*!< 0x0000000F */
#define DLYB_CFGR_SEL           DLYB_CFGR_SEL_Msk                              /*!<Select the phase for the Output clock[3:0] */
#define DLYB_CFGR_SEL_0         (0x1U << DLYB_CFGR_SEL_Pos)                    /*!< 0x00000001 */
#define DLYB_CFGR_SEL_1         (0x2U << DLYB_CFGR_SEL_Pos)                    /*!< 0x00000002 */
#define DLYB_CFGR_SEL_2         (0x3U << DLYB_CFGR_SEL_Pos)                    /*!< 0x00000003 */
#define DLYB_CFGR_SEL_3         (0x8U << DLYB_CFGR_SEL_Pos)                    /*!< 0x00000008 */

#define DLYB_CFGR_UNIT_Pos      (8U)
#define DLYB_CFGR_UNIT_Msk      (0x7FU << DLYB_CFGR_UNIT_Pos)                  /*!< 0x00007F00 */
#define DLYB_CFGR_UNIT          DLYB_CFGR_UNIT_Msk                             /*!<Delay Defines the delay of a Unit delay cell[6:0] */
#define DLYB_CFGR_UNIT_0        (0x01U << DLYB_CFGR_UNIT_Pos)                  /*!< 0x00000100 */
#define DLYB_CFGR_UNIT_1        (0x02U << DLYB_CFGR_UNIT_Pos)                  /*!< 0x00000200 */
#define DLYB_CFGR_UNIT_2        (0x04U << DLYB_CFGR_UNIT_Pos)                  /*!< 0x00000400 */
#define DLYB_CFGR_UNIT_3        (0x08U << DLYB_CFGR_UNIT_Pos)                  /*!< 0x00000800 */
#define DLYB_CFGR_UNIT_4        (0x10U << DLYB_CFGR_UNIT_Pos)                  /*!< 0x00001000 */
#define DLYB_CFGR_UNIT_5        (0x20U << DLYB_CFGR_UNIT_Pos)                  /*!< 0x00002000 */
#define DLYB_CFGR_UNIT_6        (0x40U << DLYB_CFGR_UNIT_Pos)                  /*!< 0x00004000 */

#define DLYB_CFGR_LNG_Pos       (16U)
#define DLYB_CFGR_LNG_Msk       (0xFFFU << DLYB_CFGR_LNG_Pos)                  /*!< 0x0FFF0000 */
#define DLYB_CFGR_LNG           DLYB_CFGR_LNG_Msk                              /*!<Delay line length value[11:0] */
#define DLYB_CFGR_LNG_0         (0x001U << DLYB_CFGR_LNG_Pos)                  /*!< 0x00010000 */
#define DLYB_CFGR_LNG_1         (0x002U << DLYB_CFGR_LNG_Pos)                  /*!< 0x00020000 */
#define DLYB_CFGR_LNG_2         (0x004U << DLYB_CFGR_LNG_Pos)                  /*!< 0x00040000 */
#define DLYB_CFGR_LNG_3         (0x008U << DLYB_CFGR_LNG_Pos)                  /*!< 0x00080000 */
#define DLYB_CFGR_LNG_4         (0x010U << DLYB_CFGR_LNG_Pos)                  /*!< 0x00100000 */
#define DLYB_CFGR_LNG_5         (0x020U << DLYB_CFGR_LNG_Pos)                  /*!< 0x00200000 */
#define DLYB_CFGR_LNG_6         (0x040U << DLYB_CFGR_LNG_Pos)                  /*!< 0x00400000 */
#define DLYB_CFGR_LNG_7         (0x080U << DLYB_CFGR_LNG_Pos)                  /*!< 0x00800000 */
#define DLYB_CFGR_LNG_8         (0x100U << DLYB_CFGR_LNG_Pos)                  /*!< 0x01000000 */
#define DLYB_CFGR_LNG_9         (0x200U << DLYB_CFGR_LNG_Pos)                  /*!< 0x02000000 */
#define DLYB_CFGR_LNG_10        (0x400U << DLYB_CFGR_LNG_Pos)                  /*!< 0x04000000 */
#define DLYB_CFGR_LNG_11        (0x800U << DLYB_CFGR_LNG_Pos)                  /*!< 0x08000000 */

#define DLYB_CFGR_LNGF_Pos      (31U)
#define DLYB_CFGR_LNGF_Msk      (0x1U << DLYB_CFGR_LNGF_Pos)                   /*!< 0x80000000 */
#define DLYB_CFGR_LNGF          DLYB_CFGR_LNGF_Msk                             /*!<Length valid flag */

/**********************  Bit definition for DLYB_VERR register  *****************/
#define DLYB_VERR_MINREV_Pos      (0U)
#define DLYB_VERR_MINREV_Msk      (0xFU << DLYB_VERR_MINREV_Pos)               /*!< 0x0000000F */
#define DLYB_VERR_MINREV          DLYB_VERR_MINREV_Msk                         /*!< Minor Revision number */
#define DLYB_VERR_MAJREV_Pos      (4U)
#define DLYB_VERR_MAJREV_Msk      (0xFU << DLYB_VERR_MAJREV_Pos)               /*!< 0x000000F0 */
#define DLYB_VERR_MAJREV          DLYB_VERR_MAJREV_Msk                         /*!< Major Revision number */

/**********************  Bit definition for DLYB_IPIDR register  ****************/
#define DLYB_IPIDR_IPID_Pos       (0U)
#define DLYB_IPIDR_IPID_Msk       (0xFFFFFFFFU << DLYB_IPIDR_IPID_Pos)         /*!< 0xFFFFFFFF */
#define DLYB_IPIDR_IPID           DLYB_IPIDR_IPID_Msk                          /*!< IP Identification */

/**********************  Bit definition for DLYB_SIDR register  *****************/
#define DLYB_SIDR_SID_Pos         (0U)
#define DLYB_SIDR_SID_Msk         (0xFFFFFFFFU << DLYB_SIDR_SID_Pos)           /*!< 0xFFFFFFFF */
#define DLYB_SIDR_SID             DLYB_SIDR_SID_Msk                            /*!< IP size identification */

/******************************************************************************/
/*                                                                            */
/*                        Serial Peripheral Interface (SPI)                   */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for SPI_CR1 register  ********************/
#define SPI_CR1_SPE_Pos             (0U)
#define SPI_CR1_SPE_Msk             (0x1U << SPI_CR1_SPE_Pos)                  /*!< 0x00000001 */
#define SPI_CR1_SPE                 SPI_CR1_SPE_Msk                            /*!<Serial Peripheral Enable                       */
#define SPI_CR1_MASRX_Pos           (8U)
#define SPI_CR1_MASRX_Msk           (0x1U << SPI_CR1_MASRX_Pos)                /*!< 0x00000100 */
#define SPI_CR1_MASRX               SPI_CR1_MASRX_Msk                          /*!<Master automatic SUSP in Receive mode          */
#define SPI_CR1_CSTART_Pos          (9U)
#define SPI_CR1_CSTART_Msk          (0x1U << SPI_CR1_CSTART_Pos)               /*!< 0x00000200 */
#define SPI_CR1_CSTART              SPI_CR1_CSTART_Msk                         /*!<Master transfer start                          */
#define SPI_CR1_CSUSP_Pos           (10U)
#define SPI_CR1_CSUSP_Msk           (0x1U << SPI_CR1_CSUSP_Pos)                /*!< 0x00000400 */
#define SPI_CR1_CSUSP               SPI_CR1_CSUSP_Msk                          /*!<Master SUSPend request                         */
#define SPI_CR1_HDDIR_Pos           (11U)
#define SPI_CR1_HDDIR_Msk           (0x1U << SPI_CR1_HDDIR_Pos)                /*!< 0x00000800 */
#define SPI_CR1_HDDIR               SPI_CR1_HDDIR_Msk                          /*!<Rx/Tx direction at Half-duplex mode            */
#define SPI_CR1_SSI_Pos             (12U)
#define SPI_CR1_SSI_Msk             (0x1U << SPI_CR1_SSI_Pos)                  /*!< 0x00001000 */
#define SPI_CR1_SSI                 SPI_CR1_SSI_Msk                            /*!<Internal SS signal input level                 */
#define SPI_CR1_CRC33_17_Pos        (13U)
#define SPI_CR1_CRC33_17_Msk        (0x1U << SPI_CR1_CRC33_17_Pos)             /*!< 0x00002000 */
#define SPI_CR1_CRC33_17            SPI_CR1_CRC33_17_Msk                       /*!<32-bit CRC polynomial configuration            */
#define SPI_CR1_RCRCINI_Pos         (14U)
#define SPI_CR1_RCRCINI_Msk         (0x1U << SPI_CR1_RCRCINI_Pos)              /*!< 0x00004000 */
#define SPI_CR1_RCRCINI             SPI_CR1_RCRCINI_Msk                        /*!<CRC calculation initialization pattern control for receiver    */
#define SPI_CR1_TCRCINI_Pos         (15U)
#define SPI_CR1_TCRCINI_Msk         (0x1U << SPI_CR1_TCRCINI_Pos)              /*!< 0x00008000 */
#define SPI_CR1_TCRCINI             SPI_CR1_TCRCINI_Msk                        /*!<CRC calculation initialization pattern control for transmitter */
#define SPI_CR1_IOLOCK_Pos          (16U)
#define SPI_CR1_IOLOCK_Msk          (0x1U << SPI_CR1_IOLOCK_Pos)               /*!< 0x00010000 */
#define SPI_CR1_IOLOCK              SPI_CR1_IOLOCK_Msk                         /*!<Locking the AF configuration of associated IOs */

/*******************  Bit definition for SPI_CR2 register  ********************/
#define SPI_CR2_TSER_Pos            (16U)
#define SPI_CR2_TSER_Msk            (0xFFFFU << SPI_CR2_TSER_Pos)              /*!< 0xFFFF0000 */
#define SPI_CR2_TSER                SPI_CR2_TSER_Msk                           /*!<Number of data transfer extension                */
#define SPI_CR2_TSIZE_Pos           (0U)
#define SPI_CR2_TSIZE_Msk           (0xFFFFU << SPI_CR2_TSIZE_Pos)             /*!< 0x0000FFFF */
#define SPI_CR2_TSIZE               SPI_CR2_TSIZE_Msk                          /*!<Number of data at current transfer               */

/*******************  Bit definition for SPI_CFG1 register  ********************/
#define SPI_CFG1_DSIZE_Pos          (0U)
#define SPI_CFG1_DSIZE_Msk          (0x1FU << SPI_CFG1_DSIZE_Pos)              /*!< 0x0000001F */
#define SPI_CFG1_DSIZE              SPI_CFG1_DSIZE_Msk                         /*!<DSIZE [4:0]: Number of bits in at single SPI data frame */
#define SPI_CFG1_DSIZE_0            (0x01U << SPI_CFG1_DSIZE_Pos)              /*!< 0x00000001 */
#define SPI_CFG1_DSIZE_1            (0x02U << SPI_CFG1_DSIZE_Pos)              /*!< 0x00000002 */
#define SPI_CFG1_DSIZE_2            (0x04U << SPI_CFG1_DSIZE_Pos)              /*!< 0x00000004 */
#define SPI_CFG1_DSIZE_3            (0x08U << SPI_CFG1_DSIZE_Pos)              /*!< 0x00000008 */
#define SPI_CFG1_DSIZE_4            (0x10U << SPI_CFG1_DSIZE_Pos)              /*!< 0x00000010 */

#define SPI_CFG1_FTHLV_Pos          (5U)
#define SPI_CFG1_FTHLV_Msk          (0xFU << SPI_CFG1_FTHLV_Pos)               /*!< 0x000001E0 */
#define SPI_CFG1_FTHLV              SPI_CFG1_FTHLV_Msk                         /*!<FTHVL [3:0]: FIFO threshold level*/
#define SPI_CFG1_FTHLV_0            (0x1U << SPI_CFG1_FTHLV_Pos)               /*!< 0x00000020 */
#define SPI_CFG1_FTHLV_1            (0x2U << SPI_CFG1_FTHLV_Pos)               /*!< 0x00000040 */
#define SPI_CFG1_FTHLV_2            (0x4U << SPI_CFG1_FTHLV_Pos)               /*!< 0x00000080 */
#define SPI_CFG1_FTHLV_3            (0x8U << SPI_CFG1_FTHLV_Pos)               /*!< 0x00000100 */

#define SPI_CFG1_UDRCFG_Pos         (9U)
#define SPI_CFG1_UDRCFG_Msk         (0x3U << SPI_CFG1_UDRCFG_Pos)              /*!< 0x00000600 */
#define SPI_CFG1_UDRCFG             SPI_CFG1_UDRCFG_Msk                        /*!<UDRCFG [1:0]: Behavior of slave transmitter at underrun condition*/
#define SPI_CFG1_UDRCFG_0           (0x1U << SPI_CFG1_UDRCFG_Pos)              /*!< 0x00000200 */
#define SPI_CFG1_UDRCFG_1           (0x2U << SPI_CFG1_UDRCFG_Pos)              /*!< 0x00000400 */


#define SPI_CFG1_UDRDET_Pos         (11U)
#define SPI_CFG1_UDRDET_Msk         (0x3U << SPI_CFG1_UDRDET_Pos)              /*!< 0x00001800 */
#define SPI_CFG1_UDRDET             SPI_CFG1_UDRDET_Msk                        /*!<UDRDET [1:0]: Detection of underrun condition at slave transmitter*/
#define SPI_CFG1_UDRDET_0           (0x1U << SPI_CFG1_UDRDET_Pos)              /*!< 0x00000800 */
#define SPI_CFG1_UDRDET_1           (0x2U << SPI_CFG1_UDRDET_Pos)              /*!< 0x00001000 */

#define SPI_CFG1_RXDMAEN_Pos        (14U)
#define SPI_CFG1_RXDMAEN_Msk        (0x1U << SPI_CFG1_RXDMAEN_Pos)             /*!< 0x00004000 */
#define SPI_CFG1_RXDMAEN            SPI_CFG1_RXDMAEN_Msk                       /*!<Rx DMA stream enable                */
#define SPI_CFG1_TXDMAEN_Pos        (15U)
#define SPI_CFG1_TXDMAEN_Msk        (0x1U << SPI_CFG1_TXDMAEN_Pos)             /*!< 0x00008000 */
#define SPI_CFG1_TXDMAEN            SPI_CFG1_TXDMAEN_Msk                       /*!<Tx DMA stream enable                */

#define SPI_CFG1_CRCSIZE_Pos        (16U)
#define SPI_CFG1_CRCSIZE_Msk        (0x1FU << SPI_CFG1_CRCSIZE_Pos)            /*!< 0x001F0000 */
#define SPI_CFG1_CRCSIZE            SPI_CFG1_CRCSIZE_Msk                       /*!<CRCSIZE [4:0]: Length of CRC frame*/
#define SPI_CFG1_CRCSIZE_0          (0x01U << SPI_CFG1_CRCSIZE_Pos)            /*!< 0x00010000 */
#define SPI_CFG1_CRCSIZE_1          (0x02U << SPI_CFG1_CRCSIZE_Pos)            /*!< 0x00020000 */
#define SPI_CFG1_CRCSIZE_2          (0x04U << SPI_CFG1_CRCSIZE_Pos)            /*!< 0x00040000 */
#define SPI_CFG1_CRCSIZE_3          (0x08U << SPI_CFG1_CRCSIZE_Pos)            /*!< 0x00080000 */
#define SPI_CFG1_CRCSIZE_4          (0x10U << SPI_CFG1_CRCSIZE_Pos)            /*!< 0x00100000 */

#define SPI_CFG1_CRCEN_Pos          (22U)                                      
#define SPI_CFG1_CRCEN_Msk          (0x1U << SPI_CFG1_CRCEN_Pos)               /*!< 0x00400000 */
#define SPI_CFG1_CRCEN              SPI_CFG1_CRCEN_Msk                         /*!<Hardware CRC computation enable */

#define SPI_CFG1_MBR_Pos            (28U)
#define SPI_CFG1_MBR_Msk            (0x7U << SPI_CFG1_MBR_Pos)                 /*!< 0x70000000 */
#define SPI_CFG1_MBR                SPI_CFG1_MBR_Msk                           /*!<Master baud rate                */
#define SPI_CFG1_MBR_0              (0x1U << SPI_CFG1_MBR_Pos)                 /*!< 0x10000000 */
#define SPI_CFG1_MBR_1              (0x2U << SPI_CFG1_MBR_Pos)                 /*!< 0x20000000 */
#define SPI_CFG1_MBR_2              (0x4U << SPI_CFG1_MBR_Pos)                 /*!< 0x40000000 */

/*******************  Bit definition for SPI_CFG2 register  ********************/
#define SPI_CFG2_MSSI_Pos           (0U)
#define SPI_CFG2_MSSI_Msk           (0xFU << SPI_CFG2_MSSI_Pos)                /*!< 0x0000000F */
#define SPI_CFG2_MSSI               SPI_CFG2_MSSI_Msk                          /*!<Master SS Idleness */
#define SPI_CFG2_MSSI_0             (0x1U << SPI_CFG2_MSSI_Pos)                /*!< 0x00000001 */
#define SPI_CFG2_MSSI_1             (0x2U << SPI_CFG2_MSSI_Pos)                /*!< 0x00000002 */
#define SPI_CFG2_MSSI_2             (0x4U << SPI_CFG2_MSSI_Pos)                /*!< 0x00000004 */
#define SPI_CFG2_MSSI_3             (0x8U << SPI_CFG2_MSSI_Pos)                /*!< 0x00000008 */

#define SPI_CFG2_MIDI_Pos           (4U)
#define SPI_CFG2_MIDI_Msk           (0xFU << SPI_CFG2_MIDI_Pos)                /*!< 0x000000F0 */
#define SPI_CFG2_MIDI               SPI_CFG2_MIDI_Msk                          /*!<Master Inter-Data Idleness */
#define SPI_CFG2_MIDI_0             (0x1U << SPI_CFG2_MIDI_Pos)                /*!< 0x00000010 */
#define SPI_CFG2_MIDI_1             (0x2U << SPI_CFG2_MIDI_Pos)                /*!< 0x00000020 */
#define SPI_CFG2_MIDI_2             (0x4U << SPI_CFG2_MIDI_Pos)                /*!< 0x00000040 */
#define SPI_CFG2_MIDI_3             (0x8U << SPI_CFG2_MIDI_Pos)                /*!< 0x00000080 */

#define SPI_CFG2_IOSWP_Pos          (15U)
#define SPI_CFG2_IOSWP_Msk          (0x1U << SPI_CFG2_IOSWP_Pos)               /*!< 0x00008000 */
#define SPI_CFG2_IOSWP              SPI_CFG2_IOSWP_Msk                         /*!<Swap functionality of MISO and MOSI pins */

#define SPI_CFG2_COMM_Pos           (17U)
#define SPI_CFG2_COMM_Msk           (0x3U << SPI_CFG2_COMM_Pos)                /*!< 0x00060000 */
#define SPI_CFG2_COMM               SPI_CFG2_COMM_Msk                          /*!<COMM [1:0]: SPI Communication Mode*/
#define SPI_CFG2_COMM_0             (0x1U << SPI_CFG2_COMM_Pos)                /*!< 0x00020000 */
#define SPI_CFG2_COMM_1             (0x2U << SPI_CFG2_COMM_Pos)                /*!< 0x00040000 */

#define SPI_CFG2_SP_Pos             (19U)
#define SPI_CFG2_SP_Msk             (0x7U << SPI_CFG2_SP_Pos)                  /*!< 0x00380000 */
#define SPI_CFG2_SP                 SPI_CFG2_SP_Msk                            /*!<SP[2:0]: Serial Protocol */
#define SPI_CFG2_SP_0               (0x1U << SPI_CFG2_SP_Pos)                  /*!< 0x00080000 */
#define SPI_CFG2_SP_1               (0x2U << SPI_CFG2_SP_Pos)                  /*!< 0x00100000 */
#define SPI_CFG2_SP_2               (0x4U << SPI_CFG2_SP_Pos)                  /*!< 0x00200000 */

#define SPI_CFG2_MASTER_Pos         (22U)
#define SPI_CFG2_MASTER_Msk         (0x1U << SPI_CFG2_MASTER_Pos)              /*!< 0x00400000 */
#define SPI_CFG2_MASTER             SPI_CFG2_MASTER_Msk                        /*!<SPI Master           */
#define SPI_CFG2_LSBFRST_Pos        (23U)
#define SPI_CFG2_LSBFRST_Msk        (0x1U << SPI_CFG2_LSBFRST_Pos)             /*!< 0x00800000 */
#define SPI_CFG2_LSBFRST            SPI_CFG2_LSBFRST_Msk                       /*!<Data frame format               */
#define SPI_CFG2_CPHA_Pos           (24U)
#define SPI_CFG2_CPHA_Msk           (0x1U << SPI_CFG2_CPHA_Pos)                /*!< 0x01000000 */
#define SPI_CFG2_CPHA               SPI_CFG2_CPHA_Msk                          /*!<Clock Phase      */
#define SPI_CFG2_CPOL_Pos           (25U)
#define SPI_CFG2_CPOL_Msk           (0x1U << SPI_CFG2_CPOL_Pos)                /*!< 0x02000000 */
#define SPI_CFG2_CPOL               SPI_CFG2_CPOL_Msk                          /*!<Clock Polarity   */
#define SPI_CFG2_SSM_Pos            (26U)
#define SPI_CFG2_SSM_Msk            (0x1U << SPI_CFG2_SSM_Pos)                 /*!< 0x04000000 */
#define SPI_CFG2_SSM                SPI_CFG2_SSM_Msk                           /*!<Software slave management */

#define SPI_CFG2_SSIOP_Pos          (28U)
#define SPI_CFG2_SSIOP_Msk          (0x1U << SPI_CFG2_SSIOP_Pos)               /*!< 0x10000000 */
#define SPI_CFG2_SSIOP              SPI_CFG2_SSIOP_Msk                         /*!<SS input/output polarity */
#define SPI_CFG2_SSOE_Pos           (29U)
#define SPI_CFG2_SSOE_Msk           (0x1U << SPI_CFG2_SSOE_Pos)                /*!< 0x20000000 */
#define SPI_CFG2_SSOE               SPI_CFG2_SSOE_Msk                          /*!<SS output enable */
#define SPI_CFG2_SSOM_Pos           (30U)
#define SPI_CFG2_SSOM_Msk           (0x1U << SPI_CFG2_SSOM_Pos)                /*!< 0x40000000 */
#define SPI_CFG2_SSOM               SPI_CFG2_SSOM_Msk                          /*!<SS output management in master mode */

#define SPI_CFG2_AFCNTR_Pos         (31U)
#define SPI_CFG2_AFCNTR_Msk         (0x1U << SPI_CFG2_AFCNTR_Pos)              /*!< 0x80000000 */
#define SPI_CFG2_AFCNTR             SPI_CFG2_AFCNTR_Msk                        /*!<Alternate function GPIOs control */

/*******************  Bit definition for SPI_IER register  ********************/
#define SPI_IER_RXPIE_Pos           (0U)
#define SPI_IER_RXPIE_Msk           (0x1U << SPI_IER_RXPIE_Pos)                /*!< 0x00000001 */
#define SPI_IER_RXPIE               SPI_IER_RXPIE_Msk                          /*!<RXP Interrupt Enable                     */
#define SPI_IER_TXPIE_Pos           (1U)
#define SPI_IER_TXPIE_Msk           (0x1U << SPI_IER_TXPIE_Pos)                /*!< 0x00000002 */
#define SPI_IER_TXPIE               SPI_IER_TXPIE_Msk                          /*!<TXP interrupt enable                     */
#define SPI_IER_DXPIE_Pos           (2U)
#define SPI_IER_DXPIE_Msk           (0x1U << SPI_IER_DXPIE_Pos)                /*!< 0x00000004 */
#define SPI_IER_DXPIE               SPI_IER_DXPIE_Msk                          /*!<DXP interrupt enable                         */
#define SPI_IER_EOTIE_Pos           (3U)
#define SPI_IER_EOTIE_Msk           (0x1U << SPI_IER_EOTIE_Pos)                /*!< 0x00000008 */
#define SPI_IER_EOTIE               SPI_IER_EOTIE_Msk                          /*!<EOT/SUSP/TXC interrupt enable    */
#define SPI_IER_TXTFIE_Pos          (4U)
#define SPI_IER_TXTFIE_Msk          (0x1U << SPI_IER_TXTFIE_Pos)               /*!< 0x00000010 */
#define SPI_IER_TXTFIE              SPI_IER_TXTFIE_Msk                         /*!<TXTF interrupt enable                    */
#define SPI_IER_UDRIE_Pos           (5U)
#define SPI_IER_UDRIE_Msk           (0x1U << SPI_IER_UDRIE_Pos)                /*!< 0x00000020 */
#define SPI_IER_UDRIE               SPI_IER_UDRIE_Msk                          /*!<UDR interrupt enable                         */
#define SPI_IER_OVRIE_Pos           (6U)
#define SPI_IER_OVRIE_Msk           (0x1U << SPI_IER_OVRIE_Pos)                /*!< 0x00000040 */
#define SPI_IER_OVRIE               SPI_IER_OVRIE_Msk                          /*!<OVR interrupt enable                         */
#define SPI_IER_CRCEIE_Pos           (7U)
#define SPI_IER_CRCEIE_Msk           (0x1U << SPI_IER_CRCEIE_Pos)                /*!< 0x00000080 */
#define SPI_IER_CRCEIE               SPI_IER_CRCEIE_Msk                          /*!<CRC interrupt enable                       */
#define SPI_IER_TIFREIE_Pos         (8U)
#define SPI_IER_TIFREIE_Msk         (0x1U << SPI_IER_TIFREIE_Pos)              /*!< 0x00000100 */
#define SPI_IER_TIFREIE             SPI_IER_TIFREIE_Msk                        /*!<TI Frame Error interrupt enable */
#define SPI_IER_MODFIE_Pos          (9U)
#define SPI_IER_MODFIE_Msk          (0x1U << SPI_IER_MODFIE_Pos)               /*!< 0x00000200 */
#define SPI_IER_MODFIE              SPI_IER_MODFIE_Msk                         /*!<MODF interrupt enable                    */
#define SPI_IER_TSERFIE_Pos          (10U)
#define SPI_IER_TSERFIE_Msk          (0x1U << SPI_IER_TSERFIE_Pos)               /*!< 0x00000400 */
#define SPI_IER_TSERFIE              SPI_IER_TSERFIE_Msk                         /*!<TSERF interrupt enable                 */

/*******************  Bit definition for SPI_SR register  ********************/
#define SPI_SR_RXP_Pos              (0U)
#define SPI_SR_RXP_Msk              (0x1U << SPI_SR_RXP_Pos)                   /*!< 0x00000001 */
#define SPI_SR_RXP                  SPI_SR_RXP_Msk                             /*!<Rx-Packet available            */
#define SPI_SR_TXP_Pos              (1U)
#define SPI_SR_TXP_Msk              (0x1U << SPI_SR_TXP_Pos)                   /*!< 0x00000002 */
#define SPI_SR_TXP                  SPI_SR_TXP_Msk                             /*!<Tx-Packet space available      */
#define SPI_SR_DXP_Pos              (2U)
#define SPI_SR_DXP_Msk              (0x1U << SPI_SR_DXP_Pos)                   /*!< 0x00000004 */
#define SPI_SR_DXP                  SPI_SR_DXP_Msk                             /*!<Duplex Packet available         */
#define SPI_SR_EOT_Pos              (3U)
#define SPI_SR_EOT_Msk              (0x1U << SPI_SR_EOT_Pos)                   /*!< 0x00000008 */
#define SPI_SR_EOT                  SPI_SR_EOT_Msk                             /*!<Duplex Packet available         */
#define SPI_SR_TXTF_Pos             (4U)
#define SPI_SR_TXTF_Msk             (0x1U << SPI_SR_TXTF_Pos)                  /*!< 0x00000010 */
#define SPI_SR_TXTF                 SPI_SR_TXTF_Msk                            /*!<Transmission Transfer Filled    */
#define SPI_SR_UDR_Pos              (5U)
#define SPI_SR_UDR_Msk              (0x1U << SPI_SR_UDR_Pos)                   /*!< 0x00000020 */
#define SPI_SR_UDR                  SPI_SR_UDR_Msk                             /*!<UDR at Slave transmission       */
#define SPI_SR_OVR_Pos              (6U)
#define SPI_SR_OVR_Msk              (0x1U << SPI_SR_OVR_Pos)                   /*!< 0x00000040 */
#define SPI_SR_OVR                  SPI_SR_OVR_Msk                             /*!<Rx-Packet available            */
#define SPI_SR_CRCE_Pos             (7U)
#define SPI_SR_CRCE_Msk             (0x1U << SPI_SR_CRCE_Pos)                  /*!< 0x00000080 */
#define SPI_SR_CRCE                 SPI_SR_CRCE_Msk                            /*!<CRC Error Detected              */
#define SPI_SR_TIFRE_Pos            (8U)
#define SPI_SR_TIFRE_Msk            (0x1U << SPI_SR_TIFRE_Pos)                 /*!< 0x00000100 */
#define SPI_SR_TIFRE                SPI_SR_TIFRE_Msk                           /*!<TI frame format error Detected  */
#define SPI_SR_MODF_Pos             (9U)
#define SPI_SR_MODF_Msk             (0x1U << SPI_SR_MODF_Pos)                  /*!< 0x00000200 */
#define SPI_SR_MODF                 SPI_SR_MODF_Msk                            /*!<Mode Fault Detected             */
#define SPI_SR_TSERF_Pos            (10U)
#define SPI_SR_TSERF_Msk            (0x1U << SPI_SR_TSERF_Pos)                 /*!< 0x00000400 */
#define SPI_SR_TSERF                SPI_SR_TSERF_Msk                           /*!<Additional number of SPI data to be transacted was reload */
#define SPI_SR_SUSP_Pos             (11U)
#define SPI_SR_SUSP_Msk             (0x1U << SPI_SR_SUSP_Pos)                  /*!< 0x00000800 */
#define SPI_SR_SUSP                 SPI_SR_SUSP_Msk                            /*!<SUSP is set by hardware  */
#define SPI_SR_TXC_Pos              (12U)
#define SPI_SR_TXC_Msk              (0x1U << SPI_SR_TXC_Pos)                   /*!< 0x00001000 */
#define SPI_SR_TXC                  SPI_SR_TXC_Msk                             /*!<TxFIFO transmission complete */
#define SPI_SR_RXPLVL_Pos           (13U)
#define SPI_SR_RXPLVL_Msk           (0x3U << SPI_SR_RXPLVL_Pos)                /*!< 0x00006000 */
#define SPI_SR_RXPLVL               SPI_SR_RXPLVL_Msk                          /*!<RxFIFO Packing Level                             */
#define SPI_SR_RXPLVL_0             (0x1U << SPI_SR_RXPLVL_Pos)                /*!< 0x00002000 */
#define SPI_SR_RXPLVL_1             (0x2U << SPI_SR_RXPLVL_Pos)                /*!< 0x00004000 */
#define SPI_SR_RXWNE_Pos            (15U)
#define SPI_SR_RXWNE_Msk            (0x1U << SPI_SR_RXWNE_Pos)                 /*!< 0x00008000 */
#define SPI_SR_RXWNE                SPI_SR_RXWNE_Msk                           /*!<Rx FIFO Word Not Empty                           */
#define SPI_SR_CTSIZE_Pos           (16U)
#define SPI_SR_CTSIZE_Msk           (0xFFFFU << SPI_SR_CTSIZE_Pos)             /*!< 0xFFFF0000 */
#define SPI_SR_CTSIZE               SPI_SR_CTSIZE_Msk                          /*!<Number of data frames remaining in TSIZE         */

/*******************  Bit definition for SPI_IFCR register  ********************/
#define SPI_IFCR_EOTC_Pos           (3U)
#define SPI_IFCR_EOTC_Msk           (0x1U << SPI_IFCR_EOTC_Pos)                /*!< 0x00000008 */
#define SPI_IFCR_EOTC               SPI_IFCR_EOTC_Msk                          /*!<End Of Transfer flag clear              */
#define SPI_IFCR_TXTFC_Pos          (4U)
#define SPI_IFCR_TXTFC_Msk          (0x1U << SPI_IFCR_TXTFC_Pos)               /*!< 0x00000010 */
#define SPI_IFCR_TXTFC              SPI_IFCR_TXTFC_Msk                         /*!<Transmission Transfer Filled flag clear */
#define SPI_IFCR_UDRC_Pos           (5U)
#define SPI_IFCR_UDRC_Msk           (0x1U << SPI_IFCR_UDRC_Pos)                /*!< 0x00000020 */
#define SPI_IFCR_UDRC               SPI_IFCR_UDRC_Msk                          /*!<Underrun flag clear                     */
#define SPI_IFCR_OVRC_Pos           (6U)
#define SPI_IFCR_OVRC_Msk           (0x1U << SPI_IFCR_OVRC_Pos)                /*!< 0x00000040 */
#define SPI_IFCR_OVRC               SPI_IFCR_OVRC_Msk                          /*!<Overrun flag clear                      */
#define SPI_IFCR_CRCEC_Pos          (7U)
#define SPI_IFCR_CRCEC_Msk          (0x1U << SPI_IFCR_CRCEC_Pos)               /*!< 0x00000080 */
#define SPI_IFCR_CRCEC              SPI_IFCR_CRCEC_Msk                         /*!<CRC Error flag clear                    */
#define SPI_IFCR_TIFREC_Pos         (8U)
#define SPI_IFCR_TIFREC_Msk         (0x1U << SPI_IFCR_TIFREC_Pos)              /*!< 0x00000100 */
#define SPI_IFCR_TIFREC             SPI_IFCR_TIFREC_Msk                        /*!<TI frame format error flag clear        */
#define SPI_IFCR_MODFC_Pos          (9U)
#define SPI_IFCR_MODFC_Msk          (0x1U << SPI_IFCR_MODFC_Pos)               /*!< 0x00000200 */
#define SPI_IFCR_MODFC              SPI_IFCR_MODFC_Msk                         /*!<Mode Fault flag clear                   */
#define SPI_IFCR_TSERFC_Pos         (10U)
#define SPI_IFCR_TSERFC_Msk         (0x1U << SPI_IFCR_TSERFC_Pos)              /*!< 0x00000400 */
#define SPI_IFCR_TSERFC             SPI_IFCR_TSERFC_Msk                        /*!<TSERFC flag clear                       */
#define SPI_IFCR_SUSPC_Pos          (11U)
#define SPI_IFCR_SUSPC_Msk          (0x1U << SPI_IFCR_SUSPC_Pos)               /*!< 0x00000800 */
#define SPI_IFCR_SUSPC              SPI_IFCR_SUSPC_Msk                         /*!<SUSPend flag clear                      */

/*******************  Bit definition for SPI_TXDR register  ********************/
#define SPI_TXDR_TXDR_Pos           (0U)                                       
#define SPI_TXDR_TXDR_Msk           (0xFFFFFFFFU << SPI_TXDR_TXDR_Pos)         /*!< 0xFFFFFFFF */
#define SPI_TXDR_TXDR               SPI_TXDR_TXDR_Msk                          /* Transmit Data Register */

/*******************  Bit definition for SPI_RXDR register  ********************/
#define SPI_RXDR_RXDR_Pos           (0U)                                       
#define SPI_RXDR_RXDR_Msk           (0xFFFFFFFFU << SPI_RXDR_RXDR_Pos)         /*!< 0xFFFFFFFF */
#define SPI_RXDR_RXDR               SPI_RXDR_RXDR_Msk                          /* Receive Data Register  */

/*******************  Bit definition for SPI_CRCPOLY register  ********************/
#define SPI_CRCPOLY_CRCPOLY_Pos     (0U)                                       
#define SPI_CRCPOLY_CRCPOLY_Msk     (0xFFFFFFFFU << SPI_CRCPOLY_CRCPOLY_Pos)   /*!< 0xFFFFFFFF */
#define SPI_CRCPOLY_CRCPOLY         SPI_CRCPOLY_CRCPOLY_Msk                    /* CRC Polynomial register  */

/*******************  Bit definition for SPI_TXCRC register  ********************/
#define SPI_TXCRC_TXCRC_Pos         (0U)                                       
#define SPI_TXCRC_TXCRC_Msk         (0xFFFFFFFFU << SPI_TXCRC_TXCRC_Pos)       /*!< 0xFFFFFFFF */
#define SPI_TXCRC_TXCRC             SPI_TXCRC_TXCRC_Msk                        /* CRCRegister for transmitter */

/*******************  Bit definition for SPI_RXCRC register  ********************/
#define SPI_RXCRC_RXCRC_Pos         (0U)                                       
#define SPI_RXCRC_RXCRC_Msk         (0xFFFFFFFFU << SPI_RXCRC_RXCRC_Pos)       /*!< 0xFFFFFFFF */
#define SPI_RXCRC_RXCRC             SPI_RXCRC_RXCRC_Msk                        /* CRCRegister for receiver */

/*******************  Bit definition for SPI_UDRDR register  ********************/
#define SPI_UDRDR_UDRDR_Pos         (0U)                                       
#define SPI_UDRDR_UDRDR_Msk         (0xFFFFFFFFU << SPI_UDRDR_UDRDR_Pos)       /*!< 0xFFFFFFFF */
#define SPI_UDRDR_UDRDR             SPI_UDRDR_UDRDR_Msk                        /* Data at slave underrun condition */

/******************  Bit definition for SPI_I2SCFGR register  *****************/
#define SPI_I2SCFGR_I2SMOD_Pos      (0U)
#define SPI_I2SCFGR_I2SMOD_Msk      (0x1U << SPI_I2SCFGR_I2SMOD_Pos)           /*!< 0x00000001 */
#define SPI_I2SCFGR_I2SMOD          SPI_I2SCFGR_I2SMOD_Msk                     /*!<I2S mode selection */
#define SPI_I2SCFGR_I2SCFG_Pos      (1U)
#define SPI_I2SCFGR_I2SCFG_Msk      (0x7U << SPI_I2SCFGR_I2SCFG_Pos)           /*!< 0x0000000E */
#define SPI_I2SCFGR_I2SCFG          SPI_I2SCFGR_I2SCFG_Msk                     /*!<I2SCFGR[1:0] bits (I2S configuration mode) */
#define SPI_I2SCFGR_I2SCFG_0        (0x1U << SPI_I2SCFGR_I2SCFG_Pos)           /*!< 0x00000002 */
#define SPI_I2SCFGR_I2SCFG_1        (0x2U << SPI_I2SCFGR_I2SCFG_Pos)           /*!< 0x00000004 */
#define SPI_I2SCFGR_I2SCFG_2        (0x4U << SPI_I2SCFGR_I2SCFG_Pos)           /*!< 0x00000008 */
#define SPI_I2SCFGR_I2SSTD_Pos      (4U)
#define SPI_I2SCFGR_I2SSTD_Msk      (0x3U << SPI_I2SCFGR_I2SSTD_Pos)           /*!< 0x00000030 */
#define SPI_I2SCFGR_I2SSTD          SPI_I2SCFGR_I2SSTD_Msk                     /*!<I2SSTD[1:0] I2S standard selection                */
#define SPI_I2SCFGR_I2SSTD_0        (0x1U << SPI_I2SCFGR_I2SSTD_Pos)           /*!< 0x00000010 */
#define SPI_I2SCFGR_I2SSTD_1        (0x2U << SPI_I2SCFGR_I2SSTD_Pos)           /*!< 0x00000020 */
#define SPI_I2SCFGR_PCMSYNC_Pos     (7U)
#define SPI_I2SCFGR_PCMSYNC_Msk     (0x1U << SPI_I2SCFGR_PCMSYNC_Pos)          /*!< 0x00000080 */
#define SPI_I2SCFGR_PCMSYNC         SPI_I2SCFGR_PCMSYNC_Msk                    /*!<PCM frame synchronization                         */
#define SPI_I2SCFGR_DATLEN_Pos      (8U)
#define SPI_I2SCFGR_DATLEN_Msk      (0x3U << SPI_I2SCFGR_DATLEN_Pos)           /*!< 0x00000300 */
#define SPI_I2SCFGR_DATLEN          SPI_I2SCFGR_DATLEN_Msk                     /*!<DATLEN[1:0] Data length to be transferred         */
#define SPI_I2SCFGR_DATLEN_0        (0x1U << SPI_I2SCFGR_DATLEN_Pos)           /*!< 0x00000100 */
#define SPI_I2SCFGR_DATLEN_1        (0x2U << SPI_I2SCFGR_DATLEN_Pos)           /*!< 0x00000200 */
#define SPI_I2SCFGR_CHLEN_Pos       (10U)
#define SPI_I2SCFGR_CHLEN_Msk       (0x1U << SPI_I2SCFGR_CHLEN_Pos)            /*!< 0x00000400 */
#define SPI_I2SCFGR_CHLEN           SPI_I2SCFGR_CHLEN_Msk                      /*!<Channel length (number of bits per audio channel) */
#define SPI_I2SCFGR_CKPOL_Pos       (11U)
#define SPI_I2SCFGR_CKPOL_Msk       (0x1U << SPI_I2SCFGR_CKPOL_Pos)            /*!< 0x00000800 */
#define SPI_I2SCFGR_CKPOL           SPI_I2SCFGR_CKPOL_Msk                      /*!<Steady state clock polarity                       */
#define SPI_I2SCFGR_FIXCH_Pos       (12U)
#define SPI_I2SCFGR_FIXCH_Msk       (0x1U << SPI_I2SCFGR_FIXCH_Pos)            /*!< 0x00001000 */
#define SPI_I2SCFGR_FIXCH           SPI_I2SCFGR_FIXCH_Msk                      /*!<Fixed channel length in SLAVE                     */
#define SPI_I2SCFGR_WSINV_Pos       (13U)
#define SPI_I2SCFGR_WSINV_Msk       (0x1U << SPI_I2SCFGR_WSINV_Pos)            /*!< 0x00002000 */
#define SPI_I2SCFGR_WSINV           SPI_I2SCFGR_WSINV_Msk                      /*!<Word select inversion                             */
#define SPI_I2SCFGR_DATFMT_Pos      (14U)
#define SPI_I2SCFGR_DATFMT_Msk      (0x1U << SPI_I2SCFGR_DATFMT_Pos)           /*!< 0x00003000 */
#define SPI_I2SCFGR_DATFMT          SPI_I2SCFGR_DATFMT_Msk                     /*!<Data format                                       */
#define SPI_I2SCFGR_I2SDIV_Pos      (16U)                                      
#define SPI_I2SCFGR_I2SDIV_Msk      (0xFFU << SPI_I2SCFGR_I2SDIV_Pos)          /*!< 0x00FF0000 */
#define SPI_I2SCFGR_I2SDIV          SPI_I2SCFGR_I2SDIV_Msk                     /*!<I2S Linear prescaler */
#define SPI_I2SCFGR_ODD_Pos         (24U)
#define SPI_I2SCFGR_ODD_Msk         (0x1U << SPI_I2SCFGR_ODD_Pos)              /*!< 0x01000000 */
#define SPI_I2SCFGR_ODD             SPI_I2SCFGR_ODD_Msk                        /*!<Odd factor for the prescaler */
#define SPI_I2SCFGR_MCKOE_Pos       (25U)
#define SPI_I2SCFGR_MCKOE_Msk       (0x1U << SPI_I2SCFGR_MCKOE_Pos)            /*!< 0x02000000 */
#define SPI_I2SCFGR_MCKOE           SPI_I2SCFGR_MCKOE_Msk                      /*!<Master Clock Output Enable */

/**********************  Bit definition for SPI_HWCFGR register  ***************/
#define SPI_HWCFGR_TXFCFG_Pos    (0U)
#define SPI_HWCFGR_TXFCFG_Msk    (0xFU << SPI_HWCFGR_TXFCFG_Pos)               /*!< 0x0000000F */
#define SPI_HWCFGR_TXFCFG        SPI_HWCFGR_TXFCFG_Msk                         /*!< TxFIFO size */
#define SPI_HWCFGR_RXFCFG_Pos    (4U)
#define SPI_HWCFGR_RXFCFG_Msk    (0xFU << SPI_HWCFGR_RXFCFG_Pos)               /*!< 0x0000000F */
#define SPI_HWCFGR_RXFCFG        SPI_HWCFGR_RXFCFG_Msk                         /*!< RxFIFO size */
#define SPI_HWCFGR_CRCCFG_Pos    (8U)
#define SPI_HWCFGR_CRCCFG_Msk    (0xFU << SPI_HWCFGR_CRCCFG_Pos)               /*!< 0x0000000F */
#define SPI_HWCFGR_CRCCFG        SPI_HWCFGR_CRCCFG_Msk                         /*!< CRC configuration for SPI */
#define SPI_HWCFGR_I2SCFG_Pos    (12U)
#define SPI_HWCFGR_I2SCFG_Msk    (0xFU << SPI_HWCFGR_I2SCFG_Pos)               /*!< 0x0000000F */
#define SPI_HWCFGR_I2SCFG        SPI_HWCFGR_I2SCFG_Msk                         /*!< I2S configuration */
#define SPI_HWCFGR_DSCFG_Pos     (16U)
#define SPI_HWCFGR_DSCFG_Msk     (0xFU << SPI_HWCFGR_DSCFG_Pos)                /*!< 0x0000000F */
#define SPI_HWCFGR_DSCFG         SPI_HWCFGR_DSCFG_Msk                          /*!< SPI data size configuration */

/**********************  Bit definition for SPI_VERR register  *****************/
#define SPI_VERR_MINREV_Pos      (0U)
#define SPI_VERR_MINREV_Msk      (0xFU << SPI_VERR_MINREV_Pos)               /*!< 0x0000000F */
#define SPI_VERR_MINREV          SPI_VERR_MINREV_Msk                         /*!< Minor Revision number */
#define SPI_VERR_MAJREV_Pos      (4U)
#define SPI_VERR_MAJREV_Msk      (0xFU << SPI_VERR_MAJREV_Pos)               /*!< 0x000000F0 */
#define SPI_VERR_MAJREV          SPI_VERR_MAJREV_Msk                         /*!< Major Revision number */

/**********************  Bit definition for SPI_IPIDR register  ****************/
#define SPI_IPIDR_IPID_Pos       (0U)
#define SPI_IPIDR_IPID_Msk       (0xFFFFFFFFU << SPI_IPIDR_IPID_Pos)         /*!< 0xFFFFFFFF */
#define SPI_IPIDR_IPID           SPI_IPIDR_IPID_Msk                          /*!< IP Identification */

/**********************  Bit definition for SPI_SIDR register  *****************/
#define SPI_SIDR_SID_Pos         (0U)
#define SPI_SIDR_SID_Msk         (0xFFFFFFFFU << SPI_SIDR_SID_Pos)           /*!< 0xFFFFFFFF */
#define SPI_SIDR_SID             SPI_SIDR_SID_Msk                            /*!< IP size identification */

/******************************************************************************/
/*                                                                            */
/*                                    QUADSPI                                 */
/*                                                                            */
/******************************************************************************/
/*****************  Bit definition for QUADSPI_CR register  *******************/
#define QUADSPI_CR_EN_Pos                (0U)
#define QUADSPI_CR_EN_Msk                (0x1U << QUADSPI_CR_EN_Pos)           /*!< 0x00000001 */
#define QUADSPI_CR_EN                    QUADSPI_CR_EN_Msk                     /*!< Enable */
#define QUADSPI_CR_ABORT_Pos             (1U)
#define QUADSPI_CR_ABORT_Msk             (0x1U << QUADSPI_CR_ABORT_Pos)        /*!< 0x00000002 */
#define QUADSPI_CR_ABORT                 QUADSPI_CR_ABORT_Msk                  /*!< Abort request */
#define QUADSPI_CR_DMAEN_Pos             (2U)
#define QUADSPI_CR_DMAEN_Msk             (0x1U << QUADSPI_CR_DMAEN_Pos)        /*!< 0x00000004 */
#define QUADSPI_CR_DMAEN                 QUADSPI_CR_DMAEN_Msk                  /*!< DMA Enable */
#define QUADSPI_CR_TCEN_Pos              (3U)
#define QUADSPI_CR_TCEN_Msk              (0x1U << QUADSPI_CR_TCEN_Pos)         /*!< 0x00000008 */
#define QUADSPI_CR_TCEN                  QUADSPI_CR_TCEN_Msk                   /*!< Timeout Counter Enable */
#define QUADSPI_CR_SSHIFT_Pos            (4U)
#define QUADSPI_CR_SSHIFT_Msk            (0x1U << QUADSPI_CR_SSHIFT_Pos)       /*!< 0x00000010 */
#define QUADSPI_CR_SSHIFT                QUADSPI_CR_SSHIFT_Msk                 /*!< SSHIFT Sample Shift */
#define QUADSPI_CR_DFM_Pos               (6U)
#define QUADSPI_CR_DFM_Msk               (0x1U << QUADSPI_CR_DFM_Pos)          /*!< 0x00000040 */
#define QUADSPI_CR_DFM                   QUADSPI_CR_DFM_Msk                    /*!< Dual Flash Mode */
#define QUADSPI_CR_FSEL_Pos              (7U)
#define QUADSPI_CR_FSEL_Msk              (0x1U << QUADSPI_CR_FSEL_Pos)         /*!< 0x00000080 */
#define QUADSPI_CR_FSEL                  QUADSPI_CR_FSEL_Msk                   /*!< Flash Select */
#define QUADSPI_CR_FTHRES_Pos            (8U)
#define QUADSPI_CR_FTHRES_Msk            (0xFU << QUADSPI_CR_FTHRES_Pos)       /*!< 0x00000F00 */
#define QUADSPI_CR_FTHRES                QUADSPI_CR_FTHRES_Msk                 /*!< FTHRES[3:0] FIFO Level */
#define QUADSPI_CR_FTHRES_0              (0x1U << QUADSPI_CR_FTHRES_Pos)       /*!< 0x00000100 */
#define QUADSPI_CR_FTHRES_1              (0x2U << QUADSPI_CR_FTHRES_Pos)       /*!< 0x00000200 */
#define QUADSPI_CR_FTHRES_2              (0x4U << QUADSPI_CR_FTHRES_Pos)       /*!< 0x00000400 */
#define QUADSPI_CR_FTHRES_3              (0x8U << QUADSPI_CR_FTHRES_Pos)       /*!< 0x00000800 */
#define QUADSPI_CR_TEIE_Pos              (16U)
#define QUADSPI_CR_TEIE_Msk              (0x1U << QUADSPI_CR_TEIE_Pos)         /*!< 0x00010000 */
#define QUADSPI_CR_TEIE                  QUADSPI_CR_TEIE_Msk                   /*!< Transfer Error Interrupt Enable */
#define QUADSPI_CR_TCIE_Pos              (17U)
#define QUADSPI_CR_TCIE_Msk              (0x1U << QUADSPI_CR_TCIE_Pos)         /*!< 0x00020000 */
#define QUADSPI_CR_TCIE                  QUADSPI_CR_TCIE_Msk                   /*!< Transfer Complete Interrupt Enable */
#define QUADSPI_CR_FTIE_Pos              (18U)
#define QUADSPI_CR_FTIE_Msk              (0x1U << QUADSPI_CR_FTIE_Pos)         /*!< 0x00040000 */
#define QUADSPI_CR_FTIE                  QUADSPI_CR_FTIE_Msk                   /*!< FIFO Threshold Interrupt Enable */
#define QUADSPI_CR_SMIE_Pos              (19U)
#define QUADSPI_CR_SMIE_Msk              (0x1U << QUADSPI_CR_SMIE_Pos)         /*!< 0x00080000 */
#define QUADSPI_CR_SMIE                  QUADSPI_CR_SMIE_Msk                   /*!< Status Match Interrupt Enable */
#define QUADSPI_CR_TOIE_Pos              (20U)
#define QUADSPI_CR_TOIE_Msk              (0x1U << QUADSPI_CR_TOIE_Pos)         /*!< 0x00100000 */
#define QUADSPI_CR_TOIE                  QUADSPI_CR_TOIE_Msk                   /*!< TimeOut Interrupt Enable */
#define QUADSPI_CR_APMS_Pos              (22U)
#define QUADSPI_CR_APMS_Msk              (0x1U << QUADSPI_CR_APMS_Pos)         /*!< 0x00400000 */
#define QUADSPI_CR_APMS                  QUADSPI_CR_APMS_Msk                   /*!< Bit 1 */
#define QUADSPI_CR_PMM_Pos               (23U)
#define QUADSPI_CR_PMM_Msk               (0x1U << QUADSPI_CR_PMM_Pos)          /*!< 0x00800000 */
#define QUADSPI_CR_PMM                   QUADSPI_CR_PMM_Msk                    /*!< Polling Match Mode */
#define QUADSPI_CR_PRESCALER_Pos         (24U)
#define QUADSPI_CR_PRESCALER_Msk         (0xFFU << QUADSPI_CR_PRESCALER_Pos)   /*!< 0xFF000000 */
#define QUADSPI_CR_PRESCALER             QUADSPI_CR_PRESCALER_Msk              /*!< PRESCALER[7:0] Clock prescaler */
#define QUADSPI_CR_PRESCALER_0           (0x01U << QUADSPI_CR_PRESCALER_Pos)   /*!< 0x01000000 */
#define QUADSPI_CR_PRESCALER_1           (0x02U << QUADSPI_CR_PRESCALER_Pos)   /*!< 0x02000000 */
#define QUADSPI_CR_PRESCALER_2           (0x04U << QUADSPI_CR_PRESCALER_Pos)   /*!< 0x04000000 */
#define QUADSPI_CR_PRESCALER_3           (0x08U << QUADSPI_CR_PRESCALER_Pos)   /*!< 0x08000000 */
#define QUADSPI_CR_PRESCALER_4           (0x10U << QUADSPI_CR_PRESCALER_Pos)   /*!< 0x10000000 */
#define QUADSPI_CR_PRESCALER_5           (0x20U << QUADSPI_CR_PRESCALER_Pos)   /*!< 0x20000000 */
#define QUADSPI_CR_PRESCALER_6           (0x40U << QUADSPI_CR_PRESCALER_Pos)   /*!< 0x40000000 */
#define QUADSPI_CR_PRESCALER_7           (0x80U << QUADSPI_CR_PRESCALER_Pos)   /*!< 0x80000000 */

/*****************  Bit definition for QUADSPI_DCR register  ******************/
#define QUADSPI_DCR_CKMODE_Pos           (0U)
#define QUADSPI_DCR_CKMODE_Msk           (0x1U << QUADSPI_DCR_CKMODE_Pos)      /*!< 0x00000001 */
#define QUADSPI_DCR_CKMODE               QUADSPI_DCR_CKMODE_Msk                /*!< Mode 0 / Mode 3 */
#define QUADSPI_DCR_CSHT_Pos             (8U)
#define QUADSPI_DCR_CSHT_Msk             (0x7U << QUADSPI_DCR_CSHT_Pos)        /*!< 0x00000700 */
#define QUADSPI_DCR_CSHT                 QUADSPI_DCR_CSHT_Msk                  /*!< CSHT[2:0]: ChipSelect High Time */
#define QUADSPI_DCR_CSHT_0               (0x1U << QUADSPI_DCR_CSHT_Pos)        /*!< 0x00000100 */
#define QUADSPI_DCR_CSHT_1               (0x2U << QUADSPI_DCR_CSHT_Pos)        /*!< 0x00000200 */
#define QUADSPI_DCR_CSHT_2               (0x4U << QUADSPI_DCR_CSHT_Pos)        /*!< 0x00000400 */
#define QUADSPI_DCR_FSIZE_Pos            (16U)
#define QUADSPI_DCR_FSIZE_Msk            (0x1FU << QUADSPI_DCR_FSIZE_Pos)      /*!< 0x001F0000 */
#define QUADSPI_DCR_FSIZE                QUADSPI_DCR_FSIZE_Msk                 /*!< FSIZE[4:0]: Flash Size */
#define QUADSPI_DCR_FSIZE_0              (0x01U << QUADSPI_DCR_FSIZE_Pos)      /*!< 0x00010000 */
#define QUADSPI_DCR_FSIZE_1              (0x02U << QUADSPI_DCR_FSIZE_Pos)      /*!< 0x00020000 */
#define QUADSPI_DCR_FSIZE_2              (0x04U << QUADSPI_DCR_FSIZE_Pos)      /*!< 0x00040000 */
#define QUADSPI_DCR_FSIZE_3              (0x08U << QUADSPI_DCR_FSIZE_Pos)      /*!< 0x00080000 */
#define QUADSPI_DCR_FSIZE_4              (0x10U << QUADSPI_DCR_FSIZE_Pos)      /*!< 0x00100000 */

/******************  Bit definition for QUADSPI_SR register  *******************/
#define QUADSPI_SR_TEF_Pos               (0U)
#define QUADSPI_SR_TEF_Msk               (0x1U << QUADSPI_SR_TEF_Pos)          /*!< 0x00000001 */
#define QUADSPI_SR_TEF                   QUADSPI_SR_TEF_Msk                    /*!< Transfer Error Flag */
#define QUADSPI_SR_TCF_Pos               (1U)
#define QUADSPI_SR_TCF_Msk               (0x1U << QUADSPI_SR_TCF_Pos)          /*!< 0x00000002 */
#define QUADSPI_SR_TCF                   QUADSPI_SR_TCF_Msk                    /*!< Transfer Complete Flag */
#define QUADSPI_SR_FTF_Pos               (2U)
#define QUADSPI_SR_FTF_Msk               (0x1U << QUADSPI_SR_FTF_Pos)          /*!< 0x00000004 */
#define QUADSPI_SR_FTF                   QUADSPI_SR_FTF_Msk                    /*!< FIFO Threshlod Flag */
#define QUADSPI_SR_SMF_Pos               (3U)
#define QUADSPI_SR_SMF_Msk               (0x1U << QUADSPI_SR_SMF_Pos)          /*!< 0x00000008 */
#define QUADSPI_SR_SMF                   QUADSPI_SR_SMF_Msk                    /*!< Status Match Flag */
#define QUADSPI_SR_TOF_Pos               (4U)
#define QUADSPI_SR_TOF_Msk               (0x1U << QUADSPI_SR_TOF_Pos)          /*!< 0x00000010 */
#define QUADSPI_SR_TOF                   QUADSPI_SR_TOF_Msk                    /*!< Timeout Flag */
#define QUADSPI_SR_BUSY_Pos              (5U)
#define QUADSPI_SR_BUSY_Msk              (0x1U << QUADSPI_SR_BUSY_Pos)         /*!< 0x00000020 */
#define QUADSPI_SR_BUSY                  QUADSPI_SR_BUSY_Msk                   /*!< Busy */
#define QUADSPI_SR_FLEVEL_Pos            (8U)
#define QUADSPI_SR_FLEVEL_Msk            (0x1FU << QUADSPI_SR_FLEVEL_Pos)      /*!< 0x00001F00 */
#define QUADSPI_SR_FLEVEL                QUADSPI_SR_FLEVEL_Msk                 /*!< FIFO Threshlod Flag */
#define QUADSPI_SR_FLEVEL_0              (0x01U << QUADSPI_SR_FLEVEL_Pos)      /*!< 0x00000100 */
#define QUADSPI_SR_FLEVEL_1              (0x02U << QUADSPI_SR_FLEVEL_Pos)      /*!< 0x00000200 */
#define QUADSPI_SR_FLEVEL_2              (0x04U << QUADSPI_SR_FLEVEL_Pos)      /*!< 0x00000400 */
#define QUADSPI_SR_FLEVEL_3              (0x08U << QUADSPI_SR_FLEVEL_Pos)      /*!< 0x00000800 */
#define QUADSPI_SR_FLEVEL_4              (0x10U << QUADSPI_SR_FLEVEL_Pos)      /*!< 0x00001000 */

/******************  Bit definition for QUADSPI_FCR register  ******************/
#define QUADSPI_FCR_CTEF_Pos             (0U)
#define QUADSPI_FCR_CTEF_Msk             (0x1U << QUADSPI_FCR_CTEF_Pos)        /*!< 0x00000001 */
#define QUADSPI_FCR_CTEF                 QUADSPI_FCR_CTEF_Msk                  /*!< Clear Transfer Error Flag */
#define QUADSPI_FCR_CTCF_Pos             (1U)
#define QUADSPI_FCR_CTCF_Msk             (0x1U << QUADSPI_FCR_CTCF_Pos)        /*!< 0x00000002 */
#define QUADSPI_FCR_CTCF                 QUADSPI_FCR_CTCF_Msk                  /*!< Clear Transfer Complete Flag */
#define QUADSPI_FCR_CSMF_Pos             (3U)
#define QUADSPI_FCR_CSMF_Msk             (0x1U << QUADSPI_FCR_CSMF_Pos)        /*!< 0x00000008 */
#define QUADSPI_FCR_CSMF                 QUADSPI_FCR_CSMF_Msk                  /*!< Clear Status Match Flag */
#define QUADSPI_FCR_CTOF_Pos             (4U)
#define QUADSPI_FCR_CTOF_Msk             (0x1U << QUADSPI_FCR_CTOF_Pos)        /*!< 0x00000010 */
#define QUADSPI_FCR_CTOF                 QUADSPI_FCR_CTOF_Msk                  /*!< Clear Timeout Flag */

/******************  Bit definition for QUADSPI_DLR register  ******************/
#define QUADSPI_DLR_DL_Pos               (0U)
#define QUADSPI_DLR_DL_Msk               (0xFFFFFFFFU << QUADSPI_DLR_DL_Pos)   /*!< 0xFFFFFFFF */
#define QUADSPI_DLR_DL                   QUADSPI_DLR_DL_Msk                    /*!< DL[31:0]: Data Length */

/******************  Bit definition for QUADSPI_CCR register  ******************/
#define QUADSPI_CCR_INSTRUCTION_Pos      (0U)
#define QUADSPI_CCR_INSTRUCTION_Msk      (0xFFU << QUADSPI_CCR_INSTRUCTION_Pos) /*!< 0x000000FF */
#define QUADSPI_CCR_INSTRUCTION          QUADSPI_CCR_INSTRUCTION_Msk           /*!< INSTRUCTION[7:0]: Instruction */
#define QUADSPI_CCR_INSTRUCTION_0        (0x01U << QUADSPI_CCR_INSTRUCTION_Pos) /*!< 0x00000001 */
#define QUADSPI_CCR_INSTRUCTION_1        (0x02U << QUADSPI_CCR_INSTRUCTION_Pos) /*!< 0x00000002 */
#define QUADSPI_CCR_INSTRUCTION_2        (0x04U << QUADSPI_CCR_INSTRUCTION_Pos) /*!< 0x00000004 */
#define QUADSPI_CCR_INSTRUCTION_3        (0x08U << QUADSPI_CCR_INSTRUCTION_Pos) /*!< 0x00000008 */
#define QUADSPI_CCR_INSTRUCTION_4        (0x10U << QUADSPI_CCR_INSTRUCTION_Pos) /*!< 0x00000010 */
#define QUADSPI_CCR_INSTRUCTION_5        (0x20U << QUADSPI_CCR_INSTRUCTION_Pos) /*!< 0x00000020 */
#define QUADSPI_CCR_INSTRUCTION_6        (0x40U << QUADSPI_CCR_INSTRUCTION_Pos) /*!< 0x00000040 */
#define QUADSPI_CCR_INSTRUCTION_7        (0x80U << QUADSPI_CCR_INSTRUCTION_Pos) /*!< 0x00000080 */
#define QUADSPI_CCR_IMODE_Pos            (8U)
#define QUADSPI_CCR_IMODE_Msk            (0x3U << QUADSPI_CCR_IMODE_Pos)       /*!< 0x00000300 */
#define QUADSPI_CCR_IMODE                QUADSPI_CCR_IMODE_Msk                 /*!< IMODE[1:0]: Instruction Mode */
#define QUADSPI_CCR_IMODE_0              (0x1U << QUADSPI_CCR_IMODE_Pos)       /*!< 0x00000100 */
#define QUADSPI_CCR_IMODE_1              (0x2U << QUADSPI_CCR_IMODE_Pos)       /*!< 0x00000200 */
#define QUADSPI_CCR_ADMODE_Pos           (10U)
#define QUADSPI_CCR_ADMODE_Msk           (0x3U << QUADSPI_CCR_ADMODE_Pos)      /*!< 0x00000C00 */
#define QUADSPI_CCR_ADMODE               QUADSPI_CCR_ADMODE_Msk                /*!< ADMODE[1:0]: Address Mode */
#define QUADSPI_CCR_ADMODE_0             (0x1U << QUADSPI_CCR_ADMODE_Pos)      /*!< 0x00000400 */
#define QUADSPI_CCR_ADMODE_1             (0x2U << QUADSPI_CCR_ADMODE_Pos)      /*!< 0x00000800 */
#define QUADSPI_CCR_ADSIZE_Pos           (12U)
#define QUADSPI_CCR_ADSIZE_Msk           (0x3U << QUADSPI_CCR_ADSIZE_Pos)      /*!< 0x00003000 */
#define QUADSPI_CCR_ADSIZE               QUADSPI_CCR_ADSIZE_Msk                /*!< ADSIZE[1:0]: Address Size */
#define QUADSPI_CCR_ADSIZE_0             (0x1U << QUADSPI_CCR_ADSIZE_Pos)      /*!< 0x00001000 */
#define QUADSPI_CCR_ADSIZE_1             (0x2U << QUADSPI_CCR_ADSIZE_Pos)      /*!< 0x00002000 */
#define QUADSPI_CCR_ABMODE_Pos           (14U)
#define QUADSPI_CCR_ABMODE_Msk           (0x3U << QUADSPI_CCR_ABMODE_Pos)      /*!< 0x0000C000 */
#define QUADSPI_CCR_ABMODE               QUADSPI_CCR_ABMODE_Msk                /*!< ABMODE[1:0]: Alternate Bytes Mode */
#define QUADSPI_CCR_ABMODE_0             (0x1U << QUADSPI_CCR_ABMODE_Pos)      /*!< 0x00004000 */
#define QUADSPI_CCR_ABMODE_1             (0x2U << QUADSPI_CCR_ABMODE_Pos)      /*!< 0x00008000 */
#define QUADSPI_CCR_ABSIZE_Pos           (16U)
#define QUADSPI_CCR_ABSIZE_Msk           (0x3U << QUADSPI_CCR_ABSIZE_Pos)      /*!< 0x00030000 */
#define QUADSPI_CCR_ABSIZE               QUADSPI_CCR_ABSIZE_Msk                /*!< ABSIZE[1:0]: Instruction Mode */
#define QUADSPI_CCR_ABSIZE_0             (0x1U << QUADSPI_CCR_ABSIZE_Pos)      /*!< 0x00010000 */
#define QUADSPI_CCR_ABSIZE_1             (0x2U << QUADSPI_CCR_ABSIZE_Pos)      /*!< 0x00020000 */
#define QUADSPI_CCR_DCYC_Pos             (18U)
#define QUADSPI_CCR_DCYC_Msk             (0x1FU << QUADSPI_CCR_DCYC_Pos)       /*!< 0x007C0000 */
#define QUADSPI_CCR_DCYC                 QUADSPI_CCR_DCYC_Msk                  /*!< DCYC[4:0]: Dummy Cycles */
#define QUADSPI_CCR_DCYC_0               (0x01U << QUADSPI_CCR_DCYC_Pos)       /*!< 0x00040000 */
#define QUADSPI_CCR_DCYC_1               (0x02U << QUADSPI_CCR_DCYC_Pos)       /*!< 0x00080000 */
#define QUADSPI_CCR_DCYC_2               (0x04U << QUADSPI_CCR_DCYC_Pos)       /*!< 0x00100000 */
#define QUADSPI_CCR_DCYC_3               (0x08U << QUADSPI_CCR_DCYC_Pos)       /*!< 0x00200000 */
#define QUADSPI_CCR_DCYC_4               (0x10U << QUADSPI_CCR_DCYC_Pos)       /*!< 0x00400000 */
#define QUADSPI_CCR_DMODE_Pos            (24U)
#define QUADSPI_CCR_DMODE_Msk            (0x3U << QUADSPI_CCR_DMODE_Pos)       /*!< 0x03000000 */
#define QUADSPI_CCR_DMODE                QUADSPI_CCR_DMODE_Msk                 /*!< DMODE[1:0]: Data Mode */
#define QUADSPI_CCR_DMODE_0              (0x1U << QUADSPI_CCR_DMODE_Pos)       /*!< 0x01000000 */
#define QUADSPI_CCR_DMODE_1              (0x2U << QUADSPI_CCR_DMODE_Pos)       /*!< 0x02000000 */
#define QUADSPI_CCR_FMODE_Pos            (26U)
#define QUADSPI_CCR_FMODE_Msk            (0x3U << QUADSPI_CCR_FMODE_Pos)       /*!< 0x0C000000 */
#define QUADSPI_CCR_FMODE                QUADSPI_CCR_FMODE_Msk                 /*!< FMODE[1:0]: Functional Mode */
#define QUADSPI_CCR_FMODE_0              (0x1U << QUADSPI_CCR_FMODE_Pos)       /*!< 0x04000000 */
#define QUADSPI_CCR_FMODE_1              (0x2U << QUADSPI_CCR_FMODE_Pos)       /*!< 0x08000000 */
#define QUADSPI_CCR_SIOO_Pos             (28U)
#define QUADSPI_CCR_SIOO_Msk             (0x1U << QUADSPI_CCR_SIOO_Pos)        /*!< 0x10000000 */
#define QUADSPI_CCR_SIOO                 QUADSPI_CCR_SIOO_Msk                  /*!< SIOO: Send Instruction Only Once Mode */
#define QUADSPI_CCR_DHHC_Pos             (30U)
#define QUADSPI_CCR_DHHC_Msk             (0x1U << QUADSPI_CCR_DHHC_Pos)        /*!< 0x40000000 */
#define QUADSPI_CCR_DHHC                 QUADSPI_CCR_DHHC_Msk                  /*!< DHHC: DDR hold half cycle */
#define QUADSPI_CCR_DDRM_Pos             (31U)
#define QUADSPI_CCR_DDRM_Msk             (0x1U << QUADSPI_CCR_DDRM_Pos)        /*!< 0x80000000 */
#define QUADSPI_CCR_DDRM                 QUADSPI_CCR_DDRM_Msk                  /*!< DDRM: Double Data Rate Mode */

/******************  Bit definition for QUADSPI_AR register  *******************/
#define QUADSPI_AR_ADDRESS_Pos           (0U)
#define QUADSPI_AR_ADDRESS_Msk           (0xFFFFFFFFU << QUADSPI_AR_ADDRESS_Pos) /*!< 0xFFFFFFFF */
#define QUADSPI_AR_ADDRESS               QUADSPI_AR_ADDRESS_Msk                /*!< ADDRESS[31:0]: Address */

/******************  Bit definition for QUADSPI_ABR register  ******************/
#define QUADSPI_ABR_ALTERNATE_Pos        (0U)
#define QUADSPI_ABR_ALTERNATE_Msk        (0xFFFFFFFFU << QUADSPI_ABR_ALTERNATE_Pos) /*!< 0xFFFFFFFF */
#define QUADSPI_ABR_ALTERNATE            QUADSPI_ABR_ALTERNATE_Msk             /*!< ALTERNATE[31:0]: Alternate Bytes */

/******************  Bit definition for QUADSPI_DR register  *******************/
#define QUADSPI_DR_DATA_Pos              (0U)
#define QUADSPI_DR_DATA_Msk              (0xFFFFFFFFU << QUADSPI_DR_DATA_Pos)  /*!< 0xFFFFFFFF */
#define QUADSPI_DR_DATA                  QUADSPI_DR_DATA_Msk                   /*!< DATA[31:0]: Data */

/******************  Bit definition for QUADSPI_PSMKR register  ****************/
#define QUADSPI_PSMKR_MASK_Pos           (0U)
#define QUADSPI_PSMKR_MASK_Msk           (0xFFFFFFFFU << QUADSPI_PSMKR_MASK_Pos) /*!< 0xFFFFFFFF */
#define QUADSPI_PSMKR_MASK               QUADSPI_PSMKR_MASK_Msk                /*!< MASK[31:0]: Status Mask */

/******************  Bit definition for QUADSPI_PSMAR register  ****************/
#define QUADSPI_PSMAR_MATCH_Pos          (0U)
#define QUADSPI_PSMAR_MATCH_Msk          (0xFFFFFFFFU << QUADSPI_PSMAR_MATCH_Pos) /*!< 0xFFFFFFFF */
#define QUADSPI_PSMAR_MATCH              QUADSPI_PSMAR_MATCH_Msk               /*!< MATCH[31:0]: Status Match */

/******************  Bit definition for QUADSPI_PIR register  *****************/
#define QUADSPI_PIR_INTERVAL_Pos         (0U)
#define QUADSPI_PIR_INTERVAL_Msk         (0xFFFFU << QUADSPI_PIR_INTERVAL_Pos) /*!< 0x0000FFFF */
#define QUADSPI_PIR_INTERVAL             QUADSPI_PIR_INTERVAL_Msk              /*!< INTERVAL[15:0]: Polling Interval */

/******************  Bit definition for QUADSPI_LPTR register  *****************/
#define QUADSPI_LPTR_TIMEOUT_Pos         (0U)
#define QUADSPI_LPTR_TIMEOUT_Msk         (0xFFFFU << QUADSPI_LPTR_TIMEOUT_Pos) /*!< 0x0000FFFF */
#define QUADSPI_LPTR_TIMEOUT             QUADSPI_LPTR_TIMEOUT_Msk              /*!< TIMEOUT[15:0]: Timeout period */

/**********************  Bit definition for QUADSPI_HWCFGR register  ***************/
#define QUADSPI_HWCFGR_FIFOSIZE_Pos   (0U)
#define QUADSPI_HWCFGR_FIFOSIZE_Msk   (0xFU << QUADSPI_HWCFGR_FIFOSIZE_Pos)           /*!< 0x0000000F */
#define QUADSPI_HWCFGR_FIFOSIZE        QUADSPI_HWCFGR_FIFOSIZE_Msk                     /*!< size of FIFO in words */
#define QUADSPI_HWCFGR_IDLENGTH_Pos   (4U)
#define QUADSPI_HWCFGR_IDLENGTH_Msk   (0xFU << QUADSPI_HWCFGR_IDLENGTH_Pos)           /*!< 0x0000000F */
#define QUADSPI_HWCFGR_IDLENGTH        QUADSPI_HWCFGR_IDLENGTH_Msk                     /*!< size in bit of the FIFO pointer */
#define QUADSPI_HWCFGR_PRESCVAL_Pos    (8U)
#define QUADSPI_HWCFGR_PRESCVAL_Msk   (0xFU << QUADSPI_HWCFGR_PRESCVAL_Pos)           /*!< 0x0000000F */
#define QUADSPI_HWCFGR_PRESCVAL        QUADSPI_HWCFGR_PRESCVAL_Msk                     /*!< reset value of the prescaler */
#define QUADSPI_HWCFGR_IDLENGTH_Pos   (4U)
#define QUADSPI_HWCFGR_IDLENGTH_Msk   (0xFU << QUADSPI_HWCFGR_IDLENGTH_Pos)           /*!< 0x0000000F */
#define QUADSPI_HWCFGR_IDLENGTH        QUADSPI_HWCFGR_IDLENGTH_Msk                     /*!< length of the AXI IDs. */

/**********************  Bit definition for QUADSPI_VERR register  *****************/
#define QUADSPI_VERR_MINREV_Pos      (0U)
#define QUADSPI_VERR_MINREV_Msk      (0xFU << QUADSPI_VERR_MINREV_Pos)               /*!< 0x0000000F */
#define QUADSPI_VERR_MINREV          QUADSPI_VERR_MINREV_Msk                         /*!< Minor Revision number */
#define QUADSPI_VERR_MAJREV_Pos      (4U)
#define QUADSPI_VERR_MAJREV_Msk      (0xFU << QUADSPI_VERR_MAJREV_Pos)               /*!< 0x000000F0 */
#define QUADSPI_VERR_MAJREV          QUADSPI_VERR_MAJREV_Msk                         /*!< Major Revision number */

/**********************  Bit definition for QUADSPI_IPIDR register  ****************/
#define QUADSPI_IPIDR_ID_Pos       (0U)
#define QUADSPI_IPIDR_ID_Msk       (0xFFFFFFFFU << QUADSPI_IPIDR_ID_Pos)         /*!< 0xFFFFFFFF */
#define QUADSPI_IPIDR_ID           QUADSPI_IPIDR_ID_Msk                          /*!< IP Identification */

/**********************  Bit definition for QUADSPI_SIDR register  *****************/
#define QUADSPI_SIDR_SID_Pos         (0U)
#define QUADSPI_SIDR_SID_Msk         (0xFFFFFFFFU << QUADSPI_SIDR_SID_Pos)           /*!< 0xFFFFFFFF */
#define QUADSPI_SIDR_SID             QUADSPI_SIDR_SID_Msk                            /*!< IP size identification */

/******************************************************************************/
/*                                                                            */
/*                                 SYSCFG                                     */
/*                                                                            */
/******************************************************************************/
/******************  Constant for SYSCFG  *****************/
#define SYSCFG_ANALOG_CONNECT_SUPPORT                                 /*!< analog connection between the ANAx and PAx */
/******************  Bit definition for SYSCFG_BOOTR register  *****************/
#define SYSCFG_BOOTR_BOOT0_Pos               (0U)
#define SYSCFG_BOOTR_BOOT0_Msk               (0x1U << SYSCFG_BOOTR_BOOT0_Pos)  /*!< 0x00000001 */
#define SYSCFG_BOOTR_BOOT0                   SYSCFG_BOOTR_BOOT0_Msk            /*!< BOOT0 pin value */
#define SYSCFG_BOOTR_BOOT1_Pos               (1U)                              
#define SYSCFG_BOOTR_BOOT1_Msk               (0x1U << SYSCFG_BOOTR_BOOT1_Pos)  /*!< 0x00000002 */
#define SYSCFG_BOOTR_BOOT1                   SYSCFG_BOOTR_BOOT1_Msk            /*!< BOOT1 pin value */
#define SYSCFG_BOOTR_BOOT2_Pos               (2U)                              
#define SYSCFG_BOOTR_BOOT2_Msk               (0x1U << SYSCFG_BOOTR_BOOT2_Pos)  /*!< 0x00000004 */
#define SYSCFG_BOOTR_BOOT2                   SYSCFG_BOOTR_BOOT2_Msk            /*!< BOOT2 pin value */
#define SYSCFG_BOOTR_BOOT0_PD_Pos            (4U)                              
#define SYSCFG_BOOTR_BOOT0_PD_Msk            (0x1U << SYSCFG_BOOTR_BOOT0_PD_Pos) /*!< 0x00000010 */
#define SYSCFG_BOOTR_BOOT0_PD                SYSCFG_BOOTR_BOOT0_PD_Msk         /*!< BOOT0 pin pull-down disable */
#define SYSCFG_BOOTR_BOOT1_PD_Pos            (5U)                              
#define SYSCFG_BOOTR_BOOT1_PD_Msk            (0x1U << SYSCFG_BOOTR_BOOT1_PD_Pos) /*!< 0x00000020 */
#define SYSCFG_BOOTR_BOOT1_PD                SYSCFG_BOOTR_BOOT1_PD_Msk         /*!< BOOT1 pin pull-down disable */
#define SYSCFG_BOOTR_BOOT2_PD_Pos            (6U)                              
#define SYSCFG_BOOTR_BOOT2_PD_Msk            (0x1U << SYSCFG_BOOTR_BOOT2_PD_Pos) /*!< 0x00000040 */
#define SYSCFG_BOOTR_BOOT2_PD                SYSCFG_BOOTR_BOOT2_PD_Msk         /*!< BOOT2 pin pull-down disable */

/******************  Bit definition for SYSCFG_PMCSETR register  ******************/
#define SYSCFG_PMCSETR_I2C1_FMP_Pos     (0U)
#define SYSCFG_PMCSETR_I2C1_FMP_Msk     (0x1U << SYSCFG_PMCSETR_I2C1_FMP_Pos)        /*!< 0x00000001 */
#define SYSCFG_PMCSETR_I2C1_FMP         SYSCFG_PMCSETR_I2C1_FMP_Msk                  /*!< I2C1 Fast mode plus */
#define SYSCFG_PMCSETR_I2C2_FMP_Pos     (1U)
#define SYSCFG_PMCSETR_I2C2_FMP_Msk     (0x1U << SYSCFG_PMCSETR_I2C2_FMP_Pos)        /*!< 0x00000002 */
#define SYSCFG_PMCSETR_I2C2_FMP         SYSCFG_PMCSETR_I2C2_FMP_Msk                  /*!< I2C2 Fast mode plus */
#define SYSCFG_PMCSETR_I2C3_FMP_Pos     (2U)
#define SYSCFG_PMCSETR_I2C3_FMP_Msk     (0x1U << SYSCFG_PMCSETR_I2C3_FMP_Pos)        /*!< 0x00000004 */
#define SYSCFG_PMCSETR_I2C3_FMP         SYSCFG_PMCSETR_I2C3_FMP_Msk                  /*!< I2C3 Fast mode plus */
#define SYSCFG_PMCSETR_I2C4_FMP_Pos     (3U)
#define SYSCFG_PMCSETR_I2C4_FMP_Msk     (0x1U << SYSCFG_PMCSETR_I2C4_FMP_Pos)        /*!< 0x00000008 */
#define SYSCFG_PMCSETR_I2C4_FMP         SYSCFG_PMCSETR_I2C4_FMP_Msk                  /*!< I2C4 Fast mode plus */
#define SYSCFG_PMCSETR_I2C5_FMP_Pos     (4U)
#define SYSCFG_PMCSETR_I2C5_FMP_Msk     (0x1U << SYSCFG_PMCSETR_I2C5_FMP_Pos)        /*!< 0x00000010 */
#define SYSCFG_PMCSETR_I2C5_FMP         SYSCFG_PMCSETR_I2C5_FMP_Msk                  /*!< I2C5 Fast mode plus */
#define SYSCFG_PMCSETR_I2C6_FMP_Pos     (5U)
#define SYSCFG_PMCSETR_I2C6_FMP_Msk     (0x1U << SYSCFG_PMCSETR_I2C6_FMP_Pos)        /*!< 0x00000020 */
#define SYSCFG_PMCSETR_I2C6_FMP         SYSCFG_PMCSETR_I2C6_FMP_Msk                  /*!< I2C6 Fast mode plus */

#define SYSCFG_PMCSETR_EN_BOOSTER_Pos     (8U)
#define SYSCFG_PMCSETR_EN_BOOSTER_Msk     (0x1U << SYSCFG_PMCSETR_EN_BOOSTER_Pos)         /*!< 0x00000100 */
#define SYSCFG_PMCSETR_EN_BOOSTER          SYSCFG_PMCSETR_EN_BOOSTER_Msk                   /*!< I/O analog switch voltage booster enable */

#define SYSCFG_PMCSETR_ANASWVDD_Pos     (9U)
#define SYSCFG_PMCSETR_ANASWVDD_Msk     (0x1U << SYSCFG_PMCSETR_ANASWVDD_Pos)         /*!< 0x00000200 */
#define SYSCFG_PMCSETR_ANASWVDD         SYSCFG_PMCSETR_ANASWVDD_Msk                   /*!< GPIO analog switches control voltage selection */

#define SYSCFG_PMCSETR_ETH_CLK_SEL_Pos         (16U)
#define SYSCFG_PMCSETR_ETH_CLK_SEL_Msk         (0x1U << SYSCFG_PMCSETR_ETH_CLK_SEL_Pos)           /*!< 0x00010000 */
#define SYSCFG_PMCSETR_ETH_CLK_SEL             SYSCFG_PMCSETR_ETH_CLK_SEL_Msk                     /*!< Internal clock ETH_CLK from RCC is used regardless AFMux */
#define SYSCFG_PMCSETR_ETH_REF_CLK_SEL_Pos     (17U)
#define SYSCFG_PMCSETR_ETH_REF_CLK_SEL_Msk     (0x1U << SYSCFG_PMCSETR_ETH_REF_CLK_SEL_Pos)       /*!< 0x00020000 */
#define SYSCFG_PMCSETR_ETH_REF_CLK_SEL         SYSCFG_PMCSETR_ETH_REF_CLK_SEL_Msk                 /*!< Ethernet 50MHz RMII clock selection */

#define SYSCFG_PMCSETR_ETH_SELMII_Pos          (20U)
#define SYSCFG_PMCSETR_ETH_SELMII_Msk          (0x1U << SYSCFG_PMCSETR_ETH_SELMII_Pos)            /*!< 0x00100000 */
#define SYSCFG_PMCSETR_ETH_SELMII_SEL          SYSCFG_PMCSETR_ETH_SELMII_Msk                      /*!< controls MII or GMII when ETH_SEL[2:0] = 0b000 */

#define SYSCFG_PMCSETR_ETH_SEL_Pos             (21U)
#define SYSCFG_PMCSETR_ETH_SEL_Msk             (0x7U << SYSCFG_PMCSETR_ETH_SEL_Pos)               /*!< 0x00E00000 */
#define SYSCFG_PMCSETR_ETH_SEL                 SYSCFG_PMCSETR_ETH_SEL_Msk                         /*!< Ethernet PHY Interface Selection */
#define SYSCFG_PMCSETR_ETH_SEL_0               (0x1U << SYSCFG_PMCSETR_ETH_SEL_Pos)               /*!< 0x00200000 */
#define SYSCFG_PMCSETR_ETH_SEL_1               (0x2U << SYSCFG_PMCSETR_ETH_SEL_Pos)               /*!< 0x00400000 */
#define SYSCFG_PMCSETR_ETH_SEL_2               (0x4U << SYSCFG_PMCSETR_ETH_SEL_Pos)               /*!< 0x00800000 */
#define SYSCFG_PMCSETR_ETH_SEL_CONF_Pos        (20U)
#define SYSCFG_PMCSETR_ETH_SEL_CONF_Msk        (0xFU << SYSCFG_PMCSETR_ETH_SEL_CONF_Pos)         /*!< 0x00F00000 */
#define SYSCFG_PMCSETR_ETH_SEL_CONF            SYSCFG_PMCSETR_ETH_SEL_CONF_Msk                    /*!< Ethernet PHY Interface Configuration */

#define SYSCFG_PMCSETR_ANA0_SEL_Pos            (24U)
#define SYSCFG_PMCSETR_ANA0_SEL_Msk            (0x1U << SYSCFG_PMCSETR_ANA0_SEL_Pos)              /*!< 0x01000000 */
#define SYSCFG_PMCSETR_ANA0_SEL_SEL             SYSCFG_PMCSETR_ANA0_SEL_Msk                       /*!< controls analog connection between ANA0 and PA0 pin */
#define SYSCFG_PMCSETR_ANA1_SEL_Pos            (25U)
#define SYSCFG_PMCSETR_ANA1_SEL_Msk            (0x1U << SYSCFG_PMCSETR_ANA1_SEL_Pos)              /*!< 0x02000000 */
#define SYSCFG_PMCSETR_ANA1_SEL_SEL            SYSCFG_PMCSETR_ANA1_SEL_Msk                       /*!< controls analog connection between ANA1 and PA1 pin */


/******************  Bit definition for SYSCFG_PMCCLRR register  ******************/
#define SYSCFG_PMCCLRR_I2C1_FMP_Pos     (0U)
#define SYSCFG_PMCCLRR_I2C1_FMP_Msk     (0x1U << SYSCFG_PMCCLRR_I2C1_FMP_Pos)        /*!< 0x00000001 */
#define SYSCFG_PMCCLRR_I2C1_FMP         SYSCFG_PMCCLRR_I2C1_FMP_Msk                  /*!< I2C1 Fast mode plus */
#define SYSCFG_PMCCLRR_I2C2_FMP_Pos     (1U)
#define SYSCFG_PMCCLRR_I2C2_FMP_Msk     (0x1U << SYSCFG_PMCCLRR_I2C2_FMP_Pos)        /*!< 0x00000002 */
#define SYSCFG_PMCCLRR_I2C2_FMP         SYSCFG_PMCCLRR_I2C2_FMP_Msk                  /*!< I2C2 Fast mode plus */
#define SYSCFG_PMCCLRR_I2C3_FMP_Pos     (2U)
#define SYSCFG_PMCCLRR_I2C3_FMP_Msk     (0x1U << SYSCFG_PMCCLRR_I2C3_FMP_Pos)        /*!< 0x00000004 */
#define SYSCFG_PMCCLRR_I2C3_FMP         SYSCFG_PMCCLRR_I2C3_FMP_Msk                  /*!< I2C3 Fast mode plus */
#define SYSCFG_PMCCLRR_I2C4_FMP_Pos     (3U)
#define SYSCFG_PMCCLRR_I2C4_FMP_Msk     (0x1U << SYSCFG_PMCCLRR_I2C4_FMP_Pos)        /*!< 0x00000008 */
#define SYSCFG_PMCCLRR_I2C4_FMP         SYSCFG_PMCCLRR_I2C4_FMP_Msk                  /*!< I2C4 Fast mode plus */
#define SYSCFG_PMCCLRR_I2C5_FMP_Pos     (4U)
#define SYSCFG_PMCCLRR_I2C5_FMP_Msk     (0x1U << SYSCFG_PMCCLRR_I2C5_FMP_Pos)        /*!< 0x00000010 */
#define SYSCFG_PMCCLRR_I2C5_FMP         SYSCFG_PMCCLRR_I2C5_FMP_Msk                  /*!< I2C5 Fast mode plus */
#define SYSCFG_PMCCLRR_I2C6_FMP_Pos     (5U)
#define SYSCFG_PMCCLRR_I2C6_FMP_Msk     (0x1U << SYSCFG_PMCCLRR_I2C6_FMP_Pos)        /*!< 0x00000020 */
#define SYSCFG_PMCCLRR_I2C6_FMP         SYSCFG_PMCCLRR_I2C6_FMP_Msk                  /*!< I2C6 Fast mode plus */

#define SYSCFG_PMCCLRR_EN_BOOSTER_Pos     (8U)
#define SYSCFG_PMCCLRR_EN_BOOSTER_Msk     (0x1U << SYSCFG_PMCCLRR_EN_BOOSTER_Pos)         /*!< 0x00000100 */
#define SYSCFG_PMCCLRR_EN_BOOSTER          SYSCFG_PMCCLRR_EN_BOOSTER_Msk                   /*!< I/O analog switch voltage booster enable */

#define SYSCFG_PMCCLRR_ANASWVDD_Pos     (9U)
#define SYSCFG_PMCCLRR_ANASWVDD_Msk     (0x1U << SYSCFG_PMCCLRR_ANASWVDD_Pos)         /*!< 0x00000200 */
#define SYSCFG_PMCCLRR_ANASWVDD         SYSCFG_PMCCLRR_ANASWVDD_Msk                   /*!< GPIO analog switches control voltage selection */

#define SYSCFG_PMCCLRR_ETH_CLK_SEL_Pos         (16U)
#define SYSCFG_PMCCLRR_ETH_CLK_SEL_Msk         (0x1U << SYSCFG_PMCCLRR_ETH_CLK_SEL_Pos)           /*!< 0x00010000 */
#define SYSCFG_PMCCLRR_ETH_CLK_SEL             SYSCFG_PMCCLRR_ETH_CLK_SEL_Msk                     /*!< Internal clock ETH_CLK1 from RCC is used regardless AFMux */
#define SYSCFG_PMCCLRR_ETH_REF_CLK_SEL_Pos     (17U)
#define SYSCFG_PMCCLRR_ETH_REF_CLK_SEL_Msk     (0x1U << SYSCFG_PMCCLRR_ETH_REF_CLK_SEL_Pos)       /*!< 0x00020000 */
#define SYSCFG_PMCCLRR_ETH_REF_CLK_SEL         SYSCFG_PMCCLRR_ETH_REF_CLK_SEL_Msk                 /*!< Ethernet 50MHz RMII clock selection */
#define SYSCFG_PMCCLRR_ETH_SELMII_Pos          (20U)
#define SYSCFG_PMCCLRR_ETH_SELMII_Msk          (0x1U << SYSCFG_PMCCLRR_ETH_SELMII_Pos)            /*!< 0x00100000 */
#define SYSCFG_PMCCLRR_ETH_SELMII_SEL          SYSCFG_PMCCLRR_ETH_SELMII_Msk                      /*!< controls MII or GMII when ETH_SEL[2:0] = 0b000 */
#define SYSCFG_PMCCLRR_ETH_SEL_Pos             (21U)
#define SYSCFG_PMCCLRR_ETH_SEL_Msk             (0x7U << SYSCFG_PMCCLRR_ETH_SEL_Pos)               /*!< 0x00E00000 */
#define SYSCFG_PMCCLRR_ETH_SEL                 SYSCFG_PMCCLRR_ETH_SEL_Msk                         /*!< Ethernet PHY Interface Selection */
#define SYSCFG_PMCCLRR_ETH_SEL_0               (0x1U << SYSCFG_PMCCLRR_ETH_SEL_Pos)               /*!< 0x00200000 */
#define SYSCFG_PMCCLRR_ETH_SEL_1               (0x2U << SYSCFG_PMCCLRR_ETH_SEL_Pos)               /*!< 0x00400000 */
#define SYSCFG_PMCCLRR_ETH_SEL_2               (0x4U << SYSCFG_PMCCLRR_ETH_SEL_Pos)               /*!< 0x00800000 */
#define SYSCFG_PMCCLRR_ETH_SEL_CONF_Pos        (20U)
#define SYSCFG_PMCCLRR_ETH_SEL_CONF_Msk        (0xFU << SYSCFG_PMCCLRR_ETH_SEL_CONF_Pos)          /*!< 0x00F00000 */
#define SYSCFG_PMCCLRR_ETH_SEL_CONF            SYSCFG_PMCCLRR_ETH_SEL_CONF_Msk                   /*!< Ethernet PHY Interface Configuration */

#define SYSCFG_PMCCLRR_ANA0_SEL_Pos            (24U)
#define SYSCFG_PMCCLRR_ANA0_SEL_Msk            (0x1U << SYSCFG_PMCCLRR_ANA0_SEL_Pos)              /*!< 0x01000000 */
#define SYSCFG_PMCCLRR_ANA0_SEL_SEL             SYSCFG_PMCCLRR_ANA0_SEL_Msk                       /*!< controls analog connection between ANA0 and PA0 pin */
#define SYSCFG_PMCCLRR_ANA1_SEL_Pos            (25U)
#define SYSCFG_PMCCLRR_ANA1_SEL_Msk            (0x1U << SYSCFG_PMCCLRR_ANA1_SEL_Pos)              /*!< 0x02000000 */
#define SYSCFG_PMCCLRR_ANA1_SEL_SEL            SYSCFG_PMCCLRR_ANA1_SEL_Msk                       /*!< controls analog connection between ANA1 and PA1 pin */




/******************  Bit definition for SYSCFG_IOCTRLSETR register  *****************/
#define SYSCFG_IOCTRLSETR_HSLVEN_TRACE_Pos      (0U)
#define SYSCFG_IOCTRLSETR_HSLVEN_TRACE_Msk      (0x1U << SYSCFG_IOCTRLSETR_HSLVEN_TRACE_Pos)     /*!< 0x00000001 */
#define SYSCFG_IOCTRLSETR_HSLVEN_TRACE          SYSCFG_IOCTRLSETR_HSLVEN_TRACE_Msk               /*!< High Speed Low Voltage Pad mode Enable */
#define SYSCFG_IOCTRLSETR_HSLVEN_QUADSPI_Pos    (1U)
#define SYSCFG_IOCTRLSETR_HSLVEN_QUADSPI_Msk    (0x1U << SYSCFG_IOCTRLSETR_HSLVEN_QUADSPI_Pos)   /*!< 0x00000002 */
#define SYSCFG_IOCTRLSETR_HSLVEN_QUADSPI        SYSCFG_IOCTRLSETR_HSLVEN_QUADSPI_Msk             /*!< High Speed Low Voltage Pad mode Enable */
#define SYSCFG_IOCTRLSETR_HSLVEN_ETH_Pos        (2U)
#define SYSCFG_IOCTRLSETR_HSLVEN_ETH_Msk        (0x1U << SYSCFG_IOCTRLSETR_HSLVEN_ETH_Pos)       /*!< 0x00000004 */
#define SYSCFG_IOCTRLSETR_HSLVEN_ETH            SYSCFG_IOCTRLSETR_HSLVEN_ETH_Msk                 /*!< High Speed Low Voltage Pad mode Enable */
#define SYSCFG_IOCTRLSETR_HSLVEN_SDMMC_Pos      (3U)
#define SYSCFG_IOCTRLSETR_HSLVEN_SDMMC_Msk      (0x1U << SYSCFG_IOCTRLSETR_HSLVEN_SDMMC_Pos)     /*!< 0x00000008 */
#define SYSCFG_IOCTRLSETR_HSLVEN_SDMMC          SYSCFG_IOCTRLSETR_HSLVEN_SDMMC_Msk               /*!< High Speed Low Voltage Pad mode Enable */
#define SYSCFG_IOCTRLSETR_HSLVEN_SPI_Pos        (4U)
#define SYSCFG_IOCTRLSETR_HSLVEN_SPI_Msk        (0x1U << SYSCFG_IOCTRLSETR_HSLVEN_SPI_Pos)       /*!< 0x00000010 */
#define SYSCFG_IOCTRLSETR_HSLVEN_SPI            SYSCFG_IOCTRLSETR_HSLVEN_SPI_Msk                 /*!< High Speed Low Voltage Pad mode Enable */

/******************  Bit definition for SYSCFG_IOCTRLCLRR register  *****************/
#define SYSCFG_IOCTRLCLRR_HSLVEN_TRACE_Pos      (0U)
#define SYSCFG_IOCTRLCLRR_HSLVEN_TRACE_Msk      (0x1U << SYSCFG_IOCTRLCLRR_HSLVEN_TRACE_Pos)     /*!< 0x00000001 */
#define SYSCFG_IOCTRLCLRR_HSLVEN_TRACE          SYSCFG_IOCTRLCLRR_HSLVEN_TRACE_Msk               /*!< High Speed Low Voltage Pad mode Enable */
#define SYSCFG_IOCTRLCLRR_HSLVEN_QUADSPI_Pos    (1U)
#define SYSCFG_IOCTRLCLRR_HSLVEN_QUADSPI_Msk    (0x1U << SYSCFG_IOCTRLCLRR_HSLVEN_QUADSPI_Pos)   /*!< 0x00000002 */
#define SYSCFG_IOCTRLCLRR_HSLVEN_QUADSPI        SYSCFG_IOCTRLCLRR_HSLVEN_QUADSPI_Msk             /*!< High Speed Low Voltage Pad mode Enable */
#define SYSCFG_IOCTRLCLRR_HSLVEN_ETH_Pos        (2U)
#define SYSCFG_IOCTRLCLRR_HSLVEN_ETH_Msk        (0x1U << SYSCFG_IOCTRLCLRR_HSLVEN_ETH_Pos)       /*!< 0x00000004 */
#define SYSCFG_IOCTRLCLRR_HSLVEN_ETH            SYSCFG_IOCTRLCLRR_HSLVEN_ETH_Msk                 /*!< High Speed Low Voltage Pad mode Enable */
#define SYSCFG_IOCTRLCLRR_HSLVEN_SDMMC_Pos      (3U)
#define SYSCFG_IOCTRLCLRR_HSLVEN_SDMMC_Msk      (0x1U << SYSCFG_IOCTRLCLRR_HSLVEN_SDMMC_Pos)     /*!< 0x00000008 */
#define SYSCFG_IOCTRLCLRR_HSLVEN_SDMMC          SYSCFG_IOCTRLCLRR_HSLVEN_SDMMC_Msk               /*!< High Speed Low Voltage Pad mode Enable */
#define SYSCFG_IOCTRLCLRR_HSLVEN_SPI_Pos        (4U)
#define SYSCFG_IOCTRLCLRR_HSLVEN_SPI_Msk        (0x1U << SYSCFG_IOCTRLCLRR_HSLVEN_SPI_Pos)       /*!< 0x00000010 */
#define SYSCFG_IOCTRLCLRR_HSLVEN_SPI            SYSCFG_IOCTRLCLRR_HSLVEN_SPI_Msk                 /*!< High Speed Low Voltage Pad mode Enable */

/******************  Bit definition for SYSCFG_ICNR register  ********************/
#define SYSCFG_ICNR_AXI_M0_Pos               (0U)                              
#define SYSCFG_ICNR_AXI_M0_Msk               (0x1U << SYSCFG_ICNR_AXI_M0_Pos)  /*!< 0x00000001 */
#define SYSCFG_ICNR_AXI_M0                   SYSCFG_ICNR_AXI_M0_Msk            /*!< controls which slave port is used by the master to access the DDR */
#define SYSCFG_ICNR_AXI_M1_Pos               (1U)                              
#define SYSCFG_ICNR_AXI_M1_Msk               (0x1U << SYSCFG_ICNR_AXI_M1_Pos)  /*!< 0x00000002 */
#define SYSCFG_ICNR_AXI_M1                   SYSCFG_ICNR_AXI_M1_Msk            /*!< controls which slave port is used by the master to access the DDR */
#define SYSCFG_ICNR_AXI_M2_Pos               (2U)                              
#define SYSCFG_ICNR_AXI_M2_Msk               (0x1U << SYSCFG_ICNR_AXI_M2_Pos)  /*!< 0x00000004 */
#define SYSCFG_ICNR_AXI_M2                   SYSCFG_ICNR_AXI_M2_Msk            /*!< controls which slave port is used by the master to access the DDR */
#define SYSCFG_ICNR_AXI_M3_Pos               (3U)                              
#define SYSCFG_ICNR_AXI_M3_Msk               (0x1U << SYSCFG_ICNR_AXI_M3_Pos)  /*!< 0x00000008 */
#define SYSCFG_ICNR_AXI_M3                   SYSCFG_ICNR_AXI_M3_Msk            /*!< controls which slave port is used by the master to access the DDR */
#define SYSCFG_ICNR_AXI_M5_Pos               (5U)                              
#define SYSCFG_ICNR_AXI_M5_Msk               (0x1U << SYSCFG_ICNR_AXI_M5_Pos)  /*!< 0x00000020 */
#define SYSCFG_ICNR_AXI_M5                   SYSCFG_ICNR_AXI_M5_Msk            /*!< controls which slave port is used by the master to access the DDR */
#define SYSCFG_ICNR_AXI_M6_Pos               (6U)                              
#define SYSCFG_ICNR_AXI_M6_Msk               (0x1U << SYSCFG_ICNR_AXI_M6_Pos)  /*!< 0x00000040 */
#define SYSCFG_ICNR_AXI_M6                   SYSCFG_ICNR_AXI_M6_Msk            /*!< controls which slave port is used by the master to access the DDR */
#define SYSCFG_ICNR_AXI_M7_Pos               (7U)                              
#define SYSCFG_ICNR_AXI_M7_Msk               (0x1U << SYSCFG_ICNR_AXI_M7_Pos)  /*!< 0x00000080 */
#define SYSCFG_ICNR_AXI_M7                   SYSCFG_ICNR_AXI_M7_Msk            /*!< controls which slave port is used by the master to access the DDR */
#define SYSCFG_ICNR_AXI_M8_Pos               (8U)                              
#define SYSCFG_ICNR_AXI_M8_Msk               (0x1U << SYSCFG_ICNR_AXI_M8_Pos)  /*!< 0x00000100 */
#define SYSCFG_ICNR_AXI_M8                   SYSCFG_ICNR_AXI_M8_Msk            /*!< controls which slave port is used by the master to access the DDR */
#define SYSCFG_ICNR_AXI_M9_Pos               (9U)                              
#define SYSCFG_ICNR_AXI_M9_Msk               (0x1U << SYSCFG_ICNR_AXI_M9_Pos)  /*!< 0x00000200 */
#define SYSCFG_ICNR_AXI_M9                   SYSCFG_ICNR_AXI_M9_Msk            /*!< controls which slave port is used by the master to access the DDR */
#define SYSCFG_ICNR_AXI_M10_Pos              (10U)                             
#define SYSCFG_ICNR_AXI_M10_Msk              (0x1U << SYSCFG_ICNR_AXI_M10_Pos) /*!< 0x00000400 */
#define SYSCFG_ICNR_AXI_M10                  SYSCFG_ICNR_AXI_M10_Msk           /*!< controls which slave port is used by the master to access the DDR */

/******************  Bit definition for SYSCFG_CMPCR register   ********************/
#define SYSCFG_CMPCR_SW_CTRL_Pos             (1U)                              
#define SYSCFG_CMPCR_SW_CTRL_Msk             (0x1U << SYSCFG_CMPCR_SW_CTRL_Pos) /*!< 0x00000002 */
#define SYSCFG_CMPCR_SW_CTRL                 SYSCFG_CMPCR_SW_CTRL_Msk           /*!< Compensation Software Control */
#define SYSCFG_CMPCR_READY_Pos               (8U)                              
#define SYSCFG_CMPCR_READY_Msk               (0x1U << SYSCFG_CMPCR_READY_Pos)   /*!< 0x00000100 */
#define SYSCFG_CMPCR_READY                   SYSCFG_CMPCR_READY_Msk             /*!< Compensation cell ready flag */
#define SYSCFG_CMPCR_RANSRC_Pos              (16U)                             
#define SYSCFG_CMPCR_RANSRC_Msk              (0xFU << SYSCFG_CMPCR_RANSRC_Pos)  /*!< 0x000F0000 */
#define SYSCFG_CMPCR_RANSRC                  SYSCFG_CMPCR_RANSRC_Msk            /*!< NMOS I/O Compensation value sent to IOs when SW_CTRL = 1 */
#define SYSCFG_CMPCR_RANSRC_0                (0x1U << SYSCFG_CMPCR_RANSRC_Pos)  /*!< 0x00010000 */
#define SYSCFG_CMPCR_RANSRC_1                (0x2U << SYSCFG_CMPCR_RANSRC_Pos)  /*!< 0x00020000 */
#define SYSCFG_CMPCR_RANSRC_2                (0x4U << SYSCFG_CMPCR_RANSRC_Pos)  /*!< 0x00040000 */
#define SYSCFG_CMPCR_RANSRC_3                (0x8U << SYSCFG_CMPCR_RANSRC_Pos)  /*!< 0x00080000 */
#define SYSCFG_CMPCR_RAPSRC_Pos              (20U)                             
#define SYSCFG_CMPCR_RAPSRC_Msk              (0xFU << SYSCFG_CMPCR_RAPSRC_Pos)  /*!< 0x00F00000 */
#define SYSCFG_CMPCR_RAPSRC                  SYSCFG_CMPCR_RAPSRC_Msk            /*!< PMOS I/O Compensation value sent to IOs when SW_CTRL = 1 */
#define SYSCFG_CMPCR_RAPSRC_0                (0x1U << SYSCFG_CMPCR_RAPSRC_Pos)  /*!< 0x00100000 */
#define SYSCFG_CMPCR_RAPSRC_1                (0x2U << SYSCFG_CMPCR_RAPSRC_Pos)  /*!< 0x00200000 */
#define SYSCFG_CMPCR_RAPSRC_2                (0x4U << SYSCFG_CMPCR_RAPSRC_Pos)  /*!< 0x00400000 */
#define SYSCFG_CMPCR_RAPSRC_3                (0x8U << SYSCFG_CMPCR_RAPSRC_Pos)  /*!< 0x00800000 */
#define SYSCFG_CMPCR_ANSRC_Pos               (24U)                             
#define SYSCFG_CMPCR_ANSRC_Msk               (0xFU << SYSCFG_CMPCR_ANSRC_Pos)   /*!< 0x0F000000 */
#define SYSCFG_CMPCR_ANSRC                   SYSCFG_CMPCR_ANSRC_Msk             /*!< NMOS I/O Compensation value provided by compensation cell */
#define SYSCFG_CMPCR_ANSRC_0                 (0x1U << SYSCFG_CMPCR_ANSRC_Pos)   /*!< 0x01000000 */
#define SYSCFG_CMPCR_ANSRC_1                 (0x2U << SYSCFG_CMPCR_ANSRC_Pos)   /*!< 0x02000000 */
#define SYSCFG_CMPCR_ANSRC_2                 (0x4U << SYSCFG_CMPCR_ANSRC_Pos)   /*!< 0x04000000 */
#define SYSCFG_CMPCR_ANSRC_3                 (0x8U << SYSCFG_CMPCR_ANSRC_Pos)   /*!< 0x08000000 */
#define SYSCFG_CMPCR_APSRC_Pos               (28U)                             
#define SYSCFG_CMPCR_APSRC_Msk               (0xFU << SYSCFG_CMPCR_APSRC_Pos)   /*!< 0xF0000000 */
#define SYSCFG_CMPCR_APSRC                   SYSCFG_CMPCR_APSRC_Msk             /*!< PMOS I/O Compensation value provided by compensation cell */
#define SYSCFG_CMPCR_APSRC_0                 (0x1U << SYSCFG_CMPCR_APSRC_Pos)   /*!< 0x10000000 */
#define SYSCFG_CMPCR_APSRC_1                 (0x2U << SYSCFG_CMPCR_APSRC_Pos)   /*!< 0x20000000 */
#define SYSCFG_CMPCR_APSRC_2                 (0x4U << SYSCFG_CMPCR_APSRC_Pos)   /*!< 0x40000000 */
#define SYSCFG_CMPCR_APSRC_3                 (0x8U << SYSCFG_CMPCR_APSRC_Pos)   /*!< 0x80000000 */

/******************  Bit definition for SYSCFG_CMPENSETR register   ********************/
#define SYSCFG_CMPENSETR_MPU_EN_Pos              (0U)
#define SYSCFG_CMPENSETR_MPU_EN_Msk              (0x1U << SYSCFG_CMPENSETR_MPU_EN_Pos) /*!< 0x00000001 */
#define SYSCFG_CMPENSETR_MPU_EN                  SYSCFG_CMPENSETR_MPU_EN_Msk           /*!< Compensation cell enable */
#define SYSCFG_CMPENSETR_MCU_EN_Pos              (1U)
#define SYSCFG_CMPENSETR_MCU_EN_Msk              (0x1U << SYSCFG_CMPENSETR_MCU_EN_Pos) /*!< 0x00000002 */
#define SYSCFG_CMPENSETR_MCU_EN                  SYSCFG_CMPENSETR_MCU_EN_Msk           /*!< Compensation cell enable */

/******************  Bit definition for SYSCFG_CMPENCLRR register   ********************/
#define SYSCFG_CMPENCLRR_MPU_EN_Pos              (0U)
#define SYSCFG_CMPENCLRR_MPU_EN_Msk              (0x1U << SYSCFG_CMPENCLRR_MPU_EN_Pos)  /*!< 0x00000001 */
#define SYSCFG_CMPENCLRR_MPU_EN                  SYSCFG_CMPENCLRR_MPU_EN_Msk            /*!< Compensation cell disable */
#define SYSCFG_CMPENCLRR_MCU_EN_Pos              (1U)
#define SYSCFG_CMPENCLRR_MCU_EN_Msk              (0x1U << SYSCFG_CMPENCLRR_MCU_EN_Pos)  /*!< 0x00000002 */
#define SYSCFG_CMPENCLRR_MCU_EN                  SYSCFG_CMPENCLRR_MCU_EN_Msk            /*!< Compensation cell disable */

/******************  Bit definition for SYSCFG_CBR register  ******************/
#define SYSCFG_CBR_CLL_Pos           (0U)
#define SYSCFG_CBR_CLL_Msk           (0x1U << SYSCFG_CBR_CLL_Pos)              /*!< 0x00000001 */
#define SYSCFG_CBR_CLL               SYSCFG_CBR_CLL_Msk                        /*!< Cortex-M4 LOCKUP (Hardfault) output enable bit */
#define SYSCFG_CBR_PVDL_Pos          (2U)
#define SYSCFG_CBR_PVDL_Msk          (0x1U << SYSCFG_CBR_PVDL_Pos)             /*!< 0x00000004 */
#define SYSCFG_CBR_PVDL              SYSCFG_CBR_PVDL_Msk                       /*!< PVD lock enable bit */










/**********************  Bit definition for SYSCFG_VERR register  *****************/
#define SYSCFG_VERR_MINREV_Pos      (0U)
#define SYSCFG_VERR_MINREV_Msk      (0xFU << SYSCFG_VERR_MINREV_Pos)               /*!< 0x0000000F */
#define SYSCFG_VERR_MINREV          SYSCFG_VERR_MINREV_Msk                         /*!< Minor Revision number */
#define SYSCFG_VERR_MAJREV_Pos      (4U)
#define SYSCFG_VERR_MAJREV_Msk      (0xFU << SYSCFG_VERR_MAJREV_Pos)               /*!< 0x000000F0 */
#define SYSCFG_VERR_MAJREV          SYSCFG_VERR_MAJREV_Msk                         /*!< Major Revision number */

/**********************  Bit definition for SYSCFG_IPIDR register  ****************/
#define SYSCFG_IPIDR_IPID_Pos       (0U)
#define SYSCFG_IPIDR_IPID_Msk       (0xFFFFFFFFU << SYSCFG_IPIDR_IPID_Pos)         /*!< 0xFFFFFFFF */
#define SYSCFG_IPIDR_IPID           SYSCFG_IPIDR_IPID_Msk                          /*!< IP Identification */

/**********************  Bit definition for SYSCFG_SIDR register  *****************/
#define SYSCFG_SIDR_SID_Pos         (0U)
#define SYSCFG_SIDR_SID_Msk         (0xFFFFFFFFU << SYSCFG_SIDR_SID_Pos)           /*!< 0xFFFFFFFF */
#define SYSCFG_SIDR_SID             SYSCFG_SIDR_SID_Msk                            /*!< IP size identification */

/******************************************************************************/
/*                                                                            */
/*                         Temperature Sensor (DTS)                           */
/*                                                                            */
/******************************************************************************/

/******************  Bit definition for DTS_CFGR1 register  ******************/
#define DTS_CFGR1_TS1_EN_Pos               (0U)
#define DTS_CFGR1_TS1_EN_Msk               (0x1U << DTS_CFGR1_TS1_EN_Pos) /*!< 0x00000001 */
#define DTS_CFGR1_TS1_EN                   DTS_CFGR1_TS1_EN_Msk        /*!< DTS1 Enable */
#define DTS_CFGR1_TS1_START_Pos            (4U)
#define DTS_CFGR1_TS1_START_Msk            (0x1U << DTS_CFGR1_TS1_START_Pos) /*!< 0x00000010 */
#define DTS_CFGR1_TS1_START                DTS_CFGR1_TS1_START_Msk     /*!< Proceed to a frequency measurement on DTS1 */
#define DTS_CFGR1_TS1_INTRIG_SEL_Pos       (8U)
#define DTS_CFGR1_TS1_INTRIG_SEL_Msk       (0xFU << DTS_CFGR1_TS1_INTRIG_SEL_Pos) /*!< 0x00000F00 */
#define DTS_CFGR1_TS1_INTRIG_SEL           DTS_CFGR1_TS1_INTRIG_SEL_Msk /*!< Input triggers selection bits [3:0] for DTS1 */
#define DTS_CFGR1_TS1_INTRIG_SEL_0         (0x1U << DTS_CFGR1_TS1_INTRIG_SEL_Pos) /*!< 0x00000100 */
#define DTS_CFGR1_TS1_INTRIG_SEL_1         (0x2U << DTS_CFGR1_TS1_INTRIG_SEL_Pos) /*!< 0x00000200 */
#define DTS_CFGR1_TS1_INTRIG_SEL_2         (0x4U << DTS_CFGR1_TS1_INTRIG_SEL_Pos) /*!< 0x00000400 */
#define DTS_CFGR1_TS1_INTRIG_SEL_3         (0x8U << DTS_CFGR1_TS1_INTRIG_SEL_Pos) /*!< 0x00000800 */
#define DTS_CFGR1_TS1_SMP_TIME_Pos         (16U)
#define DTS_CFGR1_TS1_SMP_TIME_Msk         (0xFU << DTS_CFGR1_TS1_SMP_TIME_Pos) /*!< 0x000F0000 */
#define DTS_CFGR1_TS1_SMP_TIME             DTS_CFGR1_TS1_SMP_TIME_Msk  /*!< Sample time [3:0] for DTS1 */
#define DTS_CFGR1_TS1_SMP_TIME_0           (0x1U << DTS_CFGR1_TS1_SMP_TIME_Pos) /*!< 0x00010000 */
#define DTS_CFGR1_TS1_SMP_TIME_1           (0x2U << DTS_CFGR1_TS1_SMP_TIME_Pos) /*!< 0x00020000 */
#define DTS_CFGR1_TS1_SMP_TIME_2           (0x4U << DTS_CFGR1_TS1_SMP_TIME_Pos) /*!< 0x00040000 */
#define DTS_CFGR1_TS1_SMP_TIME_3           (0x8U << DTS_CFGR1_TS1_SMP_TIME_Pos) /*!< 0x00080000 */
#define DTS_CFGR1_REFCLK_SEL_Pos           (20U)
#define DTS_CFGR1_REFCLK_SEL_Msk           (0x1U << DTS_CFGR1_REFCLK_SEL_Pos) /*!< 0x00100000 */
#define DTS_CFGR1_REFCLK_SEL               DTS_CFGR1_REFCLK_SEL_Msk    /*!< Reference Clock Selection */
#define DTS_CFGR1_Q_MEAS_OPT_Pos           (21U)
#define DTS_CFGR1_Q_MEAS_OPT_Msk           (0x1U << DTS_CFGR1_Q_MEAS_OPT_Pos) /*!< 0x00200000 */
#define DTS_CFGR1_Q_MEAS_OPT               DTS_CFGR1_Q_MEAS_OPT_Msk    /*!< Quick measure option bit  */
#define DTS_CFGR1_HSREF_CLK_DIV_Pos        (24U)
#define DTS_CFGR1_HSREF_CLK_DIV_Msk        (0x7FU << DTS_CFGR1_HSREF_CLK_DIV_Pos) /*!< 0x7F000000 */
#define DTS_CFGR1_HSREF_CLK_DIV            DTS_CFGR1_HSREF_CLK_DIV_Msk /*!< High Speed Clock Divider Ratio [6:0]*/

/******************  Bit definition for DTS_T0VALR1 register  ******************/
#define DTS_T0VALR1_TS1_FMT0_Pos           (0U)
#define DTS_T0VALR1_TS1_FMT0_Msk           (0xFFFFU << DTS_T0VALR1_TS1_FMT0_Pos) /*!< 0x0000FFFF */
#define DTS_T0VALR1_TS1_FMT0               DTS_T0VALR1_TS1_FMT0_Msk    /*!< Engineering value of the measured frequency at T0 for DTS1 */
#define DTS_T0VALR1_TS1_T0_Pos             (16U)
#define DTS_T0VALR1_TS1_T0_Msk             (0x3U << DTS_T0VALR1_TS1_T0_Pos) /*!< 0x00030000 */
#define DTS_T0VALR1_TS1_T0                 DTS_T0VALR1_TS1_T0_Msk      /*!< Engineering value of the DTSerature T0 for DTS1 */

/******************  Bit definition for DTS_RAMPVALR register  ******************/
#define DTS_RAMPVALR_TS1_RAMP_COEFF_Pos    (0U)
#define DTS_RAMPVALR_TS1_RAMP_COEFF_Msk    (0xFFFFU << DTS_RAMPVALR_TS1_RAMP_COEFF_Pos) /*!< 0x0000FFFF */
#define DTS_RAMPVALR_TS1_RAMP_COEFF        DTS_RAMPVALR_TS1_RAMP_COEFF_Msk /*!< Engineering value of the ramp coefficient for DTS1 */

/******************  Bit definition for DTS_ITR1 register      ******************/
#define DTS_ITR1_TS1_LITTHD_Pos            (0U)
#define DTS_ITR1_TS1_LITTHD_Msk            (0xFFFFU << DTS_ITR1_TS1_LITTHD_Pos) /*!< 0x0000FFFF */
#define DTS_ITR1_TS1_LITTHD                DTS_ITR1_TS1_LITTHD_Msk     /*!< Low interrupt threshold[15:0] for DTS1 */
#define DTS_ITR1_TS1_HITTHD_Pos            (16U)
#define DTS_ITR1_TS1_HITTHD_Msk            (0xFFFFU << DTS_ITR1_TS1_HITTHD_Pos) /*!< 0xFFFF0000 */
#define DTS_ITR1_TS1_HITTHD                DTS_ITR1_TS1_HITTHD_Msk     /*!< High interrupt threshold[15:0] for DTS1 */

/******************  Bit definition for DTS_DR register        ******************/
#define DTS_DR_TS1_MFREQ_Pos               (0U)
#define DTS_DR_TS1_MFREQ_Msk               (0xFFFFU << DTS_DR_TS1_MFREQ_Pos) /*!< 0x0000FFFF */
#define DTS_DR_TS1_MFREQ                   DTS_DR_TS1_MFREQ_Msk        /*!< Measured Frequency[15:0] for DTS1 */

/******************  Bit definition for DTS_SR register        ******************/
#define DTS_SR_TS1_ITEF_Pos                (0U)
#define DTS_SR_TS1_ITEF_Msk                (0x1U << DTS_SR_TS1_ITEF_Pos) /*!< 0x00000001 */
#define DTS_SR_TS1_ITEF                    DTS_SR_TS1_ITEF_Msk         /*!< Interrupt flag for end of measure for DTS1 */
#define DTS_SR_TS1_ITLF_Pos                (1U)
#define DTS_SR_TS1_ITLF_Msk                (0x1U << DTS_SR_TS1_ITLF_Pos) /*!< 0x00000002 */
#define DTS_SR_TS1_ITLF                    DTS_SR_TS1_ITLF_Msk         /*!< Interrupt flag for low threshold for DTS1  */
#define DTS_SR_TS1_ITHF_Pos                (2U)
#define DTS_SR_TS1_ITHF_Msk                (0x1U << DTS_SR_TS1_ITHF_Pos) /*!< 0x00000004 */
#define DTS_SR_TS1_ITHF                    DTS_SR_TS1_ITHF_Msk         /*!< Interrupt flag for high threshold for DTS1 */
#define DTS_SR_TS1_AITEF_Pos               (4U)
#define DTS_SR_TS1_AITEF_Msk               (0x1U << DTS_SR_TS1_AITEF_Pos) /*!< 0x00000010 */
#define DTS_SR_TS1_AITEF                   DTS_SR_TS1_AITEF_Msk        /*!< Asynchronous interrupt flag for end of measure for DTS1 */
#define DTS_SR_TS1_AITLF_Pos               (5U)
#define DTS_SR_TS1_AITLF_Msk               (0x1U << DTS_SR_TS1_AITLF_Pos) /*!< 0x00000020 */
#define DTS_SR_TS1_AITLF                   DTS_SR_TS1_AITLF_Msk        /*!< Asynchronous interrupt flag for low threshold for DTS1  */
#define DTS_SR_TS1_AITHF_Pos               (6U)
#define DTS_SR_TS1_AITHF_Msk               (0x1U << DTS_SR_TS1_AITHF_Pos) /*!< 0x00000040 */
#define DTS_SR_TS1_AITHF                   DTS_SR_TS1_AITHF_Msk        /*!< Asynchronous interrupt flag for high threshold for DTS1 */
#define DTS_SR_TS1_RDY_Pos                 (15U)
#define DTS_SR_TS1_RDY_Msk                 (0x1U << DTS_SR_TS1_RDY_Pos) /*!< 0x00008000 */
#define DTS_SR_TS1_RDY                     DTS_SR_TS1_RDY_Msk          /*!< DTS1 ready flag */

/******************  Bit definition for DTS_ITENR register      ******************/
#define DTS_ITENR_TS1_ITEEN_Pos            (0U)
#define DTS_ITENR_TS1_ITEEN_Msk            (0x1U << DTS_ITENR_TS1_ITEEN_Pos) /*!< 0x00000001 */
#define DTS_ITENR_TS1_ITEEN                DTS_ITENR_TS1_ITEEN_Msk     /*!< Enable interrupt flag for end of measure for DTS1 */
#define DTS_ITENR_TS1_ITLEN_Pos            (1U)
#define DTS_ITENR_TS1_ITLEN_Msk            (0x1U << DTS_ITENR_TS1_ITLEN_Pos) /*!< 0x00000002 */
#define DTS_ITENR_TS1_ITLEN                DTS_ITENR_TS1_ITLEN_Msk     /*!< Enable interrupt flag for low threshold for DTS1  */
#define DTS_ITENR_TS1_ITHEN_Pos            (2U)
#define DTS_ITENR_TS1_ITHEN_Msk            (0x1U << DTS_ITENR_TS1_ITHEN_Pos) /*!< 0x00000004 */
#define DTS_ITENR_TS1_ITHEN                DTS_ITENR_TS1_ITHEN_Msk     /*!< Enable interrupt flag for high threshold for DTS1 */
#define DTS_ITENR_TS1_AITEEN_Pos           (4U)
#define DTS_ITENR_TS1_AITEEN_Msk           (0x1U << DTS_ITENR_TS1_AITEEN_Pos) /*!< 0x00000010 */
#define DTS_ITENR_TS1_AITEEN               DTS_ITENR_TS1_AITEEN_Msk    /*!< Enable asynchronous interrupt flag for end of measure for DTS1 */
#define DTS_ITENR_TS1_AITLEN_Pos           (5U)
#define DTS_ITENR_TS1_AITLEN_Msk           (0x1U << DTS_ITENR_TS1_AITLEN_Pos) /*!< 0x00000020 */
#define DTS_ITENR_TS1_AITLEN               DTS_ITENR_TS1_AITLEN_Msk    /*!< Enable Asynchronous interrupt flag for low threshold for DTS1  */
#define DTS_ITENR_TS1_AITHEN_Pos           (6U)
#define DTS_ITENR_TS1_AITHEN_Msk           (0x1U << DTS_ITENR_TS1_AITHEN_Pos) /*!< 0x00000040 */
#define DTS_ITENR_TS1_AITHEN               DTS_ITENR_TS1_AITHEN_Msk    /*!< Enable asynchronous interrupt flag for high threshold for DTS1 */

/******************  Bit definition for DTS_ICIFR register      ******************/
#define DTS_ICIFR_TS1_CITEF_Pos            (0U)
#define DTS_ICIFR_TS1_CITEF_Msk            (0x1U << DTS_ICIFR_TS1_CITEF_Pos) /*!< 0x00000001 */
#define DTS_ICIFR_TS1_CITEF                DTS_ICIFR_TS1_CITEF_Msk     /*!< Clear the IT flag for End Of Measure for DTS1 */
#define DTS_ICIFR_TS1_CITLF_Pos            (1U)
#define DTS_ICIFR_TS1_CITLF_Msk            (0x1U << DTS_ICIFR_TS1_CITLF_Pos) /*!< 0x00000002 */
#define DTS_ICIFR_TS1_CITLF                DTS_ICIFR_TS1_CITLF_Msk     /*!< Clear the IT flag for low threshold for DTS1  */
#define DTS_ICIFR_TS1_CITHF_Pos            (2U)
#define DTS_ICIFR_TS1_CITHF_Msk            (0x1U << DTS_ICIFR_TS1_CITHF_Pos) /*!< 0x00000004 */
#define DTS_ICIFR_TS1_CITHF                DTS_ICIFR_TS1_CITHF_Msk     /*!< Clear the IT flag for high threshold on DTS1  */
#define DTS_ICIFR_TS1_CAITEF_Pos           (4U)
#define DTS_ICIFR_TS1_CAITEF_Msk           (0x1U << DTS_ICIFR_TS1_CAITEF_Pos) /*!< 0x00000010 */
#define DTS_ICIFR_TS1_CAITEF               DTS_ICIFR_TS1_CAITEF_Msk    /*!< Clear the asynchronous IT flag for End Of Measure for DTS1 */
#define DTS_ICIFR_TS1_CAITLF_Pos           (5U)
#define DTS_ICIFR_TS1_CAITLF_Msk           (0x1U << DTS_ICIFR_TS1_CAITLF_Pos) /*!< 0x00000020 */
#define DTS_ICIFR_TS1_CAITLF               DTS_ICIFR_TS1_CAITLF_Msk    /*!< Clear the asynchronous IT flag for low threshold for DTS1  */
#define DTS_ICIFR_TS1_CAITHF_Pos           (6U)
#define DTS_ICIFR_TS1_CAITHF_Msk           (0x1U << DTS_ICIFR_TS1_CAITHF_Pos) /*!< 0x00000040 */
#define DTS_ICIFR_TS1_CAITHF               DTS_ICIFR_TS1_CAITHF_Msk    /*!< Clear the asynchronous IT flag for high threshold on DTS1  */


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
