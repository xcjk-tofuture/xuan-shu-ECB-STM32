#include "lcd_proc.h"
#include "lcd_init.h"
#include "lcdfont.h"
#include "lcdimage.h"
#include "motor_proc.h"
#include "delay.h"
#include "mpu6050_proc.h"

extern MOTOR MotorA, MotorB;  //编号对应 2 3
extern My_Pos CarPos;

u8 LcdDisp[40];

u8 LcdPage = 1;

osThreadId LCDTaskHandle;


void LCD_Task_Proc(void const * argument)
{
  /* USER CODE BEGIN LCD_Task_Proc */
  /* Infinite loop */
	LCD_Init();//LCD初始化
	LCD_Image(0, 0, 128,160, startup);
	osDelay(200);
	LCD_Clear(BLACK);
  for(;;)
  {
		LCD_Chinese16ForFile(10,0,0, LIGHTBLUE, BLACK); //标题  星
		LCD_Chinese16ForFile(10 + 18,0,1, LIGHTBLUE, BLACK); //标题  枢
		LCD_ShowString(10 + 36,0,"V1.0 RTOS",YELLOW,BLACK,16,0);
		sprintf(LcdDisp,"TIME:%d", uwTick/1000);
		LCD_ShowString(0,160 - 16, LcdDisp,WHITE,BLACK,16,0);
		sprintf(LcdDisp,"PAGE:%d", LcdPage);
		LCD_ShowString(80,160 - 16, LcdDisp,WHITE,BLACK,16,0);
		
		//PAGE 1
		if(LcdPage == 1)
		{
		sprintf(LcdDisp,"MOTOR"); //电机显示页面
		LCD_ShowString(50,16 , LcdDisp,YELLOW,BLACK,16,0);	 
			
		sprintf(LcdDisp,"MOTORA:speed:%0.2fCM/S   ",MotorA.Speed);    //电机A
		LCD_ShowString(0,16 + 16, LcdDisp,WHITE,BLACK,12,0);
			
		sprintf(LcdDisp,"speedrange:%d  ",MotorA.SetSpeedRange);    //电机A
		LCD_ShowString(0,16 + 16 + 12, LcdDisp,WHITE,BLACK,12,0);	
			
			
		sprintf(LcdDisp,"MOTORB:speed:%0.2fCM/S   ",MotorB.Speed);
		LCD_ShowString(0,16 + 16 + 2 * 12, LcdDisp,WHITE,BLACK,12,0);	  //电机B
			
		sprintf(LcdDisp,"speedrange:%d  ",MotorB.SetSpeedRange);    //电机b
		LCD_ShowString(0,16 + 16 + 3 * 12, LcdDisp,WHITE,BLACK,12,0);
		

		
		}
		
		if(LcdPage == 2)
		{
		sprintf(LcdDisp,"SERVO"); //舵机显示页面
		LCD_ShowString(50,16 , LcdDisp,YELLOW,BLACK,16,0);	 
			
		sprintf(LcdDisp,"PWM1:D:%0.2f       ",(float)TIM1->CCR1/TIM1->ARR);    //舵机1
		LCD_ShowString(0,16 + 16, LcdDisp,WHITE,BLACK,12,0);
			
		sprintf(LcdDisp,"PWM2:D:%0.2f       ",(float)TIM1->CCR2/TIM1->ARR);    //舵机2
		LCD_ShowString(0,16 + 16 + 12, LcdDisp,WHITE,BLACK,12,0);	
			
			
		sprintf(LcdDisp,"PWM3:D:%0.2f       ",(float)TIM1->CCR3 / TIM1->ARR);
		LCD_ShowString(0,16 + 16 + 2 * 12, LcdDisp,WHITE,BLACK,12,0);	  //舵机3
			
		sprintf(LcdDisp,"PWM4:D:%0.2f       ",(float)TIM1->CCR4 / TIM1->ARR);    //舵机4
		LCD_ShowString(0,16 + 16 + 3 * 12, LcdDisp,WHITE,BLACK,12,0);
		

		sprintf(LcdDisp,"PWM5:D:%0.2f       ",(float)TIM8->CCR3 / TIM8->ARR);
		LCD_ShowString(0,16 + 16 + 4 * 12, LcdDisp,WHITE,BLACK,12,0);	  //舵机5
			
		sprintf(LcdDisp,"PWM6:D:%0.2f       ",(float)TIM8->CCR4 / TIM8->ARR);    //舵机6
		LCD_ShowString(0,16 + 16 + 5 * 12, LcdDisp,WHITE,BLACK,12,0);	
			
			
		sprintf(LcdDisp,"PWM7:D:%0.2f       ",(float)TIM10->CCR1 / TIM10->ARR);				//舵机7
		LCD_ShowString(0,16 + 16 + 6 * 12, LcdDisp,WHITE,BLACK,12,0);	
		
		sprintf(LcdDisp,"PWM8:D:%0.2f       ",(float)TIM11->CCR1 / TIM11->ARR);    //舵机8
		LCD_ShowString(0,16 + 16 + 7 * 12, LcdDisp,WHITE,BLACK,12,0);
		
		}
		
		if(LcdPage == 3)
		{
		sprintf(LcdDisp,"MPU6050"); //MPU6050显示页面
		LCD_ShowString(50,16 , LcdDisp,YELLOW,BLACK,16,0);	 
			
		sprintf(LcdDisp,"GX:%d            ",CarPos.gx);    //X加速度
		LCD_ShowString(0,16 + 16, LcdDisp,WHITE,BLACK,12,0);
			
		sprintf(LcdDisp,"GY:%d            ",CarPos.gy);    //Y加速度
		LCD_ShowString(0,16 + 16 + 12, LcdDisp,WHITE,BLACK,12,0);	
			
			
		sprintf(LcdDisp,"GZ:%d            ",CarPos.gz);		 //Z加速度
		LCD_ShowString(0,16 + 16 + 2 * 12, LcdDisp,WHITE,BLACK,12,0);	  
			
		sprintf(LcdDisp,"pitch:%0.2f        ",CarPos.pitch);  //俯仰角
		LCD_ShowString(0,16 + 16 + 3 * 12, LcdDisp,WHITE,BLACK,12,0);
		

		sprintf(LcdDisp," roll:%0.2f        ",CarPos.roll);  //翻滚角
		LCD_ShowString(0,16 + 16 + 4 * 12, LcdDisp,WHITE,BLACK,12,0);	  
			
		sprintf(LcdDisp,"  yaw:%0.2f       ", CarPos.yaw);    //偏航角
		LCD_ShowString(0,16 + 16 + 5 * 12, LcdDisp,WHITE,BLACK,12,0);	
			
		}
		

		
		
    osDelay(100);
  }
  /* USER CODE END LCD_Task_Proc */
}






void LCD_Image(u16 x, u16 y, u16 width, u16 height, const u8 *image) 
{  
	
	u16 colorData=0;
	u32 cnt=0;
	
 	for(u16 i=0; i<height; i++)                // 一行一行地显示
	{
 		LCD_Address_Set(x, y+i, x+width, y+height);  // 重新设置光标位置 
		for(u16 j=0; j<width; j++)             // 一行中，从左到事，逐个像素处理
		{		    
		    colorData=(image[cnt*2+1]<<8) | image[cnt*2]; 
		    LCD_WR_DATA(colorData);              // 写入16位颜色数据 
			cnt++;	
		}
	}	  
} 




//清屏函数

void LCD_Clear(u16 color)
{

LCD_Fill(0,0,LCD_W,LCD_H,color);

}



/******************************************************************
 * 函数名： LCD_Chinese16ForFile
 * 功  能： 显示1个16号汉字,字库数据在font文件中，只适合少量汉字固定输出
 *          PCtoLCD2002取模：阴码+逐列式+顺向+C51格式
 * 参  数： u16 x,y     左上角起始坐标
 *          u8  index   字库数据在缓存中的位置
 *          u32 fColor  字色
 *          u32 bColor  底色
 *****************************************************************/
void LCD_Chinese16ForFile(u32 x, u32 y, u8 index, u16 fColor, u16 bColor)	
{  
	
	
	const u8 *temp=hanzi16 + index*32;              // 获取字体数据在数组中的的起始位置 

	for(u8 j=0;j<16;j++)
	{
		LCD_Address_Set(x,y+j ,x+16, y+j+16);
		for(u8 k=0;k<2;k++)
		{
			for(u8 i=0;i<8;i++)
			{ 		     
			 	if((*temp&(1<<i))!=0)			
					LCD_WR_DATA(fColor);				
				else			
					LCD_WR_DATA(bColor);				 
			}
			temp++;
		}
	 }
}	

/******************************************************************
 * 函数名： LCD_Chinese32ForFile
 * 功  能： 显示1个32号汉字,字库数据在font文件中，只适合少量汉字固定输出
 *          PCtoLCD2002取模：阴码+逐列式+顺向+C51格式
 * 参  数： u16 x,y     左上角起始坐标
 *          u8  index   字库数据在缓存中的位置
 *          u32 fColor  字体颜色
 *          u32 bColor  背景颜色
 *****************************************************************/
void LCD_Chinese32ForFile(u32 x, u32 y, u8 index, u16 fColor, u16 bColor)	
{ 
	
	
	const u8 *temp = hanzi32 + index*128;       // 获取字体数据在数组中的的起始位置 

	for(u8 j=0; j<32; j++)                      // 一行一行地向下写
	{
		LCD_Address_Set(x,y+j,x+32, y+j+32);          // 只要定位了首个坐标，后面发送的数据，就会向后排列，直至收到新的命令
		for(u8 k=0;k<4;k++)
		{
			for(u8 i=0;i<8;i++)
			{ 		     
			 	if((*temp&(1<<i))!=0)				
					LCD_WR_DATA(fColor);				
				else
					LCD_WR_DATA(bColor);				 
			}
			temp++;
		}
	 }
}	


/******************************************************************************
      函数说明：在指定区域填充颜色
      入口数据：xsta,ysta   起始坐标
                xend,yend   终止坐标
								color       要填充的颜色
      返回值：  无
******************************************************************************/
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{          
	u16 i,j; 
	LCD_Address_Set(xsta,ysta,xend-1,yend-1);//设置显示范围
	for(i=ysta;i<yend;i++)
	{													   	 	
		for(j=xsta;j<xend;j++)
		{
			LCD_WR_DATA(color);
		}
	} 					  	    
}

/******************************************************************************
      函数说明：在指定位置画点
      入口数据：x,y 画点坐标
                color 点的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawPoint(u16 x,u16 y,u16 color)
{
	LCD_Address_Set(x,y,x,y);//设置光标位置 
	LCD_WR_DATA(color);
} 


/******************************************************************************
      函数说明：画线
      入口数据：x1,y1   起始坐标
                x2,y2   终止坐标
                color   线的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1;
	uRow=x1;//画线起点坐标
	uCol=y1;
	if(delta_x>0)incx=1; //设置单步方向 
	else if (delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if (delta_y==0)incy=0;//水平线 
	else {incy=-1;delta_y=-delta_y;}
	if(delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y;
	for(t=0;t<distance+1;t++)
	{
		LCD_DrawPoint(uRow,uCol,color);//画点
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}


/******************************************************************************
      函数说明：画矩形
      入口数据：x1,y1   起始坐标
                x2,y2   终止坐标
                color   矩形的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
	LCD_DrawLine(x1,y1,x2,y1,color);
	LCD_DrawLine(x1,y1,x1,y2,color);
	LCD_DrawLine(x1,y2,x2,y2,color);
	LCD_DrawLine(x2,y1,x2,y2,color);
}


/******************************************************************************
      函数说明：画圆
      入口数据：x0,y0   圆心坐标
                r       半径
                color   圆的颜色
      返回值：  无
******************************************************************************/
void Draw_Circle(u16 x0,u16 y0,u8 r,u16 color)
{
	int a,b;
	a=0;b=r;	  
	while(a<=b)
	{
		LCD_DrawPoint(x0-b,y0-a,color);             //3           
		LCD_DrawPoint(x0+b,y0-a,color);             //0           
		LCD_DrawPoint(x0-a,y0+b,color);             //1                
		LCD_DrawPoint(x0-a,y0-b,color);             //2             
		LCD_DrawPoint(x0+b,y0+a,color);             //4               
		LCD_DrawPoint(x0+a,y0-b,color);             //5
		LCD_DrawPoint(x0+a,y0+b,color);             //6 
		LCD_DrawPoint(x0-b,y0+a,color);             //7
		a++;
		if((a*a+b*b)>(r*r))//判断要画的点是否过远
		{
			b--;
		}
	}
}


/******************************************************************************
      函数说明：显示单个字符
      入口数据：x,y显示坐标
                num 要显示的字符
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChar(u16 x,u16 y,u8 num,u16 fc,u16 bc,u8 sizey,u8 mode)
{
	u8 temp,sizex,t,m=0;
	u16 i,TypefaceNum;//一个字符所占字节大小
	u16 x0=x;
	sizex=sizey/2;
	TypefaceNum=(sizex/8+((sizex%8)?1:0))*sizey;
	num=num-' ';    //得到偏移后的值
	LCD_Address_Set(x,y,x+sizex-1,y+sizey-1);  //设置光标位置 
	for(i=0;i<TypefaceNum;i++)
	{ 
		if(sizey==12)temp=ascii_1206[num][i];		       //调用6x12字体
		else if(sizey==16)temp=ascii_1608[num][i];		 //调用8x16字体
		else if(sizey==24)temp=ascii_2412[num][i];		 //调用12x24字体
		else if(sizey==32)temp=ascii_3216[num][i];		 //调用16x32字体
		else return;
		for(t=0;t<8;t++)
		{
			if(!mode)//非叠加模式
			{
				if(temp&(0x01<<t))LCD_WR_DATA(fc);
				else LCD_WR_DATA(bc);
				m++;
				if(m%sizex==0)
				{
					m=0;
					break;
				}
			}
			else//叠加模式
			{
				if(temp&(0x01<<t))LCD_DrawPoint(x,y,fc);//画一个点
				x++;
				if((x-x0)==sizex)
				{
					x=x0;
					y++;
					break;
				}
			}
		}
	}   	 	  
}








/******************************************************************************
      函数说明：显示字符串
      入口数据：x,y显示坐标
                *p 要显示的字符串
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowString(u16 x,u16 y,const u8 *p,u16 fc,u16 bc,u8 sizey,u8 mode)
{         
	while(*p!='\0')
	{       
		LCD_ShowChar(x,y,*p,fc,bc,sizey,mode);
		x+=sizey/2;
		p++;
	}  
}


/******************************************************************************
      函数说明：显示数字
      入口数据：m底数，n指数
      返回值：  无
******************************************************************************/
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;
	return result;
}


/******************************************************************************
      函数说明：显示整数变量
      入口数据：x,y显示坐标
                num 要显示整数变量
                len 要显示的位数
                fc 字的颜色
                bc 字的背景色
                sizey 字号
      返回值：  无
******************************************************************************/
void LCD_ShowIntNum(u16 x,u16 y,u16 num,u8 len,u16 fc,u16 bc,u8 sizey)
{         	
	u8 t,temp;
	u8 enshow=0;
	u8 sizex=sizey/2;
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
} 


/******************************************************************************
      函数说明：显示两位小数变量
      入口数据：x,y显示坐标
                num 要显示小数变量
                len 要显示的位数
                fc 字的颜色
                bc 字的背景色
                sizey 字号
      返回值：  无
******************************************************************************/
void LCD_ShowFloatNum1(u16 x,u16 y,float num,u8 len,u16 fc,u16 bc,u8 sizey)
{         	
	u8 t,temp,sizex;
	u16 num1;
	sizex=sizey/2;
	num1=num*100;
	for(t=0;t<len;t++)
	{
		temp=(num1/mypow(10,len-t-1))%10;
		if(t==(len-2))
		{
			LCD_ShowChar(x+(len-2)*sizex,y,'.',fc,bc,sizey,0);
			t++;
			len+=1;
		}
	 	LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
}



