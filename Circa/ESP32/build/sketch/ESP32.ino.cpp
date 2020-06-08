#include <Arduino.h>
#line 1 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/ESP32.ino"
#if defined(ARDUINO) && ARDUINO >= 100
// No extras
#elif defined(ARDUINO) // pre-1.0
// No extras
#elif defined(ESP_PLATFORM)
#include "arduinoish.hpp"
#endif

// Led strip libs
#include <esp32_digital_led_lib.h>
#include <esp32_digital_led_funcs.h>

/// *** led strip settings ***///
#define COUNT_OF(x) ((sizeof(x) / sizeof(0 [x])) / ((size_t)(!(sizeof(x) % sizeof(0 [x])))))

// **Required** if debugging is enabled in library header
// TODO: Is there any way to put this in digitalLeds_addStrands() and avoid undefined refs?
#if DEBUG_ESP32_DIGITAL_LED_LIB
int digitalLeds_debugBufferSz = 1024;
char *digitalLeds_debugBuffer = static_cast<char *>(calloc(digitalLeds_debugBufferSz, sizeof(char)));
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers" // It's noisy here with `-Wall`

strand_t STRANDS[1] = {
    // Avoid using any of the strapping pins on the ESP32, anything >=32, 16, 17... not much left.
    {.rmtChannel = 0, .gpioNum = 14, .ledType = LED_SK6812W_V1, .brightLimit = 255, .numPixels = 60},
};

#pragma GCC diagnostic pop
int STRANDCNT = COUNT_OF(STRANDS);

float beforeBed_animDuration = 10.0; // seconds
float sunrise_animDuration = 6.0;    // seconds
float sunset_animDuration = 60.0;    // seconds

unsigned long sunrise_startTime;                                               // time to start sunrise in millis() -> from daily httpClient request
unsigned long beforeBed_startTime;                                             // time to start beforeBed (moment to prepare for sleep) in millis() -> from daily httpClient request
unsigned long sunset_startTime = beforeBed_startTime + beforeBed_animDuration; // directly after before bed indicatio

///*** current time settings ***///
// NTP server current time libs
#include <NTPClient.h>
#include <WiFiUdp.h>

const long utcOffsetInSeconds = 3600;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
int currentTime;

// WiFi libs
#include <WiFi.h>
#include <HTTPClient.h>

HTTPClient client;

///*** WiFi settings ***//
const char *ssid = "Lekker Wi-Fi bij Guerrero";
const char *password = "B4gels=L0ve";

// Json lib
#include <ArduinoJson.h>

///*** states ***///
bool isInBed = false;
bool wasInBed = false;

String inBedTimeRecord;
String outBedTimeRecord;

bool sendRecords = false;

///*** device ID ***///
int deviceId = 1;

//**************************************************************************//
#line 82 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/ESP32.ino"
void setup();
#line 106 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/ESP32.ino"
void loop();
#line 16 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/fansFunctions.ino"
void fansInit();
#line 37 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/fansFunctions.ino"
void fansOn();
#line 47 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/fansFunctions.ino"
void fansOff();
#line 57 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/fansFunctions.ino"
void setSpeed(int amount);
#line 30 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/httpRequests.ino"
String httpRequest(String request);
#line 54 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/httpRequests.ino"
bool httpSendRecords();
#line 74 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/httpRequests.ino"
void httpGetRecommended();
#line 89 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/httpRequests.ino"
int getHour(String time);
#line 90 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/httpRequests.ino"
int getMinutes(String time);
#line 91 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/httpRequests.ino"
int getSeconds(String time);
#line 93 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/httpRequests.ino"
String urlencode(String str);
#line 3 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/ledFunctions.ino"
void ledStripUpdate();
#line 3 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/ledInit.ino"
int getMaxMalloc(int min_mem, int max_mem);
#line 41 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/ledInit.ino"
void dumpSysInfo();
#line 55 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/ledInit.ino"
void dumpDebugBuffer(int id, char *debugBuffer);
#line 65 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/ledInit.ino"
bool initStrands();
#line 103 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/ledInit.ino"
void ledStripInit();
#line 1 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/ntpClientInit.ino"
void ntpClientInit();
#line 10 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/recordTimes.ino"
void btnLedInit();
#line 17 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/recordTimes.ino"
void btnPress();
#line 38 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/recordTimes.ino"
void setBedTimeRecords();
#line 82 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/ESP32.ino"
void setup()
{
  Serial.begin(115200);
  Serial.println("Initializing...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  // laat de verbinding met de server openstaan (als mogelijk)
  client.setReuse(true);

  ledStripInit();
  fansInit();
  ntpClientInit();
  btnLedInit();

  Serial.println("Init complete");
}

//**************************************************************************//
void loop()
{
  // find/reset led strip
  ledStripUpdate();

  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  currentTime = timeClient.getEpochTime();
  // Serial.println(String(timeClient.getHours()) + ":" + String(timeClient.getMinutes()) + ":" + String(timeClient.getSeconds()) );
  // Serial.println(currentTime);
  btnPress();
  setBedTimeRecords();
  if(sendRecords) {
    delay(10);
    if(httpSendRecords()) httpGetRecommended();
  }
  // beforeBed(STRANDS);
  //  sunrise(STRANDS);
}
//**************************************************************************//

#line 1 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/fansFunctions.ino"
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

#line 1 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/httpRequests.ino"
const char *ROOT_CA_CERT =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIDtzCCAp+gAwIBAgIQDOfg5RfYRv6P5WD8G/AwOTANBgkqhkiG9w0BAQUFADBl\n"
    "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
    "d3cuZGlnaWNlcnQuY29tMSQwIgYDVQQDExtEaWdpQ2VydCBBc3N1cmVkIElEIFJv\n"
    "b3QgQ0EwHhcNMDYxMTEwMDAwMDAwWhcNMzExMTEwMDAwMDAwWjBlMQswCQYDVQQG\n"
    "EwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3d3cuZGlnaWNl\n"
    "cnQuY29tMSQwIgYDVQQDExtEaWdpQ2VydCBBc3N1cmVkIElEIFJvb3QgQ0EwggEi\n"
    "MA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCtDhXO5EOAXLGH87dg+XESpa7c\n"
    "JpSIqvTO9SA5KFhgDPiA2qkVlTJhPLWxKISKityfCgyDF3qPkKyK53lTXDGEKvYP\n"
    "mDI2dsze3Tyoou9q+yHyUmHfnyDXH+Kx2f4YZNISW1/5WBg1vEfNoTb5a3/UsDg+\n"
    "wRvDjDPZ2C8Y/igPs6eD1sNuRMBhNZYW/lmci3Zt1/GiSw0r/wty2p5g0I6QNcZ4\n"
    "VYcgoc/lbQrISXwxmDNsIumH0DJaoroTghHtORedmTpyoeb6pNnVFzF1roV9Iq4/\n"
    "AUaG9ih5yLHa5FcXxH4cDrC0kqZWs72yl+2qp/C3xag/lRbQ/6GW6whfGHdPAgMB\n"
    "AAGjYzBhMA4GA1UdDwEB/wQEAwIBhjAPBgNVHRMBAf8EBTADAQH/MB0GA1UdDgQW\n"
    "BBRF66Kv9JLLgjEtUYunpyGd823IDzAfBgNVHSMEGDAWgBRF66Kv9JLLgjEtUYun\n"
    "pyGd823IDzANBgkqhkiG9w0BAQUFAAOCAQEAog683+Lt8ONyc3pklL/3cmbYMuRC\n"
    "dWKuh+vy1dneVrOfzM4UKLkNl2BcEkxY5NM9g0lFWJc1aRqoR+pWxnmrEthngYTf\n"
    "fwk8lOa4JiwgvT2zKIn3X/8i4peEH+ll74fg38FnSbNd67IJKusm7Xi+fT8r87cm\n"
    "NW1fiQG2SVufAQWbqz0lwcy2f8Lxb4bG+mRo64EtlOtCt/qMHt1i8b5QZ7dsvfPx\n"
    "H2sMNgcWfzd8qVttevESRmCD1ycEvkvOl77DZypoEd+A5wwzZr8TDRRu838fYxAe\n"
    "+o0bJW1sj6W3YQGx0qMmoRBxna3iw/nDmVG3KwcIzi7mULKn+gpFL6Lw8g==\n"
    "-----END CERTIFICATE-----\n";

int userId = 1;

String protocol = "https";
String host = "studenthome.hku.nl/~luuk.siewers/circa";

String httpRequest(String request)
{
    String url = protocol + "://" + host + "/esp32/" + request;

    client.begin(url,ROOT_CA_CERT);

    Serial.println("Send request...");
    Serial.println(url);
    int httpResultCode = client.GET();
    if (httpResultCode = HTTP_CODE_OK)
    {
        Serial.println(client.getString());
        return client.getString();
    }
    else
    {
        Serial.print("Error in request: code=");
        Serial.println(httpResultCode);
        delay(3000);
    }

    client.end();
}

bool httpSendRecords() {
    // create json object
    DynamicJsonDocument doc(2048);
    // mock data
    bool setInBedRecord = doc["inBedTimeRecord"].set("2020-06-05 23:23:21");
    bool setOutBedRecord = doc["outBedTimeRecord"].set("2020-06-06 10:21:34");
    bool setInBedRecommended = doc["inBedTimeRecommended"].set("2020-06-05 22:40:00");
    bool setOutBedRecommended = doc["outBedTimeRecommended"].set("2020-06-06 10:10:00");
    if(setInBedRecord && setOutBedRecord && setInBedRecommended && setOutBedRecommended) {
        String jsonStr;        
        serializeJson(doc, jsonStr);
        String request = String("set-records.php?deviceId=") + String(deviceId) + String("&data=") + urlencode(jsonStr);
        // Serial.println(request);
        // send json data in request
        return (bool)httpRequest(request);
    } else {
        Serial.println("set json data went wrong...");
    }
}

void httpGetRecommended() {
    String response = httpRequest("get-recommended.php?deviceId=" + String(deviceId));
    DynamicJsonDocument doc(256);   
    DeserializationError err = deserializeJson(doc, response);
    
    if (!err) {
        const int inBedTimeRecommended = doc["inBedTimeRecommended"];
        Serial.print("In bed at: ");
        Serial.println(inBedTimeRecommended);
    } else {
      Serial.println(F("JSON incorrect?"));
      Serial.println(err.c_str());
    }
}

int getHour(String time) { return time.substring(0,2).toInt(); }
int getMinutes(String time) { return time.substring(3,5).toInt(); }
int getSeconds(String time) { return time.substring(6,8).toInt(); }

String urlencode(String str)
{
    String encodedString="";
    char c;
    char code0;
    char code1;
    char code2;
    for (int i =0; i < str.length(); i++){
      c=str.charAt(i);
      if (c == ' '){
        encodedString+= '+';
      } else if (isalnum(c)){
        encodedString+=c;
      } else{
        code1=(c & 0xf)+'0';
        if ((c & 0xf) >9){
            code1=(c & 0xf) - 10 + 'A';
        }
        c=(c>>4)&0xf;
        code0=c+'0';
        if (c > 9){
            code0=c - 10 + 'A';
        }
        code2='\0';
        encodedString+='%';
        encodedString+=code0;
        encodedString+=code1;
        //encodedString+=code2;
      }
      yield();
    }
    return encodedString;
    
}
#line 1 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/ledFunctions.ino"
#include "ledVariables.h"

void ledStripUpdate() {
  strand_t * strands[1] = {&STRANDS[0]};
  digitalLeds_resetPixels(strands, STRANDCNT);
  int m1 = getMaxMalloc(1*1024, 16*1024*1024);
}

// void sunrise(strand_t ** strands) {
//   // led sunrise animation
//   if (currentTime >= sunrise_startTime && currentTime - sunrise_startTime <= sunrise_animDuration) {
//     float startTime;
//     if(!animation_active) {
//         startTime = millis();
//         Serial.println("sunset started");
//         animation_active = true;
//     }
//     strand_t * pStrand = strands[0]; // select only strip
//     sunrise_animProgress = map(millis() - startTime, 0, sunrise_animDuration * 1000, 0, sunrise_animPrecision);

//     if (sunrise_animProgress < sunrise_animPrecision - sunrise_animPrecision * sunrise_fullDuration) {
//       sunrise_activeStep = map(sunrise_animProgress, 0, sunrise_animPrecision - sunrise_animPrecision * sunrise_fullDuration, 0, sun_quarterStep * 2); 
//     } else sunrise_activeStep = sun_quarterStep * 2;
//     // sun led's
//     for(int i = 0; i <= round(sunrise_activeStep); i++) {
//       int sumIndex = sun_bottomCenter + i;
//       if(i > sun_quarterStep) {
//         sumIndex = sun_bottomCenter - sun_quarterStep * 3 + i - sun_quarterStep;
//       }
//       // i = 0 to sun_quarterStep
//       pStrand->pixels[sun_bottomCenter - i] = pixelFromRGBW(sunriseFadeColor("r", i), sunriseFadeColor("g", i), 0, sunriseFadeColor("w", i));
//       pStrand->pixels[sumIndex] = pixelFromRGBW(sunriseFadeColor("r", i), sunriseFadeColor("g", i), 0, sunriseFadeColor("w", i));
//     }
//     // top led's
//     for(int i = 0; i < sun_bottomCenter - 3 * sun_quarterStep; i++) {
//       pStrand->pixels[i] = pixelFromRGBW(sunriseFadeColor("r", i), sunriseFadeColor("g", i), 0, 0);
//     }
//     digitalLeds_drawPixels(strands, 1);
//   } else if (animation_active) animation_active = false;
// }

// // color fade in function
// uint8_t sunriseFadeColor(String rgbwColor, int i) {
//   float treshold = sunrise_animPrecision * sunrise_ledFadeInDuration;
//   // i (0 - quarterstep * 2), progress (0 - precision)
//   // precision / (quarterstep * 2) * i = i progress in precision
//   float thisProgressStart = (sunrise_animPrecision - sunrise_animPrecision * sunrise_fullDuration) / (sun_quarterStep * 2.0) * float(i);
//   float thisProgressEnd = thisProgressStart + treshold;
//   float fadeProgress;
//   uint8_t color;

//   // led not reached yet
//   if (sunrise_animProgress < thisProgressStart) fadeProgress = 0.0;
//   // led fading in
//   else if (sunrise_animProgress < thisProgressEnd) fadeProgress = map(sunrise_animProgress, thisProgressStart, thisProgressEnd, 0, sunrise_ledFadeInPrecision);
//   // led fade ended
//   else fadeProgress = sunrise_ledFadeInPrecision;

//   if(fadeProgress <= 0.0) {
//    if (rgbwColor == "r") color = uint8_t(0.0);
//    if (rgbwColor == "g") color = uint8_t(0.0);
//    if (rgbwColor == "w") color = uint8_t(0.0);
//   }
//   else if(fadeProgress < sunrise_ledFadeInPrecision/2) {
//    if (rgbwColor == "r") color = uint8_t(255.0/sunrise_ledFadeInPrecision/2*fadeProgress);
//    if (rgbwColor == "g") color = uint8_t(0.0);
//    if (rgbwColor == "w") color = uint8_t(0.0);
//   } else if(fadeProgress < sunrise_ledFadeInPrecision) {
//    if (rgbwColor == "r") color = uint8_t(255.0 - (155.0/(sunrise_ledFadeInPrecision/2)*(fadeProgress-sunrise_ledFadeInPrecision/2)));
//    if (rgbwColor == "g") color = uint8_t(30.0/(sunrise_ledFadeInPrecision/2)*(fadeProgress-sunrise_ledFadeInPrecision/2));
//    if (rgbwColor == "w") color = uint8_t(25.0/(sunrise_ledFadeInPrecision/2)*(fadeProgress-sunrise_ledFadeInPrecision/2));
//   }
//   else {
//    if (rgbwColor == "r") color = uint8_t(100.0);
//    if (rgbwColor == "g") color = uint8_t(30.0);
//    if (rgbwColor == "w") color = uint8_t(25.0);
//   }
  
//   return color;
// }
// ///*** end sunrise ***///

// ///*** before going to bed (time to adjust environment) ***///
// bool beforeBed(strand_t ** strands) {
//   if (currentTime >= beforeBed_startTime && currentTime - beforeBed_startTime <= beforeBed_animDuration) {
//     float startTime;
//     if(!animation_active) {
//         startTime = millis();
//         Serial.println("before bed indication started");
//         animation_active = true;
//     }
//     strand_t * pStrand = strands[0]; // select only strip
//     beforeBed_animProgress = map(millis() - startTime, 0, beforeBed_animDuration * 1000, 0, beforeBed_animPrecision);
//     Serial.println(beforeBed_animProgress);
//     for(int i = 0; i <= sun_quarterStep * 2; i++) {
//       int sumIndex = sun_bottomCenter + i;
//       if(i > sun_quarterStep) {
//         sumIndex = sun_bottomCenter - sun_quarterStep * 3 + i - sun_quarterStep;
//       }
//       // i = 0 to sun_quarterStep
//       pStrand->pixels[sun_bottomCenter - i] = pixelFromRGBW(fadeInColor("r", 100.0), fadeInColor("g", 30.0), 0, 0);
//       pStrand->pixels[sumIndex] = pixelFromRGBW(fadeInColor("r", 100.0), fadeInColor("g", 30.0), 0, 0);
//     }
//     digitalLeds_drawPixels(strands, 1);
//   } else if (animation_active) animation_active = false;
// }

// uint8_t fadeInColor(String rgbwColor, uint8_t value) {
//   uint8_t color;
//   if(currentTime - beforeBed_startTime <= fadeInDuration) {
//     float fadeProgress = map(currentTime - beforeBed_startTime, 0, fadeInDuration, 0, fadeInPrecision); // progress in percentage
//     Serial.println("Fade In Progress: " + String(fadeProgress));

//     if(fadeProgress < fadeInPrecision) {
//      if (rgbwColor == "r") color = uint8_t(map(fadeProgress, 0, fadeInPrecision, 0, value));
//      if (rgbwColor == "g") color = uint8_t(map(fadeProgress, 0, fadeInPrecision, 0, value));
//     }
//   } else {
//    if (rgbwColor == "r") color = uint8_t(value);
//    if (rgbwColor == "g") color = uint8_t(value);
//   }

//   return color;
// }

// ///*** sunset, directly after before bed indication ***///
// void sunset(strand_t ** strands) { // led sunrise animation
//   if (currentTime >= sunset_startTime && currentTime - sunset_startTime <= sunset_animDuration) {
//     float startTime;
//     if(!animation_active) {
//         startTime = millis();
//         Serial.println("sunset started"); 
//         animation_active = true;
//     }
//     strand_t * pStrand = strands[0]; // select only strip
//     sunset_animProgress = map(millis() - startTime, 0, sunset_animDuration * 1000, 0, sunset_animPrecision);

//     if (sunset_animProgress < sunset_animPrecision - sunset_animPrecision * sunset_fullDuration) {
//       sunset_activeStep = map(sunset_animProgress, 0, sunset_animPrecision - sunset_animPrecision * sunset_fullDuration, 0, sun_quarterStep * 2); 
//     } else sunset_activeStep = sun_quarterStep * 2;

//     int startingPoint = sun_bottomCenter - sun_quarterStep * 2;
//     for(int i = 0; i <= round(sunrise_activeStep); i++) {
//       int sumIndex = startingPoint - i;
//       if(i < startingPoint + sun_quarterStep) {
//         sumIndex = startingPoint + sun_quarterStep - i;
//       }
//       // i = 0 to sun_quarterStep
//       pStrand->pixels[startingPoint + i] = pixelFromRGBW(sunsetFadeColor("r", i), sunsetFadeColor("g", i), 0, 0);
//       pStrand->pixels[sumIndex] = pixelFromRGBW(sunsetFadeColor("r", i), sunsetFadeColor("g", i), 0, 0);
//     }
//     digitalLeds_drawPixels(strands, 1);
//   } else if (animation_active) animation_active = false;
// }

// // color fade out function
// uint8_t sunsetFadeColor(String rgbwColor, int i) {
//   float treshold = sunset_animPrecision * sunset_ledFadeOutDuration;
//   // i (0 - quarterstep * 2), progress (0 - precision)
//   // precision / (quarterstep * 2) * i = i progress in precision
//   float thisProgressStart = (sunset_animPrecision - sunset_animPrecision * sunset_fullDuration) / (sun_quarterStep * 2.0) * float(i);
//   float thisProgressEnd = thisProgressStart - treshold;
//   float fadeProgress;
//   uint8_t color;

//   // led not reached yet
//   if (sunset_animProgress < thisProgressStart) fadeProgress = 0.0;
//   // led fading in
//   else if (sunset_animProgress < thisProgressEnd) fadeProgress = map(sunset_animProgress, thisProgressStart, thisProgressEnd, 0, sunset_ledFadeOutPrecision);
//   // led fade ended
//   else fadeProgress = sunset_ledFadeOutPrecision;

//   if(fadeProgress <= 0.0) {
//    if (rgbwColor == "r") color = uint8_t(100.0);
//    if (rgbwColor == "g") color = uint8_t(30.0);
//   }
//   else if(fadeProgress < sunset_ledFadeOutPrecision) {
//    if (rgbwColor == "r") color = uint8_t(100.0 - (100.0/(sunset_ledFadeOutPrecision/2)*(fadeProgress-sunset_ledFadeOutPrecision/2)));
//    if (rgbwColor == "g") color = uint8_t(30.0 - 30.0/(sunset_ledFadeOutPrecision/2)*(fadeProgress-sunset_ledFadeOutPrecision/2));
//   }
//   else {
//    if (rgbwColor == "r") color = uint8_t(0.0);
//    if (rgbwColor == "g") color = uint8_t(0.0);
//   }
  
//   return color;
// }

#line 1 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/ledInit.ino"

//**************************************************************************//
int getMaxMalloc(int min_mem, int max_mem)
{
  int prev_size = min_mem;
  int curr_size = min_mem;
  int max_free = 0;
  //  Serial.print("checkmem: testing alloc from ");
  //  Serial.print(min_mem);
  //  Serial.print(" : ");
  //  Serial.print(max_mem);
  //  Serial.println(" bytes");
  while (1)
  {
    void *foo1 = malloc(curr_size);
    if (foo1 == nullptr)
    { // Back off
      max_mem = std::min(curr_size, max_mem);
      curr_size = (int)(curr_size - (curr_size - prev_size) / 2.0);
    }
    else
    { // Advance
      free(foo1);
      max_free = curr_size;
      prev_size = curr_size;
      curr_size = std::min(curr_size * 2, max_mem);
    }
    if (abs(curr_size - prev_size) == 0)
    {
      break;
    }
  }
  //  Serial.print("checkmem: max free heap = ");
  //  Serial.print(esp_get_free_heap_size());
  //  Serial.print(" bytes, max allocable = ");
  //  Serial.print(max_free);
  //  Serial.println(" bytes");
  return max_free;
}

void dumpSysInfo()
{
  esp_chip_info_t sysinfo;
  esp_chip_info(&sysinfo);
  Serial.print("Model: ");
  Serial.print((int)sysinfo.model);
  Serial.print("; Features: 0x");
  Serial.print((int)sysinfo.features, HEX);
  Serial.print("; Cores: ");
  Serial.print((int)sysinfo.cores);
  Serial.print("; Revision: r");
  Serial.println((int)sysinfo.revision);
}

void dumpDebugBuffer(int id, char *debugBuffer)
{
  Serial.print("DEBUG: (");
  Serial.print(id);
  Serial.print(") ");
  Serial.println(debugBuffer);
  debugBuffer[0] = 0;
}

//**************************************************************************//
bool initStrands()
{
  digitalLeds_initDriver();

  for (int i = 0; i < STRANDCNT; i++)
  {
    gpioSetup(STRANDS[i].gpioNum, OUTPUT, LOW);
  }

  strand_t *strands[8];
  for (int i = 0; i < STRANDCNT; i++)
  {
    strands[i] = &STRANDS[i];
  }
  int rc = digitalLeds_addStrands(strands, STRANDCNT);
  if (rc)
  {
    Serial.print("Init rc = ");
    Serial.println(rc);
    return false;
  }

  for (int i = 0; i < STRANDCNT; i++)
  {
    strand_t *pStrand = strands[i];
    Serial.print("Strand ");
    Serial.print(i);
    Serial.print(" = ");
    Serial.print((uint32_t)(pStrand->pixels), HEX);
    Serial.println();
#if DEBUG_ESP32_DIGITAL_LED_LIB
    dumpDebugBuffer(-2, digitalLeds_debugBuffer);
#endif
  }

  return true;
}

void ledStripInit()
{
  dumpSysInfo();
  getMaxMalloc(1 * 1024, 16 * 1024 * 1024);

  if (!initStrands())
  {
    Serial.println("Init FAILURE: halting");
    while (true)
    {
      delay(100);
    }
  }
  delay(100);
}
#line 1 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/ntpClientInit.ino"
void ntpClientInit()
{
    timeClient.begin();
    timeClient.update();
    // currentTime = timeClient.getSeconds() + timeClient.getMinutes() * 60 + timeClient.getHours() * 3600;
    Serial.println(timeClient.getEpochTime());
    //  Serial.println(currentTime);
    // beforeBed_startTime = currentTime + 5;
}
#line 1 "/Users/luuksiewers/Developer/PlatformIO/Projects/KM4/Circa/ESP32/recordTimes.ino"
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
