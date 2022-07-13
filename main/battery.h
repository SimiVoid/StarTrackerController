#ifndef __BATTERY_H__
#define __BATTERY_H__

#include "main.h"

void vTaskBattery(void* pvParameters);
float getBatteryVoltage(void) const;

#endif // __BATTERY_H__