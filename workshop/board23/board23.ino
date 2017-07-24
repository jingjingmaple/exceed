#include <UnoWiFiDevEd.h>
#include <pt.h>

#define PT_DELAY(pt, ms, ts)\
  ts = millis();\
  PT_WAIT_WHILE(pt, millis()-ts < (ms));
struct pt pt_sentTemp;
struct pt pt_airControl;
struct pt pt_lightControl;
struct pt pt_lightValue;
#define CONNECTOR "rest"
#define SERVER_ADDR "158.108.165.223"

#include <dht.h>
#define DHT11 8
#define LED1 2 //air con
#define LED2 3 //out light
dht DHT;
int dhtTemp;
int resultLux;
String temperature;
String humidity;
String value2;
String readAddr = "/data/AssassinZEED/";
CiaoData data;
void setup() {
  Serial.begin(9600);
  Ciao.begin();
  PT_INIT(&pt_sentTemp);
  PT_INIT(&pt_airControl);
  PT_INIT(&pt_lightControl);

  pinMode(LED1,OUTPUT); //air con
  pinMode(LED2,OUTPUT); //out light
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
  sentTemp(&pt_sentTemp);
  airControl(&pt_airControl);
  lightControl(&pt_lightControl);
  lightValue(&pt_lightValue);
}

PT_THREAD(sentTemp(struct pt* pt)) {
  static uint32_t ts;
  PT_BEGIN(pt);
  while(1) {
    Serial.println("sentTemp");
    dhtTemp = DHT.read11(DHT11);
    temperature = String(DHT.temperature);
    humidity = String(DHT.humidity);
    sentData("temp",temperature);
    sentData("humid",humidity);

    
    PT_DELAY(pt, 10000, ts);
  }
  PT_END(pt);
}

PT_THREAD(airControl(struct pt* pt)) {
  static uint32_t ts;
  PT_BEGIN(pt);
  while(1) {
     value2 = getData("aircon");
     if (value2 == "true") {
      digitalWrite(LED1,HIGH);
     } else if (value2 == "false") {
      digitalWrite(LED1,LOW);
     }
    
    PT_DELAY(pt, 2000, ts);
  }
  PT_END(pt);
}

PT_THREAD(lightControl(struct pt* pt)) {
  static uint32_t ts;
  PT_BEGIN(pt);
  while(1) {
    if (getData("autoison") == "true") {
      Serial.println(resultLux);
      if (resultLux <400) {
        digitalWrite(LED2,HIGH);       
      } else {
        digitalWrite(LED2,LOW);
      }
    } else {
       value2 = getData("outlight");
       if (value2 == "true") {
        digitalWrite(LED2,HIGH);
       } else if (value2 == "false") {
        digitalWrite(LED2,LOW);
       }
    }
    PT_DELAY(pt, 2000, ts);
  }
  PT_END(pt);
}

PT_THREAD(lightValue(struct pt* pt)) {
  static uint32_t ts;
  PT_BEGIN(pt);
  while(1) {
    resultLux = 1023 - analogRead(A0);
    //resultLux = map(resultLux, 300, 1023, 0, 100);
    sentData("light",String(resultLux));   
    PT_DELAY(pt, 2000, ts);
  }
  PT_END(pt);
}



/*PT_THREAD(task2(struct pt* pt)) {
  static uint32_t ts;
  PT_BEGIN(pt);
  while(1) {
    Serial.println("task2");
    PT_DELAY(pt, 2000, ts);
  }
  PT_END(pt);
}*/


