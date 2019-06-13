#include "Utils.h"
#define EXP               1000  // độ chính xác đến 3 chữ số thập phân (1
void String_Copy(uint8_t* stringin, uint8_t* stringout)
{
  uint8_t i = 0;
  while(stringout[i] != '\0')
  {
    stringout[i] = 0; //clear old data
    i++;
  }
  i = 0;
  while(stringin[i] !='\0')
  {
    stringout[i] = stringin[i];
    i++;
  }
}
void String_Clear(uint8_t* string)
{
  uint8_t i = 0;
  while(string[i] != '\0')
  {
    string[i] = 0;
    i++;
  }
  i = 0;
}
void String_RemoveCRLF(uint8_t* stringin, uint8_t* stringout)
{
   String_Clear(stringout);
   while(*stringin != '\0')
   {
     if(*stringin == '\r' || *stringin == '\n')
     {
       //next
     }
     else
     {
       *(stringout++) = *stringin;
     }
     stringin++;
   }  
}
void String_Split(uint8_t* stringin, uint8_t character, uint8_t startpos, uint8_t* stringout)
{
  uint8_t count = 0;
  while(stringout[count] != '\0')
  {
    stringout[count] = 0; //clear string data
    count++;
  }
  count = 0;
  while(*stringin != '\0')
  {
    if(*stringin == character)
    {
      count++;
    }
    else
    {
      if(count == startpos)
      {
        *(stringout++) = *stringin;
      }
    }
    stringin++;
  }
}
double Str2Double(uint8_t *string)
{
  return atof((char*)string);
}
void parse_float(float val, int &prefix, int &suffix) {
  prefix = int(val);
  suffix = abs((val - prefix)) * EXP;
}
void Double2Str(double dbnum,uint8_t num_of_frac,char* string)
{
  int32_t decnum = 0, powfracnum = 0;
  double fracnum = 0;
  uint8_t decstr[20] = {0}, fracstr[20] = {0};
  uint8_t i = 0, id = 0, ifr = 0;
  while(string[i] != '\0')
  {
    string[i] = 0;  //clear string data
    i++;
  }
  i = 0;
  decnum = (int)dbnum;// get decimal
  if(dbnum>=0)
  {
    fracnum = dbnum - decnum;//get fraction
  }
  else
  {
    fracnum = -(dbnum - decnum);//get fraction
  }
  Int2Str(decnum,decstr);
  powfracnum = (uint32_t)(fracnum*pow(10.0,num_of_frac));//convert fraction to decimal with num of fraction
  Int2Str(powfracnum,fracstr);//convert fraction to string
  while(decstr[id] != '\0')// add decimal string to dest string
  {
    string[id] = decstr[id];
    id++;
  }
  string[id] = '.';//add '.'
  while(fracstr[ifr] != '\0')//add fraction string to dest string
  {
    string[id+1+ifr] = fracstr[ifr];
    ifr++;
  } 
}
void Int2Str(int32_t inum, uint8_t* string)
{
  bool sign = false; //possitive
  uint8_t numcount = 0, i = 0, j = 0;
  uint32_t temp = 0, posnum = 0, pownum = 0;
  while( string[i] != '\0')
  {
    string[i] = 0;  //clear string data
    i++;
  }
  i = 0;
  if(inum>=0)//positive
  {
    posnum = inum;
    sign = false;
  }
  else     //negative
  {
    posnum = -inum;
    sign = true;
    *(string++) = '-';
  }
  temp = posnum;
  while(temp > 0)
  {
    numcount++;
    temp = temp/10; // divide and take decimal
  }
  temp = posnum;
  if(numcount == 0) // ~ inum = 0
  {
    *string = '0';
  }
  else
  {
    for(i=0;i<numcount;i++)
    {
      pownum = 1;
      for(j=i+1;j<numcount;j++)
      {
        pownum = pownum*10;
      }
      *(string++) = temp/pownum + 48;
      temp = temp%pownum;
    }
  }
}
