#ifndef __BATTERY_H__
#define __BATTERY_H__

#include "main.h"

extern float batteryVoltage;

void vTaskBattery(void* pvParameters);

#endif // __BATTERY_H__