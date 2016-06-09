#include "config.h"
#define CONFIGURATION_PAGE 0x08007C00

extern uint16_t OptionDelayTime;
extern uint16_t PressureMin;
extern uint16_t PressureMax;


void SaveConfiguration(){
    FLASH_SetLatency(FLASH_Latency_0);
    FLASH_Unlock();
    FLASH_ErasePage(CONFIGURATION_PAGE);
    FLASH_ProgramWord(CONFIGURATION_PAGE,(uint32_t) PressureMax);
    FLASH_ProgramWord(CONFIGURATION_PAGE + 0x04,(uint32_t) PressureMin);
    FLASH_ProgramWord(CONFIGURATION_PAGE + 0x08,(uint32_t) OptionDelayTime);
    FLASH_Lock();
};

void LoadConfiguration(){

    uint32_t * CONF_PRESSURE_MAX = CONFIGURATION_PAGE;
    uint32_t * CONF_PRESSURE_MIN = CONFIGURATION_PAGE + 0x04;
    uint32_t * CONF_DELAY = CONFIGURATION_PAGE +  0x08;

    if(*CONF_PRESSURE_MAX > 5000)
            PressureMax = 1500;
    else
        PressureMax = *CONF_PRESSURE_MAX;
    if(*CONF_PRESSURE_MIN > 5000)
            PressureMin = 500;
    else
        PressureMin = *CONF_PRESSURE_MIN;
    if(*CONF_DELAY > 300)
            OptionDelayTime = 10;
    else
        OptionDelayTime = *CONF_DELAY;

};



void ClockConfiguration(){

    RCC_HSEConfig(RCC_HSE_ON);
    while(!RCC_WaitForHSEStartUp());

    RCC_PLLConfig(RCC_PLLSource_HSE,RCC_PLLMul_2);
    RCC_PCLKConfig(RCC_HCLK_Div1);

    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    RCC_PLLCmd(ENABLE);





}
