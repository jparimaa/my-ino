#include <Arduino_FreeRTOS.h>
#include <queue.h>

const int c_redPin = 2;
const int c_greenPin = 3;
const int c_bluePin = 4;
const int c_yellowPin = 5;

int ledStatus[4] = {0, 0, 0, 0};
QueueHandle_t myQueue;

void senderTask(void* /*pvParameters*/)
{
  while (true)
  {
    const int togglePin = random(c_redPin, c_yellowPin + 1);
    xQueueSendToBack(myQueue, &togglePin, 0);
    const TickType_t delayMs = pdMS_TO_TICKS(random(500, 1000));
    vTaskDelay(delayMs);
  }
}

void receiverTask(void* /*pvParameters*/)
{
  while (true)
  {
    int togglePin;
    xQueueReceive(myQueue, &togglePin, portMAX_DELAY);
    int ledIndex = togglePin - 2;
    int toggledValue = (ledStatus[ledIndex] + 1) % 2;
    ledStatus[ledIndex] = toggledValue;
    digitalWrite(togglePin, toggledValue);
  }
}

void setup()
{
  Serial.begin(9600);
  for (int i = c_redPin; i <= c_yellowPin; ++i)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

  myQueue = xQueueCreate(5, sizeof(int));
  if (myQueue == NULL)
  {
    Serial.println("Could not create queue");
    return;
  }
  Serial.println("Queue created");

  xTaskCreate(senderTask, "Sender1", 128, NULL, 1, NULL);
  Serial.println("Sender 1 created");
  xTaskCreate(senderTask, "Sender2", 128, NULL, 1, NULL);
  Serial.println("Sender 2 created");
  xTaskCreate(receiverTask, "Receiver", 128, NULL, 2, NULL);
  Serial.println("Receiver created");
  Serial.println("Starting scheduler...");
  vTaskStartScheduler();
}

void loop()
{
}
