#include "stepper_motor.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "nvs.h"

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"

stepper_motor_config_t stepper_motor_config;

static const char* TAG = "stepper_motor";

static void stepper_motor_config_init(void);
static void stepper_motor_gpio_init(void);
static void stepper_motor_gpio_config(void);
static void stepper_motor_config_control(void);

void vTaskControlMotor(void* pvParameters) {
    stepper_motor_config_init();
    stepper_motor_gpio_init();
    stepper_motor_gpio_config();

    while (1) {
        stepper_motor_config_control();
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
            ESP_LOGE(TAG, "Failed to reset config: %d", err);
        }
    }
}

static void stepper_motor_gpio_init(void) {

}

static void stepper_motor_gpio_config(void) {

}

static void stepper_motor_config_control(void) {
    static stepper_motor_config_t prev_config = {0};

    if(!stepper_motor_config_are_equal(&prev_config, &stepper_motor_config)) {
        stepper_motor_gpio_config();
        prev_config = stepper_motor_config;
    }
}

bool stepper_motor_config_are_equal(stepper_motor_config_t* config1, stepper_motor_config_t* config2) {
    return config1->step_config == config2->step_config &&
           config1->dir == config2->dir &&
           config1->speed == config2->speed;
}