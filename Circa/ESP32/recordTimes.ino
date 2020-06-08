// We assigned a name LED pin to pin number 22
const int LedPin = 23; 
// this will assign the name PushButton to pin numer 15
const int BtnPin = 34;

bool btnPressed = false;
unsigned long btnPressTimeOutDuration = 3000.0; // minimal time between in bed/out bed
unsigned long btnPressedTime = 0.0;

void btnLedInit() {
  // This statement will declare pin 22 as digital output 
  pinMode(LedPin, OUTPUT);
  // This statement will declare pin 15 as digital input 
  pinMode(BtnPin, INPUT);
}

void btnPress() {
    int btnVal = digitalRead(BtnPin);
    btnPressed = (millis() - btnPressedTime < btnPressTimeOutDuration);

    if(btnVal == LOW) {
        if (!btnPressed) {
            btnPressedTime = millis();
            isInBed = !isInBed;
            if(isInBed) {
                digitalWrite(LedPin, LOW);
                Serial.println("Good night");
            } else {
                digitalWrite(LedPin, HIGH);
                Serial.println("Good morning");
            } 
        }
    }
}



void setBedTimeRecords()
{
    sendRecords = false;
    if (!wasInBed && isInBed)
    {
        inBedTimeRecord = currentTime;
        wasInBed = true;
        // Serial.println("In bed at: " + inBedTimeRecord);
    }
    else if (wasInBed && !isInBed)
    {
        outBedTimeRecord = currentTime;
        wasInBed = false;
        // Serial.println("Out of bed at: " + outBedTimeRecord);
        sendRecords = true;
    }
}