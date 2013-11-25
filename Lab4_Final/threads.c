#include "threads.h"

	//GLOBAL VARIABLES
	int ticks = 0, ticks2 = 0;
	double pitch, roll;
	double temperature;
	int bFlag = 0;
	int tapFlag = 0;
	int doNothing = 0;

/* Delayer ------------------------------------------------------------------*/
void Delay(uint32_t delay) {
	int i;
  for(i=0;i<delay;i++); 
}

/*-Hardware PWM LED display----------------------------------------------*/
void pwm(void ){

	int brightness = 0;
	int n = 0;
	
	 while(tapFlag && bFlag)  // Do not exit
 {
   if (((brightness + n) >= 2000) || ((brightness + n) <= 0))
     n = -n; // if  brightness maximum/maximum change direction

   brightness += n;

   TIM4->CCR1 = brightness; // set brightness
   TIM4->CCR2 = brightness; // set 
	 TIM4->CCR3 = brightness; // set brightness
	 TIM4->CCR4 = brightness; // set brightness

   osDelay(100);						// delay
	}
}
/*-Tilt/Roll Calcilator----------------------------------------------*/
void thread_accReader(void const * argument){

	int32_t out[3];
	double x,y,z;
	double OffX = 0.0139, OffY = -0.0257, OffZ = -0.032;		//Offset for calibration
	
	//filter buffer
	double bufferValsX[FILTER_DEPTH] = {0};									
	double bufferValsY[FILTER_DEPTH] = {0};
	double bufferValsZ[FILTER_DEPTH] = {0};
	
	//XYZ filters
	struct movingAvgFilter filterX = {FILTER_DEPTH,1,0};
	struct movingAvgFilter filterY = {FILTER_DEPTH,1,0};
	struct movingAvgFilter filterZ = {FILTER_DEPTH,1,0};
	
	while(1){
		
		// Wait for an interrupt
		osSignalWait(0x01,osWaitForever);
		
		//Obtain rax XYZ values
		LIS302DL_ReadACC(out);
	
		//Filter values
		movingFilter(out[0],bufferValsX,&filterX);
		movingFilter(out[1],bufferValsY,&filterY);
 		movingFilter(out[2],bufferValsZ,&filterZ);		
 		
		
		//Calibrate data
		x = ((filterX.average)*MILLI)- OffX;
		y = ((filterY.average)*MILLI)- OffY;
 		z = ((filterZ.average)*MILLI)- OffZ;
		
		//Claculate pitch and roll
		pitch	= atan((x)/(sqrt((y*y)+(z*z))))*DEGREE;
		roll 	= atan((y)/(sqrt((x*x)+(z*z))))*DEGREE;

	}
}

/*Acclerometer LED display ---------------------------------------------------------------*/
void accLED(void){
	GPIOD->BSRRH = LED_ALL;
	int p,r;
	while(tapFlag && !bFlag){	
			if(pitch >= -90 && pitch <-45)		p=1;//	delayP = 1250000;
			else if(pitch >= -45 && pitch <0)	p=2;//	delayP = 625000;
			else if(pitch >= 0 && pitch <45)  p=3;//  delayP = 312500 ;
			else if(pitch >= 45 && pitch <90)	p=4;//  delayP = 156250;


			
			if(roll >= -90 && roll <-45)			r=1;//delayR = 1250000;
			else if(roll >= -45 && roll <0)		r=2;//delayR = 625000;
			else if(roll >= 0 && roll <45)	  r=3;//delayR = 312500;
			else if(roll >= 45 && roll <90)	  r=4;//delayR = 156250;
			
			if (p==1){
					switch(r){
						case(1):
							GPIO_ToggleBits(GPIOD,LED1); 	// toggle LED
	 						// wait a short period of time
							osDelay(500);
							GPIO_ToggleBits(GPIOD,LED1); 	// toggle LED
							osDelay(500);
							break;
		
						case(2):
							GPIO_ToggleBits(GPIOD,LED1); 	// toggle LED
							// wait a short period of time
							osDelay(400);
							GPIO_ToggleBits(GPIOD,LED1); 	// toggle LED
							osDelay(400);
							break;
						case(3):
							GPIO_ToggleBits(GPIOD,LED1); 	// toggle LED
							osDelay(300);
							GPIO_ToggleBits(GPIOD,LED1); 	// toggle LED
							osDelay(300);
							break;
						case(4):
							GPIO_ToggleBits(GPIOD,LED1); 	// toggle LED
							osDelay(200);
							GPIO_ToggleBits(GPIOD,LED1); 	// toggle LED
							osDelay(200);
							break;
						default: break;
						}
							
			}
			if (p==2){
					switch(r){
						case(1):
							GPIO_ToggleBits(GPIOD,LED2); 	// toggle LED
							osDelay(500);
						GPIO_ToggleBits(GPIOD,LED2); 	// toggle LED
						osDelay(500);
							break;
		
						case(2):
							GPIO_ToggleBits(GPIOD,LED2); 	// toggle LED
						osDelay(400);
							GPIO_ToggleBits(GPIOD,LED2); 	// toggle LED
						osDelay(400);
							break;
						case(3):
							GPIO_ToggleBits(GPIOD,LED2); 	// toggle LED
						osDelay(300);
							GPIO_ToggleBits(GPIOD,LED2); 	// toggle LED
						osDelay(300);
							break;
						case(4):
							GPIO_ToggleBits(GPIOD,LED2); 	// toggle LED
						osDelay(200);
							GPIO_ToggleBits(GPIOD,LED2); 	// toggle LED
						osDelay(200);
							break;
						default: break;
						}
							
			}		
			
			if (p==3){
					switch(r){
						case(1):
							GPIO_ToggleBits(GPIOD,LED3); 	// toggle LED
							osDelay(500);		 						// wait a short period of time
							GPIO_ToggleBits(GPIOD,LED3); 	// toggle LED
							osDelay(500);
							break;
		
						case(2):
							GPIO_ToggleBits(GPIOD,LED3); 	// toggle LED
							osDelay(400);		 						// wait a short period of time
							GPIO_ToggleBits(GPIOD,LED3); 	// toggle LED
							osDelay(400);
							break;
						case(3):
							GPIO_ToggleBits(GPIOD,LED3); 	// toggle LED
							osDelay(300);		 						// wait a short period of time
							GPIO_ToggleBits(GPIOD,LED3); 	// toggle LED
							osDelay(300);
							break;
						case(4):
							GPIO_ToggleBits(GPIOD,LED3); 	// toggle LED
							osDelay(200);		 						// wait a short period of time
							GPIO_ToggleBits(GPIOD,LED3); 	// toggle LED
							osDelay(200);
							break;
						default: break;
						}
							
			}		
			if (p==4){
				switch(r){
					case(1):
						GPIO_ToggleBits(GPIOD,LED4); 	// toggle LED
						osDelay(500);		 						// wait a short period of time
						GPIO_ToggleBits(GPIOD,LED4); 	// toggle LED
						osDelay(500);
						break;
	
					case(2):
						GPIO_ToggleBits(GPIOD,LED4); 	// toggle LED
						osDelay(400);		 						// wait a short period of time
						GPIO_ToggleBits(GPIOD,LED4); 	// toggle LED
						osDelay(400);
						break;
					case(3):
						GPIO_ToggleBits(GPIOD,LED4); 	// toggle LED
						osDelay(300);		 						// wait a short period of time
						GPIO_ToggleBits(GPIOD,LED4); 	// toggle LED
						osDelay(300);
						break;
					case(4):
						GPIO_ToggleBits(GPIOD,LED4); 	// toggle LED
						osDelay(200);		 						// wait a short period of time
						GPIO_ToggleBits(GPIOD,LED4); 	// toggle LED
						osDelay(200);
						break;
					default: break;
				}		
			}
		}			
}

/*Temperatre implementaion ----------------------------------------------------------*/
void thread_adc(void const * argument){
	
	struct movingAvgFilter filter = {FILTER_DEPTH,1,0};
	double bufferVals[FILTER_DEPTH] = {0};
	
	uint16_t adcData;
	double Vadc;

	while(1){
		osSignalWait(0x02,osWaitForever);												// Wait for an interrupt
		
		ADC_SoftwareStartConv(ADC1);														// Start analog to digital conversion
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET); 	// Wait till end of convsion flag is raised
		adcData = ADC_GetConversionValue(ADC1); 								// Result available in ADC1->DR
		
		movingFilter(adcData,bufferVals,&filter);								//Filter data
		
		Vadc = (filter.average/4095)*V_DD;											//Calclate Vadc
		temperature = ((Vadc-V_25)/AVG_SLOPE)+25;								//Claculate temperature


		ADC_ClearFlag(ADC1, ADC_FLAG_EOC);											// Resst EOC flag
		

	}
}	
/*Temperature LED display------------------------------------------------------------------------*/
void tempLED(void){	

	double compTemp = 30;
	double differ;
	
	GPIOD->BSRRH = LED_ALL;
	
	while(!tapFlag && !bFlag){
		differ =	temperature - compTemp ;
		
		if (differ >= 2){
			//if LED1 ON
			if(GPIO_ReadInputDataBit(GPIOD,LED1)==(uint8_t)Bit_SET){
				GPIO_ToggleBits(GPIOD, LED1|LED2);
			}
			
			//if LED2 ON
			else if(GPIO_ReadInputDataBit(GPIOD,LED2)==(uint8_t)Bit_SET){
				GPIO_ToggleBits(GPIOD, LED2|LED3);
			}
			
			//if LED3 ON
			else if(GPIO_ReadInputDataBit(GPIOD,LED3)==(uint8_t)Bit_SET){
				GPIO_ToggleBits(GPIOD, LED3|LED4);
			}
			
			//if LED4 ON
			else if(GPIO_ReadInputDataBit(GPIOD,LED4)==(uint8_t)Bit_SET){
				GPIO_ToggleBits(GPIOD, LED4|LED1);		
			}
			//no LED ON
			else{
				GPIO_ToggleBits(GPIOD, LED1);
			}
			
			compTemp = temperature;
		}
		
		
		else if (differ <= -2){
			//if LED1 ON
			if(GPIO_ReadInputDataBit(GPIOD,LED1)==(uint8_t)Bit_SET){
				GPIO_ToggleBits(GPIOD, LED1|LED4);
			}
			
			//if LED2 ON
			else if(GPIO_ReadInputDataBit(GPIOD,LED2)==(uint8_t)Bit_SET){
				GPIO_ToggleBits(GPIOD, LED2|LED1);
			}
			
			//if LED3 ON
			else if(GPIO_ReadInputDataBit(GPIOD,LED3)==(uint8_t)Bit_SET){
				GPIO_ToggleBits(GPIOD, LED3|LED2);
			}
			
			//if LED4 ON
			else if(GPIO_ReadInputDataBit(GPIOD,LED4)==(uint8_t)Bit_SET){
				GPIO_ToggleBits(GPIOD, LED4|LED3);
			}
			//no LED ON
			else{
				GPIO_ToggleBits(GPIOD, LED1);
			}

			compTemp = temperature;
		}
	}
}

/*Flash LED display------------------------------------------------------------------------*/
void flasLED(void){
	
	GPIOD->BSRRH = LED_ALL;							//Turn off all LED
	
	while(!tapFlag && bFlag){
		GPIO_ToggleBits(GPIOD,LED_ALL); 	// toggle LED
		osDelay(500);		 									// wait a short period of time
		GPIO_ToggleBits(GPIOD,LED_ALL); 	// turn of LED
		osDelay(500);	
	}			
}

void threadLED (void const *argument) {


	osThreadId tid_thread1;
	osThreadId tid_thread2;
	osThreadId tid_thread3;
	osThreadId tid_thread4;
	
	while(1){
		if(!tapFlag){
			configLED();
			if (!bFlag){
				tempLED();
			}
			else{
				flasLED();
			}
		}
		else{
			if (!bFlag){
				configLED();
				accLED();
			}
			else{
				pwmInit();
				pwm();
			}			
		}
			
	}		
}



//External interrupt handler (TAP)
void EXTI1_IRQHandler ()
{
	if ((EXTI_GetFlagStatus(EXTI_Line1) != RESET) )
  {
    EXTI_ClearITPendingBit(EXTI_Line1);
		tapFlag = !tapFlag;								//Set tap flag
		
		if((GPIOA->IDR & 0x0001)){
			tapFlag = !tapFlag;							//Dont set tap flag if button pressed
		}
	}
}

//External interrupt handler (BUTTON)
void EXTI0_IRQHandler ()
{
	if ((EXTI_GetFlagStatus(EXTI_Line0) != RESET) )
  {
    EXTI_ClearITPendingBit(EXTI_Line0);
		bFlag = !bFlag;							//Set button Flag
		tapFlag  = 0;	
	}
}



