#include "gpioConfig.h"

void configLED(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	
	/* The LEDs on the STM324F Discovery are connected to the
	 * pins PD12 thru PD15
	 */
	GPIO_InitStructure.GPIO_Pin 	= LED_ALL; 					// configure all LED GPIO pins
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT; 		// pins to be an output
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // sets the GPIO modules clock speed
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 		// sets the pin type to push / pull (as opposed to open drain)
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL; // sets the pullup / pulldown resistors to be inactive
	
	GPIO_Init(GPIOD, &GPIO_InitStructure); 						// passes configuration to set the corresponding bits.

}

void configBUTTON(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_0;		  		// configure PIN 0: BUTTON
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN; 	  	// pin to be an input
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// sets the GPIO modules clock speed
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;   		// sets the pin type to push / pull (as opposed to open drain)
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_DOWN;   	// enables the pulldown resistor --> we want to detect a high level
	GPIO_Init(GPIOA, &GPIO_InitStructure);			  			// passes the configuration to set the corresponding bits.

}
