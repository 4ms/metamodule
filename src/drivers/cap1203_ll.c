#include "cap1203_ll.h"

/// \defgroup capTouch Capacitive Touch Controller
/// These functions let you communicate with the CAP1203 capacitive touch controller
/// @{

/**
 *@brief Configuration for capacitive touch controller sets up the sensor 
 *       sets gain to 1 , enables interrupts and activates all three channels
 *@return none
 */ 
void CAP1203_Initialize(void)
{
    unsigned char ctrl_reg = CAP1203_ActiveMode();
    //Todo: check ctrl_reg for...something? 

    CAP1203_Write(SENSINPUTEN, CS1|CS2|CS3);
    CAP1203_Write(AVERAGE_SAMP_CONF, AVG|SAMP_TIME|CYCLE_TIME); //Setup averaging and sampling time 
    //CAP1203_Write(CONFIG1,~TOUCH);                    //The SMBus timeout and idle functionality are disabled
}

/**
 * @brief Sets the controller to active mode
 * @return status Contents of status register
 */
unsigned char CAP1203_ActiveMode(void)
{
    unsigned char status = CAP1203_Read(MAIN_CTRL_REG);
    status &= ~STBY;
    CAP1203_Write(MAIN_CTRL_REG,status);
    return CAP1203_Read(MAIN_CTRL_REG);
}

/**
 * @brief Set the controller to standby mode
 * @return status Contents of status register
 */
unsigned char CAP1203_StandbyMode(void)
{
    CAP1203_Write(STANDBY_SENS,0x07);       //Set sensitivity in standby mode    
    unsigned char status = CAP1203_Read(MAIN_CTRL_REG);
    status |= STBY;
    CAP1203_Write(MAIN_CTRL_REG,status);
    return CAP1203_Read(MAIN_CTRL_REG);
}

/**
 * @brief Set the controller to deep sleep mode
 * @return STATUS register
 */
unsigned char CAP1203_DeepSleep(void)
{
    unsigned char status = CAP1203_Read(MAIN_CTRL_REG);
    status |= SLEEP;                            //Set Sleep bit
    CAP1203_Write(MAIN_CTRL_REG,status);        //Update register
    return CAP1203_Read(MAIN_CTRL_REG);
}

/**
 * @brief Get the controller out of deep sleep mode
 * @return STATUS register
 */
unsigned char CAP1203_ResumeFromDeepSleep(void)
{
    unsigned char status = CAP1203_Read(MAIN_CTRL_REG);
    status &= ~SLEEP;
    CAP1203_Write(MAIN_CTRL_REG,status);
    return CAP1203_Read(MAIN_CTRL_REG);
}

/**
 * @brief Enables the multi-touch capability of the controller
 * @param number touch type
 * @param chan One of the three channels.
 * @return none
 */
void CAP1203_ConfigureMultiTouch(touch_type number,button_type chan )
{
    CAP1203_Write(MULTITOUCH,number);       //Set number of simultaneous touches
    CAP1203_Write(MULTIPATCONF,0x80);       //Enable multitouch
    CAP1203_Write(MULTIPATTERN,chan);
}

/**
 * @brief  Configures the button as a power button.
 * @param button One of the three buttons
 * @return none
 */
void CAP1203_SetPowerButton(button_type button)
{
    CAP1203_Write(PWR_BUTTON,button);
    CAP1203_Write(PWR_CONFIG,PWR_EN|TIME1120ms);        //Configure as power button in Active mode
}   

/**
 * @brief Read the Status register indicating which button was pressed
 * @return Button pressed
 */
unsigned char CAP1203_ReadPressedButton(void)
{
    unsigned char buttonPressed = 0;
    unsigned char status = CAP1203_GetStatusReg();      //Check if touch bit was registered
    if (status & TOUCH)
    {
        unsigned char button = CAP1203_Read(SENSOR_INPUTS);
        switch(button)
        {
            case CS1:
                    buttonPressed = 3;
                break;
            case CS2:
                    buttonPressed = 2;
                break;
            case CS3:
                    buttonPressed = 1;
                break;
            default:
                    buttonPressed = 0;
                break;
        }
    }   
    CAP1203_Write(MAIN_CTRL_REG,0x00);      //Clear interrupt
    return buttonPressed;    
}

/**
 * @brief Reads the status register.
 * @return status Contents of status register
 */
unsigned char CAP1203_GetStatusReg(void)
{
    unsigned char status = CAP1203_Read(GEN_STATUS);
    return status;
}

/**
 *@brief Enable interrupt, the ALERT pin goes high once an interrupt occurs
 *@param pin Enables interrupt on the specific pin
 *@return none
 */
void CAP1203_EnableInterrupt(button_type pin)
{
    CAP1203_Write(REPEAT_RATE,pin);     //Enable repeat rate for the input pins
    CAP1203_Write(INT_ENABLE,pin);      //2:0 c2:c1:c0  last three bits are the specific channels
}

/**
 *@brief Sets the sensitivity of each channel.
 *@param sensitivity Change button sensitivity settings.
 *@return none
 */
void CAP1203_SetSensitivity(uint8_t sensitivity)
{
    CAP1203_Write(SENSITIVITY, sensitivity);
}

/**
 *@brief Checks the sensor status
 *@return Status Current chip status
 */
unsigned char CAP1203_CheckSensorStatus(void)
{
    unsigned char sensor = 0;

    return sensor;
}

/**
 *@brief Clears any impending interrupts
 *@return intStatus Interrupt status
 */ 
unsigned char CAP1203_ClearInterrupt(void)
{
    unsigned char intStatus = 0x00;
    CAP1203_Read(GEN_STATUS);
    return intStatus;
}

/**
 *@brief Return chip and manufacturing ID
 *@return chipID 16 bit chip and manufacturer ID
 */
unsigned int CAP1203_ReadID(void)
{
    unsigned char id = CAP1203_Read(PRODUCT_ID);
    unsigned char manu = CAP1203_Read(MAN_ID);
    return ((manu << 8)|id);
}

/// @}

/**
 * @brief Write data value to register
 * @param reg Register to write to
 * @param data Value to write to register
 */
void CAP1203_Write(unsigned char reg, unsigned char data)
{
    i2c_mem_write(CAP1203ADDR, reg, &data, 1);
}

/**
 * @brief Read  value of register reg
 * @param reg   Register to read from
 * @return Register value
 */
unsigned char CAP1203_Read(unsigned char reg)
{
    unsigned char value;
    i2c_mem_read(CAP1203ADDR, reg, &value, 1);
    return value;
}
