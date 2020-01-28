/*
 * Header for asis.c
 */
#ifndef _ASIS_H_
#define _ASIS_H_

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>

#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Drivers/Board/Joystick.h>
#include <LUFA/Drivers/Board/LEDs.h>
#include <LUFA/Drivers/Board/Buttons.h>
#include <LUFA/Platform/Platform.h>


//Buttons
#define ASIS_BUTTON_NOTHING 0x0000
#define ASIS_BUTTON_Y       0x0001
#define ASIS_BUTTON_B       0x0002
#define ASIS_BUTTON_A       0x0004
#define ASIS_BUTTON_X       0x0008
#define ASIS_BUTTON_L       0x0010
#define ASIS_BUTTON_R       0x0020
#define ASIS_BUTTON_ZL      0x0040
#define ASIS_BUTTON_ZR      0x0080
#define ASIS_BUTTON_MINUS   0x0100
#define ASIS_BUTTON_PLUS    0x0200
#define ASIS_BUTTON_LCLICK  0x0400
#define ASIS_BUTTON_RCLICK  0x0800
#define ASIS_BUTTON_HOME    0x1000
#define ASIS_BUTTON_CAPTURE 0x2000
//D-pad (HAT)
#define ASIS_D_PAD_UP         0x00
#define ASIS_D_PAD_UP_RIGHT   0x01
#define ASIS_D_PAD_RIGHT      0x02
#define ASIS_D_PAD_DOWN_RIGHT 0x03
#define ASIS_D_PAD_DOWN       0x04
#define ASIS_D_PAD_DOWN_LEFT  0x05
#define ASIS_D_PAD_LEFT       0x06
#define ASIS_D_PAD_UP_LEFT    0x07
#define ASIS_D_PAD_CENTER     0x08
//Sticks
#define ASIS_STICK_L_MAX    0xFF00
#define ASIS_STICK_L_MIN    0x0000
#define ASIS_STICK_L_CENTER 0x8000
#define ASIS_STICK_R_MAX    0x00FF
#define ASIS_STICK_R_MIN    0x0000
#define ASIS_STICK_R_CENTER 0x0080 
#define ASIS_STICK_CENTER   0x8080
//Instructions
#define ASIS_INSN_BUTTON 0
#define ASIS_INSN_STICK  1
#define ASIS_INSN_REPEAT 2
#define ASIS_INSN_CALL   3
#define ASIS_INSN_RET    4
#define ASIS_INSN_NOP    5
#define ASIS_INSN_EXIT   6
#define ASIS_INSN_D_PAD  7
#define ASIS_INSN_JUMP   8

//Instruction type
typedef struct{
  uint16_t operation;
  uint16_t duration;//jump_target is also stored here
  uint16_t button;
  uint16_t arg1;//stick_x, repeat_total 
  uint16_t arg2;//stick_y, repeat_current
} asis_insn_t;

//Packet type
typedef struct{
  uint16_t button;
  uint8_t hat;
  uint16_t stick_x;//upper for L stick, lower for R stick
  uint16_t stick_y;
  bool exit;
} asis_packet_t;

/* System functions. Script Users should not call these */
//Initialize ASIS
void asis_sys_init(void);
//Called each cycle
void asis_sys_cycle(asis_packet_t*);
//Main
void asis_sys_main(void);
//Prepare for execution after loading main
void asis_sys_prepare(void);

/* User function.*/
//Load a button instruction (button, duration)
void asis_button(uint16_t, uint16_t);
//Load a stick instruction (x,y,duration)
void asis_stick(uint16_t,uint16_t,uint16_t);
//Load a d-pad instruction (hat,duration)
void asis_d_pad(uint16_t,uint16_t);
//Load a wait instruction (duration)
void asis_wait(uint16_t);
//Get current instruction index
uint16_t asis_current(void);
//Load a loop (repeat) instruction (location, repeat_time)
void asis_repeat(uint16_t,uint16_t);
//Load a jump instruction
void asis_jump(uint16_t);
//Load a function
uint16_t asis_function(void func());
//Load a function call instruction
void asis_call(uint16_t);
//Load an exit instruction
void asis_exit(void);

#endif
