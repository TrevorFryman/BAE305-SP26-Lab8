
#include <PID_v2.h> // Include added library to code

// Declare variables, allows for manual input as the robot is running 
double setpoint = 15.0;
double Kp = 7;
double Ki = 3;
double Kd = 2;
double measurement = 0.0;
double output = 0.0;
/********************************************************************/

//the right motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 13;           //control pin 1 on the motor driver for the right motor
const int AIN2 = 12;            //control pin 2 on the motor driver for the right motor
const int PWMA = 11;            //speed control pin on the motor driver for the right motor
//the left motor will be controlled by the motor B pins on the motor driver
const int PWMB = 10;           //speed control pin on the motor driver for the left motor
const int BIN2 = 9;           //control pin 2 on the motor driver for the left motor
const int BIN1 = 8;           //control pin 1 on the motor driver for the left motor

const int driveTime = 20;      //this is the number of milliseconds that it takes the robot to drive 1 inch
const int turnTime = 8;        //this is the number of milliseconds that it takes to turn the robot 1 degree

String botDirection;           //the direction that the robot will drive in (this change which direction the two motors spin in)
String speed;               //the speed to travel in each directionconst int speedlow = 30;

const int trigPin = 6; // Pin that the trig is connected to.
const int echoPin = 7; // Pin that the echo is connected to.
float duration, D; // Duration: Length of soundwave, D: How far object is.
// float creates inputs for later on.

/********************************************************************************/

// Create the PID instance
PID myPID(&measurement, &output, &setpoint, Kp, Ki, Kd, REVERSE);

void setup()
{
  // Intialize the PID
  myPID.SetTunings(Kp, Ki, Kd); 
  myPID.SetMode(AUTOMATIC);

  //set the motor control pins as outputs
  pinMode(AIN1, OUTPUT); //set right motor output to pin 13 on arduino 
  pinMode(AIN2, OUTPUT); //set right motor output to pin 12 on arduino 
  pinMode(PWMA, OUTPUT); //set right motor speed output to pin 11 on arduino 

  pinMode(BIN1, OUTPUT); //set left motor output to pin 10 on arduino 
  pinMode(BIN2, OUTPUT); //set left motor output to pin 9 on arduino 
  pinMode(PWMB, OUTPUT); //set left motor speed output to pin 8 on arduino 

  pinMode(trigPin, OUTPUT); //set ultrasonic sensor trig output to pin 6
  pinMode(echoPin, INPUT); //set ultrasonic sensor echo input to pin 7

  Serial.begin(9600);   //begin serial communication with the computer

 
  
}

/********************************************************************************/
void loop()
{
  int x; //establish "x" as an integer
// tells when the ultrasonic sensor should calculate the distance for use in the PID
  digitalWrite(trigPin, LOW); //pin 6 voltage off
  delayMicroseconds(2); //wait 2 microseconds
  digitalWrite(trigPin, HIGH); //pin 6 voltage on
  delayMicroseconds(10); //wait 10 microseconds
  digitalWrite(trigPin, HIGH); //pin 6 voltage on
  duration = pulseIn(echoPin, HIGH); //establish variable "duration" from pin 7 received data
  D = (duration*.0343)/2; //calculate the distance in centimeters from input of pin 7
  delay(100); //wait 5 seconds 
  // Serial.println(D); //used to see if distance is printed correctly
  
  // Run PID after obtaining the distance
  myPID.Compute();
  // Print out variables established, this will allow you to see how long it takes the PID
  measurement = D;                    // to stabalize inturn giving you information on what
  Serial.print(setpoint);             // variables you need to adjust.
  Serial.print(", ");
  Serial.print(measurement);
  Serial.print(", ");
  Serial.print(output);
  Serial.print(", ");
  Serial.print(Kp);
  Serial.print(", ");
  Serial.print(Ki);
  Serial.print(", ");
  Serial.print(Kd);
  Serial.print(", ");
  
  x = (map(output, 0, 255, -255, 255)); // change the PID min and max values to the motors min and max values
  Serial.println(x);                    // This will in turn change the speed at which the robot moves


    rightMotor(x);
    leftMotor(x);
 
}
/********************************************************************************/
void rightMotor(int motorSpeed)  //function for driving the right motor
{
  if (motorSpeed > 0)           //if the motor should drive forward (positive speed)
  {
    digitalWrite(AIN1, HIGH);   //set pin 13 voltage to on
    digitalWrite(AIN2, LOW);    //set pin 12 voltage to off
  }
  else if (motorSpeed < 0)     //if the motor should drive backward (negative speed)
  {
    digitalWrite(AIN1, LOW);    //set pin 13 voltage to off
    digitalWrite(AIN2, HIGH);   //set pin 12 voltage to on
  }
  else                       //if the motor should stop
  {
    digitalWrite(AIN1, LOW);  //set pin 13 voltage to off
    digitalWrite(AIN2, LOW);  //set pin 12 voltage to off
  }
  analogWrite(PWMA, abs(motorSpeed)); //now that the motor direction is set, drive it at the entered speed
}

/********************************************************************************/
void leftMotor(int motorSpeed) //function for driving the left motor
{
  if (motorSpeed > 0)        //if the motor should drive forward (positive speed)
  {
    digitalWrite(BIN1, HIGH); //set pin 8 voltage to on
    digitalWrite(BIN2, LOW);  //set pin 9 voltage to off
  }
  else if (motorSpeed < 0)   //if the motor should drive backward (negative speed)
  {
    digitalWrite(BIN1, LOW);  //set pin 8 voltage to off
    digitalWrite(BIN2, HIGH); //set pin 9 voltage to on
  }
  else                         //if the motor should stop
  {
    digitalWrite(BIN1, LOW);  //set pin 8 voltage to off
    digitalWrite(BIN2, LOW);  //set pin 9 voltage to off
  }
  analogWrite(PWMB, abs(motorSpeed));  //now that the motor direction is set, drive it at the entered speed
}
