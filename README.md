# Project_1_egfwd
This Project is created for the egfwd advanced embedded systems track </br>
Controlling DIO pin ON/OFF time that emulates PWM signal.
</br>
Created APIs
</br>
____________________________________________________________
</br>
AppSetInterval(double on_time ,double off_time,u32 frequency);
</br>
Return Type : void
</br>
Function : it sets high and low periods on a DIO pin 
</br>
Parameters: on_time holds the high period , off_time holds the low period , frequency holds the mcu clock frequency.
</br>
____________________________________________________________
</br>
The APIs is tested on TIVA-C launchboard runs on Cortex-M mcu

