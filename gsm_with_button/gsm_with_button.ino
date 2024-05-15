#include <SoftwareSerial.h>

SoftwareSerial SIM900A(11,12);

const int BUTTON_PIN = 4;
bool state =1;
int buttonState = 0;

void setup() {
  // put your setup code here, to run once:
 pinMode(BUTTON_PIN, INPUT_PULLUP);

  SIM900A.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  
  Serial.println("Initializing..."); 
  delay(1000);

  SIM900A.println("AT"); //Once the handshake test is successful, i t will back to OK
  updateSerial();
 
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);

  
  if(buttonState == LOW ){         // If button is pressing
    Serial.println(state);
    SendMessage();
    state =1;
  }
  else if(buttonState == HIGH ) {                         // otherwise, button is not pressing
    Serial.println(state);
    state =0;
  }
 
   
  // control LED according to the state of button
  
  

}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    SIM900A.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(SIM900A.available()) 
  {
    Serial.write(SIM900A.read());//Forward what Software Serial received to Serial Port
  }
}

void call()
 {
   
  
 SIM900A.println("ATD+94704209730;"); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
  updateSerial();
  delay(20000); // wait for 20 seconds...
  SIM900A.println("ATH"); //hang up
  updateSerial();
 }

 void SendMessage()
{
  Serial.println ("Sending Message");
  SIM900A.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println ("Set SMS Number");
  SIM900A.println("AT+CMGS=\"+94704209730\"\r"); //Mobile phone number to send message
  delay(1000);
  Serial.println ("Set SMS Content");
  SIM900A.println("Emergency!!!!!!!!");// Messsage content
  delay(100);
  Serial.println ("Finish");
  SIM900A.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println ("Message has been sent ->SMS Selesai dikirim");
}
