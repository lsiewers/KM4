#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include "ESP32.h"

String NETWORK_NAME = "Lekker Wi-Fi bij Guerrero";
String NETWORK_PASSWORD = "B4gels=L0ve";

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  delay(5000);

  connectWiFi();
}

// the loop function runs over and over again forever
void loop() {
  HTTPClient client;

  String protocol = "https";
  String host = "km4.mobidapt.com";
  String request = "/time.php";

  String url = protocol + "://" + host + request;

  client.begin(url);
  int httpResultCode = client.GET();
  
  if (httpResultCode == HTTP_CODE_OK) {
    Serial.print(httpResultCode);
    String response = client.getString();
    Serial.println(" " + response);
    delay(2000);
  } else {
    Serial.println("error! ");
    Serial.println(httpResultCode);
    delay(3000);
  }

  client.end();

}
