// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "Lift 01 "
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 87 bytes
  { 255,3,0,65,0,80,0,16,96,1,3,5,11,38,7,30,2,26,67,5,
  0,30,64,5,2,26,61,71,56,17,6,30,30,1,32,1,75,0,0,0,
  0,0,0,128,64,0,0,128,63,0,0,64,64,0,0,160,64,24,0,135,
  0,0,0,0,0,0,128,64,3,5,46,38,7,30,2,26,1,0,22,71,
  19,19,2,31,71,111,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t select_2; // =0 if select position A, =1 if position B, =2 if position C, ... 
  uint8_t select_1; // =0 if select position A, =1 if position B, =2 if position C, ... 
  uint8_t button_1; // =1 if button pressed, else =0 

    // output variables
  char text_1[61];  // string UTF8 end zero 
  float instrument_1;  // from 0 to 4 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

int start=1;
int current=1;
int current_i=1;
int des_i =1;
int t=1;
char str[] = "select current & destination floors";

void setup() 
{
  RemoteXY_Init (); 
  
  
  for(int i =7;i<=11;i++)
   {
   pinMode(i,OUTPUT);
   }
   floor(start);
   strcpy  (RemoteXY.text_1, str);//set text
  
}



void loop() 
{ 
  RemoteXY_Handler ();
  
 
  char str1[] ="Get on to lift";
  char str2[] ="You reached your destination";
  char str3[] ="You are at destination floor";
  
  
  current_i=RemoteXY.select_2;
  des_i =RemoteXY.select_1;

  if(RemoteXY.button_1==1 && current_i==des_i)
    {
      strcpy (RemoteXY.text_1, str3); 
      t=1;
    }
  else if(RemoteXY.button_1==1 && t==1)
  {
    
    run(5-current_i);
    start=5-current_i;
    strcpy (RemoteXY.text_1, str1);        
    t=t+1;   
    
  }
  else if(RemoteXY.button_1==1 && t==2)
    {
      
      run(5-des_i);
      start=5-des_i;      
      strcpy (RemoteXY.text_1, str2);
      t=1;
      
    }  


}

void floor(int y)
{
  switch(y) {
  case 1:
    digitalWrite(7,HIGH);
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    current=1;
    RemoteXY.instrument_1=0;
    
    break;
  case 2:
    digitalWrite(7,LOW);
    digitalWrite(8,HIGH);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    current=2;
    RemoteXY.instrument_1=1;
    
    break;
   case 3:
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
    digitalWrite(9,HIGH);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    current=3;
    RemoteXY.instrument_1=2;
    
    break;
   case 4:
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    digitalWrite(10,HIGH);
    digitalWrite(11,LOW);
    current=4; 
    RemoteXY.instrument_1=3;
      
    break;
   case 5:
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,HIGH);
    current=5;
    RemoteXY.instrument_1=4;
    
    break;
  
}
}

void run(int x)
{

  if(start>x)
  {
    for(int i=start;i>=x;i--)
    {
      floor(i);
      RemoteXY_delay(1000);
      
      
    }
  }
  else if(start<x)
  {
    for(int i=start;i<=x;i++)
    {
      floor(i);
      RemoteXY_delay(1000);
      
    }
    
  }
  
  
}
