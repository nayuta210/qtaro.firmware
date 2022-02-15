#include "initialize.hpp"
#include "main.h"

extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;

extern ADC_HandleTypeDef hadc1;

extern uint16_t ADC_buff[1];

void initialize(void){
	setbuf(stdout, NULL);
  printf("Hello World!\r\n");

  HAL_TIM_Base_Start_IT(&htim4);
  HAL_TIM_Base_Start_IT(&htim7);
  // HAL_TIM_Base_Start(&htim5);

  HAL_TIM_GenerateEvent(&htim4, TIM_EVENTSOURCE_UPDATE);
//  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 500);

//  HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADC_buff, sizeof(ADC_buff) / sizeof(ADC_buff[0]));
}

