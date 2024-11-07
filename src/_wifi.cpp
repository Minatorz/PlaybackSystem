#include "_wifi.h"
#include "_led.h"

// const char* ssid = "Earthyy_2.4G"; //AT THE CUBE
// const char* password = "Wire4826.";

const char* ssid = "33291_2.4G"; //BJ HOME
const char* password = "107136139";

void connectToWiFi() {
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("\nConnected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    LedGreen();
}

void monitorWiFiConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected. Attempting to reconnect...");
    LedBlue();
    // Reconnect logic
    WiFi.disconnect();  // Optional: disconnect first for a clean reconnection
    connectToWiFi();    // Reconnect using the existing connection function
    
    // Check if connection is restored
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Reconnected to WiFi successfully.");
    } else {
      Serial.println("Failed to reconnect to WiFi.");
      LedRed();
    }
  } else {
    // Serial.println("WiFi is connected.");
  }
}