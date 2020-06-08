void ntpClientInit()
{
    timeClient.begin();
    timeClient.update();
    // currentTime = timeClient.getSeconds() + timeClient.getMinutes() * 60 + timeClient.getHours() * 3600;
    Serial.println(timeClient.getEpochTime());
    //  Serial.println(currentTime);
    // beforeBed_startTime = currentTime + 5;
}