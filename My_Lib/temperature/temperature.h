#ifndef __TEMPERATURE_H
#define __TEMPERATURE_H 

#include "ALL_Includes.h"

void T_Adc_Init(void);
int32_t Get_Temperature(void);
short Get_Temprate(void);
u16 T_Get_Adc_Average(u8 times);
u16 T_Get_Temp(void);
u16 T_Get_Adc(void);


#endif
