#include "Encoder.h"
#define encoderLeftPinA  2
#define encoderLeftPinB  5
#define encoderRightPinA  3
#define encoderRightPinB  4
int32_t encoderLeft;
int32_t encoderRight;

void initial_encoder(void)
{
  pinMode(encoderLeftPinA, INPUT);
  pinMode(encoderRightPinA, INPUT);

  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderLeftA, CHANGE);

  // encoder pin on interrupt 1 (pin 3)
  attachInterrupt(1, d1EncoderRightA, CHANGE);
}
void doEncoderLeftA() {
  // look for a low-to-high on channel A
  if (digitalRead(encoderLeftPinA) == HIGH) {

    // check channel B to see which way encoder is turning
    if (digitalRead(encoderLeftPinB) == LOW) {
      encoderLeft = encoderLeft + 1;         // CW
    }
    else {
      encoderLeft = encoderLeft - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoderLeftPinB) == HIGH) {
      encoderLeft = encoderLeft + 1;          // CW
    }
    else {
      encoderLeft = encoderLeft - 1;          // CCW
    }
  }
  //Serial.println(encoderLeft);
}

void d1EncoderRightA() {
  if (digitalRead(encoderRightPinA) == HIGH) {
    // check channel A to see which way encoder is turning
    if (digitalRead(encoderRightPinB) == HIGH) {
      encoderRight = encoderRight + 1;         // CW
    }
    else {
      encoderRight = encoderRight - 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B

  else {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoderRightPinB) == LOW) {
      encoderRight = encoderRight + 1;          // CW
    }
    else {
      encoderRight = encoderRight - 1;          // CCW
    }
  }
  //Serial.println(encoderRight);
}
