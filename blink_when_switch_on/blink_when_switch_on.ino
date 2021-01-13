int switchState = 0;
const int c_green = 3;
const int c_red1 = 4;
const int c_red2 = 5;
int red1Enabled = LOW;

int getOpposite(int status)
{
  return status == LOW ? HIGH : LOW;
}

void setup() {
  pinMode(c_green, OUTPUT);
  pinMode(c_red1, OUTPUT);
  pinMode(c_red2, OUTPUT);
  pinMode(2, INPUT);
}

void loop() {
  switchState = digitalRead(2);
  if (switchState == LOW)
  {
    digitalWrite(c_green, LOW);
    digitalWrite(c_red1, HIGH);
    digitalWrite(c_red2, HIGH);
  }
  else
  {
    digitalWrite(c_green, HIGH);
    
    const int red1Toggled = getOpposite(red1Enabled);
    digitalWrite(c_red1, red1Enabled);
    digitalWrite(c_red2, red1Toggled);
    red1Enabled = red1Toggled;
  }
  delay(250);
}
