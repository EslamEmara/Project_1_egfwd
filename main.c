#include "Includes/Clock.h"
#include "Includes/gpio.h"
#include "Includes/Interrupt.h"
#include "Includes/Timer.h"

#include "APP/App.h"

int main(void)
{
    AppInit();
    AppSetInterval(1,0.1,16670000);
 
    while(1){   

    }
}

