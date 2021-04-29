/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define GREEN 	GPIO_PIN_0
#define RED 	GPIO_PIN_14
#define BLUE 	GPIO_PIN_7

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
//__HAL_UART_ENABLE_IT(&huart4,UART_IT_RXNE);
//#define Blink_LED (pin, sr) ( HAL_GPIO_WritePin(GPIOB, pin, sr); )
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
UART_HandleTypeDef huart4;
DMA_HandleTypeDef hdma_usart4_rx;

unsigned char msg_flag = 0;
unsigned char rx_uart4_buf[50]={};
char tx_uart4_buf[50]={};
unsigned int intr=0,count=0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void application_handling(unsigned char *cmd);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static void inline Blink_LED(unsigned int pin, unsigned char sr){
		HAL_GPIO_WritePin(GPIOB, pin, sr);
}

void delayfor(unsigned long int delay){
	for(unsigned long int i=0;i<delay;i++);
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
  MX_DMA_Init();
  MX_UART4_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  __HAL_UART_ENABLE_IT(&huart4,UART_IT_RXNE);
  printf("Application Start\r\n");
  strcpy(tx_uart4_buf,"Application Start\r\n");
  HAL_UART_Transmit(&huart4,(uint8_t *)&tx_uart4_buf,strlen(tx_uart4_buf),100);
  HAL_UART_Receive_DMA(&huart4,rx_uart4_buf,8);
  //HAL_UART_Receive_IT (&huart4, rx_uart4_buf, 12);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


  while (1)
  {
	  if(msg_flag){
		  application_handling(rx_uart4_buf);
		  msg_flag=0;
		  memset(rx_uart4_buf, 0, sizeof(rx_uart4_buf));
	  }
	  Blink_LED(BLUE,GPIO_PIN_SET);//Blink_LED(GREEN,GPIO_PIN_SET);
	  delayfor(60000);
	  Blink_LED(BLUE,GPIO_PIN_RESET);//Blink_LED(GREEN,GPIO_PIN_RESET);
	  delayfor(60000);

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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void application_handling(unsigned char *cmd)
{
	if(strstr(cmd, "LED ON") != NULL)
	{
		//Turn LED ON
		//HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
		Blink_LED(RED,GPIO_PIN_SET);
		printf("RED LED Turned ON\r\n");
	}
	else if(strstr(cmd, "LED OFF") != NULL)
	{
		//Turn LED OFF
		//HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		Blink_LED(RED,GPIO_PIN_RESET);
		printf("RED LED Turned OFF\r\n");
	}
	else
	{
		//Invalid command
		printf("Invalid Command!\r\n");
	}
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==UART4){
		msg_flag=1;
	}
    HAL_UART_Transmit(&huart4, rx_uart4_buf, 8, 100);
    HAL_UART_Receive_DMA(&huart4, rx_uart4_buf, 8);
    //HAL_UART_Receive_IT(&huart4, rx_uart4_buf, 12);
}

/*
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	UNUSED(huart);
//	if(huart->Instance==UART4){
//			msg_flag = 1;
//	}
	Blink_LED(RED,GPIO_PIN_SET);
	//application_handling(rx_uart4_buf);
	//memset(rx_uart4_buf, 0, sizeof(rx_uart4_buf));
	//Get back to state 1
	HAL_UART_Receive_DMA(&huart4, (uint8_t *)rx_uart4_buf, 3);
	//HAL_UART_Transmit(&huart4,(uint8_t *)&rx_uart4_buf,1,100);
	if(rx_uart4_buf[0] == '1')
		Blink_LED(RED,GPIO_PIN_SET);
	else
		Blink_LED(RED,GPIO_PIN_RESET);
}
*/
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
