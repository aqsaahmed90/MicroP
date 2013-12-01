//Given includes
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
//#include "stm32f4_discovery_lis302dl.h"

//Our header files
#include "accelerometer.h"
#include "timers.h"
#include "gpio.h"
#include "motor.h"
#include "filter.h"
#include <math.h>

/* TO DO: UPDATE COMMENTS EVERY TIME YOU CREATE A METHOD.
	- Read values from accelerometer 											(DONE)
		+Configure and initialize accelerometer 						(DONE)
		+Determine correct settings and why they're 				(DONE)
		 correct																						(DONE)
		+Read from accelerometer 														(DONE)
		+Convert reading to G's															(DONE)
	- Set up timer 																				(DONE)
		+Configure and initialize 													(DONE)
			=25 Hz 																						(DONE)
			=Prescaler and divisor can't overflow registers		(DONE)
		+Create interrupt routine 													(DONE)
			=Make it small! 																	(DONE)
		+Modify main to run on interrupt. NO SPINLOCKING 		(DONE)
	- Calibration																					(DONE)
		+Create Second Program															(DONE)
			=Use already written code from main								(DONE)
		+Create code for calibration process								(DONE)
			=See slides and documentation for details					(DONE)
		+Run Calibration process														(DONE)
			=Several times if you want, I don't really				(DONE)
			 care. It will probably be easy to run in the			(DONE)
			 future.																					(DONE)
		+Put results of calibration into main program				(DONE)
			=See slides for equations.												(DONE)
			=Equations should go in read_Accelerometer.				(DONE)
	- Filtering (LAB 2)																		(DONE)
		+Add in code for the filter													(DONE)
		+Matlab analysis must be preformed on filter depth	(DONE)
		 as in Lab 2.																				(DONE)
	- Detect single taps																	(DONE)
		+Generate interrupt on single tap										(DONE)
		+Functionality of accelerometer											(DONE)
			=Look in documentation for process.								(DONE)
		+Switch mode on single tap													(DONE)
			=Think of a better way than a FSM.								(DONE)
	- Hardware PWM																				(DONE)
		+Hard way:																					(DONE)
			=Configure and initialize TIM4										(DONE)
			=Look at example peripheral projects for how			(DONE)
			 to get PWM working																(DONE)
		+Look at config/setup to figure out what settings		(DONE)
		 do																									(DONE)
	-Use LEDs to display angle data												(DONE)
	-Go through driver code to figure out what accel calls(DONE)
	 are doing																						(DONE)
	-Prove with oscilliscope that clock is going at				(Ben & Tanuj)
	 25Hz																									(Ben & Tanuj)
*/

volatile uint_fast16_t tick = 0;
volatile uint_fast16_t tap = 0;



int main(){
	GPIO_Config();
	INTTIM_Config();
	ACCEL_Config();
	

	angle_data new_vals;
	INTTIM_Config();
	ACCEL_Config();
	
	initMotorR();
	initMotorP();
	
//	while(1) {
//		if(tick){
//			new_vals = read_Accelerometer();
//			printf("pitch: %f\n", new_vals.pitch);
//			printf("roll : %f\n", new_vals.roll);
//			
//			tick = 0;
//			Clear_Accel_Int();
//		}
//		//motorMove(new_vals.roll,new_vals.pitch);	
//		motorMove(-90,0);
//		motorMove(90,0);
//		motorMove(0,0);
//		motorMove(0,90);
//		motorMove(0,-90);
//		motorMove(90,90);
//		motorMove(-90,-90	);	
//	}
		motorMove(-90,0);
		motorMove(90,0);
		motorMove(0,0);
		motorMove(0,90);
		motorMove(0,-90);
		motorMove(90,90);
		motorMove(-90,-90);
		
		int n=1;
		double roll = -45;
		while(1){
			
			if (((roll + n) < -45) || ((roll + n) >  45))
				n = -n; // if maximum/minimum change direction
			
			roll = roll + n;
			motorMove(roll,80);
		}
}

