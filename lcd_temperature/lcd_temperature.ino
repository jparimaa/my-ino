#include <LiquidCrystal.h>
#include <stdlib.h>

const int c_temperatureSensorPin = A0;
const float c_temperatureAtZeroVoltage = -50.0;
const float c_voltageToCelsius = 100.0;

const int c_numReadings = 20;
const int c_displayWidth = 16;

float latestReadings[c_numReadings];
int readingIndex = 0;
bool hasEnoughReadings = false;
char temperatureStr[c_displayWidth];
float prevAvgTemperature = 0.0f;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void updateReadings(float f)
{
  latestReadings[readingIndex] = f;
  ++readingIndex;
  if (readingIndex == c_numReadings)
  {
    hasEnoughReadings = true;
  }
  readingIndex = readingIndex % c_numReadings;
}

float getReadingsAverage()
{
  float f = 0.0f;
  for (int i = 0; i < c_numReadings; ++i)
  {
    f += latestReadings[i];
  }
  f /= c_numReadings;
  return f;
}

void floatToTemperatureString(float f, char *str)
{
  dtostrf(f, 0, 1, str);
  strcat(str, " C");
}

bool almostEqual(float a, float b)
{
  return (a < (b + 0.1f)) && (a > (b - 0.1f));
}

void setup()
{
  lcd.begin(16, 2);
  lcd.print("Measuring...");
  Serial.begin(9600);
}

void loop()
{
  int sensorValue = analogRead(c_temperatureSensorPin);
  const float sensorValueVoltage = (sensorValue / 1024.0) * 5.0;
  const float temperature = c_temperatureAtZeroVoltage + (sensorValueVoltage * c_voltageToCelsius);

  Serial.print("Sensor value: ");
  Serial.print(sensorValue);
  Serial.print(", voltage: ");
  Serial.print(sensorValueVoltage);
  Serial.print(", temperature: ");
  Serial.print(temperature);
  Serial.print("°C");
  Serial.print(" -> ");
  Serial.println(temperatureStr);

  updateReadings(temperature);

  if (hasEnoughReadings)
  {
    const float avgTemperature = getReadingsAverage();
    if (!almostEqual(avgTemperature, prevAvgTemperature))
    {
      prevAvgTemperature = avgTemperature;
      memset(temperatureStr, 0, c_displayWidth);
      floatToTemperatureString(avgTemperature, temperatureStr);
      lcd.clear();
      lcd.print(temperatureStr);
    }
  }

  delay(500);
}
