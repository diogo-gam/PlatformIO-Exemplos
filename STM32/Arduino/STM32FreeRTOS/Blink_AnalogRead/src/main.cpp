/*
 * Based on Blink_AnalogRead example from: https://github.com/feilipu/Arduino_FreeRTOS_Library
 * Modified by: Frederic Pillon <frederic.pillon (at) st.com>
 */

#include <Arduino.h>
#include <STM32FreeRTOS.h>

#define OUTPUT_PORT Serial

// define two tasks for Blink & AnalogRead
void TaskBlink(void *pvParameters);
void TaskAnalogRead(void *pvParameters);

// the setup function runs once when you press reset or power the board
void setup()
{

  // initialize serial communication at 9600 bits per second:
  OUTPUT_PORT.begin(115200);
  OUTPUT_PORT.println("--- STM32FreeRTOS Iniciado! ---");

  // Now set up two tasks to run independently.
  xTaskCreate(
      TaskBlink, (const portCHAR *)"Blink" // A name just for humans
      ,
      128 // This stack size can be checked & adjusted by reading the Stack Highwater
      ,
      NULL, 2 // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
      ,
      NULL);

  xTaskCreate(
      TaskAnalogRead, (const portCHAR *)"AnalogRead", 128 // Stack size
      ,
      NULL, 1 // Priority
      ,
      NULL);

  // start scheduler
  vTaskStartScheduler();
  OUTPUT_PORT.println("Insufficient RAM");
  while (1)
    ;
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlink(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  // initialize digital LED_PIN on pin 13 as an output.
  pinMode(LED_PIN, OUTPUT);

  while(true) // A Task shall never return or exit.
  {
    digitalWrite(LED_PIN, HIGH);       // turn the LED on (HIGH is the voltage level)
    vTaskDelay(1000 / portTICK_PERIOD_MS); // wait for one second
    digitalWrite(LED_PIN, LOW);        // turn the LED off by making the voltage LOW
    vTaskDelay(1000 / portTICK_PERIOD_MS); // wait for one second
  }
}

void TaskAnalogRead(void *pvParameters) // This is a task.
{
  (void)pvParameters;
  while(true)
  {
    // read the input on analog pin 0:
    int sensorValue = analogRead(A0);
    // print out the value you read:
    OUTPUT_PORT.print("sensorValue = ");
    OUTPUT_PORT.println(sensorValue);
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}
