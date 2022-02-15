#include "main_cycle.hpp"
#include "main.h"

#include <stdint.h>
#include <cmath>
// #include <iostream>

extern ADC_HandleTypeDef hadc1;
extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim4;

uint16_t ADC_buff[1];


void loop_main(void){
//    static uint16_t value = 0;
//
//    HAL_Delay(500);
//
//    if (HAL_ADC_Start(&hadc1) != HAL_OK){
//        Error_Handler();
//    }
//    if (HAL_ADC_PollForConversion(&hadc1, 100) != HAL_OK){
//        Error_Handler();
//    }
//    value = HAL_ADC_GetValue(&hadc1);
//
//    printf("value = %d\r\n", value);

}

void callback_1ms(void){
    static uint16_t t = 0;

    HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, (uint16_t)(2000 * std::sin(2 * 3.14159 * t / 1000) + 2048));

    printf("%d\r\n", ADC_buff[0]);

    if(t==1000) t = 0;
    else        t++;
}

void callback_8000Hz(void){
	static uint16_t n = 0;
	if (HAL_ADC_Start_IT(&hadc1) != HAL_OK){
		Error_Handler();
	}

	if(n==8000) n = 0;
	else        n++;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim == &htim7){
        callback_1ms();
    }
	if(htim == &htim4){
		callback_8000Hz();
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  if(hadc == &hadc1){
	  ADC_buff[0] = HAL_ADC_GetValue(&hadc1);
  }
}
