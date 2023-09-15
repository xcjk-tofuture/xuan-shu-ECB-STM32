#include "sbus_proc.h"




osThreadId SbusTaskHandle;
u16 SbusChannels[16];

extern u8 Uart6Rx[MAX_UART_RX_NUM];
extern u8 Uart6Tx[MAX_UART_TX_NUM];

//串口对于的是usart6  对应的缓冲数组为 Uart6_Rx, Uart6_Tx  
typedef struct
{
		uint16_t CH1;//通道1数值
		uint16_t CH2;//通道2数值
		uint16_t CH3;//通道3数值
		uint16_t CH4;//通道4数值
		uint16_t CH5;//通道5数值
		uint16_t CH6;//通道6数值
    uint16_t CH7;//通道7数值
    uint16_t CH8;//通道8数值
    uint16_t CH9;//通道9数值
    uint16_t CH10;//通道10数值
    uint16_t CH11;//通道11数值
    uint16_t CH12;//通道12数值
    uint16_t CH13;//通道13数值
    uint16_t CH14;//通道14数值
    uint16_t CH15;//通道15数值
    uint16_t CH16;//通道16数值
	uint8_t ConnectState;//遥控器与接收器连接状态 0=未连接，1=正常连接
}SBUS_CH_Struct;

SBUS_CH_Struct SBUS_CH;

void Sbus_Task_Proc(void const * argument)
{

	
  for(;;)
  {
//	printf("channel_1: %.0f \r\n", Sbus_To_Range(SBUS_CH.CH1, 50, 100));
//	printf("channel_2: %.0f \r\n", Sbus_To_Range(SBUS_CH.CH2, 50, 100));
//	printf("channel_3: %.0f \r\n", Sbus_To_Range(SBUS_CH.CH3, 50, 100));
//	printf("channel_4: %.0f \r\n", Sbus_To_Range(SBUS_CH.CH4, 50, 100));
//	printf("channel_5:%d\r\n", SBUS_CH.CH5);
//	printf("channel_6:%d\r\n", SBUS_CH.CH6);		
//	printf("channel_7:%d\r\n", SBUS_CH.CH7);
//	printf("channel_8:%d\r\n", SBUS_CH.CH8);				
//	printf("ConnectState: %d\r\n", SBUS_CH.ConnectState);
    osDelay(1000);
  }

}



//下面是驱动





void Sbus_Uart6_IDLE_Proc(uint16_t Size)
{
	
	if(Size == 25 && Uart6Rx[0] == 0x0f &&  Uart6Rx[24] == 0x00)          //效验
	{
		Sbus_Channels_Proc();
		if(Uart6Rx[23] == 0)
		{
				SBUS_CH.ConnectState = 1; //遥控器打开
		}
		else
		{
				SBUS_CH.ConnectState = 0; //遥控器关闭
		}

	}

}

void Sbus_Channels_Proc(void)          //解析sbus函数
{
    SbusChannels[0]  = ((Uart6Rx[1]|Uart6Rx[2]<<8)           & 0x07FF);
    SbusChannels[1]  = ((Uart6Rx[2]>>3 |Uart6Rx[3]<<5)                 & 0x07FF);
    SbusChannels[2]  = ((Uart6Rx[3]>>6 |Uart6Rx[4]<<2 |Uart6Rx[5]<<10)  & 0x07FF);
    SbusChannels[3]  = ((Uart6Rx[5]>>1 |Uart6Rx[6]<<7)                 & 0x07FF);
    SbusChannels[4]  = ((Uart6Rx[6]>>4 |Uart6Rx[7]<<4)                 & 0x07FF);
    SbusChannels[5]  = ((Uart6Rx[7]>>7 |Uart6Rx[8]<<1 |Uart6Rx[9]<<9)   & 0x07FF);
    SbusChannels[6]  = ((Uart6Rx[9]>>2 |Uart6Rx[10]<<6)                & 0x07FF);
    SbusChannels[7]  = ((Uart6Rx[10]>>5|Uart6Rx[11]<<3)                & 0x07FF);
    SbusChannels[8]  = ((Uart6Rx[12]   |Uart6Rx[13]<<8)                & 0x07FF);
    SbusChannels[9]  = ((Uart6Rx[13]>>3|Uart6Rx[14]<<5)                & 0x07FF);
    SbusChannels[10] = ((Uart6Rx[14]>>6|Uart6Rx[15]<<2|Uart6Rx[16]<<10) & 0x07FF);
    SbusChannels[11] = ((Uart6Rx[16]>>1|Uart6Rx[17]<<7)                & 0x07FF);
    SbusChannels[12] = ((Uart6Rx[17]>>4|Uart6Rx[18]<<4)                & 0x07FF);
    SbusChannels[13] = ((Uart6Rx[18]>>7|Uart6Rx[19]<<1|Uart6Rx[20]<<9)  & 0x07FF);
    SbusChannels[14] = ((Uart6Rx[20]>>2|Uart6Rx[21]<<6)                & 0x07FF);
    SbusChannels[15] = ((Uart6Rx[21]>>5|Uart6Rx[22]<<3)                & 0x07FF);
	
		SBUS_CH.CH1 = SbusChannels[0];
		SBUS_CH.CH2 = SbusChannels[1];
		SBUS_CH.CH3 = SbusChannels[2];
		SBUS_CH.CH4 = SbusChannels[3];
		SBUS_CH.CH5 = SbusChannels[4];
		SBUS_CH.CH6 = SbusChannels[5];
		SBUS_CH.CH7 = SbusChannels[6];
		SBUS_CH.CH8 = SbusChannels[7];
		SBUS_CH.CH9 = SbusChannels[8];
		SBUS_CH.CH10 = SbusChannels[9];
		SBUS_CH.CH11 = SbusChannels[10];
		SBUS_CH.CH12 = SbusChannels[11];
		SBUS_CH.CH13 = SbusChannels[12];
		SBUS_CH.CH14 = SbusChannels[13];
		SBUS_CH.CH15 = SbusChannels[14];
		SBUS_CH.CH16 = SbusChannels[15];
		

}

//u16 Sbus_To_Pwm(u16 sbus_value)
//{
//    float pwm;
//    pwm = (float)SBUS_TARGET_MIN + (float)(sbus_value - SBUS_RANGE_MIN) * SBUS_SCALE_FACTOR;
//    //                1000                                   300              1000/1400
//    if (pwm > 2000) pwm = 2000;
//    if (pwm < 1000) pwm = 1000;
//    return (u16)pwm;
//}
//将sbus信号通道值转化为特定区间的数值  [p_min,p_max] 
float Sbus_To_Range(u16 sbus_value, float p_min, float p_max)
{
    float p;
    p = p_min + (float)(sbus_value - SBUS_RANGE_MIN) * (p_max-p_min)/(float)(SBUS_RANGE_MAX - SBUS_RANGE_MIN);  
    if (p > p_max) p = p_max;
    if (p < p_min) p = p_min;
    return p;
}