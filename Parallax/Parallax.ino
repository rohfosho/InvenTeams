#include <elapsedMillis.h>
#include <SoftwareSerial.h>
#include <SF02.h>

#define TERMINAL_MONITOR_BAUDRATE  9600

// Arduino Pin Definitions - Set these to whatever suits your Ardunio configuration.
#define SERIAL_RX_PIN      11
#define SERIAL_TX_PIN      10
#define SERIAL_RX_PIN_2     6
#define SERIAL_TX_PIN_2     5

SF02 RF1;
SoftwareSerial rf1Serial(SERIAL_RX_PIN, SERIAL_TX_PIN);
SF02 RF2;
SoftwareSerial rf2Serial(SERIAL_RX_PIN_2, SERIAL_TX_PIN_2);

elapsedMillis timer();
#define interval 20
int timer0;
float curReading1;
float curReading2;
float prevReading1 = 0.0;
float prevReading2 = 0.0;
float velocity = 0.0;

void setup()
{
  Serial.begin(TERMINAL_MONITOR_BAUDRATE);
  timer0 = 0;
  rf1Serial.begin(RF1.getAuxUartBaudRate());
  RF1.begin(rf1Serial);
  RF1.set00vDistance(0.0);
  RF1.setAnalogInputPin(1);
  rf2Serial.begin(RF2.getAuxUartBaudRate());
  RF2.begin(rf2Serial);
  RF2.set00vDistance(0.0);
  RF2.setAnalogInputPin(2);
}

void loop()
{
    curReading1 = RF1.getAnalogDistance()-0.80;
    curReading2 = RF2.getAnalogDistance()-0.80;
    Serial.print("Distance: ");
    Serial.print(curReading1);
    if(prevReading1 < 0.05 && prevReading2 < 0.05) {
      if(prevReading1 != curReading1) {
        //not detecting something that is stationary
        //can beep
       Serial.print("beep"); 
      }
      if(prevReading2 != curReading2) {
        //not detecting something that is stationary
        //can beep 
        Serial.print("beep");        
      }
    }
    Serial.println(" m");
    prevReading1 = curReading1;
    prevReading2 = curReading2;
}

