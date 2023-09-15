#include "servo_proc.h"




osThreadId ServoTaskHandle;



//并行舵机对4应的定时器为
//TIM1 TIM_CHANNEL 1-4 
//TIM8 TIM_CHANNEL 3 4 
//TIM10 TIM_CHANNEL 1
//TIM11 TIM_CHANNEL 1

//时钟默认分配为1MHZ  arr默认为19999  则对应ARR 5% - 25%  CCR为 999 - 4999

//舵机进程
void Servo_Task_Proc(void const * argument)
{
  /* USER CODE BEGIN Servo_Task_Proc */
  /* Infinite loop */
	

	//Servo_Diver(8, 80);		if(++Count  > 10)
	//		u8 Count;
  for(;;)
  {
	Servo_Enable_All();
	Servo_Diver(1, 0);
	Servo_Diver(2, 100);
	Servo_Diver(3, 30);
	Servo_Diver(4, 40);
	Servo_Diver(5, 50);
	Servo_Diver(6, 60);
	Servo_Diver(7, 70);

//		Servo_Diver(1, 100);
//		Servo_Diver(2, 0);
//		Servo_Diver(3, 0);
//		Servo_Diver(4, 0);
//		Servo_Diver(5, 0);
//		Servo_Diver(6, 100);
//		Servo_Diver(7, 50);
//		Servo_Diver(8, Count * 50);
//				if(++Count  >= 3)
//				Count = 0;
		osDelay(1000);
  }
  /* USER CODE END Servo_Task_Proc */
}


/******************************************************************************
      函数说明：使能全部舵机 舵机全部回中
      入口数据：无    
      返回值：  无
******************************************************************************/
void Servo_Enable_All()
{

	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim11, TIM_CHANNEL_1);
	
//	TIM1->CCR1 = 1499;
//	TIM1->CCR2 = 1499;
//	TIM1->CCR3 = 1499;
//	TIM1->CCR4 = 1499;
	TIM8->CCR3 = 1499;
	TIM8->CCR4 = 1499;
	TIM10->CCR1 = 1499;
	TIM11->CCR1 = 1499;
	
	//TIM1->CCR1 = 3399;
}

/******************************************************************************
      函数说明：失能舵机
      入口数据：servo_num   舵机id 对应板子上的1到8            
      返回值：  无
******************************************************************************/
void Servo_Disable(u8 servo_num)
{
	if(servo_num == 1)
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	if(servo_num == 2)
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
	if(servo_num == 3)
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
	if(servo_num == 4)
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_4);
	if(servo_num == 5)
		HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_3);
	if(servo_num == 6)
		HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_4);
	if(servo_num == 7)
		HAL_TIM_PWM_Stop(&htim10, TIM_CHANNEL_1);
	if(servo_num == 8)
		HAL_TIM_PWM_Stop(&htim11, TIM_CHANNEL_1);

}

/******************************************************************************
      函数说明：指定舵机转相应范围  对应占空比2.5%-12.5%
      入口数据：servo_num   舵机id 对应板子上的1到8
							 range			 范围 默认0-100
      返回值：  无
******************************************************************************/
void Servo_Diver(u8 servo_num, u8 range)
{
		if(servo_num == 1)
		{
				TIM1->CCR1 =  (TIM1->ARR + 1 ) * 0.025 + (TIM1->ARR + 1 ) * range * 0.001  - 1;
				//printf("%d\r\n",TIM1->CCR1);
		}
		else if(servo_num == 2)
		{
				TIM1->CCR2 =  (TIM1->ARR + 1 ) * 0.025 + (TIM1->ARR + 1 ) * range * 0.001  - 1;
				//printf("%d\r\n",TIM1->CCR2);
		}
		else if(servo_num == 3)
		{
				TIM1->CCR3 =  (TIM1->ARR + 1 ) * 0.025 + (TIM1->ARR + 1 ) * range * 0.001  - 1;
				//printf("%d\r\n",TIM1->CCR3);
		}
		else if(servo_num == 4)
		{
				TIM1->CCR4 =  (TIM1->ARR + 1 ) * 0.025 + (TIM1->ARR + 1 ) * range * 0.001  - 1;
				//printf("%d\r\n",TIM1->CCR4);
		}
				else if(servo_num == 5)
		{
				TIM8->CCR3 =  (TIM8->ARR + 1 ) * 0.025 + (TIM8->ARR + 1 ) * range * 0.001  - 1;
				//printf("%d\r\n",TIM8->CCR3);
		}
		else if(servo_num == 6)
		{
				TIM8->CCR4 =  (TIM8->ARR + 1 ) * 0.025 + (TIM8->ARR + 1 ) * range * 0.001  - 1;
				//printf("%d\r\n",TIM8->CCR4);
		}
		else if(servo_num == 7)
		{
				TIM10->CCR1 =  (TIM10->ARR + 1 ) * 0.025 + (TIM10->ARR + 1 ) * range * 0.001  - 1;
				//printf("%d\r\n",TIM10->CCR1);
		}
				else if(servo_num == 8)
		{
				TIM11->CCR1 =  (TIM11->ARR + 1 ) * 0.025 + (TIM11->ARR + 1 ) * range * 0.001  - 1;
				//printf("%d\r\n",TIM11->CCR1);
		}

}