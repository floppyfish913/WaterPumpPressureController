#include "hd44780.h"

 void LCDInitPins8bitMode(){
 // SET A Port to output
 // P10|P9|P8|P7|P6|P5|P4|P3|P2|P1|P0|
 // EN|RW|RS|D7|D6|D5|D4|D3|D2|D1|D0
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);

    GPIO_InitTypeDef LCD;

    LCD.GPIO_Mode = GPIO_Mode_OUT;
    LCD.GPIO_Pin  = 0x0fff;
    LCD.GPIO_PuPd = GPIO_PuPd_NOPULL;
    LCD.GPIO_Speed = GPIO_Speed_10MHz;
    LCD.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOA,&LCD);

 }
 void LCDInit(){


     BlockingDelayMS(100);

	 LCDInitPins8bitMode();
	 BlockingDelayMS(50);
	 LCDWriteCMD(0x30);
	 BlockingDelayMS(10);
	 LCDWriteCMD(0x30);
	 BlockingDelayMS(10);
     LCDWriteCMD(0x30);
     BlockingDelayMS(10);


     LCDWriteCMD(0x38);
     BlockingDelayMS(10);
     LCDWriteCMD(0x0C);
     BlockingDelayMS(10);
	 LCDWriteCMD(0x06);
     BlockingDelayMS(10);
	 LCDWriteCMD(0x01);
     BlockingDelayMS(10);
 }

 void LCDWrite(char c){

	int PortBits = 0x0500;
	PortBits +=c;
	//write port
	GPIO_Write(GPIOA,PortBits);

	GPIO_WriteBit(GPIOA,GPIO_Pin_10,0);
	BlockingDelayMS(1);
 }

 void LCDWriteCMD(char command){
	int PortBits = 0x0400;
	PortBits +=command;
	//write port
	GPIO_Write(GPIOA,PortBits);

	GPIO_WriteBit(GPIOA,GPIO_Pin_10,0);
	BlockingDelayMS(1);
 }

 void LCDWriteRow(char rowNum,char * row){

	 char i=0;
	 LCDCursorToXY(0,rowNum);
	 while (row[i] && i < 16)
			LCDWrite(row[i++]);
 }

 void LCDCursorToXY(char x,char y){
	 char cursor = 0x80;
	 cursor += 0x40*y + x;
	 LCDWriteCMD(cursor);

 }

 void LCDClear(){
    LCDWriteCMD(0x01);
 }
