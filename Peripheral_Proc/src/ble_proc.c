#include "ble_proc.h"



osThreadId BleTaskHandle;


void Ble_Task_Proc(void const * argument)
{
  /* USER CODE BEGIN Ble_Task_Proc */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Ble_Task_Proc */
}