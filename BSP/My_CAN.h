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
	
	uint32_t DbusOutofContact : 1;
	uint32_t ChassisOutofContact : 1;
	uint32_t JudgementOutofContact : 1;
	uint32_t VisionOutofContact : 1;
	uint32_t Wheel_LF_OutofContact : 1;
	uint32_t Wheel_RF_OutofContact : 1;
	uint32_t Wheel_LB_OutofContact : 1;
	uint32_t Wheel_RB_OutofContact : 1;
	
	uint32_t Cloud_Fric_l_OutofContact : 1;
	uint32_t Cloud_Fric_r_OutofContact : 1;
	uint32_t Cloud_Yaw_OutofContact : 1;
	uint32_t Cloud_Pitch_OutofContact : 1;
	uint32_t Cloud_Magzine_OutofContact : 1;
	uint32_t ChassisJudgementOutofContact : 1;
	uint32_t CloudJudgementRepaired : 1;
	uint32_t ChassisJudgementRepaired : 1;
	
	uint32_t TFCardOutofContact : 1;
	uint32_t BuffCamOutofContact : 1;
	uint32_t a : 14;
	
	uint32_t b;
}MonitorData_t;//�豸��������
extern MonitorData_t MonitorData;

extern uint8_t Online_flag;//�����ӵ����ر�־
extern uint32_t Last_update_tick;//�ϴθ���ʱ��

void CAN_Init(void);

#endif
