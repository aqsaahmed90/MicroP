
///* Includes ------------------------------------------------------------------*/
//#include <stdio.h>
//#include "stm32f4xx.h"
//#include "stm32f4xx_conf.h"
//#include "adcExample.h"
//#include "movingAvgFilter.h"
//#include "gpio_example.h"
//#include <stm32f4xx_gpio.h>

///* Defines ------------------------------------------------------------------*/
//#define Y_MAX 1000000L
//#define Y_MIN 5000L


///* Delayer ------------------------------------------------------------------*/
//void Delay(__IO uint32_t nCount) {
//  while(nCount--) {
//	}
//}


//void pwm(__IO uint32_t delay){
//	
//			GPIOD->BSRRH = LED_ALL;							//Turn off all LED
//			
///* BRIGHTNING LEDS -------------------------------------------------------------------*/
//			while(delay < Y_MAX){
//				GPIO_ToggleBits(GPIOD,LED_ALL); 	// toggle LED
//				Delay(delay);		 									// wait a short period of time
//				GPIO_ToggleBits(GPIOD,LED_ALL); 	// turn of LED
//				printf("delay is: %i\n" ,Y_MAX-(2*delay));
//				if((Y_MAX-(2*delay)) <= 0){
//					Delay (Y_MAX-(delay));
//					break;
//				}
//				else{
//					printf("please come in next\n");
//					Delay(Y_MAX-(2*delay));
//				}
//				delay += Y_MIN;
//			}
//			printf("Max brightness\n");

///* DIMMING LED -------------------------------------------------------------------*/
//				while(delay > Y_MIN){
//					printf("Dimming now\n");
//					GPIO_ToggleBits(GPIOD,LED_ALL); 	// toggle LED
//					Delay(delay);		 									// wait a short period of time
//					GPIO_ToggleBits(GPIOD,LED_ALL); 	// toggle LED
//					Delay(Y_MAX- (2*delay));	
//					delay -= Y_MIN;
//				}
//}
///* MAIN ------------------------------------------------------------------*/
//int main()
//{
//	__IO uint32_t delay = Y_MIN;
//	
///* 
//*	At 168MHz, this just a bit slower than 20Hz
//*	Number of ticks between two interrupt: 1/Freq* SystemCoreClock 
//*/
//	SysTick_Config(1 * SystemCoreClock / 250); 

//	configLED();


//	while(1){
//			pwm(delay);
//	}
//}

///* INTERRUPT HANDLER ----------------------------------------------------------------*/
//void SysTick_Handler(){
//	ticks = 1;
//}


/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "adcExample.h"
#include "movingAvgFilter.h"
#include "gpio_example.h"
#include <stm32f4xx_gpio.h>

/* Defines ------------------------------------------------------------------*/
#define Y_MAX 1000000L
#define Y_MIN 5000L


/* Delayer ------------------------------------------------------------------*/
void Delay(__IO uint32_t nCount) {
  while(nCount--) {
  }
}

/* MAIN ------------------------------------------------------------------*/
int main()
{
	struct movingAvgFilter filter = {FILTER_DEPTH,1,0};
	
	uint16_t adcData;
	ticks = 0;
	double compTemp = 30;
	double temperature;
	int defaultFlag = 1;
	__IO uint32_t delay = Y_MIN;
	
/* 
*	At 168MHz, this just a bit slower than 20Hz
*	Number of ticks between two interrupt: 1/Freq* SystemCoreClock 
*/
	SysTick_Config(1 * SystemCoreClock / 20); 
	
/* Initializing ADC LED and BUTTON  -------------------------------------------------------------------*/		
	adcInit();
	configLED();
  configBUTTON();


	while(1){
		while(!ticks);																					// Wait for an interrupt
		ticks = 0;																							// Decrement ticks
		
		ADC_SoftwareStartConv(ADC1);														// Start analog to digital conversion
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET); 	// Wait till end of convsion flag is raised
		adcData = ADC_GetConversionValue(ADC1); 								// Result available in ADC1->DR

			movingFilter (adcData, &filter);
		temperature = getTemp(filter.average);

/* ------------------PRINT TEMP-----------------------*/
		printf("Temperature: %f\n", temperature);
		
/* BUTTON PRESSED -------------------------------------------------------------------*/		
		if(GPIOA->IDR & 0x0001){
			defaultFlag = !defaultFlag;
			Delay(5000000L); 										// add a small delay to debounce the switch
		}
		
		if(defaultFlag){
			seeTempChange(temperature , &compTemp);
		}
		else{
			GPIOD->BSRRH = LED_ALL;							//Turn off all LED
			
/* BRIGHTNING LEDS -------------------------------------------------------------------*/
			while(delay < Y_MAX){
				GPIO_ToggleBits(GPIOD,LED_ALL); 	// toggle LED
				Delay(delay);		 									// wait a short period of time
				GPIO_ToggleBits(GPIOD,LED_ALL); 	// turn of LED
				Delay(Y_MAX-(delay));	
				delay += Y_MIN;
				
				if(GPIOA->IDR & 0x0001){					//If button pressed then exit to default
					defaultFlag = !defaultFlag;
					GPIOD->BSRRL = LED1;
					break;
				}
			}
			
/* DIMMING LED -------------------------------------------------------------------*/
				while(delay > Y_MIN){
					GPIO_ToggleBits(GPIOD,LED_ALL); 	// toggle LED
					Delay(delay);		 									// wait a short period of time
					GPIO_ToggleBits(GPIOD,LED_ALL); 	// toggle LED
					Delay(Y_MAX-delay);	
					delay -= Y_MIN;
					
					if(GPIOA->IDR & 0x0001){					//If button pressed then exit to default
						defaultFlag = !defaultFlag;
						GPIOD->BSRRL = LED1;
						break;
					}
				}
			}		

		ADC_ClearFlag(ADC1, ADC_FLAG_EOC);											// Resst EOC flag
	}
}

/* INTERRUPT HANDLER ----------------------------------------------------------------*/
void SysTick_Handler(){
	ticks = 1;
}



