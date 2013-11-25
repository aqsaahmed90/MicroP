/* Inculdes ------------------------------------------------------*/
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_adc.h"

/* Defines -------------------------------------------------------*/
#define FILTER_DEPTH 10
#define V_DD  			3
#define V_25  			0.76
#define AVG_SLOPE	 	0.0025

/* FILTER -------------------------------------------------------*/
struct movingAvgFilter{
	int buffer;
	int index;
	double average;
};

/* Method declerations ------------------------------------------*/
void movingFilter(uint16_t adcData, struct movingAvgFilter* filter);
double getTemp(double adcData);


