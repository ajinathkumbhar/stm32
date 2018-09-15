//print string on UART
HAL_UART_Transmit(&huart4, (uint8_t*)string, strlen(string), HAL_MAX_DELAY);

// LED ON OFF
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
HAL_Delay(100);
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
HAL_Delay(100);

// LED ON OFF toggle
HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_1);
HAL_Delay(100);

// User defined logs
//------------------------------------
void Slog(const char *fmt, ...) // custom printf() function
{
    va_list args;
    va_start(args, fmt);
    char string[200];
    if(0 < vsprintf(string,fmt,args)) {
    	HAL_UART_Transmit(&huart4, (uint8_t*)string, strlen(string), HAL_MAX_DELAY);
    } else
    	HAL_UART_Transmit(&huart4, (uint8_t*)"failed to build string", strlen(string), HAL_MAX_DELAY);
    va_end(args);
}

Slog("Enter in to funtion");
Slog("The current val : %d\n",val);
//------------------------------------

// Create task in freeRTOS

  xTaskCreate(Led_Gatekeeper,
		  (const char * const) "led_gate",
		  configMINIMAL_STACK_SIZE,
		  0,
		  2,
		  0);

void Led_Gatekeeper(void * pvParamerters) {
	int iLoop=0;
	for(;;){
		Slog("Led on for loop : %d \n",iLoop++);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1,GPIO_PIN_RESET);
		vTaskDelay(mxDelay);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1,GPIO_PIN_SET);
		vTaskDelay(mxDelay);
	}
}

