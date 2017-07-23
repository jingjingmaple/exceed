#include  <Servo.h>
Servo myservo;         // create servo object to control a servo 
int val;  
int potpin = 3;        // Pin to potentiometer
void setup() 
{ 
  Serial.begin(9600);
  delay(400);
  myservo.attach(3);  // attaches the servo on pin 9 to the servo control pin (orange)
  delay(300);
} 
  
void loop() 
{ 
   for (int i=0; i<=140; i++) {
     //val = analogRead(potpin);         // define analog read pin
     //val = map(val, 0, 1023, 0, 140);  // scaling input to 0 - 180 degree
     val =i;
     Serial.println(val);
     myservo.write(val);               // position of servo arm
     delay(15);                        // adjust for selecting movement speed
   }
   delay(3000);
}
