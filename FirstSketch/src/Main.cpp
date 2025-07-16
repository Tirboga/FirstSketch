#include <Arduino.h>
#include <RichShieldTM1637.h>
#include "Buzz.h"

//Переменный-------------------------------------------------------------------------------
int RED = 4;
int GREEN = 5;
int BLUE = 6;
int YELLOW = 7;
int ButtonK1 = 9;
int ButtonK2 = 8;
TM1637 disp(10,11);
int Knob = 0;

int ButtonEnable1 = 1;
int ButtonEnable2 = 1;
int ButtonEnable11 = 0;
int ButtonEnable22 = 0;
int SD = 1;
unsigned long timeSD;
unsigned long timeBU;
int8_t A,B,C,D;
int KnobVal;

//Объявление функций-------------------------------------------------------------------------
void SvetoDiod11();
void SvetoDiod00();
void SvetoDiod12();
void display(int8_t A,int8_t B,int8_t C,int8_t D,int p1,int p2,int p3,int p4);
void Knob1();
void Buzz1();

//Инициализация программы--------------------------------------------------------------------
void setup() 
{
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(YELLOW,OUTPUT);
  pinMode(ButtonK1,INPUT_PULLUP);
  pinMode(ButtonK2,INPUT_PULLUP);
  disp.init();
  A=1;
  B=1;
  C=16;
  D=16;
  display(A,C,D,B,0,0,0,0);
  timeSD = millis();
  timeBU = millis();
  pinMode(3,OUTPUT);
}

//Основная программа---------------------------------------------------------------------------
void loop() 
{ 
  if (digitalRead(ButtonK1)==LOW)
  {
    if(ButtonEnable1==1)
    {
      ButtonEnable1=0;
      timeBU = millis();
      timeSD = millis(); 
      A++;
      B=1;
      D=16;
      if(A>3){A=1;}
      display(A,C,D,B,0,0,0,0);
    }
  }
  else
  {
    if(millis()-timeBU>50)
    {
      if(ButtonEnable11==0)
      {
        ButtonEnable11=1;
        timeBU = millis();
      }
      else
      {
        ButtonEnable1=1;
        ButtonEnable11=0;
      }
    }
  }
  
  if (digitalRead(ButtonK2)==LOW)
  {
    if(ButtonEnable2==1)
    {
      ButtonEnable2=0;
      timeBU = millis();
      B++;
      D=16;
      if(B>3){B=1;}
      display(A,C,D,B,0,0,0,0);
    }
  }
  else
  {
    if(millis()-timeBU>50)
    {
      if(ButtonEnable22==0)
      {
        ButtonEnable22=1;
        timeBU = millis();
      }
      else
      {
        ButtonEnable2=1;
        ButtonEnable22=0;
      }
    }
  }

  switch(A)
  {
    case 1:
      switch(B)
      {
        case 1: SvetoDiod11(); break;
        case 2: SvetoDiod12(); break;
        default: SvetoDiod00(); break;
      }
    break;

    case 2:
      SvetoDiod00();
      switch(B)
      {
        case 1: Knob1(); break;
      }
    break;

    case 3:
      SvetoDiod00();
      switch(B)
      {
        case 1: Buzz1(); break;
      }
    break;
    
    default: SvetoDiod00(); break;
  }
}

//Функции-------------------------------------------------------------------------------------
//Светодиоды----------------------------------------------------------------------------------
void SvetoDiod11()
{
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH); 
  digitalWrite(BLUE, HIGH); 
  digitalWrite(YELLOW, HIGH); 
}

void SvetoDiod00()
{
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW); 
  digitalWrite(BLUE, HIGH); 
  digitalWrite(YELLOW, LOW);
}

void SvetoDiod12()
{
  if(millis()-timeSD>1000)
  {
    SD++;
    if(SD>4){SD=1;}
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW); 
    digitalWrite(BLUE, LOW); 
    digitalWrite(YELLOW, LOW);
    switch(SD)
    {
    case 1: digitalWrite(YELLOW, HIGH); break;
    case 2: digitalWrite(BLUE, HIGH); break;
    case 3: digitalWrite(GREEN, HIGH); break;
    case 4: digitalWrite(RED, HIGH); break;
    }
    timeSD = millis();
  }
}

//Дисплей---------------------------------------------------------------------------------
void display(int8_t A,int8_t B,int8_t C,int8_t D,int p1,int p2,int p3,int p4)
{
  disp._PointFlag = p1;
  disp.display(0x00,A);
  disp._PointFlag = p2;
  disp.display(0x01,B);
  disp._PointFlag = p3;
  disp.display(0x02,C);
  disp._PointFlag = p4;
  disp.display(0x03,D);
}

//Переменный резистор---------------------------------------------------------------------
void Knob1()
{
  int t1;
  int t2;

  KnobVal = analogRead(Knob); 
  t1 = KnobVal/204;
  t2 = (KnobVal%204)/21;
  display(A,C,t1,t2,0,0,1,0);
}

//Динамик---------------------------------------------------------------------------------
void Buzz1()
{
  long delayValue;
  long numCycles;
  long length;
  
  if(millis()-timeSD>10000)
  {
    for (int i = 0; i < 33; i++)
    {
      delayValue = 1000000 / doubleTiger[i] / 2;
      length = 500*tempo[i];
      numCycles = doubleTiger[i] * length / 1000; 
      for (long j = 0; j < numCycles; j++)
      {
      digitalWrite(3, HIGH);
      delayMicroseconds(delayValue);
      digitalWrite(3, LOW);
      delayMicroseconds(delayValue);
      }
    }
      timeSD = millis();
  }
  
}

//--------