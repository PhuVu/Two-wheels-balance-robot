#ifndef PID_H_
#define PID_H_
void PID_balance();
double PIDAngle_Process (double setpoint);
double PID_Position(double setpoint);
double PID_Speed(double setpoint);
#endif
