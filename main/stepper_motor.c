#include "stepper_motor.h"

#include "nvs_flash.h"
#include "nvs.h"

stepper_motor_config_t stepper_motor_config;

void vTaskControlMotor(void* pvParameters) {
    // Setup pins

    while (1) {

    }
}

esp_err_t loadConfig(void) {
    nvs_handle handle;
    esp_err_t err;

    err = nvs_open("storage", NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        return err;
    }
    else {
        size_t required_size = sizeof(stepper_motor_config_t);
        err = nvs_get_blob(handle, "stepper_motor_config", &stepper_motor_config, &required_size);
    }

    nvs_close(handle);

    return err;
}

esp_err_t saveConfig(void) {
    nvs_handle handle;
    esp_err_t err;

    err = nvs_open("storage", NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        return err;
    }
    else {
        err = nvs_set_blob(handle, "stepper_motor_config", &stepper_motor_config, sizeof(stepper_motor_config_t));
    }

    nvs_close(handle);

    return err;
}

esp_err_t resetConfig(void) {
    stepper_motor_config.step_config = DEFAULT_STEPPER_MOTOR_STEPS_CONFIG;
    stepper_motor_config.dir = 0;
    stepper_motor_config.speed = 0;

    return saveConfig();
}