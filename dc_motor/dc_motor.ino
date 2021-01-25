const int c_controlPin1 = 2;
const int c_controlPin2 = 3;
const int c_enablePin = 9;
const int c_directionSwitchPin = 4;
const int c_onOffSwitchPin = 5;
const int c_potPin = A0;

int onOffSwitchState = 0;
int prevOnOffSwitchState = 0;
int directionSwitchState = 0;
int prevDirectionSwitchState = 0;

int motorEnabled = 0;
int motorSpeed = 0;
int motorDirection = 0;

void setup()
{
  pinMode(c_directionSwitchPin, INPUT);
  pinMode(c_onOffSwitchPin, INPUT);
  pinMode(c_controlPin1, OUTPUT);
  pinMode(c_controlPin2, OUTPUT);
  pinMode(c_enablePin, OUTPUT);
  digitalWrite(c_enablePin, LOW);
}

void loop()
{
  onOffSwitchState = digitalRead(c_onOffSwitchPin);
  delay(1);
  directionSwitchState = digitalRead(c_directionSwitchPin);

  motorSpeed = analogRead(c_potPin) / 4;

  if (onOffSwitchState != prevOnOffSwitchState && onOffSwitchState == HIGH)
  {
    motorEnabled = !motorEnabled;
  }
  if (directionSwitchState != prevDirectionSwitchState && directionSwitchState == HIGH)
  {
    motorDirection = !motorDirection;
  }

  if (motorDirection == 1)
  {
    digitalWrite(c_controlPin1, HIGH);
    digitalWrite(c_controlPin2, LOW);
  }
  else
  {
    digitalWrite(c_controlPin1, LOW);
    digitalWrite(c_controlPin2, HIGH);
  }

  analogWrite(c_enablePin, motorEnabled == 1 ? motorSpeed : 0);

  prevOnOffSwitchState = onOffSwitchState;
  prevDirectionSwitchState = directionSwitchState;
}
