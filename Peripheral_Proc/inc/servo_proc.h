#ifndef __SERVO_PROC_H
#define __SERVO_PROC_H



#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "sys.h"
#include "tim.h"


void Servo_Diver(u8 servo_num, u8 range);
void Servo_Disable(u8 Servo_Num);
void Servo_Enable_All();



#endif