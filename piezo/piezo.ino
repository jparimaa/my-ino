const unsigned int A = 440;
const unsigned int B = 494;
const unsigned int D = 587;
const unsigned int E = 659;
const int delayTime = 120;

const int red = 5;
const int green = 4;
const int blue = 3;
int currentLed = red;

void playNote(int note, int count, int playTimeMs)
{
  for (int i = 0; i < count; ++i)
  {
    tone(8, note, playTimeMs);
    delay(delayTime);
  }
}

void playBSeries()
{
  playNote(B, 4, 10);
  playNote(B, 1, 20);
  playNote(B, 6, 10);
  playNote(B, 1, 20);
}

void playESeries()
{
  playNote(E, 6, 10);
  playNote(E, 1, 20);
}

void playDSeries()
{
  playNote(D, 6, 10);
  playNote(D, 1, 20);
}

void toggleNextLedOn()
{
  currentLed += 1;
  currentLed = currentLed == 6 ? 3 : currentLed;
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(currentLed, HIGH);
}

void setup()
{
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop()
{
  toggleNextLedOn();
  playBSeries();
  toggleNextLedOn();
  playESeries();
  toggleNextLedOn();
  playDSeries();
  toggleNextLedOn();
  playNote(A, 2, 10);
  toggleNextLedOn();
  playBSeries();
  toggleNextLedOn();
  playNote(E, 2, 10);
  toggleNextLedOn();
  playBSeries();
  toggleNextLedOn();
  playNote(E, 2, 10);
  toggleNextLedOn();
  playBSeries();
  toggleNextLedOn();
  playESeries();
  toggleNextLedOn();
  playDSeries();
  toggleNextLedOn();
  playNote(A, 2, 10);
  toggleNextLedOn();
  playBSeries();
  toggleNextLedOn();
  playNote(E, 2, 10);
  toggleNextLedOn();
  playBSeries();
}
