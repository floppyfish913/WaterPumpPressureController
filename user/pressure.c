#include "pressure.h"

void PressureSensorInit(){

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);

    GPIO_InitTypeDef ADC_IO;
    ADC_InitTypeDef adc;

    ADC_IO.GPIO_Mode=GPIO_Mode_AN;
    ADC_IO.GPIO_Pin = GPIO_Pin_1;
    ADC_IO.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB,&ADC_IO);


    ADC_StructInit(&adc);
    adc.ADC_DataAlign = ADC_DataAlign_Right;
    adc.ADC_ContinuousConvMode = DISABLE;
    adc.ADC_Resolution = ADC_Resolution_10b;
    ADC_Init(ADC1,&adc);
    ADC_Cmd(ADC1,ENABLE);

    ADC_ChannelConfig(ADC1,ADC_Channel_9,ADC_SampleTime_55_5Cycles);

};
uint16_t ReadPressureSensor(){

    ADC_StartOfConversion(ADC1);
    while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
    return ADC_GetConversionValue(ADC1);

};


uint16_t getPressureValue_mBAR(){
    uint16_t average=0;
    uint16_t PressureADC = 0;
    float Pressure = 0;
    char i;

    for(i=0;i<BUFFER_SIZE;i++){
        average += ReadPressureSensor();
    }
    average /= BUFFER_SIZE;

    if ((average - PRESSURE_OFFSET) < 0) PressureADC = 0;
    else
        PressureADC = average - PRESSURE_OFFSET;

    Pressure = (float)PressureADC * ADC_LSB_mV / PRESSURE_GRAD;

    return (uint16_t)Pressure;
}


