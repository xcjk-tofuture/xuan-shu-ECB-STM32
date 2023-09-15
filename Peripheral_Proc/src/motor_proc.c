#include "motor_proc.h"
#include "simplepid.h"
#include "niming.h"

//*****************************
//注意1软件pwm生成 用到了 定时器7  10us一次中断 分为1000份 生成不同占空比的1khz的波形来驱动电机
//*****************************
//*****************************
//注意2电机由于是镜像放置 所以有方向正 方向反  现采用强制定义 定义A C为正方向电机   B D为反方向电机 带有强制取反操作  故安装电机时 例如 前轮为C D一组 后轮 为 A B 一组的安装
//*****************************

osThreadId MotorTaskHandle;
osThreadId EncoderTaskHandle;
int motor1;
int motor2;
extern int change_output;
extern int change_x;
extern tPid speed_left;
extern tPid speed_right;
u32 TIM7Count;
extern int angle;
extern int change_output;
extern int change_x;
extern int x;
MOTOR MotorA, MotorB;  //编号对应 0 1 

void xianfu_angle(int * motor)
{
	if(*motor < 30)
		*motor = -30;
}


//void xianfu_position(int x,int* change_x)
//{
//	if(x<=10  &&  x>=-10)
//		*change_x = 0;
//}


//void xianfu_chasu()
//{
//	if(fabs(change_output*2 - change_x*2) > 200)
//		
//}
void ditongfilter(int* motor,int target)
{
	*motor = *motor * 0.4 + target * 0.6;
}
void Motor_Task_Proc(void const * argument)   //电机驱动进程
{
	
	Motor_Init();
	//PID_speedinit();
  s16 Count = 0;
	for(;;)
	{
		
		Motor_Speed_Set(&MotorA, 950);
	
//		Motor_Speed_Set(&MotorA, -500);
//		osDelay(1000);
		Motor_Speed_Set(&MotorB, 950);
//		if(++Count > 9)
//			Count = -9;
//		TIM4->ARR = 999;
//		HAL_GPIO_WritePin(MOTORA_IN1_GPIO_Port, MOTORA_IN1_Pin, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(MOTORA_IN2_GPIO_Port, MOTORA_IN2_Pin, GPIO_PIN_RESET);
//		TIM4->CCR3 = 800;
//		
//		HAL_GPIO_WritePin(MOTORB_IN1_GPIO_Port, MOTORB_IN1_Pin, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(MOTORB_IN2_GPIO_Port, MOTORB_IN2_Pin, GPIO_PIN_SET);
//		TIM4->CCR4 = 600;
		printf("num:%d, speed:%.2f, direction: %d\r\n",MotorA.Num, MotorA.Speed, MotorA.direction);
		printf("num:%d, speed:%.2f, direction: %d\r\n",MotorB.Num, MotorB.Speed, MotorB.direction);

		osDelay(100);

	}


}

void Encoder_Task_Proc(void const * argument)		//编码器读取进程
{

		Motor_Encoder_Init();//编码器初始化
		for(;;)
	{
		Motor_Get_Value(&MotorA);
		Motor_Get_Value(&MotorB);
		osDelay(10);
	}
}



//电机编码器初始化
/******************************************************************************
      函数说明：电机编码器初始化（封存编码器模式读脉冲）
      入口数据：无    
      返回值：  无
******************************************************************************/
void Motor_Encoder_Init()
{

	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1); 
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_2);
																									//开启编码器模式
  HAL_TIM_Base_Start_IT(&htim2);                  //开启编码器的中断
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1); //开启编码器模式
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_2);
	HAL_TIM_Base_Start_IT(&htim3);                  //开启编码器的中断
                 //开启编码器的中断
	MotorA.Num = 0;
	MotorB.Num = 1;
}

//获取电机的脉冲值 方向  并转换为速度 电机 A B C D 对应 0 1 2 3
/******************************************************************************
      函数说明：四倍频外部中断法 M测速法 获取电机的脉冲值 方向  并转换为速度 电机 A B C D 对应 0 1 2 3
      入口数据：电机结构体指针    
      返回值：  无
******************************************************************************/
void Motor_Get_Value(MOTOR  *motor)
{
	switch(motor->Num)
	{
		case 0: motor->Trig = __HAL_TIM_GetCounter(&htim2);//获取计数值  
						__HAL_TIM_SetCounter(&htim2, 0);//清空计数值
						motor->direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim2);//获取方向		
						motor->direction = !motor->direction;  
						motor->Speed = motor->Trig * 3.25 ;
						break;
		case 1: motor->Trig = (short)__HAL_TIM_GetCounter(&htim3);//获取计数值  
						__HAL_TIM_SetCounter(&htim3, 0);//清空计数值
						motor->direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim3);//获取方向		
						motor->direction = !motor->direction;  //强制取反
						motor->Trig = -motor->Trig;						//强制取反
						motor->Speed = motor->Trig * 3.25 ;
						break;
	}
					
}

/******************************************************************************
      函数说明：电机输出pwm初始化
      入口数据：无    
      返回值：  无
******************************************************************************/
void Motor_Init()
{

	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);  //MOTORA_PWM
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);	 //MOTORB_PWM

	HAL_GPIO_WritePin(MOTORB_IN1_GPIO_Port, MOTORB_IN1_Pin, 0);
	HAL_GPIO_WritePin(MOTORB_IN2_GPIO_Port, MOTORB_IN2_Pin, 0);
	HAL_GPIO_WritePin(MOTORA_IN1_GPIO_Port, MOTORA_IN1_Pin, 0);
	HAL_GPIO_WritePin(MOTORA_IN2_GPIO_Port, MOTORA_IN2_Pin, 0);
	
}


/******************************************************************************
      函数说明：绝对值函数
      入口数据：数值    
      返回值：  无
******************************************************************************/
int ABS(int a)
{
	a = a>0?a:(-a);
	return a;

}

/******************************************************************************
      函数说明：PWM1-4辅助电机控制  速度设置函数 设置电机速度  范围 -999 - +999
      入口数据：电机结构体指针   速度    
      返回值：  无
******************************************************************************/
//void Motor_Speed_Set_Extra(MOTOR *motor, s16 speed)
//{

//	if(speed >= 1000 ) speed = 999;
//	if(speed <= -1000 ) speed = -999;   //限幅
//switch(motor->Num)
//{
//	case 0: motor->SetSpeedRange = speed;
//				motor->SetDirection =  motor->SetSpeedRange >= 0 ? 0 : 1;  //判断方向   0为正 1为负
//				if(!motor->SetDirection) //正向
//				{
//						TIM1->CCR1 = 0;
//						TIM1->CCR2 = ABS((motor->SetSpeedRange   + 1)* 2 -1) ; 
//						 
//				
//				}
//				else if(motor->SetDirection)
//				{
//						TIM1->CCR2 = 0;
//						TIM1->CCR1 = ABS((motor->SetSpeedRange   + 1) * 2 -1) ; 
//				}
//				break;
//	case 1: motor->SetSpeedRange = speed;
//				motor->SetDirection =  motor->SetSpeedRange >= 0 ? 0 : 1;  //判断方向
//				if(!motor->SetDirection) //正向
//				{
//						TIM1->CCR4 = 0;
//						TIM1->CCR3 = ABS((motor->SetSpeedRange + 1) * 2 -1) ; 
//						 
//				
//				}
//				else if(motor->SetDirection)
//				{
//						TIM1->CCR3 = 0;
//						TIM1->CCR4 = ABS((motor->SetSpeedRange + 1) * 2 -1); 
//				}
//				break;
//}	
//	
//	
//	
//}


/******************************************************************************
      函数说明：电机速度设置函数 设置电机速度  范围 -999 - +999
      入口数据：电机结构体指针   速度    
      返回值：  无
******************************************************************************/
void Motor_Speed_Set(MOTOR *motor, s16 speed)
{

	if(speed >= 1000 ) speed = 999;
	if(speed <= -1000 ) speed = -999;   //限幅
	switch(motor->Num)
	{
		case 0: motor->SetSpeedRange = speed;
						motor->SetDirection =  motor->SetSpeedRange >= 0 ? 0 : 1;  //判断方向   0为正 1为负
						if(!motor->SetDirection) //正向
						{
							HAL_GPIO_WritePin(MOTORA_IN1_GPIO_Port, MOTORA_IN1_Pin, 1);
							HAL_GPIO_WritePin(MOTORA_IN2_GPIO_Port, MOTORA_IN2_Pin, 0);
							TIM4->CCR3 = ABS(motor->SetSpeedRange) ; 
								 
						
						}
					else if(motor->SetDirection) //反向
					{
							HAL_GPIO_WritePin(MOTORA_IN1_GPIO_Port, MOTORA_IN1_Pin, 0);
							HAL_GPIO_WritePin(MOTORA_IN2_GPIO_Port, MOTORA_IN2_Pin, 1);
							TIM4->CCR3 = ABS(motor->SetSpeedRange) ; 
						}
						break;
		case 1: motor->SetSpeedRange = speed;
						motor->SetDirection =  motor->SetSpeedRange >= 0 ? 0 : 1;  //判断方向
						if(!motor->SetDirection) //正向
						{
							HAL_GPIO_WritePin(MOTORB_IN1_GPIO_Port, MOTORB_IN1_Pin, 0);
							HAL_GPIO_WritePin(MOTORB_IN2_GPIO_Port, MOTORB_IN2_Pin, 1);
							TIM4->CCR4 = ABS(motor->SetSpeedRange) ; 
						}
					else if(motor->SetDirection) //反向
					{
							HAL_GPIO_WritePin(MOTORB_IN1_GPIO_Port, MOTORB_IN1_Pin, 1);
							HAL_GPIO_WritePin(MOTORB_IN2_GPIO_Port, MOTORB_IN2_Pin,  0);
							TIM4->CCR4 = ABS(motor->SetSpeedRange) ; 
					
					}
						break;
	}
					

}
