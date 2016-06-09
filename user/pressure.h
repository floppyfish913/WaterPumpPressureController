#include "stm32f0xx_conf.h"
#define BUFFER_SIZE 8
#define ADC_LSB_mV 3.2226
#define PRESSURE_OFFSET 128
#define PRESSURE_GRAD 0.8



void PressureSensorInit();
uint16_t ReadPressureSensor();

uint16_t getPressureValue_mBAR();
