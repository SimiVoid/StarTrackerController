#include "stepper_motor.h"

stepper_motor_config_t stepper_motor_config;

void vTaskControlMotor(void* pvParameters) {
    // Setup pins

    while (1) {

    }
}

void loadEEPROMConfig(void) {
    // Load config from EEPROM
}

void saveEEPROMConfig(void) {
    // Save config to EEPROM
}

void resetEEPROMConfig(void) {
    // Reset config to default
}