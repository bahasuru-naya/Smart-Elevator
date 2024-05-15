#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "Elevator prototype"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 61 bytes
  { 255,2,0,0,0,54,0,16,55,1,1,0,23,44,17,17,2,31,85,112,
  0,1,0,24,69,17,17,2,31,68,111,119,110,0,129,0,8,25,49,5,
  37,87,101,108,99,111,109,101,32,116,111,32,69,108,101,118,97,116,111,114,
  0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t button_1; // =1 if button pressed, else =0 
  uint8_t button_2; // =1 if button pressed, else =0 

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

const int LED_PIN =  13; 
const int SensorPin =  A0;  


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


  rotateMotor(0, 0);  
  
  pinMode(LED_PIN, OUTPUT);
 
   pinMode(SensorPin, INPUT);

}

void loop() 
{ 
  RemoteXY_Handler ();
  int SensorValue = digitalRead(SensorPin);
  

   if (SensorValue==LOW){ // LOW MEANS Object Detected
    digitalWrite(LED_PIN, HIGH);
    rotateMotor(0, 0);
  }
  else if(SensorValue==HIGH){

    
    digitalWrite(LED_PIN, LOW);

     if(RemoteXY.button_1==1 )
  {
    rotateMotor(MOTOR_SPEED, 0);
    
  }
  else if(RemoteXY.button_2==1)
  {    
   rotateMotor(-MOTOR_SPEED, 0);
     
  } 
   else
  {
    rotateMotor(0, 0);
  }

  }
  
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