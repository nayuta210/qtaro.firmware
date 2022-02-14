#include "main_cycle.hpp"
#include "main.h"

#include <stdint.h>
//#include <iostream>

extern ADC_HandleTypeDef hadc1;

void loop_main(void){
    static uint16_t value = 0;

    HAL_Delay(500);

    if (HAL_ADC_Start(&hadc1) != HAL_OK){
        Error_Handler();
    }
    if (HAL_ADC_PollForConversion(&hadc1, 100) != HAL_OK){
        Error_Handler();
    }
    value = HAL_ADC_GetValue(&hadc1);

    printf("value = %d\r\n", value);

}
