#include <xc.h>
#include "digital_header.h"

void init_config(void)
{
    TRISB = 0x00;
    PORTB = 0x01;

    init_digital_keypad();
}

void main(void)
{
    uint8_t key;
    uint8_t running = 0;
    uint8_t pattern = 1;
    uint8_t count = 0;
    uint16_t delay = 0;

    init_config();

    while(1)
    {
        key = read_digital_keypad(LEVEL);

        /* Select pattern */
        if(key == SW1)
        {
            running = 1;
            count = 0;
            PORTB = 0x01;
        }
        else if(key == SW2)
        {
            running = 2;
            count = 0;
            PORTB = 0x01;
        }
        else if(key == SW3)
        {
            running = 3;
            pattern = 1;
        }
        else if(key == SW4)
        {
            running = 4;
            pattern = 1;
        }

        /* Pattern 1 */
        if(running == 1)
        {
            if(delay++ >= 5000)
            {
                delay = 0;

                if(count < 8)
                {
                    PORTB = (PORTB << 1) | 0x01;
                }
                else if(count < 16)
                {
                    PORTB = PORTB >> 1;
                }
                else if(count < 24)
                {
                    PORTB = (PORTB >> 1) | 0x80;
                }
                else if(count < 32)
                {
                    PORTB = PORTB << 1;
                }

                count++;

                if(count == 32)
                {
                    count = 0;
                    PORTB = 0x01;
                }
            }
        }

        /* Pattern 2 */
        else if(running == 2)
        {
            if(delay++ >= 5000)
            {
                delay = 0;

                if(count < 8)
                {
                    PORTB = (PORTB >> 1) | 0x80;
                }
                else if(count < 16)
                {
                    PORTB = PORTB << 1;
                }

                count++;

                if(count == 16)
                {
                    count = 0;
                    PORTB = 0x01;
                }
            }
        }

        /* Pattern 3 */
        else if(running == 3)
        {
            if(delay++ >= 50000)
            {
                delay = 0;

                if(pattern == 0)
                {
                    PORTB = 0xAA;
                    pattern = 1;
                }
                else
                {
                    PORTB = 0x55;
                    pattern = 0;
                }
            }
        }

        /* Pattern 4 */
        else if(running == 4)
        {
            if(delay++ >= 50000)
            {
                delay = 0;

                if(pattern == 0)
                {
                    PORTB = 0x0F;
                    pattern = 1;
                }
                else
                {
                    PORTB = 0xF0;
                    pattern = 0;
                }
            }
        }
    }
}