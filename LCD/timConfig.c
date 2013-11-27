#include "timConfig.h"

void timConfig(void)
{
	//	uint32_t  = 168000000;
  NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  /* Enable the TIM3 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  /* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 100;  
  TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock/(2*25*100)); 
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  /* TIM IT enable */
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);
	/*Timer 2----------------------------------------------------------------------------*/
	NVIC_InitTypeDef NVIC_InitStructure2;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure2;
  /* Enable the TIM2 gloabal Interrupt */
  NVIC_InitStructure2.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure2);
  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  /* Time base configuration */
  TIM_TimeBaseStructure2.TIM_Period = 100;  
  TIM_TimeBaseStructure2.TIM_Prescaler = (SystemCoreClock/(2*20*100)); 
  TIM_TimeBaseStructure2.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure2.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure2);
  /* TIM IT enable */
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);
}

void pwmInit(void){
	  RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOD, ENABLE );		//Enables  the AHB1 peripheral clock.
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4, ENABLE );		//Enables  the APB1 peripheral clock.

  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  TIM_OCInitTypeDef TIM_OCInitStruct;
    
 
    GPIO_StructInit(&GPIO_InitStructure); // Reset init structure
 
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);		//Change mapping of pins
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);
	// Setup All LED on STM32-Discovery Board to use PWM.
	GPIO_InitStructure.GPIO_Pin =  0xf000;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;            // Alt Function - Push Pull
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init( GPIOD, &GPIO_InitStructure );
       

 
    // Let PWM frequency equal 100Hz.
    // Let period equal 1000. Therefore, timer runs from zero to 1000. Gives 0.1Hz resolution.
    // Solving for prescaler gives 240.
    TIM_TimeBaseStructInit( &TIM_TimeBaseInitStruct );
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV4;
    TIM_TimeBaseInitStruct.TIM_Period = 1000 ;   // 0..999
    TIM_TimeBaseInitStruct.TIM_Prescaler = 240; // Div 240
    TIM_TimeBaseInit( TIM4, &TIM_TimeBaseInitStruct );
 
    TIM_OCStructInit( &TIM_OCInitStruct );
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    // Initial duty cycle equals 0%. Value can range from zero to 1000.
    TIM_OCInitStruct.TIM_Pulse = 500; // 0 .. 1000 (0=Always Off, 1000=Always On)
		//Channel 1-4 for the 4 LEDs
    TIM_OC1Init( TIM4, &TIM_OCInitStruct ); 
    TIM_OC2Init( TIM4, &TIM_OCInitStruct ); 
		TIM_OC3Init( TIM4, &TIM_OCInitStruct ); 
		TIM_OC4Init( TIM4, &TIM_OCInitStruct );
 
    TIM_Cmd( TIM4, ENABLE );
 
}
