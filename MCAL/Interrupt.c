/*
 * Interrupt.c
 *
 *  Created on: 15 Apr 2020
 *      Author: Eslam
 */
#include "../Includes/Interrupt.h"

extern void (* g_pfnVectors[])(void);
void (*g_pfnRAMVectors[155])(void);

#pragma DATA_ALIGN(g_pfnRAMVectors, 1024)
#pragma DATA_SECTION(g_pfnRAMVectors, ".vtable")

void Int_En(unsigned char int_ID , void (*interrupt_to_register)(void))
{
    SETBIT(INT_EN0 , 19);

    int i =0;
    for( i = 0; i < 155; i++)
    {
        g_pfnRAMVectors[i] = g_pfnVectors[i];
    }

    volatile u32*   reg     =   VECTOR_TABLE_OFFSET ;
    *reg = (unsigned long int)g_pfnRAMVectors;

    reg = INTERRUPT_0_31_SET_ENABLE +  ((int_ID/32) * 4);
    *reg |= (1<<(int_ID%32));

    g_pfnRAMVectors[int_ID+16] = interrupt_to_register;
}

