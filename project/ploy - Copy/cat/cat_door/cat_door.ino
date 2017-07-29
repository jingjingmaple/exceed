#include <UnoWiFiDevEd.h>
#include <Wire.h>
#define CONNECTOR "rest"
#define SERVER_ADDR "158.108.165.223"
//char readAddr[] = "/data/AssassinZEED/people";
String writeAddrplus = "/data/AssassinZEED/countcat/set/plus";
String writeAddrmin = "/data/AssassinZEED/countcat/set/minus";
String writeAddr = "/data/AssassinZEED/countcat/set/";
int  count1,count2=0;

CiaoData data;

#define TRIG_PIN1 10 // outhome
#define ECHO_PIN1 11
                              //มี 2ตัว
#define TRIG_PIN2 12 // inhome
#define ECHO_PIN2 13
//#define servo 3
  void setup() {
  Serial.begin(9600);
  Ciao.begin();
  pinMode(TRIG_PIN1,OUTPUT);
  pinMode(ECHO_PIN1,INPUT);
  
  pinMode(TRIG_PIN2,OUTPUT);
  pinMode(ECHO_PIN2,INPUT);
}
 
void loop()
{
   int duration1, distanceMeter1,duration2, distanceMeter2;
   
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(TRIG_PIN1, LOW);
  delay(500);
  digitalWrite(TRIG_PIN1, HIGH);
  delay(500);
  digitalWrite(TRIG_PIN1, LOW);
  duration1 = pulseIn(ECHO_PIN1,HIGH);
 
  // convert the time into a distance
  distanceMeter1 = duration1 / 29.1 / 2 ;

digitalWrite(TRIG_PIN2, LOW);
  delay(500);
  digitalWrite(TRIG_PIN2, HIGH);
  delay(500);
  digitalWrite(TRIG_PIN2, LOW);
  duration2 = pulseIn(ECHO_PIN2,HIGH);
 
  // convert the time into a distance
  distanceMeter2 = duration2 / 29.1 / 2;

 if(distanceMeter1<distanceMeter2){// outside
  if(distanceMeter1<0){
    Serial.print("1ERROR!");
    Serial.println(distanceMeter1);
    }
  else if 
  (distanceMeter1 <= 3&count1!=1){// ต้องมั่นใจว่าเข้าใกล้จริงๆ
    //ส่งไปว่าminus
    Serial.print("1 ");
    Serial.println(distanceMeter1);
    count1++;
    count2=0;
  }
    else if(distanceMeter1 <= 3&count1==1)
    {data = Ciao.write(CONNECTOR, SERVER_ADDR, writeAddrplus);
    Serial.println("openplus");
    count1=0;
    count2=0; 
    delay(3000);
    data = Ciao.write(CONNECTOR, SERVER_ADDR, writeAddr);
    delay(3000);
    }
    }  
 else if(distanceMeter2<distanceMeter1){
    
    if(distanceMeter1<0){
    Serial.print("2ERROR!");
    Serial.println(distanceMeter2);
    }
    else if(distanceMeter2 <= 3&count2!=1){
      count2++;
      count1=0;
      Serial.print("2 ");
      Serial.println(distanceMeter2);
    }
    else if(distanceMeter2 <= 3&count2==1){
    data = Ciao.write(CONNECTOR, SERVER_ADDR, writeAddrmin);
    Serial.println("openminus");//เซฮเวอร์โวทำงาน
    delay(3000);
    count2=0;
    count1=0;
    data = Ciao.write(CONNECTOR, SERVER_ADDR, writeAddr);
    delay(3000);
    }
    }
}

