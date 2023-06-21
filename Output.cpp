#include "stm32f1xx_hal.h"
#include "main.h"
#include "gpio.h"
#include "Output.h"


Output::Output ( 
                 GPIO_TypeDef * _pin_port, 
                 uint16_t _pin_num,
                 bool _pin_activstate )
{
  pin_port = _pin_port;
  pin_num = _pin_num;
  pin_activstate = _pin_activstate;
}

void Output::Poll ( bool state) 
{
  HAL_GPIO_WritePin(pin_port, pin_num, (GPIO_PinState)(!pin_activstate ^ state));
}

