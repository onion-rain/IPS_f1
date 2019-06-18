/** 
	* @brief    CAN
	* @details  CAN�ص�����
	* @author   Onion rain
	* @date     2018.10.15 
	* @version  1.0
	* @par Copyright (c):  Onion rain
	* @par ��־
*/

#include "My_CAN.h"
#include "can.h"
#include <string.h>

MonitorData_t MonitorData;

void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef *hcan)
{
	memcpy(&MonitorData, hcan->pRxMsg->Data, 8);
}


