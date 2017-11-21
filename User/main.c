#include "ALL_Includes.h"//包含所需的头文件

int main(void)
{	
	Delay_Init(48);
	//LED_Init();
	USART1_Init();
	T_Adc_Init();
	//Init_ADF5355();	
	Init_LMX259x();

	while (1)
	{
		delay_ms(1000);
		//Get_Temprate();	
	}
	
}

int fputc(int ch, FILE *f)

{

USART_SendData(USART1, (unsigned char) ch);// USART1 ???? USART2 ?

while (!(USART1->ISR & USART_FLAG_TXE));

return (ch);

}



int GetKey (void) {

while (!(USART1->ISR & USART_FLAG_RXNE));

return ((int)(USART1->TDR & 0x1FF));

}
	

