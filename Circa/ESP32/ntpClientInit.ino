void ntpClientInit()
{
    timeClient.begin();
    timeClient.update();
    // Covert time to seconds, so I can compare them to other time variables
    currentTime = timeClient.getSeconds() + timeClient.getMinutes() * 60 + timeClient.getHours() * 3600;
    Serial.println(timeClient.getFormattedTime());
    Serial.println(currentTime);
    // beforeBed_startTime = currentTime + 5;
}