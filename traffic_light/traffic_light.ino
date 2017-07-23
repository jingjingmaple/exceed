#define RED 2
#define YELLOW 3
#define GREEN 4
#define SWITCH 5
#define BUZZER 6
#define SWITCH_PRESSED LOW
#define SWITCH_UNPRESSED HIGH
String now="green";
void setup() {
  // put your setup code here, to run once:
  pinMode(RED,OUTPUT);
  pinMode(YELLOW,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(SWITCH,INPUT);
  now = "green";
  Serial.begin(9600);
}
void detect() {
  if (now == "red"){
    digitalWrite(GREEN,HIGH);
    digitalWrite(RED,LOW);
    //digitalWrite(YELLOW,LOW);
    analogWrite(BUZZER,1);
    now="green";
  } else if (now=="green") {
    analogWrite(BUZZER,0);
    digitalWrite(GREEN,LOW);
    digitalWrite(YELLOW,HIGH);
    delay(1000);
    digitalWrite(YELLOW,LOW);
    digitalWrite(RED,HIGH);
    now="red";
  }
}

void loop() {
  if (digitalRead(SWITCH) == SWITCH_PRESSED) {
    delay(200);
    if (digitalRead(SWITCH) == SWITCH_PRESSED) {
      detect();
    }
  }
  delay(100);
}
