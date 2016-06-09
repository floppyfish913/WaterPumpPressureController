#include "menu.h"

char state = 0;
char holdon = 0;

uint16_t DelayTime = 0;
uint16_t OptionDelayTime = 10;
uint16_t PressureMin=400;
uint16_t PressureMax=600;
char Pump_State = PUMP_STOP;
char Pump_Flag = PUMP_NORMAL;


void menuStateMachine(){

    char string_buffer[16];
    switch(state){

    case START_SCREEN :
        LCDWriteRow(0," Vizicsibe2000");
        LoadConfiguration();
        if ( holdon  == 10) {
                state = 1;
                holdon = 0;
        }
    break;

    case PUMP_STATUS :

        if (Pump_Flag != PUMP_OVER_PRESSURE){

            if (Pump_State ==PUMP_STOP && DelayTime != 0)
                {
                sprintf(string_buffer,"KI | START %#4d ",OptionDelayTime - DelayTime);
                LCDWriteRow(0,string_buffer);
                }
            else if (Pump_State == PUMP_STOP)
                {
                LCDWriteRow(0,"KI              ");
                }
            else
                {
                LCDWriteRow(0,"BE              ");
                }
        }
        else {
            if (Pump_State != PUMP_STOP)
                LCDWriteRow(0,"BE | TULNYOMAS  ");
            else
                LCDWriteRow(0,"KI | TULNYOMAS  ");
        }

        sprintf(string_buffer,"%#4d mBar       ",getPressureValue_mBAR());
        LCDWriteRow(1,string_buffer);
            if ( holdon  == 80) {
                state = CURRENT_PRESSURE;
                holdon = 0;
        }

    break;


    case CURRENT_PRESSURE :

        LCDWriteRow(0,"Aktualis nyomas:");
        sprintf(string_buffer,"%#4d mBar       ",getPressureValue_mBAR());
        LCDWriteRow(1,string_buffer);

        if ( holdon  == 20) {
                state = PUMP_STATUS;
                holdon = 0;
        }

    break;
        case MAX_PRESSURE :
        LCDWriteRow(0,"Maximum nyomas: ");
        sprintf(string_buffer,"%#4d mBar       ",PressureMax);
        LCDWriteRow(1,string_buffer);

        if ( holdon  == 120) {
                state = PUMP_STATUS;
                holdon = 0;
        }

    break;

    case MIN_PRESSURE :
        LCDWriteRow(0,"Minimum nyomas: ");
        sprintf(string_buffer,"%#4d mBar       ",PressureMin);
        LCDWriteRow(1,string_buffer);

        if ( holdon  == 120) {
                state = PUMP_STATUS;
                holdon = 0;
        }
    break;

    case DELAY_TIMER :
        LCDWriteRow(0,"Kesleltetesi ido:");
        sprintf(string_buffer,"%#4d            ",OptionDelayTime+1 - DelayTime);
        LCDWriteRow(1,string_buffer);

        if ( holdon  == 120) {
                state = PUMP_STATUS;
                holdon = 0;
        }
    break;
    case SAVE_CONFIG :
        LCDWriteRow(0,"Beallitasok Ment");
        LCDWriteRow(1,"NEM    |    IGEN");

        if ( holdon  == 120) {
                state = PUMP_STATUS;
                holdon = 0;
        }
    break;
    case CONFIG_SAVED :
        LCDWriteRow(0,"Beallitasok     ");
        LCDWriteRow(1,"MENTVE!         ");

        if ( holdon  == 15) {
                state = PUMP_STATUS;
                holdon = 0;
        }
    break;
    case CONFIG_DISCARD :
        LCDWriteRow(0,"Beallitasok     ");
        LCDWriteRow(1,"NINCS MENTES!   ");

        if ( holdon  == 15) {
                state = PUMP_STATUS;
                holdon = 0;
        }
    break;
    }
    holdon++;

}

void MenuControl(){
    if(!(ReadButtons() & BUTTON_SELECT)) {
            state++;
            while(!(ReadButtons() & 2));
            if (state >= 7)
                state = 1;
    }
    if(!(ReadButtons() & BUTTON_STARTSTOP)){
            if( DelayTime > 0 ||  Pump_State == PUMP_IDLE)
            {
                DelayTime = 0;
                Pump_State = PUMP_STOP;
            }
            else{
                DelayTime++;
            }

            while(!(ReadButtons() & 0x01)){

            };
     }
     if(!(ReadButtons() & BUTTON_UP)) {
            holdon = 0;
            if (state == MAX_PRESSURE){
                if(PressureMax < 4000)
                    PressureMax+=5;
            }
            if (state == MIN_PRESSURE){
                if(PressureMin < PressureMax)
                    PressureMin+=5;
            }
            if (state == DELAY_TIMER){
                if(OptionDelayTime < 300)
                    OptionDelayTime++;
            }
            if (state == SAVE_CONFIG){
                SaveConfiguration();
                state = CONFIG_SAVED;
            }


     }

     if(!(ReadButtons() & BUTTON_DOWN)) {
            holdon = 0;
            if (state == MAX_PRESSURE){
                if(PressureMax > PressureMin)
                    PressureMax-=5;
            }
            if (state == MIN_PRESSURE){
                if(PressureMin > 0)
                    PressureMin-=5;
            }
            if (state == DELAY_TIMER){
                if(OptionDelayTime > 0)
                    OptionDelayTime--;
            }
            if (state == SAVE_CONFIG){
                state = CONFIG_DISCARD;
            }
     }



}

void DelayTimer(){
    if(DelayTime>0 && Pump_State == PUMP_STOP){

            if(DelayTime == OptionDelayTime){
                    Pump_State = PUMP_START;
                    DelayTime = 0;
            }
            DelayTime++;

    }

}

void HysteresisSwitcher(){

    uint16_t CurrentPressure = getPressureValue_mBAR();

    if( CurrentPressure > PressureMax )
        Pump_Flag = PUMP_OVER_PRESSURE;
    else if( CurrentPressure < PressureMin)
        Pump_Flag = PUMP_UNDER_PRESSURE;
    else
        Pump_Flag = PUMP_NORMAL;

    if(Pump_State == PUMP_START && Pump_Flag!=PUMP_OVER_PRESSURE){
        SetRelayState(ENABLE);
        Pump_State = PUMP_IDLE;
    }
    else if (Pump_State == PUMP_STOP){
        SetRelayState(DISABLE);
        }
    else if (Pump_State==PUMP_IDLE && Pump_Flag == PUMP_UNDER_PRESSURE){
       SetRelayState(ENABLE);
    }
    else if (Pump_State==PUMP_IDLE && Pump_Flag == PUMP_OVER_PRESSURE){
       SetRelayState(DISABLE);
    }



}
