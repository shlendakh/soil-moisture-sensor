#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

#define SOIL_MOISTURE_PIN A0

// Change in the .env file
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

AsyncWebServer server(80);  // Server instance

// Function to read a file from LittleFS
String readFile(fs::FS &fs, const char * path) {
  File file = fs.open(path, "r");
  if(!file || file.isDirectory()) {
    Serial.println("- failed to open file for reading");
    return String();
  }
  
  String fileContent;
  while(file.available()) {
    fileContent += String((char)file.read());
  }
  file.close();
  return fileContent;
}

void setup() {
  Serial.begin(115200);
  pinMode(SOIL_MOISTURE_PIN, INPUT);

  // Initialize LittleFS
  if (!LittleFS.begin()) {
    Serial.println("Error mounting LittleFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // Serve HTML file
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = readFile(LittleFS, "/index.html");
    //String html = "<html><head><title>Test</title></head><body><p>Test2</p></body></html>";
    request->send(200, "text/html", html);
  });

  server.on("/percents", HTTP_GET, [](AsyncWebServerRequest *request) {
    int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
    float moisturePercent = 100 * (1 - (soilMoistureValue / 1023.0));

    request->send(200, "text/plain", String(moisturePercent));
  });

  server.serveStatic("/assets/", LittleFS, "/assets/");

  server.begin();
}

void loop() {
  // Do nothing here
}