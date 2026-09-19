#include<xc.h>
#include "digital_header.h"


void init_digital_keypad(void)
{
    TRISC = TRISC | 0x0F;
}

uint8_t read_digital_keypad(uint8_t trigger)
{
    static uint8_t flag=1;
    
    if(trigger == LEVEL)
    {
       return PORTC & 0x0F;
    }
    else if(trigger == EDGE)
    {
     if(((PORTC & 0x0F) != ALL_RELEASED) && (flag ==1))
        {
          flag=0;
          return PORTC & 0x0F;
        }else if((PORTC & 0x0F) == ALL_RELEASED)
        {
            flag=1;
        }
     return ALL_RELEASED;
    }
    return ALL_RELEASED;
}