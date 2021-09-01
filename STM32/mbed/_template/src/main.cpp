/* 
 * https://docs.platformio.org/en/latest/frameworks/mbed.html#mbed-os-5-and-mbed-2
 * 
 */

#include "mbed.h"
#include "platform/mbed_thread.h"

// USER_BUTTON 

// Blinking rate in milliseconds
#define BLINKING_RATE_MS    250


int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);

    while (true) {
        led = !led;
        thread_sleep_for(BLINKING_RATE_MS);
    }
}
