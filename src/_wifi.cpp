#include "_wifi.h"

const char* ssid = "Earthyy_2.4G";
const char* password = "Wire4826.";

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
}

void monitorWiFiConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected. Attempting to reconnect...");
    
    // Reconnect logic
    WiFi.disconnect();  // Optional: disconnect first for a clean reconnection
    connectToWiFi();    // Reconnect using the existing connection function
    
    // Check if connection is restored
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Reconnected to WiFi successfully.");
    } else {
      Serial.println("Failed to reconnect to WiFi.");
    }
  } else {
    Serial.println("WiFi is connected.");
  }
}