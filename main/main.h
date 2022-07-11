#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef BUZZER
    #include "buzzer.h"
#endif

#define STEP_MOTOR_DIR_PIN
#define STEP_MOTOR_STEP_PIN
#define STEP_MOTOR_ENABLE_PIN

#define BATTERY_ADC_UNIT ADC_UNIT_1
#define BATTERY_ADC_CHANNEL ADC1_CHANNEL_7
#define VOLTAGE_DIVIDER_RATIO (float)1.0f

#endif // __MAIN_H__