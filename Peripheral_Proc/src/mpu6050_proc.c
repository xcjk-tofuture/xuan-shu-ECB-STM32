#include "mpu6050_proc.h"
#include "vector3.h"

osThreadId MPU6050TaskHandle;

My_Pos CarPos;
state_t State;		/*姿态*/
Vector3f_t CarAcc;
Vector3f_t CarGryo;
void MPU6050_Task_Proc()
{
//	if(MPU_Init() == 0)			//MPU6050初始化
//			printf("iic mpu6050 ok\r\n");
//	else
//			printf("iic mpu6050 error\r\n");
 // mpu_dmp_init();		//dmp初始化
	//printf("------**********------------------\r\n");
	MPU_6050_Init();
	//MPU6050_calibrate();
	osDelay(1000);	
 u16 count = 0;
	for(;;)
	{
//		mpu_dmp_get_data(&(CarPos.pitch),&(CarPos.roll),&(CarPos.yaw)); //Dmp算法计算三个角度
//		if(MPU_Get_Accelerometer(&(CarPos.gx),&(CarPos.gy),&(CarPos.gz)) == 0)
	//	printf("----------------------------------\r\n");	
	//	HAL_Delay(500);
		count ++;
		Read_Mpu_Gyro();
		Read_Mpu_Accel();		
		//printf("ax:%1.3f g,\tgx:%f deg/s\r\n",(float)ax/(0xffff/4),(float)gx/(0xffff/500));  //输出加速度计和陀螺仪的初始数据  
		//printf("ay:%1.3f g,\tgx:%f deg/s\r\n",(float)ay/(0xffff/4),(float)gy/(0xffff/500));  //输出加速度计和陀螺仪的初始数据  
		//printf("az:%1.3f g,\tgx:%f deg/s\r\n",(float)az/(0xffff/4),(float)gz/(0xffff/500));  //输出加速度计和陀螺仪的初始数据  
		CarAcc.x = (float)ax/(0xffff/4);
		CarAcc.y = (float)ay/(0xffff/4);
		CarAcc.z = (float)az/(0xffff/4);
		
		CarGryo.x = (float)gx/(0xffff/500);
		CarGryo.y = (float)gy/(0xffff/500);
		CarGryo.z = (float)gz/(0xffff/500);
		imuUpdate(CarAcc, CarGryo, &State, 0.01);
		osDelay(100);	
		if (count % 10 == 0 )
		{
			printf("Pitch:&.2f, Roll :%.2f Yaw: %.2f", State.attitude.pitch, State.attitude.roll, State.attitude.yaw);
		}
	}
}




#define DEG2RAD		0.017453293f	/* 度转弧度 π/180 */
#define RAD2DEG		57.29578f		/* 弧度转度 180/π */


float Kp = 3;		/*比例增益*/
float Ki = 0.0001;		/*积分增益*/
float exInt = 0.0f;
float eyInt = 0.0f;
float ezInt = 0.0f;		/*积分误差累计*/

static float q0 = 1.0f;	/*四元数*/
static float q1 = 0.0f;
static float q2 = 0.0f;
static float q3 = 0.0f;	

static float baseZacc = 1.0;		/*静态Z轴加速度*/
static bool isCalibrated = false;


static float invSqrt(float x);	/*快速开平方求倒*/

void imuUpdate(Vector3f_t acc, Vector3f_t gyro, state_t *state , float dt)	/*数据融合 互补滤波*/
{
	float normalise;
	float ex, ey, ez;
	float q0s, q1s, q2s, q3s;	/*四元数的平方*/
	static float R11,R21;		/*矩阵(1,1),(2,1)项*/
	static float vecxZ, vecyZ, veczZ;	/*机体坐标系下的Z方向向量*/
	float halfT =0.5f * dt;
	Vector3f_t tempacc =acc;

	gyro.x = gyro.x * DEG2RAD;	/* 度转弧度 */
	gyro.y = gyro.y * DEG2RAD;
	gyro.z = gyro.z * DEG2RAD;

	/* 某一个方向加速度不为0 */
	if((acc.x != 0.0f) || (acc.y != 0.0f) || (acc.z != 0.0f))
	{
		/*单位化加速计测量值*/
		normalise = invSqrt(acc.x * acc.x + acc.y * acc.y + acc.z * acc.z);
		acc.x *= normalise;
		acc.y *= normalise;
		acc.z *= normalise;

		/*加速计读取的方向与重力加速计方向的差值，用向量叉乘计算*/
		ex = (acc.y * veczZ - acc.z * vecyZ);
		ey = (acc.z * vecxZ - acc.x * veczZ);
		ez = (acc.x * vecyZ - acc.y * vecxZ);
		
		/*误差累计，与积分常数相乘*/
		exInt += Ki * ex * dt ;  
		eyInt += Ki * ey * dt ;
		ezInt += Ki * ez * dt ;
		
		/*用叉积误差来做PI修正陀螺零偏，即抵消陀螺读数中的偏移量*/
		gyro.x += Kp * ex + exInt;
		gyro.y += Kp * ey + eyInt;
		gyro.z += Kp * ez + ezInt;
	}
	/* 一阶近似算法，四元数运动学方程的离散化形式和积分 */
	q0 += (-q1 * gyro.x - q2 * gyro.y - q3 * gyro.z) * halfT;
	q1 += (q0 * gyro.x + q2 * gyro.z - q3 * gyro.y) * halfT;
	q2 += (q0 * gyro.y - q1 * gyro.z + q3 * gyro.x) * halfT;
	q3 += (q0 * gyro.z + q1 * gyro.y - q2 * gyro.x) * halfT;
	
	/*单位化四元数*/
	normalise = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= normalise;
	q1 *= normalise;
	q2 *= normalise;
	q3 *= normalise;
	/*四元数的平方*/
	q0s = q0 * q0;
	q1s = q1 * q1;
	q2s = q2 * q2;
	q3s = q3 * q3;
	
	R11 = q0s + q1s - q2s - q3s;	/*矩阵(1,1)项*/
	R21 = 2 * (q1 * q2 + q0 * q3);	/*矩阵(2,1)项*/

	/*机体坐标系下的Z方向向量*/
	vecxZ = 2 * (q1 * q3 - q0 * q2);/*矩阵(3,1)项*/
	vecyZ = 2 * (q0 * q1 + q2 * q3);/*矩阵(3,2)项*/
	veczZ = q0s - q1s - q2s + q3s;	/*矩阵(3,3)项*/
	
	if (vecxZ>1) vecxZ=1;
	if (vecxZ<-1) vecxZ=-1;
	
	/*计算roll pitch yaw 欧拉角*/
	state->attitude.pitch = -asinf(vecxZ) * RAD2DEG; 
	state->attitude.roll = atan2f(vecyZ, veczZ) * RAD2DEG;
	state->attitude.yaw = atan2f(R21, R11) * RAD2DEG;
	
	if (!isCalibrated)	/*校准*/
	{
		baseZacc = tempacc.x* vecxZ + tempacc.y * vecyZ + tempacc.z * veczZ;
		isCalibrated = true;
	}
	state->acc.z= tempacc.x* vecxZ + tempacc.y * vecyZ + tempacc.z * veczZ - baseZacc;	/*Z轴加速度(去除重力加速度)*/
}

// Fast inverse square-root
// See: http://en.wikipedia.org/wiki/Fast_inverse_square_root
float invSqrt(float x)	/*快速开平方求倒*/
{
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}
