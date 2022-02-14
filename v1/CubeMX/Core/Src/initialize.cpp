#include "main.h"

void initialize(void){
	setbuf(stdout, NULL);
  char buf[] ="Hello World\r\n";
  HAL_UART_Transmit(&huart2,(uint8_t *)buf,sizeof(buf),0xffff);
  printf("Hello World!\r\n");
}

