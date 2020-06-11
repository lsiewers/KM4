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

int beforeBed_animDuration = 1800; // seconds (30 minutes)
int sunrise_animDuration = 1800;    // 30 minutes in seconds
int sunset_animDuration = 1800;    // 30 minutes in seconds

int sunrise_startTime; // time to start sunrise in millis() -> from daily httpClient request
int sunset_startTime; // directly after before bed indicatio
int beforeBed_startTime; // time to start beforeBed (moment to prepare for sleep) in millis() -> from daily httpClient request

///*** current time settings ***///
// NTP server current time libs
#include <NTPClient.h>
#include <WiFiUdp.h>

const long utcOffsetInSeconds = 7200;

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

String inBedTimeRecommended;
String outBedTimeRecommended;
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
  httpGetRecommended();
  
  // Test animations after start-up
//  sunrise_startTime = currentTime;
  // beforeBed_startTime = currentTime;
  //  sunset_startTime = currentTime;

  Serial.println("Init complete");
}

//**************************************************************************//
void loop()
{
  strand_t * strands [STRANDCNT];
  for (int i = 0; i < STRANDCNT; i++) {
    strands[i] = &STRANDS[i];
  }
  while(!timeClient.update()) timeClient.forceUpdate();
  // find/reset led strip
  ledStripUpdate();
  currentTime = timeClient.getHours() * 3600 + timeClient.getMinutes() * 60 + timeClient.getSeconds();
  // Serial.println(currentTime);
  btnPress();
  setBedTimeRecords();
  if(sendRecords) {
    delay(10);
    httpSendRecords();
  }
  if(currentTime == (12 * 3600)) httpGetRecommended(); // if it's 12:00:00, get new recommended times
  beforeBed(strands); // if it's time to prepare
  // sunset(strands); // if it's time to go to bed
  sunrise(strands); // if it's time to go to bed
}
//**************************************************************************//
