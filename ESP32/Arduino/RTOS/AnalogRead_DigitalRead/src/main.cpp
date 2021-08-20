/*
 * Based on AnalogRead_DigitalRead example from: https://github.com/feilipu/Arduino_FreeRTOS_Library
 * Modified by: Frederic Pillon <frederic.pillon (at) st.com>
 * Traduzido por Petrus Candido <petrusz1 (at) gmail.com>
 * 
 * TODO: Terminar de traduzir
 */

#include <Arduino.h>
#include <STM32FreeRTOS.h>

// Se não houver nennum pino definido para o botão do usuário, definimos um
#ifndef USER_BTN
#define USER_BTN PC_13 //Nucleo64
#endif

// #define USER_BTN PA0 //black pill

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
  Serial.begin(115200);

  // Semaphores are useful to stop a Task proceeding, where it should be paused to wait,
  // because it is sharing a resource, such as the Serial port.
  // Semaphores should only be used whilst the scheduler is running, but we can set it up here.
  if (xSerialSemaphore == NULL) // Check to confirm that the Serial Semaphore has not already been created.
  {
    xSerialSemaphore = xSemaphoreCreateMutex(); // Create a mutex semaphore we will use to manage the Serial Port
    if ((xSerialSemaphore) != NULL)
      xSemaphoreGive((xSerialSemaphore)); // Make the Serial Port available for use, by "Giving" the Semaphore.
  }

  // criamos duas tarefas que vão rodar independentes
  xTaskCreate(
      TaskDigitalRead, (const portCHAR *)"DigitalRead" // A name just for humans
      ,
      128 // tamanho da pilha pode ser analisada e ajustada usando o Stack Highwater
      ,
      NULL
      ,
      2 // prioridade com 3 (configMAX_PRIORITIES - 1) sendo a maior e 0 sendo a menor
      ,
      NULL);

  xTaskCreate(
      TaskAnalogRead, (const portCHAR *)"AnalogRead",
      128 // tamanho da pilha (memória)
      ,
      NULL
      , 
      1 // prioridade
      ,
      NULL);

  // Inicia o agendador de tarefas
  vTaskStartScheduler();
  Serial.println("Insufficient RAM");
  while (1)
    ;
}

void loop()
{
  // Vazio. tudo roda nas tarefas
}

/*--------------------------------------------------*/
/*--------------------- Tarefas --------------------*/
/*--------------------------------------------------*/

void TaskDigitalRead(void *pvParameters __attribute__((unused))) // This is a Task.
{
  /*
    DigitalReadSerial
    Reads a digital input on pin defined with USER_BTN, prints the result to the serial monitor

    This example code is in the public domain.
  */

  // defined USER_BTN digital pin  has a pushbutton attached to it. Give it a name:
  uint8_t pushButton = USER_BTN;

  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);

  int buttonState;
  int lastbuttonState;

  for (;;) // esta tarefa nunca deve retornar ou sair
  {
    // lê o estado do pino de entrada
    buttonState = digitalRead(pushButton);

    // See if we can obtain or "Take" the Serial Semaphore.
    // If the semaphore is not available, wait 5 ticks of the Scheduler to see if it becomes free.
    if (xSemaphoreTake(xSerialSemaphore, (TickType_t)5) == pdTRUE)
    {
      // Fomos capazes de obter ou "tomar" o semáfoto e agora podemos acessar o recurso compartilhado
      // Nós queremos ter a porta serial somente para nós já que demora algum tempo para imprimir
      // para que ele não seja 'roubado' durante uma conversão
      // imprime o estado do botão
      if(buttonState != lastbuttonState){
        lastbuttonState = buttonState;
        if (buttonState == 0)
          Serial.println("Botao acionado");
      }
      // Serial.print("Button state: ");
      // Serial.println(buttonState);

      xSemaphoreGive(xSerialSemaphore); // Agora nos "damos" a porta serial para os outros
    }

    vTaskDelay(15 / portTICK_PERIOD_MS); // osDelay(15);
  }
}

void TaskAnalogRead(void *pvParameters __attribute__((unused))) // Isto e uma tarefa
{

  for (;;)
  {
    // read the input on analog pin 0:
    int sensorValue = analogRead(A0);

    // See if we can obtain or "Take" the Serial Semaphore.
    // If the semaphore is not available, wait 5 ticks of the Scheduler to see if it becomes free.
    if (xSemaphoreTake(xSerialSemaphore, (TickType_t)5) == pdTRUE)
    {
      // Fomos capazes de obter ou "tomar" o semáfoto e agora podemos acessar o recurso compartilhado
      // Nós queremos ter a porta serial somente para nós já que demora algum tempo para imprimir
      // para que ele não seja 'roubado' durante uma conversão
      // imprime a leitura analógica
      Serial.println(sensorValue);

      xSemaphoreGive(xSerialSemaphore); // Agora nos "damos" a porta serial para os outros
    }

    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}