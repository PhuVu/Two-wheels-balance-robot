#include "PWM.h"
//#include <avr/io.h>
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include "pins_arduino.h"
#endif
#define MAX_SPEED 255
#define MIN_SPEED 0
int DirLeft1 = 6, DirLeft0 = 53, DirRight1 = 8, DirRight0 = 52 , PWMLeft = 9, PWMRight = 10;
void initial_PWM(void)
{
  pinMode(PWMRight, OUTPUT);

  pinMode(PWMLeft, OUTPUT);
//  DDRB |= (1<<9);
//  DDRB |= (1<<10);//set the OCR1 pins as outputs
  pinMode(DirLeft0, OUTPUT);
  pinMode(DirLeft1, OUTPUT);
  pinMode(DirRight0, OUTPUT);
  pinMode(DirRight1, OUTPUT);
  int myEraser = 7;             // this is 111 in binary and is used as an eraser
  TCCR2B &= ~myEraser;   // this operation (AND plus NOT),  set the three bits in TCCR2B to 0
  int myPrescaler = 1;         // this could be a number in [1 , 6]. In this case, 3 corresponds in binary to 011.   
  TCCR2B |= myPrescaler;  //this operation (OR), replaces the last three bits in TCCR2B with our new value 011
//  prescaler = 1 ---> PWM frequency is 31000 Hz
//prescaler = 2 ---> PWM frequency is 4000 Hz
//prescaler = 3 ---> PWM frequency is 490 Hz (default value)
//prescaler = 4 ---> PWM frequency is 120 Hz
//prescaler = 5 ---> PWM frequency is 30 Hz
//prescaler = 6 ---> PWM frequency is <20 Hz

//     
//  TCCR1B |= (1<<CS11) | (1<<CS10);//set timer1 clock prescaler to 64
//  TCCR1A |= (1<<WGM10) | (1<<WGM12); //fast pwm (8bit) with top as 0x03FF

//This bits for incase you want 16bit and not 10bit PWM on timer1
//        TCCR1A |= (1<<WGM11)
//                | (1<<WGM12)
//                | (1<<WGM13); //fast pwm (16bit) with top as 0x03FF
//        //ICR1H = 0xFF; //set IRC1 to max for full 16bit resolution
//        //IRC1L = 0xFF;
  //TIMSK1 |= (1 << TOIE1); 
  //TCCR1A = (1 << WGM10);
  //sei();
}
void PWMLEFT(int16_t value)
{
  TCCR1A |= (1<<COM1A1);
  OCR1A = value;
}
void PWMRIGHT(int16_t value)
{
  TCCR1A |= (1<<COM1B1);
  OCR1B = value;
}
int Out_PWM_Left(int out)
{
  if (out > 0)
  {
    //PWMLEFT(out);
    analogWrite(PWMLeft,out);
    //OCR1A = out;
    digitalWrite(DirLeft0, HIGH);
    digitalWrite(DirLeft1, LOW);
  }
  if (out < 0)
  {
    //PWMLEFT(-out);
    analogWrite(PWMLeft,-out);
    //OCR1A = -out;
    digitalWrite(DirLeft0, LOW);
    digitalWrite(DirLeft1, HIGH);
  }
}

int Out_PWM_Right(int out)
{

  if (out > 0)
  {
    //PWMRIGHT(out);
    analogWrite(PWMRight,out);
    //OCR1B = out;
    digitalWrite(DirRight0, HIGH);
    digitalWrite(DirRight1, LOW);
  }
  if (out < 0)
  {
    //PWMRIGHT(-out);
    analogWrite(PWMRight,-out);
    //OCR1B = -out;
    digitalWrite(DirRight0, LOW);
    digitalWrite(DirRight1, HIGH);
  }
}

