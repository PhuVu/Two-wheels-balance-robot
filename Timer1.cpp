#include "timer.h"
#include <avr/interrupt.h>

void initial_timer1(int thgian)
{
  cli(); 
  /* Reset Timer/Counter1 */
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;
    /* Setup Timer/Counter1 */
    TCCR1B |= (1 << CS11) | (1 << CS10);    // prescale = 64
    TCNT1 = 65536-16000000*thgian/64;                         // time = (65536-TCNT1)*64/16MHz =>TCNT1 = 65536 -16MHz*time/64
    TIMSK1 |= (1 << TOIE1);                  // Overflow interrupt enable 
    sei();                                  // cho phép ngắt toàn cục
}

void initial_timer2(int thgian)
{
    cli(); 
  /* Reset Timer/Counter1 */
    TCCR2A = 0;
    TCCR2B = 0;
    TIMSK2 = 0;
    /* Setup Timer/Counter1 */
    TCCR2B |= (1 << CS22);    // prescale = 64
    TCNT2 = 65536-16000000*thgian/64;                         // time = (65536-TCNT1)*64/16MHz =>TCNT1 = 65536 -16MHz*time/64
    TIMSK2 |= (1 << TOIE2);                  // Overflow interrupt enable 
    sei();                                  // cho phép ngắt toàn cục
}

void initial_timer0(int thgian)
{
    cli(); 
  /* Reset Timer/Counter1 */
    TCCR0A = 0;
    TCCR0B = 0;
    TIMSK0 = 0;
    /* Setup Timer/Counter1 */
    TCCR0B |= (1 << CS01) | (1 << CS00);    // prescale = 64
    TCNT0 = 65536-16000000*thgian/64;                         // time = (65536-TCNT1)*64/16MHz =>TCNT1 = 65536 -16MHz*time/64
    TIMSK0 |= (1 << TOIE0);                  // Overflow interrupt enable 
    sei();                                  // cho phép ngắt toàn cục
}

