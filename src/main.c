/*
 *  Copyright (c) 2014 Álan Crístoffer
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"

#include "utils.h"

static const char char_table[16] = {
  /*0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  A,  B,  C,  D,  E,  F */
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 65, 66, 67, 68, 69, 70};

void buffer_fill(char * _buf);

int main(void)
{
    DDRA = 0xFF;
    PORTA = 0;

    DDRC = 0;
    PORTC = 0;

    char str[] = "1 2 3 4 5 6 7 8 \r\n";
    uart0_init(UART_BAUD_SELECT(9600, F_CPU));
    sei();
    uart0_puts(str);

    while(1){
        char buf[19];
        buf[16]='\n';
        buf[17]='\r';

        buffer_fill(buf);
        uart0_puts(buf);
//        uart0_putc(PORTC);
        _delay_ms(1000);
    }


}

void buffer_fill(char _buf[]){
    for (uint8_t ind, i = 0; i < 8; ++i) {
        PORTA = 1 << i;
        ind = (PINC & 0xf0) >> 8;
        _buf[i*2] = char_table[ind];
        ind = PINC & 0x0f;
        _buf[i*2+1] = char_table[ind];
        PORTA = 0;
    }
}



