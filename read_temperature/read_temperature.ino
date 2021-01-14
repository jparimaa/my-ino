const int c_temperatureSensorPin = A0;
const float c_temperatureAtZeroVoltage = -50.0f;
const float c_voltageToCelsius = 100.0f;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int sensorValue = analogRead(c_temperatureSensorPin);
  Serial.print("Sensor value: ");
  Serial.print(sensorValue);
  const float sensorValueVoltage = (sensorValue / 1024.0f) * 5.0f;
  Serial.print(", voltage: ");
  Serial.print(sensorValueVoltage);
  const float temperature = c_temperatureAtZeroVoltage + (sensorValueVoltage * c_voltageToCelsius);
  Serial.print(", temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
  delay(1000);
}
