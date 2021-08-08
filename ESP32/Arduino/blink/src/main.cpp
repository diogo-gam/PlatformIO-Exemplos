/**
 * exemplo basico piscando led e enviando alo na serial
 * 
 */

#include <Arduino.h>
#define DBG_OUTPUT_PORT Serial
#define LED 13
#define DELAY 1000

void setup() {
  pinMode(LED, OUTPUT);
  DBG_OUTPUT_PORT.begin(115200);
  DBG_OUTPUT_PORT.println("\n\nSistema Iniciado!\n");
}

int n = 0;
void loop() {
  DBG_OUTPUT_PORT.print("n = ");
  DBG_OUTPUT_PORT.println(n++);
  digitalWrite(LED, 0);
  delay(DELAY);
  digitalWrite(LED, 1);
  delay(DELAY);            
}