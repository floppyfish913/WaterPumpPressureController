#include "stm32f0xx_conf.h"

#define BUTTON_UP           0x08
#define BUTTON_DOWN         0x04
#define BUTTON_SELECT       0x02
#define BUTTON_STARTSTOP    0x01





void ButtonInit();

void RelayOutputInit();

char ReadButtons();

void SetRelayState(FunctionalState status);

FunctionalState GetRelayState();
