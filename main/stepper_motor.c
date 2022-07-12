#include "stepper_motor.h"

#include "nvs_flash.h"
#include "nvs.h"

stepper_motor_config_t stepper_motor_config;

void vTaskControlMotor(void* pvParameters) {
    stepper_motor_config_init();
    stepper_motor_gpio_init();

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

static void stepper_motor_config_init(void) {
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    err = loadConfig();
    if (err != ESP_OK) {
        err = resetConfig();

        if (err != ESP_OK) {
            ESP_LOG_ERROR("Failed to reset config");
        }
    }
}

static void stepper_motor_gpio_init(void) {

}

static void stepper_motor_change_config(void) {

}