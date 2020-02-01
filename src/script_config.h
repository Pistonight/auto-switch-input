//Script Configuration File
#ifndef _SCRIPT_CONFIG_H_
#define _SCRIPT_CONFIG_H_

/*Script Config Section*/

//Buffer size for instruction array
#define ASIS_MAX_INSTRUCTION 200
//Stack size (maximum nested call)
#define ASIS_MAX_STACK 8
//Duration for a button press
#define ASIS_BUTTON_DURATION 3

//The wait time for each cycle of wait
//High value will allow you to wait precisely
//Low value will save power when waiting for long time
//Unit is millisecond
#define ASIS_WAIT_PERIOD 100 
/*Script Config Section*/
#endif
