#include <Arduino_FreeRTOS.h>
#include <semphr.h>

const int c_switchPin = 2;

const int c_greenPin = 3;
const int c_bluePin = 4;
const int c_yellowPin = 5;
const int c_redPin = 6;

int currentPinInUse = c_redPin;

SemaphoreHandle_t binarySemaphore = NULL;

void ledChangerTask(void * /*pvParameters*/)
{
  /* Take the newly created semaphore so it doesn't block */
  xSemaphoreTake(binarySemaphore, 0);
  Serial.println("ledChangerTask started");

  while (true)
  {
    xSemaphoreTake(binarySemaphore, portMAX_DELAY);
    currentPinInUse += 1;
    if (currentPinInUse > c_redPin)
    {
      currentPinInUse = c_greenPin;
    }
    for (int i = c_greenPin; i <= c_redPin; ++i)
    {
      digitalWrite(i, LOW);
    }
  }
}

void interruptHandler(void)
{
  Serial.println("Interrupt");

  /*
    portYIELD_FROM_ISR wasn't available so skip it

    static signed portBASE_TYPE higherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR( binarySemaphore, (signed portBASE_TYPE*)&higherPriorityTaskWoken );
    portYIELD_FROM_ISR(higherPriorityTaskWoken);
  */
  xSemaphoreGiveFromISR(binarySemaphore, NULL);
}

void blinkLed(void * /*pvParameters*/)
{
  Serial.println("blinkLed started");
  while (true)
  {
    digitalWrite(currentPinInUse, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(currentPinInUse, LOW);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void setup()
{
  Serial.begin(9600);

  for (int i = c_greenPin; i <= c_redPin; ++i)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  pinMode(c_switchPin, INPUT);

  binarySemaphore = xSemaphoreCreateBinary();
  if (binarySemaphore == NULL)
  {
    return;
  }
  Serial.println("Semaphore created");

  xTaskCreate(ledChangerTask, "ledChangerTask", 64, NULL, 3, NULL);
  Serial.println("ledChangerTask created");
  xTaskCreate(blinkLed, "blinkLed", 64, NULL, 1, NULL);
  Serial.println("blinkLed created");
  attachInterrupt(digitalPinToInterrupt(c_switchPin), interruptHandler, RISING);
  Serial.println("Interrupt attached");
  Serial.println("Starting scheduler...");
  vTaskStartScheduler();
  Serial.println("Scheduler returned");
}

void loop()
{
}
