#define LED 3
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i<=200; i++) {
    analogWrite(LED,i);
    delay(25);
  }
   for (int i=200; i>=0; i--) {
    analogWrite(LED,i);
    delay(25);
  }

}
