# ASIS Complete Documentation
**WIP**

## Constants

#### Button Const
Button constants are for `asis_click()` and `asis_button()` Button press can be combined with add(+) or or(|)

| Const Name | HEX | Description |
|------------|-----|-------------|
| ASIS_BUTTON_NOTHING | 0x0000 | No Button
| ASIS_BUTTON_Y       | 0x0001 | Y Button
| ASIS_BUTTON_B       | 0x0002 | B Button
| ASIS_BUTTON_A       | 0x0004 | A Button
| ASIS_BUTTON_X       | 0x0008 | X Button
| ASIS_BUTTON_L       | 0x0010 | L Button
| ASIS_BUTTON_R       | 0x0020 | R Button
| ASIS_BUTTON_ZL      | 0x0040 | ZL Button
| ASIS_BUTTON_ZR      | 0x0080 | ZR Button
| ASIS_BUTTON_MINUS   | 0x0100 | MINUS Button
| ASIS_BUTTON_PLUS    | 0x0200 | PLUS Button
| ASIS_BUTTON_LCLICK  | 0x0400 | Left stick click
| ASIS_BUTTON_RCLICK  | 0x0800 | Right stick click
| ASIS_BUTTON_HOME    | 0x1000 | Home button. Using `uasis_home()` is recommended (see Util below)
| ASIS_BUTTON_CAPTURE | 0x2000 | Capture button

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

## Makefile Configuration
| Variable | Description |
|--------|---------|
| ASIS_SCRIPT | Name of the script. If your script is located at `src/foo_bar.c`, the value should be set to `foo_bar` |
| ASIS_LED | Set to `-DLED_ENABLE` to enable LED during script execution. The LED will flash when executing wait instructions. This is useful for debugging. Setting the value to empty will disable LED, but it will still flash when an error is detected or when the script finishes |
| ASIS_MAX_INSTRUCTION | Size of the instruction buffer. Don't set this too big or you will overflow your device's memory. You can use loop instructions and function call instructions to optimize the size of your script
| ASIS_MAX_FUNCTION | Size of the function section within the instruction buffer. Must be less than the instruction buffer size |
| ASIS_MAX_STACK | Size of the call stack. For each call only the return value is stored, so this is equivalent to maximum nested call |
| ASIS_BUTTON_DURATION | Duration for asis_click(). Default is 3
| ASIS_WAIT_PERIOD | The wait period in milliseconds. You will only be able to wait for a length that is a multiple of this period. Lower value will allow more precised wait, while higher value may save some power during long waits. Default value is 100 |

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

## ASIS Util Functions

## LED indication
 - 2 rapid blinks followed by 1 second off = buffer overflow when building the script
 - 2 rapid blinks followed by 1 second on then 1 second off = buffer overflow when running the script (stack or memory)
 - 1 rapid blink follwed by 1 second off = waiting
 - blink once followed by 3 second off = script finished successfully with an exit instruction
