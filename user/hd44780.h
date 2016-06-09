#include "stm32f0xx_conf.h"

 void LCDInitPins8bitMode();
 void LCDInit();

 void LCDWrite(char c);

 void LCDWriteCMD(char command);

 void LCDWriteRow(char rowNum,char * row);

 void LCDCursorToXY(char x,char y);
