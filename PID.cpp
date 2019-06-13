#include "PWM.h"
#include "uart.h"
double PIDangle, KpAngle = 40, KiAngle, KdAngle =-6;//Kp = 40 ,Ki = 0, Kd = -5
double Pangle, Iangle, Dangle, ErrorAngle, PreErrorAngle, tangle;
////////////////////////////////
double PIDPosition, KpPo=0.02, KiPo=0.01, KdPo=0.005;
double PPo, IPo, DPo, ErrorPo, PreErrorPo, distance, tdistance;
///////////////////////////////
double PIDSpeed, KpSp=0.8, KiSp=0.5, KdSp;// Kp = 0.8, Ki = 0.2, Kd = 0;
double PSp, ISp, DSp, ErrorSp, PreErrorSp;
///////////////////////////////
double PIDRotate, KpRo = 20, KiRo = 15, KdRo=0;// Kp = 
double PRo, IRo, DRo, ErrorRo, PreErrorRo, OutRo, trotate;
int16_t DeltaPulse;
float PulsetoDegree = 0.2667 , AngleRotate;//Db2w = 0.27m
///////////////////////////////
float tsample = 0.01, invtsample = 100;
double OutPosition, OutSpeed, OutPWM, OutPWMLeft, OutPWMRight;
int64_t Pulse, prePulseSpeed;
extern int32_t encoderLeft, encoderRight;
int LimitPWM = 255;
float LimitPo = 0.5, LimitSp = 18, Speed;
int8_t tdelaySp, tdelayPo;
double CalibPoSp = 0;
extern float Angle,GyroYrate;
float CPo, CRo;
double PIDAngle_Process (double setpoint)
{
  ErrorAngle = setpoint - Angle +1;
  Pangle = KpAngle*ErrorAngle;
  Iangle = KiAngle*ErrorAngle*tsample;
  //Dangle = KdAngle*(ErrorAngle-PreErrorAngle)*invtsample;
  Dangle = KdAngle*GyroYrate;
  PIDangle = Pangle + Iangle + Dangle;
  PreErrorAngle = ErrorAngle;
  return PIDangle;
}
double PID_Position(double setpoint)
{
  tdelayPo++;
  if(tdelayPo == 5)
  {
    distance = PI*0.08*Pulse/200;
    ErrorPo = setpoint - distance;
    PPo = KpPo*ErrorPo;
    IPo = KiPo*ErrorPo*tsample*5;
    DPo = KdPo*(ErrorPo-PreErrorPo)*20;
    PIDPosition = PPo + IPo + DPo;
    PreErrorPo = ErrorPo;
    if(PIDPosition > LimitPo) PIDPosition = LimitPo;
    if(PIDPosition < -LimitPo) PIDPosition = -LimitPo;
    tdelayPo = 0;
  }
  return PIDPosition;
}

double PID_Speed(double setpoint)
{
  tdelaySp++;
  if(tdelaySp == 5)
  {
    CalibPoSp = setpoint*796;
    Speed = Pulse - prePulseSpeed;
    prePulseSpeed = Pulse;
    ErrorSp = CalibPoSp -Speed;
    PSp = KpSp*ErrorSp;
    ISp = KiSp*ErrorSp*tsample*5;
    DSp = KdSp*(ErrorSp-PreErrorSp)*20;
    PIDSpeed = PSp + ISp + DSp;
    PreErrorSp = ErrorSp;
    if(PIDSpeed > LimitSp) PIDSpeed = LimitSp;
    if(PIDSpeed < -LimitSp) PIDSpeed = -LimitSp;
    tdelaySp = 0;
  }
  return PIDSpeed;
}
double PID_Rotate(float setpoint)
{
  DeltaPulse = (encoderLeft - encoderRight);
  AngleRotate = DeltaPulse * PulsetoDegree;
  ErrorRo = setpoint - AngleRotate;
  PRo = KpRo*ErrorRo;
  IRo = KiRo*ErrorRo*tsample;
  DRo = KdRo*(ErrorRo - PreErrorRo)* invtsample;
  PIDRotate = PRo + IRo + DRo;
  //if(PIDRotate > 100 ) PIDRotate = 100;
  //if(PIDRotate < -100) PIDRotate = -100;
  return PIDRotate;
}
void PID_balance()
{
  Pulse = (encoderLeft + encoderRight)/2;
  OutPosition = PID_Position(CPo);
  OutSpeed = PID_Speed(OutPosition);
  OutPWM = PIDAngle_Process(OutSpeed);
  OutRo = PID_Rotate(CRo);

  OutPWMLeft = OutPWM - OutRo;
  OutPWMRight = OutPWM +OutRo;
  if(OutPWMLeft > LimitPWM) OutPWMLeft = LimitPWM - 10;
  if(OutPWMLeft < - LimitPWM) OutPWMLeft = -LimitPWM +10;
  if(OutPWMRight > LimitPWM) OutPWMRight = LimitPWM -10;
  if(OutPWMRight < -LimitPWM) OutPWMRight = -LimitPWM+10;
  if(Angle<40 && Angle >-40)
  {
    Out_PWM_Left(OutPWMLeft);
    Out_PWM_Right(OutPWMRight);
    //Serial.println(Angle);
  }
}

