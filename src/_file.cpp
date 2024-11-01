#include "_file.h"

bool initializeFileSystem() {
    if (!LittleFS.begin()) {
        Serial.println("LittleFS Mount Failed");
        return false;
    }
    return true;
}

File openFile(const char* path, const char* mode) {
    return LittleFS.open(path, mode);
}
