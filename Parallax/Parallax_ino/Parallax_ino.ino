#include <elapsedMillis.h>
#include <SoftwareSerial.h>
#include <SF02.h>

#define TERMINAL_MONITOR_BAUDRATE  9600

// Arduino Pin Definitions - Set these to whatever suits your Ardunio configuration.
#define SERIAL_RX_PIN      11
#define SERIAL_TX_PIN      10

SF02 sf02;
SoftwareSerial sf02Serial(SERIAL_RX_PIN, SERIAL_TX_PIN);

elapsedMillis timer();
#define interval 50
float prevReading = 0.0;
float velocity = 0.0;

void setup()
{
  Serial.begin(TERMINAL_MONITOR_BAUDRATE);
  timer0 = 0;
  sf02Serial.begin(sf02.getAuxUartBaudRate());
  sf02.begin(sf02Serial);
  sf02.set00vDistance(0.0);
  sf02.setAnalogInputPin(1);
}

void loop()
{
  if(timer0 > interval){
    timer0-=interval;
    prevReading = sf02.getAnalogDistance()-0.80;
    Serial.print("Distance: ");
    Serial.print(sf02.getAnalogDistance()-0.80);
    Serial.println(" m");

  }
}

