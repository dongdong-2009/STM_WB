#include "stm32f0xx.h"
#include "LMX259x.h"

#define high    1
#define low     0
#define RegNum			44
#define RegNum2594			115
/****************************************************************/
#define  SCL_PIN		GPIO_Pin_4        //LMX_SCK  
#define  WDATA_PIN	GPIO_Pin_3         //LMX_SDI 
#define  CS_PIN			GPIO_Pin_2         //LMX_CSB 	
#define  RDATA_PIN	GPIO_Pin_1         //LMX_RDATA 

#define  HIGH_LOW	  GPIO_Pin_5         //LMX_RDATA 

#define LMX259x_Port					GPIOA
#define LMX259x_GPIO_CLK   RCC_AHBPeriph_GPIOA 



#define  CS_1 	LMX259x_Port->BSRR = CS_PIN;	//置1
#define		 CS_0 	LMX259x_Port->BRR = CS_PIN;	//置0																					                           


#define	 SCL_1	LMX259x_Port->BSRR = SCL_PIN;	//置1
#define		 SCL_0	LMX259x_Port->BRR = SCL_PIN;

#define WDATA_1	LMX259x_Port->BSRR = WDATA_PIN;
#define		WDATA_0	LMX259x_Port->BRR = WDATA_PIN;

#define RDATA	((LMX259x_Port->IDR) & RDATA_PIN);
//#define RESET_1	LMX259x_Port->BSRR = RDATA_PIN;
//#define		RESET_0	LMX259x_Port->BRR = RDATA_PIN;
//ref 40 pfd 100 out 1845
//unsigned	int	InibufLow[RegNum] = 
//{
//	
//	0x00221E  ,
//0x4001AF   ,
//0x3E0000   ,
//0x3D0001   ,
//0x3B0000   ,
//0x3003FC   ,
//0x2F00D4   ,
//0x2E0FA2   ,
//0x2DD4FE   ,
//0x2C7378   ,
//0x2B0000   ,
//0x2A0000   ,
//0x29FFFF   ,
//0x28FFFF   ,
//0x278204   ,
//0x260024   ,
//0x254000   ,
//0x240C11   ,
//0x23021B   ,
//0x22C3F0   ,
//0x214210   ,
//0x204210   ,
//0x1F0601   ,
//0x1E0034   ,
//0x1D0084   ,
//0x1C2924   ,
//0x190000   ,
//0x180509   ,
//0x178842   ,
//0x162300   ,
//0x14012C   ,
//0x130965   ,
//0x0E0FFE   ,
//0x0D4000   ,
//0x0C7001   ,
//0x0B0028   ,
//0x0A12D8   ,
//0x090302   ,
//0x081084   ,
//0x0728B2   ,
//0x041943   ,
//0x020500   ,
//0x010808   ,
//0x00221C




//	};




//	
//	//ref 40 pfd 100 out 7380
//	
//unsigned	int	InibufHigh[RegNum] = 
//{
//	
//	0x00221E  ,
//0x4001AF   ,
//0x3E0000   ,
//0x3D0001   ,
//0x3B0000   ,
//0x3003FC   ,
//0x2F08D4   ,
//0x2E0FA2   ,
//0x2DD4FE   ,
//0x2C7378   ,
//0x2B0000   ,
//0x2A0000   ,
//0x29FFFF   ,
//0x28FFFF   ,
//0x278204   ,
//0x260024   ,
//0x255000   ,
//0x240811   ,
//0x23021B   ,
//0x22C3F0   ,
//0x214210   ,
//0x204210   ,
//0x1F0401   ,
//0x1E0035   ,
//0x1D0084   ,
//0x1C2924   ,
//0x190000   ,
//0x180509   ,
//0x178842   ,
//0x162300   ,
//0x14012C   ,
//0x130965   ,
//0x0E0FFE   ,
//0x0D4000   ,
//0x0C7001   ,
//0x0B0028   ,
//0x0A12D8   ,
//0x090302   ,
//0x081084   ,
//0x0728B2   ,
//0x041943   ,
//0x020500   ,
//0x010808   ,
//0x00221C



//	
//	};	

	
	

void static delay(void)				 	
{
   unsigned int T;
   for (T = 0;T<0x800 ; T++);
}
unsigned char ReadFromLMX259x(unsigned short Addr )
{
	unsigned	char ValueBack=0;
    unsigned	char	i = 0;




	delay();
	SCL_0;
	CS_1;
	WDATA_0;
	delay();
	/******READ BACK MODE****/
	
	CS_0;
	
	WDATA_1;
	SCL_1;
	delay();
	SCL_0;

	WDATA_0;
	delay();
	SCL_1;
	delay();
	SCL_0;
	delay();
	SCL_1;
	delay();
	SCL_0;
	/*********READ BACK MODE**********/
	 
		for(i=0; i<13; i++)
		{
			if(0x1000 == ( Addr&0x1000))
			{
				WDATA_1;	  //Send one to SDO pin
			}
			else
			{
				WDATA_0;	  //Send zero to SDO pin
			}
			delay();
			SCL_1;
			delay();
			Addr <<= 1;	//Rotate data
			SCL_0;
		}
		
		for(i=0;i<8;i++)
		{
			delay();
			SCL_1;
			//ValueBack+=RDATA;
			delay();
			SCL_0;	
			ValueBack<<=1;
		
		}
		
		

	delay();
	CS_1;
	delay();
		
		return ValueBack;

}
void WriteToLMX259x(unsigned char count, unsigned int *buf)
{
	unsigned	long	ValueToWrite = 0;
    unsigned	char	i = 0;
	unsigned	char	j = 0;

	//SET_DATA_OUT();

	delay();
	SCL_0;
	WDATA_0;
	CS_1;
	delay();
	

	for(i=0;i<count;i++)
 	{
			CS_0;
	 	ValueToWrite = *(buf + i );
		for(j=0; j<24; j++)
		{
			if(0x800000 == (ValueToWrite & 0x800000))
			{
				WDATA_1;	  //Send one to SDO pin
			}
			else
			{
				WDATA_0;	  //Send zero to SDO pin
			}
			delay();
			SCL_1;
			delay();
			ValueToWrite <<= 1;	//Rotate data
			SCL_0;
		}
		ValueToWrite=0;
		CS_1;
		delay();
	}
	WDATA_0;
	delay();
	
	delay();
}

void WriteToLMX259xRegister( unsigned long V)
{
	unsigned	long	ValueToWrite = V;

	unsigned	char	j = 0;

	//SET_DATA_OUT();

	delay();
	SCL_0;
	CS_0;
	delay();

	
	 	
		for(j=0; j<24; j++)
		{
			if(0x800000 == (ValueToWrite & 0x800000))
			{
				WDATA_1;	  //Send one to SDO pin
			}
			else
			{
				WDATA_0;	  //Send zero to SDO pin
			}
			delay();
			SCL_1;
			delay();
			ValueToWrite <<= 1;	//Rotate data
			SCL_0;
		}
	
	WDATA_0;
	delay();
	CS_1;

	delay();
}

void LMX259xGPIO_Ini(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;

	  RCC_AHBPeriphClockCmd(LMX259x_GPIO_CLK , ENABLE);
   
    GPIO_InitStructure.GPIO_Pin = SCL_PIN|CS_PIN|WDATA_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	
    GPIO_Init(LMX259x_Port, &GPIO_InitStructure);
	
	CS_1;  // 初始化后立即拉高CS
	delay();
	SCL_0;
	WDATA_0;
	
	delay();
//	RESET_1;
	
	delay();
//	RESET_0;


	
}




void Init_LMX259x(void)
{
	//unsigned char i=0;
	//unsigned char tem=0;
	
	
		LMX259xGPIO_Ini();

//WriteToLMX259x(RegNum2594, Inibuf2594);
	
//	for(i=0;i<80;i++)
//	{
//		delay();
//		tem=GPIO_ReadInputDataBit(LMX259x_Port,HIGH_LOW);
//		delay();
//	}
//	
//	if(tem)
//	{
//	WriteToLMX259x(RegNum, InibufHigh);
//	
//	}
//	else WriteToLMX259x(RegNum, InibufLow);
	

	//	WriteToLMX259x(RegNum, HIGH_CH1_112M);
		//WriteToLMX259x(RegNum, LOW_CH1_112M);


}



