/**
 * exemplo basico piscando led e enviando olá na serial
 * 
 */

#include <Arduino.h>
#define DBG_OUTPUT_PORT Serial
#define LED 2

int delayTime = 1000;

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
  delay(delayTime);
  digitalWrite(LED, 1);
  delay(delayTime);            
}