#ifndef __MPU6050_H
#define __MPU6050_H

#include  "main.h"
#include  "i2c.h"

#define  MPU6050_Write_Addr           0xd0     //默认状态 地址为0X69 只有六位数据 使用IC7位寻址  ，第七位根据MPU6050引脚AD0在判断  AD0=0 第七位0  AD0=1 第七位1   第八位I2C读1 写0  我这里使用AD0=0低电平
#define  MPU6050_Read_Addr            0xd1
#define  MPU_Out_Fre_DIV_Addr         0x19      //采样频率地址   默认8Khz  如果开了低通滤波器 则变为1Khz
#define  MPU_Dlpf_Addr                0x1A		//低通滤波器地址 
#define  MPU_Gyro_Addr			      0x1B		//陀螺仪数据地址    第八七六位  XYZ轴自检给1  不自检给0  第五四两位 用于给陀螺仪量程范围  00-0~250  01-0~500 10-0~1000  11-0~2000  其余位0
#define  MPU_Accel_Addr               0x1C		//加速计数据地址    第八七六位  XYZ轴自检给1  不自检给0  第五四两位 用于给陀螺仪量程范围  00-±2G   01-±4G 	10-±8G  	 11-±16G 其余位0
#define  MPU_Id_Addr                  0x75      //MPU ID的地址
#define  MPU_Int_Addr				  0X38		//mpu中断使能地址
#define  MPU_User_Addr				  0x6A      //MPU用户控制地址  用于控制FIFO  I2C主模式
#define  MPU_Fifo_En_Addr			  0x23		//MPU的FIFO使能地址
#define  MPU_Int_Pin_Addr			  0x37      //INT中断地址
#define  PowerMem_Register1_Addr      0x6B		//电源管理1的地址
#define  PowerMem_Register2_Addr      0x6C		//电源管理2的地址





#define  Set_PowerMen_Reset           0x80		//在电源管理 输入 这个数据 为MPU 复位
#define  Set_PowerMen_Start_XPPL	  0x01      //在电源管理 输入 这个数据 为MPU唤醒 且使用X轴的时钟源
#define  Set_Smplrt_Div				  0x00      //采样分频
#define  Set_Dlpf_Div				  0x00      //低通滤波器模式
#define  Set_Gyro_Range               0x11      //设置陀螺仪的量程范围
#define  Set_Accel_Range              0x00      //设置加速计的量程范围
#define  Set_Int_Enable				  0x00      //设置关闭全部中断
#define  Set_User_I2c				  0x00		//禁止FIFO  I2C主模式
#define  Set_Fifo_Enable			  0x00      //禁止FIFO模式
#define  Set_Int_Pin_L				  0x80      //INT脚低电平有效
#define  Sat_Start_Mpu				  0x00		//设置启动MPU陀螺仪

//加速度计 数据寄存器地址
#define ACCEL_Xout_H				  0x3B
#define ACCEL_Xout_L				  0x3C
#define ACCEL_Yout_H				  0x3D
#define ACCEL_Yout_L  				  0x3E
#define ACCEL_Zout_H				  0x3F
#define ACCEL_Zout_L				  0x40

//陀螺仪  数据寄存器地址
#define GYRO_Xout_H					  0x43
#define GYRO_Xout_L					  0x44
#define GYRO_Yout_H				      0x45
#define GYRO_Yout_L					  0x46
#define GYRO_Zout_H					  0x47
#define GYRO_Zout_L					  0x48


extern signed short ax;
extern signed short ay;
extern signed short az;

extern signed short gx;
extern signed short gy;
extern signed short gz;

extern signed short ax_l;
extern signed short ay_l;
extern signed short az_l;

extern signed short gx_l;
extern signed short gy_l;
extern signed short gz_l;

void I2C_Write(unsigned char dev_addr,unsigned char mem_addr , unsigned char data);
void I2C_Read(unsigned char dev_addr,unsigned char mem_addr , unsigned char *buf,unsigned char len);
void MPU_Set_LPF(uint16_t lpf);
void Set_Mpu_Rate(uint16_t rata);
void MPU_6050_Init(void);
void Read_Mpu_Gyro(void);
void Read_Mpu_Accel(void);
void MPU6050_calibrate(void);
#endif