# 星落梦科技-星枢
```c
  作者：星橙极客  最后更新时间 2023 - 6 - 28
		
		IO口映射表
UART1    Rx——PA10，Tx——PA9； MOTORA:IN1——TIME2_CH4，IN2——TIME2_CH3；																									ADC1:PC4；
UART2	 Rx——PD6，Tx——PD5；MOTORB:IN1——TIME3_CH4，IN2——TIME3_CH3；																										ADC2:PC5；
UART3	Rx——PD9，Tx——PD8；MOTORC:	IN1——TIME4_CH4，IN2——TIME4_CH3；																				BUZZER(TIM12):PB14；

UART4	Rx——PC11，Tx——PC10；	MOTORD:	IN1——TIME5_CH4，IN2——TIME5_CH3；																				RGB:R——PC13，G——PC14，B——PC15；
UART5	Rx——PD2，Tx——PD12；	IIC1(MPU6050)	SDA——PB7，SCL——PB6；											

UART6	Rx——PC7，Tx——PC6；	
 SPI1(ST7735S, W25Q32):   MOSI——PB5，MISO——PB4，SCK——PA5，FLASH（W35Q32）——PA4，TFT（ST7735s）——PE2；        
 SPI2:MOSI——PC3，MISO——PC2，mcu_cs——PB12，SCK——PB13；         

UART1暂时定义为打印表   输入ts 显示时间占用信息
					 输入ls 显示任务堆栈信息
支持TRACERECORDER功能（未启用）
格式规范： 规定变量采用大驼峰命名法 如 Uart1Rx
							规定函数采用下划线命名法 如 Servo_Diver
							规定结构体采用全大写     如MOTOR
							变量全部定义在需要的进程C文件中 不需要外部调用的请用 static关键字  需要外部调用的需要注意命名位置 外部采用 extern关键字
```
