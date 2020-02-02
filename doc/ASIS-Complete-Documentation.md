# ASIS Complete Documentation
**WIP**

## Constants

### Buttons Input
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

### D-pad Input
These constants are for `asis_d_pad()`. The switch register them differently than the left joycon directional buttons, but should function the same. (I don't think any game specifically require the joycon button input)

| Const Name | HEX | Description |
|------------|-----|-------------|
| ASIS_D_PAD_UP         | 0x01 | D-pad up input
| ASIS_D_PAD_UP_RIGHT   | 0x01 | D-pad up and right
| ASIS_D_PAD_RIGHT      | 0x02 | D-pad right
| ASIS_D_PAD_DOWN_RIGHT | 0x03 | D-pad down and right
| ASIS_D_PAD_DOWN       | 0x04 | D-pad down
| ASIS_D_PAD_DOWN_LEFT  | 0x05 | D-pad down and left
| ASIS_D_PAD_LEFT       | 0x06 | D-pad left
| ASIS_D_PAD_UP_LEFT    | 0x07 | D-pad up and left
| ASIS_D_PAD_CENTER     | 0x08 | No D-pad input

### Stick Input
These constants are convienient to set up an `asis_stick()` instruction. Each analog stick outputs values from `0x00` to `0xFF`. ASIS encodes the left and right stick with a 16-bit integer. The upper 8 bits are for the left stick and the lower 8 for the right. These constants can be combined with or(|) to include both sticks. See asis_stick() for more details

| Const Name | Hex | Description |
|------------|-----|-------------|
| ASIS_STICK_L_MAX    | 0xFF00 | Left stick max (down/right)
| ASIS_STICK_L_MIN    | 0x0000 | Left stick min (up/left)
| ASIS_STICK_L_CENTER | 0x8000 | Left stick center
| ASIS_STICK_R_MAX    | 0x00FF | Right stick max (down/right)
| ASIS_STICK_R_MIN    | 0x0000 | Right stick min (up/left)
| ASIS_STICK_R_CENTER | 0x0080 | Right stick center
| ASIS_STICK_CENTER   | 0x8080 | Both stick center

### Instruction Opcode
These are for ASIS internal use. Users do not need to refer to them when writing scripts.

| Const Name | Value | Description |
|------------|-------|-------------|
| ASIS_INSN_BUTTON | 0 | Button instruction. Loaded by `asis_click()` and `asis_button()' |
| ASIS_INSN_STICK  | 1 | Stick instruction. Loaded by `asis_stick()` |
| ASIS_INSN_REPEAT | 2 | Repeat (loop) instruction. Loaded by `asis_repeat()` |
| ASIS_INSN_CALL   | 3 | Call instruction. Loaded by `asis_call()` **WIP** |
| ASIS_INSN_RET    | 4 | Return instruction. Loaded by `asis_function()` **WIP** |
| ASIS_INSN_NOP    | 5 | No-op (wait) instruction. Loaded by `asis_wait_s()`, `asis_wait_ms()` and `asis_wait()` |
| ASIS_INSN_EXIT   | 6 | Exit instruction. Loaded by `asis_exit()` |
| ASIS_INSN_D_PAD  | 7 | D-pad instruction. Loaded by `asis_d_pad()` |
| ASIS_INSN_JUMP   | 8 | Unconditional jump instruction. Loaded by `asis_jump()` **WIP** |

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
 - Called right after hardware is set up. Initialize PC, SP, memory and other global variables

###### void asis_sys_cycle(asis_packet_t\* packet)
 - Called each cycle to execute the next instruction and output a packet, which will be processed into data to send to the switch

###### void asis_sys_main()
 - Called to setup the script. Users should define this function in the script

###### void asis_sys_prepare()
 - Called after `asis_sys_main()` to initialize variables and check for errors before execution starts

###### void asis_sys_ovfl(bool\* output)
 - Store the overflow status in the output parameter. There are two types of overflow: script compile time and run time. Script compile time overflow happens if the instruction memory is not large enough to hold all instructions. Run time overflow happens if an instruction causes a jump to out-of-bound location. These overflows are detected by the system and will be indicated by LED (see below).

## ASIS User Functions
These functions are used by the user to load instructions. For durations, 40 is about 1 second.
###### void asis_click(uint16_t button)
 - Load a button instruction. `button` is one of the Button Constants or combination of them. The duration is specified through Makefile Configuration

###### void asis_button(uint16_t button, uint16_t duration)
 - Load a button instruction. `button` is one of the Button Constants or combination of them. `duration` is how long the button should be held. (40=1s)

###### void asis_stick(uint16_t x, uint16_t y, uint16_t duration)
 - Load a stick instruction. `x` and `y` are Stick Constants or combination to specify both left and right sticks. 

###### void asis_d_pad(uint16_t hat, uint16_t duration)
 - Load a D-pad instruction. `hat` is one of the D-pad Constants.

###### void asis_wait(uint16_t repeat, uint16_t ms)
 - Wait `repeat` times, each time wait for `ms` milliseconds. Casual users should use `asis_wait_s()` or `asis_wait_ms()` for a more convienient interface.
 
###### void asis_wait_s(uint16_t second)
 - Load a wait instruction to wait for `second` seconds

###### void asis_wait_ms(uint16_t ms)
 - Load a wait instruction to wait for `ms` milliseconds

###### uint16_t asis_curloc()
 - Return the current location. Used with `asis_repeat()` and `asis_jump()` to create loops

###### void asis_repeat(uint16_t location, uint16_t times)
 - Load a repeat instruction to jump to `location` `times` times. For example, if you want to create a loop to execute 7 times, this is what to do:

```
    uint16_t loop = asis_curloc(); //Get location of the start of the loop
    /* Loop code */
    asis_repeat(6,loop);// Note repeat 6 times, not 7 
                        // since 1 loop is already 
                        // executed before the first 
                        // time we execute repeat
```
 - Similarly, the following loop execute 12 times:

```
    uint16_t loop = asis_curloc();
    /* Loop code */
    asis_repeat(2, loop);//Inner loop 3 times
    asis_repeat(3, loop);//Outer loop 4 times
```
###### void asis_jump(uint16_t location)
 - Load a jump instruction. This can be used to create an infinite loop like this:


    uint16_t inf_loop = asis_curloc();
    /* Loop */
    asis_jump(inf_loop);

###### uint16_t asis_function(void (\*func)(void)); **WIP**
###### void asis_call(uint16_t) **WIP**
###### void asis_exit()
 - Load an exit instruction to terminate the script. The buffer will be initially filled with exit instructions, so usually you don't need to use this. However it is usefull if you are debugging your script and want it to exit in the middle of somewhere.

## ASIS Internal Functions

## ASIS Util Functions

## LED indication
 - 2 rapid blinks followed by 1 second off = buffer overflow when building the script
 - 2 rapid blinks followed by 1 second on then 1 second off = buffer overflow when running the script (stack or memory)
 - 1 rapid blink follwed by 1 second off = waiting
 - blink once followed by 3 second off = script finished successfully with an exit instruction
