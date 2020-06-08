#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
 b
#include "ESP32.h"

HTTPClient client;

#define BUTTON_PIN 18
#define NETWORK_NAME "Lekker Wi-Fi bij Guerrero"
#define NETWORK_PASSWORD "B4gels=L0ve"

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  delay(5000);

  connectWiFi();

  pinMode(BUTTON_PIN, INPUT_PULLDOWN);

  client.setReuse(true);
}

// the loop function runs over and over again forever
void loop() {
  String protocol = "https";
  String host = "km4.mobidapt.com";
  String request = "/lights.php?userid=luuk&lightid=light1&colour=";

  int buttonPressed = digitalRead(BUTTON_PIN);

  if(buttonPressed) {
    request += "red";
  } else {
    request += "green";
  }

  String url = protocol + "://" + host + request;
  Serial.println(url);
  client.begin(url);

  int resultCode = client.GET();
  if(resultCode == HTTP_CODE_OK) {
    String response = client.getString();
    Serial.println(response);
  } else {
    String error = client.getString();
    Serial.println(error);
  }

  client.end();

  delay(1000);
}
