#include "DisplayLevel.h"
float Vadap;
void TurnOnShowLevel(void )
{
	
	Vadap= (float)HAL_ADC_GetValue(&hadc1)/4096.*3.3;
	if ((Vadap<=3.3)&&(Vadap>=3.114))
	{
			HAL_GPIO_WritePin(GPIOB,Level1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level32_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level4_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level65_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level7_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level89_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level10_Pin,GPIO_PIN_SET);
	}
	else if ((Vadap<3.114)&&(Vadap>=2.928))
	{
			HAL_GPIO_WritePin(GPIOB,Level1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level32_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level4_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level65_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level7_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level89_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level10_Pin,GPIO_PIN_RESET);
	}
	else if ((Vadap<2.928)&&(Vadap>=2.742))
	{
			HAL_GPIO_WritePin(GPIOB,Level1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level32_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level4_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level65_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level7_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level89_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,Level10_Pin,GPIO_PIN_RESET);
	}
	else if ((Vadap<2.742)&&(Vadap>=2.556))
	{
			HAL_GPIO_WritePin(GPIOB,Level1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level32_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level4_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level65_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level7_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,Level89_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,Level10_Pin,GPIO_PIN_RESET);
	}
	else if ((Vadap<2.556)&&(Vadap>=2.37))
	{
			HAL_GPIO_WritePin(GPIOB,Level1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level32_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level4_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level65_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,Level7_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,Level89_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,Level10_Pin,GPIO_PIN_RESET);
	}
	else if ((Vadap<2.37)&&(Vadap>=2.184))
	{
			HAL_GPIO_WritePin(GPIOB,Level1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level32_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level4_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,Level65_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,Level7_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,Level89_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,Level10_Pin,GPIO_PIN_RESET);
	}
	else if ((Vadap<2.184)&&(Vadap>=1.998))
	{
			HAL_GPIO_WritePin(GPIOB,Level1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,Level32_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,Level4_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,Level65_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,Level7_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,Level89_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,Level10_Pin,GPIO_PIN_RESET);
	}
	else if ((Vadap<1.998))
	{
			TurnOffShowLevel();
	}
}
void TurnOffShowLevel(void )
{
		HAL_GPIO_WritePin(GPIOB,Level1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB,Level32_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB,Level4_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB,Level65_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB,Level7_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB,Level89_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB,Level10_Pin,GPIO_PIN_RESET);
}
