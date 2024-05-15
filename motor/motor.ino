
#define MOTOR_SPEED 220

const int BUTTON_PIN1 = 11;
const int BUTTON_PIN2 = 4;
const int BUTTON_PIN3 = 3;
const int BUTTON_PIN4 = 13;

int mospeed = 75;
int t = 0;

//Right motor
int enableRightMotor = 6;
int rightMotorPin1 = 7;
int rightMotorPin2 = 8;

//Left motor
int enableLeftMotor = 5;
int leftMotorPin1 = 9;
int leftMotorPin2 = 10;

long duration;
int distance;

void setup() {
  //The problem with TT gear motors is that, at very low pwm value it does not even rotate.
  //If we increase the PWM value then it rotates faster and our robot is not controlled in that speed and goes out of line.
  //For that we need to increase the frequency of analogWrite.
  //Below line is important to change the frequency of PWM signal on pin D5 and D6
  //Because of this, motor runs in controlled manner (lower speed) at high PWM value.
  //This sets frequecny as 7812.5 hz.
  TCCR0B = TCCR0B & B11111000 | B00000010;

  // put your setup code here, to run once:
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);


  rotateMotor(0, 0);

  pinMode(BUTTON_PIN1, INPUT);
  pinMode(BUTTON_PIN2, INPUT);
  pinMode(BUTTON_PIN3, INPUT);
  pinMode(BUTTON_PIN4, INPUT);


  Serial.begin(9600);                  // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("motor controller");  // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}


void loop() {
  rotateMotor(MOTOR_SPEED, MOTOR_SPEED);  // go straight
                                          //rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);// turn right
                                          //rotateMotor(MOTOR_SPEED, -MOTOR_SPEED); //turn left
                                          //rotateMotor(-MOTOR_SPEED, -MOTOR_SPEED); //reverse
  // rotateMotor(0, 0); //stop

  bool buttonState1 = digitalRead(BUTTON_PIN1);
  bool buttonState2 = digitalRead(BUTTON_PIN2);
  bool buttonState3 = digitalRead(BUTTON_PIN3);
  bool buttonState4 = digitalRead(BUTTON_PIN4);

  if (buttonState1 == HIGH) {
    Serial.println(" 1=1");
  } else if (buttonState2 == HIGH) {
    Serial.println(" 2=1");
  } else if (buttonState3 == HIGH) {
    Serial.println(" 3=1");
  } else if (buttonState4 == HIGH) {
    Serial.println(" 4=1");
  } else {
    Serial.println("none");
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
