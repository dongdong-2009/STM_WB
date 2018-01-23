//=============================================================================
//�ļ����ƣ�usart1.c
//���ܸ�Ҫ������1�����ļ�
//����ʱ�䣺2014-01-04
//=============================================================================
#include "ALL_Includes.h"
#include "USART1.h"

/* USART��ʼ�� */
void USART1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);  //ʹ��GPIOA��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//ʹ��USART��ʱ��
	/* USART1�Ķ˿����� */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);//����PA9�ɵڶ���������	TX
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);//����PA10�ɵڶ���������  RX	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	

	/* USART1�Ļ������� */
	USART_InitStructure.USART_BaudRate = 115200;              //������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStructure);		
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);           //ʹ�ܽ����ж�
	USART_Cmd(USART1, ENABLE);                             //ʹ��USART1

	/* USART1��NVIC�ж����� */
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPriority = 0x02;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
			
}

//=============================================================================
//�ļ����ƣ�
//���ܸ�Ҫ��USART1�жϺ���
//����˵������
//�������أ���
//=============================================================================
int i = 0, j = 0, num = 0,tim; //ȫ�ֱ���
unsigned int WriteLMX259x[RegNum] = {0}; //ȫ�ֱ���

void USART1_IRQHandler(void)
{
  uint16_t ch;
	int ret;

  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
		ch = USART_ReceiveData(USART1);
		if(num < 44 * 3)
			{				
				//printf("ch = %x \n", ch);
				tim = 1;
				i = num/3;
				j = num%3;
				num++;
				WriteLMX259x[i] = WriteLMX259x[i] + (ch << (j * 8));
				//printf("i=%d j=%d num=%d %x\n",i, j, num, WriteLMX259x[i]);
			}
			else
			{
				WriteToLMX259x(RegNum, WriteLMX259x);
				i = 0;
				j = 0;
				num = 0;
				for(ret = 0; ret < 44; ret++)
				{
					//printf("WriteLMX259x[%d] = %x\n", ret, WriteLMX259x[ret]);
					WriteLMX259x[ret] = 0;
				}
			}
  }  
} 

