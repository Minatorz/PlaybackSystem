#ifndef _WEBSERVER_H
#define _WEBSERVER_H

#include <WebServer.h>
#include <ArduinoJson.h>

extern WebServer server;
extern String cueDataJson;
extern int currentCueIndex;

void initializeWebServer();
void handleWebServer();

#endif
