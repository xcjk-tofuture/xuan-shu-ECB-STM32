#ifndef __MOTOR_PROC_H
#define __MOTOR_PROC_H


#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "sys.h"
#include "tim.h"

typedef struct motor
{
	u8 Num;       //编号
	u8 direction; //方向
	s32 Trig;     //脉冲数
	float Speed;  //当前速度
	s16 SetSpeedRange; //设定的速度档位   负号代表反方向
	s8 SetDirection; //   负号代表反方向
	
}MOTOR;

void Motor_Encoder_Init();
void Motor_Get_Value(MOTOR  *motor);
void Motor_Init();
void Motor_Speed_Set(MOTOR *motor, s16 speed);
void Motor_Speed_Set_Extra(MOTOR *motor, s16 speed);
#endif