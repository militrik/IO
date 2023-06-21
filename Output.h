#ifndef __OUTPUT_H
#define __OUTPUT_H

#include "stdint.h"
#include "stm32f1xx_hal.h"

enum
{
  OFF=0,              // включить              
  ON             // выключить            
};

#ifndef ACTIVE_PINSTATE_HIGH
#define ACTIVE_PINSTATE_HIGH 1
#endif
#ifndef ACTIVE_PINSTATE_LOW
#define ACTIVE_PINSTATE_LOW 0
#endif

class Output
{
private:
  GPIO_TypeDef * pin_port;
  uint16_t pin_num;
  
 
public:
  bool pin_activstate;
  Output(GPIO_TypeDef *, uint16_t, bool);
  void Poll (bool);
};
#endif

