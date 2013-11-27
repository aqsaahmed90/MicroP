/* Includes ------------------------------------------------------------------*/
#include "movingFilter.h"


/* MOVING FILTER -------------------------------------------------------------*/
void movingFilter(int32_t rawData, double* bufferVals, struct movingAvgFilter* filter){

	//double bufferVals[filter->buffer];
	double sum =0;
	int i;
	
	bufferVals[filter->index-1] = (double) rawData;
			
	for(i=1; i<=filter->buffer; i++ ){
		sum  += bufferVals[i-1];								//Get sum of values in array
	}
		
	filter->average = sum / filter->buffer;		//Get average
		
	filter->index++;													//Increment index

	if(filter->index == (filter->buffer+1)){	//If index exceeds buufer size:
		filter->index = 1;											//Reset index
	}

}
