#include <stdio.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "main.h"

void control_step_motor_task(void* pvParameters);
void battery_task(void* pvParameters);
void bluetooth_control_task(void* pvParameters);

void app_main(void) {
    xTaskCreate(control_step_motor_task, "control_step_motor_task", 1024, NULL, 2, NULL);
    xTaskCreate(battery_task, "battery_task", 1024, NULL, 1, NULL);
    xTaskCreate(bluetooth_control_task, "bluetooth_control_task", 1024, NULL, 1, NULL);
}

void control_step_motor_task(void* pvParameters) {
    // Setup pins

    while (1) {

    }
}

void battery_task(void* pvParameters) {
    // Setup pins

    while (1) {

    }
}

void bluetooth_control_task(void* pvParameters) {

}
