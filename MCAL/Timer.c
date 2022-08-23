
#include "../Includes/Timer.h"




u32 TimerID_ADD[12] = {TIMER0_BASE,TIMER1_BASE,TIMER2_BASE,TIMER3_BASE,TIMER4_BASE,TIMER5_BASE,
                   TIMER0_WIDE_BASE,TIMER1_WIDE_BASE,TIMER2_WIDE_BASE,TIMER3_WIDE_BASE,TIMER4_WIDE_BASE,TIMER5_WIDE_BASE};
u8 vectorsA[12] ={19,21,23,35,70,92,94,96,98,100,102,104};

void TimerInit(St_TimerConfig init_str){
    SETBIT(INT_EN0 , 19);
    if(init_str.TimerID <= 5)
        SETBIT(RCGCTIMER,init_str.TimerID);
    else
        SETBIT(RCGCTIMER,init_str.TimerID-6 );

    REG(TimerID_ADD[init_str.TimerID]) = init_str.TimerBits ;          //GPTM Configuration


    if(init_str.TimerNum == TIMER_A){
        CLRBIT(REG(TimerID_ADD[init_str.TimerID] + GPTMCTL) , 0);                             //ENABLE TIMER A

        REG(TimerID_ADD[init_str.TimerID] + GPTMTAMR) = init_str.TimerMode;
    }
    else{
        CLRBIT(REG(TimerID_ADD[init_str.TimerID] + GPTMCTL) , 8);                              //ENABLE TIMER B
        REG(TimerID_ADD[init_str.TimerID] + GPTMTBMR) = init_str.TimerMode;                   //MODE EX: PERIODIC
    }

}

void TimerDisable(St_TimerConfig init_str){
    if(init_str.TimerNum == TIMER_A){
           CLRBIT(REG(TimerID_ADD[init_str.TimerID] + GPTMCTL) , 0);                             //ENABLE TIMER A
       }
       else{
           CLRBIT(REG(TimerID_ADD[init_str.TimerID] + GPTMCTL) , 8);                              //ENABLE TIMER B
       }
}

void TimerLoadInterval(St_TimerConfig init_str , u32 data){
    if(init_str.TimerNum == TIMER_A){
        REG(TimerID_ADD[init_str.TimerID]+GPTMTAILR) = data;
    }
    else{
        REG(TimerID_ADD[init_str.TimerID]+GPTMTBILR) = data;
    }


    if(init_str.TimerNum == TIMER_A){
        SETBIT(REG(TimerID_ADD[init_str.TimerID] + GPTMCTL) , 0);                             //ENABLE TIMER A

    }
    else{
        SETBIT(REG(TimerID_ADD[init_str.TimerID] + GPTMCTL) , 8);                              //ENABLE TIMER B
    }

}


void TimerOFIntEnable(St_TimerConfig init_str,void (*interrupt_address)(void))
{
    if(init_str.TimerNum == TIMER_A){
           SETBIT(REG(TimerID_ADD[init_str.TimerID]+GPTMIMR) , 0);
           Int_En(vectorsA[init_str.TimerID],interrupt_address);

       }
       else{
           SETBIT(REG(TimerID_ADD[init_str.TimerID]+GPTMIMR) , 8);
           Int_En((vectorsA[init_str.TimerID]+1),interrupt_address);
       }
    SETBIT(REG(TimerID_ADD[init_str.TimerID] + GPTMICR) , 0);
}

void TimerClearInt(EN_TimerID timer_id,EN_TimerNum timer_no){
        if(timer_no== TIMER_A){
        SETBIT(REG(TimerID_ADD[timer_id] + GPTMICR) , 0);

       }
       else{
         SETBIT(REG(TimerID_ADD[timer_id] + GPTMICR) , 8);
       }
}
