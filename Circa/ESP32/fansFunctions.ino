///*** fan settings ***///
// fan A
int enable1Pin = 27;
int fan1Pin1 = 26;
int fan1Pin2 = 25;
// fan B
int fan2Pin1 = 19;
int fan2Pin2 = 18;
int enable2Pin = 21;

// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 1;
const int resolution = 8;

void fansInit()
{
  // sets the pins as outputs:
  pinMode(fan1Pin1, OUTPUT);
  pinMode(fan1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  // sets the pins as outputs:
  pinMode(fan2Pin1, OUTPUT);
  pinMode(fan2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);

  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable2Pin, pwmChannel);
  ledcWrite(pwmChannel, 255);
}

void fansOn()
{
  digitalWrite(enable1Pin, LOW); // see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN
  digitalWrite(enable2Pin, LOW);
  digitalWrite(fan1Pin1, LOW);
  digitalWrite(fan1Pin2, HIGH);
  digitalWrite(fan2Pin1, LOW);
  digitalWrite(fan2Pin2, HIGH);
}

void fansOff()
{
  digitalWrite(enable1Pin, LOW); // see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN
  digitalWrite(enable2Pin, LOW);
  digitalWrite(fan1Pin1, LOW);
  digitalWrite(fan1Pin2, LOW);
  digitalWrite(fan2Pin1, LOW);
  digitalWrite(fan2Pin2, LOW);
}

void setSpeed(int amount)
{
  if (amount <= 255)
  {
    ledcWrite(pwmChannel, amount);
  }
}
