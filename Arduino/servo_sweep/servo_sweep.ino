// Sweep
// by BARRAGAN <http://barraganstudio.com>
// This example code is in the public domain.

#include <Servo.h>

#define SERVO_PIN 12
#define SERVO_DELAY 40
#define SERVO_STEP 5

Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created
 
int pos = 0;    // variable to store the servo position
boolean dir = 0; // direction of servo travel
 
void setup()
{
  Serial.begin(9600);
  myservo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
}
 
 
void loop()
{
  pos += (!dir)? SERVO_STEP : -SERVO_STEP;
  if (pos % 180 == 0)
    dir = !dir;
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
  Serial.print("Dir: ");
  Serial.print(dir);
  Serial.print(" Pos: ");
  Serial.println(pos);
  delay(SERVO_DELAY);                       // waits 15ms for the servo to reach the position
}
