/** 
	* @brief    CAN
	* @details  CAN相关函数
	* @author   Onion rain
	* @date     2018.10.15 
	* @version  1.0
	* @par Copyright (c):  Onion rain
	* @par 日志
*/

#include "My_CAN.h"
#include "can.h"
#include <string.h>

MonitorData_t MonitorData;

CanRxMsgTypeDef RxMessage;

void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan)
{
	 __HAL_CAN_ENABLE_IT(hcan, CAN_IT_FMP0);
	 if(hcan->pRxMsg->StdId == 0x301)
	 {
			memcpy(&MonitorData, hcan->pRxMsg->Data, 8);
	 }
}

void CAN_FilterConfig(void)
{
	hcan.pRxMsg = &RxMessage;
	CAN_FilterConfTypeDef  sFilterConfig;
	
	sFilterConfig.FilterNumber = 0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh = 0x0000;
  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0x0000;
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.BankNumber = 14;
  HAL_CAN_ConfigFilter(&hcan, &sFilterConfig);
}

void CAN_Init(void)
{
	CAN_FilterConfig();
	__HAL_CAN_ENABLE_IT(&hcan, CAN_IT_FMP0);
}


