#include "accConfig.h"

uint8_t crtl;
void AccelInit()
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	LIS302DL_InitTypeDef  					LIS302DL_InitStruct;
	LIS302DL_InterruptConfigTypeDef LIS302DL_InterruptStruct;  


	/* Set configuration of LIS302DL*/
	LIS302DL_InitStruct.Power_Mode			= LIS302DL_LOWPOWERMODE_ACTIVE;
	LIS302DL_InitStruct.Output_DataRate = LIS302DL_DATARATE_100;
	LIS302DL_InitStruct.Axes_Enable 		= LIS302DL_X_ENABLE | LIS302DL_Y_ENABLE | LIS302DL_Z_ENABLE;
	LIS302DL_InitStruct.Full_Scale 			= LIS302DL_FULLSCALE_2_3;
	LIS302DL_InitStruct.Self_Test 			= LIS302DL_SELFTEST_NORMAL;

	LIS302DL_Init(&LIS302DL_InitStruct);
	
	
	/*Tap Config---------------------------------------------------------------------------------------	*/
	
	/* Set configuration of Internal High Pass Filter of LIS302DL*/
	LIS302DL_InterruptStruct.Latch_Request 		= LIS302DL_INTERRUPTREQUEST_LATCHED;
	LIS302DL_InterruptStruct.SingleClick_Axes = LIS302DL_CLICKINTERRUPT_XYZ_ENABLE;

	LIS302DL_InterruptConfig(&LIS302DL_InterruptStruct);
	
	/* Enable GPIOE clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);			//Enables the AHB1 peripheral GPIOE clock.
  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);		//Enables (APB2) peripheral SYSCFG clock
  
  /* Configure PE0 pin as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  /* Connect EXTI Line0 to PE0 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource1);		//Selects the GPIOE pin 1 used as EXTI Line1.
  /* Configure EXTI Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;											//Specifies the new state of the selected EXTI lines
  EXTI_Init(&EXTI_InitStructure);
  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	 /* Configure Interrupt control register: enable Click interrupt2 */
  crtl = 0x38;
  LIS302DL_Write(&crtl, LIS302DL_CTRL_REG3_ADDR, 1);
  
  /* Enable Interrupt generation on click on Z axis */
  crtl = 0x15;
  LIS302DL_Write(&crtl, LIS302DL_CLICK_CFG_REG_ADDR, 1);
  
  /* Configure Click Threshold on X/Y axis (10 x 0.5g) */
  crtl = 0xAA;
  LIS302DL_Write(&crtl, LIS302DL_CLICK_THSY_X_REG_ADDR, 1);
  
  /* Configure Click Threshold on Z axis (10 x 0.5g) */
  crtl = 0x0A;
  LIS302DL_Write(&crtl, LIS302DL_CLICK_THSZ_REG_ADDR, 1);
  
  /* Configure Time Limit */
  crtl = 0x03;
  LIS302DL_Write(&crtl, LIS302DL_CLICK_TIMELIMIT_REG_ADDR, 1);
    
  /* Configure Latency */
  crtl = 0x7F;
  LIS302DL_Write(&crtl, LIS302DL_CLICK_LATENCY_REG_ADDR, 1);
}
