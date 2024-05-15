/*
   -- lift --
   
   P.H.D.B.Nayanakantha
   Elevator prototype 
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
#define REMOTEXY_WIFI_SSID "My Elevator"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 68 bytes
  { 255,2,0,68,0,61,0,16,96,1,67,5,22,22,19,22,36,26,6,3,
  132,12,57,40,11,2,26,129,0,14,49,35,7,64,71,32,32,32,49,32,
  32,32,50,32,32,32,51,0,1,0,23,75,17,17,2,31,71,79,0,67,
  5,0,12,64,6,2,26,62 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t select_1; // =0 if select position A, =1 if position B, =2 if position C, ... 
  uint8_t button_1; // =1 if button pressed, else =0 

    // output variables
  char text_1[6];  // string UTF8 end zero 
  char text_2[62];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////
#define MOTOR_SPEED 210

//Right motor
int enableRightMotor = 6;
int rightMotorPin1 = 7;
int rightMotorPin2 = 8;

//Left motor
int enableLeftMotor = 5;
int leftMotorPin1 = 9;
int leftMotorPin2 = 10;

 

const int IRGPin =  14;
const int IR1Pin =  15;
const int IR2Pin =  16;
const int IR3Pin =  17;  

char strW[] = "Select floors & Press GO";
char str[] = "Going....";
char strs[] = "Same floor choose another";
char strG[] = "Lift reached ground floor";
char str1[] = "Lift reached 1st floor";
char str2[] = "Lift reached 2nd floor";
char str3[] = "Lift reached 3rd floor";

char sG[] = "↑G";
char s1[] = "1";
char s2[] = "2";
char s3[] = "3";

int cur_f=0;
int des_f=0;
int s_f=0;

int t =0;

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

  strcpy  (RemoteXY.text_1, sG);//set text
  strcpy  (RemoteXY.text_2, strW);//set text
  
}

void loop() 
{ 
  RemoteXY_Handler ();
   read();
  sdisplay();

  des_f =RemoteXY.select_1;
  
  
  if(RemoteXY.button_1==1 )
    {
      
      go(s_f,RemoteXY.select_1);
      
      
    }
   else
   {
    

   }

    
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay(), use instead RemoteXY_delay() 


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

void sdisplay()
{
  if (SensorValueG==LOW){ // LOW MEANS Object Detected
    s_f=0;
    strcpy  (RemoteXY.text_1, sG);
  }
   if (SensorValue1==LOW){ // LOW MEANS Object Detected
    s_f=1;
    strcpy  (RemoteXY.text_1, s1);
  }
   if (SensorValue2==LOW){ // LOW MEANS Object Detected
    s_f=2;
    strcpy  (RemoteXY.text_1, s2);
  }
   if (SensorValue3==LOW){ // LOW MEANS Object Detected
    s_f=3;
    strcpy  (RemoteXY.text_1, s3);
  }
  else{
     s_f=0;
  }
  
}

void cdisplay()
{
  if (SensorValueG==LOW){ // LOW MEANS Object Detected
    cur_f=0;
    strcpy  (RemoteXY.text_1, sG);
  }
   if (SensorValue1==LOW){ // LOW MEANS Object Detected
    cur_f=1;
    strcpy  (RemoteXY.text_1, s1);
  }
   if (SensorValue2==LOW){ // LOW MEANS Object Detected
    cur_f=2;
    strcpy  (RemoteXY.text_1, s2);
  }
   if (SensorValue3==LOW){ // LOW MEANS Object Detected
    cur_f=3;
    strcpy  (RemoteXY.text_1, s3);
  }
  
}

void read()
{
  SensorValueG = digitalRead(IRGPin);
  SensorValue1 = digitalRead(IR1Pin);
  SensorValue2 = digitalRead(IR2Pin);
  SensorValue3 = digitalRead(IR3Pin);
  cdisplay();
  
  
}

void go(int s, int d)
{
   
   if(s>d)
   {
        if(d==0){ 
                        
            while(t==0){          
            
            read();
            if(SensorValueG==LOW)
                {
                
                rotateMotor(0, 0);
                t=1;
                
              }
            if(SensorValueG==HIGH)
                
             {
                
                rotateMotor(-MOTOR_SPEED, 0);
                
                t=0;
             }                      

            }
                    
          }
        else if(d==1){          
          
          while(t==0){              
            
            read();
            if(SensorValue1==LOW)
            {
              
              rotateMotor(0, 0);
              t=1;
             
            }
           if(SensorValue1==HIGH)
            {
              
              rotateMotor(-MOTOR_SPEED, 0);
             
              t=0;
            }
            
            }
          
         }
        else if(d==2){          
                     
            while(t==0){            
            
            read();
            if(SensorValue2==LOW)
            {
              
              rotateMotor(0, 0);
              t=1;
              
            }
            if(SensorValue2==HIGH)
            {
              
              rotateMotor(-MOTOR_SPEED, 0);
              
              t=0;

            } 
            
            }
          
        }         
        
        
   }
   if(s<d)
   {
       if(d==1){
            
                      
            while(t==0){
            read();
            if(SensorValue1==LOW)
            {
              
              rotateMotor(0, 0);
              t=1;
             
            }
            if(SensorValue1==HIGH)
            {
             
             
              rotateMotor(MOTOR_SPEED, 0);
              
              t=0;
              }
            
            }
       }    
       else if(d==2){                              
                     
            while(t==0){         
            
            read(); 
           
            if(SensorValue2==HIGH)
            {
             
            rotateMotor(MOTOR_SPEED, 0);
           
            t=0;
            }
            if(SensorValue2==LOW)
            {
             
              rotateMotor(0, 0);
              t=1;
              
            }
           
            }
            
       }   
        else if(d==3){
          
             
            while(t==0){            
           
            read(); 
            if(SensorValue3==LOW)
            {
              
             
              t=1;
              
            }
            if(SensorValue3==HIGH)
            {
             
               rotateMotor(MOTOR_SPEED, 0);
              
              t=0;
            }


            
            }
          
        }
          
   }
   
   t=0;
}

void going(int s, int d)
{
    if(d==0)
    {
        if(s<d)
        {
          read();      
         
            do{
              rotateMotor(MOTOR_SPEED, 0);
              read();
            }while(SensorValueG==HIGH);
            if(SensorValueG==LOW)
            {
             rotateMotor(0, 0);
              
            }
         

        }
        if(s>d)
        {
          read();
          
          
            do{
              rotateMotor(-MOTOR_SPEED, 0);
              read();
            }while(SensorValueG==HIGH);
            if(SensorValueG==LOW)
            {
             rotateMotor(0, 0);
              
            }
          
        }
    }
    else if(d==1)
    {
         if(s<d)
        {
          read();
          
         
            do{
              rotateMotor(MOTOR_SPEED, 0);
              read();
            }while(SensorValue1==HIGH);
            if(SensorValue1==LOW)
            {
             rotateMotor(0, 0);
              
            }
          

        }
        if(s>d)
        {
          read();
          
          
            do{
              rotateMotor(-MOTOR_SPEED, 0);
              read();
            }while(SensorValue1==HIGH);
            if(SensorValue1==LOW)
            {
             rotateMotor(0, 0);
              
            }
          
        }
    }
    else if(d==2)
    {
         if(s<d)
        {
          read();
          
         
            do{
              rotateMotor(MOTOR_SPEED, 0);
              read();
            }while(SensorValue2==HIGH);
            if(SensorValue2==LOW)
            {
             rotateMotor(0, 0);
              
            }
          

        }
        if(s>d)
        {
          read();
          
          
            do{
              rotateMotor(-MOTOR_SPEED, 0);
              read();
            }while(SensorValue2==HIGH);
            if(SensorValue2==LOW)
            {
             rotateMotor(0, 0);
              
            }
          
        }
    }
    else if(d==3)
    {
         if(s<d)
        {
          read();
          
         
            do{
              rotateMotor(MOTOR_SPEED, 0);
              read();
            }while(SensorValue3==HIGH);
            if(SensorValue3==LOW)
            {
             rotateMotor(0, 0);
              
            }
          

        }
        if(s>d)
        {
          read();
          
          
            do{
              rotateMotor(-MOTOR_SPEED, 0);
              read();
            }while(SensorValue3==HIGH);
            if(SensorValue3==LOW)
            {
             rotateMotor(0, 0);
              
            }
          
        }
    }


}

