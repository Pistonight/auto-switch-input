# Automatic Switch Input System (ASIS) (Updated 1/28/2020)

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

## How to build the project
First thing you will need is [LUFA](http://www.lufa-lib.org). Download the library, extract its content and rename the folder `LUFA` in the project root directory. 

Once you have LUFA, follow one of the instructions below to setup the environment
 - Linux Users: [Instructions](doc/Step1-Setup-Linux.md)
 - MacOS Users: [Instructions](doc/Step1-Setup-MacOS.md) **This is currently unavailable. If you know how to run avr-gcc on a mac, please contribute!**
 - Windows Users: [Instructions](doc/Step1-Setup-Windows.md)
 
These instructions should contain all the links to the tools that you will need.

## How to write scripts with ASIS framework

*To Be Continued*


