#define SWITCH 2
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SWITCH, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(digitalRead(SWITCH));
  delay(100);
}
