#include <UnoWiFiDevEd.h>
#include <Wire.h>
#include <Servo.h>
#define CONNECTOR "rest"
#define SERVER_ADDR "158.108.165.223"
char readAddr[] = "/data/AssassinZEED/doorlock";
//String writeAddrplus = "/data/AssassinZEED/countcat/set/plus";
//String writeAddrmin = "/data/AssassinZEED/countcat/set/minus";
//String writeAddr = "/data/AssassinZEED/countcat/set/";
Servo servo;
String order;
CiaoData data;

void setup() {
  Serial.begin(9600);
  Ciao.begin();
  servo.attach(3);
}

void loop() {
  data = Ciao.read(CONNECTOR, SERVER_ADDR, readAddr);
  order=String(data.get(2));
  if(order=="true"){
    servo.write(140);
    
    delay(2000);
  }
  else if(order=="false"){
    servo.write(30);
    delay(2000);
  }
}
  
  

