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
////ref 40 pfd 66 out 2200  注意Inband Spur
//	unsigned	int	InibufLow[RegNum] = 
//{
//0x00221E  ,
//0x4001AF  ,
//0x3E0000  ,
//0x3D0001  ,
//0x3B0000  ,
//0x3003FC  ,
//0x2F00D4  ,
//0x2E0FA2  ,
//0x2DD9E7  ,
//0x2C01AC  ,
//0x2B0000  ,
//0x2A0000  ,
//0x29FFFF  ,
//0x28FFFF  ,
//0x278204  ,
//0x260042  ,
//0x254000  ,
//0x240C11  ,
//0x23021B  ,
//0x22C3F0  ,
//0x214210  ,
//0x204210  ,
//0x1F0601  ,
//0x1E0034  ,
//0x1D0084  ,
//0x1C2924  ,
//0x190000  ,
//0x180509  ,
//0x178842  ,
//0x162300  ,
//0x14012C  ,
//0x130965  ,
//0x0E0FFE  ,
//0x0D4000  ,
//0x0C7001  ,
//0x0B0038  ,
//0x0A12D8  ,
//0x090302  ,
//0x081084  ,
//0x0728B2  ,
//0x041943  ,
//0x020500  ,
//0x010808  ,
//0x00221C





//	
//	};
	
//	//ref 40 pfd 80 out 2200  注意Inband Spur
//	unsigned	int	InibufLow[RegNum] = 
//{
//0x00221E  ,
//0x4001AF   ,
//0x3E0000   ,
//0x3D0001   ,
//0x3B0000   ,
//0x3003FC   ,
//0x2F00D4   ,
//0x2E0FA2   ,
//0x2D6040   ,
//0x2C8165   ,
//0x2B0000   ,
//0x2A0000   ,
//0x29FFFF   ,
//0x28FFFF   ,
//0x278204   ,
//0x260036   ,
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
//0x0B0018   ,
//0x0A10D8   ,
//0x090B02   ,
//0x081084   ,
//0x0728B2   ,
//0x041943   ,
//0x020500   ,
//0x010808   ,
//0x00221C

//	
//	};




//	//ref 40 pfd 120 out 2200  注意Inband Spur
//	unsigned	int	InibufLow[RegNum] = 
//{
//0x00229E  ,
//0x4001AF   ,
//0x3E0000   ,
//0x3D0001   ,
//0x3B0000   ,
//0x3003FC   ,
//0x2F00D4   ,
//0x2E0FA2   ,
//0x2D9580   ,
//0x2C5643   ,
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
//0x0A1358   ,
//0x090302   ,
//0x081084   ,
//0x0728B2   ,
//0x041943   ,
//0x020500   ,
//0x010808   ,
//0x00229C


//	
//	};

//	//ref 40 pfd 100 out 2185  注意Inband Spur
//	unsigned	int	InibufLow[RegNum] = 
//{
//0x00221E  ,
//0x4001AF   ,
//0x3E0000   ,
//0x3D0001   ,
//0x3B0000   ,
//0x3003FC   ,
//0x2F00D4   ,
//0x2E0FA2   ,
//0x2D3055   ,
//0x2CDB2A   ,
//0x2B0000   ,
//0x2A0000   ,
//0x29FFFF   ,
//0x28FFFF   ,
//0x278204   ,
//0x26002A   ,
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
//	
//	};
//	
//	/*
	
	
	
	//ref 40 pfd 100 out 2200
unsigned	int	InibufLow[RegNum] = 
{
0x00221E  ,
0x4001AF  ,
0x3E0000  ,
0x3D0001  ,
0x3B0000  ,
0x3003FC  ,
0x2F00D4  ,
0x2E0FA2  ,
0x2DE69A  ,
0x2C011D  ,
0x2B0000  ,
0x2A0000  ,
0x29FFFF  ,
0x28FFFF  ,
0x278204  ,
0x26002C  ,
0x254000  ,
0x240C11  ,
0x23021B  ,
0x22C3F0  ,
0x214210  ,
0x204210  ,
0x1F0601  ,
0x1E0034  ,
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
////ref 40 pfd 100 out 2199
//unsigned	int	InibufLow[RegNum] = 
//{
//0x00221E  ,
//0x4001AF  ,
//0x3E0000  ,
//0x3D0001  ,
//0x3B0000  ,
//0x3003FC  ,
//0x2F00D4  ,
//0x2E0FA2  ,
//0x2DB367  ,
//0x2CFDEA  ,
//0x2B0000  ,
//0x2A0000  ,
//0x29FFFF  ,
//0x28FFFF  ,
//0x278204  ,
//0x26002A  ,
//0x254000  ,
//0x240C11  ,
//0x23021B  ,
//0x22C3F0  ,
//0x214210  ,
//0x204210  ,
//0x1F0601  ,
//0x1E0034  ,
//0x1D0084  ,
//0x1C2924  ,
//0x190000  ,
//0x180509  ,
//0x178842  ,
//0x162300  ,
//0x14012C  ,
//0x130965  ,
//0x0E0FFE  ,
//0x0D4000  ,
//0x0C7001  ,
//0x0B0028  ,
//0x0A12D8  ,
//0x090302  ,
//0x081084  ,
//0x0728B2  ,
//0x041943  ,
//0x020500  ,
//0x010808  ,
//0x00221C

//	};


////ref 40 pfd 100 out 2195
//	unsigned	int	InibufLow[RegNum] = 
//{
//0x00221E  ,
//0x4001AF   ,
//0x3E0000   ,
//0x3D0001   ,
//0x3B0000   ,
//0x3003FC   ,
//0x2F00D4   ,
//0x2E0FA2   ,
//0x2D8033   ,
//0x2CFAB7   ,
//0x2B0000   ,
//0x2A0000   ,
//0x29FFFF   ,
//0x28FFFF   ,
//0x278204   ,
//0x26002A   ,
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

	
	//ref 40 pfd 100 out 8623
	
unsigned	int	InibufHigh[RegNum] = 
{
0x00221E  ,
0x4000AF   ,
0x3E0000   ,
0x3D0001   ,
0x3B0000   ,
0x3003FC   ,
0x2F08D4   ,
0x2E0FA3   ,
0x2DC3C5   ,
0x2C8F42   ,
0x2B0000   ,
0x2A0000   ,
0x29FFFF   ,
0x28FFFF   ,
0x278204   ,
0x26002A   ,
0x255000   ,
0x240811   ,
0x23021B   ,
0x22C3F0   ,
0x214210   ,
0x204210   ,
0x1F0401   ,
0x1E0035   ,
0x1D0084   ,
0x1C2924   ,
0x190000   ,
0x180509   ,
0x178842   ,
0x162300   ,
0x14012C   ,
0x130965   ,
0x0E0FFE   ,
0x0D4000   ,
0x0C7001   ,
0x0B0028   ,
0x0A12D8   ,
0x090302   ,
0x081084   ,
0x0728B2   ,
0x041943   ,
0x020500   ,
0x010808   ,
0x00221C   



	
	};		
	
	
	//ref 100 pfd 200 out 8623
	
	/*
	
unsigned	int	Inibuf2594[RegNum2594] = 
{	
0x700000  ,
0x6F0000  ,
0x6E0000  ,
0x6D0000  ,
0x6C0000  ,
0x6B0000  ,
0x6A0000  ,
0x690021  ,
0x680000  ,
0x670000  ,
0x663F80  ,
0x650011  ,
0x640000  ,
0x630000  ,
0x620200  ,
0x610888  ,
0x600000  ,
0x5F0000  ,
0x5E0000  ,
0x5D0000  ,
0x5C0000  ,
0x5B0000  ,
0x5A0000  ,
0x590000  ,
0x580000  ,
0x570000  ,
0x560000  ,
0x55EE00  ,
0x540001  ,
0x530000  ,
0x523900  ,
0x510000  ,
0x506666  ,
0x4F0026  ,
0x4E0003  ,
0x4D0000  ,
0x4C000C  ,
0x4B0800  ,
0x4A0000  ,
0x49003F  ,
0x480001  ,
0x470081  ,
0x46C350  ,
0x450000  ,
0x4403E8  ,
0x430000  ,
0x4201F4  ,
0x410000  ,
0x401388  ,
0x3F0000  ,
0x3E0322  ,
0x3D00A8  ,
0x3C0000  ,
0x3B0001  ,
0x3A8001  ,
0x390020  ,
0x380000  ,
0x370000  ,
0x360000  ,
0x350000  ,
0x340820  ,
0x330080  ,
0x320000  ,
0x314180  ,
0x300300  ,
0x2F0300  ,
0x2E07FD  ,
0x2DC8DF  ,
0x2C1FA3  ,
0x2B3333  ,
0x2A0EE7  ,
0x290000  ,
0x280000  ,
0x270001  ,
0x267D00  ,
0x250304  ,
0x24002B  ,
0x230004  ,
0x220000  ,
0x211E21  ,
0x200393  ,
0x1F43EC  ,
0x1E318C  ,
0x1D318C  ,
0x1C0488  ,
0x1B0002  ,
0x1A0DB0  ,
0x190624  ,
0x18071A  ,
0x17007C  ,
0x160001  ,
0x150401  ,
0x14E048  ,
0x1327B7  ,
0x120064  ,
0x11012C  ,
0x100080  ,
0x0F064F  ,
0x0E1E70  ,
0x0D4000  ,
0x0C5001  ,
0x0B0018  ,
0x0A10D8  ,
0x091604  ,
0x082000  ,
0x0740B2  ,
0x06C802  ,
0x0500C8  ,
0x040A43  ,
0x030642  ,
0x020500  ,
0x010808  ,
0x00251C  
	};
	
	*/
	
	
unsigned	int	Inibuf2594[RegNum2594] = 
{	
0x00251E	  ,
0x00251C		,
0x700000	  ,
0x6F0000    ,
0x6E0000    ,
0x6D0000    ,
0x6C0000    ,
0x6B0000    ,
0x6A0000    ,
0x690021    ,
0x680000    ,
0x670000    ,
0x663F80    ,
0x650011    ,
0x640000    ,
0x630000    ,
0x620200    ,
0x610888    ,
0x600000    ,
0x5F0000    ,
0x5E0000    ,
0x5D0000    ,
0x5C0000    ,
0x5B0000    ,
0x5A0000    ,
0x590000    ,
0x580000    ,
0x570000    ,
0x560000    ,
0x55EE00    ,
0x540001    ,
0x530000    ,
0x523900    ,
0x510000    ,
0x506666    ,
0x4F0026    ,
0x4E0003    ,
0x4D0000    ,
0x4C000C    ,
0x4B0840    ,
0x4A0000    ,
0x49003F    ,
0x480001    ,
0x470081    ,
0x46C350    ,
0x450000    ,
0x4403E8    ,
0x430000    ,
0x4201F4    ,
0x410000    ,
0x401388    ,
0x3F0000    ,
0x3E0322    ,
0x3D00A8    ,
0x3C0000    ,
0x3B0001    ,
0x3A8001    ,
0x390020    ,
0x380000    ,
0x370000    ,
0x360000    ,
0x350000    ,
0x340820    ,
0x330080    ,
0x320000    ,
0x314180    ,
0x300300    ,
0x2F0300    ,
0x2E07FC    ,
0x2DC0DF    ,
0x2C1FA3    ,
0x2B3333    ,
0x2A0EE7    ,
0x290000    ,
0x280000    ,
0x270001    ,
0x267D00    ,
0x250304    ,
0x24002B    ,
0x230004    ,
0x220000    ,
0x211E21    ,
0x200393    ,
0x1F43EC    ,
0x1E318C    ,
0x1D318C    ,
0x1C0488    ,
0x1B0002    ,
0x1A0DB0    ,
0x190624    ,
0x18071A    ,
0x17007C    ,
0x160001    ,
0x150401    ,
0x14E048    ,
0x1327B7    ,
0x120064    ,
0x11012C    ,
0x100080    ,
0x0F064F    ,
0x0E1E70    ,
0x0D4000    ,
0x0C5001    ,
0x0B0018    ,
0x0A12D8    ,
0x090604    ,
0x082000    ,
0x0740B2    ,
0x06C802    ,
0x0500C8    ,
0x040A43    ,
0x030642    ,
0x020500    ,
0x010808    ,
0x00251C



 
	};
	
		
	
	
	

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
	unsigned char i=0;
	unsigned char tem=0;
	
	
		LMX259xGPIO_Ini();

//WriteToLMX259x(RegNum2594, Inibuf2594);
	
	for(i=0;i<80;i++)
	{
		delay();
		tem=GPIO_ReadInputDataBit(LMX259x_Port,HIGH_LOW);
		delay();
	}
	
	if(tem)
	{
	WriteToLMX259x(RegNum, InibufHigh);
	
	}
	else WriteToLMX259x(RegNum, InibufLow);
	

		




}



