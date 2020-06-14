// We assigned a name LED pin to pin number 23
const int LedPin = 23; 
// this will assign the name PushButton to pin numer 15
const int BtnPin = 15;

bool btnPressed = false;
unsigned long btnPressTimeOutDuration = 3000.0; // minimal time between in bed/out bed
unsigned long btnPressedTime = 0.0;

void btnLedInit() {
  // This statement will declare pin 22 as digital output 
  pinMode(LedPin, OUTPUT);
  // This statement will declare pin 15 as digital input 
  pinMode(BtnPin, INPUT);
     digitalWrite(LedPin, HIGH);
}

// set LED and isInBed variable based on button press
void btnPress() {
    int btnVal = digitalRead(BtnPin);
    btnPressed = (millis() - btnPressedTime < btnPressTimeOutDuration);

    if(btnVal == LOW) {
        Serial.println("press!!!");
        if (!btnPressed) {
            btnPressedTime = millis();
            isInBed = !isInBed;
            if(isInBed) {
                digitalWrite(LedPin, LOW);
            } else {
                digitalWrite(LedPin, HIGH);
            } 
        }
    }
}

// find out if is in bed or not and set
void setBedTimeRecords()
{
    sendRecords = false;
    if (!wasInBed && isInBed)
    {
        inBedTimeRecord = currentTime;
        wasInBed = true;
        Serial.println("Good night");
        inBedTimeRecord = getFullFormattedTime();
        // Serial.println("In bed at: " + inBedTimeRecord);
    }
    else if (wasInBed && !isInBed)
    {
        outBedTimeRecord = currentTime;
        wasInBed = false;
        // Serial.println("Out of bed at: " + outBedTimeRecord);
        Serial.println("Good morning");
        outBedTimeRecord = getFullFormattedTime();
        sendRecords = true;
    }
}

String getFullFormattedTime() {
   time_t rawtime = timeClient.getEpochTime();
   struct tm * ti;
   ti = localtime (&rawtime);

   uint16_t year = ti->tm_year + 1900;
   String yearStr = String(year);

   uint8_t month = ti->tm_mon + 1;
   String monthStr = month < 10 ? "0" + String(month) : String(month);

   uint8_t day = ti->tm_mday;
   String dayStr = day < 10 ? "0" + String(day) : String(day);

   uint8_t hours = ti->tm_hour;
   String hoursStr = hours < 10 ? "0" + String(hours) : String(hours);

   uint8_t minutes = ti->tm_min;
   String minuteStr = minutes < 10 ? "0" + String(minutes) : String(minutes);

   uint8_t seconds = ti->tm_sec;
   String secondStr = seconds < 10 ? "0" + String(seconds) : String(seconds);

   return yearStr + "-" + monthStr + "-" + dayStr + " " +
          hoursStr + ":" + minuteStr + ":" + secondStr;
}