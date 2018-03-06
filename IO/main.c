
#include "stm32f10x.h"

void GPIO_Configuration(void);
void NVIC_Configuration(void);
void DelayInit(void);
void DelayUs(uint32_t us);
void DelayMs(uint32_t ms);
//For store tick counts in us
static __IO uint32_t usTicks;

void main(void)
{
      GPIO_Configuration();
      while(1)
      {
         GPIO_SetBits(GPIOA,GPIO_Pin_0);
         DelayMs(10);
      }
}

void GPIO_Configuration(void)
{
      GPIO_InitTypeDef  GPIO_InitStructure;
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);    
      /* Configure output pushpull mode */
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;      
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void NVIC_Configuration(void)
{     
      NVIC_InitTypeDef NVIC_InitStructure;
      /* Enable IT TXE, use to get data bytes */
      NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 	1;
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 		0;
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
      NVIC_Init(&NVIC_InitStructure);
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