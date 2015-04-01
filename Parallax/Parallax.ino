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
float currentReading;
float prevReading = 0.0;
float velocity = 0.0;

void setup()
{
  Serial.begin(TERMINAL_MONITOR_BAUDRATE);
  timer0 = 0;
  rf1Serial.begin(RF1.getAuxUartBaudRate());
  RF1.begin(rf1Serial);
  RF1.set00vDistance(0.0);
  RF1.setAnalogInputPin(1);
}

void loop()
{
  if(timer0 > interval){
    timer0-=interval;
    prevReading = RF1.getAnalogDistance()-0.80;
    delay(10);
    Serial.print("Distance: ");
    currentReading = RF1.getAnalogDistance()-0.80;
    Serial.print(currentReading);
    if(prevReading != currentReading) {
      //not detecting something that is stationary
      //can beep 
    }
    Serial.println(" m");
    
  }
}

