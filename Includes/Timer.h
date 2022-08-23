#ifndef TIMER_H_
#define TIMER_H_



#include "../Common/config.h"
#include "../Common/regmap.h"
#include "../Common/STD_TYPES.h"
#include "../Common/BIT_MODE.h"
#include "Interrupt.h"


typedef enum{
    TIMER32BIT = 0x0,
    TIMER_WIDE_64BIT = 0x0,
    TIMER32BIT_RTC = 0x1,
    TIMER_WIDE_64BIT_RTC = 0x1,
    TIMER16BIT = 0x4,
    TIMER_WIDE_32BIT=0x4
}EN_TimerBits;

typedef enum{
    TIMER0 = 0,
    TIMER1,
    TIMER2,
    TIMER3,
    TIMER4,
    TIMER5,
    TIMER0_WIDE,
    TIMER1_WIDE,
    TIMER2_WIDE,
    TIMER3_WIDE,
    TIMER4_WIDE,
    TIMER5_WIDE
}EN_TimerID;

typedef enum{
    TIMER_A,
    TIMER_B
}EN_TimerNum;

typedef enum{
    ONE_SHOT = 0x1,
    PERIODIC = 0x2,
    CAPTURE = 0x3
}EN_TimerMode;

typedef struct{
    EN_TimerID TimerID;
    EN_TimerBits TimerBits;
    EN_TimerNum TimerNum;
    EN_TimerMode TimerMode;
}St_TimerConfig;

void TimerInit(St_TimerConfig init_str);
void TimerLoadInterval(St_TimerConfig init_str , u32 data);
void TimerOFIntEnable(St_TimerConfig init_str,void (*interrupt_address)(void));

void TimerClearInt(EN_TimerID timer_id,EN_TimerNum timer_no);
void TimerDisable(St_TimerConfig init_str);



#endif /* TIMER_H_ */
