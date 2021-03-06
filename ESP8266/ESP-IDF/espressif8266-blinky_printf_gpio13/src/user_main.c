#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_config.h"

#define led 13
static volatile os_timer_t some_timer;


void some_timer_func(void *arg) // in Arduino this is loop the main loop
{
  //Do blinky stuff
	if GPIO_INPUT_GET(led) {
    //Set led to LOW
		GPIO_OUTPUT_SET(led, LOW); // in Arduino this is digitalWrite(led, LOW)
		os_printf("ON \n\r");      // In Arduino this is Serial.println("ON");

  }
  else {
    //Set led to HIGH
		GPIO_OUTPUT_SET(led, HIGH); // in Arduino this is digitalWrite(led, HIGH)
		os_printf("OFF \n\r");      // In Arduino this is Serial.println("OFF");

  }
}


//Init function
void ICACHE_FLASH_ATTR
user_init()  // in arduino this is setup()
{
  // Initialize the GPIO subsystem.
  gpio_init();
	//Set GPIO13 to output mode
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13);
  //Set GPIO low
  GPIO_OUTPUT_SET(led, LOW); //  Compared with arduino pinMode(led, OUTPUT);

  // Initialize UART0
	uart_div_modify(0, UART_CLK_FREQ / 115200);  // In Arduino this is Serial.begin(115200);

	os_printf("ESP8266 chip ID:0x%x\n", system_get_chip_id());
	os_printf("\nHello World, Blinking\n\r"); // In Arduino this is Serial.println("Hello World, Blinking");

	// In Arduino there is 1 loop, Under ESP8266 you can have several loops next to each other.
	// To setup a loop use the 3 timer commands below. This will start the function called some_timer
	// some_timer will be repeated every second.

  //Disarm timer
  os_timer_disarm(&some_timer);

  //Setup timer
  os_timer_setfn(&some_timer, (os_timer_func_t *)some_timer_func, NULL);

  //Arm the timer
  //&some_timer is the pointer
  //1000 is the fire time in ms
  //0 for once and 1 for repeating
  os_timer_arm(&some_timer, 1000, 1);

}
