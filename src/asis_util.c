/*
 * Utility functions that makes the scripts easier to make
 */

#include "asis.h"

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

void uasis_home(void){
  asis_click(ASIS_BUTTON_HOME);
  asis_wait_s(2);
}
