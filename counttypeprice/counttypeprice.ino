String str= "i can't breathe without you but i have to";
int total;
void setup() {
  Serial.begin(9600);
  total = 0;
  for(char x : str) {
    if(x>= 'A' && x<='Z') {
      total +=5;
    } else if(x>='a' && x<='z') {
      total +=3;
    } else if(x>='0' && x<='9') {
      total +=7;
    } else {
      total += 1;
    }
  }
  Serial.print(total);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
}
