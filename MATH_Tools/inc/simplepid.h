#ifndef __PID_H
#define __PID_H

//声明一个结构体类型
typedef struct
{
	float target_val;//目标值
	float actual_val;//实际值
	float err;//当前偏差
	float err_last;//上次偏差
	float err_sum;//历史累计偏差
	float kp,ki,kd;//比例，积分，微分系数
} tPid;

float P_realize(tPid * pid,float actual_val);
void PID_speedinit(void);
void PID_angelInit();
void PID_positionInit();
float PI_realize(tPid * pid,float actual_val);
float PID_realize(tPid * pid,float actual_val);
int Position_PID (tPid *pid,int target);


#endif

