/**
  ********************************************************************************
  * @brief   STM32 HAL Library for INA226 Current/Power Monitor
  * @date    Feb 2016
  * @version 1.0
  * @author  George Christidis
  ********************************************************************************
  * @details
			This library contains the necessary functions to initialize, read and
			write data to the TI INA226 Current/Power Monitor using the I2C
			protocol.
	******************************************************************************
	*/

#ifndef __INA226_H
#define __INA226_H

#include "stm32f1xx_hal.h"
#include "i2c.h"
#include "math.h"

#ifndef INA226_ADDRESS_DISCHARGE
#define INA226_ADDRESS_DISCHARGE	(0x45<<1)				// da << 1
#endif

#ifndef INA226_ADDRESS_CHARGE
#define INA226_ADDRESS_CHARGE	(0x44<<1)				// da << 1
#endif

#define INA226_Vdischar_UnderVoltage_AlertLimit	0x1900  // 8V

#define INA226_CALIB_VAL_DISCHARGE		1398
#define INA226_CURRENTLSB_DISCHARGE		(0.244F/1000) // A/bit  
#define INA226_POWERLSB_DISCHARGE		((INA226_CURRENTLSB_DISCHARGE*25.0)) // bit/W

#define INA226_CALIB_VAL_CHARGE		2097
#define INA226_CURRENTLSB_CHARGE		(0.061F/1000) // A/bit  
#define INA226_POWERLSB_CHARGE		((INA226_CURRENTLSB_CHARGE*25.0)) // bit/W

#define INA226_I2CTIMEOUT		100

#define INA226_CONFIG		0x00 // Configuration Register (R/W)
#define INA226_SHUNTV		0x01 // Shunt Voltage (R)
#define INA226_BUSV			0x02 // Bus Voltage (R)
#define INA226_POWER		0x03 // Power (R)
#define INA226_CURRENT		0x04 // Current (R)
#define INA226_CALIB		0x05 // Calibration (R/W)
#define INA226_MASK			0x06 // Mask/Enable (R/W)
#define INA226_ALERTL		0x07 // Alert Limit (R/W)
#define INA226_MANUF_ID		0xFE // Manufacturer ID (R)
#define INA226_DIE_ID		0xFF // Die ID (R)

#define INA226_MODE_POWER_DOWN			(0<<0) // Power-Down
#define INA226_MODE_TRIG_SHUNT_VOLTAGE	(1<<0) // Shunt Voltage, Triggered
#define INA226_MODE_TRIG_BUS_VOLTAGE	(2<<0) // Bus Voltage, Triggered
#define INA226_MODE_TRIG_SHUNT_AND_BUS	(3<<0) // Shunt and Bus, Triggered
#define INA226_MODE_POWER_DOWN2			(4<<0) // Power-Down
#define INA226_MODE_CONT_SHUNT_VOLTAGE	(5<<0) // Shunt Voltage, Continuous
#define INA226_MODE_CONT_BUS_VOLTAGE	(6<<0) // Bus Voltage, Continuous
#define INA226_MODE_CONT_SHUNT_AND_BUS	(7<<0) // Shunt and Bus, Continuous

// Shunt Voltage Conversion Time
#define INA226_VSH_140uS			(0<<3)
#define INA226_VSH_204uS			(1<<3)
#define INA226_VSH_332uS			(2<<3)
#define INA226_VSH_588uS			(3<<3)
#define INA226_VSH_1100uS			(4<<3)
#define INA226_VSH_2116uS			(5<<3)
#define INA226_VSH_4156uS			(6<<3)
#define INA226_VSH_8244uS			(7<<3)

// Bus Voltage Conversion Time (VBUS CT Bit Settings[6-8])
#define INA226_VBUS_140uS			(0<<6)
#define INA226_VBUS_204uS			(1<<6)
#define INA226_VBUS_332uS			(2<<6)
#define INA226_VBUS_588uS			(3<<6)
#define INA226_VBUS_1100uS			(4<<6)
#define INA226_VBUS_2116uS			(5<<6)
#define INA226_VBUS_4156uS			(6<<6)
#define INA226_VBUS_8244uS			(7<<6)

// Averaging Mode (AVG Bit Settings[9-11])
#define INA226_AVG_1				(0<<9)
#define INA226_AVG_4				(1<<9)
#define INA226_AVG_16				(2<<9)
#define INA226_AVG_64				(3<<9)
#define INA226_AVG_128				(4<<9)
#define INA226_AVG_256				(5<<9)
#define INA226_AVG_512				(6<<9)
#define INA226_AVG_1024				(7<<9) 

// Reset Bit (RST bit [15])
#define INA226_RESET_ACTIVE			(1<<15)
#define INA226_RESET_INACTIVE		(0<<15)

// Mask/Enable Register
#define INA226_MER_SOL				(1<<15) // Shunt Voltage Over-Voltage
#define INA226_MER_SUL				(1<<14) // Shunt Voltage Under-Voltage
#define INA226_MER_BOL				(1<<13) // Bus Voltagee Over-Voltage
#define INA226_MER_BUL				(1<<12) // Bus Voltage Under-Voltage
#define INA226_MER_POL				(1<<11) // Power Over-Limit
#define INA226_MER_CNVR				(1<<10) // Conversion Ready
#define INA226_MER_AFF				(1<<4)  // Alert Function Flag
#define INA226_MER_CVRF				(1<<3)  // Conversion Ready Flag
#define INA226_MER_OVF				(1<<2)  // Math Overflow Flag
#define INA226_MER_APOL				(1<<1)  // Alert Polarity Bit
#define INA226_MER_LEN				(1<<0)  // Alert Latch Enable

#define INA226_MANUF_ID_DEFAULT	0x5449
#define INA226_DIE_ID_DEFAULT		0x2260

float INA226_getBusV(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
float INA226_getCurrent_Discharge(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
float INA226_getCurrent_Charge(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
float INA226_getPower_Discharge(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
float INA226_getPower_Charge(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
float INA226_getShuntV(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);

uint8_t INA226_setConfig(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress, uint16_t ConfigWord);
uint16_t INA226_getConfig(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
int16_t INA226_getShuntVReg(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
uint16_t INA226_getBusVReg(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
uint16_t INA226_getPowerReg(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
uint8_t INA226_setCalibrationReg(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress, uint16_t ConfigWord);
uint16_t INA226_getCalibrationReg(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
int16_t INA226_getCurrentReg(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
uint16_t INA226_getManufID(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
uint16_t INA226_getDieID(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
uint8_t INA226_setMaskEnable(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress, uint16_t ConfigWord);
uint16_t INA226_getMaskEnable(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
uint8_t INA226_setAlertLimit(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress, uint16_t ConfigWord);
uint16_t INA226_getAlertLimit(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);

#endif
