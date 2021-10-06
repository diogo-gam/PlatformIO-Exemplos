/*
 *  
 *
 */

#include <Arduino.h>

#define OUTPUT_PORT Serial

int ledState = LOW;

unsigned long previousMillis = 0;
const long interval = 500;
int LED = LED_PIN;

void setup()
{
  pinMode(LED, OUTPUT);
  OUTPUT_PORT.begin(115200);
  OUTPUT_PORT.println(F("\r\n\nSistema Iniciado:"));
}

void loop()
{
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(LED, ledState);
    OUTPUT_PORT.print("ledState: ");
    OUTPUT_PORT.println(ledState);
  }
}
