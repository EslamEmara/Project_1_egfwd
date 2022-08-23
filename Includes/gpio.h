/*
 * gpio.h
 *
 *  Created on: 19 Feb 2020
 *      Author: Eslam
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "../Common/config.h"
#include "../Common/regmap.h"
#include "../Common/STD_TYPES.h"
#include "../Common/BIT_MODE.h"
#include "Interrupt.h"

typedef enum {INPUT = 0x00, OUTPUT = 0xff, ALT_FUN = 0x3} gpio_mode_t;

typedef enum {PORTA=0, PORTB, PORTC,PORTD,PORTE,PORTF} gpio_port_t;
typedef enum {Drive_2mA = 0x500, Drive_4mA = 0x504, Drive_8mA = 0x508, Drive_8mA_Selw = 0x518} gpio_drive_t;
typedef enum {PAD_PU=0x510,PAD_PD=0x514,PAD_NPU_NPD=0,PAD_OD=0x50C} gpio_pad_t;
typedef enum {HIGH =0xff,LOW=0x00} gpio_data_t;

typedef enum {RISING,FALLING,RISING_FALLING,H_LEVEL,L_LEVEL} interrupt_t;

typedef struct{
    gpio_port_t port;
    u8 pins;
    gpio_mode_t type;
    gpio_drive_t max_current;
    gpio_pad_t pad_connection;
}gpio_pins_init_st;


//Functions prototype
void ConfigureBus();
void GPIO_PinsInit(gpio_pins_init_st init_str);

void GPIOClockSet(gpio_port_t port);
void GPIOClockRst(gpio_port_t port);
char GPIOClockGet(gpio_port_t port);

void GPIODirModeSet(gpio_port_t port, unsigned char pins, gpio_mode_t Mode);
unsigned char GPIODirGet(gpio_port_t port, unsigned char pins);
unsigned char GPIOModeGet(gpio_port_t port, unsigned char pins);

void GPIOPadSet(gpio_port_t port, unsigned char pins, gpio_drive_t str, gpio_pad_t pad);
unsigned char GPIOPadDriveStrGet(gpio_port_t port, unsigned char pin);
unsigned char GPIOPadOpenDrainGet(gpio_port_t port, unsigned char pins);
unsigned char GPIOPadPullUpGet(gpio_port_t port, unsigned char pins);
unsigned char GPIOPadPullDownGet(gpio_port_t port, unsigned char pins);

unsigned char GPIORead(gpio_port_t port, unsigned char pins);
void GPIOWrite(gpio_port_t port, unsigned char pins, gpio_data_t gpio_data);
void GPIO_InterruptSet(gpio_port_t port , unsigned char pins , interrupt_t type , void (*registered_interrupt_portF) (void));

#endif /* GPIO_H_ */
