long x,y,z;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  x= analogRead(A0);
  y= analogRead(A1);
  z= analogRead(A2);
  Serial.println("x: "+String(x)+" y:"+String(y)+" z:"+String(z));
  delay(400);
}
