#include "key_proc.h"
#include "lcd_proc.h"


extern u8 LcdPage;

osThreadId KeyTaskHandle;


u8 KeyVal, KeyOld, KeyUp, KeyDown;

//	KEYµÄÃ¶¾Ù
enum Key
{
	Up = 1,
	Right,
	Down,
	Left,
	Center
}key;

void Key_Task_Proc(void const * argument)
{
	
	for(;;)
	{
	KeyVal = Key_Scan();
	KeyDown = KeyVal & (KeyVal ^ KeyOld);
	KeyUp = ~KeyVal & (KeyVal ^ KeyOld);
	KeyOld = KeyVal;
		
	
	if(KeyUp == 1)
	{
	printf("UpKey Down");
	}
	else if(KeyUp == 2)
	{
		LCD_Clear(BLACK);
	printf("RightKey Down");
		if(++LcdPage > 5)
			LcdPage = 1;
	}	
	else if(KeyUp == 3)
	{
	printf("DownKey Down");
	}	
	else if(KeyUp == 4)
	{
		 LCD_Clear(BLACK);
	printf("LeftKey Down");
		if(--LcdPage < 1)
			LcdPage = 5;
	}	
	else if(KeyUp == 5)
	{
	printf("CenterKey Down");
	}	
		osDelay(20);
	}

}


u8 Key_Scan()
{
	if ((HAL_GPIO_ReadPin(KEY_U_GPIO_Port, KEY_U_Pin) == GPIO_PIN_RESET))
	{
		return 1; 
	}
	else if((HAL_GPIO_ReadPin(KEY_R_GPIO_Port, KEY_R_Pin) == GPIO_PIN_RESET))
	{
		return 2;
	}
		else if((HAL_GPIO_ReadPin(KEY_D_GPIO_Port, KEY_D_Pin) == GPIO_PIN_RESET))
	{
		return 3;
	}
		else if((HAL_GPIO_ReadPin(KEY_L_GPIO_Port, KEY_L_Pin) == GPIO_PIN_RESET))
	{
		return 4;
	}
		else if((HAL_GPIO_ReadPin(KEY_C_GPIO_Port, KEY_C_Pin) == GPIO_PIN_RESET))
	{
		return 5;
	}
	return 0;
	
}