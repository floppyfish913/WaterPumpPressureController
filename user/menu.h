#include "stm32f0xx_conf.h"
#ifndef MENU_H
#define MENU_H
typedef enum {START_SCREEN = 0,PUMP_STATUS = 1, CURRENT_PRESSURE = 2, MAX_PRESSURE = 3, MIN_PRESSURE = 4, DELAY_TIMER = 5, SAVE_CONFIG = 6, CONFIG_SAVED = 7, CONFIG_DISCARD = 8} STATES;

typedef enum {PUMP_STOP = 2, PUMP_START=1, PUMP_IDLE = 0} PUMP_STATE;
typedef enum {PUMP_OVER_PRESSURE = 2, PUMP_UNDER_PRESSURE= 1, PUMP_NORMAL = 0} PUMP_FLAG;


void menuStateMachine();

void MenuControl();

void DelayTimer();

void HysteresisSwitcher();

#endif
