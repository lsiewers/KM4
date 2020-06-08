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
