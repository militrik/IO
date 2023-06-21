#ifndef __INPUT_H
#define __INPUT_H

//#include "stdint.h"
//#include "stm32g0xx.h"
#include <cstdint>

/* User defined buttons enumerator */
typedef enum 
{
	ENTER, ESC, LEFT, RIGHT,
	LASTBUTTON
}ButtonsNames;


#ifndef ACTIVE_PINSTATE_HIGH
#define ACTIVE_PINSTATE_HIGH 1
#endif
#ifndef ACTIVE_PINSTATE_LOW
#define ACTIVE_PINSTATE_LOW 0
#endif

class Input
{
public:
    typedef enum 
    {
        
        UNCERTAIN,            // неопределенное
        
        PRESSED,              // нажато              
        RELEASED,             // отпущено            
        PRESSING,             // нажатие             
        RELEASING,            // отпускание          
        HOLD,                 // долгое нажатие
        HOLDN,                // долгое отпускание
        
        LASTPINSTATE          // не модифицировать
    }ButtonStates;
private:
    uint32_t * pin_port;
    uint16_t pin_num;
    bool pin_activstate;
    uint16_t pin_longact;
    uint8_t pin_pollnum;
    
    bool prev_pinstate, curr_pinstate;
    int16_t pin_cnt;
    
    ButtonStates prev_State;
    
public:
    Input(ButtonsNames, uint32_t *, uint16_t, bool, uint16_t, uint8_t);
    void Poll (void);
    ButtonStates State;
    ButtonsNames buttonName;
    bool IsChanged;
};


typedef struct 
{
    ButtonsNames button_name;
    Input::ButtonStates button_state;
} Button;

#define CheckButt(var,state) var==state
#define SetButt(var,state) var=state

#endif
