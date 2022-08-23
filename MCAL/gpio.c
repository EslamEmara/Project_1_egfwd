/*
 * gpio.c
 *
 *  Created on: 19 Feb 2020
 *      Author: Eslam
 */

#include "../Includes/gpio.h"
#include "../Includes/Clock.h"

u32 REGS_ADD[6] ={PORT_A,PORT_B,PORT_C,PORT_D,PORT_E,PORT_F};

static void SetMask (u8 reg_no,u16 offset, u8 pins)

{
    volatile u32* reg = REGS_ADD[reg_no]+(u32)offset;
    u32 data = *reg;
    data &= ~(pins);
    data |= (0xff & pins);
    *reg = data;
}

static void ClrMask (u8 reg_no ,u16 offset, u8 pins)
{
    volatile u32* reg =REGS_ADD[reg_no] + offset;
    u32 data = *reg;
    data &= ~(pins);
    data |= (0x00 & pins);
    *reg = data;
}


void GPIO_PinsInit(gpio_pins_init_st init_str){
    GPIOClockSet (init_str.port);
    GPIODirModeSet(init_str.port, init_str.pins, init_str.type);
    GPIOPadSet(init_str.port, init_str.pins, init_str.max_current, init_str.pad_connection);
}



void ConfigureBus()
{
     #if (PORTF_BUS == AHB)
             SETBIT(GPIOHBCTL , 0);
     #elif (PORTF_BUS == APB)
             CLRBIT(GPIOHBCTL , 0);
     #endif

     #if (PORTB_BUS == AHB)
             SETBIT(GPIOHBCTL , 1);
     #elif (PORTB_BUS == APB)
             CLRBIT(GPIOHBCTL , 1);
     #endif

     #if (PORTC_BUS == AHB)
             SETBIT(GPIOHBCTL , 2);
     #elif (PORTC_BUS == APB)
             CLRBIT(GPIOHBCTL , 2);
     #endif

     #if (PORTD_BUS == AHB)
             SETBIT(GPIOHBCTL , 3);
     #elif (PORTD_BUS == APB)
             CLRBIT(GPIOHBCTL , 3);
     #endif

     #if (PORTE_BUS == AHB)
             SETBIT(GPIOHBCTL , 4);
     #elif (PORTE_BUS == APB)
             CLRBIT(GPIOHBCTL , 4);
     #endif

     #if  (PORTF_BUS == AHB)
             SETBIT(GPIOHBCTL , 5);
     #elif (PORTF_BUS == APB)
             CLRBIT(GPIOHBCTL , 5);
     #endif
}

void GPIOClockSet(gpio_port_t port)
{
    CLOCK_voidInit();
    SETBIT (RCGCGPIO , port);

}
void GPIOClockRst(gpio_port_t port)
{

   CLRBIT (RCGCGPIO , port);
}
char GPIOClockGet(gpio_port_t port)
{
    return GETBIT (RCGCGPIO , port);
}
void GPIODirModeSet(gpio_port_t port, u8 pins, gpio_mode_t mode)     //GPIODirModeSet(PORTA,0b01100100,MODE_OUT);
{

    SetMask(port,GPIODEN,pins);

    if (mode == ALT_FUN)
        SetMask(port,GPIOAFSEL,pins);

    else
        ClrMask(port,GPIOAFSEL,pins);


     if (mode == OUTPUT)
     {
         SetMask(port,GPIODIR,pins);
                                           //     01101101
     }
     else if (mode == INPUT)
     {
         ClrMask(port,GPIODIR,pins);
                                       // data = XXXXXXX 00001001
     }
}


void GPIOPadSet(gpio_port_t port, u8 pins, gpio_drive_t str, gpio_pad_t pad)
{

    SetMask(port,str,pins);

/*--------------------------------------------------------------------------------------------------*/
   if ( pad == PAD_NPU_NPD)
   {
       ClrMask(port,PAD_PU,pins);
       ClrMask(port,PAD_PD,pins);
   }
   else
   {
    SetMask(port,pad,pins);
   }
}


void GPIOWrite(gpio_port_t port, u8 pins, gpio_data_t gpio_data)
{
        u16 spins = pins << 2;
        if (gpio_data == HIGH)
        {
            REG(REGS_ADD[port]+(spins)) = 0xFFFF;
        }
        else if (gpio_data == LOW)
        {
            REG(REGS_ADD[port]+(spins)) = 0x0000;

        }
}

u8 GPIORead(gpio_port_t port, u8 pins)
{
        u16 spins = pins << 2 & 0b001111111100;

        u8 reg =REG(REGS_ADD[port]+(spins));

        return reg;
}

void GPIO_InterruptSet(gpio_port_t port , unsigned char pins , interrupt_t type , void (*registered_interrupt) (void) )
{
             if (port == PORTA)
             {
                 Int_En(0,registered_interrupt);
             }
             else   if (port == PORTB)
             {
                 Int_En(1,registered_interrupt);
             }
             else   if (port == PORTC)
             {
                 Int_En(2,registered_interrupt);
             }
             else   if (port == PORTD)
             {
                 Int_En(3,registered_interrupt);
             }
             else   if (port == PORTE)
             {
                 Int_En(4,registered_interrupt);
             }
             else   if (port == PORTF)
             {
                 Int_En(30,registered_interrupt);
             }

           ClrMask(port,GPIOIM,pins);

           if (type <= 2)
           {
               ClrMask(port,GPIOIS,pins);
           }
           else
           {
               SetMask(port,GPIOIS,pins);
           }
           if (type == RISING_FALLING)
           {
               SetMask(port,GPIOIBE,pins);
           }
           else
           {
               ClrMask(port,GPIOIBE,pins);
           }
           if (type == RISING)
           {
               SetMask(port,GPIOIEV,pins);
           }
           else if (type == FALLING)
           {
               ClrMask(port,GPIOIEV,pins);
           }

           ClrMask(port,GPIORIS,pins);
           SetMask(port,GPIOICR,pins);
           SetMask(port,GPIOIM,pins);
}

