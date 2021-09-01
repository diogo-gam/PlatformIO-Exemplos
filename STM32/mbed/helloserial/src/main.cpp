#include <mbed.h>

#define DELAY 0.2

Serial pc(SERIAL_TX, SERIAL_RX, 115200); // tx, rx, baudrate
DigitalOut myled(LED1);          //vermelho

int main()
{
  pc.printf("Sistema Iniciado!\n");
  while (1)
  {
    myled = !myled;
    wait(DELAY);
  }
}
