#include "_task.h"

TaskHandle_t webServerTaskHandle;
TaskHandle_t WiFiTaskHandle;

void webServerTask(void *pvParameters) {
  for (;;) {
    monitorWiFiConnection();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void WiFiTask(void *pvParameters) {
  for (;;) {
    handleWebServer();
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void allTaskHandle() {
    xTaskCreatePinnedToCore(
        webServerTask, "Web Server Task", 8192, NULL, 1, &webServerTaskHandle, 1
    );

    xTaskCreatePinnedToCore(
        WiFiTask, "WiFi Task", 4096, NULL, 1, &WiFiTaskHandle, 1
    );
}