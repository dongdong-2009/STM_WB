#ifndef	LMX259x_H
#define  LMX259x_H




unsigned char ReadFromLMX259x(unsigned short Addr );
void WriteToLMX259x(unsigned char count, unsigned int *buf);
void WriteToLMX259xRegister( unsigned long V);
void LMX259xGPIO_Ini(void);
void Init_LMX259x(void);
   
	 
#endif
