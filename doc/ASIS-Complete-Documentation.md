# ASIS Complete Documentation
**WIP**

## Constants

#### ASIS Constants (see asis.h)
 - **ASIS_BUTTON_xxx** constants for buttons
 - **ASIS_D_PAD_xxx**  constants for D-pad (not left-joycon)
 - **ASIS_STICK_xxx**  constants for stick
   - MIN is up/left, MAX is down/right
 - **ASIS_INSN_xxx**   constants for instructions
   - *BUTTON* (0) A button instruction
   - *STICK* (1) A stick instruction
   - *REPEAT* (2) A repeat instruction. Jumps to a certain location in the script for a certain number of times
   - *CALL* (3) Jumps to a certain location in the script and push the return address to the stack
   - *RET* (4) Pop the return address and jump there
   - *NOP* (5) A wait instruction
   - *EXIT* (6) An exit instruction
   - *D_PAD* (7) A D-pad instruction
   - *JUMP* (8) unconditional jump

#### Configuration Constants (see script_config.h)

## ASIS System Functions
These functions are called by the library to setup ASIS framework. Users are not supposed to call them
###### void asis_sys_init()
Called right after hardware is set up. Initialize PC, SP, memory and other global variables
###### void asis_sys_cycle(asis_packet_t\* packet)
Called each cycle to execute the next instruction and output a packet, which will be processed into data to send to the switch
###### void asis_sys_main()
Called to setup the script. Users should define this function in the script
###### void asis_sys_prepare()
Called after `asis_sys_main()` to initialize variables and check for errors before execution starts
###### void asis_sys_ovfl(bool\* output)
Store the overflow status in the output parameter. There are two types of overflow: script compile time and run time. Script compile time overflow happens if the instruction memory is not large enough to hold all instructions. Run time overflow happens if an instruction causes a jump to out-of-bound location. These overflows are detected by the system and will be indicated by LED (see below).

## ASIS User Functions

## ASIS Internal Functions

## LED indication
 - 2 rapid blinks followed by 1 second off = buffer overflow when building the script
 - 2 rapid blinks followed by 1 second on then 1 second off = buffer overflow when running the script (stack or memory)
 - 1 rapid blink follwed by 1 second off = waiting
 - blink once followed by 3 second off = script finished successfully with an exit instruction
