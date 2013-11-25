//Includes
#include <math.h>
#include "stm32f4xx.h"
#include "cmsis_os.h"
#include "movingFilter.h"
#include "stm32f4_discovery_lis302dl.h"
#include "gpioConfig.h"
#include "timConfig.h"

//Define variables
#define FILTER_DEPTH	10
#define DEGREE 				180/3.1415
#define MILLI					0.001
#define V_DD  				3
#define V_25  				0.76
#define AVG_SLOPE	 		0.0025

//Function declerations
void thread_adc(void const * argument);
void thread_accReader(void const * argument);
void accLED(void); 
void tempLED(void); 
void pwm(void);
void flasLED(void); 
void threadLED(void const * argument);

void Delay(uint32_t delay);

