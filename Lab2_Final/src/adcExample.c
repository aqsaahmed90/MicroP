/* Includes ------------------------------------------------------------------*/
#include "adcExample.h"

/*
*		Initializing ADC
*/

/* ADC Configeration ------------------------------------------------------------------------------------------------*/
void adcInit(void){
	ADC_InitTypeDef adc_init_s;
	ADC_CommonInitTypeDef adc_common_init_s;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
/* Set common parameters for ADC and initialize ----------------------------------------------------------------------*/
	adc_common_init_s.ADC_Mode 						= ADC_Mode_Independent;					//Single mode (rather than multi mode)
	adc_common_init_s.ADC_Prescaler 			= ADC_Prescaler_Div2;						//Set frequency of clock to ADC
	adc_common_init_s.ADC_DMAAccessMode 	= ADC_DMAAccessMode_Disabled;   //As Independent mode so do not require DMA
	adc_common_init_s.ADC_TwoSamplingDelay= ADC_TwoSamplingDelay_5Cycles; //Set delay between 2 samplings
	
	ADC_CommonInit(&adc_common_init_s);																		//Initialize ADCs peripherals according to the 
																																				//specified parameters 				
	
/* Set specific parameters for ADC for temperature sensor ------------------------------------------------------------*/
	adc_init_s.ADC_Resolution					 	= ADC_Resolution_12b;							//Set (highest) resolution
	adc_init_s.ADC_ScanConvMode				 	= DISABLE;												//Conversion is performed in single mode
	adc_init_s.ADC_ContinuousConvMode 	= DISABLE;												//Single mode
	adc_init_s.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;	//External trigger edge not required
	adc_init_s.ADC_DataAlign 						= ADC_DataAlign_Right;						//Big Endian format
	adc_init_s.ADC_NbrOfConversion 			= 1;															//Number of conversions per cycle is set to 1
	
	ADC_Init(ADC1, &adc_init_s);																					//Initialize the ADC1 peripheral
	ADC_Cmd(ADC1, ENABLE);																								//Enable ADC1 peripheral
	ADC_RegularChannelConfig(ADC1, ADC_Channel_TempSensor, 				 				//Configure ADC1 to temp sensor channel (16)
													 1, ADC_SampleTime_480Cycles);
	
/* ENABLE temperature sensor -----------------------------------------------------------------------------------------*/
	ADC_TempSensorVrefintCmd(ENABLE);
	
}
