#include <pt.h>
#define PT_DELAY(pt, ms, ts)\
  ts = millis();\
  PT_WAIT_WHILE(pt, millis()-ts < (ms));
struct pt pt_task1;
struct pt pt_task2;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  PT_INIT(&pt_task1);
  PT_INIT(&pt_task2);
}

void loop() {
  // put your main code here, to run repeatedly:
  task1(&pt_task1);
  task2(&pt_task2);
}
PT_THREAD(task1(struct pt* pt)) {
  static uint32_t ts;
  PT_BEGIN(pt);
  while(1) {
    Serial.println("task1");
    PT_DELAY(pt, 1000, ts);
  }
  PT_END(pt);
}
PT_THREAD(task2(struct pt* pt)) {
  static uint32_t ts;
  PT_BEGIN(pt);
  while(1) {
    Serial.println("task2");
    PT_DELAY(pt, 2000, ts);
  }
  PT_END(pt);
}

