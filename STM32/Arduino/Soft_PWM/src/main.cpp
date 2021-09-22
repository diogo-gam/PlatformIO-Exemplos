/*
 *  
 *
 */

#include <Arduino.h>

#define OUTPUT_PORT Serial

#define CH1 PA4
#define CH2 PA5
#define CH3 PA6

int chState = LOW;

unsigned long previousMicros = 0;
const long interval = 1;
int channel = CH1;

void setup()
{
  pinMode(channel, OUTPUT);
  OUTPUT_PORT.begin(115200);
  OUTPUT_PORT.println(F("\r\n\nSistema Iniciado:"));
}

void loop()
{
  unsigned long currentMicros = micros();
  if(currentMicros - previousMicros >= interval) {
    previousMicros = currentMicros;
    chState = !chState;
    digitalWrite(channel, chState);
  }
}
