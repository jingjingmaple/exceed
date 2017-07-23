#include <dht.h>
#define DHT11 2
dht DHT;
int dhtTemp;
int temperature;
int humidity;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  dhtTemp = DHT.read11(DHT11);
  temperature = (int) DHT.temperature;
  humidity = (int) DHT.humidity;
  Serial.println("Temp: "+String(temperature)+", Humidity: "+String(humidity));
  delay(3000);
}
