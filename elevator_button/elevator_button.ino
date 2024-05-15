/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.11 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.11.4 or later version;
     - for iOS 1.9.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "Elevator with IR"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 78 bytes
  { 255,4,0,0,0,71,0,16,96,1,129,0,1,13,61,6,66,87,101,108,
  99,111,109,101,32,116,111,32,69,108,101,118,97,116,111,114,32,0,1,0,
  25,26,12,12,2,31,51,0,1,0,25,44,12,12,2,31,50,0,1,0,
  25,62,12,12,2,31,49,0,1,0,25,80,12,12,2,31,71,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t button_1; // =1 if button pressed, else =0 
  uint8_t button_2; // =1 if button pressed, else =0 
  uint8_t button_3; // =1 if button pressed, else =0 
  uint8_t button_4; // =1 if button pressed, else =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define MOTOR_SPEED 200

//Right motor
int enableRightMotor = 6;
int rightMotorPin1 = 7;
int rightMotorPin2 = 8;

//Left motor
int enableLeftMotor = 5;
int leftMotorPin1 = 9;
int leftMotorPin2 = 10;

int t=10;

const int IRGPin =  14;
const int IR1Pin =  15;
const int IR2Pin =  16;
const int IR3Pin =  17; 


int des_f=0;
int s_f=0;

int SensorValueG =0;
int SensorValue1 =0;
int SensorValue2 =0;
int SensorValue3 =0;



void setup() 
{
  RemoteXY_Init (); 
  
  TCCR0B = TCCR0B & B11111000 | B00000010;

  // put your setup code here, to run once:
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);    
  
  pinMode(IRGPin, INPUT);
  pinMode(IR1Pin, INPUT);
  pinMode(IR2Pin, INPUT);
  pinMode(IR3Pin, INPUT);

  rotateMotor(0, 0);
  t=10;
  
}

void loop() 
{ 
  RemoteXY_Handler ();
   read();
  if (SensorValueG==LOW){ // LOW MEANS Object Detected
    s_f=0;
   
  }
  else if (SensorValue1==LOW){ // LOW MEANS Object Detected
    s_f=1;
   
  }
  else if (SensorValue2==LOW){ // LOW MEANS Object Detected
    s_f=2;
    
  }
  else if (SensorValue3==LOW){ // LOW MEANS Object Detected
    s_f=3;
   
  }  

  if(RemoteXY.button_1==1 )
  {
      t=3;
  }
  if(RemoteXY.button_2==1 )
  {
      t=2;
  }
  if(RemoteXY.button_3==1 )
  {
      t=1;
  }
  if(RemoteXY.button_4==1 )
  {
      t=0;
  }
  if(t==3)
  {
    rotateMotor(MOTOR_SPEED, 0);
    SensorValue3 = digitalRead(IR3Pin);
    if (SensorValue3==LOW){
      t=10;
    }
  }
  if(t==2)
  {
    
    
  }
  if(t==1)
  {
    
  }
  if(t==0)
  {
    rotateMotor(-MOTOR_SPEED, 0);
    SensorValueG = digitalRead(IRGPin);
      if (SensorValueG==LOW){
        t=10;
      }  
    
  }
  else
  {
    rotateMotor(0, 0);
  }


}

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed) {

  if (rightMotorSpeed < 0) {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  } else if (rightMotorSpeed > 0) {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  } else {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
  }

  if (leftMotorSpeed < 0) {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  } else if (leftMotorSpeed > 0) {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  } else {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
  }
  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));
}

void read()
{
  SensorValueG = digitalRead(IRGPin);
  SensorValue1 = digitalRead(IR1Pin);
  SensorValue2 = digitalRead(IR2Pin);
  SensorValue3 = digitalRead(IR3Pin);
  
}
