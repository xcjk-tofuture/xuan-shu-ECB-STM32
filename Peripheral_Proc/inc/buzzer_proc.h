#ifndef __BUZZIER_PROC_H
#define __BUZZIER_PROC_H


#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "timers.h"
#include "tim.h"





void Buzzer_Task_Proc(void const * argument);
void driveBuzzer(uint16_t frequency, uint32_t duration);
void playMusic(void);
void Music_Play_Lowbattery();  //电机电量不足音乐
void Music_Play_StartUp();  //开机音乐

#endif