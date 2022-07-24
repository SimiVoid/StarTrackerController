#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef BUZZER
    #include "buzzer.h"
#endif

#define STEP_MOTOR_DIR_PIN GPIO_NUM_4
#define STEP_MOTOR_STEP_PIN GPIO_NUM_16
#define STEP_MOTOR_ENABLE_PIN GPIO_NUM_23
#define STEP_MOTOR_DIAG_PIN GPIO_NUM_18

#define STEP_MOTOR_CFG_CS1_PIN GPIO_NUM_22
#define STEP_MOTOR_CFG_CS2_PIN GPIO_NUM_21
#define STEP_MOTOR_CFG_SPREAD_PIN GPIO_NUM_19

#define BATTERY_ADC_UNIT ADC_UNIT_1
#define BATTERY_ADC_CHANNEL ADC1_CHANNEL_7
#define VOLTAGE_DIVIDER_RATIO (float)1.0f

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"

#include "nvs.h"
#include "nvs_flash.h"

#endif // __MAIN_H__