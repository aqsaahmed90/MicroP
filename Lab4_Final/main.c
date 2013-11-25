#include "main.h"
/*!
 @brief Thread to perform menial tasks such as switching LEDs
 @param argument Unused
 */




//! Thread structure for above thread

osThreadDef(threadLED, 				osPriorityNormal, 1, 0);
osThreadDef(thread_adc,				osPriorityNormal, 1, 0);
osThreadDef(thread_accReader,	osPriorityNormal, 1, 0);

	// ID for threads
	osThreadId tid_thread1; 			// for LED
	osThreadId tid_thread2; 			// for ADC
	osThreadId tid_thread3; 			// for Accelerometer

/*!
 @brief Program entry point
 */
int main (void) {
// Configuration
	configLED(); 									// configuration for LED
	configBUTTON(); 							// configuration for Button
	adcInit(); 										// configuration for ADC
	AccelInit(); 									// configuration for Accelerometer
	timConfig(); 									// timing configuration

	


	//initialization of thread
	tid_thread1 = osThreadCreate(osThread(threadLED), NULL);
	tid_thread2 = osThreadCreate(osThread(thread_adc), NULL);
	tid_thread3 = osThreadCreate(osThread(thread_accReader), NULL);

	while(1){
		osDelay(osWaitForever);
	}
}

//Timmer 3 handler for acclerometer at 25Hz
void TIM3_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		osSignalSet(tid_thread3,0x01);							//Set Signal to allow polling
  }
}

//Timmer 2 handler for ADC at 20Hz
void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		osSignalSet(tid_thread2,0x02);						//Set Signal to allow polling
  }
}