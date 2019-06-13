#include "timer.h"
#include "PID.h"
#include "Kalman.h"
#include "I2Cdev.h"
#include "mpu6050trg.h"
#include "Uart.h"
#include "PWM.h"
#include "Encoder.h"
#include "Utils.h"
#include <avr/interrupt.h>
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif
#define RAD_TO_DEG 180/PI
Kalman kalmanY;
//MPU6050 accelgyro;
int16_t ax,ay,az;
int16_t gx,gy,gz;
uint32_t timer, timer1,dt;
float AngleY, GyroYrate, GyroYangle, Angle;
char RX_data;
boolean flag;
char buffer1[10];
char buffer2[10];
char buffer3[10];
char buffer4[10];
char buffer5[10];
char buffer6[10];
char sentdata[100];
const char Header[] = "Value %d.%d %d.%d\n";
extern String inputString;
extern float AngleRotate;
extern double distance, tdistance, tangle,trotate;

void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
//    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
//        Wire.begin();
//    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
//        Fastwire::setup(400, true);
//    #endif
//  accelgyro.initialize();
  mpu6050();
  initial_PWM();
  initial_encoder();
  Serial.begin(115200);
  Serial3.begin(115200);
  initial_timer1(0.01);
  timer1 = millis();
}

void loop() {
//sprintf(sentdata,"%3.1d,%3.1d,%3.1d,%3.1d,%3.1d,%3.1d",Angle,AngleRotate,distance,tangle,trotate,tdistance);
if((unsigned long)(millis()-timer1) > 100){
  Serial3.print(Angle);
  Serial3.print(",");
  Serial3.print(AngleRotate);
  Serial3.print(",");
  Serial3.print(distance);
  Serial3.print(",");
  Serial3.print(tangle);
  Serial3.print(",");
  Serial3.print(trotate);
  Serial3.print(",");
  Serial3.println(tdistance);
  timer1 = millis();
}
Process_MPU();
}
void print_data(float angle, float angleR, float dist,float tangle, float tangleR, float tdist)
{
  int angle_pre, angle_suf, angleR_pre, angleR_suf, dist_pre, dist_suf, tangle_pre, tangle_suf, tangleR_pre, tangleR_suf, tdist_pre, tdist_suf;
  parse_float(angle,angle_pre,angle_suf);
  parse_float(angleR,angleR_pre,angleR_suf);
  parse_float(dist,dist_pre,dist_suf);
  parse_float(tangle,tangle_pre,tangle_suf);
  parse_float(tangleR,tangleR_pre,tangleR_suf);
  parse_float(tdist,tdist_pre,tdist_suf);
  char buffsent[100];
  sprintf(buffsent,"%d.%d,%d.%d,%d.%d,%d.%d,%d.%d,%d.%d",angle_pre,angle_suf,angleR_pre,angleR_suf,dist_pre,dist_suf,tangle_pre,tangle_suf,tangleR_pre,tangleR_suf,tdist_pre,tdist_suf);
  Serial.println(buffsent);
}
void Process_MPU()
{
//  accelgyro.getMotion6(&ax,&ay,&az,&gx,&gy,&gz);
  ax = get_accx();
  ay = get_accy();
  az = get_accz();
  gx = get_gyrox();
  gy = get_gyroy();
  gz = get_gyroz();
  AngleY = (atan2(ax,az))*RAD_TO_DEG;
  GyroYrate = -(double)gy/131.0;
  //GyroYangle +=  GyroYrate*((double)(micros()-timer)/1000000);
  Angle = kalmanY.getAngle(AngleY,GyroYrate,(double)(micros()-timer)/1000000);
  timer = micros();
}

ISR(TIMER1_OVF_vect)
{
  
  TCNT1 = 63036;
  //Process_MPU();
  PID_balance();
//  Double2Str(Angle,1,buffer1);
//  Double2Str(AngleRotate,1,buffer2);
//  Double2Str(distance,3,buffer3);
//  Double2Str(tangle,1,buffer4);
//  Double2Str(trotate,1,buffer5);
//  Double2Str(tdistance,3,buffer6);
//  sprintf(sentdata,"%s,%s,$s,$s,$s,$s",buffer1,buffer2,buffer3,buffer4,buffer5,buffer6);
//  Serial.println(sentdata);
}

void serialEvent3()
{
  while(Serial3.available()){
    RX_data = (char)Serial3.read();
    inputString += RX_data;
    if(RX_data == '\n')
    {
      Parameter_receive();
    }
  }
}

