#define ARM_MATH_CM4
#include "main_cycle.hpp"
#include "main.h"

#include "arm_math.h"

#include <stdint.h>
#include <cmath>
// #include <iostream>


extern ADC_HandleTypeDef hadc1;
extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim4;

constexpr uint16_t FFT_point = 256;
float32_t ADC_buff[512];
float32_t freq_fft[512];


uint16_t t = 0;


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

    // HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, (uint16_t)(2000 * std::sin(2.0 * 3.14159 * t / 1000.0) + 2048));

    // printf("%d\r\n", ADC_buff[0]);

}

void callback_8000Hz(void){
	if (HAL_ADC_Start_IT(&hadc1) != HAL_OK){
		Error_Handler();
	}

    ADC_buff[t%(FFT_point * 2)] = (uint16_t)(2000.0f * std::sin(2.0f * 3.14159f * (float)t / 256.0f) + 2048);

	if(t%(FFT_point * 2) == 256){
        fft(0);
	}else if(t%(FFT_point * 2) == 0){
        fft(256);
		// t = 0;
	}else{
		t++;
	}
    if(t==0){
		printf("----------------\r\n");
		for(uint16_t i = 0; i<FFT_point*2; i++){
			printf("%f, %f\r\n", freq_fft[i*2], freq_fft[i*2+1]);
		}
    }
}

void fft(uint16_t index){
	bool flag = true;

	if (true){
        arm_rfft_fast_instance_f32 instance = {};

        if (flag)
        { // init instance
            flag = flag && (ARM_MATH_SUCCESS == arm_rfft_fast_init_f32(&instance, FFT_point));
        }

        if (flag && index <= FFT_point)
        { // execute FFT
            arm_rfft_fast_f32(&instance, &ADC_buff[index], freq_fft, 0);
        }
	}
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
	  ADC_buff[t%(FFT_point * 2)] = (float32_t)HAL_ADC_GetValue(&hadc1);
  }
}
