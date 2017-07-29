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
struct pt pt_rgb;

#define CONNECTOR "rest"
#define SERVER_ADDR "158.108.165.223"
#define LDR 2
#define LED_AIR 4
#define LED 7
#define DHT11 8

//form
#define s0 A1
#define s1 A0
#define s2 A3
#define s3 A4
#define out A2
int redOG;
int greenOG;
int blueOG;
int error;
String color;
String catHead;
String catTail;
String catSuit;
//end form



dht DHT;
int dhtTemp;
int resultLux;
String temperature;
String humidity;
char readAddr[] = "/data/AssassinZEED/";
CiaoData data;
void setup() {
  Serial.begin(9600);
  Ciao.begin();
  myservo.attach(3);
  PT_INIT(&pt_feedFood);
  PT_INIT(&pt_detectFood);
  PT_INIT(&pt_sentTemp);
  PT_INIT(&pt_airControl);
  PT_INIT(&pt_lightControl);
  PT_INIT(&pt_rgb);
  pinMode(LDR,INPUT);
  pinMode(LED,OUTPUT);
  pinMode(LED_AIR,OUTPUT);

  //form
  pinMode(s0, OUTPUT);  
  pinMode(s1, OUTPUT);  
  pinMode(s2, OUTPUT);  
  pinMode(s3, OUTPUT);  
  pinMode(out, INPUT);   
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, LOW);
  //end form
  

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

bool getFoodLeft() {
  if (digitalRead(LDR) == 0) {
    return false;
  } else {
    return true;
  }
}

void scanColor(){    
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);  
  redOG = 255 - pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s3, HIGH);  
  blueOG = 255 - pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s2, HIGH);  
  greenOG = 255 - pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  if (redOG < 0)
    redOG = 0;
  if (greenOG < 0)
    greenOG = 0;
  if (blueOG < 0)
    blueOG = 0;
//  Serial.print("R: ");  
//  Serial.print(redOG);  
//  Serial.print(" G: ");  
//  Serial.print(greenOG);
//  Serial.print(" B: ");  
//  Serial.println(blueOG);
}

String checkColor(){
  if (redOG <= 30 && greenOG <= 30 && blueOG <= 30)
    return "black";
  else if (redOG >= 210 && greenOG >= 210 && blueOG >= 210)
    return "white";
/*  else {
    int Max = max(max(redOG,greenOG),blueOG);
    int Min = min(min(redOG,greenOG),blueOG);
    int Middle = min(max(redOG,greenOG),blueOG);
    if (Max-Min <= 50 && Middle <= Max-25 && Middle >= Min+25)
      return "gray";
    else {
      float redH = redOG/255;
      float greenH = greenOG/255;
      float blueH = blueOG/255;
      int rawHue;
      if (Max = redOG)
        rawHue = ((greenH - blueH)/(Max - Min))/6;
      else if (Max = greenOG)
        rawHue = ((blueH - redH)/(Max - Min))+2;
      else if (Max = blueOG)
        rawHue = ((redH - greenH)/(Max - Min))+4;
      int colorHue = 60*rawHue;
      if ((blueOG > redOG && blueOG > greenOG) && (colorHue <= 240 && colorHue >= 221))
        return "blue";
      else if ((redOG > blueOG && redOG > greenOG) && ((colorHue <= 10 && colorHue >= 0)||(colorHue <= 359 && colorHue >= 355)))
        return "red";
      else if ((greenOG > blueOG && greenOG > blueOG) && (colorHue <= 140 && colorHue >= 81))
        return "green";
      else if (colorHue <= 40 && colorHue >= 11)
        return "orange";
      else
        return "other";
    }
  }*/
  else if (redOG > blueOG && redOG > greenOG && redOG < 210)
    return "red";
  else if (greenOG > blueOG && greenOG > redOG && greenOG < 210)
    return "green";
  else if (blueOG > greenOG && blueOG > redOG && blueOG < 210)
    return "blue";
  else
    return "other";
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
    /*if (getData("autoison") == "true") {
      Serial.println(resultLux);
      if (resultLux <400) {
        digitalWrite(LED2,HIGH);       
      } else {
        digitalWrite(LED2,LOW);
      }
    } else {*/
       if (getData("light") == "true") {
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

PT_THREAD(rgb(struct pt* pt)) {
  static uint32_t ts;
  PT_BEGIN(pt);
  while(1) {
          scanColor();
        catHead = checkColor();
      //  Serial.print("Try......Cat's color: ");
      //  Serial.println(catHead);
        PT_DELAY(pt, 800, ts);
        while (error < 9 && (catHead == "white" || catHead == "black" || catHead == "gray" || catHead == "orange")){
          scanColor();
          catSuit = checkColor();
      //    Serial.print("Try......Cat's suit: ");
      //    Serial.println(catSuit);
          PT_DELAY(pt, 800, ts);
          while (error < 9 && (catSuit == "red" || catSuit == "green" || catSuit == "blue")){
            scanColor();
            catTail = checkColor();
      //      Serial.print("Try......Cat's tail: ");
      //      Serial.println(catTail);
            PT_DELAY(pt, 800, ts);
            while (error < 9 && catHead == catTail){
              Serial.print(">>>>>>>>True Cat!!!");
              Serial.print("\tCat's color: ");
              Serial.print(catTail);
              Serial.print("\tCat's suit: ");
              Serial.println(catSuit);
              error = 9;
              PT_DELAY(pt, 800, ts);
            }
            error++;
            PT_DELAY(pt, 800, ts);
          }
          error++;
          PT_DELAY(pt, 800, ts);
        }
        PT_DELAY(pt, 800, ts);



  }
  PT_END(pt);
}
