/*
  The code is pretty simple. It reads the value from the soil moisture sensor, calculates the percentage of moisture, and publishes it to the MQTT broker. 
  The  .env  file is used to store the sensitive information like the WiFi SSID, password, MQTT server, user, and password.

  On other branch of project, we have code with async server installed on ESP8266, but I resigned from it, because it was too much power consuming.

  Author: Paweł Szlendak
  Github: https://github.com/shlendakh
  License: MIT (c) 2024
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define SOIL_MOISTURE_PIN A0

// Change in the .env file
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

const char *mqtt_server = MQTT_SERVER;
const char *mqtt_user = MQTT_USER;
const char *mqtt_password = MQTT_PASSWORD;
const char *mqtt_topic = MQTT_TOPIC;

WiFiClient espClient;
PubSubClient client(espClient);

#define SOIL_MOISTURE_PIN A0

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
  float moisturePercent = 100 * (1 - (soilMoistureValue / 1023.0));

  char msg[50];
  snprintf(msg, 50, "{\"moisture\": %.2f}", moisturePercent);
  Serial.print("Publishing: ");
  Serial.println(msg);
  client.publish(mqtt_topic, msg);

  delay(5000);
}