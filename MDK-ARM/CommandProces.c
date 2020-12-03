#include "CommandProces.h"


char buffer[100];
char Rx_Buffer[100];
float Vdischarge;
float Idischarge;
float Pdischarge;
float Icharge;
float Pcharge;

uint8_t LightStatus;  // 1 : cho phep bat den chop 0: ko cho phep
uint8_t CurrentSource; // 1: Solar 0: Wave

void PreProces(void )
{
	uint8_t len= strlen(Rx_Buffer);
	uint8_t StartPos=0;
	uint8_t EndPos=0;
	uint8_t dem=0;
	
	for(uint8_t i=0; i<len;i++)
	{
		if (Rx_Buffer[i] =='@')
		{
			 StartPos=i;
			//printf("%d\n\r",StartPos);
		}
		
	}
	for (uint8_t i=StartPos; i<len;i++)
	{
		if (Rx_Buffer[i] =='!')
			{
				 EndPos=i;
			//printf("%d\n\r",EndPos);
				 break;
			}
	}
	for (uint8_t i=0;i<100;i++) buffer[i]=0;
	for (uint8_t i=StartPos; i<=EndPos;i++)
	{
		buffer[dem++]=Rx_Buffer[i];
	}
	//printf("%s\n\r",buffer);
}
void MainProce(void)
{
	char c =buffer[4];
	if (buffer[2] == 'C')
	{
		
		switch(c)
		{
			case '1': 
								LightTurnOn();
								break;
			case '2': 
								LightTurnOff();
								break;
			case '3': 
								WaveToSolar();
								break;
			case '4': 
								SolarToWave();
								break;
			case '5': 
								SavePowerMode();
								break;
			case '6': 
								NormalMode();
								break;
			default:
							break;
		}
	}
	else if (buffer[2] == 'I')
	{
		switch(c)
		{
			case '1': 
								Discharger();
								break;
			case '2': 
								Charger();
								break;
			case '3': 
								Status();
								break;
			default:
							break;
		}
	}
}

uint8_t LightTurnOn(void)
{
	HAL_GPIO_WritePin(GPIOA,CTRL_12V_LOAD_Pin,GPIO_PIN_SET);
	printf("@;AC;1;!\n\r");
	LightStatus = 1;
	 return 0;
}
uint8_t LightTurnOff(void)
{
	HAL_GPIO_WritePin(GPIOA,CTRL_12V_LOAD_Pin,GPIO_PIN_RESET);
	printf("@;AC;2;!\n\r");
	LightStatus = 0;
	 return 0;
}
uint8_t WaveToSolar(void)
{
	HAL_GPIO_WritePin(GPIOA,CTRL_WAVE_SOLAR_Pin,GPIO_PIN_SET);
	printf("@;AC;3;!\n\r");
	CurrentSource = 1;
	 return 0;
}
uint8_t SolarToWave(void)
{
	HAL_GPIO_WritePin(GPIOA,CTRL_WAVE_SOLAR_Pin,GPIO_PIN_RESET);
	printf("@;AC;4;!\n\r");
	CurrentSource = 0;
	 return 0;
}
uint8_t SavePowerMode(void)
{
	// Turn off DisplayLevel
	printf("@;AC;5;!\n\r");
	 return 0;
}
uint8_t NormalMode(void)
{
	// Turn on DisplayLevel
	printf("@;AC;6;!\n\r");
	 return 0;
}
uint8_t Discharger(void)
{
// 	  Read Discharge
			INA226_setCalibrationReg(&hi2c2,INA226_ADDRESS_DISCHARGE, INA226_CALIB_VAL_DISCHARGE);
			Vdischarge=INA226_getBusV(&hi2c2, INA226_ADDRESS_DISCHARGE);
			Idischarge = INA226_getCurrent_Discharge(&hi2c2, INA226_ADDRESS_DISCHARGE);
			Pdischarge = INA226_getPower_Discharge(&hi2c2, INA226_ADDRESS_DISCHARGE);
//		Vshunt =INA226_getShuntV(&hi2c2, INA226_ADDRESS_DISCHARGE);
//		IdischarReg = INA226_getCurrentReg(&hi2c2, INA226_ADDRESS_DISCHARGE);
//		if (Vdischarge > 14) HAL_GPIO_WritePin(GPIOB, Level1_Pin, GPIO_PIN_SET);
//		else HAL_GPIO_WritePin(GPIOB, Level1_Pin, GPIO_PIN_RESET);
//		HAL_Delay (100);
//		PowerReg = INA226_getPowerReg(&hi2c2, INA226_ADDRESS_DISCHARGE);
	    printf("@;AI;7;%.3f;%.4f;%.3f;!\n\r",Vdischarge,Idischarge,Pdischarge);
			return 0;
}
uint8_t Charger(void)
{
//    Read Charge
			INA226_setCalibrationReg(&hi2c2,INA226_ADDRESS_CHARGE, INA226_CALIB_VAL_CHARGE);
			Icharge = INA226_getCurrent_Charge(&hi2c2, INA226_ADDRESS_CHARGE);
  		Pcharge = INA226_getPower_Charge(&hi2c2, INA226_ADDRESS_CHARGE);
//		Vdischarge=INA226_getBusV(&hi2c2, INA226_ADDRESS_CHARGE);
//		Vshunt =INA226_getShuntV(&hi2c2, INA226_ADDRESS_CHARGE);
//		VshuntReg = INA226_getShuntVReg(&hi2c2, INA226_ADDRESS_CHARGE);
//		IdischarReg = INA226_getCurrentReg(&hi2c2, INA226_ADDRESS_CHARGE);
//		if (Vdischarge > 14) HAL_GPIO_WritePin(GPIOB, Level1_Pin, GPIO_PIN_SET);
//		else HAL_GPIO_WritePin(GPIOB, Level1_Pin, GPIO_PIN_RESET);
//		HAL_Delay (100);
//		PowerReg = INA226_getPowerReg(&hi2c2, INA226_ADDRESS_CHARGE);
			printf("@;AI;8;%.4f;%.3f;!\n\r",Icharge,Pcharge);
			return 0;
}
uint8_t Status(void)
{			
			float Vbattery= (float)HAL_ADC_GetValue(&hadc1)/4096.*12.6;
			printf("@;AI;9;%.3f;%d;%d!\n\r",Vbattery,LightStatus,CurrentSource);
		  return 0;
}
