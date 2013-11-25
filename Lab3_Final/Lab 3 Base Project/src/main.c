#include "main.h"
int ticks = 0;
int tapFlag = 0;
double OffX = 0.0139, OffY = -0.0257, OffZ = -0.032;
volatile int i;
	int n = 1;
	int brightness = 0;
	
/* Delayer ------------------------------------------------------------------*/
void Delay(uint32_t delay) {
  for(i=0;i<delay;i++); 
}


void pwm(){

	 while(1)  // Do not exit
  {
    if (((brightness + n) >= 1000) || ((brightness + n) <= 0))
      n = -n; // if  brightness maximum/maximum change direction
 
        brightness += n;
 
    TIM4->CCR1 = brightness; // set brightness
    TIM4->CCR2 = brightness; // set 
		TIM4->CCR3 = brightness; // set brightness
		TIM4->CCR4 = brightness; // set brightness
 
    Delay(10000);								  // delay
		if(!tapFlag){
			printf("switch to acc\n");
			break;
		}
  }
}

void accReader(){
	int32_t delayP=0, delayR=0;
	int32_t out[3];
	double x,y,z;
	double pitch, roll;
	double bufferValsX[FILTER_DEPTH] = {0};
	double bufferValsY[FILTER_DEPTH] = {0};
	double bufferValsZ[FILTER_DEPTH] = {0};
	
	struct movingAvgFilter filterX = {FILTER_DEPTH,1,0};
	struct movingAvgFilter filterY = {FILTER_DEPTH,1,0};
	struct movingAvgFilter filterZ = {FILTER_DEPTH,1,0};
	
	while(1){
		
		// Wait for an interrupt
		while(!ticks);
		// Decrement ticks
		ticks = 0;
		int r,p;
		LIS302DL_ReadACC(out);
	
		movingFilter(out[0],bufferValsX,&filterX);
		movingFilter(out[1],bufferValsY,&filterY);
 		movingFilter(out[2],bufferValsZ,&filterZ);		
 		
		x = ((filterX.average)*MILLI)- OffX;
		y = ((filterY.average)*MILLI)- OffY;
 		z = ((filterZ.average)*MILLI)- OffZ;
		
//		printf("x: %f\n",x);
// 		printf("y: %f\n",y);
// 		printf("z: %f\n",z);
		
		pitch	= atan((x)/(sqrt((y*y)+(z*z))))*DEGREE;
		roll 	= atan((y)/(sqrt((x*x)+(z*z))))*DEGREE;
 		printf("pitch: %f\n",pitch);
 		printf("roll : %f\n",roll);
		
#ifdef SHOW_LED		
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
						Delay(1250000);		 						// wait a short period of time
						GPIO_ToggleBits(GPIOD,LED1); 	// toggle LED
						Delay(1250000);
						break;
	
					case(2):
						GPIO_ToggleBits(GPIOD,LED1); 	// toggle LED
						Delay(625000);		 						// wait a short period of time
						GPIO_ToggleBits(GPIOD,LED1); 	// toggle LED
						Delay(625000);
						break;
					case(3):
						GPIO_ToggleBits(GPIOD,LED1); 	// toggle LED
						Delay(312500);		 						// wait a short period of time
						GPIO_ToggleBits(GPIOD,LED1); 	// toggle LED
						Delay(312500);
						break;
					case(4):
						GPIO_ToggleBits(GPIOD,LED1); 	// toggle LED
						Delay(156250);		 						// wait a short period of time
						GPIO_ToggleBits(GPIOD,LED1); 	// toggle LED
						Delay(156250);
						break;
					default: break;
					}
						
		}
		if (p==2){
				switch(r){
					case(1):
						GPIO_ToggleBits(GPIOD,LED2); 	// toggle LED
						Delay(1250000);		 						// wait a short period of time
						GPIO_ToggleBits(GPIOD,LED2); 	// toggle LED
						Delay(1250000);
						break;
	
					case(2):
						GPIO_ToggleBits(GPIOD,LED2); 	// toggle LED
						Delay(625000);		 						// wait a short period of time
						GPIO_ToggleBits(GPIOD,LED2); 	// toggle LED
						Delay(625000);
						break;
					case(3):
						GPIO_ToggleBits(GPIOD,LED2); 	// toggle LED
						Delay(312500);		 						// wait a short period of time
						GPIO_ToggleBits(GPIOD,LED2); 	// toggle LED
						Delay(312500);
						break;
					case(4):
						GPIO_ToggleBits(GPIOD,LED2); 	// toggle LED
						Delay(156250);		 						// wait a short period of time
						GPIO_ToggleBits(GPIOD,LED2); 	// toggle LED
						Delay(156250);
						break;
					default: break;
					}
						
		}		
		
		if (p==3){
				switch(r){
					case(1):
						GPIO_ToggleBits(GPIOD,LED3); 	// toggle LED
						Delay(1250000);		 						// wait a short period of time
						GPIO_ToggleBits(GPIOD,LED3); 	// toggle LED
						Delay(1250000);
						break;
	
					case(2):
						GPIO_ToggleBits(GPIOD,LED3); 	// toggle LED
						Delay(625000);		 						// wait a short period of time
						GPIO_ToggleBits(GPIOD,LED3); 	// toggle LED
						Delay(625000);
						break;
					case(3):
						GPIO_ToggleBits(GPIOD,LED3); 	// toggle LED
						Delay(312500);		 						// wait a short period of time
						GPIO_ToggleBits(GPIOD,LED3); 	// toggle LED
						Delay(312500);
						break;
					case(4):
						GPIO_ToggleBits(GPIOD,LED3); 	// toggle LED
						Delay(156250);		 						// wait a short period of time
						GPIO_ToggleBits(GPIOD,LED3); 	// toggle LED
						Delay(156250);
						break;
					default: break;
					}
						
		}		
		if (p==4){
				switch(r){
					case(1):
						GPIO_ToggleBits(GPIOD,LED4); 	// toggle LED
						Delay(1250000);		 						// wait a short period of time
						GPIO_ToggleBits(GPIOD,LED4); 	// toggle LED
						Delay(1250000);
						break;
	
					case(2):
						GPIO_ToggleBits(GPIOD,LED4); 	// toggle LED
						Delay(625000);		 						// wait a short period of time
						GPIO_ToggleBits(GPIOD,LED4); 	// toggle LED
						Delay(625000);
						break;
					case(3):
						GPIO_ToggleBits(GPIOD,LED4); 	// toggle LED
						Delay(312500);		 						// wait a short period of time
						GPIO_ToggleBits(GPIOD,LED4); 	// toggle LED
						Delay(312500);
						break;
					case(4):
						GPIO_ToggleBits(GPIOD,LED4); 	// toggle LED
						Delay(156250);		 						// wait a short period of time
						GPIO_ToggleBits(GPIOD,LED4); 	// toggle LED
						Delay(156250);
						break;
					default: break;
					}
						
		}		
		
		
//		GPIO_ToggleBits(GPIOD,LED2); 	// toggle LED
//		Delay(delayP);		 									// wait a short period of time
//		GPIO_ToggleBits(GPIOD,LED2); 	// toggle LED
//		Delay(delayP);
//		
//		GPIO_ToggleBits(GPIOD,LED1); 	// toggle LED
//		Delay(delayR);		 									// wait a short period of time
//		GPIO_ToggleBits(GPIOD,LED1); 	// toggle LED
//		Delay(delayR);
#endif					
		if(tapFlag){
			printf("switch to pwm\n");
			break;
		}
	}
}

int main()
{
	INTTIM_Config();
//	configLED();
//	pwmInit();
	AccelInit();
	
	while(1){
		if (!tapFlag){
			configLED();
			GPIOD->BSRRH = LED_ALL;
			printf("readings\n");
			accReader();
		}
		else{
			//configLED();
			pwmInit();
			printf("pwming\n");
			pwm();
		}
			
	}
	
}
void EXTI0_IRQHandler ()
{
	if (EXTI_GetFlagStatus(EXTI_Line0) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line0);
		tapFlag = !tapFlag;
  }
}
void TIM3_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		ticks = 1;
  }
}
