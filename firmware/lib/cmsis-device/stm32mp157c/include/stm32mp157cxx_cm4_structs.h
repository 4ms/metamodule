/** @addtogroup Peripheral_registers_structures
  * @{
  */

/**
  * @brief Analog to Digital Converter
  */

typedef struct
{
  __IO uint32_t ISR;              /*!< ADC Interrupt and Status Register,                 Address offset: 0x00 */
  __IO uint32_t IER;              /*!< ADC Interrupt Enable Register,                     Address offset: 0x04 */
  __IO uint32_t CR;               /*!< ADC control register,                              Address offset: 0x08 */
  __IO uint32_t CFGR;             /*!< ADC Configuration register,                        Address offset: 0x0C */
  __IO uint32_t CFGR2;            /*!< ADC Configuration register 2,                      Address offset: 0x10 */
  __IO uint32_t SMPR1;            /*!< ADC sample time register 1,                        Address offset: 0x14 */
  __IO uint32_t SMPR2;            /*!< ADC sample time register 2,                        Address offset: 0x18 */
  __IO uint32_t PCSEL;            /*!< ADC pre-channel selection,                         Address offset: 0x1C */
  __IO uint32_t LTR1;             /*!< ADC watchdog Lower threshold register 1,           Address offset: 0x20 */
  __IO uint32_t HTR1;             /*!< ADC watchdog higher threshold register 1,          Address offset: 0x24 */
  uint32_t      RESERVED1;        /*!< Reserved, 0x028                                                         */
  uint32_t      RESERVED2;        /*!< Reserved, 0x02C                                                         */
  __IO uint32_t SQR1;             /*!< ADC regular sequence register 1,                   Address offset: 0x30 */
  __IO uint32_t SQR2;             /*!< ADC regular sequence register 2,                   Address offset: 0x34 */
  __IO uint32_t SQR3;             /*!< ADC regular sequence register 3,                   Address offset: 0x38 */
  __IO uint32_t SQR4;             /*!< ADC regular sequence register 4,                   Address offset: 0x3C */
  __IO uint32_t DR;               /*!< ADC regular data register,                         Address offset: 0x40 */
  uint32_t      RESERVED3;        /*!< Reserved, 0x044                                                         */
  uint32_t      RESERVED4;        /*!< Reserved, 0x048                                                         */
  __IO uint32_t JSQR;             /*!< ADC injected sequence register,                    Address offset: 0x4C */
  uint32_t      RESERVED5[4];     /*!< Reserved, 0x050 - 0x05C                                                 */
  __IO uint32_t OFR1;             /*!< ADC offset register 1,                             Address offset: 0x60 */
  __IO uint32_t OFR2;             /*!< ADC offset register 2,                             Address offset: 0x64 */
  __IO uint32_t OFR3;             /*!< ADC offset register 3,                             Address offset: 0x68 */
  __IO uint32_t OFR4;             /*!< ADC offset register 4,                             Address offset: 0x6C */
  uint32_t      RESERVED6[4];     /*!< Reserved, 0x070 - 0x07C                                                 */
  __IO uint32_t JDR1;             /*!< ADC injected data register 1,                      Address offset: 0x80 */
  __IO uint32_t JDR2;             /*!< ADC injected data register 2,                      Address offset: 0x84 */
  __IO uint32_t JDR3;             /*!< ADC injected data register 3,                      Address offset: 0x88 */
  __IO uint32_t JDR4;             /*!< ADC injected data register 4,                      Address offset: 0x8C */
  uint32_t      RESERVED7[4];     /*!< Reserved, 0x090 - 0x09C                                                 */
  __IO uint32_t AWD2CR;           /*!< ADC  Analog Watchdog 2 Configuration Register,     Address offset: 0xA0 */
  __IO uint32_t AWD3CR;           /*!< ADC  Analog Watchdog 3 Configuration Register,     Address offset: 0xA4 */
  uint32_t      RESERVED8;        /*!< Reserved, 0x0A8                                                         */
  uint32_t      RESERVED9;        /*!< Reserved, 0x0AC                                                         */
  __IO uint32_t LTR2;             /*!< ADC watchdog Lower threshold register 2,           Address offset: 0xB0 */
  __IO uint32_t HTR2;             /*!< ADC watchdog Higher threshold register 2,          Address offset: 0xB4 */
  __IO uint32_t LTR3;             /*!< ADC watchdog Lower threshold register 3,           Address offset: 0xB8 */
  __IO uint32_t HTR3;             /*!< ADC watchdog Higher threshold register 3,          Address offset: 0xBC */
  __IO uint32_t DIFSEL;           /*!< ADC  Differential Mode Selection Register,         Address offset: 0xC0 */
  __IO uint32_t CALFACT;          /*!< ADC  Calibration Factors,                          Address offset: 0xC4 */
  __IO uint32_t CALFACT2;         /*!< ADC  Linearity Calibration Factors,                Address offset: 0xC8 */
  uint32_t      RESERVED10;       /*!< Reserved,                                                         0x0CC */
  __IO uint32_t OR;               /*!< ADC  Option Register,                             Address offset: 0x0D0 */
  uint32_t  RESERVED11[200];       /*!< Reserved,                                                0x0D4 - 0x3F0 */
  __IO uint32_t VERR;             /*!< ADC version register,                             Address offset: 0x3F4 */
  __IO uint32_t IPIDR;            /*!< ADC ID register,                                  Address offset: 0x3F8 */
  __IO uint32_t SIDR;             /*!< ADC Size ID register,                             Address offset: 0x3FC */
} ADC_TypeDef;


typedef struct
{
  __IO uint32_t CSR; /*!< ADC Common status register, Address offset: ADC1/3 base address + 0x300 */
  uint32_t RESERVED; /*!< Reserved, ADC1/3 base address + 0x304 */
  __IO uint32_t CCR; /*!< ADC common control register, Address offset: ADC1/3 base address + 0x308 */
  __IO uint32_t CDR; /*!< ADC common regular data register for dual Address offset: ADC1/3 base address + 0x30C */
  __IO uint32_t CDR2; /*!< ADC common regular data register for 32-bit dual mode Address offset: ADC1/3 base address + 0x310 */
} ADC_Common_TypeDef;

/**
  * @brief FD Controller Area Network
  */

typedef struct
{
  __IO uint32_t CREL;         /*!< FDCAN Core Release register,                                     Address offset: 0x000 */
  __IO uint32_t ENDN;         /*!< FDCAN Endian register,                                           Address offset: 0x004 */
  __IO uint32_t RESERVED1;    /*!< Reserved,                                                                        0x008 */
  __IO uint32_t DBTP;         /*!< FDCAN Data Bit Timing & Prescaler register,                      Address offset: 0x00C */
  __IO uint32_t TEST;         /*!< FDCAN Test register,                                             Address offset: 0x010 */
  __IO uint32_t RWD;          /*!< FDCAN RAM Watchdog register,                                     Address offset: 0x014 */
  __IO uint32_t CCCR;         /*!< FDCAN CC Control register,                                       Address offset: 0x018 */
  __IO uint32_t NBTP;         /*!< FDCAN Nominal Bit Timing & Prescaler register,                   Address offset: 0x01C */
  __IO uint32_t TSCC;         /*!< FDCAN Timestamp Counter Configuration register,                  Address offset: 0x020 */
  __IO uint32_t TSCV;         /*!< FDCAN Timestamp Counter Value register,                          Address offset: 0x024 */
  __IO uint32_t TOCC;         /*!< FDCAN Timeout Counter Configuration register,                    Address offset: 0x028 */
  __IO uint32_t TOCV;         /*!< FDCAN Timeout Counter Value register,                            Address offset: 0x02C */
  __IO uint32_t RESERVED2[4]; /*!< Reserved,                                                                0x030 - 0x03C */
  __IO uint32_t ECR;          /*!< FDCAN Error Counter register,                                    Address offset: 0x040 */
  __IO uint32_t PSR;          /*!< FDCAN Protocol Status register,                                  Address offset: 0x044 */
  __IO uint32_t TDCR;         /*!< FDCAN Transmitter Delay Compensation register,                   Address offset: 0x048 */
  __IO uint32_t RESERVED3;    /*!< Reserved,                                                                        0x04C */
  __IO uint32_t IR;           /*!< FDCAN Interrupt register,                                        Address offset: 0x050 */
  __IO uint32_t IE;           /*!< FDCAN Interrupt Enable register,                                 Address offset: 0x054 */
  __IO uint32_t ILS;          /*!< FDCAN Interrupt Line Select register,                            Address offset: 0x058 */
  __IO uint32_t ILE;          /*!< FDCAN Interrupt Line Enable register,                            Address offset: 0x05C */
  __IO uint32_t RESERVED4[8]; /*!< Reserved,                                                                0x060 - 0x07C */
  __IO uint32_t GFC;          /*!< FDCAN Global Filter Configuration register,                      Address offset: 0x080 */
  __IO uint32_t SIDFC;        /*!< FDCAN Standard ID Filter Configuration register,                 Address offset: 0x084 */
  __IO uint32_t XIDFC;        /*!< FDCAN Extended ID Filter Configuration register,                 Address offset: 0x088 */
  __IO uint32_t RESERVED5;    /*!< Reserved,                                                                        0x08C */
  __IO uint32_t XIDAM;        /*!< FDCAN Extended ID AND Mask register,                             Address offset: 0x090 */
  __IO uint32_t HPMS;         /*!< FDCAN High Priority Message Status register,                     Address offset: 0x094 */
  __IO uint32_t NDAT1;        /*!< FDCAN New Data 1 register,                                       Address offset: 0x098 */
  __IO uint32_t NDAT2;        /*!< FDCAN New Data 2 register,                                       Address offset: 0x09C */
  __IO uint32_t RXF0C;        /*!< FDCAN Rx FIFO 0 Configuration register,                          Address offset: 0x0A0 */
  __IO uint32_t RXF0S;        /*!< FDCAN Rx FIFO 0 Status register,                                 Address offset: 0x0A4 */
  __IO uint32_t RXF0A;        /*!< FDCAN Rx FIFO 0 Acknowledge register,                            Address offset: 0x0A8 */
  __IO uint32_t RXBC;         /*!< FDCAN Rx Buffer Configuration register,                          Address offset: 0x0AC */
  __IO uint32_t RXF1C;        /*!< FDCAN Rx FIFO 1 Configuration register,                          Address offset: 0x0B0 */
  __IO uint32_t RXF1S;        /*!< FDCAN Rx FIFO 1 Status register,                                 Address offset: 0x0B4 */
  __IO uint32_t RXF1A;        /*!< FDCAN Rx FIFO 1 Acknowledge register,                            Address offset: 0x0B8 */
  __IO uint32_t RXESC;        /*!< FDCAN Rx Buffer/FIFO Element Size Configuration register,        Address offset: 0x0BC */
  __IO uint32_t TXBC;         /*!< FDCAN Tx Buffer Configuration register,                          Address offset: 0x0C0 */
  __IO uint32_t TXFQS;        /*!< FDCAN Tx FIFO/Queue Status register,                             Address offset: 0x0C4 */
  __IO uint32_t TXESC;        /*!< FDCAN Tx Buffer Element Size Configuration register,             Address offset: 0x0C8 */
  __IO uint32_t TXBRP;        /*!< FDCAN Tx Buffer Request Pending register,                        Address offset: 0x0CC */
  __IO uint32_t TXBAR;        /*!< FDCAN Tx Buffer Add Request register,                            Address offset: 0x0D0 */
  __IO uint32_t TXBCR;        /*!< FDCAN Tx Buffer Cancellation Request register,                   Address offset: 0x0D4 */
  __IO uint32_t TXBTO;        /*!< FDCAN Tx Buffer Transmission Occurred register,                  Address offset: 0x0D8 */
  __IO uint32_t TXBCF;        /*!< FDCAN Tx Buffer Cancellation Finished register,                  Address offset: 0x0DC */
  __IO uint32_t TXBTIE;       /*!< FDCAN Tx Buffer Transmission Interrupt Enable register,          Address offset: 0x0E0 */
  __IO uint32_t TXBCIE;       /*!< FDCAN Tx Buffer Cancellation Finished Interrupt Enable register, Address offset: 0x0E4 */
  __IO uint32_t RESERVED6[2]; /*!< Reserved,                                                                0x0E8 - 0x0EC */
  __IO uint32_t TXEFC;        /*!< FDCAN Tx Event FIFO Configuration register,                      Address offset: 0x0F0 */
  __IO uint32_t TXEFS;        /*!< FDCAN Tx Event FIFO Status register,                             Address offset: 0x0F4 */
  __IO uint32_t TXEFA;        /*!< FDCAN Tx Event FIFO Acknowledge register,                        Address offset: 0x0F8 */
  __IO uint32_t RESERVED7;    /*!< Reserved,                                                                        0x0FC */
} FDCAN_GlobalTypeDef;

/**
  * @brief TTFD Controller Area Network
  */

typedef struct
{
  __IO uint32_t TTTMC;          /*!< TT Trigger Memory Configuration register,    Address offset: 0x100 */
  __IO uint32_t TTRMC;          /*!< TT Reference Message Configuration register, Address offset: 0x104 */
  __IO uint32_t TTOCF;          /*!< TT Operation Configuration register,         Address offset: 0x108 */
  __IO uint32_t TTMLM;          /*!< TT Matrix Limits register,                   Address offset: 0x10C */
  __IO uint32_t TURCF;          /*!< TUR Configuration register,                  Address offset: 0x110 */
  __IO uint32_t TTOCN;          /*!< TT Operation Control register,               Address offset: 0x114 */
  __IO uint32_t TTGTP;          /*!< TT Global Time Preset register,              Address offset: 0x118 */
  __IO uint32_t TTTMK;          /*!< TT Time Mark register,                       Address offset: 0x11C */
  __IO uint32_t TTIR;           /*!< TT Interrupt register,                       Address offset: 0x120 */
  __IO uint32_t TTIE;           /*!< TT Interrupt Enable register,                Address offset: 0x124 */
  __IO uint32_t TTILS;          /*!< TT Interrupt Line Select register,           Address offset: 0x128 */
  __IO uint32_t TTOST;          /*!< TT Operation Status register,                Address offset: 0x12C */
  __IO uint32_t TURNA;          /*!< TT TUR Numerator Actual register,            Address offset: 0x130 */
  __IO uint32_t TTLGT;          /*!< TT Local and Global Time register,           Address offset: 0x134 */
  __IO uint32_t TTCTC;          /*!< TT Cycle Time and Count register,            Address offset: 0x138 */
  __IO uint32_t TTCPT;          /*!< TT Capture Time register,                    Address offset: 0x13C */
  __IO uint32_t TTCSM;          /*!< TT Cycle Sync Mark register,                 Address offset: 0x140 */
  __IO uint32_t RESERVED1[111]; /*!< Reserved,                                            0x144 - 0x2FC */
  __IO uint32_t TTTS;           /*!< TT Trigger Select register,                  Address offset: 0x300 */
} TTCAN_TypeDef;

/**
  * @brief FD Controller Area Network
  */

typedef struct
{
  __IO uint32_t CREL;  /*!< Clock Calibration Unit Core Release register, Address offset: 0x00 */
  __IO uint32_t CCFG;  /*!< Calibration Configuration register,           Address offset: 0x04 */
  __IO uint32_t CSTAT; /*!< Calibration Status register,                  Address offset: 0x08 */
  __IO uint32_t CWD;   /*!< Calibration Watchdog register,                Address offset: 0x0C */
  __IO uint32_t IR;    /*!< CCU Interrupt register,                       Address offset: 0x10 */
  __IO uint32_t IE;    /*!< CCU Interrupt Enable register,                Address offset: 0x14 */
} FDCAN_ClockCalibrationUnit_TypeDef;

/**
  * @brief Consumer Electronics Control
  */

typedef struct
{
  __IO uint32_t CR;           /*!< CEC control register,               Address offset: 0x000 */
  __IO uint32_t CFGR;         /*!< CEC configuration register,         Address offset: 0x004 */
  __IO uint32_t TXDR;         /*!< CEC Tx data register ,              Address offset: 0x008 */
  __IO uint32_t RXDR;         /*!< CEC Rx Data Register,               Address offset: 0x00C */
  __IO uint32_t ISR;          /*!< CEC Interrupt and Status Register,  Address offset: 0x010 */
  __IO uint32_t IER;          /*!< CEC interrupt enable register,      Address offset: 0x014 */
  uint32_t  RESERVED3[247];   /*!< Reserved,                                   0x018 - 0x3F0 */
  __IO uint32_t VERR;         /*!< CEC version register,               Address offset: 0x3F4 */
  __IO uint32_t IPIDR;        /*!< CEC ID register,                    Address offset: 0x3F8 */
  __IO uint32_t SIDR;         /*!< CEC Size ID register,               Address offset: 0x3FC */
}CEC_TypeDef;

/**
  * @brief CRC calculation unit
  */

typedef struct
{
  __IO uint32_t DR;          /*!< CRC Data register,                           Address offset: 0x000 */
  __IO uint32_t IDR;         /*!< CRC Independent data register,               Address offset: 0x004 */
  __IO uint32_t CR;          /*!< CRC Control register,                        Address offset: 0x008 */
  uint32_t      RESERVED2;   /*!< Reserved,                                                    0x00C */
  __IO uint32_t INIT;        /*!< Initial CRC value register,                  Address offset: 0x010 */
  __IO uint32_t POL;         /*!< CRC polynomial register,                     Address offset: 0x014 */
  uint32_t      RESERVED3[247];   /*!< Reserved,                                       0x018 - 0x3F0 */
  __IO uint32_t VERR;        /*!< CRC version register,                        Address offset: 0x3F4 */
  __IO uint32_t IPIDR;       /*!< CRC ID register,                             Address offset: 0x3F8 */
  __IO uint32_t SIDR;        /*!< CRC Size ID register,                        Address offset: 0x3FC */
} CRC_TypeDef;


/**
  * @brief Clock Recovery System
  */
typedef struct
{
  __IO uint32_t CR;            /*!< CRS ccontrol register,              Address offset: 0x00 */
  __IO uint32_t CFGR;          /*!< CRS configuration register,         Address offset: 0x04 */
  __IO uint32_t ISR;           /*!< CRS interrupt and status register,  Address offset: 0x08 */
  __IO uint32_t ICR;           /*!< CRS interrupt flag clear register,  Address offset: 0x0C */
} CRS_TypeDef;


/**
  * @brief Digital to Analog Converter
  */

typedef struct
{
  __IO uint32_t CR;       /*!< DAC control register,                                    Address offset: 0x00 */
  __IO uint32_t SWTRIGR;  /*!< DAC software trigger register,                           Address offset: 0x04 */
  __IO uint32_t DHR12R1;  /*!< DAC channel1 12-bit right-aligned data holding register, Address offset: 0x08 */
  __IO uint32_t DHR12L1;  /*!< DAC channel1 12-bit left aligned data holding register,  Address offset: 0x0C */
  __IO uint32_t DHR8R1;   /*!< DAC channel1 8-bit right aligned data holding register,  Address offset: 0x10 */
  __IO uint32_t DHR12R2;  /*!< DAC channel2 12-bit right aligned data holding register, Address offset: 0x14 */
  __IO uint32_t DHR12L2;  /*!< DAC channel2 12-bit left aligned data holding register,  Address offset: 0x18 */
  __IO uint32_t DHR8R2;   /*!< DAC channel2 8-bit right-aligned data holding register,  Address offset: 0x1C */
  __IO uint32_t DHR12RD;  /*!< Dual DAC 12-bit right-aligned data holding register,     Address offset: 0x20 */
  __IO uint32_t DHR12LD;  /*!< DUAL DAC 12-bit left aligned data holding register,      Address offset: 0x24 */
  __IO uint32_t DHR8RD;   /*!< DUAL DAC 8-bit right aligned data holding register,      Address offset: 0x28 */
  __IO uint32_t DOR1;     /*!< DAC channel1 data output register,                       Address offset: 0x2C */
  __IO uint32_t DOR2;     /*!< DAC channel2 data output register,                       Address offset: 0x30 */
  __IO uint32_t SR;       /*!< DAC status register,                                     Address offset: 0x34 */
  __IO uint32_t CCR;      /*!< DAC calibration control register,                        Address offset: 0x38 */
  __IO uint32_t MCR;      /*!< DAC mode control register,                               Address offset: 0x3C */
  __IO uint32_t SHSR1;    /*!< DAC Sample and Hold sample time register 1,              Address offset: 0x40 */
  __IO uint32_t SHSR2;    /*!< DAC Sample and Hold sample time register 2,              Address offset: 0x44 */
  __IO uint32_t SHHR;     /*!< DAC Sample and Hold hold time register,                  Address offset: 0x48 */
  __IO uint32_t SHRR;     /*!< DAC Sample and Hold refresh time register,               Address offset: 0x4C */
  uint32_t    RESERVED0[232];  /*!< Reserved,                                           Address offset: 0x50 - 0x3EC */
  __IO uint32_t HWCFGR0;  /*!< DAC x IP hardware configuration register,                Address offset: 0x3F0 */
  __IO uint32_t VERR;      /*!< DAC version register,                                    Address offset: 0x3F4 */
  __IO uint32_t IPIDR;       /*!< DAC ID register,                                      Address offset: 0x3F8 */
  __IO uint32_t SIDR;        /*!< DAC magic ID register,                                Address offset: 0x3FC */
} DAC_TypeDef;

/*
 * @brief DDRCTRL block description (DDRCTRL)
 */
typedef struct
{
  __IO uint32_t MSTR;            /*!< DDRCTRL master register 0                            Address offset: 0x000 */
  __IO uint32_t STAT;            /*!< DDRCTRL operating mode status register               Address offset: 0x004 */
       uint32_t RESERVED0[2];    /*!< Reserved                                             Address offset: 0x008-0x00C */
  __IO uint32_t MRCTRL0;         /*!< DDRCTRL mode register read/write control register 0  Address offset: 0x010 */
  __IO uint32_t MRCTRL1;         /*!< DDRCTRL mode register read/write control register 1  Address offset: 0x014 */
  __IO uint32_t MRSTAT;          /*!< DDRCTRL mode register read/write status register     Address offset: 0x018 */
       uint32_t RESERVED1;       /*!< Reserved                                             Address offset: 0x01C */
  __IO uint32_t DERATEEN;        /*!< DDRCTRL temperature derate enable register           Address offset: 0x020 */
  __IO uint32_t DERATEINT;       /*!< DDRCTRL temperature derate interval register         Address offset: 0x024 */
       uint32_t RESERVED2[2];    /*!< Reserved                                             Address offset: 0x028-0x02C */
  __IO uint32_t PWRCTL;          /*!< DDRCTRL low power control register                   Address offset: 0x030 */
  __IO uint32_t PWRTMG;          /*!< DDRCTRL low power timing register                    Address offset: 0x034 */
  __IO uint32_t HWLPCTL;         /*!< DDRCTRL hardware low power control register          Address offset: 0x038 */
       uint32_t RESERVED3[5];    /*!< Reserved                                             Address offset: 0x03C-0x04C */
  __IO uint32_t RFSHCTL0;        /*!< DDRCTRL refresh control register 0                   Address offset: 0x050 */
       uint32_t RESERVED4[3];    /*!< Reserved                                             Address offset: 0x054-0x05C */
  __IO uint32_t RFSHCTL3;        /*!< DDRCTRL refresh control register 3                   Address offset: 0x060 */
  __IO uint32_t RFSHTMG;         /*!< DDRCTRL refresh timing register                      Address offset: 0x064 */
       uint32_t RESERVED5[22];   /*!< Reserved                                             Address offset: 0x068-0x0BC */
  __IO uint32_t CRCPARCTL0;      /*!< DDRCTRL CRC parity control register 0                Address offset: 0x0C0 */
       uint32_t RESERVED6[2];    /*!< Reserved                                             Address offset: 0x0C4-0x0C8 */
  __IO uint32_t CRCPARSTAT;      /*!< DDRCTRL CRC parity status register                   Address offset: 0x0CC */
  __IO uint32_t INIT0;           /*!< DDRCTRL SDRAM initialization register 0              Address offset: 0x0D0 */
  __IO uint32_t INIT1;           /*!< DDRCTRL SDRAM initialization register 1              Address offset: 0x0D4 */
  __IO uint32_t INIT2;           /*!< DDRCTRL SDRAM initialization register 2              Address offset: 0x0D8 */
  __IO uint32_t INIT3;           /*!< DDRCTRL SDRAM initialization register 3              Address offset: 0x0DC */
  __IO uint32_t INIT4;           /*!< DDRCTRL SDRAM initialization register 4              Address offset: 0x0E0 */
  __IO uint32_t INIT5;           /*!< DDRCTRL SDRAM initialization register 5              Address offset: 0x0E4 */
       uint32_t RESERVED7[2];    /*!< Reserved                                             Address offset: 0x0E8-0x0EC */
  __IO uint32_t DIMMCTL;         /*!< DDRCTRL DIMM control register                        Address offset: 0x0F0 */
       uint32_t RESERVED8[3];    /*!< Reserved                                             Address offset: 0x0F4-0x0FC */
  __IO uint32_t DRAMTMG0;        /*!< DDRCTRL SDRAM timing register 0                      Address offset: 0x100 */
  __IO uint32_t DRAMTMG1;        /*!< DDRCTRL SDRAM timing register 1                      Address offset: 0x104 */
  __IO uint32_t DRAMTMG2;        /*!< DDRCTRL SDRAM timing register 2                      Address offset: 0x108 */
  __IO uint32_t DRAMTMG3;        /*!< DDRCTRL SDRAM timing register 3                      Address offset: 0x10C */
  __IO uint32_t DRAMTMG4;        /*!< DDRCTRL SDRAM timing register 4                      Address offset: 0x110 */
  __IO uint32_t DRAMTMG5;        /*!< DDRCTRL SDRAM timing register 5                      Address offset: 0x114 */
  __IO uint32_t DRAMTMG6;        /*!< DDRCTRL SDRAM timing register 6                      Address offset: 0x118 */
  __IO uint32_t DRAMTMG7;        /*!< DDRCTRL SDRAM timing register 7                      Address offset: 0x11C */
  __IO uint32_t DRAMTMG8;        /*!< DDRCTRL SDRAM timing register 8                      Address offset: 0x120 */
       uint32_t RESERVED9[5];    /*!< Reserved                                             Address offset: 0x124-0x134 */
  __IO uint32_t DRAMTMG14;       /*!< DDRCTRL SDRAM timing register 14                     Address offset: 0x138 */
  __IO uint32_t DRAMTMG15;       /*!< DDRCTRL SDRAM timing register 15                     Address offset: 0x13C */
       uint32_t RESERVED10[16];  /*!< Reserved                                             Address offset: 0x140-0x17C */
  __IO uint32_t ZQCTL0;          /*!< DDRCTRL ZQ control register 0                        Address offset: 0x180 */
  __IO uint32_t ZQCTL1;          /*!< DDRCTRL ZQ control register 1                        Address offset: 0x184 */
  __IO uint32_t ZQCTL2;          /*!< DDRCTRL ZQ control register 2                        Address offset: 0x188 */
  __IO uint32_t ZQSTAT;          /*!< DDRCTRL ZQ status register                           Address offset: 0x18C */
  __IO uint32_t DFITMG0;         /*!< DDRCTRL DFI timing register 0                        Address offset: 0x190 */
  __IO uint32_t DFITMG1;         /*!< DDRCTRL DFI timing register 1                        Address offset: 0x194 */
  __IO uint32_t DFILPCFG0;       /*!< DDRCTRL low power configuration register 0           Address offset: 0x198 */
       uint32_t RESERVED11;      /*!< Reserved                                             Address offset: 0x19C */
  __IO uint32_t DFIUPD0;         /*!< DDRCTRL DFI update register 0                        Address offset: 0x1A0 */
  __IO uint32_t DFIUPD1;         /*!< DDRCTRL DFI update register 1                        Address offset: 0x1A4 */
  __IO uint32_t DFIUPD2;         /*!< DDRCTRL DFI update register 2                        Address offset: 0x1A8 */
       uint32_t RESERVED12;      /*!< Reserved                                             Address offset: 0x1AC */
  __IO uint32_t DFIMISC;         /*!< DDRCTRL DFI miscellaneous control register           Address offset: 0x1B0 */
       uint32_t RESERVED13[2];   /*!< Reserved                                             Address offset: 0x1B4-0x1B8 */
  __IO uint32_t DFISTAT;         /*!< DDRCTRL DFI status register                          Address offset: 0x1BC */
       uint32_t RESERVED14;      /*!< Reserved                                             Address offset: 0x1C0 */
  __IO uint32_t DFIPHYMSTR;      /*!< DDRCTRL DFI PHY master register                      Address offset: 0x1C4 */
       uint32_t RESERVED15[15];  /*!< Reserved                                             Address offset: 0x1C8-0x200 */
  __IO uint32_t ADDRMAP1;        /*!< DDRCTRL address map register 1                       Address offset: 0x204 */
  __IO uint32_t ADDRMAP2;        /*!< DDRCTRL address map register 2                       Address offset: 0x208 */
  __IO uint32_t ADDRMAP3;        /*!< DDRCTRL address map register 3                       Address offset: 0x20C */
  __IO uint32_t ADDRMAP4;        /*!< DDRCTRL address map register 4                       Address offset: 0x210 */
  __IO uint32_t ADDRMAP5;        /*!< DDRCTRL address map register 5                       Address offset: 0x214 */
  __IO uint32_t ADDRMAP6;        /*!< DDRCTRL address register 6                           Address offset: 0x218 */
       uint32_t RESERVED16[2];   /*!< Reserved                                             Address offset: 0x21C-0x220 */
  __IO uint32_t ADDRMAP9;        /*!< DDRCTRL address map register 9                       Address offset: 0x224 */
  __IO uint32_t ADDRMAP10;       /*!< DDRCTRL address map register 10                      Address offset: 0x228 */
  __IO uint32_t ADDRMAP11;       /*!< DDRCTRL address map register 11                      Address offset: 0x22C */
       uint32_t RESERVED17[4];   /*!< Reserved                                             Address offset: 0x230-0x23C */
  __IO uint32_t ODTCFG;          /*!< DDRCTRL ODT configuration register                   Address offset: 0x240 */
  __IO uint32_t ODTMAP;          /*!< DDRCTRL ODT/Rank map register                        Address offset: 0x244 */
       uint32_t RESERVED18[2];   /*!< Reserved                                             Address offset: 0x248-0x24C */
  __IO uint32_t SCHED;           /*!< DDRCTRL scheduler control register                   Address offset: 0x250 */
  __IO uint32_t SCHED1;          /*!< DDRCTRL scheduler control register 1                 Address offset: 0x254 */
       uint32_t RESERVED19;      /*!< Reserved                                             Address offset: 0x258 */
  __IO uint32_t PERFHPR1;        /*!< DDRCTRL high priority read CAM register 1            Address offset: 0x25C */
       uint32_t RESERVED20;      /*!< Reserved                                             Address offset: 0x260 */
  __IO uint32_t PERFLPR1;        /*!< DDRCTRL low priority read CAM register 1             Address offset: 0x264 */
       uint32_t RESERVED21;      /*!< Reserved                                             Address offset: 0x268 */
  __IO uint32_t PERFWR1;         /*!< DDRCTRL write CAM register 1                         Address offset: 0x26C */
       uint32_t RESERVED22[36];  /*!< Reserved                                             Address offset: 0x270-0x2FC */
  __IO uint32_t DBG0;            /*!< DDRCTRL debug register 0                             Address offset: 0x300 */
  __IO uint32_t DBG1;            /*!< DDRCTRL debug register 1                             Address offset: 0x304 */
  __IO uint32_t DBGCAM;          /*!< DDRCTRL CAM debug register                           Address offset: 0x308 */
  __IO uint32_t DBGCMD;          /*!< DDRCTRL command debug register                       Address offset: 0x30C */
  __IO uint32_t DBGSTAT;         /*!< DDRCTRL status debug register                        Address offset: 0x310 */
       uint32_t RESERVED23[3];   /*!< Reserved                                             Address offset: 0x314-0x31C */
  __IO uint32_t SWCTL;           /*!< DDRCTRL software register programming control enable Address offset: 0x320 */
  __IO uint32_t SWSTAT;          /*!< DDRCTRL software register programming control status Address offset: 0x324 */
       uint32_t RESERVED24[17];  /*!< Reserved                                             Address offset: 0x328-0x368 */
  __IO uint32_t POISONCFG;       /*!< DDRCTRL AXI Poison configuration register            Address offset: 0x36C */
  __IO uint32_t POISONSTAT;      /*!< DDRCTRL AXI Poison status register                   Address offset: 0x370 */
       uint32_t RESERVED25[34];  /*!< Reserved                                             Address offset: 0x374-0x3F8 */
  __IO uint32_t PSTAT;           /*!< DDRCTRL port status register                         Address offset: 0x3FC */
  __IO uint32_t PCCFG;           /*!< DDRCTRL port common configuration register           Address offset: 0x400 */
  __IO uint32_t PCFGR_0;         /*!< DDRCTRL port 0 configuration read register           Address offset: 0x404 */
  __IO uint32_t PCFGW_0;         /*!< DDRCTRL port 0 configuration write register          Address offset: 0x408 */
       uint32_t RESERVED26[33];  /*!< Reserved                                             Address offset: 0x40C-0x48C */
  __IO uint32_t PCTRL_0;         /*!< DDRCTRL port 0 control register                      Address offset: 0x490 */
  __IO uint32_t PCFGQOS0_0;      /*!< DDRCTRL port 0 read Q0S configuration register 0     Address offset: 0x494 */
  __IO uint32_t PCFGQOS1_0;      /*!< DDRCTRL port 0 read Q0S configuration register 1     Address offset: 0x498 */
  __IO uint32_t PCFGWQOS0_0;     /*!< DDRCTRL port 0 write Q0S configuration register 0    Address offset: 0x49C */
  __IO uint32_t PCFGWQOS1_0;     /*!< DDRCTRL port 0 write Q0S configuration register 1    Address offset: 0x4A0 */
       uint32_t RESERVED27[4];   /*!< Reserved                                             Address offset: 0x4A4-0x4B0 */
  __IO uint32_t PCFGR_1;         /*!< DDRCTRL port 1 configuration read register           Address offset: 0x4B4 */
  __IO uint32_t PCFGW_1;         /*!< DDRCTRL port 1 configuration write register          Address offset: 0x4B8 */
       uint32_t RESERVED28[33];  /*!< Reserved                                             Address offset: 0x4BC-0x53C */
  __IO uint32_t PCTRL_1;         /*!< DDRCTRL port 1 control register                      Address offset: 0x540 */
  __IO uint32_t PCFGQOS0_1;      /*!< DDRCTRL port 1 read Q0S configuration register 0     Address offset: 0x544 */
  __IO uint32_t PCFGQOS1_1;      /*!< DDRCTRL port 1 read Q0S configuration register 1     Address offset: 0x548 */
  __IO uint32_t PCFGWQOS0_1;     /*!< DDRCTRL port 1 write Q0S configuration register 0    Address offset: 0x54C */
  __IO uint32_t PCFGWQOS1_1;     /*!< DDRCTRL port 1 write Q0S configuration register 1    Address offset: 0x550 */
} DDRCTRL_TypeDef;

/*
 * @brief DDRPERFM block description (DDRPERFM)
 */
typedef struct
{
  __IO uint32_t CTL;             /*!< DDRPERFM control register                Address offset: 0x000 */
  __IO uint32_t CFG;             /*!< DDRPERFM configurationl register         Address offset: 0x004 */
  __IO uint32_t STATUS;          /*!< DDRPERFM status register                 Address offset: 0x008 */
  __IO uint32_t CCR;             /*!< DDRPERFM counter clear register          Address offset: 0x00C */
  __IO uint32_t IER;             /*!< DDRPERFM interrupt enable register       Address offset: 0x010 */
  __IO uint32_t ISR;             /*!< DDRPERFM interrupt status register       Address offset: 0x014 */
  __IO uint32_t ICR;             /*!< DDRPERFM interrupt clear register        Address offset: 0x018 */
       uint32_t RESERVED0;       /*!< Reserved                                 Address offset: 0x01C */
  __IO uint32_t TCNT;            /*!< DDRPERFM time counter register           Address offset: 0x020 */
       uint32_t RESERVED1[3];    /*!< Reserved                                 Address offset: 0x024-0x02C */
  __IO uint32_t CNT0;            /*!< DDRPERFM event counter 0 register        Address offset: 0x030 */
       uint32_t RESERVED2;       /*!< Reserved                                 Address offset: 0x034 */
  __IO uint32_t CNT1;            /*!< DDRPERFM event counter 1 register        Address offset: 0x038 */
       uint32_t RESERVED3;       /*!< Reserved                                 Address offset: 0x03C */
  __IO uint32_t CNT2;            /*!< DDRPERFM event counter 2 register        Address offset: 0x040 */
       uint32_t RESERVED4;       /*!< Reserved                                 Address offset: 0x044 */
  __IO uint32_t CNT3;            /*!< DDRPERFM event counter 3 register        Address offset: 0x048 */
       uint32_t RESERVED5[233];  /*!< Reserved                                 Address offset: 0x04C-0x3EC */
  __IO uint32_t HWCFG;           /*!< DDRPERFM hardware configuration register Address offset: 0x3F0 */
  __IO uint32_t VER;             /*!< DDRPERFM version register                Address offset: 0x3F4 */
  __IO uint32_t ID;              /*!< DDRPERFM ID register                     Address offset: 0x3F8 */
  __IO uint32_t SID;             /*!< DDRPERFM magic ID register               Address offset: 0x3FC */
} DDRPERFM_TypeDef;

/*
 * @brief DDRPHYC block description (DDRPHYC)
 */
typedef struct
{
  __IO uint32_t RIDR;           /*!< DDRPHYC revision ID register         Address offset: 0x000 */
  __IO uint32_t PIR;            /*!< DDRPHYC PHY initialization register  Address offset: 0x004 */
  __IO uint32_t PGCR;           /*!< DDRPHYC PHY global control register  Address offset: 0x008 */
  __IO uint32_t PGSR;           /*!< DDRPHYC PHY global status register   Address offset: 0x00C */
  __IO uint32_t DLLGCR;         /*!< DDRPHYC DDR global control register  Address offset: 0x010 */
  __IO uint32_t ACDLLCR;        /*!< DDRPHYC AC DLL control register      Address offset: 0x014 */
  __IO uint32_t PTR0;           /*!< DDRPHYC PT register 0                Address offset: 0x018 */
  __IO uint32_t PTR1;           /*!< DDRPHYC PT register 1                Address offset: 0x01C */
  __IO uint32_t PTR2;           /*!< DDRPHYC PT register 2                Address offset: 0x020 */
  __IO uint32_t ACIOCR;         /*!< DDRPHYC ACIOC register               Address offset: 0x024 */
  __IO uint32_t DXCCR;          /*!< DDRPHYC DXCC register                Address offset: 0x028 */
  __IO uint32_t DSGCR;          /*!< DDRPHYC DSGC register                Address offset: 0x02C */
  __IO uint32_t DCR;            /*!< DDRPHYC DC register                  Address offset: 0x030 */
  __IO uint32_t DTPR0;          /*!< DDRPHYC DTP register 0               Address offset: 0x034 */
  __IO uint32_t DTPR1;          /*!< DDRPHYC DTP register 1               Address offset: 0x038 */
  __IO uint32_t DTPR2;          /*!< DDRPHYC DTP register 2               Address offset: 0x03C */
  __IO uint32_t DDR3_MR0;       /*!< DDRPHYC MR0 register for DDR3        Address offset: 0x040 */
  __IO uint32_t DDR3_MR1;       /*!< DDRPHYC MR1 register for DDR3        Address offset: 0x044 */
  __IO uint32_t DDR3_MR2;       /*!< DDRPHYC MR2 register for DDR3        Address offset: 0x048 */
  __IO uint32_t DDR3_MR3;       /*!< DDRPHYC MR3 register for DDR3        Address offset: 0x04C */
  __IO uint32_t ODTCR;          /*!< DDRPHYC ODTC register                Address offset: 0x050 */
  __IO uint32_t DTAR;           /*!< DDRPHYC DTA register                 Address offset: 0x054 */
  __IO uint32_t DTDR0;          /*!< DDRPHYC DTD register 0               Address offset: 0x058 */
  __IO uint32_t DTDR1;          /*!< DDRPHYC DTD register 1               Address offset: 0x05C */
       uint32_t RESERVED0[70];  /*!< Reserved                             Address offset: 0x060-0x174 */
  __IO uint32_t GPR0;           /*!< DDRPHYC general purpose register 0   Address offset: 0x178 */
  __IO uint32_t GPR1;           /*!< DDRPHYC general purpose register 1   Address offset: 0x17C */
  __IO uint32_t ZQ0CR0;         /*!< DDRPHYC ZQ0C register 0              Address offset: 0x180 */
  __IO uint32_t ZQ0CR1;         /*!< DDRPHYC ZQ0CR1 register              Address offset: 0x184 */
  __IO uint32_t ZQ0SR0;         /*!< DDRPHYC ZQ0S register 0              Address offset: 0x188 */
  __IO uint32_t ZQ0SR1;         /*!< DDRPHYC ZQ0S register 1              Address offset: 0x18C */
       uint32_t RESERVED1[12];  /*!< Reserved                             Address offset: 0x190-0x1BC */
  __IO uint32_t DX0GCR;         /*!< DDRPHYC byte lane 0 GC register      Address offset: 0x1C0 */
  __IO uint32_t DX0GSR0;        /*!< DDRPHYC byte lane 0 GS register 0    Address offset: 0x1C4 */
  __IO uint32_t DX0GSR1;        /*!< DDRPHYC byte lane 0 GS register 1    Address offset: 0x1C8 */
  __IO uint32_t DX0DLLCR;       /*!< DDRPHYC byte lane 0 DLLC register    Address offset: 0x1CC */
  __IO uint32_t DX0DQTR;        /*!< DDRPHYC byte lane 0 DQT register     Address offset: 0x1D0 */
  __IO uint32_t DX0DQSTR;       /*!< DDRPHYC byte lane 0 DQST register    Address offset: 0x1D4 */
       uint32_t RESERVED2[10];  /*!< Reserved                             Address offset: 0x1D8-0x1FC */
  __IO uint32_t DX1GCR;         /*!< DDRPHYC byte lane 1 GC register      Address offset: 0x200 */
  __IO uint32_t DX1GSR0;        /*!< DDRPHYC byte lane 1 GS register 0    Address offset: 0x204 */
  __IO uint32_t DX1GSR1;        /*!< DDRPHYC byte lane 1 GS register 1    Address offset: 0x208 */
  __IO uint32_t DX1DLLCR;       /*!< DDRPHYC byte lane 1 DLLC register    Address offset: 0x20C */
  __IO uint32_t DX1DQTR;        /*!< DDRPHYC byte lane 1 DQT register     Address offset: 0x210 */
  __IO uint32_t DX1DQSTR;       /*!< DDRPHYC byte lane 1 DQST register    Address offset: 0x214 */
       uint32_t RESERVED3[10];  /*!< Reserved                             Address offset: 0x218-0x23C */
  __IO uint32_t DX2GCR;         /*!< DDRPHYC byte lane 2 GC register      Address offset: 0x240 */
  __IO uint32_t DX2GSR0;        /*!< DDRPHYC byte lane 2 GS register 0    Address offset: 0x244 */
  __IO uint32_t DX2GSR1;        /*!< DDRPHYC byte lane 2 GS register 1    Address offset: 0x248 */
  __IO uint32_t DX2DLLCR;       /*!< DDRPHYC byte lane 2 DLLC register    Address offset: 0x24C */
  __IO uint32_t DX2DQTR;        /*!< DDRPHYC byte lane 2 DQT register     Address offset: 0x250 */
  __IO uint32_t DX2DQSTR;       /*!< DDRPHYC byte lane 2 DQST register    Address offset: 0x254 */
       uint32_t RESERVED4[10];  /*!< Reserved                             Address offset: 0x258-0x27C */
  __IO uint32_t DX3GCR;         /*!< DDRPHYC byte lane 3 GC register      Address offset: 0x280 */
  __IO uint32_t DX3GSR0;        /*!< DDRPHYC byte lane 3 GS register 0    Address offset: 0x284 */
  __IO uint32_t DX3GSR1;        /*!< DDRPHYC byte lane 3 GS register 1    Address offset: 0x288 */
  __IO uint32_t DX3DLLCR;       /*!< DDRPHYC byte lane 3 DLLC register    Address offset: 0x28C */
  __IO uint32_t DX3DQTR;        /*!< DDRPHYC byte lane 3 DQT register     Address offset: 0x290 */
  __IO uint32_t DX3DQSTR;       /*!< DDRPHYC byte lane 3 DQST register    Address offset: 0x294 */
} DDRPHYC_TypeDef;

/**
  * @brief DFSDM module registers
  */
typedef struct
{
  __IO uint32_t FLTCR1;      /*!< DFSDM control register1,                          Address offset: 0x100 */
  __IO uint32_t FLTCR2;      /*!< DFSDM control register2,                          Address offset: 0x104 */
  __IO uint32_t FLTISR;      /*!< DFSDM interrupt and status register,              Address offset: 0x108 */
  __IO uint32_t FLTICR;      /*!< DFSDM interrupt flag clear register,              Address offset: 0x10C */
  __IO uint32_t FLTJCHGR;    /*!< DFSDM injected channel group selection register,  Address offset: 0x110 */
  __IO uint32_t FLTFCR;      /*!< DFSDM filter control register,                    Address offset: 0x114 */
  __IO uint32_t FLTJDATAR;   /*!< DFSDM data register for injected group,           Address offset: 0x118 */
  __IO uint32_t FLTRDATAR;   /*!< DFSDM data register for regular group,            Address offset: 0x11C */
  __IO uint32_t FLTAWHTR;    /*!< DFSDM analog watchdog high threshold register,    Address offset: 0x120 */
  __IO uint32_t FLTAWLTR;    /*!< DFSDM analog watchdog low threshold register,     Address offset: 0x124 */
  __IO uint32_t FLTAWSR;     /*!< DFSDM analog watchdog status register             Address offset: 0x128 */
  __IO uint32_t FLTAWCFR;    /*!< DFSDM analog watchdog clear flag register         Address offset: 0x12C */
  __IO uint32_t FLTEXMAX;    /*!< DFSDM extreme detector maximum register,          Address offset: 0x130 */
  __IO uint32_t FLTEXMIN;    /*!< DFSDM extreme detector minimum register           Address offset: 0x134 */
  __IO uint32_t FLTCNVTIMR;  /*!< DFSDM conversion timer,                           Address offset: 0x138 */
} DFSDM_Filter_TypeDef;

/**
  * @brief DFSDM channel configuration registers
  */
typedef struct
{
  __IO uint32_t CHCFGR1;     /*!< DFSDM channel configuration register1,            Address offset: 0x00 */
  __IO uint32_t CHCFGR2;     /*!< DFSDM channel configuration register2,            Address offset: 0x04 */
  __IO uint32_t CHAWSCDR;    /*!< DFSDM channel analog watchdog and
                                  short circuit detector register,                  Address offset: 0x08 */
  __IO uint32_t CHWDATAR;    /*!< DFSDM channel watchdog filter data register,      Address offset: 0x0C */
  __IO uint32_t CHDATINR;    /*!< DFSDM channel data input register,                Address offset: 0x10 */
  __IO uint32_t CHDLYR;      /*!< DFSDM channel delay register,                     Address offset: 0x14 */
} DFSDM_Channel_TypeDef;


/**
  * @brief DFSDM registers
  */
typedef struct
{
  uint32_t RESERVED[508];/*!< Reserved,                                       0x000 - 0x7F0 */
  __IO uint32_t HWCFGR;  /*!< DFSDM HW Configuration register ,       Address offset: 0x7F0 */
  __IO uint32_t VERR;    /*!< DFSDM Version register,                 Address offset: 0x7F4 */
  __IO uint32_t IPDR;    /*!< DFSDM Identification register,          Address offset: 0x7F8 */
  __IO uint32_t SIDR;    /*!< DFSDM Size Identification register,     Address offset: 0x7FC */
} DFSDM_TypeDef;


/**
  * @brief Debug MCU
  */

typedef struct
{
  __IO uint32_t IDCODE;        /*!< MCU device ID code,                         Address offset: 0x00 */
  __IO uint32_t CR;            /*!< Debug MCU configuration register,           Address offset: 0x04 */
  __IO uint32_t RESERVED4[9];  /*!< Reserved,                                   Address offset: 0x08 */
  __IO uint32_t APB4FZ1;       /*!< Debug MCU APB4FZ1 freeze register CPU1,     Address offset: 0x2C */
  __IO uint32_t APB4FZ2;       /*!< Debug MCU APB4FZ2 freeze register CPU2,     Address offset: 0x30 */
  __IO uint32_t APB1FZ1;       /*!< Debug MCU APB1FZ1 freeze register CPU1,     Address offset: 0x34 */
  __IO uint32_t APB1FZ2;       /*!< Debug MCU APB1FZ2 freeze register CPU2,     Address offset: 0x38 */
  __IO uint32_t APB2FZ1;       /*!< Debug MCU APB2FZ1 freeze register CPU1,     Address offset: 0x3C */
  __IO uint32_t APB2FZ2;       /*!< Debug MCU APB2FZ2 freeze register CPU2,     Address offset: 0x40 */
  __IO uint32_t APB3FZ1;       /*!< Debug MCU APB3FZ1 freeze register CPU1,     Address offset: 0x44 */
  __IO uint32_t APB3FZ2;       /*!< Debug MCU APB3FZ2 freeze register CPU2,     Address offset: 0x48 */
  __IO uint32_t APB5FZ1;       /*!< Debug MCU APB5FZ1 freeze register CPU1,     Address offset: 0x4C */
  __IO uint32_t APB5FZ2;       /*!< Debug MCU APB5FZ2 freeze register CPU2,     Address offset: 0x50 */
}DBGMCU_TypeDef;

/**
  * @brief DCMI
  */

typedef struct
{
  __IO uint32_t CR;       /*!< DCMI control register 1,                       Address offset: 0x000 */
  __IO uint32_t SR;       /*!< DCMI status register,                          Address offset: 0x004 */
  __IO uint32_t RISR;     /*!< DCMI raw interrupt status register,            Address offset: 0x008 */
  __IO uint32_t IER;      /*!< DCMI interrupt enable register,                Address offset: 0x00C */
  __IO uint32_t MISR;     /*!< DCMI masked interrupt status register,         Address offset: 0x010 */
  __IO uint32_t ICR;      /*!< DCMI interrupt clear register,                 Address offset: 0x014 */
  __IO uint32_t ESCR;     /*!< DCMI embedded synchronization code register,   Address offset: 0x018 */
  __IO uint32_t ESUR;     /*!< DCMI embedded synchronization unmask register, Address offset: 0x01C */
  __IO uint32_t CWSTRTR;  /*!< DCMI crop window start,                        Address offset: 0x020 */
  __IO uint32_t CWSIZER;  /*!< DCMI crop window size,                         Address offset: 0x024 */
  __IO uint32_t DR;       /*!< DCMI data register,                            Address offset: 0x028 */
  uint32_t RESERVED[242]; /*!< Reserved,                                              0x02C - 0x3F0 */
  __IO uint32_t VERR;     /*!< DCMI Version register,                         Address offset: 0x3F4 */
  __IO uint32_t IPDR;     /*!< DCMI Identification register,                  Address offset: 0x3F8 */
  __IO uint32_t SIDR;     /*!< DCMI Size Identification register,             Address offset: 0x3FC */
} DCMI_TypeDef;

/**
  * @brief DMA Controller
  */

typedef struct
{
  __IO uint32_t CR;     /*!< DMA stream x configuration register      */
  __IO uint32_t NDTR;   /*!< DMA stream x number of data register     */
  __IO uint32_t PAR;    /*!< DMA stream x peripheral address register */
  __IO uint32_t M0AR;   /*!< DMA stream x memory 0 address register   */
  __IO uint32_t M1AR;   /*!< DMA stream x memory 1 address register   */
  __IO uint32_t FCR;    /*!< DMA stream x FIFO control register       */
} DMA_Stream_TypeDef;

typedef struct
{
  __IO uint32_t LISR;   /*!< DMA low interrupt status register,      Address offset: 0x00 */
  __IO uint32_t HISR;   /*!< DMA high interrupt status register,     Address offset: 0x04 */
  __IO uint32_t LIFCR;  /*!< DMA low interrupt flag clear register,  Address offset: 0x08 */
  __IO uint32_t HIFCR;  /*!< DMA high interrupt flag clear register, Address offset: 0x0C */
  __IO uint32_t RESERVED[247];  /*!< Reserved,               Address offset: 0x10 - 0x3E8 */
  __IO uint32_t HWCFGR2; /*!< DMA HW Configuration register 2,      Address offset: 0x3EC */
  __IO uint32_t HWCFGR1; /*!< DMA HW Configuration register 1,      Address offset: 0x3F0 */
  __IO uint32_t VERR;    /*!< DMA Version register,                 Address offset: 0x3F4 */
  __IO uint32_t IPDR;    /*!< DMA Identification register,          Address offset: 0x3F8 */
  __IO uint32_t SIDR;    /*!< DMA Size Identification register,     Address offset: 0x3FC */
} DMA_TypeDef;

typedef struct
{
  __IO uint32_t  CCR;        /*!< DMA Multiplexer Channel x Control Register   */
}DMAMUX_Channel_TypeDef;

typedef struct
{
  __IO uint32_t  CSR;      /*!< DMA Channel Status Register     */
  __IO uint32_t  CFR;      /*!< DMA Channel Clear Flag Register */
}DMAMUX_ChannelStatus_TypeDef;

typedef struct
{
  __IO uint32_t  RGCR;        /*!< DMA Request Generator x Control Register   */
}DMAMUX_RequestGen_TypeDef;

typedef struct
{
  __IO uint32_t  RGSR;            /*!< DMAMUX Request Generator Status Register,           Address offset: 0x140 */
  __IO uint32_t  RGCFR;           /*!< DMAMUX Request Generator Clear Flag Register,       Address offset: 0x144 */
  uint32_t       RESERVED0[169];  /*!< Reserved, 0x144 -> 0x144                                                  */
  __IO uint32_t  HWCFGR2;         /*!< DMAMUX Configuration register 2,                    Address offset: 0x3EC */
  __IO uint32_t  HWCFGR1;         /*!< DMAMUX Configuration register 1,                    Address offset: 0x3F0 */
  __IO uint32_t  VERR;            /*!< DMAMUX Verion Register,                             Address offset: 0x3F4 */
  __IO uint32_t  IPDR;            /*!< DMAMUX Identification register,                     Address offset: 0x3F8 */
  __IO uint32_t  SIDR;            /*!< DMAMUX Size Identification register,                Address offset: 0x3FC */

}DMAMUX_RequestGenStatus_TypeDef;

/**
  * @brief MDMA Controller
  */
typedef struct
{
  __IO uint32_t  GISR0;   /*!< MDMA Global Interrupt/Status Register 0,          Address offset: 0x000 */
  uint32_t RESERVED1;      /*!< Reserved,                                                         0x004 */
//  __IO uint32_t  GISR1;   /*!< MDMA Global Interrupt/Status Register 1,          Address offset: 0x004 */
  __IO uint32_t  SGISR0;  /*!< MDMA Secure Global Interrupt/Status Register 0,   Address offset: 0x008 */
//  __IO uint32_t  SGISR1;  /*!< MDMA Secure Global Interrupt/Status Register 1,   Address offset: 0x00C */
  uint32_t RESERVED2[250]; /*!< Reserved,                                                  0x10 - 0x3F0 */
  __IO uint32_t  VERR;    /*!< MDMA Verion Register,                             Address offset: 0x3F4 */
  __IO uint32_t  IPDR;    /*!< MDMA Identification register,                     Address offset: 0x3F8 */
  __IO uint32_t  SIDR;    /*!< MDMA Size Identification register,                Address offset: 0x3FC */
}MDMA_TypeDef;

typedef struct
{
  __IO uint32_t  CISR;      /*!< MDMA channel x interrupt/status register,             Address offset: 0x40 */
  __IO uint32_t  CIFCR;     /*!< MDMA channel x interrupt flag clear register,         Address offset: 0x44 */
  __IO uint32_t  CESR;      /*!< MDMA Channel x error status register,                 Address offset: 0x48 */
  __IO uint32_t  CCR;       /*!< MDMA channel x control register,                      Address offset: 0x4C */
  __IO uint32_t  CTCR;      /*!< MDMA channel x Transfer Configuration register,       Address offset: 0x50 */
  __IO uint32_t  CBNDTR;    /*!< MDMA Channel x block number of data register,         Address offset: 0x54 */
  __IO uint32_t  CSAR;      /*!< MDMA channel x source address register,               Address offset: 0x58 */
  __IO uint32_t  CDAR;      /*!< MDMA channel x destination address register,          Address offset: 0x5C */
  __IO uint32_t  CBRUR;     /*!< MDMA channel x Block Repeat address Update register,  Address offset: 0x60 */
  __IO uint32_t  CLAR;      /*!< MDMA channel x Link Address register,                 Address offset: 0x64 */
  __IO uint32_t  CTBR;      /*!< MDMA channel x Trigger and Bus selection Register,    Address offset: 0x68 */
  uint32_t       RESERVED0; /*!< Reserved, 0x68                                                             */
 __IO uint32_t    CMAR;      /*!< MDMA channel x Mask address register,                Address offset: 0x70 */
 __IO uint32_t   CMDR;       /*!< MDMA channel x Mask Data register,                   Address offset: 0x74 */
}MDMA_Channel_TypeDef;

/**
  * @brief DSI Controller
  */

typedef struct
{
  __IO uint32_t VR;            /*!< DSI Host Version Register,                                 Address offset: 0x00      */
  __IO uint32_t CR;            /*!< DSI Host Control Register,                                 Address offset: 0x04      */
  __IO uint32_t CCR;           /*!< DSI HOST Clock Control Register,                           Address offset: 0x08      */
  __IO uint32_t LVCIDR;        /*!< DSI Host LTDC VCID Register,                               Address offset: 0x0C      */
  __IO uint32_t LCOLCR;        /*!< DSI Host LTDC Color Coding Register,                       Address offset: 0x10      */
  __IO uint32_t LPCR;          /*!< DSI Host LTDC Polarity Configuration Register,             Address offset: 0x14      */
  __IO uint32_t LPMCR;         /*!< DSI Host Low-Power Mode Configuration Register,            Address offset: 0x18      */
  uint32_t      RESERVED0[4];  /*!< Reserved, 0x1C - 0x2B                                                                */
  __IO uint32_t PCR;           /*!< DSI Host Protocol Configuration Register,                  Address offset: 0x2C      */
  __IO uint32_t GVCIDR;        /*!< DSI Host Generic VCID Register,                            Address offset: 0x30      */
  __IO uint32_t MCR;           /*!< DSI Host Mode Configuration Register,                      Address offset: 0x34      */
  __IO uint32_t VMCR;          /*!< DSI Host Video Mode Configuration Register,                Address offset: 0x38      */
  __IO uint32_t VPCR;          /*!< DSI Host Video Packet Configuration Register,              Address offset: 0x3C      */
  __IO uint32_t VCCR;          /*!< DSI Host Video Chunks Configuration Register,              Address offset: 0x40      */
  __IO uint32_t VNPCR;         /*!< DSI Host Video Null Packet Configuration Register,         Address offset: 0x44      */
  __IO uint32_t VHSACR;        /*!< DSI Host Video HSA Configuration Register,                 Address offset: 0x48      */
  __IO uint32_t VHBPCR;        /*!< DSI Host Video HBP Configuration Register,                 Address offset: 0x4C      */
  __IO uint32_t VLCR;          /*!< DSI Host Video Line Configuration Register,                Address offset: 0x50      */
  __IO uint32_t VVSACR;        /*!< DSI Host Video VSA Configuration Register,                 Address offset: 0x54      */
  __IO uint32_t VVBPCR;        /*!< DSI Host Video VBP Configuration Register,                 Address offset: 0x58      */
  __IO uint32_t VVFPCR;        /*!< DSI Host Video VFP Configuration Register,                 Address offset: 0x5C      */
  __IO uint32_t VVACR;         /*!< DSI Host Video VA Configuration Register,                  Address offset: 0x60      */
  __IO uint32_t LCCR;          /*!< DSI Host LTDC Command Configuration Register,              Address offset: 0x64      */
  __IO uint32_t CMCR;          /*!< DSI Host Command Mode Configuration Register,              Address offset: 0x68      */
  __IO uint32_t GHCR;          /*!< DSI Host Generic Header Configuration Register,            Address offset: 0x6C      */
  __IO uint32_t GPDR;          /*!< DSI Host Generic Payload Data Register,                    Address offset: 0x70      */
  __IO uint32_t GPSR;          /*!< DSI Host Generic Packet Status Register,                   Address offset: 0x74      */
  __IO uint32_t TCCR[6];       /*!< DSI Host Timeout Counter Configuration Register,           Address offset: 0x78-0x8F */
  __IO uint32_t TDCR;          /*!< DSI Host 3D Configuration Register,                        Address offset: 0x90      */
  __IO uint32_t CLCR;          /*!< DSI Host Clock Lane Configuration Register,                Address offset: 0x94      */
  __IO uint32_t CLTCR;         /*!< DSI Host Clock Lane Timer Configuration Register,          Address offset: 0x98      */
  __IO uint32_t DLTCR;         /*!< DSI Host Data Lane Timer Configuration Register,           Address offset: 0x9C      */
  __IO uint32_t PCTLR;         /*!< DSI Host PHY Control Register,                             Address offset: 0xA0      */
  __IO uint32_t PCONFR;        /*!< DSI Host PHY Configuration Register,                       Address offset: 0xA4      */
  __IO uint32_t PUCR;          /*!< DSI Host PHY ULPS Control Register,                        Address offset: 0xA8      */
  __IO uint32_t PTTCR;         /*!< DSI Host PHY TX Triggers Configuration Register,           Address offset: 0xAC      */
  __IO uint32_t PSR;           /*!< DSI Host PHY Status Register,                              Address offset: 0xB0      */
  uint32_t      RESERVED1[2];  /*!< Reserved, 0xB4 - 0xBB                                                                */
  __IO uint32_t ISR[2];        /*!< DSI Host Interrupt & Status Register,                      Address offset: 0xBC-0xC3 */
  __IO uint32_t IER[2];        /*!< DSI Host Interrupt Enable Register,                        Address offset: 0xC4-0xCB */
  uint32_t      RESERVED2[3];  /*!< Reserved, 0xD0 - 0xD7                                                                */
  __IO uint32_t FIR[2];        /*!< DSI Host Force Interrupt Register,                         Address offset: 0xD8-0xDF */
  uint32_t      RESERVED3[5];  /*!< Reserved, 0xE0 - 0xF3                                                                */
  __IO uint32_t DLTRCR;        /*!< DSI Host Data Lane Timer Read Configuration Register,      Address offset: 0xF4      */
  uint32_t      RESERVED4[2];  /*!< Reserved, 0xF8 - 0xFF                                                                */
  __IO uint32_t VSCR;          /*!< DSI Host Video Shadow Control Register,                    Address offset: 0x100     */
  uint32_t      RESERVED5[2];  /*!< Reserved, 0x104 - 0x10B                                                              */
  __IO uint32_t LCVCIDR;       /*!< DSI Host LTDC Current VCID Register,                       Address offset: 0x10C     */
  __IO uint32_t LCCCR;         /*!< DSI Host LTDC Current Color Coding Register,               Address offset: 0x110     */
  uint32_t      RESERVED6;     /*!< Reserved, 0x114                                                                      */
  __IO uint32_t LPMCCR;        /*!< DSI Host Low-power Mode Current Configuration Register,    Address offset: 0x118     */
  uint32_t      RESERVED7[7];  /*!< Reserved, 0x11C - 0x137                                                              */
  __IO uint32_t VMCCR;         /*!< DSI Host Video Mode Current Configuration Register,        Address offset: 0x138     */
  __IO uint32_t VPCCR;         /*!< DSI Host Video Packet Current Configuration Register,      Address offset: 0x13C     */
  __IO uint32_t VCCCR;         /*!< DSI Host Video Chuncks Current Configuration Register,     Address offset: 0x140     */
  __IO uint32_t VNPCCR;        /*!< DSI Host Video Null Packet Current Configuration Register, Address offset: 0x144     */
  __IO uint32_t VHSACCR;       /*!< DSI Host Video HSA Current Configuration Register,         Address offset: 0x148     */
  __IO uint32_t VHBPCCR;       /*!< DSI Host Video HBP Current Configuration Register,         Address offset: 0x14C     */
  __IO uint32_t VLCCR;         /*!< DSI Host Video Line Current Configuration Register,        Address offset: 0x150     */
  __IO uint32_t VVSACCR;       /*!< DSI Host Video VSA Current Configuration Register,         Address offset: 0x154     */
  __IO uint32_t VVBPCCR;       /*!< DSI Host Video VBP Current Configuration Register,         Address offset: 0x158     */
  __IO uint32_t VVFPCCR;       /*!< DSI Host Video VFP Current Configuration Register,         Address offset: 0x15C     */
  __IO uint32_t VVACCR;        /*!< DSI Host Video VA Current Configuration Register,          Address offset: 0x160     */
  uint32_t      RESERVED8[11]; /*!< Reserved, 0x164 - 0x18F                                                              */
  __IO uint32_t TDCCR;         /*!< DSI Host 3D Current Configuration Register,                Address offset: 0x190     */
  uint32_t      RESERVED9[155]; /*!< Reserved, 0x194 - 0x3FF                                                             */
  __IO uint32_t WCFGR;          /*!< DSI Wrapper Configuration Register,                       Address offset: 0x400     */
  __IO uint32_t WCR;            /*!< DSI Wrapper Control Register,                             Address offset: 0x404     */
  __IO uint32_t WIER;           /*!< DSI Wrapper Interrupt Enable Register,                    Address offset: 0x408     */
  __IO uint32_t WISR;           /*!< DSI Wrapper Interrupt and Status Register,                Address offset: 0x40C     */
  __IO uint32_t WIFCR;          /*!< DSI Wrapper Interrupt Flag Clear Register,                Address offset: 0x410     */
  uint32_t      RESERVED10;     /*!< Reserved, 0x414                                                                     */
  __IO uint32_t WPCR[2];        /*!< DSI Wrapper PHY Configuration Register,                   Address offset: 0x418-41C */
  uint32_t      RESERVED11[4];  /*!< Reserved, 0x420 - 0x42F                                                             */
  __IO uint32_t WRPCR;          /*!< DSI Wrapper Regulator and PLL Control Register,           Address offset: 0x430     */
  uint32_t      RESERVED12[239];  /*!< Reserved, 0x434 - 0x7EC                                                           */
  __IO uint32_t HWCFGR;         /*!< DSI Host hardware configuration register,                 Address offset: 0x7F0     */
  __IO uint32_t VERR;           /*!< DSI Host version register,                                Address offset: 0x7F4     */
  __IO uint32_t IPIDR;          /*!< DSI Host Identification register,                         Address offset: 0x7F8     */
  __IO uint32_t SIDR;           /*!< DSI Host Size ID register,                                Address offset: 0x7FC     */
} DSI_TypeDef;

/**
  * @brief Ethernet MAC
  */
typedef struct
{
  __IO uint32_t MACCR;            /*!< Operating mode configuration register                      Address offset: 0x0000 */
  __IO uint32_t MACECR;           /*!< Extended operating mode configuration register             Address offset: 0x0004 */
  __IO uint32_t MACPFR;           /*!< Packet filtering control register                          Address offset: 0x0008 */
  __IO uint32_t MACWTR;           /*!< Watchdog timeout register                                  Address offset: 0x000C */
  __IO uint32_t MACHT0R;          /*!< Hash Table 0 register                                      Address offset: 0x0010 */
  __IO uint32_t MACHT1R;          /*!< Hash Table 1 register                                      Address offset: 0x0014 */
       uint32_t RESERVED0[14];    /*!< Reserved                                                   Address offset: 0x0018-0x004C */
  __IO uint32_t MACVTR;           /*!< VLAN tag register                                          Address offset: 0x0050 */
       uint32_t RESERVED1;        /*!< Reserved                                                   Address offset: 0x0054 */
  __IO uint32_t MACVHTR;          /*!< VLAN Hash table register                                   Address offset: 0x0058 */
       uint32_t RESERVED2;        /*!< Reserved                                                   Address offset: 0x005C */
  __IO uint32_t MACVIR;           /*!< VLAN inclusion register                                    Address offset: 0x0060 */
  __IO uint32_t MACIVIR;          /*!< Inner VLAN inclusion register                              Address offset: 0x0064 */
       uint32_t RESERVED3[2];     /*!< Reserved                                                   Address offset: 0x0068-0x006C */
  __IO uint32_t MACQ0TXFCR;       /*!< Tx Queue 0 flow control register                           Address offset: 0x0070 */
       uint32_t RESERVED4[7];     /*!< Reserved                                                   Address offset: 0x0074-0x008C */
  __IO uint32_t MACRXFCR;         /*!< Rx flow control register                                   Address offset: 0x0090 */
       uint32_t RESERVED5;        /*!< Reserved                                                   Address offset: 0x0094 */
  __IO uint32_t MACTXQPMR;        /*!< Tx queue priority mapping 0 register                       Address offset: 0x0098 */
       uint32_t RESERVED6;        /*!< Reserved                                                   Address offset: 0x009C */
  __IO uint32_t MACRXQC0R;        /*!< Rx queue control 0 register                                Address offset: 0x00A0 */
  __IO uint32_t MACRXQC1R;        /*!< Rx queue control 1 register                                Address offset: 0x00A4 */
  __IO uint32_t MACRXQC2R;        /*!< Rx queue control 2 register                                Address offset: 0x00A8 */
       uint32_t RESERVED7;        /*!< Reserved                                                   Address offset: 0x00AC */
  __IO uint32_t MACISR;           /*!< Interrupt status register                                  Address offset: 0x00B0 */
  __IO uint32_t MACIER;           /*!< Interrupt enable register                                  Address offset: 0x00B4 */
  __IO uint32_t MACRXTXSR;        /*!< Rx Tx status register                                      Address offset: 0x00B8 */
       uint32_t RESERVED8;        /*!< Reserved                                                   Address offset: 0x00BC */
  __IO uint32_t MACPCSR;          /*!< PMT control status register                                Address offset: 0x00C0 */
  __IO uint32_t MACRWKPFR;        /*!< Remote wakeup packet filter register                       Address offset: 0x00C4 */
       uint32_t RESERVED9[2];     /*!< Reserved                                                   Address offset: 0x00C8-0x00CC */
  __IO uint32_t MACLCSR;          /*!< LPI control status register                                Address offset: 0x00D0 */
  __IO uint32_t MACLTCR;          /*!< LPI timers control register                                Address offset: 0x00D4 */
  __IO uint32_t MACLETR;          /*!< LPI entry timer register                                   Address offset: 0x00D8 */
  __IO uint32_t MAC1USTCR;        /*!< microsecond-tick counter register                          Address offset: 0x00DC */
       uint32_t RESERVED10[6];    /*!< Reserved                                                   Address offset: 0x00E0-0x00F4 */
  __IO uint32_t MACPHYCSR;        /*!< PHYIF control status register                              Address offset: 0x00F8 */
       uint32_t RESERVED11[5];    /*!< Reserved                                                   Address offset: 0x00FC-0x010C */
  __IO uint32_t MACVR;            /*!< Version register                                           Address offset: 0x0110 */
  __IO uint32_t MACDR;            /*!< Debug register                                             Address offset: 0x0114 */
       uint32_t RESERVED12[2];    /*!< Reserved                                                   Address offset: 0x0118-0x011C */
  __IO uint32_t MACHWF1R;         /*!< HW feature 1 register                                      Address offset: 0x0120 */
  __IO uint32_t MACHWF2R;         /*!< HW feature 2 register                                      Address offset: 0x0124 */
       uint32_t RESERVED13[54];   /*!< Reserved                                                   Address offset: 0x0128-0x01FC */
  __IO uint32_t MACMDIOAR;        /*!< MDIO address register                                      Address offset: 0x0200 */
  __IO uint32_t MACMDIODR;        /*!< MDIO data register                                         Address offset: 0x0204 */
       uint32_t RESERVED14[62];   /*!< Reserved                                                   Address offset: 0x0208-0x02FC */
  __IO uint32_t MACA0HR;          /*!< Address 0 high register                                    Address offset: 0x0300 */
  __IO uint32_t MACA0LR;          /*!< Address 0 low register                                     Address offset: 0x0304 */
  __IO uint32_t MACA1HR;          /*!< Address 1 high register                                    Address offset: 0x0308 */
  __IO uint32_t MACA1LR;          /*!< Address 1 low register                                     Address offset: 0x030C */
  __IO uint32_t MACA2HR;          /*!< Address 2 high register                                    Address offset: 0x0310 */
  __IO uint32_t MACA2LR;          /*!< Address 2 low register                                     Address offset: 0x0314 */
  __IO uint32_t MACA3HR;          /*!< Address 3 high register                                    Address offset: 0x0318 */
  __IO uint32_t MACA3LR;          /*!< Address 3 low register                                     Address offset: 0x031C */
       uint32_t RESERVED15[248];  /*!< Reserved                                                   Address offset: 0x0320-0x06FC */
  __IO uint32_t MMCCR;            /*!< MMC control register                                       Address offset: 0x0700 */
  __IO uint32_t MMCRXIR;          /*!< MMC Rx interrupt register                                  Address offset: 0x704 */
  __IO uint32_t MMCTXIR;          /*!< MMC Tx interrupt register                                  Address offset: 0x708 */
  __IO uint32_t MMCRXIMR;         /*!< MMC Rx interrupt mask register                             Address offset: 0x70C */
  __IO uint32_t MMCTXIMR;         /*!< MMC Tx interrupt mask register                      Address offset: 0x710 */
       uint32_t RESERVED16[14];   /*!< Reserved                                                    Address offset: 0x0714-0x0748 */
  __IO uint32_t MMCTXSCGPR;       /*!< Tx single collision good packets register      Address offset: 0x74C */
  __IO uint32_t MMCTXMCGPR;       /*!< Tx multiple collision good packets register  Address offset: 0x750 */
       uint32_t RESERVED16_1[5];  /*!< Reserved                                                   Address offset: 0x0754-0x0764 */
  __IO uint32_t MMCTXPCGR;        /*!< Tx packet count good register                     Address offset: 0x768 */
       uint32_t RESERVED16_2[10]; /*!< Reserved                                                  Address offset: 0x076C-0x0790 */
  __IO uint32_t MMCRXCRCEPR;      /*!< Rx CRC error packets register                   Address offset: 0x794 */
  __IO uint32_t MMCRXAEPR;        /*!< Rx alignment error packets register         Address offset: 0x798 */
       uint32_t RESERVED16_3[10]; /*!< Reserved                                                  Address offset: 0x079C-0x07C0 */
  __IO uint32_t MMCRXUPGR;        /*!< Rx unicast packets good register               Address offset: 0x7C4 */
       uint32_t RESERVED16_4[9];  /*!< Reserved                                                   Address offset: 0x07C8-0x07E8 */
  __IO uint32_t MMCTXLPIMSTR;     /*!< Tx LPI microsecond timer register                     Address offset: 0x7EC */
  __IO uint32_t MMCTXLPITCR;      /*!< Tx LPI transition counter register                    Address offset: 0x7F0 */
  __IO uint32_t MMCRXLPIMSTR;     /*!< Rx LPI microsecond counter register                   Address offset: 0x7F4 */
  __IO uint32_t MMCRXLPITCR;  /*!< Rx LPI transition counter register                    Address offset: 0x7F8 */
       uint32_t RESERVED16_5[65];  /*!< Reserved                                                  Address offset: 0x07FC-0x08FC */
  __IO uint32_t MACL3L4C0R;       /*!< L3 and L4 control 0 register                               Address offset: 0x0900 */
  __IO uint32_t MACL4A0R;         /*!< Layer4 address filter 0 register                           Address offset: 0x0904 */
       uint32_t RESERVED17[2];    /*!< Reserved                                                   Address offset: 0x0908-0x090C */
  __IO uint32_t MACL3A00R;        /*!< Layer 3 Address 0 filter 0 register                        Address offset: 0x0910 */
  __IO uint32_t MACL3A10R;        /*!< Layer3 address 1 filter 0 register                         Address offset: 0x0914 */
  __IO uint32_t MACL3A20;         /*!< Layer3 Address 2 filter 0 register                         Address offset: 0x0918 */
  __IO uint32_t MACL3A30;         /*!< Layer3 Address 3 filter 0 register                         Address offset: 0x091C */
       uint32_t RESERVED18[4];    /*!< Reserved                                                   Address offset: 0x0920-0x092C */
  __IO uint32_t MACL3L4C1R;       /*!< L3 and L4 control 1 register                               Address offset: 0x0930 */
  __IO uint32_t MACL4A1R;         /*!< Layer 4 address filter 1 register                          Address offset: 0x0934 */
       uint32_t RESERVED19[2];    /*!< Reserved                                                   Address offset: 0x0938-0x093C */
  __IO uint32_t MACL3A01R;        /*!< Layer3 address 0 filter 1 Register                         Address offset: 0x0940 */
  __IO uint32_t MACL3A11R;        /*!< Layer3 address 1 filter 1 register                         Address offset: 0x0944 */
  __IO uint32_t MACL3A21R;        /*!< Layer3 address 2 filter 1 Register                         Address offset: 0x0948 */
  __IO uint32_t MACL3A31R;        /*!< Layer3 address 3 filter 1 register                         Address offset: 0x094C */
       uint32_t RESERVED20[100];  /*!< Reserved                                                   Address offset: 0x0950-0x0ADC */
  __IO uint32_t MACARPAR;         /*!< ARP address register                                       Address offset: 0x0AE0 */
       uint32_t RESERVED21[7];    /*!< Reserved                                                   Address offset: 0x0AE4-0x0AFC */
  __IO uint32_t MACTSCR;          /*!< Timestamp control Register                                 Address offset: 0x0B00 */
  __IO uint32_t MACSSIR;          /*!< Sub-second increment register                              Address offset: 0x0B04 */
  __IO uint32_t MACSTSR;          /*!< System time seconds register                               Address offset: 0x0B08 */
  __IO uint32_t MACSTNR;          /*!< System time nanoseconds register                           Address offset: 0x0B0C */
  __IO uint32_t MACSTSUR;         /*!< System time seconds update register                        Address offset: 0x0B10 */
  __IO uint32_t MACSTNUR;         /*!< System time nanoseconds update register                    Address offset: 0x0B14 */
  __IO uint32_t MACTSAR;          /*!< Timestamp addend register                                  Address offset: 0x0B18 */
       uint32_t RESERVED22;       /*!< Reserved                                                   Address offset: 0x0B1C */
  __IO uint32_t MACTSSR;          /*!< Timestamp status register                                  Address offset: 0x0B20 */
       uint32_t RESERVED23[3];    /*!< Reserved                                                   Address offset: 0x0B24-0x0B2C */
  __IO uint32_t MACTXTSSNR;       /*!< Tx timestamp status nanoseconds register                   Address offset: 0x0B30 */
  __IO uint32_t MACTXTSSSR;       /*!< Tx timestamp status seconds register                       Address offset: 0x0B34 */
       uint32_t RESERVED24[2];    /*!< Reserved                                                   Address offset: 0x0B38-0x0B3C */
  __IO uint32_t MACACR;           /*!< Auxiliary control register                                 Address offset: 0x0B40 */
       uint32_t RESERVED25;       /*!< Reserved                                                   Address offset: 0x0B44 */
  __IO uint32_t MACATSNR;         /*!< Auxiliary timestamp nanoseconds register                   Address offset: 0x0B48 */
  __IO uint32_t MACATSSR;         /*!< Auxiliary timestamp seconds register                       Address offset: 0x0B4C */
  __IO uint32_t MACTSIACR;        /*!< Timestamp Ingress asymmetric correction register           Address offset: 0x0B50 */
  __IO uint32_t MACTSEACR;        /*!< Timestamp Egress asymmetric correction register            Address offset: 0x0B54 */
  __IO uint32_t MACTSICNR;        /*!< Timestamp Ingress correction nanosecond register           Address offset: 0x0B58 */
  __IO uint32_t MACTSECNR;        /*!< Timestamp Egress correction nanosecond register            Address offset: 0x0B5C */
       uint32_t RESERVED26[4];    /*!< Reserved                                                   Address offset: 0x0B60-0x0B6C */
  __IO uint32_t MACPPSCR;         /*!< PPS control register [alternate]                           Address offset: 0x0B70 */
       uint32_t RESERVED27[3];    /*!< Reserved                                                   Address offset: 0x0B74-0x0B7C */
  __IO uint32_t MACPPSTTSR;       /*!< PPS target time seconds register                           Address offset: 0x0B80 */
  __IO uint32_t MACPPSTTNR;       /*!< PPS target time nanoseconds register                       Address offset: 0x0B84 */
  __IO uint32_t MACPPSIR;         /*!< PPS interval register                                      Address offset: 0x0B88 */
  __IO uint32_t MACPPSWR;         /*!< PPS width register                                         Address offset: 0x0B8C */
       uint32_t RESERVED28[12];   /*!< Reserved                                                   Address offset: 0x0B90-0x0BBC */
  __IO uint32_t MACPOCR;          /*!< PTP Offload control register                               Address offset: 0x0BC0 */
  __IO uint32_t MACSPI0R;         /*!< PTP Source Port Identity 0 Register                        Address offset: 0x0BC4 */
  __IO uint32_t MACSPI1R;         /*!< PTP Source port identity 1 register                        Address offset: 0x0BC8 */
  __IO uint32_t MACSPI2R;         /*!< PTP Source port identity 2 register                        Address offset: 0x0BCC */
  __IO uint32_t MACLMIR;          /*!< Log message interval register                              Address offset: 0x0BD0 */
       uint32_t RESERVED29[11];   /*!< Reserved                                                   Address offset: 0x0BD4-0x0BFC */
  __IO uint32_t MTLOMR;           /*!< Operating mode Register                                    Address offset: 0x0C00 */
       uint32_t RESERVED30[7];    /*!< Reserved                                                   Address offset: 0x0C04-0x0C1C */
  __IO uint32_t MTLISR;           /*!< Interrupt status Register                                  Address offset: 0x0C20 */
       uint32_t RESERVED31[55];   /*!< Reserved                                                   Address offset: 0x0C24-0x0CFC */
  __IO uint32_t MTLTXQ0OMR;       /*!< Tx queue 0 operating mode Register                         Address offset: 0x0D00 */
  __IO uint32_t MTLTXQ0UR;        /*!< Tx queue 0 underflow register                              Address offset: 0x0D04 */
  __IO uint32_t MTLTXQ0DR;        /*!< Tx queue 0 debug Register                                  Address offset: 0x0D08 */
       uint32_t RESERVED32[2];    /*!< Reserved                                                   Address offset: 0x0D0C-0x0D10 */
  __IO uint32_t MTLTXQ0ESR;       /*!< Tx queue x ETS status Register                             Address offset: 0x0D14 */
       uint32_t RESERVED33[5];    /*!< Reserved                                                   Address offset: 0x0D18-0x0D28 */
  __IO uint32_t MTLQ0ICSR;        /*!< Queue 0 interrupt control status Register                  Address offset: 0x0D2C */
  __IO uint32_t MTLRXQ0OMR;       /*!< Rx queue 0 operating mode register                         Address offset: 0x0D30 */
  __IO uint32_t MTLRXQ0MPOCR;     /*!< Rx queue 0 missed packet and overflow counter register     Address offset: 0x0D34 */
  __IO uint32_t MTLRXQ0DR;        /*!< Rx queue 0 debug register                                  Address offset: 0x0D38 */
  __IO uint32_t MTLRXQ0CR;        /*!< Rx queue 0 control register                                Address offset: 0x0D3C */
  __IO uint32_t MTLTXQ1OMR;       /*!< Tx queue 1 operating mode Register                         Address offset: 0x0D40 */
  __IO uint32_t MTLTXQ1UR;        /*!< Tx queue 1 underflow register                              Address offset: 0x0D44 */
  __IO uint32_t MTLTXQ1DR;        /*!< Tx queue 1 debug Register                                  Address offset: 0x0D48 */
       uint32_t RESERVED34;       /*!< Reserved                                                   Address offset: 0x0D4C */
  __IO uint32_t MTLTXQ1ECR;       /*!< Tx queue 1 ETS control Register                            Address offset: 0x0D50 */
  __IO uint32_t MTLTXQ1ESR;       /*!< Tx queue x ETS status Register                             Address offset: 0x0D54 */
  __IO uint32_t MTLTXQ1QWR;       /*!< Tx queue 1 quantum weight register                         Address offset: 0x0D58 */
  __IO uint32_t MTLTXQ1SSCR;      /*!< Tx queue 1 send slope credit Register                      Address offset: 0x0D5C */
  __IO uint32_t MTLTXQ1HCR;       /*!< Tx Queue 1 hiCredit register                               Address offset: 0x0D60 */
  __IO uint32_t MTLTXQ1LCR;       /*!< Tx queue 1 loCredit register                               Address offset: 0x0D64 */
       uint32_t RESERVED35;       /*!< Reserved                                                   Address offset: 0x0D68 */
  __IO uint32_t MTLQ1ICSR;        /*!< Queue 1 interrupt control status Register                  Address offset: 0x0D6C */
  __IO uint32_t MTLRXQ1OMR;       /*!< Rx queue 1 operating mode register                         Address offset: 0x0D70 */
  __IO uint32_t MTLRXQ1MPOCR;     /*!< Rx queue 1 missed packet and overflow counter register     Address offset: 0x0D74 */
  __IO uint32_t MTLRXQ1DR;        /*!< Rx queue 1 debug register                                  Address offset: 0x0D78 */
  __IO uint32_t MTLRXQ1CR;        /*!< Rx queue 1 control register                                Address offset: 0x0D7C */
       uint32_t RESERVED36[160];  /*!< Reserved                                                   Address offset: 0x0D80-0x0FFC */
  __IO uint32_t DMAMR;            /*!< DMA mode register                                          Address offset: 0x1000 */
  __IO uint32_t DMASBMR;          /*!< System bus mode register                                   Address offset: 0x1004 */
  __IO uint32_t DMAISR;           /*!< Interrupt status register                                  Address offset: 0x1008 */
  __IO uint32_t DMADSR;           /*!< Debug status register                                      Address offset: 0x100C */
       uint32_t RESERVED37[4];    /*!< Reserved                                                   Address offset: 0x1010-0x101C */
  __IO uint32_t DMAA4TXACR;       /*!< AXI4 transmit channel ACE control register                 Address offset: 0x1020 */
  __IO uint32_t DMAA4RXACR;       /*!< AXI4 receive channel ACE control register                  Address offset: 0x1024 */
  __IO uint32_t DMAA4DACR;        /*!< AXI4 descriptor ACE control register                       Address offset: 0x1028 */
       uint32_t RESERVED38[53];   /*!< Reserved                                                   Address offset: 0x102C-0x10FC */
  __IO uint32_t DMAC0CR;          /*!< Channel 0 control register                                 Address offset: 0x1100 */
  __IO uint32_t DMAC0TXCR;        /*!< Channel 0 transmit control register                        Address offset: 0x1104 */
  __IO uint32_t DMAC0RXCR;        /*!< Channel 0 receive control register                         Address offset: 0x1108 */
       uint32_t RESERVED39[2];    /*!< Reserved                                                   Address offset: 0x110C-0x1110 */
  __IO uint32_t DMAC0TXDLAR;      /*!< Channel 0 Tx descriptor list address register              Address offset: 0x1114 */
       uint32_t RESERVED40;       /*!< Reserved                                                   Address offset: 0x1118 */
  __IO uint32_t DMAC0RXDLAR;      /*!< Channel 0 Rx descriptor list address register              Address offset: 0x111C */
  __IO uint32_t DMAC0TXDTPR;      /*!< Channel 0 Tx descriptor tail pointer register              Address offset: 0x1120 */
       uint32_t RESERVED41;       /*!< Reserved                                                   Address offset: 0x1124 */
  __IO uint32_t DMAC0RXDTPR;      /*!< Channel 0 Rx descriptor tail pointer register              Address offset: 0x1128 */
  __IO uint32_t DMAC0TXRLR;       /*!< Channel 0 Tx descriptor ring length register               Address offset: 0x112C */
  __IO uint32_t DMAC0RXRLR;       /*!< Channel 0 Rx descriptor ring length register               Address offset: 0x1130 */
  __IO uint32_t DMAC0IER;         /*!< Channel 0 interrupt enable register                        Address offset: 0x1134 */
  __IO uint32_t DMAC0RXIWTR;      /*!< Channel 0 Rx interrupt watchdog timer register             Address offset: 0x1138 */
  __IO uint32_t DMAC0SFCSR;       /*!< Channel 0 slot function control status register            Address offset: 0x113C */
       uint32_t RESERVED42;       /*!< Reserved                                                   Address offset: 0x1140 */
  __IO uint32_t DMAC0CATXDR;      /*!< Channel 0 current application transmit descriptor register Address offset: 0x1144 */
       uint32_t RESERVED43;       /*!< Reserved                                                   Address offset: 0x1148 */
  __IO uint32_t DMAC0CARXDR;      /*!< Channel 0 current application receive descriptor register  Address offset: 0x114C */
       uint32_t RESERVED44;       /*!< Reserved                                                   Address offset: 0x1150 */
  __IO uint32_t DMAC0CATXBR;      /*!< Channel 0 current application transmit buffer register     Address offset: 0x1154 */
       uint32_t RESERVED45;       /*!< Reserved                                                   Address offset: 0x1158 */
  __IO uint32_t DMAC0CARXBR;      /*!< Channel 0 current application receive buffer register      Address offset: 0x115C */
  __IO uint32_t DMAC0SR;          /*!< Channel 0 status register                                  Address offset: 0x1160 */
       uint32_t RESERVED46[2];    /*!< Reserved                                                   Address offset: 0x1164-0x1168 */
  __IO uint32_t DMAC0MFCR;        /*!< Channel 0 missed frame count register                      Address offset: 0x116C */
       uint32_t RESERVED47[4];    /*!< Reserved                                                   Address offset: 0x1170-0x117C */
  __IO uint32_t DMAC1CR;          /*!< Channel 1 control register                                 Address offset: 0x1180 */
  __IO uint32_t DMAC1TXCR;        /*!< Channel 1 transmit control register                        Address offset: 0x1184 */
       uint32_t RESERVED48[3];    /*!< Reserved                                                   Address offset: 0x1188-0x1190 */
  __IO uint32_t DMAC1TXDLAR;      /*!< Channel 1 Tx descriptor list address register              Address offset: 0x1194 */
       uint32_t RESERVED49[2];    /*!< Reserved                                                   Address offset: 0x1198-0x119C */
  __IO uint32_t DMAC1TXDTPR;      /*!< Channel 1 Tx descriptor tail pointer register              Address offset: 0x11A0 */
       uint32_t RESERVED50[2];    /*!< Reserved                                                   Address offset: 0x11A4-0x11A8 */
  __IO uint32_t DMAC1TXRLR;       /*!< Channel 1 Tx descriptor ring length register               Address offset: 0x11AC */
       uint32_t RESERVED51;       /*!< Reserved                                                   Address offset: 0x11B0 */
  __IO uint32_t DMAC1IER;         /*!< Channel 1 interrupt enable register                        Address offset: 0x11B4 */
       uint32_t RESERVED52;       /*!< Reserved                                                   Address offset: 0x11B8 */
  __IO uint32_t DMAC1SFCSR;       /*!< Channel 1 slot function control status register            Address offset: 0x11BC */
       uint32_t RESERVED53;       /*!< Reserved                                                   Address offset: 0x11C0 */
  __IO uint32_t DMAC1CATXDR;      /*!< Channel 1 current application transmit descriptor register Address offset: 0x11C4 */
       uint32_t RESERVED54[3];    /*!< Reserved                                                   Address offset: 0x11C8-0x11D0 */
  __IO uint32_t DMAC1CATXBR;      /*!< Channel 1 current application transmit buffer register     Address offset: 0x11D4 */
       uint32_t RESERVED55[2];    /*!< Reserved                                                   Address offset: 0x11D8-0x11DC */
  __IO uint32_t DMAC1SR;          /*!< Channel 1 status register                                  Address offset: 0x11E0 */
       uint32_t RESERVED56[2];    /*!< Reserved                                                   Address offset: 0x11E4-0x11E8 */
  __IO uint32_t DMAC1MFCR;        /*!< Channel 1 missed frame count register                      Address offset: 0x11EC */
} ETH_TypeDef;

/**
  * @brief External Interrupt/Event Controller
  */

typedef struct
{
  __IO uint32_t RTSR1;               /*!< EXTI Rising trigger selection register,                   Address offset: 0x00 */
  __IO uint32_t FTSR1;               /*!< EXTI Falling trigger selection register,                  Address offset: 0x04 */
  __IO uint32_t SWIER1;              /*!< EXTI Software interrupt event register,                   Address offset: 0x08 */
  __IO uint32_t RPR1;                /*!< EXTI Rising Edge Pending mask register,                   Address offset: 0x0C */
  __IO uint32_t FPR1;                /*!< EXTI Falling Edge Pending mask register,                  Address offset: 0x10 */
  __IO uint32_t TZENR1;              /*!< EXTI Trust Zone enable register,                          Address offset: 0x14 */
  uint32_t      RESERVED1[2];        /*!< Reserved, offset 0x18 -> 0x20                                                  */
  __IO uint32_t RTSR2;               /*!< EXTI Rising trigger selection register,                   Address offset: 0x20 */
  __IO uint32_t FTSR2;               /*!< EXTI Falling trigger selection register,                  Address offset: 0x24 */
  __IO uint32_t SWIER2;              /*!< EXTI Software interrupt event register,                   Address offset: 0x28 */
  __IO uint32_t RPR2;                /*!< EXTI Rising Edge Pending mask register,                   Address offset: 0x2C */
  __IO uint32_t FPR2;                /*!< EXTI Falling Edge Pending mask register,                  Address offset: 0x30 */
  __IO uint32_t TZENR2;              /*!< EXTI Trust Zone enable register,                          Address offset: 0x34 */
  uint32_t      RESERVED2[2];        /*!< Reserved, offset 0x38 -> 0x40                                                  */
  __IO uint32_t RTSR3;               /*!< EXTI Rising trigger selection register,                   Address offset: 0x40 */
  __IO uint32_t FTSR3;               /*!< EXTI Falling trigger selection register,                  Address offset: 0x44 */
  __IO uint32_t SWIER3;              /*!< EXTI Software interrupt event register,                   Address offset: 0x48 */
  __IO uint32_t RPR3;                /*!< EXTI Rising Edge Pending mask register,                   Address offset: 0x4C */
  __IO uint32_t FPR3;                /*!< EXTI Falling Edge Pending mask register,                  Address offset: 0x50 */
  __IO uint32_t TZENR3;              /*!< EXTI Trust Zone enable register,                          Address offset: 0x54 */
  uint32_t      RESERVED3[2];        /*!< Reserved, offset 0x58 -> 0x5C                                                  */
  __IO uint32_t EXTICR[4];           /*!< EXTI Configuration Register mask register,                Address offset: 0x60 */
  uint32_t      RESERVED4[4];        /*!< Reserved, offset 0x70 -> 0x7C                                                  */
  __IO uint32_t C1IMR1;              /*!< EXTI wakeup with interrupt mask register for cpu1 [31:0], Address offset: 0x80 */
  __IO uint32_t RESERVED5[3];        /*!< Reserved,                                                 Address offset: 0x84 - 0x8C */
  __IO uint32_t C1IMR2;              /*!< EXTI wakeup with interrupt mask register for cpu1 [31:0], Address offset: 0x90 */
  __IO uint32_t RESERVED6[3];        /*!< Reserved,                                                 Address offset: 0x94 - 0x9C */
  __IO uint32_t C1IMR3;              /*!< EXTI wakeup with interrupt mask register for cpu1 [31:0], Address offset: 0xA0 */
  __IO uint32_t RESERVED7[7];        /*!< Reserved,                                                 Address offset: 0xA4 - 0xBC */
  __IO uint32_t C2IMR1;              /*!< EXTI wakeup with interrupt mask register for cpu2 [31:0], Address offset: 0xC0 */
  __IO uint32_t C2EMR1;              /*!< EXTI wakeup with event mask register for cpu2 [31:0],     Address offset: 0xC4 */
  __IO uint32_t RESERVED8[2];        /*!< Reserved,                                                 Address offset: 0xC8 - 0xCC */
  __IO uint32_t C2IMR2;              /*!< EXTI wakeup with interrupt mask register for cpu2 [31:0], Address offset: 0xD0 */
  __IO uint32_t C2EMR2;              /*!< EXTI wakeup with event mask register for cpu2 [31:0],     Address offset: 0xD4 */
  __IO uint32_t RESERVED9[2];        /*!< Reserved,                                                 Address offset: 0xD8 - 0xDC */
  __IO uint32_t C2IMR3;              /*!< EXTI wakeup with interrupt mask register for cpu2 [31:0], Address offset: 0xE0 */
  __IO uint32_t C2EMR3;              /*!< EXTI wakeup with event mask register for cpu2 [31:0],     Address offset: 0xE4 */
  uint32_t      RESERVED10[182];     /*!< Reserved, offset 0xE8 -> 0x3BC                                                 */
  __IO uint32_t HWCFGR13;            /*!< EXTI HW Configuration Register 13,                        Address offset: 0x3C0 */
  __IO uint32_t HWCFGR12;            /*!< EXTI HW Configuration Register 12,                        Address offset: 0x3C4 */
  __IO uint32_t HWCFGR11;            /*!< EXTI HW Configuration Register 11,                        Address offset: 0x3C8 */
  __IO uint32_t HWCFGR10;            /*!< EXTI HW Configuration Register 10,                        Address offset: 0x3CC */
  __IO uint32_t HWCFGR9;             /*!< EXTI HW Configuration Register 9,                         Address offset: 0x3D0 */
  __IO uint32_t HWCFGR8;             /*!< EXTI HW Configuration Register 8,                         Address offset: 0x3D4 */
  __IO uint32_t HWCFGR7;             /*!< EXTI HW Configuration Register 7,                         Address offset: 0x3D8 */
  __IO uint32_t HWCFGR6;             /*!< EXTI HW Configuration Register 6,                         Address offset: 0x3DC */
  __IO uint32_t HWCFGR5;             /*!< EXTI HW Configuration Register 5,                         Address offset: 0x3E0 */
  __IO uint32_t HWCFGR4;             /*!< EXTI HW Configuration Register 4,                         Address offset: 0x3E4 */
  __IO uint32_t HWCFGR3;             /*!< EXTI HW Configuration Register 3,                         Address offset: 0x3E8 */
  __IO uint32_t HWCFGR2;             /*!< EXTI HW Configuration Register 2,                         Address offset: 0x3EC */
  __IO uint32_t HWCFGR1;             /*!< EXTI HW Configuration Register 1,                         Address offset: 0x3F0 */
  __IO uint32_t VERR;                /*!< EXTI Version Register ,                                   Address offset: 0x3F4 */
  __IO uint32_t IPIDR;               /*!< EXTI Identification Register ,                            Address offset: 0x3F8 */
  __IO uint32_t SIDR;                /*!< EXTI Size ID Register ,                                   Address offset: 0x3FC */

}EXTI_TypeDef;

typedef struct
{
  __IO uint32_t IMR1;                /*!< EXTI Interrupt mask register,                Address offset: 0x00 */
  __IO uint32_t EMR1;                /*!< EXTI Event mask register,                    Address offset: 0x04 */
  uint32_t      RESERVED1[2];        /*!< Reserved, offset 0x08 -> 0x10                                     */
  __IO uint32_t IMR2;                /*!< EXTI Interrupt mask register,                Address offset: 0x10 */
  __IO uint32_t EMR2;                /*!< EXTI Event mask register,                    Address offset: 0x14 */
  uint32_t      RESERVED2[2];        /*!< Reserved, offset 0x18 -> 0x20                                     */
  __IO uint32_t IMR3;                /*!< EXTI Interrupt mask register,                Address offset: 0x20 */
  __IO uint32_t EMR3;                /*!< EXTI Event mask register,                    Address offset: 0x24 */
  uint32_t      RESERVED3[6];        /*!< Reserved, offset 0x28 -> 0x40                                     */
}EXTI_Core_TypeDef;


/**
  * @brief Flexible Memory Controller
  */

typedef struct
{
  __IO uint32_t BTCR[8];    /*!< NOR/PSRAM chip-select control register(BCR) and chip-select timing register(BTR), Address offset: 0x00-1C */
  __IO uint32_t PCSCNTR;    /*!< PSRAM chip-select counter register(PCSCNTR),                                      Address offset: 0x20 */
} FMC_Bank1_TypeDef;

/**
  * @brief Flexible Memory Controller Bank1E
  */

typedef struct
{
  __IO uint32_t BWTR[7];    /*!< NOR/PSRAM write timing registers, Address offset: 0x104-0x11C */
} FMC_Bank1E_TypeDef;

/**
  * @brief Flexible Memory Controller Bank3
  */

typedef struct
{
  __IO uint32_t PCR;         /*!< NAND Flash control register 3,                       Address offset: 0x80 */
  __IO uint32_t SR;          /*!< NAND Flash FIFO status and interrupt register 3,     Address offset: 0x84 */
  __IO uint32_t PMEM;        /*!< NAND Flash Common memory space timing register 3,    Address offset: 0x88 */
  __IO uint32_t PATT;        /*!< NAND Flash Attribute memory space timing register 3, Address offset: 0x8C */
  __IO uint32_t HPR;         /*!< NAND Flash Hamming Parity result registers 3,        Address offset: 0x90 */
  __IO uint32_t HECCR;       /*!< NAND Flash Hamming ECC result registers 3,           Address offset: 0x94 */
  uint32_t RESERVED[110];    /*!< Reserved, 0x94->0x250 */
  __IO uint32_t BCHIER;      /*!< BCH Interrupt Enable Register,                       Address offset: 0x250 */
  __IO uint32_t BCHISR;      /*!< BCH Interrupt Status Register,                       Address offset: 0x254 */
  __IO uint32_t BCHICR;      /*!< BCH Interrupt Clear Register,                        Address offset: 0x258 */
  uint32_t RESERVED1;        /*!< Reserved, 0x25C */
  __IO uint32_t BCHPBR1;     /*!< BCH Parity Bits Register 1,                          Address offset: 0x260 */
  __IO uint32_t BCHPBR2;     /*!< BCH Parity Bits Register 2,                          Address offset: 0x264 */
  __IO uint32_t BCHPBR3;     /*!< BCH Parity Bits Register 3,                          Address offset: 0x268 */
  __IO uint32_t BCHPBR4;     /*!< BCH Parity Bits Register 4,                          Address offset: 0x26C */
  uint32_t RESERVED2[3];        /*!< Reserved, 0x25C */
  __IO uint32_t BCHDSR0;     /*!< BCH Decoder Status Register 0,                       Address offset: 0x27C */
  __IO uint32_t BCHDSR1;     /*!< BCH Decoder Status Register 1,                       Address offset: 0x280 */
  __IO uint32_t BCHDSR2;     /*!< BCH Decoder Status Register 2,                       Address offset: 0x284 */
  __IO uint32_t BCHDSR3;     /*!< BCH Decoder Status Register 3,                       Address offset: 0x288 */
  __IO uint32_t BCHDSR4;     /*!< BCH Decoder Status Register 4,                       Address offset: 0x28C */
  uint32_t RESERVED3[87];    /*!< Reserved, 0x28C->0x3EC */
  __IO uint32_t HWCFGR2;     /*!< FMC HW Configuration register 2,                     Address offset: 0x3EC */
  __IO uint32_t HWCFGR1;     /*!< FMC HW Configuration register 1,                     Address offset: 0x3F0 */
  __IO uint32_t VERR;        /*!< FMC Version register ,                               Address offset: 0x3F4 */
  __IO uint32_t IDR;         /*!< FMC Identification register ,                        Address offset: 0x3F8 */
  __IO uint32_t SIDR;        /*!< FMC Size ID register ,                               Address offset: 0x3FC */
} FMC_Bank3_TypeDef;


/**
  * @brief General Purpose I/O
  */

typedef struct
{
  __IO uint32_t MODER;           /*!< GPIO port mode register,                      Address offset: 0x000 */
  __IO uint32_t OTYPER;          /*!< GPIO port output type register,               Address offset: 0x004 */
  __IO uint32_t OSPEEDR;         /*!< GPIO port output speed register,              Address offset: 0x008 */
  __IO uint32_t PUPDR;           /*!< GPIO port pull-up/pull-down register,         Address offset: 0x00C */
  __IO uint32_t IDR;             /*!< GPIO port input data register,                Address offset: 0x010 */
  __IO uint32_t ODR;             /*!< GPIO port output data register,               Address offset: 0x014 */
  __IO uint32_t BSRR;            /*!< GPIO port bit set/reset register,             Address offset: 0x018 */
  __IO uint32_t LCKR;            /*!< GPIO port configuration lock register,        Address offset: 0x01C */
  __IO uint32_t AFR[2];          /*!< GPIO alternate function registers,            Address offset: 0x020-0x024 */
  __IO uint32_t BRR;             /*!< GPIO port bit reset register,                 Address offset: 0x028 */
       uint32_t RESERVED0;       /*!< Reserved,                                     Address offset: 0x02C */
  __IO uint32_t SECCFGR;         /*!< GPIO secure configuration register for GPIOZ, Address offset: 0x030 */
       uint32_t RESERVED1[229];  /*!< Reserved,                                     Address offset: 0x034-0x3C4 */
  __IO uint32_t HWCFGR10;        /*!< GPIO hardware configuration register 10,      Address offset: 0x3C8 */
  __IO uint32_t HWCFGR9;         /*!< GPIO hardware configuration register 9,       Address offset: 0x3CC */
  __IO uint32_t HWCFGR8;         /*!< GPIO hardware configuration register 8,       Address offset: 0x3D0 */
  __IO uint32_t HWCFGR7;         /*!< GPIO hardware configuration register 7,       Address offset: 0x3D4 */
  __IO uint32_t HWCFGR6;         /*!< GPIO hardware configuration register 6,       Address offset: 0x3D8 */
  __IO uint32_t HWCFGR5;         /*!< GPIO hardware configuration register 5,       Address offset: 0x3DC */
  __IO uint32_t HWCFGR4;         /*!< GPIO hardware configuration register 4,       Address offset: 0x3E0 */
  __IO uint32_t HWCFGR3;         /*!< GPIO hardware configuration register 3,       Address offset: 0x3E4 */
  __IO uint32_t HWCFGR2;         /*!< GPIO hardware configuration register 2,       Address offset: 0x3E8 */
  __IO uint32_t HWCFGR1;         /*!< GPIO hardware configuration register 1,       Address offset: 0x3EC */
  __IO uint32_t HWCFGR0;         /*!< GPIO hardware configuration register 0,       Address offset: 0x3F0 */
  __IO uint32_t VERR;            /*!< GPIO version register,                        Address offset: 0x3F4 */
  __IO uint32_t IPIDR;           /*!< GPIO identification register,                 Address offset: 0x3F8 */
  __IO uint32_t SIDR;            /*!< GPIO size identification register,            Address offset: 0x3FC */
} GPIO_TypeDef;


/**
  * @brief System configuration controller
  */

typedef struct
{
  __IO uint32_t BOOTR;          /*!< SYSCFG Boot pin control register,                                Address offset: 0x00        */
  __IO uint32_t PMCSETR;        /*!< SYSCFG Peripheral Mode configuration set register,               Address offset: 0x04        */
       uint32_t RESERVED1[4];   /*!< Reserved,                                                        Address offset: 0x08-0x14   */
  __IO uint32_t IOCTRLSETR;     /*!< SYSCFG ioctl set register,                                       Address offset: 0x18        */
  __IO uint32_t ICNR;           /*!< SYSCFG interconnect control register,                            Address offset: 0x1C        */
  __IO uint32_t CMPCR;          /*!< SYSCFG compensation cell control register,                       Address offset: 0x20        */
  __IO uint32_t CMPENSETR;      /*!< SYSCFG compensation cell enable set register,                    Address offset: 0x24        */
  __IO uint32_t CMPENCLRR;      /*!< SYSCFG compensation cell enable clear register,                  Address offset: 0x28        */
  __IO uint32_t CBR;            /*!< SYSCFG control timer break register,                             Address offset: 0x2C        */
       uint32_t RESERVED2[5];   /*!< Reserved,                                                        Address offset: 0x30-0x40   */
  __IO uint32_t PMCCLRR;        /*!< SYSCFG Peripheral Mode configuration clear register,             Address offset: 0x44        */
       uint32_t RESERVED3[4];   /*!< Reserved,                                                        Address offset: 0x48-0x54   */
  __IO uint32_t IOCTRLCLRR;     /*!< SYSCFG ioctl clear register,                                     Address offset: 0x58        */
       uint32_t RESERVED4[230]; /*!< Reserved,                                                        Address offset: 0x5C-0x3F0  */
  __IO uint32_t VERR;           /*!< SYSCFG version register,                                         Address offset: 0x3F4       */
  __IO uint32_t IPIDR;          /*!< SYSCFG ID register,                                              Address offset: 0x3F8       */
  __IO uint32_t SIDR;           /*!< SYSCFG magic ID register,                                        Address offset: 0x3FC       */
} SYSCFG_TypeDef;


/**
  * @briefVoltage reference buffer
  */
typedef struct
{
  __IO uint32_t CSR;                /*VREF control and status register                      Address offset: 0x00      */
  __IO uint32_t CCR;                /*VREF control and status register                      Address offset: 0x04      */
} VREF_TypeDef;


/**
  * @brief Inter-integrated Circuit Interface
  */

typedef struct
{
  __IO uint32_t CR1;      /*!< I2C Control register 1,            Address offset: 0x00 */
  __IO uint32_t CR2;      /*!< I2C Control register 2,            Address offset: 0x04 */
  __IO uint32_t OAR1;     /*!< I2C Own address 1 register,        Address offset: 0x08 */
  __IO uint32_t OAR2;     /*!< I2C Own address 2 register,        Address offset: 0x0C */
  __IO uint32_t TIMINGR;  /*!< I2C Timing register,               Address offset: 0x10 */
  __IO uint32_t TIMEOUTR; /*!< I2C Timeout register,              Address offset: 0x14 */
  __IO uint32_t ISR;      /*!< I2C Interrupt and status register, Address offset: 0x18 */
  __IO uint32_t ICR;      /*!< I2C Interrupt clear register,      Address offset: 0x1C */
  __IO uint32_t PECR;     /*!< I2C PEC register,                  Address offset: 0x20 */
  __IO uint32_t RXDR;     /*!< I2C Receive data register,         Address offset: 0x24 */
  __IO uint32_t TXDR;     /*!< I2C Transmit data register,        Address offset: 0x28 */
  uint32_t RESERVED[241]; /*!< Reserved, 0x2C->0x3F0 */
  __IO uint32_t HWCFGR;   /*!< I2C hardware configuration register,  Address offset: 0x3F0 */
  __IO uint32_t VERR;     /*!< I2C version register,                 Address offset: 0x3F4 */
  __IO uint32_t IPIDR;    /*!< I2C identification register,          Address offset: 0x3F8 */
  __IO uint32_t SIDR;     /*!< I2C size identification register,     Address offset: 0x3FC */
} I2C_TypeDef;

/**
  * @brief Independent WATCHDOG
  */

typedef struct
{
  __IO uint32_t KR;   /*!< IWDG Key register,                          Address offset: 0x00 */
  __IO uint32_t PR;   /*!< IWDG Prescaler register,                    Address offset: 0x04 */
  __IO uint32_t RLR;  /*!< IWDG Reload register,                       Address offset: 0x08 */
  __IO uint32_t SR;   /*!< IWDG Status register,                       Address offset: 0x0C */
  __IO uint32_t WINR; /*!< IWDG Window register,                       Address offset: 0x10 */
  __IO uint32_t EWCR; /*!< IWDG Window register,                       Address offset: 0x14 */
  uint32_t RESERVED[246]; /*!< Reserved,                                        0x18->0x3EC */
  __IO uint32_t HWCFGR;   /*!< IWDG hardware configuration register,  Address offset: 0x3F0 */
  __IO uint32_t VERR;     /*!< IWDG version register,                 Address offset: 0x3F4 */
  __IO uint32_t IDR;    /*!< IWDG identification register,            Address offset: 0x3F8 */
  __IO uint32_t SIDR;     /*!< IWDG size identification register,     Address offset: 0x3FC */
} IWDG_TypeDef;


/**
  * @brief JPEG Codec
  */
typedef struct
{
  __IO uint32_t CONFR0;          /*!< JPEG Codec Control Register (JPEG_CONFR0),        Address offset: 00h       */
  __IO uint32_t CONFR1;          /*!< JPEG Codec Control Register (JPEG_CONFR1),        Address offset: 04h       */
  __IO uint32_t CONFR2;          /*!< JPEG Codec Control Register (JPEG_CONFR2),        Address offset: 08h       */
  __IO uint32_t CONFR3;          /*!< JPEG Codec Control Register (JPEG_CONFR3),        Address offset: 0Ch       */
  __IO uint32_t CONFR4;          /*!< JPEG Codec Control Register (JPEG_CONFR4),        Address offset: 10h       */
  __IO uint32_t CONFR5;          /*!< JPEG Codec Control Register (JPEG_CONFR5),        Address offset: 14h       */
  __IO uint32_t CONFR6;          /*!< JPEG Codec Control Register (JPEG_CONFR6),        Address offset: 18h       */
  __IO uint32_t CONFR7;          /*!< JPEG Codec Control Register (JPEG_CONFR7),        Address offset: 1Ch       */
  uint32_t  Reserved20[4];       /* Reserved                                            Address offset: 20h-2Ch   */
  __IO uint32_t CR;              /*!< JPEG Control Register (JPEG_CR),                  Address offset: 30h       */
  __IO uint32_t SR;              /*!< JPEG Status Register (JPEG_SR),                   Address offset: 34h       */
  __IO uint32_t CFR;             /*!< JPEG Clear Flag Register (JPEG_CFR),              Address offset: 38h       */
  uint32_t  Reserved3c;          /* Reserved                                            Address offset: 3Ch       */
  __IO uint32_t DIR;             /*!< JPEG Data Input Register (JPEG_DIR),              Address offset: 40h       */
  __IO uint32_t DOR;             /*!< JPEG Data Output Register (JPEG_DOR),             Address offset: 44h       */
  uint32_t  Reserved48[2];       /* Reserved                                            Address offset: 48h-4Ch   */
  __IO uint32_t QMEM0[16];       /*!< JPEG quantization tables 0,                       Address offset: 50h-8Ch   */
  __IO uint32_t QMEM1[16];       /*!< JPEG quantization tables 1,                       Address offset: 90h-CCh   */
  __IO uint32_t QMEM2[16];       /*!< JPEG quantization tables 2,                       Address offset: D0h-10Ch  */
  __IO uint32_t QMEM3[16];       /*!< JPEG quantization tables 3,                       Address offset: 110h-14Ch */
  __IO uint32_t HUFFMIN[16];     /*!< JPEG HuffMin tables,                              Address offset: 150h-18Ch */
  __IO uint32_t HUFFBASE[32];    /*!< JPEG HuffSymb tables,                             Address offset: 190h-20Ch */
  __IO uint32_t HUFFSYMB[84];    /*!< JPEG HUFFSYMB tables,                             Address offset: 210h-35Ch */
  __IO uint32_t DHTMEM[103];     /*!< JPEG DHTMem tables,                               Address offset: 360h-4F8h */
  uint32_t  Reserved4FC;         /* Reserved                                            Address offset: 4FCh      */
  __IO uint32_t HUFFENC_AC0[88]; /*!< JPEG encodor, AC Huffman table 0,                 Address offset: 500h-65Ch */
  __IO uint32_t HUFFENC_AC1[88]; /*!< JPEG encodor, AC Huffman table 1,                 Address offset: 660h-7BCh */
  __IO uint32_t HUFFENC_DC0[8];  /*!< JPEG encodor, DC Huffman table 0,                 Address offset: 7C0h-7DCh */
  __IO uint32_t HUFFENC_DC1[8];  /*!< JPEG encodor, DC Huffman table 1,                 Address offset: 7E0h-7FCh */

} JPEG_TypeDef;


/**
  * @brief LCD
  */

typedef struct
{
  __IO uint32_t CR;        /*!< LCD control register,              Address offset: 0x00 */
  __IO uint32_t FCR;       /*!< LCD frame control register,        Address offset: 0x04 */
  __IO uint32_t SR;        /*!< LCD status register,               Address offset: 0x08 */
  __IO uint32_t CLR;       /*!< LCD clear register,                Address offset: 0x0C */
  uint32_t RESERVED;       /*!< Reserved,                          Address offset: 0x10 */
  __IO uint32_t RAM[16];   /*!< LCD display memory,           Address offset: 0x14-0x50 */
} LCD_TypeDef;

/**
  * @brief LCD-TFT Display Controller
  */

typedef struct
{
  uint32_t      RESERVED0[2];  /*!< Reserved, 0x00-0x04 */
  __IO uint32_t SSCR;          /*!< LTDC Synchronization Size Configuration Register,    Address offset: 0x08 */
  __IO uint32_t BPCR;          /*!< LTDC Back Porch Configuration Register,              Address offset: 0x0C */
  __IO uint32_t AWCR;          /*!< LTDC Active Width Configuration Register,            Address offset: 0x10 */
  __IO uint32_t TWCR;          /*!< LTDC Total Width Configuration Register,             Address offset: 0x14 */
  __IO uint32_t GCR;           /*!< LTDC Global Control Register,                        Address offset: 0x18 */
  uint32_t      RESERVED1[2];  /*!< Reserved, 0x1C-0x20 */
  __IO uint32_t SRCR;          /*!< LTDC Shadow Reload Configuration Register,           Address offset: 0x24 */
  uint32_t      RESERVED2[1];  /*!< Reserved, 0x28 */
  __IO uint32_t BCCR;          /*!< LTDC Background Color Configuration Register,        Address offset: 0x2C */
  uint32_t      RESERVED3[1];  /*!< Reserved, 0x30 */
  __IO uint32_t IER;           /*!< LTDC Interrupt Enable Register,                      Address offset: 0x34 */
  __IO uint32_t ISR;           /*!< LTDC Interrupt Status Register,                      Address offset: 0x38 */
  __IO uint32_t ICR;           /*!< LTDC Interrupt Clear Register,                       Address offset: 0x3C */
  __IO uint32_t LIPCR;         /*!< LTDC Line Interrupt Position Configuration Register, Address offset: 0x40 */
  __IO uint32_t CPSR;          /*!< LTDC Current Position Status Register,               Address offset: 0x44 */
  __IO uint32_t CDSR;         /*!< LTDC Current Display Status Register,                       Address offset: 0x48 */
} LTDC_TypeDef;

/**
  * @brief LCD-TFT Display layer x Controller
  */

typedef struct
{
  __IO uint32_t CR;            /*!< LTDC Layerx Control Register                                  Address offset: 0x84 */
  __IO uint32_t WHPCR;         /*!< LTDC Layerx Window Horizontal Position Configuration Register Address offset: 0x88 */
  __IO uint32_t WVPCR;         /*!< LTDC Layerx Window Vertical Position Configuration Register   Address offset: 0x8C */
  __IO uint32_t CKCR;          /*!< LTDC Layerx Color Keying Configuration Register               Address offset: 0x90 */
  __IO uint32_t PFCR;          /*!< LTDC Layerx Pixel Format Configuration Register               Address offset: 0x94 */
  __IO uint32_t CACR;          /*!< LTDC Layerx Constant Alpha Configuration Register             Address offset: 0x98 */
  __IO uint32_t DCCR;          /*!< LTDC Layerx Default Color Configuration Register              Address offset: 0x9C */
  __IO uint32_t BFCR;          /*!< LTDC Layerx Blending Factors Configuration Register           Address offset: 0xA0 */
  uint32_t      RESERVED0[2];  /*!< Reserved */
  __IO uint32_t CFBAR;         /*!< LTDC Layerx Color Frame Buffer Address Register               Address offset: 0xAC */
  __IO uint32_t CFBLR;         /*!< LTDC Layerx Color Frame Buffer Length Register                Address offset: 0xB0 */
  __IO uint32_t CFBLNR;        /*!< LTDC Layerx ColorFrame Buffer Line Number Register            Address offset: 0xB4 */
  uint32_t      RESERVED1[3];  /*!< Reserved */
  __IO uint32_t CLUTWR;         /*!< LTDC Layerx CLUT Write Register                               Address offset: 0x144 */

} LTDC_Layer_TypeDef;


/**
  * @brief USBPHYC  USB HS PHY Control
  */
typedef struct
{
  __IO uint32_t PLL;                       /*!< USBPHYC PLL control register,               Address offset: 0x000 */
  uint32_t RESERVED0;                      /*! Reserved                                     Address offset: 0x004 */
  __IO uint32_t MISC;                      /*!< USBPHYC Misc Control register,              Address offset: 0x008 */
  uint32_t RESERVED1[250] ;                /*! Reserved                              Address offset: 0x00C - 0x3F0*/
  __IO uint32_t VERR;                      /*!< USBPHYC Version register,                   Address offset: 0x3F4 */
  __IO uint32_t IPIDR;                     /*!< USBPHYC Identification register,            Address offset: 0x3F8 */
  __IO uint32_t SIDR;                      /*!< USBPHYC Size ID register,                   Address offset: 0x3FC */
}USBPHYC_GlobalTypeDef;


/**
  * @brief USBPHYC  USB HS PHY Control PHYx
  */
typedef struct
{
  uint32_t RESERVED0[3];                   /*! Reserved                              Address offset: 0x000 - 0x008 */
  __IO uint32_t TUNE;                     /*!< USBPHYC x TUNE register  ter,                Address offset: 0x00C */
}USBPHYC_InstanceTypeDef;


/**
  * @brief TZC TrustZone Address Space Controller for DDR
  */
typedef struct
{
  __IO uint32_t BUILD_CONFIG;       /*!< Build config register,               Address offset: 0x00 */
  __IO uint32_t ACTION;             /*!< Action register,                     Address offset: 0x04 */
  __IO uint32_t GATE_KEEPER;        /*!< Gate keeper register,                Address offset: 0x08 */
  __IO uint32_t SPECULATION_CTRL;   /*!< Speculation control register,        Address offset: 0x0C */
  uint8_t RESERVED0[0x100 - 0x10];
  __IO uint32_t REG_BASE_LOWO;      /*!< Region 0 base address low register,  Address offset: 0x100 */
  __IO uint32_t REG_BASE_HIGHO;     /*!< Region 0 base address high register, Address offset: 0x104 */
  __IO uint32_t REG_TOP_LOWO;       /*!< Region 0 top address low register,   Address offset: 0x108 */
  __IO uint32_t REG_TOP_HIGHO;      /*!< Region 0 top address high register,  Address offset: 0x10C */
  __IO uint32_t REG_ATTRIBUTESO;    /*!< Region 0 attribute register,         Address offset: 0x110 */
  __IO uint32_t REG_ID_ACCESSO;     /*!< Region 0 ID access register,         Address offset: 0x114 */
  /* @TODO : TypeDef to be compleated if needed*/
}TZC_TypeDef;



/**
  * @brief TZPC TrustZone Protection Controller
  */
typedef struct
{
  __IO uint32_t   TZMA0_SIZE;         /*!<TZPC ROM Secure Size Definition register,             Address offset: 0x00 */
  __IO uint32_t   TZMA1_SIZE;         /*!<TZPC SYSRAM Secure Size Definition register,          Address offset: 0x04 */
  uint32_t        RESERVED0[2];       /*!< Reserved */
  __IO uint32_t   DECPROT0;           /*!<TZPC Securable peripheral definition register 0,      Address offset: 0x10 */
  __IO uint32_t   DECPROT1;           /*!<TZPC Securable peripheral definition register 1,      Address offset: 0x14 */
  __IO uint32_t   DECPROT2;           /*!<TZPC Securable peripheral definition register 2,      Address offset: 0x18 */
  __IO uint32_t   DECPROT3;           /*!<TZPC Securable peripheral definition register 3,      Address offset: 0x1C */
  __IO uint32_t   DECPROT4;           /*!<TZPC Securable peripheral definition register 4,      Address offset: 0x20 */
  __IO uint32_t   DECPROT5;           /*!<TZPC Securable peripheral definition register 5,      Address offset: 0x24 */
  uint32_t        RESERVED1[2];       /*!< Reserved */
  __IO uint32_t   DECPROT_LOCK0;      /*!<TZPC Securable lock of security register 0,           Address offset: 0x30 */
  __IO uint32_t   DECPROT_LOCK1;      /*!<TZPC Securable lock of security register 1,           Address offset: 0x34 */
  __IO uint32_t   DECPROT_LOCK2;      /*!<TZPC Securable lock of security register 2,           Address offset: 0x38 */
  uint32_t        RESERVED2[237];     /*!< Reserved */
  __IO uint32_t   HWCFGR;             /*!< TZPC IP HW configuration register                    Address offset:0x3F0  */
  __IO uint32_t   IP_VER;             /*!< TZPC IP version register                             Address offset:0x3F4  */
  __IO uint32_t   ID;                 /*!< TZPC IP version register                             Address offset:0x3F8  */
  __IO uint32_t   SID;                /*!< TZPC IP version register                             Address offset:0x3FC  */
}TZPC_TypeDef;



/**
  * @brief STGENC System Generic Counter Control
  */
typedef struct
{
  __IO uint32_t CNTCR;          /*!< STGENC Counter Control Register,              Address offset: 0x000 */
       uint32_t CNTSR;          /*!< STGENC Counter Status Register,               Address offset: 0x004 */
  __IO uint32_t CNTCVL;         /*!< STGENC Current Counter Value Lower Register,  Address offset: 0x008 */
  __IO uint32_t CNTCVU;         /*!< STGENC Current Counter Value Upper Register,  Address offset: 0x00C */
       uint32_t RESERVED1[4];                         /*!< Reserved, Address offsets: 0x010-0x01C */
  __IO uint32_t CNTFID0;        /*!< STGENC Base Frequency ID Register,            Address offset: 0x020 */
       uint32_t RESERVED2[1003];                      /*!< Reserved, Address offsets: 0x024-0xFCC */
  __IO uint32_t PIDR4;          /*!< STGENC Peripheral ID4 Register,               Address offset: 0xFD0 */
  __IO uint32_t RESERVED3[3];                         /*!< Reserved, Address offsets: 0xFD4-0xFDC */
  __IO uint32_t PIDR[4];        /*!< STGENC Peripheral ID0-ID3 Registers,          Address offset: 0xFE0 */
  __IO uint32_t CIDR[4];        /*!< STGENC Component ID0-ID3 Registers,           Address offset: 0xFF0 */
}STGENC_TypeDef;

/**
  * @brief STGENR System Timestamp Generator Read
  */
typedef struct
{
  __IO uint32_t CNTCVL;  /*!< STGENR Current Counter Value Lower Register,  Address offset: 0x000 */
  __IO uint32_t CNTCVU;  /*!< STGENR Current Counter Value Upper Register,  Address offset: 0x004 */
       uint32_t RESERVED1[1010];                      /*!< Reserved, Address offsets: 0x008-0xFCC */
  __IO uint32_t PIDR4;   /*!< STGENR Peripheral ID4 Register,               Address offset: 0xFD0 */
  __IO uint32_t RESERVED2[3];                         /*!< Reserved, Address offsets: 0xFD4-0xFDC */
  __IO uint32_t PIDR[4]; /*!< STGENR Peripheral ID0-ID3 Registers,          Address offset: 0xFE0 */
  __IO uint32_t CIDR[4]; /*!< STGENR Component ID0-ID3 Registers,           Address offset: 0xFF0 */
} STGENR_TypeDef;
 
 
/**
  * @brief Firewall
  */

typedef struct
{
  __IO uint32_t CSSA;     /*!< Code Segment Start Address register,              Address offset: 0x00 */
  __IO uint32_t CSL;      /*!< Code Segment Length register,                      Address offset: 0x04 */
  __IO uint32_t NVDSSA;   /*!< NON volatile data Segment Start Address register,  Address offset: 0x08 */
  __IO uint32_t NVDSL;    /*!< NON volatile data Segment Length register,         Address offset: 0x0C */
  __IO uint32_t VDSSA ;   /*!< Volatile data Segment Start Address register,      Address offset: 0x10 */
  __IO uint32_t VDSL ;    /*!< Volatile data Segment Length register,             Address offset: 0x14 */
  __IO uint32_t CR ;      /*!< Configuration  register,                           Address offset: 0x20 */

} FIREWALL_TypeDef;

/**
  * @brief Power Control
  */

typedef struct
{
  __IO uint32_t CR1;              /*!< PWR control register 1,                   Address offset: 0x00 */
  __IO uint32_t CSR1;             /*!< PWR control status register 1,            Address offset: 0x04 */
  __IO uint32_t CR2;              /*!< PWR control register 2,                   Address offset: 0x08 */
  __IO uint32_t CR3;              /*!< PWR control register 3,                   Address offset: 0x0C */
  __IO uint32_t MPUCR;            /*!< PWR MPU control register,                 Address offset: 0x10 */
  __IO uint32_t MCUCR;            /*!< PWR MCU control register,                 Address offset: 0x14 */
       uint32_t RESERVED0[2];     /*!< Reserved, 0x18-0x1C                       Address offset: 0x18 */
  __IO uint32_t WKUPCR;           /*!< PWR wakeup clear register,                Address offset: 0x20 */
  __IO uint32_t WKUPFR;           /*!< PWR wakeup flag register,                 Address offset: 0x24 */
  __IO uint32_t MPUWKUPENR;       /*!< PWR wakeup enable and polarity register,  Address offset: 0x28 */
  __IO uint32_t MCUWKUPENR;       /*!< PWR wakeup enable and polarity register,  Address offset: 0x2C */
       uint32_t RESERVED1[241];   /*!< Reserved, 0x30-0x3F0                      Address offset: 0x30 */
  __IO uint32_t VER;              /*!< PWR IP version register,                  Address offset: 0x3F4 */
  __IO uint32_t ID;               /*!< PWR IP identification register,           Address offset: 0x3F8 */
  __IO uint32_t SID;              /*!< PWR size ID register,                     Address offset: 0x3FC */
} PWR_TypeDef;


/**
  * @brief Reset and Clock Control
  */

typedef struct
{
  __IO uint32_t TZCR;                      /*!< RCC TrustZone Control Register                       Address offset: 0x00 */
       uint32_t RESERVED0[2];              /*!< Reserved, 0x04-0x08                                  Address offset: 0x04 */
  __IO uint32_t OCENSETR;                  /*!< RCC Oscillator Clock Enable Set Register             Address offset: 0x0C */
  __IO uint32_t OCENCLRR;                  /*!< RCC Oscillator Enable Control Clear Register         Address offset: 0x10 */
       uint32_t RESERVED1;                 /*!< Reserved,                                            Address offset: 0x14 */
  __IO uint32_t HSICFGR;                   /*!< RCC HSI Configuration Register                       Address offset: 0x18 */
  __IO uint32_t CSICFGR;                   /*!< RCC CSI Configuration Register                       Address offset: 0x1C */
  __IO uint32_t MPCKSELR;                  /*!< RCC MPU Clock Selection Register                     Address offset: 0x20 */
  __IO uint32_t ASSCKSELR;                 /*!< RCC AXI Sub-System Clock Selection Register          Address offset: 0x24 */
  __IO uint32_t RCK12SELR;                 /*!< RCC PLL 1 and 2 Ref. Clock Selection Register        Address offset: 0x28 */
  __IO uint32_t MPCKDIVR;                  /*!< RCC MPU Clock Divider Register                       Address offset: 0x2C */
  __IO uint32_t AXIDIVR;                   /*!< RCC AXI Clock Divider Register                       Address offset: 0x30 */
       uint32_t RESERVED2[2];              /*!< Reserved, 0x34-0x38                                  Address offset: 0x34 */
  __IO uint32_t APB4DIVR;                  /*!< RCC APB4 Clock Divider Register                      Address offset: 0x3C */
  __IO uint32_t APB5DIVR;                  /*!< RCC APB5 Clock Divider Register                      Address offset: 0x40 */
  __IO uint32_t RTCDIVR;                   /*!< RCC RTC Clock Division Register                      Address offset: 0x44 */
  __IO uint32_t MSSCKSELR;                 /*!< RCC MCU Sub-System Clock Selection Register          Address offset: 0x48 */
       uint32_t RESERVED3[13];             /*!< Reserved, 0x4C-0x7C                                  Address offset: 0x4C */
  __IO uint32_t PLL1CR;                    /*!< RCC PLL1 Control Register                            Address offset: 0x80 */
  __IO uint32_t PLL1CFGR1;                 /*!< RCC PLL1 Configuration Register 1                    Address offset: 0x84 */
  __IO uint32_t PLL1CFGR2;                 /*!< RCC PLL1 Configuration Register 2                    Address offset: 0x88 */
  __IO uint32_t PLL1FRACR;                 /*!< RCC PLL1 Fractional Register                         Address offset: 0x8C */
  __IO uint32_t PLL1CSGR;                  /*!< RCC PLL1 Clock Spreading Generator Register          Address offset: 0x90 */
  __IO uint32_t PLL2CR;                    /*!< RCC PLL2 Control Register                            Address offset: 0x94 */
  __IO uint32_t PLL2CFGR1;                 /*!< RCC PLL2 Configuration Register 1                    Address offset: 0x98 */
  __IO uint32_t PLL2CFGR2;                 /*!< RCC PLL2 Configuration Register 2                    Address offset: 0x9C */
  __IO uint32_t PLL2FRACR;                 /*!< RCC PLL2 Fractional Register                         Address offset: 0xA0 */
  __IO uint32_t PLL2CSGR;                  /*!< RCC PLL2 Clock Spreading Generator Register          Address offset: 0xA4 */
       uint32_t RESERVED4[6];              /*!< Reserved, 0xA8-0xBC                                  Address offset: 0xA8 */
  __IO uint32_t I2C46CKSELR;               /*!< RCC I2C46 Kernel Clock Selection Register            Address offset: 0xC0 */
  __IO uint32_t SPI6CKSELR;                /*!< RCC SPI6 Kernel Clock Selection Register             Address offset: 0xC4 */
  __IO uint32_t UART1CKSELR;               /*!< RCC USART1 Kernel Clock Selection Register           Address offset: 0xC8 */
  __IO uint32_t RNG1CKSELR;                /*!< RCC RNG1 Kernel Clock Selection Register             Address offset: 0xCC */
  __IO uint32_t CPERCKSELR;                /*!< RCC Common Peripheral Clock Selection Register       Address offset: 0xD0 */
  __IO uint32_t STGENCKSELR;               /*!< RCC STGEN Clock Selection Register                   Address offset: 0xD4 */
  __IO uint32_t DDRITFCR;                  /*!< RCC control DDR interface, DDRC and DDRPHYC Register Address offset: 0xD8 */
       uint32_t RESERVED5;                 /*!< Reserved,                                            Address offset: 0xDC */
       uint32_t RESERVED6[8];              /*!< Reserved, 0xE0-0xFC                                  Address offset: 0xE0 */
  __IO uint32_t MP_BOOTCR;                 /*!< RCC Hold Boot Control Register                       Address offset: 0x100 */
  __IO uint32_t MP_SREQSETR;               /*!< RCC Stop Request Set Register                        Address offset: 0x104 */
  __IO uint32_t MP_SREQCLRR;               /*!< RCC Stop Request Clear Register                      Address offset: 0x108 */
  __IO uint32_t MP_GCR;                    /*!< RCC Global Control Register                          Address offset: 0x10C */
  __IO uint32_t MP_APRSTCR;                /*!< RCC Application Reset Control Register               Address offset: 0x110 */
  __IO uint32_t MP_APRSTSR;                /*!< RCC Application Reset Status Register                Address offset: 0x114 */
       uint32_t RESERVED7[10];             /*!< Reserved, 0x118-0x13C                                Address offset: 0x118 */
  __IO uint32_t BDCR;                      /*!< RCC Backup Domain Control Register                   Address offset: 0x140 */
  __IO uint32_t RDLSICR;                   /*!< RCC Reset Duration and LSI Control Register          Address offset: 0x144 */
       uint32_t RESERVED8[14];             /*!< Reserved, 0x148-0x17C                                Address offset: 0x148 */
  __IO uint32_t APB4RSTSETR;               /*!< RCC APB4 Peripheral Reset Set Register               Address offset: 0x180 */
  __IO uint32_t APB4RSTCLRR;               /*!< RCC APB4 Peripheral Reset Clear Register             Address offset: 0x184 */
  __IO uint32_t APB5RSTSETR;               /*!< RCC APB5 Peripheral Reset Set Register               Address offset: 0x188 */
  __IO uint32_t APB5RSTCLRR;               /*!< RCC APB5 Peripheral Reset Clear Register             Address offset: 0x18C */
  __IO uint32_t AHB5RSTSETR;               /*!< RCC AHB5 Peripheral Reset Set Register               Address offset: 0x190 */
  __IO uint32_t AHB5RSTCLRR;               /*!< RCC AHB5 Peripheral Reset Clear Register             Address offset: 0x194 */
  __IO uint32_t AHB6RSTSETR;               /*!< RCC AHB6 Peripheral Reset Set Register               Address offset: 0x198 */
  __IO uint32_t AHB6RSTCLRR;               /*!< RCC AHB6 Peripheral Reset Clear Register             Address offset: 0x19C */
  __IO uint32_t TZAHB6RSTSETR;             /*!< RCC AHB6 Peripheral Reset Set Register               Address offset: 0x1A0 */
  __IO uint32_t TZAHB6RSTCLRR;             /*!< RCC AHB6 Peripheral Reset Clear Register             Address offset: 0x1A4 */
       uint32_t RESERVED9[22];             /*!< Reserved, 0x1A8-0x1FC                                Address offset: 0x1A8 */
  __IO uint32_t MP_APB4ENSETR;             /*!< RCC APB4 Periph. Enable For MPU Set Register         Address offset: 0x200 */
  __IO uint32_t MP_APB4ENCLRR;             /*!< RCC APB4 Periph. Enable For MPU Clear Register       Address offset: 0x204 */
  __IO uint32_t MP_APB5ENSETR;             /*!< RCC APB5 Periph. Enable For MPU Set Register         Address offset: 0x208 */
  __IO uint32_t MP_APB5ENCLRR;             /*!< RCC APB5 Periph. Enable For MPU Clear Register       Address offset: 0x20C */
  __IO uint32_t MP_AHB5ENSETR;             /*!< RCC AHB5 Periph. Enable For MPU Set Register         Address offset: 0x210 */
  __IO uint32_t MP_AHB5ENCLRR;             /*!< RCC AHB5 Periph. Enable For MPU Clear Register       Address offset: 0x214 */
  __IO uint32_t MP_AHB6ENSETR;             /*!< RCC AHB6 Periph. Enable For MPU Set Register         Address offset: 0x218 */
  __IO uint32_t MP_AHB6ENCLRR;             /*!< RCC AHB6 Periph. Enable For MPU Clear Register       Address offset: 0x21C */
       uint32_t RESERVED10[24];             /*!< Reserved, 0x220-0x27C                                Address offset: 0x220 */
  __IO uint32_t MC_APB4ENSETR;             /*!< RCC APB4 Periph. Enable For MCU Set Register         Address offset: 0x280 */
  __IO uint32_t MC_APB4ENCLRR;             /*!< RCC APB4 Periph. Enable For MCU Clear Register       Address offset: 0x284 */
  __IO uint32_t MC_APB5ENSETR;             /*!< RCC APB5 Periph. Enable For MCU Set Register         Address offset: 0x288 */
  __IO uint32_t MC_APB5ENCLRR;             /*!< RCC APB5 Periph. Enable For MCU Clear Register       Address offset: 0x28C */
  __IO uint32_t MC_AHB5ENSETR;             /*!< RCC AHB5 Periph. Enable For MCU Set Register         Address offset: 0x290 */
  __IO uint32_t MC_AHB5ENCLRR;             /*!< RCC AHB5 Periph. Enable For MCU Clear Register       Address offset: 0x294 */
  __IO uint32_t MC_AHB6ENSETR;             /*!< RCC AHB6 Periph. Enable For MCU Set Register         Address offset: 0x298 */
  __IO uint32_t MC_AHB6ENCLRR;             /*!< RCC AHB6 Periph. Enable For MCU Clear Register       Address offset: 0x29C */
       uint32_t RESERVED11[24];            /*!< Reserved, 0x2A0-0x2FC                                Address offset: 0x2A0 */
  __IO uint32_t MP_APB4LPENSETR;           /*!< RCC APB4 Sleep Clock Ena. For MPU Set Register       Address offset: 0x300 */
  __IO uint32_t MP_APB4LPENCLRR;           /*!< RCC APB4 Sleep Clock Ena. For MPU Clear Register     Address offset: 0x304 */
  __IO uint32_t MP_APB5LPENSETR;           /*!< RCC APB5 Sleep Clock Ena. For MPU Set Register       Address offset: 0x308 */
  __IO uint32_t MP_APB5LPENCLRR;           /*!< RCC APB5 Sleep Clock Ena. For MPU Clear Register     Address offset: 0x30C */
  __IO uint32_t MP_AHB5LPENSETR;           /*!< RCC AHB5 Sleep Clock Ena. For MPU Set Register       Address offset: 0x310 */
  __IO uint32_t MP_AHB5LPENCLRR;           /*!< RCC AHB5 Sleep Clock Ena. For MPU Clear Register     Address offset: 0x314 */
  __IO uint32_t MP_AHB6LPENSETR;           /*!< RCC AHB6 Sleep Clock Ena. For MPU Set Register       Address offset: 0x318 */
  __IO uint32_t MP_AHB6LPENCLRR;           /*!< RCC AHB6 Sleep Clock Ena. For MPU Clear Register     Address offset: 0x31C */
       uint32_t RESERVED12[24];            /*!< Reserved, 0x320-0x30C                                Address offset: 0x320 */
  __IO uint32_t MC_APB4LPENSETR;           /*!< RCC APB4 Sleep Clock Ena. For MCU Set Register       Address offset: 0x380 */
  __IO uint32_t MC_APB4LPENCLRR;           /*!< RCC APB4 Sleep Clock Ena. For MCU Clear Register     Address offset: 0x384 */
  __IO uint32_t MC_APB5LPENSETR;           /*!< RCC APB5 Sleep Clock Ena. For MCU Set Register       Address offset: 0x388 */
  __IO uint32_t MC_APB5LPENCLRR;           /*!< RCC APB5 Sleep Clock Ena. For MCU Clear Register     Address offset: 0x38C */
  __IO uint32_t MC_AHB5LPENSETR;           /*!< RCC AHB5 Sleep Clock Ena. For MCU Set Register       Address offset: 0x390 */
  __IO uint32_t MC_AHB5LPENCLRR;           /*!< RCC AHB5 Sleep Clock Ena. For MCU Clear Register     Address offset: 0x394 */
  __IO uint32_t MC_AHB6LPENSETR;           /*!< RCC AHB6 Sleep Clock Ena. For MCU Set Register       Address offset: 0x398 */
  __IO uint32_t MC_AHB6LPENCLRR;           /*!< RCC AHB6 Sleep Clock Ena. For MCU Clear Register     Address offset: 0x39C */
       uint32_t RESERVED13[24];            /*!< Reserved, 0x3A0-0x3FC                                Address offset: 0x3A0 */
  __IO uint32_t BR_RSTSCLRR;               /*!< RCC BootRom Reset Status Clear Register              Address offset: 0x400 */
  __IO uint32_t MP_GRSTCSETR;              /*!< RCC Global Reset Control Set Register                Address offset: 0x404 */
  __IO uint32_t MP_RSTSCLRR;               /*!< RCC MPU Reset Status Clear Register                  Address offset: 0x408 */
  __IO uint32_t MP_IWDGFZSETR;             /*!< RCC IWDG Clock Freeze Set Register                   Address offset: 0x40C */
  __IO uint32_t MP_IWDGFZCLRR;             /*!< RCC IWDG Clock Freeze Clear Register                 Address offset: 0x410 */
  __IO uint32_t MP_CIER;                   /*!< RCC Clock Source Interrupt Enable Register           Address offset: 0x414 */
  __IO uint32_t MP_CIFR;                   /*!< RCC Clock Source Interrupt Flag Register             Address offset: 0x418 */
  __IO uint32_t PWRLPDLYCR;                /*!< RCC PWR_LP Delay Control Register                    Address offset: 0x41C */
  __IO uint32_t MP_RSTSSETR;               /*!< RCC MPU Reset Status Set Register                    Address offset: 0x420 */
       uint32_t RESERVED14[247];           /*!< Reserved, 0x424-0x7FC                                Address offset: 0x424 */
  __IO uint32_t MCO1CFGR;                  /*!< RCC MCO1 Configuration Register                      Address offset: 0x800 */
  __IO uint32_t MCO2CFGR;                  /*!< RCC MCO2 Configuration Register                      Address offset: 0x804 */
  __IO uint32_t OCRDYR;                    /*!< RCC Oscillator Clock Ready Register                  Address offset: 0x808 */
  __IO uint32_t DBGCFGR;                   /*!< Debug Configuration Register                         Address offset: 0x80C */
       uint32_t RESERVED15[4];             /*!< Reserved, 0x810-0x81C                                Address offset: 0x810 */
  __IO uint32_t RCK3SELR;                  /*!< RCC PLL 3 Ref. Clock Selection Register              Address offset: 0x820 */
  __IO uint32_t RCK4SELR;                  /*!< RCC PLL4 Ref. Clock Selection Register               Address offset: 0x824 */
  __IO uint32_t TIMG1PRER;                 /*!< RCC TIM Group 1 Prescaler Register                   Address offset: 0x828 */
  __IO uint32_t TIMG2PRER;                 /*!< RCC TIM Group 2 Prescaler Register                   Address offset: 0x82C */
  __IO uint32_t MCUDIVR;                   /*!< RCC MCU Clock Prescaler Register                     Address offset: 0x830 */
  __IO uint32_t APB1DIVR;                  /*!< RCC APB1 Clock Prescaler Register                    Address offset: 0x834 */
  __IO uint32_t APB2DIVR;                  /*!< RCC APB2 Clock Prescaler Register                    Address offset: 0x838 */
  __IO uint32_t APB3DIVR;                  /*!< RCC APB3 Clock Prescaler Register                    Address offset: 0x83C */
       uint32_t RESERVED16[16];            /*!< Reserved, 0x840-0x87C                                Address offset: 0x840 */
  __IO uint32_t PLL3CR;                    /*!< RCC PLL3 Control Register                            Address offset: 0x880 */
  __IO uint32_t PLL3CFGR1;                 /*!< RCC PLL3 Configuration Register 1                    Address offset: 0x884 */
  __IO uint32_t PLL3CFGR2;                 /*!< RCC PLL3 Configuration Register 2                    Address offset: 0x888 */
  __IO uint32_t PLL3FRACR;                 /*!< RCC PLL3 Fractional Register                         Address offset: 0x88C */
  __IO uint32_t PLL3CSGR;                  /*!< RCC PLL3 Clock Spreading Generator Register          Address offset: 0x890 */
  __IO uint32_t PLL4CR;                    /*!< RCC PLL4 Control Register                            Address offset: 0x894 */
  __IO uint32_t PLL4CFGR1;                 /*!< RCC PLL4 Configuration Register 1                    Address offset: 0x898 */
  __IO uint32_t PLL4CFGR2;                 /*!< RCC PLL4 Configuration Register 2                    Address offset: 0x89C */
  __IO uint32_t PLL4FRACR;                 /*!< RCC PLL4 Fractional Register                         Address offset: 0x8A0 */
  __IO uint32_t PLL4CSGR;                  /*!< RCC PLL4 Clock Spreading Generator Register          Address offset: 0x8A4 */
       uint32_t RESERVED17[6];             /*!< Reserved, 0x8A8-0x8BC                                Address offset: 0x8A8 */
  __IO uint32_t I2C12CKSELR;               /*!< RCC I2C1,2 Kernel Clock Selection Register           Address offset: 0x8C0 */
  __IO uint32_t I2C35CKSELR;               /*!< RCC I2C3,5 Kernel Clock Selection Register           Address offset: 0x8C4 */
  __IO uint32_t SAI1CKSELR;                /*!< RCC SAI1 Kernel Clock Selection Register             Address offset: 0x8C8 */
  __IO uint32_t SAI2CKSELR;                /*!< RCC SAI2 Kernel Clock Selection Register             Address offset: 0x8CC */
  __IO uint32_t SAI3CKSELR;                /*!< RCC SAI3 Kernel Clock Selection Register             Address offset: 0x8D0 */
  __IO uint32_t SAI4CKSELR;                /*!< RCC SAI4 Kernel Clock Selection Register             Address offset: 0x8D4 */
  __IO uint32_t SPI2S1CKSELR;              /*!< RCC SPI/I2S1 Kernel Clock Selection Register         Address offset: 0x8D8 */
  __IO uint32_t SPI2S23CKSELR;             /*!< RCC SPI/I2S2,3 Kernel Clock Selection Register       Address offset: 0x8DC */
  __IO uint32_t SPI45CKSELR;               /*!< RCC SPI4,5 Kernel Clock Selection Register           Address offset: 0x8E0 */
  __IO uint32_t UART6CKSELR;               /*!< RCC USART6 Kernel Clock Selection Register           Address offset: 0x8E4 */
  __IO uint32_t UART24CKSELR;              /*!< RCC UART2,4 Kernel Clock Selection Register          Address offset: 0x8E8 */
  __IO uint32_t UART35CKSELR;              /*!< RCC UART3,5 Kernel Clock Selection Register          Address offset: 0x8EC */
  __IO uint32_t UART78CKSELR;              /*!< RCC UART7,8 Kernel Clock Selection Register          Address offset: 0x8F0 */
  __IO uint32_t SDMMC12CKSELR;             /*!< RCC SDMMC1&2 Kernel Clock Selection Register         Address offset: 0x8F4 */
  __IO uint32_t SDMMC3CKSELR;              /*!< RCC SDMMC3 Kernel Clock Selection Register           Address offset: 0x8F8 */
  __IO uint32_t ETHCKSELR;                 /*!< RCC Ethernet Kernel Clock Selection Register         Address offset: 0x8FC */
  __IO uint32_t QSPICKSELR;                /*!< RCC QUADSPI Kernel Clock Selection Register          Address offset: 0x900 */
  __IO uint32_t FMCCKSELR;                 /*!< RCC FMC Kernel Clock Selection Register              Address offset: 0x904 */
       uint32_t RESERVED18;                /*!< Reserved,                                            Address offset: 0x908 */
  __IO uint32_t FDCANCKSELR;               /*!< RCC FDCAN Kernel Clock Selection Register            Address offset: 0x90C */
       uint32_t RESERVED19;                /*!< Reserved,                                            Address offset: 0x910 */
  __IO uint32_t SPDIFCKSELR;               /*!< RCC SPDIF Kernel Clock Selection Register            Address offset: 0x914 */
  __IO uint32_t CECCKSELR;                 /*!< RCC CEC Kernel Clock Selection Register              Address offset: 0x918 */
  __IO uint32_t USBCKSELR;                 /*!< RCC USB Kernel Clock Selection Register              Address offset: 0x91C */
  __IO uint32_t RNG2CKSELR;                /*!< RCC RNG2 Kernel Clock Selection Register             Address offset: 0x920 */
  __IO uint32_t DSICKSELR;                 /*!< RCC DSI Kernel Clock Selection Register              Address offset: 0x924 */
  __IO uint32_t ADCCKSELR;                 /*!< RCC ADC Kernel Clock Selection Register              Address offset: 0x928 */
  __IO uint32_t LPTIM45CKSELR;             /*!< RCC LPTIM4&5 Kernel Clock Selection Register         Address offset: 0x92C */
  __IO uint32_t LPTIM23CKSELR;             /*!< RCC LPTIM2&3 Kernel Clock Selection Register         Address offset: 0x930 */
  __IO uint32_t LPTIM1CKSELR;              /*!< RCC LPTIM1 Kernel Clock Selection Register           Address offset: 0x934 */
       uint32_t RESERVED20[18];            /*!< Reserved, 0x938-0x97C                                Address offset: 0x938 */
  __IO uint32_t APB1RSTSETR;               /*!< RCC APB1 Peripheral Reset Set Register               Address offset: 0x980 */
  __IO uint32_t APB1RSTCLRR;               /*!< RCC APB1 Peripheral Reset Clear Register             Address offset: 0x984 */
  __IO uint32_t APB2RSTSETR;               /*!< RCC APB2 Peripheral Reset Set Register               Address offset: 0x988 */
  __IO uint32_t APB2RSTCLRR;               /*!< RCC APB2 Peripheral Reset Clear Register             Address offset: 0x98C */
  __IO uint32_t APB3RSTSETR;               /*!< RCC APB3 Peripheral Reset Set Register               Address offset: 0x990 */
  __IO uint32_t APB3RSTCLRR;               /*!< RCC APB3 Peripheral Reset Clear Register             Address offset: 0x994 */
  __IO uint32_t AHB2RSTSETR;               /*!< RCC AHB2 Peripheral Reset Set Register               Address offset: 0x998 */
  __IO uint32_t AHB2RSTCLRR;               /*!< RCC AHB2 Peripheral Reset Clear Register             Address offset: 0x99C */
  __IO uint32_t AHB3RSTSETR;               /*!< RCC AHB3 Peripheral Reset Set Register               Address offset: 0x9A0 */
  __IO uint32_t AHB3RSTCLRR;               /*!< RCC AHB3 Peripheral Reset Clear Register             Address offset: 0x9A4 */
  __IO uint32_t AHB4RSTSETR;               /*!< RCC AHB4 Peripheral Reset Set Register               Address offset: 0x9A8 */
  __IO uint32_t AHB4RSTCLRR;               /*!< RCC AHB4 Peripheral Reset Clear Register             Address offset: 0x9AC */
       uint32_t RESERVED21[20];            /*!< Reserved, 0x9B0-0x9FC                                Address offset: 0x9B0 */
  __IO uint32_t MP_APB1ENSETR;             /*!< RCC APB1 Peripheral Enable For MPU Set Register      Address offset: 0xA00 */
  __IO uint32_t MP_APB1ENCLRR;             /*!< RCC APB1 Peripheral Enable For MPU Clear Register    Address offset: 0xA04 */
  __IO uint32_t MP_APB2ENSETR;             /*!< RCC APB2 Peripheral Enable For MPU Set Register      Address offset: 0xA08 */
  __IO uint32_t MP_APB2ENCLRR;             /*!< RCC APB2 Peripheral Enable For MPU Clear Register    Address offset: 0xA0C */
  __IO uint32_t MP_APB3ENSETR;             /*!< RCC APB3 Peripheral Enable For MPU Set Register      Address offset: 0xA10 */
  __IO uint32_t MP_APB3ENCLRR;             /*!< RCC APB3 Peripheral Enable For MPU Clear Register    Address offset: 0xA14 */
  __IO uint32_t MP_AHB2ENSETR;             /*!< RCC AHB2 Peripheral Enable For MPU Set Register      Address offset: 0xA18 */
  __IO uint32_t MP_AHB2ENCLRR;             /*!< RCC AHB2 Peripheral Enable For MPU Clear Register    Address offset: 0xA1C */
  __IO uint32_t MP_AHB3ENSETR;             /*!< RCC AHB3 Peripheral Enable For MPU Set Register      Address offset: 0xA20 */
  __IO uint32_t MP_AHB3ENCLRR;             /*!< RCC AHB3 Peripheral Enable For MPU Clear Register    Address offset: 0xA24 */
  __IO uint32_t MP_AHB4ENSETR;             /*!< RCC AHB4 Peripheral Enable For MPU Set Register      Address offset: 0xA28 */
  __IO uint32_t MP_AHB4ENCLRR;             /*!< RCC AHB4 Peripheral Enable For MPU Clear Register    Address offset: 0xA2C */
       uint32_t RESERVED22[2];             /*!< Reserved, 0xA30-0xA34                                Address offset: 0xA30 */
  __IO uint32_t MP_MLAHBENSETR;            /*!< RCC MLAHB Periph. Enable For MPU Set Register        Address offset: 0xA38 */
  __IO uint32_t MP_MLAHBENCLRR;            /*!< RCC MLAHB Periph. Enable For MPU Clear Register      Address offset: 0xA3C */
       uint32_t RESERVED23[16];            /*!< Reserved, 0x940-0xA7C                                Address offset: 0x940 */
  __IO uint32_t MC_APB1ENSETR;             /*!< RCC APB1 Peripheral Enable For MCU Set Register      Address offset: 0xA80 */
  __IO uint32_t MC_APB1ENCLRR;             /*!< RCC APB1 Peripheral Enable For MCU Clear Register    Address offset: 0xA84 */
  __IO uint32_t MC_APB2ENSETR;             /*!< RCC APB2 Peripheral Enable For MCU Set Register      Address offset: 0xA88 */
  __IO uint32_t MC_APB2ENCLRR;             /*!< RCC APB2 Peripheral Enable For MCU Clear Register    Address offset: 0xA8C */
  __IO uint32_t MC_APB3ENSETR;             /*!< RCC APB3 Peripheral Enable For MCU Set Register      Address offset: 0xA90 */
  __IO uint32_t MC_APB3ENCLRR;             /*!< RCC APB3 Peripheral Enable For MCU Clear Register    Address offset: 0xA94 */
  __IO uint32_t MC_AHB2ENSETR;             /*!< RCC AHB2 Peripheral Enable For MCU Set Register      Address offset: 0xA98 */
  __IO uint32_t MC_AHB2ENCLRR;             /*!< RCC AHB2 Peripheral Enable For MCU Clear Register    Address offset: 0xA9C */
  __IO uint32_t MC_AHB3ENSETR;             /*!< RCC AHB3 Peripheral Enable For MCU Set Register      Address offset: 0xAA0 */
  __IO uint32_t MC_AHB3ENCLRR;             /*!< RCC AHB3 Peripheral Enable For MCU Clear Register    Address offset: 0xAA4 */
  __IO uint32_t MC_AHB4ENSETR;             /*!< RCC AHB4 Peripheral Enable For MCU Set Register      Address offset: 0xAA8 */
  __IO uint32_t MC_AHB4ENCLRR;             /*!< RCC AHB4 Peripheral Enable For MCU Clear Register    Address offset: 0xAAC */
  __IO uint32_t MC_AXIMENSETR;             /*!< RCC AXI Periph. Enable For MCU Set Register          Address offset: 0xAB0 */
  __IO uint32_t MC_AXIMENCLRR;             /*!< RCC AXI Periph. Enable For MCU Clear Register        Address offset: 0xAB4 */
  __IO uint32_t MC_MLAHBENSETR;            /*!< RCC MLAHB Periph. Enable For MCU Set Register        Address offset: 0xAB8 */
  __IO uint32_t MC_MLAHBENCLRR;            /*!< RCC MLAHB Periph. Enable For MCU Clear Register      Address offset: 0xABC */
       uint32_t RESERVED24[16];            /*!< Reserved, 0xAC0-0xAFC                                Address offset: 0xAC0 */
  __IO uint32_t MP_APB1LPENSETR;           /*!< RCC APB1 Sleep Clock Ena. For MPU Set Register       Address offset: 0xB00 */
  __IO uint32_t MP_APB1LPENCLRR;           /*!< RCC APB1 Sleep Clock Ena. For MPU Clear Register     Address offset: 0xB04 */
  __IO uint32_t MP_APB2LPENSETR;           /*!< RCC APB2 Sleep Clock Ena. For MPU Set Register       Address offset: 0xB08 */
  __IO uint32_t MP_APB2LPENCLRR;           /*!< RCC APB2 Sleep Clock Ena. For MPU Clear Register     Address offset: 0xB0C */
  __IO uint32_t MP_APB3LPENSETR;           /*!< RCC APB3 Sleep Clock Ena. For MPU Set Register       Address offset: 0xB10 */
  __IO uint32_t MP_APB3LPENCLRR;           /*!< RCC APB3 Sleep Clock Ena. For MPU Clear Register     Address offset: 0xB14 */
  __IO uint32_t MP_AHB2LPENSETR;           /*!< RCC AHB2 Sleep Clock Ena. For MPU Set Register       Address offset: 0xB18 */
  __IO uint32_t MP_AHB2LPENCLRR;           /*!< RCC AHB2 Sleep Clock Ena. For MPU Clear Register     Address offset: 0xB1C */
  __IO uint32_t MP_AHB3LPENSETR;           /*!< RCC AHB3 Sleep Clock Ena. For MPU Set Register       Address offset: 0xB20 */
  __IO uint32_t MP_AHB3LPENCLRR;           /*!< RCC AHB3 Sleep Clock Ena. For MPU Clear Register     Address offset: 0xB24 */
  __IO uint32_t MP_AHB4LPENSETR;           /*!< RCC AHB4 Sleep Clock Ena. For MPU Set Register       Address offset: 0xB28 */
  __IO uint32_t MP_AHB4LPENCLRR;           /*!< RCC AHB4 Sleep Clock Ena. For MPU Clear Register     Address offset: 0xB2C */
  __IO uint32_t MP_AXIMLPENSETR;           /*!< RCC AXI Sleep Clock Ena. For MPU Set Register        Address offset: 0xB30 */
  __IO uint32_t MP_AXIMLPENCLRR;           /*!< RCC AXI Sleep Clock Ena. For MPU Clear Register      Address offset: 0xB34 */
  __IO uint32_t MP_MLAHBLPENSETR;          /*!< RCC MLAHB Sleep Clock Ena. For MPU Set Register      Address offset: 0xB38 */
  __IO uint32_t MP_MLAHBLPENCLRR;          /*!< RCC MLAHB Sleep Clock Ena. For MPU Clear Register    Address offset: 0xB3C */
       uint32_t RESERVED25[16];            /*!< Reserved, 0xB40-0xB7C                                Address offset: 0xB40 */
  __IO uint32_t MC_APB1LPENSETR;           /*!< RCC APB1 Sleep Clock Ena. For MCU Set Register       Address offset: 0xB80 */
  __IO uint32_t MC_APB1LPENCLRR;           /*!< RCC APB1 Sleep Clock Ena. For MCU Clear Register     Address offset: 0xB84 */
  __IO uint32_t MC_APB2LPENSETR;           /*!< RCC APB2 Sleep Clock Ena. For MCU Set Register       Address offset: 0xB88 */
  __IO uint32_t MC_APB2LPENCLRR;           /*!< RCC APB2 Sleep Clock Ena. For MCU Clear Register     Address offset: 0xB8C */
  __IO uint32_t MC_APB3LPENSETR;           /*!< RCC APB3 Sleep Clock Ena. For MCU Set Register       Address offset: 0xB90 */
  __IO uint32_t MC_APB3LPENCLRR;           /*!< RCC APB3 Sleep Clock Ena. For MCU Clear Register     Address offset: 0xB94 */
  __IO uint32_t MC_AHB2LPENSETR;           /*!< RCC AHB2 Sleep Clock Ena. For MCU Set Register       Address offset: 0xB98 */
  __IO uint32_t MC_AHB2LPENCLRR;           /*!< RCC AHB2 Sleep Clock Ena. For MCU Clear Register     Address offset: 0xB9C */
  __IO uint32_t MC_AHB3LPENSETR;           /*!< RCC AHB3 Sleep Clock Ena. For MCU Set Register       Address offset: 0xBA0 */
  __IO uint32_t MC_AHB3LPENCLRR;           /*!< RCC AHB3 Sleep Clock Ena. For MCU Clear Register     Address offset: 0xBA4 */
  __IO uint32_t MC_AHB4LPENSETR;           /*!< RCC AHB4 Sleep Clock Ena. For MCU Set Register       Address offset: 0xBA8 */
  __IO uint32_t MC_AHB4LPENCLRR;           /*!< RCC AHB4 Sleep Clock Ena. For MCU Clear Register     Address offset: 0xBAC */
  __IO uint32_t MC_AXIMLPENSETR;           /*!< RCC AXI Sleep Clock Ena. For MCU Set Register        Address offset: 0xBB0 */
  __IO uint32_t MC_AXIMLPENCLRR;           /*!< RCC AXI Sleep Clock Ena. For MCU Clear Register      Address offset: 0xBB4 */
  __IO uint32_t MC_MLAHBLPENSETR;          /*!< RCC MLAHB Sleep Clock Ena. For MCU Set Register      Address offset: 0xBB8 */
  __IO uint32_t MC_MLAHBLPENCLRR;          /*!< RCC MLAHB Sleep Clock Ena. For MCU Clear Register    Address offset: 0xBBC */
       uint32_t RESERVED26[16];            /*!< Reserved, 0xBC0-0xBFC                                Address offset: 0xBC0 */
  __IO uint32_t MC_RSTSCLRR;               /*!< RCC MCU Reset Status Clear Register                  Address offset: 0xC00 */
       uint32_t RESERVED27[4];             /*!< Reserved, 0xC04-0xC10                                Address offset: 0xC04 */
  __IO uint32_t MC_CIER;                   /*!< RCC Clock Source Interrupt Enable Register           Address offset: 0xC14 */
  __IO uint32_t MC_CIFR;                   /*!< RCC Clock Source Interrupt Flag Register             Address offset: 0xC18 */
       uint32_t RESERVED28[246];           /*!< Reserved, 0xC1C-0xFF0                                Address offset: 0xC1C */
  __IO uint32_t VERR;                      /*!< RCC Version register                                 Address offset: 0xFF4 */
  __IO uint32_t IPIDR;                     /*!< RCC ID register                                      Address offset: 0xFF8 */
  __IO uint32_t SIDR;                      /*!< Size ID register                                     Address offset: 0xFFC */
} RCC_TypeDef;

/**
  * @brief Hardware Debug Port
  */

typedef struct
{
  __IO uint32_t HDP_CTRL;                  /*!< HDP Control Register,                                Address offset: 0x00 */
  __IO uint32_t HDP_MUX;                   /*!< HDP Multiplexers Control Register,                   Address offset: 0x04 */
       uint32_t RESERVED0[2];              /*!< Reserved, 0x08-0x0C                                  Address offset: 0x08 */
  __IO uint32_t HDP_VAL;                   /*!< HDP Read Back Value Register,                        Address offset: 0x10 */
  __IO uint32_t HDP_GPOSET;                /*!< HDP General Purpose Output Set Register,             Address offset: 0x14 */
  __IO uint32_t HDP_GPOCLR;                /*!< HDP General Purpose Output Clear Register,           Address offset: 0x18 */
  __IO uint32_t HDP_GPOVAL;                /*!< HDP General Purpose Output Value Register,           Address offset: 0x1C */
       uint32_t RESERVED1[245];            /*!< Reserved, 0x20-0x3F4                                 Address offset: 0x20 */
  __IO uint32_t VERR;                  /*!< HDP Version Register,                                Address offset: 0x3F4 */
  __IO uint32_t IPIDR;                 /*!< HDP IP Identification Register,                      Address offset: 0x3F8 */
  __IO uint32_t SIDR;                  /*!< HDP Size Identification register,                    Address offset: 0x3FC */
} HDP_TypeDef;


/**
  * @brief Boot and Security and OTP Control
  */

typedef struct
{
  __IO uint32_t BSEC_OTP_CONFIG;           /*!< BSEC OTP Configuration,                              Address offset: 0x00 */
  __IO uint32_t BSEC_OTP_CONTROL;          /*!< BSEC OTP Control,                                    Address offset: 0x04 */
  __IO uint32_t BSEC_OTP_WRDATA;           /*!< BSEC OTP Write Data,                                 Address offset: 0x08 */
  __IO uint32_t BSEC_OTP_STATUS;           /*!< BSEC OTP Status,                                     Address offset: 0x0C */
  __IO uint32_t BSEC_OTP_LOCK;             /*!< BSEC OTP Configuration,                              Address offset: 0x10 */
  __IO uint32_t BSEC_DENABLE;              /*!< BSEC Debug Configuration,                            Address offset: 0x14 */
  __IO uint32_t RESERVED0x18;              /*!< Reserved,                                            Address offset: 0x18 */
  __IO uint32_t BSEC_OTP_DISTURBED0;       /*!< BSEC OTP Disturbed Status,                           Address offset: 0x1C */
  __IO uint32_t BSEC_OTP_DISTURBED1;       /*!< BSEC OTP Disturbed Status,                           Address offset: 0x20 */
  __IO uint32_t BSEC_OTP_DISTURBED2;       /*!< BSEC OTP Disturbed Status,                           Address offset: 0x24 */
       uint32_t RESERVED0x28;              /*!< Reserved,                                            Address offset: 0x28 */
       uint32_t RESERVED0x2C;              /*!< Reserved,                                            Address offset: 0x2C */
       uint32_t RESERVED0x30;              /*!< Reserved,                                            Address offset: 0x30 */
  __IO uint32_t BSEC_OTP_ERROR0;           /*!< BSEC OTP Error Status,                               Address offset: 0x34 */
  __IO uint32_t BSEC_OTP_ERROR1;           /*!< BSEC OTP Error Status,                               Address offset: 0x38 */
  __IO uint32_t BSEC_OTP_ERROR2;           /*!< BSEC OTP Error Status,                               Address offset: 0x3C */
       uint32_t RESERVED0x40;              /*!< Reserved,                                            Address offset: 0x40 */
       uint32_t RESERVED0x44;              /*!< Reserved,                                            Address offset: 0x44 */
       uint32_t RESERVED0x48;              /*!< Reserved,                                            Address offset: 0x48 */
  __IO uint32_t BSEC_OTP_WRLOCK0;          /*!< BSEC OTP Lock status,                                Address offset: 0x4C */
  __IO uint32_t BSEC_OTP_WRLOCK1;          /*!< BSEC OTP Lock status,                                Address offset: 0x50 */
  __IO uint32_t BSEC_OTP_WRLOCK2;          /*!< BSEC OTP Lock status,                                Address offset: 0x54 */
       uint32_t RESERVED0x58;              /*!< Reserved,                                            Address offset: 0x58 */
       uint32_t RESERVED0x5C;              /*!< Reserved,                                            Address offset: 0x5C */
       uint32_t RESERVED0x60;              /*!< Reserved,                                            Address offset: 0x60 */
  __IO uint32_t BSEC_OTP_SPLOCK0;          /*!< BSEC OTP prg lock under ctrl by stick bits,          Address offset: 0x64 */
  __IO uint32_t BSEC_OTP_SPLOCK1;          /*!< BSEC OTP prg lock under ctrl by stick bits,          Address offset: 0x68 */
  __IO uint32_t BSEC_OTP_SPLOCK2;          /*!< BSEC OTP prg lock under ctrl by stick bits,          Address offset: 0x6C */
       uint32_t RESERVED0x70;              /*!< Reserved,                                            Address offset: 0x70 */
       uint32_t RESERVED0x74;              /*!< Reserved,                                            Address offset: 0x74 */
       uint32_t RESERVED0x78;              /*!< Reserved,                                            Address offset: 0x78 */
  __IO uint32_t BSEC_OTP_SWLOCK0;          /*!< BSEC OTP Shadow Write Lck under ctrl by sticky bits, Address offset: 0x7C */
  __IO uint32_t BSEC_OTP_SWLOCK1;          /*!< BSEC OTP Shadow Write Lck under ctrl by sticky bits, Address offset: 0x80 */
  __IO uint32_t BSEC_OTP_SWLOCK2;          /*!< BSEC OTP Shadow Write Lck under ctrl by sticky bits, Address offset: 0x84 */
       uint32_t RESERVED0x88;              /*!< Reserved,                                            Address offset: 0x88 */
       uint32_t RESERVED0x8C;              /*!< Reserved,                                            Address offset: 0x8C */
       uint32_t RESERVED0x90;              /*!< Reserved,                                            Address offset: 0x90 */
  __IO uint32_t BSEC_OTP_SRLOCK0;          /*!< BSEC OTP Shadow read lock under ctrl by sticky bits, Address offset: 0x94 */
  __IO uint32_t BSEC_OTP_SRLOCK1;          /*!< BSEC OTP Shadow read lock under ctrl by sticky bits, Address offset: 0x98 */
  __IO uint32_t BSEC_OTP_SRLOCK2;          /*!< BSEC OTP Shadow read lock under ctrl by sticky bits, Address offset: 0x9C */
       uint32_t RESERVED0xA0;              /*!< Reserved,                                            Address offset: 0xA0 */
       uint32_t RESERVED0xA4;              /*!< Reserved,                                            Address offset: 0xA4 */
       uint32_t RESERVED0xA8;              /*!< Reserved,                                            Address offset: 0xA8 */
  __IO uint32_t BSEC_JTAGIN;               /*!< BSEC JTAG Input,                                     Address offset: 0xAC */
  __IO uint32_t BSEC_JTAGOUT;              /*!< BSEC JTAG Output,                                    Address offset: 0xB0 */
  __IO uint32_t BSEC_SCRATCH;              /*!< BSEC SCRATCH,                                        Address offset: 0xB4 */
       uint32_t RESERVED0xB8[82];          /*!< Reserved, 0x0B8-0x200                                Address offset: 0xB8 */
  __IO uint32_t BSEC_OTP_DATA[96];         /*!< BSEC Shadow Registers,                               Address offset: 0x200 */
       uint32_t RESERVED0x380[796];        /*!< Reserved, 0x0380-0xFF0                               Address offset: 0x380 */
  __IO uint32_t HWCFGR;                    /*!< BSEC IP HW Configuration Register,                   Address offset: 0xFF0 */
  __IO uint32_t VERR;                      /*!< BSEC IP version Register,                            Address offset: 0xFF4 */
  __IO uint32_t IPIDR;                     /*!< BSEC ID Register,                                    Address offset: 0xFF8 */
  __IO uint32_t SIDR;                      /*!< BSEC SID Register,                                   Address offset: 0xFFC */
} BSEC_TypeDef;


/**
  * @brief RTC Specific device feature definitions
  */
#define RTC_BACKUP_NB       32u /* Backup registers implemented */
#define RTC_TAMP_NB         3u  /* External tamper events (input pins) supported */

/**
  * @brief Real-Time Clock
  */

typedef struct
{
  __IO uint32_t TR;             /*!< RTC time register,                                         Address offset: 0x00 */
  __IO uint32_t DR;             /*!< RTC date register,                                         Address offset: 0x04 */
  __IO uint32_t SSR;            /*!< RTC sub-second register,                                   Address offset: 0x08 */
  __IO uint32_t ICSR;           /*!< RTC initialization control and status register,            Address offset: 0x0C */
  __IO uint32_t PRER;           /*!< RTC prescaler register,                                    Address offset: 0x10 */
  __IO uint32_t WUTR;           /*!< RTC wakeup timer register,                                 Address offset: 0x14 */
  __IO uint32_t CR;             /*!< RTC control register,                                      Address offset: 0x18 */
       uint32_t RESERVED;       /*!< Reserved                                                                        */
  __IO uint32_t SMCR;           /*!< RTC secure mode control register,                          Address offset: 0x20 */
  __IO uint32_t WPR;            /*!< RTC write protection register,                             Address offset: 0x24 */
  __IO uint32_t CALR;           /*!< RTC calibration register,                                  Address offset: 0x28 */
  __IO uint32_t SHIFTR;         /*!< RTC shift control register,                                Address offset: 0x2C */
  __IO uint32_t TSTR;           /*!< RTC time stamp time register,                              Address offset: 0x30 */
  __IO uint32_t TSDR;           /*!< RTC time stamp date register,                              Address offset: 0x34 */
  __IO uint32_t TSSSR;           /*!< RTC time stamp sub second register,                        Address offset: 0x38 */
       uint32_t RESERVED1;      /*!< Reserved                                                                        */
  __IO uint32_t ALRMAR;         /*!< RTC alarm A register,                                      Address offset: 0x40 */
  __IO uint32_t ALRMASSR;       /*!< RTC alarm A sub second register,                           Address offset: 0x44 */
  __IO uint32_t ALRMBR;         /*!< RTC alarm B register,                                      Address offset: 0x48 */
  __IO uint32_t ALRMBSSR;       /*!< RTC alarm B sub second register,                           Address offset: 0x4C */
  __IO uint32_t SR;             /*!< RTC status register,                                       Address offset: 0x50 */
  __IO uint32_t MISR;           /*!< RTC masked interrupt status register,                      Address offset: 0x54 */
  __IO uint32_t SMISR;          /*!< RTC secure masked interrupt status register,               Address offset: 0x58 */
  __IO uint32_t SCR;            /*!< RTC status clear register,                                 Address offset: 0x5C */
  __IO uint32_t CFGR;           /*!< RTC Configuration register,                               Address offset: 0x60 */
       uint32_t RESERVED2[227]; /*!< Reserved                                                                        */
  __IO uint32_t HWCFGR;         /*!< RTC hardware configuration register,                       Address offset: 0x3F0 */
  __IO uint32_t VERR;            /*!< RTC version register,                                     Address offset: 0x3F4 */
  __IO uint32_t IPIDR;          /*!< RTC identification register,                               Address offset: 0x3F8 */
  __IO uint32_t SIDR;           /*!< RTC size identification register,                          Address offset: 0x3FC */
} RTC_TypeDef;


/**
  * @brief Tamper and Backup registers
  */
typedef struct
{
  __IO uint32_t CR1;           /*!< TAMP tamper control register 1,                         Address offset: 0x00 */
  __IO uint32_t CR2;           /*!< TAMP tamper control register 2,                         Address offset: 0x04 */
       uint32_t RESERVED;      /*!< Reserved                                                                     */
  __IO uint32_t FLTCR;         /*!< TAMP filter control register,                           Address offset: 0x0C */
  __IO uint32_t ATCR1;          /*!< TAMP active tamper control register,                   Address offset: 0x10 */
  __IO uint32_t ATSEEDR;       /*!< TAMP active tamper seed register,                       Address offset: 0x14 */
  __IO uint32_t ATOR;          /*!< TAMP active tamper output register,                     Address offset: 0x18 */
       uint32_t RESERVED1;     /*!< Reserved                                                                     */
  __IO uint32_t SMCR;          /*!< TAMP secure mode control register,                      Address offset: 0x20 */
       uint32_t RESERVED2[2];  /*!< Reserved, 0x024 - 0x028                                                      */
  __IO uint32_t IER;           /*!< TAMP interrupt enable register,                         Address offset: 0x2C */
  __IO uint32_t SR;            /*!< TAMP status register,                                   Address offset: 0x30 */
  __IO uint32_t MISR;          /*!< TAMP masked interrupt status register,                  Address offset: 0x34 */
  __IO uint32_t SMISR;         /*!< TAMP secure masked interrupt status register,           Address offset: 0x38 */
  __IO uint32_t SCR;           /*!< TAMP status clear register,                             Address offset: 0x3C */
  __IO uint32_t COUNTR;        /*!< TAMP monotonic counter register,                        Address offset: 0x40 */
  uint32_t RESERVED3[3];       /*!< Reserved, 0x044 - 0x04C                                                      */
  __IO uint32_t CFGR;          /*!< TAMP Configuration register,                            Address offset: 0x50 */
  uint32_t RESERVED4[43];      /*!< Reserved, 0x054 - 0x0FC                                                      */
  __IO uint32_t BKP0R;         /*!< TAMP backup register 0,                                 Address offset: 0x100 */
  __IO uint32_t BKP1R;         /*!< TAMP backup register 1,                                 Address offset: 0x104 */
  __IO uint32_t BKP2R;         /*!< TAMP backup register 2,                                 Address offset: 0x108 */
  __IO uint32_t BKP3R;         /*!< TAMP backup register 3,                                 Address offset: 0x10C */
  __IO uint32_t BKP4R;         /*!< TAMP backup register 4,                                 Address offset: 0x110 */
  __IO uint32_t BKP5R;         /*!< TAMP backup register 5,                                 Address offset: 0x114 */
  __IO uint32_t BKP6R;         /*!< TAMP backup register 6,                                 Address offset: 0x118 */
  __IO uint32_t BKP7R;         /*!< TAMP backup register 7,                                 Address offset: 0x11C */
  __IO uint32_t BKP8R;         /*!< TAMP backup register 8,                                 Address offset: 0x120 */
  __IO uint32_t BKP9R;         /*!< TAMP backup register 9,                                 Address offset: 0x124 */
  __IO uint32_t BKP10R;        /*!< TAMP backup register 10,                                Address offset: 0x128 */
  __IO uint32_t BKP11R;        /*!< TAMP backup register 11,                                Address offset: 0x12C */
  __IO uint32_t BKP12R;        /*!< TAMP backup register 12,                                Address offset: 0x130 */
  __IO uint32_t BKP13R;        /*!< TAMP backup register 13,                                Address offset: 0x134 */
  __IO uint32_t BKP14R;        /*!< TAMP backup register 14,                                Address offset: 0x138 */
  __IO uint32_t BKP15R;        /*!< TAMP backup register 15,                                Address offset: 0x13C */
  __IO uint32_t BKP16R;        /*!< TAMP backup register 16,                                Address offset: 0x140 */
  __IO uint32_t BKP17R;        /*!< TAMP backup register 17,                                Address offset: 0x144 */
  __IO uint32_t BKP18R;        /*!< TAMP backup register 18,                                Address offset: 0x148 */
  __IO uint32_t BKP19R;        /*!< TAMP backup register 19,                                Address offset: 0x14C */
  __IO uint32_t BKP20R;        /*!< TAMP backup register 20,                                Address offset: 0x150 */
  __IO uint32_t BKP21R;        /*!< TAMP backup register 21,                                Address offset: 0x154 */
  __IO uint32_t BKP22R;        /*!< TAMP backup register 22,                                Address offset: 0x158 */
  __IO uint32_t BKP23R;        /*!< TAMP backup register 23,                                Address offset: 0x15C */
  __IO uint32_t BKP24R;        /*!< TAMP backup register 24,                                Address offset: 0x160 */
  __IO uint32_t BKP25R;        /*!< TAMP backup register 25,                                Address offset: 0x164 */
  __IO uint32_t BKP26R;        /*!< TAMP backup register 26,                                Address offset: 0x168 */
  __IO uint32_t BKP27R;        /*!< TAMP backup register 27,                                Address offset: 0x16C */
  __IO uint32_t BKP28R;        /*!< TAMP backup register 28,                                Address offset: 0x170 */
  __IO uint32_t BKP29R;        /*!< TAMP backup register 29,                                Address offset: 0x174 */
  __IO uint32_t BKP30R;        /*!< TAMP backup register 30,                                Address offset: 0x178 */
  __IO uint32_t BKP31R;        /*!< TAMP backup register 31,                                Address offset: 0x17C */
       uint32_t RESERVED5[155]; /*!< Reserved, 0x180 - 0x3E8                                                      */
  __IO uint32_t HWCFGR2;        /*!< TAMP hardware configuration register,                  Address offset: 0x3EC */
  __IO uint32_t HWCFGR1;        /*!< TAMP hardware configuration register,                  Address offset: 0x3F0 */
  __IO uint32_t VERR;           /*!< TAMP version register,                                 Address offset: 0x3F4 */
  __IO uint32_t IPIDR;          /*!< TAMP identification register,                          Address offset: 0x3F8 */
  __IO uint32_t SIDR;           /*!< TAMP size identification register,                     Address offset: 0x3FC */
} TAMP_TypeDef;


/**
  * @brief Serial Audio Interface
  */

typedef struct
{
  __IO uint32_t GCR;           /*!< SAI global configuration register, Address offset: 0x00  */
  uint32_t      RESERVED0[16]; /*!< Reserved, 0x04 - 0x43                                    */
  __IO uint32_t PDMCR;         /*!< SAI PDM control register,          Address offset: 0x44  */
  __IO uint32_t PDMDLY;        /*!< SAI PDM delay register,            Address offset: 0x48  */
  uint32_t      RESERVED1[233]; /*!< Reserved, 0x4C - 0x3EC                                  */
  __IO uint32_t HWCFGR;        /*!< SAI HW Configuration register,     Address offset: 0x3F0 */
  __IO uint32_t VERR;          /*!< SAI PVersion register,             Address offset: 0x3F4 */
  __IO uint32_t IPIDR;           /*!< SAI Identification register,       Address offset: 0x3F8 */
  __IO uint32_t SIDR;          /*!< SAI Size Identification register,  Address offset: 0x3FC */
} SAI_TypeDef;

typedef struct
{
  __IO uint32_t CR1;      /*!< SAI block x configuration register 1,     Address offset: 0x04 */
  __IO uint32_t CR2;      /*!< SAI block x configuration register 2,     Address offset: 0x08 */
  __IO uint32_t FRCR;     /*!< SAI block x frame configuration register, Address offset: 0x0C */
  __IO uint32_t SLOTR;    /*!< SAI block x slot register,                Address offset: 0x10 */
  __IO uint32_t IMR;      /*!< SAI block x interrupt mask register,       Address offset: 0x14 */
  __IO uint32_t SR;       /*!< SAI block x status register,              Address offset: 0x18 */
  __IO uint32_t CLRFR;    /*!< SAI block x clear flag register,          Address offset: 0x1C */
  __IO uint32_t DR;       /*!< SAI block x data register,                Address offset: 0x20 */
} SAI_Block_TypeDef;



/**
  * @brief  Process Monitor Block
  */

typedef struct
{
  uint32_t Reserved;            /*!< Reserved, Address offset: 0x00 */
  __IO uint32_t SENS_CTRL;      /*!< PMB Sensor control,         Address offset: 0x04 */
  __IO uint32_t REF_COUNTER;    /*!< PMB Reference counter,      Address offset: 0x08 */
  __IO uint32_t SENSOR_STATUS;  /*!< PMB Sensor Status,          Address offset: 0x0C */
}PMB_TypeDef;


/**
  * @brief SPDIF-RX Interface
  */

typedef struct
{
  __IO uint32_t   CR;           /*!< Control register,                      Address offset: 0x00 */
  __IO uint32_t   IMR;          /*!< Interrupt mask register,               Address offset: 0x04 */
  __IO uint32_t   SR;           /*!< Status register,                       Address offset: 0x08 */
  __IO uint32_t   IFCR;         /*!< Interrupt Flag Clear register,         Address offset: 0x0C */
  __IO uint32_t   DR;           /*!< Data input register,                   Address offset: 0x10 */
  __IO uint32_t   CSR;          /*!< Channel Status register,               Address offset: 0x14 */
  __IO uint32_t   DIR;          /*!< Debug Information register,            Address offset: 0x18 */
  uint32_t        RESERVED2[246];   /*!< Reserved,                                0x1C   - 0x3F0 */
  __IO uint32_t   VERR;         /*!< SPDIFRX version register,             Address offset: 0x3F4 */
  __IO uint32_t   IPIDR;          /*!< SPDIFRX Identificationn register,     Address offset: 0x3F8 */
  __IO uint32_t   SIDR;         /*!< SPDIFRX Size Identification register, Address offset: 0x3FC */
} SPDIFRX_TypeDef;


/**
  * @brief Secure digital input/output Interface
  */

typedef struct
{
  __IO uint32_t POWER;          /*!< SDMMC power control register,             Address offset: 0x00 */
  __IO uint32_t CLKCR;          /*!< SDMMC clock control register,             Address offset: 0x04 */
  __IO uint32_t ARG;            /*!< SDMMC argument register,                  Address offset: 0x08 */
  __IO uint32_t CMD;            /*!< SDMMC command register,                   Address offset: 0x0C */
  __I uint32_t  RESPCMD;        /*!< SDMMC command response register,          Address offset: 0x10 */
  __I uint32_t  RESP1;          /*!< SDMMC response 1 register,                Address offset: 0x14 */
  __I uint32_t  RESP2;          /*!< SDMMC response 2 register,                Address offset: 0x18 */
  __I uint32_t  RESP3;          /*!< SDMMC response 3 register,                Address offset: 0x1C */
  __I uint32_t  RESP4;          /*!< SDMMC response 4 register,                Address offset: 0x20 */
  __IO uint32_t DTIMER;         /*!< SDMMC data timer register,                Address offset: 0x24 */
  __IO uint32_t DLEN;           /*!< SDMMC data length register,               Address offset: 0x28 */
  __IO uint32_t DCTRL;          /*!< SDMMC data control register,              Address offset: 0x2C */
  __I uint32_t  DCOUNT;         /*!< SDMMC data counter register,              Address offset: 0x30 */
  __I uint32_t  STA;            /*!< SDMMC status register,                    Address offset: 0x34 */
  __IO uint32_t ICR;            /*!< SDMMC interrupt clear register,           Address offset: 0x38 */
  __IO uint32_t MASK;           /*!< SDMMC mask register,                      Address offset: 0x3C */
  __IO uint32_t ACKTIME;        /*!< SDMMC Acknowledgement timer register,     Address offset: 0x40 */
  uint32_t      RESERVED0[3];   /*!< Reserved, 0x44 - 0x4C - 0x4C                                   */
  __IO uint32_t IDMACTRL;       /*!< SDMMC DMA control register,               Address offset: 0x50 */
  __IO uint32_t IDMABSIZE;      /*!< SDMMC DMA buffer size register,           Address offset: 0x54 */
  __IO uint32_t IDMABASE0;      /*!< SDMMC DMA buffer 0 base address register, Address offset: 0x58 */
  __IO uint32_t IDMABASE1;      /*!< SDMMC DMA buffer 1 base address register, Address offset: 0x5C */
  uint32_t      RESERVED1[1];   /*!< Reserved, 0x60                                            */
  __IO uint32_t IDMALAR;        /*!< SDMMC DMA linked list address register,   Address offset: 0x64 */
  __IO uint32_t IDMABAR;        /*!< SDMMC DMA linked list memory base register, Address offset: 0x68 */
  uint32_t      RESERVED2[5];   /*!< Reserved, 0x6C-0x7C                                            */
  __IO uint32_t FIFO;           /*!< SDMMC data FIFO register,                Address offset: 0x80 - 0xBC */
  uint32_t      RESERVED3[220]; /*!< Reserved, 0xBC-0x3F4                                           */
  __IO uint32_t VERR;           /*!< SDMMC version register,                  Address offset: 0x3F4 */
  __IO uint32_t IPIDR;           /*!< SDMMC identification register,          Address offset: 0x3F8 */
  __IO uint32_t SIDR;           /*!< SDMMCsize ID register,                   Address offset: 0x3FC */
} SDMMC_TypeDef;


/**
  * @brief Delay Block DLYB
  */

typedef struct
{
  __IO uint32_t CR;          /*!< DELAY BLOCK control register,          Address offset: 0x00 */
  __IO uint32_t CFGR;        /*!< DELAY BLOCK configuration register,    Address offset: 0x04 */
  uint32_t  Reserved[249];   /* Reserved                         Address offset: 0x08 - 0x3F0 */
  __IO uint32_t VERR;        /*!< DELAY BLOCK Version register,         Address offset: 0x3F4 */
  __IO uint32_t IPIDR;       /*!< DELAY BLOCK Identification register,  Address offset: 0x3F8 */
  __IO uint32_t SIDR;        /*!< DELAY BLOCK Size ID register,         Address offset: 0x3FC */
} DLYB_TypeDef;

/**
  * @brief HW Semaphore HSEM
  */

typedef struct
{
  __IO uint32_t R[32];      /*!< 2-step write lock and read back registers,     Address offset: 00h-7Ch  */
  __IO uint32_t RLR[32];    /*!< 1-step read lock registers,                    Address offset: 80h-FCh  */
  __IO uint32_t C1IER;      /*!< HSEM Interrupt 0 enable register ,             Address offset: 100h     */
  __IO uint32_t C1ICR;      /*!< HSEM Interrupt 0 clear register ,              Address offset: 104h     */
  __IO uint32_t C1ISR;      /*!< HSEM Interrupt 0 Status register ,             Address offset: 108h     */
  __IO uint32_t C1MISR;     /*!< HSEM Interrupt 0 Masked Status register ,      Address offset: 10Ch     */
  __IO uint32_t C2IER;      /*!< HSEM Interrupt 1 enable register ,             Address offset: 110h     */
  __IO uint32_t C2ICR;      /*!< HSEM Interrupt 1 clear register ,              Address offset: 114h     */
  __IO uint32_t C2ISR;      /*!< HSEM Interrupt 1 Status register ,             Address offset: 118h     */
  __IO uint32_t C2MISR;     /*!< HSEM Interrupt 1 Masked Status register ,      Address offset: 11Ch     */
   uint32_t  Reserved[8];        /* Reserved                                         Address offset: 120h-13Ch*/
  __IO uint32_t CR;         /*!< HSEM Semaphore clear register ,                Address offset: 140h      */
  __IO uint32_t KEYR;       /*!< HSEM Semaphore clear key register ,            Address offset: 144h      */
  uint32_t  Reserved1[169];      /* Reserved                                         Address offset: 148h-3E8h */
  __IO uint32_t HWCFGR2;    /*!< HSEM Hardware Configuration Register 2 ,       Address offset: 3ECh      */
  __IO uint32_t HWCFGR1;    /*!< HSEM Hardware Configuration Register 1 ,       Address offset: 3F0h      */
  __IO uint32_t VERR;       /*!< HSEM IP Version Register ,                     Address offset: 3F4h      */
  __IO uint32_t IPIDR;      /*!< HSEM IP Identification Register ,              Address offset: 3F8h      */
  __IO uint32_t SIDR;      /*!< HSEM Size Identification Register ,             Address offset: 3FCh      */
} HSEM_TypeDef;

typedef struct
{
  __IO uint32_t IER;        /*!< HSEM interrupt enable register ,                Address offset:   0h     */
  __IO uint32_t ICR;        /*!< HSEM interrupt clear register ,                 Address offset:   4h     */
  __IO uint32_t ISR;        /*!< HSEM interrupt status register ,                Address offset:   8h     */
  __IO uint32_t MISR;       /*!< HSEM masked interrupt status register ,         Address offset:   Ch     */
} HSEM_Common_TypeDef;

/**
  * @brief Serial Peripheral Interface
  */

typedef struct
{
  __IO uint32_t CR1;          /*!< SPI Control register 1,                             Address offset: 0x00 */
  __IO uint32_t CR2;          /*!< SPI Control register 2,                             Address offset: 0x04 */
  __IO uint32_t CFG1;         /*!< SPI Status register,                                Address offset: 0x08 */
  __IO uint32_t CFG2;         /*!< SPI Status register,                                Address offset: 0x0C */
  __IO uint32_t IER;          /*!< SPI data register,                                  Address offset: 0x10 */
  __IO uint32_t SR;           /*!< SPI data register,                                  Address offset: 0x14 */
  __IO uint32_t IFCR;         /*!< SPI data register,                                  Address offset: 0x18 */
  uint32_t      RESERVED0;    /*!< SPI data register,                                  Address offset: 0x1C */
  __IO uint32_t TXDR;         /*!< SPI data register,                                  Address offset: 0x20 */
  uint32_t      RESERVED1[3]; /*!< Reserved, 0x24-0x2C                                                      */
  __IO uint32_t RXDR;         /*!< SPI data register,                                  Address offset: 0x30 */
  uint32_t      RESERVED2[3]; /*!< Reserved, 0x34-0x3C                                                      */
  __IO uint32_t CRCPOLY;     /*!< SPI data register,                                   Address offset: 0x40 */
  __IO uint32_t TXCRC;       /*!< SPI data register,                                   Address offset: 0x44 */
  __IO uint32_t RXCRC;       /*!< SPI data register,                                   Address offset: 0x48 */
  __IO uint32_t UDRDR;       /*!< SPI data register,                                   Address offset: 0x4C */
  __IO uint32_t I2SCFGR;     /*!< SPI data register,                                   Address offset: 0x50 */
  uint32_t      RESERVED3[231]; /*!< Reserved, 0x54-0x3EC                                                   */
  __IO uint32_t HWCFGR;       /*!< SPI HW Configuration register,                     Address offset: 0x3F0 */
  __IO uint32_t VERR;         /*!< SPI Version register,                              Address offset: 0x3F4 */
  __IO uint32_t IPIDR;        /*!< SPI identification register,                       Address offset: 0x3F8 */
  __IO uint32_t SIDR;         /*!< SPI Size Identification register,                  Address offset: 0x3FC */
} SPI_TypeDef;

/**
  * @brief QUAD Serial Peripheral Interface
  */

typedef struct
{
  __IO uint32_t CR;       /*!< QUADSPI Control register,                           Address offset: 0x00 */
  __IO uint32_t DCR;      /*!< QUADSPI Device Configuration register,              Address offset: 0x04 */
  __IO uint32_t SR;       /*!< QUADSPI Status register,                            Address offset: 0x08 */
  __IO uint32_t FCR;      /*!< QUADSPI Flag Clear register,                        Address offset: 0x0C */
  __IO uint32_t DLR;      /*!< QUADSPI Data Length register,                       Address offset: 0x10 */
  __IO uint32_t CCR;      /*!< QUADSPI Communication Configuration register,       Address offset: 0x14 */
  __IO uint32_t AR;       /*!< QUADSPI Address register,                           Address offset: 0x18 */
  __IO uint32_t ABR;      /*!< QUADSPI Alternate Bytes register,                   Address offset: 0x1C */
  __IO uint32_t DR;       /*!< QUADSPI Data register,                              Address offset: 0x20 */
  __IO uint32_t PSMKR;    /*!< QUADSPI Polling Status Mask register,               Address offset: 0x24 */
  __IO uint32_t PSMAR;    /*!< QUADSPI Polling Status Match register,              Address offset: 0x28 */
  __IO uint32_t PIR;      /*!< QUADSPI Polling Interval register,                  Address offset: 0x2C */
  __IO uint32_t LPTR;     /*!< QUADSPI Low Power Timeout register,                 Address offset: 0x30 */
  uint32_t      RESERVED[239]; /*!< Reserved, 0x34-0x3EC                                                */
  __IO uint32_t HWCFGR;   /*!< QUADSPI HW configuration register,                  Address offset: 0x3F0*/
  __IO uint32_t VERR;     /*!< QUADSPI version register,                           Address offset: 0x3F4*/
  __IO uint32_t IPIDR;    /*!< QUADSPI dentification register,                     Address offset: 0x3F8*/
  __IO uint32_t SIDR;    /*!< QUADSPI size identification register,                Address offset: 0x3FC*/
} QUADSPI_TypeDef;

/**
  * @brief Temperature Sensor
  */
/* TMPSENS has been renamed in DTS*/
typedef struct
{
  __IO uint32_t CFGR1;    /*!< Temperature Sensor Configuration Register 1,         Address offset: 0x00 */
  uint32_t RESERVED0;     /*!< Reserved,                                            Address offset: 0x04 */
  __IO uint32_t T0VALR1;  /*!< Temperature sensor T0 Value Register 1,              Address offset: 0x08 */
  uint32_t RESERVED1;     /*!< Reserved,                                            Address offset: 0x0C */
  __IO uint32_t RAMPVALR; /*!< Temperature sensor Ramp Value Register,              Address offset: 0x10 */
  __IO uint32_t ITR1;     /*!< Temperature sensor Interrupt Threshold Register 1,   Address offset: 0x14 */
  uint32_t RESERVED2;     /*!< Reserved,                                            Address offset: 0x18 */
  __IO uint32_t DR;       /*!< Temperature sensor Data Register,                    Address offset: 0x1C */
  __IO uint32_t SR;       /*!< Temperature sensor Status Register,                  Address offset: 0x20 */
  __IO uint32_t ITENR;    /*!< Temperature sensor Interrupt Enable Register,        Address offset: 0x24 */
  __IO uint32_t ICIFR;    /*!< Temperature sensor clear interrupt flag register,    Address offset: 0x28 */
  __IO uint32_t OR;       /*!< Temperature sensor option register,                  Address offset: 0x2C */
}DTS_TypeDef;

/**
  * @brief TIM
  */

typedef struct
{
  __IO uint32_t CR1;         /*!< TIM control register 1,                   Address offset: 0x00 */
  __IO uint32_t CR2;         /*!< TIM control register 2,                   Address offset: 0x04 */
  __IO uint32_t SMCR;        /*!< TIM slave mode control register,          Address offset: 0x08 */
  __IO uint32_t DIER;        /*!< TIM DMA/interrupt enable register,        Address offset: 0x0C */
  __IO uint32_t SR;          /*!< TIM status register,                      Address offset: 0x10 */
  __IO uint32_t EGR;         /*!< TIM event generation register,            Address offset: 0x14 */
  __IO uint32_t CCMR1;       /*!< TIM capture/compare mode register 1,      Address offset: 0x18 */
  __IO uint32_t CCMR2;       /*!< TIM capture/compare mode register 2,      Address offset: 0x1C */
  __IO uint32_t CCER;        /*!< TIM capture/compare enable register,      Address offset: 0x20 */
  __IO uint32_t CNT;         /*!< TIM counter register,                     Address offset: 0x24 */
  __IO uint32_t PSC;         /*!< TIM prescaler,                            Address offset: 0x28 */
  __IO uint32_t ARR;         /*!< TIM auto-reload register,                 Address offset: 0x2C */
  __IO uint32_t RCR;         /*!< TIM repetition counter register,          Address offset: 0x30 */
  __IO uint32_t CCR1;        /*!< TIM capture/compare register 1,           Address offset: 0x34 */
  __IO uint32_t CCR2;        /*!< TIM capture/compare register 2,           Address offset: 0x38 */
  __IO uint32_t CCR3;        /*!< TIM capture/compare register 3,           Address offset: 0x3C */
  __IO uint32_t CCR4;        /*!< TIM capture/compare register 4,           Address offset: 0x40 */
  __IO uint32_t BDTR;        /*!< TIM break and dead-time register,         Address offset: 0x44 */
  __IO uint32_t DCR;         /*!< TIM DMA control register,                 Address offset: 0x48 */
  __IO uint32_t DMAR;        /*!< TIM DMA address for full transfer,        Address offset: 0x4C */
  uint32_t      RESERVED0;   /*!< Reserved,                                 Address offset: 0x50 */
  __IO uint32_t CCMR3;       /*!< TIM capture/compare mode register 3,      Address offset: 0x54 */
  __IO uint32_t CCR5;        /*!< TIM capture/compare register5,            Address offset: 0x58 */
  __IO uint32_t CCR6;        /*!< TIM capture/compare register6,            Address offset: 0x5C */
  __IO uint32_t AF1;         /*!< TIM alternate function option register 1, Address offset: 0x60 */
  __IO uint32_t AF2;         /*!< TIM alternate function option register 2, Address offset: 0x64 */
  __IO uint32_t TISEL;       /*!< TIM Input Selection register,             Address offset: 0x68 */
  uint32_t  RESERVED1[226];  /*!< Reserved,                                 Address offset: 0x6C-0x3F0 */
  __IO uint32_t VERR;        /*!< TIM version register,                     Address offset: 0x3F4 */
  __IO uint32_t IPIDR;       /*!< TIM Identification register,              Address offset: 0x3F8 */
  __IO uint32_t SIDR;        /*!< TIM Size Identification register,         Address offset: 0x3FC */
} TIM_TypeDef;

/**
  * @brief LPTIMIMER
  */
typedef struct
{
  __IO uint32_t ISR;      /*!< LPTIM Interrupt and Status register,                Address offset: 0x00 */
  __IO uint32_t ICR;      /*!< LPTIM Interrupt Clear register,                     Address offset: 0x04 */
  __IO uint32_t IER;      /*!< LPTIM Interrupt Enable register,                    Address offset: 0x08 */
  __IO uint32_t CFGR;     /*!< LPTIM Configuration register,                       Address offset: 0x0C */
  __IO uint32_t CR;       /*!< LPTIM Control register,                             Address offset: 0x10 */
  __IO uint32_t CMP;      /*!< LPTIM Compare register,                             Address offset: 0x14 */
  __IO uint32_t ARR;      /*!< LPTIM Autoreload register,                          Address offset: 0x18 */
  __IO uint32_t CNT;      /*!< LPTIM Counter register,                             Address offset: 0x1C */
  uint16_t  RESERVED1;    /*!< Reserved, 0x20                                                 */
  __IO uint32_t CFGR2;    /*!< LPTIM Option register,                              Address offset: 0x24 */
  uint32_t  RESERVED2[242];    /*!< Reserved, 0x28-0x3EC                                                */
  __IO uint32_t HWCFGR;   /*!< LPTIM HW configuration register,                    Address offset: 0x3F0 */
  __IO uint32_t VERR;     /*!< LPTIM version register,                             Address offset: 0x3F4 */
  __IO uint32_t PIDR;     /*!< LPTIM Identification register,                      Address offset: 0x3F8 */
  __IO uint32_t SIDR;     /*!< LPTIM Size Identification register,                 Address offset: 0x3FC */
} LPTIM_TypeDef;

/**
  * @brief Comparator
  */
typedef struct
{
  __IO uint32_t SR;        /*!< Comparator status register,                    Address offset: 0x00 */
  __IO uint32_t ICFR;      /*!< Comparator interrupt clear flag register,      Address offset: 0x04 */
  __IO uint32_t OR;        /*!< Comparator option register,                    Address offset: 0x08 */
} COMPOPT_TypeDef;

typedef struct
{
  __IO uint32_t CFGR;      /*!< Comparator configuration register  ,           Address offset: 0x00 */
} COMP_TypeDef;

typedef struct
{
  __IO uint32_t CFGR;       /*!< COMP control and status register, used for bits common to several COMP instances, Address offset: 0x00 */
} COMP_Common_TypeDef;
/**
  * @brief Universal Synchronous Asynchronous Receiver Transmitter
  */

typedef struct
{
  __IO uint32_t CR1;    /*!< USART Control register 1,                 Address offset: 0x00 */
  __IO uint32_t CR2;    /*!< USART Control register 2,                 Address offset: 0x04 */
  __IO uint32_t CR3;    /*!< USART Control register 3,                 Address offset: 0x08 */
  __IO uint32_t BRR;    /*!< USART Baud rate register,                 Address offset: 0x0C */
  __IO uint16_t GTPR;   /*!< USART Guard time and prescaler register,  Address offset: 0x10 */
  uint16_t  RESERVED2;  /*!< Reserved, 0x12                                                 */
  __IO uint32_t RTOR;   /*!< USART Receiver Time Out register,         Address offset: 0x14 */
  __IO uint16_t RQR;    /*!< USART Request register,                   Address offset: 0x18 */
  uint16_t  RESERVED3;  /*!< Reserved, 0x1A                                                 */
  __IO uint32_t ISR;    /*!< USART Interrupt and status register,      Address offset: 0x1C */
  __IO uint32_t ICR;    /*!< USART Interrupt flag Clear register,      Address offset: 0x20 */
  __IO uint16_t RDR;    /*!< USART Receive Data register,              Address offset: 0x24 */
  uint16_t  RESERVED4;  /*!< Reserved, 0x26                                                 */
  __IO uint16_t TDR;    /*!< USART Transmit Data register,             Address offset: 0x28 */
  uint16_t  RESERVED5;  /*!< Reserved, 0x2A                                                 */
  __IO uint32_t PRESC;  /*!< USART clock Prescaler register,           Address offset: 0x2C */
  uint32_t  RESERVED6[239];  /*!< Reserved,                                    0x30 - 0x3E8 */
  __IO uint32_t HWCFGR2;  /*!< USART Configuration2 register,          Address offset: 0x3EC */
  __IO uint32_t HWCFGR1;  /*!< USART Configuration1 register,          Address offset: 0x3F0 */
  __IO uint32_t VERR;   /*!< USART Version register,                   Address offset: 0x3F4 */
  __IO uint32_t IPIDR;  /*!< USART Identification register,            Address offset: 0x3F8 */
  __IO uint32_t SIDR;   /*!< USART clock Size Identification register, Address offset: 0x3FC */

} USART_TypeDef;

/**
  * @brief Single Wire Protocol Master Interface SPWMI
  */
typedef struct
{
  __IO uint32_t CR;          /*!< SWPMI Configuration/Control register,     Address offset: 0x00 */
  __IO uint32_t BRR;         /*!< SWPMI bitrate register,                   Address offset: 0x04 */
    uint32_t  RESERVED1;     /*!< Reserved, 0x08                                                 */
  __IO uint32_t ISR;         /*!< SWPMI Interrupt and Status register,      Address offset: 0x0C */
  __IO uint32_t ICR;         /*!< SWPMI Interrupt Flag Clear register,      Address offset: 0x10 */
  __IO uint32_t IER;         /*!< SWPMI Interrupt Enable register,          Address offset: 0x14 */
  __IO uint32_t RFL;         /*!< SWPMI Receive Frame Length register,      Address offset: 0x18 */
  __IO uint32_t TDR;         /*!< SWPMI Transmit data register,             Address offset: 0x1C */
  __IO uint32_t RDR;         /*!< SWPMI Receive data register,              Address offset: 0x20 */
  __IO uint32_t OR;          /*!< SWPMI Option register,                    Address offset: 0x24 */
} SWPMI_TypeDef;

/**
  * @brief Window WATCHDOG
  */

typedef struct
{
  __IO uint32_t CR;      /*!< WWDG Control register,        Address offset:  0x00 */
  __IO uint32_t CFR;     /*!< WWDG Configuration register,  Address offset:  0x04 */
  __IO uint32_t SR;      /*!< WWDG Status register,         Address offset:  0x08 */
  uint32_t  RESERVED1[249];   /*!< Reserved,                         0x0C - 0x3EC */
  __IO uint32_t HWCFGR;  /*!< WWDG HW Config register,      Address offset: 0x3F0 */
  __IO uint32_t VERR;    /*!< WWDG Version register,        Address offset: 0x3F4 */
  __IO uint32_t IPIDR;   /*!< WWDG Identification register, Address offset: 0x3F8 */
  __IO uint32_t SIDR;    /*!< WWDG Size ID register,        Address offset: 0x3FC */

} WWDG_TypeDef;
/**
  * @brief Crypto Processor
  */

typedef struct
{
  __IO uint32_t CR;         /*!< CRYP control register,                                    Address offset: 0x00 */
  __IO uint32_t SR;         /*!< CRYP status register,                                     Address offset: 0x04 */
  __IO uint32_t DIN;        /*!< CRYP data input register,                                 Address offset: 0x08 */
  __IO uint32_t DOUT;       /*!< CRYP data output register,                                Address offset: 0x0C */
  __IO uint32_t DMACR;      /*!< CRYP DMA control register,                                Address offset: 0x10 */
  __IO uint32_t IMSCR;      /*!< CRYP interrupt mask set/clear register,                   Address offset: 0x14 */
  __IO uint32_t RISR;       /*!< CRYP raw interrupt status register,                       Address offset: 0x18 */
  __IO uint32_t MISR;       /*!< CRYP masked interrupt status register,                    Address offset: 0x1C */
  __IO uint32_t K0LR;       /*!< CRYP key left  register 0,                                Address offset: 0x20 */
  __IO uint32_t K0RR;       /*!< CRYP key right register 0,                                Address offset: 0x24 */
  __IO uint32_t K1LR;       /*!< CRYP key left  register 1,                                Address offset: 0x28 */
  __IO uint32_t K1RR;       /*!< CRYP key right register 1,                                Address offset: 0x2C */
  __IO uint32_t K2LR;       /*!< CRYP key left  register 2,                                Address offset: 0x30 */
  __IO uint32_t K2RR;       /*!< CRYP key right register 2,                                Address offset: 0x34 */
  __IO uint32_t K3LR;       /*!< CRYP key left  register 3,                                Address offset: 0x38 */
  __IO uint32_t K3RR;       /*!< CRYP key right register 3,                                Address offset: 0x3C */
  __IO uint32_t IV0LR;      /*!< CRYP initialization vector left-word  register 0,         Address offset: 0x40 */
  __IO uint32_t IV0RR;      /*!< CRYP initialization vector right-word register 0,         Address offset: 0x44 */
  __IO uint32_t IV1LR;      /*!< CRYP initialization vector left-word  register 1,         Address offset: 0x48 */
  __IO uint32_t IV1RR;      /*!< CRYP initialization vector right-word register 1,         Address offset: 0x4C */
  __IO uint32_t CSGCMCCM0R; /*!< CRYP GCM/GMAC or CCM/CMAC context swap register 0,        Address offset: 0x50 */
  __IO uint32_t CSGCMCCM1R; /*!< CRYP GCM/GMAC or CCM/CMAC context swap register 1,        Address offset: 0x54 */
  __IO uint32_t CSGCMCCM2R; /*!< CRYP GCM/GMAC or CCM/CMAC context swap register 2,        Address offset: 0x58 */
  __IO uint32_t CSGCMCCM3R; /*!< CRYP GCM/GMAC or CCM/CMAC context swap register 3,        Address offset: 0x5C */
  __IO uint32_t CSGCMCCM4R; /*!< CRYP GCM/GMAC or CCM/CMAC context swap register 4,        Address offset: 0x60 */
  __IO uint32_t CSGCMCCM5R; /*!< CRYP GCM/GMAC or CCM/CMAC context swap register 5,        Address offset: 0x64 */
  __IO uint32_t CSGCMCCM6R; /*!< CRYP GCM/GMAC or CCM/CMAC context swap register 6,        Address offset: 0x68 */
  __IO uint32_t CSGCMCCM7R; /*!< CRYP GCM/GMAC or CCM/CMAC context swap register 7,        Address offset: 0x6C */
  __IO uint32_t CSGCM0R;    /*!< CRYP GCM/GMAC context swap register 0,                    Address offset: 0x70 */
  __IO uint32_t CSGCM1R;    /*!< CRYP GCM/GMAC context swap register 1,                    Address offset: 0x74 */
  __IO uint32_t CSGCM2R;    /*!< CRYP GCM/GMAC context swap register 2,                    Address offset: 0x78 */
  __IO uint32_t CSGCM3R;    /*!< CRYP GCM/GMAC context swap register 3,                    Address offset: 0x7C */
  __IO uint32_t CSGCM4R;    /*!< CRYP GCM/GMAC context swap register 4,                    Address offset: 0x80 */
  __IO uint32_t CSGCM5R;    /*!< CRYP GCM/GMAC context swap register 5,                    Address offset: 0x84 */
  __IO uint32_t CSGCM6R;    /*!< CRYP GCM/GMAC context swap register 6,                    Address offset: 0x88 */
  __IO uint32_t CSGCM7R;    /*!< CRYP GCM/GMAC context swap register 7,                    Address offset: 0x8C */
  uint32_t RESERVED[216];
  __IO uint32_t HWCFGR;     /*!< CRYP HW Configuration,                                    Address offset: 0x3F0 */
  __IO uint32_t VERR;       /*!< CRYP version register ,                                   Address offset: 0x3F4 */
  __IO uint32_t IPIDR;      /*!< CRYP Identification register,                             Address offset: 0x3F8 */
  __IO uint32_t MID;        /*!< CRYP HW Magic ID register,                                Address offset: 0x3FC */
} CRYP_TypeDef;
/**
  * @brief HASH
  */

typedef struct
{
  __IO uint32_t CR;               /*!< HASH control register,          Address offset: 0x00        */
  __IO uint32_t DIN;              /*!< HASH data input register,       Address offset: 0x04        */
  __IO uint32_t STR;              /*!< HASH start register,            Address offset: 0x08        */
  __IO uint32_t HR[5];            /*!< HASH digest registers,          Address offset: 0x0C-0x1C   */
  __IO uint32_t IMR;              /*!< HASH interrupt enable register, Address offset: 0x20        */
  __IO uint32_t SR;               /*!< HASH status register,           Address offset: 0x24        */
       uint32_t RESERVED[52];     /*!< Reserved, 0x28-0xF4                                         */
  __IO uint32_t CSR[54];          /*!< HASH context swap registers,    Address offset: 0x0F8-0x1CC */
       uint32_t RESERVED2[80];
  __IO uint32_t HR2[8];
       uint32_t RESERVED3[48];
  __IO uint32_t HWCFGR;           /*!< HASH Hardware configuration register, Address offset: 0x3F0 */
  __IO uint32_t VERR;           /*!< HASH Version register,                   Address offset: 0x3F4 */
  __IO uint32_t IPIDR;           /*!< HASH identification register,             Address offset: 0x3F8 */
  __IO uint32_t MID;           /*!< HASH Hardware Magic ID register,         Address offset: 0x3FC */
} HASH_TypeDef;

/**
  * @brief HASH_DIGEST
  */

typedef struct
{
  __IO uint32_t HR[8];     /*!< HASH digest registers,          Address offset: 0x310-0x32C */
} HASH_DIGEST_TypeDef;


/**
  * @brief RNG
  */
typedef struct
{
  __IO uint32_t CR;              /*!< RNG control register,             Address offset: 0x00  */
  __IO uint32_t SR;              /*!< RNG status register,              Address offset: 0x04  */
  __IO uint32_t DR;              /*!< RNG data register,                Address offset: 0x08  */
  __IO uint32_t RESERVED1[249];  /*!< Reserved                          Address offset: 0x0C - 0x3EC */
  __IO uint32_t HWCFGR;          /*!< RNG HW Configuration register,    Address offset: 0x3F0 */
  __IO uint32_t VERR;            /*!< RNG Version register,             Address offset: 0x3F4 */
  __IO uint32_t IPIDR;           /*!< RNG identification register,      Address offset: 0x3F8 */
  __IO uint32_t SIDR;            /*!< RNG HW magic ID,                  Address offset: 0x3FC */
} RNG_TypeDef;

/**
  * @brief Inter-Processor Communication
  */
typedef struct
{
  __IO uint32_t C1CR;             /*!< Inter-Processor Communication: C1 control register,                  Address offset: 0x000 */
  __IO uint32_t C1MR ;            /*!< Inter-Processor Communication: C1 mask register,                     Address offset: 0x004 */
  __IO uint32_t C1SCR;            /*!< Inter-Processor Communication: C1 status set clear register,         Address offset: 0x008 */
  __IO uint32_t C1TOC2SR;         /*!< Inter-Processor Communication: C1 to processor M4  status register,  Address offset: 0x00C */
  __IO uint32_t C2CR;             /*!< Inter-Processor Communication: C2 control register,                  Address offset: 0x010 */
  __IO uint32_t C2MR ;            /*!< Inter-Processor Communication: C2 mask register,                     Address offset: 0x014 */
  __IO uint32_t C2SCR;            /*!< Inter-Processor Communication: C2 status set clear register,         Address offset: 0x018 */
  __IO uint32_t C2TOC1SR;         /*!< Inter-Processor Communication: C2 to processor M4 status register,   Address offset: 0x01C */
  __IO uint32_t RESERVED1[244];   /*!< Reserved                                                                                   */
  __IO uint32_t HWCFGR;           /*!< Inter-Processor Communication hardware configuration register,       Address offset: 0x3F0 */
  __IO uint32_t VER;             /*!< Inter-Processor Communication version register,                      Address offset: 0x3F4 */
  __IO uint32_t ID;            /*!< Inter-Processor Communication identification register,               Address offset: 0x3F8 */
  __IO uint32_t SID;             /*!< Inter-Processor Communication size identification register,          Address offset: 0x3FC */
} IPCC_TypeDef;

typedef struct
{
  __IO uint32_t CR;               /*!< Control register,                                                    Address offset: 0x000 */
  __IO uint32_t MR;               /*!< Mask register,                                                       Address offset: 0x004 */
  __IO uint32_t SCR;              /*!< Status set clear register,                                           Address offset: 0x008 */
  __IO uint32_t SR;               /*!< Status register,                                                     Address offset: 0x00C */
} IPCC_CommonTypeDef;

/**
  * @brief MDIOS
  */

typedef struct
{
  __IO uint32_t CR;               /*!< Control register,                                                    Address offset: 0x000 */
  __IO uint32_t WRFR;             /*!< Write Flag register,                                                 Address offset: 0x004 */
  __IO uint32_t CWRFR;            /*!< Clear Write Flag register,                                           Address offset: 0x008 */
  __IO uint32_t RDFR;             /*!< Read Flag register,                                                  Address offset: 0x00C */
  __IO uint32_t CRDFR;            /*!< Clear Read Flag register,                                            Address offset: 0x010 */
  __IO uint32_t SR;               /*!< Status register,                                                     Address offset: 0x014 */
  __IO uint32_t CLRFR;            /*!< Clear Flag register,                                                 Address offset: 0x018 */
  uint32_t RESERVED[57];          /*!< Reserved,                                                    Address offset: 0x01C - 0x0FC */
  __IO uint32_t DINR0;            /*!< Input Data register 0                                                Address offset: 0x100 */
  __IO uint32_t DINR1;            /*!< Input Data register 1                                                Address offset: 0x104 */
  __IO uint32_t DINR2;            /*!< Input Data register 2                                                Address offset: 0x108 */
  __IO uint32_t DINR3;            /*!< Input Data register 3                                                Address offset: 0x10C */
  __IO uint32_t DINR4;            /*!< Input Data register 4                                                Address offset: 0x110 */
  __IO uint32_t DINR5;            /*!< Input Data register 5                                                Address offset: 0x114 */
  __IO uint32_t DINR6;            /*!< Input Data register 6                                                Address offset: 0x118 */
  __IO uint32_t DINR7;            /*!< Input Data register 7                                                Address offset: 0x11C */
  __IO uint32_t DINR8;            /*!< Input Data register 8                                                Address offset: 0x120 */
  __IO uint32_t DINR9;            /*!< Input Data register 9                                                Address offset: 0x124 */
  __IO uint32_t DINR10;           /*!< Input Data register 10                                               Address offset: 0x128 */
  __IO uint32_t DINR11;           /*!< Input Data register 11                                               Address offset: 0x12C */
  __IO uint32_t DINR12;           /*!< Input Data register 12                                               Address offset: 0x130 */
  __IO uint32_t DINR13;           /*!< Input Data register 13                                               Address offset: 0x134 */
  __IO uint32_t DINR14;           /*!< Input Data register 14                                               Address offset: 0x138 */
  __IO uint32_t DINR15;           /*!< Input Data register 15                                               Address offset: 0x13C */
  __IO uint32_t DINR16;           /*!< Input Data register 16                                               Address offset: 0x140 */
  __IO uint32_t DINR17;           /*!< Input Data register 17                                               Address offset: 0x144 */
  __IO uint32_t DINR18;           /*!< Input Data register 18                                               Address offset: 0x148 */
  __IO uint32_t DINR19;           /*!< Input Data register 19                                               Address offset: 0x14C */
  __IO uint32_t DINR20;           /*!< Input Data register 20                                               Address offset: 0x150 */
  __IO uint32_t DINR21;           /*!< Input Data register 21                                               Address offset: 0x154 */
  __IO uint32_t DINR22;           /*!< Input Data register 22                                               Address offset: 0x158 */
  __IO uint32_t DINR23;           /*!< Input Data register 23                                               Address offset: 0x15C */
  __IO uint32_t DINR24;           /*!< Input Data register 24                                               Address offset: 0x160 */
  __IO uint32_t DINR25;           /*!< Input Data register 25                                               Address offset: 0x164 */
  __IO uint32_t DINR26;           /*!< Input Data register 26                                               Address offset: 0x168 */
  __IO uint32_t DINR27;           /*!< Input Data register 27                                               Address offset: 0x16C */
  __IO uint32_t DINR28;           /*!< Input Data register 28                                               Address offset: 0x170 */
  __IO uint32_t DINR29;           /*!< Input Data register 29                                               Address offset: 0x174 */
  __IO uint32_t DINR30;           /*!< Input Data register 30                                               Address offset: 0x178 */
  __IO uint32_t DINR31;           /*!< Input Data register 31                                               Address offset: 0x17C */
  __IO uint32_t DOUTR0;           /*!< Output Data register 0                                               Address offset: 0x180 */
  __IO uint32_t DOUTR1;           /*!< Output Data register 1                                               Address offset: 0x184 */
  __IO uint32_t DOUTR2;           /*!< Output Data register 2                                               Address offset: 0x188 */
  __IO uint32_t DOUTR3;           /*!< Output Data register 3                                               Address offset: 0x18C */
  __IO uint32_t DOUTR4;           /*!< Output Data register 4                                               Address offset: 0x190 */
  __IO uint32_t DOUTR5;           /*!< Output Data register 5                                               Address offset: 0x194 */
  __IO uint32_t DOUTR6;           /*!< Output Data register 6                                               Address offset: 0x198 */
  __IO uint32_t DOUTR7;           /*!< Output Data register 7                                               Address offset: 0x19C */
  __IO uint32_t DOUTR8;           /*!< Output Data register 8                                               Address offset: 0x1A0 */
  __IO uint32_t DOUTR9;           /*!< Output Data register 9                                               Address offset: 0x1A4 */
  __IO uint32_t DOUTR10;          /*!< Output Data register 10                                              Address offset: 0x1A8 */
  __IO uint32_t DOUTR11;          /*!< Output Data register 11                                              Address offset: 0x1AC */
  __IO uint32_t DOUTR12;          /*!< Output Data register 12                                              Address offset: 0x1B0 */
  __IO uint32_t DOUTR13;          /*!< Output Data register 13                                              Address offset: 0x1B4 */
  __IO uint32_t DOUTR14;          /*!< Output Data register 14                                              Address offset: 0x1B8 */
  __IO uint32_t DOUTR15;          /*!< Output Data register 15                                              Address offset: 0x1BC */
  __IO uint32_t DOUTR16;          /*!< Output Data register 16                                              Address offset: 0x1C0 */
  __IO uint32_t DOUTR17;          /*!< Output Data register 17                                              Address offset: 0x1C4 */
  __IO uint32_t DOUTR18;          /*!< Output Data register 18                                              Address offset: 0x1C8 */
  __IO uint32_t DOUTR19;          /*!< Output Data register 19                                              Address offset: 0x1CC */
  __IO uint32_t DOUTR20;          /*!< Output Data register 20                                              Address offset: 0x1D0 */
  __IO uint32_t DOUTR21;          /*!< Output Data register 21                                              Address offset: 0x1D4 */
  __IO uint32_t DOUTR22;          /*!< Output Data register 22                                              Address offset: 0x1D8 */
  __IO uint32_t DOUTR23;          /*!< Output Data register 23                                              Address offset: 0x1DC */
  __IO uint32_t DOUTR24;          /*!< Output Data register 24                                              Address offset: 0x1E0 */
  __IO uint32_t DOUTR25;          /*!< Output Data register 25                                              Address offset: 0x1E4 */
  __IO uint32_t DOUTR26;          /*!< Output Data register 26                                              Address offset: 0x1E8 */
  __IO uint32_t DOUTR27;          /*!< Output Data register 27                                              Address offset: 0x1EC */
  __IO uint32_t DOUTR28;          /*!< Output Data register 28                                              Address offset: 0x1F0 */
  __IO uint32_t DOUTR29;          /*!< Output Data register 29                                              Address offset: 0x1F4 */
  __IO uint32_t DOUTR30;          /*!< Output Data register 30                                              Address offset: 0x1F8 */
  __IO uint32_t DOUTR31;          /*!< Output Data register 31                                              Address offset: 0x1FC */
  uint32_t RESERVED1[124]; /*!< Reserved                                     0x200 - 0x3EC */
  __IO uint32_t HWCFGR;    /*!< MDIOS HW Configuration register,     Address offset: 0x3F0 */
  __IO uint32_t VERR;      /*!< MDIOS Version register,              Address offset: 0x3F4 */
  __IO uint32_t IPIDR;     /*!< MDIOS identification register,       Address offset: 0x3F8 */
  __IO uint32_t SIDR;      /*!< MDIOS Size ID register,              Address offset: 0x3FC */
} MDIOS_TypeDef;


/**
  * @brief USB_OTG_Core_Registers
  */
typedef struct
{
 __IO uint32_t GOTGCTL;               /*!< USB_OTG Control and Status Register          000h */
  __IO uint32_t GOTGINT;              /*!< USB_OTG Interrupt Register                   004h */
  __IO uint32_t GAHBCFG;              /*!< Core AHB Configuration Register              008h */
  __IO uint32_t GUSBCFG;              /*!< Core USB Configuration Register              00Ch */
  __IO uint32_t GRSTCTL;              /*!< Core Reset Register                          010h */
  __IO uint32_t GINTSTS;              /*!< Core Interrupt Register                      014h */
  __IO uint32_t GINTMSK;              /*!< Core Interrupt Mask Register                 018h */
  __IO uint32_t GRXSTSR;              /*!< Receive Sts Q Read Register                  01Ch */
  __IO uint32_t GRXSTSP;              /*!< Receive Sts Q Read & POP Register            020h */
  __IO uint32_t GRXFSIZ;              /*!< Receive FIFO Size Register                   024h */
  __IO uint32_t DIEPTXF0_HNPTXFSIZ;   /*!< EP0 / Non Periodic Tx FIFO Size Register     028h */
  __IO uint32_t HNPTXSTS;             /*!< Non Periodic Tx FIFO/Queue Sts reg           02Ch */
  __IO uint32_t GI2CCTL;              /*!< I2C Access Register                          030h */
  uint32_t Reserved30;                /*!< Reserved                                     034h */
  __IO uint32_t GCCFG;                /*!< General Purpose IO Register                  038h */
  __IO uint32_t CID;                  /*!< User ID Register                             03Ch */
  uint32_t  Reserved5[4];             /*!< Reserved                                040h-048h */
  uint32_t  Reserved6;                /*!< Reserved                                     050h */
  __IO uint32_t GLPMCFG;              /*!< LPM Register                                 054h */
  uint32_t  Reserved43[42];         /*!< Reserved                                  058h-0FFh */
  __IO uint32_t HPTXFSIZ;             /*!< Host Periodic Tx FIFO Size Reg               100h */
  __IO uint32_t DIEPTXF[0x0F];        /*!< dev Periodic Transmit FIFO */
} USB_OTG_GlobalTypeDef;


/**
  * @brief USB_OTG_device_Registers
  */
typedef struct
{
  __IO uint32_t DCFG;            /*!< dev Configuration Register   800h */
  __IO uint32_t DCTL;            /*!< dev Control Register         804h */
  __IO uint32_t DSTS;            /*!< dev Status Register (RO)     808h */
  uint32_t Reserved0C;           /*!< Reserved                     80Ch */
  __IO uint32_t DIEPMSK;         /*!< dev IN Endpoint Mask         810h */
  __IO uint32_t DOEPMSK;         /*!< dev OUT Endpoint Mask        814h */
  __IO uint32_t DAINT;           /*!< dev All Endpoints Itr Reg    818h */
  __IO uint32_t DAINTMSK;        /*!< dev All Endpoints Itr Mask   81Ch */
  uint32_t  Reserved20;          /*!< Reserved                     820h */
  uint32_t Reserved9;            /*!< Reserved                     824h */
  __IO uint32_t DVBUSDIS;        /*!< dev VBUS discharge Register  828h */
  __IO uint32_t DVBUSPULSE;      /*!< dev VBUS Pulse Register      82Ch */
  __IO uint32_t DTHRCTL;         /*!< dev threshold                830h */
  __IO uint32_t DIEPEMPMSK;      /*!< dev empty msk                834h */
  __IO uint32_t DEACHINT;        /*!< dedicated EP interrupt       838h */
  __IO uint32_t DEACHMSK;        /*!< dedicated EP msk             83Ch */
  uint32_t Reserved40;           /*!< dedicated EP mask            840h */
  __IO uint32_t DINEP1MSK;       /*!< dedicated EP mask            844h */
  uint32_t  Reserved44[15];      /*!< Reserved                 844-87Ch */
  __IO uint32_t DOUTEP1MSK;      /*!< dedicated EP msk             884h */
} USB_OTG_DeviceTypeDef;


/**
  * @brief USB_OTG_IN_Endpoint-Specific_Register
  */
typedef struct
{
  __IO uint32_t DIEPCTL;           /*!< dev IN Endpoint Control Reg    900h + (ep_num * 20h) + 00h */
  uint32_t Reserved04;             /*!< Reserved                       900h + (ep_num * 20h) + 04h */
  __IO uint32_t DIEPINT;           /*!< dev IN Endpoint Itr Reg        900h + (ep_num * 20h) + 08h */
  uint32_t Reserved0C;             /*!< Reserved                       900h + (ep_num * 20h) + 0Ch */
  __IO uint32_t DIEPTSIZ;          /*!< IN Endpoint Txfer Size         900h + (ep_num * 20h) + 10h */
  __IO uint32_t DIEPDMA;           /*!< IN Endpoint DMA Address Reg    900h + (ep_num * 20h) + 14h */
  __IO uint32_t DTXFSTS;           /*!< IN Endpoint Tx FIFO Status Reg 900h + (ep_num * 20h) + 18h */
  uint32_t Reserved18;             /*!< Reserved  900h+(ep_num*20h)+1Ch-900h+ (ep_num * 20h) + 1Ch */
} USB_OTG_INEndpointTypeDef;


/**
  * @brief USB_OTG_OUT_Endpoint-Specific_Registers
  */
typedef struct
{
  __IO uint32_t DOEPCTL;       /*!< dev OUT Endpoint Control Reg           B00h + (ep_num * 20h) + 00h */
  uint32_t Reserved04;         /*!< Reserved                               B00h + (ep_num * 20h) + 04h */
  __IO uint32_t DOEPINT;       /*!< dev OUT Endpoint Itr Reg               B00h + (ep_num * 20h) + 08h */
  uint32_t Reserved0C;         /*!< Reserved                               B00h + (ep_num * 20h) + 0Ch */
  __IO uint32_t DOEPTSIZ;      /*!< dev OUT Endpoint Txfer Size            B00h + (ep_num * 20h) + 10h */
  __IO uint32_t DOEPDMA;       /*!< dev OUT Endpoint DMA Address           B00h + (ep_num * 20h) + 14h */
  uint32_t Reserved18[2];      /*!< Reserved B00h + (ep_num * 20h) + 18h - B00h + (ep_num * 20h) + 1Ch */
} USB_OTG_OUTEndpointTypeDef;


/**
  * @brief USB_OTG_Host_Mode_Register_Structures
  */
typedef struct
{
  __IO uint32_t HCFG;             /*!< Host Configuration Register           400h */
  __IO uint32_t HFIR;             /*!< Host Frame Interval Register          404h */
  __IO uint32_t HFNUM;            /*!< Host Frame Nbr/Frame Remaining        408h */
  uint32_t Reserved40C;           /*!< Reserved                              40Ch */
  __IO uint32_t HPTXSTS;          /*!< Host Periodic Tx FIFO/ Queue Status   410h */
  __IO uint32_t HAINT;            /*!< Host All Channels Interrupt Register  414h */
  __IO uint32_t HAINTMSK;         /*!< Host All Channels Interrupt Mask      418h */
  __IO uint32_t HFLBADDR;         /*!< Host frame list base address register 41Ch */
  uint32_t Reserved420[8];        /*!< Reserved                              420h */
  __IO uint32_t HPRT;             /*!< Host port control and status register 440h */
} USB_OTG_HostTypeDef;

/**
  * @brief USB_OTG_Host_Channel_Specific_Registers
  */
typedef struct
{
  __IO uint32_t HCCHAR;           /*!< Host Channel Characteristics Register    500h */
  __IO uint32_t HCSPLT;           /*!< Host Channel Split Control Register      504h */
  __IO uint32_t HCINT;            /*!< Host Channel Interrupt Register          508h */
  __IO uint32_t HCINTMSK;         /*!< Host Channel Interrupt Mask Register     50Ch */
  __IO uint32_t HCTSIZ;           /*!< Host Channel Transfer Size Register      510h */
  __IO uint32_t HCDMA;            /*!< Host Channel DMA Address Register        514h */
  uint32_t Reserved0;             /*!< Reserved                                 518h */
  __IO uint32_t HCDMAB;           /*!< Host Channel DMA Address Buffer Register 51Ch */
  uint32_t Reserved[2];           /*!< Reserved                                      */
} USB_OTG_HostChannelTypeDef;
/**
  * @}
  */

/**
  * @brief USB_EHCI Capability Registers
  */
typedef struct
{
  __IO uint32_t HCCAPBASE;        /*!< Capability Register register,              Address offset: 0x00 */
  __IO uint32_t HCSPARAMS;        /*!< Structural Parameter register              Address offset: 0x04 */
  __IO uint32_t HCCPARAMS;        /*!< Capability Parameter register,             Address offset: 0x08 */
       uint32_t RESERVED;         /*!< USB Command register,                      Address offset: 0x0C */
  __IO uint32_t USBCMD;           /*!< USB Command register,                      Address offset: 0x10 */
  __IO uint32_t USBSTS;           /*!< USB Status register,                       Address offset: 0x14 */
  __IO uint32_t USBINTR;          /*!< USB Interrupt Enable register,             Address offset: 0x18 */
  __IO uint32_t FRINDEX;          /*!< USB Frame Index register ,                 Address offset: 0x1C */
  __IO uint32_t CTRLDSSEGMENT;    /*!< 4G Segment Selector register,              Address offset: 0x20 */
  __IO uint32_t PERIODICLISTBASE; /*!< Periodic Frame List Base Address register, Address offset: 0x24 */
  __IO uint32_t ASYNCLISTADDR;    /*!< Asynchronous List Address register,        Address offset: 0x28 */
} USB_EHCI_CapabilityTypeDef;
/**
  * @}
  */

/**
  * @brief GPU host interface registers
  */
typedef struct
{
  __IO uint32_t CLKCTRLR;     /*!< Clock control register                           Address offset: 0x00 */
  __IO uint32_t IDLESR;       /*!< IDLE status register                             Address offset: 0x04 */
  __IO uint32_t AXICFGR;      /*!< AXI Configuration register                       Address offset: 0x08 */
  __IO uint32_t AXISR;        /*!< AXI Status register,                             Address offset: 0x0C */
  __IO uint32_t INTRACK;      /*!< Interrupt acknowledge register,                  Address offset: 0x10 */
  __IO uint32_t INTREN;       /*!< Interrupt enable register,                       Address offset: 0x14 */
  __IO uint32_t CHIPID;       /*!< Chip ID,                                         Address offset: 0x18 */
  __IO uint32_t CHIPREV;      /*!< Chip revision register,                          Address offset: 0x1C */
  __IO uint32_t CHIPDATE;     /*!< Release date register,                           Address offset: 0x20 */
  __IO uint32_t CHIPTIME;     /*!< Release Time register,                           Address offset: 0x24 */
  __IO uint32_t TOTALCYCLES;  /*!< Total number of Cycles register,                 Address offset: 0x28 */
  __IO uint32_t PRODUCTID;    /*!< Product ID register,                             Address offset: 0x2C */
  __IO uint32_t POWERCTRLR;   /*!< Power control register,                          Address offset: 0x30 */
  __IO uint32_t MMUCTRLR;     /*!< MMU control register,                            Address offset: 0x34 */
  __IO uint32_t MEMDEBUG;     /*!< Memory debug register,                           Address offset: 0x38 */
  __IO uint32_t CMDBUFADDR;   /*!< Command buffer base address register,            Address offset: 0x3C */
  __IO uint32_t CMDBUFCTRL;   /*!< Command buffer control register,                 Address offset: 0x40 */
} GPU_Host_InterfaceTypeDef;
/**
  * @}
  */
