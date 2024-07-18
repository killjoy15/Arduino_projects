// Данный код изменяет частоту оборотов вибромотора в зависимости от расстояния до объекта. Чем ближе объект, тем выше частота вибраций.

#include <Wire.h>
#include <VL53L1X.h>
VL53L1X sensor;

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C
  sensor.setTimeout(500);
  pinMode(2, OUTPUT);

 if (!sensor.init()) {
  Serial.println("Failed to detect and initialize sensor!");
  while (1);
 }

  sensor.setDistanceMode(VL53L1X::Short); // default Short, but works only Long (15000 + 15)
  sensor.setMeasurementTimingBudget(50000); // default 15000 
  sensor.startContinuous(50); // default 15
}

void loop()
{
  int sense = sensor.read();
  Serial.println(String(millis())+","+String(sense));

  if (sense > 10 && sense < 200) {
    digitalWrite(2,1); 
    delay(5);
    digitalWrite(2,0); 
    delay(200);
  }

  else if (sense >= 200 && sense < 500) {
    digitalWrite(2,1);
    delay(5);
    digitalWrite(2,0); 
    delay(400);
  }

  else if (sense >= 500 && sense < 1000) {
    digitalWrite(2,1);
    delay(5);
    digitalWrite(2,0); 
    delay(800);
  }

  else if (sense >= 1000 & sense < 1500) {
    digitalWrite(2,1);
    delay(5);
    digitalWrite(2,0); 
    delay(1600);
    }
  else {
    digitalWrite(2,0); 
  }



}
