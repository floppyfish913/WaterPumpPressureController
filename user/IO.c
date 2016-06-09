#include "IO.h"

void ButtonInit(){

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);

    GPIO_InitTypeDef ButtonsIO;

    ButtonsIO.GPIO_Mode = GPIO_Mode_IN;
    ButtonsIO.GPIO_Pin  = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
    ButtonsIO.GPIO_PuPd = GPIO_PuPd_UP;
    ButtonsIO.GPIO_Speed = GPIO_Speed_2MHz;
    ButtonsIO.GPIO_OType = GPIO_OType_OD;
    GPIO_Init(GPIOB,&ButtonsIO);

}


void RelayOutputInit(){
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);

    GPIO_InitTypeDef RelayIO;

    RelayIO.GPIO_Mode = GPIO_Mode_OUT;
    RelayIO.GPIO_Pin  = GPIO_Pin_7;
    RelayIO.GPIO_PuPd = GPIO_PuPd_DOWN;
    RelayIO.GPIO_Speed = GPIO_Speed_10MHz;
    RelayIO.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOB,&RelayIO);

    SetRelayState(DISABLE);

};

char ReadButtons(){
    return GPIO_ReadInputData(GPIOB) >>3 & 0x0f;
};

void SetRelayState(FunctionalState status){

    GPIO_WriteBit(GPIOB,GPIO_Pin_7,(status ? 0x01 : 0x00));
}

FunctionalState GetRelayState(){

    if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_7))
        return ENABLE;
    return DISABLE;

}
