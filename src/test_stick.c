/*
 * Button Test
 */
#include "asis.h"
#include "asis_util.h"

void asis_sys_main(void){
  uasis_sync_from_controller_menu();
  asis_d_pad(ASIS_D_PAD_RIGHT,5);
  asis_wait_ms(500);
  asis_click(ASIS_BUTTON_A);
  asis_wait_s(1);
  for(int i=0;i<12;i++){
    //This actually inserts 12 instructions
    //rather than using a loop instruction
    asis_d_pad(ASIS_D_PAD_DOWN,5);
    asis_wait_ms(100);
  }
  asis_click(ASIS_BUTTON_A);
  asis_wait_ms(500);
  asis_d_pad(ASIS_D_PAD_DOWN,100);
  asis_d_pad(ASIS_D_PAD_UP,5);
  asis_wait_ms(500);
  asis_d_pad(ASIS_D_PAD_UP,5);
  asis_wait_ms(500);
  asis_d_pad(ASIS_D_PAD_UP,5);
  asis_wait_ms(500);
  asis_d_pad(ASIS_D_PAD_UP,5);
  asis_wait_ms(500);
  asis_d_pad(ASIS_D_PAD_UP,5);
  asis_wait_ms(500);
  asis_d_pad(ASIS_D_PAD_UP,5);
  asis_wait_ms(500);
  asis_click(ASIS_BUTTON_A);
  asis_wait_ms(500);
  //Left stick
  asis_click(ASIS_BUTTON_LCLICK);
  asis_wait_s(1);
  //So MIN is up/left, MAX is down/right
  //The function takes (x,y,duration). x is left/right and y is up/down
  asis_stick(ASIS_STICK_L_MIN,ASIS_STICK_L_MIN,50);
  asis_stick(ASIS_STICK_L_MIN,ASIS_STICK_L_CENTER,50);
  asis_stick(ASIS_STICK_L_MIN,ASIS_STICK_L_MAX,50);
  asis_stick(ASIS_STICK_L_CENTER,ASIS_STICK_L_MAX,50);
  asis_stick(ASIS_STICK_L_MAX,ASIS_STICK_L_MAX,50);
  asis_stick(ASIS_STICK_L_MAX,ASIS_STICK_L_CENTER,50);
  asis_stick(ASIS_STICK_L_MAX,ASIS_STICK_L_MIN,50);
  asis_stick(ASIS_STICK_L_CENTER,ASIS_STICK_L_MIN,50);
  asis_stick(ASIS_STICK_L_CENTER,ASIS_STICK_L_CENTER,50);
  asis_wait_s(1);
  asis_click(ASIS_BUTTON_B);
  asis_wait_ms(500);
  //Right stick
  asis_click(ASIS_BUTTON_RCLICK);
  asis_wait_s(1);
  asis_stick(ASIS_STICK_R_MIN,ASIS_STICK_R_MIN,50);
  asis_stick(ASIS_STICK_R_MIN,ASIS_STICK_R_CENTER,50);
  asis_stick(ASIS_STICK_R_MIN,ASIS_STICK_R_MAX,50);
  asis_stick(ASIS_STICK_R_CENTER,ASIS_STICK_R_MAX,50);
  asis_stick(ASIS_STICK_R_MAX,ASIS_STICK_R_MAX,50);
  asis_stick(ASIS_STICK_R_MAX,ASIS_STICK_R_CENTER,50);
  asis_stick(ASIS_STICK_R_MAX,ASIS_STICK_R_MIN,50);
  asis_stick(ASIS_STICK_R_CENTER,ASIS_STICK_R_MIN,50);
  asis_stick(ASIS_STICK_R_CENTER,ASIS_STICK_R_CENTER,50);
  asis_wait_s(1);
  uasis_home();
  
}
