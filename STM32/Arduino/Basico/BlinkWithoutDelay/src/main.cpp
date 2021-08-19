/*
 *  ESP8266 BlinkWithoutDelay by Simon Peter
 *
 */

#include <Arduino.h>

#define DBG_OUTPUT_PORT Serial

int ledState = LOW;

unsigned long previousMillis = 0;
const long interval = 100;
// int LED = 13;
int LED = PC13;

void setup()
{
  pinMode(LED, OUTPUT);
  DBG_OUTPUT_PORT.begin(115200);
  DBG_OUTPUT_PORT.println(F("\r\n\nSistema Iniciado:"));
}

void loop()
{
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
    digitalWrite(LED, ledState);
    DBG_OUTPUT_PORT.print("ledState: ");
    DBG_OUTPUT_PORT.println(ledState);
  }
}
