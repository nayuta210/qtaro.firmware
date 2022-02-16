#include "main.h"

void loop_main(void);
void callback_1ms(void);
void callback_8000HZ(void);
void fft(uint16_t index);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
