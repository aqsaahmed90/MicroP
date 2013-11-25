/* Includes ------------------------------------------------------------------*/
#include "movingAvgFilter.h"


/* MOVING FILTER -------------------------------------------------------------*/
void movingFilter(uint16_t adcData, struct movingAvgFilter* filter){

	double bufferVals[filter->buffer];
	double sum =0;
	int i;
	
	bufferVals[filter->index-1] = (double) adcData;
			
	for(i=1; i<=filter->buffer; i++ ){
		printf("bufferVals: %f\n", bufferVals[i-1]);
		sum  += bufferVals[i-1];								//Get sum of values in array
	}
		
	filter->average = sum / filter->buffer;		//Get average
		
	filter->index++;													//Increment index

	if(filter->index == (filter->buffer+1)){	//If index exceeds buufer size:
		filter->index = 1;											//Reset index
	}
}

/* CONVERT TO TEMPERATURE -----------------------------------------------------*/
double getTemp(double adcData){
	
	double Vadc = (adcData/4095)*V_DD;
	double Temp = ((Vadc-V_25)/AVG_SLOPE)+25;
	
	return Temp;
	
}

