#define LED_R 3
#define LED_G 4
#define LED_B 5
#define LED_WW 18
#define LED_WC 19

#include <Arduino.h>
#define OUTPUT_PORT Serial

int delayTime = 1000;
int LED = LED_R;

void setup() {
  pinMode(LED, OUTPUT);
  OUTPUT_PORT.begin(115200);
  OUTPUT_PORT.println("\n\nSistema Iniciado!\n");
}

int n = 0;
void loop() {
  OUTPUT_PORT.print("n = ");
  OUTPUT_PORT.println(n++);
  digitalWrite(LED, 0);
  delay(delayTime);
  digitalWrite(LED, 1);
  delay(delayTime);            
}