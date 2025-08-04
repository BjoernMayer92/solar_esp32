const int analogPin=36;
#include "config.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <string.h>
#include <time.h>

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 0;
String url = String("http://")+SERVER_IP+String(":")+SERVER_PORT+String("/solar");


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10000);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println(WiFi.localIP());

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

String getLocalTimeString() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return "N/A";
  }
  char timestring[80];
  strftime(timestring, sizeof(timestring), "%Y-%m-%d %H:%M:%S", &timeinfo);
  return String(timestring);
}

void loop() {
  int adcValue = analogRead(analogPin);
  float voltage = adcValue*3.3/4095.0;
  HTTPClient http;
  
  http.begin(url);
  http.addHeader("Content-Type", "application/json");

  
  String timestring = getLocalTimeString();
  Serial.println(timestring);
  Serial.printf("ADC Value: %d, Voltage: %.3f V\n", adcValue, voltage);

  Serial.println(url);
  String jsonData = String("{\"Time\": \") + timestring +String(\", \"Voltage\":")+String(voltage)+String("}");
  int httpResponseCode = http.POST(jsonData);

  Serial.println(jsonData);
  Serial.println(String(httpResponseCode));
  http.end(); 
  delay(5000);  
  // put your main code here, to run repeatedly:

}
