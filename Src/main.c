/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "DisplayLevel.h"
#include "ControlFunction.h"
#include "CommandProces.h"
#include "Ina226.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern float Vadap;
extern float Vdischarge;
extern float Idischarge;
extern float Pdischarge;
extern float Icharge;
extern float Pcharge;
extern uint8_t LightStatus;
extern uint8_t CurrentSource ;
float Vshunt=0;
int16_t VshuntReg =0;
int16_t IdischarReg=0;
uint16_t PowerReg =0;
uint8_t adress=0;
uint8_t FlagLoad=0;

extern char buffer[100]; //Khai bao mang buffer 100 phan tu
int len; //Khai bao bien len tuong ung voi chieu dai
char Rx_indx, Rx_data[2], Transfer_cplt;
extern char Rx_Buffer[100]; 
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t i;
	//static char data=0;
	if (huart-> Instance == USART2) // UART hien tai la uart3
	{ 
		if (Rx_indx==0) {for (i=0;i<100;i++) Rx_Buffer[i]=0;} // xoa Rx_Buffer truoc khi nhan du lieu
		
		if (Rx_data[0] !=13) // Neu du lieu nhan duoc khac voi 13 ( enter )
		{
			Rx_Buffer[Rx_indx++]=Rx_data[0];
//			if( (data=='@')&& (Rx_data[0]!='@')) Rx_Buffer[Rx_indx++]=Rx_data[0];
//			if ( (data==0)&& (Rx_data[0]=='@')) { data='@';} // Them du lieu vao Rx_Buffer
		}
		else // Neu phihm enter duoc nhan
		{
			Rx_indx =0 ;  // Dua indx ve 0
			Transfer_cplt =1 ; // Qua tring truyen hoan tat, du lieu da san sang de doc
		}
		HAL_UART_Receive_IT(&huart2 , (uint8_t *)&Rx_data, 1); //Kich hoat Uart nhan du lieu ngat moi luc
	}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_I2C2_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	HAL_ADC_Start(&hadc1);
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_GPIO_WritePin(GPIOB,Level1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,Level32_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,Level4_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,Level65_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,Level7_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,Level89_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,Level10_Pin,GPIO_PIN_RESET);
	TurnOffShowLevel();
	//I2C_HandleTypeDef I2c1Handle;
	// Set Config Register
	INA226_setConfig(&hi2c2, INA226_ADDRESS_CHARGE, INA226_MODE_CONT_SHUNT_AND_BUS|INA226_VBUS_140uS|INA226_AVG_1024);
	// Set Alert Limit Register ( 6400 = 0x1900 )
	INA226_setAlertLimit (&hi2c2, INA226_ADDRESS_DISCHARGE,INA226_Vdischar_UnderVoltage_AlertLimit);	
	// Set  Discharge Voltage Under-Voltage ( 8V )
	INA226_setMaskEnable(&hi2c2,INA226_ADDRESS_DISCHARGE, INA226_MER_BUL);
	// Bat ngat uart
	HAL_UART_Receive_IT(&huart2,(uint8_t *)Rx_data,1); // Kich hoat ngat uart khi nhan duoc 1 byte
  CurrentSource=1;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	//HAL_Delay(1000);
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		if ((HAL_GPIO_ReadPin(GPIOB,ALERT_DISCHARGE_Pin) == 1)&&(FlagLoad==1))
		{
			//printf("Da bat alert va tat\r\n");
			FlagLoad =0;
			HAL_GPIO_WritePin(GPIOA,CRTL_5V_LOAD_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA,CTRL_12V_LOAD_Pin,GPIO_PIN_SET);
		}
		else
		{
//			char str[] = "Hello world\r\n";
//			HAL_UART_Transmit(&huart2,(uint8_t *)&str,sizeof(str),100);
//			printf("Hello world\r\n");
//			HAL_Delay(1000);
			if (Transfer_cplt)
			{
				
//			sprintf(buffer,"%s\r\n",Rx_Buffer)
				PreProces();
				MainProce();
// 			printf("%s\r\n",buffer);
				Transfer_cplt =0;
			}
		}
  }

	
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
	_ARMABI int fputc(int c, FILE *stream)
{
		HAL_UART_Transmit(&huart2, (uint8_t *) &c,1,100);
		return 0;
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
		if  (htim->Instance == TIM2)
		{
				
				if ( FlagLoad ==1 )
				{
					
					HAL_GPIO_TogglePin(GPIOB,Level1_Pin);
					HAL_GPIO_WritePin(GPIOB,Level32_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOB,Level4_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOB,Level65_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOB,Level7_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOB,Level89_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOB,Level10_Pin,GPIO_PIN_RESET);
				}
				else TurnOnShowLevel();
		}
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
		if (GPIO_Pin == ALERT_DISCHARGE_Pin)
		{
				HAL_GPIO_WritePin(GPIOA,CRTL_5V_LOAD_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA,CTRL_12V_LOAD_Pin,GPIO_PIN_RESET);
				FlagLoad =1;
				//printf("Da bat alert\r\n");
			
		}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
