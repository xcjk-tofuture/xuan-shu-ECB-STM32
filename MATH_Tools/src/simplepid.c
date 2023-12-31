#include "simplepid.h"
//定义一个结构体变�
tPid speed_left;
tPid speed_right;
tPid angel;
tPid position;
//给结构体变量负值
void PID_speedinit()
{
	speed_left.target_val = 100;
	speed_left.actual_val = 0.0;
	speed_left.err = 0.0;
	speed_left.err_last = 0.0;
	speed_left.err_sum = 0.0;
	speed_left.kp = 6.5;
	speed_left.ki = 0.2;
	speed_left.kd = 0;
	speed_right.target_val = 100;
	speed_right.actual_val = 0.0;
	speed_right.err = 0.0;
	speed_right.err_last = 0.0;
	speed_right.err_sum = 0.0;
	speed_right.kp = 6.5;
	speed_right.ki = 0.2;
	speed_right.kd = 0;
}


void PID_angelInit()
{
	angel.target_val = 0.0;
	angel.actual_val = 0.0;
	angel.err = 0.0;
	angel.err_last = 0.0;
	angel.err_sum = 0.0;
	angel.kp = 1.5;
	angel.ki = 0;
	angel.kd = 0;
}

void PID_positionInit()
{
	position.target_val = 0.0;
	position.actual_val = 0.0;
	position.err = 0.0;
	position.err_last = 0.0;
	position.err_sum = 0.0;
	position.kp = 2;
	position.ki = 0;
	position.kd = 4;
}



float P_realize(tPid * pid,float actual_val)
{
	pid->actual_val = actual_val;
	pid->err = pid->target_val - pid->actual_val;
	pid->actual_val = pid->kp*pid->err;
	return pid->actual_val;
}

float PI_realize(tPid * pid,float actual_val)
{
	pid->actual_val = actual_val;
	pid->err = pid->target_val - pid->actual_val;
	pid->err_sum += pid->err;
	
	pid->actual_val = pid->kp*pid->err + pid->ki*pid->err_sum;
	
	return pid->actual_val;
}



float PID_realize(tPid * pid,float actual_val)
{
	pid->actual_val = actual_val;
	pid->err = pid->target_val - pid->actual_val;
	pid->err_sum += pid->err;
	pid->actual_val = pid->kp*pid->err + pid->ki*pid->err_sum + pid->kd*(pid->err - pid->err_last);
	pid->err_last = pid->err;
	return pid->actual_val;
}
/**************************************************************************
函数功能：位置式PID控制器
入口参数：编码器测量位置信息，目标位置
返回  值：电机PWM
根据位置式离散PID公式 
pwm=Kp*e(k)+Ki*∑e(k)+Kd[e（k）-e(k-1)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,,k;
pwm代表输出
**************************************************************************/
int Position_PID (tPid *pid,int target)
{ 	
	 static float Moto;
	 pid->err=pid->target_val-pid->actual_val;                                  //计算偏差
	 pid->err_sum+=pid->err;	                                 //求出偏差的积分
	 Moto=pid->kp*pid->err/100+pid->ki*pid->err_sum/100+pid->kd*(pid->err-pid->err_last)/100;       //位置式PID控制器
	 pid->err_last=pid->err;                                       //保存上一次偏差 
	 return Moto;                                           //增量输出
}

