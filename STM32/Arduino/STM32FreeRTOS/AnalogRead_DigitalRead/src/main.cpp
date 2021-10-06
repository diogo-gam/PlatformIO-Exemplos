/*
 * Based on AnalogRead_DigitalRead example from: https://github.com/feilipu/Arduino_FreeRTOS_Library
 * Modified by: Frederic Pillon <frederic.pillon (at) st.com>
 */

#include <Arduino.h>
#include <STM32FreeRTOS.h>

#define OUTPUT_PORT Serial

// Declare a mutex Semaphore Handle which we will use to manage the Serial Port.
// It will be used to ensure only only one Task is accessing this resource at any time.
SemaphoreHandle_t xSerialSemaphore;

// define two Tasks for DigitalRead & AnalogRead
void TaskDigitalRead(void *pvParameters);
void TaskAnalogRead(void *pvParameters);

// the setup function runs once when you press reset or power the board
void setup()
{

  // initialize serial communication at 9600 bits per second:
  OUTPUT_PORT.begin(115200);
  OUTPUT_PORT.println("--- STM32FreeRTOS Iniciado! ---");

  // Semaphores are useful to stop a Task proceeding, where it should be paused to wait,
  // because it is sharing a resource, such as the Serial port.
  // Semaphores should only be used whilst the scheduler is running, but we can set it up here.
  if (xSerialSemaphore == NULL) // Check to confirm that the Serial Semaphore has not already been created.
  {
    xSerialSemaphore = xSemaphoreCreateMutex(); // Create a mutex semaphore we will use to manage the Serial Port
    if ((xSerialSemaphore) != NULL)
      xSemaphoreGive((xSerialSemaphore)); // Make the Serial Port available for use, by "Giving" the Semaphore.
  }

  // Now set up two Tasks to run independently.
  xTaskCreate(
      TaskDigitalRead, (const portCHAR *)"DigitalRead" // A name just for humans
      ,
      128 // This stack size can be checked & adjusted by reading the Stack Highwater
      ,
      NULL
      ,
      2 // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
      ,
      NULL);

  xTaskCreate(
      TaskAnalogRead, (const portCHAR *)"AnalogRead",
      128 // Stack size
      ,
      NULL
      , 
      1 // Priority
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

void TaskDigitalRead(void *pvParameters __attribute__((unused))) // This is a Task.
{
  /*
    DigitalReadSerial
    Reads a digital input on pin defined with USER_BUTTON, prints the result to the serial monitor

    This example code is in the public domain.
  */

  // defined USER_BUTTON digital pin  has a pushbutton attached to it. Give it a name:
  uint8_t pushButton = USER_BUTTON;

  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);

  int buttonState;
  int lastbuttonState;

  for (;;) // A Task shall never return or exit.
  {
    // read the input pin:
    buttonState = digitalRead(pushButton);

    // See if we can obtain or "Take" the Serial Semaphore.
    // If the semaphore is not available, wait 5 ticks of the Scheduler to see if it becomes free.
    if (xSemaphoreTake(xSerialSemaphore, (TickType_t)5) == pdTRUE)
    {
      // We were able to obtain or "Take" the semaphore and can now access the shared resource.
      // We want to have the Serial Port for us alone, as it takes some time to print,
      // so we don't want it getting stolen during the middle of a conversion.
      // print out the state of the button:
      if(buttonState != lastbuttonState){
        lastbuttonState = buttonState;
        if (buttonState == 0)
          OUTPUT_PORT.println("Botao acionado");
      }
      // OUTPUT_PORT.print("Button state: ");
      // OUTPUT_PORT.println(buttonState);

      xSemaphoreGive(xSerialSemaphore); // Now free or "Give" the Serial Port for others.
    }

    vTaskDelay(15/portTICK_PERIOD_MS);

  }
}

void TaskAnalogRead(void *pvParameters __attribute__((unused))) // This is a Task.
{

  while(1)
  {
    int sensorValue = analogRead(A1);

    // See if we can obtain or "Take" the Serial Semaphore.
    // If the semaphore is not available, wait 5 ticks of the Scheduler to see if it becomes free.
    if (xSemaphoreTake(xSerialSemaphore, (TickType_t)5) == pdTRUE)
    {
      // We were able to obtain or "Take" the semaphore and can now access the shared resource.
      // We want to have the Serial Port for us alone, as it takes some time to print,
      // so we don't want it getting stolen during the middle of a conversion.
      // print out the value you read:
      OUTPUT_PORT.println(sensorValue);

      xSemaphoreGive(xSerialSemaphore); // Now free or "Give" the Serial Port for others.
    }

    vTaskDelay(500/portTICK_PERIOD_MS);
  }
}