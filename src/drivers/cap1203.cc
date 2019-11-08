/******************************************************************************
SparkFun_CAP1203.cpp
SFE_Capacitive Touch Slider Library - Source File
Andrea DeVore @ SparkFun Electronics
Original Creation Date: April 4, 2019
https://github.com/sparkfun/Qwiic_Capacitive_Touch_Slider_CAP1203

This file implements all functions of the CAP1203 class.

Development environment specifics:
	IDE: Arduino 1.6.0
	Hardware Platform: Arduino Uno
	CAP1203 Breakout Version: 1.0

This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.
******************************************************************************/

extern "C" {
#include "i2c.h"
}
#include "cap1203.hh"

uint32_t millis(void) {
    return HAL_GetTick();
}

/* CONSTRUCTOR
    This function, called when you initialize the class will write 
    the varibale address into a private variable for future use. 
    The variable address should be 0x28. 
*/
CAP1203::CAP1203(uint8_t addr)
{
    _deviceAddress = addr;
}

/* BEGIN INITIALIZATION
    This function initalizes the CAP1203 sensor.
*/
bool CAP1203::begin(uint8_t deviceAddress)
{
    // Set device address and wire port to private variable
    _deviceAddress = deviceAddress;

    MAIN_CONTROL_REG reg;
    reg.MAIN_CONTROL_COMBINED = readRegister(MAIN_CONTROL);
    reg.MAIN_CONTROL_FIELDS.STBY = 0;
    writeRegister(MAIN_CONTROL, reg.MAIN_CONTROL_COMBINED);

    reg.MAIN_CONTROL_COMBINED = readRegister(MAIN_CONTROL);

    SENSOR_INPUT_STATUS_REG sreg = {0};
    sreg.SENSOR_INPUT_STATUS_FIELDS.CS1 = 1;
    sreg.SENSOR_INPUT_STATUS_FIELDS.CS3 = 1;

    writeRegister(SENSOR_INPUT_ENABLE, sreg.SENSOR_INPUT_STATUS_COMBINED);

    writeRegister(AVERAGING_AND_SAMPLE_CONFIG, 0x30 | 0x08 | 0x01); //AVG=8 | SAMP_TIME=1.28ms | CYCLE_TIME=70ms

    // setSensitivity(SENSITIVITY_8X);
    // setInterruptDisabled();
    setInterruptEnabled();          // Enable INT and LED as default
    clearInterrupt();               // Clear interrupt on startup
    return true;
}

/* IS CONNECTED 
    Returns true if the I2C Device reads correct product ID
    Otherwise returns false.
*/
bool CAP1203::isConnected()
{
    uint8_t prodIDValue = readRegister(PROD_ID);
    return (prodIDValue == PROD_ID_VALUE);
}

/* CHECK MAIN CONTROL REGISTER
    Control the primary power state of the device. See data sheet
    on Main Control Register (pg. 22).
*/
void CAP1203::checkMainControl()
{
    MAIN_CONTROL_REG reg;
    reg.MAIN_CONTROL_COMBINED = readRegister(MAIN_CONTROL);
}

/* CHECK STATUS
    Checks inputs in the general status register to ensure program
    is set up correctly. See data sheet on Status Registers (pg. 23).
*/
void CAP1203::checkStatus()
{
    GENERAL_STATUS_REG reg;
    reg.GENERAL_STATUS_COMBINED = readRegister(GENERAL_STATUS);
}

/* CLEAR INTTERUPT 
    Clears the interrupt (INT) bit by writing a logic 0 to it.
    This bit must be cleared in order to detec a new capacitive
    touch input. See datasheet on Main Control Register (pg. 22).
*/
void CAP1203::clearInterrupt()
{
    MAIN_CONTROL_REG reg;
    reg.MAIN_CONTROL_COMBINED = readRegister(MAIN_CONTROL);
    reg.MAIN_CONTROL_FIELDS.INT = 0x00;
    writeRegister(MAIN_CONTROL, reg.MAIN_CONTROL_COMBINED);
}

/* DISABLE INTERRUPTS 
    This disables all the interrupts, so the alert LED will not turn on
    when a sensor is touched. Set on default in begin function See data 
    sheet on Interrupt Enable Register (pg. 33).
*/
void CAP1203::setInterruptDisabled()
{
    INTERRUPT_ENABLE_REG reg;
    reg.INTERRUPT_ENABLE_COMBINED = readRegister(INTERRUPT_ENABLE);
    reg.INTERRUPT_ENABLE_FIELDS.CS1_INT_EN = 0x00;
    reg.INTERRUPT_ENABLE_FIELDS.CS2_INT_EN = 0x00;
    reg.INTERRUPT_ENABLE_FIELDS.CS3_INT_EN = 0x00;
    writeRegister(INTERRUPT_ENABLE, reg.INTERRUPT_ENABLE_COMBINED);
}

/* ENABLE INTERRUPTS
    This turns on all the interrupts, so the alert LED turns on when any 
    sensor is touched. See data sheet on Interrupt Enable Register (pg. 33).
*/
void CAP1203::setInterruptEnabled()
{
    INTERRUPT_ENABLE_REG reg;
    reg.INTERRUPT_ENABLE_COMBINED = readRegister(INTERRUPT_ENABLE);
    reg.INTERRUPT_ENABLE_FIELDS.CS1_INT_EN = 0x01;
    reg.INTERRUPT_ENABLE_FIELDS.CS2_INT_EN = 0x01;
    reg.INTERRUPT_ENABLE_FIELDS.CS3_INT_EN = 0x01;
    writeRegister(INTERRUPT_ENABLE, reg.INTERRUPT_ENABLE_COMBINED);
}

/* IS INTERRUPT ENABLED
    Returns state of intterupt pin. Returns true if all interrupts enabled 
    (0x07), otherwise returns false. When the interrupts are enabled, the 
    LED on the CAP1203 Touch Slider Board turns on when it detects a touch 
    (pg. 33).
*/
bool CAP1203::isInterruptEnabled()
{
    INTERRUPT_ENABLE_REG reg;
    reg.INTERRUPT_ENABLE_COMBINED = readRegister(INTERRUPT_ENABLE);
    if (reg.INTERRUPT_ENABLE_FIELDS.CS1_INT_EN == 0x01 && reg.INTERRUPT_ENABLE_FIELDS.CS2_INT_EN == 0x01 && reg.INTERRUPT_ENABLE_FIELDS.CS3_INT_EN == 0x01)
    {
        return true;
    }
    return false;
}

/* SET SENSITIVITY
    Sensitivity calibrated for SparkFun Capacitive Touch Slider. You may 
    want to change sensitivity settings if creating your own capacitive 
    touch pads. See datasheet on Sensitivity Control Register (pg. 25).
*/
void CAP1203::setSensitivity(uint8_t sensitivity)
{
    SENSITIVITY_CONTROL_REG reg;
    reg.SENSITIVITY_CONTROL_COMBINED = readRegister(SENSITIVITY_CONTROL);
    if (sensitivity == SENSITIVITY_128X)
    {
        reg.SENSITIVITY_CONTROL_FIELDS.DELTA_SENSE = SENSITIVITY_128X;
    }
    else if (sensitivity == SENSITIVITY_64X)
    {
        reg.SENSITIVITY_CONTROL_FIELDS.DELTA_SENSE = SENSITIVITY_64X;
    }
    else if (sensitivity == SENSITIVITY_32X)
    {
        reg.SENSITIVITY_CONTROL_FIELDS.DELTA_SENSE = SENSITIVITY_32X;
    }
    else if (sensitivity == SENSITIVITY_16X)
    {
        reg.SENSITIVITY_CONTROL_FIELDS.DELTA_SENSE = SENSITIVITY_16X;
    }
    else if (sensitivity == SENSITIVITY_8X)
    {
        reg.SENSITIVITY_CONTROL_FIELDS.DELTA_SENSE = SENSITIVITY_8X;
    }
    else if (sensitivity == SENSITIVITY_4X)
    {
        reg.SENSITIVITY_CONTROL_FIELDS.DELTA_SENSE = SENSITIVITY_4X;
    }
    else if (sensitivity == SENSITIVITY_1X)
    {
        reg.SENSITIVITY_CONTROL_FIELDS.DELTA_SENSE = SENSITIVITY_1X;
    }
    else
    {
        // Default case: calibrated for CAP1203 touch sensor
        reg.SENSITIVITY_CONTROL_FIELDS.DELTA_SENSE = SENSITIVITY_2X;
    }
    writeRegister(SENSITIVITY_CONTROL, reg.SENSITIVITY_CONTROL_COMBINED);
}

/* GET SENSITIVITY
    Returns the sensitivity multiplier for current sensitivity settings (pg. 25).
*/
uint8_t CAP1203::getSensitivity()
{
    SENSITIVITY_CONTROL_REG reg;
    reg.SENSITIVITY_CONTROL_COMBINED = readRegister(SENSITIVITY_CONTROL);
    uint16_t sensitivity = reg.SENSITIVITY_CONTROL_FIELDS.DELTA_SENSE;
    if (sensitivity == SENSITIVITY_128X)
    {
        return 128;
    }
    else if (sensitivity == SENSITIVITY_64X)
    {
        return 64;
    }
    else if (sensitivity == SENSITIVITY_32X)
    {
        return 32;
    }
    else if (sensitivity == SENSITIVITY_16X)
    {
        return 16;
    }
    else if (sensitivity == SENSITIVITY_8X)
    {
        return 8;
    }
    else if (sensitivity == SENSITIVITY_4X)
    {
        return 4;
    }
    else if (sensitivity == SENSITIVITY_2X)
    {
        return 2;
    }
    else if (sensitivity == SENSITIVITY_1X)
    {
        return 1;
    }
    else
    {
        // Error - no possible register value (pg. 25)
        return 0;
    }
}

/* LEFT SENSOR TOUCHED
    Checks if touch input detected on left sensor (pad 1). Need to clear
    interrupt pin after touch occurs. See datasheet on Sensor Interrupt 
    Status Reg (pg.23).
*/
bool CAP1203::isLeftTouched()
{
    SENSOR_INPUT_STATUS_REG reg;
    reg.SENSOR_INPUT_STATUS_COMBINED = readRegister(SENSOR_INPUT_STATUS);

    // Touch detected
    if (reg.SENSOR_INPUT_STATUS_FIELDS.CS1 == ON)
    {
        clearInterrupt();
        return true;
    }
    return false;
}

/* MIDDLE SENSOR TOUCHED
    Checks if touch input detected on left sensor (pad 2). Need to clear
    interrupt pin after touch occurs. See datasheet on Sensor Interrupt 
    Status Reg (pg.23).
*/
bool CAP1203::isMiddleTouched()
{
    SENSOR_INPUT_STATUS_REG reg;
    reg.SENSOR_INPUT_STATUS_COMBINED = readRegister(SENSOR_INPUT_STATUS);

    // Touch detected
    if (reg.SENSOR_INPUT_STATUS_FIELDS.CS2 == ON)
    {
        clearInterrupt();
        return true;
    }
    return false;
}

/* RIGHT SENSOR TOUCHED
    Checks if touch input detected on left sensor (pad 3). Need to clear
    interrupt pin after touch occurs. See datasheet on Sensor Interrupt 
    Status Reg (pg.23).
*/
bool CAP1203::isRightTouched()
{
    SENSOR_INPUT_STATUS_REG reg;
    reg.SENSOR_INPUT_STATUS_COMBINED = readRegister(SENSOR_INPUT_STATUS);

    // Touch detected
    if (reg.SENSOR_INPUT_STATUS_FIELDS.CS3 == ON)
    {
        clearInterrupt();
        return true;
    }
    return false;
}

/* DETECT TOUCH
    Checks if touch input detected on any sensor. Need to clear
    interrupt pin after touch occurs. See datasheet on Sensor Interrupt 
    Status (pg.23).
*/
bool CAP1203::isTouched()
{
    GENERAL_STATUS_REG reg;
    reg.GENERAL_STATUS_COMBINED = readRegister(GENERAL_STATUS);

    // Touch detected
    if (reg.GENERAL_STATUS_FIELDS.TOUCH == ON)
    {
        clearInterrupt();
        return true;
    }
    return false;
}

/* IS RIGHT SWIPE
    Checks if a right swipe occured on the board. This method
    takes up all functionality due to implementation of 
    while loop with millis().
*/
bool CAP1203::isRightSwipePulled()
{
    bool swipe = false; // Tracks if conditions are being met
    unsigned long startTime = millis();

    // LEFT TOUCH CONDITION
    while ((millis() - startTime) < 100)
    {
        if (isLeftTouched() == true)
        {
            swipe = true;
            while (isLeftTouched() == true)
                ;  // Wait for user to remove their finger
            break; // Break out of loop
        }
    }

    // Return if left not touched
    if (swipe == false)
        return false;

    startTime = millis(); // Reset start time
    swipe = false;        // Reset check statement

    // MIDDLE TOUCH CONDITION
    while ((millis() - startTime) < 100)
    {
        if (isMiddleTouched() == true)
        {
            swipe = true;
            while (isMiddleTouched() == true)
                ;  // Wait for user to remove their finger
            break; // Break out of loop
        }
    }

    // Return if middle not touched
    if (swipe == false)
    {
        return false;
    }

    startTime = millis(); // Reset start time
    swipe = false;        // Reset check statement

    // RIGHT TOUCH CONDITION
    while ((millis() - startTime) < 100)
    {
        if (isRightTouched() == true)
        {
            return true;
        }
    }

    return false;
}

/* IS LEFT SWIPE PULLED
    Checks if a left swipe occured on the board. This method
    takes up all functionality due to implementation of 
    while loop with millis().
*/
bool CAP1203::isLeftSwipePulled()
{
    bool swipe = false; // Tracks if conditions are being met
    unsigned long startTime = millis();

    // RIGHT TOUCH CONDITION
    while ((millis() - startTime) < 100)
    {
        if (isRightTouched() == true)
        {
            swipe = true;
            while (isRightTouched() == true)
                ;  // Wait for user to remove their finger
            break; // Break out of loop
        }
    }

    // Return if right not touched
    if (swipe == false)
        return false;

    startTime = millis(); // Reset start time
    swipe = false;        // Reset check statement

    // MIDDLE TOUCH CONDITION
    while ((millis() - startTime) < 100)
    {
        if (isMiddleTouched() == true)
        {
            swipe = true;
            while (isMiddleTouched() == true)
                ;  // Wait for user to remove their finger
            break; // Break out of loop
        }
    }

    // Return if middle not touched
    if (swipe == false)
        return false;

    startTime = millis(); // Reset start time
    swipe = false;        // Reset check statement

    // LEFT TOUCH CONDITION
    while ((millis() - startTime) < 100)
    {
        if (isLeftTouched() == true)
        {
            return true;
        }
    }

    return false;
}

/* SET POWER BUTTON PAD
    Sets a specific pad to act as a power button. Function takes in which 
    pad to set as power button. See datasheet on Power Button (pg. 16).
*/
bool CAP1203::setPowerButtonPad(uint8_t pad)
{
    POWER_BUTTON_REG reg;
    reg.POWER_BUTTON_COMBINED = readRegister(POWER_BUTTON);

    // Set pad to act as power button (pg. 43)
    if (pad == PAD_LEFT)
    {
        reg.POWER_BUTTON_FIELDS.PWR_BTN = PWR_CS1;
    }
    else if (pad == PAD_MIDDLE)
    {
        reg.POWER_BUTTON_FIELDS.PWR_BTN = PWR_CS2;
    }
    else if (pad == PAD_RIGHT)
    {
        reg.POWER_BUTTON_FIELDS.PWR_BTN = PWR_CS3;
    }
    else
    {
        // User input invalid pad number
        return false;
    }
    writeRegister(POWER_BUTTON, reg.POWER_BUTTON_COMBINED);
    return true;
}

/* GET POWER BUTTON PAD
    Returns which capacitive touch pad is currently set to act
    as a power button.
    
    Add 1 to return value so value matches pad number.
    See data sheet on Power Button (pg. 44)
        REG VALUE   PAD
        0x00        1
        0x01        2
        0x02        3
*/
uint8_t CAP1203::getPowerButtonPad()
{
    POWER_BUTTON_REG reg;
    reg.POWER_BUTTON_COMBINED = readRegister(POWER_BUTTON);

    return (reg.POWER_BUTTON_FIELDS.PWR_BTN + 1);
}

/* SET POWER BUTTON TIME
    Configure the length of time that the designated power button
    must indicate a touch before an interrupt is generated and the
    power status indicator is set. See data sheet on Power Button
    Configuration Register (pg. 43). 
    
    Possible inputs (represent time in ms): 280, 560, 1120, 2240
*/
bool CAP1203::setPowerButtonTime(uint8_t inputTime)
{
    POWER_BUTTON_CONFIG_REG reg;
    reg.POWER_BUTTON_CONFIG_COMBINED = readRegister(POWER_BUTTON_CONFIG);
    if (inputTime == PWR_TIME_280_MS)
    {
        reg.POWER_BUTTON_CONFIG_FIELDS.PWR_TIME = PWR_TIME_280_MS;
    }
    else if (inputTime == PWR_TIME_560_MS)
    {
        reg.POWER_BUTTON_CONFIG_FIELDS.PWR_TIME = PWR_TIME_560_MS;
    }
    else if (inputTime == PWR_TIME_1120_MS)
    {
        reg.POWER_BUTTON_CONFIG_FIELDS.PWR_TIME = PWR_TIME_1120_MS;
    }
    else if (inputTime == PWR_TIME_2240_MS)
    {
        reg.POWER_BUTTON_CONFIG_FIELDS.PWR_TIME = PWR_TIME_2240_MS;
    }
    else
    {
        // User input invalid time
        return false;
    }
    writeRegister(POWER_BUTTON_CONFIG, reg.POWER_BUTTON_CONFIG_COMBINED);
    return true;
}

/* GET POWER BUTTON TIME
    Returns the length of the time designated time power button must 
    indicate a touch before an interrupt is generated. 
    
    See data sheet on Power Button Time (pg. 44)
        REG VALUE   TIME
        0x00        280 MS
        0x01        560 MS
        0x02        1120 MS
        0x03        2240 MS
*/
uint16_t CAP1203::getPowerButtonTime()
{
    POWER_BUTTON_CONFIG_REG reg;
    reg.POWER_BUTTON_CONFIG_COMBINED = readRegister(POWER_BUTTON_CONFIG);
    if (reg.POWER_BUTTON_CONFIG_FIELDS.PWR_TIME == PWR_TIME_280_MS)
    {
        return 280;
    }
    else if (reg.POWER_BUTTON_CONFIG_FIELDS.PWR_TIME == PWR_TIME_560_MS)
    {
        return 560;
    }
    else if (reg.POWER_BUTTON_CONFIG_FIELDS.PWR_TIME == PWR_TIME_1120_MS)
    {
        return 1120;
    }
    else if (reg.POWER_BUTTON_CONFIG_FIELDS.PWR_TIME == PWR_TIME_2240_MS)
    {
        return 2240;
    }
    // Invalid data reading - check hook up
    return 0;
}

/* SET POWER BUTTON ENABLED
    Enables power button in active state. See data sheet on Power Button
    Configuration Register (pg. 43-44)
*/
void CAP1203::setPowerButtonEnabled()
{
    POWER_BUTTON_CONFIG_REG reg;
    reg.POWER_BUTTON_CONFIG_COMBINED = readRegister(POWER_BUTTON_CONFIG);
    reg.POWER_BUTTON_CONFIG_FIELDS.PWR_EN = 0x01;
    writeRegister(POWER_BUTTON_CONFIG, reg.POWER_BUTTON_CONFIG_COMBINED);
}

/* SET POWER BUTTON DISABLED
    Disables power button in active state. See data sheet on Power Button
    Configuration Register (pg. 43-44)
*/
void CAP1203::setPowerButtonDisabled()
{
    POWER_BUTTON_CONFIG_REG reg;
    reg.POWER_BUTTON_CONFIG_COMBINED = readRegister(POWER_BUTTON_CONFIG);
    reg.POWER_BUTTON_CONFIG_FIELDS.PWR_EN = 0x00;
    writeRegister(POWER_BUTTON_CONFIG, reg.POWER_BUTTON_CONFIG_COMBINED);
}

/* IS POWER BUTTON ENABLED
    Returns state of power button. Returns true if enabled (reg. value is
    0x01), otherwise returns false. Power button must be ENABLED to use.
    See data sheet on Power Button Configuration Register (pg. 43-44).
*/
bool CAP1203::isPowerButtonEnabled()
{
    POWER_BUTTON_CONFIG_REG reg;
    reg.POWER_BUTTON_CONFIG_COMBINED = readRegister(POWER_BUTTON_CONFIG);
    if (reg.POWER_BUTTON_CONFIG_FIELDS.PWR_EN == 0x01)
    {
        // Power button enabled
        return true;
    }
    // Power button disabled
    return false;
}

/* IS POWER BUTTON TOUCHED
    Once the power button has been held for designated time, an interrupt 
    is generated and PWR bit is set in the General Status Register. See 
    data sheet on Power Button (pg. 16), Power Button Register (pg. 43),
    and Power Button Configuration Register (pg. 43).
*/
bool CAP1203::isPowerButtonTouched()
{
    GENERAL_STATUS_REG reg;
    reg.GENERAL_STATUS_COMBINED = readRegister(GENERAL_STATUS);

    if (reg.GENERAL_STATUS_FIELDS.PWR_STATUS == ON)
    {
        clearInterrupt();
        return true;
    }
    return false;
}

/* READ A SINGLE REGISTER
    Read a single byte of data from the CAP1203 register "reg"
*/
uint8_t CAP1203::readRegister(CAP1203_Register reg)
{
    uint8_t data;

    if (i2c_mem_read(_deviceAddress, reg, &data, 1)==0)
        return data;
    else
        return 0;
}

/* READ MULTIPLE REGISTERS
    Read "en" bytes from the CAP1203m, starting at register "reg." Bytes are 
    stored in "buffer" on exit.
*/
void CAP1203::readRegisters(CAP1203_Register reg, uint8_t *buffer, uint8_t len)
{
    i2c_mem_read(_deviceAddress, reg, buffer, len);

}

/* WRITE TO A SINGLE REGISTER
    Wire a single btyte of data to a register in CAP1203
*/
void CAP1203::writeRegister(CAP1203_Register reg, uint8_t data)
{
    writeRegisters(reg, &data, 1);
}

/* WRITE TO MULTIPLE REGISTERS
    Write an array of "len" bytes ("buffer"), starting at register "reg,"
    and auto-incementing to the next
*/
void CAP1203::writeRegisters(CAP1203_Register reg, uint8_t *buffer, uint8_t len)
{
    i2c_mem_write(_deviceAddress, reg, buffer, len);
}
