#include "simplepid.h"
//¶¨ÒåÒ»¸ö½á¹¹Ìå±äÁ
tPid speed_left;
tPid speed_right;
tPid angel;
tPid position;
//¸ø½á¹¹Ìå±äÁ¿¸ºÖµ
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
º¯Êı¹¦ÄÜ£ºÎ»ÖÃÊ½PID¿ØÖÆÆ÷
Èë¿Ú²ÎÊı£º±àÂëÆ÷²âÁ¿Î»ÖÃĞÅÏ¢£¬Ä¿±êÎ»ÖÃ
·µ»Ø  Öµ£ºµç»úPWM
¸ù¾İÎ»ÖÃÊ½ÀëÉ¢PID¹«Ê½ 
pwm=Kp*e(k)+Ki*¡Æe(k)+Kd[e£¨k£©-e(k-1)]
e(k)´ú±í±¾´ÎÆ«²î 
e(k-1)´ú±íÉÏÒ»´ÎµÄÆ«²î  
¡Æe(k)´ú±íe(k)ÒÔ¼°Ö®Ç°µÄÆ«²îµÄÀÛ»ıºÍ;ÆäÖĞkÎª1,2,,k;
pwm´ú±íÊä³ö
**************************************************************************/
int Position_PID (tPid *pid,int target)
{ 	
	 static float Moto;
	 pid->err=pid->target_val-pid->actual_val;                                  //¼ÆËãÆ«²î
	 pid->err_sum+=pid->err;	                                 //Çó³öÆ«²îµÄ»ı·Ö
	 Moto=pid->kp*pid->err/100+pid->ki*pid->err_sum/100+pid->kd*(pid->err-pid->err_last)/100;       //Î»ÖÃÊ½PID¿ØÖÆÆ÷
	 pid->err_last=pid->err;                                       //±£´æÉÏÒ»´ÎÆ«²î 
	 return Moto;                                           //ÔöÁ¿Êä³ö
}

