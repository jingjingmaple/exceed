#define SENT 7
#define REV 8
void setup() {
  // put your setup code here, to run once:
  pinMode(SENT,OUTPUT);
  pinMode(REV,INPUT);
  Serial.begin(9600);
}
long getData() {
  long duration, distanceCm, distanceIn;
  digitalWrite(SENT,LOW);
  delayMicroseconds(2);
  digitalWrite(SENT,HIGH);
  delayMicroseconds(10);
  digitalWrite(SENT,LOW);
  duration = pulseIn(REV,HIGH);
  distanceCm = duration / 29.1 / 2;
  distanceIn = duration / 74 / 2 ;
  if (distanceCm <=0) {
    Serial.println("Can't detect.");
  } else if (duration >=1324) {
    Serial.println("Out of range");
  } else {
    Serial.println("Duration: "+String(duration)+", CM: "+String(distanceCm)+", In: "+String(distanceIn));
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  getData();
  delay(2000);
}
