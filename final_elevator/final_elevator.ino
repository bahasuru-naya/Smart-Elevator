/*
   -- lift 1 --
   
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
#define REMOTEXY_WIFI_SSID "WIFI Elevator"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 77 bytes
  { 255,2,0,0,0,70,0,16,96,1,3,132,9,51,45,12,2,26,129,0,
  12,43,39,8,64,71,32,32,32,49,32,32,32,50,32,32,32,51,0,1,
  0,22,76,17,17,2,31,71,79,0,129,0,2,23,58,6,51,87,101,108,
  99,111,109,101,32,116,111,32,69,108,101,118,97,116,111,114,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t select_1; // =0 if select position A, =1 if position B, =2 if position C, ... 
  uint8_t button_1; // =1 if button pressed, else =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define MOTOR_SPEED 220

//Right motor
int enableRightMotor = 6;
int rightMotorPin1 = 7;
int rightMotorPin2 = 8;

//Left motor
int enableLeftMotor = 5;
int leftMotorPin1 = 9;
int leftMotorPin2 = 10;

int t=0;

const int IRGPin =  14;
const int IR1Pin =  15;
const int IR2Pin =  16;
const int IR3Pin =  17; 

int cur_f=0;
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
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  read();
  if (SensorValueG==LOW){ 
    s_f=0;
   
  }
  else if (SensorValue1==LOW){ 
    s_f=1;
   
  }
  else if (SensorValue2==LOW){ 
    s_f=2;
    
  }
  else if (SensorValue3==LOW){ 
    s_f=3;
   
  }
  else
  {
    for(;SensorValueG==HIGH;){
       rotateMotor(-MOTOR_SPEED, 0);
       SensorValueG = digitalRead(IRGPin);

    }
    rotateMotor(0, 0);
  }
  

  

  
       if(RemoteXY.select_1==0){
          if(RemoteXY.button_1==1 )
          {
            for(;SensorValueG==HIGH;){
          rotateMotor(-MOTOR_SPEED, 0);
          SensorValueG = digitalRead(IRGPin);

          }
         rotateMotor(0, 0);    
          }
          else
         {
            rotateMotor(0, 0);
          }

        
        
       

      }
      else if(RemoteXY.select_1==1){

      }
      else if(RemoteXY.select_1==2){

      }
      else if(RemoteXY.select_1==3){
        if(RemoteXY.button_1==1 )
          {
          for(;SensorValue3==HIGH;){
          rotateMotor(MOTOR_SPEED, 0);
          SensorValue3 = digitalRead(IR3Pin);

        }
        rotateMotor(0, 0); 
          }
          else
         {
            rotateMotor(0, 0);
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



