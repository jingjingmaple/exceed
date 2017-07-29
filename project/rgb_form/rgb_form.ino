/*#include <UnoWiFiDevEd.h>
#include <pt.h>
#define PT_DELAY(pt, ms, ts)\
  ts = millis();\
  PT_WAIT_WHILE(pt, millis()-ts < (ms));
#define CONNECTOR "rest"
#define SERVER_ADDR "158.108.165.223"
//char readAddr[] = "/data/AssassinZEED/";
CiaoData data;*/

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

void setup(){  
  Serial.begin(9600);
//  Ciao.begin();
  pinMode(s0, OUTPUT);  
  pinMode(s1, OUTPUT);  
  pinMode(s2, OUTPUT);  
  pinMode(s3, OUTPUT);  
  pinMode(out, INPUT);   
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, LOW);
  error = 0;
} 
 
void loop(){
  scanColor();
  catHead = checkColor();
//  Serial.print("Try......Cat's color: ");
//  Serial.println(catHead);
  delay(800);
  while (error < 9 && (catHead == "white" || catHead == "black" || catHead == "gray" || catHead == "orange")){
    scanColor();
    catSuit = checkColor();
//    Serial.print("Try......Cat's suit: ");
//    Serial.println(catSuit);
    delay(800);
    while (error < 9 && (catSuit == "red" || catSuit == "green" || catSuit == "blue")){
      scanColor();
      catTail = checkColor();
//      Serial.print("Try......Cat's tail: ");
//      Serial.println(catTail);
      delay(800);
      while (error < 9 && catHead == catTail){
        Serial.print(">>>>>>>>True Cat!!!");
        Serial.print("\tCat's color: ");
        Serial.print(catTail);
        Serial.print("\tCat's suit: ");
        Serial.println(catSuit);
        error = 9;
        delay(800);
      }
      error++;
      delay(800);
    }
    error++;
    delay(800);
  }
  delay(800);
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

/*bool sentData(String _name, String value) {
  int x=1;
  while(true) {
    data = Ciao.write(CONNECTOR, SERVER_ADDR, readAddr+_name+"/set/"+value);
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
}*/
