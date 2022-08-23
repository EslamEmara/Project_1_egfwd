/*
 * App.c
 *
 *  Created on: Aug 22, 2022
 *      Author: 20109
 */

#include "App.h"
St_TimerConfig Timer0init = {TIMER0,TIMER32BIT,TIMER_A,PERIODIC};
St_TimerConfig Timer1init = {TIMER1,TIMER32BIT,TIMER_A,PERIODIC};

void ISR_TIMER0(void);
void ISR_TIMER1(void);

void AppInit(){
       ConfigureBus();
       gpio_pins_init_st init = {PORTF,0b00001110,OUTPUT,Drive_8mA,PAD_NPU_NPD};
       GPIO_PinsInit(init);

       TimerInit(Timer0init);
       TimerOFIntEnable(Timer0init,ISR_TIMER0);

}
double no_of_on_ticks;
double no_of_off_ticks;

void AppSetInterval(double on_time ,double off_time,u32 frequency){

    double tick = 1.000000000 / (double)frequency;

    no_of_on_ticks =  (on_time) / tick;
    no_of_off_ticks = (off_time) / tick;

    TimerLoadInterval(Timer0init,(u32)no_of_off_ticks);

}

void ISR_TIMER0(void)
{
    static u8 flag = 1;
    if (flag == 1){
        GPIOWrite(PORTF,0b00001010,HIGH );
        TimerLoadInterval(Timer0init,(u32)no_of_on_ticks);
        flag = 0;
    }
    else{
        GPIOWrite(PORTF,0b00001010,LOW );
        TimerLoadInterval(Timer0init,(u32)no_of_off_ticks);
        flag  =1;
    }

    TimerClearInt(TIMER0,TIMER_A);
}

