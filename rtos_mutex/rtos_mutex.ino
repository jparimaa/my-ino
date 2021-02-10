#include <Arduino_FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t mutex;

void printTask(void *pvParameters)
{
  TickType_t xTimeAtWhichMutexWasTaken;
  char *stringToPrint = (char *)pvParameters;
  while (true)
  {
    xSemaphoreTake(mutex, portMAX_DELAY);
    Serial.println(stringToPrint);
    xSemaphoreGive(mutex);

    vTaskDelay(pdMS_TO_TICKS(random(1, 5)));
  }
}

void setup()
{
  Serial.begin(9600);
  mutex = xSemaphoreCreateMutex();
  xTaskCreate(printTask, "Task1", 128, "Task1.....................", 1, NULL);
  xTaskCreate(printTask, "Task2", 128, "Task2.....................", 1, NULL);
  vTaskStartScheduler();
  Serial.println("Scheduler returned");
}
void loop()
{
}
