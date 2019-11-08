/******************************************************************************
SparkFun_CAP1203_Types.h
SFE_Capacitive Touch Slider Library - CAP1203 Types and Enumerations
Andrea DeVore @ SparkFun Electronics
Original Creation Date: April 4, 2019
https://github.com/sparkfun/Qwiic_Capacitive_Touch_Slider_CAP1203
This file defines all types and enumerations used by the CAP1203 class.
Development environment specifics:
    IDE: Arduino 1.6.0
    Hardware Platform: Arduino Uno
    CAP1203 Breakout Version: 1.0
This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!
Distributed as-is; no warranty is given.
******************************************************************************/

#pragma once

#include <stm32f7xx.h>

// Declare I2C Address
#define CAP1203_I2C_ADDR (0x28<<1)

// Register values

enum CAP1203_Register
{
    MAIN_CONTROL = 0x00,
    GENERAL_STATUS = 0x02,
    SENSOR_INPUT_STATUS = 0x03,
    NOISE_FLAG_STATUS = 0x0A,
    SENSOR_INPUT_1_DELTA_COUNT = 0x10,
    SENSOR_INPUT_2_DELTA_COUNT = 0X11,
    SENSOR_INPUT_3_DELTA_COUNT = 0X12,
    SENSITIVITY_CONTROL = 0x1F,
    CONFIG = 0x20,
    SENSOR_INPUT_ENABLE = 0x21,
    SENSOR_INPUT_CONFIG = 0x22,
    SENSOR_INPUT_CONFIG_2 = 0x23,
    AVERAGING_AND_SAMPLE_CONFIG = 0x24,
    CALIBRATION_ACTIVATE_AND_STATUS = 0x26,
    INTERRUPT_ENABLE = 0x27,
    REPEAT_RATE_ENABLE = 0x28,
    MULTIPLE_TOUCH_CONFIG = 0x2A,
    MULTIPLE_TOUCH_PATTERN_CONFIG = 0x2B,
    MULTIPLE_TOUCH_PATTERN = 0x2D,
    BASE_COUNT_OUT = 0x2E,
    RECALIBRATION_CONFIG = 0x2F,
    SENSOR_1_INPUT_THRESH = 0x30,
    SENSOR_2_INPUT_THRESH = 0x31,
    SENSOR_3_INPUT_THRESH = 0x32,
    SENSOR_INPUT_NOISE_THRESH = 0x38,
    STANDBY_CHANNEL = 0x40,
    STANDBY_CONFIG = 0x41,
    STANDBY_SENSITIVITY = 0x42,
    STANDBY_THRESH = 0x43,
    CONFIG_2 = 0x44,
    SENSOR_INPUT_1_BASE_COUNT = 0x50,
    SENSOR_INPUT_2_BASE_COUNT = 0x51,
    SENSOR_INPUT_3_BASE_COUNT = 0x52,
    POWER_BUTTON = 0x60,
    POWER_BUTTON_CONFIG = 0x61,
    SENSOR_INPUT_1_CALIBRATION = 0xB1,
    SENSOR_INPUT_2_CALIBRATION = 0xB2,
    SENSOR_INPUT_3_CALIBRATION = 0xB3,
    SENSOR_INPUT_CALIBRATION_LSB_1 = 0xB9,
    PROD_ID = 0xFD,
    MANUFACTURE_ID = 0xFE,
    REVISION = 0xFF,
};

// Product ID - always the same (pg. 22)
#define PROD_ID_VALUE 0x6D

// Capacitive sensor input (pg. 23)
#define OFF 0x00 // No touch detecetd
#define ON 0x01  // Check capacitive sensor input (pg. 23)

// Pads to be power buttion (pg. 43)
#define PWR_CS1 0x00 // Pad 1 (Left)
#define PWR_CS2 0x01 // Pad 2 (Middle)
#define PWR_CS3 0x02 // Pad 3 (Right)

#define PAD_LEFT PWR_CS1
#define PAD_MIDDLE PWR_CS2
#define PAD_RIGHT PWR_CS3

// Power button hold time to generate interrupt (pg. 44)
#define PWR_TIME_280_MS 0x00  // 280 ms
#define PWR_TIME_560_MS 0x01  // 560 ms
#define PWR_TIME_1120_MS 0x02 // 1.12 sec
#define PWR_TIME_2240_MS 0x03 // 2.24 sec

// Sensitivity for touch detection (pg. 25)
#define SENSITIVITY_128X 0x00 // Most sensitive
#define SENSITIVITY_64X 0x01
#define SENSITIVITY_32X 0x02
#define SENSITIVITY_16X 0x03
#define SENSITIVITY_8X 0x04
#define SENSITIVITY_4X 0x05
#define SENSITIVITY_2X 0x06
#define SENSITIVITY_1X 0x07 // Least sensitive

// Sensitivity Control Reg (pg. 25)
typedef union {
    struct
    {
        uint8_t BASE_SHIFT : 4;
        uint8_t DELTA_SENSE : 3;
        uint8_t EMPTY_1 : 1;
    } SENSITIVITY_CONTROL_FIELDS;
    uint8_t SENSITIVITY_CONTROL_COMBINED;
} SENSITIVITY_CONTROL_REG;

// General Status Reg (pg. 23)
typedef union {
    struct
    {
        uint8_t TOUCH : 1;
        uint8_t MTP : 1;
        uint8_t MULT : 1;
        uint8_t EMPTY_1 : 1;
        uint8_t PWR_STATUS : 1;
        uint8_t ACAL_FAIL : 1;
        uint8_t BC_OUT : 1;
        uint8_t EMPTY_2 : 1;
    } GENERAL_STATUS_FIELDS;
    uint8_t GENERAL_STATUS_COMBINED;
} GENERAL_STATUS_REG;

// Sensor Input Status Reg (pg. 23)
typedef union {
    struct
    {
        uint8_t CS1 : 1;
        uint8_t CS2 : 1;
        uint8_t CS3 : 1;
        uint8_t EMPTY_1 : 5;
    } SENSOR_INPUT_STATUS_FIELDS;
    uint8_t SENSOR_INPUT_STATUS_COMBINED;
} SENSOR_INPUT_STATUS_REG;

// Main Control Register (pg. 22)
typedef union {
    struct
    {
        uint8_t INT : 1;
        uint8_t EMPTY_1 : 3;
        uint8_t DSLEEP : 1;
        uint8_t STBY : 1;
        uint8_t EMPTY_2 : 2;
    } MAIN_CONTROL_FIELDS;
    uint8_t MAIN_CONTROL_COMBINED;
} MAIN_CONTROL_REG;

// Power Button Register (pg. 43)
typedef union {
    struct
    {
        uint8_t PWR_BTN : 3;
        uint8_t EMPTY_1 : 5;
    } POWER_BUTTON_FIELDS;
    uint8_t POWER_BUTTON_COMBINED;
} POWER_BUTTON_REG;

// Power Button Configuration Register (pg. 43)
typedef union {
    struct
    {
        uint8_t PWR_TIME : 2;
        uint8_t PWR_EN : 1;
        uint8_t EMPTY_1 : 1;
        uint8_t STBY_PWR_TIME : 2;
        uint8_t STBY_PWR_EN : 1;
        uint8_t EMPTY_2 : 1;
    } POWER_BUTTON_CONFIG_FIELDS;
    uint8_t POWER_BUTTON_CONFIG_COMBINED;
} POWER_BUTTON_CONFIG_REG;

// Interrupt Enable Register (pg. 33)
typedef union {
    struct
    {
        uint8_t CS1_INT_EN : 1;
        uint8_t CS2_INT_EN : 1;
        uint8_t CS3_INT_EN : 1;
        uint8_t EMPTY_1 : 5;
    } INTERRUPT_ENABLE_FIELDS;
    uint8_t INTERRUPT_ENABLE_COMBINED;
} INTERRUPT_ENABLE_REG;

////////////////////////////////
// CAP1203 Class Declearation //
////////////////////////////////
class CAP1203
{
public:
    // Constructor
    CAP1203(uint8_t addr = CAP1203_I2C_ADDR);

    bool begin(/*TwoWire &wirePort = Wire, */uint8_t deviceAddress = CAP1203_I2C_ADDR);
    bool isConnected();
    void setSensitivity(uint8_t sensitivity);
    uint8_t getSensitivity();

    // Check if a capacitive touch panel has been touched
    bool isLeftTouched();
    bool isMiddleTouched();
    bool isRightTouched();
    bool isTouched();

    // Check if a swipe has occured
    bool isRightSwipePulled();
    bool isLeftSwipePulled();

    // Clears INT bit
    void clearInterrupt();

    // Configures if interrupt triggers on touch
    void setInterruptDisabled();
    void setInterruptEnabled();
    bool isInterruptEnabled();

    void checkMainControl();
    void checkStatus();

    // Power button configuration and check settings
    bool setPowerButtonPad(uint8_t pad);
    bool setPowerButtonTime(uint8_t time);
    uint8_t getPowerButtonPad();
    uint16_t getPowerButtonTime();
    void setPowerButtonEnabled();
    void setPowerButtonDisabled();
    bool isPowerButtonEnabled();
    bool isPowerButtonTouched();

private:
    // TwoWire *_i2cPort = NULL; //The generic connection to user's chosen I2C hardware
    uint8_t _deviceAddress;   //Keeps track of I2C address. setI2CAddress changes this.

    // Read and write to registers
    uint8_t readRegister(CAP1203_Register reg);
    void readRegisters(CAP1203_Register reg, uint8_t *buffer, uint8_t len);
    void writeRegister(CAP1203_Register reg, uint8_t data);
    void writeRegisters(CAP1203_Register reg, uint8_t *buffer, uint8_t len);
};

