#include "stm32f0xx.h"
#include "ADF5355.h"

#define high    1
#define low     0


/*******************************PA脚驱动adf5355和两个射频开关*********************************/
#define  SCL_PIN	GPIO_Pin_3         //PB6
#define  WDATA_PIN	GPIO_Pin_2          //PB5
#define  LE_PIN		GPIO_Pin_1         //PB4
//#define  CE_PIN		GPIO_Pin_6         //PB3
#define  LDET_PIN		GPIO_Pin_4         //PB7

#define AD5355_Port					GPIOA
#define AD5355_GPIO_CLK   RCC_AHBPeriph_GPIOA 


//#define  CE_1 	AD5355_Port->BSRRL = CE_PIN;	//置1
//#define		 CE_0 	AD5355_Port->BSRRH = CE_PIN;	//置0																					                           


#define	 SCL_1	AD5355_Port->BSRR = SCL_PIN;	//置1
#define		 SCL_0	AD5355_Port->BRR = SCL_PIN;

#define WDATA_1	AD5355_Port->BSRR = WDATA_PIN;
#define		WDATA_0	AD5355_Port->BRR = WDATA_PIN;

#define LE_1	AD5355_Port->BSRR = LE_PIN;
#define	 	LE_0	AD5355_Port->BRR = LE_PIN;


//unsigned	int	Inibuf[13] = 
//{
// 0x1041C    ,
// 0x61300B   ,
// 0xC00CBA   ,
// 0x908BCC9  ,
// 0x102D0428 ,
// 0x10000067 ,
// 0x3540A076 ,
// 0x800025   ,
// 0x30008984 ,
// 0x3 ,
// 0xC28FFFF2 ,
// 0x1028F51  ,
// 0x200c20   



//};

unsigned	int	Inibuf1[13] = 
{
    0x41C     ,
0x61300B      ,
0xC0193A      ,
0x1110FCC9    ,
0x102D0428    ,
0x12000007    ,
0x3540C076    ,
0x800025      ,
0x34008984    ,
0x3           ,
0x12          ,
0x1           



};

unsigned	int	Inibuf2[1] = 
{

0x200AA0 


};

//unsigned	int	Inibuf[13] = 
//{
//0x1041C       ,
//0x61300B      ,
//0xC0067A      ,
//0x5047CC9     ,
//0x102D0428    ,
//0x12000067    ,
//0x35402476    ,
//0x800025      ,
//0x32008984    ,
//0x3           ,
//0x12          ,
//0x1           ,
//0x202940      


//};

//unsigned	int	Inibuf[13] = 
//{
// 0x1041C     ,
//0x61300B     ,
//0xC0193A     ,
//0x908BCC9    ,
//0x102D0428   ,
//0x120000E7   ,
//0x35414076   ,
//0x800025     ,
//0x2c008984   ,
//0x3          ,
//0xE147FFF2   ,
//0x8147A1     ,
//0x610     



//};





void ADF5355_GPIO_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;

	  RCC_AHBPeriphClockCmd(AD5355_GPIO_CLK , ENABLE);
   
    GPIO_InitStructure.GPIO_Pin = SCL_PIN|LE_PIN|WDATA_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	
    GPIO_Init(AD5355_Port, &GPIO_InitStructure);
}
void delay(void)				 	
{
   unsigned int i;
   for (i = 0;i<0x800 ; i++);
}

void WriteToADF5355(unsigned char count, unsigned int *buf)
{
	unsigned	long	ValueToWrite = 0;
    unsigned	char	i = 0;
	unsigned	char	j = 0;

	//SET_DATA_OUT();

	delay();
	SCL_0;
	WDATA_0;
	LE_1;
	delay();
	

	for(i=0;i<count;i++)
 	{
			LE_0;
	 	ValueToWrite = *(buf + i );
		for(j=0; j<32; j++)
		{
			if(0x80000000 == (ValueToWrite & 0x80000000))
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
		delay();
		LE_1;
		delay();
	}
	WDATA_0;
	delay();
	
	delay();
}



void Init_ADF5355(void)
{
int i=0;
		ADF5355_GPIO_Init();
		/*WriteToLMK04828Register( 0x000090);
	
		delay();
		WriteToLMK04828Register( 0x000010);
		delay();
		WriteToLMK04828Register( 0x014A36);
	  */

WriteToADF5355(13, Inibuf1);
		for(i=0;i<800;i++)
	{
	
		delay();
	
	
	}
	WriteToADF5355(1, Inibuf2);
	//WriteToLMK04828Register( 0x002001);
		




}



