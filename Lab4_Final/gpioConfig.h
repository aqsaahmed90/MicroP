#include "stm32f4xx_conf.h"

/*Defines --------------------------------------------------------*/
#define LED1  GPIO_Pin_12 //GREEN
#define LED2  GPIO_Pin_13 //ORANGE
#define LED3  GPIO_Pin_14 //RED
#define LED4  GPIO_Pin_15 //BLUE
#define LED_ALL 0xF000		//ALL

#define CLOCKWISE	1				//clockwise/couter-clockwise

/* Method declerations -------------------------------------------*/
void configLED(void);
void configBUTTON(void);

