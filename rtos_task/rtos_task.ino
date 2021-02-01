#include <Arduino_FreeRTOS.h>

const int c_redPin = 2;
const int c_greenPin = 3;
const int c_bluePin = 4;
const int c_yellowPin = 5;

const TickType_t c_delay3000ms = pdMS_TO_TICKS(3000);
const TickType_t c_delay2000ms = pdMS_TO_TICKS(2000);

void setAllLedsOff()
{
  for (int i = c_redPin; i <= c_yellowPin; ++i)
  {
    digitalWrite(i, LOW);
  }
}

void blinkRed(void * /*pvParameters*/)
{
  while (true)
  {
    setAllLedsOff();
    digitalWrite(c_redPin, HIGH);
    delay(200);
    setAllLedsOff();
    vTaskDelay(c_delay3000ms);
  }
}

void enableGreen(void * /*pvParameters*/)
{
  while (true)
  {
    digitalWrite(c_greenPin, HIGH);
    vTaskDelay(c_delay2000ms);
  }
}

void setup()
{
  pinMode(c_redPin, OUTPUT);
  pinMode(c_greenPin, OUTPUT);
  pinMode(c_bluePin, OUTPUT);
  pinMode(c_yellowPin, OUTPUT);
  digitalWrite(c_redPin, LOW);
  digitalWrite(c_greenPin, LOW);
  digitalWrite(c_bluePin, LOW);
  digitalWrite(c_yellowPin, LOW);

  xTaskCreate(blinkRed, "blinkRed", 128, NULL, 1, NULL);
  xTaskCreate(enableGreen, "enableGreen", 128, NULL, 0, NULL);
  vTaskStartScheduler();
}

void loop()
{
}
