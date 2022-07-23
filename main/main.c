#include <stdio.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "main.h"
#include "battery.h"
#include "stepper_motor.h"
#include "bt.h"

void app_main(void) {
    xTaskCreate(vTaskControlMotor, "vTaskControlMotor", 1024, NULL, 2, NULL);
    xTaskCreate(vTaskBattery, "vTaskBattery", 1024, NULL, 0, NULL);
    xTaskCreate(vTaskBT, "vTaskBT", 1024, NULL, 1, NULL);
}
