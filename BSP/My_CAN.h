/** 
	* @brief    CAN
	* @details  CAN�ص�����
	* @author   Onion rain
	* @date     2018.10.15 
	* @version  1.0
	* @par Copyright (c):  Onion rain
	* @par ��־
*/

#ifndef __My_CAN_H
#define	__My_CAN_H

#include "stm32f1xx_hal.h"

typedef struct{//�Ӳ���ϵͳ��ȡ������̨��Ҫ������
	uint8_t DbusOutofContact : 1;
	uint8_t ChassisOutofContact : 1;
	uint8_t JudgementOutofContact : 1;
	uint8_t VisionOutofContact : 1;
	uint8_t Wheel_LF_OutofContact : 1;
	uint8_t Wheel_RF_OutofContact : 1;
	uint8_t Wheel_LB_OutofContact : 1;
	uint8_t Wheel_RB_OutofContact : 1;
	
	uint8_t Cloud_Fric_l_OutofContact : 1;
	uint8_t Cloud_Fric_r_OutofContact : 1;
	uint8_t Cloud_Yaw_OutofContact : 1;
	uint8_t Cloud_Pitch_OutofContact : 1;
	uint8_t Cloud_Magzine_OutofContact : 1;
	uint8_t x : 3;
	
	uint16_t a;
	uint16_t b;
	uint16_t c;
}MonitorData_t;//�豸��������
extern MonitorData_t MonitorData;

#endif
