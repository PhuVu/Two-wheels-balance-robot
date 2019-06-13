#ifndef UTILS_H_
#define UTILS_H_
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h" 
#include "pins_arduino.h"
#endif
void String_Copy(uint8_t* stringin, uint8_t* stringout);
void String_Clear(uint8_t* string);
void String_RemoveCRLF(uint8_t* stringin, uint8_t* stringout);
void String_Split(uint8_t* stringin, uint8_t character, uint8_t startpos, uint8_t* stringout);
double Str2Double(uint8_t *string);
void parse_float(float val, int &prefix, int &suffix);
void Int2Str(int32_t inum, uint8_t* string);
void Double2Str(double dbnum,uint8_t num_of_frac,char* string);
#endif
