/**
* Sample Code HTTP IoT
* Modify by :
*           Devandri Suherman (23225027)
*           Bandung, 17-02-2026
* Copyright 2026
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* serverUrl = "https://iutnhicoaxuutefmdbzn.supabase.co/functions/v1/iot-devices";
const char* deviceId = "c849899f-d0d9-4168-aa6e-cf63c593a2d6";

unsigned long lastTime = 0;
const unsigned long timerDelay = 10000; 
bool isConnected = false;

void setup() {
  Serial.begin(115200);
  delay(1000);

  //Scan WiFi
  Serial.println("\n--- WiFi Scanner ---");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  int n = WiFi.scanNetworks();
  if (n == 0) {
    Serial.println("No networks found.");
  } else {
    Serial.printf("%d networks found:\n", n);
    Serial.println("Nr | SSID                             | RSSI | Encryption");
    for (int i = 0; i < n; ++i) {
      Serial.printf("%2d | %-32.32s | %4ld | %s\n", 
                    i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i), 
                    (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "Open" : "Secured");
    }
  }
  WiFi.scanDelete();

  //Input SSID dan Password dari Serial Monitor
  Serial.println("\n--- Masukkan Kredensial ---");
  Serial.println("Format: SSID,password");
  Serial.println("(Contoh: MyWiFi,12345678)");
  
  while (!isConnected) {
    if (Serial.available() > 0) {
      String input = Serial.readStringUntil('\n');
      input.trim(); 

      int commaIndex = input.indexOf(',');
      if (commaIndex > 0) {
        String inputSSID = input.substring(0, commaIndex);
        String inputPass = input.substring(commaIndex + 1);

        Serial.printf("\nMencoba terhubung ke: %s...\n", inputSSID.c_str());
        WiFi.begin(inputSSID.c_str(), inputPass.c_str());

        int retry = 0;
        while (WiFi.status() != WL_CONNECTED && retry < 20) {
          delay(500);
          Serial.print(".");
          retry++;
        }

        if (WiFi.status() == WL_CONNECTED) {
          Serial.println("\nTerhubung!");
          configTime(7 * 3600, 0, "pool.ntp.org");
          isConnected = true;
        } else {
          Serial.println("\nGagal terhubung. Coba lagi dengan format: SSID,password");
        }
      }
    }
  }
}

String getISOTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) return "2026-02-17T00:00:00Z";
  char timeStringBuff[30];
  strftime(timeStringBuff, sizeof(timeStringBuff), "%Y-%m-%dT%H:%M:%SZ", &timeinfo);
  return String(timeStringBuff);
}

void sendSensorData() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    DynamicJsonDocument doc(1024);
    doc["device_id"] = deviceId;
    doc["timestamp"] = getISOTime();

    // Data Random
    doc["ph"] = random(700, 750) / 100.0;
    doc["ketinggian_air"] = random(600, 700) / 10.0;
    doc["arah_angin"] = random(0, 360);
    doc["kecepatan_angin"] = random(10, 20);
    doc["light"] = random(1500, 2500);
    doc["curah_hujan"] = random(0, 20) / 10.0;
    doc["o2"] = random(800, 900) / 10.0;
    doc["co2"] = random(800, 950) / 100.0;
    doc["pressure"] = random(10080, 10100) / 10.0;
    doc["humidity"] = random(550, 650) / 10.0;
    doc["temperature"] = random(280, 320) / 10.0;
    doc["soil_moisture"] = random(40, 60);
    
    // Status General
    doc["battery"] = random(80, 100);
    doc["status"] = "online";

    String payload;
    serializeJson(doc, payload);

    Serial.println("\nPayload dikirim: " + payload);
    int httpCode = http.POST(payload);
    Serial.printf("HTTP Response: %d\n", httpCode);
    http.end();
  }
}

void loop() {
  if (isConnected && (millis() - lastTime > timerDelay)) {
    sendSensorData();
    lastTime = millis();
  }
}
