
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
bool isPrime(int in) {
  int i=0;
  for(int i=0;i<=(in/2);i++) {
    if ((in%i)==0) {
      return false;
    }
  }
  return true;
}
int x=1;
void loop() {
  int y = x+6;
  if (isPrime(x)) {
    Serial.print("(");
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(")");
    Serial.print("\n");
  }
  x++;
  delay(1000);
}
