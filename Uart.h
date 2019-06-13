#ifndef UART_H_
#define UART_H_
#define CR                    '\r'
#define LF                    '\n'
#define Line                  (uint8_t*)"\n"
#define CR_LF                 (uint8_t*)"\r\n"
#define LNG_READ              5   // user
#define LNG_MAX               50  // max length of frame on USART
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h" 
#include "pins_arduino.h"
#endif
typedef struct
 {
   uint8_t     isdone; //confirm when all data is received by line
   uint16_t count; //count received data
   uint16_t LNG;   //length of received data
   char  receive[LNG_MAX];// store received data on USART Rx Interrupt
   char  string[LNG_MAX]; // store full of received data
 }USART_t;
 void Parameter_receive();
 void Process_Receive();
 void Process_MPU();
#endif
