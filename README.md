# Automatic Switch Input System (ASIS) (Updated 2/2/2020)

This is a framework that runs on Teensy 2.0++ that allows you to make automated controllers for the Switch

# This project is still under development

I will post the latest update as well as setup instructions once I get to it!

## Credit 
I put this section up front because I really appreciated all the work people had put before me to make this possible. This project is inspired by and adapted from [Automatically throws snowballs in The Legend of Zelda: Breath of the Wild by emulating a controller on a Teensy++ v2.0](https://github.com/bertrandom/snowball-thrower). 

Thanks to bertrandom and contributors to snowball-thrower, the code is much easier to work with. So I could make this framework possible without knowing too much about how joy-cons communicate with the Switch.

Also mentioned in snowball-thrower: 
>Thanks to Shiny Quagsire for his [Splatoon post printer](https://github.com/shinyquagsire23/Switch-Fightstick) and progmem for his [original discovery](https://github.com/progmem/Switch-Fightstick).

I cleaned up the code from Shiny Quagsire's printer and snowball thrower, and I took bertrandom's command structure and made it into a more generic framework.

Let's get to it!

## Step 1 - Build the Project
First thing you will need is [LUFA](http://www.lufa-lib.org). Download the library, extract its content and rename the folder `LUFA` in the project root directory. 

Once you have LUFA, follow one of the instructions below to setup the environment
 - Linux Users: [Instructions](doc/Step1-Setup-Linux.md)
 - MacOS Users: [Instructions](doc/Step1-Setup-MacOS.md) **This is currently unavailable. If you know how to run avr-gcc on a mac, please contribute!**
 - Windows Users: [Instructions](doc/Step1-Setup-Windows.md)
 
These instructions should contain all the links to the tools that you will need.

## Step 2 - Write Hello World with ASIS Framework
In this step, I will show you how to write a script from scratch. However, it might be more helpful to just look at one of the `test_xxx.c` scripts. Please refer to the [complete reference](/doc/ASIS-Complete-Documentation.md) for details of each function. If you are already familiar with programming, especially in C, this should be very easy.

 1. Open `src/my_hello_world.c` and write the following


    /*Include ASIS and ASIS utilities*/
    #include "asis.h"
    #include "asis_util.h"

    /* Main Function */
    void asis_sys_main(void){
        //Next step goes here

    }

 2. Now you have setup an ASIS script that does nothing. Inside `{  }` of the main function, write


    uasis_sync_from_controller_menu();//This utility functions contains
                                      //several instructions to sync
                                      //the controller from menu
    asis_d_pad(ASIS_D_PAD_RIGHT,5);//Press the D-pad right for 5 cycles
    asis_wait_ms(500);             //Wait for 500 ms
    asis_click(ASIS_BUTTON_A);     //Click the A button
    asis_wait_s(1);                //Wait for 1 second
    uasis_home();                  //Utility function to press home

 3. All done! This script sync the controller, then press right and A to go into settings, then press home to return to main menu! You can now follow the next steps to compile and run it.
   - The name of this script is `my_hello_world`. If you used another name, it is the file name in `src` folder without `.c`

## Step 3 - Compile and Flash to Device

#### Compile 
1. Open `makefile`, Set the variable `ASIS_SCRIPT` to the name of your script (without .c)
2. In your shell, execute `make`
3. You can find the built binaries in `build/`
4. If you want to turn off the LED indication, comment out `ASIS_LED = -DLED_ENABLE` in the makefile. This will disable the LEDs when running the script. However, the LED will still flash when an overflow is detected.

#### Flash

You want to flash this file: `build/asis_script_<YOUR SCRIPT NAME>.hex`

If you are using a Teensy like me, you can find the tool and instructions on their [website](https://www.pjrc.com/teensy/loader.html). 

## Other

#### [Almost Complete ASIS Documentation](/doc/ASIS-Complete-Documentation.md)

#### Changelog

 - (2/2/20) Documentation
 - (2/1/20)  
   - Test script for loop
   - Move configuration to makefile
 - (1/31/20) Added utility library and test scripts for buttons and sticks
 - (1/29/20) Added script compile time and run time overflow protection.
 - (1/28/20) 
   - Implemented exit and wait instructions
   - Cleaned up code
 - (1/21/20) Port the project from snowball-thrower


