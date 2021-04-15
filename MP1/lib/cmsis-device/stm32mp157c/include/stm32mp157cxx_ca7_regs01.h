/******************************************************************************/
/*                                                                            */
/*                        Analog to Digital Converter                         */
/*                                                                            */
/******************************************************************************/
/*
* @brief Specific device feature definitions
*/
#define ADC_MULTIMODE_SUPPORT                          /*!< ADC feature available only on specific devices: multimode available on devices with several ADC instances */

/********************  Bit definition for ADC_ISR register  ********************/
#define ADC_ISR_ADRDY_Pos                  (0U)
#define ADC_ISR_ADRDY_Msk                  (0x1U << ADC_ISR_ADRDY_Pos)           /*!< 0x00000001 */
#define ADC_ISR_ADRDY                      ADC_ISR_ADRDY_Msk                     /*!< ADC Ready (ADRDY) flag  */
#define ADC_ISR_EOSMP_Pos                 (1U)
#define ADC_ISR_EOSMP_Msk                 (0x1U << ADC_ISR_EOSMP_Pos)          /*!< 0x00000002 */
#define ADC_ISR_EOSMP                     ADC_ISR_EOSMP_Msk                    /*!< ADC End of Sampling flag */
#define ADC_ISR_EOC_Pos                   (2U)
#define ADC_ISR_EOC_Msk                   (0x1U << ADC_ISR_EOC_Pos)            /*!< 0x00000004 */
#define ADC_ISR_EOC                       ADC_ISR_EOC_Msk                      /*!< ADC End of Regular Conversion flag */
#define ADC_ISR_EOS_Pos                   (3U)
#define ADC_ISR_EOS_Msk                   (0x1U << ADC_ISR_EOS_Pos)            /*!< 0x00000008 */
#define ADC_ISR_EOS                       ADC_ISR_EOS_Msk                      /*!< ADC End of Regular sequence of Conversions flag */
#define ADC_ISR_OVR_Pos                   (4U)
#define ADC_ISR_OVR_Msk                   (0x1U << ADC_ISR_OVR_Pos)            /*!< 0x00000010 */
#define ADC_ISR_OVR                       ADC_ISR_OVR_Msk                      /*!< ADC overrun flag */
#define ADC_ISR_JEOC_Pos                  (5U)
#define ADC_ISR_JEOC_Msk                  (0x1U << ADC_ISR_JEOC_Pos)           /*!< 0x00000020 */
#define ADC_ISR_JEOC                      ADC_ISR_JEOC_Msk                     /*!< ADC End of Injected Conversion flag */
#define ADC_ISR_JEOS_Pos                  (6U)
#define ADC_ISR_JEOS_Msk                  (0x1U << ADC_ISR_JEOS_Pos)           /*!< 0x00000040 */
#define ADC_ISR_JEOS                      ADC_ISR_JEOS_Msk                     /*!< ADC End of Injected sequence of Conversions flag */
#define ADC_ISR_AWD1_Pos                  (7U)
#define ADC_ISR_AWD1_Msk                  (0x1U << ADC_ISR_AWD1_Pos)           /*!< 0x00000080 */
#define ADC_ISR_AWD1                      ADC_ISR_AWD1_Msk                     /*!< ADC Analog watchdog 1 flag */
#define ADC_ISR_AWD2_Pos                  (8U)
#define ADC_ISR_AWD2_Msk                  (0x1U << ADC_ISR_AWD2_Pos)           /*!< 0x00000100 */
#define ADC_ISR_AWD2                      ADC_ISR_AWD2_Msk                     /*!< ADC Analog watchdog 2 flag */
#define ADC_ISR_AWD3_Pos                  (9U)
#define ADC_ISR_AWD3_Msk                  (0x1U << ADC_ISR_AWD3_Pos)           /*!< 0x00000200 */
#define ADC_ISR_AWD3                      ADC_ISR_AWD3_Msk                     /*!< ADC Analog watchdog 3 flag */
#define ADC_ISR_JQOVF_Pos                 (10U)
#define ADC_ISR_JQOVF_Msk                 (0x1U << ADC_ISR_JQOVF_Pos)          /*!< 0x00000400 */
#define ADC_ISR_JQOVF                     ADC_ISR_JQOVF_Msk                    /*!< ADC Injected Context Queue Overflow flag */

/********************  Bit definition for ADC_IER register  ********************/
#define ADC_IER_ADRDYIE_Pos               (0U)
#define ADC_IER_ADRDYIE_Msk               (0x1U << ADC_IER_ADRDYIE_Pos)            /*!< 0x00000001 */
#define ADC_IER_ADRDYIE                   ADC_IER_ADRDYIE_Msk                      /*!< ADC Ready (ADRDY) interrupt source */
#define ADC_IER_EOSMPIE_Pos               (1U)
#define ADC_IER_EOSMPIE_Msk               (0x1U << ADC_IER_EOSMPIE_Pos)          /*!< 0x00000002 */
#define ADC_IER_EOSMPIE                   ADC_IER_EOSMPIE_Msk                    /*!< ADC End of Sampling interrupt source */
#define ADC_IER_EOCIE_Pos                 (2U)
#define ADC_IER_EOCIE_Msk                 (0x1U << ADC_IER_EOCIE_Pos)            /*!< 0x00000004 */
#define ADC_IER_EOCIE                     ADC_IER_EOCIE_Msk                      /*!< ADC End of Regular Conversion interrupt source */
#define ADC_IER_EOSIE_Pos                 (3U)
#define ADC_IER_EOSIE_Msk                 (0x1U << ADC_IER_EOSIE_Pos)            /*!< 0x00000008 */
#define ADC_IER_EOSIE                     ADC_IER_EOSIE_Msk                      /*!< ADC End of Regular sequence of Conversions interrupt source */
#define ADC_IER_OVRIE_Pos                 (4U)
#define ADC_IER_OVRIE_Msk                 (0x1U << ADC_IER_OVRIE_Pos)            /*!< 0x00000010 */
#define ADC_IER_OVRIE                     ADC_IER_OVRIE_Msk                      /*!< ADC overrun interrupt source */
#define ADC_IER_JEOCIE_Pos                (5U)
#define ADC_IER_JEOCIE_Msk                (0x1U << ADC_IER_JEOCIE_Pos)           /*!< 0x00000020 */
#define ADC_IER_JEOCIE                    ADC_IER_JEOCIE_Msk                     /*!< ADC End of Injected Conversion interrupt source */
#define ADC_IER_JEOSIE_Pos                (6U)
#define ADC_IER_JEOSIE_Msk                (0x1U << ADC_IER_JEOSIE_Pos)           /*!< 0x00000040 */
#define ADC_IER_JEOSIE                    ADC_IER_JEOSIE_Msk                     /*!< ADC End of Injected sequence of Conversions interrupt source */
#define ADC_IER_AWD1IE_Pos                (7U)
#define ADC_IER_AWD1IE_Msk                (0x1U << ADC_IER_AWD1IE_Pos)           /*!< 0x00000080 */
#define ADC_IER_AWD1IE                    ADC_IER_AWD1IE_Msk                     /*!< ADC Analog watchdog 1 interrupt source */
#define ADC_IER_AWD2IE_Pos                (8U)
#define ADC_IER_AWD2IE_Msk                (0x1U << ADC_IER_AWD2IE_Pos)           /*!< 0x00000100 */
#define ADC_IER_AWD2IE                    ADC_IER_AWD2IE_Msk                     /*!< ADC Analog watchdog 2 interrupt source */
#define ADC_IER_AWD3IE_Pos                (9U)
#define ADC_IER_AWD3IE_Msk                (0x1U << ADC_IER_AWD3IE_Pos)           /*!< 0x00000200 */
#define ADC_IER_AWD3IE                    ADC_IER_AWD3IE_Msk                     /*!< ADC Analog watchdog 3 interrupt source */
#define ADC_IER_JQOVFIE_Pos               (10U)
#define ADC_IER_JQOVFIE_Msk               (0x1U << ADC_IER_JQOVFIE_Pos)          /*!< 0x00000400 */
#define ADC_IER_JQOVFIE                   ADC_IER_JQOVFIE_Msk                    /*!< ADC Injected Context Queue Overflow interrupt source */

/********************  Bit definition for ADC_CR register  ********************/
#define ADC_CR_ADEN_Pos                   (0U)
#define ADC_CR_ADEN_Msk                   (0x1U << ADC_CR_ADEN_Pos)            /*!< 0x00000001 */
#define ADC_CR_ADEN                       ADC_CR_ADEN_Msk                      /*!< ADC Enable control */
#define ADC_CR_ADDIS_Pos                  (1U)
#define ADC_CR_ADDIS_Msk                  (0x1U << ADC_CR_ADDIS_Pos)           /*!< 0x00000002 */
#define ADC_CR_ADDIS                      ADC_CR_ADDIS_Msk                     /*!< ADC Disable command */
#define ADC_CR_ADSTART_Pos                (2U)
#define ADC_CR_ADSTART_Msk                (0x1U << ADC_CR_ADSTART_Pos)         /*!< 0x00000004 */
#define ADC_CR_ADSTART                    ADC_CR_ADSTART_Msk                   /*!< ADC Start of Regular conversion */
#define ADC_CR_JADSTART_Pos               (3U)
#define ADC_CR_JADSTART_Msk               (0x1U << ADC_CR_JADSTART_Pos)        /*!< 0x00000008 */
#define ADC_CR_JADSTART                   ADC_CR_JADSTART_Msk                  /*!< ADC Start of injected conversion */
#define ADC_CR_ADSTP_Pos                  (4U)
#define ADC_CR_ADSTP_Msk                  (0x1U << ADC_CR_ADSTP_Pos)           /*!< 0x00000010 */
#define ADC_CR_ADSTP                      ADC_CR_ADSTP_Msk                     /*!< ADC Stop of Regular conversion */
#define ADC_CR_JADSTP_Pos                 (5U)
#define ADC_CR_JADSTP_Msk                 (0x1U << ADC_CR_JADSTP_Pos)          /*!< 0x00000020 */
#define ADC_CR_JADSTP                     ADC_CR_JADSTP_Msk                    /*!< ADC Stop of injected conversion */
#define ADC_CR_BOOST_Pos                  (8U)
#define ADC_CR_BOOST_Msk                  (0x1U << ADC_CR_BOOST_Pos)           /*!< 0x00000100 */
#define ADC_CR_BOOST                      ADC_CR_BOOST_Msk                     /*!< ADC Boost Mode */
#define ADC_CR_ADCALLIN_Pos               (16U)
#define ADC_CR_ADCALLIN_Msk               (0x1U << ADC_CR_ADCALLIN_Pos)        /*!< 0x00010000 */
#define ADC_CR_ADCALLIN                   ADC_CR_ADCALLIN_Msk                  /*!< ADC Linearity calibration */
#define ADC_CR_LINCALRDYW1_Pos            (22U)
#define ADC_CR_LINCALRDYW1_Msk            (0x1U << ADC_CR_LINCALRDYW1_Pos)     /*!< 0x00400000 */
#define ADC_CR_LINCALRDYW1                ADC_CR_LINCALRDYW1_Msk               /*!< ADC Linearity calibration ready Word 1 */
#define ADC_CR_LINCALRDYW2_Pos            (23U)
#define ADC_CR_LINCALRDYW2_Msk            (0x1U << ADC_CR_LINCALRDYW2_Pos)     /*!< 0x00800000 */
#define ADC_CR_LINCALRDYW2                ADC_CR_LINCALRDYW2_Msk               /*!< ADC Linearity calibration ready Word 2 */
#define ADC_CR_LINCALRDYW3_Pos            (24U)
#define ADC_CR_LINCALRDYW3_Msk            (0x1U << ADC_CR_LINCALRDYW3_Pos)     /*!< 0x01000000 */
#define ADC_CR_LINCALRDYW3                ADC_CR_LINCALRDYW3_Msk               /*!< ADC Linearity calibration ready Word 3 */
#define ADC_CR_LINCALRDYW4_Pos            (25U)
#define ADC_CR_LINCALRDYW4_Msk            (0x1U << ADC_CR_LINCALRDYW4_Pos)     /*!< 0x02000000 */
#define ADC_CR_LINCALRDYW4                ADC_CR_LINCALRDYW4_Msk               /*!< ADC Linearity calibration ready Word 4 */
#define ADC_CR_LINCALRDYW5_Pos            (26U)
#define ADC_CR_LINCALRDYW5_Msk            (0x1U << ADC_CR_LINCALRDYW5_Pos)     /*!< 0x04000000 */
#define ADC_CR_LINCALRDYW5                ADC_CR_LINCALRDYW5_Msk               /*!< ADC Linearity calibration ready Word 5 */
#define ADC_CR_LINCALRDYW6_Pos            (27U)
#define ADC_CR_LINCALRDYW6_Msk            (0x1U << ADC_CR_LINCALRDYW6_Pos)     /*!< 0x08000000 */
#define ADC_CR_LINCALRDYW6                ADC_CR_LINCALRDYW6_Msk               /*!< ADC Linearity calibration ready Word 6 */
#define ADC_CR_ADVREGEN_Pos               (28U)
#define ADC_CR_ADVREGEN_Msk               (0x1U << ADC_CR_ADVREGEN_Pos)        /*!< 0x10000000 */
#define ADC_CR_ADVREGEN                   ADC_CR_ADVREGEN_Msk                  /*!< ADC Voltage regulator Enable */
#define ADC_CR_DEEPPWD_Pos                (29U)
#define ADC_CR_DEEPPWD_Msk                (0x1U << ADC_CR_DEEPPWD_Pos)         /*!< 0x20000000 */
#define ADC_CR_DEEPPWD                    ADC_CR_DEEPPWD_Msk                   /*!< ADC Deep power down Enable */
#define ADC_CR_ADCALDIF_Pos               (30U)
#define ADC_CR_ADCALDIF_Msk               (0x1U << ADC_CR_ADCALDIF_Pos)        /*!< 0x40000000 */
#define ADC_CR_ADCALDIF                   ADC_CR_ADCALDIF_Msk                  /*!< ADC Differential Mode for calibration */
#define ADC_CR_ADCAL_Pos                  (31U)
#define ADC_CR_ADCAL_Msk                  (0x1U << ADC_CR_ADCAL_Pos)           /*!< 0x80000000 */
#define ADC_CR_ADCAL                      ADC_CR_ADCAL_Msk                     /*!< ADC Calibration */

/********************  Bit definition for ADC_CFGR register  ********************/
#define ADC_CFGR_DMNGT_Pos                (0U)
#define ADC_CFGR_DMNGT_Msk                (0x3U << ADC_CFGR_DMNGT_Pos)         /*!< 0x00000003 */
#define ADC_CFGR_DMNGT                    ADC_CFGR_DMNGT_Msk                   /*!< ADC Data Management configuration */
#define ADC_CFGR_DMNGT_0                  (0x1U << ADC_CFGR_DMNGT_Pos)         /*!< 0x00000001 */
#define ADC_CFGR_DMNGT_1                  (0x2U << ADC_CFGR_DMNGT_Pos)         /*!< 0x00000002 */

#define ADC_CFGR_RES_Pos                  (2U)
#define ADC_CFGR_RES_Msk                  (0x7U << ADC_CFGR_RES_Pos)           /*!< 0x0000001C */
#define ADC_CFGR_RES                      ADC_CFGR_RES_Msk                     /*!< ADC Data resolution */
#define ADC_CFGR_RES_0                    (0x1U << ADC_CFGR_RES_Pos)           /*!< 0x00000004 */
#define ADC_CFGR_RES_1                    (0x2U << ADC_CFGR_RES_Pos)           /*!< 0x00000008 */
#define ADC_CFGR_RES_2                    (0x4U << ADC_CFGR_RES_Pos)           /*!< 0x00000010 */

#define ADC_CFGR_EXTSEL_Pos               (5U)
#define ADC_CFGR_EXTSEL_Msk               (0x1FU << ADC_CFGR_EXTSEL_Pos)       /*!< 0x000003E0 */
#define ADC_CFGR_EXTSEL                   ADC_CFGR_EXTSEL_Msk                  /*!< ADC External trigger selection for regular group */
#define ADC_CFGR_EXTSEL_0                 (0x01U << ADC_CFGR_EXTSEL_Pos)       /*!< 0x00000020 */
#define ADC_CFGR_EXTSEL_1                 (0x02U << ADC_CFGR_EXTSEL_Pos)       /*!< 0x00000040 */
#define ADC_CFGR_EXTSEL_2                 (0x04U << ADC_CFGR_EXTSEL_Pos)       /*!< 0x00000080 */
#define ADC_CFGR_EXTSEL_3                 (0x08U << ADC_CFGR_EXTSEL_Pos)       /*!< 0x00000100 */
#define ADC_CFGR_EXTSEL_4                 (0x10U << ADC_CFGR_EXTSEL_Pos)       /*!< 0x00000200 */

#define ADC_CFGR_EXTEN_Pos                (10U)
#define ADC_CFGR_EXTEN_Msk                (0x3U << ADC_CFGR_EXTEN_Pos)         /*!< 0x00000C00 */
#define ADC_CFGR_EXTEN                    ADC_CFGR_EXTEN_Msk                   /*!< ADC External trigger enable and polarity selection for regular channels */
#define ADC_CFGR_EXTEN_0                  (0x1U << ADC_CFGR_EXTEN_Pos)         /*!< 0x00000400 */
#define ADC_CFGR_EXTEN_1                  (0x2U << ADC_CFGR_EXTEN_Pos)         /*!< 0x00000800 */

#define ADC_CFGR_OVRMOD_Pos               (12U)
#define ADC_CFGR_OVRMOD_Msk               (0x1U << ADC_CFGR_OVRMOD_Pos)        /*!< 0x00001000 */
#define ADC_CFGR_OVRMOD                   ADC_CFGR_OVRMOD_Msk                  /*!< ADC overrun mode */
#define ADC_CFGR_CONT_Pos                 (13U)
#define ADC_CFGR_CONT_Msk                 (0x1U << ADC_CFGR_CONT_Pos)          /*!< 0x00002000 */
#define ADC_CFGR_CONT                     ADC_CFGR_CONT_Msk                    /*!< ADC Single/continuous conversion mode for regular conversion */
#define ADC_CFGR_AUTDLY_Pos               (14U)
#define ADC_CFGR_AUTDLY_Msk               (0x1U << ADC_CFGR_AUTDLY_Pos)        /*!< 0x00004000 */
#define ADC_CFGR_AUTDLY                   ADC_CFGR_AUTDLY_Msk                  /*!< ADC Delayed conversion mode */

#define ADC_CFGR_DISCEN_Pos               (16U)
#define ADC_CFGR_DISCEN_Msk               (0x1U << ADC_CFGR_DISCEN_Pos)        /*!< 0x00010000 */
#define ADC_CFGR_DISCEN                   ADC_CFGR_DISCEN_Msk                  /*!< ADC Discontinuous mode for regular channels */

#define ADC_CFGR_DISCNUM_Pos              (17U)
#define ADC_CFGR_DISCNUM_Msk              (0x7U << ADC_CFGR_DISCNUM_Pos)       /*!< 0x000E0000 */
#define ADC_CFGR_DISCNUM                  ADC_CFGR_DISCNUM_Msk                 /*!< ADC Discontinuous mode channel count */
#define ADC_CFGR_DISCNUM_0                (0x1U << ADC_CFGR_DISCNUM_Pos)       /*!< 0x00020000 */
#define ADC_CFGR_DISCNUM_1                (0x2U << ADC_CFGR_DISCNUM_Pos)       /*!< 0x00040000 */
#define ADC_CFGR_DISCNUM_2                (0x4U << ADC_CFGR_DISCNUM_Pos)       /*!< 0x00080000 */

#define ADC_CFGR_JDISCEN_Pos              (20U)
#define ADC_CFGR_JDISCEN_Msk              (0x1U << ADC_CFGR_JDISCEN_Pos)       /*!< 0x00100000 */
#define ADC_CFGR_JDISCEN                  ADC_CFGR_JDISCEN_Msk                 /*!< ADC Discontinuous mode on injected channels */
#define ADC_CFGR_JQM_Pos                  (21U)
#define ADC_CFGR_JQM_Msk                  (0x1U << ADC_CFGR_JQM_Pos)           /*!< 0x00200000 */
#define ADC_CFGR_JQM                      ADC_CFGR_JQM_Msk                     /*!< ADC JSQR Queue mode */
#define ADC_CFGR_AWD1SGL_Pos              (22U)
#define ADC_CFGR_AWD1SGL_Msk              (0x1U << ADC_CFGR_AWD1SGL_Pos)       /*!< 0x00400000 */
#define ADC_CFGR_AWD1SGL                  ADC_CFGR_AWD1SGL_Msk                 /*!< Enable the watchdog 1 on a single channel or on all channels */
#define ADC_CFGR_AWD1EN_Pos               (23U)
#define ADC_CFGR_AWD1EN_Msk               (0x1U << ADC_CFGR_AWD1EN_Pos)        /*!< 0x00800000 */
#define ADC_CFGR_AWD1EN                   ADC_CFGR_AWD1EN_Msk                  /*!< ADC Analog watchdog 1 enable on regular Channels */
#define ADC_CFGR_JAWD1EN_Pos              (24U)
#define ADC_CFGR_JAWD1EN_Msk              (0x1U << ADC_CFGR_JAWD1EN_Pos)       /*!< 0x01000000 */
#define ADC_CFGR_JAWD1EN                  ADC_CFGR_JAWD1EN_Msk                 /*!< ADC Analog watchdog 1 enable on injected Channels */
#define ADC_CFGR_JAUTO_Pos                (25U)
#define ADC_CFGR_JAUTO_Msk                (0x1U << ADC_CFGR_JAUTO_Pos)         /*!< 0x02000000 */
#define ADC_CFGR_JAUTO                    ADC_CFGR_JAUTO_Msk                   /*!< ADC Automatic injected group conversion */

#define ADC_CFGR_AWD1CH_Pos               (26U)
#define ADC_CFGR_AWD1CH_Msk               (0x1FU << ADC_CFGR_AWD1CH_Pos)       /*!< 0x7C000000 */
#define ADC_CFGR_AWD1CH                   ADC_CFGR_AWD1CH_Msk                  /*!< ADC Analog watchdog 1 Channel selection */
#define ADC_CFGR_AWD1CH_0                 (0x01U << ADC_CFGR_AWD1CH_Pos)       /*!< 0x04000000 */
#define ADC_CFGR_AWD1CH_1                 (0x02U << ADC_CFGR_AWD1CH_Pos)       /*!< 0x08000000 */
#define ADC_CFGR_AWD1CH_2                 (0x04U << ADC_CFGR_AWD1CH_Pos)       /*!< 0x10000000 */
#define ADC_CFGR_AWD1CH_3                 (0x08U << ADC_CFGR_AWD1CH_Pos)       /*!< 0x20000000 */
#define ADC_CFGR_AWD1CH_4                 (0x10U << ADC_CFGR_AWD1CH_Pos)       /*!< 0x40000000 */

#define ADC_CFGR_JQDIS_Pos                (31U)
#define ADC_CFGR_JQDIS_Msk                (0x1U << ADC_CFGR_JQDIS_Pos)         /*!< 0x80000000 */
#define ADC_CFGR_JQDIS                    ADC_CFGR_JQDIS_Msk                   /*!< ADC Injected queue disable */

/********************  Bit definition for ADC_CFGR2 register  ********************/
#define ADC_CFGR2_ROVSE_Pos               (0U)
#define ADC_CFGR2_ROVSE_Msk               (0x1U << ADC_CFGR2_ROVSE_Pos)        /*!< 0x00000001 */
#define ADC_CFGR2_ROVSE                   ADC_CFGR2_ROVSE_Msk                  /*!< ADC Regular group oversampler enable */
#define ADC_CFGR2_JOVSE_Pos               (1U)
#define ADC_CFGR2_JOVSE_Msk               (0x1U << ADC_CFGR2_JOVSE_Pos)        /*!< 0x00000002 */
#define ADC_CFGR2_JOVSE                   ADC_CFGR2_JOVSE_Msk                  /*!< ADC Injected group oversampler enable */

#define ADC_CFGR2_OVSR_Pos                (2U)
#define ADC_CFGR2_OVSR_Msk                (0x7U << ADC_CFGR2_OVSR_Pos)         /*!< 0x0000001C */
#define ADC_CFGR2_OVSR                    ADC_CFGR2_OVSR_Msk                   /*!< ADC Regular group oversampler enable TO Be removed after ADC driver update*/
#define ADC_CFGR2_OVSR_0                  (0x1U << ADC_CFGR2_OVSR_Pos)         /*!< 0x00000004 */
#define ADC_CFGR2_OVSR_1                  (0x2U << ADC_CFGR2_OVSR_Pos)         /*!< 0x00000008 */
#define ADC_CFGR2_OVSR_2                  (0x4U << ADC_CFGR2_OVSR_Pos)         /*!< 0x00000010 */

#define ADC_CFGR2_OVSS_Pos                (5U)
#define ADC_CFGR2_OVSS_Msk                (0xFU << ADC_CFGR2_OVSS_Pos)         /*!< 0x000001E0 */
#define ADC_CFGR2_OVSS                    ADC_CFGR2_OVSS_Msk                   /*!< ADC Regular Oversampling shift */
#define ADC_CFGR2_OVSS_0                  (0x1U << ADC_CFGR2_OVSS_Pos)         /*!< 0x00000020 */
#define ADC_CFGR2_OVSS_1                  (0x2U << ADC_CFGR2_OVSS_Pos)         /*!< 0x00000040 */
#define ADC_CFGR2_OVSS_2                  (0x4U << ADC_CFGR2_OVSS_Pos)         /*!< 0x00000080 */
#define ADC_CFGR2_OVSS_3                  (0x8U << ADC_CFGR2_OVSS_Pos)         /*!< 0x00000100 */

#define ADC_CFGR2_TROVS_Pos               (9U)
#define ADC_CFGR2_TROVS_Msk               (0x1U << ADC_CFGR2_TROVS_Pos)        /*!< 0x00000200 */
#define ADC_CFGR2_TROVS                   ADC_CFGR2_TROVS_Msk                  /*!< ADC Triggered regular Oversampling */
#define ADC_CFGR2_ROVSM_Pos               (10U)
#define ADC_CFGR2_ROVSM_Msk               (0x1U << ADC_CFGR2_ROVSM_Pos)        /*!< 0x00000400 */
#define ADC_CFGR2_ROVSM                   ADC_CFGR2_ROVSM_Msk                  /*!< ADC Regular oversampling mode */

#define ADC_CFGR2_RSHIFT1_Pos             (11U)
#define ADC_CFGR2_RSHIFT1_Msk             (0x1U << ADC_CFGR2_RSHIFT1_Pos)      /*!< 0x00000800 */
#define ADC_CFGR2_RSHIFT1                 ADC_CFGR2_RSHIFT1_Msk                /*!< ADC Right-shift data after Offset 1 correction */
#define ADC_CFGR2_RSHIFT2_Pos             (12U)
#define ADC_CFGR2_RSHIFT2_Msk             (0x1U << ADC_CFGR2_RSHIFT2_Pos)      /*!< 0x00001000 */
#define ADC_CFGR2_RSHIFT2                 ADC_CFGR2_RSHIFT2_Msk                /*!< ADC Right-shift data after Offset 2 correction */
#define ADC_CFGR2_RSHIFT3_Pos             (13U)
#define ADC_CFGR2_RSHIFT3_Msk             (0x1U << ADC_CFGR2_RSHIFT3_Pos)      /*!< 0x00002000 */
#define ADC_CFGR2_RSHIFT3                 ADC_CFGR2_RSHIFT3_Msk                /*!< ADC Right-shift data after Offset 3 correction */
#define ADC_CFGR2_RSHIFT4_Pos             (14U)
#define ADC_CFGR2_RSHIFT4_Msk             (0x1U << ADC_CFGR2_RSHIFT4_Pos)      /*!< 0x00004000 */
#define ADC_CFGR2_RSHIFT4                 ADC_CFGR2_RSHIFT4_Msk                /*!< ADC Right-shift data after Offset 4 correction */

#define ADC_CFGR2_OSR_Pos                 (16U)
#define ADC_CFGR2_OSR_Msk                 (0x3FFU << ADC_CFGR2_OSR_Pos)        /*!< 0x03FF0000 */
#define ADC_CFGR2_OSR                     ADC_CFGR2_OSR_Msk                    /*!< ADC oversampling Ratio */
#define ADC_CFGR2_OSR_0                   (0x001U << ADC_CFGR2_OSR_Pos)        /*!< 0x00010000 */
#define ADC_CFGR2_OSR_1                   (0x002U << ADC_CFGR2_OSR_Pos)        /*!< 0x00020000 */
#define ADC_CFGR2_OSR_2                   (0x004U << ADC_CFGR2_OSR_Pos)        /*!< 0x00040000 */
#define ADC_CFGR2_OSR_3                   (0x008U << ADC_CFGR2_OSR_Pos)        /*!< 0x00080000 */
#define ADC_CFGR2_OSR_4                   (0x010U << ADC_CFGR2_OSR_Pos)        /*!< 0x00100000 */
#define ADC_CFGR2_OSR_5                   (0x020U << ADC_CFGR2_OSR_Pos)        /*!< 0x00200000 */
#define ADC_CFGR2_OSR_6                   (0x040U << ADC_CFGR2_OSR_Pos)        /*!< 0x00400000 */
#define ADC_CFGR2_OSR_7                   (0x080U << ADC_CFGR2_OSR_Pos)        /*!< 0x00800000 */
#define ADC_CFGR2_OSR_8                   (0x100U << ADC_CFGR2_OSR_Pos)        /*!< 0x01000000 */
#define ADC_CFGR2_OSR_9                   (0x200U << ADC_CFGR2_OSR_Pos)        /*!< 0x02000000 */

#define ADC_CFGR2_LSHIFT_Pos              (28U)
#define ADC_CFGR2_LSHIFT_Msk              (0xFU << ADC_CFGR2_LSHIFT_Pos)       /*!< 0xF0000000 */
#define ADC_CFGR2_LSHIFT                  ADC_CFGR2_LSHIFT_Msk                 /*!< ADC Left shift factor */
#define ADC_CFGR2_LSHIFT_0                (0x1U << ADC_CFGR2_LSHIFT_Pos)       /*!< 0x10000000 */
#define ADC_CFGR2_LSHIFT_1                (0x2U << ADC_CFGR2_LSHIFT_Pos)       /*!< 0x20000000 */
#define ADC_CFGR2_LSHIFT_2                (0x4U << ADC_CFGR2_LSHIFT_Pos)       /*!< 0x40000000 */
#define ADC_CFGR2_LSHIFT_3                (0x8U << ADC_CFGR2_LSHIFT_Pos)       /*!< 0x80000000 */
/********************  Bit definition for ADC_SMPR1 register  ********************/
#define ADC_SMPR1_SMP0_Pos                (0U)
#define ADC_SMPR1_SMP0_Msk                (0x7U << ADC_SMPR1_SMP0_Pos)         /*!< 0x00000007 */
#define ADC_SMPR1_SMP0                    ADC_SMPR1_SMP0_Msk                   /*!< ADC Channel 0 Sampling time selection  */
#define ADC_SMPR1_SMP0_0                  (0x1U << ADC_SMPR1_SMP0_Pos)         /*!< 0x00000001 */
#define ADC_SMPR1_SMP0_1                  (0x2U << ADC_SMPR1_SMP0_Pos)         /*!< 0x00000002 */
#define ADC_SMPR1_SMP0_2                  (0x4U << ADC_SMPR1_SMP0_Pos)         /*!< 0x00000004 */

#define ADC_SMPR1_SMP1_Pos                (3U)
#define ADC_SMPR1_SMP1_Msk                (0x7U << ADC_SMPR1_SMP1_Pos)         /*!< 0x00000038 */
#define ADC_SMPR1_SMP1                    ADC_SMPR1_SMP1_Msk                   /*!< ADC Channel 1 Sampling time selection  */
#define ADC_SMPR1_SMP1_0                  (0x1U << ADC_SMPR1_SMP1_Pos)         /*!< 0x00000008 */
#define ADC_SMPR1_SMP1_1                  (0x2U << ADC_SMPR1_SMP1_Pos)         /*!< 0x00000010 */
#define ADC_SMPR1_SMP1_2                  (0x4U << ADC_SMPR1_SMP1_Pos)         /*!< 0x00000020 */

#define ADC_SMPR1_SMP2_Pos                (6U)
#define ADC_SMPR1_SMP2_Msk                (0x7U << ADC_SMPR1_SMP2_Pos)         /*!< 0x000001C0 */
#define ADC_SMPR1_SMP2                    ADC_SMPR1_SMP2_Msk                   /*!< ADC Channel 2 Sampling time selection  */
#define ADC_SMPR1_SMP2_0                  (0x1U << ADC_SMPR1_SMP2_Pos)         /*!< 0x00000040 */
#define ADC_SMPR1_SMP2_1                  (0x2U << ADC_SMPR1_SMP2_Pos)         /*!< 0x00000080 */
#define ADC_SMPR1_SMP2_2                  (0x4U << ADC_SMPR1_SMP2_Pos)         /*!< 0x00000100 */

#define ADC_SMPR1_SMP3_Pos                (9U)
#define ADC_SMPR1_SMP3_Msk                (0x7U << ADC_SMPR1_SMP3_Pos)         /*!< 0x00000E00 */
#define ADC_SMPR1_SMP3                    ADC_SMPR1_SMP3_Msk                   /*!< ADC Channel 3 Sampling time selection  */
#define ADC_SMPR1_SMP3_0                  (0x1U << ADC_SMPR1_SMP3_Pos)         /*!< 0x00000200 */
#define ADC_SMPR1_SMP3_1                  (0x2U << ADC_SMPR1_SMP3_Pos)         /*!< 0x00000400 */
#define ADC_SMPR1_SMP3_2                  (0x4U << ADC_SMPR1_SMP3_Pos)         /*!< 0x00000800 */

#define ADC_SMPR1_SMP4_Pos                (12U)
#define ADC_SMPR1_SMP4_Msk                (0x7U << ADC_SMPR1_SMP4_Pos)         /*!< 0x00007000 */
#define ADC_SMPR1_SMP4                    ADC_SMPR1_SMP4_Msk                   /*!< ADC Channel 4 Sampling time selection  */
#define ADC_SMPR1_SMP4_0                  (0x1U << ADC_SMPR1_SMP4_Pos)         /*!< 0x00001000 */
#define ADC_SMPR1_SMP4_1                  (0x2U << ADC_SMPR1_SMP4_Pos)         /*!< 0x00002000 */
#define ADC_SMPR1_SMP4_2                  (0x4U << ADC_SMPR1_SMP4_Pos)         /*!< 0x00004000 */

#define ADC_SMPR1_SMP5_Pos                (15U)
#define ADC_SMPR1_SMP5_Msk                (0x7U << ADC_SMPR1_SMP5_Pos)         /*!< 0x00038000 */
#define ADC_SMPR1_SMP5                    ADC_SMPR1_SMP5_Msk                   /*!< ADC Channel 5 Sampling time selection  */
#define ADC_SMPR1_SMP5_0                  (0x1U << ADC_SMPR1_SMP5_Pos)         /*!< 0x00008000 */
#define ADC_SMPR1_SMP5_1                  (0x2U << ADC_SMPR1_SMP5_Pos)         /*!< 0x00010000 */
#define ADC_SMPR1_SMP5_2                  (0x4U << ADC_SMPR1_SMP5_Pos)         /*!< 0x00020000 */

#define ADC_SMPR1_SMP6_Pos                (18U)
#define ADC_SMPR1_SMP6_Msk                (0x7U << ADC_SMPR1_SMP6_Pos)         /*!< 0x001C0000 */
#define ADC_SMPR1_SMP6                    ADC_SMPR1_SMP6_Msk                   /*!< ADC Channel 6 Sampling time selection  */
#define ADC_SMPR1_SMP6_0                  (0x1U << ADC_SMPR1_SMP6_Pos)         /*!< 0x00040000 */
#define ADC_SMPR1_SMP6_1                  (0x2U << ADC_SMPR1_SMP6_Pos)         /*!< 0x00080000 */
#define ADC_SMPR1_SMP6_2                  (0x4U << ADC_SMPR1_SMP6_Pos)         /*!< 0x00100000 */

#define ADC_SMPR1_SMP7_Pos                (21U)
#define ADC_SMPR1_SMP7_Msk                (0x7U << ADC_SMPR1_SMP7_Pos)         /*!< 0x00E00000 */
#define ADC_SMPR1_SMP7                    ADC_SMPR1_SMP7_Msk                   /*!< ADC Channel 7 Sampling time selection  */
#define ADC_SMPR1_SMP7_0                  (0x1U << ADC_SMPR1_SMP7_Pos)         /*!< 0x00200000 */
#define ADC_SMPR1_SMP7_1                  (0x2U << ADC_SMPR1_SMP7_Pos)         /*!< 0x00400000 */
#define ADC_SMPR1_SMP7_2                  (0x4U << ADC_SMPR1_SMP7_Pos)         /*!< 0x00800000 */

#define ADC_SMPR1_SMP8_Pos                (24U)
#define ADC_SMPR1_SMP8_Msk                (0x7U << ADC_SMPR1_SMP8_Pos)         /*!< 0x07000000 */
#define ADC_SMPR1_SMP8                    ADC_SMPR1_SMP8_Msk                   /*!< ADC Channel 8 Sampling time selection  */
#define ADC_SMPR1_SMP8_0                  (0x1U << ADC_SMPR1_SMP8_Pos)         /*!< 0x01000000 */
#define ADC_SMPR1_SMP8_1                  (0x2U << ADC_SMPR1_SMP8_Pos)         /*!< 0x02000000 */
#define ADC_SMPR1_SMP8_2                  (0x4U << ADC_SMPR1_SMP8_Pos)         /*!< 0x04000000 */

#define ADC_SMPR1_SMP9_Pos                (27U)
#define ADC_SMPR1_SMP9_Msk                (0x7U << ADC_SMPR1_SMP9_Pos)         /*!< 0x38000000 */
#define ADC_SMPR1_SMP9                    ADC_SMPR1_SMP9_Msk                   /*!< ADC Channel 9 Sampling time selection  */
#define ADC_SMPR1_SMP9_0                  (0x1U << ADC_SMPR1_SMP9_Pos)         /*!< 0x08000000 */
#define ADC_SMPR1_SMP9_1                  (0x2U << ADC_SMPR1_SMP9_Pos)         /*!< 0x10000000 */
#define ADC_SMPR1_SMP9_2                  (0x4U << ADC_SMPR1_SMP9_Pos)         /*!< 0x20000000 */

/********************  Bit definition for ADC_SMPR2 register  ********************/
#define ADC_SMPR2_SMP10_Pos               (0U)
#define ADC_SMPR2_SMP10_Msk               (0x7U << ADC_SMPR2_SMP10_Pos)        /*!< 0x00000007 */
#define ADC_SMPR2_SMP10                   ADC_SMPR2_SMP10_Msk                  /*!< ADC Channel 10 Sampling time selection  */
#define ADC_SMPR2_SMP10_0                 (0x1U << ADC_SMPR2_SMP10_Pos)        /*!< 0x00000001 */
#define ADC_SMPR2_SMP10_1                 (0x2U << ADC_SMPR2_SMP10_Pos)        /*!< 0x00000002 */
#define ADC_SMPR2_SMP10_2                 (0x4U << ADC_SMPR2_SMP10_Pos)        /*!< 0x00000004 */

#define ADC_SMPR2_SMP11_Pos               (3U)
#define ADC_SMPR2_SMP11_Msk               (0x7U << ADC_SMPR2_SMP11_Pos)        /*!< 0x00000038 */
#define ADC_SMPR2_SMP11                   ADC_SMPR2_SMP11_Msk                  /*!< ADC Channel 11 Sampling time selection  */
#define ADC_SMPR2_SMP11_0                 (0x1U << ADC_SMPR2_SMP11_Pos)        /*!< 0x00000008 */
#define ADC_SMPR2_SMP11_1                 (0x2U << ADC_SMPR2_SMP11_Pos)        /*!< 0x00000010 */
#define ADC_SMPR2_SMP11_2                 (0x4U << ADC_SMPR2_SMP11_Pos)        /*!< 0x00000020 */

#define ADC_SMPR2_SMP12_Pos               (6U)
#define ADC_SMPR2_SMP12_Msk               (0x7U << ADC_SMPR2_SMP12_Pos)        /*!< 0x000001C0 */
#define ADC_SMPR2_SMP12                   ADC_SMPR2_SMP12_Msk                  /*!< ADC Channel 12 Sampling time selection  */
#define ADC_SMPR2_SMP12_0                 (0x1U << ADC_SMPR2_SMP12_Pos)        /*!< 0x00000040 */
#define ADC_SMPR2_SMP12_1                 (0x2U << ADC_SMPR2_SMP12_Pos)        /*!< 0x00000080 */
#define ADC_SMPR2_SMP12_2                 (0x4U << ADC_SMPR2_SMP12_Pos)        /*!< 0x00000100 */

#define ADC_SMPR2_SMP13_Pos               (9U)
#define ADC_SMPR2_SMP13_Msk               (0x7U << ADC_SMPR2_SMP13_Pos)        /*!< 0x00000E00 */
#define ADC_SMPR2_SMP13                   ADC_SMPR2_SMP13_Msk                  /*!< ADC Channel 13 Sampling time selection  */
#define ADC_SMPR2_SMP13_0                 (0x1U << ADC_SMPR2_SMP13_Pos)        /*!< 0x00000200 */
#define ADC_SMPR2_SMP13_1                 (0x2U << ADC_SMPR2_SMP13_Pos)        /*!< 0x00000400 */
#define ADC_SMPR2_SMP13_2                 (0x4U << ADC_SMPR2_SMP13_Pos)        /*!< 0x00000800 */

#define ADC_SMPR2_SMP14_Pos               (12U)
#define ADC_SMPR2_SMP14_Msk               (0x7U << ADC_SMPR2_SMP14_Pos)        /*!< 0x00007000 */
#define ADC_SMPR2_SMP14                   ADC_SMPR2_SMP14_Msk                  /*!< ADC Channel 14 Sampling time selection  */
#define ADC_SMPR2_SMP14_0                 (0x1U << ADC_SMPR2_SMP14_Pos)        /*!< 0x00001000 */
#define ADC_SMPR2_SMP14_1                 (0x2U << ADC_SMPR2_SMP14_Pos)        /*!< 0x00002000 */
#define ADC_SMPR2_SMP14_2                 (0x4U << ADC_SMPR2_SMP14_Pos)        /*!< 0x00004000 */

#define ADC_SMPR2_SMP15_Pos               (15U)
#define ADC_SMPR2_SMP15_Msk               (0x7U << ADC_SMPR2_SMP15_Pos)        /*!< 0x00038000 */
#define ADC_SMPR2_SMP15                   ADC_SMPR2_SMP15_Msk                  /*!< ADC Channel 15 Sampling time selection  */
#define ADC_SMPR2_SMP15_0                 (0x1U << ADC_SMPR2_SMP15_Pos)        /*!< 0x00008000 */
#define ADC_SMPR2_SMP15_1                 (0x2U << ADC_SMPR2_SMP15_Pos)        /*!< 0x00010000 */
#define ADC_SMPR2_SMP15_2                 (0x4U << ADC_SMPR2_SMP15_Pos)        /*!< 0x00020000 */

#define ADC_SMPR2_SMP16_Pos               (18U)
#define ADC_SMPR2_SMP16_Msk               (0x7U << ADC_SMPR2_SMP16_Pos)        /*!< 0x001C0000 */
#define ADC_SMPR2_SMP16                   ADC_SMPR2_SMP16_Msk                  /*!< ADC Channel 16 Sampling time selection  */
#define ADC_SMPR2_SMP16_0                 (0x1U << ADC_SMPR2_SMP16_Pos)        /*!< 0x00040000 */
#define ADC_SMPR2_SMP16_1                 (0x2U << ADC_SMPR2_SMP16_Pos)        /*!< 0x00080000 */
#define ADC_SMPR2_SMP16_2                 (0x4U << ADC_SMPR2_SMP16_Pos)        /*!< 0x00100000 */

#define ADC_SMPR2_SMP17_Pos               (21U)
#define ADC_SMPR2_SMP17_Msk               (0x7U << ADC_SMPR2_SMP17_Pos)        /*!< 0x00E00000 */
#define ADC_SMPR2_SMP17                   ADC_SMPR2_SMP17_Msk                  /*!< ADC Channel 17 Sampling time selection  */
#define ADC_SMPR2_SMP17_0                 (0x1U << ADC_SMPR2_SMP17_Pos)        /*!< 0x00200000 */
#define ADC_SMPR2_SMP17_1                 (0x2U << ADC_SMPR2_SMP17_Pos)        /*!< 0x00400000 */
#define ADC_SMPR2_SMP17_2                 (0x4U << ADC_SMPR2_SMP17_Pos)        /*!< 0x00800000 */

#define ADC_SMPR2_SMP18_Pos               (24U)
#define ADC_SMPR2_SMP18_Msk               (0x7U << ADC_SMPR2_SMP18_Pos)        /*!< 0x07000000 */
#define ADC_SMPR2_SMP18                   ADC_SMPR2_SMP18_Msk                  /*!< ADC Channel 18 Sampling time selection  */
#define ADC_SMPR2_SMP18_0                 (0x1U << ADC_SMPR2_SMP18_Pos)        /*!< 0x01000000 */
#define ADC_SMPR2_SMP18_1                 (0x2U << ADC_SMPR2_SMP18_Pos)        /*!< 0x02000000 */
#define ADC_SMPR2_SMP18_2                 (0x4U << ADC_SMPR2_SMP18_Pos)        /*!< 0x04000000 */

#define ADC_SMPR2_SMP19_Pos               (27U)
#define ADC_SMPR2_SMP19_Msk               (0x7U << ADC_SMPR2_SMP19_Pos)        /*!< 0x38000000 */
#define ADC_SMPR2_SMP19                   ADC_SMPR2_SMP19_Msk                  /*!< ADC Channel 19 Sampling time selection  */
#define ADC_SMPR2_SMP19_0                 (0x1U << ADC_SMPR2_SMP19_Pos)        /*!< 0x08000000 */
#define ADC_SMPR2_SMP19_1                 (0x2U << ADC_SMPR2_SMP19_Pos)        /*!< 0x10000000 */
#define ADC_SMPR2_SMP19_2                 (0x4U << ADC_SMPR2_SMP19_Pos)        /*!< 0x20000000 */

/********************  Bit definition for ADC_PCSEL register  ********************/
#define ADC_PCSEL_PCSEL_Pos               (0U)
#define ADC_PCSEL_PCSEL_Msk               (0xFFFFFU << ADC_PCSEL_PCSEL_Pos)    /*!< 0x000FFFFF */
#define ADC_PCSEL_PCSEL                   ADC_PCSEL_PCSEL_Msk                  /*!< ADC pre channel selection */
#define ADC_PCSEL_PCSEL_0                 (0x00001U << ADC_PCSEL_PCSEL_Pos)    /*!< 0x00000001 */
#define ADC_PCSEL_PCSEL_1                 (0x00002U << ADC_PCSEL_PCSEL_Pos)    /*!< 0x00000002 */
#define ADC_PCSEL_PCSEL_2                 (0x00004U << ADC_PCSEL_PCSEL_Pos)    /*!< 0x00000004 */
#define ADC_PCSEL_PCSEL_3                 (0x00008U << ADC_PCSEL_PCSEL_Pos)    /*!< 0x00000008 */
#define ADC_PCSEL_PCSEL_4                 (0x00010U << ADC_PCSEL_PCSEL_Pos)    /*!< 0x00000010 */
#define ADC_PCSEL_PCSEL_5                 (0x00020U << ADC_PCSEL_PCSEL_Pos)    /*!< 0x00000020 */
#define ADC_PCSEL_PCSEL_6                 (0x00040U << ADC_PCSEL_PCSEL_Pos)    /*!< 0x00000040 */
#define ADC_PCSEL_PCSEL_7                 (0x00080U << ADC_PCSEL_PCSEL_Pos)    /*!< 0x00000080 */
#define ADC_PCSEL_PCSEL_8                 (0x00100U << ADC_PCSEL_PCSEL_Pos)    /*!< 0x00000100 */
#define ADC_PCSEL_PCSEL_9                 (0x00200U << ADC_PCSEL_PCSEL_Pos)    /*!< 0x00000200 */
#define ADC_PCSEL_PCSEL_10                (0x00400U << ADC_PCSEL_PCSEL_Pos)    /*!< 0x00000400 */
#define ADC_PCSEL_PCSEL_11                (0x00800U << ADC_PCSEL_PCSEL_Pos)    /*!< 0x00000800 */
#define ADC_PCSEL_PCSEL_12                (0x01000U << ADC_PCSEL_PCSEL_Pos)    /*!< 0x00001000 */
#define ADC_PCSEL_PCSEL_13                (0x02000U << ADC_PCSEL_PCSEL_Pos)    /*!< 0x00002000 */
#define ADC_PCSEL_PCSEL_14                (0x04000U << ADC_PCSEL_PCSEL_Pos)    /*!< 0x00004000 */
#define ADC_PCSEL_PCSEL_15                (0x08000U << ADC_PCSEL_PCSEL_Pos)    /*!< 0x00008000 */
#define ADC_PCSEL_PCSEL_16                (0x10000U << ADC_PCSEL_PCSEL_Pos)    /*!< 0x00010000 */
#define ADC_PCSEL_PCSEL_17                (0x20000U << ADC_PCSEL_PCSEL_Pos)    /*!< 0x00020000 */
#define ADC_PCSEL_PCSEL_18                (0x40000U << ADC_PCSEL_PCSEL_Pos)    /*!< 0x00040000 */
#define ADC_PCSEL_PCSEL_19                (0x80000U << ADC_PCSEL_PCSEL_Pos)    /*!< 0x00080000 */

/********************  Bit definition for ADC_LTR1 register  ********************/
#define ADC_LTR1_LT1_Pos                  (0U)
#define ADC_LTR1_LT1_Msk                  (0x3FFFFFFU << ADC_LTR1_LT1_Pos)     /*!< 0x03FFFFFF */
#define ADC_LTR1_LT1                      ADC_LTR1_LT1_Msk                     /*!< ADC Analog watchdog 1 lower threshold */
#define ADC_LTR1_LT1_0                    (0x0000001U << ADC_LTR1_LT1_Pos)     /*!< 0x00000001 */
#define ADC_LTR1_LT1_1                    (0x0000002U << ADC_LTR1_LT1_Pos)     /*!< 0x00000002 */
#define ADC_LTR1_LT1_2                    (0x0000004U << ADC_LTR1_LT1_Pos)     /*!< 0x00000004 */
#define ADC_LTR1_LT1_3                    (0x0000008U << ADC_LTR1_LT1_Pos)     /*!< 0x00000008 */
#define ADC_LTR1_LT1_4                    (0x0000010U << ADC_LTR1_LT1_Pos)     /*!< 0x00000010 */
#define ADC_LTR1_LT1_5                    (0x0000020U << ADC_LTR1_LT1_Pos)     /*!< 0x00000020 */
#define ADC_LTR1_LT1_6                    (0x0000040U << ADC_LTR1_LT1_Pos)     /*!< 0x00000040 */
#define ADC_LTR1_LT1_7                    (0x0000080U << ADC_LTR1_LT1_Pos)     /*!< 0x00000080 */
#define ADC_LTR1_LT1_8                    (0x0000100U << ADC_LTR1_LT1_Pos)     /*!< 0x00000100 */
#define ADC_LTR1_LT1_9                    (0x0000200U << ADC_LTR1_LT1_Pos)     /*!< 0x00000200 */
#define ADC_LTR1_LT1_10                   (0x0000400U << ADC_LTR1_LT1_Pos)     /*!< 0x00000400 */
#define ADC_LTR1_LT1_11                   (0x0000800U << ADC_LTR1_LT1_Pos)     /*!< 0x00000800 */
#define ADC_LTR1_LT1_12                   (0x0001000U << ADC_LTR1_LT1_Pos)     /*!< 0x00001000 */
#define ADC_LTR1_LT1_13                   (0x0002000U << ADC_LTR1_LT1_Pos)     /*!< 0x00002000 */
#define ADC_LTR1_LT1_14                   (0x0004000U << ADC_LTR1_LT1_Pos)     /*!< 0x00004000 */
#define ADC_LTR1_LT1_15                   (0x0008000U << ADC_LTR1_LT1_Pos)     /*!< 0x00008000 */
#define ADC_LTR1_LT1_16                   (0x0010000U << ADC_LTR1_LT1_Pos)     /*!< 0x00010000 */
#define ADC_LTR1_LT1_17                   (0x0020000U << ADC_LTR1_LT1_Pos)     /*!< 0x00020000 */
#define ADC_LTR1_LT1_18                   (0x0040000U << ADC_LTR1_LT1_Pos)     /*!< 0x00040000 */
#define ADC_LTR1_LT1_19                   (0x0080000U << ADC_LTR1_LT1_Pos)     /*!< 0x00080000 */
#define ADC_LTR1_LT1_20                   (0x0100000U << ADC_LTR1_LT1_Pos)     /*!< 0x00100000 */
#define ADC_LTR1_LT1_21                   (0x0200000U << ADC_LTR1_LT1_Pos)     /*!< 0x00200000 */
#define ADC_LTR1_LT1_22                   (0x0400000U << ADC_LTR1_LT1_Pos)     /*!< 0x00400000 */
#define ADC_LTR1_LT1_23                   (0x0800000U << ADC_LTR1_LT1_Pos)     /*!< 0x00800000 */
#define ADC_LTR1_LT1_24                   (0x1000000U << ADC_LTR1_LT1_Pos)     /*!< 0x01000000 */
#define ADC_LTR1_LT1_25                   (0x2000000U << ADC_LTR1_LT1_Pos)     /*!< 0x02000000 */

/********************  Bit definition for ADC_HTR1 register  ********************/
#define ADC_HTR1_HT1         ((uint32_t) 0x03FFFFFF) /*!< ADC Analog watchdog 1 higher threshold */
#define ADC_HTR1_HT1_0                    ((uint32_t)0x00000001)               /*!< ADC HT1 bit 0 */
#define ADC_HTR1_HT1_1                    ((uint32_t)0x00000002)               /*!< ADC HT1 bit 1 */
#define ADC_HTR1_HT1_2                    ((uint32_t)0x00000004)               /*!< ADC HT1 bit 2 */
#define ADC_HTR1_HT1_3                    ((uint32_t)0x00000008)               /*!< ADC HT1 bit 3 */
#define ADC_HTR1_HT1_4                    ((uint32_t)0x00000010)               /*!< ADC HT1 bit 4 */
#define ADC_HTR1_HT1_5                    ((uint32_t)0x00000020)               /*!< ADC HT1 bit 5 */
#define ADC_HTR1_HT1_6                    ((uint32_t)0x00000040)               /*!< ADC HT1 bit 6 */
#define ADC_HTR1_HT1_7                    ((uint32_t)0x00000080)               /*!< ADC HT1 bit 7 */
#define ADC_HTR1_HT1_8                    ((uint32_t)0x00000100)               /*!< ADC HT1 bit 8 */
#define ADC_HTR1_HT1_9                    ((uint32_t)0x00000200)               /*!< ADC HT1 bit 9 */
#define ADC_HTR1_HT1_10                   ((uint32_t)0x00000400)               /*!< ADC HT1 bit 10 */
#define ADC_HTR1_HT1_11                   ((uint32_t)0x00000800)               /*!< ADC HT1 bit 11 */
#define ADC_HTR1_HT1_12                   ((uint32_t)0x00001000)               /*!< ADC HT1 bit 12 */
#define ADC_HTR1_HT1_13                   ((uint32_t)0x00002000)               /*!< ADC HT1 bit 13 */
#define ADC_HTR1_HT1_14                   ((uint32_t)0x00004000)               /*!< ADC HT1 bit 14 */
#define ADC_HTR1_HT1_15                   ((uint32_t)0x00008000)               /*!< ADC HT1 bit 15 */
#define ADC_HTR1_HT1_16                   ((uint32_t)0x00010000)               /*!< ADC HT1 bit 16 */
#define ADC_HTR1_HT1_17                   ((uint32_t)0x00020000)               /*!< ADC HT1 bit 17 */
#define ADC_HTR1_HT1_18                   ((uint32_t)0x00040000)               /*!< ADC HT1 bit 18 */
#define ADC_HTR1_HT1_19                   ((uint32_t)0x00080000)               /*!< ADC HT1 bit 19 */
#define ADC_HTR1_HT1_20                   ((uint32_t)0x00100000)               /*!< ADC HT1 bit 20 */
#define ADC_HTR1_HT1_21                   ((uint32_t)0x00200000)               /*!< ADC HT1 bit 21 */
#define ADC_HTR1_HT1_22                   ((uint32_t)0x00400000)               /*!< ADC HT1 bit 22 */
#define ADC_HTR1_HT1_23                   ((uint32_t)0x00800000)               /*!< ADC HT1 bit 23 */
#define ADC_HTR1_HT1_24                   ((uint32_t)0x01000000)               /*!< ADC HT1 bit 24 */
#define ADC_HTR1_HT1_25                   ((uint32_t)0x02000000)               /*!< ADC HT1 bit 25 */


/********************  Bit definition for ADC_LTR2 register  ********************/
#define ADC_LTR2_LT2         ((uint32_t) 0x03FFFFFF) /*!< ADC Analog watchdog 2 lower threshold */
#define ADC_LTR2_LT2_0                    ((uint32_t)0x00000001)               /*!< ADC LT2 bit 0 */
#define ADC_LTR2_LT2_1                    ((uint32_t)0x00000002)               /*!< ADC LT2 bit 1 */
#define ADC_LTR2_LT2_2                    ((uint32_t)0x00000004)               /*!< ADC LT2 bit 2 */
#define ADC_LTR2_LT2_3                    ((uint32_t)0x00000008)               /*!< ADC LT2 bit 3 */
#define ADC_LTR2_LT2_4                    ((uint32_t)0x00000010)               /*!< ADC LT2 bit 4 */
#define ADC_LTR2_LT2_5                    ((uint32_t)0x00000020)               /*!< ADC LT2 bit 5 */
#define ADC_LTR2_LT2_6                    ((uint32_t)0x00000040)               /*!< ADC LT2 bit 6 */
#define ADC_LTR2_LT2_7                    ((uint32_t)0x00000080)               /*!< ADC LT2 bit 7 */
#define ADC_LTR2_LT2_8                    ((uint32_t)0x00000100)               /*!< ADC LT2 bit 8 */
#define ADC_LTR2_LT2_9                    ((uint32_t)0x00000200)               /*!< ADC LT2 bit 9 */
#define ADC_LTR2_LT2_10                   ((uint32_t)0x00000400)               /*!< ADC LT2 bit 10 */
#define ADC_LTR2_LT2_11                   ((uint32_t)0x00000800)               /*!< ADC LT2 bit 11 */
#define ADC_LTR2_LT2_12                   ((uint32_t)0x00001000)               /*!< ADC LT2 bit 12 */
#define ADC_LTR2_LT2_13                   ((uint32_t)0x00002000)               /*!< ADC LT2 bit 13 */
#define ADC_LTR2_LT2_14                   ((uint32_t)0x00004000)               /*!< ADC LT2 bit 14 */
#define ADC_LTR2_LT2_15                   ((uint32_t)0x00008000)               /*!< ADC LT2 bit 15 */
#define ADC_LTR2_LT2_16                   ((uint32_t)0x00010000)               /*!< ADC LT2 bit 16 */
#define ADC_LTR2_LT2_17                   ((uint32_t)0x00020000)               /*!< ADC LT2 bit 17 */
#define ADC_LTR2_LT2_18                   ((uint32_t)0x00040000)               /*!< ADC LT2 bit 18 */
#define ADC_LTR2_LT2_19                   ((uint32_t)0x00080000)               /*!< ADC LT2 bit 19 */
#define ADC_LTR2_LT2_20                   ((uint32_t)0x00100000)               /*!< ADC LT2 bit 20 */
#define ADC_LTR2_LT2_21                   ((uint32_t)0x00200000)               /*!< ADC LT2 bit 21 */
#define ADC_LTR2_LT2_22                   ((uint32_t)0x00400000)               /*!< ADC LT2 bit 22 */
#define ADC_LTR2_LT2_23                   ((uint32_t)0x00800000)               /*!< ADC LT2 bit 23 */
#define ADC_LTR2_LT2_24                   ((uint32_t)0x01000000)               /*!< ADC LT2 bit 24 */
#define ADC_LTR2_LT2_25                   ((uint32_t)0x02000000)               /*!< ADC LT2 bit 25 */

/********************  Bit definition for ADC_HTR2 register  ********************/
#define ADC_HTR2_HT2         ((uint32_t) 0x03FFFFFF) /*!< ADC Analog watchdog 2 higher threshold */
#define ADC_HTR2_HT2_0                    ((uint32_t)0x00000001)               /*!< ADC HT2 bit 0 */
#define ADC_HTR2_HT2_1                    ((uint32_t)0x00000002)               /*!< ADC HT2 bit 1 */
#define ADC_HTR2_HT2_2                    ((uint32_t)0x00000004)               /*!< ADC HT2 bit 2 */
#define ADC_HTR2_HT2_3                    ((uint32_t)0x00000008)               /*!< ADC HT2 bit 3 */
#define ADC_HTR2_HT2_4                    ((uint32_t)0x00000010)               /*!< ADC HT2 bit 4 */
#define ADC_HTR2_HT2_5                    ((uint32_t)0x00000020)               /*!< ADC HT2 bit 5 */
#define ADC_HTR2_HT2_6                    ((uint32_t)0x00000040)               /*!< ADC HT2 bit 6 */
#define ADC_HTR2_HT2_7                    ((uint32_t)0x00000080)               /*!< ADC HT2 bit 7 */
#define ADC_HTR2_HT2_8                    ((uint32_t)0x00000100)               /*!< ADC HT2 bit 8 */
#define ADC_HTR2_HT2_9                    ((uint32_t)0x00000200)               /*!< ADC HT2 bit 9 */
#define ADC_HTR2_HT2_10                   ((uint32_t)0x00000400)               /*!< ADC HT2 bit 10 */
#define ADC_HTR2_HT2_11                   ((uint32_t)0x00000800)               /*!< ADC HT2 bit 11 */
#define ADC_HTR2_HT2_12                   ((uint32_t)0x00001000)               /*!< ADC HT2 bit 12 */
#define ADC_HTR2_HT2_13                   ((uint32_t)0x00002000)               /*!< ADC HT2 bit 13 */
#define ADC_HTR2_HT2_14                   ((uint32_t)0x00004000)               /*!< ADC HT2 bit 14 */
#define ADC_HTR2_HT2_15                   ((uint32_t)0x00008000)               /*!< ADC HT2 bit 15 */
#define ADC_HTR2_HT2_16                   ((uint32_t)0x00010000)               /*!< ADC HT2 bit 16 */
#define ADC_HTR2_HT2_17                   ((uint32_t)0x00020000)               /*!< ADC HT2 bit 17 */
#define ADC_HTR2_HT2_18                   ((uint32_t)0x00040000)               /*!< ADC HT2 bit 18 */
#define ADC_HTR2_HT2_19                   ((uint32_t)0x00080000)               /*!< ADC HT2 bit 19 */
#define ADC_HTR2_HT2_20                   ((uint32_t)0x00100000)               /*!< ADC HT2 bit 20 */
#define ADC_HTR2_HT2_21                   ((uint32_t)0x00200000)               /*!< ADC HT2 bit 21 */
#define ADC_HTR2_HT2_22                   ((uint32_t)0x00400000)               /*!< ADC HT2 bit 22 */
#define ADC_HTR2_HT2_23                   ((uint32_t)0x00800000)               /*!< ADC HT2 bit 23 */
#define ADC_HTR2_HT2_24                   ((uint32_t)0x01000000)               /*!< ADC HT2 bit 24 */
#define ADC_HTR2_HT2_25      ((uint32_t)0x020000000) /*!< ADC HT2 bit 25 */

/********************  Bit definition for ADC_LTR3 register  ********************/
#define ADC_LTR3_LT3         ((uint32_t) 0x03FFFFFF) /*!< ADC Analog watchdog 3 lower threshold */
#define ADC_LTR3_LT3_0                    ((uint32_t)0x00000001)               /*!< ADC LT3 bit 0 */
#define ADC_LTR3_LT3_1                    ((uint32_t)0x00000002)               /*!< ADC LT3 bit 1 */
#define ADC_LTR3_LT3_2                    ((uint32_t)0x00000004)               /*!< ADC LT3 bit 2 */
#define ADC_LTR3_LT3_3                    ((uint32_t)0x00000008)               /*!< ADC LT3 bit 3 */
#define ADC_LTR3_LT3_4                    ((uint32_t)0x00000010)               /*!< ADC LT3 bit 4 */
#define ADC_LTR3_LT3_5                    ((uint32_t)0x00000020)               /*!< ADC LT3 bit 5 */
#define ADC_LTR3_LT3_6                    ((uint32_t)0x00000040)               /*!< ADC LT3 bit 6 */
#define ADC_LTR3_LT3_7                    ((uint32_t)0x00000080)               /*!< ADC LT3 bit 7 */
#define ADC_LTR3_LT3_8                    ((uint32_t)0x00000100)               /*!< ADC LT3 bit 8 */
#define ADC_LTR3_LT3_9                    ((uint32_t)0x00000200)               /*!< ADC LT3 bit 9 */
#define ADC_LTR3_LT3_10                   ((uint32_t)0x00000400)               /*!< ADC LT3 bit 10 */
#define ADC_LTR3_LT3_11                   ((uint32_t)0x00000800)               /*!< ADC LT3 bit 11 */
#define ADC_LTR3_LT3_12                   ((uint32_t)0x00001000)               /*!< ADC LT3 bit 12 */
#define ADC_LTR3_LT3_13                   ((uint32_t)0x00002000)               /*!< ADC LT3 bit 13 */
#define ADC_LTR3_LT3_14                   ((uint32_t)0x00004000)               /*!< ADC LT3 bit 14 */
#define ADC_LTR3_LT3_15                   ((uint32_t)0x00008000)               /*!< ADC LT3 bit 15 */
#define ADC_LTR3_LT3_16                   ((uint32_t)0x00010000)               /*!< ADC LT3 bit 16 */
#define ADC_LTR3_LT3_17                   ((uint32_t)0x00020000)               /*!< ADC LT3 bit 17 */
#define ADC_LTR3_LT3_18                   ((uint32_t)0x00040000)               /*!< ADC LT3 bit 18 */
#define ADC_LTR3_LT3_19                   ((uint32_t)0x00080000)               /*!< ADC LT3 bit 19 */
#define ADC_LTR3_LT3_20                   ((uint32_t)0x00100000)               /*!< ADC LT3 bit 20 */
#define ADC_LTR3_LT3_21                   ((uint32_t)0x00200000)               /*!< ADC LT3 bit 21 */
#define ADC_LTR3_LT3_22                   ((uint32_t)0x00400000)               /*!< ADC LT3 bit 22 */
#define ADC_LTR3_LT3_23                   ((uint32_t)0x00800000)               /*!< ADC LT3 bit 23 */
#define ADC_LTR3_LT3_24                   ((uint32_t)0x01000000)               /*!< ADC LT3 bit 24*/
#define ADC_LTR3_LT3_25                   ((uint32_t)0x02000000)               /*!< ADC LT3 bit 25 */

/********************  Bit definition for ADC_HTR3 register  ********************/
#define ADC_HTR3_HT3         ((uint32_t) 0x03FFFFFF) /*!< ADC Analog watchdog 3 higher threshold */
#define ADC_HTR3_HT3_0                    ((uint32_t)0x00000001)               /*!< ADC HT3 bit 0 */
#define ADC_HTR3_HT3_1                    ((uint32_t)0x00000002)               /*!< ADC HT3 bit 1 */
#define ADC_HTR3_HT3_2                    ((uint32_t)0x00000004)               /*!< ADC HT3 bit 2 */
#define ADC_HTR3_HT3_3                    ((uint32_t)0x00000008)               /*!< ADC HT3 bit 3 */
#define ADC_HTR3_HT3_4                    ((uint32_t)0x00000010)               /*!< ADC HT3 bit 4 */
#define ADC_HTR3_HT3_5                    ((uint32_t)0x00000020)               /*!< ADC HT3 bit 5 */
#define ADC_HTR3_HT3_6                    ((uint32_t)0x00000040)               /*!< ADC HT3 bit 6 */
#define ADC_HTR3_HT3_7                    ((uint32_t)0x00000080)               /*!< ADC HT3 bit 7 */
#define ADC_HTR3_HT3_8                    ((uint32_t)0x00000100)               /*!< ADC HT3 bit 8 */
#define ADC_HTR3_HT3_9                    ((uint32_t)0x00000200)               /*!< ADC HT3 bit 9 */
#define ADC_HTR3_HT3_10                   ((uint32_t)0x00000400)               /*!< ADC HT3 bit 10 */
#define ADC_HTR3_HT3_11                   ((uint32_t)0x00000800)               /*!< ADC HT3 bit 11 */
#define ADC_HTR3_HT3_12                   ((uint32_t)0x00001000)               /*!< ADC HT3 bit 12 */
#define ADC_HTR3_HT3_13                   ((uint32_t)0x00002000)               /*!< ADC HT3 bit 13 */
#define ADC_HTR3_HT3_14                   ((uint32_t)0x00004000)               /*!< ADC HT3 bit 14 */
#define ADC_HTR3_HT3_15                   ((uint32_t)0x00008000)               /*!< ADC HT3 bit 15 */
#define ADC_HTR3_HT3_16                   ((uint32_t)0x00010000)               /*!< ADC HT3 bit 16 */
#define ADC_HTR3_HT3_17                   ((uint32_t)0x00020000)               /*!< ADC HT3 bit 17 */
#define ADC_HTR3_HT3_18                   ((uint32_t)0x00040000)               /*!< ADC HT3 bit 18 */
#define ADC_HTR3_HT3_19                   ((uint32_t)0x00080000)               /*!< ADC HT3 bit 19 */
#define ADC_HTR3_HT3_20                   ((uint32_t)0x00100000)               /*!< ADC HT3 bit 20 */
#define ADC_HTR3_HT3_21                   ((uint32_t)0x00200000)               /*!< ADC HT3 bit 21 */
#define ADC_HTR3_HT3_22                   ((uint32_t)0x00400000)               /*!< ADC HT3 bit 22 */
#define ADC_HTR3_HT3_23                   ((uint32_t)0x00800000)               /*!< ADC HT3 bit 23 */
#define ADC_HTR3_HT3_24                   ((uint32_t)0x01000000)               /*!< ADC HT3 bit 24 */
#define ADC_HTR3_HT3_25                   ((uint32_t)0x02000000)               /*!< ADC HT3 bit 25 */

/********************  Bit definition for ADC_SQR1 register  ********************/
#define ADC_SQR1_L_Pos                    (0U)
#define ADC_SQR1_L_Msk                    (0xFU << ADC_SQR1_L_Pos)             /*!< 0x0000000F */
#define ADC_SQR1_L                        ADC_SQR1_L_Msk                       /*!< ADC regular channel sequence lenght */
#define ADC_SQR1_L_0                      (0x1U << ADC_SQR1_L_Pos)             /*!< 0x00000001 */
#define ADC_SQR1_L_1                      (0x2U << ADC_SQR1_L_Pos)             /*!< 0x00000002 */
#define ADC_SQR1_L_2                      (0x4U << ADC_SQR1_L_Pos)             /*!< 0x00000004 */
#define ADC_SQR1_L_3                      (0x8U << ADC_SQR1_L_Pos)             /*!< 0x00000008 */

#define ADC_SQR1_SQ1_Pos                  (6U)
#define ADC_SQR1_SQ1_Msk                  (0x1FU << ADC_SQR1_SQ1_Pos)          /*!< 0x000007C0 */
#define ADC_SQR1_SQ1                      ADC_SQR1_SQ1_Msk                     /*!< ADC 1st conversion in regular sequence */
#define ADC_SQR1_SQ1_0                    (0x01U << ADC_SQR1_SQ1_Pos)          /*!< 0x00000040 */
#define ADC_SQR1_SQ1_1                    (0x02U << ADC_SQR1_SQ1_Pos)          /*!< 0x00000080 */
#define ADC_SQR1_SQ1_2                    (0x04U << ADC_SQR1_SQ1_Pos)          /*!< 0x00000100 */
#define ADC_SQR1_SQ1_3                    (0x08U << ADC_SQR1_SQ1_Pos)          /*!< 0x00000200 */
#define ADC_SQR1_SQ1_4                    (0x10U << ADC_SQR1_SQ1_Pos)          /*!< 0x00000400 */

#define ADC_SQR1_SQ2_Pos                  (12U)
#define ADC_SQR1_SQ2_Msk                  (0x1FU << ADC_SQR1_SQ2_Pos)          /*!< 0x0001F000 */
#define ADC_SQR1_SQ2                      ADC_SQR1_SQ2_Msk                     /*!< ADC 2nd conversion in regular sequence */
#define ADC_SQR1_SQ2_0                    (0x01U << ADC_SQR1_SQ2_Pos)          /*!< 0x00001000 */
#define ADC_SQR1_SQ2_1                    (0x02U << ADC_SQR1_SQ2_Pos)          /*!< 0x00002000 */
#define ADC_SQR1_SQ2_2                    (0x04U << ADC_SQR1_SQ2_Pos)          /*!< 0x00004000 */
#define ADC_SQR1_SQ2_3                    (0x08U << ADC_SQR1_SQ2_Pos)          /*!< 0x00008000 */
#define ADC_SQR1_SQ2_4                    (0x10U << ADC_SQR1_SQ2_Pos)          /*!< 0x00010000 */

#define ADC_SQR1_SQ3_Pos                  (18U)
#define ADC_SQR1_SQ3_Msk                  (0x1FU << ADC_SQR1_SQ3_Pos)          /*!< 0x007C0000 */
#define ADC_SQR1_SQ3                      ADC_SQR1_SQ3_Msk                     /*!< ADC 3rd conversion in regular sequence */
#define ADC_SQR1_SQ3_0                    (0x01U << ADC_SQR1_SQ3_Pos)          /*!< 0x00040000 */
#define ADC_SQR1_SQ3_1                    (0x02U << ADC_SQR1_SQ3_Pos)          /*!< 0x00080000 */
#define ADC_SQR1_SQ3_2                    (0x04U << ADC_SQR1_SQ3_Pos)          /*!< 0x00100000 */
#define ADC_SQR1_SQ3_3                    (0x08U << ADC_SQR1_SQ3_Pos)          /*!< 0x00200000 */
#define ADC_SQR1_SQ3_4                    (0x10U << ADC_SQR1_SQ3_Pos)          /*!< 0x00400000 */

#define ADC_SQR1_SQ4_Pos                  (24U)
#define ADC_SQR1_SQ4_Msk                  (0x1FU << ADC_SQR1_SQ4_Pos)          /*!< 0x1F000000 */
#define ADC_SQR1_SQ4                      ADC_SQR1_SQ4_Msk                     /*!< ADC 4th conversion in regular sequence */
#define ADC_SQR1_SQ4_0                    (0x01U << ADC_SQR1_SQ4_Pos)          /*!< 0x01000000 */
#define ADC_SQR1_SQ4_1                    (0x02U << ADC_SQR1_SQ4_Pos)          /*!< 0x02000000 */
#define ADC_SQR1_SQ4_2                    (0x04U << ADC_SQR1_SQ4_Pos)          /*!< 0x04000000 */
#define ADC_SQR1_SQ4_3                    (0x08U << ADC_SQR1_SQ4_Pos)          /*!< 0x08000000 */
#define ADC_SQR1_SQ4_4                    (0x10U << ADC_SQR1_SQ4_Pos)          /*!< 0x10000000 */

/********************  Bit definition for ADC_SQR2 register  ********************/
#define ADC_SQR2_SQ5_Pos                  (0U)
#define ADC_SQR2_SQ5_Msk                  (0x1FU << ADC_SQR2_SQ5_Pos)          /*!< 0x0000001F */
#define ADC_SQR2_SQ5                      ADC_SQR2_SQ5_Msk                     /*!< ADC 5th conversion in regular sequence */
#define ADC_SQR2_SQ5_0                    (0x01U << ADC_SQR2_SQ5_Pos)          /*!< 0x00000001 */
#define ADC_SQR2_SQ5_1                    (0x02U << ADC_SQR2_SQ5_Pos)          /*!< 0x00000002 */
#define ADC_SQR2_SQ5_2                    (0x04U << ADC_SQR2_SQ5_Pos)          /*!< 0x00000004 */
#define ADC_SQR2_SQ5_3                    (0x08U << ADC_SQR2_SQ5_Pos)          /*!< 0x00000008 */
#define ADC_SQR2_SQ5_4                    (0x10U << ADC_SQR2_SQ5_Pos)          /*!< 0x00000010 */

#define ADC_SQR2_SQ6_Pos                  (6U)
#define ADC_SQR2_SQ6_Msk                  (0x1FU << ADC_SQR2_SQ6_Pos)          /*!< 0x000007C0 */
#define ADC_SQR2_SQ6                      ADC_SQR2_SQ6_Msk                     /*!< ADC 6th conversion in regular sequence */
#define ADC_SQR2_SQ6_0                    (0x01U << ADC_SQR2_SQ6_Pos)          /*!< 0x00000040 */
#define ADC_SQR2_SQ6_1                    (0x02U << ADC_SQR2_SQ6_Pos)          /*!< 0x00000080 */
#define ADC_SQR2_SQ6_2                    (0x04U << ADC_SQR2_SQ6_Pos)          /*!< 0x00000100 */
#define ADC_SQR2_SQ6_3                    (0x08U << ADC_SQR2_SQ6_Pos)          /*!< 0x00000200 */
#define ADC_SQR2_SQ6_4                    (0x10U << ADC_SQR2_SQ6_Pos)          /*!< 0x00000400 */

#define ADC_SQR2_SQ7_Pos                  (12U)
#define ADC_SQR2_SQ7_Msk                  (0x1FU << ADC_SQR2_SQ7_Pos)          /*!< 0x0001F000 */
#define ADC_SQR2_SQ7                      ADC_SQR2_SQ7_Msk                     /*!< ADC 7th conversion in regular sequence */
#define ADC_SQR2_SQ7_0                    (0x01U << ADC_SQR2_SQ7_Pos)          /*!< 0x00001000 */
#define ADC_SQR2_SQ7_1                    (0x02U << ADC_SQR2_SQ7_Pos)          /*!< 0x00002000 */
#define ADC_SQR2_SQ7_2                    (0x04U << ADC_SQR2_SQ7_Pos)          /*!< 0x00004000 */
#define ADC_SQR2_SQ7_3                    (0x08U << ADC_SQR2_SQ7_Pos)          /*!< 0x00008000 */
#define ADC_SQR2_SQ7_4                    (0x10U << ADC_SQR2_SQ7_Pos)          /*!< 0x00010000 */

#define ADC_SQR2_SQ8_Pos                  (18U)
#define ADC_SQR2_SQ8_Msk                  (0x1FU << ADC_SQR2_SQ8_Pos)          /*!< 0x007C0000 */
#define ADC_SQR2_SQ8                      ADC_SQR2_SQ8_Msk                     /*!< ADC 8th conversion in regular sequence */
#define ADC_SQR2_SQ8_0                    (0x01U << ADC_SQR2_SQ8_Pos)          /*!< 0x00040000 */
#define ADC_SQR2_SQ8_1                    (0x02U << ADC_SQR2_SQ8_Pos)          /*!< 0x00080000 */
#define ADC_SQR2_SQ8_2                    (0x04U << ADC_SQR2_SQ8_Pos)          /*!< 0x00100000 */
#define ADC_SQR2_SQ8_3                    (0x08U << ADC_SQR2_SQ8_Pos)          /*!< 0x00200000 */
#define ADC_SQR2_SQ8_4                    (0x10U << ADC_SQR2_SQ8_Pos)          /*!< 0x00400000 */

#define ADC_SQR2_SQ9_Pos                  (24U)
#define ADC_SQR2_SQ9_Msk                  (0x1FU << ADC_SQR2_SQ9_Pos)          /*!< 0x1F000000 */
#define ADC_SQR2_SQ9                      ADC_SQR2_SQ9_Msk                     /*!< ADC 9th conversion in regular sequence */
#define ADC_SQR2_SQ9_0                    (0x01U << ADC_SQR2_SQ9_Pos)          /*!< 0x01000000 */
#define ADC_SQR2_SQ9_1                    (0x02U << ADC_SQR2_SQ9_Pos)          /*!< 0x02000000 */
#define ADC_SQR2_SQ9_2                    (0x04U << ADC_SQR2_SQ9_Pos)          /*!< 0x04000000 */
#define ADC_SQR2_SQ9_3                    (0x08U << ADC_SQR2_SQ9_Pos)          /*!< 0x08000000 */
#define ADC_SQR2_SQ9_4                    (0x10U << ADC_SQR2_SQ9_Pos)          /*!< 0x10000000 */

/********************  Bit definition for ADC_SQR3 register  ********************/
#define ADC_SQR3_SQ10_Pos                 (0U)
#define ADC_SQR3_SQ10_Msk                 (0x1FU << ADC_SQR3_SQ10_Pos)         /*!< 0x0000001F */
#define ADC_SQR3_SQ10                     ADC_SQR3_SQ10_Msk                    /*!< ADC 10th conversion in regular sequence */
#define ADC_SQR3_SQ10_0                   (0x01U << ADC_SQR3_SQ10_Pos)         /*!< 0x00000001 */
#define ADC_SQR3_SQ10_1                   (0x02U << ADC_SQR3_SQ10_Pos)         /*!< 0x00000002 */
#define ADC_SQR3_SQ10_2                   (0x04U << ADC_SQR3_SQ10_Pos)         /*!< 0x00000004 */
#define ADC_SQR3_SQ10_3                   (0x08U << ADC_SQR3_SQ10_Pos)         /*!< 0x00000008 */
#define ADC_SQR3_SQ10_4                   (0x10U << ADC_SQR3_SQ10_Pos)         /*!< 0x00000010 */

#define ADC_SQR3_SQ11_Pos                 (6U)
#define ADC_SQR3_SQ11_Msk                 (0x1FU << ADC_SQR3_SQ11_Pos)         /*!< 0x000007C0 */
#define ADC_SQR3_SQ11                     ADC_SQR3_SQ11_Msk                    /*!< ADC 11th conversion in regular sequence */
#define ADC_SQR3_SQ11_0                   (0x01U << ADC_SQR3_SQ11_Pos)         /*!< 0x00000040 */
#define ADC_SQR3_SQ11_1                   (0x02U << ADC_SQR3_SQ11_Pos)         /*!< 0x00000080 */
#define ADC_SQR3_SQ11_2                   (0x04U << ADC_SQR3_SQ11_Pos)         /*!< 0x00000100 */
#define ADC_SQR3_SQ11_3                   (0x08U << ADC_SQR3_SQ11_Pos)         /*!< 0x00000200 */
#define ADC_SQR3_SQ11_4                   (0x10U << ADC_SQR3_SQ11_Pos)         /*!< 0x00000400 */

#define ADC_SQR3_SQ12_Pos                 (12U)
#define ADC_SQR3_SQ12_Msk                 (0x1FU << ADC_SQR3_SQ12_Pos)         /*!< 0x0001F000 */
#define ADC_SQR3_SQ12                     ADC_SQR3_SQ12_Msk                    /*!< ADC 12th conversion in regular sequence */
#define ADC_SQR3_SQ12_0                   (0x01U << ADC_SQR3_SQ12_Pos)         /*!< 0x00001000 */
#define ADC_SQR3_SQ12_1                   (0x02U << ADC_SQR3_SQ12_Pos)         /*!< 0x00002000 */
#define ADC_SQR3_SQ12_2                   (0x04U << ADC_SQR3_SQ12_Pos)         /*!< 0x00004000 */
#define ADC_SQR3_SQ12_3                   (0x08U << ADC_SQR3_SQ12_Pos)         /*!< 0x00008000 */
#define ADC_SQR3_SQ12_4                   (0x10U << ADC_SQR3_SQ12_Pos)         /*!< 0x00010000 */

#define ADC_SQR3_SQ13_Pos                 (18U)
#define ADC_SQR3_SQ13_Msk                 (0x1FU << ADC_SQR3_SQ13_Pos)         /*!< 0x007C0000 */
#define ADC_SQR3_SQ13                     ADC_SQR3_SQ13_Msk                    /*!< ADC 13th conversion in regular sequence */
#define ADC_SQR3_SQ13_0                   (0x01U << ADC_SQR3_SQ13_Pos)         /*!< 0x00040000 */
#define ADC_SQR3_SQ13_1                   (0x02U << ADC_SQR3_SQ13_Pos)         /*!< 0x00080000 */
#define ADC_SQR3_SQ13_2                   (0x04U << ADC_SQR3_SQ13_Pos)         /*!< 0x00100000 */
#define ADC_SQR3_SQ13_3                   (0x08U << ADC_SQR3_SQ13_Pos)         /*!< 0x00200000 */
#define ADC_SQR3_SQ13_4                   (0x10U << ADC_SQR3_SQ13_Pos)         /*!< 0x00400000 */

#define ADC_SQR3_SQ14_Pos                 (24U)
#define ADC_SQR3_SQ14_Msk                 (0x1FU << ADC_SQR3_SQ14_Pos)         /*!< 0x1F000000 */
#define ADC_SQR3_SQ14                     ADC_SQR3_SQ14_Msk                    /*!< ADC 14th conversion in regular sequence */
#define ADC_SQR3_SQ14_0                   (0x01U << ADC_SQR3_SQ14_Pos)         /*!< 0x01000000 */
#define ADC_SQR3_SQ14_1                   (0x02U << ADC_SQR3_SQ14_Pos)         /*!< 0x02000000 */
#define ADC_SQR3_SQ14_2                   (0x04U << ADC_SQR3_SQ14_Pos)         /*!< 0x04000000 */
#define ADC_SQR3_SQ14_3                   (0x08U << ADC_SQR3_SQ14_Pos)         /*!< 0x08000000 */
#define ADC_SQR3_SQ14_4                   (0x10U << ADC_SQR3_SQ14_Pos)         /*!< 0x10000000 */

/********************  Bit definition for ADC_SQR4 register  ********************/
#define ADC_SQR4_SQ15_Pos                 (0U)
#define ADC_SQR4_SQ15_Msk                 (0x1FU << ADC_SQR4_SQ15_Pos)         /*!< 0x0000001F */
#define ADC_SQR4_SQ15                     ADC_SQR4_SQ15_Msk                    /*!< ADC 15th conversion in regular sequence */
#define ADC_SQR4_SQ15_0                   (0x01U << ADC_SQR4_SQ15_Pos)         /*!< 0x00000001 */
#define ADC_SQR4_SQ15_1                   (0x02U << ADC_SQR4_SQ15_Pos)         /*!< 0x00000002 */
#define ADC_SQR4_SQ15_2                   (0x04U << ADC_SQR4_SQ15_Pos)         /*!< 0x00000004 */
#define ADC_SQR4_SQ15_3                   (0x08U << ADC_SQR4_SQ15_Pos)         /*!< 0x00000008 */
#define ADC_SQR4_SQ15_4                   (0x10U << ADC_SQR4_SQ15_Pos)         /*!< 0x00000010 */

#define ADC_SQR4_SQ16_Pos                 (6U)
#define ADC_SQR4_SQ16_Msk                 (0x1FU << ADC_SQR4_SQ16_Pos)         /*!< 0x000007C0 */
#define ADC_SQR4_SQ16                     ADC_SQR4_SQ16_Msk                    /*!< ADC 16th conversion in regular sequence */
#define ADC_SQR4_SQ16_0                   (0x01U << ADC_SQR4_SQ16_Pos)         /*!< 0x00000040 */
#define ADC_SQR4_SQ16_1                   (0x02U << ADC_SQR4_SQ16_Pos)         /*!< 0x00000080 */
#define ADC_SQR4_SQ16_2                   (0x04U << ADC_SQR4_SQ16_Pos)         /*!< 0x00000100 */
#define ADC_SQR4_SQ16_3                   (0x08U << ADC_SQR4_SQ16_Pos)         /*!< 0x00000200 */
#define ADC_SQR4_SQ16_4                   (0x10U << ADC_SQR4_SQ16_Pos)         /*!< 0x00000400 */
/********************  Bit definition for ADC_DR register  ********************/
#define ADC_DR_RDATA_Pos                  (0U)
#define ADC_DR_RDATA_Msk                  (0xFFFFFFFFU << ADC_DR_RDATA_Pos)    /*!< 0xFFFFFFFF */
#define ADC_DR_RDATA                      ADC_DR_RDATA_Msk                     /*!< ADC regular Data converted */
#define ADC_DR_RDATA_0                    (0x0001U << ADC_DR_RDATA_Pos)        /*!< 0x00000001 */
#define ADC_DR_RDATA_1                    (0x0002U << ADC_DR_RDATA_Pos)        /*!< 0x00000002 */
#define ADC_DR_RDATA_2                    (0x0004U << ADC_DR_RDATA_Pos)        /*!< 0x00000004 */
#define ADC_DR_RDATA_3                    (0x0008U << ADC_DR_RDATA_Pos)        /*!< 0x00000008 */
#define ADC_DR_RDATA_4                    (0x0010U << ADC_DR_RDATA_Pos)        /*!< 0x00000010 */
#define ADC_DR_RDATA_5                    (0x0020U << ADC_DR_RDATA_Pos)        /*!< 0x00000020 */
#define ADC_DR_RDATA_6                    (0x0040U << ADC_DR_RDATA_Pos)        /*!< 0x00000040 */
#define ADC_DR_RDATA_7                    (0x0080U << ADC_DR_RDATA_Pos)        /*!< 0x00000080 */
#define ADC_DR_RDATA_8                    (0x0100U << ADC_DR_RDATA_Pos)        /*!< 0x00000100 */
#define ADC_DR_RDATA_9                    (0x0200U << ADC_DR_RDATA_Pos)        /*!< 0x00000200 */
#define ADC_DR_RDATA_10                   (0x0400U << ADC_DR_RDATA_Pos)        /*!< 0x00000400 */
#define ADC_DR_RDATA_11                   (0x0800U << ADC_DR_RDATA_Pos)        /*!< 0x00000800 */
#define ADC_DR_RDATA_12                   (0x1000U << ADC_DR_RDATA_Pos)        /*!< 0x00001000 */
#define ADC_DR_RDATA_13                   (0x2000U << ADC_DR_RDATA_Pos)        /*!< 0x00002000 */
#define ADC_DR_RDATA_14                   (0x4000U << ADC_DR_RDATA_Pos)        /*!< 0x00004000 */
#define ADC_DR_RDATA_15                   (0x8000U << ADC_DR_RDATA_Pos)        /*!< 0x00008000 */
#define ADC_DR_RDATA_16                   (0x10000U << ADC_DR_RDATA_Pos)       /*!< 0x00010000 */
#define ADC_DR_RDATA_17                   (0x20000U << ADC_DR_RDATA_Pos)       /*!< 0x00020000 */
#define ADC_DR_RDATA_18                   (0x40000U << ADC_DR_RDATA_Pos)       /*!< 0x00040000 */
#define ADC_DR_RDATA_19                   (0x80000U << ADC_DR_RDATA_Pos)       /*!< 0x00080000 */
#define ADC_DR_RDATA_20                   (0x100000U << ADC_DR_RDATA_Pos)      /*!< 0x00100000 */
#define ADC_DR_RDATA_21                   (0x200000U << ADC_DR_RDATA_Pos)      /*!< 0x00200000 */
#define ADC_DR_RDATA_22                   (0x400000U << ADC_DR_RDATA_Pos)      /*!< 0x00400000 */
#define ADC_DR_RDATA_23                   (0x800000U << ADC_DR_RDATA_Pos)      /*!< 0x00800000 */
#define ADC_DR_RDATA_24                   (0x1000000U << ADC_DR_RDATA_Pos)     /*!< 0x01000000 */
#define ADC_DR_RDATA_25                   (0x2000000U << ADC_DR_RDATA_Pos)     /*!< 0x02000000 */
#define ADC_DR_RDATA_26                   (0x4000000U << ADC_DR_RDATA_Pos)     /*!< 0x04000000 */
#define ADC_DR_RDATA_27                   (0x8000000U << ADC_DR_RDATA_Pos)     /*!< 0x08000000 */
#define ADC_DR_RDATA_28                   (0x10000000U << ADC_DR_RDATA_Pos)    /*!< 0x10000000 */
#define ADC_DR_RDATA_29                   (0x20000000U << ADC_DR_RDATA_Pos)    /*!< 0x20000000 */
#define ADC_DR_RDATA_30                   (0x40000000U << ADC_DR_RDATA_Pos)    /*!< 0x40000000 */
#define ADC_DR_RDATA_31                   (0x80000000U << ADC_DR_RDATA_Pos)    /*!< 0x80000000 */

/********************  Bit definition for ADC_JSQR register  ********************/
#define ADC_JSQR_JL_Pos                   (0U)
#define ADC_JSQR_JL_Msk                   (0x3U << ADC_JSQR_JL_Pos)            /*!< 0x00000003 */
#define ADC_JSQR_JL                       ADC_JSQR_JL_Msk                      /*!< ADC injected channel sequence length */
#define ADC_JSQR_JL_0                     (0x1U << ADC_JSQR_JL_Pos)            /*!< 0x00000001 */
#define ADC_JSQR_JL_1                     (0x2U << ADC_JSQR_JL_Pos)            /*!< 0x00000002 */

#define ADC_JSQR_JEXTSEL_Pos              (2U)
#define ADC_JSQR_JEXTSEL_Msk              (0x1FU << ADC_JSQR_JEXTSEL_Pos)      /*!< 0x0000007C */
#define ADC_JSQR_JEXTSEL                  ADC_JSQR_JEXTSEL_Msk                 /*!< ADC external trigger selection for injected group */
#define ADC_JSQR_JEXTSEL_0                (0x01U << ADC_JSQR_JEXTSEL_Pos)      /*!< 0x00000004 */
#define ADC_JSQR_JEXTSEL_1                (0x02U << ADC_JSQR_JEXTSEL_Pos)      /*!< 0x00000008 */
#define ADC_JSQR_JEXTSEL_2                (0x04U << ADC_JSQR_JEXTSEL_Pos)      /*!< 0x00000010 */
#define ADC_JSQR_JEXTSEL_3                (0x08U << ADC_JSQR_JEXTSEL_Pos)      /*!< 0x00000020 */
#define ADC_JSQR_JEXTSEL_4                (0x10U << ADC_JSQR_JEXTSEL_Pos)      /*!< 0x00000040 */

#define ADC_JSQR_JEXTEN_Pos               (7U)
#define ADC_JSQR_JEXTEN_Msk               (0x3U << ADC_JSQR_JEXTEN_Pos)        /*!< 0x00000180 */
#define ADC_JSQR_JEXTEN                   ADC_JSQR_JEXTEN_Msk                  /*!< ADC external trigger enable and polarity selection for injected channels */
#define ADC_JSQR_JEXTEN_0                 (0x1U << ADC_JSQR_JEXTEN_Pos)        /*!< 0x00000080 */
#define ADC_JSQR_JEXTEN_1                 (0x2U << ADC_JSQR_JEXTEN_Pos)        /*!< 0x00000100 */

#define ADC_JSQR_JSQ1_Pos                 (9U)
#define ADC_JSQR_JSQ1_Msk                 (0x1FU << ADC_JSQR_JSQ1_Pos)         /*!< 0x00003E00 */
#define ADC_JSQR_JSQ1                     ADC_JSQR_JSQ1_Msk                    /*!< ADC 1st conversion in injected sequence */
#define ADC_JSQR_JSQ1_0                   (0x01U << ADC_JSQR_JSQ1_Pos)         /*!< 0x00000200 */
#define ADC_JSQR_JSQ1_1                   (0x02U << ADC_JSQR_JSQ1_Pos)         /*!< 0x00000400 */
#define ADC_JSQR_JSQ1_2                   (0x04U << ADC_JSQR_JSQ1_Pos)         /*!< 0x00000800 */
#define ADC_JSQR_JSQ1_3                   (0x08U << ADC_JSQR_JSQ1_Pos)         /*!< 0x00001000 */
#define ADC_JSQR_JSQ1_4                   (0x10U << ADC_JSQR_JSQ1_Pos)         /*!< 0x00002000 */

#define ADC_JSQR_JSQ2_Pos                 (15U)
#define ADC_JSQR_JSQ2_Msk                 (0x1FU << ADC_JSQR_JSQ2_Pos)         /*!< 0x000F8000 */
#define ADC_JSQR_JSQ2                     ADC_JSQR_JSQ2_Msk                    /*!< ADC 2nd conversion in injected sequence */
#define ADC_JSQR_JSQ2_0                   (0x01U << ADC_JSQR_JSQ2_Pos)         /*!< 0x00008000 */
#define ADC_JSQR_JSQ2_1                   (0x02U << ADC_JSQR_JSQ2_Pos)         /*!< 0x00010000 */
#define ADC_JSQR_JSQ2_2                   (0x04U << ADC_JSQR_JSQ2_Pos)         /*!< 0x00020000 */
#define ADC_JSQR_JSQ2_3                   (0x08U << ADC_JSQR_JSQ2_Pos)         /*!< 0x00040000 */
#define ADC_JSQR_JSQ2_4                   (0x10U << ADC_JSQR_JSQ2_Pos)         /*!< 0x00080000 */

#define ADC_JSQR_JSQ3_Pos                 (21U)
#define ADC_JSQR_JSQ3_Msk                 (0x1FU << ADC_JSQR_JSQ3_Pos)         /*!< 0x03E00000 */
#define ADC_JSQR_JSQ3                     ADC_JSQR_JSQ3_Msk                    /*!< ADC 3rd conversion in injected sequence */
#define ADC_JSQR_JSQ3_0                   (0x01U << ADC_JSQR_JSQ3_Pos)         /*!< 0x00200000 */
#define ADC_JSQR_JSQ3_1                   (0x02U << ADC_JSQR_JSQ3_Pos)         /*!< 0x00400000 */
#define ADC_JSQR_JSQ3_2                   (0x04U << ADC_JSQR_JSQ3_Pos)         /*!< 0x00800000 */
#define ADC_JSQR_JSQ3_3                   (0x08U << ADC_JSQR_JSQ3_Pos)         /*!< 0x01000000 */
#define ADC_JSQR_JSQ3_4                   (0x10U << ADC_JSQR_JSQ3_Pos)         /*!< 0x02000000 */

#define ADC_JSQR_JSQ4_Pos                 (27U)
#define ADC_JSQR_JSQ4_Msk                 (0x1FU << ADC_JSQR_JSQ4_Pos)         /*!< 0xF8000000 */
#define ADC_JSQR_JSQ4                     ADC_JSQR_JSQ4_Msk                    /*!< ADC 4th conversion in injected sequence */
#define ADC_JSQR_JSQ4_0                   (0x01U << ADC_JSQR_JSQ4_Pos)         /*!< 0x08000000 */
#define ADC_JSQR_JSQ4_1                   (0x02U << ADC_JSQR_JSQ4_Pos)         /*!< 0x10000000 */
#define ADC_JSQR_JSQ4_2                   (0x04U << ADC_JSQR_JSQ4_Pos)         /*!< 0x20000000 */
#define ADC_JSQR_JSQ4_3                   (0x08U << ADC_JSQR_JSQ4_Pos)         /*!< 0x40000000 */
#define ADC_JSQR_JSQ4_4                   (0x10U << ADC_JSQR_JSQ4_Pos)         /*!< 0x80000000 */

/********************  Bit definition for ADC_OFR1 register  ********************/
#define ADC_OFR1_OFFSET1_Pos              (0U)
#define ADC_OFR1_OFFSET1_Msk              (0x3FFFFFFU << ADC_OFR1_OFFSET1_Pos) /*!< 0x03FFFFFF */
#define ADC_OFR1_OFFSET1                  ADC_OFR1_OFFSET1_Msk                 /*!< ADC data offset 1 for channel programmed into bits OFFSET1_CH[4:0] */
#define ADC_OFR1_OFFSET1_0                (0x0000001U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00000001 */
#define ADC_OFR1_OFFSET1_1                (0x0000002U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00000002 */
#define ADC_OFR1_OFFSET1_2                (0x0000004U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00000004 */
#define ADC_OFR1_OFFSET1_3                (0x0000008U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00000008 */
#define ADC_OFR1_OFFSET1_4                (0x0000010U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00000010 */
#define ADC_OFR1_OFFSET1_5                (0x0000020U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00000020 */
#define ADC_OFR1_OFFSET1_6                (0x0000040U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00000040 */
#define ADC_OFR1_OFFSET1_7                (0x0000080U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00000080 */
#define ADC_OFR1_OFFSET1_8                (0x0000100U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00000100 */
#define ADC_OFR1_OFFSET1_9                (0x0000200U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00000200 */
#define ADC_OFR1_OFFSET1_10               (0x0000400U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00000400 */
#define ADC_OFR1_OFFSET1_11               (0x0000800U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00000800 */
#define ADC_OFR1_OFFSET1_12               (0x0001000U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00001000 */
#define ADC_OFR1_OFFSET1_13               (0x0002000U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00002000 */
#define ADC_OFR1_OFFSET1_14               (0x0004000U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00004000 */
#define ADC_OFR1_OFFSET1_15               (0x0008000U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00008000 */
#define ADC_OFR1_OFFSET1_16               (0x0010000U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00010000 */
#define ADC_OFR1_OFFSET1_17               (0x0020000U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00020000 */
#define ADC_OFR1_OFFSET1_18               (0x0040000U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00040000 */
#define ADC_OFR1_OFFSET1_19               (0x0080000U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00080000 */
#define ADC_OFR1_OFFSET1_20               (0x0100000U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00100000 */
#define ADC_OFR1_OFFSET1_21               (0x0200000U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00200000 */
#define ADC_OFR1_OFFSET1_22               (0x0400000U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00400000 */
#define ADC_OFR1_OFFSET1_23               (0x0800000U << ADC_OFR1_OFFSET1_Pos) /*!< 0x00800000 */
#define ADC_OFR1_OFFSET1_24               (0x1000000U << ADC_OFR1_OFFSET1_Pos) /*!< 0x01000000 */
#define ADC_OFR1_OFFSET1_25               (0x2000000U << ADC_OFR1_OFFSET1_Pos) /*!< 0x02000000 */

#define ADC_OFR1_OFFSET1_CH_Pos           (26U)
#define ADC_OFR1_OFFSET1_CH_Msk           (0x1FU << ADC_OFR1_OFFSET1_CH_Pos)   /*!< 0x7C000000 */
#define ADC_OFR1_OFFSET1_CH               ADC_OFR1_OFFSET1_CH_Msk              /*!< ADC Channel selection for the data offset 1 */
#define ADC_OFR1_OFFSET1_CH_0             (0x01U << ADC_OFR1_OFFSET1_CH_Pos)   /*!< 0x04000000 */
#define ADC_OFR1_OFFSET1_CH_1             (0x02U << ADC_OFR1_OFFSET1_CH_Pos)   /*!< 0x08000000 */
#define ADC_OFR1_OFFSET1_CH_2             (0x04U << ADC_OFR1_OFFSET1_CH_Pos)   /*!< 0x10000000 */
#define ADC_OFR1_OFFSET1_CH_3             (0x08U << ADC_OFR1_OFFSET1_CH_Pos)   /*!< 0x20000000 */
#define ADC_OFR1_OFFSET1_CH_4             (0x10U << ADC_OFR1_OFFSET1_CH_Pos)   /*!< 0x40000000 */

#define ADC_OFR1_SSATE_Pos                (31U)
#define ADC_OFR1_SSATE_Msk                (0x1U << ADC_OFR1_SSATE_Pos)         /*!< 0x80000000 */
#define ADC_OFR1_SSATE                    ADC_OFR1_SSATE_Msk                   /*!< ADC Signed saturation Enable */

/********************  Bit definition for ADC_OFR2 register  ********************/
#define ADC_OFR2_OFFSET2_Pos              (0U)
#define ADC_OFR2_OFFSET2_Msk              (0x3FFFFFFU << ADC_OFR2_OFFSET2_Pos) /*!< 0x03FFFFFF */
#define ADC_OFR2_OFFSET2                  ADC_OFR2_OFFSET2_Msk                 /*!< ADC data offset 2 for channel programmed into bits OFFSET2_CH[4:0] */
#define ADC_OFR2_OFFSET2_0                (0x0000001U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00000001 */
#define ADC_OFR2_OFFSET2_1                (0x0000002U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00000002 */
#define ADC_OFR2_OFFSET2_2                (0x0000004U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00000004 */
#define ADC_OFR2_OFFSET2_3                (0x0000008U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00000008 */
#define ADC_OFR2_OFFSET2_4                (0x0000010U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00000010 */
#define ADC_OFR2_OFFSET2_5                (0x0000020U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00000020 */
#define ADC_OFR2_OFFSET2_6                (0x0000040U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00000040 */
#define ADC_OFR2_OFFSET2_7                (0x0000080U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00000080 */
#define ADC_OFR2_OFFSET2_8                (0x0000100U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00000100 */
#define ADC_OFR2_OFFSET2_9                (0x0000200U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00000200 */
#define ADC_OFR2_OFFSET2_10               (0x0000400U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00000400 */
#define ADC_OFR2_OFFSET2_11               (0x0000800U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00000800 */
#define ADC_OFR2_OFFSET2_12               (0x0001000U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00001000 */
#define ADC_OFR2_OFFSET2_13               (0x0002000U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00002000 */
#define ADC_OFR2_OFFSET2_14               (0x0004000U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00004000 */
#define ADC_OFR2_OFFSET2_15               (0x0008000U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00008000 */
#define ADC_OFR2_OFFSET2_16               (0x0010000U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00010000 */
#define ADC_OFR2_OFFSET2_17               (0x0020000U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00020000 */
#define ADC_OFR2_OFFSET2_18               (0x0040000U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00040000 */
#define ADC_OFR2_OFFSET2_19               (0x0080000U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00080000 */
#define ADC_OFR2_OFFSET2_20               (0x0100000U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00100000 */
#define ADC_OFR2_OFFSET2_21               (0x0200000U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00200000 */
#define ADC_OFR2_OFFSET2_22               (0x0400000U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00400000 */
#define ADC_OFR2_OFFSET2_23               (0x0800000U << ADC_OFR2_OFFSET2_Pos) /*!< 0x00800000 */
#define ADC_OFR2_OFFSET2_24               (0x1000000U << ADC_OFR2_OFFSET2_Pos) /*!< 0x01000000 */
#define ADC_OFR2_OFFSET2_25               (0x2000000U << ADC_OFR2_OFFSET2_Pos) /*!< 0x02000000 */

#define ADC_OFR2_OFFSET2_CH_Pos           (26U)
#define ADC_OFR2_OFFSET2_CH_Msk           (0x1FU << ADC_OFR2_OFFSET2_CH_Pos)   /*!< 0x7C000000 */
#define ADC_OFR2_OFFSET2_CH               ADC_OFR2_OFFSET2_CH_Msk              /*!< ADC Channel selection for the data offset 2 */
#define ADC_OFR2_OFFSET2_CH_0             (0x01U << ADC_OFR2_OFFSET2_CH_Pos)   /*!< 0x04000000 */
#define ADC_OFR2_OFFSET2_CH_1             (0x02U << ADC_OFR2_OFFSET2_CH_Pos)   /*!< 0x08000000 */
#define ADC_OFR2_OFFSET2_CH_2             (0x04U << ADC_OFR2_OFFSET2_CH_Pos)   /*!< 0x10000000 */
#define ADC_OFR2_OFFSET2_CH_3             (0x08U << ADC_OFR2_OFFSET2_CH_Pos)   /*!< 0x20000000 */
#define ADC_OFR2_OFFSET2_CH_4             (0x10U << ADC_OFR2_OFFSET2_CH_Pos)   /*!< 0x40000000 */

#define ADC_OFR2_SSATE_Pos                (31U)
#define ADC_OFR2_SSATE_Msk                (0x1U << ADC_OFR2_SSATE_Pos)         /*!< 0x80000000 */
#define ADC_OFR2_SSATE                    ADC_OFR2_SSATE_Msk                   /*!< ADC Signed saturation Enable */

/********************  Bit definition for ADC_OFR3 register  ********************/
#define ADC_OFR3_OFFSET3_Pos              (0U)
#define ADC_OFR3_OFFSET3_Msk              (0x3FFFFFFU << ADC_OFR3_OFFSET3_Pos) /*!< 0x03FFFFFF */
#define ADC_OFR3_OFFSET3                  ADC_OFR3_OFFSET3_Msk                 /*!< ADC data offset 3 for channel programmed into bits OFFSET3_CH[4:0] */
#define ADC_OFR3_OFFSET3_0                (0x0000001U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00000001 */
#define ADC_OFR3_OFFSET3_1                (0x0000002U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00000002 */
#define ADC_OFR3_OFFSET3_2                (0x0000004U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00000004 */
#define ADC_OFR3_OFFSET3_3                (0x0000008U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00000008 */
#define ADC_OFR3_OFFSET3_4                (0x0000010U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00000010 */
#define ADC_OFR3_OFFSET3_5                (0x0000020U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00000020 */
#define ADC_OFR3_OFFSET3_6                (0x0000040U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00000040 */
#define ADC_OFR3_OFFSET3_7                (0x0000080U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00000080 */
#define ADC_OFR3_OFFSET3_8                (0x0000100U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00000100 */
#define ADC_OFR3_OFFSET3_9                (0x0000200U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00000200 */
#define ADC_OFR3_OFFSET3_10               (0x0000400U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00000400 */
#define ADC_OFR3_OFFSET3_11               (0x0000800U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00000800 */
#define ADC_OFR3_OFFSET3_12               (0x0001000U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00001000 */
#define ADC_OFR3_OFFSET3_13               (0x0002000U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00002000 */
#define ADC_OFR3_OFFSET3_14               (0x0004000U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00004000 */
#define ADC_OFR3_OFFSET3_15               (0x0008000U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00008000 */
#define ADC_OFR3_OFFSET3_16               (0x0010000U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00010000 */
#define ADC_OFR3_OFFSET3_17               (0x0020000U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00020000 */
#define ADC_OFR3_OFFSET3_18               (0x0040000U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00040000 */
#define ADC_OFR3_OFFSET3_19               (0x0080000U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00080000 */
#define ADC_OFR3_OFFSET3_20               (0x0100000U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00100000 */
#define ADC_OFR3_OFFSET3_21               (0x0200000U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00200000 */
#define ADC_OFR3_OFFSET3_22               (0x0400000U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00400000 */
#define ADC_OFR3_OFFSET3_23               (0x0800000U << ADC_OFR3_OFFSET3_Pos) /*!< 0x00800000 */
#define ADC_OFR3_OFFSET3_24               (0x1000000U << ADC_OFR3_OFFSET3_Pos) /*!< 0x01000000 */
#define ADC_OFR3_OFFSET3_25               (0x2000000U << ADC_OFR3_OFFSET3_Pos) /*!< 0x02000000 */

#define ADC_OFR3_OFFSET3_CH_Pos           (26U)
#define ADC_OFR3_OFFSET3_CH_Msk           (0x1FU << ADC_OFR3_OFFSET3_CH_Pos)   /*!< 0x7C000000 */
#define ADC_OFR3_OFFSET3_CH               ADC_OFR3_OFFSET3_CH_Msk              /*!< ADC Channel selection for the data offset 3 */
#define ADC_OFR3_OFFSET3_CH_0             (0x01U << ADC_OFR3_OFFSET3_CH_Pos)   /*!< 0x04000000 */
#define ADC_OFR3_OFFSET3_CH_1             (0x02U << ADC_OFR3_OFFSET3_CH_Pos)   /*!< 0x08000000 */
#define ADC_OFR3_OFFSET3_CH_2             (0x04U << ADC_OFR3_OFFSET3_CH_Pos)   /*!< 0x10000000 */
#define ADC_OFR3_OFFSET3_CH_3             (0x08U << ADC_OFR3_OFFSET3_CH_Pos)   /*!< 0x20000000 */
#define ADC_OFR3_OFFSET3_CH_4             (0x10U << ADC_OFR3_OFFSET3_CH_Pos)   /*!< 0x40000000 */

#define ADC_OFR3_SSATE_Pos                (31U)
#define ADC_OFR3_SSATE_Msk                (0x1U << ADC_OFR3_SSATE_Pos)         /*!< 0x80000000 */
#define ADC_OFR3_SSATE                    ADC_OFR3_SSATE_Msk                   /*!< ADC Signed saturation Enable */

/********************  Bit definition for ADC_OFR4 register  ********************/
#define ADC_OFR4_OFFSET4_Pos              (0U)
#define ADC_OFR4_OFFSET4_Msk              (0x3FFFFFFU << ADC_OFR4_OFFSET4_Pos) /*!< 0x03FFFFFF */
#define ADC_OFR4_OFFSET4                  ADC_OFR4_OFFSET4_Msk                 /*!< ADC data offset 4 for channel programmed into bits OFFSET4_CH[4:0] */
#define ADC_OFR4_OFFSET4_0                (0x0000001U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00000001 */
#define ADC_OFR4_OFFSET4_1                (0x0000002U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00000002 */
#define ADC_OFR4_OFFSET4_2                (0x0000004U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00000004 */
#define ADC_OFR4_OFFSET4_3                (0x0000008U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00000008 */
#define ADC_OFR4_OFFSET4_4                (0x0000010U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00000010 */
#define ADC_OFR4_OFFSET4_5                (0x0000020U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00000020 */
#define ADC_OFR4_OFFSET4_6                (0x0000040U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00000040 */
#define ADC_OFR4_OFFSET4_7                (0x0000080U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00000080 */
#define ADC_OFR4_OFFSET4_8                (0x0000100U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00000100 */
#define ADC_OFR4_OFFSET4_9                (0x0000200U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00000200 */
#define ADC_OFR4_OFFSET4_10               (0x0000400U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00000400 */
#define ADC_OFR4_OFFSET4_11               (0x0000800U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00000800 */
#define ADC_OFR4_OFFSET4_12               (0x0001000U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00001000 */
#define ADC_OFR4_OFFSET4_13               (0x0002000U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00002000 */
#define ADC_OFR4_OFFSET4_14               (0x0004000U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00004000 */
#define ADC_OFR4_OFFSET4_15               (0x0008000U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00008000 */
#define ADC_OFR4_OFFSET4_16               (0x0010000U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00010000 */
#define ADC_OFR4_OFFSET4_17               (0x0020000U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00020000 */
#define ADC_OFR4_OFFSET4_18               (0x0040000U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00040000 */
#define ADC_OFR4_OFFSET4_19               (0x0080000U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00080000 */
#define ADC_OFR4_OFFSET4_20               (0x0100000U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00100000 */
#define ADC_OFR4_OFFSET4_21               (0x0200000U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00200000 */
#define ADC_OFR4_OFFSET4_22               (0x0400000U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00400000 */
#define ADC_OFR4_OFFSET4_23               (0x0800000U << ADC_OFR4_OFFSET4_Pos) /*!< 0x00800000 */
#define ADC_OFR4_OFFSET4_24               (0x1000000U << ADC_OFR4_OFFSET4_Pos) /*!< 0x01000000 */
#define ADC_OFR4_OFFSET4_25               (0x2000000U << ADC_OFR4_OFFSET4_Pos) /*!< 0x02000000 */

#define ADC_OFR4_OFFSET4_CH_Pos           (26U)
#define ADC_OFR4_OFFSET4_CH_Msk           (0x1FU << ADC_OFR4_OFFSET4_CH_Pos)   /*!< 0x7C000000 */
#define ADC_OFR4_OFFSET4_CH               ADC_OFR4_OFFSET4_CH_Msk              /*!< ADC Channel selection for the data offset 4 */
#define ADC_OFR4_OFFSET4_CH_0             (0x01U << ADC_OFR4_OFFSET4_CH_Pos)   /*!< 0x04000000 */
#define ADC_OFR4_OFFSET4_CH_1             (0x02U << ADC_OFR4_OFFSET4_CH_Pos)   /*!< 0x08000000 */
#define ADC_OFR4_OFFSET4_CH_2             (0x04U << ADC_OFR4_OFFSET4_CH_Pos)   /*!< 0x10000000 */
#define ADC_OFR4_OFFSET4_CH_3             (0x08U << ADC_OFR4_OFFSET4_CH_Pos)   /*!< 0x20000000 */
#define ADC_OFR4_OFFSET4_CH_4             (0x10U << ADC_OFR4_OFFSET4_CH_Pos)   /*!< 0x40000000 */

#define ADC_OFR4_SSATE_Pos                (31U)
#define ADC_OFR4_SSATE_Msk                (0x1U << ADC_OFR4_SSATE_Pos)         /*!< 0x80000000 */
#define ADC_OFR4_SSATE                    ADC_OFR4_SSATE_Msk                   /*!< ADC Signed saturation Enable */

/********************  Bit definition for ADC_JDR1 register  ********************/
#define ADC_JDR1_JDATA_Pos                (0U)
#define ADC_JDR1_JDATA_Msk                (0xFFFFFFFFU << ADC_JDR1_JDATA_Pos)  /*!< 0xFFFFFFFF */
#define ADC_JDR1_JDATA                    ADC_JDR1_JDATA_Msk                   /*!< ADC Injected DATA */
#define ADC_JDR1_JDATA_0                  (0x0001U << ADC_JDR1_JDATA_Pos)      /*!< 0x00000001 */
#define ADC_JDR1_JDATA_1                  (0x0002U << ADC_JDR1_JDATA_Pos)      /*!< 0x00000002 */
#define ADC_JDR1_JDATA_2                  (0x0004U << ADC_JDR1_JDATA_Pos)      /*!< 0x00000004 */
#define ADC_JDR1_JDATA_3                  (0x0008U << ADC_JDR1_JDATA_Pos)      /*!< 0x00000008 */
#define ADC_JDR1_JDATA_4                  (0x0010U << ADC_JDR1_JDATA_Pos)      /*!< 0x00000010 */
#define ADC_JDR1_JDATA_5                  (0x0020U << ADC_JDR1_JDATA_Pos)      /*!< 0x00000020 */
#define ADC_JDR1_JDATA_6                  (0x0040U << ADC_JDR1_JDATA_Pos)      /*!< 0x00000040 */
#define ADC_JDR1_JDATA_7                  (0x0080U << ADC_JDR1_JDATA_Pos)      /*!< 0x00000080 */
#define ADC_JDR1_JDATA_8                  (0x0100U << ADC_JDR1_JDATA_Pos)      /*!< 0x00000100 */
#define ADC_JDR1_JDATA_9                  (0x0200U << ADC_JDR1_JDATA_Pos)      /*!< 0x00000200 */
#define ADC_JDR1_JDATA_10                 (0x0400U << ADC_JDR1_JDATA_Pos)      /*!< 0x00000400 */
#define ADC_JDR1_JDATA_11                 (0x0800U << ADC_JDR1_JDATA_Pos)      /*!< 0x00000800 */
#define ADC_JDR1_JDATA_12                 (0x1000U << ADC_JDR1_JDATA_Pos)      /*!< 0x00001000 */
#define ADC_JDR1_JDATA_13                 (0x2000U << ADC_JDR1_JDATA_Pos)      /*!< 0x00002000 */
#define ADC_JDR1_JDATA_14                 (0x4000U << ADC_JDR1_JDATA_Pos)      /*!< 0x00004000 */
#define ADC_JDR1_JDATA_15                 (0x8000U << ADC_JDR1_JDATA_Pos)      /*!< 0x00008000 */
#define ADC_JDR1_JDATA_16                 (0x10000U << ADC_JDR1_JDATA_Pos)     /*!< 0x00010000 */
#define ADC_JDR1_JDATA_17                 (0x20000U << ADC_JDR1_JDATA_Pos)     /*!< 0x00020000 */
#define ADC_JDR1_JDATA_18                 (0x40000U << ADC_JDR1_JDATA_Pos)     /*!< 0x00040000 */
#define ADC_JDR1_JDATA_19                 (0x80000U << ADC_JDR1_JDATA_Pos)     /*!< 0x00080000 */
#define ADC_JDR1_JDATA_20                 (0x100000U << ADC_JDR1_JDATA_Pos)    /*!< 0x00100000 */
#define ADC_JDR1_JDATA_21                 (0x200000U << ADC_JDR1_JDATA_Pos)    /*!< 0x00200000 */
#define ADC_JDR1_JDATA_22                 (0x400000U << ADC_JDR1_JDATA_Pos)    /*!< 0x00400000 */
#define ADC_JDR1_JDATA_23                 (0x800000U << ADC_JDR1_JDATA_Pos)    /*!< 0x00800000 */
#define ADC_JDR1_JDATA_24                 (0x1000000U << ADC_JDR1_JDATA_Pos)   /*!< 0x01000000 */
#define ADC_JDR1_JDATA_25                 (0x2000000U << ADC_JDR1_JDATA_Pos)   /*!< 0x02000000 */
#define ADC_JDR1_JDATA_26                 (0x4000000U << ADC_JDR1_JDATA_Pos)   /*!< 0x04000000 */
#define ADC_JDR1_JDATA_27                 (0x8000000U << ADC_JDR1_JDATA_Pos)   /*!< 0x08000000 */
#define ADC_JDR1_JDATA_28                 (0x10000000U << ADC_JDR1_JDATA_Pos)  /*!< 0x10000000 */
#define ADC_JDR1_JDATA_29                 (0x20000000U << ADC_JDR1_JDATA_Pos)  /*!< 0x20000000 */
#define ADC_JDR1_JDATA_30                 (0x40000000U << ADC_JDR1_JDATA_Pos)  /*!< 0x40000000 */
#define ADC_JDR1_JDATA_31                 (0x80000000U << ADC_JDR1_JDATA_Pos)  /*!< 0x80000000 */

/********************  Bit definition for ADC_JDR2 register  ********************/
#define ADC_JDR2_JDATA_Pos                (0U)
#define ADC_JDR2_JDATA_Msk                (0xFFFFFFFFU << ADC_JDR2_JDATA_Pos)  /*!< 0xFFFFFFFF */
#define ADC_JDR2_JDATA                    ADC_JDR2_JDATA_Msk                   /*!< ADC Injected DATA */
#define ADC_JDR2_JDATA_0                  (0x0001U << ADC_JDR2_JDATA_Pos)      /*!< 0x00000001 */
#define ADC_JDR2_JDATA_1                  (0x0002U << ADC_JDR2_JDATA_Pos)      /*!< 0x00000002 */
#define ADC_JDR2_JDATA_2                  (0x0004U << ADC_JDR2_JDATA_Pos)      /*!< 0x00000004 */
#define ADC_JDR2_JDATA_3                  (0x0008U << ADC_JDR2_JDATA_Pos)      /*!< 0x00000008 */
#define ADC_JDR2_JDATA_4                  (0x0010U << ADC_JDR2_JDATA_Pos)      /*!< 0x00000010 */
#define ADC_JDR2_JDATA_5                  (0x0020U << ADC_JDR2_JDATA_Pos)      /*!< 0x00000020 */
#define ADC_JDR2_JDATA_6                  (0x0040U << ADC_JDR2_JDATA_Pos)      /*!< 0x00000040 */
#define ADC_JDR2_JDATA_7                  (0x0080U << ADC_JDR2_JDATA_Pos)      /*!< 0x00000080 */
#define ADC_JDR2_JDATA_8                  (0x0100U << ADC_JDR2_JDATA_Pos)      /*!< 0x00000100 */
#define ADC_JDR2_JDATA_9                  (0x0200U << ADC_JDR2_JDATA_Pos)      /*!< 0x00000200 */
#define ADC_JDR2_JDATA_10                 (0x0400U << ADC_JDR2_JDATA_Pos)      /*!< 0x00000400 */
#define ADC_JDR2_JDATA_11                 (0x0800U << ADC_JDR2_JDATA_Pos)      /*!< 0x00000800 */
#define ADC_JDR2_JDATA_12                 (0x1000U << ADC_JDR2_JDATA_Pos)      /*!< 0x00001000 */
#define ADC_JDR2_JDATA_13                 (0x2000U << ADC_JDR2_JDATA_Pos)      /*!< 0x00002000 */
#define ADC_JDR2_JDATA_14                 (0x4000U << ADC_JDR2_JDATA_Pos)      /*!< 0x00004000 */
#define ADC_JDR2_JDATA_15                 (0x8000U << ADC_JDR2_JDATA_Pos)      /*!< 0x00008000 */
#define ADC_JDR2_JDATA_16                 (0x10000U << ADC_JDR2_JDATA_Pos)     /*!< 0x00010000 */
#define ADC_JDR2_JDATA_17                 (0x20000U << ADC_JDR2_JDATA_Pos)     /*!< 0x00020000 */
#define ADC_JDR2_JDATA_18                 (0x40000U << ADC_JDR2_JDATA_Pos)     /*!< 0x00040000 */
#define ADC_JDR2_JDATA_19                 (0x80000U << ADC_JDR2_JDATA_Pos)     /*!< 0x00080000 */
#define ADC_JDR2_JDATA_20                 (0x100000U << ADC_JDR2_JDATA_Pos)    /*!< 0x00100000 */
#define ADC_JDR2_JDATA_21                 (0x200000U << ADC_JDR2_JDATA_Pos)    /*!< 0x00200000 */
#define ADC_JDR2_JDATA_22                 (0x400000U << ADC_JDR2_JDATA_Pos)    /*!< 0x00400000 */
#define ADC_JDR2_JDATA_23                 (0x800000U << ADC_JDR2_JDATA_Pos)    /*!< 0x00800000 */
#define ADC_JDR2_JDATA_24                 (0x1000000U << ADC_JDR2_JDATA_Pos)   /*!< 0x01000000 */
#define ADC_JDR2_JDATA_25                 (0x2000000U << ADC_JDR2_JDATA_Pos)   /*!< 0x02000000 */
#define ADC_JDR2_JDATA_26                 (0x4000000U << ADC_JDR2_JDATA_Pos)   /*!< 0x04000000 */
#define ADC_JDR2_JDATA_27                 (0x8000000U << ADC_JDR2_JDATA_Pos)   /*!< 0x08000000 */
#define ADC_JDR2_JDATA_28                 (0x10000000U << ADC_JDR2_JDATA_Pos)  /*!< 0x10000000 */
#define ADC_JDR2_JDATA_29                 (0x20000000U << ADC_JDR2_JDATA_Pos)  /*!< 0x20000000 */
#define ADC_JDR2_JDATA_30                 (0x40000000U << ADC_JDR2_JDATA_Pos)  /*!< 0x40000000 */
#define ADC_JDR2_JDATA_31                 (0x80000000U << ADC_JDR2_JDATA_Pos)  /*!< 0x80000000 */

/********************  Bit definition for ADC_JDR3 register  ********************/
#define ADC_JDR3_JDATA_Pos                (0U)
#define ADC_JDR3_JDATA_Msk                (0xFFFFFFFFU << ADC_JDR3_JDATA_Pos)  /*!< 0xFFFFFFFF */
#define ADC_JDR3_JDATA                    ADC_JDR3_JDATA_Msk                   /*!< ADC Injected DATA */
#define ADC_JDR3_JDATA_0                  (0x0001U << ADC_JDR3_JDATA_Pos)      /*!< 0x00000001 */
#define ADC_JDR3_JDATA_1                  (0x0002U << ADC_JDR3_JDATA_Pos)      /*!< 0x00000002 */
#define ADC_JDR3_JDATA_2                  (0x0004U << ADC_JDR3_JDATA_Pos)      /*!< 0x00000004 */
#define ADC_JDR3_JDATA_3                  (0x0008U << ADC_JDR3_JDATA_Pos)      /*!< 0x00000008 */
#define ADC_JDR3_JDATA_4                  (0x0010U << ADC_JDR3_JDATA_Pos)      /*!< 0x00000010 */
#define ADC_JDR3_JDATA_5                  (0x0020U << ADC_JDR3_JDATA_Pos)      /*!< 0x00000020 */
#define ADC_JDR3_JDATA_6                  (0x0040U << ADC_JDR3_JDATA_Pos)      /*!< 0x00000040 */
#define ADC_JDR3_JDATA_7                  (0x0080U << ADC_JDR3_JDATA_Pos)      /*!< 0x00000080 */
#define ADC_JDR3_JDATA_8                  (0x0100U << ADC_JDR3_JDATA_Pos)      /*!< 0x00000100 */
#define ADC_JDR3_JDATA_9                  (0x0200U << ADC_JDR3_JDATA_Pos)      /*!< 0x00000200 */
#define ADC_JDR3_JDATA_10                 (0x0400U << ADC_JDR3_JDATA_Pos)      /*!< 0x00000400 */
#define ADC_JDR3_JDATA_11                 (0x0800U << ADC_JDR3_JDATA_Pos)      /*!< 0x00000800 */
#define ADC_JDR3_JDATA_12                 (0x1000U << ADC_JDR3_JDATA_Pos)      /*!< 0x00001000 */
#define ADC_JDR3_JDATA_13                 (0x2000U << ADC_JDR3_JDATA_Pos)      /*!< 0x00002000 */
#define ADC_JDR3_JDATA_14                 (0x4000U << ADC_JDR3_JDATA_Pos)      /*!< 0x00004000 */
#define ADC_JDR3_JDATA_15                 (0x8000U << ADC_JDR3_JDATA_Pos)      /*!< 0x00008000 */
#define ADC_JDR3_JDATA_16                 (0x10000U << ADC_JDR3_JDATA_Pos)     /*!< 0x00010000 */
#define ADC_JDR3_JDATA_17                 (0x20000U << ADC_JDR3_JDATA_Pos)     /*!< 0x00020000 */
#define ADC_JDR3_JDATA_18                 (0x40000U << ADC_JDR3_JDATA_Pos)     /*!< 0x00040000 */
#define ADC_JDR3_JDATA_19                 (0x80000U << ADC_JDR3_JDATA_Pos)     /*!< 0x00080000 */
#define ADC_JDR3_JDATA_20                 (0x100000U << ADC_JDR3_JDATA_Pos)    /*!< 0x00100000 */
#define ADC_JDR3_JDATA_21                 (0x200000U << ADC_JDR3_JDATA_Pos)    /*!< 0x00200000 */
#define ADC_JDR3_JDATA_22                 (0x400000U << ADC_JDR3_JDATA_Pos)    /*!< 0x00400000 */
#define ADC_JDR3_JDATA_23                 (0x800000U << ADC_JDR3_JDATA_Pos)    /*!< 0x00800000 */
#define ADC_JDR3_JDATA_24                 (0x1000000U << ADC_JDR3_JDATA_Pos)   /*!< 0x01000000 */
#define ADC_JDR3_JDATA_25                 (0x2000000U << ADC_JDR3_JDATA_Pos)   /*!< 0x02000000 */
#define ADC_JDR3_JDATA_26                 (0x4000000U << ADC_JDR3_JDATA_Pos)   /*!< 0x04000000 */
#define ADC_JDR3_JDATA_27                 (0x8000000U << ADC_JDR3_JDATA_Pos)   /*!< 0x08000000 */
#define ADC_JDR3_JDATA_28                 (0x10000000U << ADC_JDR3_JDATA_Pos)  /*!< 0x10000000 */
#define ADC_JDR3_JDATA_29                 (0x20000000U << ADC_JDR3_JDATA_Pos)  /*!< 0x20000000 */
#define ADC_JDR3_JDATA_30                 (0x40000000U << ADC_JDR3_JDATA_Pos)  /*!< 0x40000000 */
#define ADC_JDR3_JDATA_31                 (0x80000000U << ADC_JDR3_JDATA_Pos)  /*!< 0x80000000 */

/********************  Bit definition for ADC_JDR4 register  ********************/
#define ADC_JDR4_JDATA_Pos                (0U)
#define ADC_JDR4_JDATA_Msk                (0xFFFFFFFFU << ADC_JDR4_JDATA_Pos)  /*!< 0xFFFFFFFF */
#define ADC_JDR4_JDATA                    ADC_JDR4_JDATA_Msk                   /*!< ADC Injected DATA */
#define ADC_JDR4_JDATA_0                  (0x0001U << ADC_JDR4_JDATA_Pos)      /*!< 0x00000001 */
#define ADC_JDR4_JDATA_1                  (0x0002U << ADC_JDR4_JDATA_Pos)      /*!< 0x00000002 */
#define ADC_JDR4_JDATA_2                  (0x0004U << ADC_JDR4_JDATA_Pos)      /*!< 0x00000004 */
#define ADC_JDR4_JDATA_3                  (0x0008U << ADC_JDR4_JDATA_Pos)      /*!< 0x00000008 */
#define ADC_JDR4_JDATA_4                  (0x0010U << ADC_JDR4_JDATA_Pos)      /*!< 0x00000010 */
#define ADC_JDR4_JDATA_5                  (0x0020U << ADC_JDR4_JDATA_Pos)      /*!< 0x00000020 */
#define ADC_JDR4_JDATA_6                  (0x0040U << ADC_JDR4_JDATA_Pos)      /*!< 0x00000040 */
#define ADC_JDR4_JDATA_7                  (0x0080U << ADC_JDR4_JDATA_Pos)      /*!< 0x00000080 */
#define ADC_JDR4_JDATA_8                  (0x0100U << ADC_JDR4_JDATA_Pos)      /*!< 0x00000100 */
#define ADC_JDR4_JDATA_9                  (0x0200U << ADC_JDR4_JDATA_Pos)      /*!< 0x00000200 */
#define ADC_JDR4_JDATA_10                 (0x0400U << ADC_JDR4_JDATA_Pos)      /*!< 0x00000400 */
#define ADC_JDR4_JDATA_11                 (0x0800U << ADC_JDR4_JDATA_Pos)      /*!< 0x00000800 */
#define ADC_JDR4_JDATA_12                 (0x1000U << ADC_JDR4_JDATA_Pos)      /*!< 0x00001000 */
#define ADC_JDR4_JDATA_13                 (0x2000U << ADC_JDR4_JDATA_Pos)      /*!< 0x00002000 */
#define ADC_JDR4_JDATA_14                 (0x4000U << ADC_JDR4_JDATA_Pos)      /*!< 0x00004000 */
#define ADC_JDR4_JDATA_15                 (0x8000U << ADC_JDR4_JDATA_Pos)      /*!< 0x00008000 */
#define ADC_JDR4_JDATA_16                 (0x10000U << ADC_JDR4_JDATA_Pos)     /*!< 0x00010000 */
#define ADC_JDR4_JDATA_17                 (0x20000U << ADC_JDR4_JDATA_Pos)     /*!< 0x00020000 */
#define ADC_JDR4_JDATA_18                 (0x40000U << ADC_JDR4_JDATA_Pos)     /*!< 0x00040000 */
#define ADC_JDR4_JDATA_19                 (0x80000U << ADC_JDR4_JDATA_Pos)     /*!< 0x00080000 */
#define ADC_JDR4_JDATA_20                 (0x100000U << ADC_JDR4_JDATA_Pos)    /*!< 0x00100000 */
#define ADC_JDR4_JDATA_21                 (0x200000U << ADC_JDR4_JDATA_Pos)    /*!< 0x00200000 */
#define ADC_JDR4_JDATA_22                 (0x400000U << ADC_JDR4_JDATA_Pos)    /*!< 0x00400000 */
#define ADC_JDR4_JDATA_23                 (0x800000U << ADC_JDR4_JDATA_Pos)    /*!< 0x00800000 */
#define ADC_JDR4_JDATA_24                 (0x1000000U << ADC_JDR4_JDATA_Pos)   /*!< 0x01000000 */
#define ADC_JDR4_JDATA_25                 (0x2000000U << ADC_JDR4_JDATA_Pos)   /*!< 0x02000000 */
#define ADC_JDR4_JDATA_26                 (0x4000000U << ADC_JDR4_JDATA_Pos)   /*!< 0x04000000 */
#define ADC_JDR4_JDATA_27                 (0x8000000U << ADC_JDR4_JDATA_Pos)   /*!< 0x08000000 */
#define ADC_JDR4_JDATA_28                 (0x10000000U << ADC_JDR4_JDATA_Pos)  /*!< 0x10000000 */
#define ADC_JDR4_JDATA_29                 (0x20000000U << ADC_JDR4_JDATA_Pos)  /*!< 0x20000000 */
#define ADC_JDR4_JDATA_30                 (0x40000000U << ADC_JDR4_JDATA_Pos)  /*!< 0x40000000 */
#define ADC_JDR4_JDATA_31                 (0x80000000U << ADC_JDR4_JDATA_Pos)  /*!< 0x80000000 */

/********************  Bit definition for ADC_AWD2CR register  ********************/
#define ADC_AWD2CR_AWD2CH_Pos             (0U)
#define ADC_AWD2CR_AWD2CH_Msk             (0xFFFFFU << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x000FFFFF */
#define ADC_AWD2CR_AWD2CH                 ADC_AWD2CR_AWD2CH_Msk                /*!< ADC Analog watchdog 2 channel selection */
#define ADC_AWD2CR_AWD2CH_0               (0x00001U << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000001 */
#define ADC_AWD2CR_AWD2CH_1               (0x00002U << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000002 */
#define ADC_AWD2CR_AWD2CH_2               (0x00004U << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000004 */
#define ADC_AWD2CR_AWD2CH_3               (0x00008U << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000008 */
#define ADC_AWD2CR_AWD2CH_4               (0x00010U << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000010 */
#define ADC_AWD2CR_AWD2CH_5               (0x00020U << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000020 */
#define ADC_AWD2CR_AWD2CH_6               (0x00040U << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000040 */
#define ADC_AWD2CR_AWD2CH_7               (0x00080U << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000080 */
#define ADC_AWD2CR_AWD2CH_8               (0x00100U << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000100 */
#define ADC_AWD2CR_AWD2CH_9               (0x00200U << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000200 */
#define ADC_AWD2CR_AWD2CH_10              (0x00400U << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000400 */
#define ADC_AWD2CR_AWD2CH_11              (0x00800U << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00000800 */
#define ADC_AWD2CR_AWD2CH_12              (0x01000U << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00001000 */
#define ADC_AWD2CR_AWD2CH_13              (0x02000U << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00002000 */
#define ADC_AWD2CR_AWD2CH_14              (0x04000U << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00004000 */
#define ADC_AWD2CR_AWD2CH_15              (0x08000U << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00008000 */
#define ADC_AWD2CR_AWD2CH_16              (0x10000U << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00010000 */
#define ADC_AWD2CR_AWD2CH_17              (0x20000U << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00020000 */
#define ADC_AWD2CR_AWD2CH_18              (0x40000U << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00040000 */
#define ADC_AWD2CR_AWD2CH_19              (0x80000U << ADC_AWD2CR_AWD2CH_Pos)  /*!< 0x00080000 */

/********************  Bit definition for ADC_AWD3CR register  ********************/
#define ADC_AWD3CR_AWD3CH_Pos             (0U)
#define ADC_AWD3CR_AWD3CH_Msk             (0xFFFFFU << ADC_AWD3CR_AWD3CH_Pos)  /*!< 0x000FFFFF */
#define ADC_AWD3CR_AWD3CH                 ADC_AWD3CR_AWD3CH_Msk                /*!< ADC Analog watchdog 3 channel selection */
#define ADC_AWD3CR_AWD3CH_0               (0x00001U << ADC_AWD3CR_AWD3CH_Pos)  /*!< 0x00000001 */
#define ADC_AWD3CR_AWD3CH_1               (0x00002U << ADC_AWD3CR_AWD3CH_Pos)  /*!< 0x00000002 */
#define ADC_AWD3CR_AWD3CH_2               (0x00004U << ADC_AWD3CR_AWD3CH_Pos)  /*!< 0x00000004 */
#define ADC_AWD3CR_AWD3CH_3               (0x00008U << ADC_AWD3CR_AWD3CH_Pos)  /*!< 0x00000008 */
#define ADC_AWD3CR_AWD3CH_4               (0x00010U << ADC_AWD3CR_AWD3CH_Pos)  /*!< 0x00000010 */
#define ADC_AWD3CR_AWD3CH_5               (0x00020U << ADC_AWD3CR_AWD3CH_Pos)  /*!< 0x00000020 */
#define ADC_AWD3CR_AWD3CH_6               (0x00040U << ADC_AWD3CR_AWD3CH_Pos)  /*!< 0x00000040 */
#define ADC_AWD3CR_AWD3CH_7               (0x00080U << ADC_AWD3CR_AWD3CH_Pos)  /*!< 0x00000080 */
#define ADC_AWD3CR_AWD3CH_8               (0x00100U << ADC_AWD3CR_AWD3CH_Pos)  /*!< 0x00000100 */
#define ADC_AWD3CR_AWD3CH_9               (0x00200U << ADC_AWD3CR_AWD3CH_Pos)  /*!< 0x00000200 */
#define ADC_AWD3CR_AWD3CH_10              (0x00400U << ADC_AWD3CR_AWD3CH_Pos)  /*!< 0x00000400 */
#define ADC_AWD3CR_AWD3CH_11              (0x00800U << ADC_AWD3CR_AWD3CH_Pos)  /*!< 0x00000800 */
#define ADC_AWD3CR_AWD3CH_12              (0x01000U << ADC_AWD3CR_AWD3CH_Pos)  /*!< 0x00001000 */
#define ADC_AWD3CR_AWD3CH_13              (0x02000U << ADC_AWD3CR_AWD3CH_Pos)  /*!< 0x00002000 */
#define ADC_AWD3CR_AWD3CH_14              (0x04000U << ADC_AWD3CR_AWD3CH_Pos)  /*!< 0x00004000 */
#define ADC_AWD3CR_AWD3CH_15              (0x08000U << ADC_AWD3CR_AWD3CH_Pos)  /*!< 0x00008000 */
#define ADC_AWD3CR_AWD3CH_16              (0x10000U << ADC_AWD3CR_AWD3CH_Pos)  /*!< 0x00010000 */
#define ADC_AWD3CR_AWD3CH_17              (0x20000U << ADC_AWD3CR_AWD3CH_Pos)  /*!< 0x00020000 */
#define ADC_AWD3CR_AWD3CH_18              (0x40000U << ADC_AWD3CR_AWD3CH_Pos)  /*!< 0x00040000 */
#define ADC_AWD3CR_AWD3CH_19              (0x80000U << ADC_AWD3CR_AWD3CH_Pos)  /*!< 0x00080000 */

/********************  Bit definition for ADC_DIFSEL register  ********************/
#define ADC_DIFSEL_DIFSEL_Pos             (0U)
#define ADC_DIFSEL_DIFSEL_Msk             (0xFFFFFU << ADC_DIFSEL_DIFSEL_Pos)  /*!< 0x000FFFFF */
#define ADC_DIFSEL_DIFSEL                 ADC_DIFSEL_DIFSEL_Msk                /*!< ADC differential modes for channels 1 to 18 */
#define ADC_DIFSEL_DIFSEL_0               (0x00001U << ADC_DIFSEL_DIFSEL_Pos)  /*!< 0x00000001 */
#define ADC_DIFSEL_DIFSEL_1               (0x00002U << ADC_DIFSEL_DIFSEL_Pos)  /*!< 0x00000002 */
#define ADC_DIFSEL_DIFSEL_2               (0x00004U << ADC_DIFSEL_DIFSEL_Pos)  /*!< 0x00000004 */
#define ADC_DIFSEL_DIFSEL_3               (0x00008U << ADC_DIFSEL_DIFSEL_Pos)  /*!< 0x00000008 */
#define ADC_DIFSEL_DIFSEL_4               (0x00010U << ADC_DIFSEL_DIFSEL_Pos)  /*!< 0x00000010 */
#define ADC_DIFSEL_DIFSEL_5               (0x00020U << ADC_DIFSEL_DIFSEL_Pos)  /*!< 0x00000020 */
#define ADC_DIFSEL_DIFSEL_6               (0x00040U << ADC_DIFSEL_DIFSEL_Pos)  /*!< 0x00000040 */
#define ADC_DIFSEL_DIFSEL_7               (0x00080U << ADC_DIFSEL_DIFSEL_Pos)  /*!< 0x00000080 */
#define ADC_DIFSEL_DIFSEL_8               (0x00100U << ADC_DIFSEL_DIFSEL_Pos)  /*!< 0x00000100 */
#define ADC_DIFSEL_DIFSEL_9               (0x00200U << ADC_DIFSEL_DIFSEL_Pos)  /*!< 0x00000200 */
#define ADC_DIFSEL_DIFSEL_10              (0x00400U << ADC_DIFSEL_DIFSEL_Pos)  /*!< 0x00000400 */
#define ADC_DIFSEL_DIFSEL_11              (0x00800U << ADC_DIFSEL_DIFSEL_Pos)  /*!< 0x00000800 */
#define ADC_DIFSEL_DIFSEL_12              (0x01000U << ADC_DIFSEL_DIFSEL_Pos)  /*!< 0x00001000 */
#define ADC_DIFSEL_DIFSEL_13              (0x02000U << ADC_DIFSEL_DIFSEL_Pos)  /*!< 0x00002000 */
#define ADC_DIFSEL_DIFSEL_14              (0x04000U << ADC_DIFSEL_DIFSEL_Pos)  /*!< 0x00004000 */
#define ADC_DIFSEL_DIFSEL_15              (0x08000U << ADC_DIFSEL_DIFSEL_Pos)  /*!< 0x00008000 */
#define ADC_DIFSEL_DIFSEL_16              (0x10000U << ADC_DIFSEL_DIFSEL_Pos)  /*!< 0x00010000 */
#define ADC_DIFSEL_DIFSEL_17              (0x20000U << ADC_DIFSEL_DIFSEL_Pos)  /*!< 0x00020000 */
#define ADC_DIFSEL_DIFSEL_18              (0x40000U << ADC_DIFSEL_DIFSEL_Pos)  /*!< 0x00040000 */
#define ADC_DIFSEL_DIFSEL_19              (0x80000U << ADC_DIFSEL_DIFSEL_Pos)  /*!< 0x00080000 */

/********************  Bit definition for ADC_CALFACT register  ********************/
#define ADC_CALFACT_CALFACT_S_Pos         (0U)
#define ADC_CALFACT_CALFACT_S_Msk         (0x7FFU << ADC_CALFACT_CALFACT_S_Pos) /*!< 0x000007FF */
#define ADC_CALFACT_CALFACT_S             ADC_CALFACT_CALFACT_S_Msk            /*!< ADC calibration factors in single-ended mode */
#define ADC_CALFACT_CALFACT_S_0           (0x001U << ADC_CALFACT_CALFACT_S_Pos) /*!< 0x00000001 */
#define ADC_CALFACT_CALFACT_S_1           (0x002U << ADC_CALFACT_CALFACT_S_Pos) /*!< 0x00000002 */
#define ADC_CALFACT_CALFACT_S_2           (0x004U << ADC_CALFACT_CALFACT_S_Pos) /*!< 0x00000004 */
#define ADC_CALFACT_CALFACT_S_3           (0x008U << ADC_CALFACT_CALFACT_S_Pos) /*!< 0x00000008 */
#define ADC_CALFACT_CALFACT_S_4           (0x010U << ADC_CALFACT_CALFACT_S_Pos) /*!< 0x00000010 */
#define ADC_CALFACT_CALFACT_S_5           (0x020U << ADC_CALFACT_CALFACT_S_Pos) /*!< 0x00000020 */
#define ADC_CALFACT_CALFACT_S_6           (0x040U << ADC_CALFACT_CALFACT_S_Pos) /*!< 0x00000040 */
#define ADC_CALFACT_CALFACT_S_7           (0x080U << ADC_CALFACT_CALFACT_S_Pos) /*!< 0x00000080 */
#define ADC_CALFACT_CALFACT_S_8           (0x100U << ADC_CALFACT_CALFACT_S_Pos) /*!< 0x00000100 */
#define ADC_CALFACT_CALFACT_S_9           (0x200U << ADC_CALFACT_CALFACT_S_Pos) /*!< 0x00000200 */
#define ADC_CALFACT_CALFACT_S_10          (0x400U << ADC_CALFACT_CALFACT_S_Pos) /*!< 0x00000400 */
#define ADC_CALFACT_CALFACT_D_Pos         (16U)
#define ADC_CALFACT_CALFACT_D_Msk         (0x7FFU << ADC_CALFACT_CALFACT_D_Pos) /*!< 0x07FF0000 */
#define ADC_CALFACT_CALFACT_D             ADC_CALFACT_CALFACT_D_Msk            /*!< ADC calibration factors in differential mode */
#define ADC_CALFACT_CALFACT_D_0           (0x001U << ADC_CALFACT_CALFACT_D_Pos) /*!< 0x00010000 */
#define ADC_CALFACT_CALFACT_D_1           (0x002U << ADC_CALFACT_CALFACT_D_Pos) /*!< 0x00020000 */
#define ADC_CALFACT_CALFACT_D_2           (0x004U << ADC_CALFACT_CALFACT_D_Pos) /*!< 0x00040000 */
#define ADC_CALFACT_CALFACT_D_3           (0x008U << ADC_CALFACT_CALFACT_D_Pos) /*!< 0x00080000 */
#define ADC_CALFACT_CALFACT_D_4           (0x010U << ADC_CALFACT_CALFACT_D_Pos) /*!< 0x00100000 */
#define ADC_CALFACT_CALFACT_D_5           (0x020U << ADC_CALFACT_CALFACT_D_Pos) /*!< 0x00200000 */
#define ADC_CALFACT_CALFACT_D_6           (0x040U << ADC_CALFACT_CALFACT_D_Pos) /*!< 0x00400000 */
#define ADC_CALFACT_CALFACT_D_7           (0x080U << ADC_CALFACT_CALFACT_D_Pos) /*!< 0x00800000 */
#define ADC_CALFACT_CALFACT_D_8           (0x100U << ADC_CALFACT_CALFACT_D_Pos) /*!< 0x01000000 */
#define ADC_CALFACT_CALFACT_D_9           (0x200U << ADC_CALFACT_CALFACT_D_Pos) /*!< 0x02000000 */
#define ADC_CALFACT_CALFACT_D_10          (0x400U << ADC_CALFACT_CALFACT_D_Pos) /*!< 0x04000000 */

/********************  Bit definition for ADC_CALFACT2 register  ********************/
#define ADC_CALFACT2_LINCALFACT_Pos       (0U)
#define ADC_CALFACT2_LINCALFACT_Msk       (0x3FFFFFFFU << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x3FFFFFFF */
#define ADC_CALFACT2_LINCALFACT           ADC_CALFACT2_LINCALFACT_Msk          /*!< ADC Linearity calibration factors */
#define ADC_CALFACT2_LINCALFACT_0         (0x00000001U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00000001 */
#define ADC_CALFACT2_LINCALFACT_1         (0x00000002U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00000002 */
#define ADC_CALFACT2_LINCALFACT_2         (0x00000004U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00000004 */
#define ADC_CALFACT2_LINCALFACT_3         (0x00000008U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00000008 */
#define ADC_CALFACT2_LINCALFACT_4         (0x00000010U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00000010 */
#define ADC_CALFACT2_LINCALFACT_5         (0x00000020U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00000020 */
#define ADC_CALFACT2_LINCALFACT_6         (0x00000040U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00000040 */
#define ADC_CALFACT2_LINCALFACT_7         (0x00000080U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00000080 */
#define ADC_CALFACT2_LINCALFACT_8         (0x00000100U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00000100 */
#define ADC_CALFACT2_LINCALFACT_9         (0x00000200U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00000200 */
#define ADC_CALFACT2_LINCALFACT_10        (0x00000400U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00000400 */
#define ADC_CALFACT2_LINCALFACT_11        (0x00000800U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00000800 */
#define ADC_CALFACT2_LINCALFACT_12        (0x00001000U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00001000 */
#define ADC_CALFACT2_LINCALFACT_13        (0x00002000U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00002000 */
#define ADC_CALFACT2_LINCALFACT_14        (0x00004000U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00004000 */
#define ADC_CALFACT2_LINCALFACT_15        (0x00008000U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00008000 */
#define ADC_CALFACT2_LINCALFACT_16        (0x00010000U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00010000 */
#define ADC_CALFACT2_LINCALFACT_17        (0x00020000U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00020000 */
#define ADC_CALFACT2_LINCALFACT_18        (0x00040000U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00040000 */
#define ADC_CALFACT2_LINCALFACT_19        (0x00080000U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00080000 */
#define ADC_CALFACT2_LINCALFACT_20        (0x00100000U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00100000 */
#define ADC_CALFACT2_LINCALFACT_21        (0x00200000U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00200000 */
#define ADC_CALFACT2_LINCALFACT_22        (0x00400000U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00400000 */
#define ADC_CALFACT2_LINCALFACT_23        (0x00800000U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x00800000 */
#define ADC_CALFACT2_LINCALFACT_24        (0x01000000U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x01000000 */
#define ADC_CALFACT2_LINCALFACT_25        (0x02000000U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x02000000 */
#define ADC_CALFACT2_LINCALFACT_26        (0x04000000U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x04000000 */
#define ADC_CALFACT2_LINCALFACT_27        (0x08000001U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x08000001 */
#define ADC_CALFACT2_LINCALFACT_28        (0x10000000U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x10000000 */
#define ADC_CALFACT2_LINCALFACT_29        (0x20000000U << ADC_CALFACT2_LINCALFACT_Pos) /*!< 0x20000000 */

/********************  Bit definition for ADC2_OR - Option Register  ********************/
#define ADC2_OR_VDDCOREEN_Pos            (0U)
#define ADC2_OR_VDDCOREEN_Msk            (0x1U << ADC2_OR_VDDCOREEN_Pos) /*!< 0x00000001 */
#define ADC2_OR_VDDCOREEN                ADC2_OR_VDDCOREEN_Msk          /*!< ADC2 Option Register  - VDDCORE enable bit */

/*************************  ADC Common registers  *****************************/
/********************  Bit definition for ADC_CSR register  ********************/
#define ADC_CSR_ADRDY_MST_Pos          (0U)
#define ADC_CSR_ADRDY_MST_Msk          (0x1U << ADC_CSR_ADRDY_MST_Pos)   /*!< 0x00000001 */
#define ADC_CSR_ADRDY_MST              ADC_CSR_ADRDY_MST_Msk             /*!< Master ADC ready */
#define ADC_CSR_EOSMP_MST_Pos          (1U)
#define ADC_CSR_EOSMP_MST_Msk          (0x1U << ADC_CSR_EOSMP_MST_Pos) /*!< 0x00000002 */
#define ADC_CSR_EOSMP_MST              ADC_CSR_EOSMP_MST_Msk       /*!< End of sampling phase flag of the master ADC */
#define ADC_CSR_EOC_MST_Pos      (2U)
#define ADC_CSR_EOC_MST_Msk      (0x1U << ADC_CSR_EOC_MST_Pos) /*!< 0x00000004 */
#define ADC_CSR_EOC_MST          ADC_CSR_EOC_MST_Msk         /*!< End of regular conversion of the master ADC */
#define ADC_CSR_EOS_MST_Pos      (3U)
#define ADC_CSR_EOS_MST_Msk      (0x1U << ADC_CSR_EOS_MST_Pos) /*!< 0x00000008 */
#define ADC_CSR_EOS_MST          ADC_CSR_EOS_MST_Msk         /*!< End of regular sequence flag of the master ADC */
#define ADC_CSR_OVR_MST_Pos      (4U)
#define ADC_CSR_OVR_MST_Msk      (0x1U << ADC_CSR_OVR_MST_Pos) /*!< 0x00000010 */
#define ADC_CSR_OVR_MST          ADC_CSR_OVR_MST_Msk         /*!< Overrun flag of the master ADC */
#define ADC_CSR_JEOC_MST_Pos     (5U)
#define ADC_CSR_JEOC_MST_Msk     (0x1U << ADC_CSR_JEOC_MST_Pos) /*!< 0x00000020 */
#define ADC_CSR_JEOC_MST         ADC_CSR_JEOC_MST_Msk        /*!< End of injected conversion of the master ADC */
#define ADC_CSR_JEOS_MST_Pos     (6U)
#define ADC_CSR_JEOS_MST_Msk     (0x1U << ADC_CSR_JEOS_MST_Pos) /*!< 0x00000040 */
#define ADC_CSR_JEOS_MST         ADC_CSR_JEOS_MST_Msk        /*!< End of injected sequence flag of the master ADC */
#define ADC_CSR_AWD1_MST_Pos           (7U)
#define ADC_CSR_AWD1_MST_Msk           (0x1U << ADC_CSR_AWD1_MST_Pos)    /*!< 0x00000080 */
#define ADC_CSR_AWD1_MST               ADC_CSR_AWD1_MST_Msk              /*!< Analog watchdog 1 flag of the master ADC */
#define ADC_CSR_AWD2_MST_Pos           (8U)
#define ADC_CSR_AWD2_MST_Msk           (0x1U << ADC_CSR_AWD2_MST_Pos)    /*!< 0x00000100 */
#define ADC_CSR_AWD2_MST               ADC_CSR_AWD2_MST_Msk              /*!< Analog watchdog 2 flag of the master ADC */
#define ADC_CSR_AWD3_MST_Pos           (9U)
#define ADC_CSR_AWD3_MST_Msk           (0x1U << ADC_CSR_AWD3_MST_Pos)    /*!< 0x00000200 */
#define ADC_CSR_AWD3_MST               ADC_CSR_AWD3_MST_Msk              /*!< Analog watchdog 3 flag of the master ADC */
#define ADC_CSR_JQOVF_MST_Pos          (10U)
#define ADC_CSR_JQOVF_MST_Msk          (0x1U << ADC_CSR_JQOVF_MST_Pos)   /*!< 0x00000400 */
#define ADC_CSR_JQOVF_MST              ADC_CSR_JQOVF_MST_Msk             /*!< Injected context queue overflow flag of the master ADC */
#define ADC_CSR_ADRDY_SLV_Pos          (16U)
#define ADC_CSR_ADRDY_SLV_Msk          (0x1U << ADC_CSR_ADRDY_SLV_Pos)   /*!< 0x00010000 */
#define ADC_CSR_ADRDY_SLV              ADC_CSR_ADRDY_SLV_Msk             /*!< Slave ADC ready */
#define ADC_CSR_EOSMP_SLV_Pos    (17U)
#define ADC_CSR_EOSMP_SLV_Msk    (0x1U << ADC_CSR_EOSMP_SLV_Pos) /*!< 0x00020000 */
#define ADC_CSR_EOSMP_SLV        ADC_CSR_EOSMP_SLV_Msk       /*!< End of sampling phase flag of the slave ADC */
#define ADC_CSR_EOC_SLV_Pos      (18U)
#define ADC_CSR_EOC_SLV_Msk      (0x1U << ADC_CSR_EOC_SLV_Pos) /*!< 0x00040000 */
#define ADC_CSR_EOC_SLV          ADC_CSR_EOC_SLV_Msk         /*!< End of regular conversion of the slave ADC */
#define ADC_CSR_EOS_SLV_Pos      (19U)
#define ADC_CSR_EOS_SLV_Msk      (0x1U << ADC_CSR_EOS_SLV_Pos) /*!< 0x00080000 */
#define ADC_CSR_EOS_SLV          ADC_CSR_EOS_SLV_Msk         /*!< End of regular sequence flag of the slave ADC */
#define ADC_CSR_OVR_SLV_Pos      (20U)
#define ADC_CSR_OVR_SLV_Msk      (0x1U << ADC_CSR_OVR_SLV_Pos) /*!< 0x00100000 */
#define ADC_CSR_OVR_SLV          ADC_CSR_OVR_SLV_Msk         /*!< Overrun flag of the slave ADC */
#define ADC_CSR_JEOC_SLV_Pos     (21U)
#define ADC_CSR_JEOC_SLV_Msk     (0x1U << ADC_CSR_JEOC_SLV_Pos) /*!< 0x00200000 */
#define ADC_CSR_JEOC_SLV         ADC_CSR_JEOC_SLV_Msk        /*!< End of injected conversion of the slave ADC */
#define ADC_CSR_JEOS_SLV_Pos     (22U)
#define ADC_CSR_JEOS_SLV_Msk     (0x1U << ADC_CSR_JEOS_SLV_Pos) /*!< 0x00400000 */
#define ADC_CSR_JEOS_SLV         ADC_CSR_JEOS_SLV_Msk        /*!< End of injected sequence flag of the slave ADC */
#define ADC_CSR_AWD1_SLV_Pos           (23U)
#define ADC_CSR_AWD1_SLV_Msk           (0x1U << ADC_CSR_AWD1_SLV_Pos)    /*!< 0x00800000 */
#define ADC_CSR_AWD1_SLV               ADC_CSR_AWD1_SLV_Msk              /*!< Analog watchdog 1 flag of the slave ADC */
#define ADC_CSR_AWD2_SLV_Pos           (24U)
#define ADC_CSR_AWD2_SLV_Msk           (0x1U << ADC_CSR_AWD2_SLV_Pos)    /*!< 0x01000000 */
#define ADC_CSR_AWD2_SLV               ADC_CSR_AWD2_SLV_Msk              /*!< Analog watchdog 2 flag of the slave ADC */
#define ADC_CSR_AWD3_SLV_Pos           (25U)
#define ADC_CSR_AWD3_SLV_Msk           (0x1U << ADC_CSR_AWD3_SLV_Pos)    /*!< 0x02000000 */
#define ADC_CSR_AWD3_SLV               ADC_CSR_AWD3_SLV_Msk              /*!< Analog watchdog 3 flag of the slave ADC */
#define ADC_CSR_JQOVF_SLV_Pos          (26U)
#define ADC_CSR_JQOVF_SLV_Msk          (0x1U << ADC_CSR_JQOVF_SLV_Pos)   /*!< 0x04000000 */
#define ADC_CSR_JQOVF_SLV              ADC_CSR_JQOVF_SLV_Msk             /*!< Injected context queue overflow flag of the slave ADC */

/********************  Bit definition for ADC_CCR register  ********************/
#define ADC_CCR_DUAL_Pos                  (0U)
#define ADC_CCR_DUAL_Msk                  (0x1FU << ADC_CCR_DUAL_Pos)          /*!< 0x0000001F */
#define ADC_CCR_DUAL                      ADC_CCR_DUAL_Msk                     /*!< Dual ADC mode selection */
#define ADC_CCR_DUAL_0                    (0x01U << ADC_CCR_DUAL_Pos)          /*!< 0x00000001 */
#define ADC_CCR_DUAL_1                    (0x02U << ADC_CCR_DUAL_Pos)          /*!< 0x00000002 */
#define ADC_CCR_DUAL_2                    (0x04U << ADC_CCR_DUAL_Pos)          /*!< 0x00000004 */
#define ADC_CCR_DUAL_3                    (0x08U << ADC_CCR_DUAL_Pos)          /*!< 0x00000008 */
#define ADC_CCR_DUAL_4                    (0x10U << ADC_CCR_DUAL_Pos)          /*!< 0x00000010 */

#define ADC_CCR_DELAY_Pos                 (8U)
#define ADC_CCR_DELAY_Msk                 (0xFU << ADC_CCR_DELAY_Pos)          /*!< 0x00000F00 */
#define ADC_CCR_DELAY                     ADC_CCR_DELAY_Msk                    /*!< Delay between 2 sampling phases */
#define ADC_CCR_DELAY_0                   (0x1U << ADC_CCR_DELAY_Pos)          /*!< 0x00000100 */
#define ADC_CCR_DELAY_1                   (0x2U << ADC_CCR_DELAY_Pos)          /*!< 0x00000200 */
#define ADC_CCR_DELAY_2                   (0x4U << ADC_CCR_DELAY_Pos)          /*!< 0x00000400 */
#define ADC_CCR_DELAY_3                   (0x8U << ADC_CCR_DELAY_Pos)          /*!< 0x00000800 */

#define ADC_CCR_DAMDF_Pos                 (14U)
#define ADC_CCR_DAMDF_Msk                 (0x3U << ADC_CCR_DAMDF_Pos)          /*!< 0x0000C000 */
#define ADC_CCR_DAMDF                     ADC_CCR_DAMDF_Msk                    /*!< Dual ADC mode Data format */
#define ADC_CCR_DAMDF_0                   (0x1U << ADC_CCR_DAMDF_Pos)          /*!< 0x00004000 */
#define ADC_CCR_DAMDF_1                   (0x2U << ADC_CCR_DAMDF_Pos)          /*!< 0x00008000 */

#define ADC_CCR_CKMODE_Pos                (16U)
#define ADC_CCR_CKMODE_Msk                (0x3U << ADC_CCR_CKMODE_Pos)         /*!< 0x00030000 */
#define ADC_CCR_CKMODE                    ADC_CCR_CKMODE_Msk                   /*!< ADC clock mode */
#define ADC_CCR_CKMODE_0                  (0x1U << ADC_CCR_CKMODE_Pos)         /*!< 0x00010000 */
#define ADC_CCR_CKMODE_1                  (0x2U << ADC_CCR_CKMODE_Pos)         /*!< 0x00020000 */

#define ADC_CCR_PRESC_Pos                 (18U)
#define ADC_CCR_PRESC_Msk                 (0xFU << ADC_CCR_PRESC_Pos)          /*!< 0x003C0000 */
#define ADC_CCR_PRESC                     ADC_CCR_PRESC_Msk                    /*!< ADC prescaler */
#define ADC_CCR_PRESC_0                   (0x1U << ADC_CCR_PRESC_Pos)          /*!< 0x00040000 */
#define ADC_CCR_PRESC_1                   (0x2U << ADC_CCR_PRESC_Pos)          /*!< 0x00080000 */
#define ADC_CCR_PRESC_2                   (0x4U << ADC_CCR_PRESC_Pos)          /*!< 0x00100000 */
#define ADC_CCR_PRESC_3                   (0x8U << ADC_CCR_PRESC_Pos)          /*!< 0x00200000 */

#define ADC_CCR_VREFEN_Pos                (22U)
#define ADC_CCR_VREFEN_Msk                (0x1U << ADC_CCR_VREFEN_Pos)         /*!< 0x00400000 */
#define ADC_CCR_VREFEN                    ADC_CCR_VREFEN_Msk                   /*!< VREFINT enable */
#define ADC_CCR_VSENSEEN_Pos              (23U)
#define ADC_CCR_VSENSEEN_Msk              (0x1U << ADC_CCR_VSENSEEN_Pos)      /*!< 0x00800000 */
#define ADC_CCR_VSENSEEN                  ADC_CCR_VSENSEEN_Msk                /*!< Temperature sensor enable */
#define ADC_CCR_VBATEN_Pos                (24U)
#define ADC_CCR_VBATEN_Msk                (0x1U << ADC_CCR_VBATEN_Pos)         /*!< 0x01000000 */
#define ADC_CCR_VBATEN                    ADC_CCR_VBATEN_Msk                   /*!< VBAT enable */

/********************  Bit definition for ADC_CDR register  ********************/
#define ADC_CDR_RDATA_MST_Pos          (0U)
#define ADC_CDR_RDATA_MST_Msk          (0xFFFFU << ADC_CDR_RDATA_MST_Pos) /*!< 0x0000FFFF */
#define ADC_CDR_RDATA_MST              ADC_CDR_RDATA_MST_Msk             /*!< Regular Data of the master ADC */
#define ADC_CDR_RDATA_MST_0            (0x0001U << ADC_CDR_RDATA_MST_Pos) /*!< 0x00000001 */
#define ADC_CDR_RDATA_MST_1            (0x0002U << ADC_CDR_RDATA_MST_Pos) /*!< 0x00000002 */
#define ADC_CDR_RDATA_MST_2            (0x0004U << ADC_CDR_RDATA_MST_Pos) /*!< 0x00000004 */
#define ADC_CDR_RDATA_MST_3            (0x0008U << ADC_CDR_RDATA_MST_Pos) /*!< 0x00000008 */
#define ADC_CDR_RDATA_MST_4            (0x0010U << ADC_CDR_RDATA_MST_Pos) /*!< 0x00000010 */
#define ADC_CDR_RDATA_MST_5            (0x0020U << ADC_CDR_RDATA_MST_Pos) /*!< 0x00000020 */
#define ADC_CDR_RDATA_MST_6            (0x0040U << ADC_CDR_RDATA_MST_Pos) /*!< 0x00000040 */
#define ADC_CDR_RDATA_MST_7            (0x0080U << ADC_CDR_RDATA_MST_Pos) /*!< 0x00000080 */
#define ADC_CDR_RDATA_MST_8            (0x0100U << ADC_CDR_RDATA_MST_Pos) /*!< 0x00000100 */
#define ADC_CDR_RDATA_MST_9            (0x0200U << ADC_CDR_RDATA_MST_Pos) /*!< 0x00000200 */
#define ADC_CDR_RDATA_MST_10           (0x0400U << ADC_CDR_RDATA_MST_Pos) /*!< 0x00000400 */
#define ADC_CDR_RDATA_MST_11           (0x0800U << ADC_CDR_RDATA_MST_Pos) /*!< 0x00000800 */
#define ADC_CDR_RDATA_MST_12           (0x1000U << ADC_CDR_RDATA_MST_Pos) /*!< 0x00001000 */
#define ADC_CDR_RDATA_MST_13           (0x2000U << ADC_CDR_RDATA_MST_Pos) /*!< 0x00002000 */
#define ADC_CDR_RDATA_MST_14           (0x4000U << ADC_CDR_RDATA_MST_Pos) /*!< 0x00004000 */
#define ADC_CDR_RDATA_MST_15           (0x8000U << ADC_CDR_RDATA_MST_Pos) /*!< 0x00008000 */

#define ADC_CDR_RDATA_SLV_Pos          (16U)
#define ADC_CDR_RDATA_SLV_Msk          (0xFFFFU << ADC_CDR_RDATA_SLV_Pos) /*!< 0xFFFF0000 */
#define ADC_CDR_RDATA_SLV              ADC_CDR_RDATA_SLV_Msk             /*!< Regular Data of the master ADC */
#define ADC_CDR_RDATA_SLV_0            (0x0001U << ADC_CDR_RDATA_SLV_Pos) /*!< 0x00010000 */
#define ADC_CDR_RDATA_SLV_1            (0x0002U << ADC_CDR_RDATA_SLV_Pos) /*!< 0x00020000 */
#define ADC_CDR_RDATA_SLV_2            (0x0004U << ADC_CDR_RDATA_SLV_Pos) /*!< 0x00040000 */
#define ADC_CDR_RDATA_SLV_3            (0x0008U << ADC_CDR_RDATA_SLV_Pos) /*!< 0x00080000 */
#define ADC_CDR_RDATA_SLV_4            (0x0010U << ADC_CDR_RDATA_SLV_Pos) /*!< 0x00100000 */
#define ADC_CDR_RDATA_SLV_5            (0x0020U << ADC_CDR_RDATA_SLV_Pos) /*!< 0x00200000 */
#define ADC_CDR_RDATA_SLV_6            (0x0040U << ADC_CDR_RDATA_SLV_Pos) /*!< 0x00400000 */
#define ADC_CDR_RDATA_SLV_7            (0x0080U << ADC_CDR_RDATA_SLV_Pos) /*!< 0x00800000 */
#define ADC_CDR_RDATA_SLV_8            (0x0100U << ADC_CDR_RDATA_SLV_Pos) /*!< 0x01000000 */
#define ADC_CDR_RDATA_SLV_9            (0x0200U << ADC_CDR_RDATA_SLV_Pos) /*!< 0x02000000 */
#define ADC_CDR_RDATA_SLV_10           (0x0400U << ADC_CDR_RDATA_SLV_Pos) /*!< 0x04000000 */
#define ADC_CDR_RDATA_SLV_11           (0x0800U << ADC_CDR_RDATA_SLV_Pos) /*!< 0x08000000 */
#define ADC_CDR_RDATA_SLV_12           (0x1000U << ADC_CDR_RDATA_SLV_Pos) /*!< 0x10000000 */
#define ADC_CDR_RDATA_SLV_13           (0x2000U << ADC_CDR_RDATA_SLV_Pos) /*!< 0x20000000 */
#define ADC_CDR_RDATA_SLV_14           (0x4000U << ADC_CDR_RDATA_SLV_Pos) /*!< 0x40000000 */
#define ADC_CDR_RDATA_SLV_15           (0x8000U << ADC_CDR_RDATA_SLV_Pos) /*!< 0x80000000 */

/********************  Bit definition for ADC_CDR2 register  ********************/
#define ADC_CDR2_RDATA_ALT_Pos         (0U)
#define ADC_CDR2_RDATA_ALT_Msk         (0xFFFFFFFFU << ADC_CDR2_RDATA_ALT_Pos) /*!< 0xFFFFFFFF */
#define ADC_CDR2_RDATA_ALT             ADC_CDR2_RDATA_ALT_Msk            /*!< Regular Data for dual Mode */
#define ADC_CDR2_RDATA_ALT_0           (0x00000001U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00000001 */
#define ADC_CDR2_RDATA_ALT_1           (0x00000002U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00000002 */
#define ADC_CDR2_RDATA_ALT_2           (0x00000004U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00000004 */
#define ADC_CDR2_RDATA_ALT_3           (0x00000008U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00000008 */
#define ADC_CDR2_RDATA_ALT_4           (0x00000010U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00000010 */
#define ADC_CDR2_RDATA_ALT_5           (0x00000020U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00000020 */
#define ADC_CDR2_RDATA_ALT_6           (0x00000040U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00000040 */
#define ADC_CDR2_RDATA_ALT_7           (0x00000080U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00000080 */
#define ADC_CDR2_RDATA_ALT_8           (0x00000100U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00000100 */
#define ADC_CDR2_RDATA_ALT_9           (0x00000200U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00000200 */
#define ADC_CDR2_RDATA_ALT_10          (0x00000400U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00000400 */
#define ADC_CDR2_RDATA_ALT_11          (0x00000800U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00000800 */
#define ADC_CDR2_RDATA_ALT_12          (0x00001000U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00001000 */
#define ADC_CDR2_RDATA_ALT_13          (0x00002000U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00002000 */
#define ADC_CDR2_RDATA_ALT_14          (0x00004000U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00004000 */
#define ADC_CDR2_RDATA_ALT_15          (0x00008000U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00008000 */
#define ADC_CDR2_RDATA_ALT_16          (0x00010000U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00010000 */
#define ADC_CDR2_RDATA_ALT_17          (0x00020000U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00020000 */
#define ADC_CDR2_RDATA_ALT_18          (0x00040000U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00040000 */
#define ADC_CDR2_RDATA_ALT_19          (0x00080000U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00080000 */
#define ADC_CDR2_RDATA_ALT_20          (0x00100000U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00100000 */
#define ADC_CDR2_RDATA_ALT_21          (0x00200000U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00200000 */
#define ADC_CDR2_RDATA_ALT_22          (0x00400000U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00400000 */
#define ADC_CDR2_RDATA_ALT_23          (0x00800000U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x00800000 */
#define ADC_CDR2_RDATA_ALT_24          (0x01000000U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x01000000 */
#define ADC_CDR2_RDATA_ALT_25          (0x02000000U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x02000000 */
#define ADC_CDR2_RDATA_ALT_26          (0x04000000U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x04000000 */
#define ADC_CDR2_RDATA_ALT_27          (0x08000000U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x08000000 */
#define ADC_CDR2_RDATA_ALT_28          (0x10000000U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x10000000 */
#define ADC_CDR2_RDATA_ALT_29          (0x20000000U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x20000000 */
#define ADC_CDR2_RDATA_ALT_30          (0x40000000U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x40000000 */
#define ADC_CDR2_RDATA_ALT_31          (0x80000000U << ADC_CDR2_RDATA_ALT_Pos) /*!< 0x80000000 */


/*****************  Bit definition for ADC_VERR register  ******************/
#define ADC_VERR_MINREV_Pos               (0U)
#define ADC_VERR_MINREV_Msk               (0xFU << ADC_VERR_MINREV_Pos)        /*!< 0x0000000F */
#define ADC_VERR_MINREV                   ADC_VERR_MINREV_Msk                  /*!< Minor revision */
#define ADC_VERR_MINREV_0                 (0x1U << ADC_VERR_MINREV_Pos)        /*!< 0x00000001 */
#define ADC_VERR_MINREV_1                 (0x2U << ADC_VERR_MINREV_Pos)        /*!< 0x00000002 */
#define ADC_VERR_MINREV_2                 (0x4U << ADC_VERR_MINREV_Pos)        /*!< 0x00000004 */
#define ADC_VERR_MINREV_3                 (0x8U << ADC_VERR_MINREV_Pos)        /*!< 0x00000008 */
#define ADC_VERR_MAJREV_Pos               (4U)
#define ADC_VERR_MAJREV_Msk               (0xFU << ADC_VERR_MAJREV_Pos)        /*!< 0x000000F0 */
#define ADC_VERR_MAJREV                   ADC_VERR_MAJREV_Msk                  /*!< Major revision */
#define ADC_VERR_MAJREV_0                 (0x1U << ADC_VERR_MAJREV_Pos)        /*!< 0x00000010 */
#define ADC_VERR_MAJREV_1                 (0x2U << ADC_VERR_MAJREV_Pos)        /*!< 0x00000020 */
#define ADC_VERR_MAJREV_2                 (0x4U << ADC_VERR_MAJREV_Pos)        /*!< 0x00000040 */
#define ADC_VERR_MAJREV_3                 (0x8U << ADC_VERR_MAJREV_Pos)        /*!< 0x00000080 */

/*****************  Bit definition for ADC_IPDR register  ******************/
#define ADC_IPDR_ID_Pos                   (0U)
#define ADC_IPDR_ID_Msk                   (0xFFFFFFFFU << ADC_IPDR_ID_Pos)     /*!< 0xFFFFFFFF */
#define ADC_IPDR_ID                       ADC_IPDR_ID_Msk                      /*!< Peripheral identifier */
#define ADC_IPDR_ID_0                     (0x1U << ADC_IPDR_ID_Pos)            /*!< 0x00000001 */
#define ADC_IPDR_ID_1                     (0x2U << ADC_IPDR_ID_Pos)            /*!< 0x00000002 */
#define ADC_IPDR_ID_2                     (0x4U << ADC_IPDR_ID_Pos)            /*!< 0x00000004 */
#define ADC_IPDR_ID_3                     (0x8U << ADC_IPDR_ID_Pos)            /*!< 0x00000008 */
#define ADC_IPDR_ID_4                     (0x10U << ADC_IPDR_ID_Pos)           /*!< 0x00000010 */
#define ADC_IPDR_ID_5                     (0x20U << ADC_IPDR_ID_Pos)           /*!< 0x00000020 */
#define ADC_IPDR_ID_6                     (0x40U << ADC_IPDR_ID_Pos)           /*!< 0x00000040 */
#define ADC_IPDR_ID_7                     (0x80U << ADC_IPDR_ID_Pos)           /*!< 0x00000080 */
#define ADC_IPDR_ID_8                     (0x100U << ADC_IPDR_ID_Pos)          /*!< 0x00000100 */
#define ADC_IPDR_ID_9                     (0x200U << ADC_IPDR_ID_Pos)          /*!< 0x00000200 */
#define ADC_IPDR_ID_10                    (0x400U << ADC_IPDR_ID_Pos)          /*!< 0x00000400 */
#define ADC_IPDR_ID_11                    (0x800U << ADC_IPDR_ID_Pos)          /*!< 0x00000800 */
#define ADC_IPDR_ID_12                    (0x1000U << ADC_IPDR_ID_Pos)         /*!< 0x00001000 */
#define ADC_IPDR_ID_13                    (0x2000U << ADC_IPDR_ID_Pos)         /*!< 0x00002000 */
#define ADC_IPDR_ID_14                    (0x4000U << ADC_IPDR_ID_Pos)         /*!< 0x00004000 */
#define ADC_IPDR_ID_15                    (0x8000U << ADC_IPDR_ID_Pos)         /*!< 0x00008000 */
#define ADC_IPDR_ID_16                    (0x10000U << ADC_IPDR_ID_Pos)        /*!< 0x00010000 */
#define ADC_IPDR_ID_17                    (0x20000U << ADC_IPDR_ID_Pos)        /*!< 0x00020000 */
#define ADC_IPDR_ID_18                    (0x40000U << ADC_IPDR_ID_Pos)        /*!< 0x00040000 */
#define ADC_IPDR_ID_19                    (0x80000U << ADC_IPDR_ID_Pos)        /*!< 0x00080000 */
#define ADC_IPDR_ID_20                    (0x100000U << ADC_IPDR_ID_Pos)       /*!< 0x00100000 */
#define ADC_IPDR_ID_21                    (0x200000U << ADC_IPDR_ID_Pos)       /*!< 0x00200000 */
#define ADC_IPDR_ID_22                    (0x400000U << ADC_IPDR_ID_Pos)       /*!< 0x00400000 */
#define ADC_IPDR_ID_23                    (0x800000U << ADC_IPDR_ID_Pos)       /*!< 0x00800000 */
#define ADC_IPDR_ID_24                    (0x1000000U << ADC_IPDR_ID_Pos)      /*!< 0x01000000 */
#define ADC_IPDR_ID_25                    (0x2000000U << ADC_IPDR_ID_Pos)      /*!< 0x02000000 */
#define ADC_IPDR_ID_26                    (0x4000000U << ADC_IPDR_ID_Pos)      /*!< 0x04000000 */
#define ADC_IPDR_ID_27                    (0x8000000U << ADC_IPDR_ID_Pos)      /*!< 0x08000000 */
#define ADC_IPDR_ID_28                    (0x10000000U << ADC_IPDR_ID_Pos)     /*!< 0x10000000 */
#define ADC_IPDR_ID_29                    (0x20000000U << ADC_IPDR_ID_Pos)     /*!< 0x20000000 */
#define ADC_IPDR_ID_30                    (0x40000000U << ADC_IPDR_ID_Pos)     /*!< 0x40000000 */
#define ADC_IPDR_ID_31                    (0x80000000U << ADC_IPDR_ID_Pos)     /*!< 0x80000000 */

/*****************  Bit definition for ADC_SIDR register  ******************/
#define ADC_SIDR_SID_Pos                  (0U)
#define ADC_SIDR_SID_Msk                  (0xFFFFFFFFU << ADC_SIDR_SID_Pos)    /*!< 0xFFFFFFFF */
#define ADC_SIDR_SID                      ADC_SIDR_SID_Msk                     /*!< Size Identification */
#define ADC_SIDR_SID_0                    (0x1U << ADC_SIDR_SID_Pos)           /*!< 0x00000001 */
#define ADC_SIDR_SID_1                    (0x2U << ADC_SIDR_SID_Pos)           /*!< 0x00000002 */
#define ADC_SIDR_SID_2                    (0x4U << ADC_SIDR_SID_Pos)           /*!< 0x00000004 */
#define ADC_SIDR_SID_3                    (0x8U << ADC_SIDR_SID_Pos)           /*!< 0x00000008 */
#define ADC_SIDR_SID_4                    (0x10U << ADC_SIDR_SID_Pos)          /*!< 0x00000010 */
#define ADC_SIDR_SID_5                    (0x20U << ADC_SIDR_SID_Pos)          /*!< 0x00000020 */
#define ADC_SIDR_SID_6                    (0x40U << ADC_SIDR_SID_Pos)          /*!< 0x00000040 */
#define ADC_SIDR_SID_7                    (0x80U << ADC_SIDR_SID_Pos)          /*!< 0x00000080 */
#define ADC_SIDR_SID_8                    (0x100U << ADC_SIDR_SID_Pos)         /*!< 0x00000100 */
#define ADC_SIDR_SID_9                    (0x200U << ADC_SIDR_SID_Pos)         /*!< 0x00000200 */
#define ADC_SIDR_SID_10                   (0x400U << ADC_SIDR_SID_Pos)         /*!< 0x00000400 */
#define ADC_SIDR_SID_11                   (0x800U << ADC_SIDR_SID_Pos)         /*!< 0x00000800 */
#define ADC_SIDR_SID_12                   (0x1000U << ADC_SIDR_SID_Pos)        /*!< 0x00001000 */
#define ADC_SIDR_SID_13                   (0x2000U << ADC_SIDR_SID_Pos)        /*!< 0x00002000 */
#define ADC_SIDR_SID_14                   (0x4000U << ADC_SIDR_SID_Pos)        /*!< 0x00004000 */
#define ADC_SIDR_SID_15                   (0x8000U << ADC_SIDR_SID_Pos)        /*!< 0x00008000 */
#define ADC_SIDR_SID_16                   (0x10000U << ADC_SIDR_SID_Pos)       /*!< 0x00010000 */
#define ADC_SIDR_SID_17                   (0x20000U << ADC_SIDR_SID_Pos)       /*!< 0x00020000 */
#define ADC_SIDR_SID_18                   (0x40000U << ADC_SIDR_SID_Pos)       /*!< 0x00040000 */
#define ADC_SIDR_SID_19                   (0x80000U << ADC_SIDR_SID_Pos)       /*!< 0x00080000 */
#define ADC_SIDR_SID_20                   (0x100000U << ADC_SIDR_SID_Pos)      /*!< 0x00100000 */
#define ADC_SIDR_SID_21                   (0x200000U << ADC_SIDR_SID_Pos)      /*!< 0x00200000 */
#define ADC_SIDR_SID_22                   (0x400000U << ADC_SIDR_SID_Pos)      /*!< 0x00400000 */
#define ADC_SIDR_SID_23                   (0x800000U << ADC_SIDR_SID_Pos)      /*!< 0x00800000 */
#define ADC_SIDR_SID_24                   (0x1000000U << ADC_SIDR_SID_Pos)     /*!< 0x01000000 */
#define ADC_SIDR_SID_25                   (0x2000000U << ADC_SIDR_SID_Pos)     /*!< 0x02000000 */
#define ADC_SIDR_SID_26                   (0x4000000U << ADC_SIDR_SID_Pos)     /*!< 0x04000000 */
#define ADC_SIDR_SID_27                   (0x8000000U << ADC_SIDR_SID_Pos)     /*!< 0x08000000 */
#define ADC_SIDR_SID_28                   (0x10000000U << ADC_SIDR_SID_Pos)    /*!< 0x10000000 */
#define ADC_SIDR_SID_29                   (0x20000000U << ADC_SIDR_SID_Pos)    /*!< 0x20000000 */
#define ADC_SIDR_SID_30                   (0x40000000U << ADC_SIDR_SID_Pos)    /*!< 0x40000000 */
#define ADC_SIDR_SID_31                   (0x80000000U << ADC_SIDR_SID_Pos)    /*!< 0x80000000 */

/******************************************************************************/
/*                                                                            */
/*                                   VREFBUF                                  */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for VREFBUF_CSR register  ****************/
#define VREFBUF_CSR_ENVR_Pos        (0U)
#define VREFBUF_CSR_ENVR_Msk        (0x1U << VREFBUF_CSR_ENVR_Pos)             /*!< 0x00000001 */
#define VREFBUF_CSR_ENVR            VREFBUF_CSR_ENVR_Msk                       /*!<Voltage reference buffer enable */
#define VREFBUF_CSR_HIZ_Pos         (1U)
#define VREFBUF_CSR_HIZ_Msk         (0x1U << VREFBUF_CSR_HIZ_Pos)              /*!< 0x00000002 */
#define VREFBUF_CSR_HIZ             VREFBUF_CSR_HIZ_Msk                        /*!<High impedance mode             */
#define VREFBUF_CSR_VRR_Pos         (3U)
#define VREFBUF_CSR_VRR_Msk         (0x1U << VREFBUF_CSR_VRR_Pos)              /*!< 0x00000008 */
#define VREFBUF_CSR_VRR             VREFBUF_CSR_VRR_Msk                        /*!<Voltage reference buffer ready  */
#define VREFBUF_CSR_VRS_Pos         (4U)
#define VREFBUF_CSR_VRS_Msk         (0x7U << VREFBUF_CSR_VRS_Pos)              /*!< 0x00000070 */
#define VREFBUF_CSR_VRS             VREFBUF_CSR_VRS_Msk                        /*!<Voltage reference scale         */

#define VREFBUF_CSR_VRS_OUT1        ((uint32_t)0x00000000)                     /*!<Voltage reference VREF_OUT1     */
#define VREFBUF_CSR_VRS_OUT2_Pos    (4U)
#define VREFBUF_CSR_VRS_OUT2_Msk    (0x1U << VREFBUF_CSR_VRS_OUT2_Pos)         /*!< 0x00000010 */
#define VREFBUF_CSR_VRS_OUT2        VREFBUF_CSR_VRS_OUT2_Msk                   /*!<Voltage reference VREF_OUT2     */
#define VREFBUF_CSR_VRS_OUT3_Pos    (5U)
#define VREFBUF_CSR_VRS_OUT3_Msk    (0x1U << VREFBUF_CSR_VRS_OUT3_Pos)         /*!< 0x00000020 */
#define VREFBUF_CSR_VRS_OUT3        VREFBUF_CSR_VRS_OUT3_Msk                   /*!<Voltage reference VREF_OUT3     */
#define VREFBUF_CSR_VRS_OUT4_Pos    (4U)
#define VREFBUF_CSR_VRS_OUT4_Msk    (0x3U << VREFBUF_CSR_VRS_OUT4_Pos)         /*!< 0x00000030 */
#define VREFBUF_CSR_VRS_OUT4        VREFBUF_CSR_VRS_OUT4_Msk                   /*!<Voltage reference VREF_OUT4     */

/*******************  Bit definition for VREFBUF_CCR register  ****************/
#define VREFBUF_CCR_TRIM_Pos        (0U)
#define VREFBUF_CCR_TRIM_Msk        (0x3FU << VREFBUF_CCR_TRIM_Pos)            /*!< 0x0000003F */
#define VREFBUF_CCR_TRIM            VREFBUF_CCR_TRIM_Msk                       /*!<TRIM[5:0] bits (Trimming code)  */

/******************************************************************************/
/*                                                                            */
/*                 Flexible Datarate Controller Area Network                  */
/*                                                                            */
/******************************************************************************/
/*!<FDCAN control and status registers */
/*****************  Bit definition for FDCAN_CREL register  *******************/
#define FDCAN_CREL_DAY_Pos        (0U)
#define FDCAN_CREL_DAY_Msk        (0xFFU << FDCAN_CREL_DAY_Pos)                /*!< 0x000000FF */
#define FDCAN_CREL_DAY            FDCAN_CREL_DAY_Msk                           /*!<Timestamp Day                           */
#define FDCAN_CREL_MON_Pos        (8U)
#define FDCAN_CREL_MON_Msk        (0xFFU << FDCAN_CREL_MON_Pos)                /*!< 0x0000FF00 */
#define FDCAN_CREL_MON            FDCAN_CREL_MON_Msk                           /*!<Timestamp Month                         */
#define FDCAN_CREL_YEAR_Pos       (16U)
#define FDCAN_CREL_YEAR_Msk       (0xFU << FDCAN_CREL_YEAR_Pos)                /*!< 0x000F0000 */
#define FDCAN_CREL_YEAR           FDCAN_CREL_YEAR_Msk                          /*!<Timestamp Year                          */
#define FDCAN_CREL_SUBSTEP_Pos    (20U)
#define FDCAN_CREL_SUBSTEP_Msk    (0xFU << FDCAN_CREL_SUBSTEP_Pos)             /*!< 0x00F00000 */
#define FDCAN_CREL_SUBSTEP        FDCAN_CREL_SUBSTEP_Msk                       /*!<Sub-step of Core release                */
#define FDCAN_CREL_STEP_Pos       (24U)
#define FDCAN_CREL_STEP_Msk       (0xFU << FDCAN_CREL_STEP_Pos)                /*!< 0x0F000000 */
#define FDCAN_CREL_STEP           FDCAN_CREL_STEP_Msk                          /*!<Step of Core release                    */
#define FDCAN_CREL_REL_Pos        (28U)
#define FDCAN_CREL_REL_Msk        (0xFU << FDCAN_CREL_REL_Pos)                 /*!< 0xF0000000 */
#define FDCAN_CREL_REL            FDCAN_CREL_REL_Msk                           /*!<Core release                            */

/*****************  Bit definition for FDCAN_ENDN register  *******************/
#define FDCAN_ENDN_ETV_Pos        (0U)
#define FDCAN_ENDN_ETV_Msk        (0xFFFFFFFFU << FDCAN_ENDN_ETV_Pos)          /*!< 0xFFFFFFFF */
#define FDCAN_ENDN_ETV            FDCAN_ENDN_ETV_Msk                           /*!<TEndiannes Test Value                   */

/*****************  Bit definition for FDCAN_DBTP register  *******************/
#define FDCAN_DBTP_DSJW_Pos       (0U)
#define FDCAN_DBTP_DSJW_Msk       (0xFU << FDCAN_DBTP_DSJW_Pos)                /*!< 0x0000000F */
#define FDCAN_DBTP_DSJW           FDCAN_DBTP_DSJW_Msk                          /*!<Synchronization Jump Width              */
#define FDCAN_DBTP_DTSEG2_Pos     (4U)
#define FDCAN_DBTP_DTSEG2_Msk     (0xFU << FDCAN_DBTP_DTSEG2_Pos)              /*!< 0x000000F0 */
#define FDCAN_DBTP_DTSEG2         FDCAN_DBTP_DTSEG2_Msk                        /*!<Data time segment after sample point    */
#define FDCAN_DBTP_DTSEG1_Pos     (8U)
#define FDCAN_DBTP_DTSEG1_Msk     (0x1FU << FDCAN_DBTP_DTSEG1_Pos)              /*!< 0x00001F00 */
#define FDCAN_DBTP_DTSEG1         FDCAN_DBTP_DTSEG1_Msk                        /*!<Data time segment before sample point   */
#define FDCAN_DBTP_DBRP_Pos       (16U)
#define FDCAN_DBTP_DBRP_Msk       (0x1FU << FDCAN_DBTP_DBRP_Pos)               /*!< 0x001F0000 */
#define FDCAN_DBTP_DBRP           FDCAN_DBTP_DBRP_Msk                          /*!<Data BIt Rate Prescaler                 */
#define FDCAN_DBTP_TDC_Pos        (23U)
#define FDCAN_DBTP_TDC_Msk        (0x1U << FDCAN_DBTP_TDC_Pos)                 /*!< 0x00800000 */
#define FDCAN_DBTP_TDC            FDCAN_DBTP_TDC_Msk                           /*!<Transceiver Delay Compensation          */

/*****************  Bit definition for FDCAN_TEST register  *******************/
#define FDCAN_TEST_LBCK_Pos       (4U)
#define FDCAN_TEST_LBCK_Msk       (0x1U << FDCAN_TEST_LBCK_Pos)                /*!< 0x00000010 */
#define FDCAN_TEST_LBCK           FDCAN_TEST_LBCK_Msk                          /*!<Loop Back mode                           */
#define FDCAN_TEST_TX_Pos         (5U)
#define FDCAN_TEST_TX_Msk         (0x3U << FDCAN_TEST_TX_Pos)                  /*!< 0x00000060 */
#define FDCAN_TEST_TX             FDCAN_TEST_TX_Msk                            /*!<Control of Transmit Pin                  */
#define FDCAN_TEST_RX_Pos         (7U)
#define FDCAN_TEST_RX_Msk         (0x1U << FDCAN_TEST_RX_Pos)                  /*!< 0x00000080 */
#define FDCAN_TEST_RX             FDCAN_TEST_RX_Msk                            /*!<Receive Pin                              */

/*****************  Bit definition for FDCAN_RWD register  ********************/
#define FDCAN_RWD_WDC_Pos         (0U)
#define FDCAN_RWD_WDC_Msk         (0xFFU << FDCAN_RWD_WDC_Pos)                  /*!< 0x000000FF */
#define FDCAN_RWD_WDC             FDCAN_RWD_WDC_Msk                            /*!<Watchdog configuration                   */
#define FDCAN_RWD_WDV_Pos         (8U)
#define FDCAN_RWD_WDV_Msk         (0xFFU << FDCAN_RWD_WDV_Pos)                  /*!< 0x0000FF00 */
#define FDCAN_RWD_WDV             FDCAN_RWD_WDV_Msk                            /*!<Watchdog value                           */

/*****************  Bit definition for FDCAN_CCCR register  ********************/
#define FDCAN_CCCR_INIT_Pos       (0U)
#define FDCAN_CCCR_INIT_Msk       (0x1U << FDCAN_CCCR_INIT_Pos)                /*!< 0x00000001 */
#define FDCAN_CCCR_INIT           FDCAN_CCCR_INIT_Msk                          /*!<Initialization                           */
#define FDCAN_CCCR_CCE_Pos        (1U)
#define FDCAN_CCCR_CCE_Msk        (0x1U << FDCAN_CCCR_CCE_Pos)                 /*!< 0x00000002 */
#define FDCAN_CCCR_CCE            FDCAN_CCCR_CCE_Msk                           /*!<Configuration Change Enable              */
#define FDCAN_CCCR_ASM_Pos        (2U)
#define FDCAN_CCCR_ASM_Msk        (0x1U << FDCAN_CCCR_ASM_Pos)                 /*!< 0x00000004 */
#define FDCAN_CCCR_ASM            FDCAN_CCCR_ASM_Msk                           /*!<ASM Restricted Operation Mode            */
#define FDCAN_CCCR_CSA_Pos        (3U)
#define FDCAN_CCCR_CSA_Msk        (0x1U << FDCAN_CCCR_CSA_Pos)                 /*!< 0x00000008 */
#define FDCAN_CCCR_CSA            FDCAN_CCCR_CSA_Msk                           /*!<Clock Stop Acknowledge                   */
#define FDCAN_CCCR_CSR_Pos        (4U)
#define FDCAN_CCCR_CSR_Msk        (0x1U << FDCAN_CCCR_CSR_Pos)                 /*!< 0x00000010 */
#define FDCAN_CCCR_CSR            FDCAN_CCCR_CSR_Msk                           /*!<Clock Stop Request                       */
#define FDCAN_CCCR_MON_Pos        (5U)
#define FDCAN_CCCR_MON_Msk        (0x1U << FDCAN_CCCR_MON_Pos)                 /*!< 0x00000020 */
#define FDCAN_CCCR_MON            FDCAN_CCCR_MON_Msk                           /*!<Bus Monitoring Mode                      */
#define FDCAN_CCCR_DAR_Pos        (6U)
#define FDCAN_CCCR_DAR_Msk        (0x1U << FDCAN_CCCR_DAR_Pos)                 /*!< 0x00000040 */
#define FDCAN_CCCR_DAR            FDCAN_CCCR_DAR_Msk                           /*!<Disable Automatic Retransmission         */
#define FDCAN_CCCR_TEST_Pos       (7U)
#define FDCAN_CCCR_TEST_Msk       (0x1U << FDCAN_CCCR_TEST_Pos)                /*!< 0x00000080 */
#define FDCAN_CCCR_TEST           FDCAN_CCCR_TEST_Msk                          /*!<Test Mode Enable                         */
#define FDCAN_CCCR_FDOE_Pos       (8U)
#define FDCAN_CCCR_FDOE_Msk       (0x1U << FDCAN_CCCR_FDOE_Pos)                /*!< 0x00000100 */
#define FDCAN_CCCR_FDOE           FDCAN_CCCR_FDOE_Msk                          /*!<FD Operation Enable                      */
#define FDCAN_CCCR_BRSE_Pos       (9U)
#define FDCAN_CCCR_BRSE_Msk       (0x1U << FDCAN_CCCR_BRSE_Pos)                /*!< 0x00000200 */
#define FDCAN_CCCR_BRSE           FDCAN_CCCR_BRSE_Msk                          /*!<FDCAN Bit Rate Switching                 */
#define FDCAN_CCCR_PXHD_Pos       (12U)
#define FDCAN_CCCR_PXHD_Msk       (0x1U << FDCAN_CCCR_PXHD_Pos)                /*!< 0x00001000 */
#define FDCAN_CCCR_PXHD           FDCAN_CCCR_PXHD_Msk                          /*!<Protocol Exception Handling Disable      */
#define FDCAN_CCCR_EFBI_Pos       (13U)
#define FDCAN_CCCR_EFBI_Msk       (0x1U << FDCAN_CCCR_EFBI_Pos)                /*!< 0x00002000 */
#define FDCAN_CCCR_EFBI           FDCAN_CCCR_EFBI_Msk                          /*!<Edge Filtering during Bus Integration    */
#define FDCAN_CCCR_TXP_Pos        (14U)
#define FDCAN_CCCR_TXP_Msk        (0x1U << FDCAN_CCCR_TXP_Pos)                 /*!< 0x00004000 */
#define FDCAN_CCCR_TXP            FDCAN_CCCR_TXP_Msk                           /*!<Two CAN bit times Pause                  */
#define FDCAN_CCCR_NISO_Pos       (15U)
#define FDCAN_CCCR_NISO_Msk       (0x1U << FDCAN_CCCR_NISO_Pos)                /*!< 0x00008000 */
#define FDCAN_CCCR_NISO           FDCAN_CCCR_NISO_Msk                          /*!<Non ISO Operation                        */

/*****************  Bit definition for FDCAN_NBTP register  ********************/
#define FDCAN_NBTP_NTSEG2_Pos     (0U)
#define FDCAN_NBTP_NTSEG2_Msk     (0x7FU << FDCAN_NBTP_NTSEG2_Pos)             /*!< 0x0000007F */
#define FDCAN_NBTP_NTSEG2         FDCAN_NBTP_NTSEG2_Msk                        /*!<Nominal Time segment after sample point  */
#define FDCAN_NBTP_NTSEG1_Pos     (8U)
#define FDCAN_NBTP_NTSEG1_Msk     (0xFFU << FDCAN_NBTP_NTSEG1_Pos)             /*!< 0x0000FF00 */
#define FDCAN_NBTP_NTSEG1         FDCAN_NBTP_NTSEG1_Msk                        /*!<Nominal Time segment before sample point */
#define FDCAN_NBTP_NBRP_Pos       (16U)
#define FDCAN_NBTP_NBRP_Msk       (0x1FFU << FDCAN_NBTP_NBRP_Pos)              /*!< 0x01FF0000 */
#define FDCAN_NBTP_NBRP           FDCAN_NBTP_NBRP_Msk                          /*!<Bit Rate Prescaler                       */
#define FDCAN_NBTP_NSJW_Pos       (25U)
#define FDCAN_NBTP_NSJW_Msk       (0x7FU << FDCAN_NBTP_NSJW_Pos)               /*!< 0xFE000000 */
#define FDCAN_NBTP_NSJW           FDCAN_NBTP_NSJW_Msk                          /*!<Nominal (Re)Synchronization Jump Width   */

/*****************  Bit definition for FDCAN_TSCC register  ********************/
#define FDCAN_TSCC_TSS_Pos        (0U)
#define FDCAN_TSCC_TSS_Msk        (0x3U << FDCAN_TSCC_TSS_Pos)                 /*!< 0x00000003 */
#define FDCAN_TSCC_TSS            FDCAN_TSCC_TSS_Msk                           /*!<Timestamp Select                         */
#define FDCAN_TSCC_TCP_Pos        (16U)
#define FDCAN_TSCC_TCP_Msk        (0xFU << FDCAN_TSCC_TCP_Pos)                 /*!< 0x000F0000 */
#define FDCAN_TSCC_TCP            FDCAN_TSCC_TCP_Msk                           /*!<Timestamp Counter Prescaler              */

/*****************  Bit definition for FDCAN_TSCV register  ********************/
#define FDCAN_TSCV_TSC_Pos        (0U)
#define FDCAN_TSCV_TSC_Msk        (0xFFFFU << FDCAN_TSCV_TSC_Pos)              /*!< 0x0000FFFF */
#define FDCAN_TSCV_TSC            FDCAN_TSCV_TSC_Msk                           /*!<Timestamp Counter                        */

/*****************  Bit definition for FDCAN_TOCC register  ********************/
#define FDCAN_TOCC_ETOC_Pos       (0U)
#define FDCAN_TOCC_ETOC_Msk       (0x1U << FDCAN_TOCC_ETOC_Pos)                /*!< 0x00000001 */
#define FDCAN_TOCC_ETOC           FDCAN_TOCC_ETOC_Msk                          /*!<Enable Timeout Counter                   */
#define FDCAN_TOCC_TOS_Pos        (1U)
#define FDCAN_TOCC_TOS_Msk        (0x3U << FDCAN_TOCC_TOS_Pos)                 /*!< 0x00000006 */
#define FDCAN_TOCC_TOS            FDCAN_TOCC_TOS_Msk                           /*!<Timeout Select                           */
#define FDCAN_TOCC_TOP_Pos        (16U)
#define FDCAN_TOCC_TOP_Msk        (0xFFFFU << FDCAN_TOCC_TOP_Pos)              /*!< 0xFFFF0000 */
#define FDCAN_TOCC_TOP            FDCAN_TOCC_TOP_Msk                           /*!<Timeout Period                           */

/*****************  Bit definition for FDCAN_TOCV register  ********************/
#define FDCAN_TOCV_TOC_Pos        (0U)
#define FDCAN_TOCV_TOC_Msk        (0xFFFFU << FDCAN_TOCV_TOC_Pos)              /*!< 0x0000FFFF */
#define FDCAN_TOCV_TOC            FDCAN_TOCV_TOC_Msk                           /*!<Timeout Counter                          */

/*****************  Bit definition for FDCAN_ECR register  *********************/
#define FDCAN_ECR_TEC_Pos         (0U)
#define FDCAN_ECR_TEC_Msk         (0xFFU << FDCAN_ECR_TEC_Pos)                 /*!< 0x0000000F */
#define FDCAN_ECR_TEC             FDCAN_ECR_TEC_Msk                            /*!<Transmit Error Counter                   */
#define FDCAN_ECR_REC_Pos         (8U)
#define FDCAN_ECR_REC_Msk         (0x7FU << FDCAN_ECR_REC_Pos)                 /*!< 0x00007F00 */
#define FDCAN_ECR_REC             FDCAN_ECR_REC_Msk                            /*!<Receive Error Counter                    */
#define FDCAN_ECR_RP_Pos          (15U)
#define FDCAN_ECR_RP_Msk          (0x1U << FDCAN_ECR_RP_Pos)                   /*!< 0x00008000 */
#define FDCAN_ECR_RP              FDCAN_ECR_RP_Msk                             /*!<Receive Error Passive                    */
#define FDCAN_ECR_CEL_Pos         (16U)
#define FDCAN_ECR_CEL_Msk         (0xFFU << FDCAN_ECR_CEL_Pos)                 /*!< 0x00FF0000 */
#define FDCAN_ECR_CEL             FDCAN_ECR_CEL_Msk                            /*!<CAN Error Logging                        */

/*****************  Bit definition for FDCAN_PSR register  *********************/
#define FDCAN_PSR_LEC_Pos         (0U)
#define FDCAN_PSR_LEC_Msk         (0x7U << FDCAN_PSR_LEC_Pos)                  /*!< 0x00000007 */
#define FDCAN_PSR_LEC             FDCAN_PSR_LEC_Msk                            /*!<Last Error Code                          */
#define FDCAN_PSR_ACT_Pos         (3U)
#define FDCAN_PSR_ACT_Msk         (0x3U << FDCAN_PSR_ACT_Pos)                  /*!< 0x00000018 */
#define FDCAN_PSR_ACT             FDCAN_PSR_ACT_Msk                            /*!<Activity                                 */
#define FDCAN_PSR_EP_Pos          (5U)
#define FDCAN_PSR_EP_Msk          (0x1U << FDCAN_PSR_EP_Pos)                   /*!< 0x00000020 */
#define FDCAN_PSR_EP              FDCAN_PSR_EP_Msk                             /*!<Error Passive                            */
#define FDCAN_PSR_EW_Pos          (6U)
#define FDCAN_PSR_EW_Msk          (0x1U << FDCAN_PSR_EW_Pos)                   /*!< 0x00000040 */
#define FDCAN_PSR_EW              FDCAN_PSR_EW_Msk                             /*!<Warning Status                           */
#define FDCAN_PSR_BO_Pos          (7U)
#define FDCAN_PSR_BO_Msk          (0x1U << FDCAN_PSR_BO_Pos)                   /*!< 0x00000080 */
#define FDCAN_PSR_BO              FDCAN_PSR_BO_Msk                             /*!<Bus_Off Status                           */
#define FDCAN_PSR_DLEC_Pos        (8U)
#define FDCAN_PSR_DLEC_Msk        (0x7U << FDCAN_PSR_DLEC_Pos)                 /*!< 0x00000700 */
#define FDCAN_PSR_DLEC            FDCAN_PSR_DLEC_Msk                           /*!<Data Last Error Code                     */
#define FDCAN_PSR_RESI_Pos        (11U)
#define FDCAN_PSR_RESI_Msk        (0x1U << FDCAN_PSR_RESI_Pos)                 /*!< 0x00000800 */
#define FDCAN_PSR_RESI            FDCAN_PSR_RESI_Msk                           /*!<ESI flag of last received FDCAN Message  */
#define FDCAN_PSR_RBRS_Pos        (12U)
#define FDCAN_PSR_RBRS_Msk        (0x1U << FDCAN_PSR_RBRS_Pos)                 /*!< 0x00001000 */
#define FDCAN_PSR_RBRS            FDCAN_PSR_RBRS_Msk                           /*!<BRS flag of last received FDCAN Message  */
#define FDCAN_PSR_REDL_Pos        (13U)
#define FDCAN_PSR_REDL_Msk        (0x1U << FDCAN_PSR_REDL_Pos)                 /*!< 0x00002000 */
#define FDCAN_PSR_REDL            FDCAN_PSR_REDL_Msk                           /*!<Received FDCAN Message                   */
#define FDCAN_PSR_PXE_Pos         (14U)
#define FDCAN_PSR_PXE_Msk         (0x1U << FDCAN_PSR_PXE_Pos)                  /*!< 0x00004000 */
#define FDCAN_PSR_PXE             FDCAN_PSR_PXE_Msk                            /*!<Protocol Exception Event                 */
#define FDCAN_PSR_TDCV_Pos        (16U)
#define FDCAN_PSR_TDCV_Msk        (0x7FU << FDCAN_PSR_TDCV_Pos)                /*!< 0x007F0000 */
#define FDCAN_PSR_TDCV            FDCAN_PSR_TDCV_Msk                           /*!<Transmitter Delay Compensation Value     */

/*****************  Bit definition for FDCAN_TDCR register  ********************/
#define FDCAN_TDCR_TDCF_Pos       (0U)
#define FDCAN_TDCR_TDCF_Msk       (0x7FU << FDCAN_TDCR_TDCF_Pos)               /*!< 0x0000007F */
#define FDCAN_TDCR_TDCF           FDCAN_TDCR_TDCF_Msk                          /*!<Transmitter Delay Compensation Filter    */
#define FDCAN_TDCR_TDCO_Pos       (8U)
#define FDCAN_TDCR_TDCO_Msk       (0x7FU << FDCAN_TDCR_TDCO_Pos)               /*!< 0x00007F00 */
#define FDCAN_TDCR_TDCO           FDCAN_TDCR_TDCO_Msk                          /*!<Transmitter Delay Compensation Offset    */

/*****************  Bit definition for FDCAN_IR register  **********************/
#define FDCAN_IR_RF0N_Pos         (0U)
#define FDCAN_IR_RF0N_Msk         (0x1U << FDCAN_IR_RF0N_Pos)                  /*!< 0x00000001 */
#define FDCAN_IR_RF0N             FDCAN_IR_RF0N_Msk                            /*!<Rx FIFO 0 New Message                    */
#define FDCAN_IR_RF0W_Pos         (1U)
#define FDCAN_IR_RF0W_Msk         (0x1U << FDCAN_IR_RF0W_Pos)                  /*!< 0x00000002 */
#define FDCAN_IR_RF0W             FDCAN_IR_RF0W_Msk                            /*!<Rx FIFO 0 Watermark Reached              */
#define FDCAN_IR_RF0F_Pos         (2U)
#define FDCAN_IR_RF0F_Msk         (0x1U << FDCAN_IR_RF0F_Pos)                  /*!< 0x00000004 */
#define FDCAN_IR_RF0F             FDCAN_IR_RF0F_Msk                            /*!<Rx FIFO 0 Full                           */
#define FDCAN_IR_RF0L_Pos         (3U)
#define FDCAN_IR_RF0L_Msk         (0x1U << FDCAN_IR_RF0L_Pos)                  /*!< 0x00000008 */
#define FDCAN_IR_RF0L             FDCAN_IR_RF0L_Msk                            /*!<Rx FIFO 0 Message Lost                   */
#define FDCAN_IR_RF1N_Pos         (4U)
#define FDCAN_IR_RF1N_Msk         (0x1U << FDCAN_IR_RF1N_Pos)                  /*!< 0x00000010 */
#define FDCAN_IR_RF1N             FDCAN_IR_RF1N_Msk                            /*!<Rx FIFO 1 New Message                    */
#define FDCAN_IR_RF1W_Pos         (5U)
#define FDCAN_IR_RF1W_Msk         (0x1U << FDCAN_IR_RF1W_Pos)                  /*!< 0x00000020 */
#define FDCAN_IR_RF1W             FDCAN_IR_RF1W_Msk                            /*!<Rx FIFO 1 Watermark Reached              */
#define FDCAN_IR_RF1F_Pos         (6U)
#define FDCAN_IR_RF1F_Msk         (0x1U << FDCAN_IR_RF1F_Pos)                  /*!< 0x00000040 */
#define FDCAN_IR_RF1F             FDCAN_IR_RF1F_Msk                            /*!<Rx FIFO 1 Full                           */
#define FDCAN_IR_RF1L_Pos         (7U)
#define FDCAN_IR_RF1L_Msk         (0x1U << FDCAN_IR_RF1L_Pos)                  /*!< 0x00000080 */
#define FDCAN_IR_RF1L             FDCAN_IR_RF1L_Msk                            /*!<Rx FIFO 1 Message Lost                   */
#define FDCAN_IR_HPM_Pos          (8U)
#define FDCAN_IR_HPM_Msk          (0x1U << FDCAN_IR_HPM_Pos)                   /*!< 0x00000100 */
#define FDCAN_IR_HPM              FDCAN_IR_HPM_Msk                             /*!<High Priority Message                    */
#define FDCAN_IR_TC_Pos           (9U)
#define FDCAN_IR_TC_Msk           (0x1U << FDCAN_IR_TC_Pos)                    /*!< 0x00000200 */
#define FDCAN_IR_TC               FDCAN_IR_TC_Msk                              /*!<Transmission Completed                   */
#define FDCAN_IR_TCF_Pos          (10U)
#define FDCAN_IR_TCF_Msk          (0x1U << FDCAN_IR_TCF_Pos)                   /*!< 0x00000400 */
#define FDCAN_IR_TCF              FDCAN_IR_TCF_Msk                             /*!<Transmission Cancellation Finished       */
#define FDCAN_IR_TFE_Pos          (11U)
#define FDCAN_IR_TFE_Msk          (0x1U << FDCAN_IR_TFE_Pos)                   /*!< 0x00000800 */
#define FDCAN_IR_TFE              FDCAN_IR_TFE_Msk                             /*!<Tx FIFO Empty                            */
#define FDCAN_IR_TEFN_Pos         (12U)
#define FDCAN_IR_TEFN_Msk         (0x1U << FDCAN_IR_TEFN_Pos)                  /*!< 0x00001000 */
#define FDCAN_IR_TEFN             FDCAN_IR_TEFN_Msk                            /*!<Tx Event FIFO New Entry                  */
#define FDCAN_IR_TEFW_Pos         (13U)
#define FDCAN_IR_TEFW_Msk         (0x1U << FDCAN_IR_TEFW_Pos)                  /*!< 0x00002000 */
#define FDCAN_IR_TEFW             FDCAN_IR_TEFW_Msk                            /*!<Tx Event FIFO Watermark Reached          */
#define FDCAN_IR_TEFF_Pos         (14U)
#define FDCAN_IR_TEFF_Msk         (0x1U << FDCAN_IR_TEFF_Pos)                  /*!< 0x00004000 */
#define FDCAN_IR_TEFF             FDCAN_IR_TEFF_Msk                            /*!<Tx Event FIFO Full                       */
#define FDCAN_IR_TEFL_Pos         (15U)
#define FDCAN_IR_TEFL_Msk         (0x1U << FDCAN_IR_TEFL_Pos)                  /*!< 0x00008000 */
#define FDCAN_IR_TEFL             FDCAN_IR_TEFL_Msk                            /*!<Tx Event FIFO Element Lost               */
#define FDCAN_IR_TSW_Pos          (16U)
#define FDCAN_IR_TSW_Msk          (0x1U << FDCAN_IR_TSW_Pos)                   /*!< 0x00010000 */
#define FDCAN_IR_TSW              FDCAN_IR_TSW_Msk                             /*!<Timestamp Wraparound                     */
#define FDCAN_IR_MRAF_Pos         (17U)
#define FDCAN_IR_MRAF_Msk         (0x1U << FDCAN_IR_MRAF_Pos)                  /*!< 0x00020000 */
#define FDCAN_IR_MRAF             FDCAN_IR_MRAF_Msk                            /*!<Message RAM Access Failure               */
#define FDCAN_IR_TOO_Pos          (18U)
#define FDCAN_IR_TOO_Msk          (0x1U << FDCAN_IR_TOO_Pos)                   /*!< 0x00040000 */
#define FDCAN_IR_TOO              FDCAN_IR_TOO_Msk                             /*!<Timeout Occurred                         */
#define FDCAN_IR_DRX_Pos          (19U)
#define FDCAN_IR_DRX_Msk          (0x1U << FDCAN_IR_DRX_Pos)                   /*!< 0x00080000 */
#define FDCAN_IR_DRX              FDCAN_IR_DRX_Msk                             /*!<Message stored to Dedicated Rx Buffer    */
#define FDCAN_IR_ELO_Pos          (22U)
#define FDCAN_IR_ELO_Msk          (0x1U << FDCAN_IR_ELO_Pos)                   /*!< 0x00400000 */
#define FDCAN_IR_ELO              FDCAN_IR_ELO_Msk                             /*!<Error Logging Overflow                   */
#define FDCAN_IR_EP_Pos           (23U)
#define FDCAN_IR_EP_Msk           (0x1U << FDCAN_IR_EP_Pos)                    /*!< 0x00800000 */
#define FDCAN_IR_EP               FDCAN_IR_EP_Msk                              /*!<Error Passive                            */
#define FDCAN_IR_EW_Pos           (24U)
#define FDCAN_IR_EW_Msk           (0x1U << FDCAN_IR_EW_Pos)                    /*!< 0x01000000 */
#define FDCAN_IR_EW               FDCAN_IR_EW_Msk                              /*!<Warning Status                           */
#define FDCAN_IR_BO_Pos           (25U)
#define FDCAN_IR_BO_Msk           (0x1U << FDCAN_IR_BO_Pos)                    /*!< 0x02000000 */
#define FDCAN_IR_BO               FDCAN_IR_BO_Msk                              /*!<Bus_Off Status                           */
#define FDCAN_IR_WDI_Pos          (26U)
#define FDCAN_IR_WDI_Msk          (0x1U << FDCAN_IR_WDI_Pos)                   /*!< 0x04000000 */
#define FDCAN_IR_WDI              FDCAN_IR_WDI_Msk                             /*!<Watchdog Interrupt                       */
#define FDCAN_IR_PEA_Pos          (27U)
#define FDCAN_IR_PEA_Msk          (0x1U << FDCAN_IR_PEA_Pos)                   /*!< 0x08000000 */
#define FDCAN_IR_PEA              FDCAN_IR_PEA_Msk                             /*!<Protocol Error in Arbitration Phase      */
#define FDCAN_IR_PED_Pos          (28U)
#define FDCAN_IR_PED_Msk          (0x1U << FDCAN_IR_PED_Pos)                   /*!< 0x10000000 */
#define FDCAN_IR_PED              FDCAN_IR_PED_Msk                             /*!<Protocol Error in Data Phase             */
#define FDCAN_IR_ARA_Pos          (29U)
#define FDCAN_IR_ARA_Msk          (0x1U << FDCAN_IR_ARA_Pos)                   /*!< 0x20000000 */
#define FDCAN_IR_ARA              FDCAN_IR_ARA_Msk                             /*!<Access to Reserved Address               */

/*****************  Bit definition for FDCAN_IE register  **********************/
#define FDCAN_IE_RF0NE_Pos        (0U)
#define FDCAN_IE_RF0NE_Msk        (0x1U << FDCAN_IE_RF0NE_Pos)                 /*!< 0x00000001 */
#define FDCAN_IE_RF0NE            FDCAN_IE_RF0NE_Msk                           /*!<Rx FIFO 0 New Message Enable                 */
#define FDCAN_IE_RF0WE_Pos        (1U)
#define FDCAN_IE_RF0WE_Msk        (0x1U << FDCAN_IE_RF0WE_Pos)                 /*!< 0x00000002 */
#define FDCAN_IE_RF0WE            FDCAN_IE_RF0WE_Msk                           /*!<Rx FIFO 0 Watermark Reached Enable           */
#define FDCAN_IE_RF0FE_Pos        (2U)
#define FDCAN_IE_RF0FE_Msk        (0x1U << FDCAN_IE_RF0FE_Pos)                 /*!< 0x00000004 */
#define FDCAN_IE_RF0FE            FDCAN_IE_RF0FE_Msk                           /*!<Rx FIFO 0 Full Enable                        */
#define FDCAN_IE_RF0LE_Pos        (3U)
#define FDCAN_IE_RF0LE_Msk        (0x1U << FDCAN_IE_RF0LE_Pos)                 /*!< 0x00000008 */
#define FDCAN_IE_RF0LE            FDCAN_IE_RF0LE_Msk                           /*!<Rx FIFO 0 Message Lost Enable                */
#define FDCAN_IE_RF1NE_Pos        (4U)
#define FDCAN_IE_RF1NE_Msk        (0x1U << FDCAN_IE_RF1NE_Pos)                 /*!< 0x00000010 */
#define FDCAN_IE_RF1NE            FDCAN_IE_RF1NE_Msk                           /*!<Rx FIFO 1 New Message Enable                 */
#define FDCAN_IE_RF1WE_Pos        (5U)
#define FDCAN_IE_RF1WE_Msk        (0x1U << FDCAN_IE_RF1WE_Pos)                 /*!< 0x00000020 */
#define FDCAN_IE_RF1WE            FDCAN_IE_RF1WE_Msk                           /*!<Rx FIFO 1 Watermark Reached Enable           */
#define FDCAN_IE_RF1FE_Pos        (6U)
#define FDCAN_IE_RF1FE_Msk        (0x1U << FDCAN_IE_RF1FE_Pos)                 /*!< 0x00000040 */
#define FDCAN_IE_RF1FE            FDCAN_IE_RF1FE_Msk                           /*!<Rx FIFO 1 Full Enable                        */
#define FDCAN_IE_RF1LE_Pos        (7U)
#define FDCAN_IE_RF1LE_Msk        (0x1U << FDCAN_IE_RF1LE_Pos)                 /*!< 0x00000080 */
#define FDCAN_IE_RF1LE            FDCAN_IE_RF1LE_Msk                           /*!<Rx FIFO 1 Message Lost Enable                */
#define FDCAN_IE_HPME_Pos         (8U)
#define FDCAN_IE_HPME_Msk         (0x1U << FDCAN_IE_HPME_Pos)                  /*!< 0x00000100 */
#define FDCAN_IE_HPME             FDCAN_IE_HPME_Msk                            /*!<High Priority Message Enable                 */
#define FDCAN_IE_TCE_Pos          (9U)
#define FDCAN_IE_TCE_Msk          (0x1U << FDCAN_IE_TCE_Pos)                   /*!< 0x00000200 */
#define FDCAN_IE_TCE              FDCAN_IE_TCE_Msk                             /*!<Transmission Completed Enable                */
#define FDCAN_IE_TCFE_Pos         (10U)
#define FDCAN_IE_TCFE_Msk         (0x1U << FDCAN_IE_TCFE_Pos)                  /*!< 0x00000400 */
#define FDCAN_IE_TCFE             FDCAN_IE_TCFE_Msk                            /*!<Transmission Cancellation Finished Enable    */
#define FDCAN_IE_TFEE_Pos         (11U)
#define FDCAN_IE_TFEE_Msk         (0x1U << FDCAN_IE_TFEE_Pos)                  /*!< 0x00000800 */
#define FDCAN_IE_TFEE             FDCAN_IE_TFEE_Msk                            /*!<Tx FIFO Empty Enable                         */
#define FDCAN_IE_TEFNE_Pos        (12U)
#define FDCAN_IE_TEFNE_Msk        (0x1U << FDCAN_IE_TEFNE_Pos)                 /*!< 0x00001000 */
#define FDCAN_IE_TEFNE            FDCAN_IE_TEFNE_Msk                           /*!<Tx Event FIFO New Entry Enable               */
#define FDCAN_IE_TEFWE_Pos        (13U)
#define FDCAN_IE_TEFWE_Msk        (0x1U << FDCAN_IE_TEFWE_Pos)                 /*!< 0x00002000 */
#define FDCAN_IE_TEFWE            FDCAN_IE_TEFWE_Msk                           /*!<Tx Event FIFO Watermark Reached Enable       */
#define FDCAN_IE_TEFFE_Pos        (14U)
#define FDCAN_IE_TEFFE_Msk        (0x1U << FDCAN_IE_TEFFE_Pos)                 /*!< 0x00004000 */
#define FDCAN_IE_TEFFE            FDCAN_IE_TEFFE_Msk                           /*!<Tx Event FIFO Full Enable                    */
#define FDCAN_IE_TEFLE_Pos        (15U)
#define FDCAN_IE_TEFLE_Msk        (0x1U << FDCAN_IE_TEFLE_Pos)                 /*!< 0x00008000 */
#define FDCAN_IE_TEFLE            FDCAN_IE_TEFLE_Msk                           /*!<Tx Event FIFO Element Lost Enable            */
#define FDCAN_IE_TSWE_Pos         (16U)
#define FDCAN_IE_TSWE_Msk         (0x1U << FDCAN_IE_TSWE_Pos)                  /*!< 0x00010000 */
#define FDCAN_IE_TSWE             FDCAN_IE_TSWE_Msk                            /*!<Timestamp Wraparound Enable                  */
#define FDCAN_IE_MRAFE_Pos        (17U)
#define FDCAN_IE_MRAFE_Msk        (0x1U << FDCAN_IE_MRAFE_Pos)                 /*!< 0x00020000 */
#define FDCAN_IE_MRAFE            FDCAN_IE_MRAFE_Msk                           /*!<Message RAM Access Failure Enable            */
#define FDCAN_IE_TOOE_Pos         (18U)
#define FDCAN_IE_TOOE_Msk         (0x1U << FDCAN_IE_TOOE_Pos)                  /*!< 0x00040000 */
#define FDCAN_IE_TOOE             FDCAN_IE_TOOE_Msk                            /*!<Timeout Occurred Enable                      */
#define FDCAN_IE_DRXE_Pos         (19U)
#define FDCAN_IE_DRXE_Msk         (0x1U << FDCAN_IE_DRXE_Pos)                  /*!< 0x00080000 */
#define FDCAN_IE_DRXE             FDCAN_IE_DRXE_Msk                            /*!<Message stored to Dedicated Rx Buffer Enable */
#define FDCAN_IE_ELOE_Pos         (22U)
#define FDCAN_IE_ELOE_Msk         (0x1U << FDCAN_IE_ELOE_Pos)                  /*!< 0x00400000 */
#define FDCAN_IE_ELOE             FDCAN_IE_ELOE_Msk                            /*!<Error Logging Overflow Enable                */
#define FDCAN_IE_EPE_Pos          (23U)
#define FDCAN_IE_EPE_Msk          (0x1U << FDCAN_IE_EPE_Pos)                   /*!< 0x00800000 */
#define FDCAN_IE_EPE              FDCAN_IE_EPE_Msk                             /*!<Error Passive Enable                         */
#define FDCAN_IE_EWE_Pos          (24U)
#define FDCAN_IE_EWE_Msk          (0x1U << FDCAN_IE_EWE_Pos)                   /*!< 0x01000000 */
#define FDCAN_IE_EWE              FDCAN_IE_EWE_Msk                             /*!<Warning Status Enable                        */
#define FDCAN_IE_BOE_Pos          (25U)
#define FDCAN_IE_BOE_Msk          (0x1U << FDCAN_IE_BOE_Pos)                   /*!< 0x02000000 */
#define FDCAN_IE_BOE              FDCAN_IE_BOE_Msk                             /*!<Bus_Off Status Enable                        */
#define FDCAN_IE_WDIE_Pos         (26U)
#define FDCAN_IE_WDIE_Msk         (0x1U << FDCAN_IE_WDIE_Pos)                  /*!< 0x04000000 */
#define FDCAN_IE_WDIE             FDCAN_IE_WDIE_Msk                            /*!<Watchdog Interrupt Enable                    */
#define FDCAN_IE_PEAE_Pos         (27U)
#define FDCAN_IE_PEAE_Msk         (0x1U << FDCAN_IE_PEAE_Pos)                  /*!< 0x08000000 */
#define FDCAN_IE_PEAE             FDCAN_IE_PEAE_Msk                            /*!<Protocol Error in Arbitration Phase Enable   */
#define FDCAN_IE_PEDE_Pos         (28U)
#define FDCAN_IE_PEDE_Msk         (0x1U << FDCAN_IE_PEDE_Pos)                  /*!< 0x10000000 */
#define FDCAN_IE_PEDE             FDCAN_IE_PEDE_Msk                            /*!<Protocol Error in Data Phase Enable          */
#define FDCAN_IE_ARAE_Pos         (29U)
#define FDCAN_IE_ARAE_Msk         (0x1U << FDCAN_IE_ARAE_Pos)                  /*!< 0x20000000 */
#define FDCAN_IE_ARAE             FDCAN_IE_ARAE_Msk                            /*!<Access to Reserved Address Enable            */

/*****************  Bit definition for FDCAN_ILS register  **********************/
#define FDCAN_ILS_RF0NL_Pos       (0U)
#define FDCAN_ILS_RF0NL_Msk       (0x1U << FDCAN_ILS_RF0NL_Pos)                /*!< 0x00000001 */
#define FDCAN_ILS_RF0NL           FDCAN_ILS_RF0NL_Msk                          /*!<Rx FIFO 0 New Message Line                  */
#define FDCAN_ILS_RF0WL_Pos       (1U)
#define FDCAN_ILS_RF0WL_Msk       (0x1U << FDCAN_ILS_RF0WL_Pos)                /*!< 0x00000002 */
#define FDCAN_ILS_RF0WL           FDCAN_ILS_RF0WL_Msk                          /*!<Rx FIFO 0 Watermark Reached Line            */
#define FDCAN_ILS_RF0FL_Pos       (2U)
#define FDCAN_ILS_RF0FL_Msk       (0x1U << FDCAN_ILS_RF0FL_Pos)                /*!< 0x00000004 */
#define FDCAN_ILS_RF0FL           FDCAN_ILS_RF0FL_Msk                          /*!<Rx FIFO 0 Full Line                         */
#define FDCAN_ILS_RF0LL_Pos       (3U)
#define FDCAN_ILS_RF0LL_Msk       (0x1U << FDCAN_ILS_RF0LL_Pos)                /*!< 0x00000008 */
#define FDCAN_ILS_RF0LL           FDCAN_ILS_RF0LL_Msk                          /*!<Rx FIFO 0 Message Lost Line                 */
#define FDCAN_ILS_RF1NL_Pos       (4U)
#define FDCAN_ILS_RF1NL_Msk       (0x1U << FDCAN_ILS_RF1NL_Pos)                /*!< 0x00000010 */
#define FDCAN_ILS_RF1NL           FDCAN_ILS_RF1NL_Msk                          /*!<Rx FIFO 1 New Message Line                  */
#define FDCAN_ILS_RF1WL_Pos       (5U)
#define FDCAN_ILS_RF1WL_Msk       (0x1U << FDCAN_ILS_RF1WL_Pos)                /*!< 0x00000020 */
#define FDCAN_ILS_RF1WL           FDCAN_ILS_RF1WL_Msk                          /*!<Rx FIFO 1 Watermark Reached Line            */
#define FDCAN_ILS_RF1FL_Pos       (6U)
#define FDCAN_ILS_RF1FL_Msk       (0x1U << FDCAN_ILS_RF1FL_Pos)                /*!< 0x00000040 */
#define FDCAN_ILS_RF1FL           FDCAN_ILS_RF1FL_Msk                          /*!<Rx FIFO 1 Full Line                         */
#define FDCAN_ILS_RF1LL_Pos       (7U)
#define FDCAN_ILS_RF1LL_Msk       (0x1U << FDCAN_ILS_RF1LL_Pos)                /*!< 0x00000080 */
#define FDCAN_ILS_RF1LL           FDCAN_ILS_RF1LL_Msk                          /*!<Rx FIFO 1 Message Lost Line                 */
#define FDCAN_ILS_HPML_Pos        (8U)
#define FDCAN_ILS_HPML_Msk        (0x1U << FDCAN_ILS_HPML_Pos)                 /*!< 0x00000100 */
#define FDCAN_ILS_HPML            FDCAN_ILS_HPML_Msk                           /*!<High Priority Message Line                  */
#define FDCAN_ILS_TCL_Pos         (9U)
#define FDCAN_ILS_TCL_Msk         (0x1U << FDCAN_ILS_TCL_Pos)                  /*!< 0x00000200 */
#define FDCAN_ILS_TCL             FDCAN_ILS_TCL_Msk                            /*!<Transmission Completed Line                 */
#define FDCAN_ILS_TCFL_Pos        (10U)
#define FDCAN_ILS_TCFL_Msk        (0x1U << FDCAN_ILS_TCFL_Pos)                 /*!< 0x00000400 */
#define FDCAN_ILS_TCFL            FDCAN_ILS_TCFL_Msk                           /*!<Transmission Cancellation Finished Line     */
#define FDCAN_ILS_TFEL_Pos        (11U)
#define FDCAN_ILS_TFEL_Msk        (0x1U << FDCAN_ILS_TFEL_Pos)                 /*!< 0x00000800 */
#define FDCAN_ILS_TFEL            FDCAN_ILS_TFEL_Msk                           /*!<Tx FIFO Empty Line                          */
#define FDCAN_ILS_TEFNL_Pos       (12U)
#define FDCAN_ILS_TEFNL_Msk       (0x1U << FDCAN_ILS_TEFNL_Pos)                /*!< 0x00001000 */
#define FDCAN_ILS_TEFNL           FDCAN_ILS_TEFNL_Msk                          /*!<Tx Event FIFO New Entry Line                */
#define FDCAN_ILS_TEFWL_Pos       (13U)
#define FDCAN_ILS_TEFWL_Msk       (0x1U << FDCAN_ILS_TEFWL_Pos)                /*!< 0x00002000 */
#define FDCAN_ILS_TEFWL           FDCAN_ILS_TEFWL_Msk                          /*!<Tx Event FIFO Watermark Reached Line        */
#define FDCAN_ILS_TEFFL_Pos       (14U)
#define FDCAN_ILS_TEFFL_Msk       (0x1U << FDCAN_ILS_TEFFL_Pos)                /*!< 0x00004000 */
#define FDCAN_ILS_TEFFL           FDCAN_ILS_TEFFL_Msk                          /*!<Tx Event FIFO Full Line                     */
#define FDCAN_ILS_TEFLL_Pos       (15U)
#define FDCAN_ILS_TEFLL_Msk       (0x1U << FDCAN_ILS_TEFLL_Pos)                /*!< 0x00008000 */
#define FDCAN_ILS_TEFLL           FDCAN_ILS_TEFLL_Msk                          /*!<Tx Event FIFO Element Lost Line             */
#define FDCAN_ILS_TSWL_Pos        (16U)
#define FDCAN_ILS_TSWL_Msk        (0x1U << FDCAN_ILS_TSWL_Pos)                 /*!< 0x00010000 */
#define FDCAN_ILS_TSWL            FDCAN_ILS_TSWL_Msk                           /*!<Timestamp Wraparound Line                   */
#define FDCAN_ILS_MRAFL_Pos       (17U)
#define FDCAN_ILS_MRAFL_Msk       (0x1U << FDCAN_ILS_MRAFL_Pos)                /*!< 0x00020000 */
#define FDCAN_ILS_MRAFL           FDCAN_ILS_MRAFL_Msk                          /*!<Message RAM Access Failure Line             */
#define FDCAN_ILS_TOOL_Pos        (18U)
#define FDCAN_ILS_TOOL_Msk        (0x1U << FDCAN_ILS_TOOL_Pos)                 /*!< 0x00040000 */
#define FDCAN_ILS_TOOL            FDCAN_ILS_TOOL_Msk                           /*!<Timeout Occurred Line                       */
#define FDCAN_ILS_DRXL_Pos        (19U)
#define FDCAN_ILS_DRXL_Msk        (0x1U << FDCAN_ILS_DRXL_Pos)                 /*!< 0x00080000 */
#define FDCAN_ILS_DRXL            FDCAN_ILS_DRXL_Msk                           /*!<Message stored to Dedicated Rx Buffer Line  */
#define FDCAN_ILS_ELOL_Pos        (22U)
#define FDCAN_ILS_ELOL_Msk        (0x1U << FDCAN_ILS_ELOL_Pos)                 /*!< 0x00400000 */
#define FDCAN_ILS_ELOL            FDCAN_ILS_ELOL_Msk                           /*!<Error Logging Overflow Line                 */
#define FDCAN_ILS_EPL_Pos         (23U)
#define FDCAN_ILS_EPL_Msk         (0x1U << FDCAN_ILS_EPL_Pos)                  /*!< 0x00800000 */
#define FDCAN_ILS_EPL             FDCAN_ILS_EPL_Msk                            /*!<Error Passive Line                          */
#define FDCAN_ILS_EWL_Pos         (24U)
#define FDCAN_ILS_EWL_Msk         (0x1U << FDCAN_ILS_EWL_Pos)                  /*!< 0x01000000 */
#define FDCAN_ILS_EWL             FDCAN_ILS_EWL_Msk                            /*!<Warning Status Line                         */
#define FDCAN_ILS_BOL_Pos         (25U)
#define FDCAN_ILS_BOL_Msk         (0x1U << FDCAN_ILS_BOL_Pos)                  /*!< 0x02000000 */
#define FDCAN_ILS_BOL             FDCAN_ILS_BOL_Msk                            /*!<Bus_Off Status Line                         */
#define FDCAN_ILS_WDIL_Pos        (26U)
#define FDCAN_ILS_WDIL_Msk        (0x1U << FDCAN_ILS_WDIL_Pos)                 /*!< 0x04000000 */
#define FDCAN_ILS_WDIL            FDCAN_ILS_WDIL_Msk                           /*!<Watchdog Interrupt Line                     */
#define FDCAN_ILS_PEAL_Pos        (27U)
#define FDCAN_ILS_PEAL_Msk        (0x1U << FDCAN_ILS_PEAL_Pos)                 /*!< 0x08000000 */
#define FDCAN_ILS_PEAL            FDCAN_ILS_PEAL_Msk                           /*!<Protocol Error in Arbitration Phase Line    */
#define FDCAN_ILS_PEDL_Pos        (28U)
#define FDCAN_ILS_PEDL_Msk        (0x1U << FDCAN_ILS_PEDL_Pos)                 /*!< 0x10000000 */
#define FDCAN_ILS_PEDL            FDCAN_ILS_PEDL_Msk                           /*!<Protocol Error in Data Phase Line           */
#define FDCAN_ILS_ARAL_Pos        (29U)
#define FDCAN_ILS_ARAL_Msk        (0x1U << FDCAN_ILS_ARAL_Pos)                 /*!< 0x20000000 */
#define FDCAN_ILS_ARAL            FDCAN_ILS_ARAL_Msk                           /*!<Access to Reserved Address Line             */

/** @defgroup FDCAN_Interrupt_Group FDCAN interrupt group
  * @{
  */
#define FDCAN_IT_GROUP_RX_FIFO0          FDCAN_ILS_RF0NL|FDCAN_ILS_RF0FL|FDCAN_ILS_RF0LL|FDCAN_ILS_RF0WL
															/*!< RX FIFO 0 Interrupts Group:
                                                                  RF0LL: Rx FIFO 0 Message Lost
                                                                  RF0FL: Rx FIFO 0 is Full
                                                                  RF0NL: Rx FIFO 0 Has New Message            */
#define FDCAN_IT_GROUP_RX_FIFO1          FDCAN_ILS_RF1NL|FDCAN_ILS_RF1FL|FDCAN_ILS_RF1LL|FDCAN_ILS_RF1WL
															/*!< RX FIFO 1 Interrupts Group:
                                                                  RF1LL: Rx FIFO 1 Message Lost
                                                                  RF1FL: Rx FIFO 1 is Full
                                                                  RF1NL: Rx FIFO 1 Has New Message            */
#define FDCAN_IT_GROUP_SMSG              FDCAN_ILS_HPML|FDCAN_ILS_TCL|FDCAN_ILS_TCFL
															/*!< Status Message Interrupts Group:
                                                                  TCFL: Transmission Cancellation Finished
                                                                  TCL: Transmission Completed
                                                                  HPML: High Priority Message                 */
#define FDCAN_IT_GROUP_TX_FIFO_ERROR     FDCAN_ILS_TFEL|FDCAN_ILS_TEFNL|FDCAN_ILS_TEFWL|FDCAN_ILS_TEFLL
															/*!< TX FIFO Error Interrupts Group:
                                                                  TEFLL: Tx Event FIFO Element Lost
                                                                  TEFFL: Tx Event FIFO Full
                                                                  TEFNL: Tx Event FIFO New Entry
                                                                  TFEL: Tx FIFO Empty Interrupt Line          */
#define FDCAN_IT_GROUP_MISC              FDCAN_ILS_TSWL|FDCAN_ILS_MRAFL|FDCAN_ILS_TOOL|FDCAN_ILS_DRXL
															/*!< Misc. Interrupts Group:
                                                                  TOOL: Timeout Occurred
                                                                  MRAFL: Message RAM Access Failure
                                                                  TSWL: Timestamp Wraparound                  */
#define FDCAN_IT_GROUP_BIT_LINE_ERROR    FDCAN_ILS_ELOL|FDCAN_ILS_EPL
															/*!< Bit and Line Error Interrupts Group:
                                                                  EPL: Error Passive
                                                                  ELOL: Error Logging Overflow                */
#define FDCAN_IT_GROUP_PROTOCOL_ERROR    FDCAN_ILS_EWL|FDCAN_ILS_BOL|FDCAN_ILS_WDIL|FDCAN_ILS_PEAL|FDCAN_ILS_PEDL|FDCAN_ILS_ARAL
															/*!< Protocol Error Group:
                                                                  ARAL: Access to Reserved Address Line
                                                                  PEDL: Protocol Error in Data Phase Line
                                                                  PEAL: Protocol Error in Arbitration Phase Line
                                                                  WDIL: Watchdog Interrupt Line
                                                                  BOL: Bus_Off Status
                                                                  EWL: Warning Status                         */
/**
  * @}
  */

/*****************  Bit definition for FDCAN_ILE register  **********************/
#define FDCAN_ILE_EINT0_Pos       (0U)
#define FDCAN_ILE_EINT0_Msk       (0x1U << FDCAN_ILE_EINT0_Pos)                /*!< 0x00000001 */
#define FDCAN_ILE_EINT0           FDCAN_ILE_EINT0_Msk                          /*!<Enable Interrupt Line 0                   */
#define FDCAN_ILE_EINT1_Pos       (1U)
#define FDCAN_ILE_EINT1_Msk       (0x1U << FDCAN_ILE_EINT1_Pos)                /*!< 0x00000002 */
#define FDCAN_ILE_EINT1           FDCAN_ILE_EINT1_Msk                          /*!<Enable Interrupt Line 1                   */

/*****************  Bit definition for FDCAN_GFC register  **********************/
#define FDCAN_GFC_RRFE_Pos        (0U)
#define FDCAN_GFC_RRFE_Msk        (0x1U << FDCAN_GFC_RRFE_Pos)                 /*!< 0x00000001 */
#define FDCAN_GFC_RRFE            FDCAN_GFC_RRFE_Msk                           /*!<Reject Remote Frames Extended             */
#define FDCAN_GFC_RRFS_Pos        (1U)
#define FDCAN_GFC_RRFS_Msk        (0x1U << FDCAN_GFC_RRFS_Pos)                 /*!< 0x00000002 */
#define FDCAN_GFC_RRFS            FDCAN_GFC_RRFS_Msk                           /*!<Reject Remote Frames Standard             */
#define FDCAN_GFC_ANFE_Pos        (2U)
#define FDCAN_GFC_ANFE_Msk        (0x3U << FDCAN_GFC_ANFE_Pos)                 /*!< 0x0000000C */
#define FDCAN_GFC_ANFE            FDCAN_GFC_ANFE_Msk                           /*!<Accept Non-matching Frames Extended       */
#define FDCAN_GFC_ANFS_Pos        (4U)
#define FDCAN_GFC_ANFS_Msk        (0x3U << FDCAN_GFC_ANFS_Pos)                 /*!< 0x00000030 */
#define FDCAN_GFC_ANFS            FDCAN_GFC_ANFS_Msk                           /*!<Accept Non-matching Frames Standard       */

/*****************  Bit definition for FDCAN_SIDFC register  ********************/
#define FDCAN_SIDFC_FLSSA_Pos     (2U)
#define FDCAN_SIDFC_FLSSA_Msk     (0x3FFFU << FDCAN_SIDFC_FLSSA_Pos)           /*!< 0x0000FFFC */
#define FDCAN_SIDFC_FLSSA         FDCAN_SIDFC_FLSSA_Msk                        /*!<Filter List Standard Start Address        */
#define FDCAN_SIDFC_LSS_Pos       (16U)
#define FDCAN_SIDFC_LSS_Msk       (0xFFU << FDCAN_SIDFC_LSS_Pos)               /*!< 0x00FF0000 */
#define FDCAN_SIDFC_LSS           FDCAN_SIDFC_LSS_Msk                          /*!<List Size Standard                        */

/*****************  Bit definition for FDCAN_XIDFC register  ********************/
#define FDCAN_XIDFC_FLESA_Pos     (2U)
#define FDCAN_XIDFC_FLESA_Msk     (0x3FFFU << FDCAN_XIDFC_FLESA_Pos)           /*!< 0x0000FFFC */
#define FDCAN_XIDFC_FLESA         FDCAN_XIDFC_FLESA_Msk                        /*!<Filter List Standard Start Address        */
#define FDCAN_XIDFC_LSE_Pos       (16U)
#define FDCAN_XIDFC_LSE_Msk       (0xFFU << FDCAN_XIDFC_LSE_Pos)               /*!< 0x00FF0000 */
#define FDCAN_XIDFC_LSE           FDCAN_XIDFC_LSE_Msk                          /*!<List Size Extended                        */

/*****************  Bit definition for FDCAN_XIDAM register  ********************/
#define FDCAN_XIDAM_EIDM_Pos      (0U)
#define FDCAN_XIDAM_EIDM_Msk      (0x1FFFFFFFU << FDCAN_XIDAM_EIDM_Pos)        /*!< 0x1FFFFFFF */
#define FDCAN_XIDAM_EIDM          FDCAN_XIDAM_EIDM_Msk                         /*!<Extended ID Mask                          */

/*****************  Bit definition for FDCAN_HPMS register  *********************/
#define FDCAN_HPMS_BIDX_Pos       (0U)
#define FDCAN_HPMS_BIDX_Msk       (0x3FU << FDCAN_HPMS_BIDX_Pos)               /*!< 0x0000003F */
#define FDCAN_HPMS_BIDX           FDCAN_HPMS_BIDX_Msk                          /*!<Buffer Index                              */
#define FDCAN_HPMS_MSI_Pos        (6U)
#define FDCAN_HPMS_MSI_Msk        (0x3U << FDCAN_HPMS_MSI_Pos)                 /*!< 0x000000C0 */
#define FDCAN_HPMS_MSI            FDCAN_HPMS_MSI_Msk                           /*!<Message Storage Indicator                 */
#define FDCAN_HPMS_FIDX_Pos       (8U)
#define FDCAN_HPMS_FIDX_Msk       (0x7FU << FDCAN_HPMS_FIDX_Pos)               /*!< 0x00007F00 */
#define FDCAN_HPMS_FIDX           FDCAN_HPMS_FIDX_Msk                          /*!<Filter Index                              */
#define FDCAN_HPMS_FLST_Pos       (15U)
#define FDCAN_HPMS_FLST_Msk       (0x1U << FDCAN_HPMS_FLST_Pos)                /*!< 0x00008000 */
#define FDCAN_HPMS_FLST           FDCAN_HPMS_FLST_Msk                          /*!<Filter List                               */

/*****************  Bit definition for FDCAN_NDAT1 register  ********************/
#define FDCAN_NDAT1_ND0_Pos       (0U)
#define FDCAN_NDAT1_ND0_Msk       (0x1U << FDCAN_NDAT1_ND0_Pos)                /*!< 0x00000001 */
#define FDCAN_NDAT1_ND0           FDCAN_NDAT1_ND0_Msk                          /*!<New Data flag of Rx Buffer 0              */
#define FDCAN_NDAT1_ND1_Pos       (1U)
#define FDCAN_NDAT1_ND1_Msk       (0x1U << FDCAN_NDAT1_ND1_Pos)                /*!< 0x00000002 */
#define FDCAN_NDAT1_ND1           FDCAN_NDAT1_ND1_Msk                          /*!<New Data flag of Rx Buffer 1              */
#define FDCAN_NDAT1_ND2_Pos       (2U)
#define FDCAN_NDAT1_ND2_Msk       (0x1U << FDCAN_NDAT1_ND2_Pos)                /*!< 0x00000004 */
#define FDCAN_NDAT1_ND2           FDCAN_NDAT1_ND2_Msk                          /*!<New Data flag of Rx Buffer 2              */
#define FDCAN_NDAT1_ND3_Pos       (3U)
#define FDCAN_NDAT1_ND3_Msk       (0x1U << FDCAN_NDAT1_ND3_Pos)                /*!< 0x00000008 */
#define FDCAN_NDAT1_ND3           FDCAN_NDAT1_ND3_Msk                          /*!<New Data flag of Rx Buffer 3              */
#define FDCAN_NDAT1_ND4_Pos       (4U)
#define FDCAN_NDAT1_ND4_Msk       (0x1U << FDCAN_NDAT1_ND4_Pos)                /*!< 0x00000010 */
#define FDCAN_NDAT1_ND4           FDCAN_NDAT1_ND4_Msk                          /*!<New Data flag of Rx Buffer 4              */
#define FDCAN_NDAT1_ND5_Pos       (5U)
#define FDCAN_NDAT1_ND5_Msk       (0x1U << FDCAN_NDAT1_ND5_Pos)                /*!< 0x00000020 */
#define FDCAN_NDAT1_ND5           FDCAN_NDAT1_ND5_Msk                          /*!<New Data flag of Rx Buffer 5              */
#define FDCAN_NDAT1_ND6_Pos       (6U)
#define FDCAN_NDAT1_ND6_Msk       (0x1U << FDCAN_NDAT1_ND6_Pos)                /*!< 0x00000040 */
#define FDCAN_NDAT1_ND6           FDCAN_NDAT1_ND6_Msk                          /*!<New Data flag of Rx Buffer 6              */
#define FDCAN_NDAT1_ND7_Pos       (7U)
#define FDCAN_NDAT1_ND7_Msk       (0x1U << FDCAN_NDAT1_ND7_Pos)                /*!< 0x00000080 */
#define FDCAN_NDAT1_ND7           FDCAN_NDAT1_ND7_Msk                          /*!<New Data flag of Rx Buffer 7              */
#define FDCAN_NDAT1_ND8_Pos       (8U)
#define FDCAN_NDAT1_ND8_Msk       (0x1U << FDCAN_NDAT1_ND8_Pos)                /*!< 0x00000100 */
#define FDCAN_NDAT1_ND8           FDCAN_NDAT1_ND8_Msk                          /*!<New Data flag of Rx Buffer 8              */
#define FDCAN_NDAT1_ND9_Pos       (9U)
#define FDCAN_NDAT1_ND9_Msk       (0x1U << FDCAN_NDAT1_ND9_Pos)                /*!< 0x00000200 */
#define FDCAN_NDAT1_ND9           FDCAN_NDAT1_ND9_Msk                          /*!<New Data flag of Rx Buffer 9              */
#define FDCAN_NDAT1_ND10_Pos      (10U)
#define FDCAN_NDAT1_ND10_Msk      (0x1U << FDCAN_NDAT1_ND10_Pos)               /*!< 0x00000400 */
#define FDCAN_NDAT1_ND10          FDCAN_NDAT1_ND10_Msk                         /*!<New Data flag of Rx Buffer 10             */
#define FDCAN_NDAT1_ND11_Pos      (11U)
#define FDCAN_NDAT1_ND11_Msk      (0x1U << FDCAN_NDAT1_ND11_Pos)               /*!< 0x00000800 */
#define FDCAN_NDAT1_ND11          FDCAN_NDAT1_ND11_Msk                         /*!<New Data flag of Rx Buffer 11             */
#define FDCAN_NDAT1_ND12_Pos      (12U)
#define FDCAN_NDAT1_ND12_Msk      (0x1U << FDCAN_NDAT1_ND12_Pos)               /*!< 0x00001000 */
#define FDCAN_NDAT1_ND12          FDCAN_NDAT1_ND12_Msk                         /*!<New Data flag of Rx Buffer 12             */
#define FDCAN_NDAT1_ND13_Pos      (13U)
#define FDCAN_NDAT1_ND13_Msk      (0x1U << FDCAN_NDAT1_ND13_Pos)               /*!< 0x00002000 */
#define FDCAN_NDAT1_ND13          FDCAN_NDAT1_ND13_Msk                         /*!<New Data flag of Rx Buffer 13             */
#define FDCAN_NDAT1_ND14_Pos      (14U)
#define FDCAN_NDAT1_ND14_Msk      (0x1U << FDCAN_NDAT1_ND14_Pos)               /*!< 0x00004000 */
#define FDCAN_NDAT1_ND14          FDCAN_NDAT1_ND14_Msk                         /*!<New Data flag of Rx Buffer 14             */
#define FDCAN_NDAT1_ND15_Pos      (15U)
#define FDCAN_NDAT1_ND15_Msk      (0x1U << FDCAN_NDAT1_ND15_Pos)               /*!< 0x00008000 */
#define FDCAN_NDAT1_ND15          FDCAN_NDAT1_ND15_Msk                         /*!<New Data flag of Rx Buffer 15             */
#define FDCAN_NDAT1_ND16_Pos      (16U)
#define FDCAN_NDAT1_ND16_Msk      (0x1U << FDCAN_NDAT1_ND16_Pos)               /*!< 0x00010000 */
#define FDCAN_NDAT1_ND16          FDCAN_NDAT1_ND16_Msk                         /*!<New Data flag of Rx Buffer 16             */
#define FDCAN_NDAT1_ND17_Pos      (17U)
#define FDCAN_NDAT1_ND17_Msk      (0x1U << FDCAN_NDAT1_ND17_Pos)               /*!< 0x00020000 */
#define FDCAN_NDAT1_ND17          FDCAN_NDAT1_ND17_Msk                         /*!<New Data flag of Rx Buffer 17             */
#define FDCAN_NDAT1_ND18_Pos      (18U)
#define FDCAN_NDAT1_ND18_Msk      (0x1U << FDCAN_NDAT1_ND18_Pos)               /*!< 0x00040000 */
#define FDCAN_NDAT1_ND18          FDCAN_NDAT1_ND18_Msk                         /*!<New Data flag of Rx Buffer 18             */
#define FDCAN_NDAT1_ND19_Pos      (19U)
#define FDCAN_NDAT1_ND19_Msk      (0x1U << FDCAN_NDAT1_ND19_Pos)               /*!< 0x00080000 */
#define FDCAN_NDAT1_ND19          FDCAN_NDAT1_ND19_Msk                         /*!<New Data flag of Rx Buffer 19             */
#define FDCAN_NDAT1_ND20_Pos      (20U)
#define FDCAN_NDAT1_ND20_Msk      (0x1U << FDCAN_NDAT1_ND20_Pos)               /*!< 0x00100000 */
#define FDCAN_NDAT1_ND20          FDCAN_NDAT1_ND20_Msk                         /*!<New Data flag of Rx Buffer 20             */
#define FDCAN_NDAT1_ND21_Pos      (21U)
#define FDCAN_NDAT1_ND21_Msk      (0x1U << FDCAN_NDAT1_ND21_Pos)               /*!< 0x00200000 */
#define FDCAN_NDAT1_ND21          FDCAN_NDAT1_ND21_Msk                         /*!<New Data flag of Rx Buffer 21             */
#define FDCAN_NDAT1_ND22_Pos      (22U)
#define FDCAN_NDAT1_ND22_Msk      (0x1U << FDCAN_NDAT1_ND22_Pos)               /*!< 0x00400000 */
#define FDCAN_NDAT1_ND22          FDCAN_NDAT1_ND22_Msk                         /*!<New Data flag of Rx Buffer 22             */
#define FDCAN_NDAT1_ND23_Pos      (23U)
#define FDCAN_NDAT1_ND23_Msk      (0x1U << FDCAN_NDAT1_ND23_Pos)               /*!< 0x00800000 */
#define FDCAN_NDAT1_ND23          FDCAN_NDAT1_ND23_Msk                         /*!<New Data flag of Rx Buffer 23             */
#define FDCAN_NDAT1_ND24_Pos      (24U)
#define FDCAN_NDAT1_ND24_Msk      (0x1U << FDCAN_NDAT1_ND24_Pos)               /*!< 0x01000000 */
#define FDCAN_NDAT1_ND24          FDCAN_NDAT1_ND24_Msk                         /*!<New Data flag of Rx Buffer 24             */
#define FDCAN_NDAT1_ND25_Pos      (25U)
#define FDCAN_NDAT1_ND25_Msk      (0x1U << FDCAN_NDAT1_ND25_Pos)               /*!< 0x02000000 */
#define FDCAN_NDAT1_ND25          FDCAN_NDAT1_ND25_Msk                         /*!<New Data flag of Rx Buffer 25             */
#define FDCAN_NDAT1_ND26_Pos      (26U)
#define FDCAN_NDAT1_ND26_Msk      (0x1U << FDCAN_NDAT1_ND26_Pos)               /*!< 0x04000000 */
#define FDCAN_NDAT1_ND26          FDCAN_NDAT1_ND26_Msk                         /*!<New Data flag of Rx Buffer 26             */
#define FDCAN_NDAT1_ND27_Pos      (27U)
#define FDCAN_NDAT1_ND27_Msk      (0x1U << FDCAN_NDAT1_ND27_Pos)               /*!< 0x08000000 */
#define FDCAN_NDAT1_ND27          FDCAN_NDAT1_ND27_Msk                         /*!<New Data flag of Rx Buffer 27             */
#define FDCAN_NDAT1_ND28_Pos      (28U)
#define FDCAN_NDAT1_ND28_Msk      (0x1U << FDCAN_NDAT1_ND28_Pos)               /*!< 0x10000000 */
#define FDCAN_NDAT1_ND28          FDCAN_NDAT1_ND28_Msk                         /*!<New Data flag of Rx Buffer 28             */
#define FDCAN_NDAT1_ND29_Pos      (29U)
#define FDCAN_NDAT1_ND29_Msk      (0x1U << FDCAN_NDAT1_ND29_Pos)               /*!< 0x20000000 */
#define FDCAN_NDAT1_ND29          FDCAN_NDAT1_ND29_Msk                         /*!<New Data flag of Rx Buffer 29             */
#define FDCAN_NDAT1_ND30_Pos      (30U)
#define FDCAN_NDAT1_ND30_Msk      (0x1U << FDCAN_NDAT1_ND30_Pos)               /*!< 0x40000000 */
#define FDCAN_NDAT1_ND30          FDCAN_NDAT1_ND30_Msk                         /*!<New Data flag of Rx Buffer 30             */
#define FDCAN_NDAT1_ND31_Pos      (31U)
#define FDCAN_NDAT1_ND31_Msk      (0x1U << FDCAN_NDAT1_ND31_Pos)               /*!< 0x80000000 */
#define FDCAN_NDAT1_ND31          FDCAN_NDAT1_ND31_Msk                         /*!<New Data flag of Rx Buffer 31             */

/*****************  Bit definition for FDCAN_NDAT2 register  ********************/
#define FDCAN_NDAT2_ND32_Pos      (0U)
#define FDCAN_NDAT2_ND32_Msk      (0x1U << FDCAN_NDAT2_ND32_Pos)               /*!< 0x00000001 */
#define FDCAN_NDAT2_ND32          FDCAN_NDAT2_ND32_Msk                         /*!<New Data flag of Rx Buffer 32             */
#define FDCAN_NDAT2_ND33_Pos      (1U)
#define FDCAN_NDAT2_ND33_Msk      (0x1U << FDCAN_NDAT2_ND33_Pos)               /*!< 0x00000002 */
#define FDCAN_NDAT2_ND33          FDCAN_NDAT2_ND33_Msk                         /*!<New Data flag of Rx Buffer 33             */
#define FDCAN_NDAT2_ND34_Pos      (2U)
#define FDCAN_NDAT2_ND34_Msk      (0x1U << FDCAN_NDAT2_ND34_Pos)               /*!< 0x00000004 */
#define FDCAN_NDAT2_ND34          FDCAN_NDAT2_ND34_Msk                         /*!<New Data flag of Rx Buffer 34             */
#define FDCAN_NDAT2_ND35_Pos      (3U)
#define FDCAN_NDAT2_ND35_Msk      (0x1U << FDCAN_NDAT2_ND35_Pos)               /*!< 0x00000008 */
#define FDCAN_NDAT2_ND35          FDCAN_NDAT2_ND35_Msk                         /*!<New Data flag of Rx Buffer 35             */
#define FDCAN_NDAT2_ND36_Pos      (4U)
#define FDCAN_NDAT2_ND36_Msk      (0x1U << FDCAN_NDAT2_ND36_Pos)               /*!< 0x00000010 */
#define FDCAN_NDAT2_ND36          FDCAN_NDAT2_ND36_Msk                         /*!<New Data flag of Rx Buffer 36             */
#define FDCAN_NDAT2_ND37_Pos      (5U)
#define FDCAN_NDAT2_ND37_Msk      (0x1U << FDCAN_NDAT2_ND37_Pos)               /*!< 0x00000020 */
#define FDCAN_NDAT2_ND37          FDCAN_NDAT2_ND37_Msk                         /*!<New Data flag of Rx Buffer 37             */
#define FDCAN_NDAT2_ND38_Pos      (6U)
#define FDCAN_NDAT2_ND38_Msk      (0x1U << FDCAN_NDAT2_ND38_Pos)               /*!< 0x00000040 */
#define FDCAN_NDAT2_ND38          FDCAN_NDAT2_ND38_Msk                         /*!<New Data flag of Rx Buffer 38             */
#define FDCAN_NDAT2_ND39_Pos      (7U)
#define FDCAN_NDAT2_ND39_Msk      (0x1U << FDCAN_NDAT2_ND39_Pos)               /*!< 0x00000080 */
#define FDCAN_NDAT2_ND39          FDCAN_NDAT2_ND39_Msk                         /*!<New Data flag of Rx Buffer 39             */
#define FDCAN_NDAT2_ND40_Pos      (8U)
#define FDCAN_NDAT2_ND40_Msk      (0x1U << FDCAN_NDAT2_ND40_Pos)               /*!< 0x00000100 */
#define FDCAN_NDAT2_ND40          FDCAN_NDAT2_ND40_Msk                         /*!<New Data flag of Rx Buffer 40             */
#define FDCAN_NDAT2_ND41_Pos      (9U)
#define FDCAN_NDAT2_ND41_Msk      (0x1U << FDCAN_NDAT2_ND41_Pos)               /*!< 0x00000200 */
#define FDCAN_NDAT2_ND41          FDCAN_NDAT2_ND41_Msk                         /*!<New Data flag of Rx Buffer 41             */
#define FDCAN_NDAT2_ND42_Pos      (10U)
#define FDCAN_NDAT2_ND42_Msk      (0x1U << FDCAN_NDAT2_ND42_Pos)               /*!< 0x00000400 */
#define FDCAN_NDAT2_ND42          FDCAN_NDAT2_ND42_Msk                         /*!<New Data flag of Rx Buffer 42             */
#define FDCAN_NDAT2_ND43_Pos      (11U)
#define FDCAN_NDAT2_ND43_Msk      (0x1U << FDCAN_NDAT2_ND43_Pos)               /*!< 0x00000800 */
#define FDCAN_NDAT2_ND43          FDCAN_NDAT2_ND43_Msk                         /*!<New Data flag of Rx Buffer 43             */
#define FDCAN_NDAT2_ND44_Pos      (12U)
#define FDCAN_NDAT2_ND44_Msk      (0x1U << FDCAN_NDAT2_ND44_Pos)               /*!< 0x00001000 */
#define FDCAN_NDAT2_ND44          FDCAN_NDAT2_ND44_Msk                         /*!<New Data flag of Rx Buffer 44             */
#define FDCAN_NDAT2_ND45_Pos      (13U)
#define FDCAN_NDAT2_ND45_Msk      (0x1U << FDCAN_NDAT2_ND45_Pos)               /*!< 0x00002000 */
#define FDCAN_NDAT2_ND45          FDCAN_NDAT2_ND45_Msk                         /*!<New Data flag of Rx Buffer 45             */
#define FDCAN_NDAT2_ND46_Pos      (14U)
#define FDCAN_NDAT2_ND46_Msk      (0x1U << FDCAN_NDAT2_ND46_Pos)               /*!< 0x00004000 */
#define FDCAN_NDAT2_ND46          FDCAN_NDAT2_ND46_Msk                         /*!<New Data flag of Rx Buffer 46             */
#define FDCAN_NDAT2_ND47_Pos      (15U)
#define FDCAN_NDAT2_ND47_Msk      (0x1U << FDCAN_NDAT2_ND47_Pos)               /*!< 0x00008000 */
#define FDCAN_NDAT2_ND47          FDCAN_NDAT2_ND47_Msk                         /*!<New Data flag of Rx Buffer 47             */
#define FDCAN_NDAT2_ND48_Pos      (16U)
#define FDCAN_NDAT2_ND48_Msk      (0x1U << FDCAN_NDAT2_ND48_Pos)               /*!< 0x00010000 */
#define FDCAN_NDAT2_ND48          FDCAN_NDAT2_ND48_Msk                         /*!<New Data flag of Rx Buffer 48             */
#define FDCAN_NDAT2_ND49_Pos      (17U)
#define FDCAN_NDAT2_ND49_Msk      (0x1U << FDCAN_NDAT2_ND49_Pos)               /*!< 0x00020000 */
#define FDCAN_NDAT2_ND49          FDCAN_NDAT2_ND49_Msk                         /*!<New Data flag of Rx Buffer 49             */
#define FDCAN_NDAT2_ND50_Pos      (18U)
#define FDCAN_NDAT2_ND50_Msk      (0x1U << FDCAN_NDAT2_ND50_Pos)               /*!< 0x00040000 */
#define FDCAN_NDAT2_ND50          FDCAN_NDAT2_ND50_Msk                         /*!<New Data flag of Rx Buffer 50             */
#define FDCAN_NDAT2_ND51_Pos      (19U)
#define FDCAN_NDAT2_ND51_Msk      (0x1U << FDCAN_NDAT2_ND51_Pos)               /*!< 0x00080000 */
#define FDCAN_NDAT2_ND51          FDCAN_NDAT2_ND51_Msk                         /*!<New Data flag of Rx Buffer 51             */
#define FDCAN_NDAT2_ND52_Pos      (20U)
#define FDCAN_NDAT2_ND52_Msk      (0x1U << FDCAN_NDAT2_ND52_Pos)               /*!< 0x00100000 */
#define FDCAN_NDAT2_ND52          FDCAN_NDAT2_ND52_Msk                         /*!<New Data flag of Rx Buffer 52             */
#define FDCAN_NDAT2_ND53_Pos      (21U)
#define FDCAN_NDAT2_ND53_Msk      (0x1U << FDCAN_NDAT2_ND53_Pos)               /*!< 0x00200000 */
#define FDCAN_NDAT2_ND53          FDCAN_NDAT2_ND53_Msk                         /*!<New Data flag of Rx Buffer 53             */
#define FDCAN_NDAT2_ND54_Pos      (22U)
#define FDCAN_NDAT2_ND54_Msk      (0x1U << FDCAN_NDAT2_ND54_Pos)               /*!< 0x00400000 */
#define FDCAN_NDAT2_ND54          FDCAN_NDAT2_ND54_Msk                         /*!<New Data flag of Rx Buffer 54             */
#define FDCAN_NDAT2_ND55_Pos      (23U)
#define FDCAN_NDAT2_ND55_Msk      (0x1U << FDCAN_NDAT2_ND55_Pos)               /*!< 0x00800000 */
#define FDCAN_NDAT2_ND55          FDCAN_NDAT2_ND55_Msk                         /*!<New Data flag of Rx Buffer 55             */
#define FDCAN_NDAT2_ND56_Pos      (24U)
#define FDCAN_NDAT2_ND56_Msk      (0x1U << FDCAN_NDAT2_ND56_Pos)               /*!< 0x01000000 */
#define FDCAN_NDAT2_ND56          FDCAN_NDAT2_ND56_Msk                         /*!<New Data flag of Rx Buffer 56             */
#define FDCAN_NDAT2_ND57_Pos      (25U)
#define FDCAN_NDAT2_ND57_Msk      (0x1U << FDCAN_NDAT2_ND57_Pos)               /*!< 0x02000000 */
#define FDCAN_NDAT2_ND57          FDCAN_NDAT2_ND57_Msk                         /*!<New Data flag of Rx Buffer 57             */
#define FDCAN_NDAT2_ND58_Pos      (26U)
#define FDCAN_NDAT2_ND58_Msk      (0x1U << FDCAN_NDAT2_ND58_Pos)               /*!< 0x04000000 */
#define FDCAN_NDAT2_ND58          FDCAN_NDAT2_ND58_Msk                         /*!<New Data flag of Rx Buffer 58             */
#define FDCAN_NDAT2_ND59_Pos      (27U)
#define FDCAN_NDAT2_ND59_Msk      (0x1U << FDCAN_NDAT2_ND59_Pos)               /*!< 0x08000000 */
#define FDCAN_NDAT2_ND59          FDCAN_NDAT2_ND59_Msk                         /*!<New Data flag of Rx Buffer 59             */
#define FDCAN_NDAT2_ND60_Pos      (28U)
#define FDCAN_NDAT2_ND60_Msk      (0x1U << FDCAN_NDAT2_ND60_Pos)               /*!< 0x10000000 */
#define FDCAN_NDAT2_ND60          FDCAN_NDAT2_ND60_Msk                         /*!<New Data flag of Rx Buffer 60             */
#define FDCAN_NDAT2_ND61_Pos      (29U)
#define FDCAN_NDAT2_ND61_Msk      (0x1U << FDCAN_NDAT2_ND61_Pos)               /*!< 0x20000000 */
#define FDCAN_NDAT2_ND61          FDCAN_NDAT2_ND61_Msk                         /*!<New Data flag of Rx Buffer 61             */
#define FDCAN_NDAT2_ND62_Pos      (30U)
#define FDCAN_NDAT2_ND62_Msk      (0x1U << FDCAN_NDAT2_ND62_Pos)               /*!< 0x40000000 */
#define FDCAN_NDAT2_ND62          FDCAN_NDAT2_ND62_Msk                         /*!<New Data flag of Rx Buffer 62             */
#define FDCAN_NDAT2_ND63_Pos      (31U)
#define FDCAN_NDAT2_ND63_Msk      (0x1U << FDCAN_NDAT2_ND63_Pos)               /*!< 0x80000000 */
#define FDCAN_NDAT2_ND63          FDCAN_NDAT2_ND63_Msk                         /*!<New Data flag of Rx Buffer 63             */

/*****************  Bit definition for FDCAN_RXF0C register  ********************/
#define FDCAN_RXF0C_F0SA_Pos      (2U)
#define FDCAN_RXF0C_F0SA_Msk      (0x3FFFU << FDCAN_RXF0C_F0SA_Pos)            /*!< 0x0000FFFC */
#define FDCAN_RXF0C_F0SA          FDCAN_RXF0C_F0SA_Msk                         /*!<Rx FIFO 0 Start Address                   */
#define FDCAN_RXF0C_F0S_Pos       (16U)
#define FDCAN_RXF0C_F0S_Msk       (0x7FU << FDCAN_RXF0C_F0S_Pos)               /*!< 0x007F0000 */
#define FDCAN_RXF0C_F0S           FDCAN_RXF0C_F0S_Msk                          /*!<Number of Rx FIFO 0 elements              */
#define FDCAN_RXF0C_F0WM_Pos      (24U)
#define FDCAN_RXF0C_F0WM_Msk      (0x7FU << FDCAN_RXF0C_F0WM_Pos)              /*!< 0x7F000000 */
#define FDCAN_RXF0C_F0WM          FDCAN_RXF0C_F0WM_Msk                         /*!<FIFO 0 Watermark                          */
#define FDCAN_RXF0C_F0OM_Pos      (31U)
#define FDCAN_RXF0C_F0OM_Msk      (0x1U << FDCAN_RXF0C_F0OM_Pos)               /*!< 0x80000000 */
#define FDCAN_RXF0C_F0OM          FDCAN_RXF0C_F0OM_Msk                         /*!<FIFO 0 Operation Mode                     */

/*****************  Bit definition for FDCAN_RXF0S register  ********************/
#define FDCAN_RXF0S_F0FL_Pos      (0U)
#define FDCAN_RXF0S_F0FL_Msk      (0x7FU << FDCAN_RXF0S_F0FL_Pos)              /*!< 0x0000007F */
#define FDCAN_RXF0S_F0FL          FDCAN_RXF0S_F0FL_Msk                         /*!<Rx FIFO 0 Fill Level                      */
#define FDCAN_RXF0S_F0GI_Pos      (8U)
#define FDCAN_RXF0S_F0GI_Msk      (0x3FU << FDCAN_RXF0S_F0GI_Pos)              /*!< 0x00003F00 */
#define FDCAN_RXF0S_F0GI          FDCAN_RXF0S_F0GI_Msk                         /*!<Rx FIFO 0 Get Index                       */
#define FDCAN_RXF0S_F0PI_Pos      (16U)
#define FDCAN_RXF0S_F0PI_Msk      (0x3FU << FDCAN_RXF0S_F0PI_Pos)              /*!< 0x003F0000 */
#define FDCAN_RXF0S_F0PI          FDCAN_RXF0S_F0PI_Msk                         /*!<Rx FIFO 0 Put Index                       */
#define FDCAN_RXF0S_F0F_Pos       (24U)
#define FDCAN_RXF0S_F0F_Msk       (0x1U << FDCAN_RXF0S_F0F_Pos)                /*!< 0x01000000 */
#define FDCAN_RXF0S_F0F           FDCAN_RXF0S_F0F_Msk                          /*!<Rx FIFO 0 Full                            */
#define FDCAN_RXF0S_RF0L_Pos      (25U)
#define FDCAN_RXF0S_RF0L_Msk      (0x1U << FDCAN_RXF0S_RF0L_Pos)               /*!< 0x02000000 */
#define FDCAN_RXF0S_RF0L          FDCAN_RXF0S_RF0L_Msk                         /*!<Rx FIFO 0 Message Lost                    */

/*****************  Bit definition for FDCAN_RXF0A register  ********************/
#define FDCAN_RXF0A_F0AI_Pos      (0U)
#define FDCAN_RXF0A_F0AI_Msk      (0x3FU << FDCAN_RXF0A_F0AI_Pos)              /*!< 0x0000003F */
#define FDCAN_RXF0A_F0AI          FDCAN_RXF0A_F0AI_Msk                         /*!<Rx FIFO 0 Acknowledge Index               */

/*****************  Bit definition for FDCAN_RXBC register  ********************/
#define FDCAN_RXBC_RBSA_Pos       (2U)
#define FDCAN_RXBC_RBSA_Msk       (0x3FFFU << FDCAN_RXBC_RBSA_Pos)             /*!< 0x0000FFFC */
#define FDCAN_RXBC_RBSA           FDCAN_RXBC_RBSA_Msk                          /*!<Rx Buffer Start Address                   */

/*****************  Bit definition for FDCAN_RXF1C register  ********************/
#define FDCAN_RXF1C_F1SA_Pos      (2U)
#define FDCAN_RXF1C_F1SA_Msk      (0x3FFFU << FDCAN_RXF1C_F1SA_Pos)            /*!< 0x0000FFFC */
#define FDCAN_RXF1C_F1SA          FDCAN_RXF1C_F1SA_Msk                         /*!<Rx FIFO 1 Start Address                   */
#define FDCAN_RXF1C_F1S_Pos       (16U)
#define FDCAN_RXF1C_F1S_Msk       (0x7FU << FDCAN_RXF1C_F1S_Pos)               /*!< 0x007F0000 */
#define FDCAN_RXF1C_F1S           FDCAN_RXF1C_F1S_Msk                          /*!<Number of Rx FIFO 1 elements              */
#define FDCAN_RXF1C_F1WM_Pos      (24U)
#define FDCAN_RXF1C_F1WM_Msk      (0x7FU << FDCAN_RXF1C_F1WM_Pos)              /*!< 0x7F000000 */
#define FDCAN_RXF1C_F1WM          FDCAN_RXF1C_F1WM_Msk                         /*!<Rx FIFO 1 Watermark                       */
#define FDCAN_RXF1C_F1OM_Pos      (31U)
#define FDCAN_RXF1C_F1OM_Msk      (0x1U << FDCAN_RXF1C_F1OM_Pos)               /*!< 0x80000000 */
#define FDCAN_RXF1C_F1OM          FDCAN_RXF1C_F1OM_Msk                         /*!<FIFO 1 Operation Mode                     */

/*****************  Bit definition for FDCAN_RXF1S register  ********************/
#define FDCAN_RXF1S_F1FL_Pos      (0U)
#define FDCAN_RXF1S_F1FL_Msk      (0x7FU << FDCAN_RXF1S_F1FL_Pos)              /*!< 0x0000007F */
#define FDCAN_RXF1S_F1FL          FDCAN_RXF1S_F1FL_Msk                         /*!<Rx FIFO 1 Fill Level                      */
#define FDCAN_RXF1S_F1GI_Pos      (8U)
#define FDCAN_RXF1S_F1GI_Msk      (0x3FU << FDCAN_RXF1S_F1GI_Pos)              /*!< 0x00003F00 */
#define FDCAN_RXF1S_F1GI          FDCAN_RXF1S_F1GI_Msk                         /*!<Rx FIFO 1 Get Index                       */
#define FDCAN_RXF1S_F1PI_Pos      (16U)
#define FDCAN_RXF1S_F1PI_Msk      (0x3FU << FDCAN_RXF1S_F1PI_Pos)              /*!< 0x003F0000 */
#define FDCAN_RXF1S_F1PI          FDCAN_RXF1S_F1PI_Msk                         /*!<Rx FIFO 1 Put Index                       */
#define FDCAN_RXF1S_F1F_Pos       (24U)
#define FDCAN_RXF1S_F1F_Msk       (0x1U << FDCAN_RXF1S_F1F_Pos)                /*!< 0x01000000 */
#define FDCAN_RXF1S_F1F           FDCAN_RXF1S_F1F_Msk                          /*!<Rx FIFO 1 Full                            */
#define FDCAN_RXF1S_RF1L_Pos      (25U)
#define FDCAN_RXF1S_RF1L_Msk      (0x1U << FDCAN_RXF1S_RF1L_Pos)               /*!< 0x02000000 */
#define FDCAN_RXF1S_RF1L          FDCAN_RXF1S_RF1L_Msk                         /*!<Rx FIFO 1 Message Lost                    */
#define FDCAN_RXF1S_DMS_Pos       (30U)
#define FDCAN_RXF1S_DMS_Msk       (0x3U << FDCAN_RXF1S_DMS_Pos)                /*!< 0xC0000000 */
#define FDCAN_RXF1S_DMS           FDCAN_RXF1S_DMS_Msk                          /*!<Debug Message Status                      */

/*****************  Bit definition for FDCAN_RXF1A register  ********************/
#define FDCAN_RXF1A_F1AI_Pos      (0U)
#define FDCAN_RXF1A_F1AI_Msk      (0x3FU << FDCAN_RXF1A_F1AI_Pos)              /*!< 0x0000003F */
#define FDCAN_RXF1A_F1AI          FDCAN_RXF1A_F1AI_Msk                         /*!<Rx FIFO 1 Acknowledge Index               */

/*****************  Bit definition for FDCAN_RXESC register  ********************/
#define FDCAN_RXESC_F0DS_Pos      (0U)
#define FDCAN_RXESC_F0DS_Msk      (0x7U << FDCAN_RXESC_F0DS_Pos)               /*!< 0x00000007 */
#define FDCAN_RXESC_F0DS          FDCAN_RXESC_F0DS_Msk                         /*!<Rx FIFO 1 Data Field Size                 */
#define FDCAN_RXESC_F1DS_Pos      (4U)
#define FDCAN_RXESC_F1DS_Msk      (0x7U << FDCAN_RXESC_F1DS_Pos)               /*!< 0x00000070 */
#define FDCAN_RXESC_F1DS          FDCAN_RXESC_F1DS_Msk                         /*!<Rx FIFO 0 Data Field Size                 */
#define FDCAN_RXESC_RBDS_Pos      (8U)
#define FDCAN_RXESC_RBDS_Msk      (0x7U << FDCAN_RXESC_RBDS_Pos)               /*!< 0x00000700 */
#define FDCAN_RXESC_RBDS          FDCAN_RXESC_RBDS_Msk                         /*!<Rx Buffer Data Field Size                 */

/*****************  Bit definition for FDCAN_TXBC register  *********************/
#define FDCAN_TXBC_TBSA_Pos       (2U)
#define FDCAN_TXBC_TBSA_Msk       (0x3FFFU << FDCAN_TXBC_TBSA_Pos)             /*!< 0x000000FC */
#define FDCAN_TXBC_TBSA           FDCAN_TXBC_TBSA_Msk                          /*!<Tx Buffers Start Address                  */
#define FDCAN_TXBC_NDTB_Pos       (16U)
#define FDCAN_TXBC_NDTB_Msk       (0x3FU << FDCAN_TXBC_NDTB_Pos)               /*!< 0x003F0000 */
#define FDCAN_TXBC_NDTB           FDCAN_TXBC_NDTB_Msk                          /*!<Number of Dedicated Transmit Buffers      */
#define FDCAN_TXBC_TFQS_Pos       (24U)
#define FDCAN_TXBC_TFQS_Msk       (0x3FU << FDCAN_TXBC_TFQS_Pos)               /*!< 0x3F000000 */
#define FDCAN_TXBC_TFQS           FDCAN_TXBC_TFQS_Msk                          /*!<Transmit FIFO/Queue Size                  */
#define FDCAN_TXBC_TFQM_Pos       (30U)
#define FDCAN_TXBC_TFQM_Msk       (0x1U << FDCAN_TXBC_TFQM_Pos)                /*!< 0x40000000 */
#define FDCAN_TXBC_TFQM           FDCAN_TXBC_TFQM_Msk                          /*!<Tx FIFO/Queue Mode                        */

/*****************  Bit definition for FDCAN_TXFQS register  *********************/
#define FDCAN_TXFQS_TFFL_Pos      (0U)
#define FDCAN_TXFQS_TFFL_Msk      (0x3FU << FDCAN_TXFQS_TFFL_Pos)              /*!< 0x0000003F */
#define FDCAN_TXFQS_TFFL          FDCAN_TXFQS_TFFL_Msk                         /*!<Tx FIFO Free Level                        */
#define FDCAN_TXFQS_TFGI_Pos      (8U)
#define FDCAN_TXFQS_TFGI_Msk      (0x1FU << FDCAN_TXFQS_TFGI_Pos)              /*!< 0x00001F00 */
#define FDCAN_TXFQS_TFGI          FDCAN_TXFQS_TFGI_Msk                         /*!<Tx FIFO Get Index                         */
#define FDCAN_TXFQS_TFQPI_Pos     (16U)
#define FDCAN_TXFQS_TFQPI_Msk     (0x1FU << FDCAN_TXFQS_TFQPI_Pos)             /*!< 0x001F0000 */
#define FDCAN_TXFQS_TFQPI         FDCAN_TXFQS_TFQPI_Msk                        /*!<Tx FIFO/Queue Put Index                   */
#define FDCAN_TXFQS_TFQF_Pos      (21U)
#define FDCAN_TXFQS_TFQF_Msk      (0x1U << FDCAN_TXFQS_TFQF_Pos)               /*!< 0x00200000 */
#define FDCAN_TXFQS_TFQF          FDCAN_TXFQS_TFQF_Msk                         /*!<Tx FIFO/Queue Full                        */

/*****************  Bit definition for FDCAN_TXESC register  *********************/
#define FDCAN_TXESC_TBDS_Pos      (0U)
#define FDCAN_TXESC_TBDS_Msk      (0x7U << FDCAN_TXESC_TBDS_Pos)               /*!< 0x00000007 */
#define FDCAN_TXESC_TBDS          FDCAN_TXESC_TBDS_Msk                         /*!<Tx Buffer Data Field Size                 */

/*****************  Bit definition for FDCAN_TXBRP register  *********************/
#define FDCAN_TXBRP_TRP_Pos       (0U)
#define FDCAN_TXBRP_TRP_Msk       (0xFFFFFFFFU << FDCAN_TXBRP_TRP_Pos)         /*!< 0xFFFFFFFF */
#define FDCAN_TXBRP_TRP           FDCAN_TXBRP_TRP_Msk                          /*!<Transmission Request Pending              */

/*****************  Bit definition for FDCAN_TXBAR register  *********************/
#define FDCAN_TXBAR_AR_Pos        (0U)
#define FDCAN_TXBAR_AR_Msk        (0xFFFFFFFFU << FDCAN_TXBAR_AR_Pos)          /*!< 0xFFFFFFFF */
#define FDCAN_TXBAR_AR            FDCAN_TXBAR_AR_Msk                           /*!<Add Request                               */

/*****************  Bit definition for FDCAN_TXBCR register  *********************/
#define FDCAN_TXBCR_CR_Pos        (0U)
#define FDCAN_TXBCR_CR_Msk        (0xFFFFFFFFU << FDCAN_TXBCR_CR_Pos)          /*!< 0xFFFFFFFF */
#define FDCAN_TXBCR_CR            FDCAN_TXBCR_CR_Msk                           /*!<Cancellation Request                      */

/*****************  Bit definition for FDCAN_TXBTO register  *********************/
#define FDCAN_TXBTO_TO_Pos        (0U)
#define FDCAN_TXBTO_TO_Msk        (0xFFFFFFFFU << FDCAN_TXBTO_TO_Pos)          /*!< 0xFFFFFFFF */
#define FDCAN_TXBTO_TO            FDCAN_TXBTO_TO_Msk                           /*!<Transmission Occurred                     */

/*****************  Bit definition for FDCAN_TXBCF register  *********************/
#define FDCAN_TXBCF_CF_Pos        (0U)
#define FDCAN_TXBCF_CF_Msk        (0xFFFFFFFFU << FDCAN_TXBCF_CF_Pos)          /*!< 0xFFFFFFFF */
#define FDCAN_TXBCF_CF            FDCAN_TXBCF_CF_Msk                           /*!<Cancellation Finished                     */

/*****************  Bit definition for FDCAN_TXBTIE register  ********************/
#define FDCAN_TXBTIE_TIE_Pos      (0U)
#define FDCAN_TXBTIE_TIE_Msk      (0xFFFFFFFFU << FDCAN_TXBTIE_TIE_Pos)        /*!< 0xFFFFFFFF */
#define FDCAN_TXBTIE_TIE          FDCAN_TXBTIE_TIE_Msk                         /*!<Transmission Interrupt Enable             */

/*****************  Bit definition for FDCAN_ TXBCIE register  *******************/
#define FDCAN_TXBCIE_CF_Pos       (0U)
#define FDCAN_TXBCIE_CF_Msk       (0xFFFFFFFFU << FDCAN_TXBCIE_CF_Pos)         /*!< 0xFFFFFFFF */
#define FDCAN_TXBCIE_CF           FDCAN_TXBCIE_CF_Msk                          /*!<Cancellation Finished Interrupt Enable    */

/*****************  Bit definition for FDCAN_TXEFC register  *********************/
#define FDCAN_TXEFC_EFSA_Pos      (2U)
#define FDCAN_TXEFC_EFSA_Msk      (0x3FFFU << FDCAN_TXEFC_EFSA_Pos)            /*!< 0x0000FFFC */
#define FDCAN_TXEFC_EFSA          FDCAN_TXEFC_EFSA_Msk                         /*!<Event FIFO Start Address                  */
#define FDCAN_TXEFC_EFS_Pos       (16U)
#define FDCAN_TXEFC_EFS_Msk       (0x3FU << FDCAN_TXEFC_EFS_Pos)               /*!< 0x003F0000 */
#define FDCAN_TXEFC_EFS           FDCAN_TXEFC_EFS_Msk                          /*!<Event FIFO Size                           */
#define FDCAN_TXEFC_EFWM_Pos      (24U)
#define FDCAN_TXEFC_EFWM_Msk      (0x3FU << FDCAN_TXEFC_EFWM_Pos)              /*!< 0x3F000000 */
#define FDCAN_TXEFC_EFWM          FDCAN_TXEFC_EFWM_Msk                         /*!<Event FIFO Watermark                      */

/*****************  Bit definition for FDCAN_TXEFS register  *********************/
#define FDCAN_TXEFS_EFFL_Pos      (0U)
#define FDCAN_TXEFS_EFFL_Msk      (0x3FU << FDCAN_TXEFS_EFFL_Pos)              /*!< 0x0000003F */
#define FDCAN_TXEFS_EFFL          FDCAN_TXEFS_EFFL_Msk                         /*!<Event FIFO Fill Level                     */
#define FDCAN_TXEFS_EFGI_Pos      (8U)
#define FDCAN_TXEFS_EFGI_Msk      (0x1FU << FDCAN_TXEFS_EFGI_Pos)              /*!< 0x00001F00 */
#define FDCAN_TXEFS_EFGI          FDCAN_TXEFS_EFGI_Msk                         /*!<Event FIFO Get Index                      */
#define FDCAN_TXEFS_EFPI_Pos      (16U)
#define FDCAN_TXEFS_EFPI_Msk      (0x1FU << FDCAN_TXEFS_EFPI_Pos)              /*!< 0x001F0000 */
#define FDCAN_TXEFS_EFPI          FDCAN_TXEFS_EFPI_Msk                         /*!<Event FIFO Put Index                      */
#define FDCAN_TXEFS_EFF_Pos       (24U)
#define FDCAN_TXEFS_EFF_Msk       (0x1U << FDCAN_TXEFS_EFF_Pos)                /*!< 0x01000000 */
#define FDCAN_TXEFS_EFF           FDCAN_TXEFS_EFF_Msk                          /*!<Event FIFO Full                           */
#define FDCAN_TXEFS_TEFL_Pos      (25U)
#define FDCAN_TXEFS_TEFL_Msk      (0x1U << FDCAN_TXEFS_TEFL_Pos)               /*!< 0x02000000 */
#define FDCAN_TXEFS_TEFL          FDCAN_TXEFS_TEFL_Msk                         /*!<Tx Event FIFO Element Lost                */

/*****************  Bit definition for FDCAN_TXEFA register  *********************/
#define FDCAN_TXEFA_EFAI_Pos      (0U)
#define FDCAN_TXEFA_EFAI_Msk      (0x1FU << FDCAN_TXEFA_EFAI_Pos)              /*!< 0x0000001F */
#define FDCAN_TXEFA_EFAI          FDCAN_TXEFA_EFAI_Msk                         /*!<Event FIFO Acknowledge Index              */

/*****************  Bit definition for FDCAN_TTTMC register  *********************/
#define FDCAN_TTTMC_TMSA_Pos      (2U)
#define FDCAN_TTTMC_TMSA_Msk      (0x3FFFU << FDCAN_TTTMC_TMSA_Pos)            /*!< 0x0000FFFC */
#define FDCAN_TTTMC_TMSA          FDCAN_TTTMC_TMSA_Msk                         /*!<Trigger Memory Start Address              */
#define FDCAN_TTTMC_TME_Pos       (16U)
#define FDCAN_TTTMC_TME_Msk       (0x7FU << FDCAN_TTTMC_TME_Pos)               /*!< 0x007F0000 */
#define FDCAN_TTTMC_TME           FDCAN_TTTMC_TME_Msk                          /*!<Trigger Memory Elements                   */

/*****************  Bit definition for FDCAN_TTRMC register  *********************/
#define FDCAN_TTRMC_RID_Pos       (0U)
#define FDCAN_TTRMC_RID_Msk       (0x1FFFFFFFU << FDCAN_TTRMC_RID_Pos)         /*!< 0x1FFFFFFF */
#define FDCAN_TTRMC_RID           FDCAN_TTRMC_RID_Msk                          /*!<Reference Identifier                      */
#define FDCAN_TTRMC_XTD_Pos       (30U)
#define FDCAN_TTRMC_XTD_Msk       (0x1U << FDCAN_TTRMC_XTD_Pos)                /*!< 0x40000000 */
#define FDCAN_TTRMC_XTD           FDCAN_TTRMC_XTD_Msk                          /*!< Extended Identifier                      */
#define FDCAN_TTRMC_RMPS_Pos      (31U)
#define FDCAN_TTRMC_RMPS_Msk      (0x1U << FDCAN_TTRMC_RMPS_Pos)               /*!< 0x80000000 */
#define FDCAN_TTRMC_RMPS          FDCAN_TTRMC_RMPS_Msk                         /*!<Reference Message Payload Select          */

/*****************  Bit definition for FDCAN_TTOCF register  *********************/
#define FDCAN_TTOCF_OM_Pos        (0U)
#define FDCAN_TTOCF_OM_Msk        (0x3U << FDCAN_TTOCF_OM_Pos)                 /*!< 0x00000003 */
#define FDCAN_TTOCF_OM            FDCAN_TTOCF_OM_Msk                           /*!<Operation Mode                            */
#define FDCAN_TTOCF_GEN_Pos       (3U)
#define FDCAN_TTOCF_GEN_Msk       (0x1U << FDCAN_TTOCF_GEN_Pos)                /*!< 0x00000008 */
#define FDCAN_TTOCF_GEN           FDCAN_TTOCF_GEN_Msk                          /*!<Gap Enable                                */
#define FDCAN_TTOCF_TM_Pos        (4U)
#define FDCAN_TTOCF_TM_Msk        (0x1U << FDCAN_TTOCF_TM_Pos)                 /*!< 0x00000010 */
#define FDCAN_TTOCF_TM            FDCAN_TTOCF_TM_Msk                           /*!<Time Master                               */
#define FDCAN_TTOCF_LDSDL_Pos     (5U)
#define FDCAN_TTOCF_LDSDL_Msk     (0x7U << FDCAN_TTOCF_LDSDL_Pos)              /*!< 0x000000E0 */
#define FDCAN_TTOCF_LDSDL         FDCAN_TTOCF_LDSDL_Msk                        /*!<LD of Synchronization Deviation Limit     */
#define FDCAN_TTOCF_IRTO_Pos      (8U)
#define FDCAN_TTOCF_IRTO_Msk      (0x7FU << FDCAN_TTOCF_IRTO_Pos)              /*!< 0x00007F00 */
#define FDCAN_TTOCF_IRTO          FDCAN_TTOCF_IRTO_Msk                         /*!<Initial Reference Trigger Offset          */
#define FDCAN_TTOCF_EECS_Pos      (15U)
#define FDCAN_TTOCF_EECS_Msk      (0x1U << FDCAN_TTOCF_EECS_Pos)               /*!< 0x00008000 */
#define FDCAN_TTOCF_EECS          FDCAN_TTOCF_EECS_Msk                         /*!<Enable External Clock Synchronization     */
#define FDCAN_TTOCF_AWL_Pos       (16U)
#define FDCAN_TTOCF_AWL_Msk       (0xFFU << FDCAN_TTOCF_AWL_Pos)               /*!< 0x00FF0000 */
#define FDCAN_TTOCF_AWL           FDCAN_TTOCF_AWL_Msk                          /*!<Application Watchdog Limit                */
#define FDCAN_TTOCF_EGTF_Pos      (24U)
#define FDCAN_TTOCF_EGTF_Msk      (0x1U << FDCAN_TTOCF_EGTF_Pos)               /*!< 0x01000000 */
#define FDCAN_TTOCF_EGTF          FDCAN_TTOCF_EGTF_Msk                         /*!<Enable Global Time Filtering              */
#define FDCAN_TTOCF_ECC_Pos       (25U)
#define FDCAN_TTOCF_ECC_Msk       (0x1U << FDCAN_TTOCF_ECC_Pos)                /*!< 0x02000000 */
#define FDCAN_TTOCF_ECC           FDCAN_TTOCF_ECC_Msk                          /*!<Enable Clock Calibration                  */
#define FDCAN_TTOCF_EVTP_Pos      (26U)
#define FDCAN_TTOCF_EVTP_Msk      (0x1U << FDCAN_TTOCF_EVTP_Pos)               /*!< 0x04000000 */
#define FDCAN_TTOCF_EVTP          FDCAN_TTOCF_EVTP_Msk                         /*!<Event Trigger Polarity                    */

/*****************  Bit definition for FDCAN_TTMLM register  *********************/
#define FDCAN_TTMLM_CCM_Pos       (0U)
#define FDCAN_TTMLM_CCM_Msk       (0x3FU << FDCAN_TTMLM_CCM_Pos)               /*!< 0x0000003F */
#define FDCAN_TTMLM_CCM           FDCAN_TTMLM_CCM_Msk                          /*!<Cycle Count Max                           */
#define FDCAN_TTMLM_CSS_Pos       (6U)
#define FDCAN_TTMLM_CSS_Msk       (0x3U << FDCAN_TTMLM_CSS_Pos)                /*!< 0x000000C0 */
#define FDCAN_TTMLM_CSS           FDCAN_TTMLM_CSS_Msk                          /*!<Cycle Start Synchronization               */
#define FDCAN_TTMLM_TXEW_Pos      (8U)
#define FDCAN_TTMLM_TXEW_Msk      (0xFU << FDCAN_TTMLM_TXEW_Pos)               /*!< 0x00000F00 */
#define FDCAN_TTMLM_TXEW          FDCAN_TTMLM_TXEW_Msk                         /*!<Tx Enable Window                          */
#define FDCAN_TTMLM_ENTT_Pos      (16U)
#define FDCAN_TTMLM_ENTT_Msk      (0xFFFU << FDCAN_TTMLM_ENTT_Pos)             /*!< 0x0FFF0000 */
#define FDCAN_TTMLM_ENTT          FDCAN_TTMLM_ENTT_Msk                         /*!<Expected Number of Tx Triggers            */

/*****************  Bit definition for FDCAN_TURCF register  *********************/
#define FDCAN_TURCF_NCL_Pos       (0U)
#define FDCAN_TURCF_NCL_Msk       (0xFFFFU << FDCAN_TURCF_NCL_Pos)             /*!< 0x0000FFFF */
#define FDCAN_TURCF_NCL           FDCAN_TURCF_NCL_Msk                          /*!<Numerator Configuration Low               */
#define FDCAN_TURCF_DC_Pos        (16U)
#define FDCAN_TURCF_DC_Msk        (0x3FFFU << FDCAN_TURCF_DC_Pos)              /*!< 0x3FFF0000 */
#define FDCAN_TURCF_DC            FDCAN_TURCF_DC_Msk                           /*!<Denominator Configuration                 */
#define FDCAN_TURCF_ELT_Pos       (31U)
#define FDCAN_TURCF_ELT_Msk       (0x1U << FDCAN_TURCF_ELT_Pos)                /*!< 0x80000000 */
#define FDCAN_TURCF_ELT           FDCAN_TURCF_ELT_Msk                          /*!<Enable Local Time                         */

/*****************  Bit definition for FDCAN_TTOCN register  ********************/
#define FDCAN_TTOCN_SGT_Pos       (0U)
#define FDCAN_TTOCN_SGT_Msk       (0x1U << FDCAN_TTOCN_SGT_Pos)                /*!< 0x00000001 */
#define FDCAN_TTOCN_SGT           FDCAN_TTOCN_SGT_Msk                          /*!<Set Global time                           */
#define FDCAN_TTOCN_ECS_Pos       (1U)
#define FDCAN_TTOCN_ECS_Msk       (0x1U << FDCAN_TTOCN_ECS_Pos)                /*!< 0x00000002 */
#define FDCAN_TTOCN_ECS           FDCAN_TTOCN_ECS_Msk                          /*!<External Clock Synchronization            */
#define FDCAN_TTOCN_SWP_Pos       (2U)
#define FDCAN_TTOCN_SWP_Msk       (0x1U << FDCAN_TTOCN_SWP_Pos)                /*!< 0x00000004 */
#define FDCAN_TTOCN_SWP           FDCAN_TTOCN_SWP_Msk                          /*!<Stop Watch Polarity                       */
#define FDCAN_TTOCN_SWS_Pos       (3U)
#define FDCAN_TTOCN_SWS_Msk       (0x3U << FDCAN_TTOCN_SWS_Pos)                /*!< 0x00000018 */
#define FDCAN_TTOCN_SWS           FDCAN_TTOCN_SWS_Msk                          /*!<Stop Watch Source                         */
#define FDCAN_TTOCN_RTIE_Pos      (5U)
#define FDCAN_TTOCN_RTIE_Msk      (0x1U << FDCAN_TTOCN_RTIE_Pos)               /*!< 0x00000020 */
#define FDCAN_TTOCN_RTIE          FDCAN_TTOCN_RTIE_Msk                         /*!<Register Time Mark Interrupt Pulse Enable */
#define FDCAN_TTOCN_TMC_Pos       (6U)
#define FDCAN_TTOCN_TMC_Msk       (0x3U << FDCAN_TTOCN_TMC_Pos)                /*!< 0x000000C0 */
#define FDCAN_TTOCN_TMC           FDCAN_TTOCN_TMC_Msk                          /*!<Register Time Mark Compare                */
#define FDCAN_TTOCN_TTIE_Pos      (8U)
#define FDCAN_TTOCN_TTIE_Msk      (0x1U << FDCAN_TTOCN_TTIE_Pos)               /*!< 0x00000100 */
#define FDCAN_TTOCN_TTIE          FDCAN_TTOCN_TTIE_Msk                         /*!<Trigger Time Mark Interrupt Pulse Enable  */
#define FDCAN_TTOCN_GCS_Pos       (9U)
#define FDCAN_TTOCN_GCS_Msk       (0x1U << FDCAN_TTOCN_GCS_Pos)                /*!< 0x00000200 */
#define FDCAN_TTOCN_GCS           FDCAN_TTOCN_GCS_Msk                          /*!<Gap Control Select                        */
#define FDCAN_TTOCN_FGP_Pos       (10U)
#define FDCAN_TTOCN_FGP_Msk       (0x1U << FDCAN_TTOCN_FGP_Pos)                /*!< 0x00000400 */
#define FDCAN_TTOCN_FGP           FDCAN_TTOCN_FGP_Msk                          /*!<Finish Gap                                */
#define FDCAN_TTOCN_TMG_Pos       (11U)
#define FDCAN_TTOCN_TMG_Msk       (0x1U << FDCAN_TTOCN_TMG_Pos)                /*!< 0x00000800 */
#define FDCAN_TTOCN_TMG           FDCAN_TTOCN_TMG_Msk                          /*!<Time Mark Gap                             */
#define FDCAN_TTOCN_NIG_Pos       (12U)
#define FDCAN_TTOCN_NIG_Msk       (0x1U << FDCAN_TTOCN_NIG_Pos)                /*!< 0x00001000 */
#define FDCAN_TTOCN_NIG           FDCAN_TTOCN_NIG_Msk                          /*!<Next is Gap                               */
#define FDCAN_TTOCN_ESCN_Pos      (13U)
#define FDCAN_TTOCN_ESCN_Msk      (0x1U << FDCAN_TTOCN_ESCN_Pos)               /*!< 0x00002000 */
#define FDCAN_TTOCN_ESCN          FDCAN_TTOCN_ESCN_Msk                         /*!<External Synchronization Control          */
#define FDCAN_TTOCN_LCKC_Pos      (15U)
#define FDCAN_TTOCN_LCKC_Msk      (0x1U << FDCAN_TTOCN_LCKC_Pos)               /*!< 0x00008000 */
#define FDCAN_TTOCN_LCKC          FDCAN_TTOCN_LCKC_Msk                         /*!<TT Operation Control Register Locked      */

/*****************  Bit definition for FDCAN_TTGTP register  ********************/
#define FDCAN_TTGTP_TP_Pos        (0U)
#define FDCAN_TTGTP_TP_Msk        (0xFFFFU << FDCAN_TTGTP_TP_Pos)              /*!< 0x0000FFFF */
#define FDCAN_TTGTP_TP            FDCAN_TTGTP_TP_Msk                           /*!<Time Preset                               */
#define FDCAN_TTGTP_CTP_Pos       (16U)
#define FDCAN_TTGTP_CTP_Msk       (0xFFFFU << FDCAN_TTGTP_CTP_Pos)             /*!< 0xFFFF0000 */
#define FDCAN_TTGTP_CTP           FDCAN_TTGTP_CTP_Msk                          /*!<Cycle Time Target Phase                   */

/*****************  Bit definition for FDCAN_TTTMK register  ********************/
#define FDCAN_TTTMK_TM_Pos        (0U)
#define FDCAN_TTTMK_TM_Msk        (0xFFFFU << FDCAN_TTTMK_TM_Pos)              /*!< 0x0000FFFF */
#define FDCAN_TTTMK_TM            FDCAN_TTTMK_TM_Msk                           /*!<Time Mark                                 */
#define FDCAN_TTTMK_TICC_Pos      (16U)
#define FDCAN_TTTMK_TICC_Msk      (0x7FU << FDCAN_TTTMK_TICC_Pos)              /*!< 0x007F0000 */
#define FDCAN_TTTMK_TICC          FDCAN_TTTMK_TICC_Msk                         /*!<Time Mark Cycle Code                      */
#define FDCAN_TTTMK_LCKM_Pos      (31U)
#define FDCAN_TTTMK_LCKM_Msk      (0x1U << FDCAN_TTTMK_LCKM_Pos)               /*!< 0x80000000 */
#define FDCAN_TTTMK_LCKM          FDCAN_TTTMK_LCKM_Msk                         /*!<TT Time Mark Register Locked              */

/*****************  Bit definition for FDCAN_TTIR register  ********************/
#define FDCAN_TTIR_SBC_Pos        (0U)
#define FDCAN_TTIR_SBC_Msk        (0x1U << FDCAN_TTIR_SBC_Pos)                 /*!< 0x00000001 */
#define FDCAN_TTIR_SBC            FDCAN_TTIR_SBC_Msk                           /*!<Start of Basic Cycle                      */
#define FDCAN_TTIR_SMC_Pos        (1U)
#define FDCAN_TTIR_SMC_Msk        (0x1U << FDCAN_TTIR_SMC_Pos)                 /*!< 0x00000002 */
#define FDCAN_TTIR_SMC            FDCAN_TTIR_SMC_Msk                           /*!<Start of Matrix Cycle                     */
#define FDCAN_TTIR_CSM_Pos        (2U)
#define FDCAN_TTIR_CSM_Msk        (0x1U << FDCAN_TTIR_CSM_Pos)                 /*!< 0x00000004 */
#define FDCAN_TTIR_CSM            FDCAN_TTIR_CSM_Msk                           /*!<Change of Synchronization Mode            */
#define FDCAN_TTIR_SOG_Pos        (3U)
#define FDCAN_TTIR_SOG_Msk        (0x1U << FDCAN_TTIR_SOG_Pos)                 /*!< 0x00000008 */
#define FDCAN_TTIR_SOG            FDCAN_TTIR_SOG_Msk                           /*!<Start of Gap                              */
#define FDCAN_TTIR_RTMI_Pos       (4U)
#define FDCAN_TTIR_RTMI_Msk       (0x1U << FDCAN_TTIR_RTMI_Pos)                /*!< 0x00000010 */
#define FDCAN_TTIR_RTMI           FDCAN_TTIR_RTMI_Msk                          /*!<Register Time Mark Interrupt              */
#define FDCAN_TTIR_TTMI_Pos       (5U)
#define FDCAN_TTIR_TTMI_Msk       (0x1U << FDCAN_TTIR_TTMI_Pos)                /*!< 0x00000020 */
#define FDCAN_TTIR_TTMI           FDCAN_TTIR_TTMI_Msk                          /*!<Trigger Time Mark Event Internal          */
#define FDCAN_TTIR_SWE_Pos        (6U)
#define FDCAN_TTIR_SWE_Msk        (0x1U << FDCAN_TTIR_SWE_Pos)                 /*!< 0x00000040 */
#define FDCAN_TTIR_SWE            FDCAN_TTIR_SWE_Msk                           /*!<Stop Watch Event                          */
#define FDCAN_TTIR_GTW_Pos        (7U)
#define FDCAN_TTIR_GTW_Msk        (0x1U << FDCAN_TTIR_GTW_Pos)                 /*!< 0x00000080 */
#define FDCAN_TTIR_GTW            FDCAN_TTIR_GTW_Msk                           /*!<Global Time Wrap                          */
#define FDCAN_TTIR_GTD_Pos        (8U)
#define FDCAN_TTIR_GTD_Msk        (0x1U << FDCAN_TTIR_GTD_Pos)                 /*!< 0x00000100 */
#define FDCAN_TTIR_GTD            FDCAN_TTIR_GTD_Msk                           /*!<Global Time Discontinuity                 */
#define FDCAN_TTIR_GTE_Pos        (9U)
#define FDCAN_TTIR_GTE_Msk        (0x1U << FDCAN_TTIR_GTE_Pos)                 /*!< 0x00000200 */
#define FDCAN_TTIR_GTE            FDCAN_TTIR_GTE_Msk                           /*!<Global Time Error                         */
#define FDCAN_TTIR_TXU_Pos        (10U)
#define FDCAN_TTIR_TXU_Msk        (0x1U << FDCAN_TTIR_TXU_Pos)                 /*!< 0x00000400 */
#define FDCAN_TTIR_TXU            FDCAN_TTIR_TXU_Msk                           /*!<Tx Count Underflow                        */
#define FDCAN_TTIR_TXO_Pos        (11U)
#define FDCAN_TTIR_TXO_Msk        (0x1U << FDCAN_TTIR_TXO_Pos)                 /*!< 0x00000800 */
#define FDCAN_TTIR_TXO            FDCAN_TTIR_TXO_Msk                           /*!<Tx Count Overflow                         */
#define FDCAN_TTIR_SE1_Pos        (12U)
#define FDCAN_TTIR_SE1_Msk        (0x1U << FDCAN_TTIR_SE1_Pos)                 /*!< 0x00001000 */
#define FDCAN_TTIR_SE1            FDCAN_TTIR_SE1_Msk                           /*!<Scheduling Error 1                        */
#define FDCAN_TTIR_SE2_Pos        (13U)
#define FDCAN_TTIR_SE2_Msk        (0x1U << FDCAN_TTIR_SE2_Pos)                 /*!< 0x00002000 */
#define FDCAN_TTIR_SE2            FDCAN_TTIR_SE2_Msk                           /*!<Scheduling Error 2                        */
#define FDCAN_TTIR_ELC_Pos        (14U)
#define FDCAN_TTIR_ELC_Msk        (0x1U << FDCAN_TTIR_ELC_Pos)                 /*!< 0x00004000 */
#define FDCAN_TTIR_ELC            FDCAN_TTIR_ELC_Msk                           /*!<Error Level Changed                       */
#define FDCAN_TTIR_IWT_Pos        (15U)
#define FDCAN_TTIR_IWT_Msk        (0x1U << FDCAN_TTIR_IWT_Pos)                 /*!< 0x00008000 */
#define FDCAN_TTIR_IWT            FDCAN_TTIR_IWT_Msk                           /*!<Initialization Watch Trigger              */
#define FDCAN_TTIR_WT_Pos         (16U)
#define FDCAN_TTIR_WT_Msk         (0x1U << FDCAN_TTIR_WT_Pos)                  /*!< 0x00010000 */
#define FDCAN_TTIR_WT             FDCAN_TTIR_WT_Msk                            /*!<Watch Trigger                             */
#define FDCAN_TTIR_AW_Pos         (17U)
#define FDCAN_TTIR_AW_Msk         (0x1U << FDCAN_TTIR_AW_Pos)                  /*!< 0x00020000 */
#define FDCAN_TTIR_AW             FDCAN_TTIR_AW_Msk                            /*!<Application Watchdog                      */
#define FDCAN_TTIR_CER_Pos        (18U)
#define FDCAN_TTIR_CER_Msk        (0x1U << FDCAN_TTIR_CER_Pos)                 /*!< 0x00040000 */
#define FDCAN_TTIR_CER            FDCAN_TTIR_CER_Msk                           /*!<Configuration Error                       */

/*****************  Bit definition for FDCAN_TTIE register  ********************/
#define FDCAN_TTIE_SBCE_Pos       (0U)
#define FDCAN_TTIE_SBCE_Msk       (0x1U << FDCAN_TTIE_SBCE_Pos)                /*!< 0x00000001 */
#define FDCAN_TTIE_SBCE           FDCAN_TTIE_SBCE_Msk                          /*!<Start of Basic Cycle Interrupt Enable             */
#define FDCAN_TTIE_SMCE_Pos       (1U)
#define FDCAN_TTIE_SMCE_Msk       (0x1U << FDCAN_TTIE_SMCE_Pos)                /*!< 0x00000002 */
#define FDCAN_TTIE_SMCE           FDCAN_TTIE_SMCE_Msk                          /*!<Start of Matrix Cycle Interrupt Enable            */
#define FDCAN_TTIE_CSME_Pos       (2U)
#define FDCAN_TTIE_CSME_Msk       (0x1U << FDCAN_TTIE_CSME_Pos)                /*!< 0x00000004 */
#define FDCAN_TTIE_CSME           FDCAN_TTIE_CSME_Msk                          /*!<Change of Synchronization Mode Interrupt Enable   */
#define FDCAN_TTIE_SOGE_Pos       (3U)
#define FDCAN_TTIE_SOGE_Msk       (0x1U << FDCAN_TTIE_SOGE_Pos)                /*!< 0x00000008 */
#define FDCAN_TTIE_SOGE           FDCAN_TTIE_SOGE_Msk                          /*!<Start of Gap Interrupt Enable                     */
#define FDCAN_TTIE_RTMIE_Pos      (4U)
#define FDCAN_TTIE_RTMIE_Msk      (0x1U << FDCAN_TTIE_RTMIE_Pos)               /*!< 0x00000010 */
#define FDCAN_TTIE_RTMIE          FDCAN_TTIE_RTMIE_Msk                         /*!<Register Time Mark Interrupt Interrupt Enable     */
#define FDCAN_TTIE_TTMIE_Pos      (5U)
#define FDCAN_TTIE_TTMIE_Msk      (0x1U << FDCAN_TTIE_TTMIE_Pos)               /*!< 0x00000020 */
#define FDCAN_TTIE_TTMIE          FDCAN_TTIE_TTMIE_Msk                         /*!<Trigger Time Mark Event Internal Interrupt Enable */
#define FDCAN_TTIE_SWEE_Pos       (6U)
#define FDCAN_TTIE_SWEE_Msk       (0x1U << FDCAN_TTIE_SWEE_Pos)                /*!< 0x00000040 */
#define FDCAN_TTIE_SWEE           FDCAN_TTIE_SWEE_Msk                          /*!<Stop Watch Event Interrupt Enable                 */
#define FDCAN_TTIE_GTWE_Pos       (7U)
#define FDCAN_TTIE_GTWE_Msk       (0x1U << FDCAN_TTIE_GTWE_Pos)                /*!< 0x00000080 */
#define FDCAN_TTIE_GTWE           FDCAN_TTIE_GTWE_Msk                          /*!<Global Time Wrap Interrupt Enable                 */
#define FDCAN_TTIE_GTDE_Pos       (8U)
#define FDCAN_TTIE_GTDE_Msk       (0x1U << FDCAN_TTIE_GTDE_Pos)                /*!< 0x00000100 */
#define FDCAN_TTIE_GTDE           FDCAN_TTIE_GTDE_Msk                          /*!<Global Time Discontinuity Interrupt Enable        */
#define FDCAN_TTIE_GTEE_Pos       (9U)
#define FDCAN_TTIE_GTEE_Msk       (0x1U << FDCAN_TTIE_GTEE_Pos)                /*!< 0x00000200 */
#define FDCAN_TTIE_GTEE           FDCAN_TTIE_GTEE_Msk                          /*!<Global Time Error Interrupt Enable                */
#define FDCAN_TTIE_TXUE_Pos       (10U)
#define FDCAN_TTIE_TXUE_Msk       (0x1U << FDCAN_TTIE_TXUE_Pos)                /*!< 0x00000400 */
#define FDCAN_TTIE_TXUE           FDCAN_TTIE_TXUE_Msk                          /*!<Tx Count Underflow Interrupt Enable               */
#define FDCAN_TTIE_TXOE_Pos       (11U)
#define FDCAN_TTIE_TXOE_Msk       (0x1U << FDCAN_TTIE_TXOE_Pos)                /*!< 0x00000800 */
#define FDCAN_TTIE_TXOE           FDCAN_TTIE_TXOE_Msk                          /*!<Tx Count Overflow Interrupt Enable                */
#define FDCAN_TTIE_SE1E_Pos       (12U)
#define FDCAN_TTIE_SE1E_Msk       (0x1U << FDCAN_TTIE_SE1E_Pos)                /*!< 0x00001000 */
#define FDCAN_TTIE_SE1E           FDCAN_TTIE_SE1E_Msk                          /*!<Scheduling Error 1 Interrupt Enable               */
#define FDCAN_TTIE_SE2E_Pos       (13U)
#define FDCAN_TTIE_SE2E_Msk       (0x1U << FDCAN_TTIE_SE2E_Pos)                /*!< 0x00002000 */
#define FDCAN_TTIE_SE2E           FDCAN_TTIE_SE2E_Msk                          /*!<Scheduling Error 2 Interrupt Enable               */
#define FDCAN_TTIE_ELCE_Pos       (14U)
#define FDCAN_TTIE_ELCE_Msk       (0x1U << FDCAN_TTIE_ELCE_Pos)                /*!< 0x00004000 */
#define FDCAN_TTIE_ELCE           FDCAN_TTIE_ELCE_Msk                          /*!<Error Level Changed Interrupt Enable              */
#define FDCAN_TTIE_IWTE_Pos       (15U)
#define FDCAN_TTIE_IWTE_Msk       (0x1U << FDCAN_TTIE_IWTE_Pos)                /*!< 0x00008000 */
#define FDCAN_TTIE_IWTE           FDCAN_TTIE_IWTE_Msk                          /*!<Initialization Watch Trigger Interrupt Enable     */
#define FDCAN_TTIE_WTE_Pos        (16U)
#define FDCAN_TTIE_WTE_Msk        (0x1U << FDCAN_TTIE_WTE_Pos)                 /*!< 0x00010000 */
#define FDCAN_TTIE_WTE            FDCAN_TTIE_WTE_Msk                           /*!<Watch Trigger Interrupt Enable                    */
#define FDCAN_TTIE_AWE_Pos        (17U)
#define FDCAN_TTIE_AWE_Msk        (0x1U << FDCAN_TTIE_AWE_Pos)                 /*!< 0x00020000 */
#define FDCAN_TTIE_AWE            FDCAN_TTIE_AWE_Msk                           /*!<Application Watchdog Interrupt Enable             */
#define FDCAN_TTIE_CERE_Pos       (18U)
#define FDCAN_TTIE_CERE_Msk       (0x1U << FDCAN_TTIE_CERE_Pos)                /*!< 0x00040000 */
#define FDCAN_TTIE_CERE           FDCAN_TTIE_CERE_Msk                          /*!<Configuration Error Interrupt Enable              */

/*****************  Bit definition for FDCAN_TTILS register  ********************/
#define FDCAN_TTILS_SBCS_Pos      (0U)
#define FDCAN_TTILS_SBCS_Msk      (0x1U << FDCAN_TTILS_SBCS_Pos)               /*!< 0x00000001 */
#define FDCAN_TTILS_SBCS          FDCAN_TTILS_SBCS_Msk                         /*!<Start of Basic Cycle Interrupt Line               */
#define FDCAN_TTILS_SMCS_Pos      (1U)
#define FDCAN_TTILS_SMCS_Msk      (0x1U << FDCAN_TTILS_SMCS_Pos)               /*!< 0x00000002 */
#define FDCAN_TTILS_SMCS          FDCAN_TTILS_SMCS_Msk                         /*!<Start of Matrix Cycle Interrupt Line              */
#define FDCAN_TTILS_CSMS_Pos      (2U)
#define FDCAN_TTILS_CSMS_Msk      (0x1U << FDCAN_TTILS_CSMS_Pos)               /*!< 0x00000004 */
#define FDCAN_TTILS_CSMS          FDCAN_TTILS_CSMS_Msk                         /*!<Change of Synchronization Mode Interrupt Line     */
#define FDCAN_TTILS_SOGS_Pos      (3U)
#define FDCAN_TTILS_SOGS_Msk      (0x1U << FDCAN_TTILS_SOGS_Pos)               /*!< 0x00000008 */
#define FDCAN_TTILS_SOGS          FDCAN_TTILS_SOGS_Msk                         /*!<Start of Gap Interrupt Line                       */
#define FDCAN_TTILS_RTMIS_Pos     (4U)
#define FDCAN_TTILS_RTMIS_Msk     (0x1U << FDCAN_TTILS_RTMIS_Pos)              /*!< 0x00000010 */
#define FDCAN_TTILS_RTMIS         FDCAN_TTILS_RTMIS_Msk                        /*!<Register Time Mark Interrupt Interrupt Line       */
#define FDCAN_TTILS_TTMIS_Pos     (5U)
#define FDCAN_TTILS_TTMIS_Msk     (0x1U << FDCAN_TTILS_TTMIS_Pos)              /*!< 0x00000020 */
#define FDCAN_TTILS_TTMIS         FDCAN_TTILS_TTMIS_Msk                        /*!<Trigger Time Mark Event Internal Interrupt Line   */
#define FDCAN_TTILS_SWES_Pos      (6U)
#define FDCAN_TTILS_SWES_Msk      (0x1U << FDCAN_TTILS_SWES_Pos)               /*!< 0x00000040 */
#define FDCAN_TTILS_SWES          FDCAN_TTILS_SWES_Msk                         /*!<Stop Watch Event Interrupt Line                   */
#define FDCAN_TTILS_GTWS_Pos      (7U)
#define FDCAN_TTILS_GTWS_Msk      (0x1U << FDCAN_TTILS_GTWS_Pos)               /*!< 0x00000080 */
#define FDCAN_TTILS_GTWS          FDCAN_TTILS_GTWS_Msk                         /*!<Global Time Wrap Interrupt Line                   */
#define FDCAN_TTILS_GTDS_Pos      (8U)
#define FDCAN_TTILS_GTDS_Msk      (0x1U << FDCAN_TTILS_GTDS_Pos)               /*!< 0x00000100 */
#define FDCAN_TTILS_GTDS          FDCAN_TTILS_GTDS_Msk                         /*!<Global Time Discontinuity Interrupt Line          */
#define FDCAN_TTILS_GTES_Pos      (9U)
#define FDCAN_TTILS_GTES_Msk      (0x1U << FDCAN_TTILS_GTES_Pos)               /*!< 0x00000200 */
#define FDCAN_TTILS_GTES          FDCAN_TTILS_GTES_Msk                         /*!<Global Time Error Interrupt Line                  */
#define FDCAN_TTILS_TXUS_Pos      (10U)
#define FDCAN_TTILS_TXUS_Msk      (0x1U << FDCAN_TTILS_TXUS_Pos)               /*!< 0x00000400 */
#define FDCAN_TTILS_TXUS          FDCAN_TTILS_TXUS_Msk                         /*!<Tx Count Underflow Interrupt Line                 */
#define FDCAN_TTILS_TXOS_Pos      (11U)
#define FDCAN_TTILS_TXOS_Msk      (0x1U << FDCAN_TTILS_TXOS_Pos)               /*!< 0x00000800 */
#define FDCAN_TTILS_TXOS          FDCAN_TTILS_TXOS_Msk                         /*!<Tx Count Overflow Interrupt Line                  */
#define FDCAN_TTILS_SE1S_Pos      (12U)
#define FDCAN_TTILS_SE1S_Msk      (0x1U << FDCAN_TTILS_SE1S_Pos)               /*!< 0x00001000 */
#define FDCAN_TTILS_SE1S          FDCAN_TTILS_SE1S_Msk                         /*!<Scheduling Error 1 Interrupt Line                 */
#define FDCAN_TTILS_SE2S_Pos      (13U)
#define FDCAN_TTILS_SE2S_Msk      (0x1U << FDCAN_TTILS_SE2S_Pos)               /*!< 0x00002000 */
#define FDCAN_TTILS_SE2S          FDCAN_TTILS_SE2S_Msk                         /*!<Scheduling Error 2 Interrupt Line                 */
#define FDCAN_TTILS_ELCS_Pos      (14U)
#define FDCAN_TTILS_ELCS_Msk      (0x1U << FDCAN_TTILS_ELCS_Pos)               /*!< 0x00004000 */
#define FDCAN_TTILS_ELCS          FDCAN_TTILS_ELCS_Msk                         /*!<Error Level Changed Interrupt Line                */
#define FDCAN_TTILS_IWTS_Pos      (15U)
#define FDCAN_TTILS_IWTS_Msk      (0x1U << FDCAN_TTILS_IWTS_Pos)               /*!< 0x00008000 */
#define FDCAN_TTILS_IWTS          FDCAN_TTILS_IWTS_Msk                         /*!<Initialization Watch Trigger Interrupt Line       */
#define FDCAN_TTILS_WTS_Pos       (16U)
#define FDCAN_TTILS_WTS_Msk       (0x1U << FDCAN_TTILS_WTS_Pos)                /*!< 0x00010000 */
#define FDCAN_TTILS_WTS           FDCAN_TTILS_WTS_Msk                          /*!<Watch Trigger Interrupt Line                      */
#define FDCAN_TTILS_AWS_Pos       (17U)
#define FDCAN_TTILS_AWS_Msk       (0x1U << FDCAN_TTILS_AWS_Pos)                /*!< 0x00020000 */
#define FDCAN_TTILS_AWS           FDCAN_TTILS_AWS_Msk                          /*!<Application Watchdog Interrupt Line               */
#define FDCAN_TTILS_CERS_Pos      (18U)
#define FDCAN_TTILS_CERS_Msk      (0x1U << FDCAN_TTILS_CERS_Pos)               /*!< 0x00040000 */
#define FDCAN_TTILS_CERS          FDCAN_TTILS_CERS_Msk                         /*!<Configuration Error Interrupt Line                */

/*****************  Bit definition for FDCAN_TTOST register  ********************/
#define FDCAN_TTOST_EL_Pos        (0U)
#define FDCAN_TTOST_EL_Msk        (0x3U << FDCAN_TTOST_EL_Pos)                 /*!< 0x00000003 */
#define FDCAN_TTOST_EL            FDCAN_TTOST_EL_Msk                           /*!<Error Level                              */
#define FDCAN_TTOST_MS_Pos        (2U)
#define FDCAN_TTOST_MS_Msk        (0x3U << FDCAN_TTOST_MS_Pos)                 /*!< 0x0000000C */
#define FDCAN_TTOST_MS            FDCAN_TTOST_MS_Msk                           /*!<Master State                             */
#define FDCAN_TTOST_SYS_Pos       (4U)
#define FDCAN_TTOST_SYS_Msk       (0x3U << FDCAN_TTOST_SYS_Pos)                /*!< 0x00000030 */
#define FDCAN_TTOST_SYS           FDCAN_TTOST_SYS_Msk                          /*!<Synchronization State                    */
#define FDCAN_TTOST_QGTP_Pos      (6U)
#define FDCAN_TTOST_QGTP_Msk      (0x1U << FDCAN_TTOST_QGTP_Pos)               /*!< 0x00000040 */
#define FDCAN_TTOST_QGTP          FDCAN_TTOST_QGTP_Msk                         /*!<Quality of Global Time Phase             */
#define FDCAN_TTOST_QCS_Pos       (7U)
#define FDCAN_TTOST_QCS_Msk       (0x1U << FDCAN_TTOST_QCS_Pos)                /*!< 0x00000080 */
#define FDCAN_TTOST_QCS           FDCAN_TTOST_QCS_Msk                          /*!<Quality of Clock Speed                   */
#define FDCAN_TTOST_RTO_Pos       (8U)
#define FDCAN_TTOST_RTO_Msk       (0xFFU << FDCAN_TTOST_RTO_Pos)               /*!< 0x0000FF00 */
#define FDCAN_TTOST_RTO           FDCAN_TTOST_RTO_Msk                          /*!<Reference Trigger Offset                 */
#define FDCAN_TTOST_WGTD_Pos      (22U)
#define FDCAN_TTOST_WGTD_Msk      (0x1U << FDCAN_TTOST_WGTD_Pos)               /*!< 0x00400000 */
#define FDCAN_TTOST_WGTD          FDCAN_TTOST_WGTD_Msk                         /*!<Wait for Global Time Discontinuity       */
#define FDCAN_TTOST_GFI_Pos       (23U)
#define FDCAN_TTOST_GFI_Msk       (0x1U << FDCAN_TTOST_GFI_Pos)                /*!< 0x00800000 */
#define FDCAN_TTOST_GFI           FDCAN_TTOST_GFI_Msk                          /*!<Gap Finished Indicator                   */
#define FDCAN_TTOST_TMP_Pos       (24U)
#define FDCAN_TTOST_TMP_Msk       (0x7U << FDCAN_TTOST_TMP_Pos)                /*!< 0x07000000 */
#define FDCAN_TTOST_TMP           FDCAN_TTOST_TMP_Msk                          /*!<Time Master Priority                     */
#define FDCAN_TTOST_GSI_Pos       (27U)
#define FDCAN_TTOST_GSI_Msk       (0x1U << FDCAN_TTOST_GSI_Pos)                /*!< 0x08000000 */
#define FDCAN_TTOST_GSI           FDCAN_TTOST_GSI_Msk                          /*!<Gap Started Indicator                    */
#define FDCAN_TTOST_WFE_Pos       (28U)
#define FDCAN_TTOST_WFE_Msk       (0x1U << FDCAN_TTOST_WFE_Pos)                /*!< 0x10000000 */
#define FDCAN_TTOST_WFE           FDCAN_TTOST_WFE_Msk                          /*!<Wait for Event                           */
#define FDCAN_TTOST_AWE_Pos       (29U)
#define FDCAN_TTOST_AWE_Msk       (0x1U << FDCAN_TTOST_AWE_Pos)                /*!< 0x20000000 */
#define FDCAN_TTOST_AWE           FDCAN_TTOST_AWE_Msk                          /*!<Application Watchdog Event               */
#define FDCAN_TTOST_WECS_Pos      (30U)
#define FDCAN_TTOST_WECS_Msk      (0x1U << FDCAN_TTOST_WECS_Pos)               /*!< 0x40000000 */
#define FDCAN_TTOST_WECS          FDCAN_TTOST_WECS_Msk                         /*!<Wait for External Clock Synchronization  */
#define FDCAN_TTOST_SPL_Pos       (31U)
#define FDCAN_TTOST_SPL_Msk       (0x1U << FDCAN_TTOST_SPL_Pos)                /*!< 0x80000000 */
#define FDCAN_TTOST_SPL           FDCAN_TTOST_SPL_Msk                          /*!<Schedule Phase Lock                      */

/*****************  Bit definition for FDCAN_TURNA register  ********************/
#define FDCAN_TURNA_NAV_Pos       (0U)
#define FDCAN_TURNA_NAV_Msk       (0x3FFFFU << FDCAN_TURNA_NAV_Pos)            /*!< 0x0003FFFF */
#define FDCAN_TURNA_NAV           FDCAN_TURNA_NAV_Msk                          /*!<Numerator Actual Value                   */

/*****************  Bit definition for FDCAN_TTLGT register  ********************/
#define FDCAN_TTLGT_LT_Pos        (0U)
#define FDCAN_TTLGT_LT_Msk        (0xFFFFU << FDCAN_TTLGT_LT_Pos)              /*!< 0x0000FFFF */
#define FDCAN_TTLGT_LT            FDCAN_TTLGT_LT_Msk                           /*!<Local Time                               */
#define FDCAN_TTLGT_GT_Pos        (16U)
#define FDCAN_TTLGT_GT_Msk        (0xFFFFU << FDCAN_TTLGT_GT_Pos)              /*!< 0xFFFF0000 */
#define FDCAN_TTLGT_GT            FDCAN_TTLGT_GT_Msk                           /*!<Global Time                              */

/*****************  Bit definition for FDCAN_TTCTC register  ********************/
#define FDCAN_TTCTC_CT_Pos        (0U)
#define FDCAN_TTCTC_CT_Msk        (0xFFFFU << FDCAN_TTCTC_CT_Pos)              /*!< 0x0000FFFF */
#define FDCAN_TTCTC_CT            FDCAN_TTCTC_CT_Msk                           /*!<Cycle Time                               */
#define FDCAN_TTCTC_CC_Pos        (16U)
#define FDCAN_TTCTC_CC_Msk        (0x3FU << FDCAN_TTCTC_CC_Pos)                /*!< 0x003F0000 */
#define FDCAN_TTCTC_CC            FDCAN_TTCTC_CC_Msk                           /*!<Cycle Count                              */

/*****************  Bit definition for FDCAN_TTCPT register  ********************/
#define FDCAN_TTCPT_CCV_Pos       (0U)
#define FDCAN_TTCPT_CCV_Msk       (0x3FU << FDCAN_TTCPT_CCV_Pos)               /*!< 0x0000003F */
#define FDCAN_TTCPT_CCV           FDCAN_TTCPT_CCV_Msk                          /*!<Cycle Count Value                        */
#define FDCAN_TTCPT_SWV_Pos       (16U)
#define FDCAN_TTCPT_SWV_Msk       (0xFFFFU << FDCAN_TTCPT_SWV_Pos)             /*!< 0xFFFF0000 */
#define FDCAN_TTCPT_SWV           FDCAN_TTCPT_SWV_Msk                          /*!<Stop Watch Value                         */

/*****************  Bit definition for FDCAN_TTCSM register  ********************/
#define FDCAN_TTCSM_CSM_Pos       (0U)
#define FDCAN_TTCSM_CSM_Msk       (0xFFFFU << FDCAN_TTCSM_CSM_Pos)             /*!< 0x0000FFFF */
#define FDCAN_TTCSM_CSM           FDCAN_TTCSM_CSM_Msk                          /*!<Cycle Sync Mark                          */

/*****************  Bit definition for FDCAN_TTTS register  *********************/
#define FDCAN_TTTS_SWTSEL_Pos     (0U)
#define FDCAN_TTTS_SWTSEL_Msk     (0x3U << FDCAN_TTTS_SWTSEL_Pos)              /*!< 0x00000003 */
#define FDCAN_TTTS_SWTSEL         FDCAN_TTTS_SWTSEL_Msk                        /*!<Stop watch trigger input selection       */
#define FDCAN_TTTS_EVTSEL_Pos     (4U)
#define FDCAN_TTTS_EVTSEL_Msk     (0x3U << FDCAN_TTTS_EVTSEL_Pos)              /*!< 0x00000030 */
#define FDCAN_TTTS_EVTSEL         FDCAN_TTTS_EVTSEL_Msk                        /*!<Event trigger input selection            */

/********************************************************************************/
/*                                                                              */
/*                      FDCANCCU (Clock Calibration unit)                       */
/*                                                                              */
/********************************************************************************/

/*****************  Bit definition for FDCANCCU_CREL register  ******************/
#define FDCANCCU_CREL_DAY_Pos        (0U)
#define FDCANCCU_CREL_DAY_Msk        (0xFFU << FDCANCCU_CREL_DAY_Pos)          /*!< 0x000000FF */
#define FDCANCCU_CREL_DAY            FDCANCCU_CREL_DAY_Msk                     /*!<Timestamp Day                           */
#define FDCANCCU_CREL_MON_Pos        (8U)
#define FDCANCCU_CREL_MON_Msk        (0xFFU << FDCANCCU_CREL_MON_Pos)          /*!< 0x0000FF00 */
#define FDCANCCU_CREL_MON            FDCANCCU_CREL_MON_Msk                     /*!<Timestamp Month                         */
#define FDCANCCU_CREL_YEAR_Pos       (16U)
#define FDCANCCU_CREL_YEAR_Msk       (0xFU << FDCANCCU_CREL_YEAR_Pos)          /*!< 0x000F0000 */
#define FDCANCCU_CREL_YEAR           FDCANCCU_CREL_YEAR_Msk                    /*!<Timestamp Year                          */
#define FDCANCCU_CREL_SUBSTEP_Pos    (20U)
#define FDCANCCU_CREL_SUBSTEP_Msk    (0xFU << FDCANCCU_CREL_SUBSTEP_Pos)       /*!< 0x00F00000 */
#define FDCANCCU_CREL_SUBSTEP        FDCANCCU_CREL_SUBSTEP_Msk                 /*!<Sub-step of Core release                */
#define FDCANCCU_CREL_STEP_Pos       (24U)
#define FDCANCCU_CREL_STEP_Msk       (0xFU << FDCANCCU_CREL_STEP_Pos)          /*!< 0x0F000000 */
#define FDCANCCU_CREL_STEP           FDCANCCU_CREL_STEP_Msk                    /*!<Step of Core release                    */
#define FDCANCCU_CREL_REL_Pos        (28U)
#define FDCANCCU_CREL_REL_Msk        (0xFU << FDCANCCU_CREL_REL_Pos)           /*!< 0xF0000000 */
#define FDCANCCU_CREL_REL            FDCANCCU_CREL_REL_Msk                     /*!<Core release                            */

/*****************  Bit definition for FDCANCCU_CCFG register  ******************/
#define FDCANCCU_CCFG_TQBT_Pos       (0U)
#define FDCANCCU_CCFG_TQBT_Msk       (0x1FU << FDCANCCU_CCFG_TQBT_Pos)         /*!< 0x0000001F */
#define FDCANCCU_CCFG_TQBT           FDCANCCU_CCFG_TQBT_Msk                    /*!<Time Quanta per Bit Time                */
#define FDCANCCU_CCFG_BCC_Pos        (6U)
#define FDCANCCU_CCFG_BCC_Msk        (0x1U << FDCANCCU_CCFG_BCC_Pos)           /*!< 0x00000040 */
#define FDCANCCU_CCFG_BCC            FDCANCCU_CCFG_BCC_Msk                     /*!<Bypass Clock Calibration                */
#define FDCANCCU_CCFG_CFL_Pos        (7U)
#define FDCANCCU_CCFG_CFL_Msk        (0x1U << FDCANCCU_CCFG_CFL_Pos)           /*!< 0x00000080 */
#define FDCANCCU_CCFG_CFL            FDCANCCU_CCFG_CFL_Msk                     /*!<Calibration Field Length                */
#define FDCANCCU_CCFG_OCPM_Pos       (8U)
#define FDCANCCU_CCFG_OCPM_Msk       (0xFFU << FDCANCCU_CCFG_OCPM_Pos)         /*!< 0x0000FF00 */
#define FDCANCCU_CCFG_OCPM           FDCANCCU_CCFG_OCPM_Msk                    /*!<Oscillator Clock Periods Minimum        */
#define FDCANCCU_CCFG_CDIV_Pos       (16U)
#define FDCANCCU_CCFG_CDIV_Msk       (0xFU << FDCANCCU_CCFG_CDIV_Pos)          /*!< 0x000F0000 */
#define FDCANCCU_CCFG_CDIV           FDCANCCU_CCFG_CDIV_Msk                    /*!<Clock Divider                           */
#define FDCANCCU_CCFG_SWR_Pos        (31U)
#define FDCANCCU_CCFG_SWR_Msk        (0x1U << FDCANCCU_CCFG_SWR_Pos)           /*!< 0x80000000 */
#define FDCANCCU_CCFG_SWR            FDCANCCU_CCFG_SWR_Msk                     /*!<Software Reset                          */

/*****************  Bit definition for FDCANCCU_CSTAT register  *****************/
#define FDCANCCU_CSTAT_OCPC_Pos      (0U)
#define FDCANCCU_CSTAT_OCPC_Msk      (0x3FFFFU << FDCANCCU_CSTAT_OCPC_Pos)     /*!< 0x0003FFFF */
#define FDCANCCU_CSTAT_OCPC          FDCANCCU_CSTAT_OCPC_Msk                   /*!<Oscillator Clock Period Counter        */
#define FDCANCCU_CSTAT_TQC_Pos       (18U)
#define FDCANCCU_CSTAT_TQC_Msk       (0x7FFU << FDCANCCU_CSTAT_TQC_Pos)        /*!< 0x1FFC0000 */
#define FDCANCCU_CSTAT_TQC           FDCANCCU_CSTAT_TQC_Msk                    /*!<Time Quanta Counter                    */
#define FDCANCCU_CSTAT_CALS_Pos      (30U)
#define FDCANCCU_CSTAT_CALS_Msk      (0x3U << FDCANCCU_CSTAT_CALS_Pos)         /*!< 0xC0000000 */
#define FDCANCCU_CSTAT_CALS          FDCANCCU_CSTAT_CALS_Msk                   /*!<Calibration State                      */

/******************  Bit definition for FDCANCCU_CWD register  ******************/
#define FDCANCCU_CWD_WDC_Pos         (0U)
#define FDCANCCU_CWD_WDC_Msk         (0xFFFFU << FDCANCCU_CWD_WDC_Pos)         /*!< 0x0000FFFF */
#define FDCANCCU_CWD_WDC             FDCANCCU_CWD_WDC_Msk                      /*!<Watchdog Configuration                 */
#define FDCANCCU_CWD_WDV_Pos         (16U)
#define FDCANCCU_CWD_WDV_Msk         (0xFFFFU << FDCANCCU_CWD_WDV_Pos)         /*!< 0xFFFF0000 */
#define FDCANCCU_CWD_WDV             FDCANCCU_CWD_WDV_Msk                      /*!<Watchdog Value                         */

/******************  Bit definition for FDCANCCU_IR register  *******************/
#define FDCANCCU_IR_CWE_Pos          (0U)
#define FDCANCCU_IR_CWE_Msk          (0x1U << FDCANCCU_IR_CWE_Pos)             /*!< 0x00000001 */
#define FDCANCCU_IR_CWE              FDCANCCU_IR_CWE_Msk                       /*!<Calibration Watchdog Event             */
#define FDCANCCU_IR_CSC_Pos          (1U)
#define FDCANCCU_IR_CSC_Msk          (0x1U << FDCANCCU_IR_CSC_Pos)             /*!< 0x00000002 */
#define FDCANCCU_IR_CSC              FDCANCCU_IR_CSC_Msk                       /*!<Calibration State Changed              */

/******************  Bit definition for FDCANCCU_IE register  *******************/
#define FDCANCCU_IE_CWEE_Pos         (0U)
#define FDCANCCU_IE_CWEE_Msk         (0x1U << FDCANCCU_IE_CWEE_Pos)            /*!< 0x00000001 */
#define FDCANCCU_IE_CWEE             FDCANCCU_IE_CWEE_Msk                      /*!<Calibration Watchdog Event Enable      */
#define FDCANCCU_IE_CSCE_Pos         (1U)
#define FDCANCCU_IE_CSCE_Msk         (0x1U << FDCANCCU_IE_CSCE_Pos)            /*!< 0x00000002 */
#define FDCANCCU_IE_CSCE             FDCANCCU_IE_CSCE_Msk                      /*!<Calibration State Changed Enable       */

/******************************************************************************/
/*                                                                            */
/*                          HDMI-CEC (CEC)                                    */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for CEC_CR register  *********************/
#define CEC_CR_CECEN_Pos         (0U)
#define CEC_CR_CECEN_Msk         (0x1U << CEC_CR_CECEN_Pos)                    /*!< 0x00000001 */
#define CEC_CR_CECEN             CEC_CR_CECEN_Msk                              /*!< CEC Enable                                */
#define CEC_CR_TXSOM_Pos         (1U)
#define CEC_CR_TXSOM_Msk         (0x1U << CEC_CR_TXSOM_Pos)                    /*!< 0x00000002 */
#define CEC_CR_TXSOM             CEC_CR_TXSOM_Msk                              /*!< CEC Tx Start Of Message                   */
#define CEC_CR_TXEOM_Pos         (2U)
#define CEC_CR_TXEOM_Msk         (0x1U << CEC_CR_TXEOM_Pos)                    /*!< 0x00000004 */
#define CEC_CR_TXEOM             CEC_CR_TXEOM_Msk                              /*!< CEC Tx End Of Message                     */

/*******************  Bit definition for CEC_CFGR register  *******************/
#define CEC_CFGR_SFT_Pos         (0U)
#define CEC_CFGR_SFT_Msk         (0x7U << CEC_CFGR_SFT_Pos)                    /*!< 0x00000007 */
#define CEC_CFGR_SFT             CEC_CFGR_SFT_Msk                              /*!< CEC Signal Free Time                      */
#define CEC_CFGR_RXTOL_Pos       (3U)
#define CEC_CFGR_RXTOL_Msk       (0x1U << CEC_CFGR_RXTOL_Pos)                  /*!< 0x00000008 */
#define CEC_CFGR_RXTOL           CEC_CFGR_RXTOL_Msk                            /*!< CEC Tolerance                             */
#define CEC_CFGR_BRESTP_Pos      (4U)
#define CEC_CFGR_BRESTP_Msk      (0x1U << CEC_CFGR_BRESTP_Pos)                 /*!< 0x00000010 */
#define CEC_CFGR_BRESTP          CEC_CFGR_BRESTP_Msk                           /*!< CEC Rx Stop                               */
#define CEC_CFGR_BREGEN_Pos      (5U)
#define CEC_CFGR_BREGEN_Msk      (0x1U << CEC_CFGR_BREGEN_Pos)                 /*!< 0x00000020 */
#define CEC_CFGR_BREGEN          CEC_CFGR_BREGEN_Msk                           /*!< CEC Bit Rising Error generation           */
#define CEC_CFGR_LBPEGEN_Pos     (6U)
#define CEC_CFGR_LBPEGEN_Msk     (0x1U << CEC_CFGR_LBPEGEN_Pos)                /*!< 0x00000040 */
#define CEC_CFGR_LBPEGEN         CEC_CFGR_LBPEGEN_Msk                          /*!< CEC Long Bit Period Error generation      */
#define CEC_CFGR_SFTOPT_Pos      (8U)
#define CEC_CFGR_SFTOPT_Msk      (0x1U << CEC_CFGR_SFTOPT_Pos)                 /*!< 0x00000100 */
#define CEC_CFGR_SFTOPT          CEC_CFGR_SFTOPT_Msk                           /*!< CEC Signal Free Time optional             */
#define CEC_CFGR_BRDNOGEN_Pos    (7U)
#define CEC_CFGR_BRDNOGEN_Msk    (0x1U << CEC_CFGR_BRDNOGEN_Pos)               /*!< 0x00000080 */
#define CEC_CFGR_BRDNOGEN        CEC_CFGR_BRDNOGEN_Msk                         /*!< CEC Broadcast No error generation         */
#define CEC_CFGR_OAR_Pos         (16U)
#define CEC_CFGR_OAR_Msk         (0x7FFFU << CEC_CFGR_OAR_Pos)                 /*!< 0x7FFF0000 */
#define CEC_CFGR_OAR             CEC_CFGR_OAR_Msk                              /*!< CEC Own Address                           */
#define CEC_CFGR_LSTN_Pos        (31U)
#define CEC_CFGR_LSTN_Msk        (0x1U << CEC_CFGR_LSTN_Pos)                   /*!< 0x80000000 */
#define CEC_CFGR_LSTN            CEC_CFGR_LSTN_Msk                             /*!< CEC Listen mode                           */

/*******************  Bit definition for CEC_TXDR register  *******************/
#define CEC_TXDR_TXD_Pos         (0U)
#define CEC_TXDR_TXD_Msk         (0xFFU << CEC_TXDR_TXD_Pos)                   /*!< 0x000000FF */
#define CEC_TXDR_TXD             CEC_TXDR_TXD_Msk                              /*!< CEC Tx Data                               */

/*******************  Bit definition for CEC_RXDR register  *******************/
#define CEC_TXDR_RXD_Pos         (0U)
#define CEC_TXDR_RXD_Msk         (0xFFU << CEC_TXDR_RXD_Pos)                   /*!< 0x000000FF */
#define CEC_TXDR_RXD             CEC_TXDR_RXD_Msk                              /*!< CEC Rx Data                               */

/*******************  Bit definition for CEC_ISR register  ********************/
#define CEC_ISR_RXBR_Pos         (0U)
#define CEC_ISR_RXBR_Msk         (0x1U << CEC_ISR_RXBR_Pos)                    /*!< 0x00000001 */
#define CEC_ISR_RXBR             CEC_ISR_RXBR_Msk                              /*!< CEC Rx-Byte Received                      */
#define CEC_ISR_RXEND_Pos        (1U)
#define CEC_ISR_RXEND_Msk        (0x1U << CEC_ISR_RXEND_Pos)                   /*!< 0x00000002 */
#define CEC_ISR_RXEND            CEC_ISR_RXEND_Msk                             /*!< CEC End Of Reception                      */
#define CEC_ISR_RXOVR_Pos        (2U)
#define CEC_ISR_RXOVR_Msk        (0x1U << CEC_ISR_RXOVR_Pos)                   /*!< 0x00000004 */
#define CEC_ISR_RXOVR            CEC_ISR_RXOVR_Msk                             /*!< CEC Rx-Overrun                            */
#define CEC_ISR_BRE_Pos          (3U)
#define CEC_ISR_BRE_Msk          (0x1U << CEC_ISR_BRE_Pos)                     /*!< 0x00000008 */
#define CEC_ISR_BRE              CEC_ISR_BRE_Msk                               /*!< CEC Rx Bit Rising Error                   */
#define CEC_ISR_SBPE_Pos         (4U)
#define CEC_ISR_SBPE_Msk         (0x1U << CEC_ISR_SBPE_Pos)                    /*!< 0x00000010 */
#define CEC_ISR_SBPE             CEC_ISR_SBPE_Msk                              /*!< CEC Rx Short Bit period Error             */
#define CEC_ISR_LBPE_Pos         (5U)
#define CEC_ISR_LBPE_Msk         (0x1U << CEC_ISR_LBPE_Pos)                    /*!< 0x00000020 */
#define CEC_ISR_LBPE             CEC_ISR_LBPE_Msk                              /*!< CEC Rx Long Bit period Error              */
#define CEC_ISR_RXACKE_Pos       (6U)
#define CEC_ISR_RXACKE_Msk       (0x1U << CEC_ISR_RXACKE_Pos)                  /*!< 0x00000040 */
#define CEC_ISR_RXACKE           CEC_ISR_RXACKE_Msk                            /*!< CEC Rx Missing Acknowledge                */
#define CEC_ISR_ARBLST_Pos       (7U)
#define CEC_ISR_ARBLST_Msk       (0x1U << CEC_ISR_ARBLST_Pos)                  /*!< 0x00000080 */
#define CEC_ISR_ARBLST           CEC_ISR_ARBLST_Msk                            /*!< CEC Arbitration Lost                      */
#define CEC_ISR_TXBR_Pos         (8U)
#define CEC_ISR_TXBR_Msk         (0x1U << CEC_ISR_TXBR_Pos)                    /*!< 0x00000100 */
#define CEC_ISR_TXBR             CEC_ISR_TXBR_Msk                              /*!< CEC Tx Byte Request                       */
#define CEC_ISR_TXEND_Pos        (9U)
#define CEC_ISR_TXEND_Msk        (0x1U << CEC_ISR_TXEND_Pos)                   /*!< 0x00000200 */
#define CEC_ISR_TXEND            CEC_ISR_TXEND_Msk                             /*!< CEC End of Transmission                   */
#define CEC_ISR_TXUDR_Pos        (10U)
#define CEC_ISR_TXUDR_Msk        (0x1U << CEC_ISR_TXUDR_Pos)                   /*!< 0x00000400 */
#define CEC_ISR_TXUDR            CEC_ISR_TXUDR_Msk                             /*!< CEC Tx-Buffer Underrun                    */
#define CEC_ISR_TXERR_Pos        (11U)
#define CEC_ISR_TXERR_Msk        (0x1U << CEC_ISR_TXERR_Pos)                   /*!< 0x00000800 */
#define CEC_ISR_TXERR            CEC_ISR_TXERR_Msk                             /*!< CEC Tx-Error                              */
#define CEC_ISR_TXACKE_Pos       (12U)
#define CEC_ISR_TXACKE_Msk       (0x1U << CEC_ISR_TXACKE_Pos)                  /*!< 0x00001000 */
#define CEC_ISR_TXACKE           CEC_ISR_TXACKE_Msk                            /*!< CEC Tx Missing Acknowledge                */

/*******************  Bit definition for CEC_IER register  ********************/
#define CEC_IER_RXBRIE_Pos       (0U)
#define CEC_IER_RXBRIE_Msk       (0x1U << CEC_IER_RXBRIE_Pos)                  /*!< 0x00000001 */
#define CEC_IER_RXBRIE           CEC_IER_RXBRIE_Msk                            /*!< CEC Rx-Byte Received IT Enable            */
#define CEC_IER_RXENDIE_Pos      (1U)
#define CEC_IER_RXENDIE_Msk      (0x1U << CEC_IER_RXENDIE_Pos)                 /*!< 0x00000002 */
#define CEC_IER_RXENDIE          CEC_IER_RXENDIE_Msk                           /*!< CEC End Of Reception IT Enable            */
#define CEC_IER_RXOVRIE_Pos      (2U)
#define CEC_IER_RXOVRIE_Msk      (0x1U << CEC_IER_RXOVRIE_Pos)                 /*!< 0x00000004 */
#define CEC_IER_RXOVRIE          CEC_IER_RXOVRIE_Msk                           /*!< CEC Rx-Overrun IT Enable                  */
#define CEC_IER_BREIE_Pos        (3U)
#define CEC_IER_BREIE_Msk        (0x1U << CEC_IER_BREIE_Pos)                   /*!< 0x00000008 */
#define CEC_IER_BREIE            CEC_IER_BREIE_Msk                             /*!< CEC Rx Bit Rising Error IT Enable         */
#define CEC_IER_SBPEIE_Pos       (4U)
#define CEC_IER_SBPEIE_Msk       (0x1U << CEC_IER_SBPEIE_Pos)                  /*!< 0x00000010 */
#define CEC_IER_SBPEIE           CEC_IER_SBPEIE_Msk                            /*!< CEC Rx Short Bit period Error IT Enable   */
#define CEC_IER_LBPEIE_Pos       (5U)
#define CEC_IER_LBPEIE_Msk       (0x1U << CEC_IER_LBPEIE_Pos)                  /*!< 0x00000020 */
#define CEC_IER_LBPEIE           CEC_IER_LBPEIE_Msk                            /*!< CEC Rx Long Bit period Error IT Enable    */
#define CEC_IER_RXACKEIE_Pos     (6U)
#define CEC_IER_RXACKEIE_Msk     (0x1U << CEC_IER_RXACKEIE_Pos)                /*!< 0x00000040 */
#define CEC_IER_RXACKEIE         CEC_IER_RXACKEIE_Msk                          /*!< CEC Rx Missing Acknowledge IT Enable      */
#define CEC_IER_ARBLSTIE_Pos     (7U)
#define CEC_IER_ARBLSTIE_Msk     (0x1U << CEC_IER_ARBLSTIE_Pos)                /*!< 0x00000080 */
#define CEC_IER_ARBLSTIE         CEC_IER_ARBLSTIE_Msk                          /*!< CEC Arbitration Lost IT Enable            */
#define CEC_IER_TXBRIE_Pos       (8U)
#define CEC_IER_TXBRIE_Msk       (0x1U << CEC_IER_TXBRIE_Pos)                  /*!< 0x00000100 */
#define CEC_IER_TXBRIE           CEC_IER_TXBRIE_Msk                            /*!< CEC Tx Byte Request  IT Enable            */
#define CEC_IER_TXENDIE_Pos      (9U)
#define CEC_IER_TXENDIE_Msk      (0x1U << CEC_IER_TXENDIE_Pos)                 /*!< 0x00000200 */
#define CEC_IER_TXENDIE          CEC_IER_TXENDIE_Msk                           /*!< CEC End of Transmission IT Enable         */
#define CEC_IER_TXUDRIE_Pos      (10U)
#define CEC_IER_TXUDRIE_Msk      (0x1U << CEC_IER_TXUDRIE_Pos)                 /*!< 0x00000400 */
#define CEC_IER_TXUDRIE          CEC_IER_TXUDRIE_Msk                           /*!< CEC Tx-Buffer Underrun IT Enable          */
#define CEC_IER_TXERRIE_Pos      (11U)
#define CEC_IER_TXERRIE_Msk      (0x1U << CEC_IER_TXERRIE_Pos)                 /*!< 0x00000800 */
#define CEC_IER_TXERRIE          CEC_IER_TXERRIE_Msk                           /*!< CEC Tx-Error IT Enable                    */
#define CEC_IER_TXACKEIE_Pos     (12U)
#define CEC_IER_TXACKEIE_Msk     (0x1U << CEC_IER_TXACKEIE_Pos)                /*!< 0x00001000 */
#define CEC_IER_TXACKEIE         CEC_IER_TXACKEIE_Msk                          /*!< CEC Tx Missing Acknowledge IT Enable      */

/******************************************************************************/
/*                                                                            */
/*                          CRC calculation unit                              */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for CRC_DR register  *********************/
#define CRC_DR_DR_Pos            (0U)
#define CRC_DR_DR_Msk            (0xFFFFFFFFU << CRC_DR_DR_Pos)                /*!< 0xFFFFFFFF */
#define CRC_DR_DR                CRC_DR_DR_Msk                                 /*!< Data register bits */

/*******************  Bit definition for CRC_IDR register  ********************/
#define CRC_IDR_IDR_Pos          (0U)
#define CRC_IDR_IDR_Msk          (0xFFFFFFFFU << CRC_IDR_IDR_Pos)              /*!< 0xFFFFFFFF */
#define CRC_IDR_IDR              CRC_IDR_IDR_Msk                               /*!< General-purpose 32-bit data register bits */

/********************  Bit definition for CRC_CR register  ********************/
#define CRC_CR_RESET_Pos         (0U)
#define CRC_CR_RESET_Msk         (0x1U << CRC_CR_RESET_Pos)                    /*!< 0x00000001 */
#define CRC_CR_RESET             CRC_CR_RESET_Msk                              /*!< RESET the CRC computation unit bit */
#define CRC_CR_POLYSIZE_Pos      (3U)
#define CRC_CR_POLYSIZE_Msk      (0x3U << CRC_CR_POLYSIZE_Pos)                 /*!< 0x00000018 */
#define CRC_CR_POLYSIZE          CRC_CR_POLYSIZE_Msk                           /*!< Polynomial size bits */
#define CRC_CR_POLYSIZE_0        (0x1U << CRC_CR_POLYSIZE_Pos)                 /*!< 0x00000008 */
#define CRC_CR_POLYSIZE_1        (0x2U << CRC_CR_POLYSIZE_Pos)                 /*!< 0x00000010 */
#define CRC_CR_REV_IN_Pos        (5U)
#define CRC_CR_REV_IN_Msk        (0x3U << CRC_CR_REV_IN_Pos)                   /*!< 0x00000060 */
#define CRC_CR_REV_IN            CRC_CR_REV_IN_Msk                             /*!< REV_IN Reverse Input Data bits */
#define CRC_CR_REV_IN_0          (0x1U << CRC_CR_REV_IN_Pos)                   /*!< 0x00000020 */
#define CRC_CR_REV_IN_1          (0x2U << CRC_CR_REV_IN_Pos)                   /*!< 0x00000040 */
#define CRC_CR_REV_OUT_Pos       (7U)
#define CRC_CR_REV_OUT_Msk       (0x1U << CRC_CR_REV_OUT_Pos)                  /*!< 0x00000080 */
#define CRC_CR_REV_OUT           CRC_CR_REV_OUT_Msk                            /*!< REV_OUT Reverse Output Data bits */

/*******************  Bit definition for CRC_INIT register  *******************/
#define CRC_INIT_INIT_Pos        (0U)
#define CRC_INIT_INIT_Msk        (0xFFFFFFFFU << CRC_INIT_INIT_Pos)            /*!< 0xFFFFFFFF */
#define CRC_INIT_INIT            CRC_INIT_INIT_Msk                             /*!< Initial CRC value bits */

/*******************  Bit definition for CRC_POL register  ********************/
#define CRC_POL_POL_Pos          (0U)
#define CRC_POL_POL_Msk          (0xFFFFFFFFU << CRC_POL_POL_Pos)              /*!< 0xFFFFFFFF */
#define CRC_POL_POL              CRC_POL_POL_Msk                               /*!< Coefficients of the polynomial */

/******************************************************************************/
/*                                                                            */
/*                          CRS Clock Recovery System                         */
/******************************************************************************/

/*******************  Bit definition for CRS_CR register  *********************/
#define CRS_CR_SYNCOKIE_Pos       (0U)
#define CRS_CR_SYNCOKIE_Msk       (0x1U << CRS_CR_SYNCOKIE_Pos)                /*!< 0x00000001 */
#define CRS_CR_SYNCOKIE           CRS_CR_SYNCOKIE_Msk                          /*!< SYNC event OK interrupt enable */
#define CRS_CR_SYNCWARNIE_Pos     (1U)
#define CRS_CR_SYNCWARNIE_Msk     (0x1U << CRS_CR_SYNCWARNIE_Pos)              /*!< 0x00000002 */
#define CRS_CR_SYNCWARNIE         CRS_CR_SYNCWARNIE_Msk                        /*!< SYNC warning interrupt enable */
#define CRS_CR_ERRIE_Pos          (2U)
#define CRS_CR_ERRIE_Msk          (0x1U << CRS_CR_ERRIE_Pos)                   /*!< 0x00000004 */
#define CRS_CR_ERRIE              CRS_CR_ERRIE_Msk                             /*!< SYNC error or trimming error interrupt enable */
#define CRS_CR_ESYNCIE_Pos        (3U)
#define CRS_CR_ESYNCIE_Msk        (0x1U << CRS_CR_ESYNCIE_Pos)                 /*!< 0x00000008 */
#define CRS_CR_ESYNCIE            CRS_CR_ESYNCIE_Msk                           /*!< Expected SYNC interrupt enable */
#define CRS_CR_CEN_Pos            (5U)
#define CRS_CR_CEN_Msk            (0x1U << CRS_CR_CEN_Pos)                     /*!< 0x00000020 */
#define CRS_CR_CEN                CRS_CR_CEN_Msk                               /*!< Frequency error counter enable */
#define CRS_CR_AUTOTRIMEN_Pos     (6U)
#define CRS_CR_AUTOTRIMEN_Msk     (0x1U << CRS_CR_AUTOTRIMEN_Pos)              /*!< 0x00000040 */
#define CRS_CR_AUTOTRIMEN         CRS_CR_AUTOTRIMEN_Msk                        /*!< Automatic trimming enable */
#define CRS_CR_SWSYNC_Pos         (7U)
#define CRS_CR_SWSYNC_Msk         (0x1U << CRS_CR_SWSYNC_Pos)                  /*!< 0x00000080 */
#define CRS_CR_SWSYNC             CRS_CR_SWSYNC_Msk                            /*!< Generate software SYNC event */
#define CRS_CR_TRIM_Pos           (8U)
#define CRS_CR_TRIM_Msk           (0x3FU << CRS_CR_TRIM_Pos)                   /*!< 0x00003F00 */
#define CRS_CR_TRIM               CRS_CR_TRIM_Msk                              /*!< HSI48 oscillator smooth trimming */

/*******************  Bit definition for CRS_CFGR register  *********************/
#define CRS_CFGR_RELOAD_Pos       (0U)
#define CRS_CFGR_RELOAD_Msk       (0xFFFFU << CRS_CFGR_RELOAD_Pos)             /*!< 0x0000FFFF */
#define CRS_CFGR_RELOAD           CRS_CFGR_RELOAD_Msk                          /*!< Counter reload value */
#define CRS_CFGR_FELIM_Pos        (16U)
#define CRS_CFGR_FELIM_Msk        (0xFFU << CRS_CFGR_FELIM_Pos)                /*!< 0x00FF0000 */
#define CRS_CFGR_FELIM            CRS_CFGR_FELIM_Msk                           /*!< Frequency error limit */

#define CRS_CFGR_SYNCDIV_Pos      (24U)
#define CRS_CFGR_SYNCDIV_Msk      (0x7U << CRS_CFGR_SYNCDIV_Pos)               /*!< 0x07000000 */
#define CRS_CFGR_SYNCDIV          CRS_CFGR_SYNCDIV_Msk                         /*!< SYNC divider */
#define CRS_CFGR_SYNCDIV_0        (0x1U << CRS_CFGR_SYNCDIV_Pos)               /*!< 0x01000000 */
#define CRS_CFGR_SYNCDIV_1        (0x2U << CRS_CFGR_SYNCDIV_Pos)               /*!< 0x02000000 */
#define CRS_CFGR_SYNCDIV_2        (0x4U << CRS_CFGR_SYNCDIV_Pos)               /*!< 0x04000000 */

#define CRS_CFGR_SYNCSRC_Pos      (28U)
#define CRS_CFGR_SYNCSRC_Msk      (0x3U << CRS_CFGR_SYNCSRC_Pos)               /*!< 0x30000000 */
#define CRS_CFGR_SYNCSRC          CRS_CFGR_SYNCSRC_Msk                         /*!< SYNC signal source selection */
#define CRS_CFGR_SYNCSRC_0        (0x1U << CRS_CFGR_SYNCSRC_Pos)               /*!< 0x10000000 */
#define CRS_CFGR_SYNCSRC_1        (0x2U << CRS_CFGR_SYNCSRC_Pos)               /*!< 0x20000000 */

#define CRS_CFGR_SYNCPOL_Pos      (31U)
#define CRS_CFGR_SYNCPOL_Msk      (0x1U << CRS_CFGR_SYNCPOL_Pos)               /*!< 0x80000000 */
#define CRS_CFGR_SYNCPOL          CRS_CFGR_SYNCPOL_Msk                         /*!< SYNC polarity selection */

/*******************  Bit definition for CRS_ISR register  *********************/
#define CRS_ISR_SYNCOKF_Pos       (0U)
#define CRS_ISR_SYNCOKF_Msk       (0x1U << CRS_ISR_SYNCOKF_Pos)                /*!< 0x00000001 */
#define CRS_ISR_SYNCOKF           CRS_ISR_SYNCOKF_Msk                          /*!< SYNC event OK flag */
#define CRS_ISR_SYNCWARNF_Pos     (1U)
#define CRS_ISR_SYNCWARNF_Msk     (0x1U << CRS_ISR_SYNCWARNF_Pos)              /*!< 0x00000002 */
#define CRS_ISR_SYNCWARNF         CRS_ISR_SYNCWARNF_Msk                        /*!< SYNC warning flag */
#define CRS_ISR_ERRF_Pos          (2U)
#define CRS_ISR_ERRF_Msk          (0x1U << CRS_ISR_ERRF_Pos)                   /*!< 0x00000004 */
#define CRS_ISR_ERRF              CRS_ISR_ERRF_Msk                             /*!< Error flag */
#define CRS_ISR_ESYNCF_Pos        (3U)
#define CRS_ISR_ESYNCF_Msk        (0x1U << CRS_ISR_ESYNCF_Pos)                 /*!< 0x00000008 */
#define CRS_ISR_ESYNCF            CRS_ISR_ESYNCF_Msk                           /*!< Expected SYNC flag */
#define CRS_ISR_SYNCERR_Pos       (8U)
#define CRS_ISR_SYNCERR_Msk       (0x1U << CRS_ISR_SYNCERR_Pos)                /*!< 0x00000100 */
#define CRS_ISR_SYNCERR           CRS_ISR_SYNCERR_Msk                          /*!< SYNC error */
#define CRS_ISR_SYNCMISS_Pos      (9U)
#define CRS_ISR_SYNCMISS_Msk      (0x1U << CRS_ISR_SYNCMISS_Pos)               /*!< 0x00000200 */
#define CRS_ISR_SYNCMISS          CRS_ISR_SYNCMISS_Msk                         /*!< SYNC missed */
#define CRS_ISR_TRIMOVF_Pos       (10U)
#define CRS_ISR_TRIMOVF_Msk       (0x1U << CRS_ISR_TRIMOVF_Pos)                /*!< 0x00000400 */
#define CRS_ISR_TRIMOVF           CRS_ISR_TRIMOVF_Msk                          /*!< Trimming overflow or underflow */
#define CRS_ISR_FEDIR_Pos         (15U)
#define CRS_ISR_FEDIR_Msk         (0x1U << CRS_ISR_FEDIR_Pos)                  /*!< 0x00008000 */
#define CRS_ISR_FEDIR             CRS_ISR_FEDIR_Msk                            /*!< Frequency error direction */
#define CRS_ISR_FECAP_Pos         (16U)
#define CRS_ISR_FECAP_Msk         (0xFFFFU << CRS_ISR_FECAP_Pos)               /*!< 0xFFFF0000 */
#define CRS_ISR_FECAP             CRS_ISR_FECAP_Msk                            /*!< Frequency error capture */

/*******************  Bit definition for CRS_ICR register  *********************/
#define CRS_ICR_SYNCOKC_Pos       (0U)
#define CRS_ICR_SYNCOKC_Msk       (0x1U << CRS_ICR_SYNCOKC_Pos)                /*!< 0x00000001 */
#define CRS_ICR_SYNCOKC           CRS_ICR_SYNCOKC_Msk                          /*!< SYNC event OK clear flag */
#define CRS_ICR_SYNCWARNC_Pos     (1U)
#define CRS_ICR_SYNCWARNC_Msk     (0x1U << CRS_ICR_SYNCWARNC_Pos)              /*!< 0x00000002 */
#define CRS_ICR_SYNCWARNC         CRS_ICR_SYNCWARNC_Msk                        /*!< SYNC warning clear flag */
#define CRS_ICR_ERRC_Pos          (2U)
#define CRS_ICR_ERRC_Msk          (0x1U << CRS_ICR_ERRC_Pos)                   /*!< 0x00000004 */
#define CRS_ICR_ERRC              CRS_ICR_ERRC_Msk                             /*!< Error clear flag */
#define CRS_ICR_ESYNCC_Pos        (3U)
#define CRS_ICR_ESYNCC_Msk        (0x1U << CRS_ICR_ESYNCC_Pos)                 /*!< 0x00000008 */
#define CRS_ICR_ESYNCC            CRS_ICR_ESYNCC_Msk                           /*!< Expected SYNC clear flag */

/******************************************************************************/
/*                                                                            */
/*                            Crypto Processor                                */
/*                                                                            */
/******************************************************************************/
/******************* Bits definition for CRYP_CR register  ********************/
#define CRYP_CR_ALGODIR_Pos              (2U)
#define CRYP_CR_ALGODIR_Msk              (0x1U << CRYP_CR_ALGODIR_Pos)         /*!< 0x00000004 */
#define CRYP_CR_ALGODIR                  CRYP_CR_ALGODIR_Msk

#define CRYP_CR_ALGOMODE_Pos             (3U)
#define CRYP_CR_ALGOMODE_Msk             (0x10007U << CRYP_CR_ALGOMODE_Pos)    /*!< 0x00080038 */
#define CRYP_CR_ALGOMODE                 CRYP_CR_ALGOMODE_Msk
#define CRYP_CR_ALGOMODE_0               (0x00001U << CRYP_CR_ALGOMODE_Pos)    /*!< 0x00000008 */
#define CRYP_CR_ALGOMODE_1               (0x00002U << CRYP_CR_ALGOMODE_Pos)    /*!< 0x00000010 */
#define CRYP_CR_ALGOMODE_2               (0x00004U << CRYP_CR_ALGOMODE_Pos)    /*!< 0x00000020 */
#define CRYP_CR_ALGOMODE_TDES_ECB        ((uint32_t)0x00000000)
#define CRYP_CR_ALGOMODE_TDES_CBC_Pos    (3U)
#define CRYP_CR_ALGOMODE_TDES_CBC_Msk    (0x1U << CRYP_CR_ALGOMODE_TDES_CBC_Pos) /*!< 0x00000008 */
#define CRYP_CR_ALGOMODE_TDES_CBC        CRYP_CR_ALGOMODE_TDES_CBC_Msk
#define CRYP_CR_ALGOMODE_DES_ECB_Pos     (4U)
#define CRYP_CR_ALGOMODE_DES_ECB_Msk     (0x1U << CRYP_CR_ALGOMODE_DES_ECB_Pos) /*!< 0x00000010 */
#define CRYP_CR_ALGOMODE_DES_ECB         CRYP_CR_ALGOMODE_DES_ECB_Msk
#define CRYP_CR_ALGOMODE_DES_CBC_Pos     (3U)
#define CRYP_CR_ALGOMODE_DES_CBC_Msk     (0x3U << CRYP_CR_ALGOMODE_DES_CBC_Pos) /*!< 0x00000018 */
#define CRYP_CR_ALGOMODE_DES_CBC         CRYP_CR_ALGOMODE_DES_CBC_Msk
#define CRYP_CR_ALGOMODE_AES_ECB_Pos     (5U)
#define CRYP_CR_ALGOMODE_AES_ECB_Msk     (0x1U << CRYP_CR_ALGOMODE_AES_ECB_Pos) /*!< 0x00000020 */
#define CRYP_CR_ALGOMODE_AES_ECB         CRYP_CR_ALGOMODE_AES_ECB_Msk
#define CRYP_CR_ALGOMODE_AES_CBC_Pos     (3U)
#define CRYP_CR_ALGOMODE_AES_CBC_Msk     (0x5U << CRYP_CR_ALGOMODE_AES_CBC_Pos) /*!< 0x00000028 */
#define CRYP_CR_ALGOMODE_AES_CBC         CRYP_CR_ALGOMODE_AES_CBC_Msk
#define CRYP_CR_ALGOMODE_AES_CTR_Pos     (4U)
#define CRYP_CR_ALGOMODE_AES_CTR_Msk     (0x3U << CRYP_CR_ALGOMODE_AES_CTR_Pos) /*!< 0x00000030 */
#define CRYP_CR_ALGOMODE_AES_CTR         CRYP_CR_ALGOMODE_AES_CTR_Msk
#define CRYP_CR_ALGOMODE_AES_GCM_Pos     (19U)
#define CRYP_CR_ALGOMODE_AES_GCM_Msk     (0x1U << CRYP_CR_ALGOMODE_AES_GCM_Pos) /*!< 0x00080000 */
#define CRYP_CR_ALGOMODE_AES_GCM         CRYP_CR_ALGOMODE_AES_GCM_Msk
#define CRYP_CR_ALGOMODE_AES_CCM_Pos     (3U)
#define CRYP_CR_ALGOMODE_AES_CCM_Msk     (0x10001U << CRYP_CR_ALGOMODE_AES_CCM_Pos) /*!< 0x00080008 */
#define CRYP_CR_ALGOMODE_AES_CCM         CRYP_CR_ALGOMODE_AES_CCM_Msk
#define CRYP_CR_ALGOMODE_AES_KEY_Pos     (3U)
#define CRYP_CR_ALGOMODE_AES_KEY_Msk     (0x7U << CRYP_CR_ALGOMODE_AES_KEY_Pos) /*!< 0x00000038 */
#define CRYP_CR_ALGOMODE_AES_KEY         CRYP_CR_ALGOMODE_AES_KEY_Msk

#define CRYP_CR_DATATYPE_Pos             (6U)
#define CRYP_CR_DATATYPE_Msk             (0x3U << CRYP_CR_DATATYPE_Pos)        /*!< 0x000000C0 */
#define CRYP_CR_DATATYPE                 CRYP_CR_DATATYPE_Msk
#define CRYP_CR_DATATYPE_0               (0x1U << CRYP_CR_DATATYPE_Pos)        /*!< 0x00000040 */
#define CRYP_CR_DATATYPE_1               (0x2U << CRYP_CR_DATATYPE_Pos)        /*!< 0x00000080 */
#define CRYP_CR_KEYSIZE_Pos              (8U)
#define CRYP_CR_KEYSIZE_Msk              (0x3U << CRYP_CR_KEYSIZE_Pos)         /*!< 0x00000300 */
#define CRYP_CR_KEYSIZE                  CRYP_CR_KEYSIZE_Msk
#define CRYP_CR_KEYSIZE_0                (0x1U << CRYP_CR_KEYSIZE_Pos)         /*!< 0x00000100 */
#define CRYP_CR_KEYSIZE_1                (0x2U << CRYP_CR_KEYSIZE_Pos)         /*!< 0x00000200 */
#define CRYP_CR_FFLUSH_Pos               (14U)
#define CRYP_CR_FFLUSH_Msk               (0x1U << CRYP_CR_FFLUSH_Pos)          /*!< 0x00004000 */
#define CRYP_CR_FFLUSH                   CRYP_CR_FFLUSH_Msk
#define CRYP_CR_CRYPEN_Pos               (15U)
#define CRYP_CR_CRYPEN_Msk               (0x1U << CRYP_CR_CRYPEN_Pos)          /*!< 0x00008000 */
#define CRYP_CR_CRYPEN                   CRYP_CR_CRYPEN_Msk

#define CRYP_CR_GCM_CCMPH_Pos            (16U)
#define CRYP_CR_GCM_CCMPH_Msk            (0x3U << CRYP_CR_GCM_CCMPH_Pos)       /*!< 0x00030000 */
#define CRYP_CR_GCM_CCMPH                CRYP_CR_GCM_CCMPH_Msk
#define CRYP_CR_GCM_CCMPH_0              (0x1U << CRYP_CR_GCM_CCMPH_Pos)       /*!< 0x00010000 */
#define CRYP_CR_GCM_CCMPH_1              (0x2U << CRYP_CR_GCM_CCMPH_Pos)       /*!< 0x00020000 */
#define CRYP_CR_ALGOMODE_3               ((uint32_t)0x00080000)
#define CRYP_CR_NPBLB_Pos                (20U)
#define CRYP_CR_NPBLB_Msk                (0xFU << CRYP_CR_NPBLB_Pos)		   /*!< 0x00F00000 */
#define CRYP_CR_NPBLB                    CRYP_CR_NPBLB_Msk

/****************** Bits definition for CRYP_SR register  *********************/
#define CRYP_SR_IFEM_Pos                 (0U)
#define CRYP_SR_IFEM_Msk                 (0x1U << CRYP_SR_IFEM_Pos)            /*!< 0x00000001 */
#define CRYP_SR_IFEM                     CRYP_SR_IFEM_Msk
#define CRYP_SR_IFNF_Pos                 (1U)
#define CRYP_SR_IFNF_Msk                 (0x1U << CRYP_SR_IFNF_Pos)            /*!< 0x00000002 */
#define CRYP_SR_IFNF                     CRYP_SR_IFNF_Msk
#define CRYP_SR_OFNE_Pos                 (2U)
#define CRYP_SR_OFNE_Msk                 (0x1U << CRYP_SR_OFNE_Pos)            /*!< 0x00000004 */
#define CRYP_SR_OFNE                     CRYP_SR_OFNE_Msk
#define CRYP_SR_OFFU_Pos                 (3U)
#define CRYP_SR_OFFU_Msk                 (0x1U << CRYP_SR_OFFU_Pos)            /*!< 0x00000008 */
#define CRYP_SR_OFFU                     CRYP_SR_OFFU_Msk
#define CRYP_SR_BUSY_Pos                 (4U)
#define CRYP_SR_BUSY_Msk                 (0x1U << CRYP_SR_BUSY_Pos)            /*!< 0x00000010 */
#define CRYP_SR_BUSY                     CRYP_SR_BUSY_Msk
/****************** Bits definition for CRYP_DMACR register  ******************/
#define CRYP_DMACR_DIEN_Pos              (0U)
#define CRYP_DMACR_DIEN_Msk              (0x1U << CRYP_DMACR_DIEN_Pos)         /*!< 0x00000001 */
#define CRYP_DMACR_DIEN                  CRYP_DMACR_DIEN_Msk
#define CRYP_DMACR_DOEN_Pos              (1U)
#define CRYP_DMACR_DOEN_Msk              (0x1U << CRYP_DMACR_DOEN_Pos)         /*!< 0x00000002 */
#define CRYP_DMACR_DOEN                  CRYP_DMACR_DOEN_Msk
/*****************  Bits definition for CRYP_IMSCR register  ******************/
#define CRYP_IMSCR_INIM_Pos              (0U)
#define CRYP_IMSCR_INIM_Msk              (0x1U << CRYP_IMSCR_INIM_Pos)         /*!< 0x00000001 */
#define CRYP_IMSCR_INIM                  CRYP_IMSCR_INIM_Msk
#define CRYP_IMSCR_OUTIM_Pos             (1U)
#define CRYP_IMSCR_OUTIM_Msk             (0x1U << CRYP_IMSCR_OUTIM_Pos)        /*!< 0x00000002 */
#define CRYP_IMSCR_OUTIM                 CRYP_IMSCR_OUTIM_Msk
/****************** Bits definition for CRYP_RISR register  *******************/
#define CRYP_RISR_OUTRIS_Pos             (0U)
#define CRYP_RISR_OUTRIS_Msk             (0x1U << CRYP_RISR_OUTRIS_Pos)        /*!< 0x00000001 */
#define CRYP_RISR_OUTRIS                 CRYP_RISR_OUTRIS_Msk
#define CRYP_RISR_INRIS_Pos              (1U)
#define CRYP_RISR_INRIS_Msk              (0x1U << CRYP_RISR_INRIS_Pos)         /*!< 0x00000002 */
#define CRYP_RISR_INRIS                  CRYP_RISR_INRIS_Msk
/****************** Bits definition for CRYP_MISR register  *******************/
#define CRYP_MISR_INMIS_Pos              (0U)
#define CRYP_MISR_INMIS_Msk              (0x1U << CRYP_MISR_INMIS_Pos)         /*!< 0x00000001 */
#define CRYP_MISR_INMIS                  CRYP_MISR_INMIS_Msk
#define CRYP_MISR_OUTMIS_Pos             (1U)
#define CRYP_MISR_OUTMIS_Msk             (0x1U << CRYP_MISR_OUTMIS_Pos)        /*!< 0x00000002 */
#define CRYP_MISR_OUTMIS                 CRYP_MISR_OUTMIS_Msk

/**********************  Bit definition for CRYP_HWCFGR register  ***************/
#define CRYP_HWCFGR_CFG1_Pos  (0U)
#define CRYP_HWCFGR_CFG1_Msk  (0xFU << CRYP_HWCFGR_CFG1_Pos)          /*!< 0x0000000F */
#define CRYP_HWCFGR_CFG1      CRYP_HWCFGR_CFG1_Msk                    /*!< HW Generic 1 */
#define CRYP_HWCFGR_CFG2_Pos  (4U)
#define CRYP_HWCFGR_CFG2_Msk  (0xFU << CRYP_HWCFGR_CFG2_Pos)          /*!< 0x000000F0 */
#define CRYP_HWCFGR_CFG2      CRYP_HWCFGR_CFG2_Msk                    /*!< HW Generic 2 */
#define CRYP_HWCFGR_CFG3_Pos  (8U)
#define CRYP_HWCFGR_CFG3_Msk  (0xFU << CRYP_HWCFGR_CFG3_Pos)          /*!< 0x00000F00 */
#define CRYP_HWCFGR_CFG3      CRYP_HWCFGR_CFG3_Msk                    /*!< HW Generic 3 */
#define CRYP_HWCFGR_CFG4_Pos  (12U)
#define CRYP_HWCFGR_CFG4_Msk  (0xFU << CRYP_HWCFGR_CFG4_Pos)          /*!< 0x0000F000 */
#define CRYP_HWCFGR_CFG4      CRYP_HWCFGR_CFG4_Msk                    /*!< HW Generic 4 */

/**********************  Bit definition for CRYP_VERR register  *****************/
#define CRYP_VERR_VER_Pos      (0U)
#define CRYP_VERR_VER_Msk      (0xFFU << CRYP_VERR_VER_Pos)               /*!< 0x000000FF */
#define CRYP_VERR_VER          CRYP_VERR_VER_Msk                         /*!< Revision number */

/**********************  Bit definition for CRYP_IPIDR register  ****************/
#define CRYP_IPIDR_IPID_Pos       (0U)
#define CRYP_IPIDR_IPID_Msk       (0xFFFFFFFFU << CRYP_IPIDR_IPID_Pos)         /*!< 0xFFFFFFFF */
#define CRYP_IPIDR_IPID           CRYP_IPIDR_IPID_Msk                          /*!< IP Identification */

/**********************  Bit definition for CRYP_SIDR register  *****************/
#define CRYP_MID_MID_Pos         (0U)
#define CRYP_MID_MID_Msk         (0xFFFFFFFFU << CRYP_MID_MID_Pos)           /*!< 0xFFFFFFFF */
#define CRYP_MID_MID             CRYP_MID_MID_Msk                            /*!< IP size identification */

/******************************************************************************/
/*                                                                            */
/*                      Digital to Analog Converter                           */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for DAC_CR register  ********************/
#define DAC_CR_EN1_Pos              (0U)
#define DAC_CR_EN1_Msk              (0x1U << DAC_CR_EN1_Pos)                   /*!< 0x00000001 */
#define DAC_CR_EN1                  DAC_CR_EN1_Msk                             /*!<DAC channel1 enable */
#define DAC_CR_TEN1_Pos             (1U)
#define DAC_CR_TEN1_Msk             (0x1U << DAC_CR_TEN1_Pos)                  /*!< 0x00000002 */
#define DAC_CR_TEN1                 DAC_CR_TEN1_Msk                            /*!<DAC channel1 Trigger enable */

#define DAC_CR_TSEL1_Pos            (2U)
#define DAC_CR_TSEL1_Msk            (0xFU << DAC_CR_TSEL1_Pos)                 /*!< 0x0000003C */
#define DAC_CR_TSEL1                DAC_CR_TSEL1_Msk                           /*!<TSEL1[2:0] (DAC channel1 Trigger selection) */
#define DAC_CR_TSEL1_0              (0x1U << DAC_CR_TSEL1_Pos)                 /*!< 0x00000004 */
#define DAC_CR_TSEL1_1              (0x2U << DAC_CR_TSEL1_Pos)                 /*!< 0x00000008 */
#define DAC_CR_TSEL1_2              (0x4U << DAC_CR_TSEL1_Pos)                 /*!< 0x00000010 */
#define DAC_CR_TSEL1_3              (0x8U << DAC_CR_TSEL1_Pos)                 /*!< 0x00000020 */


#define DAC_CR_WAVE1_Pos            (6U)
#define DAC_CR_WAVE1_Msk            (0x3U << DAC_CR_WAVE1_Pos)                 /*!< 0x000000C0 */
#define DAC_CR_WAVE1                DAC_CR_WAVE1_Msk                           /*!<WAVE1[1:0] (DAC channel1 noise/triangle wave generation enable) */
#define DAC_CR_WAVE1_0              (0x1U << DAC_CR_WAVE1_Pos)                 /*!< 0x00000040 */
#define DAC_CR_WAVE1_1              (0x2U << DAC_CR_WAVE1_Pos)                 /*!< 0x00000080 */

#define DAC_CR_MAMP1_Pos            (8U)
#define DAC_CR_MAMP1_Msk            (0xFU << DAC_CR_MAMP1_Pos)                 /*!< 0x00000F00 */
#define DAC_CR_MAMP1                DAC_CR_MAMP1_Msk                           /*!<MAMP1[3:0] (DAC channel1 Mask/Amplitude selector) */
#define DAC_CR_MAMP1_0              (0x1U << DAC_CR_MAMP1_Pos)                 /*!< 0x00000100 */
#define DAC_CR_MAMP1_1              (0x2U << DAC_CR_MAMP1_Pos)                 /*!< 0x00000200 */
#define DAC_CR_MAMP1_2              (0x4U << DAC_CR_MAMP1_Pos)                 /*!< 0x00000400 */
#define DAC_CR_MAMP1_3              (0x8U << DAC_CR_MAMP1_Pos)                 /*!< 0x00000800 */

#define DAC_CR_DMAEN1_Pos           (12U)
#define DAC_CR_DMAEN1_Msk           (0x1U << DAC_CR_DMAEN1_Pos)                /*!< 0x00001000 */
#define DAC_CR_DMAEN1               DAC_CR_DMAEN1_Msk                          /*!<DAC channel1 DMA enable */
#define DAC_CR_DMAUDRIE1_Pos        (13U)
#define DAC_CR_DMAUDRIE1_Msk        (0x1U << DAC_CR_DMAUDRIE1_Pos)             /*!< 0x00002000 */
#define DAC_CR_DMAUDRIE1            DAC_CR_DMAUDRIE1_Msk                       /*!<DAC channel 1 DMA underrun interrupt enable  >*/
#define DAC_CR_CEN1_Pos             (14U)
#define DAC_CR_CEN1_Msk             (0x1U << DAC_CR_CEN1_Pos)                  /*!< 0x00004000 */
#define DAC_CR_CEN1                 DAC_CR_CEN1_Msk                            /*!<DAC channel 1 calibration enable >*/
#define DAC_CR_HFSEL_Pos            (15U)
#define DAC_CR_HFSEL_Msk            (0x1U << DAC_CR_HFSEL_Pos)                  /*!< 0x00008000 */
#define DAC_CR_HFSEL                DAC_CR_HFSEL_Msk                            /*!<High frequency interface mode enable >*/

#define DAC_CR_EN2_Pos              (16U)
#define DAC_CR_EN2_Msk              (0x1U << DAC_CR_EN2_Pos)                   /*!< 0x00010000 */
#define DAC_CR_EN2                  DAC_CR_EN2_Msk                             /*!<DAC channel2 enable */
#define DAC_CR_TEN2_Pos             (17U)
#define DAC_CR_TEN2_Msk             (0x1U << DAC_CR_TEN2_Pos)                  /*!< 0x00020000 */
#define DAC_CR_TEN2                 DAC_CR_TEN2_Msk                            /*!<DAC channel2 Trigger enable */

#define DAC_CR_TSEL2_Pos            (18U)
#define DAC_CR_TSEL2_Msk            (0xFU << DAC_CR_TSEL2_Pos)                 /*!< 0x003C0000 */
#define DAC_CR_TSEL2                DAC_CR_TSEL2_Msk                           /*!<TSEL2[2:0] (DAC channel2 Trigger selection) */
#define DAC_CR_TSEL2_0              (0x1U << DAC_CR_TSEL2_Pos)                 /*!< 0x00040000 */
#define DAC_CR_TSEL2_1              (0x2U << DAC_CR_TSEL2_Pos)                 /*!< 0x00080000 */
#define DAC_CR_TSEL2_2              (0x4U << DAC_CR_TSEL2_Pos)                 /*!< 0x00100000 */
#define DAC_CR_TSEL2_3              (0x8U << DAC_CR_TSEL2_Pos)                 /*!< 0x00200000 */


#define DAC_CR_WAVE2_Pos            (22U)
#define DAC_CR_WAVE2_Msk            (0x3U << DAC_CR_WAVE2_Pos)                 /*!< 0x00C00000 */
#define DAC_CR_WAVE2                DAC_CR_WAVE2_Msk                           /*!<WAVE2[1:0] (DAC channel2 noise/triangle wave generation enable) */
#define DAC_CR_WAVE2_0              (0x1U << DAC_CR_WAVE2_Pos)                 /*!< 0x00400000 */
#define DAC_CR_WAVE2_1              (0x2U << DAC_CR_WAVE2_Pos)                 /*!< 0x00800000 */

#define DAC_CR_MAMP2_Pos            (24U)
#define DAC_CR_MAMP2_Msk            (0xFU << DAC_CR_MAMP2_Pos)                 /*!< 0x0F000000 */
#define DAC_CR_MAMP2                DAC_CR_MAMP2_Msk                           /*!<MAMP2[3:0] (DAC channel2 Mask/Amplitude selector) */
#define DAC_CR_MAMP2_0              (0x1U << DAC_CR_MAMP2_Pos)                 /*!< 0x01000000 */
#define DAC_CR_MAMP2_1              (0x2U << DAC_CR_MAMP2_Pos)                 /*!< 0x02000000 */
#define DAC_CR_MAMP2_2              (0x4U << DAC_CR_MAMP2_Pos)                 /*!< 0x04000000 */
#define DAC_CR_MAMP2_3              (0x8U << DAC_CR_MAMP2_Pos)                 /*!< 0x08000000 */

#define DAC_CR_DMAEN2_Pos           (28U)
#define DAC_CR_DMAEN2_Msk           (0x1U << DAC_CR_DMAEN2_Pos)                /*!< 0x10000000 */
#define DAC_CR_DMAEN2               DAC_CR_DMAEN2_Msk                          /*!<DAC channel2 DMA enabled */
#define DAC_CR_DMAUDRIE2_Pos        (29U)
#define DAC_CR_DMAUDRIE2_Msk        (0x1U << DAC_CR_DMAUDRIE2_Pos)             /*!< 0x20000000 */
#define DAC_CR_DMAUDRIE2            DAC_CR_DMAUDRIE2_Msk                       /*!<DAC channel2 DMA underrun interrupt enable  >*/
#define DAC_CR_CEN2_Pos             (30U)
#define DAC_CR_CEN2_Msk             (0x1U << DAC_CR_CEN2_Pos)                  /*!< 0x40000000 */
#define DAC_CR_CEN2                 DAC_CR_CEN2_Msk                            /*!<DAC channel2 calibration enable >*/

/*****************  Bit definition for DAC_SWTRIGR register  ******************/
#define DAC_SWTRIGR_SWTRIG1         ((uint8_t)0x01)                            /*!<DAC channel1 software trigger */
#define DAC_SWTRIGR_SWTRIG2         ((uint8_t)0x02)                            /*!<DAC channel2 software trigger */

/*****************  Bit definition for DAC_DHR12R1 register  ******************/
#define DAC_DHR12R1_DACC1DHR        ((uint16_t)0x0FFF)                         /*!<DAC channel1 12-bit Right aligned data */

/*****************  Bit definition for DAC_DHR12L1 register  ******************/
#define DAC_DHR12L1_DACC1DHR        ((uint16_t)0xFFF0)                         /*!<DAC channel1 12-bit Left aligned data */

/******************  Bit definition for DAC_DHR8R1 register  ******************/
#define DAC_DHR8R1_DACC1DHR         ((uint8_t)0xFF)                            /*!<DAC channel1 8-bit Right aligned data */

/*****************  Bit definition for DAC_DHR12R2 register  ******************/
#define DAC_DHR12R2_DACC2DHR        ((uint16_t)0x0FFF)                         /*!<DAC channel2 12-bit Right aligned data */

/*****************  Bit definition for DAC_DHR12L2 register  ******************/
#define DAC_DHR12L2_DACC2DHR        ((uint16_t)0xFFF0)                         /*!<DAC channel2 12-bit Left aligned data */

/******************  Bit definition for DAC_DHR8R2 register  ******************/
#define DAC_DHR8R2_DACC2DHR         ((uint8_t)0xFF)                            /*!<DAC channel2 8-bit Right aligned data */

/*****************  Bit definition for DAC_DHR12RD register  ******************/
#define DAC_DHR12RD_DACC1DHR_Pos    (0U)
#define DAC_DHR12RD_DACC1DHR_Msk    (0xFFFU << DAC_DHR12RD_DACC1DHR_Pos)       /*!< 0x00000FFF */
#define DAC_DHR12RD_DACC1DHR        DAC_DHR12RD_DACC1DHR_Msk                   /*!<DAC channel1 12-bit Right aligned data */
#define DAC_DHR12RD_DACC2DHR_Pos    (16U)
#define DAC_DHR12RD_DACC2DHR_Msk    (0xFFFU << DAC_DHR12RD_DACC2DHR_Pos)       /*!< 0x0FFF0000 */
#define DAC_DHR12RD_DACC2DHR        DAC_DHR12RD_DACC2DHR_Msk                   /*!<DAC channel2 12-bit Right aligned data */

/*****************  Bit definition for DAC_DHR12LD register  ******************/
#define DAC_DHR12LD_DACC1DHR_Pos    (4U)
#define DAC_DHR12LD_DACC1DHR_Msk    (0xFFFU << DAC_DHR12LD_DACC1DHR_Pos)       /*!< 0x0000FFF0 */
#define DAC_DHR12LD_DACC1DHR        DAC_DHR12LD_DACC1DHR_Msk                   /*!<DAC channel1 12-bit Left aligned data */
#define DAC_DHR12LD_DACC2DHR_Pos    (20U)
#define DAC_DHR12LD_DACC2DHR_Msk    (0xFFFU << DAC_DHR12LD_DACC2DHR_Pos)       /*!< 0xFFF00000 */
#define DAC_DHR12LD_DACC2DHR        DAC_DHR12LD_DACC2DHR_Msk                   /*!<DAC channel2 12-bit Left aligned data */

/******************  Bit definition for DAC_DHR8RD register  ******************/
#define DAC_DHR8RD_DACC1DHR_Pos     (0U)
#define DAC_DHR8RD_DACC1DHR_Msk     (0xFFU << DAC_DHR8RD_DACC1DHR_Pos)         /*!< 0x000000FF */
#define DAC_DHR8RD_DACC1DHR         DAC_DHR8RD_DACC1DHR_Msk                    /*!<DAC channel1 8-bit Right aligned data */
#define DAC_DHR8RD_DACC2DHR_Pos     (0U)
#define DAC_DHR8RD_DACC2DHR_Msk     (0xFFU << DAC_DHR8RD_DACC2DHR_Pos)         /*!< 0x000000FF */
#define DAC_DHR8RD_DACC2DHR         DAC_DHR8RD_DACC2DHR_Msk                    /*!<DAC channel2 8-bit Right aligned data */

/*******************  Bit definition for DAC_DOR1 register  *******************/
#define DAC_DOR1_DACC1DOR           ((uint16_t)0x0FFF)                         /*!<DAC channel1 data output */

/*******************  Bit definition for DAC_DOR2 register  *******************/
#define DAC_DOR2_DACC2DOR           ((uint16_t)0x0FFF)                         /*!<DAC channel2 data output */

/********************  Bit definition for DAC_SR register  ********************/
#define DAC_SR_DMAUDR1_Pos          (13U)
#define DAC_SR_DMAUDR1_Msk          (0x1U << DAC_SR_DMAUDR1_Pos)               /*!< 0x00002000 */
#define DAC_SR_DMAUDR1              DAC_SR_DMAUDR1_Msk                         /*!<DAC channel1 DMA underrun flag */
#define DAC_SR_CAL_FLAG1_Pos        (14U)
#define DAC_SR_CAL_FLAG1_Msk        (0x1U << DAC_SR_CAL_FLAG1_Pos)             /*!< 0x00004000 */
#define DAC_SR_CAL_FLAG1            DAC_SR_CAL_FLAG1_Msk                       /*!<DAC channel1 calibration offset status */
#define DAC_SR_BWST1_Pos            (15U)
#define DAC_SR_BWST1_Msk            (0x4001U << DAC_SR_BWST1_Pos)              /*!< 0x20008000 */
#define DAC_SR_BWST1                DAC_SR_BWST1_Msk                           /*!<DAC channel1 busy writing sample time flag */

#define DAC_SR_DMAUDR2_Pos          (29U)
#define DAC_SR_DMAUDR2_Msk          (0x1U << DAC_SR_DMAUDR2_Pos)               /*!< 0x20000000 */
#define DAC_SR_DMAUDR2              DAC_SR_DMAUDR2_Msk                         /*!<DAC channel2 DMA underrun flag */
#define DAC_SR_CAL_FLAG2_Pos        (30U)
#define DAC_SR_CAL_FLAG2_Msk        (0x1U << DAC_SR_CAL_FLAG2_Pos)             /*!< 0x40000000 */
#define DAC_SR_CAL_FLAG2            DAC_SR_CAL_FLAG2_Msk                       /*!<DAC channel2 calibration offset status */
#define DAC_SR_BWST2_Pos            (31U)
#define DAC_SR_BWST2_Msk            (0x1U << DAC_SR_BWST2_Pos)                 /*!< 0x80000000 */
#define DAC_SR_BWST2                DAC_SR_BWST2_Msk                           /*!<DAC channel2 busy writing sample time flag */

/*******************  Bit definition for DAC_CCR register  ********************/
#define DAC_CCR_OTRIM1_Pos          (0U)
#define DAC_CCR_OTRIM1_Msk          (0x1FU << DAC_CCR_OTRIM1_Pos)              /*!< 0x0000001F */
#define DAC_CCR_OTRIM1              DAC_CCR_OTRIM1_Msk                         /*!<DAC channel1 offset trimming value */
#define DAC_CCR_OTRIM2_Pos          (16U)
#define DAC_CCR_OTRIM2_Msk          (0x1FU << DAC_CCR_OTRIM2_Pos)              /*!< 0x001F0000 */
#define DAC_CCR_OTRIM2              DAC_CCR_OTRIM2_Msk                         /*!<DAC channel2 offset trimming value */

/*******************  Bit definition for DAC_MCR register  *******************/
#define DAC_MCR_MODE1_Pos           (0U)
#define DAC_MCR_MODE1_Msk           (0x7U << DAC_MCR_MODE1_Pos)                /*!< 0x00000007 */
#define DAC_MCR_MODE1               DAC_MCR_MODE1_Msk                          /*!<MODE1[2:0] (DAC channel1 mode) */
#define DAC_MCR_MODE1_0             (0x1U << DAC_MCR_MODE1_Pos)                /*!< 0x00000001 */
#define DAC_MCR_MODE1_1             (0x2U << DAC_MCR_MODE1_Pos)                /*!< 0x00000002 */
#define DAC_MCR_MODE1_2             (0x4U << DAC_MCR_MODE1_Pos)                /*!< 0x00000004 */

#define DAC_MCR_MODE2_Pos           (16U)
#define DAC_MCR_MODE2_Msk           (0x7U << DAC_MCR_MODE2_Pos)                /*!< 0x00070000 */
#define DAC_MCR_MODE2               DAC_MCR_MODE2_Msk                          /*!<MODE2[2:0] (DAC channel2 mode) */
#define DAC_MCR_MODE2_0             (0x1U << DAC_MCR_MODE2_Pos)                /*!< 0x00010000 */
#define DAC_MCR_MODE2_1             (0x2U << DAC_MCR_MODE2_Pos)                /*!< 0x00020000 */
#define DAC_MCR_MODE2_2             (0x4U << DAC_MCR_MODE2_Pos)                /*!< 0x00040000 */

/******************  Bit definition for DAC_SHSR1 register  ******************/
#define DAC_SHSR1_TSAMPLE1_Pos      (0U)
#define DAC_SHSR1_TSAMPLE1_Msk      (0x3FFU << DAC_SHSR1_TSAMPLE1_Pos)         /*!< 0x000003FF */
#define DAC_SHSR1_TSAMPLE1          DAC_SHSR1_TSAMPLE1_Msk                     /*!<DAC channel1 sample time */

/******************  Bit definition for DAC_SHSR2 register  ******************/
#define DAC_SHSR1_TSAMPLE2_Pos      (0U)
#define DAC_SHSR1_TSAMPLE2_Msk      (0x3FFU << DAC_SHSR1_TSAMPLE2_Pos)         /*!< 0x000003FF */
#define DAC_SHSR1_TSAMPLE2          DAC_SHSR1_TSAMPLE2_Msk                     /*!<DAC channel2 sample time */

/******************  Bit definition for DAC_SHHR register  ******************/
#define DAC_SHHR_THOLD1_Pos         (0U)
#define DAC_SHHR_THOLD1_Msk         (0x3FFU << DAC_SHHR_THOLD1_Pos)            /*!< 0x000003FF */
#define DAC_SHHR_THOLD1             DAC_SHHR_THOLD1_Msk                        /*!<DAC channel1 hold time */
#define DAC_SHHR_THOLD2_Pos         (16U)
#define DAC_SHHR_THOLD2_Msk         (0x3FFU << DAC_SHHR_THOLD2_Pos)            /*!< 0x03FF0000 */
#define DAC_SHHR_THOLD2             DAC_SHHR_THOLD2_Msk                        /*!<DAC channel2 hold time */

/******************  Bit definition for DAC_SHRR register  ******************/
#define DAC_SHRR_TREFRESH1_Pos      (0U)
#define DAC_SHRR_TREFRESH1_Msk      (0xFFU << DAC_SHRR_TREFRESH1_Pos)          /*!< 0x000000FF */
#define DAC_SHRR_TREFRESH1          DAC_SHRR_TREFRESH1_Msk                     /*!<DAC channel1 refresh time */
#define DAC_SHRR_TREFRESH2_Pos      (16U)
#define DAC_SHRR_TREFRESH2_Msk      (0xFFU << DAC_SHRR_TREFRESH2_Pos)          /*!< 0x00FF0000 */
#define DAC_SHRR_TREFRESH2          DAC_SHRR_TREFRESH2_Msk                     /*!<DAC channel2 refresh time */

/**********************  Bit definition for DAC_HWCFGR0 register  ***************/
#define DAC_HWCFGR0_DUAL_Pos      (0U)
#define DAC_HWCFGR0_DUAL_Msk      (0xFF << DAC_HWCFGR0_DUAL_Pos)               /*!< 0x0000000F */
#define DAC_HWCFGR0_DUAL          DAC_HWCFGR0_DUAL_Msk                         /*!< Dual DAC capability */
#define DAC_HWCFGR0_LFSR_Pos      (4U)
#define DAC_HWCFGR0_LFSR_Msk      (0xFU << DAC_HWCFGR0_LFSR_Pos)               /*!< 0x000000F0 */
#define DAC_HWCFGR0_LFSR          DAC_HWCFGR0_LFSR_Msk                         /*!< Pseudonoise wave generation capability */
#define DAC_HWCFGR0_TRIANGLE_Pos  (8U)
#define DAC_HWCFGR0_TRIANGLE_Msk  (0xFU << DAC_HWCFGR0_TRIANGLE_Pos)           /*!< 0x00000F00 */
#define DAC_HWCFGR0_TRIANGLE      DAC_HWCFGR0_TRIANGLE_Msk                     /*!< Triangle wave generation capability */
#define DAC_HWCFGR0_SAMPLE_Pos    (12U)
#define DAC_HWCFGR0_SAMPLE_Msk    (0xFU << DAC_HWCFGR0_SAMPLE_Pos)             /*!< 0x0000F000 */
#define DAC_HWCFGR0_SAMPLE        DAC_HWCFGR0_SAMPLE_Msk                       /*!< Sample and Hold mode capability */
#define DAC_HWCFGR0_OR_CFG_Pos    (16U)
#define DAC_HWCFGR0_OR_CFG_Msk    (0xFFU << DAC_HWCFGR0_OR_CFG_Pos)            /*!< 0x00FF0000 */
#define DAC_HWCFGR0_OR_CFG        DAC_HWCFGR0_OR_CFG_Msk                       /*!< option register bit width */

/********************  Bit definition for DAC_VERR register********************/
#define DAC_VERR_MINREV_Pos        (0U)
#define DAC_VERR_MINREV_Msk        (0xFU << DAC_VERR_MINREV_Pos)           /*!< 0x0000000F */
#define DAC_VERR_MINREV            DAC_VERR_MINREV_Msk                     /*!< MAJREV[3:0] bits (Minor revision) */
#define DAC_VERR_MAJREV_Pos        (4U)
#define DAC_VERR_MAJREV_Msk        (0xFU << DAC_VERR_MAJREV_Pos)           /*!< 0x000000F0 */
#define DAC_VERR_MAJREV            DAC_VERR_MAJREV_Msk                     /*!< MINREV[3:0] bits (Major revision) */

/**********************  Bit definition for DAC_IPIDR register  ****************/
#define DAC_IPIDR_IPID_Pos       (0U)
#define DAC_IPIDR_IPID_Msk       (0xFFFFFFFFU << DAC_IPIDR_IPID_Pos)         /*!< 0xFFFFFFFF */
#define DAC_IPIDR_IPID           DAC_IPIDR_IPID_Msk                          /*!< IP Identification */

/**********************  Bit definition for DAC_SIDR register  *****************/
#define DAC_SIDR_SID_Pos         (0U)
#define DAC_SIDR_SID_Msk         (0xFFFFFFFFU << DAC_SIDR_SID_Pos)           /*!< 0xFFFFFFFF */
#define DAC_SIDR_SID             DAC_SIDR_SID_Msk                            /*!< IP size identification */

/******************************************************************************/
/*                                                                            */
/*                                DBG                                         */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for DBGMCU_IDCODE register  *************/
#define DBGMCU_IDCODE_DEV_ID_Pos              (0U)
#define DBGMCU_IDCODE_DEV_ID_Msk              (0xFFFU << DBGMCU_IDCODE_DEV_ID_Pos) /*!< 0x00000FFF */
#define DBGMCU_IDCODE_DEV_ID                  DBGMCU_IDCODE_DEV_ID_Msk
#define DBGMCU_IDCODE_REV_ID_Pos              (16U)
#define DBGMCU_IDCODE_REV_ID_Msk              (0xFFFFU << DBGMCU_IDCODE_REV_ID_Pos) /*!< 0xFFFF0000 */
#define DBGMCU_IDCODE_REV_ID                  DBGMCU_IDCODE_REV_ID_Msk

/********************  Bit definition for DBGMCU_CR register  *****************/
#define DBGMCU_CR_DBG_SLEEP_Pos               (0U)
#define DBGMCU_CR_DBG_SLEEP_Msk               (0x1U << DBGMCU_CR_DBG_SLEEP_Pos) /*!< 0x00000001 */
#define DBGMCU_CR_DBG_SLEEP                   DBGMCU_CR_DBG_SLEEP_Msk
#define DBGMCU_CR_DBG_STOP_Pos                (1U)
#define DBGMCU_CR_DBG_STOP_Msk                (0x1U << DBGMCU_CR_DBG_STOP_Pos) /*!< 0x00000002 */
#define DBGMCU_CR_DBG_STOP                    DBGMCU_CR_DBG_STOP_Msk
#define DBGMCU_CR_DBG_STANDBY_Pos             (2U)
#define DBGMCU_CR_DBG_STANDBY_Msk             (0x1U << DBGMCU_CR_DBG_STANDBY_Pos) /*!< 0x00000004 */
#define DBGMCU_CR_DBG_STANDBY                 DBGMCU_CR_DBG_STANDBY_Msk
#define DBGMCU_CR_DBG_WDFZCTL_Pos             (24U)
#define DBGMCU_CR_DBG_WDFZCTL_Msk             (0x1U << DBGMCU_CR_DBG_WDFZCTL_Pos) /*!< 0x01000000 */
#define DBGMCU_CR_DBG_WDFZCTL                 DBGMCU_CR_DBG_WDFZCTL_Msk
#define DBGMCU_CR_DBG_TRGOEN_Pos              (28U)
#define DBGMCU_CR_DBG_TRGOEN_Msk              (0x1U << DBGMCU_CR_DBG_TRGOEN_Pos) /*!< 0x10000000 */
#define DBGMCU_CR_DBG_TRGOEN                  DBGMCU_CR_DBG_TRGOEN_Msk

/********************  Bit definition for APB4FZ register  ************/
#define DBGMCU_APB4_FZ_DBG_IWDG2_STOP_Pos     (2U)
#define DBGMCU_APB4_FZ_DBG_IWDG2_STOP_Msk     (0x1U << DBGMCU_APB4_FZ_DBG_IWDG2_STOP_Pos) /*!< 0x00000004 */
#define DBGMCU_APB4_FZ_DBG_IWDG2_STOP         DBGMCU_APB4_FZ_DBG_IWDG2_STOP_Msk

/********************  Bit definition for APB1FZ register  ************/
#define DBGMCU_APB1_FZ_DBG_TIM2_STOP_Pos      (0U)
#define DBGMCU_APB1_FZ_DBG_TIM2_STOP_Msk      (0x1U << DBGMCU_APB1_FZ_DBG_TIM2_STOP_Pos) /*!< 0x00000001 */
#define DBGMCU_APB1_FZ_DBG_TIM2_STOP          DBGMCU_APB1_FZ_DBG_TIM2_STOP_Msk
#define DBGMCU_APB1_FZ_DBG_TIM3_STOP_Pos      (1U)
#define DBGMCU_APB1_FZ_DBG_TIM3_STOP_Msk      (0x1U << DBGMCU_APB1_FZ_DBG_TIM3_STOP_Pos) /*!< 0x00000002 */
#define DBGMCU_APB1_FZ_DBG_TIM3_STOP          DBGMCU_APB1_FZ_DBG_TIM3_STOP_Msk
#define DBGMCU_APB1_FZ_DBG_TIM4_STOP_Pos      (2U)
#define DBGMCU_APB1_FZ_DBG_TIM4_STOP_Msk      (0x1U << DBGMCU_APB1_FZ_DBG_TIM4_STOP_Pos) /*!< 0x00000004 */
#define DBGMCU_APB1_FZ_DBG_TIM4_STOP          DBGMCU_APB1_FZ_DBG_TIM4_STOP_Msk
#define DBGMCU_APB1_FZ_DBG_TIM5_STOP_Pos      (3U)
#define DBGMCU_APB1_FZ_DBG_TIM5_STOP_Msk      (0x1U << DBGMCU_APB1_FZ_DBG_TIM5_STOP_Pos) /*!< 0x00000008 */
#define DBGMCU_APB1_FZ_DBG_TIM5_STOP          DBGMCU_APB1_FZ_DBG_TIM5_STOP_Msk
#define DBGMCU_APB1_FZ_DBG_TIM6_STOP_Pos      (4U)
#define DBGMCU_APB1_FZ_DBG_TIM6_STOP_Msk      (0x1U << DBGMCU_APB1_FZ_DBG_TIM6_STOP_Pos) /*!< 0x00000010 */
#define DBGMCU_APB1_FZ_DBG_TIM6_STOP          DBGMCU_APB1_FZ_DBG_TIM6_STOP_Msk
#define DBGMCU_APB1_FZ_DBG_TIM7_STOP_Pos      (5U)
#define DBGMCU_APB1_FZ_DBG_TIM7_STOP_Msk      (0x1U << DBGMCU_APB1_FZ_DBG_TIM7_STOP_Pos) /*!< 0x00000020 */
#define DBGMCU_APB1_FZ_DBG_TIM7_STOP          DBGMCU_APB1_FZ_DBG_TIM7_STOP_Msk
#define DBGMCU_APB1_FZ_DBG_TIM12_STOP_Pos     (6U)
#define DBGMCU_APB1_FZ_DBG_TIM12_STOP_Msk     (0x1U << DBGMCU_APB1_FZ_DBG_TIM12_STOP_Pos) /*!< 0x00000040 */
#define DBGMCU_APB1_FZ_DBG_TIM12_STOP         DBGMCU_APB1_FZ_DBG_TIM12_STOP_Msk
#define DBGMCU_APB1_FZ_DBG_TIM13_STOP_Pos     (7U)
#define DBGMCU_APB1_FZ_DBG_TIM13_STOP_Msk     (0x1U << DBGMCU_APB1_FZ_DBG_TIM13_STOP_Pos) /*!< 0x00000080 */
#define DBGMCU_APB1_FZ_DBG_TIM13_STOP         DBGMCU_APB1_FZ_DBG_TIM13_STOP_Msk
#define DBGMCU_APB1_FZ_DBG_TIM14_STOP_Pos     (8U)
#define DBGMCU_APB1_FZ_DBG_TIM14_STOP_Msk     (0x1U << DBGMCU_APB1_FZ_DBG_TIM14_STOP_Pos) /*!< 0x00000100 */
#define DBGMCU_APB1_FZ_DBG_TIM14_STOP         DBGMCU_APB1_FZ_DBG_TIM14_STOP_Msk
#define DBGMCU_APB1_FZ_DBG_LPTIM1_STOP_Pos    (9U)
#define DBGMCU_APB1_FZ_DBG_LPTIM1_STOP_Msk    (0x1U << DBGMCU_APB1_FZ_DBG_LPTIM1_STOP_Pos) /*!< 0x00000200 */
#define DBGMCU_APB1_FZ_DBG_LPTIM1_STOP        DBGMCU_APB1_FZ_DBG_LPTIM1_STOP_Msk
#define DBGMCU_APB1_FZ_DBG_WWDG1_STOP_Pos     (10U)
#define DBGMCU_APB1_FZ_DBG_WWDG1_STOP_Msk     (0x1U << DBGMCU_APB1_FZ_DBG_WWDG1_STOP_Pos) /*!< 0x00000400 */
#define DBGMCU_APB1_FZ_DBG_WWDG1_STOP         DBGMCU_APB1_FZ_DBG_WWDG1_STOP_Msk
#define DBGMCU_APB1_FZ_DBG_I2C1_STOP_Pos      (18U)
#define DBGMCU_APB1_FZ_DBG_I2C1_STOP_Msk      (0x1U << DBGMCU_APB1_FZ_DBG_I2C1_STOP_Pos) /*!< 0x00040000 */
#define DBGMCU_APB1_FZ_DBG_I2C1_STOP          DBGMCU_APB1_FZ_DBG_I2C1_STOP_Msk
#define DBGMCU_APB1_FZ_DBG_I2C2_STOP_Pos      (19U)
#define DBGMCU_APB1_FZ_DBG_I2C2_STOP_Msk      (0x1U << DBGMCU_APB1_FZ_DBG_I2C2_STOP_Pos) /*!< 0x00080000 */
#define DBGMCU_APB1_FZ_DBG_I2C2_STOP          DBGMCU_APB1_FZ_DBG_I2C2_STOP_Msk
#define DBGMCU_APB1_FZ_DBG_I2C3_STOP_Pos      (20U)
#define DBGMCU_APB1_FZ_DBG_I2C3_STOP_Msk      (0x1U << DBGMCU_APB1_FZ_DBG_I2C3_STOP_Pos) /*!< 0x00100000 */
#define DBGMCU_APB1_FZ_DBG_I2C3_STOP          DBGMCU_APB1_FZ_DBG_I2C3_STOP_Msk
#define DBGMCU_APB1_FZ_DBG_I2C5_STOP_Pos      (21U)
#define DBGMCU_APB1_FZ_DBG_I2C5_STOP_Msk      (0x1U << DBGMCU_APB1_FZ_DBG_I2C5_STOP_Pos) /*!< 0x00200000 */
#define DBGMCU_APB1_FZ_DBG_I2C5_STOP          DBGMCU_APB1_FZ_DBG_I2C5_STOP_Msk

/********************  Bit definition for APB2FZ register  ************/
#define DBGMCU_APB2_FZ_DBG_TIM1_STOP_Pos      (0U)
#define DBGMCU_APB2_FZ_DBG_TIM1_STOP_Msk      (0x1U << DBGMCU_APB2_FZ_DBG_TIM1_STOP_Pos) /*!< 0x00000001 */
#define DBGMCU_APB2_FZ_DBG_TIM1_STOP          DBGMCU_APB2_FZ_DBG_TIM1_STOP_Msk
#define DBGMCU_APB2_FZ_DBG_TIM8_STOP_Pos      (1U)
#define DBGMCU_APB2_FZ_DBG_TIM8_STOP_Msk      (0x1U << DBGMCU_APB2_FZ_DBG_TIM8_STOP_Pos) /*!< 0x00000002 */
#define DBGMCU_APB2_FZ_DBG_TIM8_STOP          DBGMCU_APB2_FZ_DBG_TIM8_STOP_Msk
#define DBGMCU_APB2_FZ_DBG_TIM15_STOP_Pos     (6U)
#define DBGMCU_APB2_FZ_DBG_TIM15_STOP_Msk     (0x1U << DBGMCU_APB2_FZ_DBG_TIM15_STOP_Pos) /*!< 0x00000040 */
#define DBGMCU_APB2_FZ_DBG_TIM15_STOP         DBGMCU_APB2_FZ_DBG_TIM15_STOP_Msk
#define DBGMCU_APB2_FZ_DBG_TIM16_STOP_Pos     (7U)
#define DBGMCU_APB2_FZ_DBG_TIM16_STOP_Msk     (0x1U << DBGMCU_APB2_FZ_DBG_TIM16_STOP_Pos) /*!< 0x00000080 */
#define DBGMCU_APB2_FZ_DBG_TIM16_STOP         DBGMCU_APB2_FZ_DBG_TIM16_STOP_Msk
#define DBGMCU_APB2_FZ_DBG_TIM17_STOP_Pos     (8U)
#define DBGMCU_APB2_FZ_DBG_TIM17_STOP_Msk     (0x1U << DBGMCU_APB2_FZ_DBG_TIM17_STOP_Pos) /*!< 0x00000100 */
#define DBGMCU_APB2_FZ_DBG_TIM17_STOP         DBGMCU_APB2_FZ_DBG_TIM17_STOP_Msk
#define DBGMCU_APB2_FZ_DBG_FDCAN_STOP_Pos     (15U)
#define DBGMCU_APB2_FZ_DBG_FDCAN_STOP_Msk     (0x1U << DBGMCU_APB2_FZ_DBG_FDCAN_STOP_Pos) /*!< 0x00008000 */
#define DBGMCU_APB2_FZ_DBG_FDCAN_STOP         DBGMCU_APB2_FZ_DBG_FDCAN_STOP_Msk

/********************  Bit definition for APB3FZ register  ************/
#define DBGMCU_APB3_FZ_DBG_LPTIM2_STOP_Pos    (1U)
#define DBGMCU_APB3_FZ_DBG_LPTIM2_STOP_Msk    (0x1U << DBGMCU_APB3_FZ_DBG_LPTIM2_STOP_Pos) /*!< 0x00000002 */
#define DBGMCU_APB3_FZ_DBG_LPTIM2_STOP        DBGMCU_APB3_FZ_DBG_LPTIM2_STOP_Msk
#define DBGMCU_APB3_FZ_DBG_LPTIM3_STOP_Pos    (2U)
#define DBGMCU_APB3_FZ_DBG_LPTIM3_STOP_Msk    (0x1U << DBGMCU_APB3_FZ_DBG_LPTIM3_STOP_Pos) /*!< 0x00000004 */
#define DBGMCU_APB3_FZ_DBG_LPTIM3_STOP        DBGMCU_APB3_FZ_DBG_LPTIM3_STOP_Msk
#define DBGMCU_APB3_FZ_DBG_LPTIM4_STOP_Pos    (3U)
#define DBGMCU_APB3_FZ_DBG_LPTIM4_STOP_Msk    (0x1U << DBGMCU_APB3_FZ_DBG_LPTIM4_STOP_Pos) /*!< 0x00000008 */
#define DBGMCU_APB3_FZ_DBG_LPTIM4_STOP        DBGMCU_APB3_FZ_DBG_LPTIM4_STOP_Msk
#define DBGMCU_APB3_FZ_DBG_LPTIM5_STOP_Pos    (4U)
#define DBGMCU_APB3_FZ_DBG_LPTIM5_STOP_Msk    (0x1U << DBGMCU_APB3_FZ_DBG_LPTIM5_STOP_Pos) /*!< 0x00000010 */
#define DBGMCU_APB3_FZ_DBG_LPTIM5_STOP        DBGMCU_APB3_FZ_DBG_LPTIM5_STOP_Msk

/********************  Bit definition for APB5FZ register  ************/
#define DBGMCU_APB5_FZ_DBG_I2C4_STOP_Pos      (2U)
#define DBGMCU_APB5_FZ_DBG_I2C4_STOP_Msk      (0x1U << DBGMCU_APB5_FZ_DBG_I2C4_STOP_Pos) /*!< 0x00000004 */
#define DBGMCU_APB5_FZ_DBG_I2C4_STOP          DBGMCU_APB5_FZ_DBG_I2C4_STOP_Msk
#define DBGMCU_APB5_FZ_DBG_IWDG1_STOP_Pos     (3U)
#define DBGMCU_APB5_FZ_DBG_IWDG1_STOP_Msk     (0x1U << DBGMCU_APB5_FZ_DBG_IWDG1_STOP_Pos) /*!< 0x00000008 */
#define DBGMCU_APB5_FZ_DBG_IWDG1_STOP         DBGMCU_APB5_FZ_DBG_IWDG1_STOP_Msk
#define DBGMCU_APB5_FZ_DBG_RTC_STOP_Pos       (4U)
#define DBGMCU_APB5_FZ_DBG_RTC_STOP_Msk       (0x1U << DBGMCU_APB5_FZ_DBG_RTC_STOP_Pos) /*!< 0x00000010 */
#define DBGMCU_APB5_FZ_DBG_RTC_STOP           DBGMCU_APB5_FZ_DBG_RTC_STOP_Msk
#define DBGMCU_APB5_FZ_DBG_I2C6_STOP_Pos      (9U)
#define DBGMCU_APB5_FZ_DBG_I2C6_STOP_Msk      (0x1U << DBGMCU_APB5_FZ_DBG_I2C6_STOP_Pos) /*!< 0x00000200 */
#define DBGMCU_APB5_FZ_DBG_I2C6_STOP          DBGMCU_APB5_FZ_DBG_I2C6_STOP_Msk

/******************************************************************************/
/*                                                                            */
/*                                    DCMI                                    */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for DCMI_CR register  ******************/
#define DCMI_CR_CAPTURE_Pos        (0U)
#define DCMI_CR_CAPTURE_Msk        (0x1UL << DCMI_CR_CAPTURE_Pos)              /*!< 0x00000001 */
#define DCMI_CR_CAPTURE            DCMI_CR_CAPTURE_Msk
#define DCMI_CR_CM_Pos             (1U)
#define DCMI_CR_CM_Msk             (0x1UL << DCMI_CR_CM_Pos)                   /*!< 0x00000002 */
#define DCMI_CR_CM                 DCMI_CR_CM_Msk
#define DCMI_CR_CROP_Pos           (2U)
#define DCMI_CR_CROP_Msk           (0x1UL << DCMI_CR_CROP_Pos)                 /*!< 0x00000004 */
#define DCMI_CR_CROP               DCMI_CR_CROP_Msk
#define DCMI_CR_JPEG_Pos           (3U)
#define DCMI_CR_JPEG_Msk           (0x1UL << DCMI_CR_JPEG_Pos)                 /*!< 0x00000008 */
#define DCMI_CR_JPEG               DCMI_CR_JPEG_Msk
#define DCMI_CR_ESS_Pos            (4U)
#define DCMI_CR_ESS_Msk            (0x1UL << DCMI_CR_ESS_Pos)                  /*!< 0x00000010 */
#define DCMI_CR_ESS                DCMI_CR_ESS_Msk
#define DCMI_CR_PCKPOL_Pos         (5U)
#define DCMI_CR_PCKPOL_Msk         (0x1UL << DCMI_CR_PCKPOL_Pos)               /*!< 0x00000020 */
#define DCMI_CR_PCKPOL             DCMI_CR_PCKPOL_Msk
#define DCMI_CR_HSPOL_Pos          (6U)
#define DCMI_CR_HSPOL_Msk          (0x1UL << DCMI_CR_HSPOL_Pos)                /*!< 0x00000040 */
#define DCMI_CR_HSPOL              DCMI_CR_HSPOL_Msk
#define DCMI_CR_VSPOL_Pos          (7U)
#define DCMI_CR_VSPOL_Msk          (0x1UL << DCMI_CR_VSPOL_Pos)                /*!< 0x00000080 */
#define DCMI_CR_VSPOL              DCMI_CR_VSPOL_Msk
#define DCMI_CR_FCRC_0             ((uint32_t)0x00000100U)
#define DCMI_CR_FCRC_1             ((uint32_t)0x00000200U)
#define DCMI_CR_EDM_0              ((uint32_t)0x00000400U)
#define DCMI_CR_EDM_1              ((uint32_t)0x00000800U)
#define DCMI_CR_CRE_Pos            (12U)
#define DCMI_CR_CRE_Msk            (0x1UL << DCMI_CR_CRE_Pos)                  /*!< 0x00001000 */
#define DCMI_CR_CRE                DCMI_CR_CRE_Msk
#define DCMI_CR_ENABLE_Pos         (14U)
#define DCMI_CR_ENABLE_Msk         (0x1UL << DCMI_CR_ENABLE_Pos)               /*!< 0x00004000 */
#define DCMI_CR_ENABLE             DCMI_CR_ENABLE_Msk
#define DCMI_CR_BSM_Pos            (16U)
#define DCMI_CR_BSM_Msk            (0x3UL << DCMI_CR_BSM_Pos)                  /*!< 0x00030000 */
#define DCMI_CR_BSM                DCMI_CR_BSM_Msk
#define DCMI_CR_BSM_0              (0x1U << DCMI_CR_BSM_Pos)                   /*!< 0x00010000 */
#define DCMI_CR_BSM_1              (0x2U << DCMI_CR_BSM_Pos)                   /*!< 0x00020000 */
#define DCMI_CR_OEBS_Pos           (18U)
#define DCMI_CR_OEBS_Msk           (0x1UL << DCMI_CR_OEBS_Pos)                 /*!< 0x00040000 */
#define DCMI_CR_OEBS               DCMI_CR_OEBS_Msk
#define DCMI_CR_LSM_Pos            (19U)
#define DCMI_CR_LSM_Msk            (0x1UL << DCMI_CR_LSM_Pos)                  /*!< 0x00080000 */
#define DCMI_CR_LSM                DCMI_CR_LSM_Msk
#define DCMI_CR_OELS_Pos           (20U)
#define DCMI_CR_OELS_Msk           (0x1UL << DCMI_CR_OELS_Pos)                 /*!< 0x00100000 */
#define DCMI_CR_OELS               DCMI_CR_OELS_Msk

/********************  Bits definition for DCMI_SR register  ******************/
#define DCMI_SR_HSYNC_Pos          (0U)
#define DCMI_SR_HSYNC_Msk          (0x1UL << DCMI_SR_HSYNC_Pos)                /*!< 0x00000001 */
#define DCMI_SR_HSYNC              DCMI_SR_HSYNC_Msk
#define DCMI_SR_VSYNC_Pos          (1U)
#define DCMI_SR_VSYNC_Msk          (0x1UL << DCMI_SR_VSYNC_Pos)                /*!< 0x00000002 */
#define DCMI_SR_VSYNC              DCMI_SR_VSYNC_Msk
#define DCMI_SR_FNE_Pos            (2U)
#define DCMI_SR_FNE_Msk            (0x1UL << DCMI_SR_FNE_Pos)                  /*!< 0x00000004 */
#define DCMI_SR_FNE                DCMI_SR_FNE_Msk

/********************  Bits definition for DCMI_RIS register   ****************/
#define DCMI_RIS_FRAME_RIS_Pos     (0U)
#define DCMI_RIS_FRAME_RIS_Msk     (0x1UL << DCMI_RIS_FRAME_RIS_Pos)           /*!< 0x00000001 */
#define DCMI_RIS_FRAME_RIS         DCMI_RIS_FRAME_RIS_Msk
#define DCMI_RIS_OVR_RIS_Pos       (1U)
#define DCMI_RIS_OVR_RIS_Msk       (0x1UL << DCMI_RIS_OVR_RIS_Pos)             /*!< 0x00000002 */
#define DCMI_RIS_OVR_RIS           DCMI_RIS_OVR_RIS_Msk
#define DCMI_RIS_ERR_RIS_Pos       (2U)
#define DCMI_RIS_ERR_RIS_Msk       (0x1UL << DCMI_RIS_ERR_RIS_Pos)             /*!< 0x00000004 */
#define DCMI_RIS_ERR_RIS           DCMI_RIS_ERR_RIS_Msk
#define DCMI_RIS_VSYNC_RIS_Pos     (3U)
#define DCMI_RIS_VSYNC_RIS_Msk     (0x1UL << DCMI_RIS_VSYNC_RIS_Pos)           /*!< 0x00000008 */
#define DCMI_RIS_VSYNC_RIS         DCMI_RIS_VSYNC_RIS_Msk
#define DCMI_RIS_LINE_RIS_Pos      (4U)
#define DCMI_RIS_LINE_RIS_Msk      (0x1UL << DCMI_RIS_LINE_RIS_Pos)            /*!< 0x00000010 */
#define DCMI_RIS_LINE_RIS          DCMI_RIS_LINE_RIS_Msk

/********************  Bits definition for DCMI_IER register  *****************/
#define DCMI_IER_FRAME_IE_Pos      (0U)
#define DCMI_IER_FRAME_IE_Msk      (0x1UL << DCMI_IER_FRAME_IE_Pos)            /*!< 0x00000001 */
#define DCMI_IER_FRAME_IE          DCMI_IER_FRAME_IE_Msk
#define DCMI_IER_OVR_IE_Pos        (1U)
#define DCMI_IER_OVR_IE_Msk        (0x1UL << DCMI_IER_OVR_IE_Pos)              /*!< 0x00000002 */
#define DCMI_IER_OVR_IE            DCMI_IER_OVR_IE_Msk
#define DCMI_IER_ERR_IE_Pos        (2U)
#define DCMI_IER_ERR_IE_Msk        (0x1UL << DCMI_IER_ERR_IE_Pos)              /*!< 0x00000004 */
#define DCMI_IER_ERR_IE            DCMI_IER_ERR_IE_Msk
#define DCMI_IER_VSYNC_IE_Pos      (3U)
#define DCMI_IER_VSYNC_IE_Msk      (0x1UL << DCMI_IER_VSYNC_IE_Pos)            /*!< 0x00000008 */
#define DCMI_IER_VSYNC_IE          DCMI_IER_VSYNC_IE_Msk
#define DCMI_IER_LINE_IE_Pos       (4U)
#define DCMI_IER_LINE_IE_Msk       (0x1UL << DCMI_IER_LINE_IE_Pos)             /*!< 0x00000010 */
#define DCMI_IER_LINE_IE           DCMI_IER_LINE_IE_Msk


/********************  Bits definition for DCMI_MIS register  *****************/
#define DCMI_MIS_FRAME_MIS_Pos     (0U)
#define DCMI_MIS_FRAME_MIS_Msk     (0x1UL << DCMI_MIS_FRAME_MIS_Pos)           /*!< 0x00000001 */
#define DCMI_MIS_FRAME_MIS         DCMI_MIS_FRAME_MIS_Msk
#define DCMI_MIS_OVR_MIS_Pos       (1U)
#define DCMI_MIS_OVR_MIS_Msk       (0x1UL << DCMI_MIS_OVR_MIS_Pos)             /*!< 0x00000002 */
#define DCMI_MIS_OVR_MIS           DCMI_MIS_OVR_MIS_Msk
#define DCMI_MIS_ERR_MIS_Pos       (2U)
#define DCMI_MIS_ERR_MIS_Msk       (0x1UL << DCMI_MIS_ERR_MIS_Pos)             /*!< 0x00000004 */
#define DCMI_MIS_ERR_MIS           DCMI_MIS_ERR_MIS_Msk
#define DCMI_MIS_VSYNC_MIS_Pos     (3U)
#define DCMI_MIS_VSYNC_MIS_Msk     (0x1UL << DCMI_MIS_VSYNC_MIS_Pos)           /*!< 0x00000008 */
#define DCMI_MIS_VSYNC_MIS         DCMI_MIS_VSYNC_MIS_Msk
#define DCMI_MIS_LINE_MIS_Pos      (4U)
#define DCMI_MIS_LINE_MIS_Msk      (0x1UL << DCMI_MIS_LINE_MIS_Pos)            /*!< 0x00000010 */
#define DCMI_MIS_LINE_MIS          DCMI_MIS_LINE_MIS_Msk


/********************  Bits definition for DCMI_ICR register  *****************/
#define DCMI_ICR_FRAME_ISC_Pos     (0U)
#define DCMI_ICR_FRAME_ISC_Msk     (0x1UL << DCMI_ICR_FRAME_ISC_Pos)           /*!< 0x00000001 */
#define DCMI_ICR_FRAME_ISC         DCMI_ICR_FRAME_ISC_Msk
#define DCMI_ICR_OVR_ISC_Pos       (1U)
#define DCMI_ICR_OVR_ISC_Msk       (0x1UL << DCMI_ICR_OVR_ISC_Pos)             /*!< 0x00000002 */
#define DCMI_ICR_OVR_ISC           DCMI_ICR_OVR_ISC_Msk
#define DCMI_ICR_ERR_ISC_Pos       (2U)
#define DCMI_ICR_ERR_ISC_Msk       (0x1UL << DCMI_ICR_ERR_ISC_Pos)             /*!< 0x00000004 */
#define DCMI_ICR_ERR_ISC           DCMI_ICR_ERR_ISC_Msk
#define DCMI_ICR_VSYNC_ISC_Pos     (3U)
#define DCMI_ICR_VSYNC_ISC_Msk     (0x1UL << DCMI_ICR_VSYNC_ISC_Pos)           /*!< 0x00000008 */
#define DCMI_ICR_VSYNC_ISC         DCMI_ICR_VSYNC_ISC_Msk
#define DCMI_ICR_LINE_ISC_Pos      (4U)
#define DCMI_ICR_LINE_ISC_Msk      (0x1UL << DCMI_ICR_LINE_ISC_Pos)            /*!< 0x00000010 */
#define DCMI_ICR_LINE_ISC          DCMI_ICR_LINE_ISC_Msk


/********************  Bits definition for DCMI_ESCR register  ******************/
#define DCMI_ESCR_FSC_Pos          (0U)
#define DCMI_ESCR_FSC_Msk          (0xFFUL << DCMI_ESCR_FSC_Pos)               /*!< 0x000000FF */
#define DCMI_ESCR_FSC              DCMI_ESCR_FSC_Msk
#define DCMI_ESCR_LSC_Pos          (8U)
#define DCMI_ESCR_LSC_Msk          (0xFFUL << DCMI_ESCR_LSC_Pos)               /*!< 0x0000FF00 */
#define DCMI_ESCR_LSC              DCMI_ESCR_LSC_Msk
#define DCMI_ESCR_LEC_Pos          (16U)
#define DCMI_ESCR_LEC_Msk          (0xFFUL << DCMI_ESCR_LEC_Pos)               /*!< 0x00FF0000 */
#define DCMI_ESCR_LEC              DCMI_ESCR_LEC_Msk
#define DCMI_ESCR_FEC_Pos          (24U)
#define DCMI_ESCR_FEC_Msk          (0xFFUL << DCMI_ESCR_FEC_Pos)               /*!< 0xFF000000 */
#define DCMI_ESCR_FEC              DCMI_ESCR_FEC_Msk

/********************  Bits definition for DCMI_ESUR register  ******************/
#define DCMI_ESUR_FSU_Pos          (0U)
#define DCMI_ESUR_FSU_Msk          (0xFFUL << DCMI_ESUR_FSU_Pos)               /*!< 0x000000FF */
#define DCMI_ESUR_FSU              DCMI_ESUR_FSU_Msk
#define DCMI_ESUR_LSU_Pos          (8U)
#define DCMI_ESUR_LSU_Msk          (0xFFUL << DCMI_ESUR_LSU_Pos)               /*!< 0x0000FF00 */
#define DCMI_ESUR_LSU              DCMI_ESUR_LSU_Msk
#define DCMI_ESUR_LEU_Pos          (16U)
#define DCMI_ESUR_LEU_Msk          (0xFFUL << DCMI_ESUR_LEU_Pos)               /*!< 0x00FF0000 */
#define DCMI_ESUR_LEU              DCMI_ESUR_LEU_Msk
#define DCMI_ESUR_FEU_Pos          (24U)
#define DCMI_ESUR_FEU_Msk          (0xFFUL << DCMI_ESUR_FEU_Pos)               /*!< 0xFF000000 */
#define DCMI_ESUR_FEU              DCMI_ESUR_FEU_Msk

/********************  Bits definition for DCMI_CWSTRT register  ******************/
#define DCMI_CWSTRT_HOFFCNT_Pos    (0U)
#define DCMI_CWSTRT_HOFFCNT_Msk    (0x3FFFUL << DCMI_CWSTRT_HOFFCNT_Pos)       /*!< 0x00003FFF */
#define DCMI_CWSTRT_HOFFCNT        DCMI_CWSTRT_HOFFCNT_Msk
#define DCMI_CWSTRT_VST_Pos        (16U)
#define DCMI_CWSTRT_VST_Msk        (0x1FFFUL << DCMI_CWSTRT_VST_Pos)           /*!< 0x1FFF0000 */
#define DCMI_CWSTRT_VST            DCMI_CWSTRT_VST_Msk

/********************  Bits definition for DCMI_CWSIZE register  ******************/
#define DCMI_CWSIZE_CAPCNT_Pos     (0U)
#define DCMI_CWSIZE_CAPCNT_Msk     (0x3FFFUL << DCMI_CWSIZE_CAPCNT_Pos)        /*!< 0x00003FFF */
#define DCMI_CWSIZE_CAPCNT         DCMI_CWSIZE_CAPCNT_Msk
#define DCMI_CWSIZE_VLINE_Pos      (16U)
#define DCMI_CWSIZE_VLINE_Msk      (0x3FFFUL << DCMI_CWSIZE_VLINE_Pos)         /*!< 0x3FFF0000 */
#define DCMI_CWSIZE_VLINE          DCMI_CWSIZE_VLINE_Msk

/********************  Bits definition for DCMI_DR register  ******************/
#define DCMI_DR_BYTE0_Pos          (0U)
#define DCMI_DR_BYTE0_Msk          (0xFFUL << DCMI_DR_BYTE0_Pos)               /*!< 0x000000FF */
#define DCMI_DR_BYTE0              DCMI_DR_BYTE0_Msk
#define DCMI_DR_BYTE1_Pos          (8U)
#define DCMI_DR_BYTE1_Msk          (0xFFUL << DCMI_DR_BYTE1_Pos)               /*!< 0x0000FF00 */
#define DCMI_DR_BYTE1              DCMI_DR_BYTE1_Msk
#define DCMI_DR_BYTE2_Pos          (16U)
#define DCMI_DR_BYTE2_Msk          (0xFFUL << DCMI_DR_BYTE2_Pos)               /*!< 0x00FF0000 */
#define DCMI_DR_BYTE2              DCMI_DR_BYTE2_Msk
#define DCMI_DR_BYTE3_Pos          (24U)
#define DCMI_DR_BYTE3_Msk          (0xFFUL << DCMI_DR_BYTE3_Pos)               /*!< 0xFF000000 */
#define DCMI_DR_BYTE3              DCMI_DR_BYTE3_Msk
