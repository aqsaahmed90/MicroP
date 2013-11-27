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
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Enable the BUTTON Clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //RCC_AHB1Periph_GPIOA
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* Configure Button pin as input */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOA /*GPIOA*/, &GPIO_InitStructure);
  
   /* Connect Button EXTI Line to Button GPIO Pin */
   SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0); //EXTI_PortSourceGPIOA EXTI_PinSource0
  
   /* Configure Button EXTI line */
   EXTI_InitStructure.EXTI_Line = EXTI_Line0;
   EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
   EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
   EXTI_InitStructure.EXTI_LineCmd = ENABLE;
   EXTI_Init(&EXTI_InitStructure);
  
   /* Enable and set Button EXTI Interrupt to have a higher priority than the TAP interrupt */
   NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn; 
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  
   NVIC_Init(&NVIC_InitStructure); 
}
