/* 
Parameter Settings, 
Enable Continous Conversion Mode
Enable DMA Continous Requests 

DMA Settings,
Mode circular
Half word.


Does not block processes. 
Faster.

The uart transmission delay of 500ms is counter productive, i put it for testing.


The half complete callback is triggered when the buffer is halfway filled automatically by the DMA.

I'm just looking at the second value of the buffer for testing, to implement a filter design, iterate over the buffer like the code below.

for(int i = 0; i < bufferSize / 2; i++){
  dacBuffer[i] = adcBuffer[i] / 2     // just an example
}

Using uint16_t for the adcBuffer is a concious decision. Since DMA is configured as half word(16 bits) and the ADC has 12bit resulation, 
using 16 bits instead of 32 will save memory because 16 bit can store every possible result of the DMA (0 to 4095).


*/


//callback functions
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc){
	value = adcBuffer[1];
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){

}

#define bufferSize 5000

uint16_t adcBuffer[bufferSize];

 


int main(void){

SystemClock_Config();
MX_GPIO_Init();
MX_DMA_Init();
MX_USART2_UART_Init();
MX_ADC1_Init();
HAL_ADC_Start_DMA(&hadc1, adcBuffer, bufferSize);
  
while (1)
  {
    
	  valueVolts = scaler * value;

	  uint32_t valueVoltsWhole = (int)(valueVolts * 100);

	  sprintf(message_1, " raw value: %lu\r\n", value);
	  HAL_UART_Transmit(&huart2, (uint8_t*)message_1, strlen(message_1), HAL_MAX_DELAY);

	  sprintf(message_2, "real voltage: %lu.%02lu V\r\n", valueVoltsWhole / 100, valueVoltsWhole % 100);
	  HAL_UART_Transmit(&huart2, (uint8_t*)message_2, strlen(message_2), HAL_MAX_DELAY);

	  HAL_Delay(500);

  }

}

