#include "Uart.h"
#include "Utils.h"
#include "stdlib.h"

USART_t PID_Usart = {0,0,0,{0},{0}};
char ParaReceive[25];
String inputString;
String head;
boolean flagsent;
extern char RX_data;
extern double KpAngle, KiAngle, KdAngle;
extern double KpSp, KiSp, KdSp;
extern double KpRo, KiRo, KdRo;
extern double KpPo, KiPo, KdPo, distance;
extern boolean flag;
extern float CPo, CRo, AngleRotate;
int ind1; // , locations
int ind2;
int ind3;
int ind4;

void Parameter_receive()
{
   ind1 = inputString.indexOf(',');
   head = inputString.substring(0, ind1);
   Process_Receive();
   inputString = "";
}

void Process_Receive()
{
  String Kp, Ki, Kd, strCP, strCR;
  if(head == "PID1")
  {
    ind2 = inputString.indexOf(',',ind1+1);
    Kp = inputString.substring(ind1 + 1, ind2);
    KpAngle = atof(Kp.c_str());
    ind3 = inputString .indexOf(',',ind2+1);
    Ki = inputString.substring(ind2+1, ind3);
    KiAngle = atof(Ki.c_str());
    ind4 = inputString.indexOf(',',ind3+1);
    Kd = inputString.substring(ind3+1,ind4);
    KdAngle = atof(Kd.c_str());
    Serial.println(KdAngle);
  }
  if(head == "PID2")
  {
    ind2 = inputString.indexOf(',',ind1+1);
    Kp = inputString.substring(ind1 + 1, ind2);
    KpSp = atof(Kp.c_str());
    ind3 = inputString .indexOf(',',ind2+1);
    Ki = inputString.substring(ind2+1, ind3);
    KiSp = atof(Ki.c_str());
    ind4 = inputString.indexOf(',',ind3+1);
    Kd = inputString.substring(ind3+1,ind4);
    KdSp = atof(Kd.c_str());
  }
  if(head == "PID3")
  {
    ind2 = inputString.indexOf(',',ind1+1);
    Kp = inputString.substring(ind1 + 1, ind2);
    KpPo = atof(Kp.c_str());
    ind3 = inputString .indexOf(',',ind2+1);
    Ki = inputString.substring(ind2+1, ind3);
    KiPo = atof(Ki.c_str());
    ind4 = inputString.indexOf(',',ind3+1);
    Kd = inputString.substring(ind3+1,ind4);
    KdPo = atof(Kd.c_str());
  }
  if(head == "PID4")
  {
    ind2 = inputString.indexOf(',',ind1+1);
    Kp = inputString.substring(ind1 + 1, ind2);
    KpRo = atof(Kp.c_str());
    ind3 = inputString .indexOf(',',ind2+1);
    Ki = inputString.substring(ind2+1, ind3);
    KiRo = atof(Ki.c_str());
    ind4 = inputString.indexOf(',',ind3+1);
    Kd = inputString.substring(ind3+1,ind4);
    KdRo = atof(Kd.c_str());
  }
  if(head == "SET")
  {
    ind2 = inputString.indexOf(',',ind1+1);
    strCP = inputString.substring(ind1 + 1, ind2);
    CPo = atof(strCP.c_str());
    ind3 = inputString.indexOf(',',ind2 +1);
    strCR = inputString.substring(ind2+1,ind3);
  }
  if(head == "1")
  {
    CPo = CPo + 0.1;
    Serial3.println(inputString);
  }
  if(head == "2")
  {
    CPo = CPo -0.1;
  }
  if(head == "3")
  {
    CRo = CRo + 10;
  }
  if(head == "4")
  {
    CRo = CRo - 10;
  }
  if(head == "5")
  {
    CPo = distance;
    CRo = AngleRotate;
  }
  if(head == "9")
  {
    flagsent = true;
  }
}

