#ifndef __COMMANDPROCES_H
#define __COMMANDPROCES_H

#include "stm32f1xx_hal.h"
#include "string.h"
#include "usart.h"
#include "stdio.h"
#include "ina226.h"
#include "adc.h"

//@;C;Y;!   -------------------- @;A;OKX;!
//Y belong to
// Control Command 			
//#define LightTurnOn		1
//#define LightTurnOff	2
//#define WaveToSolar  	3
//#define SolarToWave   4
//#define SavePowerMode	5
//#define NormalMode    6

//@;I;Y;!   -------------------- @;AI;...;....;!
//Y belong to
//// Getting Infor Command	I
//#define	Discharger				1
//#define Charger						2
//#define Status						3

void PreProces(void );
uint8_t LightTurnOn(void);
uint8_t LightTurnOff(void);
uint8_t WaveToSolar(void);
uint8_t SolarToWave(void);
uint8_t SavePowerMode(void);
uint8_t NormalMode(void);
uint8_t Discharger(void);
uint8_t Charger(void);
uint8_t Status(void);
void MainProce(void);
#endif
