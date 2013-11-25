/* Inculdes ------------------------------------------------------*/
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_adc.h"

/* Defines -------------------------------------------------------*/
#define FILTER_DEPTH 10


/* FILTER -------------------------------------------------------*/
struct movingAvgFilter{
	int buffer;
	int index;
	double average;
};

/* Method declerations ------------------------------------------*/
void movingFilter(int32_t rawData, double* bufferVals, struct movingAvgFilter* filter);
