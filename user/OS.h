#include "stm32f0xx_conf.h"

uint64_t SystemTime;
char Tick;


void InitSysTick();
void BlockingDelayMS(int ms);
uint64_t GetSystemTime();
void OSStart();
void OSInitDevices();
void OSStartScheduler();
