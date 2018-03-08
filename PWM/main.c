#include "stm32f10x.h"
void GPIO_Configuration();
void TIM_PWM_Configuration();
void Delay ();


void main()
{
  TIM_PWM_Configuration();
  GPIO_Configuration();
  Delay ();
 TIM1->CCR1 = 10 * 65535 / 100;  //10% Duty cycle
 TIM1->CCR2 = 30 * 65535 / 100;  //30% Duty cycle
 TIM1->CCR3 = 60 * 65535 / 100;  //60% Duty cycle
 TIM1->CCR4 = 90 * 65535 / 100;  //90% Duty cycle
 while(1)        
 {
  
 }
}


void TIM_PWM_Configuration(void)
{
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
TIM_OCInitTypeDef          TIM_OCInitStructure;    
 
 TIM_TimeBaseStructure.TIM_Prescaler = 0;  
 TIM_TimeBaseStructure.TIM_Period = 0xFFFF;   // 65535
 TIM_TimeBaseStructure.TIM_ClockDivision = 0;
 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
 
 TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
  
 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
 TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; 
 TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
 TIM_OCInitStructure.TIM_Pulse = 0;
 //TIM_OCStructInit(&TIM_OCInitStructure);
    
 TIM_OC1Init(TIM1, &TIM_OCInitStructure);  
 TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
 
 TIM_OC2Init(TIM1, &TIM_OCInitStructure);
 TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
  
 TIM_OC3Init(TIM1, &TIM_OCInitStructure);
 TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
 
 TIM_OC4Init(TIM1, &TIM_OCInitStructure);
 TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
 
 TIM_ARRPreloadConfig(TIM1, ENABLE);
 
 /* TIM1 enable counter */
 TIM_Cmd(TIM1, ENABLE);
 TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void GPIO_Configuration()
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef  GPIO_InitStructure;
 /* Configure PB0 PB1 in output pushpull mode */
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
 GPIO_Init(GPIOA, &GPIO_InitStructure);  
}
void Delay(__IO uint32_t nCount)
{
 while(nCount--)
 {
 }
}