#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "battery.h"
#include "stepper_motor.h"
#include "bt.h"

static const char* TAG = "main";

void app_main(void) {
    portENABLE_INTERRUPTS();

    ESP_LOGI(TAG, "Initializing NVS");
    esp_err_t err = nvs_flash_init();
    if(err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGW(TAG, "NVS partition was truncated and needs to be erased");
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    ESP_LOGI(TAG, "Initializing...");

    BaseType_t ret;

    TaskHandle_t motorXTaskHandle;
    ret = xTaskCreate(vTaskControlMotor, "TaskControlMotor", 2048, NULL, 1, &motorXTaskHandle);
    if (ret != pdPASS) {
        ESP_LOGE(TAG, "Failed to create TaskControlMotor task");
    }

    TaskHandle_t batteryXTaskHandle;
    ret = xTaskCreate(vTaskBattery, "TaskBattery", 2048, NULL, 1, &batteryXTaskHandle);
    if (ret != pdPASS) {
        ESP_LOGE(TAG, "Failed to create TaskControlMotor task");
    }

    // TaskHandle_t btXTaskHandle;
    // ret = xTaskCreate(vTaskBT, "TaskBT", 2048, NULL, 1, &btXTaskHandle);
    // if (ret != pdPASS) {
    //     ESP_LOGE(TAG, "Failed to create TaskControlMotor task");
    // }

    return;
}
