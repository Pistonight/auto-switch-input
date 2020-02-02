/*
 * Function Test
 */
#include "asis.h"
#include "asis_util.h"
void godown(void* args){
  asis_d_pad(ASIS_D_PAD_DOWN,5);
  asis_wait_ms(100);
}

void my_stick_func(void* args){
  if(((int)args)==0){
    asis_stick(ASIS_STICK_CENTER,ASIS_STICK_L_MAX,5);
  }else{
    asis_stick(ASIS_STICK_L_MAX,ASIS_STICK_CENTER,5);
  }
  asis_wait_ms(100);
}

void asis_sys_main(void){
  uasis_sync_from_controller_menu();
  asis_d_pad(ASIS_D_PAD_RIGHT,5);
  asis_wait_ms(500);
  uint16_t test_loop = asis_curloc();
  asis_click(ASIS_BUTTON_A);
  asis_wait_s(1);

  uint16_t loop_start = asis_curloc();
  uint16_t go_down_func = asis_function(&godown,NULL);
  asis_call(go_down_func);
  asis_repeat(loop_start,3);
  asis_repeat(loop_start,2);//setup to loop 12 times

  asis_click(ASIS_BUTTON_A);
  asis_wait_ms(500);
  asis_d_pad(ASIS_D_PAD_DOWN,80);
  asis_d_pad(ASIS_D_PAD_UP,5);
  asis_wait_ms(500);
  asis_click(ASIS_BUTTON_A);
  asis_wait_ms(500);
  asis_click(ASIS_BUTTON_A);
  asis_wait_s(1);
  //Test Start here
  asis_click(ASIS_BUTTON_A);
  asis_wait_ms(100);
  asis_click(ASIS_BUTTON_B);
  asis_wait_ms(100);
  asis_click(ASIS_BUTTON_X);
  asis_wait_ms(100);
  asis_click(ASIS_BUTTON_Y);
  asis_wait_ms(100);
  asis_click(ASIS_BUTTON_L);
  asis_wait_ms(100);
  asis_click(ASIS_BUTTON_R);
  asis_wait_ms(100);
  asis_click(ASIS_BUTTON_ZL);
  asis_wait_ms(100);
  asis_click(ASIS_BUTTON_ZR);
  asis_wait_ms(100);
  asis_click(ASIS_BUTTON_MINUS);
  asis_wait_ms(100);
  asis_click(ASIS_BUTTON_PLUS);
  asis_wait_ms(100);
  asis_click(ASIS_BUTTON_LCLICK);
  asis_wait_ms(100);
  asis_click(ASIS_BUTTON_RCLICK);
  asis_wait_ms(100);
  asis_d_pad(ASIS_D_PAD_UP,5);
  asis_wait_ms(100);
  asis_d_pad(ASIS_D_PAD_UP_RIGHT,5);
  asis_wait_ms(100);
  asis_d_pad(ASIS_D_PAD_RIGHT,5);
  asis_wait_ms(100);
  asis_d_pad(ASIS_D_PAD_DOWN_RIGHT,5);
  asis_wait_ms(100);
  asis_d_pad(ASIS_D_PAD_DOWN,5);
  asis_wait_ms(100);
  asis_d_pad(ASIS_D_PAD_DOWN_LEFT,5);
  asis_wait_ms(100);
  asis_d_pad(ASIS_D_PAD_LEFT,5);
  asis_wait_ms(100);
  asis_d_pad(ASIS_D_PAD_UP_LEFT,5);
  asis_wait_ms(100);
  //
  //Last test home and capture
  asis_wait_ms(500);
  uasis_home();
  uint16_t stick_func = asis_function(&my_stick_func,(void*)0);
  asis_call(stick_func);
  uint16_t stick_func2 = asis_function(&my_stick_func,(void*)1);
  uint16_t last_loop = asis_curloc();
  asis_call(stick_func2);
  asis_repeat(last_loop,3);
  asis_jump(test_loop);//Infinite loop
  
}
