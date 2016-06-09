#include "OS.h"
#include "IO.h"
#include "hd44780.h"
#include "pressure.h"
#include <stdio.h>

void InitSysTick(){

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    TIM_TimeBaseInitTypeDef Sys_Tick;
    Sys_Tick.TIM_CounterMode = TIM_CounterMode_Up;
    Sys_Tick.TIM_Prescaler = 15; // 1ms @ 8MHz
    Sys_Tick.TIM_Period = 999;
    Sys_Tick.TIM_ClockDivision = TIM_CKD_DIV1;
    Sys_Tick.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3,&Sys_Tick);
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);

    NVIC_InitTypeDef SysTickITReg;
    SysTickITReg.NVIC_IRQChannel = TIM3_IRQn;
    SysTickITReg.NVIC_IRQChannelCmd = ENABLE;
    SysTickITReg.NVIC_IRQChannelPriority= 0;
    NVIC_Init(&SysTickITReg);

    TIM_Cmd(TIM3,ENABLE);

}


void TIM3_IRQHandler(){
    if(TIM_GetITStatus(TIM3,TIM_IT_Update)){
        SystemTime++;
        Tick=1;
        }
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);

}


void BlockingDelayMS(int ms){
        uint64_t WaitUntil = SystemTime + ms;
        while(SystemTime < WaitUntil);
        return;
}

uint64_t GetSystemTime(){
    return SystemTime;
};

void OSInitDevices(){
    //************************Init IO Ports********************
    //************************Init connected modules***********
    ClockConfiguration();
    RelayOutputInit();
    ButtonInit();
    LCDInit();
    PressureSensorInit();

};

void OSStart(){
    SystemTime = 0;
    Tick = 0;
    InitSysTick();

    OSInitDevices();

    OSStartScheduler();
}

void OSStartScheduler(){
    uint64_t Time = 0;
    while(1){
            //Non-Preemtive Round Robin task manager
        if(Tick){
                Time = GetSystemTime();


                if(!(Time % 7)){
                            HysteresisSwitcher();
                            }
                if(!(Time % 251)){
                            menuStateMachine();
                            }
                if(!(Time % 51)){
                            MenuControl();
                            }
                if(!(Time % 3799)){
                            DelayTimer();
                            }

        Tick = 0;
        }

   }
}



