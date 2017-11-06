#include "ALL_Includes.h"
#include "temperature.h"

/****************************************************
函数功能：ADC初始化
输入参数：无
输出参数：无
备    注：

****************************************************/   
void T_Adc_Init(void) //ADC通道初始化
{

		
    ADC_InitTypeDef ADC_InitStuctrue;
		GPIO_InitTypeDef PORT_ADC;
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
		
		  
    PORT_ADC.GPIO_Pin=GPIO_Pin_0;  
    PORT_ADC.GPIO_Mode=GPIO_Mode_AN;  
    PORT_ADC.GPIO_PuPd=GPIO_PuPd_NOPULL;  
    GPIO_Init(GPIOA,&PORT_ADC);  

    ADC_InitStuctrue.ADC_Resolution=ADC_Resolution_12b;//12位精度  
    ADC_InitStuctrue.ADC_ContinuousConvMode=DISABLE;//单次ADC  
    ADC_InitStuctrue.ADC_ExternalTrigConvEdge=ADC_ExternalTrigConvEdge_None;  
    ADC_InitStuctrue.ADC_DataAlign=ADC_DataAlign_Right;//数据右对齐  
    ADC_InitStuctrue.ADC_ScanDirection=ADC_ScanDirection_Backward;//数据覆盖  
    ADC_Init(ADC1,&ADC_InitStuctrue);  
	
		//配置ADC采样的通道和采样周期  
    //PA0对应ADC通道0  
    //注意，采集的数据是否准确与采样时间有关系  
    ADC_ChannelConfig(ADC1,ADC_Channel_0,ADC_SampleTime_239_5Cycles);  
    //如果采集系统内部温度，则通道为16，同时要使能温度传感器  
    ADC_ChannelConfig(ADC1,ADC_Channel_16,ADC_SampleTime_239_5Cycles);  
    ADC_TempSensorCmd(ENABLE);		
   
		//校准  
    ADC_GetCalibrationFactor(ADC1);  
    //使能  
    ADC_Cmd(ADC1,ENABLE);     

}



int32_t Get_Temperature(void)
{
	
		int32_t temperature;
  	unsigned short adc_data;
				
		//等待ADC准备  
    while(ADC_GetFlagStatus(ADC1,ADC_FLAG_ADEN)==RESET);  
    //软件启动ADC转换  
    ADC_StartOfConversion(ADC1); 
	
		//等待ADC完成  
    while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);  
		//所得数据即为ADC数据 
		adc_data = ADC_GetConversionValue(ADC1);
		printf("%d\n",adc_data);
    //如果采集的是16通道，即芯片温度，则温度的值如下 
    //下面这段码，参考STM32F030数据手册（寄存器版）A.7.16 
    //出厂校准数据所存储的地址，30°C和110°C的ADC值 
    #define TEMP110_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFFF7C2)) 
    #define TEMP30_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFFF7B8)) 
    #define VDD_CALIB ((uint16_t) (330)) 
    #define VDD_APPLI ((uint16_t) (300)) 
    
    temperature = (((int32_t) ADC1->DR * VDD_APPLI / VDD_CALIB)- (int32_t) *TEMP30_CAL_ADDR ); 
    temperature = temperature * (int32_t)(110 - 30); 
    temperature = temperature / (int32_t)(*TEMP110_CAL_ADDR- *TEMP30_CAL_ADDR); 
		temperature = temperature + 30;
		temperature = (((int32_t) ADC1->DR)/1000 - 1.43)/4.3 + 25;
		printf("%d\n",temperature);
		
		return temperature;
}



u16 T_Get_Adc(void)   
{
//    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );  //ADC1,ADC通道3,第一个转换,采样时间为239.5周期                    
//    ADC_StartOfConversion(ADC1, ENABLE);     //使能指定的ADC1的软件转换启动功能
//    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
//    return ADC_GetConversionValue(ADC1);    //返回最近一次ADC1规则组的转换结果
		unsigned short adc_data;
		//等待ADC准备  
    while(ADC_GetFlagStatus(ADC1,ADC_FLAG_ADEN)==RESET);  
    //软件启动ADC转换  
    ADC_StartOfConversion(ADC1); 
	
		//等待ADC完成  
    while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);  
		//所得数据即为ADC数据 
		adc_data = ADC_GetConversionValue(ADC1);
		//printf("%d\n",adc_data);
		return adc_data;
}

//得到ADC采样内部温度传感器的值
//取10次,然后平均
u16 T_Get_Temp(void)
    {
    u16 temp_val=0;
    u8 t;
    for(t=0;t<10;t++)
        {
        temp_val+=T_Get_Adc();      //TampSensor
        delay_ms(5);
        }
    return temp_val/10;
    }

//获取通道ch的转换值
//取times次,然后平均
u16 T_Get_Adc_Average(u8 times)
{
    u32 temp_val=0;
    u8 t;
    for(t=0;t<times;t++)
    {
        temp_val+=T_Get_Adc();
        delay_ms(5);
    }
    return temp_val/times;
}      

//得到温度值
//返回值:温度值(扩大了100倍,单位:℃.)
short Get_Temprate(void)    //获取内部温度传感器温度值
{
    u32 adcx;
    short result;
    double temperate;
    adcx=T_Get_Adc_Average(20);  //读取通道16,20次取平均
    temperate=(float)adcx*(3.3/4096);       //电压值 
    temperate=(1.43-temperate)/0.0043+25;   //转换为温度值     
    result=temperate*100;                  //扩大100倍.
		printf("%d",result);
    return result;
}


