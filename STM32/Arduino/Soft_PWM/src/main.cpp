/*
 *  
 *
 */

#include <Arduino.h>

#define OUTPUT_PORT Serial

#define CH1 PA4
#define CH2 PA5
#define CH3 PA6
#define N_CHANNELS 3

int channels[N_CHANNELS] = {CH1, CH2, CH3};
// int chState[N_CHANNELS] = 0;
int chState = 0;

unsigned long previousMicros = 0;
const long interval = 1;

void setup()
{
  for (int i = 0; i < N_CHANNELS; i++)
  {
    pinMode(channels[i], OUTPUT);
  }
  
  OUTPUT_PORT.begin(115200);
  OUTPUT_PORT.println(F("\r\n\nSistema Iniciado:"));
}

void loop()
{
  unsigned long currentMicros = micros();
  if(currentMicros - previousMicros >= interval) {
    previousMicros = currentMicros;
    chState = !chState;
    for (int i = 0; i < N_CHANNELS; i++)
    {
      digitalWrite(channels[i], chState);
    }
  }
}
