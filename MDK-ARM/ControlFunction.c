#include "ControlFunction.h"

void TurnOnWave(void )
{
		HAL_GPIO_WritePin(GPIOA,CTRL_WAVE_SOLAR_Pin,GPIO_PIN_RESET);
}
void TurnOnSun(void )
{
		HAL_GPIO_WritePin(GPIOA,CTRL_WAVE_SOLAR_Pin,GPIO_PIN_SET);
}
void TurnOff5VLoad(void)
{
		HAL_GPIO_WritePin(GPIOA,CRTL_5V_LOAD_Pin,GPIO_PIN_RESET);
}
void TurnOn5VLoad(void )
{
		HAL_GPIO_WritePin(GPIOA,CRTL_5V_LOAD_Pin,GPIO_PIN_SET);
}
void TurnOff12VLoad(void )
{
		HAL_GPIO_WritePin(GPIOA,CTRL_12V_LOAD_Pin,GPIO_PIN_RESET);
}
void TurnOn12VLoad(void)
{
		HAL_GPIO_WritePin(GPIOA,CTRL_12V_LOAD_Pin,GPIO_PIN_SET);
}
