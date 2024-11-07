#include "_file.h"

bool initializeFileSystem() {
    if (!LittleFS.begin()) {
        Serial.println("LittleFS Mount Failed");
        return false;
    }
    Serial.println("LittleFS successfully Mounted!");
    return true;
}

File openFile(const char* path, const char* mode) {
    return LittleFS.open(path, mode);
}
