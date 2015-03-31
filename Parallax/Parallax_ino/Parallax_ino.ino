#include <SoftwareSerial.h>
#include <SF02.h>

#define TERMINAL_MONITOR_BAUDRATE  9600

// Arduino Pin Definitions - Set these to whatever suits your Ardunio configuration.
#define SERIAL_RX_PIN      11
#define SERIAL_TX_PIN      10

SF02 sf02;
SoftwareSerial sf02Serial(SERIAL_RX_PIN, SERIAL_TX_PIN);

/*
  In this example. We setup communications with the SF02 using 
  the SoftwareSerial interface. If no interface is specified, the
  default hardware serial interface will be used.
  
  An on-demand request for a distance reading can then eaily 
  be made from the SF02 module, by simply calling getDistance()
  on the SF02 instance.
*/

void setup()
{
  Serial.begin(TERMINAL_MONITOR_BAUDRATE);
  
  sf02Serial.begin(sf02.getAuxUartBaudRate());
  sf02.begin(sf02Serial);
  sf02.setAnalogInputPin(1);
}

void loop()
{
  Serial.print("Distance: ");
  Serial.print(sf02.getAnalogDistance());
  Serial.println(" m");
}
