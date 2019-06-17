/** 
	* @brief    CAN
	* @details  CAN回调函数
	* @author   Onion rain
	* @date     2018.10.15 
	* @version  1.0
	* @par Copyright (c):  Onion rain
	* @par 日志
*/

#include "My_CAN.h"
#include "can.h"

static uint8_t data[8];//接收数据缓冲区

void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef *hcan)
{
	for(uint8_t i=0; i<8; i++)
		data[i] = hcan->pRxMsg->Data[i];
}


