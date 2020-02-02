/*
 * Utility functions that makes the scripts easier to make
 */

#include "asis.h"

#define UASIS_FUNC_NULL 60000
uint16_t uasis_home_func = UASIS_FUNC_NULL;
void uasis_sync_from_controller_menu(void){
  asis_wait_s(1);
  asis_click(ASIS_BUTTON_L + ASIS_BUTTON_R);
  asis_wait_ms(500);
  asis_click(ASIS_BUTTON_L + ASIS_BUTTON_R);
  asis_wait_ms(500);
  asis_click(ASIS_BUTTON_L + ASIS_BUTTON_R);
  asis_wait_s(1);
  asis_click(ASIS_BUTTON_A);
  asis_wait_s(1);
  asis_click(ASIS_BUTTON_B);
  asis_wait_s(1);
}

void uasis_internal_home(void* args){
  asis_click(ASIS_BUTTON_HOME);
  asis_wait_s(2);
}

void uasis_home(void){
  if(uasis_home_func == UASIS_FUNC_NULL){
    uasis_home_func = asis_function(&uasis_internal_home,NULL);
  }
  asis_call(uasis_home_func);
}
