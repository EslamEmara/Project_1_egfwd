/*
 * Interrupt.h
 *
 *  Created on: 15 Apr 2020
 *      Author: Eslam
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "../Common/config.h"
#include "../Common/regmap.h"
#include "../Common/STD_TYPES.h"
#include "../Common/BIT_MODE.h"

void isr_Empty (void);
extern void (*registered_interrupt_portF) (void); //Interrupt.h
void Int_En(unsigned char int_ID , void (*interrupt_to_register)(void));

#endif /* INTERRUPT_H_ */
