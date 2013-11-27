#include "main.h"
int ticks = 0;
//int tapFlag = 0;
double OffX = 0.0139, OffY = -0.0257, OffZ = -0.032;
volatile int i;
	int n = 1;
	int brightness  = 600;
	int brightness2 = 1500;
/* Delayer ------------------------------------------------------------------*/
void Delay(uint32_t delay) {
  for(i=0;i<delay;i++); 
}


void pwm(){

	 while(1)  // Do not exit
  {
    if (((brightness + n) >= 2400) || ((brightness + n) <= 600))
      n = -n; // if  brightness maximum/maximum change direction
 
		brightness += n;
 
    TIM4->CCR1 = brightness; // set brightness
    TIM4->CCR2 = brightness; // set 
		TIM4->CCR3 = brightness; // set brightness
		TIM4->CCR4 = brightness; // set brightness
		
    TIM5->CCR2 = brightness; // set 
		
    Delay(10000);								  // delay
//		if(!tapFlag){
			printf("brightness: %i\n",brightness);
//			break;
//		}
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
		
		printf("x: %f\n",x);
 		printf("y: %f\n",y);
 		printf("z: %f\n",z);
		
		pitch	= atan((x)/(sqrt((y*y)+(z*z))))*DEGREE;
		roll 	= atan((y)/(sqrt((x*x)+(z*z))))*DEGREE;
 		printf("pitch: %f\n",pitch);
 		printf("roll : %f\n",roll);
		
//		TIM4->CCR1 = brightness2; // set brightness
 //   TIM4->CCR2 = brightness2; // set 
//		TIM4->CCR3 = brightness2; // set brightness
//		TIM4->CCR4 = brightness2; // set brightness
		
//		TIM5->CCR2 = brightness; // set 
    Delay(10000);						 // delay
		
		brightness  = 10*roll+1500;
		brightness2 = 10*pitch+1500;

		}
}

int main()
{
	INTTIM_Config();
//	configLED();
//	pwmInit();
	AccelInit();
	
			configLED();
			pwmInit();
			pwmInit2();
	
	while(1){

		

			printf("pwming\n");
			accReader();
			//pwm();		
	}
	
}
//void EXTI0_IRQHandler ()
//{
//	if (EXTI_GetFlagStatus(EXTI_Line0) != RESET)
//  {
//    EXTI_ClearITPendingBit(EXTI_Line0);
//		tapFlag = !tapFlag;
//  }
//}
void TIM3_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		ticks = 1;
  }
}
