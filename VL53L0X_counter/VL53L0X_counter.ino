// С помошью TOF-датчика считает вылетающие из станка детали. На 4000 штук делает отсечку. Выводит на дисплей текущее состояние. При каждом подсчете издает звуковой сигнал.

#include <Wire.h>
#include <VL53L0X.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
VL53L0X sensor;
#define LONG_RANGE
int callPin = A2;
int counter = 0;
unsigned long prev_ms = 0;

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  sensor.init();
  sensor.setTimeout(1); //500

#if defined LONG_RANGE
 // уменьшить предел скорости обратного сигнала (по умолчанию 0,25 MCPS)
  sensor.setSignalRateLimit(0.1);
 // увеличить периоды лазерных импульсов (по умолчанию 14 и 10 PCLK)
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
#endif

#if defined HIGH_SPEED
  // уменьшить  время до 20 мс (по умолчанию около 33 мс)
  sensor.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
 // увеличить время  до 200 мс
  sensor.setMeasurementTimingBudget(200000);
#endif

  // Очистить буфер.
  display.clearDisplay();
  display.setRotation(0);
  display.display();

  display.setTextColor(WHITE);
  pinMode(callPin, OUTPUT);
}

void displayDistance( int val, int ctr)
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(3,12);
  display.print(val);

  display.setTextSize(2);
  display.setCursor(40,12);
  display.print(ctr);
  
  display.display();
  pinMode(7, OUTPUT);
}
void beep (){
      digitalWrite(callPin, HIGH);     // включаем звук
      delay(300);
      digitalWrite(callPin, LOW);
      delay(300);
}


void loop()
{
  unsigned long currentTime = millis();
  int r = sensor.readRangeSingleMillimeters();
  
  r = r - 40;
  Serial.print(r);
  Serial.println();

  displayDistance( r, counter);
 
 if ((r < 100 ) && (currentTime - prev_ms > 2000)) {
    counter++;
    digitalWrite(callPin, HIGH);     // включаем звук
    delay(300);
    digitalWrite(callPin, LOW);      // выключаем звук 
    prev_ms = currentTime;
  }

  if ((counter == 4000)  && (currentTime - prev_ms > 1000)) {
    beep();
    beep();
    beep();
    beep();
    beep();
    beep();
    beep();
    counter = 0;
    delay(5000);
    prev_ms = currentTime;
  }

}







