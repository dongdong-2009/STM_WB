//=============================================================================
//文件名称：usart1.c
//功能概要：串口1驱动文件
//更新时间：2014-01-04
//=============================================================================
#include "ALL_Includes.h"
#include "USART1.h"


/* USART初始化 */
void USART1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);  //使能GPIOA的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//使能USART的时钟
	/* USART1的端口配置 */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);//配置PA9成第二功能引脚	TX
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);//配置PA10成第二功能引脚  RX	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	

	/* USART1的基本配置 */
	USART_InitStructure.USART_BaudRate = 115200;              //波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStructure);		
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);           //使能接收中断
	USART_Cmd(USART1, ENABLE);                             //使能USART1
	
	/* USART1的NVIC中断配置 */
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPriority = 0x02;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
				
}

//=============================================================================
//文件名称：
//功能概要：USART1中断函数
//参数说明：无
//函数返回：无
//=============================================================================

#define LOWCH1_112M  1 
#define HIGHCH1_112M 2 
#define LOWCH2_112M  3 
#define HIGHCH2_112M 4 

#define LOWCH1_56M 'a' 
#define LOWCH2_56M 'b' 
#define LOWCH3_56M 'c' 
#define LOWCH4_56M 'd' 

#define HIGHCH1_56M 'e' 
#define HIGHCH2_56M 'f' 
#define HIGHCH3_56M 'g' 
#define HIGHCH4_56M 'h' 

#define RegNum			44
	
unsigned	int LOW_CH1_112M[RegNum] = 
{
0x00221E  ,
0x4001AF  ,
0x3E0000  ,
0x3D0001  ,
0x3B0000  ,
0x3003FC  ,
0x2F08D4  ,
0x2E14A2  ,
0x2D9EEC  ,
0x2C823C  ,
0x2B0000  ,
0x2A0000  ,
0x29FFFF  ,
0x28FFFF  ,
0x278204  ,
0x26002A  ,
0x255000  ,
0x240811  ,
0x23021B  ,
0x22C3F0  ,
0x214210  ,
0x204210  ,
0x1F0401  ,
0x1E0035  ,
0x1D0084  ,
0x1C2924  ,
0x190000  ,
0x180509  ,
0x178842  ,
0x162300  ,
0x14012C  ,
0x130965  ,
0x0E0FFE  ,
0x0D4000  ,
0x0C7001  ,
0x0B0028  ,
0x0A12D8  ,
0x090302  ,
0x081084  ,
0x0728B2  ,
0x041943  ,
0x020500  ,
0x010808  ,
0x00221C
	
	};



unsigned	int LOW_CH2_112M[RegNum] = 
{
0x00221E  ,
0x4001AF  ,
0x3E0000  ,
0x3D0001  ,
0x3B0000  ,
0x3003FC  ,
0x2F08D4  ,
0x2E14A2  ,
0x2D0B77  ,
0x2CCE24  ,
0x2B0000  ,
0x2A0000  ,
0x29FFFF  ,
0x28FFFF  ,
0x278204  ,
0x26002A  ,
0x255000  ,
0x240811  ,
0x23021B  ,
0x22C3F0  ,
0x214210  ,
0x204210  ,
0x1F0401  ,
0x1E0035  ,
0x1D0084  ,
0x1C2924  ,
0x190000  ,
0x180509  ,
0x178842  ,
0x162300  ,
0x14012C  ,
0x130965  ,
0x0E0FFE  ,
0x0D4000  ,
0x0C7001  ,
0x0B0028  ,
0x0A12D8  ,
0x090302  ,
0x081084  ,
0x0728B2  ,
0x041943  ,
0x020500  ,
0x010808  ,
0x00221C
	
	};



unsigned	int HIGH_CH1_112M[RegNum] = 
{
0x00221E  ,
0x4001AF ,
0x3E0000 ,
0x3D0001 ,
0x3B0000 ,
0x3003FC ,
0x2F08D4 ,
0x2E14A2 ,
0x2DF3B6 ,
0x2C3AFD ,
0x2B0000 ,
0x2A0000 ,
0x29FFFF ,
0x28FFFF ,
0x278204 ,
0x260024 ,
0x255000 ,
0x240811 ,
0x23021B ,
0x22C3F0 ,
0x214210 ,
0x204210 ,
0x1F0401 ,
0x1E0035 ,
0x1D0084 ,
0x1C2924 ,
0x190000 ,
0x180509 ,
0x178842 ,
0x162300 ,
0x14012C ,
0x130965 ,
0x0E0FFE ,
0x0D4000 ,
0x0C7001 ,
0x0B0028 ,
0x0A12D8 ,
0x090302 ,
0x081084 ,
0x0728B2 ,
0x041943 ,
0x020500 ,
0x010808 ,
0x00221C
	
	};	




unsigned	int HIGH_CH2_112M[RegNum] = 
{
0x00221E  ,
0x4001AF  ,
0x3E0000  ,
0x3D0001  ,
0x3B0000  ,
0x3003FC  ,
0x2F08D4  ,
0x2E14A2  ,
0x2D6041  ,
0x2C86E5  ,
0x2B0000  ,
0x2A0000  ,
0x29FFFF  ,
0x28FFFF  ,
0x278204  ,
0x260024  ,
0x255000  ,
0x240811  ,
0x23021B  ,
0x22C3F0  ,
0x214210  ,
0x204210  ,
0x1F0401  ,
0x1E0035  ,
0x1D0084  ,
0x1C2924  ,
0x190000  ,
0x180509  ,
0x178842  ,
0x162300  ,
0x14012C  ,
0x130965  ,
0x0E0FFE  ,
0x0D4000  ,
0x0C7001  ,
0x0B0028  ,
0x0A12D8  ,
0x090302  ,
0x081084  ,
0x0728B2  ,
0x041943  ,
0x020500  ,
0x010808  ,
0x00221C
	
	};




//void USART1_IRQHandler(void)
//{
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
//	{
//   USART_SendData(USART1,USART_ReceiveData(USART1));
//	 while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
//	}
//			
//}
	
void USART1_IRQHandler(void)  
{  
  uint16_t ch;
	unsigned int count;
  
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
  {   
			count = RegNum; 
		
      ch = USART_ReceiveData(USART1);
  	
			printf("%d",ch);
			if(ch == LOWCH1_112M)
			{
				WriteToLMX259x( count, LOW_CH1_112M);
				printf("WriteToLMX259x LOW_CH1_112M");
			}
			if(ch == HIGHCH1_112M)
			{
				WriteToLMX259x( count, HIGH_CH1_112M);
				printf("WriteToLMX259x HIGH_CH1_112M");
			}
			if(ch == LOWCH2_112M)
			{
				WriteToLMX259x( count, LOW_CH2_112M);
				printf("WriteToLMX259x LOW_CH2_112M");
			}
			if(ch == HIGHCH2_112M)
			{
				WriteToLMX259x( count, HIGH_CH2_112M);
				printf("WriteToLMX259x HIGH_CH2_112M");
			}
			
			if(ch == LOWCH1_56M)
			{
				printf("WriteToLMX259x LOWCH1_56M");
			}
			if(ch == LOWCH2_56M)
			{
				printf("WriteToLMX259x LOWCH2_56M");
			}
			if(ch == LOWCH3_56M)
			{
				printf("WriteToLMX259x LOWCH3_56M");
			}
			if(ch == LOWCH4_56M)
			{
				printf("WriteToLMX259x LOWCH4_56M");
			}
			
			if(ch == HIGHCH1_56M)
			{
				printf("WriteToLMX259x HIGHCH1_56M");
			}
			if(ch == HIGHCH2_56M)
			{
				printf("WriteToLMX259x HIGHCH2_56M");
			}
			if(ch == HIGHCH3_56M)
			{
				printf("WriteToLMX259x HIGHCH3_56M");
			}
			if(ch == HIGHCH4_56M)
			{
				printf("WriteToLMX259x HIGHCH4_56M");
			}
    }   
}  


/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
//PUTCHAR_PROTOTYPE
//{
//  /* Place your implementation of fputc here */
//  /* e.g. write a character to the USART */
//  USART_SendData(USART1, (uint8_t) ch);

//  /* Loop until the end of transmission */
//  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
//  {}

//  return ch;
//}



//int GetKey (void) 
//{

//	while (!(USART1->ISR & USART_FLAG_RXNE));

//	return ((int)(USART1->RDR & 0x1FF));

//}

