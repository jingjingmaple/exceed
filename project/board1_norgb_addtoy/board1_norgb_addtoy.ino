#include  <Servo.h>
Servo myservo; 
#include <UnoWiFiDevEd.h>
#include <pt.h>
#include <dht.h>
#define PT_DELAY(pt, ms, ts)\
  ts = millis();\
  PT_WAIT_WHILE(pt, millis()-ts < (ms));
// PROTO THREAD  
struct pt pt_feedFood;
struct pt pt_detectFood;
struct pt pt_sentTemp;
struct pt pt_lightControl;
struct pt pt_airControl;


char readAddr[] = "/data/AssassinZEED/toyison";
char readAddrMan[] = "/data/AssassinZEED/toyman";
String writeAddr = "/data/AssassinZEED/toyman/set/false";


#define CONNECTOR "rest"
#define SERVER_ADDR "158.108.165.223"
#define LDR 2
#define LED_AIR 4
#define LED 7
#define DHT11 8
#define NODE 13
dht DHT;
int dhtTemp;
int resultLux;
String temperature;
String humidity;
char readAddrp[] = "/data/AssassinZEED/";
CiaoData data;
void setup() {
  Serial.begin(9600);
  Ciao.begin();
  myservo.attach(3);
  //myservo.write(0);
  pinMode(NODE,INPUT);
  
  PT_INIT(&pt_feedFood);
  PT_INIT(&pt_detectFood);
  PT_INIT(&pt_sentTemp);
  PT_INIT(&pt_airControl);
  PT_INIT(&pt_lightControl);

  pinMode(LDR,INPUT);
  pinMode(LED,OUTPUT);
  pinMode(LED_AIR,OUTPUT);

}
bool sentData(String _name, String value) {
  int x=1;
  while(true) {
    data = Ciao.read(CONNECTOR, SERVER_ADDR, readAddrp+_name+"/set/"+value);
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
    data = Ciao.read(CONNECTOR, SERVER_ADDR, readAddrp+_name);
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

bool getFoodLeft() {
  if (digitalRead(LDR) == 0) {
    return false;
  } else {
    return true;
  }
}

void loop() {
  feedFood(&pt_feedFood);
  detectFood(&pt_detectFood);
  sentTemp(&pt_sentTemp);
  lightControl(&pt_lightControl);
  airControl(&pt_airControl);
}

PT_THREAD(feedFood(struct pt* pt)) {
  static uint32_t ts;
  PT_BEGIN(pt);
  
  while(1) {
    if (getData("feed") == "true") {
      if (getFoodLeft() != true) {
        Serial.println("feed");
        myservo.write(130);
        PT_DELAY(pt, 1000, ts);
        myservo.write(30);
        sentData("feed","false");
      }
    }

    PT_DELAY(pt, 3000, ts);
  }
  PT_END(pt);
}

PT_THREAD(detectFood(struct pt* pt)) {
  static uint32_t ts;
  PT_BEGIN(pt);
  
  while(1) {
    if (getFoodLeft()) {
      sentData("foodleft","true");
    } else {
      sentData("foodleft","false");
    }
    PT_DELAY(pt, 3000, ts);
  }
  PT_END(pt);
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

     if (getData("aircon") == "true") {
      digitalWrite(LED_AIR,HIGH);
     } else {
      digitalWrite(LED_AIR,LOW);
     }
    
    PT_DELAY(pt, 2000, ts);
  }
  PT_END(pt);
}

PT_THREAD(lightControl(struct pt* pt)) {
  static uint32_t ts;
  PT_BEGIN(pt);
  while(1) {
    //Serial.println(digitalRead(NODE));
    /*if (getData("autoison") == "true") {
      Serial.println(resultLux);
      if (resultLux <400) {
        digitalWrite(LED2,HIGH);       
      } else {
        digitalWrite(LED2,LOW);
      }
    } else {*/
       if (getData("outlight") == "true") {
        digitalWrite(LED,HIGH);
        Serial.println("Holy shit");
       } else {
        digitalWrite(LED,LOW);
       }
    //}
    PT_DELAY(pt, 2000, ts);
  }
  PT_END(pt);
}
/*PT_THREAD(toy(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while(1){
    Serial.println(digitalRead(NODE));
    
    if (getData("toyison") == "false") {
      if (getData("toyman") == "true") {
        myservo2.write(140);
          PT_DELAY(pt, 2000, ts);
         myservo2.write(30);
          PT_DELAY(pt, 2000, ts);
      }
    } else {
      if (digitalRead(NODE) == 1) {
         myservo2.write(140);
          PT_DELAY(pt, 2000, ts);
         myservo2.write(30);
          PT_DELAY(pt, 2000, ts);
      }
    }
    PT_DELAY(pt, 1000, ts);  
  }
  PT_END(pt);
}*/

