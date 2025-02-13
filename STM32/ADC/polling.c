
  /*
  Slow. Blocks the process until reads. 
  Easy to implement.
  For more speed, use DMA.
  */
  

    HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	  value = HAL_ADC_GetValue(&hadc1);
	  valueVolts = scaler * value; //scaler is (VCC)/(2^(bit number) -1)

	  uint32_t valueVoltsWhole = (int)(valueVolts * 100); // to not use floats.

	  sprintf(message_1, " raw value: %lu\r\n", value);
	  HAL_UART_Transmit(&huart2, (uint8_t*)message_1, strlen(message_1), HAL_MAX_DELAY);

	  sprintf(message_2, "real voltage: %lu.%02lu V\r\n", valueVoltsWhole / 100, valueVoltsWhole % 100);
	  HAL_UART_Transmit(&huart2, (uint8_t*)message_2, strlen(message_2), HAL_MAX_DELAY);



	  HAL_Delay(500);
