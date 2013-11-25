

#include "movingAvgFilter.h"
	
struct movingAvgFilter movingFilter(uint16_t adcData, struct movingAvgFilter filter){

	double bufferVals[filter.buffer];
	double sum =0;
	static int bufferFull = 0;
	int i;
	
	bufferVals[filter.index-1] = (double) adcData;
	
	//printf("adcData is: %i\n", adcData);
	//printf("filter index is at: %i\n", filter.index);
	
	if(bufferFull == 0){
		
		for(i=1; i<=filter.index; i++ ){
			sum  += bufferVals[i-1];
			//printf("sum is first: %f\n",sum);
		}
		
		filter.average = sum / filter.index;
		
		filter.index++;
		//printf("avg is first: %f\n",filter.average);
		//printf("ind is first: %i\n",filter.index);
		if(filter.index == 11){
			bufferFull = 1;
		}
	}
	//-------------------------------------------------------------
	else{
		
		for(i=1; i<=10; i++ ){
			sum  += bufferVals[i-1];
			//printf("sum is first: %f\n",sum);
		}
		
		filter.average = sum / filter.buffer;
		
		filter.index++;
		//printf("avg is second: %f\n",filter.average);
		//printf("index is second: %i\n",filter.index);
		
	}
	if(filter.index == 11){
		filter.index = 1;
	}
	
	return filter;
}


double getTemp(double adcData){
	double Vdd = 3;
	double V25 = 0.76;
	double Avg_Slope	= 0.0025;
	
	double Vadc = (adcData/4095)*Vdd;
	double Temp = ((Vadc-V25)/Avg_Slope)+25;
	
	return Temp;
	
}

