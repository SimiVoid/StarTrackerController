#ifndef __STEPPER_MOTOR_H__
#define __STEPPER_MOTOR_H__

#include <stdint.h>

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

typedef struct {
    uint8_t step_config;
    uint8_t speed;
    uint8_t dir;
} __attribute__ ((packed)) stepper_motor_config_t;

extern stepper_motor_config_t stepper_motor_config;

void loadEEPROMConfig(void);
void saveEEPROMConfig(void);
void resetEEPROMConfig(void);

void vTaskControlMotor(void* pvParameters);

#endif