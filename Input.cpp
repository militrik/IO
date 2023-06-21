//#include "stm32f1xx_hal.h"
//#include "main.h"
//#include "gpio.h"
#include "Input.hpp"


Input::Input ( 
							ButtonsNames _buttonName,
               uint32_t *_pin_port, 
               uint16_t _pin_num,
               bool _pin_activstate, 
               uint16_t _pin_longact,
               uint8_t _pin_pollnum
             )
{
	buttonName = _buttonName;
  pin_port = _pin_port;
  pin_num = _pin_num;
  pin_activstate = _pin_activstate;
  pin_longact = _pin_longact;
  pin_pollnum = _pin_pollnum;
}

void Input::Poll ( void )
{
  IsChanged = false; 
  {  
    bool pin;
    pin = !pin_activstate ^ (bool)(*pin_port & pin_num);
    if (pin)
    {
      if (pin_cnt<0) pin_cnt=0;
      pin_cnt++;
    }
    else
    {
      if (pin_cnt>0) pin_cnt=0;
      pin_cnt--;    
    }
  }
  if (pin_cnt>0 && pin_cnt>pin_pollnum) curr_pinstate = 1;
  if (pin_cnt<0 && pin_cnt<(-pin_pollnum)) curr_pinstate = 0;

  if (!prev_pinstate && !curr_pinstate) State = RELEASED;
  if (!prev_pinstate && curr_pinstate) State = PRESSING;
  if (prev_pinstate && !curr_pinstate) State = RELEASING;
  if (prev_pinstate && curr_pinstate) State = PRESSED;

  if (pin_cnt>0 && pin_cnt>pin_longact)
  {
    pin_cnt=pin_longact;
    if (State == PRESSED) State = HOLD;
  }
  if (pin_cnt<0 && pin_cnt<(-pin_longact))
  {
    pin_cnt=(-pin_longact);
    //if (State == RELEASED) State = HOLDN;
  }
  
  if (prev_State != State) IsChanged = true;
  prev_pinstate = curr_pinstate;   
  prev_State = State;
 
}

