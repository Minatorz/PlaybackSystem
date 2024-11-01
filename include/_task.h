#ifndef _TASK_H
#define _TASK_H

#include "_wifi.h"
#include "_webserver.h"

extern TaskHandle_t webServerTaskHandle;
extern TaskHandle_t WiFiTaskHandle;

void webServerTask(void *pvParameters);
void WiFiTask(void *pvParameters);
void allTaskHandle();

#endif