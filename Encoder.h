#ifndef ENCODER_H_
#define ENCODER_H_
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include "pins_arduino.h"
#endif
void initial_encoder(void);
void doEncoderLeftA();
void d1EncoderRightA();
#endif
