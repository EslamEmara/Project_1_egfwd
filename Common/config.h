/*
 * config.h
 *
 *  Created on: Feb 19, 2020
 *      Author: Eslam
 */

#ifndef CONFIG_H_
#define CONFIG_H_
#include "regmap.h"

/*================================= CLOCK CONFIGURATION ==================================*/

/* MOSC
 * PIOSC
 * PIOSC_4
 * LFIOSC
 */

#define CLOCK_SOURCE             PIOSC
#define PLL_MODE                 ENABLE
#define SYS_DIV                  SYSDIV_12

/*================================= GPIO CONFIGURATION ====================================*/

#define PORTA_BUS   AHB
#define PORTB_BUS   AHB
#define PORTC_BUS   AHB
#define PORTD_BUS   AHB
#define PORTE_BUS   AHB
#define PORTF_BUS   AHB

#endif /* CONFIG_H_ */
