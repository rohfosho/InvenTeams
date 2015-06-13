#include <StopWatch.h>
#include <SoftwareSerial.h>
#include <SF02.h>

#define TERMINAL_MONITOR_BAUDRATE  9600

#define SERIAL_RX_PIN      11
#define SERIAL_TX_PIN      10
#define SERIAL_RX_PIN_2     6
#define SERIAL_TX_PIN_2     5
#define ANALOG_PIN_1        1
#define ANALOG_PIN_2        0

SF02 RF1;
SoftwareSerial rf1Serial(SERIAL_RX_PIN, SERIAL_TX_PIN);
SF02 RF2;
SoftwareSerial rf2Serial(SERIAL_RX_PIN_2, SERIAL_TX_PIN_2);

StopWatch stopWatch(StopWatch::MICROS);

float curReading1, curReading2;
float prevReading1 = 0.0, prevReading2 = 0.0;
float d1, d2; 
float dx; //distance object travels between rf1 and rf2
float total1 = 0.0, total2 = 0.0; //for testing only
float v = 0.0;
float x = 0.127; //distance in meters between rangefinders
float minChange = 0.7;
float minVelocity = 2.0; //meters per second (min velocity to be bike)
float maxVelocity = 8.0; //meteres per second (max velocity to be bike)
boolean detected = false; //was object detected from first rangefinder
int counter = 0;
int speakerPin = 9;

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
  pinMode(speakerPin,OUTPUT);
  
}

void loop()
{
    dx = 0;
    delay(50);
    curReading1 = RF1.getAnalogDistance()-2.8;
    curReading2 = RF2.getAnalogDistance()-1;
    
    //Serial.print(curReading1);
    //Serial.print(", ");
    //Serial.println(curReading2);
    if(prevReading1 < 0.05 && prevReading2 < 0.05) {
      prevReading1 = curReading1;
      prevReading2 = curReading2;
    }
    float change1 = prevReading1-curReading1;
    float change2 = prevReading2-curReading2;

    if(change1 >= minChange && !detected) {
      stopWatch.start();
      d1 = curReading1;
      detected=true;
      //Serial.println(detected);
    }

    if(change2 >= minChange && detected) {
      stopWatch.stop();
      unsigned long dt = stopWatch.value();
      stopWatch.reset();
      d2 = curReading2;
      double diff = d1-d2;
      if(diff < 0) {
        diff = -1*diff;
      }
      Serial.println(d1);
      Serial.println(d2);
      Serial.println(diff);
      dx = sqrt(pow(x,2)+pow(diff,2));
      Serial.print("dx: ");
      Serial.println(dx,10);
      Serial.print("dt: ");
      double elapsedTime = (double)dt/1000000;
      Serial.println(elapsedTime,10);    
      v = dx/elapsedTime;
      Serial.print("v: ");
      Serial.println(v);
      detected = false;
      //Serial.println(detected);
      if(v > minVelocity && v < maxVelocity) {
        //BEEP
        digitalWrite(speakerPin, HIGH);
      }
    }
    
    prevReading1 = curReading1;
    prevReading2 = curReading2;
}
