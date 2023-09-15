#include "pc_proc.h"



//串口对于的是usart1  对应的缓冲数组为 Uart1_Rx, Uart1_Tx



osThreadId PCTaskHandle;
extern u8 TaskListFlag;
extern u8 RunTimeFlag;
extern char InfoBuffer[1000];
extern u8 Uart1Rx[MAX_UART_RX_NUM];
extern u8 Uart1Tx[MAX_UART_TX_NUM];

void PC_Task_Proc(void const * argument)
{
	for(; ;)
	{
 if(TaskListFlag)
 {
	 
	TaskListFlag = 0;
	memset(InfoBuffer,0,1000);	 
	vTaskList(InfoBuffer);
	printf("\r\n任务名称 运行状态 优先级 剩余堆栈 任务序号\r\n");
	printf("%s\r\n", InfoBuffer);
	printf("B : 阻塞, R : 就绪, D : 删除, S : 暂停\r\n"); 
 }
 if(RunTimeFlag)
 {
	RunTimeFlag = 0; 
	memset(InfoBuffer,0,1000);				//信息缓冲区清零
	vTaskGetRunTimeStats(InfoBuffer);		//获取任务运行时间信息
	printf("任务名\t\t\t运行时间\t运行所占百分比\r\n");
	printf("%s\r\n",InfoBuffer);

 }
	osDelay(10);
	}

}