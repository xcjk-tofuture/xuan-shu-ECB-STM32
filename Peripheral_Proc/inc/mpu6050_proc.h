#ifndef __MPU6050_PROC_H
#define __MPU6050_PROC_H




#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "sys.h"
#include "i2c.h"
#include "IIC.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "vector3.h"
typedef struct  
{
 float pitch;
 float roll;
 float yaw;
	
	short gx;
	short gy;
	short gz;
	
	short gyrox;
	short gyroy;
	short gyroz;
	
	float Mechanical_Angle;
}My_Pos;

typedef struct  
{
	u32 timestamp;	/*时间戳*/

	float roll;
	float pitch;
	float yaw;
} attitude_t;

struct  vec3_s 
{
	u32 timestamp;	/*时间戳*/

	float x;
	float y;
	float z;
};

typedef struct vec3_s point_t;
typedef struct vec3_s velocity_t;
typedef struct vec3_s acc_t;


typedef struct
{
	attitude_t attitude;
	point_t position;
	velocity_t velocity;
	acc_t acc;
} state_t;


void imuUpdate(Vector3f_t acc, Vector3f_t gyro, state_t *state , float dt);

#endif