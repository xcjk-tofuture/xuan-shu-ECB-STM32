#include "buzzer_proc.h"

osThreadId BuzzerTaskHandle;


// 定义七种音的频率
#define DO 523
#define RE 587
#define MI 659
#define FA 698
#define SO 784
#define LA 880
#define SI 988



void Buzzer_Task_Proc(void const * argument)
{
  /* USER CODE BEGIN Buzzier_Task_Proc */
  /* Infinite loop */
	//pwm_init(1000, 50);
//开机音效
	Music_Play_StartUp();
//	driveBuzzer(LA, 200);
//	driveBuzzer(SI, 200);
	
  for(;;)
  {
		

    osDelay(1000);
  }
  /* USER CODE END Buzzier_Task_Proc */
}

//驱动发生音乐
void driveBuzzer(uint16_t frequency, uint32_t duration) 
	{  

	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
	TIM12->ARR  = (1000000/ frequency) - 1;
	TIM12->CCR1  = ((TIM12->ARR +1 ) * 0.5) - 1; 
	osDelay(duration);
  HAL_TIM_PWM_Stop(&htim12, TIM_CHANNEL_1);
}


void Music_Play_StartUp()  //开机音乐
{
  driveBuzzer(DO, 200);
	driveBuzzer(RE, 200);
	driveBuzzer(MI, 200);
	driveBuzzer(DO, 200);
	driveBuzzer(RE, 200);
	driveBuzzer(MI, 200);
	driveBuzzer(SO, 200);
	driveBuzzer(FA, 200);

}

void Music_Play_Lowbattery()  //电机电量不足音乐
{
	driveBuzzer(MI, 200);
	driveBuzzer(RE, 200);
  driveBuzzer(DO, 200);
	
	driveBuzzer(MI, 200);
	driveBuzzer(RE, 200);
  driveBuzzer(DO, 200);
	

}
