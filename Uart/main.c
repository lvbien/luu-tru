
#include "stm32f10x.h"

void GPIO_Configuration(void);
void NVIC_Configuration(void);
void USART1_Configuration(void);

void DelayInit(void);
void DelayUs(uint32_t us);
void DelayMs(uint32_t ms);
static __IO uint32_t usTicks;

void main(void)
{
      GPIO_Configuration();
      NVIC_Configuration();
      USART1_Configuration();
      DelayInit();
      GPIO_SetBits(GPIOA,GPIO_Pin_0);
      for(;;)
      {
          USART_SendData(USART1,'a');
          DelayMs(1000);
          if(USART_ReceiveData(USART1))
          {
            GPIO_ResetBits(GPIOA,GPIO_Pin_0);
          }
      }
}

void GPIO_Configuration(void)
{
      GPIO_InitTypeDef  GPIO_InitStructure;
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);    
      /* Configure output pushpull mode */
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
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
void USART1_Configuration(void)
{
      GPIO_InitTypeDef GPIO_InitStructure;
      /* Enable the USART3 Pins Software Remapping */
      GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
  
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   
/********************************* PORTA *************************************/
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
/*________________________________ OUTPUT ___________________________________*/
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;    // TX - USART1                     
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOA, &GPIO_InitStructure);
/*________________________________ INPUT ____________________________________*/
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;    // RX - USART1               
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOA, &GPIO_InitStructure);
      
      /* Enable the USARTy */
      USART_Cmd(USART1, ENABLE);
      
      USART_InitTypeDef USART_InitStructure;    
      USART_InitStructure.USART_BaudRate = 9600;
      USART_InitStructure.USART_WordLength = USART_WordLength_8b;
      USART_InitStructure.USART_StopBits = USART_StopBits_1;
      USART_InitStructure.USART_Parity = USART_Parity_No;
      USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
      USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
        
      /* Configure USART1 */
      USART_Init(USART1, &USART_InitStructure);
       
      /* Enable USARTy Receive and Transmit interrupts */
      USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
      NVIC_EnableIRQ(USART1_IRQn);
}

void USART1_IRQHandler(void)
{
      if( USART_GetITStatus( USART1, USART_IT_RXNE) != RESET )
      {
          GPIO_ResetBits(GPIOA,GPIO_Pin_0);
      }
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

