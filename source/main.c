/*	Author: kma023
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum states {start, init, reset, decrement, increment, wait0, wait1} state;
void count() {
	switch(state) {
                case start:	
                        state = init;
                        break;
                case init:
                        if((PINA & 0x03) == 0x03) {
                                state = reset;
                        }
                        else if((PINA & 0x03) == 0x02) {
                                state = decrement;
                        }
                        else if((PINA & 0x03) == 0x01) {
                                state = increment;
                        }
                        else {
                                state = init;
                        }
                        break;
                case decrement:
                       	state = wait0;
                        break;
		case wait0: 
			if((PINA & 0x03) == 0x02) {
                                state = decrement;
                        }
                        else if((PINA & 0x03) == 0x01) {
                                state = increment;
                        }
                        else if((PINA & 0x03) == 0x03) {
                                state = reset;
                        }
			else {
				state = wait0;
			}
			break;
                case increment:
			state = wait1;
                        break;
		case wait1:
			if((PINA & 0x03) == 0x01) {
                                state = increment;
                        }
                        else if((PINA & 0x03) == 0x03) {
                                state = reset;
                        }
			else if((PINA & 0x03) == 0x02) {
				state = decrement;
			}
			else {
				state = wait1;
			}
                        break;
		case reset:
                        if((PINA & 0x03) == 0x02) {
                                state = decrement;
                        }
                        else if((PINA & 0x03) == 0x01) {
                                state = increment;
                        }
                        else if((PINA & 0x03) == 0x03) {
                                state = reset;
                        }
                        else {
                                state = init;
                        }
                        break;

                default:
                        state = init;
                        break;
        }

        switch(state) {
		case start:
		
		case init:
			PORTB = 0x07;
			 break;
		
		case decrement:
                        if(PORTB > 0)
 			{
                                PORTB = PORTB - 1;
                        }
                        break;
		
		case wait0:
                        break;

                case increment:
                        if(PORTB < 0x09) {
                                PORTB = PORTB + 1;
                        }
                        break;
	
		case wait1:
			break;
		case reset:
                        PORTB = 0x00;
                        break;

                default:
                        break;
        }
}
int main(void) {

        DDRA = 0x00; PORTA = 0xFF;
        DDRB = 0xFF; PORTB = 0x00;
	state = start;
	while(1){
		count();
	}
	
	return 1;
}
