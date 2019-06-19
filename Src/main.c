
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "can.h"
#include "spi.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "OLED_SPI.h"
#include "My_CAN.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
#define OLED_SIZE 16 
uint16_t COLOR = WHITE;//Ĭ����ɫ��ɫ
static char average_buffer[8]={0},
						bulletSpeed_buffer[8]={0},
						n_buffer[8]={0}, 
						n_block_buffer[8]={0}, 
						friction_spe_set_buffer[8] = {0}, 
						variance_buffer[8] = {0},
						magazine_speed_buffer[8] = {0};//OLEDˢ�����ݻ����
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_CAN_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
	CAN_Init();
	CHIP_SELECTED();//Ƭѡ�ź�
	InitST7735S();//OLED���س�ʼ��
	BIAS_LIGHT_ON();//�����⿪
	Display_Purity_Color(BLACK);//����
	OLED_Display_ON();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		if(HAL_GetTick()-Last_update_tick > 200)
			Online_flag = 0;
		
		if(Online_flag)
		{
			if(MonitorData.Cloud_Pitch_OutofContact)
				OLED_ShowString(0, 0, (char*)"Pitch", OLED_SIZE, MAGENTA|YELLOW, PURITY);
			else OLED_ShowString(0, 0, (char*)"Pitch", OLED_SIZE, CYAN, PURITY);
			
			if(MonitorData.Cloud_Yaw_OutofContact)
				OLED_ShowString(0, OLED_SIZE, (char*)"Yaw  ", OLED_SIZE, MAGENTA|YELLOW, PURITY);
			else OLED_ShowString(0, OLED_SIZE, (char*)"Yaw  ", OLED_SIZE, CYAN, PURITY);
			
			if(MonitorData.Cloud_Magzine_OutofContact)
				OLED_ShowString(0, OLED_SIZE*2, (char*)"Magaz", OLED_SIZE, MAGENTA|YELLOW, PURITY);
			else OLED_ShowString(0, OLED_SIZE*2, (char*)"Magaz", OLED_SIZE, CYAN, PURITY);
			
			if(MonitorData.Cloud_Fric_l_OutofContact)
				OLED_ShowString(0, OLED_SIZE*3, (char*)"Fricl", OLED_SIZE, MAGENTA|YELLOW, PURITY);
			else OLED_ShowString(0, OLED_SIZE*3, (char*)"Fricl", OLED_SIZE, CYAN, PURITY);
			
			if(MonitorData.Cloud_Fric_r_OutofContact)
				OLED_ShowString(0, OLED_SIZE*4, (char*)"Fricr", OLED_SIZE, MAGENTA|YELLOW, PURITY);
			else OLED_ShowString(0, OLED_SIZE*4, (char*)"Fricr", OLED_SIZE, CYAN, PURITY);
			
			
			if(MonitorData.ChassisOutofContact)
				OLED_ShowString(50, 0, (char*)"Chassis", OLED_SIZE, MAGENTA|YELLOW, PURITY);
			else OLED_ShowString(50, 0, (char*)"Chassis", OLED_SIZE, CYAN, PURITY);
			
			if(MonitorData.Wheel_LF_OutofContact)
				OLED_ShowString(50, OLED_SIZE, (char*)"Motor1", OLED_SIZE, MAGENTA|YELLOW, PURITY);
			else OLED_ShowString(50, OLED_SIZE, (char*)"Motor1", OLED_SIZE, CYAN, PURITY);
			
			if(MonitorData.Wheel_RF_OutofContact)
				OLED_ShowString(50, OLED_SIZE*2, (char*)"Motor2", OLED_SIZE, MAGENTA|YELLOW, PURITY);
			else OLED_ShowString(50, OLED_SIZE*2, (char*)"Motor2", OLED_SIZE, CYAN, PURITY);
			
			if(MonitorData.Wheel_LB_OutofContact)
				OLED_ShowString(50, OLED_SIZE*3, (char*)"Motor3", OLED_SIZE, MAGENTA|YELLOW, PURITY);
			else OLED_ShowString(50, OLED_SIZE*3, (char*)"Motor3", OLED_SIZE, CYAN, PURITY);
			
			if(MonitorData.Wheel_RB_OutofContact)
				OLED_ShowString(50, OLED_SIZE*4, (char*)"Motor4", OLED_SIZE, MAGENTA|YELLOW, PURITY);
			else OLED_ShowString(50, OLED_SIZE*4, (char*)"Motor4", OLED_SIZE, CYAN, PURITY);
			
			
			if(MonitorData.VisionOutofContact)
				OLED_ShowString(110, 0, (char*)"Vision", OLED_SIZE, MAGENTA|YELLOW, PURITY);
			else OLED_ShowString(110, 0, (char*)"Vision", OLED_SIZE, CYAN, PURITY);
			
			if(MonitorData.DbusOutofContact)
				OLED_ShowString(110, OLED_SIZE, (char*)"Dbus", OLED_SIZE, MAGENTA|YELLOW, PURITY);
			else OLED_ShowString(110, OLED_SIZE, (char*)"Dbus", OLED_SIZE, CYAN, PURITY);
			
			if(MonitorData.JudgementOutofContact)
				OLED_ShowString(110, OLED_SIZE*2, (char*)"Judge", OLED_SIZE, MAGENTA|YELLOW, PURITY);
			else OLED_ShowString(110, OLED_SIZE*2, (char*)"Judge", OLED_SIZE, CYAN, PURITY);
			
//			if(MonitorData.Cloud_Yaw_OutofContact)
//				OLED_ShowString(110, OLED_SIZE*3, (char*)"hhh", OLED_SIZE, MAGENTA|YELLOW, PURITY);
//			else OLED_ShowString(110, OLED_SIZE*3, (char*)"hhh", OLED_SIZE, CYAN, PURITY);
//			
//			if(MonitorData.Cloud_Yaw_OutofContact)
//				OLED_ShowString(110, OLED_SIZE*4, (char*)"hhh", OLED_SIZE, MAGENTA|YELLOW, PURITY);
//			else OLED_ShowString(110, OLED_SIZE*4, (char*)"hhh", OLED_SIZE, CYAN, PURITY);
		}else
		{
			OLED_ShowString(20, 15, (char*)"CLOUD", 28, YELLOW, PURITY);
			OLED_ShowString(40, 44, (char*)"OFFLINE", 28, YELLOW, PURITY);
		}

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
