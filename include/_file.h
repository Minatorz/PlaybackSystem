#ifndef _FILE_H
#define _FILE_H

#include <LittleFS.h>

bool initializeFileSystem();
File openFile(const char* path, const char* mode);

#endif