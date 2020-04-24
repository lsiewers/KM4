#include <WiFi.h>
#include <Ticker.h>

Ticker blinkLed;

#define NETWORK_NAME "Lekker Wi-Fi bij Guerrero"
#define NETWORK_PASSWORD "B4gels=L0ve"

void toggleLED() {
  digitalWrite(LED_BUILTIN, !(digitalRead(LED_BUILTIN)));
}

void connectWiFi() {
  delay(2000); // geef de ESP tijd om op te starten

  // laat het blauwe ledje knipperen zolang WiFi nog niet verbonden is
  pinMode(LED_BUILTIN, OUTPUT);
  blinkLed.attach(0.1, toggleLED);
  
  WiFi.begin(NETWORK_NAME, NETWORK_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Verbinden met netwerk " NETWORK_NAME);
    delay(1000);
  }

  // knipperen van LEDje uit
  blinkLed.detach();
  digitalWrite(LED_BUILTIN, LOW);

  Serial.println("Succes! Verbonden met netwerk " NETWORK_NAME);

  // check wat voor IP adres we gekregen hebben
  Serial.print("Mijn IP adres: ");
  Serial.println(WiFi.localIP());
  
  // toon 't MAC (hardware) adres
  Serial.print("Mijn MAC adres: ");
  Serial.println(WiFi.macAddress());
}