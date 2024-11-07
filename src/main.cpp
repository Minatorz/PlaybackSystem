#include <Arduino.h>
#include "_wifi.h"
#include "_file.h"
#include "_midi.h"
#include "_webserver.h"
#include "_task.h"

void setup() {
  Serial.begin(115200);

  initilaizeMIDI();
  if (!initializeFileSystem()) {
    return;
  }
  connectToWiFi();
  initializeWebServer();
  allTaskHandle();
}
void loop() {

}