#include <UnoWiFiDevEd.h>
#include <Wire.h>
#include <Servo.h>
#define CONNECTOR2 "rest"
#define SERVER_ADDR2 "128.199.232.240"
char writeAddrplus2[] = "/cat/add";
char writeAddrmin2[] = "/cat/minus";
#define CONNECTOR "rest"
#define SERVER_ADDR "158.108.165.223"
char readAddr[] = "/data/AssassinZEED/doorlock";
char readAddr1[] = "/data/AssassinZEED/toyison";
char readAddrMan[] = "/data/AssassinZEED/toyman";
char writeAddr[] = "/data/AssassinZEED/toyman/set/false";
Servo servo,servo1;
CiaoData data;
#include <pt.h>
#define PT_DELAY(pt, ms, ts)\
  ts = millis();\
  PT_WAIT_WHILE(pt, millis()-ts < (ms));
struct pt pt_task2;
struct pt pt_lock;
struct pt pt_toy;
int lockcheck=0;
#define TRIG_PIN1 10 // outhome
#define ECHO_PIN1 11          //มี 2ตัว
#define TRIG_PIN2 12 // inhome
#define ECHO_PIN2 13
#define LOCK 5
#define TRIG_PIN 7 
#define ECHO_PIN 8
String manOrder,order1,order ;
int duration1, distanceMeter1,duration2, distanceMeter2,count1,count2,duration,distance,i;//////////////


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

void setup() {
  Serial.begin(9600);
  PT_INIT(&pt_task2);
  PT_INIT(&pt_lock);
  PT_INIT(&pt_toy);
  ////////////////////////////////////////////////////////////////////////
  Ciao.begin();
  ////////////////////////////////////////////////////////////////////////
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
  pinMode(TRIG_PIN1,OUTPUT);
  pinMode(ECHO_PIN1,INPUT);
  pinMode(TRIG_PIN2,OUTPUT);
  pinMode(ECHO_PIN2,INPUT);
  servo1.attach(9);
  servo.attach(LOCK);
}

void loop() {
  // put your main code here, to run repeatedly:
   toy(&pt_toy);
   task2(&pt_task2);
  lock(&pt_lock);

}

PT_THREAD(toy(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while(1){ 
    distance=Ultra();
    data = Ciao.read(CONNECTOR, SERVER_ADDR, readAddr);
    //order = String(data.get(2));
   Serial.println(order);//-------------
    if(String(data.get(2))=="false"){//ไม่ได้auto
     data = Ciao.read(CONNECTOR, SERVER_ADDR, readAddrMan);/////////////////////
     Serial.println(data.get(2));//-------------
    // manOrder = String(data.get(2));
   
     if(String(data.get(2))=="true"){
       i=0;
       for( ;i<=3;i++){
        servo.write(250);
        PT_DELAY(pt,500, ts);
         servo.write(10);
         PT_DELAY(pt,500, ts);
         Serial.println("1round");
       }
       data = Ciao.write(CONNECTOR, SERVER_ADDR, writeAddr);
     }   
     }
     else if(String(data.get(2))=="true"){//auto
      { Serial.println(distance);
        if(distance<=100&&distance>=0){
         
      do{
       // i=0;
        //for(;i>=3;i++){
        servo.write(250);
        PT_DELAY(pt, 500, ts);
         servo.write(10);
         PT_DELAY(pt, 500, ts);
        //}
        //servo work จนกว่าจะไป // function เปิดปิด ultr
        distance=Ultra(); 
        Serial.println(distance);
      }while(distance<=100);
     }
        }
     }
  }
  PT_END(pt);
}
PT_THREAD(task2(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while(1){
PT_DELAY(pt, 500, ts);
    digitalWrite(TRIG_PIN1, HIGH);
    PT_DELAY(pt, 500, ts);
    digitalWrite(TRIG_PIN1, LOW);
    duration1 = pulseIn(ECHO_PIN1,HIGH);
    distanceMeter1 = duration1 / 29.1 / 2 ;
digitalWrite(TRIG_PIN2, LOW);
  PT_DELAY(pt, 500, ts);
  digitalWrite(TRIG_PIN2, HIGH);
  PT_DELAY(pt, 500, ts);
  digitalWrite(TRIG_PIN2, LOW);
  duration2 = pulseIn(ECHO_PIN2,HIGH);
  distanceMeter2 = duration2 / 29.1 / 2;
 if(distanceMeter1<distanceMeter2){// outside
  if(distanceMeter1<0){
    Serial.print("1ERROR!");
    Serial.println(distanceMeter1);
    count1=0;
    count2=0; 
    }
  else if 
  (distanceMeter1 <= 3&count1!=1){// ต้องมั่นใจว่าเข้าใกล้จริงๆ
    //ส่งไปว่าminus
    Serial.print("fromout ");
    Serial.println(distanceMeter1);
    count1++;
    count2=0;
  }
    else if(distanceMeter1 <= 3&count1==1)
    {data = Ciao.write(CONNECTOR2, SERVER_ADDR2, writeAddrplus2);
    Serial.println("openplus");
    count1=0;
    count2=0; 
    PT_DELAY(pt, 500, ts);
    }
    }  
 else if(distanceMeter2<distanceMeter1){   //inside
    if(distanceMeter2=0){
    Serial.print("2ERROR!");
    Serial.println(distanceMeter2);
    count1=0;
    count2=0; 
    }
    else if(distanceMeter2 <= 3&count2!=1){
      count2++;
      count1=0;
      Serial.print("inside ");
      Serial.println(distanceMeter2);
    }
    else if(distanceMeter2 <= 3&count2==1){
    data = Ciao.write(CONNECTOR2, SERVER_ADDR2, writeAddrmin2);
    Serial.println("openminus");//เซฮเวอร์โวทำงาน
    PT_DELAY(pt, 500, ts);
    count2=0;
    count1=0;
    }
    }
  }
  PT_END(pt);
}
PT_THREAD(lock(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while(1){
    data = Ciao.read(CONNECTOR, SERVER_ADDR, readAddr);
 //   order=String(data.get(2));
  if(String(data.get(2))=="true"){
    if (lockcheck==0) {
      servo.write(140);
      PT_DELAY(pt,2000, ts);
      lockcheck=1;
    }
  }
  else if(String(data.get(2))=="false"){
    servo.write(30);
    lockcheck=0;
    
  }
   PT_DELAY(pt,2000, ts); 
  }
  PT_END(pt);
}
 
