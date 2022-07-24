#ifndef __STEPPER_MOTOR_H__
#define __STEPPER_MOTOR_H__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "esp_system.h"
#include "main.h"

enum stepper_motor_steps {
    STEPPER_MOTOR_STEPS_1_8 = 0,
    STEPPER_MOTOR_STEPS_1_32 = 1,
    STEPPER_MOTOR_STEPS_1_64 = 2,
    STEPPER_MOTOR_STEPS_1_16 = 3,
};

enum stepper_motor_mode {
    STEPPER_MOTOR_MODE_STEALTH_CHOP = 0,
    STEPPER_MOTOR_MODE_SPREAD_CYCLE = 4
};

#define DEFAULT_STEPPER_MOTOR_STEPS_CONFIG STEPPER_MOTOR_STEPS_1_16 | STEPPER_MOTOR_MODE_SPREAD_CYCLE
#define STORAGE_NAMESPACE "stepper_motor"
#define STORAGE_KEY_CONFIG "config"

typedef struct {
    uint8_t step_config;
    uint8_t speed;
    /**
     * int8_t dir
     * -1: backward
     * 0: stop
     * 1: forward
     */
    int8_t dir;
} __attribute__ ((packed)) stepper_motor_config_t;

extern stepper_motor_config_t stepper_motor_config;

bool stepper_motor_config_are_equal(stepper_motor_config_t* config1, stepper_motor_config_t* config2);

esp_err_t loadConfig(void);
esp_err_t saveConfig(void);
esp_err_t resetConfig(void);

void vTaskControlMotor(void* pvParameters);

#endif