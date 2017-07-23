#include <UnoWiFiDevEd.h>
#define CONNECTOR "rest"
#define SERVER_ADDR "158.108.165.223"

String readAddr = "/data/AssassinZEED/";
CiaoData data;
void setup() {
  Serial.begin(9600);
  Ciao.begin();
}
bool sentData(String _name, String value) {
  int x=1;
  while(true) {
    data = Ciao.read(CONNECTOR, SERVER_ADDR, readAddr+_name+"/set/"+value);
    Serial.println(data.get(2));
    if (!data.isEmpty()){
      return true;
    } else {
      delay(2000);
    }
    if (x>5) {
      return false;
    }
    x++;
  } 
}
String getData(String _name) {
  int x=1;
  String result;
  while(true) {
    data = Ciao.read(CONNECTOR, SERVER_ADDR, readAddr+_name);
    result = data.get(2);
    if (!data.isEmpty()){
      return result;
    } else {
      delay(2000);
    }
    if (x>5) {
      return "";
    }
    x++;
  } 
}

void loop() {
  Serial.println("start");
  Serial.println(sentData("test","value"));
  delay(2000);
  Serial.println(getData("test"));
  delay(2000);
}
