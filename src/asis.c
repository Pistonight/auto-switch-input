/*
 * Auto Switch Input System
 */
/*Include*/
#include "asis.h"
#include "script_config.h"

//Instruction Memory
asis_insn_t asis_memory[ASIS_MAX_INSTRUCTION];
//Stack
uint16_t asis_stack[ASIS_MAX_STACK];
//Program Counter
uint16_t asis_pc;
//Load Counter;
uint16_t asis_lc;
//Stack pointer
uint16_t asis_sp;
//Duration Counter;
uint16_t asis_dc;

//Initialize
void asis_sys_init(void){
  asis_pc = 0;
  asis_lc = 0;
  asis_sp = 0;
  asis_dc = 0;
  int i;
  for(i=0;i<ASIS_MAX_INSTRUCTION;i++){
    asis_memory[i].operation=ASIS_INSN_EXIT;
  }
}


void asis_sys_set_pc(uint16_t new_pc){
  asis_pc = new_pc;
  if(asis_pc < ASIS_MAX_INSTRUCTION){
    asis_dc = asis_memory[asis_pc].duration;
  }
}

void asis_sys_prepare(void){
  asis_sys_set_pc(0);
}
//Cycle
void asis_sys_cycle(asis_packet_t* packet){
  asis_insn_t* insn;
  bool proceed = false;

  //Handle control flow first
  while(!proceed){
    if(asis_pc >= ASIS_MAX_INSTRUCTION ||
        asis_sp >= ASIS_MAX_STACK){
      packet->exit = true;
      return;//Buffer Overflow Protection
    }

    insn = asis_memory + asis_pc;
    switch(insn->operation){
      case ASIS_INSN_REPEAT:
        if(insn->arg2==0){
          //Repeat finish, just pass through
          insn->arg2 = insn->arg1;
          asis_sys_set_pc(asis_pc+1);
        }else{
          insn->arg2 = insn->arg2 - 1;
          asis_sys_set_pc(insn->duration); //jump_target is stored in duration
        }
        break;
      case ASIS_INSN_CALL:
        asis_stack[asis_sp]=asis_pc+1;//Return address
        asis_sp++;
        //Fall through
      case ASIS_INSN_JUMP:
        asis_sys_set_pc(insn->duration);//jump_target is stored in duration
        break;
      case ASIS_INSN_RET:
        asis_sys_set_pc(asis_stack[asis_sp-1]); 
        asis_sp--;
        break;
      default:
        proceed = true;
        break;
    }
  }
  insn = asis_memory + asis_pc;

  //Handle actual instructions
  switch(insn->operation){
    case ASIS_INSN_BUTTON:
      packet->button  = insn->button;
      packet->hat     = ASIS_D_PAD_CENTER;
      packet->stick_x = ASIS_STICK_CENTER;
      packet->stick_y = ASIS_STICK_CENTER;
      packet->wait    = 0;
      packet->exit    = false;
      break;
    case ASIS_INSN_STICK:
      packet->button  = ASIS_BUTTON_NOTHING;
      packet->hat     = ASIS_D_PAD_CENTER;
      packet->stick_x = insn->arg1;
      packet->stick_y = insn->arg2;
      packet->wait    = 0;
      packet->exit    = false;
      break;
    case ASIS_INSN_D_PAD:
      packet->button  = ASIS_BUTTON_NOTHING;
      packet->hat     = insn->button;
      packet->stick_x = ASIS_STICK_CENTER;
      packet->stick_y = ASIS_STICK_CENTER;
      packet->wait    = 0;
      packet->exit    = false;
      break;
    case ASIS_INSN_NOP:
      packet->button  = ASIS_BUTTON_NOTHING;
      packet->hat     = ASIS_D_PAD_CENTER;
      packet->stick_x = ASIS_STICK_CENTER;
      packet->stick_y = ASIS_STICK_CENTER;
      packet->wait    = insn->arg1;
      packet->exit    = false;
      break;
    case ASIS_INSN_EXIT:
      packet->exit    = true;
      break;
  }
  //Decrement duration counter
  if(asis_dc==0){
    asis_sys_set_pc(asis_pc+1);//Go to next instruction
  }else{
    asis_dc--;
  }
}

void asis_click(uint16_t button){
  asis_button(button,ASIS_BUTTON_DURATION);
}

void asis_button(uint16_t button,uint16_t duration){
  if(asis_lc>=ASIS_MAX_INSTRUCTION)return;
  asis_insn_t* insn = asis_memory + asis_lc;
  insn->operation = ASIS_INSN_BUTTON;
  insn->duration  = duration;
  insn->button    = button;
  insn->arg1      = 0;//Not Used
  insn->arg2      = 0;//Not Used
  asis_lc++;
}

void asis_stick(uint16_t x,uint16_t y, uint16_t duration){
  asis_insn_t* insn;
  if(asis_lc>=ASIS_MAX_INSTRUCTION)return;
  insn = asis_memory + asis_lc;
  insn->operation = ASIS_INSN_STICK;
  insn->duration  = duration;
  insn->button    = 0;
  insn->arg1      = x;//Stick x
  insn->arg2      = y;//Stick y
  asis_lc++;
}

void asis_d_pad(uint16_t dpad,uint16_t duration){
  if(asis_lc>=ASIS_MAX_INSTRUCTION)return;
  asis_insn_t* insn = asis_memory + asis_lc;
  insn->operation = ASIS_INSN_D_PAD;
  insn->duration  = duration;
  insn->button    = dpad;
  insn->arg1      = 0;//Not Used
  insn->arg2      = 0;//Not Used
  asis_lc++;
}

void asis_wait(uint16_t second){
  if(second>1000){
    asis_wait_ms(1000,second);
  }else{
    asis_wait_ms(second,1000);
  }
}

void asis_wait_ms(uint16_t repeat,uint16_t ms_each_time){
  asis_insn_t* insn;
  if(asis_lc>=ASIS_MAX_INSTRUCTION)return;
  insn = asis_memory + asis_lc;
  insn->operation = ASIS_INSN_NOP;
  insn->duration  = repeat;//How many times to execute the wait
  insn->button    = 0;
  insn->arg1      = ms_each_time;//How long to wait each time
  insn->arg2      = 0;//Not Used
  asis_lc++;
}

uint16_t asis_current(void){
  return asis_lc;
}

void asis_repeat(uint16_t jump_target,uint16_t repeat_time){
  asis_insn_t* insn;
  if(asis_lc>=ASIS_MAX_INSTRUCTION)return;
  insn = asis_memory + asis_lc;
  insn->operation = ASIS_INSN_REPEAT;
  insn->duration  = jump_target;
  insn->button    = 0;
  insn->arg1      = repeat_time;//repeat total
  insn->arg2      = repeat_time;//repeat counter
  asis_lc++;
}

uint16_t asis_function(void (*function)(void)){
  uint16_t function_location = asis_lc + 1;
  asis_insn_t* insn;
  if(asis_lc>=ASIS_MAX_INSTRUCTION-2)return 0;
  asis_lc++;
  function();
  //return instruction
  insn = asis_memory + asis_lc;
  insn->operation = ASIS_INSN_RET;
  insn->duration  = 0;
  insn->button    = 0;
  insn->arg1      = 0;
  insn->arg2      = 0;
  asis_lc++;
  if(asis_lc>=ASIS_MAX_INSTRUCTION)return 0;
  //put a jump instruction at top
  insn = asis_memory + function_location - 1;
  insn->operation = ASIS_INSN_REPEAT;
  insn->duration  = asis_lc;//Jump to after function
  insn->button    = 0;
  insn->arg1      = 1;//repeat total
  insn->arg2      = 1;//repeat counter
  return function_location;
}

void asis_call(uint16_t jump_target){
  asis_insn_t* insn;
  if(asis_lc>=ASIS_MAX_INSTRUCTION)return;
  insn = asis_memory + asis_lc;
  insn->operation = ASIS_INSN_CALL;
  insn->duration  = jump_target;
  insn->button    = 0;
  insn->arg1      = 0;
  insn->arg2      = 0;
  asis_lc++;
}

void asis_jump(uint16_t jump_target){
  asis_insn_t* insn;
  if(asis_lc>=ASIS_MAX_INSTRUCTION)return;
  insn = asis_memory + asis_lc;
  insn->operation = ASIS_INSN_JUMP;
  insn->duration  = jump_target;
  insn->button    = 0;
  insn->arg1      = 0;
  insn->arg2      = 0;
  asis_lc++;
}
void asis_exit(void){
  asis_insn_t* insn;
  if(asis_lc>=ASIS_MAX_INSTRUCTION)return;
  insn = asis_memory + asis_lc;
  insn->operation = ASIS_INSN_EXIT;
  insn->duration  = 0;
  insn->button    = 0;
  insn->arg1      = 0;
  insn->arg2      = 0;
  asis_lc++;
}




