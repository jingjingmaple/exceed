#include <Servo.h>
Servo servo;
///////////////////////////////////
#include <UnoWiFiDevEd.h>
#include <Wire.h>
#define CONNECTOR "rest"
#define SERVER_ADDR "158.108.165.223"
char readAddr[] = "/data/AssassinZEED/toyison";
char readAddrMan[] = "/data/AssassinZEED/toyman";
String writeAddr = "/data/AssassinZEED/toyman/set/false";
//char str[30];
CiaoData data;
////////////////////////////////////////////////////
#include <pt.h>
#define PT_DELAY(pt, ms, ts)\
  ts = millis();\
  PT_WAIT_WHILE(pt, millis()-ts < (ms));
struct pt pt_toy;
////////////////////////////////////////////////////
#define TRIG_PIN 3 
#define ECHO_PIN 4
int duration,distance,count1,count2,i;
String manOrder,order ;
/////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  PT_INIT(&pt_toy);
  //////////////////////////////////////////
  Ciao.begin();
  ////////////////////////////////////////////
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
  ////////////////////////////////////////////
  servo.attach(6);

///////////////////////
}

void loop() {
  toy(&pt_toy);
  // put your main code here, to run repeatedly:

}
PT_THREAD(toy(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  int z;
  while(1){
    z=0;
    /*digitalWrite(TRIG_PIN1, LOW);
    PT_DELAY(pt, 500, ts);
    digitalWrite(TRIG_PIN1, HIGH);
    PT_DELAY(pt, 500, ts);
    digitalWrite(TRIG_PIN1, LOW);
    duration = pulseIn(ECHO_PIN1,HIGH);
    distanceMeter = duration / 29.1 / 2 ;
    */
    distance=Ultra();
    data = Ciao.read(CONNECTOR, SERVER_ADDR, readAddr);
    order = String(data.get(2));
   Serial.println(order);//-------------
    if(order=="false"){//ไม่ได้auto
     /*if(distanceMeter<=20&&distanceMeter>=0){
      for(int i =0;i>=0;i++){
        servo.write(140);
        PT_DELAY(pt, 1000, ts);
         servo.write(30);
        //servo work จนกว่าจะไป // function เปิดปิด ultr
        Ultra(distance); 
        if(distance>20)
          break;
      }
     }
     */    
     data = Ciao.read(CONNECTOR, SERVER_ADDR, readAddrMan);/////////////////////
     Serial.println(data.get(2));//-------------
     manOrder = String(data.get(2));
   
     if(manOrder=="true"){
       i=0;
       for( ;i<=3;i++){
        servo.write(250);
        PT_DELAY(pt,1000, ts);
         servo.write(10);
         PT_DELAY(pt,1000, ts);
         Serial.println("1round");
       }
       data = Ciao.read(CONNECTOR, SERVER_ADDR, writeAddr);
     }
    
     }
     
    
     /////////////////////////////////////////////////////////////////
     
     else if(order=="true"){//auto
      { Serial.println(distance);
        if(distance<=10&&distance>=0){
         
      do{
       // i=0;
        //for(;i>=3;i++){
        servo.write(250);
        PT_DELAY(pt, 1000, ts);
         servo.write(10);
         PT_DELAY(pt, 1000, ts);
        //}
        //servo work จนกว่าจะไป // function เปิดปิด ultr
        distance=Ultra(); 
        Serial.println(distance);
      }while(distance<=10);
     }
        }
     }
  }
  PT_END(pt);
}
int Ultra(){
    digitalWrite(TRIG_PIN, LOW);
    delay(500);
    digitalWrite(TRIG_PIN, HIGH);
    delay(500);
    digitalWrite(TRIG_PIN, LOW);
    duration = pulseIn(ECHO_PIN,HIGH);
    int distanceCm = duration / 29.1 / 2 ;
    return distanceCm;
  }
