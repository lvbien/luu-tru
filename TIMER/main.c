#include "stm32f10x.h"
 
GPIO_InitTypeDef GPIO_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 
void GPIO_Configuration(void);
void TIMbase_Configuration(void);
void TIM2_Configuration(void);
void DelayInit(void);
void DelayUs(uint32_t us);
void DelayMs(uint32_t ms);
 
volatile int32_t debug;
 
void main(void)
{
  GPIO_Configuration();
  TIMbase_Configuration();
  TIM2_Configuration();
  DelayInit();
  while (1)
  {
    TIM_SetCounter(TIM2,0);
    DelayMs(1000);
    debug = TIM_GetCounter(TIM2);
  }
}
 
void GPIO_Configuration(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  /* Configure PB0 PB1 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
 
void TIMbase_Configuration(void)
{
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
   
 /* Time base configuration */
 TIM_TimeBaseStructure.TIM_Prescaler = ((SystemCoreClock/2)/1000000)-1;     // frequency = 1000000
 TIM_TimeBaseStructure.TIM_Period = 1000 - 1;
 TIM_TimeBaseStructure.TIM_ClockDivision = 0;
 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
 TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
 TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
 TIM_Cmd(TIM4, ENABLE);
 
 NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 NVIC_Init(&NVIC_InitStructure);   
}
void TIM4_IRQHandler(void)
{
 static uint32_t time=0;
 if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
 {
  if(++time==999)
  {
   GPIO_SetBits(GPIOB,GPIO_Pin_0);
   DelayMs(10000);
  }
   if(++time>1000)
   {
    GPIO_ResetBits(GPIOB,GPIO_Pin_0); 
    time=0;
    DelayMs(10000);
   }
 TIM_ClearITPendingBit(TIM4, TIM_IT_Update); 
 }
}
  
void TIM2_Configuration(void)
{
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
   
 /* Time base configuration */
 TIM_TimeBaseStructure.TIM_Prescaler = 0;
 TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
 TIM_TimeBaseStructure.TIM_ClockDivision = 0;
 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
 TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
 TIM_Cmd(TIM2, ENABLE);
}
  
  
void DelayInit()
{
	// Update SystemCoreClock value
	SystemCoreClockUpdate();
	// Configure the SysTick timer to overflow every 1 us
	SysTick_Config(SystemCoreClock / 1000000);
}

void DelayUs(uint32_t us)
{
	// Reload us value
	usTicks = us;
	// Wait until usTick reach zero
	while (usTicks);
}

void DelayMs(uint32_t ms)
{
	// Wait until ms reach zero
	while (ms--)
	{
		// Delay 1ms
		DelayUs(1000);
	}
}