# MetaModule Pro p1 board configuration

Pin map for the MetaModule Pro p1 board (`~/4ms/kicad/MetaModulePro/p1/`) on the mp2-devboard v0.1
(`~/4ms/kicad/mp2-devboard/v0.1/`). The conf headers in this directory implement this table.

Extracted from the KiCad netlists (`kicad-cli sch export netlist` on both top-level schematics),
with alternate-function numbers from the STM32MP257 pinctrl table (Linux `pinctrl-stm32mp257.c`).

Devboard J1/J2/J7 mate with pro sockets U1/U2/U3 (pro pin `A<n>`/`B<n>`/`C<n>` = devboard J1/J2/J7 pin n).
The jack board (PCM3168, jack-sense expander, MIDI, HP amp) connects to the main pro board through J21 (main) / J20 (jack board).

## MCU pins used by the pro board

| Function | Pin | Ball | Notes |
|---|---|---|---|
| SAI MCLK | PE14 | B25 | SAI1_MCLK_A AF4. VDDIO2 = 1.8V! |
| SAI LRCLK | PE11 | B23 | SAI1_FS_A AF4. VDDIO2 = 1.8V! |
| SAI SCLK | PE15 | D24 | SAI1_SCK_A AF4. VDDIO2 = 1.8V! |
| SAI DAC (MCU→codec DIN1) | PE13 | C24 | SAI1_SD_A AF4. VDDIO2 = 1.8V! |
| SAI ADC (codec DOUT1→MCU) | PB13 | A26 | SAI1_SD_B AF4 |
| CODEC_RST | PD2 | D12 | PCM3168 RST |
| I2C4 SDA / SCL | PD10 / PD11 | C17 / A15 | AF6. PCM3168 (0x44), FUSB302 (0x22), jack-sense TCA9555 U1212 (0x20) |
| JACKBRD_INT | PH9 | AA13 | U1212 INT |
| I2C2 "SDA" / "SCL" | PB5 / PB4 | C14 / B15 | **Swapped**: PB5 is I2C2_SCL, PB4 is I2C2_SDA (AF9). TCA9555 U1210 (0x21), U1211 (0x22) |
| GPIO_INT_2 | PB2 | A14 | U1210 INT |
| GPIO_INT_1 | PB11 | A11 | U1211 INT. Also devboard microSD SDDET1! |
| I2C3 SDA / SCL | PG2 / PG1 | AG5 / AD4 | AF9. TCA9555 U1213 (0x23), U1209 (0x24) |
| GPIO_INT_0 | PG7 | U2 | U1213 INT |
| GPIO_INT_3 | PC12 | AE7 | U1209 INT |
| I2C6 SDA / SCL | PG5 / PG6 | R3 / T3 | AF9. LP5018 U5 (0x28), U8 (0x29) |
| SDMMC D0..D3 | PE4, PE5, PE0, PE1 | | SDMMC1 AF10. Shared with devboard microSD CON1 |
| SDMMC CMD / CLK | PE2 / PE3 | | |
| DSI CLK, D0..D3 | DSI PHY | | 4 lanes to J11 (ER-TFT050-10 FPC) |
| SCREEN_RESET | PI6 | J3 | panel RST |
| SCREEN_LED_ENABLE | PI5 | K4 | backlight boost (AP3012) ~SHDN. TIM5_CH2 AF8 for PWM |
| USB jack D+/D- | USB3DR | AF22/AG22 | J17 USB-C, via devboard J1.75/J1.77 (devboard needs its D+/D- jumper fix) |
| FUSB_INT | PE9 | A23 | FUSB302 INT_N (level, open drain, no external pull-up) |
| USB_5V_ENABLE | PD13 | D25 | TPS22919 load switch ON |
| DIN MIDI IN | PF4 | AF10 | USART6_RX AF6 |
| DIN MIDI OUT | PF5 | AA11 | USART6_TX AF6 |
| GATE_IN1 | PF0 | AA15 | |
| GATE_IN2 | PC10 | AG10 | |
| HP_SENSE | PF2 | AC15 | |
| HP_SHUTDOWN | PF3 | AF11 | |
| CTLENC A / B / BUT | PC3 / PC9 / PH10 | | no timer encoder-mode pair |
| NAVENC A / B / BUT | PC6 / PA10 / PA5 | | no timer encoder-mode pair |
| BACK_BUT | PA9 | AF15 | |
| ESP RX (MCU TX) | PH7 | AE16 | ESP32-C6 RXD0. Only UART4_TX (AF4) |
| ESP TX (MCU RX) | PH5 | AG18 | ESP32-C6 TXD0. Only UART7_RX (AF8) |
| ESP_ENABLE | PI4 | P6 | EN/CHIP_PU |
| ESP_BOOT | PF14 | P3 | GPIO9 |
| ESP_GPIO8 / 10 / 11 | PH4 / PF7 / PF8 | | |

Unused on pro p1 (free on the sockets): PB0, PB6, PF1, PF9, PH8, PA12, PC4, PC5, PC7, PC8, PC11, PB15, PF10, PF11, PG3, PG4; all LTDC parallel pins except those reused above.

## Devboard-only

| Function | Pin | Notes |
|---|---|---|
| Console TX / RX | PB8 / PB10 | USART1 AF6, J4 header |
| DEBUG0 / DEBUG1 | PD9 / PD8 | J4 header |
| OCTOSPI NOR (W25Q128) | CLK PD0, CS PD3, IO0-3 PD4-PD7 | OCTOSPIM_P1 AF10 |
| PMIC I2C7 | SCL PD15, SDA PD14 | AF10, STPMIC25 at 0x33 (TF-A owns it) |
| PMIC INT / wakeup | PA0 | |
| devboard microSD detect 2 | PB3 | |
| DFU_BOOT button | PB1 | also PMIC PONKEY |
| USB-C (devboard) | USB2 HS + UCPD1 CC | |

## I/O supply domains (devboard)

| Rail | Pins | Devboard supply |
|---|---|---|
| VDDIO1 | PE[5:0] | PMIC LDO8 (VDDIO_SDCARD) |
| VDDIO2 | PE[15:6] | **+1V8** (shared with the 1.8V analog rails) |
| VDDIO3 | PD[11:0] | VDD_IO |
| VDDIO4 | PB[11:0] | VDD_IO |

All four have their supply-valid bits set in `system_init()`.

## I2C expanders (TCA9555)

| Ref | Bus | Addr | INT | Port 0 (P00..P07) | Port 1 (P10..P17) |
|---|---|---|---|---|---|
| U1210 | I2C2 | 0x21 | PB2 | NAV3, NAV2, NAV1, KNOBSET, BUT1, BUT2, BUT3, BUT4 | ENC4 BUT/A/B, ENC8 B/A/BUT, ENC7 A/B |
| U1211 | I2C2 | 0x22 | PB11 | ENC5 BUT/A/B, ENC6 BUT/A/B, ENC7 BUT, ENC3 A | ENC3 B/BUT, ENC2 A/B/BUT, ENC1 A/B/BUT |
| U1213 | I2C3 | 0x23 | PG7 | ENC11 A/B, ENC12 BUT, ENC16 BUT, ENC12 B/A, ENC16 B/A | BUT5, BUT6, BUT7, BUT8, PLAY, NAV6, NAV5, NAV4 |
| U1209 | I2C3 | 0x24 | PC12 | ENC13 BUT/A/B, ENC14 BUT/A/B, ENC15 BUT/A | ENC15 B, ENC11 BUT, ENC10 B/A/BUT, ENC9 A/B/BUT |
| U1212 | I2C4 | 0x20 | PH9 | SENSE: GATEIN1, GATEIN2, In5, In6, In3, In4, In1, In2 | SENSE: OUT8, OUT7, OUT6, OUT5, OUT4, OUT3, OUT2, OUT1 |

## LED drivers (LP5018, I2C6)

| Ref | Addr | OUT0-2 | OUT3-5 | OUT6-8 | OUT9-11 | OUT12-14 |
|---|---|---|---|---|---|---|
| U5 | 0x28 | BUT4 RGB | BUT3 RGB | BUT2 RGB | BUT1 RGB | BUT9 RGB |
| U8 | 0x29 | BUT10 RGB | BUT8 RGB | BUT7 RGB | BUT6 RGB | BUT5 RGB |

LED_BUT9 is the KNOBSET button (SW109) and LED_BUT10 is PLAY (SW110). The RGB button switches connect to +3V3 (active high).

## Codec

PCM3168 on the jack board: I2C mode (MODE=GND), ADR0=ADR1=GND → 0x44. Single DIN1/DOUT1 (TDM), BCLK/LRCLK shared AD/DA. Same as MP1.
Its digital supply (VDD1/VDD2) is 3.3V.

## Known p1 hardware issues

1. **I2C2 SDA/SCL swapped.** PB5 is I2C2_SCL and PB4 is I2C2_SDA, but p1 routes PB5 to the expanders' SDA
   and PB4 to their SCL. Expanders U1210/U1211 (ENC1-8, BUT1-4, NAV1-3, KNOBSET) are unreachable with the
   I2C2 peripheral. p1 fix: cut traces and swap PB4/PB5. The firmware assumes this bodge.
2. **SAI outputs at 1.8V.** PE11/13/14/15 are on VDDIO2, which the devboard ties to +1V8. The PCM3168's
   digital inputs need ~2.3V (0.7 x 3.3V) for a logic high. Needs 1.8V→3.3V level shifting on MCLK, SCLK,
   LRCLK, and DAC data. No SAI instance has a complete MCLK/SCK/FS set on the free 3.3V socket pins.
   p1 fix: a level-shifter board between J21 and J20. Only those four lines (all MCU→codec) need shifting;
   every other J20/J21 signal is on a 3.3V bank. J20/J21 have no 1.8V pin, so use a single-supply
   up-translator powered from +3.3V_B (e.g. SN74LV4T125).
3. **ESP32 UART split across two UARTs.** PH7 can only be UART4_TX and PH5 can only be UART7_RX. Works as
   two half-UARTs at the same baud rate.
4. **USB D+/D- (devboard).** The devboard routes ball AG22 (USB3DR_DM) to J1.75, which its schematic labels
   /USB3_DP; the pro board then sends J1.75 to the jack's D+. The pro board itself is straight-through, so
   the devboard jumper fix (swapping the pair before J1) is all that's needed.
5. **PB11 shared.** GPIO_INT_1 (U1211 INT) is also the devboard microSD SDDET1. The SDMMC1 bus also goes to
   the devboard's own microSD slot: leave that slot empty.
