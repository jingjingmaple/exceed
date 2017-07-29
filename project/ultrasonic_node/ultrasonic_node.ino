#define SENT D1
#define REV D2
void setup() {
  // put your setup code here, to run once:
  pinMode(SENT,OUTPUT);
  pinMode(REV,INPUT);
  pinMode(D3,OUTPUT);
  Serial.begin(9600);
}
float getData() {
  int c=0;
  float distanceCm =-555;
  float before;
  while(true) {
    c++;
    if (c >8) {
      return 0; 
    }
    //Serial.println(c);
    float duration;
    //float distanceCm, distanceIn;
    digitalWrite(SENT,LOW);
    delayMicroseconds(2);
    digitalWrite(SENT,HIGH);
    delayMicroseconds(10);
    digitalWrite(SENT,LOW);
    duration = pulseIn(REV,HIGH);
    distanceCm = duration / 29.1 / 2;
    //distanceIn = duration / 74 / 2 ;
    if (distanceCm <=0) {
      //Serial.println("Can't detect.");
      continue;
    } else if (duration >=23529) {
      //Serial.println("Out of range");
      continue;
    } else {
      //Serial.println("Duration: "+String(duration)+", CM: "+String(distanceCm)+", In: "+String(distanceIn));
    }
    if (abs(distanceCm-before) < 3) {
      return distanceCm;
    }
    before=distanceCm;
    
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  if (getData() >0 && getData() <7) {
    digitalWrite(D3,HIGH);
  } else {
    digitalWrite(D3,LOW);
  }
  delay(200);
}
