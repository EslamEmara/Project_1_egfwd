/*
 * APP.h
 *
 *  Created on: Aug 22, 2022
 *      Author: 20109
 */

#ifndef APP_APP_H_
#define APP_APP_H_

#include "../Includes/Timer.h"
#include "../Includes/gpio.h"

void AppInit();
void AppSetInterval(double on_time ,double off_time,u32 frequency);
#endif /* APP_APP_H_ */
