#include <UnoWiFiDevEd.h>
#include <Wire.h>
#define CONNECTOR "rest"
#define SERVER_ADDR "158.108.165.223"
char readAddr[] = "/data/AssassinZEED/a";
String writeAddr = "/data/AssassinZEED/a/set/hahaha";
//char str[30];
CiaoData data;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Ciao.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  //data = Ciao.read(CONNECTOR, SERVER_ADDR, readAddr);
  data = Ciao.write(CONNECTOR, SERVER_ADDR, writeAddr);
  if (data.isEmpty()) {
    Serial.println(F("Failed"));
   
  } else {
    Serial.println(String(data.get(2)));
    
  }
  delay(1000);
}
