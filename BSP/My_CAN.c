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

static uint8_t data[8];//�������ݻ�����

void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef *hcan)
{
	for(uint8_t i=0; i<8; i++)
		data[i] = hcan->pRxMsg->Data[i];
}


