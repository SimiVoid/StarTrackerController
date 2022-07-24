#include "stepper_motor.h"

#include "driver/gpio.h"

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

    // while (1) {
    //     stepper_motor_config_control();
    // }
}

esp_err_t loadConfig(void) {
    nvs_handle_t handle;
    esp_err_t err;

    ESP_LOGI(TAG, "Loading motor config");

    if ((err = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &handle)) != ESP_OK) {
        return err;
    }

    size_t required_size = sizeof(stepper_motor_config_t);
    err = nvs_get_blob(handle, STORAGE_KEY_CONFIG, &stepper_motor_config, &required_size);

    nvs_close(handle);

    return err;
}

esp_err_t saveConfig(void) {
    nvs_handle_t handle;
    esp_err_t err;

    ESP_LOGI(TAG, "Saving new configuration to NVS");

    if((err = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &handle)) != ESP_OK) {
        return err;
    }
    if((err =  nvs_set_blob(handle, STORAGE_KEY_CONFIG, &stepper_motor_config, sizeof(stepper_motor_config_t)) != ESP_OK)) {
        return err;
    }
    if((err = nvs_commit(handle) != ESP_OK)) {
        return err;
    }

    nvs_close(handle);

    return err;
}

esp_err_t resetConfig(void) {
    ESP_LOGI(TAG, "Resetting configuration to default");

    stepper_motor_config.step_config = DEFAULT_STEPPER_MOTOR_STEPS_CONFIG;
    stepper_motor_config.dir = 0;
    stepper_motor_config.speed = 0;

    return saveConfig();
}

static void stepper_motor_config_init(void) {
    esp_err_t err;

    if ((err = loadConfig()) != ESP_OK) {
        if ((err = resetConfig()) != ESP_OK) {
            ESP_LOGE(TAG, "Failed to reset config: %d", err);
        }
    }

    ESP_LOGI(TAG, "Config loaded");
    ESP_LOGD(TAG, "Config: %d %d %d", stepper_motor_config.step_config, stepper_motor_config.dir, stepper_motor_config.speed);
}

static void stepper_motor_gpio_init(void) {
    ESP_LOGI(TAG, "Initializing GPIO");

    gpio_pad_select_gpio(STEP_MOTOR_DIR_PIN);
    gpio_pad_select_gpio(STEP_MOTOR_STEP_PIN);
    gpio_pad_select_gpio(STEP_MOTOR_ENABLE_PIN);
    gpio_pad_select_gpio(STEP_MOTOR_DIAG_PIN);
    gpio_pad_select_gpio(STEP_MOTOR_CFG_CS1_PIN);
    gpio_pad_select_gpio(STEP_MOTOR_CFG_CS2_PIN);
    gpio_pad_select_gpio(STEP_MOTOR_CFG_SPREAD_PIN);

    gpio_set_direction(STEP_MOTOR_DIR_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(STEP_MOTOR_STEP_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(STEP_MOTOR_ENABLE_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(STEP_MOTOR_DIAG_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(STEP_MOTOR_CFG_CS1_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(STEP_MOTOR_CFG_CS2_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(STEP_MOTOR_CFG_SPREAD_PIN, GPIO_MODE_OUTPUT);
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