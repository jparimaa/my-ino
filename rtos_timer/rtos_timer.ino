#include <Arduino_FreeRTOS.h>
#include <timers.h>
#include <task.h>

const int c_redPin = 2;
const int c_greenPin = 3;
const int c_bluePin = 4;
const int c_yellowPin = 5;

struct ToggleData
{
  int pin;
  int enabled;
};

void lightToggler(TimerHandle_t handle)
{
  Serial.println("Executing toggler timer");
  ToggleData *data = (ToggleData *)pvTimerGetTimerID(handle);
  digitalWrite(data->pin, data->enabled);
}

void timerCreator(void * /*pvParameters*/)
{
  const TickType_t frequency = pdMS_TO_TICKS(1000);

  ToggleData enableData{0, HIGH};
  ToggleData disableData{0, LOW};

  TimerHandle_t onTimer = xTimerCreate("OnTimer", pdMS_TO_TICKS(200), 0, (void *)&enableData, lightToggler);
  TimerHandle_t offTimer = xTimerCreate("OffTimer", pdMS_TO_TICKS(500), 0, (void *)&disableData, lightToggler);

  while (true)
  {
    Serial.println("Executing toggler task");

    const int pin = random(c_redPin, c_yellowPin + 1);
    enableData.pin = pin;
    disableData.pin = pin;
    xTimerStart(onTimer, 10);
    xTimerStart(offTimer, 10);
    vTaskDelay(frequency);
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

  xTaskCreate(timerCreator, "TimerCreator", 512, NULL, 1, NULL);
  Serial.println("Task created");
  Serial.println("Starting scheduler...");
  vTaskStartScheduler();
}

void loop()
{
}
