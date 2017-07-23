#include <UnoWiFiDevEd.h>
#include <dht.h>
#define DHT11 2
dht DHT;
#define CONNECTOR "rest"
#define SERVER_ADDR "158.108.165.223"
int dhtTemp;
String temperature;
String humidity;
//char readAddr[] = "/data/AssassinZEED/a";
String readAddr = "/data/AssassinZEED/";
//char str[30];
CiaoData data;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Ciao.begin();
}
void sentData(String _name, String value) {
  int x=1;
  while(true) {
    data = Ciao.read(CONNECTOR, SERVER_ADDR, readAddr+_name+"/set/"+value);
    Serial.println(data.get(2));
    if (!data.isEmpty()){
      return;
    } else {
      delay(10000);
    }
    if (x>5) {
      return;
    }
    x++;
  } 
}
void loop() {
  dhtTemp = DHT.read11(DHT11);
  temperature = String(DHT.temperature);
  humidity = String(DHT.humidity);
  sentData("temp",temperature);
  sentData("humid",humidity);
  Serial.println(">>>>");
  Serial.println(temperature);
  Serial.println(humidity);
  /*data = Ciao.read(CONNECTOR, SERVER_ADDR, readAddr+"temp/"+temperature);
  
  //data = Ciao.write(CONNECTOR, SERVER_ADDR, writeAddr);
  if (data.isEmpty()) {
    Serial.println(F("Failed"));
   
  } else {
    Serial.println(String(data.get(2)));
    
  }*/
  delay(10000);
}
