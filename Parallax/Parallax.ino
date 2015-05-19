#include <StopWatch.h>
#include <SoftwareSerial.h>
#include <SF02.h>

#define TERMINAL_MONITOR_BAUDRATE  9600

#define SERIAL_RX_PIN      11
#define SERIAL_TX_PIN      10
#define SERIAL_RX_PIN_2     6
#define SERIAL_TX_PIN_2     5
#define ANALOG_PIN_1        1
#define ANALOG_PIN_2        2

SF02 RF1;
SoftwareSerial rf1Serial(SERIAL_RX_PIN, SERIAL_TX_PIN);
SF02 RF2;
SoftwareSerial rf2Serial(SERIAL_RX_PIN_2, SERIAL_TX_PIN_2);

StopWatch sw(StopWatch::MICROS);

#define interval 20
unsigned long dt;
long timeElapsed;
float curReading1, curReading2;
float prevReading1 = 0.0, prevReading2 = 0.0;
float d1, d2, dx;
float v = 0.0;
float x = 0.127; //distance in meters between rangefinders
float minChange = 0.7;
float minVelocity = 2.0;
boolean detected = false;

void setup()
{
  Serial.begin(TERMINAL_MONITOR_BAUDRATE);
  rf1Serial.begin(RF1.getAuxUartBaudRate());
  RF1.begin(rf1Serial);
  RF1.set00vDistance(0.0);
  RF1.setAnalogInputPin(ANALOG_PIN_1);
  rf2Serial.begin(RF2.getAuxUartBaudRate());
  RF2.begin(rf2Serial);
  RF2.set00vDistance(0.0);
  RF2.setAnalogInputPin(ANALOG_PIN_2);
}

void loop()
{
    dx = 0;
    delay(100);
    curReading1 = RF1.getAnalogDistance()-2.8;
    curReading2 = RF2.getAnalogDistance()-2.8;
    if(prevReading1 < 0.05 && prevReading2 < 0.05) {
      prevReading1 = curReading1;
      prevReading2 = curReading2;
    }
    float change1 = prevReading1-curReading1;
    float change2 = prevReading2-curReading2;
    dt = 0;
    Serial.print("Change 1: ");
      Serial.println(change1);
    if(change1 >= minChange && !detected) {
      sw.reset();
      sw.start();
      Serial.print("starting time: ");
      Serial.println(sw.value());
      d1 = curReading1;
      detected=true;
    }

    if(change2 >= minChange && detected) {
      Serial.print("Change 2: ");
      Serial.println(change2);
      Serial.print("dt: ");
      Serial.println(dt);
      d2 = curReading2;
      Serial.print("D1: ");
        Serial.println(d1);
      Serial.print("D2: ");
        Serial.println(d2);
      Serial.print("StopWatch Value: ");
      Serial.println(sw.value());
      sw.stop();
      double diff = d1-d2;
      if(diff < 0) {
        diff = -1*diff;
      }
      dx = sqrt(pow(x,2)+pow(diff,2));
      //Serial.print("dx: ");
      //Serial.println(dx,10);
      //v = dx/(timeElapsed);
      detected = false;
      //Serial.println(detected);
    }
    
    if(dt > 0 && v > minVelocity) {
      //Serial.println("beep"); //make sound with buzzer
    }
    prevReading1 = curReading1;
    prevReading2 = curReading2;
}
