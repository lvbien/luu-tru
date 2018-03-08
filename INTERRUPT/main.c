
#include "stm32f10x.h"
 
GPIO_InitTypeDef  GPIO_InitStructure;
NVIC_InitTypeDef  NVIC_InitStructure;
EXTI_InitTypeDef  EXTI_InitStructure;
 
 
void GPIO_Configuration(void);
void EXTILine0_Config(void);
void Delay(__IO uint32_t nCount);
 
void main()
{
 GPIO_Configuration();
 EXTILine0_Config();
 while(1)        
 {
  GPIO_SetBits(GPIOB,GPIO_Pin_0);
  Delay(6000000);
  GPIO_ResetBits (GPIOB,GPIO_Pin_0);
  Delay(6000000);

 }
}
void GPIO_Configuration(void)
{
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
 
 /* Configure PB0 PB1 in output pushpull mode */
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_Init(GPIOB, &GPIO_InitStructure);                         
}
void EXTILine0_Config(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
  
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
  
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
      
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
 
void Delay(__IO uint32_t nCount)
{
 while(nCount--)
 {
 }
}
void EXTI0_IRQHandler(void)
{
 if(EXTI_GetITStatus(EXTI_Line0) != RESET)
 {
  GPIO_SetBits(GPIOB,GPIO_Pin_1);
  Delay(6000000);
  GPIO_ResetBits (GPIOB,GPIO_Pin_1);
  Delay(6000000);
  EXTI->PR = EXTI_Line0;
 }
}
  
